/**
 * @file
 * Command Class Notification I/O handling with NVM
 * @copyright 2022 Silicon Laboratories Inc.
 */
#include "cc_notification_io.h"
#include "cc_notification_config_api.h"
#include <cc_notification_config.h>

#include <ZAF_nvm_app.h>
#include <ZAF_nvm.h>
#include <ZAF_file_ids.h>
#include <zpal_misc.h>
//#define DEBUGPRINT
#include "DebugPrint.h"


/**
 * Structure that holds the data that can be persisted
 * Includes notification status (on/Off)
 */
typedef struct {
  NOTIFICATION_STATUS status;
} notification_data_t;

/// All statuses are saved in one big struct.
typedef struct notifications_data_t_
{
  notification_data_t notifications[CC_NOTIFICATION_MAX_NOTIFICATIONS];
} notifications_data_t;

#define ZAF_FILE_SIZE_NOTIFICATIONDATA     (sizeof(notifications_data_t))

bool cc_notification_write (void) {

  notifications_data_t notifications_data;
  cc_notification_t *notifications = cc_notification_get_config();

  for(uint8_t i = 0; i <cc_notification_get_config_length(); i++) {
    notifications_data.notifications[i].status = notifications[i].status;
  }
  zpal_status_t status = ZAF_nvm_write(ZAF_FILE_ID_NOTIFICATIONDATA,
                                        &notifications_data,
                                        ZAF_FILE_SIZE_NOTIFICATIONDATA);
  return status == ZPAL_STATUS_OK;
}

bool cc_notification_read (void) {
  size_t dataLen;

  if ((ZPAL_STATUS_OK !=
      ZAF_nvm_get_object_size(ZAF_FILE_ID_NOTIFICATIONDATA, &dataLen))
      || (ZAF_FILE_SIZE_NOTIFICATIONDATA != dataLen)) {
    return false;
  }

  notifications_data_t notifications_data;
  if (ZPAL_STATUS_OK != ZAF_nvm_read(ZAF_FILE_ID_NOTIFICATIONDATA,
                                      &notifications_data,
                                      ZAF_FILE_SIZE_NOTIFICATIONDATA)) {
    return false;
  }

  cc_notification_t *notifications = cc_notification_get_config();
  for(uint8_t i = 0; i <cc_notification_get_config_length(); i++) {
    notifications[i].status = notifications_data.notifications[i].status;
  }
  return true;
}
