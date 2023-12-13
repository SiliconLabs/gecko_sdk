/***************************************************************************//**
 * @file
 * @brief Segment LCD Config for the LCD module CE322_1002
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
#define SL_SEGMENT_LCD_MODULE_CE322_1002

// <<< Use Configuration Wizard in Context Menu >>>

// <h>Frame Rate
// LCD Controller Prescaler (divide LCDCLK / 64)
// LCDCLK_pre = 512 Hz
// Set FDIV=1, means 512/2 = 256 Hz
// With quadruplex mode, 256/8 => 32 Hz Frame Rate

// <o SL_SEGMENT_LCD_CLK_PRE> LCD Controller prescaler
// <i> Default: 64
#define SL_SEGMENT_LCD_CLK_PRE         64

// <o SL_SEGMENT_LCD_FRAME_RATE_DIV> LCD frame rate divisor
// <i> Default: 1
#define SL_SEGMENT_LCD_FRAME_RATE_DIV   1
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
#define SL_SEGMENT_LCD_BOOST_CONTRAST      0x0F

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
// <i> Default: lcdMuxQuadruplex
#define SL_SEGMENT_LCD_MUX_CONFIG             lcdMuxQuadruplex

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
// <i> Default: lcdBiasOneThird
#define SL_SEGMENT_LCD_BIAS_SETTING           lcdBiasOneThird

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

// Range of symbols available on display
typedef enum {
  SL_LCD_SYMBOL_P2, //!< SL_LCD_SYMBOL_P2
  SL_LCD_SYMBOL_P3, //!< SL_LCD_SYMBOL_P3
  SL_LCD_SYMBOL_P4, //!< SL_LCD_SYMBOL_P4
  SL_LCD_SYMBOL_P5, //!< SL_LCD_SYMBOL_P5
  SL_LCD_SYMBOL_P6, //!< SL_LCD_SYMBOL_P6
  SL_LCD_SYMBOL_DEGC//!< SL_LCD_SYMBOL_DEGC
} sl_segment_lcd_symbol_t;

#define SL_LCD_SYMBOL_P2_COM  SL_SEGMENT_LCD_COM_C00
#define SL_LCD_SYMBOL_P2_SEG  SL_SEGMENT_LCD_SEG_S03
#define SL_LCD_SYMBOL_P3_COM  SL_SEGMENT_LCD_COM_C00
#define SL_LCD_SYMBOL_P3_SEG  SL_SEGMENT_LCD_SEG_S05
#define SL_LCD_SYMBOL_P4_COM  SL_SEGMENT_LCD_COM_C00
#define SL_LCD_SYMBOL_P4_SEG  SL_SEGMENT_LCD_SEG_S08
#define SL_LCD_SYMBOL_P5_COM  SL_SEGMENT_LCD_COM_C03
#define SL_LCD_SYMBOL_P5_SEG  SL_SEGMENT_LCD_SEG_S07
#define SL_LCD_SYMBOL_P6_COM  SL_SEGMENT_LCD_COM_C03
#define SL_LCD_SYMBOL_P6_SEG  SL_SEGMENT_LCD_SEG_S01
#define SL_LCD_SYMBOL_DEGC_COM  SL_SEGMENT_LCD_COM_C03
#define SL_LCD_SYMBOL_DEGC_SEG  SL_SEGMENT_LCD_SEG_S07

// Multiplexing table: See board schematic for more details
#define SL_SEGMENT_LCD_EFM_DISPLAY_DEF {                                    \
    .number      = {                                                        \
      { /* #5 location : Segments 5A/5B/5C/5D/5E/5F/5G */                   \
        .com[0] = SL_SEGMENT_LCD_COM_C03, .com[1] = SL_SEGMENT_LCD_COM_C02, \
        .com[2] = SL_SEGMENT_LCD_COM_C01, .com[3] = SL_SEGMENT_LCD_COM_C00, \
        .bit[0] = SL_SEGMENT_LCD_SEG_S09, .bit[1] = SL_SEGMENT_LCD_SEG_S09, \
        .bit[2] = SL_SEGMENT_LCD_SEG_S09, .bit[3] = SL_SEGMENT_LCD_SEG_S09, \
        .com[4] = SL_SEGMENT_LCD_COM_C01, .com[5] = SL_SEGMENT_LCD_COM_C03, \
        .com[6] = SL_SEGMENT_LCD_COM_C02,                                   \
        .bit[4] = SL_SEGMENT_LCD_SEG_S08, .bit[5] = SL_SEGMENT_LCD_SEG_S08, \
        .bit[6] = SL_SEGMENT_LCD_SEG_S08,                                   \
      },                                                                    \
      { /* #4 location : Segments 4A/4B/4C/4D/4E/4F/4G */                   \
        .com[0] = SL_SEGMENT_LCD_COM_C03, .com[1] = SL_SEGMENT_LCD_COM_C02, \
        .com[2] = SL_SEGMENT_LCD_COM_C00, .com[3] = SL_SEGMENT_LCD_COM_C00, \
        .bit[0] = SL_SEGMENT_LCD_SEG_S06, .bit[1] = SL_SEGMENT_LCD_SEG_S07, \
        .bit[2] = SL_SEGMENT_LCD_SEG_S07, .bit[3] = SL_SEGMENT_LCD_SEG_S06, \
        .com[4] = SL_SEGMENT_LCD_COM_C01, .com[5] = SL_SEGMENT_LCD_COM_C02, \
        .com[6] = SL_SEGMENT_LCD_COM_C01,                                   \
        .bit[4] = SL_SEGMENT_LCD_SEG_S06, .bit[5] = SL_SEGMENT_LCD_SEG_S06, \
        .bit[6] = SL_SEGMENT_LCD_SEG_S07,                                   \
      },                                                                    \
      { /* #3 location : Segments 3A/3B/3C/3D/3E/3F/3G */                   \
        .com[0] = SL_SEGMENT_LCD_COM_C03, .com[1] = SL_SEGMENT_LCD_COM_C03, \
        .com[2] = SL_SEGMENT_LCD_COM_C01, .com[3] = SL_SEGMENT_LCD_COM_C00, \
        .bit[0] = SL_SEGMENT_LCD_SEG_S04, .bit[1] = SL_SEGMENT_LCD_SEG_S05, \
        .bit[2] = SL_SEGMENT_LCD_SEG_S05, .bit[3] = SL_SEGMENT_LCD_SEG_S04, \
        .com[4] = SL_SEGMENT_LCD_COM_C01, .com[5] = SL_SEGMENT_LCD_COM_C02, \
        .com[6] = SL_SEGMENT_LCD_COM_C02,                                   \
        .bit[4] = SL_SEGMENT_LCD_SEG_S04, .bit[5] = SL_SEGMENT_LCD_SEG_S04, \
        .bit[6] = SL_SEGMENT_LCD_SEG_S05,                                   \
      },                                                                    \
      { /* #2 location : Segments 2A/2B/2C/2D/2E/2F/2G */                   \
        .com[0] = SL_SEGMENT_LCD_COM_C03, .com[1] = SL_SEGMENT_LCD_COM_C03, \
        .com[2] = SL_SEGMENT_LCD_COM_C01, .com[3] = SL_SEGMENT_LCD_COM_C00, \
        .bit[0] = SL_SEGMENT_LCD_SEG_S02, .bit[1] = SL_SEGMENT_LCD_SEG_S03, \
        .bit[2] = SL_SEGMENT_LCD_SEG_S03, .bit[3] = SL_SEGMENT_LCD_SEG_S02, \
        .com[4] = SL_SEGMENT_LCD_COM_C01, .com[5] = SL_SEGMENT_LCD_COM_C02, \
        .com[6] = SL_SEGMENT_LCD_COM_C02,                                   \
        .bit[4] = SL_SEGMENT_LCD_SEG_S02, .bit[5] = SL_SEGMENT_LCD_SEG_S02, \
        .bit[6] = SL_SEGMENT_LCD_SEG_S03,                                   \
      },                                                                    \
      { /* #1 location : Segments 1A/1B/1C/1D/1E/1F/1G */                   \
        .com[0] = SL_SEGMENT_LCD_COM_C03, .com[1] = SL_SEGMENT_LCD_COM_C02, \
        .com[2] = SL_SEGMENT_LCD_COM_C00, .com[3] = SL_SEGMENT_LCD_COM_C00, \
        .bit[0] = SL_SEGMENT_LCD_SEG_S00, .bit[1] = SL_SEGMENT_LCD_SEG_S01, \
        .bit[2] = SL_SEGMENT_LCD_SEG_S01, .bit[3] = SL_SEGMENT_LCD_SEG_S00, \
        .com[4] = SL_SEGMENT_LCD_COM_C01, .com[5] = SL_SEGMENT_LCD_COM_C02, \
        .com[6] = SL_SEGMENT_LCD_COM_C01,                                   \
        .bit[4] = SL_SEGMENT_LCD_SEG_S00, .bit[5] = SL_SEGMENT_LCD_SEG_S00, \
        .bit[6] = SL_SEGMENT_LCD_SEG_S01,                                   \
      }                                                                     \
    }                                                                       \
}

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
  (1 << SL_SEGMENT_LCD_SEG_S09))

// Utility Macros
#define SL_SEGMENT_LCD_NUMBER_OFF()                                     \
  do {                                                                  \
    LCD_SegmentSetLow(0, SL_SEGMENT_LCD_ALL_SEG_BITMASK &               \
                      (~( (1 << SL_SEGMENT_LCD_SEG_S03)|                \
                          (1 << SL_SEGMENT_LCD_SEG_S05)|                \
                      (1 << SL_SEGMENT_LCD_SEG_S08))), 0x0000);         \
    LCD_SegmentSetLow(1, SL_SEGMENT_LCD_ALL_SEG_BITMASK, 0x0000);       \
    LCD_SegmentSetLow(2, SL_SEGMENT_LCD_ALL_SEG_BITMASK, 0x0000);       \
    LCD_SegmentSetLow(3, SL_SEGMENT_LCD_ALL_SEG_BITMASK &               \
                      (~( (1 << SL_SEGMENT_LCD_SEG_S01)|                \
                          (1 << SL_SEGMENT_LCD_SEG_S07)))               \
                      , 0x0000);                                        \
  } while (0)

#define SL_SEGMENT_LCD_ALL_SEGMENTS_OFF()  \
  do {                                     \
    LCD_SegmentSetLow(0, 0xFFFFF, 0x0000); \
    LCD_SegmentSetLow(1, 0xFFFFF, 0x0000); \
    LCD_SegmentSetLow(2, 0xFFFFF, 0x0000); \
    LCD_SegmentSetLow(3, 0xFFFFF, 0x0000); \
  } while (0)

#define SL_SEGMENT_LCD_ALL_SEGMENTS_ON()      \
    do {                                      \
      LCD_SegmentSetLow(0, 0xFFFFF, 0xFFFFF); \
      LCD_SegmentSetLow(1, 0xFFFFF, 0xFFFFF); \
      LCD_SegmentSetLow(2, 0xFFFFF, 0xFFFFF); \
      LCD_SegmentSetLow(3, 0xFFFFF, 0xFFFFF); \
    } while (0)

#define SL_SEGMENT_LCD_SEGMENTS_ENABLE()             \
  do {                                               \
    LCD_ComEnable(SL_SEGMENT_LCD_COM_C00, true);     \
    LCD_ComEnable(SL_SEGMENT_LCD_COM_C01, true);     \
    LCD_ComEnable(SL_SEGMENT_LCD_COM_C02, true);     \
    LCD_ComEnable(SL_SEGMENT_LCD_COM_C03, true);     \
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
    ;                                                \
  } while (0)

#define SL_SEGMENT_LCD_DISPLAY_ENABLE() \
  do {                                  \
    ;                                   \
  } while (0)


#ifdef __cplusplus
}
#endif

#endif
