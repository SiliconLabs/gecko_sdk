/***************************************************************************//**
 * @file
 * @brief CLI for the Green Power Server plugin.
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
#include "green-power-server.h"
#include "green-power-common.h"

bool sli_zigbee_af_green_power_server_gp_sink_commissioning_mode_command_handler(uint8_t options,
                                                                                 uint16_t gpmAddrForSecurity,
                                                                                 uint16_t gpmAddrForPairing,
                                                                                 uint8_t sinkEndpoint);

// Sink Commissioning Mode Enter
void emberAfPluginGreenPowerServerCommissioningMode(SL_CLI_COMMAND_ARG)
{
  uint8_t options = sl_cli_get_argument_uint8(arguments, 0);
  uint16_t gpmAddressSecurity = sl_cli_get_argument_uint16(arguments, 1);
  uint16_t gpmAddressPairing = sl_cli_get_argument_uint16(arguments, 2);
  uint8_t endpoint = sl_cli_get_argument_uint8(arguments, 3);
  sli_zigbee_af_green_power_server_gp_sink_commissioning_mode_command_handler(options,
                                                                              gpmAddressSecurity,
                                                                              gpmAddressPairing,
                                                                              endpoint);
}

// Sink Commissioning Window Extend
void emberAfGreenPowerClusterGpSinkCliCommissioningWindowExtend(SL_CLI_COMMAND_ARG)
{
  uint16_t commissioningWindow = sl_cli_get_argument_uint16(arguments, 0);
  emberAfGreenPowerClusterGpSinkCommissioningWindowExtend(commissioningWindow);
}

void emberAfPluginGreenPowerServerCliClearSinkTable(SL_CLI_COMMAND_ARG)
{
  emberGpSinkTableClearAll();
}

void emberAfPluginGreenPowerServerCliSinkTablePrint(SL_CLI_COMMAND_ARG)
{
  bool tableEmpty = true;
  emberAfCorePrintln("\n\rSt Optn Ap SourceId Ep Dv Alis Gr So FrameCtr");
  for (uint8_t index = 0; index < EMBER_GP_SINK_TABLE_SIZE; index++) {
    EmberGpSinkTableEntry entry = { 0 };
    EmberStatus status = emberGpSinkTableGetEntry(index, &entry);
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
}

void emberAfPluginGreenPowerServerCliRunTestVectors(SL_CLI_COMMAND_ARG)
{
#if (EMBER_AF_PLUGIN_GREEN_POWER_SERVER_SECURITY_TEST_VECTORS == 1)
  // A test to run the security test vectors upon reset
  EmberStatus status = sli_zigbee_af_gp_test_security();
  if (status == EMBER_SUCCESS) {
    emberAfGreenPowerClusterPrintln("~~ gp-test-vectors PASS ~~");
  } else {
    emberAfGreenPowerClusterPrintln("~~ gp-test-vectors FAIL ~~");
  }
#else // (EMBER_AF_PLUGIN_GREEN_POWER_SERVER_SECURITY_TEST_VECTORS == 0)
  emberAfCorePrintln("Command is not supported");
#endif // (EMBER_AF_PLUGIN_GREEN_POWER_SERVER_SECURITY_TEST_VECTORS == 1)
}
