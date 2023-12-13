#include "stack/include/ember.h"
#include "stack/include/stack-info.h"
#include "stack/core/sli-connect-api.h"
#include "psa/crypto.h"
#include "ncp-security.h"
#include "ncp-init.h"
#include "core/sli-connect-token.h"

#define SLI_CONNECT_CRYPTO_INVALID_KEY_ID (0x00000000)

EmberEventControl sl_connect_ncp_security_init_event;

static EmberStatus import_psa_key(uint8_t *keyContents, uint8_t keyLength, psa_key_lifetime_t key_lifetime, psa_key_id_t *key_id)
{
  psa_key_attributes_t key_attr;
  psa_status_t status;

  key_attr = psa_key_attributes_init();
  psa_set_key_type(&key_attr, PSA_KEY_TYPE_AES);
  psa_set_key_bits(&key_attr, 128);
  psa_set_key_usage_flags(&key_attr, PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT);
  psa_set_key_algorithm(&key_attr, PSA_ALG_ECB_NO_PADDING);
  if (key_lifetime == PSA_KEY_LIFETIME_PERSISTENT) {
    psa_set_key_id(&key_attr, *key_id);
  }

  #ifdef PSA_KEY_LOCATION_SLI_SE_OPAQUE
  psa_set_key_lifetime(&key_attr,
                       PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(
                         key_lifetime,
                         PSA_KEY_LOCATION_SLI_SE_OPAQUE));
  #else
  psa_set_key_lifetime(&key_attr,
                       PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(
                         key_lifetime,
                         PSA_KEY_LOCATION_LOCAL_STORAGE));
  #endif

  status = psa_import_key(&key_attr,
                          keyContents,
                          keyLength,
                          key_id);

  if (status != PSA_SUCCESS) {
    return EMBER_SECURITY_DATA_INVALID;
  }
  return EMBER_SUCCESS;
}

EmberStatus emApiSetNcpSecurityKeyPersistent(uint8_t *keyContents, uint8_t keyLength, uint32_t key_id)
{
  EmberStatus emstatus = EMBER_ERR_FATAL;

  if (keyLength != EMBER_ENCRYPTION_KEY_SIZE) {
    return EMBER_BAD_ARGUMENT;
  }

  // Destroy the key if it exists
  psa_destroy_key(key_id);

  emstatus = import_psa_key(keyContents, keyLength, PSA_KEY_LIFETIME_PERSISTENT, &key_id);
  if (EMBER_SUCCESS != emstatus) {
    return emstatus;
  }
  emstatus = emApiSetPsaSecurityKey(key_id);
  if (EMBER_SUCCESS != emstatus) {
    return emstatus;
  }
  // Store the key ID in the NVM to recover it in case of a reset
  sl_token_set_data(TOKEN_STACK_SECURITY_KEY_ID,
                    0,
                    (tokTypeStackKeyID*)&key_id,
                    TOKEN_STACK_SECURITY_KEY_ID_SIZE);
  return emstatus;
}

EmberStatus emApiSetNcpSecurityKey(uint8_t *keyContents, uint8_t keyLength)
{
  EmberStatus emstatus = EMBER_ERR_FATAL;

  psa_status_t status;
  psa_key_id_t key_id = emApiGetKeyId();

  if (keyLength != EMBER_ENCRYPTION_KEY_SIZE) {
    return EMBER_BAD_ARGUMENT;
  }

  if (key_id != SLI_CONNECT_CRYPTO_INVALID_KEY_ID) {
    // Allow persistant key be replaced by deleting the old one
    status = psa_destroy_key(key_id);
    if (status != PSA_SUCCESS) {
      return EMBER_ERR_FATAL;
    }
  }

  emstatus = import_psa_key(keyContents, keyLength, PSA_KEY_LIFETIME_VOLATILE, &key_id);
  if (EMBER_SUCCESS != emstatus) {
    return emstatus;
  }
  emstatus = emApiSetPsaSecurityKey(key_id);
  return emstatus;
}

// We cannot load a NVM item in a stack_init event so instead we instantiate an event
// that is triggered only once
void sli_connect_ncp_key_loader_handler(void)
{
  psa_key_id_t key_id;
  sl_token_set_data(TOKEN_STACK_SECURITY_KEY_ID,
                    0,
                    (tokTypeStackKeyID*)&key_id,
                    TOKEN_STACK_SECURITY_KEY_ID_SIZE);

  if ((key_id != SLI_CONNECT_CRYPTO_INVALID_KEY_ID) && (key_id != 0xFFFFFFFFu)) {
    emApiSetPsaSecurityKey(key_id);
  }
  emberEventControlSetInactive(sl_connect_ncp_security_init_event);
}

void sli_connect_init_ncp_security(void)
{
  emberEventControlSetActive(sl_connect_ncp_security_init_event);
}
