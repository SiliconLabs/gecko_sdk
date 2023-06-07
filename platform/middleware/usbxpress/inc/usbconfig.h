/***************************************************************************//**
 * @file
 * @brief   USB protocol stack library, application supplied configuration
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SILICON_LABS_USBCONFIG_H
#define SILICON_LABS_USBCONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#define USB_DEVICE        // Compile stack for device mode.

#define USB_CORECLK_HFRCO // Use HFRCO as core clock, default is HFXO.

#define USB_PWRSAVE_MODE (USB_PWRSAVE_MODE_ONVBUSOFF   \
                          | USB_PWRSAVE_MODE_ONSUSPEND \
                          | USB_PWRSAVE_MODE_ENTEREM2)

/****************************************************************************
**                                                                         **
** Specify number of endpoints used (in addition to EP0).                  **
**                                                                         **
*****************************************************************************/
#define NUM_EP_USED 2

/****************************************************************************
**                                                                         **
** Specify number of application timers you need.                          **
**                                                                         **
*****************************************************************************/
#define NUM_APP_TIMERS 1

#ifdef __cplusplus
}
#endif

#endif // SILICON_LABS_USBCONFIG_H
