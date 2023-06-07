/***************************************************************************//**
 * @file
 * @brief ESL Tag RAM Image logic.
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

// Single image object storage type
typedef PACKSTRUCT (struct {
  uint16_t  max_size;
  uint16_t  size;
  uint8_t   *data;
}) esl_image_object_t;

// Internal image registry type
typedef PACKSTRUCT (struct {
  esl_image_object_t  *active_image;
  uint8_t             *next_object;
  uint8_t             images_count;
}) esl_image_registry_t;

// Image registry structure
static esl_image_registry_t image_registry = { 0 };

// Image object array - max. number of elements is defined in config header
static esl_image_object_t   image_object[ESL_TAG_MAX_IMAGES] = { 0 };

// Image pool - the static storage for all image data
static uint8_t              image_pool[ESL_TAG_RAM_IMAGE_POOL_SIZE];

void esl_image_receive_finished(void)
{
}

sl_status_t esl_image_chunk_received(uint8_t const *data,
                                     uint16_t length)
{
  sl_status_t result  = SL_STATUS_INVALID_INDEX;
  esl_image_object_t *active_image = image_registry.active_image;

  // ESL RAM image: data must fit to RAM pool. Please check your config!
  sl_bt_esl_assert(length <= ESL_TAG_RAM_IMAGE_POOL_SIZE);

  // if there's a valid image object selected
  if (active_image != NULL) {
    // check for overflow condition
    if ((active_image->size + length) > active_image->max_size) {
      sl_bt_esl_log(ESL_LOG_COMPONENT_RAM_IMAGE,
                    ESL_LOG_LEVEL_ERROR,
                    "Image size overflow!");
      // invalidate the image in this case by clearing it's size
      active_image->size = 0;
      // return the error
      result = SL_STATUS_WOULD_OVERFLOW;
    } else {
      // store the data, otherwise
      memcpy(&(active_image->data[active_image->size]), data, length);
      // adjust the size
      active_image->size += length;

      // improve OTS response by not sending credit after the storage is full
      if (active_image->size < active_image->max_size) {
        result = SL_STATUS_OK;
      } else {
        result = SL_STATUS_FULL;
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
      // there's no temporary storage -> initiating image transfer by this
      // selection it will destroy the previous image content (if any)
      image_registry.active_image->size = 0;
      result = SL_STATUS_OK;
    }
  }

  return result;
}

void esl_image_init(void)
{
  // clear all images data, ESL Profile specification d09r18, Section 3.2
  memset(image_pool, 0, sizeof(image_pool));

  // initialize zero images count, set max. available size for image allocation
  image_registry.active_image = NULL;
  image_registry.next_object  = (void *)image_pool;
  image_registry.images_count = 0;
}

void esl_image_characteristic_update(void)
{
  sl_status_t sc;
  (void)sc; // suppress the compiler warning if sl_bt_esl_assert disabled
  uint8_t gatt_data = image_registry.images_count; // ESL Serv.spec. 3.7.1

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
      // get buffer size in bytes
      uint32_t  size      = (bits_per_pixel * width * height) / 8;
      // get remaining pool size
      uint32_t  available = &image_pool[ESL_TAG_RAM_IMAGE_POOL_SIZE]
                            - image_registry.next_object;
      result = SL_STATUS_ALLOCATION_FAILED;

      if (size <= available) {
        uint8_t new_image_index = image_registry.images_count;
        const sl_bt_ots_object_type_t* type;
        // currently, there are only two types of images available
        type = bits_per_pixel == 1 ? &esl_image_type_1b : &esl_image_type_2b;

        // store maximum size of the image object
        image_object[new_image_index].max_size = (uint16_t)size;
        // set actual size to zero, initially
        image_object[new_image_index].size     = 0;
        // allocate raw data pointer in the pool
        image_object[new_image_index].data     = image_registry.next_object;
        // finish registration
        ++image_registry.images_count;
        image_registry.next_object += size;
        result = esl_tag_ots_add_object(type, size, ESL_OTS_IMAGE_OBJECT);
      } else {
        sl_bt_esl_log(ESL_LOG_COMPONENT_RAM_IMAGE,
                      ESL_LOG_LEVEL_ERROR,
                      "Unable to add image due size constraints.");
      }
    } else {
      sl_bt_esl_log(ESL_LOG_COMPONENT_RAM_IMAGE,
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
    // calculate the remaining size to read
    uint16_t remaining_size = image_object[image_index].size - *offset;
    // calculate the source address to read from
    uint8_t *source_ptr     = &(image_object[image_index].data[*offset]);

    // check if image has valid data
    if (image_object[image_index].size == 0) {
      // set proper ESL ERROR to be sent to the ESL Access point
      esl_core_set_last_error(ESL_ERROR_IMAGE_NOT_AVAILABLE);
      return SL_STATUS_NOT_AVAILABLE;
    } else if (*offset > image_object[image_index].size) {
      // else check if offset is out of bounds
      esl_core_set_last_error(ESL_ERROR_UNSPECIFIED);
      return SL_STATUS_ABORT;
    } else if (*offset == image_object[image_index].size) {
      // else check an edge case: read to be finished just right now
      return SL_STATUS_OK;
    } else if (remaining_size > buf_size) {
      // or adjust remaining size to the buffer size on success
      remaining_size = buf_size;
    }

    // if there's still data to read
    if (remaining_size != 0) {
      // copy data chunk
      memcpy(target_buf, source_ptr, remaining_size);
      // shift the offset
      *offset += remaining_size;
    }

    result = SL_STATUS_OK;
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
