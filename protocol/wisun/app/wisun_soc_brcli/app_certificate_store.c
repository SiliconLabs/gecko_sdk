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
#include "nvm3.h"
#include "sl_common.h"
#include "sl_wisun_cli_util.h"
#include "sl_wisun_test_certificates.h"
#include "app_certificate_store.h"

static const app_enum_t app_certificate_type_enum[] =
{
  { "[TRUSTED]", app_certificate_type_trusted },
  { "[DEVICE]", app_certificate_type_device },
  { "[DEVICEPK]", app_certificate_type_device_pk },
  { NULL, 0 }
};

SL_WEAK const char * const app_certificate_store_default[APP_CERTIFICATE_STORE_MAX_INDEX] =
{
  (const char *)WISUN_ROOT_CERTIFICATE,
  (const char *)WISUN_SERVER_CERTIFICATE,
  (const char *)WISUN_SERVER_KEY,
  NULL,
  NULL,
};

static app_certificate_t *app_certificate_store_default_get(uint8_t index)
{
  app_certificate_t *cert;
  uint16_t size;

  if (!app_certificate_store_default[index]) {
    return NULL;
  }

  size = strlen(app_certificate_store_default[index]);

  cert = app_certificate_init(size);
  if (!cert) {
    return NULL;
  }

  app_certificate_append_data(cert, app_certificate_store_default[index], size);

  return cert;
}

static sl_status_t app_certificate_store_nvm_set(uint8_t index,
                                                 const app_certificate_t *certificate)
{
  nvm3_ObjectKey_t handle;
  Ecode_t ret;

  handle = (nvm3_ObjectKey_t)(APP_CERTIFICATE_STORE_NVM_KEY_BASE + index);

  if (certificate) {
    // The terminating NULL byte is not written to NVM
    ret = nvm3_writeData(nvm3_defaultHandle,
                         handle,
                         certificate->data,
                         certificate->data_length - 1);
    if (ret != ECODE_NVM3_OK) {
      return SL_STATUS_FAIL;
    }
  } else {
    // Delete the certificate index by writing a zero-length entry
    ret = nvm3_writeData(nvm3_defaultHandle,
                         handle,
                         NULL,
                         0);
    if (ret != ECODE_NVM3_OK) {
      return SL_STATUS_FAIL;
    }
  }

  return SL_STATUS_OK;
}

static app_certificate_t *app_certificate_store_nvm_get(uint8_t index)
{
  nvm3_ObjectKey_t handle;
  app_certificate_t *cert;
  uint32_t nvm_type;
  size_t nvm_size;
  Ecode_t ret;

  handle = (nvm3_ObjectKey_t)(APP_CERTIFICATE_STORE_NVM_KEY_BASE + index);

  ret = nvm3_getObjectInfo(nvm3_defaultHandle,
                           handle,
                           &nvm_type,
                           &nvm_size);
  if (ret != ECODE_NVM3_OK) {
    return NULL;
  }

  cert = app_certificate_init(nvm_size);
  if (!cert) {
    return NULL;
  }

  ret = nvm3_readData(nvm3_defaultHandle,
                      handle,
                      app_certificate_data(cert),
                      nvm_size);
  if (ret != ECODE_NVM3_OK) {
    app_certificate_free(cert);
    return NULL;
  }

  app_certificate_append(cert, nvm_size);

  return cert;
}

void app_certificate_store_init()
{
}

void app_certificate_store_reset()
{
  nvm3_enumDeletedObjects(nvm3_defaultHandle,
                          NULL,
                          0,
                          (nvm3_ObjectKey_t)APP_CERTIFICATE_STORE_NVM_KEY_BASE,
                          (nvm3_ObjectKey_t)(APP_CERTIFICATE_STORE_NVM_KEY_BASE +
                                             APP_CERTIFICATE_STORE_MAX_INDEX - 1));
}

void app_certificate_store_list()
{
  int i;
  sl_status_t ret;
  const app_enum_t *type_enum;
  app_certificate_t *cert;
  app_certicate_info_t info;

  printf("!  ##  Type        Info\r\n");

  for (i = 0; i < APP_CERTIFICATE_STORE_MAX_INDEX; ++i) {
    cert = app_certificate_store_get(i);
    if (cert) {
      ret = app_certificate_parse(cert, &info);
      if (ret != SL_STATUS_OK) {
        goto cleanup;
      }

      type_enum = app_util_get_enum_by_integer(app_certificate_type_enum, info.type);
      if (!type_enum) {
        goto cleanup;
      }

      if ((info.type == app_certificate_type_trusted) ||
          (info.type == app_certificate_type_device)) {
        if (strlen(info.subject)) {
          printf("#  %2u  %-10s  %s %u-bit public key (%s)\r\n", i,
                 type_enum->value_str, info.algorithm, info.bitlen, info.subject);
        } else {
          printf("#  %2u  %-10s  %s %u-bit public key\r\n", i,
                 type_enum->value_str, info.algorithm, info.bitlen);
        }
      } else if (info.type == app_certificate_type_device_pk) {
        printf("#  %2u  %-10s  %s %u-bit private key\r\n", i,
               type_enum->value_str, info.algorithm, info.bitlen);
      }

cleanup:

     app_certificate_free(cert);
    } else {
      printf("#  %2u  [EMPTY]\r\n", i);
    }
  }

  printf("!\r\n");
}

app_certificate_t *app_certificate_store_get(uint8_t index)
{
  app_certificate_t *cert;

  if (index >= APP_CERTIFICATE_STORE_MAX_INDEX) {
    // Certificate index doesn't exist
    return NULL;
  }

  // Attempt to use an NVM certificate
  cert = app_certificate_store_nvm_get(index);
  if (!cert) {
    // Attempt to use a default certificate
    cert = app_certificate_store_default_get(index);
    if (!cert) {
      // Certificate index doesn't exist
      return NULL;
    }
  } else if (!cert->data_offset) {
    // Zero-length certificate indicates the certificate index
    // has been deleted. Treat it as a non-existing index.
    app_certificate_free(cert);
    return NULL;
  }

  return cert;
}

sl_status_t app_certificate_store_set(uint8_t index,
                                      const app_certificate_t* certificate)
{
  return app_certificate_store_nvm_set(index, certificate);
}

sl_status_t app_certificate_store_remove(uint8_t index_mask)
{
  int i;
  sl_status_t ret;

  for (i = 0; i < APP_CERTIFICATE_STORE_MAX_INDEX; ++i) {
    if (index_mask & (1 << i)) {
      ret = app_certificate_store_nvm_set(i, NULL);
      if (ret != SL_STATUS_OK) {
        return ret;
      }
    }
  }

  return SL_STATUS_OK;
}
