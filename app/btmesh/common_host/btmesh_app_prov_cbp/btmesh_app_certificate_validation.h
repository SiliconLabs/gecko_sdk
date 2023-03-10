/**************************************************************************//**
 * @file
 * @brief BT Mesh Host Provisioner component - Certificate Validation
 ******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
 ******************************************************************************
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
 *****************************************************************************/
#ifndef CERTIFICATE_VALIDATION_H
#define CERTIFICATE_VALIDATION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sl_status.h"
#include "sl_bgapi.h"

/***************************************************************************//**
* Validate the received certificate and extract public key
*
* @param[in] raw_cert Pointer to the device certificate
* @param[in] cert_len Length of the certificate
* @param[in] root_cert_path Path of the root certificate
* @param[in] uuid UUID of the device
* @param[in] key_size size of pub_key in bytes
* @param[out] pub_key Pointer to the extracted public key
* @return Status of the validation and kex extraction
*******************************************************************************/
sl_status_t btmesh_prov_validate_certificate(const unsigned char *raw_cert,
                                             size_t cert_len,
                                             const char *root_cert_path,
                                             uuid_128 *uuid,
                                             size_t key_size,
                                             uint8_t *pub_key);

#ifdef __cplusplus
}
#endif

#endif //CERTIFICATE_VALIDATION_H
