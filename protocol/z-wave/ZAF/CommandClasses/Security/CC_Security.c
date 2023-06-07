/**
 * @file
 * Handles SECURITY_COMMANDS_SUPPORTED_GET and SECURITY_2_COMMANDS_SUPPORTED_GET for endpoints.
 *
 * The Z-Wave stack will handle the above commands for the root device.
 * @copyright 2022 Silicon Laboratories Inc.
 */

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/
#include <ZW_basis_api.h>
#include <ZW_TransportLayer.h>
#include <ZW_TransportMulticast.h>
#include <string.h>
#include <ZAF_Common_interface.h>

/****************************************************************************/
/*                      PRIVATE TYPES and DEFINITIONS                       */
/****************************************************************************/

/****************************************************************************/
/*                              PRIVATE DATA                                */
/****************************************************************************/

/****************************************************************************/
/*                              EXPORTED DATA                               */
/****************************************************************************/

/****************************************************************************/
/*                            PRIVATE FUNCTIONS                             */
/****************************************************************************/



/*==============================   handleCommandClassBinarySwitch  ============
**
**  Function:  handler for Binary Switch Info CC
**
**  Side effects: None
**
**--------------------------------------------------------------------------*/
static received_frame_status_t
CC_Security_handler(
  RECEIVE_OPTIONS_TYPE_EX *rxOpt, /* IN receive options of type RECEIVE_OPTIONS_TYPE_EX  */
  ZW_APPLICATION_TX_BUFFER *pCmd, /* IN  Payload from the received frame */
  uint8_t cmdLength,              /* IN Number of command bytes including the command */
  ZW_APPLICATION_TX_BUFFER * pFrameOut,
  uint8_t * pLengthOut)
{
  uint8_t length;
  UNUSED(cmdLength);

  if(true == Check_not_legal_response_job(rxOpt))
  {
    /*Get/Report do not support endpoint bit-addressing */
    return RECEIVED_FRAME_STATUS_FAIL;
  }

  if ((SECURITY_COMMANDS_SUPPORTED_GET != pCmd->ZW_Common.cmd) &&
      (SECURITY_2_COMMANDS_SUPPORTED_GET != pCmd->ZW_Common.cmd))
  {
    return RECEIVED_FRAME_STATUS_NO_SUPPORT;
  }

  uint8_t* pPayload = NULL;
  security_key_t secureLevel;
  zaf_cc_list_t *pCmdClassList  = NULL;

  if ((SECURITY_KEY_S2_UNAUTHENTICATED <= rxOpt->securityKey) &&  // We must respond to "S0 SUPPORTED GET" also when included at higher S2 level
      (SECURITY_KEY_S0 >= rxOpt->securityKey) &&
	  (SECURITY_COMMANDS_SUPPORTED_GET == pCmd->ZW_Common.cmd) && (COMMAND_CLASS_SECURITY == pCmd->ZW_Common.cmdClass))
  {
    pFrameOut->ZW_SecurityCommandsSupportedReport1byteFrame.cmdClass = COMMAND_CLASS_SECURITY;
    pFrameOut->ZW_SecurityCommandsSupportedReport1byteFrame.cmd = SECURITY_COMMANDS_SUPPORTED_REPORT;
    pFrameOut->ZW_SecurityCommandsSupportedReport1byteFrame.reportsToFollow = 0;
    length = sizeof(pFrameOut->ZW_SecurityCommandsSupportedReport1byteFrame) - 3;
    secureLevel = SECURITY_KEY_S0;
    pPayload = &pFrameOut->ZW_SecurityCommandsSupportedReport1byteFrame.commandClassSupport1;
  }
  else if ((SECURITY_KEY_S2_UNAUTHENTICATED <= rxOpt->securityKey) && (SECURITY_KEY_S2_ACCESS >= rxOpt->securityKey) &&
		   (SECURITY_2_COMMANDS_SUPPORTED_GET == pCmd->ZW_Common.cmd) && (COMMAND_CLASS_SECURITY_2 == pCmd->ZW_Common.cmdClass))
  {
    pFrameOut->ZW_SecurityCommandsSupportedReport1byteFrame.cmdClass = COMMAND_CLASS_SECURITY_2;
    pFrameOut->ZW_SecurityCommandsSupportedReport1byteFrame.cmd = SECURITY_2_COMMANDS_SUPPORTED_REPORT;
    length = 2; /*SECURITY_2_COMMANDS_SUPPORTED_REPORT = 2*/
    secureLevel = rxOpt->securityKey;//SECURITY_KEY_S2_UNAUTHENTICATED;
    pPayload = &pFrameOut->ZW_SecurityCommandsSupportedReport1byteFrame.reportsToFollow;
  }
  else
  {
    /*Job failed */
    return RECEIVED_FRAME_STATUS_NO_SUPPORT;
  }

  pCmdClassList = GetCommandClassList((0 != ZAF_GetNodeID()), secureLevel, rxOpt->destNode.endpoint);
  if(NULL != pCmdClassList)
  {
    length += pCmdClassList->list_size;
    memcpy(pPayload, pCmdClassList->cc_list, pCmdClassList->list_size);
  }

  *pLengthOut = length;

  return RECEIVED_FRAME_STATUS_SUCCESS;
}

/*
 * Register for both S0 and S2. Version is set to zero because the version is set by and fetched
 * from the Z-Wave protocol.
 */
REGISTER_CC_V2(COMMAND_CLASS_SECURITY,   0x00, CC_Security_handler);
REGISTER_CC_V2(COMMAND_CLASS_SECURITY_2, 0x00, CC_Security_handler);