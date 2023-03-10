/***************************************************************************//**
* @file
* @brief BT Mesh Host Provisioner component - Certificate-Based Provisioning
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
#include <getopt.h>
#include <unistd.h>
#include <string.h>

// app-related headers
#include "app.h"
#include "app_assert.h"
#include "app_log.h"
#include "btmesh_app_prov.h"
#include "btmesh_app_prov_cbp.h"
#include "btmesh_prov.h"
#include "sl_common.h"
#include "sl_bt_api.h"
#include "btmesh_app_certificate_validation.h"

// -----------------------------------------------------------------------------
// Macros

/// EC public key size without the leading 0x04
#define CBP_PUBLIC_KEY_SIZE                   64
/// Flag indicating if an OOB public key is required or not
#define CBP_OOB_REQUIREMENT_PUBLIC_KEY        1
/// Flag indicating OOB authorization method
#define CBP_AUTH_METHOD_FLAG                  0
/// Flag indicating output action, if any
#define CBP_OUTPUT_ACTION_FLAG                0
/// Flag indicating input action, if any
#define CBP_INPUT_ACTION_FLAG                 0
/// Minimum size of the in/outout action, 0 if not used
#define CBP_MINIMUM_OOB_ACTION_SIZE           0
/// Maximum size of the in/outout action, 0 if not used
#define CBP_MAXIMUM_OOB_ACTION_SIZE           0

/// Suspend provisioning at link open
#define CBP_PROVISIONING_SUSPEND_AT_LINK_OPEN 2
/// Provisioning has been suspended at link open
#define CBP_PROVISIONING_SUSPENDED_LINK_OPEN  1

// -----------------------------------------------------------------------------
// Enums, structs, typedefs

/// Possible states of CBP
typedef enum cbp_state_e{
  CBP_NONE,
  CBP_WAITING_FOR_PROVISION_SUSPEND,
  CBP_STARTED,
  CBP_WAITING_FOR_PROVISION_RECORDS_LIST,
  CBP_HANDLE_PROVISION_RECORDS_LIST,
  CBP_WAITING_FOR_PROVISION_RECORD_DATA,
  CBP_VALIDATING,
  CBP_WAITING_FOR_PKEY_REQUEST,
  CBP_SEND_PKEY_RESPONSE,
  CBP_ERROR,
  CBP_DONE
} cbp_state_t;

// -----------------------------------------------------------------------------
// Static Function Declarations

/***************************************************************************//**
 * Handle provisioning records list event
 *
 * @param[in] result Result of the event
 * @param[in] uuid UUID of the device
 * @param[in] list Pointer to the list of provisioning results array
 ******************************************************************************/
static void btmesh_prov_on_provisioning_records_list_received(uint16_t result,
                                                              uuid_128 uuid,
                                                              uint8array *list);

/***************************************************************************//**
* Handle provisioning record data event
*
* @param[in] result Result of the event
* @param[in] uuid UUID of the device
* @param[in] record Provisioning record ID
* @param[in] final Flag indicating the last part of the data
* @param[in] data Pointer to the received data array
*******************************************************************************/
static void btmesh_prov_on_provisioning_record_data_received(uint16_t result,
                                                             uuid_128 uuid,
                                                             uint16_t record,
                                                             uint8_t final,
                                                             uint8array *data);

// -----------------------------------------------------------------------------
// Static Variables

/// CBP is to be used in provisioning
bool cbp_enabled = false;
/// Current state of CBP handling
cbp_state_t cbp_state = CBP_NONE;
/// Pointer to the device certificate
uint8_t *certificate = NULL;
/// Length of the certificate
static size_t certificate_len = 0;
/// Public key extracted from certificate
uint8_t pkey[CBP_PUBLIC_KEY_SIZE] = { 0 };
/// UUID of the device to be provisioned
uuid_128 cbp_uuid = { 0 };
/// Command line options
static struct option cbp_long_options[CBP_OPTLENGTH] = {
  { "cbp", no_argument, 0, 'c' }
};

// -----------------------------------------------------------------------------
// Function definitions

sl_status_t btmesh_cbp_init(int cmd_opt, char *cmd_optarg)
{
  sl_status_t sc = SL_STATUS_OK;

  switch (cmd_opt) {
    case 'c':
      cbp_enabled = true;
      break;
    default:
      sc = SL_STATUS_NOT_FOUND;
      break;
  }
  return sc;
}

/***************************************************************************//**
* BT Mesh event handler for CBP
*******************************************************************************/
void btmesh_cbp_on_event(sl_btmesh_msg_t *evt)
{
  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_btmesh_evt_prov_provisioning_records_list_id:
    {
      // The list shows all provisioning records, e.g. all certificates present on the device
      sl_btmesh_evt_prov_provisioning_records_list_t *prov_records_list_evt;
      prov_records_list_evt = (sl_btmesh_evt_prov_provisioning_records_list_t *)&(evt->data);
      uint16_t result = prov_records_list_evt->result;
      uuid_128 uuid = prov_records_list_evt->uuid;
      uint8array *list = &prov_records_list_evt->list;
      btmesh_prov_on_provisioning_records_list_received(result,
                                                        uuid,
                                                        list);
      break;
    }
    case sl_btmesh_evt_prov_provisioning_record_data_id:
    {
      // Data of a requested provisioning record, i.e. the certificate itself
      // This is a recurring event until final == 1 is received
      sl_btmesh_evt_prov_provisioning_record_data_t *prov_record_data_evt;
      prov_record_data_evt = (sl_btmesh_evt_prov_provisioning_record_data_t *)&(evt->data);
      uint16_t result = prov_record_data_evt->result;
      uuid_128 uuid = prov_record_data_evt->uuid;
      uint16_t record = prov_record_data_evt->record;
      uint8_t final = prov_record_data_evt->final;
      uint8array *data = &prov_record_data_evt->data;
      btmesh_prov_on_provisioning_record_data_received(result,
                                                       uuid,
                                                       record,
                                                       final,
                                                       data);
      break;
    }
    case sl_btmesh_evt_prov_provisioning_suspended_id:
    {
      // For CBP provisioning must be suspended at link open to fetch and validate
      // the device certificate(s)
      sl_btmesh_evt_prov_provisioning_suspended_t *prov_suspended_evt;
      prov_suspended_evt = (sl_btmesh_evt_prov_provisioning_suspended_t *)&(evt->data);
      uint8_t reason = prov_suspended_evt->reason;
      if (reason == CBP_PROVISIONING_SUSPENDED_LINK_OPEN) {
        app_log_debug("Provisioning suspended, link open" APP_LOG_NEW_LINE);
        cbp_state = CBP_STARTED;
      } else {
        app_log_info("Provisioning suspended, reason: 0x%02x" APP_LOG_NEW_LINE, reason);
        cbp_state = CBP_ERROR;
      }
      break;
    }
    case sl_btmesh_evt_prov_oob_pkey_request_id:
      app_log_debug("pkey request received" APP_LOG_NEW_LINE);
      // The device asks for the public key of its previously sent device certificate
      if (cbp_state == CBP_WAITING_FOR_PKEY_REQUEST) {
        // Only switch to the response state if we actually anticipate the pkey request
        cbp_state = CBP_SEND_PKEY_RESPONSE;
      }
      break;
    default:
      break;
  }
}

/***************************************************************************//**
* Wrapper for provisioning records initialization
*******************************************************************************/
sl_status_t btmesh_prov_init_provisioning_records(void)
{
  return sl_btmesh_prov_init_provisioning_records();
}

/***************************************************************************//**
* Setup certificate-based provisioning
*******************************************************************************/
sl_status_t btmesh_prov_setup_cbp(uuid_128 uuid)
{
  sl_status_t sc = SL_STATUS_OK;
  if (cbp_enabled == true) {
    app_log_debug("Setup CBP" APP_LOG_NEW_LINE);
    // Set OOB requirements so CBP is expected
    // The second parameter indicates OOB public key usage
    sc = sl_btmesh_prov_set_oob_requirements(uuid,
                                             CBP_OOB_REQUIREMENT_PUBLIC_KEY,
                                             CBP_AUTH_METHOD_FLAG,
                                             CBP_OUTPUT_ACTION_FLAG,
                                             CBP_INPUT_ACTION_FLAG,
                                             CBP_MINIMUM_OOB_ACTION_SIZE,
                                             CBP_MAXIMUM_OOB_ACTION_SIZE);
    if (sc != SL_STATUS_OK) {
      app_log_status_error_f(sc, "Failed to set OOB requirements" APP_LOG_NEW_LINE);
      return sc;
    }

    // Set provisioning suspend event right after link open
    // This lets provision_adv_device() start the provisioning session
    // but will instantly suspend it so the provisioner can get the
    // provisioning record data (i.e. the device certificate)
    sc = sl_btmesh_prov_set_provisioning_suspend_event(CBP_PROVISIONING_SUSPEND_AT_LINK_OPEN);
    if (sc != SL_STATUS_OK) {
      app_log_status_error_f(sc, "Failed to set provisioning suspend event" APP_LOG_NEW_LINE);
      return sc;
    }
    cbp_uuid = uuid;
    cbp_state = CBP_NONE;
  }
  return sc;
}

/***************************************************************************//**
* Handle certificate-based provisioning
*******************************************************************************/
void btmesh_app_prov_handle_cbp(uint16_t netkey_index,
                                uuid_128 uuid,
                                bd_addr mac_address,
                                uint8_t bearer_type)
{
  if (cbp_enabled == true) {
    switch (cbp_state) {
      case CBP_NONE:
      {
        app_log_info("Starting CBP provisioning" APP_LOG_NEW_LINE);
        if (bearer_type != HOST_PROV_PB_REMOTE) {
          // Initial state, start provisioning. A suspended event shall occur soon
          sl_status_t sc = btmesh_prov_provision_adv_device(netkey_index, uuid, mac_address, bearer_type, 0);
          if (sc != SL_STATUS_OK) {
            app_log_status_error_f(sc, "Failed to start provisioning" APP_LOG_NEW_LINE);
            cbp_state = CBP_ERROR;
            return;
          }
        }
        app_log_debug("Waiting for provision suspend event" APP_LOG_NEW_LINE);
        cbp_state = CBP_WAITING_FOR_PROVISION_SUSPEND;
        break;
      }
      case CBP_WAITING_FOR_PROVISION_SUSPEND:
        // Wait for the provision suspended event. Next state called from event handler.
        break;
      case CBP_STARTED:
      {
        // Provisioning suspended, acquire provisioning records list
        app_log_debug("Provisioning suspended, getting provisioning records list" APP_LOG_NEW_LINE);
        sl_status_t sc;
        sc = sl_btmesh_prov_get_provisioning_records_list(cbp_uuid);
        if (sc != SL_STATUS_OK) {
          app_log_status_error_f(sc, "Failed to get provisioning records list" APP_LOG_NEW_LINE);
          cbp_state = CBP_ERROR;
          return;
        }
        cbp_state = CBP_WAITING_FOR_PROVISION_RECORDS_LIST;
        break;
      }
      case CBP_WAITING_FOR_PROVISION_RECORDS_LIST:
        // Wait for the records list. Next state called form event handler.
        break;
      case CBP_HANDLE_PROVISION_RECORDS_LIST:
      {
        // Handle records list if more than one certificates are present on the device.
        // In this example only one device certificate is present, its record ID is always 1.
        uint16_t record = 1;
        sl_status_t sc = sl_btmesh_prov_get_provisioning_record_data(cbp_uuid, record);
        if (sc != SL_STATUS_OK) {
          app_log_error("Failed to get provisioning record data" APP_LOG_NEW_LINE);
          cbp_state = CBP_ERROR;
          return;
        }
        cbp_state = CBP_WAITING_FOR_PROVISION_RECORD_DATA;
        break;
      }
      case CBP_WAITING_FOR_PROVISION_RECORD_DATA:
        // Wait for the record data. Next state called form event handler.
        break;
      case CBP_VALIDATING:
      {
        // Validate the device certificate. Check expiration, UUID, etc.
        app_log_info("Validating device certificate" APP_LOG_NEW_LINE);
        sl_status_t sc = btmesh_prov_validate_certificate(
          certificate,
          certificate_len,
          "CA/ca-certificate.crt",
          &cbp_uuid,
          CBP_PUBLIC_KEY_SIZE,
          pkey
          );
        free(certificate);
        certificate_len = 0;
        if (sc != SL_STATUS_OK) {
          app_log_error("Failed to validate certificate" APP_LOG_NEW_LINE);
          cbp_state = CBP_ERROR;
          return;
        }

        // Continue provisioning if the certificate is valid
        sc = sl_btmesh_prov_continue_provisioning(cbp_uuid);
        if (sc != SL_STATUS_OK) {
          app_log_error("Failed to continue provisioning" APP_LOG_NEW_LINE);
          cbp_state = CBP_ERROR;
          return;
        }
        cbp_state = CBP_WAITING_FOR_PKEY_REQUEST;
        break;
      }

      case CBP_WAITING_FOR_PKEY_REQUEST:
        // Wait for pkey request. Next state called form event handler.
        break;

      case CBP_SEND_PKEY_RESPONSE:
      {
        app_log_debug("Sending pkey response" APP_LOG_NEW_LINE);
        // Send back the extracted EC public key to the device
        size_t pkey_len = CBP_PUBLIC_KEY_SIZE;
        sl_status_t sc = sl_btmesh_prov_send_oob_pkey_response(cbp_uuid, pkey_len, pkey);
        if (sc != SL_STATUS_OK) {
          app_log_status_error_f(sc, "Failed to send pkey response" APP_LOG_NEW_LINE);
          cbp_state = CBP_ERROR;
          return;
        }
        cbp_state = CBP_DONE;
        break;
      }
      case CBP_ERROR:
        // Handle any errors and inform the user about failure
        btmesh_prov_on_provision_failed_evt(0x04, cbp_uuid);
        break;
      case CBP_DONE:
        // CBP finished successfully. The application will handle the provisioning
        // finished (or failed) event independently.
        break;
      default:
        break;
    }
  } else if (bearer_type != HOST_PROV_PB_REMOTE) {
    // If CBP is not requested, provisioning of the selected device must be started
    // at this point. If remote provisioning is ongoing, then this is handled.
    static bool prov_started = false;
    if (prov_started == false) {
      sl_status_t sc = btmesh_prov_provision_adv_device(netkey_index, uuid, mac_address, bearer_type, 0);
      app_assert_status_f(sc, "Provisioning failed" APP_LOG_NEW_LINE);
      prov_started = true;
    }
  }
}

void btmesh_app_prov_set_cbp_capability(bool capability)
{
  app_log_debug("CBP set to %s" APP_LOG_NEW_LINE, capability ? "true" : "false");
  cbp_enabled = capability;
}

// -----------------------------------------------------------------------------
// Callbacks

/*******************************************************************************
 * Handle provisioning records list event
 ******************************************************************************/
void btmesh_prov_on_provisioning_records_list_received(uint16_t result,
                                                       uuid_128 uuid,
                                                       uint8array *list)
{
  // Handle multiple (intermediate) certificates here
  cbp_state = CBP_HANDLE_PROVISION_RECORDS_LIST;
}

/*******************************************************************************
* Handle provisioning record data event
*******************************************************************************/
void btmesh_prov_on_provisioning_record_data_received(uint16_t result,
                                                      uuid_128 uuid,
                                                      uint16_t record,
                                                      uint8_t final,
                                                      uint8array *data)
{
  // Store device certificate and extract the EC public key from it
  certificate_len += data->len;
  certificate = (uint8_t *)realloc(certificate, certificate_len);
  if (certificate == NULL) {
    app_log_error("Failed to allocate memory for CBP certificate" APP_LOG_NEW_LINE);
    cbp_state = CBP_ERROR;
    return;
  }
  memcpy(certificate + certificate_len - data->len, data->data, data->len);
  if (final == 1) {
    // The raw certificate is to be used in validation, no free here
    cbp_state = CBP_VALIDATING;
  }
}

/***************************************************************************//**
* Check if CBP-related options are enabled
*******************************************************************************/
sl_status_t btmesh_cbp_on_check_cmd_options(int cmd_opt, char *cmd_optarg)
{
  return btmesh_cbp_init(cmd_opt, cmd_optarg);
}

void btmesh_cbp_on_build_cmd_options(struct option *long_options)
{
  if (NULL != long_options) {
    memcpy(long_options, cbp_long_options, CBP_OPTLENGTH * sizeof(struct option));
  }
}
