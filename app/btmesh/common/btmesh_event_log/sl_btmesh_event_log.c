/***************************************************************************//**
 * @file
 * @brief Bt Mesh Event Logging module
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "sl_btmesh_api.h"
#include "sl_bt_api.h"

#include "app_log.h"

#include "sl_btmesh_event_log_config.h"
#include "sl_btmesh_event_log.h"

// Warning! The app_btmesh_util shall be included after the component configuration
// header file in order to provide the component specific logging macro.
#include "app_btmesh_util.h"

#define log_append_byte(x) app_log_append("%02x", (x))

static void log_append_byte_array_le(uint8_t *data, size_t size)
{
  app_log_append("0x");
  for (int i = size - 1; i >= 0; i--) {
    log_append_byte(data[i]);
  }
}

static void log_append_byte_array_be(uint8_t *data, size_t size)
{
  app_log_append("[");
  for (size_t i = 0; i < size; i++) {
    log_append_byte(data[i]);
  }
  app_log_append("]");
}

#define log_append_sl_bt_uuid_16_t(x) log_append_byte_array_le((x).data, 2)
#define log_append_sl_bt_uuid_64_t(x) log_append_byte_array_le((x).data, 8)
#define log_append_bd_addr(x) log_append_byte_array_le((x).addr, 6)
#define log_append_uuid_128(x) log_append_byte_array_le((x).data, 16)
#define log_append_aes_key_128(x) log_append_byte_array_le((x).data, 16)

#define log_append_uint8array(x) log_append_byte_array_be(&*(x).data, (x).len)
#define log_append_byte_array(x) log_append_byte_array_be(&*(x).data, (x).len)

#define log_append_uint8_t(x) app_log_append("0x%02x", (x))
#define log_append_uint16_t(x) app_log_append("0x%04x", (x))
#define log_append_uint32_t(x) app_log_append("0x%08lx", (x))
#define log_append_uint64_t(x) log_append_byte_array_le((uint8_t*)&(x), 8)

#define log_append_int8_t(x) app_log_append("%d", (x))
#define log_append_int16_t(x) app_log_append("%d", (x))
#define log_append_int32_t(x) app_log_append("%ld", (x))
#define log_append_int64_t(x)

#define PREFIX SL_BTMESH_EVENT_LOG_PREFIX_CFG_VAL

/***************************************************************************//**
 * @addtogroup BtMeshEventLog
 * @{
 ******************************************************************************/

/*******************************************************************************
 * Log Bluetooth mesh events
 * @param[in] evt     Pointer to incoming event
 ******************************************************************************/
void sl_btmesh_log_btmesh_events(sl_btmesh_msg_t *evt)
{
  if (NULL == evt) {
    return;
  }

  uint32_t evt_id = SL_BT_MSG_ID(evt->header);

  // Handle events
  switch (evt_id) {
    // node
    // Mesh Node
    case sl_btmesh_evt_node_initialized_id: {
      app_log(PREFIX "node_initialized(");
      sl_btmesh_evt_node_initialized_t *data =
        &evt->data.evt_node_initialized;
      app_log_append(" provisioned="); log_append_uint8_t(data->provisioned);
      app_log_append(" address="); log_append_uint16_t(data->address);
      app_log_append(" iv_index="); log_append_uint32_t(data->iv_index);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_node_provisioned_id: {
      app_log(PREFIX "node_provisioned(");
      sl_btmesh_evt_node_provisioned_t *data =
        &evt->data.evt_node_provisioned;
      app_log_append(" address="); log_append_uint16_t(data->address);
      app_log_append(" iv_index="); log_append_uint32_t(data->iv_index);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_node_config_get_id: {
      app_log(PREFIX "node_config_get(");
      sl_btmesh_evt_node_config_get_t *data =
        &evt->data.evt_node_config_get;
      app_log_append(" netkey_index="); log_append_uint16_t(data->netkey_index);
      app_log_append(" id="); log_append_uint16_t(data->id);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_node_config_set_id: {
      app_log(PREFIX "node_config_set(");
      sl_btmesh_evt_node_config_set_t *data =
        &evt->data.evt_node_config_set;
      app_log_append(" netkey_index="); log_append_uint16_t(data->netkey_index);
      app_log_append(" id="); log_append_uint16_t(data->id);
      app_log_append(" value="); log_append_uint8array(data->value);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_node_display_output_oob_id: {
      app_log(PREFIX "node_display_output_oob(");
      sl_btmesh_evt_node_display_output_oob_t *data =
        &evt->data.evt_node_display_output_oob;
      app_log_append(" output_action="); log_append_uint8_t(data->output_action);
      app_log_append(" output_size="); log_append_uint8_t(data->output_size);
      app_log_append(" data="); log_append_uint8array(data->data);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_node_input_oob_request_id: {
      app_log(PREFIX "node_input_oob_request(");
      sl_btmesh_evt_node_input_oob_request_t *data =
        &evt->data.evt_node_input_oob_request;
      app_log_append(" input_action="); log_append_uint8_t(data->input_action);
      app_log_append(" input_size="); log_append_uint8_t(data->input_size);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_node_provisioning_started_id: {
      app_log(PREFIX "node_provisioning_started(");
      sl_btmesh_evt_node_provisioning_started_t *data =
        &evt->data.evt_node_provisioning_started;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_node_provisioning_failed_id: {
      app_log(PREFIX "node_provisioning_failed(");
      sl_btmesh_evt_node_provisioning_failed_t *data =
        &evt->data.evt_node_provisioning_failed;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_node_key_added_id: {
      app_log(PREFIX "node_key_added(");
      sl_btmesh_evt_node_key_added_t *data =
        &evt->data.evt_node_key_added;
      app_log_append(" type="); log_append_uint8_t(data->type);
      app_log_append(" index="); log_append_uint16_t(data->index);
      app_log_append(" netkey_index="); log_append_uint16_t(data->netkey_index);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_node_model_config_changed_id: {
      app_log(PREFIX "node_model_config_changed(");
      sl_btmesh_evt_node_model_config_changed_t *data =
        &evt->data.evt_node_model_config_changed;
      app_log_append(" node_config_state="); log_append_uint8_t(data->node_config_state);
      app_log_append(" element_address="); log_append_uint16_t(data->element_address);
      app_log_append(" vendor_id="); log_append_uint16_t(data->vendor_id);
      app_log_append(" model_id="); log_append_uint16_t(data->model_id);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_node_reset_id: {
      sl_btmesh_log_on_node_reset();
    } break;
    case sl_btmesh_evt_node_ivrecovery_needed_id: {
      app_log(PREFIX "node_ivrecovery_needed(");
      sl_btmesh_evt_node_ivrecovery_needed_t *data =
        &evt->data.evt_node_ivrecovery_needed;
      app_log_append(" node_iv_index="); log_append_uint32_t(data->node_iv_index);
      app_log_append(" network_iv_index="); log_append_uint32_t(data->network_iv_index);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_node_changed_ivupdate_state_id: {
      app_log(PREFIX "node_changed_ivupdate_state(");
      sl_btmesh_evt_node_changed_ivupdate_state_t *data =
        &evt->data.evt_node_changed_ivupdate_state;
      app_log_append(" iv_index="); log_append_uint32_t(data->iv_index);
      app_log_append(" state="); log_append_uint8_t(data->state);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_node_static_oob_request_id: {
      app_log(PREFIX "node_static_oob_request(");
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_node_key_removed_id: {
      app_log(PREFIX "node_key_removed(");
      sl_btmesh_evt_node_key_removed_t *data =
        &evt->data.evt_node_key_removed;
      app_log_append(" type="); log_append_uint8_t(data->type);
      app_log_append(" index="); log_append_uint16_t(data->index);
      app_log_append(" netkey_index="); log_append_uint16_t(data->netkey_index);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_node_key_updated_id: {
      app_log(PREFIX "node_key_updated(");
      sl_btmesh_evt_node_key_updated_t *data =
        &evt->data.evt_node_key_updated;
      app_log_append(" type="); log_append_uint8_t(data->type);
      app_log_append(" index="); log_append_uint16_t(data->index);
      app_log_append(" netkey_index="); log_append_uint16_t(data->netkey_index);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_node_heartbeat_id: {
      app_log(PREFIX "node_heartbeat(");
      sl_btmesh_evt_node_heartbeat_t *data =
        &evt->data.evt_node_heartbeat;
      app_log_append(" src_addr="); log_append_uint16_t(data->src_addr);
      app_log_append(" dst_addr="); log_append_uint16_t(data->dst_addr);
      app_log_append(" hops="); log_append_uint8_t(data->hops);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_node_heartbeat_start_id: {
      app_log(PREFIX "node_heartbeat_start(");
      sl_btmesh_evt_node_heartbeat_start_t *data =
        &evt->data.evt_node_heartbeat_start;
      app_log_append(" src_addr="); log_append_uint16_t(data->src_addr);
      app_log_append(" dst_addr="); log_append_uint16_t(data->dst_addr);
      app_log_append(" period_sec="); log_append_uint32_t(data->period_sec);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_node_heartbeat_stop_id: {
      app_log(PREFIX "node_heartbeat_stop(");
      sl_btmesh_evt_node_heartbeat_stop_t *data =
        &evt->data.evt_node_heartbeat_stop;
      app_log_append(" src_addr="); log_append_uint16_t(data->src_addr);
      app_log_append(" dst_addr="); log_append_uint16_t(data->dst_addr);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_node_beacon_received_id: {
      app_log(PREFIX "node_beacon_received(");
      sl_btmesh_evt_node_beacon_received_t *data =
        &evt->data.evt_node_beacon_received;
      app_log_append(" netkey_index="); log_append_uint16_t(data->netkey_index);
      app_log_append(" key_refresh="); log_append_uint8_t(data->key_refresh);
      app_log_append(" iv_update="); log_append_uint8_t(data->iv_update);
      app_log_append(" iv_index="); log_append_uint32_t(data->iv_index);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_node_local_dcd_data_id: {
      app_log(PREFIX "node_local_dcd_data(");
      sl_btmesh_evt_node_local_dcd_data_t *data =
        &evt->data.evt_node_local_dcd_data;
      app_log_append(" page="); log_append_uint8_t(data->page);
      app_log_append(" data="); log_append_uint8array(data->data);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_node_local_dcd_data_end_id: {
      app_log(PREFIX "node_local_dcd_data_end(");
      sl_btmesh_evt_node_local_dcd_data_end_t *data =
        &evt->data.evt_node_local_dcd_data_end;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_node_local_model_metadata_page_id: {
      app_log(PREFIX "node_local_model_metadata_page(");
      sl_btmesh_evt_node_local_model_metadata_page_t *data =
        &evt->data.evt_node_local_model_metadata_page;
      app_log_append(" page="); log_append_uint8_t(data->page);
      app_log_append(" data="); log_append_uint8array(data->data);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_node_local_model_metadata_page_end_id: {
      app_log(PREFIX "node_local_model_metadata_page_end(");
      sl_btmesh_evt_node_local_model_metadata_page_end_t *data =
        &evt->data.evt_node_local_model_metadata_page_end;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_node_start_received_id: {
      app_log(PREFIX "node_start_received(");
      sl_btmesh_evt_node_start_received_t *data =
        &evt->data.evt_node_start_received;
      app_log_append(" algorithm="); log_append_uint8_t(data->algorithm);
      app_log_append(" public_key="); log_append_uint8_t(data->public_key);
      app_log_append(" authentication_method="); log_append_uint8_t(data->authentication_method);
      app_log_append(" authentication_action="); log_append_uint8_t(data->authentication_action);
      app_log_append(" authentication_size="); log_append_uint8_t(data->authentication_size);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_node_address_updated_id: {
      app_log(PREFIX "node_address_updated(");
      sl_btmesh_evt_node_address_updated_t *data =
        &evt->data.evt_node_address_updated;
      app_log_append(" new_address="); log_append_uint16_t(data->new_address);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_node_dcd_updated_id: {
      app_log(PREFIX "node_dcd_updated(");
      app_log_append(" )" NL);
    } break;

    // prov
    // Bluetooth Mesh Stack Provisioner
    case sl_btmesh_evt_prov_initialized_id: {
      app_log(PREFIX "prov_initialized(");
      sl_btmesh_evt_prov_initialized_t *data =
        &evt->data.evt_prov_initialized;
      app_log_append(" networks="); log_append_uint8_t(data->networks);
      app_log_append(" address="); log_append_uint16_t(data->address);
      app_log_append(" iv_index="); log_append_uint32_t(data->iv_index);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_prov_provisioning_suspended_id: {
      app_log(PREFIX "prov_provisioning_suspended(");
      sl_btmesh_evt_prov_provisioning_suspended_t *data =
        &evt->data.evt_prov_provisioning_suspended;
      app_log_append(" uuid="); log_append_uuid_128(data->uuid);
      app_log_append(" reason="); log_append_uint8_t(data->reason);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_prov_capabilities_id: {
      app_log(PREFIX "prov_capabilities(");
      sl_btmesh_evt_prov_capabilities_t *data =
        &evt->data.evt_prov_capabilities;
      app_log_append(" uuid="); log_append_uuid_128(data->uuid);
      app_log_append(" elements="); log_append_uint8_t(data->elements);
      app_log_append(" algorithms="); log_append_uint16_t(data->algorithms);
      app_log_append(" pkey_type="); log_append_uint8_t(data->pkey_type);
      app_log_append(" static_oob_type="); log_append_uint8_t(data->static_oob_type);
      app_log_append(" ouput_oob_size="); log_append_uint8_t(data->ouput_oob_size);
      app_log_append(" output_oob_action="); log_append_uint16_t(data->output_oob_action);
      app_log_append(" input_oob_size="); log_append_uint8_t(data->input_oob_size);
      app_log_append(" intput_oob_action="); log_append_uint16_t(data->intput_oob_action);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_prov_provisioning_failed_id: {
      app_log(PREFIX "prov_provisioning_failed(");
      sl_btmesh_evt_prov_provisioning_failed_t *data =
        &evt->data.evt_prov_provisioning_failed;
      app_log_append(" reason="); log_append_uint8_t(data->reason);
      app_log_append(" uuid="); log_append_uuid_128(data->uuid);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_prov_device_provisioned_id: {
      app_log(PREFIX "prov_device_provisioned(");
      sl_btmesh_evt_prov_device_provisioned_t *data =
        &evt->data.evt_prov_device_provisioned;
      app_log_append(" address="); log_append_uint16_t(data->address);
      app_log_append(" uuid="); log_append_uuid_128(data->uuid);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_prov_unprov_beacon_id: {
      app_log(PREFIX "prov_unprov_beacon(");
      sl_btmesh_evt_prov_unprov_beacon_t *data =
        &evt->data.evt_prov_unprov_beacon;
      app_log_append(" oob_capabilities="); log_append_uint16_t(data->oob_capabilities);
      app_log_append(" uri_hash="); log_append_uint32_t(data->uri_hash);
      app_log_append(" bearer="); log_append_uint8_t(data->bearer);
      app_log_append(" address="); log_append_bd_addr(data->address);
      app_log_append(" address_type="); log_append_uint8_t(data->address_type);
      app_log_append(" uuid="); log_append_uuid_128(data->uuid);
      app_log_append(" rssi="); log_append_int8_t(data->rssi);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_prov_oob_pkey_request_id: {
      app_log(PREFIX "prov_oob_pkey_request(");
      sl_btmesh_evt_prov_oob_pkey_request_t *data =
        &evt->data.evt_prov_oob_pkey_request;
      app_log_append(" uuid="); log_append_uuid_128(data->uuid);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_prov_oob_auth_request_id: {
      app_log(PREFIX "prov_oob_auth_request(");
      sl_btmesh_evt_prov_oob_auth_request_t *data =
        &evt->data.evt_prov_oob_auth_request;
      app_log_append(" output="); log_append_uint8_t(data->output);
      app_log_append(" output_action="); log_append_uint8_t(data->output_action);
      app_log_append(" output_size="); log_append_uint8_t(data->output_size);
      app_log_append(" uuid="); log_append_uuid_128(data->uuid);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_prov_oob_display_input_id: {
      app_log(PREFIX "prov_oob_display_input(");
      sl_btmesh_evt_prov_oob_display_input_t *data =
        &evt->data.evt_prov_oob_display_input;
      app_log_append(" uuid="); log_append_uuid_128(data->uuid);
      app_log_append(" input_action="); log_append_uint8_t(data->input_action);
      app_log_append(" input_size="); log_append_uint8_t(data->input_size);
      app_log_append(" data="); log_append_uint8array(data->data);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_prov_ddb_list_id: {
      app_log(PREFIX "prov_ddb_list(");
      sl_btmesh_evt_prov_ddb_list_t *data =
        &evt->data.evt_prov_ddb_list;
      app_log_append(" uuid="); log_append_uuid_128(data->uuid);
      app_log_append(" address="); log_append_uint16_t(data->address);
      app_log_append(" elements="); log_append_uint8_t(data->elements);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_prov_uri_id: {
      app_log(PREFIX "prov_uri(");
      sl_btmesh_evt_prov_uri_t *data =
        &evt->data.evt_prov_uri;
      app_log_append(" hash="); log_append_uint32_t(data->hash);
      app_log_append(" data="); log_append_uint8array(data->data);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_prov_key_refresh_phase_update_id: {
      app_log(PREFIX "prov_key_refresh_phase_update(");
      sl_btmesh_evt_prov_key_refresh_phase_update_t *data =
        &evt->data.evt_prov_key_refresh_phase_update;
      app_log_append(" key="); log_append_uint16_t(data->key);
      app_log_append(" phase="); log_append_uint8_t(data->phase);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_prov_key_refresh_node_update_id: {
      app_log(PREFIX "prov_key_refresh_node_update(");
      sl_btmesh_evt_prov_key_refresh_node_update_t *data =
        &evt->data.evt_prov_key_refresh_node_update;
      app_log_append(" key="); log_append_uint16_t(data->key);
      app_log_append(" phase="); log_append_uint8_t(data->phase);
      app_log_append(" uuid="); log_append_uuid_128(data->uuid);
      app_log_append(" failure="); log_append_uint8_t(data->failure);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_prov_key_refresh_complete_id: {
      app_log(PREFIX "prov_key_refresh_complete(");
      sl_btmesh_evt_prov_key_refresh_complete_t *data =
        &evt->data.evt_prov_key_refresh_complete;
      app_log_append(" key="); log_append_uint16_t(data->key);
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_prov_add_ddb_entry_complete_id: {
      app_log(PREFIX "prov_add_ddb_entry_complete(");
      sl_btmesh_evt_prov_add_ddb_entry_complete_t *data =
        &evt->data.evt_prov_add_ddb_entry_complete;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" uuid="); log_append_uuid_128(data->uuid);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_prov_delete_ddb_entry_complete_id: {
      app_log(PREFIX "prov_delete_ddb_entry_complete(");
      sl_btmesh_evt_prov_delete_ddb_entry_complete_t *data =
        &evt->data.evt_prov_delete_ddb_entry_complete;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" uuid="); log_append_uuid_128(data->uuid);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_prov_initialization_failed_id: {
      app_log(PREFIX "prov_initialization_failed(");
      sl_btmesh_evt_prov_initialization_failed_t *data =
        &evt->data.evt_prov_initialization_failed;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_prov_provisioning_records_list_id: {
      app_log(PREFIX "prov_provisioning_records_list(");
      sl_btmesh_evt_prov_provisioning_records_list_t *data =
        &evt->data.evt_prov_provisioning_records_list;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" uuid="); log_append_uuid_128(data->uuid);
      app_log_append(" list="); log_append_uint8array(data->list);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_prov_provisioning_record_data_id: {
      app_log(PREFIX "prov_provisioning_record_data(");
      sl_btmesh_evt_prov_provisioning_record_data_t *data =
        &evt->data.evt_prov_provisioning_record_data;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" uuid="); log_append_uuid_128(data->uuid);
      app_log_append(" record="); log_append_uint16_t(data->record);
      app_log_append(" final="); log_append_uint8_t(data->final);
      app_log_append(" data="); log_append_uint8array(data->data);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_prov_start_sent_id: {
      app_log(PREFIX "prov_start_sent(");
      sl_btmesh_evt_prov_start_sent_t *data =
        &evt->data.evt_prov_start_sent;
      app_log_append(" uuid="); log_append_uuid_128(data->uuid);
      app_log_append(" algorithm="); log_append_uint8_t(data->algorithm);
      app_log_append(" public_key="); log_append_uint8_t(data->public_key);
      app_log_append(" authentication_method="); log_append_uint8_t(data->authentication_method);
      app_log_append(" authentication_action="); log_append_uint8_t(data->authentication_action);
      app_log_append(" authentication_size="); log_append_uint8_t(data->authentication_size);
      app_log_append(" )" NL);
    } break;

    // proxy
    // Bluetooth Mesh Proxy Connections
    case sl_btmesh_evt_proxy_connected_id: {
      app_log(PREFIX "proxy_connected(");
      sl_btmesh_evt_proxy_connected_t *data =
        &evt->data.evt_proxy_connected;
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_proxy_disconnected_id: {
      app_log(PREFIX "proxy_disconnected(");
      sl_btmesh_evt_proxy_disconnected_t *data =
        &evt->data.evt_proxy_disconnected;
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" reason="); log_append_uint16_t(data->reason);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_proxy_filter_status_id: {
      app_log(PREFIX "proxy_filter_status(");
      sl_btmesh_evt_proxy_filter_status_t *data =
        &evt->data.evt_proxy_filter_status;
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" type="); log_append_uint8_t(data->type);
      app_log_append(" count="); log_append_uint16_t(data->count);
      app_log_append(" )" NL);
    } break;

    // silabs_config_client
    // Bluetooth Mesh Silabs Configuration Client Vendor Model
    case sl_btmesh_evt_silabs_config_client_tx_status_id: {
      app_log(PREFIX "silabs_config_client_tx_status(");
      sl_btmesh_evt_silabs_config_client_tx_status_t *data =
        &evt->data.evt_silabs_config_client_tx_status;
      app_log_append(" server="); log_append_uint16_t(data->server);
      app_log_append(" status="); log_append_uint8_t(data->status);
      app_log_append(" tx_phy="); log_append_uint8_t(data->tx_phy);
      app_log_append(" tx_options_bitmap="); log_append_uint32_t(data->tx_options_bitmap);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_silabs_config_client_model_status_id: {
      app_log(PREFIX "silabs_config_client_model_status(");
      sl_btmesh_evt_silabs_config_client_model_status_t *data =
        &evt->data.evt_silabs_config_client_model_status;
      app_log_append(" server="); log_append_uint16_t(data->server);
      app_log_append(" status="); log_append_uint8_t(data->status);
      app_log_append(" elem_index="); log_append_uint8_t(data->elem_index);
      app_log_append(" vendor_id="); log_append_uint16_t(data->vendor_id);
      app_log_append(" model_id="); log_append_uint16_t(data->model_id);
      app_log_append(" value="); log_append_uint16_t(data->value);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_silabs_config_client_network_pdu_status_id: {
      app_log(PREFIX "silabs_config_client_network_pdu_status(");
      sl_btmesh_evt_silabs_config_client_network_pdu_status_t *data =
        &evt->data.evt_silabs_config_client_network_pdu_status;
      app_log_append(" server="); log_append_uint16_t(data->server);
      app_log_append(" status="); log_append_uint8_t(data->status);
      app_log_append(" pdu_max_size="); log_append_uint16_t(data->pdu_max_size);
      app_log_append(" )" NL);
    } break;

    // vendor_model
    // Bluetooth Mesh Vendor Model
    case sl_btmesh_evt_vendor_model_receive_id: {
      app_log(PREFIX "vendor_model_receive(");
      sl_btmesh_evt_vendor_model_receive_t *data =
        &evt->data.evt_vendor_model_receive;
      app_log_append(" destination_address="); log_append_uint16_t(data->destination_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" vendor_id="); log_append_uint16_t(data->vendor_id);
      app_log_append(" model_id="); log_append_uint16_t(data->model_id);
      app_log_append(" source_address="); log_append_uint16_t(data->source_address);
      app_log_append(" va_index="); log_append_int8_t(data->va_index);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" nonrelayed="); log_append_uint8_t(data->nonrelayed);
      app_log_append(" message_flags="); log_append_uint8_t(data->message_flags);
      app_log_append(" opcode="); log_append_uint8_t(data->opcode);
      app_log_append(" final="); log_append_uint8_t(data->final);
      app_log_append(" payload="); log_append_uint8array(data->payload);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_vendor_model_send_complete_id: {
      app_log(PREFIX "vendor_model_send_complete(");
      sl_btmesh_evt_vendor_model_send_complete_t *data =
        &evt->data.evt_vendor_model_send_complete;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" handle="); log_append_uint16_t(data->handle);
      app_log_append(" message_flags="); log_append_uint8_t(data->message_flags);
      app_log_append(" )" NL);
    } break;

    // health_client
    // Bluetooth Mesh Health Client Model
    case sl_btmesh_evt_health_client_server_status_id: {
      app_log(PREFIX "health_client_server_status(");
      sl_btmesh_evt_health_client_server_status_t *data =
        &evt->data.evt_health_client_server_status;
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" current="); log_append_uint8_t(data->current);
      app_log_append(" test_id="); log_append_uint8_t(data->test_id);
      app_log_append(" vendor_id="); log_append_uint16_t(data->vendor_id);
      app_log_append(" faults="); log_append_uint8array(data->faults);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_health_client_server_status_period_id: {
      app_log(PREFIX "health_client_server_status_period(");
      sl_btmesh_evt_health_client_server_status_period_t *data =
        &evt->data.evt_health_client_server_status_period;
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" period="); log_append_uint8_t(data->period);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_health_client_server_status_attention_id: {
      app_log(PREFIX "health_client_server_status_attention(");
      sl_btmesh_evt_health_client_server_status_attention_t *data =
        &evt->data.evt_health_client_server_status_attention;
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" attention_sec="); log_append_uint8_t(data->attention_sec);
      app_log_append(" )" NL);
    } break;

    // health_server
    // Bluetooth Mesh Health Server Model
    case sl_btmesh_evt_health_server_attention_id: {
      app_log(PREFIX "health_server_attention(");
      sl_btmesh_evt_health_server_attention_t *data =
        &evt->data.evt_health_server_attention;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" timer_sec="); log_append_uint8_t(data->timer_sec);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_health_server_test_request_id: {
      app_log(PREFIX "health_server_test_request(");
      sl_btmesh_evt_health_server_test_request_t *data =
        &evt->data.evt_health_server_test_request;
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" test_id="); log_append_uint8_t(data->test_id);
      app_log_append(" vendor_id="); log_append_uint16_t(data->vendor_id);
      app_log_append(" response_required="); log_append_uint8_t(data->response_required);
      app_log_append(" )" NL);
    } break;

    // generic_client
    // Bluetooth Mesh Generic Client Model
    case sl_btmesh_evt_generic_client_server_status_id: {
      app_log(PREFIX "generic_client_server_status(");
      sl_btmesh_evt_generic_client_server_status_t *data =
        &evt->data.evt_generic_client_server_status;
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" model_id="); log_append_uint16_t(data->model_id);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" remaining_ms="); log_append_uint32_t(data->remaining_ms);
      app_log_append(" flags="); log_append_uint16_t(data->flags);
      app_log_append(" type="); log_append_uint8_t(data->type);
      app_log_append(" parameters="); log_append_uint8array(data->parameters);
      app_log_append(" )" NL);
    } break;

    // generic_server
    // Bluetooth Mesh Generic Server Model
    case sl_btmesh_evt_generic_server_client_request_id: {
      app_log(PREFIX "generic_server_client_request(");
      sl_btmesh_evt_generic_server_client_request_t *data =
        &evt->data.evt_generic_server_client_request;
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" model_id="); log_append_uint16_t(data->model_id);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" transition_ms="); log_append_uint32_t(data->transition_ms);
      app_log_append(" delay_ms="); log_append_uint16_t(data->delay_ms);
      app_log_append(" flags="); log_append_uint16_t(data->flags);
      app_log_append(" type="); log_append_uint8_t(data->type);
      app_log_append(" parameters="); log_append_uint8array(data->parameters);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_generic_server_state_changed_id: {
      app_log(PREFIX "generic_server_state_changed(");
      sl_btmesh_evt_generic_server_state_changed_t *data =
        &evt->data.evt_generic_server_state_changed;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" model_id="); log_append_uint16_t(data->model_id);
      app_log_append(" remaining_ms="); log_append_uint32_t(data->remaining_ms);
      app_log_append(" type="); log_append_uint8_t(data->type);
      app_log_append(" parameters="); log_append_uint8array(data->parameters);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_generic_server_state_recall_id: {
      app_log(PREFIX "generic_server_state_recall(");
      sl_btmesh_evt_generic_server_state_recall_t *data =
        &evt->data.evt_generic_server_state_recall;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" model_id="); log_append_uint16_t(data->model_id);
      app_log_append(" transition_time_ms="); log_append_uint32_t(data->transition_time_ms);
      app_log_append(" type="); log_append_uint8_t(data->type);
      app_log_append(" parameters="); log_append_uint8array(data->parameters);
      app_log_append(" )" NL);
    } break;

    // test
    // Bluetooth Mesh Test Utilities
    case sl_btmesh_evt_test_local_heartbeat_subscription_complete_id: {
      app_log(PREFIX "test_local_heartbeat_subscription_complete(");
      sl_btmesh_evt_test_local_heartbeat_subscription_complete_t *data =
        &evt->data.evt_test_local_heartbeat_subscription_complete;
      app_log_append(" count="); log_append_uint16_t(data->count);
      app_log_append(" hop_min="); log_append_uint8_t(data->hop_min);
      app_log_append(" hop_max="); log_append_uint8_t(data->hop_max);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_test_replay_protection_list_entry_set_id: {
      app_log(PREFIX "test_replay_protection_list_entry_set(");
      sl_btmesh_evt_test_replay_protection_list_entry_set_t *data =
        &evt->data.evt_test_replay_protection_list_entry_set;
      app_log_append(" address="); log_append_uint16_t(data->address);
      app_log_append(" cancel="); log_append_uint8_t(data->cancel);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_test_replay_protection_list_entry_cleared_id: {
      app_log(PREFIX "test_replay_protection_list_entry_cleared(");
      sl_btmesh_evt_test_replay_protection_list_entry_cleared_t *data =
        &evt->data.evt_test_replay_protection_list_entry_cleared;
      app_log_append(" address="); log_append_uint16_t(data->address);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_test_replay_protection_list_saved_id: {
      app_log(PREFIX "test_replay_protection_list_saved(");
      sl_btmesh_evt_test_replay_protection_list_saved_t *data =
        &evt->data.evt_test_replay_protection_list_saved;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" saved_count="); log_append_uint16_t(data->saved_count);
      app_log_append(" total_count="); log_append_uint16_t(data->total_count);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_test_replay_protection_list_full_id: {
      app_log(PREFIX "test_replay_protection_list_full(");
      app_log_append(" )" NL);
    } break;

    // lpn
    // Bluetooth Mesh Low Power Node API
    case sl_btmesh_evt_lpn_friendship_established_id: {
      app_log(PREFIX "lpn_friendship_established(");
      sl_btmesh_evt_lpn_friendship_established_t *data =
        &evt->data.evt_lpn_friendship_established;
      app_log_append(" netkey_index="); log_append_uint16_t(data->netkey_index);
      app_log_append(" friend_address="); log_append_uint16_t(data->friend_address);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_lpn_friendship_failed_id: {
      app_log(PREFIX "lpn_friendship_failed(");
      sl_btmesh_evt_lpn_friendship_failed_t *data =
        &evt->data.evt_lpn_friendship_failed;
      app_log_append(" netkey_index="); log_append_uint16_t(data->netkey_index);
      app_log_append(" reason="); log_append_uint16_t(data->reason);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_lpn_friendship_terminated_id: {
      app_log(PREFIX "lpn_friendship_terminated(");
      sl_btmesh_evt_lpn_friendship_terminated_t *data =
        &evt->data.evt_lpn_friendship_terminated;
      app_log_append(" netkey_index="); log_append_uint16_t(data->netkey_index);
      app_log_append(" reason="); log_append_uint16_t(data->reason);
      app_log_append(" )" NL);
    } break;

    // friend
    // Bluetooth Mesh Friend Node API
    case sl_btmesh_evt_friend_friendship_established_id: {
      app_log(PREFIX "friend_friendship_established(");
      sl_btmesh_evt_friend_friendship_established_t *data =
        &evt->data.evt_friend_friendship_established;
      app_log_append(" netkey_index="); log_append_uint16_t(data->netkey_index);
      app_log_append(" lpn_address="); log_append_uint16_t(data->lpn_address);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_friend_friendship_terminated_id: {
      app_log(PREFIX "friend_friendship_terminated(");
      sl_btmesh_evt_friend_friendship_terminated_t *data =
        &evt->data.evt_friend_friendship_terminated;
      app_log_append(" netkey_index="); log_append_uint16_t(data->netkey_index);
      app_log_append(" lpn_address="); log_append_uint16_t(data->lpn_address);
      app_log_append(" reason="); log_append_uint16_t(data->reason);
      app_log_append(" )" NL);
    } break;

    // proxy_client
    // Bluetooth Mesh GATT Proxy Client

    // proxy_server
    // Bluetooth Mesh GATT Proxy Server

    // config_client
    // Bluetooth Mesh Configuration Client Model
    case sl_btmesh_evt_config_client_request_modified_id: {
      app_log(PREFIX "config_client_request_modified(");
      sl_btmesh_evt_config_client_request_modified_t *data =
        &evt->data.evt_config_client_request_modified;
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_config_client_netkey_status_id: {
      app_log(PREFIX "config_client_netkey_status(");
      sl_btmesh_evt_config_client_netkey_status_t *data =
        &evt->data.evt_config_client_netkey_status;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_config_client_netkey_list_id: {
      app_log(PREFIX "config_client_netkey_list(");
      sl_btmesh_evt_config_client_netkey_list_t *data =
        &evt->data.evt_config_client_netkey_list;
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" netkey_indices="); log_append_uint8array(data->netkey_indices);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_config_client_netkey_list_end_id: {
      app_log(PREFIX "config_client_netkey_list_end(");
      sl_btmesh_evt_config_client_netkey_list_end_t *data =
        &evt->data.evt_config_client_netkey_list_end;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_config_client_appkey_status_id: {
      app_log(PREFIX "config_client_appkey_status(");
      sl_btmesh_evt_config_client_appkey_status_t *data =
        &evt->data.evt_config_client_appkey_status;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_config_client_appkey_list_id: {
      app_log(PREFIX "config_client_appkey_list(");
      sl_btmesh_evt_config_client_appkey_list_t *data =
        &evt->data.evt_config_client_appkey_list;
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" appkey_indices="); log_append_uint8array(data->appkey_indices);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_config_client_appkey_list_end_id: {
      app_log(PREFIX "config_client_appkey_list_end(");
      sl_btmesh_evt_config_client_appkey_list_end_t *data =
        &evt->data.evt_config_client_appkey_list_end;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_config_client_binding_status_id: {
      app_log(PREFIX "config_client_binding_status(");
      sl_btmesh_evt_config_client_binding_status_t *data =
        &evt->data.evt_config_client_binding_status;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_config_client_bindings_list_id: {
      app_log(PREFIX "config_client_bindings_list(");
      sl_btmesh_evt_config_client_bindings_list_t *data =
        &evt->data.evt_config_client_bindings_list;
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" appkey_indices="); log_append_uint8array(data->appkey_indices);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_config_client_bindings_list_end_id: {
      app_log(PREFIX "config_client_bindings_list_end(");
      sl_btmesh_evt_config_client_bindings_list_end_t *data =
        &evt->data.evt_config_client_bindings_list_end;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_config_client_model_pub_status_id: {
      app_log(PREFIX "config_client_model_pub_status(");
      sl_btmesh_evt_config_client_model_pub_status_t *data =
        &evt->data.evt_config_client_model_pub_status;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" address="); log_append_uint16_t(data->address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" credentials="); log_append_uint8_t(data->credentials);
      app_log_append(" ttl="); log_append_uint8_t(data->ttl);
      app_log_append(" period_ms="); log_append_uint32_t(data->period_ms);
      app_log_append(" retransmit_count="); log_append_uint8_t(data->retransmit_count);
      app_log_append(" retransmit_interval_ms="); log_append_uint16_t(data->retransmit_interval_ms);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_config_client_model_sub_status_id: {
      app_log(PREFIX "config_client_model_sub_status(");
      sl_btmesh_evt_config_client_model_sub_status_t *data =
        &evt->data.evt_config_client_model_sub_status;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_config_client_subs_list_id: {
      app_log(PREFIX "config_client_subs_list(");
      sl_btmesh_evt_config_client_subs_list_t *data =
        &evt->data.evt_config_client_subs_list;
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" addresses="); log_append_uint8array(data->addresses);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_config_client_subs_list_end_id: {
      app_log(PREFIX "config_client_subs_list_end(");
      sl_btmesh_evt_config_client_subs_list_end_t *data =
        &evt->data.evt_config_client_subs_list_end;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_config_client_heartbeat_pub_status_id: {
      app_log(PREFIX "config_client_heartbeat_pub_status(");
      sl_btmesh_evt_config_client_heartbeat_pub_status_t *data =
        &evt->data.evt_config_client_heartbeat_pub_status;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" destination_address="); log_append_uint16_t(data->destination_address);
      app_log_append(" netkey_index="); log_append_uint16_t(data->netkey_index);
      app_log_append(" count_log="); log_append_uint8_t(data->count_log);
      app_log_append(" period_log="); log_append_uint8_t(data->period_log);
      app_log_append(" ttl="); log_append_uint8_t(data->ttl);
      app_log_append(" features="); log_append_uint16_t(data->features);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_config_client_heartbeat_sub_status_id: {
      app_log(PREFIX "config_client_heartbeat_sub_status(");
      sl_btmesh_evt_config_client_heartbeat_sub_status_t *data =
        &evt->data.evt_config_client_heartbeat_sub_status;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" source_address="); log_append_uint16_t(data->source_address);
      app_log_append(" destination_address="); log_append_uint16_t(data->destination_address);
      app_log_append(" period_log="); log_append_uint8_t(data->period_log);
      app_log_append(" count_log="); log_append_uint8_t(data->count_log);
      app_log_append(" min_hops="); log_append_uint8_t(data->min_hops);
      app_log_append(" max_hops="); log_append_uint8_t(data->max_hops);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_config_client_beacon_status_id: {
      app_log(PREFIX "config_client_beacon_status(");
      sl_btmesh_evt_config_client_beacon_status_t *data =
        &evt->data.evt_config_client_beacon_status;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" value="); log_append_uint8_t(data->value);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_config_client_default_ttl_status_id: {
      app_log(PREFIX "config_client_default_ttl_status(");
      sl_btmesh_evt_config_client_default_ttl_status_t *data =
        &evt->data.evt_config_client_default_ttl_status;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" value="); log_append_uint8_t(data->value);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_config_client_gatt_proxy_status_id: {
      app_log(PREFIX "config_client_gatt_proxy_status(");
      sl_btmesh_evt_config_client_gatt_proxy_status_t *data =
        &evt->data.evt_config_client_gatt_proxy_status;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" value="); log_append_uint8_t(data->value);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_config_client_relay_status_id: {
      app_log(PREFIX "config_client_relay_status(");
      sl_btmesh_evt_config_client_relay_status_t *data =
        &evt->data.evt_config_client_relay_status;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" relay="); log_append_uint8_t(data->relay);
      app_log_append(" retransmit_count="); log_append_uint8_t(data->retransmit_count);
      app_log_append(" retransmit_interval_ms="); log_append_uint16_t(data->retransmit_interval_ms);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_config_client_network_transmit_status_id: {
      app_log(PREFIX "config_client_network_transmit_status(");
      sl_btmesh_evt_config_client_network_transmit_status_t *data =
        &evt->data.evt_config_client_network_transmit_status;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" transmit_count="); log_append_uint8_t(data->transmit_count);
      app_log_append(" transmit_interval_ms="); log_append_uint16_t(data->transmit_interval_ms);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_config_client_identity_status_id: {
      app_log(PREFIX "config_client_identity_status(");
      sl_btmesh_evt_config_client_identity_status_t *data =
        &evt->data.evt_config_client_identity_status;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" value="); log_append_uint8_t(data->value);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_config_client_friend_status_id: {
      app_log(PREFIX "config_client_friend_status(");
      sl_btmesh_evt_config_client_friend_status_t *data =
        &evt->data.evt_config_client_friend_status;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" value="); log_append_uint8_t(data->value);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_config_client_key_refresh_phase_status_id: {
      app_log(PREFIX "config_client_key_refresh_phase_status(");
      sl_btmesh_evt_config_client_key_refresh_phase_status_t *data =
        &evt->data.evt_config_client_key_refresh_phase_status;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" netkey_index="); log_append_uint16_t(data->netkey_index);
      app_log_append(" value="); log_append_uint8_t(data->value);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_config_client_lpn_polltimeout_status_id: {
      app_log(PREFIX "config_client_lpn_polltimeout_status(");
      sl_btmesh_evt_config_client_lpn_polltimeout_status_t *data =
        &evt->data.evt_config_client_lpn_polltimeout_status;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" poll_timeout_ms="); log_append_uint32_t(data->poll_timeout_ms);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_config_client_dcd_data_id: {
      app_log(PREFIX "config_client_dcd_data(");
      sl_btmesh_evt_config_client_dcd_data_t *data =
        &evt->data.evt_config_client_dcd_data;
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" page="); log_append_uint8_t(data->page);
      app_log_append(" data="); log_append_uint8array(data->data);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_config_client_dcd_data_end_id: {
      app_log(PREFIX "config_client_dcd_data_end(");
      sl_btmesh_evt_config_client_dcd_data_end_t *data =
        &evt->data.evt_config_client_dcd_data_end;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_config_client_reset_status_id: {
      app_log(PREFIX "config_client_reset_status(");
      sl_btmesh_evt_config_client_reset_status_t *data =
        &evt->data.evt_config_client_reset_status;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_config_client_obo_ack_received_id: {
      app_log(PREFIX "config_client_obo_ack_received(");
      sl_btmesh_evt_config_client_obo_ack_received_t *data =
        &evt->data.evt_config_client_obo_ack_received;
      app_log_append(" lpn_addr="); log_append_uint16_t(data->lpn_addr);
      app_log_append(" friend_addr="); log_append_uint16_t(data->friend_addr);
      app_log_append(" )" NL);
    } break;

    // mbt_client
    // Bluetooth Mesh BLOB Transfer Client Model
    case sl_btmesh_evt_mbt_client_server_information_status_id: {
      app_log(PREFIX "mbt_client_server_information_status(");
      sl_btmesh_evt_mbt_client_server_information_status_t *data =
        &evt->data.evt_mbt_client_server_information_status;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" min_block_size_log="); log_append_uint8_t(data->min_block_size_log);
      app_log_append(" max_block_size_log="); log_append_uint8_t(data->max_block_size_log);
      app_log_append(" max_chunks="); log_append_uint16_t(data->max_chunks);
      app_log_append(" max_chunk_size="); log_append_uint16_t(data->max_chunk_size);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_mbt_client_query_information_complete_id: {
      app_log(PREFIX "mbt_client_query_information_complete(");
      sl_btmesh_evt_mbt_client_query_information_complete_t *data =
        &evt->data.evt_mbt_client_query_information_complete;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" block_size_log_min="); log_append_uint8_t(data->block_size_log_min);
      app_log_append(" block_size_log_max="); log_append_uint8_t(data->block_size_log_max);
      app_log_append(" max_chunk_size_min="); log_append_uint16_t(data->max_chunk_size_min);
      app_log_append(" max_chunks_min="); log_append_uint16_t(data->max_chunks_min);
      app_log_append(" supported_transfer_modes="); log_append_uint8_t(data->supported_transfer_modes);
      app_log_append(" common_transfer_modes="); log_append_uint8_t(data->common_transfer_modes);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_mbt_client_server_transfer_status_id: {
      app_log(PREFIX "mbt_client_server_transfer_status(");
      sl_btmesh_evt_mbt_client_server_transfer_status_t *data =
        &evt->data.evt_mbt_client_server_transfer_status;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" status="); log_append_uint8_t(data->status);
      app_log_append(" phase="); log_append_uint8_t(data->phase);
      app_log_append(" blob_id="); log_append_sl_bt_uuid_64_t(data->blob_id);
      app_log_append(" blob_size="); log_append_uint32_t(data->blob_size);
      app_log_append(" block_size_log="); log_append_uint8_t(data->block_size_log);
      app_log_append(" blocks_not_received="); log_append_uint8array(data->blocks_not_received);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_mbt_client_start_transfer_complete_id: {
      app_log(PREFIX "mbt_client_start_transfer_complete(");
      sl_btmesh_evt_mbt_client_start_transfer_complete_t *data =
        &evt->data.evt_mbt_client_start_transfer_complete;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_mbt_client_server_block_status_id: {
      app_log(PREFIX "mbt_client_server_block_status(");
      sl_btmesh_evt_mbt_client_server_block_status_t *data =
        &evt->data.evt_mbt_client_server_block_status;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" status="); log_append_uint8_t(data->status);
      app_log_append(" missing_chunks="); log_append_uint8array(data->missing_chunks);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_mbt_client_start_block_complete_id: {
      app_log(PREFIX "mbt_client_start_block_complete(");
      sl_btmesh_evt_mbt_client_start_block_complete_t *data =
        &evt->data.evt_mbt_client_start_block_complete;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" block_number="); log_append_uint16_t(data->block_number);
      app_log_append(" block_size="); log_append_uint32_t(data->block_size);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_mbt_client_send_chunk_request_id: {
      app_log(PREFIX "mbt_client_send_chunk_request(");
      sl_btmesh_evt_mbt_client_send_chunk_request_t *data =
        &evt->data.evt_mbt_client_send_chunk_request;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" offset="); log_append_uint32_t(data->offset);
      app_log_append(" length="); log_append_uint16_t(data->length);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_mbt_client_server_partial_block_report_id: {
      app_log(PREFIX "mbt_client_server_partial_block_report(");
      sl_btmesh_evt_mbt_client_server_partial_block_report_t *data =
        &evt->data.evt_mbt_client_server_partial_block_report;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" missing_chunks="); log_append_uint8array(data->missing_chunks);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_mbt_client_send_chunks_complete_id: {
      app_log(PREFIX "mbt_client_send_chunks_complete(");
      sl_btmesh_evt_mbt_client_send_chunks_complete_t *data =
        &evt->data.evt_mbt_client_send_chunks_complete;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_mbt_client_query_block_status_complete_id: {
      app_log(PREFIX "mbt_client_query_block_status_complete(");
      sl_btmesh_evt_mbt_client_query_block_status_complete_t *data =
        &evt->data.evt_mbt_client_query_block_status_complete;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" block_complete="); log_append_uint8_t(data->block_complete);
      app_log_append(" transfer_complete="); log_append_uint8_t(data->transfer_complete);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_mbt_client_tx_complete_id: {
      app_log(PREFIX "mbt_client_tx_complete(");
      sl_btmesh_evt_mbt_client_tx_complete_t *data =
        &evt->data.evt_mbt_client_tx_complete;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_mbt_client_server_failed_id: {
      app_log(PREFIX "mbt_client_server_failed(");
      sl_btmesh_evt_mbt_client_server_failed_t *data =
        &evt->data.evt_mbt_client_server_failed;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" timeout="); log_append_uint8_t(data->timeout);
      app_log_append(" error="); log_append_uint8_t(data->error);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_mbt_client_transfer_complete_id: {
      app_log(PREFIX "mbt_client_transfer_complete(");
      sl_btmesh_evt_mbt_client_transfer_complete_t *data =
        &evt->data.evt_mbt_client_transfer_complete;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" )" NL);
    } break;

    // mbt_server
    // Bluetooth Mesh BLOB Transfer Server Model
    case sl_btmesh_evt_mbt_server_state_changed_id: {
      app_log(PREFIX "mbt_server_state_changed(");
      sl_btmesh_evt_mbt_server_state_changed_t *data =
        &evt->data.evt_mbt_server_state_changed;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" new_state="); log_append_uint8_t(data->new_state);
      app_log_append(" blob_id="); log_append_sl_bt_uuid_64_t(data->blob_id);
      app_log_append(" blob_size="); log_append_uint32_t(data->blob_size);
      app_log_append(" block_number="); log_append_uint16_t(data->block_number);
      app_log_append(" block_size="); log_append_uint32_t(data->block_size);
      app_log_append(" chunk_size="); log_append_uint16_t(data->chunk_size);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_mbt_server_transfer_start_req_id: {
      app_log(PREFIX "mbt_server_transfer_start_req(");
      sl_btmesh_evt_mbt_server_transfer_start_req_t *data =
        &evt->data.evt_mbt_server_transfer_start_req;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" blob_id="); log_append_sl_bt_uuid_64_t(data->blob_id);
      app_log_append(" blob_size="); log_append_uint32_t(data->blob_size);
      app_log_append(" block_size_log="); log_append_uint8_t(data->block_size_log);
      app_log_append(" transfer_mode="); log_append_uint8_t(data->transfer_mode);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_mbt_server_block_start_id: {
      app_log(PREFIX "mbt_server_block_start(");
      sl_btmesh_evt_mbt_server_block_start_t *data =
        &evt->data.evt_mbt_server_block_start;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" blob_id="); log_append_sl_bt_uuid_64_t(data->blob_id);
      app_log_append(" block_number="); log_append_uint16_t(data->block_number);
      app_log_append(" chunk_size="); log_append_uint16_t(data->chunk_size);
      app_log_append(" block_size="); log_append_uint16_t(data->block_size);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_mbt_server_chunk_id: {
      app_log(PREFIX "mbt_server_chunk(");
      sl_btmesh_evt_mbt_server_chunk_t *data =
        &evt->data.evt_mbt_server_chunk;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" block_number="); log_append_uint16_t(data->block_number);
      app_log_append(" total_offset="); log_append_uint32_t(data->total_offset);
      app_log_append(" block_offset="); log_append_uint32_t(data->block_offset);
      app_log_append(" data="); log_append_uint8array(data->data);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_mbt_server_block_complete_id: {
      app_log(PREFIX "mbt_server_block_complete(");
      sl_btmesh_evt_mbt_server_block_complete_t *data =
        &evt->data.evt_mbt_server_block_complete;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" blob_id="); log_append_sl_bt_uuid_64_t(data->blob_id);
      app_log_append(" block_number="); log_append_uint16_t(data->block_number);
      app_log_append(" block_size="); log_append_uint16_t(data->block_size);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_mbt_server_transfer_cancel_id: {
      app_log(PREFIX "mbt_server_transfer_cancel(");
      sl_btmesh_evt_mbt_server_transfer_cancel_t *data =
        &evt->data.evt_mbt_server_transfer_cancel;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" blob_id="); log_append_sl_bt_uuid_64_t(data->blob_id);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_mbt_server_partial_block_report_tx_complete_id: {
      app_log(PREFIX "mbt_server_partial_block_report_tx_complete(");
      sl_btmesh_evt_mbt_server_partial_block_report_tx_complete_t *data =
        &evt->data.evt_mbt_server_partial_block_report_tx_complete;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" num_requested_chunks="); log_append_uint16_t(data->num_requested_chunks);
      app_log_append(" requested_chunks="); log_append_uint8array(data->requested_chunks);
      app_log_append(" )" NL);
    } break;

    // sensor_server
    // Bluetooth Mesh Sensor Server Model
    case sl_btmesh_evt_sensor_server_get_request_id: {
      app_log(PREFIX "sensor_server_get_request(");
      sl_btmesh_evt_sensor_server_get_request_t *data =
        &evt->data.evt_sensor_server_get_request;
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" flags="); log_append_uint8_t(data->flags);
      app_log_append(" property_id="); log_append_uint16_t(data->property_id);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_sensor_server_get_column_request_id: {
      app_log(PREFIX "sensor_server_get_column_request(");
      sl_btmesh_evt_sensor_server_get_column_request_t *data =
        &evt->data.evt_sensor_server_get_column_request;
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" flags="); log_append_uint8_t(data->flags);
      app_log_append(" property_id="); log_append_uint16_t(data->property_id);
      app_log_append(" column_ids="); log_append_uint8array(data->column_ids);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_sensor_server_get_series_request_id: {
      app_log(PREFIX "sensor_server_get_series_request(");
      sl_btmesh_evt_sensor_server_get_series_request_t *data =
        &evt->data.evt_sensor_server_get_series_request;
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" flags="); log_append_uint8_t(data->flags);
      app_log_append(" property_id="); log_append_uint16_t(data->property_id);
      app_log_append(" column_ids="); log_append_uint8array(data->column_ids);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_sensor_server_publish_id: {
      app_log(PREFIX "sensor_server_publish(");
      sl_btmesh_evt_sensor_server_publish_t *data =
        &evt->data.evt_sensor_server_publish;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" period_ms="); log_append_uint32_t(data->period_ms);
      app_log_append(" )" NL);
    } break;

    // sensor_setup_server
    // Bluetooth Mesh Sensor Setup Server Model
    case sl_btmesh_evt_sensor_setup_server_get_cadence_request_id: {
      app_log(PREFIX "sensor_setup_server_get_cadence_request(");
      sl_btmesh_evt_sensor_setup_server_get_cadence_request_t *data =
        &evt->data.evt_sensor_setup_server_get_cadence_request;
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" flags="); log_append_uint8_t(data->flags);
      app_log_append(" property_id="); log_append_uint16_t(data->property_id);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_sensor_setup_server_set_cadence_request_id: {
      app_log(PREFIX "sensor_setup_server_set_cadence_request(");
      sl_btmesh_evt_sensor_setup_server_set_cadence_request_t *data =
        &evt->data.evt_sensor_setup_server_set_cadence_request;
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" flags="); log_append_uint8_t(data->flags);
      app_log_append(" property_id="); log_append_uint16_t(data->property_id);
      app_log_append(" period_divisor="); log_append_uint8_t(data->period_divisor);
      app_log_append(" trigger_type="); log_append_uint8_t(data->trigger_type);
      app_log_append(" params="); log_append_uint8array(data->params);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_sensor_setup_server_get_settings_request_id: {
      app_log(PREFIX "sensor_setup_server_get_settings_request(");
      sl_btmesh_evt_sensor_setup_server_get_settings_request_t *data =
        &evt->data.evt_sensor_setup_server_get_settings_request;
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" flags="); log_append_uint8_t(data->flags);
      app_log_append(" property_id="); log_append_uint16_t(data->property_id);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_sensor_setup_server_get_setting_request_id: {
      app_log(PREFIX "sensor_setup_server_get_setting_request(");
      sl_btmesh_evt_sensor_setup_server_get_setting_request_t *data =
        &evt->data.evt_sensor_setup_server_get_setting_request;
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" flags="); log_append_uint8_t(data->flags);
      app_log_append(" property_id="); log_append_uint16_t(data->property_id);
      app_log_append(" setting_id="); log_append_uint16_t(data->setting_id);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_sensor_setup_server_set_setting_request_id: {
      app_log(PREFIX "sensor_setup_server_set_setting_request(");
      sl_btmesh_evt_sensor_setup_server_set_setting_request_t *data =
        &evt->data.evt_sensor_setup_server_set_setting_request;
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" flags="); log_append_uint8_t(data->flags);
      app_log_append(" property_id="); log_append_uint16_t(data->property_id);
      app_log_append(" setting_id="); log_append_uint16_t(data->setting_id);
      app_log_append(" raw_value="); log_append_uint8array(data->raw_value);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_sensor_setup_server_publish_id: {
      app_log(PREFIX "sensor_setup_server_publish(");
      sl_btmesh_evt_sensor_setup_server_publish_t *data =
        &evt->data.evt_sensor_setup_server_publish;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" period_ms="); log_append_uint32_t(data->period_ms);
      app_log_append(" )" NL);
    } break;

    // sensor_client
    // Bluetooth Mesh Sensor Client Model
    case sl_btmesh_evt_sensor_client_descriptor_status_id: {
      app_log(PREFIX "sensor_client_descriptor_status(");
      sl_btmesh_evt_sensor_client_descriptor_status_t *data =
        &evt->data.evt_sensor_client_descriptor_status;
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" flags="); log_append_uint8_t(data->flags);
      app_log_append(" descriptors="); log_append_uint8array(data->descriptors);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_sensor_client_cadence_status_id: {
      app_log(PREFIX "sensor_client_cadence_status(");
      sl_btmesh_evt_sensor_client_cadence_status_t *data =
        &evt->data.evt_sensor_client_cadence_status;
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" flags="); log_append_uint8_t(data->flags);
      app_log_append(" property_id="); log_append_uint16_t(data->property_id);
      app_log_append(" params="); log_append_uint8array(data->params);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_sensor_client_settings_status_id: {
      app_log(PREFIX "sensor_client_settings_status(");
      sl_btmesh_evt_sensor_client_settings_status_t *data =
        &evt->data.evt_sensor_client_settings_status;
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" flags="); log_append_uint8_t(data->flags);
      app_log_append(" property_id="); log_append_uint16_t(data->property_id);
      app_log_append(" setting_ids="); log_append_uint8array(data->setting_ids);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_sensor_client_setting_status_id: {
      app_log(PREFIX "sensor_client_setting_status(");
      sl_btmesh_evt_sensor_client_setting_status_t *data =
        &evt->data.evt_sensor_client_setting_status;
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" flags="); log_append_uint8_t(data->flags);
      app_log_append(" property_id="); log_append_uint16_t(data->property_id);
      app_log_append(" setting_id="); log_append_uint16_t(data->setting_id);
      app_log_append(" raw_value="); log_append_uint8array(data->raw_value);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_sensor_client_status_id: {
      app_log(PREFIX "sensor_client_status(");
      sl_btmesh_evt_sensor_client_status_t *data =
        &evt->data.evt_sensor_client_status;
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" flags="); log_append_uint8_t(data->flags);
      app_log_append(" sensor_data="); log_append_uint8array(data->sensor_data);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_sensor_client_column_status_id: {
      app_log(PREFIX "sensor_client_column_status(");
      sl_btmesh_evt_sensor_client_column_status_t *data =
        &evt->data.evt_sensor_client_column_status;
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" flags="); log_append_uint8_t(data->flags);
      app_log_append(" property_id="); log_append_uint16_t(data->property_id);
      app_log_append(" sensor_data="); log_append_uint8array(data->sensor_data);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_sensor_client_series_status_id: {
      app_log(PREFIX "sensor_client_series_status(");
      sl_btmesh_evt_sensor_client_series_status_t *data =
        &evt->data.evt_sensor_client_series_status;
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" flags="); log_append_uint8_t(data->flags);
      app_log_append(" property_id="); log_append_uint16_t(data->property_id);
      app_log_append(" sensor_data="); log_append_uint8array(data->sensor_data);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_sensor_client_publish_id: {
      app_log(PREFIX "sensor_client_publish(");
      sl_btmesh_evt_sensor_client_publish_t *data =
        &evt->data.evt_sensor_client_publish;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" period_ms="); log_append_uint32_t(data->period_ms);
      app_log_append(" )" NL);
    } break;

    // fw_update_client
    // Bluetooth Mesh Firmware Update Client Model
    case sl_btmesh_evt_fw_update_client_info_status_current_fwid_id: {
      app_log(PREFIX "fw_update_client_info_status_current_fwid(");
      sl_btmesh_evt_fw_update_client_info_status_current_fwid_t *data =
        &evt->data.evt_fw_update_client_info_status_current_fwid;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" index="); log_append_uint8_t(data->index);
      app_log_append(" count="); log_append_uint8_t(data->count);
      app_log_append(" current_fwid="); log_append_uint8array(data->current_fwid);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_update_client_info_status_update_uri_id: {
      app_log(PREFIX "fw_update_client_info_status_update_uri(");
      sl_btmesh_evt_fw_update_client_info_status_update_uri_t *data =
        &evt->data.evt_fw_update_client_info_status_update_uri;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" index="); log_append_uint8_t(data->index);
      app_log_append(" count="); log_append_uint8_t(data->count);
      app_log_append(" update_uri="); log_append_uint8array(data->update_uri);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_update_client_update_status_id: {
      app_log(PREFIX "fw_update_client_update_status(");
      sl_btmesh_evt_fw_update_client_update_status_t *data =
        &evt->data.evt_fw_update_client_update_status;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" status="); log_append_uint8_t(data->status);
      app_log_append(" phase="); log_append_uint8_t(data->phase);
      app_log_append(" additional_information="); log_append_uint8_t(data->additional_information);
      app_log_append(" update_timeout_base="); log_append_uint16_t(data->update_timeout_base);
      app_log_append(" distributor_ttl="); log_append_uint8_t(data->distributor_ttl);
      app_log_append(" blob_id="); log_append_sl_bt_uuid_64_t(data->blob_id);
      app_log_append(" fw_index="); log_append_uint8_t(data->fw_index);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_update_client_metadata_status_id: {
      app_log(PREFIX "fw_update_client_metadata_status(");
      sl_btmesh_evt_fw_update_client_metadata_status_t *data =
        &evt->data.evt_fw_update_client_metadata_status;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" status="); log_append_uint8_t(data->status);
      app_log_append(" additional_information="); log_append_uint8_t(data->additional_information);
      app_log_append(" fw_index="); log_append_uint8_t(data->fw_index);
      app_log_append(" )" NL);
    } break;

    // lc_client
    // Bluetooth Mesh Light Control Client Model
    case sl_btmesh_evt_lc_client_mode_status_id: {
      app_log(PREFIX "lc_client_mode_status(");
      sl_btmesh_evt_lc_client_mode_status_t *data =
        &evt->data.evt_lc_client_mode_status;
      app_log_append(" destination_address="); log_append_uint16_t(data->destination_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" mode_status_value="); log_append_uint8_t(data->mode_status_value);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_lc_client_om_status_id: {
      app_log(PREFIX "lc_client_om_status(");
      sl_btmesh_evt_lc_client_om_status_t *data =
        &evt->data.evt_lc_client_om_status;
      app_log_append(" destination_address="); log_append_uint16_t(data->destination_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" om_status_value="); log_append_uint8_t(data->om_status_value);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_lc_client_light_onoff_status_id: {
      app_log(PREFIX "lc_client_light_onoff_status(");
      sl_btmesh_evt_lc_client_light_onoff_status_t *data =
        &evt->data.evt_lc_client_light_onoff_status;
      app_log_append(" destination_address="); log_append_uint16_t(data->destination_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" present_light_onoff="); log_append_uint8_t(data->present_light_onoff);
      app_log_append(" target_light_onoff="); log_append_uint8_t(data->target_light_onoff);
      app_log_append(" remaining_time_ms="); log_append_uint32_t(data->remaining_time_ms);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_lc_client_property_status_id: {
      app_log(PREFIX "lc_client_property_status(");
      sl_btmesh_evt_lc_client_property_status_t *data =
        &evt->data.evt_lc_client_property_status;
      app_log_append(" destination_address="); log_append_uint16_t(data->destination_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" property_id="); log_append_uint16_t(data->property_id);
      app_log_append(" property_value="); log_append_uint8array(data->property_value);
      app_log_append(" )" NL);
    } break;

    // lc_server
    // Bluetooth Mesh Light Control Server Model
    case sl_btmesh_evt_lc_server_mode_updated_id: {
      app_log(PREFIX "lc_server_mode_updated(");
      sl_btmesh_evt_lc_server_mode_updated_t *data =
        &evt->data.evt_lc_server_mode_updated;
      app_log_append(" destination_address="); log_append_uint16_t(data->destination_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" mode_value="); log_append_uint8_t(data->mode_value);
      app_log_append(" manual_override="); log_append_uint8_t(data->manual_override);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_lc_server_om_updated_id: {
      app_log(PREFIX "lc_server_om_updated(");
      sl_btmesh_evt_lc_server_om_updated_t *data =
        &evt->data.evt_lc_server_om_updated;
      app_log_append(" destination_address="); log_append_uint16_t(data->destination_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" om_value="); log_append_uint8_t(data->om_value);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_lc_server_light_onoff_updated_id: {
      app_log(PREFIX "lc_server_light_onoff_updated(");
      sl_btmesh_evt_lc_server_light_onoff_updated_t *data =
        &evt->data.evt_lc_server_light_onoff_updated;
      app_log_append(" destination_address="); log_append_uint16_t(data->destination_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" source_address="); log_append_uint16_t(data->source_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" onoff_state="); log_append_uint8_t(data->onoff_state);
      app_log_append(" onoff_trans_time_ms="); log_append_uint32_t(data->onoff_trans_time_ms);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_lc_server_occupancy_updated_id: {
      app_log(PREFIX "lc_server_occupancy_updated(");
      sl_btmesh_evt_lc_server_occupancy_updated_t *data =
        &evt->data.evt_lc_server_occupancy_updated;
      app_log_append(" destination_address="); log_append_uint16_t(data->destination_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" source_address="); log_append_uint16_t(data->source_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" occupancy_value="); log_append_uint8_t(data->occupancy_value);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_lc_server_ambient_lux_level_updated_id: {
      app_log(PREFIX "lc_server_ambient_lux_level_updated(");
      sl_btmesh_evt_lc_server_ambient_lux_level_updated_t *data =
        &evt->data.evt_lc_server_ambient_lux_level_updated;
      app_log_append(" destination_address="); log_append_uint16_t(data->destination_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" source_address="); log_append_uint16_t(data->source_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" ambient_lux_level_value="); log_append_uint32_t(data->ambient_lux_level_value);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_lc_server_linear_output_updated_id: {
      app_log(PREFIX "lc_server_linear_output_updated(");
      sl_btmesh_evt_lc_server_linear_output_updated_t *data =
        &evt->data.evt_lc_server_linear_output_updated;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" linear_output_value="); log_append_uint16_t(data->linear_output_value);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_lc_server_state_updated_id: {
      app_log(PREFIX "lc_server_state_updated(");
      sl_btmesh_evt_lc_server_state_updated_t *data =
        &evt->data.evt_lc_server_state_updated;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" state="); log_append_uint8_t(data->state);
      app_log_append(" transition_time="); log_append_uint32_t(data->transition_time);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_lc_server_regulator_debug_info_id: {
      app_log(PREFIX "lc_server_regulator_debug_info(");
      sl_btmesh_evt_lc_server_regulator_debug_info_t *data =
        &evt->data.evt_lc_server_regulator_debug_info;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" i="); log_append_uint16_t(data->i);
      app_log_append(" l="); log_append_uint16_t(data->l);
      app_log_append(" )" NL);
    } break;

    // lc_setup_server
    // Bluetooth Mesh Light Control Setup Server Model
    case sl_btmesh_evt_lc_setup_server_set_property_id: {
      app_log(PREFIX "lc_setup_server_set_property(");
      sl_btmesh_evt_lc_setup_server_set_property_t *data =
        &evt->data.evt_lc_setup_server_set_property;
      app_log_append(" destination_address="); log_append_uint16_t(data->destination_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" property_id="); log_append_uint16_t(data->property_id);
      app_log_append(" property_value="); log_append_uint8array(data->property_value);
      app_log_append(" )" NL);
    } break;

    // scene_client
    // Bluetooth Mesh Scene Client Model
    case sl_btmesh_evt_scene_client_status_id: {
      app_log(PREFIX "scene_client_status(");
      sl_btmesh_evt_scene_client_status_t *data =
        &evt->data.evt_scene_client_status;
      app_log_append(" destination_address="); log_append_uint16_t(data->destination_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" status="); log_append_uint8_t(data->status);
      app_log_append(" current_scene="); log_append_uint16_t(data->current_scene);
      app_log_append(" target_scene="); log_append_uint16_t(data->target_scene);
      app_log_append(" remaining_time_ms="); log_append_uint32_t(data->remaining_time_ms);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_scene_client_register_status_id: {
      app_log(PREFIX "scene_client_register_status(");
      sl_btmesh_evt_scene_client_register_status_t *data =
        &evt->data.evt_scene_client_register_status;
      app_log_append(" destination_address="); log_append_uint16_t(data->destination_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" status="); log_append_uint8_t(data->status);
      app_log_append(" current_scene="); log_append_uint16_t(data->current_scene);
      app_log_append(" scenes="); log_append_uint8array(data->scenes);
      app_log_append(" )" NL);
    } break;

    // scene_server
    // Bluetooth Mesh Scene Server Model
    case sl_btmesh_evt_scene_server_get_id: {
      app_log(PREFIX "scene_server_get(");
      sl_btmesh_evt_scene_server_get_t *data =
        &evt->data.evt_scene_server_get;
      app_log_append(" destination_address="); log_append_uint16_t(data->destination_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_scene_server_register_get_id: {
      app_log(PREFIX "scene_server_register_get(");
      sl_btmesh_evt_scene_server_register_get_t *data =
        &evt->data.evt_scene_server_register_get;
      app_log_append(" destination_address="); log_append_uint16_t(data->destination_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_scene_server_recall_id: {
      app_log(PREFIX "scene_server_recall(");
      sl_btmesh_evt_scene_server_recall_t *data =
        &evt->data.evt_scene_server_recall;
      app_log_append(" destination_address="); log_append_uint16_t(data->destination_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" selected_scene="); log_append_uint16_t(data->selected_scene);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" transition_time_ms="); log_append_uint32_t(data->transition_time_ms);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_scene_server_publish_id: {
      app_log(PREFIX "scene_server_publish(");
      sl_btmesh_evt_scene_server_publish_t *data =
        &evt->data.evt_scene_server_publish;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" period_ms="); log_append_uint32_t(data->period_ms);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_scene_server_compact_recall_id: {
      app_log(PREFIX "scene_server_compact_recall(");
      sl_btmesh_evt_scene_server_compact_recall_t *data =
        &evt->data.evt_scene_server_compact_recall;
      app_log_append(" states="); log_append_uint8array(data->states);
      app_log_append(" )" NL);
    } break;

    // scene_setup_server
    // Bluetooth Mesh Scene Setup Server Model
    case sl_btmesh_evt_scene_setup_server_store_id: {
      app_log(PREFIX "scene_setup_server_store(");
      sl_btmesh_evt_scene_setup_server_store_t *data =
        &evt->data.evt_scene_setup_server_store;
      app_log_append(" destination_address="); log_append_uint16_t(data->destination_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" scene_id="); log_append_uint16_t(data->scene_id);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_scene_setup_server_delete_id: {
      app_log(PREFIX "scene_setup_server_delete(");
      sl_btmesh_evt_scene_setup_server_delete_t *data =
        &evt->data.evt_scene_setup_server_delete;
      app_log_append(" destination_address="); log_append_uint16_t(data->destination_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" scene_id="); log_append_uint16_t(data->scene_id);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_scene_setup_server_publish_id: {
      app_log(PREFIX "scene_setup_server_publish(");
      sl_btmesh_evt_scene_setup_server_publish_t *data =
        &evt->data.evt_scene_setup_server_publish;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" period_ms="); log_append_uint32_t(data->period_ms);
      app_log_append(" )" NL);
    } break;

    // scheduler_client
    // Bluetooth Mesh Scheduler Client Model
    case sl_btmesh_evt_scheduler_client_status_id: {
      app_log(PREFIX "scheduler_client_status(");
      sl_btmesh_evt_scheduler_client_status_t *data =
        &evt->data.evt_scheduler_client_status;
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" scheduler="); log_append_uint16_t(data->scheduler);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_scheduler_client_action_status_id: {
      app_log(PREFIX "scheduler_client_action_status(");
      sl_btmesh_evt_scheduler_client_action_status_t *data =
        &evt->data.evt_scheduler_client_action_status;
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" index="); log_append_uint8_t(data->index);
      app_log_append(" year="); log_append_uint8_t(data->year);
      app_log_append(" month="); log_append_uint16_t(data->month);
      app_log_append(" day="); log_append_uint8_t(data->day);
      app_log_append(" hour="); log_append_uint8_t(data->hour);
      app_log_append(" minute="); log_append_uint8_t(data->minute);
      app_log_append(" second="); log_append_uint8_t(data->second);
      app_log_append(" day_of_week="); log_append_uint8_t(data->day_of_week);
      app_log_append(" action="); log_append_uint8_t(data->action);
      app_log_append(" transition_time_ms="); log_append_uint32_t(data->transition_time_ms);
      app_log_append(" scene_number="); log_append_uint16_t(data->scene_number);
      app_log_append(" )" NL);
    } break;

    // scheduler_server
    // Bluetooth Mesh Scheduler Server Model
    case sl_btmesh_evt_scheduler_server_action_changed_id: {
      app_log(PREFIX "scheduler_server_action_changed(");
      sl_btmesh_evt_scheduler_server_action_changed_t *data =
        &evt->data.evt_scheduler_server_action_changed;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" index="); log_append_uint8_t(data->index);
      app_log_append(" year="); log_append_uint8_t(data->year);
      app_log_append(" month="); log_append_uint16_t(data->month);
      app_log_append(" day="); log_append_uint8_t(data->day);
      app_log_append(" hour="); log_append_uint8_t(data->hour);
      app_log_append(" minute="); log_append_uint8_t(data->minute);
      app_log_append(" second="); log_append_uint8_t(data->second);
      app_log_append(" day_of_week="); log_append_uint8_t(data->day_of_week);
      app_log_append(" action="); log_append_uint8_t(data->action);
      app_log_append(" transition_time_ms="); log_append_uint32_t(data->transition_time_ms);
      app_log_append(" scene_number="); log_append_uint16_t(data->scene_number);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_scheduler_server_scene_changed_id: {
      app_log(PREFIX "scheduler_server_scene_changed(");
      sl_btmesh_evt_scheduler_server_scene_changed_t *data =
        &evt->data.evt_scheduler_server_scene_changed;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" transition_time_ms="); log_append_uint32_t(data->transition_time_ms);
      app_log_append(" scene_number="); log_append_uint16_t(data->scene_number);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_scheduler_server_action_triggered_id: {
      app_log(PREFIX "scheduler_server_action_triggered(");
      sl_btmesh_evt_scheduler_server_action_triggered_t *data =
        &evt->data.evt_scheduler_server_action_triggered;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" index="); log_append_uint8_t(data->index);
      app_log_append(" action="); log_append_uint8_t(data->action);
      app_log_append(" transition_time_ms="); log_append_uint32_t(data->transition_time_ms);
      app_log_append(" scene_number="); log_append_uint16_t(data->scene_number);
      app_log_append(" )" NL);
    } break;

    // fw_update_server
    // Bluetooth Mesh Firmware Update Server Model
    case sl_btmesh_evt_fw_update_server_check_fw_metadata_req_id: {
      app_log(PREFIX "fw_update_server_check_fw_metadata_req(");
      sl_btmesh_evt_fw_update_server_check_fw_metadata_req_t *data =
        &evt->data.evt_fw_update_server_check_fw_metadata_req;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" fw_index="); log_append_uint8_t(data->fw_index);
      app_log_append(" metadata="); log_append_uint8array(data->metadata);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_update_server_update_start_req_id: {
      app_log(PREFIX "fw_update_server_update_start_req(");
      sl_btmesh_evt_fw_update_server_update_start_req_t *data =
        &evt->data.evt_fw_update_server_update_start_req;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" blob_id="); log_append_sl_bt_uuid_64_t(data->blob_id);
      app_log_append(" fw_index="); log_append_uint8_t(data->fw_index);
      app_log_append(" metadata="); log_append_uint8array(data->metadata);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_update_server_verify_fw_req_id: {
      app_log(PREFIX "fw_update_server_verify_fw_req(");
      sl_btmesh_evt_fw_update_server_verify_fw_req_t *data =
        &evt->data.evt_fw_update_server_verify_fw_req;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_update_server_apply_id: {
      app_log(PREFIX "fw_update_server_apply(");
      sl_btmesh_evt_fw_update_server_apply_t *data =
        &evt->data.evt_fw_update_server_apply;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_update_server_update_cancelled_id: {
      app_log(PREFIX "fw_update_server_update_cancelled(");
      sl_btmesh_evt_fw_update_server_update_cancelled_t *data =
        &evt->data.evt_fw_update_server_update_cancelled;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_update_server_distributor_self_update_req_id: {
      app_log(PREFIX "fw_update_server_distributor_self_update_req(");
      sl_btmesh_evt_fw_update_server_distributor_self_update_req_t *data =
        &evt->data.evt_fw_update_server_distributor_self_update_req;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" fw_index="); log_append_uint8_t(data->fw_index);
      app_log_append(" fw_list_index="); log_append_uint16_t(data->fw_list_index);
      app_log_append(" )" NL);
    } break;

    // time_server
    // Bluetooth Mesh Time Server Model
    case sl_btmesh_evt_time_server_time_updated_id: {
      app_log(PREFIX "time_server_time_updated(");
      sl_btmesh_evt_time_server_time_updated_t *data =
        &evt->data.evt_time_server_time_updated;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" tai_seconds="); log_append_uint64_t(data->tai_seconds);
      app_log_append(" subsecond="); log_append_uint8_t(data->subsecond);
      app_log_append(" uncertainty="); log_append_uint8_t(data->uncertainty);
      app_log_append(" time_authority="); log_append_uint8_t(data->time_authority);
      app_log_append(" tai_utc_delta="); log_append_int32_t(data->tai_utc_delta);
      app_log_append(" time_zone_offset="); log_append_int16_t(data->time_zone_offset);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_time_server_time_zone_offset_updated_id: {
      app_log(PREFIX "time_server_time_zone_offset_updated(");
      sl_btmesh_evt_time_server_time_zone_offset_updated_t *data =
        &evt->data.evt_time_server_time_zone_offset_updated;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" time_zone_offset_current="); log_append_int16_t(data->time_zone_offset_current);
      app_log_append(" time_zone_offset_new="); log_append_int16_t(data->time_zone_offset_new);
      app_log_append(" tai_of_zone_change="); log_append_uint64_t(data->tai_of_zone_change);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_time_server_tai_utc_delta_updated_id: {
      app_log(PREFIX "time_server_tai_utc_delta_updated(");
      sl_btmesh_evt_time_server_tai_utc_delta_updated_t *data =
        &evt->data.evt_time_server_tai_utc_delta_updated;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" tai_utc_delta_current="); log_append_int32_t(data->tai_utc_delta_current);
      app_log_append(" tai_utc_delta_new="); log_append_int32_t(data->tai_utc_delta_new);
      app_log_append(" tai_of_delta_change="); log_append_uint64_t(data->tai_of_delta_change);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_time_server_time_role_updated_id: {
      app_log(PREFIX "time_server_time_role_updated(");
      sl_btmesh_evt_time_server_time_role_updated_t *data =
        &evt->data.evt_time_server_time_role_updated;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" time_role="); log_append_uint8_t(data->time_role);
      app_log_append(" )" NL);
    } break;

    // time_client
    // Bluetooth Mesh Time Client Model
    case sl_btmesh_evt_time_client_time_status_id: {
      app_log(PREFIX "time_client_time_status(");
      sl_btmesh_evt_time_client_time_status_t *data =
        &evt->data.evt_time_client_time_status;
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" tai_seconds="); log_append_uint64_t(data->tai_seconds);
      app_log_append(" subsecond="); log_append_uint8_t(data->subsecond);
      app_log_append(" uncertainty="); log_append_uint8_t(data->uncertainty);
      app_log_append(" time_authority="); log_append_uint8_t(data->time_authority);
      app_log_append(" tai_utc_delta="); log_append_int32_t(data->tai_utc_delta);
      app_log_append(" time_zone_offset="); log_append_int16_t(data->time_zone_offset);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_time_client_time_zone_status_id: {
      app_log(PREFIX "time_client_time_zone_status(");
      sl_btmesh_evt_time_client_time_zone_status_t *data =
        &evt->data.evt_time_client_time_zone_status;
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" time_zone_offset_current="); log_append_int16_t(data->time_zone_offset_current);
      app_log_append(" time_zone_offset_new="); log_append_int16_t(data->time_zone_offset_new);
      app_log_append(" tai_of_zone_change="); log_append_uint64_t(data->tai_of_zone_change);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_time_client_tai_utc_delta_status_id: {
      app_log(PREFIX "time_client_tai_utc_delta_status(");
      sl_btmesh_evt_time_client_tai_utc_delta_status_t *data =
        &evt->data.evt_time_client_tai_utc_delta_status;
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" tai_utc_delta_current="); log_append_int32_t(data->tai_utc_delta_current);
      app_log_append(" tai_utc_delta_new="); log_append_int32_t(data->tai_utc_delta_new);
      app_log_append(" tai_of_delta_change="); log_append_uint64_t(data->tai_of_delta_change);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_time_client_time_role_status_id: {
      app_log(PREFIX "time_client_time_role_status(");
      sl_btmesh_evt_time_client_time_role_status_t *data =
        &evt->data.evt_time_client_time_role_status;
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" time_role="); log_append_uint8_t(data->time_role);
      app_log_append(" )" NL);
    } break;

    // fw_dist_server
    // Bluetooth Mesh Firmware Distribution Server Model
    case sl_btmesh_evt_fw_dist_server_nodes_added_id: {
      app_log(PREFIX "fw_dist_server_nodes_added(");
      sl_btmesh_evt_fw_dist_server_nodes_added_t *data =
        &evt->data.evt_fw_dist_server_nodes_added;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" total_nodes="); log_append_uint16_t(data->total_nodes);
      app_log_append(" num_added_nodes="); log_append_uint16_t(data->num_added_nodes);
      app_log_append(" added_nodes="); log_append_uint8array(data->added_nodes);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_dist_server_nodes_deleted_id: {
      app_log(PREFIX "fw_dist_server_nodes_deleted(");
      sl_btmesh_evt_fw_dist_server_nodes_deleted_t *data =
        &evt->data.evt_fw_dist_server_nodes_deleted;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_dist_server_dist_start_req_id: {
      app_log(PREFIX "fw_dist_server_dist_start_req(");
      sl_btmesh_evt_fw_dist_server_dist_start_req_t *data =
        &evt->data.evt_fw_dist_server_dist_start_req;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" group_address="); log_append_uint16_t(data->group_address);
      app_log_append(" virtual_address="); log_append_uuid_128(data->virtual_address);
      app_log_append(" ttl="); log_append_uint8_t(data->ttl);
      app_log_append(" apply_immediately="); log_append_uint8_t(data->apply_immediately);
      app_log_append(" fw_list_index="); log_append_uint16_t(data->fw_list_index);
      app_log_append(" timeout_base="); log_append_uint16_t(data->timeout_base);
      app_log_append(" transfer_mode="); log_append_uint8_t(data->transfer_mode);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_dist_server_dist_cancel_id: {
      app_log(PREFIX "fw_dist_server_dist_cancel(");
      sl_btmesh_evt_fw_dist_server_dist_cancel_t *data =
        &evt->data.evt_fw_dist_server_dist_cancel;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_dist_server_dist_cancel_complete_id: {
      app_log(PREFIX "fw_dist_server_dist_cancel_complete(");
      sl_btmesh_evt_fw_dist_server_dist_cancel_complete_t *data =
        &evt->data.evt_fw_dist_server_dist_cancel_complete;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_dist_server_upload_start_metadata_id: {
      app_log(PREFIX "fw_dist_server_upload_start_metadata(");
      sl_btmesh_evt_fw_dist_server_upload_start_metadata_t *data =
        &evt->data.evt_fw_dist_server_upload_start_metadata;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" metadata="); log_append_uint8array(data->metadata);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_dist_server_upload_start_req_id: {
      app_log(PREFIX "fw_dist_server_upload_start_req(");
      sl_btmesh_evt_fw_dist_server_upload_start_req_t *data =
        &evt->data.evt_fw_dist_server_upload_start_req;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" size="); log_append_uint32_t(data->size);
      app_log_append(" blob_id="); log_append_sl_bt_uuid_64_t(data->blob_id);
      app_log_append(" fwid="); log_append_uint8array(data->fwid);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_dist_server_upload_cancel_id: {
      app_log(PREFIX "fw_dist_server_upload_cancel(");
      sl_btmesh_evt_fw_dist_server_upload_cancel_t *data =
        &evt->data.evt_fw_dist_server_upload_cancel;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_dist_server_dist_state_changed_id: {
      app_log(PREFIX "fw_dist_server_dist_state_changed(");
      sl_btmesh_evt_fw_dist_server_dist_state_changed_t *data =
        &evt->data.evt_fw_dist_server_dist_state_changed;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" state="); log_append_uint8_t(data->state);
      app_log_append(" num_active_nodes="); log_append_uint16_t(data->num_active_nodes);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_dist_server_node_failed_id: {
      app_log(PREFIX "fw_dist_server_node_failed(");
      sl_btmesh_evt_fw_dist_server_node_failed_t *data =
        &evt->data.evt_fw_dist_server_node_failed;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" address="); log_append_uint16_t(data->address);
      app_log_append(" update_phase="); log_append_uint8_t(data->update_phase);
      app_log_append(" update_status="); log_append_uint8_t(data->update_status);
      app_log_append(" mbt_status="); log_append_uint8_t(data->mbt_status);
      app_log_append(" progress="); log_append_uint8_t(data->progress);
      app_log_append(" fw_index="); log_append_uint8_t(data->fw_index);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_dist_server_upload_complete_metadata_id: {
      app_log(PREFIX "fw_dist_server_upload_complete_metadata(");
      sl_btmesh_evt_fw_dist_server_upload_complete_metadata_t *data =
        &evt->data.evt_fw_dist_server_upload_complete_metadata;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" metadata="); log_append_uint8array(data->metadata);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_dist_server_upload_complete_id: {
      app_log(PREFIX "fw_dist_server_upload_complete(");
      sl_btmesh_evt_fw_dist_server_upload_complete_t *data =
        &evt->data.evt_fw_dist_server_upload_complete;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" size="); log_append_uint32_t(data->size);
      app_log_append(" blob_id="); log_append_sl_bt_uuid_64_t(data->blob_id);
      app_log_append(" fwid="); log_append_uint8array(data->fwid);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_dist_server_upload_failed_id: {
      app_log(PREFIX "fw_dist_server_upload_failed(");
      sl_btmesh_evt_fw_dist_server_upload_failed_t *data =
        &evt->data.evt_fw_dist_server_upload_failed;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" size="); log_append_uint32_t(data->size);
      app_log_append(" blob_id="); log_append_sl_bt_uuid_64_t(data->blob_id);
      app_log_append(" fwid="); log_append_uint8array(data->fwid);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_dist_server_upload_oob_start_uri_id: {
      app_log(PREFIX "fw_dist_server_upload_oob_start_uri(");
      sl_btmesh_evt_fw_dist_server_upload_oob_start_uri_t *data =
        &evt->data.evt_fw_dist_server_upload_oob_start_uri;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" uri="); log_append_uint8array(data->uri);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_dist_server_upload_oob_start_req_id: {
      app_log(PREFIX "fw_dist_server_upload_oob_start_req(");
      sl_btmesh_evt_fw_dist_server_upload_oob_start_req_t *data =
        &evt->data.evt_fw_dist_server_upload_oob_start_req;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" fwid="); log_append_uint8array(data->fwid);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_dist_server_fw_delete_req_id: {
      app_log(PREFIX "fw_dist_server_fw_delete_req(");
      sl_btmesh_evt_fw_dist_server_fw_delete_req_t *data =
        &evt->data.evt_fw_dist_server_fw_delete_req;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" fwid="); log_append_uint8array(data->fwid);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_dist_server_fw_delete_all_req_id: {
      app_log(PREFIX "fw_dist_server_fw_delete_all_req(");
      sl_btmesh_evt_fw_dist_server_fw_delete_all_req_t *data =
        &evt->data.evt_fw_dist_server_fw_delete_all_req;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_dist_server_dist_suspend_id: {
      app_log(PREFIX "fw_dist_server_dist_suspend(");
      sl_btmesh_evt_fw_dist_server_dist_suspend_t *data =
        &evt->data.evt_fw_dist_server_dist_suspend;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_dist_server_resume_req_id: {
      app_log(PREFIX "fw_dist_server_resume_req(");
      sl_btmesh_evt_fw_dist_server_resume_req_t *data =
        &evt->data.evt_fw_dist_server_resume_req;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" group_address="); log_append_uint16_t(data->group_address);
      app_log_append(" app_index="); log_append_uint16_t(data->app_index);
      app_log_append(" ttl="); log_append_uint16_t(data->ttl);
      app_log_append(" update_policy="); log_append_uint16_t(data->update_policy);
      app_log_append(" fw_index="); log_append_uint16_t(data->fw_index);
      app_log_append(" timeout_base="); log_append_uint16_t(data->timeout_base);
      app_log_append(" transfer_mode="); log_append_uint16_t(data->transfer_mode);
      app_log_append(" )" NL);
    } break;

    // fw_dist_client
    // Bluetooth Mesh Firmware Distribution Client Model
    case sl_btmesh_evt_fw_dist_client_receivers_status_id: {
      app_log(PREFIX "fw_dist_client_receivers_status(");
      sl_btmesh_evt_fw_dist_client_receivers_status_t *data =
        &evt->data.evt_fw_dist_client_receivers_status;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" status="); log_append_uint8_t(data->status);
      app_log_append(" nodes_list_size="); log_append_uint16_t(data->nodes_list_size);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_dist_client_receivers_list_id: {
      app_log(PREFIX "fw_dist_client_receivers_list(");
      sl_btmesh_evt_fw_dist_client_receivers_list_t *data =
        &evt->data.evt_fw_dist_client_receivers_list;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" index="); log_append_uint16_t(data->index);
      app_log_append(" nodes_list_size="); log_append_uint16_t(data->nodes_list_size);
      app_log_append(" address="); log_append_uint16_t(data->address);
      app_log_append(" phase="); log_append_uint8_t(data->phase);
      app_log_append(" update_status="); log_append_uint8_t(data->update_status);
      app_log_append(" transfer_status="); log_append_uint8_t(data->transfer_status);
      app_log_append(" progress="); log_append_uint8_t(data->progress);
      app_log_append(" fw_index="); log_append_uint8_t(data->fw_index);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_dist_client_receivers_list_end_id: {
      app_log(PREFIX "fw_dist_client_receivers_list_end(");
      sl_btmesh_evt_fw_dist_client_receivers_list_end_t *data =
        &evt->data.evt_fw_dist_client_receivers_list_end;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" start_index="); log_append_uint16_t(data->start_index);
      app_log_append(" num_reported="); log_append_uint16_t(data->num_reported);
      app_log_append(" nodes_list_size="); log_append_uint16_t(data->nodes_list_size);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_dist_client_capabilities_status_id: {
      app_log(PREFIX "fw_dist_client_capabilities_status(");
      sl_btmesh_evt_fw_dist_client_capabilities_status_t *data =
        &evt->data.evt_fw_dist_client_capabilities_status;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" max_nodes_list_size="); log_append_uint16_t(data->max_nodes_list_size);
      app_log_append(" max_fw_list_size="); log_append_uint16_t(data->max_fw_list_size);
      app_log_append(" max_fw_size="); log_append_uint32_t(data->max_fw_size);
      app_log_append(" max_upload_space="); log_append_uint32_t(data->max_upload_space);
      app_log_append(" remaining_upload_space="); log_append_uint32_t(data->remaining_upload_space);
      app_log_append(" oob_supported="); log_append_uint8_t(data->oob_supported);
      app_log_append(" uri_scheme_names="); log_append_uint8array(data->uri_scheme_names);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_dist_client_distribution_status_id: {
      app_log(PREFIX "fw_dist_client_distribution_status(");
      sl_btmesh_evt_fw_dist_client_distribution_status_t *data =
        &evt->data.evt_fw_dist_client_distribution_status;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" status="); log_append_uint8_t(data->status);
      app_log_append(" phase="); log_append_uint8_t(data->phase);
      app_log_append(" group_address="); log_append_uint16_t(data->group_address);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" distributor_ttl="); log_append_uint8_t(data->distributor_ttl);
      app_log_append(" timeout_base="); log_append_uint16_t(data->timeout_base);
      app_log_append(" transfer_mode="); log_append_uint8_t(data->transfer_mode);
      app_log_append(" apply_immediately="); log_append_uint8_t(data->apply_immediately);
      app_log_append(" fw_list_index="); log_append_uint16_t(data->fw_list_index);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_dist_client_upload_status_id: {
      app_log(PREFIX "fw_dist_client_upload_status(");
      sl_btmesh_evt_fw_dist_client_upload_status_t *data =
        &evt->data.evt_fw_dist_client_upload_status;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" status="); log_append_uint8_t(data->status);
      app_log_append(" phase="); log_append_uint8_t(data->phase);
      app_log_append(" type="); log_append_uint8_t(data->type);
      app_log_append(" progress="); log_append_uint8_t(data->progress);
      app_log_append(" fwid="); log_append_uint8array(data->fwid);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_dist_client_fw_status_id: {
      app_log(PREFIX "fw_dist_client_fw_status(");
      sl_btmesh_evt_fw_dist_client_fw_status_t *data =
        &evt->data.evt_fw_dist_client_fw_status;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" status="); log_append_uint8_t(data->status);
      app_log_append(" num_entries="); log_append_uint16_t(data->num_entries);
      app_log_append(" index="); log_append_uint16_t(data->index);
      app_log_append(" fwid="); log_append_uint8array(data->fwid);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_dist_client_upload_complete_id: {
      app_log(PREFIX "fw_dist_client_upload_complete(");
      sl_btmesh_evt_fw_dist_client_upload_complete_t *data =
        &evt->data.evt_fw_dist_client_upload_complete;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" blob_id="); log_append_sl_bt_uuid_64_t(data->blob_id);
      app_log_append(" blob_size="); log_append_uint32_t(data->blob_size);
      app_log_append(" fwid="); log_append_uint8array(data->fwid);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_dist_client_upload_failed_id: {
      app_log(PREFIX "fw_dist_client_upload_failed(");
      sl_btmesh_evt_fw_dist_client_upload_failed_t *data =
        &evt->data.evt_fw_dist_client_upload_failed;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" server_address="); log_append_uint16_t(data->server_address);
      app_log_append(" status_code="); log_append_uint8_t(data->status_code);
      app_log_append(" dist_status_code="); log_append_uint8_t(data->dist_status_code);
      app_log_append(" progress="); log_append_uint8_t(data->progress);
      app_log_append(" blob_id="); log_append_sl_bt_uuid_64_t(data->blob_id);
      app_log_append(" blob_size="); log_append_uint32_t(data->blob_size);
      app_log_append(" fwid="); log_append_uint8array(data->fwid);
      app_log_append(" )" NL);
    } break;

    // remote_provisioning_client
    // Bluetooth Mesh Remote Provisioning Client Model
    case sl_btmesh_evt_remote_provisioning_client_scan_capabilities_id: {
      app_log(PREFIX "remote_provisioning_client_scan_capabilities(");
      sl_btmesh_evt_remote_provisioning_client_scan_capabilities_t *data =
        &evt->data.evt_remote_provisioning_client_scan_capabilities;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" server="); log_append_uint16_t(data->server);
      app_log_append(" max_items="); log_append_uint8_t(data->max_items);
      app_log_append(" active="); log_append_uint8_t(data->active);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_remote_provisioning_client_scan_status_id: {
      app_log(PREFIX "remote_provisioning_client_scan_status(");
      sl_btmesh_evt_remote_provisioning_client_scan_status_t *data =
        &evt->data.evt_remote_provisioning_client_scan_status;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" server="); log_append_uint16_t(data->server);
      app_log_append(" status="); log_append_uint8_t(data->status);
      app_log_append(" state="); log_append_uint8_t(data->state);
      app_log_append(" max_reports="); log_append_uint8_t(data->max_reports);
      app_log_append(" timeout_sec="); log_append_uint8_t(data->timeout_sec);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_remote_provisioning_client_scan_report_id: {
      app_log(PREFIX "remote_provisioning_client_scan_report(");
      sl_btmesh_evt_remote_provisioning_client_scan_report_t *data =
        &evt->data.evt_remote_provisioning_client_scan_report;
      app_log_append(" server="); log_append_uint16_t(data->server);
      app_log_append(" rssi="); log_append_int8_t(data->rssi);
      app_log_append(" uuid="); log_append_uuid_128(data->uuid);
      app_log_append(" oob="); log_append_uint16_t(data->oob);
      app_log_append(" uri="); log_append_uint32_t(data->uri);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_remote_provisioning_client_extended_scan_report_id: {
      app_log(PREFIX "remote_provisioning_client_extended_scan_report(");
      sl_btmesh_evt_remote_provisioning_client_extended_scan_report_t *data =
        &evt->data.evt_remote_provisioning_client_extended_scan_report;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" server="); log_append_uint16_t(data->server);
      app_log_append(" status="); log_append_uint8_t(data->status);
      app_log_append(" uuid="); log_append_uuid_128(data->uuid);
      app_log_append(" oob="); log_append_uint16_t(data->oob);
      app_log_append(" ad_structures="); log_append_uint8array(data->ad_structures);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_remote_provisioning_client_link_status_id: {
      app_log(PREFIX "remote_provisioning_client_link_status(");
      sl_btmesh_evt_remote_provisioning_client_link_status_t *data =
        &evt->data.evt_remote_provisioning_client_link_status;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" server="); log_append_uint16_t(data->server);
      app_log_append(" status="); log_append_uint8_t(data->status);
      app_log_append(" state="); log_append_uint8_t(data->state);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_remote_provisioning_client_link_report_id: {
      app_log(PREFIX "remote_provisioning_client_link_report(");
      sl_btmesh_evt_remote_provisioning_client_link_report_t *data =
        &evt->data.evt_remote_provisioning_client_link_report;
      app_log_append(" server="); log_append_uint16_t(data->server);
      app_log_append(" status="); log_append_uint8_t(data->status);
      app_log_append(" state="); log_append_uint8_t(data->state);
      app_log_append(" reason="); log_append_uint8_t(data->reason);
      app_log_append(" )" NL);
    } break;

    // remote_provisioning_server
    // Bluetooth Mesh Remote Provisioning Server Model
    case sl_btmesh_evt_remote_provisioning_server_link_open_request_id: {
      app_log(PREFIX "remote_provisioning_server_link_open_request(");
      sl_btmesh_evt_remote_provisioning_server_link_open_request_t *data =
        &evt->data.evt_remote_provisioning_server_link_open_request;
      app_log_append(" address="); log_append_bd_addr(data->address);
      app_log_append(" address_type="); log_append_uint8_t(data->address_type);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_remote_provisioning_server_link_close_request_id: {
      app_log(PREFIX "remote_provisioning_server_link_close_request(");
      sl_btmesh_evt_remote_provisioning_server_link_close_request_t *data =
        &evt->data.evt_remote_provisioning_server_link_close_request;
      app_log_append(" connection="); log_append_uint8_t(data->connection);
      app_log_append(" )" NL);
    } break;

    // fw_standalone_updater
    // Bluetooth Mesh Standalone Updater
    case sl_btmesh_evt_fw_standalone_updater_dist_state_changed_id: {
      app_log(PREFIX "fw_standalone_updater_dist_state_changed(");
      sl_btmesh_evt_fw_standalone_updater_dist_state_changed_t *data =
        &evt->data.evt_fw_standalone_updater_dist_state_changed;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" state="); log_append_uint8_t(data->state);
      app_log_append(" num_active_nodes="); log_append_uint16_t(data->num_active_nodes);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_fw_standalone_updater_node_failed_id: {
      app_log(PREFIX "fw_standalone_updater_node_failed(");
      sl_btmesh_evt_fw_standalone_updater_node_failed_t *data =
        &evt->data.evt_fw_standalone_updater_node_failed;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" address="); log_append_uint16_t(data->address);
      app_log_append(" update_phase="); log_append_uint8_t(data->update_phase);
      app_log_append(" update_status="); log_append_uint8_t(data->update_status);
      app_log_append(" mbt_status="); log_append_uint8_t(data->mbt_status);
      app_log_append(" progress="); log_append_uint8_t(data->progress);
      app_log_append(" fw_index="); log_append_uint8_t(data->fw_index);
      app_log_append(" )" NL);
    } break;

    // migration
    // Bluetooth Mesh Key migration

    // ncp_fw_list
    // NCP firmware list cache
    case sl_btmesh_evt_ncp_fw_list_fw_deleted_id: {
      app_log(PREFIX "ncp_fw_list_fw_deleted(");
      sl_btmesh_evt_ncp_fw_list_fw_deleted_t *data =
        &evt->data.evt_ncp_fw_list_fw_deleted;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" fwid="); log_append_uint8array(data->fwid);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_ncp_fw_list_fw_all_deleted_id: {
      app_log(PREFIX "ncp_fw_list_fw_all_deleted(");
      sl_btmesh_evt_ncp_fw_list_fw_all_deleted_t *data =
        &evt->data.evt_ncp_fw_list_fw_all_deleted;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" client_address="); log_append_uint16_t(data->client_address);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_ncp_fw_list_fw_added_id: {
      app_log(PREFIX "ncp_fw_list_fw_added(");
      sl_btmesh_evt_ncp_fw_list_fw_added_t *data =
        &evt->data.evt_ncp_fw_list_fw_added;
      app_log_append(" elem_index="); log_append_uint16_t(data->elem_index);
      app_log_append(" size="); log_append_uint32_t(data->size);
      app_log_append(" blob_id="); log_append_sl_bt_uuid_64_t(data->blob_id);
      app_log_append(" fwid="); log_append_uint8array(data->fwid);
      app_log_append(" )" NL);
    } break;

    // sar_config_client
    // Bluetooth Mesh SAR Configuration Client Model
    case sl_btmesh_evt_sar_config_client_sar_transmitter_status_id: {
      app_log(PREFIX "sar_config_client_sar_transmitter_status(");
      sl_btmesh_evt_sar_config_client_sar_transmitter_status_t *data =
        &evt->data.evt_sar_config_client_sar_transmitter_status;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" segment_interval_step="); log_append_uint8_t(data->segment_interval_step);
      app_log_append(" unicast_retrans_count="); log_append_uint8_t(data->unicast_retrans_count);
      app_log_append(" unicast_retrans_wo_progress_count="); log_append_uint8_t(data->unicast_retrans_wo_progress_count);
      app_log_append(" unicast_retrans_interval_step="); log_append_uint16_t(data->unicast_retrans_interval_step);
      app_log_append(" unicast_retrans_interval_increment="); log_append_uint16_t(data->unicast_retrans_interval_increment);
      app_log_append(" multicast_retrans_count="); log_append_uint8_t(data->multicast_retrans_count);
      app_log_append(" multicast_retrans_interval_step="); log_append_uint16_t(data->multicast_retrans_interval_step);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_sar_config_client_sar_receiver_status_id: {
      app_log(PREFIX "sar_config_client_sar_receiver_status(");
      sl_btmesh_evt_sar_config_client_sar_receiver_status_t *data =
        &evt->data.evt_sar_config_client_sar_receiver_status;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" segments_threshold="); log_append_uint8_t(data->segments_threshold);
      app_log_append(" ack_delay_increment="); log_append_uint8_t(data->ack_delay_increment);
      app_log_append(" discard_timeout="); log_append_uint32_t(data->discard_timeout);
      app_log_append(" segment_interval_step="); log_append_uint8_t(data->segment_interval_step);
      app_log_append(" ack_retrans_count="); log_append_uint8_t(data->ack_retrans_count);
      app_log_append(" )" NL);
    } break;

    // sar_config_server
    // Bluetooth Mesh SAR Configuration Server Model
    case sl_btmesh_evt_sar_config_server_sar_transmitter_set_id: {
      app_log(PREFIX "sar_config_server_sar_transmitter_set(");
      sl_btmesh_evt_sar_config_server_sar_transmitter_set_t *data =
        &evt->data.evt_sar_config_server_sar_transmitter_set;
      app_log_append(" segment_interval_step="); log_append_uint8_t(data->segment_interval_step);
      app_log_append(" unicast_retrans_count="); log_append_uint8_t(data->unicast_retrans_count);
      app_log_append(" unicast_retrans_wo_progress_count="); log_append_uint8_t(data->unicast_retrans_wo_progress_count);
      app_log_append(" unicast_retrans_interval_step="); log_append_uint16_t(data->unicast_retrans_interval_step);
      app_log_append(" unicast_retrans_interval_increment="); log_append_uint16_t(data->unicast_retrans_interval_increment);
      app_log_append(" multicast_retrans_count="); log_append_uint8_t(data->multicast_retrans_count);
      app_log_append(" multicast_retrans_interval_step="); log_append_uint16_t(data->multicast_retrans_interval_step);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_sar_config_server_sar_receiver_set_id: {
      app_log(PREFIX "sar_config_server_sar_receiver_set(");
      sl_btmesh_evt_sar_config_server_sar_receiver_set_t *data =
        &evt->data.evt_sar_config_server_sar_receiver_set;
      app_log_append(" segments_threshold="); log_append_uint8_t(data->segments_threshold);
      app_log_append(" ack_delay_increment="); log_append_uint8_t(data->ack_delay_increment);
      app_log_append(" discard_timeout="); log_append_uint32_t(data->discard_timeout);
      app_log_append(" segment_interval_step="); log_append_uint8_t(data->segment_interval_step);
      app_log_append(" ack_retrans_count="); log_append_uint8_t(data->ack_retrans_count);
      app_log_append(" )" NL);
    } break;

    // private_beacon_client
    // Bluetooth Mesh Private Beacon Client Model
    case sl_btmesh_evt_private_beacon_client_beacon_status_id: {
      app_log(PREFIX "private_beacon_client_beacon_status(");
      sl_btmesh_evt_private_beacon_client_beacon_status_t *data =
        &evt->data.evt_private_beacon_client_beacon_status;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" state="); log_append_uint8_t(data->state);
      app_log_append(" random_update_steps="); log_append_uint8_t(data->random_update_steps);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_private_beacon_client_gatt_proxy_status_id: {
      app_log(PREFIX "private_beacon_client_gatt_proxy_status(");
      sl_btmesh_evt_private_beacon_client_gatt_proxy_status_t *data =
        &evt->data.evt_private_beacon_client_gatt_proxy_status;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" state="); log_append_uint8_t(data->state);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_private_beacon_client_identity_status_id: {
      app_log(PREFIX "private_beacon_client_identity_status(");
      sl_btmesh_evt_private_beacon_client_identity_status_t *data =
        &evt->data.evt_private_beacon_client_identity_status;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" status="); log_append_uint8_t(data->status);
      app_log_append(" netkey_index="); log_append_uint16_t(data->netkey_index);
      app_log_append(" state="); log_append_uint8_t(data->state);
      app_log_append(" )" NL);
    } break;

    // private_beacon_server
    // Bluetooth Mesh Private Beacon Server Model

    // lcd_client
    // Bluetooth Mesh Large Composition Data Client Model
    case sl_btmesh_evt_lcd_client_data_header_id: {
      app_log(PREFIX "lcd_client_data_header(");
      sl_btmesh_evt_lcd_client_data_header_t *data =
        &evt->data.evt_lcd_client_data_header;
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" page_number="); log_append_uint8_t(data->page_number);
      app_log_append(" offset="); log_append_uint16_t(data->offset);
      app_log_append(" total_size="); log_append_uint16_t(data->total_size);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_lcd_client_data_id: {
      app_log(PREFIX "lcd_client_data(");
      sl_btmesh_evt_lcd_client_data_t *data =
        &evt->data.evt_lcd_client_data;
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" data="); log_append_uint8array(data->data);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_lcd_client_data_end_id: {
      app_log(PREFIX "lcd_client_data_end(");
      sl_btmesh_evt_lcd_client_data_end_t *data =
        &evt->data.evt_lcd_client_data_end;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" )" NL);
    } break;

    // lcd_server
    // Bluetooth Mesh Large Composition Data Server Model

    // on_demand_private_proxy_client
    // Bluetooth Mesh On-demand Private Proxy Client Model
    case sl_btmesh_evt_on_demand_private_proxy_client_private_gatt_proxy_status_id: {
      app_log(PREFIX "on_demand_private_proxy_client_private_gatt_proxy_status(");
      sl_btmesh_evt_on_demand_private_proxy_client_private_gatt_proxy_status_t *data =
        &evt->data.evt_on_demand_private_proxy_client_private_gatt_proxy_status;
      app_log_append(" result="); log_append_uint16_t(data->result);
      app_log_append(" handle="); log_append_uint32_t(data->handle);
      app_log_append(" value="); log_append_uint8_t(data->value);
      app_log_append(" )" NL);
    } break;

    // solicitation_config_client
    // Bluetooth Mesh Solicitation PDU RPL Config Client Model
    case sl_btmesh_evt_solicitation_config_client_items_status_id: {
      app_log(PREFIX "solicitation_config_client_items_status(");
      sl_btmesh_evt_solicitation_config_client_items_status_t *data =
        &evt->data.evt_solicitation_config_client_items_status;
      app_log_append(" src="); log_append_uint16_t(data->src);
      app_log_append(" dst="); log_append_uint16_t(data->dst);
      app_log_append(" appkey_index="); log_append_uint16_t(data->appkey_index);
      app_log_append(" range_start="); log_append_uint16_t(data->range_start);
      app_log_append(" length_present="); log_append_uint8_t(data->length_present);
      app_log_append(" range_length="); log_append_uint8_t(data->range_length);
      app_log_append(" )" NL);
    } break;

    // on_demand_private_proxy_server
    // Bluetooth Mesh On-demand Private Proxy Server Model

    // silabs_config_server
    // Bluetooth Mesh Silabs Configuration Server Vendor Model
    case sl_btmesh_evt_silabs_config_server_tx_changed_id: {
      app_log(PREFIX "silabs_config_server_tx_changed(");
      sl_btmesh_evt_silabs_config_server_tx_changed_t *data =
        &evt->data.evt_silabs_config_server_tx_changed;
      app_log_append(" phy="); log_append_uint8_t(data->phy);
      app_log_append(" options="); log_append_uint32_t(data->options);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_silabs_config_server_model_option_changed_id: {
      app_log(PREFIX "silabs_config_server_model_option_changed(");
      sl_btmesh_evt_silabs_config_server_model_option_changed_t *data =
        &evt->data.evt_silabs_config_server_model_option_changed;
      app_log_append(" elem_index="); log_append_uint8_t(data->elem_index);
      app_log_append(" vendor_id="); log_append_uint16_t(data->vendor_id);
      app_log_append(" model_id="); log_append_uint16_t(data->model_id);
      app_log_append(" value="); log_append_uint16_t(data->value);
      app_log_append(" )" NL);
    } break;
    case sl_btmesh_evt_silabs_config_server_network_pdu_changed_id: {
      app_log(PREFIX "silabs_config_server_network_pdu_changed(");
      sl_btmesh_evt_silabs_config_server_network_pdu_changed_t *data =
        &evt->data.evt_silabs_config_server_network_pdu_changed;
      app_log_append(" max_size="); log_append_uint16_t(data->max_size);
      app_log_append(" )" NL);
    } break;

    default:
      #if SL_BTMESH_EVENT_LOG_ENABLE_UNKNOWN_CFG_VAL
      app_log(PREFIX);
      app_log_append("unknown evt: %8.8x class %2.2x method %2.2x" NL,
                     evt_id,
                     (evt_id >> 16) & 0xFF,
                     (evt_id >> 24) & 0xFF);
      #endif // SL_BTMESH_EVENT_LOG_ENABLE_UNKNOWN_CFG_VAL
      break;
  }
}

/*******************************************************************************
 * Component node reset handler.
 ******************************************************************************/
void sl_btmesh_log_on_node_reset(void)
{
  app_log(PREFIX "node_reset(");
  app_log_append(" )" NL);
}

/*******************************************************************************
 * Log Bluetooth LE connection events
 * @param[in] evt     Pointer to incoming event
 ******************************************************************************/
void sl_btmesh_log_bt_connection_events(sl_bt_msg_t *evt)
{
  if (NULL == evt) {
    return;
  }

  uint32_t evt_id = SL_BT_MSG_ID(evt->header);

  // Handle events
  switch (evt_id) {
    case sl_bt_evt_connection_opened_id: {
      app_log(PREFIX "connection_opened()" NL);
    } break;
    case sl_bt_evt_connection_parameters_id: {
      app_log("connection_parameters(");
      sl_bt_evt_connection_parameters_t data = evt->data.evt_connection_parameters;
      app_log_append(" interval="); log_append_uint16_t(data.interval);
      app_log_append(" latency="); log_append_uint16_t(data.latency);
      app_log_append(" timeout="); log_append_uint16_t(data.timeout);
      // note: there are more params
      app_log_append(" )" NL);
    } break;
    case sl_bt_evt_connection_closed_id: {
      app_log("connection_closed(");
      sl_bt_evt_connection_closed_t data = evt->data.evt_connection_closed;
      app_log_append(" reason="); log_append_uint16_t(data.reason);
      app_log_append(" )" NL);
    } break;
    default:
      break;
  }
}

/** @} (end addtogroup BtMeshEventLog) */
