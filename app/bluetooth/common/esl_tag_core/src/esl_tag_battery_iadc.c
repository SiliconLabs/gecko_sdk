/***************************************************************************//**
 * @file
 * @brief ESL Tag core built-in battery measurement with IADC.
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
#include "em_cmu.h"
#include "em_common.h"
#include "esl_tag_core_config.h"
#include "esl_tag_battery_internal.h"

#if (ESL_TAG_BUILTIN_BATTERY_MEASURE_ENABLE == 1) && defined (IADC_PRESENT)

// set 2MHz ADC base clock for reduced current consumption
#define CLK_SRC_ADC_FREQ        2000000

// 1MHz ADC sample frequency will be enough
#define CLK_ADC_FREQ            1000000

// ADC conversion result maximum value
#define ADC_RESULT_MAX          0xFFF

// Raw IADC conversion result
static volatile IADC_Result_t   sample;

// backup for IADC Vref value in milli Volts unit
static uint32_t                 vref_mv;

sl_status_t esl_sensor_battery_read(void)
{
  // set an implausible value until the conversion is finished
  sample.data = ESL_TAG_BATTERY_LEVEL_UNKNOWN;

  // re-enable the peripheral clock
  CMU_ClockEnable(cmuClock_IADC0, true);
  // re-enable IADC0
  IADC0->EN_SET = IADC_EN_EN;

  IADC_command(IADC0, iadcCmdStartSingle);

  // only the WEAK implementation returns an error
  return SL_STATUS_OK;
}

sl_status_t esl_sensor_battery_init(void)
{
  // declare IADC initialization structures
  IADC_Init_t init = IADC_INIT_DEFAULT;
  IADC_AllConfigs_t init_all_configs = IADC_ALLCONFIGS_DEFAULT;
  IADC_InitSingle_t init_single = IADC_INITSINGLE_DEFAULT;

  // single input structure
  IADC_SingleInput_t single_input = IADC_SINGLEINPUT_DEFAULT;
  CMU_ClockEnable(cmuClock_IADC0, true);

  // use the FSRC0 as the IADC clock so it can run in EM2
  CMU_CLOCK_SELECT_SET(IADCCLK, FSRCO);

  // set the prescaler needed for the intended IADC clock frequency
  init.srcClkPrescale = IADC_calcSrcClkPrescale(IADC0, CLK_SRC_ADC_FREQ, 0);

  // Shutdown between conversions to reduce current
  init.warmup = iadcWarmupNormal;

  // select 2x oversampling which implicitly generates 12-bit results
  init_all_configs.configs[0].osrHighSpeed = iadcCfgOsrHighSpeed2x;

  // set derive the intended CLK_ADC frequency.
  init_all_configs.configs[0].adcClkPrescale = IADC_calcAdcClkPrescale(IADC0,
                                                                       CLK_ADC_FREQ,
                                                                       0,
                                                                       iadcCfgModeNormal,
                                                                       init.srcClkPrescale);

  // the following will actually select AVDD/4 to measure, according to RM
  single_input.posInput   = iadcPosInputAvdd;

  // store vref value for later use
  vref_mv = init_all_configs.configs[0].vRef;

  // initialize IADC
  IADC_init(IADC0, &init, &init_all_configs);

  // initialize a single-channel conversion
  IADC_initSingle(IADC0, &init_single, &single_input);

  // clear any previous interrupt flags
  IADC_clearInt(IADC0, _IADC_IF_MASK);

  // enable single-channel done interrupts
  IADC_enableInt(IADC0, IADC_IEN_SINGLEDONE);

  // enable IADC interrupts
  NVIC_ClearPendingIRQ(IADC_IRQn);
  NVIC_EnableIRQ(IADC_IRQn);

  return esl_sensor_battery_read();
}

void IADC_IRQHandler(void)
{
  // read a result from the FIFO
  sample = IADC_pullSingleFifoResult(IADC0);

  // clear the interrupt flag
  IADC_clearInt(IADC0, IADC_IF_SINGLEDONE);
  #if defined(IADC_STATUS_SYNCBUSY)
  while ((IADC0->STATUS & IADC_STATUS_SYNCBUSY) != 0U) {
    // wait for synchronization to finish before disable
  }
  #endif // defined(IADC_STATUS_SYNCBUSY)
  // to reduce power consumption to the limits: disable IADC0 in EM2
  IADC0->EN_CLR = IADC_EN_EN;

  #if defined _IADC_EN_DISABLING_MASK && defined IADC_EN_DISABLING
  // wait for IADC to disable on some MCUs, e.g. on BG24
  while ((IADC0->EN & _IADC_EN_DISABLING_MASK) == IADC_EN_DISABLING) ;
  #endif // defined _IADC_EN_DISABLING_MASK && defined IADC_EN_DISABLING

  // and disable the peripheral clock too after every single conversion
  CMU_ClockEnable(cmuClock_IADC0, false);
}

uint32_t esl_sensor_get_battery_voltage_mv(void)
{
  uint32_t battery_millivolts = ESL_TAG_BATTERY_LEVEL_UNKNOWN;
  CORE_DECLARE_IRQ_STATE;

  CORE_ENTER_CRITICAL();
  if (sample.data != ESL_TAG_BATTERY_LEVEL_UNKNOWN) {
    // for single-ended conversions, the result can range from 0 to
    // +Vref, i.e., for Vref = VrefInt = 1.21 V the value 0xFFF represents the
    // full scale value of 1.21 V. Since our input is AVDD / 4, the actual
    // battery value can be calculated as follows (with rounding correction for
    // integer division)
    battery_millivolts = ((4 * sample.data * vref_mv) + (ADC_RESULT_MAX / 2))
                         / ADC_RESULT_MAX;
  }
  CORE_EXIT_CRITICAL();

  return battery_millivolts;
}
#endif // (ESL_TAG_BUILTIN_BATTERY_MEASURE_ENABLE == 1) && defined (IADC_PRESENT)
