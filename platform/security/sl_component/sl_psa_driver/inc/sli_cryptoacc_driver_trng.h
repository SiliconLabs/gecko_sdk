/*******************************************************************************
 * @file
 * @brief Silicon Labs PSA Crypto TRNG driver functions for VSE devices.
 *******************************************************************************
 * # License
 * <b>Copyright 2024 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SLI_CRYPTOACC_DRIVER_TRNG_H_
#define SLI_CRYPTOACC_DRIVER_TRNG_H_

#include "psa/crypto.h"

#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------------
// Global Variable Declarations

/*
 * \brief
 *   Global struct to be used by functions in the LibCryptoSoC library when
 *   generating randomness.
 *
 * \note
 *   The function pointed to by tis struct expects to the CRYPTOACC peripheral
 *   to be clocked before being called.
 *
 * \attention
 *   The use of this wrapper struct should __not__ be replaced by a naive struct
 *   containing a pointer to sx_trng_fill_blk().
 *
 * \warning
 *   Since the function pointed to by this wrapper is not able (or expected) to
 *   return an error code, any errors are therefore handled by resetting the
 *   system. This is deemed appropriate since a failed randomness generation may
 *   have severe security implications.
 */
extern const struct sx_rng sli_cryptoacc_trng_wrapper;

//------------------------------------------------------------------------------
// Function Declarations

/*
 * \brief
 *   Function for getting random data from the TRNG.
 *
 * \note
 *   This function will make attempted reads until the requested amount of
 *   randomness has been collected. If the function returns successfully, it
 *   can be assumed that the full length of requested data has been written.
 *
 * \return
 *   PSA_SUCCESS if no error was encountered, else PSA_ERROR_HARDWARE_FAILURE.
 */
psa_status_t sli_cryptoacc_trng_get_random(unsigned char *output, size_t len);

#ifdef __cplusplus
}
#endif

#endif // SLI_CRYPTOACC_DRIVER_TRNG_H_
