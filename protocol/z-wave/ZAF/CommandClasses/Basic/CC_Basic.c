/**
 * @file
 * Handler for Command Class Basic.
 * @copyright 2018 Silicon Laboratories Inc.
 */

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/
#include <ZAF_Common_interface.h>
#include <ZW_TransportSecProtocol.h>
#include <ZW_TransportEndpoint.h>
#include <ZW_TransportMulticast.h>
#include <ZW_transport_api.h>
#include <CC_Basic.h>
#include <CC_Common.h>
#include <string.h>
#include "ZAF_tx_mutex.h"
#include "ZAF_CC_Invoker.h"
#include "zaf_config_api.h"

//#define DEBUGPRINT
#include "DebugPrint.h"

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

/**
 * This function will be invoked when a Basic Set command is received.
 *
 * @attention This is a weak implementation of the Basic Set handler for when the application hasn't
 *            implemented this and there are no mapped CCs to Basic CC for the target endpoint.
 */
ZW_WEAK e_cmd_handler_return_code_t CC_Basic_Set_handler(uint8_t val, uint8_t endpoint)
{
  UNUSED(val);
  UNUSED(endpoint);
  return E_CMD_HANDLER_RETURN_CODE_NOT_SUPPORTED;
}

typedef struct {
  zaf_cc_list_t * pCmdClassList;
  CC_handler_map_latest_t * p_cc_output;
} context_t;

static bool cc_callback(CC_handler_map_latest_t const * const p_cc_entry, zaf_cc_context_t context) {
  context_t * p_context = context;

  for ( uint8_t i = 0; i < p_context->pCmdClassList->list_size; i++)
  {
    if (p_context->pCmdClassList->cc_list[i] != p_cc_entry->CC) {
      // Continue if there is no match on the CC.
      continue;
    }

    if ((NULL != p_cc_entry->basic_set_mapper) ||
        (NULL != p_cc_entry->basic_get_mapper))
    {
      // Either the Basic Set mapper or the Basic Get mapper is defined. Return the match.
      p_context->p_cc_output = (CC_handler_map_latest_t *)p_cc_entry;
      return true;
    }
  }
  return false;
}

/*
 * 1. Get a list of supported CCs for the specific endpoint that received the Basic Set.
 *       (Check to see if this CC is supported for current level of security.)
 * 2. Match with the list of linked CCs that has a Basic Set mapper function.
 * 3. Invoke the Basic Set mapper function.
 * 4. Invoke the corresponding CC handler.
 */
static CC_handler_map_latest_t const * get_cc_handler_map(
    RECEIVE_OPTIONS_TYPE_EX const * const rxOpt) {

  zaf_cc_list_t *pCmdClassList  = NULL;

  // Set "included" argument to true as this call will only happen if the device is included.
  pCmdClassList = GetCommandClassList(true, rxOpt->securityKey, rxOpt->destNode.endpoint);
  ASSERT(NULL != pCmdClassList);  // FATAL: Empty CC list. We should not have reached this point. Unlikely scenario!

  context_t context = {
                       .pCmdClassList = pCmdClassList,
                       .p_cc_output = NULL
  };

  ZAF_CC_foreach(cc_callback, &context);

  return context.p_cc_output;
}

static received_frame_status_t
CC_Basic_handler(
  RECEIVE_OPTIONS_TYPE_EX *rxOpt,
  ZW_APPLICATION_TX_BUFFER *pCmd,
  uint8_t cmdLength,
  ZW_APPLICATION_TX_BUFFER *pFrameOut,
  uint8_t * pFrameOutLength)
{
  UNUSED(cmdLength);

  switch (pCmd->ZW_Common.cmd)
  {
      //Must be ignored to avoid unintentional operation. Cannot be mapped to another command class.
    case BASIC_SET:
      if ((0x63 < pCmd->ZW_BasicSetV2Frame.value) && (0xFF != pCmd->ZW_BasicSetV2Frame.value))
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      /*
       * CC:0060.03.00.21.004: For backwards compatibility, the Root Device MUST mirror the
       * application functionality of End Point 1.
       */
      if ((zaf_config_get_number_of_endpoints() > 0) && (0 == rxOpt->destNode.endpoint))
      {
        rxOpt->destNode.endpoint = 1;
      }

      /*
       * Call the legacy handler first. If it's defined in the application, the application will
       * take care of the mapping. If not, the weak implementation will return no support and the
       * CC linker section will be searched.
       */
      e_cmd_handler_return_code_t return_code = CC_Basic_Set_handler(pCmd->ZW_BasicSetFrame.value, rxOpt->destNode.endpoint);

      if (E_CMD_HANDLER_RETURN_CODE_WORKING == return_code)
      {
        return RECEIVED_FRAME_STATUS_WORKING;
      }

      /* Return the handler result */
      if (E_CMD_HANDLER_RETURN_CODE_FAIL == return_code)
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      if (E_CMD_HANDLER_RETURN_CODE_HANDLED == return_code) {
        return RECEIVED_FRAME_STATUS_SUCCESS;
      }

      CC_handler_map_latest_t const * const cc_Handler_Iter = get_cc_handler_map(rxOpt);

      if ((NULL != cc_Handler_Iter) && (NULL != cc_Handler_Iter->basic_set_mapper)) {
        cc_Handler_Iter->basic_set_mapper(pCmd);

        /*
         * Invoke the corresponding handler. Since we know this is a set command, the output
         * parameters can be set to NULL.
         */
        return ZAF_CC_invoke_specific(cc_Handler_Iter, rxOpt, pCmd, cmdLength, NULL, NULL);
      }

      /*
       * At this point the Basic Set was not mapped by the application nor was a mapped function
       * found in the CC section.
       */
      return RECEIVED_FRAME_STATUS_NO_SUPPORT;
      break;

    case BASIC_GET:
    {
      if (true == Check_not_legal_response_job(rxOpt))
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      CC_handler_map_latest_t const * const cc_Handler_Iter = get_cc_handler_map(rxOpt);

      if ((NULL != cc_Handler_Iter) && (NULL != cc_Handler_Iter->basic_get_mapper)) {
        pFrameOut->ZW_BasicReportV2Frame.cmdClass = COMMAND_CLASS_BASIC;
        pFrameOut->ZW_BasicReportV2Frame.cmd      = BASIC_REPORT;

        uint8_t basicGetEndpoint = rxOpt->destNode.endpoint;

        if (0 == basicGetEndpoint) {
          basicGetEndpoint = zaf_config_get_default_endpoint();
        }

        cc_Handler_Iter->basic_get_mapper(basicGetEndpoint,
                                          &pFrameOut->ZW_BasicReportV2Frame.currentValue,
                                          &pFrameOut->ZW_BasicReportV2Frame.targetValue,
                                          &pFrameOut->ZW_BasicReportV2Frame.duration);

        *pFrameOutLength = sizeof(ZW_BASIC_REPORT_V2_FRAME);
        return RECEIVED_FRAME_STATUS_SUCCESS;
      }

      return RECEIVED_FRAME_STATUS_NO_SUPPORT;
    }
      break;

    default:
      return RECEIVED_FRAME_STATUS_NO_SUPPORT;
  }
  return RECEIVED_FRAME_STATUS_SUCCESS;
}

JOB_STATUS
CC_Basic_Report_tx(
  AGI_PROFILE* pProfile,
  uint8_t sourceEndpoint,
  uint8_t bValue,
  ZAF_TX_Callback_t callback)
{
  CMD_CLASS_GRP cmdGrp = {COMMAND_CLASS_BASIC, BASIC_REPORT};

  return cc_engine_multicast_request(
      pProfile,
      sourceEndpoint,
      &cmdGrp,
      &bValue,
      1,
      true,
      callback);
}

/**************************************************************************************************
 * Linker magic - Creates a section for an array of registered CCs and mapped CCs to the Basic CC.
 *************************************************************************************************/

REGISTER_CC_V2(COMMAND_CLASS_BASIC, BASIC_VERSION_V2, CC_Basic_handler);
