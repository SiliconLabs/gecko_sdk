/**
 * @file
 * Command Class Multilevel Switch I/O handling with NVM
 * @copyright 2022 Silicon Laboratories Inc.
 */
#include "cc_multilevel_switch_support_io.h"

#include <ZAF_nvm_app.h>
#include <ZAF_nvm.h>
#include <ZAF_file_ids.h>
#include <zpal_nvm.h>
#include <zpal_misc.h>
//#define DEBUGPRINT
#include "DebugPrint.h"

#define CC_MULTILEVEL_SWITCH_OFFSET(a) (ZAF_FILE_ID_CC_MULTILEVEL_SWITCH_BASE + a)

/**
 * Structure that holds the data that can be persisted
 */
typedef struct {
  uint8_t current_value;      ///< Current value of actuator
  uint8_t endpoint;           ///< Endpoint that supports colorId
} multilevel_switch_data_t;

bool
cc_multilevel_switch_write(uint8_t multilevel_component_id, cc_multilevel_switch_t *multilevel_switch)
{
  zpal_status_t status;
  multilevel_switch_data_t multilevel_switch_data = {
    .endpoint = multilevel_switch->endpoint,
    .current_value = ZAF_Actuator_GetCurrentValue(&multilevel_switch->actuator)
  };
  status = ZAF_nvm_write(CC_MULTILEVEL_SWITCH_OFFSET(multilevel_component_id), &multilevel_switch_data, sizeof(multilevel_switch_data));

  return status == ZPAL_STATUS_OK;
}

bool
cc_multilevel_switch_read(uint8_t multilevel_component_id, cc_multilevel_switch_t *multilevel_switch)
{
  zpal_status_t status;
  multilevel_switch_data_t multilevel_switch_data = { 0 };

  status = ZAF_nvm_read(CC_MULTILEVEL_SWITCH_OFFSET(multilevel_component_id), &multilevel_switch_data, sizeof(multilevel_switch_data));
  if (status != ZPAL_STATUS_OK) {
    return false;
  }

  multilevel_switch->endpoint = multilevel_switch_data.endpoint;
  ZAF_Actuator_Set(&multilevel_switch->actuator, multilevel_switch_data.current_value, 0);

  return true;
}
