/***************************************************************************//**
 * @file
 * @brief BT Mesh Firmware Distribution Server
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
#include "em_common.h"

#include "sl_bt_api.h"
#include "sl_btmesh_api.h"
#include "sl_btmesh_dcd.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT

#ifdef SL_CATALOG_APP_LOG_PRESENT
#include "app_log.h"
#endif // SL_CATALOG_APP_LOG_PRESENT

#include "app_assert.h"
#include "app_timer.h"
#include "sl_malloc.h"

#include "sl_btmesh_blob_storage_app_id.h"
#include "sl_btmesh_blob_storage.h"

#include "sl_btmesh_blob_transfer_client.h"

#include "sl_btmesh_capi_types.h"
#include "sl_btmesh_dfu_platform_capi.h"
#include "sl_btmesh_model_specification_v1_1_defs.h"

#include "sl_btmesh_fw_distribution_server.h"
#include "sl_btmesh_fw_distribution_server_config.h"

// Warning! The app_btmesh_util shall be included after the component configuration
// header file in order to provide the component specific logging macro.
#include "app_btmesh_util.h"

/***************************************************************************//**
 * @addtogroup dist_server BT Mesh Firmware Distribution Server
 * @{
 ******************************************************************************/

// -----------------------------------------------------------------------------
//                                    Macros
// -----------------------------------------------------------------------------

// Shortcut for the log prefix with space character separator
#define LOG_PREFIX SL_BTMESH_FW_DIST_SERVER_LOG_PREFIX_CFG_VAL " "

#if (SL_BTMESH_FW_DIST_SERVER_PLATFORM_CALLBACK_LOGGING_CFG_VAL != 0)
#define log_btmesh_platform_cb(...)  log_debug(__VA_ARGS__)
#else
#define log_btmesh_platform_cb(...)
#endif // (SL_BTMESH_FW_DIST_SERVER_PLATFORM_CALLBACK_LOGGING_CFG_VAL != 0)

#if defined(SL_CATALOG_APP_LOG_PRESENT) && (APP_BTMESH_UTIL_COMPONENT_LOGGING != 0)
#define log_fwid_level(level, fwid, fwid_len, hex_format) \
  _log_fwid_level(level, fwid, fwid_len, hex_format)
#define log_metadata_level(level, metadata, metadata_len, hex_format) \
  _log_metadata_level(level, metadata, metadata_len, hex_format)
#define log_bytes_as_text(level, bytes, len, null_replacement_char) \
  _log_bytes_as_text(level, bytes, len, null_replacement_char)
#define log_check_level(level) \
  app_log_check_level(level)
#else
#define log_fwid_level(level, fwid, fwid_len, hex_format)
#define log_metadata_level(level, metadata, metadata_len, hex_format)
#define log_bytes_as_text(level, bytes, len, null_replacement_char)
#define log_check_level(level)    false
#endif // defined(SL_CATALOG_APP_LOG_PRESENT) && (APP_BTMESH_UTIL_COMPONENT_LOGGING != 0)

// Temporary buffer to store byte array chunk
#define LOG_BYTES_AS_TEXT_CHUNK_SIZE  32

// Suppress compiler warning of unused static function
#define SL_UNUSED  __attribute__((unused))

// Utility macro to calculate the length of an array (number of array elements)
#define ARRAY_LEN(a)              (sizeof(a) / sizeof(a[0]))

// Maximum length of the firmware metadata based on the Mesh Model specification
//
// See Firmware Distribution Upload Start message in the specification for more
// details
#define DFU_METADATA_MAX_LEN      MESH_DFU_METADATA_MAX_LEN

// Maximum length of firmware identifier based on the Mesh Model specification
//
// See Firmware ID format in the Firmware update states chapter of the
// specification.
// 2 bytes company ID + 0..106 bytes Version Information => Total of 108 bytes
#define DFU_FWID_MAX_LEN          MESH_DFU_FWID_MAX_LEN

// Minimum length of firmware identifier based on the Mesh Model specification
#define DFU_FWID_MIN_LEN          MESH_DFU_FWID_MIN_LEN

// The node address zero is invalid according to the BT Mesh specification so
// it can be used to initialize address variables
#define UNASSIGNED_ADDRESS        0x0000

// Size of the firmware list depends on the current number of stored firmwares
#define FW_LIST_NVM_SIZE(fw_list_len) (sizeof(fw_dist_server_fw_list_nvm_t) \
                                       + (fw_list_len) * sizeof(sl_bt_uuid_64_t))

// Size of the firmware descriptor depends on the FW identifier length
#define FW_DESCRIPTOR_SIZE(fwid_length) (sizeof(fw_dist_server_fw_descriptor_t) \
                                         + fwid_length)

// Checks if given server is operational, and returns retval if not
#define SERVER_STATUS_CHECK(_srv, retval ...)  \
  if (((_srv) == NULL) || (_srv)->init_failed) \
    return retval

// Checks if given server is operational, and provides retval if not
#define SERVER_STATUS_GET(_srv, retval) \
  ((((_srv) == NULL) || ((_srv)->init_failed)) ? (retval) : SL_STATUS_OK)

// Returns the string representation of BLOB ID in a compound literal.
// WARNING! This macro shall be used as a parameter of log calls only due to the
// lifetime of underlying compound literal in APP_BTMESH_UUID_64_TO_STRING.
#define BLOB_ID_TO_STRING(blob_id) APP_BTMESH_UUID_64_TO_STRING(blob_id, ' ', true)

// -----------------------------------------------------------------------------
//                               Type definitions
// -----------------------------------------------------------------------------

typedef enum {
  FW_BLOB_SELECTOR_STORAGE,
  FW_BLOB_SELECTOR_CURRENT
} fw_blob_selector_t;

typedef enum {
  UPLOAD_STATE_INACTIVE,
  UPLOAD_STATE_TRANSFER_FAILED,
  UPLOAD_STATE_TRANSFER_CANCELED,
  UPLOAD_STATE_TRANSFER_SUCCESS,
  UPLOAD_STATE_TRANSFER_ACTIVE,
  UPLOAD_STATE_COUNT
} upload_state_t;

typedef struct {
  bool idle : 1;
  bool execute_step : 1;
  bool retry : 1;
} dist_state_flags_t;

typedef struct {
  bool idle : 1;
} upload_state_flags_t;

typedef struct {
  uint32_t size;
  sl_bt_uuid_64_t blob_id;
  uint8_t *metadata;
  uint8_t metadata_length;
  uint8_t fwid_length;
  uint8_t fwid[];
} fw_dist_server_fw_descriptor_t;

/// Upload process data representation
typedef struct {
  /// Status of the upload
  upload_state_t state;
  /// Firmware descriptor
  fw_dist_server_fw_descriptor_t *fw_descriptor;
  /// Metadata pointer (heap array)
  uint8_t *temp_metadata;
  /// Metadata length
  uint8_t temp_metadata_length;
  /// Metadata error flag
  bool metadata_error : 1;
  /// Managed flag error flag
  bool managed_blob_error : 1;
} fw_dist_server_upload_t;

/// Distribution process data representation
typedef struct {
  /// Timer handler
  struct app_timer timer;
  /// Size of the FW being transferred
  uint32_t fw_size;
  /// Number of nodes currently distributing to
  uint16_t node_count;
  /// The number of active nodes.
  /// Nodes the distributor currently distributes to, that haven't failed.
  uint16_t num_active_nodes;
  /// Index of the FW being transported
  uint16_t fw_list_index;
  /// Counter used for retriable operations
  uint16_t retry_counter;
  /// Current state of distribution
  sl_btmesh_fw_dist_server_dist_step_t state;
  /// BLOB ID of the distributed BLOB
  ///
  /// This ID is the ID which the distributor received the BLOB by.
  /// @note Not the BLOB ID that's used during distribution.
  sl_bt_uuid_64_t storage_blob_id;
  /// Transfer mode for distribution specified by Initiator node
  sl_btmesh_mbt_client_transfer_mode_t transfer_mode;
  /// Flag indicating whether retry timer elapsed
  bool retry_time_elapsed : 1;
  /// Flag indicating whether BLOB transfer was started in current distribution
  bool blob_transfer_started : 1;
} fw_dist_server_dist_t;

/// Distribution Server capabilities data representation
typedef struct {
  /// The size of the biggest image that could be stored on the device
  uint32_t max_fw_image_size;
  /// Sum of the available space in slots
  uint32_t max_upload_space;
  /// Maximum length of the FW list.
  ///
  /// The maximum number of possible FWs to store is the number of slots.
  /// @see sl_btmesh_blob_storage_get_max_blob_count
  uint16_t max_fw_list_length;
} fw_dist_server_capabilities_t;

/// Firmware list representation
typedef PACKSTRUCT (struct {
  /// Length of the list
  uint16_t current_fw_list_length;
  /// BLOB IDs of FW images
  sl_bt_uuid_64_t blob_ids[];
}) fw_dist_server_fw_list_nvm_t;

/// Distributor Server data representation
typedef struct {
  /// Element belonging to the represented Server model
  uint16_t elem_index;
  /// RAM mirror of Firmware List data which is stored in NVM
  fw_dist_server_fw_list_nvm_t *fw_list_nvm;
  /// Firmware List data
  fw_dist_server_fw_descriptor_t **fw_list;
  /// Capabilities of the Server
  fw_dist_server_capabilities_t *capabilities;
  /// Upload related status variables
  fw_dist_server_upload_t upload;
  /// Distribution related status variables
  fw_dist_server_dist_t dist;
  /// The address of the client requesting delete stored for async. response
  uint16_t async_req_client_address;
  /// FW ID length of current single image deletion
  uint8_t deleting_fwid_len;
  /// FW ID of current single image deletion
  uint8_t * deleting_fwid;
  /// Flag indicating initialization failure
  bool init_failed : 1;
  /// Flag indicating storage corruption
  bool storage_corrupted : 1;
  /// Ongoing single image delete
  bool deleting : 1;
  /// Ongoing delete of all images
  bool deleting_all : 1;
} fw_dist_server_t;

/// Linked list of distribution servers
typedef struct fw_dist_server_list_s {
  /// Distribution server descriptor
  fw_dist_server_t server;
  /// Next list element
  struct fw_dist_server_list_s *next;
} fw_dist_server_list_t;

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

/***************************************************************************//**
 * Log byte array as text
 *
 * The byte arrays might not be null terminated so it is not a valid C string
 * and therefore it can't be used directly with log macros. This function adds
 * null character termination and replaces zero bytes with the provided
 * replacement character.
 *
 * @param level Log level
 * @param bytes Pointer to the byte array which shall be logged
 * @param len Length of byte array
 * @param null_replacement_char Zero bytes are replaced with this character
 *
 ******************************************************************************/
SL_UNUSED static void _log_bytes_as_text(uint8_t level,
                                         const uint8_t *bytes,
                                         uint16_t len,
                                         char null_replacement_char);

/***************************************************************************//**
 * Log firmware identifier
 *
 * @param level Log level
 * @param fwid Pointer to the FW id byte array
 * @param fwid_len Length of FW id byte array
 * @param hex_format If it is set to true then hex format is used otherwise it
 *   is logged as a string
 *
 ******************************************************************************/
SL_UNUSED static void _log_fwid_level(uint8_t level,
                                      const uint8_t *fwid,
                                      uint8_t fwid_len,
                                      bool hex_format);

/***************************************************************************//**
 * Log metadata
 *
 * @param level Log level
 * @param metadata Pointer to the metadata byte array
 * @param metadata_len Length of metadata byte array
 * @param hex_format If it is set to true then hex format is used otherwise it
 *   is logged as a string
 *
 ******************************************************************************/
SL_UNUSED static void _log_metadata_level(uint8_t level,
                                          const uint8_t *metadata,
                                          uint8_t metadata_len,
                                          bool hex_format);

/***************************************************************************//**
 * Transition Upload state machine into selected state
 *
 * @param self Pointer to Distribution Server descriptor sturcture
 * @param target_state State to transition into
 ******************************************************************************/
static void upload_state_transition(fw_dist_server_t *const self,
                                    const upload_state_t target_state);

/***************************************************************************//**
 * Initializes the distributor state vaiables
 *
 * @param[in] self Pointer to the Distributor Server data representing the
 *                 current Distributor
 ******************************************************************************/
static void dist_init(fw_dist_server_t *const self);

/***************************************************************************//**
 * Notification handler for BLOB Transfer Client API
 *
 * @param notification Notification data
 ******************************************************************************/
static void handle_blob_transfer_client_notification(
  const sl_btmesh_blob_transfer_client_notification_t *const notification);

/***************************************************************************//**
 * Transition Distribution state machine into selected state
 *
 * @param self Pointer to Distribution Server descriptor structure
 * @param target_state State to transition into
 ******************************************************************************/
static void dist_state_transition(fw_dist_server_t *const self,
                                  const sl_btmesh_fw_dist_server_dist_step_t target_state);

/***************************************************************************//**
 * Finds server in linked list belonging to elem_index
 *
 * @see fw_dist_server_list_t, fw_dist_server_list
 *
 * @param[in] elem_index Element index for the server
 *
 * @returns Pointer to the server descriptor
 ******************************************************************************/
static fw_dist_server_t* find_server(uint16_t elem_index);

/***************************************************************************//**
 * Invalidates the FW list in BLOB storage and clears the FW list in NVM and RAM
 *
 * @param[in] self Pointer to the Distributor Server data representing the
 *                 current Distributor
 ******************************************************************************/
static sl_status_t fw_invalidate_all(fw_dist_server_t *const self);

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------
static const upload_state_flags_t upload_state_flags[UPLOAD_STATE_COUNT] = {
  [UPLOAD_STATE_INACTIVE]           = { .idle = 1 },
  [UPLOAD_STATE_TRANSFER_FAILED]    = { .idle = 1 },
  [UPLOAD_STATE_TRANSFER_CANCELED]  = { .idle = 1 },
  [UPLOAD_STATE_TRANSFER_SUCCESS]   = { .idle = 1 },
  [UPLOAD_STATE_TRANSFER_ACTIVE]    = { .idle = 0 },
};

static const dist_state_flags_t dist_state_flags[] = {
  [sl_btmesh_fw_dist_server_dist_step_idle]                   = { .idle = 1, .execute_step = 0, .retry = 0 },
  [sl_btmesh_fw_dist_server_dist_step_starting_update]        = { .idle = 0, .execute_step = 1, .retry = 1 },
  [sl_btmesh_fw_dist_server_dist_step_transferring_image]     = { .idle = 0, .execute_step = 0, .retry = 0 },
  [sl_btmesh_fw_dist_server_dist_step_checking_verification]  = { .idle = 0, .execute_step = 1, .retry = 1 },
  [sl_btmesh_fw_dist_server_dist_step_waiting_for_apply]      = { .idle = 0, .execute_step = 0, .retry = 0 },
  [sl_btmesh_fw_dist_server_dist_step_applying_update]        = { .idle = 0, .execute_step = 1, .retry = 1 },
  [sl_btmesh_fw_dist_server_dist_step_checking_update_result] = { .idle = 0, .execute_step = 1, .retry = 1 },
  [sl_btmesh_fw_dist_server_dist_step_completed]              = { .idle = 1, .execute_step = 0, .retry = 0 },
  [sl_btmesh_fw_dist_server_dist_step_failed]                 = { .idle = 1, .execute_step = 0, .retry = 0 },
  [sl_btmesh_fw_dist_server_dist_step_cancelling]             = { .idle = 0, .execute_step = 1, .retry = 1 },
  [sl_btmesh_fw_dist_server_dist_step_suspended]              = { .idle = 0, .execute_step = 0, .retry = 0 },
};

/// Linked list of available servers
static fw_dist_server_list_t *fw_dist_server_list = NULL;
/// Common storage capabilities descriptor
static fw_dist_server_capabilities_t fw_dist_server_capabilities = { 0 };

static void _log_bytes_as_text(uint8_t level,
                               const uint8_t *bytes,
                               uint16_t len,
                               char null_replacement_char)
{
  const uint16_t temp_str_size = LOG_BYTES_AS_TEXT_CHUNK_SIZE;
  char temp_buffer[LOG_BYTES_AS_TEXT_CHUNK_SIZE + 1];

  // If the logging is disabled then the buffer is not used so the compiler
  // warning is suppressed because this function is not used at all in case of
  // disabled logging
  (void) temp_buffer;

  // There is no terminating zero character at the end of bytes and it might
  // contain null characters which might terminate the logging early
  if (log_check_level(level) && (bytes != NULL)) {
    uint16_t remaining_len = len;
    uint16_t offset = 0;
    while (0 < remaining_len) {
      uint16_t chunk_len = (remaining_len < temp_str_size) ? remaining_len : temp_str_size;
      uint16_t idx;
      for (idx = 0; idx < chunk_len; idx++) {
        temp_buffer[idx] = (bytes[offset] != '\0') ? bytes[offset] : null_replacement_char;
        offset++;
      }
      temp_buffer[idx] = '\0';
      log_append(temp_buffer);
      remaining_len -= chunk_len;
    }
  }
  (void)level;
}

static void _log_fwid_level(uint8_t level,
                            const uint8_t *fwid,
                            uint8_t fwid_len,
                            bool hex_format)
{
  // This function is not used when the logging is turned off
  (void) level;

  if ((fwid != NULL) && (fwid_len >= DFU_FWID_MIN_LEN)) {
    if (hex_format) {
      log_hexdump_level_s(level, "", fwid, fwid_len);
    } else {
      log_hexdump_level_s(level, "", fwid, DFU_FWID_MIN_LEN);
      log_bytes_as_text(level,
                        &fwid[DFU_FWID_MIN_LEN],
                        fwid_len - DFU_FWID_MIN_LEN,
                        ' ');
    }
  }
}

static void _log_metadata_level(uint8_t level,
                                const uint8_t *metadata,
                                uint8_t metadata_len,
                                bool hex_format)
{
  // This function is not used when the logging is turned off
  (void) level;
  (void) metadata_len;

  if (metadata != NULL) {
    if (hex_format) {
      log_hexdump_level(level, metadata, metadata_len);
    } else {
      log_bytes_as_text(level, metadata, metadata_len, ' ');
    }
  }
}

static fw_dist_server_t* find_server(uint16_t elem_index)
{
  fw_dist_server_list_t *head = fw_dist_server_list;
  if (head == NULL) {
    return NULL;
  }
  do {
    if (head->server.elem_index == elem_index) {
      return &head->server;
    }
  } while (NULL != (head = head->next));
  return NULL;
}

static void dist_retry_timer_cb(app_timer_t *timer, void *data)
{
  (void) timer;
  fw_dist_server_t *const self = data;

  self->dist.retry_time_elapsed = true;
  // If the retry timer elapses, then the current state shall be reentered to
  // execute the state entry behavior again (self transition)
  // Note: the retry timer is only started in states which supports retry, so it
  //       is not necessary to check that here
  dist_state_transition(self, self->dist.state);

  app_assert(NULL != data, "The data is NULL in retry timer callback");
}

static void dist_start_retry_timer(fw_dist_server_t *const self)
{
  sl_status_t sc;

  // There is no tx complete event in the distributor which signals whether the
  // mesh messages are sent or they are still in the message queue. Therefore it
  // does not really make sense to send messages without waiting some time.
  //
  // Wait the retry time to provide some time for the servers to respond. This
  // also spares bandwidth, because the Fw Distributor does not flood the mesh
  // network with messages.
  sc = app_timer_start(&self->dist.timer,
                       SL_BTMESH_FW_DIST_SERVER_RETRY_TIME_MS_CFG_VAL,
                       dist_retry_timer_cb,
                       self,
                       false);
  app_assert_status_f(sc,
                      "Failed to dist start retry timer (elem=%d)",
                      self->elem_index);
}

static void dist_stop_retry_timer(fw_dist_server_t *const self)
{
  // It is not considered an error if stop is requested for a timer which is not
  // running, therefore stop is called here always to be safe.
  sl_status_t sc = app_timer_stop(&self->dist.timer);

  app_assert_status_f(sc,
                      "Failed to stop dist retry timer (elem=%d)",
                      self->elem_index);
}

static uint32_t calc_fw_storage_max_app_footer_size(void)
{
  // Max number of storage bytes used to store FWID in BLOB storage
  uint32_t fwid_footer_size =
    sl_btmesh_blob_storage_calc_app_footer_size(DFU_FWID_MAX_LEN);

  // Max number of storage bytes used to store metadata in BLOB storage
  uint32_t metadata_footer_size =
    sl_btmesh_blob_storage_calc_app_footer_size(DFU_METADATA_MAX_LEN);

  // Max number of storage bytes used to store managed flag in BLOB storage
  uint32_t managed_flag_size = sl_btmesh_blob_storage_get_managed_flag_size();

  // Max number of storage bytes used to store distribution server specific
  // data in BLOB storage in case of a single BLOB
  return fwid_footer_size + metadata_footer_size + managed_flag_size;
}

static uint32_t calc_fw_storage_max_fw_image_size(void)
{
  uint32_t max_fw_image_size = sl_btmesh_blob_storage_get_max_blob_size();
  uint32_t max_app_footer_size = calc_fw_storage_max_app_footer_size();

  if (max_app_footer_size < max_fw_image_size) {
    max_fw_image_size -= max_app_footer_size;
  } else {
    max_fw_image_size = 0;
  }
  return max_fw_image_size;
}

static uint32_t calc_fw_storage_max_fw_image_size_free(void)
{
  uint32_t max_fw_image_size_free = sl_btmesh_blob_storage_get_max_blob_size_free(true);
  uint32_t max_app_footer_size = calc_fw_storage_max_app_footer_size();

  if (max_app_footer_size < max_fw_image_size_free) {
    max_fw_image_size_free -= max_app_footer_size;
  } else {
    max_fw_image_size_free = 0;
  }
  return max_fw_image_size_free;
}

static uint32_t calc_fw_storage_max_upload_space(fw_dist_server_t *const self)
{
  uint32_t max_upload_space = sl_btmesh_blob_storage_get_total_space();
  uint32_t max_app_footer_size = calc_fw_storage_max_app_footer_size();

  uint32_t max_fw_list_app_footer_size =
    max_app_footer_size * self->capabilities->max_fw_list_length;

  if (max_fw_list_app_footer_size < max_upload_space) {
    max_upload_space -= max_fw_list_app_footer_size;
  } else {
    max_upload_space = 0;
  }
  return max_upload_space;
}

static uint32_t calc_fw_storage_remaining_upload_space(fw_dist_server_t *const self)
{
  uint32_t remaining_upload_space = sl_btmesh_blob_storage_get_remaining_space(true);
  uint32_t max_app_footer_size = calc_fw_storage_max_app_footer_size();

  if (NULL == self->fw_list_nvm) {
    remaining_upload_space = 0;
  } else {
    // Some bytes shall be reserved to store app footers in BLOB storage for each
    // free entry in the FW list so the remaining bytes shall be decreased by
    // that amount. BLOB storage does not able to provide this information in the
    // sl_btmesh_blob_storage_get_remaining_space API call because the number and
    // length of the footer data depends on the distributor.
    uint32_t max_fw_list_app_footer_size = max_app_footer_size
                                           * (self->capabilities->max_fw_list_length
                                              - self->fw_list_nvm->current_fw_list_length);

    if (max_fw_list_app_footer_size < remaining_upload_space) {
      remaining_upload_space -= max_fw_list_app_footer_size;
    } else {
      remaining_upload_space = 0;
    }
  }
  return remaining_upload_space;
}

static void upload_init(fw_dist_server_t *const self)
{
  self->upload.state = UPLOAD_STATE_INACTIVE;
  self->upload.metadata_error = false;
  self->upload.managed_blob_error = false;
}

static sl_status_t fw_storage_cleanup(fw_dist_server_t *const self)
{
  sl_status_t sc = SL_STATUS_OK, sc_cleanup = SL_STATUS_OK;
  uint32_t occurrence_idx = 0;
  sl_bt_uuid_64_t blob_id;
  uint16_t fw_list_index;

  while (true) {
    // Iterate each BLOB in BLOB storage which belongs to FW Distribution Server
    // Note: the API returns SL_STATUS_NOT_FOUND if no BLOBs are found with
    // owner_id or the occurrence_idx is greater or equal to the number of BLOBs
    // managed by the owner
    sc = sl_btmesh_blob_storage_get_blob_id_by_owner(BLOB_STORAGE_OWNER_ID_FW_DIST_SERVER,
                                                     occurrence_idx,
                                                     &blob_id);
    if (sc != SL_STATUS_OK) {
      if (sc != SL_STATUS_NOT_FOUND) {
        // An unexpected error occurred in BLOB storage
        log_status_error_f(sc,
                           LOG_PREFIX
                           "Failed to get BLOB by owner (elem=%d,blobid=%s)" NL,
                           self->elem_index,
                           BLOB_ID_TO_STRING(&blob_id));
        sc_cleanup = sc;
      }
      break;
    }

    // Leaked BLOBs in BLOB storage are those BLOBs which belongs to the FW
    // Distribution Server but they are not in the FW list.
    // For example: Leaked BLOBs may occur when the NVM data is deleted
    // externally but the BLOB storage remains intact. BLOB leak can happen also
    // when a reset occurs after the BLOB is stored in the flash but before
    // the fwid is written as an application footer to the BLOB.
    bool blob_leaked = true;

    // Check if the BLOB is present in the FW list
    for (fw_list_index = 0;
         fw_list_index < self->fw_list_nvm->current_fw_list_length;
         fw_list_index++) {
      if (0 == memcmp(&self->fw_list[fw_list_index]->blob_id,
                      &blob_id,
                      sizeof(sl_bt_uuid_64_t))) {
        blob_leaked = false;
        break;
      }
    }

    if (blob_leaked) {
      // Invalidate the leaked BLOB in BLOB storage
      // BLOB storage guarantees that the BLOBs of FW Distribution Server with
      // higher occurrence_idx than the invalidated BLOB are decremented by one
      // when invalidation is executed so occurrence_idx shall not be modified
      sl_status_t sc_invalidate = sl_btmesh_blob_storage_invalidate(&blob_id);

      log_warning(LOG_PREFIX
                  "BLOB storage cleanup (elem=%d,blobid=%s)" NL,
                  self->elem_index,
                  BLOB_ID_TO_STRING(&blob_id));

      if (SL_STATUS_OK != sc_invalidate) {
        // Invalidation failed so as a last resort try to delete the BLOB
        // by erasing the medium
        sl_status_t sc_delete = sl_btmesh_blob_storage_delete(&blob_id);

        if (SL_STATUS_OK != sc_delete) {
          log_status_error_f(sc_delete,
                             LOG_PREFIX "BLOB storage cleanup failed"
                                        "(elem=%d,blobid=%s)" NL,
                             self->elem_index,
                             BLOB_ID_TO_STRING(&blob_id));
          sc_cleanup = sc;
        }
      }
    } else {
      // Continue the iteration
      occurrence_idx++;
    }
  }
  return sc_cleanup;
}

static sl_status_t fw_storage_get_fwid_length(fw_dist_server_t *const self,
                                              const sl_bt_uuid_64_t *blob_id,
                                              uint8_t *fwid_length)
{
  (void) self;
  sl_status_t sc;
  uint16_t length;

  sc = sl_btmesh_blob_storage_get_app_footer_length(blob_id,
                                                    BLOB_STORAGE_APP_ID_DFU_FWID,
                                                    &length);
  // The mandatory firmware ID footer was not written in the BLOB storage,
  // which means the BLOB storage shall be considered corrupted.
  log_status_error_f(sc,
                     LOG_PREFIX
                     "Firmware ID is missing from BLOB storage "
                     "(elem=%d,blobid=%s)" NL,
                     self->elem_index,
                     BLOB_ID_TO_STRING(blob_id));

  if (sc == SL_STATUS_OK) {
    if ((length >= DFU_FWID_MIN_LEN) && (length <= DFU_FWID_MAX_LEN)) {
      *fwid_length = length;
    } else {
      sc = SL_STATUS_INVALID_RANGE;
      // The mandatory firmware ID footer has invalid length in the BLOB
      // storage, which means the BLOB shall be considered corrupted.
      log_error(LOG_PREFIX
                "Firmware ID with invalid length in BLOB storage "
                "(elem=%d,fwid_len=%u,blobid=%s)" NL,
                self->elem_index,
                length,
                BLOB_ID_TO_STRING(blob_id));
    }
  }
  return sc;
}

static sl_status_t fw_storage_get_metadata_length(fw_dist_server_t *const self,
                                                  const sl_bt_uuid_64_t *blob_id,
                                                  uint8_t *metadata_length)
{
  (void) self;
  sl_status_t sc;
  uint16_t length;

  sc = sl_btmesh_blob_storage_get_app_footer_length(blob_id,
                                                    BLOB_STORAGE_APP_ID_DFU_METADATA,
                                                    &length);
  if (SL_STATUS_NOT_FOUND != sc) {
    // The metadata is optional so it is not an error if it is missing
    log_status_error_f(sc,
                       LOG_PREFIX
                       "Failed to read metadata from BLOB storage"
                       "(elem=%d,blobid=%s)" NL,
                       self->elem_index,
                       BLOB_ID_TO_STRING(blob_id));
  }

  if (sc == SL_STATUS_OK) {
    // If the metadata exists then it shall be at least one byte long
    if (length > 0 && length <= DFU_METADATA_MAX_LEN) {
      *metadata_length = length;
    } else {
      sc = SL_STATUS_INVALID_RANGE;
      log_error(LOG_PREFIX
                "Metadata with invalid length in BLOB storage "
                "(elem=%d,metadata_len=%u,blobid=%s)" NL,
                self->elem_index,
                length,
                BLOB_ID_TO_STRING(blob_id));
    }
  }
  return sc;
}

static sl_status_t fw_storage_fill_fw_descriptor(fw_dist_server_t *const self,
                                                 uint16_t fw_list_idx,
                                                 const sl_bt_uuid_64_t *blob_id,
                                                 uint32_t blob_size,
                                                 uint8_t fwid_length,
                                                 uint8_t metadata_length,
                                                 bool metadata_exists)
{
  sl_status_t sc;
  sl_status_t sc_fwid_get = SL_STATUS_FAIL, sc_metadata_get = SL_STATUS_NOT_FOUND;
  fw_dist_server_fw_descriptor_t *const fw_descriptor = self->fw_list[fw_list_idx];

  // The fw_list_build allocates the necessary space for fwid and metadata based
  // on the previous BLOB storage application footer length getter calls so the
  // fwid and metadata should fit into these allocated dynamic memory buffers
  uint16_t storage_fwid_length = fwid_length;
  uint16_t storage_metadata_length = metadata_length;

  fw_descriptor->size = blob_size;
  fw_descriptor->blob_id = *blob_id;
  fw_descriptor->fwid_length = fwid_length;
  sc_fwid_get =
    sl_btmesh_blob_storage_get_app_footer(blob_id,
                                          BLOB_STORAGE_APP_ID_DFU_FWID,
                                          fw_descriptor->fwid,
                                          &storage_fwid_length);

  // This error is really unexpected because fw_storage_get_fwid_length and
  // fw_storage_get_metadata_length was successful so the BLOB has valid fwid
  // and metadata which should be readable
  log_status_error_f(sc_fwid_get,
                     LOG_PREFIX
                     "Firmware ID is missing from BLOB storage "
                     "(elem=%d,blobid=%s)" NL,
                     self->elem_index,
                     BLOB_ID_TO_STRING(blob_id));

  if ((sc_fwid_get == SL_STATUS_OK)
      && (fwid_length != storage_fwid_length)) {
    log_error(LOG_PREFIX
              "Unexpected fwid length in BLOB storage "
              "(elem=%d,blobid=%s,fwid_len=%u[%u])" NL,
              self->elem_index,
              BLOB_ID_TO_STRING(blob_id),
              storage_fwid_length,
              fwid_length);
    sc_fwid_get = SL_STATUS_INVALID_RANGE;
  }

  if (metadata_exists) {
    fw_descriptor->metadata_length = metadata_length;
    sc_metadata_get =
      sl_btmesh_blob_storage_get_app_footer(blob_id,
                                            BLOB_STORAGE_APP_ID_DFU_METADATA,
                                            fw_descriptor->metadata,
                                            &storage_metadata_length);

    log_status_error_f(sc_metadata_get,
                       LOG_PREFIX
                       "Failed to read metadata from BLOB storage"
                       "(elem=%d,blobid=%s)" NL,
                       self->elem_index,
                       BLOB_ID_TO_STRING(blob_id));

    if ((sc_metadata_get == SL_STATUS_OK)
        && (metadata_length != storage_metadata_length)) {
      log_error(LOG_PREFIX
                "Unexpected metadata length in BLOB storage "
                "(elem=%d,blobid=%s,metadata_len=%u[%u])" NL,
                self->elem_index,
                BLOB_ID_TO_STRING(blob_id),
                storage_metadata_length,
                metadata_length);
      sc_metadata_get = SL_STATUS_INVALID_RANGE;
    }
  } else {
    fw_descriptor->metadata = NULL;
    fw_descriptor->metadata_length = 0;
  }

  if (sc_fwid_get != SL_STATUS_OK) {
    sc = sc_fwid_get;
  } else if (metadata_exists && (sc_metadata_get != SL_STATUS_OK)) {
    sc = sc_metadata_get;
  } else {
    sc = SL_STATUS_OK;
  }
  return sc;
}

static void fw_list_handle_build_error(fw_dist_server_t *const self,
                                       uint16_t fw_list_idx,
                                       const sl_bt_uuid_64_t blob_id,
                                       bool remove_from_blob_storage)
{
  // If the length query of fwid or metadata fails then the fw descriptor
  // is not allocated so a NULL check is necessary here
  if (self->fw_list[fw_list_idx] != NULL) {
    sl_free(self->fw_list[fw_list_idx]->metadata);
    sl_free(self->fw_list[fw_list_idx]);
    self->fw_list[fw_list_idx] = NULL;
  }

  // The complete NVM FW list was read from the NVM already so in order to remove
  // the inconsistent BLOB from NVM FW list all following BLOB shall be shifted
  // towards the position of the removed inconsistent BLOB.
  for (uint16_t idx = fw_list_idx;
       (idx + 1) < self->fw_list_nvm->current_fw_list_length;
       idx++) {
    self->fw_list_nvm->blob_ids[idx] = self->fw_list_nvm->blob_ids[idx + 1];
  }
  // Inconsistent BLOB is removed so the FW list length is decremented
  self->fw_list_nvm->current_fw_list_length--;

  log_warning(LOG_PREFIX
              "Inconsistent BLOB is removed from FW list "
              "(elem=%d,blob_id=%s)" NL,
              self->elem_index,
              BLOB_ID_TO_STRING(&blob_id));

  if (remove_from_blob_storage) {
    // Invalidate the BLOB in BLOB storage because it is much faster than the
    // delete operation which is important to have fast startup
    sl_status_t sc_invalidate = sl_btmesh_blob_storage_invalidate(&blob_id);

    log_warning(LOG_PREFIX
                "Incomplete BLOB removal from BLOB storage (elem=%d,blobid=%s)" NL,
                self->elem_index,
                BLOB_ID_TO_STRING(&blob_id));

    if (SL_STATUS_OK != sc_invalidate) {
      // Invalidation failed so as a last resort try to delete the BLOB
      // by erasing the medium
      sl_status_t sc_delete = sl_btmesh_blob_storage_delete(&blob_id);

      if (SL_STATUS_OK != sc_delete) {
        log_status_error_f(sc_delete,
                           LOG_PREFIX
                           "Incomplete BLOB removal from BLOB storage failed "
                           "(elem=%d,blobid=%s)" NL,
                           self->elem_index,
                           BLOB_ID_TO_STRING(&blob_id));
      }
    }
  }
}

static sl_status_t fw_list_build(fw_dist_server_t *const self)
{
  uint16_t fw_list_idx = 0;
  bool fw_list_nvm_changed = false;

  while (fw_list_idx < self->fw_list_nvm->current_fw_list_length) {
    sl_status_t sc_blob_size = SL_STATUS_FAIL;
    sl_status_t sc_fwid_len = SL_STATUS_FAIL;
    sl_status_t sc_metadata_len = SL_STATUS_NOT_FOUND;
    sl_status_t sc_fill_fw_desc = SL_STATUS_FAIL;
    uint32_t blob_size = 0;
    uint8_t fwid_length = 0, metadata_length = 0;
    bool fw_list_nvm_entry_invalid = false;
    sl_bt_uuid_64_t *blob_id = &self->fw_list_nvm->blob_ids[fw_list_idx];

    sc_blob_size = sl_btmesh_blob_storage_get_blob_size(blob_id,
                                                        &blob_size);

    if (SL_STATUS_OK == sc_blob_size) {
      sc_fwid_len = fw_storage_get_fwid_length(self, blob_id, &fwid_length);
      sc_metadata_len = fw_storage_get_metadata_length(self, blob_id, &metadata_length);
    } else {
      // This means that the passed BLOB ID is not stored in BLOB storage,
      // which means that there is inconsistency between the NVM FW list
      // and the BLOB storage.
      log_status_error_f(sc_blob_size,
                         LOG_PREFIX
                         "BLOB from NVM FW list is not found in BLOB storage "
                         "(elem=%d,blobid=%s)" NL,
                         self->elem_index,
                         BLOB_ID_TO_STRING(blob_id));
    }

    // Metadata is not mandatory so it is not an error when it is missing.
    // Note: During upload, the firmware ID is written after the metadata.
    // If a reset occurs during writing the metadata, then it means that the
    // firmware ID is not written as well, and the previous checks regarding
    // the firmware ID would have failed.
    bool fw_storage_data_valid = (sc_blob_size == SL_STATUS_OK)
                                 && (sc_fwid_len == SL_STATUS_OK)
                                 && ((sc_metadata_len == SL_STATUS_OK)
                                     || (sc_metadata_len == SL_STATUS_NOT_FOUND));

    if (fw_storage_data_valid == false) {
      fw_list_nvm_entry_invalid = true;
    } else {
      bool metadata_exists = (sc_metadata_len == SL_STATUS_OK);

      // The fwid and metadata length is known so the the dynamic memory can
      // be allocated and it can be used to store the fwid and metadata so
      // no local variable is necessary during BLOB storage read.
      self->fw_list[fw_list_idx] = sl_malloc(FW_DESCRIPTOR_SIZE(fwid_length));

      if (self->fw_list[fw_list_idx] == NULL) {
        log_critical(LOG_PREFIX
                     "FW info allocation failed (elem=%d,blobid=%s)" NL,
                     self->elem_index,
                     BLOB_ID_TO_STRING(blob_id));
        return SL_STATUS_ALLOCATION_FAILED;
      }

      if (metadata_exists) {
        self->fw_list[fw_list_idx]->metadata = sl_malloc(metadata_length);
        if (self->fw_list[fw_list_idx]->metadata == NULL) {
          log_critical(LOG_PREFIX
                       "Metadata allocation failed (elem=%d,blobid=%s)" NL,
                       self->elem_index,
                       BLOB_ID_TO_STRING(blob_id));
          sl_free(self->fw_list[fw_list_idx]);
          self->fw_list[fw_list_idx] = NULL;
          return SL_STATUS_ALLOCATION_FAILED;
        }
      }

      // Fill the allocated FW descriptor with available data like BLOB ID and
      // size and fill the fwid and metadata from the BLOB storage directly
      sc_fill_fw_desc = fw_storage_fill_fw_descriptor(self,
                                                      fw_list_idx,
                                                      blob_id,
                                                      blob_size,
                                                      fwid_length,
                                                      metadata_length,
                                                      metadata_exists);
      if (sc_fill_fw_desc != SL_STATUS_OK) {
        fw_list_nvm_entry_invalid = true;
      }
    }

    // If there is inconsistency between NVM FW list and BLOB storage content
    // then the inconsistent BLOB shall removed from the FW list and from the
    // NVM FW list and from BLOB storage.
    if (fw_list_nvm_entry_invalid) {
      // It is possible that the BLOB is stored in BLOB storage but there are
      // some integrity failures like missing FWID so the BLOB shall be removed
      // from the BLOB storage in this special case.
      bool remove_from_blob_storage = (sc_blob_size == SL_STATUS_OK);

      // The FW list is being built in this function so in order to remove the
      // BLOB from the FW list it is enough to avoid incrementing the fw_list_idx.
      fw_list_handle_build_error(self,
                                 fw_list_idx,
                                 *blob_id,
                                 remove_from_blob_storage);

      // The NVM FW list is changed in RAM so it shall be saved into the NVM but
      // it might happen that multiple BLOBs are removed due to inconsistency
      // during the iteration so it is better to save it once after the iteration
      fw_list_nvm_changed = true;
    } else {
      // Valid entry is added to the FW list so the index shall be incremented
      fw_list_idx++;
    }
  }

  if (fw_list_nvm_changed) {
    sl_status_t sc;
    sc = app_btmesh_nvm_write(SL_BTMESH_FW_DIST_SERVER_FW_LIST_NVM_KEY_CFG_VAL,
                              self->fw_list_nvm,
                              FW_LIST_NVM_SIZE(self->fw_list_nvm->current_fw_list_length));
    log_status_error_f(sc,
                       LOG_PREFIX "Failed to save NVM FW list (elem=%d)" NL,
                       self->elem_index);
  }
  return SL_STATUS_OK;
}

static void fw_list_free_fw_descriptors(fw_dist_server_t *const self)
{
  // The NULL check guarantees that this API can be called at initialization time
  if (NULL != self->fw_list) {
    for (uint16_t fw_list_index = 0;
         fw_list_index < self->fw_list_nvm->current_fw_list_length;
         fw_list_index++) {
      fw_dist_server_fw_descriptor_t *fw_descriptor = self->fw_list[fw_list_index];
      if (fw_descriptor != NULL) {
        // The sl_free function handles null pointer like a no-operation
        sl_free(fw_descriptor->metadata);
      }
      sl_free(fw_descriptor);
      self->fw_list[fw_list_index] = NULL;
    }
  }
}

static void fw_list_init(fw_dist_server_t *const self)
{
  sl_status_t sc;
  self->fw_list_nvm = NULL;

  if (0 == self->capabilities->max_fw_list_length) {
    // The BLOB storage is not able store any firmware image which makes the
    // distributor useless which may occur when the bootloader storage slot
    // configuration is not correct (BLOB storage stores FW in bootloader slots)
    self->init_failed = true;
    return;
  }

  uint16_t max_fw_list_length = self->capabilities->max_fw_list_length;

  size_t max_fw_list_nvm_size = FW_LIST_NVM_SIZE(max_fw_list_length);

  // The RAM mirror for NVM firmware list is allocated for the maximum firmware
  // list length at initialization time to avoid reallocation at runtime
  self->fw_list_nvm = sl_calloc(1, max_fw_list_nvm_size);

  if (self->fw_list_nvm == NULL) {
    self->init_failed = true;
    log_critical(LOG_PREFIX "NVM FW list allocation failed (elem=%d)" NL,
                 self->elem_index);
    return;
  }

  // Allocate the array of pointers to FW list elements at initialization time
  // to avoid reallocation at runtime
  // Note: size of pointers are not significant compared to the elements
  self->fw_list = sl_calloc(max_fw_list_length, sizeof(self->fw_list[0]));

  if (self->fw_list == NULL) {
    self->init_failed = true;
    log_critical(LOG_PREFIX "FW list allocation failed (elem=%d)" NL,
                 self->elem_index);
    return;
  }

  size_t fw_list_nvm_size = max_fw_list_nvm_size;
  sc = app_btmesh_nvm_init();
  if (SL_STATUS_OK == sc) {
    // The NVM provides the size of the read data which can be less than the
    // maximum length of firmware list because only the actual firmware list
    // elements are written into the NVM at upload
    sc = app_btmesh_nvm_read(SL_BTMESH_FW_DIST_SERVER_FW_LIST_NVM_KEY_CFG_VAL,
                             self->fw_list_nvm,
                             &fw_list_nvm_size);

    if (SL_STATUS_WOULD_OVERFLOW == sc) {
      log_error(LOG_PREFIX
                "NVM FW list size is too high (elem=%d,fw_list_nvm_size=0x%X,"
                "max_fw_list_nvm_size=0x%X)" NL,
                self->elem_index,
                fw_list_nvm_size,
                max_fw_list_nvm_size);
      // The FW list could not be constructed so set the length to zero in order
      // to execute fw_invalidate_all properly because there is no allocated entry
      // in the FW list.
      self->fw_list_nvm->current_fw_list_length = 0;

      // The NVM content could not fit into the allocated NVM FW list RAM object
      // if a new bootloader is flashed (OTA or debugger) with less storage slots.
      // The best strategy is to invalidate every firmware because the FW list
      // can't be restored and it might happen that the storage slot sizes are
      // modified as well.
      // The initiator can expect that after a distributor FW update the
      // firmware list might not be valid anymore.
      // Note: It is important to use invalidate all instead of delete all because
      //       the former is faster (flash write vs erase). The Distribution Server
      //       SDK component is initialized when the device is provisioned or when
      //       the previously provisioned node is initialized (after reset).
      //       A delete all operation in the BLOB storage could lead to
      //       configuration timeout because a device is usually configured just
      //       after the provisioning was completed.
      (void) fw_invalidate_all(self);

      // If the invalidation was successful then the FW list is empty so it does
      // not make sense to continue the FW list initialization. If the invalidation
      // failed then something went terribly wrong so the fw_invalidate_all sets the
      // storage corrupted flag and the FW list initialization shall be terminated.
      return;
    }
  }

  if (SL_STATUS_OK != sc) {
    // This could be the correct behavior if no firmware was uploaded to the
    // distributor since the last mass erase.
    self->fw_list_nvm->current_fw_list_length = 0;

    log_status_info_f(sc,
                      LOG_PREFIX "No FW list found in NVM (elem=%d)" NL,
                      self->elem_index);

    // If the NVM data is deleted externally then some leaked BLOB might remain
    // in the BLOB storage which belongs to the Distribution Server.
    // If there isn't any NVM data then no BLOB shall remain in the BLOB storage
    // so all BLOBs can be removed from BLOB storage which are owned by the
    // Distribution Server SW component.
    (void) fw_invalidate_all(self);
    return;
  }

  // Calculate the minimum size of firmware list in NVM based on the firmware
  // list length information stored in the NVM object itself
  size_t min_fw_list_nvm_size;
  if (fw_list_nvm_size < sizeof(fw_dist_server_fw_list_nvm_t)) {
    min_fw_list_nvm_size = sizeof(fw_dist_server_fw_list_nvm_t);
  } else {
    min_fw_list_nvm_size = sizeof(fw_dist_server_fw_list_nvm_t)
                           + self->fw_list_nvm->current_fw_list_length
                           * sizeof(sl_bt_uuid_64_t);
  }

  // Check if the size of NVM object is consistent with the length of the
  // firmware list stored in the NVM object itself
  if ((max_fw_list_nvm_size < fw_list_nvm_size)
      || (fw_list_nvm_size < min_fw_list_nvm_size)) {
    log_error(LOG_PREFIX
              "FW list is corrupted in NVM (elem=%d,fw_list_nvm_size=0x%X,"
              "min_fw_list_nvm_size=0x%X,max_fw_list_nvm_size=0x%X)" NL,
              self->elem_index,
              fw_list_nvm_size,
              min_fw_list_nvm_size,
              max_fw_list_nvm_size);

    // The FW list could not be constructed so set the length to zero in order
    // to execute fw_invalidate_all properly because there is no allocated entry
    // in the FW list.
    self->fw_list_nvm->current_fw_list_length = 0;

    // This kind of NVM inconsistency should not occur. It could mean somehow
    // the data is corrupted in NVM.
    // Note: If the number of storage slots in the bootloader is decreased then
    //       the NVM read itself fails because the NVM data does not fit into the
    //       allocated NVM fw list buffer.
    (void) fw_invalidate_all(self);

    // If the invalidation was successful then the FW list is empty so it does
    // not make sense to continue the FW list initialization. If the invalidation
    // failed then something went terribly wrong so the fw_invalidate_all sets the
    // storage corrupted flag and the FW list initialization shall be terminated.
    return;
  }

  // FW list is built in RAM based on the NVM FW list and BLOB storage content.
  // The FW Distribution Server checks the consistency between the NVM FW list
  // and BLOB storage and the integrity of these persistent data.
  // Inconsistency or integrity issues may occur when a BLOB id in the NVM list
  // is not present in the BLOB storage or the BLOB is present in the BLOB
  // storage but no FWID information is stored with the BLOB.
  // This kind of inconsistency may occur if a new bootloader is flashed
  // (OTA or debugger) with different storage slot configurations or the NVM
  // content is deleted externally.
  // The inconsistent data is removed from the NVM FW list and from the BLOB
  // storage but the consistent BLOBs are kept and the FW list is built from
  // these entries in RAM.
  // Rationale: It takes long time to upload FW images to the distributor so
  // it can make sense to save all valid entries. This means the the FW list is
  // modified without the knowledge of the Initiator but this happens after a
  // reset only and the initiator shall query the FW list before it starts the
  // firmware distribution procedure.
  // Note: the FW List fails only if allocation error occurs.
  sc = fw_list_build(self);

  if (SL_STATUS_OK != sc) {
    // If the allocation of existing firmware list entries is not possible then
    // the distribution server can't operate
    self->init_failed = true;
    return;
  }

  // Remove leaked BLOBs from BLOB storage to free space in BLOB storage.
  // Note: The fw_storage_cleanup operation assumes that the FW list is valid.
  (void) fw_storage_cleanup(self);

  // The FW list has been constructed successfully so the application shall be
  // notified about the already existing firmware images on the distributor
  for (uint16_t fw_list_idx = 0;
       fw_list_idx < self->fw_list_nvm->current_fw_list_length;
       ++fw_list_idx) {
    fw_dist_server_fw_descriptor_t *fw_descriptor = self->fw_list[fw_list_idx];
    sl_btmesh_fw_distribution_server_on_firmware_added(self->elem_index,
                                                       UNASSIGNED_ADDRESS,
                                                       fw_descriptor->size,
                                                       fw_list_idx,
                                                       fw_list_idx + 1,
                                                       self->capabilities->max_fw_list_length,
                                                       fw_descriptor->fwid,
                                                       fw_descriptor->fwid_length);
  }
}

static sl_status_t fw_list_get_storage_blob_id_by_index(fw_dist_server_t *const self,
                                                        uint16_t fw_list_index,
                                                        sl_bt_uuid_64_t *storage_blob_id)
{
  if ((self->init_failed != false) || (self->storage_corrupted != false)) {
    return SL_STATUS_INVALID_STATE;
  }

  if (self->fw_list_nvm->current_fw_list_length <= fw_list_index) {
    return SL_STATUS_NOT_FOUND;
  }

  memcpy(storage_blob_id,
         &self->fw_list_nvm->blob_ids[fw_list_index],
         sizeof(sl_bt_uuid_64_t));
  return SL_STATUS_OK;
}

static sl_status_t fw_list_get_fw_info_by_index(fw_dist_server_t *const self,
                                                uint16_t fw_list_index,
                                                fw_blob_selector_t blob_selector,
                                                mesh_dfu_dist_server_fw_info_t *fw_info)
{
  fw_dist_server_fw_descriptor_t *fw_descriptor = NULL;

  if ((self->init_failed != false) || (self->storage_corrupted != false)) {
    return SL_STATUS_INVALID_STATE;
  }

  if (self->fw_list_nvm->current_fw_list_length <= fw_list_index) {
    return SL_STATUS_BT_MESH_DOES_NOT_EXIST;
  }

  fw_descriptor = self->fw_list[fw_list_index];

  // The fw_info is not a mandatory parameter because the caller might need only
  // the information if the firmware exists at all
  if (fw_info != NULL) {
    fw_info->size = fw_descriptor->size;
    fw_info->index = fw_list_index;
    fw_info->p_blob_id = (blob_selector == FW_BLOB_SELECTOR_STORAGE)
                         ? self->fw_list_nvm->blob_ids[fw_list_index].data
                         : fw_descriptor->blob_id.data;
    fw_info->p_fwid = fw_descriptor->fwid;
    fw_info->fwid_len = fw_descriptor->fwid_length;
    fw_info->p_metadata = fw_descriptor->metadata;
    fw_info->metadata_len = fw_descriptor->metadata_length;
  }

  return SL_STATUS_OK;
}

static sl_status_t fw_list_get_fw_info_by_fwid(fw_dist_server_t *const self,
                                               const uint8_t *fwid,
                                               uint8_t fwid_length,
                                               fw_blob_selector_t blob_selector,
                                               mesh_dfu_dist_server_fw_info_t *fw_info)
{
  uint16_t fw_list_index;

  if ((self->init_failed != false) || (self->storage_corrupted != false)) {
    return SL_STATUS_INVALID_STATE;
  }

  for (fw_list_index = 0; fw_list_index < self->fw_list_nvm->current_fw_list_length;
       fw_list_index++) {
    if ((self->fw_list[fw_list_index]->fwid_length == fwid_length)
        && (0 == memcmp(self->fw_list[fw_list_index]->fwid, fwid, fwid_length))) {
      break;
    }
  }

  if (self->fw_list_nvm->current_fw_list_length <= fw_list_index) {
    return SL_STATUS_BT_MESH_DOES_NOT_EXIST;
  }

  return fw_list_get_fw_info_by_index(self, fw_list_index, blob_selector, fw_info);
}

static sl_status_t fw_list_append(fw_dist_server_t *const self,
                                  fw_dist_server_fw_descriptor_t *fw_descriptor)
{
  sl_status_t sc;
  if (self->capabilities->max_fw_list_length
      <= self->fw_list_nvm->current_fw_list_length) {
    sc = SL_STATUS_NO_MORE_RESOURCE;
  } else {
    uint16_t fw_list_index = self->fw_list_nvm->current_fw_list_length++;
    self->fw_list[fw_list_index] = fw_descriptor;
    memcpy(&self->fw_list_nvm->blob_ids[fw_list_index],
           &fw_descriptor->blob_id,
           sizeof(sl_bt_uuid_64_t));

    sc = app_btmesh_nvm_write(SL_BTMESH_FW_DIST_SERVER_FW_LIST_NVM_KEY_CFG_VAL,
                              self->fw_list_nvm,
                              FW_LIST_NVM_SIZE(self->fw_list_nvm->current_fw_list_length));
    log_status_error_f(sc,
                       LOG_PREFIX "Failed to save NVM FW list (elem=%d)" NL,
                       self->elem_index);
  }
  return sc;
}

static sl_status_t fw_list_delete_all(fw_dist_server_t *const self)
{
  sl_status_t sc;

  fw_list_free_fw_descriptors(self);

  self->fw_list_nvm->current_fw_list_length = 0;
  sc = app_btmesh_nvm_write(SL_BTMESH_FW_DIST_SERVER_FW_LIST_NVM_KEY_CFG_VAL,
                            self->fw_list_nvm,
                            FW_LIST_NVM_SIZE(self->fw_list_nvm->current_fw_list_length));
  log_status_error_f(sc,
                     LOG_PREFIX "Failed to save NVM FW list (elem=%d)" NL,
                     self->elem_index);
  return sc;
}

static sl_status_t fw_list_delete(fw_dist_server_t *const self,
                                  uint16_t target_fw_list_index)
{
  sl_status_t sc;

  if (target_fw_list_index < self->fw_list_nvm->current_fw_list_length) {
    // The sl_free function handles null pointer like a no-operation
    sl_free(self->fw_list[target_fw_list_index]->metadata);
    sl_free(self->fw_list[target_fw_list_index]);

    for (uint16_t fw_list_idx = target_fw_list_index;
         (fw_list_idx + 1) < self->fw_list_nvm->current_fw_list_length;
         fw_list_idx++) {
      self->fw_list_nvm->blob_ids[fw_list_idx] = self->fw_list_nvm->blob_ids[fw_list_idx + 1];
      self->fw_list[fw_list_idx] = self->fw_list[fw_list_idx + 1];
    }

    // Every FW descriptors above the target index is shifted to the beginning
    // of the FW list so the last position is empty so it can be set to NULL
    self->fw_list[self->fw_list_nvm->current_fw_list_length - 1] = NULL;

    self->fw_list_nvm->current_fw_list_length--;
    sc = app_btmesh_nvm_write(SL_BTMESH_FW_DIST_SERVER_FW_LIST_NVM_KEY_CFG_VAL,
                              self->fw_list_nvm,
                              FW_LIST_NVM_SIZE(self->fw_list_nvm->current_fw_list_length));
    log_status_error_f(sc,
                       LOG_PREFIX "Failed to save NVM FW list (elem=%d)" NL,
                       self->elem_index);
  } else {
    sc = SL_STATUS_INVALID_PARAMETER;
  }

  return sc;
}

static void sl_btmesh_fw_distribution_server_element_init(uint16_t elem_index)
{
  sl_status_t sc;
  fw_dist_server_t *self;
  uint32_t max_blob_count;
  static fw_dist_server_list_t *tail;

  fw_dist_server_list_t *new_fw_dist_server =
    sl_calloc(1, sizeof(struct fw_dist_server_list_s));

  if (new_fw_dist_server == NULL) {
    app_assert(new_fw_dist_server != NULL,
               "Allocation of distribution server list failed!");
    // If the asserts are turned off then the initialization shall not be
    // continued because the NULL pointer could be dereferenced
    // Note: SERVER_STATUS_CHECK macro makes sure that the NULL pointer is not
    //       dereferenced at other entry points of the component
    return;
  }

  // If no server has been initialized, create list head
  if (fw_dist_server_list == NULL) {
    fw_dist_server_list = new_fw_dist_server;
    tail = fw_dist_server_list;
  } else {
    // If head is present (implies tale is valid), create new tail
    tail->next = new_fw_dist_server;
    tail = tail->next;
  }
  // Initialize tail
  tail->next = NULL;
  self = &tail->server;

  self->elem_index = elem_index;
  self->storage_corrupted = false;
  self->init_failed = false;

  self->async_req_client_address = UINT16_MAX;
  self->deleting = false;
  self->deleting_fwid_len = 0;
  self->deleting_fwid = NULL;
  self->deleting_all = false;

  // Future proofing, if multiple instances of storage interfaces are used
  self->capabilities = &fw_dist_server_capabilities;

  // There is no use case, that the blob storage should be able to store more
  // than 65535 blobs inside an EFR32 MCU.
  max_blob_count = sl_btmesh_blob_storage_get_max_blob_count();
  self->capabilities->max_fw_list_length =
    (max_blob_count < 0xFFFF) ? max_blob_count : 0xFFFF;

  // The max_fw_list_length capability shall be set because it is used to
  // calculate the max_upload_space
  self->capabilities->max_upload_space = calc_fw_storage_max_upload_space(self);
  self->capabilities->max_fw_image_size = calc_fw_storage_max_fw_image_size();

  // It does not make sense to use Distributor if it is not able to store at
  // least one firmware in the BLOB storage.
  // Note: the return value of the functions, which provide this data is set
  //       to zero if an error is encountered.
  app_assert(0 < self->capabilities->max_fw_list_length,
             "Max BLOB count is zero.");
  app_assert(0 < self->capabilities->max_upload_space,
             "Max upload space is zero.");
  app_assert(0 < self->capabilities->max_fw_image_size,
             "Max firmware size is zero.");

  upload_init(self);
  dist_init(self);
  fw_list_init(self);

  sc = sl_btmesh_fw_dist_server_init(BTMESH_FW_DISTRIBUTION_SERVER_GROUP_MAIN_ELEM_INDEX,
                                     SL_BTMESH_FW_DIST_SERVER_MAX_NODE_LIST_SIZE_CFG_VAL,
                                     self->capabilities->max_fw_list_length,
                                     self->capabilities->max_fw_image_size,
                                     self->capabilities->max_upload_space,
                                     SL_BTMESH_FW_DIST_SERVER_MULTICAST_THRESHOLD_DEFAULT_CFG_VAL,
                                     0,
                                     NULL);

  app_assert_status_f(sc, "Failed to init FW Distribution Server");

  sl_btmesh_fw_distribution_server_on_distribution_state_changed(self->elem_index,
                                                                 self->dist.state,
                                                                 self->dist.num_active_nodes,
                                                                 self->dist.node_count);
}

static void sl_btmesh_fw_distribution_server_init(void)
{
  sl_btmesh_fw_distribution_server_element_init(BTMESH_FW_DISTRIBUTION_SERVER_GROUP_MAIN_ELEM_INDEX);
}

static void dist_reset_node_counters(fw_dist_server_t *const self)
{
  self->dist.node_count = 0;
  self->dist.num_active_nodes = 0;
}

static void dist_super_state_idle_entry(fw_dist_server_t *const self)
{
  self->dist.blob_transfer_started = false;
  self->dist.retry_time_elapsed = false;
  self->dist.retry_counter = 0;
}

static void dist_init(fw_dist_server_t *const self)
{
  self->dist.state = sl_btmesh_fw_dist_server_dist_step_idle;
  self->dist.fw_list_index = 0xFFFF;
  self->dist.fw_size = 0;
  memset(&self->dist.storage_blob_id, 0, sizeof(self->dist.storage_blob_id));

  dist_reset_node_counters(self);
  dist_super_state_idle_entry(self);
}

static void handle_nodes_added(
  const sl_btmesh_evt_fw_dist_server_nodes_added_t *const evt)
{
  fw_dist_server_t *self = find_server(evt->elem_index);
  SERVER_STATUS_CHECK(self);
  if (0 != dist_state_flags[self->dist.state].idle) {
    // The BT Mesh stack filters those nodes from the Firmware Distribution
    // Receivers Add message which are already present in the distribution
    // receivers list (remove duplicates).
    // The BT Mesh stack also checks remaining new nodes after the filtering, if
    // there is sufficient space for the new nodes in the receivers list.
    if ((self->dist.node_count + evt->num_added_nodes)
        <= SL_BTMESH_FW_DIST_SERVER_MAX_NODE_LIST_SIZE_CFG_VAL) {
      for (uint8_t idx = 0; (idx + 2) < evt->added_nodes.len; idx += 3) {
        // Access layer messages are little endian
        uint16_t server_address = (evt->added_nodes.data[idx + 1] << 8)
                                  | evt->added_nodes.data[idx];
        uint8_t update_fw_image_idx = evt->added_nodes.data[idx + 2];

        self->dist.node_count++;

        // Inform the application about the added receiver nodes to list
        sl_btmesh_fw_distribution_server_on_node_added(self->elem_index,
                                                       server_address,
                                                       update_fw_image_idx,
                                                       self->dist.node_count);
        log_info(LOG_PREFIX
                 "node is added to distribution list "
                 "(elem=%d,claddr=0x%04X,node_addr=0x%04X,node_cnt=%d)" NL,
                 evt->elem_index,
                 evt->client_address,
                 server_address,
                 self->dist.node_count);
      }
    } else {
      log_debug(LOG_PREFIX
                "space is not sufficient in node list "
                "(elem=%d,claddr=0x%04X,list_max=%d,list_cur=%d,list_add=%d)" NL,
                evt->elem_index,
                evt->client_address,
                SL_BTMESH_FW_DIST_SERVER_MAX_NODE_LIST_SIZE_CFG_VAL,
                self->dist.node_count,
                evt->num_added_nodes);
    }
  } else {
    // This should not happen based on the state machine in the BT Mesh stack.
    // If the event is not received in the expected state then it is ignored
    // and a log message is emitted.
    log_debug(LOG_PREFIX "unexpected Nodes Added event (elem=%d,state=%d)" NL,
              self->elem_index,
              self->dist.state);
  }
}

static void handle_nodes_deleted(
  const sl_btmesh_evt_fw_dist_server_nodes_deleted_t *const evt)
{
  fw_dist_server_t *self = find_server(evt->elem_index);
  SERVER_STATUS_CHECK(self);
  if (0 != dist_state_flags[self->dist.state].idle) {
    dist_reset_node_counters(self);

    sl_btmesh_fw_distribution_server_on_all_nodes_deleted(evt->elem_index);

    log_info(LOG_PREFIX "all nodes are deleted from distribution list "
                        "(elem=%d,claddr=0x%04X)" NL,
             evt->elem_index,
             evt->client_address);
  } else {
    // This should not happen based on the state machine in the BT Mesh stack.
    // If the event is not received in the expected state then it is ignored
    // and a log message is emitted.
    log_debug(LOG_PREFIX "unexpected Nodes Deleted event (elem=%d,state=%d)" NL,
              self->elem_index,
              self->dist.state);
  }
}

static void handle_dist_start_request(
  const sl_btmesh_evt_fw_dist_server_dist_start_req_t *const evt)
{
  sl_status_t sc_fw_info, sc_storage_blob_id, sc_dist_start_rsp;
  mesh_dfu_dist_server_fw_info_t fw_info;
  sl_btmesh_fw_dist_server_dist_status_t dist_status =
    sl_btmesh_fw_dist_server_dist_status_internal_error;

  fw_dist_server_t *self = find_server(evt->elem_index);
  SERVER_STATUS_CHECK(self);

  if (self->storage_corrupted != false) {
    // If the storage is corrupted then the distribution start request is
    // rejected with internal error
  } else if (0 != dist_state_flags[self->dist.state].idle) {
    // Store transfer mode because it shall be provided for BLOB Transfer Client
    // when the BLOB transfer is started
    self->dist.transfer_mode = (sl_btmesh_mbt_client_transfer_mode_t) evt->transfer_mode;

    // It is not necessary to store client and group addresses, ttl,
    // apply_immediately and timeout_base event parameters, because these are
    // used by and stored in the BT Mesh stack. Furthermore these are not
    // necessary in application level logic, but from diagnostic point of view
    // it can be useful, so these event parameters are logged.
    log_info(LOG_PREFIX
             "Distribution Start message is received "
             "(elem=%d,claddr=0x%04X,graddr=0x%04X,ttl=%d,policy=%d,fw_list_idx=%d,"
             "timeout_base=%d,tf_mode=%s)" NL,
             evt->elem_index,
             evt->client_address,
             evt->group_address,
             evt->ttl,
             evt->apply_immediately,
             evt->fw_list_index,
             evt->timeout_base,
             sl_btmesh_blob_transfer_client_transfer_mode_to_string(self->dist.transfer_mode));

    // The state is changed only in the State Changed event, which is expected
    // to be triggered after this event immediately
    self->dist.fw_list_index = evt->fw_list_index;

    self->dist.num_active_nodes = self->dist.node_count;

    // The FW list is created at initialization time from NVM FW list data with
    // storage BLOB IDs and firmware list length and from BLOB storage data with
    // firmware ID and metadata. The FW list is managed by adding new firmware
    // data at upload complete and removing firmware data at firmware delete so
    // the FW list is in sync with data in NVM and BLOB storage.
    sc_fw_info = fw_list_get_fw_info_by_index(self,
                                              evt->fw_list_index,
                                              FW_BLOB_SELECTOR_CURRENT,
                                              &fw_info);

    sc_storage_blob_id = fw_list_get_storage_blob_id_by_index(self,
                                                              evt->fw_list_index,
                                                              &self->dist.storage_blob_id);

    if ((SL_STATUS_OK != sc_fw_info) || (SL_STATUS_OK != sc_storage_blob_id)) {
      // It was not possible to determine the firmware info which belongs to the
      // firmware list index, therefore it is meaningless to continue
      // Internal error is passed to BT Mesh stack in distribution start response
      log_status_error_f((SL_STATUS_OK != sc_fw_info) ? (unsigned int)sc_fw_info : (unsigned int)sc_storage_blob_id,
                         LOG_PREFIX
                         "Distribution Start failed due failed fw lookup "
                         "(elem=%u,fw_list_idx=%u)" NL,
                         evt->elem_index,
                         evt->fw_list_index);
    } else {
      sl_status_t sc_gen_blob_id;
      sl_bt_uuid_64_t *dist_blob_id = &self->fw_list[evt->fw_list_index]->blob_id;

      log_debug(LOG_PREFIX "Distribution Start request (fwid=");
      log_fwid_level(APP_LOG_LEVEL_DEBUG,
                     fw_info.p_fwid,
                     fw_info.fwid_len,
                     SL_BTMESH_FW_DIST_SERVER_FWID_METADATA_LOG_FORMAT_HEX);
      log_append_debug(",metadata=");
      log_metadata_level(APP_LOG_LEVEL_DEBUG,
                         fw_info.p_metadata,
                         fw_info.metadata_len,
                         SL_BTMESH_FW_DIST_SERVER_FWID_METADATA_LOG_FORMAT_HEX);
      log_append_debug(")" NL);

      // The distribution procedure can be started so success status is passed
      // to BT Mesh stack in distribution start response
      dist_status = sl_btmesh_fw_dist_server_dist_status_success;
      sc_gen_blob_id = sl_btmesh_fw_distribution_server_generate_blob_id(dist_blob_id);
      if (sc_gen_blob_id != SL_STATUS_OK) {
        *dist_blob_id = self->dist.storage_blob_id;
      }

      sl_btmesh_fw_dist_server_dfu_policy_t update_policy =
        (sl_btmesh_fw_dist_server_dfu_policy_t) evt->apply_immediately;

      // Call distribution started application callback to inform the application.
      // The distribution started callback shall be called before the distribution
      // start response (sl_btmesh_fw_dist_server_dist_start_rsp) BT Mesh stack
      // API is called in order to make it possible to set the multicast threshold
      // value for the current distribution.
      sl_btmesh_fw_distribution_server_on_distribution_started(evt->elem_index,
                                                               evt->client_address,
                                                               evt->group_address,
                                                               evt->ttl,
                                                               update_policy,
                                                               evt->fw_list_index,
                                                               evt->timeout_base,
                                                               self->dist.transfer_mode,
                                                               self->dist.node_count);
    }
  } else {
    // This should not happen based on the state machine in the BT Mesh stack.
    // If the event is not received in the expected state then it is ignored
    // and a log message is emitted
    // Internal error is passed to BT Mesh stack in distribution start response
    log_debug(LOG_PREFIX
              "unexpected Distribution Start Request event (elem=%d,state=%d)" NL,
              self->elem_index,
              self->dist.state);
  }

  // Respond to distribution start request with status information which
  // indicates that the request is accepted or rejected
  sc_dist_start_rsp = sl_btmesh_fw_dist_server_dist_start_rsp(self->elem_index,
                                                              dist_status);
  log_status_error_f(sc_dist_start_rsp,
                     LOG_PREFIX "Distribution Start response failed (elem=%d)" NL,
                     self->elem_index);
}

static void handle_dist_cancel(
  const sl_btmesh_evt_fw_dist_server_dist_cancel_t *const evt)
{
  fw_dist_server_t *self = find_server(evt->elem_index);
  SERVER_STATUS_CHECK(self);

  // The FW distribution server SDK component state transitions are triggered
  // by sl_btmesh_evt_fw_dist_server_dist_state_changed BT Mesh stack events.
  // The cancel event is logged and application callback is called to provide
  // client address information to the application.
  log_info(LOG_PREFIX "Distribution canceled (elem=%d,claddr=0x%04X)" NL,
           evt->elem_index,
           evt->client_address);
  sl_btmesh_fw_distribution_server_on_distribution_canceled(evt->elem_index,
                                                            evt->client_address);

  if (sl_btmesh_fw_dist_server_dist_step_transferring_image == self->dist.state) {
    sl_status_t sc = sl_btmesh_blob_transfer_client_on_aborted(evt->elem_index);
    log_status_error_f(sc,
                       LOG_PREFIX "BLOB Transfer Client abort error (elem=%d)" NL,
                       self->elem_index);
  }
}

static void handle_dist_suspend(
  const sl_btmesh_evt_fw_dist_server_dist_suspend_t *const evt)
{
  fw_dist_server_t *self = find_server(evt->elem_index);
  SERVER_STATUS_CHECK(self);

  if (sl_btmesh_fw_dist_server_dist_step_transferring_image == self->dist.state) {
    log_info(LOG_PREFIX "Distribution suspended (elem=%d,claddr=0x%04X)" NL,
             evt->elem_index,
             evt->client_address);

    sl_btmesh_fw_distribution_server_on_distribution_suspended(evt->elem_index,
                                                               evt->client_address);
  } else {
    // This should not happen based on the state machine in the BT Mesh stack.
    // If the event is not received in the expected state then it is ignored
    // and a log message is emitted.
    log_debug(LOG_PREFIX
              "unexpected Distribution Suspend event (elem=%d,state=%d)" NL,
              self->elem_index,
              self->dist.state);
  }
}

static void handle_dist_resume_request(
  const sl_btmesh_evt_fw_dist_server_resume_req_t *const evt)
{
  fw_dist_server_t *self = find_server(evt->elem_index);
  SERVER_STATUS_CHECK(self);

  sl_btmesh_fw_dist_server_dfu_policy_t update_policy =
    (sl_btmesh_fw_dist_server_dfu_policy_t) evt->update_policy;

  sl_btmesh_fw_dist_server_dist_status_t dist_status =
    sl_btmesh_fw_dist_server_dist_status_internal_error;

  if (sl_btmesh_fw_dist_server_dist_step_suspended == self->dist.state) {
    log_info(LOG_PREFIX
             "Distribution resumed (elem=%d,claddr=0x%04X,graddr=0x%04X,ttl=%d,"
             "policy=%d,fw_list_idx=%d,timeout_base=%d,tf_mode=%s)" NL,
             evt->elem_index,
             evt->client_address,
             evt->group_address,
             evt->ttl,
             evt->update_policy,
             evt->fw_index,
             evt->timeout_base,
             sl_btmesh_blob_transfer_client_transfer_mode_to_string(self->dist.transfer_mode));
    sl_btmesh_fw_distribution_server_on_distribution_resumed(evt->elem_index,
                                                             evt->client_address,
                                                             evt->group_address,
                                                             evt->ttl,
                                                             update_policy,
                                                             evt->fw_index,
                                                             evt->timeout_base,
                                                             self->dist.transfer_mode,
                                                             self->dist.node_count);
    dist_status = sl_btmesh_fw_dist_server_dist_status_success;
  } else {
    // This should not happen based on the state machine in the BT Mesh stack.
    // If the event is not received in the expected state then log message is
    // emitted and resume response is called with internal error.
    log_debug(LOG_PREFIX
              "unexpected Distribution Resume event (elem=%d,state=%d)" NL,
              self->elem_index,
              self->dist.state);
  }

  sl_status_t sc = sl_btmesh_fw_dist_server_resume_rsp(evt->elem_index,
                                                       dist_status);
  log_status_error_f(sc,
                     LOG_PREFIX "Distribution resume response failed (elem=%d)" NL,
                     evt->elem_index);
}

static void handle_dist_state_changed(
  const sl_btmesh_evt_fw_dist_server_dist_state_changed_t *const evt)
{
  fw_dist_server_t *self = find_server(evt->elem_index);
  SERVER_STATUS_CHECK(self);

  if (0 != dist_state_flags[self->dist.state].idle) {
    self->dist.num_active_nodes = evt->num_active_nodes;
  }
  sl_btmesh_fw_distribution_server_on_distribution_state_changed(self->elem_index,
                                                                 (sl_btmesh_fw_dist_server_dist_step_t)evt->state,
                                                                 evt->num_active_nodes,
                                                                 self->dist.node_count);
  dist_state_transition(self, (sl_btmesh_fw_dist_server_dist_step_t)evt->state);
}

static void handle_dist_server_node_failed(
  const sl_btmesh_evt_fw_dist_server_node_failed_t *const evt)
{
  fw_dist_server_t *self = find_server(evt->elem_index);
  SERVER_STATUS_CHECK(self);
  if (0 == dist_state_flags[self->dist.state].idle) {
    self->dist.num_active_nodes--;

    log_info(LOG_PREFIX "node failed phase '%s', status '%s' "
                        "(elem=%d,addr=0x%04X)" NL,
             sl_btmesh_fw_distribution_server_node_phase_to_string((sl_btmesh_fw_dist_server_dist_node_phase_t) evt->update_phase),
             sl_btmesh_fw_distribution_server_firmware_update_status_to_string((sl_btmesh_fw_update_server_update_status_t) evt->update_status),
             evt->elem_index,
             evt->address);

    sl_btmesh_fw_distribution_server_on_distribution_node_failed(evt->elem_index,
                                                                 evt->address,
                                                                 (sl_btmesh_fw_dist_server_dist_node_phase_t) evt->update_phase,
                                                                 (sl_btmesh_fw_update_server_update_status_t) evt->update_status,
                                                                 evt->mbt_status,
                                                                 evt->progress,
                                                                 evt->fw_index,
                                                                 self->dist.num_active_nodes,
                                                                 self->dist.node_count);
  } else {
    // This should not happen based on the state machine in the BT Mesh stack.
    // If the event is not received in the expected state then it is ignored
    // and a log message is emitted.
    log_debug(LOG_PREFIX
              "unexpected Node Failed event (elem=%d,state=%d)" NL,
              self->elem_index,
              self->dist.state);
  }
}

static sl_status_t delete_firmware(fw_dist_server_t *self,
                                   uint16_t target_fw_list_index)
{
  // This function expects valid FW list index so the caller shall validate it
  // and therefore only an assert is added here
  app_assert_s(target_fw_list_index < self->fw_list_nvm->current_fw_list_length);
  sl_status_t sc_storage, sc_fw_list;

  // If it is not possible to invalidate the blob in the blob storage due to
  // an error, then the implementation tries to erase the flash pages where
  // the BLOB is stored.
  // Note: The erase is very slow 5s/10s for 1024kB Internal / SPI flash
  sl_bt_uuid_64_t *storage_blob_id = &self->fw_list_nvm->blob_ids[target_fw_list_index];
  sc_storage = sl_btmesh_blob_storage_delete_start(storage_blob_id);

  // The BLOB is deleted from the firmware list as well
  sc_fw_list = fw_list_delete(self, target_fw_list_index);

  if ((SL_STATUS_OK != sc_storage) || (SL_STATUS_OK != sc_fw_list)) {
    self->storage_corrupted = true;
    log_status_error_f(sc_storage,
                       LOG_PREFIX
                       "BLOB storage delete failed (elem=%d,blobid=%s)" NL,
                       self->elem_index,
                       BLOB_ID_TO_STRING(storage_blob_id));

    log_status_error_f(sc_fw_list,
                       LOG_PREFIX
                       "FW list delete failed (elem=%d,blobid=%s)" NL,
                       self->elem_index,
                       BLOB_ID_TO_STRING(storage_blob_id));
  }

  return (SL_STATUS_OK != sc_storage) ? sc_storage : sc_fw_list;
}

static bool upload_is_empty_space_sufficient(fw_dist_server_t *const self,
                                             uint32_t fwsize)
{
  uint32_t max_fw_image_size_free, remaining_upload_space;

  max_fw_image_size_free = calc_fw_storage_max_fw_image_size_free();
  remaining_upload_space = calc_fw_storage_remaining_upload_space(self);

  return (fwsize <= max_fw_image_size_free) && (fwsize <= remaining_upload_space);
}

static void handle_upload_start_metadata(
  const sl_btmesh_evt_fw_dist_server_upload_start_metadata_t *const evt)
{
  fw_dist_server_t *self = find_server(evt->elem_index);
  SERVER_STATUS_CHECK(self);

  // If upload is in progress then the event shall be ignored
  if (0 != upload_state_flags[self->upload.state].idle) {
    self->upload.temp_metadata = NULL;
    self->upload.temp_metadata_length = 0;
    self->upload.metadata_error = false;
    self->upload.managed_blob_error = false;

    // It is not necessary to check the upper limit of the metadata length as
    // it is stored in an 8 bit variable so it can't be greater than 255
    if (0 < evt->metadata.len) {
      // The firmware metadata shall be stored at the beginning of the upload
      // in order to reject the BT Mesh stack upload request with internal
      // error if the dynamic memory allocation of metadata fails
      self->upload.temp_metadata = sl_malloc(evt->metadata.len);
      if (self->upload.temp_metadata != NULL) {
        memcpy(self->upload.temp_metadata, evt->metadata.data, evt->metadata.len);
        self->upload.temp_metadata_length = evt->metadata.len;
      } else {
        self->upload.metadata_error = true;
        log_error(LOG_PREFIX "Upload metadata allocation failed (elem=%d)" NL,
                  self->elem_index);
      }
    }
  } else {
    // This should not happen based on the state machine in the BT Mesh stack.
    // If the event is not received in the expected state then it is ignored
    // and a log message is emitted.
    log_debug(LOG_PREFIX "unexpected Upload Start Metadata event "
                         "(elem=%d,state=%d)" NL,
              self->elem_index,
              self->upload.state);
  }
}

static sl_status_t upload_is_start_req_valid(
  const sl_btmesh_evt_fw_dist_server_upload_start_req_t *const evt)
{
  fw_dist_server_t *self = find_server(evt->elem_index);
  sl_status_t sc;
  sl_bt_uuid_64_t blob_id;

  // The BLOB storage and the FW list in the NVM was detected as inconsistent
  // at startup, previous upload or delete firmware commands failed during
  // BLOB storage, or NVM3 write operation.
  if (false != self->storage_corrupted) {
    log_error(LOG_PREFIX "Upload failed due to storage corrupted (elem=%d)" NL,
              evt->elem_index);
    return SL_STATUS_FAIL;
  }

  // The metadata is received in the same Firmware Distribution Upload Start
  // message, but it is passed in a different event (upload start metadata) due
  // to BGAPI limitations. (one variable length array per message)
  // It is guaranteed, that the upload start metadata event is received first
  // and the upload started event afterwards.
  if (self->upload.metadata_error != false) {
    log_error(LOG_PREFIX "Upload with invalid metadata (elem=%d)" NL,
              evt->elem_index);
    return SL_STATUS_NULL_POINTER;
  }

  // The firmware id does not fit into the allocated array or the length of the
  // firmware id (mandatory) is zero, then error is returned.
  if ((0 == evt->fwid.len)
      || (DFU_FWID_MAX_LEN < evt->fwid.len)) {
    log_error(LOG_PREFIX "Upload with invalid FW id (elem=%d)" NL,
              evt->elem_index);
    return SL_STATUS_INVALID_RANGE;
  }

  // If there is not enough space to store the firmware binary, then an error is
  // returned. This should not happen because the distribution client can query
  // the available space before the upload procedure.
  if (false == upload_is_empty_space_sufficient(self, evt->size)) {
    log_error(LOG_PREFIX
              "Upload failed due to lack of free space "
              "(elem=%d,fw_size=0x%lX,rem_space=0x%lX,max_space=0x%lX,max_fw_size=0x%lX)" NL,
              evt->elem_index,
              evt->size,
              calc_fw_storage_remaining_upload_space(self),
              self->capabilities->max_upload_space,
              calc_fw_storage_max_fw_image_size_free());
    return SL_STATUS_NO_MORE_RESOURCE;
  }

  if (self->capabilities->max_fw_list_length
      <= self->fw_list_nvm->current_fw_list_length) {
    log_error(LOG_PREFIX "Upload failed due to full firmware list "
                         "(elem=%d,fw_list_len=%d)" NL,
              evt->elem_index,
              self->capabilities->max_fw_list_length);
    return SL_STATUS_NO_MORE_RESOURCE;
  }

  // Check if the firmware is already stored in the BLOB storage. However, the
  // BT Mesh stack should not start the upload and notify this component, if the
  // firmware is already present on the device, so this would mean there is some
  // inconsistency between the NVM firmware list and BLOB storage.
  sc = sl_btmesh_blob_storage_get_blob_id_by_footer(BLOB_STORAGE_APP_ID_DFU_FWID,
                                                    evt->fwid.data,
                                                    evt->fwid.len,
                                                    &blob_id);

  // The get function returns SL_STATUS_OK, if the firmware ID is found.
  // If the firmware ID already exists, then an error code is returned and the
  // upload is rejected and a warning is emitted.
  // The initiator can delete all firmware images to start again.
  if (SL_STATUS_OK == sc) {
    log_error(LOG_PREFIX "Upload failed due to firmware id already exists (elem=%d)" NL,
              evt->elem_index);
    sc = SL_STATUS_ALREADY_EXISTS;
  }

  return SL_STATUS_OK;
}

static void handle_upload_start_request(
  const sl_btmesh_evt_fw_dist_server_upload_start_req_t *const evt)
{
  sl_btmesh_fw_dist_server_dist_status_t upload_status =
    sl_btmesh_fw_dist_server_dist_status_internal_error;

  fw_dist_server_t *self = find_server(evt->elem_index);
  SERVER_STATUS_CHECK(self);

  // From the FW Distribution Server SDK component perspective there is no
  // difference between new and resumed upload because the BT Mesh stack emits
  // the very same sl_btmesh_evt_fw_dist_server_upload_start_metadata and
  // sl_btmesh_evt_fw_dist_server_upload_start_req events.
  // If the BT Mesh stack detects that a BLOB transfer was suspended with the
  // same BLOB ID received in FW DIST UPLOAD START message then it considers it
  // as a resume and it does not start a new BLOB transfer which means the BLOB
  // progress is preserved in the BT Mesh stack.

  // If an upload is already in progress then ignore the new request
  if (0 != upload_state_flags[self->upload.state].idle) {
    log_debug(LOG_PREFIX "Upload start request (fwid=");
    log_fwid_level(APP_LOG_LEVEL_DEBUG,
                   evt->fwid.data,
                   evt->fwid.len,
                   SL_BTMESH_FW_DIST_SERVER_FWID_METADATA_LOG_FORMAT_HEX);
    log_append_debug(",metadata=");
    log_metadata_level(APP_LOG_LEVEL_DEBUG,
                       self->upload.temp_metadata,
                       self->upload.temp_metadata_length,
                       SL_BTMESH_FW_DIST_SERVER_FWID_METADATA_LOG_FORMAT_HEX);
    log_append_debug(")" NL);

    sl_status_t sc_upload_valid = upload_is_start_req_valid(evt);

    if (SL_STATUS_OK == sc_upload_valid) {
      self->upload.fw_descriptor = sl_malloc(FW_DESCRIPTOR_SIZE(evt->fwid.len));
      if (self->upload.fw_descriptor != NULL) {
        self->upload.fw_descriptor->size = evt->size;
        self->upload.fw_descriptor->blob_id = evt->blob_id;
        memcpy(self->upload.fw_descriptor->fwid, evt->fwid.data, evt->fwid.len);
        self->upload.fw_descriptor->fwid_length = evt->fwid.len;
        self->upload.fw_descriptor->metadata = self->upload.temp_metadata;
        self->upload.fw_descriptor->metadata_length = self->upload.temp_metadata_length;
        upload_status = sl_btmesh_fw_dist_server_dist_status_success;
        upload_state_transition(self, UPLOAD_STATE_TRANSFER_ACTIVE);
      } else {
        log_error(LOG_PREFIX "Upload FW descriptor allocation failed (elem=%d)" NL,
                  self->elem_index);
      }
    }

    if (upload_status != sl_btmesh_fw_dist_server_dist_status_success) {
      // If the upload status is not success because metadata error then the
      // temporary metadata pointer is NULL so the sl_free is a no-operation.
      // If the upload status is not success because of invalid upload request
      // the allocation of the FW descriptor is failed then the upload is
      // rejected and the metadata shall be deallocated.
      sl_free(self->upload.temp_metadata);
    }

    // Temporary metadata pointer is no longer necessary because it it was added
    // to the FW descriptor or the upload was rejected and the metadata storage
    // was already deallocated
    self->upload.temp_metadata = NULL;
    self->upload.temp_metadata_length = 0;

    log_info(LOG_PREFIX
             "Upload %s (elem=%d,claddr=0x%04X,fw_size=0x%lX,blobid=%s)" NL,
             (upload_status == sl_btmesh_fw_dist_server_dist_status_success)
             ? "started" : "start rejected",
             evt->elem_index,
             evt->client_address,
             evt->size,
             BLOB_ID_TO_STRING(&evt->blob_id));
  } else {
    // This should not happen based on the state machine in the BT Mesh stack.
    // If the event is not received in the expected state then it is ignored
    // and a log message is emitted.
    log_debug(LOG_PREFIX "unexpected Upload Start event "
                         "(elem=%d,state=%d)" NL,
              self->elem_index,
              self->upload.state);
  }

  sl_status_t sc_upload_rsp = sl_btmesh_fw_dist_server_upload_start_rsp(evt->elem_index,
                                                                        upload_status);
  log_status_error_f(sc_upload_rsp,
                     LOG_PREFIX "Upload start response failed (elem=%d,claddr=0x%04X)" NL,
                     evt->elem_index,
                     evt->client_address);

  if ((sc_upload_rsp != SL_STATUS_OK)
      && (upload_status == sl_btmesh_fw_dist_server_dist_status_success)) {
    // If the upload can be started but the BT Mesh stack upload start response
    // fails then the upload is not started so the upload state machine shall
    // transition to idle state which deallocates the FW descriptor
    upload_state_transition(self, UPLOAD_STATE_TRANSFER_FAILED);
  }
}

static void handle_upload_cancel(
  const sl_btmesh_evt_fw_dist_server_upload_cancel_t *const evt)
{
  fw_dist_server_t *self = find_server(evt->elem_index);
  SERVER_STATUS_CHECK(self);
  // If there is no active transfer then the cancellation event shall be ignored
  if (UPLOAD_STATE_TRANSFER_CANCELED != self->upload.state) {
    log_info(LOG_PREFIX "upload is canceled (elem=%d,claddr=0x%04X)" NL,
             evt->elem_index,
             evt->client_address);

    // The state transition to canceled state deallocates the FW descriptor
    upload_state_transition(self, UPLOAD_STATE_TRANSFER_CANCELED);
  } else {
    // This should not happen based on the state machine in the BT Mesh stack.
    // If the event is not received in the expected state then it is ignored
    // and a log message is emitted.
    log_debug(LOG_PREFIX "unexpected Upload Cancel event "
                         "(elem=%d,state=%d)" NL,
              self->elem_index,
              self->upload.state);
  }
}

static void handle_upload_complete_metadata(
  const sl_btmesh_evt_fw_dist_server_upload_complete_metadata_t *const evt)
{
  fw_dist_server_t *self = find_server(evt->elem_index);
  SERVER_STATUS_CHECK(self);
  sl_status_t sc_metadata_write, sc_managed_flag_write;

  if (0 != upload_state_flags[self->upload.state].idle) {
    // This should not happen based on the state machine in the BT Mesh stack.
    // If the event is not received in the expected state then it is ignored
    // and a log message is emitted.
    log_debug(LOG_PREFIX "unexpected Upload Completed event "
                         "(elem=%d,state=%d)" NL,
              self->elem_index,
              self->upload.state);
    return;
  }

  // Set the managed flag first before metadata and fwid write.
  // If a reset occurs after the managed flag is written but before the fwid is
  // written then the BLOB is not part of the NVM FW list but it is managed by
  // the FW Distribution Server so the storage cleanup at startup will remove
  // this BLOB from BLOB storage.
  // If a reset occurs before the managed flag is written then the BLOB remains
  // unmanaged and the BLOB storage deletes it when it needs space to store new
  // BLOB. It is important that the FWID is not written in this case so it could
  // not cause problems when the FW Distributor Server searches BLOBs by FWID.
  sc_managed_flag_write = sl_btmesh_blob_storage_set_managed(&self->upload.fw_descriptor->blob_id,
                                                             BLOB_STORAGE_OWNER_ID_FW_DIST_SERVER);
  log_status_error_f(sc_managed_flag_write,
                     LOG_PREFIX "Upload failed to write managed flag into BLOB storage "
                                "(elem=%d,blobid=%s)" NL,
                     evt->elem_index,
                     BLOB_ID_TO_STRING(&self->upload.fw_descriptor->blob_id));

  if (SL_STATUS_OK == sc_managed_flag_write) {
    self->upload.managed_blob_error = false;
  } else {
    self->upload.managed_blob_error = true;
  }

  if (0 < evt->metadata.len) {
    sc_metadata_write = sl_btmesh_blob_storage_write_app_footer(&self->upload.fw_descriptor->blob_id,
                                                                &evt->metadata.data[0],
                                                                BLOB_STORAGE_APP_ID_DFU_METADATA,
                                                                evt->metadata.len);
    if (SL_STATUS_OK == sc_metadata_write) {
      self->upload.metadata_error = false;
    } else {
      self->upload.metadata_error = true;
      log_status_error_f(sc_metadata_write,
                         LOG_PREFIX
                         "Upload failed to write metadata into BLOB storage "
                         "(elem=%d,blobid=%s)" NL,
                         evt->elem_index,
                         BLOB_ID_TO_STRING(&self->upload.fw_descriptor->blob_id));
    }
  }
}

static void handle_upload_complete(
  const sl_btmesh_evt_fw_dist_server_upload_complete_t *const evt)
{
  fw_dist_server_t *self = find_server(evt->elem_index);
  SERVER_STATUS_CHECK(self);

  sl_status_t sc_fwid_write;
  sl_status_t sc_fw_list_append = SL_STATUS_FAIL;
  uint16_t fw_list_index;

  if (0 != upload_state_flags[self->upload.state].idle) {
    // This should not happen based on the state machine in the BT Mesh stack.
    // If the event is not received in the expected state then it is ignored
    // and a log message is emitted.
    log_debug(LOG_PREFIX "unexpected Upload Completed event "
                         "(elem=%d,state=%d)" NL,
              self->elem_index,
              self->upload.state);
    return;
  }

  fw_list_index = self->fw_list_nvm->current_fw_list_length;

  sc_fwid_write =
    sl_btmesh_blob_storage_write_app_footer(&evt->blob_id,
                                            &evt->fwid.data[0],
                                            BLOB_STORAGE_APP_ID_DFU_FWID,
                                            evt->fwid.len);
  log_status_error_f(sc_fwid_write,
                     LOG_PREFIX "Upload failed to write fwid into BLOB storage "
                                "(elem=%d,blobid=%s)" NL,
                     evt->elem_index,
                     BLOB_ID_TO_STRING(&evt->blob_id));

  // If any BLOB storage error occurs then the FW list shall not be updated in
  // the NVM in order to avoid invalid entries.
  if ((SL_STATUS_OK == sc_fwid_write)
      && (false == self->upload.managed_blob_error)
      && (false == self->upload.metadata_error)) {
    sc_fw_list_append = fw_list_append(self, self->upload.fw_descriptor);
    log_status_error_f(sc_fw_list_append,
                       LOG_PREFIX "Upload failed to append to firmware list "
                                  "(elem=%d,blobid=%s)" NL,
                       evt->elem_index,
                       BLOB_ID_TO_STRING(&evt->blob_id));
  }

  // FW list append can be successful only if the previous BLOB storage
  // operations were successful as well because sc_fw_list_append is initialized
  // to SL_STATUS_FAIL
  if (SL_STATUS_OK == sc_fw_list_append) {
    // It is essential to NULL the FW descriptor in the upload data structure
    // because the ownership of the descriptor is transferred to the FW list
    // at the end successful upload and the upload state machines deallocates
    // the FW descriptor when it transitions into an idle state (unless it is NULL)
    self->upload.fw_descriptor = NULL;

    sl_btmesh_fw_distribution_server_on_firmware_added(evt->elem_index,
                                                       evt->client_address,
                                                       evt->size,
                                                       fw_list_index,
                                                       self->fw_list_nvm->current_fw_list_length,
                                                       self->capabilities->max_fw_list_length,
                                                       evt->fwid.data,
                                                       evt->fwid.len);
    log_info(LOG_PREFIX
             "Upload completed (elem=%d,claddr=0x%04X,fw_list_idx=%d,"
             "fw_size=0x%lX,blobid=%s)" NL,
             evt->elem_index,
             evt->client_address,
             fw_list_index,
             evt->size,
             BLOB_ID_TO_STRING(&evt->blob_id));

    upload_state_transition(self, UPLOAD_STATE_TRANSFER_SUCCESS);
  } else {
    // If any BLOB storage operation is failed then the FW list is not appended
    // and therefore the NVM data is not updated. If all BLOB storage operations
    // are successful but the FW append was failed then it means the NVM data
    // was not updated in this case as well.
    // The initiator expects that the FW image was uploaded at this point because
    // the BLOB transfer was successful however the necessary data could not be
    // stored persistently in BLOB storage and NVM. The uploaded firmware is
    // appended to the end of list so indexes of other firmwares are not affected.
    // The best strategy is to remove all persistently stored data belonging to
    // the just uploaded firmware in order to restore a consistent state which
    // means that the BLOB shall be invalidated or deleted in the BLOB storage.
    // If the initiator starts the distribution with the new highest index then
    // it receives FW Distribution Status message with "Firmware Not Found" status
    // which describes the problem quite well. If the initiator queries the FW
    // list element by Firmware Get or Firmware Get By Index message then the
    // Firmware Status message indicates that the FW does not exists on the
    // distribution server.
    log_info(LOG_PREFIX
             "BLOB storage recovery (elem=%d,blobid=%s)" NL,
             evt->elem_index,
             BLOB_ID_TO_STRING(&evt->blob_id));

    // Invalidate the BLOB just in case
    sl_status_t sc_invalidate = sl_btmesh_blob_storage_invalidate(&evt->blob_id);

    if (SL_STATUS_OK != sc_invalidate) {
      // As a last resort try to delete the BLOB by erasing the medium
      sl_status_t sc_delete = sl_btmesh_blob_storage_delete(&evt->blob_id);

      if (SL_STATUS_OK != sc_delete) {
        log_status_error_f(sc_delete,
                           LOG_PREFIX "BLOB storage recovery failed"
                                      "(elem=%d,blobid=%s)" NL,
                           evt->elem_index,
                           BLOB_ID_TO_STRING(&evt->blob_id));

        // All recovery method failed so the storage is set to corrupted because
        // persistent data is inconsistent or missing.
        self->storage_corrupted = true;
      }
    }
    upload_state_transition(self, UPLOAD_STATE_TRANSFER_FAILED);
  }
}

static void handle_upload_failed(
  const sl_btmesh_evt_fw_dist_server_upload_failed_t *const evt)
{
  fw_dist_server_t *self = find_server(evt->elem_index);
  SERVER_STATUS_CHECK(self);
  if (0 != upload_state_flags[self->upload.state].idle) {
    // This should not happen based on the state machine in the BT Mesh stack.
    // If the event is not received in the expected state then it is ignored
    // and a log message is emitted.
    log_debug(LOG_PREFIX "unexpected Upload Failed event "
                         "(elem=%d,state=%d)" NL,
              self->elem_index,
              self->upload.state);
    return;
  }

  // The upload process fails if and only if the BLOB Transfer fails.
  // The BLOB ID is written into the BLOB Storage as the last step of the BLOB
  // Transfer by BLOB Transfer Server. The BLOB storage considers a binary valid
  // if its BLOB ID is written into flash and it reuses the space of invalid
  // binaries automatically therefore it is not necessary to delete anything
  // in BLOB storage in case of failed upload.

  log_warning(LOG_PREFIX
              "Upload failed, suspended, or aborted (elem=%d,"
              "claddr=0x%04X,fw_size=0x%lX,blobid=%s)" NL,
              evt->elem_index,
              evt->client_address,
              evt->size,
              BLOB_ID_TO_STRING(&evt->blob_id));

  // The state transition to failed state deallocates the FW descriptor
  upload_state_transition(self, UPLOAD_STATE_TRANSFER_FAILED);
}

static void handle_fw_delete_request(
  const sl_btmesh_evt_fw_dist_server_fw_delete_req_t *const evt)
{
  sl_status_t sc;
  mesh_dfu_dist_server_fw_info_t fw_info;

  fw_dist_server_t *self = find_server(evt->elem_index);
  SERVER_STATUS_CHECK(self);

  log_info(LOG_PREFIX "FW delete request (elem=%d,claddr=0x%04X",
           evt->elem_index,
           evt->client_address);
  log_append_debug(",fwid=");
  log_fwid_level(APP_LOG_LEVEL_DEBUG,
                 evt->fwid.data,
                 evt->fwid.len,
                 SL_BTMESH_FW_DIST_SERVER_FWID_METADATA_LOG_FORMAT_HEX);
  log_append_info(")" NL);

  // Search for firmware information in FW list by fwid
  sc = fw_list_get_fw_info_by_fwid(self,
                                   evt->fwid.data,
                                   evt->fwid.len,
                                   FW_BLOB_SELECTOR_STORAGE,
                                   &fw_info);

  if (SL_STATUS_OK == sc) {
    self->deleting_fwid_len = evt->fwid.len;
    self->deleting_fwid = sl_malloc(self->deleting_fwid_len);

    if (self->deleting_fwid != NULL) {
      memcpy(self->deleting_fwid, evt->fwid.data, self->deleting_fwid_len);

      sc = delete_firmware(self, fw_info.index);
    } else {
      sc = SL_STATUS_ALLOCATION_FAILED;
      log_error(LOG_PREFIX "Memory allocation failed! (elem=%d)" NL,
                self->elem_index);
    }

    if (SL_STATUS_OK == sc) {
      self->deleting = true;
      self->async_req_client_address = evt->client_address;
    } else {
      sc = sl_btmesh_fw_dist_server_delete_rsp(self->elem_index,
                                               sl_btmesh_fw_dist_server_dist_status_internal_error,
                                               evt->fwid.len,
                                               evt->fwid.data);
    }
  } else {
    log_status_error_f(sc,
                       LOG_PREFIX "FW delete failed %s (elem=%d,claddr=0x%04X)" NL,
                       (SL_STATUS_BT_MESH_DOES_NOT_EXIST  == sc)
                       ? "because fwid was not found"
                       : "during fwid search",
                       evt->elem_index,
                       evt->client_address);
  }
}

static void handle_fw_delete_response(fw_dist_server_t *self,
                                      sl_status_t erase_status)
{
  sl_status_t sc;
  sl_btmesh_fw_dist_server_dist_status_t firmware_status =
    sl_btmesh_fw_dist_server_dist_status_internal_error;

  if (SL_STATUS_OK == erase_status) {
    sl_btmesh_fw_distribution_server_on_firmware_deleted(
      self->elem_index,
      self->async_req_client_address,
      self->fw_list_nvm->current_fw_list_length,
      self->capabilities->max_fw_list_length,
      self->deleting_fwid,
      self->deleting_fwid_len);

    log_info(LOG_PREFIX "FW deleted (elem=%d,claddr=0x%04X)" NL,
             self->elem_index,
             self->async_req_client_address);

    firmware_status = sl_btmesh_fw_dist_server_dist_status_success;
  }

  // Respond to firmware delete request with status information
  // The BT Mesh stack sends the Firmware Distribution Firmware Status message
  // with the provided status information to the Distribution Client
  sc = sl_btmesh_fw_dist_server_delete_rsp(self->elem_index,
                                           firmware_status,
                                           self->deleting_fwid_len,
                                           self->deleting_fwid);
  log_status_error_f(sc,
                     LOG_PREFIX "FW delete response failed (elem=%d,claddr=0x%04X)" NL,
                     self->elem_index,
                     self->async_req_client_address);

  self->deleting = false;
  self->async_req_client_address = UINT16_MAX;
  self->deleting_fwid_len = 0;
  sl_free(self->deleting_fwid);
  self->deleting_fwid = NULL;
}

static sl_status_t fw_invalidate_all(fw_dist_server_t *const self)
{
  sl_status_t sc_fw_list, sc_storage;

  // Clear the firmware list in RAM and NVM
  sc_fw_list = fw_list_delete_all(self);

  // Make every BLOB in the BLOB storage invalid which is faster than the delete
  // all operation because the flash is only written and not erased.
  sc_storage = sl_btmesh_blob_storage_invalidate_by_owner(BLOB_STORAGE_OWNER_ID_FW_DIST_SERVER);

  if ((SL_STATUS_OK == sc_storage)
      && (SL_STATUS_OK == sc_fw_list)) {
    // The whole BLOB storage was invalidated and the FW list in the NVM3 was
    // deleted successfully which restores the state of these resources and
    // therefore it fixes storage corruption as well
    self->storage_corrupted = false;

    // The upper layer shall be notified through the following callback
    sl_btmesh_fw_distribution_server_on_all_firmware_deleted(self->elem_index,
                                                             MESH_ADDR_UNASSIGNED,
                                                             self->capabilities->max_fw_list_length);

    log_info(LOG_PREFIX "all FWs are invalidated (elem=%d)" NL,
             self->elem_index);
  } else {
    self->storage_corrupted = true;
    log_status_error_f(sc_storage,
                       LOG_PREFIX "BLOB storage invalidate all failed (elem=%d)" NL,
                       self->elem_index);

    log_status_error_f(sc_fw_list,
                       LOG_PREFIX "FW list delete all failed (elem=%d)" NL,
                       self->elem_index);
  }

  return (sc_fw_list != SL_STATUS_OK) ? sc_fw_list : sc_storage;
}

static void handle_fw_delete_all_request(
  const sl_btmesh_evt_fw_dist_server_fw_delete_all_req_t *const evt)
{
  sl_status_t sc_fw_list, sc_delete_req, sc_delete_rsp;

  fw_dist_server_t *self = find_server(evt->elem_index);
  SERVER_STATUS_CHECK(self);

  if (self->deleting_all) {
    sc_delete_rsp = sl_btmesh_fw_dist_server_delete_all_rsp(self->elem_index,
                                                            sl_btmesh_fw_dist_server_dist_status_internal_error);

    log_status_error_f(sc_delete_rsp,
                       LOG_PREFIX "FW delete all response failed (elem=%d,claddr=0x%04X)" NL,
                       evt->elem_index,
                       evt->client_address);

    return;
  }

  log_info(LOG_PREFIX "FW delete all request (elem=%d,claddr=0x%04X)" NL,
           evt->elem_index,
           evt->client_address);

  sc_fw_list = fw_list_delete_all(self);

  log_status_error_f(sc_fw_list,
                     LOG_PREFIX "FW list delete all failed "
                                "(elem=%d,claddr=0x%04X)" NL,
                     evt->elem_index,
                     evt->client_address);

  // All storage slots are erased in BLOB storage
  // Note: The erase is very slow 5s/10s for 1024kB Internal / SPI flash
  sc_delete_req = sl_btmesh_blob_storage_delete_managed_by_owner_start(BLOB_STORAGE_OWNER_ID_FW_DIST_SERVER);

  log_status_error_f(sc_delete_req,
                     LOG_PREFIX "BLOB storage delete all failed "
                                "(elem=%d,claddr=0x%04X)" NL,
                     evt->elem_index,
                     evt->client_address);

  if (SL_STATUS_OK == sc_fw_list && SL_STATUS_OK == sc_delete_req) {
    self->deleting_all = true;
    self->async_req_client_address = evt->client_address;
  } else {
    sc_delete_rsp = sl_btmesh_fw_dist_server_delete_all_rsp(self->elem_index,
                                                            sl_btmesh_fw_dist_server_dist_status_internal_error);

    log_status_error_f(sc_delete_rsp,
                       LOG_PREFIX "FW delete all response failed (elem=%d,claddr=0x%04X)" NL,
                       evt->elem_index,
                       evt->client_address);
  }
}

static void handle_fw_delete_all_response(fw_dist_server_t *self,
                                          sl_status_t erase_status)
{
  sl_status_t sc_delete_rsp;
  sl_btmesh_fw_dist_server_dist_status_t firmware_status =
    sl_btmesh_fw_dist_server_dist_status_internal_error;

  if ((SL_STATUS_OK == erase_status)) {
    // The whole BLOB storage and the FW list in the NVM3 was deleted successfully
    // which restores the original state of these resources and therefore it fixes
    // storage corruption as well
    self->storage_corrupted = false;

    // All Firmware were deleted so set the status to success
    firmware_status = sl_btmesh_fw_dist_server_dist_status_success;

    // The upper layer shall be notified through the following callback
    sl_btmesh_fw_distribution_server_on_all_firmware_deleted(
      self->elem_index,
      self->async_req_client_address,
      self->capabilities->max_fw_list_length);

    log_info(LOG_PREFIX "all FWs are deleted (elem=%d,claddr=0x%04X)" NL,
             self->elem_index,
             self->async_req_client_address);
  } else {
    self->storage_corrupted = true;
  }

  // Respond to firmware delete all request with status information
  // The BT Mesh stack sends the Firmware Distribution Firmware Status message
  // with the provided status information to the Distribution Client
  sc_delete_rsp = sl_btmesh_fw_dist_server_delete_all_rsp(self->elem_index,
                                                          firmware_status);
  log_status_error_f(sc_delete_rsp,
                     LOG_PREFIX "FW delete all response failed (elem=%d,claddr=0x%04X)" NL,
                     self->elem_index,
                     self->async_req_client_address);

  self->deleting_all = false;
  self->async_req_client_address = UINT16_MAX;
}

static void handle_blob_transfer_client_notification(
  const sl_btmesh_blob_transfer_client_notification_t *const notification)
{
  fw_dist_server_t *const self = find_server(notification->elem_index);
  SERVER_STATUS_CHECK(self);
  app_assert_s(NULL != notification);

  // Ignore BLOB transfer client events in idle substates
  if (0 == dist_state_flags[self->dist.state].idle) {
    if (SL_BTMESH_BLOB_TRANSFER_CLIENT_KIND_PROGRESS == notification->kind) {
      uint32_t confirmed_tx_bytes = notification->params.progress.confirmed_tx_bytes;
      uint32_t blob_size = notification->params.progress.blob_size;

      log_info(LOG_PREFIX "distribution progress (%lu/%lu, %u%%)" NL,
               confirmed_tx_bytes,
               blob_size,
               (unsigned) SL_PROG_TO_PCT_INT(blob_size, confirmed_tx_bytes));

      sl_btmesh_fw_distribution_server_on_distribution_blob_progress_changed(self->elem_index,
                                                                             confirmed_tx_bytes,
                                                                             blob_size,
                                                                             self->dist.node_count);
    }
  } else {
    // This should not happen based on the state machine in the BT Mesh stack.
    // If the event is not received in the expected state then it is ignored
    // and a log message is emitted.
    log_debug(LOG_PREFIX "unexpected BLOB Transfer Client notification "
                         "(elem=%d,state=%d)" NL,
              self->elem_index,
              self->upload.state);
  }
}

static sl_status_t dist_execute_step(fw_dist_server_t *const self)
{
  sl_status_t sc = sl_btmesh_fw_dist_server_execute_distribution_step(self->elem_index);

  if (SL_STATUS_OK == sc) {
    log_info(LOG_PREFIX "execute %s step %s(elem=%d,nodes_active=%d/%d)" NL,
             sl_btmesh_fw_distribution_server_distribution_state_to_string(self->dist.state),
             self->dist.retry_time_elapsed ? "retry " : "",
             self->elem_index,
             self->dist.num_active_nodes,
             self->dist.node_count);
  } else {
    log_status_error_f(sc,
                       LOG_PREFIX
                       "execute %s step %sfailed (elem=%d,nodes_active=%d/%d)" NL,
                       sl_btmesh_fw_distribution_server_distribution_state_to_string(self->dist.state),
                       self->dist.retry_time_elapsed ? "retry " : "",
                       self->elem_index,
                       self->dist.num_active_nodes,
                       self->dist.node_count);
  }
  return sc;
}

static void dist_state_waiting_for_apply_entry(fw_dist_server_t *const self)
{
  (void) self;
  log_info(LOG_PREFIX "waiting for apply (elem=%d,nodes_active=%d/%d)" NL,
           self->elem_index,
           self->dist.num_active_nodes,
           self->dist.node_count);
}

static void dist_state_transferring_image_start(fw_dist_server_t *const self)
{
  sl_status_t sc;

  // It is not necessary to call the sl_btmesh_blob_transfer_client_setup,
  // because the distributor code in BT Mesh stack calls the setup function.
  sc = sl_btmesh_blob_transfer_client_setup_data_provider_blob_storage(self->elem_index,
                                                                       &self->dist.storage_blob_id);
  if (SL_STATUS_OK != sc) {
    log_status_error_f(sc,
                       LOG_PREFIX "BLOB Transfer start failed %s(elem=%d)" NL,
                       "because data provider setup failed ",
                       self->elem_index);
    return;
  }

  sc = sl_btmesh_blob_transfer_client_start(self->elem_index,
                                            self->dist.transfer_mode,
                                            handle_blob_transfer_client_notification);

  if (SL_STATUS_OK != sc) {
    log_status_error_f(sc,
                       LOG_PREFIX "BLOB Transfer start failed %s(elem=%d)" NL,
                       "because blob transfer client start failed ",
                       self->elem_index);
    return;
  }

  self->dist.blob_transfer_started = true;

  log_info(LOG_PREFIX "BLOB Transfer is started (elem=%d,nodes_active=%d/%d)" NL,
           self->elem_index,
           self->dist.num_active_nodes,
           self->dist.node_count);
}

static void dist_state_transferring_image_resume(fw_dist_server_t *const self)
{
  sl_status_t sc = sl_btmesh_blob_transfer_client_on_resumed(self->elem_index);
  log_status_error_f(sc,
                     LOG_PREFIX "BLOB Transfer Client resume error (elem=%d)" NL,
                     self->elem_index);
}

static void dist_log_node_status(fw_dist_server_t *const self,
                                 uint16_t node_idx)
{
  uint16_t address;
  uint8_t  retrieved_phase;
  uint8_t  update_server_status;
  uint8_t  mbt_server_status;
  uint8_t  transfer_progress;
  uint8_t  fw_index;

  sl_status_t sc = sl_btmesh_fw_dist_server_get_node_status_by_index(self->elem_index,
                                                                     node_idx,
                                                                     &address,
                                                                     &retrieved_phase,
                                                                     &update_server_status,
                                                                     &mbt_server_status,
                                                                     &transfer_progress,
                                                                     &fw_index);
  log_status_error_f(sc,
                     LOG_PREFIX "node failed event with non-existing node index "
                                "(elem=%d,index=0x%04X)" NL,
                     self->elem_index,
                     node_idx);
  if (sc == SL_STATUS_OK) {
    log_info(LOG_PREFIX "node status (addr=0x%04X,upd_fw_idx=%d,transfer_progress=%d,"
                        "dist_phase=%d-%s,upd_status=%d-%s,blob_status=%d-%s)" NL,
             address,
             fw_index,
             transfer_progress,
             retrieved_phase,
             sl_btmesh_fw_distribution_server_node_phase_to_string((sl_btmesh_fw_dist_server_dist_node_phase_t)retrieved_phase),
             update_server_status,
             sl_btmesh_fw_distribution_server_firmware_update_status_to_string((sl_btmesh_fw_update_server_update_status_t)update_server_status),
             mbt_server_status,
             sl_btmesh_blob_transfer_client_mbt_status_to_string((sl_btmesh_mbt_server_status_t)mbt_server_status));
  }
}

static void dist_log_all_node_status(fw_dist_server_t *const self)
{
  for (uint16_t node_idx = 0; node_idx < self->dist.node_count; ++node_idx) {
    dist_log_node_status(self, node_idx);
  }
}

static void dist_state_suspended_entry(fw_dist_server_t *const self)
{
  sl_status_t sc = sl_btmesh_blob_transfer_client_on_suspended(self->elem_index);
  log_status_error_f(sc,
                     LOG_PREFIX "BLOB Transfer Client suspend error (elem=%d)" NL,
                     self->elem_index);
}

static void dist_state_completed_entry(fw_dist_server_t *const self)
{
  log_info(LOG_PREFIX "distribution is completed (elem=%d,nodes_active=%d/%d)" NL,
           self->elem_index,
           self->dist.num_active_nodes,
           self->dist.node_count);

  dist_log_all_node_status(self);
}

static void dist_state_failed_entry(fw_dist_server_t *const self)
{
  log_info(LOG_PREFIX "distribution has failed (elem=%d,nodes_active=%d/%d)" NL,
           self->elem_index,
           self->dist.num_active_nodes,
           self->dist.node_count);

  dist_log_all_node_status(self);
}

static void dist_state_idle_entry(fw_dist_server_t *const self)
{
  (void) self;
  log_info(LOG_PREFIX "idle state is entered (elem=%d)" NL,
           self->elem_index);
}

static void dist_state_transition(fw_dist_server_t *const self,
                                  const sl_btmesh_fw_dist_server_dist_step_t target_state)
{
  app_assert_s(target_state < ARRAY_LEN(dist_state_flags));

  sl_btmesh_fw_dist_server_dist_step_t source_state = self->dist.state;
  dist_state_flags_t source_state_flags = dist_state_flags[source_state];
  dist_state_flags_t target_state_flags = dist_state_flags[target_state];

  if (0 != source_state_flags.retry) {
    // If a state with retry support is left then the retry timer is stopped
    dist_stop_retry_timer(self);
  }

  self->dist.state = target_state;

  if ((0 == source_state_flags.idle)
      && (0 != target_state_flags.idle)) {
    // If any of the idle sub-states are entered from a non-idle state, then
    // the idle entry function is called.
    dist_super_state_idle_entry(self);
  }

  if (target_state != source_state) {
    log_debug(LOG_PREFIX "state change to %d-%s (elem=%d)" NL,
              target_state,
              sl_btmesh_fw_distribution_server_distribution_state_to_string(target_state),
              self->elem_index);

    if (0 != target_state_flags.retry) {
      // If a new state with retry support is entered, then the retry counter
      // shall be set to zero, because the retries are counted in each state
      // separately
      self->dist.retry_counter = 0;
    }
  }

  if (0 != target_state_flags.execute_step) {
    // Execute distribution step to send the state specific BT Mesh messages to
    // the target nodes. (Firmware Update Start/Cancel/Get/Apply/Information Get)
    // The execute distribution check could fail if it called from the wrong state.
    // This could happen if the retry self-transition occurs when the distribution
    // server has just changed state but the distribution server SDK component
    // has not processed the sl_btmesh_evt_fw_dist_server_dist_state_changed
    // event yet.
    // Note: This race condition exists because the retries are called by the
    //       app timer while each sl_btmesh_step processes one event in each
    //       loop so the issue can occur if the BT Mesh stack generates multiple
    //       events and the app timer elapses. This is a very rare issue.
    // If the distribution step execution fails then it is a good strategy to
    // continue and start the retry timer. If the problem is temporary then the
    // retry call may recover the distribution process otherwise the distribution
    // server model will timeout in the BT Mesh stack which is reported to this
    // component by sl_btmesh_evt_fw_dist_server_dist_state_changed event.
    // The errors are logged in the function so the return value is suppressed.
    (void) dist_execute_step(self);
  } else {
    switch (target_state) {
      case sl_btmesh_fw_dist_server_dist_step_transferring_image: {
        if (false == self->dist.blob_transfer_started) {
          dist_state_transferring_image_start(self);
        } else {
          dist_state_transferring_image_resume(self);
        }
        break;
      }
      case sl_btmesh_fw_dist_server_dist_step_waiting_for_apply: {
        dist_state_waiting_for_apply_entry(self);
        break;
      }
      case sl_btmesh_fw_dist_server_dist_step_suspended: {
        dist_state_suspended_entry(self);
        break;
      }
      case sl_btmesh_fw_dist_server_dist_step_completed: {
        dist_state_completed_entry(self);
        break;
      }
      case sl_btmesh_fw_dist_server_dist_step_failed: {
        dist_state_failed_entry(self);
        break;
      }
      case sl_btmesh_fw_dist_server_dist_step_idle: {
        dist_state_idle_entry(self);
        break;
      }
      default:
        // No other state needs to be processed
        break;
    }
  }

  if (0 != target_state_flags.retry) {
    self->dist.retry_counter++;
    self->dist.retry_time_elapsed = false;
    dist_start_retry_timer(self);
  }
}

static void upload_state_transition(fw_dist_server_t *const self,
                                    const upload_state_t target_state)
{
  app_assert_s(target_state < UPLOAD_STATE_COUNT);
  const upload_state_t source_state = self->upload.state;
  if ((upload_state_flags[source_state].idle == 0)
      && (upload_state_flags[target_state].idle != 0)) {
    // If the upload state machine transitions from a non-idle substate to an idle
    // substate then the FW descriptor shall be deallocated
    // Note: FW descriptor can be NULL when the upload is successful and
    //   therefore it is appended to the FW list. The metadata might be NULL
    //   because it is not mandatory but in that case the sl_free is a no-operation.
    if (self->upload.fw_descriptor != NULL) {
      sl_free(self->upload.fw_descriptor->metadata);
    }
    sl_free(self->upload.fw_descriptor);
    self->upload.fw_descriptor = NULL;
  }
  self->upload.state = target_state;
}

// Called to generate BLOB ID for firmware distribution
SL_WEAK sl_status_t
sl_btmesh_fw_distribution_server_generate_blob_id(sl_bt_uuid_64_t *blob_id)
{
  sl_status_t sc;
  if (blob_id == NULL) {
    sc = SL_STATUS_NULL_POINTER;
  } else {
    size_t bytes_written;
    sc = sl_bt_system_get_random_data(sizeof(blob_id->data),
                                      sizeof(blob_id->data),
                                      &bytes_written,
                                      blob_id->data);

    if ((sc == SL_STATUS_OK) && (bytes_written != sizeof(blob_id->data))) {
      sc = SL_STATUS_FAIL;
    }
  }
  return sc;
}

// Called when receiver target node is added to the firmware distribution list
SL_WEAK void
sl_btmesh_fw_distribution_server_on_node_added(uint16_t elem_index,
                                               uint16_t server_address,
                                               uint8_t  update_fw_image_idx,
                                               uint16_t node_count)
{
  (void) elem_index;
  (void) server_address;
  (void) update_fw_image_idx;
  (void) node_count;
}

// Called when all receiver target nodes are deleted from the firmware
// distribution list
SL_WEAK void
sl_btmesh_fw_distribution_server_on_all_nodes_deleted(uint16_t elem_index)
{
  (void) elem_index;
}

// Called when firmware distribution is started
SL_WEAK void
sl_btmesh_fw_distribution_server_on_distribution_started(uint16_t elem_index,
                                                         uint16_t client_address,
                                                         uint16_t group_address,
                                                         uint8_t  ttl,
                                                         sl_btmesh_fw_dist_server_dfu_policy_t update_policy,
                                                         uint16_t fw_list_index,
                                                         uint16_t timeout_base,
                                                         sl_btmesh_mbt_client_transfer_mode_t transfer_mode,
                                                         uint16_t node_count)
{
  (void) elem_index;
  (void) client_address;
  (void) group_address;
  (void) ttl;
  (void) update_policy;
  (void) fw_list_index;
  (void) timeout_base;
  (void) transfer_mode;
  (void) node_count;
}

// Called when firmware distribution is canceled
SL_WEAK void
sl_btmesh_fw_distribution_server_on_distribution_canceled(uint16_t elem_index,
                                                          uint16_t client_address)
{
  (void) elem_index;
  (void) client_address;
}

// Called when firmware distribution is suspended
SL_WEAK void
sl_btmesh_fw_distribution_server_on_distribution_suspended(uint16_t elem_index,
                                                           uint16_t client_address)
{
  (void) elem_index;
  (void) client_address;
}

// Called when firmware distribution is resumed
SL_WEAK void
sl_btmesh_fw_distribution_server_on_distribution_resumed(uint16_t elem_index,
                                                         uint16_t client_address,
                                                         uint16_t group_address,
                                                         uint8_t  ttl,
                                                         sl_btmesh_fw_dist_server_dfu_policy_t update_policy,
                                                         uint16_t fw_list_index,
                                                         uint16_t timeout_base,
                                                         sl_btmesh_mbt_client_transfer_mode_t transfer_mode,
                                                         uint16_t node_count)
{
  (void) elem_index;
  (void) client_address;
  (void) group_address;
  (void) ttl;
  (void) update_policy;
  (void) fw_list_index;
  (void) timeout_base;
  (void) transfer_mode;
  (void) node_count;
}

// Called when firmware distribution state is changed
SL_WEAK void
sl_btmesh_fw_distribution_server_on_distribution_state_changed(uint16_t elem_index,
                                                               sl_btmesh_fw_dist_server_dist_step_t state,
                                                               uint16_t num_active_nodes,
                                                               uint16_t node_count)
{
  (void) elem_index;
  (void) state;
  (void) num_active_nodes;
  (void) node_count;
}

// Called when progress of BLOB transfer step during the firmware distribution
// is changed
SL_WEAK void
sl_btmesh_fw_distribution_server_on_distribution_blob_progress_changed(uint16_t elem_index,
                                                                       uint32_t confirmed_tx_bytes,
                                                                       uint32_t blob_size,
                                                                       uint16_t node_count)
{
  (void) elem_index;
  (void) confirmed_tx_bytes;
  (void) blob_size;
  (void) node_count;
}

// Called when a Target Node fails during the distribution
SL_WEAK void
sl_btmesh_fw_distribution_server_on_distribution_node_failed(uint16_t elem_index,
                                                             uint16_t server_address,
                                                             sl_btmesh_fw_dist_server_dist_node_phase_t update_phase,
                                                             sl_btmesh_fw_update_server_update_status_t update_status,
                                                             uint8_t  mbt_status,
                                                             uint8_t  progress,
                                                             uint8_t  fw_index,
                                                             uint16_t num_active_nodes,
                                                             uint16_t node_count)
{
  (void) elem_index;
  (void) server_address;
  (void) update_phase;
  (void) update_status;
  (void) mbt_status;
  (void) progress;
  (void) fw_index;
  (void) num_active_nodes;
  (void) node_count;
}

// Called when firmware is added to the Distributor
SL_WEAK void
sl_btmesh_fw_distribution_server_on_firmware_added(uint16_t elem_index,
                                                   uint16_t client_address,
                                                   uint32_t fw_size,
                                                   uint16_t fw_list_idx,
                                                   uint16_t current_fw_list_length,
                                                   uint16_t max_fw_list_length,
                                                   const uint8_t *fwid,
                                                   uint8_t fwid_length)
{
  (void) elem_index;
  (void) client_address;
  (void) fw_size;
  (void) fw_list_idx;
  (void) current_fw_list_length;
  (void) max_fw_list_length;
  (void) fwid;
  (void) fwid_length;
}

// Called when a firmware is deleted from the Distributor
SL_WEAK void
sl_btmesh_fw_distribution_server_on_firmware_deleted(uint16_t elem_index,
                                                     uint16_t client_address,
                                                     uint16_t current_fw_list_length,
                                                     uint16_t max_fw_list_length,
                                                     const uint8_t *fwid,
                                                     uint8_t fwid_length)
{
  (void) elem_index;
  (void) client_address;
  (void) current_fw_list_length;
  (void) max_fw_list_length;
  (void) fwid;
  (void) fwid_length;
}

// Called when ALL firmwares are deleted from the Distributor
SL_WEAK void
sl_btmesh_fw_distribution_server_on_all_firmware_deleted(uint16_t elem_index,
                                                         uint16_t client_address,
                                                         uint16_t max_fw_list_length)
{
  (void) elem_index;
  (void) client_address;
  (void) max_fw_list_length;
}

sl_status_t mesh_platform_dfu_dist_server_get_fw_count(size_t element_index,
                                                       uint16_t *count)
{
  sl_status_t sc;
  fw_dist_server_t *self = find_server(element_index);
  sc = SERVER_STATUS_GET(self, SL_STATUS_INVALID_STATE);

  if (sc == SL_STATUS_OK) {
    if (count == NULL) {
      sc = SL_STATUS_NULL_POINTER;
    } else if (self->storage_corrupted != false) {
      // The FW delete all event is triggered only when the firmware count is
      // non-zero. If the storage is corrupted then the FW delete all event is
      // used to clean the NVM and BLOB storage to recover from corrupted
      // storage state.
      *count = 1;
      sc = SL_STATUS_FAIL;
    } else {
      // If count is not set then the BT Mesh stack uses zero as a default value
      *count = self->fw_list_nvm->current_fw_list_length;
    }
  }

  log_btmesh_platform_cb(LOG_PREFIX "%s(elem=%d)->(sc=0x%04lx,count=%u)" NL,
                         __func__,
                         element_index,
                         sc,
                         self->fw_list_nvm->current_fw_list_length);
  return sc;
}

sl_status_t mesh_platform_dfu_dist_server_get_remaining_space(size_t element_index,
                                                              uint32_t *bytes)
{
  sl_status_t sc;
  uint32_t remaining_upload_space = 0;
  fw_dist_server_t *self = find_server(element_index);

  sc = SERVER_STATUS_GET(self, SL_STATUS_INVALID_STATE);

  if (sc == SL_STATUS_OK) {
    if (NULL == bytes) {
      sc = SL_STATUS_NULL_POINTER;
    } else if (self->storage_corrupted != false) {
      *bytes = 0;
      sc = SL_STATUS_FAIL;
    } else {
      // If bytes is not set then the BT Mesh stack uses zero as a default value
      remaining_upload_space = calc_fw_storage_remaining_upload_space(self);
      *bytes = remaining_upload_space;
    }
  }

  log_btmesh_platform_cb(LOG_PREFIX "%s(elem=%d)->(sc=0x%04lx,bytes=%lu)" NL,
                         __func__,
                         element_index,
                         sc,
                         remaining_upload_space);
  return sc;
}

sl_status_t sli_btmesh_fw_dist_server_get_fw_by_index(uint16_t element_index,
                                                      uint16_t fw_index,
                                                      mesh_dfu_dist_server_fw_info_t *info)
{
  sl_status_t sc;
  fw_dist_server_t *self = find_server(element_index);
  SERVER_STATUS_CHECK(self, SL_STATUS_INVALID_STATE);

  sc = fw_list_get_fw_info_by_index(self, fw_index, FW_BLOB_SELECTOR_STORAGE, info);

  return sc;
}

sl_status_t mesh_platform_dfu_dist_server_get_fw_by_index(size_t element_index,
                                                          uint16_t fw_index,
                                                          mesh_dfu_dist_server_fw_info_t *info)
{
  sl_status_t sc;
  fw_dist_server_t *self = find_server(element_index);
  SERVER_STATUS_CHECK(self, SL_STATUS_INVALID_STATE);

  sc = fw_list_get_fw_info_by_index(self, fw_index, FW_BLOB_SELECTOR_CURRENT, info);

#if (SL_BTMESH_FW_DIST_SERVER_PLATFORM_CALLBACK_LOGGING_CFG_VAL != 0)
  log_debug(LOG_PREFIX "%s(elem=%d,fw_list_idx=%u)->", __func__, element_index, fw_index);
  if ((sc != SL_STATUS_OK) || (info == NULL)) {
    log_append_debug("(sc=0x%04lx)" NL, sc);
  } else {
    log_append_debug("(sc=0x%04lx,size=%lu,fwid=", sc, info->size);
    log_fwid_level(APP_LOG_LEVEL_DEBUG,
                   info->p_fwid,
                   info->fwid_len,
                   SL_BTMESH_FW_DIST_SERVER_FWID_METADATA_LOG_FORMAT_HEX);
    log_append_debug(",metadata=");
    log_metadata_level(APP_LOG_LEVEL_DEBUG,
                       info->p_metadata,
                       info->metadata_len,
                       SL_BTMESH_FW_DIST_SERVER_FWID_METADATA_LOG_FORMAT_HEX);
    log_append_debug(")" NL);
  }
#endif

  return sc;
}

sl_status_t mesh_platform_dfu_dist_server_get_fw_by_fwid(size_t element_index,
                                                         uint8_t fwid_len,
                                                         const uint8_t *fwid,
                                                         mesh_dfu_dist_server_fw_info_t *info)
{
  sl_status_t sc;
  fw_dist_server_t *self = find_server(element_index);
  SERVER_STATUS_CHECK(self, SL_STATUS_INVALID_STATE);

  sc = fw_list_get_fw_info_by_fwid(self, fwid, fwid_len, FW_BLOB_SELECTOR_CURRENT, info);

#if (SL_BTMESH_FW_DIST_SERVER_PLATFORM_CALLBACK_LOGGING_CFG_VAL != 0)
  log_debug(LOG_PREFIX "%s(elem=%d,fwid=", __func__, element_index);
  log_fwid_level(APP_LOG_LEVEL_DEBUG,
                 fwid,
                 fwid_len,
                 SL_BTMESH_FW_DIST_SERVER_FWID_METADATA_LOG_FORMAT_HEX);
  if ((sc != SL_STATUS_OK) || (info == NULL)) {
    log_append_debug(")->(sc=0x%04lx)" NL, sc);
  } else {
    log_append_debug(")->(sc=0x%04lx,fw_list_idx=%u,size=%lu,metadata=",
                     sc,
                     info->index,
                     (unsigned long) info->size);
    log_metadata_level(APP_LOG_LEVEL_DEBUG,
                       info->p_metadata,
                       info->metadata_len,
                       SL_BTMESH_FW_DIST_SERVER_FWID_METADATA_LOG_FORMAT_HEX);
    log_append_debug(")" NL);
  }
#endif

  return sc;
}

// Set the multicast threshold value.
sl_status_t sl_btmesh_fw_distribution_server_set_multicast_threshold(uint16_t elem_index,
                                                                     uint16_t multicast_threshold)
{
  return sl_btmesh_fw_dist_server_set_multicast_threshold(elem_index,
                                                          multicast_threshold);
}

void sl_btmesh_fw_distribution_server_delete_step_handle(void)
{
  uint16_t element_index = BTMESH_FW_DISTRIBUTION_SERVER_GROUP_MAIN_ELEM_INDEX;
  do {
    fw_dist_server_t *self = find_server(element_index);
    SERVER_STATUS_CHECK(self);

    if (self->deleting_all) {
      sl_btmesh_blob_storage_delete_state_t error_code =
        sl_btmesh_blob_storage_get_erase_error_code();
      switch (error_code) {
        case SL_BTMESH_BLOB_STORAGE_DELETE_FAILED:
          handle_fw_delete_all_response(self, SL_STATUS_FLASH_ERASE_FAILED);
          break;
        case SL_BTMESH_BLOB_STORAGE_DELETE_SUCCESS:
        case SL_BTMESH_BLOB_STORAGE_DELETE_INACTIVE:
          // If all BLOBs owned by the distributor were deleted successfully or
          // no BLOBs owned by the distributor were present in BLOB storage
          handle_fw_delete_all_response(self, SL_STATUS_OK);
          break;
        default:
          // BLOB erase is either inactive or busy
          break;
      }
    }
    if (self->deleting) {
      sl_btmesh_blob_storage_delete_state_t error_code =
        sl_btmesh_blob_storage_get_erase_error_code();
      switch (error_code) {
        case SL_BTMESH_BLOB_STORAGE_DELETE_FAILED:
        case SL_BTMESH_BLOB_STORAGE_DELETE_INACTIVE:
          // If the BLOB delete failed or the BLOB was not found in BLOB storage
          // FW delete needs to delete a specific BLOB so if that is not found
          // then it is considered as an error
          handle_fw_delete_response(self, SL_STATUS_FLASH_ERASE_FAILED);
          break;
        case SL_BTMESH_BLOB_STORAGE_DELETE_SUCCESS:
          handle_fw_delete_response(self, SL_STATUS_OK);
          break;
        default:
          // BLOB erase is either inactive or busy
          break;
      }
    }
    // Should return much-much earlier, but this is a very rudimentary fail-safe
  } while (element_index++ < UINT16_MAX);
}

// Handle Firmware Distribution Server events
void sl_btmesh_fw_distribution_server_on_event(const sl_btmesh_msg_t *const evt)
{
  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_btmesh_evt_prov_initialized_id:
    case sl_btmesh_evt_node_provisioned_id: {
      sl_btmesh_fw_distribution_server_init();
      break;
    }
    case sl_btmesh_evt_node_initialized_id: {
      if (evt->data.evt_node_initialized.provisioned) {
        sl_btmesh_fw_distribution_server_init();
      }
      break;
    }
    case sl_btmesh_evt_fw_dist_server_nodes_added_id: {
      handle_nodes_added(&evt->data.evt_fw_dist_server_nodes_added);
      break;
    }
    case sl_btmesh_evt_fw_dist_server_nodes_deleted_id: {
      handle_nodes_deleted(&evt->data.evt_fw_dist_server_nodes_deleted);
      break;
    }
    case sl_btmesh_evt_fw_dist_server_dist_start_req_id: {
      handle_dist_start_request(&evt->data.evt_fw_dist_server_dist_start_req);
      break;
    }
    case sl_btmesh_evt_fw_dist_server_dist_cancel_id: {
      handle_dist_cancel(&evt->data.evt_fw_dist_server_dist_cancel);
      break;
    }
    case sl_btmesh_evt_fw_dist_server_dist_state_changed_id: {
      handle_dist_state_changed(
        &evt->data.evt_fw_dist_server_dist_state_changed);
      break;
    }
    case sl_btmesh_evt_fw_dist_server_node_failed_id: {
      handle_dist_server_node_failed(&evt->data.evt_fw_dist_server_node_failed);
      break;
    }
    case sl_btmesh_evt_fw_dist_server_upload_start_metadata_id: {
      handle_upload_start_metadata(
        &evt->data.evt_fw_dist_server_upload_start_metadata);
      break;
    }
    case sl_btmesh_evt_fw_dist_server_upload_start_req_id: {
      handle_upload_start_request(
        &evt->data.evt_fw_dist_server_upload_start_req);
      break;
    }
    case sl_btmesh_evt_fw_dist_server_upload_cancel_id: {
      handle_upload_cancel(&evt->data.evt_fw_dist_server_upload_cancel);
      break;
    }
    case sl_btmesh_evt_fw_dist_server_upload_complete_metadata_id: {
      handle_upload_complete_metadata(
        &evt->data.evt_fw_dist_server_upload_complete_metadata);
      break;
    }
    case sl_btmesh_evt_fw_dist_server_upload_complete_id: {
      handle_upload_complete(&evt->data.evt_fw_dist_server_upload_complete);
      break;
    }
    case sl_btmesh_evt_fw_dist_server_upload_failed_id: {
      handle_upload_failed(&evt->data.evt_fw_dist_server_upload_failed);
      break;
    }
    case sl_btmesh_evt_fw_dist_server_fw_delete_req_id: {
      handle_fw_delete_request(&evt->data.evt_fw_dist_server_fw_delete_req);
      break;
    }
    case sl_btmesh_evt_fw_dist_server_fw_delete_all_req_id: {
      handle_fw_delete_all_request(&evt->data.evt_fw_dist_server_fw_delete_all_req);
      break;
    }
    case sl_btmesh_evt_fw_dist_server_dist_suspend_id: {
      handle_dist_suspend(&evt->data.evt_fw_dist_server_dist_suspend);
      break;
    }
    case sl_btmesh_evt_fw_dist_server_resume_req_id: {
      handle_dist_resume_request(&evt->data.evt_fw_dist_server_resume_req);
      break;
    }
  }
}

// Provides the string representation of distribution state
const char *sl_btmesh_fw_distribution_server_distribution_state_to_string(sl_btmesh_fw_dist_server_dist_step_t state)
{
  switch (state) {
    case sl_btmesh_fw_dist_server_dist_step_idle:
      return "Idle";
    case sl_btmesh_fw_dist_server_dist_step_starting_update:
      return "Starting Update";
    case sl_btmesh_fw_dist_server_dist_step_transferring_image:
      return "Transfer Image";
    case sl_btmesh_fw_dist_server_dist_step_checking_verification:
      return "Checking Verification";
    case sl_btmesh_fw_dist_server_dist_step_waiting_for_apply:
      return "Waiting for Apply";
    case sl_btmesh_fw_dist_server_dist_step_applying_update:
      return "Apply Update";
    case sl_btmesh_fw_dist_server_dist_step_checking_update_result:
      return "Check Update Result";
    case sl_btmesh_fw_dist_server_dist_step_completed:
      return "Completed";
    case sl_btmesh_fw_dist_server_dist_step_failed:
      return "Failed";
    case sl_btmesh_fw_dist_server_dist_step_cancelling:
      return "Canceling";
    case sl_btmesh_fw_dist_server_dist_step_suspended:
      return "Suspended";
    default:
      return "INVALID";
  }
}

// Provides the string representation of firmware update phase
const char *sl_btmesh_fw_distribution_server_node_phase_to_string(sl_btmesh_fw_dist_server_dist_node_phase_t node_phase)
{
  switch (node_phase) {
    case sl_btmesh_fw_dist_server_dist_node_phase_idle:
      return "idle";
    case sl_btmesh_fw_dist_server_dist_node_phase_transfer_error:
      return "transfer error";
    case sl_btmesh_fw_dist_server_dist_node_phase_transfer_in_progress:
      return "transfer in progress";
    case sl_btmesh_fw_dist_server_dist_node_phase_verifying_update:
      return "verifying update";
    case sl_btmesh_fw_dist_server_dist_node_phase_verification_success:
      return "verification success";
    case sl_btmesh_fw_dist_server_dist_node_phase_verification_failed:
      return "verification failed";
    case sl_btmesh_fw_dist_server_dist_node_phase_apply_in_progress:
      return "apply in progress";
    case sl_btmesh_fw_dist_server_dist_node_phase_transfer_cancelled:
      return "transfer cancelled";
    case sl_btmesh_fw_dist_server_dist_node_phase_apply_success:
      return "apply success";
    case sl_btmesh_fw_dist_server_dist_node_phase_apply_failed:
      return "apply failed";
    case sl_btmesh_fw_dist_server_dist_node_phase_unknown:
      return "unknown";
    default:
      return "INVALID";
  }
}

// Provides the string representation of node firmware update status
const char *sl_btmesh_fw_distribution_server_firmware_update_status_to_string(sl_btmesh_fw_update_server_update_status_t update_server_status)
{
  switch (update_server_status) {
    case sl_btmesh_fw_update_server_update_status_success:
      return "success";
    case sl_btmesh_fw_update_server_update_status_out_of_resources:
      return "out of resources";
    case sl_btmesh_fw_update_server_update_status_wrong_phase:
      return "wrong phase";
    case sl_btmesh_fw_update_server_update_status_internal_error:
      return "internal error";
    case sl_btmesh_fw_update_server_update_status_wrong_fw_index:
      return "wrong fw index";
    case sl_btmesh_fw_update_server_update_status_metadata_check_failed:
      return "metadata check failed";
    case sl_btmesh_fw_update_server_update_status_temporarily_unable:
      return "temporarily unavailable";
    case sl_btmesh_fw_update_server_update_status_blob_transfer_busy:
      return "BLOB transfer busy";
    default:
      return "INVALID";
  }
}
/** @} end dist_server */
