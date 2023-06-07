/***************************************************************************//**
 * @file
 * @brief Sharp Memory LCD LS013B7DH03 driver
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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
#ifndef SL_MEMLCD_DISPLAY_H
#define SL_MEMLCD_DISPLAY_H

#include "sl_status.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SL_MEMLCD_LS013B7DH03             1

#define SL_MEMLCD_DISPLAY_WIDTH           128
#define SL_MEMLCD_DISPLAY_HEIGHT          128
#define SL_MEMLCD_DISPLAY_BPP             1
#define SL_MEMLCD_DISPLAY_RGB_3BIT        0

/* Max supported frequency is 1.1 MHz */
#define SL_MEMLCD_SCLK_FREQ               1100000

/* EXTCOMIN pin signal must have a frequency in the range of 54-65 Hz */
#define SL_MEMLCD_EXTCOMIN_FREQUENCY      60

#define SL_MEMLCD_SCS_SETUP_US            6
#define SL_MEMLCD_SCS_HOLD_US             2

/**************************************************************************//**
 * @brief
 *   Initialization function for the LS013B7DH03 device driver.
 *
 * @return
 *   If all operations completed sucessfully SL_STATUS_OK is returned. On
 *   failure a different status code is returned specifying the error.
 *****************************************************************************/
sl_status_t sl_memlcd_init(void);

#ifdef __cplusplus
}
#endif

#endif
