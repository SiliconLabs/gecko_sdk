/***************************************************************************//**
 * @file
 * @brief Custom LCD Configuration File
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

#ifndef SL_MEMLCD_CUSTOM_CONFIG_H
#define SL_MEMLCD_CUSTOM_CONFIG_H

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

// <<< end of configuration section >>>

#endif
