/***************************************************************************//**
 * @file
 * @brief Zigbee BLE DMP - Common BLE CLI code
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include PLATFORM_HEADER
#include "hal.h"
#include "ember.h"
#include "sl_cli.h"
#include "sl_bluetooth.h"
#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif
#ifdef SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
#include "af.h"
#endif //SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT

#ifdef SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
#include "sl_zigbee_debug_print.h"
#endif // SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
#include "sl_bt_rtos_adaptation.h"
#include "sl_bluetooth_advertiser_config.h"
#include "sl_bluetooth_connection_config.h"
#ifdef SL_CATALOG_ZIGBEE_BLE_EVENT_HANDLER_PRESENT
#include "sl_ble_event_handler.h"
#endif //SL_CATALOG_ZIGBEE_BLE_EVENT_HANDLER_PRESENT
#define MAX_CHAR_SIZE                   252

// Advertisement data
#define UINT16_TO_BYTES(n)        ((uint8_t) (n)), ((uint8_t)((n) >> 8))
#define UINT16_TO_BYTE0(n)        ((uint8_t) (n))
#define UINT16_TO_BYTE1(n)        ((uint8_t) ((n) >> 8))
// Ble TX test macros and functions
#define BLE_TX_TEST_DATA_SIZE   2
// We need to put the device name into a scan response packet,
// since it isn't included in the 'standard' beacons -
// I've included the flags, since certain apps seem to expect them
#define DEVNAME "DMP%02X%02X"
#define DEVNAME_LEN 8  // incl term null
#define UUID_LEN 16 // 128-bit UUID
#define SOURCE_ADDRESS_LEN 8

#define OTA_SCAN_RESPONSE_DATA        0x04
#define OTA_ADVERTISING_DATA          0x02
#define PUBLIC_DEVICE_ADDRESS         0
#define STATIC_RANDOM_ADDRESS         1

/******************************************************************************
 * This component still has the style of Bluetooth BGAPI version 2.0 (last used
 * on 19Q4 GSDK) where the advertising data generation and setting are coupled
 * in the context of starting Bluetooth advertiser.
 *
 * New Bluetooth BGAPIs separated advertising data setting from starting the
 * advertiser. As a result some types are not used since BGAPI 3.0 on 20Q2 GSDK.
 * Define these types locally in this file so that the CLI host and device keep
 * to be functional as before.
 *****************************************************************************/

// The advertising broadcast discoverable mode, equivalent to the deprecated
// BGAPI enum sl_bt_advertiser_broadcast. This mode doesn't exist in latest API.
// Semantically it is the same as sl_bt_advertiser_non_discoverable.
#define BGAPI_ADVERTISER_MODE_BROADCAST    3

// The advertising user-data discoverable mode, equivalent to the deprecated
// enum sl_bt_advertiser_user_data. This mode does not exist in latest BGAPI
// which has no concept of user-data discoverable mode.
#define BGAPI_ADVERTISER_MODE_USER_DATA    4

static sl_status_t bleGenerateAdvertisingData(uint8_t adv_handle,
                                              uint8_t discoverable_mode)
{
  if (discoverable_mode == BGAPI_ADVERTISER_MODE_BROADCAST) {
    // The broadcast mode is mapped to sl_bt_advertiser_non_discoverable
    // in the context of Bluetooth stack generating the
    // advertising data.
    discoverable_mode = sl_bt_advertiser_non_discoverable;
  }

  sl_status_t status = sl_bt_legacy_advertiser_generate_data(adv_handle, discoverable_mode);
  if (status != SL_STATUS_OK) {
    sl_zigbee_app_debug_print("Generate ble advertising data error: 0x%2x\n", status);
  }
  return status;
}

void emberAfPluginBleHelloCommand(sl_cli_command_arg_t *arguments)
{
  sl_status_t status = sl_bt_system_hello();

  sl_zigbee_app_debug_print("BLE hello: %s",
                            (status == SL_STATUS_OK) ? "success" : "error");
}
#ifdef SL_CATALOG_BLUETOOTH_ON_DEMAND_START_PRESENT
void emberAfPluginBleStartCommand(sl_cli_command_arg_t *arguments)
{
  sl_status_t status = sl_bt_system_start_bluetooth();

  if (status == SL_STATUS_OK) {
    sl_zigbee_app_debug_print("Starting Bluetooth Stack: success\n");
  } else {
    sl_zigbee_app_debug_print("error: 0x%2x\n", status);
  }
}

void emberAfPluginBleStopCommand(sl_cli_command_arg_t *arguments)
{
  sl_status_t status = sl_bt_system_stop_bluetooth();

  if (status == SL_STATUS_OK) {
    sl_zigbee_app_debug_print("Stopping Bluetooth Stack: success\n");
  } else {
    sl_zigbee_app_debug_print("error: 0x%2x\n", status);
  }
}
#endif //SL_CATALOG_BLUETOOTH_ON_DEMAND_START_PRESENT
void emberAfPluginBleGetAddressCommand(sl_cli_command_arg_t *arguments)
{
  bd_addr ble_address;
  uint8_t type;

  (void)sl_bt_system_get_identity_address(&ble_address, &type);

  sl_zigbee_app_debug_print("\nBLE address: [%02X %02X %02X %02X %02X %02X]\n",
                            ble_address.addr[5], ble_address.addr[4], ble_address.addr[3],
                            ble_address.addr[2], ble_address.addr[1], ble_address.addr[0]);
}

void emberAfPluginBleSetAdvertisementParamsCommand(sl_cli_command_arg_t *arguments)
{
  uint8_t adv_handle = sl_cli_get_argument_uint8(arguments, 0);
  uint16_t min_interval = sl_cli_get_argument_uint16(arguments, 1);
  uint16_t max_interval = sl_cli_get_argument_uint16(arguments, 2);
  uint8_t channel_map = sl_cli_get_argument_uint8(arguments, 3);

  sl_status_t status = sl_bt_advertiser_set_channel_map(adv_handle, channel_map);

  if (status == SL_STATUS_OK) {
    status = sl_bt_advertiser_set_timing(adv_handle, // handle
                                         min_interval,
                                         max_interval,
                                         0, // duration : continue advertisement until stopped
                                         0); // max_events :continue advertisement until stopped
  }
  if (status == SL_STATUS_OK) {
    sl_zigbee_app_debug_print("success\n");
  } else {
    sl_zigbee_app_debug_print("error: 0x%2x\n", status);
  }
}

void emberAfPluginBleSetGapModeCommand(sl_cli_command_arg_t *arguments)
{
  uint8_t adv_handle = sl_cli_get_argument_uint8(arguments, 0);
  uint8_t discoverable_mode = sl_cli_get_argument_uint8(arguments, 1);
  uint8_t connectable_mode = sl_cli_get_argument_uint8(arguments, 2);

  if (discoverable_mode > BGAPI_ADVERTISER_MODE_USER_DATA
      || connectable_mode > sl_bt_advertiser_connectable_non_scannable) {
    sl_zigbee_app_debug_print("Invalid params");
    return;
  }

  sl_status_t status = SL_STATUS_OK;
  if (discoverable_mode < BGAPI_ADVERTISER_MODE_USER_DATA) {
    // Other discovery modes than user_data rely on the Bluetooth stack
    // generating the advertising data.
    status = bleGenerateAdvertisingData(adv_handle, discoverable_mode);
  }

  if (status == SL_STATUS_OK) {
    status = sl_bt_legacy_advertiser_start(adv_handle, connectable_mode);
  }

  if (status == SL_STATUS_OK) {
    sl_zigbee_app_debug_print("success\n");
  } else {
    sl_zigbee_app_debug_print("error: 0x%2x\n", status);
  }
}

void emberAfPluginBleSetBt5GapModeCommand(sl_cli_command_arg_t *arguments)
{
  uint8_t adv_handle = sl_cli_get_argument_uint8(arguments, 0);
  uint8_t discoverable_mode = sl_cli_get_argument_uint8(arguments, 1);
  uint8_t connectable_mode = sl_cli_get_argument_uint8(arguments, 2);
  uint16_t max_events = sl_cli_get_argument_uint16(arguments, 3);

  if (discoverable_mode > BGAPI_ADVERTISER_MODE_USER_DATA
      || connectable_mode > sl_bt_advertiser_connectable_non_scannable) {
    sl_zigbee_app_debug_print("Invalid params");
    return;
  }

  sl_status_t status = SL_STATUS_OK;
  if (discoverable_mode < BGAPI_ADVERTISER_MODE_USER_DATA) {
    // Other discovery modes than user_data rely on the Bluetooth stack
    // generating the advertising data.
    status = bleGenerateAdvertisingData(adv_handle, discoverable_mode);
  }

  if (status == SL_STATUS_OK) {
    status = sl_bt_advertiser_set_timing(adv_handle,
                                         (uint16_t)(100 / 0.625), //100ms min adv interval in terms of 0.625ms
                                         (uint16_t)(100 / 0.625), //100ms max adv interval in terms of 0.625ms
                                         0, // duration : continue advertisement until stopped
                                         max_events);
  }
  if (status == SL_STATUS_OK) {
    status = sl_bt_legacy_advertiser_start(adv_handle,
                                           connectable_mode);
  }

  if (status == SL_STATUS_OK) {
    sl_zigbee_app_debug_print("success\n");
  } else {
    sl_zigbee_app_debug_print("error: 0x%2x\n", status);
  }
}

#ifdef SL_CATALOG_BLUETOOTH_FEATURE_SCANNER_PRESENT

void emberAfPluginBleGapStartScanCommand(sl_cli_command_arg_t *arguments)
{
  uint8_t discovery_mode = sl_cli_get_argument_uint8(arguments, 0);
  if (discovery_mode > sl_bt_scanner_discover_observation) {
    sl_zigbee_app_debug_print("Invalid params");
    return;
  }

  // Preferred phy 1: 1M phy, 2: 2M phy, 4: 125k coded phy, 8: 500k coded phy
  sl_status_t status = sl_bt_scanner_start(sl_bt_gap_1m_phy, discovery_mode);

  if (status == SL_STATUS_OK) {
    sl_zigbee_app_debug_print("success\n");
  } else {
    sl_zigbee_app_debug_print("error: 0x%2x\n", status);
  }
}

void emberAfPluginBleGapStopScanCommand(sl_cli_command_arg_t *arguments)
{
  sl_status_t status = sl_bt_scanner_stop();

  if (status == SL_STATUS_OK) {
    sl_zigbee_app_debug_print("success\n");
  } else {
    sl_zigbee_app_debug_print("error: 0x%2x\n", status);
  }
}

void emberAfPluginBleGapScanConfigCommand(sl_cli_command_arg_t *arguments)
{
  uint8_t mode = sl_cli_get_argument_uint8(arguments, 0);
  uint16_t interval = sl_cli_get_argument_uint16(arguments, 1);
  uint16_t window = sl_cli_get_argument_uint16(arguments, 2);

  if (mode > sl_bt_scanner_scan_mode_active) {
    sl_zigbee_app_debug_print("Invalid params");
    return;
  }

  sl_status_t status = sl_bt_scanner_set_parameters(mode,
                                                    (uint16_t)(interval),
                                                    (uint16_t)(window));

  if (status == SL_STATUS_OK) {
    sl_zigbee_app_debug_print("success\n");
  } else {
    sl_zigbee_app_debug_print("error: 0x%2x\n", status);
  }
}

#endif // SL_CATALOG_BLUETOOTH_FEATURE_SCANNER_PRESENT

void emberAfPluginBleGapConnectionOpenCommand(sl_cli_command_arg_t *arguments)
{
  sl_status_t status;
  uint8_t address_type = sl_cli_get_argument_uint8(arguments, 1);
  bd_addr address;
  size_t _address_len;
  uint8_t *_address = (uint8_t *)&address;
  _address = sl_cli_get_argument_hex(arguments, 0, &_address_len);
  uint8_t connection_handle;
  emberReverseMemCopy((uint8_t *)&address, _address, sizeof(address));

  if (address_type > sl_bt_gap_random_nonresolvable_address) {
    sl_zigbee_app_debug_print("Invalid params");
    return;
  }

  status = sl_bt_connection_open(address, address_type, sl_bt_gap_1m_phy, &connection_handle);

  if (status == SL_STATUS_OK) {
    sl_zigbee_app_debug_print("success\n");
  } else {
    sl_zigbee_app_debug_print("error: 0x%2x\n", status);
  }
}

void emberAfPluginBleGapSetConnectionParamsCommand(sl_cli_command_arg_t *arguments)
{
  uint16_t min_interval = sl_cli_get_argument_uint16(arguments, 0);
  uint16_t max_interval = sl_cli_get_argument_uint16(arguments, 1);
  uint16_t slave_latency = sl_cli_get_argument_uint16(arguments, 2);
  uint16_t supervision_timeout = sl_cli_get_argument_uint16(arguments, 3);

  sl_status_t status = sl_bt_connection_set_default_parameters(min_interval,
                                                               max_interval,
                                                               slave_latency,
                                                               supervision_timeout,
                                                               0, // min_ce_length
                                                               0xFFFF); // max_ce_length

  if (status == SL_STATUS_OK) {
    sl_zigbee_app_debug_print("success\n");
  } else {
    sl_zigbee_app_debug_print("error: 0x%2x\n", status);
  }
}

void emberAfPluginBleConnectionSetParamsCommand(sl_cli_command_arg_t *arguments)
{
  uint16_t connection_handle = sl_cli_get_argument_uint16(arguments, 0);
  uint16_t min_interval = sl_cli_get_argument_uint16(arguments, 1);
  uint16_t max_interval = sl_cli_get_argument_uint16(arguments, 2);
  uint16_t slave_latency = sl_cli_get_argument_uint16(arguments, 3);
  uint16_t supervision_timeout = sl_cli_get_argument_uint16(arguments, 4);

  sl_status_t status =  sl_bt_connection_set_parameters(connection_handle,
                                                        min_interval,
                                                        max_interval,
                                                        slave_latency,
                                                        supervision_timeout,
                                                        0, // min_ce_length
                                                        0xFFFF); // max_ce_length

  if (status == SL_STATUS_OK) {
    sl_zigbee_app_debug_print("success\n");
  } else {
    sl_zigbee_app_debug_print("error: 0x%2x\n", status);
  }
}

void emberAfPluginBleSecurityManagerConfigureCommand(sl_cli_command_arg_t *arguments)
{
  uint8_t flags = sl_cli_get_argument_uint8(arguments, 0);
  uint8_t io_cap = sl_cli_get_argument_uint8(arguments, 1);

  sl_status_t status = sl_bt_sm_configure(flags, io_cap);

  if (status == SL_STATUS_OK) {
    sl_zigbee_app_debug_print("success\n");
  } else {
    sl_zigbee_app_debug_print("error: 0x%2x\n", status);
  }
}

void emberAfPluginBleSecurityManagerIncreaseSecurityCommand(sl_cli_command_arg_t *arguments)
{
  uint8_t connection_handle = sl_cli_get_argument_uint8(arguments, 0);

  sl_status_t status = sl_bt_sm_increase_security(connection_handle);

  if (status == SL_STATUS_OK) {
    sl_zigbee_app_debug_print("success\n");
  } else {
    sl_zigbee_app_debug_print("error: 0x%2x\n", status);
  }
}

void emberAfPluginBleSecurityManagerListAllBondingsCommand(sl_cli_command_arg_t *arguments)
{
  #define BLE_MAX_BONDINGS (32u) // The Bluetooth stack supports max 32 bondings
  sl_status_t status;

  for (uint8_t i = 0; i < BLE_MAX_BONDINGS; i++) {
    bd_addr address;
    uint8_t address_type;
    uint8_t security_mode;
    uint8_t key_size;
    status = sl_bt_sm_get_bonding_details(i,
                                          &address,
                                          &address_type,
                                          &security_mode,
                                          &key_size);

    if (status == SL_STATUS_OK) {
      sl_zigbee_app_debug_print("bonding handle %d", i);
      sl_zigbee_app_debug_print("\nBLE address: [%02X %02X %02X %02X %02X %02X]\n",
                                address.addr[5], address.addr[4], address.addr[3],
                                address.addr[2], address.addr[1], address.addr[0]);
      sl_zigbee_app_debug_print(" 0x%x 0x%x 0x%x \n", address_type, security_mode, key_size);
    }
  }
}

void emberAfPluginBleSecurityManagerDeleteBondingCommand(sl_cli_command_arg_t *arguments)
{
  uint8_t bonding_handle = sl_cli_get_argument_uint8(arguments, 0);

  sl_status_t status = sl_bt_sm_delete_bonding(bonding_handle);

  if (status == SL_STATUS_OK) {
    sl_zigbee_app_debug_print("success\n");
  } else {
    sl_zigbee_app_debug_print("error: 0x%2x\n", status);
  }
}

void emberAfPluginBleSecurityManagerDeleteAllBondingsCommand(sl_cli_command_arg_t *arguments)
{
  sl_status_t status = sl_bt_sm_delete_bondings();

  if (status == SL_STATUS_OK) {
    sl_zigbee_app_debug_print("success\n");
  } else {
    sl_zigbee_app_debug_print("error: 0x%2x\n", status);
  }
}

void emberAfPluginBleSecurityManagerSetBondableModeCommand(sl_cli_command_arg_t *arguments)
{
  uint8_t bondable_mode = sl_cli_get_argument_uint8(arguments, 0);

  if (bondable_mode > 1) {
    sl_zigbee_app_debug_print("Invalid params");
    return;
  }

  sl_status_t status = sl_bt_sm_set_bondable_mode(bondable_mode);

  if (status == SL_STATUS_OK) {
    sl_zigbee_app_debug_print("success\n");
  } else {
    sl_zigbee_app_debug_print("error: 0x%2x\n", status);
  }
}

void emberAfPluginBleSecurityManagerConfirmPasskeyCommand(sl_cli_command_arg_t *arguments)
{
  uint8_t connection = sl_cli_get_argument_uint8(arguments, 0);
  uint8_t confirm = sl_cli_get_argument_uint8(arguments, 1);

  sl_status_t status = sl_bt_sm_passkey_confirm(connection, confirm);

  if (status == SL_STATUS_OK) {
    sl_zigbee_app_debug_print("success\n");
  } else {
    sl_zigbee_app_debug_print("error: 0x%2x\n", status);
  }
}

void emberAfPluginBleSecurityManagerEnterPasskeyCommand(sl_cli_command_arg_t *arguments)
{
  uint8_t connection = sl_cli_get_argument_uint8(arguments, 0);
  uint32_t passkey = sl_cli_get_argument_uint32(arguments, 1);

  sl_status_t status = sl_bt_sm_enter_passkey(connection, passkey);

  if (status == SL_STATUS_OK) {
    sl_zigbee_app_debug_print("success\n");
  } else {
    sl_zigbee_app_debug_print("error: 0x%2x\n", status);
  }
}

void emberAfPluginBleGattDiscoverPrimaryServicesCommand(sl_cli_command_arg_t *arguments)
{
  uint8_t connection_handle = sl_cli_get_argument_uint8(arguments, 0);

  sl_status_t status = sl_bt_gatt_discover_primary_services(connection_handle);

  if (status == SL_STATUS_OK) {
    sl_zigbee_app_debug_print("success\n");
  } else {
    sl_zigbee_app_debug_print("error: 0x%2x\n", status);
  }
}

void emberAfPluginBleGattDiscoverCharacteristicsCommand(sl_cli_command_arg_t *arguments)
{
  uint8_t connection_handle = sl_cli_get_argument_uint8(arguments, 0);
  uint32_t service_handle = sl_cli_get_argument_uint32(arguments, 1);

  sl_status_t status = sl_bt_gatt_discover_characteristics(connection_handle, service_handle);

  if (status == SL_STATUS_OK) {
    sl_zigbee_app_debug_print("success\n");
  } else {
    sl_zigbee_app_debug_print("error: 0x%2x\n", status);
  }
}

void emberAfPluginBleGattSetCharacteristicNotificationCommand(sl_cli_command_arg_t *arguments)
{
  uint8_t connection_handle = sl_cli_get_argument_uint8(arguments, 0);
  uint16_t char_handle = sl_cli_get_argument_uint16(arguments, 1);
  uint8_t flags = sl_cli_get_argument_uint8(arguments, 2);

  sl_status_t status = sl_bt_gatt_set_characteristic_notification(connection_handle,
                                                                  char_handle,
                                                                  flags);
  if (status == SL_STATUS_OK) {
    sl_zigbee_app_debug_print("success\n");
  } else {
    sl_zigbee_app_debug_print("error: 0x%2x\n", status);
  }
}

void emberAfPluginBleGattWriteCharacteristicValueCommand(sl_cli_command_arg_t *arguments)
{
  size_t value_len;
  uint8_t connection_handle = sl_cli_get_argument_uint8(arguments, 0);
  uint16_t characteristic = sl_cli_get_argument_uint16(arguments, 1);
  uint8_t *value = sl_cli_get_argument_hex(arguments, 2, (size_t *)&value_len);

  sl_status_t status = sl_bt_gatt_write_characteristic_value(connection_handle,
                                                             characteristic,
                                                             (size_t)value_len,
                                                             value);

  if (status == SL_STATUS_OK) {
    sl_zigbee_app_debug_print("success\n");
  } else {
    sl_zigbee_app_debug_print("error: 0x%2x\n", status);
  }
}

void emberAfPluginBleConnectionCloseCommand(sl_cli_command_arg_t *arguments)
{
  uint8_t connection_handle = sl_cli_get_argument_uint8(arguments, 0);

  sl_status_t status = sl_bt_connection_close(connection_handle);

  if (status == SL_STATUS_OK) {
    sl_zigbee_app_debug_print("success\n");
  } else {
    sl_zigbee_app_debug_print("error: 0x%2x\n", status);
  }
}

void emberAfPluginBleStopAdvertising(sl_cli_command_arg_t *arguments)
{
  uint8_t adv_handle = sl_cli_get_argument_uint8(arguments, 0);

  if ( adv_handle != 0xFF ) {
    sl_status_t status = sl_bt_advertiser_stop(adv_handle);
    if (status == SL_STATUS_OK) {
      sl_zigbee_app_debug_print("success\n");
    } else {
      sl_zigbee_app_debug_print("error: 0x%2x\n", status);
    }
  }
}

void emberAfPluginBleSetTxPowerCommand(sl_cli_command_arg_t *arguments)
{
  int16_t tx_power_set_value = sl_cli_get_argument_int16(arguments, 0);
  int16_t tx_power_min_val = 0xFF;
  int16_t tx_power_max_val = 0xFF;

  /* Set max and min transmit power to 0 dBm */
  sl_status_t status = sl_bt_system_set_tx_power(tx_power_set_value, tx_power_set_value, &tx_power_min_val, &tx_power_max_val);

  if (status == SL_STATUS_OK) {
    sl_zigbee_app_debug_print("tx power is set to: %d.%ddBm", (tx_power_min_val / 10), (tx_power_min_val % 10));
  } else {
    sl_zigbee_app_debug_print("error: 0x%2x", status);
  }
}

void sl_dmp_print_connections(sl_cli_command_arg_t *arguments)
{
  (void)arguments;
  #ifdef SL_CATALOG_ZIGBEE_BLE_EVENT_HANDLER_PRESENT
  zb_ble_dmp_print_ble_connections();
  #endif //SL_CATALOG_ZIGBEE_BLE_EVENT_HANDLER_PRESENT
}
