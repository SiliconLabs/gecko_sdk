/*
 *  Copyright (c) 2023, The OpenThread Authors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 *   This file implements the OpenThread platform abstraction for PSA.
 *
 */
#include "security_manager.h"
#include <openthread-core-config.h>
#include <openthread/error.h>
#include <openthread/platform/crypto.h>
#include "utils/code_utils.h"
#include "common/debug.hpp"

#include <mbedtls/ecdsa.h>
#include <mbedtls/md.h>
#include <mbedtls/pk.h>
#include "mbedtls/psa_util.h"
#include "em_device.h"
#include "em_system.h"
#include "sl_psa_crypto.h"

#if OPENTHREAD_CONFIG_CRYPTO_LIB == OPENTHREAD_CONFIG_CRYPTO_LIB_PSA

#define PERSISTENCE_KEY_ID_USED_MAX     (7)
#define MAX_HMAC_KEY_SIZE               (32)

// Helper function to convert otCryptoKeyType to psa_key_type_t
static psa_key_type_t getPsaKeyType(otCryptoKeyType aKeyType)
{
    psa_key_type_t aPsaKeyType = 0;

    switch (aKeyType)
    {
    case OT_CRYPTO_KEY_TYPE_RAW:
        aPsaKeyType = PSA_KEY_TYPE_RAW_DATA;
        break;

    case OT_CRYPTO_KEY_TYPE_AES:
        aPsaKeyType = PSA_KEY_TYPE_AES;
        break;

    case OT_CRYPTO_KEY_TYPE_HMAC:
        aPsaKeyType = PSA_KEY_TYPE_HMAC;
        break;

    case OT_CRYPTO_KEY_TYPE_ECDSA:
        aPsaKeyType = PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1);
        break;
    }

    return aPsaKeyType;
}

// Helper function to convert aKeyAlgorithm to psa_algorithm_t
static psa_algorithm_t getPsaAlgorithm(otCryptoKeyAlgorithm aKeyAlgorithm)
{
    psa_algorithm_t aPsaKeyAlgorithm = 0;

    switch (aKeyAlgorithm)
    {
    case OT_CRYPTO_KEY_ALG_VENDOR:
        aPsaKeyAlgorithm = PSA_ALG_VENDOR_FLAG;
        break;

    case OT_CRYPTO_KEY_ALG_AES_ECB:
        aPsaKeyAlgorithm = PSA_ALG_ECB_NO_PADDING;
        break;

    case OT_CRYPTO_KEY_ALG_HMAC_SHA_256:
        aPsaKeyAlgorithm = PSA_ALG_HMAC(PSA_ALG_SHA_256);
        break;

    case OT_CRYPTO_KEY_ALG_ECDSA:
        aPsaKeyAlgorithm = PSA_ALG_ECDSA(PSA_ALG_ANY_HASH);
        break;
    }

    return aPsaKeyAlgorithm;
}

// Helper function to convert aKeyUsage to psa_key_usage_t
static psa_key_usage_t getPsaKeyUsage(int aKeyUsage)
{
    psa_key_usage_t aPsaKeyUsage = 0;

    if (aKeyUsage & OT_CRYPTO_KEY_USAGE_EXPORT)
    {
        aPsaKeyUsage |= PSA_KEY_USAGE_EXPORT;
    }

    if (aKeyUsage & OT_CRYPTO_KEY_USAGE_ENCRYPT)
    {
        aPsaKeyUsage |= PSA_KEY_USAGE_ENCRYPT;
    }

    if (aKeyUsage & OT_CRYPTO_KEY_USAGE_DECRYPT)
    {
        aPsaKeyUsage |= PSA_KEY_USAGE_DECRYPT;
    }

    if (aKeyUsage & OT_CRYPTO_KEY_USAGE_SIGN_HASH)
    {
        aPsaKeyUsage |= PSA_KEY_USAGE_SIGN_HASH;
    }

    return aPsaKeyUsage;
}

// Helper function to convert otCryptoKeyStorage to psa_key_persistence_t
static psa_key_persistence_t getPsaKeyPersistence(otCryptoKeyStorage aKeyPersistence)
{
    psa_key_persistence_t aPsaKeyPersistence = 0;

    switch (aKeyPersistence)
    {
    case OT_CRYPTO_KEY_STORAGE_VOLATILE:
        aPsaKeyPersistence = PSA_KEY_PERSISTENCE_VOLATILE;
        break;

    case OT_CRYPTO_KEY_STORAGE_PERSISTENT:
        aPsaKeyPersistence = PSA_KEY_PERSISTENCE_DEFAULT;
        break;
    }

    return aPsaKeyPersistence;
}

#if defined(SEMAILBOX_PRESENT) && !defined(SL_TRUSTZONE_NONSECURE)
static bool shouldWrap(psa_key_attributes_t *key_attr)
{
    psa_key_location_t  keyLocation = PSA_KEY_LIFETIME_GET_LOCATION(psa_get_key_lifetime(key_attr));
    psa_key_type_t      keyType = psa_get_key_type(key_attr);

    return ((keyLocation != SL_PSA_KEY_LOCATION_WRAPPED) && (keyType != PSA_KEY_TYPE_HMAC));
}

static void checkAndWrapKeys(void)
{
    for(int index = 1; index <= PERSISTENCE_KEY_ID_USED_MAX; index++)
    {
        otCryptoKeyRef          key_ref = OPENTHREAD_CONFIG_PSA_ITS_NVM_OFFSET + index;
        psa_key_attributes_t    key_attr = PSA_KEY_ATTRIBUTES_INIT;

        // If there is a key present in the location..
        if (sl_sec_man_get_key_attributes(key_ref, &key_attr) == PSA_SUCCESS)
        {
            if (shouldWrap(&key_attr))
            {
                // Wrap the key..
                otCryptoKeyRef dst_key_ref = key_ref;
                psa_key_lifetime_t key_lifetime =
                PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(PSA_KEY_PERSISTENCE_DEFAULT, SL_PSA_KEY_LOCATION_WRAPPED);

                psa_set_key_lifetime(&key_attr, key_lifetime);
                sl_sec_man_copy_key(key_ref, &key_attr, &dst_key_ref);
            }
        }
    }
}
#endif // SEMAILBOX_PRESENT && !SL_TRUSTZONE_NONSECURE

void otPlatCryptoInit(void)
{
    (void)sl_sec_man_init();

#if defined(SEMAILBOX_PRESENT) && !defined(SL_TRUSTZONE_NONSECURE)
  if (SYSTEM_GetSecurityCapability() == securityCapabilityVault) 
  {
    checkAndWrapKeys();
  }
#endif
}

static otError extractPrivateKeyFromDer(uint8_t *aPrivateKey, const uint8_t *aDer, uint8_t aDerLen)
{
    otError              error = OT_ERROR_NONE;
    mbedtls_pk_context   pk;
    mbedtls_ecp_keypair *keyPair;

    mbedtls_pk_init(&pk);

    otEXPECT_ACTION(mbedtls_pk_setup(&pk, mbedtls_pk_info_from_type(MBEDTLS_PK_ECKEY)) == 0, error = OT_ERROR_FAILED);

#if (MBEDTLS_VERSION_NUMBER >= 0x03000000)
    otEXPECT_ACTION(mbedtls_pk_parse_key(&pk, aDer, aDerLen, NULL, 0, mbedtls_psa_get_random, MBEDTLS_PSA_RANDOM_STATE)
                        == 0,
                    error = OT_ERROR_PARSE);
#else
    otEXPECT_ACTION(mbedtls_pk_parse_key(&pk, aDer, aDerLen, NULL, 0) == 0, error = OT_ERROR_PARSE);
#endif

    keyPair = mbedtls_pk_ec(pk);
    mbedtls_mpi_write_binary(&keyPair->MBEDTLS_PRIVATE(d), aPrivateKey, SL_OPENTHREAD_ECDSA_PRIVATE_KEY_SIZE);

exit:
    return error;
}

otError otPlatCryptoImportKey(otCryptoKeyRef      *aKeyId,
                              otCryptoKeyType      aKeyType,
                              otCryptoKeyAlgorithm aKeyAlgorithm,
                              int                  aKeyUsage,
                              otCryptoKeyStorage   aKeyPersistence,
                              const uint8_t       *aKey,
                              size_t               aKeyLen)
{
    otError        error = OT_ERROR_NONE;
    psa_status_t   status;
    uint8_t        aPrivateKey[SL_OPENTHREAD_ECDSA_PRIVATE_KEY_SIZE];
    const uint8_t *keyToImport = aKey;
    size_t         keySize     = aKeyLen;

    if (aKeyType == OT_CRYPTO_KEY_TYPE_ECDSA)
    {
        error       = extractPrivateKeyFromDer(aPrivateKey, aKey, aKeyLen);
        keyToImport = aPrivateKey;
        keySize     = SL_OPENTHREAD_ECDSA_PRIVATE_KEY_SIZE;
    }

    status = sl_sec_man_import_key(aKeyId,
                                   getPsaKeyType(aKeyType),
                                   getPsaAlgorithm(aKeyAlgorithm),
                                   getPsaKeyUsage(aKeyUsage),
                                   getPsaKeyPersistence(aKeyPersistence),
                                   keyToImport,
                                   keySize);

    otEXPECT_ACTION((status == PSA_SUCCESS), error = OT_ERROR_FAILED);

exit:
    return error;
}

otError otPlatCryptoExportKey(otCryptoKeyRef aKeyId, uint8_t *aBuffer, size_t aBufferLen, size_t *aKeyLen)
{
    otError      error = OT_ERROR_NONE;
    psa_status_t status;

    status = sl_sec_man_export_key(aKeyId, aBuffer, aBufferLen, aKeyLen);

    otEXPECT_ACTION((status == PSA_SUCCESS), error = OT_ERROR_FAILED);

exit:
    return error;
}

otError otPlatCryptoDestroyKey(otCryptoKeyRef aKeyId)
{
    otError      error = OT_ERROR_NONE;
    psa_status_t status;

    status = sl_sec_man_destroy_key(aKeyId);

    otEXPECT_ACTION((status == PSA_SUCCESS), error = OT_ERROR_FAILED);

exit:
    return error;
}

bool otPlatCryptoHasKey(otCryptoKeyRef aKeyRef)
{
    psa_key_attributes_t aAttr = PSA_KEY_ATTRIBUTES_INIT;

    return (sl_sec_man_get_key_attributes(aKeyRef, &aAttr) == PSA_SUCCESS);
}

// AES  Implementation
otError otPlatCryptoAesInit(otCryptoContext *aContext)
{
    otError error = OT_ERROR_NONE;
    (void)aContext;
    return error;
}

otError otPlatCryptoAesSetKey(otCryptoContext *aContext, const otCryptoKey *aKey)
{
    otError         error   = OT_ERROR_NONE;
    otCryptoKeyRef *mKeyRef = NULL;

    otEXPECT_ACTION((aContext != NULL) && (aContext->mContext != NULL), error = OT_ERROR_INVALID_ARGS);

    mKeyRef  = (otCryptoKeyRef *)aContext->mContext;
    *mKeyRef = aKey->mKeyRef;

exit:
    return error;
}

otError otPlatCryptoAesEncrypt(otCryptoContext *aContext, const uint8_t *aInput, uint8_t *aOutput)
{
    otError         error = OT_ERROR_NONE;
    psa_status_t    status;
    otCryptoKeyRef *mKeyRef = NULL;

    otEXPECT_ACTION(((aContext != NULL) && (aContext->mContext != NULL) && (aOutput != NULL) && (aInput != NULL)),
                    error = OT_ERROR_INVALID_ARGS);
    mKeyRef = (otCryptoKeyRef *)aContext->mContext;
    status  = sl_sec_man_aes_encrypt(*mKeyRef, PSA_ALG_ECB_NO_PADDING, aInput, aOutput);

    otEXPECT_ACTION((status == PSA_SUCCESS), error = OT_ERROR_FAILED);

exit:
    return error;
}

otError otPlatCryptoAesFree(otCryptoContext *aContext)
{
    otError error = OT_ERROR_NONE;
    (void)aContext;
    return error;
}

// HMAC implementations
otError otPlatCryptoHmacSha256Init(otCryptoContext *aContext)
{
    otError              error         = OT_ERROR_NONE;
    psa_mac_operation_t *mMacOperation = (psa_mac_operation_t *)aContext->mContext;
    *mMacOperation                     = psa_mac_operation_init();
    return error;
}

otError otPlatCryptoHmacSha256Deinit(otCryptoContext *aContext)
{
    otError              error         = OT_ERROR_NONE;
    psa_mac_operation_t *mMacOperation = (psa_mac_operation_t *)aContext->mContext;
    psa_status_t         status;

    status = sl_sec_man_hmac_deinit(mMacOperation);

    otEXPECT_ACTION((status == PSA_SUCCESS), error = OT_ERROR_FAILED);

exit:
    return error;
}

static psa_status_t reImportUnwrapped(const otCryptoKey *aKey, otCryptoKeyRef *aHmacKeyRef)
{
    psa_status_t         status = PSA_SUCCESS;

#if defined (SEMAILBOX_PRESENT)
    uint8_t              hmacKeyBytes[MAX_HMAC_KEY_SIZE];
    size_t               key_size;
    psa_key_attributes_t key_attr = PSA_KEY_ATTRIBUTES_INIT;

    status = sl_sec_man_get_key_attributes(aKey->mKeyRef, &key_attr);

    otEXPECT(status == PSA_SUCCESS);

    status = sl_sec_man_export_key(aKey->mKeyRef,
                                   hmacKeyBytes,
                                   sizeof(hmacKeyBytes),
                                   &key_size);

    otEXPECT(status == PSA_SUCCESS);

    status = sl_sec_man_import_key( aHmacKeyRef,
                                    psa_get_key_type(&key_attr),
                                    psa_get_key_algorithm(&key_attr),
                                    psa_get_key_usage_flags(&key_attr),
                                    PSA_KEY_PERSISTENCE_VOLATILE,
                                    hmacKeyBytes,
                                    key_size);

    memset(hmacKeyBytes, 0, sizeof(hmacKeyBytes));
    
    otEXPECT(status == PSA_SUCCESS);

exit:
#else
    *aHmacKeyRef = aKey->mKeyRef;
#endif
    return status;
}

otError otPlatCryptoHmacSha256Start(otCryptoContext *aContext, const otCryptoKey *aKey)
{
    otError              error         = OT_ERROR_NONE;
    psa_mac_operation_t *mMacOperation = (psa_mac_operation_t *)aContext->mContext;
    psa_status_t         status;
    otCryptoKeyRef       hmacKeyRef;

    status = reImportUnwrapped(aKey, &hmacKeyRef);
    otEXPECT_ACTION((status == PSA_SUCCESS), error = OT_ERROR_FAILED);

    status = sl_sec_man_hmac_start(mMacOperation, hmacKeyRef);
    otEXPECT_ACTION((status == PSA_SUCCESS), error = OT_ERROR_FAILED);

#if defined (SEMAILBOX_PRESENT)
    sl_sec_man_destroy_key(hmacKeyRef);
#else
    hmacKeyRef = 0;
#endif

exit:
    return error;
}

otError otPlatCryptoHmacSha256Update(otCryptoContext *aContext, const void *aBuf, uint16_t aBufLength)
{
    otError              error         = OT_ERROR_NONE;
    psa_mac_operation_t *mMacOperation = (psa_mac_operation_t *)aContext->mContext;
    psa_status_t         status;

    status = sl_sec_man_hmac_update(mMacOperation, (const uint8_t *)aBuf, (size_t)aBufLength);

    otEXPECT_ACTION((status == PSA_SUCCESS), error = OT_ERROR_FAILED);

exit:
    return error;
}

otError otPlatCryptoHmacSha256Finish(otCryptoContext *aContext, uint8_t *aBuf, size_t aBufLength)
{
    otError              error         = OT_ERROR_NONE;
    psa_mac_operation_t *mMacOperation = (psa_mac_operation_t *)aContext->mContext;
    psa_status_t         status;

    status = sl_sec_man_hmac_finish(mMacOperation, aBuf, aBufLength);

    otEXPECT_ACTION((status == PSA_SUCCESS), error = OT_ERROR_FAILED);

exit:
    return error;
}

// HKDF platform implementations
// As the HKDF does not actually use mbedTLS APIs but uses HMAC module, this feature is not implemented.
otError otPlatCryptoHkdfExpand(otCryptoContext *aContext,
                               const uint8_t   *aInfo,
                               uint16_t         aInfoLength,
                               uint8_t         *aOutputKey,
                               uint16_t         aOutputKeyLength)
{
    otError      error = OT_ERROR_NONE;
    psa_status_t status;

    otEXPECT_ACTION(((aContext != NULL) && (aContext->mContext != NULL) && (aInfo != NULL) && (aOutputKey != NULL)),
                    error = OT_ERROR_INVALID_ARGS);

    status = sl_sec_man_key_derivation_expand(aContext->mContext, aInfo, aInfoLength, aOutputKey, aOutputKeyLength);

    otEXPECT_ACTION((status == PSA_SUCCESS), error = OT_ERROR_FAILED);

exit:
    return error;
}

otError otPlatCryptoHkdfExtract(otCryptoContext   *aContext,
                                const uint8_t     *aSalt,
                                uint16_t           aSaltLength,
                                const otCryptoKey *aKey)
{
    otError      error = OT_ERROR_NONE;
    psa_status_t status;

    otEXPECT_ACTION(
        ((aContext != NULL) && (aContext->mContext != NULL) && (aKey != NULL) && (aSalt != NULL) && (aSaltLength != 0)),
        error = OT_ERROR_INVALID_ARGS);

    status = sl_sec_man_key_derivation_extract(aContext->mContext, PSA_ALG_SHA_256, aKey->mKeyRef, aSalt, aSaltLength);

    otEXPECT_ACTION((status == PSA_SUCCESS), error = OT_ERROR_FAILED);

exit:
    return error;
}

// SHA256 platform implementations
otError otPlatCryptoSha256Init(otCryptoContext *aContext)
{
    otError error = OT_ERROR_NONE;
    otEXPECT_ACTION((aContext != NULL), error = OT_ERROR_INVALID_ARGS);
    psa_hash_operation_t *ctx = (psa_hash_operation_t *)aContext->mContext;

    otEXPECT_ACTION((ctx != NULL), error = OT_ERROR_INVALID_ARGS);

    *ctx = sl_sec_man_hash_init();

exit:
    return error;
}

otError otPlatCryptoSha256Deinit(otCryptoContext *aContext)
{
    otError error = OT_ERROR_NONE;
    otEXPECT_ACTION((aContext != NULL), error = OT_ERROR_INVALID_ARGS);
    psa_hash_operation_t *ctx = (psa_hash_operation_t *)aContext->mContext;

    otEXPECT_ACTION((ctx != NULL), error = OT_ERROR_INVALID_ARGS);
    otEXPECT_ACTION((sl_sec_man_hash_deinit(ctx) == PSA_SUCCESS), error = OT_ERROR_FAILED);

exit:
    return error;
}

otError otPlatCryptoSha256Start(otCryptoContext *aContext)
{
    otError error = OT_ERROR_NONE;
    otEXPECT_ACTION((aContext != NULL), error = OT_ERROR_INVALID_ARGS);
    psa_hash_operation_t *ctx = (psa_hash_operation_t *)aContext->mContext;

    otEXPECT_ACTION((ctx != NULL), error = OT_ERROR_INVALID_ARGS);
    otEXPECT_ACTION((sl_sec_man_hash_start(ctx, PSA_ALG_SHA_256) == PSA_SUCCESS), error = OT_ERROR_FAILED);

exit:
    return error;
}

otError otPlatCryptoSha256Update(otCryptoContext *aContext, const void *aBuf, uint16_t aBufLength)
{
    otError error = OT_ERROR_NONE;
    otEXPECT_ACTION((aContext != NULL), error = OT_ERROR_INVALID_ARGS);
    psa_hash_operation_t *ctx = (psa_hash_operation_t *)aContext->mContext;

    otEXPECT_ACTION(((ctx != NULL) && (aBuf != NULL)), error = OT_ERROR_INVALID_ARGS);
    otEXPECT_ACTION((sl_sec_man_hash_update(ctx, (uint8_t *)aBuf, aBufLength) == PSA_SUCCESS), error = OT_ERROR_FAILED);

exit:
    return error;
}

otError otPlatCryptoSha256Finish(otCryptoContext *aContext, uint8_t *aHash, uint16_t aHashSize)
{
    otError error       = OT_ERROR_NONE;
    size_t  aHashLength = 0;
    otEXPECT_ACTION((aContext != NULL), error = OT_ERROR_INVALID_ARGS);
    psa_hash_operation_t *ctx = (psa_hash_operation_t *)aContext->mContext;

    otEXPECT_ACTION(((ctx != NULL) && (aHash != NULL)), error = OT_ERROR_INVALID_ARGS);
    otEXPECT_ACTION((sl_sec_man_hash_finish(ctx, aHash, aHashSize, &aHashLength) == PSA_SUCCESS),
                    error = OT_ERROR_FAILED);

exit:
    return error;
}

otError otPlatCryptoEcdsaGenerateAndImportKey(otCryptoKeyRef aKeyRef)
{
    otError      error      = OT_ERROR_NONE;
    size_t       aKeyLength = 256;
    psa_status_t status;

    status = sl_sec_man_generate_key(&aKeyRef,
                                     PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1),
                                     PSA_ALG_ECDSA(PSA_ALG_ANY_HASH),
                                     (PSA_KEY_USAGE_SIGN_HASH | PSA_KEY_USAGE_VERIFY_HASH),
                                     PSA_KEY_LIFETIME_PERSISTENT,
                                     aKeyLength);

    otEXPECT_ACTION((status == PSA_SUCCESS), error = OT_ERROR_FAILED);

exit:
    return error;
}

otError otPlatCryptoEcdsaExportPublicKey(otCryptoKeyRef aKeyRef, otPlatCryptoEcdsaPublicKey *aPublicKey)
{
    otError      error = OT_ERROR_NONE;
    size_t       aKeyLength;
    psa_status_t status;
    uint8_t      aByteArray[OT_CRYPTO_ECDSA_PUBLIC_KEY_SIZE + 1];

    otEXPECT_ACTION((aPublicKey != NULL), error = OT_ERROR_INVALID_ARGS);

    // Use byte array to get the public key because PSA adds a encoding header at the beginning of the array.
    // It is easier to export it to a byte array and copy only the public key to output array.
    status = sl_sec_man_export_public_key(aKeyRef, aByteArray, sizeof(aByteArray), &aKeyLength);

    memcpy(aPublicKey->m8, &aByteArray[1], OT_CRYPTO_ECDSA_PUBLIC_KEY_SIZE);
    otEXPECT_ACTION((status == PSA_SUCCESS), error = OT_ERROR_FAILED);

exit:
    return error;
}

otError otPlatCryptoEcdsaSignUsingKeyRef(otCryptoKeyRef                aKeyRef,
                                         const otPlatCryptoSha256Hash *aHash,
                                         otPlatCryptoEcdsaSignature   *aSignature)
{
    otError      error = OT_ERROR_NONE;
    size_t       aSignatureLength;
    psa_status_t status;
    bool         aIsHash = true;

    otEXPECT_ACTION(((aHash != NULL) && (aSignature != NULL)), error = OT_ERROR_INVALID_ARGS);

    status = sl_sec_man_sign(aKeyRef,
                             PSA_ALG_ECDSA(PSA_ALG_SHA_256),
                             aHash->m8,
                             sizeof(aHash->m8),
                             aSignature->m8,
                             sizeof(aSignature->m8),
                             &aSignatureLength,
                             aIsHash);

    otEXPECT_ACTION((status == PSA_SUCCESS), error = OT_ERROR_FAILED);

exit:
    return error;
}

otError otPlatCryptoEcdsaVerifyUsingKeyRef(otCryptoKeyRef                    aKeyRef,
                                           const otPlatCryptoSha256Hash     *aHash,
                                           const otPlatCryptoEcdsaSignature *aSignature)
{
    otError      error = OT_ERROR_NONE;
    psa_status_t status;
    bool         aIsHash = true;

    otEXPECT_ACTION(((aHash != NULL) && (aSignature != NULL)), error = OT_ERROR_INVALID_ARGS);

    // Verify the signature.
    status = sl_sec_man_verify(aKeyRef,
                               PSA_ALG_ECDSA(PSA_ALG_SHA_256),
                               aHash->m8,
                               sizeof(aHash->m8),
                               aSignature->m8,
                               sizeof(aSignature->m8),
                               aIsHash);

    otEXPECT_ACTION((status == PSA_SUCCESS), error = OT_ERROR_FAILED);

exit:
    return error;
}

void otPlatCryptoPbkdf2GenerateKey( const uint8_t *aPassword,
                                    uint16_t       aPasswordLen,
                                    const uint8_t *aSalt,
                                    uint16_t       aSaltLen,
                                    uint32_t       aIterationCounter,
                                    uint16_t       aKeyLen,
                                    uint8_t       *aKey)
{
    psa_status_t    status;
    size_t          outSize;
    psa_key_id_t    passwordKeyId = 0;
    psa_key_id_t    saltKeyId = 0;
    psa_key_id_t    keyId = 0;

    // Algorithm is PBKDF2-AES-CMAC-PRF-128
    psa_algorithm_t algo = PSA_ALG_PBKDF2_AES_CMAC_PRF_128;

    // Initialize key derivation
    psa_key_derivation_operation_t operation = psa_key_derivation_operation_init();
    status = psa_key_derivation_setup(&operation, algo);
    OT_ASSERT(status == PSA_SUCCESS);

    // Set capacity
    status = psa_key_derivation_set_capacity(&operation, aKeyLen);
    OT_ASSERT(status == PSA_SUCCESS);

    // Set iteration count as cost
    status = psa_key_derivation_input_integer(&operation,
                                                PSA_KEY_DERIVATION_INPUT_COST,
                                                aIterationCounter);
    OT_ASSERT(status == PSA_SUCCESS);

    // Create salt as a key
    psa_key_attributes_t saltKeyAttr = psa_key_attributes_init();
    psa_set_key_usage_flags(&saltKeyAttr, PSA_KEY_USAGE_DERIVE);
    psa_set_key_type(&saltKeyAttr, PSA_KEY_TYPE_RAW_DATA);
    psa_set_key_algorithm(&saltKeyAttr, algo);
    OT_ASSERT(status == PSA_SUCCESS);

    status = psa_import_key(&saltKeyAttr,
                            aSalt,
                            aSaltLen,
                            &saltKeyId);
    OT_ASSERT(status == PSA_SUCCESS);

    // Provide salt
    status = psa_key_derivation_input_key(&operation,
                                            PSA_KEY_DERIVATION_INPUT_SALT,
                                            saltKeyId);
    OT_ASSERT(status == PSA_SUCCESS);

    // Create key for password (key)
    psa_key_attributes_t passwordKeyAttr = psa_key_attributes_init();
    psa_set_key_usage_flags(&passwordKeyAttr, PSA_KEY_USAGE_DERIVE);
    psa_set_key_type(&passwordKeyAttr, PSA_KEY_TYPE_PASSWORD);
    psa_set_key_algorithm(&passwordKeyAttr, algo);

    status = psa_import_key(&passwordKeyAttr,
                            aPassword,
                            aPasswordLen,
                            &passwordKeyId);
    OT_ASSERT(status == PSA_SUCCESS);

    // Provide password (key)
    status = psa_key_derivation_input_key(&operation,
                                            PSA_KEY_DERIVATION_INPUT_PASSWORD,
                                            passwordKeyId);
    OT_ASSERT(status == PSA_SUCCESS);

    // Configure output as a key
    psa_key_attributes_t keyAttrResult = psa_key_attributes_init();
    psa_set_key_bits(&keyAttrResult, (8 * aKeyLen));
    psa_set_key_usage_flags(&keyAttrResult, PSA_KEY_USAGE_EXPORT);
    psa_set_key_type(&keyAttrResult, PSA_KEY_TYPE_RAW_DATA);
    psa_set_key_algorithm(&keyAttrResult, PSA_ALG_CTR);

    status = psa_key_derivation_output_key(&keyAttrResult,
                                            &operation,
                                            &keyId);
    OT_ASSERT(status == PSA_SUCCESS);

    // Export output key
    status = psa_export_key(keyId,
                            aKey,
                            aKeyLen,
                            &outSize);
    OT_ASSERT(status == PSA_SUCCESS);

    // Release keys used
    psa_destroy_key(keyId);
    psa_destroy_key(saltKeyId);
    psa_destroy_key(passwordKeyId);
}

#endif // OPENTHREAD_CONFIG_PLATFORM_KEY_REFERENCES_ENABLE
