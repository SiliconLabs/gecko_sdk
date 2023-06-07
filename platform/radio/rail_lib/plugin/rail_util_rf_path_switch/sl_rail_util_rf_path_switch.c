/***************************************************************************//**
 * @file sl_rail_util_rf_path_switch.c
 * @brief
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "sl_rail_util_rf_path_switch.h"
#include "em_assert.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_prs.h"

#ifdef SL_RAIL_UTIL_RF_PATH_SWITCH_PRESENT
#ifdef _SILICON_LABS_32B_SERIES_2
static uint32_t get_free_prs_channel(const uint32_t start)
{
  for (uint32_t i = start; i < PRS_ASYNC_CHAN_COUNT; ++i) {
#if defined(_PRS_ASYNC_CH_CTRL_SOURCESEL_MASK)
    PRS_Signal_t signal = (PRS_Signal_t) (PRS->ASYNC_CH[i].CTRL
                                          & (_PRS_ASYNC_CH_CTRL_SOURCESEL_MASK | _PRS_ASYNC_CH_CTRL_SIGSEL_MASK));
#else
    PRS_Signal_t signal = (PRS_Signal_t) (PRS->CH[i].CTRL
                                          & (_PRS_CH_CTRL_SOURCESEL_MASK | _PRS_CH_CTRL_SIGSEL_MASK));
#endif
    if (signal == prsSignalNone) {
      return i;
    }
  }
  return PRS_ASYNC_CHAN_COUNT;
}

static uint32_t route_prs_output_to_switch(const GPIO_Port_TypeDef port,
                                           const uint32_t pin,
                                           const PRS_Signal_t signal)
{
  const uint32_t start = port >= gpioPortC ? 6U : 0U;
  const uint32_t channel = get_free_prs_channel(start);
  if (channel < PRS_ASYNC_CHAN_COUNT) {
    GPIO_PinModeSet(port, pin, gpioModePushPull, 0U);
    PRS_ConnectSignal(channel, prsTypeAsync, signal);
    PRS_PinOutput(channel, prsTypeAsync, port, pin);
  } else {
    EFM_ASSERT(0);
  }
  return channel;
}
#endif // _SILICON_LABS_32B_SERIES_2
#endif // SL_RAIL_UTIL_RF_PATH_SWITCH_PRESENT

void sl_rail_util_rf_path_switch_init(void)
{
#ifdef SL_RAIL_UTIL_RF_PATH_SWITCH_PRESENT
#ifdef _SILICON_LABS_32B_SERIES_2
  CMU_ClockEnable(cmuClock_GPIO, true);
  CMU_ClockEnable(cmuClock_PRS, true);

#ifdef SL_RAIL_UTIL_RF_PATH_SWITCH_RADIO_ACTIVE_PORT
  const uint32_t powerChannel = route_prs_output_to_switch(
    SL_RAIL_UTIL_RF_PATH_SWITCH_RADIO_ACTIVE_PORT,
    SL_RAIL_UTIL_RF_PATH_SWITCH_RADIO_ACTIVE_PIN,
    prsSignalRACL_ACTIVE);
#else // !SL_RAIL_UTIL_RF_PATH_SWITCH_RADIO_ACTIVE_PORT
#if SL_RAIL_UTIL_RF_PATH_SWITCH_RADIO_ACTIVE_MODE == SL_RAIL_UTIL_RF_PATH_SWITCH_RADIO_ACTIVE_COMBINE
  const uint32_t powerChannel = get_free_prs_channel(0U);
  if (powerChannel < PRS_ASYNC_CHAN_COUNT) {
    PRS_ConnectSignal(powerChannel, prsTypeAsync, prsSignalRACL_ACTIVE);
  } else {
    EFM_ASSERT(0);
  }
#endif // SL_RAIL_UTIL_RF_PATH_SWITCH_RADIO_ACTIVE_MODE == SL_RAIL_UTIL_RF_PATH_SWITCH_RADIO_ACTIVE_COMBINE
#endif // SL_RAIL_UTIL_RF_PATH_SWITCH_RADIO_ACTIVE_PORT

#ifdef SL_RAIL_UTIL_RF_PATH_SWITCH_CONTROL_PORT
  const uint32_t ctrlChannel = route_prs_output_to_switch(
    SL_RAIL_UTIL_RF_PATH_SWITCH_CONTROL_PORT,
    SL_RAIL_UTIL_RF_PATH_SWITCH_CONTROL_PIN,
    prsSignalSYNTH_MUX0);
  (void)ctrlChannel;
#if SL_RAIL_UTIL_RF_PATH_SWITCH_RADIO_ACTIVE_MODE == SL_RAIL_UTIL_RF_PATH_SWITCH_RADIO_ACTIVE_COMBINE
  PRS_Combine(ctrlChannel, powerChannel, prsLogic_A_AND_B);
#endif // SL_RAIL_UTIL_RF_PATH_SWITCH_RADIO_ACTIVE_MODE == SL_RAIL_UTIL_RF_PATH_SWITCH_RADIO_ACTIVE_COMBINE
#endif // SL_RAIL_UTIL_RF_PATH_SWITCH_CONTROL_PORT

#ifdef SL_RAIL_UTIL_RF_PATH_SWITCH_INVERTED_CONTROL_PORT
  const uint32_t invertedCtrlChannel = route_prs_output_to_switch(
    SL_RAIL_UTIL_RF_PATH_SWITCH_INVERTED_CONTROL_PORT,
    SL_RAIL_UTIL_RF_PATH_SWITCH_INVERTED_CONTROL_PIN,
    prsSignalSYNTH_MUX0);
#if SL_RAIL_UTIL_RF_PATH_SWITCH_RADIO_ACTIVE_MODE == SL_RAIL_UTIL_RF_PATH_SWITCH_RADIO_ACTIVE_COMBINE
  PRS_Combine(invertedCtrlChannel, powerChannel, prsLogic_NOT_A_AND_B);
#else // SL_RAIL_UTIL_RF_PATH_SWITCH_RADIO_ACTIVE_MODE != SL_RAIL_UTIL_RF_PATH_SWITCH_RADIO_ACTIVE_COMBINE
  PRS_Combine(invertedCtrlChannel, invertedCtrlChannel, prsLogic_NOT_A);
#endif // SL_RAIL_UTIL_RF_PATH_SWITCH_RADIO_ACTIVE_MODE == SL_RAIL_UTIL_RF_PATH_SWITCH_RADIO_ACTIVE_COMBINE
#endif // SL_RAIL_UTIL_RF_PATH_SWITCH_INVERTED_CONTROL_PORT

#endif // _SILICON_LABS_32B_SERIES_2
#endif // SL_RAIL_UTIL_RF_PATH_SWITCH_PRESENT
}
