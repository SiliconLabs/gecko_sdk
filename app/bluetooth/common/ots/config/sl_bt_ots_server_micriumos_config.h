/***************************************************************************//**
 * @file
 * @brief OTS Server Micrium OS adaptation configuration file
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

// <o SL_BT_OTS_SERVER_TASK_PRIO> OTS Server task priority
// <i> Default: 5
// <i> Define the priority of the OTS Server task.
#define SL_BT_OTS_SERVER_TASK_PRIO         5

// <o SL_BT_OTS_SERVER_TASK_STACK> OTS Server task stack size in bytes
// <i> Default: 2048
// <i> Define the stack size of the OTS Server task in bytes.
#define SL_BT_OTS_SERVER_TASK_STACK        2048

// <o SL_BT_OTS_SERVER_MUTEX_WAIT> Mutex Timeout for OTS Server task (OS ticks)
// <i> Default: 100
#define SL_BT_OTS_SERVER_MUTEX_WAIT        100
