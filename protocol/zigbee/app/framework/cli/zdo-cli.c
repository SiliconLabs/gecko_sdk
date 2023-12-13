/***************************************************************************//**
 * @file
 * @brief CLI commands for sending ZDO messages.
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

// common include file
#include "app/framework/util/common.h"
#include "app/framework/util/af-main.h"

#include "app/framework/include/af.h"
#include "app/util/serial/sl_zigbee_command_interpreter.h"

#include "app/util/zigbee-framework/zigbee-device-common.h"

#if defined(EZSP_HOST)
  #include "app/util/zigbee-framework/zigbee-device-host.h"
#else // SOC
  #include "app/util/zigbee-framework/zigbee-device-library.h"
#endif

#include "app/framework/cli/option-cli.h"

EmberStatus matchDescriptorsRequest(EmberNodeId target,
                                    uint16_t profile,
                                    uint8_t inCount,
                                    uint8_t outCount,
                                    uint16_t *inClusters,
                                    uint16_t *outClusters,
                                    EmberApsOption options);

#define MAX_CLUSTERS_CAN_MATCH 5
uint16_t sli_zigbee_af_cli_zdo_in_clusters[MAX_CLUSTERS_CAN_MATCH];
uint16_t sli_zigbee_af_cli_zdo_out_clusters[MAX_CLUSTERS_CAN_MATCH];
uint8_t sli_zigbee_af_cli_in_cl_count = 0;
uint8_t sli_zigbee_af_cli_out_cl_count = 0;

//------------------------------------------------------------------------------

// *****************************************
// zdoCommand
//
// zdo nwk <eui64:big-endian>
// zdo ieee <node-id>
// zdo simple <dest> <target ep>
// zdo node <dest>
// zdo match  <dest> <profile>
// zdo bind   <dest> <local ep> <remote ep> <cluster> <THEIR eui> <dest eui>
// zdo in-cl-list add <cluster IDs>
// zdo in-cl-list clear
// zdo out-cl-list add <clusters IDs>
// zdo out-cl-list clear
// zdo nwk-upd chan  <channel>
// zdo nwk-upd set   <nwk mgr id>  <chan mask>
// zdo nwk-upd scan  <target> <duration> <count>
// zdo active <target>
// *****************************************

void zdoNwkAddressRequestCommand(sl_cli_command_arg_t *args)
{
  EmberEUI64 eui64;
  sl_zigbee_copy_eui64_arg(args, 0, eui64, true);
  emberAfFindNodeId(eui64,
                    sli_zigbee_af_cli_service_discovery_callback);
}

void zdoIeeeAddressRequestCommand(sl_cli_command_arg_t *args)
{
  EmberNodeId id = (EmberNodeId)sl_cli_get_argument_uint16(args, 0);
  emberAfFindIeeeAddress(id,
                         sli_zigbee_af_cli_service_discovery_callback);
}

void zdoSimpleCommand(sl_cli_command_arg_t *args)
{
  EmberNodeId target = (EmberNodeId)sl_cli_get_argument_uint16(args, 0);
  uint8_t targetEndpoint = sl_cli_get_argument_uint8(args, 1);
  EmberStatus status = emberSimpleDescriptorRequest(target,
                                                    targetEndpoint,
                                                    EMBER_AF_DEFAULT_APS_OPTIONS);
  sl_zigbee_app_debug_println("ZDO simple desc req %02x", status);
}

void zdoNodeCommand(sl_cli_command_arg_t *args)
{
  EmberNodeId target = (EmberNodeId)sl_cli_get_argument_uint16(args, 0);
  EmberStatus status = emberNodeDescriptorRequest(target,
                                                  EMBER_AF_DEFAULT_APS_OPTIONS);
  sl_zigbee_app_debug_println("ZDO node desc req %02x", status);
}

void zdoMatchCommand(sl_cli_command_arg_t *args)
{
  EmberNodeId target = sl_cli_get_argument_uint16(args, 0);
  uint16_t profile = sl_cli_get_argument_uint16(args, 1);
  EmberStatus status = matchDescriptorsRequest(target,
                                               profile,
                                               sli_zigbee_af_cli_in_cl_count,
                                               sli_zigbee_af_cli_out_cl_count,
                                               sli_zigbee_af_cli_zdo_in_clusters,
                                               sli_zigbee_af_cli_zdo_out_clusters,
                                               EMBER_AF_DEFAULT_APS_OPTIONS);
  sl_zigbee_app_debug_println("ZDO match desc req %x", status);
}

static EmberStatus copyOrLookupEui64(sl_cli_command_arg_t *args,
                                     uint8_t argumentNumber,
                                     EmberNodeId nodeId,
                                     EmberEUI64 returnEui64)
{
  EmberStatus status = EMBER_SUCCESS;
  if (0 == sl_zigbee_copy_eui64_arg(args, argumentNumber, returnEui64, true)) {
    status = emberLookupEui64ByNodeId(nodeId, returnEui64);
    if (status != EMBER_SUCCESS) {
      sl_zigbee_app_debug_println("Error:  EUI64 argument is empty and lookup by node ID failed.");
    }
  }
  return status;
}

// For simple bind requests, just put {} as the last argument
//   zdo bind <dest> <local ep> <remote ep> <cluster> <THEIR EUI> {}
//
// More complex requests, you can actually specify the dest EUI64 of,
// the binding, which is NOT the same as the EUI64 of the destination
// of the device receiving the binding.  This allows for a user
// to set multiple bindings on the destination for different devices.
//   zdo bind <dest> <local ep> <remote ep> <cluster> <THEIR EUI> <dest EUI64>
void zdoBindCommand(sl_cli_command_arg_t *args)
{
  EmberStatus status;
  EmberEUI64 sourceEui, destEui;  // names relative to binding sent over-the-air
  EmberNodeId target = (EmberNodeId)sl_cli_get_argument_uint16(args, 0);
  uint8_t sourceEndpoint = sl_cli_get_argument_uint8(args, 1);
  uint8_t destinationEndpoint = sl_cli_get_argument_uint8(args, 2);
  uint16_t clusterId = sl_cli_get_argument_uint16(args, 3);

  // NOTE:  The source/dest EUI is relative to the context.
  // In the case of the syntax of the CLI, we take "THEIR EUI64" to mean
  // the recipient of the binding request message.  However, when sending
  // the bind request that EUI64 used by the ZDO command is
  // actually the source for the binding because we are telling the remote
  // device (the destination) to create a binding with a source of itself.
  // And the destination for that binding will be this local device.
  // This is also not to be confused with the (short) destination of the ZDO
  // request itself.
  if (EMBER_SUCCESS != copyOrLookupEui64(args, 4, target, sourceEui)) {
    return;
  }

  // If the last argument is empty, assume an EUI64 of the local device.
  // This allows for the simple case.  If an EUI64 is specified, it will
  // be used instead of the local EUI.  This is used for setting
  // multiple bindings on the same remote device.
  if (0 == sl_zigbee_copy_eui64_arg(args, 5, destEui, true)) {
    sl_zigbee_app_debug_println("Using my local EUI64 for dest EUI64 in binding");
    emberAfGetEui64(destEui);
  }

  status = emberBindRequest(target,           // who gets the bind req
                            sourceEui,       // source eui IN the binding
                            sourceEndpoint,
                            clusterId,
                            UNICAST_BINDING, // binding type
                            destEui,         // destination eui IN the binding
                            0,               // groupId for new binding
                            destinationEndpoint,
                            EMBER_AF_DEFAULT_APS_OPTIONS);
  UNUSED_VAR(status);
  sl_zigbee_app_debug_println("ZDO bind req %02x", status);
}

void zdoAddClusterCommand(sl_cli_command_arg_t *args)
{
  uint16_t *clusters;
  uint8_t *clCount;

  if (memcmp(args->argv[args->arg_ofs - 2], "in", strlen("in")) == 0) {
    clusters = sli_zigbee_af_cli_zdo_in_clusters;
    clCount = &sli_zigbee_af_cli_in_cl_count;
  } else {
    clusters = sli_zigbee_af_cli_zdo_out_clusters;
    clCount = &sli_zigbee_af_cli_out_cl_count;
  }

  if (*clCount < MAX_CLUSTERS_CAN_MATCH) {
    clusters[*clCount] = sl_cli_get_argument_uint16(args, 0);
    (*clCount)++;
  } else {
    sl_zigbee_app_debug_println("cluster limit reached");
  }
}

void zdoClearClusterCommand(sl_cli_command_arg_t *args)
{
  if (memcmp(args->argv[args->arg_ofs - 2], "in", strlen("in")) == 0) {
    sli_zigbee_af_cli_in_cl_count = 0;
  } else {
    sli_zigbee_af_cli_out_cl_count = 0;
  }
}

void zdoNetworkUpdateChannelCommand(sl_cli_command_arg_t *args)
{
  uint8_t channel = sl_cli_get_argument_uint8(args, 0);
  uint8_t page = 0;
  EmberStatus status;

  if (sl_cli_get_argument_count(args) > 1) {
    page = sl_cli_get_argument_uint8(args, 1);
  } else {
    // page and channels are encoded in 8 bits as page 7..5 bits
    // channel 4...0 bits
    // 3rd and 4th bits are always 1's
    page = (uint8_t)(channel >> 5) | 0x18;
    channel = channel & 0x1F;
  }

  if (EMBER_SUCCESS != sli_zigbee_af_validate_channel_pages(page, channel)) {
    sl_zigbee_app_debug_println("invalid page: %d or channel: %d", page, channel);
  } else {
    if (page == EMBER_NO_CHANNEL_PAGE_IN_USE) {
      // Request for 2.4Ghz network if page is zero
      status = emberChannelChangeRequest(channel);
    } else {
      // 31..27 bits for page and 26..0 for channels
      uint32_t pageChannelBitMask = (page << 27 | BIT32(channel));
      status = emberEnergyScanRequest(EMBER_SLEEPY_BROADCAST_ADDRESS,
                                      pageChannelBitMask,
                                      0xFE,
                                      0);
    }
    sl_zigbee_app_debug_println("Change channel status: 0x%02x", status);
  }
}

void zdoNetworkUpdateScanCommand(sl_cli_command_arg_t *args)
{
  EmberNodeId target = (EmberNodeId)sl_cli_get_argument_uint16(args, 0);
  uint8_t scanDuration = sl_cli_get_argument_uint8(args, 1);
  uint16_t scanCount = sl_cli_get_argument_uint16(args, 2);
  uint32_t scanChannelsMask = EMBER_ALL_802_15_4_CHANNELS_MASK;
  if (scanDuration > 5 || scanCount == 0 || scanCount > 8) {
    sl_zigbee_app_debug_println("duration must be in range 0 - 5");
    sl_zigbee_app_debug_println("count must be in range 1 - 8");
  } else {
    if (sl_cli_get_argument_count(args) > 3) {
      scanChannelsMask = sl_cli_get_argument_uint32(args, 3);
    }

    EmberStatus status = emberEnergyScanRequest(target,
                                                scanChannelsMask,
                                                scanDuration,
                                                scanCount);
    emberAfAppPrint("scan status 0x%x", status);
  }
}

void zdoNetworkUpdateSetCommand(sl_cli_command_arg_t *args)
{
  EmberNodeId networkManager = (EmberNodeId)sl_cli_get_argument_uint16(args, 0);
  uint32_t activeChannels = sl_cli_get_argument_uint32(args, 1);
  EmberStatus status = emberSetNetworkManagerRequest(networkManager,
                                                     activeChannels);
  emberAfAppPrint("network update set status 0x%x", status);
}

void zdoActiveEpCommand(sl_cli_command_arg_t *args)
{
  EmberNodeId target = (EmberNodeId)sl_cli_get_argument_uint16(args, 0);
  EmberStatus status = emberActiveEndpointsRequest(target,
                                                   EMBER_APS_OPTION_RETRY);
  emberAfAppPrint("Active EP request status: 0x%X",
                  status);
}

void zdoMgmtLqiCommand(sl_cli_command_arg_t *args)
{
  EmberNodeId target = (EmberNodeId)sl_cli_get_argument_uint16(args, 0);
  uint8_t index = sl_cli_get_argument_uint8(args, 1);
  EmberStatus status = emberLqiTableRequest(target,
                                            index,
                                            EMBER_APS_OPTION_RETRY);
  emberAfAppPrint("LQI Table request: 0x%X", status);
}

void zdoMgmtBindCommand(sl_cli_command_arg_t *args)
{
  EmberNodeId target = (EmberNodeId)sl_cli_get_argument_uint16(args, 0);
  uint8_t index = sl_cli_get_argument_uint8(args, 1);
  EmberStatus status = emberBindingTableRequest(target,
                                                index,
                                                EMBER_APS_OPTION_RETRY);
  emberAfAppPrint("Binding Table request: 0x%X", status);
}

void zdoLeaveRequestCommand(sl_cli_command_arg_t *args)
{
  EmberNodeId target = (EmberNodeId)sl_cli_get_argument_uint16(args, 0);
  // CCB 2047
  // - CCB makes the first step to depracate the 'leave and remove children' functionality.
  // - We were proactive here and deprecated it right away.
  // bool removeChildren = (bool)emberUnsignedCommandArgument(1);
  bool rejoin = (bool)sl_cli_get_argument_uint8(args, 2);
  EmberEUI64 nullEui64 = { 0, 0, 0, 0, 0, 0, 0, 0 };
  EmberStatus status;

  uint8_t options = 0;
  if (rejoin) {
    options |= EMBER_ZIGBEE_LEAVE_AND_REJOIN;
  }

  status = emberLeaveRequest(target,
                             nullEui64,
                             options,
                             EMBER_APS_OPTION_RETRY);

  sl_zigbee_app_debug_println("Leave %p0x%X", "Request: ", status);
}

void zdoPowerDescriptorRequestCommand(sl_cli_command_arg_t *args)
{
  EmberNodeId target = (EmberNodeId)sl_cli_get_argument_uint16(args, 0);
  EmberStatus status = emberPowerDescriptorRequest(target,
                                                   EMBER_APS_OPTION_RETRY);
  sl_zigbee_app_debug_println("Power Descriptor %p0x%X", "Request: ", status);
}

static void unbindRequest(sl_cli_command_arg_t *args,
                          bool isGroupAddress,
                          void* destination,
                          uint8_t destinationEndpoint)
{
  EmberNodeId target = (EmberNodeId)sl_cli_get_argument_uint16(args, 0);
  uint8_t sourceEndpoint = sl_cli_get_argument_uint8(args, 2);
  EmberAfClusterId clusterId = (EmberAfClusterId)sl_cli_get_argument_uint16(args, 3);
  EmberEUI64 sourceEui64;
  EmberEUI64 destinationEui64;
  EmberStatus status;
  EmberNodeId groupAddress = EMBER_NULL_NODE_ID;

  if (EMBER_SUCCESS != copyOrLookupEui64(args, 1, target, sourceEui64)) {
    return;
  }

  if (isGroupAddress) {
    groupAddress = *((EmberNodeId*)destination);
  } else {
    groupAddress = 0;
    MEMMOVE(destinationEui64, destination, EUI64_SIZE);
  }

  status = emberUnbindRequest(target,
                              sourceEui64,
                              sourceEndpoint,
                              clusterId,
                              (isGroupAddress
                               ? MULTICAST_BINDING
                               : UNICAST_BINDING),
                              destinationEui64,
                              groupAddress,
                              destinationEndpoint,
                              EMBER_APS_OPTION_RETRY);
  UNUSED_VAR(status);
  sl_zigbee_app_debug_println("Unbind %p %p0x%X",
                              (isGroupAddress
                               ? "Group"
                               : "Unicast"),
                              "Request: ",
                              status);
}

void zdoUnbindGroupCommand(sl_cli_command_arg_t *args)
{
  EmberNodeId groupAddress = (EmberNodeId)sl_cli_get_argument_uint16(args, 4);
  unbindRequest(args, true,  // group addressed binding?
                &groupAddress,
                0);   // destination endpoint (unused)
}

void zdoUnbindUnicastCommand(sl_cli_command_arg_t *args)
{
  EmberEUI64 destinationEui64;
  uint8_t destinationEndpoint = sl_cli_get_argument_uint8(args, 5);

  // If the destination EUI64 of the binding (not the destination of the
  // actual message) is empty, use our local EUI64.
  if (0 == sl_zigbee_copy_eui64_arg(args, 4, destinationEui64, true)) {
    sl_zigbee_app_debug_println("Using my local EUI64 for dest EUI64 in unbinding");
    emberAfGetEui64(destinationEui64);
  }

  unbindRequest(args, false,   // group addressed binding?
                destinationEui64,
                destinationEndpoint);
}

void zdoRouteRequestCommand(sl_cli_command_arg_t *args)
{
  EmberNodeId target = (EmberNodeId)sl_cli_get_argument_uint16(args, 0);
  uint8_t index = sl_cli_get_argument_uint8(args, 1);
  EmberStatus status = emberRoutingTableRequest(target,
                                                index,
                                                EMBER_APS_OPTION_RETRY);
  sl_zigbee_app_debug_println("Route Table %p0x%X", "Request: ", status);
}

//------------------------------------------------------------------------------
// Platform specific code

#if defined(EZSP_HOST)
EmberStatus matchDescriptorsRequest(EmberNodeId target,
                                    uint16_t profile,
                                    uint8_t inCount,
                                    uint8_t outCount,
                                    uint16_t *inClusters,
                                    uint16_t *outClusters,
                                    EmberApsOption options)
{
  return ezspMatchDescriptorsRequest(target,
                                     profile,
                                     inCount,
                                     outCount,
                                     inClusters,
                                     outClusters,
                                     options);
}

#else

// Copy the list of uint16_t input and output cluster lists into
// message buffers.
EmberStatus matchDescriptorsRequest(EmberNodeId target,
                                    uint16_t profile,
                                    uint8_t inCount,
                                    uint8_t outCount,
                                    uint16_t *inClusters,
                                    uint16_t *outClusters,
                                    EmberApsOption options)
{
  uint8_t i;
  uint8_t output;
  EmberMessageBuffer inClusterBuffer = EMBER_NULL_MESSAGE_BUFFER;
  EmberMessageBuffer outClusterBuffer = EMBER_NULL_MESSAGE_BUFFER;
  EmberStatus status = EMBER_NO_BUFFERS;
  for (output = 0; output < 2; output++) {
    EmberMessageBuffer* bufferPtr;
    uint8_t count;
    uint16_t* list;
    if (output != 0U) {
      count = outCount;
      list = outClusters;
      bufferPtr = &outClusterBuffer;
    } else {  // input
      count = inCount;
      list = inClusters;
      bufferPtr = &inClusterBuffer;
    }
    if (count == 0) {
      continue;
    }

    *bufferPtr = emberAllocateStackBuffer();
    if (*bufferPtr == EMBER_NULL_MESSAGE_BUFFER) {
      goto cleanup;
    }

    for (i = 0; i < count; i++) {
      uint8_t cluster[2];
      cluster[0] = LOW_BYTE(list[i]);
      cluster[1] = HIGH_BYTE(list[i]);
      status = emberAppendToLinkedBuffers(*bufferPtr,
                                          cluster,
                                          2);
      if (EMBER_SUCCESS != status) {
        goto cleanup;
      }
    }
  }
  status = emberMatchDescriptorsRequest(target,
                                        profile,
                                        inClusterBuffer,
                                        outClusterBuffer,
                                        options);
  cleanup:
  if (inClusterBuffer != EMBER_NULL_MESSAGE_BUFFER) {
    emberReleaseMessageBuffer(inClusterBuffer);
  }
  if (outClusterBuffer != EMBER_NULL_MESSAGE_BUFFER) {
    emberReleaseMessageBuffer(outClusterBuffer);
  }
  return status;
}

#endif // !defined(EZSP_HOST)
