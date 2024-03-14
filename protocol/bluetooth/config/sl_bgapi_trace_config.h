/***************************************************************************//**
 * @file
 * @brief BGAPI trace utility configuration
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the
 * use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software in a
 *    product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#ifndef SL_BGAPI_TRACE_CONFIG_H
#define SL_BGAPI_TRACE_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> BGAPI Trace Utility Configuration

// <o SL_BGAPI_TRACE_RTT_BUFFER_INDEX> RTT buffer index for BGAPI message output <1-255>
// <i> Default: 2
// <i> This configuration specifies the RTT buffer index to use for outputting the BGAPI messages. If other components use RTT buffers, configure each component to use a unique buffer index.
#ifndef SL_BGAPI_TRACE_RTT_BUFFER_INDEX
  #define SL_BGAPI_TRACE_RTT_BUFFER_INDEX  2
#endif

// <o SL_BGAPI_TRACE_RTT_BUFFER_SIZE> RTT buffer size for BGAPI message output <256-65536>
// <i> Default: 256
// <i> This configuration specifies the size of the RTT buffer to use for outputting the BGAPI messages.
#ifndef SL_BGAPI_TRACE_RTT_BUFFER_SIZE
  #define SL_BGAPI_TRACE_RTT_BUFFER_SIZE  256
#endif

// <o SL_BGAPI_TRACE_MESSAGE_METADATA_ENABLE> Enable (1) or disable outputting message metadata <0-1>
// <i> Default: 1
// <i> This configuration enables (1) or disables (0) the output of BGAPI message metadata. The metadata includes the timestamp and the precise message type for more accurate analysis in the BGAPI trace tool.
#ifndef SL_BGAPI_TRACE_MESSAGE_METADATA_ENABLE
  #define SL_BGAPI_TRACE_MESSAGE_METADATA_ENABLE  1
#endif

// </h> End BGAPI Trace Utility Configuration

// <<< end of configuration section >>>

#endif // SL_BGAPI_TRACE_CONFIG_H
