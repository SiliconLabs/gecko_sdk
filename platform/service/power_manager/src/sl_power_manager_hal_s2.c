/***************************************************************************//**
 * @file
 * @brief Power Manager HAL API implementation.
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "em_device.h"
#if defined(_SILICON_LABS_32B_SERIES_2)
#include "em_emu.h"
#include "em_cmu.h"
#include "sl_assert.h"
#include "sl_power_manager_config.h"
#include "sl_power_manager.h"
#include "sli_power_manager_private.h"
#include "sl_sleeptimer.h"
#include "sli_sleeptimer.h"
#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif
#if !defined(SL_CATALOG_POWER_MANAGER_NO_DEEPSLEEP_PRESENT) \
  && !defined(SL_CATALOG_POWER_MANAGER_DEEPSLEEP_BLOCKING_HFXO_RESTORE_PRESENT)
#include "sli_hfxo_manager.h"
#endif

#include <stdbool.h>

/*******************************************************************************
 *********************************   DEFINES   *********************************
 ******************************************************************************/

// Time required by the hardware to come out of EM2 in microseconds.
// This value includes HW startup, emlib and sleepdrv execution time.
// Voltage scaling, HFXO startup and HFXO steady times are excluded from
// this because they are handled separately. RTCCSYNC time is also
// excluded and it is handled by RTCCSYNC code itself.
#if (_SILICON_LABS_32B_SERIES_2_CONFIG == 1)
#define EM2_WAKEUP_PROCESS_TIME_OVERHEAD_US (31u)
#else // (_SILICON_LABS_32B_SERIES_2_CONFIG == 2),
#define EM2_WAKEUP_PROCESS_TIME_OVERHEAD_US (31u)
#endif

// DPLL Locking delay related defines
#define DPLL_COARSECOUNT_VALUE  (5u)

// Time it takes to upscale voltage after EM2 in microseconds.
// This value represents the time for scaling from VSCALE0 to VSCALE2.
#define EM2_WAKEUP_VSCALE_OVERHEAD_US (64u)

// Default time value in microseconds required to wake-up the hfxo oscillator.
#define HFXO_WAKE_UP_TIME_DEFAULT_VALUE_US  (400u)

// high frequency oscillator wake-up time margin for possible variation
// A shift by 3 will be like a division by 8, so a percentage of 12.5%.
#define HFXO_START_UP_TIME_OVERHEAD_LOG2   3

// Default time value in microseconds for the HFXO minimum off time.
#define HFXO_MINIMUM_OFFTIME_DEFAULT_VALUE_US  (400u)

#if defined(SL_CATALOG_POWER_MANAGER_DEEPSLEEP_BLOCKING_HFXO_RESTORE_PRESENT)
// Table size of HFXO wake-up time measurement
#define HFXO_WAKE_UP_TIME_TABLE_SIZE  10
#endif

// Defines for hidden HFXO0 DBGSTATUS register and STARTUPDONE flag
#define HFXO0_DBGSTATUS  (*(volatile uint32_t *)(HFXO0_BASE + 0x05C))
#define HFXO_DBGSTATUS_STARTUPDONE                  (0x1UL << 1)                               /**< Startup Done Status                         */
#define _HFXO_DBGSTATUS_STARTUPDONE_SHIFT           1                                          /**< Shift value for HFXO_STARTUPDONE            */
#define _HFXO_DBGSTATUS_STARTUPDONE_MASK            0x2UL                                      /**< Bit mask for HFXO_STARTUPDONE               */

/*******************************************************************************
 *******************************  MACROS   *************************************
 ******************************************************************************/

/*******************************************************************************
* DPLL lock time can be approximately calculated by the equation:
*   COARSECOUNT * (M + 1) * Tref
* Where
*   - COARSECOUNT is calibration value in a hidden register. Its default value
*     is 5 and should not change with calibration.
*   - M is one the DPLL configuration parameter.
*   - Tref is the reference clock period.
*******************************************************************************/
#define DPLL_LOCKING_DELAY_US_FUNCTION(M, freq_ref) \
  ((uint64_t)(DPLL_COARSECOUNT_VALUE * ((M) +1)) * 1000000 + ((freq_ref) - 1)) / (freq_ref)

/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/

#if !defined(SL_CATALOG_POWER_MANAGER_NO_DEEPSLEEP_PRESENT)
// Variables to save the relevant clock registers.
uint32_t cmu_em01_grpA_clock_register;
#if defined(_CMU_EM01GRPBCLKCTRL_CLKSEL_MASK)
uint32_t cmu_em01_grpB_clock_register;
#endif
#if defined(_CMU_EM01GRPCCLKCTRL_CLKSEL_MASK)
uint32_t cmu_em01_grpC_clock_register;
#endif
#if defined(_CMU_DPLLREFCLKCTRL_CLKSEL_MASK)
uint32_t cmu_dpll_ref_clock_register;
#endif

uint32_t cmu_sys_clock_register;

// Time in ticks required for the general wake-up process.
static uint32_t process_wakeup_overhead_tick = 0;

#if defined(EMU_VSCALE_PRESENT)
static bool is_fast_wakeup_enabled = true;
#endif

static bool is_hf_x_oscillator_used = false;
static bool is_dpll_used = false;
static bool is_entering_deepsleep = false;

static bool is_hf_x_oscillator_already_started = false;

#if defined(SL_CATALOG_POWER_MANAGER_DEEPSLEEP_BLOCKING_HFXO_RESTORE_PRESENT)
static uint32_t hf_x_oscillator_wakeup_time_tc_inital = 0;

static uint32_t hfxo_wakeup_time_table[HFXO_WAKE_UP_TIME_TABLE_SIZE];
static uint8_t hfxo_wakeup_time_table_index = 0;
static uint32_t hfxo_wakeup_time_sum_average = 0;

// Time in ticks required for HFXO start-up after wake-up from sleep.
static uint32_t hfxo_wakeup_time_tick = 0;
#endif
#endif

/*******************************************************************************
 **************************   LOCAL FUNCTIONS   ********************************
 ******************************************************************************/

/***************************************************************************//**
 * Do some hardware initialization if necessary.
 ******************************************************************************/
void sli_power_manager_init_hardware(void)
{
  // Initializes EMU (voltage scaling in EM2/3)
#if defined(EMU_VSCALE_EM01_PRESENT)
  EMU_EM01Init_TypeDef em01_init = EMU_EM01INIT_DEFAULT;

  EMU_EM01Init(&em01_init);
#endif

#if !defined(SL_CATALOG_POWER_MANAGER_NO_DEEPSLEEP_PRESENT)
#if defined(EMU_VSCALE_PRESENT)
#if defined(SL_POWER_MANAGER_CONFIG_VOLTAGE_SCALING_FAST_WAKEUP)
#if (SL_POWER_MANAGER_CONFIG_VOLTAGE_SCALING_FAST_WAKEUP == 0)
  sli_power_manager_em23_voltage_scaling_enable_fast_wakeup(false);
#else
  sli_power_manager_em23_voltage_scaling_enable_fast_wakeup(true);
#endif
#else
  sli_power_manager_em23_voltage_scaling_enable_fast_wakeup(false);
#endif
#endif

  // Get the current HF oscillator for the SYSCLK
  cmu_sys_clock_register = CMU->SYSCLKCTRL & _CMU_SYSCLKCTRL_CLKSEL_MASK;
#if defined(_CMU_DPLLREFCLKCTRL_CLKSEL_MASK)
  cmu_dpll_ref_clock_register = CMU->DPLLREFCLKCTRL & _CMU_DPLLREFCLKCTRL_CLKSEL_MASK;
#endif

#if defined(CMU_CLKEN0_DPLL0)
  CMU->CLKEN0_SET = CMU_CLKEN0_HFXO0;

  CMU->CLKEN0_SET = CMU_CLKEN0_DPLL0;
#endif

  is_dpll_used = ((DPLL0->STATUS & _DPLL_STATUS_ENS_MASK) != 0);

  is_hf_x_oscillator_used = ((cmu_sys_clock_register == CMU_SYSCLKCTRL_CLKSEL_HFXO)
                             || ((CMU->EM01GRPACLKCTRL & _CMU_EM01GRPACLKCTRL_CLKSEL_MASK) == CMU_EM01GRPACLKCTRL_CLKSEL_HFXO));

#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_1)
  is_hf_x_oscillator_used |= (CMU->RADIOCLKCTRL & _CMU_RADIOCLKCTRL_EN_MASK) != 0;
#endif

#if defined(CMU_EM01GRPBCLKCTRL_CLKSEL_HFXO)
  is_hf_x_oscillator_used |= ((CMU->EM01GRPBCLKCTRL & _CMU_EM01GRPBCLKCTRL_CLKSEL_MASK) == CMU_EM01GRPBCLKCTRL_CLKSEL_HFXO);
#endif

#if defined(CMU_EM01GRPCCLKCTRL_CLKSEL_HFXO)
  is_hf_x_oscillator_used |= ((CMU->EM01GRPCCLKCTRL & _CMU_EM01GRPCCLKCTRL_CLKSEL_MASK) == CMU_EM01GRPCCLKCTRL_CLKSEL_HFXO);
#endif

#if defined(SL_CATALOG_POWER_MANAGER_DEEPSLEEP_BLOCKING_HFXO_RESTORE_PRESENT)
  // Set HFXO wakeup time to conservative default value
  hfxo_wakeup_time_tick = sli_power_manager_convert_delay_us_to_tick(HFXO_WAKE_UP_TIME_DEFAULT_VALUE_US);
  for (uint8_t i = 0; i < HFXO_WAKE_UP_TIME_TABLE_SIZE; i++) {
    hfxo_wakeup_time_table[i] = hfxo_wakeup_time_tick;
    hfxo_wakeup_time_sum_average += hfxo_wakeup_time_tick;
  }
#endif

  if (is_dpll_used && !is_hf_x_oscillator_used) {
    is_hf_x_oscillator_used |= (CMU->DPLLREFCLKCTRL & _CMU_DPLLREFCLKCTRL_CLKSEL_MASK) == _CMU_DPLLREFCLKCTRL_CLKSEL_HFXO;
  }

  // Calculate DPLL locking delay from its configuration
  if (is_dpll_used) {
    uint32_t freq = 0;

    switch (CMU->DPLLREFCLKCTRL & _CMU_DPLLREFCLKCTRL_CLKSEL_MASK) {
      case _CMU_DPLLREFCLKCTRL_CLKSEL_HFXO:
        freq = SystemHFXOClockGet();
        break;

      case _CMU_DPLLREFCLKCTRL_CLKSEL_LFXO:
        freq = SystemLFXOClockGet();
        break;

      case _CMU_DPLLREFCLKCTRL_CLKSEL_CLKIN0:
        freq = SystemCLKIN0Get();
        break;

      default:
        EFM_ASSERT(false);
        break;
    }
    if (freq > 0) { // Avoid division by 0
      // Add DPLL Locking delay
      process_wakeup_overhead_tick += sli_power_manager_convert_delay_us_to_tick(DPLL_LOCKING_DELAY_US_FUNCTION((DPLL0->CFG1 & _DPLL_CFG1_M_MASK) >> _DPLL_CFG1_M_SHIFT, freq));
    }
  }

  process_wakeup_overhead_tick += sli_power_manager_convert_delay_us_to_tick(EM2_WAKEUP_PROCESS_TIME_OVERHEAD_US);
#endif
}

/***************************************************************************//**
 * Enable or disable fast wake-up in EM2 and EM3.
 ******************************************************************************/
void sli_power_manager_em23_voltage_scaling_enable_fast_wakeup(bool enable)
{
#if (defined(EMU_VSCALE_PRESENT) && !defined(SL_CATALOG_POWER_MANAGER_NO_DEEPSLEEP_PRESENT))

  if (enable == is_fast_wakeup_enabled) {
    return;
  }

  EMU_EM23Init_TypeDef em23_init = EMU_EM23INIT_DEFAULT;

  // Enable/disable EMU voltage scaling in EM2/3
  if (enable) {
    em23_init.vScaleEM23Voltage = emuVScaleEM23_FastWakeup;
  } else {
    em23_init.vScaleEM23Voltage = emuVScaleEM23_LowPower;
  }

  EMU_EM23Init(&em23_init);

  // Calculate and add voltage scaling wake-up delays in ticks
  if (enable) {
    // Remove voltage scaling delay if it was added before
    process_wakeup_overhead_tick -= sli_power_manager_convert_delay_us_to_tick(EM2_WAKEUP_VSCALE_OVERHEAD_US);
  } else {
    // Add voltage scaling delay if it was not added before
    process_wakeup_overhead_tick += sli_power_manager_convert_delay_us_to_tick(EM2_WAKEUP_VSCALE_OVERHEAD_US);
  }

  is_fast_wakeup_enabled = enable;
#else
  (void)enable;
#endif
}

#if !defined(SL_CATALOG_POWER_MANAGER_NO_DEEPSLEEP_PRESENT)
/***************************************************************************//**
 * Save the CMU HF clock select state, oscillator enable, and voltage scaling.
 ******************************************************************************/
void sli_power_manager_save_states(void)
{
  // Save HF clock sources
  cmu_em01_grpA_clock_register = CMU->EM01GRPACLKCTRL & _CMU_EM01GRPACLKCTRL_CLKSEL_MASK;
#if defined(_CMU_EM01GRPBCLKCTRL_CLKSEL_MASK)
  cmu_em01_grpB_clock_register = CMU->EM01GRPBCLKCTRL & _CMU_EM01GRPBCLKCTRL_CLKSEL_MASK;
#endif
#if defined(_CMU_EM01GRPCCLKCTRL_CLKSEL_MASK)
  cmu_em01_grpC_clock_register = CMU->EM01GRPCCLKCTRL & _CMU_EM01GRPCCLKCTRL_CLKSEL_MASK;
#endif

  EMU_Save();
}
#endif

#if !defined(SL_CATALOG_POWER_MANAGER_NO_DEEPSLEEP_PRESENT)
/***************************************************************************//**
 * Handle pre-sleep operations if any are necessary, like manually disabling
 * oscillators, change clock settings, etc.
 ******************************************************************************/
void EMU_EM23PresleepHook(void)
{
  // Change the HF Clocks to be on FSRCO before sleep
  if (is_entering_deepsleep) {
    is_entering_deepsleep = false;

    CMU->SYSCLKCTRL = (CMU->SYSCLKCTRL & ~_CMU_SYSCLKCTRL_CLKSEL_MASK) | _CMU_SYSCLKCTRL_CLKSEL_FSRCO;
    // Switch the HF Clocks oscillator's to FSRCO before deepsleep
    CMU->EM01GRPACLKCTRL = (CMU->EM01GRPACLKCTRL  & ~_CMU_EM01GRPACLKCTRL_CLKSEL_MASK) | _CMU_EM01GRPACLKCTRL_CLKSEL_FSRCO;
#if defined(_CMU_EM01GRPBCLKCTRL_CLKSEL_MASK)
    CMU->EM01GRPBCLKCTRL = (CMU->EM01GRPBCLKCTRL  & ~_CMU_EM01GRPBCLKCTRL_CLKSEL_MASK) | _CMU_EM01GRPBCLKCTRL_CLKSEL_FSRCO;
#endif
#if defined(_CMU_EM01GRPCCLKCTRL_CLKSEL_MASK)
    CMU->EM01GRPCCLKCTRL = (CMU->EM01GRPCCLKCTRL  & ~_CMU_EM01GRPCCLKCTRL_CLKSEL_MASK) | _CMU_EM01GRPCCLKCTRL_CLKSEL_FSRCO;
#endif
    // Disable DPLL before deepsleep
#if (_DPLL_IPVERSION_IPVERSION_DEFAULT >= 1)
#if defined(_CMU_DPLLREFCLKCTRL_CLKSEL_MASK)
    if (is_dpll_used) {
      DPLL0->EN_CLR = DPLL_EN_EN;
      while ((DPLL0->EN & _DPLL_EN_DISABLING_MASK) != 0) {
      }
    }
#endif
#endif

    SystemCoreClockUpdate();
  }
  // Clear HFXO IEN RDY before entering sleep to prevent HFXO HW requests from waking up the system
  HFXO0->IEN_CLR = HFXO_IEN_RDY;
}
#endif

#if !defined(SL_CATALOG_POWER_MANAGER_NO_DEEPSLEEP_PRESENT)
/***************************************************************************//**
 * Handle post-sleep operations. The idea is to start HFXO ASAP when we know we
 * will need it.
 *
 * @note In case HFXO is already started when we wake-up (ENS flag is up),
 *       the hidden flag STARTUPDONE is check to see if the HFXO was just
 *       enabled or not. If HFXO is enabled automatically following the wake-up,
 *       the STARTUPDONE flag will not yet be up, and it's an indication that
 *       we can still process to the HFXO restore time measurement.
 ******************************************************************************/
void EMU_EM23PostsleepHook(void)
{
  // Re enable HFXO IEN RDY since it was disabled in EMU_EM23PresleepHook
  HFXO0->IEN_SET = HFXO_IEN_RDY;

  // Poke sleeptimer to determine if power manager's timer expired before the
  // ISR handler executes.
  // Also, check if HFXO is used.
  if (is_hf_x_oscillator_used
      && sli_sleeptimer_hal_is_int_status_set(SLEEPTIMER_EVENT_COMP)
      && sli_sleeptimer_is_power_manager_timer_next_to_expire()) {
    // Check if HFXO is already running and has finished its startup.
    // If yes, don't do the HFXO restore time measurement.
    if (((HFXO0->STATUS & _HFXO_STATUS_ENS_MASK) != 0
         && (HFXO0_DBGSTATUS & _HFXO_DBGSTATUS_STARTUPDONE_MASK) != 0)
        || (HFXO0->STATUS & _HFXO_STATUS_RDY_MASK) != 0) {
#if !defined(SL_CATALOG_POWER_MANAGER_DEEPSLEEP_BLOCKING_HFXO_RESTORE_PRESENT)
      // Force-enable HFXO in case the HFXO on-demand request would be removed
      // before we finish the restore process.
      HFXO0->CTRL_SET = HFXO_CTRL_FORCEEN;
#endif
      return;
    }

    // Start measure HFXO restore time.
    is_hf_x_oscillator_already_started = true;

#if defined(SL_CATALOG_POWER_MANAGER_DEEPSLEEP_BLOCKING_HFXO_RESTORE_PRESENT)
    hf_x_oscillator_wakeup_time_tc_inital = sl_sleeptimer_get_tick_count();

    // Switch SYSCLK to HFXO to measure restore time
    CMU->SYSCLKCTRL = (CMU->SYSCLKCTRL & ~_CMU_SYSCLKCTRL_CLKSEL_MASK) | cmuSelect_HFXO;
    SystemCoreClockUpdate();
#else
    sli_hfxo_manager_begin_startup_measurement();

    // Force enable HFXO to measure restore time
    HFXO0->CTRL_SET = HFXO_CTRL_FORCEEN;
#endif
  }
}
#endif

#if !defined(SL_CATALOG_POWER_MANAGER_NO_DEEPSLEEP_PRESENT)
/***************************************************************************//**
 * Handle pre-deepsleep operations if any are necessary, like manually disabling
 * oscillators, change clock settings, etc.
 ******************************************************************************/
void sli_power_manager_handle_pre_deepsleep_operations(void)
{
  is_entering_deepsleep = true;
}
#endif

#if !defined(SL_CATALOG_POWER_MANAGER_NO_DEEPSLEEP_PRESENT)
/***************************************************************************//**
 * Handle post-sleep operations if any are necessary, like manually enabling
 * oscillators, change clock settings, etc.
 ******************************************************************************/
void sli_power_manager_restore_high_freq_accuracy_clk(void)
{
  if (!is_hf_x_oscillator_used) {
    return;
  }

  // For the cases where it's not started from an early wake up
  // And if HFXO is not already running.
  if (!is_hf_x_oscillator_already_started) {
    // Check if HFXO is already running and has finished its startup.
    // If yes, don't do the HFXO restore time measurement.
    if (((HFXO0->STATUS & _HFXO_STATUS_ENS_MASK) != 0
         && (HFXO0_DBGSTATUS & _HFXO_DBGSTATUS_STARTUPDONE_MASK) != 0)
        || (HFXO0->STATUS & _HFXO_STATUS_RDY_MASK) != 0) {
#if !defined(SL_CATALOG_POWER_MANAGER_DEEPSLEEP_BLOCKING_HFXO_RESTORE_PRESENT)
      // Force-enable HFXO in case the HFXO on-demand request would be removed
      // before we finish the restore process.
      HFXO0->CTRL_SET = HFXO_CTRL_FORCEEN;
#endif
      return;
    }

#if defined(SL_CATALOG_POWER_MANAGER_DEEPSLEEP_BLOCKING_HFXO_RESTORE_PRESENT)
    hf_x_oscillator_wakeup_time_tc_inital = sl_sleeptimer_get_tick_count();

    // Switch SYSCLK to HFXO to measure restore time
    CMU->SYSCLKCTRL = (CMU->SYSCLKCTRL & ~_CMU_SYSCLKCTRL_CLKSEL_MASK) | cmuSelect_HFXO;
    SystemCoreClockUpdate();
#else
    // Start measure HFXO restore time
    sli_hfxo_manager_begin_startup_measurement();

    // Force enable HFXO to measure restore time
    HFXO0->CTRL_SET = HFXO_CTRL_FORCEEN;
#endif
  }

#if defined(SL_CATALOG_POWER_MANAGER_DEEPSLEEP_BLOCKING_HFXO_RESTORE_PRESENT)
  uint32_t current_time = sl_sleeptimer_get_tick_count() - hf_x_oscillator_wakeup_time_tc_inital;
  // Calculate average for HFXO restore time
  hfxo_wakeup_time_sum_average -= (int32_t)hfxo_wakeup_time_table[hfxo_wakeup_time_table_index] - (int32_t)current_time;
  hfxo_wakeup_time_table[hfxo_wakeup_time_table_index] = current_time;
  hfxo_wakeup_time_tick = ((hfxo_wakeup_time_sum_average + (HFXO_WAKE_UP_TIME_TABLE_SIZE - 1) ) / HFXO_WAKE_UP_TIME_TABLE_SIZE);

  // Update index of wakeup time table
  hfxo_wakeup_time_table_index++;
  hfxo_wakeup_time_table_index %= HFXO_WAKE_UP_TIME_TABLE_SIZE;
#endif

  is_hf_x_oscillator_already_started = false;
}
#endif

#if !defined(SL_CATALOG_POWER_MANAGER_NO_DEEPSLEEP_PRESENT)
/***************************************************************************//**
 * Checks if HF accuracy clocks is fully restored and, if needed, waits for it.
 *
 * @param wait  True, to wait for HF accuracy clocks to be ready
 *              False, otherwise.
 *
 * @return True, if HFXO ready.
 *         False, otherwise.
 ******************************************************************************/
bool sli_power_manager_is_high_freq_accuracy_clk_ready(bool wait)
{
  if (!is_hf_x_oscillator_used) {
    return true;
  }

#if defined(SL_CATALOG_POWER_MANAGER_DEEPSLEEP_BLOCKING_HFXO_RESTORE_PRESENT)
  (void)wait;
  return true;
#else
  return sli_hfxo_manager_is_hfxo_ready(wait);
#endif
}
#endif

#if !defined(SL_CATALOG_POWER_MANAGER_NO_DEEPSLEEP_PRESENT)
/***************************************************************************//**
 * Restore CMU HF clock select state, oscillator enable, and voltage scaling.
 ******************************************************************************/
void sli_power_manager_restore_states(void)
{
  // Restore specific EMU saved contexts
  EMU_Restore();

  // Restore DPLL after deepsleep
#if (_DPLL_IPVERSION_IPVERSION_DEFAULT >= 1)
#if defined(_CMU_DPLLREFCLKCTRL_CLKSEL_MASK)
  if (is_dpll_used) {
    DPLL0->EN_SET = DPLL_EN_EN;
    while ((DPLL0->STATUS & _DPLL_STATUS_RDY_MASK) == 0U) {
    }
  }
#endif
#endif

  // Restore SYSCLK to what it was before the deepsleep
  CMU->SYSCLKCTRL = (CMU->SYSCLKCTRL & ~_CMU_SYSCLKCTRL_CLKSEL_MASK) | cmu_sys_clock_register;

  // Restore the HF Clocks to what they were before deepsleep
  CMU->EM01GRPACLKCTRL = (CMU->EM01GRPACLKCTRL & ~_CMU_EM01GRPACLKCTRL_CLKSEL_MASK) | cmu_em01_grpA_clock_register;
#if defined(_CMU_EM01GRPBCLKCTRL_CLKSEL_MASK)
  CMU->EM01GRPBCLKCTRL = (CMU->EM01GRPBCLKCTRL & ~_CMU_EM01GRPBCLKCTRL_CLKSEL_MASK) | cmu_em01_grpB_clock_register;
#endif
#if defined(_CMU_EM01GRPCCLKCTRL_CLKSEL_MASK)
  CMU->EM01GRPCCLKCTRL = (CMU->EM01GRPCCLKCTRL & ~_CMU_EM01GRPCCLKCTRL_CLKSEL_MASK) | cmu_em01_grpC_clock_register;
#endif

  // Remove FORCEEN on HFXO
  if (is_hf_x_oscillator_used) {
    HFXO0->CTRL_CLR = HFXO_CTRL_FORCEEN;
  }

  SystemCoreClockUpdate();

#if 0 // TODO PLATFORM_MTL-8499
  // Wait for DPLL to lock
  if (is_dpll_used) {
    while (!(DPLL0->STATUS && _DPLL_STATUS_RDY_MASK)) {
    }
  }
#endif
}
#endif

/***************************************************************************//**
 * Applies energy mode.
 *
 * @param em  Energy mode to apply:
 *            SL_POWER_MANAGER_EM0
 *            SL_POWER_MANAGER_EM1
 *            SL_POWER_MANAGER_EM2
 *
 * @note EMU_EnterEM2() and EMU_EnterEM3() has the parameter 'restore' set to
 *       true in the Power Manager. When set to true, the parameter 'restore'
 *       allows the EMU driver to save and restore oscillators, clocks and
 *       voltage scaling. When the processor returns from EM2 or EM3, its
 *       execution resumes in a clean and stable state.
 ******************************************************************************/
void sli_power_manager_apply_em(sl_power_manager_em_t em)
{
  // Perform required actions according to energy mode
  switch (em) {
    case SL_POWER_MANAGER_EM1:
#if (SL_EMLIB_CORE_ENABLE_INTERRUPT_DISABLED_TIMING == 1)
      // when measuring interrupt disabled time, we don't
      // want to count the time spent in sleep
      sl_cycle_counter_pause();
#endif
      EMU_EnterEM1();
#if (SL_EMLIB_CORE_ENABLE_INTERRUPT_DISABLED_TIMING == 1)
      sl_cycle_counter_resume();
#endif
      break;

    case SL_POWER_MANAGER_EM2:
      EMU_EnterEM2(false);
      break;

    case SL_POWER_MANAGER_EM3:
      EMU_EnterEM3(false);
      break;

    case SL_POWER_MANAGER_EM0:
    default:
      EFM_ASSERT(false);
      break;
  }
}

#if !defined(SL_CATALOG_POWER_MANAGER_NO_DEEPSLEEP_PRESENT)
/*******************************************************************************
 * Returns the default minimum offtime for HFXO.
 ******************************************************************************/
uint32_t sli_power_manager_get_default_high_frequency_minimum_offtime(void)
{
  return sli_power_manager_convert_delay_us_to_tick(HFXO_MINIMUM_OFFTIME_DEFAULT_VALUE_US);
}
#endif

/*******************************************************************************
 * Gets the delay associated the wake-up process from EM23.
 *
 * @return Delay for the complete wake-up process with full restore.
 ******************************************************************************/
uint32_t sli_power_manager_get_wakeup_process_time_overhead(void)
{
#if !defined(SL_CATALOG_POWER_MANAGER_NO_DEEPSLEEP_PRESENT)
  uint32_t delay = 0;

  // Add HFXO start-up delay if applicable
  if (is_hf_x_oscillator_used) {
#if defined(SL_CATALOG_POWER_MANAGER_DEEPSLEEP_BLOCKING_HFXO_RESTORE_PRESENT)
    delay = hfxo_wakeup_time_tick;
#else
    delay = sli_hfxo_manager_get_startup_time();
#endif
    delay += delay >> HFXO_START_UP_TIME_OVERHEAD_LOG2;
  }

  // Add all additional overhead wake-up delays (DPLL, VSCALE, general wake-up process)
  delay += process_wakeup_overhead_tick;

  return delay;
#else
  return 0;
#endif
}

#if !defined(SL_CATALOG_POWER_MANAGER_NO_DEEPSLEEP_PRESENT)
/***************************************************************************//**
 * Informs the power manager module that the high accuracy/high frequency clock
 * is used.
 ******************************************************************************/
void sli_power_manager_set_high_accuracy_hf_clock_as_used(void)
{
  is_hf_x_oscillator_used = true;
}
#endif

#if !defined(SL_CATALOG_POWER_MANAGER_NO_DEEPSLEEP_PRESENT)
/*******************************************************************************
 * Restores the Low Frequency clocks according to what LF oscillators are used.
 *
 * @note On series 2, the on-demand will enable automatically the oscillators
 *       used when coming from sleep.
 ******************************************************************************/
void sli_power_manager_low_frequency_restore(void)
{
}

/***************************************************************************//**
 * Informs the power manager if the high accuracy/high frequency clock
 * is used, prior to scheduling an early clock restore.
 *
 * @return true if HFXO is used, else false.
 ******************************************************************************/
bool sli_power_manager_is_high_freq_accuracy_clk_used(void)
{
  return is_hf_x_oscillator_used;
}
#endif
#endif
