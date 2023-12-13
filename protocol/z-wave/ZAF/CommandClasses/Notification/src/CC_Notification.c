/**
 * @file
 * Handler for Command Class Notification.
 *
 * @startuml
 * title Trigger Notification
 * skinparam handwritten false
 * skinparam backgroundColor #MintCream
 *
 * == EVENT Triggered ==
 * rnote over App #Coral: Notification EVENT\n happened
 * App->CC_Notification: CC_Notification_TriggerAndTransmit(id, EVENT, param=0)
 *
 * activate CC_Notification #BlanchedAlmond
 * rnote over CC_Notification #BlanchedAlmond: Set current event to EVENT
 *
 * CC_Notification->AGI_Profile: CmdClassNotificationReport()
 * rnote over AGI_Profile: Notify associations\n in AGI Profile
 * activate CC_Notification #BurlyWood
 * rnote over CC_Notification  #BurlyWood: Notification\n Status ON?
 *
 *
 * CC_Notification->Lifeline: ZAF_TSE_Trigger()
 * rnote over Lifeline: Inform Lifeline\nif associations exist
 *
 * deactivate CC_Notification
 * deactivate CC_Notification
 *
 *
 * == EVENT Stopped ==
 * rnote over App #Lightgreen: Notification EVENT\n stopped
 * App->CC_Notification: CC_Notification_TriggerAndTransmit(id, 0, param=EVENT)
 *
 * activate CC_Notification #BlanchedAlmond
 * rnote over CC_Notification #BlanchedAlmond: Set current event to Idle
 *
 * CC_Notification->AGI_Profile:CmdClassNotificationReport()
 * rnote over AGI_Profile: Notify associations\n in AGI Profile
 *
 * activate CC_Notification #BurlyWood
 * rnote over CC_Notification  #BurlyWood: Notification\n Status ON?
 *
 * CC_Notification->Lifeline: ZAF_TSE_Trigger()
 * rnote over Lifeline: Inform Lifeline\nif associations exist
 *
 * deactivate CC_Notification
 * deactivate CC_Notification
 *
 * @enduml
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */

#include <CC_Notification.h>
#include "ZW_TransportEndpoint.h"
#include "cc_notification_config_api.h"
#include <string.h>
#include <ZAF_TSE.h>
#include "zaf_transport_tx.h"
#include "zaf_config_api.h"
#include "cc_notification_io.h"

//#define DEBUGPRINT
#include "DebugPrint.h"

void CC_Notification_report_stx(zaf_tx_options_t *tx_options, void* pData);

JOB_STATUS CmdClassNotificationReport(
    uint8_t notification_index,
    uint8_t * pEvPar,
    uint8_t evParLen,
    void(*pCallback)(TRANSMISSION_RESULT * pTransmissionResult));

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

static void init(void)
{
  // If there is existing setting saved in NVM, update notifications array with it.
  if (!cc_notification_read()) {
    //if read failed, update persistent data
    cc_notification_write();
  }
  notifications = cc_notification_get_config();
}

static void reset(void) {
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

/**
 * @brief Application specific Notification Set cmd handler.
 * @param[in] notificationType notification type
 * @param[in] notificationStatus notification status of type NOTIFICATION_STATUS
 * @param[in] endpoint is the destination endpoint
 * @return command handler return code
 * @private
 */
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

/**
 * Fills in Bit Mask with supported events for given notification.
 * Used to prepare data for Event Supported Report Command
 *
 * Finds notification based on {type, endpoint} values
 * an d creates bitmask with supported events. @see cc_notification_config.c
 *
 * @param[in] type Notification type
 * @param[in] endpoint Notification Endpoint
 * @param[out] pBitMaskArray The Bit Mask of supported Events within the requested Notification Type.
 * @return Number of Bit Masks fields (1-31) used in bytes
 * @private
 */
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

  uint8_t number_of_events = cc_notification_config_get_number_of_events(index);

  for (uint8_t i = 0; i < number_of_events; i++) {
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

/**
 * Prepares data for Notification Report command as response to
 * Notification Get
 *
 * @param[in,out] pType Notification Type
 * @param[in] endpoint Notification endpoint
 * @param[in,out] pEvent If specified, current state of notification
 * @param[out] pStatus Current Notification status - On/Off
 * @return true if notification with {type,endpoint} exists,
 *         false if input data wasn't correct
 * @private
 */
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

s_CC_notification_data_t ZAF_TSE_NotificationData = { 0 };

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

/**
 * Fills in Bit Mask with supported Notification Types.
 *
 * Used to prepare data for Notification Supported Report Command
 * as response to Notification Supported Get Command.
 *
 * @param[out] pBitMaskArray The Bit Mask fields describe the supported Notification
 *             Type(s) by the device
 * @param[in] bBitMaskLen The length of the Bit Mask fields
 * @param[in] endpoint is the destination endpoint
 * @return Number of Bit Masks fields (1-31) used, in bytes.
 * @private
 */
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

static received_frame_status_t
CC_Notification_handler(
  RECEIVE_OPTIONS_TYPE_EX *rxOpt, /* IN receive options of type RECEIVE_OPTIONS_TYPE_EX  */
  ZW_APPLICATION_TX_BUFFER *pCmd, /* IN  Payload from the received frame */
  uint8_t cmdLength,               /* IN Number of command bytes including the command */
  ZW_APPLICATION_TX_BUFFER *pFrameOut,
  uint8_t * pFrameOutLength)
{
  size_t size;

  DPRINTF("CmdClassAlarm %d\r\n", pCmd->ZW_Common.cmd);
  switch (pCmd->ZW_Common.cmd)
  {
    case NOTIFICATION_SET_V4:
      if (E_CMD_HANDLER_RETURN_CODE_FAIL == handleAppNotificationSet(
          (notification_type_t)pCmd->ZW_NotificationSetV4Frame.notificationType,
          (NOTIFICATION_STATUS)pCmd->ZW_NotificationSetV4Frame.notificationStatus,
          rxOpt->destNode.endpoint)) {
        return RECEIVED_FRAME_STATUS_FAIL;
      }
      return RECEIVED_FRAME_STATUS_SUCCESS;
      break;

    case NOTIFICATION_GET_V4:
      if(true == Check_not_legal_response_job(rxOpt)) {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      if(3 > cmdLength) {
        DPRINT("Invalid Notification Get Frame Length\n");
        return RECEIVED_FRAME_STATUS_FAIL;
      }
      notification_type_t type;
      NOTIFICATION_STATUS status;

      // fill in common data
      pFrameOut->ZW_NotificationReport1byteV4Frame.cmdClass = COMMAND_CLASS_NOTIFICATION_V4;
      pFrameOut->ZW_NotificationReport1byteV4Frame.cmd = NOTIFICATION_REPORT_V4;
      pFrameOut->ZW_NotificationReport1byteV4Frame.v1AlarmType = 0; /*must be set to 0*/
      pFrameOut->ZW_NotificationReport1byteV4Frame.v1AlarmLevel = 0; /*must be set to 0*/
      pFrameOut->ZW_NotificationReport1byteV4Frame.reserved = 0; /*must be set to 0*/
      pFrameOut->ZW_NotificationReport1byteV4Frame.properties1 = 0;
      pFrameOut->ZW_NotificationReport1byteV4Frame.eventParameter1 = 0;
      pFrameOut->ZW_NotificationReport1byteV4Frame.mevent = 0;

      if(3 == cmdLength) {
        DPRINT("ZW_ALARM_GET_V1_FRAME\n");

        size = sizeof(ZW_NOTIFICATION_REPORT_1BYTE_V4_FRAME) - 2; //Remove event-parameter and sequence number
        type = 0xFF;
        status = 0xFF;
      } else {
        if (4 == cmdLength) {
          DPRINT("ZW_ALARM_GET_V2_FRAME\n");
        } else {
          DPRINT("ZW_NOTIFICAION_GET\n");

          pFrameOut->ZW_NotificationReport1byteV4Frame.mevent = pCmd->ZW_NotificationGetV4Frame.mevent;
          DPRINTF("Type %d/event %d/ EP %d\n",
                  pCmd->ZW_NotificationGetV4Frame.notificationType,
                  pCmd->ZW_NotificationGetV4Frame.mevent,
                  rxOpt->destNode.endpoint);
        }
        if (!cc_notification_is_type_supported(pCmd->ZW_NotificationGetV4Frame.notificationType)
            && NOTIFICATION_TYPE_MULTIDEVICE != pCmd->ZW_NotificationGetV4Frame.notificationType) {
          return RECEIVED_FRAME_STATUS_FAIL;
        }

        type = pCmd->ZW_NotificationGetV4Frame.notificationType;

        size = (sizeof(ZW_NOTIFICATION_REPORT_1BYTE_V4_FRAME) - sizeof(uint8_t) +
            (pFrameOut->ZW_NotificationReport1byteV4Frame.properties1
                & NOTIFICATION_REPORT_PROPERTIES1_EVENT_PARAMETERS_LENGTH_MASK_V4)) -
                    sizeof(uint8_t); /* Removed sequence number*/

        if (false == notification_report_get_data(&type,
                                                  rxOpt->destNode.endpoint,
                                                  &(pFrameOut->ZW_NotificationReport1byteV4Frame.mevent),
                                                  &status)) {
          return RECEIVED_FRAME_STATUS_FAIL;
        }
      }

      pFrameOut->ZW_NotificationReport1byteV4Frame.notificationStatus = (uint8_t)status;
      pFrameOut->ZW_NotificationReport1byteV4Frame.notificationType = (uint8_t)type;

      *pFrameOutLength = size;

      return RECEIVED_FRAME_STATUS_SUCCESS;

    case NOTIFICATION_SUPPORTED_GET_V4:
      if(true == Check_not_legal_response_job(rxOpt)) {
        return RECEIVED_FRAME_STATUS_FAIL;
      }
      memset(&pFrameOut->ZW_NotificationSupportedReport1byteV4Frame.bitMask1, 0, NOTIFICATION_BITMASK_ARRAY_LENGTH);
      pFrameOut->ZW_NotificationSupportedReport1byteV4Frame.cmdClass = COMMAND_CLASS_NOTIFICATION_V4;
      pFrameOut->ZW_NotificationSupportedReport1byteV4Frame.cmd = NOTIFICATION_SUPPORTED_REPORT_V4;
      pFrameOut->ZW_NotificationSupportedReport1byteV4Frame.properties1 =
          cc_notification_supported_notifications_bitmask (
              &(pFrameOut->ZW_NotificationSupportedReport1byteV4Frame.bitMask1),
              NOTIFICATION_BITMASK_ARRAY_LENGTH,
              rxOpt->destNode.endpoint);

      /*
       * Requirement CC:0071.03.08.11.001:
       * MSb of properties1 tells whether a node supports Alarm CC V1. This implementation of
       * Notification CC does not support Alarm CC V1, hence this field is set to zero.
       */
      pFrameOut->ZW_NotificationSupportedReport1byteV4Frame.properties1 &= 0x7F;

      *pFrameOutLength = sizeof(ZW_NOTIFICATION_SUPPORTED_REPORT_1BYTE_V4_FRAME) - 1 +
                                       pFrameOut->ZW_NotificationSupportedReport1byteV4Frame.properties1;

      return RECEIVED_FRAME_STATUS_SUCCESS;

    case EVENT_SUPPORTED_GET_V4:
      if(true == Check_not_legal_response_job(rxOpt)) {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      memset(&pFrameOut->ZW_NotificationSupportedReport1byteV4Frame.bitMask1, 0, NOTIFICATION_BITMASK_ARRAY_LENGTH);
      pFrameOut->ZW_EventSupportedReport1byteV4Frame.cmdClass = COMMAND_CLASS_NOTIFICATION_V4;
      pFrameOut->ZW_EventSupportedReport1byteV4Frame.cmd = EVENT_SUPPORTED_REPORT_V4;
      pFrameOut->ZW_EventSupportedReport1byteV4Frame.notificationType = pCmd->ZW_EventSupportedGetV4Frame.notificationType;
      pFrameOut->ZW_EventSupportedReport1byteV4Frame.properties1 =
          cc_notification_supported_events_bitmask((notification_type_t) pFrameOut->ZW_EventSupportedReport1byteV4Frame.notificationType,
                                                   rxOpt->destNode.endpoint,
                                                   &(pFrameOut->ZW_EventSupportedReport1byteV4Frame.bitMask1));

      pFrameOut->ZW_EventSupportedReport1byteV4Frame.properties1 &= 0x7F;

      *pFrameOutLength = sizeof(ZW_EVENT_SUPPORTED_REPORT_1BYTE_V4_FRAME) - 1 +
                          (pFrameOut->ZW_EventSupportedReport1byteV4Frame.properties1 & 0x1F); /*remove reserved bits*/

      return RECEIVED_FRAME_STATUS_SUCCESS;

    default:
      break;
  }
  return RECEIVED_FRAME_STATUS_NO_SUPPORT;
}

/**
 * Transmits a Notification Report.
 *
 * See SDS11060.doc "Table of defined Notification Types & Events".
 * @param notification_index index of notification to be reported
 *                            in notifications array
 * @param pEvPar List of parameters to be reported
 * @param evParLen Length of event parameters list
 * @param pCallback callback function returning state on job
 * @return JOB_STATUS
 * @private
 */
JOB_STATUS CmdClassNotificationReport(
    uint8_t notification_index,
    uint8_t * pEvPar,
    uint8_t evParLen,
    void(*pCallback)(TRANSMISSION_RESULT * pTransmissionResult))
{
  ZW_NOTIFICATION_REPORT_1BYTE_V4_FRAME frame = {
    .cmdClass = COMMAND_CLASS_NOTIFICATION_V4,
    .cmd = NOTIFICATION_REPORT_V4,
    .v1AlarmType = 0,
    .v1AlarmLevel = 0,
    .reserved = 0,
    .notificationStatus = NOTIFICATION_STATUS_UNSOLICIT_ACTIVATED,
    .notificationType = cc_notification_get_type(notification_index),
    .mevent = cc_notification_get_current_event(notification_index),
    .properties1 = evParLen & NOTIFICATION_REPORT_PROPERTIES1_EVENT_PARAMETERS_LENGTH_MASK_V4 /*remove sequence number and reserved flags*/
  };
  memcpy(&(frame.eventParameter1), pEvPar, evParLen);

  uint8_t dataLength = sizeof(ZW_NOTIFICATION_REPORT_1BYTE_V4_FRAME) - sizeof(uint8_t) +
                       frame.properties1 - sizeof(CMD_CLASS_GRP);

  /* Remove sequence number if Sequence flag is not set*/
  if (!(NOTIFICATION_REPORT_PROPERTIES1_SEQUENCE_BIT_MASK_V4 & frame.properties1))
  {
    dataLength -= (uint8_t)sizeof(uint8_t);
  }
  
  const agi_profile_t profile = cc_notification_get_agi_profile(notification_index);

  return cc_engine_multicast_request(&profile,
      cc_notification_get_endpoint(notification_index),
      (CMD_CLASS_GRP *) &frame,
      &frame.v1AlarmType,
      dataLength,
      true,
      pCallback);
}

/**
 * Send report via lifeLine when a change happens.
 *
 * Callback used by TSE module. Refer to @ref ZAF_TSE.h for more details.
 *
 * @param tx_options txOptions
 * @param pData Command payload for the report
 */
void
CC_Notification_report_stx(zaf_tx_options_t *tx_options, void* pData)
{
  DPRINTF("* %s() *\n"
      "\ttxOpt.src = %d\n"
      "\ttxOpt.options %#02x\n",
      __func__, tx_options->source_endpoint, tx_options->tx_options);

  /* Prepare payload for report */
  s_CC_notification_data_t* pNotificationData = (s_CC_notification_data_t*)pData;
  cc_notification_t *notification = cc_notification_get(pNotificationData->index);

  ZW_APPLICATION_TX_BUFFER txBuf = {
    .ZW_NotificationReport1byteV4Frame.cmdClass = COMMAND_CLASS_NOTIFICATION_V4,
    .ZW_NotificationReport1byteV4Frame.cmd = NOTIFICATION_REPORT_V4,
    .ZW_NotificationReport1byteV4Frame.v1AlarmType = 0,
    .ZW_NotificationReport1byteV4Frame.v1AlarmLevel = 0,
    .ZW_NotificationReport1byteV4Frame.reserved = 0,
    .ZW_NotificationReport1byteV4Frame.notificationStatus = notification->status,
    .ZW_NotificationReport1byteV4Frame.notificationType = notification->type,
    .ZW_NotificationReport1byteV4Frame.mevent = notification->current_event,
    .ZW_NotificationReport1byteV4Frame.properties1 = pNotificationData->eventParamLength & NOTIFICATION_REPORT_PROPERTIES1_EVENT_PARAMETERS_LENGTH_MASK_V4 /*remove sequence number and reserved flags*/
  };

  memcpy(&(txBuf.ZW_NotificationReport1byteV4Frame.eventParameter1),
         pNotificationData->pEventParameters,
         pNotificationData->eventParamLength);

  size_t dataLength = sizeof(ZW_NOTIFICATION_REPORT_1BYTE_V4_FRAME) - sizeof(uint8_t) +
                       txBuf.ZW_NotificationReport1byteV4Frame.properties1;

  /* Remove sequence number if Sequence flag is not set*/
  if (!(NOTIFICATION_REPORT_PROPERTIES1_SEQUENCE_BIT_MASK_V4 & txBuf.ZW_NotificationReport1byteV4Frame.properties1))
  {
    dataLength -= sizeof(uint8_t);
  }
  tx_options->use_supervision = true;

  (void) zaf_transport_tx((uint8_t *)&txBuf,
                          dataLength,
                          ZAF_TSE_TXCallback,
                          tx_options);
}

static uint8_t lifeline_reporting(ccc_pair_t * p_ccc_pair)
{
  p_ccc_pair->cmdClass = COMMAND_CLASS_NOTIFICATION_V8;
  p_ccc_pair->cmd      = NOTIFICATION_REPORT_V8;
  return 1;
}

REGISTER_CC_V4(COMMAND_CLASS_NOTIFICATION_V8, NOTIFICATION_VERSION_V8, CC_Notification_handler, NULL, NULL, lifeline_reporting, 0, init, reset);
