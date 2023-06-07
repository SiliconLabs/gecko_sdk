/***************************************************************************//**
 * @file
 * @brief ESL Tag abstract display logic.
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
#include "gatt_db.h"
#include "esl_tag_log.h"
#include "esl_tag_display.h"
#include "esl_tag_image_core.h"

#define ESL_LAST_IMAGE_UNSET  -1

// Display Information type - same format as defined in ESL Specification,
// Display Information Characteristic definition
PACKSTRUCT(struct esl_display_info_t {
  uint16_t              width;
  uint16_t              height;
  esl_display_type_t    type;
});

// Extended display object type, containing additional function pointers for
// internal use
typedef PACKSTRUCT (struct {
  esl_display_info_p    info;
  esl_va_method_p       init;
  esl_va_method_p       write_image;
  int32_t               last_image;
}) esl_display_object_t;

// Internal display registry type
typedef PACKSTRUCT (struct {
  esl_display_object_t  *next_object;
  uint8_t               display_count;
}) esl_display_registry_t;

// Display info array - max. number of elements is defined in config header
static struct esl_display_info_t  display_info[ESL_TAG_MAX_DISPLAYS];

// Display object array for internal use
static esl_display_object_t       display_object[ESL_TAG_MAX_DISPLAYS];

// Display registry structure
static esl_display_registry_t     display_registry;

/******************************************************************************
 * Display info getter - returns with all display data in a format which can be
 * easily write to the ESL Display Information characteristic.
 * @param[out] uint16_t* size of the ESL display info data
 * @param[out] void** pointer to the serialized ESL Display Info data
 *****************************************************************************/
static inline void esl_display_get_all_info(uint16_t *data_size, void **out)
{
  *data_size = display_registry.display_count * sizeof(struct esl_display_info_t);

  // having the characteristic with zero length of data is invalid!
  if (*data_size == 0) {
    // this is an 'user error' condition, still the GATT req. shall succeed once
    // the ESL access point tries to read it, thus we need at least one full set
    // to be reported even if this "shadow" display itself will be invalid
    // (0 x 0 pixels, type 0) and hence non-functioning without registering at
    // least one during the ESL boot event, properly
    *data_size = sizeof(struct esl_display_info_t);
  }

  *out = (void *)display_info;
}

void esl_display_init(void)
{
  uint8_t i;
  // clear all display data
  memset(display_info, 0, sizeof(display_info));
  memset(display_object, 0, sizeof(display_object));

  // 1:1 assign every display_info to the corresponding display_objects
  for (i = 0; i < ESL_TAG_MAX_DISPLAYS; ++i) {
    display_object[i].info = &display_info[i];
    // set an invalid last image index to all, too
    display_object[i].last_image = ESL_LAST_IMAGE_UNSET;
  }
  // initialize zero display count, prepare display creation / allocation
  display_registry.next_object  = display_object;
  display_registry.display_count = 0;
}

void esl_display_bt_on_event(sl_bt_msg_t *evt)
{
  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_bt_evt_gatt_server_user_read_request_id:
      if (evt->data.evt_gatt_server_user_read_request.characteristic == gattdb_esl_display_info) {
        uint8_t*  raw_info;
        uint16_t  raw_size, offset;
        uint16_t  mtu_size;
        sl_status_t sc;
        (void)sc; // suppress the compiler warning if sl_bt_esl_assert disabled

        // get pointer first to the beginning of the display_info packed struct
        esl_display_get_all_info(&raw_size, (void *)&raw_info);
        // then get the offset value from the request
        offset = evt->data.evt_gatt_server_user_read_request.offset;
        // finally, adjust offset and size
        raw_info += offset;
        raw_size -= offset;

        // check current ATT_MTU limits
        sc = sl_bt_gatt_server_get_mtu(evt->data.evt_gatt_server_user_read_request.connection, &mtu_size);
        sl_bt_esl_assert(sc == SL_STATUS_OK);

        // sl_bt_gatt_server_send_user_read_response allows (ATT_MTU - 1) size
        --mtu_size; // of data to be sent at once!

        // and limit the actual data size to be sent accordingly
        raw_size = raw_size > mtu_size ? mtu_size : raw_size;

        // send data (chunk, maybe more read reqs. with offset != 0 will follow)
        sc = sl_bt_gatt_server_send_user_read_response(evt->data.evt_gatt_server_user_read_request.connection,
                                                       evt->data.evt_gatt_server_user_read_request.characteristic,
                                                       SL_STATUS_OK,
                                                       raw_size,
                                                       raw_info,
                                                       NULL);
        sl_bt_esl_assert(sc == SL_STATUS_OK);
      }
      break;

    default:
      break;
  }
}

sl_status_t esl_display_refresh(uint8_t display_index, uint8_t *image_index)
{
  sl_status_t result = SL_STATUS_INVALID_INDEX;

  if (display_index < display_registry.display_count) {
    esl_display_object_t  *active_display = &display_object[display_index];

    // Invalid display object!
    sl_bt_esl_assert(NULL != active_display->write_image);

    if (active_display->last_image != ESL_LAST_IMAGE_UNSET) {
      result = (*active_display->write_image)(ESL_DISPLAY_WRITE_FUNC_PARAMETERS_COUNT,
                                              display_index,
                                              active_display->last_image);
      if (image_index != NULL) {
        *image_index = (uint8_t)active_display->last_image;
      }
    } else {
      esl_core_set_last_error(ESL_ERROR_IMAGE_NOT_AVAILABLE);
    }
  } else {
    esl_core_set_last_error(ESL_ERROR_INVALID_PARAMETER);
  }

  return result;
}

sl_status_t esl_display_update(uint8_t display_index, uint8_t image_index)
{
  return esl_display_set_image(display_index, image_index);
}

sl_status_t esl_display_create(uint16_t width,
                               uint16_t height,
                               esl_display_type_t type,
                               esl_display_info_p *info)
{
  sl_status_t result = SL_STATUS_NO_MORE_RESOURCE;

  if (display_registry.display_count < ESL_TAG_MAX_DISPLAYS) {
    // select an available slot for object creation
    *info           = display_registry.next_object->info;
    (*info)->width  = width;
    (*info)->height = height;
    (*info)->type   = type;
    result          = SL_STATUS_OK;
  }

  return result;
}

sl_status_t esl_display_add(esl_display_info_p info,
                            esl_va_method_p init_func,
                            esl_va_method_p write_func)
{
  sl_status_t result = SL_STATUS_INVALID_STATE;
  esl_state_t state  = esl_core_get_status();

  // ESL Display: write function is mandatory!
  sl_bt_esl_assert(NULL != write_func);

  // ESL Display: adding displays after the boot event is disallowed!
  sl_bt_esl_assert(esl_state_boot == state);

  if (state == esl_state_boot) {
    result = SL_STATUS_NO_MORE_RESOURCE;

    if (display_registry.display_count < ESL_TAG_MAX_DISPLAYS) {
      display_registry.next_object->info        = info;
      display_registry.next_object->write_image = write_func;

      if (init_func != NULL) {
        // call with current display index
        init_func(ESL_DISPLAY_INIT_FUNC_PARAMETERS_COUNT,
                  display_registry.display_count);
      }

      // increase display count
      ++display_registry.display_count;
      // get next object
      ++display_registry.next_object;
      result = SL_STATUS_OK;
    } else {
      sl_bt_esl_log(ESL_LOG_COMPONENT_DISPLAY,
                    ESL_LOG_LEVEL_ERROR,
                    "Unable to add more display, ESL_TAG_MAX_DISPLAYS might be low.");
    }
  }

  return result;
}

sl_status_t esl_display_set_image(uint8_t display_index, uint8_t image_index)
{
  sl_status_t result = SL_STATUS_INVALID_INDEX;

  if (display_index < display_registry.display_count) {
    esl_display_object_t  *active_display;

    active_display = &display_object[display_index];

    // Invalid display object!
    sl_bt_esl_assert(NULL != active_display->write_image);

    result = (*active_display->write_image)(ESL_DISPLAY_WRITE_FUNC_PARAMETERS_COUNT,
                                            display_index, image_index);
    active_display->last_image = image_index;
  } else {
    esl_core_set_last_error(ESL_ERROR_INVALID_PARAMETER);
  }

  return result;
}

sl_status_t esl_display_get_width(uint8_t display_index, uint16_t *width)
{
  sl_status_t result = SL_STATUS_INVALID_INDEX;

  if (display_index < display_registry.display_count) {
    esl_display_object_t  *active_display = &display_object[display_index];
    *width = active_display->info->width;
    result = SL_STATUS_OK;
  }

  return result;
}

sl_status_t esl_display_get_height(uint8_t display_index, uint16_t *height)
{
  sl_status_t result = SL_STATUS_INVALID_INDEX;

  if (display_index < display_registry.display_count) {
    esl_display_object_t  *active_display = &display_object[display_index];
    *height = active_display->info->height;
    result = SL_STATUS_OK;
  }

  return result;
}

sl_status_t esl_display_get_type(uint8_t display_index,
                                 esl_display_type_t *type)
{
  sl_status_t result = SL_STATUS_INVALID_INDEX;

  if (display_index < display_registry.display_count) {
    esl_display_object_t  *active_display = &display_object[display_index];
    *type = active_display->info->type;
    result = SL_STATUS_OK;
  }

  return result;
}

uint8_t esl_display_get_count()
{
  return display_registry.display_count;
}
