/***************************************************************************/ /**
 * @file
 * @brief CPC Security Endpoint of the Secondary
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

#ifndef SL_CPC_SECURITY_SECONDARY_H_
#define SL_CPC_SECURITY_SECONDARY_H_

#include <stdint.h>
#include "sl_status.h"
#include "sl_enum.h"
#include "psa/crypto.h"
#include "psa_crypto_storage.h"
#include "sl_cpc_security_config.h"

/// The security state enabled bit mask
#define SL_CPC_SECURITY_STATE_ENABLE_MASK (1 << 0)

/// The security state bounded bit mask
#define SL_CPC_SECURITY_STATE_BOUND_MASK  (1 << 1)

SL_ENUM_GENERIC(sl_cpc_security_binding_key_method_t, uint8_t)
{
  SL_CPC_SECURITY_BINDING_KEY_CUSTOMER_SPECIFIC = 0x03,
  SL_CPC_SECURITY_BINDING_KEY_ECDH              = 0x02,
  SL_CPC_SECURITY_BINDING_KEY_PLAINTEXT_SHARE   = 0x01,
  SL_CPC_SECURITY_BINDING_KEY_NONE              = 0x00
};

#define SLI_CPC_SECURITY_BINDING_TYPE_PLAINTEXT 0x00
#define SLI_CPC_SECURITY_BINDING_TYPE_ECDH      0x01

#define SLI_CPC_SECURITY_PROTOCOL_RESPONSE_MASK 0x8000

SL_ENUM_GENERIC(sl_cpc_security_id_t, uint16_t)
{
  BINDING_REQUEST_ID       = 0x0001,
  PLAIN_TEXT_KEY_SHARE_ID  = 0x0002,
  PUBLIC_KEY_SHARE_ID      = 0x0003,
  SESSION_INIT_ID          = 0x0004,
  UNBIND_REQUEST_ID        = 0x0005
};

SL_ENUM_GENERIC(sl_cpc_binding_request_t, uint8_t)
{
  PLAIN_TEXT_KEY_SHARE_BINDING_REQUEST = 0x00,
  ECDH_BINDING_REQUEST = 0x01
};

typedef struct {
  uint16_t request_len;
  uint16_t response_len;
  sl_cpc_security_id_t command_id;
}sl_cpc_security_protocol_cmd_info_t;

#define SLI_SECURITY_BINDING_KEY_LENGTH_BYTES         16
#define SLI_SECURITY_PUBLIC_KEY_LENGTH_BYTES          32
#define SLI_SECURITY_SESSION_KEY_LENGTH_BYTES         32
#define SLI_SECURITY_SESSION_ID_LENGTH_BYTES          8
#define SLI_SECURITY_SESSION_INIT_RANDOM_LENGTH_BYTES 64
#define SLI_SECURITY_SHA256_LENGTH_BYTES              32

#define SLI_SECURITY_PROTOCOL_PAYLOAD_MAX_LENGTH (sizeof(sl_status_t) + SLI_SECURITY_SESSION_INIT_RANDOM_LENGTH_BYTES)
#define SLI_SECURITY_PROTOCOL_HEADER_LENGTH (sizeof(uint16_t) + sizeof(sl_cpc_security_id_t))

typedef __PACKED_STRUCT {
  uint16_t len;
  sl_cpc_security_id_t command_id;
  uint8_t payload[SLI_SECURITY_PROTOCOL_PAYLOAD_MAX_LENGTH];
} sl_cpc_security_protocol_cmd_t;

typedef __PACKED_STRUCT {
  sl_status_t status;
  uint8_t random2[SLI_SECURITY_SESSION_INIT_RANDOM_LENGTH_BYTES];
} session_init_response_t;

#ifdef __cplusplus
extern "C"
{
#endif

/***************************************************************************/ /**
 * @addtogroup cpc_security_secondary
 * @brief CPC Security Secondary
 * @details
 * @{
 ******************************************************************************/
uint32_t sl_cpc_security_get_state(void);

/***************************************************************************/ /**
 * User callback to provide CPC with a binding key
 *
 * SL_CPC_SECURITY_BINDING_KEY_METHOD config must be set to
 * SL_CPC_SECURITY_BINDING_KEY_CUSTOMER_SPECIFIC
 *
 * @param[out] key               The encryption key
 * @param[out] key_size          The encryption key size
 *                               Note: Only 16 bytes keys are supported for the moment
 ******************************************************************************/
void sl_cpc_security_fetch_user_specified_binding_key(uint8_t **key, uint16_t *key_size_in_bytes);

/***************************************************************************/ /**
 * Security endpoint init
 ******************************************************************************/
void sl_cpc_security_init(void);

/***************************************************************************/ /**
 * Security endpoint process action
 ******************************************************************************/
void sli_cpc_security_process(void);

/** @} (end addtogroup cpc_security_secondary) */

#ifdef __cplusplus
}
#endif

#endif /* SL_CPC_SECURITY_SECONDARY_H_ */
