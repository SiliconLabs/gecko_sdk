/***************************************************************************//**
 * @file
 * @brief App BT Mesh Utility
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

#include "nvm3.h"
#include "sl_status.h"
#include "app_btmesh_util.h"

/// Handler for NVM3, use default
#define SL_BTMESH_NVM3            nvm3_defaultHandle
/// Start of the BT mesh NVM3 region keys
#define SL_BTMESH_NVM3_REGION     0
/// The maximum LSBs of the BT mesh NVM3 region keys
#define SL_BTMESH_NVM3_END        0xFFFF

/**
 * Converts @ref Ecode_t to @ref sl_status_t
 *
 * @param ec Error code coming from NVM3 API calls
 * @return  The appropriate value the input is converted to. Some cases that
 *          would be hard to make sense of in higher layers are merged into
 *          @ref SL_STATUS_FAIL.
 */
static sl_status_t ecode2sc(Ecode_t ec);

sl_status_t app_btmesh_nvm_init(void)
{
  return ecode2sc(nvm3_initDefault());
}

sl_status_t app_btmesh_nvm_read(uint16_t key, void *buf, size_t *len)
{
  uint32_t nvm3_objecttype;
  // Store input buffer length temporarily
  size_t tmp = *len;
  // Read length of the data
  Ecode_t nvm3_ec = nvm3_getObjectInfo(SL_BTMESH_NVM3,
                                       SL_BTMESH_NVM3_REGION | (uint32_t)key,
                                       &nvm3_objecttype,
                                       len);

  // If would be too long, fail
  if (*len > tmp) {
    return SL_STATUS_WOULD_OVERFLOW;
  }

  // If failure has occurred, return proper error code
  if (ECODE_NVM3_OK != nvm3_ec) {
    return ecode2sc(nvm3_ec);
  }

  // Read the data into the buffer based on the read length
  nvm3_ec = nvm3_readData(SL_BTMESH_NVM3,
                          SL_BTMESH_NVM3_REGION | (uint32_t)key,
                          buf,
                          *len);

  return ecode2sc(nvm3_ec);
}

sl_status_t app_btmesh_nvm_write(uint16_t key,
                                 const void *buf,
                                 size_t len)
{
  Ecode_t nvm3_ec = nvm3_writeData(SL_BTMESH_NVM3,
                                   SL_BTMESH_NVM3_REGION | (uint32_t)key,
                                   buf, len);

  return ecode2sc(nvm3_ec);
}

sl_status_t app_btmesh_nvm_erase(uint16_t key)
{
  Ecode_t nvm3_ec = nvm3_deleteObject(SL_BTMESH_NVM3,
                                      SL_BTMESH_NVM3_REGION | key);

  return ecode2sc(nvm3_ec);
}

sl_status_t app_btmesh_nvm_erase_all(void)
{
  Ecode_t nvm3_ec = nvm3_eraseAll(SL_BTMESH_NVM3);

  return ecode2sc(nvm3_ec);
}

static sl_status_t ecode2sc(Ecode_t ec)
{
  switch (ec) {
    case ECODE_NVM3_OK:
      return SL_STATUS_OK;
    case ECODE_NVM3_ERR_SIZE_TOO_SMALL:
    case ECODE_NVM3_ERR_NO_VALID_PAGES:
    case ECODE_NVM3_ERR_RESIZE_NOT_ENOUGH_SPACE:
      return SL_STATUS_NO_MORE_RESOURCE;
    case ECODE_NVM3_ERR_PAGE_SIZE_NOT_SUPPORTED:
    case ECODE_NVM3_ERR_PARAMETER:
    case ECODE_NVM3_ERR_WRITE_DATA_SIZE:
    case ECODE_NVM3_ERR_OBJECT_SIZE_NOT_SUPPORTED:
    case ECODE_NVM3_ERR_RESIZE_PARAMETER:
    case ECODE_NVM3_ERR_ADDRESS_RANGE:
      return SL_STATUS_INVALID_PARAMETER;
    case ECODE_NVM3_ERR_STORAGE_FULL:
      return SL_STATUS_FULL;
    case ECODE_NVM3_ERR_NOT_OPENED:
      return SL_STATUS_INVALID_STATE;
    case ECODE_NVM3_ERR_OPENED_WITH_OTHER_PARAMETERS:
      return SL_STATUS_ALREADY_INITIALIZED;
    case ECODE_NVM3_ERR_KEY_INVALID:
    case ECODE_NVM3_ERR_INT_KEY_MISMATCH:
      return SL_STATUS_INVALID_KEY;
    case ECODE_NVM3_ERR_KEY_NOT_FOUND:
      return SL_STATUS_NOT_FOUND;
    case ECODE_NVM3_ERR_ERASE_FAILED:
      return SL_STATUS_FLASH_ERASE_FAILED;
    case ECODE_NVM3_ERR_WRITE_FAILED:
      return SL_STATUS_FLASH_PROGRAM_FAILED;
    default:
      return SL_STATUS_FAIL;
  }
}

const char *app_btmesh_uuid_64_to_string(char *buffer,
                                         uint32_t buffer_size,
                                         const sl_bt_uuid_64_t *uuid_64,
                                         char separator,
                                         bool uppercase)
{
  return app_btmesh_bytes_to_hex(buffer,
                                 buffer_size,
                                 uuid_64->data,
                                 sizeof(uuid_64->data),
                                 separator,
                                 uppercase);
}

const char *app_btmesh_bytes_to_hex(char *buffer,
                                    uint32_t buffer_size,
                                    const uint8_t *bytes,
                                    uint32_t bytes_size,
                                    char separator,
                                    bool uppercase)
{
  const char hex_char_uppercase[] = { '0', '1', '2', '3', '4', '5', '6', '7',
                                      '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
  const char hex_char_lowercase[] = { '0', '1', '2', '3', '4', '5', '6', '7',
                                      '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

  const char *hex_char = uppercase ? hex_char_uppercase : hex_char_lowercase;
  uint32_t total_size, total_separator_size;
  const char *hex_str = "INVALID";

  // If no input array is provided or the length of the input array is zero then
  // an empty string is returned unless the output buffer is invalid (e.g. NULL)
  bytes_size = (bytes != NULL) ? bytes_size : 0;

  // If the separator is set the null character then no separator is used so
  // the multiplication by zero results in zero total separator size.
  // There is a separator after each two hex characters except for the last two.
  total_separator_size = ((0 < bytes_size) ? (bytes_size - 1) : 0)
                         * (separator != '\0');

  // One character shall be reserved for the terminating null character
  total_size = 2 * bytes_size + total_separator_size + 1;

  if ((buffer != NULL) && (total_size <= buffer_size)) {
    uint32_t out_idx = 0;
    for (uint32_t in_idx = 0; in_idx < bytes_size; in_idx++) {
      buffer[out_idx++] = hex_char[(bytes[in_idx] >> 4) & 0xF];
      buffer[out_idx++] = hex_char[(bytes[in_idx] >> 0) & 0xF];
      if (separator != '\0' && (in_idx + 1) < bytes_size) {
        buffer[out_idx++] = separator;
      }
    }
    buffer[out_idx] = '\0';
    hex_str = buffer;
  }
  return hex_str;
}
