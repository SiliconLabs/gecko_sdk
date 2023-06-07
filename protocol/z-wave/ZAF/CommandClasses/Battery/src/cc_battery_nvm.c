/**
 * @file
 * Command Class Battery I/O handling with NVM
 * @copyright 2022 Silicon Laboratories Inc.
 */

#include <string.h>
#include "cc_battery_io.h"
#include <ZAF_nvm_app.h>
#include <ZAF_nvm.h>
#include <ZAF_file_ids.h>
#include <zpal_misc.h>
#include <Assert.h>
//#define DEBUGPRINT
#include "DebugPrint.h"

bool
cc_battery_write(SBatteryData* battery_data)
{
  zpal_status_t status;

  status = ZAF_nvm_write(ZAF_FILE_ID_BATTERYDATA, battery_data, sizeof(SBatteryData));

  return status == ZPAL_STATUS_OK;
}

bool
cc_battery_read(SBatteryData* battery_data)
{
  zpal_status_t status;

  status = ZAF_nvm_read(ZAF_FILE_ID_BATTERYDATA, battery_data, sizeof(SBatteryData));

  return status == ZPAL_STATUS_OK;
}
