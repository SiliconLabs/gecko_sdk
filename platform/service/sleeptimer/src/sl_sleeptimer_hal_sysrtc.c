/***************************************************************************//**
 * @file
 * @brief SLEEPTIMER hardware abstraction implementation for SYSRTC.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif
#include "peripheral_sysrtc.h"
#include "sl_sleeptimer.h"
#include "sli_sleeptimer_hal.h"
#include "em_core.h"
#include "em_cmu.h"

#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
#include "sl_power_manager.h"
#endif

#if defined(SL_CATALOG_POWER_MANAGER_PRESENT) || defined(SL_CATALOG_HFXO_MANAGER_PRESENT)
#if defined(_SILICON_LABS_32B_SERIES_2)
#include "em_prs.h"
#else
#include "sl_peripheral_prs.h"
#endif
#endif

#if SL_SLEEPTIMER_PERIPHERAL == SL_SLEEPTIMER_PERIPHERAL_SYSRTC

// Minimum difference between current count value and what the comparator of the timer can be set to.
// 1 tick is added to the minimum diff for the algorithm of compensation for the IRQ handler that
// triggers when CNT == compare_value + 1. For more details refer to sleeptimer_hal_set_compare() function's header.
#define SLEEPTIMER_COMPARE_MIN_DIFF  (2 + 1)

#define SLEEPTIMER_TMR_WIDTH (_SYSRTC_CNT_MASK)

static bool cc_disabled = true;

static bool cc1_disabled = true;

__STATIC_INLINE uint32_t get_time_diff(uint32_t a,
                                       uint32_t b);

/******************************************************************************
 * Initializes SYSRTC sleep timer.
 *****************************************************************************/
void sleeptimer_hal_init_timer(void)
{
  sl_hal_sysrtc_config_t sysrtc_config = SYSRTC_CONFIG_DEFAULT;
  sl_hal_sysrtc_group_config_t group_config = SYSRTC_GROUP_CONFIG_DEFAULT;

  CMU_ClockEnable(cmuClock_SYSRTC, true);

#if (SL_SLEEPTIMER_DEBUGRUN == 1)
  sysrtc_config.enable_debug_run = true;
#endif

  sl_hal_sysrtc_init(&sysrtc_config);

  group_config.compare_channel0_enable = false;

  sl_hal_sysrtc_init_group(0u, &group_config);

  sl_hal_sysrtc_disable_group_interrupts(0u, _SYSRTC_GRP0_IEN_MASK);
  sl_hal_sysrtc_clear_group_interrupts(0u, _SYSRTC_GRP0_IF_MASK);
  sl_hal_sysrtc_enable();
  sl_hal_sysrtc_set_counter(0u);

  NVIC_ClearPendingIRQ(SYSRTC_APP_IRQn);
  NVIC_EnableIRQ(SYSRTC_APP_IRQn);
}

/*******************************************************************************
 * Hardware Abstraction Layer to perform initialization related to Power Manager.
 ******************************************************************************/
#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
void sli_sleeptimer_hal_power_manager_integration_init(void)
{
  // Initialize PRS to start HFXO for early wakeup
  CMU_ClockEnable(cmuClock_PRS, true);

#if defined(_SILICON_LABS_32B_SERIES_2)
  PRS_ConnectSignal(1UL, prsTypeAsync, prsSignalSYSRTC0_GRP0OUT1);
  PRS_ConnectConsumer(1UL, prsTypeAsync, prsConsumerHFXO0_OSCREQ);
#else
  sl_hal_prs_async_connect_channel_producer(1UL, SL_HAL_PRS_ASYNC_SYSRTC0_GRP0OUT1);
  sl_hal_prs_connect_channel_consumer(1UL, SL_HAL_PRS_TYPE_ASYNC, SL_HAL_PRS_CONSUMER_HFXO0_OSCREQ);
#endif

  // Set SYSRTC Compare Channel 1
  SYSRTC0->GRP0_CTRL |= (_SYSRTC_GRP0_CTRL_CMP1CMOA_CMPIF << _SYSRTC_GRP0_CTRL_CMP1CMOA_SHIFT);
}
#endif

/*******************************************************************************
 * Hardware Abstraction Layer to perform initialization related to HFXO Manager.
 ******************************************************************************/
#if defined(SL_CATALOG_HFXO_MANAGER_PRESENT)
void sli_sleeptimer_hal_hfxo_manager_integration_init(void)
{
  // Set PRS signal from HFXO to SYSRTC capture channel
  CMU_ClockEnable(cmuClock_PRS, true);

#if defined(_SILICON_LABS_32B_SERIES_2)
  PRS_ConnectSignal(2UL, prsTypeAsync, prsSignalHFXO0L_STATUS1);
  PRS_ConnectConsumer(2UL, prsTypeAsync, prsConsumerSYSRTC0_SRC0);
#else
  sl_hal_prs_async_connect_channel_producer(2UL, SL_HAL_PRS_ASYNC_SYXO0L_STATUS1);
  sl_hal_prs_connect_channel_consumer(2UL, SL_HAL_PRS_TYPE_ASYNC, SL_HAL_PRS_CONSUMER_SYSRTC0_IN0);
#endif

  // Set SYSRTC Capture Channel
  SYSRTC0->GRP0_CTRL |= (_SYSRTC_GRP0_CTRL_CAP0EDGE_RISING << _SYSRTC_GRP0_CTRL_CAP0EDGE_SHIFT);
}
#endif

/******************************************************************************
 * Gets SYSRTC counter value.
 *****************************************************************************/
uint32_t sleeptimer_hal_get_counter(void)
{
  return sl_hal_sysrtc_get_counter();
}

/******************************************************************************
 * Gets SYSRTC channel zero's compare value.
 *****************************************************************************/
uint32_t sleeptimer_hal_get_compare(void)
{
  return sl_hal_sysrtc_get_group_compare_channel_value(0u, 0u);
}

/******************************************************************************
 * Sets SYSRTC channel zero's compare value.
 *
 * @note Compare match value is set to the requested value - 1. This is done
 * to compensate for the fact that the SYSRTC compare match interrupt always
 * triggers at the end of the requested ticks and that the IRQ handler is
 * executed when current tick count == compare_value + 1.
 *****************************************************************************/
void sleeptimer_hal_set_compare(uint32_t value)
{
  CORE_DECLARE_IRQ_STATE;
  uint32_t counter;
  uint32_t compare;
  uint32_t compare_value = value;

  CORE_ENTER_CRITICAL();
  counter = sleeptimer_hal_get_counter();
  compare = sleeptimer_hal_get_compare();

  if (((sl_hal_sysrtc_get_group_interrupts(0u) & SYSRTC_GRP0_IEN_CMP0) != 0)
      || get_time_diff(compare, counter) > SLEEPTIMER_COMPARE_MIN_DIFF
      || compare == counter) {
    // Add margin if necessary
    if (get_time_diff(compare_value, counter) < SLEEPTIMER_COMPARE_MIN_DIFF) {
      compare_value = counter + SLEEPTIMER_COMPARE_MIN_DIFF;
    }
    compare_value %= SLEEPTIMER_TMR_WIDTH;

    sl_hal_sysrtc_set_group_compare_channel_value(0u, 0u, compare_value - 1);
    sleeptimer_hal_enable_int(SLEEPTIMER_EVENT_COMP);
  }
  CORE_EXIT_CRITICAL();

  if (cc_disabled) {
    SYSRTC0->GRP0_CTRL |= SYSRTC_GRP0_CTRL_CMP0EN;
    cc_disabled = false;
  }
}

/*******************************************************************************
 * Sets SYSRTC channel one's compare value.
 *
 * @note Compare match value is set to the requested value - 1. This is done
 * to compensate for the fact that the SYSRTC compare match interrupt always
 * triggers at the end of the requested ticks and that the IRQ handler is
 * executed when current tick count == compare_value + 1.
 ******************************************************************************/
void sleeptimer_hal_set_compare_prs_hfxo_startup(int32_t value)
{
  CORE_DECLARE_IRQ_STATE;
  uint32_t counter;
  uint32_t compare_value;

  CORE_ENTER_CRITICAL();

  counter = sleeptimer_hal_get_counter();

  compare_value = value + counter;

  // Add margin if necessary
  if (get_time_diff(compare_value, counter) < SLEEPTIMER_COMPARE_MIN_DIFF) {
    compare_value = counter + SLEEPTIMER_COMPARE_MIN_DIFF;
  }

  compare_value %= SLEEPTIMER_TMR_WIDTH;

  sl_hal_sysrtc_set_group_compare_channel_value(0u, 1u, compare_value - 1);

  CORE_EXIT_CRITICAL();

  if (cc1_disabled) {
    SYSRTC0->GRP0_CTRL |= SYSRTC_GRP0_CTRL_CMP1EN;
    SYSRTC0->GRP0_CTRL |= SYSRTC_GRP0_CTRL_CAP0EN;
    cc1_disabled = false;
  }
}

/******************************************************************************
 * Enables SYSRTC interrupts.
 *****************************************************************************/
void sleeptimer_hal_enable_int(uint8_t local_flag)
{
  uint32_t sysrtc_ien = 0u;

  if (local_flag & SLEEPTIMER_EVENT_OF) {
    sysrtc_ien |= SYSRTC_GRP0_IEN_OVF;
  }

  if (local_flag & SLEEPTIMER_EVENT_COMP) {
    sysrtc_ien |= SYSRTC_GRP0_IEN_CMP0;
  }

  sl_hal_sysrtc_enable_group_interrupts(0u, sysrtc_ien);
}

/******************************************************************************
 * Disables SYSRTC interrupts.
 *****************************************************************************/
void sleeptimer_hal_disable_int(uint8_t local_flag)
{
  uint32_t sysrtc_int_dis = 0u;

  if (local_flag & SLEEPTIMER_EVENT_OF) {
    sysrtc_int_dis |= SYSRTC_GRP0_IEN_OVF;
  }

  if (local_flag & SLEEPTIMER_EVENT_COMP) {
    sysrtc_int_dis |= SYSRTC_GRP0_IEN_CMP0;

    cc_disabled = true;
    SYSRTC0->GRP0_CTRL &= ~_SYSRTC_GRP0_CTRL_CMP0EN_MASK;
  }

  sl_hal_sysrtc_disable_group_interrupts(0u, sysrtc_int_dis);
}

/*******************************************************************************
 * Hardware Abstraction Layer to set timer interrupts.
 ******************************************************************************/
void sleeptimer_hal_set_int(uint8_t local_flag)
{
  if (local_flag & SLEEPTIMER_EVENT_COMP) {
    SYSRTC0->GRP0_IF_SET = SYSRTC_GRP0_IF_CMP0;
  }
}

/******************************************************************************
 * Gets status of specified interrupt.
 *
 * Note: This function must be called with interrupts disabled.
 *****************************************************************************/
bool sli_sleeptimer_hal_is_int_status_set(uint8_t local_flag)
{
  bool int_is_set = false;
  uint32_t irq_flag = sl_hal_sysrtc_get_group_interrupts(0u);

  switch (local_flag) {
    case SLEEPTIMER_EVENT_COMP:
      int_is_set = ((irq_flag & SYSRTC_GRP0_IF_CMP0) == SYSRTC_GRP0_IF_CMP0);
      break;

    case SLEEPTIMER_EVENT_OF:
      int_is_set = ((irq_flag & SYSRTC_GRP0_IF_OVF) == SYSRTC_GRP0_IF_OVF);
      break;

    default:
      break;
  }

  return int_is_set;
}

/*******************************************************************************
 * SYSRTC interrupt handler.
 ******************************************************************************/
void SYSRTC_APP_IRQHandler(void)
{
  CORE_DECLARE_IRQ_STATE;
  uint8_t local_flag = 0;
  uint32_t irq_flag;

  CORE_ENTER_ATOMIC();
  irq_flag = sl_hal_sysrtc_get_group_interrupts(0u);

  if (irq_flag & SYSRTC_GRP0_IF_OVF) {
    local_flag |= SLEEPTIMER_EVENT_OF;
  }

  if (irq_flag & SYSRTC_GRP0_IF_CMP0) {
    local_flag |= SLEEPTIMER_EVENT_COMP;
  }
  sl_hal_sysrtc_clear_group_interrupts(0u, irq_flag & (SYSRTC_GRP0_IF_OVF | SYSRTC_GRP0_IF_CMP0));

  process_timer_irq(local_flag);

  CORE_EXIT_ATOMIC();
}

/*******************************************************************************
 * Gets SYSRTC timer frequency.
 ******************************************************************************/
uint32_t sleeptimer_hal_get_timer_frequency(void)
{
  return (CMU_ClockFreqGet(cmuClock_SYSRTC));
}

/*******************************************************************************
 * Computes difference between two times taking into account timer wrap-around.
 *
 * @param a Time.
 * @param b Time to substract from a.
 *
 * @return Time difference.
 ******************************************************************************/
__STATIC_INLINE uint32_t get_time_diff(uint32_t a,
                                       uint32_t b)
{
  return (a - b);
}

/*******************************************************************************
 * @brief
 *   Gets the precision (in PPM) of the sleeptimer's clock.
 *
 * @return
 *   Clock accuracy, in PPM.
 *
 ******************************************************************************/
uint16_t sleeptimer_hal_get_clock_accuracy(void)
{
  return CMU_LF_ClockPrecisionGet(cmuClock_SYSRTC);
}

/*******************************************************************************
 * Hardware Abstraction Layer to get the capture channel value.
 ******************************************************************************/
uint32_t sleeptimer_hal_get_capture(void)
{
  if ((sl_hal_sysrtc_get_group_interrupts(0) & _SYSRTC_GRP0_IF_CAP0_MASK) != 0) {
    sl_hal_sysrtc_clear_group_interrupts(0, _SYSRTC_GRP0_IF_CAP0_MASK);
    return sl_hal_sysrtc_get_group_capture_channel_value(0);
  } else {
    return 0;
  }
}

/*******************************************************************************
 * Hardware Abstraction Layer to reset PRS signal triggered by the associated
 * peripheral.
 ******************************************************************************/
void sleeptimer_hal_reset_prs_signal(void)
{
  sl_hal_sysrtc_clear_group_interrupts(0, SYSRTC_GRP0_IF_CMP1);
}

/*******************************************************************************
 * Hardware Abstraction Layer to disable PRS compare and capture channel.
 ******************************************************************************/
void sleeptimer_hal_disable_prs_compare_and_capture_channel(void)
{
  if (!cc1_disabled) {
    SYSRTC0->GRP0_CTRL &= ~SYSRTC_GRP0_CTRL_CMP1EN;
    SYSRTC0->GRP0_CTRL &= ~SYSRTC_GRP0_CTRL_CAP0EN;
    cc1_disabled = true;
  }
}

/***************************************************************************//**
 * Set lowest energy mode based on a project's configurations and clock source
 *
 * @note If power_manager_no_deepsleep component is included in a project, the
 *       lowest possible energy mode is EM1, else lowest energy mode is
 *       determined by clock source.
 ******************************************************************************/
#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
void sli_sleeptimer_set_pm_em_requirement(void)
{
  switch (CMU->SYSRTC0CLKCTRL & _CMU_SYSRTC0CLKCTRL_CLKSEL_MASK) {
    case CMU_SYSRTC0CLKCTRL_CLKSEL_LFRCO:
    case CMU_SYSRTC0CLKCTRL_CLKSEL_LFXO:
      sl_power_manager_add_em_requirement(SL_POWER_MANAGER_EM2);
      break;
    default:
      break;
  }
}
#endif
#endif
