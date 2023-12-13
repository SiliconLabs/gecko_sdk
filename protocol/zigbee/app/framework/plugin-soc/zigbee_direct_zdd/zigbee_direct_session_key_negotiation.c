/***************************************************************************//**
 * @file zigbee_direct_session_key_negotiation.c
 * @brief Implementation of Session Key Negotiation with SPEKE/ECDHE
 *        message sending/handling of key-negotiation messages carrying
 *        public variables for establishing a TC Link Key
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "app/framework/include/af.h"
#include "app/framework/util/af-main.h"
#include "app/framework/util/util.h"

#include "zigbee_direct_common.h"
#include "zigbee_direct_tlv.h"
#include "sl_component_catalog.h"
#include "sl_bluetooth.h"
#include "gatt_db.h"
#ifdef SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
#include "sl_zigbee_debug_print.h"
#endif // SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
#include "stack/include/ember-types.h"
#include "stack/include/sl_zigbee_tlv_core.h"
#include "stack/include/sl_zigbee_stack_specific_tlv.h"
#include "stack/include/sl_zigbee_dlk_negotiation.h"
#include "stack/include/zigbee-security-manager.h"
#include "stack/include/sl_zigbee_security_manager_dlk_ecc.h"
#include "stack/include/zigbee-device-stack.h"
#include "zigbee_direct_session_key_negotiation.h"
#include "zigbee_direct_zdd_config.h"
#include "app/util/zigbee-framework/zigbee-device-common.h"
#include "sl_custom_token_header.h"
#include "token-manufacturing.h"
#include "app/framework/security/af-security.h"
#include "mbedtls/sha256.h"

#ifndef SL_ZIGBEE_DIRECT_ZDD_DEFAULT_PASSCODE
// The default passcode to use for session key negotiation.
// Passcode with all zeros would be rejected so customers
// need to specify their own passcode in the app SLCP file.
#define SL_ZIGBEE_DIRECT_ZDD_DEFAULT_PASSCODE { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
#endif // SL_ZIGBEE_DIRECT_ZDD_DEFAULT_PASSCODE

uint8_t sl_my_passcode[EMBER_ENCRYPTION_KEY_SIZE] = SL_ZIGBEE_DIRECT_ZDD_DEFAULT_PASSCODE;
sl_zigbee_direct_dlk_public_key_tlv_t ourPointTlv;
sl_zigbee_direct_dlk_public_key_tlv_t peerPointTlv;
const uint8_t emDlkAnonymousKeyContents[EMBER_ENCRYPTION_KEY_SIZE] = "ZigBeeAlliance18";

static sli_zb_sec_man_dlk_ecc_context_t ecdhCtx;
static uint8_t our_public_point[DLK_ECC_P256_PUBLIC_KEY_SIZE];

extern uint8_t sl_my_connection;
extern sl_zigbee_direct_connection_status_t sl_zvd_connection_status;
extern sl_zigbee_direct_connection_status_t sl_zvd_connection_status_next;

extern sl_status_t sli_zb_sec_man_speke_expand_shared_secret(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx, uint8_t *our_eui, uint8_t *their_eui);

// Convert EUI64 to UINT64 in little endianness order for EUI64 comparison
#define EUI64_TO_UINT64_LE(eui64) (((uint64_t)(((uint8_t *)(eui64))[0]) <<  0)   \
                                   + ((uint64_t)(((uint8_t *)(eui64))[1]) <<  8) \
                                   + ((uint64_t)(((uint8_t *)(eui64))[2]) << 16) \
                                   + ((uint64_t)(((uint8_t *)(eui64))[3]) << 24) \
                                   + ((uint64_t)(((uint8_t *)(eui64))[4]) << 32) \
                                   + ((uint64_t)(((uint8_t *)(eui64))[5]) << 40) \
                                   + ((uint64_t)(((uint8_t *)(eui64))[6]) << 48) \
                                   + ((uint64_t)(((uint8_t *)(eui64))[7]) << 56))

// ----------------------------------------------------------------------------
// Supported Key Negotiation Bitmask
#define SLI_ZIGBEE_DIRECT_SESSION_KEY_REQUEST 1
#define SLI_ZIGBEE_DIRECT_SESSION_KEY_RESPONSE 0

// ----------------------------------------------------------------------------
//  TLV processing

// define the local tlv processing validation environment
static sl_zigbee_tlv_tag_min_length_t dlkReqLocalTlvEnv[] =
{ { .tag_id = SL_ZIGBEE_DIRECT_DLK_TLV_SELECTED_NEGOTIATION_METHOD_TAG_ID,
    .min_length = SL_ZIGBEE_DIRECT_DLK_TLV_SELECTED_NEGOTIATION_METHOD_MIN_LEN },
  { .tag_id = SL_ZIGBEE_DIRECT_SECURITY_TLV_P256_PUBLIC_POINT_TAG_ID,
    .min_length = SL_ZIGBEE_DIRECT_SECURITY_TLV_P256_PUBLIC_POINT_MIN_LEN },
  { .tag_id = SL_ZIGBEE_DIRECT_SECURITY_TLV_C25519_PUBLIC_POINT_TAG_ID,
    .min_length =  SL_ZIGBEE_DIRECT_SECURITY_TLV_C25519_PUBLIC_POINT_MIN_LEN },
  TLV_ENV_TERMINATOR, };

// NOTE we'll decode the selected method to determine the public point type and
// length of the key. Use a boolean switch to indicate request vs response
static Buffer constructKeyNegotiationTlvPayload(Buffer payload,
                                                uint16_t tlvIndex,
                                                bool isRequest)
{
  EmberNodeType myNodeType;
  EmberStatus status = emberGetNodeType(&myNodeType);

  //tlvindex has no meaning, we are just appending
  sl_zigbee_app_debug_println("Old size %X plus %X", emberMessageBufferLength(payload), sl_zigbee_tlv_get_length(&ourPointTlv));
  if (sl_zigbee_tlv_concat_to_buffer(&payload, tlvIndex, (sl_zigbee_tlv_t *) &ourPointTlv) == SL_STATUS_OK) {
    // if is key negotiation request, we need to include the selected key negotiation method
    // NOTE the latest revision of the spec mandates that both the request and response include
    // the selected key negotiation method

    sl_zigbee_app_debug_println("Appended public point tlv, new size %X", emberMessageBufferLength(payload));

    if (status != EMBER_NOT_JOINED) {
      sl_zigbee_app_debug_println("Appending nwk sequence no tlv");
    }
  } else {
    sl_zigbee_core_debug_println("Error appending tlv");
  }
  return payload;
}

// returns a bool to indicate if the message contains a public point tlv
// returns the result
static bool containsPublicKeyTlv(Buffer message,
                                 uint16_t index,
                                 sl_zigbee_direct_dlk_public_key_tlv_t *tlvResult)
{
  uint8_t p256Tag = SL_ZIGBEE_DIRECT_SECURITY_TLV_P256_PUBLIC_POINT_TAG_ID;
  uint8_t c25519Tag = SL_ZIGBEE_DIRECT_SECURITY_TLV_C25519_PUBLIC_POINT_TAG_ID;
  // this is not very readable but it basically scans once to see if a certain id exists
  // then again to actually fetch the results
  if (sl_zigbee_tlv_search_buffer_payload_for_id(message,
                                                 index,
                                                 p256Tag,
                                                 NULL,
                                                 SL_ZIGBEE_DIRECT_DLK_TLV_PUBLIC_KEY_P256_MAX_LEN) == EMBER_SUCCESS) {
    sl_zigbee_tlv_search_buffer_payload_for_id(message,
                                               index,
                                               p256Tag,
                                               (sl_zigbee_tlv_t *) tlvResult,
                                               SL_ZIGBEE_DIRECT_DLK_TLV_PUBLIC_KEY_P256_MAX_LEN);
  } else if (sl_zigbee_tlv_search_buffer_payload_for_id(message,
                                                        index,
                                                        c25519Tag,
                                                        NULL,
                                                        SL_ZIGBEE_DIRECT_DLK_TLV_PUBLIC_KEY_P256_MAX_LEN) == EMBER_SUCCESS) {
    sl_zigbee_tlv_search_buffer_payload_for_id(message,
                                               index,
                                               c25519Tag,
                                               (sl_zigbee_tlv_t *) tlvResult,
                                               SL_ZIGBEE_DIRECT_DLK_TLV_PUBLIC_KEY_P256_MAX_LEN);
  } else {
    return false;
  }
  return true;
}

static sli_dlk_ecc_curve_id get_curve_id_with_valid_public_key_tlv(sl_zigbee_direct_dlk_public_key_tlv_t tlv,
                                                                   sli_dlk_ecc_selected_method selected_method)
{
  // check to make sure the tlv matches the expected key negotiation method,
  // and that the length is sensible
  sli_dlk_ecc_curve_id curve;
  sli_dlk_ecc_selected_method method;
  uint16_t length;
  if (tlv.tag_id == SL_ZIGBEE_DIRECT_SECURITY_TLV_P256_PUBLIC_POINT_TAG_ID) {
    curve = DLK_ECC_CURVE_P256;
    method = DLK_ECC_P256_SHA_256;
    length = DLK_ECC_P256_PUBLIC_KEY_SIZE;
  } else if (tlv.tag_id == SL_ZIGBEE_DIRECT_SECURITY_TLV_C25519_PUBLIC_POINT_TAG_ID) {
    curve =  DLK_ECC_CURVE_25519;
    method = DLK_ECC_CURVE25519_AES_MMO_128;
    length = DLK_ECC_COORDINATE_SIZE;
  } else {
    curve = DLK_ECC_CURVE_INVALID;
    method = 0;
    length = 0xFFFF;
  }

  bool curveMatch = (method == selected_method);
  bool lengthOk = ((sl_zigbee_tlv_get_length(&tlv) - EUI64_SIZE) == length);

  if (!curveMatch || !lengthOk) {
    return DLK_ECC_CURVE_INVALID;
  }
  return curve;
}

static sl_status_t sli_zigbee_direct_p256_expand_shared_secret(sli_zb_sec_man_dlk_ecc_context_t *ctx)
{
  extern uint8_t sl_zvd_public_point_x[DLK_ECC_COORDINATE_SIZE];
  extern uint8_t sl_zvd_public_point_y[DLK_ECC_COORDINATE_SIZE];
  extern EmberEUI64 sl_zvd_eui;

  uint8_t buffer[DLK_ECC_COORDINATE_SIZE + EMBER_ENCRYPTION_KEY_SIZE + EUI64_SIZE + DLK_ECC_P256_PUBLIC_KEY_SIZE + EUI64_SIZE + DLK_ECC_P256_PUBLIC_KEY_SIZE];
  int buffLen = DLK_ECC_COORDINATE_SIZE + EMBER_ENCRYPTION_KEY_SIZE + EUI64_SIZE + DLK_ECC_P256_PUBLIC_KEY_SIZE + EUI64_SIZE + DLK_ECC_P256_PUBLIC_KEY_SIZE;
  int ret;

  ret = mbedtls_mpi_write_binary(&ctx->x_k, buffer, DLK_ECC_COORDINATE_SIZE);
  if (ret != 0) {
    return ret;
  }

  if (EUI64_TO_UINT64_LE(emberGetEui64()) > EUI64_TO_UINT64_LE(sl_zvd_eui)) {
    memcpy(buffer + DLK_ECC_COORDINATE_SIZE, sl_zvd_eui, EUI64_SIZE);
    memcpy(buffer + DLK_ECC_COORDINATE_SIZE + EUI64_SIZE, sl_zvd_public_point_x, DLK_ECC_COORDINATE_SIZE);
    memcpy(buffer + DLK_ECC_COORDINATE_SIZE + EUI64_SIZE + DLK_ECC_COORDINATE_SIZE, sl_zvd_public_point_y, DLK_ECC_COORDINATE_SIZE);
    memcpy(buffer + DLK_ECC_COORDINATE_SIZE + EUI64_SIZE + DLK_ECC_P256_PUBLIC_KEY_SIZE, emberGetEui64(), EUI64_SIZE);
    memcpy(buffer + DLK_ECC_COORDINATE_SIZE + EUI64_SIZE + DLK_ECC_P256_PUBLIC_KEY_SIZE + EUI64_SIZE, our_public_point, DLK_ECC_P256_PUBLIC_KEY_SIZE);
  } else {
    memcpy(buffer + DLK_ECC_COORDINATE_SIZE, emberGetEui64(), EUI64_SIZE);
    memcpy(buffer + DLK_ECC_COORDINATE_SIZE + EUI64_SIZE, our_public_point, DLK_ECC_P256_PUBLIC_KEY_SIZE);
    memcpy(buffer + DLK_ECC_COORDINATE_SIZE + EUI64_SIZE + DLK_ECC_P256_PUBLIC_KEY_SIZE, sl_zvd_eui, EUI64_SIZE);
    memcpy(buffer + DLK_ECC_COORDINATE_SIZE + EUI64_SIZE + DLK_ECC_P256_PUBLIC_KEY_SIZE + EUI64_SIZE, sl_zvd_public_point_x, DLK_ECC_COORDINATE_SIZE);
    memcpy(buffer + DLK_ECC_COORDINATE_SIZE + EUI64_SIZE + DLK_ECC_P256_PUBLIC_KEY_SIZE + EUI64_SIZE + DLK_ECC_COORDINATE_SIZE, sl_zvd_public_point_y, DLK_ECC_COORDINATE_SIZE);
  }
  memcpy(buffer + DLK_ECC_COORDINATE_SIZE + EUI64_SIZE + DLK_ECC_P256_PUBLIC_KEY_SIZE + EUI64_SIZE + DLK_ECC_P256_PUBLIC_KEY_SIZE, ctx->psk, EMBER_ENCRYPTION_KEY_SIZE);

  ret = mbedtls_sha256(buffer, buffLen, ctx->secret, 0);
  return ret;
}

sl_status_t sli_zigbee_handle_incoming_dlk_negotiation_request(Buffer message,
                                                               uint16_t payloadIndex,
                                                               EmberNodeId partnerId,
                                                               uint16_t characteristic)
{
  EmberKeyData psk;
  tokTypeMfgInstallationCode tokInstallCode;
  EmberKeyData basic_key;
  uint8_t *pointy2;
  size_t length;
  uint8_t installcode_with_crc[18];
  EmberStatus status;

  Buffer response = emberFillLinkedBuffers(NULL, SL_ZIGBEE_DIRECT_RESPONSE_MIN_LENGTH);
  if (response == NULL_BUFFER) {
    return EMBER_NO_BUFFERS;
  }

  // NOTE declarations are up here to satisfy the compiler as a result of the GOTO
  // the control flow is a little weird here since we need to shortcut
  // sending response on failures (considered harmful?)
  sl_zigbee_direct_dlk_selected_negotiation_method_tlv_t selectedTlv;

  sl_status_t sendStatus;
  //check if we are missing required TLVs
  if (!(sl_zigbee_tlv_check_general_format_env(message, payloadIndex, dlkReqLocalTlvEnv) == EMBER_SUCCESS)
      || !((sl_zigbee_tlv_search_buffer_payload_for_id(message,
                                                       payloadIndex,
                                                       SL_ZIGBEE_DIRECT_DLK_TLV_SELECTED_NEGOTIATION_METHOD_TAG_ID,
                                                       (sl_zigbee_tlv_t *) &selectedTlv,
                                                       SL_ZIGBEE_DIRECT_DLK_TLV_SELECTED_NEGOTIATION_METHOD_MAX_LEN) == EMBER_SUCCESS)
           // can contain either key
           && containsPublicKeyTlv(message, payloadIndex, &peerPointTlv))) {
    sl_zigbee_app_debug_println("Seem to be missing a needed TLV");
    return EMBER_ERR_FATAL;
  }

  sl_zigbee_app_debug_print("Peer Point TLV [");
  for (uint8_t i = 0; i < peerPointTlv.length; i++) {
    sl_zigbee_app_debug_print(" %X", peerPointTlv.value[i]);
  }
  sl_zigbee_app_debug_println("]");

  sli_dlk_ecc_selected_method selected_method = selectedTlv.value[0];
  sli_dlk_ecc_curve_id curve_id = get_curve_id_with_valid_public_key_tlv(peerPointTlv, selected_method);
  // discard if the public point tlv is invalid or unsupported
  if (curve_id == DLK_ECC_CURVE_INVALID) {
    sl_zigbee_app_debug_println("Not the negotiation method %X  against peerpoint %X with length %2X but will continue anyway", selected_method, peerPointTlv.tag_id, peerPointTlv.length);
    return EMBER_ERR_FATAL;
  }

  EmberEUI64 *peerEuiData = (EmberEUI64 *) peerPointTlv.value;

  switch (selectedTlv.value[1]) {
    case DLK_SECRET_ENUM_WELL_KNOWN_KEY:   // well-known secret
      if (sl_zvd_connection_status == PROVISIONED_IN_PROVISIONING_SESSION) {
        sl_zvd_connection_status = PROVISIONED;
        halCommonSetToken(TOKEN_PLUGIN_ZDD_AUTH_STATUS, &sl_zvd_connection_status);
      }
      if ((sl_zvd_connection_status >= PROVISIONED) && ((emberGetPermitJoining() == false) || (sl_zigbee_direct_anonymous_join_timeout_sec == 0))) {
        sl_zigbee_app_debug_println("Killing attempt as we are already commissioned (%X) or permit joining is closed %X sec or timeout %4X sec",
                                    sl_zvd_connection_status, emberAfGetOpenNetworkDurationSec(), sl_zigbee_direct_anonymous_join_timeout_sec);
        sl_bt_connection_close(sl_my_connection);
        return EMBER_ERR_FATAL;
      } else {
        sl_zigbee_app_debug_println("NOT Killing attempt as commissioned (%X) and permit joining %X sec and timeout %4X sec",
                                    sl_zvd_connection_status, emberAfGetOpenNetworkDurationSec(), sl_zigbee_direct_anonymous_join_timeout_sec);
      }
      sl_zvd_connection_status_next = PROVISIONED_IN_PROVISIONING_SESSION;
      MEMMOVE(emberKeyContents(&psk), emDlkAnonymousKeyContents, EMBER_ENCRYPTION_KEY_SIZE);
      break;

    case DLK_SECRET_ENUM_SYMMETRIC_AUTH_TOKEN:   //symmetric authentication token
      // Don't need to Handle this case at this moment
      break;

    case DLK_SECRET_ENUM_PRECONFIG_INSTALL_CODE:   //install code
      if (sl_zvd_connection_status == PROVISIONED_IN_PROVISIONING_SESSION) {
        sl_zvd_connection_status = PROVISIONED;
        halCommonSetToken(TOKEN_PLUGIN_ZDD_AUTH_STATUS, &sl_zvd_connection_status);
      }
      if ((sl_zvd_connection_status >= PROVISIONED) && ((emberGetPermitJoining() == false) || (sl_zigbee_direct_anonymous_join_timeout_sec == 0))) {
        sl_zigbee_app_debug_println("Killing attempt as we are already commissioned (%X) or permit joining is closed %X sec or timeout %4X sec",
                                    sl_zvd_connection_status, emberAfGetOpenNetworkDurationSec(), sl_zigbee_direct_anonymous_join_timeout_sec);
        sl_bt_connection_close(sl_my_connection);
        return EMBER_ERR_FATAL;
      }
      sl_zvd_connection_status_next = PROVISIONED_IN_PROVISIONING_SESSION;
      halCommonGetMfgToken(&tokInstallCode, TOKEN_MFG_INSTALLATION_CODE);
      sl_zigbee_core_debug_println("Install Code:");
      sl_zigbee_core_debug_println("CRC: %2X", tokInstallCode.crc);
      MEMCOPY(installcode_with_crc, tokInstallCode.value, 16);
      installcode_with_crc[16] = LOW_BYTE(tokInstallCode.crc);
      installcode_with_crc[17] = HIGH_BYTE(tokInstallCode.crc);
      status = sli_zigbee_af_install_code_to_key(installcode_with_crc, 18, &psk);
      sl_zigbee_core_debug_println("Install Code based key status %X: ", status);
      emberAfPrintZigbeeKey(emberKeyContents(&psk));
      break;

    case DLK_SECRET_ENUM_VARIABLE_LENGTH_PASSCODE:   // Variable length passcode
      sl_zigbee_core_debug_println("Variable length passcode:");
      emberAfPrintZigbeeKey(sl_my_passcode);
      if ((sl_my_passcode[0] == 0x00)
          && (memcmp(sl_my_passcode, sl_my_passcode + 1, EMBER_ENCRYPTION_KEY_SIZE - 1) == 0)) {
        sl_zigbee_core_debug_println("Error: Passcode with all 0 would be rejected.");
        return EMBER_ERR_FATAL;
      }
      MEMMOVE(emberKeyContents(&psk), sl_my_passcode, EMBER_ENCRYPTION_KEY_SIZE);
      break;

    case DLK_SECRET_ENUM_BASIC_ACCESS_KEY:   // basic key,
      sl_zigbee_direct_calculate_basic_key((uint8_t*)peerEuiData, emberKeyContents(&basic_key));
      MEMMOVE(emberKeyContents(&psk), emberKeyContents(&basic_key), EMBER_ENCRYPTION_KEY_SIZE);
      sl_zigbee_core_debug_println("Calculated Basic Key:");
      emberAfPrintZigbeeKey(emberKeyContents(&basic_key));
      sl_zigbee_app_debug_println("Setting COMMISSIONED_BASIC");
      sl_zvd_connection_status_next = COMMISSIONED_BASIC;
      break;

    case DLK_SECRET_ENUM_ADMIN_ACCESS_KEY:   //Admin Key
      MEMMOVE(emberKeyContents(&psk), admin_key, EMBER_ENCRYPTION_KEY_SIZE);
      sl_zigbee_app_debug_println("Setting COMMISSIONED_ADMIN");
      sl_zvd_connection_status_next = COMMISSIONED_ADMIN;
      break;

    default:
      sl_zigbee_app_debug_println("Sending Msg 2 / 2");
      return EMBER_ERR_FATAL;
      break;
  }

  sli_dlk_ecc_operation_id operation_id;
  sli_dlk_ecc_hash_id hash_id;
  // Construct the public point tlv
  if (curve_id == DLK_ECC_CURVE_25519) {
    operation_id = DLK_ECC_OPERATION_SPEKE;
    hash_id = DLK_ECC_HASH_AES_MMO_128;
    emberAfAppPrintln("Curve25519");
    ourPointTlv.tag_id = SL_ZIGBEE_DIRECT_SECURITY_TLV_C25519_PUBLIC_POINT_TAG_ID;
    sl_zigbee_tlv_set_length(&ourPointTlv, SL_ZIGBEE_DIRECT_SECURITY_TLV_C25519_PUBLIC_POINT_MAX_LEN + 1);
  } else { // P256
    operation_id = DLK_ECC_OPERATION_ECDHE_PSK;
    hash_id = DLK_ECC_HASH_SHA_256;
    emberAfAppPrintln("Curve P256");
    ourPointTlv.tag_id = SL_ZIGBEE_DIRECT_SECURITY_TLV_P256_PUBLIC_POINT_TAG_ID;
    sl_zigbee_tlv_set_length(&ourPointTlv, 72);//SL_ZIGBEE_DIRECT_SECURITY_TLV_P256_PUBLIC_POINT_MAX_LEN;
  }
  sl_zigbee_app_debug_println("Starting DLK with curve_id %X and hash_id %X length of public point %X", curve_id, hash_id, ourPointTlv.length);
  // first 8 bytes of tlv are EUI64
  MEMCOPY(ourPointTlv.value, emberGetEui64(), EUI64_SIZE);
  // the rest of the tlv is the public point
  uint8_t *publicKeyBuff = ourPointTlv.value + EUI64_SIZE;
  size_t pointSize;
  sl_status_t ret;
  sli_zb_dlk_ecc_config_t zddEccConfig = { operation_id, curve_id, hash_id };
  ret = sli_zb_sec_man_ecc_init(&ecdhCtx, &zddEccConfig, psk.contents);
  if (ret == SL_STATUS_OK) {
    ret = sli_zb_sec_man_ecc_generate_keypair(&ecdhCtx, publicKeyBuff, &pointSize);
    if (ret == SL_STATUS_OK) {
      sl_zigbee_app_debug_println("Getting the public key with size %X", pointSize);
    } else {
      sli_zb_sec_man_ecc_free(&ecdhCtx);
      sl_zigbee_app_debug_println("Not ACTUALLY getting the public key with size %X!!!", pointSize);
    }
  }

  sl_zigbee_app_debug_println("ping");
  if (curve_id == DLK_ECC_CURVE_25519) {
    MEMCOPY(our_public_point, ourPointTlv.value + EUI64_SIZE, 64);
  } else {
    MEMCOPY(our_public_point, ourPointTlv.value + EUI64_SIZE, 64);
  }
  // clear the flag and set it to indicate whether we are sending a request or response
  sl_zigbee_app_debug_println("pointSize %X", pointSize);

  //finish key negotiation
  EmberKeyData keyResult;
  // if key negotiation was successful construct the tlv response
  uint8_t *peerKeyBytes = peerPointTlv.value + EUI64_SIZE;
  EmberStatus finishStatus = EMBER_ERR_FATAL;
  ret = sli_zb_sec_man_ecc_extract_shared_secret(&ecdhCtx, peerKeyBytes, pointSize);
  if (ret == SL_STATUS_OK) {
    sl_zigbee_app_debug_println("gr2");
    if (ecdhCtx.config.operation_id == DLK_ECC_OPERATION_SPEKE) {
      ret = sli_zb_sec_man_speke_expand_shared_secret(&ecdhCtx, emberGetEui64(), *peerEuiData);
    }
    if (ecdhCtx.config.operation_id == DLK_ECC_OPERATION_ECDHE_PSK) {
      ret = sli_zigbee_direct_p256_expand_shared_secret(&ecdhCtx);
    }
    if (ret == SL_STATUS_OK) {
      sl_zigbee_app_debug_println("gr3");
      ret = sli_zb_sec_man_ecc_derive_link_key(&ecdhCtx);
      if (ret == SL_STATUS_OK) {
        sl_zigbee_app_debug_println("gr4");
        MEMCOPY(keyResult.contents, ecdhCtx.derived_key, EMBER_ENCRYPTION_KEY_SIZE);
        finishStatus = EMBER_SUCCESS;
      }
    }
  }

  if (finishStatus == EMBER_SUCCESS) {
    response = constructKeyNegotiationTlvPayload(response,
                                                 SL_ZIGBEE_DIRECT_RESPONSE_MIN_LENGTH,
                                                 SLI_ZIGBEE_DIRECT_SESSION_KEY_RESPONSE);
    // set emberTransientKeyTimeoutS to reserved value to prevent session key from timing out
    uint16_t currentTransientKeyTimeoutS = emberTransientKeyTimeoutS;
    emberTransientKeyTimeoutS = EMBER_TRANSIENT_KEY_SESSION_TIMEOUT_VAL;
    // store session key
    sl_zb_sec_man_import_transient_key(*peerEuiData, (sl_zb_sec_man_key_t*)&keyResult);
    // reset emberTransientKeyTimeoutS
    emberTransientKeyTimeoutS = currentTransientKeyTimeoutS;
  } else {
    sl_zigbee_app_debug_println("Error finishing key negotiation");
  }

  sli_zb_sec_man_ecc_free(&ecdhCtx);
  //send_response:

  pointy2 = emberMessageBufferContents(response);
  length = emberMessageBufferLength(response);
  pointy2[0] = 0x02;

  sl_zigbee_app_debug_print("Response has length %X and is [", length);
  for (uint16_t i = 0; i < length; i++) {
    sl_zigbee_app_debug_print(" %X", pointy2[i]);
  }
  sl_zigbee_app_debug_print("]");

  sendStatus = sl_bt_gatt_server_send_indication(sl_my_connection,
                                                 characteristic,
                                                 length,
                                                 pointy2);

  if (sendStatus != 0) {
    sl_zigbee_app_debug_println("Error sending message 2 with status %2X", sendStatus);
    return EMBER_ERR_FATAL;
  } else {
    sl_zigbee_app_debug_println("Message 2 sent successfully");
    return EMBER_SUCCESS;
  }
}
