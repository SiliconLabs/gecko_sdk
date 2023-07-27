/***************************************************************************//**
 * @file
 * @brief ESL Tag NVM Image logic.
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/
#include <stddef.h>
#include <string.h>
#include "esl_tag_image_config.h"
#include "esl_tag_ots_server.h"
#include "esl_tag_image_core.h"
#include "esl_tag_errors.h"
#include "esl_tag_image.h"
#include "esl_tag_core.h"
#include "esl_tag_log.h"
#include "em_common.h"
#include "gatt_db.h"
#include "nvm3.h"
#include "nvm3_hal_flash.h"
#include "nvm3_default_config.h"

// Size of single image chunk
#define NVM_IMAGE_CHUNK_SIZE        (NVM3_DEFAULT_MAX_OBJECT_SIZE \
                                     - sizeof(nvm3_ObjectKey_t))
// NVM storage handle
#define NVM3_ESL_IMAGE_HANDLE       nvm3_defaultHandle
// NVM3 region to be used to store ESL image data
#define ESL_IMAGE_NVM3_REGION_BEGIN (0x04000)

// Maximum number image chunks that can be stored in ESL image data NVM region
#define ESL_IMAGE_MAX_OBJECT_COUNT  (0x02000)

// NVM3 region end of ESL image data storage space
#define ESL_IMAGE_NVM3_REGION_END   (ESL_IMAGE_NVM3_REGION_BEGIN \
                                     + ESL_IMAGE_MAX_OBJECT_COUNT)

// NVM image object storage type
typedef PACKSTRUCT (struct {
  uint16_t          max_size;
  uint16_t          size;
  nvm3_ObjectKey_t  first_nvm_obj_key;
}) esl_image_object_t;

// NVM image - single image chunk type
typedef PACKSTRUCT (struct {
  nvm3_ObjectKey_t  next_nvm_obj_key;
  uint8_t           nvm_data[NVM_IMAGE_CHUNK_SIZE];
}) esl_image_chunk_t;

// Internal NVM image registry type
typedef PACKSTRUCT (struct {
  esl_image_object_t  *active_image;
  nvm3_ObjectKey_t    next_nvm_object_key;
  uint16_t            pending_write;
  uint8_t             images_count;
}) esl_image_registry_t;

// Image registry structure
static esl_image_registry_t image_registry = { 0 };

// Image object array - max. number of elements is defined in config header
static esl_image_object_t   image_object[ESL_TAG_MAX_IMAGES] = { 0 };

// NVM image chunk buffer
static esl_image_chunk_t    image_chunk_buffer;

void esl_image_receive_finished(void)
{
  esl_image_object_t *active_image = image_registry.active_image;

  if (active_image != NULL && image_registry.pending_write != 0) {
    Ecode_t nvm_status;
    nvm3_ObjectKey_t target_key = image_chunk_buffer.next_nvm_obj_key;

    image_chunk_buffer.next_nvm_obj_key = 0;
    nvm_status = nvm3_writeData(NVM3_ESL_IMAGE_HANDLE,
                                target_key,
                                &image_chunk_buffer,
                                image_registry.pending_write + sizeof(nvm3_ObjectKey_t));

    if (nvm_status == ECODE_NVM3_OK) {
      image_registry.pending_write = 0;
    } else {
      sl_bt_esl_log(ESL_LOG_COMPONENT_NVM_IMAGE,
                    ESL_LOG_LEVEL_ERROR,
                    "ESL NVM Image: NVM operation failed with status 0x%lx!",
                    nvm_status);
    }
  }
}

sl_status_t esl_image_chunk_received(uint8_t const *data,
                                     uint32_t offset,
                                     uint16_t length)
{
  sl_status_t result  = SL_STATUS_INVALID_INDEX;
  esl_image_object_t *active_image = image_registry.active_image;

  // ESL NVM image: data must fit to NVM object. Please check NVM config!
  sl_bt_esl_assert(length <= NVM_IMAGE_CHUNK_SIZE);

  // if there's a valid image object selected
  if (active_image != NULL) {
    // check if it is the start from the beginning
    if (offset == 0) {
      // there's no temporary storage -> initiating image transfer on current
      // object at offset 0 it will destroy the previous image content (if any)
      active_image->size = 0;
      image_registry.pending_write = 0;
      // prepare buffer for the transfer
      image_chunk_buffer.next_nvm_obj_key = active_image->first_nvm_obj_key;
    }

    // check for overflow condition
    if ((active_image->size + length) > active_image->max_size) {
      sl_bt_esl_log(ESL_LOG_COMPONENT_NVM_IMAGE,
                    ESL_LOG_LEVEL_ERROR,
                    "Image size overflow!");
      // invalidate the image in this case by clearing it's size
      active_image->size = 0;
      // return the error
      result = SL_STATUS_WOULD_OVERFLOW;
    } else {
      // store the data, otherwise
      uint32_t data_index   = active_image->size % NVM_IMAGE_CHUNK_SIZE;
      uint32_t outrun_bytes = (NVM_IMAGE_CHUNK_SIZE < (data_index + length))
                              ? (data_index + length) % NVM_IMAGE_CHUNK_SIZE
                              : 0;
      length -= outrun_bytes;

      memcpy(&(image_chunk_buffer.nvm_data[data_index]), data, length);
      active_image->size           += length;
      image_registry.pending_write += length;

      result = SL_STATUS_OK;
      // check for NVM write conditions:
      if (outrun_bytes != 0 || image_registry.pending_write == NVM_IMAGE_CHUNK_SIZE) {
        Ecode_t nvm_status;
        // select target object key, increase object ID in buffer for later use
        nvm3_ObjectKey_t target_key = image_chunk_buffer.next_nvm_obj_key++;

        // check if this is the last expected image chunk - if it is, then
        // close our "poor man's linked list" by setting next key to zero
        if (active_image->size == active_image->max_size) {
          image_chunk_buffer.next_nvm_obj_key = 0;
          // improve OTS response by not sending credit after the slot is full
          result = SL_STATUS_FULL;
        }

        nvm_status = nvm3_writeData(NVM3_ESL_IMAGE_HANDLE,
                                    target_key,
                                    &image_chunk_buffer,
                                    sizeof(image_chunk_buffer));

        // if there were more bytes received than the size of one image chunk
        // then adjust buffer and registry data accordingly, save data to buffer
        if (nvm_status == ECODE_NVM3_OK) {
          image_registry.pending_write = outrun_bytes;
          memcpy(image_chunk_buffer.nvm_data, &data[length], outrun_bytes);
          active_image->size += outrun_bytes;
        } else {
          result = SL_STATUS_FAIL;
          sl_bt_esl_log(ESL_LOG_COMPONENT_NVM_IMAGE,
                        ESL_LOG_LEVEL_ERROR,
                        "ESL NVM Image: NVM operation failed with status 0x%lx!",
                        nvm_status);
        }
      }
    }
  }

  return result;
}

sl_status_t esl_image_select_object(void const *data, uint16_t length)
{
  // in case of size mismatch, this is the default answer:
  sl_status_t    result     = SL_STATUS_INVALID_HANDLE;
  const uint16_t valid_size = sizeof(esl_image_object_id_t);

  // select null object by default (in case of error)
  image_registry.active_image = NULL;

  if (length == valid_size) {
    if (*(uint16_t *)data < ESL_IMAGE_OBJECT_BASE) {
      // invalid Object ID (wrong base?)
      result = SL_STATUS_INVALID_PARAMETER;
    } else if (*(uint8_t *)data >= image_registry.images_count) {
      // image index is out of bounds
      result = SL_STATUS_INVALID_INDEX;
    } else {
      // select active image storage for the upcoming data transfer
      image_registry.active_image = &image_object[*(uint8_t *)data];
      result = SL_STATUS_OK;
    }
  }

  return result;
}

void esl_image_init(void)
{
  Ecode_t status = nvm3_open(NVM3_ESL_IMAGE_HANDLE, nvm3_defaultInit);

  if (ECODE_NVM3_OK == status) {
    size_t numberOfObjects;

    // Get the number of valid image chunk keys already in NVM3
    const nvm3_ObjectKey_t MAX_KEY = ESL_IMAGE_NVM3_REGION_END - 1;
    nvm3_ObjectKey_t       current_key;

    // Skip if we don't have image chunks at all
    while ((numberOfObjects = nvm3_enumObjects(NVM3_ESL_IMAGE_HANDLE,
                                               &current_key, 1,
                                               ESL_IMAGE_NVM3_REGION_BEGIN,
                                               MAX_KEY))) {
      // Clear all images data, ESL Profile specification d09r18, Section 3.2
      (void)nvm3_deleteObject(NVM3_ESL_IMAGE_HANDLE, current_key);
    }

    if (nvm3_repackNeeded(NVM3_ESL_IMAGE_HANDLE)) {
      (void)nvm3_repack(NVM3_ESL_IMAGE_HANDLE);
    }
  } else {
    sl_bt_esl_log(ESL_LOG_COMPONENT_NVM_IMAGE,
                  ESL_LOG_LEVEL_ERROR,
                  "ESL NVM Image: initialization failure!");
  }

  // initialize zero images count, set max. available size for image allocation
  image_registry.active_image         = NULL;
  image_registry.next_nvm_object_key  = ESL_IMAGE_NVM3_REGION_BEGIN;
  image_registry.images_count         = 0;
  image_registry.pending_write        = 0;
}

void esl_image_characteristic_update(void)
{
  sl_status_t sc;
  uint8_t gatt_data = image_registry.images_count;// ESL Serv.spec. 3.7.1

  // gattdb_esl_image_info shall contain Max_Image_Index, not the image count!
  if (gatt_data > 0) {
    gatt_data -= 1;
  }

  sc = sl_bt_gatt_server_write_attribute_value(gattdb_esl_image_info,
                                               0,
                                               sizeof(gatt_data),
                                               &gatt_data);
  sl_bt_esl_assert(sc == SL_STATUS_OK);
}

sl_status_t esl_image_add(uint16_t width, uint16_t height,
                          uint8_t bits_per_pixel)
{
  sl_status_t result = SL_STATUS_INVALID_STATE;
  esl_state_t state  = esl_core_get_status();

  // ESL Image: adding images after ESL boot event is disallowed!
  sl_bt_esl_assert(esl_state_boot == state);

  if (state == esl_state_boot) {
    result = SL_STATUS_NO_MORE_RESOURCE;

    // Refuse to add any new image if the max images count is reached!
    if (image_registry.images_count < ESL_TAG_MAX_IMAGES) {
      // get image size in bytes
      uint32_t  size      = (bits_per_pixel * width * height) / 8;
      // calculate chunks count needed to store the whole image in NVM
      uint32_t  chunks    = (size / NVM_IMAGE_CHUNK_SIZE)
                            + (size % NVM_IMAGE_CHUNK_SIZE ? 1 : 0);
      // get remaining objects count
      uint32_t  available = ESL_IMAGE_MAX_OBJECT_COUNT
                            + ESL_IMAGE_NVM3_REGION_BEGIN
                            - image_registry.next_nvm_object_key;

      result = SL_STATUS_ALLOCATION_FAILED;

      if (chunks <= available) {
        uint8_t new_image_index = image_registry.images_count;
        const sl_bt_ots_object_type_t* type;
        // currently, there are only two types of images available
        type = bits_per_pixel == 1 ? &esl_image_type_1b : &esl_image_type_2b;

        // store maximum size of the image object
        image_object[new_image_index].max_size = (uint16_t)size;
        // set actual size to zero, initially
        image_object[new_image_index].size     = 0;
        // allocate raw data pointer in the pool
        image_object[new_image_index].first_nvm_obj_key = image_registry.next_nvm_object_key;
        // finish registration
        ++image_registry.images_count;
        image_registry.next_nvm_object_key += chunks;
        result = esl_tag_ots_add_object(type, size, ESL_OTS_IMAGE_OBJECT);
      } else {
        sl_bt_esl_log(ESL_LOG_COMPONENT_NVM_IMAGE,
                      ESL_LOG_LEVEL_ERROR,
                      "Unable to add image due size constraints.");
      }
    } else {
      sl_bt_esl_log(ESL_LOG_COMPONENT_NVM_IMAGE,
                    ESL_LOG_LEVEL_ERROR,
                    "Unable to add more images, ESL_TAG_MAX_IMAGES might be low.");
    }
  }

  return result;
}

sl_status_t esl_image_get_data(uint8_t image_index, uint16_t* offset,
                               uint16_t buf_size, uint8_t *target_buf)
{
  sl_status_t result = SL_STATUS_INVALID_INDEX;

  // check if given index points to a registered image
  if (image_index < image_registry.images_count) {
    Ecode_t nvm_status;
    esl_image_object_t *image = &image_object[image_index];

    // calculate the remaining size to read
    uint16_t          remaining_size = image->size - *offset;
    // calculate the source key to read from
    nvm3_ObjectKey_t  source_key     = (*offset / NVM_IMAGE_CHUNK_SIZE)
                                       + image->first_nvm_obj_key;
    uint16_t          source_offset  = (*offset % NVM_IMAGE_CHUNK_SIZE)
                                       + sizeof(nvm3_ObjectKey_t);

    // check if image has valid data
    if (image->size == 0) {
      esl_core_set_last_error(ESL_ERROR_IMAGE_NOT_AVAILABLE);
      return SL_STATUS_NOT_AVAILABLE;
    } else if (*offset > image->size) {
      // else check if offset is out of bounds
      esl_core_set_last_error(ESL_ERROR_UNSPECIFIED);
      return SL_STATUS_ABORT;
    } else if (*offset == image->size) {
      // else check an edge case: read to be finished just right now
      return SL_STATUS_OK;
    } else if (remaining_size > buf_size) {
      // or adjust remaining size to the buffer size on success
      remaining_size = buf_size;
    }

    result = SL_STATUS_OK;

    // if there's still data to read
    while (remaining_size != 0 && result == SL_STATUS_OK) {
      uint32_t size_to_read = remaining_size;

      // check if byte count to be read is available under the current key, only
      if ((source_offset + size_to_read) > NVM3_DEFAULT_MAX_OBJECT_SIZE) {
        size_to_read = NVM3_DEFAULT_MAX_OBJECT_SIZE - source_offset;
      }
      // get data chunk(s) from NVM to the buffer

      nvm_status = nvm3_readPartialData(NVM3_ESL_IMAGE_HANDLE,
                                        source_key,
                                        target_buf,
                                        source_offset,
                                        size_to_read);
      // shift target pointer
      target_buf     += size_to_read;
      // shift the offset
      *offset        += size_to_read;
      // calculate remaining
      remaining_size -= size_to_read;
      // get next key
      source_key++;
      // set the source offset (skip forward link)
      source_offset = sizeof(nvm3_ObjectKey_t);
      // set result according to NVM status
      result = ECODE_NVM3_OK == nvm_status ? SL_STATUS_OK : SL_STATUS_FAIL;
    }
  } else {
    // signal invalid index to the remote ESL Access Point
    esl_core_set_last_error(ESL_ERROR_INVALID_IMAGE_INDEX);
  }

  return result;
}

uint8_t esl_image_get_count()
{
  return image_registry.images_count;
}

void esl_image_reset_storage(void)
{
  uint8_t image_index = image_registry.images_count;

  while (image_index--) {
    // get every image objects one by one
    esl_image_object_t *image = &image_object[image_index];
    // invalidate data content by clearing the size
    image->size = 0;
  }
}
