/***************************************************************************//**
 * @file
 * @brief BLOB Transfer Server application level functionality
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
#include <stdint.h>
#include <stdbool.h>

#include "sl_bt_api.h"
#include "sl_btmesh.h"
#include "sl_btmesh_api.h"
#include "sl_btmesh_dcd.h"
#include "sl_malloc.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT

#include "app_assert.h"

#ifdef SL_CATALOG_APP_LOG_PRESENT
#include "app_log.h"
#endif // SL_CATALOG_APP_LOG_PRESENT

#include "sl_simple_timer.h"

#include "sl_btmesh_blob_storage.h"

#ifdef SL_CATALOG_BTMESH_STACK_LPN_PRESENT
#include "sl_btmesh_lpn.h"
#endif // SL_CATALOG_BTMESH_STACK_LPN_PRESENT

#include "sl_btmesh_blob_transfer_server.h"
#include "sl_btmesh_blob_transfer_server_api.h"
#include "sl_btmesh_blob_transfer_server_config.h"

// Warning! The app_btmesh_util shall be included after the component configuration
// header file in order to provide the component specific logging macro.
#include "app_btmesh_util.h"

/***************************************************************************//**
 * @addtogroup mesh_blob_transfer_server
 * @{
 ******************************************************************************/

/// In high throughput mode the LPN node polls the friend node more frequently
/// to increase the throughput at the expense of power consumption
/// @note LPN high throughput mode can be active only in LPN mode
#define LPN_HIGH_THROUGHPUT_MODE_ACTIVE           \
  SL_BTMESH_BLOB_TRANSFER_SERVER_LPN_MODE_CFG_VAL \
  && SL_BTMESH_BLOB_TRANSFER_SERVER_LPN_HIGH_THROUGHPUT_MODE_CFG_VAL

// Returns the string representation of BLOB ID in a compound literal.
// WARNING! This macro shall be used as a parameter of log calls only due to the
// lifetime of underlying compound literal in APP_BTMESH_UUID_64_TO_STRING.
#define BLOB_ID_TO_STRING(blob_id) APP_BTMESH_UUID_64_TO_STRING(blob_id, ' ', true)

#if SL_BTMESH_BLOB_TRANSFER_SERVER_LPN_POLL_LOGGING_CFG_VAL
#define blob_lpn_poll_log(...) log_debug(__VA_ARGS__)
#else
#define blob_lpn_poll_log(...)
#endif

typedef enum {
  /// The BLOB server is idle
  IDLE,
  /// BLOB server is active
  ACTIVE,
  /*************************************************************************//**
   * @addtogroup activesubstates Active Sub-states
   * @{
   ****************************************************************************/
  /// BLOBs are being erased
  ACTIVE_ERASING,
  /// Invalid BLOBs are being erased
  ACTIVE_ERASING_INVALID,
  /// Unamanged BLOBs are being erased
  ACTIVE_ERASING_UNMANAGED,
  /// Transfer is ongoing
  ACTIVE_TRANSFER,
  /** @} end activesubstates */
  /*************************************************************************//**
   * @addtogroup idlesubstates Idle Sub-states
   * @{
   ****************************************************************************/
  /// The state machine is either initialized or the transfer is canceled
  IDLE_INACTIVE,
  /// The transfer has been completed
  IDLE_DONE
  /** @} end idlesubstates */
} blob_transfer_server_state_t;

struct {
#if LPN_HIGH_THROUGHPUT_MODE_ACTIVE
  /// Handler for the LPN high throughput timer
  sl_btmesh_lpn_high_throughput_timer_t high_throughput_timer;
#endif // LPN_HIGH_THROUGHPUT_MODE_ACTIVE
  /// ID of the BLOB being transferred
  sl_bt_uuid_64_t blob_id;
  /// Size of the BLOB being transferred
  uint32_t blob_size;
  /// Current progress of the current transfer in bytes
  uint32_t progress;
  /// Block size calculated based on the log value received at transfer start
  uint32_t blob_block_size;
  /// Buffer for blocks
  uint8_t * block_buffer;
  /// State of the current transfer
  union {
    struct {
      uint16_t idle : 1; ///< Idle state
      uint16_t inactive : 1; ///< Idle/Inactive state
      uint16_t done : 1; ///< Idle/Done state
      uint16_t active : 1; ///< Active state
      uint16_t suspended : 1; ///< Active/Suspended state
      uint16_t erasing : 1; ///< Active/Erasing state
      uint16_t erasing_invalid : 1; ///< Active/Erasing Invalid state
      uint16_t erasing_unmanaged : 1; ///< Active/Erasing Unmanaged state
      uint16_t transfer : 1; ///< Active/Transfer state
    };
    uint16_t raw; ///< raw data for quick access
  } state;
} blob_transfer_server;

/***************************************************************************//**
 * Handler for state change
 *
 * Takes care of entry actions.
 *
 * @param state State to transfer into
 ******************************************************************************/
static void blob_transfer_server_state_change(blob_transfer_server_state_t state);

void sl_btmesh_blob_transfer_server_init(void)
{
  uint32_t max_blob_size = sl_btmesh_blob_storage_get_max_blob_size();
  if (max_blob_size == 0) {
    log_warning("No available flash for BLOB Transfer. "
                "Consider removing the component." NL);
  } else {
    sl_status_t sc =
      sl_btmesh_mbt_server_init(BTMESH_BLOB_TRANSFER_SERVER_MAIN,
                                SL_BTMESH_BLOB_TRANSFER_SERVER_MIN_BLOCK_SIZE_LOG_CFG_VAL,
                                SL_BTMESH_BLOB_TRANSFER_SERVER_MAX_BLOCK_SIZE_LOG_CFG_VAL,
                                SL_BTMESH_BLOB_TRANSFER_SERVER_MAX_CHUNKS_PER_BLOCK_CFG_VAL,
                                SL_BTMESH_BLOB_TRANSFER_SERVER_MAX_CHUNK_SIZE_CFG_VAL,
                                max_blob_size,
                                SL_BTMESH_BLOB_TRANSFER_SERVER_PUSH_MODE_CFG_VAL
                                | (SL_BTMESH_BLOB_TRANSFER_SERVER_PULL_MODE_CFG_VAL << 1),
                                SL_BTMESH_BLOB_TRANSFER_SERVER_PULL_CHUNK_REQUEST_CNT_CFG_VAL,
                                SL_BTMESH_BLOB_TRANSFER_SERVER_PULL_RETRY_INTERVAL_MS_CFG_VAL,
                                SL_BTMESH_BLOB_TRANSFER_SERVER_PULL_RETRY_CNT_CFG_VAL);
    app_assert_status(sc);

    // Initial state is Idle
    blob_transfer_server_state_change(IDLE);
  }
}

inline sl_status_t sl_btmesh_blob_transfer_server_start(sl_bt_uuid_64_t const *const blob_id,
                                                        const uint16_t timeout_10s,
                                                        const uint8_t ttl)
{
  // This function essentially wraps the call below
  return sl_btmesh_mbt_server_start(BTMESH_BLOB_TRANSFER_SERVER_MAIN,
                                    *blob_id,
                                    timeout_10s,
                                    ttl);
}

sl_status_t sl_btmesh_blob_transfer_server_set_pull_mode_parameters(uint16_t pull_mode_retry_interval_ms,
                                                                    uint16_t pull_mode_retry_count)
{
  // This function essentially wraps the call below
  return sl_btmesh_mbt_server_set_pull_mode_parameters(BTMESH_BLOB_TRANSFER_SERVER_MAIN,
                                                       pull_mode_retry_interval_ms,
                                                       pull_mode_retry_count);
}

void sl_btmesh_blob_transfer_server_on_event(sl_btmesh_msg_t const *evt)
{
  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_btmesh_evt_node_provisioned_id:
      sl_btmesh_blob_transfer_server_init();
      break;
    case sl_btmesh_evt_node_initialized_id:
      if (evt->data.evt_node_initialized.provisioned) {
        sl_btmesh_blob_transfer_server_init();
      }
      break;
    case sl_btmesh_evt_mbt_server_transfer_start_req_id: {
      sl_btmesh_evt_mbt_server_transfer_start_req_t const *msg =
        &evt->data.evt_mbt_server_transfer_start_req;
      // If suspended, there are two cases we can move forward
      if (blob_transfer_server.state.suspended == 1) {
        if (0
            == memcmp(&blob_transfer_server.blob_id,
                      &msg->blob_id,
                      sizeof(sl_bt_uuid_64_t))) {
          // If it's the same blob, resume.
          blob_transfer_server.state.suspended = 0;
          sl_btmesh_mbt_server_transfer_start_rsp(BTMESH_BLOB_TRANSFER_SERVER_MAIN,
                                                  sl_btmesh_mbt_server_status_success);
          return;
        }
        // If it's a different BLOB, treat it as regular start message
      }
      // If BLOB already present ignore
      if (sl_btmesh_blob_storage_is_present(&msg->blob_id)) {
        log_error("BLOB (%s) already present!" NL,
                  BLOB_ID_TO_STRING(&msg->blob_id));
        sl_btmesh_mbt_server_transfer_start_rsp(BTMESH_BLOB_TRANSFER_SERVER_MAIN,
                                                sl_btmesh_mbt_server_status_internal_error);
        return;
      }
      memcpy(&blob_transfer_server.blob_id,
             &msg->blob_id,
             sizeof(sl_bt_uuid_64_t));
      // Set progress target
      blob_transfer_server.blob_size = msg->blob_size;
      // Set expected block size
      blob_transfer_server.blob_block_size = 1 << msg->block_size_log;
      blob_transfer_server.block_buffer =
        sl_malloc(blob_transfer_server.blob_block_size);
      // Check allocation result
      if (blob_transfer_server.block_buffer == NULL) {
        log_critical("Block buffer allocation failed!" NL);
        sl_btmesh_mbt_server_transfer_start_rsp(BTMESH_BLOB_TRANSFER_SERVER_MAIN,
                                                sl_btmesh_mbt_server_status_internal_error);
        // State change
        blob_transfer_server_state_change(IDLE_INACTIVE);
      } else {
        log_info("BLOB Transfer Start received, id: %s\t"
                 "size: %lu B" NL,
                 BLOB_ID_TO_STRING(&blob_transfer_server.blob_id),
                 blob_transfer_server.blob_size);

        // State change
        blob_transfer_server_state_change(ACTIVE);
      }
      break;
    }
    case sl_btmesh_evt_mbt_server_block_start_id: {
      // If not in Active/Transfer state, ignore message
      if (blob_transfer_server.state.transfer == 0) {
        return;
      }
      sl_btmesh_evt_mbt_server_block_start_t const *msg =
        &evt->data.evt_mbt_server_block_start;
      // Check whether received block is related to BLOB being received
      if (memcmp(&msg->blob_id,
                 &blob_transfer_server.blob_id,
                 sizeof(sl_bt_uuid_64_t))
          != 0) {
        return;
      }
      blob_transfer_server.progress = msg->block_number
                                      * blob_transfer_server.blob_block_size;

      log_debug("Block %d start" NL, msg->block_number);
      break;
    }
    case sl_btmesh_evt_mbt_server_block_complete_id: {
      sl_btmesh_evt_mbt_server_block_complete_t const *msg =
        &evt->data.evt_mbt_server_block_complete;
      // If not in Active/Transfer state, ignore message
      if (blob_transfer_server.state.transfer == 0) {
        return;
      }
#if SL_BTMESH_BLOB_TRANSFER_PROGRESS_CALLBACK_CFG_VAL
      // User callback for progress at block end
      sl_btmesh_blob_transfer_server_transfer_progress(&blob_transfer_server.blob_id,
                                                       SL_PROG_TO_PCT(blob_transfer_server.blob_size,
                                                                      blob_transfer_server.progress));
#endif // SL_BTMESH_BLOB_TRANSFER_PROGRESS_CALLBACK_CFG_VAL
      // Calculate offset of block to be received; since the last block can be
      // smaller than the rest, use the size received in Transfer Start to
      // calculate offset
      uint32_t write_offset = blob_transfer_server.blob_block_size
                              * msg->block_number;
      // Write data using wrapper
      sl_status_t sc =
        sl_btmesh_blob_storage_write(write_offset,
                                     msg->block_size,
                                     blob_transfer_server.block_buffer);
      app_assert_status_f(sc, "Storage writing failed!");
      log_info("Block %d complete (%s), progress %u%%" NL,
               msg->block_number,
               BLOB_ID_TO_STRING(&blob_transfer_server.blob_id),
               // Calculate progress in percent
               (unsigned) SL_PROG_TO_PCT_INT(blob_transfer_server.blob_size,
                                             blob_transfer_server.progress));

      if (blob_transfer_server.progress == blob_transfer_server.blob_size) {
        // State change
        blob_transfer_server_state_change(IDLE_DONE);
      }
      break;
    }
#if LPN_HIGH_THROUGHPUT_MODE_ACTIVE
    case sl_btmesh_evt_mbt_server_partial_block_report_tx_complete_id:
    {
      // Start polling after partial block report is sent out, because
      // the next messages are sent out quickly by the client.
      sl_btmesh_lpn_high_throughput_register(&blob_transfer_server.high_throughput_timer,
                                             SL_BTMESH_BLOB_TRANSFER_SERVER_LPN_POLL_DELAY_MS_CFG_VAL,
                                             SL_BTMESH_LPN_HIGH_THROUGHPUT_SLOWING);
      blob_lpn_poll_log("Start slowing poll delay %dms (partial block)" NL,
                        SL_BTMESH_BLOB_TRANSFER_SERVER_LPN_POLL_DELAY_MS_CFG_VAL);
      break;
    }
#endif // LPN_HIGH_THROUGHPUT_MODE_ACTIVE
    case sl_btmesh_evt_mbt_server_state_changed_id: {
      sl_btmesh_evt_mbt_server_state_changed_t const *msg =
        &evt->data.evt_mbt_server_state_changed;
      log_debug("MBT Server state changed to %d" NL, msg->new_state);
      switch (msg->new_state) {
        case sl_btmesh_mbt_server_phase_suspended:
          blob_transfer_server.state.suspended = 1;
          break;
        case sl_btmesh_mbt_server_phase_inactive:
          if (blob_transfer_server.state.idle == 0) {
            log_error("BLOB Transfer (%s) aborted" NL,
                      BLOB_ID_TO_STRING(&blob_transfer_server.blob_id));
            // Notify user that transfer is aborted
            sl_btmesh_blob_transfer_server_transfer_abort(&blob_transfer_server.blob_id);
            blob_transfer_server_state_change(IDLE_INACTIVE);
          }
#if LPN_HIGH_THROUGHPUT_MODE_ACTIVE
        // intentional fall-through
        case sl_btmesh_mbt_server_phase_waiting_for_block:
          // Start poll delay to poll for expected BLOB transfer messages:
          // BLOB Transfer Start, BLOB Block Start
          // Note: sl_btmesh_mbt_server_phase_idle means that the expected BLOB ID
          //       is set but the BLOB Transfer Start message is not received yet
          sl_btmesh_lpn_high_throughput_register(&blob_transfer_server.high_throughput_timer,
                                                 SL_BTMESH_BLOB_TRANSFER_SERVER_LPN_POLL_DELAY_MS_CFG_VAL,
                                                 SL_BTMESH_LPN_HIGH_THROUGHPUT_SLOWING);
          blob_lpn_poll_log("Start slowing poll delay %dms (state change)" NL,
                            SL_BTMESH_BLOB_TRANSFER_SERVER_LPN_POLL_DELAY_MS_CFG_VAL);
#endif // LPN_HIGH_THROUGHPUT_MODE_ACTIVE
          break;
        default:
#if LPN_HIGH_THROUGHPUT_MODE_ACTIVE
          // If the BLOB transfer is no longer active then the LPN high throughput
          // request shall be unregistered.
          sl_btmesh_lpn_high_throughput_unregister(&blob_transfer_server.high_throughput_timer);
#endif // LPN_HIGH_THROUGHPUT_MODE_ACTIVE
          break;
      }
      // sl_btmesh_evt_mbt_server_state_changed_id
      break;
    }
    case sl_btmesh_evt_mbt_server_chunk_id: {
      // If not in Active state, ignore message
      if (blob_transfer_server.state.active == 0) {
        return;
      }
      sl_btmesh_evt_mbt_server_chunk_t const *msg =
        &evt->data.evt_mbt_server_chunk;
      // Increment progress
      blob_transfer_server.progress += msg->data.len;
      // Buffer data according to block offset
      memcpy(&blob_transfer_server.block_buffer[msg->block_offset],
             msg->data.data,
             msg->data.len);
      // Calculate progress in percent
      float prog = SL_PROG_TO_PCT(blob_transfer_server.blob_size,
                                  blob_transfer_server.progress);
      log_debug("BLOB Transfer (%s) %3d.%02d%%" NL,
                BLOB_ID_TO_STRING(&blob_transfer_server.blob_id),
                (int)prog,
                (int)(prog * 100) % 100);
      (void)prog;
      break;
    }
    case sl_btmesh_evt_mbt_server_transfer_cancel_id: {
      if (blob_transfer_server.state.active == 0) {
        return;
      }
      sl_btmesh_evt_mbt_server_transfer_cancel_t const *msg =
        &evt->data.evt_mbt_server_transfer_cancel;
      // Compare ID's
      if (0 == memcmp(&msg->blob_id,
                      &blob_transfer_server.blob_id,
                      sizeof(sl_bt_uuid_64_t))) {
        // State change
        blob_transfer_server_state_change(IDLE_INACTIVE);
        // Log cancellation
        log_info("BLOB Transfer (%s) Canceled" NL,
                 BLOB_ID_TO_STRING(&blob_transfer_server.blob_id));
      }
      break;
    }
    default:
      // empty
      break;
  }
}

static void blob_transfer_server_state_change(blob_transfer_server_state_t state)
{
  // Clear state flags
  blob_transfer_server.state.raw = 0;
  switch (state) {
    case IDLE:
    // Idle has an initial state transition to Idle/Inactive: fall through
    case IDLE_INACTIVE:
      blob_transfer_server.state.idle = 1;
      blob_transfer_server.state.inactive = 1;
      // Set the BLOB ID to Unknown, i.e. 0xFFFFFFFFFFFFFFFF
      memset(&blob_transfer_server.blob_id, UINT8_MAX, sizeof(sl_bt_uuid_64_t));
      // Set BLOB Size to Unknown, i.e. 0xFFFFFFFF
      blob_transfer_server.blob_size = UINT32_MAX;
      // Set progress to Unknown, i.e. 0xFFFFFFFF
      blob_transfer_server.progress = UINT32_MAX;
      sl_free(blob_transfer_server.block_buffer);
      blob_transfer_server.block_buffer = NULL;
      break;
    case IDLE_DONE: {
      blob_transfer_server.state.idle = 1;
      blob_transfer_server.state.done = 1;
      // Log finished transfer
      log_info("BLOB Transfer (%s) Done" NL,
               BLOB_ID_TO_STRING(&blob_transfer_server.blob_id));
      sl_status_t sc = sl_btmesh_blob_storage_verify();
      log_status_critical_f(sc, "BLOB signing failed!" NL);
#if SL_BTMESH_BLOB_TRANSFER_SERVER_TRANSFER_DONE_CALLBACK_CFG_VAL
      // Notify user that transfer has completed
      sl_btmesh_blob_transfer_server_transfer_done(&blob_transfer_server.blob_id);
#endif // SL_BTMESH_BLOB_TRANSFER_SERVER_TRANSFER_DONE_CALLBACK_CFG_VAL
      sl_free(blob_transfer_server.block_buffer);
      break;
    }
    case ACTIVE:
    case ACTIVE_TRANSFER: {
      sl_status_t s;
      blob_transfer_server.state.active = 1;
      // Reset progress
      blob_transfer_server.progress = 0;

      // Notify storage wrapper about write start
      s = sl_btmesh_blob_storage_write_start(&blob_transfer_server.blob_id,
                                             blob_transfer_server.blob_size);

      if (SL_STATUS_NO_MORE_RESOURCE == s) {
        log_info("No more slots available, attempting erase." NL);
        blob_transfer_server_state_change(ACTIVE_ERASING);
        break;
      }

      switch (s) {
        case SL_STATUS_OK:
          sl_btmesh_mbt_server_transfer_start_rsp(BTMESH_BLOB_TRANSFER_SERVER_MAIN,
                                                  sl_btmesh_mbt_server_status_success);
#if SL_BTMESH_BLOB_TRANSFER_START_CALLBACK_CFG_VAL
          // Notify user about transfer start
          sl_btmesh_blob_transfer_server_transfer_start(&blob_transfer_server.blob_id);
#endif // SL_BTMESH_BLOB_TRANSFER_START_CALLBACK_CFG_VAL
          blob_transfer_server.state.transfer = 1;
          break;

        default:
          sl_btmesh_mbt_server_transfer_start_rsp(BTMESH_BLOB_TRANSFER_SERVER_MAIN,
                                                  sl_btmesh_mbt_server_status_internal_error);
          blob_transfer_server_state_change(IDLE_INACTIVE);
          break;
      }
      break;
      case ACTIVE_ERASING:
      case ACTIVE_ERASING_INVALID:
        blob_transfer_server.state.active = 1;
        blob_transfer_server.state.erasing = 1;
        blob_transfer_server.state.erasing_invalid = 1;
        sl_btmesh_blob_storage_delete_invalid_slots_start();
        break;
      case ACTIVE_ERASING_UNMANAGED:
        blob_transfer_server.state.active = 1;
        blob_transfer_server.state.erasing = 1;
        blob_transfer_server.state.erasing_unmanaged = 1;
        sl_btmesh_blob_storage_delete_unmanaged_slots_start();
        break;
    }
  }
}

void sl_btmesh_blob_transfer_server_step_handle(void)
{
  if (1 == blob_transfer_server.state.erasing) {
    switch (sl_btmesh_blob_storage_get_erase_error_code()) {
      case SL_BTMESH_BLOB_STORAGE_DELETE_SUCCESS:
        blob_transfer_server_state_change(ACTIVE_TRANSFER);
        break;
      case SL_BTMESH_BLOB_STORAGE_DELETE_FAILED:
      case SL_BTMESH_BLOB_STORAGE_DELETE_INACTIVE:
        // If the delete failed or the last delete operation didn't find any
        // invalid or unmanaged slot to delete
        if (blob_transfer_server.state.erasing_invalid == 1) {
          blob_transfer_server_state_change(ACTIVE_ERASING_UNMANAGED);
        } else if (blob_transfer_server.state.erasing_unmanaged == 1) {
          sl_btmesh_mbt_server_transfer_start_rsp(BTMESH_BLOB_TRANSFER_SERVER_MAIN,
                                                  sl_btmesh_mbt_server_status_storage_limit);
          blob_transfer_server_state_change(IDLE_INACTIVE);
        }
        break;
      default:
        // empty
        break;
    }
  }
}

/** @} end mesh_blob_transfer_server */
