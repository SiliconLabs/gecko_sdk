/**
 * @file
 * Command Class Notification helper module.
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */

#include <cc_notification_config_api.h>
#include <notification.h>
#include "cc_notification_io.h"
#include "zaf_config_api.h"
#include "ZAF_TSE.h"

#include <string.h> // For memset
#include "SizeOf.h"
#include <Assert.h>
//#define DEBUGPRINT
#include "DebugPrint.h"

static cc_notification_t * notifications;


/**
 * Finds first notification type for given endpoint
 * @param endpoint
 * @return index of notification if found,
 *         -1 if given endpoint has no notifications.
 */
static int get_notification_by_endpoint(uint8_t endpoint)
{
  for (uint8_t i = 0; i < cc_notification_get_config_length(); i++) {
    if (endpoint == notifications[i].endpoint) {
      return i;
    }
  }
   return -1;
}

void notification_init()
{
  // If there is existing setting saved in NVM, update notifications array with it.
  if (!cc_notification_read()) {
    //if read failed, update persistent data
    cc_notification_write();
  }
  notifications = cc_notification_get_config();
}

void notification_reset() {
  //Save default settings to persistent data
  cc_notification_write();

  notifications = cc_notification_get_config();
}

static void set_notification_status(uint8_t index, NOTIFICATION_STATUS notificationStatus) {
  if (notificationStatus != notifications[index].status) {
    DPRINTF("Change notification[%d] status from %d to %d\n", index,  notifications[index].status, notificationStatus);
    notifications[index].status = notificationStatus;
  }
}
e_cmd_handler_return_code_t handleAppNotificationSet(
    notification_type_t notificationType,
    NOTIFICATION_STATUS notificationStatus,
    uint8_t endpoint)
{
  
  if (false == cc_notification_is_type_supported(notificationType)) {
    return E_CMD_HANDLER_RETURN_CODE_FAIL;
  }

  if (NOTIFICATION_STATUS_UNSOLICIT_DEACTIVATED != notificationStatus
      && NOTIFICATION_STATUS_UNSOLICIT_ACTIVATED != notificationStatus) {
    // NotificationStatus is invalid, abort.
    return E_CMD_HANDLER_RETURN_CODE_FAIL;
  }

  if (endpoint) {
    // Enable/disable notification status for the requested EndPoint only
    int8_t index = cc_notification_get_index_by_type_and_endpoint(notificationType, endpoint);
    if (index < 0 ) {
      // Notification with {type, endpoint} combination not found
      return E_CMD_HANDLER_RETURN_CODE_FAIL;
    }
    set_notification_status((uint8_t)index, notificationStatus);
  } else {
    // Enable/disable notification status for all EndPoints in case of root node is addressed
    for (uint8_t index = 0; index < cc_notification_get_config_length(); index++) {
      if (notificationType == notifications[index].type) {
        set_notification_status((uint8_t)index, notificationStatus);
      }
    }

    cc_notification_write();
  }

  return E_CMD_HANDLER_RETURN_CODE_HANDLED;
}

uint8_t cc_notification_supported_events_bitmask(
    notification_type_t type,
    uint8_t endpoint,
    uint8_t * pBitMaskArray)
{
  uint8_t count = 0;
  if (!endpoint) {
     endpoint = zaf_config_get_default_endpoint();
  }
  int8_t index = cc_notification_get_index_by_type_and_endpoint(type, endpoint);
  if (index < 0) {
    // no such notification
    return count;
  }

  for (uint8_t i = 0; i < CC_NOTIFICATION_MAX_EVENTS_PER_NOTIFICATION; i++) {
    if (0 != notifications[index].events[i] &&
        0xFE > notifications[index].events[i]) {

      pBitMaskArray[notifications[index].events[i]/8] |= (uint8_t)(0x01<< (notifications[index].events[i]%8));

      /*calc number of bitmask bytes*/
      if (count < (notifications[index].events[i]/8 + 1)) {
        count = notifications[index].events[i]/8 + 1;
      }
    }
  }
  DPRINTF("Supported Events number of bit masks = %d\n", count);
  return count;
}

bool notification_report_get_data(notification_type_t* pType,
                                  uint8_t endpoint,
                                  uint8_t* pEvent,
                                  NOTIFICATION_STATUS* pStatus)
{
  DPRINTF("notification_report_get_data Type %d  ep %d event %d\n", *pType, endpoint, *pEvent);
  if (!endpoint) {
    endpoint = zaf_config_get_default_endpoint();
  }

  int index;
  if (NOTIFICATION_TYPE_MULTIDEVICE == *pType) {
    if (0 != * pEvent) {
      // Event must be 0 if Type is 0xFF. Requirement CC:0071.03.04.11.008
      return false;
    }
    // if notification type is not specified, take first notification type.
    index = get_notification_by_endpoint(endpoint);
    if (index < 0) {
      // No notifications for given endpoint.
      return false;
    }
    // CC:0071.03.04.12.002 Notification Type = 0xFF. Take first notification found
    *pType = cc_notification_get_type((uint8_t)index);
    *pEvent = cc_notification_get_current_event((uint8_t)index);
  } else {
    // Type specified
    index =cc_notification_get_index_by_type_and_endpoint(*pType, endpoint);
    if (index < 0) {
      return false;
    }
    if (0 != *pEvent) {
      // if event is specified, return current state/event
      int event_index = cc_notification_find_event(*pEvent, (uint8_t)index);
      if (event_index < 0) {
        //if event is non-supported, return "unknown event" (CC:0071.03.04.11.009)
        *pEvent = NOTIFICATION_EVENT_UNKNOWN_EVENT;
      } else {
        *pEvent = cc_notification_get_current_event((uint8_t)index);
      }
    }
  }
  *pStatus = cc_notification_get_status((uint8_t)index);
  return true;
}

s_CC_notification_data_t ZAF_TSE_NotificationData;

static RECEIVE_OPTIONS_TYPE_EX pRxOpt = {
    .rxStatus = 0,        /* rxStatus, verified by the TSE for Multicast */
    .securityKey = 0,     /* securityKey, ignored by the TSE */
    .sourceNode = {       /* sourceNode (nodeId, endpoint), verified against lifeline destinations by the TSE */
      .endpoint = 0,
      .res = 0
    },
    .destNode = {         /* destNode (nodeId, endpoint), verified by the TSE for local endpoint */
      .endpoint = 0,
      .BitAddress = 0
    }
};

/**
 * Prepare the data input for the TSE for Notification events.
*/
void* CC_Notification_prepare_zaf_tse_data(uint8_t index, uint8_t *pEventParameters, uint8_t eventParamLength)
{
  /*
   * Ignore bitfield conversion warnings as there is no good solution other than stop
   * using bitfields.
   */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
  /* Specify which endpoint triggered this state change  */
  pRxOpt.destNode.endpoint = cc_notification_get_endpoint(index);
#pragma GCC diagnostic pop
  /* And store the data and return the pointer */
  ZAF_TSE_NotificationData.rxOptions = pRxOpt;
  ZAF_TSE_NotificationData.index = index;
  ZAF_TSE_NotificationData.pEventParameters = pEventParameters;
  ZAF_TSE_NotificationData.eventParamLength = eventParamLength;

  return &ZAF_TSE_NotificationData;
}

JOB_STATUS CC_Notification_TriggerAndTransmit(
    uint8_t index,
    uint8_t notificationEvent,
    uint8_t * pEvPar,
    uint8_t evParLen,
    void (*pCallback)(TRANSMISSION_RESULT * pTransmissionResult),
    bool tse)
{
  if (NULL == cc_notification_get(index)) {
    // wrong index
    return JOB_STATUS_BUSY;
  }

  if ((0 != notificationEvent)
      && (cc_notification_find_event(notificationEvent, index) < 0)) {
    // No such event for specified {type, endpoint}
    return JOB_STATUS_BUSY;
  }

  notifications[index].current_event = notificationEvent;

  DPRINTF("Notification[%d] triggered, event:%d\n", index, notificationEvent);
  DPRINTF("%s Event params ", __func__);
  for (uint8_t i = 0; i< evParLen; i++) {
   DPRINTF(" %d",pEvPar[i]);
  }
  DPRINT(".\n");

  if (NOTIFICATION_STATUS_UNSOLICIT_ACTIVATED != notifications[index].status) {
    // Don't send notification report. All done, exit with success.
    return JOB_STATUS_SUCCESS;
  }

  JOB_STATUS status = CmdClassNotificationReport(index, pEvPar, evParLen, pCallback);

  if (tse) {
    void     *pData;
    /* Tell the lifeline destinations that an Endpoint state has been modified */
    pData = CC_Notification_prepare_zaf_tse_data(index, pEvPar, evParLen);
    if (pData) {
      DPRINT("Trigger TSE.\n");
      ZAF_TSE_Trigger(CC_Notification_report_stx, pData, true);
    }
  }

  return status;
}

uint8_t cc_notification_supported_notifications_bitmask(
    uint8_t * pBitMaskArray,
    uint8_t   bBitMaskLen,
    uint8_t endpoint)
{
  uint8_t count = 0;

  for(uint8_t i = 0; i < cc_notification_get_config_length(); i++) {
    if (0 != endpoint && endpoint != notifications[i].endpoint) {
      // if endoipoint is given (not root device) and it doesn't match, move on
      continue;
    }
    /*Don't write to the bitmask array if the index is out of bound or */
    /*the notification type is invalid*/
    if ((notifications[i].type != NOTIFICATION_TYPE_NONE) &&
        (bBitMaskLen > (notifications[i].type / 8)))
    {
      /* Add Bit in bit-mask byte (notifications[i].type / 8)*/
      *(pBitMaskArray + (notifications[i].type / 8)) |= (uint8_t)(1 << ((notifications[i].type) % 8));

      /* Find max number of bit masks*/
      if (count < ((notifications[i].type / 8) + 1))
      {
        count = (uint8_t)((notifications[i].type / 8) + 1);
      }
    }
  }
  DPRINTF("Supported Notifications number of bit masks = %d\n", count);
  return count;
}

