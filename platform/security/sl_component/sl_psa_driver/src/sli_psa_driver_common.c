/***************************************************************************/ /**
 * @file
 * @brief PSA Driver common utility functions
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

#include "sli_psa_driver_common.h"

#include "constant_time_internal.h"
#include "constant_time_impl.h"

//------------------------------------------------------------------------------
// Function definitions

psa_status_t sli_psa_validate_pkcs7_padding(uint8_t *padded_data,
                                            size_t padded_data_length,
                                            size_t *padding_bytes)
{
  size_t i, pad_idx;
  unsigned char padding_len;

  padding_len = padded_data[padded_data_length - 1];
  *padding_bytes = padding_len;

  mbedtls_ct_condition_t bad =
    mbedtls_ct_uint_gt(padding_len, padded_data_length);
  bad = mbedtls_ct_bool_or(bad, mbedtls_ct_uint_eq(padding_len, 0));

  // The number of bytes checked must be independent of padding_len, so pick
  // input_len, which is 16 bytes (one block) for our use cases.
  pad_idx = padded_data_length - padding_len;
  for (i = 0; i < padded_data_length; i++) {
    mbedtls_ct_condition_t in_padding = mbedtls_ct_uint_ge(i, pad_idx);
    mbedtls_ct_condition_t different =
      mbedtls_ct_uint_ne(padded_data[i], padding_len);
    bad = mbedtls_ct_bool_or(bad, mbedtls_ct_bool_and(in_padding, different));
  }

  return (psa_status_t)mbedtls_ct_error_if_else_0(bad,
                                                  PSA_ERROR_INVALID_PADDING);
}
