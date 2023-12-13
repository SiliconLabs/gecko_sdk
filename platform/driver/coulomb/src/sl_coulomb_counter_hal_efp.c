/***************************************************************************//**
 * @file
 * @brief Coulomb Counter Driver Implementation for EFP
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

#include <math.h>

#include "sl_coulomb_counter_config.h"
#include "sli_coulomb_counter_hal.h"
#include "sl_efp_instances.h"

/// @cond DO_NOT_INCLUDE_WITH_DOXYGEN
#define EFP_INSTANCE_IMPL(_inst) sl_efp_efp ## _inst
#define EFP_INSTANCE(_inst)      EFP_INSTANCE_IMPL(_inst)
#define ARRAY_SIZE(_array)  (sizeof(_array) / sizeof(_array[0]))
/// @endcond

/// EFP's supported outputs
static sli_coulomb_counter_output_t output_voa     = SLI_COULOMB_COUNTER_OUTPUT_INIT(SL_COULOMB_COUNTER_OUTPUT_EFP_VOA);
static sli_coulomb_counter_output_t output_vob_em0 = SLI_COULOMB_COUNTER_OUTPUT_INIT(SL_COULOMB_COUNTER_OUTPUT_EFP_VOB_EM0);
static sli_coulomb_counter_output_t output_vob_em2 = SLI_COULOMB_COUNTER_OUTPUT_INIT(SL_COULOMB_COUNTER_OUTPUT_EFP_VOB_EM2);
static sli_coulomb_counter_output_t output_voc     = SLI_COULOMB_COUNTER_OUTPUT_INIT(SL_COULOMB_COUNTER_OUTPUT_EFP_VOC);

/// EFP handle for I2C communication
static sl_efp_handle_t efp_handle = NULL;

/// OTP values, read during initialization.
static uint8_t otp_cccal_low = 0;
static uint8_t otp_cccal_high = 0;
static float otp_10mhz_osc_freq = 0.0f;

/*
 * CPPs (Coulomb Per Pulse) are values that are computed during calibration. By
 * reading the counters (CCA_MSBY, CCA_LSBY, etc.), that count a number of
 * pulses, and multiplying these values by CPPs, we get back the number of
 * coulombs.
 * CPPs depend on a number of elements, such as inductance, peak current, input
 * and output voltages. It is possible that EM2 is configured in a way that
 * cannot be replicated in EM0, for instance if voltage scaling is set to 0.9V.
 * Also, it's not really possible to start calibration and then go to EM2, as
 * the current drawn must be constant during calibration for accurate results.
 * Hopefully, there is a constant factor that can be applied to convert CPP
 * computed in one mode to get the CPP in another mode, and that factor only
 * depends on the input voltage of the EFP.
 *
 *   (1) Vbatt, input of the EFP
 *   (2) factor to convert CPP@1.0V to CPP@0.9V
 *   (3) factor to convert CPP@1.1V to CPP@0.9V
 * All these factors are expressed multiplied by 1000, i.e. 988 means 0.988.
 */
static int16_t cpp_em2_adjustments[][3] = {
  /* (1)   (2)   (3)  */
  { 1800, 988, 951 },
  { 2000, 1010, 1000 },
  { 2200, 1026, 1034 },
  { 2400, 1037, 1059 },
  { 2600, 1046, 1078 },
  { 2800, 1053, 1094 },
  { 3000, 1058, 1106 },
  { 3200, 1063, 1116 },
  { 3400, 1067, 1124 },
  { 3600, 1070, 1132 },
  { 3800, 1073, 1138 },
  { 4000, 1075, 1143 },
  { 4200, 1077, 1148 },
  { 4400, 1079, 1152 },
  { 4600, 1081, 1156 },
  { 4800, 1083, 1160 },
  { 5000, 1084, 1163 },
  { 5200, 1085, 1165 },
  { 5400, 1086, 1168 },
};

/***************************************************************************//**
 * @brief
 *   Return pointer to output structure that matches the mask.
 ******************************************************************************/
sli_coulomb_counter_output_t* sli_coulomb_counter_hal_get_output(sl_coulomb_counter_output_mask_t mask)
{
  switch (mask) {
    case SL_COULOMB_COUNTER_OUTPUT_EFP_VOA:
      return &output_voa;
      break;

    case SL_COULOMB_COUNTER_OUTPUT_EFP_VOB_EM0:
      return &output_vob_em0;
      break;

    case SL_COULOMB_COUNTER_OUTPUT_EFP_VOB_EM2:
      return &output_vob_em2;
      break;

    case SL_COULOMB_COUNTER_OUTPUT_EFP_VOC:
      return &output_voc;
      break;

    default:
      return NULL;
      break;
  }
}

/***************************************************************************//**
 * @brief
 *   Helper function to unmask EFP interrupt.
 *
 * param[in] flag
 *   interrupt flag.
 *
 * param[in] enable
 *   1 to enable, 0 to disable.
 *
 * @return
 *   0 if successful, error code otherwise.
 ******************************************************************************/
static sl_status_t sli_coulomb_counter_hal_int_configure(uint8_t flag, uint8_t enable)
{
  if (flag == SL_COULOMB_COUNTER_INT_CALIBRATION_DONE) {
    return sl_efp_write_register_field(efp_handle, _EFP01_STATUS_GM_ADDRESS, enable,
                                       _EFP01_STATUS_GM_CCC_ISDONE_UNMASK_MASK,
                                       _EFP01_STATUS_GM_CCC_ISDONE_UNMASK_SHIFT);
  } else if (flag == SL_COULOMB_COUNTER_INT_COUNTER_FULL) {
    return sl_efp_write_register_field(efp_handle, _EFP01_STATUS_GM_ADDRESS, enable,
                                       _EFP01_STATUS_GM_CC_FULL_UNMASK_MASK,
                                       _EFP01_STATUS_GM_CC_FULL_UNMASK_SHIFT);
  } else {
    return SL_STATUS_FAIL;
  }
}

/***************************************************************************//**
 * @brief
 *   HAL implementation to enable interrupt flag.
 ******************************************************************************/
sl_status_t sli_coulomb_counter_hal_int_enable(uint8_t flag)
{
  return sli_coulomb_counter_hal_int_configure(flag, 0x1);
}

/***************************************************************************//**
 * @brief
 *   HAL implementation to disable interrupt.
 ******************************************************************************/
sl_status_t sli_coulomb_counter_hal_int_disable(uint8_t flag)
{
  return sli_coulomb_counter_hal_int_configure(flag, 0);
}

/***************************************************************************//**
 * @brief
 *   HAL implementation for checking if interrupt flag is set.
 ******************************************************************************/
sl_status_t sli_coulomb_counter_hal_int_is_set(uint8_t flag, bool *is_set)
{
  sl_status_t status;
  uint8_t reg;

  if (flag == SL_COULOMB_COUNTER_INT_CALIBRATION_DONE) {
    status = sl_efp_read_register_field(efp_handle, _EFP01_STATUS_G_ADDRESS, &reg,
                                        _EFP01_STATUS_G_CCC_ISDONE_MASK,
                                        _EFP01_STATUS_G_CCC_ISDONE_SHIFT);
  } else if (flag == SL_COULOMB_COUNTER_INT_COUNTER_FULL) {
    status = sl_efp_read_register_field(efp_handle, _EFP01_STATUS_G_ADDRESS, &reg,
                                        _EFP01_STATUS_G_CC_FULL_MASK,
                                        _EFP01_STATUS_G_CC_FULL_SHIFT);
  } else {
    return SL_STATUS_FAIL;
  }

  if (status == SL_STATUS_OK) {
    if (reg) {
      *is_set = true;
    } else {
      *is_set = false;
    }
  }

  return status;
}

/***************************************************************************//**
 * @brief
 *   HAL implementation for clearing interrupt flag.
 ******************************************************************************/
sl_status_t sli_coulomb_counter_hal_int_clear(uint8_t flag)
{
  if (flag == SL_COULOMB_COUNTER_INT_CALIBRATION_DONE) {
    return sl_efp_write_register_field(efp_handle, _EFP01_STATUS_G_ADDRESS, 0x1,
                                       _EFP01_STATUS_G_CCC_ISDONE_MASK,
                                       _EFP01_STATUS_G_CCC_ISDONE_SHIFT);
  } else if (flag == SL_COULOMB_COUNTER_INT_COUNTER_FULL) {
    return sl_efp_write_register_field(efp_handle, _EFP01_STATUS_G_ADDRESS, 0x1,
                                       _EFP01_STATUS_G_CC_FULL_MASK,
                                       _EFP01_STATUS_G_CC_FULL_SHIFT);
  } else {
    return SL_STATUS_FAIL;
  }
}

/***************************************************************************//**
 * @brief
 *   HAL-specific initialization. This is called by
 *   @ref sl_coulomb_counter_init().
 ******************************************************************************/
sl_status_t sli_coulomb_counter_hal_init(sli_coulomb_counter_handle_t *handle)
{
  sl_status_t status;
  uint8_t reg;

  efp_handle = EFP_INSTANCE(SL_COULOMB_COUNTER_EFP_INSTANCE);
  if (efp_handle == NULL) {
    return SL_STATUS_FAIL;
  }

  /*
   * Read OTP calibration constants.
   */
  status = sl_efp_read_otp(efp_handle, EFP01_OTP_CCCAL_LOW, &otp_cccal_low);
  if (status != SL_STATUS_OK) {
    return status;
  }

  status = sl_efp_read_otp(efp_handle, EFP01_OTP_CCCAL_HIGH, &otp_cccal_high);
  if (status != SL_STATUS_OK) {
    return status;
  }

  status = sl_efp_read_otp(efp_handle, EFP01_OTP_OSC10MHZ_CAL, &reg);
  if (status != SL_STATUS_OK) {
    return status;
  }

  /*
   * Encoded as 2s complement of round(128 * (ErrPct / 0.40%))).
   */
  otp_10mhz_osc_freq = 1e7 * (1 + (int8_t)reg * 0.004 / 128);

  /*
   * Update prescaler and threshold value.
   */
  status = sl_efp_read_register(efp_handle, _EFP01_CC_CTRL_ADDRESS, &reg);
  if (status != SL_STATUS_OK) {
    return status;
  }

  reg =  (reg & ~_EFP01_CC_CTRL_CC_PRESCL_MASK)
        | ((handle->prescaler << _EFP01_CC_CTRL_CC_PRESCL_SHIFT) & _EFP01_CC_CTRL_CC_PRESCL_MASK);

  reg =  (reg & ~_EFP01_CC_CTRL_CC_THRSH_MASK)
        | ((handle->threshold << _EFP01_CC_CTRL_CC_THRSH_SHIFT) & _EFP01_CC_CTRL_CC_THRSH_MASK);

  status = sl_efp_write_register(efp_handle, _EFP01_CC_CTRL_ADDRESS, reg);

  return status;
}

/***************************************************************************//**
 * @brief
 *   HAL implementation to start counting Coulombs.
 ******************************************************************************/
sl_status_t sli_coulomb_counter_hal_start(void)
{
  return sl_efp_write_register_field(efp_handle, _EFP01_CC_CTRL_ADDRESS, 1,
                                     _EFP01_CC_CTRL_CC_EN_MASK,
                                     _EFP01_CC_CTRL_CC_EN_SHIFT);
}

/***************************************************************************//**
 * @brief
 *   HAL implementation to stop counting Coulombs.
 ******************************************************************************/
sl_status_t sli_coulomb_counter_hal_stop(void)
{
  return sl_efp_write_register_field(efp_handle, _EFP01_CC_CTRL_ADDRESS, 0,
                                     _EFP01_CC_CTRL_CC_EN_MASK,
                                     _EFP01_CC_CTRL_CC_EN_SHIFT);
}

/***************************************************************************//**
 * @brief
 *   Read counters for that output and increment its total charge.
 ******************************************************************************/
sl_status_t sli_coulomb_counter_hal_read_output(sli_coulomb_counter_output_t *output,
                                                bool *need_recalibration)
{
  uint8_t cc_msby_addr, cc_lsby_addr;
  uint8_t cc_mode_mask = 0x0;
  uint16_t read_val;
  uint8_t tmp_val;
  sl_status_t status;

  if (output->calibration_state != SLI_COULOMB_COUNTER_CALIBRATION_COMPLETE) {
    return SL_STATUS_FAIL;
  }

  if (output == &output_voa) {
    /*
     * MSB and LSB registers might be different when operating
     * with LDO C in parallel. This case is not handled for now.
     */
    cc_msby_addr = _EFP01_CCA_MSBY_ADDRESS;
    cc_lsby_addr = _EFP01_CCA_LSBY_ADDRESS;
    cc_mode_mask = _EFP01_CC_MODE_CCA_MODE_MASK;
  } else if (output == &output_vob_em0 ) {
    cc_msby_addr = _EFP01_CCB0_MSBY_ADDRESS;
    cc_lsby_addr = _EFP01_CCB0_LSBY_ADDRESS;
    cc_mode_mask = _EFP01_CC_MODE_CCB_MODE_MASK;
  } else if (output == &output_vob_em2) {
    cc_msby_addr = _EFP01_CCB2_MSBY_ADDRESS;
    cc_lsby_addr = _EFP01_CCB2_LSBY_ADDRESS;
    cc_mode_mask = _EFP01_CC_MODE_CCB_MODE_MASK;
  } else if (output == &output_voc) {
    cc_msby_addr = _EFP01_CCC_MSBY_ADDRESS;
    cc_lsby_addr = _EFP01_CCC_LSBY_ADDRESS;
  } else {
    return SL_STATUS_FAIL;
  }

  /*
   * read MSB and LSB registers to get number of pulses.
   */
  status = sl_efp_read_register(efp_handle, cc_msby_addr, &tmp_val);
  if (status != SL_STATUS_OK) {
    return status;
  }

  read_val = tmp_val << 8;

  status = sl_efp_read_register(efp_handle, cc_lsby_addr, &tmp_val);
  if (status != SL_STATUS_OK) {
    return status;
  }

  read_val |= tmp_val;

  /*
   * Accumulate total charge (charge per pulse x number of pulses).
   */
  output->total_charge = output->total_charge + (output->cpp * (float)read_val) / NANOCOULOMB_TO_COULOMB;

  /*
   * Get mode of operation. CPP values that are computed during calibration
   * are dependent of the operation mode so if it changes, recalibration
   * must be done.
   */
  if (cc_mode_mask != 0) {
    status = sl_efp_read_register(efp_handle, _EFP01_CC_MODE_ADDRESS, &tmp_val);
    if (status != SL_STATUS_OK) {
      return status;
    }

    tmp_val &= cc_mode_mask;

    /*
     * if operation mode has changed, reset CPP and mark
     * output as not calibrated.
     */
    if (output->calibration_mode != tmp_val) {
      output->cpp = 0;
      output->calibration_state = SLI_COULOMB_COUNTER_CALIBRATION_NOT_CALIBRATED;
      *need_recalibration = true;
    } else {
      *need_recalibration = false;
    }
  } else {
    *need_recalibration = false;
  }

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * @brief
 *   Reset Coulomb counters for all outputs to zero.
 ******************************************************************************/
sl_status_t sli_coulomb_counter_hal_clear_counters(void)
{
  return sl_efp_write_register_field(efp_handle, _EFP01_CMD_ADDRESS, 1,
                                     _EFP01_CMD_CC_CLR_MASK,
                                     _EFP01_CMD_CC_CLR_SHIFT);
}

/***************************************************************************//**
 * @brief
 *   Return value to be written in CCL_SEL based on the output.
 *
 * param[in] output
 *   Output to be calibrated.
 *
 * @return
 *   Value to be written in CC_CAL.CCL_SEL for the corresponding output.
 ******************************************************************************/
static uint8_t hal_efp_cal_get_ccl_sel(sli_coulomb_counter_output_t *output)
{
  if (output == &output_voa) {
    return 0x1;
  } else if (output == &output_vob_em0 || output == &output_vob_em2) {
    return 0x2;
  } else if (output == &output_voc) {
    return 0x3;
  } else {
    EFM_ASSERT(0);
    return 0;
  }
}

/***************************************************************************//**
 * @brief
 *   Convert calibration current load enum to current value.
 ******************************************************************************/
float sli_coulomb_counter_hal_cal_get_load_current(int8_t ccl_level)
{
  float cal_current_ua;

  EFM_ASSERT(ccl_level >= 0);
  EFM_ASSERT(ccl_level <= 7);

  if (ccl_level > 3) {
    /*
     * CC_CAL_HIGH = OTP_CCCAL_HIGH * 23.4375uA + 13.9mA
     */
    cal_current_ua = otp_cccal_high * 23.4375f + 13900.0f;
  } else {
    /*
     * CC_CAL_LOW = OTP_CCCAL_LOW * 1.5725uA = 0.87mA
     */
    cal_current_ua = otp_cccal_low * 1.5725f + 870.0f;
  }

  switch (ccl_level) {
    case 0:
    case 4:
      cal_current_ua = cal_current_ua * 0.5094f;
      break;

    case 1:
    case 5:
      cal_current_ua = cal_current_ua * 0.6352f;
      break;

    case 2:
    case 6:
      cal_current_ua = cal_current_ua * 0.802f;
      break;
  }

  return cal_current_ua;
}

/***************************************************************************//**
 * @brief
 *   Get calibration oscillator frequency.
 ******************************************************************************/
float sli_coulomb_counter_hal_get_osc_frequency(void)
{
  return otp_10mhz_osc_freq;
}

/***************************************************************************//**
 * @brief
 *   Check if output is available in EM2 or not.
 ******************************************************************************/
bool sli_coulomb_counter_hal_output_supports_em2(sli_coulomb_counter_output_t *output)
{
  if (output == &output_vob_em2) {
    return true;
  } else {
    return false;
  }
}

/***************************************************************************//**
 * @brief
 *   Get index to be used in cpp_em2_adjustments according to vscale settings.
 *
 * @param[out] index
 *   Index to be used in cpp_em2_adjustments to compute the factor between EM0
 *   and EM2.
 *
 * @param[in] em0_vscale
 *   Voltage scaling value for EM0.
 *
 * @param[in] em2_vscale
 *   Voltage scaling value for EM2.
 *
 * @return
 *   0 if successful, error code otherwise.
 ******************************************************************************/
static sl_status_t sli_coulomb_counter_hal_get_factor_index(int *index, int em0_vscale, int em2_vscale)
{
  if (em2_vscale != 0 || em0_vscale == em2_vscale) {
    return SL_STATUS_FAIL;
  }

  if (em0_vscale == EMU_VSCALE2) {
    *index = 2;
  } else if (em0_vscale == EMU_VSCALE1) {
    *index = 1;
  } else {
    return SL_STATUS_FAIL;
  }

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * @brief
 *   Adjust output's CPP if voltage scaling is different in EM0 and EM2.
 ******************************************************************************/
sl_status_t sli_coulomb_counter_hal_cal_adjust_em2_cpp(sli_coulomb_counter_output_t *output,
                                                       int em0_vscale, int em2_vscale)
{
  int size = ARRAY_SIZE(cpp_em2_adjustments);
  int voltage_index = 0;
  float factor = 0;
  int factor_index;
  uint16_t input_mv = 0;
  sl_status_t status;

  if (!sli_coulomb_counter_hal_output_supports_em2(output)) {
    return SL_STATUS_OK;
  }

  /* determine factor index in cpp_em2_adjustments. */
  status = sli_coulomb_counter_hal_get_factor_index(&factor_index, em0_vscale, em2_vscale);
  if (status != SL_STATUS_OK) {
    return status;
  }

  /* read input. */
  status = sl_efp_get_vdd_avg(efp_handle, &input_mv);
  if (status != SL_STATUS_OK) {
    return status;
  }

  /*
   * if the value was out of known boundaries, just approximate
   * with the closest factor.
   */
  if (input_mv < cpp_em2_adjustments[0][voltage_index]) {
    factor = (float)cpp_em2_adjustments[0][factor_index];
  } else if (input_mv > cpp_em2_adjustments[size - 1][voltage_index]) {
    factor = (float)cpp_em2_adjustments[size - 1][factor_index];
  }

  if (factor != 0) {
    factor = factor / 1000.0f; /* convert back to original value. */
    output->cpp = output->cpp * factor;

    return SL_STATUS_OK;
  }

  for (int i = 1; i < size; i++) {
    if (input_mv > cpp_em2_adjustments[i][voltage_index]) {
      continue;
    }

    /*
     * At this point:
     *   cpp_em2_adjustments[i - 1][voltage_index] <= input_mv <= cpp_em2_adjustments[i][voltage_index]
     *
     * Calculate affine function that goes through these two points to determine
     * the closest factor possible.
     *
     * Factor = slope * input_mv + offset
     */

    float slope = (float)(cpp_em2_adjustments[i][factor_index] - cpp_em2_adjustments[i - 1][factor_index]);
    slope = slope / (float)(cpp_em2_adjustments[i][voltage_index] - cpp_em2_adjustments[i - 1][voltage_index]);

    float offset = (float)cpp_em2_adjustments[i][factor_index] - (float)(cpp_em2_adjustments[i][voltage_index]) * slope;

    factor = slope * (float)input_mv + offset;
    factor = factor / 1000.0f; /* values in array are stored multiplied by a thousand. */

    output->cpp = output->cpp * factor;

    return SL_STATUS_OK;
  }

  return SL_STATUS_FAIL;
}

/***************************************************************************//**
 * @brief
 *   Start calibration for given output.
 ******************************************************************************/
sl_status_t sli_coulomb_counter_hal_cal_start(sli_coulomb_counter_output_t *output,
                                              int8_t nreq,
                                              int8_t ccl_level)
{
  sl_status_t status;
  uint8_t cc_cal;

  uint8_t ccl_sel = hal_efp_cal_get_ccl_sel(output);

  cc_cal  =  (nreq << _EFP01_CC_CAL_CC_CAL_NREQ_SHIFT)
            | (ccl_sel << _EFP01_CC_CAL_CCL_SEL_SHIFT)
            | (ccl_level << _EFP01_CC_CAL_CCL_LVL_SHIFT);
  status = sl_efp_write_register(efp_handle, _EFP01_CC_CAL_ADDRESS, cc_cal);
  if (status != SL_STATUS_OK) {
    return status;
  }

  status = sl_efp_write_register_field(efp_handle, _EFP01_CMD_ADDRESS, 1,
                                       _EFP01_CMD_CC_CLR_MASK,
                                       _EFP01_CMD_CC_CLR_SHIFT);
  if (status != SL_STATUS_OK) {
    return status;
  }

  return sl_efp_write_register_field(efp_handle, _EFP01_CMD_ADDRESS, 1,
                                     _EFP01_CMD_CC_CAL_STRT_MASK,
                                     _EFP01_CMD_CC_CAL_STRT_SHIFT);
}

/***************************************************************************//**
 * @brief
 *   Stop the calibration. Remove current load that was applied for calibration.
 ******************************************************************************/
sl_status_t sli_coulomb_counter_hal_cal_stop(void)
{
  return sl_efp_write_register(efp_handle, _EFP01_CC_CAL_ADDRESS, 0x00);
}

/***************************************************************************//**
 * @brief
 *   Read calibration result, i.e. the number of calibration clock cycles that were
 *   counted.
 ******************************************************************************/
sl_status_t sli_coulomb_counter_hal_cal_read_result(uint16_t *result)
{
  sl_status_t status;
  uint8_t reg;

  status = sl_efp_read_register(efp_handle, _EFP01_CCC_MSBY_ADDRESS, &reg);
  if (status != SL_STATUS_OK) {
    return status;
  }

  *result = reg << 8;

  status = sl_efp_read_register(efp_handle, _EFP01_CCC_LSBY_ADDRESS, &reg);
  if (status != SL_STATUS_OK) {
    return status;
  }

  *result |= reg;

  return status;
}

/***************************************************************************//**
 * @brief
 *   Perform the Charge-Per-Pulse (CPP) Calculation.
 *
 * @note
 *   The Charge-Per-Pulse (CPP) Calculation is explained in the AN1188.
 ******************************************************************************/
float sli_coulomb_counter_hal_compute_cpp(sli_coulomb_counter_handle_t *handle)
{
  float cpp;

  /*
   * AN1188 gives following formula:
   *
   *                       I_large_load - I_small_load
   * CPP = ---------------------------------------------------
   *            7    nreq_large + 1        7    nreq_small + 1
   *         10^ * 2^                 - 10^ * 2^
   *         ----------------------     ----------------------
   *                 count_large               count_low
   *
   * Rearranged:
   *
   *
   *                (count_low * count_large) * (I_large_load - I_small_load)
   * CPP = -----------------------------------------------------------------------------
   *            7                   nreq_large + 1                      nreq_small + 1
   *        10^   * [(count_low * 2^               ) - (count_large * 2^               )]
   */

  float i_large_load_ua = sli_coulomb_counter_hal_cal_get_load_current(CCL_LEVEL_HIGH);
  float i_small_load_ua = sli_coulomb_counter_hal_cal_get_load_current(CCL_LEVEL_LOW);

  float pulses_large = (float)(pow(2, handle->cal_nreq_high + 1)) * (float)handle->cal_count_low;
  float pulses_small = (float)(pow(2, handle->cal_nreq_low + 1)) * (float)handle->cal_count_high;

  /* numerator */
  cpp = handle->cal_count_low * handle->cal_count_high;
  cpp = cpp * (i_large_load_ua - i_small_load_ua);

  /* denominator */
  cpp = cpp / (pulses_large - pulses_small);

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
   * Finally, divide that cpp by 10^7, for the 10MHz oscillator frequency. It's
   * possible that the HAL provides a more precise frequency for that
   * oscillator, so use that instead for more accurate cpp.
   */
  cpp = cpp / sli_coulomb_counter_hal_get_osc_frequency();

  return cpp;
}

/***************************************************************************//**
 * @brief
 *   Compute the number of PFM pulses (nreq) required to avoid the overflow
 *   of the CCC_MSBY:CCC_LSBY 16-bit register pair during calibration.
 ******************************************************************************/
int sli_coulomb_counter_calibrate_compute_nreq(int16_t ccc)
{
  int nreq;

  /*
   * Formula is given in application note AN1188:
   *
   *                                2^17
   *  Max NReq = rounddown( log2 (-------) - 1 )
   *                                CCC
   */
  nreq = (int)floor(log((double)pow(2, 17) / (double)ccc) / log(2) - 1);
  if (nreq > 7) {
    nreq = 7;
  }

  EFM_ASSERT(nreq >= 0);

  return nreq;
}
