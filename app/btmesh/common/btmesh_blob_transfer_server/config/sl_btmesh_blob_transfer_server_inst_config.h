/***************************************************************************//**
 * @file
 * @brief BLOB Transfer Server Instance Configuration Header
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_CONFIG_H
#define SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_CONFIG_H

#include "sl_btmesh_dcd.h"

// <<< Use Configuration Wizard in Context Menu >>>

// <e SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_ELEM_INDEX_OVERRIDE_CFG_VAL> Override Element Index
// <i> Default element index is provided by project or components.
// <i> If the default element index is not sufficient then it can be overridden by activating this option.
#define SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_ELEM_INDEX_OVERRIDE_CFG_VAL  0

// <o SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_ELEM_INDEX_CFG_VAL> Element Index
// <i> Element index of BLOB Transfer Server model instance.
// <i> It has an effect only when "Override Element Index" configuration option is activated.
// <i> Range: 0-255, Default: 0
// <0..255:1>
// <d> 0
#define SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_ELEM_INDEX_CFG_VAL  0

// </e>

// <o SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_MIN_BLOCK_SIZE_LOG_CFG_VAL> Min Block Size Log <0x6-0x20> <f.h>
// <i> Please note, that decreasing the minimum block size will result in increased heap usage.
// <i> Block states need to be monitored. The smaller the blocks, the bigger the state storage.
// <i> Change this value with care.
// <d> 0x9
#define SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_MIN_BLOCK_SIZE_LOG_CFG_VAL   0x9

// <o SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_MAX_BLOCK_SIZE_LOG_CFG_VAL> Max Block Size Log <0x6-0x20> <f.h>
// <i> Please note, that increasing the maximum block size will result in increased heap usage.
// <i> Blocks are cached on heap before being written into NVM.
// <i> Change this value with care.
// <i> The maximum block size shall be less than or equal to the product of max chunks per block and chunk size.
// <d> 0x9
#define SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_MAX_BLOCK_SIZE_LOG_CFG_VAL   0x9

// <o SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_MAX_CHUNKS_PER_BLOCK_CFG_VAL> Maximum of number of chunks per block <8-64:8>
// <d> 40
#define SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_MAX_CHUNKS_PER_BLOCK_CFG_VAL  40

// <o SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_MAX_CHUNK_SIZE_CFG_VAL> Maximum chunk size <8-241:1>
// <i> If the max chunk size is 8 then the chunk data fits into a single BT Mesh advertisement message.
// <i> If the chunk data is segmented then N segments is able to transfer (N*12)-7 byte data.
// <i> The advantage of higher chunk size is the higher throughput in low noise environment.
// <i> The advantage of lower chunk size is that fewer messages are retransmitted in high noise environment due to lost chunk messages.
// <i> LPN only: the number of chunk messages (segments) multiplied by requested chunk count in partial block report shall fit into the friend queue.
// <d> 241
#define SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_MAX_CHUNK_SIZE_CFG_VAL 241

// <h> Supported Transfer Modes

// <e SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_PUSH_MODE_CFG_VAL> Push Mode
// <d> 1
#define SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_PUSH_MODE_CFG_VAL 1

// </e>

// <e SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_PULL_MODE_CFG_VAL> Pull Mode
// <d> 1
#define SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_PULL_MODE_CFG_VAL 1

// <o SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_PULL_CHUNK_REQUEST_CNT_CFG_VAL> Number of chunks requested in Block Status or Partial Block Report <1-32>
// <d> 4
#define SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_PULL_CHUNK_REQUEST_CNT_CFG_VAL 4

// <o SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_PULL_RETRY_INTERVAL_MS_CFG_VAL> Interval, in milliseconds, between Partial Block Reports, if nothing is received <1000-30000:100>
// <d> 1000
#define SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_PULL_RETRY_INTERVAL_MS_CFG_VAL 1000

// <o SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_PULL_RETRY_CNT_CFG_VAL> Number of retries sending the same Partial Block Report, before giving up <1-10>
// <d> 8
#define SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_PULL_RETRY_CNT_CFG_VAL 8

// <e SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_LPN_MODE_CFG_VAL> LPN Mode
// <i> Only pull transfer mode can be used on LPN nodes.
// <d> 0
#define SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_LPN_MODE_CFG_VAL 0

// <e SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_LPN_HIGH_THROUGHPUT_MODE_CFG_VAL> LPN high throughput mode
// <i> In high throughput mode the LPN node polls the friend node more frequently to increase the throughput at the expense of power consumption.
// <d> 1
#define SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_LPN_HIGH_THROUGHPUT_MODE_CFG_VAL 1

// <o SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_LPN_POLL_DELAY_MS_CFG_VAL> LPN poll delay in milliseconds <100-30000:100>
// <i> The delay of first LPN poll when the BLOB Transfer Server expects messages from the client after an event.
// <i> The major part of BLOB transfer to LPN is the waiting for the poll timeout to elapse in order to poll the friend node for BLOB Transfer messages.
// <i> The maximum number of messages can be transferred per polling equals to friend queue size during BLOB transfer to LPN.
// <i> This poll delay configuration parameter value makes the polling more frequent when BLOB Transfer messages are expected to increase the throughput.
// <i> The LPN poll delay shall be less than SL_BTMESH_LPN_POLL_TIMEOUT_CFG_VAL in sl_btmesh_lpn_config.h file.
// <d> 500
#define SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_LPN_POLL_DELAY_MS_CFG_VAL 500

// </e>
// </e>
// </e>

// </h>

// <<< end of configuration section >>>

#if SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_MIN_BLOCK_SIZE_LOG_CFG_VAL > SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_MAX_BLOCK_SIZE_LOG_CFG_VAL
#error The Max Block Size Log value shall be equal to or greater than the Min Block Size Log value.
#endif

#endif // SL_BTMESH_BLOB_TRANSFER_SERVER_INSTANCE_CONFIG_H
