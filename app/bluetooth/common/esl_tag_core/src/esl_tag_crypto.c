/***************************************************************************//**
 * @file
 * @brief ESL Tag basic cryptography implementation.
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "em_common.h"
#include "esl_tag_log.h"
#include "esl_tag_core.h"
#include "esl_tag_crypto.h"
#include "sl_bt_ead_core.h"
#include "psa/crypto.h"

#define ENCRYPTION_ENABLED    1

#if ENCRYPTION_ENABLED

static uint8_t cipher_message_buffer[ESL_PAYLOAD_MAX_LENGTH
                                     + SL_BT_EAD_PACKET_OVERHEAD
                                     + ESL_PAYLOAD_OVERHEAD];

// ESL Tag encrypt function
void* esl_core_encrypt_message(void *msg, uint8_t *len)
{
  void* ret_val = NULL;
  sl_status_t status;
  struct sl_bt_ead_key_material_s key_material;
  struct sl_bt_ead_nonce_s nonce;
  sl_bt_ead_mic_t mic;
  struct sl_bt_ead_ad_structure_s ad_info = {
    *len,
    SL_BT_ENCRYPTED_DATA_AD_TYPE,
    &nonce.randomizer,
    msg,
    &mic
  };

  sl_bt_esl_assert(len != NULL);
  sl_bt_esl_assert(msg != NULL);

  status = esl_core_read_response_key(&key_material);

  if (status == SL_STATUS_OK) {
    status = sl_bt_ead_session_init(&key_material, NULL, &nonce);
  }

  if (status == SL_STATUS_OK) {
    status = sl_bt_ead_encrypt(&key_material, &nonce, *len, msg, mic);
  }

  if (status == SL_STATUS_OK) {
    *len = sizeof(cipher_message_buffer);
    status = sl_bt_ead_pack_ad_data(&ad_info, len, cipher_message_buffer);
  }

  if (status == SL_STATUS_OK) {
    ret_val = cipher_message_buffer;
  }

  return ret_val;
}

// ESL Tag decrypt function
void* esl_core_decrypt_message(void *msg, uint8_t *len)
{
  void* ret_val = NULL;

  if (*len > SL_BT_EAD_PACKET_OVERHEAD) {
    uint8_t *data = (uint8_t *)msg;
    struct sl_bt_ead_key_material_s key_material;
    sl_status_t status = esl_core_read_ap_key(&key_material);

    if (status == SL_STATUS_OK) {
      status = sl_bt_ead_unpack_decrypt(&key_material, &data, len);
    }

    if (status == SL_STATUS_OK) {
      ret_val = (void *)data;
    }
  }

  return ret_val;
}

#else // ENCRYPTION_ENABLED
// ESL Tag dummy encrypt function
SL_WEAK void* esl_core_encrypt_message(void *msg, uint8_t* len)
{
  (void)len;

  return msg;
}
// ESL Tag dummy decrypt function
SL_WEAK void* esl_core_decrypt_message(void *msg, uint8_t* len)
{
  (void)len;

  return msg;
}

#endif // ENCRYPTION_ENABLED
