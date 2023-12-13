/***************************************************************************//**
 * @file
 * @brief BT Mesh BLOB Transfer Client Configuration
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_BTMESH_BLOB_TRANSFER_CLIENT_CONFIG_H
#define SL_BTMESH_BLOB_TRANSFER_CLIENT_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> BT Mesh BLOB Transfer Client Configuration

// <e SL_BTMESH_BLOB_TRANSFER_CLIENT_LOGGING_CFG_VAL> Enable Logging
// <i> Default: 1
// <i> Enable / disable logging of BLOB Transfer Client model specific messages
#define SL_BTMESH_BLOB_TRANSFER_CLIENT_LOGGING_CFG_VAL   (1)

// <s SL_BTMESH_BLOB_TRANSFER_CLIENT_LOG_PREFIX_CFG_VAL> Text prepended to every log message
// <i> Default: "BLOB Transfer"
// <i> Every log message in the component is started with this text.
#define SL_BTMESH_BLOB_TRANSFER_CLIENT_LOG_PREFIX_CFG_VAL "BlobTfClient"

// <q SL_BTMESH_BLOB_TRANSFER_CLIENT_LOG_BLOB_STATUS_MSG_CFG_VAL> Log BLOB Status messages
// <i> Default: 1
// <i> Log the content of BT Mesh BLOB status messages.
#define SL_BTMESH_BLOB_TRANSFER_CLIENT_LOG_BLOB_STATUS_MSG_CFG_VAL 1

// </e>

// <h> BLOB Transfer Limits

// <o SL_BTMESH_BLOB_TRANSFER_CLIENT_MAX_SERVERS_CFG_VAL> Max number of servers
// <1-1008:1>
// <i> Default: 4
// <i> Maximum number of BLOB transfer servers which can be serviced in a transfer (affects BT Mesh stack memory usage)
#define SL_BTMESH_BLOB_TRANSFER_CLIENT_MAX_SERVERS_CFG_VAL                 4

// <o SL_BTMESH_BLOB_TRANSFER_CLIENT_MAX_BLOCKS_CFG_VAL> Max number of blocks
// <1-1888:1>
// <i> Default: 1024
// <i> Maximum number of blocks supported in a BLOB Transfer (affects BT Mesh stack memory usage)
#define SL_BTMESH_BLOB_TRANSFER_CLIENT_MAX_BLOCKS_CFG_VAL                  1024

// <o SL_BTMESH_BLOB_TRANSFER_CLIENT_MAX_CHUNKS_PER_BLOCK_CFG_VAL> Max number of chunks per block
// <1-2000:1>
// <i> Default: 40
// <i> Maximum number of chunks per block supported in a BLOB Transfer (affects BT Mesh stack memory usage).
// <i> WARNING! If the number of chunks per block exceeds 40 in case of Push BLOB Transfer Mode then high number of
// <i> BLOB Block Status messages become segmented which could make the BLOB Transfer slower and less robust.
// <i> Note: Format field of BLOB Block Status message affects the size of the message as well so the segmentation
// <i> occurs over 40 chunks per block when the format is Some Chunks Missing (0x2).
#define SL_BTMESH_BLOB_TRANSFER_CLIENT_MAX_CHUNKS_PER_BLOCK_CFG_VAL        40

// <o SL_BTMESH_BLOB_TRANSFER_CLIENT_MAX_CHUNK_SIZE_CFG_VAL> Max chunk size
// <1-241:1>
// <i> Default: 241
// <i> Maximum chunk size which can be selected during BLOB Transfer
#define SL_BTMESH_BLOB_TRANSFER_CLIENT_MAX_CHUNK_SIZE_CFG_VAL              241

// <o SL_BTMESH_BLOB_TRANSFER_CLIENT_PREF_CHUNK_SIZE_CFG_VAL> Preferred chunk size
// <1-241:1>
// <i> Default: 53
// <i> If the preferred chunk size is supported by all BLOB Transfer Servers then the default chunk size calculation
// <i> algorithm tries to select it as chunk size of the block otherwise the chunk size is set to the closest value
// <i> which fills all segments of the chunk. There is a tradeoff between small and large chunks.
// <i> The normal (non-AE) segmented chunks are able to transfer 12 bytes per advertisement minus the 1 byte
// <i> opcode and 2 byte chunk number and 4 bytes of MIC. This means N regular advertisements are able to
// <i> transfer 12 x N - 7 bytes of chunk data. If N is a big number then the payload per message converges
// <i> to 12 but if N is low then the fixed 7 byte protocol overhead penalty becomes significant.
// <i> If there is noise and at least one segment is lost then the whole chunk needs to be retransmitted.
// <i> Probability of transfer failure is higher for long segmented chunks and it takes more time to retransmit
// <i> a long chunk. The chunk size can't be arbitrarily low because the max number of chunks per block multiplied
// <i> by the chunk size shall be greater than or equal to block size. A low chunk size leads to more chunks per
// <i> block which has negative effects when the number of chunks per block exceeds 40, because the BLOB Block Status
// <i> message becomes segmented, which means all servers starts to respond with segmented messages. This might have
// <i> significant impact on the transfer speed.
// <i> Chunk size with 5 full segments is used as default preferred chunk size because in this case the
// <i> (12 x N - 7) / (12 x N) = 88% of the ideal (non-noisy) transfer speed is preserved and
// <i> 40 x (12 x N - 7) = 2120 -> 2048 (2^N) byte blocks can be used without BLOB Block Status
// <i> message segmentation.
// <i> If BT Mesh over Advertisement Extension Silabs proprietary feature is turned on then the default chunk
// <i> calculation algorithm selects the chunk size to fill the AE packet completely with chunk data based on
// <i> the network PDU size if the chunk size is supported by the BLOB Transfer Servers, otherwise it falls back
// <i> to the preferred chunk size calculation. (see Advertisement Extension Server component for details)
#define SL_BTMESH_BLOB_TRANSFER_CLIENT_PREF_CHUNK_SIZE_CFG_VAL                53

// </h>

// <h> Retry and Separation parameters

// <o SL_BTMESH_BLOB_TRANSFER_CLIENT_SEPARATION_TIME_MS_DEFAULT_CFG_VAL> Default separation time between chunks
// <0-65535:1>
// <i> Default: 0
// <i> Default minimum separation time between two chunks in the same block
#define SL_BTMESH_BLOB_TRANSFER_CLIENT_SEPARATION_TIME_MS_DEFAULT_CFG_VAL     0

// <o SL_BTMESH_BLOB_TRANSFER_CLIENT_LOCAL_RETRY_MAX_DEFAULT_CFG_VAL> Default max local retry of message transmission requests
// <0-1000:1>
// <i> Default: 1000
// <i> Default local max retries of message transmission requests during query info, transfer start, block start, block query
// <i> chunk transfer and transfer cancel procedures.
// <i> Default max local retry is used when the BT Mesh stack rejects sending BLOB Transfer messages due to a recoverable error,
// <i> so BT Mesh stack API returns with recoverable error code, for example due to lack of memory.
#define SL_BTMESH_BLOB_TRANSFER_CLIENT_LOCAL_RETRY_MAX_DEFAULT_CFG_VAL        1000

// <o SL_BTMESH_BLOB_TRANSFER_CLIENT_REMOTE_RETRY_THRESHOLD_DEFAULT_CFG_VAL> Default retry threshold of frequent message transmissions
// <0-1000:1>
// <i> Default: 200
// <i> Default retry threshold of frequent message transmissions during query info, transfer start, block start, block query and
// <i> transfer cancel procedures before infrequent message transmission is activated with doubled retry time.
#define SL_BTMESH_BLOB_TRANSFER_CLIENT_REMOTE_RETRY_THRESHOLD_DEFAULT_CFG_VAL 200

// <o SL_BTMESH_BLOB_TRANSFER_CLIENT_LOCAL_RETRY_TIME_MS_DEFAULT_CFG_VAL> Default local retry time [ms]
// <1-65535:1>
// <i> Default: 500
// <i> Default local retry time of message transmission requests during query info, transfer start, block start, block query,
// <i> chunk transfer and transfer cancel procedures.
// <i> Default local retry time is used when the BT Mesh stack rejects sending BLOB Transfer messages due to a recoverable error,
// <i> so BT Mesh stack API returns with recoverable error code, for example due to lack of memory.
#define SL_BTMESH_BLOB_TRANSFER_CLIENT_LOCAL_RETRY_TIME_MS_DEFAULT_CFG_VAL    500

// <o SL_BTMESH_BLOB_TRANSFER_CLIENT_PUSH_RETRY_TIME_MS_DEFAULT_CFG_VAL> Default retry time for push transfer [ms]
// <0-65535:1>
// <i> Default: 2000
// <i> Default retry time of message transmissions during push transfer.
// <i> The transfer start, block start, block query and transfer cancel procedures use this retry time during push transfer
// <i> to send the proper procedure specific message again if at least one receiver haven't responded when retry timeout
// <i> is reached.
// <i> The query info procedure use this retry time value when the push transfer mode is selected explicitly by upper
// <i> layer or both transfer modes (push & pull) are allowed by the upper layer.
// <i> Rationale: transfer mode is chosen after query info procedure in this case.
// <i> Note: if the expected procedure specific status message is received from a receiver then the retry time measurement
// <i> is started again to avoid too early message retransmission while the receivers are still responding otherwise
// <i> the interference between receiver nodes would be even higher.
#define SL_BTMESH_BLOB_TRANSFER_CLIENT_PUSH_RETRY_TIME_MS_DEFAULT_CFG_VAL     2000

// <o SL_BTMESH_BLOB_TRANSFER_CLIENT_PULL_RETRY_TIME_MS_DEFAULT_CFG_VAL> Default retry time for pull transfer [ms]
// <0-65535:1>
// <i> Default: 4000
// <i> Default retry time of message transmissions during pull transfer.
// <i> The transfer start, block start, block query and transfer cancel procedures use this retry time during pull transfer
// <i> to send the proper procedure specific message again if at least one receiver haven't responded when retry timeout
// <i> is reached.
// <i> The query info procedure use this retry time when the pull transfer mode is selected explicitly by upper layer.
// <i> Note: if the expected procedure specific status message is received from a receiver then the retry time measurement
// <i> is started again to avoid too early message retransmission while the receivers are still responding otherwise
// <i> the interference between receiver nodes would be even higher.
#define SL_BTMESH_BLOB_TRANSFER_CLIENT_PULL_RETRY_TIME_MS_DEFAULT_CFG_VAL     4000

// </h>

// </h>

// <<< end of configuration section >>>

#if SL_BTMESH_BLOB_TRANSFER_CLIENT_LOCAL_RETRY_TIME_MS_DEFAULT_CFG_VAL == 0
#error "BT Mesh BLOB Transfer Client Local Retry Time [ms] configuration shall not be zero."
#endif

 #endif // SL_BTMESH_BLOB_TRANSFER_CLIENT_CONFIG_H
