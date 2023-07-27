/***************************************************************************//**
 * @file
 * @brief ESL Tag custom driver interface for Pervasive Displays EPD driver.
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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
#ifndef ESL_TAG_PD_EPD_INTERFACE_H
#define ESL_TAG_PD_EPD_INTERFACE_H

#include "sl_status.h"

/**************************************************************************//**
 * PD EPD display power save function
 *****************************************************************************/
void esl_pd_epd_display_power_save(void);

/**************************************************************************//**
 * PD EPD display write function
 *
 * @param[in] param_count The number of parameters.
 * @return sl_status_t
 *****************************************************************************/
sl_status_t esl_pd_epd_display_write(int param_count, ...);

/**************************************************************************//**
 * PD EPD display init function
 *
 * @param[in] param_count The number of parameters.
 * @return sl_status_t
 *****************************************************************************/
sl_status_t esl_pd_epd_display_init(int param_count, ...);

#endif // ESL_TAG_PD_EPD_INTERFACE_H
