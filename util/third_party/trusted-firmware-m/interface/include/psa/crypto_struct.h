/*
 * Copyright (c) 2018-2022, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
/**
 * \file psa/crypto_struct.h
 *
 * \brief PSA cryptography module: structured type implementations
 *
 * \note This file may not be included directly. Applications must
 * include psa/crypto.h.
 *
 * This file contains the definitions of some data structures with
 * implementation-specific definitions.
 *
 * In implementations with isolation between the application and the
 * cryptography module, it is expected that the front-end and the back-end
 * would have different versions of this file.
 */

#if defined(SL_TRUSTZONE_SECURE)
/* The Secure library must use the standard crypto_struct.h from the mbedtls repo. */
#include "mbedtls/include/psa/crypto_struct.h"

#else /* SL_TRUSTZONE_SECURE */

#ifndef PSA_CRYPTO_STRUCT_H
#define PSA_CRYPTO_STRUCT_H

#ifdef __cplusplus
extern "C" {
#endif

/* If present, include the customised Mbed TLS configuration file here
 * since there are a few conditions. Also other mbedtls support files
 * like sl_psa_values.h */
#if defined(MBEDTLS_CONFIG_FILE)
#include MBEDTLS_CONFIG_FILE
#endif

/*
 * Note that the below structures are different from the decalrations in
 * mbed-crypto. This is because TF-M maintains 'front-end' and 'back-end'
 * versions of this header. In the front-end version, exported to NS
 * clients in interface/include/psa, a crypto operation is defined as an
 * opaque handle to a context in the Crypto service. The back-end
 * version, directly included from the mbed-crypto repo by the Crypto
 * service, contains the full definition of the operation structs.
 *
 * One of the functions of the Crypto service is to allocate the back-end
 * operation contexts in its own partition memory (in crypto_alloc.c),
 * and then do the mapping between front-end operation handles passed by
 * NS clients and the corresponding back-end operation contexts. The
 * advantage of doing it this way is that internal mbed-crypto state is never
 * exposed to the NS client.
 */

struct psa_hash_operation_s
{
    uint32_t handle;
};

#define PSA_HASH_OPERATION_INIT {0}
static inline struct psa_hash_operation_s psa_hash_operation_init(void)
{
    const struct psa_hash_operation_s v = PSA_HASH_OPERATION_INIT;
    return v;
}

struct psa_mac_operation_s
{
    uint32_t handle;
};

#define PSA_MAC_OPERATION_INIT {0}
static inline struct psa_mac_operation_s psa_mac_operation_init(void)
{
    const struct psa_mac_operation_s v = PSA_MAC_OPERATION_INIT;
    return v;
}

struct psa_cipher_operation_s
{
    uint32_t handle;
};

#define PSA_CIPHER_OPERATION_INIT {0}
static inline struct psa_cipher_operation_s psa_cipher_operation_init(void)
{
    const struct psa_cipher_operation_s v = PSA_CIPHER_OPERATION_INIT;
    return v;
}

struct psa_aead_operation_s
{
    uint32_t handle;
};

#define PSA_AEAD_OPERATION_INIT {0}
static inline struct psa_aead_operation_s psa_aead_operation_init(void)
{
    const struct psa_aead_operation_s v = PSA_AEAD_OPERATION_INIT;
    return v;
}

struct psa_key_derivation_s
{
    uint32_t handle;
};

#define PSA_KEY_DERIVATION_OPERATION_INIT {0}
static inline struct psa_key_derivation_s psa_key_derivation_operation_init(void)
{
    const struct psa_key_derivation_s v = PSA_KEY_DERIVATION_OPERATION_INIT;
    return v;
}

/* The type used internally for key sizes.
 * Public interfaces use size_t, but internally we use a smaller type. */
typedef uint16_t psa_key_bits_t;
/* The maximum value of the type used to represent bit-sizes.
 * This is used to mark an invalid key size. */
#define PSA_KEY_BITS_TOO_LARGE          ((psa_key_bits_t) -1)
/* The maximum size of a key in bits.
 * Currently defined as the maximum that can be represented, rounded down
 * to a whole number of bytes.
 * This is an uncast value so that it can be used in preprocessor
 * conditionals. */
#ifndef PSA_MAX_KEY_BITS
#define PSA_MAX_KEY_BITS 0xfff8
#endif

/* On the client side, only some key attributes are visible.
 * The server has a different definition of psa_key_attributes_s which
 * maintains more attributes.
 */
#include "crypto_client_struct.h"
struct psa_key_attributes_s {
    struct psa_client_key_attributes_s client;
};

#define PSA_KEY_ATTRIBUTES_INIT {PSA_CLIENT_KEY_ATTRIBUTES_INIT}

static inline struct psa_key_attributes_s psa_key_attributes_init(void)
{
    const struct psa_key_attributes_s v = PSA_KEY_ATTRIBUTES_INIT;
    return v;
}

static inline void psa_set_key_id(psa_key_attributes_t *attributes,
                                  mbedtls_svc_key_id_t key)
{
    psa_key_lifetime_t lifetime = attributes->client.lifetime;

    attributes->client.id = (psa_key_id_t)key;

    if (PSA_KEY_LIFETIME_IS_VOLATILE(lifetime))
    {
        attributes->client.lifetime =
            PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(
                PSA_KEY_LIFETIME_PERSISTENT,
                PSA_KEY_LIFETIME_GET_LOCATION(lifetime));
    }
}

static inline mbedtls_svc_key_id_t psa_get_key_id(
    const psa_key_attributes_t *attributes)
{
    return (mbedtls_svc_key_id_t)attributes->client.id;
}

static inline void psa_set_key_lifetime(psa_key_attributes_t *attributes,
                                        psa_key_lifetime_t lifetime)
{
    attributes->client.lifetime = lifetime;
    if (PSA_KEY_LIFETIME_IS_VOLATILE(lifetime))
    {
        attributes->client.id = 0;
    }
}

static inline psa_key_lifetime_t psa_get_key_lifetime(
    const psa_key_attributes_t *attributes)
{
    return attributes->client.lifetime;
}

static inline void psa_extend_key_usage_flags(psa_key_usage_t *usage_flags)
{
    if (*usage_flags & PSA_KEY_USAGE_SIGN_HASH) {
        *usage_flags |= PSA_KEY_USAGE_SIGN_MESSAGE;
    }

    if (*usage_flags & PSA_KEY_USAGE_VERIFY_HASH) {
        *usage_flags |= PSA_KEY_USAGE_VERIFY_MESSAGE;
    }
}

static inline void psa_set_key_usage_flags(psa_key_attributes_t *attributes,
                                           psa_key_usage_t usage_flags)
{
    psa_extend_key_usage_flags(&usage_flags);
    attributes->client.usage = usage_flags;
}

static inline psa_key_usage_t psa_get_key_usage_flags(
    const psa_key_attributes_t *attributes)
{
    return attributes->client.usage;
}

static inline void psa_set_key_algorithm(psa_key_attributes_t *attributes,
                                         psa_algorithm_t alg)
{
    attributes->client.alg = alg;
}

static inline psa_algorithm_t psa_get_key_algorithm(
    const psa_key_attributes_t *attributes)
{
    return attributes->client.alg;
}

static inline void psa_set_key_type(psa_key_attributes_t *attributes,
                                    psa_key_type_t type)
{
    attributes->client.type = type;
}

static inline psa_key_type_t psa_get_key_type(
    const psa_key_attributes_t *attributes)
{
    return attributes->client.type;
}

static inline void psa_set_key_bits(psa_key_attributes_t *attributes,
                                    size_t bits)
{
    if (bits > PSA_MAX_KEY_BITS) {
        attributes->client.bits = PSA_KEY_BITS_TOO_LARGE;
    } else {
        attributes->client.bits = bits;
    }
}

static inline size_t psa_get_key_bits(
    const psa_key_attributes_t *attributes)
{
    return attributes->client.bits;
}

#ifdef __cplusplus
}
#endif

#endif /* PSA_CRYPTO_STRUCT_H */

#endif /* SL_TRUSTZONE_SECURE */
