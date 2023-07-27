/***************************************************************************//**
 * @file
 * @brief Wi-SUN OTA DFU configuration
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
#ifndef SL_WISUN_OTA_DFU_CONFIG_H
#define SL_WISUN_OTA_DFU_CONFIG_H

/**************************************************************************//**
 * @defgroup SL_WISUN_OTA_DFU_CONFIG Configuration
 * @ingroup SL_WISUN_OTA_DFU_API
 * @{
 *****************************************************************************/

// <<< Use Configuration Wizard in Context Menu >>>

// <h>Wi-SUN OTA DFU configuration

// <q SL_WISUN_OTA_DFU_VERBOSE_MODE_ENABLED> Enable verbose mode
// <i> Default value: 0
#define SL_WISUN_OTA_DFU_VERBOSE_MODE_ENABLED       0U

// <o SL_WISUN_OTA_DFU_STACK_SIZE_WORD> OTA DFU service stack size in CPU word
// <i> Default: 360
#define SL_WISUN_OTA_DFU_STACK_SIZE_WORD            360UL

// <o SL_WISUN_OTA_DFU_TFTP_PORT> TFTP service listener port
// <i> Default: 69
// <i> This is the port number where TFTP service is listening
// <1-65536>
#define SL_WISUN_OTA_DFU_TFTP_PORT                  69U

// <s SL_WISUN_OTA_DFU_HOST_ADDR> TFTP service listening address
#define SL_WISUN_OTA_DFU_HOST_ADDR                  "2001:db8::1"

// <s SL_WISUN_OTA_DFU_GBL_FILE> Firmware image (gbl) file name on TFTP server.
#define SL_WISUN_OTA_DFU_GBL_FILE                   "wisun_firmware.gbl"

// <s SL_WISUN_OTA_DFU_URI_PATH> OTA DFU resource URI path
#define SL_WISUN_OTA_DFU_URI_PATH                   "/ota/dfu"

// <q SL_WISUN_OTA_DFU_HOST_NOTIFY_ENABLED> Enable host notification
// <i> Default value: 1
#define SL_WISUN_OTA_DFU_HOST_NOTIFY_ENABLED        1U

#if SL_WISUN_OTA_DFU_HOST_NOTIFY_ENABLED
// <s SL_WISUN_OTA_DFU_NOTIFY_HOST_ADDR> OTA DFU notification server address
#define SL_WISUN_OTA_DFU_NOTIFY_HOST_ADDR           "2001:db8::1"

// <s SL_WISUN_OTA_DFU_NOTIFY_URI_PATH> OTA DFU notification resource URI path
#define SL_WISUN_OTA_DFU_NOTIFY_URI_PATH            "/ota/dfu_notify"

// <o SL_WISUN_OTA_DFU_NOTIFY_DOWNLOAD_CHUNK_CNT> Count of received chunk to notify in download task
// <i> Default value: 10
#define SL_WISUN_OTA_DFU_NOTIFY_DOWNLOAD_CHUNK_CNT  10U

// <o SL_WISUN_OTA_DFU_NOTIFY_PORT> OTA DFU Host notification listener port.
// <i> Default: 5685
#define SL_WISUN_OTA_DFU_NOTIFY_PORT                5685U
#endif

// </h>
// <<< end of configuration section >>>

/** @}*/

#endif
