/***************************************************************************//**
 * @file
 * @brief Definitions of Firmware Update Server functionality
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
#include "sl_component_catalog.h"

#include "sl_btmesh.h"
#include "sl_btmesh_dcd.h"

#include "sl_bt_api.h"
#include "sl_btmesh_api.h"

#ifdef SL_CATALOG_APP_LOG_PRESENT
#include "app_log.h"
#endif // SL_CATALOG_log_PRESENT

#ifdef SL_CATALOG_APP_ASSERT_PRESENT
#include "app_assert.h"
#endif // SL_CATALOG_APP_ASSERT_PRESENT

#include "app_timer.h"

#ifdef SL_CATALOG_BTMESH_STACK_FW_DISTRIBUTION_SERVER_PRESENT
#include "sli_btmesh_fw_distribution_server.h"
#endif // SL_CATALOG_BTMESH_STACK_FW_DISTRIBUTION_SERVER_PRESENT

#include "sl_btmesh_blob_storage.h"
#include "sl_btmesh_blob_storage_app_id.h"

#include "sl_btmesh_firmware_update_server.h"
#include "sl_btmesh_firmware_update_server_api.h"
#include "sl_btmesh_firmware_update_server_config.h"

// Warning! The app_btmesh_util shall be included after the component configuration
// header file in order to provide the component specific logging macro.
#include "app_btmesh_util.h"

/***************************************************************************//**
 * @addtogroup mesh_fw_update_server
 * @{
 ******************************************************************************/

/// Returns the string representation of BLOB ID in a compound literal.
/// WARNING! This macro shall be used as a parameter of log calls only due to the
/// lifetime of underlying compound literal in APP_BTMESH_UUID_64_TO_STRING.
#define BLOB_ID_TO_STRING(blob_id) APP_BTMESH_UUID_64_TO_STRING(blob_id, ' ', true)

/// Storage for internal state variables
static struct {
  union {
    /// State flags
    struct {
      /// Idle state
      uint16_t idle : 1;
      /// Idle/Inactive state
      uint16_t inactive : 1;
      /// Idle/Failed state
      uint16_t failed : 1;
      /// Idle/Failed/Transfer Failed state
      uint16_t transfer_failed : 1;
      /// Idle/Failed/Verification Failed state
      uint16_t verification_failed : 1;
      /// Active state
      uint16_t active : 1;
      /// Active/Transfer state
      uint16_t transfer : 1;
      /// Active/Verification state
      uint16_t verification : 1;
      /// Verification Successful state
      uint16_t verification_success : 1;
    };
    uint16_t raw;
  } state;
  /// Current status of verification (used in Active/Verification)
  sl_btmesh_fw_update_server_verify_state_t verification_status;
  /// Chunk storage for verification steps
  uint8_t * verification_chunk_buffer;
  /// Size of the chunks for verification
  uint32_t verification_chunk_size;
  /// Size of the BLOB being verified
  uint32_t verification_size;
  /// Current progress of verification
  uint32_t verification_progress;
  /// Verification log timer
  app_timer_t verify_timer;
  /// BLOB identifier being transferred
  sl_bt_uuid_64_t blob_id;

  union {
    /// Metadata check state machine state flags
    struct {
      /// Idle state flag
      uint8_t idle : 1;
      /// Active state flag
      uint8_t active : 1;
      /// Indicates that Update Start triggered the metadata check
      uint8_t start_response : 1;
    };
    uint8_t raw;
  } metadata_check_state;
  /// Used for distributor to indicate self update
  bool self_update;
  /// Current status of metadata check (used in Active)
  sl_btmesh_fw_update_server_metadata_check_state_t metadata_check_status;
  PACKSTRUCT(struct {
    /// Firmware index of metadata being checked
    uint8_t metadata_fw_index;
    /// Metadata buffer
    uint8_t metadata[SL_BTMESH_FW_UPDATE_SERVER_METADATA_LENGTH_CFG_VAL];
  })
  ;
  /// Length of metadata
  uint8_t metadata_len;
  /// Metadata check response Additional Information
  sl_btmesh_fw_update_server_additional_information_t additional_information;
} firmware_update_server;

typedef enum {
  /// Idle
  IDLE,
  /// Idle/Inactive
  IDLE_INACTIVE,
  /// Idle/Failed/Transfer Failed
  IDLE_FAILED_TRANSFER_FAILED,
  /// Idle/Failed/Verification Failed
  IDLE_FAILED_VERIFICATION_FAILED,
  /// Idle/Suspended
  IDLE_SUSPENDED,
  /// Active/Transfer
  ACTIVE_TRANSFER,
  /// Active/Verification
  ACTIVE_VERIFICATION,
  /// Verification Success
  VERIFICATION_SUCCESS,

  /// Metadata check Idle
  METADATA_IDLE,
  /// Metadata check Active
  METADATA_ACTIVE
} btmesh_firmware_udpate_state_t;

/***************************************************************************//**
 * Transitions state machine to a state with handling entry actions
 *
 * @param[in] state State to transition into
 ******************************************************************************/
static void btmesh_firmware_udpate_server_change_state(btmesh_firmware_udpate_state_t state);

/***************************************************************************//**
 * Logs verification progress
 *
 * @note Inputs are not used.
 *
 * @param[in] timer Timer structure
 * @param[in] data Callback data
 ******************************************************************************/
static void btmesh_firmware_update_server_verify_progress_ui_update(app_timer_t *timer,
                                                                    void *data);

void sl_btmesh_firmware_update_server_init(void)
{
  sl_btmesh_fw_update_server_init(BTMESH_FIRMWARE_UPDATE_SERVER_GROUP_MAIN_ELEM_INDEX,
                                  SL_BTMESH_FW_UPDATE_SERVER_NUM_OF_FW_CFG_VAL,
                                  SL_BTMESH_FW_UPDATE_SERVER_METADATA_LENGTH_CFG_VAL);

  // Initial state is Idle
  btmesh_firmware_udpate_server_change_state(IDLE);
  firmware_update_server.metadata_check_state.raw = 0;
  firmware_update_server.metadata_check_state.idle = 1;
}

void sl_btmesh_firmware_update_server_on_event(sl_btmesh_msg_t *evt)
{
  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_btmesh_evt_prov_initialized_id:
    case sl_btmesh_evt_node_provisioned_id:
      sl_btmesh_firmware_update_server_init();
      break;
    case sl_btmesh_evt_node_initialized_id:
      if (evt->data.evt_node_initialized.provisioned) {
        sl_btmesh_firmware_update_server_init();
      }
      break;
    case sl_btmesh_evt_fw_update_server_check_fw_metadata_req_id: {
      sl_btmesh_evt_fw_update_server_check_fw_metadata_req_t *msg =
        &evt->data.evt_fw_update_server_check_fw_metadata_req;
      log_debug("Received Metadata Check request." NL);
      // Save FW index from message
      firmware_update_server.metadata_fw_index = msg->fw_index;
      firmware_update_server.metadata_len = msg->metadata.len;
      firmware_update_server.metadata_check_state.start_response = 0;
      memcpy(firmware_update_server.metadata,
             msg->metadata.data,
             firmware_update_server.metadata_len);
      btmesh_firmware_udpate_server_change_state(METADATA_ACTIVE);
      break;
    }
    case sl_btmesh_evt_fw_update_server_update_start_req_id: {
      if (0 == firmware_update_server.state.idle) {
        return;
      }
      sl_btmesh_evt_fw_update_server_update_start_req_t *msg =
        &evt->data.evt_fw_update_server_update_start_req;

      // Store BLOB ID of incoming firmware
      memcpy(&firmware_update_server.blob_id,
             &msg->blob_id,
             sizeof(sl_bt_uuid_64_t));

      log_info("Update Start (BLOB ID: %s)" NL,
               BLOB_ID_TO_STRING(&firmware_update_server.blob_id));

      firmware_update_server.metadata_len = msg->metadata.len;
      firmware_update_server.metadata_fw_index = msg->fw_index;
      firmware_update_server.metadata_check_state.start_response = 1;

      // Store received metadata
      memcpy(firmware_update_server.metadata,
             msg->metadata.data,
             firmware_update_server.metadata_len);
      btmesh_firmware_udpate_server_change_state(METADATA_ACTIVE);
      break;
    }
    case sl_btmesh_evt_mbt_server_state_changed_id: {
      if (0 == firmware_update_server.state.transfer) {
        return;
      }
      sl_btmesh_evt_mbt_server_state_changed_t *msg =
        &evt->data.evt_mbt_server_state_changed;
      // timed out
      switch (msg->new_state) {
        case sl_btmesh_mbt_server_phase_suspended:
          if (firmware_update_server.state.active == 1
              && firmware_update_server.state.transfer == 1) {
            btmesh_firmware_udpate_server_change_state(IDLE_SUSPENDED);
          }
          break;
        case sl_btmesh_mbt_server_phase_inactive:
          if (firmware_update_server.state.idle == 0) {
            // If the MBT server goes inactive, and FW Update is not idle, it
            // must've been an MBT abort, meaning update is aborted.
            // Notify user about update abort
            sl_btmesh_fw_update_server_update_aborted();
            log_error("Firmware Update aborted due BLOB Transfer is abort" NL);
          }
          btmesh_firmware_udpate_server_change_state(IDLE_INACTIVE);
          break;
      }
      // sl_btmesh_evt_mbt_server_state_changed_id
      break;
    }
    case sl_btmesh_evt_fw_update_server_update_cancelled_id:
      if (0 == firmware_update_server.state.active) {
        return;
      }
      log_info("Firmware Update Canceled" NL);
      // Notify user about update cancelation
      sl_btmesh_fw_update_server_update_canceled();
      btmesh_firmware_udpate_server_change_state(IDLE_INACTIVE);
      break;
    case sl_btmesh_evt_fw_update_server_verify_fw_req_id: {
      if (0 == firmware_update_server.state.transfer && !firmware_update_server.self_update) {
        return;
      }
      btmesh_firmware_udpate_server_change_state(ACTIVE_VERIFICATION);
      break;
    }
    case sl_btmesh_evt_fw_update_server_apply_id:
      if (0 == firmware_update_server.state.verification_success) {
        return;
      }
      log_info("Applying Firmware." NL);
      // User callback for FW apply
      sl_btmesh_fw_update_server_apply();
      break;
    case sl_btmesh_evt_fw_update_server_distributor_self_update_req_id:
      if (0 == firmware_update_server.state.idle) {
        return;
      } else {
#ifdef SL_CATALOG_BTMESH_STACK_FW_DISTRIBUTION_SERVER_PRESENT
        mesh_dfu_dist_server_fw_info_t info;
        sl_btmesh_evt_fw_update_server_distributor_self_update_req_t *msg =
          &evt->data.evt_fw_update_server_distributor_self_update_req;
        sl_status_t sc = sli_btmesh_fw_dist_server_get_fw_by_index(
          BTMESH_FIRMWARE_UPDATE_SERVER_GROUP_MAIN_ELEM_INDEX,
          msg->fw_index,
          &info);
        if (SL_STATUS_OK != sc) {
          sl_btmesh_fw_update_server_distributor_self_update_rsp(
            BTMESH_FIRMWARE_UPDATE_SERVER_GROUP_MAIN_ELEM_INDEX,
            sl_btmesh_fw_update_server_update_start_response_type_reject_internal_error,
            (uint8_t)firmware_update_server.additional_information);
        } else {
          memcpy(&firmware_update_server.blob_id,
                 info.p_blob_id,
                 sizeof(sl_bt_uuid_64_t));
          memcpy(firmware_update_server.metadata,
                 info.p_metadata,
                 info.metadata_len);
          firmware_update_server.self_update = true;
          btmesh_firmware_udpate_server_change_state(METADATA_ACTIVE);
        }
#else // SL_CATALOG_BTMESH_STACK_FW_DISTRIBUTION_SERVER_PRESENT
        sl_btmesh_fw_update_server_distributor_self_update_rsp(
          BTMESH_FIRMWARE_UPDATE_SERVER_GROUP_MAIN_ELEM_INDEX,
          sl_btmesh_fw_update_server_update_start_response_type_reject_internal_error,
          (uint8_t)firmware_update_server.additional_information);
#endif
      }
      break;
    default:
      // empty
      break;
  }
}

void sl_btmesh_firmware_update_server_verify_step_handle(void)
{
  if (1 == firmware_update_server.state.verification) {
    switch (firmware_update_server.verification_status) {
      case BTMESH_FW_UPDATE_SERVER_VERIFY_SUCCESS:
        // In case of success, accept firmware
        sl_btmesh_fw_update_server_verify_fw_rsp(BTMESH_FIRMWARE_UPDATE_SERVER_GROUP_MAIN_ELEM_INDEX,
                                                 !0);
        app_timer_stop(&firmware_update_server.verify_timer);
#if FW_UPDATE_SERVER_VERIFY_PROGRESS_UI_UPDATE_PERIOD > 0
        btmesh_firmware_update_server_verify_progress_ui_update(NULL, NULL);
#endif // FW_UPDATE_SERVER_VERIFY_PROGRESS_UI_UPDATE_PERIOD > 0
        btmesh_firmware_udpate_server_change_state(VERIFICATION_SUCCESS);
        break;
      case BTMESH_FW_UPDATE_SERVER_VERIFY_ERROR:
        // In case of error, reject firmware
        sl_btmesh_fw_update_server_verify_fw_rsp(BTMESH_FIRMWARE_UPDATE_SERVER_GROUP_MAIN_ELEM_INDEX,
                                                 0);
        app_timer_stop(&firmware_update_server.verify_timer);
#if FW_UPDATE_SERVER_VERIFY_PROGRESS_UI_UPDATE_PERIOD > 0
        btmesh_firmware_update_server_verify_progress_ui_update(NULL, NULL);
#endif // FW_UPDATE_SERVER_VERIFY_PROGRESS_UI_UPDATE_PERIOD > 0
        btmesh_firmware_udpate_server_change_state(IDLE_FAILED_VERIFICATION_FAILED);
        break;
      case BTMESH_FW_UPDATE_SERVER_VERIFY_PENDING:
        if (NULL != firmware_update_server.verification_chunk_buffer) {
          // Read out data from flash to pass to user callback
          //
          // In the default implementation this data is not used. However, this
          // way the user has the opportunity to implement their own verification.
          sl_btmesh_blob_storage_read(&firmware_update_server.blob_id,
                                      firmware_update_server.verification_progress,
                                      &firmware_update_server.verification_chunk_size,
                                      firmware_update_server.verification_chunk_buffer);
        }
        // If pending, call step
        firmware_update_server.verification_status =
          sl_btmesh_fw_update_server_verify_step(firmware_update_server.verification_chunk_buffer,
                                                 firmware_update_server.verification_chunk_size);
        firmware_update_server.verification_progress +=
          firmware_update_server.verification_chunk_size;
#if SL_BTMESH_FW_UPDATE_SERVER_VERIFY_PROGRESS_UI_UPDATE_PERIOD_CFG_VAL == 0
        btmesh_firmware_update_server_verify_progress_ui_update(NULL, NULL);
#endif // SL_BTMESH_FW_UPDATE_SERVER_VERIFY_PROGRESS_UI_UPDATE_PERIOD_CFG_VAL == 0
        break;
    }
  }
}

void sl_btmesh_firmware_update_server_metadata_check_step_handle(void)
{
  if (1 == firmware_update_server.metadata_check_state.active) {
    switch (firmware_update_server.metadata_check_status) {
      case BTMESH_FW_UPDATE_SERVER_METADATA_CHECK_SUCCESS:
        log_info("Metadata check successful" NL);

        // In case of success, accept metadata
        if (firmware_update_server.self_update) {
          sl_btmesh_fw_update_server_distributor_self_update_rsp(
            BTMESH_FIRMWARE_UPDATE_SERVER_GROUP_MAIN_ELEM_INDEX,
            sl_btmesh_fw_update_server_update_start_response_type_accept,
            (uint8_t)firmware_update_server.additional_information);
        } else if (1 == firmware_update_server.metadata_check_state.start_response) {
          sl_bt_uuid_64_t blob_id;

          // SL_STATUS_OK indicates, that the exact footer has been found
          // blob_id is used as dummy storage
          sl_status_t metadata_footer_check =
            sl_btmesh_blob_storage_get_blob_id_by_footer(
              BLOB_STORAGE_APP_ID_DFU_METADATA,
              &firmware_update_server.metadata_fw_index,
              firmware_update_server.metadata_len + 1,
              &blob_id);

          if (metadata_footer_check == SL_STATUS_OK) {
            // Set the BLOB ID to the one stored, so it identifies the already
            // stored image
            memcpy(&firmware_update_server.blob_id,
                   &blob_id,
                   sizeof(sl_bt_uuid_64_t));
          }

          sl_btmesh_fw_update_server_update_start_response_type_t response =
            (metadata_footer_check == SL_STATUS_OK)
            ? sl_btmesh_fw_update_server_update_start_response_type_fw_already_exists
            : sl_btmesh_fw_update_server_update_start_response_type_accept;

          sl_btmesh_fw_update_server_update_start_rsp(
            BTMESH_FIRMWARE_UPDATE_SERVER_GROUP_MAIN_ELEM_INDEX,
            (uint8_t)response,
            (uint8_t)firmware_update_server.additional_information);
          btmesh_firmware_udpate_server_change_state(
            (metadata_footer_check == SL_STATUS_OK)
            ? ACTIVE_VERIFICATION
            : ACTIVE_TRANSFER);
        } else {
          sl_btmesh_fw_update_server_check_fw_metadata_rsp(
            BTMESH_FIRMWARE_UPDATE_SERVER_GROUP_MAIN_ELEM_INDEX,
            sl_btmesh_fw_update_server_update_start_response_type_accept,
            (uint8_t)firmware_update_server.additional_information,
            firmware_update_server.metadata_fw_index);
        }
        // Notify user about update starting
        sl_btmesh_fw_update_server_update_start(&firmware_update_server.blob_id);
        // Switch to Idle state
        btmesh_firmware_udpate_server_change_state(METADATA_IDLE);
        break;
      case BTMESH_FW_UPDATE_SERVER_METADATA_CHECK_ERROR:
        log_error("Metadata check error" NL);
        // In case of error, reject metadata
        if (firmware_update_server.self_update) {
          sl_btmesh_fw_update_server_distributor_self_update_rsp(
            BTMESH_FIRMWARE_UPDATE_SERVER_GROUP_MAIN_ELEM_INDEX,
            sl_btmesh_fw_update_server_update_start_response_type_reject_metadata_check_failed,
            (uint8_t)firmware_update_server.additional_information);
        } else if (1 == firmware_update_server.metadata_check_state.start_response) {
          sl_btmesh_fw_update_server_update_start_rsp(
            BTMESH_FIRMWARE_UPDATE_SERVER_GROUP_MAIN_ELEM_INDEX,
            sl_btmesh_fw_update_server_update_start_response_type_reject_metadata_check_failed,
            (uint8_t)firmware_update_server.additional_information);
        } else {
          sl_btmesh_fw_update_server_check_fw_metadata_rsp(
            BTMESH_FIRMWARE_UPDATE_SERVER_GROUP_MAIN_ELEM_INDEX,
            sl_btmesh_fw_update_server_update_start_response_type_reject_metadata_check_failed,
            (uint8_t)firmware_update_server.additional_information,
            firmware_update_server.metadata_fw_index);
        }
        // Switch to Idle state
        btmesh_firmware_udpate_server_change_state(METADATA_IDLE);
        break;
      case BTMESH_FW_UPDATE_SERVER_METADATA_CHECK_PENDING:
        // If pending, call step
        firmware_update_server.metadata_check_status =
          sl_btmesh_firmware_update_server_metadata_check_step(
            &firmware_update_server.additional_information);
        break;
    }
  }
}

bool sl_btmesh_firmware_update_server_is_ok_to_sleep(void)
{
  return (0 == firmware_update_server.metadata_check_state.active)
         && (0 == firmware_update_server.state.verification);
}

static void btmesh_firmware_udpate_server_change_state(btmesh_firmware_udpate_state_t state)
{
  if (state < METADATA_IDLE) {
    firmware_update_server.state.raw = 0;
  }
  switch (state) {
    case IDLE:
    // Idle's initial substate is Idle/Inactive
    case IDLE_INACTIVE:
      firmware_update_server.state.idle = 1;
      firmware_update_server.state.inactive = 1;
      firmware_update_server.self_update = false;
      break;
    case IDLE_FAILED_TRANSFER_FAILED:
      firmware_update_server.state.idle = 1;
      firmware_update_server.state.failed = 1;
      firmware_update_server.state.transfer_failed = 1;
      log_error("Firmware Transfer Failed" NL);
      break;
    case IDLE_FAILED_VERIFICATION_FAILED:
      firmware_update_server.state.idle = 1;
      firmware_update_server.state.failed = 1;
      firmware_update_server.state.verification_failed = 1;
      log_error("Firmware Verification Failed" NL);
      break;
    case ACTIVE_TRANSFER:
      firmware_update_server.state.active = 1;
      firmware_update_server.state.transfer = 1;
      log_info("Firmware Transfer Start" NL);
      break;
    case IDLE_SUSPENDED:
      firmware_update_server.state.idle = 1;
      firmware_update_server.state.transfer = 1;
      log_info("Firmware Transfer Suspended" NL);
      break;
    case ACTIVE_VERIFICATION:
      firmware_update_server.state.active = 1;
      firmware_update_server.state.verification = 1;
      log_info("Firmware Verification Start (BLOB ID: %s)" NL,
               BLOB_ID_TO_STRING(&firmware_update_server.blob_id));
      sl_btmesh_blob_storage_slot_metadata_cache_t const * cache;
      uint32_t len;
      // Get BLOB size from cached BLOB table
      sl_btmesh_blob_storage_get_cache(&cache, &len);
      for (uint32_t i = 0; i < len; ++i) {
        if (0 == memcmp(&cache[i].blob_id,
                        &firmware_update_server.blob_id,
                        sizeof(sl_bt_uuid_64_t))) {
          firmware_update_server.verification_size = cache[i].blob_size;
          break;
        }
      }
      firmware_update_server.verification_progress = 0;
      // Start verification with user callback
      firmware_update_server.verification_status =
        sl_btmesh_fw_update_server_verify_start(&firmware_update_server.blob_id,
                                                &firmware_update_server.verification_chunk_buffer,
                                                &firmware_update_server.verification_chunk_size,
                                                firmware_update_server.verification_size);
#if SL_BTMESH_FW_UPDATE_SERVER_VERIFY_PROGRESS_UI_UPDATE_PERIOD_CFG_VAL > 0
      app_timer_start(&firmware_update_server.verify_timer,
                      SL_BTMESH_FW_UPDATE_SERVER_VERIFY_PROGRESS_UI_UPDATE_PERIOD_CFG_VAL,
                      btmesh_firmware_update_server_verify_progress_ui_update,
                      NULL,
                      true);
#else // SL_BTMESH_FW_UPDATE_SERVER_VERIFY_PROGRESS_UI_UPDATE_PERIOD_CFG_VAL > 0
      btmesh_firmware_update_server_verify_progress_ui_update(NULL, NULL);
#endif // FW_UPDATE_SERVER_LOGGING_VERIFY_PROGRESS_PERIOD > 0
      break;
    case VERIFICATION_SUCCESS: {
      firmware_update_server.state.verification_success = 1;
      // Store metadata and FW index
      sl_status_t sc =
        sl_btmesh_blob_storage_write_app_footer(&firmware_update_server.blob_id,
                                                &firmware_update_server.metadata_fw_index,
                                                BLOB_STORAGE_APP_ID_DFU_METADATA,
                                                firmware_update_server.metadata_len
                                                + 1);
      app_assert_status_f(sc, "BLOB Storage footer writing failed!");
      log_info("Firmware Verification Successful" NL);
      break;
    }
    case METADATA_ACTIVE: {
      firmware_update_server.metadata_check_state.idle = 0;
      firmware_update_server.metadata_check_state.active = 1;
      // Notify user application about metadata check starting
      firmware_update_server.metadata_check_status =
        sl_btmesh_fw_update_server_metadata_check_start(firmware_update_server.metadata,
                                                        firmware_update_server.metadata_len,
                                                        &firmware_update_server.additional_information);
      log_info("Metadata check start." NL);
      log_debug("Metadata length: %d, Add. Info: %d" NL,
                firmware_update_server.metadata_len,
                firmware_update_server.additional_information);
      break;
    }
    case METADATA_IDLE:
      firmware_update_server.metadata_check_state.active = 0;
      firmware_update_server.metadata_check_state.idle = 1;
      break;
  }
}

static void btmesh_firmware_update_server_verify_progress_ui_update(app_timer_t *timer,
                                                                    void *data)
{
  (void)timer;
  (void)data;
  if (BTMESH_FW_UPDATE_SERVER_VERIFY_ERROR != firmware_update_server.verification_status) {
    uint8_t pct = SL_PROG_TO_PCT_INT(firmware_update_server.verification_size,
                                     firmware_update_server.verification_progress);
#if SL_BTMESH_FW_UPDATE_SERVER_VERIFY_PROGRESS_UI_UPDATE_PERIOD_CFG_VAL == 0
    static uint8_t prev;
    if (firmware_update_server.verification_progress == 0) {
      prev = 0;
    }
    if (pct > prev) {
#endif // SL_BTMESH_FW_UPDATE_SERVER_VERIFY_PROGRESS_UI_UPDATE_PERIOD_CFG_VAL == 0
    log_info("Firmware verification progress %d%%" NL,
             pct);
#if SL_BTMESH_FW_UPDATE_SERVER_VERIFY_PROGRESS_UI_UPDATE_PERIOD_CFG_VAL == 0
    prev = pct;
  }
#endif // SL_BTMESH_FW_UPDATE_SERVER_VERIFY_PROGRESS_UI_UPDATE_PERIOD_CFG_VAL == 0
    (void)pct; // In case logging is disabled, avoid warning.
  }
  sl_btmesh_fw_update_server_verify_progress_ui_update(firmware_update_server.verification_status,
                                                       firmware_update_server.verification_progress,
                                                       firmware_update_server.verification_size);
}

/** @} mesh_fw_update_server */
