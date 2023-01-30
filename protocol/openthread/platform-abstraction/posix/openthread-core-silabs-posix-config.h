/*
 *  Copyright (c) 2017, The OpenThread Authors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 *   This file includes all compile-time configuration constants used by SiLabs POSIX builds.
 *
 *   To use this configuration in your POSIX builds, copy this file into the following folder:
 *   <openthread_location>/src/posix/platform/
 */

#ifndef OPENTHREAD_CORE_SILABS_POSIX_CONFIG_H_
#define OPENTHREAD_CORE_SILABS_POSIX_CONFIG_H_

/******************************************************************************
 * RCP BUS defaults
 *****************************************************************************/

/**
 * This setting configures what type of RCP bus to use (default UART)
 *
 * UART: OT_POSIX_RCP_BUS_UART
 * SPI: OT_POSIX_RCP_BUS_SPI
 * CPC: OT_POSIX_RCP_BUS_CPC
 *
 */
#ifndef OPENTHREAD_POSIX_CONFIG_RCP_BUS
#define OPENTHREAD_POSIX_CONFIG_RCP_BUS OT_POSIX_RCP_BUS_UART
#endif

/******************************************************************************
 * Co-processor RPC defaults
 *****************************************************************************/

/**
 * Default to 1 to enable Host->Co-processor remote procedure call support.
 */
#ifndef OPENTHREAD_CONFIG_COPROCESSOR_RPC_ENABLE
#define OPENTHREAD_CONFIG_COPROCESSOR_RPC_ENABLE 1
#endif

#if OPENTHREAD_CONFIG_COPROCESSOR_RPC_ENABLE

// NOTE: The following must be true otherwise prints on the POSIX Host will be truncated.
// OPENTHREAD_CONFIG_CLI_MAX_LINE_LENGTH >= OPENTHREAD_CONFIG_COPROCESSOR_RPC_OUTPUT_BUFFER_SIZE

/**
 * Force maximum size of the CLI line in bytes including the null terminator.
 *
 */
#undef OPENTHREAD_CONFIG_CLI_MAX_LINE_LENGTH
#define OPENTHREAD_CONFIG_CLI_MAX_LINE_LENGTH 1200

// 
/**
 * Force OpenThread Co-processor Remote Procedure Call output buffer size in bytes
 *
 */
#undef OPENTHREAD_CONFIG_COPROCESSOR_RPC_OUTPUT_BUFFER_SIZE
#define OPENTHREAD_CONFIG_COPROCESSOR_RPC_OUTPUT_BUFFER_SIZE 1200

#endif // OPENTHREAD_CONFIG_COPROCESSOR_RPC_ENABLE

/******************************************************************************
 * MultiPan RCP (CPC) defaults
 *****************************************************************************/

/**
 * Define to 1 to enable multipan RCP support.
 */
#ifndef OPENTHREAD_CONFIG_MULTIPAN_RCP_ENABLE
#define OPENTHREAD_CONFIG_MULTIPAN_RCP_ENABLE 0
#endif

#if OPENTHREAD_CONFIG_MULTIPAN_RCP_ENABLE

/**
 * Force disable max power table support.
 *
 */
#undef OPENTHREAD_POSIX_CONFIG_MAX_POWER_TABLE_ENABLE
#define OPENTHREAD_POSIX_CONFIG_MAX_POWER_TABLE_ENABLE 0

/**
 * Force disable Channel Manager support.
 *
 */
#undef OPENTHREAD_CONFIG_CHANNEL_MANAGER_ENABLE
#define OPENTHREAD_CONFIG_CHANNEL_MANAGER_ENABLE 0

/**
 * Force diable Channel Monitor support.
 *
 */
#undef OPENTHREAD_CONFIG_CHANNEL_MONITOR_ENABLE
#define OPENTHREAD_CONFIG_CHANNEL_MONITOR_ENABLE 0

#endif // OPENTHREAD_CONFIG_MULTIPAN_RCP_ENABLE

/******************************************************************************
 * Proprietary SubGhz defaults
 *****************************************************************************/

/**
 * Define to 1 if you want to enable proprietary radio support as defined by platform.
 *
 * @note If this setting is set to 1, the channel range is defined by the platform. Choosing this option requires
 * the following configuration options to be defined by Platform:
 * OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_PAGE,
 * OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MIN,
 * OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MAX and,
 * OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MASK.
 *
 */
#ifndef OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_SUPPORT
#ifndef OPENTHREAD_CONFIG_RADIO_915MHZ_OQPSK_SUPPORT
#ifndef OPENTHREAD_CONFIG_RADIO_2P4GHZ_OQPSK_SUPPORT
#define OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_SUPPORT 0
#define OPENTHREAD_CONFIG_RADIO_915MHZ_OQPSK_SUPPORT         0
#define OPENTHREAD_CONFIG_RADIO_2P4GHZ_OQPSK_SUPPORT         1
#endif
#endif
#endif

#if OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_SUPPORT

#undef OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_PAGE
#define OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_PAGE 23

#undef OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MIN
#define OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MIN 0

#undef OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MAX
#define OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MAX 24

#undef OPENTHREAD_CONFIG_DEFAULT_CHANNEL
#define OPENTHREAD_CONFIG_DEFAULT_CHANNEL OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MIN

#undef OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MASK
#define OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MASK 0x1ffffff

/**
 * Force disable OQPSK modulation in 915MHz frequency band. The physical layer parameters are defined in
 * section 6 of IEEE802.15.4-2006.
 *
 */
#undef OPENTHREAD_CONFIG_RADIO_915MHZ_OQPSK_SUPPORT
#define OPENTHREAD_CONFIG_RADIO_915MHZ_OQPSK_SUPPORT 0

/**
 * Force disable OQPSK modulation in 2.4GHz frequency band. The physical layer parameters are defined in
 * section 6 of IEEE802.15.4-2006.
 *
 */
#undef OPENTHREAD_CONFIG_RADIO_2P4GHZ_OQPSK_SUPPORT
#define OPENTHREAD_CONFIG_RADIO_2P4GHZ_OQPSK_SUPPORT 0

/**
 * Define to enable platform logging and `otLog{Level}Plat()` OT functions.
 *
 */
#undef OPENTHREAD_CONFIG_LOG_PLATFORM
#define OPENTHREAD_CONFIG_LOG_PLATFORM 1

#endif // OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_SUPPORT

/******************************************************************************
 * Project defaults
 *
 * See also ot-br-posix/third_party/openthread/CMakeLists.txt for other defaults
 *****************************************************************************/

/**
 * Define to 1 to enable Factory Diagnostics support.
 *
 */
#undef OPENTHREAD_CONFIG_DIAG_ENABLE
#define OPENTHREAD_CONFIG_DIAG_ENABLE 1

/**
 * The log level (used at compile time). If `OPENTHREAD_CONFIG_LOG_LEVEL_DYNAMIC_ENABLE` is set, this defines the most
 * verbose log level possible. See `OPENTHREAD_CONFIG_LOG_LEVEL_INIT` to set the initial log level.
 *
 */
#undef OPENTHREAD_CONFIG_LOG_LEVEL
#define OPENTHREAD_CONFIG_LOG_LEVEL OT_LOG_LEVEL_DEBG

/**
 * Define to prepend the log level to all log messages.
 *
 */
#undef OPENTHREAD_CONFIG_LOG_PREPEND_LEVEL
#define OPENTHREAD_CONFIG_LOG_PREPEND_LEVEL 1

/**
 * Defines the max count of RCP failures allowed to be recovered.
 * 0 means to disable RCP failure recovering.
 *
 */
#undef OPENTHREAD_SPINEL_CONFIG_RCP_RESTORATION_MAX_COUNT
#define OPENTHREAD_SPINEL_CONFIG_RCP_RESTORATION_MAX_COUNT 100

/**
 * Define to enable CLI logging and `otLogCli()` OT function.
 *
 */
#undef OPENTHREAD_CONFIG_LOG_CLI
#define OPENTHREAD_CONFIG_LOG_CLI 0

/******************************************************************************
 * Include OpenThread project's POSIX defaults
 *****************************************************************************/
#include "openthread-core-posix-config.h"

#endif // OPENTHREAD_CORE_SILABS_POSIX_CONFIG_H_
