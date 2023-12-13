/***************************************************************************//**
 * @file
 * @brief User interface for delayd join.
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "app/framework/util/util.h"
#include "app/framework/plugin/delayed-join/delayed-join.h"

#include "app/framework/util/af-main.h"
#include "stack/include/trust-center.h"

// *****************************************************************************
// Functions
void sli_zigbee_af_delayed_join_activate_command(sl_cli_command_arg_t *arguments)
{
  #if defined(EZSP_HOST)
  EzspStatus status = emberAfSetEzspPolicy(EZSP_TRUST_CENTER_POLICY,
                                           (EZSP_DECISION_ALLOW_JOINS
                                            | EZSP_DECISION_ALLOW_UNSECURED_REJOINS
                                            | EZSP_DECISION_DEFER_JOINS),
                                           "Trust Center Policy",
                                           "Delayed joins");

  if (EZSP_SUCCESS != status) {
    emberAfCorePrintln("%s: %s: 0x%02X",
                       EMBER_AF_PLUGIN_DELAYED_JOIN_PLUGIN_NAME,
                       "failed to configure delayed joining",
                       status);
    return;
  }
  #endif // EZSP_HOST
  emberAfPluginDelayedJoinActivate(true);
}

void sli_zigbee_af_delayed_join_send_network_key_command(sl_cli_command_arg_t *arguments)
{
  EmberNodeId targetShort = sl_cli_get_argument_uint16(arguments, 0);
  EmberEUI64  targetLong;
  sl_zigbee_copy_eui64_arg(arguments, 1, targetLong, true);
  EmberNodeId parentShort = sl_cli_get_argument_uint16(arguments, 2);

  if (!emberAfPluginDelayedJoinIsActivated()) {
    emberAfCorePrintln("%s: %s ",
                       EMBER_AF_PLUGIN_DELAYED_JOIN_PLUGIN_NAME,
                       "Not activated");
    return;
  }

  if (EMBER_SUCCESS != emberUnicastCurrentNetworkKey(targetShort,
                                                     targetLong,
                                                     parentShort)) {
    emberAfCorePrintln("%s: %s 0x%02X",
                       EMBER_AF_PLUGIN_DELAYED_JOIN_PLUGIN_NAME,
                       "failed to send the encrypted network key to ",
                       targetShort);
  }
}

void sli_zigbee_af_delayed_join_set_network_key_timeout_command(sl_cli_command_arg_t *arguments)
{
  uint8_t seconds = sl_cli_get_argument_uint8(arguments, 0);
  if (seconds > EMBER_AF_PLUGIN_DELAYED_JOIN_MAXIMUM_TIMEOUT_SUPPORTED_S) {
    emberAfCorePrintln("%s: %s %3d",
                       EMBER_AF_PLUGIN_DELAYED_JOIN_PLUGIN_NAME,
                       "failed to set network key timeout that is greater than upper limit",
                       EMBER_AF_PLUGIN_DELAYED_JOIN_MAXIMUM_TIMEOUT_SUPPORTED_S);
  } else {
    emberAfPluginDelayedJoinSetNetworkKeyTimeout(seconds);
  }
}

void sli_zigbee_af_delayed_join_set_supported_timeout_command(sl_cli_command_arg_t *arguments)
{
  uint8_t seconds = sl_cli_get_argument_uint8(arguments, 0);
  if (seconds > EMBER_AF_PLUGIN_DELAYED_JOIN_MAXIMUM_TIMEOUT_SUPPORTED_S) {
    emberAfCorePrintln("%s: %s %3d",
                       EMBER_AF_PLUGIN_DELAYED_JOIN_PLUGIN_NAME,
                       "failed to set supported timeout that is greater than upper limit",
                       EMBER_AF_PLUGIN_DELAYED_JOIN_MAXIMUM_TIMEOUT_SUPPORTED_S);
  } else {
    if (sl_zigbee_set_transient_device_table_timeout_ms(seconds * MILLISECOND_TICKS_PER_SECOND) == SL_STATUS_OK) {
      emberAfCorePrintln("%s: %s %3d",
                         EMBER_AF_PLUGIN_DELAYED_JOIN_PLUGIN_NAME,
                         "Adjust TC timeout to",
                         seconds);
    } else {
      emberAfCorePrintln("%s: %s",
                         EMBER_AF_PLUGIN_DELAYED_JOIN_PLUGIN_NAME,
                         "failed to set supported timeout");
    }
  }
}
