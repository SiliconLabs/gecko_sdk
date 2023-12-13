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
  cc_handler_input_t * input,
  cc_handler_output_t * output)
{
  switch (input->frame->ZW_Common.cmd)
  {
      //Must be ignored to avoid unintentional operation. Cannot be mapped to another command class.
    case BASIC_SET:
    {
      /*
       * CC:0000.00.00.11.021:
       * The outgoing frame's encapsulation must match the incoming frame's.
       * Create a copy of the received frame's properties, so that it can be
       * passed to the CC mapped to the Basic CC with the mirrored End Point.
       * The original received frame's destination End Point must not be
       * modified if it was the Root Device, as this would incorrectly trigger
       * Multichannel encapsulation.
       */
      RECEIVE_OPTIONS_TYPE_EX rxOptMirrored = *input->rx_options;

      if ((0x63 < input->frame->ZW_BasicSetV2Frame.value) &&
          (0xFF != input->frame->ZW_BasicSetV2Frame.value))
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      /*
       * CC:0060.03.00.21.004: For backwards compatibility, the Root Device MUST mirror the
       * application functionality of End Point 1.
       */
      if ((zaf_config_get_number_of_endpoints() > 0) && (0 == input->rx_options->destNode.endpoint))
      {
        rxOptMirrored.destNode.endpoint = 1;
      }

      CC_handler_map_latest_t const * const cc_Handler_Iter = get_cc_handler_map(&rxOptMirrored);

      if ((NULL != cc_Handler_Iter) && (NULL != cc_Handler_Iter->basic_set_mapper)) {
        cc_Handler_Iter->basic_set_mapper(input->frame);

        return ZAF_CC_invoke_specific(cc_Handler_Iter, input, output);

      }

      /*
       * At this point the Basic Set was not mapped by the application nor was a mapped function
       * found in the CC section.
       */
      return RECEIVED_FRAME_STATUS_NO_SUPPORT;
    }
      break;

    case BASIC_GET:
    {
      if (true == Check_not_legal_response_job(input->rx_options))
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      CC_handler_map_latest_t const * const cc_Handler_Iter = get_cc_handler_map(input->rx_options);

      if ((NULL != cc_Handler_Iter) && (NULL != cc_Handler_Iter->basic_get_mapper)) {
        output->frame->ZW_BasicReportV2Frame.cmdClass = COMMAND_CLASS_BASIC;
        output->frame->ZW_BasicReportV2Frame.cmd      = BASIC_REPORT;

        uint8_t basicGetEndpoint = input->rx_options->destNode.endpoint;

        if (0 == basicGetEndpoint) {
          basicGetEndpoint = zaf_config_get_default_endpoint();
        }

        cc_Handler_Iter->basic_get_mapper(basicGetEndpoint,
                                          &output->frame->ZW_BasicReportV2Frame.currentValue,
                                          &output->frame->ZW_BasicReportV2Frame.targetValue,
                                          &output->frame->ZW_BasicReportV2Frame.duration);

        output->length = sizeof(ZW_BASIC_REPORT_V2_FRAME);
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
  CMD_CLASS_GRP cmdGrp = {
    .cmdClass=COMMAND_CLASS_BASIC,
    .cmd=BASIC_REPORT
  };

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

REGISTER_CC_V5(COMMAND_CLASS_BASIC, BASIC_VERSION_V2, CC_Basic_handler, NULL, NULL, NULL, 0, NULL, NULL);
