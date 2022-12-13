/**
 * @file
 * Command Class User Code I/O handling with NVM
 * @copyright 2022 Silicon Laboratories Inc.
 */

#include <string.h>
#include <cc_door_lock_io.h>
#include <cc_door_lock_config_api.h>
#include <ZAF_nvm_app.h>
#include <ZAF_nvm.h>
#include <ZAF_file_ids.h>
#include <zpal_nvm.h>
#include <zpal_misc.h>
#include <Assert.h>
//#define DEBUGPRINT
#include "DebugPrint.h"

// Matches FILE_ID_APPLICATIONDATA from DoorLockKeyPad sample app
#define DOOR_LOCK_DATA_LEGACY_FILE_ID (0x00000)

bool
cc_door_lock_write(cc_door_lock_data_t *door_lock_data)
{
  zpal_status_t status;

  status = ZAF_nvm_write(ZAF_FILE_ID_CC_DOOR_LOCK, door_lock_data, sizeof(cc_door_lock_data_t));

  return status == ZPAL_STATUS_OK;
}

bool
cc_door_lock_read(cc_door_lock_data_t *door_lock_data)
{
  zpal_status_t status;

  status = ZAF_nvm_read(ZAF_FILE_ID_CC_DOOR_LOCK, door_lock_data, sizeof(cc_door_lock_data_t));

  return status == ZPAL_STATUS_OK;
}

void
cc_door_lock_migrate(void)
{
  zpal_status_t status;
  cc_door_lock_data_t application_data;
  cc_door_lock_data_t door_lock_data;

  // On initial implementation of DoorLock Command Class
  // This information belonged to the application
  // From SDK 7.19.0 this information was moved to the command class
  // In order to migrate, we need to read the `DOOR_LOCK_DATA_LEGACY_FILE_ID` which points to
  // `FILE_ID_APPLICATIONDATA` Compare some constant values `type`, `insideDoorHandleMode`
  // and `outsideDoorHandleMode`. If those constants matches, migrate the file to the new location
  status = ZAF_nvm_app_read(DOOR_LOCK_DATA_LEGACY_FILE_ID, &application_data, sizeof(cc_door_lock_data_t));
  if (status != ZPAL_STATUS_OK) {
    return;
  }

  door_lock_data.type = cc_door_lock_get_operation_type();
  door_lock_data.insideDoorHandleMode  = cc_door_lock_get_supported_inside_handles();
  door_lock_data.outsideDoorHandleMode = cc_door_lock_get_supported_outside_handles();

  if (application_data.type != door_lock_data.type
      || application_data.insideDoorHandleMode != door_lock_data.insideDoorHandleMode
      || application_data.outsideDoorHandleMode != door_lock_data.outsideDoorHandleMode) {
    return;
  }

  ZAF_nvm_write(ZAF_FILE_ID_CC_DOOR_LOCK, &application_data, sizeof(cc_door_lock_data_t));
  ZAF_nvm_app_erase_object(DOOR_LOCK_DATA_LEGACY_FILE_ID);
}
