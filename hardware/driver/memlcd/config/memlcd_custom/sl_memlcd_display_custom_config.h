/***************************************************************************//**
 * @file
 * @brief Custom LCD Using SPI Configuration File 
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
