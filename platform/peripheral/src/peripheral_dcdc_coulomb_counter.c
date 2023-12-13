/***************************************************************************//**
 * @file
 * @brief DCDC Coulomb Counter (DCDC_COULOMB_COUNTER) peripheral API
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "peripheral_dcdc_coulomb_counter.h"
#if defined(DCDC_COUNT) && (DCDC_COUNT > 0) && defined(DCDC_CCCTRL_CCEN)
#include "sl_assert.h"
#include "em_bus.h"
#include "em_prs.h"

/***************************************************************************//**
 * @addtogroup dcdccoulombcounter DCDC - DCDC Coulomb Counter Unit
 * @brief DCDC Coulomb Counter (DCDC_COULOMB_COUNTER) Peripheral API
 * @details
 *  This module contains functions to control the DCDC_COULOMB_COUNTER peripheral
 *  of Silicon Labs 32-bit MCUs and SoCs. The DCDC_COULOMB_COUNTER module
 *  measures the charge delivered by the DC-DC.
 * @{
 ******************************************************************************/

/* Global variable to store the channel assigned for calibrating */
/* the DCDC Coulomb Counter module. */
static int prs_channel = -1;

/***************************************************************************//**
 * Initializes DCDC_COULOMB_COUNTER module.
 ******************************************************************************/
void sl_hal_dcdc_coulomb_counter_init(const sl_hal_dcdc_coulomb_counter_config_t *p_config)
{
  if (DCDC->CCCTRL & _DCDC_CCCTRL_CCEN_MASK) {
    /* Disable COULOMB_COUNTER_INTERNAL module. */
    sl_hal_dcdc_coulomb_counter_disable();
  }

  /* Set configuration. */
  /* The counter thresholds can be used be used to establish a service  */
  /* interval for the coulomb counter hardware. */
  DCDC->CCTHR = ((uint32_t)(p_config->counter_threshold_em0) << _DCDC_CCTHR_EM0CNT_SHIFT)
                | ((uint32_t)(p_config->counter_threshold_em2) << _DCDC_CCTHR_EM2CNT_SHIFT);
}

/***************************************************************************//**
 * Disables DCDC_COULOMB_COUNTER module.
 ******************************************************************************/
void sl_hal_dcdc_coulomb_counter_disable(void)
{
  /* Quick exit if the DCDC_COULOMB_COUNTER and is already disabled. */
  if ((DCDC->CCCTRL & _DCDC_CCCTRL_CCEN_MASK) == 0U) {
    return;
  }

  /* Stop counting if running. */
  if (DCDC->CCSTATUS & _DCDC_CCSTATUS_CCRUNNING_MASK) {
    sl_hal_dcdc_coulomb_counter_stop();
  }

  /* Disable module. */
  EMU_DCDCSync(_DCDC_SYNCBUSY_MASK);
  DCDC->CCCTRL_CLR = DCDC_CCCTRL_CCEN;
}

/***************************************************************************//**
 * Gets the DCDC_COULOMB_COUNTER count for the selected energy mode.
 *
 * @note As a guideline, using the default DC-DC settings, the DC-DC may
 * produce up to 60,000-70,000 pulses per second for every mA of load current.
 ******************************************************************************/
uint32_t sl_hal_dcdc_coulomb_counter_get_count(sl_hal_dcdc_coulomb_counter_emode_t emode)
{
  if (emode == SL_HAL_DCDC_COULOMB_COUNTER_EM0) {
    return DCDC->CCEM0CNT;
  } else {
    return DCDC->CCEM2CNT;
  }
}

/***************************************************************************//**
 * Initializes the calibration of the DCDC Coulomb Counter.
 *
 * @note The coulomb counter should be calibrated to determine the
 * charge per pulse, both for EM0/1 and for EM2/3 settings of the DC-DC.
 ******************************************************************************/
void sl_hal_dcdc_coulomb_counter_cal_init(sl_hal_dcdc_coulomb_counter_calibration_config_t config)
{
  CMU_ClockEnable(cmuClock_PRS, true);

  if (prs_channel == -1) {
    prs_channel = PRS_GetFreeChannel(prsTypeAsync);

    /* Channel number >= 0 if an unused PRS channel was found. */
    /* If no free PRS channel was found then -1 is returned. */
    if (prs_channel == -1) {
      EFM_ASSERT(false);
    }

    /* Configure an asynchronous PRS channel */
    /* to route the DCDC MONO70NSANA producer to the CMU CALDN consumer. */
    PRS_SourceAsyncSignalSet(prs_channel, PRS_ASYNC_CH_CTRL_SOURCESEL_DCDC, PRS_ASYNC_CH_CTRL_SIGSEL_DCDCMONO70NSANA);
    PRS_ConnectConsumer(prs_channel, prsTypeAsync, prsConsumerCMU_CALDN);
  }

  /* Setup the calibration circuit: */
  /*  - HFXO is clocking up-counter. */
  /*  - PRS CMU_CALDN consumer is clocking down-counter. */
  CMU_CalibrateConfig(config.cal_count, cmuSelect_PRS, config.reference_clk);
  CMU_CalibrateCont(false);

  /* Enable the desired calibration load. */
  sl_hal_dcdc_coulomb_counter_set_cal_load_level(config.cal_emode, config.cal_load_level);
  sl_hal_dcdc_coulomb_counter_enable_cal_load();

  /* Wait for at least one DC-DC pulse to settle DC-DC. */
  DCDC->IF_CLR = DCDC_IF_REGULATION;
  while ((DCDC->IF & DCDC_IF_REGULATION) == 0U) {
    /* Wait for DCDC to complete it's startup. */
  }

  /* Clear any pending calibration flags. */
  CMU->IF_CLR = CMU_IF_CALRDY;
  DCDC->CCCALCTRL_CLR = DCDC_CCCALCTRL_CCCALHALT;
}

/***************************************************************************//**
 * Starts DCDC_COULOMB_COUNTER calibration sequence.
 ******************************************************************************/
void sl_hal_dcdc_coulomb_counter_cal_start(void)
{
  /* Start the up counter. */
  CMU_CalibrateStart();
}

/***************************************************************************//**
 * Stops DCDC_COULOMB_COUNTER calibration sequence.
 ******************************************************************************/
void sl_hal_dcdc_coulomb_counter_cal_stop(void)
{
  CMU_CalibrateStop();

  sl_hal_dcdc_coulomb_counter_disable_cal_load();
}

/***************************************************************************//**
 * Sets the calibration load level.
 ******************************************************************************/
void sl_hal_dcdc_coulomb_counter_set_cal_load_level(sl_hal_dcdc_coulomb_counter_emode_t emode,
                                                    sl_hal_dcdc_coulomb_counter_calibration_load_level_t load_level)
{
  /* Set load level. */
  DCDC->CCCALCTRL = (DCDC->CCCALCTRL & ~(_DCDC_CCCALCTRL_CCLVL_MASK))
                    | ((load_level << _DCDC_CCCALCTRL_CCLVL_SHIFT) & _DCDC_CCCALCTRL_CCLVL_MASK);

  EMU_DCDCSync(_DCDC_SYNCBUSY_MASK);
  /* Adjust DCDC when calibrating for EM2. */
  if (emode == SL_HAL_DCDC_COULOMB_COUNTER_EM2) {
    /* Forces DCDC to use EM23CTRL0.IPKVAL peak current settings in EM0. */
    DCDC->CCCALCTRL_SET = DCDC_CCCALCTRL_CCCALEM2;
  } else {
    DCDC->CCCALCTRL_CLR = DCDC_CCCALCTRL_CCCALEM2;
  }
}

/***************************************************************************//**
 * Enables the calibration load.
 ******************************************************************************/
void sl_hal_dcdc_coulomb_counter_enable_cal_load(void)
{
  DCDC->CCCALCTRL_SET = DCDC_CCCALCTRL_CCLOADEN;
}

/***************************************************************************//**
 * Disables the calibration load.
 ******************************************************************************/
void sl_hal_dcdc_coulomb_counter_disable_cal_load(void)
{
  DCDC->CCCALCTRL_CLR = DCDC_CCCALCTRL_CCLOADEN;
}

/***************************************************************************//**
 * Gets the calibration load current from the stored value
 * in DEVINFO as measured during production testing.
 ******************************************************************************/
uint16_t sl_hal_dcdc_coulomb_counter_get_cal_load_current(sl_hal_dcdc_coulomb_counter_calibration_load_level_t load_level)
{
  uint16_t ccload = 0U;

  switch (load_level) {
    case SL_HAL_DCDC_COULOMB_COUNTER_CAL_LOAD0:
      ccload = (DEVINFO->CCLOAD10 & _DEVINFO_CCLOAD10_CCLOAD0_MASK)
               >> _DEVINFO_CCLOAD10_CCLOAD0_SHIFT;
      break;

    case SL_HAL_DCDC_COULOMB_COUNTER_CAL_LOAD1:
      ccload = (DEVINFO->CCLOAD10 & _DEVINFO_CCLOAD10_CCLOAD1_MASK)
               >> _DEVINFO_CCLOAD10_CCLOAD1_SHIFT;
      break;

    case SL_HAL_DCDC_COULOMB_COUNTER_CAL_LOAD2:
      ccload = (DEVINFO->CCLOAD32 & _DEVINFO_CCLOAD32_CCLOAD2_MASK)
               >> _DEVINFO_CCLOAD32_CCLOAD2_SHIFT;
      break;

    case SL_HAL_DCDC_COULOMB_COUNTER_CAL_LOAD3:
      ccload = (DEVINFO->CCLOAD32 & _DEVINFO_CCLOAD32_CCLOAD3_MASK)
               >> _DEVINFO_CCLOAD32_CCLOAD3_SHIFT;
      break;

    case SL_HAL_DCDC_COULOMB_COUNTER_CAL_LOAD4:
      ccload = (DEVINFO->CCLOAD54 & _DEVINFO_CCLOAD54_CCLOAD4_MASK)
               >> _DEVINFO_CCLOAD54_CCLOAD4_SHIFT;
      break;

    case SL_HAL_DCDC_COULOMB_COUNTER_CAL_LOAD5:
      ccload = (DEVINFO->CCLOAD54 & _DEVINFO_CCLOAD54_CCLOAD5_MASK)
               >> _DEVINFO_CCLOAD54_CCLOAD5_SHIFT;
      break;

    case SL_HAL_DCDC_COULOMB_COUNTER_CAL_LOAD6:
      ccload = (DEVINFO->CCLOAD76 & _DEVINFO_CCLOAD76_CCLOAD6_MASK)
               >> _DEVINFO_CCLOAD76_CCLOAD6_SHIFT;
      break;

    case SL_HAL_DCDC_COULOMB_COUNTER_CAL_LOAD7:
      ccload = (DEVINFO->CCLOAD76 & _DEVINFO_CCLOAD76_CCLOAD7_MASK)
               >> _DEVINFO_CCLOAD76_CCLOAD7_SHIFT;
      break;

    default:
      EFM_ASSERT(false);
  }

  /* Make sure calibration load setting was measured during production test. */
  EFM_ASSERT(ccload < (_DEVINFO_CCLOAD10_CCLOAD0_MASK >> _DEVINFO_CCLOAD10_CCLOAD0_SHIFT));

  return ccload;
}

/***************************************************************************//**
 * Gets the frequency (in Hz) of the CMU Calibration Up-Counter source.
 *
 * @note A high-frequency oscillator source of known frequency (fHF)
 * is used to time pulses from the DC-DC and establish the charge per pulse.
 ******************************************************************************/
uint32_t sl_hal_dcdc_coulomb_counter_get_cal_reference_freq(void)
{
  uint32_t freq = 0U;
  uint8_t upsel = _CMU_CALCTRL_UPSEL_DISABLED;

  upsel = (CMU->CALCTRL & _CMU_CALCTRL_UPSEL_MASK) >> _CMU_CALCTRL_UPSEL_SHIFT;

  switch (upsel) {
    case _CMU_CALCTRL_UPSEL_PRS:
      freq =  CMU_ClockFreqGet(cmuClock_PRS);
      break;

    case _CMU_CALCTRL_UPSEL_HFXO:
      freq  = SystemHFXOClockGet();
      break;

    case _CMU_CALCTRL_UPSEL_LFXO:
      freq = SystemLFXOClockGet();
      break;

    case _CMU_CALCTRL_UPSEL_HFRCODPLL:
      freq = SystemHFRCODPLLClockGet();
      break;

    case _CMU_CALCTRL_UPSEL_FSRCO:
      freq = SystemFSRCOClockGet();
      break;

    case _CMU_CALCTRL_UPSEL_LFRCO:
      freq = SystemLFRCOClockGet();
      break;

    case _CMU_CALCTRL_UPSEL_ULFRCO:
      freq = SystemULFRCOClockGet();
      break;

    case _CMU_CALCTRL_UPSEL_DISABLED:
    default:
      EFM_ASSERT(false);
  }

  return freq;
}

/** @} (end addtogroup dcdccoulombcounter) */
#endif /* defined(DCDC_COUNT) && (DCDC_COUNT > 0) && defined(DCDC_CCCTRL_CCEN) */
