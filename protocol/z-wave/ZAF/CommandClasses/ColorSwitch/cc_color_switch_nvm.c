/**
 * @file
 * Command Class Color Switch I/O handling with NVM
 * @copyright 2022 Silicon Laboratories Inc.
 */
#include <cc_color_switch_io.h>

#include <ZAF_nvm_app.h>
#include <ZAF_nvm.h>
#include <ZAF_file_ids.h>
#include <zpal_nvm.h>
#include <zpal_misc.h>
//#define DEBUGPRINT
#include "DebugPrint.h"

#define CC_COLOR_SWITCH_OFFSET(a) (ZAF_FILE_ID_CC_COLOR_SWITCH_BASE + a)

/**
 * Structure that holds the data that can be persisted
 */
typedef struct {
  uint8_t current_value;      ///< Current value of actuator
  uint8_t endpoint;           ///< Endpoint that supports colorId
  EColorComponents color_id;  ///< Color Component ID
} color_switch_data_t;

bool
cc_color_switch_write(uint8_t color_component_id, s_colorComponent *color_component)
{
  zpal_status_t status;
  color_switch_data_t color_switch_data;

  color_switch_data.endpoint = color_component->ep;
  color_switch_data.current_value = ZAF_Actuator_GetCurrentValue(&color_component->obj);
  color_switch_data.color_id = color_component->colorId;

  status = ZAF_nvm_write(CC_COLOR_SWITCH_OFFSET(color_component_id), &color_switch_data, sizeof(color_switch_data_t));

  return status == ZPAL_STATUS_OK;
}

bool
cc_color_switch_read(uint8_t color_component_id, s_colorComponent *color_component)
{
  zpal_status_t status;
  color_switch_data_t color_switch_data;

  status = ZAF_nvm_read(CC_COLOR_SWITCH_OFFSET(color_component_id), &color_switch_data, sizeof(color_switch_data_t));
  if (status != ZPAL_STATUS_OK) {
    return false;
  }

  color_component->colorId = color_switch_data.color_id;
  color_component->ep = color_switch_data.endpoint;
  ZAF_Actuator_Set(&color_component->obj, color_switch_data.current_value, 0);

  return true;
}
