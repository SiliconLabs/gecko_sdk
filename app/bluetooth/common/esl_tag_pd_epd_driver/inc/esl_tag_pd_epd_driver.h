/***************************************************************************//**
 * @file
 * @brief E-paper display low level driver API for Pervasive Displays products.
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
#ifndef ESL_TAG_PD_EPD_DRIVER_H
#define ESL_TAG_PD_EPD_DRIVER_H

#include "sl_status.h"
#include "em_gpio.h"
#include "esl_tag_display.h"
#include "esl_tag_pd_epd_driver_config.h"

// Display pixel size definitions
#if (PD_EPD_DISPLAY_SIZE == 154)
#define PD_EPD_DISPLAY_WIDTH                      152
#define PD_EPD_DISPLAY_HEIGHT                     152
#elif (PD_EPD_DISPLAY_SIZE == 213)
#define PD_EPD_DISPLAY_WIDTH                      104
#define PD_EPD_DISPLAY_HEIGHT                     212
#elif (PD_EPD_DISPLAY_SIZE == 266)
#define PD_EPD_DISPLAY_WIDTH                      152
#define PD_EPD_DISPLAY_HEIGHT                     296
#elif (PD_EPD_DISPLAY_SIZE == 271)
#define PD_EPD_DISPLAY_WIDTH                      176
#define PD_EPD_DISPLAY_HEIGHT                     264
#elif (PD_EPD_DISPLAY_SIZE == 287)
#define PD_EPD_DISPLAY_WIDTH                      128
#define PD_EPD_DISPLAY_HEIGHT                     296
#elif (PD_EPD_DISPLAY_SIZE == 290)
#define PD_EPD_DISPLAY_WIDTH                      168
#define PD_EPD_DISPLAY_HEIGHT                     384
#elif (PD_EPD_DISPLAY_SIZE == 370)
#define PD_EPD_DISPLAY_WIDTH                      240
#define PD_EPD_DISPLAY_HEIGHT                     416
#elif (PD_EPD_DISPLAY_SIZE == 420)
#define PD_EPD_DISPLAY_WIDTH                      400
#define PD_EPD_DISPLAY_HEIGHT                     300
#elif (PD_EPD_DISPLAY_SIZE == 437)
#define PD_EPD_DISPLAY_WIDTH                      176
#define PD_EPD_DISPLAY_HEIGHT                     480
#endif

#define PD_EPD_MONO                               0
#define PD_EPD_SPECTRA                            1

/* Pin mode and initial state definitions for the EPD signals */
#define PD_EPD_GPIO_LEVEL_LOW                   0
#define PD_EPD_GPIO_LEVEL_HIGH                  1

/// BUSY pin
#define PD_EPD_DRIVER_DEVICE_BUSY_SIGNAL_MODE   gpioModeInputPull
#define PD_EPD_DRIVER_DEVICE_BUSY_SIGNAL_INIT   PD_EPD_GPIO_LEVEL_HIGH

/// DATA/COMMAND pin
#define PD_EPD_DRIVER_DATA_CONTROL_MODE         gpioModePushPull
#define PD_EPD_DRIVER_DATA_CONTROL_INIT         PD_EPD_GPIO_LEVEL_LOW

/// EPD Chip Select pin
#define PD_EPD_DRIVER_CHIP_SELECT_MODE          gpioModePushPull
#define PD_EPD_DRIVER_CHIP_SELECT_INIT          PD_EPD_GPIO_LEVEL_HIGH

/// RESET pin
#define PD_EPD_DRIVER_SYSTEM_RESET_MODE         gpioModePushPull
#define PD_EPD_DRIVER_SYSTEM_RESET_INIT         PD_EPD_GPIO_LEVEL_LOW

/// Pervasive Display registers
#define PD_REG_BLACK_BUFFER             0x10
#define PD_REG_RED_BUFFER               0x13
#define PD_REG_DISPLAY_REFRESH          0x12
#define PD_REG_DCDC                     0x02
#define PD_REG_POWER_ON                 0x04
#define PD_REG_INPUT_TEMPERATURE        0xE5
#define PD_REG_ACTIVE_TEMPERATURE       0xE0
#define PD_REG_PSR                      0x00
#define PD_REG_SOFT_RESET               0x00
#define PD_REG_NOP                      0xFF

/// Temperature and PSR constants, PD EPD 3.7"
#define PD_ACTIVE_TEMPERATURE_DATA      0x02
#define PD_PSR_BYTE_0                   0xCF
#define PD_PSR_BYTE_1                   0x89

/// Soft reset data
#define PD_SOFT_RESET                   0x0E

/// Pervasive Display Bits per Pixel value for 3 color EPD
#define PD_EPD_THREE_COLOR_BPP          2
#define PD_EPD_MONOCHROME_BPP           1

/**************************************************************************//**
 * PD EPD init function
 * This one runs by the user implementation (usually in app.c) in parallel.
 *****************************************************************************/
sl_status_t pd_epd_init(void);

/**************************************************************************//**
 * PD EPD init GPIO function
 *****************************************************************************/
sl_status_t pd_epd_init_GPIOs(void);

/**************************************************************************//**
 * PD EPD deinit GPIO function
 *****************************************************************************/
sl_status_t pd_epd_deinit_GPIOs(void);

/**************************************************************************//**
 * PD EPD low level write function
 *
 * @param[in] reg The register to write.
 * @param[in] data Data to write.
 * @param[in] len Data lenght.
 *****************************************************************************/
sl_status_t pd_epd_write_data(const uint8_t *reg, const uint8_t *data, uint32_t len);

/**************************************************************************//**
 * PD EPD set temperature and PSR
 *
 * @param[in] temperature The temperature to set.
 *****************************************************************************/
sl_status_t pd_epd_set_temperature_and_PSR(int8_t temperature);

/**************************************************************************//**
 * PD EPD soft reset function
 *****************************************************************************/
sl_status_t pd_epd_soft_reset(void);

/**************************************************************************//**
 * PD EPD update image function
 *
 * @param[in] display_index The display index of the EPD.
 * @param[in] image_index The image index of the ESL.
 *****************************************************************************/
sl_status_t pd_epd_update_image(uint8_t display_index, uint8_t image_index);

/**************************************************************************//**
 * ESL EPD bluetooth stack event handler.
 * This one runs by the user implementation (usually in app.c) in parallel.
 *
 * @param[in] evt Event coming from the Bluetooth stack.
 *****************************************************************************/
void esl_pd_epd_bt_on_event(sl_bt_msg_t *evt);

#endif /* ESL_TAG_EPD_DRIVER_H */
