/***************************************************************************//**
 * @file app_certificates.h
 * @brief Application certificate store
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef APP_CERTIFICATE_STORE_H
#define APP_CERTIFICATE_STORE_H

#include <stdint.h>
#include "sl_status.h"
#include "sl_wisun_api.h"
#include "app_certificate.h"

/// Maximum amount of certificates
#define APP_CERTIFICATE_STORE_MAX_INDEX 5

/// NVM key base address
#define APP_CERTIFICATE_STORE_NVM_KEY_BASE 0x00000100U

/// Compile-time default certificates
extern const char * const app_certificate_store_default[APP_CERTIFICATE_STORE_MAX_INDEX];

/**************************************************************************//**
 * Compile-time default certificates.
 * The array must contain pointers to PEM-formatted certificates, non-existing
 * indexes must contain a NULL pointer.
 *
 * Example:
 * const char * const app_certificate_store_default[APP_CERTIFICATE_STORE_MAX_INDEX] =
 * {
 *   (const char *)WISUN_ROOT_CERTIFICATE,
 *   NULL,
 *   NULL,
 *   NULL,
 *   NULL
 * };
 *
 *
 *****************************************************************************/

/**************************************************************************//**
 * Initialize certificate store.
 *****************************************************************************/
void app_certificate_store_init();

/**************************************************************************//**
 * Reset certificate store to build-time configuration.
 *****************************************************************************/
void app_certificate_store_reset();

/**************************************************************************//**
 * List all certificates in the store.
 *****************************************************************************/
void app_certificate_store_list();

/**************************************************************************//**
 * Retrieve an individual certificate from the store.
 *
 * @param index Index of the certificate, from 0 to APP_CERTIFICATE_STORE_MAX_INDEX - 1
 * @return Pointer the certificate, NULL if none found. Ownership is transferred.
 *****************************************************************************/
app_certificate_t *app_certificate_store_get(uint8_t index);

/**************************************************************************//**
 * Store a certificate to the store.
 *
 * @param index Index of the certificate, from 0 to APP_CERTIFICATE_STORE_MAX_INDEX - 1
 * @param certificate Pointer the certificate to store.
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t app_certificate_store_set(uint8_t index,
                                      const app_certificate_t* certificate);

/**************************************************************************//**
 * Remove a certificate from the store.
 *
 * @param index Bit mask of indexes to remove.
 * @return SL_STATUS_OK if successful, an error code otherwise
 *****************************************************************************/
sl_status_t app_certificate_store_remove(uint8_t index_mask);

#endif  // APP_CERTIFICATE_STORE_H
