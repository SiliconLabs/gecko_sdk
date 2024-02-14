/***************************************************************************//**
 * @file zigbee_direct_common.c
 * @brief Zigbee Direct Common
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc.  Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement.  This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
#include PLATFORM_HEADER
#include "app/framework/include/af.h"
#include "app/framework/util/af-main.h"
#include "app/framework/util/util.h"
#include "app/framework/util/common.h"

#include "sl_component_catalog.h"
#ifdef SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
#include "sl_zigbee_debug_print.h"
#endif // SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
#ifdef SL_CATALOG_ZIGBEE_DISPLAY_PRESENT
#include "app/framework/plugin/dmp-ui-demo/sl_dmp_ui.h"
#endif // SL_CATALOG_ZIGBEE_DISPLAY_PRESENT
#ifdef SL_CATALOG_ZIGBEE_DIRECT_TUNNELING_PRESENT
#include "zigbee_direct_tunneling.h"
#endif //SL_CATALOG_ZIGBEE_DIRECT_TUNNELING_PRESENT

#include "sl_bluetooth.h"
#include "gatt_db.h"
#include "stack/include/ember-types.h"
#include "stack/include/sl_zigbee_tlv_core.h"
#include "stack/include/sl_zigbee_stack_specific_tlv.h"
#include "stack/include/zigbee-security-manager.h"
#include "zigbee_direct_tlv.h"
#include "zigbee_direct_session_key_negotiation.h"
#include "zigbee_direct_common.h"
#include "zap-cluster-command-parser.h"
#include "app/framework/plugin/find-and-bind-initiator/find-and-bind-initiator.h"
#include "app/framework/plugin/find-and-bind-target/find-and-bind-target.h"
#include "app/framework/plugin/network-steering/network-steering.h"
#include "app/framework/plugin/network-creator-security/network-creator-security.h"
#include "app/framework/plugin/network-creator/network-creator.h"

//some macros
#define DEVNAME_LEN 5  // incl term null
#define UUID_LEN 16 // 128-bit UUID

#define SL_ZIGBEE_DIRECT_JOINING_METHOD_MAC_ASSOCIATION 0x00
#define SL_ZIGBEE_DIRECT_JOINING_METHOD_NWK_REJOIN_WITH_KEY 0x01
#define SL_ZIGBEE_DIRECT_JOINING_METHOD_OOB_NO_BEACON_CHECK 0x02

#define SLI_ZIGBEE_CHECK_KEY_ALL_ZERO(key_ptr) ((*key_ptr == 0x00) && (memcmp(key_ptr, key_ptr + 1, EMBER_ENCRYPTION_KEY_SIZE - 1) == 0))

// prototypes
static void sli_zigbee_direct_commissioning_status_read(uint8_t connection);
static void sli_zigbee_direct_permit_joining_write(uint8_t connection, uint8array *writeValue);
static void sli_zigbee_direct_identify_read(uint8_t connection);
static void sli_zigbee_direct_leave_network_write(uint8_t connection, uint8array *writeValue);
static void sli_zigbee_direct_join_network_write(uint8_t connection, uint8array *writeValue);
static void sli_zigbee_direct_form_network_write(uint8_t connection, uint8array *writeValue);
static void sli_zigbee_direct_identify_write(uint8_t connection, uint8array *writeValue);
static void sli_zigbee_direct_manage_joiners_write(uint8_t connection, uint8array *writeValue);
static void sli_zigbee_direct_finding_binding_write(uint8_t connection, uint8array *writeValue);

#ifdef SL_CATALOG_ZIGBEE_DIRECT_SECURITY_P256_PRESENT
static void sli_zigbee_direct_authenticate_write_p256(uint8_t connection, uint8array *writeValue);
#endif // SL_CATALOG_ZIGBEE_DIRECT_SECURITY_P256_PRESENT

#ifdef SL_CATALOG_ZIGBEE_DIRECT_SECURITY_CURVE25519_PRESENT
static void sli_zigbee_direct_authenticate_write_25519(uint8_t connection, uint8array *writeValue);
#endif // SL_CATALOG_ZIGBEE_DIRECT_SECURITY_CURVE25519_PRESENT

static void sli_zigbee_direct_send_status_via_commissioning_status_notification(uint8_t connection, uint8_t status_domain, uint8_t status_code);
static EmberStatus sli_zigbee_direct_oob_join(void);
static uint8_t sli_channel_masks_first_channel(uint32_t sl_channel_mask);
static void sli_zigbee_direct_extract_data_from_tlvs_buf(Buffer my_Buffer, uint8_t len);
static uint8_t sli_zigbee_direct_form_network(sl_zigbee_tlv_tag_list* tlvs_for_forming);
static void send_network_status_notification(uint8_t connection);

//globals
EmberNetworkParameters sl_zigbee_direct_network_params;
EmberInitialSecurityState sl_zigbee_direct_security_state;
static uint8_t activeBleConnections = 0;
static uint32_t sl_my_channelMask;
uint16_t sl_zvd_node_id = 0xFFFF;
EmberEUI64 sl_zvd_eui;
uint8_t sl_zvd_public_point_x[DLK_ECC_COORDINATE_SIZE];
uint8_t sl_zvd_public_point_y[DLK_ECC_COORDINATE_SIZE];
sl_zigbee_direct_connection_status_t sl_zvd_connection_status;
sl_zigbee_direct_connection_status_t sl_zvd_connection_status_next = OPEN_TO_BE_PROVISIONED;
bool form_in_process = false;
bool sli_zd_admin_key_provided_when_joining = false;
bool advertisements_enabled = false;
uint8_t admin_key[16];
extern uint8_t  appResponseData[EMBER_AF_RESPONSE_BUFFER_LEN];
extern bool sli_zigbee_remove_transient_link_key(EmberEUI64 eui64ToFind, EmberKeyStructBitmask* bitmask);
extern uint8_t sli_zigbee_get_nwk_update_id(void);

// to convert hex number to its ascii character
uint8_t ascii_lut[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

static uint8_t zigbee_direct_mac_assoc_excl_tags[] = {
  SL_ZIGBEE_DIRECT_TLV_NETWORK_KEY_TAG_ID,
  SL_ZIGBEE_DIRECT_TLV_DEVICE_TYPE_TAG_ID,
  SL_ZIGBEE_DIRECT_TLV_IEEE_ADDRESS_TAG_ID,
  SL_ZIGBEE_DIRECT_TLV_NETWORK_STATUS_MAP_TAG_ID,
  SL_ZIGBEE_DIRECT_TLV_NETWORK_UPDATE_ID_TAG_ID,
  SL_ZIGBEE_DIRECT_TLV_NETWORK_ACTIVE_KEY_SEQ_NUMBER_TAG_ID,
};
static sl_zigbee_tlv_tag_list zigbee_direct_mac_assoc_excl_tag_list = { sizeof(zigbee_direct_mac_assoc_excl_tags), zigbee_direct_mac_assoc_excl_tags };

static uint8_t zigbee_direct_nwk_rejoin_excl_tags[] = {
  SL_ZIGBEE_DIRECT_TLV_NETWORK_KEY_TAG_ID,
  SL_ZIGBEE_DIRECT_TLV_LINK_KEY_TAG_ID,
  SL_ZIGBEE_DIRECT_TLV_NWK_ADDRESS_TAG_ID,
  SL_ZIGBEE_DIRECT_TLV_DEVICE_TYPE_TAG_ID,
  SL_ZIGBEE_DIRECT_TLV_IEEE_ADDRESS_TAG_ID,
  SL_ZIGBEE_DIRECT_TLV_NETWORK_STATUS_MAP_TAG_ID,
  SL_ZIGBEE_DIRECT_TLV_NETWORK_UPDATE_ID_TAG_ID,
  SL_ZIGBEE_DIRECT_TLV_NETWORK_ACTIVE_KEY_SEQ_NUMBER_TAG_ID
};
static sl_zigbee_tlv_tag_list zigbee_direct_nwk_rejoin_excl_tag_list = { sizeof(zigbee_direct_nwk_rejoin_excl_tags), zigbee_direct_nwk_rejoin_excl_tags };

static uint8_t zigbee_direct_nwk_oob_excl_tags[] = {
  SL_ZIGBEE_DIRECT_TLV_DEVICE_TYPE_TAG_ID,
  SL_ZIGBEE_DIRECT_TLV_IEEE_ADDRESS_TAG_ID,
  SL_ZIGBEE_DIRECT_TLV_NETWORK_STATUS_MAP_TAG_ID
};
static sl_zigbee_tlv_tag_list zigbee_direct_nwk_oob_excl_tag_list = { sizeof(zigbee_direct_nwk_oob_excl_tags), zigbee_direct_nwk_oob_excl_tags };

static uint8_t zigbee_direct_nwk_oob_incl_tags[] = {
  SL_ZIGBEE_DIRECT_TLV_EXTENDED_PAN_ID_TAG_ID,
  SL_ZIGBEE_DIRECT_TLV_PAN_ID_TAG_ID,
  SL_ZIGBEE_DIRECT_TLV_NETWORK_CHANNEL_MASK_TAG_ID,
  SL_ZIGBEE_DIRECT_TLV_NETWORK_KEY_TAG_ID
};
static sl_zigbee_tlv_tag_list zigbee_direct_nwk_oob_incl_tag_list = { sizeof(zigbee_direct_nwk_oob_incl_tags), zigbee_direct_nwk_oob_incl_tags };

static uint8_t zigbee_direct_nwk_form_excl_tags[] = {
  SL_ZIGBEE_DIRECT_TLV_DEVICE_TYPE_TAG_ID,
  SL_ZIGBEE_DIRECT_TLV_JOINING_METHOD_TAG_ID,
  SL_ZIGBEE_DIRECT_TLV_IEEE_ADDRESS_TAG_ID,
  SL_ZIGBEE_DIRECT_TLV_NETWORK_STATUS_MAP_TAG_ID
};
static sl_zigbee_tlv_tag_list zigbee_direct_nwk_form_excl_tag_list = { sizeof(zigbee_direct_nwk_form_excl_tags), zigbee_direct_nwk_form_excl_tags };

// ZigBee Direct TLV env
sl_zigbee_tlv_tag_min_length_t zigbee_direct_tlv_env[] =
{ { .tag_id = SL_ZIGBEE_DIRECT_TLV_EXTENDED_PAN_ID_TAG_ID,
    .min_length = SL_ZIGBEE_DIRECT_TLV_EXTENDED_PAN_ID_MIN_LEN, },
  { .tag_id = SL_ZIGBEE_DIRECT_TLV_PAN_ID_TAG_ID,
    .min_length = SL_ZIGBEE_DIRECT_TLV_PAN_ID_MIN_LEN, },
  { .tag_id = SL_ZIGBEE_DIRECT_TLV_NETWORK_CHANNEL_MASK_TAG_ID,
    .min_length = SL_ZIGBEE_DIRECT_TLV_NETWORK_CHANNEL_MASK_MIN_LEN, },
  { .tag_id = SL_ZIGBEE_DIRECT_TLV_NETWORK_KEY_TAG_ID,
    .min_length = SL_ZIGBEE_DIRECT_TLV_NETWORK_KEY_MIN_LEN, },
  { .tag_id = SL_ZIGBEE_DIRECT_TLV_LINK_KEY_TAG_ID,
    .min_length = SL_ZIGBEE_DIRECT_TLV_LINK_KEY_MIN_LEN, },
  { .tag_id = SL_ZIGBEE_DIRECT_TLV_DEVICE_TYPE_TAG_ID,
    .min_length = SL_ZIGBEE_DIRECT_TLV_DEVICE_TYPE_MIN_LEN, },
  { .tag_id = SL_ZIGBEE_DIRECT_TLV_NWK_ADDRESS_TAG_ID,
    .min_length = SL_ZIGBEE_DIRECT_TLV_NWK_ADDRESS_MIN_LEN, },
  { .tag_id = SL_ZIGBEE_DIRECT_TLV_JOINING_METHOD_TAG_ID,
    .min_length = SL_ZIGBEE_DIRECT_TLV_JOINING_METHOD_MIN_LEN, },
  { .tag_id = SL_ZIGBEE_DIRECT_TLV_IEEE_ADDRESS_TAG_ID,
    .min_length = SL_ZIGBEE_DIRECT_TLV_IEEE_ADDRESS_MIN_LEN, },
  { .tag_id = SL_ZIGBEE_DIRECT_TLV_TRUST_CENTER_ADDRESS_TAG_ID,
    .min_length = SL_ZIGBEE_DIRECT_TLV_TRUST_CENTER_ADDRESS_MIN_LEN, },
  { .tag_id = SL_ZIGBEE_DIRECT_TLV_NETWORK_STATUS_MAP_TAG_ID,
    .min_length = SL_ZIGBEE_DIRECT_TLV_NETWORK_STATUS_MAP_MIN_LEN, },
  { .tag_id = SL_ZIGBEE_DIRECT_TLV_NETWORK_UPDATE_ID_TAG_ID,
    .min_length = SL_ZIGBEE_DIRECT_TLV_NETWORK_UPDATE_ID_MIN_LEN, },
  { .tag_id = SL_ZIGBEE_DIRECT_TLV_NETWORK_ACTIVE_KEY_SEQ_NUMBER_TAG_ID,
    .min_length = SL_ZIGBEE_DIRECT_TLV_NETWORK_ACTIVE_KEY_SEQ_NUMBER_MIN_LEN, },
  { .tag_id = SL_ZIGBEE_DIRECT_TLV_DISTRIBUTED_SECURITY_ADMIN_KEY_TAG_ID,
    .min_length = SL_ZIGBEE_DIRECT_TLV_DISTRIBUTED_SECURITY_ADMIN_KEY_MIN_LEN, },
  { .tag_id = SL_ZIGBEE_DIRECT_TLV_STATUS_CODE_TAG_ID,
    .min_length = SL_ZIGBEE_DIRECT_TLV_EXTENDED_STATUS_CODE_TAG_ID, },
  { .tag_id = SL_ZIGBEE_DIRECT_TLV_EXTENDED_STATUS_CODE_KEY_MIN_LEN,
    .min_length = SL_ZIGBEE_DIRECT_TLV_STATUS_CODE_KEY_MIN_LEN, },
  { .tag_id = SL_ZIGBEE_DIRECT_TUNNELING_TLV_NPDU_MESSAGE_TAG_ID,
    .min_length = SL_ZIGBEE_DIRECT_TUNNELING_TLV_NPDU_MESSAGE_MIN_LEN, },
  { .tag_id = SL_ZIGBEE_DIRECT_SECURITY_TLV_SELECTED_KEY_NEGOTIATION_METHOD_TAG_ID,
    .min_length = SL_ZIGBEE_DIRECT_SECURITY_TLV_SELECTED_KEY_NEGOTIATION_METHOD_MIN_LEN, },
#ifdef SL_CATALOG_ZIGBEE_DIRECT_SECURITY_P256_PRESENT
  { .tag_id = SL_ZIGBEE_DIRECT_SECURITY_TLV_P256_PUBLIC_POINT_TAG_ID,
    .min_length = SL_ZIGBEE_DIRECT_SECURITY_TLV_P256_PUBLIC_POINT_MIN_LEN, },
#endif // SL_CATALOG_ZIGBEE_DIRECT_SECURITY_P256_PRESENT
#ifdef SL_CATALOG_ZIGBEE_DIRECT_SECURITY_CURVE25519_PRESENT
  { .tag_id = SL_ZIGBEE_DIRECT_SECURITY_TLV_C25519_PUBLIC_POINT_TAG_ID,
    .min_length = SL_ZIGBEE_DIRECT_SECURITY_TLV_C25519_PUBLIC_POINT_MIN_LEN, },
#endif // SL_CATALOG_ZIGBEE_DIRECT_SECURITY_CURVE25519_PRESENT
  { .tag_id = SL_ZIGBEE_DIRECT_SECURITY_TLV_KEY_SEQUENCE_NUMBER_TAG_ID,
    .min_length = SL_ZIGBEE_DIRECT_SECURITY_TLV_KEY_SEQUENCE_NUMBER_MIN_LEN, },
  { .tag_id = SL_ZIGBEE_DIRECT_SECURITY_TLV_MAC_TAG_TAG_ID,
    .min_length = SL_ZIGBEE_DIRECT_SECURITY_TLV_MAC_TAG_MIN_LEN, },
  TLV_ENV_TERMINATOR, };

// BLE CHARACTERISTIC RELATED  ---
/** GATT Server Attribute User Read Configuration.
 *  Structure to register handler functions to user read events. */
typedef struct {
  uint16_t charId; /**< ID of the Characteristic. */
  void (*fctn)(uint8_t connection); /**< Handler function. */
} AppCfgGattServerUserReadRequest_t;

/** GATT Server Attribute Value Write Configuration.
 *  Structure to register handler functions to characteristic write events. */
typedef struct {
  uint16_t charId; /**< ID of the Characteristic. */
  /**< Handler function. */
  void (*fctn)(uint8_t connection, uint8array * writeValue);
} AppCfgGattServerUserWriteRequest_t;

static const AppCfgGattServerUserReadRequest_t appCfgGattServerUserReadRequest[] =
{
  { gattdb_commissioning_status, sli_zigbee_direct_commissioning_status_read },
  { gattdb_identify, sli_zigbee_direct_identify_read },
  { 0, NULL }
};

static const AppCfgGattServerUserWriteRequest_t appCfgGattServerUserWriteRequest[] =
{
  { gattdb_permit_joining, sli_zigbee_direct_permit_joining_write },
  { gattdb_leave_network, sli_zigbee_direct_leave_network_write },
  { gattdb_join_network, sli_zigbee_direct_join_network_write },
  { gattdb_form_network, sli_zigbee_direct_form_network_write },
  { gattdb_identify, sli_zigbee_direct_identify_write },
  { gattdb_manage_joiners, sli_zigbee_direct_manage_joiners_write },
  { gattdb_finding_binding, sli_zigbee_direct_finding_binding_write },
#ifdef SL_CATALOG_ZIGBEE_DIRECT_TUNNELING_PRESENT
  { gattdb_zigbee_tunnel_2, sl_zigbee_direct_tunnel_write },
#endif //SL_CATALOG_ZIGBEE_DIRECT_TUNNELING_PRESENT
#ifdef SL_CATALOG_ZIGBEE_DIRECT_SECURITY_P256_PRESENT
  { gattdb_authenticate_p256, sli_zigbee_direct_authenticate_write_p256 },
#endif // SL_CATALOG_ZIGBEE_DIRECT_SECURITY_P256_PRESENT
#ifdef SL_CATALOG_ZIGBEE_DIRECT_SECURITY_CURVE25519_PRESENT
  { gattdb_authenticate_25519, sli_zigbee_direct_authenticate_write_25519 },
#endif // SL_CATALOG_ZIGBEE_DIRECT_SECURITY_CURVE25519_PRESENT
  { 0, NULL }
};

size_t appCfgGattServerUserReadRequestSize = COUNTOF(appCfgGattServerUserReadRequest) - 1;
size_t appCfgGattServerUserWriteRequestSize = COUNTOF(appCfgGattServerUserWriteRequest) - 1;
// --- BLE CHARACTERISTIC RELATED

/* Advertising handles */

enum {
  START_STATE = 0,
  LEAVE_WRITE,
  PERMIT_JOIN_WRITE,
  MANAGE_JOINERS_WRITE,
  JOIN_NWK_WRITE,
  FORM_NWK_WRITE,
  IDENTIFY_WRITE,
  BINDING_WRITE,
  P256_WRITE,
  C25519_WRITE,
};

static uint8_t current_connection = 0;
static uint8array *current_writeValue;
static uint8_t current_state = START_STATE;
uint8_t adv_handle[MAX_ADV_HANDLES];
bleConnectionTable_t bleConnectionTable[SL_BT_CONFIG_MAX_CONNECTIONS];

uint8_t sli_zigbee_direct_ad_data[SL_ZIGBEE_DIRECT_ADVERTISEMENT_LENGTH] = { 0x02, // length (incl type)
                                                                             0x01, // type
                                                                             0x04 | 0x02, // Flags: LE General Discoverable Mode, BR/EDR is disabled
                                                                             0x03, // length, used to be 0x02
                                                                             0x02, // AD Type
                                                                             0xF7, // AD Data 16-bit UUID of the device's main service
                                                                             0xFF, // AD Data 16-bit UUID of the device's main service
                                                                             0x08, // length again
                                                                             0x16, // Service Data, 16-bit UUID
                                                                             0xF7, // AD Data 16-bit UUID of the device's main service
                                                                             0xFF, // AD Data 16-bit UUID of the device's main service
                                                                             0x11, // example data
                                                                             0xFF, // PAN ID
                                                                             0xFF, // PAN ID
                                                                             0xFF, // network ID
                                                                             0xFF // network ID
};

static uint8_t sli_zigbee_direct_resp[] = { 12,   // length (incl type)
                                            0x09, // type
                                            'S',
                                            'L',
                                            '_',
                                            'Z',
                                            'D',
                                            'D',
                                            '1',
                                            '2',
                                            '3',
                                            '4',
                                            '\0' };

void zb_ble_dmp_print_ble_address(uint8_t *address)
{
  sl_zigbee_core_debug_println("BLE address: [%X %X %X %X %X %X]",
                               address[5], address[4], address[3],
                               address[2], address[1], address[0]);
}

void bleConnectionInfoTableInit(void)
{
  uint8_t i;
  for (i = 0; i < SL_BT_CONFIG_MAX_CONNECTIONS; i++) {
    bleConnectionTable[i].inUse = false;
  }
}

uint8_t bleConnectionInfoTableFindUnused(void)
{
  uint8_t i;
  for (i = 0; i < SL_BT_CONFIG_MAX_CONNECTIONS; i++) {
    if (!bleConnectionTable[i].inUse) {
      return i;
    }
  }
  return 0xFF;
}

bool bleConnectionInfoTableIsEmpty(void)
{
  uint8_t i;
  for (i = 0; i < SL_BT_CONFIG_MAX_CONNECTIONS; i++) {
    if (bleConnectionTable[i].inUse) {
      return false;
    }
  }
  return true;
}

uint8_t bleConnectionInfoTableLookup(uint8_t connHandle)
{
  uint8_t i;
  for (i = 0; i < SL_BT_CONFIG_MAX_CONNECTIONS; i++) {
    if (bleConnectionTable[i].inUse
        && bleConnectionTable[i].connectionHandle == connHandle) {
      return i;
    }
  }
  return 0xFF;
}

void bleConnectionInfoTablePrintEntry(uint8_t index)
{
  assert(index < SL_BT_CONFIG_MAX_CONNECTIONS
         && bleConnectionTable[index].inUse);
  sl_zigbee_core_debug_println("**** Connection Info index[%d]****", index);
  sl_zigbee_core_debug_println("connection handle 0x%x",
                               bleConnectionTable[index].connectionHandle);
  sl_zigbee_core_debug_println("bonding handle = 0x%x",
                               bleConnectionTable[index].bondingHandle);
  sl_zigbee_core_debug_println("local node is %s",
                               (bleConnectionTable[index].isMaster) ? "master" : "slave");
  sl_zigbee_core_debug_print("remote address: ");
  zb_ble_dmp_print_ble_address(bleConnectionTable[index].remoteAddress);
  sl_zigbee_core_debug_println("");
  sl_zigbee_core_debug_println("*************************");
}

void enableBleAdvertisements(void)
{
  sl_status_t status;
  int16_t min_tx_power_set_value = 100;
  int16_t min_tx_power_get_value = 0xFF;
  int16_t max_tx_power_set_value = 100;
  int16_t max_tx_power_get_value = 0xFF;

  advertisements_enabled = true;

  /* Create the device Id and name based on the 16-bit truncated bluetooth address
     Copy to the local GATT database - this will be used by the BLE stack
     to put the local device name into the advertisements, but only if we are
     using default advertisements */
  uint8_t type;
  bd_addr ble_address;
  static char devName[DEVNAME_LEN];

  /* Set transmit power to 0 dBm */
  status = sl_bt_system_set_tx_power(min_tx_power_set_value, max_tx_power_set_value, &min_tx_power_get_value, &max_tx_power_get_value);
  if ( status != SL_STATUS_OK ) {
    sl_zigbee_core_debug_println("Unable to set min Tx Power to %d, max power to %d. Error code: %X", min_tx_power_get_value, max_tx_power_get_value, status);
    return;
  }
  sl_zigbee_core_debug_println("Set Min Tx Power to %d.", min_tx_power_get_value);

  status = sl_bt_system_get_identity_address(&ble_address, &type);
  if ( status != SL_STATUS_OK ) {
    sl_zigbee_core_debug_println("Unable to get BLE address. Error code: 0x%x", status);
    return;
  }

  devName[0] = ascii_lut[( (ble_address.addr[1] & 0xF0) >> 4)];
  devName[1] = ascii_lut[(ble_address.addr[1] & 0x0F)];
  devName[2] = ascii_lut[( (ble_address.addr[0] & 0xF0) >> 4)];
  devName[3] = ascii_lut[(ble_address.addr[0] & 0x0F)];
  devName[4] = '\0';

  sl_zigbee_core_debug_println("devName = %s", devName);
  status = sl_bt_gatt_server_write_attribute_value(gattdb_device_name,
                                                   0,
                                                   strlen(devName),
                                                   (uint8_t *)devName);

  if ( status != SL_STATUS_OK ) {
    sl_zigbee_core_debug_println("Unable to sl_bt_gatt_server_write_attribute_value device name. Error code: 0x%x", status);
    return;
  }

  sl_dmp_ui_set_ble_device_name(devName);   //LCD display

  /* Copy the shortened device name to the response data, overwriting
     the default device name which is set at compile time */
  MEMCOPY(((uint8_t*) &sli_zigbee_direct_resp) + 8, devName, DEVNAME_LEN);

  /* Set the advertising data and scan response data*/
  /* Note that the Wireless Gecko mobile app filters by a specific UUID and
     if the advertising data is not set, the device will not be found on the app*/
  status = sl_bt_legacy_advertiser_set_data(adv_handle[HANDLE_ZIGBEE_DIRECT],
                                            0,      //advertising packets
                                            SL_ZIGBEE_DIRECT_ADVERTISEMENT_LENGTH,
                                            (uint8_t*) &sli_zigbee_direct_ad_data);

  if (status != SL_STATUS_OK) {
    sl_zigbee_core_debug_println("Unable to set adv data sl_bt_legacy_advertiser_set_data. Error code: 0x%x", status);
    return;
  }

  status = sl_bt_legacy_advertiser_set_data(adv_handle[HANDLE_ZIGBEE_DIRECT],
                                            1,      //scan response packets
                                            sizeof(sli_zigbee_direct_resp),
                                            (uint8_t*) &sli_zigbee_direct_resp);
  if (status != SL_STATUS_OK) {
    sl_zigbee_core_debug_println("Unable to set scan response data sl_bt_legacy_advertiser_set_data. Error code: 0x%x", status);
    return;
  }

  status = sl_bt_advertiser_set_timing(adv_handle[HANDLE_ZIGBEE_DIRECT],
                                       (100 / 0.625), //100ms min adv interval in terms of 0.625ms
                                       (100 / 0.625), //100ms max adv interval in terms of 0.625ms
                                       0,   // duration : continue advertisement until stopped
                                       0);   // max_events :continue advertisement until stopped
  if (status != SL_STATUS_OK) {
    return;
  }
  status = sl_bt_advertiser_set_report_scan_request(adv_handle[HANDLE_ZIGBEE_DIRECT], 1);   //scan request reported as events
  if (status != SL_STATUS_OK) {
    return;
  }
  /* Start advertising in user mode and enable connections*/
  status = sl_bt_legacy_advertiser_start(adv_handle[HANDLE_ZIGBEE_DIRECT],
                                         sl_bt_advertiser_connectable_scannable);
  if ( status ) {
    sl_zigbee_core_debug_println("sl_bt_legacy_advertiser_start ERROR : status = 0x%0X", status);
  } else {
    sl_zigbee_core_debug_println("BLE custom advertisements enabled");
  }
}

/** @brief
 *
 * This function is called from the BLE stack to notify the application of a
 * stack event.
 */
void sl_bt_on_event(sl_bt_msg_t* evt)
{
  switch (SL_BT_MSG_ID(evt->header)) {
    /* This event indicates that a remote GATT client is attempting to read a value of an
     *  attribute from the local GATT database, where the attribute was defined in the GATT
     *  XML firmware configuration file to have type="user". */

    case sl_bt_evt_gatt_server_user_read_request_id:
      for (uint32_t i = 0; i < appCfgGattServerUserReadRequestSize; i++) {
        if ((appCfgGattServerUserReadRequest[i].charId
             == evt->data.evt_gatt_server_user_read_request.characteristic)
            && (appCfgGattServerUserReadRequest[i].fctn)) {
          appCfgGattServerUserReadRequest[i].fctn(
            evt->data.evt_gatt_server_user_read_request.connection);
        }
      }
      break;

    /* This event indicates that a remote GATT client is attempting to write a value of an
     * attribute in to the local GATT database, where the attribute was defined in the GATT
     * XML firmware configuration file to have type="user".  */

    case sl_bt_evt_gatt_server_user_write_request_id:
      for (uint32_t i = 0; i < appCfgGattServerUserWriteRequestSize; i++) {
        if ((appCfgGattServerUserWriteRequest[i].charId
             == evt->data.evt_gatt_server_characteristic_status.characteristic)
            && (appCfgGattServerUserWriteRequest[i].fctn)) {
          appCfgGattServerUserWriteRequest[i].fctn(
            evt->data.evt_gatt_server_user_read_request.connection,
            &(evt->data.evt_gatt_server_attribute_value.value));
        }
      }
      break;

    case sl_bt_evt_system_boot_id: {
      bd_addr ble_address;
      uint8_t type;
      sl_status_t status = sl_bt_system_hello();
      sl_zigbee_core_debug_println("BLE hello: %s",
                                   (status == SL_STATUS_OK) ? "success" : "error");

      status = sl_bt_system_get_identity_address(&ble_address, &type);
      zb_ble_dmp_print_ble_address(ble_address.addr);

      status = sl_bt_advertiser_create_set(&adv_handle[HANDLE_ZIGBEE_DIRECT]);
      if (status) {
        sl_zigbee_core_debug_println("sl_bt_advertiser_create_set status 0x%x", status);
      }

      enableBleAdvertisements();
    }
    break;

    case sl_bt_evt_connection_opened_id: {
      sl_bt_evt_connection_opened_t *conn_evt =
        (sl_bt_evt_connection_opened_t*) &(evt->data);
      uint8_t index = bleConnectionInfoTableFindUnused();
      if (index == 0xFF) {
        sl_zigbee_core_debug_println("MAX active BLE connections");
        assert(index < 0xFF);
      } else {
        bleConnectionTable[index].inUse = true;
        bleConnectionTable[index].isMaster = (conn_evt->master > 0);
        bleConnectionTable[index].connectionHandle = conn_evt->connection;
        bleConnectionTable[index].bondingHandle = conn_evt->bonding;
        (void) memcpy(bleConnectionTable[index].remoteAddress,
                      conn_evt->address.addr, 6);

        activeBleConnections++;
        //preferred phy 1: 1M phy, 2: 2M phy, 4: 125k coded phy, 8: 500k coded phy
        //accepted phy 1: 1M phy, 2: 2M phy, 4: coded phy, ff: any
        sl_bt_connection_set_preferred_phy(conn_evt->connection, sl_bt_gap_phy_1m, 0xff);
        sl_bt_connection_set_parameters(
          conn_evt->connection,
          12,            // min. con. interval (milliseconds * 1.25)
          30,            // max. con. interval (milliseconds * 1.25)
          4,             // latency
          250,           // timeout (milliseconds * 10)
          0x0,           // min. connection event length (milliseconds * 0.625)
          0xffff);       // max. connection event length (milliseconds * 0.625)
        enableBleAdvertisements();
        sl_zigbee_core_debug_println("BLE connection opened");
        bleConnectionInfoTablePrintEntry(index);
        sl_zigbee_core_debug_println("%d active BLE connection",
                                     activeBleConnections);
      }
    }
    break;
    case sl_bt_evt_connection_phy_status_id: {
      sl_bt_evt_connection_phy_status_t *conn_evt =
        (sl_bt_evt_connection_phy_status_t *)&(evt->data);
      // indicate the PHY that has been selected
      sl_zigbee_core_debug_println("Now using the %d PHY",
                                   conn_evt->phy);
    }
    break;
    case sl_bt_evt_connection_closed_id: {
      sl_bt_evt_connection_closed_t *conn_evt =
        (sl_bt_evt_connection_closed_t*) &(evt->data);
      uint8_t index = bleConnectionInfoTableLookup(conn_evt->connection);
      assert(index < 0xFF);

      bleConnectionTable[index].inUse = false;
      if ( activeBleConnections ) {
        --activeBleConnections;
      }
      // restart advertising, set connectable
      enableBleAdvertisements();
      if (bleConnectionInfoTableIsEmpty()) {
        sl_dmp_ui_bluetooth_connected(false);
      }
      sl_zigbee_core_debug_println("BLE connection closed, handle=0x%x, reason=0x%2x : [%d] active BLE connection",
                                   conn_evt->connection, conn_evt->reason, activeBleConnections);
    }
    break;

    case sl_bt_evt_connection_parameters_id: {
      sl_bt_evt_connection_parameters_t* param_evt =
        (sl_bt_evt_connection_parameters_t*) &(evt->data);
      sl_zigbee_core_debug_println(
        "BLE connection parameters are updated, handle=0x%02x, interval=0x%04x, latency=0x%04x, timeout=0x%04x, security=0x%02x, txsize=0x%04x",
        param_evt->connection,
        param_evt->interval,
        param_evt->latency,
        param_evt->timeout,
        param_evt->security_mode,
        param_evt->txsize);
      sl_dmp_ui_bluetooth_connected(true);
    }
    break;

    case sl_bt_evt_gatt_service_id: {
      sl_bt_evt_gatt_service_t* service_evt =
        (sl_bt_evt_gatt_service_t*) &(evt->data);
      uint8_t i;
      sl_zigbee_core_debug_println("GATT service, conn_handle=0x%x, service_handle=0x%4x",
                                   service_evt->connection, service_evt->service);
      sl_zigbee_core_debug_print("UUID=[");
      for (i = 0; i < service_evt->uuid.len; i++) {
        sl_zigbee_core_debug_print("0x%x ", service_evt->uuid.data[i]);
      }
      sl_zigbee_core_debug_println("]");
    }
    break;

    default:
      break;
  }
}

static void sli_zigbee_zdd_manage_joiners_write(void)
{
  uint8_t ble_status = ES_WRITE_OK;
  uint8_t myStatus = SL_ZIGBEE_DIRECT_STATUS_CODE_ERROR;
  sl_status_t status;
  EmberNodeType NodeType;
  sl_zigbee_app_debug_print("Received manage joiners command [");
  for (uint8_t i = 0; i < (current_writeValue->len) - 8; i++) {
    sl_zigbee_app_debug_print(" %X", current_writeValue->data[i]);
  }
  sl_zigbee_app_debug_println("]");

  status = emberGetNodeType(&NodeType);

  if ((status == EMBER_SUCCESS) && (EMBER_COORDINATOR == NodeType)) {
    sl_wildcard_tlv_t sl_tlv_pointer4, sl_tlv_pointer5, sl_tlv_pointer6; //max len here
    uint8_t tmp_len = (current_writeValue->len) - 8;
    Buffer my_Buffer;
    my_Buffer = emberFillLinkedBuffers(&current_writeValue->data[0], tmp_len);
    if (my_Buffer == EMBER_NULL_MESSAGE_BUFFER) {
      sl_zigbee_core_debug_println("Error allocating buffer");
      return;
    }

    if (sl_zigbee_tlv_search_buffer_payload_for_id(my_Buffer, 0, SL_ZIGBEE_DIRECT_TLV_MANAGE_JONERS_COMMAND_TAG_ID, (sl_zigbee_tlv_t *) &sl_tlv_pointer4, tmp_len) == EMBER_SUCCESS) {
      sl_zigbee_core_debug_println("Found command ID and executing %X", sl_tlv_pointer4.value[0]);
      switch (sl_tlv_pointer4.value[0]) {
        case 0:  // drop all provisional link keys
          emberClearTransientLinkKeys();
          myStatus = SL_ZIGBEE_DIRECT_STATUS_CODE_SUCCESS;
          break;

        case 1:  // add provisional link key
          if ((sl_zigbee_tlv_search_buffer_payload_for_id(my_Buffer, 0, SL_ZIGBEE_DIRECT_TLV_JOINERS_IEEE_ADDRESS_TAG_ID, (sl_zigbee_tlv_t *) &sl_tlv_pointer5, tmp_len) == EMBER_SUCCESS)
              && (sl_zigbee_tlv_search_buffer_payload_for_id(my_Buffer, 0, SL_ZIGBEE_DIRECT_TLV_PROVISIONAL_LINK_KEY_TAG_ID, (sl_zigbee_tlv_t *) &sl_tlv_pointer6, tmp_len) == EMBER_SUCCESS)) {
            sl_zb_sec_man_key_t myKey;
            EmberEUI64 my_Eui;
            MEMCOPY(&myKey.key, &sl_tlv_pointer6.value[0], EMBER_ENCRYPTION_KEY_SIZE);
            MEMCOPY(my_Eui, &sl_tlv_pointer5.value[0], EUI64_SIZE);
            status =  sl_zb_sec_man_import_transient_key(my_Eui, &myKey);
            if (status == EMBER_SUCCESS) {
              myStatus = SL_ZIGBEE_DIRECT_STATUS_CODE_SUCCESS;
            } else {
              sl_zigbee_core_debug_println("There has been an issue adding transient link key %X", status);
            }
          }
          break;

        case 2:  // remove joiners provisional link key
          if (sl_zigbee_tlv_search_buffer_payload_for_id(my_Buffer, 0, SL_ZIGBEE_DIRECT_TLV_JOINERS_IEEE_ADDRESS_TAG_ID, (sl_zigbee_tlv_t *) &sl_tlv_pointer5, tmp_len) == EMBER_SUCCESS) {
            EmberEUI64 my_Eui;
            MEMCOPY(my_Eui, &sl_tlv_pointer5.value[0], EUI64_SIZE);
            sli_zigbee_remove_transient_link_key(my_Eui, NULL);
            myStatus = SL_ZIGBEE_DIRECT_STATUS_CODE_SUCCESS;
          }
          break;

        default:
          break;
      }
    }
  }

  sl_bt_gatt_server_send_user_write_response(current_connection, gattdb_manage_joiners, ble_status);

  if (ble_status == ES_WRITE_OK) {
    sli_zigbee_direct_send_status_via_commissioning_status_notification(current_connection, SL_ZIGBEE_DIRECT_STATUS_DOMAIN_MJOIN, myStatus);
  }
}

static void sli_zigbee_zdd_join_network_write(void)
{
  uint8_t joining_method = SL_ZIGBEE_DIRECT_JOINING_METHOD_MAC_ASSOCIATION;
  sl_status_t join_network_status;
  uint8_t tmp_len = current_writeValue->len;
  sl_wildcard_tlv_t sl_tlv_pointer1; //max len here
  sl_zigbee_tlv_chain sl_zb_direct_tlv_chain = { &current_writeValue->data[0], (current_writeValue->len) };
  Buffer my_Buffer;
  my_Buffer = emberFillLinkedBuffers(&current_writeValue->data[0], (current_writeValue->len));
  if (my_Buffer == EMBER_NULL_MESSAGE_BUFFER) {
    sl_zigbee_core_debug_println("Error allocating buffer");
    return;
  }

  uint8_t ble_status = ES_WRITE_OK;
  sl_status_t status;
  EmberEUI64 wildcardEui = EMBER_NULL_EUI64;

  sl_zigbee_app_debug_print("Request to join a PAN with payload:");
  for (uint8_t i = 0; i < tmp_len - 8; i++) {
    sl_zigbee_app_debug_print(" %X", current_writeValue->data[i]);
  }
  sl_zigbee_app_debug_println("");

  if (emberNetworkState() != EMBER_NO_NETWORK) {
    goto ERROREXIT;
  }

  if (sl_zigbee_tlv_search_buffer_payload_for_id(my_Buffer, 0, SL_ZIGBEE_DIRECT_TLV_JOINING_METHOD_TAG_ID, (sl_zigbee_tlv_t *) &sl_tlv_pointer1, current_writeValue->len - 1) == EMBER_SUCCESS) {
    joining_method = sl_tlv_pointer1.value[0];
    sl_zigbee_core_debug_println("The joining method is: %X", joining_method);
  } else {
    sl_zigbee_core_debug_println("Joining method TLV is missing");
    goto ERROREXIT;
  }

  sli_zigbee_direct_extract_data_from_tlvs_buf(my_Buffer, tmp_len);
  // this link key is also used for joining (with all attempts)
  status = sl_zb_sec_man_import_transient_key(wildcardEui,
                                              (sl_zb_sec_man_key_t*)&sl_zigbee_direct_security_state.preconfiguredKey);
  sl_zigbee_core_debug_println("Adding Link Key with status: %X", status);

  switch (joining_method) {
    case SL_ZIGBEE_DIRECT_JOINING_METHOD_MAC_ASSOCIATION:
      if (sl_zigbee_tlv_chain_contains_any_tag(&sl_zb_direct_tlv_chain, &zigbee_direct_mac_assoc_excl_tag_list)) {
        goto ERROREXIT;
      }
      if (sl_zigbee_tlv_search_buffer_payload_for_id(my_Buffer, 0, SL_ZIGBEE_DIRECT_TLV_EXTENDED_PAN_ID_TAG_ID, (sl_zigbee_tlv_t *) &sl_tlv_pointer1, current_writeValue->len - 1) == EMBER_SUCCESS) {
        sli_zigbee_af_network_steering_set_extended_pan_id_filter(sl_zigbee_direct_network_params.extendedPanId, true);
      } else {
        sli_zigbee_af_network_steering_set_extended_pan_id_filter(sl_zigbee_direct_network_params.extendedPanId, false);
      }

      sli_zigbee_af_network_steering_set_channel_mask(sl_my_channelMask, false);
      sli_zigbee_af_network_steering_set_channel_mask(0x00000000, true);

      if (emberAfPluginNetworkSteeringStart() != EMBER_SUCCESS) {
        sl_zigbee_core_debug_println("NWK steering start called error");
        goto ERROREXIT;
      }
      break;
    case SL_ZIGBEE_DIRECT_JOINING_METHOD_NWK_REJOIN_WITH_KEY:
      if (sl_zigbee_tlv_chain_contains_any_tag(&sl_zb_direct_tlv_chain, &zigbee_direct_nwk_rejoin_excl_tag_list)) {
        goto ERROREXIT;
      }
      join_network_status = emberFindAndRejoinNetwork(true, sl_my_channelMask);
      if (join_network_status != EMBER_SUCCESS) {
        goto ERROREXIT;
      }
      break;
    case SL_ZIGBEE_DIRECT_JOINING_METHOD_OOB_NO_BEACON_CHECK:
      if (sl_zigbee_tlv_chain_contains_any_tag(&sl_zb_direct_tlv_chain, &zigbee_direct_nwk_oob_excl_tag_list)
          || (!sl_zigbee_tlv_chain_contains_all_tags(&sl_zb_direct_tlv_chain, &zigbee_direct_nwk_oob_incl_tag_list))) {
        goto ERROREXIT;
      }

      if (sl_zigbee_tlv_search_buffer_payload_for_id(my_Buffer, 0, SL_ZIGBEE_DIRECT_TLV_NWK_ADDRESS_TAG_ID, (sl_zigbee_tlv_t *) &sl_tlv_pointer1, current_writeValue->len - 1) == EMBER_SUCCESS) {
        emberSetNodeId(emberFetchLowHighInt16u(&sl_tlv_pointer1.value[0]));
        sl_zigbee_app_debug_println("Found NodeID");
      }

      sl_zigbee_direct_network_params.radioChannel = sli_channel_masks_first_channel(sl_my_channelMask);
      sl_zigbee_direct_network_params.joinMethod = EMBER_USE_CONFIGURED_NWK_STATE;
      sl_zigbee_direct_network_params.nwkManagerId = 0x0000; // use TC node ID
      sl_zigbee_direct_security_state.bitmask = (EMBER_STANDARD_SECURITY_MODE | EMBER_HAVE_NETWORK_KEY | EMBER_HAVE_PRECONFIGURED_KEY | EMBER_HAVE_TRUST_CENTER_EUI64);
      if (sl_zigbee_tlv_search_buffer_payload_for_id(my_Buffer, 0, SL_ZIGBEE_DIRECT_TLV_TRUST_CENTER_ADDRESS_TAG_ID, (sl_zigbee_tlv_t *) &sl_tlv_pointer1, current_writeValue->len  - 1) == EMBER_SUCCESS) {
        sl_zigbee_direct_security_state.bitmask |= EMBER_DISTRIBUTED_TRUST_CENTER_MODE;
        sl_zigbee_app_debug_println("Distributed TC mode detected");
      }
      join_network_status = sli_zigbee_direct_oob_join();
      sl_zigbee_app_debug_println("Joined with status %X", join_network_status);
      if (join_network_status != EMBER_SUCCESS) {
        goto ERROREXIT;
      }
      break;
    default:
      ERROREXIT:
      sli_zigbee_direct_send_status_via_commissioning_status_notification(current_connection, SL_ZIGBEE_DIRECT_STATUS_DOMAIN_JOIN, SL_ZIGBEE_DIRECT_STATUS_CODE_ERROR);
      break;
  }

  sl_bt_gatt_server_send_user_write_response(current_connection, gattdb_join_network, ble_status);
}

void zdd_state_machine()
{
  uint8_t ble_status = ES_WRITE_OK;
  sl_status_t status = 0xFF;
  EmberNetworkStatus state = emberAfNetworkState();
  uint8_t zd_status = SL_ZIGBEE_DIRECT_STATUS_CODE_SUCCESS;
  sl_zigbee_tlv_tag_list sl_tlv_chain1 = { current_writeValue->len, current_writeValue->data };
  uint8_t options = 0;
  bool temp_bool;

  switch (current_state) {
    case LEAVE_WRITE:
      //ignoring current_writeValue->data[0] as we deprecated handling LEAVE_REQUEST_REMOVE_CHILDREN_FLAG
      if (current_writeValue->data[1] != 0) {
        options |= LEAVE_REQUEST_REJOIN_FLAG;
      }
      status = emberZigbeeLeave(options);
      sl_zigbee_app_debug_println("I was requested to leave the PAN with payload: %X %X. Executed with status %X", current_writeValue->data[0], current_writeValue->data[1], status);

      if (status != SL_STATUS_OK) {
        sli_zigbee_direct_send_status_via_commissioning_status_notification(current_connection, SL_ZIGBEE_DIRECT_STATUS_DOMAIN_LEAVE, SL_ZIGBEE_DIRECT_STATUS_CODE_ERROR);
      }
      break;

    case PERMIT_JOIN_WRITE:
      if (emberAfNetworkState() != EMBER_NO_NETWORK) {
        temp_bool = emberGetPermitJoining();
        status = emberAfBroadcastPermitJoin(current_writeValue->data[0]);
        if (status == SL_STATUS_OK) {
          //send status in case we are modifying join time without opening
          if (emberGetPermitJoining() && temp_bool) {
            if (current_writeValue->data[0] != 0x00) {
              send_network_status_notification(0xFF); //send to all connected devices
            }
          } else if (!(temp_bool)) {
            if (current_writeValue->data[0] == 0x00) {
              send_network_status_notification(0xFF); //send to all connected devices
            }
          }
        }
      } else {
        status = 0xFF;   // no network to open
      }
      sl_zigbee_app_debug_println("I was requested to open/close with payload %X. executed with status %X", current_writeValue->data[0], status);

      if (status != SL_STATUS_OK) {
        sli_zigbee_direct_send_status_via_commissioning_status_notification(current_connection, SL_ZIGBEE_DIRECT_STATUS_DOMAIN_PJOIN, SL_ZIGBEE_DIRECT_STATUS_CODE_ERROR);
      }
      break;
    case MANAGE_JOINERS_WRITE:
      sl_zigbee_app_debug_println("MANAGE_JOINERS_WRITE: %X %X", state, zd_status);
      sli_zigbee_zdd_manage_joiners_write();
      current_state = START_STATE;
      break;
    case JOIN_NWK_WRITE:
      sli_zigbee_zdd_join_network_write();
      current_state = START_STATE;
      break;
    case FORM_NWK_WRITE:
      status = sli_zigbee_direct_form_network(&sl_tlv_chain1);
      sl_zigbee_app_debug_println("Network Create status 0x%X", status);
      if (status == SL_ZIGBEE_DIRECT_STATUS_CODE_DECRYPT_FAIL) {
        ble_status = ES_ERR_APPLICATION_SPECIFIC;
      } else if (status != SL_STATUS_OK) {
        sli_zigbee_direct_send_status_via_commissioning_status_notification(current_connection, SL_ZIGBEE_DIRECT_STATUS_DOMAIN_FORM, status);
      }
      sl_bt_gatt_server_send_user_write_response(current_connection, gattdb_form_network, ble_status);
      current_state = START_STATE;
      break;

    case IDENTIFY_WRITE:
      if (sl_zvd_connection_status == PROVISIONED) {
        zd_status = SL_ZIGBEE_DIRECT_STATUS_CODE_ERROR;
        sl_zigbee_app_debug_println("Can't identify as provisioned");
      } else {
        status = emberAfWriteServerAttribute(SL_ZIGBEE_DIRECT_DEVICE_LIGHT_ENDPOINT,
                                             ZCL_IDENTIFY_CLUSTER_ID,
                                             ZCL_IDENTIFY_TIME_ATTRIBUTE_ID,
                                             (uint8_t *)&current_writeValue->data[0],
                                             ZCL_INT16U_ATTRIBUTE_TYPE);
        if (EMBER_ZCL_STATUS_SUCCESS != status) {
          sl_zigbee_app_debug_println("There has been an issue writing the identify server attribute %X", status);
          zd_status = SL_ZIGBEE_DIRECT_STATUS_CODE_ERROR;
        }
      }
      sl_bt_gatt_server_send_user_write_response(current_connection, gattdb_identify, ble_status);
      if (ble_status == ES_WRITE_OK) {
        sli_zigbee_direct_send_status_via_commissioning_status_notification(current_connection, SL_ZIGBEE_DIRECT_STATUS_DOMAIN_IDENTIFY, zd_status);
      }
      current_state = START_STATE;
      break;

    case BINDING_WRITE:
      ble_status = ES_WRITE_OK;
      state = emberAfNetworkState();
      if (state != EMBER_JOINED_NETWORK) {
        zd_status = SL_ZIGBEE_DIRECT_STATUS_CODE_ERROR;
        sl_zigbee_app_debug_println("Not part of a network");
      }

      if (current_writeValue->data[1] & 0x01) { //if we are to be the initiator
        status = emberAfPluginFindAndBindInitiatorStart(current_writeValue->data[0]);
      } else { // if we are to be the target
        status = emberAfPluginFindAndBindTargetStart(current_writeValue->data[0]);
      }

      if (EMBER_ZCL_STATUS_SUCCESS != status) {
        sl_zigbee_app_debug_println("There has been an issue triggering find and bind %X", status);
        zd_status = SL_ZIGBEE_DIRECT_STATUS_CODE_ERROR;
      }
      sl_bt_gatt_server_send_user_write_response(current_connection, gattdb_finding_binding, ble_status);
      if (ble_status == ES_WRITE_OK) {
        sli_zigbee_direct_send_status_via_commissioning_status_notification(current_connection, SL_ZIGBEE_DIRECT_STATUS_DOMAIN_FUB, zd_status);
      }
      current_state = START_STATE;
      break;
#ifdef SL_CATALOG_ZIGBEE_DIRECT_SECURITY_P256_PRESENT
    case P256_WRITE:
      sl_zigbee_direct_handle_authenticate_write(current_connection, current_writeValue, gattdb_authenticate_p256);
      current_state = START_STATE;
      break;
#endif // SL_CATALOG_ZIGBEE_DIRECT_SECURITY_P256_PRESENT
#ifdef SL_CATALOG_ZIGBEE_DIRECT_SECURITY_CURVE25519_PRESENT
    case C25519_WRITE:
      sl_zigbee_direct_handle_authenticate_write(current_connection, current_writeValue, gattdb_authenticate_25519);
      current_state = START_STATE;
      break;
#endif // SL_CATALOG_ZIGBEE_DIRECT_SECURITY_CURVE25519_PRESENT
    default:
      break;
  }

  current_state = START_STATE;
  return;
}

static sl_zigbee_event_t zb_stack_event;
static void zb_stack_event_handler(sl_zigbee_event_t *event)
{
  UNUSED_VAR(event);
  sl_zigbee_event_set_inactive(&zb_stack_event);
  zdd_state_machine();
}

// Initialization of all application code
void sli_zigbee_af_zdd_application_init(uint8_t init_level)
{
  switch (init_level) {
    case SL_ZIGBEE_INIT_LEVEL_EVENT:
    {
      sl_zigbee_event_init(&zb_stack_event, zb_stack_event_handler);
      sl_zigbee_event_set_inactive(&zb_stack_event);
      break;
    }

    case SL_ZIGBEE_INIT_LEVEL_LOCAL_DATA:
    {
      bleConnectionInfoTableInit();
      break;
    }
  }
}

static uint8_t sl_generate_commissioning_status(uint8_t *data)
{
  uint8_t counter = 0;
  uint32_t sl_channel_mask;
  uint16_t sl_pan_id;
  uint16_t sl_node_id;
  EmberNodeType sl_my_nodetype;
  uint8_t sl_extended_pan_id[EXTENDED_PAN_ID_SIZE];
  EmberNetworkStatus sl_my_network_status = emberAfNetworkState();
  EmberCurrentSecurityState securityState;
  EmberStatus status;
  uint16_t temp;

  //first let's add the TLVs which are always included
  //Network Status
  data[counter++] = SL_ZIGBEE_DIRECT_TLV_NETWORK_STATUS_MAP_TAG_ID;
  data[counter++] = SL_ZIGBEE_DIRECT_TLV_NETWORK_STATUS_MAP_MAX_LEN;
  data[counter] = 0x00;
  switch (sl_my_network_status) {
    case EMBER_JOINING_NETWORK:
      data[counter] |= 0x01;
      break;
    case EMBER_JOINED_NETWORK:
      data[counter] |= 0x02;
      break;
    case EMBER_JOINED_NETWORK_NO_PARENT:
      data[counter] |= 0x03;
      break;
    case EMBER_LEAVING_NETWORK:
      data[counter] |= 0x04;
      break;
    default:
      break;
  }
  if (emberGetPermitJoining()) {
    data[counter] |= 0x08;
  }
  status = emberGetCurrentSecurityState(&securityState);
  sl_zigbee_core_debug_println("Reading security state with %X", status);
  if (status == EMBER_SUCCESS) {
    sl_zigbee_core_debug_println("SECURITY STATE IS %2X", securityState.bitmask);
    if ((securityState.bitmask & EMBER_DISTRIBUTED_TRUST_CENTER_MODE) == 0x00) {
      temp = securityState.bitmask & EMBER_DISTRIBUTED_TRUST_CENTER_MODE;
      sl_zigbee_core_debug_println("Setting bit %2X", temp);
      data[counter] |= 0x10;
    }
  }
  counter++;
  //IEEE Address
  data[counter++] = SL_ZIGBEE_DIRECT_TLV_IEEE_ADDRESS_TAG_ID;
  data[counter++] = SL_ZIGBEE_DIRECT_TLV_IEEE_ADDRESS_MAX_LEN;
  MEMCOPY(&data[counter], emberGetEui64(), EUI64_SIZE);
  counter += 8;
  //next add the ones needed if we are part of a network
  if ((sl_my_network_status == EMBER_JOINED_NETWORK) || (sl_my_network_status == EMBER_JOINED_NETWORK_NO_PARENT)) {
    //Channel
    data[counter++] = SL_ZIGBEE_DIRECT_TLV_NETWORK_CHANNEL_MASK_TAG_ID;
    data[counter++] = SL_ZIGBEE_DIRECT_TLV_NETWORK_CHANNEL_MASK_MAX_LEN;
    data[counter++] = 1;
    sl_channel_mask = 1 << emberGetRadioChannel();
    emberStoreLowHighInt32u(&data[counter], sl_channel_mask);
    counter += 4;
    //Extended PAN ID
    data[counter++] = SL_ZIGBEE_DIRECT_TLV_EXTENDED_PAN_ID_TAG_ID;
    data[counter++] = SL_ZIGBEE_DIRECT_TLV_EXTENDED_PAN_ID_MAX_LEN;
    emberGetExtendedPanId(sl_extended_pan_id);
    MEMCOPY(&data[counter], sl_extended_pan_id, EXTENDED_PAN_ID_SIZE);
    counter += 8;
    //Short PAN ID
    data[counter++] = SL_ZIGBEE_DIRECT_TLV_PAN_ID_TAG_ID;
    data[counter++] = SL_ZIGBEE_DIRECT_TLV_PAN_ID_MAX_LEN;
    sl_pan_id = emberGetPanId();
    data[counter++] = (int8u)sl_pan_id;
    data[counter++] = sl_pan_id >> 8;
    //NWK Address
    data[counter++] = SL_ZIGBEE_DIRECT_TLV_NWK_ADDRESS_TAG_ID;
    data[counter++] = SL_ZIGBEE_DIRECT_TLV_NWK_ADDRESS_MAX_LEN;
    sl_node_id = emberGetNodeId();
    data[counter++] = (int8u)sl_node_id;
    data[counter++] = sl_node_id >> 8;
    //Device Type
    data[counter++] = SL_ZIGBEE_DIRECT_TLV_DEVICE_TYPE_TAG_ID;
    data[counter++] = SL_ZIGBEE_DIRECT_TLV_DEVICE_TYPE_MAX_LEN;
    emberGetNodeType(&sl_my_nodetype);
    switch (sl_my_nodetype) {
      case EMBER_COORDINATOR:
        data[counter++] = 0x00;
        break;
      case EMBER_ROUTER:
        data[counter++] = 0x01;
        break;
      case EMBER_END_DEVICE:
      case EMBER_SLEEPY_END_DEVICE:
        data[counter++] = 0x02;
        break;
      default:
        counter -= 2; //something is wrong, so let's remove this TLV
        break;
    }
    //NWK Update ID
    data[counter++] = SL_ZIGBEE_DIRECT_TLV_NETWORK_UPDATE_ID_TAG_ID;
    data[counter++] = SL_ZIGBEE_DIRECT_TLV_NETWORK_UPDATE_ID_MAX_LEN;
    data[counter++] = sli_zigbee_get_nwk_update_id();
    //Active Key Seq Number
    data[counter++] = SL_ZIGBEE_DIRECT_TLV_NETWORK_ACTIVE_KEY_SEQ_NUMBER_TAG_ID;
    data[counter++] = SL_ZIGBEE_DIRECT_TLV_NETWORK_ACTIVE_KEY_SEQ_NUMBER_MAX_LEN;
    sl_zb_sec_man_network_key_info_t nwk_key_info;
    sl_zb_sec_man_get_network_key_info(&nwk_key_info);
    data[counter++] = nwk_key_info.network_key_sequence_number;
    //Trust Center Address
    data[counter++] = SL_ZIGBEE_DIRECT_TLV_TRUST_CENTER_ADDRESS_TAG_ID;
    data[counter++] = SL_ZIGBEE_DIRECT_TLV_TRUST_CENTER_ADDRESS_MAX_LEN;
    if (securityState.bitmask & EMBER_DISTRIBUTED_TRUST_CENTER_MODE) {
      MEMSET(&data[counter], 0xFF, EUI64_SIZE);
    } else {
      MEMCOPY(&data[counter], securityState.trustCenterLongAddress, EUI64_SIZE);
    }
    counter += 8;
  }
  return (counter);
}

static void sli_zigbee_direct_commissioning_status_read(uint8_t connection)
{
  uint8_t response[SL_ZIGBEE_DIRECT_RESPONSE_MAX_LENGTH];
  uint8_t length_of_network_status = sl_generate_commissioning_status(&response[4]);
  uint16_t sent_length;
  sl_status_t status;

  if ((sl_zvd_connection_status != COMMISSIONED_ADMIN) && (sl_zvd_connection_status != OPEN_TO_BE_PROVISIONED) && (sl_zvd_connection_status != PROVISIONED_IN_PROVISIONING_SESSION) && (sl_zvd_connection_status != COMMISSIONED_BASIC)) {
    sl_zigbee_core_debug_println("Error, no rights %X Line %d", sl_zvd_connection_status, __LINE__);
    sl_bt_gatt_server_send_user_read_response(connection,
                                              gattdb_commissioning_status,
                                              ES_ERR_APPLICATION_SPECIFIC,
                                              0,
                                              response,
                                              &sent_length);
    return;
  }

  sl_zigbee_app_debug_println("Preparing Status Read:");
  for (uint8_t i = 0; i < length_of_network_status; i++) {
    sl_zigbee_app_debug_print(" %X", response[4 + i]);
  }
  sl_zigbee_app_debug_println("");

  status = sl_zigbee_direct_security_encrypt_packet(emberGetEui64(), &response[4], length_of_network_status, gattdb_commissioning_status);
  if (status != SL_STATUS_OK) {
    return;
  }
  status = sl_bt_gatt_server_send_user_read_response(connection,
                                                     gattdb_commissioning_status,
                                                     ES_READ_OK,
                                                     length_of_network_status + 8,
                                                     response,
                                                     &sent_length);
  sl_zigbee_app_debug_println("Responded status read with length %2X and status %2X ", sent_length, status);
}

static void sli_zigbee_direct_identify_read(uint8_t connection)
{
  sl_status_t status;
  uint8_t ble_status = ES_WRITE_OK;
  uint8_t response[10];
  uint16_t length_to_send = 10;
  uint16_t sent_length;
  uint8_t dataType;

  if ((sl_zvd_connection_status != COMMISSIONED_ADMIN)  && (sl_zvd_connection_status != PROVISIONED_IN_PROVISIONING_SESSION) && (sl_zvd_connection_status != COMMISSIONED_BASIC)) {
    sl_zigbee_core_debug_println("Error, no rights %X Line %d", sl_zvd_connection_status, __LINE__);
    ble_status = ES_ERR_APPLICATION_SPECIFIC;
    length_to_send = 0;
    goto EXIT;
  }

  status = emberAfReadAttribute(
    0x01, //endpoint
    ZCL_IDENTIFY_CLUSTER_ID,
    ZCL_IDENTIFY_TIME_ATTRIBUTE_ID,
    CLUSTER_MASK_SERVER,
    response,
    2,
    &dataType);

  if (SL_STATUS_OK != status) {
    sl_zigbee_core_debug_println("There has been an issue reading the identify server attribute %X", status);
    ble_status = ES_ERR_APPLICATION_SPECIFIC;
    length_to_send = 0;
    goto EXIT;
  }

  status = sl_zigbee_direct_security_encrypt_packet(emberGetEui64(), response, 2, gattdb_identify);
  if (status != SL_STATUS_OK) {
    ble_status = ES_ERR_APPLICATION_SPECIFIC;
    length_to_send = 0;
  }

  EXIT:
  sl_bt_gatt_server_send_user_read_response(connection,
                                            gattdb_identify,
                                            ble_status,
                                            length_to_send,
                                            response,
                                            &sent_length);
}

static void send_network_status_notification(uint8_t connection)
{
  uint8_t sl_response[SL_ZIGBEE_DIRECT_RESPONSE_MAX_LENGTH];
  uint8_t sl_length_of_network_status = sl_generate_commissioning_status(&sl_response[4]);
  sl_status_t status;

  sl_zigbee_app_debug_print("Preparing to send Notification to gattdb_commissioning_Status");
  for (uint8_t i = 4; i < sl_length_of_network_status + 4; i++) {
    sl_zigbee_app_debug_print(" %X ", sl_response[i]);
  }
  sl_zigbee_app_debug_println("");

  status = sl_zigbee_direct_security_encrypt_packet(emberGetEui64(), &sl_response[4], sl_length_of_network_status, gattdb_commissioning_status);
  if (status != EMBER_SUCCESS) {
    return;
  }

  if (connection == 0xff) {
    status = sl_bt_gatt_server_notify_all(gattdb_commissioning_status,
                                          sl_length_of_network_status + 8,
                                          sl_response);
  } else {
    status = sl_bt_gatt_server_send_notification(connection,
                                                 gattdb_commissioning_status,
                                                 sl_length_of_network_status + 8,
                                                 sl_response);
  }
  sl_zigbee_app_debug_println("Sending Notification to gattdb_commissioning_Status with status %X", status);
}

static void sli_zigbee_direct_send_status_via_commissioning_status_notification(uint8_t connection, uint8_t status_domain, uint8_t status_code)
{
  uint8_t sl_response[SL_ZIGBEE_DIRECT_RESPONSE_MAX_LENGTH];
  uint8_t sl_length_of_network_status = sl_generate_commissioning_status(&sl_response[4]);
  EmberStatus status;

  sl_response[sl_length_of_network_status + 4] = SL_ZIGBEE_DIRECT_TLV_STATUS_CODE_TAG_ID;
  sl_response[sl_length_of_network_status + 5] = SL_ZIGBEE_DIRECT_TLV_STATUS_CODE_KEY_MAX_LEN;
  sl_response[sl_length_of_network_status + 6] = status_domain;
  sl_response[sl_length_of_network_status + 7] = status_code;

  sl_length_of_network_status = sl_length_of_network_status + 4;

  sl_zigbee_app_debug_println("Sending domain %X and status %X  status", status_domain, status_code);

  status = sl_zigbee_direct_security_encrypt_packet(emberGetEui64(), &sl_response[4], sl_length_of_network_status, gattdb_commissioning_status);
  if (status != EMBER_SUCCESS) {
    return;
  }
  sl_bt_gatt_server_send_notification(connection,
                                      gattdb_commissioning_status,
                                      sl_length_of_network_status + 8,
                                      sl_response);
}

static void sli_zigbee_direct_permit_joining_write(uint8_t connection, uint8array *writeValue)
{
  uint8_t ble_status = ES_WRITE_OK;

  if ((sl_zvd_connection_status != COMMISSIONED_ADMIN)  && (sl_zvd_connection_status != PROVISIONED_IN_PROVISIONING_SESSION)) {
    sl_zigbee_core_debug_println("Error, no rights to execute pjoin from ZVD %X", sl_zvd_connection_status);
    ble_status = ES_ERR_APPLICATION_SPECIFIC;
    goto EXIT;
  }

  if (!(sl_zigbee_direct_security_decrypt_packet(sl_zvd_eui, writeValue->data, writeValue->len, gattdb_permit_joining))) {
    ble_status = ES_ERR_APPLICATION_SPECIFIC;
    goto EXIT;
  }

  current_state = PERMIT_JOIN_WRITE;
  current_connection = connection;
  current_writeValue = writeValue;
  sl_zigbee_event_set_active(&zb_stack_event);
  sl_zigbee_common_rtos_wakeup_stack_task();

  EXIT:
  sl_bt_gatt_server_send_user_write_response(connection, gattdb_permit_joining, ble_status);
}

static void sli_zigbee_direct_leave_network_write(uint8_t connection, uint8array *writeValue)
{
  uint8_t ble_status = ES_WRITE_OK;

  if ((sl_zvd_connection_status != COMMISSIONED_ADMIN)  && (sl_zvd_connection_status != PROVISIONED_IN_PROVISIONING_SESSION)) {
    sl_zigbee_core_debug_println("Error, no rights to execute leave from ZVD %X", sl_zvd_connection_status);
    ble_status = ES_ERR_APPLICATION_SPECIFIC;
    goto EXIT;
  }

  if (!(sl_zigbee_direct_security_decrypt_packet(sl_zvd_eui, writeValue->data, writeValue->len, gattdb_leave_network))) {
    ble_status = ES_ERR_APPLICATION_SPECIFIC;
    goto EXIT;
  }

  current_state = LEAVE_WRITE;
  current_connection = connection;
  current_writeValue = writeValue;
  sl_zigbee_event_set_active(&zb_stack_event);
  sl_zigbee_common_rtos_wakeup_stack_task();

  EXIT:
  sl_bt_gatt_server_send_user_write_response(connection, gattdb_leave_network, ble_status);
}

static uint8_t sli_channel_masks_first_channel(uint32_t sl_channel_mask)
{
  for (uint8_t i = 0; i < 32; i++) {
    if (sl_channel_mask & (0x01 << i)) {
      return i;
    }
  }
  return 0xff;
}

static void sli_zigbee_direct_extract_data_from_tlvs_buf(Buffer my_Buffer, uint8_t len)
{
  sl_zigbee_direct_tunneling_tlv_npdu_message_t sl_tlv_pointer1;
  sl_zigbee_app_debug_println("Extracting TLVs with chain of length %X", len);

  if (sl_zigbee_tlv_search_buffer_payload_for_id(my_Buffer, 0, SL_ZIGBEE_DIRECT_TLV_NETWORK_CHANNEL_MASK_TAG_ID, (sl_zigbee_tlv_t *) &sl_tlv_pointer1, len) == EMBER_SUCCESS) {
    sl_my_channelMask = emberFetchLowHighInt32u(&sl_tlv_pointer1.value[1]);
    sl_zigbee_app_debug_println("The channel mask is: %4X", sl_my_channelMask);
  } else {
    sl_my_channelMask = EMBER_ALL_802_15_4_CHANNELS_MASK;
  }

  if (sl_zigbee_tlv_search_buffer_payload_for_id(my_Buffer, 0, SL_ZIGBEE_DIRECT_TLV_DISTRIBUTED_SECURITY_ADMIN_KEY_TAG_ID, (sl_zigbee_tlv_t *) &sl_tlv_pointer1, len) == EMBER_SUCCESS) {
    MEMCOPY(admin_key, &sl_tlv_pointer1.value[0], 16);
    sli_zd_admin_key_provided_when_joining = true;
    sl_zigbee_app_debug_println("Found the admin key");
  } else {
    MEMSET(admin_key, 0x00, 16);
  }

  if (sl_zigbee_tlv_search_buffer_payload_for_id(my_Buffer, 0, SL_ZIGBEE_DIRECT_TLV_TRUST_CENTER_ADDRESS_TAG_ID, (sl_zigbee_tlv_t *) &sl_tlv_pointer1, len) == EMBER_SUCCESS) {
    MEMCOPY(&sl_zigbee_direct_security_state.preconfiguredTrustCenterEui64, &sl_tlv_pointer1.value[0], EUI64_SIZE);
    sl_zigbee_app_debug_println("Found TC EUI");
  } else {
    MEMSET(&sl_zigbee_direct_security_state.preconfiguredTrustCenterEui64, 0x00, 8);
  }

  if (sl_zigbee_tlv_search_buffer_payload_for_id(my_Buffer, 0, SL_ZIGBEE_DIRECT_TLV_LINK_KEY_TAG_ID, (sl_zigbee_tlv_t *) &sl_tlv_pointer1, len) == EMBER_SUCCESS) {
    MEMCOPY(&sl_zigbee_direct_security_state.preconfiguredKey, &sl_tlv_pointer1.value[1], EMBER_ENCRYPTION_KEY_SIZE);
    sl_zigbee_app_debug_println("Found link key");
  } else {
    if (sli_zigbee_af_memory_byte_compare(sl_zigbee_direct_security_state.preconfiguredTrustCenterEui64, EUI64_SIZE, 0xFF)) { //distributed NWK
      EmberKeyData distributedKey = ZIGBEE_3_DISTRIBUTED_SECURITY_LINK_KEY;
      MEMCOPY(&(sl_zigbee_direct_security_state.preconfiguredKey),
              emberKeyContents(&distributedKey),
              EMBER_ENCRYPTION_KEY_SIZE);
    } else { //centralized NWK
      emberAfGenerateRandomKey(&(sl_zigbee_direct_security_state.preconfiguredKey));
    }
  }

  if (sl_zigbee_tlv_search_buffer_payload_for_id(my_Buffer, 0, SL_ZIGBEE_DIRECT_TLV_NETWORK_UPDATE_ID_TAG_ID, (sl_zigbee_tlv_t *) &sl_tlv_pointer1, len) == EMBER_SUCCESS) {
    sl_zigbee_direct_network_params.nwkUpdateId  = sl_tlv_pointer1.value[0];
    sl_zigbee_app_debug_println("Found NWK update ID: %X", sl_zigbee_direct_network_params.nwkUpdateId);
  } else {
    sl_zigbee_direct_network_params.nwkUpdateId = 0;
  }

  if (sl_zigbee_tlv_search_buffer_payload_for_id(my_Buffer, 0, SL_ZIGBEE_DIRECT_TLV_NETWORK_ACTIVE_KEY_SEQ_NUMBER_TAG_ID, (sl_zigbee_tlv_t *) &sl_tlv_pointer1, len) == EMBER_SUCCESS) {
    sl_zigbee_direct_security_state.networkKeySequenceNumber   = sl_tlv_pointer1.value[0];
    sl_zigbee_app_debug_println("Found Key sequence No: %X", sl_zigbee_direct_security_state.networkKeySequenceNumber);
  } else {
    sl_zigbee_direct_security_state.networkKeySequenceNumber = 0;
  }

  if (sl_zigbee_tlv_search_buffer_payload_for_id(my_Buffer, 0, SL_ZIGBEE_DIRECT_TLV_PAN_ID_TAG_ID, (sl_zigbee_tlv_t *) &sl_tlv_pointer1, len) == EMBER_SUCCESS) {
    sl_zigbee_direct_network_params.panId = emberFetchLowHighInt16u(&sl_tlv_pointer1.value[0]);
    sl_zigbee_app_debug_println("Found PAN ID: %2X", sl_zigbee_direct_network_params.panId);
  } else {
    sl_zigbee_direct_network_params.panId = emberGetPseudoRandomNumber();
    sl_zigbee_app_debug_println("Set random PAN ID: %2X", sl_zigbee_direct_network_params.panId);
  }

  if (sl_zigbee_tlv_search_buffer_payload_for_id(my_Buffer, 0, SL_ZIGBEE_DIRECT_TLV_EXTENDED_PAN_ID_TAG_ID, (sl_zigbee_tlv_t *) &sl_tlv_pointer1, len) == EMBER_SUCCESS) {
    MEMCOPY(sl_zigbee_direct_network_params.extendedPanId, &sl_tlv_pointer1.value[0], EXTENDED_PAN_ID_SIZE);
    sl_zigbee_app_debug_println("Found extended PAN ID");
  }

  if (sl_zigbee_tlv_search_buffer_payload_for_id(my_Buffer, 0, SL_ZIGBEE_DIRECT_TLV_NETWORK_KEY_TAG_ID, (sl_zigbee_tlv_t *) &sl_tlv_pointer1, len) == EMBER_SUCCESS) {
    MEMCOPY(&sl_zigbee_direct_security_state.networkKey, &sl_tlv_pointer1.value[0], EMBER_ENCRYPTION_KEY_SIZE);
    sl_zigbee_app_debug_println("Found Network key");
  } else {
    emberAfGenerateRandomKey(&(sl_zigbee_direct_security_state.networkKey));
  }
}

static EmberStatus sli_zigbee_direct_oob_join(void)
{
  sl_status_t status = emberSetInitialSecurityState(&sl_zigbee_direct_security_state);
  if (status != EMBER_SUCCESS) {
    sl_zigbee_core_debug_println("Security Status %X", status);
    return status;
  }
  status = emberSetExtendedSecurityBitmask(EMBER_EXT_NO_FRAME_COUNTER_RESET || EMBER_JOINER_GLOBAL_LINK_KEY);
  if (status != EMBER_SUCCESS) {
    sl_zigbee_core_debug_println("Ext Security Status %X", status);
    return status;
  }
  status = emberJoinNetwork(EMBER_ROUTER, &sl_zigbee_direct_network_params);
  if (status != EMBER_SUCCESS) {
    sl_zigbee_core_debug_println("Join Status %X", status);
    return status;
  }
  return status;
}

static void sli_zigbee_direct_join_network_write(uint8_t connection, uint8array *writeValue)
{
  uint8_t ble_status = ES_WRITE_OK;

  if ((sl_zvd_connection_status != PROVISIONED_IN_PROVISIONING_SESSION) && (sl_zvd_connection_status != COMMISSIONED_ADMIN)) {
    sl_zigbee_core_debug_println("Error, no rights %X Line %d", sl_zvd_connection_status, __LINE__);
    ble_status = ES_ERR_APPLICATION_SPECIFIC;
    goto EXIT;
  }

  if (!(sl_zigbee_direct_security_decrypt_packet(sl_zvd_eui, writeValue->data, writeValue->len, gattdb_join_network))) {
    ble_status = ES_ERR_APPLICATION_SPECIFIC;
    goto EXIT;
  }

  current_state = JOIN_NWK_WRITE;
  current_connection = connection;
  current_writeValue = writeValue;
  ATOMIC(sl_zigbee_event_set_delay_ms(&zb_stack_event, 5); );
  sl_zigbee_common_rtos_wakeup_stack_task();
  return;

  EXIT:
  sl_bt_gatt_server_send_user_write_response(connection, gattdb_join_network, ble_status);
}

void sli_zigbee_zdd_update_keys(EmberInitialSecurityState *state)
{
  // Don't overwrite keys if key contents are all zeros
  uint8_t *key_ptr = sl_zigbee_direct_security_state.networkKey.contents;
  if (!SLI_ZIGBEE_CHECK_KEY_ALL_ZERO(key_ptr)) {
    MEMCOPY(state->networkKey.contents,
            emberKeyContents(&sl_zigbee_direct_security_state.networkKey),
            EMBER_ENCRYPTION_KEY_SIZE);
    sl_zigbee_app_debug_println("Updated Network Key!!!");
  }

  key_ptr = sl_zigbee_direct_security_state.preconfiguredKey.contents;
  if (!SLI_ZIGBEE_CHECK_KEY_ALL_ZERO(key_ptr)) {
    MEMCOPY(state->preconfiguredKey.contents,
            emberKeyContents(&sl_zigbee_direct_security_state.preconfiguredKey),
            EMBER_ENCRYPTION_KEY_SIZE);
    sl_zigbee_app_debug_println("Updated Preconfigured Key!!!");
  }
}

static uint8_t sli_zigbee_direct_form_network(sl_zigbee_tlv_tag_list* tlvs_for_forming1)
{
  EmberStatus status;
  sl_zigbee_direct_tlv_extended_pan_id_t sl_tlv_pointer1;
  bool centralizedSecurity = true;

  tlvs_for_forming1->length  = tlvs_for_forming1->length - 8;

  //check if forming is in progress to satisfy testcase
  if (form_in_process) {
    sl_zigbee_core_debug_println("Form is in progress");
    return SL_ZIGBEE_DIRECT_STATUS_CODE_ERROR;
  }

  sl_zigbee_app_debug_print("Requeste to form a PAN with payload: ");
  for (uint8_t i = 0; i < tlvs_for_forming1->length; i++) {
    sl_zigbee_app_debug_print(" %X", tlvs_for_forming1->tag_ids[i]);
  }
  sl_zigbee_app_debug_println("");

  sl_zigbee_tlv_chain sl_zb_direct_tlv_chain = { &tlvs_for_forming1->tag_ids[0], tlvs_for_forming1->length };
  Buffer my_Buffer;
  my_Buffer = emberFillLinkedBuffers(&tlvs_for_forming1->tag_ids[0], tlvs_for_forming1->length);
  if (my_Buffer == EMBER_NULL_MESSAGE_BUFFER) {
    sl_zigbee_core_debug_println("Error allocating buffer");
    return SL_ZIGBEE_DIRECT_STATUS_CODE_ERROR;
  }

  // return if TLV chain is invalid
  // if (tlv_chain_is_valid_with_local_env(tlvs_for_forming, zigbee_direct_tlv_env, false) != TLV_STATUS_OK) {
  if ((sl_zigbee_tlv_check_general_format_env(my_Buffer, 0, zigbee_direct_tlv_env) != EMBER_SUCCESS)) {
    sl_zigbee_core_debug_println("error checking local env");
    return SL_ZIGBEE_DIRECT_STATUS_CODE_ERROR;
  }

  // return if invalid TLV is included
  if (sl_zigbee_tlv_chain_contains_any_tag(&sl_zb_direct_tlv_chain, &zigbee_direct_nwk_form_excl_tag_list)) {
    sl_zigbee_core_debug_println("Invalid TLV in message");
    return SL_ZIGBEE_DIRECT_STATUS_CODE_ERROR;
  }

  // check for correct parameter to satisfy testcase
  if (sl_zigbee_tlv_search_buffer_payload_for_id(my_Buffer, 0, SL_ZIGBEE_DIRECT_TLV_EXTENDED_PAN_ID_TAG_ID, (sl_zigbee_tlv_t *) &sl_tlv_pointer1, tlvs_for_forming1->length) == EMBER_SUCCESS) {
    if (sli_zigbee_af_memory_byte_compare(&sl_tlv_pointer1.value[0], EXTENDED_PAN_ID_SIZE, 0xFF) || sli_zigbee_af_memory_byte_compare(&sl_tlv_pointer1.value[0], EXTENDED_PAN_ID_SIZE, 0x00)) {
      sl_zigbee_core_debug_println("found invalid extended PAN ID");
      return SL_ZIGBEE_DIRECT_STATUS_CODE_ERROR;
    }
  }

  if (emberAfNetworkState() == EMBER_NO_NETWORK) {
    sli_zigbee_direct_extract_data_from_tlvs_buf(my_Buffer, tlvs_for_forming1->length);
    // check if nwk is to be distributed security
    if (sli_zigbee_af_memory_byte_compare(sl_zigbee_direct_security_state.preconfiguredTrustCenterEui64, EUI64_SIZE, 0xFF)) {
      centralizedSecurity = false;
      if (sl_zigbee_tlv_search_buffer_payload_for_id(my_Buffer, 0, SL_ZIGBEE_DIRECT_TLV_NWK_ADDRESS_TAG_ID, (sl_zigbee_tlv_t *) &sl_tlv_pointer1, tlvs_for_forming1->length) == EMBER_SUCCESS) {
        uint16_t my_node_id;
        my_node_id = emberFetchLowHighInt16u(&sl_tlv_pointer1.value[0]);
        emberSetNodeId(my_node_id);
        sl_zigbee_app_debug_println("found nwk address %2X", my_node_id);
      }
    } else {  //centralized security
              //error out in case we received non-Wildcard TC Address TLV
      if (sl_zigbee_tlv_search_buffer_payload_for_id(my_Buffer, 0, SL_ZIGBEE_DIRECT_TLV_TRUST_CENTER_ADDRESS_TAG_ID, (sl_zigbee_tlv_t *) &sl_tlv_pointer1, tlvs_for_forming1->length) == EMBER_SUCCESS) {
        sl_zigbee_core_debug_println("error received non wildcard TC address");
        return SL_ZIGBEE_DIRECT_STATUS_CODE_ERROR;
      }
    }

    MEMMOVE(sli_zigbee_af_extended_pan_id, sl_zigbee_direct_network_params.extendedPanId, EXTENDED_PAN_ID_SIZE);
    sli_zigbee_af_network_creator_primary_channel_mask = sl_my_channelMask;
    sli_zigbee_af_network_creator_secondary_channel_mask = 0;
    emberSetNwkUpdateId(sl_zigbee_direct_network_params.nwkUpdateId);

    status = emberAfPluginNetworkCreatorStart(centralizedSecurity);
    if (status != EMBER_SUCCESS) {
      return SL_ZIGBEE_DIRECT_STATUS_CODE_ERROR;
    }
    form_in_process = true;
  } else {
    sli_zd_admin_key_provided_when_joining = false;
    return SL_ZIGBEE_DIRECT_STATUS_CODE_ERROR;
  }
  return EMBER_SUCCESS;
}

EmberPanId emberAfPluginNetworkCreatorGetPanIdCallback(void)
{
  return sl_zigbee_direct_network_params.panId;
}

static void sli_zigbee_direct_form_network_write(uint8_t connection, uint8array *writeValue)
{
  uint8_t ble_status = ES_WRITE_OK;

  if ((sl_zvd_connection_status != PROVISIONED_IN_PROVISIONING_SESSION) && (sl_zvd_connection_status != OPEN_TO_BE_PROVISIONED)) {
    sl_zigbee_core_debug_println("Error, no rights %X Line %d", sl_zvd_connection_status, __LINE__);
    ble_status = ES_ERR_APPLICATION_SPECIFIC;
    goto EXIT;
  }

  if (!(sl_zigbee_direct_security_decrypt_packet(sl_zvd_eui, writeValue->data, writeValue->len, gattdb_form_network))) {
    ble_status = ES_ERR_APPLICATION_SPECIFIC;
    goto EXIT;
  }

  current_state = FORM_NWK_WRITE;
  current_connection = connection;
  current_writeValue = writeValue;
  sl_zigbee_common_rtos_wakeup_stack_task();
  ATOMIC(sl_zigbee_event_set_active(&zb_stack_event); );

  return;

  EXIT:
  sl_bt_gatt_server_send_user_write_response(connection, gattdb_form_network, ble_status);
}

static void sli_zigbee_direct_identify_write(uint8_t connection, uint8array *writeValue)
{
  uint8_t ble_status = ES_WRITE_OK;
  uint8_t zd_status = SL_ZIGBEE_DIRECT_STATUS_CODE_SUCCESS;

  if ((sl_zvd_connection_status != COMMISSIONED_ADMIN)  && (sl_zvd_connection_status != PROVISIONED_IN_PROVISIONING_SESSION) && (sl_zvd_connection_status != COMMISSIONED_BASIC)) {
    sl_zigbee_core_debug_println("Error, no rights %X Line %d", sl_zvd_connection_status, __LINE__);
    ble_status = ES_ERR_APPLICATION_SPECIFIC;
    goto EXIT;
  }

  if (!(sl_zigbee_direct_security_decrypt_packet(sl_zvd_eui, writeValue->data, writeValue->len, gattdb_identify))) {
    ble_status = ES_ERR_APPLICATION_SPECIFIC;
    goto EXIT;
  }

  current_state = IDENTIFY_WRITE;
  current_connection = connection;
  current_writeValue = writeValue;
  ATOMIC(sl_zigbee_event_set_delay_ms(&zb_stack_event, 5); );
  sl_zigbee_common_rtos_wakeup_stack_task();
  return;

  EXIT:
  sl_bt_gatt_server_send_user_write_response(connection, gattdb_identify, ble_status);
  if (ble_status == ES_WRITE_OK) {
    sli_zigbee_direct_send_status_via_commissioning_status_notification(connection, SL_ZIGBEE_DIRECT_STATUS_DOMAIN_IDENTIFY, zd_status);
  }
}

void emberAfPluginIdentifyStartFeedbackCallback(uint8_t endpoint,
                                                uint16_t identifyTime)
{
  sl_zigbee_core_debug_println("Identify started for endpoint %X and time %2X", endpoint, identifyTime);
}

void emberAfPluginIdentifyStopFeedbackCallback(uint8_t endpoint)
{
  sl_zigbee_core_debug_println("Identify stopped for endpoint %X", endpoint);
}

static void sli_zigbee_direct_manage_joiners_write(uint8_t connection, uint8array *writeValue)
{
  uint8_t ble_status = ES_WRITE_OK;
  uint8_t myStatus = SL_ZIGBEE_DIRECT_STATUS_CODE_ERROR;

  if (sl_zvd_connection_status != COMMISSIONED_ADMIN) {
    sl_zigbee_core_debug_println("Error, no rights %X Line %d", sl_zvd_connection_status, __LINE__);
    ble_status = ES_ERR_APPLICATION_SPECIFIC;
    goto EXIT;
  }

  if (!(sl_zigbee_direct_security_decrypt_packet(sl_zvd_eui, writeValue->data, writeValue->len, gattdb_manage_joiners))) {
    ble_status = ES_ERR_APPLICATION_SPECIFIC;
    goto EXIT;
  }

  current_state = MANAGE_JOINERS_WRITE;
  current_connection = connection;
  current_writeValue = writeValue;
  ATOMIC(sl_zigbee_event_set_delay_ms(&zb_stack_event, 5); );
  sl_zigbee_common_rtos_wakeup_stack_task();
  return;

  EXIT:
  sl_bt_gatt_server_send_user_write_response(connection, gattdb_manage_joiners, ble_status);

  if (ble_status == ES_WRITE_OK) {
    sli_zigbee_direct_send_status_via_commissioning_status_notification(connection, SL_ZIGBEE_DIRECT_STATUS_DOMAIN_MJOIN, myStatus);
  }
}

static void sli_zigbee_direct_finding_binding_write(uint8_t connection, uint8array *writeValue)
{
  uint8_t ble_status = ES_WRITE_OK;
  uint8_t my_status = SL_ZIGBEE_DIRECT_STATUS_CODE_SUCCESS;

  if ((sl_zvd_connection_status != COMMISSIONED_ADMIN) && (sl_zvd_connection_status != COMMISSIONED_BASIC)) {
    sl_zigbee_core_debug_println("Error, no rights %X Line %d", sl_zvd_connection_status, __LINE__);
    ble_status = ES_ERR_APPLICATION_SPECIFIC;
    goto EXIT;
  }

  if (!(sl_zigbee_direct_security_decrypt_packet(sl_zvd_eui, writeValue->data, writeValue->len, gattdb_finding_binding))) {
    ble_status = ES_ERR_APPLICATION_SPECIFIC;
    goto EXIT;
  }

  current_state = BINDING_WRITE;
  current_connection = connection;
  current_writeValue = writeValue;
  ATOMIC(sl_zigbee_event_set_delay_ms(&zb_stack_event, 5); );
  sl_zigbee_common_rtos_wakeup_stack_task();
  return;

  EXIT:
  sl_bt_gatt_server_send_user_write_response(connection, gattdb_finding_binding, ble_status);
  if (ble_status == ES_WRITE_OK) {
    sli_zigbee_direct_send_status_via_commissioning_status_notification(connection, SL_ZIGBEE_DIRECT_STATUS_DOMAIN_FUB, my_status);
  }
}

#ifdef SL_CATALOG_ZIGBEE_DIRECT_SECURITY_CURVE25519_PRESENT
static void sli_zigbee_direct_authenticate_write_25519(uint8_t connection, uint8array *writeValue)
{
  sl_bt_gatt_server_send_user_write_response(connection, gattdb_authenticate_25519, ES_WRITE_OK);
  current_state = C25519_WRITE;
  current_connection = connection;
  current_writeValue = writeValue;
  ATOMIC(sl_zigbee_event_set_delay_ms(&zb_stack_event, 10); );
  sl_zigbee_common_rtos_wakeup_stack_task();
}
#endif // SL_CATALOG_ZIGBEE_DIRECT_SECURITY_CURVE25519_PRESENT

#ifdef SL_CATALOG_ZIGBEE_DIRECT_SECURITY_P256_PRESENT
static void sli_zigbee_direct_authenticate_write_p256(uint8_t connection, uint8array *writeValue)
{
  sl_bt_gatt_server_send_user_write_response(connection, gattdb_authenticate_p256, ES_WRITE_OK);
  current_state = P256_WRITE;
  current_connection = connection;
  current_writeValue = writeValue;
  ATOMIC(sl_zigbee_event_set_delay_ms(&zb_stack_event, 10); );
  sl_zigbee_common_rtos_wakeup_stack_task();
}
#endif // SL_CATALOG_ZIGBEE_DIRECT_SECURITY_P256_PRESENT

static void sli_zigbee_store_int24u(bool lowHigh, uint8_t* contents, uint32_t value)
{
  uint8_t ii;
  for (ii = 0; ii < 3; ii++) {
    uint8_t index = (lowHigh ? ii : 2 - ii);
    contents[index] = (uint8_t)(value & 0xFF);
    value = (value >> 8);
  }
}

uint32_t emberAfZigbeeDirectClusterServerCommandParse(sl_service_opcode_t opcode,
                                                      sl_service_function_context_t *context)
{
  (void)opcode;

  bool wasHandled = false;
  EmberAfClusterCommand *cmd = (EmberAfClusterCommand *)context->data;

  sl_zigbee_app_debug_println("Received command %X on the ZD cluster!!!", cmd->commandId);

  if (cmd->type != EMBER_INCOMING_UNICAST) {
    sl_zigbee_app_debug_println("Not a unicast, ignoring it");
    emberAfSendDefaultResponse(cmd, EMBER_ZCL_STATUS_NOT_AUTHORIZED);
    return EMBER_ZCL_STATUS_NOT_AUTHORIZED;
  }

  EmberCurrentSecurityState my_security_state;
  emberGetCurrentSecurityState(&my_security_state);
  // in centralized nwk we need APs crypto and unicast from COO
  if (!(my_security_state.bitmask & EMBER_DISTRIBUTED_TRUST_CENTER_MODE)) {
    if (!((cmd->apsFrame->options & EMBER_APS_OPTION_ENCRYPTION) && (cmd->source == 0x00))) {
      sl_zigbee_app_debug_println("Centralized network and not unicast or not from COO, but %2X with %2X", cmd->source, cmd->apsFrame->options);
      emberAfSendDefaultResponse(cmd, EMBER_ZCL_STATUS_NOT_AUTHORIZED);
      return EMBER_ZCL_STATUS_NOT_AUTHORIZED;
    }
  }

  if (!cmd->mfgSpecific) {
    switch (cmd->commandId) {
      case SL_ZIGBEE_DIRECT_CONFIGURE_INTERFACE_COMMAND_ID:
      {
        //verify the correct range of parameter
        wasHandled = true;
        if (cmd->buffer[cmd->payloadStartIndex]) {
          sl_zigbee_core_debug_println("Enabling ZD Interface");
          sl_zigbee_direct_interface_state = 0x01;
          sl_bt_legacy_advertiser_start(adv_handle[HANDLE_ZIGBEE_DIRECT], sl_bt_advertiser_connectable_scannable);
        } else {
          sl_zigbee_core_debug_println("Disabling ZD Interface");
          sl_zigbee_direct_interface_state = 0x00;
          sl_bt_advertiser_stop(adv_handle[HANDLE_ZIGBEE_DIRECT]);
        }
        emberAfWriteServerAttribute(cmd->apsFrame->destinationEndpoint,
                                    0x003D,
                                    0x0000,
                                    &sl_zigbee_direct_interface_state,
                                    ZCL_BITMAP8_ATTRIBUTE_TYPE);
        (void) emberAfPutInt8uInResp(0x19); //frame control
        (void) emberAfPutInt8uInResp(0x00); //sequence
        (void) emberAfPutInt8uInResp(0x00); //command ID
        (void) emberAfPutInt8uInResp(0x00); // status
        (void) emberAfPutInt8uInResp(sl_zigbee_direct_interface_state); // interface state
        emberAfSendResponse();
        break;
      }
      case SL_ZIGBEE_DIRECT_CONFIGURE_TIMEOUT_COMMAND_ID:
      {
        //verify the correct range of parameter
        wasHandled = true;
        sl_zigbee_direct_anonymous_join_timeout_sec = ((uint32_t)cmd->buffer[cmd->payloadStartIndex + 2] << 16) | ((uint16_t)cmd->buffer[cmd->payloadStartIndex + 1] << 8) | (cmd->buffer[cmd->payloadStartIndex]);
        sl_zigbee_core_debug_println("Set Anonymous join timeout to 0x%04X seconds.", sl_zigbee_direct_anonymous_join_timeout_sec);
        if ((sl_zigbee_direct_anonymous_join_timeout_sec > 0) && (sl_zigbee_direct_anonymous_join_timeout_sec < 0x100001)) {
          sl_zigbee_event_set_delay_ms(&sli_zigbee_direct_anonymous_join_event, sl_zigbee_direct_anonymous_join_timeout_sec * 1000);
        }
        emberAfWriteServerAttribute(cmd->apsFrame->destinationEndpoint,
                                    0x003D,
                                    0x0001,
                                    (uint8_t *) &sl_zigbee_direct_anonymous_join_timeout_sec,
                                    ZCL_INT24U_ATTRIBUTE_TYPE);
        halCommonSetToken(TOKEN_PLUGIN_ZDD_JOIN_TIMEOUT, &sl_zigbee_direct_anonymous_join_timeout_sec);
        emberAfSendDefaultResponse(cmd, EMBER_ZCL_STATUS_SUCCESS);
        break;
      }
      default:
      {
        sl_zigbee_core_debug_println("Command ID unknown.");
        break;
      }
    }
  }

  return ((wasHandled)
          ? EMBER_ZCL_STATUS_SUCCESS
          : EMBER_ZCL_STATUS_UNSUP_COMMAND);
}

bool authorized_read = TRUE;

EmberAfStatus emberAfExternalAttributeReadCallback(uint8_t endpoint,
                                                   EmberAfClusterId clusterId,
                                                   EmberAfAttributeMetadata *attributeMetadata,
                                                   uint16_t manufacturerCode,
                                                   uint8_t *buffer,
                                                   uint16_t maxReadLength)
{
  uint32_t temp_timeout;

  sl_zigbee_app_debug_println("External Attribute Read Callback.");
  if (clusterId == 0x003D) {
    sl_zigbee_app_debug_println("Attribute read from ZD cluster detected.");

    if (!(authorized_read)) {
      sl_zigbee_app_debug_println("Returning Not Authorized.");
      return EMBER_ZCL_STATUS_NOT_AUTHORIZED;
    }
    switch (attributeMetadata->attributeId) {
      case 0x000:
        buffer[0] = sl_zigbee_direct_interface_state;
        return EMBER_ZCL_STATUS_SUCCESS;
        break;

      case 0x0001:
        halCommonGetToken(&temp_timeout, TOKEN_PLUGIN_ZDD_JOIN_TIMEOUT);
        sl_zigbee_app_debug_println("WRITING %4X", temp_timeout);
        sli_zigbee_store_int24u(true, buffer, temp_timeout);
        return EMBER_ZCL_STATUS_SUCCESS;
        break;

      default:
        break;
    }
  }
  return EMBER_ZCL_STATUS_FAILURE;
}

EmberAfStatus emberAfExternalAttributeWriteCallback(uint8_t endpoint,
                                                    EmberAfClusterId clusterId,
                                                    EmberAfAttributeMetadata *attributeMetadata,
                                                    uint16_t manufacturerCode,
                                                    uint8_t *buffer)
{
  if (clusterId == 0x003D) {
    sl_zigbee_app_debug_println("Refusing attribute write");
    return EMBER_ZCL_STATUS_READ_ONLY;
  }
  return EMBER_ZCL_STATUS_FAILURE;
}

bool emberAfPreCommandReceivedCallbackZDD(EmberAfClusterCommand* cmd)
{
  EmberCurrentSecurityState my_security_state;

  if (cmd->apsFrame->clusterId == 0x003D) {
    sl_zigbee_app_debug_println("emberAfPreCommandReceivedCallback is for my cluster");
    emberGetCurrentSecurityState(&my_security_state);

    if (!(my_security_state.bitmask & EMBER_DISTRIBUTED_TRUST_CENTER_MODE)) {
      //must be unicast from TC and APS encrypted
      if (!((cmd->apsFrame->options & EMBER_APS_OPTION_ENCRYPTION) && (cmd->source == 0x0000))) {
        emberAfSendDefaultResponse(cmd, EMBER_ZCL_STATUS_NOT_AUTHORIZED);
        sl_zigbee_app_debug_println("Dropping message because no aps encryption and no TC, but %2X %2X", cmd->source, cmd->apsFrame->options);
        authorized_read = false;
        return false;
      }
    }
  }
  authorized_read = true;
  return false;
}

bool emberAfAttributeReadAccessCallback(int8u endpoint,
                                        EmberAfClusterId clusterId,
                                        int16u manufacturerCode,
                                        int16u attributeId)
{
  if (clusterId == 0x003D) {
    sl_zigbee_app_debug_println("emberAfAttributeReadAccessCallback is for my cluster");
  }
  return true;
}

bool emberAfAttributeWriteAccessCallback(int8u endpoint,
                                         EmberAfClusterId clusterId,
                                         int16u manufacturerCode,
                                         int16u attributeId)
{
  if (clusterId == 0x003D) {
    return false;
  }
  return true;
}

bool emberAfClusterSecurityCustomCallback(EmberAfProfileId profileId,
                                          EmberAfClusterId clusterId,
                                          bool incoming,
                                          int8u commandId)
{
  EmberCurrentSecurityState my_security_state;

  if (clusterId == 0x003D) {
    emberGetCurrentSecurityState(&my_security_state);
    if (!(my_security_state.bitmask & EMBER_DISTRIBUTED_TRUST_CENTER_MODE)) {
      return true;
    }
  }
  // By default, assume APS encryption is not required.
  return false;
}

void sli_zigbee_af_plugin_zdd_stack_status_callback(sl_status_t status)
{
  sl_zigbee_app_debug_println("StackStatus: %X", status);

  switch (status) {
    case EMBER_NETWORK_UP:
      if (sli_zd_admin_key_provided_when_joining) {
        sl_zigbee_app_debug_println("Setting COMMISSIONED_ADMIN");
        sl_zvd_connection_status = COMMISSIONED_ADMIN; \
      } else {
        sl_zigbee_app_debug_println("Setting PROVISIONED");
        sl_zvd_connection_status = PROVISIONED_IN_PROVISIONING_SESSION;
      }
      //setDefaultReportEntry();
      //dmpUiDisplayZigBeeState(DMP_UI_NETWORK_UP);
      emberStoreLowHighInt16u(&sli_zigbee_direct_ad_data[12], emberGetPanId());
      emberStoreLowHighInt16u(&sli_zigbee_direct_ad_data[14], emberGetNodeId());
      break;

    case EMBER_NETWORK_DOWN:
      sli_zigbee_direct_ad_data[12] = 0xFF; //set PAN ID
      sli_zigbee_direct_ad_data[13] = 0xFF; //set PAN ID
      sli_zigbee_direct_ad_data[14] = 0xFF; //set Node ID
      sli_zigbee_direct_ad_data[15] = 0xFF; //set Node ID
      sl_zigbee_app_debug_println("Setting OPEN_TO_BE_PROVISIONED");
      sl_zvd_connection_status = OPEN_TO_BE_PROVISIONED;
      MEMSET(&sl_zigbee_direct_security_state, 0, sizeof(sl_zigbee_direct_security_state));
      break;

    case EMBER_NODE_ID_CHANGED:
      emberStoreHighLowInt16u(&sli_zigbee_direct_ad_data[14], emberGetNodeId());
      break;

    case EMBER_PAN_ID_CHANGED:
      emberStoreHighLowInt16u(&sli_zigbee_direct_ad_data[12], emberGetPanId());
      break;

    case EMBER_CHANNEL_CHANGED:
      break;

    case EMBER_NETWORK_OPENED:
      sli_zigbee_direct_ad_data[11] = sli_zigbee_direct_ad_data[11] | 0x20; //set permit join flag in advertisement
      break;

    case EMBER_NETWORK_CLOSED:
      sli_zigbee_direct_ad_data[11] = sli_zigbee_direct_ad_data[11] & 0xDF; //clear permit join flag in advertisement
      break;

    default:
      break;
  }

  halCommonSetToken(TOKEN_PLUGIN_ZDD_AUTH_STATUS, &sl_zvd_connection_status);

  sl_bt_legacy_advertiser_set_data(adv_handle[HANDLE_ZIGBEE_DIRECT],
                                   0,  //advertising packets
                                   sizeof(sli_zigbee_direct_ad_data),
                                   (uint8_t*) &sli_zigbee_direct_ad_data);
  send_network_status_notification(0xFF); //send to all connected devices

  sl_zigbee_app_debug_println("Un-Setting Form in Process");
  form_in_process = false;
  sli_zd_admin_key_provided_when_joining = false;
  return;
}
