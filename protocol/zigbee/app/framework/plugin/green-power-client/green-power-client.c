/***************************************************************************//**
 * @file
 * @brief Routines for the Green Power Client plugin.
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
#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif
#ifdef SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
#include "app/framework/include/af.h"
#include "app/framework/util/af-main.h"
#include "app/framework/util/common.h"
#include "zap-cluster-command-parser.h"
#else // !SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
#include "green-power-adapter.h"
#endif //SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT

#include "green-power-client.h"
#include "stack/include/gp-types.h"
#include "stack/gp/gp-proxy-table.h"
#include "app/framework/plugin/green-power-common/green-power-common.h"

#ifdef EZSP_HOST
  #define emberGpepIncomingMessageHandler ezspGpepIncomingMessageHandler
  #define emberDGpSentHandler ezspDGpSentHandler
#endif

#define MIN_RESERVED_GPD_COMMAND_ID 0xE4
#define MAX_RESERVED_GPD_COMMAND_ID 0xEF
#define EMBER_ZCL_GP_GPDF_RESERVED_MIN 0xF7
#define EMBER_ZCL_GP_GPDF_RESERVED_MAX  0xFF

#define GP_PROXY_TABLE_RESPONSE_ENTRIES_OFFSET 3
#define GP_NON_MANUFACTURER_ZCL_HEADER_LENGTH 3

// Channel event timeout is 5 seconds
#define GP_CHANNEL_EVENT_TIMEOUT_IN_MSEC  (5 * MILLISECOND_TICKS_PER_SECOND)

#define isNodeIdValid(nodeId) ((nodeId) < EMBER_DISCOVERY_ACTIVE_NODE_ID)

#ifdef EZSP_HOST
#define sli_zigbee_af_set_add_delay(delay) (void)0
#else
void sli_zigbee_af_set_add_delay(uint16_t delay);
#endif // EZSP_HOST

static EmberAfGreenPowerClientCommissioningState commissioningState;
static EmberAfGreenPowerDuplicateFilter duplicateFilter;

static sl_zigbee_event_t exitCommissioningEvent;
static sl_zigbee_event_t channelEvent;
void channelEventHandler(sl_zigbee_event_t * event);
void exitCommissioningEventHandler(sl_zigbee_event_t * event);
#if (EMBER_AF_PLUGIN_GREEN_POWER_CLIENT_ENABLE_BIDIRECTIONAL_OPERATION == 1)
#define ENABLE_BIDIRECTIONAL_OPERATION
#endif

static void flushGpTxQueue(void)
{
  EmberGpAddress addr;
  // Use 0xFFFFFFFF wildcard to clear out the gpTxQueue
  addr.applicationId = EMBER_GP_APPLICATION_SOURCE_ID;
  addr.id.sourceId = GP_GPD_SRC_ID_WILDCARD;
  emberDGpSend(false, false, &addr, 0, 0, NULL, 0, 0);
}

static void sendChannelConfigToGpStub(void)
{
  uint8_t payload = (emberAfGetRadioChannel() - 11) // The channel is coded as : Operational Channel - 11
                    | 0x10; //basic
  EmberGpAddress addr;
  addr.id.sourceId = GP_GPD_SRC_ID_FOR_CAHNNEL_CONFIG;
  addr.applicationId = EMBER_GP_APPLICATION_SOURCE_ID;
  emberDGpSend(true, //add
               false,//no CCA
               &addr,
               EMBER_ZCL_GP_GPDF_CHANNEL_CONFIGURATION,
               sizeof(payload), //length
               &(payload),
               0, //gpepHandle
               0); //entryLifetimeMs
}

void emberAfPluginGreenPowerClientInitCallback(uint8_t init_level)
{
  switch (init_level) {
    case SL_ZIGBEE_INIT_LEVEL_EVENT:
    {
      sl_zigbee_event_init(&exitCommissioningEvent,
                           exitCommissioningEventHandler);
      sl_zigbee_event_init(&channelEvent,
                           channelEventHandler);
      break;
    }

    case SL_ZIGBEE_INIT_LEVEL_LOCAL_DATA:
    {
      MEMSET(&commissioningState,
             0x00,
             sizeof(EmberAfGreenPowerClientCommissioningState));
      MEMSET(&duplicateFilter, 0x00, sizeof(EmberAfGreenPowerDuplicateFilter));
      commissioningState.gppCommissioningWindow = EMBER_AF_PLUGIN_GREEN_POWER_CLIENT_GPP_COMMISSIONING_WINDOW;
      break;
    }

    case SL_ZIGBEE_INIT_LEVEL_DONE:
    {
      // Write the max proxy table entries attribute, since we currently have no
      // way to configure it at compile time.
      uint8_t proxyTableSize = EMBER_GP_PROXY_TABLE_SIZE;
      EmberAfStatus UNUSED status
        = emberAfWriteClientAttribute(EMBER_GP_ENDPOINT,
                                      ZCL_GREEN_POWER_CLUSTER_ID,
                                      ZCL_GP_CLIENT_GPP_MAX_PROXY_TABLE_ENTRIES_ATTRIBUTE_ID,
                                      &proxyTableSize,
                                      ZCL_INT8U_ATTRIBUTE_TYPE);
      break;
    }
  }
}

static void exitCommissioningMode(void)
{
  commissioningState.inCommissioningMode = false;
  emberAfGreenPowerClusterPrintln("Exit comm for sink %2x", commissioningState.commissioningSink);

  flushGpTxQueue();
}

void channelEventHandler(sl_zigbee_event_t * event)
{
  if (commissioningState.channelStatus & GP_CLIENT_ON_TRANSMIT_CHANNEL_MASK) {
    if (commissioningState.channelStatus & GP_CLIENT_ADDITIONAL_CHANNEL_REQUEST_PENDING) {
      commissioningState.channelStatus &= ~GP_CLIENT_ADDITIONAL_CHANNEL_REQUEST_PENDING;
      sendChannelConfigToGpStub();
      return;
    }
    emberAfGreenPowerClusterPrintln("return to chan %d", emberAfGetRadioChannel());
    emberStopScan();
    commissioningState.channelStatus = 0;
    flushGpTxQueue();
  }

  sl_zigbee_event_set_inactive(&channelEvent);
}

void exitCommissioningEventHandler(sl_zigbee_event_t * event)
{
  exitCommissioningMode();

  sl_zigbee_event_set_inactive(&exitCommissioningEvent);
}

static uint16_t storeProxyTableEntry(EmberGpProxyTableEntry *entry,
                                     uint8_t *buffer)
{
  uint8_t *finger = buffer;
  //uint8_t securityLevel = entry->securityOptions & EMBER_AF_GP_PROXY_TABLE_ENTRY_SECURITY_OPTIONS_SECURITY_LEVEL;
  //uint8_t securityKeyType = entry->securityOptions & EMBER_AF_GP_PROXY_TABLE_ENTRY_SECURITY_OPTIONS_SECURITY_KEY_TYPE;

  emberAfCopyInt16u(finger, 0, (uint16_t)(entry->options & 0xFFFF));
  finger += sizeof(uint16_t);
  if (entry->gpd.applicationId == EMBER_GP_APPLICATION_SOURCE_ID) {
    emberAfCopyInt32u(finger, 0, entry->gpd.id.sourceId);
    finger += sizeof(uint32_t);
  } else if (entry->gpd.applicationId == EMBER_GP_APPLICATION_IEEE_ADDRESS) {
    MEMMOVE(finger, entry->gpd.id.gpdIeeeAddress, EUI64_SIZE);
    finger += EUI64_SIZE;
  }

  if (entry->gpd.applicationId == EMBER_GP_APPLICATION_IEEE_ADDRESS) {
    emberAfCopyInt8u(finger, 0, entry->gpd.endpoint);
    finger += sizeof(uint8_t);
  }

  if (entry->options & EMBER_AF_GP_PROXY_TABLE_ENTRY_OPTIONS_ASSIGNED_ALIAS) {
    emberAfCopyInt16u(finger, 0, entry->assignedAlias);
    finger += sizeof(uint16_t);
  }

  if (entry->options & EMBER_AF_GP_PROXY_TABLE_ENTRY_OPTIONS_SECURITY_USE) {
    emberAfCopyInt8u(finger, 0, entry->securityOptions);
    finger += sizeof(uint8_t);
    emberAfCopyInt32u(finger, 0, entry->gpdSecurityFrameCounter);
    finger += sizeof(uint32_t);
    MEMMOVE(finger, entry->gpdKey.contents, EMBER_ENCRYPTION_KEY_SIZE);
    finger += EMBER_ENCRYPTION_KEY_SIZE;
  } else if (entry->options & EMBER_AF_GP_PROXY_TABLE_ENTRY_OPTIONS_SEQUENCE_NUMBER_CAP) {
    emberAfCopyInt32u(finger, 0, entry->gpdSecurityFrameCounter);
    finger += sizeof(uint32_t);
  }

  // Lightweight sink address list
  if (entry->options & EMBER_AF_GP_PROXY_TABLE_ENTRY_OPTIONS_LIGHTWEIGHT_UNICAST_GPS) {
    // let's count
    uint8_t index = 0;
    uint8_t *entryCount = finger;
    emberAfCopyInt8u(finger, 0, 0x00);
    finger += sizeof(uint8_t);
    for (index = 0; index < GP_SINK_LIST_ENTRIES; index++) {
      EmberGpSinkListEntry * sinkEntry = &entry->sinkList[index];

      if (sinkEntry->type == EMBER_GP_SINK_TYPE_LW_UNICAST) {
        MEMMOVE(finger, sinkEntry->target.unicast.sinkEUI, EUI64_SIZE);
        finger += EUI64_SIZE;
        emberAfCopyInt16u(finger, 0, sinkEntry->target.unicast.sinkNodeId);
        finger += sizeof(uint16_t);
        (*entryCount)++;
      } else {
        continue;
      }
    }
  }

  // Sink group list
  if (entry->options & EMBER_AF_GP_PROXY_TABLE_ENTRY_OPTIONS_COMMISIONED_GROUP_GPS) {
    // let's count
    uint8_t index = 0;
    uint8_t *entryCount = finger;
    emberAfCopyInt8u(finger, 0, 0x00);
    finger += sizeof(uint8_t);
    for (index = 0; index < GP_SINK_LIST_ENTRIES; index++) {
      EmberGpSinkListEntry * sinkEntry = &entry->sinkList[index];

      if (sinkEntry->type == EMBER_GP_SINK_TYPE_GROUPCAST) {
        emberAfCopyInt16u(finger, 0, sinkEntry->target.groupcast.groupID);
        finger += sizeof(uint16_t);
        emberAfCopyInt16u(finger, 0, sinkEntry->target.groupcast.alias);
        finger += sizeof(uint16_t);
        (*entryCount)++;
      } else {
        continue;
      }
    }
  }

  emberAfCopyInt8u(finger, 0, entry->groupcastRadius);
  finger += sizeof(uint8_t);

  if ((entry->options & EMBER_AF_GP_PROXY_TABLE_ENTRY_OPTIONS_ENTRY_ACTIVE) == 0
      || (entry->options & EMBER_AF_GP_PROXY_TABLE_ENTRY_OPTIONS_ENTRY_VALID) == 0) {
    emberAfCopyInt8u(finger, 0, entry->searchCounter);
    finger += sizeof(uint8_t);
  }

  if (entry->options & EMBER_AF_GP_PROXY_TABLE_ENTRY_OPTIONS_EXTENSION) {
    emberAfCopyInt16u(finger, 0, (entry->options >> 16) & 0xFFFF);
    finger += sizeof(uint16_t);
  }

  // full unicast sink address list
  if (entry->options & EMBER_AF_GP_PROXY_TABLE_ENTRY_OPTIONS_FULL_UNICAST_GPS) {
    // let's count
    uint8_t index = 0;
    uint8_t *len = finger;
    emberAfCopyInt8u(finger, 0, 0); // Add zero length
    finger += sizeof(uint8_t);
    for (index = 0; index < GP_SINK_LIST_ENTRIES; index++) {
      EmberGpSinkListEntry * sinkEntry = &entry->sinkList[index];

      if (sinkEntry->type == EMBER_GP_SINK_TYPE_LW_UNICAST) {
        MEMMOVE(finger, sinkEntry->target.unicast.sinkEUI, EUI64_SIZE);
        finger += EUI64_SIZE;
        emberAfCopyInt16u(finger, 0, sinkEntry->target.unicast.sinkNodeId);
        finger += sizeof(uint16_t);
        *len += EUI64_SIZE + sizeof(uint16_t);
      } else {
        continue;
      }
    }
  }

  return (uint16_t)(finger - buffer);
}

//---------------------------
// Command callbacks

bool sli_zigbee_af_green_power_client_gp_proxy_commissioning_mode_command_handler(uint8_t options,
                                                                                  uint16_t commissioningWindow,
                                                                                  uint8_t channel,
                                                                                  bool localCommandLoopback)
{
  bool enterCommissioningMode = (options
                                 & EMBER_AF_GP_PROXY_COMMISSIONING_MODE_OPTION_ACTION);
  // The exitMode enumeration type is mapped as [b3b2b1] = [b3b2] | [b1] of `options` fields in the Gp Proxy Commissioning Mode
  // command where (b3-b2) for `ExitMode` fields and b1 is the exit on commissioning window time expiry.
  uint8_t exitMode = (options                                                                         \
                      & (EMBER_AF_GP_PROXY_COMMISSIONING_MODE_OPTION_EXIT_MODE                        \
                         | EMBER_AF_GP_PROXY_COMMISSIONING_MODE_OPTION_COMMISSIONING_WINDOW_PRESENT)) \
                     >> 1;

  bool chanPresent = (options
                      & EMBER_AF_GP_PROXY_COMMISSIONING_MODE_OPTION_CHANNEL_PRESENT); // should always be 0
  bool unicastCommunication = (options
                               & EMBER_AF_GP_PROXY_COMMISSIONING_MODE_OPTION_UNICAST_COMMUNICATION);

  if (!localCommandLoopback && emberAfCurrentEndpoint() != EMBER_GP_ENDPOINT) {
  } else if (!localCommandLoopback
             && commissioningState.inCommissioningMode
             && (emberGetSender() != commissioningState.commissioningSink)) {
    // check if current message sender is same as sender that put us in
    // commissioning mode.
    // if not, drop message silently.
  } else if (enterCommissioningMode) {
    commissioningState.commissioningSink = (localCommandLoopback ? emberGetNodeId() : emberGetSender());
    commissioningState.inCommissioningMode = true;
    commissioningState.gppCommissioningWindow = EMBER_AF_PLUGIN_GREEN_POWER_CLIENT_GPP_COMMISSIONING_WINDOW;
    commissioningState.exitMode = (EmberAfGreenPowerClientCommissioningExitMode) exitMode;
    commissioningState.unicastCommunication = unicastCommunication;
    emberAfGreenPowerClusterPrintln("Enter comm for sink %2x", commissioningState.commissioningSink);
    if (commissioningState.exitMode & EMBER_AF_GPC_COMMISSIONING_EXIT_ON_COMMISSIONING_WINDOW_EXP) {
      // store the new commissioning window value and update our local default
      // one.
      sl_zigbee_event_set_delay_ms(&exitCommissioningEvent,
                                   (commissioningWindow * MILLISECOND_TICKS_PER_SECOND));
    } else {
      sl_zigbee_event_set_delay_ms(&exitCommissioningEvent,
                                   (EMBER_AF_PLUGIN_GREEN_POWER_CLIENT_GPP_COMMISSIONING_WINDOW * MILLISECOND_TICKS_PER_SECOND));
    }
    if (chanPresent) {
      commissioningState.channel = channel;
      // TODO: goto channel
    } else {
      // TODO: goto operational channel
    }
  } else {
    // exit commissioning mode.
    exitCommissioningMode();
  }
  return true;
}

/*
 * Disable default response bit should be set per GP Spec 14-0563-08
 */
bool emberAfGreenPowerClusterGpProxyCommissioningModeCallback(EmberAfClusterCommand *cmd)
{
  sl_zcl_green_power_cluster_gp_proxy_commissioning_mode_command_t cmd_data;

  if (zcl_decode_green_power_cluster_gp_proxy_commissioning_mode_command(cmd, &cmd_data)
      != EMBER_ZCL_STATUS_SUCCESS) {
    return false;
  }

  return sli_zigbee_af_green_power_client_gp_proxy_commissioning_mode_command_handler(cmd_data.options,
                                                                                      cmd_data.commissioningWindow,
                                                                                      cmd_data.channel,
                                                                                      false);
}

/*
 * Disable default response should be enabled in the sending message.
 */
bool emberAfGreenPowerClusterGpPairingCallback(EmberAfClusterCommand *cmd)
{
  sl_zcl_green_power_cluster_gp_pairing_command_t cmd_data;
  uint8_t securityLevel;
  uint8_t commMode;
  uint8_t securityKeyType;
  EmberGpAddress addr;
  bool createdPairing = false;
  bool broadcast = false;

  if (zcl_decode_green_power_cluster_gp_pairing_command(cmd, &cmd_data)
      != EMBER_ZCL_STATUS_SUCCESS) {
    return false;
  }

  securityLevel = ((cmd_data.options & EMBER_AF_GP_PAIRING_OPTION_SECURITY_LEVEL)
                   >> EMBER_AF_GP_PAIRING_OPTION_SECURITY_LEVEL_OFFSET);
  commMode = ((cmd_data.options & EMBER_AF_GP_PAIRING_OPTION_COMMUNICATION_MODE)
              >> EMBER_AF_GP_PAIRING_OPTION_COMMUNICATION_MODE_OFFSET);
  securityKeyType = ((cmd_data.options & EMBER_AF_GP_PAIRING_OPTION_SECURITY_KEY_TYPE)
                     >> EMBER_AF_GP_PAIRING_OPTION_SECURITY_KEY_TYPE_OFFSET);

  // If "option & addSinkBit(3) == 1" AND "groupcastRadiusBit(17)==0"
  // then groupcastRadius = 0 not 0xFF that was passed by call-command-handler
  if ((cmd_data.options & EMBER_AF_GP_PAIRING_OPTION_ADD_SINK)
      && !(cmd_data.options & EMBER_AF_GP_PAIRING_OPTION_GROUPCAST_RADIUS_PRESENT)) {
    cmd_data.groupcastRadius = 0;
  }

  if (cmd->type == EMBER_INCOMING_BROADCAST) {
    broadcast = true;
  }
  EmberGpApplicationId appId = (cmd_data.options & EMBER_AF_GP_PAIRING_OPTION_APPLICATION_ID);
  if (!sli_zigbee_af_gp_make_addr(&addr,
                                  appId,
                                  cmd_data.gpdSrcId,
                                  cmd_data.gpdIeee,
                                  cmd_data.endpoint)
      || IS_GPD_SRC_ID_ZERO(appId, cmd_data.gpdSrcId)) {
    // GPD Address or App Id are invalid, so drop the command
    return true;
  }

  emberAfCorePrint("GP Pairing\n");

  // Commissioning: Step 21a: Proxy finalizes commissioning
  if (emberAfCurrentEndpoint() != EMBER_GP_ENDPOINT) {
  } else if (securityLevel == EMBER_GP_SECURITY_LEVEL_RESERVED) {
  } else if ((cmd_data.options & EMBER_AF_GP_PAIRING_OPTION_ADD_SINK)
             && (cmd_data.options & EMBER_AF_GP_PAIRING_OPTION_REMOVE_GPD)) {
  } else if ((securityKeyType > EMBER_GP_SECURITY_KEY_GPD_OOB)
             &&  (securityKeyType < EMBER_GP_SECURITY_KEY_GPD_DERIVED)) {
  } else if ((commMode == EMBER_ZCL_GP_PAIRING_OPTIONS_COMMUNICATION_MODE_FULL_UNICAST_FORWARDING)
             && (!(cmd_data.options & EMBER_AF_GP_PAIRING_OPTION_REMOVE_GPD))) {
    // CCB #2278 -In case of unicast GP Pairing, the proxy SHALL respond with ZCL Default
    //  Response with relevant error code: INVALID_FIELD for Full unicast;
    //  -In case of broadcast GP Pairing, the proxy SHALL silently drop the frame.
    //  If RemoveGPD options bit is set the comms mode is not valid so ignore this test
    if (broadcast == true) {
      // Silently drop it as its a broadcast
    } else {
      //send default response for unicast pairing
      emberAfSendImmediateDefaultResponse(EMBER_ZCL_STATUS_INVALID_FIELD);
    }
  } else {
    // Step b:

    emberAfGreenPowerClusterPrintln("GP Pairing SRCID = %4x, Opt= %u Sink = %2x", addr.id.sourceId, cmd_data.options, cmd_data.sinkNwkAddress);

    createdPairing = emberGpProxyTableProcessGpPairing(cmd_data.options,
                                                       &addr,
                                                       commMode,
                                                       cmd_data.sinkNwkAddress,
                                                       cmd_data.sinkGroupId,
                                                       cmd_data.assignedAlias,
                                                       cmd_data.sinkIeeeAddress,
                                                       (EmberKeyData *) cmd_data.gpdKey,
                                                       cmd_data.gpdSecurityFrameCounter,
                                                       cmd_data.groupcastRadius);

    // step c: optionally, exit commissioning mode
    if (createdPairing
        && (commissioningState.exitMode & EMBER_AF_GPC_COMMISSIONING_EXIT_ON_FIRST_PAIRING_SUCCESS)) {
      exitCommissioningMode();
    } else if ((cmd_data.options & EMBER_AF_GP_PAIRING_OPTION_ADD_SINK) && !createdPairing) {
#ifndef EZSP_HOST
      uint8_t index = sli_zigbee_af_gp_proxy_table_get_free_entry_index();  //sli_zigbee_af_gp_proxy_table_find_or_allocate_entry(&addr);   //checking if pairing failed because of no
      // space
      if (index == 0xFF) {
        emberAfGreenPowerClusterPrintln("ERR PROXY TABLE FULL");
        if (broadcast != true) {
          // CCB # 2279 - only send default response if not broadcast - broadcasts are dropped
          emberAfSendImmediateDefaultResponse(EMBER_ZCL_STATUS_INSUFFICIENT_SPACE);
        }
      }
    }
#else
      // Checking if the proxy table is full is more of a pain on Host
      // We have to search through the whole table.
      // Because of this, we only do it for the non-broadcast case
      // Next time we bump the EZSP version, we should change the
      // return of Process GP Pairing to a status instead of a bool
      if (!broadcast) {
        EmberGpProxyTableEntry entry;
        for (uint8_t entryIndex = 0; entryIndex < EMBER_GP_PROXY_TABLE_SIZE; entryIndex++) {
          emberGpProxyTableGetEntry(entryIndex, &entry);
          if (entry.status == EMBER_GP_PROXY_TABLE_ENTRY_STATUS_UNUSED) {
            return true; // We have an unused entry so we don't need to send a DR for full
          }
        }
        emberAfGreenPowerClusterPrintln("ERR PROXY TABLE FULL");
        emberAfSendImmediateDefaultResponse(EMBER_ZCL_STATUS_INSUFFICIENT_SPACE);
      }
    }
#endif
  }
  return true;
}

bool emberAfGreenPowerClusterGpResponseCallback(EmberAfClusterCommand *cmd)
{
  sl_zcl_green_power_cluster_gp_response_command_t cmd_data;

  if (zcl_decode_green_power_cluster_gp_response_command(cmd, &cmd_data)
      != EMBER_ZCL_STATUS_SUCCESS) {
    return false;
  }

  if (emberAfCurrentEndpoint() != EMBER_GP_ENDPOINT) {
    goto kickout;
  }
  emberAfGreenPowerClusterPrintln("GpResponse cmd: %1x", cmd_data.gpdCommandId);

  EmberGpApplicationId appId = (cmd_data.options & EMBER_AF_GP_RESPONSE_OPTION_APPLICATION_ID);
  EmberGpAddress addr;
  if (!sli_zigbee_af_gp_make_addr(&addr,
                                  appId,
                                  cmd_data.gpdSrcId,
                                  cmd_data.gpdIeee,
                                  cmd_data.endpoint)
      || (IS_GPD_SRC_ID_ZERO(appId, cmd_data.gpdSrcId)
          && cmd_data.gpdCommandId != EMBER_ZCL_GP_GPDF_CHANNEL_CONFIGURATION)
      || (!IS_GPD_SRC_ID_ZERO(appId, cmd_data.gpdSrcId)
          && cmd_data.gpdCommandId == EMBER_ZCL_GP_GPDF_CHANNEL_CONFIGURATION)) {
    // GPD Address or App Id are invalid and
    // SrcId is only 0 for Channel configuration, else drop
    return true;
  }
  EmberStatus result;
  switch (cmd_data.gpdCommandId) {
    case EMBER_ZCL_GP_GPDF_CHANNEL_CONFIGURATION:
    {
      if (cmd_data.tempMasterShortAddress == emberGetNodeId()) {
        if (!sl_zigbee_event_is_scheduled(&channelEvent)
            || (commissioningState.channelStatus & GP_CLIENT_TRANSMIT_SAME_AS_OPERATIONAL_CHANNEL_MASK)) {
          sendChannelConfigToGpStub();
          commissioningState.channelStatus |= GP_CLIENT_ON_TRANSMIT_CHANNEL_MASK;
          // based on figure 88 of GP proxy basic spec V1.0 page 191
          // the following condition seems neccessary
          if (emberAfGetRadioChannel() != (cmd_data.tempMasterTxChannel + 11) ) {
            emberAfGreenPowerClusterPrintln("GP switch to chan %d", cmd_data.tempMasterTxChannel + 11);
            emberStartScan(EMBER_STACK_GP_CHANNEL_DELIVERY_SCAN, (1 << (cmd_data.tempMasterTxChannel + 11)), 0 /*duration*/);
            commissioningState.channelStatus &= ~GP_CLIENT_TRANSMIT_SAME_AS_OPERATIONAL_CHANNEL_MASK;
          } else {
            if (commissioningState.channelStatus & GP_CLIENT_TRANSMIT_SAME_AS_OPERATIONAL_CHANNEL_MASK) {
              commissioningState.channelStatus |= GP_CLIENT_ADDITIONAL_CHANNEL_REQUEST_PENDING;
            }
            commissioningState.channelStatus |= GP_CLIENT_TRANSMIT_SAME_AS_OPERATIONAL_CHANNEL_MASK;
          }
          // Stared timeout to clear the Tx Queue if the packet is not delivered,

          sl_zigbee_event_set_delay_ms(&channelEvent,
                                       GP_CHANNEL_EVENT_TIMEOUT_IN_MSEC);
          return true;
        } else {
          return false;
        }
      } else {
        //TODO clear firstToForward
        channelEventHandler(&channelEvent);
        //emberDGpSend(false, false, &addr, 0, 0, NULL, 0, 0);
      }
      break;
    }
    case EMBER_ZCL_GP_GPDF_COMMISSIONING_REPLY:
      //TODO IEEE GPD
    {
      if (cmd_data.tempMasterShortAddress == emberGetNodeId()) {
        emberAfGreenPowerClusterPrintln("dgpsend comm reply %s", "A");
        result = emberDGpSend(true, //add
                              false, //skip cca
                              &addr,
                              EMBER_ZCL_GP_GPDF_COMMISSIONING_REPLY,
                              cmd_data.gpdCommandPayload[0],
                              cmd_data.gpdCommandPayload + 1,
                              0, 0
                              );
        if (result == EMBER_SUCCESS) {
          emberAfGreenPowerClusterPrintln("success");
        } else {
          emberAfGreenPowerClusterPrintln("fail %02x", result);
        }
      } else {
        emberAfGreenPowerClusterPrintln("Flush GP TX");
        emberDGpSend(false, false, &addr, 0, 0, NULL, 0, 0);
      }
      break;
    }
    default:
    {
      if ((cmd_data.gpdCommandId >= EMBER_ZCL_GP_GPDF_RESERVED_MIN) //and implicitly check gpdCommandId <= EMBER_ZCL_GP_GPDF_RESERVED_MAX
          || (cmd_data.gpdCommandId >= EMBER_ZCL_GP_GPDF_MFR_DEF_GPD_CMD0
              && cmd_data.gpdCommandId <= EMBER_ZCL_GP_GPDF_MFR_DEF_GPD_CMD_F)) {
        emberAfGreenPowerClusterPrintln("dgpsend comm reply %s", "B");
        result = emberDGpSend(true,   //add
                              false,   //skip cca
                              &addr,
                              cmd_data.gpdCommandId,
                              cmd_data.gpdCommandPayload[0],
                              cmd_data.gpdCommandPayload + 1,
                              0, 0
                              );
        if (result == EMBER_SUCCESS) {
          emberAfGreenPowerClusterPrintln("success");
        } else {
          emberAfGreenPowerClusterPrintln("fail %02x", result);
        }
      }
      break;
    }
  }
  kickout: return false;
}

bool emberAfGreenPowerClusterGpProxyTableRequestCallback(EmberAfClusterCommand *cmd)
{
  sl_zcl_green_power_cluster_gp_proxy_table_request_command_t cmd_data;
  uint8_t validEntriesCount = 0;
  uint8_t entryIndex = 0;
  uint8_t appId;
  uint8_t requestType;
  EmberGpProxyTableEntry entry;

  if (zcl_decode_green_power_cluster_gp_proxy_table_request_command(cmd, &cmd_data)
      != EMBER_ZCL_STATUS_SUCCESS) {
    return false;
  }

  appId = cmd_data.options & EMBER_AF_GP_PROXY_TABLE_REQUEST_OPTIONS_APPLICATION_ID;
  requestType = (cmd_data.options & EMBER_AF_GP_PROXY_TABLE_REQUEST_OPTIONS_REQUEST_TYPE)
                >> EMBER_AF_GP_PROXY_TABLE_REQUEST_OPTIONS_REQUEST_TYPE_OFFSET;

  // only respond to unicast messages.
  if (emberAfCurrentCommand()->type != EMBER_INCOMING_UNICAST) {
    goto kickout;
  }

  if (EMBER_GP_PROXY_TABLE_SIZE == 0) {
    emberAfSendImmediateDefaultResponse(EMBER_ZCL_STATUS_UNSUP_COMMAND);
    goto kickout;
  }

  if (emberAfCurrentEndpoint() != EMBER_GP_ENDPOINT) {
    return false;
  }

  for (entryIndex = 0; entryIndex < EMBER_GP_PROXY_TABLE_SIZE; entryIndex++) {
    if (emberGpProxyTableGetEntry(entryIndex, &entry) != EMBER_SUCCESS) {
      return false;
    }

    if (entry.status != EMBER_GP_PROXY_TABLE_ENTRY_STATUS_UNUSED) {
      validEntriesCount++;
    }
  }

  if (requestType == EMBER_ZCL_GP_PROXY_TABLE_REQUEST_OPTIONS_REQUEST_TYPE_BY_GPD_ID) {
    EmberGpAddress addr;
    if (!sli_zigbee_af_gp_make_addr(&addr,
                                    appId,
                                    cmd_data.gpdSrcId,
                                    cmd_data.gpdIeee,
                                    cmd_data.endpoint)
        || IS_GPD_SRC_ID_ZERO(appId, cmd_data.gpdSrcId)) {
      // Invalid app Id or reserved address, just respond back as not found.
      emberAfFillCommandGreenPowerClusterGpProxyTableResponseSmart(EMBER_ZCL_GP_PROXY_TABLE_RESPONSE_STATUS_NOT_FOUND,
                                                                   validEntriesCount,
                                                                   0xff,
                                                                   0);
      sli_zigbee_af_gp_send_response_unicast();
      goto kickout;
    }
    entryIndex = emberGpProxyTableLookup(&addr);
    if (entryIndex == 0xFF) {
      emberAfFillCommandGreenPowerClusterGpProxyTableResponseSmart(EMBER_ZCL_GP_PROXY_TABLE_RESPONSE_STATUS_NOT_FOUND,
                                                                   validEntriesCount,
                                                                   0xff,
                                                                   0);
      sli_zigbee_af_gp_send_response_unicast();
      goto kickout;
    } else {
      emberAfFillCommandGreenPowerClusterGpProxyTableResponseSmart(EMBER_ZCL_GP_PROXY_TABLE_RESPONSE_STATUS_SUCCESS,
                                                                   validEntriesCount,
                                                                   0xff,
                                                                   1);
      if (emberGpProxyTableGetEntry(entryIndex, &entry) != EMBER_SUCCESS) {
        return false;
      }

      appResponseLength
        += storeProxyTableEntry(&entry,
                                appResponseData + appResponseLength);
      sli_zigbee_af_gp_send_response_unicast();
      goto kickout;
    }
  } else if (requestType == EMBER_ZCL_GP_PROXY_TABLE_REQUEST_OPTIONS_REQUEST_TYPE_BY_INDEX) {
    if (cmd_data.index >= validEntriesCount) {
      //Nothing to send
      emberAfFillCommandGreenPowerClusterGpProxyTableResponseSmart(EMBER_ZCL_GP_PROXY_TABLE_RESPONSE_STATUS_NOT_FOUND,
                                                                   validEntriesCount,
                                                                   cmd_data.index,
                                                                   0);
      sli_zigbee_af_gp_send_response_unicast();
      goto kickout;
    } else {
      emberAfFillCommandGreenPowerClusterGpProxyTableResponseSmart(EMBER_ZCL_GP_PROXY_TABLE_RESPONSE_STATUS_SUCCESS,
                                                                   validEntriesCount,
                                                                   cmd_data.index,
                                                                   0);

      validEntriesCount = 0;
      uint16_t entriesCount = 0;
      for (entryIndex = 0; entryIndex < EMBER_GP_PROXY_TABLE_SIZE; entryIndex++) {
        if (emberGpProxyTableGetEntry(entryIndex, &entry) != EMBER_SUCCESS) {
          return false;
        }

        uint8_t  tempDatabuffer[EMBER_AF_RESPONSE_BUFFER_LEN];
        uint16_t tempDataLength = 0;

        if (entry.status != EMBER_GP_PROXY_TABLE_ENTRY_STATUS_UNUSED) {
          validEntriesCount++;
          if (validEntriesCount > cmd_data.index) {
            // Copy to a temp buffer and add if there is spoce
            tempDataLength = storeProxyTableEntry(&entry, tempDatabuffer);

            // If space add to buffer
            if ( sizeof(appResponseData) > (appResponseLength + tempDataLength)) {
              MEMMOVE(&appResponseData[appResponseLength], tempDatabuffer, tempDataLength);
              appResponseLength +=  tempDataLength;
              entriesCount++;
            } else {
              break;
            }
          }
        }
      }

      //Insert the number of entries actually included
      appResponseData[GP_PROXY_TABLE_RESPONSE_ENTRIES_OFFSET + GP_NON_MANUFACTURER_ZCL_HEADER_LENGTH] = entriesCount;

      EmberStatus status = sli_zigbee_af_gp_send_response_unicast();

      if (status == EMBER_MESSAGE_TOO_LONG) {
        emberAfFillCommandGreenPowerClusterGpProxyTableResponseSmart(EMBER_ZCL_GP_PROXY_TABLE_RESPONSE_STATUS_SUCCESS,
                                                                     validEntriesCount,
                                                                     cmd_data.index,
                                                                     0);
        sli_zigbee_af_gp_send_response_unicast();
      }
      goto kickout;
    }
  }

  kickout:  return true;
}

bool sli_zigbee_af_green_power_client_retrieve_attribute_and_craft_response(uint8_t endpoint,
                                                                            EmberAfClusterId clusterId,
                                                                            EmberAfAttributeId attrId,
                                                                            uint8_t mask,
                                                                            uint16_t manufacturerCode,
                                                                            uint16_t readLength)
{
  uint8_t proxyTableEntryAppResponseData[EMBER_AF_RESPONSE_BUFFER_LEN];
  uint8_t zclStatus = EMBER_ZCL_STATUS_SUCCESS;
  uint16_t stringDataOffsetStart = 0;
  uint16_t stringLength = 0;
  bool    status = false;

  if (endpoint != EMBER_GP_ENDPOINT
      || clusterId != ZCL_GREEN_POWER_CLUSTER_ID
      || attrId != ZCL_GP_CLIENT_PROXY_TABLE_ATTRIBUTE_ID
      || mask != CLUSTER_MASK_CLIENT
      || manufacturerCode != EMBER_AF_NULL_MANUFACTURER_CODE) {
    // do nothing but return false
  } else if (readLength < 6) {
    // Can't fit the ZCL header in available length so exit with error
    // do nothing but return true as we are processing the correct type of packet
  } else {
    (void) emberAfPutInt16uInResp(attrId);

    // The proxy table attribute is a long string ZCL attribute type, which means
    // it is encoded starting with a 2-byte length. We fill in the real length
    // after we have encoded the whole proxy table.
    // Fopur bytes extra = 2byte length + 1 byte ZCl Status + 1 byte Attribute Type
    uint16_t stringDataOffset =  appResponseLength + 4;
    stringDataOffsetStart = stringDataOffset;

    // Search the proxy table and respond with entries
    for (uint8_t i = 0; i < EMBER_GP_PROXY_TABLE_SIZE; i++) {
      EmberGpProxyTableEntry entry;

      if (emberGpProxyTableGetEntry(i, &entry) != EMBER_SUCCESS) {
        return false;
      } else if (entry.status != EMBER_GP_PROXY_TABLE_ENTRY_STATUS_UNUSED) {
        // Have a valid entry so encode response in temp buffer and add if it fits
        uint16_t proxyTableEntryLength = storeProxyTableEntry(&entry, proxyTableEntryAppResponseData);

        if ( (proxyTableEntryLength + stringDataOffset) > readLength) {
          // String is too big so
          zclStatus = EMBER_ZCL_STATUS_INSUFFICIENT_SPACE;
          break;
        } else {
          MEMMOVE(&appResponseData[stringDataOffset], proxyTableEntryAppResponseData, proxyTableEntryLength);
          stringDataOffset += proxyTableEntryLength;
        }
      }
    }

    // calculate string length
    stringLength = stringDataOffset - stringDataOffsetStart;

    if (zclStatus == EMBER_ZCL_STATUS_SUCCESS) {
      (void) emberAfPutInt8uInResp(zclStatus);
      (void) emberAfPutInt8uInResp(ZCL_LONG_OCTET_STRING_ATTRIBUTE_TYPE);
      (void) emberAfPutInt16uInResp(stringLength);
    } else {
      (void) emberAfPutInt8uInResp(zclStatus);
    }

    appResponseLength += stringLength;
    status = true;
  }

  return status;
}

static UNUSED uint8_t qualityBasedDelay(uint8_t gpdLink)
{
  // The top 2 bits of gpdlink is operated with the mask 0xC0 (b11000000), hence needs to be shifted by 6.
  uint8_t ourLqi = (gpdLink & 0xC0) >> 6;
  // A.3.6.3.1 : QualityBasedDelay is calculated as follows:
  //  For Link quality = 0b11: 0 ms;
  //  For Link quality = 0b10: 32ms;
  //  For Link quality = 0b01: 64ms;
  //  For Link quality = 0b00: 96ms;
  // So, the return from this function is a delay expressed as b0XX00000 ms, where bXX is (3 - ourLqi) in binary
  return ((3 - ourLqi) << 5);
}

static UNUSED void gppTunnelingDelay(uint8_t bidirectionalInfo, uint8_t gpdLink)
{
  if (bidirectionalInfo & EMBER_GP_BIDIRECTION_INFO_RX_AFTER_TX_MASK) {
    sli_zigbee_af_set_add_delay(GP_DMIN_B + qualityBasedDelay(gpdLink));
  } else {
    sli_zigbee_af_set_add_delay(GP_DMIN_U + qualityBasedDelay(gpdLink));
  }
}

static bool autoCommissioningCallback(GP_PARAMS)
{
  uint16_t options = 0;
  EmberApsFrame *apsFrame = NULL;

  if (!commissioningState.inCommissioningMode) {
    return true;
  }

  if (addr->applicationId == EMBER_GP_APPLICATION_SOURCE_ID
      && addr->id.sourceId == 0x00000000) {
    return true;
  }
  if (gpdCommandId == EMBER_ZCL_GP_GPDF_COMMISSIONING || gpdCommandId == EMBER_ZCL_GP_GPDF_SUCCESS) {
    return true;
  }

  if (bidirectionalInfo & EMBER_GP_BIDIRECTION_INFO_RX_AFTER_TX_MASK) {
    return true;
  }

  /* TODO
     uint8_t UNUSED proxyIndex = 0xFF;
     proxyIndex = emberGpProxyTableLookup(addr);
     if (proxyIndex != 0xFF) {
     //we have a proxy table entry for this GPD
     sli_zigbee_gp_proxy_table_set_in_range(proxyIndex);
     } else {
     //we don't have a proxy table entry
     //optionally create an active invalid entry here
     //not required for proxy basic
     }
   */

  if (status == EMBER_NO_SECURITY) {
    options = 0;
  }
  //TODO handle other cases

  options |= addr->applicationId;
  options |= gpdfSecurityLevel
             << GP_COMMISSIONING_SECURITY_LEVEL_TO_OPTIONS_SHIFT;
  options |= gpdfSecurityKeyType
             << GP_COMMISSIONING_SECURITY_KEY_TYPE_TO_OPTIONS_SHIFT; //security key type
  options |= EMBER_AF_GP_COMMISSIONING_NOTIFICATION_OPTION_PROXY_INFO_PRESENT;
  if (emberAfFillCommandGreenPowerClusterGpCommissioningNotificationSmart(options,
                                                                          addr->id.sourceId,
                                                                          addr->id.gpdIeeeAddress,
                                                                          addr->endpoint,
                                                                          sequenceNumber,
                                                                          gpdfSecurityLevel,
                                                                          gpdSecurityFrameCounter,
                                                                          gpdCommandId,
                                                                          gpdCommandPayloadLength,
                                                                          gpdCommandPayload,
                                                                          emberGetNodeId(),
                                                                          gpdLink,
                                                                          mic) == 0) {
    return true;
  }

  apsFrame = emberAfGetCommandApsFrame();
  apsFrame->sourceEndpoint = EMBER_GP_ENDPOINT; //emberAfCurrentEndpoint();
  apsFrame->destinationEndpoint = EMBER_GP_ENDPOINT; //emberAfCurrentEndpoint();
  gppTunnelingDelay(bidirectionalInfo, gpdLink);
  if (commissioningState.unicastCommunication) {
    emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT,
                              commissioningState.commissioningSink);
  } else {
    apsFrame->sequence = sequenceNumber - EMBER_GP_COMMISSIONING_NOTIFICATION_SEQUENCE_NUMBER_OFFSET;
    apsFrame->options |= EMBER_APS_OPTION_USE_ALIAS_SEQUENCE_NUMBER;
    emberAfSendCommandBroadcastWithAlias(EMBER_RX_ON_WHEN_IDLE_BROADCAST_ADDRESS,
                                         sli_zigbee_af_gpd_alias(addr),
                                         sequenceNumber - EMBER_GP_COMMISSIONING_NOTIFICATION_SEQUENCE_NUMBER_OFFSET);
  }
  sli_zigbee_af_set_add_delay(0);
  return true;
}

static bool commissioningGpdfCallback(GP_PARAMS)
{
  EmberApsFrame *apsFrame;

  // Per GP spec 14-0563-08:
  // Commissioning: Step 12a: Proxy receives commissioning command
  // If applicationId == 0b0000 and srcId == 0 or reserved range 0xfffffff9 - 0xffffffffe
  // OR applicationId == 0b0010 and srcId == 0, drop frame.
  if (!sli_zigbee_af_gp_make_addr(addr,
                                  addr->applicationId,
                                  addr->id.sourceId,
                                  addr->id.gpdIeeeAddress,
                                  addr->endpoint)
      || IS_GPD_SRC_ID_ZERO(addr->applicationId, addr->id.sourceId)) {
    // GPD Address or App Id are invalid, so drop the command
    goto kickout;
  }

  if (autoCommissioning) {
    goto kickout;
  }

  // Step b
  if ((gpdfSecurityLevel == EMBER_GP_SECURITY_LEVEL_FC_MIC)
      || (gpdfSecurityLevel == EMBER_GP_SECURITY_LEVEL_FC_MIC_ENCRYPTED)) {
    if ((status == EMBER_AUTH_FAILURE)
        || (status == EMBER_UNPROCESSED)) {
      // fwd frame with Security processing failed bit set as part of GP
      // Commissioning Notification.
      goto send_notification;
    }
  }

  // Step c
  // RxAfterTx is true
  {
    bool frameFound = false;
    if ((bidirectionalInfo & EMBER_GP_BIDIRECTION_INFO_RX_AFTER_TX_MASK)
        && (gpdCommandId == EMBER_ZCL_GP_GPDF_COMMISSIONING)) {
      if (addr->applicationId == EMBER_GP_APPLICATION_IEEE_ADDRESS) {
        // TODO: check endpoint
      }
    }

    if (frameFound) {
      // send at least one Commissioning Reply GPDF
      //XXX compare to where we do this now
    }
  }

  // Step d
  /* TODO
     {
     uint8_t gpProxyTableIndex = emberGpProxyTableLookup(addr);
     if (gpProxyTableIndex != 0xFF) {
      sli_zigbee_gp_proxy_table_set_in_range(gpProxyTableIndex);
     } else {
       //basic proxy doesn't have to do anything in this situation
     }

     }
   */

  // Step e: sending GP Commissioning Notification
  send_notification: {
    uint16_t options = addr->applicationId;
    if (bidirectionalInfo & EMBER_GP_BIDIRECTION_INFO_RX_AFTER_TX_MASK) {
      options |= EMBER_AF_GP_COMMISSIONING_NOTIFICATION_OPTION_RX_AFTER_TX;
    }

    if ((status == EMBER_AUTH_FAILURE)
        || (status == EMBER_UNPROCESSED)) {
      options |=
        EMBER_AF_GP_COMMISSIONING_NOTIFICATION_OPTION_SECURITY_PROCESSING_FAILED;
      options |= (gpdfSecurityKeyType ? 0x4 : 0) // see 1.0 spec line 3040
                 << GP_COMMISSIONING_SECURITY_KEY_TYPE_TO_OPTIONS_SHIFT;
    } else {
      options |= gpdfSecurityKeyType
                 << GP_COMMISSIONING_SECURITY_KEY_TYPE_TO_OPTIONS_SHIFT;
    }

    options |= gpdfSecurityLevel
               << GP_COMMISSIONING_SECURITY_LEVEL_TO_OPTIONS_SHIFT;
    options |= EMBER_AF_GP_COMMISSIONING_NOTIFICATION_OPTION_PROXY_INFO_PRESENT;
    if (commissioningState.unicastCommunication) {
      if (emberAfFillCommandGreenPowerClusterGpCommissioningNotificationSmart(options,
                                                                              addr->id.sourceId,
                                                                              addr->id.gpdIeeeAddress,
                                                                              addr->endpoint,
                                                                              sequenceNumber,
                                                                              gpdfSecurityLevel,
                                                                              gpdSecurityFrameCounter,
                                                                              gpdCommandId,
                                                                              gpdCommandPayloadLength,
                                                                              gpdCommandPayload,
                                                                              emberGetNodeId(),
                                                                              gpdLink,
                                                                              mic) == 0) {
        goto kickout;
      }

      gppTunnelingDelay(bidirectionalInfo, gpdLink);
      apsFrame = emberAfGetCommandApsFrame();
      apsFrame->sourceEndpoint = EMBER_GP_ENDPOINT;  //emberAfCurrentEndpoint();
      apsFrame->destinationEndpoint = EMBER_GP_ENDPOINT; //emberAfCurrentEndpoint();
      UNUSED EmberStatus retval = emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT,
                                                            commissioningState.commissioningSink);
      sli_zigbee_af_set_add_delay(0);
    } else {
      if (emberAfFillCommandGreenPowerClusterGpCommissioningNotificationSmart(options,
                                                                              addr->id.sourceId,
                                                                              addr->id.gpdIeeeAddress,
                                                                              addr->endpoint,
                                                                              sequenceNumber,
                                                                              gpdfSecurityLevel,
                                                                              gpdSecurityFrameCounter,
                                                                              gpdCommandId,
                                                                              gpdCommandPayloadLength,
                                                                              gpdCommandPayload,
                                                                              emberGetNodeId(),
                                                                              gpdLink,
                                                                              mic) == 0) {
        goto kickout;
      }

      apsFrame = emberAfGetCommandApsFrame();
      apsFrame->sourceEndpoint = EMBER_GP_ENDPOINT;  //emberAfCurrentEndpoint();
      apsFrame->destinationEndpoint = EMBER_GP_ENDPOINT; //emberAfCurrentEndpoint();
      apsFrame->sequence = sequenceNumber - EMBER_GP_COMMISSIONING_NOTIFICATION_SEQUENCE_NUMBER_OFFSET;
      apsFrame->options |= EMBER_APS_OPTION_USE_ALIAS_SEQUENCE_NUMBER;
      gppTunnelingDelay(bidirectionalInfo, gpdLink);

      UNUSED EmberStatus retval = emberAfSendCommandBroadcastWithAlias(EMBER_RX_ON_WHEN_IDLE_BROADCAST_ADDRESS,
                                                                       sli_zigbee_af_gpd_alias(addr),
                                                                       sequenceNumber - EMBER_GP_COMMISSIONING_NOTIFICATION_SEQUENCE_NUMBER_OFFSET);
      sli_zigbee_af_set_add_delay(0);
    }
  }

  kickout: return true;
}

static bool channelRequestGpdfCallback(GP_PARAMS)
{
  if (!commissioningState.inCommissioningMode) {
    return true;
  }

  // based on figure 88 of GP proxy basic spec V1.0 page 191
  // the second condition of the following condition seems neccessary
  if ((commissioningState.channelStatus & GP_CLIENT_ON_TRANSMIT_CHANNEL_MASK)
      && (!(commissioningState.channelStatus & GP_CLIENT_TRANSMIT_SAME_AS_OPERATIONAL_CHANNEL_MASK))) {
    //Don't forward if we're on the transmit channel, and the transmit channel
    // is not same as the operational channel
  } else {
    //TODO: check for a reason not to forward (busy, etc)

    uint16_t options = 0; //always uses appID srcID becase srcID is absent was addr.applicationId;

    //rxAfter Tx always set for channel request
    options |=
      EMBER_AF_GP_COMMISSIONING_NOTIFICATION_OPTION_RX_AFTER_TX;

    if (status == EMBER_AUTH_FAILURE) {
      options |=
        EMBER_AF_GP_COMMISSIONING_NOTIFICATION_OPTION_SECURITY_PROCESSING_FAILED;
    }

    options |= gpdfSecurityLevel
               << GP_COMMISSIONING_SECURITY_LEVEL_TO_OPTIONS_SHIFT;
    options |= gpdfSecurityKeyType
               << GP_COMMISSIONING_SECURITY_KEY_TYPE_TO_OPTIONS_SHIFT;
    options |= EMBER_AF_GP_COMMISSIONING_NOTIFICATION_OPTION_PROXY_INFO_PRESENT;

    EmberApsFrame *apsFrame;

    if (commissioningState.unicastCommunication) {
      if (emberAfFillCommandGreenPowerClusterGpCommissioningNotificationSmart(options,
                                                                              0x00000000, //addr.id.sourceId,
                                                                              NULL, //addr.id.gpdIeeeAddress,
                                                                              0, //addr.endpoint,
                                                                              sequenceNumber,
                                                                              gpdfSecurityLevel,
                                                                              gpdSecurityFrameCounter,
                                                                              gpdCommandId,
                                                                              gpdCommandPayloadLength,
                                                                              gpdCommandPayload,
                                                                              emberGetNodeId(),
                                                                              gpdLink,
                                                                              mic) == 0) {
        return true;
      }

      apsFrame = emberAfGetCommandApsFrame();
      apsFrame->sourceEndpoint = EMBER_GP_ENDPOINT;  //emberAfCurrentEndpoint();
      apsFrame->destinationEndpoint = EMBER_GP_ENDPOINT; //emberAfCurrentEndpoint();
      gppTunnelingDelay(bidirectionalInfo, gpdLink);
      UNUSED EmberStatus retval = emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT,
                                                            commissioningState.commissioningSink);
      sli_zigbee_af_set_add_delay(0);
    } else {
      if (emberAfFillCommandGreenPowerClusterGpCommissioningNotificationSmart(options,
                                                                              0x00000000, //addr.id.sourceId,
                                                                              NULL, //addr.id.gpdIeeeAddress,
                                                                              0, //addr.endpoint,
                                                                              sequenceNumber,
                                                                              gpdfSecurityLevel,
                                                                              gpdSecurityFrameCounter,
                                                                              gpdCommandId,
                                                                              gpdCommandPayloadLength,
                                                                              gpdCommandPayload,
                                                                              emberGetNodeId(),
                                                                              gpdLink,
                                                                              mic) == 0) {
        return true;
      }

      apsFrame = emberAfGetCommandApsFrame();
      apsFrame->sourceEndpoint = EMBER_GP_ENDPOINT;  //emberAfCurrentEndpoint();
      apsFrame->destinationEndpoint = EMBER_GP_ENDPOINT; //emberAfCurrentEndpoint();
      apsFrame->sequence = sequenceNumber - EMBER_GP_COMMISSIONING_NOTIFICATION_SEQUENCE_NUMBER_OFFSET;
      apsFrame->options |= EMBER_APS_OPTION_USE_ALIAS_SEQUENCE_NUMBER;
      gppTunnelingDelay(bidirectionalInfo, gpdLink);
      UNUSED EmberStatus retval = emberAfSendCommandBroadcastWithAlias(EMBER_RX_ON_WHEN_IDLE_BROADCAST_ADDRESS,
                                                                       sli_zigbee_af_gpd_alias(addr),
                                                                       sequenceNumber - EMBER_GP_COMMISSIONING_NOTIFICATION_SEQUENCE_NUMBER_OFFSET);
      sli_zigbee_af_set_add_delay(0);
    }
  }

  return true;
}

static bool gpdfForwardCallback(GP_PARAMS)
{
  uint8_t i;
  uint16_t options = 0;
  uint16_t alias = 0;
  EmberApsFrame *apsFrame;

  if (proxyTableIndex == 0xFF) {
    return true;
  }
  EmberGpProxyTableEntry entry;
  if (proxyTableIndex != 0xFF) {
#ifndef EZSP_HOST
    //TODO, we need to decide how to do this for host
    sli_zigbee_gp_proxy_table_set_first_to_forward(proxyTableIndex);
    sli_zigbee_gp_proxy_table_set_in_range(proxyTableIndex);    //TODO is this the right place for this?
#endif
    if (emberGpProxyTableGetEntry(proxyTableIndex, &entry) != EMBER_SUCCESS) {
      return true;
    }
  }

  options |= addr->applicationId;

  //Traverse the sink list to set the options flags
  for (i = 0; i < GP_SINK_LIST_ENTRIES; i++) {
    if (entry.sinkList[i].type == EMBER_GP_SINK_TYPE_FULL_UNICAST
        || entry.sinkList[i].type == EMBER_GP_SINK_TYPE_LW_UNICAST) {
      options |= EMBER_AF_GP_NOTIFICATION_OPTION_ALSO_UNICAST;
    } else if (entry.sinkList[i].type == EMBER_GP_SINK_TYPE_GROUPCAST) {
      options |= EMBER_AF_GP_NOTIFICATION_OPTION_ALSO_COMMISSIONED_GROUP;
    }
  }

  if (entry.options & EMBER_AF_GP_PROXY_TABLE_ENTRY_OPTIONS_DERIVED_GROUP_GPS) {
    options |= EMBER_AF_GP_NOTIFICATION_OPTION_ALSO_DERIVED_GROUP;
  }

  options |= gpdfSecurityLevel
             << EMBER_AF_GP_NOTIFICATION_OPTION_SECURITY_LEVEL_OFFSET;

  options |= gpdfSecurityKeyType
             << EMBER_AF_GP_NOTIFICATION_OPTION_SECURITY_KEY_TYPE_OFFSET;

#ifndef ENABLE_BIDIRECTIONAL_OPERATION
  //Basic proxy always sends queue full for data gpdfs (not commissioning)
  options |= EMBER_AF_GP_NOTIFICATION_OPTION_GP_TX_QUEUE_FULL;
#else
  // Advanced proxy uses queue availability to fill this information
  options |= (bidirectionalInfo & EMBER_GP_BIDIRECTION_INFO_TX_QUEUE_AVAILABLE_MASK) \
             ? 0 : EMBER_AF_GP_NOTIFICATION_OPTION_GP_TX_QUEUE_FULL;
#endif
  // Basic Proxy implementing the latest spec always sets this
  options |= EMBER_AF_GP_NOTIFICATION_OPTION_PROXY_INFO_PRESENT;

  // comm/decomm frames ignore rx after tx bit in operational mode
  if (((gpdCommandId != EMBER_ZCL_GP_GPDF_COMMISSIONING
        && gpdCommandId != EMBER_ZCL_GP_GPDF_DECOMMISSIONING)
       || commissioningState.inCommissioningMode)
      && (bidirectionalInfo & EMBER_GP_BIDIRECTION_INFO_RX_AFTER_TX_MASK)) {
    options |= EMBER_AF_GP_NOTIFICATION_OPTION_RX_AFTER_TX;
  }

  if (  gpdfSecurityLevel == EMBER_GP_SECURITY_KEY_NONE) {
    // If no security use the MAC sequence number instead
    gpdSecurityFrameCounter = (uint32_t)(sequenceNumber & 0x000000ff);
  }

  if (emberAfFillCommandGreenPowerClusterGpNotificationSmart(options,
                                                             addr->id.sourceId,
                                                             addr->id.gpdIeeeAddress,
                                                             addr->endpoint,
                                                             gpdSecurityFrameCounter,
                                                             gpdCommandId,
                                                             gpdCommandPayloadLength,
                                                             gpdCommandPayload,
                                                             emberGetNodeId(),
                                                             gpdLink) == 0) {
    return true;
  }

  // The Proxy table gets populated from the Gp Pairing message that does not have capability to accept the
  // sink group list. But in a combo application, that has both sink and proxy, the sink list can be supplied
  // using the Gp Pairing Configuration command from a commissioning tool and the sink table holds those
  // in its entry. And the expected outcome from the combo basic is that it should be able to forward
  // the messages to the sink table based groupcast. The following callback is used to get an updated sink
  // list entry from user. If the green power server is present it implements this callback.
  emberAfGreenPowerClientGpdfSinkTableBasedForwardCallback(addr,
                                                           entry.sinkList,
                                                           GP_SINK_LIST_ENTRIES);

  for (i = 0; i < GP_SINK_LIST_ENTRIES; i++) {
    if (entry.sinkList[i].type == EMBER_GP_SINK_TYPE_FULL_UNICAST
        || entry.sinkList[i].type == EMBER_GP_SINK_TYPE_LW_UNICAST) {
      apsFrame = emberAfGetCommandApsFrame();
      apsFrame->sourceEndpoint = EMBER_GP_ENDPOINT;  //emberAfCurrentEndpoint();
      apsFrame->destinationEndpoint = EMBER_GP_ENDPOINT;  //emberAfCurrentEndpoint();
      gppTunnelingDelay(bidirectionalInfo, gpdLink);
      // The sinkNodeId is optimised to not be in the proxy table token structure because it can be looked up.
      // Incase the proxy table is updated witha valid address earlier it needs to use that.
      // So, check if the proxy table node id is not valid UCAST id before looking up the map and then forward the notification.
      if (!isNodeIdValid(entry.sinkList[i].target.unicast.sinkNodeId)) {
        EmberNodeId nodeId = emberLookupNodeIdByEui64(entry.sinkList[i].target.unicast.sinkEUI);
        if (isNodeIdValid(nodeId)) {
          entry.sinkList[i].target.unicast.sinkNodeId = nodeId;
        }
      }

      UNUSED EmberStatus retval = emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT,
                                                            entry.sinkList[i].target.unicast.sinkNodeId);
      sli_zigbee_af_set_add_delay(0);
    } else if (entry.sinkList[i].type == EMBER_GP_SINK_TYPE_GROUPCAST) {
      apsFrame = emberAfGetCommandApsFrame();
      apsFrame->sourceEndpoint = EMBER_GP_ENDPOINT;  //emberAfCurrentEndpoint();
      apsFrame->destinationEndpoint = EMBER_GP_ENDPOINT;  //emberAfCurrentEndpoint();
      apsFrame->sequence = sequenceNumber - EMBER_GP_NOTIFICATION_COMMISSIONED_GROUPCAST_SEQUENCE_NUMBER_OFFSET;
      apsFrame->options |= EMBER_APS_OPTION_USE_ALIAS_SEQUENCE_NUMBER;
      apsFrame->radius = entry.groupcastRadius;
      gppTunnelingDelay(bidirectionalInfo, gpdLink);
      UNUSED EmberStatus retval = emberAfSendCommandMulticastWithAlias(entry.sinkList[i].target.groupcast.groupID,
                                                                       (entry.sinkList[i].target.groupcast.alias == 0xFFFF)
                                                                       ? sli_zigbee_af_gpd_alias(addr)
                                                                       : entry.sinkList[i].target.groupcast.alias,
                                                                       sequenceNumber - EMBER_GP_NOTIFICATION_COMMISSIONED_GROUPCAST_SEQUENCE_NUMBER_OFFSET);
      sli_zigbee_af_set_add_delay(0);
    }
  }
  if (entry.options & EMBER_AF_GP_PROXY_TABLE_ENTRY_OPTIONS_DERIVED_GROUP_GPS) {
    apsFrame = emberAfGetCommandApsFrame();
    apsFrame->sourceEndpoint = EMBER_GP_ENDPOINT;  //emberAfCurrentEndpoint();
    apsFrame->destinationEndpoint = EMBER_GP_ENDPOINT;  //emberAfCurrentEndpoint();
    apsFrame->sequence = sequenceNumber;
    apsFrame->options |= EMBER_APS_OPTION_USE_ALIAS_SEQUENCE_NUMBER;
    apsFrame->radius = entry.groupcastRadius;
    gppTunnelingDelay(bidirectionalInfo, gpdLink);

    //get derived alias for address alias and group ID alias
    if (entry.options & EMBER_AF_GP_PROXY_TABLE_ENTRY_OPTIONS_ASSIGNED_ALIAS) {
      alias = entry.assignedAlias;
    } else {
      alias = sli_zigbee_af_gpd_alias(addr);
    }

    UNUSED EmberStatus retval = emberAfSendCommandMulticastWithAlias((EmberMulticastId)sli_zigbee_af_gpd_alias(addr),
                                                                     (EmberNodeId)alias,
                                                                     sequenceNumber);
    sli_zigbee_af_set_add_delay(0);
  }
  return true;
}

/*
 * Check if a EmberGpAddress entry is being used by checking each elemental
 * sequence number's corresponding expiration time field.
 */
static bool is_gp_addr_used(EmberAfGreenPowerDuplicateFilter * filter,
                            uint8_t index)
{
  uint32_t * expirationTimes;
  uint8_t i;
  uint32_t curTime = halCommonGetInt32uMillisecondTick();

  if (index >= EMBER_AF_PLUGIN_GREEN_POWER_CLIENT_MAX_ADDR_ENTRIES) {
    return true;
  }
  expirationTimes = (uint32_t *) &(filter->expirationTimes[index][0]);

  for (i = 0;
       i < EMBER_AF_PLUGIN_GREEN_POWER_CLIENT_MAX_SEQ_NUM_ENTRIES_PER_ADDR;
       i++) {
    if (expirationTimes[i] > curTime) {
      return true;
    }
  }

  return false;
}

/*
 * return index to the entry with the smallest expiration date.
 */
static uint8_t find_earliest_expiration_time_in_addr(EmberAfGreenPowerDuplicateFilter * filter,
                                                     uint8_t addrIndex)
{
  // addrIndex must be less than EMBER_AF_PLUGIN_GREEN_POWER_CLIENT_MAX_SEQ_NUM_ENTRIES_PER_ADDR
  // so we dont need to check it here. It is done in preceding function calls.
  uint32_t * expirationTimes = filter->expirationTimes[addrIndex];
  uint32_t earliestTimeIndex = 0;
  uint32_t earliestTime = expirationTimes[0];
  uint8_t index;

  for (index = 0;
       index < EMBER_AF_PLUGIN_GREEN_POWER_CLIENT_MAX_SEQ_NUM_ENTRIES_PER_ADDR;
       index++) {
    if (expirationTimes[index] < earliestTime) {
      earliestTime = expirationTimes[index];
      earliestTimeIndex = index;
    }
  }

  return earliestTimeIndex;
}

static bool add_random_mac_seq_num(EmberAfGreenPowerDuplicateFilter * filter,
                                   uint8_t addrIndex,
                                   uint8_t randomSeqNum)
{
  uint8_t * seqNumList = NULL;
  uint32_t * expirationTimeList = NULL;
  uint8_t i;
  uint32_t curTime = halCommonGetInt32uMillisecondTick();
  uint8_t entryIndex;

  // addrIndex must be less than the EMBER_AF_PLUGIN_GREEN_POWER_CLIENT_MAX_SEQ_NUM_ENTRIES_PER_ADDR
  // so we dont need to check it here. It is done in preceding function calls.
  seqNumList = (filter->randomSeqNums[addrIndex]);
  expirationTimeList = (filter->expirationTimes[addrIndex]);

  // check if an existing sequence number with valid expiration date exists
  for (i = 0;
       i < EMBER_AF_PLUGIN_GREEN_POWER_CLIENT_MAX_SEQ_NUM_ENTRIES_PER_ADDR;
       i++) {
    if ((randomSeqNum == seqNumList[i]) && (expirationTimeList[i] > curTime)) {
      return false;
    }
  }

  entryIndex = find_earliest_expiration_time_in_addr(filter,
                                                     addrIndex);

  seqNumList[entryIndex] = randomSeqNum;
  expirationTimeList[entryIndex] = curTime + (2 * MILLISECOND_TICKS_PER_MINUTE);

  return true;
}

/* Helper function for handling duplicateFilter */
static uint8_t find_gp_addr_index(EmberGpAddress * addr,
                                  EmberGpAddress * addrList,
                                  uint8_t sizeOfList)
{
  uint8_t index = 0;
  for (index = 0; index < sizeOfList; index++) {
    if (sli_zigbee_af_gp_address_match(addr, &addrList[index])) {
      return index;
    }
  }

  return 0xFF;
}

static uint8_t add_gp_addr(EmberAfGreenPowerDuplicateFilter * filter,
                           EmberGpAddress * addr)
{
  uint8_t addrIndex;

  for (addrIndex = 0;
       addrIndex < EMBER_AF_PLUGIN_GREEN_POWER_CLIENT_MAX_ADDR_ENTRIES;
       addrIndex++) {
    if (!is_gp_addr_used(&duplicateFilter, addrIndex)) {
      MEMCOPY(&filter->addrs[addrIndex], addr, sizeof(EmberGpAddress));
      return addrIndex;
    }
  }

  return 0xFF;
}

/*
 * Check if the incoming message is a duplicate message when the GPD's
 * Mac Sequence Number Capability indicate that random Mac Sequence Number is
 * used.
 *
 *
 * @return
 * If a duplicate mac sequence number has been found, we'll return true in
 * order to reject the message. Otherwise, we'll save the new random mac seq
 * number and return false to accept the message.
 *
 */
bool sli_zigbee_af_green_power_find_duplicate_mac_seq_num(EmberGpAddress * addr,
                                                          uint8_t randomSeqNum)
{
  bool added = false;
  uint8_t addrIndex = find_gp_addr_index(addr,
                                         duplicateFilter.addrs,
                                         EMBER_AF_PLUGIN_GREEN_POWER_CLIENT_MAX_ADDR_ENTRIES);
  if (addrIndex == 0xFF) {
    addrIndex = add_gp_addr(&duplicateFilter, addr);
  }

  if (addrIndex == 0xFF) {
    return false;
  }

  added = add_random_mac_seq_num(&duplicateFilter,
                                 addrIndex,
                                 randomSeqNum);
  return !added;
}

/*
 * This function implements the "Duplicate checking" and "Freshness check"
 * section of the GP implementation details.
 *
 * @return true if given sequenceNumber is valid and message should be
 *         accepted, false otherwise.
 */
bool sli_zigbee_af_gp_message_checking(EmberGpAddress *gpAddr, uint8_t sequenceNumber)
{
  /*
     uint8_t proxyTableIndex = emberGpProxyTableLookup(gpAddr);
     EmberGpProxyTableEntry entry;
     EmberGpSecurityLevel securityLevel;
     EmberGpGpdMacSeqNumCap macCap;

     if (proxyTableIndex == 0xFF) {
     return true;
     }

     emberGpProxyTableGetEntry(proxyTableIndex, &entry);
     securityLevel = (EmberGpSecurityLevel) ((entry.options >> 9) & 0x03);
     macCap = (EmberGpGpdMacSeqNumCap) ((entry.options >> 8) & 0x01);

     // Duplicate filtering / Freshness check
     if (securityLevel == EMBER_GP_SECURITY_LEVEL_NONE) {
     // filter by MAC Sequence Number
     if (macCap == EMBER_GP_GPD_MAC_SEQ_NUM_CAP_SEQUENTIAL) {
      uint8_t macSeqNum = (entry.gpdSecurityFrameCounter) & 0xFF;
      if (sequenceNumber <= macSeqNum) {
        emberAfGreenPowerClusterPrintln("Drop frame due to invalid sequence number. incoming(0x%4X), current(0x%4X)", sequenceNumber, macSeqNum);
        return false;
      }
     } else { // EMBER_GP_GPD_MAC_SEQ_NUM_CAP_RANDOM
      if (sli_zigbee_af_green_power_find_duplicate_mac_seq_num(gpAddr, sequenceNumber)) {
        emberAfGreenPowerClusterPrintln("Drop frame due to duplicate sequence number: 0x%4X", sequenceNumber);
        return false;
      }
     }
     } else if ((securityLevel == EMBER_GP_SECURITY_LEVEL_FC_MIC)
   || (securityLevel == EMBER_GP_SECURITY_LEVEL_FC_MIC_ENCRYPTED)) {
     // filter base on GPD security frame counter
     if (sequenceNumber <= entry.gpdSecurityFrameCounter) {
      emberAfGreenPowerClusterPrintln("Drop frame due to lower sequence number: 0x%4X", sequenceNumber);
      return false;
     }
   */
  return true;
}

//GP-DATA.indication
void sli_zigbee_af_green_power_client_gpep_incoming_message_callback(GP_PARAMS)
{
  //emberAfGreenPowerClusterPrintln("Gpep cmd %x status %x SFC %4x", gpdCommandId, status, gpdSecurityFrameCounter);
  if ((commissioningState.channelStatus & GP_CLIENT_ON_TRANSMIT_CHANNEL_MASK)
      && gpdCommandId != EMBER_ZCL_GP_GPDF_CHANNEL_REQUEST) {
    //drop everything but a channel request when we're off on a different channel
    return;
  }

  if ( gpdfSecurityLevel == EMBER_GP_SECURITY_LEVEL_NONE
       && !commissioningState.inCommissioningMode) {
    // earlier a message satisfying this condition would have been
    // dropped in gp-data, but
    // this check is needed here after we added a condition
    // in gp-data to always pass up the unsecure commissioning messages
    // up to this function (EMZIGBEE-1417)
    // when we have a security enabled proxy table entry
    // We only need to forward the unsecure commisioning messages
    // in the commisisong mode, and not in the operational mode
    // (EMZIGBEE-1578)
    bool secureEntry = false;
    uint8_t index = emberGpProxyTableLookup(addr);
    if (index != 0xFF) {
      EmberGpProxyTableEntry entry;
      EmberStatus getStatus = emberGpProxyTableGetEntry(index, &entry);
      if (getStatus != EMBER_SUCCESS) {
        return;
      }
      secureEntry = ((entry.options & EMBER_AF_GP_PROXY_TABLE_ENTRY_OPTIONS_SECURITY_USE)
                     || (entry.securityOptions));
    }

    if (secureEntry) {
      return;
    }
  }

  if (status == EMBER_SUCCESS
      || status == EMBER_NO_SECURITY
      || (status == EMBER_UNPROCESSED && commissioningState.inCommissioningMode)
      || (status == EMBER_AUTH_FAILURE  && commissioningState.inCommissioningMode)) {
    // duplicate filter
    if (sli_zigbee_af_gp_message_checking(addr, sequenceNumber)) {
      if (commissioningState.inCommissioningMode) {
        if (autoCommissioning) {
          autoCommissioningCallback(GP_ARGS);
        }
        // If status is unprocessed and security is level 3, then gpdCommandId with its payload are encrypted
        // and can not be interpreated by proxy, hence forward it as a GP Commissioning Notification with security
        // processing failed bit set, so that sink can process the commissioning notification.
        if ((status == EMBER_UNPROCESSED || status == EMBER_AUTH_FAILURE)
            && gpdfSecurityLevel == EMBER_GP_SECURITY_LEVEL_FC_MIC_ENCRYPTED) {
          status = EMBER_AUTH_FAILURE;
          commissioningGpdfCallback(GP_ARGS);
          return;
        }
        // Proceed with command processing based on gpdCommandId
        switch (gpdCommandId) {
          case EMBER_ZCL_GP_GPDF_COMMISSIONING:
          case EMBER_ZCL_GP_GPDF_DECOMMISSIONING:
          case EMBER_ZCL_GP_GPDF_SUCCESS:
            commissioningGpdfCallback(GP_ARGS);
            break;
          case EMBER_ZCL_GP_GPDF_CHANNEL_REQUEST:
            channelRequestGpdfCallback(GP_ARGS);
            break;

          default:
            if (status == EMBER_NO_SECURITY
                && ((gpdCommandId >= MIN_RESERVED_GPD_COMMAND_ID
                     && gpdCommandId <= MAX_RESERVED_GPD_COMMAND_ID)
                    || (gpdCommandId >= EMBER_ZCL_GP_GPDF_MFR_DEF_GPD_CMD0
                        && gpdCommandId <= EMBER_ZCL_GP_GPDF_MFR_DEF_GPD_CMD_F))) {
              commissioningGpdfCallback(GP_ARGS);
            } else if (status == EMBER_UNPROCESSED) {
              status = EMBER_AUTH_FAILURE;
              commissioningGpdfCallback(GP_ARGS);
            } else {
              gpdfForwardCallback(GP_ARGS);
            }
            break;
        }
      } else {
        //outside of commissioning mode, everything gets forwarded, including commissioning related messages
        // But not success messages (See A3.9.1)
        if (gpdCommandId == EMBER_ZCL_GP_GPDF_SUCCESS
            && !commissioningState.inCommissioningMode) {
          // Drop a success message
        } else {
          gpdfForwardCallback(GP_ARGS);
        }
      }
    }
  }
}

void emberAfPluginGreenPowerClientClearProxyTable(void)
{
#ifndef EZSP_HOST
  sli_zigbee_gp_clear_proxy_table();
#else
  EmberGpProxyTableEntry entry;
  uint8_t entryIndex;
  for (entryIndex = 0; entryIndex < EMBER_GP_PROXY_TABLE_SIZE; entryIndex++) {
    if (emberGpProxyTableGetEntry(entryIndex, &entry) != EMBER_SUCCESS) {
      return;
    }
    uint8_t allZeroesIeeeAddress[17];
    if (entry.status == EMBER_GP_PROXY_TABLE_ENTRY_STATUS_ACTIVE) {
      emberGpProxyTableProcessGpPairing(EMBER_AF_GP_PAIRING_OPTION_REMOVE_GPD,
                                        &(entry.gpd),
                                        0,// commMode,
                                        EMBER_NULL_NODE_ID,
                                        0,// sinkGroupId,
                                        EMBER_NULL_NODE_ID,// assignedAlias,
                                        allZeroesIeeeAddress,//sinkIeeeAddress,
                                        (EmberKeyData *) allZeroesIeeeAddress,// EmberKeyData* gpdKey,
                                        0,// gpdSecurityFrameCounter,
                                        0); // forwardingRadius)
    }
  }
#endif
}

void sli_zigbee_af_green_power_client_d_gp_sent_callback(EmberStatus status, uint8_t gpepHandle)
{
  emberAfGreenPowerClusterPrintln("emberDGpSentHandler Status = %x", status);
  if (status == EMBER_SUCCESS
      && (commissioningState.channelStatus & GP_CLIENT_ON_TRANSMIT_CHANNEL_MASK)) {
    // Here, the sent event is for channel configuration delivery.
    // Clear the 5 sec timer that started while submitted a packet to TxQueue - call handler
    channelEventHandler(&channelEvent);
  }
}

void sli_zigbee_af_green_power_client_stack_status_callback(EmberStatus status)
{
  if (status == EMBER_NETWORK_DOWN
      && emberStackIsPerformingRejoin() == FALSE) {
    // Clear proxy table when leaving the network.
    emberAfPluginGreenPowerClientClearProxyTable();
  }
}

uint32_t emberAfGreenPowerClusterClientCommandParse(sl_service_opcode_t opcode,
                                                    sl_service_function_context_t *context)
{
  (void)opcode;

  EmberAfClusterCommand *cmd = (EmberAfClusterCommand *)context->data;
  bool wasHandled = false;

  if (!cmd->mfgSpecific) {
    switch (cmd->commandId) {
      case ZCL_GP_PAIRING_COMMAND_ID:
      {
        wasHandled = emberAfGreenPowerClusterGpPairingCallback(cmd);
        break;
      }
      case ZCL_GP_PROXY_COMMISSIONING_MODE_COMMAND_ID:
      {
        wasHandled = emberAfGreenPowerClusterGpProxyCommissioningModeCallback(cmd);
        break;
      }
      case ZCL_GP_RESPONSE_COMMAND_ID:
      {
        wasHandled = emberAfGreenPowerClusterGpResponseCallback(cmd);
        break;
      }
      case ZCL_GP_PROXY_TABLE_REQUEST_COMMAND_ID:
      {
        wasHandled = emberAfGreenPowerClusterGpProxyTableRequestCallback(cmd);
        break;
      }
    }
  }

  return ((wasHandled)
          ? EMBER_ZCL_STATUS_SUCCESS
          : EMBER_ZCL_STATUS_UNSUP_COMMAND);
}

WEAK(void emberAfGreenPowerClientGpdfSinkTableBasedForwardCallback(EmberGpAddress *addr,
                                                                   EmberGpSinkListEntry *sinkList,
                                                                   uint8_t maxNumberEntries))
{
}
