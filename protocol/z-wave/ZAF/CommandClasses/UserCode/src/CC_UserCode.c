/**
 * @file
 * @brief Handler for Command Class User Code.
 * @copyright 2018 Silicon Laboratories Inc.
 */

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/
#include <ZW_TransportLayer.h>

#include <CC_UserCode.h>
#include <cc_user_code_config.h>
#include <cc_user_code_io.h>
#include <string.h>
#include "zaf_event_distributor_soc.h"

//#define DEBUGPRINT
#include "DebugPrint.h"
#include "ZW_typedefs.h"
#include <ZAF_TSE.h>
#include "zaf_transport_tx.h"

/****************************************************************************/
/*                      PRIVATE TYPES and DEFINITIONS                       */
/****************************************************************************/

typedef struct
{
  uint8_t userIdentifier;
  uint8_t userIdStatus;
  uint8_t userCode[USERCODE_MAX_LEN];
}
user_code_report_t;

/****************************************************************************/
/*                              PRIVATE DATA                                */
/****************************************************************************/

static s_CC_userCode_data_t userCodeData = { 0 };

/****************************************************************************/
/*                              EXPORTED DATA                               */
/****************************************************************************/

/****************************************************************************/
/*                            PRIVATE FUNCTIONS                             */
/****************************************************************************/
static void CC_UserCode_report_stx(zaf_tx_options_t *tx_options, void* pData);


static received_frame_status_t
CC_UserCode_handler(
  RECEIVE_OPTIONS_TYPE_EX *rxOpt,
  ZW_APPLICATION_TX_BUFFER *pCmd,
  uint8_t cmdLength,
  ZW_APPLICATION_TX_BUFFER *pFrameOut,
  uint8_t * pFrameOutLength)
{
  switch (pCmd->ZW_Common.cmd)
  {
    case USER_CODE_GET:
      if(true == Check_not_legal_response_job(rxOpt))
      {
        /*Get/Report do not support endpoint bit-addressing */
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      size_t len = 0;
      uint8_t maxNumberOfUsers = CC_UserCode_UsersNumberReport_handler(rxOpt->destNode.endpoint);

      pFrameOut->ZW_UserCodeReport1byteFrame.cmdClass = COMMAND_CLASS_USER_CODE;
      pFrameOut->ZW_UserCodeReport1byteFrame.cmd = USER_CODE_REPORT;
      pFrameOut->ZW_UserCodeReport1byteFrame.userIdentifier = pCmd->ZW_UserCodeGetFrame.userIdentifier;

      if((0 == pCmd->ZW_UserCodeGetFrame.userIdentifier)
         || (pCmd->ZW_UserCodeGetFrame.userIdentifier > maxNumberOfUsers))
      {
        pFrameOut->ZW_UserCodeReport1byteFrame.userIdStatus = USER_ID_NO_STATUS;
      }
      else
      {
        if(false == CC_UserCode_getId_handler(
            pCmd->ZW_UserCodeGetFrame.userIdentifier,
            (user_id_status_t*)&(pFrameOut->ZW_UserCodeReport1byteFrame.userIdStatus),
            rxOpt->destNode.endpoint))
        {
          return RECEIVED_FRAME_STATUS_FAIL;
        }

        if(false == CC_UserCode_Report_handler(
            pCmd->ZW_UserCodeGetFrame.userIdentifier,
            &(pFrameOut->ZW_UserCodeReport1byteFrame.userCode1),
            &len,
            rxOpt->destNode.endpoint))
        {
          /*Job failed */
          return RECEIVED_FRAME_STATUS_FAIL; /*failing*/
        }
      }

      *pFrameOutLength = sizeof(ZW_USER_CODE_REPORT_1BYTE_FRAME) + len - 1;

      return RECEIVED_FRAME_STATUS_SUCCESS;

    case USER_CODE_SET:
      {
        bool status = true;
        uint16_t i;
        uint8_t user_code_length = cmdLength - 4;

        if (!((pCmd->ZW_UserCodeSet1byteFrame.userIdentifier <= CC_UserCode_UsersNumberReport_handler(rxOpt->destNode.endpoint)) &&
            ((USERCODE_MIN_LEN <= user_code_length) && (USERCODE_MAX_LEN >= user_code_length)))
          )
        {
          return RECEIVED_FRAME_STATUS_FAIL;
        }

        switch (pCmd->ZW_UserCodeSet1byteFrame.userIdStatus)
        {
          case USER_ID_AVAILABLE:
            for (i = 0; i < 4; i++)
            {
              *(&pCmd->ZW_UserCodeSet1byteFrame.userCode1 + i) = 0x00;
            }
            user_code_length = 4;
            break;

          case USER_ID_OCCUPIED:
          case USER_ID_RESERVED:
            // Validate user code are digits
            for(i = 0; i < user_code_length; i++)
            {
              if( ((0x30 > (uint8_t)*(&pCmd->ZW_UserCodeSet1byteFrame.userCode1 + i)) || (0x39 < (uint8_t)*(&pCmd->ZW_UserCodeSet1byteFrame.userCode1 + i))))
              {
                status = false;
                break;
              }
            }
            break;

          default:
            return RECEIVED_FRAME_STATUS_FAIL;
            break;
        }

        if (true == status)
        {
          e_cmd_handler_return_code_t return_code;
          if (0 == pCmd->ZW_UserCodeSet1byteFrame.userIdentifier)
          {
            uint8_t max_users = CC_UserCode_UsersNumberReport_handler(rxOpt->destNode.endpoint);
            for (uint8_t user_id = 1; user_id <= max_users; user_id++)
            {
              return_code = CC_UserCode_Set_handler(user_id,
                                                    pCmd->ZW_UserCodeSet1byteFrame.userIdStatus,
                                                    &(pCmd->ZW_UserCodeSet1byteFrame.userCode1),
                                                    user_code_length,
                                                    rxOpt->destNode.endpoint);

              if (E_CMD_HANDLER_RETURN_CODE_FAIL == return_code || E_CMD_HANDLER_RETURN_CODE_HANDLED == return_code)
              {
                // Build up new CC data structure
                memset(&userCodeData, 0, sizeof(s_CC_userCode_data_t));
                userCodeData.rxOptions = *rxOpt;
                userCodeData.userIdentifier = user_id;

                /* We cannot know if the same User Identifier was modified several times
                or not, so do not overwrite_previous_trigger. Also we want to know if a
                User Code was updated, even for a very short time */
                if (false == ZAF_TSE_Trigger(CC_UserCode_report_stx,
                                             (void*)&userCodeData,
                                             false))
                {
                  DPRINTF("%s(): ZAF_TSE_Trigger failed\n", __func__);
                }
              }

              if (E_CMD_HANDLER_RETURN_CODE_FAIL == return_code)
              {
                return RECEIVED_FRAME_STATUS_FAIL;
              }
            }
            return RECEIVED_FRAME_STATUS_SUCCESS;
          }
          else
          {
            return_code = CC_UserCode_Set_handler(pCmd->ZW_UserCodeSet1byteFrame.userIdentifier,
                                                  pCmd->ZW_UserCodeSet1byteFrame.userIdStatus,
                                                  &(pCmd->ZW_UserCodeSet1byteFrame.userCode1),
                                                  user_code_length,
                                                  rxOpt->destNode.endpoint);

            if (E_CMD_HANDLER_RETURN_CODE_FAIL == return_code || E_CMD_HANDLER_RETURN_CODE_HANDLED == return_code)
            {
              // Build up new CC data structure
              memset(&userCodeData, 0, sizeof(s_CC_userCode_data_t));
              userCodeData.rxOptions = *rxOpt;
              userCodeData.userIdentifier = pCmd->ZW_UserCodeGetFrame.userIdentifier;
              /* We cannot know if the same User Identifier was modified several times
                or not, so do not overwrite_previous_trigger. Also we want to know if a
                User Code was updated, even for a very short time */
              if (false == ZAF_TSE_Trigger(CC_UserCode_report_stx,
                                           (void*)&userCodeData,
                                           false))
              {
                DPRINTF("%s(): ZAF_TSE_Trigger failed\n", __func__);
              }
            }

            if (E_CMD_HANDLER_RETURN_CODE_HANDLED == return_code)
            {
              return RECEIVED_FRAME_STATUS_SUCCESS;
            }
          }
        }
        return RECEIVED_FRAME_STATUS_FAIL;
      }
      break;

    case USERS_NUMBER_GET:
      if(false == Check_not_legal_response_job(rxOpt))
      {
        pFrameOut->ZW_UsersNumberReportFrame.cmdClass = COMMAND_CLASS_USER_CODE;
        pFrameOut->ZW_UsersNumberReportFrame.cmd = USERS_NUMBER_REPORT;
        pFrameOut->ZW_UsersNumberReportFrame.supportedUsers =
          CC_UserCode_UsersNumberReport_handler( rxOpt->destNode.endpoint );

        *pFrameOutLength = sizeof(ZW_USERS_NUMBER_REPORT_FRAME);

        return RECEIVED_FRAME_STATUS_SUCCESS;
      }
      return RECEIVED_FRAME_STATUS_FAIL;
      break;
  }
  return RECEIVED_FRAME_STATUS_NO_SUPPORT;
}

JOB_STATUS CC_UserCode_SupportReport(
  AGI_PROFILE* pProfile,
  uint8_t sourceEndpoint,
  uint8_t userIdentifier,
  uint8_t userIdStatus,
  uint8_t* pUserCode,
  uint8_t userCodeLen,
  VOID_CALLBACKFUNC(pCallback)(TRANSMISSION_RESULT * pTransmissionResult))
{
  CMD_CLASS_GRP cmdGrp = {
    .cmdClass = COMMAND_CLASS_USER_CODE,
    .cmd = USER_CODE_REPORT
  };

  if ((0 == userIdentifier) || IS_NULL(pUserCode) ||
      (userCodeLen > USERCODE_MAX_LEN) || (userCodeLen < USERCODE_MIN_LEN) ||
      (2 < userIdStatus))
  {
    return JOB_STATUS_BUSY;
  }

  user_code_report_t user_code_report = {
    .userIdentifier = userIdentifier,
    .userIdStatus = userIdStatus
  };

  memcpy(user_code_report.userCode, pUserCode, userCodeLen);

  return cc_engine_multicast_request(
      pProfile,
      sourceEndpoint,
      &cmdGrp,
      (uint8_t*)&user_code_report,
      sizeof(user_code_report_t) + userCodeLen - USERCODE_MAX_LEN,
      false,
      pCallback);
}

static void
CC_UserCode_report_stx(zaf_tx_options_t *tx_options, void* pData)
{
  DPRINTF("* %s() *\n"
      "\ttxOpt.src = %d\n"
      "\ttxOpt.options %#02x\n",
      __func__, tx_options->source_endpoint, tx_options->tx_options);

  /* Prepare payload for report */
  size_t len;
  s_CC_userCode_data_t *pUserCodeData = (s_CC_userCode_data_t*)pData;

  ZW_APPLICATION_TX_BUFFER txBuf = {
    .ZW_UserCodeReport1byteFrame.cmdClass = COMMAND_CLASS_USER_CODE,
    .ZW_UserCodeReport1byteFrame.cmd = USER_CODE_REPORT,
    .ZW_UserCodeReport1byteFrame.userIdentifier = pUserCodeData->userIdentifier
  };

  if(false == CC_UserCode_getId_handler(
      pUserCodeData->userIdentifier,
      (user_id_status_t*)&(txBuf.ZW_UserCodeReport1byteFrame.userIdStatus),
      pUserCodeData->rxOptions.destNode.endpoint))
  {
    DPRINTF("%s(): CC_UserCode_getId_handler() failed. \n", __func__);
    return;

  }

  if(false == CC_UserCode_Report_handler(
      pUserCodeData->userIdentifier,
      &(txBuf.ZW_UserCodeReport1byteFrame.userCode1),
      &len,
      pUserCodeData->rxOptions.destNode.endpoint))
  {
    /*Job failed */
    DPRINTF("%s(): CC_UserCode_Report_handler() failed. \n", __func__);
    return;
  }
  tx_options->use_supervision = true;

  (void) zaf_transport_tx((uint8_t *)&txBuf,
                          sizeof(ZW_USER_CODE_REPORT_1BYTE_FRAME) + len - 1,
                          ZAF_TSE_TXCallback, tx_options);
}

e_cmd_handler_return_code_t
CC_UserCode_Set_handler(
  uint8_t identifier,
  USER_ID_STATUS id,
  uint8_t* pUserCode,
  uint8_t len,
  __attribute__((unused)) uint8_t endpoint)
{
  uint8_t i;
  bool status;
  SUserCode userCodeData = { 0 };

  // Make sure identifier is valid
  if (identifier > CC_USER_CODE_MAX_IDS) {
    return E_CMD_HANDLER_RETURN_CODE_HANDLED;
  }

  // it is possible to remove all user codes at once when identifier == 0
  if (identifier == 0) {
    if (id == USER_ID_AVAILABLE) {
      userCodeData.user_id_status = id;
      memset(userCodeData.userCode, 0xFF, len);
      userCodeData.userCodeLen = len;

      for (i = 0; i < CC_USER_CODE_MAX_IDS; i++) {
        status = CC_UserCode_Write(i + 1, &userCodeData);
        ASSERT(status);
      }
    }
  } else {
    userCodeData.user_id_status = id;
    memcpy(userCodeData.userCode, pUserCode, len);
    userCodeData.userCodeLen = len;

    status = CC_UserCode_Write(identifier, &userCodeData);
    ASSERT(status);
  }

  for (i = 0; i < len; i++) {
    DPRINTF("%d", *(pUserCode + i));
  }
  DPRINT("\r\n");
  return E_CMD_HANDLER_RETURN_CODE_HANDLED;
}

bool
CC_UserCode_getId_handler(
  uint8_t identifier,
  USER_ID_STATUS* pId,
  __attribute__((unused)) uint8_t endpoint)
{
  bool status;
  SUserCode userCodeData = { 0 };

  status = CC_UserCode_Read(identifier, &userCodeData);
  ASSERT(status);

  *pId = userCodeData.user_id_status;
  return true;
}

bool
CC_UserCode_Report_handler(
  uint8_t identifier,
  uint8_t* pUserCode,
  size_t * pLen,
  __attribute__((unused)) uint8_t endpoint)
{
  bool status;
  SUserCode userCodeData = { 0 };

  status = CC_UserCode_Read(identifier, &userCodeData);
  ASSERT(status);

  *pLen = userCodeData.userCodeLen;
  if (USERCODE_MAX_LEN >= *pLen) {
    memcpy(pUserCode, userCodeData.userCode, *pLen);

    DPRINT("hCmdUC_Report = ");
    for (size_t i = 0; i < *pLen; i++) {
      DPRINTF("%d", *(pUserCode + i));
    }
    DPRINT("\r\n");
    return true;
  }
  return false;
}

void
CC_UserCode_reset_data(void)
{
  uint8_t i;
  uint8_t defaultUserCode[] = CC_USER_CODE_DEFAULT;
  bool status;

  SUserCode userCodeDefaultData = {
    .user_id_status = USER_ID_OCCUPIED,
    .userCodeLen = sizeof(defaultUserCode)
  };
  memcpy(userCodeDefaultData.userCode, defaultUserCode, userCodeDefaultData.userCodeLen);

  status = CC_UserCode_Write(1, &userCodeDefaultData);
  ASSERT(status);

  if (CC_USER_CODE_MAX_IDS > 1) {
    for (i = 1; i < CC_USER_CODE_MAX_IDS; i++) {
      userCodeDefaultData.user_id_status = USER_ID_AVAILABLE;
      userCodeDefaultData.userCodeLen = sizeof(defaultUserCode);
      memset(userCodeDefaultData.userCode, 0xFF, userCodeDefaultData.userCodeLen);
      status = CC_UserCode_Write(i + 1, &userCodeDefaultData);
      ASSERT(status);
    }
  }
}

uint8_t
CC_UserCode_UsersNumberReport_handler(__attribute__((unused)) uint8_t endpoint)
{
  return CC_USER_CODE_MAX_IDS;
}

static bool
CC_UserCode_Validate(uint8_t identifier, const uint8_t *pCode, uint8_t len)
{
  bool status;
  SUserCode userCodeData ={ 0 };

  status = CC_UserCode_Read(identifier, &userCodeData);
  ASSERT(status);

  if ((len == userCodeData.userCodeLen)
      && ((USER_ID_OCCUPIED == userCodeData.user_id_status)
          || (USER_ID_RESERVED == userCodeData.user_id_status))) {
    if (0 == memcmp(pCode, userCodeData.userCode, len)) {
      return true;
    }
  }
  return false;
}

ZW_WEAK void
CC_UserCode_Migrate(void)
{
}

ZW_WEAK bool
CC_UserCode_Write(__attribute__((unused)) uint8_t identifier, __attribute__((unused)) SUserCode *userCodeData)
{
  return true;
}

ZW_WEAK bool
CC_UserCode_Read(__attribute__((unused)) uint8_t identifier, __attribute__((unused)) SUserCode *userCodeData)
{
  return true;
}

static uint8_t lifeline_reporting(ccc_pair_t * p_ccc_pair)
{
  p_ccc_pair->cmdClass = COMMAND_CLASS_USER_CODE;
  p_ccc_pair->cmd      = USER_CODE_REPORT;
  return 1;
}

static void
init(void)
{
  CC_UserCode_Migrate();
}

static void
reset(void)
{
  CC_UserCode_reset_data();
}

REGISTER_CC_V4(COMMAND_CLASS_USER_CODE, USER_CODE_VERSION, CC_UserCode_handler, NULL, NULL, lifeline_reporting, 0, init, reset);

static void
user_code_event_handler(const uint8_t event, const void *data)
{
  cc_user_code_event_validate_data_t* validate_data;

  switch (event) {
    case CC_USER_CODE_EVENT_VALIDATE:
      validate_data = (cc_user_code_event_validate_data_t*) data;
      if (CC_UserCode_Validate(validate_data->id, validate_data->data, validate_data->length)) {
        zaf_event_distributor_enqueue_cc_event(COMMAND_CLASS_USER_CODE, CC_USER_CODE_EVENT_VALIDATE_VALID, NULL);
      } else {
        zaf_event_distributor_enqueue_cc_event(COMMAND_CLASS_USER_CODE, CC_USER_CODE_EVENT_VALIDATE_INVALID, NULL);
      }
      break;
  }
}

ZAF_EVENT_DISTRIBUTOR_REGISTER_CC_EVENT_HANDLER(COMMAND_CLASS_USER_CODE, user_code_event_handler);
