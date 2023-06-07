/***************************************************************************//**
 * @file
 * @brief Routines for the ZLL Commissioning Network plugin.
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
#include "app/util/common/form-and-join.h"
#include "app/framework/plugin/zll-commissioning-common/zll-commissioning.h"

#include "zigbee_stack_callback_dispatcher.h"
#include "zll-commissioning-network-config.h"

#define WAITING_BIT 0x80

enum {
  ZLL_NETWORK_INITIAL= 0x00,
  UNUSED_PRIMARY     = 0x01,
  JOINABLE_PRIMARY   = 0x02,
  JOINABLE_SECONDARY = 0x03,
  WAITING_PRIMARY    = WAITING_BIT | JOINABLE_PRIMARY,
  WAITING_SECONDARY  = WAITING_BIT | JOINABLE_SECONDARY,
};
static uint8_t state = ZLL_NETWORK_INITIAL;
sl_zigbee_event_t emberAfPluginZllCommissioningNetworkNetworkEvent;
#define zllCommissioningNetworkEventControl (&emberAfPluginZllCommissioningNetworkNetworkEvent)
void emberAfPluginZllCommissioningNetworkNetworkEventHandler(sl_zigbee_event_t * event);
uint8_t extendedPanId[EXTENDED_PAN_ID_SIZE] = EMBER_AF_PLUGIN_ZLL_COMMISSIONING_NETWORK_EXTENDED_PAN_ID;

// The exponent of the number of scan periods, where a scan period is 960
// symbols, and a symbol is 16 miscroseconds.  The scan will occur for
// ((2^duration) + 1) scan periods.  The ZLL specification requires routers to
// scan for joinable networks using a duration of 4.
#define SCAN_DURATION 4

// Private ZLL commissioning functions
EmberNodeType sli_zigbee_af_zll_get_logical_node_type(void);
EmberStatus sli_zigbee_af_zll_form_network(uint8_t channel, int8_t power, EmberPanId panId);

void sli_zigbee_af_zll_commissioning_network_init_callback(uint8_t init_level)
{
  (void)init_level;

  sl_zigbee_event_init(&emberAfPluginZllCommissioningNetworkNetworkEvent,
                       emberAfPluginZllCommissioningNetworkNetworkEventHandler);
}
//------------------------------------------------------------------------------

EmberStatus emberAfZllScanForJoinableNetwork(void)
{
  EmberStatus status = EMBER_INVALID_CALL;
  if (state == ZLL_NETWORK_INITIAL) {
    // TODO: The scan duration is hardcoded to 3 for the joinable part of the
    // form and join library, but ZLL specifies the duration should be 4.
    status = emberScanForJoinableNetwork(emberGetZllPrimaryChannelMask(),
                                         extendedPanId);
    if (status == EMBER_SUCCESS) {
      state = JOINABLE_PRIMARY;
    } else {
      emberAfAppPrintln("Error: %s: 0x%X",
                        "could not scan for joinable network",
                        status);
    }
  }
  return status;
}

EmberStatus emberAfZllScanForUnusedPanId(void)
{
  EmberStatus status = EMBER_INVALID_CALL;
  if (state == ZLL_NETWORK_INITIAL) {
    status = emberScanForUnusedPanId(emberGetZllPrimaryChannelMask(),
                                     SCAN_DURATION);
    if (status == EMBER_SUCCESS) {
      state = UNUSED_PRIMARY;
    } else {
      emberAfAppPrintln("Error: %s: 0x%x",
                        "could not scan for unused network",
                        status);
    }
  }
  return status;
}

void emberAfJoinableNetworkFoundCallback(EmberZigbeeNetwork *networkFound,
                                         uint8_t lqi,
                                         int8_t rssi)
{
  EmberStatus status = EMBER_ERR_FATAL;
  if (emberAfPluginZllCommissioningNetworkJoinCallback(networkFound, lqi, rssi)) {
    EmberNetworkParameters parameters;
    MEMSET(&parameters, 0, sizeof(EmberNetworkParameters));
    MEMMOVE(parameters.extendedPanId,
            networkFound->extendedPanId,
            EXTENDED_PAN_ID_SIZE);
    parameters.panId = networkFound->panId;
    parameters.radioTxPower = EMBER_AF_PLUGIN_ZLL_COMMISSIONING_COMMON_RADIO_TX_POWER;
    parameters.radioChannel = networkFound->channel;

    emberAfZllSetInitialSecurityState();
    status = emberAfJoinNetwork(&parameters);
  }

  // Note: If the application wants to skip this network or if the join fails,
  // we cannot call emberScanForNextJoinableNetwork to continue the scan
  // because we would be recursing.  Instead, schedule an event to fire at the
  // next tick and restart from there.
  if (status != EMBER_SUCCESS) {
    emberAfAppPrintln("Error: %s: 0x%X", "could not join network", status);
    sl_zigbee_event_set_active(zllCommissioningNetworkEventControl);
  }
}

void emberAfPluginFormAndJoinNetworkFoundCallback(EmberZigbeeNetwork *networkFound,
                                                  uint8_t lqi,
                                                  int8_t rssi)
{
  emberAfJoinableNetworkFoundCallback(networkFound, lqi, rssi);
}

void sli_zigbee_af_zll_commissioning_network_unused_pan_id_found_callback(EmberPanId panId, uint8_t channel)
{
  EmberStatus status = sli_zigbee_af_zll_form_network(channel,
                                                      EMBER_AF_PLUGIN_ZLL_COMMISSIONING_COMMON_RADIO_TX_POWER,
                                                      panId);
  if (status != EMBER_SUCCESS) {
    emberAfAppPrintln("Error: %s: 0x%X", "could not form network", status);
    sli_zigbee_af_zll_commissioning_network_scan_error_callback(status);
  }
}

void emberAfPluginFormAndJoinUnusedPanIdFoundCallback(EmberPanId panId, uint8_t channel)
{
  sli_zigbee_af_zll_commissioning_network_unused_pan_id_found_callback(panId, channel);
}

void sli_zigbee_af_zll_commissioning_network_scan_error_callback(EmberStatus status)
{
#ifdef SCAN_SECONDARY_CHANNELS
  if (status == EMBER_NO_BEACONS
      && state == JOINABLE_PRIMARY
      && emberGetZllSecondaryChannelMask() != 0) {
    state = JOINABLE_SECONDARY;
    sl_zigbee_event_set_active(zllCommissioningNetworkEventControl);
    return;
  }
#endif
  emberAfAppPrintln("Error: %s: 0x%X",
                    (state == UNUSED_PRIMARY
                     ? "could not find unused network"
                     : "could not find joinable network"),
                    status);
  state = ZLL_NETWORK_INITIAL;
}

void emberAfGetFormAndJoinExtendedPanIdCallback(uint8_t *resultLocation)
{
  MEMMOVE(resultLocation, extendedPanId, EXTENDED_PAN_ID_SIZE);
}

void emberAfSetFormAndJoinExtendedPanIdCallback(const uint8_t *extPanId)
{
  // Note, this function will also be used by the 'network extpanid' CLI command.
  MEMMOVE(extendedPanId, extPanId, EXTENDED_PAN_ID_SIZE);
}

void emberAfPluginZllCommissioningNetworkNetworkEventHandler(sl_zigbee_event_t * event)
{
  EmberStatus status = EMBER_ERR_FATAL;
  sl_zigbee_event_set_inactive(zllCommissioningNetworkEventControl);
  if ((state == JOINABLE_PRIMARY || state == JOINABLE_SECONDARY)
      && emberFormAndJoinCanContinueJoinableNetworkScan()) {
    status = emberScanForNextJoinableNetwork();
    if (status != EMBER_SUCCESS) {
      emberAfAppPrintln("Error: %s: 0x%X",
                        "could not continue scan for joinable network",
                        status);
    }
#ifdef SCAN_SECONDARY_CHANNELS
  } else if (state == JOINABLE_SECONDARY) {
    // TODO: The scan duration is hardcoded to 3 for the joinable part of the
    // form and join library, but ZLL specifies the duration should be 4.
    status = emberScanForJoinableNetwork(emberGetZllSecondaryChannelMask(),
                                         extendedPanId);
    if (status != EMBER_SUCCESS) {
      emberAfAppPrintln("Error: %s: 0x%X",
                        "could not scan for joinable network",
                        status);
    }
#endif
  }

  if (status != EMBER_SUCCESS) {
    state = ZLL_NETWORK_INITIAL;
    emberFormAndJoinCleanup(EMBER_SUCCESS);
  }
}

void sli_zigbee_af_zll_commissioning_network_stack_status_callback(EmberStatus status)
{
  uint8_t delayMinutes = MAX_INT8U_VALUE;

  if (status == EMBER_NETWORK_UP) {
    if (state == UNUSED_PRIMARY) {
      delayMinutes = 0;
    } else if (state == JOINABLE_PRIMARY || state == JOINABLE_SECONDARY) {
      // The ZLL state is now updated in emberAfPluginZllCommissioningCommonStackStatusCallback():
      // this callback just takes care of the network module state.
      state |= WAITING_BIT; // JOINABLE_XXX to WAITING_XXX
      delayMinutes = EMBER_AF_PLUGIN_ZLL_COMMISSIONING_NETWORK_JOINABLE_SCAN_TIMEOUT_MINUTES;
    }
  } else if (JOINABLE_PRIMARY <= state) {
    state &= ~WAITING_BIT; // JOINABLE_XXX or WAITING_XXX to JOINABLE_XXX
    delayMinutes = 0;
  }

  if (delayMinutes == 0) {
    emberAfPluginZllCommissioningNetworkNetworkEventHandler(zllCommissioningNetworkEventControl);
  } else if (delayMinutes != MAX_INT8U_VALUE) {
    sl_zigbee_event_set_delay_minutes(zllCommissioningNetworkEventControl,
                                      delayMinutes);
  }
}
