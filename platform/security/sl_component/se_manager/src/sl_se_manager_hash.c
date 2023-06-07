/***************************************************************************//**
 * @file
 * @brief Silicon Labs Secure Engine Manager API.
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

#include "sl_se_manager.h"

#if defined(SLI_MAILBOX_COMMAND_SUPPORTED)

#include "sli_se_manager_internal.h"
#include "em_se.h"
#include "sl_assert.h"
#include <string.h>

/***************************************************************************//**
 * \addtogroup sl_se Secure Engine Manager API
 * @{
 ******************************************************************************/

// -----------------------------------------------------------------------------
// Global functions

/***************************************************************************//**
 * Start a SHA1 stream operation.
 ******************************************************************************/
sl_status_t sl_se_hash_sha1_multipart_starts(sl_se_sha1_multipart_context_t *sha1_ctx,
                                             sl_se_command_context_t *cmd_ctx)
{
  static const uint8_t init_state_sha1[32] = {
    0x67, 0x45, 0x23, 0x01,
    0xEF, 0xCD, 0xAB, 0x89,
    0x98, 0xBA, 0xDC, 0xFE,
    0x10, 0x32, 0x54, 0x76,
    0xC3, 0xD2, 0xE1, 0xF0,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
  };

  if (cmd_ctx == NULL || sha1_ctx == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  sha1_ctx->total[0] = 0;
  sha1_ctx->total[1] = 0;
  memcpy(sha1_ctx->state, init_state_sha1, sizeof(sha1_ctx->state));

  sha1_ctx->hash_type = SL_SE_HASH_SHA1;

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Start a SHA224 stream operation.
 ******************************************************************************/
sl_status_t
sl_se_hash_sha224_multipart_starts(sl_se_sha224_multipart_context_t *sha224_ctx,
                                   sl_se_command_context_t *cmd_ctx)
{
  static const uint8_t init_state_sha224[32] = {
    0xC1, 0x05, 0x9E, 0xD8,
    0x36, 0x7C, 0xD5, 0x07,
    0x30, 0x70, 0xDD, 0x17,
    0xF7, 0x0E, 0x59, 0x39,
    0xFF, 0xC0, 0x0B, 0x31,
    0x68, 0x58, 0x15, 0x11,
    0x64, 0xF9, 0x8F, 0xA7,
    0xBE, 0xFA, 0x4F, 0xA4
  };

  if (cmd_ctx == NULL || sha224_ctx == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  sha224_ctx->total[0] = 0;
  sha224_ctx->total[1] = 0;
  memcpy(sha224_ctx->state, init_state_sha224, sizeof(sha224_ctx->state));

  sha224_ctx->hash_type = SL_SE_HASH_SHA224;

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Start a SHA256 stream operation.
 ******************************************************************************/
sl_status_t
sl_se_hash_sha256_multipart_starts(sl_se_sha256_multipart_context_t *sha256_ctx,
                                   sl_se_command_context_t *cmd_ctx)
{
  static const uint8_t init_state_sha256[32] = {
    0x6A, 0x09, 0xE6, 0x67,
    0xBB, 0x67, 0xAE, 0x85,
    0x3C, 0x6E, 0xF3, 0x72,
    0xA5, 0x4F, 0xF5, 0x3A,
    0x51, 0x0E, 0x52, 0x7F,
    0x9B, 0x05, 0x68, 0x8C,
    0x1F, 0x83, 0xD9, 0xAB,
    0x5B, 0xE0, 0xCD, 0x19
  };

  if (cmd_ctx == NULL || sha256_ctx == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  sha256_ctx->total[0] = 0;
  sha256_ctx->total[1] = 0;
  memcpy(sha256_ctx->state, init_state_sha256, sizeof(sha256_ctx->state));

  sha256_ctx->hash_type = SL_SE_HASH_SHA256;

  return SL_STATUS_OK;
}

#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
/***************************************************************************//**
 * Start a SHA384 stream operation.
 ******************************************************************************/
sl_status_t
sl_se_hash_sha384_multipart_starts(sl_se_sha384_multipart_context_t *sha384_ctx,
                                   sl_se_command_context_t *cmd_ctx)
{
  static const uint8_t init_state_sha384[64] = {
    0xCB, 0xBB, 0x9D, 0x5D, 0xC1, 0x05, 0x9E, 0xD8,
    0x62, 0x9A, 0x29, 0x2A, 0x36, 0x7C, 0xD5, 0x07,
    0x91, 0x59, 0x01, 0x5A, 0x30, 0x70, 0xDD, 0x17,
    0x15, 0x2F, 0xEC, 0xD8, 0xF7, 0x0E, 0x59, 0x39,
    0x67, 0x33, 0x26, 0x67, 0xFF, 0xC0, 0x0B, 0x31,
    0x8E, 0xB4, 0x4A, 0x87, 0x68, 0x58, 0x15, 0x11,
    0xDB, 0x0C, 0x2E, 0x0D, 0x64, 0xF9, 0x8F, 0xA7,
    0x47, 0xB5, 0x48, 0x1D, 0xBE, 0xFA, 0x4F, 0xA4
  };

  if (cmd_ctx == NULL || sha384_ctx == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  sha384_ctx->total[0] = 0;
  sha384_ctx->total[1] = 0;
  sha384_ctx->total[2] = 0;
  sha384_ctx->total[3] = 0;
  memcpy(sha384_ctx->state, init_state_sha384, sizeof(sha384_ctx->state));

  sha384_ctx->hash_type = SL_SE_HASH_SHA384;

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Start a SHA512 stream operation.
 ******************************************************************************/
sl_status_t
sl_se_hash_sha512_multipart_starts(sl_se_sha512_multipart_context_t *sha512_ctx, sl_se_command_context_t *cmd_ctx)
{
  static const uint8_t init_state_sha512[64] = {
    0x6A, 0x09, 0xE6, 0x67, 0xF3, 0xBC, 0xC9, 0x08,
    0xBB, 0x67, 0xAE, 0x85, 0x84, 0xCA, 0xA7, 0x3B,
    0x3C, 0x6E, 0xF3, 0x72, 0xFE, 0x94, 0xF8, 0x2B,
    0xA5, 0x4F, 0xF5, 0x3A, 0x5F, 0x1D, 0x36, 0xF1,
    0x51, 0x0E, 0x52, 0x7F, 0xAD, 0xE6, 0x82, 0xD1,
    0x9B, 0x05, 0x68, 0x8C, 0x2B, 0x3E, 0x6C, 0x1F,
    0x1F, 0x83, 0xD9, 0xAB, 0xFB, 0x41, 0xBD, 0x6B,
    0x5B, 0xE0, 0xCD, 0x19, 0x13, 0x7E, 0x21, 0x79
  };

  if (cmd_ctx == NULL || sha512_ctx == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  sha512_ctx->total[0] = 0;
  sha512_ctx->total[1] = 0;
  sha512_ctx->total[2] = 0;
  sha512_ctx->total[3] = 0;
  memcpy(sha512_ctx->state, init_state_sha512, sizeof(sha512_ctx->state));

  sha512_ctx->hash_type = SL_SE_HASH_SHA512;

  return SL_STATUS_OK;
}

#endif

/***************************************************************************//**
 * Start a hash stream operation.
 ******************************************************************************/
sl_status_t sl_se_hash_multipart_starts(void *hash_type_ctx,
                                        sl_se_command_context_t *cmd_ctx,
                                        sl_se_hash_type_t hash_type)
{
  if (cmd_ctx == NULL || hash_type_ctx == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  switch (hash_type) {
    case SL_SE_HASH_SHA1:
      return sl_se_hash_sha1_multipart_starts((sl_se_sha1_multipart_context_t*)
                                              hash_type_ctx, cmd_ctx);

    case SL_SE_HASH_SHA224:
      return sl_se_hash_sha224_multipart_starts((sl_se_sha224_multipart_context_t*)
                                                hash_type_ctx, cmd_ctx);

    case SL_SE_HASH_SHA256:
      return sl_se_hash_sha256_multipart_starts((sl_se_sha256_multipart_context_t*)
                                                hash_type_ctx, cmd_ctx);

#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
    case SL_SE_HASH_SHA384:
      return sl_se_hash_sha384_multipart_starts((sl_se_sha384_multipart_context_t*)
                                                hash_type_ctx,
                                                cmd_ctx);

    case SL_SE_HASH_SHA512:
      return sl_se_hash_sha512_multipart_starts((sl_se_sha512_multipart_context_t*)
                                                hash_type_ctx, cmd_ctx);
#endif

    default:
      return SL_STATUS_INVALID_PARAMETER;
  }
}

/***************************************************************************//**
 *   Feeds an input block into an ongoing hash computation.
 ******************************************************************************/
static sl_status_t se_cmd_hash_multipart_update(void *hash_type_ctx,
                                                sl_se_command_context_t *cmd_ctx,
                                                const uint8_t *input,
                                                uint32_t num_blocks)
{
  SE_Command_t *se_cmd = &cmd_ctx->command;
  uint8_t *state;
  uint32_t command_word = SLI_SE_COMMAND_HASHUPDATE;
  size_t state_len, blocksize;

  switch (((sl_se_sha1_multipart_context_t*)hash_type_ctx)->hash_type) {
    case SL_SE_HASH_SHA1:
      state = ((sl_se_sha1_multipart_context_t*)hash_type_ctx)->state;
      command_word |= SLI_SE_COMMAND_OPTION_HASH_SHA1;
      state_len = 20;
      blocksize = 64;
      break;
    case SL_SE_HASH_SHA224:
      state = ((sl_se_sha224_multipart_context_t*)hash_type_ctx)->state;
      command_word |= SLI_SE_COMMAND_OPTION_HASH_SHA224;
      state_len = 32;
      blocksize = 64;
      break;
    case SL_SE_HASH_SHA256:
      state = ((sl_se_sha256_multipart_context_t*)hash_type_ctx)->state;
      command_word |= SLI_SE_COMMAND_OPTION_HASH_SHA256;
      state_len = 32;
      blocksize = 64;
      break;

#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
    case SL_SE_HASH_SHA384:
      state = ((sl_se_sha384_multipart_context_t*)hash_type_ctx)->state;
      command_word |= SLI_SE_COMMAND_OPTION_HASH_SHA384;
      state_len = 64;
      blocksize = 128;
      break;
    case SL_SE_HASH_SHA512:
      state = ((sl_se_sha512_multipart_context_t*)hash_type_ctx)->state;
      command_word |= SLI_SE_COMMAND_OPTION_HASH_SHA512;
      state_len = 64;
      blocksize = 128;
      break;
#endif

    default:
      return SL_STATUS_INVALID_PARAMETER;
  }

  sli_se_command_init(cmd_ctx, command_word);

  size_t ilen = blocksize * num_blocks;
  SE_addParameter(se_cmd, ilen);

  SE_DataTransfer_t data_in = SE_DATATRANSFER_DEFAULT(input, ilen);
  SE_DataTransfer_t iv_in = SE_DATATRANSFER_DEFAULT(state, state_len);
  SE_DataTransfer_t iv_out = SE_DATATRANSFER_DEFAULT(state, state_len);

  SE_addDataInput(se_cmd, &iv_in);
  SE_addDataInput(se_cmd, &data_in);
  SE_addDataOutput(se_cmd, &iv_out);

  // Execute and wait
  return sli_se_execute_and_wait(cmd_ctx);
}

/***************************************************************************//**
 *   Feeds an input buffer into an ongoing hash computation.
 ******************************************************************************/
sl_status_t sl_se_hash_multipart_update(void *hash_type_ctx,
                                        sl_se_command_context_t *cmd_ctx,
                                        const uint8_t *input,
                                        size_t input_len)
{
  size_t blocks, fill, left, blocksize, countersize;
  sl_status_t status;
  uint8_t *buffer;
  uint32_t *counter;

  if ( input_len == 0 ) {
    return SL_STATUS_OK;
  }

  if (hash_type_ctx == NULL || cmd_ctx == NULL || input == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  switch (((sl_se_sha1_multipart_context_t*)hash_type_ctx)->hash_type) {
    case SL_SE_HASH_SHA1:
      counter = ((sl_se_sha1_multipart_context_t*)hash_type_ctx)->total;
      buffer = ((sl_se_sha1_multipart_context_t*)hash_type_ctx)->buffer;
      blocksize = 64;
      break;
    case SL_SE_HASH_SHA224:
      counter = ((sl_se_sha224_multipart_context_t*)hash_type_ctx)->total;
      buffer = ((sl_se_sha224_multipart_context_t*)hash_type_ctx)->buffer;
      blocksize = 64;
      break;
    case SL_SE_HASH_SHA256:
      counter = ((sl_se_sha256_multipart_context_t*)hash_type_ctx)->total;
      buffer = ((sl_se_sha256_multipart_context_t*)hash_type_ctx)->buffer;
      blocksize = 64;
      break;

#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
    case SL_SE_HASH_SHA384:
      counter = ((sl_se_sha384_multipart_context_t*)hash_type_ctx)->total;
      buffer = ((sl_se_sha384_multipart_context_t*)hash_type_ctx)->buffer;
      blocksize = 128;
      break;
    case SL_SE_HASH_SHA512:
      counter = ((sl_se_sha512_multipart_context_t*)hash_type_ctx)->total;
      buffer = ((sl_se_sha512_multipart_context_t*)hash_type_ctx)->buffer;
      blocksize = 128;
      break;
#endif

    default:
      return SL_STATUS_INVALID_PARAMETER;
  }

  countersize = blocksize / 32;
  left = (counter[0] & (blocksize - 1));
  fill = blocksize - left;

  counter[0] += input_len;

  // ripple counter
  if ( counter[0] < input_len ) {
    counter[1] += 1;
#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
    for (size_t i = 1; i < (countersize - 1); i++) {
      if ( counter[i] == 0 ) {
        counter[i + 1]++;
      }
    }
#else
    (void)countersize;
#endif
  }

  // We only support hashing up to 4 GB data
  // so if anything but counter[0] is set, return NOT_SUPPORTED
#if defined(SLI_SE_MAJOR_VERSION_TWO)
  for (size_t i = 1; i < countersize; i++) {
    if (counter[i] != 0) {
      return SL_STATUS_NOT_SUPPORTED;
    }
  }
#endif

  if ( (left > 0) && (input_len >= fill) ) {
    memcpy( (void *) (buffer + left), input, fill);
    status = se_cmd_hash_multipart_update(hash_type_ctx, cmd_ctx, buffer, 1);
    if (status != SL_STATUS_OK) {
      return status;
    }
    input += fill;
    input_len -= fill;
    left = 0;
  }

  if ( input_len >= blocksize ) {
    blocks = input_len / blocksize;
    status = se_cmd_hash_multipart_update(hash_type_ctx, cmd_ctx, input, blocks);
    if (status != SL_STATUS_OK) {
      return status;
    }
    input += blocksize * blocks;
    input_len -= blocksize * blocks;
  }

  if ( input_len > 0 ) {
    memcpy( (void *) (buffer + left), input, input_len);
  }

  return SL_STATUS_OK;
}

/***************************************************************************//**
 *   Finish an ongoing hash streaming computation.
 ******************************************************************************/
sl_status_t sl_se_hash_multipart_finish(void *hash_type_ctx,
                                        sl_se_command_context_t *cmd_ctx,
                                        uint8_t *digest_out,
                                        size_t   digest_len)
{
  sl_status_t status;
  size_t countersize, blocksize, outputsize;
  uint8_t *state;
  uint32_t *counter;
#if defined(SLI_SE_MAJOR_VERSION_TWO)
  uint32_t command_word = SLI_SE_COMMAND_HASHFINISH;
  uint8_t *buffer;
  size_t state_len;
#else
  size_t last_data_byte, num_pad_bytes;
  uint8_t msglen[16];
  // Define padding as largest padding we might need
  #if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
  static const unsigned char sha_padding[128] = {
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  };
  #else
  static const unsigned char sha_padding[64] = {
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  };
  #endif
#endif
  if (hash_type_ctx == NULL || cmd_ctx == NULL || digest_out == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  switch (((sl_se_sha1_multipart_context_t*)hash_type_ctx)->hash_type) {
    case SL_SE_HASH_SHA1:
      state = ((sl_se_sha1_multipart_context_t*)hash_type_ctx)->state;
      counter = ((sl_se_sha1_multipart_context_t*)hash_type_ctx)->total;
      outputsize = 20;
      blocksize = 64;
    #if defined(SLI_SE_MAJOR_VERSION_TWO)
      state_len = 20;
      command_word |= SLI_SE_COMMAND_OPTION_HASH_SHA1;
      buffer = ((sl_se_sha1_multipart_context_t*)hash_type_ctx)->buffer;
    #endif
      break;
    case SL_SE_HASH_SHA224:
      state = ((sl_se_sha224_multipart_context_t*)hash_type_ctx)->state;
      counter = ((sl_se_sha224_multipart_context_t*)hash_type_ctx)->total;
      outputsize = 28;
      blocksize = 64;
    #if defined(SLI_SE_MAJOR_VERSION_TWO)
      state_len = 32;
      command_word |= SLI_SE_COMMAND_OPTION_HASH_SHA224;
      buffer = ((sl_se_sha224_multipart_context_t*)hash_type_ctx)->buffer;
    #endif
      break;
    case SL_SE_HASH_SHA256:
      state = ((sl_se_sha256_multipart_context_t*)hash_type_ctx)->state;
      counter = ((sl_se_sha256_multipart_context_t*)hash_type_ctx)->total;
      outputsize = 32;
      blocksize = 64;
    #if defined(SLI_SE_MAJOR_VERSION_TWO)
      state_len = 32;
      command_word |= SLI_SE_COMMAND_OPTION_HASH_SHA256;
      buffer = ((sl_se_sha256_multipart_context_t*)hash_type_ctx)->buffer;
    #endif
      break;

#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
    case SL_SE_HASH_SHA384:
      state = ((sl_se_sha384_multipart_context_t*)hash_type_ctx)->state;
      counter = ((sl_se_sha384_multipart_context_t*)hash_type_ctx)->total;
      outputsize = 48;
      blocksize = 128;
    #if defined(SLI_SE_MAJOR_VERSION_TWO)
      state_len = 64;
      command_word |= SLI_SE_COMMAND_OPTION_HASH_SHA384;
      buffer = ((sl_se_sha384_multipart_context_t*)hash_type_ctx)->buffer;
    #endif
      break;
    case SL_SE_HASH_SHA512:
      state = ((sl_se_sha512_multipart_context_t*)hash_type_ctx)->state;
      counter = ((sl_se_sha512_multipart_context_t*)hash_type_ctx)->total;
      outputsize = 64;
      blocksize = 128;
    #if defined(SLI_SE_MAJOR_VERSION_TWO)
      state_len = 64;
      command_word |= SLI_SE_COMMAND_OPTION_HASH_SHA512;
      buffer = ((sl_se_sha512_multipart_context_t*)hash_type_ctx)->buffer;
    #endif
      break;
#endif

    default:
      return SL_STATUS_INVALID_PARAMETER;
  }

  if ( digest_len < outputsize ) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  countersize = blocksize / 32;
#if defined(SLI_SE_MAJOR_VERSION_TWO)

  // We only support hashing up to 4 GB data
  // so if anything but counter[0] is set, return NOT_SUPPORTED
  for (size_t i = 1; i < countersize; i++) {
    if (counter[i] != 0) {
      return SL_STATUS_NOT_SUPPORTED;
    }
  }
  // Remaining bytes in buffer
  size_t rem_bytes = (counter[0] & (blocksize - 1));

  SE_Command_t *se_cmd = &cmd_ctx->command;

  sli_se_command_init(cmd_ctx, command_word);

  SE_addParameter(se_cmd, rem_bytes);
  SE_addParameter(se_cmd, counter[0]);

  SE_DataTransfer_t in_0 = SE_DATATRANSFER_DEFAULT(state, state_len);
  SE_DataTransfer_t in_1 = SE_DATATRANSFER_DEFAULT(buffer, rem_bytes);
  SE_DataTransfer_t out = SE_DATATRANSFER_DEFAULT(digest_out, outputsize);

  SE_addDataInput(se_cmd, &in_0);
  SE_addDataInput(se_cmd, &in_1);
  SE_addDataOutput(se_cmd, &out);

  // Execute and wait
  status = sli_se_execute_and_wait(cmd_ctx);
#else

  /* Convert counter value to bits, and put in big-endian array */
  uint8_t residual = 0;
  for (size_t i = 0; i < countersize; i++) {
    size_t msglen_index = ( (countersize - i) * sizeof(uint32_t) ) - 1;

    msglen[msglen_index - 0] = ((counter[i] << 3) + residual) & 0xFF;
    msglen[msglen_index - 1] = (counter[i] >> 5) & 0xFF;
    msglen[msglen_index - 2] = (counter[i] >> 13) & 0xFF;
    msglen[msglen_index - 3] = (counter[i] >> 21) & 0xFF;

    residual = (counter[i] >> 29) & 0xFF;
  }

  last_data_byte = (counter[0] & (blocksize - 1) );
  num_pad_bytes = (last_data_byte < (blocksize - (countersize * 4)) )
                  ? ( (blocksize - (countersize * 4)) - last_data_byte)
                  : ( ((2 * blocksize) - (countersize * 4)) - last_data_byte);

  status = sl_se_hash_multipart_update(hash_type_ctx, cmd_ctx, sha_padding, num_pad_bytes);

  if (status == SL_STATUS_OK) {
    status = sl_se_hash_multipart_update(hash_type_ctx, cmd_ctx, msglen, countersize * 4);
  }

  if (status == SL_STATUS_OK) {
    memcpy(digest_out, state, outputsize);
  }
#endif // SLI_SE_MAJOR_VERSION_TWO
  return status;
}

/***************************************************************************//**
 *   Produce a message digest (a hash block) using the input data.
 ******************************************************************************/
sl_status_t sl_se_hash(sl_se_command_context_t *cmd_ctx,
                       sl_se_hash_type_t hash_type,
                       const uint8_t *message,
                       unsigned int message_size,
                       uint8_t* digest,
                       size_t digest_len)
{
  if (cmd_ctx == NULL
      || digest == NULL
      || (message == NULL
          && message_size != 0)) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  SE_Command_t *se_cmd = &cmd_ctx->command;
  uint32_t command_word = SLI_SE_COMMAND_HASH;
  uint32_t digest_size = 0;

  switch (hash_type) {
    case SL_SE_HASH_SHA1:
      command_word |= SLI_SE_COMMAND_OPTION_HASH_SHA1;
      digest_size = 20;
      break;
    case SL_SE_HASH_SHA224:
      command_word |= SLI_SE_COMMAND_OPTION_HASH_SHA224;
      digest_size = 28;
      break;
    case SL_SE_HASH_SHA256:
      command_word |= SLI_SE_COMMAND_OPTION_HASH_SHA256;
      digest_size = 32;
      break;
#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
    case SL_SE_HASH_SHA384:
      command_word |= SLI_SE_COMMAND_OPTION_HASH_SHA384;
      digest_size = 48;
      break;
    case SL_SE_HASH_SHA512:
      digest_size = 64;
      command_word |= SLI_SE_COMMAND_OPTION_HASH_SHA512;
      break;
#endif
    default:
      return SL_STATUS_INVALID_PARAMETER;
  }

  if ( digest_len < digest_size ) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  sli_se_command_init(cmd_ctx, command_word);

  SE_addParameter(se_cmd, message_size);

  SE_DataTransfer_t data_in = SE_DATATRANSFER_DEFAULT(message, message_size);
  SE_DataTransfer_t data_out = SE_DATATRANSFER_DEFAULT(digest, digest_size);

  SE_addDataInput(se_cmd, &data_in);
  SE_addDataOutput(se_cmd, &data_out);

  // Execute and wait
  return sli_se_execute_and_wait(cmd_ctx);
}

/** @} (end addtogroup sl_se) */

#endif // defined(SLI_MAILBOX_COMMAND_SUPPORTED)
