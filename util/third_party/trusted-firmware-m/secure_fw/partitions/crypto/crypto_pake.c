/*
 * Copyright (c) 2019-2021, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <stddef.h>
#include <stdint.h>

#include "tfm_mbedcrypto_include.h"

#include "tfm_crypto_api.h"
#include "tfm_crypto_defs.h"
#include "tfm_crypto_private.h"

/*!
 * \defgroup public_psa Public functions, PSA
 *
 */

/*!@{*/
psa_status_t tfm_crypto_pake_setup(psa_invec in_vec[],
                                   size_t in_len,
                                   psa_outvec out_vec[],
                                   size_t out_len)
{
#ifdef TFM_CRYPTO_PAKE_MODULE_DISABLED
    SUPPRESS_UNUSED_IOVEC_PARAM_WARNING();
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status = PSA_SUCCESS;
    psa_pake_operation_t *operation = NULL;

    CRYPTO_IN_OUT_LEN_VALIDATE(in_len, 2, 2, out_len, 1, 1);

    if ((out_vec[0].len != sizeof(uint32_t)) ||
        (in_vec[0].len != sizeof(struct tfm_crypto_pack_iovec)) ||
        (in_vec[1].len != sizeof(psa_pake_cipher_suite_t))) {
        return PSA_ERROR_PROGRAMMER_ERROR;
    }
    const struct tfm_crypto_pack_iovec *iov = in_vec[0].base;
    uint32_t handle = iov->op_handle;
    uint32_t *handle_out = out_vec[0].base;

    const psa_pake_cipher_suite_t *cipher_suite = in_vec[1].base;

    /* Allocate the operation context in the secure world */
    status = tfm_crypto_operation_alloc(TFM_CRYPTO_PAKE_OPERATION,
                                        &handle,
                                        (void **)&operation);
    if (status != PSA_SUCCESS) {
        if (status == PSA_ERROR_BAD_STATE) {
            /* Invalidate the handle and abort the operation since the setup functon
               never gets called to perform the proper abort operation */
            /* Release the operation context, ignore if the operation fails. */
            (void)tfm_crypto_operation_release(handle_out, true);
        }
        return status;
    }
    *handle_out = handle;

    status = psa_pake_setup(operation, cipher_suite);
    if (status != PSA_SUCCESS) {
        goto exit;
    }

    return status;

exit:
    /* Release the operation context, ignore if the operation fails. */
    (void)tfm_crypto_operation_release(handle_out, true);
    return status;
#endif /* TFM_CRYPTO_PAKE_MODULE_DISABLED */
}

psa_status_t tfm_crypto_pake_set_password_key(psa_invec in_vec[],
                                              size_t in_len,
                                              psa_outvec out_vec[],
                                              size_t out_len)
{
#ifdef TFM_CRYPTO_PAKE_MODULE_DISABLED
    SUPPRESS_UNUSED_IOVEC_PARAM_WARNING();
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status = PSA_SUCCESS;
    psa_pake_operation_t *operation = NULL;

    CRYPTO_IN_OUT_LEN_VALIDATE(in_len, 2, 2, out_len, 0, 0);

    if ((in_vec[0].len != sizeof(struct tfm_crypto_pack_iovec)) ||
        (in_vec[1].len != sizeof(mbedtls_svc_key_id_t))) {
        return PSA_ERROR_PROGRAMMER_ERROR;
    }
    struct tfm_crypto_pack_iovec *iov = (struct tfm_crypto_pack_iovec *)in_vec[0].base;
    uint32_t *handle = &iov->op_handle;

    const mbedtls_svc_key_id_t *password = in_vec[1].base;

    /* Look up the corresponding operation context */
    status = tfm_crypto_operation_lookup(TFM_CRYPTO_PAKE_OPERATION,
                                         *handle,
                                         (void **)&operation);
    if (status != PSA_SUCCESS) {
        return status;
    }

    status = psa_pake_set_password_key(operation, *password);
    if (status != PSA_SUCCESS) {
        /* If the operation failed, the abort() function is called by the
           underlying crypto function so just indicate that the operation is
           invalid. */
        (void)tfm_crypto_operation_release(handle, false);
    }

    (void)out_vec;
    return status;
#endif /* TFM_CRYPTO_PAKE_MODULE_DISABLED */
}

psa_status_t tfm_crypto_pake_set_user(psa_invec in_vec[],
                                      size_t in_len,
                                      psa_outvec out_vec[],
                                      size_t out_len)
{
#ifdef TFM_CRYPTO_PAKE_MODULE_DISABLED
    SUPPRESS_UNUSED_IOVEC_PARAM_WARNING();
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status = PSA_SUCCESS;
    psa_pake_operation_t *operation = NULL;

    CRYPTO_IN_OUT_LEN_VALIDATE(in_len, 2, 2, out_len, 0, 0);

    if (in_vec[0].len != sizeof(struct tfm_crypto_pack_iovec)) {
        return PSA_ERROR_PROGRAMMER_ERROR;
    }
    struct tfm_crypto_pack_iovec *iov = (struct tfm_crypto_pack_iovec *)in_vec[0].base;
    uint32_t *handle = &iov->op_handle;

    const uint8_t *user_id = in_vec[1].base;
    size_t user_id_len = in_vec[1].len;

    /* Look up the corresponding operation context */
    status = tfm_crypto_operation_lookup(TFM_CRYPTO_PAKE_OPERATION,
                                         *handle,
                                         (void **)&operation);
    if (status != PSA_SUCCESS) {
        return status;
    }

    status = psa_pake_set_user(operation, user_id, user_id_len);
    if (status != PSA_SUCCESS) {
        /* If the operation failed, the abort() function is called by the
           underlying crypto function so just indicate that the operation is
           invalid. */
        (void)tfm_crypto_operation_release(handle, false);
    }

    (void)out_vec;
    return status;
#endif /* TFM_CRYPTO_PAKE_MODULE_DISABLED */
}

psa_status_t tfm_crypto_pake_set_peer(psa_invec in_vec[],
                                      size_t in_len,
                                      psa_outvec out_vec[],
                                      size_t out_len)
{
#ifdef TFM_CRYPTO_PAKE_MODULE_DISABLED
    SUPPRESS_UNUSED_IOVEC_PARAM_WARNING();
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status = PSA_SUCCESS;
    psa_pake_operation_t *operation = NULL;

    CRYPTO_IN_OUT_LEN_VALIDATE(in_len, 2, 2, out_len, 0, 0);

    if (in_vec[0].len != sizeof(struct tfm_crypto_pack_iovec)) {
        return PSA_ERROR_PROGRAMMER_ERROR;
    }
    struct tfm_crypto_pack_iovec *iov = (struct tfm_crypto_pack_iovec *)in_vec[0].base;
    uint32_t *handle = &iov->op_handle;

    const uint8_t *peer_id = in_vec[1].base;
    size_t peer_id_len = in_vec[1].len;

    /* Look up the corresponding operation context */
    status = tfm_crypto_operation_lookup(TFM_CRYPTO_PAKE_OPERATION,
                                         *handle,
                                         (void **)&operation);
    if (status != PSA_SUCCESS) {
        return status;
    }

    status = psa_pake_set_peer(operation, peer_id, peer_id_len);
    if (status != PSA_SUCCESS) {
        /* If the operation failed, the abort() function is called by the
           underlying crypto function so just indicate that the operation is
           invalid. */
        (void)tfm_crypto_operation_release(handle, false);
    }

    (void)out_vec;
    return status;
#endif /* TFM_CRYPTO_PAKE_MODULE_DISABLED */
}

psa_status_t tfm_crypto_pake_set_role(psa_invec in_vec[],
                                      size_t in_len,
                                      psa_outvec out_vec[],
                                      size_t out_len)
{
#ifdef TFM_CRYPTO_PAKE_MODULE_DISABLED
    SUPPRESS_UNUSED_IOVEC_PARAM_WARNING();
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status = PSA_SUCCESS;
    psa_pake_operation_t *operation = NULL;

    CRYPTO_IN_OUT_LEN_VALIDATE(in_len, 2, 2, out_len, 0, 0);

    if ((in_vec[0].len != sizeof(struct tfm_crypto_pack_iovec)) ||
        (in_vec[1].len != sizeof(psa_pake_role_t))) {
        return PSA_ERROR_PROGRAMMER_ERROR;
    }
    struct tfm_crypto_pack_iovec *iov = (struct tfm_crypto_pack_iovec *)in_vec[0].base;
    uint32_t *handle = &iov->op_handle;

    const psa_pake_role_t *role = in_vec[1].base;

    /* Look up the corresponding operation context */
    status = tfm_crypto_operation_lookup(TFM_CRYPTO_PAKE_OPERATION,
                                         *handle,
                                         (void **)&operation);
    if (status != PSA_SUCCESS) {
        return status;
    }

    status = psa_pake_set_role(operation, *role);
    if (status != PSA_SUCCESS) {
        /* If the operation failed, the abort() function is called by the
           underlying crypto function so just indicate that the operation is
           invalid. */
        (void)tfm_crypto_operation_release(handle, false);
    }

    (void)out_vec;
    return status;
#endif /* TFM_CRYPTO_PAKE_MODULE_DISABLED */
}

psa_status_t tfm_crypto_pake_output(psa_invec in_vec[],
                                    size_t in_len,
                                    psa_outvec out_vec[],
                                    size_t out_len)
{
#ifdef TFM_CRYPTO_PAKE_MODULE_DISABLED
    SUPPRESS_UNUSED_IOVEC_PARAM_WARNING();
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status = PSA_SUCCESS;
    psa_pake_operation_t *operation = NULL;

    CRYPTO_IN_OUT_LEN_VALIDATE(in_len, 1, 1, out_len, 1, 1);

    if (in_vec[0].len != sizeof(struct tfm_crypto_pack_iovec)) {
        return PSA_ERROR_PROGRAMMER_ERROR;
    }
    struct tfm_crypto_pack_iovec *iov = (struct tfm_crypto_pack_iovec *)in_vec[0].base;
    uint32_t *handle = &iov->op_handle;
    psa_pake_step_t step = (psa_pake_step_t)iov->step;
    uint8_t *output = out_vec[0].base;
    size_t output_size = out_vec[0].len;
    size_t *output_length = &out_vec[0].len;

    /* Look up the corresponding operation context */
    status = tfm_crypto_operation_lookup(TFM_CRYPTO_PAKE_OPERATION,
                                         *handle,
                                         (void **)&operation);
    if (status != PSA_SUCCESS) {
        return status;
    }

    status = psa_pake_output(operation,
                             step,
                             output,
                             output_size,
                             output_length);
    if (status != PSA_SUCCESS) {
        /* If the operation failed, the abort() function is called by the
           underlying crypto function so just indicate that the operation is
           invalid. */
        (void)tfm_crypto_operation_release(handle, false);
    }

    return status;
#endif /* TFM_CRYPTO_PAKE_MODULE_DISABLED */
}

psa_status_t tfm_crypto_pake_input(psa_invec in_vec[],
                                   size_t in_len,
                                   psa_outvec out_vec[],
                                   size_t out_len)
{
#ifdef TFM_CRYPTO_PAKE_MODULE_DISABLED
    SUPPRESS_UNUSED_IOVEC_PARAM_WARNING();
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status = PSA_SUCCESS;
    psa_pake_operation_t *operation = NULL;

    CRYPTO_IN_OUT_LEN_VALIDATE(in_len, 2, 2, out_len, 0, 0);

    if (in_vec[0].len != sizeof(struct tfm_crypto_pack_iovec)) {
        return PSA_ERROR_PROGRAMMER_ERROR;
    }
    struct tfm_crypto_pack_iovec *iov = (struct tfm_crypto_pack_iovec *)in_vec[0].base;
    uint32_t *handle = &iov->op_handle;
    psa_pake_step_t step = (psa_pake_step_t)iov->step;
    const uint8_t *input = in_vec[1].base;
    size_t input_length = in_vec[1].len;

    /* Look up the corresponding operation context */
    status = tfm_crypto_operation_lookup(TFM_CRYPTO_PAKE_OPERATION,
                                         *handle,
                                         (void **)&operation);
    if (status != PSA_SUCCESS) {
        return status;
    }

    status = psa_pake_input(operation,
                            step,
                            input,
                            input_length);
    if (status != PSA_SUCCESS) {
        /* If the operation failed, the abort() function is called by the
           underlying crypto function so just indicate that the operation is
           invalid. */
        (void)tfm_crypto_operation_release(handle, false);
    }

    (void)out_vec;
    return status;
#endif /* TFM_CRYPTO_PAKE_MODULE_DISABLED */
}

psa_status_t tfm_crypto_pake_get_implicit_key(psa_invec in_vec[],
                                              size_t in_len,
                                              psa_outvec out_vec[],
                                              size_t out_len)
{
#ifdef TFM_CRYPTO_PAKE_MODULE_DISABLED
    SUPPRESS_UNUSED_IOVEC_PARAM_WARNING();
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status = PSA_SUCCESS;
    psa_pake_operation_t *operation_pake = NULL;
    psa_key_derivation_operation_t *operation_key_derivation = NULL;

    CRYPTO_IN_OUT_LEN_VALIDATE(in_len, 2, 2, out_len, 0, 0);

    if (in_vec[0].len != sizeof(struct tfm_crypto_pack_iovec) ||
        (in_vec[1].len != sizeof(uint32_t))) {
        return PSA_ERROR_PROGRAMMER_ERROR;
    }
    struct tfm_crypto_pack_iovec *iov = (struct tfm_crypto_pack_iovec *)in_vec[0].base;
    uint32_t *handle_pake = &iov->op_handle;
    uint32_t *handle_key_derivation = (uint32_t *)in_vec[1].base;

    /* Look up the corresponding PAKE operation context */
    status = tfm_crypto_operation_lookup(TFM_CRYPTO_PAKE_OPERATION,
                                         *handle_pake,
                                         (void **)&operation_pake);
    if (status != PSA_SUCCESS) {
        return status;
    }

    /* Look up the corresponding key derivation operation context */
    status = tfm_crypto_operation_lookup(TFM_CRYPTO_KEY_DERIVATION_OPERATION,
                                         *handle_key_derivation,
                                         (void **)&operation_key_derivation);
    if (status != PSA_SUCCESS) {
        return status;
    }

    status = psa_pake_get_implicit_key(operation_pake,
                                       operation_key_derivation);

    /* We are now done with the PAKE operation. */
    (void)tfm_crypto_operation_release(handle_pake, false);

    (void)out_vec;
    return status;
#endif /* TFM_CRYPTO_PAKE_MODULE_DISABLED */
}

psa_status_t tfm_crypto_pake_derive_secret(psa_invec in_vec[],
                                           size_t in_len,
                                           psa_outvec out_vec[],
                                           size_t out_len)
{
#if defined(TFM_CRYPTO_PAKE_MODULE_DISABLED) \
  || !defined(SLI_MBEDTLS_PSA_EC_JPAKE_TLS_WORKAROUND)
    SUPPRESS_UNUSED_IOVEC_PARAM_WARNING();
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status = PSA_SUCCESS;
    psa_pake_operation_t *operation = NULL;

    CRYPTO_IN_OUT_LEN_VALIDATE(in_len, 1, 1, out_len, 1, 1);

    if (in_vec[0].len != sizeof(struct tfm_crypto_pack_iovec)) {
        return PSA_ERROR_PROGRAMMER_ERROR;
    }
    struct tfm_crypto_pack_iovec *iov = (struct tfm_crypto_pack_iovec *)in_vec[0].base;
    uint32_t *handle = &iov->op_handle;
    uint8_t *key_buf = out_vec[0].base;
    size_t key_length = out_vec[0].len;

    /* Look up the corresponding operation context */
    status = tfm_crypto_operation_lookup(TFM_CRYPTO_PAKE_OPERATION,
                                         *handle,
                                         (void **)&operation);
    if (status != PSA_SUCCESS) {
        return status;
    }

    status = psa_pake_derive_secret(operation, key_buf, key_length);

    /* We are now done with the PAKE operation. */
    (void)tfm_crypto_operation_release(handle, false);

    return status;
#endif /* TFM_CRYPTO_PAKE_MODULE_DISABLED */
}

psa_status_t tfm_crypto_pake_abort(psa_invec in_vec[],
                                   size_t in_len,
                                   psa_outvec out_vec[],
                                   size_t out_len)
{
#ifdef TFM_CRYPTO_PAKE_MODULE_DISABLED
    SUPPRESS_UNUSED_IOVEC_PARAM_WARNING();
    return PSA_ERROR_NOT_SUPPORTED;
#else
    psa_status_t status = PSA_SUCCESS;
    psa_pake_operation_t *operation = NULL;

    CRYPTO_IN_OUT_LEN_VALIDATE(in_len, 1, 1, out_len, 0, 0);

    if (in_vec[0].len != sizeof(struct tfm_crypto_pack_iovec)) {
        return PSA_ERROR_PROGRAMMER_ERROR;
    }
    const struct tfm_crypto_pack_iovec *iov = in_vec[0].base;
    uint32_t *handle = (uint32_t *)&iov->op_handle;

    /* Look up the corresponding operation context */
    status = tfm_crypto_operation_lookup(TFM_CRYPTO_PAKE_OPERATION,
                                         *handle,
                                         (void **)&operation);
    if (status != PSA_SUCCESS) {
        /* Operation does not exist, so abort has no effect */
        return PSA_SUCCESS;
    }

    status = psa_pake_abort(operation);
    if (status != PSA_SUCCESS) {
        /* Release the operation context, ignore if the operation fails. */
        (void)tfm_crypto_operation_release(handle, true);
        return status;
    }

    /* The abort() function was called by the underlying crypto function
       so just invalidate the operation */
    (void)out_vec;
    return tfm_crypto_operation_release(handle, false);
#endif /* TFM_CRYPTO_PAKE_MODULE_DISABLED */
}

/*!@}*/
