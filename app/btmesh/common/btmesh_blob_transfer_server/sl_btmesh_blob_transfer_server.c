/***************************************************************************//**
 * @file
 * @brief BLOB Transfer Server application level functionality
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

#include "app_timer.h"

#include "sl_btmesh_blob_storage.h"

#ifdef SL_CATALOG_BTMESH_LPN_PRESENT
#include "sl_btmesh_lpn.h"
#endif // SL_CATALOG_BTMESH_LPN_PRESENT

#include "sl_btmesh_blob_transfer_server.h"
#include "sl_btmesh_blob_transfer_server_api.h"
#include "sl_btmesh_blob_transfer_server_config.h"
#include "sli_btmesh_blob_transfer_server_instances.h"

// Warning! The app_btmesh_util shall be included after the component configuration
// header file in order to provide the component specific logging macro.
#include "app_btmesh_util.h"

/***************************************************************************//**
 * @addtogroup mesh_blob_transfer_server
 * @{
 ******************************************************************************/

// In high throughput mode the LPN node polls the friend node more frequently
// to increase the throughput at the expense of power consumption
// Note: LPN high throughput mode can be active only in LPN mode
#define LPN_HIGH_THROUGHPUT_MODE_ACTIVE \
  SLI_BTMESH_BLOB_TRANSFER_SERVER_LPN_HIGH_THROUGHPUT_MODE_ACTIVE

// Returns the string representation of BLOB ID in a compound literal.
// WARNING! This macro shall be used as a parameter of log calls only due to the
// lifetime of underlying compound literal in APP_BTMESH_UUID_64_TO_STRING.
#define BLOB_ID_TO_STRING(blob_id) APP_BTMESH_UUID_64_TO_STRING(blob_id, ' ', true)

#if SL_BTMESH_BLOB_TRANSFER_SERVER_LPN_POLL_LOGGING_CFG_VAL
#define blob_lpn_poll_log(...) log_debug(__VA_ARGS__)
#else
#define blob_lpn_poll_log(...)
#endif

#define assert_not_null(ptr) do { app_assert_s(ptr != NULL); } while (0)

#define CHECK_PTR(ptr, ...)  do { \
    if (ptr == NULL) {            \
      assert_not_null(ptr);       \
      return __VA_ARGS__;         \
    }                             \
} while (0)

/***************************************************************************//**
 * Handler for state change
 *
 * Takes care of entry actions.
 *
 * @param state State to transfer into
 ******************************************************************************/
static void blob_transfer_server_state_change(sli_btmesh_blob_transfer_server_t *const self,
                                              sli_btmesh_blob_transfer_server_state_t state);

void sl_btmesh_blob_transfer_server_inst_init(sli_btmesh_blob_transfer_server_t *const self,
                                              uint32_t max_blob_size)
{
  sl_status_t sc;
  assert_not_null(self);

  sc = sl_btmesh_mbt_server_init(self->config->elem_index,
                                 self->config->min_block_size_log,
                                 self->config->max_block_size_log,
                                 self->config->max_chunks_per_block,
                                 self->config->max_chunk_size,
                                 max_blob_size,
                                 self->config->supported_transfer_modes,
                                 self->config->pull_mode_chunks_to_request,
                                 self->config->pull_mode_retry_interval_ms,
                                 self->config->pull_mode_retry_count);
  app_assert_status(sc);

  // Initial state is Idle
  blob_transfer_server_state_change(self, SLI_BTMESH_BLOB_TRANSFER_SERVER_IDLE);
}

void sl_btmesh_blob_transfer_server_init(void)
{
  uint32_t max_blob_size = sl_btmesh_blob_storage_get_max_blob_size();
  if (max_blob_size == 0) {
    log_warning("No available flash for BLOB Transfer. "
                "Consider removing the component." NL);
  } else {
    for (uint16_t inst_idx = 0; inst_idx < SLI_BTMESH_BLOB_TRANSFER_SERVER_COUNT; inst_idx++) {
      sli_btmesh_blob_transfer_server_t *const self =
        sli_btmesh_blob_transfer_server_get_by_inst_index(inst_idx);
      sl_btmesh_blob_transfer_server_inst_init(self, max_blob_size);
    }
  }
}

inline sl_status_t sl_btmesh_blob_transfer_server_start(uint16_t elem_index,
                                                        sl_bt_uuid_64_t const *const blob_id,
                                                        const uint16_t timeout_10s,
                                                        const uint8_t ttl)
{
  // This function essentially wraps the call below
  return sl_btmesh_mbt_server_start(elem_index,
                                    *blob_id,
                                    timeout_10s,
                                    ttl);
}

sl_status_t sl_btmesh_blob_transfer_server_set_pull_mode_parameters(uint16_t elem_index,
                                                                    uint16_t pull_mode_retry_interval_ms,
                                                                    uint16_t pull_mode_retry_count)
{
  // This function essentially wraps the call below
  return sl_btmesh_mbt_server_set_pull_mode_parameters(elem_index,
                                                       pull_mode_retry_interval_ms,
                                                       pull_mode_retry_count);
}

void sl_btmesh_blob_transfer_server_on_event(sl_btmesh_msg_t const *evt)
{
  sli_btmesh_blob_transfer_server_t *self = NULL;

  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_btmesh_evt_prov_initialized_id:
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
      self = sli_btmesh_blob_transfer_server_get_by_elem_index(msg->elem_index);
      CHECK_PTR(self);
      // If suspended, there are two cases we can move forward
      if (self->state.suspended == 1) {
        if (0 == memcmp(&self->blob_id, &msg->blob_id, sizeof(sl_bt_uuid_64_t))) {
          // If it's the same blob, resume.
          self->state.suspended = 0;
          sl_btmesh_mbt_server_transfer_start_rsp(self->config->elem_index,
                                                  sl_btmesh_mbt_server_status_success);
          return;
        }
        // If it's a different BLOB, treat it as regular start message
      }
      // If BLOB already present ignore
      if (sl_btmesh_blob_storage_is_present(&msg->blob_id)) {
        log_error("BLOB (%s) already present!" NL,
                  BLOB_ID_TO_STRING(&msg->blob_id));
        sl_btmesh_mbt_server_transfer_start_rsp(self->config->elem_index,
                                                sl_btmesh_mbt_server_status_internal_error);
        return;
      }
      memcpy(&self->blob_id, &msg->blob_id, sizeof(sl_bt_uuid_64_t));
      // Set progress target
      self->blob_size = msg->blob_size;
      // Set expected block size
      self->blob_block_size = 1 << msg->block_size_log;
      self->block_buffer = sl_malloc(self->blob_block_size);
      // Check allocation result
      if (self->block_buffer == NULL) {
        log_critical("Block buffer allocation failed!" NL);
        sl_btmesh_mbt_server_transfer_start_rsp(self->config->elem_index,
                                                sl_btmesh_mbt_server_status_internal_error);
        // State change
        blob_transfer_server_state_change(self, SLI_BTMESH_BLOB_TRANSFER_SERVER_IDLE_INACTIVE);
      } else {
        log_info("BLOB Transfer Start received, id: %s\t"
                 "size: %lu B" NL,
                 BLOB_ID_TO_STRING(&self->blob_id),
                 self->blob_size);

        // State change
        blob_transfer_server_state_change(self, SLI_BTMESH_BLOB_TRANSFER_SERVER_ACTIVE);
      }
      break;
    }
    case sl_btmesh_evt_mbt_server_block_start_id: {
      sl_btmesh_evt_mbt_server_block_start_t const *msg =
        &evt->data.evt_mbt_server_block_start;
      self = sli_btmesh_blob_transfer_server_get_by_elem_index(msg->elem_index);
      CHECK_PTR(self);
      // If not in Active/Transfer state, ignore message
      if (self->state.transfer == 0) {
        return;
      }
      // Check whether received block is related to BLOB being received
      if (memcmp(&msg->blob_id, &self->blob_id, sizeof(sl_bt_uuid_64_t)) != 0) {
        return;
      }
      self->progress = msg->block_number * self->blob_block_size;

      log_debug("Block %d start" NL, msg->block_number);
      break;
    }
    case sl_btmesh_evt_mbt_server_block_complete_id: {
      sl_btmesh_evt_mbt_server_block_complete_t const *msg =
        &evt->data.evt_mbt_server_block_complete;
      self = sli_btmesh_blob_transfer_server_get_by_elem_index(msg->elem_index);
      CHECK_PTR(self);
      // If not in Active/Transfer state, ignore message
      if (self->state.transfer == 0) {
        return;
      }
#if SL_BTMESH_BLOB_TRANSFER_PROGRESS_CALLBACK_CFG_VAL
      // User callback for progress at block end
      sl_btmesh_blob_transfer_server_transfer_progress(&self->blob_id,
                                                       SL_PROG_TO_PCT(self->blob_size,
                                                                      self->progress));
#endif // SL_BTMESH_BLOB_TRANSFER_PROGRESS_CALLBACK_CFG_VAL
      // Calculate offset of block to be received; since the last block can be
      // smaller than the rest, use the size received in Transfer Start to
      // calculate offset
      uint32_t write_offset = self->blob_block_size * msg->block_number;
      // Write data using wrapper
      sl_status_t sc = sl_btmesh_blob_storage_write(write_offset,
                                                    msg->block_size,
                                                    self->block_buffer);
      app_assert_status_f(sc, "Storage writing failed!");
      log_info("Block %d complete (%s), progress %u%%" NL,
               msg->block_number,
               BLOB_ID_TO_STRING(&self->blob_id),
               // Calculate progress in percent
               (unsigned) SL_PROG_TO_PCT_INT(self->blob_size,
                                             self->progress));

      if (self->progress == self->blob_size) {
        // State change
        blob_transfer_server_state_change(self, SLI_BTMESH_BLOB_TRANSFER_SERVER_IDLE_DONE);
      }
      break;
    }
#if LPN_HIGH_THROUGHPUT_MODE_ACTIVE
    case sl_btmesh_evt_mbt_server_partial_block_report_tx_complete_id: {
      sl_btmesh_evt_mbt_server_partial_block_report_tx_complete_t const *msg =
        &evt->data.evt_mbt_server_partial_block_report_tx_complete;
      self = sli_btmesh_blob_transfer_server_get_by_elem_index(msg->elem_index);
      CHECK_PTR(self);
      if (self->config->high_throughput_timer != NULL) {
        // Start polling after partial block report is sent out, because
        // the next messages are sent out quickly by the client.
        sl_btmesh_lpn_high_throughput_register(self->config->high_throughput_timer,
                                               self->config->lpn_poll_delay_ms,
                                               SL_BTMESH_LPN_HIGH_THROUGHPUT_SLOWING);
        blob_lpn_poll_log("Start slowing poll delay %dms (partial block)" NL,
                          self->config->lpn_poll_delay_ms);
      }
      break;
    }
#endif // LPN_HIGH_THROUGHPUT_MODE_ACTIVE
    case sl_btmesh_evt_mbt_server_state_changed_id: {
      sl_btmesh_evt_mbt_server_state_changed_t const *msg =
        &evt->data.evt_mbt_server_state_changed;
      self = sli_btmesh_blob_transfer_server_get_by_elem_index(msg->elem_index);
      CHECK_PTR(self);
      log_debug("MBT Server state changed to %d" NL, msg->new_state);
      switch (msg->new_state) {
        case sl_btmesh_mbt_server_phase_suspended:
          self->state.suspended = 1;
          break;
        case sl_btmesh_mbt_server_phase_inactive:
          if (self->state.idle == 0) {
            log_error("BLOB Transfer (%s) aborted" NL,
                      BLOB_ID_TO_STRING(&self->blob_id));
            // Notify user that transfer is aborted
            sl_btmesh_blob_transfer_server_transfer_abort(&self->blob_id);
            blob_transfer_server_state_change(self, SLI_BTMESH_BLOB_TRANSFER_SERVER_IDLE_INACTIVE);
          }
#if LPN_HIGH_THROUGHPUT_MODE_ACTIVE
        // intentional fall-through
        case sl_btmesh_mbt_server_phase_waiting_for_block:
          // Start poll delay to poll for expected BLOB transfer messages:
          // BLOB Transfer Start, BLOB Block Start
          // Note: sl_btmesh_mbt_server_phase_idle means that the expected BLOB ID
          //       is set but the BLOB Transfer Start message is not received yet
          if (self->config->high_throughput_timer != NULL) {
            sl_btmesh_lpn_high_throughput_register(self->config->high_throughput_timer,
                                                   self->config->lpn_poll_delay_ms,
                                                   SL_BTMESH_LPN_HIGH_THROUGHPUT_SLOWING);
            blob_lpn_poll_log("Start slowing poll delay %dms (state change)" NL,
                              self->config->lpn_poll_delay_ms);
          }
#endif // LPN_HIGH_THROUGHPUT_MODE_ACTIVE
          break;
        default:
#if LPN_HIGH_THROUGHPUT_MODE_ACTIVE
          // If the BLOB transfer is no longer active then the LPN high throughput
          // request shall be unregistered.
          if (self->config->high_throughput_timer != NULL) {
            sl_btmesh_lpn_high_throughput_unregister(self->config->high_throughput_timer);
          }
#endif // LPN_HIGH_THROUGHPUT_MODE_ACTIVE
          break;
      }
      // sl_btmesh_evt_mbt_server_state_changed_id
      break;
    }
    case sl_btmesh_evt_mbt_server_chunk_id: {
      sl_btmesh_evt_mbt_server_chunk_t const *msg = &evt->data.evt_mbt_server_chunk;
      self = sli_btmesh_blob_transfer_server_get_by_elem_index(msg->elem_index);
      CHECK_PTR(self);
      // If not in Active state, ignore message
      if (self->state.active == 0) {
        return;
      }
      // Increment progress
      self->progress += msg->data.len;
      // Buffer data according to block offset
      memcpy(&self->block_buffer[msg->block_offset],
             msg->data.data,
             msg->data.len);
      // Calculate progress in percent
      float prog = SL_PROG_TO_PCT(self->blob_size, self->progress);
      log_debug("BLOB Transfer (%s) %3d.%02d%%" NL,
                BLOB_ID_TO_STRING(&self->blob_id),
                (int)prog,
                (int)(prog * 100) % 100);
      (void)prog;
      break;
    }
    case sl_btmesh_evt_mbt_server_transfer_cancel_id: {
      sl_btmesh_evt_mbt_server_transfer_cancel_t const *msg =
        &evt->data.evt_mbt_server_transfer_cancel;
      self = sli_btmesh_blob_transfer_server_get_by_elem_index(msg->elem_index);
      CHECK_PTR(self);
      if (self->state.active == 0) {
        return;
      }
      // Compare ID's
      if (0 == memcmp(&msg->blob_id,
                      &self->blob_id,
                      sizeof(sl_bt_uuid_64_t))) {
        // State change
        blob_transfer_server_state_change(self, SLI_BTMESH_BLOB_TRANSFER_SERVER_IDLE_INACTIVE);
        // Log cancellation
        log_info("BLOB Transfer (%s) Canceled" NL,
                 BLOB_ID_TO_STRING(&self->blob_id));
      }
      break;
    }
    default:
      // empty
      break;
  }
}

static void blob_transfer_server_state_change(sli_btmesh_blob_transfer_server_t *const self,
                                              sli_btmesh_blob_transfer_server_state_t state)
{
  // Clear state flags
  self->state.raw = 0;
  switch (state) {
    case SLI_BTMESH_BLOB_TRANSFER_SERVER_IDLE:
    // Idle has an initial state transition to Idle/Inactive: fall through
    case SLI_BTMESH_BLOB_TRANSFER_SERVER_IDLE_INACTIVE:
      self->state.idle = 1;
      self->state.inactive = 1;
      // Set the BLOB ID to Unknown, i.e. 0xFFFFFFFFFFFFFFFF
      memset(&self->blob_id, UINT8_MAX, sizeof(sl_bt_uuid_64_t));
      // Set BLOB Size to Unknown, i.e. 0xFFFFFFFF
      self->blob_size = UINT32_MAX;
      // Set progress to Unknown, i.e. 0xFFFFFFFF
      self->progress = UINT32_MAX;
      sl_free(self->block_buffer);
      self->block_buffer = NULL;
      break;
    case SLI_BTMESH_BLOB_TRANSFER_SERVER_IDLE_DONE: {
      self->state.idle = 1;
      self->state.done = 1;
      // Log finished transfer
      log_info("BLOB Transfer (%s) Done" NL,
               BLOB_ID_TO_STRING(&self->blob_id));
      sl_status_t sc = sl_btmesh_blob_storage_verify();
      log_status_critical_f(sc, "BLOB signing failed!" NL);
#if SL_BTMESH_BLOB_TRANSFER_SERVER_TRANSFER_DONE_CALLBACK_CFG_VAL
      // Notify user that transfer has completed
      sl_btmesh_blob_transfer_server_transfer_done(&self->blob_id);
#endif // SL_BTMESH_BLOB_TRANSFER_SERVER_TRANSFER_DONE_CALLBACK_CFG_VAL
      sl_free(self->block_buffer);
      break;
    }
    case SLI_BTMESH_BLOB_TRANSFER_SERVER_ACTIVE:
    case SLI_BTMESH_BLOB_TRANSFER_SERVER_ACTIVE_TRANSFER: {
      sl_status_t s;
      self->state.active = 1;
      // Reset progress
      self->progress = 0;

      // Notify storage wrapper about write start
      s = sl_btmesh_blob_storage_write_start(&self->blob_id,
                                             self->blob_size);

      if (SL_STATUS_NO_MORE_RESOURCE == s) {
        log_info("No more slots available, attempting erase." NL);
        blob_transfer_server_state_change(self, SLI_BTMESH_BLOB_TRANSFER_SERVER_ACTIVE_ERASING);
        break;
      }

      switch (s) {
        case SL_STATUS_OK:
          sl_btmesh_mbt_server_transfer_start_rsp(self->config->elem_index,
                                                  sl_btmesh_mbt_server_status_success);
#if SL_BTMESH_BLOB_TRANSFER_START_CALLBACK_CFG_VAL
          // Notify user about transfer start
          sl_btmesh_blob_transfer_server_transfer_start(&self->blob_id);
#endif // SL_BTMESH_BLOB_TRANSFER_START_CALLBACK_CFG_VAL
          self->state.transfer = 1;
          break;

        default:
          sl_btmesh_mbt_server_transfer_start_rsp(self->config->elem_index,
                                                  sl_btmesh_mbt_server_status_internal_error);
          blob_transfer_server_state_change(self, SLI_BTMESH_BLOB_TRANSFER_SERVER_IDLE_INACTIVE);
          break;
      }
      break;
      case SLI_BTMESH_BLOB_TRANSFER_SERVER_ACTIVE_ERASING:
      case SLI_BTMESH_BLOB_TRANSFER_SERVER_ACTIVE_ERASING_INVALID:
        self->state.active = 1;
        self->state.erasing = 1;
        self->state.erasing_invalid = 1;
        sl_btmesh_blob_storage_delete_invalid_slots_start();
        break;
      case SLI_BTMESH_BLOB_TRANSFER_SERVER_ACTIVE_ERASING_UNMANAGED:
        self->state.active = 1;
        self->state.erasing = 1;
        self->state.erasing_unmanaged = 1;
        sl_btmesh_blob_storage_delete_unmanaged_slots_start();
        break;
    }
  }
}

void sl_btmesh_blob_transfer_server_step_handle(void)
{
  for (uint16_t inst_idx = 0; inst_idx < SLI_BTMESH_BLOB_TRANSFER_SERVER_COUNT; inst_idx++) {
    sli_btmesh_blob_transfer_server_t *const self =
      sli_btmesh_blob_transfer_server_get_by_inst_index(inst_idx);
    assert_not_null(self);

    if (1 == self->state.erasing) {
      switch (sl_btmesh_blob_storage_get_erase_error_code()) {
        case SL_BTMESH_BLOB_STORAGE_DELETE_SUCCESS:
          blob_transfer_server_state_change(self, SLI_BTMESH_BLOB_TRANSFER_SERVER_ACTIVE_TRANSFER);
          break;
        case SL_BTMESH_BLOB_STORAGE_DELETE_FAILED:
        case SL_BTMESH_BLOB_STORAGE_DELETE_INACTIVE:
          // If the delete failed or the last delete operation didn't find any
          // invalid or unmanaged slot to delete
          if (self->state.erasing_invalid == 1) {
            blob_transfer_server_state_change(self, SLI_BTMESH_BLOB_TRANSFER_SERVER_ACTIVE_ERASING_UNMANAGED);
          } else if (self->state.erasing_unmanaged == 1) {
            sl_btmesh_mbt_server_transfer_start_rsp(self->config->elem_index,
                                                    sl_btmesh_mbt_server_status_storage_limit);
            blob_transfer_server_state_change(self, SLI_BTMESH_BLOB_TRANSFER_SERVER_IDLE_INACTIVE);
          }
          break;
        default:
          // empty
          break;
      }
    }
  }
}

/** @} end mesh_blob_transfer_server */
