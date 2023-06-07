/***************************************************************************//**
 * @file
 * @brief Routines for the ZLL Utility Client plugin.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include "app/framework/include/af.h"

#include "zap-cluster-command-parser.h"

bool emberAfZllCommissioningClusterEndpointInformationCallback(EmberAfClusterCommand *cmd)
{
  (void)cmd;

#ifdef SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
  sl_zcl_zll_commissioning_cluster_endpoint_information_command_t cmd_data;

  if (zcl_decode_zll_commissioning_cluster_endpoint_information_command(cmd, &cmd_data)
      != EMBER_ZCL_STATUS_SUCCESS) {
    return false;
  }

  emberAfZllCommissioningClusterPrint("RX: EndpointInformation ");
  emberAfZllCommissioningClusterDebugExec(emberAfPrintBigEndianEui64(cmd_data.ieeeAddress));
  emberAfZllCommissioningClusterPrintln(", 0x%2x, 0x%x, 0x%2x, 0x%2x, 0x%x",
                                        cmd_data.networkAddress,
                                        cmd_data.endpointId,
                                        cmd_data.profileId,
                                        cmd_data.deviceId,
                                        cmd_data.version);
#endif // SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT

  emberAfSendImmediateDefaultResponse(EMBER_ZCL_STATUS_SUCCESS);
  return true;
}

bool emberAfZllCommissioningClusterGetGroupIdentifiersResponseCallback(EmberAfClusterCommand *cmd)
{
  (void)cmd;

#ifdef SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
  sl_zcl_zll_commissioning_cluster_get_group_identifiers_response_command_t cmd_data;
  uint16_t groupInformationRecordListLen;
  uint16_t groupInformationRecordListIndex;
  uint8_t i;

  if (zcl_decode_zll_commissioning_cluster_get_group_identifiers_response_command(cmd, &cmd_data)
      != EMBER_ZCL_STATUS_SUCCESS) {
    return false;
  }
  groupInformationRecordListLen = (emberAfCurrentCommand()->bufLen
                                   - (emberAfCurrentCommand()->payloadStartIndex
                                      + sizeof(cmd_data.total)
                                      + sizeof(cmd_data.startIndex)
                                      + sizeof(cmd_data.count)));
  groupInformationRecordListIndex = 0;

  emberAfZllCommissioningClusterPrint("RX: GetGroupIdentifiersResponse 0x%x, 0x%x, 0x%x,",
                                      cmd_data.total,
                                      cmd_data.startIndex,
                                      cmd_data.count);

  for (i = 0; i < cmd_data.count; i++) {
    uint16_t groupId;
    uint8_t groupType;
    groupId = emberAfGetInt16u(cmd_data.groupInformationRecordList, groupInformationRecordListIndex, groupInformationRecordListLen);
    groupInformationRecordListIndex += 2;
    groupType = emberAfGetInt8u(cmd_data.groupInformationRecordList, groupInformationRecordListIndex, groupInformationRecordListLen);
    groupInformationRecordListIndex++;
    emberAfZllCommissioningClusterPrint(" [0x%2x 0x%x]", groupId, groupType);
  }
  emberAfZllCommissioningClusterPrintln("");
#endif // SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT

  emberAfSendImmediateDefaultResponse(EMBER_ZCL_STATUS_SUCCESS);
  return true;
}

bool emberAfZllCommissioningClusterGetEndpointListResponseCallback(EmberAfClusterCommand *cmd)
{
  (void)cmd;

#ifdef SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
  sl_zcl_zll_commissioning_cluster_get_endpoint_list_response_command_t cmd_data;
  uint16_t endpointInformationRecordListLen;
  uint16_t endpointInformationRecordListIndex;
  uint8_t i;

  if (zcl_decode_zll_commissioning_cluster_get_endpoint_list_response_command(cmd, &cmd_data)
      != EMBER_ZCL_STATUS_SUCCESS) {
    return false;
  }

  endpointInformationRecordListLen = (emberAfCurrentCommand()->bufLen
                                      - (emberAfCurrentCommand()->payloadStartIndex
                                         + sizeof(cmd_data.total)
                                         + sizeof(cmd_data.startIndex)
                                         + sizeof(cmd_data.count)));
  endpointInformationRecordListIndex = 0;

  emberAfZllCommissioningClusterPrint("RX: GetEndpointListResponse 0x%x, 0x%x, 0x%x,",
                                      cmd_data.total,
                                      cmd_data.startIndex,
                                      cmd_data.count);

  for (i = 0; i < cmd_data.count; i++) {
    uint16_t networkAddress;
    uint8_t endpointId;
    uint16_t profileId;
    uint16_t deviceId;
    uint8_t version;
    networkAddress = emberAfGetInt16u(cmd_data.endpointInformationRecordList, endpointInformationRecordListIndex, endpointInformationRecordListLen);
    endpointInformationRecordListIndex += 2;
    endpointId = emberAfGetInt8u(cmd_data.endpointInformationRecordList, endpointInformationRecordListIndex, endpointInformationRecordListLen);
    endpointInformationRecordListIndex++;
    profileId = emberAfGetInt16u(cmd_data.endpointInformationRecordList, endpointInformationRecordListIndex, endpointInformationRecordListLen);
    endpointInformationRecordListIndex += 2;
    deviceId = emberAfGetInt16u(cmd_data.endpointInformationRecordList, endpointInformationRecordListIndex, endpointInformationRecordListLen);
    endpointInformationRecordListIndex += 2;
    version = emberAfGetInt8u(cmd_data.endpointInformationRecordList, endpointInformationRecordListIndex, endpointInformationRecordListLen);
    endpointInformationRecordListIndex++;
    emberAfZllCommissioningClusterPrint(" [0x%2x 0x%x 0x%2x 0x%2x 0x%x]",
                                        networkAddress,
                                        endpointId,
                                        profileId,
                                        deviceId,
                                        version);
  }

  emberAfZllCommissioningClusterPrintln("");
#endif // SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT

  emberAfSendDefaultResponse(emberAfCurrentCommand(), EMBER_ZCL_STATUS_SUCCESS);
  return true;
}

uint32_t emberAfZllCommissioningClusterClientCommandParse(sl_service_opcode_t opcode,
                                                          sl_service_function_context_t *context)
{
  (void)opcode;

  EmberAfClusterCommand *cmd = (EmberAfClusterCommand *)context->data;
  bool wasHandled = false;

  if (!cmd->mfgSpecific) {
    switch (cmd->commandId) {
      case ZCL_ENDPOINT_INFORMATION_COMMAND_ID:
      {
        wasHandled = emberAfZllCommissioningClusterEndpointInformationCallback(cmd);
        break;
      }
      case ZCL_GET_GROUP_IDENTIFIERS_RESPONSE_COMMAND_ID:
      {
        wasHandled = emberAfZllCommissioningClusterGetGroupIdentifiersResponseCallback(cmd);
        break;
      }
      case ZCL_GET_ENDPOINT_LIST_RESPONSE_COMMAND_ID:
      {
        wasHandled = emberAfZllCommissioningClusterGetEndpointListResponseCallback(cmd);
        break;
      }
    }
  }

  return ((wasHandled)
          ? EMBER_ZCL_STATUS_SUCCESS
          : EMBER_ZCL_STATUS_UNSUP_COMMAND);
}
