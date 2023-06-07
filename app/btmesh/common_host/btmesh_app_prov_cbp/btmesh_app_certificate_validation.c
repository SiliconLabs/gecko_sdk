/***************************************************************************//**
* @file
* @brief BT Mesh Host Provisioner component - Certificate Validation
********************************************************************************
* # License
* <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
********************************************************************************
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
*******************************************************************************/

// -----------------------------------------------------------------------------
// Includes

// standard library headers
#include <string.h>

// OpenSSL X.509 header
#include <openssl/asn1.h>
#include <openssl/objects.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <openssl/x509_vfy.h>

// app-related headers
#include "btmesh_app_certificate_validation.h"
#include "app_log.h"

// -----------------------------------------------------------------------------
// Macros

/// Length of UUID in the canonical fields-and-hyphens format
#define UUID_CANONICAL_STRING_LEN             36
/// Length of the extra data in common name field
/// " BCID:xxxx BPID:xxxx"
#define COMMON_NAME_EXTRA_DATA                20

/// Version field of the certificate, decimal 2 = v3
#define CBP_CERTIFICATE_VERSION               2

// -----------------------------------------------------------------------------
// Static Function Declarations

/***************************************************************************//**
* Extract the public key from an X509 certificate
*
* @param[in] cert An X.509 certificate
* @param[in] key_size public key size
* @param[out] pub_key Pointer to the place to extract the public key
* @return Status of the key extraction
* @retval SL_STATUS_OK if the key is successfully extracted
*         Error code otherwise
*******************************************************************************/
static sl_status_t btmesh_app_prov_cbp_extract_public_key(X509 *cert, size_t key_size, uint8_t* key);
/***************************************************************************//**
* Get the common name string from an X509 certificate
*
* @param[in] cert An X.509 certificate
* @return Pointer to a null-terminated char string
*         containing the common name field
*******************************************************************************/
static const unsigned char* btmesh_app_prov_cbp_get_x509_common_name(X509 *cert);

/***************************************************************************//**
* Check if the UUID in the X.509 certificate matches the UUID of the device
* currently provisioned
*
* @param[in] cert The certificate
* @param[in] uuid UUID of the device being provisioned
* @return Status of the validation
* @retval SL_STATUS_OK if the two match
*         Error code otherwise
*******************************************************************************/
static sl_status_t btmesh_app_prov_cbp_validate_uuid(X509 *cert, uuid_128 *uuid);

/***************************************************************************//**
* Validate the device certificate with a given root certificate
*
* @param[in] cert The device certificate
* @param[in] root The root certificate
* @return Status of the validation
* @retval SL_STATUS_OK if the certificate is valid
*         Error code otherwise
*******************************************************************************/
sl_status_t btmesh_app_prov_cbp_validate_certificate_with_root(X509 *cert, X509 *root);

/***************************************************************************//**
* Validate certificate's expiration times
*
* @param[in] cert The device certificate
* @return Status of the validation
* @retval SL_STATUS_OK if the certificate is valid
*         Error code otherwise
*******************************************************************************/
sl_status_t btmesh_app_prov_cbp_validate_expiration(X509 *cert);

/***************************************************************************//**
* Validate the data fields of a certificate
*
* @param[in] cert The device certificate
* @return Status of the validation
* @retval SL_STATUS_OK if the certificate is valid
*         Error code otherwise
*******************************************************************************/
sl_status_t btmesh_app_prov_cbp_validate_data_fields(X509 *cert);

/*******************************************************************************
* Validate the received certificate
*******************************************************************************/
sl_status_t btmesh_prov_validate_certificate(
  const unsigned char *raw_cert,
  size_t cert_len,
  const char *root_cert_path,
  uuid_128 *uuid,
  size_t key_size,
  uint8_t *pub_key
  )
{
  sl_status_t sc;
  // OpenSSL setup
  OpenSSL_add_all_algorithms();

  // Device certificate
  X509 *cert = d2i_X509(NULL, &raw_cert, cert_len);
  if (cert == NULL) {
    app_log_error("Failed to parse certificate" APP_LOG_NEW_LINE);
    return SL_STATUS_FAIL;
  }

  // Root certificate
  FILE *fp = fopen(root_cert_path, "r");
  if (fp == NULL) {
    app_log_error("Failed to open root certificate" APP_LOG_NEW_LINE);
    X509_free(cert);
    return SL_STATUS_FAIL;
  }
  X509 *root = PEM_read_X509(fp, NULL, NULL, NULL);
  if (root == NULL) {
    app_log_error("Failed to parse root certificate" APP_LOG_NEW_LINE);
    X509_free(cert);
    fclose(fp);
    return SL_STATUS_FAIL;
  }
  // Root CA file loaded into OpenSSL, handle can now be closed
  fclose(fp);

  if ( btmesh_app_prov_cbp_validate_data_fields(cert) == SL_STATUS_OK
       && btmesh_app_prov_cbp_validate_uuid(cert, uuid) == SL_STATUS_OK
       && btmesh_app_prov_cbp_validate_certificate_with_root(cert, root) == SL_STATUS_OK
       && btmesh_app_prov_cbp_validate_expiration(cert) == SL_STATUS_OK
       && btmesh_app_prov_cbp_extract_public_key(cert, key_size, pub_key) == SL_STATUS_OK ) {
    sc = SL_STATUS_OK;
    app_log_info("Certificate validated successfully" APP_LOG_NEW_LINE);
  } else {
    sc = SL_STATUS_FAIL;
  }

  X509_free(cert);
  X509_free(root);
  return sc;
}

/*******************************************************************************
* Extract the raw pubic key from the certificate
*******************************************************************************/
sl_status_t btmesh_app_prov_cbp_extract_public_key(X509 *cert, size_t key_size, uint8_t* key)
{
  // Extract public key in OpenSSL's format
  EVP_PKEY *pubkey = X509_get0_pubkey(cert);
  if (pubkey == NULL) {
    app_log_error("Failed to get public key" APP_LOG_NEW_LINE);
    return SL_STATUS_FAIL;
  }
  // Check if the Key ID matches the required algorithm: id-ecPublicKey
  int key_type = EVP_PKEY_id(pubkey);
  if (key_type != NID_X9_62_id_ecPublicKey) {
    app_log_error("Wrong public key algorithm" APP_LOG_NEW_LINE);
    return SL_STATUS_FAIL;
  }
  // Extract EC key in OpenSSL's format
  EC_KEY *ec_key = EVP_PKEY_get0_EC_KEY(pubkey);
  if (ec_key == NULL) {
    app_log_error("Failed to get EC key" APP_LOG_NEW_LINE);
    return SL_STATUS_FAIL;
  }
  // Setup OpenSSL conversion parameters to extract the raw public key
  const EC_GROUP *group = EC_KEY_get0_group(ec_key);
  if (group == NULL) {
    app_log_error("Failed to get EC group" APP_LOG_NEW_LINE);
    return SL_STATUS_FAIL;
  }
  point_conversion_form_t form = EC_GROUP_get_point_conversion_form(group);

  // Extract raw public key - the function allocates memory
  unsigned char *raw_pubkey;
  size_t key_len = EC_KEY_key2buf(ec_key, form, &raw_pubkey, NULL);
  if (key_len == 0) {
    app_log_error("Failed to get EC public key" APP_LOG_NEW_LINE);
    return SL_STATUS_FAIL;
  }
  // Copy raw key to the parameter
  memcpy(key, &raw_pubkey[1], key_size);
  OPENSSL_free(raw_pubkey);
  return SL_STATUS_OK;
}

/*******************************************************************************
* Get the common name string from an X509 certificate
*******************************************************************************/
const unsigned char* btmesh_app_prov_cbp_get_x509_common_name(X509 *cert)
{
  X509_NAME *subject_name = X509_get_subject_name(cert);
  int lastpos = -1;
  lastpos = X509_NAME_get_index_by_NID(subject_name, NID_commonName, lastpos);
  X509_NAME_ENTRY *e = X509_NAME_get_entry(subject_name, lastpos);
  ASN1_STRING *d = X509_NAME_ENTRY_get_data(e);
  return ASN1_STRING_get0_data(d);
}

/*******************************************************************************
* Check if the UUID in the X.509 certificate matches the UUID of the device
* currently provisioned
*******************************************************************************/
sl_status_t btmesh_app_prov_cbp_validate_uuid(X509 *cert, uuid_128 *uuid)
{
  const char *common_name = (const char *)btmesh_app_prov_cbp_get_x509_common_name(cert);
  app_log_debug("Common name: %s" APP_LOG_NEW_LINE, common_name);
  uuid_128 common_uuid = { 0 };
  int len = strlen((const char *)common_name);
  // Parse UUID
  int s = sscanf(common_name,
                 "%2hhx%2hhx%2hhx%2hhx-%2hhx%2hhx-%2hhx%2hhx-%2hhx%2hhx-%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx",
                 &common_uuid.data[0],
                 &common_uuid.data[1],
                 &common_uuid.data[2],
                 &common_uuid.data[3],
                 &common_uuid.data[4],
                 &common_uuid.data[5],
                 &common_uuid.data[6],
                 &common_uuid.data[7],
                 &common_uuid.data[8],
                 &common_uuid.data[9],
                 &common_uuid.data[10],
                 &common_uuid.data[11],
                 &common_uuid.data[12],
                 &common_uuid.data[13],
                 &common_uuid.data[14],
                 &common_uuid.data[15]);
  // Compare the received string to the device under provision
  if (len != (UUID_CANONICAL_STRING_LEN + COMMON_NAME_EXTRA_DATA)
      || s < 16
      || memcmp(uuid, &common_uuid, sizeof(uuid_128)) != 0) {
    app_log_error("UUID of the device and in the certificate does not match" APP_LOG_NEW_LINE);
    return SL_STATUS_INVALID_PARAMETER;
  } else {
    return SL_STATUS_OK;
  }
}
/*******************************************************************************
* Authenticate device certificate with root certificate
*******************************************************************************/
sl_status_t btmesh_app_prov_cbp_validate_certificate_with_root(X509 *cert, X509 *root)
{
  X509_STORE *store = X509_STORE_new();
  if (store == NULL) {
    app_log_error("Unable to create X.509 store" APP_LOG_NEW_LINE);
    return SL_STATUS_ALLOCATION_FAILED;
  }
  X509_STORE_CTX *store_ctx = X509_STORE_CTX_new();
  if (store_ctx == NULL) {
    app_log_error("Unable to create X.509 store context" APP_LOG_NEW_LINE);
    X509_STORE_free(store);
    return SL_STATUS_ALLOCATION_FAILED;
  }

  sl_status_t sc = SL_STATUS_FAIL;
  if (X509_STORE_add_cert(store, root) != 1) {
    app_log_error("Unable to add root certificate to store" APP_LOG_NEW_LINE);
  } else if (X509_STORE_CTX_init(store_ctx, store, cert, NULL) != 1) {
    app_log_error("Unable to init store context" APP_LOG_NEW_LINE);
  } else if (X509_verify_cert(store_ctx) != 1) {
    app_log_error("Unable to verify certificate" APP_LOG_NEW_LINE);
  } else {
    sc = SL_STATUS_OK;
  }

  X509_STORE_CTX_free(store_ctx);
  X509_STORE_free(store);

  return sc;
}

/*******************************************************************************
* Validate certificate's expiration times
*******************************************************************************/
sl_status_t btmesh_app_prov_cbp_validate_expiration(X509 *cert)
{
  int status = 0;
  // Start date
  status = X509_cmp_current_time(X509_get_notBefore(cert));
  if (status != -1) {
    // -1 means certificate time <= now
    app_log_error("Certificate is not yet valid" APP_LOG_NEW_LINE);
    return SL_STATUS_FAIL;
  }
  // Expiry date
  status = X509_cmp_current_time(X509_get_notAfter(cert));
  if (status != 1) {
    // 1 means certificate time > now
    app_log_error("Certificate has expired" APP_LOG_NEW_LINE);
    return SL_STATUS_FAIL;
  }

  return SL_STATUS_OK;
}

/*******************************************************************************
* Validate the data fields of a certificate
*******************************************************************************/
sl_status_t btmesh_app_prov_cbp_validate_data_fields(X509 *cert)
{
  // Version field shall be set to v3, decimal value 2
  long version = X509_get_version(cert);
  if (version != CBP_CERTIFICATE_VERSION) {
    app_log_error("Incorrect certificate version" APP_LOG_NEW_LINE);
    return SL_STATUS_FAIL;
  }
  // Signature algorithm shall be ecdsa-with-SHA256
  int signature = X509_get_signature_nid(cert);
  if (signature != NID_ecdsa_with_SHA256) {
    app_log_error("Incorrect certificate algorithm" APP_LOG_NEW_LINE);
    return SL_STATUS_FAIL;
  }
  // Check not allowed extensions
  const STACK_OF(X509_EXTENSION) * extensions = X509_get0_extensions(cert);
  const int not_allowed_extensions[] = {
    NID_subject_alt_name,
    NID_issuer_alt_name,
    NID_name_constraints,
    NID_policy_constraints,
    NID_ext_key_usage,
    NID_inhibit_any_policy,
  };
  const int not_allowed_ext_size = sizeof(not_allowed_extensions) / sizeof(int);
  void *extension_ptr = NULL;
  // If any of the not allowed extensions is present, the certificate is invalid
  for (int i = 0; i < not_allowed_ext_size; i++) {
    extension_ptr = X509V3_get_d2i(extensions, not_allowed_extensions[i], NULL, NULL);
    if (extension_ptr != NULL) {
      app_log_error("Not allowed extensions" APP_LOG_NEW_LINE);
      return SL_STATUS_FAIL;
    }
  }
  // Key usage shall be present and it shall be set as keyAgreement
  // UINT32_MAX indicates key usage field is not present
  uint32_t key_usage = X509_get_key_usage(cert);
  if (key_usage == UINT32_MAX) {
    app_log_error("Key usage field is not present" APP_LOG_NEW_LINE);
    return SL_STATUS_FAIL;
  }
  if ((key_usage & KU_KEY_AGREEMENT) == 0) {
    app_log_error("keyAgreement is not set in key usage" APP_LOG_NEW_LINE);
    return SL_STATUS_FAIL;
  }
  return SL_STATUS_OK;
}
