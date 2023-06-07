/***************************************************************************//**
 * @file sl_zigbee_security_manager_dlk_ecc_test_vectors.h
 * @brief test vectors for dynamic link key elliptic curve cryptography
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

#ifndef SL_ZIGBEE_SECURITY_MANAGER_DLK_ECC_TEST_VECTORS_H
#define SL_ZIGBEE_SECURITY_MANAGER_DLK_ECC_TEST_VECTORS_H

#include "stack/include/sl_zigbee_security_manager_dlk_ecc.h"
// SL_ZIGBEE_DLK_ECC_ENABLE_TEST_VECTORS
/// Test Vectors

// structs to help organize data for the test vectors
#ifdef P256_VECTORS_ENABLED
#define DLK_ECC_TEST_VECTOR_POINT_LENGTH DLK_ECC_P256_PUBLIC_KEY_SIZE
#else
#define DLK_ECC_TEST_VECTOR_POINT_LENGTH DLK_ECC_CURVE25519_PUBLIC_KEY_SIZE
#endif

typedef struct sl_zigbee_dlk_ecc_test_vector_profile_data {
  uint8_t GIVEN_eui64[8];
  uint8_t GIVEN_privkey[DLK_ECC_COORDINATE_SIZE];
  uint32_t EXPECT_pubkeys[][DLK_ECC_TEST_VECTOR_POINT_LENGTH];
} sli_zigbee_dlk_ecc_test_vector_profile_data_t;

typedef struct sl_zigbee_dlk_ecc_test_vector_shared_data {
  sli_zb_dlk_ecc_config_t config;
  uint8_t GIVEN_psk[DLK_KEY_SIZE];
  uint8_t EXPECT_G[DLK_ECC_TEST_VECTOR_POINT_LENGTH];
  uint8_t EXPECT_x_k[DLK_ECC_COORDINATE_SIZE];
  uint8_t EXPECT_s[MAX_SHARED_SECRET_LEN];
  uint8_t EXPECT_dk[DLK_KEY_SIZE];
} sli_zigbee_dlk_ecc_test_vector_shared_data_t;

typedef struct sli_zigbee_dlk_ecc_test_vector_bundle {
  sli_zigbee_dlk_ecc_test_vector_shared_data_t *shared;
  sli_zigbee_dlk_ecc_test_vector_profile_data_t *profile;
} sli_zigbee_dlk_ecc_test_vector_bundle_t;

// test vector givens
#define GIVEN_speke_c25519_alice_privkey            \
  {                                                 \
    0x41, 0x6C, 0x69, 0x63, 0x65, 0x41, 0x6C, 0x69, \
    0x63, 0x65, 0x41, 0x6C, 0x69, 0x63, 0x65, 0x41, \
    0x6C, 0x69, 0x63, 0x65, 0x41, 0x6C, 0x69, 0x63, \
    0x65, 0x41, 0x6C, 0x69, 0x63, 0x65, 0x41, 0x6C, \
  }
#define GIVEN_speke_alice_eui64 { 0xAA, 0x00, 0xA0, 0xA0, 0x0A, 0x0A, 0xA0, 0xA0, }

#define GIVEN_speke_c25519_bob_privkey              \
  {                                                 \
    0x42, 0x6F, 0x62, 0x42, 0x6F, 0x62, 0x42, 0x6F, \
    0x62, 0x42, 0x6F, 0x62, 0x42, 0x6F, 0x62, 0x42, \
    0x6F, 0x62, 0x42, 0x6F, 0x62, 0x42, 0x6F, 0x62, \
    0x42, 0x6F, 0x62, 0x42, 0x6F, 0x62, 0x42, 0x6F, \
  }
#define GIVEN_speke_bob_eui64 { 0xBB, 0x00, 0xB0, 0xB0, 0x0B, 0x0B, 0xB0, 0xB0, }

// NOTE more memory/programmer friendly way of laying out the test vectors
extern struct sl_zigbee_dlk_ecc_test_vector_shared_data sl_dlk_ecc_speke_c25519_share_data[];
extern struct sl_zigbee_dlk_ecc_test_vector_profile_data sl_dlk_ecc_speke_c25519_alice_data;
extern struct sl_zigbee_dlk_ecc_test_vector_profile_data sl_dlk_ecc_speke_c25519_bob_data;

// NOTE these apis are for managing the 'assumed role' if performing live dlk with test vectors
sli_zigbee_dlk_ecc_test_vector_profile_data_t* sli_zigbee_dlk_ecc_test_vector_get_profile(void);
void sli_zigbee_dlk_ecc_test_vector_set_profile(sli_zigbee_dlk_ecc_test_vector_profile_data_t* profile);

sl_status_t sli_zb_sec_man_ecc_init_with_test_vector(
  sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx,
  sli_zb_dlk_ecc_config_t *config,
  uint8_t *psk,
  sli_zigbee_dlk_ecc_test_vector_bundle_t *vector_data);

#endif // SL_ZIGBEE_SECURITY_MANAGER_DLK_ECC_TEST_VECTORS_H
