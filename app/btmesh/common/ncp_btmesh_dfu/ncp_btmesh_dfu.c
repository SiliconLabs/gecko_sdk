/***************************************************************************//**
 * @file
 * @brief Implementation of FW Update Server application level functionality
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#include <stdlib.h>

#include "em_common.h"
#include "sl_bt_api.h"

#include "ncp_btmesh_dfu.h"
#include "sl_ncp.h"
#include "sl_status.h"

/// Maximum length of the version infromation
#define VER_INFO_MAX_LENGTH   106
/// Length of the Company ID in bytes
#define CID_LENGTH            2
/// Maximum length of firmware URI
#define URI_MAX_LENGTH        255

/// User command to set FWID
#define USER_CMD_FWID_ID 'F'
typedef struct {
  uint8_t idx;
  uint8_t len;
  uint8_t data[];
} cmd_fwid_t;

/// User command to set FW URI
#define USER_CMD_URI_ID 'U'
typedef struct {
  uint8_t type;
  uint8_t idx;
  uint8_t len;
  uint8_t data[];
} cmd_uri_t;

PACKSTRUCT(struct user_cmd {
  uint8_t hdr;
  union {
    cmd_fwid_t cmd_fwid;
    cmd_uri_t cmd_uri;
  } data;
});

typedef struct user_cmd user_cmd_t;

/// Storage entry structure
typedef PACKSTRUCT (struct storage_s {
  /// Length of the FWID
  uint8_t fwid_len;
  /// FWID data
  ///
  /// @details Contains 2 bytes of CID (little-endian) and up to 106 bytes of
  /// version information.
  uint8_t *fwid_data;
  /// URI length
  uint8_t uri_len;
  /// URI data
  ///
  /// @details Contains up to 255 bytes.
  uint8_t *uri_data;
}) storage_t;

PACKSTRUCT(struct {
  /// Current length of the storage
  uint8_t storage_len;
  /// Storage data
  storage_t * storage;
}) dfu = { .storage_len = 0, .storage = NULL }; // Initialize values to 0

/***************************************************************************//**
 * (Re)allocates storage based on the index of the FW
 *
 * @param idx Index of the firmware for which reallocate storage if needed
 * @return Status code
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_NO_MORE_RESOURCE In case of memory allocation error
 ******************************************************************************/
static sl_status_t allocate_storage(uint8_t idx);

static sl_status_t allocate_storage(uint8_t idx)
{
  void *ptr;

  if (idx >= dfu.storage_len) {
    ptr = calloc((idx + 1), sizeof(storage_t));
    if (NULL == ptr) {
      return SL_STATUS_NO_MORE_RESOURCE;
    }
    if (dfu.storage != NULL) {
      memcpy(ptr, dfu.storage, sizeof(storage_t) * dfu.storage_len);
    }
    free(dfu.storage);
    dfu.storage = ptr;
    dfu.storage_len = idx + 1;
  }

  return SL_STATUS_OK;
}

sl_status_t mesh_platform_get_installed_firmware_information(uint8_t index,
                                                             uint8_t *fwid_len,
                                                             const uint8_t **fwid_ptr,
                                                             uint8_t *uri_len,
                                                             const uint8_t **uri_ptr)
{
  if (index < dfu.storage_len) {
    *fwid_len = dfu.storage[index].fwid_len;
    *fwid_ptr = dfu.storage[index].fwid_data;
    *uri_len = dfu.storage[index].uri_len;
    *uri_ptr = dfu.storage[index].uri_data;
    return SL_STATUS_OK;
  }

  return SL_STATUS_NOT_FOUND;
}

sl_status_t sl_btmesh_ncp_dfu_set_fwid(uint8_t idx, uint8_t len, uint8_t *data)
{
  void *ptr;
  if ((len < CID_LENGTH) || (len > (CID_LENGTH + VER_INFO_MAX_LENGTH))) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  sl_status_t sc = allocate_storage(idx);
  if (SL_STATUS_OK != sc) {
    return sc;
  }
  ptr = realloc(dfu.storage[idx].fwid_data, len);
  if (NULL == ptr) {
    return SL_STATUS_NO_MORE_RESOURCE;
  }
  dfu.storage[idx].fwid_len = len;
  dfu.storage[idx].fwid_data = ptr;
  memcpy(dfu.storage[idx].fwid_data, data, len);

  return SL_STATUS_OK;
}

sl_status_t sl_btmesh_ncp_dfu_set_uri(uint8_t idx,
                                      uint8_t type,
                                      uint8_t len,
                                      uint8_t *data)
{
  void *ptr;

  switch (type) {
    case USER_SUB_CMD_URI_ID_WRT: {
      sl_status_t sc = allocate_storage(idx);
      if (SL_STATUS_OK != sc) {
        return sc;
      }
      ptr = realloc(dfu.storage[idx].uri_data, len);
      if (NULL == ptr) {
        return SL_STATUS_NO_MORE_RESOURCE;
      }
      dfu.storage[idx].uri_data = ptr;
      dfu.storage[idx].uri_len = len;
      memcpy(dfu.storage[idx].uri_data, data, len);
    }
    break;
    case USER_SUB_CMD_URI_ID_APP:
      if (idx >= dfu.storage_len) {
        // This index has not been initialized yet
        return SL_STATUS_NOT_FOUND;
      }
      if (dfu.storage[idx].uri_len + len > URI_MAX_LENGTH) {
        // According to the specification, URI can't be longer than 255 bytes
        return SL_STATUS_INVALID_PARAMETER;
      }
      // Allocate memory to fit appended value
      ptr = realloc(dfu.storage[idx].uri_data, dfu.storage[idx].uri_len + len);
      if (NULL == ptr) {
        return SL_STATUS_NO_MORE_RESOURCE;
      }
      dfu.storage[idx].uri_data = ptr;
      // Append data to the existing URI
      memcpy(&dfu.storage[idx].uri_data[dfu.storage[idx].uri_len], data, len);
      // Increment URI length
      dfu.storage[idx].uri_len += len;
      break;
    default:
      return SL_STATUS_INVALID_PARAMETER;
  }

  return SL_STATUS_OK;
}

void sl_btmesh_ncp_dfu_handle_cmd(void *data, bool *cmd_handled)
{
  uint8array *cmd = (uint8array *)data;
  user_cmd_t *user_cmd = (user_cmd_t *)cmd->data;

  if (*cmd_handled == true) {
    return;
  }

  switch (user_cmd->hdr) {
    case USER_CMD_FWID_ID: {
      sl_status_t sc = sl_btmesh_ncp_dfu_set_fwid(user_cmd->data.cmd_fwid.idx,
                                                  user_cmd->data.cmd_fwid.len,
                                                  user_cmd->data.cmd_fwid.data);
      sl_ncp_user_cmd_message_to_target_rsp(sc, cmd->len, cmd->data);
      *cmd_handled = true;
      break;
    }
    case USER_CMD_URI_ID: {
      sl_status_t sc = sl_btmesh_ncp_dfu_set_uri(user_cmd->data.cmd_uri.idx,
                                                 user_cmd->data.cmd_uri.type,
                                                 user_cmd->data.cmd_uri.len,
                                                 user_cmd->data.cmd_uri.data);
      sl_ncp_user_cmd_message_to_target_rsp(sc, cmd->len, cmd->data);
      *cmd_handled = true;
      break;
    }
    default:
      break;
  }
}
