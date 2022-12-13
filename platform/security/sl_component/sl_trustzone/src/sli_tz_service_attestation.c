/***************************************************************************//**
 * @file
 * @brief Silicon Labs TrustZone attestation service (secure side).
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

#include <string.h>
#include "em_device.h"
#include "sli_tz_iovec_check.h"

#if (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)
  #include "tz_secure_memory_autogen.h"

  #include "em_system.h"

// SE Manager
  #include "sl_se_manager_util.h"

// PSA Crypto
  #include "psa/crypto.h"
  #include "psa/crypto_types.h"
  #include "psa/crypto_values.h"
  #include "psa/internal_trusted_storage.h"
  #include "psa/sli_internal_trusted_storage.h"

// TF-M
  #include "attest.h"
  #include "attest_token.h"
  #include "attest_eat_defines.h"
  #include "tfm_plat_defs.h"
  #include "tfm_attest_hal.h"
  #include "tfm_plat_device_id.h"
  #include "tfm_plat_crypto_keys.h"

// QCBOR
  #include "qcbor.h"
  #include "q_useful_buf.h"

// Bootloader interface
  #include "api/btl_interface.h"
  #include "api/application_properties.h"
#else
// PSA Crypto
  #include "psa/crypto_types.h"
  #include "psa/crypto_values.h"

// SE Manager
  #include "sl_se_manager_util.h"
  #include "sl_se_manager_attestation.h"
#endif // (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)

// -----------------------------------------------------------------------------
// External symbols

#if (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)
extern const uint32_t linker_vectors_begin;
#endif // (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)

//------------------------------------------------------------------------------
// Defines

#define ATTESTATION_PUBLIC_KEY_SIZE        (1u + 64u)
#if (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)
  #define ATTESTATION_KEY_UID              (0xFFFFFFFFFFFFFFFFULL)
  #define ATTESTATION_PRIVATE_KEY_SIZE     (32u)
  #define INVALID_KEY_ID                   mbedtls_svc_key_id_make(0, 0xfedcba98)
  #define INSTANCE_ID_LENGTH               (9u)
  #define BOOT_SEED_LENGTH                 (32u)
  #define TZ_ATTESTATION_SHA256_DIGESTSIZE (32u)
  #define IMPLEMENTATION_ID_SIZE           (32u)
  #define FIRMWARE_END                     TZ_S_FLASH_END
// The NS application start right after the S application.
  #define TZ_NS_FLASH_START                (FIRMWARE_END)
#endif // (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)

//------------------------------------------------------------------------------
// Global variables

#if (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)
// The below variables are initialized at startup in the SKL main.
extern bool                          otp_initialized;
extern sl_se_otp_init_t              otp_configuration;
extern uint32_t                      otp_version;
extern const ApplicationProperties_t sl_app_properties;
#endif // (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)

//------------------------------------------------------------------------------
// Static variables

#if (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)
static const uint8_t profile_id_psa[] =
{ 'h', 't', 't', 'p', ':', '/', '/', 'a', 'r', 'm', '.', 'c', 'o', 'm', '/',
  'p', 's', 'a', '/', '2', '.', '0', '.', '0' };
static const uint8_t measurement_type_bl[] =
{ 'B', 'L' };
static const uint8_t measurement_type_prot[] =
{ 'P', 'R', 'o', 'T' };
static const uint8_t measurement_type_app[] =
{ 'A', 'P', 'P' };
static uint8_t boot_seed[BOOT_SEED_LENGTH] = { 0u };
static bool bood_seed_generated = false;
#endif // (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)

//------------------------------------------------------------------------------
// Static function declarations

#if (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)
static psa_status_t generate_firmware_hash(uint8_t *firmware_addr,
                                           size_t firmware_size,
                                           uint8_t *hash_buffer,
                                           size_t *hash_size);
static bool validate_signature_location(uint32_t firmware_start, uint32_t firmware_end);
static uint32_t get_application_properties_struct_addr(uint32_t start_addr);
static bool check_application_properties_magic(ApplicationProperties_t *app_properties);
static void version_to_string(uint8_t  *buffer,
                              uint32_t version);
static void prepare_key_attribute(psa_key_attributes_t *key_attr);
static psa_status_t generate_attestation_key(void);
static psa_status_t check_existence_attestation_key(void);
static psa_status_t check_and_generate_attestation_key(void);
static psa_status_t get_attestation_public_key(uint8_t *output_key);
static psa_status_t get_attestation_private_key(uint8_t *key_buffer,
                                                size_t key_size);
static bool bootloader_exists(void);
#else
static psa_status_t error_mapping_sl_status_to_psa_status(sl_status_t status);
#endif // (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)

//------------------------------------------------------------------------------
// Helper functions

// Get attestation public key.
static psa_status_t get_attestation_get_public_key(uint8_t *key_buffer,
                                                   size_t key_size)
{
  if (key_size != ATTESTATION_PUBLIC_KEY_SIZE) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

#if (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)
  psa_status_t status = PSA_ERROR_GENERIC_ERROR;

  status = check_and_generate_attestation_key();
  if (status != PSA_SUCCESS) {
    return status;
  }

  return get_attestation_public_key(key_buffer);
#else
  sl_status_t status = SL_STATUS_FAIL;
  sl_se_command_context_t cmd_ctx = { 0 };

  status = sl_se_init();
  if (status != SL_STATUS_OK) {
    return error_mapping_sl_status_to_psa_status(status);
  }
  status = sl_se_init_command_context(&cmd_ctx);
  if (status != SL_STATUS_OK) {
    return error_mapping_sl_status_to_psa_status(status);
  }

  status = sl_se_read_pubkey(&cmd_ctx,
                             SL_SE_KEY_TYPE_IMMUTABLE_SE_ATTESTATION,
                             key_buffer,
                             (key_size - 1u));

  // Write the uncompressed format byte
  if (status == SL_STATUS_OK) {
    if (memmove(&key_buffer[1], key_buffer, ATTESTATION_PUBLIC_KEY_SIZE) == NULL) {
      return PSA_ERROR_BAD_STATE;
    }
    key_buffer[0u] = 0x04;
  }
  return error_mapping_sl_status_to_psa_status(status);
#endif // (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)
}

#if (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)

// Generate hash of the input data
static psa_status_t generate_firmware_hash(uint8_t *firmware_addr,
                                           size_t firmware_size,
                                           uint8_t *hash_buffer,
                                           size_t *hash_size)
{
  #if (FLASH_BASE == 0UL)
  // Process the first 4 bytes by moving them into the stack buffer.
  // this is needed since the address 0 can't be used as the input.

  #define HASH_BUFFER_SIZE (4u)
  psa_hash_operation_t hash_operation;
  hash_operation = psa_hash_operation_init();

  psa_status_t status = psa_hash_setup(&hash_operation, PSA_ALG_SHA_256);
  if (status != PSA_SUCCESS) {
    return status;
  }
  uint8_t hash_in_buffer[HASH_BUFFER_SIZE];
  memcpy(hash_in_buffer, (uint8_t *)((uint32_t)firmware_addr), HASH_BUFFER_SIZE);
  status = psa_hash_update(&hash_operation,
                           (const uint8_t *)hash_in_buffer,
                           HASH_BUFFER_SIZE);
  if (status != PSA_SUCCESS) {
    return status;
  }
  status = psa_hash_update(&hash_operation,
                           (uint8_t *)((uint32_t)firmware_addr + HASH_BUFFER_SIZE),
                           firmware_size - HASH_BUFFER_SIZE);
  if (status != PSA_SUCCESS) {
    return status;
  }
  status = psa_hash_finish(&hash_operation,
                           hash_buffer,
                           TZ_ATTESTATION_SHA256_DIGESTSIZE,
                           hash_size);
  #else
  psa_status_t status = psa_hash_compute(PSA_ALG_SHA_256,
                                         (const uint8_t *)firmware_addr,
                                         firmware_size,
                                         hash_buffer,
                                         TZ_ATTESTATION_SHA256_DIGESTSIZE,
                                         hash_size);
  #endif
  return status;
}

// Validates the signature location address
static bool validate_signature_location(uint32_t firmware_start, uint32_t firmware_end)
{
  if ((firmware_end < firmware_start)
      || (firmware_end > FLASH_BASE + FLASH_SIZE)) {
    // Signature location is not set, which indicates that the firmware is not
    // even signed.
    return false;
  }
  return true;
}

static uint32_t get_application_properties_struct_addr(uint32_t start_addr)
{
  uint32_t *application_properties_ptr
    = (uint32_t *)(start_addr + (uint32_t)offsetof(BareBootTable_t, signature));
  return *application_properties_ptr;
}

// Checks the application properties struct magic
static bool check_application_properties_magic(ApplicationProperties_t *app_properties)
{
  if ((app_properties == NULL) || ((uint32_t) app_properties == 0xFFFFFFFFUL)) {
    return false;
  }

  if (((uint32_t)app_properties > (FLASH_BASE + FLASH_SIZE - sizeof(ApplicationProperties_t)))
  #if (FLASH_BASE > 0x0UL)
      || ((uint32_t)app_properties < FLASH_BASE)
  #endif
      ) {
    return false;
  }

  uint8_t magicRev[16U] = APPLICATION_PROPERTIES_REVERSED;
  uint8_t *magic = (uint8_t *)app_properties->magic;

  for (size_t i = 0U; i < 16U; i++) {
    if (magicRev[15U - i] != magic[i]) {
      return false;
    }
  }

  return true;
}

// Converts a uint32 (corresponding to a version number) to an ASCII string.
// Note: the input buffer needs to be at least 8 bytes of size.
static void version_to_string(uint8_t  *buffer,
                              uint32_t version)
{
  for (size_t i = 0; i < 8; i++) {
    uint8_t char_value =  (version >> ((7 - i) * 4)) & 0xF;
    if (char_value > 0x9) {
      // Start counting from character 'A' (index 0x41 of the ASCII table).
      buffer[i] = char_value - 0xA + 0x41;
    } else {
      // Start counting from character '0' (index 0x30 of the ASCII table).
      buffer[i] = char_value + 0x30;
    }
  }
}

// Prepares a key attribute for the attestation key
static void prepare_key_attribute(psa_key_attributes_t *key_attr)
{
  psa_key_type_t key_type = PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1);
  psa_key_usage_t usage = PSA_KEY_USAGE_EXPORT | PSA_KEY_USAGE_SIGN_HASH | PSA_KEY_USAGE_VERIFY_HASH;
  *key_attr = psa_key_attributes_init();
  psa_set_key_type(key_attr, key_type);
  psa_set_key_bits(key_attr, 256u);
  psa_set_key_usage_flags(key_attr, usage);
  psa_set_key_algorithm(key_attr, PSA_ALG_ECDSA_ANY);
}

// Generate the attestation key and store it in ITS.
static psa_status_t generate_attestation_key(void)
{
  uint8_t attestation_private_key[ATTESTATION_PRIVATE_KEY_SIZE];
  size_t export_key_output_size = 0u;

  psa_status_t status = PSA_ERROR_GENERIC_ERROR;
  mbedtls_svc_key_id_t key_id = INVALID_KEY_ID;
  psa_key_attributes_t key_attr;
  prepare_key_attribute(&key_attr);

  status = psa_generate_key(&key_attr, &key_id);
  if (status != PSA_SUCCESS) {
    return status;
  }

  status = psa_export_key(key_id,
                          attestation_private_key,
                          sizeof(attestation_private_key),
                          &export_key_output_size);
  if (status != PSA_SUCCESS) {
    // It is fine to clean the key buffer anyway.
    goto exit;
  }

  status = psa_its_set(ATTESTATION_KEY_UID,
                       sizeof(attestation_private_key),
                       attestation_private_key,
                       PSA_STORAGE_FLAG_WRITE_ONCE_SECURE_ACCESSIBLE);
  if (status != PSA_SUCCESS) {
    goto exit;
  }

  exit:
  // Clean the private key buffer explicitly
  memset(attestation_private_key, 0u, sizeof(attestation_private_key));
  // The key has been generated and stored in ITS, hence the key can be cleaned.
  (void)psa_destroy_key(key_id);
  return status;
}

// Check existence of the attestation key.
static psa_status_t check_existence_attestation_key(void)
{
  struct psa_storage_info_t attestation_storage_info;
  psa_status_t status = psa_its_get_info(ATTESTATION_KEY_UID,
                                         &attestation_storage_info);
  if (status != PSA_SUCCESS) {
    // All the error code including PSA_ERROR_DOES_NOT_EXIST should be returned.
    return status;
  }

  if (attestation_storage_info.flags != PSA_STORAGE_FLAG_WRITE_ONCE_SECURE_ACCESSIBLE) {
    // A wrong flag is set to this UID. Return this error code and try to update
    // the object using the attestation UID.
    return PSA_ERROR_DOES_NOT_EXIST;
  }

  return status;
}

// Check existence of the attestation key and generate one if it does not exist.
static psa_status_t check_and_generate_attestation_key(void)
{
  psa_status_t status = check_existence_attestation_key();
  if (status == PSA_ERROR_DOES_NOT_EXIST) {
    status = generate_attestation_key();
  }

  return status;
}

// Read the attestation public key from ITS.
// @param[out] output_key: buffer storing the attestation public key.
static psa_status_t get_attestation_public_key(uint8_t *output_key)
{
  size_t output_length = 0u;
  uint8_t attestation_private_key[ATTESTATION_PRIVATE_KEY_SIZE];
  psa_status_t status = PSA_ERROR_GENERIC_ERROR;

  status = psa_its_get(ATTESTATION_KEY_UID,
                       0u,
                       sizeof(attestation_private_key),
                       attestation_private_key,
                       &output_length);
  if (status != PSA_SUCCESS) {
    return status;
  }

  mbedtls_svc_key_id_t key_id = INVALID_KEY_ID;
  psa_key_attributes_t key_attr;
  prepare_key_attribute(&key_attr);

  status = psa_import_key(&key_attr,
                          attestation_private_key,
                          sizeof(attestation_private_key),
                          &key_id);
  if (status != PSA_SUCCESS) {
    goto exit;
  }

  status = psa_export_public_key(key_id,
                                 output_key,
                                 ATTESTATION_PUBLIC_KEY_SIZE,
                                 &output_length);
  (void)psa_destroy_key(key_id);

  exit:
  // Clean the private key buffer explicitly
  memset(attestation_private_key, 0u, sizeof(attestation_private_key));
  return status;
}

// Get attestation private key.
static psa_status_t get_attestation_private_key(uint8_t *key_buffer,
                                                size_t key_size)
{
  psa_status_t status = PSA_ERROR_GENERIC_ERROR;
  size_t output_length = 0u;

  status = check_and_generate_attestation_key();
  if (status != PSA_SUCCESS) {
    return status;
  }

  return psa_its_get(ATTESTATION_KEY_UID,
                     0u,
                     key_size,
                     key_buffer,
                     &output_length);
}

// Check if we have a bootloader or not.
static bool bootloader_exists(void)
{
  bool bootloader_present = false;
  BootloaderInformation_t bl_info;
  bootloader_getInfo(&bl_info);
  if (bl_info.type == SL_BOOTLOADER) {
    bootloader_present = true;
  }

  return bootloader_present;
}

#else // (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)

// Error mapping function.
static psa_status_t error_mapping_sl_status_to_psa_status(sl_status_t status)
{
  switch (status) {
    case SL_STATUS_OK:
      return PSA_SUCCESS;
      break;
    case SL_STATUS_NOT_INITIALIZED:
      return PSA_ERROR_SERVICE_FAILURE;
      break;
    case SL_STATUS_INVALID_PARAMETER:
      return PSA_ERROR_INVALID_ARGUMENT;
      break;
    case SL_STATUS_WOULD_OVERFLOW:
      return PSA_ERROR_BUFFER_TOO_SMALL;
      break;
    case SL_STATUS_NOT_SUPPORTED:
    case SL_STATUS_NOT_AVAILABLE:
    case SL_STATUS_FAIL:
    default:
      return PSA_ERROR_GENERIC_ERROR;
  }
}

#endif // (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)

//-------------------------------------
// Public functions

#if (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)

enum tfm_plat_err_t sli_plat_get_initial_attest_key(uint8_t          *key_buf,
                                                    uint32_t          size,
                                                    struct ecc_key_t *ecc_key,
                                                    psa_ecc_family_t *curve_type)
{
  if (size < ATTESTATION_PRIVATE_KEY_SIZE) {
    return TFM_PLAT_ERR_INVALID_INPUT;
  }

  psa_status_t status = get_attestation_private_key(key_buf,
                                                    size);
  if (status != PSA_SUCCESS) {
    return TFM_PLAT_ERR_SYSTEM_ERR;
  }
  ecc_key->priv_key = key_buf;
  ecc_key->priv_key_size = ATTESTATION_PRIVATE_KEY_SIZE;
  *curve_type = PSA_ECC_FAMILY_SECP_R1;
  return TFM_PLAT_ERR_SUCCESS;
}

#endif // (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)

//-------------------------------------
// IAT Claims

#if (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)

// 2394: ARM PSA Partition ID
enum psa_attest_err_t sli_attest_get_caller_client_id(int32_t *caller_id)
{
  // Client ID isn't available for the secure library.
  // Set -1 since request came from a non-secure master.
  *caller_id = -1;
  return PSA_ATTEST_ERR_SUCCESS;
}

// 2395: ARM PSA Lifecycle
/**
 * \brief Retrieve the security lifecycle of the device
 *
 * \note HUK is always available
 *
 * Security lifecycle is a mandatory claim in the initial attestation token.
 *
 * \return According to \ref tfm_security_lifecycle_t
 */
enum tfm_security_lifecycle_t sli_attest_hal_get_security_lifecycle(void)
{
  bool secure_boot_on = false;

  /// Debug lock options
  typedef struct {
    bool debug_port_lock;
    bool non_secure_invasive_lock;
    bool non_secure_non_invasive_lock;
    bool secure_invasive_lock;
    bool secure_non_invasive_lock;
  } debug_options_t;
  debug_options_t debug_options = { false };

  if (bootloader_exists()) {
    if (bootloader_secureBootEnforced() && otp_initialized && otp_configuration.enable_secure_boot) {
      secure_boot_on = true;
    }
  } else {
    if (otp_initialized && otp_configuration.enable_secure_boot) {
      secure_boot_on = true;
    }
  }

  #if defined(_SYSCFG_ROOTLOCKSTATUS_MASK)
  uint32_t syscfg_rootlock_status;

  #if defined(CMU_CLKEN0_SYSCFG)
  bool syscfg_clken_set = (bool)(CMU->CLKEN0 & CMU_CLKEN0_SYSCFG);
  if (!syscfg_clken_set) {
    CMU->CLKEN0_SET = CMU_CLKEN0_SYSCFG;
  }
  #endif
  syscfg_rootlock_status = SYSCFG->ROOTLOCKSTATUS;
  #if defined(CMU_CLKEN0_SYSCFG)
  if (!syscfg_clken_set) {
    CMU->CLKEN0_CLR = CMU_CLKEN0_SYSCFG;
  }
  #endif

  debug_options.debug_port_lock = (bool)(syscfg_rootlock_status & SYSCFG_ROOTLOCKSTATUS_USERDBGAPLOCK);
  debug_options.non_secure_invasive_lock = (bool)(syscfg_rootlock_status & SYSCFG_ROOTLOCKSTATUS_USERDBGLOCK);
  debug_options.non_secure_non_invasive_lock = (bool)(syscfg_rootlock_status & SYSCFG_ROOTLOCKSTATUS_USERNIDLOCK);
  debug_options.secure_invasive_lock = (bool)(syscfg_rootlock_status & SYSCFG_ROOTLOCKSTATUS_USERSPIDLOCK);
  debug_options.secure_non_invasive_lock = (bool)(syscfg_rootlock_status & SYSCFG_ROOTLOCKSTATUS_USERSPNIDLOCK);
  #else // _SYSCFG_ROOTLOCKSTATUS_MASK
  sl_se_command_context_t cmd_ctx = { 0 };
  sl_status_t status = sl_se_init_command_context(&cmd_ctx);
  if (status != SL_STATUS_OK) {
    return TFM_SLC_UNKNOWN;
  }
  sl_se_debug_status_t debug_lock_status = { 0 };
  status = sl_se_get_debug_lock_status(&cmd_ctx, &debug_lock_status);
  if (status != SL_STATUS_OK) {
    return TFM_SLC_UNKNOWN;
  }

  debug_options.debug_port_lock = debug_lock_status.debug_port_lock_state;   // true if locked
  debug_options.non_secure_invasive_lock = !(debug_lock_status.options_state.non_secure_invasive_debug);   // false if locked
  debug_options.non_secure_non_invasive_lock = !(debug_lock_status.options_state.non_secure_non_invasive_debug);   // false if locked
  debug_options.secure_invasive_lock = !(debug_lock_status.options_state.secure_invasive_debug);   // false if locked
  debug_options.secure_non_invasive_lock = !(debug_lock_status.options_state.secure_non_invasive_debug);   // false if locked
  #endif // _SYSCFG_ROOTLOCKSTATUS_MASK

  if (!secure_boot_on && !debug_options.debug_port_lock) {
    // Host debug port is open and SB is disabled
    return TFM_SLC_PSA_ROT_PROVISIONING;
  }

  if ((secure_boot_on && debug_options.debug_port_lock)
      || (secure_boot_on
          && debug_options.non_secure_invasive_lock
          && debug_options.non_secure_non_invasive_lock
          && debug_options.secure_invasive_lock
          && debug_options.secure_non_invasive_lock)) {
    // SB is on and all the debug access is disabled
    return TFM_SLC_SECURED;
  }

  if (secure_boot_on
      && debug_options.secure_invasive_lock
      && debug_options.secure_non_invasive_lock) {
    // Only the NS state debugging is allowed.
    return TFM_SLC_NON_PSA_ROT_DEBUG;
  }

  return TFM_SLC_UNKNOWN;
}

// 2396: ARM PSA Implementation ID
/**
 * \brief Get the Implementation ID of the device.
 *
 * This mandatory claim represents the original implementation signer of the
 * attestation key and identifies the contract between the report and
 * verification. A verification service will use this claim to locate the
 * details of the verification process. The claim will be represented by a
 * custom EAT claim with a value consisting of a CBOR byte string. The size of
 * this string will normally be 32 bytes to accommodate a 256 bit hash.
 *
 * \param[in/out] size  As an input value it indicates the size of the caller
 *                      allocated buffer (in bytes) to store the implementation
 *                      ID. At return its value is updated with the exact size
 *                      of the implementation ID.
 * \param[out]    implementation_id   Pointer to the buffer to store the implementation ID
 *
 * \return  Returns error code specified in \ref tfm_plat_err_t
 */
enum tfm_plat_err_t sli_plat_get_implementation_id(uint32_t *size,
                                                   uint32_t implementation_id[8u],
                                                   size_t   implementation_id_size)
{
  if (implementation_id_size != IMPLEMENTATION_ID_SIZE) {
    return TFM_PLAT_ERR_INVALID_INPUT;
  }
  // ChipRevHW contains die family, major and minor die revision.
  #if defined(CMU_CLKEN0_SYSCFG)
  bool syscfg_clken_set = (bool)(CMU->CLKEN0 & CMU_CLKEN0_SYSCFG);
  if (!syscfg_clken_set) {
    CMU->CLKEN0_SET = CMU_CLKEN0_SYSCFG;
  }
  #endif
  implementation_id[0] = SYSCFG->CHIPREVHW;
  #if defined(CMU_CLKEN0_SYSCFG)
  if (!syscfg_clken_set) {
    CMU->CLKEN0_CLR = CMU_CLKEN0_SYSCFG;
  }
  #endif

  // SE bootloader OTP version.
  implementation_id[1] = otp_version;

  // Family security capability.
  implementation_id[2] = (uint32_t)SYSTEM_GetSecurityCapability();

  // Add PTE production version.
  implementation_id[3] = (DEVINFO->PART & _DEVINFO_PART_DEVICENUM_MASK);
  implementation_id[3] |= (DEVINFO->INFO & _DEVINFO_INFO_PRODREV_MASK);

  // implementation_id[4:7] is set to zeros.
  memset(&implementation_id[4], 0u, sizeof(uint32_t) * 4u);

  *size = IMPLEMENTATION_ID_SIZE;

  return TFM_PLAT_ERR_SUCCESS;
}

// 2397: ARM PSA boot seed
/**
 * \brief Gets the boot seed, which is a constant random number during a boot
 *        cycle.
 *
 * \param[in]  size The required size of boot seed in bytes
 * \param[out] buf  Pointer to the buffer to store boot seed
 *
 * \return  TFM_PLAT_ERR_SUCCESS if the value is generated correctly. Otherwise,
 *          it returns TFM_PLAT_ERR_SYSTEM_ERR.
 */
enum tfm_plat_err_t sli_plat_get_boot_seed(uint32_t size, uint8_t *buf)
{
  if (size > sizeof(boot_seed)) {
    return TFM_PLAT_ERR_INVALID_INPUT;
  }
  if (!bood_seed_generated) {
    psa_status_t status = psa_generate_random(boot_seed, sizeof(boot_seed));
    if (status != PSA_SUCCESS) {
      return TFM_PLAT_ERR_SYSTEM_ERR;
    }
    bood_seed_generated = true;
  }
  memcpy(buf, boot_seed, size);

  return TFM_PLAT_ERR_SUCCESS;
}

// 265: ARM PSA Profile ID
/**
 * \brief Get the profile definition claim that encode the unique
 *        identifier that corresponds to the EAT profile
 *
 * \param[out] size The size of the profile ID
 * \param[out] buf  Pointer to the buffer to store the profile ID
 *
 * \return  TFM_PLAT_ERR_SUCCESS if the profile ID is set correctly. Otherwise,
 *          it returns TFM_PLAT_ERR_SYSTEM_ERR.
 */
enum tfm_plat_err_t sli_attest_hal_get_profile_definition(uint32_t *size, uint8_t *buf)
{
  if (sizeof(profile_id_psa) > VERIFICATION_URL_MAX_SIZE) {
    return TFM_PLAT_ERR_SYSTEM_ERR;
  }

  *size = sizeof(profile_id_psa);
  memcpy(buf, profile_id_psa, *size);

  return TFM_PLAT_ERR_SUCCESS;
}

// 2399: ARM PSA SW Components
/*!
 * \brief Static function to add the claims of all SW components to the
 *        attestation token.
 *
 * \param[in]  token_ctx  Token encoding context
 *
 * \return Returns error code as specified in \ref psa_attest_err_t
 */
enum psa_attest_err_t sli_attest_add_all_sw_components(struct attest_token_encode_ctx *token_ctx)
{
  bool bootloader_is_present = bootloader_exists();
  if (!otp_initialized || !otp_configuration.enable_secure_boot) {
    // Secure boot is not enabled.
    return PSA_ATTEST_ERR_CLAIM_UNAVAILABLE;
  }
  if (bootloader_is_present && !bootloader_secureBootEnforced()) {
    // Bootloader is present, but the bootloader does not enforce
    // secure boot.
    return PSA_ATTEST_ERR_CLAIM_UNAVAILABLE;
  }

  enum psa_attest_err_t ret_val = PSA_ATTEST_ERR_GENERAL;
  uint32_t firmware_start_addr = (uint32_t)&linker_vectors_begin;
  QCBOREncodeContext *encoding_ctx = &(token_ctx->cbor_enc_ctx);

  // After this line, always use goto after setting the proper
  // return value.
  QCBOREncode_OpenArrayInMapN(encoding_ctx,
                              EAT_CBOR_ARM_LABEL_SW_COMPONENTS);

  if (bootloader_is_present) {
    ApplicationProperties_t *bl_app_properties
      = (ApplicationProperties_t *)get_application_properties_struct_addr(FLASH_BASE);

    uint32_t bl_start_addr = FLASH_BASE; // assume the bootloader to be here.
    uint32_t bl_end_addr = (uint32_t)bl_app_properties->signatureLocation;
    if (!validate_signature_location(bl_start_addr, bl_end_addr)) {
      ret_val = PSA_ATTEST_ERR_CLAIM_UNAVAILABLE;
      goto exit;
    }
    size_t bl_size = bl_end_addr - bl_start_addr;

    uint8_t hash_buffer[TZ_ATTESTATION_SHA256_DIGESTSIZE] = { 0 };
    size_t out_hash_length = 0u;
    psa_status_t status = generate_firmware_hash((uint8_t *)bl_start_addr,
                                                 bl_size,
                                                 hash_buffer,
                                                 &out_hash_length);
    if (status != PSA_SUCCESS || out_hash_length != TZ_ATTESTATION_SHA256_DIGESTSIZE) {
      ret_val = PSA_ATTEST_ERR_GENERAL;
      goto exit;
    }

    if (check_application_properties_magic(bl_app_properties)
        && (bl_app_properties->app.type == APPLICATION_TYPE_BOOTLOADER)) {
      QCBOREncode_OpenMap(encoding_ctx);

      // Add measurement type.
      UsefulBufC measurement_type_data = {
        measurement_type_bl,
        sizeof(measurement_type_bl)
      };
      QCBOREncode_AddTextToMapN(encoding_ctx,
                                EAT_CBOR_SW_COMPONENT_MEASUREMENT_TYPE,
                                measurement_type_data);
      // Add component version.
      uint8_t component_version_string[8] = { 0 };
      version_to_string(component_version_string,
                        bl_app_properties->app.version);
      UsefulBufC component_version_data = {
        component_version_string,
        sizeof(component_version_string)
      };

      QCBOREncode_AddTextToMapN(encoding_ctx,
                                EAT_CBOR_SW_COMPONENT_VERSION,
                                component_version_data);

      // Add measurement value: SHA-256 hash
      UsefulBufC hash_data = { hash_buffer, sizeof(hash_buffer) };
      QCBOREncode_AddBytesToMapN(encoding_ctx,
                                 EAT_CBOR_SW_COMPONENT_MEASUREMENT_VALUE,
                                 hash_data);

      QCBOREncode_CloseMap(encoding_ctx);

      ret_val = PSA_ATTEST_ERR_SUCCESS;
    }
  }

  // Add measurement for the secure code.
  {
    uint32_t firmware_end_addr = FIRMWARE_END;
    if (!validate_signature_location(firmware_start_addr, firmware_end_addr)) {
      ret_val = PSA_ATTEST_ERR_CLAIM_UNAVAILABLE;
      goto exit;
    }
    size_t firmware_size = firmware_end_addr - firmware_start_addr;

    // Compute SHA-256 hash of the firmware
    uint8_t hash_buffer[TZ_ATTESTATION_SHA256_DIGESTSIZE] = { 0 };
    size_t out_hash_length = 0u;
    psa_status_t status = generate_firmware_hash((uint8_t *)firmware_start_addr,
                                                 firmware_size,
                                                 hash_buffer,
                                                 &out_hash_length);
    if (status != PSA_SUCCESS || out_hash_length != TZ_ATTESTATION_SHA256_DIGESTSIZE) {
      ret_val = PSA_ATTEST_ERR_GENERAL;
      goto exit;
    }

    QCBOREncode_OpenMap(encoding_ctx);

    // Add measurement type.
    UsefulBufC measurement_type_data = {
      measurement_type_prot,
      sizeof(measurement_type_prot)
    };
    QCBOREncode_AddTextToMapN(encoding_ctx,
                              EAT_CBOR_SW_COMPONENT_MEASUREMENT_TYPE,
                              measurement_type_data);

    // Add component version.
    uint8_t component_version_string[8] = { 0 };
    version_to_string(component_version_string,
                      sl_app_properties.app.version);
    UsefulBufC component_version_data = {
      component_version_string,
      sizeof(component_version_string)
    };
    QCBOREncode_AddTextToMapN(encoding_ctx,
                              EAT_CBOR_SW_COMPONENT_VERSION,
                              component_version_data);

    // Add measurement value: SHA-256 hash
    UsefulBufC hash_data = { hash_buffer, sizeof(hash_buffer) };
    QCBOREncode_AddBytesToMapN(encoding_ctx,
                               EAT_CBOR_SW_COMPONENT_MEASUREMENT_VALUE,
                               hash_data);

    QCBOREncode_CloseMap(encoding_ctx);

    ret_val = PSA_ATTEST_ERR_SUCCESS;
  }

  // Add measurement for the non-secure code.
  {
    uint32_t ns_firmware_start_addr = TZ_NS_FLASH_START;
    // S and NS blob is merged and has a single signature
    // if the above checks indicated that secure boot is enabled,
    // the application properties struct will contain a pointer which points
    // to the address at the end of the NS application.
    uint32_t ns_firmware_end_addr = (uint32_t)sl_app_properties.signatureLocation;
    if (!validate_signature_location(ns_firmware_start_addr, ns_firmware_end_addr)) {
      return PSA_ATTEST_ERR_CLAIM_UNAVAILABLE;
    }
    size_t ns_firmware_size = ns_firmware_end_addr - ns_firmware_start_addr;

    // Compute SHA-256 hash of the firmware
    uint8_t hash_buffer[TZ_ATTESTATION_SHA256_DIGESTSIZE] = { 0 };
    size_t out_hash_length = 0u;
    psa_status_t status = generate_firmware_hash((uint8_t *)ns_firmware_start_addr,
                                                 ns_firmware_size,
                                                 hash_buffer,
                                                 &out_hash_length);
    if (status != PSA_SUCCESS || out_hash_length != TZ_ATTESTATION_SHA256_DIGESTSIZE) {
      ret_val = PSA_ATTEST_ERR_GENERAL;
      goto exit;
    }

    QCBOREncode_OpenMap(encoding_ctx);

    // Add measurement type.
    UsefulBufC measurement_type_data = {
      measurement_type_app,
      sizeof(measurement_type_app)
    };
    QCBOREncode_AddTextToMapN(encoding_ctx,
                              EAT_CBOR_SW_COMPONENT_MEASUREMENT_TYPE,
                              measurement_type_data);

    // Get the version of NS application by finding the application properties.
    uint32_t ns_version = 0u;
    ApplicationProperties_t *ns_app_properties =
      (ApplicationProperties_t *)get_application_properties_struct_addr(ns_firmware_start_addr);
    if (check_application_properties_magic(ns_app_properties)) {
      ns_version = ns_app_properties->app.version;
    }

    // Add component version.
    uint8_t component_version_string[8] = { 0 };
    version_to_string(component_version_string,
                      ns_version);
    UsefulBufC component_version_data = {
      component_version_string,
      sizeof(component_version_string)
    };
    QCBOREncode_AddTextToMapN(encoding_ctx,
                              EAT_CBOR_SW_COMPONENT_VERSION,
                              component_version_data);

    // Add measurement value: SHA-256 hash
    UsefulBufC hash_data = { hash_buffer, sizeof(hash_buffer) };
    QCBOREncode_AddBytesToMapN(encoding_ctx,
                               EAT_CBOR_SW_COMPONENT_MEASUREMENT_VALUE,
                               hash_data);

    QCBOREncode_CloseMap(encoding_ctx);

    ret_val = PSA_ATTEST_ERR_SUCCESS;
  }

  exit:
  QCBOREncode_CloseArray(encoding_ctx);
  return ret_val;
}

#endif // (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)

//-------------------------------------
// Full services (IOVEC usage)

/**************************************************************************//**
 * @brief Get attestation public key.
 *****************************************************************************/
psa_status_t sli_tz_attestation_get_public_key(psa_invec in_vec[],
                                               size_t in_len,
                                               psa_outvec out_vec[],
                                               size_t out_len)
{
  (void)in_vec;
  // in vec stores the function ID
  // out vec stores the buffer to output the key
  SLI_TZ_IOVEC_ASSERT_N_IOVECS(1, 1);

  uint8_t *out_buffer = out_vec[0].base;
  size_t out_buffer_size = out_vec[0].len;

  return get_attestation_get_public_key(out_buffer,
                                        out_buffer_size);
}

#if (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)

/**************************************************************************//**
 * @brief Get IAT attestation token.
 *****************************************************************************/
psa_status_t sli_initial_attest_get_token(psa_invec in_vec[],
                                          size_t in_len,
                                          psa_outvec out_vec[],
                                          size_t out_len)
{
  return initial_attest_get_token((const psa_invec *)in_vec,
                                  in_len,
                                  out_vec,
                                  out_len);
}

/**************************************************************************//**
 * @brief Get IAT attestation token size.
 *****************************************************************************/
psa_status_t sli_initial_attest_get_token_size(psa_invec in_vec[],
                                               size_t in_len,
                                               psa_outvec out_vec[],
                                               size_t out_len)
{
  return initial_attest_get_token_size((const psa_invec *)in_vec,
                                       in_len,
                                       out_vec,
                                       out_len);
}

#else // (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)

/**************************************************************************//**
 * @brief Get IAT attestation token.
 *****************************************************************************/
psa_status_t sli_initial_attest_get_token(psa_invec in_vec[],
                                          size_t in_len,
                                          psa_outvec out_vec[],
                                          size_t out_len)
{
  (void)in_len;
  (void)out_len;

  const uint8_t *auth_challenge = in_vec[1].base;
  size_t challenge_size = in_vec[1].len;
  uint8_t *token_buf = out_vec[0].base;
  size_t token_buf_size = out_vec[0].len;
  size_t token_size = 0u;

  sl_se_command_context_t cmd_ctx = { 0 };
  sl_status_t status = sl_se_init_command_context(&cmd_ctx);
  if (status != SL_STATUS_OK) {
    return error_mapping_sl_status_to_psa_status(status);
  }
  status = sl_se_attestation_get_psa_iat_token(&cmd_ctx,
                                               auth_challenge,
                                               challenge_size,
                                               token_buf,
                                               token_buf_size,
                                               &token_size);

  return error_mapping_sl_status_to_psa_status(status);
}

/**************************************************************************//**
 * @brief Get IAT attestation token size.
 *****************************************************************************/
psa_status_t sli_initial_attest_get_token_size(psa_invec in_vec[],
                                               size_t in_len,
                                               psa_outvec out_vec[],
                                               size_t out_len)
{
  (void)in_len;
  (void)out_len;

  size_t challenge_size = *(size_t *)in_vec[1].base;
  size_t *token_buf_size = (size_t *)out_vec[0].base;

  sl_se_command_context_t cmd_ctx = { 0 };
  sl_status_t status = sl_se_init_command_context(&cmd_ctx);
  if (status != SL_STATUS_OK) {
    return error_mapping_sl_status_to_psa_status(status);
  }
  status = sl_se_attestation_get_psa_iat_token_size(&cmd_ctx,
                                                    challenge_size,
                                                    token_buf_size);

  return error_mapping_sl_status_to_psa_status(status);
}

#endif // (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)
