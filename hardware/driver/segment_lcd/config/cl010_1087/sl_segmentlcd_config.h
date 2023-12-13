/***************************************************************************//**
 * @file
 * @brief Segment LCD Config for the LCD module CL010_1087
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

#ifndef SL_SEGMENTLCD_CONFIG_H
#define SL_SEGMENTLCD_CONFIG_H

#include "em_lcd.h"
#include "sl_segmentlcd_pin_config.h"

#ifdef __cplusplus
extern "C" {
#endif

// Define the LCD module type
#define SL_SEGMENT_LCD_MODULE_CL010_1087
// *********************************************
//
// Board/device specific config
//
// *********************************************

// <<< Use Configuration Wizard in Context Menu >>>

// <h>Frame Rate
// LCD Controller Prescaler (divide LCDCLK / 64)
// LCDCLK_pre = 512 Hz
// Set FDIV=0, means 512/1 = 512 Hz
// With octaplex mode, 512/16 => 32 Hz Frame Rate

// <o SL_SEGMENT_LCD_CLK_PRE> LCD Controller prescaler
// <i> Default: 64
#define SL_SEGMENT_LCD_CLK_PRE          64

// <o SL_SEGMENT_LCD_FRAME_RATE_DIV> LCD frame rate divisor
// <i> Default: 0
#define SL_SEGMENT_LCD_FRAME_RATE_DIV   0
// </h> end Frame Rate

// <h> LDMA settings
// <o SL_SEGMENT_LCD_LDMA_MODE> LDMA mode of operation
// <lcdDmaModeDisable=> No DMA requests are generated 
// <lcdDmaModeFrameCounterEvent=> DMA request on frame counter event
// <lcdDmaModeDisplayEvent=> DMA request on display counter event
// <i> Default: lcdDmaModeDisable
#define SL_SEGMENT_LCD_LDMA_MODE      lcdDmaModeDisable

// <o SL_SEGMENT_LCD_BACFG_FCPRESC> Frame Counter Clock Prescaler
// FC-CLK = FrameRate (Hz) / this factor.
// <lcdFCPrescDiv1=> Prescale Div 1 
// <lcdFCPrescDiv2=> Prescale Div 2
// <lcdFCPrescDiv4=> Prescale Div 4
// <lcdFCPrescDiv8=> Prescale Div 8
// <i> Default: lcdFCPrescDiv1
#define SL_SEGMENT_LCD_BACFG_FCPRESC   lcdFCPrescDiv1
// </h> end LDMA settings

// <o SL_SEGMENT_LCD_CONTRAST> LCD contrast
// <i> Default: 15
#define SL_SEGMENT_LCD_CONTRAST   15

// LCD boost contrast
#define SL_SEGMENT_LCD_BOOST_CONTRAST   0x2

// <o SL_SEGMENT_LCD_ENABLE_CONTROLLER> Enable at initialization
// <false=> Disabled
// <true=> Enabled
// <i> Default: true
#define SL_SEGMENT_LCD_ENABLE_CONTROLLER      true

// <o SL_SEGMENT_LCD_MUX_CONFIG> Mux configuration
// <lcdMuxStatic=> Static 
// <lcdMuxDuplex=> Duplex (1/2 duty cycle)
// <lcdMuxTriplex=> Triplex (1/3 duty cycle)
// <lcdMuxQuadruplex=> Quadruplex (1/4 duty cycle)
// <lcdMuxSextaplex=> Sextaplex (1/6 duty cycle)
// <lcdMuxOctaplex=> Octaplex (1/8 duty cycle)
// <i> Default: lcdMuxOctaplex
#define SL_SEGMENT_LCD_MUX_CONFIG             lcdMuxOctaplex

// <o SL_SEGMENT_LCD_WAVE_TYPE> Wave type
// <lcdWaveLowPower=> Low power
// <lcdWaveNormal=> Regular
// <i> Default: lcdWaveLowPower
#define SL_SEGMENT_LCD_WAVE_TYPE              lcdWaveLowPower

// <o SL_SEGMENT_LCD_BIAS_SETTING> Bias setting
// <lcdBiasStatic=> Static (2 levels)
// <lcdBiasOneHalf=> 1/2 bias (3 levels)
// <lcdBiasOneThird=> 1/3 bias (4 levels)
// <lcdBiasOneFourth=> 1/4 bias (5 levels)
// <i> Default: lcdBiasOneFourth
#define SL_SEGMENT_LCD_BIAS_SETTING           lcdBiasOneFourth

// <o SL_SEGMENT_LCD_MODE_OPERATION> Mode of operation
// <lcdModeStepDown=> Mode step down
// <lcdModeChargePump=> Mode charge pump
// <i> Default: lcdModeChargePump
#define SL_SEGMENT_LCD_MODE_OPERATION         lcdModeChargePump

// <o SL_SEGMENT_LCD_CHARGE_REDIS_CYCL> Charge redistribution cycles
// <lcdChargeRedistributionDisable=> Disabled
// <lcdChargeRedistributionEnable=> 1 prescaled low frequency
// <lcdChargeRedistributionTwoCycle=> 2 prescaled low frequency
// <lcdChargeRedistributionThreeCycle=> 3 prescaled low frequency
// <lcdChargeRedistributionFourCycle=> 4 prescaled low frequency
// <i> Default: lcdChargeRedistributionDisable
#define SL_SEGMENT_LCD_CHARGE_REDIS_CYCL       lcdChargeRedistributionDisable

// <<< end of configuration section >>>

// LCD initialization structure
#define SL_SEGMENT_LCD_INIT_DEF             \
  { SL_SEGMENT_LCD_ENABLE_CONTROLLER,       \
    SL_SEGMENT_LCD_MUX_CONFIG,              \
    SL_SEGMENT_LCD_BIAS_SETTING,            \
    SL_SEGMENT_LCD_WAVE_TYPE,               \
    SL_SEGMENT_LCD_MODE_OPERATION,          \
    SL_SEGMENT_LCD_CHARGE_REDIS_CYCL,       \
    SL_SEGMENT_LCD_FRAME_RATE_DIV,          \
    SL_SEGMENT_LCD_CONTRAST,                \
    SL_SEGMENT_LCD_CLK_PRE                  \
  }

// *********************************************
//
// General LCD_MODULE_CL010_1087 config
//
// *********************************************

/** Range of symbols available on display */
typedef enum {
  SL_LCD_SYMBOL_GECKO,
  SL_LCD_SYMBOL_ANT,
  SL_LCD_SYMBOL_PAD0,
  SL_LCD_SYMBOL_PAD1,
  SL_LCD_SYMBOL_EFM32,
  SL_LCD_SYMBOL_MINUS,
  SL_LCD_SYMBOL_COL3,
  SL_LCD_SYMBOL_COL5,
  SL_LCD_SYMBOL_COL10,
  SL_LCD_SYMBOL_DEGC,
  SL_LCD_SYMBOL_DEGF,
  SL_LCD_SYMBOL_DP2,
  SL_LCD_SYMBOL_DP3,
  SL_LCD_SYMBOL_DP4,
  SL_LCD_SYMBOL_DP5,
  SL_LCD_SYMBOL_DP6,
  SL_LCD_SYMBOL_DP10,
} sl_segment_lcd_symbol_t;

#define SL_LCD_SYMBOL_GECKO_COM    SL_SEGMENT_LCD_COM_C06
#define SL_LCD_SYMBOL_GECKO_SEG    SL_SEGMENT_LCD_SEG_S00
#define SL_LCD_SYMBOL_ANT_COM      SL_SEGMENT_LCD_COM_C07
#define SL_LCD_SYMBOL_ANT_SEG      SL_SEGMENT_LCD_SEG_S12
#define SL_LCD_SYMBOL_PAD0_COM     SL_SEGMENT_LCD_COM_C04
#define SL_LCD_SYMBOL_PAD0_SEG     SL_SEGMENT_LCD_SEG_S19
#define SL_LCD_SYMBOL_PAD1_COM     SL_SEGMENT_LCD_COM_C05
#define SL_LCD_SYMBOL_PAD1_SEG     SL_SEGMENT_LCD_SEG_S00
#define SL_LCD_SYMBOL_EFM32_COM    SL_SEGMENT_LCD_COM_C07
#define SL_LCD_SYMBOL_EFM32_SEG    SL_SEGMENT_LCD_SEG_S08
#define SL_LCD_SYMBOL_MINUS_COM    SL_SEGMENT_LCD_COM_C04
#define SL_LCD_SYMBOL_MINUS_SEG    SL_SEGMENT_LCD_SEG_S00
#define SL_LCD_SYMBOL_COL3_COM     SL_SEGMENT_LCD_COM_C03
#define SL_LCD_SYMBOL_COL3_SEG     SL_SEGMENT_LCD_SEG_S00
#define SL_LCD_SYMBOL_COL5_COM     SL_SEGMENT_LCD_COM_C07
#define SL_LCD_SYMBOL_COL5_SEG     SL_SEGMENT_LCD_SEG_S10
#define SL_LCD_SYMBOL_COL10_COM    SL_SEGMENT_LCD_COM_C02
#define SL_LCD_SYMBOL_COL10_SEG    SL_SEGMENT_LCD_SEG_S19
#define SL_LCD_SYMBOL_DEGC_COM     SL_SEGMENT_LCD_COM_C07
#define SL_LCD_SYMBOL_DEGC_SEG     SL_SEGMENT_LCD_SEG_S14
#define SL_LCD_SYMBOL_DEGF_COM     SL_SEGMENT_LCD_COM_C07
#define SL_LCD_SYMBOL_DEGF_SEG     SL_SEGMENT_LCD_SEG_S15
#define SL_LCD_SYMBOL_DP2_COM      SL_SEGMENT_LCD_COM_C00
#define SL_LCD_SYMBOL_DP2_SEG      SL_SEGMENT_LCD_SEG_S00
#define SL_LCD_SYMBOL_DP3_COM      SL_SEGMENT_LCD_COM_C02
#define SL_LCD_SYMBOL_DP3_SEG      SL_SEGMENT_LCD_SEG_S00
#define SL_LCD_SYMBOL_DP4_COM      SL_SEGMENT_LCD_COM_C01
#define SL_LCD_SYMBOL_DP4_SEG      SL_SEGMENT_LCD_SEG_S00
#define SL_LCD_SYMBOL_DP5_COM      SL_SEGMENT_LCD_COM_C00
#define SL_LCD_SYMBOL_DP5_SEG      SL_SEGMENT_LCD_SEG_S09
#define SL_LCD_SYMBOL_DP6_COM      SL_SEGMENT_LCD_COM_C00
#define SL_LCD_SYMBOL_DP6_SEG      SL_SEGMENT_LCD_SEG_S11
#define SL_LCD_SYMBOL_DP10_COM     SL_SEGMENT_LCD_COM_C03
#define SL_LCD_SYMBOL_DP10_SEG     SL_SEGMENT_LCD_SEG_S19

#define SL_SEGMENT_LCD_EFM_DISPLAY_TEXT    \
    .text        = {                                                                                                                                      \
          { /* 1 */                                                                                                                                       \
            .com[0] = SL_SEGMENT_LCD_COM_C06, .com[1] = SL_SEGMENT_LCD_COM_C06, .com[2] = SL_SEGMENT_LCD_COM_C02, .com[3] = SL_SEGMENT_LCD_COM_C00,       \
            .bit[0] = SL_SEGMENT_LCD_SEG_S01, .bit[1] = SL_SEGMENT_LCD_SEG_S02, .bit[2] = SL_SEGMENT_LCD_SEG_S02, .bit[3] = SL_SEGMENT_LCD_SEG_S02,       \
            .com[4] = SL_SEGMENT_LCD_COM_C00, .com[5] = SL_SEGMENT_LCD_COM_C04, .com[6] = SL_SEGMENT_LCD_COM_C03, .com[7] = SL_SEGMENT_LCD_COM_C05,       \
            .bit[4] = SL_SEGMENT_LCD_SEG_S01, .bit[5] = SL_SEGMENT_LCD_SEG_S01, .bit[6] = SL_SEGMENT_LCD_SEG_S01, .bit[7] = SL_SEGMENT_LCD_SEG_S01,       \
            .com[8] = SL_SEGMENT_LCD_COM_C04, .com[9] = SL_SEGMENT_LCD_COM_C05, .com[10] = SL_SEGMENT_LCD_COM_C03, .com[11] = SL_SEGMENT_LCD_COM_C01,     \
            .bit[8] = SL_SEGMENT_LCD_SEG_S02, .bit[9] = SL_SEGMENT_LCD_SEG_S02, .bit[10] = SL_SEGMENT_LCD_SEG_S02, .bit[11] = SL_SEGMENT_LCD_SEG_S02,     \
            .com[12] = SL_SEGMENT_LCD_COM_C02, .com[13] = SL_SEGMENT_LCD_COM_C01,                                                                         \
            .bit[12] = SL_SEGMENT_LCD_SEG_S01, .bit[13] = SL_SEGMENT_LCD_SEG_S01                                                                          \
          },                                                                                                                                              \
          { /* 2 */                                                                                                                                       \
            .com[0] = SL_SEGMENT_LCD_COM_C06, .com[1] = SL_SEGMENT_LCD_COM_C06, .com[2] = SL_SEGMENT_LCD_COM_C02, .com[3] = SL_SEGMENT_LCD_COM_C00,       \
            .bit[0] = SL_SEGMENT_LCD_SEG_S03, .bit[1] = SL_SEGMENT_LCD_SEG_S04, .bit[2] = SL_SEGMENT_LCD_SEG_S04, .bit[3] = SL_SEGMENT_LCD_SEG_S04,       \
            .com[4] = SL_SEGMENT_LCD_COM_C00, .com[5] = SL_SEGMENT_LCD_COM_C04, .com[6] = SL_SEGMENT_LCD_COM_C03, .com[7] = SL_SEGMENT_LCD_COM_C05,       \
            .bit[4] = SL_SEGMENT_LCD_SEG_S03, .bit[5] = SL_SEGMENT_LCD_SEG_S03, .bit[6] = SL_SEGMENT_LCD_SEG_S03, .bit[7] = SL_SEGMENT_LCD_SEG_S03,       \
            .com[8] = SL_SEGMENT_LCD_COM_C04, .com[9] = SL_SEGMENT_LCD_COM_C05, .com[10] = SL_SEGMENT_LCD_COM_C03, .com[11] = SL_SEGMENT_LCD_COM_C01,     \
            .bit[8] = SL_SEGMENT_LCD_SEG_S04, .bit[9] = SL_SEGMENT_LCD_SEG_S04, .bit[10] = SL_SEGMENT_LCD_SEG_S04, .bit[11] = SL_SEGMENT_LCD_SEG_S04,     \
            .com[12] = SL_SEGMENT_LCD_COM_C02, .com[13] = SL_SEGMENT_LCD_COM_C01,                                                                         \
            .bit[12] = SL_SEGMENT_LCD_SEG_S03, .bit[13] = SL_SEGMENT_LCD_SEG_S03                                                                          \
          },                                                                                                                                              \
          { /* 3 */                                                                                                                                       \
            .com[0] = SL_SEGMENT_LCD_COM_C06, .com[1] = SL_SEGMENT_LCD_COM_C06, .com[2] = SL_SEGMENT_LCD_COM_C02, .com[3] = SL_SEGMENT_LCD_COM_C00,       \
            .bit[0] = SL_SEGMENT_LCD_SEG_S05, .bit[1] = SL_SEGMENT_LCD_SEG_S06, .bit[2] = SL_SEGMENT_LCD_SEG_S06, .bit[3] = SL_SEGMENT_LCD_SEG_S06,       \
            .com[4] = SL_SEGMENT_LCD_COM_C00, .com[5] = SL_SEGMENT_LCD_COM_C04, .com[6] = SL_SEGMENT_LCD_COM_C03, .com[7] = SL_SEGMENT_LCD_COM_C05,       \
            .bit[4] = SL_SEGMENT_LCD_SEG_S05, .bit[5] = SL_SEGMENT_LCD_SEG_S05, .bit[6] = SL_SEGMENT_LCD_SEG_S05, .bit[7] = SL_SEGMENT_LCD_SEG_S05,       \
            .com[8] = SL_SEGMENT_LCD_COM_C04, .com[9] = SL_SEGMENT_LCD_COM_C05, .com[10] = SL_SEGMENT_LCD_COM_C03, .com[11] = SL_SEGMENT_LCD_COM_C01,     \
            .bit[8] = SL_SEGMENT_LCD_SEG_S06, .bit[9] = SL_SEGMENT_LCD_SEG_S06, .bit[10] = SL_SEGMENT_LCD_SEG_S06, .bit[11] = SL_SEGMENT_LCD_SEG_S06,     \
            .com[12] = SL_SEGMENT_LCD_COM_C02, .com[13] = SL_SEGMENT_LCD_COM_C01,                                                                         \
            .bit[12] = SL_SEGMENT_LCD_SEG_S05, .bit[13] = SL_SEGMENT_LCD_SEG_S05                                                                          \
          },                                                                                                                                              \
          { /* 4 */                                                                                                                                       \
            .com[0] = SL_SEGMENT_LCD_COM_C06, .com[1] = SL_SEGMENT_LCD_COM_C06, .com[2] = SL_SEGMENT_LCD_COM_C02, .com[3] = SL_SEGMENT_LCD_COM_C00,       \
            .bit[0] = SL_SEGMENT_LCD_SEG_S07, .bit[1] = SL_SEGMENT_LCD_SEG_S08, .bit[2] = SL_SEGMENT_LCD_SEG_S08, .bit[3] = SL_SEGMENT_LCD_SEG_S08,       \
            .com[4] = SL_SEGMENT_LCD_COM_C00, .com[5] = SL_SEGMENT_LCD_COM_C04, .com[6] = SL_SEGMENT_LCD_COM_C03, .com[7] = SL_SEGMENT_LCD_COM_C05,       \
            .bit[4] = SL_SEGMENT_LCD_SEG_S07, .bit[5] = SL_SEGMENT_LCD_SEG_S07, .bit[6] = SL_SEGMENT_LCD_SEG_S07, .bit[7] = SL_SEGMENT_LCD_SEG_S07,       \
            .com[8] = SL_SEGMENT_LCD_COM_C04, .com[9] = SL_SEGMENT_LCD_COM_C05, .com[10] = SL_SEGMENT_LCD_COM_C03, .com[11] = SL_SEGMENT_LCD_COM_C01,     \
            .bit[8] = SL_SEGMENT_LCD_SEG_S08, .bit[9] = SL_SEGMENT_LCD_SEG_S08, .bit[10] = SL_SEGMENT_LCD_SEG_S08, .bit[11] = SL_SEGMENT_LCD_SEG_S08,     \
            .com[12] = SL_SEGMENT_LCD_COM_C02, .com[13] = SL_SEGMENT_LCD_COM_C01,                                                                         \
            .bit[12] = SL_SEGMENT_LCD_SEG_S07, .bit[13] = SL_SEGMENT_LCD_SEG_S07                                                                          \
          },                                                                                                                                              \
          { /* 5 */                                                                                                                                       \
            .com[0] = SL_SEGMENT_LCD_COM_C07, .com[1] = SL_SEGMENT_LCD_COM_C06, .com[2] = SL_SEGMENT_LCD_COM_C02, .com[3] = SL_SEGMENT_LCD_COM_C00,       \
            .bit[0] = SL_SEGMENT_LCD_SEG_S09, .bit[1] = SL_SEGMENT_LCD_SEG_S10, .bit[2] = SL_SEGMENT_LCD_SEG_S10, .bit[3] = SL_SEGMENT_LCD_SEG_S10,       \
            .com[4] = SL_SEGMENT_LCD_COM_C01, .com[5] = SL_SEGMENT_LCD_COM_C05, .com[6] = SL_SEGMENT_LCD_COM_C04, .com[7] = SL_SEGMENT_LCD_COM_C06,       \
            .bit[4] = SL_SEGMENT_LCD_SEG_S09, .bit[5] = SL_SEGMENT_LCD_SEG_S09, .bit[6] = SL_SEGMENT_LCD_SEG_S09, .bit[7] = SL_SEGMENT_LCD_SEG_S09,       \
            .com[8] = SL_SEGMENT_LCD_COM_C04, .com[9] = SL_SEGMENT_LCD_COM_C05, .com[10] = SL_SEGMENT_LCD_COM_C03, .com[11] = SL_SEGMENT_LCD_COM_C01,     \
            .bit[8] = SL_SEGMENT_LCD_SEG_S10, .bit[9] = SL_SEGMENT_LCD_SEG_S10, .bit[10] = SL_SEGMENT_LCD_SEG_S10, .bit[11] = SL_SEGMENT_LCD_SEG_S10,     \
            .com[12] = SL_SEGMENT_LCD_COM_C03, .com[13] = SL_SEGMENT_LCD_COM_C02,                                                                         \
            .bit[12] = SL_SEGMENT_LCD_SEG_S09, .bit[13] = SL_SEGMENT_LCD_SEG_S09                                                                          \
          },                                                                                                                                              \
          { /* 6 */                                                                                                                                       \
            .com[0] = SL_SEGMENT_LCD_COM_C07, .com[1] = SL_SEGMENT_LCD_COM_C06, .com[2] = SL_SEGMENT_LCD_COM_C02, .com[3] = SL_SEGMENT_LCD_COM_C00,       \
            .bit[0] = SL_SEGMENT_LCD_SEG_S11, .bit[1] = SL_SEGMENT_LCD_SEG_S12, .bit[2] = SL_SEGMENT_LCD_SEG_S12, .bit[3] = SL_SEGMENT_LCD_SEG_S12,       \
            .com[4] = SL_SEGMENT_LCD_COM_C01, .com[5] = SL_SEGMENT_LCD_COM_C05, .com[6] = SL_SEGMENT_LCD_COM_C04, .com[7] = SL_SEGMENT_LCD_COM_C06,       \
            .bit[4] = SL_SEGMENT_LCD_SEG_S11, .bit[5] = SL_SEGMENT_LCD_SEG_S11, .bit[6] = SL_SEGMENT_LCD_SEG_S11, .bit[7] = SL_SEGMENT_LCD_SEG_S11,       \
            .com[8] = SL_SEGMENT_LCD_COM_C04, .com[9] = SL_SEGMENT_LCD_COM_C05, .com[10] = SL_SEGMENT_LCD_COM_C03, .com[11] = SL_SEGMENT_LCD_COM_C01,     \
            .bit[8] = SL_SEGMENT_LCD_SEG_S12, .bit[9] = SL_SEGMENT_LCD_SEG_S12, .bit[10] = SL_SEGMENT_LCD_SEG_S12, .bit[11] = SL_SEGMENT_LCD_SEG_S12,     \
            .com[12] = SL_SEGMENT_LCD_COM_C03, .com[13] = SL_SEGMENT_LCD_COM_C02,                                                                         \
            .bit[12] = SL_SEGMENT_LCD_SEG_S11, .bit[13] = SL_SEGMENT_LCD_SEG_S11                                                                          \
          },                                                                                                                                              \
          { /* 7 */                                                                                                                                       \
            .com[0] = SL_SEGMENT_LCD_COM_C06, .com[1] = SL_SEGMENT_LCD_COM_C06, .com[2] = SL_SEGMENT_LCD_COM_C02, .com[3] = SL_SEGMENT_LCD_COM_C00,       \
            .bit[0] = SL_SEGMENT_LCD_SEG_S13, .bit[1] = SL_SEGMENT_LCD_SEG_S14, .bit[2] = SL_SEGMENT_LCD_SEG_S14, .bit[3] = SL_SEGMENT_LCD_SEG_S14,       \
            .com[4] = SL_SEGMENT_LCD_COM_C00, .com[5] = SL_SEGMENT_LCD_COM_C04, .com[6] = SL_SEGMENT_LCD_COM_C03, .com[7] = SL_SEGMENT_LCD_COM_C05,       \
            .bit[4] = SL_SEGMENT_LCD_SEG_S13, .bit[5] = SL_SEGMENT_LCD_SEG_S13, .bit[6] = SL_SEGMENT_LCD_SEG_S13, .bit[7] = SL_SEGMENT_LCD_SEG_S13,       \
            .com[8] = SL_SEGMENT_LCD_COM_C04, .com[9] = SL_SEGMENT_LCD_COM_C05, .com[10] = SL_SEGMENT_LCD_COM_C03, .com[11] = SL_SEGMENT_LCD_COM_C01,     \
            .bit[8] = SL_SEGMENT_LCD_SEG_S14, .bit[9] = SL_SEGMENT_LCD_SEG_S14, .bit[10] = SL_SEGMENT_LCD_SEG_S14, .bit[11] = SL_SEGMENT_LCD_SEG_S14,     \
            .com[12] = SL_SEGMENT_LCD_COM_C02, .com[13] = SL_SEGMENT_LCD_COM_C01,                                                                         \
            .bit[12] = SL_SEGMENT_LCD_SEG_S13, .bit[13] = SL_SEGMENT_LCD_SEG_S13                                                                          \
          },                                                                                                                                              \
        }

#define SL_SEGMENT_LCD_EFM_DISPLAY_NUM    \
          .number      = {                                                                                                                                      \
                {                                                                                                                                               \
                  .com[0] = SL_SEGMENT_LCD_COM_C00, .com[1] = SL_SEGMENT_LCD_COM_C02, .com[2] = SL_SEGMENT_LCD_COM_C05, .com[3] = SL_SEGMENT_LCD_COM_C06,       \
                  .bit[0] = SL_SEGMENT_LCD_SEG_S15, .bit[1] = SL_SEGMENT_LCD_SEG_S15, .bit[2] = SL_SEGMENT_LCD_SEG_S15, .bit[3] = SL_SEGMENT_LCD_SEG_S15,       \
                  .com[4] = SL_SEGMENT_LCD_COM_C04, .com[5] = SL_SEGMENT_LCD_COM_C01, .com[6] = SL_SEGMENT_LCD_COM_C03,                                         \
                  .bit[4] = SL_SEGMENT_LCD_SEG_S15, .bit[5] = SL_SEGMENT_LCD_SEG_S15, .bit[6] = SL_SEGMENT_LCD_SEG_S15,                                         \
                },                                                                                                                                              \
                {                                                                                                                                               \
                  .com[0] = SL_SEGMENT_LCD_COM_C00, .com[1] = SL_SEGMENT_LCD_COM_C02, .com[2] = SL_SEGMENT_LCD_COM_C05, .com[3] = SL_SEGMENT_LCD_COM_C06,       \
                  .bit[0] = SL_SEGMENT_LCD_SEG_S16, .bit[1] = SL_SEGMENT_LCD_SEG_S16, .bit[2] = SL_SEGMENT_LCD_SEG_S16, .bit[3] = SL_SEGMENT_LCD_SEG_S16,       \
                  .com[4] = SL_SEGMENT_LCD_COM_C04, .com[5] = SL_SEGMENT_LCD_COM_C01, .com[6] = SL_SEGMENT_LCD_COM_C03,                                         \
                  .bit[4] = SL_SEGMENT_LCD_SEG_S16, .bit[5] = SL_SEGMENT_LCD_SEG_S16, .bit[6] = SL_SEGMENT_LCD_SEG_S16,                                         \
                },                                                                                                                                              \
                {                                                                                                                                               \
                  .com[0] = SL_SEGMENT_LCD_COM_C00, .com[1] = SL_SEGMENT_LCD_COM_C02, .com[2] = SL_SEGMENT_LCD_COM_C05, .com[3] = SL_SEGMENT_LCD_COM_C06,       \
                  .bit[0] = SL_SEGMENT_LCD_SEG_S17, .bit[1] = SL_SEGMENT_LCD_SEG_S17, .bit[2] = SL_SEGMENT_LCD_SEG_S17, .bit[3] = SL_SEGMENT_LCD_SEG_S17,       \
                  .com[4] = SL_SEGMENT_LCD_COM_C04, .com[5] = SL_SEGMENT_LCD_COM_C01, .com[6] = SL_SEGMENT_LCD_COM_C03,                                         \
                  .bit[4] = SL_SEGMENT_LCD_SEG_S17, .bit[5] = SL_SEGMENT_LCD_SEG_S17, .bit[6] = SL_SEGMENT_LCD_SEG_S17,                                         \
                },                                                                                                                                              \
                {                                                                                                                                               \
                  .com[0] = SL_SEGMENT_LCD_COM_C00, .com[1] = SL_SEGMENT_LCD_COM_C02, .com[2] = SL_SEGMENT_LCD_COM_C05, .com[3] = SL_SEGMENT_LCD_COM_C06,       \
                  .bit[0] = SL_SEGMENT_LCD_SEG_S18, .bit[1] = SL_SEGMENT_LCD_SEG_S18, .bit[2] = SL_SEGMENT_LCD_SEG_S18, .bit[3] = SL_SEGMENT_LCD_SEG_S18,       \
                  .com[4] = SL_SEGMENT_LCD_COM_C04, .com[5] = SL_SEGMENT_LCD_COM_C01, .com[6] = SL_SEGMENT_LCD_COM_C03,                                         \
                  .bit[4] = SL_SEGMENT_LCD_SEG_S18, .bit[5] = SL_SEGMENT_LCD_SEG_S18, .bit[6] = SL_SEGMENT_LCD_SEG_S18,                                         \
                },                                                                                                                                              \
              }

#define SL_SEGMENT_LCD_EFM_DISPLAY_SYMBOL    \
            .emode       = {                                                                            \
              .com[0] = SL_SEGMENT_LCD_COM_C07, .bit[0] = SL_SEGMENT_LCD_SEG_S19,                       \
              .com[1] = SL_SEGMENT_LCD_COM_C06, .bit[1] = SL_SEGMENT_LCD_SEG_S19,                       \
              .com[2] = SL_SEGMENT_LCD_COM_C00, .bit[2] = SL_SEGMENT_LCD_SEG_S19,                       \
              .com[3] = SL_SEGMENT_LCD_COM_C05, .bit[3] = SL_SEGMENT_LCD_SEG_S19,                       \
              .com[4] = SL_SEGMENT_LCD_COM_C01, .bit[4] = SL_SEGMENT_LCD_SEG_S19,                       \
            },                                                                                          \
            .aring       = {                                                                            \
              .com[0] = SL_SEGMENT_LCD_COM_C07, .bit[0] = SL_SEGMENT_LCD_SEG_S07,                       \
              .com[1] = SL_SEGMENT_LCD_COM_C07, .bit[1] = SL_SEGMENT_LCD_SEG_S06,                       \
              .com[2] = SL_SEGMENT_LCD_COM_C07, .bit[2] = SL_SEGMENT_LCD_SEG_S05,                       \
              .com[3] = SL_SEGMENT_LCD_COM_C07, .bit[3] = SL_SEGMENT_LCD_SEG_S04,                       \
              .com[4] = SL_SEGMENT_LCD_COM_C07, .bit[4] = SL_SEGMENT_LCD_SEG_S03,                       \
              .com[5] = SL_SEGMENT_LCD_COM_C07, .bit[5] = SL_SEGMENT_LCD_SEG_S02,                       \
              .com[6] = SL_SEGMENT_LCD_COM_C07, .bit[6] = SL_SEGMENT_LCD_SEG_S01,                       \
              .com[7] = SL_SEGMENT_LCD_COM_C07, .bit[7] = SL_SEGMENT_LCD_SEG_S00,                       \
            },                                                                                          \
            .battery     = {                                                                            \
              .com[0] = SL_SEGMENT_LCD_COM_C07, .bit[0] = SL_SEGMENT_LCD_SEG_S13,                       \
              .com[1] = SL_SEGMENT_LCD_COM_C07, .bit[1] = SL_SEGMENT_LCD_SEG_S17,                       \
              .com[2] = SL_SEGMENT_LCD_COM_C07, .bit[2] = SL_SEGMENT_LCD_SEG_S16,                       \
              .com[3] = SL_SEGMENT_LCD_COM_C07, .bit[3] = SL_SEGMENT_LCD_SEG_S18,                       \
            }

#define SL_SEGMENT_LCD_EFM_DISPLAY_TOP_BLOCK    \
          .top_blocks   = {                                                                                                                                     \
                { /* 1 */                                                                                                                                       \
                  .com[0] = SL_SEGMENT_LCD_COM_C06, .com[1] = SL_SEGMENT_LCD_COM_C06, .com[2] = SL_SEGMENT_LCD_COM_C04, .com[3] = SL_SEGMENT_LCD_COM_C03,       \
                  .bit[0] = SL_SEGMENT_LCD_SEG_S01, .bit[1] = SL_SEGMENT_LCD_SEG_S02, .bit[2] = SL_SEGMENT_LCD_SEG_S01, .bit[3] = SL_SEGMENT_LCD_SEG_S01,       \
                  .com[4] = SL_SEGMENT_LCD_COM_C03, .com[5] = SL_SEGMENT_LCD_COM_C05, .com[6] = SL_SEGMENT_LCD_COM_C04, .com[7] = SL_SEGMENT_LCD_COM_C05,       \
                  .bit[4] = SL_SEGMENT_LCD_SEG_S02, .bit[5] = SL_SEGMENT_LCD_SEG_S01, .bit[6] = SL_SEGMENT_LCD_SEG_S02, .bit[7] = SL_SEGMENT_LCD_SEG_S02        \
                },                                                                                                                                              \
                { /* 2 */                                                                                                                                       \
                  .com[0] = SL_SEGMENT_LCD_COM_C06, .com[1] = SL_SEGMENT_LCD_COM_C06, .com[2] = SL_SEGMENT_LCD_COM_C04, .com[3] = SL_SEGMENT_LCD_COM_C03,       \
                  .bit[0] = SL_SEGMENT_LCD_SEG_S03, .bit[1] = SL_SEGMENT_LCD_SEG_S04, .bit[2] = SL_SEGMENT_LCD_SEG_S03, .bit[3] = SL_SEGMENT_LCD_SEG_S03,       \
                  .com[4] = SL_SEGMENT_LCD_COM_C03, .com[5] = SL_SEGMENT_LCD_COM_C05, .com[6] = SL_SEGMENT_LCD_COM_C04, .com[7] = SL_SEGMENT_LCD_COM_C05,       \
                  .bit[4] = SL_SEGMENT_LCD_SEG_S04, .bit[5] = SL_SEGMENT_LCD_SEG_S03, .bit[6] = SL_SEGMENT_LCD_SEG_S04, .bit[7] = SL_SEGMENT_LCD_SEG_S04        \
                },                                                                                                                                              \
                { /* 3 */                                                                                                                                       \
                  .com[0] = SL_SEGMENT_LCD_COM_C06, .com[1] = SL_SEGMENT_LCD_COM_C06, .com[2] = SL_SEGMENT_LCD_COM_C04, .com[3] = SL_SEGMENT_LCD_COM_C03,       \
                  .bit[0] = SL_SEGMENT_LCD_SEG_S05, .bit[1] = SL_SEGMENT_LCD_SEG_S06, .bit[2] = SL_SEGMENT_LCD_SEG_S05, .bit[3] = SL_SEGMENT_LCD_SEG_S05,       \
                  .com[4] = SL_SEGMENT_LCD_COM_C03, .com[5] = SL_SEGMENT_LCD_COM_C05, .com[6] = SL_SEGMENT_LCD_COM_C04, .com[7] = SL_SEGMENT_LCD_COM_C05,       \
                  .bit[4] = SL_SEGMENT_LCD_SEG_S06, .bit[5] = SL_SEGMENT_LCD_SEG_S05, .bit[6] = SL_SEGMENT_LCD_SEG_S06, .bit[7] = SL_SEGMENT_LCD_SEG_S06        \
                },                                                                                                                                              \
                { /* 4 */                                                                                                                                       \
                  .com[0] = SL_SEGMENT_LCD_COM_C06, .com[1] = SL_SEGMENT_LCD_COM_C06, .com[2] = SL_SEGMENT_LCD_COM_C04, .com[3] = SL_SEGMENT_LCD_COM_C03,       \
                  .bit[0] = SL_SEGMENT_LCD_SEG_S07, .bit[1] = SL_SEGMENT_LCD_SEG_S08, .bit[2] = SL_SEGMENT_LCD_SEG_S07, .bit[3] = SL_SEGMENT_LCD_SEG_S07,       \
                  .com[4] = SL_SEGMENT_LCD_COM_C03, .com[5] = SL_SEGMENT_LCD_COM_C05, .com[6] = SL_SEGMENT_LCD_COM_C04, .com[7] = SL_SEGMENT_LCD_COM_C05,       \
                  .bit[4] = SL_SEGMENT_LCD_SEG_S08, .bit[5] = SL_SEGMENT_LCD_SEG_S07, .bit[6] = SL_SEGMENT_LCD_SEG_S08, .bit[7] = SL_SEGMENT_LCD_SEG_S08        \
                },                                                                                                                                              \
                { /* 5 */                                                                                                                                       \
                  .com[0] = SL_SEGMENT_LCD_COM_C07, .com[1] = SL_SEGMENT_LCD_COM_C06, .com[2] = SL_SEGMENT_LCD_COM_C05, .com[3] = SL_SEGMENT_LCD_COM_C04,       \
                  .bit[0] = SL_SEGMENT_LCD_SEG_S09, .bit[1] = SL_SEGMENT_LCD_SEG_S10, .bit[2] = SL_SEGMENT_LCD_SEG_S09, .bit[3] = SL_SEGMENT_LCD_SEG_S09,       \
                  .com[4] = SL_SEGMENT_LCD_COM_C03, .com[5] = SL_SEGMENT_LCD_COM_C06, .com[6] = SL_SEGMENT_LCD_COM_C04, .com[7] = SL_SEGMENT_LCD_COM_C05,       \
                  .bit[4] = SL_SEGMENT_LCD_SEG_S10, .bit[5] = SL_SEGMENT_LCD_SEG_S09, .bit[6] = SL_SEGMENT_LCD_SEG_S10, .bit[7] = SL_SEGMENT_LCD_SEG_S10        \
                },                                                                                                                                              \
                { /* 6 */                                                                                                                                       \
                  .com[0] = SL_SEGMENT_LCD_COM_C07, .com[1] = SL_SEGMENT_LCD_COM_C06, .com[2] = SL_SEGMENT_LCD_COM_C05, .com[3] = SL_SEGMENT_LCD_COM_C04,       \
                  .bit[0] = SL_SEGMENT_LCD_SEG_S11, .bit[1] = SL_SEGMENT_LCD_SEG_S12, .bit[2] = SL_SEGMENT_LCD_SEG_S11, .bit[3] = SL_SEGMENT_LCD_SEG_S11,       \
                  .com[4] = SL_SEGMENT_LCD_COM_C03, .com[5] = SL_SEGMENT_LCD_COM_C06, .com[6] = SL_SEGMENT_LCD_COM_C04, .com[7] = SL_SEGMENT_LCD_COM_C05,       \
                  .bit[4] = SL_SEGMENT_LCD_SEG_S12, .bit[5] = SL_SEGMENT_LCD_SEG_S11, .bit[6] = SL_SEGMENT_LCD_SEG_S12, .bit[7] = SL_SEGMENT_LCD_SEG_S12        \
                },                                                                                                                                              \
                { /* 7 */                                                                                                                                       \
                  .com[0] = SL_SEGMENT_LCD_COM_C06, .com[1] = SL_SEGMENT_LCD_COM_C06, .com[2] = SL_SEGMENT_LCD_COM_C04, .com[3] = SL_SEGMENT_LCD_COM_C03,       \
                  .bit[0] = SL_SEGMENT_LCD_SEG_S13, .bit[1] = SL_SEGMENT_LCD_SEG_S14, .bit[2] = SL_SEGMENT_LCD_SEG_S13, .bit[3] = SL_SEGMENT_LCD_SEG_S13,       \
                  .com[4] = SL_SEGMENT_LCD_COM_C03, .com[5] = SL_SEGMENT_LCD_COM_C05, .com[6] = SL_SEGMENT_LCD_COM_C04, .com[7] = SL_SEGMENT_LCD_COM_C05,       \
                  .bit[4] = SL_SEGMENT_LCD_SEG_S14, .bit[5] = SL_SEGMENT_LCD_SEG_S13, .bit[6] = SL_SEGMENT_LCD_SEG_S14, .bit[7] = SL_SEGMENT_LCD_SEG_S14        \
                },                                                                                                                                              \
              }

#define SL_SEGMENT_LCD_EFM_DISPLAY_BOT_BLOCK    \
          .bot_blocks   = {                                                                                                                                     \
                { /* 1 */                                                                                                                                       \
                  .com[0] = SL_SEGMENT_LCD_COM_C02, .com[1] = SL_SEGMENT_LCD_COM_C00, .com[2] = SL_SEGMENT_LCD_COM_C00, .com[3] = SL_SEGMENT_LCD_COM_C03,       \
                  .bit[0] = SL_SEGMENT_LCD_SEG_S02, .bit[1] = SL_SEGMENT_LCD_SEG_S02, .bit[2] = SL_SEGMENT_LCD_SEG_S01, .bit[3] = SL_SEGMENT_LCD_SEG_S01,       \
                  .com[4] = SL_SEGMENT_LCD_COM_C03, .com[5] = SL_SEGMENT_LCD_COM_C01, .com[6] = SL_SEGMENT_LCD_COM_C02, .com[7] = SL_SEGMENT_LCD_COM_C01,       \
                  .bit[4] = SL_SEGMENT_LCD_SEG_S02, .bit[5] = SL_SEGMENT_LCD_SEG_S02, .bit[6] = SL_SEGMENT_LCD_SEG_S01, .bit[7] = SL_SEGMENT_LCD_SEG_S01        \
                },                                                                                                                                              \
                { /* 2 */                                                                                                                                       \
                  .com[0] = SL_SEGMENT_LCD_COM_C02, .com[1] = SL_SEGMENT_LCD_COM_C00, .com[2] = SL_SEGMENT_LCD_COM_C00, .com[3] = SL_SEGMENT_LCD_COM_C03,       \
                  .bit[0] = SL_SEGMENT_LCD_SEG_S04, .bit[1] = SL_SEGMENT_LCD_SEG_S04, .bit[2] = SL_SEGMENT_LCD_SEG_S03, .bit[3] = SL_SEGMENT_LCD_SEG_S03,       \
                  .com[4] = SL_SEGMENT_LCD_COM_C03, .com[5] = SL_SEGMENT_LCD_COM_C01, .com[6] = SL_SEGMENT_LCD_COM_C02, .com[7] = SL_SEGMENT_LCD_COM_C01,       \
                  .bit[4] = SL_SEGMENT_LCD_SEG_S04, .bit[5] = SL_SEGMENT_LCD_SEG_S04, .bit[6] = SL_SEGMENT_LCD_SEG_S03, .bit[7] = SL_SEGMENT_LCD_SEG_S03        \
                },                                                                                                                                              \
                { /* 3 */                                                                                                                                       \
                  .com[0] = SL_SEGMENT_LCD_COM_C02, .com[1] = SL_SEGMENT_LCD_COM_C00, .com[2] = SL_SEGMENT_LCD_COM_C00, .com[3] = SL_SEGMENT_LCD_COM_C03,       \
                  .bit[0] = SL_SEGMENT_LCD_SEG_S06, .bit[1] = SL_SEGMENT_LCD_SEG_S06, .bit[2] = SL_SEGMENT_LCD_SEG_S05, .bit[3] = SL_SEGMENT_LCD_SEG_S05,       \
                  .com[4] = SL_SEGMENT_LCD_COM_C03, .com[5] = SL_SEGMENT_LCD_COM_C01, .com[6] = SL_SEGMENT_LCD_COM_C02, .com[7] = SL_SEGMENT_LCD_COM_C01,       \
                  .bit[4] = SL_SEGMENT_LCD_SEG_S06, .bit[5] = SL_SEGMENT_LCD_SEG_S06, .bit[6] = SL_SEGMENT_LCD_SEG_S05, .bit[7] = SL_SEGMENT_LCD_SEG_S05        \
                },                                                                                                                                              \
                { /* 4 */                                                                                                                                       \
                  .com[0] = SL_SEGMENT_LCD_COM_C02, .com[1] = SL_SEGMENT_LCD_COM_C00, .com[2] = SL_SEGMENT_LCD_COM_C00, .com[3] = SL_SEGMENT_LCD_COM_C03,       \
                  .bit[0] = SL_SEGMENT_LCD_SEG_S08, .bit[1] = SL_SEGMENT_LCD_SEG_S08, .bit[2] = SL_SEGMENT_LCD_SEG_S07, .bit[3] = SL_SEGMENT_LCD_SEG_S07,       \
                  .com[4] = SL_SEGMENT_LCD_COM_C03, .com[5] = SL_SEGMENT_LCD_COM_C01, .com[6] = SL_SEGMENT_LCD_COM_C02, .com[7] = SL_SEGMENT_LCD_COM_C01,       \
                  .bit[4] = SL_SEGMENT_LCD_SEG_S08, .bit[5] = SL_SEGMENT_LCD_SEG_S08, .bit[6] = SL_SEGMENT_LCD_SEG_S07, .bit[7] = SL_SEGMENT_LCD_SEG_S07        \
                },                                                                                                                                              \
                { /* 5 */                                                                                                                                       \
                  .com[0] = SL_SEGMENT_LCD_COM_C02, .com[1] = SL_SEGMENT_LCD_COM_C00, .com[2] = SL_SEGMENT_LCD_COM_C01, .com[3] = SL_SEGMENT_LCD_COM_C04,       \
                  .bit[0] = SL_SEGMENT_LCD_SEG_S10, .bit[1] = SL_SEGMENT_LCD_SEG_S10, .bit[2] = SL_SEGMENT_LCD_SEG_S09, .bit[3] = SL_SEGMENT_LCD_SEG_S09,       \
                  .com[4] = SL_SEGMENT_LCD_COM_C03, .com[5] = SL_SEGMENT_LCD_COM_C01, .com[6] = SL_SEGMENT_LCD_COM_C03, .com[7] = SL_SEGMENT_LCD_COM_C02,       \
                  .bit[4] = SL_SEGMENT_LCD_SEG_S10, .bit[5] = SL_SEGMENT_LCD_SEG_S10, .bit[6] = SL_SEGMENT_LCD_SEG_S09, .bit[7] = SL_SEGMENT_LCD_SEG_S09        \
                },                                                                                                                                              \
                { /* 6 */                                                                                                                                       \
                  .com[0] = SL_SEGMENT_LCD_COM_C02, .com[1] = SL_SEGMENT_LCD_COM_C00, .com[2] = SL_SEGMENT_LCD_COM_C01, .com[3] = SL_SEGMENT_LCD_COM_C04,       \
                  .bit[0] = SL_SEGMENT_LCD_SEG_S12, .bit[1] = SL_SEGMENT_LCD_SEG_S12, .bit[2] = SL_SEGMENT_LCD_SEG_S11, .bit[3] = SL_SEGMENT_LCD_SEG_S11,       \
                  .com[4] = SL_SEGMENT_LCD_COM_C03, .com[5] = SL_SEGMENT_LCD_COM_C01, .com[6] = SL_SEGMENT_LCD_COM_C03, .com[7] = SL_SEGMENT_LCD_COM_C02,       \
                  .bit[4] = SL_SEGMENT_LCD_SEG_S12, .bit[5] = SL_SEGMENT_LCD_SEG_S12, .bit[6] = SL_SEGMENT_LCD_SEG_S11, .bit[7] = SL_SEGMENT_LCD_SEG_S11        \
                },                                                                                                                                              \
                { /* 7 */                                                                                                                                       \
                  .com[0] = SL_SEGMENT_LCD_COM_C02, .com[1] = SL_SEGMENT_LCD_COM_C00, .com[2] = SL_SEGMENT_LCD_COM_C00, .com[3] = SL_SEGMENT_LCD_COM_C03,       \
                  .bit[0] = SL_SEGMENT_LCD_SEG_S14, .bit[1] = SL_SEGMENT_LCD_SEG_S14, .bit[2] = SL_SEGMENT_LCD_SEG_S13, .bit[3] = SL_SEGMENT_LCD_SEG_S13,       \
                  .com[4] = SL_SEGMENT_LCD_COM_C03, .com[5] = SL_SEGMENT_LCD_COM_C01, .com[6] = SL_SEGMENT_LCD_COM_C02, .com[7] = SL_SEGMENT_LCD_COM_C01,       \
                  .bit[4] = SL_SEGMENT_LCD_SEG_S14, .bit[5] = SL_SEGMENT_LCD_SEG_S14, .bit[6] = SL_SEGMENT_LCD_SEG_S13, .bit[7] = SL_SEGMENT_LCD_SEG_S13        \
                },                                                                                                                                              \
              }

#define SL_SEGMENT_LCD_EFM_DISPLAY_DEF {          \
            SL_SEGMENT_LCD_EFM_DISPLAY_TEXT,      \
            SL_SEGMENT_LCD_EFM_DISPLAY_NUM,       \
            SL_SEGMENT_LCD_EFM_DISPLAY_SYMBOL,    \
            SL_SEGMENT_LCD_EFM_DISPLAY_TOP_BLOCK, \
            SL_SEGMENT_LCD_EFM_DISPLAY_BOT_BLOCK, \
          }

// Utility Macros
#define SL_SEGMENT_LCD_ALL_SEG_BITMASK ( \
  (1 << SL_SEGMENT_LCD_SEG_S00) | \
  (1 << SL_SEGMENT_LCD_SEG_S01) | \
  (1 << SL_SEGMENT_LCD_SEG_S02) | \
  (1 << SL_SEGMENT_LCD_SEG_S03) | \
  (1 << SL_SEGMENT_LCD_SEG_S04) | \
  (1 << SL_SEGMENT_LCD_SEG_S05) | \
  (1 << SL_SEGMENT_LCD_SEG_S06) | \
  (1 << SL_SEGMENT_LCD_SEG_S07) | \
  (1 << SL_SEGMENT_LCD_SEG_S08) | \
  (1 << SL_SEGMENT_LCD_SEG_S09) | \
  (1 << SL_SEGMENT_LCD_SEG_S10) | \
  (1 << SL_SEGMENT_LCD_SEG_S11) | \
  (1 << SL_SEGMENT_LCD_SEG_S12) | \
  (1 << SL_SEGMENT_LCD_SEG_S13) | \
  (1 << SL_SEGMENT_LCD_SEG_S14) | \
  (1 << SL_SEGMENT_LCD_SEG_S15) | \
  (1 << SL_SEGMENT_LCD_SEG_S16) | \
  (1 << SL_SEGMENT_LCD_SEG_S17) | \
  (1 << SL_SEGMENT_LCD_SEG_S18) | \
  (1 << SL_SEGMENT_LCD_SEG_S19))

#define SL_LCD_ALL_SEG_NUM_BITMASK ( \
  (1 << SL_SEGMENT_LCD_SEG_S15) | \
  (1 << SL_SEGMENT_LCD_SEG_S16) | \
  (1 << SL_SEGMENT_LCD_SEG_S17) | \
  (1 << SL_SEGMENT_LCD_SEG_S18))

#define SL_LCD_ALL_SEG_ALPHA_BITMASK ( \
  (1 << SL_SEGMENT_LCD_SEG_S01) | \
  (1 << SL_SEGMENT_LCD_SEG_S02) | \
  (1 << SL_SEGMENT_LCD_SEG_S03) | \
  (1 << SL_SEGMENT_LCD_SEG_S04) | \
  (1 << SL_SEGMENT_LCD_SEG_S05) | \
  (1 << SL_SEGMENT_LCD_SEG_S06) | \
  (1 << SL_SEGMENT_LCD_SEG_S07) | \
  (1 << SL_SEGMENT_LCD_SEG_S08) | \
  (1 << SL_SEGMENT_LCD_SEG_S09) | \
  (1 << SL_SEGMENT_LCD_SEG_S10) | \
  (1 << SL_SEGMENT_LCD_SEG_S11) | \
  (1 << SL_SEGMENT_LCD_SEG_S12) | \
  (1 << SL_SEGMENT_LCD_SEG_S13) | \
  (1 << SL_SEGMENT_LCD_SEG_S14))

//  LCD_NUMBER_OFF
#define SL_SEGMENT_LCD_NUMBER_OFF()                               \
  do {                                                 \
    LCD_SegmentSetLow(0, SL_LCD_ALL_SEG_NUM_BITMASK, 0);  \
    LCD_SegmentSetLow(1, SL_LCD_ALL_SEG_NUM_BITMASK, 0);  \
    LCD_SegmentSetLow(2, SL_LCD_ALL_SEG_NUM_BITMASK, 0);  \
    LCD_SegmentSetLow(3, SL_LCD_ALL_SEG_NUM_BITMASK, 0);  \
    LCD_SegmentSetLow(4, SL_LCD_ALL_SEG_NUM_BITMASK, 0);  \
    LCD_SegmentSetLow(5, SL_LCD_ALL_SEG_NUM_BITMASK, 0);  \
    LCD_SegmentSetLow(6, SL_LCD_ALL_SEG_NUM_BITMASK, 0);  \
  } while (0)

//  LCD_ALPHA_NUMBER_OFF
#define SL_LCD_ALPHA_NUMBER_OFF()                                \
  do {                                                        \
    LCD_SegmentSetLow(0, SL_LCD_ALL_SEG_ALPHA_BITMASK &          \
                      (~((1 << SL_SEGMENT_LCD_SEG_S09)|(1 << SL_SEGMENT_LCD_SEG_S11))), 0); \
    LCD_SegmentSetLow(1, SL_LCD_ALL_SEG_ALPHA_BITMASK, 0);       \
    LCD_SegmentSetLow(2, SL_LCD_ALL_SEG_ALPHA_BITMASK, 0);       \
    LCD_SegmentSetLow(3, SL_LCD_ALL_SEG_ALPHA_BITMASK, 0);       \
    LCD_SegmentSetLow(4, SL_LCD_ALL_SEG_ALPHA_BITMASK, 0);       \
    LCD_SegmentSetLow(5, SL_LCD_ALL_SEG_ALPHA_BITMASK, 0);       \
    LCD_SegmentSetLow(6, SL_LCD_ALL_SEG_ALPHA_BITMASK, 0);       \
    LCD_SegmentSetLow(7, ((1 << SL_SEGMENT_LCD_SEG_S09)|(1 << SL_SEGMENT_LCD_SEG_S11)), 0); \
  } while (0)

#define SL_SEGMENT_LCD_ALL_SEGMENTS_OFF()                     \
  do {                                             \
    LCD_SegmentSetLow(0, SL_SEGMENT_LCD_ALL_SEG_BITMASK, 0);  \
    LCD_SegmentSetLow(1, SL_SEGMENT_LCD_ALL_SEG_BITMASK, 0);  \
    LCD_SegmentSetLow(2, SL_SEGMENT_LCD_ALL_SEG_BITMASK, 0);  \
    LCD_SegmentSetLow(3, SL_SEGMENT_LCD_ALL_SEG_BITMASK, 0);  \
    LCD_SegmentSetLow(4, SL_SEGMENT_LCD_ALL_SEG_BITMASK, 0);  \
    LCD_SegmentSetLow(5, SL_SEGMENT_LCD_ALL_SEG_BITMASK, 0);  \
    LCD_SegmentSetLow(6, SL_SEGMENT_LCD_ALL_SEG_BITMASK, 0);  \
    LCD_SegmentSetLow(7, SL_SEGMENT_LCD_ALL_SEG_BITMASK, 0);  \
  } while (0)

#define SL_SEGMENT_LCD_ALL_SEGMENTS_ON()                                    \
  do {                                                           \
    LCD_SegmentSetLow(0, SL_SEGMENT_LCD_ALL_SEG_BITMASK, _LCD_SEGD0_MASK);  \
    LCD_SegmentSetLow(1, SL_SEGMENT_LCD_ALL_SEG_BITMASK, _LCD_SEGD0_MASK);  \
    LCD_SegmentSetLow(2, SL_SEGMENT_LCD_ALL_SEG_BITMASK, _LCD_SEGD0_MASK);  \
    LCD_SegmentSetLow(3, SL_SEGMENT_LCD_ALL_SEG_BITMASK, _LCD_SEGD0_MASK);  \
    LCD_SegmentSetLow(4, SL_SEGMENT_LCD_ALL_SEG_BITMASK, _LCD_SEGD0_MASK);  \
    LCD_SegmentSetLow(5, SL_SEGMENT_LCD_ALL_SEG_BITMASK, _LCD_SEGD0_MASK);  \
    LCD_SegmentSetLow(6, SL_SEGMENT_LCD_ALL_SEG_BITMASK, _LCD_SEGD0_MASK);  \
    LCD_SegmentSetLow(7, SL_SEGMENT_LCD_ALL_SEG_BITMASK, _LCD_SEGD0_MASK);  \
  } while (0)

#define SL_SEGMENT_LCD_SEGMENTS_ENABLE()         \
  do {                                \
    LCD_ComEnable(SL_SEGMENT_LCD_COM_C00, true);     \
    LCD_ComEnable(SL_SEGMENT_LCD_COM_C01, true);     \
    LCD_ComEnable(SL_SEGMENT_LCD_COM_C02, true);     \
    LCD_ComEnable(SL_SEGMENT_LCD_COM_C03, true);     \
    LCD_ComEnable(SL_SEGMENT_LCD_COM_C04, true);     \
    LCD_ComEnable(SL_SEGMENT_LCD_COM_C05, true);     \
    LCD_ComEnable(SL_SEGMENT_LCD_COM_C06, true);     \
    LCD_ComEnable(SL_SEGMENT_LCD_COM_C07, true);     \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S00, true); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S01, true); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S02, true); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S03, true); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S04, true); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S05, true); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S06, true); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S07, true); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S08, true); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S09, true); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S10, true); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S11, true); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S12, true); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S13, true); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S14, true); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S15, true); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S16, true); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S17, true); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S18, true); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S19, true); \
  } while (0)

#define SL_LCD_SEGMENTS_ALPHA_DIS()      \
  do {                                \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S00, false); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S01, false); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S02, false); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S03, false); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S04, false); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S05, false); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S06, false); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S07, false); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S08, false); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S09, false); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S10, false); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S11, false); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S12, false); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S13, false); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S14, false); \
  } while (0)

#define SL_LCD_SEGMENTS_NUM_DIS()         \
  do {                                 \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S15, false); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S16, false); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S17, false); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S18, false); \
    LCD_SegmentEnable(SL_SEGMENT_LCD_SEG_S19, false); \
  } while (0)

#define SL_SEGMENT_LCD_DISPLAY_ENABLE() \
  do {                       \
    ;                        \
  } while (0)


#ifdef __cplusplus
}
#endif

#endif
