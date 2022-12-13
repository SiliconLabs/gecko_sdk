/***************************************************************************//**
 * @file
 * @brief Application OS statistic configuration header.
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
#ifndef APP_OS_STAT_CONFIG_H
#define APP_OS_STAT_CONFIG_H

#include "cmsis_os2.h"

// <<< Use Configuration Wizard in Context Menu >>>

// // <h> App OS Statistic configuration

// <o APP_OS_STAT_THREAD_PRIO> App OS statistic thread priority
// <i> Default: osPriorityLow3
#define APP_OS_STAT_THREAD_PRIO                  osPriorityLow3

// <o APP_OS_STAT_STACK_SIZE_WORD> App OS statistic thread stack size in word
// <i> Default: 256
#define APP_OS_STAT_STACK_SIZE_WORD              256U

// <o APP_OS_STAT_UPDATE_PERIODE_TIME_MS> App OS statistic update periode time
// <i> Default: 1000
#define APP_OS_STAT_UPDATE_PERIODE_TIME_MS       1000U

// <o APP_OS_STAT_MAX_THREAD_CNT> Maximum registerable thread count
// <i> Default: 10
#define APP_OS_STAT_MAX_THREAD_CNT               10U

// <o APP_OS_STAT_RTT_LOG_CHANNEL> RTT Log channel for app os statistics
// <i> Default: 0
#define APP_OS_STAT_RTT_LOG_CHANNEL              0U

// <q APP_OS_STAT_THREAD_STACK_ENABLED> Enable thread stack usage statistic
// <i> default 1
#define APP_OS_STAT_THREAD_STACK_ENABLED         1U

// <q APP_OS_STAT_HEAP_ENABLED> Enable heap usage statistic
// <i> default 1
#define APP_OS_STAT_HEAP_ENABLED                 1U

// <q APP_OS_STAT_MANUAL_REGISTER_THREADS> Enable manual thread registering
// <i> default 0
#define APP_OS_STAT_MANUAL_REGISTER_THREADS      0U

// </h>

// <<< end of configuration section >>>

#endif
