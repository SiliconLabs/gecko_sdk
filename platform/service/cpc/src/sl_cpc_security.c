/***************************************************************************/ /**
 * @file
 * @brief CPC Security Endpoint API implementation.
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "psa/crypto.h"
#include "psa/crypto_sizes.h"

#include "sl_cpc.h"
#include "sli_cpc.h"
#include "sl_cpc_security.h"
#include "sl_atomic.h"

#define SLI_CPC_SECURITY_PSA_CRYPTO_BINDING_KEY_ID 0x00004200

static uint32_t security_state = 0;

#if (SL_CPC_ENDPOINT_SECURITY_ENABLED >= 1)
#if (defined(SLI_CPC_DEVICE_UNDER_TEST))
bool security_endpoint_initialized = false;
sl_cpc_endpoint_handle_t security_ep;
#else
static sl_cpc_endpoint_handle_t security_ep;
#endif
static sl_cpc_security_protocol_cmd_t security_protocol_response;
static sl_cpc_security_protocol_cmd_t security_protocol_request;
static bool security_write_completed = true;
static bool security_request_pending = false;
static bool security_endpoint_in_error = false;

static bool is_bound = false;
static psa_key_id_t session_key_id;
static const psa_key_id_t binding_key_id = SLI_CPC_SECURITY_PSA_CRYPTO_BINDING_KEY_ID;
static uint8_t session_id_primary[SLI_SECURITY_SESSION_ID_LENGTH_BYTES] = { 0 };
static uint8_t session_id_secondary[SLI_SECURITY_SESSION_ID_LENGTH_BYTES] = { 0 };

const sl_cpc_security_protocol_cmd_info_t sli_cpc_security_command[] = {
  [BINDING_REQUEST_ID] =  {
    .request_len = sizeof(sl_cpc_security_binding_key_method_t),
    .response_len = sizeof(sl_status_t),
    .command_id = BINDING_REQUEST_ID
  },
  [PLAIN_TEXT_KEY_SHARE_ID] =  {
    .request_len = SLI_SECURITY_BINDING_KEY_LENGTH_BYTES,
    .response_len = sizeof(sl_status_t),
    .command_id = PLAIN_TEXT_KEY_SHARE_ID
  },
  [PUBLIC_KEY_SHARE_ID] =  {
    .request_len = SLI_SECURITY_PUBLIC_KEY_LENGTH_BYTES,
    .response_len = sizeof(sl_status_t) + SLI_SECURITY_PUBLIC_KEY_LENGTH_BYTES,
    .command_id = PUBLIC_KEY_SHARE_ID
  },
  [SESSION_INIT_ID] =  {
    .request_len = SLI_SECURITY_SESSION_INIT_RANDOM_LENGTH_BYTES,
    .response_len = sizeof(sl_status_t) + SLI_SECURITY_SESSION_INIT_RANDOM_LENGTH_BYTES,
    .command_id = SESSION_INIT_ID
  },
  [UNBIND_REQUEST_ID] =  {
    .request_len = 0x0000,
    .response_len = sizeof(sl_status_t),
    .command_id = UNBIND_REQUEST_ID
  },
};

#endif

uint32_t sl_cpc_security_get_state(void)
{
  uint32_t local_security_state;

  sl_atomic_load(local_security_state, security_state);

  return local_security_state;
}

#if (SL_CPC_ENDPOINT_SECURITY_ENABLED >= 1)

sl_status_t sli_cpc_security_store_binding_key(uint8_t *key, uint16_t key_size);
sl_status_t security_initialize_session(uint8_t *random1, uint8_t *random2);
sl_status_t sli_cpc_security_erase_binding_key(void);

__WEAK void sl_cpc_security_fetch_user_specified_binding_key(uint8_t **key, uint16_t *key_size_in_bytes)
{
  (void)key;
  (void)key_size_in_bytes;
  EFM_ASSERT(0); // User must provide the binding key by overriding this function
}

static void on_security_error(uint8_t endpoint_id, void *arg)
{
  (void)arg;

  EFM_ASSERT(endpoint_id == SL_CPC_ENDPOINT_SECURITY);

  if (sl_cpc_get_endpoint_state(&security_ep) != SL_CPC_STATE_OPEN) {
    security_endpoint_in_error = true;
  }
}

static void on_security_write_completed(sl_cpc_user_endpoint_id_t endpoint_id,
                                        void *buffer, void *arg, sl_status_t status)
{
  (void) endpoint_id;
  (void) arg;
  (void) buffer;

  EFM_ASSERT(endpoint_id == SL_CPC_ENDPOINT_SECURITY);

  if (status != SL_STATUS_OK) {
    security_endpoint_in_error = true;
  }

  security_write_completed = true;
}

static bool cmd_is_a_response(sl_cpc_security_protocol_cmd_t *cmd)
{
  if (cmd->command_id & SLI_CPC_SECURITY_PROTOCOL_RESPONSE_MASK) {
    return true;
  }
  return false;
}

static void send_request(sl_cpc_security_protocol_cmd_t *request)
{
  EFM_ASSERT(security_write_completed == true);
  security_write_completed = false;

  sl_cpc_write(&security_ep, request,
               request->len + SLI_SECURITY_PROTOCOL_HEADER_LENGTH,
               0, on_security_write_completed);
}

static void send_response(sl_cpc_security_protocol_cmd_t *response)
{
  EFM_ASSERT(security_write_completed == true);
  security_write_completed = false;

  sl_cpc_write(&security_ep, response,
               response->len + SLI_SECURITY_PROTOCOL_HEADER_LENGTH,
               0, on_security_write_completed);
}

static void on_binding_cmd(sl_cpc_security_protocol_cmd_t *cmd)
{
  uint8_t binding_type;
  sl_status_t status;

  binding_type = cmd->payload[0];
  security_protocol_response.len = sli_cpc_security_command[BINDING_REQUEST_ID].response_len;
  security_protocol_response.command_id = cmd->command_id | SLI_CPC_SECURITY_PROTOCOL_RESPONSE_MASK;

  if (is_bound) {
    status = SL_STATUS_ALREADY_INITIALIZED;
  } else {
    switch (binding_type) {
      case SLI_CPC_SECURITY_BINDING_TYPE_PLAINTEXT:
#if (SL_CPC_SECURITY_BINDING_KEY_METHOD == SL_CPC_SECURITY_BINDING_KEY_PLAINTEXT_SHARE)
        status = SL_STATUS_OK;
#else
        status = SL_STATUS_INVALID_MODE;
#endif
        break;
      case SLI_CPC_SECURITY_BINDING_TYPE_ECDH:
#if (SL_CPC_SECURITY_BINDING_KEY_METHOD == SLI_CPC_SECURITY_BINDING_TYPE_ECDH)
        status = SL_STATUS_OK;
#else
        status = SL_STATUS_INVALID_MODE;
#endif
        break;
      default:
        status = SL_STATUS_INVALID_MODE;
        break;
    }
  }

  memcpy(&security_protocol_response.payload, &status, sizeof(status));
  send_response(&security_protocol_response);
}

static void on_plaintext_key_share_cmd(sl_cpc_security_protocol_cmd_t *cmd)
{
  sl_status_t status = SL_STATUS_FAIL;

#if (SL_CPC_SECURITY_BINDING_KEY_METHOD == SL_CPC_SECURITY_BINDING_KEY_PLAINTEXT_SHARE)
  status = sli_cpc_security_store_binding_key(cmd->payload, SLI_SECURITY_BINDING_KEY_LENGTH_BYTES);
#else
  status = SL_STATUS_INVALID_MODE;
#endif

  security_protocol_response.len = sli_cpc_security_command[cmd->command_id].response_len;
  security_protocol_response.command_id = cmd->command_id | SLI_CPC_SECURITY_PROTOCOL_RESPONSE_MASK;
  memcpy(&security_protocol_response.payload, &status, sizeof(status));
  send_response(&security_protocol_response);
}

static void on_public_key_share_cmd(sl_cpc_security_protocol_cmd_t *cmd)
{
  sl_status_t status = SL_STATUS_NOT_SUPPORTED;

  security_protocol_response.len = sli_cpc_security_command[cmd->command_id].response_len;
  security_protocol_response.command_id = cmd->command_id | SLI_CPC_SECURITY_PROTOCOL_RESPONSE_MASK;
  memcpy(&security_protocol_response.payload, &status, sizeof(status));
  send_response(&security_protocol_response);
}

static void on_session_init_cmd(sl_cpc_security_protocol_cmd_t *cmd)
{
  session_init_response_t *response = (session_init_response_t*)security_protocol_response.payload;

  if (is_bound) {
    response->status = security_initialize_session(cmd->payload, response->random2);
  } else {
    response->status = SL_STATUS_NOT_INITIALIZED;
    //Just to be pedantic and not leak anything
    mbedtls_platform_zeroize(response->random2, sizeof(response->random2));
  }

  security_protocol_response.len = sli_cpc_security_command[cmd->command_id].response_len;
  security_protocol_response.command_id = cmd->command_id | SLI_CPC_SECURITY_PROTOCOL_RESPONSE_MASK;
  send_response(&security_protocol_response);
}

// TODO: This is only the basic behavior, improvements are required PLATFORM_MTL-5111
// -> Improvements made in Feature/PLATFORM MTL-3936 with the flag 'is_bound'
static void on_unbind_cmd(sl_cpc_security_protocol_cmd_t *cmd)
{
  sl_status_t status;

  status = sli_cpc_security_erase_binding_key();

  security_protocol_response.len = sli_cpc_security_command[cmd->command_id].response_len;
  security_protocol_response.command_id = cmd->command_id | SLI_CPC_SECURITY_PROTOCOL_RESPONSE_MASK;
  memcpy(&security_protocol_response.payload, &status, sizeof(status));
  send_response(&security_protocol_response);
}

static void process_security_command_rx(sl_cpc_security_protocol_cmd_t *cmd)
{
  if (cmd_is_a_response(cmd)) {
    EFM_ASSERT(0); // Should not receive a response, only requests are allowed
  }

  EFM_ASSERT(cmd->command_id >= BINDING_REQUEST_ID && cmd->command_id <= UNBIND_REQUEST_ID);
  EFM_ASSERT(cmd->len == sli_cpc_security_command[cmd->command_id].request_len);

  // Check if the command is a response or a request
  switch (cmd->command_id) {
    case BINDING_REQUEST_ID:
      on_binding_cmd(cmd);
      break;
    case PLAIN_TEXT_KEY_SHARE_ID:
      on_plaintext_key_share_cmd(cmd);
      break;
    case PUBLIC_KEY_SHARE_ID:
      on_public_key_share_cmd(cmd);
      break;
    case SESSION_INIT_ID:
      on_session_init_cmd(cmd);
      break;
    case UNBIND_REQUEST_ID:
      on_unbind_cmd(cmd);
      break;
    default:
      EFM_ASSERT(0); // Unknown command
  }
}

/***************************************************************************//**
 * Security endpoint open function, will return false if endpoint is busy (CLOSING)
 ******************************************************************************/
static bool security_open_endpoint(void)
{
  sl_status_t status;

  status = sli_cpc_open_security_endpoint(&security_ep, 0x00, 1);
  if (status == SL_STATUS_BUSY) {
    return false;
  }
  EFM_ASSERT(status == SL_STATUS_OK);

  status = sl_cpc_set_endpoint_option(&security_ep,
                                      SL_CPC_ENDPOINT_ON_IFRAME_WRITE_COMPLETED,
                                      on_security_write_completed);
  EFM_ASSERT(status == SL_STATUS_OK);

  status = sl_cpc_set_endpoint_option(&security_ep, SL_CPC_ENDPOINT_ON_ERROR, (void *)on_security_error);
  EFM_ASSERT(status == SL_STATUS_OK);

  return true;
}

static void security_recover_endpoint(void)
{
  EFM_ASSERT(SL_STATUS_OK == sl_cpc_close_endpoint(&security_ep));

  if (security_open_endpoint()) {
    security_write_completed = true;
    security_endpoint_in_error = false;
  }
}

sl_status_t sli_cpc_security_store_binding_key(uint8_t *key, uint16_t key_size)
{
  if (key == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  if (key_size != SLI_SECURITY_BINDING_KEY_LENGTH_BYTES) {
    // Only 128-bits key is supported
    return SL_STATUS_NOT_SUPPORTED;
  }

  if (is_bound) {
    return SL_STATUS_ALREADY_INITIALIZED;
  }

/* TODO This macro is missing from psa_crypto in crypto_values.h. It will be added when this
 * PR is merged : https://github.com/ARMmbed/mbedtls/pull/4966/commits/fa78f2422328295ff622bd4e9af9c638e3cede44
 * It will likely lead to a warning as error when redefined as it finds its way here. */
#define PSA_ALG_NONE ((psa_algorithm_t)0)

  // Set key attributes.
  psa_key_attributes_t attr = psa_key_attributes_init();
  psa_set_key_algorithm(&attr, PSA_ALG_NONE);
  psa_set_key_usage_flags(&attr, PSA_KEY_USAGE_EXPORT);
  psa_set_key_type(&attr, PSA_KEY_TYPE_RAW_DATA);
  psa_set_key_bits(&attr, PSA_BYTES_TO_BITS(SLI_SECURITY_BINDING_KEY_LENGTH_BYTES));
  psa_set_key_id(&attr, binding_key_id);
  psa_set_key_lifetime(&attr, PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(
                         PSA_KEY_LIFETIME_PERSISTENT, PSA_KEY_LOCATION_LOCAL_STORAGE));

  // Import key.
  psa_key_id_t key_id;
  psa_status_t psa_status = psa_import_key(&attr,
                                           key,
                                           SLI_SECURITY_BINDING_KEY_LENGTH_BYTES,
                                           &key_id);

  // The key is expected to be in RAM, we need to squash it now that it's loaded in the SE
  mbedtls_platform_zeroize(key, key_size);

#if (defined(SLI_CPC_DEVICE_UNDER_TEST))
  security_endpoint_initialized = true;
#endif

  //Big logic corruption with is_bound flash if the key already exists
  EFM_ASSERT(psa_status != PSA_ERROR_ALREADY_EXISTS);

  // Output result.
  if (psa_status == PSA_SUCCESS) {
    /* When registering a persistent key, the returned key_id should be equal to
     * the one set with psa_set_key_id. Something is terribly wrong if it isn't */
    EFM_ASSERT(key_id == binding_key_id);
    is_bound = true;
    return SL_STATUS_OK;
  } else {
    return SL_STATUS_FAIL;
  }
}

sl_status_t sli_cpc_security_erase_binding_key(void)
{
  //Check if the key is already erased
  if (psa_is_key_present_in_storage(binding_key_id) == 0) {
    //Just a sanity check to make sure 'is_bound' flag is consistent with the key status
    EFM_ASSERT(is_bound == false);
    return (sl_status_t) SL_STATUS_NOT_INITIALIZED;
  }

  if (psa_destroy_persistent_key(binding_key_id) != PSA_SUCCESS) {
    return (sl_status_t)SL_STATUS_FAIL;
  }

  //Just a confirmation
  if (psa_is_key_present_in_storage(binding_key_id) == 1) {
    return (sl_status_t)SL_STATUS_FAIL;
  }

  is_bound = false;
  return (sl_status_t)SL_STATUS_OK;
}

sl_status_t security_initialize_session(uint8_t *random1, uint8_t *random2)
{
  psa_status_t psa_status;
  const size_t half_random_len = SLI_SECURITY_SESSION_INIT_RANDOM_LENGTH_BYTES / 2;
  uint8_t random3[SLI_SECURITY_SESSION_INIT_RANDOM_LENGTH_BYTES];
  uint8_t sha256_random3[SLI_SECURITY_SHA256_LENGTH_BYTES];
  uint8_t random4[2 * half_random_len + SLI_SECURITY_BINDING_KEY_LENGTH_BYTES];
  uint8_t tmp_session_key[SLI_SECURITY_SESSION_KEY_LENGTH_BYTES] = { 0 };

  /* Generate Session ID and Session Key */
  {
    /* Both devices will construct a string of bits:  Rand-3 = Rand-1[0:255] || Rand-2[0:255] */
    {
      /* random1 is generated by the primary and supplied to us */
      memcpy(&random3[0],
             random1,
             half_random_len);

#if (defined(SLI_CPC_DEVICE_UNDER_TEST))
      //When testing, we need a known random number to assert on the testint side
      size_t i;
      for (i = 0; i != SLI_SECURITY_SESSION_INIT_RANDOM_LENGTH_BYTES; i++) {
        random2[i] = i;
      }
#else
      /* random2 is generated by the secondary. */
      psa_status = psa_generate_random(random2,
                                       SLI_SECURITY_SESSION_INIT_RANDOM_LENGTH_BYTES);
      if (psa_status != PSA_SUCCESS) {
        return SL_STATUS_FAIL;
      }
#endif

      memcpy(&random3[half_random_len],
             random2,
             half_random_len);
    }

    /* Both devices will perform SHA256 on Rand-3. */
    {
      size_t hash_length;

      psa_status = psa_hash_compute(PSA_ALG_SHA_256,
                                    random3,
                                    sizeof(random3),
                                    sha256_random3,
                                    sizeof(sha256_random3),
                                    &hash_length);

      EFM_ASSERT(hash_length == sizeof(sha256_random3));

      if (psa_status != PSA_SUCCESS) {
        return SL_STATUS_FAIL;
      }
    }

    /* The resulting 32-byte number will be split into two 8-byte values as follows: Result = Session-ID-Host || Session-ID-NCP || Discarded data */
    {
      memcpy(session_id_primary,
             &sha256_random3[0],
             SLI_SECURITY_SESSION_ID_LENGTH_BYTES);

      memcpy(session_id_secondary,
             &sha256_random3[SLI_SECURITY_SESSION_ID_LENGTH_BYTES],
             SLI_SECURITY_SESSION_ID_LENGTH_BYTES);
    }

    /* To generate the session key a second string of bits is constructed:
    * Rand-4 = Rand-1[256:511] || Rand-2[256:511] || Binding Key[0:128] */
    {
      size_t key_length;

      //Rand-4 = Rand-1[256:511]
      memcpy(&random4[0],
             &random1[half_random_len],
             half_random_len);

      //Rand-4 = || Rand-2[256:511]
      memcpy(&random4[half_random_len],
             &random2[half_random_len],
             half_random_len);

      //Rand-4 = || Binding Key[0:128]
      psa_status = psa_export_key(binding_key_id,
                                  &random4[2 * half_random_len], //
                                  SLI_SECURITY_BINDING_KEY_LENGTH_BYTES,
                                  &key_length);

      /* Something terribly wrong if the retrived binding key length is not the
       * same as the one when it was stored */
      EFM_ASSERT(key_length == SLI_SECURITY_BINDING_KEY_LENGTH_BYTES);

      if (psa_status != PSA_SUCCESS) {
        /* If for whatever reason the export failed, squash random4 anyway */
        mbedtls_platform_zeroize(random4, sizeof(random4));
        return SL_STATUS_FAIL;
      }
    }

    /* Both devices perform SHA256 on RAND-4 */
    {
      size_t hash_length;

      psa_status = psa_hash_compute(PSA_ALG_SHA_256,
                                    random4,
                                    sizeof(random4),
                                    tmp_session_key,
                                    sizeof(tmp_session_key),
                                    &hash_length);

      /* Squash the random4 containing the binding key in plain text now that its
       * hash has been computed */
      mbedtls_platform_zeroize(random4, sizeof(random4));

      /* Something is terribly wrong if sha256 doesn't give a 256 length (session key length) */
      EFM_ASSERT(hash_length == SLI_SECURITY_SESSION_KEY_LENGTH_BYTES);

      if (psa_status != PSA_SUCCESS) {
        /* If for whatever reason the hash failed, squash tmp_session_key anyway */
        mbedtls_platform_zeroize(tmp_session_key, sizeof(tmp_session_key));
        return SL_STATUS_FAIL;
      }
    }

    /* The resulting 256 bit number is then used as the session key */
    {
      // Set key attributes.
      psa_key_attributes_t attr = psa_key_attributes_init();
      psa_set_key_algorithm(&attr, PSA_ALG_GCM);
      psa_set_key_usage_flags(&attr, PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT);
      psa_set_key_type(&attr, PSA_KEY_TYPE_AES);
      psa_set_key_bits(&attr, PSA_BYTES_TO_BITS(sizeof(tmp_session_key)));
      /* psa_set_key_id() is not used because it is a volatile key, and using it
       * would implicitly mark it as persistent. psa_import_key will assign us
       * a key_id  */
      psa_set_key_lifetime(&attr, PSA_KEY_LIFETIME_VOLATILE);

      /* Create the key and retrieve its key_id in session_key_id. */
      psa_status_t status = psa_import_key(&attr,
                                           tmp_session_key,
                                           sizeof(tmp_session_key),
                                           &session_key_id);

      /* Squash the session_key temp buffer now that it is managed by psa_crypto */
      mbedtls_platform_zeroize(tmp_session_key, sizeof(tmp_session_key));

      if (status != PSA_SUCCESS) {
        return SL_STATUS_FAIL;
      }
    }
  }

  /* Initialize the nonce */
  {
    //TODO in PLATFORM_MTL-5106
  }

  return SL_STATUS_OK;
}

void sli_cpc_security_process(void)
{
  sl_status_t status;
  void *read_buffer;
  uint16_t size;

#if (defined(SLI_CPC_DEVICE_UNDER_TEST))
  if (security_endpoint_initialized == false) {
    return;
  }
#endif

  sl_cpc_security_protocol_cmd_t *rx_security_cmd;

  // Recover the security endpoint if it failed
  if (security_endpoint_in_error) {
    security_recover_endpoint();
    if (security_endpoint_in_error) {
      return; // Could not recover the security endpoint retry the process later on
    }
  }

  if (security_write_completed == true) {
    status = sl_cpc_read(&security_ep, &read_buffer, &size, 0u, SL_CPC_FLAG_NO_BLOCK);

    if (status == SL_STATUS_OK) {
      rx_security_cmd = (sl_cpc_security_protocol_cmd_t *)read_buffer;
      process_security_command_rx(rx_security_cmd);
    } else if (status == SL_STATUS_EMPTY) {
      if (security_request_pending) {
        send_request(&security_protocol_request);
        security_request_pending = false;
      }
    } else {
      security_recover_endpoint();
    }
  }
}
#endif // SL_CPC_ENDPOINT_SECURITY_ENABLED

void sl_cpc_security_init(void)
{
#if (SL_CPC_ENDPOINT_SECURITY_ENABLED >= 1)
  sl_status_t status;
  uint8_t *key = NULL;
  uint16_t key_size = 0;

  psa_status_t psa_status =  psa_crypto_init();
  EFM_ASSERT(psa_status == PSA_SUCCESS);

  if (psa_is_key_present_in_storage(binding_key_id)) {
    is_bound = true;
  } else {
#if (SL_CPC_SECURITY_BINDING_KEY_METHOD == SL_CPC_SECURITY_BINDING_KEY_CUSTOMER_SPECIFIC)
    sl_cpc_security_fetch_user_specified_binding_key(&key, &key_size);
    EFM_ASSERT(key != NULL);
    EFM_ASSERT(key_size == 16);

    status = sli_cpc_security_store_binding_key(key, key_size);
    EFM_ASSERT(status == SL_STATUS_OK);
#else
    is_bound = false;
    (void)status;
    (void)key;
    (void)key_size;
#endif
  }

  security_open_endpoint();

#endif
}
