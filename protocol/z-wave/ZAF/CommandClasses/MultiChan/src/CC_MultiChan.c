/**
 * @file
 * Handler for Command Class Multi Channel.
 * @copyright 2018 Silicon Laboratories Inc.
 */

#include "multichannel.h"
#include <string.h>
#include <ZW_TransportSecProtocol.h>
#include <ZAF_command_class_utils.h>
#include <ZAF_Common_interface.h>
#include "ZAF_CC_Invoker.h"
#include "zaf_config_api.h"
#include "cc_multi_channel_config_api.h"

//#define DEBUGPRINT
#include "DebugPrint.h"

/// Header size of ZW_MULTI_CHANNEL_CMD_ENCAP_V2_FRAME, before encapFrame field
#define CC_MULTICHAN_ENCAP_HEADER_SIZE   4

static inline bool CC_MultiChannel_IsLongRange()
{
  return (ZAF_GetNodeID() >= LOWEST_LONG_RANGE_NODE_ID);
}

static void CmdClassMultiChannelEncapsulateCmd(
    cc_handler_input_t * input,
    cc_handler_output_t * output);

static received_frame_status_t CC_MultiChannel_handler(
    cc_handler_input_t * input,
    cc_handler_output_t * output)
{
  const uint8_t END_POINT_MASK = MULTI_CHANNEL_CAPABILITY_GET_PROPERTIES1_END_POINT_MASK_V4;

  switch(input->frame->ZW_Common.cmd)
  {
    case MULTI_CHANNEL_END_POINT_GET_V4:
      if (true == Check_not_legal_response_job(input->rx_options))
      {
        // None of the following commands support endpoint bit addressing.
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      output->frame->ZW_MultiChannelEndPointReportV4Frame.cmdClass      = COMMAND_CLASS_MULTI_CHANNEL_V4;
      output->frame->ZW_MultiChannelEndPointReportV4Frame.cmd           = MULTI_CHANNEL_END_POINT_REPORT_V4;
      output->frame->ZW_MultiChannelEndPointReportV4Frame.properties1 = (cc_multi_channel_are_endpoints_identical() == true) ?
        MULTI_CHANNEL_END_POINT_REPORT_PROPERTIES1_IDENTICAL_BIT_MASK_V4 : 0x00;

      // Fill out individual endpoints.
      output->frame->ZW_MultiChannelEndPointReportV4Frame.properties2 = END_POINT_MASK & zaf_config_get_number_of_endpoints();

      // Hardcode to zero as aggregated endpoints are deprecated.
      output->frame->ZW_MultiChannelEndPointReportV4Frame.properties3 = 0;

      output->length = sizeof(ZW_MULTI_CHANNEL_END_POINT_REPORT_V4_FRAME);
      return RECEIVED_FRAME_STATUS_SUCCESS;
      break;

    case MULTI_CHANNEL_CAPABILITY_GET_V4:
      if (true == Check_not_legal_response_job(input->rx_options))
      {
        // None of the following commands support endpoint bit addressing.
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      uint8_t endpoint = input->frame->ZW_MultiChannelCapabilityGetV4Frame.properties1 & END_POINT_MASK;
      if (endpoint == 0 || zaf_config_get_number_of_endpoints() < endpoint)
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      {
        ZW_MULTI_CHANNEL_CAPABILITY_GET_V4_FRAME * pCmdCap = (ZW_MULTI_CHANNEL_CAPABILITY_GET_V4_FRAME *)input->frame;
        cc_multi_channel_config_t const * const p_config = cc_multi_channel_get_config_endpoint(pCmdCap->properties1 & END_POINT_MASK);
        zaf_cc_list_t* pCmdClassList = GetCommandClassList((0 != ZAF_GetNodeID()), SECURITY_KEY_NONE, pCmdCap->properties1 & END_POINT_MASK);

        if (IS_NULL(pCmdClassList) || IS_NULL(pCmdClassList->cc_list) || (0 == pCmdClassList->list_size) || IS_NULL(p_config))
        {
          return RECEIVED_FRAME_STATUS_FAIL;
        }

        output->frame->ZW_MultiChannelCapabilityReport4byteV4Frame.cmdClass    = COMMAND_CLASS_MULTI_CHANNEL_V4;
        output->frame->ZW_MultiChannelCapabilityReport4byteV4Frame.cmd         = MULTI_CHANNEL_CAPABILITY_REPORT_V4;
        output->frame->ZW_MultiChannelCapabilityReport4byteV4Frame.properties1 = pCmdCap->properties1 & END_POINT_MASK;
        output->frame->ZW_MultiChannelCapabilityReport4byteV4Frame.genericDeviceClass  = p_config->generic_type;
        output->frame->ZW_MultiChannelCapabilityReport4byteV4Frame.specificDeviceClass = p_config->specific_type;

        // Copy Command Classes
        uint8_t* const cc_list_out = &output->frame->ZW_MultiChannelCapabilityReport4byteV4Frame.commandClass1;
        uint8_t cc_list_out_len = 0;

        /*
         * List of Command classes to omit:
         * - Transport Service CC must not be returned (CC:0055.02.00.21.004)
         * - Security 0 CC is not applicable in Long Range networks
         */
        const uint8_t* cc_list = pCmdClassList->cc_list;
        const bool curr_region_is_lr = CC_MultiChannel_IsLongRange();

        for (uint8_t i = 0; i < pCmdClassList->list_size; ++i) {
          if (
            cc_list[i] == COMMAND_CLASS_TRANSPORT_SERVICE_V2 ||
            (cc_list[i] == COMMAND_CLASS_SECURITY && curr_region_is_lr)
          ) {
            DPRINTF("Remove unnecessary CC: %d\n", cc_list[i]);
            continue;
          }
          cc_list_out[cc_list_out_len++] = cc_list[i];
        }

        output->length = sizeof(ZW_MULTI_CHANNEL_CAPABILITY_REPORT_1BYTE_V4_FRAME) - 1 + cc_list_out_len;
      }
      return RECEIVED_FRAME_STATUS_SUCCESS;
      break;

    case MULTI_CHANNEL_END_POINT_FIND_V4:
      if (true == Check_not_legal_response_job(input->rx_options))
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      {
        ZW_MULTI_CHANNEL_END_POINT_FIND_V4_FRAME* pcmdEpfind = (ZW_MULTI_CHANNEL_END_POINT_FIND_V4_FRAME *)input->frame;

        output->frame->ZW_MultiChannelEndPointFindReport1byteV4Frame.cmdClass = COMMAND_CLASS_MULTI_CHANNEL_V4;
        output->frame->ZW_MultiChannelEndPointFindReport1byteV4Frame.cmd = MULTI_CHANNEL_END_POINT_FIND_REPORT_V4;
        output->frame->ZW_MultiChannelEndPointFindReport1byteV4Frame.reportsToFollow = 0;
        output->frame->ZW_MultiChannelEndPointFindReport1byteV4Frame.genericDeviceClass = pcmdEpfind->genericDeviceClass;
        output->frame->ZW_MultiChannelEndPointFindReport1byteV4Frame.specificDeviceClass = pcmdEpfind->specificDeviceClass;

        uint8_t * p_frame = (uint8_t *)&output->frame->ZW_MultiChannelEndPointFindReport1byteV4Frame.variantgroup1;

        uint8_t matched_endpoints = 0;
        uint8_t number_of_endpoints = zaf_config_get_number_of_endpoints();
        for(uint8_t endpoint = 1; endpoint <= number_of_endpoints; endpoint++)
        {
          cc_multi_channel_config_t const * const p_entry =  cc_multi_channel_get_config_endpoint(endpoint);
          if( ((0xFF == pcmdEpfind->genericDeviceClass) && (0xFF == pcmdEpfind->specificDeviceClass) ) ||
              ((pcmdEpfind->genericDeviceClass == p_entry->generic_type) &&
               ((pcmdEpfind->specificDeviceClass == p_entry->specific_type) ||
               (pcmdEpfind->specificDeviceClass == 0xFF)))
            )
          {
            // Increase match counter and add the current endpoint to the frame.
            *(p_frame + matched_endpoints++) = endpoint;
          }
        }
        /*
         * CC:0060.03.0C.11.006
         *
         * In case no endpoints match the given generic and specific type, return one endpoint of
         * value 0.
         */
        if (0 == matched_endpoints)
        {
          matched_endpoints = 1;
          *p_frame = 0;
        }

        output->length = sizeof(ZW_MULTI_CHANNEL_END_POINT_FIND_REPORT_1BYTE_V4_FRAME) + matched_endpoints - 1;
      }
      return RECEIVED_FRAME_STATUS_SUCCESS;
      break;
    case MULTI_CHANNEL_CMD_ENCAP_V4:
      CmdClassMultiChannelEncapsulateCmd(input, output);
      return RECEIVED_FRAME_STATUS_SUCCESS;
      break;
    case MULTI_CHANNEL_AGGREGATED_MEMBERS_GET_V4:
      if (true == Check_not_legal_response_job(input->rx_options))
      {
        return RECEIVED_FRAME_STATUS_FAIL;
      }

      {
        uint8_t aggregated_endpoint = input->frame->ZW_MultiChannelAggregatedMembersGetV4Frame.properties1;
        output->frame->ZW_MultiChannelAggregatedMembersReport1byteV4Frame.cmdClass = COMMAND_CLASS_MULTI_CHANNEL_V4;
        output->frame->ZW_MultiChannelAggregatedMembersReport1byteV4Frame.cmd = MULTI_CHANNEL_AGGREGATED_MEMBERS_REPORT_V4;
        output->frame->ZW_MultiChannelAggregatedMembersReport1byteV4Frame.properties1 = END_POINT_MASK & aggregated_endpoint;

        // Hardcode number of bit masks to zero as aggregated endpoints are deprecated.
        output->frame->ZW_MultiChannelAggregatedMembersReport1byteV4Frame.numberOfBitMasks = 0;
      }

      // Subtract one as there are zero bitmasks in the frame.
      output->length = sizeof(ZW_MULTI_CHANNEL_AGGREGATED_MEMBERS_REPORT_1BYTE_V4_FRAME) - 1;
      return RECEIVED_FRAME_STATUS_SUCCESS;
      break;

  }
  return RECEIVED_FRAME_STATUS_NO_SUPPORT;
}

/**
 * Extracts the content of a multichannel frame and call the application command handler.
 */
static void CmdClassMultiChannelEncapsulateCmd(
    cc_handler_input_t * input,
    cc_handler_output_t * output)
{
  ZW_MULTI_CHANNEL_CMD_ENCAP_V2_FRAME *pCmd = (ZW_MULTI_CHANNEL_CMD_ENCAP_V2_FRAME *) input->frame;
  uint8_t number_of_endpoints = zaf_config_get_number_of_endpoints();

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
  // Setup source node endpoint
  input->rx_options->sourceNode.endpoint = pCmd->properties1 & MULTI_CHANNEL_CMD_ENCAP_PROPERTIES1_SOURCE_END_POINT_MASK_V4;
#pragma GCC diagnostic pop

  bool treat_as_mask = (pCmd->properties2 & MULTI_CHANNEL_CMD_ENCAP_PROPERTIES2_BIT_ADDRESS_BIT_MASK_V4);

  if (true == treat_as_mask)
  {
    /*
     * Make sure the receiving command class knows that the command was received via bit addressing
     * to avoid responding.
     */
    input->rx_options->destNode.BitAddress = 1;
  }

  // CC:0060.03.0D.11.00E: Bit zero represents endpoint 1, bit one represents endpoint 2, etc.
  uint8_t bit_number = 0;

  uint8_t mask = (pCmd->properties2 & MULTI_CHANNEL_CMD_ENCAP_PROPERTIES2_DESTINATION_END_POINT_MASK_V4);

  /*
   * Always run once as we expect to process at least one endpoint either from a decimal value or
   * from a bitmask.
   */
  do
  {
    if (true == treat_as_mask)
    {
      if (!(mask & (1 << bit_number)))
      {
        // Bit is NOT set => continue to next bit.
        continue;
      }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
      input->rx_options->destNode.endpoint = bit_number + 1;
#pragma GCC diagnostic pop
    }
    else
    {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
      // Bit addressing does not apply. Parse the field as a decimal value.
      input->rx_options->destNode.endpoint = pCmd->properties2 & 0x7f;
#pragma GCC diagnostic pop
    }

    // Received endpoint can never be higher than the configured number of endpoints.
    if (input->rx_options->destNode.endpoint > number_of_endpoints) {
      break;
    }

    /*
     * When bit addressing is used, a Command Class handler could overwrite
     * the Command Class byte of the incoming frame.
     * In this case, the command would only be executed for the first End Point.
     * To ensure that all subsequent End Points also receive the incoming
     * command, a copy of the encapsulated frame must be used for each iteration
     * of the loop.
     */
    ZW_APPLICATION_TX_BUFFER encapsulatedFrame = *(ZW_APPLICATION_TX_BUFFER*)&pCmd->encapFrame;

    if (true == ZAF_CC_MultiChannel_IsCCSupported(input->rx_options, &encapsulatedFrame))
    {
      /* Command class supported */
      cc_handler_input_t input_encap = {
        .rx_options = input->rx_options,
        .frame = &encapsulatedFrame,
        .length = input->length - CC_MULTICHAN_ENCAP_HEADER_SIZE
      };

      // No encapsulation, use original output frame.
      // Encapsulation happens later using CmdClassMultiChannelEncapsulate()
      received_frame_status_t status = invoke_cc_handler(&input_encap, output);

      if (RECEIVED_FRAME_STATUS_CC_NOT_FOUND == status) {
        Transport_ApplicationCommandHandlerEx(input_encap.rx_options, &encapsulatedFrame, input_encap.length);
      }
    }
  }
  while ((true == treat_as_mask) && (7 > ++bit_number));
}


REGISTER_CC_V5(COMMAND_CLASS_MULTI_CHANNEL_V4, MULTI_CHANNEL_VERSION_V4, CC_MultiChannel_handler, NULL, NULL, NULL, 0, NULL, NULL);

