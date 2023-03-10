/***************************************************************************//**
 * @brief SL_BT_API commands for NCP host
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "sl_btmesh_api.h"
#include "sli_btmesh_api.h"

void sl_btmesh_host_handle_command();
void sl_btmesh_host_handle_command_noresponse();
extern sl_btmesh_msg_t *sl_btmesh_cmd_msg;
extern sl_btmesh_msg_t *sl_btmesh_rsp_msg;

sl_status_t sl_btmesh_node_init() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_node_init_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_node_init.result;

}

sl_status_t sl_btmesh_node_set_exportable_keys() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_node_set_exportable_keys_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_node_set_exportable_keys.result;

}

sl_status_t sl_btmesh_node_start_unprov_beaconing(uint8_t bearer) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_node_start_unprov_beaconing.bearer=bearer;

    cmd->header=sl_btmesh_cmd_node_start_unprov_beaconing_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_node_start_unprov_beaconing.result;

}

sl_status_t sl_btmesh_node_stop_unprov_beaconing() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_node_stop_unprov_beaconing_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_node_stop_unprov_beaconing.result;

}

sl_status_t sl_btmesh_node_get_rssi(int8_t *rssi) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_node_get_rssi_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (rssi) {
        *rssi = rsp->data.rsp_node_get_rssi.rssi;
    }
    return rsp->data.rsp_node_get_rssi.result;

}

sl_status_t sl_btmesh_node_send_input_oob_request_response(size_t data_len,
                                                           const uint8_t* data) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    if ((1+data_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_node_send_input_oob_request_response.data.len=data_len;
    memcpy(cmd->data.cmd_node_send_input_oob_request_response.data.data,data,data_len);

    cmd->header=sl_btmesh_cmd_node_send_input_oob_request_response_id+(((1+data_len)&0xff)<<8)+(((1+data_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_node_send_input_oob_request_response.result;

}

sl_status_t sl_btmesh_node_get_uuid(uuid_128 *uuid) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_node_get_uuid_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (uuid) {
        *uuid = rsp->data.rsp_node_get_uuid.uuid;
    }
    return rsp->data.rsp_node_get_uuid.result;

}

sl_status_t sl_btmesh_node_set_provisioning_data(aes_key_128 device_key,
                                                 aes_key_128 network_key,
                                                 uint16_t netkey_index,
                                                 uint32_t iv_index,
                                                 uint16_t address,
                                                 uint8_t kr_in_progress) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    memcpy(&cmd->data.cmd_node_set_provisioning_data.device_key,&device_key,sizeof(aes_key_128));
    memcpy(&cmd->data.cmd_node_set_provisioning_data.network_key,&network_key,sizeof(aes_key_128));
    cmd->data.cmd_node_set_provisioning_data.netkey_index=netkey_index;
    cmd->data.cmd_node_set_provisioning_data.iv_index=iv_index;
    cmd->data.cmd_node_set_provisioning_data.address=address;
    cmd->data.cmd_node_set_provisioning_data.kr_in_progress=kr_in_progress;

    cmd->header=sl_btmesh_cmd_node_set_provisioning_data_id+(((41)&0xff)<<8)+(((41)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_node_set_provisioning_data.result;

}

sl_status_t sl_btmesh_node_init_oob(uint8_t public_key,
                                    uint8_t auth_methods,
                                    uint16_t output_actions,
                                    uint8_t output_size,
                                    uint16_t input_actions,
                                    uint8_t input_size,
                                    uint16_t oob_location) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_node_init_oob.public_key=public_key;
    cmd->data.cmd_node_init_oob.auth_methods=auth_methods;
    cmd->data.cmd_node_init_oob.output_actions=output_actions;
    cmd->data.cmd_node_init_oob.output_size=output_size;
    cmd->data.cmd_node_init_oob.input_actions=input_actions;
    cmd->data.cmd_node_init_oob.input_size=input_size;
    cmd->data.cmd_node_init_oob.oob_location=oob_location;

    cmd->header=sl_btmesh_cmd_node_init_oob_id+(((10)&0xff)<<8)+(((10)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_node_init_oob.result;

}

sl_status_t sl_btmesh_node_set_ivrecovery_mode(uint8_t mode) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_node_set_ivrecovery_mode.mode=mode;

    cmd->header=sl_btmesh_cmd_node_set_ivrecovery_mode_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_node_set_ivrecovery_mode.result;

}

sl_status_t sl_btmesh_node_get_ivrecovery_mode(uint8_t *mode) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_node_get_ivrecovery_mode_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (mode) {
        *mode = rsp->data.rsp_node_get_ivrecovery_mode.mode;
    }
    return rsp->data.rsp_node_get_ivrecovery_mode.result;

}

sl_status_t sl_btmesh_node_get_statistics(size_t max_statistics_size,
                                          size_t *statistics_len,
                                          uint8_t *statistics) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_node_get_statistics_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (statistics_len) {
        *statistics_len = rsp->data.rsp_node_get_statistics.statistics.len;
    }
    if (statistics && (rsp->data.rsp_node_get_statistics.statistics.len <= max_statistics_size)) {
        memcpy(statistics,rsp->data.rsp_node_get_statistics.statistics.data,rsp->data.rsp_node_get_statistics.statistics.len);
    }
    return rsp->data.rsp_node_get_statistics.result;

}

sl_status_t sl_btmesh_node_clear_statistics() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_node_clear_statistics_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_node_clear_statistics.result;

}

sl_status_t sl_btmesh_node_set_net_relay_delay(uint8_t min_ms, uint8_t max_ms) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_node_set_net_relay_delay.min_ms=min_ms;
    cmd->data.cmd_node_set_net_relay_delay.max_ms=max_ms;

    cmd->header=sl_btmesh_cmd_node_set_net_relay_delay_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_node_set_net_relay_delay.result;

}

sl_status_t sl_btmesh_node_get_net_relay_delay(uint8_t *min_ms,
                                               uint8_t *max_ms) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_node_get_net_relay_delay_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (min_ms) {
        *min_ms = rsp->data.rsp_node_get_net_relay_delay.min_ms;
    }
    if (max_ms) {
        *max_ms = rsp->data.rsp_node_get_net_relay_delay.max_ms;
    }
    return rsp->data.rsp_node_get_net_relay_delay.result;

}

sl_status_t sl_btmesh_node_get_ivupdate_state(uint32_t *iv_index,
                                              uint8_t *state) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_node_get_ivupdate_state_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (iv_index) {
        *iv_index = rsp->data.rsp_node_get_ivupdate_state.iv_index;
    }
    if (state) {
        *state = rsp->data.rsp_node_get_ivupdate_state.state;
    }
    return rsp->data.rsp_node_get_ivupdate_state.result;

}

sl_status_t sl_btmesh_node_request_ivupdate() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_node_request_ivupdate_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_node_request_ivupdate.result;

}

sl_status_t sl_btmesh_node_get_seq_remaining(uint16_t elem_index,
                                             uint32_t *count) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_node_get_seq_remaining.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_node_get_seq_remaining_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (count) {
        *count = rsp->data.rsp_node_get_seq_remaining.count;
    }
    return rsp->data.rsp_node_get_seq_remaining.result;

}

sl_status_t sl_btmesh_node_save_replay_protection_list() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_node_save_replay_protection_list_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_node_save_replay_protection_list.result;

}

sl_status_t sl_btmesh_node_set_uuid(uuid_128 uuid) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_node_set_uuid.uuid=uuid;

    cmd->header=sl_btmesh_cmd_node_set_uuid_id+(((16)&0xff)<<8)+(((16)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_node_set_uuid.result;

}

sl_status_t sl_btmesh_node_get_replay_protection_list_status(uint16_t *total_entries,
                                                             uint16_t *unsaved_entries) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_node_get_replay_protection_list_status_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (total_entries) {
        *total_entries = rsp->data.rsp_node_get_replay_protection_list_status.total_entries;
    }
    if (unsaved_entries) {
        *unsaved_entries = rsp->data.rsp_node_get_replay_protection_list_status.unsaved_entries;
    }
    return rsp->data.rsp_node_get_replay_protection_list_status.result;

}

sl_status_t sl_btmesh_node_get_element_address(uint16_t elem_index,
                                               uint16_t *address) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_node_get_element_address.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_node_get_element_address_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (address) {
        *address = rsp->data.rsp_node_get_element_address.address;
    }
    return rsp->data.rsp_node_get_element_address.result;

}

sl_status_t sl_btmesh_node_send_static_oob_request_response(size_t data_len,
                                                            const uint8_t* data) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    if ((1+data_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_node_send_static_oob_request_response.data.len=data_len;
    memcpy(cmd->data.cmd_node_send_static_oob_request_response.data.data,data,data_len);

    cmd->header=sl_btmesh_cmd_node_send_static_oob_request_response_id+(((1+data_len)&0xff)<<8)+(((1+data_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_node_send_static_oob_request_response.result;

}

sl_status_t sl_btmesh_node_reset() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_node_reset_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_node_reset.result;

}

sl_status_t sl_btmesh_node_set_beacon_reporting(uint8_t report) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_node_set_beacon_reporting.report=report;

    cmd->header=sl_btmesh_cmd_node_set_beacon_reporting_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_node_set_beacon_reporting.result;

}

sl_status_t sl_btmesh_node_set_iv_update_age(uint32_t age_sec) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_node_set_iv_update_age.age_sec=age_sec;

    cmd->header=sl_btmesh_cmd_node_set_iv_update_age_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_node_set_iv_update_age.result;

}

sl_status_t sl_btmesh_node_get_key_count(uint8_t type, uint32_t *count) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_node_get_key_count.type=type;

    cmd->header=sl_btmesh_cmd_node_get_key_count_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (count) {
        *count = rsp->data.rsp_node_get_key_count.count;
    }
    return rsp->data.rsp_node_get_key_count.result;

}

sl_status_t sl_btmesh_node_get_key(uint8_t type,
                                   uint32_t index,
                                   uint8_t current,
                                   uint16_t *id,
                                   uint16_t *netkey_index,
                                   aes_key_128 *key) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_node_get_key.type=type;
    cmd->data.cmd_node_get_key.index=index;
    cmd->data.cmd_node_get_key.current=current;

    cmd->header=sl_btmesh_cmd_node_get_key_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (id) {
        *id = rsp->data.rsp_node_get_key.id;
    }
    if (netkey_index) {
        *netkey_index = rsp->data.rsp_node_get_key.netkey_index;
    }
    if (key) {
        memcpy(key,&rsp->data.rsp_node_get_key.key,sizeof(aes_key_128));
    }
    return rsp->data.rsp_node_get_key.result;

}

sl_status_t sl_btmesh_node_get_networks(size_t max_networks_size,
                                        size_t *networks_len,
                                        uint8_t *networks) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_node_get_networks_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (networks_len) {
        *networks_len = rsp->data.rsp_node_get_networks.networks.len;
    }
    if (networks && (rsp->data.rsp_node_get_networks.networks.len <= max_networks_size)) {
        memcpy(networks,rsp->data.rsp_node_get_networks.networks.data,rsp->data.rsp_node_get_networks.networks.len);
    }
    return rsp->data.rsp_node_get_networks.result;

}

sl_status_t sl_btmesh_node_get_element_seqnum(uint16_t elem_index,
                                              uint32_t *seqnum) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_node_get_element_seqnum.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_node_get_element_seqnum_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (seqnum) {
        *seqnum = rsp->data.rsp_node_get_element_seqnum.seqnum;
    }
    return rsp->data.rsp_node_get_element_seqnum.result;

}

sl_status_t sl_btmesh_node_set_model_option(uint16_t elem_index,
                                            uint16_t vendor_id,
                                            uint16_t model_id,
                                            uint8_t option,
                                            uint32_t value) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_node_set_model_option.elem_index=elem_index;
    cmd->data.cmd_node_set_model_option.vendor_id=vendor_id;
    cmd->data.cmd_node_set_model_option.model_id=model_id;
    cmd->data.cmd_node_set_model_option.option=option;
    cmd->data.cmd_node_set_model_option.value=value;

    cmd->header=sl_btmesh_cmd_node_set_model_option_id+(((11)&0xff)<<8)+(((11)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_node_set_model_option.result;

}

sl_status_t sl_btmesh_node_get_local_dcd(uint8_t page) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_node_get_local_dcd.page=page;

    cmd->header=sl_btmesh_cmd_node_get_local_dcd_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_node_get_local_dcd.result;

}

sl_status_t sl_btmesh_node_power_off() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_node_power_off_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_node_power_off.result;

}

sl_status_t sl_btmesh_node_set_adv_phy(uint8_t phy) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_node_set_adv_phy.phy=phy;

    cmd->header=sl_btmesh_cmd_node_set_adv_phy_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_node_set_adv_phy.result;

}

sl_status_t sl_btmesh_node_get_adv_phy(uint8_t *phy) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_node_get_adv_phy_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (phy) {
        *phy = rsp->data.rsp_node_get_adv_phy.phy;
    }
    return rsp->data.rsp_node_get_adv_phy.result;

}

sl_status_t sl_btmesh_node_set_provisioning_algorithms(uint16_t algorithms) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_node_set_provisioning_algorithms.algorithms=algorithms;

    cmd->header=sl_btmesh_cmd_node_set_provisioning_algorithms_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_node_set_provisioning_algorithms.result;

}

sl_status_t sl_btmesh_node_init_provisioning_records() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_node_init_provisioning_records_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_node_init_provisioning_records.result;

}

sl_status_t sl_btmesh_node_set_unprov_beaconing_adv_interval(uint16_t adv_interval_min,
                                                             uint16_t adv_interval_max) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_node_set_unprov_beaconing_adv_interval.adv_interval_min=adv_interval_min;
    cmd->data.cmd_node_set_unprov_beaconing_adv_interval.adv_interval_max=adv_interval_max;

    cmd->header=sl_btmesh_cmd_node_set_unprov_beaconing_adv_interval_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_node_set_unprov_beaconing_adv_interval.result;

}

sl_status_t sl_btmesh_node_set_proxy_service_adv_interval(uint16_t adv_interval_min,
                                                          uint16_t adv_interval_max) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_node_set_proxy_service_adv_interval.adv_interval_min=adv_interval_min;
    cmd->data.cmd_node_set_proxy_service_adv_interval.adv_interval_max=adv_interval_max;

    cmd->header=sl_btmesh_cmd_node_set_proxy_service_adv_interval_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_node_set_proxy_service_adv_interval.result;

}

sl_status_t sl_btmesh_node_set_provisioning_service_adv_interval(uint16_t adv_interval_min,
                                                                 uint16_t adv_interval_max) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_node_set_provisioning_service_adv_interval.adv_interval_min=adv_interval_min;
    cmd->data.cmd_node_set_provisioning_service_adv_interval.adv_interval_max=adv_interval_max;

    cmd->header=sl_btmesh_cmd_node_set_provisioning_service_adv_interval_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_node_set_provisioning_service_adv_interval.result;

}

sl_status_t sl_btmesh_node_get_local_model_metadata_page(uint8_t page) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_node_get_local_model_metadata_page.page=page;

    cmd->header=sl_btmesh_cmd_node_get_local_model_metadata_page_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_node_get_local_model_metadata_page.result;

}

sl_status_t sl_btmesh_node_save_proxy_solicitation_rpl() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_node_save_proxy_solicitation_rpl_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_node_save_proxy_solicitation_rpl.result;

}

sl_status_t sl_btmesh_node_get_proxy_solicitation_rpl_status(uint16_t *total_entries,
                                                             uint16_t *unsaved_entries) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_node_get_proxy_solicitation_rpl_status_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (total_entries) {
        *total_entries = rsp->data.rsp_node_get_proxy_solicitation_rpl_status.total_entries;
    }
    if (unsaved_entries) {
        *unsaved_entries = rsp->data.rsp_node_get_proxy_solicitation_rpl_status.unsaved_entries;
    }
    return rsp->data.rsp_node_get_proxy_solicitation_rpl_status.result;

}

sl_status_t sl_btmesh_node_set_oob_uri(size_t uri_len, const uint8_t* uri) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    if ((1+uri_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_node_set_oob_uri.uri.len=uri_len;
    memcpy(cmd->data.cmd_node_set_oob_uri.uri.data,uri,uri_len);

    cmd->header=sl_btmesh_cmd_node_set_oob_uri_id+(((1+uri_len)&0xff)<<8)+(((1+uri_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_node_set_oob_uri.result;

}

sl_status_t sl_btmesh_node_get_oob_uri(size_t max_uri_size,
                                       size_t *uri_len,
                                       uint8_t *uri) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_node_get_oob_uri_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (uri_len) {
        *uri_len = rsp->data.rsp_node_get_oob_uri.uri.len;
    }
    if (uri && (rsp->data.rsp_node_get_oob_uri.uri.len <= max_uri_size)) {
        memcpy(uri,rsp->data.rsp_node_get_oob_uri.uri.data,rsp->data.rsp_node_get_oob_uri.uri.len);
    }
    return rsp->data.rsp_node_get_oob_uri.result;

}

sl_status_t sl_btmesh_prov_init() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_prov_init_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_init.result;

}

sl_status_t sl_btmesh_prov_scan_unprov_beacons() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_prov_scan_unprov_beacons_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_scan_unprov_beacons.result;

}

sl_status_t sl_btmesh_prov_create_provisioning_session(uint16_t netkey_index,
                                                       uuid_128 uuid,
                                                       uint8_t attention_timer_sec) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_create_provisioning_session.netkey_index=netkey_index;
    cmd->data.cmd_prov_create_provisioning_session.uuid=uuid;
    cmd->data.cmd_prov_create_provisioning_session.attention_timer_sec=attention_timer_sec;

    cmd->header=sl_btmesh_cmd_prov_create_provisioning_session_id+(((19)&0xff)<<8)+(((19)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_create_provisioning_session.result;

}

sl_status_t sl_btmesh_prov_set_provisioning_suspend_event(uint8_t status) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_set_provisioning_suspend_event.status=status;

    cmd->header=sl_btmesh_cmd_prov_set_provisioning_suspend_event_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_set_provisioning_suspend_event.result;

}

sl_status_t sl_btmesh_prov_provision_adv_device(uuid_128 uuid) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_provision_adv_device.uuid=uuid;

    cmd->header=sl_btmesh_cmd_prov_provision_adv_device_id+(((16)&0xff)<<8)+(((16)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_provision_adv_device.result;

}

sl_status_t sl_btmesh_prov_provision_gatt_device(uuid_128 uuid,
                                                 uint8_t connection) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_provision_gatt_device.uuid=uuid;
    cmd->data.cmd_prov_provision_gatt_device.connection=connection;

    cmd->header=sl_btmesh_cmd_prov_provision_gatt_device_id+(((17)&0xff)<<8)+(((17)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_provision_gatt_device.result;

}

sl_status_t sl_btmesh_prov_provision_remote_device(uuid_128 uuid,
                                                   uint16_t server) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_provision_remote_device.uuid=uuid;
    cmd->data.cmd_prov_provision_remote_device.server=server;

    cmd->header=sl_btmesh_cmd_prov_provision_remote_device_id+(((18)&0xff)<<8)+(((18)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_provision_remote_device.result;

}

sl_status_t sl_btmesh_prov_continue_provisioning(uuid_128 uuid) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_continue_provisioning.uuid=uuid;

    cmd->header=sl_btmesh_cmd_prov_continue_provisioning_id+(((16)&0xff)<<8)+(((16)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_continue_provisioning.result;

}

sl_status_t sl_btmesh_prov_abort_provisioning(uuid_128 uuid, uint8_t reason) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_abort_provisioning.uuid=uuid;
    cmd->data.cmd_prov_abort_provisioning.reason=reason;

    cmd->header=sl_btmesh_cmd_prov_abort_provisioning_id+(((17)&0xff)<<8)+(((17)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_abort_provisioning.result;

}

sl_status_t sl_btmesh_prov_set_device_address(uuid_128 uuid, uint16_t address) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_set_device_address.uuid=uuid;
    cmd->data.cmd_prov_set_device_address.address=address;

    cmd->header=sl_btmesh_cmd_prov_set_device_address_id+(((18)&0xff)<<8)+(((18)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_set_device_address.result;

}

sl_status_t sl_btmesh_prov_create_network(uint16_t netkey_index,
                                          size_t key_len,
                                          const uint8_t* key) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_create_network.netkey_index=netkey_index;
    if ((3+key_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_prov_create_network.key.len=key_len;
    memcpy(cmd->data.cmd_prov_create_network.key.data,key,key_len);

    cmd->header=sl_btmesh_cmd_prov_create_network_id+(((3+key_len)&0xff)<<8)+(((3+key_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_create_network.result;

}

sl_status_t sl_btmesh_prov_create_appkey(uint16_t netkey_index,
                                         uint16_t appkey_index,
                                         size_t key_len,
                                         const uint8_t* key,
                                         size_t max_application_key_size,
                                         size_t *application_key_len,
                                         uint8_t *application_key) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_create_appkey.netkey_index=netkey_index;
    cmd->data.cmd_prov_create_appkey.appkey_index=appkey_index;
    if ((5+key_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_prov_create_appkey.key.len=key_len;
    memcpy(cmd->data.cmd_prov_create_appkey.key.data,key,key_len);

    cmd->header=sl_btmesh_cmd_prov_create_appkey_id+(((5+key_len)&0xff)<<8)+(((5+key_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (application_key_len) {
        *application_key_len = rsp->data.rsp_prov_create_appkey.application_key.len;
    }
    if (application_key && (rsp->data.rsp_prov_create_appkey.application_key.len <= max_application_key_size)) {
        memcpy(application_key,rsp->data.rsp_prov_create_appkey.application_key.data,rsp->data.rsp_prov_create_appkey.application_key.len);
    }
    return rsp->data.rsp_prov_create_appkey.result;

}

sl_status_t sl_btmesh_prov_send_oob_pkey_response(uuid_128 uuid,
                                                  size_t pkey_len,
                                                  const uint8_t* pkey) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_send_oob_pkey_response.uuid=uuid;
    if ((17+pkey_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_prov_send_oob_pkey_response.pkey.len=pkey_len;
    memcpy(cmd->data.cmd_prov_send_oob_pkey_response.pkey.data,pkey,pkey_len);

    cmd->header=sl_btmesh_cmd_prov_send_oob_pkey_response_id+(((17+pkey_len)&0xff)<<8)+(((17+pkey_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_send_oob_pkey_response.result;

}

sl_status_t sl_btmesh_prov_send_oob_auth_response(uuid_128 uuid,
                                                  size_t data_len,
                                                  const uint8_t* data) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_send_oob_auth_response.uuid=uuid;
    if ((17+data_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_prov_send_oob_auth_response.data.len=data_len;
    memcpy(cmd->data.cmd_prov_send_oob_auth_response.data.data,data,data_len);

    cmd->header=sl_btmesh_cmd_prov_send_oob_auth_response_id+(((17+data_len)&0xff)<<8)+(((17+data_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_send_oob_auth_response.result;

}

sl_status_t sl_btmesh_prov_set_oob_requirements(uuid_128 uuid,
                                                uint8_t public_key,
                                                uint8_t auth_methods,
                                                uint16_t output_actions,
                                                uint16_t input_actions,
                                                uint8_t min_size,
                                                uint8_t max_size) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_set_oob_requirements.uuid=uuid;
    cmd->data.cmd_prov_set_oob_requirements.public_key=public_key;
    cmd->data.cmd_prov_set_oob_requirements.auth_methods=auth_methods;
    cmd->data.cmd_prov_set_oob_requirements.output_actions=output_actions;
    cmd->data.cmd_prov_set_oob_requirements.input_actions=input_actions;
    cmd->data.cmd_prov_set_oob_requirements.min_size=min_size;
    cmd->data.cmd_prov_set_oob_requirements.max_size=max_size;

    cmd->header=sl_btmesh_cmd_prov_set_oob_requirements_id+(((24)&0xff)<<8)+(((24)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_set_oob_requirements.result;

}

sl_status_t sl_btmesh_prov_start_key_refresh(uint16_t netkey_index,
                                             uint8_t num_appkeys,
                                             size_t appkey_indices_len,
                                             const uint8_t* appkey_indices) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_start_key_refresh.netkey_index=netkey_index;
    cmd->data.cmd_prov_start_key_refresh.num_appkeys=num_appkeys;
    if ((4+appkey_indices_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_prov_start_key_refresh.appkey_indices.len=appkey_indices_len;
    memcpy(cmd->data.cmd_prov_start_key_refresh.appkey_indices.data,appkey_indices,appkey_indices_len);

    cmd->header=sl_btmesh_cmd_prov_start_key_refresh_id+(((4+appkey_indices_len)&0xff)<<8)+(((4+appkey_indices_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_start_key_refresh.result;

}

sl_status_t sl_btmesh_prov_get_key_refresh_exclusion(uint16_t key,
                                                     uuid_128 uuid,
                                                     uint8_t *status) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_get_key_refresh_exclusion.key=key;
    cmd->data.cmd_prov_get_key_refresh_exclusion.uuid=uuid;

    cmd->header=sl_btmesh_cmd_prov_get_key_refresh_exclusion_id+(((18)&0xff)<<8)+(((18)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (status) {
        *status = rsp->data.rsp_prov_get_key_refresh_exclusion.status;
    }
    return rsp->data.rsp_prov_get_key_refresh_exclusion.result;

}

sl_status_t sl_btmesh_prov_set_key_refresh_exclusion(uint16_t key,
                                                     uint8_t status,
                                                     uuid_128 uuid) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_set_key_refresh_exclusion.key=key;
    cmd->data.cmd_prov_set_key_refresh_exclusion.status=status;
    cmd->data.cmd_prov_set_key_refresh_exclusion.uuid=uuid;

    cmd->header=sl_btmesh_cmd_prov_set_key_refresh_exclusion_id+(((19)&0xff)<<8)+(((19)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_set_key_refresh_exclusion.result;

}

sl_status_t sl_btmesh_prov_set_key_refresh_failure(uint16_t key, uuid_128 uuid) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_set_key_refresh_failure.key=key;
    cmd->data.cmd_prov_set_key_refresh_failure.uuid=uuid;

    cmd->header=sl_btmesh_cmd_prov_set_key_refresh_failure_id+(((18)&0xff)<<8)+(((18)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_set_key_refresh_failure.result;

}

sl_status_t sl_btmesh_prov_phase_timeout_get(uint32_t *phase_timeout_s) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_prov_phase_timeout_get_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (phase_timeout_s) {
        *phase_timeout_s = rsp->data.rsp_prov_phase_timeout_get.phase_timeout_s;
    }
    return rsp->data.rsp_prov_phase_timeout_get.result;

}

sl_status_t sl_btmesh_prov_phase_timeout_set(uint32_t phase_timeout_s) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_phase_timeout_set.phase_timeout_s=phase_timeout_s;

    cmd->header=sl_btmesh_cmd_prov_phase_timeout_set_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_phase_timeout_set.result;

}

sl_status_t sl_btmesh_prov_get_ddb_entry(uuid_128 uuid,
                                         aes_key_128 *device_key,
                                         uint16_t *netkey_index,
                                         uint16_t *address,
                                         uint8_t *elements) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_get_ddb_entry.uuid=uuid;

    cmd->header=sl_btmesh_cmd_prov_get_ddb_entry_id+(((16)&0xff)<<8)+(((16)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (device_key) {
        memcpy(device_key,&rsp->data.rsp_prov_get_ddb_entry.device_key,sizeof(aes_key_128));
    }
    if (netkey_index) {
        *netkey_index = rsp->data.rsp_prov_get_ddb_entry.netkey_index;
    }
    if (address) {
        *address = rsp->data.rsp_prov_get_ddb_entry.address;
    }
    if (elements) {
        *elements = rsp->data.rsp_prov_get_ddb_entry.elements;
    }
    return rsp->data.rsp_prov_get_ddb_entry.result;

}

sl_status_t sl_btmesh_prov_delete_ddb_entry(uuid_128 uuid) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_delete_ddb_entry.uuid=uuid;

    cmd->header=sl_btmesh_cmd_prov_delete_ddb_entry_id+(((16)&0xff)<<8)+(((16)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_delete_ddb_entry.result;

}

sl_status_t sl_btmesh_prov_add_ddb_entry(uuid_128 uuid,
                                         aes_key_128 device_key,
                                         uint16_t netkey_index,
                                         uint16_t address,
                                         uint8_t elements) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_add_ddb_entry.uuid=uuid;
    memcpy(&cmd->data.cmd_prov_add_ddb_entry.device_key,&device_key,sizeof(aes_key_128));
    cmd->data.cmd_prov_add_ddb_entry.netkey_index=netkey_index;
    cmd->data.cmd_prov_add_ddb_entry.address=address;
    cmd->data.cmd_prov_add_ddb_entry.elements=elements;

    cmd->header=sl_btmesh_cmd_prov_add_ddb_entry_id+(((37)&0xff)<<8)+(((37)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_add_ddb_entry.result;

}

sl_status_t sl_btmesh_prov_list_ddb_entries(uint16_t *count) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_prov_list_ddb_entries_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (count) {
        *count = rsp->data.rsp_prov_list_ddb_entries.count;
    }
    return rsp->data.rsp_prov_list_ddb_entries.result;

}

sl_status_t sl_btmesh_prov_initialize_network(uint16_t address, uint32_t ivi) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_initialize_network.address=address;
    cmd->data.cmd_prov_initialize_network.ivi=ivi;

    cmd->header=sl_btmesh_cmd_prov_initialize_network_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_initialize_network.result;

}

sl_status_t sl_btmesh_prov_get_key_refresh_appkey_exclusion(uint16_t netkey_index,
                                                            uint16_t appkey_index,
                                                            uuid_128 uuid,
                                                            uint8_t *status) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_get_key_refresh_appkey_exclusion.netkey_index=netkey_index;
    cmd->data.cmd_prov_get_key_refresh_appkey_exclusion.appkey_index=appkey_index;
    cmd->data.cmd_prov_get_key_refresh_appkey_exclusion.uuid=uuid;

    cmd->header=sl_btmesh_cmd_prov_get_key_refresh_appkey_exclusion_id+(((20)&0xff)<<8)+(((20)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (status) {
        *status = rsp->data.rsp_prov_get_key_refresh_appkey_exclusion.status;
    }
    return rsp->data.rsp_prov_get_key_refresh_appkey_exclusion.result;

}

sl_status_t sl_btmesh_prov_set_key_refresh_appkey_exclusion(uint16_t netkey_index,
                                                            uint16_t appkey_index,
                                                            uint8_t status,
                                                            uuid_128 uuid) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_set_key_refresh_appkey_exclusion.netkey_index=netkey_index;
    cmd->data.cmd_prov_set_key_refresh_appkey_exclusion.appkey_index=appkey_index;
    cmd->data.cmd_prov_set_key_refresh_appkey_exclusion.status=status;
    cmd->data.cmd_prov_set_key_refresh_appkey_exclusion.uuid=uuid;

    cmd->header=sl_btmesh_cmd_prov_set_key_refresh_appkey_exclusion_id+(((21)&0xff)<<8)+(((21)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_set_key_refresh_appkey_exclusion.result;

}

sl_status_t sl_btmesh_prov_stop_scan_unprov_beacons() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_prov_stop_scan_unprov_beacons_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_stop_scan_unprov_beacons.result;

}

sl_status_t sl_btmesh_prov_update_device_netkey_index(uuid_128 uuid,
                                                      uint16_t netkey_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_update_device_netkey_index.uuid=uuid;
    cmd->data.cmd_prov_update_device_netkey_index.netkey_index=netkey_index;

    cmd->header=sl_btmesh_cmd_prov_update_device_netkey_index_id+(((18)&0xff)<<8)+(((18)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_update_device_netkey_index.result;

}

sl_status_t sl_btmesh_prov_suspend_key_refresh(uint16_t netkey_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_suspend_key_refresh.netkey_index=netkey_index;

    cmd->header=sl_btmesh_cmd_prov_suspend_key_refresh_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_suspend_key_refresh.result;

}

sl_status_t sl_btmesh_prov_resume_key_refresh(uint16_t netkey_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_resume_key_refresh.netkey_index=netkey_index;

    cmd->header=sl_btmesh_cmd_prov_resume_key_refresh_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_resume_key_refresh.result;

}

sl_status_t sl_btmesh_prov_get_key_refresh_phase(uint16_t netkey_index,
                                                 uint8_t *phase) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_get_key_refresh_phase.netkey_index=netkey_index;

    cmd->header=sl_btmesh_cmd_prov_get_key_refresh_phase_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (phase) {
        *phase = rsp->data.rsp_prov_get_key_refresh_phase.phase;
    }
    return rsp->data.rsp_prov_get_key_refresh_phase.result;

}

sl_status_t sl_btmesh_prov_start_key_refresh_from_phase(uint8_t phase,
                                                        uint16_t netkey_index,
                                                        uint8_t num_appkeys,
                                                        size_t appkey_indices_len,
                                                        const uint8_t* appkey_indices) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_start_key_refresh_from_phase.phase=phase;
    cmd->data.cmd_prov_start_key_refresh_from_phase.netkey_index=netkey_index;
    cmd->data.cmd_prov_start_key_refresh_from_phase.num_appkeys=num_appkeys;
    if ((5+appkey_indices_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_prov_start_key_refresh_from_phase.appkey_indices.len=appkey_indices_len;
    memcpy(cmd->data.cmd_prov_start_key_refresh_from_phase.appkey_indices.data,appkey_indices,appkey_indices_len);

    cmd->header=sl_btmesh_cmd_prov_start_key_refresh_from_phase_id+(((5+appkey_indices_len)&0xff)<<8)+(((5+appkey_indices_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_start_key_refresh_from_phase.result;

}

sl_status_t sl_btmesh_prov_flush_key_refresh_state(uint16_t netkey_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_flush_key_refresh_state.netkey_index=netkey_index;

    cmd->header=sl_btmesh_cmd_prov_flush_key_refresh_state_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_flush_key_refresh_state.result;

}

sl_status_t sl_btmesh_prov_test_identity(uint16_t address,
                                         uint16_t netkey_index,
                                         size_t data_len,
                                         const uint8_t* data,
                                         uint8_t *match) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_test_identity.address=address;
    cmd->data.cmd_prov_test_identity.netkey_index=netkey_index;
    if ((5+data_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_prov_test_identity.data.len=data_len;
    memcpy(cmd->data.cmd_prov_test_identity.data.data,data,data_len);

    cmd->header=sl_btmesh_cmd_prov_test_identity_id+(((5+data_len)&0xff)<<8)+(((5+data_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (match) {
        *match = rsp->data.rsp_prov_test_identity.match;
    }
    return rsp->data.rsp_prov_test_identity.result;

}

sl_status_t sl_btmesh_prov_get_provisioning_records_list(uuid_128 uuid) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_get_provisioning_records_list.uuid=uuid;

    cmd->header=sl_btmesh_cmd_prov_get_provisioning_records_list_id+(((16)&0xff)<<8)+(((16)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_get_provisioning_records_list.result;

}

sl_status_t sl_btmesh_prov_get_provisioning_record_data(uuid_128 uuid,
                                                        uint16_t record) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_prov_get_provisioning_record_data.uuid=uuid;
    cmd->data.cmd_prov_get_provisioning_record_data.record=record;

    cmd->header=sl_btmesh_cmd_prov_get_provisioning_record_data_id+(((18)&0xff)<<8)+(((18)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_get_provisioning_record_data.result;

}

sl_status_t sl_btmesh_prov_init_provisioning_records() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_prov_init_provisioning_records_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_prov_init_provisioning_records.result;

}

sl_status_t sl_btmesh_proxy_connect(uint8_t connection, uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_proxy_connect.connection=connection;

    cmd->header=sl_btmesh_cmd_proxy_connect_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_proxy_connect.handle;
    }
    return rsp->data.rsp_proxy_connect.result;

}

sl_status_t sl_btmesh_proxy_disconnect(uint32_t handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_proxy_disconnect.handle=handle;

    cmd->header=sl_btmesh_cmd_proxy_disconnect_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_proxy_disconnect.result;

}

sl_status_t sl_btmesh_proxy_set_filter_type(uint32_t handle,
                                            uint16_t netkey_index,
                                            uint8_t type) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_proxy_set_filter_type.handle=handle;
    cmd->data.cmd_proxy_set_filter_type.netkey_index=netkey_index;
    cmd->data.cmd_proxy_set_filter_type.type=type;

    cmd->header=sl_btmesh_cmd_proxy_set_filter_type_id+(((7)&0xff)<<8)+(((7)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_proxy_set_filter_type.result;

}

sl_status_t sl_btmesh_proxy_allow(uint32_t handle,
                                  uint16_t netkey_index,
                                  uint16_t address) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_proxy_allow.handle=handle;
    cmd->data.cmd_proxy_allow.netkey_index=netkey_index;
    cmd->data.cmd_proxy_allow.address=address;

    cmd->header=sl_btmesh_cmd_proxy_allow_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_proxy_allow.result;

}

sl_status_t sl_btmesh_proxy_deny(uint32_t handle,
                                 uint16_t netkey_index,
                                 uint16_t address) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_proxy_deny.handle=handle;
    cmd->data.cmd_proxy_deny.netkey_index=netkey_index;
    cmd->data.cmd_proxy_deny.address=address;

    cmd->header=sl_btmesh_cmd_proxy_deny_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_proxy_deny.result;

}

sl_status_t sl_btmesh_proxy_optimisation_toggle(uint8_t enable) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_proxy_optimisation_toggle.enable=enable;

    cmd->header=sl_btmesh_cmd_proxy_optimisation_toggle_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_proxy_optimisation_toggle.result;

}

sl_status_t sl_btmesh_proxy_send_solicitation(uint8_t enc_netkey_index,
                                              uint16_t elem_index,
                                              uint16_t dst) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_proxy_send_solicitation.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_proxy_send_solicitation.elem_index=elem_index;
    cmd->data.cmd_proxy_send_solicitation.dst=dst;

    cmd->header=sl_btmesh_cmd_proxy_send_solicitation_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_proxy_send_solicitation.result;

}

sl_status_t sl_btmesh_silabs_config_client_init() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_silabs_config_client_init_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_silabs_config_client_init.result;

}

sl_status_t sl_btmesh_silabs_config_client_set_tx(uint16_t server_address,
                                                  uint16_t appkey_index,
                                                  uint8_t tx_phy,
                                                  uint32_t tx_options_bitmap) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_silabs_config_client_set_tx.server_address=server_address;
    cmd->data.cmd_silabs_config_client_set_tx.appkey_index=appkey_index;
    cmd->data.cmd_silabs_config_client_set_tx.tx_phy=tx_phy;
    cmd->data.cmd_silabs_config_client_set_tx.tx_options_bitmap=tx_options_bitmap;

    cmd->header=sl_btmesh_cmd_silabs_config_client_set_tx_id+(((9)&0xff)<<8)+(((9)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_silabs_config_client_set_tx.result;

}

sl_status_t sl_btmesh_silabs_config_client_get_tx(uint16_t server_address,
                                                  uint16_t appkey_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_silabs_config_client_get_tx.server_address=server_address;
    cmd->data.cmd_silabs_config_client_get_tx.appkey_index=appkey_index;

    cmd->header=sl_btmesh_cmd_silabs_config_client_get_tx_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_silabs_config_client_get_tx.result;

}

sl_status_t sl_btmesh_silabs_config_client_set_model_enable(uint16_t server_address,
                                                            uint16_t appkey_index,
                                                            uint16_t elem_index,
                                                            uint16_t vendor_id,
                                                            uint16_t model_id,
                                                            uint8_t enable) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_silabs_config_client_set_model_enable.server_address=server_address;
    cmd->data.cmd_silabs_config_client_set_model_enable.appkey_index=appkey_index;
    cmd->data.cmd_silabs_config_client_set_model_enable.elem_index=elem_index;
    cmd->data.cmd_silabs_config_client_set_model_enable.vendor_id=vendor_id;
    cmd->data.cmd_silabs_config_client_set_model_enable.model_id=model_id;
    cmd->data.cmd_silabs_config_client_set_model_enable.enable=enable;

    cmd->header=sl_btmesh_cmd_silabs_config_client_set_model_enable_id+(((11)&0xff)<<8)+(((11)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_silabs_config_client_set_model_enable.result;

}

sl_status_t sl_btmesh_silabs_config_client_get_model_enable(uint16_t server_address,
                                                            uint16_t appkey_index,
                                                            uint16_t elem_index,
                                                            uint16_t vendor_id,
                                                            uint16_t model_id) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_silabs_config_client_get_model_enable.server_address=server_address;
    cmd->data.cmd_silabs_config_client_get_model_enable.appkey_index=appkey_index;
    cmd->data.cmd_silabs_config_client_get_model_enable.elem_index=elem_index;
    cmd->data.cmd_silabs_config_client_get_model_enable.vendor_id=vendor_id;
    cmd->data.cmd_silabs_config_client_get_model_enable.model_id=model_id;

    cmd->header=sl_btmesh_cmd_silabs_config_client_get_model_enable_id+(((10)&0xff)<<8)+(((10)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_silabs_config_client_get_model_enable.result;

}

sl_status_t sl_btmesh_silabs_config_client_set_network_pdu(uint16_t server_address,
                                                           uint16_t appkey_index,
                                                           uint16_t pdu_max_size) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_silabs_config_client_set_network_pdu.server_address=server_address;
    cmd->data.cmd_silabs_config_client_set_network_pdu.appkey_index=appkey_index;
    cmd->data.cmd_silabs_config_client_set_network_pdu.pdu_max_size=pdu_max_size;

    cmd->header=sl_btmesh_cmd_silabs_config_client_set_network_pdu_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_silabs_config_client_set_network_pdu.result;

}

sl_status_t sl_btmesh_silabs_config_client_get_network_pdu(uint16_t server_address,
                                                           uint16_t appkey_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_silabs_config_client_get_network_pdu.server_address=server_address;
    cmd->data.cmd_silabs_config_client_get_network_pdu.appkey_index=appkey_index;

    cmd->header=sl_btmesh_cmd_silabs_config_client_get_network_pdu_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_silabs_config_client_get_network_pdu.result;

}

sl_status_t sl_btmesh_silabs_config_client_deinit() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_silabs_config_client_deinit_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_silabs_config_client_deinit.result;

}

sl_status_t sl_btmesh_vendor_model_send(uint16_t destination_address,
                                        int8_t va_index,
                                        uint16_t appkey_index,
                                        uint16_t elem_index,
                                        uint16_t vendor_id,
                                        uint16_t model_id,
                                        uint8_t nonrelayed,
                                        uint8_t opcode,
                                        uint8_t final,
                                        size_t payload_len,
                                        const uint8_t* payload) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_vendor_model_send.destination_address=destination_address;
    cmd->data.cmd_vendor_model_send.va_index=va_index;
    cmd->data.cmd_vendor_model_send.appkey_index=appkey_index;
    cmd->data.cmd_vendor_model_send.elem_index=elem_index;
    cmd->data.cmd_vendor_model_send.vendor_id=vendor_id;
    cmd->data.cmd_vendor_model_send.model_id=model_id;
    cmd->data.cmd_vendor_model_send.nonrelayed=nonrelayed;
    cmd->data.cmd_vendor_model_send.opcode=opcode;
    cmd->data.cmd_vendor_model_send.final=final;
    if ((15+payload_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_vendor_model_send.payload.len=payload_len;
    memcpy(cmd->data.cmd_vendor_model_send.payload.data,payload,payload_len);

    cmd->header=sl_btmesh_cmd_vendor_model_send_id+(((15+payload_len)&0xff)<<8)+(((15+payload_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_vendor_model_send.result;

}

sl_status_t sl_btmesh_vendor_model_set_publication(uint16_t elem_index,
                                                   uint16_t vendor_id,
                                                   uint16_t model_id,
                                                   uint8_t opcode,
                                                   uint8_t final,
                                                   size_t payload_len,
                                                   const uint8_t* payload) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_vendor_model_set_publication.elem_index=elem_index;
    cmd->data.cmd_vendor_model_set_publication.vendor_id=vendor_id;
    cmd->data.cmd_vendor_model_set_publication.model_id=model_id;
    cmd->data.cmd_vendor_model_set_publication.opcode=opcode;
    cmd->data.cmd_vendor_model_set_publication.final=final;
    if ((9+payload_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_vendor_model_set_publication.payload.len=payload_len;
    memcpy(cmd->data.cmd_vendor_model_set_publication.payload.data,payload,payload_len);

    cmd->header=sl_btmesh_cmd_vendor_model_set_publication_id+(((9+payload_len)&0xff)<<8)+(((9+payload_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_vendor_model_set_publication.result;

}

sl_status_t sl_btmesh_vendor_model_clear_publication(uint16_t elem_index,
                                                     uint16_t vendor_id,
                                                     uint16_t model_id) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_vendor_model_clear_publication.elem_index=elem_index;
    cmd->data.cmd_vendor_model_clear_publication.vendor_id=vendor_id;
    cmd->data.cmd_vendor_model_clear_publication.model_id=model_id;

    cmd->header=sl_btmesh_cmd_vendor_model_clear_publication_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_vendor_model_clear_publication.result;

}

sl_status_t sl_btmesh_vendor_model_publish(uint16_t elem_index,
                                           uint16_t vendor_id,
                                           uint16_t model_id) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_vendor_model_publish.elem_index=elem_index;
    cmd->data.cmd_vendor_model_publish.vendor_id=vendor_id;
    cmd->data.cmd_vendor_model_publish.model_id=model_id;

    cmd->header=sl_btmesh_cmd_vendor_model_publish_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_vendor_model_publish.result;

}

sl_status_t sl_btmesh_vendor_model_init(uint16_t elem_index,
                                        uint16_t vendor_id,
                                        uint16_t model_id,
                                        uint8_t publish,
                                        size_t opcodes_len,
                                        const uint8_t* opcodes) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_vendor_model_init.elem_index=elem_index;
    cmd->data.cmd_vendor_model_init.vendor_id=vendor_id;
    cmd->data.cmd_vendor_model_init.model_id=model_id;
    cmd->data.cmd_vendor_model_init.publish=publish;
    if ((8+opcodes_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_vendor_model_init.opcodes.len=opcodes_len;
    memcpy(cmd->data.cmd_vendor_model_init.opcodes.data,opcodes,opcodes_len);

    cmd->header=sl_btmesh_cmd_vendor_model_init_id+(((8+opcodes_len)&0xff)<<8)+(((8+opcodes_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_vendor_model_init.result;

}

sl_status_t sl_btmesh_vendor_model_deinit(uint16_t elem_index,
                                          uint16_t vendor_id,
                                          uint16_t model_id) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_vendor_model_deinit.elem_index=elem_index;
    cmd->data.cmd_vendor_model_deinit.vendor_id=vendor_id;
    cmd->data.cmd_vendor_model_deinit.model_id=model_id;

    cmd->header=sl_btmesh_cmd_vendor_model_deinit_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_vendor_model_deinit.result;

}

sl_status_t sl_btmesh_vendor_model_send_tracked(uint16_t destination_address,
                                                int8_t va_index,
                                                uint16_t appkey_index,
                                                uint16_t elem_index,
                                                uint16_t vendor_id,
                                                uint16_t model_id,
                                                uint8_t nonrelayed,
                                                uint8_t segment,
                                                uint8_t opcode,
                                                uint8_t final,
                                                size_t payload_len,
                                                const uint8_t* payload,
                                                uint16_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_vendor_model_send_tracked.destination_address=destination_address;
    cmd->data.cmd_vendor_model_send_tracked.va_index=va_index;
    cmd->data.cmd_vendor_model_send_tracked.appkey_index=appkey_index;
    cmd->data.cmd_vendor_model_send_tracked.elem_index=elem_index;
    cmd->data.cmd_vendor_model_send_tracked.vendor_id=vendor_id;
    cmd->data.cmd_vendor_model_send_tracked.model_id=model_id;
    cmd->data.cmd_vendor_model_send_tracked.nonrelayed=nonrelayed;
    cmd->data.cmd_vendor_model_send_tracked.segment=segment;
    cmd->data.cmd_vendor_model_send_tracked.opcode=opcode;
    cmd->data.cmd_vendor_model_send_tracked.final=final;
    if ((16+payload_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_vendor_model_send_tracked.payload.len=payload_len;
    memcpy(cmd->data.cmd_vendor_model_send_tracked.payload.data,payload,payload_len);

    cmd->header=sl_btmesh_cmd_vendor_model_send_tracked_id+(((16+payload_len)&0xff)<<8)+(((16+payload_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_vendor_model_send_tracked.handle;
    }
    return rsp->data.rsp_vendor_model_send_tracked.result;

}

sl_status_t sl_btmesh_vendor_model_set_publication_tracked(uint16_t elem_index,
                                                           uint16_t vendor_id,
                                                           uint16_t model_id,
                                                           uint8_t segment,
                                                           uint8_t opcode,
                                                           uint8_t final,
                                                           size_t payload_len,
                                                           const uint8_t* payload,
                                                           uint16_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_vendor_model_set_publication_tracked.elem_index=elem_index;
    cmd->data.cmd_vendor_model_set_publication_tracked.vendor_id=vendor_id;
    cmd->data.cmd_vendor_model_set_publication_tracked.model_id=model_id;
    cmd->data.cmd_vendor_model_set_publication_tracked.segment=segment;
    cmd->data.cmd_vendor_model_set_publication_tracked.opcode=opcode;
    cmd->data.cmd_vendor_model_set_publication_tracked.final=final;
    if ((10+payload_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_vendor_model_set_publication_tracked.payload.len=payload_len;
    memcpy(cmd->data.cmd_vendor_model_set_publication_tracked.payload.data,payload,payload_len);

    cmd->header=sl_btmesh_cmd_vendor_model_set_publication_tracked_id+(((10+payload_len)&0xff)<<8)+(((10+payload_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_vendor_model_set_publication_tracked.handle;
    }
    return rsp->data.rsp_vendor_model_set_publication_tracked.result;

}

sl_status_t sl_btmesh_health_client_init() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_health_client_init_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_health_client_init.result;

}

sl_status_t sl_btmesh_health_client_deinit() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_health_client_deinit_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_health_client_deinit.result;

}

sl_status_t sl_btmesh_health_client_get(uint16_t server_address,
                                        uint16_t elem_index,
                                        uint16_t appkey_index,
                                        uint16_t vendor_id) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_health_client_get.server_address=server_address;
    cmd->data.cmd_health_client_get.elem_index=elem_index;
    cmd->data.cmd_health_client_get.appkey_index=appkey_index;
    cmd->data.cmd_health_client_get.vendor_id=vendor_id;

    cmd->header=sl_btmesh_cmd_health_client_get_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_health_client_get.result;

}

sl_status_t sl_btmesh_health_client_clear(uint16_t server_address,
                                          uint16_t elem_index,
                                          uint16_t appkey_index,
                                          uint16_t vendor_id,
                                          uint8_t reliable) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_health_client_clear.server_address=server_address;
    cmd->data.cmd_health_client_clear.elem_index=elem_index;
    cmd->data.cmd_health_client_clear.appkey_index=appkey_index;
    cmd->data.cmd_health_client_clear.vendor_id=vendor_id;
    cmd->data.cmd_health_client_clear.reliable=reliable;

    cmd->header=sl_btmesh_cmd_health_client_clear_id+(((9)&0xff)<<8)+(((9)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_health_client_clear.result;

}

sl_status_t sl_btmesh_health_client_test(uint16_t server_address,
                                         uint16_t elem_index,
                                         uint16_t appkey_index,
                                         uint8_t test_id,
                                         uint16_t vendor_id,
                                         uint8_t reliable) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_health_client_test.server_address=server_address;
    cmd->data.cmd_health_client_test.elem_index=elem_index;
    cmd->data.cmd_health_client_test.appkey_index=appkey_index;
    cmd->data.cmd_health_client_test.test_id=test_id;
    cmd->data.cmd_health_client_test.vendor_id=vendor_id;
    cmd->data.cmd_health_client_test.reliable=reliable;

    cmd->header=sl_btmesh_cmd_health_client_test_id+(((10)&0xff)<<8)+(((10)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_health_client_test.result;

}

sl_status_t sl_btmesh_health_client_get_period(uint16_t server_address,
                                               uint16_t elem_index,
                                               uint16_t appkey_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_health_client_get_period.server_address=server_address;
    cmd->data.cmd_health_client_get_period.elem_index=elem_index;
    cmd->data.cmd_health_client_get_period.appkey_index=appkey_index;

    cmd->header=sl_btmesh_cmd_health_client_get_period_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_health_client_get_period.result;

}

sl_status_t sl_btmesh_health_client_set_period(uint16_t server_address,
                                               uint16_t elem_index,
                                               uint16_t appkey_index,
                                               uint8_t period,
                                               uint8_t reliable) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_health_client_set_period.server_address=server_address;
    cmd->data.cmd_health_client_set_period.elem_index=elem_index;
    cmd->data.cmd_health_client_set_period.appkey_index=appkey_index;
    cmd->data.cmd_health_client_set_period.period=period;
    cmd->data.cmd_health_client_set_period.reliable=reliable;

    cmd->header=sl_btmesh_cmd_health_client_set_period_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_health_client_set_period.result;

}

sl_status_t sl_btmesh_health_client_get_attention(uint16_t server_address,
                                                  uint16_t elem_index,
                                                  uint16_t appkey_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_health_client_get_attention.server_address=server_address;
    cmd->data.cmd_health_client_get_attention.elem_index=elem_index;
    cmd->data.cmd_health_client_get_attention.appkey_index=appkey_index;

    cmd->header=sl_btmesh_cmd_health_client_get_attention_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_health_client_get_attention.result;

}

sl_status_t sl_btmesh_health_client_set_attention(uint16_t server_address,
                                                  uint16_t elem_index,
                                                  uint16_t appkey_index,
                                                  uint8_t attention_sec,
                                                  uint8_t reliable) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_health_client_set_attention.server_address=server_address;
    cmd->data.cmd_health_client_set_attention.elem_index=elem_index;
    cmd->data.cmd_health_client_set_attention.appkey_index=appkey_index;
    cmd->data.cmd_health_client_set_attention.attention_sec=attention_sec;
    cmd->data.cmd_health_client_set_attention.reliable=reliable;

    cmd->header=sl_btmesh_cmd_health_client_set_attention_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_health_client_set_attention.result;

}

sl_status_t sl_btmesh_health_server_set_fault(uint16_t elem_index, uint8_t id) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_health_server_set_fault.elem_index=elem_index;
    cmd->data.cmd_health_server_set_fault.id=id;

    cmd->header=sl_btmesh_cmd_health_server_set_fault_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_health_server_set_fault.result;

}

sl_status_t sl_btmesh_health_server_clear_fault(uint16_t elem_index,
                                                uint8_t id) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_health_server_clear_fault.elem_index=elem_index;
    cmd->data.cmd_health_server_clear_fault.id=id;

    cmd->header=sl_btmesh_cmd_health_server_clear_fault_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_health_server_clear_fault.result;

}

sl_status_t sl_btmesh_health_server_send_test_response(uint16_t client_address,
                                                       uint16_t elem_index,
                                                       uint16_t appkey_index,
                                                       uint16_t vendor_id) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_health_server_send_test_response.client_address=client_address;
    cmd->data.cmd_health_server_send_test_response.elem_index=elem_index;
    cmd->data.cmd_health_server_send_test_response.appkey_index=appkey_index;
    cmd->data.cmd_health_server_send_test_response.vendor_id=vendor_id;

    cmd->header=sl_btmesh_cmd_health_server_send_test_response_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_health_server_send_test_response.result;

}

sl_status_t sl_btmesh_generic_client_get(uint16_t server_address,
                                         uint16_t elem_index,
                                         uint16_t model_id,
                                         uint16_t appkey_index,
                                         uint8_t type) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_generic_client_get.server_address=server_address;
    cmd->data.cmd_generic_client_get.elem_index=elem_index;
    cmd->data.cmd_generic_client_get.model_id=model_id;
    cmd->data.cmd_generic_client_get.appkey_index=appkey_index;
    cmd->data.cmd_generic_client_get.type=type;

    cmd->header=sl_btmesh_cmd_generic_client_get_id+(((9)&0xff)<<8)+(((9)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_client_get.result;

}

sl_status_t sl_btmesh_generic_client_set(uint16_t server_address,
                                         uint16_t elem_index,
                                         uint16_t model_id,
                                         uint16_t appkey_index,
                                         uint8_t tid,
                                         uint32_t transition_ms,
                                         uint16_t delay_ms,
                                         uint16_t flags,
                                         uint8_t type,
                                         size_t parameters_len,
                                         const uint8_t* parameters) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_generic_client_set.server_address=server_address;
    cmd->data.cmd_generic_client_set.elem_index=elem_index;
    cmd->data.cmd_generic_client_set.model_id=model_id;
    cmd->data.cmd_generic_client_set.appkey_index=appkey_index;
    cmd->data.cmd_generic_client_set.tid=tid;
    cmd->data.cmd_generic_client_set.transition_ms=transition_ms;
    cmd->data.cmd_generic_client_set.delay_ms=delay_ms;
    cmd->data.cmd_generic_client_set.flags=flags;
    cmd->data.cmd_generic_client_set.type=type;
    if ((19+parameters_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_generic_client_set.parameters.len=parameters_len;
    memcpy(cmd->data.cmd_generic_client_set.parameters.data,parameters,parameters_len);

    cmd->header=sl_btmesh_cmd_generic_client_set_id+(((19+parameters_len)&0xff)<<8)+(((19+parameters_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_client_set.result;

}

sl_status_t sl_btmesh_generic_client_publish(uint16_t elem_index,
                                             uint16_t model_id,
                                             uint8_t tid,
                                             uint32_t transition_ms,
                                             uint16_t delay_ms,
                                             uint16_t flags,
                                             uint8_t type,
                                             size_t parameters_len,
                                             const uint8_t* parameters) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_generic_client_publish.elem_index=elem_index;
    cmd->data.cmd_generic_client_publish.model_id=model_id;
    cmd->data.cmd_generic_client_publish.tid=tid;
    cmd->data.cmd_generic_client_publish.transition_ms=transition_ms;
    cmd->data.cmd_generic_client_publish.delay_ms=delay_ms;
    cmd->data.cmd_generic_client_publish.flags=flags;
    cmd->data.cmd_generic_client_publish.type=type;
    if ((15+parameters_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_generic_client_publish.parameters.len=parameters_len;
    memcpy(cmd->data.cmd_generic_client_publish.parameters.data,parameters,parameters_len);

    cmd->header=sl_btmesh_cmd_generic_client_publish_id+(((15+parameters_len)&0xff)<<8)+(((15+parameters_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_client_publish.result;

}

sl_status_t sl_btmesh_generic_client_get_params(uint16_t server_address,
                                                uint16_t elem_index,
                                                uint16_t model_id,
                                                uint16_t appkey_index,
                                                uint8_t type,
                                                size_t parameters_len,
                                                const uint8_t* parameters) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_generic_client_get_params.server_address=server_address;
    cmd->data.cmd_generic_client_get_params.elem_index=elem_index;
    cmd->data.cmd_generic_client_get_params.model_id=model_id;
    cmd->data.cmd_generic_client_get_params.appkey_index=appkey_index;
    cmd->data.cmd_generic_client_get_params.type=type;
    if ((10+parameters_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_generic_client_get_params.parameters.len=parameters_len;
    memcpy(cmd->data.cmd_generic_client_get_params.parameters.data,parameters,parameters_len);

    cmd->header=sl_btmesh_cmd_generic_client_get_params_id+(((10+parameters_len)&0xff)<<8)+(((10+parameters_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_client_get_params.result;

}

sl_status_t sl_btmesh_generic_client_init() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_generic_client_init_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_client_init.result;

}

sl_status_t sl_btmesh_generic_client_init_common() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_generic_client_init_common_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_client_init_common.result;

}

sl_status_t sl_btmesh_generic_client_init_on_off() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_generic_client_init_on_off_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_client_init_on_off.result;

}

sl_status_t sl_btmesh_generic_client_init_level() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_generic_client_init_level_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_client_init_level.result;

}

sl_status_t sl_btmesh_generic_client_init_default_transition_time() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_generic_client_init_default_transition_time_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_client_init_default_transition_time.result;

}

sl_status_t sl_btmesh_generic_client_init_power_on_off() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_generic_client_init_power_on_off_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_client_init_power_on_off.result;

}

sl_status_t sl_btmesh_generic_client_init_power_level() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_generic_client_init_power_level_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_client_init_power_level.result;

}

sl_status_t sl_btmesh_generic_client_init_battery() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_generic_client_init_battery_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_client_init_battery.result;

}

sl_status_t sl_btmesh_generic_client_init_location() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_generic_client_init_location_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_client_init_location.result;

}

sl_status_t sl_btmesh_generic_client_init_property() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_generic_client_init_property_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_client_init_property.result;

}

sl_status_t sl_btmesh_generic_client_init_lightness() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_generic_client_init_lightness_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_client_init_lightness.result;

}

sl_status_t sl_btmesh_generic_client_init_ctl() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_generic_client_init_ctl_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_client_init_ctl.result;

}

sl_status_t sl_btmesh_generic_client_init_hsl() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_generic_client_init_hsl_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_client_init_hsl.result;

}

sl_status_t sl_btmesh_generic_server_respond(uint16_t client_address,
                                             uint16_t elem_index,
                                             uint16_t model_id,
                                             uint16_t appkey_index,
                                             uint32_t remaining_ms,
                                             uint16_t flags,
                                             uint8_t type,
                                             size_t parameters_len,
                                             const uint8_t* parameters) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_generic_server_respond.client_address=client_address;
    cmd->data.cmd_generic_server_respond.elem_index=elem_index;
    cmd->data.cmd_generic_server_respond.model_id=model_id;
    cmd->data.cmd_generic_server_respond.appkey_index=appkey_index;
    cmd->data.cmd_generic_server_respond.remaining_ms=remaining_ms;
    cmd->data.cmd_generic_server_respond.flags=flags;
    cmd->data.cmd_generic_server_respond.type=type;
    if ((16+parameters_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_generic_server_respond.parameters.len=parameters_len;
    memcpy(cmd->data.cmd_generic_server_respond.parameters.data,parameters,parameters_len);

    cmd->header=sl_btmesh_cmd_generic_server_respond_id+(((16+parameters_len)&0xff)<<8)+(((16+parameters_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_server_respond.result;

}

sl_status_t sl_btmesh_generic_server_update(uint16_t elem_index,
                                            uint16_t model_id,
                                            uint32_t remaining_ms,
                                            uint8_t type,
                                            size_t parameters_len,
                                            const uint8_t* parameters) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_generic_server_update.elem_index=elem_index;
    cmd->data.cmd_generic_server_update.model_id=model_id;
    cmd->data.cmd_generic_server_update.remaining_ms=remaining_ms;
    cmd->data.cmd_generic_server_update.type=type;
    if ((10+parameters_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_generic_server_update.parameters.len=parameters_len;
    memcpy(cmd->data.cmd_generic_server_update.parameters.data,parameters,parameters_len);

    cmd->header=sl_btmesh_cmd_generic_server_update_id+(((10+parameters_len)&0xff)<<8)+(((10+parameters_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_server_update.result;

}

sl_status_t sl_btmesh_generic_server_publish(uint16_t elem_index,
                                             uint16_t model_id,
                                             uint8_t type) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_generic_server_publish.elem_index=elem_index;
    cmd->data.cmd_generic_server_publish.model_id=model_id;
    cmd->data.cmd_generic_server_publish.type=type;

    cmd->header=sl_btmesh_cmd_generic_server_publish_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_server_publish.result;

}

sl_status_t sl_btmesh_generic_server_init() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_generic_server_init_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_server_init.result;

}

sl_status_t sl_btmesh_generic_server_init_common() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_generic_server_init_common_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_server_init_common.result;

}

sl_status_t sl_btmesh_generic_server_init_on_off() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_generic_server_init_on_off_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_server_init_on_off.result;

}

sl_status_t sl_btmesh_generic_server_init_level() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_generic_server_init_level_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_server_init_level.result;

}

sl_status_t sl_btmesh_generic_server_init_default_transition_time() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_generic_server_init_default_transition_time_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_server_init_default_transition_time.result;

}

sl_status_t sl_btmesh_generic_server_init_power_on_off() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_generic_server_init_power_on_off_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_server_init_power_on_off.result;

}

sl_status_t sl_btmesh_generic_server_init_power_level() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_generic_server_init_power_level_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_server_init_power_level.result;

}

sl_status_t sl_btmesh_generic_server_init_battery() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_generic_server_init_battery_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_server_init_battery.result;

}

sl_status_t sl_btmesh_generic_server_init_location() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_generic_server_init_location_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_server_init_location.result;

}

sl_status_t sl_btmesh_generic_server_init_property() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_generic_server_init_property_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_server_init_property.result;

}

sl_status_t sl_btmesh_generic_server_init_lightness() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_generic_server_init_lightness_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_server_init_lightness.result;

}

sl_status_t sl_btmesh_generic_server_init_ctl() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_generic_server_init_ctl_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_server_init_ctl.result;

}

sl_status_t sl_btmesh_generic_server_init_hsl() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_generic_server_init_hsl_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_generic_server_init_hsl.result;

}

sl_status_t sl_btmesh_generic_server_get_cached_state(uint16_t elem_index,
                                                      uint16_t model_id,
                                                      uint8_t type,
                                                      uint32_t *remaining_ms,
                                                      size_t max_parameters_size,
                                                      size_t *parameters_len,
                                                      uint8_t *parameters) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_generic_server_get_cached_state.elem_index=elem_index;
    cmd->data.cmd_generic_server_get_cached_state.model_id=model_id;
    cmd->data.cmd_generic_server_get_cached_state.type=type;

    cmd->header=sl_btmesh_cmd_generic_server_get_cached_state_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (remaining_ms) {
        *remaining_ms = rsp->data.rsp_generic_server_get_cached_state.remaining_ms;
    }
    if (parameters_len) {
        *parameters_len = rsp->data.rsp_generic_server_get_cached_state.parameters.len;
    }
    if (parameters && (rsp->data.rsp_generic_server_get_cached_state.parameters.len <= max_parameters_size)) {
        memcpy(parameters,rsp->data.rsp_generic_server_get_cached_state.parameters.data,rsp->data.rsp_generic_server_get_cached_state.parameters.len);
    }
    return rsp->data.rsp_generic_server_get_cached_state.result;

}

sl_status_t sl_btmesh_test_get_nettx(uint8_t *count, uint8_t *interval) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_test_get_nettx_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (count) {
        *count = rsp->data.rsp_test_get_nettx.count;
    }
    if (interval) {
        *interval = rsp->data.rsp_test_get_nettx.interval;
    }
    return rsp->data.rsp_test_get_nettx.result;

}

sl_status_t sl_btmesh_test_set_nettx(uint8_t count, uint8_t interval) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_set_nettx.count=count;
    cmd->data.cmd_test_set_nettx.interval=interval;

    cmd->header=sl_btmesh_cmd_test_set_nettx_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_set_nettx.result;

}

sl_status_t sl_btmesh_test_get_relay(uint8_t *enabled,
                                     uint8_t *count,
                                     uint8_t *interval) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_test_get_relay_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (enabled) {
        *enabled = rsp->data.rsp_test_get_relay.enabled;
    }
    if (count) {
        *count = rsp->data.rsp_test_get_relay.count;
    }
    if (interval) {
        *interval = rsp->data.rsp_test_get_relay.interval;
    }
    return rsp->data.rsp_test_get_relay.result;

}

sl_status_t sl_btmesh_test_set_relay(uint8_t enabled,
                                     uint8_t count,
                                     uint8_t interval) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_set_relay.enabled=enabled;
    cmd->data.cmd_test_set_relay.count=count;
    cmd->data.cmd_test_set_relay.interval=interval;

    cmd->header=sl_btmesh_cmd_test_set_relay_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_set_relay.result;

}

SL_BGAPI_DEPRECATED sl_status_t sl_btmesh_test_set_adv_scan_params(uint16_t adv_interval_min,
                                               uint16_t adv_interval_max,
                                               uint8_t adv_repeat_packets,
                                               uint8_t adv_use_random_address,
                                               uint8_t adv_channel_map,
                                               uint16_t scan_interval,
                                               uint16_t scan_window) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_set_adv_scan_params.adv_interval_min=adv_interval_min;
    cmd->data.cmd_test_set_adv_scan_params.adv_interval_max=adv_interval_max;
    cmd->data.cmd_test_set_adv_scan_params.adv_repeat_packets=adv_repeat_packets;
    cmd->data.cmd_test_set_adv_scan_params.adv_use_random_address=adv_use_random_address;
    cmd->data.cmd_test_set_adv_scan_params.adv_channel_map=adv_channel_map;
    cmd->data.cmd_test_set_adv_scan_params.scan_interval=scan_interval;
    cmd->data.cmd_test_set_adv_scan_params.scan_window=scan_window;

    cmd->header=sl_btmesh_cmd_test_set_adv_scan_params_id+(((11)&0xff)<<8)+(((11)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_set_adv_scan_params.result;

}

sl_status_t sl_btmesh_test_set_ivupdate_test_mode(uint8_t mode) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_set_ivupdate_test_mode.mode=mode;

    cmd->header=sl_btmesh_cmd_test_set_ivupdate_test_mode_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_set_ivupdate_test_mode.result;

}

sl_status_t sl_btmesh_test_get_ivupdate_test_mode(uint8_t *mode) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_test_get_ivupdate_test_mode_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (mode) {
        *mode = rsp->data.rsp_test_get_ivupdate_test_mode.mode;
    }
    return rsp->data.rsp_test_get_ivupdate_test_mode.result;

}

sl_status_t sl_btmesh_test_set_segment_send_delay(uint8_t delay) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_set_segment_send_delay.delay=delay;

    cmd->header=sl_btmesh_cmd_test_set_segment_send_delay_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_set_segment_send_delay.result;

}

sl_status_t sl_btmesh_test_set_ivupdate_state(uint8_t state) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_set_ivupdate_state.state=state;

    cmd->header=sl_btmesh_cmd_test_set_ivupdate_state_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_set_ivupdate_state.result;

}

sl_status_t sl_btmesh_test_send_beacons() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_test_send_beacons_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_send_beacons.result;

}

sl_status_t sl_btmesh_test_bind_local_model_app(uint16_t elem_index,
                                                uint16_t appkey_index,
                                                uint16_t vendor_id,
                                                uint16_t model_id) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_bind_local_model_app.elem_index=elem_index;
    cmd->data.cmd_test_bind_local_model_app.appkey_index=appkey_index;
    cmd->data.cmd_test_bind_local_model_app.vendor_id=vendor_id;
    cmd->data.cmd_test_bind_local_model_app.model_id=model_id;

    cmd->header=sl_btmesh_cmd_test_bind_local_model_app_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_bind_local_model_app.result;

}

sl_status_t sl_btmesh_test_unbind_local_model_app(uint16_t elem_index,
                                                  uint16_t appkey_index,
                                                  uint16_t vendor_id,
                                                  uint16_t model_id) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_unbind_local_model_app.elem_index=elem_index;
    cmd->data.cmd_test_unbind_local_model_app.appkey_index=appkey_index;
    cmd->data.cmd_test_unbind_local_model_app.vendor_id=vendor_id;
    cmd->data.cmd_test_unbind_local_model_app.model_id=model_id;

    cmd->header=sl_btmesh_cmd_test_unbind_local_model_app_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_unbind_local_model_app.result;

}

sl_status_t sl_btmesh_test_add_local_model_sub(uint16_t elem_index,
                                               uint16_t vendor_id,
                                               uint16_t model_id,
                                               uint16_t sub_address) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_add_local_model_sub.elem_index=elem_index;
    cmd->data.cmd_test_add_local_model_sub.vendor_id=vendor_id;
    cmd->data.cmd_test_add_local_model_sub.model_id=model_id;
    cmd->data.cmd_test_add_local_model_sub.sub_address=sub_address;

    cmd->header=sl_btmesh_cmd_test_add_local_model_sub_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_add_local_model_sub.result;

}

sl_status_t sl_btmesh_test_remove_local_model_sub(uint16_t elem_index,
                                                  uint16_t vendor_id,
                                                  uint16_t model_id,
                                                  uint16_t sub_address) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_remove_local_model_sub.elem_index=elem_index;
    cmd->data.cmd_test_remove_local_model_sub.vendor_id=vendor_id;
    cmd->data.cmd_test_remove_local_model_sub.model_id=model_id;
    cmd->data.cmd_test_remove_local_model_sub.sub_address=sub_address;

    cmd->header=sl_btmesh_cmd_test_remove_local_model_sub_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_remove_local_model_sub.result;

}

sl_status_t sl_btmesh_test_add_local_model_sub_va(uint16_t elem_index,
                                                  uint16_t vendor_id,
                                                  uint16_t model_id,
                                                  size_t sub_address_len,
                                                  const uint8_t* sub_address) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_add_local_model_sub_va.elem_index=elem_index;
    cmd->data.cmd_test_add_local_model_sub_va.vendor_id=vendor_id;
    cmd->data.cmd_test_add_local_model_sub_va.model_id=model_id;
    if ((7+sub_address_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_test_add_local_model_sub_va.sub_address.len=sub_address_len;
    memcpy(cmd->data.cmd_test_add_local_model_sub_va.sub_address.data,sub_address,sub_address_len);

    cmd->header=sl_btmesh_cmd_test_add_local_model_sub_va_id+(((7+sub_address_len)&0xff)<<8)+(((7+sub_address_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_add_local_model_sub_va.result;

}

sl_status_t sl_btmesh_test_remove_local_model_sub_va(uint16_t elem_index,
                                                     uint16_t vendor_id,
                                                     uint16_t model_id,
                                                     size_t sub_address_len,
                                                     const uint8_t* sub_address) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_remove_local_model_sub_va.elem_index=elem_index;
    cmd->data.cmd_test_remove_local_model_sub_va.vendor_id=vendor_id;
    cmd->data.cmd_test_remove_local_model_sub_va.model_id=model_id;
    if ((7+sub_address_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_test_remove_local_model_sub_va.sub_address.len=sub_address_len;
    memcpy(cmd->data.cmd_test_remove_local_model_sub_va.sub_address.data,sub_address,sub_address_len);

    cmd->header=sl_btmesh_cmd_test_remove_local_model_sub_va_id+(((7+sub_address_len)&0xff)<<8)+(((7+sub_address_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_remove_local_model_sub_va.result;

}

sl_status_t sl_btmesh_test_get_local_model_sub(uint16_t elem_index,
                                               uint16_t vendor_id,
                                               uint16_t model_id,
                                               size_t max_addresses_size,
                                               size_t *addresses_len,
                                               uint8_t *addresses) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_get_local_model_sub.elem_index=elem_index;
    cmd->data.cmd_test_get_local_model_sub.vendor_id=vendor_id;
    cmd->data.cmd_test_get_local_model_sub.model_id=model_id;

    cmd->header=sl_btmesh_cmd_test_get_local_model_sub_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (addresses_len) {
        *addresses_len = rsp->data.rsp_test_get_local_model_sub.addresses.len;
    }
    if (addresses && (rsp->data.rsp_test_get_local_model_sub.addresses.len <= max_addresses_size)) {
        memcpy(addresses,rsp->data.rsp_test_get_local_model_sub.addresses.data,rsp->data.rsp_test_get_local_model_sub.addresses.len);
    }
    return rsp->data.rsp_test_get_local_model_sub.result;

}

sl_status_t sl_btmesh_test_set_local_model_pub(uint16_t elem_index,
                                               uint16_t appkey_index,
                                               uint16_t vendor_id,
                                               uint16_t model_id,
                                               uint16_t pub_address,
                                               uint8_t ttl,
                                               uint8_t period,
                                               uint8_t retrans,
                                               uint8_t credentials) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_set_local_model_pub.elem_index=elem_index;
    cmd->data.cmd_test_set_local_model_pub.appkey_index=appkey_index;
    cmd->data.cmd_test_set_local_model_pub.vendor_id=vendor_id;
    cmd->data.cmd_test_set_local_model_pub.model_id=model_id;
    cmd->data.cmd_test_set_local_model_pub.pub_address=pub_address;
    cmd->data.cmd_test_set_local_model_pub.ttl=ttl;
    cmd->data.cmd_test_set_local_model_pub.period=period;
    cmd->data.cmd_test_set_local_model_pub.retrans=retrans;
    cmd->data.cmd_test_set_local_model_pub.credentials=credentials;

    cmd->header=sl_btmesh_cmd_test_set_local_model_pub_id+(((14)&0xff)<<8)+(((14)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_set_local_model_pub.result;

}

sl_status_t sl_btmesh_test_set_local_model_pub_va(uint16_t elem_index,
                                                  uint16_t appkey_index,
                                                  uint16_t vendor_id,
                                                  uint16_t model_id,
                                                  uint8_t ttl,
                                                  uint8_t period,
                                                  uint8_t retrans,
                                                  uint8_t credentials,
                                                  size_t pub_address_len,
                                                  const uint8_t* pub_address) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_set_local_model_pub_va.elem_index=elem_index;
    cmd->data.cmd_test_set_local_model_pub_va.appkey_index=appkey_index;
    cmd->data.cmd_test_set_local_model_pub_va.vendor_id=vendor_id;
    cmd->data.cmd_test_set_local_model_pub_va.model_id=model_id;
    cmd->data.cmd_test_set_local_model_pub_va.ttl=ttl;
    cmd->data.cmd_test_set_local_model_pub_va.period=period;
    cmd->data.cmd_test_set_local_model_pub_va.retrans=retrans;
    cmd->data.cmd_test_set_local_model_pub_va.credentials=credentials;
    if ((13+pub_address_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_test_set_local_model_pub_va.pub_address.len=pub_address_len;
    memcpy(cmd->data.cmd_test_set_local_model_pub_va.pub_address.data,pub_address,pub_address_len);

    cmd->header=sl_btmesh_cmd_test_set_local_model_pub_va_id+(((13+pub_address_len)&0xff)<<8)+(((13+pub_address_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_set_local_model_pub_va.result;

}

sl_status_t sl_btmesh_test_get_local_model_pub(uint16_t elem_index,
                                               uint16_t vendor_id,
                                               uint16_t model_id,
                                               uint16_t *appkey_index,
                                               uint16_t *pub_address,
                                               uint8_t *ttl,
                                               uint8_t *period,
                                               uint8_t *retrans,
                                               uint8_t *credentials) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_get_local_model_pub.elem_index=elem_index;
    cmd->data.cmd_test_get_local_model_pub.vendor_id=vendor_id;
    cmd->data.cmd_test_get_local_model_pub.model_id=model_id;

    cmd->header=sl_btmesh_cmd_test_get_local_model_pub_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (appkey_index) {
        *appkey_index = rsp->data.rsp_test_get_local_model_pub.appkey_index;
    }
    if (pub_address) {
        *pub_address = rsp->data.rsp_test_get_local_model_pub.pub_address;
    }
    if (ttl) {
        *ttl = rsp->data.rsp_test_get_local_model_pub.ttl;
    }
    if (period) {
        *period = rsp->data.rsp_test_get_local_model_pub.period;
    }
    if (retrans) {
        *retrans = rsp->data.rsp_test_get_local_model_pub.retrans;
    }
    if (credentials) {
        *credentials = rsp->data.rsp_test_get_local_model_pub.credentials;
    }
    return rsp->data.rsp_test_get_local_model_pub.result;

}

sl_status_t sl_btmesh_test_set_local_heartbeat_subscription(uint16_t subscription_source,
                                                            uint16_t subscription_destination,
                                                            uint8_t period_log) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_set_local_heartbeat_subscription.subscription_source=subscription_source;
    cmd->data.cmd_test_set_local_heartbeat_subscription.subscription_destination=subscription_destination;
    cmd->data.cmd_test_set_local_heartbeat_subscription.period_log=period_log;

    cmd->header=sl_btmesh_cmd_test_set_local_heartbeat_subscription_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_set_local_heartbeat_subscription.result;

}

sl_status_t sl_btmesh_test_get_local_heartbeat_subscription(uint16_t *count,
                                                            uint8_t *hop_min,
                                                            uint8_t *hop_max) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_test_get_local_heartbeat_subscription_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (count) {
        *count = rsp->data.rsp_test_get_local_heartbeat_subscription.count;
    }
    if (hop_min) {
        *hop_min = rsp->data.rsp_test_get_local_heartbeat_subscription.hop_min;
    }
    if (hop_max) {
        *hop_max = rsp->data.rsp_test_get_local_heartbeat_subscription.hop_max;
    }
    return rsp->data.rsp_test_get_local_heartbeat_subscription.result;

}

sl_status_t sl_btmesh_test_get_local_heartbeat_publication(uint16_t *publication_address,
                                                           uint8_t *count,
                                                           uint8_t *period_log,
                                                           uint8_t *ttl,
                                                           uint16_t *features,
                                                           uint16_t *publication_netkey_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_test_get_local_heartbeat_publication_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (publication_address) {
        *publication_address = rsp->data.rsp_test_get_local_heartbeat_publication.publication_address;
    }
    if (count) {
        *count = rsp->data.rsp_test_get_local_heartbeat_publication.count;
    }
    if (period_log) {
        *period_log = rsp->data.rsp_test_get_local_heartbeat_publication.period_log;
    }
    if (ttl) {
        *ttl = rsp->data.rsp_test_get_local_heartbeat_publication.ttl;
    }
    if (features) {
        *features = rsp->data.rsp_test_get_local_heartbeat_publication.features;
    }
    if (publication_netkey_index) {
        *publication_netkey_index = rsp->data.rsp_test_get_local_heartbeat_publication.publication_netkey_index;
    }
    return rsp->data.rsp_test_get_local_heartbeat_publication.result;

}

sl_status_t sl_btmesh_test_set_local_heartbeat_publication(uint16_t publication_address,
                                                           uint8_t count_log,
                                                           uint8_t period_log,
                                                           uint8_t ttl,
                                                           uint16_t features,
                                                           uint16_t publication_netkey_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_set_local_heartbeat_publication.publication_address=publication_address;
    cmd->data.cmd_test_set_local_heartbeat_publication.count_log=count_log;
    cmd->data.cmd_test_set_local_heartbeat_publication.period_log=period_log;
    cmd->data.cmd_test_set_local_heartbeat_publication.ttl=ttl;
    cmd->data.cmd_test_set_local_heartbeat_publication.features=features;
    cmd->data.cmd_test_set_local_heartbeat_publication.publication_netkey_index=publication_netkey_index;

    cmd->header=sl_btmesh_cmd_test_set_local_heartbeat_publication_id+(((9)&0xff)<<8)+(((9)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_set_local_heartbeat_publication.result;

}

SL_BGAPI_DEPRECATED sl_status_t sl_btmesh_test_set_local_config(uint16_t id,
                                            uint16_t netkey_index,
                                            size_t value_len,
                                            const uint8_t* value) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_set_local_config.id=id;
    cmd->data.cmd_test_set_local_config.netkey_index=netkey_index;
    if ((5+value_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_test_set_local_config.value.len=value_len;
    memcpy(cmd->data.cmd_test_set_local_config.value.data,value,value_len);

    cmd->header=sl_btmesh_cmd_test_set_local_config_id+(((5+value_len)&0xff)<<8)+(((5+value_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_set_local_config.result;

}

SL_BGAPI_DEPRECATED sl_status_t sl_btmesh_test_get_local_config(uint16_t id,
                                            uint16_t netkey_index,
                                            size_t max_data_size,
                                            size_t *data_len,
                                            uint8_t *data) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_get_local_config.id=id;
    cmd->data.cmd_test_get_local_config.netkey_index=netkey_index;

    cmd->header=sl_btmesh_cmd_test_get_local_config_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (data_len) {
        *data_len = rsp->data.rsp_test_get_local_config.data.len;
    }
    if (data && (rsp->data.rsp_test_get_local_config.data.len <= max_data_size)) {
        memcpy(data,rsp->data.rsp_test_get_local_config.data.data,rsp->data.rsp_test_get_local_config.data.len);
    }
    return rsp->data.rsp_test_get_local_config.result;

}

sl_status_t sl_btmesh_test_add_local_key(uint8_t key_type,
                                         aes_key_128 key,
                                         uint16_t key_index,
                                         uint16_t netkey_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_add_local_key.key_type=key_type;
    memcpy(&cmd->data.cmd_test_add_local_key.key,&key,sizeof(aes_key_128));
    cmd->data.cmd_test_add_local_key.key_index=key_index;
    cmd->data.cmd_test_add_local_key.netkey_index=netkey_index;

    cmd->header=sl_btmesh_cmd_test_add_local_key_id+(((21)&0xff)<<8)+(((21)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_add_local_key.result;

}

sl_status_t sl_btmesh_test_remove_local_key(uint8_t key_type,
                                            uint16_t key_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_remove_local_key.key_type=key_type;
    cmd->data.cmd_test_remove_local_key.key_index=key_index;

    cmd->header=sl_btmesh_cmd_test_remove_local_key_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_remove_local_key.result;

}

sl_status_t sl_btmesh_test_update_local_key(uint8_t key_type,
                                            aes_key_128 key,
                                            uint16_t key_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_update_local_key.key_type=key_type;
    memcpy(&cmd->data.cmd_test_update_local_key.key,&key,sizeof(aes_key_128));
    cmd->data.cmd_test_update_local_key.key_index=key_index;

    cmd->header=sl_btmesh_cmd_test_update_local_key_id+(((19)&0xff)<<8)+(((19)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_update_local_key.result;

}

sl_status_t sl_btmesh_test_set_sar_config(uint32_t incomplete_timer_ms,
                                          uint32_t pending_ack_base_ms,
                                          uint32_t pending_ack_mul_ms,
                                          uint32_t wait_for_ack_base_ms,
                                          uint32_t wait_for_ack_mul_ms,
                                          uint8_t max_send_rounds) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_set_sar_config.incomplete_timer_ms=incomplete_timer_ms;
    cmd->data.cmd_test_set_sar_config.pending_ack_base_ms=pending_ack_base_ms;
    cmd->data.cmd_test_set_sar_config.pending_ack_mul_ms=pending_ack_mul_ms;
    cmd->data.cmd_test_set_sar_config.wait_for_ack_base_ms=wait_for_ack_base_ms;
    cmd->data.cmd_test_set_sar_config.wait_for_ack_mul_ms=wait_for_ack_mul_ms;
    cmd->data.cmd_test_set_sar_config.max_send_rounds=max_send_rounds;

    cmd->header=sl_btmesh_cmd_test_set_sar_config_id+(((21)&0xff)<<8)+(((21)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_set_sar_config.result;

}

sl_status_t sl_btmesh_test_set_adv_bearer_state(uint8_t state) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_set_adv_bearer_state.state=state;

    cmd->header=sl_btmesh_cmd_test_set_adv_bearer_state_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_set_adv_bearer_state.result;

}

sl_status_t sl_btmesh_test_prov_get_device_key(uint16_t address,
                                               aes_key_128 *device_key) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_prov_get_device_key.address=address;

    cmd->header=sl_btmesh_cmd_test_prov_get_device_key_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (device_key) {
        memcpy(device_key,&rsp->data.rsp_test_prov_get_device_key.device_key,sizeof(aes_key_128));
    }
    return rsp->data.rsp_test_prov_get_device_key.result;

}

sl_status_t sl_btmesh_test_prov_prepare_key_refresh(aes_key_128 net_key,
                                                    size_t app_keys_len,
                                                    const uint8_t* app_keys) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    memcpy(&cmd->data.cmd_test_prov_prepare_key_refresh.net_key,&net_key,sizeof(aes_key_128));
    if ((17+app_keys_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_test_prov_prepare_key_refresh.app_keys.len=app_keys_len;
    memcpy(cmd->data.cmd_test_prov_prepare_key_refresh.app_keys.data,app_keys,app_keys_len);

    cmd->header=sl_btmesh_cmd_test_prov_prepare_key_refresh_id+(((17+app_keys_len)&0xff)<<8)+(((17+app_keys_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_prov_prepare_key_refresh.result;

}

sl_status_t sl_btmesh_test_cancel_segmented_tx(uint16_t src_addr,
                                               uint16_t dst_addr) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_cancel_segmented_tx.src_addr=src_addr;
    cmd->data.cmd_test_cancel_segmented_tx.dst_addr=dst_addr;

    cmd->header=sl_btmesh_cmd_test_cancel_segmented_tx_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_cancel_segmented_tx.result;

}

sl_status_t sl_btmesh_test_set_iv_index(uint32_t iv_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_set_iv_index.iv_index=iv_index;

    cmd->header=sl_btmesh_cmd_test_set_iv_index_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_set_iv_index.result;

}

sl_status_t sl_btmesh_test_set_element_seqnum(uint16_t elem_index,
                                              uint32_t seqnum) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_set_element_seqnum.elem_index=elem_index;
    cmd->data.cmd_test_set_element_seqnum.seqnum=seqnum;

    cmd->header=sl_btmesh_cmd_test_set_element_seqnum_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_set_element_seqnum.result;

}

sl_status_t sl_btmesh_test_set_model_option(uint16_t elem_index,
                                            uint16_t vendor_id,
                                            uint16_t model_id,
                                            uint8_t option,
                                            uint32_t value) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_set_model_option.elem_index=elem_index;
    cmd->data.cmd_test_set_model_option.vendor_id=vendor_id;
    cmd->data.cmd_test_set_model_option.model_id=model_id;
    cmd->data.cmd_test_set_model_option.option=option;
    cmd->data.cmd_test_set_model_option.value=value;

    cmd->header=sl_btmesh_cmd_test_set_model_option_id+(((11)&0xff)<<8)+(((11)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_set_model_option.result;

}

sl_status_t sl_btmesh_test_get_local_model_app_bindings(uint16_t elem_index,
                                                        uint16_t vendor_id,
                                                        uint16_t model_id,
                                                        size_t max_appkeys_size,
                                                        size_t *appkeys_len,
                                                        uint8_t *appkeys) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_get_local_model_app_bindings.elem_index=elem_index;
    cmd->data.cmd_test_get_local_model_app_bindings.vendor_id=vendor_id;
    cmd->data.cmd_test_get_local_model_app_bindings.model_id=model_id;

    cmd->header=sl_btmesh_cmd_test_get_local_model_app_bindings_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (appkeys_len) {
        *appkeys_len = rsp->data.rsp_test_get_local_model_app_bindings.appkeys.len;
    }
    if (appkeys && (rsp->data.rsp_test_get_local_model_app_bindings.appkeys.len <= max_appkeys_size)) {
        memcpy(appkeys,rsp->data.rsp_test_get_local_model_app_bindings.appkeys.data,rsp->data.rsp_test_get_local_model_app_bindings.appkeys.len);
    }
    return rsp->data.rsp_test_get_local_model_app_bindings.result;

}

sl_status_t sl_btmesh_test_get_replay_protection_list_entry(uint16_t address,
                                                            uint32_t *seq,
                                                            uint32_t *seq_ivindex) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_get_replay_protection_list_entry.address=address;

    cmd->header=sl_btmesh_cmd_test_get_replay_protection_list_entry_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (seq) {
        *seq = rsp->data.rsp_test_get_replay_protection_list_entry.seq;
    }
    if (seq_ivindex) {
        *seq_ivindex = rsp->data.rsp_test_get_replay_protection_list_entry.seq_ivindex;
    }
    return rsp->data.rsp_test_get_replay_protection_list_entry.result;

}

sl_status_t sl_btmesh_test_clear_replay_protection_list_entry(uint16_t address) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_clear_replay_protection_list_entry.address=address;

    cmd->header=sl_btmesh_cmd_test_clear_replay_protection_list_entry_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_clear_replay_protection_list_entry.result;

}

sl_status_t sl_btmesh_test_set_replay_protection_list_diagnostics(uint8_t enable) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_set_replay_protection_list_diagnostics.enable=enable;

    cmd->header=sl_btmesh_cmd_test_set_replay_protection_list_diagnostics_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_set_replay_protection_list_diagnostics.result;

}

sl_status_t sl_btmesh_test_get_model_option(uint16_t elem_index,
                                            uint16_t vendor_id,
                                            uint16_t model_id,
                                            uint8_t option,
                                            uint32_t *value) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_get_model_option.elem_index=elem_index;
    cmd->data.cmd_test_get_model_option.vendor_id=vendor_id;
    cmd->data.cmd_test_get_model_option.model_id=model_id;
    cmd->data.cmd_test_get_model_option.option=option;

    cmd->header=sl_btmesh_cmd_test_get_model_option_id+(((7)&0xff)<<8)+(((7)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (value) {
        *value = rsp->data.rsp_test_get_model_option.value;
    }
    return rsp->data.rsp_test_get_model_option.result;

}

sl_status_t sl_btmesh_test_get_default_ttl(uint8_t *value) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_test_get_default_ttl_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (value) {
        *value = rsp->data.rsp_test_get_default_ttl.value;
    }
    return rsp->data.rsp_test_get_default_ttl.result;

}

sl_status_t sl_btmesh_test_set_default_ttl(uint8_t set_value, uint8_t *value) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_set_default_ttl.set_value=set_value;

    cmd->header=sl_btmesh_cmd_test_set_default_ttl_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (value) {
        *value = rsp->data.rsp_test_set_default_ttl.value;
    }
    return rsp->data.rsp_test_set_default_ttl.result;

}

sl_status_t sl_btmesh_test_get_gatt_proxy(uint8_t *value) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_test_get_gatt_proxy_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (value) {
        *value = rsp->data.rsp_test_get_gatt_proxy.value;
    }
    return rsp->data.rsp_test_get_gatt_proxy.result;

}

sl_status_t sl_btmesh_test_set_gatt_proxy(uint8_t set_value, uint8_t *value) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_set_gatt_proxy.set_value=set_value;

    cmd->header=sl_btmesh_cmd_test_set_gatt_proxy_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (value) {
        *value = rsp->data.rsp_test_set_gatt_proxy.value;
    }
    return rsp->data.rsp_test_set_gatt_proxy.result;

}

sl_status_t sl_btmesh_test_get_identity(uint16_t get_netkey_index,
                                        uint16_t *netkey_index,
                                        uint8_t *value) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_get_identity.get_netkey_index=get_netkey_index;

    cmd->header=sl_btmesh_cmd_test_get_identity_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (netkey_index) {
        *netkey_index = rsp->data.rsp_test_get_identity.netkey_index;
    }
    if (value) {
        *value = rsp->data.rsp_test_get_identity.value;
    }
    return rsp->data.rsp_test_get_identity.result;

}

sl_status_t sl_btmesh_test_set_identity(uint16_t set_netkey_index,
                                        uint8_t set_value,
                                        uint16_t *netkey_index,
                                        uint8_t *value) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_set_identity.set_netkey_index=set_netkey_index;
    cmd->data.cmd_test_set_identity.set_value=set_value;

    cmd->header=sl_btmesh_cmd_test_set_identity_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (netkey_index) {
        *netkey_index = rsp->data.rsp_test_set_identity.netkey_index;
    }
    if (value) {
        *value = rsp->data.rsp_test_set_identity.value;
    }
    return rsp->data.rsp_test_set_identity.result;

}

sl_status_t sl_btmesh_test_get_friend(uint8_t *value) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_test_get_friend_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (value) {
        *value = rsp->data.rsp_test_get_friend.value;
    }
    return rsp->data.rsp_test_get_friend.result;

}

sl_status_t sl_btmesh_test_set_friend(uint8_t set_value, uint8_t *value) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_set_friend.set_value=set_value;

    cmd->header=sl_btmesh_cmd_test_set_friend_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (value) {
        *value = rsp->data.rsp_test_set_friend.value;
    }
    return rsp->data.rsp_test_set_friend.result;

}

sl_status_t sl_btmesh_test_get_beacon(uint8_t *value) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_test_get_beacon_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (value) {
        *value = rsp->data.rsp_test_get_beacon.value;
    }
    return rsp->data.rsp_test_get_beacon.result;

}

sl_status_t sl_btmesh_test_set_beacon(uint8_t set_value, uint8_t *value) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_set_beacon.set_value=set_value;

    cmd->header=sl_btmesh_cmd_test_set_beacon_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (value) {
        *value = rsp->data.rsp_test_set_beacon.value;
    }
    return rsp->data.rsp_test_set_beacon.result;

}

sl_status_t sl_btmesh_test_get_private_identity(uint16_t get_netkey_index,
                                                uint16_t *netkey_index,
                                                uint8_t *value) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_get_private_identity.get_netkey_index=get_netkey_index;

    cmd->header=sl_btmesh_cmd_test_get_private_identity_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (netkey_index) {
        *netkey_index = rsp->data.rsp_test_get_private_identity.netkey_index;
    }
    if (value) {
        *value = rsp->data.rsp_test_get_private_identity.value;
    }
    return rsp->data.rsp_test_get_private_identity.result;

}

sl_status_t sl_btmesh_test_set_private_identity(uint16_t set_netkey_index,
                                                uint8_t set_value,
                                                uint16_t *netkey_index,
                                                uint8_t *value) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_set_private_identity.set_netkey_index=set_netkey_index;
    cmd->data.cmd_test_set_private_identity.set_value=set_value;

    cmd->header=sl_btmesh_cmd_test_set_private_identity_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (netkey_index) {
        *netkey_index = rsp->data.rsp_test_set_private_identity.netkey_index;
    }
    if (value) {
        *value = rsp->data.rsp_test_set_private_identity.value;
    }
    return rsp->data.rsp_test_set_private_identity.result;

}

sl_status_t sl_btmesh_test_set_adv_provisioning_bearer_timing(uint16_t pbadv_interval_ms,
                                                              uint16_t pbadv_variation_ms) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_set_adv_provisioning_bearer_timing.pbadv_interval_ms=pbadv_interval_ms;
    cmd->data.cmd_test_set_adv_provisioning_bearer_timing.pbadv_variation_ms=pbadv_variation_ms;

    cmd->header=sl_btmesh_cmd_test_set_adv_provisioning_bearer_timing_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_set_adv_provisioning_bearer_timing.result;

}

sl_status_t sl_btmesh_test_update_keyrefresh_phase(uint16_t network_key_index,
                                                   uint8_t *phase) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_update_keyrefresh_phase.network_key_index=network_key_index;

    cmd->header=sl_btmesh_cmd_test_update_keyrefresh_phase_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (phase) {
        *phase = rsp->data.rsp_test_update_keyrefresh_phase.phase;
    }
    return rsp->data.rsp_test_update_keyrefresh_phase.result;

}

sl_status_t sl_btmesh_test_send_private_beacons() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_test_send_private_beacons_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_send_private_beacons.result;

}

sl_status_t sl_btmesh_test_set_adv_params(uint16_t adv_interval_min,
                                          uint16_t adv_interval_max,
                                          uint8_t adv_repeat_packets,
                                          uint8_t adv_channel_map) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_set_adv_params.adv_interval_min=adv_interval_min;
    cmd->data.cmd_test_set_adv_params.adv_interval_max=adv_interval_max;
    cmd->data.cmd_test_set_adv_params.adv_repeat_packets=adv_repeat_packets;
    cmd->data.cmd_test_set_adv_params.adv_channel_map=adv_channel_map;

    cmd->header=sl_btmesh_cmd_test_set_adv_params_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_set_adv_params.result;

}

sl_status_t sl_btmesh_test_set_scan_params(uint16_t scan_interval,
                                           uint16_t scan_window) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_set_scan_params.scan_interval=scan_interval;
    cmd->data.cmd_test_set_scan_params.scan_window=scan_window;

    cmd->header=sl_btmesh_cmd_test_set_scan_params_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_set_scan_params.result;

}

sl_status_t sl_btmesh_test_adv_use_random_address(uint8_t address_type) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_test_adv_use_random_address.address_type=address_type;

    cmd->header=sl_btmesh_cmd_test_adv_use_random_address_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_test_adv_use_random_address.result;

}

sl_status_t sl_btmesh_lpn_init() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_lpn_init_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_lpn_init.result;

}

sl_status_t sl_btmesh_lpn_deinit() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_lpn_deinit_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_lpn_deinit.result;

}

sl_status_t sl_btmesh_lpn_establish_friendship(uint16_t netkey_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_lpn_establish_friendship.netkey_index=netkey_index;

    cmd->header=sl_btmesh_cmd_lpn_establish_friendship_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_lpn_establish_friendship.result;

}

sl_status_t sl_btmesh_lpn_poll(uint16_t netkey_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_lpn_poll.netkey_index=netkey_index;

    cmd->header=sl_btmesh_cmd_lpn_poll_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_lpn_poll.result;

}

sl_status_t sl_btmesh_lpn_terminate_friendship(uint16_t netkey_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_lpn_terminate_friendship.netkey_index=netkey_index;

    cmd->header=sl_btmesh_cmd_lpn_terminate_friendship_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_lpn_terminate_friendship.result;

}

sl_status_t sl_btmesh_lpn_config(uint8_t setting_id, uint32_t value) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_lpn_config.setting_id=setting_id;
    cmd->data.cmd_lpn_config.value=value;

    cmd->header=sl_btmesh_cmd_lpn_config_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_lpn_config.result;

}

sl_status_t sl_btmesh_friend_init() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_friend_init_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_friend_init.result;

}

sl_status_t sl_btmesh_friend_deinit() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_friend_deinit_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_friend_deinit.result;

}

sl_status_t sl_btmesh_config_client_cancel_request(uint32_t handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_cancel_request.handle=handle;

    cmd->header=sl_btmesh_cmd_config_client_cancel_request_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_config_client_cancel_request.result;

}

sl_status_t sl_btmesh_config_client_get_request_status(uint32_t handle,
                                                       uint16_t *server_address,
                                                       uint16_t *opcode,
                                                       uint32_t *age_ms,
                                                       uint32_t *remaining_ms,
                                                       uint8_t *friend_acked) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_get_request_status.handle=handle;

    cmd->header=sl_btmesh_cmd_config_client_get_request_status_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (server_address) {
        *server_address = rsp->data.rsp_config_client_get_request_status.server_address;
    }
    if (opcode) {
        *opcode = rsp->data.rsp_config_client_get_request_status.opcode;
    }
    if (age_ms) {
        *age_ms = rsp->data.rsp_config_client_get_request_status.age_ms;
    }
    if (remaining_ms) {
        *remaining_ms = rsp->data.rsp_config_client_get_request_status.remaining_ms;
    }
    if (friend_acked) {
        *friend_acked = rsp->data.rsp_config_client_get_request_status.friend_acked;
    }
    return rsp->data.rsp_config_client_get_request_status.result;

}

sl_status_t sl_btmesh_config_client_get_default_timeout(uint32_t *timeout_ms,
                                                        uint32_t *lpn_timeout_ms) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_config_client_get_default_timeout_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (timeout_ms) {
        *timeout_ms = rsp->data.rsp_config_client_get_default_timeout.timeout_ms;
    }
    if (lpn_timeout_ms) {
        *lpn_timeout_ms = rsp->data.rsp_config_client_get_default_timeout.lpn_timeout_ms;
    }
    return rsp->data.rsp_config_client_get_default_timeout.result;

}

sl_status_t sl_btmesh_config_client_set_default_timeout(uint32_t timeout_ms,
                                                        uint32_t lpn_timeout_ms) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_set_default_timeout.timeout_ms=timeout_ms;
    cmd->data.cmd_config_client_set_default_timeout.lpn_timeout_ms=lpn_timeout_ms;

    cmd->header=sl_btmesh_cmd_config_client_set_default_timeout_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_config_client_set_default_timeout.result;

}

sl_status_t sl_btmesh_config_client_add_netkey(uint16_t enc_netkey_index,
                                               uint16_t server_address,
                                               uint16_t netkey_index,
                                               uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_add_netkey.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_add_netkey.server_address=server_address;
    cmd->data.cmd_config_client_add_netkey.netkey_index=netkey_index;

    cmd->header=sl_btmesh_cmd_config_client_add_netkey_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_add_netkey.handle;
    }
    return rsp->data.rsp_config_client_add_netkey.result;

}

sl_status_t sl_btmesh_config_client_remove_netkey(uint16_t enc_netkey_index,
                                                  uint16_t server_address,
                                                  uint16_t netkey_index,
                                                  uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_remove_netkey.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_remove_netkey.server_address=server_address;
    cmd->data.cmd_config_client_remove_netkey.netkey_index=netkey_index;

    cmd->header=sl_btmesh_cmd_config_client_remove_netkey_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_remove_netkey.handle;
    }
    return rsp->data.rsp_config_client_remove_netkey.result;

}

sl_status_t sl_btmesh_config_client_list_netkeys(uint16_t enc_netkey_index,
                                                 uint16_t server_address,
                                                 uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_list_netkeys.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_list_netkeys.server_address=server_address;

    cmd->header=sl_btmesh_cmd_config_client_list_netkeys_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_list_netkeys.handle;
    }
    return rsp->data.rsp_config_client_list_netkeys.result;

}

sl_status_t sl_btmesh_config_client_add_appkey(uint16_t enc_netkey_index,
                                               uint16_t server_address,
                                               uint16_t appkey_index,
                                               uint16_t netkey_index,
                                               uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_add_appkey.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_add_appkey.server_address=server_address;
    cmd->data.cmd_config_client_add_appkey.appkey_index=appkey_index;
    cmd->data.cmd_config_client_add_appkey.netkey_index=netkey_index;

    cmd->header=sl_btmesh_cmd_config_client_add_appkey_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_add_appkey.handle;
    }
    return rsp->data.rsp_config_client_add_appkey.result;

}

sl_status_t sl_btmesh_config_client_remove_appkey(uint16_t enc_netkey_index,
                                                  uint16_t server_address,
                                                  uint16_t appkey_index,
                                                  uint16_t netkey_index,
                                                  uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_remove_appkey.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_remove_appkey.server_address=server_address;
    cmd->data.cmd_config_client_remove_appkey.appkey_index=appkey_index;
    cmd->data.cmd_config_client_remove_appkey.netkey_index=netkey_index;

    cmd->header=sl_btmesh_cmd_config_client_remove_appkey_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_remove_appkey.handle;
    }
    return rsp->data.rsp_config_client_remove_appkey.result;

}

sl_status_t sl_btmesh_config_client_list_appkeys(uint16_t enc_netkey_index,
                                                 uint16_t server_address,
                                                 uint16_t netkey_index,
                                                 uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_list_appkeys.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_list_appkeys.server_address=server_address;
    cmd->data.cmd_config_client_list_appkeys.netkey_index=netkey_index;

    cmd->header=sl_btmesh_cmd_config_client_list_appkeys_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_list_appkeys.handle;
    }
    return rsp->data.rsp_config_client_list_appkeys.result;

}

sl_status_t sl_btmesh_config_client_bind_model(uint16_t enc_netkey_index,
                                               uint16_t server_address,
                                               uint8_t elem_index,
                                               uint16_t vendor_id,
                                               uint16_t model_id,
                                               uint16_t appkey_index,
                                               uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_bind_model.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_bind_model.server_address=server_address;
    cmd->data.cmd_config_client_bind_model.elem_index=elem_index;
    cmd->data.cmd_config_client_bind_model.vendor_id=vendor_id;
    cmd->data.cmd_config_client_bind_model.model_id=model_id;
    cmd->data.cmd_config_client_bind_model.appkey_index=appkey_index;

    cmd->header=sl_btmesh_cmd_config_client_bind_model_id+(((11)&0xff)<<8)+(((11)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_bind_model.handle;
    }
    return rsp->data.rsp_config_client_bind_model.result;

}

sl_status_t sl_btmesh_config_client_unbind_model(uint16_t enc_netkey_index,
                                                 uint16_t server_address,
                                                 uint8_t elem_index,
                                                 uint16_t vendor_id,
                                                 uint16_t model_id,
                                                 uint16_t appkey_index,
                                                 uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_unbind_model.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_unbind_model.server_address=server_address;
    cmd->data.cmd_config_client_unbind_model.elem_index=elem_index;
    cmd->data.cmd_config_client_unbind_model.vendor_id=vendor_id;
    cmd->data.cmd_config_client_unbind_model.model_id=model_id;
    cmd->data.cmd_config_client_unbind_model.appkey_index=appkey_index;

    cmd->header=sl_btmesh_cmd_config_client_unbind_model_id+(((11)&0xff)<<8)+(((11)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_unbind_model.handle;
    }
    return rsp->data.rsp_config_client_unbind_model.result;

}

sl_status_t sl_btmesh_config_client_list_bindings(uint16_t enc_netkey_index,
                                                  uint16_t server_address,
                                                  uint8_t elem_index,
                                                  uint16_t vendor_id,
                                                  uint16_t model_id,
                                                  uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_list_bindings.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_list_bindings.server_address=server_address;
    cmd->data.cmd_config_client_list_bindings.elem_index=elem_index;
    cmd->data.cmd_config_client_list_bindings.vendor_id=vendor_id;
    cmd->data.cmd_config_client_list_bindings.model_id=model_id;

    cmd->header=sl_btmesh_cmd_config_client_list_bindings_id+(((9)&0xff)<<8)+(((9)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_list_bindings.handle;
    }
    return rsp->data.rsp_config_client_list_bindings.result;

}

sl_status_t sl_btmesh_config_client_get_model_pub(uint16_t enc_netkey_index,
                                                  uint16_t server_address,
                                                  uint8_t elem_index,
                                                  uint16_t vendor_id,
                                                  uint16_t model_id,
                                                  uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_get_model_pub.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_get_model_pub.server_address=server_address;
    cmd->data.cmd_config_client_get_model_pub.elem_index=elem_index;
    cmd->data.cmd_config_client_get_model_pub.vendor_id=vendor_id;
    cmd->data.cmd_config_client_get_model_pub.model_id=model_id;

    cmd->header=sl_btmesh_cmd_config_client_get_model_pub_id+(((9)&0xff)<<8)+(((9)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_get_model_pub.handle;
    }
    return rsp->data.rsp_config_client_get_model_pub.result;

}

sl_status_t sl_btmesh_config_client_set_model_pub(uint16_t enc_netkey_index,
                                                  uint16_t server_address,
                                                  uint8_t elem_index,
                                                  uint16_t vendor_id,
                                                  uint16_t model_id,
                                                  uint16_t address,
                                                  uint16_t appkey_index,
                                                  uint8_t credentials,
                                                  uint8_t ttl,
                                                  uint32_t period_ms,
                                                  uint8_t retransmit_count,
                                                  uint16_t retransmit_interval_ms,
                                                  uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_set_model_pub.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_set_model_pub.server_address=server_address;
    cmd->data.cmd_config_client_set_model_pub.elem_index=elem_index;
    cmd->data.cmd_config_client_set_model_pub.vendor_id=vendor_id;
    cmd->data.cmd_config_client_set_model_pub.model_id=model_id;
    cmd->data.cmd_config_client_set_model_pub.address=address;
    cmd->data.cmd_config_client_set_model_pub.appkey_index=appkey_index;
    cmd->data.cmd_config_client_set_model_pub.credentials=credentials;
    cmd->data.cmd_config_client_set_model_pub.ttl=ttl;
    cmd->data.cmd_config_client_set_model_pub.period_ms=period_ms;
    cmd->data.cmd_config_client_set_model_pub.retransmit_count=retransmit_count;
    cmd->data.cmd_config_client_set_model_pub.retransmit_interval_ms=retransmit_interval_ms;

    cmd->header=sl_btmesh_cmd_config_client_set_model_pub_id+(((22)&0xff)<<8)+(((22)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_set_model_pub.handle;
    }
    return rsp->data.rsp_config_client_set_model_pub.result;

}

sl_status_t sl_btmesh_config_client_set_model_pub_va(uint16_t enc_netkey_index,
                                                     uint16_t server_address,
                                                     uint8_t elem_index,
                                                     uint16_t vendor_id,
                                                     uint16_t model_id,
                                                     uuid_128 address,
                                                     uint16_t appkey_index,
                                                     uint8_t credentials,
                                                     uint8_t ttl,
                                                     uint32_t period_ms,
                                                     uint8_t retransmit_count,
                                                     uint16_t retransmit_interval_ms,
                                                     uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_set_model_pub_va.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_set_model_pub_va.server_address=server_address;
    cmd->data.cmd_config_client_set_model_pub_va.elem_index=elem_index;
    cmd->data.cmd_config_client_set_model_pub_va.vendor_id=vendor_id;
    cmd->data.cmd_config_client_set_model_pub_va.model_id=model_id;
    cmd->data.cmd_config_client_set_model_pub_va.address=address;
    cmd->data.cmd_config_client_set_model_pub_va.appkey_index=appkey_index;
    cmd->data.cmd_config_client_set_model_pub_va.credentials=credentials;
    cmd->data.cmd_config_client_set_model_pub_va.ttl=ttl;
    cmd->data.cmd_config_client_set_model_pub_va.period_ms=period_ms;
    cmd->data.cmd_config_client_set_model_pub_va.retransmit_count=retransmit_count;
    cmd->data.cmd_config_client_set_model_pub_va.retransmit_interval_ms=retransmit_interval_ms;

    cmd->header=sl_btmesh_cmd_config_client_set_model_pub_va_id+(((36)&0xff)<<8)+(((36)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_set_model_pub_va.handle;
    }
    return rsp->data.rsp_config_client_set_model_pub_va.result;

}

sl_status_t sl_btmesh_config_client_add_model_sub(uint16_t enc_netkey_index,
                                                  uint16_t server_address,
                                                  uint8_t elem_index,
                                                  uint16_t vendor_id,
                                                  uint16_t model_id,
                                                  uint16_t sub_address,
                                                  uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_add_model_sub.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_add_model_sub.server_address=server_address;
    cmd->data.cmd_config_client_add_model_sub.elem_index=elem_index;
    cmd->data.cmd_config_client_add_model_sub.vendor_id=vendor_id;
    cmd->data.cmd_config_client_add_model_sub.model_id=model_id;
    cmd->data.cmd_config_client_add_model_sub.sub_address=sub_address;

    cmd->header=sl_btmesh_cmd_config_client_add_model_sub_id+(((11)&0xff)<<8)+(((11)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_add_model_sub.handle;
    }
    return rsp->data.rsp_config_client_add_model_sub.result;

}

sl_status_t sl_btmesh_config_client_add_model_sub_va(uint16_t enc_netkey_index,
                                                     uint16_t server_address,
                                                     uint8_t elem_index,
                                                     uint16_t vendor_id,
                                                     uint16_t model_id,
                                                     uuid_128 sub_address,
                                                     uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_add_model_sub_va.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_add_model_sub_va.server_address=server_address;
    cmd->data.cmd_config_client_add_model_sub_va.elem_index=elem_index;
    cmd->data.cmd_config_client_add_model_sub_va.vendor_id=vendor_id;
    cmd->data.cmd_config_client_add_model_sub_va.model_id=model_id;
    cmd->data.cmd_config_client_add_model_sub_va.sub_address=sub_address;

    cmd->header=sl_btmesh_cmd_config_client_add_model_sub_va_id+(((25)&0xff)<<8)+(((25)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_add_model_sub_va.handle;
    }
    return rsp->data.rsp_config_client_add_model_sub_va.result;

}

sl_status_t sl_btmesh_config_client_remove_model_sub(uint16_t enc_netkey_index,
                                                     uint16_t server_address,
                                                     uint8_t elem_index,
                                                     uint16_t vendor_id,
                                                     uint16_t model_id,
                                                     uint16_t sub_address,
                                                     uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_remove_model_sub.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_remove_model_sub.server_address=server_address;
    cmd->data.cmd_config_client_remove_model_sub.elem_index=elem_index;
    cmd->data.cmd_config_client_remove_model_sub.vendor_id=vendor_id;
    cmd->data.cmd_config_client_remove_model_sub.model_id=model_id;
    cmd->data.cmd_config_client_remove_model_sub.sub_address=sub_address;

    cmd->header=sl_btmesh_cmd_config_client_remove_model_sub_id+(((11)&0xff)<<8)+(((11)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_remove_model_sub.handle;
    }
    return rsp->data.rsp_config_client_remove_model_sub.result;

}

sl_status_t sl_btmesh_config_client_remove_model_sub_va(uint16_t enc_netkey_index,
                                                        uint16_t server_address,
                                                        uint8_t elem_index,
                                                        uint16_t vendor_id,
                                                        uint16_t model_id,
                                                        uuid_128 sub_address,
                                                        uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_remove_model_sub_va.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_remove_model_sub_va.server_address=server_address;
    cmd->data.cmd_config_client_remove_model_sub_va.elem_index=elem_index;
    cmd->data.cmd_config_client_remove_model_sub_va.vendor_id=vendor_id;
    cmd->data.cmd_config_client_remove_model_sub_va.model_id=model_id;
    cmd->data.cmd_config_client_remove_model_sub_va.sub_address=sub_address;

    cmd->header=sl_btmesh_cmd_config_client_remove_model_sub_va_id+(((25)&0xff)<<8)+(((25)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_remove_model_sub_va.handle;
    }
    return rsp->data.rsp_config_client_remove_model_sub_va.result;

}

sl_status_t sl_btmesh_config_client_set_model_sub(uint16_t enc_netkey_index,
                                                  uint16_t server_address,
                                                  uint8_t elem_index,
                                                  uint16_t vendor_id,
                                                  uint16_t model_id,
                                                  uint16_t sub_address,
                                                  uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_set_model_sub.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_set_model_sub.server_address=server_address;
    cmd->data.cmd_config_client_set_model_sub.elem_index=elem_index;
    cmd->data.cmd_config_client_set_model_sub.vendor_id=vendor_id;
    cmd->data.cmd_config_client_set_model_sub.model_id=model_id;
    cmd->data.cmd_config_client_set_model_sub.sub_address=sub_address;

    cmd->header=sl_btmesh_cmd_config_client_set_model_sub_id+(((11)&0xff)<<8)+(((11)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_set_model_sub.handle;
    }
    return rsp->data.rsp_config_client_set_model_sub.result;

}

sl_status_t sl_btmesh_config_client_set_model_sub_va(uint16_t enc_netkey_index,
                                                     uint16_t server_address,
                                                     uint8_t elem_index,
                                                     uint16_t vendor_id,
                                                     uint16_t model_id,
                                                     uuid_128 sub_address,
                                                     uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_set_model_sub_va.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_set_model_sub_va.server_address=server_address;
    cmd->data.cmd_config_client_set_model_sub_va.elem_index=elem_index;
    cmd->data.cmd_config_client_set_model_sub_va.vendor_id=vendor_id;
    cmd->data.cmd_config_client_set_model_sub_va.model_id=model_id;
    cmd->data.cmd_config_client_set_model_sub_va.sub_address=sub_address;

    cmd->header=sl_btmesh_cmd_config_client_set_model_sub_va_id+(((25)&0xff)<<8)+(((25)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_set_model_sub_va.handle;
    }
    return rsp->data.rsp_config_client_set_model_sub_va.result;

}

sl_status_t sl_btmesh_config_client_clear_model_sub(uint16_t enc_netkey_index,
                                                    uint16_t server_address,
                                                    uint8_t elem_index,
                                                    uint16_t vendor_id,
                                                    uint16_t model_id,
                                                    uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_clear_model_sub.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_clear_model_sub.server_address=server_address;
    cmd->data.cmd_config_client_clear_model_sub.elem_index=elem_index;
    cmd->data.cmd_config_client_clear_model_sub.vendor_id=vendor_id;
    cmd->data.cmd_config_client_clear_model_sub.model_id=model_id;

    cmd->header=sl_btmesh_cmd_config_client_clear_model_sub_id+(((9)&0xff)<<8)+(((9)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_clear_model_sub.handle;
    }
    return rsp->data.rsp_config_client_clear_model_sub.result;

}

sl_status_t sl_btmesh_config_client_list_subs(uint16_t enc_netkey_index,
                                              uint16_t server_address,
                                              uint8_t elem_index,
                                              uint16_t vendor_id,
                                              uint16_t model_id,
                                              uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_list_subs.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_list_subs.server_address=server_address;
    cmd->data.cmd_config_client_list_subs.elem_index=elem_index;
    cmd->data.cmd_config_client_list_subs.vendor_id=vendor_id;
    cmd->data.cmd_config_client_list_subs.model_id=model_id;

    cmd->header=sl_btmesh_cmd_config_client_list_subs_id+(((9)&0xff)<<8)+(((9)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_list_subs.handle;
    }
    return rsp->data.rsp_config_client_list_subs.result;

}

sl_status_t sl_btmesh_config_client_get_heartbeat_pub(uint16_t enc_netkey_index,
                                                      uint16_t server_address,
                                                      uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_get_heartbeat_pub.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_get_heartbeat_pub.server_address=server_address;

    cmd->header=sl_btmesh_cmd_config_client_get_heartbeat_pub_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_get_heartbeat_pub.handle;
    }
    return rsp->data.rsp_config_client_get_heartbeat_pub.result;

}

sl_status_t sl_btmesh_config_client_set_heartbeat_pub(uint16_t enc_netkey_index,
                                                      uint16_t server_address,
                                                      uint16_t destination_address,
                                                      uint16_t netkey_index,
                                                      uint8_t count_log,
                                                      uint8_t period_log,
                                                      uint8_t ttl,
                                                      uint16_t features,
                                                      uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_set_heartbeat_pub.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_set_heartbeat_pub.server_address=server_address;
    cmd->data.cmd_config_client_set_heartbeat_pub.destination_address=destination_address;
    cmd->data.cmd_config_client_set_heartbeat_pub.netkey_index=netkey_index;
    cmd->data.cmd_config_client_set_heartbeat_pub.count_log=count_log;
    cmd->data.cmd_config_client_set_heartbeat_pub.period_log=period_log;
    cmd->data.cmd_config_client_set_heartbeat_pub.ttl=ttl;
    cmd->data.cmd_config_client_set_heartbeat_pub.features=features;

    cmd->header=sl_btmesh_cmd_config_client_set_heartbeat_pub_id+(((13)&0xff)<<8)+(((13)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_set_heartbeat_pub.handle;
    }
    return rsp->data.rsp_config_client_set_heartbeat_pub.result;

}

sl_status_t sl_btmesh_config_client_get_heartbeat_sub(uint16_t enc_netkey_index,
                                                      uint16_t server_address,
                                                      uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_get_heartbeat_sub.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_get_heartbeat_sub.server_address=server_address;

    cmd->header=sl_btmesh_cmd_config_client_get_heartbeat_sub_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_get_heartbeat_sub.handle;
    }
    return rsp->data.rsp_config_client_get_heartbeat_sub.result;

}

sl_status_t sl_btmesh_config_client_set_heartbeat_sub(uint16_t enc_netkey_index,
                                                      uint16_t server_address,
                                                      uint16_t source_address,
                                                      uint16_t destination_address,
                                                      uint8_t period_log,
                                                      uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_set_heartbeat_sub.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_set_heartbeat_sub.server_address=server_address;
    cmd->data.cmd_config_client_set_heartbeat_sub.source_address=source_address;
    cmd->data.cmd_config_client_set_heartbeat_sub.destination_address=destination_address;
    cmd->data.cmd_config_client_set_heartbeat_sub.period_log=period_log;

    cmd->header=sl_btmesh_cmd_config_client_set_heartbeat_sub_id+(((9)&0xff)<<8)+(((9)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_set_heartbeat_sub.handle;
    }
    return rsp->data.rsp_config_client_set_heartbeat_sub.result;

}

sl_status_t sl_btmesh_config_client_get_beacon(uint16_t enc_netkey_index,
                                               uint16_t server_address,
                                               uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_get_beacon.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_get_beacon.server_address=server_address;

    cmd->header=sl_btmesh_cmd_config_client_get_beacon_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_get_beacon.handle;
    }
    return rsp->data.rsp_config_client_get_beacon.result;

}

sl_status_t sl_btmesh_config_client_set_beacon(uint16_t enc_netkey_index,
                                               uint16_t server_address,
                                               uint8_t value,
                                               uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_set_beacon.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_set_beacon.server_address=server_address;
    cmd->data.cmd_config_client_set_beacon.value=value;

    cmd->header=sl_btmesh_cmd_config_client_set_beacon_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_set_beacon.handle;
    }
    return rsp->data.rsp_config_client_set_beacon.result;

}

sl_status_t sl_btmesh_config_client_get_default_ttl(uint16_t enc_netkey_index,
                                                    uint16_t server_address,
                                                    uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_get_default_ttl.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_get_default_ttl.server_address=server_address;

    cmd->header=sl_btmesh_cmd_config_client_get_default_ttl_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_get_default_ttl.handle;
    }
    return rsp->data.rsp_config_client_get_default_ttl.result;

}

sl_status_t sl_btmesh_config_client_set_default_ttl(uint16_t enc_netkey_index,
                                                    uint16_t server_address,
                                                    uint8_t value,
                                                    uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_set_default_ttl.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_set_default_ttl.server_address=server_address;
    cmd->data.cmd_config_client_set_default_ttl.value=value;

    cmd->header=sl_btmesh_cmd_config_client_set_default_ttl_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_set_default_ttl.handle;
    }
    return rsp->data.rsp_config_client_set_default_ttl.result;

}

sl_status_t sl_btmesh_config_client_get_gatt_proxy(uint16_t enc_netkey_index,
                                                   uint16_t server_address,
                                                   uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_get_gatt_proxy.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_get_gatt_proxy.server_address=server_address;

    cmd->header=sl_btmesh_cmd_config_client_get_gatt_proxy_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_get_gatt_proxy.handle;
    }
    return rsp->data.rsp_config_client_get_gatt_proxy.result;

}

sl_status_t sl_btmesh_config_client_set_gatt_proxy(uint16_t enc_netkey_index,
                                                   uint16_t server_address,
                                                   uint8_t value,
                                                   uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_set_gatt_proxy.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_set_gatt_proxy.server_address=server_address;
    cmd->data.cmd_config_client_set_gatt_proxy.value=value;

    cmd->header=sl_btmesh_cmd_config_client_set_gatt_proxy_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_set_gatt_proxy.handle;
    }
    return rsp->data.rsp_config_client_set_gatt_proxy.result;

}

sl_status_t sl_btmesh_config_client_get_relay(uint16_t enc_netkey_index,
                                              uint16_t server_address,
                                              uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_get_relay.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_get_relay.server_address=server_address;

    cmd->header=sl_btmesh_cmd_config_client_get_relay_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_get_relay.handle;
    }
    return rsp->data.rsp_config_client_get_relay.result;

}

sl_status_t sl_btmesh_config_client_set_relay(uint16_t enc_netkey_index,
                                              uint16_t server_address,
                                              uint8_t value,
                                              uint8_t retransmit_count,
                                              uint16_t retransmit_interval_ms,
                                              uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_set_relay.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_set_relay.server_address=server_address;
    cmd->data.cmd_config_client_set_relay.value=value;
    cmd->data.cmd_config_client_set_relay.retransmit_count=retransmit_count;
    cmd->data.cmd_config_client_set_relay.retransmit_interval_ms=retransmit_interval_ms;

    cmd->header=sl_btmesh_cmd_config_client_set_relay_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_set_relay.handle;
    }
    return rsp->data.rsp_config_client_set_relay.result;

}

sl_status_t sl_btmesh_config_client_get_network_transmit(uint16_t enc_netkey_index,
                                                         uint16_t server_address,
                                                         uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_get_network_transmit.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_get_network_transmit.server_address=server_address;

    cmd->header=sl_btmesh_cmd_config_client_get_network_transmit_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_get_network_transmit.handle;
    }
    return rsp->data.rsp_config_client_get_network_transmit.result;

}

sl_status_t sl_btmesh_config_client_set_network_transmit(uint16_t enc_netkey_index,
                                                         uint16_t server_address,
                                                         uint8_t transmit_count,
                                                         uint16_t transmit_interval_ms,
                                                         uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_set_network_transmit.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_set_network_transmit.server_address=server_address;
    cmd->data.cmd_config_client_set_network_transmit.transmit_count=transmit_count;
    cmd->data.cmd_config_client_set_network_transmit.transmit_interval_ms=transmit_interval_ms;

    cmd->header=sl_btmesh_cmd_config_client_set_network_transmit_id+(((7)&0xff)<<8)+(((7)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_set_network_transmit.handle;
    }
    return rsp->data.rsp_config_client_set_network_transmit.result;

}

sl_status_t sl_btmesh_config_client_get_identity(uint16_t enc_netkey_index,
                                                 uint16_t server_address,
                                                 uint16_t netkey_index,
                                                 uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_get_identity.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_get_identity.server_address=server_address;
    cmd->data.cmd_config_client_get_identity.netkey_index=netkey_index;

    cmd->header=sl_btmesh_cmd_config_client_get_identity_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_get_identity.handle;
    }
    return rsp->data.rsp_config_client_get_identity.result;

}

sl_status_t sl_btmesh_config_client_set_identity(uint16_t enc_netkey_index,
                                                 uint16_t server_address,
                                                 uint16_t netkey_index,
                                                 uint8_t value,
                                                 uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_set_identity.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_set_identity.server_address=server_address;
    cmd->data.cmd_config_client_set_identity.netkey_index=netkey_index;
    cmd->data.cmd_config_client_set_identity.value=value;

    cmd->header=sl_btmesh_cmd_config_client_set_identity_id+(((7)&0xff)<<8)+(((7)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_set_identity.handle;
    }
    return rsp->data.rsp_config_client_set_identity.result;

}

sl_status_t sl_btmesh_config_client_get_friend(uint16_t enc_netkey_index,
                                               uint16_t server_address,
                                               uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_get_friend.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_get_friend.server_address=server_address;

    cmd->header=sl_btmesh_cmd_config_client_get_friend_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_get_friend.handle;
    }
    return rsp->data.rsp_config_client_get_friend.result;

}

sl_status_t sl_btmesh_config_client_set_friend(uint16_t enc_netkey_index,
                                               uint16_t server_address,
                                               uint8_t value,
                                               uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_set_friend.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_set_friend.server_address=server_address;
    cmd->data.cmd_config_client_set_friend.value=value;

    cmd->header=sl_btmesh_cmd_config_client_set_friend_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_set_friend.handle;
    }
    return rsp->data.rsp_config_client_set_friend.result;

}

sl_status_t sl_btmesh_config_client_get_key_refresh_phase(uint16_t enc_netkey_index,
                                                          uint16_t server_address,
                                                          uint16_t netkey_index,
                                                          uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_get_key_refresh_phase.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_get_key_refresh_phase.server_address=server_address;
    cmd->data.cmd_config_client_get_key_refresh_phase.netkey_index=netkey_index;

    cmd->header=sl_btmesh_cmd_config_client_get_key_refresh_phase_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_get_key_refresh_phase.handle;
    }
    return rsp->data.rsp_config_client_get_key_refresh_phase.result;

}

sl_status_t sl_btmesh_config_client_get_lpn_polltimeout(uint16_t enc_netkey_index,
                                                        uint16_t server_address,
                                                        uint16_t lpn_address,
                                                        uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_get_lpn_polltimeout.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_get_lpn_polltimeout.server_address=server_address;
    cmd->data.cmd_config_client_get_lpn_polltimeout.lpn_address=lpn_address;

    cmd->header=sl_btmesh_cmd_config_client_get_lpn_polltimeout_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_get_lpn_polltimeout.handle;
    }
    return rsp->data.rsp_config_client_get_lpn_polltimeout.result;

}

sl_status_t sl_btmesh_config_client_get_dcd(uint16_t enc_netkey_index,
                                            uint16_t server_address,
                                            uint8_t page,
                                            uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_get_dcd.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_get_dcd.server_address=server_address;
    cmd->data.cmd_config_client_get_dcd.page=page;

    cmd->header=sl_btmesh_cmd_config_client_get_dcd_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_get_dcd.handle;
    }
    return rsp->data.rsp_config_client_get_dcd.result;

}

sl_status_t sl_btmesh_config_client_reset_node(uint16_t enc_netkey_index,
                                               uint16_t server_address,
                                               uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_reset_node.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_config_client_reset_node.server_address=server_address;

    cmd->header=sl_btmesh_cmd_config_client_reset_node_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_config_client_reset_node.handle;
    }
    return rsp->data.rsp_config_client_reset_node.result;

}

sl_status_t sl_btmesh_config_client_set_request_timeout_for_node(uint16_t lpn_address,
                                                                 uint16_t timeout_ms) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_config_client_set_request_timeout_for_node.lpn_address=lpn_address;
    cmd->data.cmd_config_client_set_request_timeout_for_node.timeout_ms=timeout_ms;

    cmd->header=sl_btmesh_cmd_config_client_set_request_timeout_for_node_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_config_client_set_request_timeout_for_node.result;

}

sl_status_t sl_btmesh_mbt_client_init(uint16_t elem_index,
                                      uint16_t max_servers,
                                      uint16_t max_blocks,
                                      uint16_t max_chunks_per_block) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_mbt_client_init.elem_index=elem_index;
    cmd->data.cmd_mbt_client_init.max_servers=max_servers;
    cmd->data.cmd_mbt_client_init.max_blocks=max_blocks;
    cmd->data.cmd_mbt_client_init.max_chunks_per_block=max_chunks_per_block;

    cmd->header=sl_btmesh_cmd_mbt_client_init_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_mbt_client_init.result;

}

sl_status_t sl_btmesh_mbt_client_setup(uint16_t elem_index,
                                       sl_bt_uuid_64_t blob_id,
                                       uint32_t blob_size,
                                       uint16_t appkey_index,
                                       uint8_t ttl,
                                       uint16_t timeout_base,
                                       uint8_t supported_transfer_modes,
                                       uint16_t group_address,
                                       uuid_128 virtual_address,
                                       uint16_t multicast_threshold,
                                       size_t servers_len,
                                       const uint8_t* servers) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_mbt_client_setup.elem_index=elem_index;
    cmd->data.cmd_mbt_client_setup.blob_id=blob_id;
    cmd->data.cmd_mbt_client_setup.blob_size=blob_size;
    cmd->data.cmd_mbt_client_setup.appkey_index=appkey_index;
    cmd->data.cmd_mbt_client_setup.ttl=ttl;
    cmd->data.cmd_mbt_client_setup.timeout_base=timeout_base;
    cmd->data.cmd_mbt_client_setup.supported_transfer_modes=supported_transfer_modes;
    cmd->data.cmd_mbt_client_setup.group_address=group_address;
    cmd->data.cmd_mbt_client_setup.virtual_address=virtual_address;
    cmd->data.cmd_mbt_client_setup.multicast_threshold=multicast_threshold;
    if ((41+servers_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_mbt_client_setup.servers.len=servers_len;
    memcpy(cmd->data.cmd_mbt_client_setup.servers.data,servers,servers_len);

    cmd->header=sl_btmesh_cmd_mbt_client_setup_id+(((41+servers_len)&0xff)<<8)+(((41+servers_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_mbt_client_setup.result;

}

sl_status_t sl_btmesh_mbt_client_query_information(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_mbt_client_query_information.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_mbt_client_query_information_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_mbt_client_query_information.result;

}

sl_status_t sl_btmesh_mbt_client_get_server_status(uint16_t elem_index,
                                                   uint16_t server_index,
                                                   uint16_t *server_address,
                                                   uint8_t *current_procedure_status,
                                                   uint16_t *rx_blocks,
                                                   uint16_t *rx_chunks) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_mbt_client_get_server_status.elem_index=elem_index;
    cmd->data.cmd_mbt_client_get_server_status.server_index=server_index;

    cmd->header=sl_btmesh_cmd_mbt_client_get_server_status_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (server_address) {
        *server_address = rsp->data.rsp_mbt_client_get_server_status.server_address;
    }
    if (current_procedure_status) {
        *current_procedure_status = rsp->data.rsp_mbt_client_get_server_status.current_procedure_status;
    }
    if (rx_blocks) {
        *rx_blocks = rsp->data.rsp_mbt_client_get_server_status.rx_blocks;
    }
    if (rx_chunks) {
        *rx_chunks = rsp->data.rsp_mbt_client_get_server_status.rx_chunks;
    }
    return rsp->data.rsp_mbt_client_get_server_status.result;

}

sl_status_t sl_btmesh_mbt_client_add_server(uint16_t elem_index,
                                            uint16_t server_address) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_mbt_client_add_server.elem_index=elem_index;
    cmd->data.cmd_mbt_client_add_server.server_address=server_address;

    cmd->header=sl_btmesh_cmd_mbt_client_add_server_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_mbt_client_add_server.result;

}

sl_status_t sl_btmesh_mbt_client_start_transfer(uint16_t elem_index,
                                                uint8_t block_size_log,
                                                uint8_t transfer_mode) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_mbt_client_start_transfer.elem_index=elem_index;
    cmd->data.cmd_mbt_client_start_transfer.block_size_log=block_size_log;
    cmd->data.cmd_mbt_client_start_transfer.transfer_mode=transfer_mode;

    cmd->header=sl_btmesh_cmd_mbt_client_start_transfer_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_mbt_client_start_transfer.result;

}

sl_status_t sl_btmesh_mbt_client_start_block(uint16_t elem_index,
                                             uint16_t chunk_size,
                                             uint16_t *block_number,
                                             uint32_t *block_size) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_mbt_client_start_block.elem_index=elem_index;
    cmd->data.cmd_mbt_client_start_block.chunk_size=chunk_size;

    cmd->header=sl_btmesh_cmd_mbt_client_start_block_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (block_number) {
        *block_number = rsp->data.rsp_mbt_client_start_block.block_number;
    }
    if (block_size) {
        *block_size = rsp->data.rsp_mbt_client_start_block.block_size;
    }
    return rsp->data.rsp_mbt_client_start_block.result;

}

sl_status_t sl_btmesh_mbt_client_send_chunk_request_rsp(uint16_t elem_index,
                                                        size_t data_len,
                                                        const uint8_t* data) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_mbt_client_send_chunk_request_rsp.elem_index=elem_index;
    if ((3+data_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_mbt_client_send_chunk_request_rsp.data.len=data_len;
    memcpy(cmd->data.cmd_mbt_client_send_chunk_request_rsp.data.data,data,data_len);

    cmd->header=sl_btmesh_cmd_mbt_client_send_chunk_request_rsp_id+(((3+data_len)&0xff)<<8)+(((3+data_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_mbt_client_send_chunk_request_rsp.result;

}

sl_status_t sl_btmesh_mbt_client_query_block_status(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_mbt_client_query_block_status.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_mbt_client_query_block_status_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_mbt_client_query_block_status.result;

}

sl_status_t sl_btmesh_mbt_client_get_status(uint16_t elem_index,
                                            uint8_t *state,
                                            uint16_t *total_blocks,
                                            uint16_t *total_chunks) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_mbt_client_get_status.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_mbt_client_get_status_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (state) {
        *state = rsp->data.rsp_mbt_client_get_status.state;
    }
    if (total_blocks) {
        *total_blocks = rsp->data.rsp_mbt_client_get_status.total_blocks;
    }
    if (total_chunks) {
        *total_chunks = rsp->data.rsp_mbt_client_get_status.total_chunks;
    }
    return rsp->data.rsp_mbt_client_get_status.result;

}

sl_status_t sl_btmesh_mbt_client_get_transfer_status(uint16_t elem_index,
                                                     uint16_t server_address,
                                                     uuid_128 virtual_address,
                                                     uint16_t appkey_index,
                                                     uint8_t ttl) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_mbt_client_get_transfer_status.elem_index=elem_index;
    cmd->data.cmd_mbt_client_get_transfer_status.server_address=server_address;
    cmd->data.cmd_mbt_client_get_transfer_status.virtual_address=virtual_address;
    cmd->data.cmd_mbt_client_get_transfer_status.appkey_index=appkey_index;
    cmd->data.cmd_mbt_client_get_transfer_status.ttl=ttl;

    cmd->header=sl_btmesh_cmd_mbt_client_get_transfer_status_id+(((23)&0xff)<<8)+(((23)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_mbt_client_get_transfer_status.result;

}

sl_status_t sl_btmesh_mbt_client_cancel_transfer(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_mbt_client_cancel_transfer.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_mbt_client_cancel_transfer_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_mbt_client_cancel_transfer.result;

}

sl_status_t sl_btmesh_mbt_client_abort(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_mbt_client_abort.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_mbt_client_abort_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_mbt_client_abort.result;

}

sl_status_t sl_btmesh_mbt_server_init(uint16_t elem_index,
                                      uint8_t min_block_size_log,
                                      uint8_t max_block_size_log,
                                      uint16_t max_chunks_per_block,
                                      uint16_t max_chunk_size,
                                      uint32_t max_blob_size,
                                      uint8_t supported_transfer_modes,
                                      uint16_t pull_mode_chunks_to_request,
                                      uint16_t pull_mode_retry_interval_ms,
                                      uint16_t pull_mode_retry_count) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_mbt_server_init.elem_index=elem_index;
    cmd->data.cmd_mbt_server_init.min_block_size_log=min_block_size_log;
    cmd->data.cmd_mbt_server_init.max_block_size_log=max_block_size_log;
    cmd->data.cmd_mbt_server_init.max_chunks_per_block=max_chunks_per_block;
    cmd->data.cmd_mbt_server_init.max_chunk_size=max_chunk_size;
    cmd->data.cmd_mbt_server_init.max_blob_size=max_blob_size;
    cmd->data.cmd_mbt_server_init.supported_transfer_modes=supported_transfer_modes;
    cmd->data.cmd_mbt_server_init.pull_mode_chunks_to_request=pull_mode_chunks_to_request;
    cmd->data.cmd_mbt_server_init.pull_mode_retry_interval_ms=pull_mode_retry_interval_ms;
    cmd->data.cmd_mbt_server_init.pull_mode_retry_count=pull_mode_retry_count;

    cmd->header=sl_btmesh_cmd_mbt_server_init_id+(((19)&0xff)<<8)+(((19)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_mbt_server_init.result;

}

sl_status_t sl_btmesh_mbt_server_start(uint16_t elem_index,
                                       sl_bt_uuid_64_t blob_id,
                                       uint16_t timeout_10s,
                                       uint8_t ttl) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_mbt_server_start.elem_index=elem_index;
    cmd->data.cmd_mbt_server_start.blob_id=blob_id;
    cmd->data.cmd_mbt_server_start.timeout_10s=timeout_10s;
    cmd->data.cmd_mbt_server_start.ttl=ttl;

    cmd->header=sl_btmesh_cmd_mbt_server_start_id+(((13)&0xff)<<8)+(((13)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_mbt_server_start.result;

}

sl_status_t sl_btmesh_mbt_server_get_transfer_status(uint16_t elem_index,
                                                     uint8_t *state,
                                                     sl_bt_uuid_64_t *blob_id,
                                                     uint32_t *blob_size,
                                                     uint16_t *block_number,
                                                     size_t max_blocks_missing_mask_size,
                                                     size_t *blocks_missing_mask_len,
                                                     uint8_t *blocks_missing_mask) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_mbt_server_get_transfer_status.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_mbt_server_get_transfer_status_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (state) {
        *state = rsp->data.rsp_mbt_server_get_transfer_status.state;
    }
    if (blob_id) {
        *blob_id = rsp->data.rsp_mbt_server_get_transfer_status.blob_id;
    }
    if (blob_size) {
        *blob_size = rsp->data.rsp_mbt_server_get_transfer_status.blob_size;
    }
    if (block_number) {
        *block_number = rsp->data.rsp_mbt_server_get_transfer_status.block_number;
    }
    if (blocks_missing_mask_len) {
        *blocks_missing_mask_len = rsp->data.rsp_mbt_server_get_transfer_status.blocks_missing_mask.len;
    }
    if (blocks_missing_mask && (rsp->data.rsp_mbt_server_get_transfer_status.blocks_missing_mask.len <= max_blocks_missing_mask_size)) {
        memcpy(blocks_missing_mask,rsp->data.rsp_mbt_server_get_transfer_status.blocks_missing_mask.data,rsp->data.rsp_mbt_server_get_transfer_status.blocks_missing_mask.len);
    }
    return rsp->data.rsp_mbt_server_get_transfer_status.result;

}

sl_status_t sl_btmesh_mbt_server_transfer_complete(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_mbt_server_transfer_complete.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_mbt_server_transfer_complete_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_mbt_server_transfer_complete.result;

}

sl_status_t sl_btmesh_mbt_server_abort(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_mbt_server_abort.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_mbt_server_abort_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_mbt_server_abort.result;

}

sl_status_t sl_btmesh_mbt_server_set_pull_mode_parameters(uint16_t elem_index,
                                                          uint16_t pull_mode_retry_interval_ms,
                                                          uint16_t pull_mode_retry_count) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_mbt_server_set_pull_mode_parameters.elem_index=elem_index;
    cmd->data.cmd_mbt_server_set_pull_mode_parameters.pull_mode_retry_interval_ms=pull_mode_retry_interval_ms;
    cmd->data.cmd_mbt_server_set_pull_mode_parameters.pull_mode_retry_count=pull_mode_retry_count;

    cmd->header=sl_btmesh_cmd_mbt_server_set_pull_mode_parameters_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_mbt_server_set_pull_mode_parameters.result;

}

sl_status_t sl_btmesh_mbt_server_transfer_start_rsp(uint16_t elem_index,
                                                    uint8_t status) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_mbt_server_transfer_start_rsp.elem_index=elem_index;
    cmd->data.cmd_mbt_server_transfer_start_rsp.status=status;

    cmd->header=sl_btmesh_cmd_mbt_server_transfer_start_rsp_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_mbt_server_transfer_start_rsp.result;

}

sl_status_t sl_btmesh_sensor_server_init(uint16_t elem_index,
                                         size_t descriptors_len,
                                         const uint8_t* descriptors) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_sensor_server_init.elem_index=elem_index;
    if ((3+descriptors_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_sensor_server_init.descriptors.len=descriptors_len;
    memcpy(cmd->data.cmd_sensor_server_init.descriptors.data,descriptors,descriptors_len);

    cmd->header=sl_btmesh_cmd_sensor_server_init_id+(((3+descriptors_len)&0xff)<<8)+(((3+descriptors_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_sensor_server_init.result;

}

sl_status_t sl_btmesh_sensor_server_deinit(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_sensor_server_deinit.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_sensor_server_deinit_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_sensor_server_deinit.result;

}

sl_status_t sl_btmesh_sensor_server_send_descriptor_status(uint16_t client_address,
                                                           uint16_t elem_index,
                                                           uint16_t appkey_index,
                                                           uint8_t flags,
                                                           size_t descriptors_len,
                                                           const uint8_t* descriptors) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_sensor_server_send_descriptor_status.client_address=client_address;
    cmd->data.cmd_sensor_server_send_descriptor_status.elem_index=elem_index;
    cmd->data.cmd_sensor_server_send_descriptor_status.appkey_index=appkey_index;
    cmd->data.cmd_sensor_server_send_descriptor_status.flags=flags;
    if ((8+descriptors_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_sensor_server_send_descriptor_status.descriptors.len=descriptors_len;
    memcpy(cmd->data.cmd_sensor_server_send_descriptor_status.descriptors.data,descriptors,descriptors_len);

    cmd->header=sl_btmesh_cmd_sensor_server_send_descriptor_status_id+(((8+descriptors_len)&0xff)<<8)+(((8+descriptors_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_sensor_server_send_descriptor_status.result;

}

sl_status_t sl_btmesh_sensor_server_send_status(uint16_t client_address,
                                                uint16_t elem_index,
                                                uint16_t appkey_index,
                                                uint8_t flags,
                                                size_t sensor_data_len,
                                                const uint8_t* sensor_data) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_sensor_server_send_status.client_address=client_address;
    cmd->data.cmd_sensor_server_send_status.elem_index=elem_index;
    cmd->data.cmd_sensor_server_send_status.appkey_index=appkey_index;
    cmd->data.cmd_sensor_server_send_status.flags=flags;
    if ((8+sensor_data_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_sensor_server_send_status.sensor_data.len=sensor_data_len;
    memcpy(cmd->data.cmd_sensor_server_send_status.sensor_data.data,sensor_data,sensor_data_len);

    cmd->header=sl_btmesh_cmd_sensor_server_send_status_id+(((8+sensor_data_len)&0xff)<<8)+(((8+sensor_data_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_sensor_server_send_status.result;

}

sl_status_t sl_btmesh_sensor_server_send_column_status(uint16_t client_address,
                                                       uint16_t elem_index,
                                                       uint16_t appkey_index,
                                                       uint8_t flags,
                                                       uint16_t property_id,
                                                       size_t sensor_data_len,
                                                       const uint8_t* sensor_data) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_sensor_server_send_column_status.client_address=client_address;
    cmd->data.cmd_sensor_server_send_column_status.elem_index=elem_index;
    cmd->data.cmd_sensor_server_send_column_status.appkey_index=appkey_index;
    cmd->data.cmd_sensor_server_send_column_status.flags=flags;
    cmd->data.cmd_sensor_server_send_column_status.property_id=property_id;
    if ((10+sensor_data_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_sensor_server_send_column_status.sensor_data.len=sensor_data_len;
    memcpy(cmd->data.cmd_sensor_server_send_column_status.sensor_data.data,sensor_data,sensor_data_len);

    cmd->header=sl_btmesh_cmd_sensor_server_send_column_status_id+(((10+sensor_data_len)&0xff)<<8)+(((10+sensor_data_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_sensor_server_send_column_status.result;

}

sl_status_t sl_btmesh_sensor_server_send_series_status(uint16_t client_address,
                                                       uint16_t elem_index,
                                                       uint16_t appkey_index,
                                                       uint8_t flags,
                                                       uint16_t property_id,
                                                       size_t sensor_data_len,
                                                       const uint8_t* sensor_data) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_sensor_server_send_series_status.client_address=client_address;
    cmd->data.cmd_sensor_server_send_series_status.elem_index=elem_index;
    cmd->data.cmd_sensor_server_send_series_status.appkey_index=appkey_index;
    cmd->data.cmd_sensor_server_send_series_status.flags=flags;
    cmd->data.cmd_sensor_server_send_series_status.property_id=property_id;
    if ((10+sensor_data_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_sensor_server_send_series_status.sensor_data.len=sensor_data_len;
    memcpy(cmd->data.cmd_sensor_server_send_series_status.sensor_data.data,sensor_data,sensor_data_len);

    cmd->header=sl_btmesh_cmd_sensor_server_send_series_status_id+(((10+sensor_data_len)&0xff)<<8)+(((10+sensor_data_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_sensor_server_send_series_status.result;

}

sl_status_t sl_btmesh_sensor_setup_server_send_cadence_status(uint16_t client_address,
                                                              uint16_t elem_index,
                                                              uint16_t appkey_index,
                                                              uint8_t flags,
                                                              uint16_t property_id,
                                                              size_t params_len,
                                                              const uint8_t* params) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_sensor_setup_server_send_cadence_status.client_address=client_address;
    cmd->data.cmd_sensor_setup_server_send_cadence_status.elem_index=elem_index;
    cmd->data.cmd_sensor_setup_server_send_cadence_status.appkey_index=appkey_index;
    cmd->data.cmd_sensor_setup_server_send_cadence_status.flags=flags;
    cmd->data.cmd_sensor_setup_server_send_cadence_status.property_id=property_id;
    if ((10+params_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_sensor_setup_server_send_cadence_status.params.len=params_len;
    memcpy(cmd->data.cmd_sensor_setup_server_send_cadence_status.params.data,params,params_len);

    cmd->header=sl_btmesh_cmd_sensor_setup_server_send_cadence_status_id+(((10+params_len)&0xff)<<8)+(((10+params_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_sensor_setup_server_send_cadence_status.result;

}

sl_status_t sl_btmesh_sensor_setup_server_send_settings_status(uint16_t client_address,
                                                               uint16_t elem_index,
                                                               uint16_t appkey_index,
                                                               uint8_t flags,
                                                               uint16_t property_id,
                                                               size_t setting_ids_len,
                                                               const uint8_t* setting_ids) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_sensor_setup_server_send_settings_status.client_address=client_address;
    cmd->data.cmd_sensor_setup_server_send_settings_status.elem_index=elem_index;
    cmd->data.cmd_sensor_setup_server_send_settings_status.appkey_index=appkey_index;
    cmd->data.cmd_sensor_setup_server_send_settings_status.flags=flags;
    cmd->data.cmd_sensor_setup_server_send_settings_status.property_id=property_id;
    if ((10+setting_ids_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_sensor_setup_server_send_settings_status.setting_ids.len=setting_ids_len;
    memcpy(cmd->data.cmd_sensor_setup_server_send_settings_status.setting_ids.data,setting_ids,setting_ids_len);

    cmd->header=sl_btmesh_cmd_sensor_setup_server_send_settings_status_id+(((10+setting_ids_len)&0xff)<<8)+(((10+setting_ids_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_sensor_setup_server_send_settings_status.result;

}

sl_status_t sl_btmesh_sensor_setup_server_send_setting_status(uint16_t client_address,
                                                              uint16_t elem_index,
                                                              uint16_t appkey_index,
                                                              uint8_t flags,
                                                              uint16_t property_id,
                                                              uint16_t setting_id,
                                                              size_t raw_value_len,
                                                              const uint8_t* raw_value) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_sensor_setup_server_send_setting_status.client_address=client_address;
    cmd->data.cmd_sensor_setup_server_send_setting_status.elem_index=elem_index;
    cmd->data.cmd_sensor_setup_server_send_setting_status.appkey_index=appkey_index;
    cmd->data.cmd_sensor_setup_server_send_setting_status.flags=flags;
    cmd->data.cmd_sensor_setup_server_send_setting_status.property_id=property_id;
    cmd->data.cmd_sensor_setup_server_send_setting_status.setting_id=setting_id;
    if ((12+raw_value_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_sensor_setup_server_send_setting_status.raw_value.len=raw_value_len;
    memcpy(cmd->data.cmd_sensor_setup_server_send_setting_status.raw_value.data,raw_value,raw_value_len);

    cmd->header=sl_btmesh_cmd_sensor_setup_server_send_setting_status_id+(((12+raw_value_len)&0xff)<<8)+(((12+raw_value_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_sensor_setup_server_send_setting_status.result;

}

sl_status_t sl_btmesh_sensor_client_init() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_sensor_client_init_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_sensor_client_init.result;

}

sl_status_t sl_btmesh_sensor_client_deinit() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_sensor_client_deinit_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_sensor_client_deinit.result;

}

sl_status_t sl_btmesh_sensor_client_get_descriptor(uint16_t server_address,
                                                   uint16_t elem_index,
                                                   uint16_t appkey_index,
                                                   uint8_t flags,
                                                   uint16_t property_id) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_sensor_client_get_descriptor.server_address=server_address;
    cmd->data.cmd_sensor_client_get_descriptor.elem_index=elem_index;
    cmd->data.cmd_sensor_client_get_descriptor.appkey_index=appkey_index;
    cmd->data.cmd_sensor_client_get_descriptor.flags=flags;
    cmd->data.cmd_sensor_client_get_descriptor.property_id=property_id;

    cmd->header=sl_btmesh_cmd_sensor_client_get_descriptor_id+(((9)&0xff)<<8)+(((9)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_sensor_client_get_descriptor.result;

}

sl_status_t sl_btmesh_sensor_client_get(uint16_t server_address,
                                        uint16_t elem_index,
                                        uint16_t appkey_index,
                                        uint8_t flags,
                                        uint16_t property_id) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_sensor_client_get.server_address=server_address;
    cmd->data.cmd_sensor_client_get.elem_index=elem_index;
    cmd->data.cmd_sensor_client_get.appkey_index=appkey_index;
    cmd->data.cmd_sensor_client_get.flags=flags;
    cmd->data.cmd_sensor_client_get.property_id=property_id;

    cmd->header=sl_btmesh_cmd_sensor_client_get_id+(((9)&0xff)<<8)+(((9)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_sensor_client_get.result;

}

sl_status_t sl_btmesh_sensor_client_get_column(uint16_t server_address,
                                               uint16_t elem_index,
                                               uint16_t appkey_index,
                                               uint8_t flags,
                                               uint16_t property_id,
                                               size_t column_id_len,
                                               const uint8_t* column_id) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_sensor_client_get_column.server_address=server_address;
    cmd->data.cmd_sensor_client_get_column.elem_index=elem_index;
    cmd->data.cmd_sensor_client_get_column.appkey_index=appkey_index;
    cmd->data.cmd_sensor_client_get_column.flags=flags;
    cmd->data.cmd_sensor_client_get_column.property_id=property_id;
    if ((10+column_id_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_sensor_client_get_column.column_id.len=column_id_len;
    memcpy(cmd->data.cmd_sensor_client_get_column.column_id.data,column_id,column_id_len);

    cmd->header=sl_btmesh_cmd_sensor_client_get_column_id+(((10+column_id_len)&0xff)<<8)+(((10+column_id_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_sensor_client_get_column.result;

}

sl_status_t sl_btmesh_sensor_client_get_series(uint16_t server_address,
                                               uint16_t elem_index,
                                               uint16_t appkey_index,
                                               uint8_t flags,
                                               uint16_t property_id,
                                               size_t column_ids_len,
                                               const uint8_t* column_ids) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_sensor_client_get_series.server_address=server_address;
    cmd->data.cmd_sensor_client_get_series.elem_index=elem_index;
    cmd->data.cmd_sensor_client_get_series.appkey_index=appkey_index;
    cmd->data.cmd_sensor_client_get_series.flags=flags;
    cmd->data.cmd_sensor_client_get_series.property_id=property_id;
    if ((10+column_ids_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_sensor_client_get_series.column_ids.len=column_ids_len;
    memcpy(cmd->data.cmd_sensor_client_get_series.column_ids.data,column_ids,column_ids_len);

    cmd->header=sl_btmesh_cmd_sensor_client_get_series_id+(((10+column_ids_len)&0xff)<<8)+(((10+column_ids_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_sensor_client_get_series.result;

}

sl_status_t sl_btmesh_sensor_client_get_cadence(uint16_t server_address,
                                                uint16_t elem_index,
                                                uint16_t appkey_index,
                                                uint8_t flags,
                                                uint16_t property_id) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_sensor_client_get_cadence.server_address=server_address;
    cmd->data.cmd_sensor_client_get_cadence.elem_index=elem_index;
    cmd->data.cmd_sensor_client_get_cadence.appkey_index=appkey_index;
    cmd->data.cmd_sensor_client_get_cadence.flags=flags;
    cmd->data.cmd_sensor_client_get_cadence.property_id=property_id;

    cmd->header=sl_btmesh_cmd_sensor_client_get_cadence_id+(((9)&0xff)<<8)+(((9)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_sensor_client_get_cadence.result;

}

sl_status_t sl_btmesh_sensor_client_set_cadence(uint16_t server_address,
                                                uint16_t elem_index,
                                                uint16_t appkey_index,
                                                uint8_t flags,
                                                uint16_t property_id,
                                                size_t params_len,
                                                const uint8_t* params) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_sensor_client_set_cadence.server_address=server_address;
    cmd->data.cmd_sensor_client_set_cadence.elem_index=elem_index;
    cmd->data.cmd_sensor_client_set_cadence.appkey_index=appkey_index;
    cmd->data.cmd_sensor_client_set_cadence.flags=flags;
    cmd->data.cmd_sensor_client_set_cadence.property_id=property_id;
    if ((10+params_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_sensor_client_set_cadence.params.len=params_len;
    memcpy(cmd->data.cmd_sensor_client_set_cadence.params.data,params,params_len);

    cmd->header=sl_btmesh_cmd_sensor_client_set_cadence_id+(((10+params_len)&0xff)<<8)+(((10+params_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_sensor_client_set_cadence.result;

}

sl_status_t sl_btmesh_sensor_client_get_settings(uint16_t server_address,
                                                 uint16_t elem_index,
                                                 uint16_t appkey_index,
                                                 uint8_t flags,
                                                 uint16_t property_id) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_sensor_client_get_settings.server_address=server_address;
    cmd->data.cmd_sensor_client_get_settings.elem_index=elem_index;
    cmd->data.cmd_sensor_client_get_settings.appkey_index=appkey_index;
    cmd->data.cmd_sensor_client_get_settings.flags=flags;
    cmd->data.cmd_sensor_client_get_settings.property_id=property_id;

    cmd->header=sl_btmesh_cmd_sensor_client_get_settings_id+(((9)&0xff)<<8)+(((9)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_sensor_client_get_settings.result;

}

sl_status_t sl_btmesh_sensor_client_get_setting(uint16_t server_address,
                                                uint16_t elem_index,
                                                uint16_t appkey_index,
                                                uint8_t flags,
                                                uint16_t property_id,
                                                uint16_t setting_id) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_sensor_client_get_setting.server_address=server_address;
    cmd->data.cmd_sensor_client_get_setting.elem_index=elem_index;
    cmd->data.cmd_sensor_client_get_setting.appkey_index=appkey_index;
    cmd->data.cmd_sensor_client_get_setting.flags=flags;
    cmd->data.cmd_sensor_client_get_setting.property_id=property_id;
    cmd->data.cmd_sensor_client_get_setting.setting_id=setting_id;

    cmd->header=sl_btmesh_cmd_sensor_client_get_setting_id+(((11)&0xff)<<8)+(((11)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_sensor_client_get_setting.result;

}

sl_status_t sl_btmesh_sensor_client_set_setting(uint16_t server_address,
                                                uint16_t elem_index,
                                                uint16_t appkey_index,
                                                uint8_t flags,
                                                uint16_t property_id,
                                                uint16_t setting_id,
                                                size_t raw_value_len,
                                                const uint8_t* raw_value) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_sensor_client_set_setting.server_address=server_address;
    cmd->data.cmd_sensor_client_set_setting.elem_index=elem_index;
    cmd->data.cmd_sensor_client_set_setting.appkey_index=appkey_index;
    cmd->data.cmd_sensor_client_set_setting.flags=flags;
    cmd->data.cmd_sensor_client_set_setting.property_id=property_id;
    cmd->data.cmd_sensor_client_set_setting.setting_id=setting_id;
    if ((12+raw_value_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_sensor_client_set_setting.raw_value.len=raw_value_len;
    memcpy(cmd->data.cmd_sensor_client_set_setting.raw_value.data,raw_value,raw_value_len);

    cmd->header=sl_btmesh_cmd_sensor_client_set_setting_id+(((12+raw_value_len)&0xff)<<8)+(((12+raw_value_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_sensor_client_set_setting.result;

}

sl_status_t sl_btmesh_fw_update_client_init(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_update_client_init.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_fw_update_client_init_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_update_client_init.result;

}

sl_status_t sl_btmesh_fw_update_client_deinit(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_update_client_deinit.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_fw_update_client_deinit_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_update_client_deinit.result;

}

sl_status_t sl_btmesh_fw_update_client_get_info(uint16_t elem_index,
                                                uint16_t dst,
                                                uuid_128 virtual_address,
                                                uint16_t appkey_index,
                                                uint8_t ttl,
                                                uint8_t first_index,
                                                uint8_t max_entries) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_update_client_get_info.elem_index=elem_index;
    cmd->data.cmd_fw_update_client_get_info.dst=dst;
    cmd->data.cmd_fw_update_client_get_info.virtual_address=virtual_address;
    cmd->data.cmd_fw_update_client_get_info.appkey_index=appkey_index;
    cmd->data.cmd_fw_update_client_get_info.ttl=ttl;
    cmd->data.cmd_fw_update_client_get_info.first_index=first_index;
    cmd->data.cmd_fw_update_client_get_info.max_entries=max_entries;

    cmd->header=sl_btmesh_cmd_fw_update_client_get_info_id+(((25)&0xff)<<8)+(((25)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_update_client_get_info.result;

}

sl_status_t sl_btmesh_fw_update_client_get_update(uint16_t elem_index,
                                                  uint16_t dst,
                                                  uuid_128 virtual_address,
                                                  uint16_t appkey_index,
                                                  uint8_t ttl) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_update_client_get_update.elem_index=elem_index;
    cmd->data.cmd_fw_update_client_get_update.dst=dst;
    cmd->data.cmd_fw_update_client_get_update.virtual_address=virtual_address;
    cmd->data.cmd_fw_update_client_get_update.appkey_index=appkey_index;
    cmd->data.cmd_fw_update_client_get_update.ttl=ttl;

    cmd->header=sl_btmesh_cmd_fw_update_client_get_update_id+(((23)&0xff)<<8)+(((23)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_update_client_get_update.result;

}

sl_status_t sl_btmesh_fw_update_client_start_update(uint16_t elem_index,
                                                    uint16_t dst,
                                                    uuid_128 virtual_address,
                                                    uint16_t appkey_index,
                                                    uint8_t ttl,
                                                    uint8_t update_ttl,
                                                    uint16_t update_timeout_base,
                                                    sl_bt_uuid_64_t blob_id,
                                                    uint8_t fw_index,
                                                    size_t metadata_len,
                                                    const uint8_t* metadata) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_update_client_start_update.elem_index=elem_index;
    cmd->data.cmd_fw_update_client_start_update.dst=dst;
    cmd->data.cmd_fw_update_client_start_update.virtual_address=virtual_address;
    cmd->data.cmd_fw_update_client_start_update.appkey_index=appkey_index;
    cmd->data.cmd_fw_update_client_start_update.ttl=ttl;
    cmd->data.cmd_fw_update_client_start_update.update_ttl=update_ttl;
    cmd->data.cmd_fw_update_client_start_update.update_timeout_base=update_timeout_base;
    cmd->data.cmd_fw_update_client_start_update.blob_id=blob_id;
    cmd->data.cmd_fw_update_client_start_update.fw_index=fw_index;
    if ((36+metadata_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_fw_update_client_start_update.metadata.len=metadata_len;
    memcpy(cmd->data.cmd_fw_update_client_start_update.metadata.data,metadata,metadata_len);

    cmd->header=sl_btmesh_cmd_fw_update_client_start_update_id+(((36+metadata_len)&0xff)<<8)+(((36+metadata_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_update_client_start_update.result;

}

sl_status_t sl_btmesh_fw_update_client_cancel_update(uint16_t elem_index,
                                                     uint16_t dst,
                                                     uuid_128 virtual_address,
                                                     uint16_t appkey_index,
                                                     uint8_t ttl) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_update_client_cancel_update.elem_index=elem_index;
    cmd->data.cmd_fw_update_client_cancel_update.dst=dst;
    cmd->data.cmd_fw_update_client_cancel_update.virtual_address=virtual_address;
    cmd->data.cmd_fw_update_client_cancel_update.appkey_index=appkey_index;
    cmd->data.cmd_fw_update_client_cancel_update.ttl=ttl;

    cmd->header=sl_btmesh_cmd_fw_update_client_cancel_update_id+(((23)&0xff)<<8)+(((23)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_update_client_cancel_update.result;

}

sl_status_t sl_btmesh_fw_update_client_apply_update(uint16_t elem_index,
                                                    uint16_t dst,
                                                    uuid_128 virtual_address,
                                                    uint16_t appkey_index,
                                                    uint8_t ttl) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_update_client_apply_update.elem_index=elem_index;
    cmd->data.cmd_fw_update_client_apply_update.dst=dst;
    cmd->data.cmd_fw_update_client_apply_update.virtual_address=virtual_address;
    cmd->data.cmd_fw_update_client_apply_update.appkey_index=appkey_index;
    cmd->data.cmd_fw_update_client_apply_update.ttl=ttl;

    cmd->header=sl_btmesh_cmd_fw_update_client_apply_update_id+(((23)&0xff)<<8)+(((23)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_update_client_apply_update.result;

}

sl_status_t sl_btmesh_fw_update_client_check_metadata(uint16_t elem_index,
                                                      uint16_t dst,
                                                      uuid_128 virtual_address,
                                                      uint16_t appkey_index,
                                                      uint8_t ttl,
                                                      uint8_t fw_index,
                                                      size_t metadata_len,
                                                      const uint8_t* metadata) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_update_client_check_metadata.elem_index=elem_index;
    cmd->data.cmd_fw_update_client_check_metadata.dst=dst;
    cmd->data.cmd_fw_update_client_check_metadata.virtual_address=virtual_address;
    cmd->data.cmd_fw_update_client_check_metadata.appkey_index=appkey_index;
    cmd->data.cmd_fw_update_client_check_metadata.ttl=ttl;
    cmd->data.cmd_fw_update_client_check_metadata.fw_index=fw_index;
    if ((25+metadata_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_fw_update_client_check_metadata.metadata.len=metadata_len;
    memcpy(cmd->data.cmd_fw_update_client_check_metadata.metadata.data,metadata,metadata_len);

    cmd->header=sl_btmesh_cmd_fw_update_client_check_metadata_id+(((25+metadata_len)&0xff)<<8)+(((25+metadata_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_update_client_check_metadata.result;

}

sl_status_t sl_btmesh_lc_client_init(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_lc_client_init.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_lc_client_init_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_lc_client_init.result;

}

sl_status_t sl_btmesh_lc_client_get_mode(uint16_t server_address,
                                         uint16_t elem_index,
                                         uint16_t appkey_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_lc_client_get_mode.server_address=server_address;
    cmd->data.cmd_lc_client_get_mode.elem_index=elem_index;
    cmd->data.cmd_lc_client_get_mode.appkey_index=appkey_index;

    cmd->header=sl_btmesh_cmd_lc_client_get_mode_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_lc_client_get_mode.result;

}

sl_status_t sl_btmesh_lc_client_set_mode(uint16_t server_address,
                                         uint16_t elem_index,
                                         uint16_t appkey_index,
                                         uint8_t flags,
                                         uint8_t mode) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_lc_client_set_mode.server_address=server_address;
    cmd->data.cmd_lc_client_set_mode.elem_index=elem_index;
    cmd->data.cmd_lc_client_set_mode.appkey_index=appkey_index;
    cmd->data.cmd_lc_client_set_mode.flags=flags;
    cmd->data.cmd_lc_client_set_mode.mode=mode;

    cmd->header=sl_btmesh_cmd_lc_client_set_mode_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_lc_client_set_mode.result;

}

sl_status_t sl_btmesh_lc_client_get_om(uint16_t server_address,
                                       uint16_t elem_index,
                                       uint16_t appkey_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_lc_client_get_om.server_address=server_address;
    cmd->data.cmd_lc_client_get_om.elem_index=elem_index;
    cmd->data.cmd_lc_client_get_om.appkey_index=appkey_index;

    cmd->header=sl_btmesh_cmd_lc_client_get_om_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_lc_client_get_om.result;

}

sl_status_t sl_btmesh_lc_client_set_om(uint16_t server_address,
                                       uint16_t elem_index,
                                       uint16_t appkey_index,
                                       uint8_t flags,
                                       uint8_t mode) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_lc_client_set_om.server_address=server_address;
    cmd->data.cmd_lc_client_set_om.elem_index=elem_index;
    cmd->data.cmd_lc_client_set_om.appkey_index=appkey_index;
    cmd->data.cmd_lc_client_set_om.flags=flags;
    cmd->data.cmd_lc_client_set_om.mode=mode;

    cmd->header=sl_btmesh_cmd_lc_client_set_om_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_lc_client_set_om.result;

}

sl_status_t sl_btmesh_lc_client_get_light_onoff(uint16_t server_address,
                                                uint16_t elem_index,
                                                uint16_t appkey_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_lc_client_get_light_onoff.server_address=server_address;
    cmd->data.cmd_lc_client_get_light_onoff.elem_index=elem_index;
    cmd->data.cmd_lc_client_get_light_onoff.appkey_index=appkey_index;

    cmd->header=sl_btmesh_cmd_lc_client_get_light_onoff_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_lc_client_get_light_onoff.result;

}

sl_status_t sl_btmesh_lc_client_set_light_onoff(uint16_t server_address,
                                                uint16_t elem_index,
                                                uint16_t appkey_index,
                                                uint8_t flags,
                                                uint8_t target_state,
                                                uint8_t tid,
                                                uint32_t transition_time_ms,
                                                uint16_t message_delay_ms) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_lc_client_set_light_onoff.server_address=server_address;
    cmd->data.cmd_lc_client_set_light_onoff.elem_index=elem_index;
    cmd->data.cmd_lc_client_set_light_onoff.appkey_index=appkey_index;
    cmd->data.cmd_lc_client_set_light_onoff.flags=flags;
    cmd->data.cmd_lc_client_set_light_onoff.target_state=target_state;
    cmd->data.cmd_lc_client_set_light_onoff.tid=tid;
    cmd->data.cmd_lc_client_set_light_onoff.transition_time_ms=transition_time_ms;
    cmd->data.cmd_lc_client_set_light_onoff.message_delay_ms=message_delay_ms;

    cmd->header=sl_btmesh_cmd_lc_client_set_light_onoff_id+(((15)&0xff)<<8)+(((15)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_lc_client_set_light_onoff.result;

}

sl_status_t sl_btmesh_lc_client_get_property(uint16_t server_address,
                                             uint16_t elem_index,
                                             uint16_t appkey_index,
                                             uint16_t property_id) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_lc_client_get_property.server_address=server_address;
    cmd->data.cmd_lc_client_get_property.elem_index=elem_index;
    cmd->data.cmd_lc_client_get_property.appkey_index=appkey_index;
    cmd->data.cmd_lc_client_get_property.property_id=property_id;

    cmd->header=sl_btmesh_cmd_lc_client_get_property_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_lc_client_get_property.result;

}

sl_status_t sl_btmesh_lc_client_set_property(uint16_t server_address,
                                             uint16_t elem_index,
                                             uint16_t appkey_index,
                                             uint8_t flags,
                                             uint16_t property_id,
                                             size_t params_len,
                                             const uint8_t* params) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_lc_client_set_property.server_address=server_address;
    cmd->data.cmd_lc_client_set_property.elem_index=elem_index;
    cmd->data.cmd_lc_client_set_property.appkey_index=appkey_index;
    cmd->data.cmd_lc_client_set_property.flags=flags;
    cmd->data.cmd_lc_client_set_property.property_id=property_id;
    if ((10+params_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_lc_client_set_property.params.len=params_len;
    memcpy(cmd->data.cmd_lc_client_set_property.params.data,params,params_len);

    cmd->header=sl_btmesh_cmd_lc_client_set_property_id+(((10+params_len)&0xff)<<8)+(((10+params_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_lc_client_set_property.result;

}

sl_status_t sl_btmesh_lc_server_init(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_lc_server_init.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_lc_server_init_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_lc_server_init.result;

}

sl_status_t sl_btmesh_lc_server_deinit(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_lc_server_deinit.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_lc_server_deinit_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_lc_server_deinit.result;

}

sl_status_t sl_btmesh_lc_server_update_mode(uint16_t elem_index, uint8_t mode) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_lc_server_update_mode.elem_index=elem_index;
    cmd->data.cmd_lc_server_update_mode.mode=mode;

    cmd->header=sl_btmesh_cmd_lc_server_update_mode_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_lc_server_update_mode.result;

}

sl_status_t sl_btmesh_lc_server_update_om(uint16_t elem_index, uint8_t om) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_lc_server_update_om.elem_index=elem_index;
    cmd->data.cmd_lc_server_update_om.om=om;

    cmd->header=sl_btmesh_cmd_lc_server_update_om_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_lc_server_update_om.result;

}

sl_status_t sl_btmesh_lc_server_update_light_onoff(uint16_t elem_index,
                                                   uint8_t light_onoff,
                                                   uint32_t transition_time_ms) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_lc_server_update_light_onoff.elem_index=elem_index;
    cmd->data.cmd_lc_server_update_light_onoff.light_onoff=light_onoff;
    cmd->data.cmd_lc_server_update_light_onoff.transition_time_ms=transition_time_ms;

    cmd->header=sl_btmesh_cmd_lc_server_update_light_onoff_id+(((7)&0xff)<<8)+(((7)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_lc_server_update_light_onoff.result;

}

sl_status_t sl_btmesh_lc_server_init_all_properties(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_lc_server_init_all_properties.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_lc_server_init_all_properties_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_lc_server_init_all_properties.result;

}

sl_status_t sl_btmesh_lc_server_set_publish_mask(uint16_t elem_index,
                                                 uint16_t status_type,
                                                 uint8_t value) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_lc_server_set_publish_mask.elem_index=elem_index;
    cmd->data.cmd_lc_server_set_publish_mask.status_type=status_type;
    cmd->data.cmd_lc_server_set_publish_mask.value=value;

    cmd->header=sl_btmesh_cmd_lc_server_set_publish_mask_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_lc_server_set_publish_mask.result;

}

sl_status_t sl_btmesh_lc_server_set_regulator_interval(uint16_t elem_index,
                                                       uint8_t value) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_lc_server_set_regulator_interval.elem_index=elem_index;
    cmd->data.cmd_lc_server_set_regulator_interval.value=value;

    cmd->header=sl_btmesh_cmd_lc_server_set_regulator_interval_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_lc_server_set_regulator_interval.result;

}

sl_status_t sl_btmesh_lc_server_set_event_mask(uint16_t elem_index,
                                               uint16_t event_type,
                                               uint8_t value) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_lc_server_set_event_mask.elem_index=elem_index;
    cmd->data.cmd_lc_server_set_event_mask.event_type=event_type;
    cmd->data.cmd_lc_server_set_event_mask.value=value;

    cmd->header=sl_btmesh_cmd_lc_server_set_event_mask_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_lc_server_set_event_mask.result;

}

sl_status_t sl_btmesh_lc_server_get_lc_state(uint16_t elem_index,
                                             uint8_t *state,
                                             uint32_t *transition_time) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_lc_server_get_lc_state.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_lc_server_get_lc_state_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (state) {
        *state = rsp->data.rsp_lc_server_get_lc_state.state;
    }
    if (transition_time) {
        *transition_time = rsp->data.rsp_lc_server_get_lc_state.transition_time;
    }
    return rsp->data.rsp_lc_server_get_lc_state.result;

}

sl_status_t sl_btmesh_lc_setup_server_update_property(uint16_t elem_index,
                                                      uint16_t property_id,
                                                      size_t params_len,
                                                      const uint8_t* params) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_lc_setup_server_update_property.elem_index=elem_index;
    cmd->data.cmd_lc_setup_server_update_property.property_id=property_id;
    if ((5+params_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_lc_setup_server_update_property.params.len=params_len;
    memcpy(cmd->data.cmd_lc_setup_server_update_property.params.data,params,params_len);

    cmd->header=sl_btmesh_cmd_lc_setup_server_update_property_id+(((5+params_len)&0xff)<<8)+(((5+params_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_lc_setup_server_update_property.result;

}

sl_status_t sl_btmesh_scene_client_init(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_scene_client_init.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_scene_client_init_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_scene_client_init.result;

}

sl_status_t sl_btmesh_scene_client_get(uint16_t server_address,
                                       uint16_t elem_index,
                                       uint16_t appkey_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_scene_client_get.server_address=server_address;
    cmd->data.cmd_scene_client_get.elem_index=elem_index;
    cmd->data.cmd_scene_client_get.appkey_index=appkey_index;

    cmd->header=sl_btmesh_cmd_scene_client_get_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_scene_client_get.result;

}

sl_status_t sl_btmesh_scene_client_get_register(uint16_t server_address,
                                                uint16_t elem_index,
                                                uint16_t appkey_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_scene_client_get_register.server_address=server_address;
    cmd->data.cmd_scene_client_get_register.elem_index=elem_index;
    cmd->data.cmd_scene_client_get_register.appkey_index=appkey_index;

    cmd->header=sl_btmesh_cmd_scene_client_get_register_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_scene_client_get_register.result;

}

sl_status_t sl_btmesh_scene_client_recall(uint16_t server_address,
                                          uint16_t elem_index,
                                          uint16_t selected_scene,
                                          uint16_t appkey_index,
                                          uint8_t flags,
                                          uint8_t tid,
                                          uint32_t transition_time_ms,
                                          uint16_t delay_ms) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_scene_client_recall.server_address=server_address;
    cmd->data.cmd_scene_client_recall.elem_index=elem_index;
    cmd->data.cmd_scene_client_recall.selected_scene=selected_scene;
    cmd->data.cmd_scene_client_recall.appkey_index=appkey_index;
    cmd->data.cmd_scene_client_recall.flags=flags;
    cmd->data.cmd_scene_client_recall.tid=tid;
    cmd->data.cmd_scene_client_recall.transition_time_ms=transition_time_ms;
    cmd->data.cmd_scene_client_recall.delay_ms=delay_ms;

    cmd->header=sl_btmesh_cmd_scene_client_recall_id+(((16)&0xff)<<8)+(((16)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_scene_client_recall.result;

}

sl_status_t sl_btmesh_scene_client_store(uint16_t server_address,
                                         uint16_t elem_index,
                                         uint16_t selected_scene,
                                         uint16_t appkey_index,
                                         uint8_t flags) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_scene_client_store.server_address=server_address;
    cmd->data.cmd_scene_client_store.elem_index=elem_index;
    cmd->data.cmd_scene_client_store.selected_scene=selected_scene;
    cmd->data.cmd_scene_client_store.appkey_index=appkey_index;
    cmd->data.cmd_scene_client_store.flags=flags;

    cmd->header=sl_btmesh_cmd_scene_client_store_id+(((9)&0xff)<<8)+(((9)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_scene_client_store.result;

}

sl_status_t sl_btmesh_scene_client_delete(uint16_t server_address,
                                          uint16_t elem_index,
                                          uint16_t selected_scene,
                                          uint16_t appkey_index,
                                          uint8_t flags) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_scene_client_delete.server_address=server_address;
    cmd->data.cmd_scene_client_delete.elem_index=elem_index;
    cmd->data.cmd_scene_client_delete.selected_scene=selected_scene;
    cmd->data.cmd_scene_client_delete.appkey_index=appkey_index;
    cmd->data.cmd_scene_client_delete.flags=flags;

    cmd->header=sl_btmesh_cmd_scene_client_delete_id+(((9)&0xff)<<8)+(((9)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_scene_client_delete.result;

}

sl_status_t sl_btmesh_scene_server_init(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_scene_server_init.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_scene_server_init_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_scene_server_init.result;

}

sl_status_t sl_btmesh_scene_server_deinit(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_scene_server_deinit.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_scene_server_deinit_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_scene_server_deinit.result;

}

sl_status_t sl_btmesh_scene_server_reset_register(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_scene_server_reset_register.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_scene_server_reset_register_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_scene_server_reset_register.result;

}

sl_status_t sl_btmesh_scene_server_enable_compact_recall_events() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_scene_server_enable_compact_recall_events_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_scene_server_enable_compact_recall_events.result;

}

sl_status_t sl_btmesh_scene_setup_server_init(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_scene_setup_server_init.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_scene_setup_server_init_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_scene_setup_server_init.result;

}

sl_status_t sl_btmesh_scheduler_client_init(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_scheduler_client_init.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_scheduler_client_init_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_scheduler_client_init.result;

}

sl_status_t sl_btmesh_scheduler_client_deinit(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_scheduler_client_deinit.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_scheduler_client_deinit_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_scheduler_client_deinit.result;

}

sl_status_t sl_btmesh_scheduler_client_get(uint16_t server_address,
                                           uint16_t elem_index,
                                           uint16_t appkey_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_scheduler_client_get.server_address=server_address;
    cmd->data.cmd_scheduler_client_get.elem_index=elem_index;
    cmd->data.cmd_scheduler_client_get.appkey_index=appkey_index;

    cmd->header=sl_btmesh_cmd_scheduler_client_get_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_scheduler_client_get.result;

}

sl_status_t sl_btmesh_scheduler_client_get_action(uint16_t server_address,
                                                  uint16_t elem_index,
                                                  uint16_t appkey_index,
                                                  uint8_t index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_scheduler_client_get_action.server_address=server_address;
    cmd->data.cmd_scheduler_client_get_action.elem_index=elem_index;
    cmd->data.cmd_scheduler_client_get_action.appkey_index=appkey_index;
    cmd->data.cmd_scheduler_client_get_action.index=index;

    cmd->header=sl_btmesh_cmd_scheduler_client_get_action_id+(((7)&0xff)<<8)+(((7)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_scheduler_client_get_action.result;

}

sl_status_t sl_btmesh_scheduler_client_set_action(uint16_t server_address,
                                                  uint16_t elem_index,
                                                  uint16_t appkey_index,
                                                  uint8_t flags,
                                                  uint8_t index,
                                                  uint8_t year,
                                                  uint16_t month,
                                                  uint8_t day,
                                                  uint8_t hour,
                                                  uint8_t minute,
                                                  uint8_t second,
                                                  uint8_t day_of_week,
                                                  uint8_t action,
                                                  uint32_t transition_time_ms,
                                                  uint16_t scene_number) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_scheduler_client_set_action.server_address=server_address;
    cmd->data.cmd_scheduler_client_set_action.elem_index=elem_index;
    cmd->data.cmd_scheduler_client_set_action.appkey_index=appkey_index;
    cmd->data.cmd_scheduler_client_set_action.flags=flags;
    cmd->data.cmd_scheduler_client_set_action.index=index;
    cmd->data.cmd_scheduler_client_set_action.year=year;
    cmd->data.cmd_scheduler_client_set_action.month=month;
    cmd->data.cmd_scheduler_client_set_action.day=day;
    cmd->data.cmd_scheduler_client_set_action.hour=hour;
    cmd->data.cmd_scheduler_client_set_action.minute=minute;
    cmd->data.cmd_scheduler_client_set_action.second=second;
    cmd->data.cmd_scheduler_client_set_action.day_of_week=day_of_week;
    cmd->data.cmd_scheduler_client_set_action.action=action;
    cmd->data.cmd_scheduler_client_set_action.transition_time_ms=transition_time_ms;
    cmd->data.cmd_scheduler_client_set_action.scene_number=scene_number;

    cmd->header=sl_btmesh_cmd_scheduler_client_set_action_id+(((23)&0xff)<<8)+(((23)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_scheduler_client_set_action.result;

}

sl_status_t sl_btmesh_scheduler_server_init(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_scheduler_server_init.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_scheduler_server_init_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_scheduler_server_init.result;

}

sl_status_t sl_btmesh_scheduler_server_deinit(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_scheduler_server_deinit.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_scheduler_server_deinit_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_scheduler_server_deinit.result;

}

sl_status_t sl_btmesh_scheduler_server_get(uint16_t elem_index,
                                           uint16_t *status) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_scheduler_server_get.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_scheduler_server_get_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (status) {
        *status = rsp->data.rsp_scheduler_server_get.status;
    }
    return rsp->data.rsp_scheduler_server_get.result;

}

sl_status_t sl_btmesh_scheduler_server_get_action(uint16_t elem_index,
                                                  uint8_t index,
                                                  uint8_t *index_,
                                                  uint8_t *year,
                                                  uint16_t *month,
                                                  uint8_t *day,
                                                  uint8_t *hour,
                                                  uint8_t *minute,
                                                  uint8_t *second,
                                                  uint8_t *day_of_week,
                                                  uint8_t *action,
                                                  uint32_t *transition_time_ms,
                                                  uint16_t *scene_number) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_scheduler_server_get_action.elem_index=elem_index;
    cmd->data.cmd_scheduler_server_get_action.index=index;

    cmd->header=sl_btmesh_cmd_scheduler_server_get_action_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (index_) {
        *index_ = rsp->data.rsp_scheduler_server_get_action.index_;
    }
    if (year) {
        *year = rsp->data.rsp_scheduler_server_get_action.year;
    }
    if (month) {
        *month = rsp->data.rsp_scheduler_server_get_action.month;
    }
    if (day) {
        *day = rsp->data.rsp_scheduler_server_get_action.day;
    }
    if (hour) {
        *hour = rsp->data.rsp_scheduler_server_get_action.hour;
    }
    if (minute) {
        *minute = rsp->data.rsp_scheduler_server_get_action.minute;
    }
    if (second) {
        *second = rsp->data.rsp_scheduler_server_get_action.second;
    }
    if (day_of_week) {
        *day_of_week = rsp->data.rsp_scheduler_server_get_action.day_of_week;
    }
    if (action) {
        *action = rsp->data.rsp_scheduler_server_get_action.action;
    }
    if (transition_time_ms) {
        *transition_time_ms = rsp->data.rsp_scheduler_server_get_action.transition_time_ms;
    }
    if (scene_number) {
        *scene_number = rsp->data.rsp_scheduler_server_get_action.scene_number;
    }
    return rsp->data.rsp_scheduler_server_get_action.result;

}

sl_status_t sl_btmesh_scheduler_server_set_action(uint16_t elem_index,
                                                  uint8_t index,
                                                  uint8_t year,
                                                  uint16_t month,
                                                  uint8_t day,
                                                  uint8_t hour,
                                                  uint8_t minute,
                                                  uint8_t second,
                                                  uint8_t day_of_week,
                                                  uint8_t action,
                                                  uint32_t transition_time_ms,
                                                  uint16_t scene_number) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_scheduler_server_set_action.elem_index=elem_index;
    cmd->data.cmd_scheduler_server_set_action.index=index;
    cmd->data.cmd_scheduler_server_set_action.year=year;
    cmd->data.cmd_scheduler_server_set_action.month=month;
    cmd->data.cmd_scheduler_server_set_action.day=day;
    cmd->data.cmd_scheduler_server_set_action.hour=hour;
    cmd->data.cmd_scheduler_server_set_action.minute=minute;
    cmd->data.cmd_scheduler_server_set_action.second=second;
    cmd->data.cmd_scheduler_server_set_action.day_of_week=day_of_week;
    cmd->data.cmd_scheduler_server_set_action.action=action;
    cmd->data.cmd_scheduler_server_set_action.transition_time_ms=transition_time_ms;
    cmd->data.cmd_scheduler_server_set_action.scene_number=scene_number;

    cmd->header=sl_btmesh_cmd_scheduler_server_set_action_id+(((18)&0xff)<<8)+(((18)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_scheduler_server_set_action.result;

}

sl_status_t sl_btmesh_fw_update_server_init(uint16_t elem_index,
                                            uint8_t num_installed_fw,
                                            uint8_t max_metadata_len) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_update_server_init.elem_index=elem_index;
    cmd->data.cmd_fw_update_server_init.num_installed_fw=num_installed_fw;
    cmd->data.cmd_fw_update_server_init.max_metadata_len=max_metadata_len;

    cmd->header=sl_btmesh_cmd_fw_update_server_init_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_update_server_init.result;

}

sl_status_t sl_btmesh_fw_update_server_deinit(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_update_server_deinit.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_fw_update_server_deinit_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_update_server_deinit.result;

}

sl_status_t sl_btmesh_fw_update_server_check_fw_metadata_rsp(uint16_t elem_index,
                                                             uint8_t response_type,
                                                             uint8_t additional_information,
                                                             uint8_t fw_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_update_server_check_fw_metadata_rsp.elem_index=elem_index;
    cmd->data.cmd_fw_update_server_check_fw_metadata_rsp.response_type=response_type;
    cmd->data.cmd_fw_update_server_check_fw_metadata_rsp.additional_information=additional_information;
    cmd->data.cmd_fw_update_server_check_fw_metadata_rsp.fw_index=fw_index;

    cmd->header=sl_btmesh_cmd_fw_update_server_check_fw_metadata_rsp_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_update_server_check_fw_metadata_rsp.result;

}

sl_status_t sl_btmesh_fw_update_server_update_start_rsp(uint16_t elem_index,
                                                        uint8_t response_type,
                                                        uint8_t additional_information) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_update_server_update_start_rsp.elem_index=elem_index;
    cmd->data.cmd_fw_update_server_update_start_rsp.response_type=response_type;
    cmd->data.cmd_fw_update_server_update_start_rsp.additional_information=additional_information;

    cmd->header=sl_btmesh_cmd_fw_update_server_update_start_rsp_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_update_server_update_start_rsp.result;

}

sl_status_t sl_btmesh_fw_update_server_verify_fw_rsp(uint16_t elem_index,
                                                     uint8_t accept) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_update_server_verify_fw_rsp.elem_index=elem_index;
    cmd->data.cmd_fw_update_server_verify_fw_rsp.accept=accept;

    cmd->header=sl_btmesh_cmd_fw_update_server_verify_fw_rsp_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_update_server_verify_fw_rsp.result;

}

sl_status_t sl_btmesh_fw_update_server_distributor_self_update_rsp(uint16_t elem_index,
                                                                   uint8_t response_type,
                                                                   uint8_t additional_information) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_update_server_distributor_self_update_rsp.elem_index=elem_index;
    cmd->data.cmd_fw_update_server_distributor_self_update_rsp.response_type=response_type;
    cmd->data.cmd_fw_update_server_distributor_self_update_rsp.additional_information=additional_information;

    cmd->header=sl_btmesh_cmd_fw_update_server_distributor_self_update_rsp_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_update_server_distributor_self_update_rsp.result;

}

sl_status_t sl_btmesh_time_server_init(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_time_server_init.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_time_server_init_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_time_server_init.result;

}

sl_status_t sl_btmesh_time_server_deinit(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_time_server_deinit.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_time_server_deinit_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_time_server_deinit.result;

}

sl_status_t sl_btmesh_time_server_get_time(uint16_t elem_index,
                                           uint64_t *tai_seconds,
                                           uint8_t *subsecond,
                                           uint8_t *uncertainty,
                                           uint8_t *time_authority,
                                           int16_t *time_zone_offset,
                                           int32_t *tai_utc_delta) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_time_server_get_time.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_time_server_get_time_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (tai_seconds) {
        *tai_seconds = rsp->data.rsp_time_server_get_time.tai_seconds;
    }
    if (subsecond) {
        *subsecond = rsp->data.rsp_time_server_get_time.subsecond;
    }
    if (uncertainty) {
        *uncertainty = rsp->data.rsp_time_server_get_time.uncertainty;
    }
    if (time_authority) {
        *time_authority = rsp->data.rsp_time_server_get_time.time_authority;
    }
    if (time_zone_offset) {
        *time_zone_offset = rsp->data.rsp_time_server_get_time.time_zone_offset;
    }
    if (tai_utc_delta) {
        *tai_utc_delta = rsp->data.rsp_time_server_get_time.tai_utc_delta;
    }
    return rsp->data.rsp_time_server_get_time.result;

}

sl_status_t sl_btmesh_time_server_set_time(uint16_t elem_index,
                                           uint64_t tai_seconds,
                                           uint8_t subsecond,
                                           uint8_t uncertainty,
                                           uint8_t time_authority,
                                           int16_t time_zone_offset,
                                           int32_t tai_utc_delta) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_time_server_set_time.elem_index=elem_index;
    cmd->data.cmd_time_server_set_time.tai_seconds=tai_seconds;
    cmd->data.cmd_time_server_set_time.subsecond=subsecond;
    cmd->data.cmd_time_server_set_time.uncertainty=uncertainty;
    cmd->data.cmd_time_server_set_time.time_authority=time_authority;
    cmd->data.cmd_time_server_set_time.time_zone_offset=time_zone_offset;
    cmd->data.cmd_time_server_set_time.tai_utc_delta=tai_utc_delta;

    cmd->header=sl_btmesh_cmd_time_server_set_time_id+(((19)&0xff)<<8)+(((19)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_time_server_set_time.result;

}

sl_status_t sl_btmesh_time_server_get_time_zone_offset_new(uint16_t elem_index,
                                                           int16_t *new_offset,
                                                           uint64_t *tai_of_zone_change) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_time_server_get_time_zone_offset_new.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_time_server_get_time_zone_offset_new_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (new_offset) {
        *new_offset = rsp->data.rsp_time_server_get_time_zone_offset_new.new_offset;
    }
    if (tai_of_zone_change) {
        *tai_of_zone_change = rsp->data.rsp_time_server_get_time_zone_offset_new.tai_of_zone_change;
    }
    return rsp->data.rsp_time_server_get_time_zone_offset_new.result;

}

sl_status_t sl_btmesh_time_server_set_time_zone_offset_new(uint16_t elem_index,
                                                           int16_t new_offset,
                                                           uint64_t tai_of_zone_change) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_time_server_set_time_zone_offset_new.elem_index=elem_index;
    cmd->data.cmd_time_server_set_time_zone_offset_new.new_offset=new_offset;
    cmd->data.cmd_time_server_set_time_zone_offset_new.tai_of_zone_change=tai_of_zone_change;

    cmd->header=sl_btmesh_cmd_time_server_set_time_zone_offset_new_id+(((12)&0xff)<<8)+(((12)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_time_server_set_time_zone_offset_new.result;

}

sl_status_t sl_btmesh_time_server_get_tai_utc_delta_new(uint16_t elem_index,
                                                        int32_t *new_delta,
                                                        uint64_t *tai_of_delta_change) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_time_server_get_tai_utc_delta_new.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_time_server_get_tai_utc_delta_new_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (new_delta) {
        *new_delta = rsp->data.rsp_time_server_get_tai_utc_delta_new.new_delta;
    }
    if (tai_of_delta_change) {
        *tai_of_delta_change = rsp->data.rsp_time_server_get_tai_utc_delta_new.tai_of_delta_change;
    }
    return rsp->data.rsp_time_server_get_tai_utc_delta_new.result;

}

sl_status_t sl_btmesh_time_server_set_tai_utc_delta_new(uint16_t elem_index,
                                                        int32_t new_delta,
                                                        uint64_t tai_of_delta_change) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_time_server_set_tai_utc_delta_new.elem_index=elem_index;
    cmd->data.cmd_time_server_set_tai_utc_delta_new.new_delta=new_delta;
    cmd->data.cmd_time_server_set_tai_utc_delta_new.tai_of_delta_change=tai_of_delta_change;

    cmd->header=sl_btmesh_cmd_time_server_set_tai_utc_delta_new_id+(((14)&0xff)<<8)+(((14)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_time_server_set_tai_utc_delta_new.result;

}

sl_status_t sl_btmesh_time_server_get_time_role(uint16_t elem_index,
                                                uint8_t *time_role) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_time_server_get_time_role.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_time_server_get_time_role_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (time_role) {
        *time_role = rsp->data.rsp_time_server_get_time_role.time_role;
    }
    return rsp->data.rsp_time_server_get_time_role.result;

}

sl_status_t sl_btmesh_time_server_set_time_role(uint16_t elem_index,
                                                uint8_t time_role) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_time_server_set_time_role.elem_index=elem_index;
    cmd->data.cmd_time_server_set_time_role.time_role=time_role;

    cmd->header=sl_btmesh_cmd_time_server_set_time_role_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_time_server_set_time_role.result;

}

sl_status_t sl_btmesh_time_server_get_datetime(uint16_t elem_index,
                                               uint16_t *year,
                                               uint8_t *month,
                                               uint8_t *day,
                                               uint8_t *hour,
                                               uint8_t *min,
                                               uint8_t *sec,
                                               uint16_t *ms,
                                               int16_t *timezone,
                                               uint8_t *day_of_week) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_time_server_get_datetime.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_time_server_get_datetime_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (year) {
        *year = rsp->data.rsp_time_server_get_datetime.year;
    }
    if (month) {
        *month = rsp->data.rsp_time_server_get_datetime.month;
    }
    if (day) {
        *day = rsp->data.rsp_time_server_get_datetime.day;
    }
    if (hour) {
        *hour = rsp->data.rsp_time_server_get_datetime.hour;
    }
    if (min) {
        *min = rsp->data.rsp_time_server_get_datetime.min;
    }
    if (sec) {
        *sec = rsp->data.rsp_time_server_get_datetime.sec;
    }
    if (ms) {
        *ms = rsp->data.rsp_time_server_get_datetime.ms;
    }
    if (timezone) {
        *timezone = rsp->data.rsp_time_server_get_datetime.timezone;
    }
    if (day_of_week) {
        *day_of_week = rsp->data.rsp_time_server_get_datetime.day_of_week;
    }
    return rsp->data.rsp_time_server_get_datetime.result;

}

sl_status_t sl_btmesh_time_server_publish(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_time_server_publish.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_time_server_publish_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_time_server_publish.result;

}

sl_status_t sl_btmesh_time_server_status(uint16_t destination_address,
                                         uint16_t elem_index,
                                         uint16_t appkey_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_time_server_status.destination_address=destination_address;
    cmd->data.cmd_time_server_status.elem_index=elem_index;
    cmd->data.cmd_time_server_status.appkey_index=appkey_index;

    cmd->header=sl_btmesh_cmd_time_server_status_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_time_server_status.result;

}

sl_status_t sl_btmesh_time_client_init(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_time_client_init.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_time_client_init_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_time_client_init.result;

}

sl_status_t sl_btmesh_time_client_deinit(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_time_client_deinit.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_time_client_deinit_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_time_client_deinit.result;

}

sl_status_t sl_btmesh_time_client_get_time(uint16_t server_address,
                                           uint16_t elem_index,
                                           uint16_t appkey_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_time_client_get_time.server_address=server_address;
    cmd->data.cmd_time_client_get_time.elem_index=elem_index;
    cmd->data.cmd_time_client_get_time.appkey_index=appkey_index;

    cmd->header=sl_btmesh_cmd_time_client_get_time_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_time_client_get_time.result;

}

sl_status_t sl_btmesh_time_client_set_time(uint16_t server_address,
                                           uint16_t elem_index,
                                           uint16_t appkey_index,
                                           uint64_t tai_seconds,
                                           uint8_t subsecond,
                                           uint8_t uncertainty,
                                           uint8_t time_authority,
                                           int32_t tai_utc_delta,
                                           int16_t time_zone_offset) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_time_client_set_time.server_address=server_address;
    cmd->data.cmd_time_client_set_time.elem_index=elem_index;
    cmd->data.cmd_time_client_set_time.appkey_index=appkey_index;
    cmd->data.cmd_time_client_set_time.tai_seconds=tai_seconds;
    cmd->data.cmd_time_client_set_time.subsecond=subsecond;
    cmd->data.cmd_time_client_set_time.uncertainty=uncertainty;
    cmd->data.cmd_time_client_set_time.time_authority=time_authority;
    cmd->data.cmd_time_client_set_time.tai_utc_delta=tai_utc_delta;
    cmd->data.cmd_time_client_set_time.time_zone_offset=time_zone_offset;

    cmd->header=sl_btmesh_cmd_time_client_set_time_id+(((23)&0xff)<<8)+(((23)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_time_client_set_time.result;

}

sl_status_t sl_btmesh_time_client_get_time_zone(uint16_t server_address,
                                                uint16_t elem_index,
                                                uint16_t appkey_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_time_client_get_time_zone.server_address=server_address;
    cmd->data.cmd_time_client_get_time_zone.elem_index=elem_index;
    cmd->data.cmd_time_client_get_time_zone.appkey_index=appkey_index;

    cmd->header=sl_btmesh_cmd_time_client_get_time_zone_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_time_client_get_time_zone.result;

}

sl_status_t sl_btmesh_time_client_set_time_zone(uint16_t server_address,
                                                uint16_t elem_index,
                                                uint16_t appkey_index,
                                                int16_t time_zone_offset_new,
                                                uint64_t tai_of_zone_change) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_time_client_set_time_zone.server_address=server_address;
    cmd->data.cmd_time_client_set_time_zone.elem_index=elem_index;
    cmd->data.cmd_time_client_set_time_zone.appkey_index=appkey_index;
    cmd->data.cmd_time_client_set_time_zone.time_zone_offset_new=time_zone_offset_new;
    cmd->data.cmd_time_client_set_time_zone.tai_of_zone_change=tai_of_zone_change;

    cmd->header=sl_btmesh_cmd_time_client_set_time_zone_id+(((16)&0xff)<<8)+(((16)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_time_client_set_time_zone.result;

}

sl_status_t sl_btmesh_time_client_get_tai_utc_delta(uint16_t server_address,
                                                    uint16_t elem_index,
                                                    uint16_t appkey_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_time_client_get_tai_utc_delta.server_address=server_address;
    cmd->data.cmd_time_client_get_tai_utc_delta.elem_index=elem_index;
    cmd->data.cmd_time_client_get_tai_utc_delta.appkey_index=appkey_index;

    cmd->header=sl_btmesh_cmd_time_client_get_tai_utc_delta_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_time_client_get_tai_utc_delta.result;

}

sl_status_t sl_btmesh_time_client_set_tai_utc_delta(uint16_t server_address,
                                                    uint16_t elem_index,
                                                    uint16_t appkey_index,
                                                    int32_t tai_utc_delta_new,
                                                    uint64_t tai_of_delta_change) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_time_client_set_tai_utc_delta.server_address=server_address;
    cmd->data.cmd_time_client_set_tai_utc_delta.elem_index=elem_index;
    cmd->data.cmd_time_client_set_tai_utc_delta.appkey_index=appkey_index;
    cmd->data.cmd_time_client_set_tai_utc_delta.tai_utc_delta_new=tai_utc_delta_new;
    cmd->data.cmd_time_client_set_tai_utc_delta.tai_of_delta_change=tai_of_delta_change;

    cmd->header=sl_btmesh_cmd_time_client_set_tai_utc_delta_id+(((18)&0xff)<<8)+(((18)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_time_client_set_tai_utc_delta.result;

}

sl_status_t sl_btmesh_time_client_get_time_role(uint16_t server_address,
                                                uint16_t elem_index,
                                                uint16_t appkey_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_time_client_get_time_role.server_address=server_address;
    cmd->data.cmd_time_client_get_time_role.elem_index=elem_index;
    cmd->data.cmd_time_client_get_time_role.appkey_index=appkey_index;

    cmd->header=sl_btmesh_cmd_time_client_get_time_role_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_time_client_get_time_role.result;

}

sl_status_t sl_btmesh_time_client_set_time_role(uint16_t server_address,
                                                uint16_t elem_index,
                                                uint16_t appkey_index,
                                                uint8_t time_role) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_time_client_set_time_role.server_address=server_address;
    cmd->data.cmd_time_client_set_time_role.elem_index=elem_index;
    cmd->data.cmd_time_client_set_time_role.appkey_index=appkey_index;
    cmd->data.cmd_time_client_set_time_role.time_role=time_role;

    cmd->header=sl_btmesh_cmd_time_client_set_time_role_id+(((7)&0xff)<<8)+(((7)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_time_client_set_time_role.result;

}

sl_status_t sl_btmesh_fw_dist_server_init(uint16_t elem_index,
                                          uint16_t max_node_list_size,
                                          uint16_t max_fw_entries,
                                          uint32_t max_fw_size,
                                          uint32_t total_store_size,
                                          uint16_t multicast_threshold,
                                          size_t oob_supported_uri_scheme_names_len,
                                          const uint8_t* oob_supported_uri_scheme_names) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_server_init.elem_index=elem_index;
    cmd->data.cmd_fw_dist_server_init.max_node_list_size=max_node_list_size;
    cmd->data.cmd_fw_dist_server_init.max_fw_entries=max_fw_entries;
    cmd->data.cmd_fw_dist_server_init.max_fw_size=max_fw_size;
    cmd->data.cmd_fw_dist_server_init.total_store_size=total_store_size;
    cmd->data.cmd_fw_dist_server_init.multicast_threshold=multicast_threshold;
    if ((17+oob_supported_uri_scheme_names_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_fw_dist_server_init.oob_supported_uri_scheme_names.len=oob_supported_uri_scheme_names_len;
    memcpy(cmd->data.cmd_fw_dist_server_init.oob_supported_uri_scheme_names.data,oob_supported_uri_scheme_names,oob_supported_uri_scheme_names_len);

    cmd->header=sl_btmesh_cmd_fw_dist_server_init_id+(((17+oob_supported_uri_scheme_names_len)&0xff)<<8)+(((17+oob_supported_uri_scheme_names_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_server_init.result;

}

sl_status_t sl_btmesh_fw_dist_server_deinit(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_server_deinit.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_fw_dist_server_deinit_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_server_deinit.result;

}

sl_status_t sl_btmesh_fw_dist_server_upload_start_rsp(uint16_t elem_index,
                                                      uint8_t status) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_server_upload_start_rsp.elem_index=elem_index;
    cmd->data.cmd_fw_dist_server_upload_start_rsp.status=status;

    cmd->header=sl_btmesh_cmd_fw_dist_server_upload_start_rsp_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_server_upload_start_rsp.result;

}

sl_status_t sl_btmesh_fw_dist_server_execute_distribution_step(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_server_execute_distribution_step.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_fw_dist_server_execute_distribution_step_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_server_execute_distribution_step.result;

}

sl_status_t sl_btmesh_fw_dist_server_upload_oob_start_rsp(uint16_t elem_index,
                                                          uint8_t status_code,
                                                          size_t fwid_len,
                                                          const uint8_t* fwid) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_server_upload_oob_start_rsp.elem_index=elem_index;
    cmd->data.cmd_fw_dist_server_upload_oob_start_rsp.status_code=status_code;
    if ((4+fwid_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_fw_dist_server_upload_oob_start_rsp.fwid.len=fwid_len;
    memcpy(cmd->data.cmd_fw_dist_server_upload_oob_start_rsp.fwid.data,fwid,fwid_len);

    cmd->header=sl_btmesh_cmd_fw_dist_server_upload_oob_start_rsp_id+(((4+fwid_len)&0xff)<<8)+(((4+fwid_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_server_upload_oob_start_rsp.result;

}

sl_status_t sl_btmesh_fw_dist_server_set_upload_oob_metadata(uint16_t elem_index,
                                                             size_t metadata_len,
                                                             const uint8_t* metadata) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_server_set_upload_oob_metadata.elem_index=elem_index;
    if ((3+metadata_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_fw_dist_server_set_upload_oob_metadata.metadata.len=metadata_len;
    memcpy(cmd->data.cmd_fw_dist_server_set_upload_oob_metadata.metadata.data,metadata,metadata_len);

    cmd->header=sl_btmesh_cmd_fw_dist_server_set_upload_oob_metadata_id+(((3+metadata_len)&0xff)<<8)+(((3+metadata_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_server_set_upload_oob_metadata.result;

}

sl_status_t sl_btmesh_fw_dist_server_set_upload_oob_image_size(uint16_t elem_index,
                                                               uint32_t size) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_server_set_upload_oob_image_size.elem_index=elem_index;
    cmd->data.cmd_fw_dist_server_set_upload_oob_image_size.size=size;

    cmd->header=sl_btmesh_cmd_fw_dist_server_set_upload_oob_image_size_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_server_set_upload_oob_image_size.result;

}

sl_status_t sl_btmesh_fw_dist_server_set_upload_oob_progress(uint16_t elem_index,
                                                             uint8_t error,
                                                             uint8_t progress,
                                                             uint16_t *fw_list_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_server_set_upload_oob_progress.elem_index=elem_index;
    cmd->data.cmd_fw_dist_server_set_upload_oob_progress.error=error;
    cmd->data.cmd_fw_dist_server_set_upload_oob_progress.progress=progress;

    cmd->header=sl_btmesh_cmd_fw_dist_server_set_upload_oob_progress_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (fw_list_index) {
        *fw_list_index = rsp->data.rsp_fw_dist_server_set_upload_oob_progress.fw_list_index;
    }
    return rsp->data.rsp_fw_dist_server_set_upload_oob_progress.result;

}

sl_status_t sl_btmesh_fw_dist_server_get_node_status_by_index(uint16_t elem_index,
                                                              uint16_t entry_index,
                                                              uint16_t *address,
                                                              uint8_t *retrieved_phase,
                                                              uint8_t *update_server_status,
                                                              uint8_t *mbt_server_status,
                                                              uint8_t *transfer_progress,
                                                              uint8_t *fw_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_server_get_node_status_by_index.elem_index=elem_index;
    cmd->data.cmd_fw_dist_server_get_node_status_by_index.entry_index=entry_index;

    cmd->header=sl_btmesh_cmd_fw_dist_server_get_node_status_by_index_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (address) {
        *address = rsp->data.rsp_fw_dist_server_get_node_status_by_index.address;
    }
    if (retrieved_phase) {
        *retrieved_phase = rsp->data.rsp_fw_dist_server_get_node_status_by_index.retrieved_phase;
    }
    if (update_server_status) {
        *update_server_status = rsp->data.rsp_fw_dist_server_get_node_status_by_index.update_server_status;
    }
    if (mbt_server_status) {
        *mbt_server_status = rsp->data.rsp_fw_dist_server_get_node_status_by_index.mbt_server_status;
    }
    if (transfer_progress) {
        *transfer_progress = rsp->data.rsp_fw_dist_server_get_node_status_by_index.transfer_progress;
    }
    if (fw_index) {
        *fw_index = rsp->data.rsp_fw_dist_server_get_node_status_by_index.fw_index;
    }
    return rsp->data.rsp_fw_dist_server_get_node_status_by_index.result;

}

sl_status_t sl_btmesh_fw_dist_server_get_node_status_by_address(uint16_t elem_index,
                                                                uint16_t node_address,
                                                                uint16_t *address,
                                                                uint8_t *retrieved_phase,
                                                                uint8_t *update_server_status,
                                                                uint8_t *mbt_server_status,
                                                                uint8_t *transfer_progress,
                                                                uint8_t *fw_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_server_get_node_status_by_address.elem_index=elem_index;
    cmd->data.cmd_fw_dist_server_get_node_status_by_address.node_address=node_address;

    cmd->header=sl_btmesh_cmd_fw_dist_server_get_node_status_by_address_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (address) {
        *address = rsp->data.rsp_fw_dist_server_get_node_status_by_address.address;
    }
    if (retrieved_phase) {
        *retrieved_phase = rsp->data.rsp_fw_dist_server_get_node_status_by_address.retrieved_phase;
    }
    if (update_server_status) {
        *update_server_status = rsp->data.rsp_fw_dist_server_get_node_status_by_address.update_server_status;
    }
    if (mbt_server_status) {
        *mbt_server_status = rsp->data.rsp_fw_dist_server_get_node_status_by_address.mbt_server_status;
    }
    if (transfer_progress) {
        *transfer_progress = rsp->data.rsp_fw_dist_server_get_node_status_by_address.transfer_progress;
    }
    if (fw_index) {
        *fw_index = rsp->data.rsp_fw_dist_server_get_node_status_by_address.fw_index;
    }
    return rsp->data.rsp_fw_dist_server_get_node_status_by_address.result;

}

sl_status_t sl_btmesh_fw_dist_server_delete_rsp(uint16_t elem_index,
                                                uint16_t status,
                                                size_t fwid_len,
                                                const uint8_t* fwid) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_server_delete_rsp.elem_index=elem_index;
    cmd->data.cmd_fw_dist_server_delete_rsp.status=status;
    if ((5+fwid_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_fw_dist_server_delete_rsp.fwid.len=fwid_len;
    memcpy(cmd->data.cmd_fw_dist_server_delete_rsp.fwid.data,fwid,fwid_len);

    cmd->header=sl_btmesh_cmd_fw_dist_server_delete_rsp_id+(((5+fwid_len)&0xff)<<8)+(((5+fwid_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_server_delete_rsp.result;

}

sl_status_t sl_btmesh_fw_dist_server_dist_start_rsp(uint16_t elem_index,
                                                    uint16_t status) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_server_dist_start_rsp.elem_index=elem_index;
    cmd->data.cmd_fw_dist_server_dist_start_rsp.status=status;

    cmd->header=sl_btmesh_cmd_fw_dist_server_dist_start_rsp_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_server_dist_start_rsp.result;

}

sl_status_t sl_btmesh_fw_dist_server_set_multicast_threshold(uint16_t elem_index,
                                                             uint16_t multicast_threshold) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_server_set_multicast_threshold.elem_index=elem_index;
    cmd->data.cmd_fw_dist_server_set_multicast_threshold.multicast_threshold=multicast_threshold;

    cmd->header=sl_btmesh_cmd_fw_dist_server_set_multicast_threshold_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_server_set_multicast_threshold.result;

}

sl_status_t sl_btmesh_fw_dist_server_delete_all_rsp(uint16_t elem_index,
                                                    uint16_t status) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_server_delete_all_rsp.elem_index=elem_index;
    cmd->data.cmd_fw_dist_server_delete_all_rsp.status=status;

    cmd->header=sl_btmesh_cmd_fw_dist_server_delete_all_rsp_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_server_delete_all_rsp.result;

}

sl_status_t sl_btmesh_fw_dist_server_resume_rsp(uint16_t elem_index,
                                                uint16_t status) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_server_resume_rsp.elem_index=elem_index;
    cmd->data.cmd_fw_dist_server_resume_rsp.status=status;

    cmd->header=sl_btmesh_cmd_fw_dist_server_resume_rsp_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_server_resume_rsp.result;

}

sl_status_t sl_btmesh_fw_dist_client_init(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_client_init.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_fw_dist_client_init_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_client_init.result;

}

sl_status_t sl_btmesh_fw_dist_client_deinit(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_client_deinit.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_fw_dist_client_deinit_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_client_deinit.result;

}

sl_status_t sl_btmesh_fw_dist_client_setup(uint16_t elem_index,
                                           uint16_t appkey_index,
                                           uint8_t ttl) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_client_setup.elem_index=elem_index;
    cmd->data.cmd_fw_dist_client_setup.appkey_index=appkey_index;
    cmd->data.cmd_fw_dist_client_setup.ttl=ttl;

    cmd->header=sl_btmesh_cmd_fw_dist_client_setup_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_client_setup.result;

}

sl_status_t sl_btmesh_fw_dist_client_setup_upload(uint16_t elem_index,
                                                  uint16_t server_address,
                                                  uint8_t ttl,
                                                  uint16_t timeout_base,
                                                  sl_bt_uuid_64_t blob_id,
                                                  uint32_t size,
                                                  size_t fwid_len,
                                                  const uint8_t* fwid) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_client_setup_upload.elem_index=elem_index;
    cmd->data.cmd_fw_dist_client_setup_upload.server_address=server_address;
    cmd->data.cmd_fw_dist_client_setup_upload.ttl=ttl;
    cmd->data.cmd_fw_dist_client_setup_upload.timeout_base=timeout_base;
    cmd->data.cmd_fw_dist_client_setup_upload.blob_id=blob_id;
    cmd->data.cmd_fw_dist_client_setup_upload.size=size;
    if ((20+fwid_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_fw_dist_client_setup_upload.fwid.len=fwid_len;
    memcpy(cmd->data.cmd_fw_dist_client_setup_upload.fwid.data,fwid,fwid_len);

    cmd->header=sl_btmesh_cmd_fw_dist_client_setup_upload_id+(((20+fwid_len)&0xff)<<8)+(((20+fwid_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_client_setup_upload.result;

}

sl_status_t sl_btmesh_fw_dist_client_set_upload_metadata(uint16_t elem_index,
                                                         size_t metadata_len,
                                                         const uint8_t* metadata) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_client_set_upload_metadata.elem_index=elem_index;
    if ((3+metadata_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_fw_dist_client_set_upload_metadata.metadata.len=metadata_len;
    memcpy(cmd->data.cmd_fw_dist_client_set_upload_metadata.metadata.data,metadata,metadata_len);

    cmd->header=sl_btmesh_cmd_fw_dist_client_set_upload_metadata_id+(((3+metadata_len)&0xff)<<8)+(((3+metadata_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_client_set_upload_metadata.result;

}

sl_status_t sl_btmesh_fw_dist_client_get_receivers(uint16_t elem_index,
                                                   uint16_t dst,
                                                   uint16_t start_index,
                                                   uint16_t max_entries) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_client_get_receivers.elem_index=elem_index;
    cmd->data.cmd_fw_dist_client_get_receivers.dst=dst;
    cmd->data.cmd_fw_dist_client_get_receivers.start_index=start_index;
    cmd->data.cmd_fw_dist_client_get_receivers.max_entries=max_entries;

    cmd->header=sl_btmesh_cmd_fw_dist_client_get_receivers_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_client_get_receivers.result;

}

sl_status_t sl_btmesh_fw_dist_client_get(uint16_t elem_index, uint16_t dst) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_client_get.elem_index=elem_index;
    cmd->data.cmd_fw_dist_client_get.dst=dst;

    cmd->header=sl_btmesh_cmd_fw_dist_client_get_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_client_get.result;

}

sl_status_t sl_btmesh_fw_dist_client_start_distribution(uint16_t elem_index,
                                                        uint16_t dst,
                                                        uint8_t dist_appkey_index,
                                                        uint8_t dist_ttl,
                                                        uint16_t dist_timeout_base,
                                                        uint8_t transfer_mode,
                                                        uint8_t update_policy,
                                                        uint16_t fw_list_index,
                                                        uint16_t group_address,
                                                        uuid_128 virtual_address) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_client_start_distribution.elem_index=elem_index;
    cmd->data.cmd_fw_dist_client_start_distribution.dst=dst;
    cmd->data.cmd_fw_dist_client_start_distribution.dist_appkey_index=dist_appkey_index;
    cmd->data.cmd_fw_dist_client_start_distribution.dist_ttl=dist_ttl;
    cmd->data.cmd_fw_dist_client_start_distribution.dist_timeout_base=dist_timeout_base;
    cmd->data.cmd_fw_dist_client_start_distribution.transfer_mode=transfer_mode;
    cmd->data.cmd_fw_dist_client_start_distribution.update_policy=update_policy;
    cmd->data.cmd_fw_dist_client_start_distribution.fw_list_index=fw_list_index;
    cmd->data.cmd_fw_dist_client_start_distribution.group_address=group_address;
    cmd->data.cmd_fw_dist_client_start_distribution.virtual_address=virtual_address;

    cmd->header=sl_btmesh_cmd_fw_dist_client_start_distribution_id+(((30)&0xff)<<8)+(((30)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_client_start_distribution.result;

}

sl_status_t sl_btmesh_fw_dist_client_cancel_distribution(uint16_t elem_index,
                                                         uint16_t dst) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_client_cancel_distribution.elem_index=elem_index;
    cmd->data.cmd_fw_dist_client_cancel_distribution.dst=dst;

    cmd->header=sl_btmesh_cmd_fw_dist_client_cancel_distribution_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_client_cancel_distribution.result;

}

sl_status_t sl_btmesh_fw_dist_client_apply_distribution(uint16_t elem_index,
                                                        uint16_t dst) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_client_apply_distribution.elem_index=elem_index;
    cmd->data.cmd_fw_dist_client_apply_distribution.dst=dst;

    cmd->header=sl_btmesh_cmd_fw_dist_client_apply_distribution_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_client_apply_distribution.result;

}

sl_status_t sl_btmesh_fw_dist_client_suspend_distribution(uint16_t elem_index,
                                                          uint16_t dst) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_client_suspend_distribution.elem_index=elem_index;
    cmd->data.cmd_fw_dist_client_suspend_distribution.dst=dst;

    cmd->header=sl_btmesh_cmd_fw_dist_client_suspend_distribution_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_client_suspend_distribution.result;

}

sl_status_t sl_btmesh_fw_dist_client_add_receivers(uint16_t elem_index,
                                                   uint16_t dst,
                                                   size_t nodes_len,
                                                   const uint8_t* nodes) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_client_add_receivers.elem_index=elem_index;
    cmd->data.cmd_fw_dist_client_add_receivers.dst=dst;
    if ((5+nodes_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_fw_dist_client_add_receivers.nodes.len=nodes_len;
    memcpy(cmd->data.cmd_fw_dist_client_add_receivers.nodes.data,nodes,nodes_len);

    cmd->header=sl_btmesh_cmd_fw_dist_client_add_receivers_id+(((5+nodes_len)&0xff)<<8)+(((5+nodes_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_client_add_receivers.result;

}

sl_status_t sl_btmesh_fw_dist_client_delete_all_receivers(uint16_t elem_index,
                                                          uint16_t dst) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_client_delete_all_receivers.elem_index=elem_index;
    cmd->data.cmd_fw_dist_client_delete_all_receivers.dst=dst;

    cmd->header=sl_btmesh_cmd_fw_dist_client_delete_all_receivers_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_client_delete_all_receivers.result;

}

sl_status_t sl_btmesh_fw_dist_client_get_capabilities(uint16_t elem_index,
                                                      uint16_t dst) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_client_get_capabilities.elem_index=elem_index;
    cmd->data.cmd_fw_dist_client_get_capabilities.dst=dst;

    cmd->header=sl_btmesh_cmd_fw_dist_client_get_capabilities_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_client_get_capabilities.result;

}

sl_status_t sl_btmesh_fw_dist_client_get_upload(uint16_t elem_index,
                                                uint16_t dst) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_client_get_upload.elem_index=elem_index;
    cmd->data.cmd_fw_dist_client_get_upload.dst=dst;

    cmd->header=sl_btmesh_cmd_fw_dist_client_get_upload_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_client_get_upload.result;

}

sl_status_t sl_btmesh_fw_dist_client_start_upload(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_client_start_upload.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_fw_dist_client_start_upload_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_client_start_upload.result;

}

sl_status_t sl_btmesh_fw_dist_client_cancel_upload(uint16_t elem_index,
                                                   uint16_t dst) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_client_cancel_upload.elem_index=elem_index;
    cmd->data.cmd_fw_dist_client_cancel_upload.dst=dst;

    cmd->header=sl_btmesh_cmd_fw_dist_client_cancel_upload_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_client_cancel_upload.result;

}

sl_status_t sl_btmesh_fw_dist_client_get_fw(uint16_t elem_index,
                                            uint16_t dst,
                                            size_t fwid_len,
                                            const uint8_t* fwid) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_client_get_fw.elem_index=elem_index;
    cmd->data.cmd_fw_dist_client_get_fw.dst=dst;
    if ((5+fwid_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_fw_dist_client_get_fw.fwid.len=fwid_len;
    memcpy(cmd->data.cmd_fw_dist_client_get_fw.fwid.data,fwid,fwid_len);

    cmd->header=sl_btmesh_cmd_fw_dist_client_get_fw_id+(((5+fwid_len)&0xff)<<8)+(((5+fwid_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_client_get_fw.result;

}

sl_status_t sl_btmesh_fw_dist_client_get_fw_by_index(uint16_t elem_index,
                                                     uint16_t dst,
                                                     uint16_t index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_client_get_fw_by_index.elem_index=elem_index;
    cmd->data.cmd_fw_dist_client_get_fw_by_index.dst=dst;
    cmd->data.cmd_fw_dist_client_get_fw_by_index.index=index;

    cmd->header=sl_btmesh_cmd_fw_dist_client_get_fw_by_index_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_client_get_fw_by_index.result;

}

sl_status_t sl_btmesh_fw_dist_client_delete_fw(uint16_t elem_index,
                                               uint16_t dst,
                                               size_t fwid_len,
                                               const uint8_t* fwid) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_client_delete_fw.elem_index=elem_index;
    cmd->data.cmd_fw_dist_client_delete_fw.dst=dst;
    if ((5+fwid_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_fw_dist_client_delete_fw.fwid.len=fwid_len;
    memcpy(cmd->data.cmd_fw_dist_client_delete_fw.fwid.data,fwid,fwid_len);

    cmd->header=sl_btmesh_cmd_fw_dist_client_delete_fw_id+(((5+fwid_len)&0xff)<<8)+(((5+fwid_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_client_delete_fw.result;

}

sl_status_t sl_btmesh_fw_dist_client_delete_all_fw(uint16_t elem_index,
                                                   uint16_t dst) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_client_delete_all_fw.elem_index=elem_index;
    cmd->data.cmd_fw_dist_client_delete_all_fw.dst=dst;

    cmd->header=sl_btmesh_cmd_fw_dist_client_delete_all_fw_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_client_delete_all_fw.result;

}

sl_status_t sl_btmesh_fw_dist_client_prepare_oob_upload(uint16_t elem_index,
                                                        size_t fwid_len,
                                                        const uint8_t* fwid) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_client_prepare_oob_upload.elem_index=elem_index;
    if ((3+fwid_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_fw_dist_client_prepare_oob_upload.fwid.len=fwid_len;
    memcpy(cmd->data.cmd_fw_dist_client_prepare_oob_upload.fwid.data,fwid,fwid_len);

    cmd->header=sl_btmesh_cmd_fw_dist_client_prepare_oob_upload_id+(((3+fwid_len)&0xff)<<8)+(((3+fwid_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_client_prepare_oob_upload.result;

}

sl_status_t sl_btmesh_fw_dist_client_start_oob_upload(uint16_t elem_index,
                                                      uint16_t dst,
                                                      uint16_t appkey_index,
                                                      uint8_t ttl,
                                                      size_t uri_len,
                                                      const uint8_t* uri) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_client_start_oob_upload.elem_index=elem_index;
    cmd->data.cmd_fw_dist_client_start_oob_upload.dst=dst;
    cmd->data.cmd_fw_dist_client_start_oob_upload.appkey_index=appkey_index;
    cmd->data.cmd_fw_dist_client_start_oob_upload.ttl=ttl;
    if ((8+uri_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_fw_dist_client_start_oob_upload.uri.len=uri_len;
    memcpy(cmd->data.cmd_fw_dist_client_start_oob_upload.uri.data,uri,uri_len);

    cmd->header=sl_btmesh_cmd_fw_dist_client_start_oob_upload_id+(((8+uri_len)&0xff)<<8)+(((8+uri_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_client_start_oob_upload.result;

}

sl_status_t sl_btmesh_fw_dist_client_suspend_upload(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_client_suspend_upload.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_fw_dist_client_suspend_upload_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_client_suspend_upload.result;

}

sl_status_t sl_btmesh_fw_dist_client_resume_upload(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_dist_client_resume_upload.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_fw_dist_client_resume_upload_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_dist_client_resume_upload.result;

}

sl_status_t sl_btmesh_remote_provisioning_client_init() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_remote_provisioning_client_init_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_remote_provisioning_client_init.result;

}

sl_status_t sl_btmesh_remote_provisioning_client_get_scan_capabilities(uint16_t enc_netkey_index,
                                                                       uint16_t server,
                                                                       uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_remote_provisioning_client_get_scan_capabilities.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_remote_provisioning_client_get_scan_capabilities.server=server;
    cmd->data.cmd_remote_provisioning_client_get_scan_capabilities.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_remote_provisioning_client_get_scan_capabilities_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_remote_provisioning_client_get_scan_capabilities.result;

}

sl_status_t sl_btmesh_remote_provisioning_client_start_scan(uint16_t enc_netkey_index,
                                                            uint16_t server,
                                                            uint16_t elem_index,
                                                            uint8_t item_limit,
                                                            uint8_t timeout_sec,
                                                            uint8_t single_scan,
                                                            uuid_128 uuid) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_remote_provisioning_client_start_scan.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_remote_provisioning_client_start_scan.server=server;
    cmd->data.cmd_remote_provisioning_client_start_scan.elem_index=elem_index;
    cmd->data.cmd_remote_provisioning_client_start_scan.item_limit=item_limit;
    cmd->data.cmd_remote_provisioning_client_start_scan.timeout_sec=timeout_sec;
    cmd->data.cmd_remote_provisioning_client_start_scan.single_scan=single_scan;
    cmd->data.cmd_remote_provisioning_client_start_scan.uuid=uuid;

    cmd->header=sl_btmesh_cmd_remote_provisioning_client_start_scan_id+(((25)&0xff)<<8)+(((25)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_remote_provisioning_client_start_scan.result;

}

sl_status_t sl_btmesh_remote_provisioning_client_get_scan_status(uint16_t enc_netkey_index,
                                                                 uint16_t server,
                                                                 uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_remote_provisioning_client_get_scan_status.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_remote_provisioning_client_get_scan_status.server=server;
    cmd->data.cmd_remote_provisioning_client_get_scan_status.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_remote_provisioning_client_get_scan_status_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_remote_provisioning_client_get_scan_status.result;

}

sl_status_t sl_btmesh_remote_provisioning_client_stop_scan(uint16_t enc_netkey_index,
                                                           uint16_t server,
                                                           uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_remote_provisioning_client_stop_scan.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_remote_provisioning_client_stop_scan.server=server;
    cmd->data.cmd_remote_provisioning_client_stop_scan.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_remote_provisioning_client_stop_scan_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_remote_provisioning_client_stop_scan.result;

}

sl_status_t sl_btmesh_remote_provisioning_client_start_extended_scan(uint16_t enc_netkey_index,
                                                                     uint16_t server,
                                                                     uint16_t elem_index,
                                                                     uint8_t timeout_sec,
                                                                     uint8_t mode,
                                                                     uuid_128 uuid,
                                                                     size_t ad_types_len,
                                                                     const uint8_t* ad_types) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_remote_provisioning_client_start_extended_scan.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_remote_provisioning_client_start_extended_scan.server=server;
    cmd->data.cmd_remote_provisioning_client_start_extended_scan.elem_index=elem_index;
    cmd->data.cmd_remote_provisioning_client_start_extended_scan.timeout_sec=timeout_sec;
    cmd->data.cmd_remote_provisioning_client_start_extended_scan.mode=mode;
    cmd->data.cmd_remote_provisioning_client_start_extended_scan.uuid=uuid;
    if ((25+ad_types_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_remote_provisioning_client_start_extended_scan.ad_types.len=ad_types_len;
    memcpy(cmd->data.cmd_remote_provisioning_client_start_extended_scan.ad_types.data,ad_types,ad_types_len);

    cmd->header=sl_btmesh_cmd_remote_provisioning_client_start_extended_scan_id+(((25+ad_types_len)&0xff)<<8)+(((25+ad_types_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_remote_provisioning_client_start_extended_scan.result;

}

sl_status_t sl_btmesh_remote_provisioning_client_open_link(uint16_t enc_netkey_index,
                                                           uint16_t server,
                                                           uint16_t elem_index,
                                                           uint8_t timeout_sec,
                                                           uint8_t dkri,
                                                           uuid_128 uuid) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_remote_provisioning_client_open_link.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_remote_provisioning_client_open_link.server=server;
    cmd->data.cmd_remote_provisioning_client_open_link.elem_index=elem_index;
    cmd->data.cmd_remote_provisioning_client_open_link.timeout_sec=timeout_sec;
    cmd->data.cmd_remote_provisioning_client_open_link.dkri=dkri;
    cmd->data.cmd_remote_provisioning_client_open_link.uuid=uuid;

    cmd->header=sl_btmesh_cmd_remote_provisioning_client_open_link_id+(((24)&0xff)<<8)+(((24)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_remote_provisioning_client_open_link.result;

}

sl_status_t sl_btmesh_remote_provisioning_client_get_link_status(uint16_t enc_netkey_index,
                                                                 uint16_t server,
                                                                 uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_remote_provisioning_client_get_link_status.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_remote_provisioning_client_get_link_status.server=server;
    cmd->data.cmd_remote_provisioning_client_get_link_status.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_remote_provisioning_client_get_link_status_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_remote_provisioning_client_get_link_status.result;

}

sl_status_t sl_btmesh_remote_provisioning_client_close_link(uint16_t enc_netkey_index,
                                                            uint16_t server,
                                                            uint16_t elem_index,
                                                            uint8_t reason) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_remote_provisioning_client_close_link.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_remote_provisioning_client_close_link.server=server;
    cmd->data.cmd_remote_provisioning_client_close_link.elem_index=elem_index;
    cmd->data.cmd_remote_provisioning_client_close_link.reason=reason;

    cmd->header=sl_btmesh_cmd_remote_provisioning_client_close_link_id+(((7)&0xff)<<8)+(((7)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_remote_provisioning_client_close_link.result;

}

sl_status_t sl_btmesh_remote_provisioning_server_init() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_remote_provisioning_server_init_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_remote_provisioning_server_init.result;

}

sl_status_t sl_btmesh_remote_provisioning_server_open_link(uint8_t connection) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_remote_provisioning_server_open_link.connection=connection;

    cmd->header=sl_btmesh_cmd_remote_provisioning_server_open_link_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_remote_provisioning_server_open_link.result;

}

sl_status_t sl_btmesh_remote_provisioning_server_set_default_bearer(uint8_t bearer) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_remote_provisioning_server_set_default_bearer.bearer=bearer;

    cmd->header=sl_btmesh_cmd_remote_provisioning_server_set_default_bearer_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_remote_provisioning_server_set_default_bearer.result;

}

sl_status_t sl_btmesh_fw_standalone_updater_init(uint16_t elem_index,
                                                 uint16_t max_node_list_size) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_standalone_updater_init.elem_index=elem_index;
    cmd->data.cmd_fw_standalone_updater_init.max_node_list_size=max_node_list_size;

    cmd->header=sl_btmesh_cmd_fw_standalone_updater_init_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_standalone_updater_init.result;

}

sl_status_t sl_btmesh_fw_standalone_updater_deinit(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_standalone_updater_deinit.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_fw_standalone_updater_deinit_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_standalone_updater_deinit.result;

}

sl_status_t sl_btmesh_fw_standalone_updater_setup(uint16_t elem_index,
                                                  uint32_t fw_size,
                                                  sl_bt_uuid_64_t blob_id,
                                                  size_t fwid_len,
                                                  const uint8_t* fwid) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_standalone_updater_setup.elem_index=elem_index;
    cmd->data.cmd_fw_standalone_updater_setup.fw_size=fw_size;
    cmd->data.cmd_fw_standalone_updater_setup.blob_id=blob_id;
    if ((15+fwid_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_fw_standalone_updater_setup.fwid.len=fwid_len;
    memcpy(cmd->data.cmd_fw_standalone_updater_setup.fwid.data,fwid,fwid_len);

    cmd->header=sl_btmesh_cmd_fw_standalone_updater_setup_id+(((15+fwid_len)&0xff)<<8)+(((15+fwid_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_standalone_updater_setup.result;

}

sl_status_t sl_btmesh_fw_standalone_updater_set_metadata(uint16_t elem_index,
                                                         size_t metadata_len,
                                                         const uint8_t* metadata) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_standalone_updater_set_metadata.elem_index=elem_index;
    if ((3+metadata_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_fw_standalone_updater_set_metadata.metadata.len=metadata_len;
    memcpy(cmd->data.cmd_fw_standalone_updater_set_metadata.metadata.data,metadata,metadata_len);

    cmd->header=sl_btmesh_cmd_fw_standalone_updater_set_metadata_id+(((3+metadata_len)&0xff)<<8)+(((3+metadata_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_standalone_updater_set_metadata.result;

}

sl_status_t sl_btmesh_fw_standalone_updater_set_multicast_threshold(uint16_t elem_index,
                                                                    uint16_t multicast_threshold) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_standalone_updater_set_multicast_threshold.elem_index=elem_index;
    cmd->data.cmd_fw_standalone_updater_set_multicast_threshold.multicast_threshold=multicast_threshold;

    cmd->header=sl_btmesh_cmd_fw_standalone_updater_set_multicast_threshold_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_standalone_updater_set_multicast_threshold.result;

}

sl_status_t sl_btmesh_fw_standalone_updater_add_receiver(uint16_t elem_index,
                                                         uint16_t address,
                                                         uint8_t fw_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_standalone_updater_add_receiver.elem_index=elem_index;
    cmd->data.cmd_fw_standalone_updater_add_receiver.address=address;
    cmd->data.cmd_fw_standalone_updater_add_receiver.fw_index=fw_index;

    cmd->header=sl_btmesh_cmd_fw_standalone_updater_add_receiver_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_standalone_updater_add_receiver.result;

}

sl_status_t sl_btmesh_fw_standalone_updater_delete_all_receivers(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_standalone_updater_delete_all_receivers.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_fw_standalone_updater_delete_all_receivers_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_standalone_updater_delete_all_receivers.result;

}

sl_status_t sl_btmesh_fw_standalone_updater_start(uint16_t elem_index,
                                                  uint16_t dist_appkey_index,
                                                  uint8_t dist_ttl,
                                                  uint16_t dist_timeout_base,
                                                  uint8_t transfer_mode,
                                                  uint16_t group_address,
                                                  uuid_128 virtual_address) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_standalone_updater_start.elem_index=elem_index;
    cmd->data.cmd_fw_standalone_updater_start.dist_appkey_index=dist_appkey_index;
    cmd->data.cmd_fw_standalone_updater_start.dist_ttl=dist_ttl;
    cmd->data.cmd_fw_standalone_updater_start.dist_timeout_base=dist_timeout_base;
    cmd->data.cmd_fw_standalone_updater_start.transfer_mode=transfer_mode;
    cmd->data.cmd_fw_standalone_updater_start.group_address=group_address;
    cmd->data.cmd_fw_standalone_updater_start.virtual_address=virtual_address;

    cmd->header=sl_btmesh_cmd_fw_standalone_updater_start_id+(((26)&0xff)<<8)+(((26)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_standalone_updater_start.result;

}

sl_status_t sl_btmesh_fw_standalone_updater_execute_distribution_step(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_standalone_updater_execute_distribution_step.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_fw_standalone_updater_execute_distribution_step_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_standalone_updater_execute_distribution_step.result;

}

sl_status_t sl_btmesh_fw_standalone_updater_apply(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_standalone_updater_apply.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_fw_standalone_updater_apply_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_standalone_updater_apply.result;

}

sl_status_t sl_btmesh_fw_standalone_updater_get_state(uint16_t elem_index,
                                                      uint8_t *state,
                                                      uint16_t *total_nodes,
                                                      uint16_t *num_active_nodes) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_standalone_updater_get_state.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_fw_standalone_updater_get_state_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (state) {
        *state = rsp->data.rsp_fw_standalone_updater_get_state.state;
    }
    if (total_nodes) {
        *total_nodes = rsp->data.rsp_fw_standalone_updater_get_state.total_nodes;
    }
    if (num_active_nodes) {
        *num_active_nodes = rsp->data.rsp_fw_standalone_updater_get_state.num_active_nodes;
    }
    return rsp->data.rsp_fw_standalone_updater_get_state.result;

}

sl_status_t sl_btmesh_fw_standalone_updater_get_node_status_by_index(uint16_t elem_index,
                                                                     uint16_t entry_index,
                                                                     uint16_t *address,
                                                                     uint8_t *retrieved_phase,
                                                                     uint8_t *update_server_status,
                                                                     uint8_t *mbt_server_status,
                                                                     uint8_t *transfer_progress,
                                                                     uint8_t *fw_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_standalone_updater_get_node_status_by_index.elem_index=elem_index;
    cmd->data.cmd_fw_standalone_updater_get_node_status_by_index.entry_index=entry_index;

    cmd->header=sl_btmesh_cmd_fw_standalone_updater_get_node_status_by_index_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (address) {
        *address = rsp->data.rsp_fw_standalone_updater_get_node_status_by_index.address;
    }
    if (retrieved_phase) {
        *retrieved_phase = rsp->data.rsp_fw_standalone_updater_get_node_status_by_index.retrieved_phase;
    }
    if (update_server_status) {
        *update_server_status = rsp->data.rsp_fw_standalone_updater_get_node_status_by_index.update_server_status;
    }
    if (mbt_server_status) {
        *mbt_server_status = rsp->data.rsp_fw_standalone_updater_get_node_status_by_index.mbt_server_status;
    }
    if (transfer_progress) {
        *transfer_progress = rsp->data.rsp_fw_standalone_updater_get_node_status_by_index.transfer_progress;
    }
    if (fw_index) {
        *fw_index = rsp->data.rsp_fw_standalone_updater_get_node_status_by_index.fw_index;
    }
    return rsp->data.rsp_fw_standalone_updater_get_node_status_by_index.result;

}

sl_status_t sl_btmesh_fw_standalone_updater_get_node_status_by_address(uint16_t elem_index,
                                                                       uint16_t node_address,
                                                                       uint16_t *address,
                                                                       uint8_t *retrieved_phase,
                                                                       uint8_t *update_server_status,
                                                                       uint8_t *mbt_server_status,
                                                                       uint8_t *transfer_progress,
                                                                       uint8_t *fw_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_standalone_updater_get_node_status_by_address.elem_index=elem_index;
    cmd->data.cmd_fw_standalone_updater_get_node_status_by_address.node_address=node_address;

    cmd->header=sl_btmesh_cmd_fw_standalone_updater_get_node_status_by_address_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (address) {
        *address = rsp->data.rsp_fw_standalone_updater_get_node_status_by_address.address;
    }
    if (retrieved_phase) {
        *retrieved_phase = rsp->data.rsp_fw_standalone_updater_get_node_status_by_address.retrieved_phase;
    }
    if (update_server_status) {
        *update_server_status = rsp->data.rsp_fw_standalone_updater_get_node_status_by_address.update_server_status;
    }
    if (mbt_server_status) {
        *mbt_server_status = rsp->data.rsp_fw_standalone_updater_get_node_status_by_address.mbt_server_status;
    }
    if (transfer_progress) {
        *transfer_progress = rsp->data.rsp_fw_standalone_updater_get_node_status_by_address.transfer_progress;
    }
    if (fw_index) {
        *fw_index = rsp->data.rsp_fw_standalone_updater_get_node_status_by_address.fw_index;
    }
    return rsp->data.rsp_fw_standalone_updater_get_node_status_by_address.result;

}

sl_status_t sl_btmesh_fw_standalone_updater_cancel(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_fw_standalone_updater_cancel.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_fw_standalone_updater_cancel_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_fw_standalone_updater_cancel.result;

}

sl_status_t sl_btmesh_migration_migrate_keys() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_migration_migrate_keys_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_migration_migrate_keys.result;

}

sl_status_t sl_btmesh_migration_migrate_ddb() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_migration_migrate_ddb_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_migration_migrate_ddb.result;

}

sl_status_t sl_btmesh_ncp_fw_list_init(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_ncp_fw_list_init.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_ncp_fw_list_init_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_ncp_fw_list_init.result;

}

sl_status_t sl_btmesh_ncp_fw_list_deinit(uint16_t elem_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_ncp_fw_list_deinit.elem_index=elem_index;

    cmd->header=sl_btmesh_cmd_ncp_fw_list_deinit_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_ncp_fw_list_deinit.result;

}

sl_status_t sl_btmesh_ncp_fw_list_get_fw_info_by_index(uint16_t elem_index,
                                                       uint16_t index,
                                                       uint32_t *size,
                                                       sl_bt_uuid_64_t *blob_id,
                                                       size_t max_fwid_size,
                                                       size_t *fwid_len,
                                                       uint8_t *fwid) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_ncp_fw_list_get_fw_info_by_index.elem_index=elem_index;
    cmd->data.cmd_ncp_fw_list_get_fw_info_by_index.index=index;

    cmd->header=sl_btmesh_cmd_ncp_fw_list_get_fw_info_by_index_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (size) {
        *size = rsp->data.rsp_ncp_fw_list_get_fw_info_by_index.size;
    }
    if (blob_id) {
        *blob_id = rsp->data.rsp_ncp_fw_list_get_fw_info_by_index.blob_id;
    }
    if (fwid_len) {
        *fwid_len = rsp->data.rsp_ncp_fw_list_get_fw_info_by_index.fwid.len;
    }
    if (fwid && (rsp->data.rsp_ncp_fw_list_get_fw_info_by_index.fwid.len <= max_fwid_size)) {
        memcpy(fwid,rsp->data.rsp_ncp_fw_list_get_fw_info_by_index.fwid.data,rsp->data.rsp_ncp_fw_list_get_fw_info_by_index.fwid.len);
    }
    return rsp->data.rsp_ncp_fw_list_get_fw_info_by_index.result;

}

sl_status_t sl_btmesh_ncp_fw_list_get_fw_metadata_by_index(uint16_t elem_index,
                                                           uint16_t index,
                                                           size_t max_metadata_size,
                                                           size_t *metadata_len,
                                                           uint8_t *metadata) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_ncp_fw_list_get_fw_metadata_by_index.elem_index=elem_index;
    cmd->data.cmd_ncp_fw_list_get_fw_metadata_by_index.index=index;

    cmd->header=sl_btmesh_cmd_ncp_fw_list_get_fw_metadata_by_index_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (metadata_len) {
        *metadata_len = rsp->data.rsp_ncp_fw_list_get_fw_metadata_by_index.metadata.len;
    }
    if (metadata && (rsp->data.rsp_ncp_fw_list_get_fw_metadata_by_index.metadata.len <= max_metadata_size)) {
        memcpy(metadata,rsp->data.rsp_ncp_fw_list_get_fw_metadata_by_index.metadata.data,rsp->data.rsp_ncp_fw_list_get_fw_metadata_by_index.metadata.len);
    }
    return rsp->data.rsp_ncp_fw_list_get_fw_metadata_by_index.result;

}

sl_status_t sl_btmesh_ncp_fw_list_add_fw(uint16_t elem_index,
                                         uint32_t size,
                                         sl_bt_uuid_64_t blob_id,
                                         size_t fwid_len,
                                         const uint8_t* fwid,
                                         uint16_t *fw_list_index) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_ncp_fw_list_add_fw.elem_index=elem_index;
    cmd->data.cmd_ncp_fw_list_add_fw.size=size;
    cmd->data.cmd_ncp_fw_list_add_fw.blob_id=blob_id;
    if ((15+fwid_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_ncp_fw_list_add_fw.fwid.len=fwid_len;
    memcpy(cmd->data.cmd_ncp_fw_list_add_fw.fwid.data,fwid,fwid_len);

    cmd->header=sl_btmesh_cmd_ncp_fw_list_add_fw_id+(((15+fwid_len)&0xff)<<8)+(((15+fwid_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (fw_list_index) {
        *fw_list_index = rsp->data.rsp_ncp_fw_list_add_fw.fw_list_index;
    }
    return rsp->data.rsp_ncp_fw_list_add_fw.result;

}

sl_status_t sl_btmesh_ncp_fw_list_set_fw_metadata(uint16_t elem_index,
                                                  uint16_t fw_list_index,
                                                  size_t metadata_len,
                                                  const uint8_t* metadata) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_ncp_fw_list_set_fw_metadata.elem_index=elem_index;
    cmd->data.cmd_ncp_fw_list_set_fw_metadata.fw_list_index=fw_list_index;
    if ((5+metadata_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_ncp_fw_list_set_fw_metadata.metadata.len=metadata_len;
    memcpy(cmd->data.cmd_ncp_fw_list_set_fw_metadata.metadata.data,metadata,metadata_len);

    cmd->header=sl_btmesh_cmd_ncp_fw_list_set_fw_metadata_id+(((5+metadata_len)&0xff)<<8)+(((5+metadata_len)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_ncp_fw_list_set_fw_metadata.result;

}

sl_status_t sl_btmesh_sar_config_client_init() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_sar_config_client_init_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_sar_config_client_init.result;

}

sl_status_t sl_btmesh_sar_config_client_deinit() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_sar_config_client_deinit_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_sar_config_client_deinit.result;

}

sl_status_t sl_btmesh_sar_config_client_get_sar_transmitter(uint16_t enc_netkey_index,
                                                            uint16_t server_address,
                                                            uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_sar_config_client_get_sar_transmitter.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_sar_config_client_get_sar_transmitter.server_address=server_address;

    cmd->header=sl_btmesh_cmd_sar_config_client_get_sar_transmitter_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_sar_config_client_get_sar_transmitter.handle;
    }
    return rsp->data.rsp_sar_config_client_get_sar_transmitter.result;

}

sl_status_t sl_btmesh_sar_config_client_set_sar_transmitter(uint16_t enc_netkey_index,
                                                            uint16_t server_address,
                                                            uint8_t segment_interval_step,
                                                            uint8_t unicast_retrans_count,
                                                            uint8_t unicast_retrans_wo_progress_count,
                                                            uint16_t unicast_retrans_interval_step,
                                                            uint16_t unicast_retrans_interval_increment,
                                                            uint8_t multicast_retrans_count,
                                                            uint16_t multicast_retrans_interval_step,
                                                            uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_sar_config_client_set_sar_transmitter.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_sar_config_client_set_sar_transmitter.server_address=server_address;
    cmd->data.cmd_sar_config_client_set_sar_transmitter.segment_interval_step=segment_interval_step;
    cmd->data.cmd_sar_config_client_set_sar_transmitter.unicast_retrans_count=unicast_retrans_count;
    cmd->data.cmd_sar_config_client_set_sar_transmitter.unicast_retrans_wo_progress_count=unicast_retrans_wo_progress_count;
    cmd->data.cmd_sar_config_client_set_sar_transmitter.unicast_retrans_interval_step=unicast_retrans_interval_step;
    cmd->data.cmd_sar_config_client_set_sar_transmitter.unicast_retrans_interval_increment=unicast_retrans_interval_increment;
    cmd->data.cmd_sar_config_client_set_sar_transmitter.multicast_retrans_count=multicast_retrans_count;
    cmd->data.cmd_sar_config_client_set_sar_transmitter.multicast_retrans_interval_step=multicast_retrans_interval_step;

    cmd->header=sl_btmesh_cmd_sar_config_client_set_sar_transmitter_id+(((14)&0xff)<<8)+(((14)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_sar_config_client_set_sar_transmitter.handle;
    }
    return rsp->data.rsp_sar_config_client_set_sar_transmitter.result;

}

sl_status_t sl_btmesh_sar_config_client_get_sar_receiver(uint16_t enc_netkey_index,
                                                         uint16_t server_address,
                                                         uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_sar_config_client_get_sar_receiver.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_sar_config_client_get_sar_receiver.server_address=server_address;

    cmd->header=sl_btmesh_cmd_sar_config_client_get_sar_receiver_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_sar_config_client_get_sar_receiver.handle;
    }
    return rsp->data.rsp_sar_config_client_get_sar_receiver.result;

}

sl_status_t sl_btmesh_sar_config_client_set_sar_receiver(uint16_t enc_netkey_index,
                                                         uint16_t server_address,
                                                         uint8_t segments_threshold,
                                                         uint8_t ack_delay_increment,
                                                         uint32_t discard_timeout,
                                                         uint8_t segment_interval_step,
                                                         uint8_t ack_retrans_count,
                                                         uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_sar_config_client_set_sar_receiver.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_sar_config_client_set_sar_receiver.server_address=server_address;
    cmd->data.cmd_sar_config_client_set_sar_receiver.segments_threshold=segments_threshold;
    cmd->data.cmd_sar_config_client_set_sar_receiver.ack_delay_increment=ack_delay_increment;
    cmd->data.cmd_sar_config_client_set_sar_receiver.discard_timeout=discard_timeout;
    cmd->data.cmd_sar_config_client_set_sar_receiver.segment_interval_step=segment_interval_step;
    cmd->data.cmd_sar_config_client_set_sar_receiver.ack_retrans_count=ack_retrans_count;

    cmd->header=sl_btmesh_cmd_sar_config_client_set_sar_receiver_id+(((12)&0xff)<<8)+(((12)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_sar_config_client_set_sar_receiver.handle;
    }
    return rsp->data.rsp_sar_config_client_set_sar_receiver.result;

}

sl_status_t sl_btmesh_sar_config_server_init() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_sar_config_server_init_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_sar_config_server_init.result;

}

sl_status_t sl_btmesh_sar_config_server_deinit() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_sar_config_server_deinit_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_sar_config_server_deinit.result;

}

sl_status_t sl_btmesh_sar_config_server_get_sar_transmitter(uint8_t *segment_interval_step,
                                                            uint8_t *unicast_retrans_count,
                                                            uint8_t *unicast_retrans_wo_progress_count,
                                                            uint16_t *unicast_retrans_interval_step,
                                                            uint16_t *unicast_retrans_interval_increment,
                                                            uint8_t *multicast_retrans_count,
                                                            uint16_t *multicast_retrans_interval_step) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_sar_config_server_get_sar_transmitter_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (segment_interval_step) {
        *segment_interval_step = rsp->data.rsp_sar_config_server_get_sar_transmitter.segment_interval_step;
    }
    if (unicast_retrans_count) {
        *unicast_retrans_count = rsp->data.rsp_sar_config_server_get_sar_transmitter.unicast_retrans_count;
    }
    if (unicast_retrans_wo_progress_count) {
        *unicast_retrans_wo_progress_count = rsp->data.rsp_sar_config_server_get_sar_transmitter.unicast_retrans_wo_progress_count;
    }
    if (unicast_retrans_interval_step) {
        *unicast_retrans_interval_step = rsp->data.rsp_sar_config_server_get_sar_transmitter.unicast_retrans_interval_step;
    }
    if (unicast_retrans_interval_increment) {
        *unicast_retrans_interval_increment = rsp->data.rsp_sar_config_server_get_sar_transmitter.unicast_retrans_interval_increment;
    }
    if (multicast_retrans_count) {
        *multicast_retrans_count = rsp->data.rsp_sar_config_server_get_sar_transmitter.multicast_retrans_count;
    }
    if (multicast_retrans_interval_step) {
        *multicast_retrans_interval_step = rsp->data.rsp_sar_config_server_get_sar_transmitter.multicast_retrans_interval_step;
    }
    return rsp->data.rsp_sar_config_server_get_sar_transmitter.result;

}

sl_status_t sl_btmesh_sar_config_server_set_sar_transmitter(uint8_t segment_interval_step,
                                                            uint8_t unicast_retrans_count,
                                                            uint8_t unicast_retrans_wo_progress_count,
                                                            uint16_t unicast_retrans_interval_step,
                                                            uint16_t unicast_retrans_interval_increment,
                                                            uint8_t multicast_retrans_count,
                                                            uint16_t multicast_retrans_interval_step) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_sar_config_server_set_sar_transmitter.segment_interval_step=segment_interval_step;
    cmd->data.cmd_sar_config_server_set_sar_transmitter.unicast_retrans_count=unicast_retrans_count;
    cmd->data.cmd_sar_config_server_set_sar_transmitter.unicast_retrans_wo_progress_count=unicast_retrans_wo_progress_count;
    cmd->data.cmd_sar_config_server_set_sar_transmitter.unicast_retrans_interval_step=unicast_retrans_interval_step;
    cmd->data.cmd_sar_config_server_set_sar_transmitter.unicast_retrans_interval_increment=unicast_retrans_interval_increment;
    cmd->data.cmd_sar_config_server_set_sar_transmitter.multicast_retrans_count=multicast_retrans_count;
    cmd->data.cmd_sar_config_server_set_sar_transmitter.multicast_retrans_interval_step=multicast_retrans_interval_step;

    cmd->header=sl_btmesh_cmd_sar_config_server_set_sar_transmitter_id+(((10)&0xff)<<8)+(((10)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_sar_config_server_set_sar_transmitter.result;

}

sl_status_t sl_btmesh_sar_config_server_get_sar_receiver(uint8_t *segments_threshold,
                                                         uint8_t *ack_delay_increment,
                                                         uint32_t *discard_timeout,
                                                         uint8_t *segment_interval_step,
                                                         uint8_t *ack_retrans_count) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_sar_config_server_get_sar_receiver_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (segments_threshold) {
        *segments_threshold = rsp->data.rsp_sar_config_server_get_sar_receiver.segments_threshold;
    }
    if (ack_delay_increment) {
        *ack_delay_increment = rsp->data.rsp_sar_config_server_get_sar_receiver.ack_delay_increment;
    }
    if (discard_timeout) {
        *discard_timeout = rsp->data.rsp_sar_config_server_get_sar_receiver.discard_timeout;
    }
    if (segment_interval_step) {
        *segment_interval_step = rsp->data.rsp_sar_config_server_get_sar_receiver.segment_interval_step;
    }
    if (ack_retrans_count) {
        *ack_retrans_count = rsp->data.rsp_sar_config_server_get_sar_receiver.ack_retrans_count;
    }
    return rsp->data.rsp_sar_config_server_get_sar_receiver.result;

}

sl_status_t sl_btmesh_sar_config_server_set_sar_receiver(uint8_t segments_threshold,
                                                         uint8_t ack_delay_increment,
                                                         uint32_t discard_timeout,
                                                         uint8_t segment_interval_step,
                                                         uint8_t ack_retrans_count) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_sar_config_server_set_sar_receiver.segments_threshold=segments_threshold;
    cmd->data.cmd_sar_config_server_set_sar_receiver.ack_delay_increment=ack_delay_increment;
    cmd->data.cmd_sar_config_server_set_sar_receiver.discard_timeout=discard_timeout;
    cmd->data.cmd_sar_config_server_set_sar_receiver.segment_interval_step=segment_interval_step;
    cmd->data.cmd_sar_config_server_set_sar_receiver.ack_retrans_count=ack_retrans_count;

    cmd->header=sl_btmesh_cmd_sar_config_server_set_sar_receiver_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_sar_config_server_set_sar_receiver.result;

}

sl_status_t sl_btmesh_private_beacon_client_init() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_private_beacon_client_init_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_private_beacon_client_init.result;

}

sl_status_t sl_btmesh_private_beacon_client_deinit() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_private_beacon_client_deinit_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_private_beacon_client_deinit.result;

}

sl_status_t sl_btmesh_private_beacon_client_get_beacon(uint16_t enc_netkey_index,
                                                       uint16_t server_address,
                                                       uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_private_beacon_client_get_beacon.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_private_beacon_client_get_beacon.server_address=server_address;

    cmd->header=sl_btmesh_cmd_private_beacon_client_get_beacon_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_private_beacon_client_get_beacon.handle;
    }
    return rsp->data.rsp_private_beacon_client_get_beacon.result;

}

sl_status_t sl_btmesh_private_beacon_client_set_beacon(uint16_t enc_netkey_index,
                                                       uint16_t server_address,
                                                       uint8_t state,
                                                       uint16_t random_update_steps,
                                                       uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_private_beacon_client_set_beacon.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_private_beacon_client_set_beacon.server_address=server_address;
    cmd->data.cmd_private_beacon_client_set_beacon.state=state;
    cmd->data.cmd_private_beacon_client_set_beacon.random_update_steps=random_update_steps;

    cmd->header=sl_btmesh_cmd_private_beacon_client_set_beacon_id+(((7)&0xff)<<8)+(((7)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_private_beacon_client_set_beacon.handle;
    }
    return rsp->data.rsp_private_beacon_client_set_beacon.result;

}

sl_status_t sl_btmesh_private_beacon_client_get_gatt_proxy(uint16_t enc_netkey_index,
                                                           uint16_t server_address,
                                                           uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_private_beacon_client_get_gatt_proxy.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_private_beacon_client_get_gatt_proxy.server_address=server_address;

    cmd->header=sl_btmesh_cmd_private_beacon_client_get_gatt_proxy_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_private_beacon_client_get_gatt_proxy.handle;
    }
    return rsp->data.rsp_private_beacon_client_get_gatt_proxy.result;

}

sl_status_t sl_btmesh_private_beacon_client_set_gatt_proxy(uint16_t enc_netkey_index,
                                                           uint16_t server_address,
                                                           uint8_t state,
                                                           uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_private_beacon_client_set_gatt_proxy.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_private_beacon_client_set_gatt_proxy.server_address=server_address;
    cmd->data.cmd_private_beacon_client_set_gatt_proxy.state=state;

    cmd->header=sl_btmesh_cmd_private_beacon_client_set_gatt_proxy_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_private_beacon_client_set_gatt_proxy.handle;
    }
    return rsp->data.rsp_private_beacon_client_set_gatt_proxy.result;

}

sl_status_t sl_btmesh_private_beacon_client_get_identity(uint16_t enc_netkey_index,
                                                         uint16_t server_address,
                                                         uint16_t netkey_index,
                                                         uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_private_beacon_client_get_identity.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_private_beacon_client_get_identity.server_address=server_address;
    cmd->data.cmd_private_beacon_client_get_identity.netkey_index=netkey_index;

    cmd->header=sl_btmesh_cmd_private_beacon_client_get_identity_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_private_beacon_client_get_identity.handle;
    }
    return rsp->data.rsp_private_beacon_client_get_identity.result;

}

sl_status_t sl_btmesh_private_beacon_client_set_identity(uint16_t enc_netkey_index,
                                                         uint16_t server_address,
                                                         uint16_t netkey_index,
                                                         uint8_t state,
                                                         uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_private_beacon_client_set_identity.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_private_beacon_client_set_identity.server_address=server_address;
    cmd->data.cmd_private_beacon_client_set_identity.netkey_index=netkey_index;
    cmd->data.cmd_private_beacon_client_set_identity.state=state;

    cmd->header=sl_btmesh_cmd_private_beacon_client_set_identity_id+(((7)&0xff)<<8)+(((7)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_private_beacon_client_set_identity.handle;
    }
    return rsp->data.rsp_private_beacon_client_set_identity.result;

}

sl_status_t sl_btmesh_private_beacon_server_init() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_private_beacon_server_init_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_private_beacon_server_init.result;

}

sl_status_t sl_btmesh_private_beacon_server_deinit() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_private_beacon_server_deinit_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_private_beacon_server_deinit.result;

}

sl_status_t sl_btmesh_lcd_client_init() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_lcd_client_init_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_lcd_client_init.result;

}

sl_status_t sl_btmesh_lcd_client_deinit() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_lcd_client_deinit_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_lcd_client_deinit.result;

}

sl_status_t sl_btmesh_lcd_client_get_composition_data(uint16_t enc_netkey_index,
                                                      uint16_t server_address,
                                                      uint8_t page_number,
                                                      uint16_t offset,
                                                      uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_lcd_client_get_composition_data.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_lcd_client_get_composition_data.server_address=server_address;
    cmd->data.cmd_lcd_client_get_composition_data.page_number=page_number;
    cmd->data.cmd_lcd_client_get_composition_data.offset=offset;

    cmd->header=sl_btmesh_cmd_lcd_client_get_composition_data_id+(((7)&0xff)<<8)+(((7)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_lcd_client_get_composition_data.handle;
    }
    return rsp->data.rsp_lcd_client_get_composition_data.result;

}

sl_status_t sl_btmesh_lcd_client_get_metadata(uint16_t enc_netkey_index,
                                              uint16_t server_address,
                                              uint8_t page_number,
                                              uint16_t offset,
                                              uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_lcd_client_get_metadata.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_lcd_client_get_metadata.server_address=server_address;
    cmd->data.cmd_lcd_client_get_metadata.page_number=page_number;
    cmd->data.cmd_lcd_client_get_metadata.offset=offset;

    cmd->header=sl_btmesh_cmd_lcd_client_get_metadata_id+(((7)&0xff)<<8)+(((7)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_lcd_client_get_metadata.handle;
    }
    return rsp->data.rsp_lcd_client_get_metadata.result;

}

sl_status_t sl_btmesh_lcd_server_init() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_lcd_server_init_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_lcd_server_init.result;

}

sl_status_t sl_btmesh_lcd_server_deinit() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_lcd_server_deinit_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_lcd_server_deinit.result;

}

sl_status_t sl_btmesh_on_demand_private_proxy_client_init() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_on_demand_private_proxy_client_init_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_on_demand_private_proxy_client_init.result;

}

sl_status_t sl_btmesh_on_demand_private_proxy_client_deinit() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_on_demand_private_proxy_client_deinit_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_on_demand_private_proxy_client_deinit.result;

}

sl_status_t sl_btmesh_on_demand_private_proxy_client_get_on_demand_private_gatt_proxy(uint16_t enc_netkey_index,
                                                                                      uint16_t server_address,
                                                                                      uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_on_demand_private_proxy_client_get_on_demand_private_gatt_proxy.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_on_demand_private_proxy_client_get_on_demand_private_gatt_proxy.server_address=server_address;

    cmd->header=sl_btmesh_cmd_on_demand_private_proxy_client_get_on_demand_private_gatt_proxy_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_on_demand_private_proxy_client_get_on_demand_private_gatt_proxy.handle;
    }
    return rsp->data.rsp_on_demand_private_proxy_client_get_on_demand_private_gatt_proxy.result;

}

sl_status_t sl_btmesh_on_demand_private_proxy_client_set_on_demand_private_gatt_proxy(uint16_t enc_netkey_index,
                                                                                      uint16_t server_address,
                                                                                      uint8_t value,
                                                                                      uint32_t *handle) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_on_demand_private_proxy_client_set_on_demand_private_gatt_proxy.enc_netkey_index=enc_netkey_index;
    cmd->data.cmd_on_demand_private_proxy_client_set_on_demand_private_gatt_proxy.server_address=server_address;
    cmd->data.cmd_on_demand_private_proxy_client_set_on_demand_private_gatt_proxy.value=value;

    cmd->header=sl_btmesh_cmd_on_demand_private_proxy_client_set_on_demand_private_gatt_proxy_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_on_demand_private_proxy_client_set_on_demand_private_gatt_proxy.handle;
    }
    return rsp->data.rsp_on_demand_private_proxy_client_set_on_demand_private_gatt_proxy.result;

}

sl_status_t sl_btmesh_solicitation_config_client_init() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_solicitation_config_client_init_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_solicitation_config_client_init.result;

}

sl_status_t sl_btmesh_solicitation_config_client_deinit() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_solicitation_config_client_deinit_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_solicitation_config_client_deinit.result;

}

sl_status_t sl_btmesh_solicitation_config_client_clear_items(uint16_t dst,
                                                             uint16_t appkey_index,
                                                             uint16_t range_start,
                                                             uint8_t length_present,
                                                             uint8_t range_length,
                                                             uint8_t response_required) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_solicitation_config_client_clear_items.dst=dst;
    cmd->data.cmd_solicitation_config_client_clear_items.appkey_index=appkey_index;
    cmd->data.cmd_solicitation_config_client_clear_items.range_start=range_start;
    cmd->data.cmd_solicitation_config_client_clear_items.length_present=length_present;
    cmd->data.cmd_solicitation_config_client_clear_items.range_length=range_length;
    cmd->data.cmd_solicitation_config_client_clear_items.response_required=response_required;

    cmd->header=sl_btmesh_cmd_solicitation_config_client_clear_items_id+(((9)&0xff)<<8)+(((9)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_solicitation_config_client_clear_items.result;

}

sl_status_t sl_btmesh_on_demand_private_proxy_server_init() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_on_demand_private_proxy_server_init_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_on_demand_private_proxy_server_init.result;

}

sl_status_t sl_btmesh_on_demand_private_proxy_server_deinit() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_on_demand_private_proxy_server_deinit_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_on_demand_private_proxy_server_deinit.result;

}

sl_status_t sl_btmesh_silabs_config_server_init() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_silabs_config_server_init_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_silabs_config_server_init.result;

}

sl_status_t sl_btmesh_silabs_config_server_deinit() {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_silabs_config_server_deinit_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_silabs_config_server_deinit.result;

}

sl_status_t sl_btmesh_silabs_config_server_set_tx(uint8_t phy,
                                                  uint32_t options) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_silabs_config_server_set_tx.phy=phy;
    cmd->data.cmd_silabs_config_server_set_tx.options=options;

    cmd->header=sl_btmesh_cmd_silabs_config_server_set_tx_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_silabs_config_server_set_tx.result;

}

sl_status_t sl_btmesh_silabs_config_server_get_tx(uint8_t *phy,
                                                  uint32_t *options) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_silabs_config_server_get_tx_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (phy) {
        *phy = rsp->data.rsp_silabs_config_server_get_tx.phy;
    }
    if (options) {
        *options = rsp->data.rsp_silabs_config_server_get_tx.options;
    }
    return rsp->data.rsp_silabs_config_server_get_tx.result;

}

sl_status_t sl_btmesh_silabs_config_server_set_model_enable(uint8_t elem_index,
                                                            uint16_t vendor_id,
                                                            uint16_t model_id,
                                                            uint16_t value) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_silabs_config_server_set_model_enable.elem_index=elem_index;
    cmd->data.cmd_silabs_config_server_set_model_enable.vendor_id=vendor_id;
    cmd->data.cmd_silabs_config_server_set_model_enable.model_id=model_id;
    cmd->data.cmd_silabs_config_server_set_model_enable.value=value;

    cmd->header=sl_btmesh_cmd_silabs_config_server_set_model_enable_id+(((7)&0xff)<<8)+(((7)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_silabs_config_server_set_model_enable.result;

}

sl_status_t sl_btmesh_silabs_config_server_get_model_enable(uint8_t elem_index,
                                                            uint16_t vendor_id,
                                                            uint16_t model_id,
                                                            uint16_t *value) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_silabs_config_server_get_model_enable.elem_index=elem_index;
    cmd->data.cmd_silabs_config_server_get_model_enable.vendor_id=vendor_id;
    cmd->data.cmd_silabs_config_server_get_model_enable.model_id=model_id;

    cmd->header=sl_btmesh_cmd_silabs_config_server_get_model_enable_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (value) {
        *value = rsp->data.rsp_silabs_config_server_get_model_enable.value;
    }
    return rsp->data.rsp_silabs_config_server_get_model_enable.result;

}

sl_status_t sl_btmesh_silabs_config_server_set_network_pdu(uint16_t max_size) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;

    cmd->data.cmd_silabs_config_server_set_network_pdu.max_size=max_size;

    cmd->header=sl_btmesh_cmd_silabs_config_server_set_network_pdu_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_btmesh_host_handle_command();
    return rsp->data.rsp_silabs_config_server_set_network_pdu.result;

}

sl_status_t sl_btmesh_silabs_config_server_get_network_pdu(uint16_t *max_size) {
    struct sl_btmesh_packet *cmd = (struct sl_btmesh_packet *)sl_btmesh_cmd_msg;

    struct sl_btmesh_packet *rsp = (struct sl_btmesh_packet *)sl_btmesh_rsp_msg;


    cmd->header=sl_btmesh_cmd_silabs_config_server_get_network_pdu_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_btmesh_host_handle_command();
    if (max_size) {
        *max_size = rsp->data.rsp_silabs_config_server_get_network_pdu.max_size;
    }
    return rsp->data.rsp_silabs_config_server_get_network_pdu.result;

}
