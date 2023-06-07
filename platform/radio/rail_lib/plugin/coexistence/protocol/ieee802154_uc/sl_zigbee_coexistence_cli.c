/***************************************************************************//**
 * @file
 * @brief sl_zigbee_coexistence_cli.c
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#include "sl_cli.h"
#include "sl_zigbee_debug_print.h"
#include "stack/include/ember-types.h"
#include "counters.h"

#ifdef EZSP_HOST
#include "app/util/ezsp/ezsp-protocol.h"
#include "app/util/ezsp/ezsp.h"
typedef uint32_t sl_rail_util_coex_options_t;
#define SL_RAIL_UTIL_COEX_OPT_DISABLED             0u
#ifdef RAIL_SIM_EZSP
#include "af_main.h"
#include "coexistence-hal.h"
#else //!RAIL_SIM_EZSP
#include "af.h"
#include "app/framework/util/af-main.h"
#endif //RAIL_SIM_EZSP
#else //!EZSP_HOST
#include "coexistence-802154.h"
#endif //EZSP_HOST

//-----------------------------------------------------------------------------
// Get PTA state (enabled/disabled)
// Console Command : "plugin coexistence get-pta-state"
// Console Response: "PTA is <ENABLED|DISABLED>"
void emberAfPluginCoexistenceGetPtaState(sl_cli_command_arg_t *arguments)
{
  (void)arguments;
  uint8_t ptaState = 0U;
#ifdef EZSP_HOST
  uint8_t valueLength = sizeof(ptaState);

  ezspGetValue(EZSP_VALUE_ENABLE_PTA, &valueLength, &ptaState);
#else //!EZSP_HOST
  ptaState = (uint8_t)sl_rail_util_coex_is_enabled();
#endif //EZSP_HOST
  sl_zigbee_app_debug_print("PTA is %s\n", ((ptaState != 0U) ? "ENABLED" : "DISABLED"));
}

//-----------------------------------------------------------------------------
// Set PTA state (disabled=0/enabled=1)
// Console Command : "plugin coexistence set-pta-state <0|1>"
// Console Response: "PTA is <ENABLED|DISABLED>"
void emberAfPluginCoexistenceSetPtaState(sl_cli_command_arg_t *arguments)
{
  uint8_t ptaState = sl_cli_get_argument_uint8(arguments, 0);
#ifdef EZSP_HOST
  uint8_t valueLength = sizeof(ptaState);

  emberAfSetEzspValue(EZSP_VALUE_ENABLE_PTA,
                      valueLength,
                      &ptaState,
                      "enable pta");
#else //!EZSP_HOST
  sl_rail_util_coex_set_enable((bool)ptaState);
#endif //EZSP_HOST
  emberAfPluginCoexistenceGetPtaState(arguments);
}

//-----------------------------------------------------------------------------
#define PTA_OPTION_FIELDS 16
#define PTA_OPTION_LINE_MAX 80

static const char * const ptaHelp[PTA_OPTION_FIELDS + 1] = {
  "Field                             Bit Position  Size(bits)  Value",
  "RX retry timeout ms              ",
  "Disable ACK if nGRANT||RHO||nREQ ",
  "Abort mid TX if grant is lost    ",
  "TX request is high priority      ",
  "RX request is high priority      ",
  "RX retry request is high priority",
  "RX retry request is enabled      ",
  "Radio holdoff is enabled         ",
  "Reserved                         ",
  "Disable REQ (force holdoff)      ",
  "Synch MAC to GRANT (MAC holdoff) ",
  "REQ/PRI Assert (PreSync/AddrDet) ",
  "CCA/GRANT TX PRI Escalation Thres",
  "Reserved                         ",
  "MAC Fail TX PRI Escalation Thresh",
  "Reserved                         "
};

static const uint8_t ptaBitShift[PTA_OPTION_FIELDS + 1] = { 0, 8, 9, 10, 11, 12, 13,
                                                            14, 15, 16, 17, 18, 20, 23, 25, 27, 32 };
static const uint32_t ptaBitMask[PTA_OPTION_FIELDS] = { 0xFF, 0x1, 0x1, 0x1, 0x1,
                                                        0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x3, 0x7, 0x3, 0x3, 0x1F };

//-----------------------------------------------------------------------------
// Get ptaOptions and print hex value to console
// Console Command : "plugin coexistence get-pta-options"
// Console Response: "PTA Configuration Option: 0x<ptaOptions>"
void emberAfPluginCoexistenceGetPtaOptions(sl_cli_command_arg_t *arguments)
{
  (void)arguments;
  uint8_t i;
  uint32_t value;
  uint32_t ptaOptions = 0U;
#ifdef EZSP_HOST
  uint8_t valueLength = sizeof(ptaOptions);

  ezspGetValue(EZSP_VALUE_PTA_OPTIONS,
               &valueLength,
               (uint8_t*)&ptaOptions);
#else //!EZSP_HOST
  ptaOptions = (uint32_t)sl_rail_util_coex_get_options();
#endif //EZSP_HOST

  sl_zigbee_app_debug_print("PTA Configuration Option: 0x%04x\n", ptaOptions);

  sl_zigbee_app_debug_print("%s\n", ptaHelp[0]);
  for (i = 0; i < PTA_OPTION_FIELDS; i++) {
    value = (ptaOptions >> ptaBitShift[i]) & ptaBitMask[i];
    sl_zigbee_app_debug_print("%s %02d            %d          %d\n",
                              ptaHelp[i + 1],
                              ptaBitShift[i],
                              (ptaBitShift[i + 1] - ptaBitShift[i]),
                              value);
  }
  sl_zigbee_app_debug_print("\n");
}

//-----------------------------------------------------------------------------
// Set ptaOptions from console
// Console Command : "plugin coexistence set-pta-options 0x<ptaOptions>"
// Console Response: "PTA Configuration Option: 0x<ptaOptions>"
void emberAfPluginCoexistenceSetPtaOptions(sl_cli_command_arg_t *arguments)
{
  uint32_t ptaOptions = sl_cli_get_argument_uint32(arguments, 0);

#ifdef EZSP_HOST
  uint8_t valueLength = sizeof(ptaOptions);

  emberAfSetEzspValue(EZSP_VALUE_PTA_OPTIONS,
                      valueLength,
                      (uint8_t*)&ptaOptions,
                      "pta options");
#else //!EZSP_HOST
  sl_status_t status = sl_rail_util_coex_set_options((sl_rail_util_coex_options_t)ptaOptions);
  if (status == SL_STATUS_INVALID_PARAMETER) {
    uint32_t constant_options = sl_rail_util_coex_get_constant_options();
    uint32_t current_options = sl_rail_util_coex_get_options();
    sl_zigbee_app_debug_print("Error: SL_STATUS_INVALID_PARAMETER\n");
    sl_zigbee_app_debug_print("Constant options: 0x%08x\n", constant_options);
    sl_zigbee_app_debug_print("Desired  options: 0x%08x\n", ptaOptions);
    sl_zigbee_app_debug_print("Invalid  options: 0x%08x\n", ((current_options & constant_options) ^ (ptaOptions & constant_options)));
  } else {
    sl_zigbee_app_debug_print("Status: 0x%x\n", status);
  }
#endif //EZSP_HOST
  emberAfPluginCoexistenceGetPtaOptions(arguments);
}

//-----------------------------------------------------------------------------
// Get PWM state from console
// Console Command : "plugin coexistence get-pta-state"
// Console Response: "PTA PWM (ENABLE|DISABLED): <period> (PERIOD in 0.5ms),
//                             <duty-cycle> (%DC), <0|1> (<LOW|HIGH> PRIORITY)"
void emberAfPluginCoexistenceGetPwmState(sl_cli_command_arg_t *arguments)
{
  (void)arguments;
  uint8_t pwmPeriodHalfMs;
  uint8_t pwmPulseDc;
  bool pwmPriority;
  uint8_t getPwmStateVariable[3];

#ifdef EZSP_HOST
  uint8_t valueLength = sizeof(getPwmStateVariable);

  ezspGetValue(EZSP_VALUE_PTA_PWM_OPTIONS,
               &valueLength,
               getPwmStateVariable);
#else //!EZSP_HOST
  const sl_rail_util_coex_pwm_args_t *pwm_args = sl_rail_util_coex_get_request_pwm_args();
  if (pwm_args == NULL) {
    getPwmStateVariable[0] = 0;
    getPwmStateVariable[1] = 0;
    getPwmStateVariable[2] = 0;
  } else {
    getPwmStateVariable[0] = (uint8_t)pwm_args->req;
    getPwmStateVariable[1] = pwm_args->dutyCycle;
    getPwmStateVariable[2] = pwm_args->periodHalfMs;
  }
#endif //EZSP_HOST

  switch (getPwmStateVariable[0]) {
    case 0x00:
      pwmPulseDc = 0;
      pwmPriority = false;
      break;

    case 0x80:
      pwmPulseDc = getPwmStateVariable[1];
      pwmPriority = false;
      break;

    case 0x82:
      pwmPulseDc = getPwmStateVariable[1];
      pwmPriority = true;
      break;

    default:
      sl_zigbee_app_debug_print("Invalid PWM state variable: %u\n", getPwmStateVariable[0]);
      return;
  }
  pwmPeriodHalfMs = getPwmStateVariable[2];

  sl_zigbee_app_debug_print("PTA PWM (%s): %u (PERIOD in 0.5ms), %u (%%DC), %u (%s PRIORITY)\n",
                            ((pwmPulseDc > 0u) ? "ENABLED" : "DISABLED"),
                            pwmPeriodHalfMs,
                            pwmPulseDc,
                            pwmPriority,
                            (pwmPriority ? "HIGH" : "LOW"));
}

//------------------------------------------------------------------------------
// Set PWM state from console
// Console Command : "plugin coexistence set-pta-state <periodHalfms>
//                                              <duty-cycle %> <priority, 0|1>"
// Console Response: "PTA PWM (ENABLE|DISABLED): <period> (PERIOD in 0.5ms),
//                             <duty-cycle> (%DC), <0|1> (<LOW|HIGH> PRIORITY)"
void emberAfPluginCoexistenceSetPwmState(sl_cli_command_arg_t *arguments)
{
  uint8_t pwmPeriodHalfMs = sl_cli_get_argument_uint8(arguments, 0);
  uint8_t pwmPulseDc = sl_cli_get_argument_uint8(arguments, 1);
  uint8_t pwmPriority = (bool)sl_cli_get_argument_uint8(arguments, 2);
  uint8_t pwmComposite = (pwmPulseDc > 0u) ? (pwmPriority ? 0x82 : 0x80) : 0x00;

#ifdef EZSP_HOST
  uint8_t setPwmStateVariable[3];
  uint8_t valueLength = sizeof(setPwmStateVariable);

  setPwmStateVariable[0] = pwmComposite;
  setPwmStateVariable[1] = pwmPulseDc;
  setPwmStateVariable[2] = pwmPeriodHalfMs;

  emberAfSetEzspValue(EZSP_VALUE_PTA_PWM_OPTIONS,
                      valueLength,
                      setPwmStateVariable,
                      "configure PWM options");
#else //!EZSP_HOST
  sl_rail_util_coex_set_request_pwm(pwmComposite,
                                    0,
                                    pwmPulseDc,
                                    pwmPeriodHalfMs);
#endif //EZSP_HOST
  emberAfPluginCoexistenceGetPwmState(arguments);
}

//------------------------------------------------------------------------------
// Get Directional PRIORITY state from console
// Console Command : "plugin coexistence get-dp-state"
// Console Response: "Directional PRIORITY: <ENABLED|DISABLED>, <pulseWidth>(us)"
void emberAfPluginCoexistenceGetDpState(sl_cli_command_arg_t *arguments)
{
// if Directional PRIORITY compiled in:
// 1. Enabled = pulse-width!=0, Disabled = pulse-width==0
// 2. Pulse-width is adjustable in us resolution (1-255)
  (void)arguments;
#ifdef EZSP_HOST
  uint8_t dpPulse = 0U;
  uint8_t valueLength = sizeof(dpPulse);
  EzspStatus status;

  status = ezspGetValue(EZSP_VALUE_PTA_DIRECTIONAL_PRIORITY_PULSE_WIDTH,
                        &valueLength,
                        &dpPulse);
  if (status == EZSP_SUCCESS) {
    sl_zigbee_app_debug_print("Directional PRIORITY: %s, %u (us)\n",
                              (dpPulse > 0u) ? "ENABLED" : "DISABLED",
                              dpPulse);
  } else {
    sl_zigbee_app_debug_print("Error code: %x\n", status);
    sl_zigbee_app_debug_print("Error getting Directional PRIORITY information from NCP!\n");
  }

#elif SL_RAIL_UTIL_COEX_DP_ENABLED
  uint8_t dpPulse = sl_rail_util_coex_get_directional_priority_pulse_width();

  sl_zigbee_app_debug_print("Directional PRIORITY: %s, %u (us)\n",
                            (dpPulse > 0u) ? "ENABLED" : "DISABLED",
                            dpPulse);
#else //!SL_RAIL_UTIL_COEX_DP_ENABLED
  sl_zigbee_app_debug_print("Directional PRIORITY not included in build!\n");
#endif //SL_RAIL_UTIL_COEX_DP_ENABLED
}

//------------------------------------------------------------------------------
// Set PWM state from console
// Console Command : "plugin coexistence set-dp-state <pulseWidth>"
// Console Response: "Directional PRIORITY: <ENABLED|DISABLED>, <pulseWidth>(us)"
void emberAfPluginCoexistenceSetDpState(sl_cli_command_arg_t *arguments)
{
// if Directional PRIORITY compiled in:
// 1. Enabled = pulse-width!=0, Disabled = pulse-width==0
// 2. Pulse-width is adjustable in us resolution (1-255)
  uint8_t dpPulse = sl_cli_get_argument_uint8(arguments, 0);
  (void)dpPulse;
#ifdef EZSP_HOST
  uint8_t valueLength = sizeof(dpPulse);

  EzspStatus status;

  status = emberAfSetEzspValue(EZSP_VALUE_PTA_DIRECTIONAL_PRIORITY_PULSE_WIDTH,
                               valueLength,
                               &dpPulse,
                               "configure Directional Priority pulse width");

  if (status != EZSP_SUCCESS) {
    sl_zigbee_app_debug_print("Error code: %x\n", status);
    sl_zigbee_app_debug_print("Error getting Directional PRIORITY information from NCP!\n");
  }
#elif SL_RAIL_UTIL_COEX_DP_ENABLED
  sl_rail_util_coex_set_directional_priority_pulse_width(dpPulse);
#else //!SL_RAIL_UTIL_COEX_DP_ENABLED
  sl_zigbee_app_debug_print("Directional PRIORITY not included in build!\n");
#endif //SL_RAIL_UTIL_COEX_DP_ENABLED
  emberAfPluginCoexistenceGetDpState(arguments);
}

//------------------------------------------------------------------------------
// clear all counters
void emberAfPluginCoexistenceClearCounters(sl_cli_command_arg_t *arguments)
{
  (void)arguments;
  sl_zigbee_app_debug_print("Clearing counters\n");
  emberAfPluginCountersClear();
}

//------------------------------------------------------------------------------
// Get PHY select state from console
// Console Command : "plugin coexistence get-phy-state"
// Console Response: "PHY Select: <ENABLED|DISABLED>, <timeout> (ms)"
void emberAfPluginCoexistenceGetPhyState(sl_cli_command_arg_t *arguments)
{
// Set PHY select timeout in milliseconds
// case 1. timeoutMs == 0 -> disable COEX optimized PHY
// case 2. 0 < timeoutMs < PTA_PHY_SELECT_TIMEOUT_MAX -> disable COEX optimized PHY
//   if there is no WiFi activity for timeoutMs
// case 3. timeoutMs == PTA_PHY_SELECT_TIMEOUT_MAX -> enable COEX optimize PHY
  (void)arguments;
#ifdef EZSP_HOST
  uint8_t timeout = 0U;
  uint8_t valueLength = sizeof(timeout);
  EzspStatus status;

  status = ezspGetValue(EZSP_VALUE_PTA_PHY_SELECT_TIMEOUT,
                        &valueLength,
                        &timeout);
  if (status == EZSP_SUCCESS) {
    sl_zigbee_app_debug_print("PHY Select: %s, %u (ms)\n",
                              (timeout > 0u) ? "ENABLED" : "DISABLED",
                              timeout);
  } else {
    sl_zigbee_app_debug_print("Error code: %x\n", status);
    sl_zigbee_app_debug_print("Error getting PHY Select information from NCP!\n");
  }
#elif SL_RAIL_UTIL_COEX_RUNTIME_PHY_SELECT
  uint8_t timeout = sl_rail_util_coex_get_phy_select_timeout();

  sl_zigbee_app_debug_print("PHY Select: %s, %u (ms)\n",
                            (timeout > 0u) ? "ENABLED" : "DISABLED",
                            timeout);
#else //!SL_RAIL_UTIL_COEX_RUNTIME_PHY_SELECT
  sl_zigbee_app_debug_print("PHY Select not included in build!\n");
#endif //SL_RAIL_UTIL_COEX_RUNTIME_PHY_SELECT
}

//------------------------------------------------------------------------------
// Set PHY select timeout from console
// Console Command : "plugin coexistence set-phy-state <timeout>"
// Console Response: none
void emberAfPluginCoexistenceSetPhyState(sl_cli_command_arg_t *arguments)
{
// Set PHY select timeout in milliseconds
// case 1. timeoutMs == 0 -> disable COEX optimized PHY
// case 2. 0 < timeoutMs < PTA_PHY_SELECT_TIMEOUT_MAX -> disable COEX optimized PHY
//   if there is no WiFi activity for timeoutMs
// case 3. timeoutMs == PTA_PHY_SELECT_TIMEOUT_MAX -> enable COEX optimize PHY
  uint8_t timeout = sl_cli_get_argument_uint8(arguments, 0);
#ifdef EZSP_HOST
  uint8_t valueLength = sizeof(timeout);

  EzspStatus status;

  status = emberAfSetEzspValue(EZSP_VALUE_PTA_PHY_SELECT_TIMEOUT,
                               valueLength,
                               &timeout,
                               "configure PHY select timeout");

  if (status != EZSP_SUCCESS) {
    sl_zigbee_app_debug_print("Error code: %x\n", status);
    sl_zigbee_app_debug_print("Error getting PHY Select information from NCP!\n");
  }
#elif SL_RAIL_UTIL_COEX_RUNTIME_PHY_SELECT
  sl_rail_util_coex_set_phy_select_timeout(timeout);
  emberAfPluginCoexistenceGetPhyState(arguments);
#else //!SL_RAIL_UTIL_COEX_RUNTIME_PHY_SELECT
  (void)timeout;
  sl_zigbee_app_debug_print("PHY Select not included in build!\n");
#endif //SL_RAIL_UTIL_COEX_RUNTIME_PHY_SELECT
}

#if !EZSP_HOST && SL_RAIL_UTIL_COEX_OVERRIDE_GPIO_INPUT
static const char * const gpioNames[] = {
  "PTA_GPIO_INDEX_RHO",
  "PTA_GPIO_INDEX_REQ",
  "PTA_GPIO_INDEX_GNT",
  "PTA_GPIO_INDEX_PHY_SELECT",
  "PTA_GPIO_INDEX_WIFI_TX",
  "PTA_GPIO_INDEX_INTERNAL_REQ",
  "PTA_GPIO_INDEX_INTERNAL_PWM_REQ"
};
#endif //!EZSP_HOST && SL_RAIL_UTIL_COEX_OVERRIDE_GPIO_INPUT

//------------------------------------------------------------------------------
// Get GPIO Input override from console
// Console Command : "plugin coexistence get-phy-state"
// Console Response: "<GPIO NAME> GPIO: <ENABLED|DISABLED>"
void emberAfPluginCoexistenceGetGpioInputOverride(sl_cli_command_arg_t *arguments)
{
#if !defined(EZSP_HOST) && SL_RAIL_UTIL_COEX_OVERRIDE_GPIO_INPUT
  sl_rail_util_coex_gpio_index_t gpioIndex = (sl_rail_util_coex_gpio_index_t)sl_cli_get_argument_uint8(arguments, 0);
  if (gpioIndex < (COEX_GPIO_INDEX_COUNT - 1)) {
    bool enabled = sl_rail_util_coex_get_gpio_input_override(gpioIndex);
    sl_zigbee_app_debug_print("%s GPIO: %s\n",
                              gpioNames[gpioIndex],
                              enabled ? "ENABLED" : "DISABLED");
  } else {
    sl_zigbee_app_debug_print("COEX GPIO index out of bounds!\n");
  }
#else //!SL_RAIL_UTIL_COEX_OVERRIDE_GPIO_INPUT
  (void)arguments;
  sl_zigbee_app_debug_print("COEX GPIO input override not included in build!\n");
#endif //SL_RAIL_UTIL_COEX_OVERRIDE_GPIO_INPUT
}

//------------------------------------------------------------------------------
// Set GPIO Input override from console
// Console Command : "plugin coexistence set-gpio-input <gpioIndex>"
// Console Response: none
void emberAfPluginCoexistenceSetGpioInputOverride(sl_cli_command_arg_t *arguments)
{
  // Set PTA GPIO input override by gpioIndex
#if !defined(EZSP_HOST) && SL_RAIL_UTIL_COEX_OVERRIDE_GPIO_INPUT
  sl_rail_util_coex_gpio_index_t gpioIndex = (sl_rail_util_coex_gpio_index_t)sl_cli_get_argument_uint8(arguments, 0);
  if (gpioIndex < (COEX_GPIO_INDEX_COUNT - 1)) {
    bool enabled = (bool)sl_cli_get_argument_uint8(arguments, 1);
    sl_rail_util_coex_set_gpio_input_override(gpioIndex, enabled);
    emberAfPluginCoexistenceGetGpioInputOverride(arguments);
  } else {
    sl_zigbee_app_debug_print("COEX GPIO index out of bounds!\n");
  }
#else //!SL_RAIL_UTIL_COEX_OVERRIDE_GPIO_INPUT
  (void)arguments;
  sl_zigbee_app_debug_print("COEX GPIO input override not included in build!\n");
#endif //SL_RAIL_UTIL_COEX_OVERRIDE_GPIO_INPUT
}

//------------------------------------------------------------------------------
extern const char * titleStrings[];

//------------------------------------------------------------------------------
static void printCounter(uint8_t id)
{
  sl_zigbee_app_debug_print("%s: %u\n", titleStrings[id], emberCounters[id]);
}

//------------------------------------------------------------------------------
// Print all counters specific to coex
void emberAfPluginCoexistencePrintCounters(sl_cli_command_arg_t *arguments)
{
  (void)arguments;
  #ifdef EZSP_HOST
  ezspReadCounters(emberCounters);
  #endif //EZSP_HOST
  sl_zigbee_app_debug_print("COUNTERS\n");
  printCounter(EMBER_COUNTER_PTA_LO_PRI_REQUESTED);
  printCounter(EMBER_COUNTER_PTA_HI_PRI_REQUESTED);
  printCounter(EMBER_COUNTER_PTA_LO_PRI_DENIED);
  printCounter(EMBER_COUNTER_PTA_HI_PRI_DENIED);
  printCounter(EMBER_COUNTER_PTA_LO_PRI_TX_ABORTED);
  printCounter(EMBER_COUNTER_PTA_HI_PRI_TX_ABORTED);
}
