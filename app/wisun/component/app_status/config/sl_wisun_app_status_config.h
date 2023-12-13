/***************************************************************************//**
 * @file
 * @brief Wi-SUN Application Status CoAP notfication configuration header.
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
#ifndef SL_WISUN_APP_STATUS_CONFIG_H
#define SL_WISUN_APP_STATUS_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// // <h> App status configuration

// <o SL_WISUN_APP_STATUS_DEFAULT_REMOTE_PORT> Default port of the remote host to send status report
// <i> Default: 5683
// <1-65536>
#define SL_WISUN_APP_STATUS_DEFAULT_REMOTE_PORT        5683U

// <s SL_WISUN_APP_STATUS_DEFAULT_REMOTE_ADDR> Default remote address to send status report
// <i> This address is used by default as notification target
#define SL_WISUN_APP_STATUS_DEFAULT_REMOTE_ADDR        "2001:db8::1"

// <s SL_WISUN_APP_STATUS_DEFAULT_URI_PATH> Default URI Path to use in status report packet
// <i> Default: app/status
#define SL_WISUN_APP_STATUS_DEFAULT_URI_PATH           "app/status"

// <s SL_WISUN_APP_STATUS_DEFAULT_NOTIFCATION_ID> Default notification ID string
// <i> Default: app-status
#define SL_WISUN_APP_STATUS_DEFAULT_NOTIFCATION_ID     "app-status"

// <o SL_WISUN_APP_STATUS_DEFAULT_SCHEDULE_TIME_MS> Default schedule time to send status report
// <i> Default: 10000
#define SL_WISUN_APP_STATUS_DEFAULT_SCHEDULE_TIME_MS   10000UL

// <q SL_WISUN_APP_STATUS_NEIGHBOR_INFO_ENABLE> Enable Neighbor info
// <i> Default: 1
#define SL_WISUN_APP_STATUS_NEIGHBOR_INFO_ENABLE       1U

// <q SL_WISUN_APP_STATUS_EXECUTION_TIME_ENABLE> Enable execution time
// <i> Default: 1
#define SL_WISUN_APP_STATUS_EXECUTION_TIME_ENABLE      1U

// <q SL_WISUN_APP_STATUS_DEVICE_INFO_ENABLE> Enable execution time
// <i> Default: 1
#define SL_WISUN_APP_STATUS_DEVICE_INFO_ENABLE         1U

// </h>

// <<< end of configuration section >>>

#endif
