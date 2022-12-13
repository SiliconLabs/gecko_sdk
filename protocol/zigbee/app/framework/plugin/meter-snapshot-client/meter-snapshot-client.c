/***************************************************************************//**
 * @file
 * @brief Code to handle meter snapshot client behavior.
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
#include "app/framework/util/common.h"

#ifdef UC_BUILD
#include "zap-cluster-command-parser.h"
#endif

#ifndef fieldLength
  #define fieldLength(field) \
  (emberAfCurrentCommand()->bufLen - (field - emberAfCurrentCommand()->buffer))
#endif

#ifdef UC_BUILD
bool emberAfSimpleMeteringClusterScheduleSnapshotResponseCallback(EmberAfClusterCommand *cmd)
{
  sl_zcl_simple_metering_cluster_schedule_snapshot_response_command_t cmd_data;

  if (zcl_decode_simple_metering_cluster_schedule_snapshot_response_command(cmd, &cmd_data)
      != EMBER_ZCL_STATUS_SUCCESS) {
    return false;
  }

  emberAfSimpleMeteringClusterPrintln("RX: ScheduleSnapshotResponse 0x%4x",
                                      cmd_data.issuerEventId);

  // according to the documentation, the payload comprises of two uint8_t types
  emberAfSimpleMeteringClusterPrintln("    Payload: 0x%x, 0x%x",
                                      cmd_data.snapshotResponsePayload[0],
                                      cmd_data.snapshotResponsePayload[2]);

  emberAfSendImmediateDefaultResponse(EMBER_ZCL_STATUS_SUCCESS);
  return true;
}

bool emberAfSimpleMeteringClusterTakeSnapshotResponseCallback(EmberAfClusterCommand *cmd)
{
  sl_zcl_simple_metering_cluster_take_snapshot_response_command_t cmd_data;

  if (zcl_decode_simple_metering_cluster_take_snapshot_response_command(cmd, &cmd_data)
      != EMBER_ZCL_STATUS_SUCCESS) {
    return false;
  }
  emberAfSimpleMeteringClusterPrintln("RX: TakeSnapshotResponse 0x%4x, 0x%x",
                                      cmd_data.snapshotId,
                                      cmd_data.snapshotConfirmation);

  emberAfSendImmediateDefaultResponse(EMBER_ZCL_STATUS_SUCCESS);
  return true;
}

bool emberAfSimpleMeteringClusterPublishSnapshotCallback(EmberAfClusterCommand *cmd)
{
  sl_zcl_simple_metering_cluster_publish_snapshot_command_t cmd_data;

  if (zcl_decode_simple_metering_cluster_publish_snapshot_command(cmd, &cmd_data)
      != EMBER_ZCL_STATUS_SUCCESS) {
    return false;
  }
  uint8_t i;
  uint16_t snapshotPayloadLength = fieldLength(cmd_data.snapshotPayload);

  emberAfSimpleMeteringClusterPrintln("RX: PublishSnapshotResponse 0x%4x, 0x%4x, 0x%x, 0x%x, 0x%x, 0x%4x, 0x%x",
                                      cmd_data.snapshotId,
                                      cmd_data.snapshotTime,
                                      cmd_data.totalSnapshotsFound,
                                      cmd_data.commandIndex,
                                      cmd_data.totalCommands,
                                      cmd_data.snapshotCause,
                                      cmd_data.snapshotPayloadType);

  // Documentation only mentions payload type for debt/credit status, which comprises of 6 int32 types
  // so I am printing rows of four int8 values at a time, until the end of payload
  // Not passing proper payload structure may result in garbage print values
  if (cmd_data.snapshotPayloadType == EMBER_ZCL_PREPAY_SNAPSHOT_PAYLOAD_TYPE_DEBT_CREDIT_STATUS) {
    emberAfSimpleMeteringClusterPrintln("    Payload:");

    for (i = 0; i < snapshotPayloadLength; i += 4) {
      emberAfSimpleMeteringClusterPrintln("            0x%x 0x%x 0x%x 0x%x",
                                          cmd_data.snapshotPayload[i],
                                          cmd_data.snapshotPayload[i + 1],
                                          cmd_data.snapshotPayload[i + 2],
                                          cmd_data.snapshotPayload[i + 3]);
    }
  }

  emberAfSendImmediateDefaultResponse(EMBER_ZCL_STATUS_SUCCESS);
  return true;
}

EmberAfStatus emberAfSimpleMeteringClusterClientSnapshotCommandParse(sl_service_opcode_t opcode,
                                                                     sl_service_function_context_t *context)
{
  (void)opcode;

  EmberAfClusterCommand *cmd = (EmberAfClusterCommand *)context->data;
  bool wasHandled = false;

  if (!cmd->mfgSpecific) {
    switch (cmd->commandId) {
      case ZCL_SCHEDULE_SNAPSHOT_RESPONSE_COMMAND_ID:
        wasHandled = emberAfSimpleMeteringClusterScheduleSnapshotResponseCallback(cmd);
        break;
      case ZCL_TAKE_SNAPSHOT_RESPONSE_COMMAND_ID:
        wasHandled = emberAfSimpleMeteringClusterTakeSnapshotResponseCallback(cmd);
        break;
      case ZCL_PUBLISH_SNAPSHOT_COMMAND_ID:
        wasHandled = emberAfSimpleMeteringClusterPublishSnapshotCallback(cmd);
        break;
      default:
        break;
    }
  }
  return ((wasHandled)
          ? EMBER_ZCL_STATUS_SUCCESS
          : EMBER_ZCL_STATUS_UNSUP_COMMAND);
}
#else // !UC_BUILD
bool emberAfSimpleMeteringClusterScheduleSnapshotResponseCallback(uint32_t issuerEventId,
                                                                  uint8_t* snapshotResponsePayload)
{
  emberAfSimpleMeteringClusterPrintln("RX: ScheduleSnapshotResponse 0x%4x",
                                      issuerEventId);

  // according to the documentation, the payload comprises of two uint8_t types
  emberAfSimpleMeteringClusterPrintln("    Payload: 0x%x, 0x%x",
                                      snapshotResponsePayload[0],
                                      snapshotResponsePayload[2]);

  emberAfSendImmediateDefaultResponse(EMBER_ZCL_STATUS_SUCCESS);
  return true;
}

bool emberAfSimpleMeteringClusterTakeSnapshotResponseCallback(uint32_t snapshotId,
                                                              uint8_t snapshotConfirmation)
{
  emberAfSimpleMeteringClusterPrintln("RX: TakeSnapshotResponse 0x%4x, 0x%x",
                                      snapshotId,
                                      snapshotConfirmation);

  emberAfSendImmediateDefaultResponse(EMBER_ZCL_STATUS_SUCCESS);
  return true;
}

bool emberAfSimpleMeteringClusterPublishSnapshotCallback(uint32_t snapshotId,
                                                         uint32_t snapshotTime,
                                                         uint8_t totalSnapshotsFound,
                                                         uint8_t commandIndex,
                                                         uint8_t totalCommands,
                                                         uint32_t snapshotCause,
                                                         uint8_t snapshotPayloadType,
                                                         uint8_t* snapshotPayload)
{
  uint8_t i;
  uint16_t snapshotPayloadLength = fieldLength(snapshotPayload);

  emberAfSimpleMeteringClusterPrintln("RX: PublishSnapshotResponse 0x%4x, 0x%4x, 0x%x, 0x%x, 0x%x, 0x%4x, 0x%x",
                                      snapshotId,
                                      snapshotTime,
                                      totalSnapshotsFound,
                                      commandIndex,
                                      totalCommands,
                                      snapshotCause,
                                      snapshotPayloadType);

  // Documentation only mentions payload type for debt/credit status, which comprises of 6 int32 types
  // so I am printing rows of four int8 values at a time, until the end of payload
  // Not passing proper payload structure may result in garbage print values
  if (snapshotPayloadType == EMBER_ZCL_PREPAY_SNAPSHOT_PAYLOAD_TYPE_DEBT_CREDIT_STATUS) {
    emberAfSimpleMeteringClusterPrintln("    Payload:");

    for (i = 0; i < snapshotPayloadLength; i += 4) {
      emberAfSimpleMeteringClusterPrintln("            0x%x 0x%x 0x%x 0x%x",
                                          snapshotPayload[i],
                                          snapshotPayload[i + 1],
                                          snapshotPayload[i + 2],
                                          snapshotPayload[i + 3]);
    }
  }

  emberAfSendImmediateDefaultResponse(EMBER_ZCL_STATUS_SUCCESS);
  return true;
}
#endif // !UC_BUILD
