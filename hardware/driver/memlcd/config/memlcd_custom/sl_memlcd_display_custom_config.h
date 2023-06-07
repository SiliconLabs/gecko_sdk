/***************************************************************************//**
 * @file
 * @brief Custom LCD Using SPI Configuration File 
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

#ifndef SL_MEMLCD_DISPLAY_CUSTOM_CONFIG_H
#define SL_MEMLCD_DISPLAY_CUSTOM_CONFIG_H

#include "sl_memlcd_display.h"

// <<< Use Configuration Wizard in Context Menu >>>

// <h>Display Specifications

// <o SL_MEMLCD_DISPLAY_WIDTH> Memory LCD Diplay's Pixel Width <0-600>
// <i> Default: 128
#define SL_MEMLCD_DISPLAY_WIDTH    128

// <o SL_MEMLCD_DISPLAY_HEIGHT> Memory LCD Diplay's Pixel Height <0-600>
// <i> Default: 128
#define SL_MEMLCD_DISPLAY_HEIGHT    128

// <o SL_MEMLCD_DISPLAY_BPP> Memory LCD Diplay's BPP (Bits per pixel) <0-8>
// <i> Default: 1
#define SL_MEMLCD_DISPLAY_BPP    1

// <o SL_MEMLCD_DISPLAY_RGB_3BIT> Memory LCD Display's Color Mode
// <false=> Monochrome
// <true=> RGB
// <i> Default: false
#define SL_MEMLCD_DISPLAY_RGB_3BIT       false

// </h> end Display Specifications

// <h>SPI Specifications

// <o SL_MEMLCD_SCLK_FREQ> Memory LCD SPI's Clock Frequency <0-3000000>
// <i> Default: 1100000
#define SL_MEMLCD_SCLK_FREQ    1100000

// <o SL_MEMLCD_EXTCOMIN_FREQUENCY> Memory LCD's Extcomin Pin Toggle Frequency <54-65>
// <i> Default: 60
#define SL_MEMLCD_EXTCOMIN_FREQUENCY    60

// <o SL_MEMLCD_SCS_SETUP_US> Memory LCD SPI's CS Setup Time <1-6>
// <i> Default: 6
#define SL_MEMLCD_SCS_SETUP_US    6

// <o SL_MEMLCD_SCS_HOLD_US> Memory LCD SPI's CS Hold Time <1-2>
// <i> Default: 2
#define SL_MEMLCD_SCS_HOLD_US    2

// </h> end SPI Specifications

// <<< end of configuration section >>>

#endif
