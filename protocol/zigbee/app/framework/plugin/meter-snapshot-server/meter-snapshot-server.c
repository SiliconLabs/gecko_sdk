/***************************************************************************//**
 * @file
 * @brief Code to handle meter snapshot server behavior.
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
#include "meter-snapshot-server.h"

#include "zap-cluster-command-parser.h"

bool emberAfSimpleMeteringClusterScheduleSnapshotCallback(EmberAfClusterCommand *cmd)
{
  sl_zcl_simple_metering_cluster_schedule_snapshot_command_t cmd_data;

  if (zcl_decode_simple_metering_cluster_schedule_snapshot_command(cmd, &cmd_data)
      != EMBER_ZCL_STATUS_SUCCESS) {
    return false;
  }
  uint8_t responsePayload[2];

  // Attempt to schedule the snapshot
  emberAfPluginMeterSnapshotServerScheduleSnapshotCallback(cmd->apsFrame->destinationEndpoint,
                                                           cmd->apsFrame->sourceEndpoint,
                                                           cmd->source,
                                                           cmd_data.snapshotSchedulePayload,
                                                           (uint8_t *)responsePayload);

  emberAfFillCommandSimpleMeteringClusterScheduleSnapshotResponse(cmd_data.issuerEventId,
                                                                  responsePayload,
                                                                  2);

  emberAfSendResponse();
  return true;
}

bool emberAfSimpleMeteringClusterTakeSnapshotCallback(EmberAfClusterCommand *cmd)
{
  sl_zcl_simple_metering_cluster_take_snapshot_command_t cmd_data;
  if (zcl_decode_simple_metering_cluster_take_snapshot_command(cmd, &cmd_data)
      != EMBER_ZCL_STATUS_SUCCESS) {
    return false;
  }

  uint8_t endpoint = emberAfCurrentEndpoint();
  uint8_t snapshotConfirmation;
  uint32_t snapshotId;

  // Attempt to take the snapshot
  snapshotId = emberAfPluginMeterSnapshotServerTakeSnapshotCallback(endpoint,
                                                                    cmd_data.snapshotCause,
                                                                    &snapshotConfirmation);

  emberAfFillCommandSimpleMeteringClusterTakeSnapshotResponse(snapshotId,
                                                              snapshotConfirmation);
  emberAfSendResponse();
  return true;
}

bool emberAfSimpleMeteringClusterGetSnapshotCallback(EmberAfClusterCommand *cmd)
{
  sl_zcl_simple_metering_cluster_get_snapshot_command_t cmd_data;
  if (zcl_decode_simple_metering_cluster_get_snapshot_command(cmd, &cmd_data)
      != EMBER_ZCL_STATUS_SUCCESS) {
    return false;
  }

  uint8_t snapshotCriteria[13];

  // Package the snapshot criteria for our callback to process
  emberAfCopyInt32u((uint8_t *)snapshotCriteria, 0, cmd_data.earliestStartTime);
  emberAfCopyInt32u((uint8_t *)snapshotCriteria, 4, cmd_data.latestEndTime);
  snapshotCriteria[8] = cmd_data.snapshotOffset;
  emberAfCopyInt32u((uint8_t *)snapshotCriteria, 9, cmd_data.snapshotCause);
  emberAfCorePrintln("snapshotCause %u", cmd_data.snapshotCause);
  emberAfCorePrintln("snapshotCause %u", cmd_data.snapshotCause);

  emberAfCorePrintln("Start Time %u Endpoint %u snapshot Offset %u SnapShotCause %u", cmd_data.earliestStartTime, cmd_data.latestEndTime, cmd_data.snapshotOffset, cmd_data.snapshotCause);
  // Get / publish the snapshot
  emberAfPluginMeterSnapshotServerGetSnapshotCallback(cmd->apsFrame->destinationEndpoint,
                                                      cmd->apsFrame->sourceEndpoint,
                                                      cmd->source,
                                                      (uint8_t *)snapshotCriteria);

  return true;
}

uint32_t emberAfSimpleMeteringClusterServerSnapshotCommandParse(sl_service_opcode_t opcode,
                                                                sl_service_function_context_t *context)
{
  (void)opcode;

  EmberAfClusterCommand *cmd = (EmberAfClusterCommand *)context->data;
  bool wasHandled = false;

  if (!cmd->mfgSpecific) {
    switch (cmd->commandId) {
      case ZCL_TAKE_SNAPSHOT_COMMAND_ID:
        wasHandled = emberAfSimpleMeteringClusterTakeSnapshotCallback(cmd);
        break;
      case ZCL_GET_SNAPSHOT_COMMAND_ID:
        wasHandled = emberAfSimpleMeteringClusterGetSnapshotCallback(cmd);
        break;
      case ZCL_SCHEDULE_SNAPSHOT_COMMAND_ID:
        wasHandled = emberAfSimpleMeteringClusterScheduleSnapshotCallback(cmd);
        break;
      default:
        break;
    }
  }

  return ((wasHandled)
          ? EMBER_ZCL_STATUS_SUCCESS
          : EMBER_ZCL_STATUS_UNSUP_COMMAND);
}
