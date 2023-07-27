/***************************************************************************//**
 * @file
 * @brief ESL Tag Pervasive Display E-paper display driver config file.
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
#ifndef ESL_TAG_PD_EPD_DRIVER_CONFIG_H
#define ESL_TAG_PD_EPD_DRIVER_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>
// <h> E-paper display type selection

// <o PD_EPD_DISPLAY_COLOR_TYPE> Display color type
// <PD_EPD_MONO=> Monochrome
// <PD_EPD_SPECTRA=> Three color
// <i> Default: Three color
#define PD_EPD_DISPLAY_COLOR_TYPE                 PD_EPD_SPECTRA

// <o PD_EPD_DISPLAY_SIZE> Display size (inch)
//   <154=> 1.54 inch
//   <213=> 2.13 inch
//   <266=> 2.66 inch
//   <271=> 2.71 inch
//   <287=> 2.87 inch
//   <290=> 2.9 inch HR
//   <370=> 3.7 inch
//   <420=> 4.2 inch
//   <437=> 4.37 inch
// <i> Default: 370
#define PD_EPD_DISPLAY_SIZE                       370

// </h>
// <<< end of configuration section >>>

/* Port and pin definitions for the PD EPD signals */
// <<< sl:start pin_tool >>>
// Display DATA/COMMAND pin
// <gpio> PD_EPD_DRIVER_DATA_CONTROL
// $[GPIO_PD_EPD_DRIVER_DATA_CONTROL]
#define PD_EPD_DRIVER_DATA_CONTROL_PORT           gpioPortB
#define PD_EPD_DRIVER_DATA_CONTROL_PIN            0
// [GPIO_PD_EPD_DRIVER_DATA_CONTROL]$

// Display SYSTEM RESET pin
// <gpio> PD_EPD_DRIVER_SYSTEM_RESET
// $[GPIO_PD_EPD_DRIVER_SYSTEM_RESET]
#define PD_EPD_DRIVER_SYSTEM_RESET_PORT           gpioPortB
#define PD_EPD_DRIVER_SYSTEM_RESET_PIN            1
// [GPIO_PD_EPD_DRIVER_SYSTEM_RESET]$

// <<< sl:end pin_tool >>>

// Display DEVICE BUSY pin
#ifndef PD_EPD_DRIVER_DEVICE_BUSY_SIGNAL_PORT
#define PD_EPD_DRIVER_DEVICE_BUSY_SIGNAL_PORT     SL_SPIDRV_EXP_EPD_RX_PORT
#endif
#ifndef PD_EPD_DRIVER_DEVICE_BUSY_SIGNAL_PIN
#define PD_EPD_DRIVER_DEVICE_BUSY_SIGNAL_PIN      SL_SPIDRV_EXP_EPD_RX_PIN
#endif

// Display CHIP SELECT pin
#ifndef PD_EPD_DRIVER_CHIP_SELECT_PORT
#define PD_EPD_DRIVER_CHIP_SELECT_PORT            SL_SPIDRV_EXP_EPD_CS_PORT
#endif
#ifndef PD_EPD_DRIVER_CHIP_SELECT_PIN
#define PD_EPD_DRIVER_CHIP_SELECT_PIN             SL_SPIDRV_EXP_EPD_CS_PIN
#endif

#endif //ESL_TAG_PD_EPD_DRIVER_CONFIG_H
