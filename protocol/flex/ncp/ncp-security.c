#include "stack/include/ember.h"
#include "stack/include/stack-info.h"
#include "stack/core/sli-connect-api.h"
#include "psa/crypto.h"
#include "ncp-security.h"

EmberStatus emApiSetNcpSecurityKey(uint8_t *keyContents, uint8_t keyLength)
{
  EmberStatus emstatus = EMBER_ERR_FATAL;

  psa_key_attributes_t key_attr;
  psa_status_t status;
  psa_key_id_t key_id;

  if (keyLength != EMBER_ENCRYPTION_KEY_SIZE) {
    return EMBER_BAD_ARGUMENT;
  }

  key_attr = psa_key_attributes_init();
  psa_set_key_type(&key_attr, PSA_KEY_TYPE_AES);
  psa_set_key_bits(&key_attr, 128);
  psa_set_key_usage_flags(&key_attr, PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT);
  psa_set_key_algorithm(&key_attr, PSA_ALG_ECB_NO_PADDING);
  #ifdef PSA_KEY_LOCATION_SLI_SE_OPAQUE
  psa_set_key_lifetime(&key_attr,
                       PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(
                         PSA_KEY_LIFETIME_VOLATILE,
                         PSA_KEY_LOCATION_SLI_SE_OPAQUE));
  #else
  psa_set_key_lifetime(&key_attr,
                       PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(
                         PSA_KEY_LIFETIME_VOLATILE,
                         PSA_KEY_LOCATION_LOCAL_STORAGE));
  #endif

  status = psa_import_key(&key_attr,
                          keyContents,
                          keyLength,
                          &key_id);

  if (status != PSA_SUCCESS) {
    return EMBER_SECURITY_DATA_INVALID;
  }

  emstatus = emApiSetPsaSecurityKey(key_id);
  return emstatus;
}
