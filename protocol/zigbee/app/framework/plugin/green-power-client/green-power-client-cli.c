/***************************************************************************//**
 * @file
 * @brief CLI for the Green Power Client plugin.
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
#else // !SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
#include "green-power-adapter.h"
#endif //SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT

#include "stack/gp/gp-proxy-table.h"
#include "green-power-client.h"
#include "app/framework/plugin/green-power-common/green-power-common.h"
#include "app/util/serial/sl_zigbee_command_interpreter.h"

#ifndef EMBER_AF_GENERATE_CLI
#error The Green Power Client plugin is not compatible with the legacy CLI.
#endif

void emberAfPluginGreenPowerClientSetProxyEntry(SL_CLI_COMMAND_ARG)
{
#ifndef EZSP_HOST
  uint8_t index = sl_cli_get_argument_uint8(arguments, 0);
  uint32_t srcID = sl_cli_get_argument_uint32(arguments, 1);
  uint16_t sinkNodeID = sl_cli_get_argument_uint16(arguments, 2);
  EmberGpProxyTableEntry entry;

  entry.gpd.applicationId = 0;
  entry.gpd.id.sourceId = srcID;
  entry.options = sl_cli_get_argument_uint32(arguments, 3);
  entry.status = EMBER_GP_PROXY_TABLE_ENTRY_STATUS_ACTIVE;
  entry.securityOptions = 0;
  entry.sinkList[0].type = EMBER_GP_SINK_TYPE_LW_UNICAST;
  entry.sinkList[1].type = EMBER_GP_SINK_TYPE_UNUSED;
  entry.sinkList[0].target.unicast.sinkNodeId = sinkNodeID;
  entry.sinkList[0].target.unicast.sinkEUI[0] = 0x84;
  entry.sinkList[0].target.unicast.sinkEUI[1] = 0x40;
  entry.sinkList[0].target.unicast.sinkEUI[2] = 0x18;
  entry.sinkList[0].target.unicast.sinkEUI[3] = 0x00;
  entry.sinkList[0].target.unicast.sinkEUI[4] = 0x00;
  entry.sinkList[0].target.unicast.sinkEUI[5] = 0x00;
  entry.sinkList[0].target.unicast.sinkEUI[6] = 0x00;
  entry.sinkList[0].target.unicast.sinkEUI[7] = 0x00;
  entry.gpdSecurityFrameCounter = 0x00;

  sli_zigbee_af_gp_proxy_table_set_entry(index, &entry);
#endif
}

void emberAfPluginGreenPowerClientAddSink(SL_CLI_COMMAND_ARG)
{
#ifndef EZSP_HOST
  EmberGpAddress addr;
  uint32_t srcID = sl_cli_get_argument_uint32(arguments, 0);
  EmberEUI64 eui64;
  sl_zigbee_copy_eui64_arg(arguments, 1, eui64, true);
  addr.applicationId = 0;
  addr.id.sourceId = srcID;

  uint8_t index = sli_zigbee_af_gp_proxy_table_find_or_allocate_entry(&addr);
  if (index != 0xFF) {
    sli_zigbee_af_gp_proxy_table_add_sink(index,
                                          EMBER_GP_SINK_TYPE_LW_UNICAST,
                                          eui64,
                                          EMBER_UNKNOWN_NODE_ID,
                                          0,
                                          0xFFFF);
  }
#endif
}
void emberAfPluginGreenPowerClientAddGroupcastSink(SL_CLI_COMMAND_ARG)
{
#ifndef EZSP_HOST
  EmberGpAddress addr;
  uint32_t srcID = sl_cli_get_argument_uint32(arguments, 0);
  uint16_t groupID = sl_cli_get_argument_uint16(arguments, 1);
  addr.applicationId = 0;
  addr.id.sourceId = srcID;

  uint8_t index = sli_zigbee_af_gp_proxy_table_find_or_allocate_entry(&addr);
  if (index != 0xFF) {
    sli_zigbee_af_gp_proxy_table_add_sink(index,
                                          EMBER_GP_SINK_TYPE_GROUPCAST,
                                          0,
                                          EMBER_UNKNOWN_NODE_ID,
                                          groupID,
                                          0xFFFF);
  }
#endif
}

void emberAfPluginGreenPowerClientRemoveProxyTableEntry(SL_CLI_COMMAND_ARG)
{
#ifndef EZSP_HOST
  EmberGpAddress addr;
  uint32_t srcID = sl_cli_get_argument_uint32(arguments, 0);
  addr.applicationId = 0;
  addr.id.sourceId = srcID;
  sli_zigbee_af_gp_proxy_table_remove_entry(emberGpProxyTableLookup(&addr));
#endif
}

void emberAfPluginGreenPowerClientPrintProxyTable(SL_CLI_COMMAND_ARG)
{
#ifndef EZSP_HOST
  uint8_t i, j;
  uint8_t cleared = 0;
  emberAfGreenPowerClusterPrint("Proxy Table:\n");
  for (i = 0; i < sli_zigbee_gp_proxy_table_size; i++) {
    if (sli_zigbee_gp_proxy_table_entry_in_use(i)) {
      emberAfCorePrint("%d opt:%4x seco:%x srcID:%4x ", i, sli_zigbee_gp_proxy_table[i].options, sli_zigbee_gp_proxy_table[i].securityOptions, sli_zigbee_gp_proxy_table[i].gpd.id.sourceId);
      for (j = 0; j < 2; j++) {
        if (sli_zigbee_gp_proxy_table[i].sinkList[j].type == EMBER_GP_SINK_TYPE_UNUSED) {
          emberAfCorePrint("unused");
        } else if (sli_zigbee_gp_proxy_table[i].sinkList[j].type == EMBER_GP_SINK_TYPE_GROUPCAST) {
          emberAfCorePrint("GC %2x", sli_zigbee_gp_proxy_table[i].sinkList[j].target.groupcast.groupID);
        } else if (sli_zigbee_gp_proxy_table[i].sinkList[j].type == EMBER_GP_SINK_TYPE_LW_UNICAST) {
          emberAfCorePrint("LU:");
          emberAfPrintBigEndianEui64(sli_zigbee_gp_proxy_table[i].sinkList[j].target.unicast.sinkEUI);
        }
        emberAfCorePrint(" ");
      }
      emberAfCorePrint(" ");
      for (j = 0; j < EMBER_ENCRYPTION_KEY_SIZE; j++) {
        emberAfCorePrint("%x", sli_zigbee_gp_proxy_table[i].gpdKey.contents[j]);
      }
      emberAfCorePrint(" ");
      emberAfCorePrint("%x", sli_zigbee_gp_proxy_table[i].gpdSecurityFrameCounter);
      emberAfCorePrint("\n");
    } else {
      cleared++;
    }
  }
  if (cleared == sli_zigbee_gp_proxy_table_size) {
    emberAfCorePrintln("No Proxy Entries");
  }
#else

  EmberGpProxyTableEntry entry;
  uint8_t i, j;
  emberAfGreenPowerClusterPrint("Proxy Table:\n");
  for (i = 0; i < 5; i++) { //TODO: set the size properly
    emberGpProxyTableGetEntry(i, &entry);
    if (entry.status == EMBER_GP_PROXY_TABLE_ENTRY_STATUS_ACTIVE) {
      emberAfCorePrint("%d opt:%4x seco:%x srcID:%4x ", i, entry.options, entry.securityOptions, entry.gpd.id.sourceId);
      for (j = 0; j < 2; j++) {
        if (entry.sinkList[j].type == EMBER_GP_SINK_TYPE_UNUSED) {
          emberAfCorePrint("unused");
        } else if (entry.sinkList[j].type == EMBER_GP_SINK_TYPE_GROUPCAST) {
          emberAfCorePrint("GC %2x", entry.sinkList[j].target.groupcast.groupID);
        } else if (entry.sinkList[j].type == EMBER_GP_SINK_TYPE_LW_UNICAST) {
          emberAfCorePrint("LU:");
          emberAfPrintBigEndianEui64(entry.sinkList[j].target.unicast.sinkEUI);
        }
        emberAfCorePrint(" ");
      }
      emberAfCorePrint(" ");
      for (j = 0; j < EMBER_ENCRYPTION_KEY_SIZE; j++) {
        emberAfCorePrint("%x", entry.gpdKey.contents[j]);
      }
      emberAfCorePrint(" ");
      emberAfCorePrint("%x", entry.gpdSecurityFrameCounter);
      emberAfCorePrint("\n");
    }
  }

#endif
}

void emberAfPluginGreenPowerClientDuplicateFilteringTest(SL_CLI_COMMAND_ARG)
{
#ifndef EZSP_HOST
  EmberGpAddress sender;
  sender.endpoint = sl_cli_get_argument_uint8(arguments, 0);
  sender.applicationId = EMBER_GP_APPLICATION_SOURCE_ID;
  sender.id.sourceId = sl_cli_get_argument_uint32(arguments, 1);
  sli_zigbee_af_gp_message_checking(&sender, sl_cli_get_argument_uint8(arguments, 2));
  //sli_zigbee_af_green_power_find_duplicate_mac_seq_num(&sender, (uint8_t)emberUnsignedCommandArgument(2));
#endif
}

void emberAfPluginGreenPowerClientSetKey(SL_CLI_COMMAND_ARG)
{
#ifndef EZSP_HOST
  uint8_t index;
  EmberKeyData keyData;
  index = sl_cli_get_argument_uint8(arguments, 0);
  sl_zigbee_copy_hex_arg(arguments,                  \
                         1,                          \
                         emberKeyContents(&keyData), \
                         EMBER_ENCRYPTION_KEY_SIZE,  \
                         true);
  sli_zigbee_af_gp_proxy_table_set_key(index, (keyData.contents), 0 /*key type TODO*/);
#endif
}

void emberAfPluginGreenPowerClientSpoofDevAnnce(SL_CLI_COMMAND_ARG)
{
  uint16_t nodeId = sl_cli_get_argument_uint16(arguments, 0);
  EmberEUI64 eui64;

  sl_zigbee_copy_eui64_arg(arguments, 1, eui64, true);
  uint8_t capabilities = sl_cli_get_argument_uint8(arguments, 2);
  sli_zigbee_af_gp_spoof_device_annce(nodeId,
                                      eui64,
                                      capabilities);
}
