/****************************************************************************
 * @file ccm-star.c
 * @brief implements the CCM* API, providing both software and mbedtls versions
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
#ifdef PLATFORM_HEADER
  #include PLATFORM_HEADER
#else
  #include "hal/micro/unix/compiler/gcc.h"
#endif
#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif

// TODO: EMZIGBEE-3712
void sli_util_stand_alone_encrypt_block(uint8_t* block);

extern void sli_zigbee_get_key_from_core(uint8_t* key);

#include "stack/include/ember-types.h"
#include "stack/include/ccm-star.h"

#define ENCRYPTION_BLOCK_SIZE 16

// This implements the CCM* encryption algorithm, using AES-128 as the
// underlying block cipher.  AES-128 is essentially a hash function
// controlled by 128-bit (16 byte) keys.  The AES-128 algorithm takes a key
// and a 16-byte block of data and produces a 16-byte block of noise.
//
// The em250 implements AES-128 in hardware.  The hardware can also handle
// some of the other CCM* calculations, but at this point we only use the
// basic AES-128 functionality.
//
// CCM* uses AES-128 for authentication and encryption.  In authentication,
// AES-128 is used create a hash number from a message, called a MIC.
// The MIC is appended to the message before transmission.  The recipient
// hashes the message and verifies that it obtains the same MIC.  Changes
// to either the body of the message or the appended MIC will result in
// the recipient's MIC differing from the appended MIC.
//
// For encryption, AES-128 is used to create a series of pseudo-random
// blocks which are xor-ed with the message to produce the encrypted
// version.  The recipient performs the same operation, which results in
// the original message.  It is important that each message be encrypted
// with a different psuedo-random sequence.  If two messages used the
// same sequence, xor-ing the encrypted messages would produce the xor
// of the unencrypted messages.
//
// Both authentication and encryption begin by encrypting a special block
// of data called a 'nonce' (as in 'for the nonce').  The goal is that each
// use of a particular key will use a different nonce.  The nonce is:
//
// Offset Size
//   0     1    flags
//   1     8    source EUI64
//   9     4    frame counter
//  13     1    control byte
//  14     2    block count
//
// The frame counter is incremented for each message and the block count is
// incremented for each encryption block.  The flags and control byte ensure
// that different operations on the same message, such as MIC generation and
// encryption, do not use the same nonce.

#if !(defined SL_CATALOG_ZIGBEE_CCM_SOFTWARE_PRESENT) && !defined(EMBER_TEST)
#error "Only the Zigbee CCM (Software) component should bring in this file. Hardware should bring in the ZB Security Manager component"
#endif // SL_CATALOG_ZIGBEE_

// -----------------------------------------------------------------
// Software Implementation of CCM on top of the single-block AES API
// -----------------------------------------------------------------

// Handy macro.  This is unsafe because it duplicates its arguments.
#define min(x, y) ((x) < (y) ? (x) : (y))

//----------------------------------------------------------------
// MIC encryption flags

// For authentication, the flags byte has the following form:
//  <reserved:1> <adata:1> <M:3> <L:3>
// Where
//  <reserved:1> = 0   Reserved for future expansion.
//  <adata:1>          0 for zero-length messages, 1 for non-zero-length
//  <M:3>              MIC length, encoded as (micLength - 2)/2
//  <L:3>              Number of bytes used to represent the length
//                     of the message, - 1.

#if MESSAGE_LENGTH_FIELD_SIZE > 0
  #define MIC_FLAG_ADATA_FIELD 0x40
  #define FLAG_L_FIELD ((MESSAGE_LENGTH_FIELD_SIZE - 1) & 0x07)
#else
  #define MIC_FLAG_ADATA_FIELD 0x00
  #define FLAG_L_FIELD 0x00
#endif

#ifdef USE_8_BYTE_MIC
  #define MIC_FLAG_M_FIELD 0x18
#else
  #define MIC_FLAG_M_FIELD 0x08
#endif

#define MIC_FLAG_MASK \
  (MIC_FLAG_ADATA_FIELD | MIC_FLAG_M_FIELD | FLAG_L_FIELD)
#define ENCRYPTION_FLAG_MASK (0x00 | FLAG_L_FIELD)

// Performs an actual nonce encryption, after first setting the fields
// specific to this block.  We do a copy to avoid clobbering the (shared)
// nonce.

#define encryptMicBlock0(nonce, variableField, result) \
  (encryptNonce((nonce), MIC_FLAG_MASK, (variableField), (result)))

#define encryptBlock0(nonce, variableField, result) \
  (encryptNonce((nonce), ENCRYPTION_FLAG_MASK, (variableField), (result)))

static void encryptNonce(uint8_t *nonce,
                         uint8_t flagsMask,
                         uint16_t variableField,
                         uint8_t block[ENCRYPTION_BLOCK_SIZE])
{
  MEMCOPY(block + STANDALONE_NONCE_INDEX, nonce, NONCE_LENGTH);

  block[STANDALONE_FLAGS_INDEX] = flagsMask;
  block[STANDALONE_VARIABLE_FIELD_INDEX_HIGH] = HIGH_BYTE(variableField);
  block[STANDALONE_VARIABLE_FIELD_INDEX_LOW] = LOW_BYTE(variableField);

  sli_util_stand_alone_encrypt_block(block);
}

//----------------------------------------------------------------
// This performs the core of the MIC calculation.  'Count' bytes from
// 'bytes' are xor-ed into 'block' and then encrypted.  We start at
// 'blockIndex' in the block.
//
// The final blockIndex is returned.

static uint8_t xorBytesIntoBlock(uint8_t *block,
                                 uint8_t blockIndex,
                                 const uint8_t *bytes,
                                 uint16_t count)
{
  uint16_t i;

  for (i = 0; i < count; ) {
    uint16_t needed = ENCRYPTION_BLOCK_SIZE - blockIndex;
    uint16_t todo = count - i;
    uint16_t copied = min(todo, needed);
    uint16_t j;

    for (j = 0; j < copied; j++, blockIndex++) {
      block[blockIndex] ^= *bytes++;
    }
    i += copied;

    if (blockIndex == ENCRYPTION_BLOCK_SIZE) {
      sli_util_stand_alone_encrypt_block(block);
      blockIndex = 0;
    }
  }
  return blockIndex;
}

// static buffer to hold blocks of data for AES encryption
static uint8_t encryptionBlock[ENCRYPTION_BLOCK_SIZE];

// Encrypt an array of bytes by xor-ing with a series of AES encrypted nonces
static void ccmEncryptData(uint8_t *bytes,
                           uint16_t length,
                           uint8_t blockCount,
                           uint8_t *nonce)
{
  while (length > 0) {
    uint8_t todo = min(length, ENCRYPTION_BLOCK_SIZE);
    uint8_t i;
    encryptBlock0(nonce, blockCount, encryptionBlock);
    blockCount += 1;

    for (i = 0; i < todo; i++) {
      *bytes++ ^= encryptionBlock[i];
    }

    length -= todo;
  }
}

// Calculate the MIC by hashing first the authenticated portion of the
// packet and then the encrypted portion (which hasn't been encrypted yet).
//
// The encrypted bytes are processed on a block boundary, so we finish off
// the block at the end of the authenticated bytes.
//
// The 'for' loop goes around two times (authenticated bytes, encrypted bytes).
void emberCcmCalculateAndEncryptMic(uint8_t *nonce,
                                    uint8_t *authData,
                                    uint16_t authlen,
                                    uint8_t *payload,
                                    uint16_t payloadlen,
                                    uint8_t *micResult)
{
  uint8_t blockIndex = 2;     // skip over frame length field
  uint8_t *chunk = authData;
  uint16_t chunklen;
  uint8_t phase;

  chunklen = authlen;
  encryptMicBlock0(nonce, payloadlen, encryptionBlock);

  // first two bytes are the 16-bit representation of the frame length,
  // high byte first
  encryptionBlock[0] ^= HIGH_BYTE(authlen);
  encryptionBlock[1] ^= LOW_BYTE(authlen);

  // phase 0: go over authenticated data
  // phase 1: go over the payload
  for (phase = 0; phase < 2; phase++) {
    blockIndex = xorBytesIntoBlock(encryptionBlock,
                                   blockIndex,
                                   chunk,
                                   chunklen);
    chunk = payload;
    chunklen = payloadlen;

    // finish off authData if not on an encryption block boundary
    if (blockIndex > 0) {
      sli_util_stand_alone_encrypt_block(encryptionBlock);
      blockIndex = 0;
    }
  }

  MEMCOPY(micResult, encryptionBlock, MIC_LENGTH);
  // The MIC gets encrypted as block zero of the message.
  ccmEncryptData(micResult, MIC_LENGTH, 0, nonce);
}

//----------------------------------------------------------------
// The core encryption/decrytion functions

EmberStatus emberCcmEncryptAndTag(uint8_t *nonce,
                                  uint8_t *authData,
                                  uint16_t authlen,
                                  uint8_t *encryptData,
                                  uint16_t encryptlen,
                                  uint8_t *micResult)
{
  emberCcmCalculateAndEncryptMic(nonce,
                                 authData,
                                 authlen,
                                 encryptData,
                                 encryptlen,
                                 micResult);

  if (encryptlen > 0) {
    ccmEncryptData(encryptData, encryptlen, 1, nonce);
  }
  return EMBER_SUCCESS;
}

static uint8_t rxMic[MIC_LENGTH];
static uint8_t calcMic[MIC_LENGTH];

EmberStatus emberCcmAuthDecrypt(uint8_t *nonce,
                                uint8_t *authData,
                                uint16_t authlen,
                                uint8_t *encryptData,
                                uint16_t encryptlen,
                                uint8_t *mic)
{
  bool authenticated;
  ccmEncryptData(encryptData, encryptlen, 1, nonce);

  emberCcmCalculateAndEncryptMic(nonce,
                                 authData,
                                 authlen,
                                 encryptData,
                                 encryptlen,
                                 calcMic);
  authenticated = MEMCOMPARE(mic, calcMic, MIC_LENGTH) == 0;
  if (authenticated) {
    return EMBER_SUCCESS;
  } else {
    return EMBER_AUTH_FAILURE;
  }
}

// encryption / decryption on flat packets with an implicit ordering

EmberStatus emberCcmEncryptAndTagPacket(uint8_t *nonce,
                                        uint8_t *packet,
                                        uint16_t authlen,
                                        uint16_t encryptlen)
{
  return emberCcmEncryptAndTag(nonce,
                               packet,
                               authlen,
                               packet + authlen,
                               encryptlen,
                               packet + authlen + encryptlen);
}

EmberStatus emberCcmAuthDecryptPacket(uint8_t *nonce,
                                      uint8_t *packet,
                                      uint16_t authlen,
                                      uint16_t encryptlen)
{
  MEMCOPY(rxMic, packet + authlen + encryptlen, MIC_LENGTH);
  return emberCcmAuthDecrypt(nonce,
                             packet,
                             authlen,
                             packet + authlen,
                             encryptlen,
                             rxMic);
}

void emberCcmEncryptBytes(uint8_t *payload,
                          uint16_t length,
                          uint8_t* nonce)
{
  ccmEncryptData(payload, length, 1, nonce);
}
