/***************************************************************************//**
 * @file
 * @brief CLI for the Reporting plugin.
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
#include "app/util/serial/sl_zigbee_command_interpreter.h"
#include "app/framework/util/attribute-storage.h"
#include "reporting.h"

#include "app/util/serial/sl_zigbee_command_interpreter.h"

// plugin reporting print
void sli_zigbee_af_reporting_cli_print(sl_cli_command_arg_t *arguments)
{
  uint16_t i;
  for (i = 0; i < sli_zigbee_af_reporting_num_entries(); i++) {
    EmberAfPluginReportingEntry entry;
    sli_zigbee_af_reporting_get_entry(i, &entry);
    emberAfReportingPrint("%x:", i);
    if (entry.endpoint != EMBER_AF_PLUGIN_REPORTING_UNUSED_ENDPOINT_ID) {
      emberAfReportingPrint("ep %x clus %2x attr %2x svr %c",
                            entry.endpoint,
                            entry.clusterId,
                            entry.attributeId,
                            (entry.mask == CLUSTER_MASK_SERVER ? 'y' : 'n'));
      if (entry.manufacturerCode != EMBER_AF_NULL_MANUFACTURER_CODE) {
        emberAfReportingPrint(" mfg %x", entry.manufacturerCode);
      }
      if (entry.direction == EMBER_ZCL_REPORTING_DIRECTION_REPORTED) {
        emberAfReportingPrint(" report min %2x max %2x rpt-chg %4x",
                              entry.data.reported.minInterval,
                              entry.data.reported.maxInterval,
                              entry.data.reported.reportableChange);
        emberAfReportingFlush();
      } else {
        emberAfReportingPrint(" receive from %2x ep %x timeout %2x",
                              entry.data.received.source,
                              entry.data.received.endpoint,
                              entry.data.received.timeout);
      }
    }
    emberAfReportingPrintln("");
    emberAfReportingFlush();
    // EMZIGBEE-5125: apps with lot's of endpoints/reporting table configs will
    // watchdog when printing
    halResetWatchdog();
  }
}

// plugin reporting clear
void sli_zigbee_af_reporting_cli_clear(sl_cli_command_arg_t *arguments)
{
  EmberStatus status = emberAfClearReportTableCallback();
  emberAfReportingPrintln("%p 0x%x", "clear", status);
}

// plugin reporting remove <index:1>
void sli_zigbee_af_reporting_cli_remove(sl_cli_command_arg_t *arguments)
{
  EmberStatus status = sli_zigbee_af_reporting_remove_entry(sl_cli_get_argument_uint16(arguments, 0));
  emberAfReportingPrintln("%p 0x%x", "remove", status);
}

// plugin reporting add <endpoint:1> <cluster id:2> <attribute id:2> ...
// ... <mask:1> <min interval:2> <max interval:2> <reportable change:4>
void sli_zigbee_af_reporting_cli_add(sl_cli_command_arg_t *arguments)
{
  EmberAfStatus status = EMBER_ZCL_STATUS_SUCCESS;
  EmberAfPluginReportingEntry entry = {
    .endpoint = (int8u)sl_cli_get_argument_uint8(arguments, 0),
    .clusterId = (EmberAfClusterId)sl_cli_get_argument_uint16(arguments, 1),
    .attributeId = (EmberAfAttributeId)sl_cli_get_argument_uint16(arguments, 2),
    .mask = (int8u)(sl_cli_get_argument_uint8(arguments, 3) == 0
                    ? CLUSTER_MASK_CLIENT
                    : CLUSTER_MASK_SERVER),
    .manufacturerCode = EMBER_AF_NULL_MANUFACTURER_CODE,
    .data.reported.minInterval = (int16u)sl_cli_get_argument_uint16(arguments, 4),
    .data.reported.maxInterval = (int16u)sl_cli_get_argument_uint16(arguments, 5),
    .data.reported.reportableChange = (int32u)sl_cli_get_argument_uint32(arguments, 6),
    .direction = EMBER_ZCL_REPORTING_DIRECTION_REPORTED,
  };
  UNUSED_VAR(status);
  status = emberAfPluginReportingConfigureReportedAttribute(&entry);

  emberAfReportingPrintln("%p 0x%x", "add", status);
}

// plugin reporting add clear-last-report-time
void sli_zigbee_af_reporting_cli_clear_last_report_time(sl_cli_command_arg_t *arguments)
{
  uint16_t i;
  for (i = 0; i < REPORT_TABLE_SIZE; i++) {
    sli_zigbee_af_report_volatile_data[i].lastReportTimeMs = halCommonGetInt32uMillisecondTick();
  }
  emberAfReportingPrintln("clearing last report time of all attributes");
}

void emberAfPluginReportingInitCallback(uint8_t init_level);

static uint16_t rawTableScan(uint16_t numEntries)
{
  uint16_t i, acc;
  EmberAfPluginReportingEntry entry;
  acc = 0;
  for (i = 0; i < numEntries; i++) {
    sli_zigbee_af_reporting_get_entry(i, &entry);
    acc++;
  }
  return acc;
}

// plugin reporting test-timing
void sli_zigbee_af_reporting_cli_test_timing(sl_cli_command_arg_t *arguments)
{
  uint32_t before, after;
  emberAfReportingPrintln("testing timing of various reporting operations");
  emberAfReportingPrintln("-----------------------------------------------");

  emberAfReportingPrintln("--table reads - full table--");
  before = halCommonGetInt32uMillisecondTick();
  rawTableScan(REPORT_TABLE_SIZE);
  after = halCommonGetInt32uMillisecondTick();
  emberAfReportingPrintln("result = %d ms", after - before);

  emberAfReportingPrintln("--init / schedule tick---");
  before = halCommonGetInt32uMillisecondTick();
  emberAfPluginReportingInitCallback(SL_ZIGBEE_INIT_LEVEL_LOCAL_DATA);
  after = halCommonGetInt32uMillisecondTick();
  emberAfReportingPrintln("result = %d ms", after - before);

  emberAfReportingPrintln("--load configuration defaults--");
  before = halCommonGetInt32uMillisecondTick();
  emberAfPluginReportingLoadReportingConfigDefaults();
  after = halCommonGetInt32uMillisecondTick();
  emberAfReportingPrintln("result = %d ms", after - before);
}
