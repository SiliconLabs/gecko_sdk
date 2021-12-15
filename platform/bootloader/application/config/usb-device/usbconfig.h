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

#ifndef __USBCONFIG_H
#define __USBCONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "application-configuration.h"

#define USB_DEVICE         // Compile stack for device mode.

#define USB_CLKSRC_USHFRCO // USHFRCO as USB clock source.

/****************************************************************************
**                                                                         **
** Specify number of endpoints used (in addition to EP0).                  **
**                                                                         **
*****************************************************************************/
#define NUM_EP_USED 2

/****************************************************************************
**                                                                         **
** USB Mass storage class device driver definitions.                       **
**                                                                         **
*****************************************************************************/
#define MSD_INTERFACE_NO  (0)
#define MSD_BULK_OUT      (0x01)   // Endpoint for MSD data reception.
#define MSD_BULK_IN       (0x81)   // Endpoint for MSD data transmission.

#ifdef __cplusplus
}
#endif

#endif // __USBCONFIG_H 
