/***************************************************************************//**
 * @file
 * @brief CLI for the GBCS Device Log plugin.
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
#include "app/framework/util/af-main.h"
#include "gbcs-device-log.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif
#include "gbcs-device-log-config.h"

// plugin gbcs-device-log clear
void sli_zigbee_af_gbcs_device_log_cli_clear(sl_cli_command_arg_t *arguments)
{
  emberAfPluginGbcsDeviceLogClear();
}

// plugin gbcs-device-log reset
void sli_zigbee_af_gbcs_device_log_cli_reset(sl_cli_command_arg_t *arguments)
{
  emberAfPluginGbcsDeviceLogReset();
}

// plugin gbcs-device-log count
void sli_zigbee_af_gbcs_device_log_cli_count(sl_cli_command_arg_t *arguments)
{
  uint8_t count = emberAfPluginGbcsDeviceLogCount();
  emberAfPluginGbcsDeviceLogPrintln("The GBCS Device Log currently has %d entries", count);
}

// plugin gbcs-device-log store <EUI64> <deviceType:1>
void sli_zigbee_af_gbcs_device_log_cli_store(sl_cli_command_arg_t *arguments)
{
  EmberEUI64 deviceId;
  EmberAfGBCSDeviceLogInfo deviceInfo;
  sl_zigbee_copy_eui64_arg(arguments, 0, deviceId, true);
  deviceInfo.deviceType = (EmberAfGBCSDeviceType)sl_cli_get_argument_uint8(arguments, 1);
  if (emberAfPluginGbcsDeviceLogStore(deviceId, &deviceInfo)) {
    emberAfPluginGbcsDeviceLogPrintln("Device has been successfully stored in the device log");
  }
}

// plugin gbcs-device-log remove <EUI64>
void sli_zigbee_af_gbcs_device_log_cli_remove(sl_cli_command_arg_t *arguments)
{
  EmberEUI64 deviceId;
  sl_zigbee_copy_eui64_arg(arguments, 0, deviceId, true);
  if (emberAfPluginGbcsDeviceLogRemove(deviceId)) {
    emberAfPluginGbcsDeviceLogPrintln("Device has been successfully removed from the device log");
  }
}

// plugin gbcs-device-log get <EUI64>
void sli_zigbee_af_gbcs_device_log_cli_get(sl_cli_command_arg_t *arguments)
{
  EmberEUI64 deviceId;
  EmberAfGBCSDeviceLogInfo deviceInfo;
  sl_zigbee_copy_eui64_arg(arguments, 0, deviceId, true);
  if (emberAfPluginGbcsDeviceLogGet(deviceId, &deviceInfo)) {
    emberAfPluginGbcsDeviceLogPrint("EUI64=");
    emberAfPluginGbcsDeviceLogDebugExec(emberAfPrintBigEndianEui64(deviceId));
    emberAfPluginGbcsDeviceLogPrintln(", type=%d", deviceInfo.deviceType);
  }
}

// plugin gbcs-device-log exists <EUI64> <deviceType:1>
void sli_zigbee_af_gbcs_device_log_cli_exists(sl_cli_command_arg_t *arguments)
{
  EmberEUI64 deviceId;
  EmberAfGBCSDeviceType deviceType = (EmberAfGBCSDeviceType)sl_cli_get_argument_uint8(arguments, 1);
  sl_zigbee_copy_eui64_arg(arguments, 0, deviceId, true);
  if (emberAfPluginGbcsDeviceLogExists(deviceId, deviceType)) {
    emberAfPluginGbcsDeviceLogPrintln("Device exists in the device log");
  } else {
    emberAfPluginGbcsDeviceLogPrintln("Device does not exist in the device log");
  }
}

// plugin gbcs-device-log print
void sli_zigbee_af_gbcs_device_log_cli_print(sl_cli_command_arg_t *arguments)
{
  emberAfPluginGbcsDeviceLogPrintEntries();
}

// plugin gbcs-device-log is-sleepy <deviceType:1>
void sli_zigbee_af_gbcs_device_log_cli_is_sleepy(sl_cli_command_arg_t *arguments)
{
  EmberAfGBCSDeviceType deviceType = (EmberAfGBCSDeviceType)sl_cli_get_argument_uint8(arguments, 0);
  if (emberAfPluginGbcsDeviceLogIsSleepyType(deviceType)) {
    emberAfPluginGbcsDeviceLogPrintln("Device type %d is a sleepy device type", deviceType);
  } else {
    emberAfPluginGbcsDeviceLogPrintln("Device type %d is not a sleepy device type", deviceType);
  }
}

// plugin gbcs-device-log fill
void sli_zigbee_af_gbcs_device_log_cli_fill(sl_cli_command_arg_t *arguments)
{
  uint8_t i;
  EmberEUI64 deviceId = { 0, 0, 0, 0, 0, 0, 0, 0 };
  EmberAfGBCSDeviceLogInfo deviceInfo;

  emberAfPluginGbcsDeviceLogClear();
  for (i = 0; i < EMBER_AF_PLUGIN_GBCS_DEVICE_LOG_DEVICE_LOG_SIZE; i++) {
    deviceId[7] = i + 1;
    deviceInfo.deviceType = EMBER_AF_GBCS_ESME_DEVICE_TYPE;
    emberAfPluginGbcsDeviceLogStore(deviceId, &deviceInfo);
  }
}
