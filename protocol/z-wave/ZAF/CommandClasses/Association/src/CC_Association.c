/**
 * @file CC_Association.c
 * Handler for Command Class Association.
 * @copyright 2018 Silicon Laboratories Inc.
 */

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/

#include <association_plus_base.h>
#include <CC_Association.h>
#include <string.h>
#include "CC_AssociationGroupInfo.h"
//#define DEBUGPRINT
#include "DebugPrint.h"

/****************************************************************************/
/*                      PRIVATE TYPES and DEFINITIONS                       */
/****************************************************************************/

/****************************************************************************/
/*                              PRIVATE DATA                                */
/****************************************************************************/

// Nothing here.

/****************************************************************************/
/*                              EXPORTED DATA                               */
/****************************************************************************/

// Nothing here.

/****************************************************************************/
/*                            PRIVATE FUNCTIONS                             */
/****************************************************************************/

static received_frame_status_t
CC_Association_handler(
    RECEIVE_OPTIONS_TYPE_EX *rxOpt,
    ZW_APPLICATION_TX_BUFFER *pCmd,
    uint8_t cmdLength,
    ZW_APPLICATION_TX_BUFFER *pFrameOut,
    uint8_t * pFrameOutLength
)
{
  switch (pCmd->ZW_Common.cmd)
  {
    case ASSOCIATION_GET_V2:
      {
        if (true == Check_not_legal_response_job(rxOpt))
        {
          // Get/Report do not support endpoint bit addressing.
          return RECEIVED_FRAME_STATUS_FAIL;
        }

        AssociationGet(
            rxOpt->destNode.endpoint,
            (uint8_t *)&pCmd->ZW_AssociationGetFrame.cmdClass,
            (uint8_t *)pFrameOut,
            pFrameOutLength);

        return RECEIVED_FRAME_STATUS_SUCCESS;
      }
      break;

    case ASSOCIATION_SET_V2:
      if (E_CMD_HANDLER_RETURN_CODE_FAIL == handleAssociationSet(
          rxOpt->destNode.endpoint,
          (ZW_MULTI_CHANNEL_ASSOCIATION_SET_1BYTE_V2_FRAME*)pCmd,
          cmdLength,
          COMMAND_CLASS_ASSOCIATION))
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }
      return RECEIVED_FRAME_STATUS_SUCCESS;

    case ASSOCIATION_REMOVE_V2:
      if (3 > cmdLength)
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }
      if (E_CMD_HANDLER_RETURN_CODE_FAIL == AssociationRemove(
          pCmd->ZW_AssociationRemove1byteV2Frame.groupingIdentifier,
          rxOpt->destNode.endpoint,
          (ZW_MULTI_CHANNEL_ASSOCIATION_REMOVE_1BYTE_V2_FRAME*)pCmd,
          cmdLength))
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }
      return RECEIVED_FRAME_STATUS_SUCCESS;
      break;

    case ASSOCIATION_GROUPINGS_GET_V2:
        DPRINT("ASSOCIATION_GROUPINGS_GET_V2\r\n");

        if(true == Check_not_legal_response_job(rxOpt))
        {
          return RECEIVED_FRAME_STATUS_FAIL;
        }
        
        pFrameOut->ZW_AssociationGroupingsReportV2Frame.cmdClass = COMMAND_CLASS_ASSOCIATION;
        pFrameOut->ZW_AssociationGroupingsReportV2Frame.cmd = ASSOCIATION_GROUPINGS_REPORT_V2;
        pFrameOut->ZW_AssociationGroupingsReportV2Frame.supportedGroupings = CC_AGI_groupCount_handler(rxOpt->destNode.endpoint);

        *pFrameOutLength = sizeof(pFrameOut->ZW_AssociationGroupingsReportV2Frame);

        return RECEIVED_FRAME_STATUS_SUCCESS;

    case ASSOCIATION_SPECIFIC_GROUP_GET_V2:
        DPRINT("ASSOCIATION_GROUPINGS_GET_V2\r\n");

        if(true == Check_not_legal_response_job(rxOpt))
        {
          return RECEIVED_FRAME_STATUS_FAIL;
        }
        
        pFrameOut->ZW_AssociationSpecificGroupReportV2Frame.cmdClass = COMMAND_CLASS_ASSOCIATION;
        pFrameOut->ZW_AssociationSpecificGroupReportV2Frame.cmd = ASSOCIATION_SPECIFIC_GROUP_REPORT_V2;
        pFrameOut->ZW_AssociationSpecificGroupReportV2Frame.group = ApplicationGetLastActiveGroupId();

        *pFrameOutLength = sizeof(pFrameOut->ZW_AssociationSpecificGroupReportV2Frame);

        return RECEIVED_FRAME_STATUS_SUCCESS;
  }
  return RECEIVED_FRAME_STATUS_NO_SUPPORT;
}

static void init(void)
{
  CC_Association_Init();
}

static void reset(void)
{
  CC_Association_Reset();
}

REGISTER_CC_V4(COMMAND_CLASS_ASSOCIATION, ASSOCIATION_VERSION_V2, CC_Association_handler,NULL,NULL,NULL,0,init, reset);
