/***************************************************************************//**
 * @file
 * @brief Custom LCD Configuration File
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
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
