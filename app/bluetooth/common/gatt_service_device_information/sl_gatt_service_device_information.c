/***************************************************************************//**
 * @file
 * @brief Device Information GATT Service
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "sl_status.h"
#include "sl_gsdk_version.h"
#include "gatt_db.h"
#include "app_assert.h"
#include "sl_gatt_service_device_information.h"

#define GATTDB_MODEL_NUMBER_STRING_LEN          8
#define GATTDB_HARDWARE_REVISION_STRING_LEN     3
#define GATTDB_FIRMWARE_REVISION_STRING_LEN     5
#define GATTDB_SYSTEM_ID_LEN                    8

/**************************************************************************//**
 * Bluetooth stack event handler.
 *****************************************************************************/
void sl_gatt_service_device_information_on_event(sl_bt_msg_t *evt)
{
  sl_status_t sc;
  bd_addr address;
  uint8_t address_type;
  uint8_t system_id[GATTDB_SYSTEM_ID_LEN];

  // Handle stack events
  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_bt_evt_system_boot_id:
      // Model Number String
#if defined(gattdb_model_number_string) && defined(SL_BOARD_NAME)
      sc = sl_bt_gatt_server_write_attribute_value(gattdb_model_number_string,
                                                   0,
                                                   GATTDB_MODEL_NUMBER_STRING_LEN,
                                                   (uint8_t *)SL_BOARD_NAME);
      app_assert_status(sc);
#else
#warning "Could not set Model Number String."
// Check the presence of this characteristic and the ID reference in the GATT
// Configurator. If using a custom board, remove this section and use the
// GATT Configurator to set the value manually.
#endif

      // Hardware Revision String
#if defined(gattdb_hardware_revision_string) && defined(SL_BOARD_REV)
      sc = sl_bt_gatt_server_write_attribute_value(gattdb_hardware_revision_string,
                                                   0,
                                                   GATTDB_HARDWARE_REVISION_STRING_LEN,
                                                   (uint8_t *)SL_BOARD_REV);
      app_assert_status(sc);
#else
#warning "Could not set Hardware Revision String."
// Check the presence of this characteristic and the ID reference in the GATT
// Configurator. If using a custom board, remove this section and use the
// GATT Configurator to set the value manually.
#endif

      // Firmware Revision String
#if defined(gattdb_firmware_revision_string)
      sc = sl_bt_gatt_server_write_attribute_value(gattdb_firmware_revision_string,
                                                   0,
                                                   GATTDB_FIRMWARE_REVISION_STRING_LEN,
                                                   (uint8_t *)SL_GSDK_VERSION_STR);
      app_assert_status(sc);
#else
#warning "Could not set Firmware Revision String."
// Check the presence of this characteristic and the ID reference in the GATT
// Configurator.
#endif

      // System ID
#if defined(gattdb_system_id)
      // Extract unique ID from BT Address.
      sc = sl_bt_system_get_identity_address(&address, &address_type);
      app_assert_status(sc);

      // Pad and reverse unique ID to get System ID.
      system_id[0] = address.addr[5];
      system_id[1] = address.addr[4];
      system_id[2] = address.addr[3];
      system_id[3] = 0xFF;
      system_id[4] = 0xFE;
      system_id[5] = address.addr[2];
      system_id[6] = address.addr[1];
      system_id[7] = address.addr[0];

      sc = sl_bt_gatt_server_write_attribute_value(gattdb_system_id,
                                                   0,
                                                   sizeof(system_id),
                                                   system_id);
      app_assert_status(sc);
#else
#warning "Could not set System ID."
// Check the presence of this characteristic and the ID reference in the GATT
// Configurator.
#endif
      break;

    default:
      break;
  }
}
