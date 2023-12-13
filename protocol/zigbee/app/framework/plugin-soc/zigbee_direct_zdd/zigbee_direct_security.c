/***************************************************************************//**
 * @file zigbee_direct_security.c
 * @brief Zigbee Direct Security
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
#include "hal.h"
#include "ember.h"
#include "af.h"
#include "app/framework/include/af.h"
#include "app/framework/util/af-main.h"
#include "stack/include/security.h"
#include "stack/include/aes-mmo.h"
#include "stack/include/zigbee-security-manager.h"
#include "sl_component_catalog.h"
#include "sl_bluetooth.h"
#include "gatt_db.h"
#ifdef SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
#include "sl_zigbee_debug_print.h"
#endif // SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
#include "stack/include/ember-types.h"
#include "stack/include/sl_zigbee_tlv_core.h"
#include "stack/include/sl_zigbee_stack_specific_tlv.h"
#include "stack/include/sl_zigbee_security_manager_dlk_ecc.h"
#include "zigbee_direct_tlv.h"
#include "zigbee_direct_common.h"
#include "zigbee_direct_session_key_negotiation.h"
#include "mbedtls/sha256.h"
#include "mbedtls/aes.h"
#include "mbedtls/md.h"
#include "sl_bt_rtos_adaptation.h"
#include "sl_custom_token_header.h"

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#ifdef MBEDTLS_CONFIG_FILE
  #include MBEDTLS_CONFIG_FILE
#else
  #include "mbedtls/config.h"
#endif

#include "mbedtls/ccm.h"

#if  !defined(MBEDTLS_CCM_C)
  #error Must enable mbedTLS CCM module
#endif

#if !defined(MBEDTLS_AES_C)
  #error Must enable mbedTLS AES  module
#endif

#define ZIGBEE_DIRECT_NONCE_LENGTH 13
#define ZIGBEE_DIRECT_AUTH_DATA_LENGTH 34
#define ZIGBEE_DIRECT_MIC_LENGTH 4
#define ENCRYPTION_KEYBITS ENCRYPTION_BLOCK_SIZE * 8
#define UUID_SIZE 16

uint32_t sl_zigbee_direct_anonymous_join_timeout_sec;
uint8_t sl_zigbee_direct_interface_state = 0x01;
uint32_t outgoing_counter = 1;
uint32_t incoming_counter = 0;
static mbedtls_ccm_context ccm_zigbee_direct_Ctx;
uint8_t zigbee_direct_session_key[EMBER_ENCRYPTION_KEY_SIZE];
extern sl_zigbee_direct_dlk_public_key_tlv_t ourPointTlv;
uint8_t sl_my_connection;
sl_zigbee_event_t sli_zigbee_direct_anonymous_join_event;
bool sli_zigbee_direct_tc_is_zigbee_direct_aware = false;
uint8_t sli_zigbee_direct_key_negotiation_method;
uint8_t sli_zigbee_direct_preshared_key;

//--------------
// Event handler
void sli_zigbee_direct_anonymous_join_event_handler(sl_zigbee_event_t *event)
{
  sl_zigbee_app_debug_println("sli_zigbee_direct_anonymous_join_event_handler");
  if ((sl_zigbee_direct_anonymous_join_timeout_sec > 0) && (sl_zigbee_direct_anonymous_join_timeout_sec != 0xFFFFFF)) {
    sl_zigbee_direct_anonymous_join_timeout_sec = 0;
    if (sl_zvd_connection_status <= PROVISIONED_IN_PROVISIONING_SESSION) {
      sl_bt_connection_close(sl_my_connection);
    }
  }
}

sl_status_t sl_zigbee_direct_calculate_basic_key(EmberEUI64 zvd_IEEE, uint8_t* basic_key)
{
  sl_zb_sec_man_key_t hash;
  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_key_t network_key;
  uint8_t input[24];
  uint8_t data = 0x03;
  uint8_t i;

  sl_zb_sec_man_init_context(&context);
  context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_NETWORK;
  if ( SL_STATUS_OK != sl_zb_sec_man_export_key(&context, &network_key)) {
    return SL_STATUS_FAIL;
  }

  MEMCOPY(input, zvd_IEEE, EUI64_SIZE);
  MEMCOPY(input + EUI64_SIZE, &network_key, EMBER_ENCRYPTION_KEY_SIZE);

  sl_zigbee_app_debug_print("Calculating Basic Key for Device [");
  for (i = 0; i < EUI64_SIZE; i++) {
    sl_zigbee_app_debug_print(" %X", input[i]);
  }
  sl_zigbee_app_debug_print("] with network key [");
  for (i = 0; i < 16; i++) {
    sl_zigbee_app_debug_print(" %X", input[i + 8]);
  }
  sl_zigbee_app_debug_println("]");

  if (SL_STATUS_OK != emberAesHashSimple(24, input, (uint8_t*)&hash.key)) {
    return SL_STATUS_FAIL;
  }
  //this hash is also a derived type
  context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_INTERNAL;
  sl_zb_sec_man_import_key(&context, &hash);
  sl_zb_sec_man_load_key_context(&context);
  sl_zb_sec_man_hmac_aes_mmo(&data, 1, (uint8_t*) basic_key);

  return SL_STATUS_OK;
}

sl_status_t sl_zigbee_direct_calculate_admin_key(EmberEUI64 zvd_IEEE, uint8_t* admin_key)
{
  sl_zb_sec_man_key_t hash;
  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_key_t network_key;
  uint8_t input[24];
  uint8_t data = 0x04;

  sl_zb_sec_man_init_context(&context);
  context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_NETWORK;
  if ( SL_STATUS_OK != sl_zb_sec_man_export_key(&context, &network_key)) {
    return SL_STATUS_FAIL;
  }

  MEMCOPY(input, zvd_IEEE, EUI64_SIZE);
  MEMCOPY(input + EUI64_SIZE, &network_key, EMBER_ENCRYPTION_KEY_SIZE);

  if (SL_STATUS_OK != emberAesHashSimple(24, input, (uint8_t*) &hash)) {
    return SL_STATUS_FAIL;
  }
  context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_INTERNAL;
  sl_zb_sec_man_import_key(&context, &hash);
  sl_zb_sec_man_load_key_context(&context);
  sl_zb_sec_man_hmac_aes_mmo(&data, 1, (uint8_t*)admin_key);

  return SL_STATUS_OK;
}

void sl_convert_16bit_uuid_to_128bit_uuid(uint16_t input, uint8_t *output)
{
  const uint8_t uuid[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB };

  MEMCOPY(output, uuid, UUID_SIZE);
  emberStoreHighLowInt16u(&output[2], input);
}

static bool sli_zigbee_direct_extract_value_from_previous_uuid(uint16_t handle, uint8_t *uuid, size_t *size, uint8_t *data)
{
  uint16_t handle_pointer = handle - 1;
  sl_status_t status;
  uint16_t c_location;

  while (handle_pointer) {
    status = sl_bt_gatt_server_find_attribute(handle_pointer, 2, uuid, &c_location);
    if ((status == 0) && (c_location < handle)) {
      status = sl_bt_gatt_server_read_attribute_value(handle_pointer, 0, 19, size, data);
      if (status == 0) {
        return true;
      }
    }
    handle_pointer--;
  }
  return false;
}

static void sli_zigbee_direct_extract_uuids_from_handle(uint16_t handle, uint8_t *service_uuid, uint8_t *characteristic_uuid)
{
  uint8_t search_type_characteristic[2] = { 0x03, 0x28 };
  uint8_t search_type_service[2] = { 0x00, 0x28 };
  uint8_t retval[19];
  size_t ret_size;

  if (sli_zigbee_direct_extract_value_from_previous_uuid(handle, search_type_characteristic, &ret_size, retval)) {
    if (ret_size == 2) {
      sl_convert_16bit_uuid_to_128bit_uuid(emberFetchLowHighInt16u(retval), &retval[3]);
      MEMCOPY(characteristic_uuid, &retval[3], UUID_SIZE);
      ret_size = 19;
    } else {
      emberReverseMemCopy(characteristic_uuid, &retval[3], UUID_SIZE);
    }
  } else {
    return;
  }

  if (sli_zigbee_direct_extract_value_from_previous_uuid(handle, search_type_service, &ret_size, retval)) {
    if (ret_size == 2) {
      sl_convert_16bit_uuid_to_128bit_uuid(emberFetchLowHighInt16u(retval), retval);
      ret_size = 16;
      MEMCOPY(service_uuid, retval, UUID_SIZE);
    } else {
      emberReverseMemCopy(service_uuid, retval, UUID_SIZE);
    }
  }
}

sl_status_t sli_zigbee_direct_security_init()
{
  sl_status_t status;

  sl_zigbee_app_debug_print("Crypto Key:");
  for (uint8_t i = 0; i < 16; i++) {
    sl_zigbee_app_debug_print(" %X", zigbee_direct_session_key[i]);
  }
  sl_zigbee_app_debug_println("");

  status = mbedtls_ccm_setkey(&ccm_zigbee_direct_Ctx, MBEDTLS_CIPHER_ID_AES, zigbee_direct_session_key, ENCRYPTION_KEYBITS);

  outgoing_counter = 1;
  incoming_counter = 0;

  return status;
}

sl_status_t sl_zigbee_direct_security_encrypt_packet(EmberEUI64 sourceEui, uint8_t *encryptData, uint16_t dataLen, uint16_t handle)
{
  sl_status_t status;
  uint8_t nonce[ZIGBEE_DIRECT_NONCE_LENGTH];
  uint8_t authData[ZIGBEE_DIRECT_AUTH_DATA_LENGTH];
  uint8_t service_uuid[16];
  uint8_t characteristic_uuid[16];

  sli_zigbee_direct_extract_uuids_from_handle(handle, service_uuid, characteristic_uuid);

  //MIC result is attached to packet (4 bytes)
  //4 byte counter is added at beginning
  // assemble NONCE
  MEMCOPY(nonce, sourceEui, EUI64_SIZE);
  emberStoreLowHighInt32u(&nonce[8], outgoing_counter);
  nonce[12] = 0x05; // security level should be 5 -> Encryption with 32-bit MIC

  // assemble authentication data
  MEMCOPY(authData, service_uuid, UUID_SIZE); // 1. Service UUID (bytes 0-15)
  authData[16] = 0x00; // Service Instance (SHALL be 0)
  MEMCOPY(&authData[17], characteristic_uuid, UUID_SIZE);  // 3. Characteristic UUID (byte 17-32)
  authData[33] = 0x00; // Characteristic Instance (SHALL be 0)

  status = mbedtls_ccm_encrypt_and_tag(&ccm_zigbee_direct_Ctx,
                                       dataLen,
                                       nonce,
                                       ZIGBEE_DIRECT_NONCE_LENGTH,
                                       authData,
                                       ZIGBEE_DIRECT_AUTH_DATA_LENGTH,
                                       encryptData,
                                       encryptData,
                                       encryptData + dataLen,
                                       ZIGBEE_DIRECT_MIC_LENGTH);
  if (status != SL_STATUS_OK) {
    return SL_STATUS_FAIL;
  }
  emberStoreLowHighInt32u(&encryptData[-4], outgoing_counter++);

  return SL_STATUS_OK;
}

bool sl_zigbee_direct_security_decrypt_packet(EmberEUI64 sourceEui, uint8_t *decryptData, uint16_t dataLen, uint16_t handle)
{
  uint8_t status;
  uint8_t nonce[ZIGBEE_DIRECT_NONCE_LENGTH];
  uint8_t authData[ZIGBEE_DIRECT_AUTH_DATA_LENGTH];
  uint8_t service_uuid[16];
  uint8_t characteristic_uuid[16];
  uint32_t counter_from_packet;

  sli_zigbee_direct_extract_uuids_from_handle(handle, service_uuid, characteristic_uuid);

  //check counter
  counter_from_packet = emberFetchLowHighInt32u(decryptData);
  if (incoming_counter >= counter_from_packet) {
    sl_zigbee_app_debug_print("Received Frame counter too small %4X", counter_from_packet);
    return false;
  } else {
    sl_zigbee_app_debug_print("Frame counter check ok %4X", counter_from_packet);
    incoming_counter = counter_from_packet;
  }

  // assemble NONCE
  MEMCOPY(nonce, sourceEui, EUI64_SIZE);
  emberStoreLowHighInt32u(&nonce[8], counter_from_packet);
  nonce[12] = 0x05; // security level should be 5 -> Encryption with 32-bit MIC

  // assemble authentication data
  MEMCOPY(authData, service_uuid, UUID_SIZE); // 1. Service UUID (bytes 0-15)
  authData[16] = 0x00; // Service Instance (SHALL be 0)
  MEMCOPY(&authData[17], characteristic_uuid, UUID_SIZE);  // 3. Characteristic UUID (byte 17-32)
  authData[33] = 0x00; // Characteristic Instance (SHALL be 0)

  status = mbedtls_ccm_auth_decrypt(&ccm_zigbee_direct_Ctx,
                                    dataLen - 8,
                                    nonce,
                                    ZIGBEE_DIRECT_NONCE_LENGTH,
                                    authData,
                                    ZIGBEE_DIRECT_AUTH_DATA_LENGTH,
                                    &decryptData[4],
                                    decryptData,
                                    &decryptData[dataLen - 4],
                                    ZIGBEE_DIRECT_MIC_LENGTH);
  if (status != SL_STATUS_OK) {
    sl_zigbee_core_debug_println("Error from mbed TLS: %4X", status);
    return false;
  }

  return true;
}

static int sli_zigbee_direct_calculate_mac_tag_value(bool useKC_2_U, uint8_t *output, uint8_t method)
{
  int ret;
  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_key_t plaintext_key;
  sl_zb_sec_man_aps_key_metadata_t metadata;

  if (method != DLK_ECC_P256_SHA_256) {
    uint8_t input[86];
    ret = sl_zb_sec_man_export_transient_key_by_eui(sl_zvd_eui,
                                                    &context,
                                                    &plaintext_key,
                                                    &metadata);
    if (ret == 0) {
      sl_zigbee_core_debug_print("Session key: ");
      emberAfPrintZigbeeKey((const uint8_t*)&(plaintext_key.key));
      sl_zigbee_core_debug_println("");
      MEMCOPY(zigbee_direct_session_key, &plaintext_key, 16);

      if (useKC_2_U) {
        input[0] = 'K';
        input[1] = 'C';
        input[2] = '_';
        input[3] = '2';
        input[4] = '_';
        input[5] = 'U';
      } else {
        input[0] = 'K';
        input[1] = 'C';
        input[2] = '_';
        input[3] = '2';
        input[4] = '_';
        input[5] = 'V';
      }

      MEMCOPY(&input[6], emberGetEui64(), 8);
      MEMCOPY(&input[14], &ourPointTlv.value[8], 32);
      MEMCOPY(&input[46], sl_zvd_eui, 8);
      MEMCOPY(&input[54], sl_zvd_public_point_x, DLK_ECC_COORDINATE_SIZE);

      sl_zb_sec_man_load_key_context(&context);
      sl_zb_sec_man_hmac_aes_mmo(input, 86, output);
      return EMBER_SUCCESS;
    }
  } else {
    const mbedtls_md_info_t *md_info = mbedtls_md_info_from_type(MBEDTLS_MD_SHA256);
    mbedtls_md_context_t ctx;

    mbedtls_md_init(&ctx);

    ret = mbedtls_md_setup(&ctx, md_info, 1);

    if (ret == 0) {
      ret = sl_zb_sec_man_export_transient_key_by_eui(sl_zvd_eui,
                                                      &context,
                                                      &plaintext_key,
                                                      &metadata);
    }
    if (ret == 0) {
      sl_zigbee_core_debug_print("Session key: ");
      emberAfPrintZigbeeKey((const uint8_t*)&(plaintext_key.key));
      sl_zigbee_core_debug_println("");
      MEMCOPY(zigbee_direct_session_key, &plaintext_key, 16);
      ret = mbedtls_md_hmac_starts(&ctx, (const unsigned char *)&plaintext_key, 16);
    }
    if (ret == 0) {
      if (useKC_2_U) {
        ret = mbedtls_md_hmac_update(&ctx, (const unsigned char *)"KC_2_U", 6);
      } else {
        ret = mbedtls_md_hmac_update(&ctx, (const unsigned char *)"KC_2_V", 6);
      }
    }
    if (ret == 0) {
      ret = mbedtls_md_hmac_update(&ctx, emberGetEui64(), 8);
      sl_zigbee_core_debug_print("ZDD EUI: ");
      emberAfPrintLittleEndianEui64(emberGetEui64());
      sl_zigbee_core_debug_println("");
    }
    if (ret == 0) {
      ret = mbedtls_md_hmac_update(&ctx, &ourPointTlv.value[8], 32);
      sl_zigbee_core_debug_print("ZDD Point X: ");
      for (uint8_t i = 0; i < 32; i++) {
        sl_zigbee_core_debug_print(" %X", ourPointTlv.value[8 + i]);
      }
      sl_zigbee_core_debug_println("");
    }

    if (ret == 0) {
      ret = mbedtls_md_hmac_update(&ctx, &ourPointTlv.value[40], 32);
      sl_zigbee_core_debug_print("ZDD Point Y: ");
      for (uint8_t i = 0; i < 32; i++) {
        sl_zigbee_core_debug_print(" %X", ourPointTlv.value[40 + i]);
      }
      sl_zigbee_core_debug_println("");
    }
    if (ret == 0) {
      ret = mbedtls_md_hmac_update(&ctx, sl_zvd_eui, 8);
      sl_zigbee_core_debug_print("ZVD EUI: ");
      emberAfPrintLittleEndianEui64(sl_zvd_eui);
      sl_zigbee_core_debug_println("");
    }
    if (ret == 0) {
      ret = mbedtls_md_hmac_update(&ctx, sl_zvd_public_point_x, DLK_ECC_COORDINATE_SIZE);
      sl_zigbee_core_debug_print("ZVD Point X: ");
      for (uint8_t i = 0; i < 32; i++) {
        sl_zigbee_core_debug_print(" %X", sl_zvd_public_point_x[i]);
      }
      sl_zigbee_core_debug_println("");
    }
    if (ret == 0) {
      ret = mbedtls_md_hmac_update(&ctx, sl_zvd_public_point_y, DLK_ECC_COORDINATE_SIZE);
      sl_zigbee_core_debug_print("ZVD Point Y: ");
      for (uint8_t i = 0; i < 32; i++) {
        sl_zigbee_core_debug_print(" %X", sl_zvd_public_point_y[i]);
      }
      sl_zigbee_core_debug_println("");
    }
    if (ret == 0) {
      ret = mbedtls_md_hmac_finish(&ctx, output);
    }
    mbedtls_md_free(&ctx);
  }
  return ret;
}

static void sli_zigbee_direct_send_mac_tag(uint8_t connection, uint16_t characteristic)
{
  EmberStatus status;
  uint8_t sl_response[35];
  uint8_t hash_output[32];
  uint8_t point_offset = 0;

#ifdef SL_CATALOG_ZIGBEE_DIRECT_SECURITY_P256_PRESENT
  if (characteristic == gattdb_authenticate_p256) {
    point_offset = 16;
  }
#endif // SL_CATALOG_ZIGBEE_DIRECT_SECURITY_P256_PRESENT

#ifdef SL_CATALOG_ZIGBEE_DIRECT_SECURITY_CURVE25519_PRESENT
  if (characteristic == gattdb_authenticate_25519) {
    point_offset = 0;
  }
#endif // SL_CATALOG_ZIGBEE_DIRECT_SECURITY_CURVE25519_PRESENT

  sl_response[0] = SESSION_ESTABLISHMENT_MSG_4;
  sl_response[1] = SL_ZIGBEE_DIRECT_SECURITY_TLV_MAC_TAG_TAG_ID;
  sl_response[2] = 15 + point_offset;
  sl_zigbee_app_debug_println("Calculating the MacTagValue");

  status = sli_zigbee_direct_calculate_mac_tag_value(false, hash_output, sli_zigbee_direct_key_negotiation_method);
  if (status != EMBER_SUCCESS) {
    sl_zigbee_core_debug_println("Error calculating the MacTagValue");
    return;
  }

  MEMCOPY(&sl_response[3], hash_output, 16 + point_offset);

  status = sl_bt_gatt_server_send_indication(connection,
                                             characteristic,
                                             19 + point_offset,
                                             sl_response);

  if (status != EMBER_SUCCESS) {
    sl_zigbee_core_debug_println("Error sending message 4");
  } else {
    sl_zigbee_app_debug_print("Message 4 sent successfully [");
    for (uint8_t i = 0; i < 19 + point_offset; i++) {
      sl_zigbee_app_debug_print(" %X", sl_response[i]);
    }
    sl_zigbee_app_debug_println("]");
  }
  sli_zigbee_direct_security_init();
}

void sl_zigbee_direct_handle_authenticate_write(uint8_t connection, uint8array *writeValue, uint16_t characteristic)
{
  EmberStatus status;
  sl_wildcard_tlv_t sl_tlv_pointer1;// max possible value

  uint8_t i;

  sl_zigbee_app_debug_print("Received SE message: %X [", writeValue->data[0]);
  for (i = 1; (i < writeValue->len); i++) {
    sl_zigbee_app_debug_print(" %X", writeValue->data[i]);
  }
  sl_zigbee_app_debug_println("]");
  Buffer my_Buffer;
  my_Buffer = emberFillLinkedBuffers(&writeValue->data[1], (writeValue->len - 1));
  if (my_Buffer == EMBER_NULL_MESSAGE_BUFFER) {
    sl_zigbee_core_debug_println("Error allocating buffer");
    return;
  }
  //as a ZDD only receiving opcodes 1 and 3 makes sense
  switch (writeValue->data[0]) {
    case 1:
      // handle Key Negotiation Req Selected Key Negotiation Method TLV
      if (sl_zigbee_tlv_search_buffer_payload_for_id(my_Buffer, 0, SL_ZIGBEE_DIRECT_SECURITY_TLV_SELECTED_KEY_NEGOTIATION_METHOD_TAG_ID, (sl_zigbee_tlv_t *) &sl_tlv_pointer1, 78 /*writeValue->len - 1*/) == EMBER_SUCCESS) {
        sl_zigbee_app_debug_println("Use Key Negotiation method %X and pre-shared secret %X", sl_tlv_pointer1.value[0], sl_tlv_pointer1.value[1]);
        sli_zigbee_direct_key_negotiation_method = sl_tlv_pointer1.value[0];
        sli_zigbee_direct_preshared_key = sl_tlv_pointer1.value[1];
      } else {
        sl_zigbee_app_debug_println("Received invalid SE message: Key Neg TLV not present in SE1");
        break;
      }

      if ( sl_zigbee_tlv_search_buffer_payload_for_id(my_Buffer, 0, SL_ZIGBEE_DIRECT_SECURITY_TLV_P256_PUBLIC_POINT_TAG_ID, (sl_zigbee_tlv_t *) &sl_tlv_pointer1, 78 /*writeValue->len - 1*/) == EMBER_SUCCESS) {
        sl_zigbee_app_debug_print("Negotiate a key with %X%X%X%X%X%X%X%X using the P-256 public point [", sl_tlv_pointer1.value[0], sl_tlv_pointer1.value[1], sl_tlv_pointer1.value[2], sl_tlv_pointer1.value[3], sl_tlv_pointer1.value[4], sl_tlv_pointer1.value[5], sl_tlv_pointer1.value[6], sl_tlv_pointer1.value[7]);
        for (i = 0; i < 64; i++) {
          sl_zigbee_app_debug_print(" %X", sl_tlv_pointer1.value[i + 8]);
        }
        sl_zigbee_app_debug_println("]");
        MEMCOPY(sl_zvd_eui, &sl_tlv_pointer1.value[0], EUI64_SIZE);
        MEMCOPY(sl_zvd_public_point_x, &sl_tlv_pointer1.value[8], DLK_ECC_COORDINATE_SIZE);
        MEMCOPY(sl_zvd_public_point_y, &sl_tlv_pointer1.value[40], DLK_ECC_COORDINATE_SIZE);
      } else if ( sl_zigbee_tlv_search_buffer_payload_for_id(my_Buffer, 0, SL_ZIGBEE_DIRECT_SECURITY_TLV_C25519_PUBLIC_POINT_TAG_ID, (sl_zigbee_tlv_t *) &sl_tlv_pointer1, writeValue->len - 1) == EMBER_SUCCESS) {
        sl_zigbee_app_debug_print("Negotiate a key with %X%X%X%X%X%X%X%X using the C25519 public point [", sl_tlv_pointer1.value[0], sl_tlv_pointer1.value[1], sl_tlv_pointer1.value[2], sl_tlv_pointer1.value[3], sl_tlv_pointer1.value[4], sl_tlv_pointer1.value[5], sl_tlv_pointer1.value[6], sl_tlv_pointer1.value[7]);
        for (i = 0; i < 32; i++) {
          sl_zigbee_app_debug_print(" %X", sl_tlv_pointer1.value[i + 8]);
        }
        sl_zigbee_app_debug_println("]");
        MEMCOPY(sl_zvd_eui, &sl_tlv_pointer1.value[0], EUI64_SIZE);
        MEMCOPY(sl_zvd_public_point_x, &sl_tlv_pointer1.value[8], DLK_ECC_COORDINATE_SIZE);
      } else {
        sl_zigbee_app_debug_println("Received invalid SE message: Selected Public Point TLV not present in SE1");
        break;
      }

      sl_my_connection = connection;

      status = sli_zigbee_handle_incoming_dlk_negotiation_request(my_Buffer, (uint16_t)0, sl_zvd_node_id, characteristic);
      if (status != EMBER_SUCCESS) {
        sl_zigbee_app_debug_println("Error handling incoming negotiation Request");
      } else {
        sl_zigbee_app_debug_println("Success handling incoming negotiation Request");
      }
      break;

    case 3:
      if ( sl_zigbee_tlv_search_buffer_payload_for_id(my_Buffer, 0, SL_ZIGBEE_DIRECT_SECURITY_TLV_MAC_TAG_TAG_ID, (sl_zigbee_tlv_t *) &sl_tlv_pointer1, writeValue->len - 1) == EMBER_SUCCESS) {
        sl_zigbee_app_debug_print("Received the MacTag [");
        for (i = 0; i < (writeValue->len - 1); i++) {
          sl_zigbee_app_debug_print(" %X", sl_tlv_pointer1.value[i]);
        }
        sl_zigbee_app_debug_println("]");
      } else {
        sl_zigbee_app_debug_println("Received invalid SE message: MacTag TLV not present in SE2");
        break;
      }

      uint8_t MacTag_check[32];
      status = sli_zigbee_direct_calculate_mac_tag_value(true, MacTag_check, sli_zigbee_direct_key_negotiation_method);
      if (status != EMBER_SUCCESS) {
        sl_zigbee_app_debug_println("Error calculating the MacTagValue");
        return;
      }

      uint8_t compare_length;
      if (sli_zigbee_direct_key_negotiation_method == DLK_ECC_P256_SHA_256) {
        compare_length = 32;
      } else {
        compare_length = 16;
      }

      sl_zigbee_app_debug_print("The MacTag should be afaik [");
      for (i = 0; i < compare_length; i++) {
        sl_zigbee_app_debug_print(" %X", MacTag_check[i]);
      }
      sl_zigbee_app_debug_println("]");

      if (MEMCOMPARE(MacTag_check, &sl_tlv_pointer1.value[0], compare_length) == 0) {
        sl_zigbee_app_debug_println("MAC TAG is matching!");
        sl_zvd_connection_status = sl_zvd_connection_status_next;
        halCommonSetToken(TOKEN_PLUGIN_ZDD_AUTH_STATUS, &sl_zvd_connection_status);
      } else {
        sl_zigbee_app_debug_println("MAC TAG is NOT matching");
        return;
      }

      sli_zigbee_direct_send_mac_tag(connection, characteristic);
      break;

    default:
      sl_zigbee_app_debug_println("Received invalid SE message: Wrong Opcode");
      break;
  }
}
