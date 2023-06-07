/***************************************************************************//**
 * @file
 * @brief ESL Tag core built-in battery measurement with ADC.
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

#if (ESL_TAG_BUILTIN_BATTERY_MEASURE_ENABLE == 1) && defined (ADC_PRESENT)

// 1MHz ADC sample frequency will be enough
#define CLK_ADC_FREQ            1000000

// ADC conversion result maximum value
#define ADC_RESULT_MAX          0xFFF

// Raw ADC conversion result
static volatile uint32_t        sample;

// backup for ADC Vref value in milli Volts unit - using internal Vref 5V
static const uint32_t           vref_mv = 5000;

sl_status_t esl_sensor_battery_read(void)
{
  // set an implausible value until the conversion is finished
  sample = ESL_TAG_BATTERY_LEVEL_UNKNOWN;

  // re-enable ADC clock
  CMU_ClockEnable(cmuClock_ADC0, true);

  // start next ADC conversion
  ADC_Start(ADC0, adcStartSingle);

  // only the WEAK implementation returns an error
  return SL_STATUS_OK;
}

sl_status_t esl_sensor_battery_init(void)
{
  // enable ADC0 clock
  CMU_ClockEnable(cmuClock_ADC0, true);

  // declare init structs
  ADC_Init_TypeDef init = ADC_INIT_DEFAULT;
  // use single ended default at 12-bit resolution, select Vref later
  ADC_InitSingle_TypeDef init_single = ADC_INITSINGLE_DEFAULT;

  // modify init structs and initialize
  init.prescale = ADC_PrescaleCalc(CLK_ADC_FREQ, 0);
  init.timebase = ADC_TimebaseCalc(0);

  // set acquisition time to meet minimum requirements
  init_single.acqTime = adcAcqTime4;
  // select 5V internal reference
  init_single.reference = adcRef5VDIFF;

  // select ADC input
  init_single.posSel = adcPosSelAVDD;

  ADC_Init(ADC0, &init);
  ADC_InitSingle(ADC0, &init_single);

  // enable ADC Single Conversion Complete interrupt
  ADC_IntEnable(ADC0, ADC_IEN_SINGLE);

  // enable ADC interrupts
  NVIC_ClearPendingIRQ(ADC0_IRQn);
  NVIC_EnableIRQ(ADC0_IRQn);

  return esl_sensor_battery_read();
}

void ADC0_IRQHandler(void)
{
  // get ADC result
  sample = ADC_DataSingleGet(ADC0);

  ADC0->CMD = ADC_CMD_SINGLESTOP | ADC_CMD_SCANSTOP;
  // clear interrupt flag
  ADC0->IFC = _ADC_IFC_MASK;

  // clear data FIFOs to allow enter EM2 after single converion
  #if defined(_ADC_SINGLEFIFOCLEAR_MASK)
  ADC0->SINGLEFIFOCLEAR |= ADC_SINGLEFIFOCLEAR_SINGLEFIFOCLEAR;
  #endif // defined(_ADC_SINGLEFIFOCLEAR_MASK)

  // disable clock to save more power until the next conversion
  CMU_ClockEnable(cmuClock_ADC0, false);
}

uint32_t esl_sensor_get_battery_voltage_mv(void)
{
  uint32_t battery_millivolts = ESL_TAG_BATTERY_LEVEL_UNKNOWN;
  CORE_DECLARE_IRQ_STATE;

  CORE_ENTER_CRITICAL();
  if (sample != ESL_TAG_BATTERY_LEVEL_UNKNOWN) {
    // for single-ended conversions, the result can range from 0 to
    // +Vref, i.e., for Vref = adcRef5V = 5.0 V the value 0xFFF represents the
    // full scale value of 5.0 V. Since our input is AVDD, the actual battery
    // value can be calculated as follows (with rounding correction for integer
    // division)
    battery_millivolts = ((sample * vref_mv) + (ADC_RESULT_MAX / 2))
                         / ADC_RESULT_MAX;
  }
  CORE_EXIT_CRITICAL();

  return battery_millivolts;
}
#endif // (ESL_TAG_BUILTIN_BATTERY_MEASURE_ENABLE == 1) && defined (ADC_PRESENT)
