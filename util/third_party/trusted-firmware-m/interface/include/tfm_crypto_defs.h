/*
 * Copyright (c) 2018-2021, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef __TFM_CRYPTO_DEFS_H__
#define __TFM_CRYPTO_DEFS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <limits.h>
#include "tfm_api.h"
#include "psa/crypto.h"
#include "sli_tz_funcs_sids_autogen.h"

/**
 * \brief This type is used to overcome a limitation in the number of maximum
 *        IOVECs that can be used especially in psa_aead_encrypt and
 *        psa_aead_decrypt. To be removed in case the AEAD APIs number of
 *        parameters passed gets restructured
 */
#define TFM_CRYPTO_MAX_NONCE_LENGTH (16u)
struct tfm_crypto_aead_pack_input {
    uint8_t nonce[TFM_CRYPTO_MAX_NONCE_LENGTH];
    uint32_t nonce_length;
};

/**
 * \brief Structure used to pack non-pointer types in a call
 *
 */
struct tfm_crypto_pack_iovec {
    uint32_t sfn_id;             /*!< Secure function ID used to dispatch the
                                  *   request
                                  */
    uint16_t step;               /*!< Key derivation or PAKE step */
    psa_key_id_t key_id;         /*!< Key id */
    psa_algorithm_t alg;         /*!< Algorithm */
    uint32_t op_handle;          /*!< Frontend context handle associated to a
                                  *   multipart operation
                                  */
    size_t capacity;             /*!< Key derivation capacity */

    struct tfm_crypto_aead_pack_input aead_in; /*!< FixMe: Temporarily used for
                                                *   AEAD until the API is
                                                *   restructured
                                                */
};

/**
 * \brief Define an invalid value for an SID
 *
 */
#define TFM_CRYPTO_SID_INVALID (~0x0u)

/**
 * \brief This value is used to mark an handle as invalid.
 *
 */
#define TFM_CRYPTO_INVALID_HANDLE (0x0u)

/**
 * \brief The persistent key identifier that refers to the hardware unique key.
 *
 */
#define TFM_CRYPTO_KEY_ID_HUK (0xFFFF815Bu)

/**
 * \brief The algorithm identifier that refers to key derivation from the
 *        hardware unique key.
 *
 */
#define TFM_CRYPTO_ALG_HUK_DERIVATION ((psa_algorithm_t)0xB0000F00)

/**
 * \brief Define miscellaneous literal constants that are used in the service
 *
 */
enum {
    TFM_CRYPTO_NOT_IN_USE = 0,
    TFM_CRYPTO_IN_USE = 1
};

#ifdef __cplusplus
}
#endif

#endif /* __TFM_CRYPTO_DEFS_H__ */
