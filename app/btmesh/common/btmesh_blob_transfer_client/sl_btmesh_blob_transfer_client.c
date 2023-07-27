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

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include <stdbool.h>
#include "sl_status.h"
#include "em_device.h"

#include "sl_bt_api.h"
#include "sl_btmesh_api.h"
#include "sl_btmesh_dcd.h"
#include "sl_btmesh_model_specification_v1_1_defs.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT

#ifdef SL_CATALOG_APP_LOG_PRESENT
#include "app_log.h"
#endif // SL_CATALOG_APP_LOG_PRESENT

#include "app_assert.h"
#include "app_timer.h"
#include "sl_btmesh_blob_storage.h"

#include "sl_btmesh_blob_transfer_client.h"
#include "sl_btmesh_blob_transfer_client_config.h"

// Warning! The app_btmesh_util shall be included after the component configuration
// header file in order to provide the component specific logging macro.
#include "app_btmesh_util.h"

// -----------------------------------------------------------------------------
//                                    Macros
// -----------------------------------------------------------------------------

// Shortcut to add log prefix to log messages
#define LOG_PREFIX SL_BTMESH_BLOB_TRANSFER_CLIENT_LOG_PREFIX_CFG_VAL " "

// Shortcut for Invalid Block Size Log constant
#define INVALID_BLOCK_SIZE_LOG SL_BTMESH_BLOB_TRANSFER_CLIENT_INVALID_BLOCK_SIZE_LOG

// Logs non-temporary procedure errors
#define log_procedure_status_error(sc, procedure, elem_index)               \
  do {                                                                      \
    if ((SL_STATUS_BUSY != (sc)) && (SL_STATUS_NO_MORE_RESOURCE != (sc))) { \
      log_status_error_f(sc,                                                \
                         LOG_PREFIX procedure " failed (elem=%d)" NL,       \
                         elem_index);                                       \
    }                                                                       \
  } while (0)

// Suppress compiler warning of unused static function
#define SL_UNUSED  __attribute__((unused))

// Returns the string representation of BLOB ID in a compound literal.
// WARNING! This macro shall be used as a parameter of log calls only due to the
// lifetime of underlying compound literal in APP_BTMESH_UUID_64_TO_STRING.
#define BLOB_ID_TO_STRING(blob_id) APP_BTMESH_UUID_64_TO_STRING(blob_id, ' ', true)

// Vendor ID of Bluetooth SIG model
#define SIG_VENDOR_ID    0xFFFF

// The BT Mesh standard network PDU size belonging to non-connectable
// non-scannable advertisements
#define STANDARD_NETWORK_PDU_SIZE   29

// Provides string representation of MBT phase
#define mbt_phase_to_string(mbt_phase) \
  sl_btmesh_blob_transfer_client_mbt_phase_to_string((sl_btmesh_mbt_server_phase_t) mbt_phase)

// Provides string representation of MBT status
#define mbt_status_to_string(mbt_status) \
  sl_btmesh_blob_transfer_client_mbt_status_to_string((sl_btmesh_mbt_server_status_t) mbt_status)

/***************************************************************************//**
 * @addtogroup blob_transfer_client BT Mesh BLOB Transfer Client
 * @{
 ******************************************************************************/

// -----------------------------------------------------------------------------
//                               Type definitions
// -----------------------------------------------------------------------------

/// BLOB Transfer Client state constants
typedef enum {
  /// Uninitialized state
  STATE_UNINIT,
  /// Inactive state
  STATE_INACTIVE,
  /// All BLOB transfer failed (error or timeout on every server)
  STATE_TRANSFER_FAILED,
  /// At least one BLOB Transfer Server received the BLOB successfully
  STATE_TRANSFER_COMPLETED,
  /// Last BLOB transfer was canceled by upper layer
  STATE_TRANSFER_CANCELED,
  /// Send BLOB information get message to servers until they respond or timeout
  STATE_SEND_QUERY_INFO,
  /// Send BLOB transfer start message to servers until they respond or timeout
  STATE_SEND_TRANSFER_START,
  /// Send BLOB block start message to servers until they respond or timeout
  STATE_SEND_BLOCK_START,
  /// Send BLOB chunk transfer messages to servers
  STATE_SEND_CHUNKS,
  /// Send BLOB block query message to servers until they respond or timeout
  STATE_SEND_BLOCK_QUERY,
  /// Send cancel message to servers until they respond or timeout
  STATE_CANCELING,
  /// Current BLOB transfer is suspended
  STATE_SUSPENDED,
  /// Total number of BLOB Transfer Client states
  STATE_COUNT
} blob_transfer_client_state_t;

/// BLOB Data Provider type determines how the data is provided for the chunk
/// transfer. Based on this information the BLOB Transfer Client is able to
/// provide the data for the chunk transfers automatically.
typedef enum {
  /// No BLOB data provider is configured
  BLOB_DATA_PROVIDER_NONE,
  /// The BLOB data is provided in a continuous memory location (array)
  BLOB_DATA_PROVIDER_ARRAY,
  /// The BLOB data is provided in the BLOB storage component
  BLOB_DATA_PROVIDER_BLOB_STORAGE
} blob_data_provider_type_t;

/// Each @ref blob_transfer_client_state_t has its own state flags which
/// makes it possible to categorize certain states from different aspects
typedef struct {
  /// If idle state flag is set, then no BLOB Transfer is active and the BLOB
  /// Transfer Client is able to start a new transfer
  uint8_t idle : 1;
  /// If retry state flag is set, then it means the current state supports
  /// retry.
  ///
  /// In retry states the BLOB Transfer Client sends messages to the BLOB
  /// Transfer Servers and waits for their responses. It might happen that
  /// the request or the response message is lost which means it could be
  /// necessary to sends these messages multiple times until every active
  /// BLOB Transfer Server responds or times out.
  ///
  /// The @ref blob_transfer_client_t::retry_time_ms is measured from the
  /// reception of the BT Mesh stack event
  /// @ref sl_btmesh_evt_mbt_client_tx_complete_id. If the retry timer elapses
  /// and maximum number of retries (@ref blob_transfer_client_t::retry_max) is
  /// not yet reached, then the current state is entered again
  /// (self-transition), which executes the proper state entry and exit actions.
  ///
  /// The Mesh Model 1.1 Specification refers to these retries as:
  /// "The number of request repetitions is implementation specific"
  uint8_t retry : 1;
  /// Separation flag is set for chunk transfer and it keeps
  /// @ref blob_transfer_client_t::separation_time_ms between two chunks to
  /// spare the bandwidth in the Mesh network.
  ///
  /// By default 0ms is the separation time to achieve the highest possible
  /// throughput.
  uint8_t separation : 1;
} blob_transfer_client_state_flags_t;

typedef struct {
  /// BLOB Data Provider type determines how data is provided for chunk transfer
  blob_data_provider_type_t type;
  /// Union of Data Provider descriptors
  union {
    struct {
      sl_bt_uuid_64_t blob_id;
    } blob_storage;
    struct {
      const uint8_t *data;
      uint32_t length;
    } array;
  } descriptor;
} blob_data_provider_t;

typedef struct {
  struct app_timer retry_timer;
  struct app_timer separation_timer;
  sl_btmesh_blob_transfer_client_notify_cb_t notify;
  blob_data_provider_t data_provider;
  uint32_t blob_size;
  uint32_t current_chunk_offset;
  uint16_t current_chunk_length;
  uint16_t current_block_chunk_size;
  uint16_t current_block_number;
  uint16_t elem_index;
  uint16_t separation_time_ms;
  uint16_t retry_time_ms;
  uint16_t retry_max;
  uint16_t retry_counter;
  uint16_t max_chunk_size_min;
  uint16_t max_chunks_min;
  uint8_t  block_size_log;
  blob_transfer_client_state_t state;
  sl_btmesh_mbt_client_transfer_mode_t transfer_mode;
  bool retry_time_elapsed : 1;
  bool separation_time_elapsed : 1;
  bool chunk_requested : 1;
  uint8_t chunk_data[SL_BTMESH_BLOB_TRANSFER_CLIENT_MAX_CHUNK_SIZE_CFG_VAL];
  const uint8_t *chunk_data_ptr;
} blob_transfer_client_t;

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

/***************************************************************************//**
 * Translates BLOB Transfer Client result and notifies the user
 *
 * @param self BLOB Transfer Client descriptor structure
 * @param result BLOB Transfer Client result parameter
 ******************************************************************************/
static void notify_transfer_result(blob_transfer_client_t *const self,
                                   sl_btmesh_blob_transfer_client_result_t result);

/***************************************************************************//**
 * Notifies user about BLOB Transfer progress
 *
 * @param self BLOB Transfer Client descriptor structure
 * @param confirmed_tx_bytes Number of transmitted bytes confirmed
 ******************************************************************************/
static void notify_progress(blob_transfer_client_t *const self,
                            uint32_t confirmed_tx_bytes);

/***************************************************************************//**
 * Notifies user that server has failed
 *
 * @param self BLOB Transfer Client descriptor structure
 * @param server_address Address of the server that failed
 * @param timeout Timout flag
 * @param error Error code of failure
 ******************************************************************************/
static void notify_server_failed(blob_transfer_client_t *const self,
                                 uint16_t server_address,
                                 uint8_t timeout,
                                 uint8_t error);

/***************************************************************************//**
 * Notifies user that transfer has failed
 *
 * @param self BLOB Transfer Client descriptor structure
 ******************************************************************************/
static void process_transfer_failed(blob_transfer_client_t *const self);

/***************************************************************************//**
 * Transitions the BLOB Transfer Client state machine into the selected state
 *
 * @param self Pointer to the BLOB Transfer Client descriptor structure
 * @param target_state State to transfer into
 ******************************************************************************/
static void state_transition(blob_transfer_client_t *const self,
                             blob_transfer_client_state_t target_state);

/***************************************************************************//**
 * Handles Transfer Complete event
 *
 * The event is received when the transfer has completed, either successfully or
 * unsuccessfully. Success depends on the state of servers.
 *
 * @param self Pointer to the BLOB Transfer Client descriptor structure
 ******************************************************************************/
static void handle_transfer_complete(blob_transfer_client_t *const self);

/***************************************************************************//**
 * Callback for retry timer
 *
 * @param timer Timer handler
 * @param data Callback data
 ******************************************************************************/
static void retry_timer_cb(app_timer_t *timer, void *data);

/***************************************************************************//**
 * Callback for separation timer
 *
 * @param timer Timer handler
 * @param data Callback data
 ******************************************************************************/
static void separation_timer_cb(app_timer_t *timer, void *data);

/***************************************************************************//**
 * Callback for chunk request response retry timer
 *
 * @param timer Timer handler
 * @param data Callback data
 ******************************************************************************/
static void send_chunk_request_response(app_timer_t *timer, void *data);

// -----------------------------------------------------------------------------
//                      Static Inline Function Declarations
// -----------------------------------------------------------------------------

/***************************************************************************//**
 * Calculates the number of blocks for the BLOB being transferred
 *
 * @param self Pointer to the BLOB Transfer Client descriptor structure
 * @return Number of blocks in BLOB
 ******************************************************************************/
__STATIC_INLINE uint16_t calc_total_block_count(blob_transfer_client_t *const self)
{
  uint32_t block_count = (self->blob_size >> self->block_size_log);

  // Check if there's a partial block at the end
  if (0 != (self->blob_size & ((1UL << self->block_size_log) - 1))) {
    // If so increment block count to include the partial last block
    block_count++;
  }
  return block_count;
}

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

static const blob_transfer_client_state_flags_t state_flags[STATE_COUNT] = {
  [STATE_UNINIT]              = { .idle = 0, .retry = 0, .separation = 0 },
  [STATE_INACTIVE]            = { .idle = 1, .retry = 0, .separation = 0 },
  [STATE_TRANSFER_FAILED]     = { .idle = 1, .retry = 0, .separation = 0 },
  [STATE_TRANSFER_COMPLETED]  = { .idle = 1, .retry = 0, .separation = 0 },
  [STATE_TRANSFER_CANCELED]   = { .idle = 1, .retry = 0, .separation = 0 },
  [STATE_SEND_QUERY_INFO]     = { .idle = 0, .retry = 1, .separation = 0 },
  [STATE_SEND_TRANSFER_START] = { .idle = 0, .retry = 1, .separation = 0 },
  [STATE_SEND_BLOCK_START]    = { .idle = 0, .retry = 1, .separation = 0 },
  [STATE_SEND_CHUNKS]         = { .idle = 0, .retry = 0, .separation = 1 },
  [STATE_SEND_BLOCK_QUERY]    = { .idle = 0, .retry = 1, .separation = 0 },
  [STATE_CANCELING]           = { .idle = 0, .retry = 1, .separation = 0 },
  [STATE_SUSPENDED]           = { .idle = 0, .retry = 0, .separation = 0 }
};

static blob_transfer_client_t blob_tf_client;

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

// Set up a new BLOB transfer
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
                                                 const uint8_t* servers)
{
  sl_status_t sc;
  blob_transfer_client_t *const self = &blob_tf_client;

  if (0 == state_flags[self->state].idle) {
    log_error(LOG_PREFIX
              "Setup call in non-idle state (elem=%d)" NL,
              elem_index);
    return SL_STATUS_INVALID_STATE;
  }

  self->blob_size = blob_size;

  // The BLOB Transfer Server component supports both transfer mode so the mbt
  // client stack model setup function is called accordingly and the transfer
  // mode is selected when the BLOB transfer is started
  sc = sl_btmesh_mbt_client_setup(elem_index,
                                  blob_id,
                                  blob_size,
                                  appkey_index,
                                  ttl,
                                  timeout_base,
                                  (uint8_t) sl_btmesh_mbt_client_mbt_transfer_mode_both,
                                  group_address,
                                  virtual_address,
                                  multicast_threshold,
                                  servers_len,
                                  servers);
  log_status_error_f(sc,
                     LOG_PREFIX "Setup has failed (elem=%d)" NL,
                     elem_index);
  return sc;
}

sl_status_t sl_btmesh_blob_transfer_client_set_params(uint16_t elem_index,
                                                      uint16_t separation_time_ms,
                                                      uint16_t retry_time_ms,
                                                      uint16_t retry_max)
{
  (void) elem_index;
  blob_transfer_client_t *const self = &blob_tf_client;

  if (0 == state_flags[self->state].idle) {
    log_error(LOG_PREFIX
              "set Params call in non-idle state (elem=%d)" NL,
              elem_index);
    return SL_STATUS_INVALID_STATE;
  }

  self->separation_time_ms = separation_time_ms;
  self->retry_time_ms = retry_time_ms;
  self->retry_max = retry_max;

  return SL_STATUS_OK;
}

sl_status_t sl_btmesh_blob_transfer_client_setup_data_provider_array(uint16_t elem_index,
                                                                     const uint8_t *array,
                                                                     uint32_t length)
{
  (void)elem_index;
  blob_transfer_client_t *const self = &blob_tf_client;

  app_assert(NULL != array, "BLOB Transfer array is null.");
  app_assert(0 != length, "BLOB Transfer array length is zero.");

  if (0 == state_flags[self->state].idle) {
    log_error(LOG_PREFIX
              "Data Provider call in non-idle state (elem=%d)" NL,
              elem_index);
    return SL_STATUS_INVALID_STATE;
  }

  // If the upper layer is NOT the distribution server, then the BLOB size
  // parameter of sl_btmesh_blob_transfer_client_setup shall be consistent with
  // data size parameter of data provider
  // Note: if the upper layer is the btmesh_fw_distribution_server then the
  //       sl_btmesh_blob_transfer_client_setup is not called as the setup
  //       process is executed automatically in the BT Mesh stack
  if (0 == self->blob_size) {
    self->blob_size = length;
  } else if (self->blob_size != length) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  self->data_provider.type = BLOB_DATA_PROVIDER_ARRAY;
  self->data_provider.descriptor.array.data = array;
  self->data_provider.descriptor.array.length = length;

  return SL_STATUS_OK;
}

sl_status_t sl_btmesh_blob_transfer_client_setup_data_provider_blob_storage(uint16_t elem_index,
                                                                            const sl_bt_uuid_64_t *blob_id)
{
  (void)elem_index;
  blob_transfer_client_t *const self = &blob_tf_client;
  uint32_t blob_size;

  app_assert(NULL != blob_id, "BLOB id is null.");

  if (0 == state_flags[self->state].idle) {
    log_error(LOG_PREFIX
              "Data Provider call in non-idle state (elem=%d)" NL,
              elem_index);
    return SL_STATUS_INVALID_STATE;
  }

  // Check if the BLOB id exists at all in the BLOB storage
  sl_status_t sc = sl_btmesh_blob_storage_get_blob_size(blob_id,
                                                        &blob_size);
  if (SL_STATUS_OK != sc) {
    log_status_error_f(sc,
                       LOG_PREFIX "Data Provider setup failed (elem=%d)" NL,
                       elem_index);
    return sc;
  }
  // If the upper layer is NOT the distribution server then BLOB size parameter
  // of sl_btmesh_blob_transfer_client_setup shall be consistent with data size
  // parameter of data provider
  // Note: if the upper layer is the btmesh_fw_distribution_server then the
  //       sl_btmesh_blob_transfer_client_setup is not called as the setup
  //       process is executed automatically in the BT Mesh stack
  if (0 == self->blob_size) {
    self->blob_size = blob_size;
  } else if (self->blob_size != blob_size) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  self->data_provider.type = BLOB_DATA_PROVIDER_BLOB_STORAGE;
  memcpy(&self->data_provider.descriptor.blob_storage.blob_id,
         blob_id,
         sizeof(self->data_provider.descriptor.blob_storage.blob_id));

  return SL_STATUS_OK;
}

sl_status_t sl_btmesh_blob_transfer_client_start(uint16_t elem_index,
                                                 sl_btmesh_mbt_client_transfer_mode_t transfer_mode,
                                                 sl_btmesh_blob_transfer_client_notify_cb_t notify)
{
  (void)elem_index;
  blob_transfer_client_t *const self = &blob_tf_client;

  if (transfer_mode == sl_btmesh_mbt_client_mbt_transfer_mode_none) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  if (0 == state_flags[self->state].idle) {
    log_error(LOG_PREFIX
              "Start call in non-idle state (elem=%d)" NL,
              elem_index);
    return SL_STATUS_INVALID_STATE;
  }

  if (BLOB_DATA_PROVIDER_NONE == self->data_provider.type) {
    return SL_STATUS_INVALID_CONFIGURATION;
  }

  self->elem_index = elem_index;
  self->transfer_mode = transfer_mode;
  self->notify = notify;

  state_transition(self, STATE_SEND_QUERY_INFO);

  if (STATE_SEND_QUERY_INFO != self->state) {
    // The state transition might not be successful, if the query information
    // BT Mesh stack API call fails (sl_btmesh_mbt_client_query_information)
    // however this should not happen.
    log_error(LOG_PREFIX
              "Start call state transition failed (elem=%d,state=%d)" NL,
              elem_index,
              self->state);
    return SL_STATUS_INVALID_STATE;
  }

  return SL_STATUS_OK;
}

void sl_btmesh_blob_transfer_client_cancel(uint16_t elem_index)
{
  (void) elem_index;
  blob_transfer_client_t *const self = &blob_tf_client;

  state_transition(self, STATE_CANCELING);
}

sl_status_t sl_btmesh_blob_transfer_client_abort(uint16_t elem_index)
{
  (void) elem_index;
  blob_transfer_client_t *const self = &blob_tf_client;

  state_transition(self, STATE_INACTIVE);

  return sl_btmesh_mbt_client_abort(self->elem_index);
}

sl_status_t sl_btmesh_blob_transfer_client_on_aborted(uint16_t elem_index)
{
  (void) elem_index;
  sl_status_t sc;

  blob_transfer_client_t *const self = &blob_tf_client;

  if (STATE_INACTIVE != self->state) {
    state_transition(self, STATE_INACTIVE);
    sc = SL_STATUS_OK;
  } else {
    sc = SL_STATUS_INVALID_STATE;
  }

  return sc;
}

sl_status_t sl_btmesh_blob_transfer_client_on_suspended(uint16_t elem_index)
{
  (void) elem_index;
  sl_status_t sc = SL_STATUS_FAIL;
  blob_transfer_client_t *const self = &blob_tf_client;

  if (0 == state_flags[self->state].idle) {
    state_transition(self, STATE_SUSPENDED);
    sc = SL_STATUS_OK;
  } else {
    sc = SL_STATUS_INVALID_STATE;
  }

  return sc;
}

sl_status_t sl_btmesh_blob_transfer_client_on_resumed(uint16_t elem_index)
{
  (void) elem_index;
  sl_status_t sc = SL_STATUS_FAIL;
  blob_transfer_client_t *const self = &blob_tf_client;

  if (STATE_SUSPENDED == self->state) {
    state_transition(self, STATE_SEND_TRANSFER_START);
    sc = SL_STATUS_OK;
  } else {
    sc = SL_STATUS_INVALID_STATE;
  }

  return sc;
}

SL_WEAK uint8_t
sl_btmesh_blob_transfer_client_calculate_block_size_log(uint32_t blob_size,
                                                        uint8_t  block_size_log_min,
                                                        uint8_t  block_size_log_max,
                                                        uint16_t block_count_max,
                                                        uint16_t max_chunk_size_min,
                                                        uint16_t max_chunks_min)
{
  uint32_t block_size_min_limit, block_size_max_limit;
  uint8_t block_size_log = block_size_log_max;
  uint32_t block_size = 1UL << block_size_log_max;

  // Block size can't be greater than the product of the maximum chunk size and
  // the maximum number of chunks per block
  block_size_max_limit =
    (uint32_t) max_chunk_size_min * max_chunks_min;
  // Minimum block size is limited by the maximum number of blocks, because
  // high BLOB size with small blocks leads to too many blocks.
  block_size_min_limit = (blob_size + block_count_max - 1) / block_count_max;

  // The default block size calculation prefers the maximum possible block size,
  // which leads to the highest transfer speed due to fewer BLOB Block Start
  // Block Get and Block Status messages. BLOB Transfer Client has to wait for
  // the status message of every BLOB Transfer Server which can add up quite
  // fast in a multicast scenario, where there are tens or hundreds of nodes.
  // Note: It is unlikely, but possible, that the block_size_log_max is smaller
  //       than block_size_log_min because the block size log ranges of the
  //       different BLOB Transfer Servers have no intersection. In this case it
  //       is not possible to transfer the BLOB to all servers at the same time
  //       so the implementation chooses the block_size_log_max to send the BLOB
  //       at least to a subset of servers.
  //       In general this should not happen in case of firmware image transfer
  //       because the same kind of updating nodes are updated with the same
  //       firmware so their capabilities should match.
  for (block_size_log = block_size_log_max;
       block_size_log_min <= block_size_log;
       block_size_log--) {
    block_size = 1UL << block_size_log;
    if (block_size <= block_size_max_limit) {
      break;
    }
  }

  if ((block_size < block_size_min_limit)
      && (block_size_max_limit < block_size)) {
    return SL_BTMESH_BLOB_TRANSFER_CLIENT_INVALID_BLOCK_SIZE_LOG;
  }

  return block_size_log;
}

SL_WEAK uint16_t
sl_btmesh_blob_transfer_client_calculate_chunk_size(uint8_t block_size_log,
                                                    uint16_t max_chunk_size_min,
                                                    uint16_t max_chunks_min,
                                                    uint16_t nw_pdu_size)
{
  const uint16_t LOTP_PAYLOAD_PER_SEG_MSG = 12;
  const uint16_t LOTP_PAYLOAD_PER_NON_SEG_MSG = 15;
  // Protocol overhead of Network Layer
  // (IVI+NID) + (CTL+TTL) + SEQ + SRC + DST + NetMIC = 13 bytes
  //    1      +     1     +  3  +  2  +  2  +   4    = 13 bytes
  const uint16_t NW_MSG_PROT_OVERHEAD = 13;
  // Protocol overhead of Lower Transport Layer
  // (SEG+AID+AKF) = 1 byte
  const uint16_t LOTP_UNSEG_MSG_PROT_OVERHEAD = 1;
  // Protocol overhead of Upper Transport Layer: TransMIC (4 bytes)
  const uint16_t UPTP_PROT_OVERHEAD = 4;
  // BLOB Chunk Transfer access message: Opcode (1byte) + Chunk number (2 byte)
  const uint16_t ACCESS_CHUNK_PROT_OVERHEAD = 3;
  // Total protocol overhead of upper transport layer and access layer
  const uint16_t UPTP_ACCESS_PROT_OVERHEAD =
    UPTP_PROT_OVERHEAD + ACCESS_CHUNK_PROT_OVERHEAD;
  // BLOB Chunk Transfer unsegmented access message data size
  const uint16_t ACCESS_CHUNK_DATA_PER_NON_SEG_MSG =
    LOTP_PAYLOAD_PER_NON_SEG_MSG - UPTP_ACCESS_PROT_OVERHEAD;
  // Total protocol overhead in NW PDU (unsegmented)
  const uint16_t TOTAL_UNSEG_PROT_OVERHEAD = NW_MSG_PROT_OVERHEAD
                                             + LOTP_UNSEG_MSG_PROT_OVERHEAD
                                             + UPTP_PROT_OVERHEAD
                                             + ACCESS_CHUNK_PROT_OVERHEAD;

  uint32_t block_size = 1 << block_size_log;
  // The block size and maximum number of chunks limits the chunk size (minimum)
  uint16_t min_chunk_size = (block_size + max_chunks_min - 1) / max_chunks_min;
  uint16_t chunk_size;

  if (SL_BTMESH_BLOB_TRANSFER_CLIENT_MAX_CHUNK_SIZE_CFG_VAL < max_chunk_size_min) {
    max_chunk_size_min = SL_BTMESH_BLOB_TRANSFER_CLIENT_MAX_CHUNK_SIZE_CFG_VAL;
  }

  if (max_chunk_size_min < min_chunk_size) {
    // This should not happen if the BLOB transfer servers are configured properly.
    // The max_chunk_size_min is returned because it might work for some servers
    // when the configurations of BLOB transfer servers are different.
    return max_chunk_size_min;
  }

  if (STANDARD_NETWORK_PDU_SIZE < nw_pdu_size) {
    // The Silicon Labs BT Mesh over Advertisement Extensions proprietary feature
    // is enabled so the chunk size is calculated to fit into a single AE packet
    // unless the calculated chunk size is not in the allowed chunk size range.
    chunk_size = nw_pdu_size - TOTAL_UNSEG_PROT_OVERHEAD;
    if (min_chunk_size <= chunk_size && chunk_size <= max_chunk_size_min) {
      return chunk_size;
    } else if (max_chunk_size_min < chunk_size) {
      return max_chunk_size_min;
    } else {
      // If AE packet can't be used then the chunk size calculation falls back
      // to standard BT Mesh 1.0 advertisements.
    }
  }

  if (max_chunk_size_min <= (2 * LOTP_PAYLOAD_PER_SEG_MSG - UPTP_ACCESS_PROT_OVERHEAD)) {
    if (max_chunk_size_min <= ACCESS_CHUNK_DATA_PER_NON_SEG_MSG) {
      // If max_chunk_size_min is less than chunk data size which fits into a
      // single segment then the max_chunk_size_min is used as the chunk size.
      chunk_size = max_chunk_size_min;
    } else {
      // If the max chunk size does not make it possible to fill two segments
      // completely with data then it is not efficient to send segmented messages
      // so unsegmented chunks are used if min_chunk_size makes it possible.
      if (min_chunk_size <= ACCESS_CHUNK_DATA_PER_NON_SEG_MSG) {
        chunk_size = ACCESS_CHUNK_DATA_PER_NON_SEG_MSG;
      } else {
        chunk_size = max_chunk_size_min;
      }
    }
  } else if (SL_BTMESH_BLOB_TRANSFER_CLIENT_PREF_CHUNK_SIZE_CFG_VAL < min_chunk_size) {
    // If the preferred chunk size is less than the min_chunk_size then chunk
    // size is set to the closest value which results in full chunk segments.
    chunk_size = ((min_chunk_size + UPTP_ACCESS_PROT_OVERHEAD + LOTP_PAYLOAD_PER_SEG_MSG - 1)
                  / LOTP_PAYLOAD_PER_SEG_MSG) * LOTP_PAYLOAD_PER_SEG_MSG
                 - UPTP_ACCESS_PROT_OVERHEAD;
    if (chunk_size < min_chunk_size || max_chunk_size_min < chunk_size) {
      // If selected chunk size does not fit into the allowed chunk size range
      // then min_chunk_size is selected.
      chunk_size = min_chunk_size;
    }
  } else if (max_chunk_size_min < SL_BTMESH_BLOB_TRANSFER_CLIENT_PREF_CHUNK_SIZE_CFG_VAL) {
    // If the preferred chunk size is greater than the max_chunk_size_min then
    // chunk size is set to the closest value which results in full chunk segments.
    chunk_size = ((max_chunk_size_min + UPTP_ACCESS_PROT_OVERHEAD)
                  / LOTP_PAYLOAD_PER_SEG_MSG) * LOTP_PAYLOAD_PER_SEG_MSG
                 - UPTP_ACCESS_PROT_OVERHEAD;
    if (chunk_size < min_chunk_size || max_chunk_size_min < chunk_size) {
      // If selected chunk size does not fit into the allowed chunk size range
      // then max_chunk_size_min is selected.
      chunk_size = max_chunk_size_min;
    }
  } else {
    // The preferred chunk size is selected if it fits into the allowed
    // chunk size range.
    chunk_size = SL_BTMESH_BLOB_TRANSFER_CLIENT_PREF_CHUNK_SIZE_CFG_VAL;
  }

  return chunk_size;
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------

static void notify_transfer_result(blob_transfer_client_t *const self,
                                   sl_btmesh_blob_transfer_client_result_t result)
{
  if (NULL != self->notify) {
    sl_btmesh_blob_transfer_client_notification_t notification;
    notification.kind = SL_BTMESH_BLOB_TRANSFER_CLIENT_KIND_TRANSFER_RESULT;
    notification.elem_index = self->elem_index;
    notification.params.transfer_result = result;
    self->notify(&notification);
  }
}

static void notify_progress(blob_transfer_client_t *const self,
                            uint32_t confirmed_tx_bytes)
{
  if (NULL != self->notify) {
    sl_btmesh_blob_transfer_client_notification_t notification;
    notification.kind = SL_BTMESH_BLOB_TRANSFER_CLIENT_KIND_PROGRESS;
    notification.elem_index = self->elem_index;
    notification.params.progress.confirmed_tx_bytes = confirmed_tx_bytes;
    notification.params.progress.blob_size = self->blob_size;
    self->notify(&notification);
  }
}

static void notify_server_failed(blob_transfer_client_t *const self,
                                 uint16_t server_address,
                                 uint8_t timeout,
                                 uint8_t error)
{
  if (NULL != self->notify) {
    sl_btmesh_blob_transfer_client_notification_t notification;
    notification.kind = SL_BTMESH_BLOB_TRANSFER_CLIENT_KIND_SERVER_FAILED;
    notification.elem_index = self->elem_index;
    notification.params.server_failed.server_address = server_address;
    notification.params.server_failed.timeout = timeout;
    notification.params.server_failed.error = error;
    self->notify(&notification);
  }
}

static void process_transfer_failed(blob_transfer_client_t *const self)
{
  notify_transfer_result(self,
                         SL_BTMESH_BLOB_TRANSFER_CLIENT_RESULT_FAILED);
  state_transition(self, STATE_TRANSFER_FAILED);
}

static void start_retry_timer(blob_transfer_client_t *const self)
{
  sl_status_t sc;

  if (0 == self->retry_time_ms) {
    // If the retry time is zero then it means that the retry shall be performed
    // immediately after the current messages are sent to the server.
    // (tx complete)
    retry_timer_cb(&self->retry_timer, self);
  } else {
    // Wait for the retry time to provide some time for the servers to respond
    // This also spares bandwidth, because the BLOB transfer client does not
    // flood the mesh network with messages
    sc = app_timer_start(&self->retry_timer,
                         self->retry_time_ms,
                         retry_timer_cb,
                         self,
                         false);
    app_assert_status_f(sc,
                        "Failed to start retry timer (elem=%d)",
                        self->elem_index);
  }
}

static void restart_retry_timer(blob_transfer_client_t *const self)
{
  // In case in the meantime the state-machine transitioned into a state without
  // retry, to avoid unintended behavior.
  if (!state_flags[self->state].retry) {
    return;
  }
  start_retry_timer(self);
}

static void stop_retry_timer(blob_transfer_client_t *const self)
{
  // It is not considered an error, if stop is requested for a timer which is
  // not running therefore stop is always called here to be safe
  sl_status_t sc = app_timer_stop(&self->retry_timer);

  app_assert_status_f(sc,
                      "Failed to stop retry timer (elem=%d)",
                      self->elem_index);
}

static void start_separation_timer(blob_transfer_client_t *const self)
{
  sl_status_t sc;

  if (0 == self->separation_time_ms) {
    /*
     * If the separation time is zero then the callback function shall be called
     * immediately and it is not necessary to start the timer at all
     */
    separation_timer_cb(&self->separation_timer, self);
  } else {
    /*
     * Wait the separation time to have some idle time between mesh messages
     * to avoid flooding the mesh network with messages
     */
    sc = app_timer_start(&self->separation_timer,
                         self->separation_time_ms,
                         separation_timer_cb,
                         self,
                         false);
    app_assert_status_f(sc,
                        "Failed to start separation timer (elem=%d)",
                        self->elem_index);
  }
}

static void stop_separation_timer(blob_transfer_client_t *const self)
{
  // It is not considered an error, if stop is requested for a timer which is
  // not running therefore stop is always called here to be safe
  sl_status_t sc = app_timer_stop(&self->separation_timer);

  app_assert_status_f(sc,
                      "Failed to stop separation timer (elem=%d)",
                      self->elem_index);
}

static void sl_btmesh_blob_transfer_client_element_init(uint16_t elem_index)
{
  sl_status_t sc;
  blob_transfer_client_t *const self = &blob_tf_client;

  self->data_provider.type = BLOB_DATA_PROVIDER_NONE;
  self->elem_index = elem_index;
  self->state = STATE_UNINIT;

  sc = sl_btmesh_mbt_client_init(elem_index,
                                 SL_BTMESH_BLOB_TRANSFER_CLIENT_MAX_SERVERS_CFG_VAL,
                                 SL_BTMESH_BLOB_TRANSFER_CLIENT_MAX_BLOCKS_CFG_VAL,
                                 SL_BTMESH_BLOB_TRANSFER_CLIENT_MAX_CHUNKS_PER_BLOCK_CFG_VAL);

  app_assert_status_f(sc, "Failed to init BLOB Transfer Client");

  state_transition(self, STATE_INACTIVE);
}

static void sl_btmesh_blob_transfer_client_init(void)
{
  sl_btmesh_blob_transfer_client_element_init(BTMESH_BLOB_TRANSFER_CLIENT_MAIN);
}

// Process the return value of MBT procedure BT Mesh stack API calls in retry state
static void process_mbt_procedure_status(blob_transfer_client_t *const self,
                                         sl_status_t sc)
{
  if (SL_STATUS_OK != sc) {
    if ((SL_STATUS_BUSY == sc) || (SL_STATUS_NO_MORE_RESOURCE == sc)) {
      // The retry counter is not incremented here, because the message was not
      // sent at all due to busy transport layer or not enough memory but the
      // current operation shall be retried later
      start_retry_timer(self);
    } else {
      // The retry counter is incremented to reduce number of retries in case
      // of unrecoverable errors but the retry timer is started for additional
      // robustness in case of unexpected temporary errors
      if ((self->retry_counter + 1) < self->retry_max) {
        // The retry counter is incremented by 2 overall (other in state_transition)
        self->retry_counter++;
        start_retry_timer(self);
      }
    }
  }
}

static void super_state_idle_entry(blob_transfer_client_t *const self)
{
  self->data_provider.type = BLOB_DATA_PROVIDER_NONE;
  self->separation_time_ms = SL_BTMESH_BLOB_TRANSFER_CLIENT_SEPARATION_TIME_MS_DEFAULT_CFG_VAL;
  self->retry_max = SL_BTMESH_BLOB_TRANSFER_CLIENT_RETRY_MAX_DEFAULT_CFG_VAL;
  self->retry_time_ms = SL_BTMESH_BLOB_TRANSFER_CLIENT_RETRY_TIME_MS_DEFAULT_CFG_VAL;
  self->blob_size = 0;
}

static void state_send_query_info_entry(blob_transfer_client_t *const self)
{
  sl_status_t sc;

  // Send the BLOB Information Get messages to the BLOB Transfer servers.
  // Based on the multicast threshold multiple messages could be sent.
  // Multiple BLOB transfer server can receive the messages
  sc = sl_btmesh_mbt_client_query_information(self->elem_index);

  log_info(LOG_PREFIX "Query Info procedure %s%s(elem=%d)" NL,
           (0 < self->retry_counter) ? "retry " : "",
           (SL_STATUS_BUSY == sc) ? "busy "
           : ((SL_STATUS_NO_MORE_RESOURCE == sc) ? "no memory " : ""),
           self->elem_index);

  process_mbt_procedure_status(self, sc);
  log_procedure_status_error(sc, "Query Info", self->elem_index);
}

static void state_send_transfer_start_entry(blob_transfer_client_t *const self)
{
  sl_status_t sc;

  // Send the BLOB Transfer Start messages to the BLOB Transfer servers.
  // Based on the multicast threshold multiple messages could be sent.
  // Multiple BLOB transfer server can receive the messages
  sc = sl_btmesh_mbt_client_start_transfer(self->elem_index,
                                           self->block_size_log,
                                           self->transfer_mode);

  log_info(LOG_PREFIX "Start procedure %s%s(elem=%d,blk_log=%d,tf_mode=%s)" NL,
           (0 < self->retry_counter) ? "retry " : "",
           (SL_STATUS_BUSY == sc) ? "busy "
           : ((SL_STATUS_NO_MORE_RESOURCE == sc) ? "no memory " : ""),
           self->elem_index,
           self->block_size_log,
           sl_btmesh_blob_transfer_client_transfer_mode_to_string(self->transfer_mode));

  process_mbt_procedure_status(self, sc);
  log_procedure_status_error(sc, "Start", self->elem_index);
}

static void state_send_start_block_entry(blob_transfer_client_t *const self)
{
  sl_status_t sc;
  uint16_t block_number = 0;
  uint32_t block_size = 0;

  // Send the BLOB Transfer Block Start messages to the BLOB Transfer servers.
  // Based on the multicast threshold multiple messages could be sent.
  // Multiple BLOB transfer server can receive the messages
  // Note: the block number and block size are not used here, because those are
  //       set in the block start complete event.
  sc = sl_btmesh_mbt_client_start_block(self->elem_index,
                                        self->current_block_chunk_size,
                                        &block_number,
                                        &block_size);

  log_info(LOG_PREFIX "Block Start procedure %s%s(elem=%d,chunk_size=%d)" NL,
           (0 < self->retry_counter) ? "retry " : "",
           (SL_STATUS_BUSY == sc) ? "busy "
           : ((SL_STATUS_NO_MORE_RESOURCE == sc) ? "no memory " : ""),
           self->elem_index,
           self->current_block_chunk_size);

  process_mbt_procedure_status(self, sc);
  log_procedure_status_error(sc, "Block Start", self->elem_index);
}

static void state_send_block_query_entry(blob_transfer_client_t *const self)
{
  sl_status_t sc;

  sc = sl_btmesh_mbt_client_query_block_status(self->elem_index);

  log_info(LOG_PREFIX "Block Query procedure %s%s(elem=%d)" NL,
           (0 < self->retry_counter) ? "retry " : "",
           (SL_STATUS_BUSY == sc) ? "busy "
           : ((SL_STATUS_NO_MORE_RESOURCE == sc) ? "no memory " : ""),
           self->elem_index);

  process_mbt_procedure_status(self, sc);
  log_procedure_status_error(sc, "Block Query", self->elem_index);
}

static void state_send_cancel(blob_transfer_client_t *const self)
{
  sl_status_t sc;

  sc = sl_btmesh_mbt_client_cancel_transfer(self->elem_index);

  log_info(LOG_PREFIX "Transfer Cancel procedure %s%s(elem=%d)" NL,
           (0 < self->retry_counter) ? "retry " : "",
           (SL_STATUS_BUSY == sc) ? "busy "
           : ((SL_STATUS_NO_MORE_RESOURCE == sc) ? "no memory " : ""),
           self->elem_index);

  process_mbt_procedure_status(self, sc);
  log_procedure_status_error(sc, "Cancel", self->elem_index);
}

static void send_chunk(blob_transfer_client_t *const self)
{
  // This is a sanity check to avoid buffer overflow, but this should not happen
  // due to the max chunk size saturation in handle_query_information_complete
  if (SL_BTMESH_BLOB_TRANSFER_CLIENT_MAX_CHUNK_SIZE_CFG_VAL < self->current_chunk_length) {
    log_error(LOG_PREFIX "chunk length is too high (elem=%d,"
                         "chunk_len=0x%04X,chunk_len_max=0x%04X)" NL,
              self->elem_index,
              self->current_chunk_length,
              SL_BTMESH_BLOB_TRANSFER_CLIENT_MAX_CHUNK_SIZE_CFG_VAL);
    process_transfer_failed(self);
    return;
  }

  self->chunk_requested = false;
  self->separation_time_elapsed = false;

  if (BLOB_DATA_PROVIDER_ARRAY == self->data_provider.type) {
    self->chunk_data_ptr =
      &self->data_provider.descriptor.array.data[self->current_chunk_offset];
    const uint32_t array_length = self->data_provider.descriptor.array.length;

    if (array_length < self->current_chunk_offset + self->current_chunk_length) {
      log_error(LOG_PREFIX
                "length mismatch when read from array provider "
                "(elem=%d,offset=0x%08lX,chunk_len=0x%04X,array_len=0x%08lX)" NL,
                self->elem_index,
                self->current_chunk_offset,
                self->current_chunk_length,
                array_length);
      process_transfer_failed(self);
      return;
    }
  } else if (BLOB_DATA_PROVIDER_BLOB_STORAGE == self->data_provider.type) {
    sl_status_t sc;
    uint32_t chunk_length = self->current_chunk_length;
    const sl_bt_uuid_64_t *blob_id =
      &self->data_provider.descriptor.blob_storage.blob_id;
    self->chunk_data_ptr = &self->chunk_data[0];

    sc = sl_btmesh_blob_storage_read(blob_id,
                                     self->current_chunk_offset,
                                     &chunk_length,
                                     &self->chunk_data[0]);
    if (SL_STATUS_OK != sc) {
      log_status_error_f(sc,
                         LOG_PREFIX
                         "failed to read from BLOB storage "
                         "(elem=%d,blobid=%s,offset=0x%08lX,chunk_len=0x%04X)" NL,
                         self->elem_index,
                         BLOB_ID_TO_STRING(blob_id),
                         self->current_chunk_offset,
                         self->current_chunk_length);
      process_transfer_failed(self);
      return;
    } else if (chunk_length != self->current_chunk_length) {
      // The length of the read data is less than the requested
      log_error(LOG_PREFIX
                "BLOB storage read length mismatch (elem=%d,blobid=%s,"
                "offset=0x%08lX,req_chunk_len=0x%04X,is_chunk_len=0x%04lX)" NL,
                self->elem_index,
                BLOB_ID_TO_STRING(blob_id),
                self->current_chunk_offset,
                self->current_chunk_length,
                chunk_length);
      process_transfer_failed(self);
      return;
    }
  } else {
    // This is an unexpected error, as previous state machine state makes sure
    // this should not happen so the transfer is stopped and a log message
    // is emitted
    log_error(LOG_PREFIX "invalid data provider" NL);
    process_transfer_failed(self);
    return;
  }

  // Chunk request has its own retry mechanism
  send_chunk_request_response(&self->retry_timer, self);
}

static void handle_server_information_status(blob_transfer_client_t *const self,
                                             const sl_btmesh_evt_mbt_client_server_information_status_t *const evt)
{
  (void)evt; // To suppress the warning if the logging is disabled

  // Restart the timer since we know in case this event is handled, that the
  // message was sent out properly. However, we don't stop the retry timer,
  // since if any node doesn't respond, we still need to retry.
  restart_retry_timer(self);

#if (SL_BTMESH_BLOB_TRANSFER_CLIENT_LOG_BLOB_STATUS_MSG_CFG_VAL != 0)
  // This event is triggered, if one BLOB Information Status message is received
  // from a specific server. The BT Mesh stack waits for the status message of
  // every server and triggers the query information complete event with the
  // block and chunk parameters supported by every server.
  // This means that it is not necessary to store the information about every
  // server as the stack aggregates them and provides it in another event.
  // The individual information could be useful for analysis and diagnostics
  // so it is logged.
  log_info(LOG_PREFIX
           "Info received (elem=%d,addr=0x%04X,blk_log=%d-%d,"
           "max_chunk_size=0x%04X,max_chunks=%d)" NL,
           evt->elem_index,
           evt->server_address,
           evt->min_block_size_log,
           evt->max_block_size_log,
           evt->max_chunk_size,
           evt->max_chunks);
#endif // SL_BTMESH_BLOB_TRANSFER_CLIENT_LOG_BLOB_STATUS_MSG_CFG_VAL
}

static void handle_server_transfer_status(blob_transfer_client_t *const self,
                                          const sl_btmesh_evt_mbt_client_server_transfer_status_t *const evt)
{
  (void)evt; // To suppress the warning if the logging is disabled

  // Restart the timer since we know in case this event is handled, that the
  // message was sent out properly. However, we don't stop the retry timer,
  // since if any node doesn't respond, we still need to retry.
  restart_retry_timer(self);

#if (SL_BTMESH_BLOB_TRANSFER_CLIENT_LOG_BLOB_STATUS_MSG_CFG_VAL != 0)
  log_info(LOG_PREFIX
           "Transfer Status received (elem=%d,addr=0x%04X,status=%s,"
           "phase=%s,blobid=%s,blob_size=0x%08lX,blk_log=%d",
           evt->elem_index,
           evt->server_address,
           mbt_status_to_string(evt->status),
           mbt_phase_to_string(evt->phase),
           BLOB_ID_TO_STRING(&evt->blob_id),
           evt->blob_size,
           evt->block_size_log);
  if (0 < evt->blocks_not_received.len) {
    log_append_info(",miss_blks=");
    log_hexdump_info(evt->blocks_not_received.data, evt->blocks_not_received.len);
  }
  log_append_info(")" NL);
#endif // SL_BTMESH_BLOB_TRANSFER_CLIENT_LOG_BLOB_STATUS_MSG_CFG_VAL
}

static void handle_server_block_status(blob_transfer_client_t *const self,
                                       const sl_btmesh_evt_mbt_client_server_block_status_t *const evt)
{
  (void)evt; // To suppress the warning if the logging is disabled

  // Restart the timer since we know in case this event is handled, that the
  // message was sent out properly. However, we don't stop the retry timer,
  // since if any node doesn't respond, we still need to retry.
  restart_retry_timer(self);

#if (SL_BTMESH_BLOB_TRANSFER_CLIENT_LOG_BLOB_STATUS_MSG_CFG_VAL != 0)
  log_info(LOG_PREFIX "Block Status received (elem=%d,addr=0x%04X,status=%s",
           evt->elem_index,
           evt->server_address,
           mbt_status_to_string(evt->status));
  if (0 < evt->missing_chunks.len) {
    log_append_info(",miss_chunks=");
    log_hexdump_info(evt->missing_chunks.data, evt->missing_chunks.len);
  }
  log_append_info(")" NL);
#endif // SL_BTMESH_BLOB_TRANSFER_CLIENT_LOG_BLOB_STATUS_MSG_CFG_VAL
}

static void handle_server_partial_block_report(blob_transfer_client_t *const self,
                                               const sl_btmesh_evt_mbt_client_server_partial_block_report_t *const evt)
{
  (void)self;
  (void)evt; // To suppress the warning if the logging is disabled

#if (SL_BTMESH_BLOB_TRANSFER_CLIENT_LOG_BLOB_STATUS_MSG_CFG_VAL != 0)
  log_info(LOG_PREFIX "Partial Block Report received (elem=%d,addr=0x%04X",
           evt->elem_index,
           evt->server_address);
  if (0 < evt->missing_chunks.len) {
    log_append_info(",miss_chunks=");
    log_hexdump_info(evt->missing_chunks.data, evt->missing_chunks.len);
  }
  log_append_info(")" NL);
#endif // SL_BTMESH_BLOB_TRANSFER_CLIENT_LOG_BLOB_STATUS_MSG_CFG_VAL
}

static void handle_query_information_complete(blob_transfer_client_t *const self,
                                              const sl_btmesh_evt_mbt_client_query_information_complete_t *const evt)
{
  if (STATE_SEND_QUERY_INFO == self->state) {
    self->max_chunks_min = evt->max_chunks_min;

    if (SL_BTMESH_BLOB_TRANSFER_CLIENT_MAX_CHUNK_SIZE_CFG_VAL < evt->max_chunk_size_min) {
      self->max_chunk_size_min = SL_BTMESH_BLOB_TRANSFER_CLIENT_MAX_CHUNK_SIZE_CFG_VAL;
    } else {
      self->max_chunk_size_min = evt->max_chunk_size_min;
    }

    self->block_size_log =
      sl_btmesh_blob_transfer_client_calculate_block_size_log(self->blob_size,
                                                              evt->block_size_log_min,
                                                              evt->block_size_log_max,
                                                              SL_BTMESH_BLOB_TRANSFER_CLIENT_MAX_BLOCKS_CFG_VAL,
                                                              self->max_chunk_size_min,
                                                              evt->max_chunks_min);
    if (INVALID_BLOCK_SIZE_LOG == self->block_size_log) {
      self->block_size_log = evt->block_size_log_max;
      log_error(LOG_PREFIX
                "Block Size Calculation failed defaults to Block Size Log Max"
                "(elem=%d,blob_size=0x%08lX,blk_log=%d-%d,blk_cnt_max=%d,"
                "max_chunk_size=0x%04X,max_chunks=%d)" NL,
                evt->elem_index,
                self->blob_size,
                evt->block_size_log_min,
                evt->block_size_log_max,
                SL_BTMESH_BLOB_TRANSFER_CLIENT_MAX_BLOCKS_CFG_VAL,
                evt->max_chunk_size_min,
                evt->max_chunks_min);
    }

    sl_btmesh_mbt_client_transfer_mode_t supported_transfer_modes =
      (sl_btmesh_mbt_client_transfer_mode_t) evt->supported_transfer_modes;
    sl_btmesh_mbt_client_transfer_mode_t common_transfer_modes =
      (sl_btmesh_mbt_client_transfer_mode_t) evt->common_transfer_modes;

    // The supported_transfer_modes is used for logging only
    (void) supported_transfer_modes;

    log_info(LOG_PREFIX
             "Query Info Complete "
             "(elem=%d,blk_log=%d-%d,max_chunk_size=0x%04X,max_chunks=%d,"
             "sup_tf_mode=%s,com_tf_mode=%s)" NL,
             evt->elem_index,
             evt->block_size_log_min,
             evt->block_size_log_max,
             evt->max_chunk_size_min,
             evt->max_chunks_min,
             sl_btmesh_blob_transfer_client_transfer_mode_to_string(supported_transfer_modes),
             sl_btmesh_blob_transfer_client_transfer_mode_to_string(common_transfer_modes));

    if (sl_btmesh_mbt_client_mbt_transfer_mode_both == self->transfer_mode) {
      // The transfer mode shall be set by the query info completely
      switch (common_transfer_modes) {
        case sl_btmesh_mbt_client_mbt_transfer_mode_push:
        case sl_btmesh_mbt_client_mbt_transfer_mode_pull:
          self->transfer_mode = common_transfer_modes;
          break;
        case sl_btmesh_mbt_client_mbt_transfer_mode_both:
        // Push mode shall be the default if both transfer modes are supported
        case sl_btmesh_mbt_client_mbt_transfer_mode_none:
        // Subset of updating nodes can participate in the BLOB transfer because
        // neither transfer mode is supported by all nodes (defaults to push)
        // Note: it is not necessary to check the supported_transfer_modes in
        // the event because it must have "both" value otherwise the
        // common_transfer_modes would not be "none"
        default:
          self->transfer_mode = sl_btmesh_mbt_client_mbt_transfer_mode_push;
          break;
      }
    }
    state_transition(self, STATE_SEND_TRANSFER_START);
  } else {
    // This should not happen based on the state machine in the BT Mesh stack.
    // If the event is not received in the expected state then it is ignored
    // and a log message is emitted.
    log_debug(LOG_PREFIX
              "unexpected Query Info Complete event "
              "(elem=%d,state=%d)" NL,
              self->elem_index,
              self->state);
  }
}

static void handle_start_transfer_complete(blob_transfer_client_t *const self,
                                           const sl_btmesh_evt_mbt_client_start_transfer_complete_t *const evt)
{
  (void)evt; // To suppress the warning if the logging is disabled
  uint16_t nw_pdu_size = STANDARD_NETWORK_PDU_SIZE;

  if (STATE_SEND_TRANSFER_START == self->state) {
    log_info(LOG_PREFIX "Start Transfer Complete (elem=%d)" NL,
             evt->elem_index);

#ifdef SL_CATALOG_BTMESH_AE_SERVER_PRESENT
    sl_status_t sc_nw, sc_mdl;
    uint16_t configured_nw_pdu_size = STANDARD_NETWORK_PDU_SIZE;
    uint16_t blob_transfer_client_ae_enabled = false;
    sc_nw = sl_btmesh_silabs_config_server_get_network_pdu(&configured_nw_pdu_size);
    sc_mdl = sl_btmesh_silabs_config_server_get_model_enable(self->elem_index,
                                                             SIG_VENDOR_ID,
                                                             MESH_MBT_SERVER_MODEL_ID,
                                                             &blob_transfer_client_ae_enabled);
    if (sc_nw == SL_STATUS_OK && sc_mdl == SL_STATUS_OK) {
      if (blob_transfer_client_ae_enabled) {
        nw_pdu_size = configured_nw_pdu_size;
      } else {
        nw_pdu_size = STANDARD_NETWORK_PDU_SIZE;
      }
    } else {
      log_status_error_f(sc_nw,
                         LOG_PREFIX
                         "failed to query network PDU size (elem=%d)" NL,
                         self->elem_index);
      log_status_error_f(sc_nw,
                         LOG_PREFIX
                         "failed to query BLOB Transfer Client model AE status "
                         "(elem=%d)" NL,
                         self->elem_index);
    }
#endif // SL_CATALOG_BTMESH_AE_SERVER_PRESENT

    self->current_block_chunk_size =
      sl_btmesh_blob_transfer_client_calculate_chunk_size(self->block_size_log,
                                                          self->max_chunk_size_min,
                                                          self->max_chunks_min,
                                                          nw_pdu_size);

    // This is last event handler before the transfer of the blocks is started
    // therefore the progress notification with zero confirmed tx bytes shall
    // be emitted here
    notify_progress(self, 0);

    state_transition(self, STATE_SEND_BLOCK_START);
  } else {
    // This should not happen based on the state machine in the BT Mesh stack.
    // If the event is not received in the expected state then it is ignored
    // and a log message is emitted.
    log_debug(LOG_PREFIX
              "unexpected Start Transfer Complete event "
              "(elem=%d,state=%d)" NL,
              self->elem_index,
              self->state);
  }
}

static void handle_start_block_complete(blob_transfer_client_t *const self,
                                        const sl_btmesh_evt_mbt_client_start_block_complete_t *const evt)
{
  (void)evt; // To suppress the warning if the logging is disabled

  if (STATE_SEND_BLOCK_START == self->state) {
    self->current_block_number = evt->block_number;
    log_info(LOG_PREFIX
             "Start Block Complete (elem=%d,blk_idx=%d,blk_num=%d,blk_size=%lu)" NL,
             evt->elem_index,
             evt->block_number,
             calc_total_block_count(self),
             evt->block_size);

    state_transition(self, STATE_SEND_CHUNKS);
  } else {
    // This should not happen based on the state machine in the BT Mesh stack.
    // If the event is not received in the expected state then it is ignored
    // and a log message is emitted.
    log_debug(LOG_PREFIX "unexpected Start Block Complete event "
                         "(elem=%d,state=%d)" NL,
              self->elem_index,
              self->state);
  }
}

static void handle_send_chunk_request(blob_transfer_client_t *const self,
                                      const sl_btmesh_evt_mbt_client_send_chunk_request_t *const evt)
{
  if (STATE_SEND_CHUNKS == self->state) {
    self->chunk_requested = true;
    self->current_chunk_offset = evt->offset;
    self->current_chunk_length = evt->length;

    if (false != self->separation_time_elapsed) {
      // The chunk data is transmitted at the first chunk of the block, because
      // separation time is measured between chunks of the same block therefore
      // the first chunk shall be sent in this event handler.
      //
      // If the separation time is zero then the handle_tx_complete sets the
      // separation_time_elapsed flag therefore this event handler sends the
      // chunk immediately.
      send_chunk(self);
    }
  } else {
    // This should not happen based on the state machine in the BT Mesh stack.
    // If the event is not received in the expected state then it is ignored
    // and a log message is emitted.
    log_debug(LOG_PREFIX
              "unexpected Send Chunk Request event (elem=%d,state=%d)" NL,
              self->elem_index,
              self->state);
  }
}

static void handle_send_chunks_complete(blob_transfer_client_t *const self,
                                        const sl_btmesh_evt_mbt_client_send_chunks_complete_t *const evt)
{
  (void)evt;
  if (STATE_SEND_CHUNKS == self->state) {
    state_transition(self, STATE_SEND_BLOCK_QUERY);
  } else {
    // This should not happen based on the state machine in the BT Mesh stack.
    // If the event is not received in the expected state then it is ignored
    // and a log message is emitted.
    log_debug(LOG_PREFIX
              "unexpected Send Chunks Complete event (elem=%d,state=%d)" NL,
              self->elem_index,
              self->state);
  }
}

static void handle_query_block_status_complete(blob_transfer_client_t *const self,
                                               const sl_btmesh_evt_mbt_client_query_block_status_complete_t *const evt)
{
  if (STATE_SEND_BLOCK_QUERY == self->state) {
    uint32_t confirmed_tx_bytes;
    uint16_t completed_block_count = self->current_block_number
                                     + (0 != evt->block_complete);

    if (completed_block_count < calc_total_block_count(self)) {
      confirmed_tx_bytes = completed_block_count
                           * (1UL << self->block_size_log);
    } else {
      confirmed_tx_bytes = self->blob_size;
    }

    log_info(LOG_PREFIX
             "Query Block Status Complete "
             "(elem=%d,blk_done=%d,transfer_done=%d,progress=%u%%)" NL,
             evt->elem_index,
             evt->block_complete,
             evt->transfer_complete,
             (unsigned) (100 * confirmed_tx_bytes / self->blob_size));

    if (0 != evt->transfer_complete) {
      notify_progress(self, self->blob_size);
    } else if (0 != evt->block_complete) {
      notify_progress(self, confirmed_tx_bytes);
      state_transition(self, STATE_SEND_BLOCK_START);
    } else {
      state_transition(self, STATE_SEND_CHUNKS);
    }
  } else {
    // This should not happen based on the state machine in the BT Mesh stack.
    // If the event is not received in the expected state then it is ignored
    // and a log message is emitted.
    log_debug(LOG_PREFIX
              "unexpected Query Block Status Complete event (elem=%d,state=%d)" NL,
              self->elem_index,
              self->state);
  }
}

static void handle_tx_complete(blob_transfer_client_t *const self)
{
  // If the state supports retry, then it shall start the retry timer if the max
  // number of retries is not reached.
  // If the maximum number of retries is reached, then the state machine waits
  // in the current state until the BT Mesh stack drops the nonresponding BLOB
  // servers and continues with the active servers. (BT Mesh stack event)
  if (0 != state_flags[self->state].retry) {
    if (self->retry_counter < self->retry_max) {
      start_retry_timer(self);
    }
  }

  // If multiple consecutive mesh messages need to be sent (send chunks), then
  // the separation time feature makes it possible to introduce a separation
  // time between these messages in order to spare the bandwidth for another
  // nodes
  if (0 != state_flags[self->state].separation) {
    // The separation time is started after the last message as well, because
    // this component is not able to determine which message is the last.
    // For example in case of push mode BLOB transfer the chunks are not sent
    // in order especially when the missing chunks are sent.
    // The timer is started after the last chunk, however it will be stopped by
    // the state exit code when the state transition occurs due to the send
    // chunks complete event. Even if the timer elapses only a flag is set and
    // the send chunk function won't be called because the chunk_requested flag
    // is not set.
    start_separation_timer(self);
  }
}

static void handle_server_failed(blob_transfer_client_t *const self,
                                 const sl_btmesh_evt_mbt_client_server_failed_t *const evt)
{
  if (0 == state_flags[self->state].idle) {
    log_info(LOG_PREFIX
             "Server Failed received (elem=%d,addr=0x%04X,timeout=%d,err=%s)" NL,
             evt->elem_index,
             evt->server_address,
             evt->timeout,
             mbt_status_to_string(evt->error));

    // Send notification to the upper layer about the BLOB Transfer Server failure
    notify_server_failed(self, evt->server_address, evt->timeout, evt->error);
  } else {
    // This should not happen based on the state machine in the BT Mesh stack.
    // If the event is not received in the expected state then it is ignored
    // and a log message is emitted.
    log_debug(LOG_PREFIX
              "unexpected Server Failed event (elem=%d,state=%d)" NL,
              self->elem_index,
              self->state);
  }
}

static void handle_transfer_complete(blob_transfer_client_t *const self)
{
  const uint16_t max_server_count = SL_BTMESH_BLOB_TRANSFER_CLIENT_MAX_SERVERS_CFG_VAL;
  uint16_t server_count = 0, failed_server_count = 0;
  uint16_t server_address = 0, rx_blocks = 0, rx_chunks = 0;
  uint8_t current_procedure_status;
  bool all_server_failed = false;
  sl_status_t sc;

  if (0 == state_flags[self->state].idle) {
    // Iterate over the BLOB transfer servers to check their status
    // The number of servers in the BLOB transfer is not known but the maximum
    // server count is known because that is an initialization parameter of the
    // BT Mesh stack MBT client model. The server count can be determined by
    // checking the return value of sl_btmesh_mbt_client_get_server_status.
    for (uint16_t server_idx = 0; server_idx < max_server_count; server_idx++) {
      sc = sl_btmesh_mbt_client_get_server_status(self->elem_index,
                                                  server_idx,
                                                  &server_address,
                                                  &current_procedure_status,
                                                  &rx_blocks,
                                                  &rx_chunks);
      if (sc == SL_STATUS_OK) {
        sl_btmesh_mbt_client_server_status_t server_status;
        server_status = (sl_btmesh_mbt_client_server_status_t) current_procedure_status;
        server_count++;
        if (server_status == sl_btmesh_mbt_client_server_status_error) {
          failed_server_count++;
        }
      } else if ((sc == SL_STATUS_BT_MESH_DOES_NOT_EXIST) && (server_idx != 0)) {
        // The BT Mesh stack returns SL_STATUS_BT_MESH_DOES_NOT_EXIST when the
        // server index does not exists so it is possible to determine the number
        // of servers by checking this return value.
        // The server with zero index shall exist because a BLOB transfer shall
        // have at least one BLOB transfer server, and consequently the first
        // sl_btmesh_mbt_client_get_server_status BT Mesh stack call can return
        // the SL_STATUS_BT_MESH_DOES_NOT_EXIST return value because of an error.
        break;
      } else {
        // Unexpected error so the BLOB transfer is considered  to be failed
        all_server_failed = true;
        log_status_error_f(sc,
                           LOG_PREFIX "failed to get server status "
                                      "(elem=%d,server_idx=%u)" NL,
                           self->elem_index,
                           server_idx);
        break;
      }
    }

    all_server_failed = (server_count == failed_server_count);

    if (all_server_failed) {
      process_transfer_failed(self);
    } else if (self->state == STATE_CANCELING) {
      notify_transfer_result(self,
                             SL_BTMESH_BLOB_TRANSFER_CLIENT_RESULT_CANCELED);
      state_transition(self, STATE_TRANSFER_CANCELED);
    } else {
      notify_transfer_result(self,
                             SL_BTMESH_BLOB_TRANSFER_CLIENT_RESULT_COMPLETED);
      state_transition(self, STATE_TRANSFER_COMPLETED);
    }
  }
}

static void retry_timer_cb(app_timer_t *timer, void *data)
{
  (void) timer;
  blob_transfer_client_t *const self = data;

  app_assert(NULL != data, "The data is NULL in retry timer callback");

  // Register that the retry timer elapsed which is important in states which
  // support retries because it clears the retry counter only if the state is
  // entered the first time and not as the result of a retry (self transition).
  self->retry_time_elapsed = true;

  // If the retry time elapsed then a self transition is executed in order to
  // run the state actions again. The current state is left and entered again
  // which means the entry and exit functions are called again therefore this
  // implements the retry.
  state_transition(self, self->state);
}

static void separation_timer_cb(app_timer_t *timer, void *data)
{
  (void) timer;
  blob_transfer_client_t *const self = data;

  app_assert(NULL != data, "The data is NULL in retry timer callback");

  self->separation_time_elapsed = true;

  if (false != self->chunk_requested) {
    send_chunk(self);
  }
}

static void send_chunk_request_response(app_timer_t *timer, void *data)
{
  sl_status_t sc;

  blob_transfer_client_t *const self = data;

  sc = sl_btmesh_mbt_client_send_chunk_request_rsp(self->elem_index,
                                                   self->current_chunk_length,
                                                   self->chunk_data_ptr);

  switch (sc) {
    default:
      log_status_error_f(sc,
                         LOG_PREFIX "Send Chunk failed (elem=%d,chunk_len=0x%04X)" NL,
                         self->elem_index,
                         self->current_chunk_length);
      process_transfer_failed(self);
      break;
    case SL_STATUS_BUSY:
    case SL_STATUS_NO_MORE_RESOURCE:
      // In these two cases, start the retry timer with this callback function
      sc = app_timer_start(timer,
                           self->retry_time_ms,
                           send_chunk_request_response,
                           &data,
                           false);
      app_assert_status_f(sc,
                          "Failed to start chunk request response retry timer (elem=%d)",
                          self->elem_index);
      break;
    case SL_STATUS_OK:
      // The chunk request is frequent so it is logged only in debug mode
      log_debug(LOG_PREFIX "Send Chunk (elem=%d,offset=0x%08lX,chunk_len=0x%04X)" NL,
                self->elem_index,
                self->current_chunk_offset,
                self->current_chunk_length);
      break;
  }
}

void sl_btmesh_blob_transfer_client_on_event(const sl_btmesh_msg_t * const evt)
{
  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_btmesh_evt_prov_initialized_id:
    case sl_btmesh_evt_node_provisioned_id: {
      sl_btmesh_blob_transfer_client_init();
      break;
    }
    case sl_btmesh_evt_node_initialized_id: {
      if (0 != evt->data.evt_node_initialized.provisioned) {
        sl_btmesh_blob_transfer_client_init();
      }
      break;
    }
    case sl_btmesh_evt_mbt_client_server_information_status_id: {
      handle_server_information_status(
        &blob_tf_client,
        &evt->data.evt_mbt_client_server_information_status);
      break;
    }
    case sl_btmesh_evt_mbt_client_server_transfer_status_id: {
      handle_server_transfer_status(
        &blob_tf_client,
        &evt->data.evt_mbt_client_server_transfer_status);
      break;
    }
    case sl_btmesh_evt_mbt_client_server_block_status_id: {
      handle_server_block_status(
        &blob_tf_client,
        &evt->data.evt_mbt_client_server_block_status);
      break;
    }
    case sl_btmesh_evt_mbt_client_server_partial_block_report_id: {
      handle_server_partial_block_report(
        &blob_tf_client,
        &evt->data.evt_mbt_client_server_partial_block_report);
      break;
    }
    case sl_btmesh_evt_mbt_client_query_information_complete_id: {
      handle_query_information_complete(
        &blob_tf_client,
        &evt->data.evt_mbt_client_query_information_complete);
      break;
    }
    case sl_btmesh_evt_mbt_client_start_transfer_complete_id: {
      handle_start_transfer_complete(
        &blob_tf_client,
        &evt->data.evt_mbt_client_start_transfer_complete);
      break;
    }
    case sl_btmesh_evt_mbt_client_start_block_complete_id: {
      handle_start_block_complete(
        &blob_tf_client,
        &evt->data.evt_mbt_client_start_block_complete);
      break;
    }
    case sl_btmesh_evt_mbt_client_send_chunk_request_id: {
      handle_send_chunk_request(
        &blob_tf_client,
        &evt->data.evt_mbt_client_send_chunk_request);
      break;
    }
    case sl_btmesh_evt_mbt_client_send_chunks_complete_id: {
      handle_send_chunks_complete(
        &blob_tf_client,
        &evt->data.evt_mbt_client_send_chunks_complete);
      break;
    }
    case sl_btmesh_evt_mbt_client_query_block_status_complete_id: {
      handle_query_block_status_complete(
        &blob_tf_client,
        &evt->data.evt_mbt_client_query_block_status_complete);
      break;
    }
    case sl_btmesh_evt_mbt_client_tx_complete_id: {
      handle_tx_complete(&blob_tf_client);
      break;
    }
    case sl_btmesh_evt_mbt_client_server_failed_id: {
      handle_server_failed(&blob_tf_client,
                           &evt->data.evt_mbt_client_server_failed);
      break;
    }
    case sl_btmesh_evt_mbt_client_transfer_complete_id: {
      handle_transfer_complete(&blob_tf_client);
      break;
    }
  }
}

static void state_transition(blob_transfer_client_t *const self,
                             blob_transfer_client_state_t target_state)
{
  blob_transfer_client_state_flags_t source_state_flags, target_state_flags;

  app_assert_s(target_state < STATE_COUNT);

  source_state_flags = state_flags[self->state];
  target_state_flags = state_flags[target_state];

  // No state can support the separation and retry at the same time because
  // only one app timer data structure is allocated, therefore only one timer
  // can run at any point of time in the BLOB Transfer Client
  app_assert_s((0 == source_state_flags.retry)
               || (0 == source_state_flags.separation));

  // If a state with the retry feature is exited, then the retry timer shall
  // be stopped, even in case of a retry self-transition, because in this case
  // the retry timer is started again by the tx complete event handler
  // Note: it is not considered as an error if a non-running timer is stopped
  //       in the app timer component
  stop_retry_timer(self);

  // If a state with separation feature is exited, then the separation timer
  // shall be stopped
  // Note: it is not considered an error, if a non-running timer is stopped
  //       in the app timer component
  stop_separation_timer(self);

  self->state = target_state;

  if ((0 == source_state_flags.idle)
      && (0 != target_state_flags.idle)) {
    // If any of the idle sub-states are entered from a non-idle state, then
    // the idle entry function is called.
    super_state_idle_entry(self);
  }

  if (0 != target_state_flags.retry) {
    // If a state with retry feature is entered the first time during the
    // transfer and not as a result of a retry self-transition then the retry
    // counter shall be cleared.
    if (false == self->retry_time_elapsed) {
      self->retry_counter = 0;
    } else {
      self->retry_counter++;
      self->retry_time_elapsed = false;
    }
  }

  if (0 != target_state_flags.separation) {
    // It is not necessary to respect the separation time when the first chunk
    // is sent, because the separation time is measured between chunks
    self->separation_time_elapsed = true;
  }

  switch (target_state) {
    case STATE_SEND_QUERY_INFO: {
      state_send_query_info_entry(self);
      break;
    }
    case STATE_SEND_TRANSFER_START: {
      state_send_transfer_start_entry(self);
      break;
    }
    case STATE_SEND_BLOCK_START: {
      state_send_start_block_entry(self);
      break;
    }
    case STATE_SEND_BLOCK_QUERY: {
      state_send_block_query_entry(self);
      break;
    }
    case STATE_CANCELING: {
      state_send_cancel(self);
      break;
    }
    default:
      // Suppress the switch warnings
      break;
  }
}

const char *sl_btmesh_blob_transfer_client_transfer_mode_to_string(sl_btmesh_mbt_client_transfer_mode_t transfer_mode)
{
  switch (transfer_mode) {
    case sl_btmesh_mbt_client_mbt_transfer_mode_none:
      return "None";
    case sl_btmesh_mbt_client_mbt_transfer_mode_push:
      return "Push";
    case sl_btmesh_mbt_client_mbt_transfer_mode_pull:
      return "Pull";
    case sl_btmesh_mbt_client_mbt_transfer_mode_both:
      return "Both";
    default:
      return "INVALID";
  }
}

const char *sl_btmesh_blob_transfer_client_mbt_phase_to_string(sl_btmesh_mbt_server_phase_t mbt_phase)
{
  // The string representation is set based on the latest specification
  switch (mbt_phase) {
    case sl_btmesh_mbt_server_phase_inactive:
      return "Inactive";
    case sl_btmesh_mbt_server_phase_idle:
      return "Wait Start";
    case sl_btmesh_mbt_server_phase_waiting_for_block:
      return "Wait Block";
    case sl_btmesh_mbt_server_phase_waiting_for_chunks:
      return "Wait Chunk";
    case sl_btmesh_mbt_server_phase_complete:
      return "Complete";
    case sl_btmesh_mbt_server_phase_suspended:
      return "Suspended";
    default:
      return "INVALID";
  }
}

const char *sl_btmesh_blob_transfer_client_mbt_status_to_string(sl_btmesh_mbt_server_status_t mbt_status)
{
  switch (mbt_status) {
    case sl_btmesh_mbt_server_status_success:
      return "Success";
    case sl_btmesh_mbt_server_status_invalid_block_number:
      return "Invalid Block Number";
    case sl_btmesh_mbt_server_status_wrong_block_size:
      return "Invalid Block Size";
    case sl_btmesh_mbt_server_status_wrong_chunk_size:
      return "Invalid Chunk Size";
    case sl_btmesh_mbt_server_status_invalid_state:
      return "Wrong Phase";
    case sl_btmesh_mbt_server_status_invalid_parameter:
      return "Invalid Parameter";
    case sl_btmesh_mbt_server_status_wrong_object_id:
      return "Wrong BLOB ID";
    case sl_btmesh_mbt_server_status_storage_limit:
      return "BLOB Too Large";
    case sl_btmesh_mbt_server_status_unsupported_transfer_mode:
      return "Unsupported Transfer Mode";
    case sl_btmesh_mbt_server_status_internal_error:
      return "Internal Error";
    case sl_btmesh_mbt_server_status_information_unavailable:
      return "Information Unavailable";
    case sl_btmesh_mbt_server_status_malformed_message:
      return "Malformed Message";
    case sl_btmesh_mbt_server_status_timeout:
      return "Timeout";
    default:
      return "INVALID";
  }
}

/** @} end blob_transfer_client */
