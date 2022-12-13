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
#include "cc_notification_config_api.h"
#include <ZW_basis_api.h>
#include <ZW_TransportLayer.h>

#include <association_plus_base.h>
#include <ZW_TransportMulticast.h>
#include <string.h>
#include <ZAF_TSE.h>
#include "ZAF_tx_mutex.h"

//#define DEBUGPRINT
#include "DebugPrint.h"

static received_frame_status_t
CC_Notification_handler(
  RECEIVE_OPTIONS_TYPE_EX *rxOpt, /* IN receive options of type RECEIVE_OPTIONS_TYPE_EX  */
  ZW_APPLICATION_TX_BUFFER *pCmd, /* IN  Payload from the received frame */
  uint8_t cmdLength,               /* IN Number of command bytes including the command */
  ZW_APPLICATION_TX_BUFFER *pFrameOut,
  uint8_t * pFrameOutLength)
{
  UNUSED(pFrameOut);
  UNUSED(pFrameOutLength);

  size_t size;
  ZAF_TRANSPORT_TX_BUFFER  TxBuf;
  ZW_APPLICATION_TX_BUFFER *pTxBuf = &(TxBuf.appTxBuf);
  memset((uint8_t*)pTxBuf, 0, sizeof(ZW_APPLICATION_TX_BUFFER) );
  TRANSMIT_OPTIONS_TYPE_SINGLE_EX *pTxOptionsEx;

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
      RxToTxOptions(rxOpt, &pTxOptionsEx);

      if(3 > cmdLength) {
        DPRINT("Invalid Notification Get Frame Length\n");
        return RECEIVED_FRAME_STATUS_FAIL;
      }
      notification_type_t type;
      NOTIFICATION_STATUS status;

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

          pTxBuf->ZW_NotificationReport1byteV4Frame.mevent = pCmd->ZW_NotificationGetV4Frame.mevent;
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
            (pTxBuf->ZW_NotificationReport1byteV4Frame.properties1
                & NOTIFICATION_REPORT_PROPERTIES1_EVENT_PARAMETERS_LENGTH_MASK_V4)) -
                    sizeof(uint8_t); /* Removed sequence number*/


        if (false == notification_report_get_data(&type,
                                                  rxOpt->destNode.endpoint,
                                                  &(pTxBuf->ZW_NotificationReport1byteV4Frame.mevent),
                                                  &status)) {
          return RECEIVED_FRAME_STATUS_FAIL;
        }
      }
      // fill in common data
      pTxBuf->ZW_NotificationReport1byteV4Frame.cmdClass = COMMAND_CLASS_NOTIFICATION_V4;
      pTxBuf->ZW_NotificationReport1byteV4Frame.cmd = NOTIFICATION_REPORT_V4;
      pTxBuf->ZW_NotificationReport1byteV4Frame.v1AlarmType = 0; /*must be set to 0*/
      pTxBuf->ZW_NotificationReport1byteV4Frame.v1AlarmLevel = 0; /*must be set to 0*/
      pTxBuf->ZW_NotificationReport1byteV4Frame.reserved = 0; /*must be set to 0*/
      pTxBuf->ZW_NotificationReport1byteV4Frame.notificationStatus = (uint8_t)status;
      pTxBuf->ZW_NotificationReport1byteV4Frame.notificationType = (uint8_t)type;
      pTxBuf->ZW_NotificationReport1byteV4Frame.properties1 = 0;
      pTxBuf->ZW_NotificationReport1byteV4Frame.eventParameter1 = 0;

      if(ZAF_ENQUEUE_STATUS_SUCCESS != Transport_SendResponseEP((uint8_t *)pTxBuf,
                                                                size,
                                                                pTxOptionsEx,
                                                                NULL)) {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      return RECEIVED_FRAME_STATUS_SUCCESS;
      break;

    case NOTIFICATION_SUPPORTED_GET_V4:
      if(true == Check_not_legal_response_job(rxOpt)) {
        return RECEIVED_FRAME_STATUS_FAIL;
      }
      RxToTxOptions(rxOpt, &pTxOptionsEx);
      pTxBuf->ZW_NotificationSupportedReport1byteV4Frame.cmdClass = COMMAND_CLASS_NOTIFICATION_V4;
      pTxBuf->ZW_NotificationSupportedReport1byteV4Frame.cmd = NOTIFICATION_SUPPORTED_REPORT_V4;
      pTxBuf->ZW_NotificationSupportedReport1byteV4Frame.properties1 =
          cc_notification_supported_notifications_bitmask (
              &(pTxBuf->ZW_NotificationSupportedReport1byteV4Frame.bitMask1),
              NOTIFICATION_BITMASK_ARRAY_LENGTH,
              rxOpt->destNode.endpoint);

      /*
       * Requirement CC:0071.03.08.11.001:
       * MSb of properties1 tells whether a node supports Alarm CC V1. This implementation of
       * Notification CC does not support Alarm CC V1, hence this field is set to zero.
       */
      pTxBuf->ZW_NotificationSupportedReport1byteV4Frame.properties1 &= 0x7F;

      if(ZAF_ENQUEUE_STATUS_SUCCESS != Transport_SendResponseEP((uint8_t *)pTxBuf,
                                       sizeof(ZW_NOTIFICATION_SUPPORTED_REPORT_1BYTE_V4_FRAME) - 1 +
                                       pTxBuf->ZW_NotificationSupportedReport1byteV4Frame.properties1,
                                       pTxOptionsEx, NULL)) {
        return RECEIVED_FRAME_STATUS_FAIL;
      }
      return RECEIVED_FRAME_STATUS_SUCCESS;
      break;

    case EVENT_SUPPORTED_GET_V4:
      if(true == Check_not_legal_response_job(rxOpt)) {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      RxToTxOptions(rxOpt, &pTxOptionsEx);
      pTxBuf->ZW_EventSupportedReport1byteV4Frame.cmdClass = COMMAND_CLASS_NOTIFICATION_V4;
      pTxBuf->ZW_EventSupportedReport1byteV4Frame.cmd = EVENT_SUPPORTED_REPORT_V4;
      pTxBuf->ZW_EventSupportedReport1byteV4Frame.notificationType = pCmd->ZW_EventSupportedGetV4Frame.notificationType;
      pTxBuf->ZW_EventSupportedReport1byteV4Frame.properties1 =
          cc_notification_supported_events_bitmask((notification_type_t) pTxBuf->ZW_EventSupportedReport1byteV4Frame.notificationType,
                                                   rxOpt->destNode.endpoint,
                                                   &(pTxBuf->ZW_EventSupportedReport1byteV4Frame.bitMask1));

      pTxBuf->ZW_EventSupportedReport1byteV4Frame.properties1 &= 0x7F;
      if(ZAF_ENQUEUE_STATUS_SUCCESS != Transport_SendResponseEP((uint8_t *)pTxBuf,
                                                                sizeof(ZW_EVENT_SUPPORTED_REPORT_1BYTE_V4_FRAME) - 1 +
                                                                (pTxBuf->ZW_EventSupportedReport1byteV4Frame.properties1 & 0x1F), /*remove reserved bits*/
                                                                pTxOptionsEx, NULL)) {
        return RECEIVED_FRAME_STATUS_FAIL;
      }
      return RECEIVED_FRAME_STATUS_SUCCESS;
      break;

    default:
      break;
  }
  return RECEIVED_FRAME_STATUS_NO_SUPPORT;
}

JOB_STATUS CmdClassNotificationReport(
    uint8_t notification_index,
    uint8_t * pEvPar,
    uint8_t evParLen,
    void(*pCallback)(TRANSMISSION_RESULT * pTransmissionResult))
{
  ZW_APPLICATION_TX_BUFFER *pTxBuf = GetRequestBuffer(pCallback);
  if( IS_NULL( pTxBuf ) ) {
    /*Ongoing job is active.. just stop current job*/
    return JOB_STATUS_BUSY;
  }
  TRANSMIT_OPTIONS_TYPE_EX* pTxOptionsEx = NULL;

  pTxBuf->ZW_NotificationReport1byteV4Frame.cmdClass = COMMAND_CLASS_NOTIFICATION_V4;
  pTxBuf->ZW_NotificationReport1byteV4Frame.cmd = NOTIFICATION_REPORT_V4;
  pTxBuf->ZW_NotificationReport1byteV4Frame.v1AlarmType = 0;
  pTxBuf->ZW_NotificationReport1byteV4Frame.v1AlarmLevel = 0;
  pTxBuf->ZW_NotificationReport1byteV4Frame.reserved = 0;
  pTxBuf->ZW_NotificationReport1byteV4Frame.notificationStatus = NOTIFICATION_STATUS_UNSOLICIT_ACTIVATED;
  pTxBuf->ZW_NotificationReport1byteV4Frame.notificationType = cc_notification_get_type(notification_index);
  pTxBuf->ZW_NotificationReport1byteV4Frame.mevent = cc_notification_get_current_event(notification_index);
  memcpy(&(pTxBuf->ZW_NotificationReport1byteV4Frame.eventParameter1), pEvPar, evParLen);

  pTxBuf->ZW_NotificationReport1byteV4Frame.properties1 = evParLen;
  pTxBuf->ZW_NotificationReport1byteV4Frame.properties1 &= NOTIFICATION_REPORT_PROPERTIES1_EVENT_PARAMETERS_LENGTH_MASK_V4; /*remove sequence number and reserved flags*/

  uint8_t dataLength = sizeof(ZW_NOTIFICATION_REPORT_1BYTE_V4_FRAME) - sizeof(uint8_t) +
                       pTxBuf->ZW_NotificationReport1byteV4Frame.properties1;

  /* Remove sequence number if Sequence flag is not set*/
  if (!(NOTIFICATION_REPORT_PROPERTIES1_SEQUENCE_BIT_MASK_V4 & pTxBuf->ZW_NotificationReport1byteV4Frame.properties1))
  {
    dataLength -= (uint8_t)sizeof(uint8_t);
  }

  /*Get transmit options (node list)*/
  const agi_profile_t profile = cc_notification_get_agi_profile(notification_index);
  pTxOptionsEx = ReqNodeList( &profile,
                              (CMD_CLASS_GRP*) &(pTxBuf->ZW_Common.cmdClass),
                              cc_notification_get_endpoint(notification_index));
  if( IS_NULL( pTxOptionsEx ) )
  {
    /*Job failed, free transmit-buffer pTxBuf by cleaning mutex */
    DPRINTF("%s(): JOB_STATUS_NO_DESTINATIONS \n", __func__);
    FreeRequestBuffer();
    return JOB_STATUS_NO_DESTINATIONS;
  }

  if (ETRANSPORTMULTICAST_ADDED_TO_QUEUE != ZW_TransportMulticast_SendRequest(
      (uint8_t *)pTxBuf,
      dataLength,
      true,
      pTxOptionsEx,
      ZCB_RequestJobStatus))
  {
    /*Job failed, free transmit-buffer pTxBuf by cleaning mutex */
    FreeRequestBuffer();
    return JOB_STATUS_BUSY;
  }
  return JOB_STATUS_SUCCESS;
}

void CC_Notification_report_stx(
    TRANSMIT_OPTIONS_TYPE_SINGLE_EX txOptions,
    void * pData)
{
  DPRINTF("* %s() *\n"
      "\ttxOpt.src = %d\n"
      "\ttxOpt.options %#02x\n"
      "\ttxOpt.secOptions %#02x\n",
      __func__, txOptions.sourceEndpoint, txOptions.txOptions, txOptions.txSecOptions);

  /* Prepare payload for report */
  ZAF_TRANSPORT_TX_BUFFER  TxBuf;
  ZW_APPLICATION_TX_BUFFER *pTxBuf = &(TxBuf.appTxBuf);
  memset((uint8_t*)pTxBuf, 0, sizeof(ZW_APPLICATION_TX_BUFFER) );
  s_CC_notification_data_t* pNotificationData = (s_CC_notification_data_t*)pData;
  cc_notification_t *notification = cc_notification_get(pNotificationData->index);

  pTxBuf->ZW_NotificationReport1byteV4Frame.cmdClass = COMMAND_CLASS_NOTIFICATION_V4;
  pTxBuf->ZW_NotificationReport1byteV4Frame.cmd = NOTIFICATION_REPORT_V4;
  pTxBuf->ZW_NotificationReport1byteV4Frame.v1AlarmType = 0;
  pTxBuf->ZW_NotificationReport1byteV4Frame.v1AlarmLevel = 0;
  pTxBuf->ZW_NotificationReport1byteV4Frame.reserved = 0;
  pTxBuf->ZW_NotificationReport1byteV4Frame.notificationStatus = notification->status;
  pTxBuf->ZW_NotificationReport1byteV4Frame.notificationType = notification->type;
  pTxBuf->ZW_NotificationReport1byteV4Frame.mevent = notification->current_event;
  memcpy(&(pTxBuf->ZW_NotificationReport1byteV4Frame.eventParameter1),
         pNotificationData->pEventParameters,
         pNotificationData->eventParamLength);
  pTxBuf->ZW_NotificationReport1byteV4Frame.properties1 = pNotificationData->eventParamLength;
  pTxBuf->ZW_NotificationReport1byteV4Frame.properties1 &= NOTIFICATION_REPORT_PROPERTIES1_EVENT_PARAMETERS_LENGTH_MASK_V4; /*remove sequence number and reserved flags*/

  size_t dataLength = sizeof(ZW_NOTIFICATION_REPORT_1BYTE_V4_FRAME) - sizeof(uint8_t) +
                       pTxBuf->ZW_NotificationReport1byteV4Frame.properties1;

  /* Remove sequence number if Sequence flag is not set*/
  if (!(NOTIFICATION_REPORT_PROPERTIES1_SEQUENCE_BIT_MASK_V4 & pTxBuf->ZW_NotificationReport1byteV4Frame.properties1))
  {
    dataLength -= sizeof(uint8_t);
  }

  if (ZAF_ENQUEUE_STATUS_SUCCESS != Transport_SendRequestEP((uint8_t *)pTxBuf,
                                                            dataLength,
                                                            &txOptions,
                                                            ZAF_TSE_TXCallback))
  {
    //sending request failed
    DPRINTF("%s(): Transport_SendRequestEP() failed. \n", __func__);
  }
}

static uint8_t lifeline_reporting(ccc_pair_t * p_ccc_pair)
{
  p_ccc_pair->cmdClass = COMMAND_CLASS_NOTIFICATION_V8;
  p_ccc_pair->cmd      = NOTIFICATION_REPORT_V8;
  return 1;
}

static void init()
{
  notification_init();
}

static void reset()
{
  notification_reset();
}

REGISTER_CC_V4(COMMAND_CLASS_NOTIFICATION_V8, NOTIFICATION_VERSION_V8, CC_Notification_handler, NULL, NULL, lifeline_reporting, 0, init, reset);
