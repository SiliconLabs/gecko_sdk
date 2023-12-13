/***************************************************************************//**
 * @file
 * @brief BT Mesh BLOB Transfer Client
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
#ifndef SL_BTMESH_BLOB_TRANSFER_CLIENT_H
#define SL_BTMESH_BLOB_TRANSFER_CLIENT_H

#include "sl_enum.h"
#include "sl_status.h"
#include "em_common.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/***************************************************************************//**
 * @addtogroup blob_transfer_client BT Mesh BLOB Transfer Client
 * @{
 ******************************************************************************/

/// Invalid value for the binary logarithm of the block size
#define SL_BTMESH_BLOB_TRANSFER_CLIENT_INVALID_BLOCK_SIZE_LOG   0xFF

/// BLOB Transfer Client Kind
SL_ENUM(sl_btmesh_blob_transfer_client_notification_kind_t) {
  /// BLOB Transfer Result Notification
  ///
  /// This notification is triggered at the end of BLOB Transfer
  SL_BTMESH_BLOB_TRANSFER_CLIENT_KIND_TRANSFER_RESULT,

  /// BLOB Transfer Progress Notification
  ///
  /// The progress is reported at the end of each block because at the end of
  /// the block it is sure that all active BLOB Transfer Servers have received
  /// the whole block (every chunk).
  ///
  /// @note If some BLOB Transfer Servers didn't receive certain chunks then
  /// those chunk would be retransmitted in case of Push and Pull transfers
  /// as well, therefore the transmitted chunks are not a good indicator of
  /// the overall transfer progress.
  SL_BTMESH_BLOB_TRANSFER_CLIENT_KIND_PROGRESS,

  /// BLOB Transfer Server Failed Notification
  ///
  /// @note If one BLOB Transfer Server fails but at least one other BLOB
  /// Transfer Server remains active then the BLOB Transfer is continued
  SL_BTMESH_BLOB_TRANSFER_CLIENT_KIND_SERVER_FAILED
};

/// BLOB Transfer Client Result
SL_ENUM(sl_btmesh_blob_transfer_client_result_t) {
  /// At least one BLOB Transfer Server received the BLOB successfully.
  /// The other servers might have failed due to error or timeout.
  SL_BTMESH_BLOB_TRANSFER_CLIENT_RESULT_COMPLETED,
  /// All BLOB Transfer Servers have failed due to timeout or various kinds of
  /// errors (e.g. internal error, out of resources see Mesh Model specification
  /// 1.1)
  SL_BTMESH_BLOB_TRANSFER_CLIENT_RESULT_FAILED,
  /// Last BLOB transfer was canceled by upper layer
  SL_BTMESH_BLOB_TRANSFER_CLIENT_RESULT_CANCELED
};

/// BLOB Transfer progress
///
/// This structure represent the progress of the active BLOB Transfer Servers
///
/// @note Some servers could fail with error or timeout, but if there is at least
/// one active BLOB Transfer Server then the transfer continues
typedef struct {
  /// Number of BLOB bytes which have been received by every active BLOB Transfer
  /// Server
  ///
  /// @note The progress is calculated at the end of the blocks because in the
  /// block, chunks could be retransmitted multiple times
  uint32_t  confirmed_tx_bytes;
  /// BLOB size in bytes
  uint32_t blob_size;
} sl_btmesh_blob_transfer_client_progress_t;

/// BLOB Transfer Server Failed Notification
typedef struct {
  /// Address of the BLOB Transfer Server
  uint16_t server_address;
  /// If a BLOB Transfer Server doesn't respond until a specified time then
  /// the timeout is set to 1
  uint8_t  timeout;
  /// The error is set only if the timeout is zero and a BLOB Transfer Server has
  /// responded with non-zero status code (error) in BLOB Transfer Status or BLOB
  /// Block Status message
  uint8_t  error;
} sl_btmesh_blob_transfer_client_server_failed_t;

/// Notification data for upper layers
typedef struct {
  /// Identifies the notification type
  sl_btmesh_blob_transfer_client_notification_kind_t kind;
  /// Index of the element which triggered the notification
  uint16_t elem_index;
  /// Notification specific parameters
  union {
    /// Status of the active BLOB transfer on the element
    sl_btmesh_blob_transfer_client_result_t transfer_result;
    /// Progress of the active BLOB Transfer on the element
    sl_btmesh_blob_transfer_client_progress_t progress;
    /// Reason of BLOB Transfer Server failure during the active BLOB Transfer
    sl_btmesh_blob_transfer_client_server_failed_t server_failed;
  } params;
} sl_btmesh_blob_transfer_client_notification_t;

typedef void (*sl_btmesh_blob_transfer_client_notify_cb_t)(
  const sl_btmesh_blob_transfer_client_notification_t *const notification);

/***************************************************************************//**
 *
 * Set up a new BLOB transfer.
 *
 * @note This shall not be called when the Distribution Server initiates the
 * BLOB transfer because BT Mesh stack sets up the BLOB transfer inside the BT
 * Mesh stack automatically.
 *
 * @param[in] elem_index The client model element index.
 * @param[in] blob_id The ID of the BLOB.
 * @param[in] blob_size The size of the BLOB.
 * @param[in] appkey_index Index of the application key to be used for
 *   communicating with the servers
 * @param[in] ttl The TTL to use when communicating with the servers.
 * @param[in] timeout_base If a Server does not respond within this time frame,
 *   it will be marked as inactive.
 * @param[in] group_address The group address to used if the
 *   @ref sl_btmesh_blob_transfer_client_setup::multicast_threshold is exceeded.
 *   Zero to only use unicast.
 * @param[in] virtual_address Virtual address in case virtual addresses are used
 * @param[in] multicast_threshold If the number of servers for any step exceeds
 *   this number, the group address will be used. Otherwise, servers will be
 *   looped through one by one.
 * @param[in] servers_len Length of data in servers
 * @param[in] servers List of MBT server addresses, represented as little endian
 *   two byte sequences.
 *
 * @return Result of the BLOB Transfer setup
 * @retval SL_STATUS_OK if successful. Error code otherwise.
 * @retval SL_STATUS_INVALID_STATE if not Idle
 *
 ******************************************************************************/
sl_status_t sl_btmesh_blob_transfer_client_setup(uint16_t elem_index,
                                                 sl_bt_uuid_64_t blob_id,
                                                 uint32_t blob_size,
                                                 uint16_t appkey_index,
                                                 uint8_t ttl,
                                                 uint32_t timeout_base,
                                                 uint16_t group_address,
                                                 uuid_128 virtual_address,
                                                 uint16_t multicast_threshold,
                                                 size_t servers_len,
                                                 const uint8_t* servers);

/***************************************************************************//**
 *
 * Set up an array data provider for a new BLOB transfer.
 *
 * The BLOB transfer client reads the BLOB data from this array during chunk
 * transfer.
 *
 * @param[in] elem_index Client model element index
 * @param[in] array Pointer to an array which stores the BLOB data
 * @param[in] length Length of the array
 *
 * @return Result of the Data Provider setup
 * @retval SL_STATUS_OK if successful
 * @retval SL_STATUS_INVALID_STATE Data Provider setup called in non-idle state
 * @retval SL_STATUS_INVALID_PARAMETER BLOB size inconsistency between the
 *   @ref sl_btmesh_blob_transfer_client_setup and this Data Provider setup call
 *
 ******************************************************************************/
sl_status_t
sl_btmesh_blob_transfer_client_setup_data_provider_array(uint16_t elem_index,
                                                         const uint8_t *array,
                                                         uint32_t length);

/***************************************************************************//**
 *
 * Set up a BLOB storage data provider for a new BLOB transfer.
 *
 * The BLOB Transfer Client reads the BLOB data from the BLOB storage based on
 * the passed BLOB id.
 *
 * @note The BLOB id used to identify the BLOB data in the BLOB storage (on the
 *   client side) is likely not the same as the BLOB id used during the BLOB
 *   transfer to the servers.
 *
 * @param[in] elem_index Client model element index
 * @param[in] blob_id Pointer to the BLOB id
 *
 * @return Result of the Data Provider setup
 * @retval SL_STATUS_OK if successful
 * @retval SL_STATUS_INVALID_STATE Data Provider setup called in non-idle state
 * @retval SL_STATUS_NOT_FOUND BLOB is not found in the BLOB storage
 * @retval SL_STATUS_INVALID_PARAMETER BLOB size inconsistency between the
 *   @ref sl_btmesh_blob_transfer_client_setup and this Data Provider setup call
 *
 ******************************************************************************/
sl_status_t
sl_btmesh_blob_transfer_client_setup_data_provider_blob_storage(uint16_t elem_index,
                                                                const sl_bt_uuid_64_t *blob_id);

/***************************************************************************//**
 *
 * Set up additional parameters for new BLOB transfers
 *
 * The separation and retry parameters are set for all future BLOB Transfers
 * until the next reset (stored in RAM).
 * On reset, the respective default separation and retry parameters are set
 * based on the component configuration at component initialization time.
 *
 * @note This function is separated from @ref sl_btmesh_blob_transfer_client_setup
 *   because the @ref sl_btmesh_blob_transfer_client_setup shall not be called
 *   when @ref sl_btmesh_fw_distribution_server initiates the BLOB transfer
 *   because BT Mesh stack sets up the BLOB transfer inside the BT Mesh stack
 *   automatically.
 *
 * @param[in] elem_index Client model element index
 * @param[in] separation_time_ms Minimum separation time between two chunks
 *    in the same block, in milliseconds
 * @param[in] retry_time_local_ms Local retry time of message transmission
 *    requests during query info, transfer start, block start, block query,
 *    chunk transfer and transfer cancel procedures. Local retry time is used
 *    when the BT Mesh stack rejects sending BLOB Transfer messages due to a
 *    recoverable error, so BT Mesh stack API returns with recoverable error code,
 *    for example due to lack of memory.
 *    Local retry time shall be greater than zero.
 * @param[in] retry_time_push_ms Retry time of message transmissions during push
 *    transfer. The transfer start, block start, block query and transfer cancel
 *    procedures use this retry time during push transfer to send the procedure
 *    specific message again if at least one receiver haven't responded when retry
 *    timeout is reached. The query info procedure use this retry time value when
 *    the push transfer mode is selected explicitly by upper layer or both transfer
 *    modes (push & pull) are allowed by the upper layer.
 * @param[in] retry_time_pull_ms Retry time of message transmissions during pull
 *    transfer. The transfer start, block start, block query and transfer cancel
 *    procedures use this retry time during pull transfer to send the procedure
 *    specific message again if at least one receiver haven't responded when this
 *    retry timeout is reached.The query info procedure use this retry time when
 *    the pull transfer mode is selected explicitly by upper layer.
 * @param[in] retry_max_local Local max retries of message transmission
 *    requests during query info, transfer start, block start, block query
 *    chunk transfer and transfer cancel procedures. Max local retry is used when
 *    the BT Mesh stack rejects sending BLOB Transfer messages due to a recoverable
 *    error, so BT Mesh stack API returns with recoverable error code, for example
 *    due to lack of memory
 * @param[in] retry_threshold_remote Retry threshold of frequent message
 *    transmissions during query info, transfer start, block start, block query
 *    and transfer cancel procedures before infrequent message transmission is
 *    activated with doubled retry time.
 *
 * @return Result of the parameter setup
 * @retval SL_STATUS_OK if successful
 * @retval SL_STATUS_INVALID_STATE Parameter setup called in non-idle state
 * @retval SL_STATUS_INVALID_PARAMETER One or more parameters are invalid
 *
 ******************************************************************************/
sl_status_t sl_btmesh_blob_transfer_client_set_params(uint16_t elem_index,
                                                      uint16_t separation_time_ms,
                                                      uint16_t retry_time_local_ms,
                                                      uint16_t retry_time_push_ms,
                                                      uint16_t retry_time_pull_ms,
                                                      uint16_t retry_max_local,
                                                      uint16_t retry_threshold_remote);

/***************************************************************************//**
 *
 * Starts a previously set up BLOB Transfer.
 *
 * @param[in] elem_index Client model element index
 * @param[in] transfer_mode Allowed transfer mode
 * @param[in] notify Function pointer to a notification callback function which
 *   is called in the following cases:
 *     \li BLOB Transfer completed
 *     \li BLOB Transfer failed
 *     \li BLOB Transfer canceled
 *     \li BLOB Transfer progress changes
 *     \li BLOB Transfer Server failed
 *
 * It is valid to pass NULL as notify parameter. If the callback function is
 * null then no notification is initiated.
 * If @p transfer_mode is set to @p sl_btmesh_mbt_client_mbt_transfer_mode_both
 * then the BLOB transfer client selects the transfer mode based on the result
 * of query information. If one transfer mode is supported by all receiving nodes
 * only then that transfer mode is selected otherwise push mode is selected.
 * If @p transfer_mode is set to @p sl_btmesh_mbt_client_mbt_transfer_mode_push
 * or @p sl_btmesh_mbt_client_mbt_transfer_mode_pull then that is used as
 * transfer mode.
 *
 * @return SL_STATUS_OK if successful. Error code otherwise
 * @retval SL_STATUS_INVALID_PARAMETER Invalid transfer mode
 * @retval SL_STATUS_INVALID_STATE BLOB Transfer Client busy with another transfer
 * @retval SL_STATUS_INVALID_CONFIGURATION No data provider was specified
 *
 ******************************************************************************/
sl_status_t
sl_btmesh_blob_transfer_client_start(uint16_t elem_index,
                                     sl_btmesh_mbt_client_transfer_mode_t transfer_mode,
                                     sl_btmesh_blob_transfer_client_notify_cb_t notify);

/***************************************************************************//**
 *
 * Cancels an ongoing BLOB Transfer.
 *
 * @param[in] elem_index Client model element index
 *
 ******************************************************************************/
void sl_btmesh_blob_transfer_client_cancel(uint16_t elem_index);

/***************************************************************************//**
 *
 * Aborts an ongoing BLOB Transfer.
 *
 * @param[in] elem_index Client model element index
 *
 * @note This function is not to be used when the MBT client is interfaced
 *       by a higher layer component (e.g. distribution server).
 *
 * @return SL_STATUS_OK if successful. Error code otherwise.
 *
 ******************************************************************************/
sl_status_t sl_btmesh_blob_transfer_client_abort(uint16_t elem_index);

/***************************************************************************//**
 *
 * Informs BLOB Transfer Client SDK component that the transfer in MBT Client
 * model of BT Mesh stack was aborted.
 *
 * @param[in] elem_index Client model element index
 *
 * @note This function shall be used only when the MBT client is interfaced
 *       by a higher layer component (e.g. distribution server).
 *       The MBT Client model can be aborted by higher layer models in the BT
 *       Mesh stack which is not reported in MBT Client model events so it shall
 *       be reported by calling this API.
 *
 * @return SL_STATUS_OK if successful. Error code otherwise.
 *
 ******************************************************************************/
sl_status_t sl_btmesh_blob_transfer_client_on_aborted(uint16_t elem_index);

/***************************************************************************//**
 *
 * Informs BLOB Transfer Client SDK component that the transfer in MBT Client
 * model of BT Mesh stack was suspended.
 *
 * @param[in] elem_index Client model element index
 *
 * @note This function shall be used only when the MBT client is interfaced
 *       by a higher layer component (e.g. distribution server).
 *       The MBT Client model can be suspended by higher layer models in the BT
 *       Mesh stack which is not reported in MBT Client model events so it shall
 *       be reported by calling this API.
 *
 * @return SL_STATUS_OK if successful. Error code otherwise.
 *
 ******************************************************************************/
sl_status_t sl_btmesh_blob_transfer_client_on_suspended(uint16_t elem_index);

/***************************************************************************//**
 *
 * Informs BLOB Transfer Client SDK component that the transfer in MBT Client
 * model of BT Mesh stack was resumed.
 *
 * @param[in] elem_index Client model element index
 *
 * @note This function shall be used only when the MBT client is interfaced
 *       by a higher layer component (e.g. distribution server).
 *       The MBT Client model can be resumed by higher layer models in the BT
 *       Mesh stack which is not reported in MBT Client model events so it shall
 *       be reported by calling this API.
 *
 * @return SL_STATUS_OK if successful. Error code otherwise.
 *
 ******************************************************************************/
sl_status_t sl_btmesh_blob_transfer_client_on_resumed(uint16_t elem_index);

/***************************************************************************//**
 * Handle BLOB Transfer Client events.
 *
 * This function is called automatically after enabling the component.
 *
 * @param[in] evt  Pointer to incoming event.
 *
 ******************************************************************************/
void sl_btmesh_blob_transfer_client_on_event(const sl_btmesh_msg_t * const evt);

// -----------------------------------------------------------------------------
//                        Overridable Callback Functions
// -----------------------------------------------------------------------------
/***************************************************************************//**
 * Calculates the binary logarithm of the block size for the current BLOB
 * transfer from the provided parameters which are the result of the Retrieve
 * Capabilities procedure of the BLOB Transfer.
 *
 * The parameters passed represent the aggregated capabilities of the BLOB
 * transfer client and every BLOB transfer server which participates in the
 * current transfer.
 *
 * The default implementation calculates the greatest possible block size from
 * the parameters. If another implementation is required then the strong symbol
 * definition shall be provided for this function with the implementation in the
 * application code.
 *
 * @param[in] blob_size           Size of the BLOB
 * @param[in] block_size_log_min  Min allowed binary logarithm of the block size
 * @param[in] block_size_log_max  Max allowed binary logarithm of the block size
 * @param[in] block_count_max     Max allowed number of blocks
 * @param[in] max_chunk_size_min  Max allowed chunk size in the current transfer
 * @param[in] max_chunks_min      Max allowed number of chunks per block in the
 *                                current transfer
 *
 * @return Binary logarithm of the selected block size for the current transfer
 * @retval SL_BTMESH_BLOB_TRANSFER_CLIENT_INVALID_BLOCK_SIZE_LOG Invalid parameters
 *
 ******************************************************************************/
uint8_t
sl_btmesh_blob_transfer_client_calculate_block_size_log(uint32_t blob_size,
                                                        uint8_t  block_size_log_min,
                                                        uint8_t  block_size_log_max,
                                                        uint16_t block_count_max,
                                                        uint16_t max_chunk_size_min,
                                                        uint16_t max_chunks_min);

/***************************************************************************//**
 * Calculates the chunk size for the next block in the current BLOB transfer
 * from the previously selected binary logarithm of the block size and from
 * the result of the Retrieve Capabilities procedure of the BLOB Transfer.
 *
 * If the configurable preferred chunk size is supported by all BLOB Transfer
 * Servers then the default chunk size calculation algorithm selects it as chunk
 * size of the block otherwise the chunk size is set to the closest value which
 * fills all segments of the chunk.
 * If another implementation is required then the strong symbol definition shall
 * be provided for this function with the implementation in the application code.
 *
 * @param[in] block_size_log      The selected binary logarithm of the block size
 *                                during previous phase of the BLOB transfer
 * @param[in] max_chunk_size_min  Max allowed chunk size in the current transfer
 * @param[in] max_chunks_min      Max allowed number of chunks per block in the
 *                                current transfer
 * @param[in] nw_pdu_size         Size of Network PDU. If the Silicon Labs BT Mesh
 *                                over advertisement extension proprietary feature
 *                                is turned on then it can be greater than 29 bytes.
 *
 * @return Chunk size for next block in the current BLOB transfer
 *
 ******************************************************************************/
uint16_t
sl_btmesh_blob_transfer_client_calculate_chunk_size(uint8_t block_size_log,
                                                    uint16_t max_chunk_size_min,
                                                    uint16_t max_chunks_min,
                                                    uint16_t nw_pdu_size);

/***************************************************************************//**
 * Provides string representation of transfer mode
 *
 * It is guaranteed that this function returns a valid string even in case of
 * invalid transfer mode.
 *
 * @param[in] transfer_mode transfer mode
 *
 * @note The to_string functions are used for log calls only in this component.
 *   If the logging is disabled then the linker can eliminate these functions.
 *
 * @return String representation of transfer mode
 * @retval "INVALID" if the transfer mode is invalid
 ******************************************************************************/
const char *sl_btmesh_blob_transfer_client_transfer_mode_to_string(sl_btmesh_mbt_client_transfer_mode_t transfer_mode);

/***************************************************************************//**
 * Provides string representation of MBT phase
 *
 * It is guaranteed that this function returns a valid string even in case of
 * invalid MBT phase.
 *
 * @param[in] mbt_phase MBT phase
 *
 * @note The to_string functions are used for log calls only in this component.
 *   If the logging is disabled then the linker can eliminate these functions.
 *
 * @return String representation of MBT phase
 * @retval "INVALID" if the MBT phase is invalid
 ******************************************************************************/
const char *sl_btmesh_blob_transfer_client_mbt_phase_to_string(sl_btmesh_mbt_server_phase_t mbt_phase);

/***************************************************************************//**
 * Provides string representation of MBT status
 *
 * It is guaranteed that this function returns a valid string even in case of
 * invalid MBT status.
 *
 * @param[in] mbt_status MBT status
 *
 * @note The to_string functions are used for log calls only in this component.
 *   If the logging is disabled then the linker can eliminate these functions.
 *
 * @return String representation of MBT status
 * @retval "INVALID" if the MBT status is invalid
 ******************************************************************************/
const char *sl_btmesh_blob_transfer_client_mbt_status_to_string(sl_btmesh_mbt_server_status_t mbt_status);

/** @} end blob_transfer_client */

#ifdef __cplusplus
}
#endif // __cplusplus

 #endif // SL_BTMESH_BLOB_TRANSFER_CLIENT_H
