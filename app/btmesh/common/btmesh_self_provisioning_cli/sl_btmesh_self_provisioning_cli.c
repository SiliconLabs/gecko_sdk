/***************************************************************************//**
 * @file  sl_btmesh_self_provisioning.c
 * @brief Self Provisioning module
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
#include "sl_bt_api.h"
#include "sl_btmesh_api.h"
#include "sl_btmesh.h"
#include "em_common.h"
#include "sl_cli.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT

#ifdef SL_CATALOG_APP_LOG_PRESENT
#include "app_log.h"
#endif // SL_CATALOG_APP_LOG_PRESENT

#include "sl_btmesh_self_provisioning_cli_config.h"

// Warning! The app_btmesh_util shall be included after the component configuration
// header file in order to provide the component specific logging macro.
#include "app_btmesh_util.h"

/***************************************************************************//**
 * @addtogroup SelfProvisioning
 * @{
 ******************************************************************************/

// Key position
#define KEY_INDEX                     0
// Old key data. Old key data can be queried only during the key refresh.
#define OLD_KEY_DATA                  0
// Current key data
#define CURRENT_KEY_DATA              1
// Key length
#define KEY_LENGTH                    16
// Address length
#define ADDRESS_LENGTH                2
// Current IV Index used in the network
#define IV_INDEX                      0
// Current operation is not a key refresh
#define NOT_KEY_REFRESH               0
// Network key index to which the application key is bound
#define APPKEY_BOUND_TO_NETKEY        0

/***************************************************************************//**
   // Static Function Declarations
 ******************************************************************************/

/***************************************************************************//**
 * Self provisioning according to input parameters
 *
 * @dev_key[in] - device key
 * @dev_key[in] - network key
 * @dev_key[in] - primary element address
 ******************************************************************************/
static void sl_btmesh_self_provisioning(aes_key_128 dev_key,
                                        aes_key_128 net_key,
                                        uint16_t address);

/***************************************************************************//**
 * Add an application key locally.
 *
 * @app_key[in] - application key
 ******************************************************************************/
static void sl_btmesh_add_app_key(aes_key_128 app_key);

/***************************************************************************//**
 * CLI Callback
 * @param[in] arguments pointer to CLI arguments
 ******************************************************************************/
#ifdef SL_CATALOG_CLI_PRESENT
void sl_btmesh_self_provisioning_from_cli(sl_cli_command_arg_t *arguments)
{
  size_t arg_length;
  uint8_t *input_arguments;
  aes_key_128 network_key;
  aes_key_128 device_key;
  uint16_t primary_address = 0;

  // Get the first argument - device key
  input_arguments = sl_cli_get_argument_hex(arguments, 0, &arg_length);
  if (arg_length != KEY_LENGTH) {
    log_warning("Wrong device key length: %u, should be %d"NL, arg_length, KEY_LENGTH);
    return;
  }
  memcpy(device_key.data, input_arguments, arg_length);

  // Get the second argument - network key
  input_arguments = sl_cli_get_argument_hex(arguments, 1, &arg_length);
  if (arg_length != KEY_LENGTH) {
    log_warning("Wrong network key length: %u, should be %d"NL, arg_length, KEY_LENGTH);
    return;
  }
  memcpy(network_key.data, input_arguments, arg_length);

  // Get the third argument - primary element address
  input_arguments = sl_cli_get_argument_hex(arguments, 2, &arg_length);
  if (arg_length != ADDRESS_LENGTH) {
    log_warning("Wrong primary element address length: %u, should be %d"NL, arg_length, ADDRESS_LENGTH);
    return;
  }
  primary_address = ((uint16_t)input_arguments[0] << 8) | input_arguments[1];

  sl_btmesh_self_provisioning(device_key, network_key, primary_address);
}

void sl_btmesh_system_reset_from_cli(sl_cli_command_arg_t *arguments)
{
  (void)arguments;
  sl_bt_system_reset(0);
}

void sl_btmesh_add_app_key_from_cli(sl_cli_command_arg_t *arguments)
{
  size_t arg_length;
  uint8_t *input_arguments;
  aes_key_128 application_key;

  // Get the argument - application key
  input_arguments = sl_cli_get_argument_hex(arguments, 0, &arg_length);
  if (arg_length != KEY_LENGTH) {
    log_warning("Wrong device key length: %u, should be %d"NL, arg_length, KEY_LENGTH);
    return;
  }
  memcpy(application_key.data, input_arguments, arg_length);

  sl_btmesh_add_app_key(application_key);
}
#endif // SL_CATALOG_CLI_PRESENT

/***************************************************************************//**
   // Helper functions
 ******************************************************************************/
void sl_btmesh_self_provisioning(aes_key_128 dev_key,
                                 aes_key_128 net_key,
                                 uint16_t address)
{
  sl_status_t sc;
  uint32_t key_count;
  sl_btmesh_msg_t evt;

  log_info("Self provisioning started"NL);

  // Get the stored network key number
  sc = sl_btmesh_node_get_key_count(sl_btmesh_node_key_type_net, &key_count);
  if (sc != SL_STATUS_OK) {
    log_status_warning_f(sc, "Failed to get key count" NL);
    return;
  }

  // If there is stored network key the node is considered already provisioned
  if (key_count != 0) {
    log_warning("Netkey already stored: %ld"NL, key_count);
    return;
  }

  // Stop the unprovisioned beaconing
  sc = sl_btmesh_node_stop_unprov_beaconing();
  if (sc != SL_STATUS_OK) {
    log_status_warning_f(sc, "Failed to stop unprovisioned beaconing" NL);
    return;
  }

  // Save the provisioning data to make the device reachable and configurable
  // in the Provisioner's network.
  sc = sl_btmesh_node_set_provisioning_data(dev_key,
                                            net_key,
                                            KEY_INDEX,
                                            IV_INDEX,
                                            address,
                                            NOT_KEY_REFRESH);
  if (sc != SL_STATUS_OK) {
    log_status_warning_f(sc, "Failed to set provisioning data" NL);
    return;
  }

  log_info("Self provisioning successful" NL);

  // Node provisioned event processed
  evt.header = sl_btmesh_evt_node_provisioned_id;
  evt.data.evt_node_provisioned.address = address;
  evt.data.evt_node_provisioned.iv_index = IV_INDEX;
  sl_btmesh_process_event(&evt);

  // The device must be reset after saving provisioning data.
  sl_bt_system_reset(0);
}

void sl_btmesh_add_app_key(aes_key_128 app_key)
{
  sl_status_t sc;

  // Add application key
  sc = sl_btmesh_test_add_local_key(sl_btmesh_test_key_type_app,
                                    app_key,
                                    KEY_INDEX,
                                    APPKEY_BOUND_TO_NETKEY);
  if (sc != SL_STATUS_OK) {
    log_status_warning_f(sc, "Failed to add app key" NL);
    return;
  }

  log_info("Application key added"NL);
}

/** @} (end addtogroup SelfProvisioning) */
