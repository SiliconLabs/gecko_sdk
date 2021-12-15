/***************************************************************************//**
 * @file
 * @brief ECDH Key exchange component related header.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_ECDH_KEY_EXCHANGE_H_
#define SL_ECDH_KEY_EXCHANGE_H_

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include <stdbool.h>
#include <stdint.h>
#include "sl_ecdh_key_exchange_config.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------
#define SL_ECDH_KEY_EXCHANGE_KEY_SIZE_BYTES             (32)
#define SL_ECDH_KEY_EXCHANGE_ENCRYPTION_KEY_SIZE_BITS  (256)

typedef enum _SL_ECDH_KEY_EXCHANGE_BUFFER{
  SL_ECDH_KEY_EXCHANGE_BUFFER_PUBLICXLOCAL,
  SL_ECDH_KEY_EXCHANGE_BUFFER_PUBLICYLOCAL,
  SL_ECDH_KEY_EXCHANGE_BUFFER_PUBLICXREMOTE,
  SL_ECDH_KEY_EXCHANGE_BUFFER_PUBLICYREMOTE,
  SL_ECDH_KEY_EXCHANGE_BUFFER_END
} SL_ECDH_KEY_EXCHANGE_BUFFER;

typedef enum _SL_ECDH_KEY_EXCHANGE_RETURN_VALUE{
  SL_ECDH_KEY_EXCHANGE_RETURN_VALUE_OK,
  SL_ECDH_KEY_EXCHANGE_RETURN_VALUE_ERROR,
  SL_ECDH_KEY_EXCHANGE_RETURN_VALUE_ERROR_UNSUPPORTED_KEY_SIZE,
  SL_ECDH_KEY_EXCHANGE_RETURN_VALUE_END
} SL_ECDH_KEY_EXCHANGE_RETURN_VALUE;

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Declarations
// -----------------------------------------------------------------------------
SL_ECDH_KEY_EXCHANGE_RETURN_VALUE sl_ecdh_key_exchange_init(void);
SL_ECDH_KEY_EXCHANGE_RETURN_VALUE sl_ecdh_key_exchange_shared_key_generate(void);
uint8_t* sl_ecdh_key_exchange_shared_key_get(void);
uint8_t* sl_ecdh_key_exchange_buffer_get(SL_ECDH_KEY_EXCHANGE_BUFFER i_buffer_id);
SL_ECDH_KEY_EXCHANGE_RETURN_VALUE sl_ecdh_key_exchange_network_key_encrypt(uint8_t* i_network_key, uint8_t* o_network_key_encrypted);
SL_ECDH_KEY_EXCHANGE_RETURN_VALUE sl_ecdh_key_exchange_network_key_decrypt(uint8_t* i_encrypted_buffer, uint8_t* o_decrypted_buffer);
#endif /* SL_ECDH_KEY_EXCHANGE_H_ */
