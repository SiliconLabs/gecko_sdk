/***************************************************************************//**
 * @file
 * @brief Segment LCD Pin map for the EFM32PG28 Pro Kit Board (BRD2506A)
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
 
#ifndef SL_SEGMENTLCD_PIN_CONFIG_H
#define SL_SEGMENTLCD_PIN_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

// Map LCD segment S0 to LCD peripheral LCD_SEG0 etc
// Seg0 pin
#define SL_SEGMENT_LCD_SEG_S00 0
// Seg1 pin
#define SL_SEGMENT_LCD_SEG_S01 1
// Seg2 pin
#define SL_SEGMENT_LCD_SEG_S02 2
// Seg3 pin
#define SL_SEGMENT_LCD_SEG_S03 3
// Seg4 pin
#define SL_SEGMENT_LCD_SEG_S04 4
// Seg5 pin
#define SL_SEGMENT_LCD_SEG_S05 5
// Seg6 pin
#define SL_SEGMENT_LCD_SEG_S06 6
// Seg7 pin
#define SL_SEGMENT_LCD_SEG_S07 7
// Seg8 pin
#define SL_SEGMENT_LCD_SEG_S08 8
// Seg9 pin
#define SL_SEGMENT_LCD_SEG_S09 10
// Seg10 pin
#define SL_SEGMENT_LCD_SEG_S10 11
// Seg11 pin
#define SL_SEGMENT_LCD_SEG_S11 12
// Seg12 pin
#define SL_SEGMENT_LCD_SEG_S12 13
// Seg13 pin
#define SL_SEGMENT_LCD_SEG_S13 16
// Seg14 pin
#define SL_SEGMENT_LCD_SEG_S14 17
// Seg15 pin
#define SL_SEGMENT_LCD_SEG_S15 18
// Seg16 pin
#define SL_SEGMENT_LCD_SEG_S16 19
// Seg17 pin
#define SL_SEGMENT_LCD_SEG_S17 20
// Seg18 pin
#define SL_SEGMENT_LCD_SEG_S18 21
// Seg19 pin
#define SL_SEGMENT_LCD_SEG_S19 22

// Map LCD COM0 to LCD peripheral LCD_COM0 etc
// Com0 pin
#define SL_SEGMENT_LCD_COM_C00 0
// Com1 pin
#define SL_SEGMENT_LCD_COM_C01 1
// Com2 pin
#define SL_SEGMENT_LCD_COM_C02 2
// Com3 pin
#define SL_SEGMENT_LCD_COM_C03 3
// Com4 pin
#define SL_SEGMENT_LCD_COM_C04 4
// Com5 pin
#define SL_SEGMENT_LCD_COM_C05 5
// Com6 pin
#define SL_SEGMENT_LCD_COM_C06 6
// Com7 pin
#define SL_SEGMENT_LCD_COM_C07 7

#ifdef __cplusplus
}
#endif

#endif
