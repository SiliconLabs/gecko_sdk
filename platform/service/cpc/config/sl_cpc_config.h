/***************************************************************************//**
 * @file
 * @brief CPC configuration file.
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

#ifndef SL_CPC_CONFIG_H
#define SL_CPC_CONFIG_H

// <h>CPC Configuration
// <o SL_CPC_TASK_PRIORITY> CPC task priority
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
// <i> Priority of the CPC task using the CMSIS order and using the enum name
// <i> This configuration is only used when the project contains an RTOS.
#define SL_CPC_TASK_PRIORITY      osPriorityAboveNormal3

// <o SL_CPC_TASK_STACK_SIZE> CPC task stack size
// <i> Default: 1024
// <i> Stack size for the CPC task in words.
// <i> This configuration is only used when the project contains an RTOS.
#define SL_CPC_TASK_STACK_SIZE            (1024)

// <o SL_CPC_RX_PAYLOAD_MAX_LENGTH><1-4087>
// <i> Default: 256
// <i> Maximum size of the payload in bytes of each RX buffer
#define SL_CPC_RX_PAYLOAD_MAX_LENGTH      (256)

// <o SL_CPC_TX_QUEUE_ITEM_MAX_COUNT>
// <i> Default 20
// <i> The maximum number of outgoing messages capable of being queued for transmission,
// <i> including outgoing messages on the TX side and ACKs or NACKs on the RX side.
#define SL_CPC_TX_QUEUE_ITEM_MAX_COUNT    (20)

// <o SL_CPC_RX_BUFFER_MAX_COUNT>
// <i> Default 20
// <i> Maximum count of CPC RX buffers assigned across all endpoints
// <i> Multiple RX buffers can be associated with a single endpoint
#define SL_CPC_RX_BUFFER_MAX_COUNT        (20)

// <o SL_CPC_USER_ENDPOINT_MAX_COUNT > <0-10>
// <i> Default 10
// <i> Maximum count of CPC user endpoints that can be opened at once.
#define SL_CPC_USER_ENDPOINT_MAX_COUNT    (10)

// <q SL_CPC_DEBUG_SYSTEM_VIEW_LOG_CORE_EVENT> Enable debug core tracing with system view
// <i> Default: 0
#define SL_CPC_DEBUG_SYSTEM_VIEW_LOG_CORE_EVENT       0

// <q SL_CPC_DEBUG_SYSTEM_VIEW_LOG_ENDPOINT_EVENT> Enable debug endpoint tracing with system view
// <i> Default: 0
#define SL_CPC_DEBUG_SYSTEM_VIEW_LOG_ENDPOINT_EVENT    0

// <q SL_CPC_DEBUG_CORE_EVENT_COUNTERS> Enable debug counters for event that happen at the core level
// <i> Default: 0
#define SL_CPC_DEBUG_CORE_EVENT_COUNTERS     0

// <q SL_CPC_DEBUG_ENDPOINT_EVENT_COUNTERS> Enable debug counters for event that happen on an endpoint
// <i> Default: 0
#define SL_CPC_DEBUG_ENDPOINT_EVENT_COUNTERS     0

// <q SL_CPC_DEBUG_MEMORY_ALLOCATOR_COUNTERS> Enable debug counters for memory allocation
// <i> Default: 0
#define SL_CPC_DEBUG_MEMORY_ALLOCATOR_COUNTERS     0

// </h>

// <<< end of configuration section >>>

#endif /* SL_CPC_CONFIG_H */
