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

#ifndef SL_SEGMENTLCD_H
#define SL_SEGMENTLCD_H

#include <stdbool.h>
#include <stdlib.h>
#include "em_device.h"
#include "sl_segmentlcd_config.h"

/***************************************************************************//**
 * @addtogroup SegmentLcd
 * @{
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

#if defined(SL_SEGMENT_LCD_MODULE_CL010_1087) || defined(SL_SEGMENT_LCD_MODULE_CE322_1001)
/**< Segment lcd block mode blank. */
#define SL_SEGMENT_LCD_BLOCK_MODE_BLANK          0
/**< Segment lcd block mode fill. */
#define SL_SEGMENT_LCD_BLOCK_MODE_FILL           1
/**< Segment lcd block mode outline. */
#define SL_SEGMENT_LCD_BLOCK_MODE_OUTLINE        2
/**< Segment lcd block mode outline fill. */
#define SL_SEGMENT_LCD_BLOCK_MODE_OUTLINE_FILL   3
/**< Segment lcd number of block columns. */
#define SL_SEGMENT_LCD_NUM_BLOCK_COLUMNS         7
#endif

#if defined(SL_SEGMENT_LCD_MODULE_CE322_1001) // EFM32TG11 STK
/**< Number of digits. */
#define SL_SEGMENT_LCD_NUM_DIGITS              6
/**< Number value max. */
#define SL_SEGMENT_LCD_NUM_VAL_MAX             999999
/**< Number value min. */
#define SL_SEGMENT_LCD_NUM_VAL_MIN             -99999
/**< Number value max hex. */
#define SL_SEGMENT_LCD_NUM_VAL_MAX_HEX         0xFFFFFF
/**< Number of alpha digits. */
#define SL_SEGMENT_LCD_ALPHA_DIGITS            8
/**< Alpha value max. */
#define SL_SEGMENT_LCD_ALPHA_VAL_MAX           99999999
/**< Alpha value min. */
#define SL_SEGMENT_LCD_ALPHA_VAL_MIN           -9999999
#elif defined(SL_SEGMENT_LCD_MODULE_CE322_1002) // xG23 kits (just 4 digits)
/**< Number of digits. */
#define SL_SEGMENT_LCD_NUM_DIGITS              5
/**< Number value max. */
#define SL_SEGMENT_LCD_NUM_VAL_MAX             99999
/**< Number value min. */
#define SL_SEGMENT_LCD_NUM_VAL_MIN             -9999
/**< Number value max hex.*/
#define SL_SEGMENT_LCD_NUM_VAL_MAX_HEX         0xFFFFF
#elif defined(SL_SEGMENT_LCD_MODULE_CL010_1087) // Series 0 STKs and PG28 PK
/**< Number of digits. */
#define SL_SEGMENT_LCD_NUM_DIGITS              4
/**< Number value max. */
#define SL_SEGMENT_LCD_NUM_VAL_MAX             9999
/**< Number value min. */
#define SL_SEGMENT_LCD_NUM_VAL_MIN             -999
/**< Number value max hex. */
#define SL_SEGMENT_LCD_NUM_VAL_MAX_HEX         0xFFFF
/**< Number of alpha digits. */
#define SL_SEGMENT_LCD_ALPHA_DIGITS            7
/**< Alpha value max. */
#define SL_SEGMENT_LCD_ALPHA_VAL_MAX           9999999
/**< Alpha value min. */
#define SL_SEGMENT_LCD_ALPHA_VAL_MIN           -9999999
#endif

#if defined(SL_SEGMENT_LCD_MODULE_CE322_1002)
#define SL_SEGMENT_LCD_NEGATIVE_CASE      0        // Used for negative temperature readings
#define SL_SEGMENT_LCD_THREE_DIGIT_CASE   100000   // Used for three-digit temperature readings
#endif
/**************************************************************************//**
 * @brief
 * Defines each text symbol's segment in terms of COM and BIT numbers,
 * in a way that we can enumerate each bit for each text segment in the
 * following bit pattern:
 * @verbatim
 *  -------0------
 *
 * |   \7  |8  /9 |
 * |5   \  |  /   |1
 *
 *  --6---  ---10--
 *
 * |    /  |  \11 |
 * |4  /13 |12 \  |2
 *
 *  -------3------
 * @endverbatim
 * E.g.: First text character bit pattern #3 (above) is
 * Segment 1D for Display
 * Location COM 3, BIT 0
 *****************************************************************************/
typedef struct {
  uint8_t com[14]; /**< LCD COM line (for multiplexing) */
  uint8_t bit[14]; /**< LCD bit number */
} sl_segment_lcd_char_t;

/**************************************************************************//**
 * @brief Defines segment COM and BIT fields numeric display
 *****************************************************************************/
typedef struct {
  uint8_t com[7]; /**< LCD COM line (for multiplexing) */
  uint8_t bit[7]; /**< LCD bit number */
} sl_segment_lcd_number_t;

/**************************************************************************//**
 * @brief Defines segment COM and BIT fields for Energy Modes on display
 *****************************************************************************/
typedef struct {
  uint8_t com[5]; /**< LCD COM line (for multiplexing) */
  uint8_t bit[5]; /**< LCD bit number */
} sl_segment_lcd_em_t;

/**************************************************************************//**
 * @brief Defines segment COM and BIT fields for A-wheel (suited for Anim)
 *****************************************************************************/
typedef struct {
  uint8_t com[8]; /**< LCD COM line (for multiplexing) */
  uint8_t bit[8]; /**< LCD bit number */
} sl_segment_lcd_aring_t;

/**************************************************************************//**
 * @brief Defines segment COM and BIT fields for Battery (suited for Anim)
 *****************************************************************************/
typedef struct {
  uint8_t com[4]; /**< LCD COM line (for multiplexing) */
  uint8_t bit[4]; /**< LCD bit number */
} sl_segment_lcd_battery_t;

/**************************************************************************//**
 * @brief Defines segment COM and BIT fields for array
 *****************************************************************************/
typedef struct {
  uint8_t com[35]; /**< LCD COM line (for multiplexing) */
  uint8_t bit[35]; /**< LCD bit number */
} sl_segment_lcd_array_t;

/**************************************************************************//**
 * @brief Defines segment COM and BIT fields for top and bottom row blocks.
 * The bit pattern shown above for characters can be split into upper and lower
 * portions for animation purposes. There are separate COM and BIT numbers
 * which together represent a set of stacked blocks which can be shown on two
 * rows in the segmented LCD screen.
 *
 * There are four blocks shown on the top row:
 * @verbatim
 *  -------0------
 *
 * |   \5  |6  /7 |
 * |2   \  |  /   |1
 *
 *  --3---  ---4--
 * @endverbatim
 *
 * There are four blocks shown on the bottom row :
 * @verbatim
 *  --3---  ---4--
 *
 * |    /  |  \5  |
 * |2  /7  |6  \  |0
 *
 *  -------1------
 * @endverbatim
 *
 * The upper row has four blocks which are placed directly above the four
 * blocks on the lower row. Each block can be in one of three states:
 * blank - outer five segments off, inner three segments off
 * outer - outer five segments on,  inner three segments off
 * inner - outer five segments off, inner three segments on
 * full  - outer five segments on,  inner three segments on
 *
 * @verbatim
 * Top row:    0 1 2 3 4 5 6 7
 * Bottom row: 0 1 2 3 4 5 6 7
 * @endverbatim
 *****************************************************************************/
typedef struct {
  uint8_t com[8]; /**< LCD COM line (for multiplexing) */
  uint8_t bit[8]; /**< LCD bit number */
} sl_segment_lcd_block_t;

/**************************************************************************//**
 * @brief Defines prototype for all segments in display
 *****************************************************************************/
#if defined(SL_SEGMENT_LCD_MODULE_CL010_1087)
typedef struct {
  sl_segment_lcd_char_t    text[SL_SEGMENT_LCD_ALPHA_DIGITS];       /**< Text on display */
  sl_segment_lcd_number_t  number[SL_SEGMENT_LCD_NUM_DIGITS];       /**< Numbers on display */
  sl_segment_lcd_em_t      emode;                    /**< Display energy mode */
  sl_segment_lcd_aring_t   aring;                    /**< Display ring */
  sl_segment_lcd_battery_t battery;                  /**< Display battery */
  sl_segment_lcd_block_t   top_blocks[SL_SEGMENT_LCD_ALPHA_DIGITS]; /**< Display top blocks */
  sl_segment_lcd_block_t   bot_blocks[SL_SEGMENT_LCD_ALPHA_DIGITS]; /**< Display bottom blocks */
} sl_segment_lcd_mcu_display_t;
#endif

#if defined(SL_SEGMENT_LCD_MODULE_CE322_1001)
typedef struct {
  sl_segment_lcd_char_t    text[SL_SEGMENT_LCD_ALPHA_DIGITS];       /**< Text on display */
  sl_segment_lcd_number_t  number[SL_SEGMENT_LCD_NUM_DIGITS];       /**< Numbers on display */
  sl_segment_lcd_array_t   Array;                    /**< Display array */
  sl_segment_lcd_block_t   top_blocks[SL_SEGMENT_LCD_ALPHA_DIGITS]; /**< Display top blocks */
  sl_segment_lcd_block_t   bot_blocks[SL_SEGMENT_LCD_ALPHA_DIGITS]; /**< Display bottom blocks */
} sl_segment_lcd_mcu_display_t;
#endif

#if defined(SL_SEGMENT_LCD_MODULE_CE322_1002)
typedef struct {
  sl_segment_lcd_number_t  number[SL_SEGMENT_LCD_NUM_DIGITS];        /**< Numbers on display */
} sl_segment_lcd_mcu_display_t;
#endif
/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/
/**************************************************************************//**
 * @brief Defines segment lcd block modes
 *****************************************************************************/
#if defined(SL_SEGMENT_LCD_MODULE_CL010_1087) || defined(SL_SEGMENT_LCD_MODULE_CE322_1001)
typedef enum {
  /**< segment lcd block mode Blank */
  sl_segment_lcd_block_mode_blank = SL_SEGMENT_LCD_BLOCK_MODE_BLANK,
  /**< segment lcd block mode Fill */
  sl_segment_lcd_block_mode_fill = SL_SEGMENT_LCD_BLOCK_MODE_FILL,
  /**< segment lcd block mode Outline */
  sl_segment_lcd_block_mode_outline = SL_SEGMENT_LCD_BLOCK_MODE_OUTLINE,
  /**< segment lcd block mode Outline and fill */
  sl_segment_lcd_block_mode_outline_fill = SL_SEGMENT_LCD_BLOCK_MODE_OUTLINE_FILL,
} sl_segment_lcd_block_mode_t;
#endif

/*******************************************************************************
 *******************************  FUNCTIONS  ***********************************
 ******************************************************************************/

/* Regular functions */
/**************************************************************************//**
 * @brief Disable all segments
 *****************************************************************************/
void sl_segment_lcd_all_off(void);

/**************************************************************************//**
 * @brief Enable all segments
 *****************************************************************************/
void sl_segment_lcd_all_on(void);

/**************************************************************************//**
 * @brief Turn all segments on alpha characters in display off
 *****************************************************************************/
#if defined(SL_SEGMENT_LCD_MODULE_CL010_1087) || defined(SL_SEGMENT_LCD_MODULE_CE322_1001)
void sl_segment_lcd_alpha_number_off(void);
#endif

/**************************************************************************//**
 * @brief Disables LCD controller
 *****************************************************************************/
void sl_segment_lcd_disable(void);


/**************************************************************************//**
 * @brief Segment LCD Initialization routine for EFM32 STK display
 * @param[in] useBoost Set to use voltage boost
 *****************************************************************************/
void sl_segment_lcd_init(bool use_boost);

#if defined(SL_SEGMENT_LCD_MODULE_CL010_1087) || defined(SL_SEGMENT_LCD_MODULE_CE322_1001)

/**************************************************************************//**
 * @brief Write a hexadecimal number on lower alphanumeric part of
 *        Segment LCD display
 * @param[in] num Hexadecimal number value to put on display, in range 0
 *        to 0x0FFFFFFF
 *****************************************************************************/
void sl_segment_lcd_lower_hex(uint32_t num);


/**************************************************************************//**
 * @brief Write number on lower alphanumeric part of Segment LCD display
 * @param[in] num Numeric value to put on display, in range -9999999 to +9999999
 *****************************************************************************/
void sl_segment_lcd_lower_number(int num);
#endif


/**************************************************************************//**
 * @brief Write number on numeric part on Segment LCD display
 * @param[in] value Numeric value to put on display, in range -999 to +9999
 *****************************************************************************/
void sl_segment_lcd_number(int value);

/**************************************************************************//**
 * @brief Write temperature on Segment LCD display
 * @details The following function are written to handle the cases when the sensor
 * measures negative temperature values, three digit temperature values, and
 * temperature values from 0-100 degrees Celsius. Keep in mind, the Si7021 part
 * has an operating temperature range of -40 to +125 degrees Celsius.
 * The temp_data variable stores a temperature read by the Si7021 that is
 * multiplied by a factor of 1000. In order to display the temperature correctly
 * in the negative and three digit cases, the temp_data variable must be divided
 * by 10 to remove one digit from the variable. Without this, the value of
 * temp_data passed to the SegmentLCD_Number() function may be higher than the
 * max value the Segment LCD could display.
 * @param[in] temperature value to put on display, in range -40000 to +125000
 *****************************************************************************/
void sl_segment_lcd_temp_display(int32_t temp_data);

/**************************************************************************//**
 * @brief Turn all segments on numeric digits in display off
 *****************************************************************************/
void sl_segment_lcd_number_off(void);


/**************************************************************************//**
 * @brief Light up or shut off various symbols on Segment LCD
 * @param[in] s Which symbol to turn on or off
 * @param[in] on Zero is off, non-zero is on
 *****************************************************************************/
void sl_segment_lcd_symbol(sl_segment_lcd_symbol_t s, int on);


/**************************************************************************//**
 * @brief Write hexadecimal number on numeric part on Segment LCD display
 * @param[in] value Numeric value to put on display
 *****************************************************************************/
void sl_segment_lcd_unsigned_hex(uint32_t value);

#if defined(SL_SEGMENT_LCD_MODULE_CL010_1087) || defined(SL_SEGMENT_LCD_MODULE_CE322_1001)

/**************************************************************************//**
 * @brief Write text on LCD display
 * @param[in] string Text string to show on display
 *****************************************************************************/
void sl_segment_lcd_write(const char *string);

/******************************************************************************
* @brief Display blocks on LCD display: blank, fill, outline, outline & fill
* @param[in] topMode array of block modes for the top row with element zero
* representing the left-most column and element six representing the
* right-most column
* @param[in] botMode array of block modes for the bottom row with element zero
* representing the left-most column and element six representing the
* right-most column
******************************************************************************/
void sl_segment_lcd_block(
  sl_segment_lcd_block_mode_t top_mode[SL_SEGMENT_LCD_NUM_BLOCK_COLUMNS],
  sl_segment_lcd_block_mode_t bot_mode[SL_SEGMENT_LCD_NUM_BLOCK_COLUMNS]);
#endif

#if defined(_SILICON_LABS_32B_SERIES_1) || defined(_SILICON_LABS_32B_SERIES_2)
// Dynamic charge redistribution

/**************************************************************************//**
 * @brief Counting the number of active segments in a single common line
 * @param[in] segdl in registers LCD_SEGDnL (n = common line number)
 * @param[in] segdh in registers LCD_SEGDnH (n = common line number)
 *****************************************************************************/
uint16_t sl_segment_lcd_seg_cnt(uint32_t segdl, uint32_t segdh);

/**************************************************************************//**
 * @brief Enabling/disabling dynamic charge redistribution
 * @param[in] true ==> enable, false ==> disable
 *****************************************************************************/
void sl_segment_lcd_charge_redistribution_enable(bool enable);


/**************************************************************************//**
 * @brief
 * Dynamically switching charge redistribution ON/OFF based on display contents
 * @param None
 *****************************************************************************/
void sl_segment_lcd_update_chg_rdst(void);
#endif

#if defined(SL_SEGMENT_LCD_MODULE_CE322_1001)
/**************************************************************************//**
 * @brief Turn on or off individual pixels in the array
 * @param[in] element "pixel number", range 0 - 34
 * @param[in] on false is off, true is on
 *****************************************************************************/
void sl_segment_lcd_array(int element, bool on);

#elif defined(SL_SEGMENT_LCD_MODULE_CL010_1087)

/**************************************************************************//**
 * @brief Light up or shut off Ring of Indicators
 * @param[in] anum "Segment number" on "Ring", range 0 - 7
 * @param[in] on Zero is off, non-zero is on
 *****************************************************************************/
void sl_segment_lcd_aring(int anum, int on);

/**************************************************************************//**
 * @brief Light up or shut off Battery Indicator
 * @param[in] batteryLevel Battery Level, 0 to 4 (0 turns all off)
 *****************************************************************************/
void sl_segment_lcd_battery(int battery_level);


/**************************************************************************//**
 * @brief Light up or shut off Energy Mode indicator
 * @param[in] em Energy Mode numer 0 to 4
 * @param[in] on Zero is off, non-zero is on
 *****************************************************************************/
void sl_segment_lcd_energy_mode(int em, int on);

#endif
#ifdef __cplusplus
}
#endif

/** @} (end group SegmentLcd) */

#endif
