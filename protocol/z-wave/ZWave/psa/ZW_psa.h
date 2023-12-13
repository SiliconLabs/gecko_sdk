#ifndef _ZW_PSA_H_
#define _ZW_PSA_H_

#include <stdint.h>
#include <string.h>
#include <psa/crypto.h>
#include <psa/crypto_values.h>
#include <s2_keystore.h>
#include <s2_psa.h>

/* Zwave key range 0x00070000 to 0x0007FFFF */
#define ZWAVE_PSA_ECDH_KEY_ID                      ((psa_key_id_t)0x00070000)
#define ZWAVE_PSA_NET_KEY_S0_ID                    ((psa_key_id_t)0x00070001)
#define ZWAVE_PSA_NET_KEY_S0_SINGLE_CAST_ID               ((psa_key_id_t)0x00070002)
#define ZWAVE_PSA_NET_KEY_S0_MULTI_CAST_ID               ((psa_key_id_t)0x00070003)
#define ZWAVE_PSA_NET_KEY_S2_UNAUTH_ID             ((psa_key_id_t)0x00070004)
#define ZWAVE_PSA_NET_KEY_S2_UNAUTH_SINGLE_CAST_ID        ((psa_key_id_t)0x00070005)
#define ZWAVE_PSA_NET_KEY_S2_UNAUTH_MULTI_CAST_ID        ((psa_key_id_t)0x00070006)
#define ZWAVE_PSA_NET_KEY_S2_AUTH_ID               ((psa_key_id_t)0x00070007)
#define ZWAVE_PSA_NET_KEY_S2_AUTH_SINGLE_CAST_ID          ((psa_key_id_t)0x00070008)
#define ZWAVE_PSA_NET_KEY_S2_AUTH_MULTI_CAST_ID          ((psa_key_id_t)0x00070009)
#define ZWAVE_PSA_NET_KEY_S2_ACCESS_ID             ((psa_key_id_t)0x0007000A)
#define ZWAVE_PSA_NET_KEY_S2_ACCESS_SINGLE_CAST_ID        ((psa_key_id_t)0x0007000B)
#define ZWAVE_PSA_NET_KEY_S2_ACCESS_MULTI_CAST_ID        ((psa_key_id_t)0x0007000C)
#define ZWAVE_PSA_NET_KEY_S2_AUTH_LR_ID            ((psa_key_id_t)0x0007000D)
#define ZWAVE_PSA_NET_KEY_S2_AUTH_LR_SINGLE_CAST_ID       ((psa_key_id_t)0x0007000E)
#define ZWAVE_PSA_NET_KEY_S2_AUTH_LR_MULTI_CAST_ID       ((psa_key_id_t)0x0007000F)
#define ZWAVE_PSA_NET_KEY_S2_ACCESS_LR_ID          ((psa_key_id_t)0x00070010)
#define ZWAVE_PSA_NET_KEY_S2_ACCESS_LR_SINGLE_CAST_ID     ((psa_key_id_t)0x00070011)
#define ZWAVE_PSA_NET_KEY_S2_ACCESS_LR_MULTI_CAST_ID     ((psa_key_id_t)0x00070012)
/* == ZWAVE_PSA_KEY_ID_MARKER == */

#define ZWAVE_MAC_SIZE                      16
#define ZWAVE_AES_CCM_KEY_SIZE              16
#define ZWAVE_ECC_KEY_SIZE                  32
#define ECC_PUBLIC_KEY_LENGTH               64

extern uint8_t public_key_buffer[ECC_PUBLIC_KEY_LENGTH+1];

typedef struct zwave_ecdh_shared_secret zwave_ecdh_shared_secret_t;

typedef struct zwave_s2_ecc_keypair_t
{
  psa_key_handle_t zwave_ecc_key_handle;
  uint8_t zwave_s2_ecc_public_key[ZWAVE_ECC_KEY_SIZE];
} zwave_s2_ecc_keypair_t;

void zw_psa_compute_sha1(const uint8_t *input, size_t in_len,
                                uint8_t *hash, size_t *hash_length);

psa_status_t zw_psa_gen_ecc_keypair(psa_key_handle_t *key_id);
psa_status_t zw_psa_gen_dynamic_ecc_keypair(zwave_s2_ecc_keypair_t *ecc_keypair);

psa_status_t zw_compute_ecdh_test_vector_nacl();

psa_status_t zw_psa_generate_random(uint8_t *output, size_t output_size);

psa_key_id_t convert_key_class_to_psa_key_id(uint8_t key_class);
psa_key_id_t convert_keyclass_to_derived_key_id (uint32_t key_class, zwave_derived_key_type_t key_type);
#ifdef ZWAVE_PSA_AES
psa_status_t zw_read_network_key_aes_cmac(psa_key_id_t key_id, uint8_t *buff, size_t buff_size, size_t *out_len);
void zw_psa_clear_all_network_keys(void);
void zw_psa_clear_network_key(uint8_t key_class);
zw_status_t zw_import_aes_key_secure_vault(uint32_t *key_id, const uint8_t *aes_key, uint32_t key_algorithm);
void DeleteAllNetworkKeys (void);
#endif

#define ZWAVE_SECURE_TRUE  0xAA55
#define ZWAVE_SECURE_FALSE 0x55AA

#endif /* _ZW_PSA_H_ */
