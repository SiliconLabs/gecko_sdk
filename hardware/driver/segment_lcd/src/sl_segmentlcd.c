/***************************************************************************//**
 * @file
 * @brief Segment LCD Display driver
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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "em_device.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_lcd.h"

#include "sl_segmentlcd.h"

/***************************************************************************//**
 * @addtogroup SegmentLcd
 * @brief Segment LCD driver
 *
 * @details
 *  This driver implements symbol and string write support for EFM32/EFR32 kits
 *  with segment LCD.
 * @{
 ******************************************************************************/

/**************************************************************************//**
 * @brief Working instance of LCD display
 *****************************************************************************/
const sl_segment_lcd_mcu_display_t efm_display = SL_SEGMENT_LCD_EFM_DISPLAY_DEF;

/**************************************************************************//**
 * @brief Working instance of LCD display
 *****************************************************************************/
#if defined(SL_SEGMENT_LCD_MODULE_CL010_1087) || defined(SL_SEGMENT_LCD_MODULE_CE322_1001)
static void display_block(
  sl_segment_lcd_block_mode_t top_mode[SL_SEGMENT_LCD_NUM_BLOCK_COLUMNS],
  sl_segment_lcd_block_mode_t bot_mode[SL_SEGMENT_LCD_NUM_BLOCK_COLUMNS]);
#endif

/**************************************************************************//**
 * @brief
 * Defines higlighted segments for the alphabet, starting from "blank" (SPACE)
 * Uses bit pattern as defined for text segments above.
 * E.g. a capital O, would have bits 0 1 2 3 4 5 => 0x003f defined
 *****************************************************************************/
#if defined(SL_SEGMENT_LCD_MODULE_CL010_1087) || defined(SL_SEGMENT_LCD_MODULE_CE322_1001)
const uint16_t segment_alphabet[] = {
  0x0000, /* space */
  0x1100, /* ! */
  0x0280, /* " */
  0x0000, /* # */
  0x0000, /* $ */
  0x0602, /* % */
  0x0000, /* & */
  0x0020, /* ' */
  0x0039, /* ( */
  0x000f, /* ) */
  0x0000, /* * */
  0x1540, /* + */
  0x2000, /* , */
  0x0440, /* - */
  0x1000, /* . */
  0x2200, /* / */

  0x003f, /* 0 */
  0x0006, /* 1 */
  0x045b, /* 2 */
  0x044f, /* 3 */
  0x0466, /* 4 */
  0x046d, /* 5 */
  0x047d, /* 6 */
  0x0007, /* 7 */
  0x047f, /* 8 */
  0x046f, /* 9 */

  0x0000, /* : */
  0x0000, /* ; */
  0x0a00, /* < */
  0x0000, /* = */
  0x2080, /* > */
  0x0000, /* ? */
  0xffff, /* @ */

  0x0477, /* A */
  0x0a79, /* B */
  0x0039, /* C */
  0x20b0, /* D */
  0x0079, /* E */
  0x0071, /* F */
  0x043d, /* G */
  0x0476, /* H */
  0x0006, /* I */
  0x000e, /* J */
  0x0a70, /* K */
  0x0038, /* L */
  0x02b6, /* M */
  0x08b6, /* N */
  0x003f, /* O */
  0x0473, /* P */
  0x083f, /* Q */
  0x0c73, /* R */
  0x046d, /* S */
  0x1101, /* T */
  0x003e, /* U */
  0x2230, /* V */
  0x2836, /* W */
  0x2a80, /* X */
  0x046e, /* Y */
  0x2209, /* Z */

  0x0039, /* [ */
  0x0880, /* backslash */
  0x000f, /* ] */
  0x0001, /* ^ */
  0x0008, /* _ */
  0x0100, /* ` */

  0x1058, /* a */
  0x047c, /* b */
  0x0058, /* c */
  0x045e, /* d */
  0x2058, /* e */
  0x0471, /* f */
  0x0c0c, /* g */
  0x0474, /* h */
  0x0004, /* i */
  0x000e, /* j */
  0x0c70, /* k */
  0x0038, /* l */
  0x1454, /* m */
  0x0454, /* n */
  0x045c, /* o */
  0x0473, /* p */
  0x0467, /* q */
  0x0450, /* r */
  0x0c08, /* s */
  0x0078, /* t */
  0x001c, /* u */
  0x2010, /* v */
  0x2814, /* w */
  0x2a80, /* x */
  0x080c, /* y */
  0x2048, /* z */

  0x0000,
};

#endif
/**************************************************************************//**
 * @brief
 * Defines higlighted segments for the numeric display
 *****************************************************************************/
const uint16_t segment_numbers[] = {
  0x003f, /* 0 */
  0x0006, /* 1 */
  0x005b, /* 2 */
  0x004f, /* 3 */
  0x0066, /* 4 */
  0x006d, /* 5 */
  0x007d, /* 6 */
  0x0007, /* 7 */
  0x007f, /* 8 */
  0x006f, /* 9 */
  0x0077, /* A */
  0x007c, /* b */
  0x0039, /* C */
  0x005e, /* d */
  0x0079, /* E */
  0x0071, /* F */
  0x0040  /* - */
};

/**************************************************************************//**
 * @brief
 * Defines highlighted segments for the block display
 *****************************************************************************/
#if defined(SL_SEGMENT_LCD_MODULE_CL010_1087) || defined(SL_SEGMENT_LCD_MODULE_CE322_1001)
const uint16_t blocks[] = {
  0x0000, /* blank */
  0x00E0, /* inner */
  0x001F, /* outer */
  0x00FF  /* full */
};
#endif

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */
/* sign is last element of the table  */
const uint16_t sign_index = sizeof(segment_numbers) / sizeof(uint16_t) - 1;

const LCD_Init_TypeDef lcd_init = SL_SEGMENT_LCD_INIT_DEF;

#if defined(_SILICON_LABS_32B_SERIES_1) || defined(_SILICON_LABS_32B_SERIES_2)
static bool dynamic_chg_redist_enabled = true;
#endif

/** @endcond */

#if defined(_SILICON_LABS_32B_SERIES_1) || defined(_SILICON_LABS_32B_SERIES_2)
void sl_segment_lcd_update_chg_rdst(void);
#endif

/**************************************************************************//**
 *    Disable all segments
 *****************************************************************************/
void sl_segment_lcd_all_off(void)
{
  /* Turn on low segments */
  SL_SEGMENT_LCD_ALL_SEGMENTS_OFF();

#if defined(_SILICON_LABS_32B_SERIES_2)
  LCD_SyncStart(false, lcdLoadAddrNone);
  LCD_LoadBusyWait();
#endif

#if defined(_SILICON_LABS_32B_SERIES_1) || defined(_SILICON_LABS_32B_SERIES_2)
  /* Switching charge redistribution OFF (if dynamic change is enabled)*/
  if (dynamic_chg_redist_enabled) {
      /* Disable the controller before reconfiguration. */
    LCD_Enable(false);
#if defined(_SILICON_LABS_32B_SERIES_2)
    LCD_ReadyWait();
#endif
    LCD->DISPCTRL = (LCD->DISPCTRL & ~_LCD_DISPCTRL_CHGRDST_MASK)
                    | lcdChargeRedistributionDisable;
    LCD_Enable(true);
  }
#endif
}

/**************************************************************************//**
 *    Enable all segments
 *****************************************************************************/
void sl_segment_lcd_all_on(void)
{
  SL_SEGMENT_LCD_ALL_SEGMENTS_ON();

#if defined(_SILICON_LABS_32B_SERIES_2)
  LCD_SyncStart(false, lcdLoadAddrNone);
  LCD_LoadBusyWait();
#endif

#if defined(_SILICON_LABS_32B_SERIES_1) || defined(_SILICON_LABS_32B_SERIES_2)
  /* Switching charge redistribution ON (if dynamic change is enabled) */
  if (dynamic_chg_redist_enabled) {
      /* Disable the controller before reconfiguration. */
    LCD_Enable(false);
#if defined(_SILICON_LABS_32B_SERIES_2)
    LCD_ReadyWait();
#endif
    LCD->DISPCTRL = (LCD->DISPCTRL & ~_LCD_DISPCTRL_CHGRDST_MASK)
                    | lcdChargeRedistributionEnable;
    LCD_Enable(true);
  }
#endif
}

/**************************************************************************//**
 *    Turn all segments on alpha characters in display off
 *****************************************************************************/
#if defined(SL_SEGMENT_LCD_MODULE_CL010_1087) || defined(SL_SEGMENT_LCD_MODULE_CE322_1001)
void sl_segment_lcd_alpha_number_off(void)
{
  SL_LCD_ALPHA_NUMBER_OFF();

#if defined(_SILICON_LABS_32B_SERIES_1) || defined(_SILICON_LABS_32B_SERIES_2)
  /* Evaluating the updated display contents and switching charge
     redistribution ON or OFF accordingly (only if dynamic change is enabled) */
  if (dynamic_chg_redist_enabled) {
    sl_segment_lcd_update_chg_rdst();
  }
#endif
}
#endif

/******************************************************************************
*    Display blocks on LCD display: blank, fill, outline, outline & fill
******************************************************************************/
#if defined(SL_SEGMENT_LCD_MODULE_CL010_1087) || defined(SL_SEGMENT_LCD_MODULE_CE322_1001)
void sl_segment_lcd_block(
  sl_segment_lcd_block_mode_t top_mode[SL_SEGMENT_LCD_NUM_BLOCK_COLUMNS],
  sl_segment_lcd_block_mode_t bot_mode[SL_SEGMENT_LCD_NUM_BLOCK_COLUMNS])
{
  /* If an update is in progress we must block, or there might be tearing */
#if defined(_SILICON_LABS_32B_SERIES_0) || defined(_SILICON_LABS_32B_SERIES_1)
  LCD_SyncBusyDelay(0xFFFFFFFF);

  /* Freeze LCD to avoid partial updates */
  LCD_FreezeEnable(true);
#else
  LCD_ReadyWait();
#endif

  /* Turn all segments off */
  sl_segment_lcd_alpha_number_off();

  display_block(top_mode, bot_mode);

#if defined(_SILICON_LABS_32B_SERIES_0) || defined(_SILICON_LABS_32B_SERIES_1)
  /* Sync LCD registers to LE domain */
  LCD_FreezeEnable(false);
#else
  LCD_SyncStart(false, lcdLoadAddrNone);
  LCD_LoadBusyWait();
#endif
}
#endif

/**************************************************************************//**
 *    Disables LCD controller
 *****************************************************************************/
void sl_segment_lcd_disable(void)
{
  /* Disable LCD */
  LCD_Enable(false);

#if defined(_SILICON_LABS_32B_SERIES_0) || defined(_SILICON_LABS_32B_SERIES_1)
  /* Make sure CTRL register has been updated */
  LCD_SyncBusyDelay(LCD_SYNCBUSY_CTRL);
#else
  LCD_ReadyWait();
#endif

  /* Turn off LCD clock */
  CMU_ClockEnable(cmuClock_LCD, false);

#if defined(_SILICON_LABS_32B_SERIES_0)
  /* Turn off voltage boost if enabled */
  CMU->LCDCTRL = 0;
#endif
}

/**************************************************************************//**
 *    Segment LCD Initialization routine for EFM32 STK display
 *****************************************************************************/
void sl_segment_lcd_init(bool use_boost)
{
#if defined(_SILICON_LABS_32B_SERIES_0) || defined(_SILICON_LABS_32B_SERIES_1)
  /* Ensure LE modules are accessible */
  CMU_ClockEnable(cmuClock_CORELE, true);

  /* Enable LFRCO as LFACLK in CMU (will also enable oscillator if not enabled) */
  CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFRCO);

  /* LCD Controller Prescaler  */
  CMU_ClockDivSet(cmuClock_LCDpre, LCD_CMU_CLK_PRE);

  /* Frame Rate */
  CMU_LCDClkFDIVSet(LCD_CMU_CLK_DIV);
#endif

#if defined(_SILICON_LABS_32B_SERIES_2)
  /* Enable LFRCO as LFACLK in CMU (will also enable oscillator if not enabled) */
  CMU_ClockSelectSet(cmuClock_LCD, cmuSelect_LFRCO);
#endif

  /* Enable clock to LCD module */
  CMU_ClockEnable(cmuClock_LCD, true);

  SL_SEGMENT_LCD_DISPLAY_ENABLE();

  /* Disable interrupts */
  LCD_IntDisable(0xFFFFFFFF);

  /* Initialize and enable LCD controller */
  LCD_Init(&lcd_init);
#if defined(_SILICON_LABS_32B_SERIES_1) || defined(_SILICON_LABS_32B_SERIES_2)
  if (lcd_init.chargeRedistribution == lcdChargeRedistributionDisable) {
    dynamic_chg_redist_enabled = false;
  }
#endif

  /* Enable all display segments */
  SL_SEGMENT_LCD_SEGMENTS_ENABLE();

#if defined(_SILICON_LABS_32B_SERIES_2)
  CMU_ClockEnable(cmuClock_GPIO, true);
#endif

  /* Enable boost if necessary */
  if (use_boost) {
#if defined(_SILICON_LABS_32B_SERIES_0)
    LCD_VBoostSet(LCD_BOOST_LEVEL);
    LCD_VLCDSelect(lcdVLCDSelVExtBoost);
    CMU->LCDCTRL |= CMU_LCDCTRL_VBOOSTEN;
#elif defined(_SILICON_LABS_32B_SERIES_1) || defined(_SILICON_LABS_32B_SERIES_2)
    /* Set charge pump mode and adjust contrast */
#if defined(_SILICON_LABS_32B_SERIES_1)
    LCD_ModeSet(lcdModeCpIntOsc);
#else
    LCD_ModeSet(lcdModeChargePump);
#endif
    LCD_ContrastSet(SL_SEGMENT_LCD_BOOST_CONTRAST);
#endif
  }

  if (SL_SEGMENT_LCD_LDMA_MODE != lcdDmaModeDisable) {
    // Setting the LDMA mode
    LCD_DmaModeSet(SL_SEGMENT_LCD_LDMA_MODE);
    // Frame Counter event occurs
    LCD_FrameCountInit_TypeDef fc_init = {
      .enable = true,
      .top = 32,
      .prescale = SL_SEGMENT_LCD_BACFG_FCPRESC
    };
    LCD_FrameCountInit(&fc_init);
  #if defined(SL_SEGMENT_LCD_MODULE_CE322_1002)
    // Sync the SEGn registers automatically when SEG3 is written to
    LCD_SyncStart(true, lcdLoadAddrSegd3);
  #elif defined(SL_SEGMENT_LCD_MODULE_CL010_1087)
    // Sync the SEGn registers automatically when SEG7 is written to
    LCD_SyncStart(true, lcdLoadAddrSegd7);
  #endif
  }
  /* Turn all segments off */
  sl_segment_lcd_all_off();

#if defined(_SILICON_LABS_32B_SERIES_0) || defined(_SILICON_LABS_32B_SERIES_1)
  LCD_SyncBusyDelay(0xFFFFFFFF);
#else
  LCD_ReadyWait();
#endif
}

/**************************************************************************//**
 *    Write a hexadecimal number on lower alphanumeric part of
 *    Segment LCD display
 *****************************************************************************/
#if defined(SL_SEGMENT_LCD_MODULE_CL010_1087) || defined(SL_SEGMENT_LCD_MODULE_CE322_1001)
void sl_segment_lcd_lower_hex(uint32_t num)
{
  int8_t    i;
  char      str[SL_SEGMENT_LCD_ALPHA_DIGITS + 1];
  uint32_t  nibble;

#if defined(SL_SEGMENT_LCD_MODULE_CL010_1087)
  sl_segment_lcd_symbol(SL_LCD_SYMBOL_MINUS, 0);
#endif

  for (i = (SL_SEGMENT_LCD_ALPHA_DIGITS - 1); i >= 0; i--) {
    nibble = num & 0xF;

    if ( nibble < 10 ) {
      str[i] = nibble + '0';
    } else if ( nibble == 11 ) {
      str[i] = 'b';
    } else if ( nibble == 13 ) {
      str[i] = 'd';
    } else {
      str[i] = (nibble - 10) + 'A';
    }

    num >>= 4;
  }

  sl_segment_lcd_write(str);
}
#endif

/**************************************************************************//**
 *    Write number on lower alphanumeric part of Segment LCD display
 *****************************************************************************/
#if defined(SL_SEGMENT_LCD_MODULE_CL010_1087) || defined(SL_SEGMENT_LCD_MODULE_CE322_1001)
void sl_segment_lcd_lower_number(int num)
{
  int8_t i;
  char str[SL_SEGMENT_LCD_ALPHA_DIGITS + 1];
  bool neg = false;
  bool val = true;

  memset(str, 0, sizeof(str));
#if defined(_SILICON_LABS_32B_SERIES_0)
  sl_segment_lcd_symbol(SL_LCD_SYMBOL_MINUS, false);
#endif

  if ((num > SL_SEGMENT_LCD_ALPHA_VAL_MAX) || (num < SL_SEGMENT_LCD_ALPHA_VAL_MIN)) {
    sl_segment_lcd_write("Ovrflow");
    return;
  }

  if (num < 0) {
    num = -num;
    neg = true;
  }

  for (i = (SL_SEGMENT_LCD_ALPHA_DIGITS - 1); i >= 0; i--) {
    if (val) {
      str[i] = (num % 10) + '0';
    } else {
      str[i] = neg ? '-' : ' ';
      neg = false;
    }
    num /= 10;
    val = (num != 0);
  }
#if defined(_SILICON_LABS_32B_SERIES_0)
  if (neg) {
    sl_segment_lcd_symbol(SL_LCD_SYMBOL_MINUS, true);
  }
#endif

  sl_segment_lcd_write(str);
}
#endif

/**************************************************************************//**
 *    Write temperature on Segment LCD display
 *****************************************************************************/
void sl_segment_lcd_temp_display(int32_t temp_data)
{
#if defined(SL_SEGMENT_LCD_MODULE_CE322_1002)
  /* Used when the temperature is below 0 degrees Celsius */
  if (temp_data < SL_SEGMENT_LCD_NEGATIVE_CASE) {
    temp_data = temp_data / 10;
    sl_segment_lcd_number(temp_data);           // Display the value of temp_data
    sl_segment_lcd_symbol(SL_LCD_SYMBOL_DEGC, 1);  // Display Degree C symbol
    sl_segment_lcd_symbol(SL_LCD_SYMBOL_P3, 1);    // Display decimal symbol

  /* Used when the temperature is above 100 degrees Celsius */
  } else if (temp_data >= SL_SEGMENT_LCD_THREE_DIGIT_CASE) {
    temp_data = temp_data / 10;
    sl_segment_lcd_number(temp_data);           // Display the value of temp_data
    sl_segment_lcd_symbol(SL_LCD_SYMBOL_DEGC, 1);  // Display Degree C symbol
    sl_segment_lcd_symbol(SL_LCD_SYMBOL_P3, 1);    // Display decimal symbol

   /* Used when the temperature is between 0-100 degrees Celsius */
  } else {
    sl_segment_lcd_number(temp_data);           // Display the value of temp_data
    sl_segment_lcd_symbol(SL_LCD_SYMBOL_DEGC, 1);  // Display Degree C symbol
    sl_segment_lcd_symbol(SL_LCD_SYMBOL_P2, 1);    // Display decimal symbol
  }
#elif defined(SL_SEGMENT_LCD_MODULE_CL010_1087)
  /*
   * Using segment_lcd_lower_number(), the lower
   * segments on the display are utilized. segment_lcd_lower_number() converts
   * signed value to text and will print alpha-numeric minus symbol when
   * measurement is negative. Turn on decimal symbol at appropriate
   * location.
   */
  sl_segment_lcd_lower_number(temp_data);     // Display the value of temp_data
  sl_segment_lcd_symbol(SL_LCD_SYMBOL_DEGC, 1);  // Display Degree C symbol
  sl_segment_lcd_symbol(SL_LCD_SYMBOL_DP5, 1);   // Display decimal symbol
#endif
}

/**************************************************************************//**
 *    Write number on numeric part on Segment LCD display
 *****************************************************************************/
void sl_segment_lcd_number(int value)
{
  uint8_t  i, com, bit, digit, neg;
  uint32_t div;
  uint32_t j, segment_data_reg[LCD_COM_LINES_MAX];
  uint16_t bitpattern;
  uint16_t num;

  /* Parameter consistency check */
  if (value >= SL_SEGMENT_LCD_NUM_VAL_MAX) {
    value = SL_SEGMENT_LCD_NUM_VAL_MAX;
  }
  if (value < SL_SEGMENT_LCD_NUM_VAL_MIN) {
    value = SL_SEGMENT_LCD_NUM_VAL_MIN;
  }
  if (value < 0) {
    value = abs(value);
    neg   = 1;
  } else {
    neg = 0;
  }

  /* If an update is in progress we must block, or there might be tearing */
#if defined(_SILICON_LABS_32B_SERIES_0) || defined(_SILICON_LABS_32B_SERIES_1)
  LCD_SyncBusyDelay(0xFFFFFFFF);
  /* Freeze updates to avoid partial refresh of display */
  LCD_FreezeEnable(true);
#else
  LCD_LoadBusyWait();
#endif

  for (j = 0; j < LCD_COM_LINES_MAX; j++) {
    segment_data_reg[j] = 0;
  }

  /* Extract useful digits */
  div = 1;
  for (digit = 0; digit < SL_SEGMENT_LCD_NUM_DIGITS; digit++) {
    num = (value / div) % 10;
    if ((neg == 1) && (digit == (SL_SEGMENT_LCD_NUM_DIGITS - 1))) {
      num = sign_index;
    }
    /* Get number layout of display */
    bitpattern = segment_numbers[num];
    for (i = 0; i < 7; i++) {
      bit = efm_display.number[digit].bit[i];
      com = efm_display.number[digit].com[i];
      if (bitpattern & (1 << i)) {
        segment_data_reg[com] |= (1 << bit);
      }
    }
    div = div * 10;
  }

  for (j = 0; j < LCD_COM_LINES_MAX; j++) {
    LCD_SegmentSetLow(j, SL_SEGMENT_LCD_ALL_SEG_BITMASK, segment_data_reg[j]);
  }

  /* Sync LCD registers to LE domain */
#if defined(_SILICON_LABS_32B_SERIES_0) || defined(_SILICON_LABS_32B_SERIES_1)
  LCD_FreezeEnable(false);
#else
  LCD_SyncStart(false, lcdLoadAddrNone);
  LCD_LoadBusyWait();
#endif

#if defined(_SILICON_LABS_32B_SERIES_1) || defined(_SILICON_LABS_32B_SERIES_2)
  /* Evaluating the updated display contents and switching charge
     redistribution ON or OFF accordingly (only if dynamic change is enabled) */
  if (dynamic_chg_redist_enabled) {
    sl_segment_lcd_update_chg_rdst();
  }
#endif
}

/**************************************************************************//**
 *    Turn all segments on numeric digits in display off
 *****************************************************************************/
void sl_segment_lcd_number_off(void)
{
  /* Turn off all number segments */
  SL_SEGMENT_LCD_NUMBER_OFF();

#if defined(_SILICON_LABS_32B_SERIES_2)
  LCD_SyncStart(false, lcdLoadAddrNone);
  LCD_LoadBusyWait();
#endif

#if defined(_SILICON_LABS_32B_SERIES_1)
  /* Evaluating the updated display contents and switching charge
     redistribution ON or OFF accordingly (only if dynamic change is enabled) */
  if (dynamic_chg_redist_enabled) {
    sl_segment_lcd_update_chg_rdst();
  }
#endif
}

/**************************************************************************//**
 *    Light up or shut off various symbols on Segment LCD
 *****************************************************************************/
void sl_segment_lcd_symbol(sl_segment_lcd_symbol_t s, int on)
{
  uint8_t com = 0;
  uint8_t bit = 0;

  switch (s) {
#ifdef SL_LCD_SYMBOL_GECKO_SEG
    case SL_LCD_SYMBOL_GECKO:
      com = SL_LCD_SYMBOL_GECKO_COM;
      bit = SL_LCD_SYMBOL_GECKO_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_ANT_SEG
    case SL_LCD_SYMBOL_ANT:
      com = SL_LCD_SYMBOL_ANT_COM;
      bit = SL_LCD_SYMBOL_ANT_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_PAD0_SEG
    case SL_LCD_SYMBOL_PAD0:
      com = SL_LCD_SYMBOL_PAD0_COM;
      bit = SL_LCD_SYMBOL_PAD0_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_PAD1_SEG
    case SL_LCD_SYMBOL_PAD1:
      com = SL_LCD_SYMBOL_PAD1_COM;
      bit = SL_LCD_SYMBOL_PAD1_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_EFM32_SEG
    case SL_LCD_SYMBOL_EFM32:
      com = SL_LCD_SYMBOL_EFM32_COM;
      bit = SL_LCD_SYMBOL_EFM32_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_MINUS_SEG
    case SL_LCD_SYMBOL_MINUS:
      com = SL_LCD_SYMBOL_MINUS_COM;
      bit = SL_LCD_SYMBOL_MINUS_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_C1_SEG
    case SL_LCD_SYMBOL_C1:
      com = SL_LCD_SYMBOL_C1_COM;
      bit = SL_LCD_SYMBOL_C1_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_C2_SEG
    case SL_LCD_SYMBOL_C2:
      com = SL_LCD_SYMBOL_C2_COM;
      bit = SL_LCD_SYMBOL_C2_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_C3_SEG
    case SL_LCD_SYMBOL_C3:
      com = SL_LCD_SYMBOL_C3_COM;
      bit = SL_LCD_SYMBOL_C3_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_C4_SEG
    case SL_LCD_SYMBOL_C4:
      com = SL_LCD_SYMBOL_C4_COM;
      bit = SL_LCD_SYMBOL_C4_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_C5_SEG
    case SL_LCD_SYMBOL_C5:
      com = SL_LCD_SYMBOL_C5_COM;
      bit = SL_LCD_SYMBOL_C5_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_C6_SEG
    case SL_LCD_SYMBOL_C6:
      com = SL_LCD_SYMBOL_C6_COM;
      bit = SL_LCD_SYMBOL_C6_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_C7_SEG
    case SL_LCD_SYMBOL_C7:
      com = SL_LCD_SYMBOL_C7_COM;
      bit = SL_LCD_SYMBOL_C7_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_C8_SEG
    case SL_LCD_SYMBOL_C8:
      com = SL_LCD_SYMBOL_C8_COM;
      bit = SL_LCD_SYMBOL_C8_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_C9_SEG
    case SL_LCD_SYMBOL_C9:
      com = SL_LCD_SYMBOL_C9_COM;
      bit = SL_LCD_SYMBOL_C9_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_C10_SEG
    case SL_LCD_SYMBOL_C10:
      com = SL_LCD_SYMBOL_C10_COM;
      bit = SL_LCD_SYMBOL_C10_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_C11_SEG
    case SL_LCD_SYMBOL_C11:
      com = SL_LCD_SYMBOL_C11_COM;
      bit = SL_LCD_SYMBOL_C11_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_C12_SEG
    case SL_LCD_SYMBOL_C12:
      com = SL_LCD_SYMBOL_C12_COM;
      bit = SL_LCD_SYMBOL_C12_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_C13_SEG
    case SL_LCD_SYMBOL_C13:
      com = SL_LCD_SYMBOL_C13_COM;
      bit = SL_LCD_SYMBOL_C13_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_C14_SEG
    case SL_LCD_SYMBOL_C14:
      com = SL_LCD_SYMBOL_C14_COM;
      bit = SL_LCD_SYMBOL_C14_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_C15_SEG
    case SL_LCD_SYMBOL_C15:
      com = SL_LCD_SYMBOL_C15_COM;
      bit = SL_LCD_SYMBOL_C15_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_C16_SEG
    case SL_LCD_SYMBOL_C16:
      com = SL_LCD_SYMBOL_C16_COM;
      bit = SL_LCD_SYMBOL_C16_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_C17_SEG
    case SL_LCD_SYMBOL_C17:
      com = SL_LCD_SYMBOL_C17_COM;
      bit = SL_LCD_SYMBOL_C17_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_C18_SEG
    case SL_LCD_SYMBOL_C18:
      com = SL_LCD_SYMBOL_C18_COM;
      bit = SL_LCD_SYMBOL_C18_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_C19_SEG
    case SL_LCD_SYMBOL_C19:
      com = SL_LCD_SYMBOL_C19_COM;
      bit = SL_LCD_SYMBOL_C19_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_COL1_SEG
    case SL_LCD_SYMBOL_COL1:
      com = SL_LCD_SYMBOL_COL1_COM;
      bit = SL_LCD_SYMBOL_COL1_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_COL2_SEG
    case SL_LCD_SYMBOL_COL2:
      com = SL_LCD_SYMBOL_COL2_COM;
      bit = SL_LCD_SYMBOL_COL2_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_COL3_SEG
    case SL_LCD_SYMBOL_COL3:
      com = SL_LCD_SYMBOL_COL3_COM;
      bit = SL_LCD_SYMBOL_COL3_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_COL5_SEG
    case SL_LCD_SYMBOL_COL5:
      com = SL_LCD_SYMBOL_COL5_COM;
      bit = SL_LCD_SYMBOL_COL5_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_COL10_SEG
    case SL_LCD_SYMBOL_COL10:
      com = SL_LCD_SYMBOL_COL10_COM;
      bit = SL_LCD_SYMBOL_COL10_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_DEGC_SEG
    case SL_LCD_SYMBOL_DEGC:
      com = SL_LCD_SYMBOL_DEGC_COM;
      bit = SL_LCD_SYMBOL_DEGC_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_DEGF_SEG
    case SL_LCD_SYMBOL_DEGF:
      com = SL_LCD_SYMBOL_DEGF_COM;
      bit = SL_LCD_SYMBOL_DEGF_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_DP2_SEG
    case SL_LCD_SYMBOL_DP2:
      com = SL_LCD_SYMBOL_DP2_COM;
      bit = SL_LCD_SYMBOL_DP2_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_DP3_SEG
    case SL_LCD_SYMBOL_DP3:
      com = SL_LCD_SYMBOL_DP3_COM;
      bit = SL_LCD_SYMBOL_DP3_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_DP4_SEG
    case SL_LCD_SYMBOL_DP4:
      com = SL_LCD_SYMBOL_DP4_COM;
      bit = SL_LCD_SYMBOL_DP4_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_DP5_SEG
    case SL_LCD_SYMBOL_DP5:
      com = SL_LCD_SYMBOL_DP5_COM;
      bit = SL_LCD_SYMBOL_DP5_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_DP6
    case SL_LCD_SYMBOL_DP6:
      com = SL_LCD_SYMBOL_DP6_COM;
      bit = SL_LCD_SYMBOL_DP6_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_DP10
    case SL_LCD_SYMBOL_DP10:
      com = SL_LCD_SYMBOL_DP10_COM;
      bit = SL_LCD_SYMBOL_DP10_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_AM_SEG
    case SL_LCD_SYMBOL_AM:
      com = SL_LCD_SYMBOL_AM_COM;
      bit = SL_LCD_SYMBOL_AM_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_PM_SEG
    case SL_LCD_SYMBOL_PM:
      com = SL_LCD_SYMBOL_PM_COM;
      bit = SL_LCD_SYMBOL_PM_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_MICROAMP_SEG
    case SL_LCD_SYMBOL_MICROAMP:
      com = SL_LCD_SYMBOL_MICROAMP_COM;
      bit = SL_LCD_SYMBOL_MICROAMP_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_MILLIAMP_SEG
    case SL_LCD_SYMBOL_MILLIAMP:
      com = SL_LCD_SYMBOL_MILLIAMP_COM;
      bit = SL_LCD_SYMBOL_MILLIAMP_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_S2_SEG
    case SL_LCD_SYMBOL_S2:
      com = SL_LCD_SYMBOL_S2_COM;
      bit = SL_LCD_SYMBOL_S2_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_S3_SEG
    case SL_LCD_SYMBOL_S3:
      com = SL_LCD_SYMBOL_S3_COM;
      bit = SL_LCD_SYMBOL_S3_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_S4_SEG
    case SL_LCD_SYMBOL_S4:
      com = SL_LCD_SYMBOL_S4_COM;
      bit = SL_LCD_SYMBOL_S4_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_S5_SEG
    case SL_LCD_SYMBOL_S5:
      com = SL_LCD_SYMBOL_S5_COM;
      bit = SL_LCD_SYMBOL_S5_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_S6_SEG
    case SL_LCD_SYMBOL_S6:
      com = SL_LCD_SYMBOL_S6_COM;
      bit = SL_LCD_SYMBOL_S6_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_S7_SEG
    case SL_LCD_SYMBOL_S7:
      com = SL_LCD_SYMBOL_S7_COM;
      bit = SL_LCD_SYMBOL_S7_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_S8_SEG
    case SL_LCD_SYMBOL_S8:
      com = SL_LCD_SYMBOL_S8_COM;
      bit = SL_LCD_SYMBOL_S8_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_S9_SEG
    case SL_LCD_SYMBOL_S9:
      com = SL_LCD_SYMBOL_S9_COM;
      bit = SL_LCD_SYMBOL_S9_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_S10_SEG
    case SL_LCD_SYMBOL_S10:
      com = SL_LCD_SYMBOL_S10_COM;
      bit = SL_LCD_SYMBOL_S10_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_S11_SEG
    case SL_LCD_SYMBOL_S11:
      com = SL_LCD_SYMBOL_S11_COM;
      bit = SL_LCD_SYMBOL_S11_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_S12_SEG
    case SL_LCD_SYMBOL_S12:
      com = SL_LCD_SYMBOL_S12_COM;
      bit = SL_LCD_SYMBOL_S12_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_S13_SEG
    case SL_LCD_SYMBOL_S13:
      com = SL_LCD_SYMBOL_S13_COM;
      bit = SL_LCD_SYMBOL_S13_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_S14_SEG
    case SL_LCD_SYMBOL_S14:
      com = SL_LCD_SYMBOL_S14_COM;
      bit = SL_LCD_SYMBOL_S14_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_P2_SEG
    case SL_LCD_SYMBOL_P2:
      com = SL_LCD_SYMBOL_P2_COM;
      bit = SL_LCD_SYMBOL_P2_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_P3_SEG
    case SL_LCD_SYMBOL_P3:
      com = SL_LCD_SYMBOL_P3_COM;
      bit = SL_LCD_SYMBOL_P3_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_P4_SEG
    case SL_LCD_SYMBOL_P4:
      com = SL_LCD_SYMBOL_P4_COM;
      bit = SL_LCD_SYMBOL_P4_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_P5_SEG
    case SL_LCD_SYMBOL_P5:
      com = SL_LCD_SYMBOL_P5_COM;
      bit = SL_LCD_SYMBOL_P5_SEG;
      break;
#endif
#ifdef SL_LCD_SYMBOL_P6_SEG
    case SL_LCD_SYMBOL_P6:
      com = SL_LCD_SYMBOL_P6_COM;
      bit = SL_LCD_SYMBOL_P6_SEG;
      break;
#endif
    default:
      break;
  }
  if (on) {
    LCD_SegmentSet(com, bit, true);
  } else {
    LCD_SegmentSet(com, bit, false);
  }

#if defined(_SILICON_LABS_32B_SERIES_2)
  LCD_SyncStart(false, lcdLoadAddrNone);
  LCD_LoadBusyWait();
#endif

#if defined(_SILICON_LABS_32B_SERIES_1) || defined(_SILICON_LABS_32B_SERIES_2)
  /* Evaluating the updated display contents and switching charge
     redistribution ON or OFF accordingly (only if dynamic change is enabled) */
  if (dynamic_chg_redist_enabled) {
    sl_segment_lcd_update_chg_rdst();
  }
#endif
}

/**************************************************************************//**
 *    Write hexadecimal number on numeric part on Segment LCD display
 *****************************************************************************/
void sl_segment_lcd_unsigned_hex(uint32_t value)
{
  uint8_t      num, i, com, bit, digit;
  uint32_t j, segment_data_reg[LCD_COM_LINES_MAX];
  uint16_t bitpattern;

  /* Parameter consistancy check */
  if (value >= SL_SEGMENT_LCD_NUM_VAL_MAX_HEX) {
    value = SL_SEGMENT_LCD_NUM_VAL_MAX_HEX;
  }

#if defined(_SILICON_LABS_32B_SERIES_0) || defined(_SILICON_LABS_32B_SERIES_1)
  /* If an update is in progress we must block, or there might be tearing */
  LCD_SyncBusyDelay(0xFFFFFFFF);

  /* Freeze updates to avoid partial refresh of display */
  LCD_FreezeEnable(true);
#else
  LCD_LoadBusyWait();
#endif

  for (j = 0; j < LCD_COM_LINES_MAX; j++) {
    segment_data_reg[j] = 0;
  }

  for (digit = 0; digit < SL_SEGMENT_LCD_NUM_DIGITS; digit++) {
    num        = (value >> (4 * digit)) & 0x0f;
    bitpattern = segment_numbers[num];
    for (i = 0; i < 7; i++) {
      bit = efm_display.number[digit].bit[i];
      com = efm_display.number[digit].com[i];
      if (bitpattern & (1 << i)) {
        segment_data_reg[com] = (1 << bit);
      }
    }
  }

  for (j = 0; j < LCD_COM_LINES_MAX; j++) {
    LCD_SegmentSetLow(j, SL_SEGMENT_LCD_ALL_SEG_BITMASK, segment_data_reg[j]);
  }

#if defined(_SILICON_LABS_32B_SERIES_0) || defined(_SILICON_LABS_32B_SERIES_1)
  /* Sync LCD registers to LE domain */
  LCD_FreezeEnable(false);
#else
  LCD_SyncStart(false, lcdLoadAddrNone);
  LCD_LoadBusyWait();
#endif

#if defined(_SILICON_LABS_32B_SERIES_1) || defined(_SILICON_LABS_32B_SERIES_2)
  /* Evaluating the updated display contents and switching charge
     redistribution ON or OFF accordingly (only if dynamic change is enabled) */
  if (dynamic_chg_redist_enabled) {
    sl_segment_lcd_update_chg_rdst();
  }
#endif
}

/**************************************************************************//**
 *    Write text on LCD display
 *****************************************************************************/
#if defined(SL_SEGMENT_LCD_MODULE_CL010_1087) || defined(SL_SEGMENT_LCD_MODULE_CE322_1001)
void sl_segment_lcd_write(const char *string)
{
  uint8_t  data, length, index, i;
  uint32_t j, segment_data_reg[LCD_COM_LINES_MAX];
  uint16_t bitfield;
  uint32_t com, bit;

  length = strlen(string);
  index  = 0;

  /* If an update is in progress we must block, or there might be tearing */
#if defined(_SILICON_LABS_32B_SERIES_0) || defined(_SILICON_LABS_32B_SERIES_1)
  LCD_SyncBusyDelay(0xFFFFFFFF);

  /* Freeze LCD to avoid partial updates */
  LCD_FreezeEnable(true);
#else
  LCD_ReadyWait();
#endif

  for (j = 0; j < LCD_COM_LINES_MAX; j++) {
    segment_data_reg[j] = 0;
  }

  /* Turn all segments off */
  sl_segment_lcd_alpha_number_off();

  /* Fill out all characters on display */
  for (index = 0; index < SL_SEGMENT_LCD_ALPHA_DIGITS; index++) {
    if (index < length) {
      data = (int) *string;
    } else {       /* Padding with space */
      data = 0x20; /* SPACE */
    }
    /* Defined letters currently starts at "SPACE" - ASCII 0x20; */
    data = data - 0x20;
    /* Get font for this letter */
    bitfield = segment_alphabet[data];

    for (i = 0; i < 14; i++) {
      bit = efm_display.text[index].bit[i];
      com = efm_display.text[index].com[i];

      if (bitfield & (1 << i)) {
        /* Turn on segment */
        segment_data_reg[com] |= (1 << bit);
      }
    }
    string++;
  }

  for (j = 0; j < LCD_COM_LINES_MAX; j++) {
    LCD_SegmentSetLow(j, SL_SEGMENT_LCD_ALL_SEG_BITMASK, segment_data_reg[j]);
  }

#if defined(_SILICON_LABS_32B_SERIES_0) || defined(_SILICON_LABS_32B_SERIES_1)
  /* Sync LCD registers to LE domain */
  LCD_FreezeEnable(false);
#else
  LCD_SyncStart(false, lcdLoadAddrNone);
  LCD_LoadBusyWait();
#endif

#if defined(_SILICON_LABS_32B_SERIES_1) || defined(_SILICON_LABS_32B_SERIES_2)
  /* Evaluating the updated display contents and switching charge
     redistribution ON or OFF accordingly (only if dynamic change is enabled) */
  if (dynamic_chg_redist_enabled) {
    sl_segment_lcd_update_chg_rdst();
  }
#endif
}
#endif

/**************************************************************************//**
 *    Counting the number of active segments in a single common line
 *****************************************************************************/
#if defined(_SILICON_LABS_32B_SERIES_1) || defined(_SILICON_LABS_32B_SERIES_2)
uint16_t sl_segment_lcd_seg_cnt(uint32_t segdl, uint32_t segdh)
{
  /* Number of ones in a nibble */
  const uint8_t one_cnt[16] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4 };

  uint16_t cnt = 0;

  /* Accumulating number of ones in each nibble */
  cnt += one_cnt[(segdl >>  0) & 0x0000000f];
  cnt += one_cnt[(segdl >>  4) & 0x0000000f];
  cnt += one_cnt[(segdl >>  8) & 0x0000000f];
  cnt += one_cnt[(segdl >> 12) & 0x0000000f];
  cnt += one_cnt[(segdl >> 16) & 0x0000000f];
  cnt += one_cnt[(segdl >> 20) & 0x0000000f];
  cnt += one_cnt[(segdl >> 24) & 0x0000000f];
  cnt += one_cnt[(segdl >> 28) & 0x0000000f];
  cnt += one_cnt[(segdh >>  0) & 0x0000000f];
  cnt += one_cnt[(segdh >>  4) & 0x0000000f];

  return cnt;
}
#endif

/**************************************************************************//**
 *    Enabling/disabling dynamic charge redistribution
 *****************************************************************************/
#if defined(_SILICON_LABS_32B_SERIES_1) || defined(_SILICON_LABS_32B_SERIES_2)
void sl_segment_lcd_charge_redistribution_enable(bool enable)
{
  /* Disable the controller before reconfiguration. */
  LCD_Enable(false);
#if defined(_SILICON_LABS_32B_SERIES_2)
  LCD_ReadyWait();
#endif
  if ( enable ) {
    LCD->DISPCTRL = (LCD->DISPCTRL & ~_LCD_DISPCTRL_CHGRDST_MASK)
                    | lcdChargeRedistributionEnable;
    dynamic_chg_redist_enabled = true;
  } else {
    LCD->DISPCTRL = (LCD->DISPCTRL & ~_LCD_DISPCTRL_CHGRDST_MASK)
                    | lcdChargeRedistributionDisable;
    dynamic_chg_redist_enabled = false;
  }
  LCD_Enable(true);
}
#endif

/**************************************************************************//**
 *    Dynamically switching charge redistribution ON/OFF based on display contents
 *****************************************************************************/
#if defined(_SILICON_LABS_32B_SERIES_1) || defined(_SILICON_LABS_32B_SERIES_2)
void sl_segment_lcd_update_chg_rdst(void)
{
  bool switch_chg_redist_on_old = ((LCD->DISPCTRL & _LCD_DISPCTRL_CHGRDST_MASK) != 0);
  const uint16_t COM_0_THRESHOLD_HI = 20;
  const uint16_t COM_0_THRESHOLD_LO = 14;
  const uint16_t COM_1_6_THRESHOLD_HI = 11;
  const uint16_t COM_1_6_THRESHOLD_LO = 9;
#if defined(_SILICON_LABS_32B_SERIES_1)
  const uint16_t COM_7_THRESHOLD_HI = 28;
  const uint16_t COM_7_THRESHOLD_LO = 24;
#endif
  const uint16_t SEG_TOTAL_THRESHOLD = 40;
  uint32_t segdl;
  uint16_t seg_cnt_acc = 0, seg_cnt;
  bool threshold_hi_reached = false;
  bool threshold_lo_reached = false;
  bool switch_chg_redist_on = false;

#if defined(_SILICON_LABS_32B_SERIES_1)
  segdl = LCD->SEGD0L;
  seg_cnt = sl_segment_lcd_seg_cnt(segdl, LCD->SEGD0H);
#else
  segdl = LCD->SEGD0;
  seg_cnt = sl_segment_lcd_seg_cnt(segdl, 0);
#endif
  if (seg_cnt >= COM_0_THRESHOLD_HI) {
    threshold_hi_reached = true;
  }
  if (seg_cnt >= COM_0_THRESHOLD_LO) {
    threshold_lo_reached = true;
  }
  seg_cnt_acc += seg_cnt;

#if defined(_SILICON_LABS_32B_SERIES_1)
  segdl = LCD->SEGD1L;
  seg_cnt = sl_segment_lcd_seg_cnt(segdl, LCD->SEGD1H);
#else
  segdl = LCD->SEGD1;
  seg_cnt = sl_segment_lcd_seg_cnt(segdl, 0);
#endif
  if (seg_cnt >= COM_1_6_THRESHOLD_HI) {
    threshold_hi_reached = true;
  }
  if (seg_cnt >= COM_1_6_THRESHOLD_LO) {
    threshold_lo_reached = true;
  }
  seg_cnt_acc += seg_cnt;

#if defined(_SILICON_LABS_32B_SERIES_1)
  segdl = LCD->SEGD2L;
  seg_cnt = sl_segment_lcd_seg_cnt(segdl, LCD->SEGD2H);
#else
  segdl = LCD->SEGD2;
  seg_cnt = sl_segment_lcd_seg_cnt(segdl, 0);
#endif
  if (seg_cnt >= COM_1_6_THRESHOLD_HI) {
    threshold_hi_reached = true;
  }
  if (seg_cnt >= COM_1_6_THRESHOLD_LO) {
    threshold_lo_reached = true;
  }
  seg_cnt_acc += seg_cnt;

#if defined(_SILICON_LABS_32B_SERIES_1)
  segdl = LCD->SEGD3L;
  seg_cnt = sl_segment_lcd_seg_cnt(segdl, LCD->SEGD3H);
#else
  segdl = LCD->SEGD3;
  seg_cnt = sl_segment_lcd_seg_cnt(segdl, 0);
#endif
  if (seg_cnt >= COM_1_6_THRESHOLD_HI) {
    threshold_hi_reached = true;
  }
  if (seg_cnt >= COM_1_6_THRESHOLD_LO) {
    threshold_lo_reached = true;
  }
  seg_cnt_acc += seg_cnt;

#if defined(_SILICON_LABS_32B_SERIES_1)
  segdl = LCD->SEGD4L;
  seg_cnt = sl_segment_lcd_seg_cnt(segdl, LCD->SEGD4H);
  if (seg_cnt >= COM_1_6_THRESHOLD_HI) {
    threshold_hi_reached = true;
  }
  if (seg_cnt >= COM_1_6_THRESHOLD_LO) {
    threshold_lo_reached = true;
  }
  seg_cnt_acc += seg_cnt;

  segdl = LCD->SEGD5L;
  seg_cnt = sl_segment_lcd_seg_cnt(segdl, LCD->SEGD5H);
  if (seg_cnt >= COM_1_6_THRESHOLD_HI) {
    threshold_hi_reached = true;
  }
  if (seg_cnt >= COM_1_6_THRESHOLD_LO) {
    threshold_lo_reached = true;
  }
  seg_cnt_acc += seg_cnt;

  segdl = LCD->SEGD6L;
  seg_cnt = sl_segment_lcd_seg_cnt(segdl, LCD->SEGD6H);
  if (seg_cnt >= COM_1_6_THRESHOLD_HI) {
    threshold_hi_reached = true;
  }
  if (seg_cnt >= COM_1_6_THRESHOLD_LO) {
    threshold_lo_reached = true;
  }
  seg_cnt_acc += seg_cnt;

  segdl = LCD->SEGD7L;
  seg_cnt = sl_segment_lcd_seg_cnt(segdl, LCD->SEGD7H);
  if (seg_cnt >= COM_7_THRESHOLD_HI) {
    threshold_hi_reached = true;
  }
  if (seg_cnt >= COM_7_THRESHOLD_LO) {
    threshold_lo_reached = true;
  }
  seg_cnt_acc += seg_cnt;
#endif

  /* Switch charge redistribution ON if condition 1 or 2 (or both) below is met
     1. at least one of the common lines has reached its high threshold
        of active segments
     2. at least one of the common lines has reached its low threshold
        of active segments and there are 40 or more active segments in
        the display (i.e. all common lines combined) */
  switch_chg_redist_on =
    (threshold_hi_reached)
    || (threshold_lo_reached && (seg_cnt_acc >= SEG_TOTAL_THRESHOLD));
  if(switch_chg_redist_on_old != switch_chg_redist_on){
    /* Disable the controller before reconfiguration. */
    LCD_Enable(false);
  #if defined(_SILICON_LABS_32B_SERIES_2)
    LCD_ReadyWait();
  #endif
    if (switch_chg_redist_on) {
      /* Switching charge redistribution ON */
      LCD->DISPCTRL = (LCD->DISPCTRL & ~_LCD_DISPCTRL_CHGRDST_MASK)
                      | lcdChargeRedistributionEnable;
    } else {
      /* Switching charge redistribution OFF */
      LCD->DISPCTRL = (LCD->DISPCTRL & ~_LCD_DISPCTRL_CHGRDST_MASK)
                      | lcdChargeRedistributionDisable;
    }
    LCD_Enable(true);
    switch_chg_redist_on_old = switch_chg_redist_on;
  }
}
#endif

/******************************************************************************
* @brief Display blocks on LCD display: blank, fill, outline, outline & fill
* @param topMode array of block modes for the top row with element zero
* representing the left-most column and element six representing the
* right-most column
* @param botMode array of block modes for the bottom row with element zero
* representing the left-most column and element six representing the
* right-most column
******************************************************************************/
#if defined(SL_SEGMENT_LCD_MODULE_CL010_1087) || defined(SL_SEGMENT_LCD_MODULE_CE322_1001)
static void display_block(
  sl_segment_lcd_block_mode_t top_mode[SL_SEGMENT_LCD_NUM_BLOCK_COLUMNS],
  sl_segment_lcd_block_mode_t bot_mode[SL_SEGMENT_LCD_NUM_BLOCK_COLUMNS])
{
  uint8_t  index;
  uint8_t  mode;
  uint16_t bitfield;
  uint32_t com, bit;
  uint8_t  i;

  /* Fill out all blocks in the top row of the display */
  for (index = 0; index < SL_SEGMENT_LCD_NUM_BLOCK_COLUMNS; index++) {
    mode = top_mode[index];

    /* Get segment bitmap for this block position */
    bitfield = blocks[mode];

    for (i = 0; i < 8; i++) {
      if (bitfield & (1 << i)) {
        bit = efm_display.top_blocks[index].bit[i];
        com = efm_display.top_blocks[index].com[i];

        // Turn on segment
        LCD_SegmentSet(com, bit, true);
      }
    }
  }
  /* Fill out all blocks in the bottom row of the display */
  for (index = 0; index < SL_SEGMENT_LCD_NUM_BLOCK_COLUMNS; index++) {
    mode = bot_mode[index];

    /* Get segment bitmap for this block position */
    bitfield = blocks[mode];

    for (i = 0; i < 8; i++) {
      if (bitfield & (1 << i)) {
        bit = efm_display.bot_blocks[index].bit[i];
        com = efm_display.bot_blocks[index].com[i];

        // Turn on segment
        LCD_SegmentSet(com, bit, true);
      }
    }
  }
}
#endif

#if defined(SL_SEGMENT_LCD_MODULE_CE322_1001)
/**************************************************************************//**
 *    Turn on or off individual pixels in the array
 *****************************************************************************/
void sl_segment_lcd_array(int element, bool on)
{
  uint32_t com, bit;

  com = efm_display.Array.com[element];
  bit = efm_display.Array.bit[element];
  LCD_SegmentSet(com, bit, on);
}

#elif defined(SL_SEGMENT_LCD_MODULE_CL010_1087)

/**************************************************************************//**
 *    Light up or shut off Ring of Indicators
 *****************************************************************************/
void sl_segment_lcd_aring(int anum, int on)
{
  uint32_t com, bit;

  com = efm_display.aring.com[anum];
  bit = efm_display.aring.bit[anum];

  if (on) {
    LCD_SegmentSet(com, bit, true);
  } else {
    LCD_SegmentSet(com, bit, false);
  }
}

/**************************************************************************//**
 *    Light up or shut off Battery Indicator
 *****************************************************************************/
void sl_segment_lcd_battery(int battery_level)
{
  uint32_t com, bit;
  int      i, on;

  for (i = 0; i < 4; i++) {
    if (i < battery_level) {
      on = 1;
    } else {
      on = 0;
    }
    com = efm_display.battery.com[i];
    bit = efm_display.battery.bit[i];

    if (on) {
      LCD_SegmentSet(com, bit, true);
    } else {
      LCD_SegmentSet(com, bit, false);
    }
  }
}

/**************************************************************************//**
 *    Light up or shut off Energy Mode indicator
 *****************************************************************************/
void sl_segment_lcd_energy_mode(int em, int on)
{
  uint32_t com, bit;

  com = efm_display.emode.com[em];
  bit = efm_display.emode.bit[em];

  if (on) {
    LCD_SegmentSet(com, bit, true);
  } else {
    LCD_SegmentSet(com, bit, false);
  }
}
#endif
/** @} (end group SegmentLcd) */
