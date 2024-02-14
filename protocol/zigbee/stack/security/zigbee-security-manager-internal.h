/***************************************************************************//**
 * @file
 * @brief Internal definitions of security-related APIs, including key storage,
 *   key fetching, and crypto operations. Keys are ultimately stored in secure
 *   storage, for capable parts, or in cleartext NVM3 tokens.
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef _ZIGBEE_SECURITY_MANAGER_INTERNAL_H_
#define _ZIGBEE_SECURITY_MANAGER_INTERNAL_H_

// ZigBee defines the Load/Transport Key derivation as the outcome of
// performing our HMAC Hash function with the Link Key and a 1-octet
// input string (for transport key: 0x00, for load key: 0x02, etc).

#define DERIVE_TRANSPORT_KEY_TAG 0x00
#define DERIVE_LOAD_KEY_TAG      0x02
#define DERIVE_VERIFY_KEY_TAG    0x03

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif

// zigbeed does not have access to psa/crypto.h, and some unit tests without it
// will compile this file as well.
#ifndef SL_CATALOG_ZIGBEE_STACK_UNIX_PRESENT

//taken from ccm-star so these function calls are defined
#if defined(MBEDTLS_PSA_ACCEL_KEY_TYPE_AES) && defined(MBEDTLS_PSA_ACCEL_ALG_CCM) && defined(MBEDTLS_PSA_CRYPTO_DRIVERS)
#include "em_device.h"

//We're using some PSA APIs for all parts in zigbee-security-manager
#include "psa/crypto.h"

#if defined(SEMAILBOX_PRESENT)
#include "sli_se_transparent_functions.h"
#define AEAD_ENCRYPT_TAG_FCT    sli_se_driver_aead_encrypt_tag
#define AEAD_DECRYPT_TAG_FCT    sli_se_driver_aead_decrypt_tag
#define CIPHER_SINGLE_SHOT_ENC_FCT sli_se_transparent_cipher_encrypt
#define CIPHER_SINGLE_SHOT_DEC_FCT sli_se_transparent_cipher_decrypt
#elif defined(CRYPTO_PRESENT)
#include "sli_crypto_transparent_functions.h"
#define AEAD_ENCRYPT_TAG_FCT    sli_crypto_transparent_aead_encrypt_tag
#define AEAD_DECRYPT_TAG_FCT    sli_crypto_transparent_aead_decrypt_tag
#define CIPHER_SINGLE_SHOT_ENC_FCT sli_crypto_transparent_cipher_encrypt
#define CIPHER_SINGLE_SHOT_DEC_FCT sli_crypto_transparent_cipher_decrypt
#elif defined(CRYPTOACC_PRESENT)
#include "sli_cryptoacc_transparent_functions.h"
#define AEAD_ENCRYPT_TAG_FCT    sli_cryptoacc_transparent_aead_encrypt_tag
#define AEAD_DECRYPT_TAG_FCT    sli_cryptoacc_transparent_aead_decrypt_tag
#define CIPHER_SINGLE_SHOT_ENC_FCT sli_cryptoacc_transparent_cipher_encrypt
#define CIPHER_SINGLE_SHOT_DEC_FCT sli_cryptoacc_transparent_cipher_decrypt
#else // SEMAILBOX_PRESENT || CRYPTO_PRESENT || CRYPTOACC_PRESENT
#error "Compiling with PSA drivers for CCM, but not for a Silicon Labs target"
#endif // SEMAILBOX_PRESENT || CRYPTO_PRESENT || CRYPTOACC_PRESENT

#endif // if defined(MBEDTLS_PSA_ACCEL_KEY_TYPE_AES) && defined(MBEDTLS_PSA_ACCEL_ALG_CCM) && defined(PSA_WANT_ALG_CCM) && defined(MBEDTLS_PSA_CRYPTO_DRIVERS)

#endif // !SL_CATALOG_ZIGBEE_STACK_UNIX_PRESENT

sl_status_t zb_sec_man_check_key_context(sl_zb_sec_man_context_t* context);
sl_status_t zb_sec_man_delete_key_by_psa_id(uint32_t psa_id);
void zb_sec_man_delete_all_keys(void);
sl_status_t zb_sec_man_derive_key(sl_zb_sec_man_key_t* core_key,
                                  const sl_zb_sec_man_context_t* context,
                                  sl_zb_sec_man_key_t* derived_key);
sl_status_t zb_sec_man_delete_key(sl_zb_sec_man_context_t* context);
sl_status_t zb_sec_man_store_nwk_key(sl_zb_sec_man_context_t* context,
                                     sl_zb_sec_man_key_t* plaintext_key);
sl_status_t zb_sec_man_fetch_nwk_key(sl_zb_sec_man_context_t* context,
                                     sl_zb_sec_man_key_t* plaintext_key);
sl_status_t zb_sec_man_store_tc_link_key(sl_zb_sec_man_context_t* context,
                                         sl_zb_sec_man_key_t* plaintext_key);
sl_status_t zb_sec_man_fetch_tc_link_key(sl_zb_sec_man_context_t* context,
                                         sl_zb_sec_man_key_t* plaintext_key);
sl_status_t zb_sec_man_store_transient_key(sl_zb_sec_man_context_t* context,
                                           sl_zb_sec_man_key_t* plaintext_key);
sl_status_t zb_sec_man_fetch_transient_key(sl_zb_sec_man_context_t* context,
                                           sl_zb_sec_man_key_t* plaintext_key);
sl_status_t zb_sec_man_store_in_link_key_table(sl_zb_sec_man_context_t* context,
                                               sl_zb_sec_man_key_t* plaintext_key);
sl_status_t zb_sec_man_fetch_from_link_key_table(sl_zb_sec_man_context_t* context,
                                                 sl_zb_sec_man_key_t* plaintext_key);
sl_status_t zb_sec_man_fetch_zll_key(sl_zb_sec_man_context_t* context,
                                     sl_zb_sec_man_key_t* plaintext_key);
sl_status_t zb_sec_man_store_zll_key(sl_zb_sec_man_context_t* context,
                                     sl_zb_sec_man_key_t* plaintext_key);
sl_status_t zb_sec_man_fetch_gp_key(sl_zb_sec_man_context_t* context,
                                    sl_zb_sec_man_key_t* plaintext_key);
sl_status_t zb_sec_man_store_gp_key(sl_zb_sec_man_context_t* context,
                                    sl_zb_sec_man_key_t* plaintext_key);
sl_status_t zb_sec_man_store_cli_password_key(sl_zb_sec_man_context_t* context,
                                              sl_zb_sec_man_key_t* plaintext_key);
sl_status_t zb_sec_man_fetch_cli_password_key(sl_zb_sec_man_context_t* context,
                                              sl_zb_sec_man_key_t* plaintext_key);
sl_status_t zb_sec_man_store_cbke_mac_key(sl_zb_sec_man_context_t* context,
                                          sl_zb_sec_man_key_t* plaintext_key);
sl_status_t zb_sec_man_fetch_cbke_mac_key(sl_zb_sec_man_context_t* context,
                                          sl_zb_sec_man_key_t* plaintext_key);
sl_status_t zb_sec_man_store_internal_key(sl_zb_sec_man_context_t* context,
                                          sl_zb_sec_man_key_t* plaintext_key);
sl_status_t zb_sec_man_fetch_internal_key(sl_zb_sec_man_context_t* context,
                                          sl_zb_sec_man_key_t* plaintext_key);

sl_status_t zb_sec_man_hmac_aes_mmo(const uint8_t* input,
                                    const uint8_t data_length,
                                    uint8_t* output);

sl_status_t zb_sec_man_fetch_tc_link_key_info(sl_zb_sec_man_context_t* context,
                                              sl_zb_sec_man_aps_key_metadata_t* key_data);
sl_status_t zb_sec_man_fetch_transient_key_info(sl_zb_sec_man_context_t* context,
                                                sl_zb_sec_man_aps_key_metadata_t* key_data);
sl_status_t zb_sec_man_fetch_link_key_table_key_info(sl_zb_sec_man_context_t* context,
                                                     sl_zb_sec_man_aps_key_metadata_t* key_data);

sl_status_t zb_sec_man_delete_transient_key_by_eui(sl_zb_sec_man_context_t* context);

//Backs up a loaded context state.
//If direction is true, save in backup; if false, restore from it.
//Used by functions that are called by Zigbee Security Manager and also call an API within it
//(so they can restore the state they were called from).
void zb_sec_man_backup_key_context(bool direction);

//Returns the value of a derived key.
sl_status_t sli_zigbee_sec_man_export_derived_key(sl_zb_sec_man_context_t* context,
                                                  sl_zb_sec_man_key_t* derived_key);

#endif // _ZIGBEE_SECURITY_MANAGER_INTERNAL_H_
