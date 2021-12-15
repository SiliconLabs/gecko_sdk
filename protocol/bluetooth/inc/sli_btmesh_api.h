/***************************************************************************//**
 * @brief SL_BT_API library at application layer provided as source code
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SLI_BT_API_H
#define SLI_BT_API_H
#define VERSION no_link_tables

#ifdef __cplusplus
extern "C" {
#endif

PACKSTRUCT( struct sl_btmesh_cmd_node_start_unprov_beaconing_s
{
    uint8_t             bearer;
});

typedef struct sl_btmesh_cmd_node_start_unprov_beaconing_s sl_btmesh_cmd_node_start_unprov_beaconing_t;


PACKSTRUCT( struct sl_btmesh_cmd_node_send_input_oob_request_response_s
{
    uint8array          data;
});

typedef struct sl_btmesh_cmd_node_send_input_oob_request_response_s sl_btmesh_cmd_node_send_input_oob_request_response_t;


PACKSTRUCT( struct sl_btmesh_cmd_node_set_provisioning_data_s
{
    aes_key_128         device_key;
    aes_key_128         network_key;
    uint16_t            netkey_index;
    uint32_t            iv_index;
    uint16_t            address;
    uint8_t             kr_in_progress;
});

typedef struct sl_btmesh_cmd_node_set_provisioning_data_s sl_btmesh_cmd_node_set_provisioning_data_t;


PACKSTRUCT( struct sl_btmesh_cmd_node_init_oob_s
{
    uint8_t             public_key;
    uint8_t             auth_methods;
    uint16_t            output_actions;
    uint8_t             output_size;
    uint16_t            input_actions;
    uint8_t             input_size;
    uint16_t            oob_location;
});

typedef struct sl_btmesh_cmd_node_init_oob_s sl_btmesh_cmd_node_init_oob_t;


PACKSTRUCT( struct sl_btmesh_cmd_node_set_ivrecovery_mode_s
{
    uint8_t             mode;
});

typedef struct sl_btmesh_cmd_node_set_ivrecovery_mode_s sl_btmesh_cmd_node_set_ivrecovery_mode_t;


PACKSTRUCT( struct sl_btmesh_cmd_node_set_net_relay_delay_s
{
    uint8_t             min_ms;
    uint8_t             max_ms;
});

typedef struct sl_btmesh_cmd_node_set_net_relay_delay_s sl_btmesh_cmd_node_set_net_relay_delay_t;


PACKSTRUCT( struct sl_btmesh_cmd_node_get_seq_remaining_s
{
    uint16_t            elem_index;
});

typedef struct sl_btmesh_cmd_node_get_seq_remaining_s sl_btmesh_cmd_node_get_seq_remaining_t;


PACKSTRUCT( struct sl_btmesh_cmd_node_set_uuid_s
{
    uuid_128            uuid;
});

typedef struct sl_btmesh_cmd_node_set_uuid_s sl_btmesh_cmd_node_set_uuid_t;


PACKSTRUCT( struct sl_btmesh_cmd_node_get_element_address_s
{
    uint16_t            elem_index;
});

typedef struct sl_btmesh_cmd_node_get_element_address_s sl_btmesh_cmd_node_get_element_address_t;


PACKSTRUCT( struct sl_btmesh_cmd_node_send_static_oob_request_response_s
{
    uint8array          data;
});

typedef struct sl_btmesh_cmd_node_send_static_oob_request_response_s sl_btmesh_cmd_node_send_static_oob_request_response_t;


PACKSTRUCT( struct sl_btmesh_cmd_node_set_beacon_reporting_s
{
    uint8_t             report;
});

typedef struct sl_btmesh_cmd_node_set_beacon_reporting_s sl_btmesh_cmd_node_set_beacon_reporting_t;


PACKSTRUCT( struct sl_btmesh_cmd_node_set_iv_update_age_s
{
    uint32_t            age_sec;
});

typedef struct sl_btmesh_cmd_node_set_iv_update_age_s sl_btmesh_cmd_node_set_iv_update_age_t;


PACKSTRUCT( struct sl_btmesh_cmd_node_get_key_count_s
{
    uint8_t             type;
});

typedef struct sl_btmesh_cmd_node_get_key_count_s sl_btmesh_cmd_node_get_key_count_t;


PACKSTRUCT( struct sl_btmesh_cmd_node_get_key_s
{
    uint8_t             type;
    uint32_t            index;
    uint8_t             current;
});

typedef struct sl_btmesh_cmd_node_get_key_s sl_btmesh_cmd_node_get_key_t;


PACKSTRUCT( struct sl_btmesh_cmd_node_get_element_seqnum_s
{
    uint16_t            elem_index;
});

typedef struct sl_btmesh_cmd_node_get_element_seqnum_s sl_btmesh_cmd_node_get_element_seqnum_t;


PACKSTRUCT( struct sl_btmesh_cmd_node_set_model_option_s
{
    uint16_t            elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
    uint8_t             option;
    uint32_t            value;
});

typedef struct sl_btmesh_cmd_node_set_model_option_s sl_btmesh_cmd_node_set_model_option_t;


PACKSTRUCT( struct sl_btmesh_cmd_node_get_local_dcd_s
{
    uint8_t             page;
});

typedef struct sl_btmesh_cmd_node_get_local_dcd_s sl_btmesh_cmd_node_get_local_dcd_t;


PACKSTRUCT( struct sl_btmesh_cmd_node_set_adv_phy_s
{
    uint8_t             phy;
});

typedef struct sl_btmesh_cmd_node_set_adv_phy_s sl_btmesh_cmd_node_set_adv_phy_t;



PACKSTRUCT( struct sl_btmesh_cmd_prov_create_provisioning_session_s
{
    uint16_t            netkey_index;
    uuid_128            uuid;
    uint8_t             attention_timer_sec;
});

typedef struct sl_btmesh_cmd_prov_create_provisioning_session_s sl_btmesh_cmd_prov_create_provisioning_session_t;


PACKSTRUCT( struct sl_btmesh_cmd_prov_set_provisioning_suspend_event_s
{
    uint8_t             status;
});

typedef struct sl_btmesh_cmd_prov_set_provisioning_suspend_event_s sl_btmesh_cmd_prov_set_provisioning_suspend_event_t;


PACKSTRUCT( struct sl_btmesh_cmd_prov_provision_adv_device_s
{
    uuid_128            uuid;
});

typedef struct sl_btmesh_cmd_prov_provision_adv_device_s sl_btmesh_cmd_prov_provision_adv_device_t;


PACKSTRUCT( struct sl_btmesh_cmd_prov_provision_gatt_device_s
{
    uuid_128            uuid;
    uint8_t             connection;
});

typedef struct sl_btmesh_cmd_prov_provision_gatt_device_s sl_btmesh_cmd_prov_provision_gatt_device_t;


PACKSTRUCT( struct sl_btmesh_cmd_prov_continue_provisioning_s
{
    uuid_128            uuid;
});

typedef struct sl_btmesh_cmd_prov_continue_provisioning_s sl_btmesh_cmd_prov_continue_provisioning_t;


PACKSTRUCT( struct sl_btmesh_cmd_prov_abort_provisioning_s
{
    uuid_128            uuid;
    uint8_t             reason;
});

typedef struct sl_btmesh_cmd_prov_abort_provisioning_s sl_btmesh_cmd_prov_abort_provisioning_t;


PACKSTRUCT( struct sl_btmesh_cmd_prov_set_device_address_s
{
    uuid_128            uuid;
    uint16_t            address;
});

typedef struct sl_btmesh_cmd_prov_set_device_address_s sl_btmesh_cmd_prov_set_device_address_t;


PACKSTRUCT( struct sl_btmesh_cmd_prov_create_network_s
{
    uint16_t            netkey_index;
    uint8array          key;
});

typedef struct sl_btmesh_cmd_prov_create_network_s sl_btmesh_cmd_prov_create_network_t;


PACKSTRUCT( struct sl_btmesh_cmd_prov_create_appkey_s
{
    uint16_t            netkey_index;
    uint16_t            appkey_index;
    uint8array          key;
});

typedef struct sl_btmesh_cmd_prov_create_appkey_s sl_btmesh_cmd_prov_create_appkey_t;


PACKSTRUCT( struct sl_btmesh_cmd_prov_send_oob_pkey_response_s
{
    uuid_128            uuid;
    uint8array          pkey;
});

typedef struct sl_btmesh_cmd_prov_send_oob_pkey_response_s sl_btmesh_cmd_prov_send_oob_pkey_response_t;


PACKSTRUCT( struct sl_btmesh_cmd_prov_send_oob_auth_response_s
{
    uuid_128            uuid;
    uint8array          data;
});

typedef struct sl_btmesh_cmd_prov_send_oob_auth_response_s sl_btmesh_cmd_prov_send_oob_auth_response_t;


PACKSTRUCT( struct sl_btmesh_cmd_prov_set_oob_requirements_s
{
    uuid_128            uuid;
    uint8_t             public_key;
    uint8_t             auth_methods;
    uint16_t            output_actions;
    uint16_t            input_actions;
    uint8_t             min_size;
    uint8_t             max_size;
});

typedef struct sl_btmesh_cmd_prov_set_oob_requirements_s sl_btmesh_cmd_prov_set_oob_requirements_t;


PACKSTRUCT( struct sl_btmesh_cmd_prov_start_key_refresh_s
{
    uint16_t            netkey_index;
    uint8_t             num_appkeys;
    uint8array          appkey_indices;
});

typedef struct sl_btmesh_cmd_prov_start_key_refresh_s sl_btmesh_cmd_prov_start_key_refresh_t;


PACKSTRUCT( struct sl_btmesh_cmd_prov_get_key_refresh_exclusion_s
{
    uint16_t            key;
    uuid_128            uuid;
});

typedef struct sl_btmesh_cmd_prov_get_key_refresh_exclusion_s sl_btmesh_cmd_prov_get_key_refresh_exclusion_t;


PACKSTRUCT( struct sl_btmesh_cmd_prov_set_key_refresh_exclusion_s
{
    uint16_t            key;
    uint8_t             status;
    uuid_128            uuid;
});

typedef struct sl_btmesh_cmd_prov_set_key_refresh_exclusion_s sl_btmesh_cmd_prov_set_key_refresh_exclusion_t;


PACKSTRUCT( struct sl_btmesh_cmd_prov_get_ddb_entry_s
{
    uuid_128            uuid;
});

typedef struct sl_btmesh_cmd_prov_get_ddb_entry_s sl_btmesh_cmd_prov_get_ddb_entry_t;


PACKSTRUCT( struct sl_btmesh_cmd_prov_delete_ddb_entry_s
{
    uuid_128            uuid;
});

typedef struct sl_btmesh_cmd_prov_delete_ddb_entry_s sl_btmesh_cmd_prov_delete_ddb_entry_t;


PACKSTRUCT( struct sl_btmesh_cmd_prov_add_ddb_entry_s
{
    uuid_128            uuid;
    aes_key_128         device_key;
    uint16_t            netkey_index;
    uint16_t            address;
    uint8_t             elements;
});

typedef struct sl_btmesh_cmd_prov_add_ddb_entry_s sl_btmesh_cmd_prov_add_ddb_entry_t;


PACKSTRUCT( struct sl_btmesh_cmd_prov_initialize_network_s
{
    uint16_t            address;
    uint32_t            ivi;
});

typedef struct sl_btmesh_cmd_prov_initialize_network_s sl_btmesh_cmd_prov_initialize_network_t;


PACKSTRUCT( struct sl_btmesh_cmd_prov_get_key_refresh_appkey_exclusion_s
{
    uint16_t            netkey_index;
    uint16_t            appkey_index;
    uuid_128            uuid;
});

typedef struct sl_btmesh_cmd_prov_get_key_refresh_appkey_exclusion_s sl_btmesh_cmd_prov_get_key_refresh_appkey_exclusion_t;


PACKSTRUCT( struct sl_btmesh_cmd_prov_set_key_refresh_appkey_exclusion_s
{
    uint16_t            netkey_index;
    uint16_t            appkey_index;
    uint8_t             status;
    uuid_128            uuid;
});

typedef struct sl_btmesh_cmd_prov_set_key_refresh_appkey_exclusion_s sl_btmesh_cmd_prov_set_key_refresh_appkey_exclusion_t;


PACKSTRUCT( struct sl_btmesh_cmd_prov_update_device_netkey_index_s
{
    uuid_128            uuid;
    uint16_t            netkey_index;
});

typedef struct sl_btmesh_cmd_prov_update_device_netkey_index_s sl_btmesh_cmd_prov_update_device_netkey_index_t;


PACKSTRUCT( struct sl_btmesh_cmd_prov_suspend_key_refresh_s
{
    uint16_t            netkey_index;
});

typedef struct sl_btmesh_cmd_prov_suspend_key_refresh_s sl_btmesh_cmd_prov_suspend_key_refresh_t;


PACKSTRUCT( struct sl_btmesh_cmd_prov_resume_key_refresh_s
{
    uint16_t            netkey_index;
});

typedef struct sl_btmesh_cmd_prov_resume_key_refresh_s sl_btmesh_cmd_prov_resume_key_refresh_t;


PACKSTRUCT( struct sl_btmesh_cmd_prov_get_key_refresh_phase_s
{
    uint16_t            netkey_index;
});

typedef struct sl_btmesh_cmd_prov_get_key_refresh_phase_s sl_btmesh_cmd_prov_get_key_refresh_phase_t;


PACKSTRUCT( struct sl_btmesh_cmd_prov_start_key_refresh_from_phase_s
{
    uint8_t             phase;
    uint16_t            netkey_index;
    uint8_t             num_appkeys;
    uint8array          appkey_indices;
});

typedef struct sl_btmesh_cmd_prov_start_key_refresh_from_phase_s sl_btmesh_cmd_prov_start_key_refresh_from_phase_t;


PACKSTRUCT( struct sl_btmesh_cmd_prov_flush_key_refresh_state_s
{
    uint16_t            netkey_index;
});

typedef struct sl_btmesh_cmd_prov_flush_key_refresh_state_s sl_btmesh_cmd_prov_flush_key_refresh_state_t;


PACKSTRUCT( struct sl_btmesh_cmd_prov_test_identity_s
{
    uint16_t            address;
    uint16_t            netkey_index;
    uint8array          data;
});

typedef struct sl_btmesh_cmd_prov_test_identity_s sl_btmesh_cmd_prov_test_identity_t;



PACKSTRUCT( struct sl_btmesh_cmd_proxy_connect_s
{
    uint8_t             connection;
});

typedef struct sl_btmesh_cmd_proxy_connect_s sl_btmesh_cmd_proxy_connect_t;


PACKSTRUCT( struct sl_btmesh_cmd_proxy_disconnect_s
{
    uint32_t            handle;
});

typedef struct sl_btmesh_cmd_proxy_disconnect_s sl_btmesh_cmd_proxy_disconnect_t;


PACKSTRUCT( struct sl_btmesh_cmd_proxy_set_filter_type_s
{
    uint32_t            handle;
    uint16_t            netkey_index;
    uint8_t             type;
});

typedef struct sl_btmesh_cmd_proxy_set_filter_type_s sl_btmesh_cmd_proxy_set_filter_type_t;


PACKSTRUCT( struct sl_btmesh_cmd_proxy_allow_s
{
    uint32_t            handle;
    uint16_t            netkey_index;
    uint16_t            address;
});

typedef struct sl_btmesh_cmd_proxy_allow_s sl_btmesh_cmd_proxy_allow_t;


PACKSTRUCT( struct sl_btmesh_cmd_proxy_deny_s
{
    uint32_t            handle;
    uint16_t            netkey_index;
    uint16_t            address;
});

typedef struct sl_btmesh_cmd_proxy_deny_s sl_btmesh_cmd_proxy_deny_t;


PACKSTRUCT( struct sl_btmesh_cmd_proxy_optimisation_toggle_s
{
    uint8_t             enable;
});

typedef struct sl_btmesh_cmd_proxy_optimisation_toggle_s sl_btmesh_cmd_proxy_optimisation_toggle_t;



PACKSTRUCT( struct sl_btmesh_cmd_vendor_model_send_s
{
    uint16_t            destination_address;
    int8_t              va_index;
    uint16_t            appkey_index;
    uint16_t            elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
    uint8_t             nonrelayed;
    uint8_t             opcode;
    uint8_t             final;
    uint8array          payload;
});

typedef struct sl_btmesh_cmd_vendor_model_send_s sl_btmesh_cmd_vendor_model_send_t;


PACKSTRUCT( struct sl_btmesh_cmd_vendor_model_set_publication_s
{
    uint16_t            elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
    uint8_t             opcode;
    uint8_t             final;
    uint8array          payload;
});

typedef struct sl_btmesh_cmd_vendor_model_set_publication_s sl_btmesh_cmd_vendor_model_set_publication_t;


PACKSTRUCT( struct sl_btmesh_cmd_vendor_model_clear_publication_s
{
    uint16_t            elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
});

typedef struct sl_btmesh_cmd_vendor_model_clear_publication_s sl_btmesh_cmd_vendor_model_clear_publication_t;


PACKSTRUCT( struct sl_btmesh_cmd_vendor_model_publish_s
{
    uint16_t            elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
});

typedef struct sl_btmesh_cmd_vendor_model_publish_s sl_btmesh_cmd_vendor_model_publish_t;


PACKSTRUCT( struct sl_btmesh_cmd_vendor_model_init_s
{
    uint16_t            elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
    uint8_t             publish;
    uint8array          opcodes;
});

typedef struct sl_btmesh_cmd_vendor_model_init_s sl_btmesh_cmd_vendor_model_init_t;


PACKSTRUCT( struct sl_btmesh_cmd_vendor_model_deinit_s
{
    uint16_t            elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
});

typedef struct sl_btmesh_cmd_vendor_model_deinit_s sl_btmesh_cmd_vendor_model_deinit_t;


PACKSTRUCT( struct sl_btmesh_cmd_vendor_model_send_tracked_s
{
    uint16_t            destination_address;
    int8_t              va_index;
    uint16_t            appkey_index;
    uint16_t            elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
    uint8_t             nonrelayed;
    uint8_t             segment;
    uint8_t             opcode;
    uint8_t             final;
    uint8array          payload;
});

typedef struct sl_btmesh_cmd_vendor_model_send_tracked_s sl_btmesh_cmd_vendor_model_send_tracked_t;


PACKSTRUCT( struct sl_btmesh_cmd_vendor_model_set_publication_tracked_s
{
    uint16_t            elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
    uint8_t             segment;
    uint8_t             opcode;
    uint8_t             final;
    uint8array          payload;
});

typedef struct sl_btmesh_cmd_vendor_model_set_publication_tracked_s sl_btmesh_cmd_vendor_model_set_publication_tracked_t;



PACKSTRUCT( struct sl_btmesh_cmd_health_client_get_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint16_t            vendor_id;
});

typedef struct sl_btmesh_cmd_health_client_get_s sl_btmesh_cmd_health_client_get_t;


PACKSTRUCT( struct sl_btmesh_cmd_health_client_clear_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint16_t            vendor_id;
    uint8_t             reliable;
});

typedef struct sl_btmesh_cmd_health_client_clear_s sl_btmesh_cmd_health_client_clear_t;


PACKSTRUCT( struct sl_btmesh_cmd_health_client_test_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint8_t             test_id;
    uint16_t            vendor_id;
    uint8_t             reliable;
});

typedef struct sl_btmesh_cmd_health_client_test_s sl_btmesh_cmd_health_client_test_t;


PACKSTRUCT( struct sl_btmesh_cmd_health_client_get_period_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
});

typedef struct sl_btmesh_cmd_health_client_get_period_s sl_btmesh_cmd_health_client_get_period_t;


PACKSTRUCT( struct sl_btmesh_cmd_health_client_set_period_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint8_t             period;
    uint8_t             reliable;
});

typedef struct sl_btmesh_cmd_health_client_set_period_s sl_btmesh_cmd_health_client_set_period_t;


PACKSTRUCT( struct sl_btmesh_cmd_health_client_get_attention_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
});

typedef struct sl_btmesh_cmd_health_client_get_attention_s sl_btmesh_cmd_health_client_get_attention_t;


PACKSTRUCT( struct sl_btmesh_cmd_health_client_set_attention_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint8_t             attention_sec;
    uint8_t             reliable;
});

typedef struct sl_btmesh_cmd_health_client_set_attention_s sl_btmesh_cmd_health_client_set_attention_t;



PACKSTRUCT( struct sl_btmesh_cmd_health_server_set_fault_s
{
    uint16_t            elem_index;
    uint8_t             id;
});

typedef struct sl_btmesh_cmd_health_server_set_fault_s sl_btmesh_cmd_health_server_set_fault_t;


PACKSTRUCT( struct sl_btmesh_cmd_health_server_clear_fault_s
{
    uint16_t            elem_index;
    uint8_t             id;
});

typedef struct sl_btmesh_cmd_health_server_clear_fault_s sl_btmesh_cmd_health_server_clear_fault_t;


PACKSTRUCT( struct sl_btmesh_cmd_health_server_send_test_response_s
{
    uint16_t            client_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint16_t            vendor_id;
});

typedef struct sl_btmesh_cmd_health_server_send_test_response_s sl_btmesh_cmd_health_server_send_test_response_t;



PACKSTRUCT( struct sl_btmesh_cmd_generic_client_get_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            model_id;
    uint16_t            appkey_index;
    uint8_t             type;
});

typedef struct sl_btmesh_cmd_generic_client_get_s sl_btmesh_cmd_generic_client_get_t;


PACKSTRUCT( struct sl_btmesh_cmd_generic_client_set_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            model_id;
    uint16_t            appkey_index;
    uint8_t             tid;
    uint32_t            transition_ms;
    uint16_t            delay_ms;
    uint16_t            flags;
    uint8_t             type;
    uint8array          parameters;
});

typedef struct sl_btmesh_cmd_generic_client_set_s sl_btmesh_cmd_generic_client_set_t;


PACKSTRUCT( struct sl_btmesh_cmd_generic_client_publish_s
{
    uint16_t            elem_index;
    uint16_t            model_id;
    uint8_t             tid;
    uint32_t            transition_ms;
    uint16_t            delay_ms;
    uint16_t            flags;
    uint8_t             type;
    uint8array          parameters;
});

typedef struct sl_btmesh_cmd_generic_client_publish_s sl_btmesh_cmd_generic_client_publish_t;


PACKSTRUCT( struct sl_btmesh_cmd_generic_client_get_params_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            model_id;
    uint16_t            appkey_index;
    uint8_t             type;
    uint8array          parameters;
});

typedef struct sl_btmesh_cmd_generic_client_get_params_s sl_btmesh_cmd_generic_client_get_params_t;



PACKSTRUCT( struct sl_btmesh_cmd_generic_server_respond_s
{
    uint16_t            client_address;
    uint16_t            elem_index;
    uint16_t            model_id;
    uint16_t            appkey_index;
    uint32_t            remaining_ms;
    uint16_t            flags;
    uint8_t             type;
    uint8array          parameters;
});

typedef struct sl_btmesh_cmd_generic_server_respond_s sl_btmesh_cmd_generic_server_respond_t;


PACKSTRUCT( struct sl_btmesh_cmd_generic_server_update_s
{
    uint16_t            elem_index;
    uint16_t            model_id;
    uint32_t            remaining_ms;
    uint8_t             type;
    uint8array          parameters;
});

typedef struct sl_btmesh_cmd_generic_server_update_s sl_btmesh_cmd_generic_server_update_t;


PACKSTRUCT( struct sl_btmesh_cmd_generic_server_publish_s
{
    uint16_t            elem_index;
    uint16_t            model_id;
    uint8_t             type;
});

typedef struct sl_btmesh_cmd_generic_server_publish_s sl_btmesh_cmd_generic_server_publish_t;


PACKSTRUCT( struct sl_btmesh_cmd_generic_server_get_cached_state_s
{
    uint16_t            elem_index;
    uint16_t            model_id;
    uint8_t             type;
});

typedef struct sl_btmesh_cmd_generic_server_get_cached_state_s sl_btmesh_cmd_generic_server_get_cached_state_t;



PACKSTRUCT( struct sl_btmesh_cmd_test_set_nettx_s
{
    uint8_t             count;
    uint8_t             interval;
});

typedef struct sl_btmesh_cmd_test_set_nettx_s sl_btmesh_cmd_test_set_nettx_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_set_relay_s
{
    uint8_t             enabled;
    uint8_t             count;
    uint8_t             interval;
});

typedef struct sl_btmesh_cmd_test_set_relay_s sl_btmesh_cmd_test_set_relay_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_set_adv_scan_params_s
{
    uint16_t            adv_interval_min;
    uint16_t            adv_interval_max;
    uint8_t             adv_repeat_packets;
    uint8_t             adv_use_random_address;
    uint8_t             adv_channel_map;
    uint16_t            scan_interval;
    uint16_t            scan_window;
});

typedef struct sl_btmesh_cmd_test_set_adv_scan_params_s sl_btmesh_cmd_test_set_adv_scan_params_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_set_ivupdate_test_mode_s
{
    uint8_t             mode;
});

typedef struct sl_btmesh_cmd_test_set_ivupdate_test_mode_s sl_btmesh_cmd_test_set_ivupdate_test_mode_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_set_segment_send_delay_s
{
    uint8_t             delay;
});

typedef struct sl_btmesh_cmd_test_set_segment_send_delay_s sl_btmesh_cmd_test_set_segment_send_delay_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_set_ivupdate_state_s
{
    uint8_t             state;
});

typedef struct sl_btmesh_cmd_test_set_ivupdate_state_s sl_btmesh_cmd_test_set_ivupdate_state_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_bind_local_model_app_s
{
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
});

typedef struct sl_btmesh_cmd_test_bind_local_model_app_s sl_btmesh_cmd_test_bind_local_model_app_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_unbind_local_model_app_s
{
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
});

typedef struct sl_btmesh_cmd_test_unbind_local_model_app_s sl_btmesh_cmd_test_unbind_local_model_app_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_add_local_model_sub_s
{
    uint16_t            elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
    uint16_t            sub_address;
});

typedef struct sl_btmesh_cmd_test_add_local_model_sub_s sl_btmesh_cmd_test_add_local_model_sub_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_remove_local_model_sub_s
{
    uint16_t            elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
    uint16_t            sub_address;
});

typedef struct sl_btmesh_cmd_test_remove_local_model_sub_s sl_btmesh_cmd_test_remove_local_model_sub_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_add_local_model_sub_va_s
{
    uint16_t            elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
    uint8array          sub_address;
});

typedef struct sl_btmesh_cmd_test_add_local_model_sub_va_s sl_btmesh_cmd_test_add_local_model_sub_va_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_remove_local_model_sub_va_s
{
    uint16_t            elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
    uint8array          sub_address;
});

typedef struct sl_btmesh_cmd_test_remove_local_model_sub_va_s sl_btmesh_cmd_test_remove_local_model_sub_va_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_get_local_model_sub_s
{
    uint16_t            elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
});

typedef struct sl_btmesh_cmd_test_get_local_model_sub_s sl_btmesh_cmd_test_get_local_model_sub_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_set_local_model_pub_s
{
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
    uint16_t            pub_address;
    uint8_t             ttl;
    uint8_t             period;
    uint8_t             retrans;
    uint8_t             credentials;
});

typedef struct sl_btmesh_cmd_test_set_local_model_pub_s sl_btmesh_cmd_test_set_local_model_pub_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_set_local_model_pub_va_s
{
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
    uint8_t             ttl;
    uint8_t             period;
    uint8_t             retrans;
    uint8_t             credentials;
    uint8array          pub_address;
});

typedef struct sl_btmesh_cmd_test_set_local_model_pub_va_s sl_btmesh_cmd_test_set_local_model_pub_va_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_get_local_model_pub_s
{
    uint16_t            elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
});

typedef struct sl_btmesh_cmd_test_get_local_model_pub_s sl_btmesh_cmd_test_get_local_model_pub_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_set_local_heartbeat_subscription_s
{
    uint16_t            subscription_source;
    uint16_t            subscription_destination;
    uint8_t             period_log;
});

typedef struct sl_btmesh_cmd_test_set_local_heartbeat_subscription_s sl_btmesh_cmd_test_set_local_heartbeat_subscription_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_set_local_heartbeat_publication_s
{
    uint16_t            publication_address;
    uint8_t             count_log;
    uint8_t             period_log;
    uint8_t             ttl;
    uint16_t            features;
    uint16_t            publication_netkey_index;
});

typedef struct sl_btmesh_cmd_test_set_local_heartbeat_publication_s sl_btmesh_cmd_test_set_local_heartbeat_publication_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_set_local_config_s
{
    uint16_t            id;
    uint16_t            netkey_index;
    uint8array          value;
});

typedef struct sl_btmesh_cmd_test_set_local_config_s sl_btmesh_cmd_test_set_local_config_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_get_local_config_s
{
    uint16_t            id;
    uint16_t            netkey_index;
});

typedef struct sl_btmesh_cmd_test_get_local_config_s sl_btmesh_cmd_test_get_local_config_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_add_local_key_s
{
    uint8_t             key_type;
    aes_key_128         key;
    uint16_t            key_index;
    uint16_t            netkey_index;
});

typedef struct sl_btmesh_cmd_test_add_local_key_s sl_btmesh_cmd_test_add_local_key_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_remove_local_key_s
{
    uint8_t             key_type;
    uint16_t            key_index;
});

typedef struct sl_btmesh_cmd_test_remove_local_key_s sl_btmesh_cmd_test_remove_local_key_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_update_local_key_s
{
    uint8_t             key_type;
    aes_key_128         key;
    uint16_t            key_index;
});

typedef struct sl_btmesh_cmd_test_update_local_key_s sl_btmesh_cmd_test_update_local_key_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_set_sar_config_s
{
    uint32_t            incomplete_timer_ms;
    uint32_t            pending_ack_base_ms;
    uint32_t            pending_ack_mul_ms;
    uint32_t            wait_for_ack_base_ms;
    uint32_t            wait_for_ack_mul_ms;
    uint8_t             max_send_rounds;
});

typedef struct sl_btmesh_cmd_test_set_sar_config_s sl_btmesh_cmd_test_set_sar_config_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_set_adv_bearer_state_s
{
    uint8_t             state;
});

typedef struct sl_btmesh_cmd_test_set_adv_bearer_state_s sl_btmesh_cmd_test_set_adv_bearer_state_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_prov_get_device_key_s
{
    uint16_t            address;
});

typedef struct sl_btmesh_cmd_test_prov_get_device_key_s sl_btmesh_cmd_test_prov_get_device_key_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_prov_prepare_key_refresh_s
{
    aes_key_128         net_key;
    uint8array          app_keys;
});

typedef struct sl_btmesh_cmd_test_prov_prepare_key_refresh_s sl_btmesh_cmd_test_prov_prepare_key_refresh_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_cancel_segmented_tx_s
{
    uint16_t            src_addr;
    uint16_t            dst_addr;
});

typedef struct sl_btmesh_cmd_test_cancel_segmented_tx_s sl_btmesh_cmd_test_cancel_segmented_tx_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_set_iv_index_s
{
    uint32_t            iv_index;
});

typedef struct sl_btmesh_cmd_test_set_iv_index_s sl_btmesh_cmd_test_set_iv_index_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_set_element_seqnum_s
{
    uint16_t            elem_index;
    uint32_t            seqnum;
});

typedef struct sl_btmesh_cmd_test_set_element_seqnum_s sl_btmesh_cmd_test_set_element_seqnum_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_set_model_option_s
{
    uint16_t            elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
    uint8_t             option;
    uint32_t            value;
});

typedef struct sl_btmesh_cmd_test_set_model_option_s sl_btmesh_cmd_test_set_model_option_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_get_local_model_app_bindings_s
{
    uint16_t            elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
});

typedef struct sl_btmesh_cmd_test_get_local_model_app_bindings_s sl_btmesh_cmd_test_get_local_model_app_bindings_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_get_replay_protection_list_entry_s
{
    uint16_t            address;
});

typedef struct sl_btmesh_cmd_test_get_replay_protection_list_entry_s sl_btmesh_cmd_test_get_replay_protection_list_entry_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_clear_replay_protection_list_entry_s
{
    uint16_t            address;
});

typedef struct sl_btmesh_cmd_test_clear_replay_protection_list_entry_s sl_btmesh_cmd_test_clear_replay_protection_list_entry_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_set_replay_protection_list_diagnostics_s
{
    uint8_t             enable;
});

typedef struct sl_btmesh_cmd_test_set_replay_protection_list_diagnostics_s sl_btmesh_cmd_test_set_replay_protection_list_diagnostics_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_get_model_option_s
{
    uint16_t            elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
    uint8_t             option;
});

typedef struct sl_btmesh_cmd_test_get_model_option_s sl_btmesh_cmd_test_get_model_option_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_set_default_ttl_s
{
    uint8_t             set_value;
});

typedef struct sl_btmesh_cmd_test_set_default_ttl_s sl_btmesh_cmd_test_set_default_ttl_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_set_gatt_proxy_s
{
    uint8_t             set_value;
});

typedef struct sl_btmesh_cmd_test_set_gatt_proxy_s sl_btmesh_cmd_test_set_gatt_proxy_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_get_identity_s
{
    uint16_t            get_netkey_index;
});

typedef struct sl_btmesh_cmd_test_get_identity_s sl_btmesh_cmd_test_get_identity_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_set_identity_s
{
    uint16_t            set_netkey_index;
    uint8_t             set_value;
});

typedef struct sl_btmesh_cmd_test_set_identity_s sl_btmesh_cmd_test_set_identity_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_set_friend_s
{
    uint8_t             set_value;
});

typedef struct sl_btmesh_cmd_test_set_friend_s sl_btmesh_cmd_test_set_friend_t;


PACKSTRUCT( struct sl_btmesh_cmd_test_set_beacon_s
{
    uint8_t             set_value;
});

typedef struct sl_btmesh_cmd_test_set_beacon_s sl_btmesh_cmd_test_set_beacon_t;



PACKSTRUCT( struct sl_btmesh_cmd_lpn_establish_friendship_s
{
    uint16_t            netkey_index;
});

typedef struct sl_btmesh_cmd_lpn_establish_friendship_s sl_btmesh_cmd_lpn_establish_friendship_t;


PACKSTRUCT( struct sl_btmesh_cmd_lpn_poll_s
{
    uint16_t            netkey_index;
});

typedef struct sl_btmesh_cmd_lpn_poll_s sl_btmesh_cmd_lpn_poll_t;


PACKSTRUCT( struct sl_btmesh_cmd_lpn_terminate_friendship_s
{
    uint16_t            netkey_index;
});

typedef struct sl_btmesh_cmd_lpn_terminate_friendship_s sl_btmesh_cmd_lpn_terminate_friendship_t;


PACKSTRUCT( struct sl_btmesh_cmd_lpn_config_s
{
    uint8_t             setting_id;
    uint32_t            value;
});

typedef struct sl_btmesh_cmd_lpn_config_s sl_btmesh_cmd_lpn_config_t;






PACKSTRUCT( struct sl_btmesh_cmd_config_client_cancel_request_s
{
    uint32_t            handle;
});

typedef struct sl_btmesh_cmd_config_client_cancel_request_s sl_btmesh_cmd_config_client_cancel_request_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_get_request_status_s
{
    uint32_t            handle;
});

typedef struct sl_btmesh_cmd_config_client_get_request_status_s sl_btmesh_cmd_config_client_get_request_status_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_set_default_timeout_s
{
    uint32_t            timeout_ms;
    uint32_t            lpn_timeout_ms;
});

typedef struct sl_btmesh_cmd_config_client_set_default_timeout_s sl_btmesh_cmd_config_client_set_default_timeout_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_add_netkey_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint16_t            netkey_index;
});

typedef struct sl_btmesh_cmd_config_client_add_netkey_s sl_btmesh_cmd_config_client_add_netkey_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_remove_netkey_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint16_t            netkey_index;
});

typedef struct sl_btmesh_cmd_config_client_remove_netkey_s sl_btmesh_cmd_config_client_remove_netkey_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_list_netkeys_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
});

typedef struct sl_btmesh_cmd_config_client_list_netkeys_s sl_btmesh_cmd_config_client_list_netkeys_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_add_appkey_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint16_t            appkey_index;
    uint16_t            netkey_index;
});

typedef struct sl_btmesh_cmd_config_client_add_appkey_s sl_btmesh_cmd_config_client_add_appkey_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_remove_appkey_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint16_t            appkey_index;
    uint16_t            netkey_index;
});

typedef struct sl_btmesh_cmd_config_client_remove_appkey_s sl_btmesh_cmd_config_client_remove_appkey_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_list_appkeys_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint16_t            netkey_index;
});

typedef struct sl_btmesh_cmd_config_client_list_appkeys_s sl_btmesh_cmd_config_client_list_appkeys_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_bind_model_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint8_t             elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
    uint16_t            appkey_index;
});

typedef struct sl_btmesh_cmd_config_client_bind_model_s sl_btmesh_cmd_config_client_bind_model_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_unbind_model_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint8_t             elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
    uint16_t            appkey_index;
});

typedef struct sl_btmesh_cmd_config_client_unbind_model_s sl_btmesh_cmd_config_client_unbind_model_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_list_bindings_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint8_t             elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
});

typedef struct sl_btmesh_cmd_config_client_list_bindings_s sl_btmesh_cmd_config_client_list_bindings_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_get_model_pub_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint8_t             elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
});

typedef struct sl_btmesh_cmd_config_client_get_model_pub_s sl_btmesh_cmd_config_client_get_model_pub_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_set_model_pub_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint8_t             elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
    uint16_t            address;
    uint16_t            appkey_index;
    uint8_t             credentials;
    uint8_t             ttl;
    uint32_t            period_ms;
    uint8_t             retransmit_count;
    uint16_t            retransmit_interval_ms;
});

typedef struct sl_btmesh_cmd_config_client_set_model_pub_s sl_btmesh_cmd_config_client_set_model_pub_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_set_model_pub_va_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint8_t             elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
    uuid_128            address;
    uint16_t            appkey_index;
    uint8_t             credentials;
    uint8_t             ttl;
    uint32_t            period_ms;
    uint8_t             retransmit_count;
    uint16_t            retransmit_interval_ms;
});

typedef struct sl_btmesh_cmd_config_client_set_model_pub_va_s sl_btmesh_cmd_config_client_set_model_pub_va_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_add_model_sub_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint8_t             elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
    uint16_t            sub_address;
});

typedef struct sl_btmesh_cmd_config_client_add_model_sub_s sl_btmesh_cmd_config_client_add_model_sub_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_add_model_sub_va_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint8_t             elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
    uuid_128            sub_address;
});

typedef struct sl_btmesh_cmd_config_client_add_model_sub_va_s sl_btmesh_cmd_config_client_add_model_sub_va_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_remove_model_sub_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint8_t             elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
    uint16_t            sub_address;
});

typedef struct sl_btmesh_cmd_config_client_remove_model_sub_s sl_btmesh_cmd_config_client_remove_model_sub_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_remove_model_sub_va_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint8_t             elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
    uuid_128            sub_address;
});

typedef struct sl_btmesh_cmd_config_client_remove_model_sub_va_s sl_btmesh_cmd_config_client_remove_model_sub_va_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_set_model_sub_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint8_t             elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
    uint16_t            sub_address;
});

typedef struct sl_btmesh_cmd_config_client_set_model_sub_s sl_btmesh_cmd_config_client_set_model_sub_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_set_model_sub_va_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint8_t             elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
    uuid_128            sub_address;
});

typedef struct sl_btmesh_cmd_config_client_set_model_sub_va_s sl_btmesh_cmd_config_client_set_model_sub_va_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_clear_model_sub_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint8_t             elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
});

typedef struct sl_btmesh_cmd_config_client_clear_model_sub_s sl_btmesh_cmd_config_client_clear_model_sub_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_list_subs_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint8_t             elem_index;
    uint16_t            vendor_id;
    uint16_t            model_id;
});

typedef struct sl_btmesh_cmd_config_client_list_subs_s sl_btmesh_cmd_config_client_list_subs_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_get_heartbeat_pub_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
});

typedef struct sl_btmesh_cmd_config_client_get_heartbeat_pub_s sl_btmesh_cmd_config_client_get_heartbeat_pub_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_set_heartbeat_pub_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint16_t            destination_address;
    uint16_t            netkey_index;
    uint8_t             count_log;
    uint8_t             period_log;
    uint8_t             ttl;
    uint16_t            features;
});

typedef struct sl_btmesh_cmd_config_client_set_heartbeat_pub_s sl_btmesh_cmd_config_client_set_heartbeat_pub_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_get_heartbeat_sub_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
});

typedef struct sl_btmesh_cmd_config_client_get_heartbeat_sub_s sl_btmesh_cmd_config_client_get_heartbeat_sub_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_set_heartbeat_sub_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint16_t            source_address;
    uint16_t            destination_address;
    uint8_t             period_log;
});

typedef struct sl_btmesh_cmd_config_client_set_heartbeat_sub_s sl_btmesh_cmd_config_client_set_heartbeat_sub_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_get_beacon_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
});

typedef struct sl_btmesh_cmd_config_client_get_beacon_s sl_btmesh_cmd_config_client_get_beacon_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_set_beacon_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint8_t             value;
});

typedef struct sl_btmesh_cmd_config_client_set_beacon_s sl_btmesh_cmd_config_client_set_beacon_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_get_default_ttl_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
});

typedef struct sl_btmesh_cmd_config_client_get_default_ttl_s sl_btmesh_cmd_config_client_get_default_ttl_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_set_default_ttl_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint8_t             value;
});

typedef struct sl_btmesh_cmd_config_client_set_default_ttl_s sl_btmesh_cmd_config_client_set_default_ttl_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_get_gatt_proxy_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
});

typedef struct sl_btmesh_cmd_config_client_get_gatt_proxy_s sl_btmesh_cmd_config_client_get_gatt_proxy_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_set_gatt_proxy_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint8_t             value;
});

typedef struct sl_btmesh_cmd_config_client_set_gatt_proxy_s sl_btmesh_cmd_config_client_set_gatt_proxy_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_get_relay_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
});

typedef struct sl_btmesh_cmd_config_client_get_relay_s sl_btmesh_cmd_config_client_get_relay_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_set_relay_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint8_t             value;
    uint8_t             retransmit_count;
    uint16_t            retransmit_interval_ms;
});

typedef struct sl_btmesh_cmd_config_client_set_relay_s sl_btmesh_cmd_config_client_set_relay_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_get_network_transmit_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
});

typedef struct sl_btmesh_cmd_config_client_get_network_transmit_s sl_btmesh_cmd_config_client_get_network_transmit_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_set_network_transmit_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint8_t             transmit_count;
    uint16_t            transmit_interval_ms;
});

typedef struct sl_btmesh_cmd_config_client_set_network_transmit_s sl_btmesh_cmd_config_client_set_network_transmit_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_get_identity_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint16_t            netkey_index;
});

typedef struct sl_btmesh_cmd_config_client_get_identity_s sl_btmesh_cmd_config_client_get_identity_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_set_identity_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint16_t            netkey_index;
    uint8_t             value;
});

typedef struct sl_btmesh_cmd_config_client_set_identity_s sl_btmesh_cmd_config_client_set_identity_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_get_friend_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
});

typedef struct sl_btmesh_cmd_config_client_get_friend_s sl_btmesh_cmd_config_client_get_friend_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_set_friend_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint8_t             value;
});

typedef struct sl_btmesh_cmd_config_client_set_friend_s sl_btmesh_cmd_config_client_set_friend_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_get_key_refresh_phase_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint16_t            netkey_index;
});

typedef struct sl_btmesh_cmd_config_client_get_key_refresh_phase_s sl_btmesh_cmd_config_client_get_key_refresh_phase_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_get_lpn_polltimeout_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint16_t            lpn_address;
});

typedef struct sl_btmesh_cmd_config_client_get_lpn_polltimeout_s sl_btmesh_cmd_config_client_get_lpn_polltimeout_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_get_dcd_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
    uint8_t             page;
});

typedef struct sl_btmesh_cmd_config_client_get_dcd_s sl_btmesh_cmd_config_client_get_dcd_t;


PACKSTRUCT( struct sl_btmesh_cmd_config_client_reset_node_s
{
    uint16_t            enc_netkey_index;
    uint16_t            server_address;
});

typedef struct sl_btmesh_cmd_config_client_reset_node_s sl_btmesh_cmd_config_client_reset_node_t;



PACKSTRUCT( struct sl_btmesh_cmd_sensor_server_init_s
{
    uint16_t            elem_index;
    uint8array          descriptors;
});

typedef struct sl_btmesh_cmd_sensor_server_init_s sl_btmesh_cmd_sensor_server_init_t;


PACKSTRUCT( struct sl_btmesh_cmd_sensor_server_deinit_s
{
    uint16_t            elem_index;
});

typedef struct sl_btmesh_cmd_sensor_server_deinit_s sl_btmesh_cmd_sensor_server_deinit_t;


PACKSTRUCT( struct sl_btmesh_cmd_sensor_server_send_descriptor_status_s
{
    uint16_t            client_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint8_t             flags;
    uint8array          descriptors;
});

typedef struct sl_btmesh_cmd_sensor_server_send_descriptor_status_s sl_btmesh_cmd_sensor_server_send_descriptor_status_t;


PACKSTRUCT( struct sl_btmesh_cmd_sensor_server_send_status_s
{
    uint16_t            client_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint8_t             flags;
    uint8array          sensor_data;
});

typedef struct sl_btmesh_cmd_sensor_server_send_status_s sl_btmesh_cmd_sensor_server_send_status_t;


PACKSTRUCT( struct sl_btmesh_cmd_sensor_server_send_column_status_s
{
    uint16_t            client_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint8_t             flags;
    uint16_t            property_id;
    uint8array          sensor_data;
});

typedef struct sl_btmesh_cmd_sensor_server_send_column_status_s sl_btmesh_cmd_sensor_server_send_column_status_t;


PACKSTRUCT( struct sl_btmesh_cmd_sensor_server_send_series_status_s
{
    uint16_t            client_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint8_t             flags;
    uint16_t            property_id;
    uint8array          sensor_data;
});

typedef struct sl_btmesh_cmd_sensor_server_send_series_status_s sl_btmesh_cmd_sensor_server_send_series_status_t;



PACKSTRUCT( struct sl_btmesh_cmd_sensor_setup_server_send_cadence_status_s
{
    uint16_t            client_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint8_t             flags;
    uint16_t            property_id;
    uint8array          params;
});

typedef struct sl_btmesh_cmd_sensor_setup_server_send_cadence_status_s sl_btmesh_cmd_sensor_setup_server_send_cadence_status_t;


PACKSTRUCT( struct sl_btmesh_cmd_sensor_setup_server_send_settings_status_s
{
    uint16_t            client_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint8_t             flags;
    uint16_t            property_id;
    uint8array          setting_ids;
});

typedef struct sl_btmesh_cmd_sensor_setup_server_send_settings_status_s sl_btmesh_cmd_sensor_setup_server_send_settings_status_t;


PACKSTRUCT( struct sl_btmesh_cmd_sensor_setup_server_send_setting_status_s
{
    uint16_t            client_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint8_t             flags;
    uint16_t            property_id;
    uint16_t            setting_id;
    uint8array          raw_value;
});

typedef struct sl_btmesh_cmd_sensor_setup_server_send_setting_status_s sl_btmesh_cmd_sensor_setup_server_send_setting_status_t;



PACKSTRUCT( struct sl_btmesh_cmd_sensor_client_get_descriptor_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint8_t             flags;
    uint16_t            property_id;
});

typedef struct sl_btmesh_cmd_sensor_client_get_descriptor_s sl_btmesh_cmd_sensor_client_get_descriptor_t;


PACKSTRUCT( struct sl_btmesh_cmd_sensor_client_get_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint8_t             flags;
    uint16_t            property_id;
});

typedef struct sl_btmesh_cmd_sensor_client_get_s sl_btmesh_cmd_sensor_client_get_t;


PACKSTRUCT( struct sl_btmesh_cmd_sensor_client_get_column_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint8_t             flags;
    uint16_t            property_id;
    uint8array          column_id;
});

typedef struct sl_btmesh_cmd_sensor_client_get_column_s sl_btmesh_cmd_sensor_client_get_column_t;


PACKSTRUCT( struct sl_btmesh_cmd_sensor_client_get_series_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint8_t             flags;
    uint16_t            property_id;
    uint8array          column_ids;
});

typedef struct sl_btmesh_cmd_sensor_client_get_series_s sl_btmesh_cmd_sensor_client_get_series_t;


PACKSTRUCT( struct sl_btmesh_cmd_sensor_client_get_cadence_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint8_t             flags;
    uint16_t            property_id;
});

typedef struct sl_btmesh_cmd_sensor_client_get_cadence_s sl_btmesh_cmd_sensor_client_get_cadence_t;


PACKSTRUCT( struct sl_btmesh_cmd_sensor_client_set_cadence_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint8_t             flags;
    uint16_t            property_id;
    uint8array          params;
});

typedef struct sl_btmesh_cmd_sensor_client_set_cadence_s sl_btmesh_cmd_sensor_client_set_cadence_t;


PACKSTRUCT( struct sl_btmesh_cmd_sensor_client_get_settings_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint8_t             flags;
    uint16_t            property_id;
});

typedef struct sl_btmesh_cmd_sensor_client_get_settings_s sl_btmesh_cmd_sensor_client_get_settings_t;


PACKSTRUCT( struct sl_btmesh_cmd_sensor_client_get_setting_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint8_t             flags;
    uint16_t            property_id;
    uint16_t            setting_id;
});

typedef struct sl_btmesh_cmd_sensor_client_get_setting_s sl_btmesh_cmd_sensor_client_get_setting_t;


PACKSTRUCT( struct sl_btmesh_cmd_sensor_client_set_setting_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint8_t             flags;
    uint16_t            property_id;
    uint16_t            setting_id;
    uint8array          raw_value;
});

typedef struct sl_btmesh_cmd_sensor_client_set_setting_s sl_btmesh_cmd_sensor_client_set_setting_t;



PACKSTRUCT( struct sl_btmesh_cmd_lc_client_init_s
{
    uint16_t            elem_index;
});

typedef struct sl_btmesh_cmd_lc_client_init_s sl_btmesh_cmd_lc_client_init_t;


PACKSTRUCT( struct sl_btmesh_cmd_lc_client_get_mode_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
});

typedef struct sl_btmesh_cmd_lc_client_get_mode_s sl_btmesh_cmd_lc_client_get_mode_t;


PACKSTRUCT( struct sl_btmesh_cmd_lc_client_set_mode_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint8_t             flags;
    uint8_t             mode;
});

typedef struct sl_btmesh_cmd_lc_client_set_mode_s sl_btmesh_cmd_lc_client_set_mode_t;


PACKSTRUCT( struct sl_btmesh_cmd_lc_client_get_om_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
});

typedef struct sl_btmesh_cmd_lc_client_get_om_s sl_btmesh_cmd_lc_client_get_om_t;


PACKSTRUCT( struct sl_btmesh_cmd_lc_client_set_om_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint8_t             flags;
    uint8_t             mode;
});

typedef struct sl_btmesh_cmd_lc_client_set_om_s sl_btmesh_cmd_lc_client_set_om_t;


PACKSTRUCT( struct sl_btmesh_cmd_lc_client_get_light_onoff_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
});

typedef struct sl_btmesh_cmd_lc_client_get_light_onoff_s sl_btmesh_cmd_lc_client_get_light_onoff_t;


PACKSTRUCT( struct sl_btmesh_cmd_lc_client_set_light_onoff_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint8_t             flags;
    uint8_t             target_state;
    uint8_t             tid;
    uint32_t            transition_time_ms;
    uint16_t            message_delay_ms;
});

typedef struct sl_btmesh_cmd_lc_client_set_light_onoff_s sl_btmesh_cmd_lc_client_set_light_onoff_t;


PACKSTRUCT( struct sl_btmesh_cmd_lc_client_get_property_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint16_t            property_id;
});

typedef struct sl_btmesh_cmd_lc_client_get_property_s sl_btmesh_cmd_lc_client_get_property_t;


PACKSTRUCT( struct sl_btmesh_cmd_lc_client_set_property_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint8_t             flags;
    uint16_t            property_id;
    uint8array          params;
});

typedef struct sl_btmesh_cmd_lc_client_set_property_s sl_btmesh_cmd_lc_client_set_property_t;



PACKSTRUCT( struct sl_btmesh_cmd_lc_server_init_s
{
    uint16_t            elem_index;
});

typedef struct sl_btmesh_cmd_lc_server_init_s sl_btmesh_cmd_lc_server_init_t;


PACKSTRUCT( struct sl_btmesh_cmd_lc_server_deinit_s
{
    uint16_t            elem_index;
});

typedef struct sl_btmesh_cmd_lc_server_deinit_s sl_btmesh_cmd_lc_server_deinit_t;


PACKSTRUCT( struct sl_btmesh_cmd_lc_server_update_mode_s
{
    uint16_t            elem_index;
    uint8_t             mode;
});

typedef struct sl_btmesh_cmd_lc_server_update_mode_s sl_btmesh_cmd_lc_server_update_mode_t;


PACKSTRUCT( struct sl_btmesh_cmd_lc_server_update_om_s
{
    uint16_t            elem_index;
    uint8_t             om;
});

typedef struct sl_btmesh_cmd_lc_server_update_om_s sl_btmesh_cmd_lc_server_update_om_t;


PACKSTRUCT( struct sl_btmesh_cmd_lc_server_update_light_onoff_s
{
    uint16_t            elem_index;
    uint8_t             light_onoff;
    uint32_t            transition_time_ms;
});

typedef struct sl_btmesh_cmd_lc_server_update_light_onoff_s sl_btmesh_cmd_lc_server_update_light_onoff_t;


PACKSTRUCT( struct sl_btmesh_cmd_lc_server_init_all_properties_s
{
    uint16_t            elem_index;
});

typedef struct sl_btmesh_cmd_lc_server_init_all_properties_s sl_btmesh_cmd_lc_server_init_all_properties_t;


PACKSTRUCT( struct sl_btmesh_cmd_lc_server_set_publish_mask_s
{
    uint16_t            elem_index;
    uint16_t            status_type;
    uint8_t             value;
});

typedef struct sl_btmesh_cmd_lc_server_set_publish_mask_s sl_btmesh_cmd_lc_server_set_publish_mask_t;


PACKSTRUCT( struct sl_btmesh_cmd_lc_server_set_regulator_interval_s
{
    uint16_t            elem_index;
    uint8_t             value;
});

typedef struct sl_btmesh_cmd_lc_server_set_regulator_interval_s sl_btmesh_cmd_lc_server_set_regulator_interval_t;


PACKSTRUCT( struct sl_btmesh_cmd_lc_server_set_event_mask_s
{
    uint16_t            elem_index;
    uint16_t            event_type;
    uint8_t             value;
});

typedef struct sl_btmesh_cmd_lc_server_set_event_mask_s sl_btmesh_cmd_lc_server_set_event_mask_t;


PACKSTRUCT( struct sl_btmesh_cmd_lc_server_get_lc_state_s
{
    uint16_t            elem_index;
});

typedef struct sl_btmesh_cmd_lc_server_get_lc_state_s sl_btmesh_cmd_lc_server_get_lc_state_t;



PACKSTRUCT( struct sl_btmesh_cmd_lc_setup_server_update_property_s
{
    uint16_t            elem_index;
    uint16_t            property_id;
    uint8array          params;
});

typedef struct sl_btmesh_cmd_lc_setup_server_update_property_s sl_btmesh_cmd_lc_setup_server_update_property_t;



PACKSTRUCT( struct sl_btmesh_cmd_scene_client_init_s
{
    uint16_t            elem_index;
});

typedef struct sl_btmesh_cmd_scene_client_init_s sl_btmesh_cmd_scene_client_init_t;


PACKSTRUCT( struct sl_btmesh_cmd_scene_client_get_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
});

typedef struct sl_btmesh_cmd_scene_client_get_s sl_btmesh_cmd_scene_client_get_t;


PACKSTRUCT( struct sl_btmesh_cmd_scene_client_get_register_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
});

typedef struct sl_btmesh_cmd_scene_client_get_register_s sl_btmesh_cmd_scene_client_get_register_t;


PACKSTRUCT( struct sl_btmesh_cmd_scene_client_recall_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            selected_scene;
    uint16_t            appkey_index;
    uint8_t             flags;
    uint8_t             tid;
    uint32_t            transition_time_ms;
    uint16_t            delay_ms;
});

typedef struct sl_btmesh_cmd_scene_client_recall_s sl_btmesh_cmd_scene_client_recall_t;


PACKSTRUCT( struct sl_btmesh_cmd_scene_client_store_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            selected_scene;
    uint16_t            appkey_index;
    uint8_t             flags;
});

typedef struct sl_btmesh_cmd_scene_client_store_s sl_btmesh_cmd_scene_client_store_t;


PACKSTRUCT( struct sl_btmesh_cmd_scene_client_delete_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            selected_scene;
    uint16_t            appkey_index;
    uint8_t             flags;
});

typedef struct sl_btmesh_cmd_scene_client_delete_s sl_btmesh_cmd_scene_client_delete_t;



PACKSTRUCT( struct sl_btmesh_cmd_scene_server_init_s
{
    uint16_t            elem_index;
});

typedef struct sl_btmesh_cmd_scene_server_init_s sl_btmesh_cmd_scene_server_init_t;


PACKSTRUCT( struct sl_btmesh_cmd_scene_server_deinit_s
{
    uint16_t            elem_index;
});

typedef struct sl_btmesh_cmd_scene_server_deinit_s sl_btmesh_cmd_scene_server_deinit_t;


PACKSTRUCT( struct sl_btmesh_cmd_scene_server_reset_register_s
{
    uint16_t            elem_index;
});

typedef struct sl_btmesh_cmd_scene_server_reset_register_s sl_btmesh_cmd_scene_server_reset_register_t;



PACKSTRUCT( struct sl_btmesh_cmd_scene_setup_server_init_s
{
    uint16_t            elem_index;
});

typedef struct sl_btmesh_cmd_scene_setup_server_init_s sl_btmesh_cmd_scene_setup_server_init_t;



PACKSTRUCT( struct sl_btmesh_cmd_scheduler_client_init_s
{
    uint16_t            elem_index;
});

typedef struct sl_btmesh_cmd_scheduler_client_init_s sl_btmesh_cmd_scheduler_client_init_t;


PACKSTRUCT( struct sl_btmesh_cmd_scheduler_client_deinit_s
{
    uint16_t            elem_index;
});

typedef struct sl_btmesh_cmd_scheduler_client_deinit_s sl_btmesh_cmd_scheduler_client_deinit_t;


PACKSTRUCT( struct sl_btmesh_cmd_scheduler_client_get_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
});

typedef struct sl_btmesh_cmd_scheduler_client_get_s sl_btmesh_cmd_scheduler_client_get_t;


PACKSTRUCT( struct sl_btmesh_cmd_scheduler_client_get_action_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint8_t             index;
});

typedef struct sl_btmesh_cmd_scheduler_client_get_action_s sl_btmesh_cmd_scheduler_client_get_action_t;


PACKSTRUCT( struct sl_btmesh_cmd_scheduler_client_set_action_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint8_t             flags;
    uint8_t             index;
    uint8_t             year;
    uint16_t            month;
    uint8_t             day;
    uint8_t             hour;
    uint8_t             minute;
    uint8_t             second;
    uint8_t             day_of_week;
    uint8_t             action;
    uint32_t            transition_time_ms;
    uint16_t            scene_number;
});

typedef struct sl_btmesh_cmd_scheduler_client_set_action_s sl_btmesh_cmd_scheduler_client_set_action_t;



PACKSTRUCT( struct sl_btmesh_cmd_scheduler_server_init_s
{
    uint16_t            elem_index;
});

typedef struct sl_btmesh_cmd_scheduler_server_init_s sl_btmesh_cmd_scheduler_server_init_t;


PACKSTRUCT( struct sl_btmesh_cmd_scheduler_server_deinit_s
{
    uint16_t            elem_index;
});

typedef struct sl_btmesh_cmd_scheduler_server_deinit_s sl_btmesh_cmd_scheduler_server_deinit_t;


PACKSTRUCT( struct sl_btmesh_cmd_scheduler_server_get_s
{
    uint16_t            elem_index;
});

typedef struct sl_btmesh_cmd_scheduler_server_get_s sl_btmesh_cmd_scheduler_server_get_t;


PACKSTRUCT( struct sl_btmesh_cmd_scheduler_server_get_action_s
{
    uint16_t            elem_index;
    uint8_t             index;
});

typedef struct sl_btmesh_cmd_scheduler_server_get_action_s sl_btmesh_cmd_scheduler_server_get_action_t;


PACKSTRUCT( struct sl_btmesh_cmd_scheduler_server_set_action_s
{
    uint16_t            elem_index;
    uint8_t             index;
    uint8_t             year;
    uint16_t            month;
    uint8_t             day;
    uint8_t             hour;
    uint8_t             minute;
    uint8_t             second;
    uint8_t             day_of_week;
    uint8_t             action;
    uint32_t            transition_time_ms;
    uint16_t            scene_number;
});

typedef struct sl_btmesh_cmd_scheduler_server_set_action_s sl_btmesh_cmd_scheduler_server_set_action_t;



PACKSTRUCT( struct sl_btmesh_cmd_time_server_init_s
{
    uint16_t            elem_index;
});

typedef struct sl_btmesh_cmd_time_server_init_s sl_btmesh_cmd_time_server_init_t;


PACKSTRUCT( struct sl_btmesh_cmd_time_server_deinit_s
{
    uint16_t            elem_index;
});

typedef struct sl_btmesh_cmd_time_server_deinit_s sl_btmesh_cmd_time_server_deinit_t;


PACKSTRUCT( struct sl_btmesh_cmd_time_server_get_time_s
{
    uint16_t            elem_index;
});

typedef struct sl_btmesh_cmd_time_server_get_time_s sl_btmesh_cmd_time_server_get_time_t;


PACKSTRUCT( struct sl_btmesh_cmd_time_server_set_time_s
{
    uint16_t            elem_index;
    uint64_t            tai_seconds;
    uint8_t             subsecond;
    uint8_t             uncertainty;
    uint8_t             time_authority;
    int16_t             time_zone_offset;
    int32_t             tai_utc_delta;
});

typedef struct sl_btmesh_cmd_time_server_set_time_s sl_btmesh_cmd_time_server_set_time_t;


PACKSTRUCT( struct sl_btmesh_cmd_time_server_get_time_zone_offset_new_s
{
    uint16_t            elem_index;
});

typedef struct sl_btmesh_cmd_time_server_get_time_zone_offset_new_s sl_btmesh_cmd_time_server_get_time_zone_offset_new_t;


PACKSTRUCT( struct sl_btmesh_cmd_time_server_set_time_zone_offset_new_s
{
    uint16_t            elem_index;
    int16_t             new_offset;
    uint64_t            tai_of_zone_change;
});

typedef struct sl_btmesh_cmd_time_server_set_time_zone_offset_new_s sl_btmesh_cmd_time_server_set_time_zone_offset_new_t;


PACKSTRUCT( struct sl_btmesh_cmd_time_server_get_tai_utc_delta_new_s
{
    uint16_t            elem_index;
});

typedef struct sl_btmesh_cmd_time_server_get_tai_utc_delta_new_s sl_btmesh_cmd_time_server_get_tai_utc_delta_new_t;


PACKSTRUCT( struct sl_btmesh_cmd_time_server_set_tai_utc_delta_new_s
{
    uint16_t            elem_index;
    int32_t             new_delta;
    uint64_t            tai_of_delta_change;
});

typedef struct sl_btmesh_cmd_time_server_set_tai_utc_delta_new_s sl_btmesh_cmd_time_server_set_tai_utc_delta_new_t;


PACKSTRUCT( struct sl_btmesh_cmd_time_server_get_time_role_s
{
    uint16_t            elem_index;
});

typedef struct sl_btmesh_cmd_time_server_get_time_role_s sl_btmesh_cmd_time_server_get_time_role_t;


PACKSTRUCT( struct sl_btmesh_cmd_time_server_set_time_role_s
{
    uint16_t            elem_index;
    uint8_t             time_role;
});

typedef struct sl_btmesh_cmd_time_server_set_time_role_s sl_btmesh_cmd_time_server_set_time_role_t;


PACKSTRUCT( struct sl_btmesh_cmd_time_server_get_datetime_s
{
    uint16_t            elem_index;
});

typedef struct sl_btmesh_cmd_time_server_get_datetime_s sl_btmesh_cmd_time_server_get_datetime_t;


PACKSTRUCT( struct sl_btmesh_cmd_time_server_publish_s
{
    uint16_t            elem_index;
});

typedef struct sl_btmesh_cmd_time_server_publish_s sl_btmesh_cmd_time_server_publish_t;


PACKSTRUCT( struct sl_btmesh_cmd_time_server_status_s
{
    uint16_t            destination_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
});

typedef struct sl_btmesh_cmd_time_server_status_s sl_btmesh_cmd_time_server_status_t;



PACKSTRUCT( struct sl_btmesh_cmd_time_client_init_s
{
    uint16_t            elem_index;
});

typedef struct sl_btmesh_cmd_time_client_init_s sl_btmesh_cmd_time_client_init_t;


PACKSTRUCT( struct sl_btmesh_cmd_time_client_deinit_s
{
    uint16_t            elem_index;
});

typedef struct sl_btmesh_cmd_time_client_deinit_s sl_btmesh_cmd_time_client_deinit_t;


PACKSTRUCT( struct sl_btmesh_cmd_time_client_get_time_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
});

typedef struct sl_btmesh_cmd_time_client_get_time_s sl_btmesh_cmd_time_client_get_time_t;


PACKSTRUCT( struct sl_btmesh_cmd_time_client_set_time_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint64_t            tai_seconds;
    uint8_t             subsecond;
    uint8_t             uncertainty;
    uint8_t             time_authority;
    int32_t             tai_utc_delta;
    int16_t             time_zone_offset;
});

typedef struct sl_btmesh_cmd_time_client_set_time_s sl_btmesh_cmd_time_client_set_time_t;


PACKSTRUCT( struct sl_btmesh_cmd_time_client_get_time_zone_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
});

typedef struct sl_btmesh_cmd_time_client_get_time_zone_s sl_btmesh_cmd_time_client_get_time_zone_t;


PACKSTRUCT( struct sl_btmesh_cmd_time_client_set_time_zone_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    int16_t             time_zone_offset_new;
    uint64_t            tai_of_zone_change;
});

typedef struct sl_btmesh_cmd_time_client_set_time_zone_s sl_btmesh_cmd_time_client_set_time_zone_t;


PACKSTRUCT( struct sl_btmesh_cmd_time_client_get_tai_utc_delta_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
});

typedef struct sl_btmesh_cmd_time_client_get_tai_utc_delta_s sl_btmesh_cmd_time_client_get_tai_utc_delta_t;


PACKSTRUCT( struct sl_btmesh_cmd_time_client_set_tai_utc_delta_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    int32_t             tai_utc_delta_new;
    uint64_t            tai_of_delta_change;
});

typedef struct sl_btmesh_cmd_time_client_set_tai_utc_delta_s sl_btmesh_cmd_time_client_set_tai_utc_delta_t;


PACKSTRUCT( struct sl_btmesh_cmd_time_client_get_time_role_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
});

typedef struct sl_btmesh_cmd_time_client_get_time_role_s sl_btmesh_cmd_time_client_get_time_role_t;


PACKSTRUCT( struct sl_btmesh_cmd_time_client_set_time_role_s
{
    uint16_t            server_address;
    uint16_t            elem_index;
    uint16_t            appkey_index;
    uint8_t             time_role;
});

typedef struct sl_btmesh_cmd_time_client_set_time_role_s sl_btmesh_cmd_time_client_set_time_role_t;





PACKSTRUCT( struct sl_btmesh_rsp_node_init_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_node_init_s sl_btmesh_rsp_node_init_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_set_exportable_keys_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_node_set_exportable_keys_s sl_btmesh_rsp_node_set_exportable_keys_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_start_unprov_beaconing_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_node_start_unprov_beaconing_s sl_btmesh_rsp_node_start_unprov_beaconing_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_stop_unprov_beaconing_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_node_stop_unprov_beaconing_s sl_btmesh_rsp_node_stop_unprov_beaconing_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_get_rssi_s
{
    uint16_t            result;
    int8_t              rssi;
});

typedef struct sl_btmesh_rsp_node_get_rssi_s sl_btmesh_rsp_node_get_rssi_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_send_input_oob_request_response_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_node_send_input_oob_request_response_s sl_btmesh_rsp_node_send_input_oob_request_response_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_get_uuid_s
{
    uint16_t            result;
    uuid_128            uuid;
});

typedef struct sl_btmesh_rsp_node_get_uuid_s sl_btmesh_rsp_node_get_uuid_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_set_provisioning_data_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_node_set_provisioning_data_s sl_btmesh_rsp_node_set_provisioning_data_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_init_oob_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_node_init_oob_s sl_btmesh_rsp_node_init_oob_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_set_ivrecovery_mode_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_node_set_ivrecovery_mode_s sl_btmesh_rsp_node_set_ivrecovery_mode_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_get_ivrecovery_mode_s
{
    uint16_t            result;
    uint8_t             mode;
});

typedef struct sl_btmesh_rsp_node_get_ivrecovery_mode_s sl_btmesh_rsp_node_get_ivrecovery_mode_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_get_statistics_s
{
    uint16_t            result;
    uint8array          statistics;
});

typedef struct sl_btmesh_rsp_node_get_statistics_s sl_btmesh_rsp_node_get_statistics_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_clear_statistics_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_node_clear_statistics_s sl_btmesh_rsp_node_clear_statistics_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_set_net_relay_delay_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_node_set_net_relay_delay_s sl_btmesh_rsp_node_set_net_relay_delay_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_get_net_relay_delay_s
{
    uint16_t            result;
    uint8_t             min_ms;
    uint8_t             max_ms;
});

typedef struct sl_btmesh_rsp_node_get_net_relay_delay_s sl_btmesh_rsp_node_get_net_relay_delay_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_get_ivupdate_state_s
{
    uint16_t            result;
    uint32_t            iv_index;
    uint8_t             state;
});

typedef struct sl_btmesh_rsp_node_get_ivupdate_state_s sl_btmesh_rsp_node_get_ivupdate_state_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_request_ivupdate_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_node_request_ivupdate_s sl_btmesh_rsp_node_request_ivupdate_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_get_seq_remaining_s
{
    uint16_t            result;
    uint32_t            count;
});

typedef struct sl_btmesh_rsp_node_get_seq_remaining_s sl_btmesh_rsp_node_get_seq_remaining_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_save_replay_protection_list_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_node_save_replay_protection_list_s sl_btmesh_rsp_node_save_replay_protection_list_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_set_uuid_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_node_set_uuid_s sl_btmesh_rsp_node_set_uuid_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_get_replay_protection_list_status_s
{
    uint16_t            result;
    uint16_t            total_entries;
    uint16_t            unsaved_entries;
});

typedef struct sl_btmesh_rsp_node_get_replay_protection_list_status_s sl_btmesh_rsp_node_get_replay_protection_list_status_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_get_element_address_s
{
    uint16_t            result;
    uint16_t            address;
});

typedef struct sl_btmesh_rsp_node_get_element_address_s sl_btmesh_rsp_node_get_element_address_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_send_static_oob_request_response_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_node_send_static_oob_request_response_s sl_btmesh_rsp_node_send_static_oob_request_response_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_reset_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_node_reset_s sl_btmesh_rsp_node_reset_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_set_beacon_reporting_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_node_set_beacon_reporting_s sl_btmesh_rsp_node_set_beacon_reporting_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_set_iv_update_age_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_node_set_iv_update_age_s sl_btmesh_rsp_node_set_iv_update_age_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_get_key_count_s
{
    uint16_t            result;
    uint32_t            count;
});

typedef struct sl_btmesh_rsp_node_get_key_count_s sl_btmesh_rsp_node_get_key_count_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_get_key_s
{
    uint16_t            result;
    uint16_t            id;
    uint16_t            netkey_index;
    aes_key_128         key;
});

typedef struct sl_btmesh_rsp_node_get_key_s sl_btmesh_rsp_node_get_key_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_get_networks_s
{
    uint16_t            result;
    uint8array          networks;
});

typedef struct sl_btmesh_rsp_node_get_networks_s sl_btmesh_rsp_node_get_networks_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_get_element_seqnum_s
{
    uint16_t            result;
    uint32_t            seqnum;
});

typedef struct sl_btmesh_rsp_node_get_element_seqnum_s sl_btmesh_rsp_node_get_element_seqnum_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_set_model_option_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_node_set_model_option_s sl_btmesh_rsp_node_set_model_option_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_get_local_dcd_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_node_get_local_dcd_s sl_btmesh_rsp_node_get_local_dcd_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_erase_mesh_nvm_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_node_erase_mesh_nvm_s sl_btmesh_rsp_node_erase_mesh_nvm_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_power_off_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_node_power_off_s sl_btmesh_rsp_node_power_off_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_set_adv_phy_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_node_set_adv_phy_s sl_btmesh_rsp_node_set_adv_phy_t;


PACKSTRUCT( struct sl_btmesh_rsp_node_get_adv_phy_s
{
    uint16_t            result;
    uint8_t             phy;
});

typedef struct sl_btmesh_rsp_node_get_adv_phy_s sl_btmesh_rsp_node_get_adv_phy_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_init_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_prov_init_s sl_btmesh_rsp_prov_init_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_scan_unprov_beacons_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_prov_scan_unprov_beacons_s sl_btmesh_rsp_prov_scan_unprov_beacons_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_create_provisioning_session_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_prov_create_provisioning_session_s sl_btmesh_rsp_prov_create_provisioning_session_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_set_provisioning_suspend_event_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_prov_set_provisioning_suspend_event_s sl_btmesh_rsp_prov_set_provisioning_suspend_event_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_provision_adv_device_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_prov_provision_adv_device_s sl_btmesh_rsp_prov_provision_adv_device_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_provision_gatt_device_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_prov_provision_gatt_device_s sl_btmesh_rsp_prov_provision_gatt_device_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_continue_provisioning_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_prov_continue_provisioning_s sl_btmesh_rsp_prov_continue_provisioning_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_abort_provisioning_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_prov_abort_provisioning_s sl_btmesh_rsp_prov_abort_provisioning_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_set_device_address_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_prov_set_device_address_s sl_btmesh_rsp_prov_set_device_address_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_create_network_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_prov_create_network_s sl_btmesh_rsp_prov_create_network_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_create_appkey_s
{
    uint16_t            result;
    uint8array          application_key;
});

typedef struct sl_btmesh_rsp_prov_create_appkey_s sl_btmesh_rsp_prov_create_appkey_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_send_oob_pkey_response_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_prov_send_oob_pkey_response_s sl_btmesh_rsp_prov_send_oob_pkey_response_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_send_oob_auth_response_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_prov_send_oob_auth_response_s sl_btmesh_rsp_prov_send_oob_auth_response_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_set_oob_requirements_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_prov_set_oob_requirements_s sl_btmesh_rsp_prov_set_oob_requirements_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_start_key_refresh_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_prov_start_key_refresh_s sl_btmesh_rsp_prov_start_key_refresh_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_get_key_refresh_exclusion_s
{
    uint16_t            result;
    uint8_t             status;
});

typedef struct sl_btmesh_rsp_prov_get_key_refresh_exclusion_s sl_btmesh_rsp_prov_get_key_refresh_exclusion_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_set_key_refresh_exclusion_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_prov_set_key_refresh_exclusion_s sl_btmesh_rsp_prov_set_key_refresh_exclusion_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_get_ddb_entry_s
{
    uint16_t            result;
    aes_key_128         device_key;
    uint16_t            netkey_index;
    uint16_t            address;
    uint8_t             elements;
});

typedef struct sl_btmesh_rsp_prov_get_ddb_entry_s sl_btmesh_rsp_prov_get_ddb_entry_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_delete_ddb_entry_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_prov_delete_ddb_entry_s sl_btmesh_rsp_prov_delete_ddb_entry_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_add_ddb_entry_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_prov_add_ddb_entry_s sl_btmesh_rsp_prov_add_ddb_entry_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_list_ddb_entries_s
{
    uint16_t            result;
    uint16_t            count;
});

typedef struct sl_btmesh_rsp_prov_list_ddb_entries_s sl_btmesh_rsp_prov_list_ddb_entries_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_initialize_network_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_prov_initialize_network_s sl_btmesh_rsp_prov_initialize_network_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_get_key_refresh_appkey_exclusion_s
{
    uint16_t            result;
    uint8_t             status;
});

typedef struct sl_btmesh_rsp_prov_get_key_refresh_appkey_exclusion_s sl_btmesh_rsp_prov_get_key_refresh_appkey_exclusion_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_set_key_refresh_appkey_exclusion_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_prov_set_key_refresh_appkey_exclusion_s sl_btmesh_rsp_prov_set_key_refresh_appkey_exclusion_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_stop_scan_unprov_beacons_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_prov_stop_scan_unprov_beacons_s sl_btmesh_rsp_prov_stop_scan_unprov_beacons_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_update_device_netkey_index_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_prov_update_device_netkey_index_s sl_btmesh_rsp_prov_update_device_netkey_index_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_suspend_key_refresh_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_prov_suspend_key_refresh_s sl_btmesh_rsp_prov_suspend_key_refresh_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_resume_key_refresh_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_prov_resume_key_refresh_s sl_btmesh_rsp_prov_resume_key_refresh_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_get_key_refresh_phase_s
{
    uint16_t            result;
    uint8_t             phase;
});

typedef struct sl_btmesh_rsp_prov_get_key_refresh_phase_s sl_btmesh_rsp_prov_get_key_refresh_phase_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_start_key_refresh_from_phase_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_prov_start_key_refresh_from_phase_s sl_btmesh_rsp_prov_start_key_refresh_from_phase_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_flush_key_refresh_state_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_prov_flush_key_refresh_state_s sl_btmesh_rsp_prov_flush_key_refresh_state_t;


PACKSTRUCT( struct sl_btmesh_rsp_prov_test_identity_s
{
    uint16_t            result;
    uint8_t             match;
});

typedef struct sl_btmesh_rsp_prov_test_identity_s sl_btmesh_rsp_prov_test_identity_t;


PACKSTRUCT( struct sl_btmesh_rsp_proxy_connect_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_proxy_connect_s sl_btmesh_rsp_proxy_connect_t;


PACKSTRUCT( struct sl_btmesh_rsp_proxy_disconnect_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_proxy_disconnect_s sl_btmesh_rsp_proxy_disconnect_t;


PACKSTRUCT( struct sl_btmesh_rsp_proxy_set_filter_type_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_proxy_set_filter_type_s sl_btmesh_rsp_proxy_set_filter_type_t;


PACKSTRUCT( struct sl_btmesh_rsp_proxy_allow_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_proxy_allow_s sl_btmesh_rsp_proxy_allow_t;


PACKSTRUCT( struct sl_btmesh_rsp_proxy_deny_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_proxy_deny_s sl_btmesh_rsp_proxy_deny_t;


PACKSTRUCT( struct sl_btmesh_rsp_proxy_optimisation_toggle_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_proxy_optimisation_toggle_s sl_btmesh_rsp_proxy_optimisation_toggle_t;


PACKSTRUCT( struct sl_btmesh_rsp_vendor_model_send_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_vendor_model_send_s sl_btmesh_rsp_vendor_model_send_t;


PACKSTRUCT( struct sl_btmesh_rsp_vendor_model_set_publication_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_vendor_model_set_publication_s sl_btmesh_rsp_vendor_model_set_publication_t;


PACKSTRUCT( struct sl_btmesh_rsp_vendor_model_clear_publication_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_vendor_model_clear_publication_s sl_btmesh_rsp_vendor_model_clear_publication_t;


PACKSTRUCT( struct sl_btmesh_rsp_vendor_model_publish_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_vendor_model_publish_s sl_btmesh_rsp_vendor_model_publish_t;


PACKSTRUCT( struct sl_btmesh_rsp_vendor_model_init_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_vendor_model_init_s sl_btmesh_rsp_vendor_model_init_t;


PACKSTRUCT( struct sl_btmesh_rsp_vendor_model_deinit_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_vendor_model_deinit_s sl_btmesh_rsp_vendor_model_deinit_t;


PACKSTRUCT( struct sl_btmesh_rsp_vendor_model_send_tracked_s
{
    uint16_t            result;
    uint16_t            handle;
});

typedef struct sl_btmesh_rsp_vendor_model_send_tracked_s sl_btmesh_rsp_vendor_model_send_tracked_t;


PACKSTRUCT( struct sl_btmesh_rsp_vendor_model_set_publication_tracked_s
{
    uint16_t            result;
    uint16_t            handle;
});

typedef struct sl_btmesh_rsp_vendor_model_set_publication_tracked_s sl_btmesh_rsp_vendor_model_set_publication_tracked_t;


PACKSTRUCT( struct sl_btmesh_rsp_health_client_get_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_health_client_get_s sl_btmesh_rsp_health_client_get_t;


PACKSTRUCT( struct sl_btmesh_rsp_health_client_clear_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_health_client_clear_s sl_btmesh_rsp_health_client_clear_t;


PACKSTRUCT( struct sl_btmesh_rsp_health_client_test_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_health_client_test_s sl_btmesh_rsp_health_client_test_t;


PACKSTRUCT( struct sl_btmesh_rsp_health_client_get_period_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_health_client_get_period_s sl_btmesh_rsp_health_client_get_period_t;


PACKSTRUCT( struct sl_btmesh_rsp_health_client_set_period_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_health_client_set_period_s sl_btmesh_rsp_health_client_set_period_t;


PACKSTRUCT( struct sl_btmesh_rsp_health_client_get_attention_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_health_client_get_attention_s sl_btmesh_rsp_health_client_get_attention_t;


PACKSTRUCT( struct sl_btmesh_rsp_health_client_set_attention_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_health_client_set_attention_s sl_btmesh_rsp_health_client_set_attention_t;


PACKSTRUCT( struct sl_btmesh_rsp_health_server_set_fault_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_health_server_set_fault_s sl_btmesh_rsp_health_server_set_fault_t;


PACKSTRUCT( struct sl_btmesh_rsp_health_server_clear_fault_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_health_server_clear_fault_s sl_btmesh_rsp_health_server_clear_fault_t;


PACKSTRUCT( struct sl_btmesh_rsp_health_server_send_test_response_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_health_server_send_test_response_s sl_btmesh_rsp_health_server_send_test_response_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_client_get_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_client_get_s sl_btmesh_rsp_generic_client_get_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_client_set_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_client_set_s sl_btmesh_rsp_generic_client_set_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_client_publish_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_client_publish_s sl_btmesh_rsp_generic_client_publish_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_client_get_params_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_client_get_params_s sl_btmesh_rsp_generic_client_get_params_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_client_init_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_client_init_s sl_btmesh_rsp_generic_client_init_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_client_init_common_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_client_init_common_s sl_btmesh_rsp_generic_client_init_common_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_client_init_on_off_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_client_init_on_off_s sl_btmesh_rsp_generic_client_init_on_off_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_client_init_level_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_client_init_level_s sl_btmesh_rsp_generic_client_init_level_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_client_init_default_transition_time_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_client_init_default_transition_time_s sl_btmesh_rsp_generic_client_init_default_transition_time_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_client_init_power_on_off_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_client_init_power_on_off_s sl_btmesh_rsp_generic_client_init_power_on_off_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_client_init_power_level_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_client_init_power_level_s sl_btmesh_rsp_generic_client_init_power_level_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_client_init_battery_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_client_init_battery_s sl_btmesh_rsp_generic_client_init_battery_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_client_init_location_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_client_init_location_s sl_btmesh_rsp_generic_client_init_location_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_client_init_property_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_client_init_property_s sl_btmesh_rsp_generic_client_init_property_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_client_init_lightness_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_client_init_lightness_s sl_btmesh_rsp_generic_client_init_lightness_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_client_init_ctl_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_client_init_ctl_s sl_btmesh_rsp_generic_client_init_ctl_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_client_init_hsl_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_client_init_hsl_s sl_btmesh_rsp_generic_client_init_hsl_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_server_respond_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_server_respond_s sl_btmesh_rsp_generic_server_respond_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_server_update_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_server_update_s sl_btmesh_rsp_generic_server_update_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_server_publish_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_server_publish_s sl_btmesh_rsp_generic_server_publish_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_server_init_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_server_init_s sl_btmesh_rsp_generic_server_init_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_server_init_common_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_server_init_common_s sl_btmesh_rsp_generic_server_init_common_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_server_init_on_off_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_server_init_on_off_s sl_btmesh_rsp_generic_server_init_on_off_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_server_init_level_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_server_init_level_s sl_btmesh_rsp_generic_server_init_level_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_server_init_default_transition_time_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_server_init_default_transition_time_s sl_btmesh_rsp_generic_server_init_default_transition_time_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_server_init_power_on_off_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_server_init_power_on_off_s sl_btmesh_rsp_generic_server_init_power_on_off_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_server_init_power_level_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_server_init_power_level_s sl_btmesh_rsp_generic_server_init_power_level_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_server_init_battery_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_server_init_battery_s sl_btmesh_rsp_generic_server_init_battery_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_server_init_location_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_server_init_location_s sl_btmesh_rsp_generic_server_init_location_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_server_init_property_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_server_init_property_s sl_btmesh_rsp_generic_server_init_property_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_server_init_lightness_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_server_init_lightness_s sl_btmesh_rsp_generic_server_init_lightness_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_server_init_ctl_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_server_init_ctl_s sl_btmesh_rsp_generic_server_init_ctl_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_server_init_hsl_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_generic_server_init_hsl_s sl_btmesh_rsp_generic_server_init_hsl_t;


PACKSTRUCT( struct sl_btmesh_rsp_generic_server_get_cached_state_s
{
    uint16_t            result;
    uint32_t            remaining_ms;
    uint8array          parameters;
});

typedef struct sl_btmesh_rsp_generic_server_get_cached_state_s sl_btmesh_rsp_generic_server_get_cached_state_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_get_nettx_s
{
    uint16_t            result;
    uint8_t             count;
    uint8_t             interval;
});

typedef struct sl_btmesh_rsp_test_get_nettx_s sl_btmesh_rsp_test_get_nettx_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_set_nettx_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_test_set_nettx_s sl_btmesh_rsp_test_set_nettx_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_get_relay_s
{
    uint16_t            result;
    uint8_t             enabled;
    uint8_t             count;
    uint8_t             interval;
});

typedef struct sl_btmesh_rsp_test_get_relay_s sl_btmesh_rsp_test_get_relay_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_set_relay_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_test_set_relay_s sl_btmesh_rsp_test_set_relay_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_set_adv_scan_params_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_test_set_adv_scan_params_s sl_btmesh_rsp_test_set_adv_scan_params_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_set_ivupdate_test_mode_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_test_set_ivupdate_test_mode_s sl_btmesh_rsp_test_set_ivupdate_test_mode_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_get_ivupdate_test_mode_s
{
    uint16_t            result;
    uint8_t             mode;
});

typedef struct sl_btmesh_rsp_test_get_ivupdate_test_mode_s sl_btmesh_rsp_test_get_ivupdate_test_mode_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_set_segment_send_delay_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_test_set_segment_send_delay_s sl_btmesh_rsp_test_set_segment_send_delay_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_set_ivupdate_state_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_test_set_ivupdate_state_s sl_btmesh_rsp_test_set_ivupdate_state_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_send_beacons_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_test_send_beacons_s sl_btmesh_rsp_test_send_beacons_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_bind_local_model_app_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_test_bind_local_model_app_s sl_btmesh_rsp_test_bind_local_model_app_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_unbind_local_model_app_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_test_unbind_local_model_app_s sl_btmesh_rsp_test_unbind_local_model_app_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_add_local_model_sub_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_test_add_local_model_sub_s sl_btmesh_rsp_test_add_local_model_sub_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_remove_local_model_sub_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_test_remove_local_model_sub_s sl_btmesh_rsp_test_remove_local_model_sub_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_add_local_model_sub_va_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_test_add_local_model_sub_va_s sl_btmesh_rsp_test_add_local_model_sub_va_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_remove_local_model_sub_va_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_test_remove_local_model_sub_va_s sl_btmesh_rsp_test_remove_local_model_sub_va_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_get_local_model_sub_s
{
    uint16_t            result;
    uint8array          addresses;
});

typedef struct sl_btmesh_rsp_test_get_local_model_sub_s sl_btmesh_rsp_test_get_local_model_sub_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_set_local_model_pub_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_test_set_local_model_pub_s sl_btmesh_rsp_test_set_local_model_pub_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_set_local_model_pub_va_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_test_set_local_model_pub_va_s sl_btmesh_rsp_test_set_local_model_pub_va_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_get_local_model_pub_s
{
    uint16_t            result;
    uint16_t            appkey_index;
    uint16_t            pub_address;
    uint8_t             ttl;
    uint8_t             period;
    uint8_t             retrans;
    uint8_t             credentials;
});

typedef struct sl_btmesh_rsp_test_get_local_model_pub_s sl_btmesh_rsp_test_get_local_model_pub_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_set_local_heartbeat_subscription_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_test_set_local_heartbeat_subscription_s sl_btmesh_rsp_test_set_local_heartbeat_subscription_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_get_local_heartbeat_subscription_s
{
    uint16_t            result;
    uint16_t            count;
    uint8_t             hop_min;
    uint8_t             hop_max;
});

typedef struct sl_btmesh_rsp_test_get_local_heartbeat_subscription_s sl_btmesh_rsp_test_get_local_heartbeat_subscription_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_get_local_heartbeat_publication_s
{
    uint16_t            result;
    uint16_t            publication_address;
    uint8_t             count;
    uint8_t             period_log;
    uint8_t             ttl;
    uint16_t            features;
    uint16_t            publication_netkey_index;
});

typedef struct sl_btmesh_rsp_test_get_local_heartbeat_publication_s sl_btmesh_rsp_test_get_local_heartbeat_publication_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_set_local_heartbeat_publication_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_test_set_local_heartbeat_publication_s sl_btmesh_rsp_test_set_local_heartbeat_publication_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_set_local_config_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_test_set_local_config_s sl_btmesh_rsp_test_set_local_config_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_get_local_config_s
{
    uint16_t            result;
    uint8array          data;
});

typedef struct sl_btmesh_rsp_test_get_local_config_s sl_btmesh_rsp_test_get_local_config_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_add_local_key_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_test_add_local_key_s sl_btmesh_rsp_test_add_local_key_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_remove_local_key_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_test_remove_local_key_s sl_btmesh_rsp_test_remove_local_key_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_update_local_key_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_test_update_local_key_s sl_btmesh_rsp_test_update_local_key_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_set_sar_config_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_test_set_sar_config_s sl_btmesh_rsp_test_set_sar_config_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_set_adv_bearer_state_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_test_set_adv_bearer_state_s sl_btmesh_rsp_test_set_adv_bearer_state_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_prov_get_device_key_s
{
    uint16_t            result;
    aes_key_128         device_key;
});

typedef struct sl_btmesh_rsp_test_prov_get_device_key_s sl_btmesh_rsp_test_prov_get_device_key_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_prov_prepare_key_refresh_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_test_prov_prepare_key_refresh_s sl_btmesh_rsp_test_prov_prepare_key_refresh_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_cancel_segmented_tx_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_test_cancel_segmented_tx_s sl_btmesh_rsp_test_cancel_segmented_tx_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_set_iv_index_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_test_set_iv_index_s sl_btmesh_rsp_test_set_iv_index_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_set_element_seqnum_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_test_set_element_seqnum_s sl_btmesh_rsp_test_set_element_seqnum_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_set_model_option_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_test_set_model_option_s sl_btmesh_rsp_test_set_model_option_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_get_local_model_app_bindings_s
{
    uint16_t            result;
    uint8array          appkeys;
});

typedef struct sl_btmesh_rsp_test_get_local_model_app_bindings_s sl_btmesh_rsp_test_get_local_model_app_bindings_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_get_replay_protection_list_entry_s
{
    uint16_t            result;
    uint32_t            seq;
    uint32_t            seq_ivindex;
});

typedef struct sl_btmesh_rsp_test_get_replay_protection_list_entry_s sl_btmesh_rsp_test_get_replay_protection_list_entry_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_clear_replay_protection_list_entry_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_test_clear_replay_protection_list_entry_s sl_btmesh_rsp_test_clear_replay_protection_list_entry_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_set_replay_protection_list_diagnostics_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_test_set_replay_protection_list_diagnostics_s sl_btmesh_rsp_test_set_replay_protection_list_diagnostics_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_get_model_option_s
{
    uint16_t            result;
    uint32_t            value;
});

typedef struct sl_btmesh_rsp_test_get_model_option_s sl_btmesh_rsp_test_get_model_option_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_get_default_ttl_s
{
    uint16_t            result;
    uint8_t             value;
});

typedef struct sl_btmesh_rsp_test_get_default_ttl_s sl_btmesh_rsp_test_get_default_ttl_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_set_default_ttl_s
{
    uint16_t            result;
    uint8_t             value;
});

typedef struct sl_btmesh_rsp_test_set_default_ttl_s sl_btmesh_rsp_test_set_default_ttl_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_get_gatt_proxy_s
{
    uint16_t            result;
    uint8_t             value;
});

typedef struct sl_btmesh_rsp_test_get_gatt_proxy_s sl_btmesh_rsp_test_get_gatt_proxy_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_set_gatt_proxy_s
{
    uint16_t            result;
    uint8_t             value;
});

typedef struct sl_btmesh_rsp_test_set_gatt_proxy_s sl_btmesh_rsp_test_set_gatt_proxy_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_get_identity_s
{
    uint16_t            result;
    uint16_t            netkey_index;
    uint8_t             value;
});

typedef struct sl_btmesh_rsp_test_get_identity_s sl_btmesh_rsp_test_get_identity_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_set_identity_s
{
    uint16_t            result;
    uint16_t            netkey_index;
    uint8_t             value;
});

typedef struct sl_btmesh_rsp_test_set_identity_s sl_btmesh_rsp_test_set_identity_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_get_friend_s
{
    uint16_t            result;
    uint8_t             value;
});

typedef struct sl_btmesh_rsp_test_get_friend_s sl_btmesh_rsp_test_get_friend_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_set_friend_s
{
    uint16_t            result;
    uint8_t             value;
});

typedef struct sl_btmesh_rsp_test_set_friend_s sl_btmesh_rsp_test_set_friend_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_get_beacon_s
{
    uint16_t            result;
    uint8_t             value;
});

typedef struct sl_btmesh_rsp_test_get_beacon_s sl_btmesh_rsp_test_get_beacon_t;


PACKSTRUCT( struct sl_btmesh_rsp_test_set_beacon_s
{
    uint16_t            result;
    uint8_t             value;
});

typedef struct sl_btmesh_rsp_test_set_beacon_s sl_btmesh_rsp_test_set_beacon_t;


PACKSTRUCT( struct sl_btmesh_rsp_lpn_init_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_lpn_init_s sl_btmesh_rsp_lpn_init_t;


PACKSTRUCT( struct sl_btmesh_rsp_lpn_deinit_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_lpn_deinit_s sl_btmesh_rsp_lpn_deinit_t;


PACKSTRUCT( struct sl_btmesh_rsp_lpn_establish_friendship_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_lpn_establish_friendship_s sl_btmesh_rsp_lpn_establish_friendship_t;


PACKSTRUCT( struct sl_btmesh_rsp_lpn_poll_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_lpn_poll_s sl_btmesh_rsp_lpn_poll_t;


PACKSTRUCT( struct sl_btmesh_rsp_lpn_terminate_friendship_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_lpn_terminate_friendship_s sl_btmesh_rsp_lpn_terminate_friendship_t;


PACKSTRUCT( struct sl_btmesh_rsp_lpn_config_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_lpn_config_s sl_btmesh_rsp_lpn_config_t;


PACKSTRUCT( struct sl_btmesh_rsp_friend_init_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_friend_init_s sl_btmesh_rsp_friend_init_t;


PACKSTRUCT( struct sl_btmesh_rsp_friend_deinit_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_friend_deinit_s sl_btmesh_rsp_friend_deinit_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_cancel_request_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_config_client_cancel_request_s sl_btmesh_rsp_config_client_cancel_request_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_get_request_status_s
{
    uint16_t            result;
    uint16_t            server_address;
    uint16_t            opcode;
    uint32_t            age_ms;
    uint32_t            remaining_ms;
    uint8_t             friend_acked;
});

typedef struct sl_btmesh_rsp_config_client_get_request_status_s sl_btmesh_rsp_config_client_get_request_status_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_get_default_timeout_s
{
    uint16_t            result;
    uint32_t            timeout_ms;
    uint32_t            lpn_timeout_ms;
});

typedef struct sl_btmesh_rsp_config_client_get_default_timeout_s sl_btmesh_rsp_config_client_get_default_timeout_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_set_default_timeout_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_config_client_set_default_timeout_s sl_btmesh_rsp_config_client_set_default_timeout_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_add_netkey_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_add_netkey_s sl_btmesh_rsp_config_client_add_netkey_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_remove_netkey_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_remove_netkey_s sl_btmesh_rsp_config_client_remove_netkey_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_list_netkeys_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_list_netkeys_s sl_btmesh_rsp_config_client_list_netkeys_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_add_appkey_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_add_appkey_s sl_btmesh_rsp_config_client_add_appkey_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_remove_appkey_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_remove_appkey_s sl_btmesh_rsp_config_client_remove_appkey_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_list_appkeys_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_list_appkeys_s sl_btmesh_rsp_config_client_list_appkeys_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_bind_model_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_bind_model_s sl_btmesh_rsp_config_client_bind_model_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_unbind_model_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_unbind_model_s sl_btmesh_rsp_config_client_unbind_model_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_list_bindings_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_list_bindings_s sl_btmesh_rsp_config_client_list_bindings_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_get_model_pub_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_get_model_pub_s sl_btmesh_rsp_config_client_get_model_pub_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_set_model_pub_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_set_model_pub_s sl_btmesh_rsp_config_client_set_model_pub_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_set_model_pub_va_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_set_model_pub_va_s sl_btmesh_rsp_config_client_set_model_pub_va_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_add_model_sub_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_add_model_sub_s sl_btmesh_rsp_config_client_add_model_sub_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_add_model_sub_va_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_add_model_sub_va_s sl_btmesh_rsp_config_client_add_model_sub_va_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_remove_model_sub_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_remove_model_sub_s sl_btmesh_rsp_config_client_remove_model_sub_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_remove_model_sub_va_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_remove_model_sub_va_s sl_btmesh_rsp_config_client_remove_model_sub_va_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_set_model_sub_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_set_model_sub_s sl_btmesh_rsp_config_client_set_model_sub_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_set_model_sub_va_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_set_model_sub_va_s sl_btmesh_rsp_config_client_set_model_sub_va_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_clear_model_sub_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_clear_model_sub_s sl_btmesh_rsp_config_client_clear_model_sub_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_list_subs_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_list_subs_s sl_btmesh_rsp_config_client_list_subs_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_get_heartbeat_pub_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_get_heartbeat_pub_s sl_btmesh_rsp_config_client_get_heartbeat_pub_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_set_heartbeat_pub_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_set_heartbeat_pub_s sl_btmesh_rsp_config_client_set_heartbeat_pub_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_get_heartbeat_sub_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_get_heartbeat_sub_s sl_btmesh_rsp_config_client_get_heartbeat_sub_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_set_heartbeat_sub_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_set_heartbeat_sub_s sl_btmesh_rsp_config_client_set_heartbeat_sub_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_get_beacon_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_get_beacon_s sl_btmesh_rsp_config_client_get_beacon_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_set_beacon_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_set_beacon_s sl_btmesh_rsp_config_client_set_beacon_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_get_default_ttl_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_get_default_ttl_s sl_btmesh_rsp_config_client_get_default_ttl_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_set_default_ttl_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_set_default_ttl_s sl_btmesh_rsp_config_client_set_default_ttl_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_get_gatt_proxy_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_get_gatt_proxy_s sl_btmesh_rsp_config_client_get_gatt_proxy_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_set_gatt_proxy_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_set_gatt_proxy_s sl_btmesh_rsp_config_client_set_gatt_proxy_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_get_relay_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_get_relay_s sl_btmesh_rsp_config_client_get_relay_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_set_relay_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_set_relay_s sl_btmesh_rsp_config_client_set_relay_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_get_network_transmit_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_get_network_transmit_s sl_btmesh_rsp_config_client_get_network_transmit_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_set_network_transmit_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_set_network_transmit_s sl_btmesh_rsp_config_client_set_network_transmit_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_get_identity_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_get_identity_s sl_btmesh_rsp_config_client_get_identity_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_set_identity_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_set_identity_s sl_btmesh_rsp_config_client_set_identity_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_get_friend_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_get_friend_s sl_btmesh_rsp_config_client_get_friend_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_set_friend_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_set_friend_s sl_btmesh_rsp_config_client_set_friend_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_get_key_refresh_phase_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_get_key_refresh_phase_s sl_btmesh_rsp_config_client_get_key_refresh_phase_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_get_lpn_polltimeout_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_get_lpn_polltimeout_s sl_btmesh_rsp_config_client_get_lpn_polltimeout_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_get_dcd_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_get_dcd_s sl_btmesh_rsp_config_client_get_dcd_t;


PACKSTRUCT( struct sl_btmesh_rsp_config_client_reset_node_s
{
    uint16_t            result;
    uint32_t            handle;
});

typedef struct sl_btmesh_rsp_config_client_reset_node_s sl_btmesh_rsp_config_client_reset_node_t;


PACKSTRUCT( struct sl_btmesh_rsp_sensor_server_init_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_sensor_server_init_s sl_btmesh_rsp_sensor_server_init_t;


PACKSTRUCT( struct sl_btmesh_rsp_sensor_server_deinit_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_sensor_server_deinit_s sl_btmesh_rsp_sensor_server_deinit_t;


PACKSTRUCT( struct sl_btmesh_rsp_sensor_server_send_descriptor_status_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_sensor_server_send_descriptor_status_s sl_btmesh_rsp_sensor_server_send_descriptor_status_t;


PACKSTRUCT( struct sl_btmesh_rsp_sensor_server_send_status_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_sensor_server_send_status_s sl_btmesh_rsp_sensor_server_send_status_t;


PACKSTRUCT( struct sl_btmesh_rsp_sensor_server_send_column_status_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_sensor_server_send_column_status_s sl_btmesh_rsp_sensor_server_send_column_status_t;


PACKSTRUCT( struct sl_btmesh_rsp_sensor_server_send_series_status_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_sensor_server_send_series_status_s sl_btmesh_rsp_sensor_server_send_series_status_t;


PACKSTRUCT( struct sl_btmesh_rsp_sensor_setup_server_send_cadence_status_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_sensor_setup_server_send_cadence_status_s sl_btmesh_rsp_sensor_setup_server_send_cadence_status_t;


PACKSTRUCT( struct sl_btmesh_rsp_sensor_setup_server_send_settings_status_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_sensor_setup_server_send_settings_status_s sl_btmesh_rsp_sensor_setup_server_send_settings_status_t;


PACKSTRUCT( struct sl_btmesh_rsp_sensor_setup_server_send_setting_status_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_sensor_setup_server_send_setting_status_s sl_btmesh_rsp_sensor_setup_server_send_setting_status_t;


PACKSTRUCT( struct sl_btmesh_rsp_sensor_client_init_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_sensor_client_init_s sl_btmesh_rsp_sensor_client_init_t;


PACKSTRUCT( struct sl_btmesh_rsp_sensor_client_deinit_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_sensor_client_deinit_s sl_btmesh_rsp_sensor_client_deinit_t;


PACKSTRUCT( struct sl_btmesh_rsp_sensor_client_get_descriptor_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_sensor_client_get_descriptor_s sl_btmesh_rsp_sensor_client_get_descriptor_t;


PACKSTRUCT( struct sl_btmesh_rsp_sensor_client_get_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_sensor_client_get_s sl_btmesh_rsp_sensor_client_get_t;


PACKSTRUCT( struct sl_btmesh_rsp_sensor_client_get_column_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_sensor_client_get_column_s sl_btmesh_rsp_sensor_client_get_column_t;


PACKSTRUCT( struct sl_btmesh_rsp_sensor_client_get_series_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_sensor_client_get_series_s sl_btmesh_rsp_sensor_client_get_series_t;


PACKSTRUCT( struct sl_btmesh_rsp_sensor_client_get_cadence_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_sensor_client_get_cadence_s sl_btmesh_rsp_sensor_client_get_cadence_t;


PACKSTRUCT( struct sl_btmesh_rsp_sensor_client_set_cadence_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_sensor_client_set_cadence_s sl_btmesh_rsp_sensor_client_set_cadence_t;


PACKSTRUCT( struct sl_btmesh_rsp_sensor_client_get_settings_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_sensor_client_get_settings_s sl_btmesh_rsp_sensor_client_get_settings_t;


PACKSTRUCT( struct sl_btmesh_rsp_sensor_client_get_setting_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_sensor_client_get_setting_s sl_btmesh_rsp_sensor_client_get_setting_t;


PACKSTRUCT( struct sl_btmesh_rsp_sensor_client_set_setting_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_sensor_client_set_setting_s sl_btmesh_rsp_sensor_client_set_setting_t;


PACKSTRUCT( struct sl_btmesh_rsp_lc_client_init_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_lc_client_init_s sl_btmesh_rsp_lc_client_init_t;


PACKSTRUCT( struct sl_btmesh_rsp_lc_client_get_mode_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_lc_client_get_mode_s sl_btmesh_rsp_lc_client_get_mode_t;


PACKSTRUCT( struct sl_btmesh_rsp_lc_client_set_mode_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_lc_client_set_mode_s sl_btmesh_rsp_lc_client_set_mode_t;


PACKSTRUCT( struct sl_btmesh_rsp_lc_client_get_om_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_lc_client_get_om_s sl_btmesh_rsp_lc_client_get_om_t;


PACKSTRUCT( struct sl_btmesh_rsp_lc_client_set_om_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_lc_client_set_om_s sl_btmesh_rsp_lc_client_set_om_t;


PACKSTRUCT( struct sl_btmesh_rsp_lc_client_get_light_onoff_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_lc_client_get_light_onoff_s sl_btmesh_rsp_lc_client_get_light_onoff_t;


PACKSTRUCT( struct sl_btmesh_rsp_lc_client_set_light_onoff_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_lc_client_set_light_onoff_s sl_btmesh_rsp_lc_client_set_light_onoff_t;


PACKSTRUCT( struct sl_btmesh_rsp_lc_client_get_property_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_lc_client_get_property_s sl_btmesh_rsp_lc_client_get_property_t;


PACKSTRUCT( struct sl_btmesh_rsp_lc_client_set_property_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_lc_client_set_property_s sl_btmesh_rsp_lc_client_set_property_t;


PACKSTRUCT( struct sl_btmesh_rsp_lc_server_init_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_lc_server_init_s sl_btmesh_rsp_lc_server_init_t;


PACKSTRUCT( struct sl_btmesh_rsp_lc_server_deinit_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_lc_server_deinit_s sl_btmesh_rsp_lc_server_deinit_t;


PACKSTRUCT( struct sl_btmesh_rsp_lc_server_update_mode_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_lc_server_update_mode_s sl_btmesh_rsp_lc_server_update_mode_t;


PACKSTRUCT( struct sl_btmesh_rsp_lc_server_update_om_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_lc_server_update_om_s sl_btmesh_rsp_lc_server_update_om_t;


PACKSTRUCT( struct sl_btmesh_rsp_lc_server_update_light_onoff_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_lc_server_update_light_onoff_s sl_btmesh_rsp_lc_server_update_light_onoff_t;


PACKSTRUCT( struct sl_btmesh_rsp_lc_server_init_all_properties_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_lc_server_init_all_properties_s sl_btmesh_rsp_lc_server_init_all_properties_t;


PACKSTRUCT( struct sl_btmesh_rsp_lc_server_set_publish_mask_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_lc_server_set_publish_mask_s sl_btmesh_rsp_lc_server_set_publish_mask_t;


PACKSTRUCT( struct sl_btmesh_rsp_lc_server_set_regulator_interval_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_lc_server_set_regulator_interval_s sl_btmesh_rsp_lc_server_set_regulator_interval_t;


PACKSTRUCT( struct sl_btmesh_rsp_lc_server_set_event_mask_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_lc_server_set_event_mask_s sl_btmesh_rsp_lc_server_set_event_mask_t;


PACKSTRUCT( struct sl_btmesh_rsp_lc_server_get_lc_state_s
{
    uint16_t            result;
    uint8_t             state;
    uint32_t            transition_time;
});

typedef struct sl_btmesh_rsp_lc_server_get_lc_state_s sl_btmesh_rsp_lc_server_get_lc_state_t;


PACKSTRUCT( struct sl_btmesh_rsp_lc_setup_server_update_property_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_lc_setup_server_update_property_s sl_btmesh_rsp_lc_setup_server_update_property_t;


PACKSTRUCT( struct sl_btmesh_rsp_scene_client_init_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_scene_client_init_s sl_btmesh_rsp_scene_client_init_t;


PACKSTRUCT( struct sl_btmesh_rsp_scene_client_get_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_scene_client_get_s sl_btmesh_rsp_scene_client_get_t;


PACKSTRUCT( struct sl_btmesh_rsp_scene_client_get_register_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_scene_client_get_register_s sl_btmesh_rsp_scene_client_get_register_t;


PACKSTRUCT( struct sl_btmesh_rsp_scene_client_recall_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_scene_client_recall_s sl_btmesh_rsp_scene_client_recall_t;


PACKSTRUCT( struct sl_btmesh_rsp_scene_client_store_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_scene_client_store_s sl_btmesh_rsp_scene_client_store_t;


PACKSTRUCT( struct sl_btmesh_rsp_scene_client_delete_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_scene_client_delete_s sl_btmesh_rsp_scene_client_delete_t;


PACKSTRUCT( struct sl_btmesh_rsp_scene_server_init_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_scene_server_init_s sl_btmesh_rsp_scene_server_init_t;


PACKSTRUCT( struct sl_btmesh_rsp_scene_server_deinit_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_scene_server_deinit_s sl_btmesh_rsp_scene_server_deinit_t;


PACKSTRUCT( struct sl_btmesh_rsp_scene_server_reset_register_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_scene_server_reset_register_s sl_btmesh_rsp_scene_server_reset_register_t;


PACKSTRUCT( struct sl_btmesh_rsp_scene_server_enable_compact_recall_events_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_scene_server_enable_compact_recall_events_s sl_btmesh_rsp_scene_server_enable_compact_recall_events_t;


PACKSTRUCT( struct sl_btmesh_rsp_scene_setup_server_init_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_scene_setup_server_init_s sl_btmesh_rsp_scene_setup_server_init_t;


PACKSTRUCT( struct sl_btmesh_rsp_scheduler_client_init_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_scheduler_client_init_s sl_btmesh_rsp_scheduler_client_init_t;


PACKSTRUCT( struct sl_btmesh_rsp_scheduler_client_deinit_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_scheduler_client_deinit_s sl_btmesh_rsp_scheduler_client_deinit_t;


PACKSTRUCT( struct sl_btmesh_rsp_scheduler_client_get_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_scheduler_client_get_s sl_btmesh_rsp_scheduler_client_get_t;


PACKSTRUCT( struct sl_btmesh_rsp_scheduler_client_get_action_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_scheduler_client_get_action_s sl_btmesh_rsp_scheduler_client_get_action_t;


PACKSTRUCT( struct sl_btmesh_rsp_scheduler_client_set_action_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_scheduler_client_set_action_s sl_btmesh_rsp_scheduler_client_set_action_t;


PACKSTRUCT( struct sl_btmesh_rsp_scheduler_server_init_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_scheduler_server_init_s sl_btmesh_rsp_scheduler_server_init_t;


PACKSTRUCT( struct sl_btmesh_rsp_scheduler_server_deinit_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_scheduler_server_deinit_s sl_btmesh_rsp_scheduler_server_deinit_t;


PACKSTRUCT( struct sl_btmesh_rsp_scheduler_server_get_s
{
    uint16_t            result;
    uint16_t            status;
});

typedef struct sl_btmesh_rsp_scheduler_server_get_s sl_btmesh_rsp_scheduler_server_get_t;


PACKSTRUCT( struct sl_btmesh_rsp_scheduler_server_get_action_s
{
    uint16_t            result;
    uint8_t             index_;
    uint8_t             year;
    uint16_t            month;
    uint8_t             day;
    uint8_t             hour;
    uint8_t             minute;
    uint8_t             second;
    uint8_t             day_of_week;
    uint8_t             action;
    uint32_t            transition_time_ms;
    uint16_t            scene_number;
});

typedef struct sl_btmesh_rsp_scheduler_server_get_action_s sl_btmesh_rsp_scheduler_server_get_action_t;


PACKSTRUCT( struct sl_btmesh_rsp_scheduler_server_set_action_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_scheduler_server_set_action_s sl_btmesh_rsp_scheduler_server_set_action_t;


PACKSTRUCT( struct sl_btmesh_rsp_time_server_init_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_time_server_init_s sl_btmesh_rsp_time_server_init_t;


PACKSTRUCT( struct sl_btmesh_rsp_time_server_deinit_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_time_server_deinit_s sl_btmesh_rsp_time_server_deinit_t;


PACKSTRUCT( struct sl_btmesh_rsp_time_server_get_time_s
{
    uint16_t            result;
    uint64_t            tai_seconds;
    uint8_t             subsecond;
    uint8_t             uncertainty;
    uint8_t             time_authority;
    int16_t             time_zone_offset;
    int32_t             tai_utc_delta;
});

typedef struct sl_btmesh_rsp_time_server_get_time_s sl_btmesh_rsp_time_server_get_time_t;


PACKSTRUCT( struct sl_btmesh_rsp_time_server_set_time_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_time_server_set_time_s sl_btmesh_rsp_time_server_set_time_t;


PACKSTRUCT( struct sl_btmesh_rsp_time_server_get_time_zone_offset_new_s
{
    uint16_t            result;
    int16_t             new_offset;
    uint64_t            tai_of_zone_change;
});

typedef struct sl_btmesh_rsp_time_server_get_time_zone_offset_new_s sl_btmesh_rsp_time_server_get_time_zone_offset_new_t;


PACKSTRUCT( struct sl_btmesh_rsp_time_server_set_time_zone_offset_new_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_time_server_set_time_zone_offset_new_s sl_btmesh_rsp_time_server_set_time_zone_offset_new_t;


PACKSTRUCT( struct sl_btmesh_rsp_time_server_get_tai_utc_delta_new_s
{
    uint16_t            result;
    int32_t             new_delta;
    uint64_t            tai_of_delta_change;
});

typedef struct sl_btmesh_rsp_time_server_get_tai_utc_delta_new_s sl_btmesh_rsp_time_server_get_tai_utc_delta_new_t;


PACKSTRUCT( struct sl_btmesh_rsp_time_server_set_tai_utc_delta_new_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_time_server_set_tai_utc_delta_new_s sl_btmesh_rsp_time_server_set_tai_utc_delta_new_t;


PACKSTRUCT( struct sl_btmesh_rsp_time_server_get_time_role_s
{
    uint16_t            result;
    uint8_t             time_role;
});

typedef struct sl_btmesh_rsp_time_server_get_time_role_s sl_btmesh_rsp_time_server_get_time_role_t;


PACKSTRUCT( struct sl_btmesh_rsp_time_server_set_time_role_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_time_server_set_time_role_s sl_btmesh_rsp_time_server_set_time_role_t;


PACKSTRUCT( struct sl_btmesh_rsp_time_server_get_datetime_s
{
    uint16_t            result;
    uint16_t            year;
    uint8_t             month;
    uint8_t             day;
    uint8_t             hour;
    uint8_t             min;
    uint8_t             sec;
    uint16_t            ms;
    int16_t             timezone;
    uint8_t             day_of_week;
});

typedef struct sl_btmesh_rsp_time_server_get_datetime_s sl_btmesh_rsp_time_server_get_datetime_t;


PACKSTRUCT( struct sl_btmesh_rsp_time_server_publish_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_time_server_publish_s sl_btmesh_rsp_time_server_publish_t;


PACKSTRUCT( struct sl_btmesh_rsp_time_server_status_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_time_server_status_s sl_btmesh_rsp_time_server_status_t;


PACKSTRUCT( struct sl_btmesh_rsp_time_client_init_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_time_client_init_s sl_btmesh_rsp_time_client_init_t;


PACKSTRUCT( struct sl_btmesh_rsp_time_client_deinit_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_time_client_deinit_s sl_btmesh_rsp_time_client_deinit_t;


PACKSTRUCT( struct sl_btmesh_rsp_time_client_get_time_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_time_client_get_time_s sl_btmesh_rsp_time_client_get_time_t;


PACKSTRUCT( struct sl_btmesh_rsp_time_client_set_time_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_time_client_set_time_s sl_btmesh_rsp_time_client_set_time_t;


PACKSTRUCT( struct sl_btmesh_rsp_time_client_get_time_zone_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_time_client_get_time_zone_s sl_btmesh_rsp_time_client_get_time_zone_t;


PACKSTRUCT( struct sl_btmesh_rsp_time_client_set_time_zone_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_time_client_set_time_zone_s sl_btmesh_rsp_time_client_set_time_zone_t;


PACKSTRUCT( struct sl_btmesh_rsp_time_client_get_tai_utc_delta_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_time_client_get_tai_utc_delta_s sl_btmesh_rsp_time_client_get_tai_utc_delta_t;


PACKSTRUCT( struct sl_btmesh_rsp_time_client_set_tai_utc_delta_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_time_client_set_tai_utc_delta_s sl_btmesh_rsp_time_client_set_tai_utc_delta_t;


PACKSTRUCT( struct sl_btmesh_rsp_time_client_get_time_role_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_time_client_get_time_role_s sl_btmesh_rsp_time_client_get_time_role_t;


PACKSTRUCT( struct sl_btmesh_rsp_time_client_set_time_role_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_time_client_set_time_role_s sl_btmesh_rsp_time_client_set_time_role_t;


PACKSTRUCT( struct sl_btmesh_rsp_migration_migrate_keys_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_migration_migrate_keys_s sl_btmesh_rsp_migration_migrate_keys_t;


PACKSTRUCT( struct sl_btmesh_rsp_migration_migrate_ddb_s
{
    uint16_t            result;
});

typedef struct sl_btmesh_rsp_migration_migrate_ddb_s sl_btmesh_rsp_migration_migrate_ddb_t;



PACKSTRUCT( struct sl_btmesh_packet {
  uint32_t   header;
  union {
    uint8_t handle;
    sl_btmesh_cmd_node_start_unprov_beaconing_t                  cmd_node_start_unprov_beaconing;
    sl_btmesh_cmd_node_send_input_oob_request_response_t         cmd_node_send_input_oob_request_response;
    sl_btmesh_cmd_node_set_provisioning_data_t                   cmd_node_set_provisioning_data;
    sl_btmesh_cmd_node_init_oob_t                                cmd_node_init_oob;
    sl_btmesh_cmd_node_set_ivrecovery_mode_t                     cmd_node_set_ivrecovery_mode;
    sl_btmesh_cmd_node_set_net_relay_delay_t                     cmd_node_set_net_relay_delay;
    sl_btmesh_cmd_node_get_seq_remaining_t                       cmd_node_get_seq_remaining;
    sl_btmesh_cmd_node_set_uuid_t                                cmd_node_set_uuid;
    sl_btmesh_cmd_node_get_element_address_t                     cmd_node_get_element_address;
    sl_btmesh_cmd_node_send_static_oob_request_response_t        cmd_node_send_static_oob_request_response;
    sl_btmesh_cmd_node_set_beacon_reporting_t                    cmd_node_set_beacon_reporting;
    sl_btmesh_cmd_node_set_iv_update_age_t                       cmd_node_set_iv_update_age;
    sl_btmesh_cmd_node_get_key_count_t                           cmd_node_get_key_count;
    sl_btmesh_cmd_node_get_key_t                                 cmd_node_get_key;
    sl_btmesh_cmd_node_get_element_seqnum_t                      cmd_node_get_element_seqnum;
    sl_btmesh_cmd_node_set_model_option_t                        cmd_node_set_model_option;
    sl_btmesh_cmd_node_get_local_dcd_t                           cmd_node_get_local_dcd;
    sl_btmesh_cmd_node_set_adv_phy_t                             cmd_node_set_adv_phy;
    sl_btmesh_cmd_prov_create_provisioning_session_t             cmd_prov_create_provisioning_session;
    sl_btmesh_cmd_prov_set_provisioning_suspend_event_t          cmd_prov_set_provisioning_suspend_event;
    sl_btmesh_cmd_prov_provision_adv_device_t                    cmd_prov_provision_adv_device;
    sl_btmesh_cmd_prov_provision_gatt_device_t                   cmd_prov_provision_gatt_device;
    sl_btmesh_cmd_prov_continue_provisioning_t                   cmd_prov_continue_provisioning;
    sl_btmesh_cmd_prov_abort_provisioning_t                      cmd_prov_abort_provisioning;
    sl_btmesh_cmd_prov_set_device_address_t                      cmd_prov_set_device_address;
    sl_btmesh_cmd_prov_create_network_t                          cmd_prov_create_network;
    sl_btmesh_cmd_prov_create_appkey_t                           cmd_prov_create_appkey;
    sl_btmesh_cmd_prov_send_oob_pkey_response_t                  cmd_prov_send_oob_pkey_response;
    sl_btmesh_cmd_prov_send_oob_auth_response_t                  cmd_prov_send_oob_auth_response;
    sl_btmesh_cmd_prov_set_oob_requirements_t                    cmd_prov_set_oob_requirements;
    sl_btmesh_cmd_prov_start_key_refresh_t                       cmd_prov_start_key_refresh;
    sl_btmesh_cmd_prov_get_key_refresh_exclusion_t               cmd_prov_get_key_refresh_exclusion;
    sl_btmesh_cmd_prov_set_key_refresh_exclusion_t               cmd_prov_set_key_refresh_exclusion;
    sl_btmesh_cmd_prov_get_ddb_entry_t                           cmd_prov_get_ddb_entry;
    sl_btmesh_cmd_prov_delete_ddb_entry_t                        cmd_prov_delete_ddb_entry;
    sl_btmesh_cmd_prov_add_ddb_entry_t                           cmd_prov_add_ddb_entry;
    sl_btmesh_cmd_prov_initialize_network_t                      cmd_prov_initialize_network;
    sl_btmesh_cmd_prov_get_key_refresh_appkey_exclusion_t        cmd_prov_get_key_refresh_appkey_exclusion;
    sl_btmesh_cmd_prov_set_key_refresh_appkey_exclusion_t        cmd_prov_set_key_refresh_appkey_exclusion;
    sl_btmesh_cmd_prov_update_device_netkey_index_t              cmd_prov_update_device_netkey_index;
    sl_btmesh_cmd_prov_suspend_key_refresh_t                     cmd_prov_suspend_key_refresh;
    sl_btmesh_cmd_prov_resume_key_refresh_t                      cmd_prov_resume_key_refresh;
    sl_btmesh_cmd_prov_get_key_refresh_phase_t                   cmd_prov_get_key_refresh_phase;
    sl_btmesh_cmd_prov_start_key_refresh_from_phase_t            cmd_prov_start_key_refresh_from_phase;
    sl_btmesh_cmd_prov_flush_key_refresh_state_t                 cmd_prov_flush_key_refresh_state;
    sl_btmesh_cmd_prov_test_identity_t                           cmd_prov_test_identity;
    sl_btmesh_cmd_proxy_connect_t                                cmd_proxy_connect;
    sl_btmesh_cmd_proxy_disconnect_t                             cmd_proxy_disconnect;
    sl_btmesh_cmd_proxy_set_filter_type_t                        cmd_proxy_set_filter_type;
    sl_btmesh_cmd_proxy_allow_t                                  cmd_proxy_allow;
    sl_btmesh_cmd_proxy_deny_t                                   cmd_proxy_deny;
    sl_btmesh_cmd_proxy_optimisation_toggle_t                    cmd_proxy_optimisation_toggle;
    sl_btmesh_cmd_vendor_model_send_t                            cmd_vendor_model_send;
    sl_btmesh_cmd_vendor_model_set_publication_t                 cmd_vendor_model_set_publication;
    sl_btmesh_cmd_vendor_model_clear_publication_t               cmd_vendor_model_clear_publication;
    sl_btmesh_cmd_vendor_model_publish_t                         cmd_vendor_model_publish;
    sl_btmesh_cmd_vendor_model_init_t                            cmd_vendor_model_init;
    sl_btmesh_cmd_vendor_model_deinit_t                          cmd_vendor_model_deinit;
    sl_btmesh_cmd_vendor_model_send_tracked_t                    cmd_vendor_model_send_tracked;
    sl_btmesh_cmd_vendor_model_set_publication_tracked_t         cmd_vendor_model_set_publication_tracked;
    sl_btmesh_cmd_health_client_get_t                            cmd_health_client_get;
    sl_btmesh_cmd_health_client_clear_t                          cmd_health_client_clear;
    sl_btmesh_cmd_health_client_test_t                           cmd_health_client_test;
    sl_btmesh_cmd_health_client_get_period_t                     cmd_health_client_get_period;
    sl_btmesh_cmd_health_client_set_period_t                     cmd_health_client_set_period;
    sl_btmesh_cmd_health_client_get_attention_t                  cmd_health_client_get_attention;
    sl_btmesh_cmd_health_client_set_attention_t                  cmd_health_client_set_attention;
    sl_btmesh_cmd_health_server_set_fault_t                      cmd_health_server_set_fault;
    sl_btmesh_cmd_health_server_clear_fault_t                    cmd_health_server_clear_fault;
    sl_btmesh_cmd_health_server_send_test_response_t             cmd_health_server_send_test_response;
    sl_btmesh_cmd_generic_client_get_t                           cmd_generic_client_get;
    sl_btmesh_cmd_generic_client_set_t                           cmd_generic_client_set;
    sl_btmesh_cmd_generic_client_publish_t                       cmd_generic_client_publish;
    sl_btmesh_cmd_generic_client_get_params_t                    cmd_generic_client_get_params;
    sl_btmesh_cmd_generic_server_respond_t                       cmd_generic_server_respond;
    sl_btmesh_cmd_generic_server_update_t                        cmd_generic_server_update;
    sl_btmesh_cmd_generic_server_publish_t                       cmd_generic_server_publish;
    sl_btmesh_cmd_generic_server_get_cached_state_t              cmd_generic_server_get_cached_state;
    sl_btmesh_cmd_test_set_nettx_t                               cmd_test_set_nettx;
    sl_btmesh_cmd_test_set_relay_t                               cmd_test_set_relay;
    sl_btmesh_cmd_test_set_adv_scan_params_t                     cmd_test_set_adv_scan_params;
    sl_btmesh_cmd_test_set_ivupdate_test_mode_t                  cmd_test_set_ivupdate_test_mode;
    sl_btmesh_cmd_test_set_segment_send_delay_t                  cmd_test_set_segment_send_delay;
    sl_btmesh_cmd_test_set_ivupdate_state_t                      cmd_test_set_ivupdate_state;
    sl_btmesh_cmd_test_bind_local_model_app_t                    cmd_test_bind_local_model_app;
    sl_btmesh_cmd_test_unbind_local_model_app_t                  cmd_test_unbind_local_model_app;
    sl_btmesh_cmd_test_add_local_model_sub_t                     cmd_test_add_local_model_sub;
    sl_btmesh_cmd_test_remove_local_model_sub_t                  cmd_test_remove_local_model_sub;
    sl_btmesh_cmd_test_add_local_model_sub_va_t                  cmd_test_add_local_model_sub_va;
    sl_btmesh_cmd_test_remove_local_model_sub_va_t               cmd_test_remove_local_model_sub_va;
    sl_btmesh_cmd_test_get_local_model_sub_t                     cmd_test_get_local_model_sub;
    sl_btmesh_cmd_test_set_local_model_pub_t                     cmd_test_set_local_model_pub;
    sl_btmesh_cmd_test_set_local_model_pub_va_t                  cmd_test_set_local_model_pub_va;
    sl_btmesh_cmd_test_get_local_model_pub_t                     cmd_test_get_local_model_pub;
    sl_btmesh_cmd_test_set_local_heartbeat_subscription_t        cmd_test_set_local_heartbeat_subscription;
    sl_btmesh_cmd_test_set_local_heartbeat_publication_t         cmd_test_set_local_heartbeat_publication;
    sl_btmesh_cmd_test_set_local_config_t                        cmd_test_set_local_config;
    sl_btmesh_cmd_test_get_local_config_t                        cmd_test_get_local_config;
    sl_btmesh_cmd_test_add_local_key_t                           cmd_test_add_local_key;
    sl_btmesh_cmd_test_remove_local_key_t                        cmd_test_remove_local_key;
    sl_btmesh_cmd_test_update_local_key_t                        cmd_test_update_local_key;
    sl_btmesh_cmd_test_set_sar_config_t                          cmd_test_set_sar_config;
    sl_btmesh_cmd_test_set_adv_bearer_state_t                    cmd_test_set_adv_bearer_state;
    sl_btmesh_cmd_test_prov_get_device_key_t                     cmd_test_prov_get_device_key;
    sl_btmesh_cmd_test_prov_prepare_key_refresh_t                cmd_test_prov_prepare_key_refresh;
    sl_btmesh_cmd_test_cancel_segmented_tx_t                     cmd_test_cancel_segmented_tx;
    sl_btmesh_cmd_test_set_iv_index_t                            cmd_test_set_iv_index;
    sl_btmesh_cmd_test_set_element_seqnum_t                      cmd_test_set_element_seqnum;
    sl_btmesh_cmd_test_set_model_option_t                        cmd_test_set_model_option;
    sl_btmesh_cmd_test_get_local_model_app_bindings_t            cmd_test_get_local_model_app_bindings;
    sl_btmesh_cmd_test_get_replay_protection_list_entry_t        cmd_test_get_replay_protection_list_entry;
    sl_btmesh_cmd_test_clear_replay_protection_list_entry_t      cmd_test_clear_replay_protection_list_entry;
    sl_btmesh_cmd_test_set_replay_protection_list_diagnostics_t  cmd_test_set_replay_protection_list_diagnostics;
    sl_btmesh_cmd_test_get_model_option_t                        cmd_test_get_model_option;
    sl_btmesh_cmd_test_set_default_ttl_t                         cmd_test_set_default_ttl;
    sl_btmesh_cmd_test_set_gatt_proxy_t                          cmd_test_set_gatt_proxy;
    sl_btmesh_cmd_test_get_identity_t                            cmd_test_get_identity;
    sl_btmesh_cmd_test_set_identity_t                            cmd_test_set_identity;
    sl_btmesh_cmd_test_set_friend_t                              cmd_test_set_friend;
    sl_btmesh_cmd_test_set_beacon_t                              cmd_test_set_beacon;
    sl_btmesh_cmd_lpn_establish_friendship_t                     cmd_lpn_establish_friendship;
    sl_btmesh_cmd_lpn_poll_t                                     cmd_lpn_poll;
    sl_btmesh_cmd_lpn_terminate_friendship_t                     cmd_lpn_terminate_friendship;
    sl_btmesh_cmd_lpn_config_t                                   cmd_lpn_config;
    sl_btmesh_cmd_config_client_cancel_request_t                 cmd_config_client_cancel_request;
    sl_btmesh_cmd_config_client_get_request_status_t             cmd_config_client_get_request_status;
    sl_btmesh_cmd_config_client_set_default_timeout_t            cmd_config_client_set_default_timeout;
    sl_btmesh_cmd_config_client_add_netkey_t                     cmd_config_client_add_netkey;
    sl_btmesh_cmd_config_client_remove_netkey_t                  cmd_config_client_remove_netkey;
    sl_btmesh_cmd_config_client_list_netkeys_t                   cmd_config_client_list_netkeys;
    sl_btmesh_cmd_config_client_add_appkey_t                     cmd_config_client_add_appkey;
    sl_btmesh_cmd_config_client_remove_appkey_t                  cmd_config_client_remove_appkey;
    sl_btmesh_cmd_config_client_list_appkeys_t                   cmd_config_client_list_appkeys;
    sl_btmesh_cmd_config_client_bind_model_t                     cmd_config_client_bind_model;
    sl_btmesh_cmd_config_client_unbind_model_t                   cmd_config_client_unbind_model;
    sl_btmesh_cmd_config_client_list_bindings_t                  cmd_config_client_list_bindings;
    sl_btmesh_cmd_config_client_get_model_pub_t                  cmd_config_client_get_model_pub;
    sl_btmesh_cmd_config_client_set_model_pub_t                  cmd_config_client_set_model_pub;
    sl_btmesh_cmd_config_client_set_model_pub_va_t               cmd_config_client_set_model_pub_va;
    sl_btmesh_cmd_config_client_add_model_sub_t                  cmd_config_client_add_model_sub;
    sl_btmesh_cmd_config_client_add_model_sub_va_t               cmd_config_client_add_model_sub_va;
    sl_btmesh_cmd_config_client_remove_model_sub_t               cmd_config_client_remove_model_sub;
    sl_btmesh_cmd_config_client_remove_model_sub_va_t            cmd_config_client_remove_model_sub_va;
    sl_btmesh_cmd_config_client_set_model_sub_t                  cmd_config_client_set_model_sub;
    sl_btmesh_cmd_config_client_set_model_sub_va_t               cmd_config_client_set_model_sub_va;
    sl_btmesh_cmd_config_client_clear_model_sub_t                cmd_config_client_clear_model_sub;
    sl_btmesh_cmd_config_client_list_subs_t                      cmd_config_client_list_subs;
    sl_btmesh_cmd_config_client_get_heartbeat_pub_t              cmd_config_client_get_heartbeat_pub;
    sl_btmesh_cmd_config_client_set_heartbeat_pub_t              cmd_config_client_set_heartbeat_pub;
    sl_btmesh_cmd_config_client_get_heartbeat_sub_t              cmd_config_client_get_heartbeat_sub;
    sl_btmesh_cmd_config_client_set_heartbeat_sub_t              cmd_config_client_set_heartbeat_sub;
    sl_btmesh_cmd_config_client_get_beacon_t                     cmd_config_client_get_beacon;
    sl_btmesh_cmd_config_client_set_beacon_t                     cmd_config_client_set_beacon;
    sl_btmesh_cmd_config_client_get_default_ttl_t                cmd_config_client_get_default_ttl;
    sl_btmesh_cmd_config_client_set_default_ttl_t                cmd_config_client_set_default_ttl;
    sl_btmesh_cmd_config_client_get_gatt_proxy_t                 cmd_config_client_get_gatt_proxy;
    sl_btmesh_cmd_config_client_set_gatt_proxy_t                 cmd_config_client_set_gatt_proxy;
    sl_btmesh_cmd_config_client_get_relay_t                      cmd_config_client_get_relay;
    sl_btmesh_cmd_config_client_set_relay_t                      cmd_config_client_set_relay;
    sl_btmesh_cmd_config_client_get_network_transmit_t           cmd_config_client_get_network_transmit;
    sl_btmesh_cmd_config_client_set_network_transmit_t           cmd_config_client_set_network_transmit;
    sl_btmesh_cmd_config_client_get_identity_t                   cmd_config_client_get_identity;
    sl_btmesh_cmd_config_client_set_identity_t                   cmd_config_client_set_identity;
    sl_btmesh_cmd_config_client_get_friend_t                     cmd_config_client_get_friend;
    sl_btmesh_cmd_config_client_set_friend_t                     cmd_config_client_set_friend;
    sl_btmesh_cmd_config_client_get_key_refresh_phase_t          cmd_config_client_get_key_refresh_phase;
    sl_btmesh_cmd_config_client_get_lpn_polltimeout_t            cmd_config_client_get_lpn_polltimeout;
    sl_btmesh_cmd_config_client_get_dcd_t                        cmd_config_client_get_dcd;
    sl_btmesh_cmd_config_client_reset_node_t                     cmd_config_client_reset_node;
    sl_btmesh_cmd_sensor_server_init_t                           cmd_sensor_server_init;
    sl_btmesh_cmd_sensor_server_deinit_t                         cmd_sensor_server_deinit;
    sl_btmesh_cmd_sensor_server_send_descriptor_status_t         cmd_sensor_server_send_descriptor_status;
    sl_btmesh_cmd_sensor_server_send_status_t                    cmd_sensor_server_send_status;
    sl_btmesh_cmd_sensor_server_send_column_status_t             cmd_sensor_server_send_column_status;
    sl_btmesh_cmd_sensor_server_send_series_status_t             cmd_sensor_server_send_series_status;
    sl_btmesh_cmd_sensor_setup_server_send_cadence_status_t      cmd_sensor_setup_server_send_cadence_status;
    sl_btmesh_cmd_sensor_setup_server_send_settings_status_t     cmd_sensor_setup_server_send_settings_status;
    sl_btmesh_cmd_sensor_setup_server_send_setting_status_t      cmd_sensor_setup_server_send_setting_status;
    sl_btmesh_cmd_sensor_client_get_descriptor_t                 cmd_sensor_client_get_descriptor;
    sl_btmesh_cmd_sensor_client_get_t                            cmd_sensor_client_get;
    sl_btmesh_cmd_sensor_client_get_column_t                     cmd_sensor_client_get_column;
    sl_btmesh_cmd_sensor_client_get_series_t                     cmd_sensor_client_get_series;
    sl_btmesh_cmd_sensor_client_get_cadence_t                    cmd_sensor_client_get_cadence;
    sl_btmesh_cmd_sensor_client_set_cadence_t                    cmd_sensor_client_set_cadence;
    sl_btmesh_cmd_sensor_client_get_settings_t                   cmd_sensor_client_get_settings;
    sl_btmesh_cmd_sensor_client_get_setting_t                    cmd_sensor_client_get_setting;
    sl_btmesh_cmd_sensor_client_set_setting_t                    cmd_sensor_client_set_setting;
    sl_btmesh_cmd_lc_client_init_t                               cmd_lc_client_init;
    sl_btmesh_cmd_lc_client_get_mode_t                           cmd_lc_client_get_mode;
    sl_btmesh_cmd_lc_client_set_mode_t                           cmd_lc_client_set_mode;
    sl_btmesh_cmd_lc_client_get_om_t                             cmd_lc_client_get_om;
    sl_btmesh_cmd_lc_client_set_om_t                             cmd_lc_client_set_om;
    sl_btmesh_cmd_lc_client_get_light_onoff_t                    cmd_lc_client_get_light_onoff;
    sl_btmesh_cmd_lc_client_set_light_onoff_t                    cmd_lc_client_set_light_onoff;
    sl_btmesh_cmd_lc_client_get_property_t                       cmd_lc_client_get_property;
    sl_btmesh_cmd_lc_client_set_property_t                       cmd_lc_client_set_property;
    sl_btmesh_cmd_lc_server_init_t                               cmd_lc_server_init;
    sl_btmesh_cmd_lc_server_deinit_t                             cmd_lc_server_deinit;
    sl_btmesh_cmd_lc_server_update_mode_t                        cmd_lc_server_update_mode;
    sl_btmesh_cmd_lc_server_update_om_t                          cmd_lc_server_update_om;
    sl_btmesh_cmd_lc_server_update_light_onoff_t                 cmd_lc_server_update_light_onoff;
    sl_btmesh_cmd_lc_server_init_all_properties_t                cmd_lc_server_init_all_properties;
    sl_btmesh_cmd_lc_server_set_publish_mask_t                   cmd_lc_server_set_publish_mask;
    sl_btmesh_cmd_lc_server_set_regulator_interval_t             cmd_lc_server_set_regulator_interval;
    sl_btmesh_cmd_lc_server_set_event_mask_t                     cmd_lc_server_set_event_mask;
    sl_btmesh_cmd_lc_server_get_lc_state_t                       cmd_lc_server_get_lc_state;
    sl_btmesh_cmd_lc_setup_server_update_property_t              cmd_lc_setup_server_update_property;
    sl_btmesh_cmd_scene_client_init_t                            cmd_scene_client_init;
    sl_btmesh_cmd_scene_client_get_t                             cmd_scene_client_get;
    sl_btmesh_cmd_scene_client_get_register_t                    cmd_scene_client_get_register;
    sl_btmesh_cmd_scene_client_recall_t                          cmd_scene_client_recall;
    sl_btmesh_cmd_scene_client_store_t                           cmd_scene_client_store;
    sl_btmesh_cmd_scene_client_delete_t                          cmd_scene_client_delete;
    sl_btmesh_cmd_scene_server_init_t                            cmd_scene_server_init;
    sl_btmesh_cmd_scene_server_deinit_t                          cmd_scene_server_deinit;
    sl_btmesh_cmd_scene_server_reset_register_t                  cmd_scene_server_reset_register;
    sl_btmesh_cmd_scene_setup_server_init_t                      cmd_scene_setup_server_init;
    sl_btmesh_cmd_scheduler_client_init_t                        cmd_scheduler_client_init;
    sl_btmesh_cmd_scheduler_client_deinit_t                      cmd_scheduler_client_deinit;
    sl_btmesh_cmd_scheduler_client_get_t                         cmd_scheduler_client_get;
    sl_btmesh_cmd_scheduler_client_get_action_t                  cmd_scheduler_client_get_action;
    sl_btmesh_cmd_scheduler_client_set_action_t                  cmd_scheduler_client_set_action;
    sl_btmesh_cmd_scheduler_server_init_t                        cmd_scheduler_server_init;
    sl_btmesh_cmd_scheduler_server_deinit_t                      cmd_scheduler_server_deinit;
    sl_btmesh_cmd_scheduler_server_get_t                         cmd_scheduler_server_get;
    sl_btmesh_cmd_scheduler_server_get_action_t                  cmd_scheduler_server_get_action;
    sl_btmesh_cmd_scheduler_server_set_action_t                  cmd_scheduler_server_set_action;
    sl_btmesh_cmd_time_server_init_t                             cmd_time_server_init;
    sl_btmesh_cmd_time_server_deinit_t                           cmd_time_server_deinit;
    sl_btmesh_cmd_time_server_get_time_t                         cmd_time_server_get_time;
    sl_btmesh_cmd_time_server_set_time_t                         cmd_time_server_set_time;
    sl_btmesh_cmd_time_server_get_time_zone_offset_new_t         cmd_time_server_get_time_zone_offset_new;
    sl_btmesh_cmd_time_server_set_time_zone_offset_new_t         cmd_time_server_set_time_zone_offset_new;
    sl_btmesh_cmd_time_server_get_tai_utc_delta_new_t            cmd_time_server_get_tai_utc_delta_new;
    sl_btmesh_cmd_time_server_set_tai_utc_delta_new_t            cmd_time_server_set_tai_utc_delta_new;
    sl_btmesh_cmd_time_server_get_time_role_t                    cmd_time_server_get_time_role;
    sl_btmesh_cmd_time_server_set_time_role_t                    cmd_time_server_set_time_role;
    sl_btmesh_cmd_time_server_get_datetime_t                     cmd_time_server_get_datetime;
    sl_btmesh_cmd_time_server_publish_t                          cmd_time_server_publish;
    sl_btmesh_cmd_time_server_status_t                           cmd_time_server_status;
    sl_btmesh_cmd_time_client_init_t                             cmd_time_client_init;
    sl_btmesh_cmd_time_client_deinit_t                           cmd_time_client_deinit;
    sl_btmesh_cmd_time_client_get_time_t                         cmd_time_client_get_time;
    sl_btmesh_cmd_time_client_set_time_t                         cmd_time_client_set_time;
    sl_btmesh_cmd_time_client_get_time_zone_t                    cmd_time_client_get_time_zone;
    sl_btmesh_cmd_time_client_set_time_zone_t                    cmd_time_client_set_time_zone;
    sl_btmesh_cmd_time_client_get_tai_utc_delta_t                cmd_time_client_get_tai_utc_delta;
    sl_btmesh_cmd_time_client_set_tai_utc_delta_t                cmd_time_client_set_tai_utc_delta;
    sl_btmesh_cmd_time_client_get_time_role_t                    cmd_time_client_get_time_role;
    sl_btmesh_cmd_time_client_set_time_role_t                    cmd_time_client_set_time_role;
    sl_btmesh_rsp_node_init_t                                    rsp_node_init;
    sl_btmesh_rsp_node_set_exportable_keys_t                     rsp_node_set_exportable_keys;
    sl_btmesh_rsp_node_start_unprov_beaconing_t                  rsp_node_start_unprov_beaconing;
    sl_btmesh_rsp_node_stop_unprov_beaconing_t                   rsp_node_stop_unprov_beaconing;
    sl_btmesh_rsp_node_get_rssi_t                                rsp_node_get_rssi;
    sl_btmesh_rsp_node_send_input_oob_request_response_t         rsp_node_send_input_oob_request_response;
    sl_btmesh_rsp_node_get_uuid_t                                rsp_node_get_uuid;
    sl_btmesh_rsp_node_set_provisioning_data_t                   rsp_node_set_provisioning_data;
    sl_btmesh_rsp_node_init_oob_t                                rsp_node_init_oob;
    sl_btmesh_rsp_node_set_ivrecovery_mode_t                     rsp_node_set_ivrecovery_mode;
    sl_btmesh_rsp_node_get_ivrecovery_mode_t                     rsp_node_get_ivrecovery_mode;
    sl_btmesh_rsp_node_get_statistics_t                          rsp_node_get_statistics;
    sl_btmesh_rsp_node_clear_statistics_t                        rsp_node_clear_statistics;
    sl_btmesh_rsp_node_set_net_relay_delay_t                     rsp_node_set_net_relay_delay;
    sl_btmesh_rsp_node_get_net_relay_delay_t                     rsp_node_get_net_relay_delay;
    sl_btmesh_rsp_node_get_ivupdate_state_t                      rsp_node_get_ivupdate_state;
    sl_btmesh_rsp_node_request_ivupdate_t                        rsp_node_request_ivupdate;
    sl_btmesh_rsp_node_get_seq_remaining_t                       rsp_node_get_seq_remaining;
    sl_btmesh_rsp_node_save_replay_protection_list_t             rsp_node_save_replay_protection_list;
    sl_btmesh_rsp_node_set_uuid_t                                rsp_node_set_uuid;
    sl_btmesh_rsp_node_get_replay_protection_list_status_t       rsp_node_get_replay_protection_list_status;
    sl_btmesh_rsp_node_get_element_address_t                     rsp_node_get_element_address;
    sl_btmesh_rsp_node_send_static_oob_request_response_t        rsp_node_send_static_oob_request_response;
    sl_btmesh_rsp_node_reset_t                                   rsp_node_reset;
    sl_btmesh_rsp_node_set_beacon_reporting_t                    rsp_node_set_beacon_reporting;
    sl_btmesh_rsp_node_set_iv_update_age_t                       rsp_node_set_iv_update_age;
    sl_btmesh_rsp_node_get_key_count_t                           rsp_node_get_key_count;
    sl_btmesh_rsp_node_get_key_t                                 rsp_node_get_key;
    sl_btmesh_rsp_node_get_networks_t                            rsp_node_get_networks;
    sl_btmesh_rsp_node_get_element_seqnum_t                      rsp_node_get_element_seqnum;
    sl_btmesh_rsp_node_set_model_option_t                        rsp_node_set_model_option;
    sl_btmesh_rsp_node_get_local_dcd_t                           rsp_node_get_local_dcd;
    sl_btmesh_rsp_node_erase_mesh_nvm_t                          rsp_node_erase_mesh_nvm;
    sl_btmesh_rsp_node_power_off_t                               rsp_node_power_off;
    sl_btmesh_rsp_node_set_adv_phy_t                             rsp_node_set_adv_phy;
    sl_btmesh_rsp_node_get_adv_phy_t                             rsp_node_get_adv_phy;
    sl_btmesh_rsp_prov_init_t                                    rsp_prov_init;
    sl_btmesh_rsp_prov_scan_unprov_beacons_t                     rsp_prov_scan_unprov_beacons;
    sl_btmesh_rsp_prov_create_provisioning_session_t             rsp_prov_create_provisioning_session;
    sl_btmesh_rsp_prov_set_provisioning_suspend_event_t          rsp_prov_set_provisioning_suspend_event;
    sl_btmesh_rsp_prov_provision_adv_device_t                    rsp_prov_provision_adv_device;
    sl_btmesh_rsp_prov_provision_gatt_device_t                   rsp_prov_provision_gatt_device;
    sl_btmesh_rsp_prov_continue_provisioning_t                   rsp_prov_continue_provisioning;
    sl_btmesh_rsp_prov_abort_provisioning_t                      rsp_prov_abort_provisioning;
    sl_btmesh_rsp_prov_set_device_address_t                      rsp_prov_set_device_address;
    sl_btmesh_rsp_prov_create_network_t                          rsp_prov_create_network;
    sl_btmesh_rsp_prov_create_appkey_t                           rsp_prov_create_appkey;
    sl_btmesh_rsp_prov_send_oob_pkey_response_t                  rsp_prov_send_oob_pkey_response;
    sl_btmesh_rsp_prov_send_oob_auth_response_t                  rsp_prov_send_oob_auth_response;
    sl_btmesh_rsp_prov_set_oob_requirements_t                    rsp_prov_set_oob_requirements;
    sl_btmesh_rsp_prov_start_key_refresh_t                       rsp_prov_start_key_refresh;
    sl_btmesh_rsp_prov_get_key_refresh_exclusion_t               rsp_prov_get_key_refresh_exclusion;
    sl_btmesh_rsp_prov_set_key_refresh_exclusion_t               rsp_prov_set_key_refresh_exclusion;
    sl_btmesh_rsp_prov_get_ddb_entry_t                           rsp_prov_get_ddb_entry;
    sl_btmesh_rsp_prov_delete_ddb_entry_t                        rsp_prov_delete_ddb_entry;
    sl_btmesh_rsp_prov_add_ddb_entry_t                           rsp_prov_add_ddb_entry;
    sl_btmesh_rsp_prov_list_ddb_entries_t                        rsp_prov_list_ddb_entries;
    sl_btmesh_rsp_prov_initialize_network_t                      rsp_prov_initialize_network;
    sl_btmesh_rsp_prov_get_key_refresh_appkey_exclusion_t        rsp_prov_get_key_refresh_appkey_exclusion;
    sl_btmesh_rsp_prov_set_key_refresh_appkey_exclusion_t        rsp_prov_set_key_refresh_appkey_exclusion;
    sl_btmesh_rsp_prov_stop_scan_unprov_beacons_t                rsp_prov_stop_scan_unprov_beacons;
    sl_btmesh_rsp_prov_update_device_netkey_index_t              rsp_prov_update_device_netkey_index;
    sl_btmesh_rsp_prov_suspend_key_refresh_t                     rsp_prov_suspend_key_refresh;
    sl_btmesh_rsp_prov_resume_key_refresh_t                      rsp_prov_resume_key_refresh;
    sl_btmesh_rsp_prov_get_key_refresh_phase_t                   rsp_prov_get_key_refresh_phase;
    sl_btmesh_rsp_prov_start_key_refresh_from_phase_t            rsp_prov_start_key_refresh_from_phase;
    sl_btmesh_rsp_prov_flush_key_refresh_state_t                 rsp_prov_flush_key_refresh_state;
    sl_btmesh_rsp_prov_test_identity_t                           rsp_prov_test_identity;
    sl_btmesh_rsp_proxy_connect_t                                rsp_proxy_connect;
    sl_btmesh_rsp_proxy_disconnect_t                             rsp_proxy_disconnect;
    sl_btmesh_rsp_proxy_set_filter_type_t                        rsp_proxy_set_filter_type;
    sl_btmesh_rsp_proxy_allow_t                                  rsp_proxy_allow;
    sl_btmesh_rsp_proxy_deny_t                                   rsp_proxy_deny;
    sl_btmesh_rsp_proxy_optimisation_toggle_t                    rsp_proxy_optimisation_toggle;
    sl_btmesh_rsp_vendor_model_send_t                            rsp_vendor_model_send;
    sl_btmesh_rsp_vendor_model_set_publication_t                 rsp_vendor_model_set_publication;
    sl_btmesh_rsp_vendor_model_clear_publication_t               rsp_vendor_model_clear_publication;
    sl_btmesh_rsp_vendor_model_publish_t                         rsp_vendor_model_publish;
    sl_btmesh_rsp_vendor_model_init_t                            rsp_vendor_model_init;
    sl_btmesh_rsp_vendor_model_deinit_t                          rsp_vendor_model_deinit;
    sl_btmesh_rsp_vendor_model_send_tracked_t                    rsp_vendor_model_send_tracked;
    sl_btmesh_rsp_vendor_model_set_publication_tracked_t         rsp_vendor_model_set_publication_tracked;
    sl_btmesh_rsp_health_client_get_t                            rsp_health_client_get;
    sl_btmesh_rsp_health_client_clear_t                          rsp_health_client_clear;
    sl_btmesh_rsp_health_client_test_t                           rsp_health_client_test;
    sl_btmesh_rsp_health_client_get_period_t                     rsp_health_client_get_period;
    sl_btmesh_rsp_health_client_set_period_t                     rsp_health_client_set_period;
    sl_btmesh_rsp_health_client_get_attention_t                  rsp_health_client_get_attention;
    sl_btmesh_rsp_health_client_set_attention_t                  rsp_health_client_set_attention;
    sl_btmesh_rsp_health_server_set_fault_t                      rsp_health_server_set_fault;
    sl_btmesh_rsp_health_server_clear_fault_t                    rsp_health_server_clear_fault;
    sl_btmesh_rsp_health_server_send_test_response_t             rsp_health_server_send_test_response;
    sl_btmesh_rsp_generic_client_get_t                           rsp_generic_client_get;
    sl_btmesh_rsp_generic_client_set_t                           rsp_generic_client_set;
    sl_btmesh_rsp_generic_client_publish_t                       rsp_generic_client_publish;
    sl_btmesh_rsp_generic_client_get_params_t                    rsp_generic_client_get_params;
    sl_btmesh_rsp_generic_client_init_t                          rsp_generic_client_init;
    sl_btmesh_rsp_generic_client_init_common_t                   rsp_generic_client_init_common;
    sl_btmesh_rsp_generic_client_init_on_off_t                   rsp_generic_client_init_on_off;
    sl_btmesh_rsp_generic_client_init_level_t                    rsp_generic_client_init_level;
    sl_btmesh_rsp_generic_client_init_default_transition_time_t  rsp_generic_client_init_default_transition_time;
    sl_btmesh_rsp_generic_client_init_power_on_off_t             rsp_generic_client_init_power_on_off;
    sl_btmesh_rsp_generic_client_init_power_level_t              rsp_generic_client_init_power_level;
    sl_btmesh_rsp_generic_client_init_battery_t                  rsp_generic_client_init_battery;
    sl_btmesh_rsp_generic_client_init_location_t                 rsp_generic_client_init_location;
    sl_btmesh_rsp_generic_client_init_property_t                 rsp_generic_client_init_property;
    sl_btmesh_rsp_generic_client_init_lightness_t                rsp_generic_client_init_lightness;
    sl_btmesh_rsp_generic_client_init_ctl_t                      rsp_generic_client_init_ctl;
    sl_btmesh_rsp_generic_client_init_hsl_t                      rsp_generic_client_init_hsl;
    sl_btmesh_rsp_generic_server_respond_t                       rsp_generic_server_respond;
    sl_btmesh_rsp_generic_server_update_t                        rsp_generic_server_update;
    sl_btmesh_rsp_generic_server_publish_t                       rsp_generic_server_publish;
    sl_btmesh_rsp_generic_server_init_t                          rsp_generic_server_init;
    sl_btmesh_rsp_generic_server_init_common_t                   rsp_generic_server_init_common;
    sl_btmesh_rsp_generic_server_init_on_off_t                   rsp_generic_server_init_on_off;
    sl_btmesh_rsp_generic_server_init_level_t                    rsp_generic_server_init_level;
    sl_btmesh_rsp_generic_server_init_default_transition_time_t  rsp_generic_server_init_default_transition_time;
    sl_btmesh_rsp_generic_server_init_power_on_off_t             rsp_generic_server_init_power_on_off;
    sl_btmesh_rsp_generic_server_init_power_level_t              rsp_generic_server_init_power_level;
    sl_btmesh_rsp_generic_server_init_battery_t                  rsp_generic_server_init_battery;
    sl_btmesh_rsp_generic_server_init_location_t                 rsp_generic_server_init_location;
    sl_btmesh_rsp_generic_server_init_property_t                 rsp_generic_server_init_property;
    sl_btmesh_rsp_generic_server_init_lightness_t                rsp_generic_server_init_lightness;
    sl_btmesh_rsp_generic_server_init_ctl_t                      rsp_generic_server_init_ctl;
    sl_btmesh_rsp_generic_server_init_hsl_t                      rsp_generic_server_init_hsl;
    sl_btmesh_rsp_generic_server_get_cached_state_t              rsp_generic_server_get_cached_state;
    sl_btmesh_rsp_test_get_nettx_t                               rsp_test_get_nettx;
    sl_btmesh_rsp_test_set_nettx_t                               rsp_test_set_nettx;
    sl_btmesh_rsp_test_get_relay_t                               rsp_test_get_relay;
    sl_btmesh_rsp_test_set_relay_t                               rsp_test_set_relay;
    sl_btmesh_rsp_test_set_adv_scan_params_t                     rsp_test_set_adv_scan_params;
    sl_btmesh_rsp_test_set_ivupdate_test_mode_t                  rsp_test_set_ivupdate_test_mode;
    sl_btmesh_rsp_test_get_ivupdate_test_mode_t                  rsp_test_get_ivupdate_test_mode;
    sl_btmesh_rsp_test_set_segment_send_delay_t                  rsp_test_set_segment_send_delay;
    sl_btmesh_rsp_test_set_ivupdate_state_t                      rsp_test_set_ivupdate_state;
    sl_btmesh_rsp_test_send_beacons_t                            rsp_test_send_beacons;
    sl_btmesh_rsp_test_bind_local_model_app_t                    rsp_test_bind_local_model_app;
    sl_btmesh_rsp_test_unbind_local_model_app_t                  rsp_test_unbind_local_model_app;
    sl_btmesh_rsp_test_add_local_model_sub_t                     rsp_test_add_local_model_sub;
    sl_btmesh_rsp_test_remove_local_model_sub_t                  rsp_test_remove_local_model_sub;
    sl_btmesh_rsp_test_add_local_model_sub_va_t                  rsp_test_add_local_model_sub_va;
    sl_btmesh_rsp_test_remove_local_model_sub_va_t               rsp_test_remove_local_model_sub_va;
    sl_btmesh_rsp_test_get_local_model_sub_t                     rsp_test_get_local_model_sub;
    sl_btmesh_rsp_test_set_local_model_pub_t                     rsp_test_set_local_model_pub;
    sl_btmesh_rsp_test_set_local_model_pub_va_t                  rsp_test_set_local_model_pub_va;
    sl_btmesh_rsp_test_get_local_model_pub_t                     rsp_test_get_local_model_pub;
    sl_btmesh_rsp_test_set_local_heartbeat_subscription_t        rsp_test_set_local_heartbeat_subscription;
    sl_btmesh_rsp_test_get_local_heartbeat_subscription_t        rsp_test_get_local_heartbeat_subscription;
    sl_btmesh_rsp_test_get_local_heartbeat_publication_t         rsp_test_get_local_heartbeat_publication;
    sl_btmesh_rsp_test_set_local_heartbeat_publication_t         rsp_test_set_local_heartbeat_publication;
    sl_btmesh_rsp_test_set_local_config_t                        rsp_test_set_local_config;
    sl_btmesh_rsp_test_get_local_config_t                        rsp_test_get_local_config;
    sl_btmesh_rsp_test_add_local_key_t                           rsp_test_add_local_key;
    sl_btmesh_rsp_test_remove_local_key_t                        rsp_test_remove_local_key;
    sl_btmesh_rsp_test_update_local_key_t                        rsp_test_update_local_key;
    sl_btmesh_rsp_test_set_sar_config_t                          rsp_test_set_sar_config;
    sl_btmesh_rsp_test_set_adv_bearer_state_t                    rsp_test_set_adv_bearer_state;
    sl_btmesh_rsp_test_prov_get_device_key_t                     rsp_test_prov_get_device_key;
    sl_btmesh_rsp_test_prov_prepare_key_refresh_t                rsp_test_prov_prepare_key_refresh;
    sl_btmesh_rsp_test_cancel_segmented_tx_t                     rsp_test_cancel_segmented_tx;
    sl_btmesh_rsp_test_set_iv_index_t                            rsp_test_set_iv_index;
    sl_btmesh_rsp_test_set_element_seqnum_t                      rsp_test_set_element_seqnum;
    sl_btmesh_rsp_test_set_model_option_t                        rsp_test_set_model_option;
    sl_btmesh_rsp_test_get_local_model_app_bindings_t            rsp_test_get_local_model_app_bindings;
    sl_btmesh_rsp_test_get_replay_protection_list_entry_t        rsp_test_get_replay_protection_list_entry;
    sl_btmesh_rsp_test_clear_replay_protection_list_entry_t      rsp_test_clear_replay_protection_list_entry;
    sl_btmesh_rsp_test_set_replay_protection_list_diagnostics_t  rsp_test_set_replay_protection_list_diagnostics;
    sl_btmesh_rsp_test_get_model_option_t                        rsp_test_get_model_option;
    sl_btmesh_rsp_test_get_default_ttl_t                         rsp_test_get_default_ttl;
    sl_btmesh_rsp_test_set_default_ttl_t                         rsp_test_set_default_ttl;
    sl_btmesh_rsp_test_get_gatt_proxy_t                          rsp_test_get_gatt_proxy;
    sl_btmesh_rsp_test_set_gatt_proxy_t                          rsp_test_set_gatt_proxy;
    sl_btmesh_rsp_test_get_identity_t                            rsp_test_get_identity;
    sl_btmesh_rsp_test_set_identity_t                            rsp_test_set_identity;
    sl_btmesh_rsp_test_get_friend_t                              rsp_test_get_friend;
    sl_btmesh_rsp_test_set_friend_t                              rsp_test_set_friend;
    sl_btmesh_rsp_test_get_beacon_t                              rsp_test_get_beacon;
    sl_btmesh_rsp_test_set_beacon_t                              rsp_test_set_beacon;
    sl_btmesh_rsp_lpn_init_t                                     rsp_lpn_init;
    sl_btmesh_rsp_lpn_deinit_t                                   rsp_lpn_deinit;
    sl_btmesh_rsp_lpn_establish_friendship_t                     rsp_lpn_establish_friendship;
    sl_btmesh_rsp_lpn_poll_t                                     rsp_lpn_poll;
    sl_btmesh_rsp_lpn_terminate_friendship_t                     rsp_lpn_terminate_friendship;
    sl_btmesh_rsp_lpn_config_t                                   rsp_lpn_config;
    sl_btmesh_rsp_friend_init_t                                  rsp_friend_init;
    sl_btmesh_rsp_friend_deinit_t                                rsp_friend_deinit;
    sl_btmesh_rsp_config_client_cancel_request_t                 rsp_config_client_cancel_request;
    sl_btmesh_rsp_config_client_get_request_status_t             rsp_config_client_get_request_status;
    sl_btmesh_rsp_config_client_get_default_timeout_t            rsp_config_client_get_default_timeout;
    sl_btmesh_rsp_config_client_set_default_timeout_t            rsp_config_client_set_default_timeout;
    sl_btmesh_rsp_config_client_add_netkey_t                     rsp_config_client_add_netkey;
    sl_btmesh_rsp_config_client_remove_netkey_t                  rsp_config_client_remove_netkey;
    sl_btmesh_rsp_config_client_list_netkeys_t                   rsp_config_client_list_netkeys;
    sl_btmesh_rsp_config_client_add_appkey_t                     rsp_config_client_add_appkey;
    sl_btmesh_rsp_config_client_remove_appkey_t                  rsp_config_client_remove_appkey;
    sl_btmesh_rsp_config_client_list_appkeys_t                   rsp_config_client_list_appkeys;
    sl_btmesh_rsp_config_client_bind_model_t                     rsp_config_client_bind_model;
    sl_btmesh_rsp_config_client_unbind_model_t                   rsp_config_client_unbind_model;
    sl_btmesh_rsp_config_client_list_bindings_t                  rsp_config_client_list_bindings;
    sl_btmesh_rsp_config_client_get_model_pub_t                  rsp_config_client_get_model_pub;
    sl_btmesh_rsp_config_client_set_model_pub_t                  rsp_config_client_set_model_pub;
    sl_btmesh_rsp_config_client_set_model_pub_va_t               rsp_config_client_set_model_pub_va;
    sl_btmesh_rsp_config_client_add_model_sub_t                  rsp_config_client_add_model_sub;
    sl_btmesh_rsp_config_client_add_model_sub_va_t               rsp_config_client_add_model_sub_va;
    sl_btmesh_rsp_config_client_remove_model_sub_t               rsp_config_client_remove_model_sub;
    sl_btmesh_rsp_config_client_remove_model_sub_va_t            rsp_config_client_remove_model_sub_va;
    sl_btmesh_rsp_config_client_set_model_sub_t                  rsp_config_client_set_model_sub;
    sl_btmesh_rsp_config_client_set_model_sub_va_t               rsp_config_client_set_model_sub_va;
    sl_btmesh_rsp_config_client_clear_model_sub_t                rsp_config_client_clear_model_sub;
    sl_btmesh_rsp_config_client_list_subs_t                      rsp_config_client_list_subs;
    sl_btmesh_rsp_config_client_get_heartbeat_pub_t              rsp_config_client_get_heartbeat_pub;
    sl_btmesh_rsp_config_client_set_heartbeat_pub_t              rsp_config_client_set_heartbeat_pub;
    sl_btmesh_rsp_config_client_get_heartbeat_sub_t              rsp_config_client_get_heartbeat_sub;
    sl_btmesh_rsp_config_client_set_heartbeat_sub_t              rsp_config_client_set_heartbeat_sub;
    sl_btmesh_rsp_config_client_get_beacon_t                     rsp_config_client_get_beacon;
    sl_btmesh_rsp_config_client_set_beacon_t                     rsp_config_client_set_beacon;
    sl_btmesh_rsp_config_client_get_default_ttl_t                rsp_config_client_get_default_ttl;
    sl_btmesh_rsp_config_client_set_default_ttl_t                rsp_config_client_set_default_ttl;
    sl_btmesh_rsp_config_client_get_gatt_proxy_t                 rsp_config_client_get_gatt_proxy;
    sl_btmesh_rsp_config_client_set_gatt_proxy_t                 rsp_config_client_set_gatt_proxy;
    sl_btmesh_rsp_config_client_get_relay_t                      rsp_config_client_get_relay;
    sl_btmesh_rsp_config_client_set_relay_t                      rsp_config_client_set_relay;
    sl_btmesh_rsp_config_client_get_network_transmit_t           rsp_config_client_get_network_transmit;
    sl_btmesh_rsp_config_client_set_network_transmit_t           rsp_config_client_set_network_transmit;
    sl_btmesh_rsp_config_client_get_identity_t                   rsp_config_client_get_identity;
    sl_btmesh_rsp_config_client_set_identity_t                   rsp_config_client_set_identity;
    sl_btmesh_rsp_config_client_get_friend_t                     rsp_config_client_get_friend;
    sl_btmesh_rsp_config_client_set_friend_t                     rsp_config_client_set_friend;
    sl_btmesh_rsp_config_client_get_key_refresh_phase_t          rsp_config_client_get_key_refresh_phase;
    sl_btmesh_rsp_config_client_get_lpn_polltimeout_t            rsp_config_client_get_lpn_polltimeout;
    sl_btmesh_rsp_config_client_get_dcd_t                        rsp_config_client_get_dcd;
    sl_btmesh_rsp_config_client_reset_node_t                     rsp_config_client_reset_node;
    sl_btmesh_rsp_sensor_server_init_t                           rsp_sensor_server_init;
    sl_btmesh_rsp_sensor_server_deinit_t                         rsp_sensor_server_deinit;
    sl_btmesh_rsp_sensor_server_send_descriptor_status_t         rsp_sensor_server_send_descriptor_status;
    sl_btmesh_rsp_sensor_server_send_status_t                    rsp_sensor_server_send_status;
    sl_btmesh_rsp_sensor_server_send_column_status_t             rsp_sensor_server_send_column_status;
    sl_btmesh_rsp_sensor_server_send_series_status_t             rsp_sensor_server_send_series_status;
    sl_btmesh_rsp_sensor_setup_server_send_cadence_status_t      rsp_sensor_setup_server_send_cadence_status;
    sl_btmesh_rsp_sensor_setup_server_send_settings_status_t     rsp_sensor_setup_server_send_settings_status;
    sl_btmesh_rsp_sensor_setup_server_send_setting_status_t      rsp_sensor_setup_server_send_setting_status;
    sl_btmesh_rsp_sensor_client_init_t                           rsp_sensor_client_init;
    sl_btmesh_rsp_sensor_client_deinit_t                         rsp_sensor_client_deinit;
    sl_btmesh_rsp_sensor_client_get_descriptor_t                 rsp_sensor_client_get_descriptor;
    sl_btmesh_rsp_sensor_client_get_t                            rsp_sensor_client_get;
    sl_btmesh_rsp_sensor_client_get_column_t                     rsp_sensor_client_get_column;
    sl_btmesh_rsp_sensor_client_get_series_t                     rsp_sensor_client_get_series;
    sl_btmesh_rsp_sensor_client_get_cadence_t                    rsp_sensor_client_get_cadence;
    sl_btmesh_rsp_sensor_client_set_cadence_t                    rsp_sensor_client_set_cadence;
    sl_btmesh_rsp_sensor_client_get_settings_t                   rsp_sensor_client_get_settings;
    sl_btmesh_rsp_sensor_client_get_setting_t                    rsp_sensor_client_get_setting;
    sl_btmesh_rsp_sensor_client_set_setting_t                    rsp_sensor_client_set_setting;
    sl_btmesh_rsp_lc_client_init_t                               rsp_lc_client_init;
    sl_btmesh_rsp_lc_client_get_mode_t                           rsp_lc_client_get_mode;
    sl_btmesh_rsp_lc_client_set_mode_t                           rsp_lc_client_set_mode;
    sl_btmesh_rsp_lc_client_get_om_t                             rsp_lc_client_get_om;
    sl_btmesh_rsp_lc_client_set_om_t                             rsp_lc_client_set_om;
    sl_btmesh_rsp_lc_client_get_light_onoff_t                    rsp_lc_client_get_light_onoff;
    sl_btmesh_rsp_lc_client_set_light_onoff_t                    rsp_lc_client_set_light_onoff;
    sl_btmesh_rsp_lc_client_get_property_t                       rsp_lc_client_get_property;
    sl_btmesh_rsp_lc_client_set_property_t                       rsp_lc_client_set_property;
    sl_btmesh_rsp_lc_server_init_t                               rsp_lc_server_init;
    sl_btmesh_rsp_lc_server_deinit_t                             rsp_lc_server_deinit;
    sl_btmesh_rsp_lc_server_update_mode_t                        rsp_lc_server_update_mode;
    sl_btmesh_rsp_lc_server_update_om_t                          rsp_lc_server_update_om;
    sl_btmesh_rsp_lc_server_update_light_onoff_t                 rsp_lc_server_update_light_onoff;
    sl_btmesh_rsp_lc_server_init_all_properties_t                rsp_lc_server_init_all_properties;
    sl_btmesh_rsp_lc_server_set_publish_mask_t                   rsp_lc_server_set_publish_mask;
    sl_btmesh_rsp_lc_server_set_regulator_interval_t             rsp_lc_server_set_regulator_interval;
    sl_btmesh_rsp_lc_server_set_event_mask_t                     rsp_lc_server_set_event_mask;
    sl_btmesh_rsp_lc_server_get_lc_state_t                       rsp_lc_server_get_lc_state;
    sl_btmesh_rsp_lc_setup_server_update_property_t              rsp_lc_setup_server_update_property;
    sl_btmesh_rsp_scene_client_init_t                            rsp_scene_client_init;
    sl_btmesh_rsp_scene_client_get_t                             rsp_scene_client_get;
    sl_btmesh_rsp_scene_client_get_register_t                    rsp_scene_client_get_register;
    sl_btmesh_rsp_scene_client_recall_t                          rsp_scene_client_recall;
    sl_btmesh_rsp_scene_client_store_t                           rsp_scene_client_store;
    sl_btmesh_rsp_scene_client_delete_t                          rsp_scene_client_delete;
    sl_btmesh_rsp_scene_server_init_t                            rsp_scene_server_init;
    sl_btmesh_rsp_scene_server_deinit_t                          rsp_scene_server_deinit;
    sl_btmesh_rsp_scene_server_reset_register_t                  rsp_scene_server_reset_register;
    sl_btmesh_rsp_scene_server_enable_compact_recall_events_t    rsp_scene_server_enable_compact_recall_events;
    sl_btmesh_rsp_scene_setup_server_init_t                      rsp_scene_setup_server_init;
    sl_btmesh_rsp_scheduler_client_init_t                        rsp_scheduler_client_init;
    sl_btmesh_rsp_scheduler_client_deinit_t                      rsp_scheduler_client_deinit;
    sl_btmesh_rsp_scheduler_client_get_t                         rsp_scheduler_client_get;
    sl_btmesh_rsp_scheduler_client_get_action_t                  rsp_scheduler_client_get_action;
    sl_btmesh_rsp_scheduler_client_set_action_t                  rsp_scheduler_client_set_action;
    sl_btmesh_rsp_scheduler_server_init_t                        rsp_scheduler_server_init;
    sl_btmesh_rsp_scheduler_server_deinit_t                      rsp_scheduler_server_deinit;
    sl_btmesh_rsp_scheduler_server_get_t                         rsp_scheduler_server_get;
    sl_btmesh_rsp_scheduler_server_get_action_t                  rsp_scheduler_server_get_action;
    sl_btmesh_rsp_scheduler_server_set_action_t                  rsp_scheduler_server_set_action;
    sl_btmesh_rsp_time_server_init_t                             rsp_time_server_init;
    sl_btmesh_rsp_time_server_deinit_t                           rsp_time_server_deinit;
    sl_btmesh_rsp_time_server_get_time_t                         rsp_time_server_get_time;
    sl_btmesh_rsp_time_server_set_time_t                         rsp_time_server_set_time;
    sl_btmesh_rsp_time_server_get_time_zone_offset_new_t         rsp_time_server_get_time_zone_offset_new;
    sl_btmesh_rsp_time_server_set_time_zone_offset_new_t         rsp_time_server_set_time_zone_offset_new;
    sl_btmesh_rsp_time_server_get_tai_utc_delta_new_t            rsp_time_server_get_tai_utc_delta_new;
    sl_btmesh_rsp_time_server_set_tai_utc_delta_new_t            rsp_time_server_set_tai_utc_delta_new;
    sl_btmesh_rsp_time_server_get_time_role_t                    rsp_time_server_get_time_role;
    sl_btmesh_rsp_time_server_set_time_role_t                    rsp_time_server_set_time_role;
    sl_btmesh_rsp_time_server_get_datetime_t                     rsp_time_server_get_datetime;
    sl_btmesh_rsp_time_server_publish_t                          rsp_time_server_publish;
    sl_btmesh_rsp_time_server_status_t                           rsp_time_server_status;
    sl_btmesh_rsp_time_client_init_t                             rsp_time_client_init;
    sl_btmesh_rsp_time_client_deinit_t                           rsp_time_client_deinit;
    sl_btmesh_rsp_time_client_get_time_t                         rsp_time_client_get_time;
    sl_btmesh_rsp_time_client_set_time_t                         rsp_time_client_set_time;
    sl_btmesh_rsp_time_client_get_time_zone_t                    rsp_time_client_get_time_zone;
    sl_btmesh_rsp_time_client_set_time_zone_t                    rsp_time_client_set_time_zone;
    sl_btmesh_rsp_time_client_get_tai_utc_delta_t                rsp_time_client_get_tai_utc_delta;
    sl_btmesh_rsp_time_client_set_tai_utc_delta_t                rsp_time_client_set_tai_utc_delta;
    sl_btmesh_rsp_time_client_get_time_role_t                    rsp_time_client_get_time_role;
    sl_btmesh_rsp_time_client_set_time_role_t                    rsp_time_client_set_time_role;
    sl_btmesh_rsp_migration_migrate_keys_t                       rsp_migration_migrate_keys;
    sl_btmesh_rsp_migration_migrate_ddb_t                        rsp_migration_migrate_ddb;
    sl_btmesh_evt_node_initialized_t                             evt_node_initialized;
    sl_btmesh_evt_node_provisioned_t                             evt_node_provisioned;
    sl_btmesh_evt_node_config_get_t                              evt_node_config_get;
    sl_btmesh_evt_node_config_set_t                              evt_node_config_set;
    sl_btmesh_evt_node_display_output_oob_t                      evt_node_display_output_oob;
    sl_btmesh_evt_node_input_oob_request_t                       evt_node_input_oob_request;
    sl_btmesh_evt_node_provisioning_started_t                    evt_node_provisioning_started;
    sl_btmesh_evt_node_provisioning_failed_t                     evt_node_provisioning_failed;
    sl_btmesh_evt_node_key_added_t                               evt_node_key_added;
    sl_btmesh_evt_node_model_config_changed_t                    evt_node_model_config_changed;
    sl_btmesh_evt_node_ivrecovery_needed_t                       evt_node_ivrecovery_needed;
    sl_btmesh_evt_node_changed_ivupdate_state_t                  evt_node_changed_ivupdate_state;
    sl_btmesh_evt_node_key_removed_t                             evt_node_key_removed;
    sl_btmesh_evt_node_key_updated_t                             evt_node_key_updated;
    sl_btmesh_evt_node_heartbeat_t                               evt_node_heartbeat;
    sl_btmesh_evt_node_heartbeat_start_t                         evt_node_heartbeat_start;
    sl_btmesh_evt_node_heartbeat_stop_t                          evt_node_heartbeat_stop;
    sl_btmesh_evt_node_beacon_received_t                         evt_node_beacon_received;
    sl_btmesh_evt_node_local_dcd_data_t                          evt_node_local_dcd_data;
    sl_btmesh_evt_node_local_dcd_data_end_t                      evt_node_local_dcd_data_end;
    sl_btmesh_evt_node_start_received_t                          evt_node_start_received;
    sl_btmesh_evt_prov_initialized_t                             evt_prov_initialized;
    sl_btmesh_evt_prov_provisioning_suspended_t                  evt_prov_provisioning_suspended;
    sl_btmesh_evt_prov_capabilities_t                            evt_prov_capabilities;
    sl_btmesh_evt_prov_provisioning_failed_t                     evt_prov_provisioning_failed;
    sl_btmesh_evt_prov_device_provisioned_t                      evt_prov_device_provisioned;
    sl_btmesh_evt_prov_unprov_beacon_t                           evt_prov_unprov_beacon;
    sl_btmesh_evt_prov_oob_pkey_request_t                        evt_prov_oob_pkey_request;
    sl_btmesh_evt_prov_oob_auth_request_t                        evt_prov_oob_auth_request;
    sl_btmesh_evt_prov_oob_display_input_t                       evt_prov_oob_display_input;
    sl_btmesh_evt_prov_ddb_list_t                                evt_prov_ddb_list;
    sl_btmesh_evt_prov_uri_t                                     evt_prov_uri;
    sl_btmesh_evt_prov_key_refresh_phase_update_t                evt_prov_key_refresh_phase_update;
    sl_btmesh_evt_prov_key_refresh_node_update_t                 evt_prov_key_refresh_node_update;
    sl_btmesh_evt_prov_key_refresh_complete_t                    evt_prov_key_refresh_complete;
    sl_btmesh_evt_prov_add_ddb_entry_complete_t                  evt_prov_add_ddb_entry_complete;
    sl_btmesh_evt_prov_delete_ddb_entry_complete_t               evt_prov_delete_ddb_entry_complete;
    sl_btmesh_evt_prov_initialization_failed_t                   evt_prov_initialization_failed;
    sl_btmesh_evt_prov_start_sent_t                              evt_prov_start_sent;
    sl_btmesh_evt_proxy_connected_t                              evt_proxy_connected;
    sl_btmesh_evt_proxy_disconnected_t                           evt_proxy_disconnected;
    sl_btmesh_evt_proxy_filter_status_t                          evt_proxy_filter_status;
    sl_btmesh_evt_vendor_model_receive_t                         evt_vendor_model_receive;
    sl_btmesh_evt_vendor_model_send_complete_t                   evt_vendor_model_send_complete;
    sl_btmesh_evt_health_client_server_status_t                  evt_health_client_server_status;
    sl_btmesh_evt_health_client_server_status_period_t           evt_health_client_server_status_period;
    sl_btmesh_evt_health_client_server_status_attention_t        evt_health_client_server_status_attention;
    sl_btmesh_evt_health_server_attention_t                      evt_health_server_attention;
    sl_btmesh_evt_health_server_test_request_t                   evt_health_server_test_request;
    sl_btmesh_evt_generic_client_server_status_t                 evt_generic_client_server_status;
    sl_btmesh_evt_generic_server_client_request_t                evt_generic_server_client_request;
    sl_btmesh_evt_generic_server_state_changed_t                 evt_generic_server_state_changed;
    sl_btmesh_evt_generic_server_state_recall_t                  evt_generic_server_state_recall;
    sl_btmesh_evt_test_local_heartbeat_subscription_complete_t   evt_test_local_heartbeat_subscription_complete;
    sl_btmesh_evt_test_replay_protection_list_entry_set_t        evt_test_replay_protection_list_entry_set;
    sl_btmesh_evt_test_replay_protection_list_entry_cleared_t    evt_test_replay_protection_list_entry_cleared;
    sl_btmesh_evt_test_replay_protection_list_saved_t            evt_test_replay_protection_list_saved;
    sl_btmesh_evt_lpn_friendship_established_t                   evt_lpn_friendship_established;
    sl_btmesh_evt_lpn_friendship_failed_t                        evt_lpn_friendship_failed;
    sl_btmesh_evt_lpn_friendship_terminated_t                    evt_lpn_friendship_terminated;
    sl_btmesh_evt_friend_friendship_established_t                evt_friend_friendship_established;
    sl_btmesh_evt_friend_friendship_terminated_t                 evt_friend_friendship_terminated;
    sl_btmesh_evt_config_client_request_modified_t               evt_config_client_request_modified;
    sl_btmesh_evt_config_client_netkey_status_t                  evt_config_client_netkey_status;
    sl_btmesh_evt_config_client_netkey_list_t                    evt_config_client_netkey_list;
    sl_btmesh_evt_config_client_netkey_list_end_t                evt_config_client_netkey_list_end;
    sl_btmesh_evt_config_client_appkey_status_t                  evt_config_client_appkey_status;
    sl_btmesh_evt_config_client_appkey_list_t                    evt_config_client_appkey_list;
    sl_btmesh_evt_config_client_appkey_list_end_t                evt_config_client_appkey_list_end;
    sl_btmesh_evt_config_client_binding_status_t                 evt_config_client_binding_status;
    sl_btmesh_evt_config_client_bindings_list_t                  evt_config_client_bindings_list;
    sl_btmesh_evt_config_client_bindings_list_end_t              evt_config_client_bindings_list_end;
    sl_btmesh_evt_config_client_model_pub_status_t               evt_config_client_model_pub_status;
    sl_btmesh_evt_config_client_model_sub_status_t               evt_config_client_model_sub_status;
    sl_btmesh_evt_config_client_subs_list_t                      evt_config_client_subs_list;
    sl_btmesh_evt_config_client_subs_list_end_t                  evt_config_client_subs_list_end;
    sl_btmesh_evt_config_client_heartbeat_pub_status_t           evt_config_client_heartbeat_pub_status;
    sl_btmesh_evt_config_client_heartbeat_sub_status_t           evt_config_client_heartbeat_sub_status;
    sl_btmesh_evt_config_client_beacon_status_t                  evt_config_client_beacon_status;
    sl_btmesh_evt_config_client_default_ttl_status_t             evt_config_client_default_ttl_status;
    sl_btmesh_evt_config_client_gatt_proxy_status_t              evt_config_client_gatt_proxy_status;
    sl_btmesh_evt_config_client_relay_status_t                   evt_config_client_relay_status;
    sl_btmesh_evt_config_client_network_transmit_status_t        evt_config_client_network_transmit_status;
    sl_btmesh_evt_config_client_identity_status_t                evt_config_client_identity_status;
    sl_btmesh_evt_config_client_friend_status_t                  evt_config_client_friend_status;
    sl_btmesh_evt_config_client_key_refresh_phase_status_t       evt_config_client_key_refresh_phase_status;
    sl_btmesh_evt_config_client_lpn_polltimeout_status_t         evt_config_client_lpn_polltimeout_status;
    sl_btmesh_evt_config_client_dcd_data_t                       evt_config_client_dcd_data;
    sl_btmesh_evt_config_client_dcd_data_end_t                   evt_config_client_dcd_data_end;
    sl_btmesh_evt_config_client_reset_status_t                   evt_config_client_reset_status;
    sl_btmesh_evt_sensor_server_get_request_t                    evt_sensor_server_get_request;
    sl_btmesh_evt_sensor_server_get_column_request_t             evt_sensor_server_get_column_request;
    sl_btmesh_evt_sensor_server_get_series_request_t             evt_sensor_server_get_series_request;
    sl_btmesh_evt_sensor_server_publish_t                        evt_sensor_server_publish;
    sl_btmesh_evt_sensor_setup_server_get_cadence_request_t      evt_sensor_setup_server_get_cadence_request;
    sl_btmesh_evt_sensor_setup_server_set_cadence_request_t      evt_sensor_setup_server_set_cadence_request;
    sl_btmesh_evt_sensor_setup_server_get_settings_request_t     evt_sensor_setup_server_get_settings_request;
    sl_btmesh_evt_sensor_setup_server_get_setting_request_t      evt_sensor_setup_server_get_setting_request;
    sl_btmesh_evt_sensor_setup_server_set_setting_request_t      evt_sensor_setup_server_set_setting_request;
    sl_btmesh_evt_sensor_setup_server_publish_t                  evt_sensor_setup_server_publish;
    sl_btmesh_evt_sensor_client_descriptor_status_t              evt_sensor_client_descriptor_status;
    sl_btmesh_evt_sensor_client_cadence_status_t                 evt_sensor_client_cadence_status;
    sl_btmesh_evt_sensor_client_settings_status_t                evt_sensor_client_settings_status;
    sl_btmesh_evt_sensor_client_setting_status_t                 evt_sensor_client_setting_status;
    sl_btmesh_evt_sensor_client_status_t                         evt_sensor_client_status;
    sl_btmesh_evt_sensor_client_column_status_t                  evt_sensor_client_column_status;
    sl_btmesh_evt_sensor_client_series_status_t                  evt_sensor_client_series_status;
    sl_btmesh_evt_sensor_client_publish_t                        evt_sensor_client_publish;
    sl_btmesh_evt_lc_client_mode_status_t                        evt_lc_client_mode_status;
    sl_btmesh_evt_lc_client_om_status_t                          evt_lc_client_om_status;
    sl_btmesh_evt_lc_client_light_onoff_status_t                 evt_lc_client_light_onoff_status;
    sl_btmesh_evt_lc_client_property_status_t                    evt_lc_client_property_status;
    sl_btmesh_evt_lc_server_mode_updated_t                       evt_lc_server_mode_updated;
    sl_btmesh_evt_lc_server_om_updated_t                         evt_lc_server_om_updated;
    sl_btmesh_evt_lc_server_light_onoff_updated_t                evt_lc_server_light_onoff_updated;
    sl_btmesh_evt_lc_server_occupancy_updated_t                  evt_lc_server_occupancy_updated;
    sl_btmesh_evt_lc_server_ambient_lux_level_updated_t          evt_lc_server_ambient_lux_level_updated;
    sl_btmesh_evt_lc_server_linear_output_updated_t              evt_lc_server_linear_output_updated;
    sl_btmesh_evt_lc_server_state_updated_t                      evt_lc_server_state_updated;
    sl_btmesh_evt_lc_server_regulator_debug_info_t               evt_lc_server_regulator_debug_info;
    sl_btmesh_evt_lc_setup_server_set_property_t                 evt_lc_setup_server_set_property;
    sl_btmesh_evt_scene_client_status_t                          evt_scene_client_status;
    sl_btmesh_evt_scene_client_register_status_t                 evt_scene_client_register_status;
    sl_btmesh_evt_scene_server_get_t                             evt_scene_server_get;
    sl_btmesh_evt_scene_server_register_get_t                    evt_scene_server_register_get;
    sl_btmesh_evt_scene_server_recall_t                          evt_scene_server_recall;
    sl_btmesh_evt_scene_server_publish_t                         evt_scene_server_publish;
    sl_btmesh_evt_scene_server_compact_recall_t                  evt_scene_server_compact_recall;
    sl_btmesh_evt_scene_setup_server_store_t                     evt_scene_setup_server_store;
    sl_btmesh_evt_scene_setup_server_delete_t                    evt_scene_setup_server_delete;
    sl_btmesh_evt_scene_setup_server_publish_t                   evt_scene_setup_server_publish;
    sl_btmesh_evt_scheduler_client_status_t                      evt_scheduler_client_status;
    sl_btmesh_evt_scheduler_client_action_status_t               evt_scheduler_client_action_status;
    sl_btmesh_evt_scheduler_server_action_changed_t              evt_scheduler_server_action_changed;
    sl_btmesh_evt_scheduler_server_scene_changed_t               evt_scheduler_server_scene_changed;
    sl_btmesh_evt_time_server_time_updated_t                     evt_time_server_time_updated;
    sl_btmesh_evt_time_server_time_zone_offset_updated_t         evt_time_server_time_zone_offset_updated;
    sl_btmesh_evt_time_server_tai_utc_delta_updated_t            evt_time_server_tai_utc_delta_updated;
    sl_btmesh_evt_time_server_time_role_updated_t                evt_time_server_time_role_updated;
    sl_btmesh_evt_time_client_time_status_t                      evt_time_client_time_status;
    sl_btmesh_evt_time_client_time_zone_status_t                 evt_time_client_time_zone_status;
    sl_btmesh_evt_time_client_tai_utc_delta_status_t             evt_time_client_tai_utc_delta_status;
    sl_btmesh_evt_time_client_time_role_status_t                 evt_time_client_time_role_status;
    uint8_t payload[SL_BGAPI_MAX_PAYLOAD_SIZE];
  } data;
});

#ifdef __cplusplus
}
#endif

#endif