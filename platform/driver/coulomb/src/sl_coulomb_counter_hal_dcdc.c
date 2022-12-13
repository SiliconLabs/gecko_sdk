/***************************************************************************//**
 * @file
 * @brief Coulomb Counter Driver Implementation for EFR32
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
#include "em_cmu.h"
#include "sl_coulomb_counter_config.h"
#include "sli_coulomb_counter_hal.h"
#include "peripheral_dcdc_coulomb_counter.h"

/// @cond DO_NOT_INCLUDE_WITH_DOXYGEN
#define ARRAY_SIZE(_array)  (sizeof(_array) / sizeof(_array[0]))
/// @endcond

/// DCDC's supported outputs.
static sli_coulomb_counter_output_t output_dcdc_em0 = SLI_COULOMB_COUNTER_OUTPUT_INIT(SL_COULOMB_COUNTER_OUTPUT_DCDC_EM0);
static sli_coulomb_counter_output_t output_dcdc_em2 = SLI_COULOMB_COUNTER_OUTPUT_INIT(SL_COULOMB_COUNTER_OUTPUT_DCDC_EM2);

/***************************************************************************//**
 * @brief
 *   Return pointer to output structure that matches the mask.
 ******************************************************************************/
sli_coulomb_counter_output_t* sli_coulomb_counter_hal_get_output(sl_coulomb_counter_output_mask_t mask)
{
  switch (mask) {
    case SL_COULOMB_COUNTER_OUTPUT_DCDC_EM0:
      return &output_dcdc_em0;
      break;

    case SL_COULOMB_COUNTER_OUTPUT_DCDC_EM2:
      return &output_dcdc_em2;
      break;

    default:
      return NULL;
      break;
  }
}

/***************************************************************************//**
 * @brief
 *   HAL implementation to enable interrupt flag.
 ******************************************************************************/
sl_status_t sli_coulomb_counter_hal_int_enable(uint8_t flag)
{
  if (flag == SL_COULOMB_COUNTER_INT_CALIBRATION_DONE) {
    CMU_IntEnable(CMU_IEN_CALRDY);
  } else if (flag == SL_COULOMB_COUNTER_INT_COUNTER_FULL) {
    sl_dcdc_coulomb_counter_enable_interrupts(DCDC_CCIEN_EM0OF | DCDC_CCIEN_EM2OF);
  } else {
    return SL_STATUS_FAIL;
  }

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * @brief
 *   HAL implementation to disable interrupt.
 ******************************************************************************/
sl_status_t sli_coulomb_counter_hal_int_disable(uint8_t flag)
{
  if (flag == SL_COULOMB_COUNTER_INT_CALIBRATION_DONE) {
    CMU_IntDisable(CMU_IEN_CALRDY);
  } else if (flag == SL_COULOMB_COUNTER_INT_COUNTER_FULL) {
    sl_dcdc_coulomb_counter_disable_interrupts(DCDC_CCIEN_EM0OF | DCDC_CCIEN_EM2OF);
  } else {
    return SL_STATUS_FAIL;
  }

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * @brief
 *   HAL implementation for checking if interrupt flag is set.
 ******************************************************************************/
sl_status_t sli_coulomb_counter_hal_int_is_set(uint8_t flag, bool *is_set)
{
  uint32_t reg = 0UL;

  if (flag == SL_COULOMB_COUNTER_INT_CALIBRATION_DONE) {
    reg = CMU_IntGet() & CMU_IF_CALRDY;
  } else if (flag == SL_COULOMB_COUNTER_INT_COUNTER_FULL) {
     reg = sl_dcdc_coulomb_counter_get_interrupts() & (DCDC_CCIF_EM0OF | DCDC_CCIF_EM2OF);
  } else {
    return SL_STATUS_FAIL;
  }

  if (reg) {
    *is_set = true;
  } else {
    *is_set = false;
  }

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * @brief
 *   HAL implementation for clearing interrupt flag.
 ******************************************************************************/
sl_status_t sli_coulomb_counter_hal_int_clear(uint8_t flag)
{
  if (flag == SL_COULOMB_COUNTER_INT_CALIBRATION_DONE) {
    CMU_IntClear(CMU_IF_CALRDY);
  } else if (flag == SL_COULOMB_COUNTER_INT_COUNTER_FULL) {
    sl_dcdc_coulomb_counter_clear_interrupts(DCDC_CCIF_EM0OF | DCDC_CCIF_EM2OF);
  } else {
    return SL_STATUS_FAIL;
  }

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * @brief
 *   HAL-specific initialization. This is called by
 *   @ref sl_coulomb_counter_init().
 ******************************************************************************/
sl_status_t sli_coulomb_counter_hal_init(sli_coulomb_counter_handle_t *handle)
{
  sl_dcdc_coulomb_counter_config_t config = DCDC_COULOMB_COUNTER_CONFIG_DEFAULT;
  const uint16_t COUNTER_THRESHOLD_50 = ((UINT16_MAX + 1) / 2);
  const uint16_t COUNTER_THRESHOLD_DELTA = (COUNTER_THRESHOLD_50 / 4);  /* 12.5% */
  uint16_t threshold = 0U;

  (void)handle;

  sl_dcdc_coulomb_counter_disable();

  /* configuring the counter thresholds EM0CNT and EM2CNT. */
  threshold = COUNTER_THRESHOLD_50 + (handle->threshold * COUNTER_THRESHOLD_DELTA);
  config.counter_threshold_em0 = threshold;
  config.counter_threshold_em2 = threshold;

  sl_dcdc_coulomb_counter_init(&config);

  sl_dcdc_coulomb_counter_enable();

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * @brief
 *   HAL implementation to start counting Coulombs.
 ******************************************************************************/
sl_status_t sli_coulomb_counter_hal_start(void)
{
  sl_dcdc_coulomb_counter_start();
  sl_dcdc_coulomb_counter_wait_start();

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * @brief
 *   HAL implementation to stop counting Coulombs.
 ******************************************************************************/
sl_status_t sli_coulomb_counter_hal_stop(void)
{
  sl_dcdc_coulomb_counter_stop();
  sl_dcdc_coulomb_counter_wait_stop();

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * @brief
 *   Reset Coulomb counters for all outputs to zero.
 ******************************************************************************/
sl_status_t sli_coulomb_counter_hal_clear_counters(void)
{
  sl_dcdc_coulomb_counter_clear_counters();
  sl_dcdc_coulomb_counter_wait_clear_counters();

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * @brief
 *   Read counters for that output and increment its total charge.
 ******************************************************************************/
sl_status_t sli_coulomb_counter_hal_read_output(sli_coulomb_counter_output_t *output,
                                                bool *need_recalibration)
{
  uint16_t read_val = 0U;

  if (output->calibration_state != SLI_COULOMB_COUNTER_CALIBRATION_COMPLETE) {
    return SL_STATUS_FAIL;
  }

  if (output == &output_dcdc_em0) {
    read_val = sl_dcdc_coulomb_counter_get_count(SL_DCDC_COULOMB_COUNTER_EM0);
  } else if (output == &output_dcdc_em2) {
    read_val = sl_dcdc_coulomb_counter_get_count(SL_DCDC_COULOMB_COUNTER_EM2);
  } else {
    return SL_STATUS_FAIL;
  }

  // Accumulate total charge (charge per pulse x number of pulses).
  output->total_charge = output->total_charge + (output->cpp * (float)read_val) / NANOCOULOMB_TO_COULOMB;

  // The user must initiate recalibration if the DC-DC converter's operating parameters
  // (e.g., peak current) are changed at any time.
  *need_recalibration = false;

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * @brief
 *   Convert calibration current load enum to current value.
 ******************************************************************************/
float sli_coulomb_counter_hal_cal_get_load_current(int8_t ccl_level)
{
  uint16_t ccload = 0U;

  switch (ccl_level) {
    case 0:
      ccload = sl_dcdc_coulomb_counter_get_cal_load_current(SL_DCDC_COULOMB_COUNTER_CAL_LOAD0);
      break;

    case 1:
      ccload = sl_dcdc_coulomb_counter_get_cal_load_current(SL_DCDC_COULOMB_COUNTER_CAL_LOAD1);
      break;

    case 2:
      ccload = sl_dcdc_coulomb_counter_get_cal_load_current(SL_DCDC_COULOMB_COUNTER_CAL_LOAD2);
      break;

    case 3:
      ccload = sl_dcdc_coulomb_counter_get_cal_load_current(SL_DCDC_COULOMB_COUNTER_CAL_LOAD3);
      break;

    case 4:
      ccload = sl_dcdc_coulomb_counter_get_cal_load_current(SL_DCDC_COULOMB_COUNTER_CAL_LOAD4);
      break;

    case 5:
      ccload = sl_dcdc_coulomb_counter_get_cal_load_current(SL_DCDC_COULOMB_COUNTER_CAL_LOAD5);
      break;

    case 6:
      ccload = sl_dcdc_coulomb_counter_get_cal_load_current(SL_DCDC_COULOMB_COUNTER_CAL_LOAD6);
      break;

    case 7:
      ccload = sl_dcdc_coulomb_counter_get_cal_load_current(SL_DCDC_COULOMB_COUNTER_CAL_LOAD7);
      break;

    default:
      EFM_ASSERT(false);
  }

  return (float) (0.2f * ccload);
}

/***************************************************************************//**
 * @brief
 *   Get calibration oscillator frequency.
 ******************************************************************************/
float sli_coulomb_counter_hal_get_osc_frequency(void)
{
  return (float)sl_dcdc_coulomb_counter_get_cal_reference_freq();
}

/***************************************************************************//**
 * @brief
 *   Check if output is available in EM2 or not.
 ******************************************************************************/
bool sli_coulomb_counter_hal_output_supports_em2(sli_coulomb_counter_output_t *output)
{
  if (output == &output_dcdc_em2) {
    return true;
  } else {
    return false;
  }
}

/***************************************************************************//**
 * @brief
 *   Start calibration for given output.
 ******************************************************************************/
sl_status_t sli_coulomb_counter_hal_cal_start(sli_coulomb_counter_output_t *output,
                                              int8_t nreq,
                                              int8_t ccl_level)
{
  sl_dcdc_coulomb_counter_emode_t emode = SL_DCDC_COULOMB_COUNTER_EM0;
  sl_dcdc_coulomb_counter_calibration_load_level_t ccl = SL_DCDC_COULOMB_COUNTER_CAL_LOAD0;
  sl_dcdc_coulomb_counter_calibration_config_t config = DCDC_COULOMB_COUNTER_CALIBRATION_CONFIG_DEFAULT;

  switch (ccl_level) {
    case 0:
      ccl = SL_DCDC_COULOMB_COUNTER_CAL_LOAD0;
      break;

    case 1:
      ccl = SL_DCDC_COULOMB_COUNTER_CAL_LOAD1;
      break;

    case 2:
      ccl = SL_DCDC_COULOMB_COUNTER_CAL_LOAD2;
      break;

    case 3:
      ccl = SL_DCDC_COULOMB_COUNTER_CAL_LOAD3;
      break;

    case 4:
      ccl = SL_DCDC_COULOMB_COUNTER_CAL_LOAD4;
      break;

    case 5:
      ccl = SL_DCDC_COULOMB_COUNTER_CAL_LOAD5;
      break;

    case 6:
      ccl = SL_DCDC_COULOMB_COUNTER_CAL_LOAD6;
      break;

    case 7:
      ccl = SL_DCDC_COULOMB_COUNTER_CAL_LOAD7;
      break;

    default:
      EFM_ASSERT(false);
  }

  if (output == &output_dcdc_em2) {
    emode = SL_DCDC_COULOMB_COUNTER_EM2;
  }

  config.cal_emode = emode;
  config.cal_count = nreq;
  config.cal_load_level = ccl;

  sl_dcdc_coulomb_counter_cal_init(config);
  sl_dcdc_coulomb_counter_cal_start();
  return SL_STATUS_OK;
}

/***************************************************************************//**
 * @brief
 *   Stop the calibration. Remove current load that was applied for calibration.
 ******************************************************************************/
sl_status_t sli_coulomb_counter_hal_cal_stop(void)
{
  sl_dcdc_coulomb_counter_cal_stop();
  return SL_STATUS_OK;
}

/***************************************************************************//**
 * @brief
 *   Read calibration result, i.e. the number of calibration clock cycles that were
 *   counted.
 ******************************************************************************/
sl_status_t sli_coulomb_counter_hal_cal_read_result(uint16_t *result)
{
  uint32_t cal_count = 0UL;

  // Wait until calibration completes and get result.
  cal_count = CMU_CalibrateCountGet();

  // Read the CCCALHALT bit when calibration is complete.
  // to determine if the measurement has been compromised in this way.
  if (sl_dcdc_coulomb_counter_calhalt_is_set() == true) {
    // The calibration was halted, and should be re-tried.
    return SL_COULOMB_COUNTER_CALIBRATION_ERROR;
  }

  if (cal_count > UINT16_MAX) {
    // The specified number of DC-DC pulses was not seen
    // before counter saturation.
    return SL_COULOMB_COUNTER_CALIBRATION_ERROR;
  }

  *result = (uint16_t)(cal_count & UINT16_MAX);

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * @brief
 *   Perform the Charge-Per-Pulse (CPP) Calculation.
 *
* @note
 *   The Charge-Per-Pulse (CPP) Calculation is explained in the
 *   reference manual in the Calibration Section.
 ******************************************************************************/
float sli_coulomb_counter_hal_compute_cpp(sli_coulomb_counter_handle_t *handle)
{
  float cpp = 0.0f;

  /*
   * Charge-Per-Pulse (CPP) Calculation
   *
   * CPP = [(Nlg * Nsm) / (fHF * Ncal)] * [(iload_lg - iload_sm) / (Nsm - Nlg)]
   */

  /* Parameters cal_nreq_low and cal_nreq_high are identical for DCDC. */
  unsigned int ncal = handle->cal_nreq_low;

  float fhf = sli_coulomb_counter_hal_get_osc_frequency();

  float iload_small_ua = sli_coulomb_counter_hal_cal_get_load_current(CCL_LEVEL_LOW);
  float iload_large_ua = sli_coulomb_counter_hal_cal_get_load_current(CCL_LEVEL_HIGH);

  float nsm = (float)handle->cal_count_low;
  float nlg = (float)handle->cal_count_high;

  /* numerator */
  cpp = nlg * nsm;
  cpp = cpp * (iload_large_ua - iload_small_ua);

  /* denominator */
  cpp = cpp / (nsm - nlg);

  /*
   * Note that current values are in uA, so it should be divided by 10^6 to get
   * results in Amp. But CPP values are in the order of nano coulombs, so that
   * means multiplying by 10^9 to convert it to this unit.
   * So instead, multiply by 10^(9-6), 10^3.
   *  cpp = cpp / 1000000;    // convert from uA to A
   *  cpp = cpp * 1000000000; // convert from C to nC
   *  => cpp = cpp * 1000;
   */
  cpp = cpp * 1000;

  /*
   * Finally, divide that cpp by the calibration oscillator frequency (fHF)
   * times the number of pulses to capture (Ncal).
   */
  cpp = cpp / (fhf * ncal);

  return cpp;
}
