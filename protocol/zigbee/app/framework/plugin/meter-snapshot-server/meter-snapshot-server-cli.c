/***************************************************************************//**
 * @file
 * @brief CLI for the Meter Snapshot Server plugin.
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

#include "meter-snapshot-server.h"
#include "app/util/serial/sl_zigbee_command_interpreter.h"
// plugin meter-snapshot-server take
void sli_zigbee_af_meter_snapshot_server_cli_take(sl_cli_command_arg_t *arguments)
{
  uint8_t endpoint = sl_cli_get_argument_uint8(arguments, 0);
  uint32_t cause = sl_cli_get_argument_uint32(arguments, 1);
  uint8_t snapshotConfirmation;

  // Attempt to take the snapshot
  emberAfPluginMeterSnapshotServerTakeSnapshotCallback(endpoint,
                                                       cause,
                                                       &snapshotConfirmation);
}

// plugin meter-snapshot-server publish
void sli_zigbee_af_meter_snapshot_server_cli_publish(sl_cli_command_arg_t *arguments)
{
  EmberNodeId nodeId = (EmberNodeId)sl_cli_get_argument_uint16(arguments, 0);
  uint8_t srcEndpoint = sl_cli_get_argument_uint8(arguments, 1);
  uint8_t dstEndpoint = sl_cli_get_argument_uint8(arguments, 2);
  uint32_t startTime = sl_cli_get_argument_uint32(arguments, 3);
  uint32_t endTime = sl_cli_get_argument_uint32(arguments, 4);
  uint8_t offset = sl_cli_get_argument_uint8(arguments, 5);
  uint32_t cause = sl_cli_get_argument_uint32(arguments, 6);
  uint8_t snapshotCriteria[13];

  // Package the snapshot criteria for our callback to process
  emberAfCopyInt32u((uint8_t *)snapshotCriteria, 0, startTime);
  emberAfCopyInt32u((uint8_t *)snapshotCriteria, 4, endTime);
  snapshotCriteria[8] = offset;
  emberAfCopyInt32u((uint8_t *)snapshotCriteria, 9, cause);

  emberAfPluginMeterSnapshotServerGetSnapshotCallback(srcEndpoint,
                                                      dstEndpoint,
                                                      nodeId,
                                                      snapshotCriteria);
}
