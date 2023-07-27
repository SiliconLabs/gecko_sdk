/***************************************************************************//**
 * @file
 * @brief A sample of custom EZSP protocol.
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
#ifdef UC_BUILD
#include "sl_component_catalog.h"
#endif // UC_BUILD
#include "app/framework/include/af.h"

#ifdef SL_CATALOG_ZIGBEE_GREEN_POWER_CLIENT_CLI_PRESENT
// Green Power Client CLIs
WEAK(void emberAfPluginGreenPowerClientSetProxyEntry(SL_CLI_COMMAND_ARG))
{
}

WEAK(void emberAfPluginGreenPowerClientAddSink(SL_CLI_COMMAND_ARG))
{
}

WEAK(void emberAfPluginGreenPowerClientAddGroupcastSink(SL_CLI_COMMAND_ARG))
{
}

WEAK(void emberAfPluginGreenPowerClientRemoveProxyTableEntry(SL_CLI_COMMAND_ARG))
{
}

WEAK(void emberAfPluginGreenPowerClientDuplicateFilteringTest(SL_CLI_COMMAND_ARG))
{
}

WEAK(void emberAfPluginGreenPowerClientSetKey(SL_CLI_COMMAND_ARG))
{
}

WEAK(void emberAfPluginGreenPowerClientPrintProxyTable(SL_CLI_COMMAND_ARG))
{
#ifdef SL_CATALOG_ZIGBEE_AF_SUPPORT_PRESENT
  uint16_t proxyTableSize = 0;
  ezspGetConfigurationValue(EZSP_CONFIG_GP_PROXY_TABLE_SIZE, &proxyTableSize);
  uint8_t i, j;

  emberAfGreenPowerClusterPrint("Proxy Table:\n");
  for (i = 0; i < proxyTableSize; i++) {
    EmberGpProxyTableEntry entry = { 0 };
    if (ezspGpProxyTableGetEntry(i, &entry) != EMBER_SUCCESS) {
      return;
    }
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
#endif // SL_CATALOG_ZIGBEE_AF_SUPPORT_PRESENT
}

WEAK(void emberAfPluginGreenPowerClientClearProxyTable(void))
{
#ifdef SL_CATALOG_ZIGBEE_AF_SUPPORT_PRESENT
  uint16_t proxyTableSize = 0;
  ezspGetConfigurationValue(EZSP_CONFIG_GP_PROXY_TABLE_SIZE, &proxyTableSize);

  uint8_t entryIndex;
  for (entryIndex = 0; entryIndex < proxyTableSize; entryIndex++) {
    EmberGpProxyTableEntry entry = { 0 };
    if (ezspGpProxyTableGetEntry(entryIndex, &entry) != EMBER_SUCCESS) {
      return;
    }
    uint8_t allZeroesIeeeAddress[17];
    if (entry.status == EMBER_GP_PROXY_TABLE_ENTRY_STATUS_ACTIVE) {
      ezspGpProxyTableProcessGpPairing(EMBER_AF_GP_PAIRING_OPTION_REMOVE_GPD,
                                       &(entry.gpd),
                                       0, // commMode,
                                       EMBER_NULL_NODE_ID,
                                       0, // sinkGroupId,
                                       EMBER_NULL_NODE_ID, // assignedAlias,
                                       allZeroesIeeeAddress, //sinkIeeeAddress,
                                       (EmberKeyData *) allZeroesIeeeAddress, // EmberKeyData* gpdKey,
                                       0, // gpdSecurityFrameCounter,
                                       0);  // forwardingRadius)
    }
  }
#endif // SL_CATALOG_ZIGBEE_AF_SUPPORT_PRESENT
}

#endif //SL_CATALOG_ZIGBEE_GREEN_POWER_CLIENT_CLI_PRESENT

#ifdef SL_CATALOG_ZIGBEE_GREEN_POWER_SERVER_CLI_PRESENT
// Green Power Server CLIs

// Sink Commissioning Window Extend
WEAK(void emberAfGreenPowerClusterGpSinkCliCommissioningWindowExtend(SL_CLI_COMMAND_ARG))
{
}

WEAK(void emberAfPluginGreenPowerServerCommissioningMode(SL_CLI_COMMAND_ARG))
{
#ifdef SL_CATALOG_ZIGBEE_AF_SUPPORT_PRESENT
  uint8_t options = sl_cli_get_argument_uint8(arguments, 0);
  uint16_t gpmAddressSecurity = sl_cli_get_argument_uint16(arguments, 1);
  uint16_t gpmAddressPairing = sl_cli_get_argument_uint16(arguments, 2);
  uint8_t endpoint = sl_cli_get_argument_uint8(arguments, 3);
  EmberStatus status = ezspGpSinkCommission(options,
                                            gpmAddressSecurity,
                                            gpmAddressPairing,
                                            endpoint);
  emberAfCorePrintln("\n\rSink Commissioning Enter %s",
                     (status == EMBER_SUCCESS) ? "success" : "error");
#endif // SL_CATALOG_ZIGBEE_AF_SUPPORT_PRESENT
}

// Sink Table Print
WEAK(void emberAfPluginGreenPowerServerCliSinkTablePrint(SL_CLI_COMMAND_ARG))
{
#ifdef SL_CATALOG_ZIGBEE_AF_SUPPORT_PRESENT
  uint16_t sinkTableSize = 0;
  ezspGetConfigurationValue(EZSP_CONFIG_GP_SINK_TABLE_SIZE, &sinkTableSize);
  bool tableEmpty = true;
  emberAfCorePrintln("\n\rSink Table Size: %d", sinkTableSize);
  for (uint8_t index = 0; index < sinkTableSize; index++) {
    EmberGpSinkTableEntry entry = { 0 };
    EmberStatus status = ezspGpSinkTableGetEntry(index, &entry);
    if (status == EMBER_SUCCESS
        && entry.status == EMBER_GP_SINK_TABLE_ENTRY_STATUS_ACTIVE) {
      tableEmpty = false;
      emberAfCorePrintln("%x %2x %x %4x %x %x %2x %x %x %4x",
                         entry.status,
                         entry.options,
                         entry.gpd.applicationId,
                         entry.gpd.id.sourceId,
                         entry.gpd.endpoint,
                         entry.deviceId,
                         entry.assignedAlias,
                         entry.groupcastRadius,
                         entry.securityOptions,
                         entry.gpdSecurityFrameCounter);
    }
  }
  if (tableEmpty) {
    emberAfCorePrintln("\n\rSink Table Empty");
  }
#endif // SL_CATALOG_ZIGBEE_AF_SUPPORT_PRESENT
}

WEAK(void emberAfPluginGreenPowerServerCliClearSinkTable(SL_CLI_COMMAND_ARG))
{
#ifdef SL_CATALOG_ZIGBEE_AF_SUPPORT_PRESENT
  ezspGpSinkTableClearAll();
#endif // SL_CATALOG_ZIGBEE_AF_SUPPORT_PRESENT
}

WEAK(void emberAfPluginGreenPowerServerCliRunTestVectors(SL_CLI_COMMAND_ARG))
{
  // A test to run the security test vectors upon reset
  EmberStatus status = ezspGpSecurityTestVectors();
  if (status == EMBER_SUCCESS) {
    emberAfGreenPowerClusterPrintln("~~ gp-test-vectors PASS ~~");
  } else if (status == EMBER_LIBRARY_NOT_PRESENT) {
    emberAfGreenPowerClusterPrintln("Command is not supported");
  } else {
    emberAfGreenPowerClusterPrintln("~~ gp-test-vectors FAIL ~~");
  }
}
#endif //SL_CATALOG_ZIGBEE_GREEN_POWER_SERVER_CLI_PRESENT

#ifdef SL_CATALOG_ZIGBEE_GREEN_POWER_TRANSLATION_TABLE_CLI_PRESENT
// Green Power Translation Table CLIs

WEAK(void sli_zigbee_gp_print_additional_info_block(uint8_t gpdCommand, uint8_t addInfoOffset))
{
}

WEAK(void emberAfPluginGreenPowerServerCliClearAdditionalInfoBlockTable(SL_CLI_COMMAND_ARG))
{
}

WEAK(void emberAfPluginGreenPowerServerCliClearCustomizedTable(SL_CLI_COMMAND_ARG))
{
}

WEAK(void emberAfPluginGreenPowerServerCliClearAdditionalInfoBlockTableEntry(SL_CLI_COMMAND_ARG))
{
}

WEAK(void emberAfPluginGreenPowerServerCliClearCustomizedTableEntry(SL_CLI_COMMAND_ARG))
{
}

WEAK(void emberAfPluginGreenPowerServerCliClearTranslationTableEntry(SL_CLI_COMMAND_ARG))
{
}

WEAK(void emberAfPluginGreenPowerServerCliSetAdditionalInfoBlockTableEntry(SL_CLI_COMMAND_ARG))
{
}

WEAK(void emberAfPluginGreenPowerServerCliSetCustomizedTableEntry(SL_CLI_COMMAND_ARG))
{
}

WEAK(void emberAfPluginGreenPowerServerCliSetTranslationTable(SL_CLI_COMMAND_ARG))
{
}

WEAK(void emberAfPluginGreenPowerServerCliAdditionalInfoBlockTablePrint(SL_CLI_COMMAND_ARG))
{
}

WEAK(void emberAfPluginGreenPowerServerCliCustomizedTablePrint(SL_CLI_COMMAND_ARG))
{
}

WEAK(void emberAfPluginGreenPowerServerCliTranslationTablePrint(SL_CLI_COMMAND_ARG))
{
}

WEAK(void emberAfPluginGreenPowerServerCliRemoveGpdEndpoint(SL_CLI_COMMAND_ARG))
{
}

WEAK(void emberAfPluginGreenPowerServerCliClearTranslationTranslationTable(SL_CLI_COMMAND_ARG))
{
#ifdef SL_CATALOG_ZIGBEE_AF_SUPPORT_PRESENT
  ezspGpTranslationTableClear();
#endif // SL_CATALOG_ZIGBEE_AF_SUPPORT_PRESENT
}
#endif //SL_CATALOG_ZIGBEE_GREEN_POWER_TRANSLATION_TABLE_CLI_PRESENT
