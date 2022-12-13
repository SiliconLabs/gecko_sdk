/***************************************************************************//**
 * @file app_certificates.c
 * @brief Application certificate handler
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mbedtls/x509_crt.h"
#include "mbedtls/ecp.h"
#include "mbedtls/private_access.h"
#include "mbedtls/psa_util.h"
#include "sl_malloc.h"
#include "sl_wisun_cli_util.h"
#include "app_certificate.h"

app_certificate_t *app_certificate_init(const uint16_t data_length)
{
  app_certificate_t *cert;
  size_t cert_size = sizeof(app_certificate_t) + data_length + 1;

  cert = sl_malloc(cert_size);
  if (!cert) {
    // Unable to allocate a certificate.
    return NULL;
  }

  // Always NULL-terminate the certificate data
  memset(cert, 0, cert_size);
  cert->data_length = 1;

  return cert;
}

uint8_t *app_certificate_data(app_certificate_t *certificate)
{
  return certificate->data;
}

sl_status_t app_certificate_append(app_certificate_t *certificate,
                                   uint16_t data_length)
{
  certificate->data_length += data_length;
  certificate->data_offset += data_length;

  return SL_STATUS_OK;
}

sl_status_t app_certificate_append_data(app_certificate_t *certificate,
                                        const char *data,
                                        uint16_t data_length)
{
  memcpy(&certificate->data[certificate->data_offset], data, data_length);
  app_certificate_append(certificate, data_length);

  return SL_STATUS_OK;
}

sl_status_t app_certificate_append_string(app_certificate_t *certificate,
                                          const char *data)
{
  memcpy(&certificate->data[certificate->data_offset], data, strlen(data));
  app_certificate_append(certificate, strlen(data));

  // Always terminate a string with a linefeed
  if ((certificate->data_offset) &&
      (certificate->data[certificate->data_offset - 1] != '\n')) {
    certificate->data[certificate->data_offset] = '\n';
    app_certificate_append(certificate, 1);
  }

  return SL_STATUS_OK;
}

void app_certificate_free(app_certificate_t *certificate)
{
  free(certificate);
}

sl_status_t app_certificate_parse(const app_certificate_t *certificate,
                                  app_certicate_info_t *info)
{
  mbedtls_x509_crt crt;
  mbedtls_pk_context pk;
  mbedtls_pk_context *pk_parse = NULL;
  mbedtls_ecp_keypair *ecp;
  const mbedtls_ecp_curve_info *ecp_info;
  mbedtls_pk_type_t algorithm;
  sl_status_t ret = SL_STATUS_FAIL;
  int err;

  memset(info, 0, sizeof(app_certicate_info_t));

  mbedtls_x509_crt_init(&crt);
  mbedtls_pk_init(&pk);

  // Validate the certificate data by parsing it
  err = mbedtls_x509_crt_parse(&crt, certificate->data, certificate->data_length);
  if (!err) {
    if (crt.MBEDTLS_PRIVATE(ca_istrue)) {
      // CA attribute is set, thus this is a trusted certificate.
      info->type = app_certificate_type_trusted;
    } else {
      // CA attribute is NOT set, has to be a device certificate.
      info->type = app_certificate_type_device;
    }
    // Subject might not exist, ignore any error
    (void)mbedtls_x509_dn_gets(info->subject, APP_CERTIFICATE_MAX_SUBJECT_LENGTH, &crt.subject);
    // Parsed information is based on the public key
    pk_parse = &crt.pk;
  } else {
    // Not a valid certificate. Perhaps a private key?
    err = mbedtls_pk_parse_key(&pk, certificate->data, certificate->data_length, NULL, 0, mbedtls_psa_get_random, MBEDTLS_PSA_RANDOM_STATE);
    if (!err) {
      // Looks like a device private key.
      info->type = app_certificate_type_device_pk;
      // Parsed information is based on the private key
      pk_parse = &pk;
    }
  }

  if (pk_parse) {
    algorithm = mbedtls_pk_get_type(pk_parse);
    if ((algorithm == MBEDTLS_PK_ECKEY) ||
        (algorithm == MBEDTLS_PK_ECKEY_DH) ||
        (algorithm == MBEDTLS_PK_ECDSA)) {
      // Parse the curve used in EC certificates
      ecp = mbedtls_pk_ec(*pk_parse);
      ecp_info = mbedtls_ecp_curve_info_from_grp_id(ecp->MBEDTLS_PRIVATE(grp).id);
      sprintf(info->algorithm, "%s (%s)", mbedtls_pk_get_name(pk_parse),
              ecp_info->name);
    } else {
      // Otherwise just use to algorithm name
      strcpy(info->algorithm, mbedtls_pk_get_name(pk_parse));
    }

    info->bitlen = mbedtls_pk_get_bitlen(pk_parse);
    ret = SL_STATUS_OK;
  }

  mbedtls_pk_free(&pk);
  mbedtls_x509_crt_free(&crt);

  return ret;
}

