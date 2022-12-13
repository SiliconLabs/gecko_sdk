/***************************************************************************//**
 * @file
 * @brief System View UART recorder configuration file.
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

// <<< Use Configuration Wizard in Context Menu >>>

#ifndef SL_UART_RECORDER_CONFIG_H
#define SL_UART_RECORDER_CONFIG_H

// <s SL_SYSTEMVIEW_UART_RECORDER_IOSTREAM_INSTANCE_NAME> Name of the iostream instance to use
// <i> Default: vcom
// <i> This configuration is only used when the project contains the initializer helper AND auto-generated iostream instances
#define SL_SYSTEMVIEW_UART_RECORDER_IOSTREAM_INSTANCE_NAME         vcom

// <o SL_SYSTEMVIEW_UART_RECORDER_TASK_PRIORITY> UART recorder task priority
// <osPriorityLow=> low
// <osPriorityLow1=> low + 1
// <osPriorityLow2=> low + 2
// <osPriorityLow3=> low + 3
// <osPriorityLow4=> low + 4
// <osPriorityLow5=> low + 5
// <osPriorityLow6=> low + 6
// <osPriorityLow7=> low + 7
// <osPriorityBelowNormal=> below normal
// <osPriorityBelowNormal1=> below normal + 1
// <osPriorityBelowNormal2=> below normal + 2
// <osPriorityBelowNormal3=> below normal + 3
// <osPriorityBelowNormal4=> below normal + 4
// <osPriorityBelowNormal5=> below normal + 5
// <osPriorityBelowNormal6=> below normal + 6
// <osPriorityBelowNormal7=> below normal + 7
// <osPriorityNormal=> normal
// <osPriorityNormal1=> normal + 1
// <osPriorityNormal2=> normal + 2
// <osPriorityNormal3=> normal + 3
// <osPriorityNormal4=> normal + 4
// <osPriorityNormal5=> normal + 5
// <osPriorityNormal6=> normal + 6
// <osPriorityNormal7=> normal + 7
// <osPriorityAboveNormal => above normal
// <osPriorityAboveNormal1=> above normal + 1
// <osPriorityAboveNormal2=> above normal + 2
// <osPriorityAboveNormal3=> above normal + 3
// <osPriorityAboveNormal4=> above normal + 4
// <osPriorityAboveNormal5=> above normal + 5
// <osPriorityAboveNormal6=> above normal + 6
// <osPriorityAboveNormal7=> above normal + 7
// <osPriorityHigh=> high
// <osPriorityHigh1=> high + 1
// <osPriorityHigh2=> high + 2
// <osPriorityHigh3=> high + 3
// <osPriorityHigh4=> high + 4
// <osPriorityHigh5=> high + 5
// <osPriorityHigh6=> high + 6
// <osPriorityHigh7=> high + 7
// <osPriorityRealtime=> realtime
// <osPriorityRealtime1=> realtime + 1
// <osPriorityRealtime2=> realtime + 2
// <osPriorityRealtime3=> realtime + 3
// <osPriorityRealtime4=> realtime + 4
// <osPriorityRealtime5=> realtime + 5
// <osPriorityRealtime6=> realtime + 6
// <osPriorityRealtime7=> realtime + 7
// <i> Default: osPriorityAboveNormal3
// <i> Priority of the UART recorder task. Generally, this task should be of a low priority.
// <i> This configuration is only used when the project contains an RTOS.
#define SL_SYSTEMVIEW_UART_RECORDER_TASK_PRIORITY        osPriorityLow

// <o SL_SYSTEMVIEW_UART_RECORDER_TASK_STACK_SIZE> UART recorder task stack size
// <i> Default: 512
// <i> Stack size for the UART recorder task in words.
// <i> This configuration is only used when the project contains an RTOS.
#define SL_SYSTEMVIEW_UART_RECORDER_TASK_STACK_SIZE         512

// <q SL_SYSTEMVIEW_UART_RECORDER_PREVENT_SLEEP_BEFORE_CONNECTION> Prevent sleep before SystemView connection
// <i> Prevents the system from entering deep sleep mode (EM2-EM3) before a connection to SystemView is established.
// <i> Default: 1
#define SL_SYSTEMVIEW_UART_RECORDER_PREVENT_SLEEP_BEFORE_CONNECTION         1

// <o SL_SYSTEMVIEW_UART_RECORDER_TASK_RX_PERIOD> Period, in OS ticks, at which the task will read inputs from SystemView
// <i> Default: 100
// <i> This configuration is only used when the project contains an RTOS.
#define SL_SYSTEMVIEW_UART_RECORDER_TASK_RX_PERIOD         100

// <o SL_SYSTEMVIEW_UART_RECORDER_RX_ENABLED_DURATION> Delay, in milliseconds, before allowing sleep after connection with SystemView is established
// <i> Default: 500
// <i> Once the connection with SystemView is established, SystemView will request some information from the device.
// <i> It is not possible to enter EM2/EM3 until then otherwise it is impossible to receive the requests.
// <i> There is no easy way to configure this. If the data displayed by SystemView seems incomplete, try increasing this value.
// <i> This configuration is only used when SL_SYSTEMVIEW_UART_RECORDER_PREVENT_SLEEP_BEFORE_CONNECTION is enabled or if a kernel is used.
#define SL_SYSTEMVIEW_UART_RECORDER_RX_ENABLED_DURATION    1500

#endif  // SL_UART_RECORDER_CONFIG_H

// <<< end of configuration section >>>
