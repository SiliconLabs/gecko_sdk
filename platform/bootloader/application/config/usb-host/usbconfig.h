/***************************************************************************//**
 * @file
 * @brief USB protocol stack library, application supplied configuration options.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef USBCONFIG_H
#define USBCONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#define USB_HOST                // Compile stack for host mode.

#define USB_CLKSRC_HFRCODPLL    // Use HFRCO and DPLL as USB clock

// Use DPLL with 50 MHz HFXO as reference clock:
#define USB_DPLL_FREQUENCY      48000000UL
#define USB_DPLL_M              349U
#define USB_DPLL_N              335U
#define USB_DPLL_SRC            USB_DPLL_SRC_HFXO

/****************************************************************************
**                                                                         **
** Specify number of host channels used (in addition to EP0).              **
**                                                                         **
*****************************************************************************/
#define NUM_HC_USED 2       // Not counting default control ep which
//                             is assigned to host channels 0 and 1

//
// Some utility functions in the API needs printf. These
// functions have "print" in their name. This macro enables
// these functions.
//
#define USB_USE_PRINTF

#ifdef __cplusplus
}
#endif

#endif // USBCONFIG_H
