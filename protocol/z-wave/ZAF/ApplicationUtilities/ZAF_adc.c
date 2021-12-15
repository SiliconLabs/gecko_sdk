/**
*
* @file
* @brief ADC utility functions
*
* @copyright 2018 Silicon Laboratories Inc.
*
*/

#include "ZAF_adc.h"
#include <em_cmu.h>
#ifdef ZWAVE_SERIES_800
#include <em_iadc.h>
#else
#include <em_adc.h>
#endif

#ifdef ZWAVE_SERIES_700
static void ADC_Input_Select(ADC_PosSel_TypeDef input)
{

  ADC_InitSingle_TypeDef singleInit = ADC_INITSINGLE_DEFAULT;

  // Init for single conversion use, use 5V reference
  singleInit.reference  = adcRef5V;
  singleInit.posSel     = input;
  singleInit.resolution = adcRes12Bit;
  singleInit.acqTime    = adcAcqTime256;

  ADC_InitSingle(ADC0, &singleInit);

}
#endif
#ifdef ZWAVE_SERIES_800
static void ADC_Input_Select(IADC_PosInput_t input)
{
  IADC_InitSingle_t initSingle   = IADC_INITSINGLE_DEFAULT;
  IADC_SingleInput_t singleInput = IADC_SINGLEINPUT_DEFAULT;
  singleInput.negInput = iadcNegInputGnd;
  singleInput.posInput = input; // the positive input (avdd) is scaled down by 4
  IADC_initSingle(IADC0, &initSingle, &singleInput);
}
#endif

uint32_t ZAF_ADC_Measure_VSupply(void)
{
  uint32_t sampleAVDD;
#ifdef ZWAVE_SERIES_700
  // Measure AVDD (battery supply voltage level)
  ADC_Input_Select(adcPosSelAVDD);
  ADC_Start(ADC0, adcStartSingle);
  while (ADC0->STATUS & ADC_STATUS_SINGLEACT) ;
  sampleAVDD = ADC_DataSingleGet(ADC0);

  // Convert to mV (5V ref and 12 bit resolution)
  sampleAVDD = (sampleAVDD * 5000) / 4095;
#endif
#ifdef ZWAVE_SERIES_800
  // Measure AVDD (battery supply voltage level)
  ADC_Input_Select(iadcPosInputAvdd);
  IADC_command(IADC0,iadcCmdStartSingle);
  while (IADC0->SINGLEFIFOSTAT == 0) ;
  sampleAVDD = IADC_pullSingleFifoData(IADC0);

  // Convert to mV (1.21V ref and 12 bit resolution).
  // Also we scale the sample up by 4 since the input was scaled down by 4
  sampleAVDD = ((sampleAVDD * 1210 ) / 4095) * 4 ;

#endif
  return sampleAVDD;
}

void ZAF_ADC_Enable(void)
{
#ifdef ZWAVE_SERIES_700
   ADC_Init_TypeDef adcInit = ADC_INIT_DEFAULT;

   // Enable ADC clock
   CMU_ClockEnable(cmuClock_ADC0, true);

   // Setup ADC
   adcInit.timebase = ADC_TimebaseCalc(0);
   // Set ADC clock to 7 MHz, use default HFPERCLK
   adcInit.prescale = ADC_PrescaleCalc(7000000, 0);
   ADC_Init(ADC0, &adcInit);
#endif
#ifdef ZWAVE_SERIES_800
  /*800 sereis has only 1.21 reference volatge therefore we need to scale down the input voltage by 4*/
  IADC_Init_t init               = IADC_INIT_DEFAULT;
  IADC_AllConfigs_t allConfigs   = IADC_ALLCONFIGS_DEFAULT;
  CMU_ClockEnable(cmuClock_IADC0, true);
  IADC_init(IADC0, &init, &allConfigs);
#endif
}

void ZAF_ADC_Disable(void)
{
#ifdef ZWAVE_SERIES_700
   ADC_Reset(ADC0);
   // Disable ADC clock
   CMU_ClockEnable(cmuClock_ADC0, false);
#endif
#ifdef ZWAVE_SERIES_800
   IADC_reset(IADC0);
   // Disable IADC clock
   CMU_ClockEnable(cmuClock_IADC0, false);
#endif
}

