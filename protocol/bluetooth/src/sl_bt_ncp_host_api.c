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

#include "sl_bt_api.h"
#include "sli_bt_api.h"

void sl_bt_host_handle_command();
void sl_bt_host_handle_command_noresponse();
extern sl_bt_msg_t *sl_bt_cmd_msg;
extern sl_bt_msg_t *sl_bt_rsp_msg;

sl_status_t sl_bt_dfu_flash_set_address(uint32_t address) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_dfu_flash_set_address.address=address;

    cmd->header=sl_bt_cmd_dfu_flash_set_address_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_dfu_flash_set_address.result;

}

sl_status_t sl_bt_dfu_flash_upload(size_t data_len, const uint8_t* data) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    if ((1+data_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_dfu_flash_upload.data.len=data_len;
    memcpy(cmd->data.cmd_dfu_flash_upload.data.data,data,data_len);

    cmd->header=sl_bt_cmd_dfu_flash_upload_id+(((1+data_len)&0xff)<<8)+(((1+data_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_dfu_flash_upload.result;

}

sl_status_t sl_bt_dfu_flash_upload_finish() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_dfu_flash_upload_finish_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_dfu_flash_upload_finish.result;

}

sl_status_t sl_bt_system_hello() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_system_hello_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_system_hello.result;

}

sl_status_t sl_bt_system_start_bluetooth() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_system_start_bluetooth_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_system_start_bluetooth.result;

}

sl_status_t sl_bt_system_stop_bluetooth() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_system_stop_bluetooth_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_system_stop_bluetooth.result;

}

sl_status_t sl_bt_system_forcefully_stop_bluetooth() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_system_forcefully_stop_bluetooth_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_system_forcefully_stop_bluetooth.result;

}

sl_status_t sl_bt_system_get_version(uint16_t *major,
                                     uint16_t *minor,
                                     uint16_t *patch,
                                     uint16_t *build,
                                     uint32_t *bootloader,
                                     uint32_t *hash) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_system_get_version_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    if (major) {
        *major = rsp->data.rsp_system_get_version.major;
    }
    if (minor) {
        *minor = rsp->data.rsp_system_get_version.minor;
    }
    if (patch) {
        *patch = rsp->data.rsp_system_get_version.patch;
    }
    if (build) {
        *build = rsp->data.rsp_system_get_version.build;
    }
    if (bootloader) {
        *bootloader = rsp->data.rsp_system_get_version.bootloader;
    }
    if (hash) {
        *hash = rsp->data.rsp_system_get_version.hash;
    }
    return rsp->data.rsp_system_get_version.result;

}

void sl_bt_system_reset(uint8_t dfu) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    cmd->data.cmd_system_reset.dfu=dfu;

    cmd->header=sl_bt_cmd_system_reset_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command_noresponse();
}

sl_status_t sl_bt_system_halt(uint8_t halt) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_system_halt.halt=halt;

    cmd->header=sl_bt_cmd_system_halt_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_system_halt.result;

}

sl_status_t sl_bt_system_linklayer_configure(uint8_t key,
                                             size_t data_len,
                                             const uint8_t* data) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_system_linklayer_configure.key=key;
    if ((2+data_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_system_linklayer_configure.data.len=data_len;
    memcpy(cmd->data.cmd_system_linklayer_configure.data.data,data,data_len);

    cmd->header=sl_bt_cmd_system_linklayer_configure_id+(((2+data_len)&0xff)<<8)+(((2+data_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_system_linklayer_configure.result;

}

sl_status_t sl_bt_system_set_tx_power(int16_t min_power,
                                      int16_t max_power,
                                      int16_t *set_min,
                                      int16_t *set_max) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_system_set_tx_power.min_power=min_power;
    cmd->data.cmd_system_set_tx_power.max_power=max_power;

    cmd->header=sl_bt_cmd_system_set_tx_power_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    if (set_min) {
        *set_min = rsp->data.rsp_system_set_tx_power.set_min;
    }
    if (set_max) {
        *set_max = rsp->data.rsp_system_set_tx_power.set_max;
    }
    return rsp->data.rsp_system_set_tx_power.result;

}

sl_status_t sl_bt_system_get_tx_power_setting(int16_t *support_min,
                                              int16_t *support_max,
                                              int16_t *set_min,
                                              int16_t *set_max,
                                              int16_t *rf_path_gain) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_system_get_tx_power_setting_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    if (support_min) {
        *support_min = rsp->data.rsp_system_get_tx_power_setting.support_min;
    }
    if (support_max) {
        *support_max = rsp->data.rsp_system_get_tx_power_setting.support_max;
    }
    if (set_min) {
        *set_min = rsp->data.rsp_system_get_tx_power_setting.set_min;
    }
    if (set_max) {
        *set_max = rsp->data.rsp_system_get_tx_power_setting.set_max;
    }
    if (rf_path_gain) {
        *rf_path_gain = rsp->data.rsp_system_get_tx_power_setting.rf_path_gain;
    }
    return rsp->data.rsp_system_get_tx_power_setting.result;

}

sl_status_t sl_bt_system_set_identity_address(bd_addr address, uint8_t type) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    memcpy(&cmd->data.cmd_system_set_identity_address.address,&address,sizeof(bd_addr));
    cmd->data.cmd_system_set_identity_address.type=type;

    cmd->header=sl_bt_cmd_system_set_identity_address_id+(((7)&0xff)<<8)+(((7)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_system_set_identity_address.result;

}

sl_status_t sl_bt_system_get_identity_address(bd_addr *address, uint8_t *type) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_system_get_identity_address_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    if (address) {
        memcpy(address,&rsp->data.rsp_system_get_identity_address.address,sizeof(bd_addr));
    }
    if (type) {
        *type = rsp->data.rsp_system_get_identity_address.type;
    }
    return rsp->data.rsp_system_get_identity_address.result;

}

sl_status_t sl_bt_system_get_random_data(uint8_t length,
                                         size_t max_data_size,
                                         size_t *data_len,
                                         uint8_t *data) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_system_get_random_data.length=length;

    cmd->header=sl_bt_cmd_system_get_random_data_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    if (data_len) {
        *data_len = rsp->data.rsp_system_get_random_data.data.len;
    }
    if (data && (rsp->data.rsp_system_get_random_data.data.len <= max_data_size)) {
        memcpy(data,rsp->data.rsp_system_get_random_data.data.data,rsp->data.rsp_system_get_random_data.data.len);
    }
    return rsp->data.rsp_system_get_random_data.result;

}

sl_status_t sl_bt_system_data_buffer_write(size_t data_len,
                                           const uint8_t* data) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    if ((1+data_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_system_data_buffer_write.data.len=data_len;
    memcpy(cmd->data.cmd_system_data_buffer_write.data.data,data,data_len);

    cmd->header=sl_bt_cmd_system_data_buffer_write_id+(((1+data_len)&0xff)<<8)+(((1+data_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_system_data_buffer_write.result;

}

sl_status_t sl_bt_system_data_buffer_clear() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_system_data_buffer_clear_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_system_data_buffer_clear.result;

}

sl_status_t sl_bt_system_get_counters(uint8_t reset,
                                      uint16_t *tx_packets,
                                      uint16_t *rx_packets,
                                      uint16_t *crc_errors,
                                      uint16_t *failures) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_system_get_counters.reset=reset;

    cmd->header=sl_bt_cmd_system_get_counters_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    if (tx_packets) {
        *tx_packets = rsp->data.rsp_system_get_counters.tx_packets;
    }
    if (rx_packets) {
        *rx_packets = rsp->data.rsp_system_get_counters.rx_packets;
    }
    if (crc_errors) {
        *crc_errors = rsp->data.rsp_system_get_counters.crc_errors;
    }
    if (failures) {
        *failures = rsp->data.rsp_system_get_counters.failures;
    }
    return rsp->data.rsp_system_get_counters.result;

}

sl_status_t sl_bt_system_set_lazy_soft_timer(uint32_t time,
                                             uint32_t slack,
                                             uint8_t handle,
                                             uint8_t single_shot) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_system_set_lazy_soft_timer.time=time;
    cmd->data.cmd_system_set_lazy_soft_timer.slack=slack;
    cmd->data.cmd_system_set_lazy_soft_timer.handle=handle;
    cmd->data.cmd_system_set_lazy_soft_timer.single_shot=single_shot;

    cmd->header=sl_bt_cmd_system_set_lazy_soft_timer_id+(((10)&0xff)<<8)+(((10)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_system_set_lazy_soft_timer.result;

}

sl_status_t sl_bt_resource_get_status(uint32_t *total_bytes,
                                      uint32_t *free_bytes) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_resource_get_status_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    if (total_bytes) {
        *total_bytes = rsp->data.rsp_resource_get_status.total_bytes;
    }
    if (free_bytes) {
        *free_bytes = rsp->data.rsp_resource_get_status.free_bytes;
    }
    return rsp->data.rsp_resource_get_status.result;

}

sl_status_t sl_bt_resource_set_report_threshold(uint32_t low, uint32_t high) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_resource_set_report_threshold.low=low;
    cmd->data.cmd_resource_set_report_threshold.high=high;

    cmd->header=sl_bt_cmd_resource_set_report_threshold_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_resource_set_report_threshold.result;

}

sl_status_t sl_bt_resource_enable_connection_tx_report(uint16_t packet_count) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_resource_enable_connection_tx_report.packet_count=packet_count;

    cmd->header=sl_bt_cmd_resource_enable_connection_tx_report_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_resource_enable_connection_tx_report.result;

}

sl_status_t sl_bt_resource_get_connection_tx_status(uint8_t connection,
                                                    uint16_t *flags,
                                                    uint16_t *packet_count,
                                                    uint32_t *data_len) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_resource_get_connection_tx_status.connection=connection;

    cmd->header=sl_bt_cmd_resource_get_connection_tx_status_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    if (flags) {
        *flags = rsp->data.rsp_resource_get_connection_tx_status.flags;
    }
    if (packet_count) {
        *packet_count = rsp->data.rsp_resource_get_connection_tx_status.packet_count;
    }
    if (data_len) {
        *data_len = rsp->data.rsp_resource_get_connection_tx_status.data_len;
    }
    return rsp->data.rsp_resource_get_connection_tx_status.result;

}

sl_status_t sl_bt_resource_disable_connection_tx_report() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_resource_disable_connection_tx_report_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_resource_disable_connection_tx_report.result;

}

sl_status_t sl_bt_gap_set_privacy_mode(uint8_t privacy, uint8_t interval) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gap_set_privacy_mode.privacy=privacy;
    cmd->data.cmd_gap_set_privacy_mode.interval=interval;

    cmd->header=sl_bt_cmd_gap_set_privacy_mode_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gap_set_privacy_mode.result;

}

sl_status_t sl_bt_gap_set_data_channel_classification(size_t channel_map_len,
                                                      const uint8_t* channel_map) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    if ((1+channel_map_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_gap_set_data_channel_classification.channel_map.len=channel_map_len;
    memcpy(cmd->data.cmd_gap_set_data_channel_classification.channel_map.data,channel_map,channel_map_len);

    cmd->header=sl_bt_cmd_gap_set_data_channel_classification_id+(((1+channel_map_len)&0xff)<<8)+(((1+channel_map_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gap_set_data_channel_classification.result;

}

SL_BGAPI_DEPRECATED sl_status_t sl_bt_gap_enable_whitelisting(uint8_t enable) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gap_enable_whitelisting.enable=enable;

    cmd->header=sl_bt_cmd_gap_enable_whitelisting_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gap_enable_whitelisting.result;

}

sl_status_t sl_bt_gap_set_identity_address(bd_addr address, uint8_t addr_type) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    memcpy(&cmd->data.cmd_gap_set_identity_address.address,&address,sizeof(bd_addr));
    cmd->data.cmd_gap_set_identity_address.addr_type=addr_type;

    cmd->header=sl_bt_cmd_gap_set_identity_address_id+(((7)&0xff)<<8)+(((7)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gap_set_identity_address.result;

}

sl_status_t sl_bt_advertiser_create_set(uint8_t *handle) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_advertiser_create_set_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    if (handle) {
        *handle = rsp->data.rsp_advertiser_create_set.handle;
    }
    return rsp->data.rsp_advertiser_create_set.result;

}

sl_status_t sl_bt_advertiser_configure(uint8_t advertising_set, uint32_t flags) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_configure.advertising_set=advertising_set;
    cmd->data.cmd_advertiser_configure.flags=flags;

    cmd->header=sl_bt_cmd_advertiser_configure_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_advertiser_configure.result;

}

sl_status_t sl_bt_advertiser_set_timing(uint8_t advertising_set,
                                        uint32_t interval_min,
                                        uint32_t interval_max,
                                        uint16_t duration,
                                        uint8_t maxevents) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_set_timing.advertising_set=advertising_set;
    cmd->data.cmd_advertiser_set_timing.interval_min=interval_min;
    cmd->data.cmd_advertiser_set_timing.interval_max=interval_max;
    cmd->data.cmd_advertiser_set_timing.duration=duration;
    cmd->data.cmd_advertiser_set_timing.maxevents=maxevents;

    cmd->header=sl_bt_cmd_advertiser_set_timing_id+(((12)&0xff)<<8)+(((12)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_advertiser_set_timing.result;

}

sl_status_t sl_bt_advertiser_set_channel_map(uint8_t advertising_set,
                                             uint8_t channel_map) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_set_channel_map.advertising_set=advertising_set;
    cmd->data.cmd_advertiser_set_channel_map.channel_map=channel_map;

    cmd->header=sl_bt_cmd_advertiser_set_channel_map_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_advertiser_set_channel_map.result;

}

sl_status_t sl_bt_advertiser_set_tx_power(uint8_t advertising_set,
                                          int16_t power,
                                          int16_t *set_power) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_set_tx_power.advertising_set=advertising_set;
    cmd->data.cmd_advertiser_set_tx_power.power=power;

    cmd->header=sl_bt_cmd_advertiser_set_tx_power_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_bt_host_handle_command();
    if (set_power) {
        *set_power = rsp->data.rsp_advertiser_set_tx_power.set_power;
    }
    return rsp->data.rsp_advertiser_set_tx_power.result;

}

sl_status_t sl_bt_advertiser_set_report_scan_request(uint8_t advertising_set,
                                                     uint8_t report_scan_req) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_set_report_scan_request.advertising_set=advertising_set;
    cmd->data.cmd_advertiser_set_report_scan_request.report_scan_req=report_scan_req;

    cmd->header=sl_bt_cmd_advertiser_set_report_scan_request_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_advertiser_set_report_scan_request.result;

}

sl_status_t sl_bt_advertiser_set_random_address(uint8_t advertising_set,
                                                uint8_t addr_type,
                                                bd_addr address,
                                                bd_addr *address_out) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_set_random_address.advertising_set=advertising_set;
    cmd->data.cmd_advertiser_set_random_address.addr_type=addr_type;
    memcpy(&cmd->data.cmd_advertiser_set_random_address.address,&address,sizeof(bd_addr));

    cmd->header=sl_bt_cmd_advertiser_set_random_address_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_bt_host_handle_command();
    if (address_out) {
        memcpy(address_out,&rsp->data.rsp_advertiser_set_random_address.address_out,sizeof(bd_addr));
    }
    return rsp->data.rsp_advertiser_set_random_address.result;

}

sl_status_t sl_bt_advertiser_clear_random_address(uint8_t advertising_set) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_clear_random_address.advertising_set=advertising_set;

    cmd->header=sl_bt_cmd_advertiser_clear_random_address_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_advertiser_clear_random_address.result;

}

sl_status_t sl_bt_advertiser_stop(uint8_t advertising_set) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_stop.advertising_set=advertising_set;

    cmd->header=sl_bt_cmd_advertiser_stop_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_advertiser_stop.result;

}

sl_status_t sl_bt_advertiser_delete_set(uint8_t advertising_set) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_delete_set.advertising_set=advertising_set;

    cmd->header=sl_bt_cmd_advertiser_delete_set_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_advertiser_delete_set.result;

}

SL_BGAPI_DEPRECATED sl_status_t sl_bt_advertiser_set_phy(uint8_t advertising_set,
                                     uint8_t primary_phy,
                                     uint8_t secondary_phy) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_set_phy.advertising_set=advertising_set;
    cmd->data.cmd_advertiser_set_phy.primary_phy=primary_phy;
    cmd->data.cmd_advertiser_set_phy.secondary_phy=secondary_phy;

    cmd->header=sl_bt_cmd_advertiser_set_phy_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_advertiser_set_phy.result;

}

SL_BGAPI_DEPRECATED sl_status_t sl_bt_advertiser_set_configuration(uint8_t advertising_set,
                                               uint32_t configurations) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_set_configuration.advertising_set=advertising_set;
    cmd->data.cmd_advertiser_set_configuration.configurations=configurations;

    cmd->header=sl_bt_cmd_advertiser_set_configuration_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_advertiser_set_configuration.result;

}

SL_BGAPI_DEPRECATED sl_status_t sl_bt_advertiser_clear_configuration(uint8_t advertising_set,
                                                 uint32_t configurations) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_clear_configuration.advertising_set=advertising_set;
    cmd->data.cmd_advertiser_clear_configuration.configurations=configurations;

    cmd->header=sl_bt_cmd_advertiser_clear_configuration_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_advertiser_clear_configuration.result;

}

SL_BGAPI_DEPRECATED sl_status_t sl_bt_advertiser_set_data(uint8_t advertising_set,
                                      uint8_t packet_type,
                                      size_t adv_data_len,
                                      const uint8_t* adv_data) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_set_data.advertising_set=advertising_set;
    cmd->data.cmd_advertiser_set_data.packet_type=packet_type;
    if ((3+adv_data_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_advertiser_set_data.adv_data.len=adv_data_len;
    memcpy(cmd->data.cmd_advertiser_set_data.adv_data.data,adv_data,adv_data_len);

    cmd->header=sl_bt_cmd_advertiser_set_data_id+(((3+adv_data_len)&0xff)<<8)+(((3+adv_data_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_advertiser_set_data.result;

}

SL_BGAPI_DEPRECATED sl_status_t sl_bt_advertiser_set_long_data(uint8_t advertising_set,
                                           uint8_t packet_type) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_set_long_data.advertising_set=advertising_set;
    cmd->data.cmd_advertiser_set_long_data.packet_type=packet_type;

    cmd->header=sl_bt_cmd_advertiser_set_long_data_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_advertiser_set_long_data.result;

}

SL_BGAPI_DEPRECATED sl_status_t sl_bt_advertiser_start(uint8_t advertising_set,
                                   uint8_t discover,
                                   uint8_t connect) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_start.advertising_set=advertising_set;
    cmd->data.cmd_advertiser_start.discover=discover;
    cmd->data.cmd_advertiser_start.connect=connect;

    cmd->header=sl_bt_cmd_advertiser_start_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_advertiser_start.result;

}

SL_BGAPI_DEPRECATED sl_status_t sl_bt_advertiser_start_periodic_advertising(uint8_t advertising_set,
                                                        uint16_t interval_min,
                                                        uint16_t interval_max,
                                                        uint32_t flags) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_start_periodic_advertising.advertising_set=advertising_set;
    cmd->data.cmd_advertiser_start_periodic_advertising.interval_min=interval_min;
    cmd->data.cmd_advertiser_start_periodic_advertising.interval_max=interval_max;
    cmd->data.cmd_advertiser_start_periodic_advertising.flags=flags;

    cmd->header=sl_bt_cmd_advertiser_start_periodic_advertising_id+(((9)&0xff)<<8)+(((9)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_advertiser_start_periodic_advertising.result;

}

SL_BGAPI_DEPRECATED sl_status_t sl_bt_advertiser_stop_periodic_advertising(uint8_t advertising_set) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_stop_periodic_advertising.advertising_set=advertising_set;

    cmd->header=sl_bt_cmd_advertiser_stop_periodic_advertising_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_advertiser_stop_periodic_advertising.result;

}

sl_status_t sl_bt_legacy_advertiser_set_data(uint8_t advertising_set,
                                             uint8_t type,
                                             size_t data_len,
                                             const uint8_t* data) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_legacy_advertiser_set_data.advertising_set=advertising_set;
    cmd->data.cmd_legacy_advertiser_set_data.type=type;
    if ((3+data_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_legacy_advertiser_set_data.data.len=data_len;
    memcpy(cmd->data.cmd_legacy_advertiser_set_data.data.data,data,data_len);

    cmd->header=sl_bt_cmd_legacy_advertiser_set_data_id+(((3+data_len)&0xff)<<8)+(((3+data_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_legacy_advertiser_set_data.result;

}

sl_status_t sl_bt_legacy_advertiser_generate_data(uint8_t advertising_set,
                                                  uint8_t discover) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_legacy_advertiser_generate_data.advertising_set=advertising_set;
    cmd->data.cmd_legacy_advertiser_generate_data.discover=discover;

    cmd->header=sl_bt_cmd_legacy_advertiser_generate_data_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_legacy_advertiser_generate_data.result;

}

sl_status_t sl_bt_legacy_advertiser_start(uint8_t advertising_set,
                                          uint8_t connect) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_legacy_advertiser_start.advertising_set=advertising_set;
    cmd->data.cmd_legacy_advertiser_start.connect=connect;

    cmd->header=sl_bt_cmd_legacy_advertiser_start_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_legacy_advertiser_start.result;

}

sl_status_t sl_bt_legacy_advertiser_start_directed(uint8_t advertising_set,
                                                   uint8_t connect,
                                                   bd_addr peer_addr,
                                                   uint8_t peer_addr_type) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_legacy_advertiser_start_directed.advertising_set=advertising_set;
    cmd->data.cmd_legacy_advertiser_start_directed.connect=connect;
    memcpy(&cmd->data.cmd_legacy_advertiser_start_directed.peer_addr,&peer_addr,sizeof(bd_addr));
    cmd->data.cmd_legacy_advertiser_start_directed.peer_addr_type=peer_addr_type;

    cmd->header=sl_bt_cmd_legacy_advertiser_start_directed_id+(((9)&0xff)<<8)+(((9)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_legacy_advertiser_start_directed.result;

}

sl_status_t sl_bt_extended_advertiser_set_phy(uint8_t advertising_set,
                                              uint8_t primary_phy,
                                              uint8_t secondary_phy) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_extended_advertiser_set_phy.advertising_set=advertising_set;
    cmd->data.cmd_extended_advertiser_set_phy.primary_phy=primary_phy;
    cmd->data.cmd_extended_advertiser_set_phy.secondary_phy=secondary_phy;

    cmd->header=sl_bt_cmd_extended_advertiser_set_phy_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_extended_advertiser_set_phy.result;

}

sl_status_t sl_bt_extended_advertiser_set_data(uint8_t advertising_set,
                                               size_t data_len,
                                               const uint8_t* data) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_extended_advertiser_set_data.advertising_set=advertising_set;
    if ((2+data_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_extended_advertiser_set_data.data.len=data_len;
    memcpy(cmd->data.cmd_extended_advertiser_set_data.data.data,data,data_len);

    cmd->header=sl_bt_cmd_extended_advertiser_set_data_id+(((2+data_len)&0xff)<<8)+(((2+data_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_extended_advertiser_set_data.result;

}

sl_status_t sl_bt_extended_advertiser_set_long_data(uint8_t advertising_set) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_extended_advertiser_set_long_data.advertising_set=advertising_set;

    cmd->header=sl_bt_cmd_extended_advertiser_set_long_data_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_extended_advertiser_set_long_data.result;

}

sl_status_t sl_bt_extended_advertiser_generate_data(uint8_t advertising_set,
                                                    uint8_t discover) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_extended_advertiser_generate_data.advertising_set=advertising_set;
    cmd->data.cmd_extended_advertiser_generate_data.discover=discover;

    cmd->header=sl_bt_cmd_extended_advertiser_generate_data_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_extended_advertiser_generate_data.result;

}

sl_status_t sl_bt_extended_advertiser_start(uint8_t advertising_set,
                                            uint8_t connect,
                                            uint32_t flags) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_extended_advertiser_start.advertising_set=advertising_set;
    cmd->data.cmd_extended_advertiser_start.connect=connect;
    cmd->data.cmd_extended_advertiser_start.flags=flags;

    cmd->header=sl_bt_cmd_extended_advertiser_start_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_extended_advertiser_start.result;

}

sl_status_t sl_bt_extended_advertiser_start_directed(uint8_t advertising_set,
                                                     uint8_t connect,
                                                     uint32_t flags,
                                                     bd_addr peer_addr,
                                                     uint8_t peer_addr_type) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_extended_advertiser_start_directed.advertising_set=advertising_set;
    cmd->data.cmd_extended_advertiser_start_directed.connect=connect;
    cmd->data.cmd_extended_advertiser_start_directed.flags=flags;
    memcpy(&cmd->data.cmd_extended_advertiser_start_directed.peer_addr,&peer_addr,sizeof(bd_addr));
    cmd->data.cmd_extended_advertiser_start_directed.peer_addr_type=peer_addr_type;

    cmd->header=sl_bt_cmd_extended_advertiser_start_directed_id+(((13)&0xff)<<8)+(((13)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_extended_advertiser_start_directed.result;

}

sl_status_t sl_bt_periodic_advertiser_set_data(uint8_t advertising_set,
                                               size_t data_len,
                                               const uint8_t* data) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_periodic_advertiser_set_data.advertising_set=advertising_set;
    if ((2+data_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_periodic_advertiser_set_data.data.len=data_len;
    memcpy(cmd->data.cmd_periodic_advertiser_set_data.data.data,data,data_len);

    cmd->header=sl_bt_cmd_periodic_advertiser_set_data_id+(((2+data_len)&0xff)<<8)+(((2+data_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_periodic_advertiser_set_data.result;

}

sl_status_t sl_bt_periodic_advertiser_set_long_data(uint8_t advertising_set) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_periodic_advertiser_set_long_data.advertising_set=advertising_set;

    cmd->header=sl_bt_cmd_periodic_advertiser_set_long_data_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_periodic_advertiser_set_long_data.result;

}

sl_status_t sl_bt_periodic_advertiser_start(uint8_t advertising_set,
                                            uint16_t interval_min,
                                            uint16_t interval_max,
                                            uint32_t flags) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_periodic_advertiser_start.advertising_set=advertising_set;
    cmd->data.cmd_periodic_advertiser_start.interval_min=interval_min;
    cmd->data.cmd_periodic_advertiser_start.interval_max=interval_max;
    cmd->data.cmd_periodic_advertiser_start.flags=flags;

    cmd->header=sl_bt_cmd_periodic_advertiser_start_id+(((9)&0xff)<<8)+(((9)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_periodic_advertiser_start.result;

}

sl_status_t sl_bt_periodic_advertiser_stop(uint8_t advertising_set) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_periodic_advertiser_stop.advertising_set=advertising_set;

    cmd->header=sl_bt_cmd_periodic_advertiser_stop_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_periodic_advertiser_stop.result;

}

sl_status_t sl_bt_scanner_set_parameters(uint8_t mode,
                                         uint16_t interval,
                                         uint16_t window) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_scanner_set_parameters.mode=mode;
    cmd->data.cmd_scanner_set_parameters.interval=interval;
    cmd->data.cmd_scanner_set_parameters.window=window;

    cmd->header=sl_bt_cmd_scanner_set_parameters_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_scanner_set_parameters.result;

}

sl_status_t sl_bt_scanner_set_parameters_and_filter(uint8_t mode,
                                                    uint16_t interval,
                                                    uint16_t window,
                                                    uint32_t flags,
                                                    uint8_t filter_policy) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_scanner_set_parameters_and_filter.mode=mode;
    cmd->data.cmd_scanner_set_parameters_and_filter.interval=interval;
    cmd->data.cmd_scanner_set_parameters_and_filter.window=window;
    cmd->data.cmd_scanner_set_parameters_and_filter.flags=flags;
    cmd->data.cmd_scanner_set_parameters_and_filter.filter_policy=filter_policy;

    cmd->header=sl_bt_cmd_scanner_set_parameters_and_filter_id+(((10)&0xff)<<8)+(((10)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_scanner_set_parameters_and_filter.result;

}

sl_status_t sl_bt_scanner_stop() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_scanner_stop_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_scanner_stop.result;

}

SL_BGAPI_DEPRECATED sl_status_t sl_bt_scanner_set_timing(uint8_t phys,
                                     uint16_t scan_interval,
                                     uint16_t scan_window) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_scanner_set_timing.phys=phys;
    cmd->data.cmd_scanner_set_timing.scan_interval=scan_interval;
    cmd->data.cmd_scanner_set_timing.scan_window=scan_window;

    cmd->header=sl_bt_cmd_scanner_set_timing_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_scanner_set_timing.result;

}

SL_BGAPI_DEPRECATED sl_status_t sl_bt_scanner_set_mode(uint8_t phys, uint8_t scan_mode) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_scanner_set_mode.phys=phys;
    cmd->data.cmd_scanner_set_mode.scan_mode=scan_mode;

    cmd->header=sl_bt_cmd_scanner_set_mode_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_scanner_set_mode.result;

}

sl_status_t sl_bt_scanner_start(uint8_t scanning_phy, uint8_t discover_mode) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_scanner_start.scanning_phy=scanning_phy;
    cmd->data.cmd_scanner_start.discover_mode=discover_mode;

    cmd->header=sl_bt_cmd_scanner_start_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_scanner_start.result;

}

SL_BGAPI_DEPRECATED sl_status_t sl_bt_sync_set_parameters(uint16_t skip,
                                      uint16_t timeout,
                                      uint32_t flags) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sync_set_parameters.skip=skip;
    cmd->data.cmd_sync_set_parameters.timeout=timeout;
    cmd->data.cmd_sync_set_parameters.flags=flags;

    cmd->header=sl_bt_cmd_sync_set_parameters_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sync_set_parameters.result;

}

SL_BGAPI_DEPRECATED sl_status_t sl_bt_sync_open(bd_addr address,
                            uint8_t address_type,
                            uint8_t adv_sid,
                            uint16_t *sync) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    memcpy(&cmd->data.cmd_sync_open.address,&address,sizeof(bd_addr));
    cmd->data.cmd_sync_open.address_type=address_type;
    cmd->data.cmd_sync_open.adv_sid=adv_sid;

    cmd->header=sl_bt_cmd_sync_open_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_bt_host_handle_command();
    if (sync) {
        *sync = rsp->data.rsp_sync_open.sync;
    }
    return rsp->data.rsp_sync_open.result;

}

sl_status_t sl_bt_sync_set_reporting_mode(uint16_t sync,
                                          uint8_t reporting_mode) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sync_set_reporting_mode.sync=sync;
    cmd->data.cmd_sync_set_reporting_mode.reporting_mode=reporting_mode;

    cmd->header=sl_bt_cmd_sync_set_reporting_mode_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sync_set_reporting_mode.result;

}

sl_status_t sl_bt_sync_update_sync_parameters(uint16_t sync,
                                              uint16_t skip,
                                              uint16_t timeout) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sync_update_sync_parameters.sync=sync;
    cmd->data.cmd_sync_update_sync_parameters.skip=skip;
    cmd->data.cmd_sync_update_sync_parameters.timeout=timeout;

    cmd->header=sl_bt_cmd_sync_update_sync_parameters_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sync_update_sync_parameters.result;

}

sl_status_t sl_bt_sync_close(uint16_t sync) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sync_close.sync=sync;

    cmd->header=sl_bt_cmd_sync_close_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sync_close.result;

}

sl_status_t sl_bt_sync_scanner_set_sync_parameters(uint16_t skip,
                                                   uint16_t timeout,
                                                   uint8_t reporting_mode) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sync_scanner_set_sync_parameters.skip=skip;
    cmd->data.cmd_sync_scanner_set_sync_parameters.timeout=timeout;
    cmd->data.cmd_sync_scanner_set_sync_parameters.reporting_mode=reporting_mode;

    cmd->header=sl_bt_cmd_sync_scanner_set_sync_parameters_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sync_scanner_set_sync_parameters.result;

}

sl_status_t sl_bt_sync_scanner_open(bd_addr address,
                                    uint8_t address_type,
                                    uint8_t adv_sid,
                                    uint16_t *sync) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    memcpy(&cmd->data.cmd_sync_scanner_open.address,&address,sizeof(bd_addr));
    cmd->data.cmd_sync_scanner_open.address_type=address_type;
    cmd->data.cmd_sync_scanner_open.adv_sid=adv_sid;

    cmd->header=sl_bt_cmd_sync_scanner_open_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_bt_host_handle_command();
    if (sync) {
        *sync = rsp->data.rsp_sync_scanner_open.sync;
    }
    return rsp->data.rsp_sync_scanner_open.result;

}

sl_status_t sl_bt_past_receiver_set_default_sync_receive_parameters(uint8_t mode,
                                                                    uint16_t skip,
                                                                    uint16_t timeout,
                                                                    uint8_t reporting_mode) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_past_receiver_set_default_sync_receive_parameters.mode=mode;
    cmd->data.cmd_past_receiver_set_default_sync_receive_parameters.skip=skip;
    cmd->data.cmd_past_receiver_set_default_sync_receive_parameters.timeout=timeout;
    cmd->data.cmd_past_receiver_set_default_sync_receive_parameters.reporting_mode=reporting_mode;

    cmd->header=sl_bt_cmd_past_receiver_set_default_sync_receive_parameters_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_past_receiver_set_default_sync_receive_parameters.result;

}

sl_status_t sl_bt_past_receiver_set_sync_receive_parameters(uint8_t connection,
                                                            uint8_t mode,
                                                            uint16_t skip,
                                                            uint16_t timeout,
                                                            uint8_t reporting_mode) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_past_receiver_set_sync_receive_parameters.connection=connection;
    cmd->data.cmd_past_receiver_set_sync_receive_parameters.mode=mode;
    cmd->data.cmd_past_receiver_set_sync_receive_parameters.skip=skip;
    cmd->data.cmd_past_receiver_set_sync_receive_parameters.timeout=timeout;
    cmd->data.cmd_past_receiver_set_sync_receive_parameters.reporting_mode=reporting_mode;

    cmd->header=sl_bt_cmd_past_receiver_set_sync_receive_parameters_id+(((7)&0xff)<<8)+(((7)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_past_receiver_set_sync_receive_parameters.result;

}

sl_status_t sl_bt_advertiser_past_transfer(uint8_t connection,
                                           uint16_t service_data,
                                           uint8_t advertising_set) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_past_transfer.connection=connection;
    cmd->data.cmd_advertiser_past_transfer.service_data=service_data;
    cmd->data.cmd_advertiser_past_transfer.advertising_set=advertising_set;

    cmd->header=sl_bt_cmd_advertiser_past_transfer_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_advertiser_past_transfer.result;

}

sl_status_t sl_bt_sync_past_transfer(uint8_t connection,
                                     uint16_t service_data,
                                     uint16_t sync) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sync_past_transfer.connection=connection;
    cmd->data.cmd_sync_past_transfer.service_data=service_data;
    cmd->data.cmd_sync_past_transfer.sync=sync;

    cmd->header=sl_bt_cmd_sync_past_transfer_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sync_past_transfer.result;

}

sl_status_t sl_bt_pawr_sync_set_sync_subevents(uint16_t sync,
                                               size_t subevents_len,
                                               const uint8_t* subevents) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_pawr_sync_set_sync_subevents.sync=sync;
    if ((3+subevents_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_pawr_sync_set_sync_subevents.subevents.len=subevents_len;
    memcpy(cmd->data.cmd_pawr_sync_set_sync_subevents.subevents.data,subevents,subevents_len);

    cmd->header=sl_bt_cmd_pawr_sync_set_sync_subevents_id+(((3+subevents_len)&0xff)<<8)+(((3+subevents_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_pawr_sync_set_sync_subevents.result;

}

sl_status_t sl_bt_pawr_sync_set_response_data(uint16_t sync,
                                              uint16_t request_event,
                                              uint8_t request_subevent,
                                              uint8_t response_subevent,
                                              uint8_t response_slot,
                                              size_t response_data_len,
                                              const uint8_t* response_data) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_pawr_sync_set_response_data.sync=sync;
    cmd->data.cmd_pawr_sync_set_response_data.request_event=request_event;
    cmd->data.cmd_pawr_sync_set_response_data.request_subevent=request_subevent;
    cmd->data.cmd_pawr_sync_set_response_data.response_subevent=response_subevent;
    cmd->data.cmd_pawr_sync_set_response_data.response_slot=response_slot;
    if ((8+response_data_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_pawr_sync_set_response_data.response_data.len=response_data_len;
    memcpy(cmd->data.cmd_pawr_sync_set_response_data.response_data.data,response_data,response_data_len);

    cmd->header=sl_bt_cmd_pawr_sync_set_response_data_id+(((8+response_data_len)&0xff)<<8)+(((8+response_data_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_pawr_sync_set_response_data.result;

}

sl_status_t sl_bt_pawr_advertiser_start(uint8_t advertising_set,
                                        uint16_t interval_min,
                                        uint16_t interval_max,
                                        uint32_t flags,
                                        uint8_t num_subevents,
                                        uint8_t subevent_interval,
                                        uint8_t response_slot_delay,
                                        uint8_t response_slot_spacing,
                                        uint8_t response_slots) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_pawr_advertiser_start.advertising_set=advertising_set;
    cmd->data.cmd_pawr_advertiser_start.interval_min=interval_min;
    cmd->data.cmd_pawr_advertiser_start.interval_max=interval_max;
    cmd->data.cmd_pawr_advertiser_start.flags=flags;
    cmd->data.cmd_pawr_advertiser_start.num_subevents=num_subevents;
    cmd->data.cmd_pawr_advertiser_start.subevent_interval=subevent_interval;
    cmd->data.cmd_pawr_advertiser_start.response_slot_delay=response_slot_delay;
    cmd->data.cmd_pawr_advertiser_start.response_slot_spacing=response_slot_spacing;
    cmd->data.cmd_pawr_advertiser_start.response_slots=response_slots;

    cmd->header=sl_bt_cmd_pawr_advertiser_start_id+(((14)&0xff)<<8)+(((14)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_pawr_advertiser_start.result;

}

sl_status_t sl_bt_pawr_advertiser_set_subevent_data(uint8_t advertising_set,
                                                    uint8_t subevent,
                                                    uint8_t response_slot_start,
                                                    uint8_t response_slot_count,
                                                    size_t adv_data_len,
                                                    const uint8_t* adv_data) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_pawr_advertiser_set_subevent_data.advertising_set=advertising_set;
    cmd->data.cmd_pawr_advertiser_set_subevent_data.subevent=subevent;
    cmd->data.cmd_pawr_advertiser_set_subevent_data.response_slot_start=response_slot_start;
    cmd->data.cmd_pawr_advertiser_set_subevent_data.response_slot_count=response_slot_count;
    if ((5+adv_data_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_pawr_advertiser_set_subevent_data.adv_data.len=adv_data_len;
    memcpy(cmd->data.cmd_pawr_advertiser_set_subevent_data.adv_data.data,adv_data,adv_data_len);

    cmd->header=sl_bt_cmd_pawr_advertiser_set_subevent_data_id+(((5+adv_data_len)&0xff)<<8)+(((5+adv_data_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_pawr_advertiser_set_subevent_data.result;

}

sl_status_t sl_bt_pawr_advertiser_create_connection(uint8_t advertising_set,
                                                    uint8_t subevent,
                                                    bd_addr address,
                                                    uint8_t address_type,
                                                    uint8_t *connection) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_pawr_advertiser_create_connection.advertising_set=advertising_set;
    cmd->data.cmd_pawr_advertiser_create_connection.subevent=subevent;
    memcpy(&cmd->data.cmd_pawr_advertiser_create_connection.address,&address,sizeof(bd_addr));
    cmd->data.cmd_pawr_advertiser_create_connection.address_type=address_type;

    cmd->header=sl_bt_cmd_pawr_advertiser_create_connection_id+(((9)&0xff)<<8)+(((9)&0x700)>>8);


    sl_bt_host_handle_command();
    if (connection) {
        *connection = rsp->data.rsp_pawr_advertiser_create_connection.connection;
    }
    return rsp->data.rsp_pawr_advertiser_create_connection.result;

}

sl_status_t sl_bt_pawr_advertiser_stop(uint8_t advertising_set) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_pawr_advertiser_stop.advertising_set=advertising_set;

    cmd->header=sl_bt_cmd_pawr_advertiser_stop_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_pawr_advertiser_stop.result;

}

sl_status_t sl_bt_connection_set_default_parameters(uint16_t min_interval,
                                                    uint16_t max_interval,
                                                    uint16_t latency,
                                                    uint16_t timeout,
                                                    uint16_t min_ce_length,
                                                    uint16_t max_ce_length) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_set_default_parameters.min_interval=min_interval;
    cmd->data.cmd_connection_set_default_parameters.max_interval=max_interval;
    cmd->data.cmd_connection_set_default_parameters.latency=latency;
    cmd->data.cmd_connection_set_default_parameters.timeout=timeout;
    cmd->data.cmd_connection_set_default_parameters.min_ce_length=min_ce_length;
    cmd->data.cmd_connection_set_default_parameters.max_ce_length=max_ce_length;

    cmd->header=sl_bt_cmd_connection_set_default_parameters_id+(((12)&0xff)<<8)+(((12)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_connection_set_default_parameters.result;

}

sl_status_t sl_bt_connection_set_default_preferred_phy(uint8_t preferred_phy,
                                                       uint8_t accepted_phy) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_set_default_preferred_phy.preferred_phy=preferred_phy;
    cmd->data.cmd_connection_set_default_preferred_phy.accepted_phy=accepted_phy;

    cmd->header=sl_bt_cmd_connection_set_default_preferred_phy_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_connection_set_default_preferred_phy.result;

}

sl_status_t sl_bt_connection_set_default_data_length(uint16_t tx_data_len) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_set_default_data_length.tx_data_len=tx_data_len;

    cmd->header=sl_bt_cmd_connection_set_default_data_length_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_connection_set_default_data_length.result;

}

sl_status_t sl_bt_connection_open(bd_addr address,
                                  uint8_t address_type,
                                  uint8_t initiating_phy,
                                  uint8_t *connection) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    memcpy(&cmd->data.cmd_connection_open.address,&address,sizeof(bd_addr));
    cmd->data.cmd_connection_open.address_type=address_type;
    cmd->data.cmd_connection_open.initiating_phy=initiating_phy;

    cmd->header=sl_bt_cmd_connection_open_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_bt_host_handle_command();
    if (connection) {
        *connection = rsp->data.rsp_connection_open.connection;
    }
    return rsp->data.rsp_connection_open.result;

}

sl_status_t sl_bt_connection_set_parameters(uint8_t connection,
                                            uint16_t min_interval,
                                            uint16_t max_interval,
                                            uint16_t latency,
                                            uint16_t timeout,
                                            uint16_t min_ce_length,
                                            uint16_t max_ce_length) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_set_parameters.connection=connection;
    cmd->data.cmd_connection_set_parameters.min_interval=min_interval;
    cmd->data.cmd_connection_set_parameters.max_interval=max_interval;
    cmd->data.cmd_connection_set_parameters.latency=latency;
    cmd->data.cmd_connection_set_parameters.timeout=timeout;
    cmd->data.cmd_connection_set_parameters.min_ce_length=min_ce_length;
    cmd->data.cmd_connection_set_parameters.max_ce_length=max_ce_length;

    cmd->header=sl_bt_cmd_connection_set_parameters_id+(((13)&0xff)<<8)+(((13)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_connection_set_parameters.result;

}

sl_status_t sl_bt_connection_set_preferred_phy(uint8_t connection,
                                               uint8_t preferred_phy,
                                               uint8_t accepted_phy) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_set_preferred_phy.connection=connection;
    cmd->data.cmd_connection_set_preferred_phy.preferred_phy=preferred_phy;
    cmd->data.cmd_connection_set_preferred_phy.accepted_phy=accepted_phy;

    cmd->header=sl_bt_cmd_connection_set_preferred_phy_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_connection_set_preferred_phy.result;

}

sl_status_t sl_bt_connection_disable_slave_latency(uint8_t connection,
                                                   uint8_t disable) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_disable_slave_latency.connection=connection;
    cmd->data.cmd_connection_disable_slave_latency.disable=disable;

    cmd->header=sl_bt_cmd_connection_disable_slave_latency_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_connection_disable_slave_latency.result;

}

sl_status_t sl_bt_connection_get_median_rssi(uint8_t connection, int8_t *rssi) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_get_median_rssi.connection=connection;

    cmd->header=sl_bt_cmd_connection_get_median_rssi_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    if (rssi) {
        *rssi = rsp->data.rsp_connection_get_median_rssi.rssi;
    }
    return rsp->data.rsp_connection_get_median_rssi.result;

}

sl_status_t sl_bt_connection_read_channel_map(uint8_t connection,
                                              size_t max_channel_map_size,
                                              size_t *channel_map_len,
                                              uint8_t *channel_map) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_read_channel_map.connection=connection;

    cmd->header=sl_bt_cmd_connection_read_channel_map_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    if (channel_map_len) {
        *channel_map_len = rsp->data.rsp_connection_read_channel_map.channel_map.len;
    }
    if (channel_map && (rsp->data.rsp_connection_read_channel_map.channel_map.len <= max_channel_map_size)) {
        memcpy(channel_map,rsp->data.rsp_connection_read_channel_map.channel_map.data,rsp->data.rsp_connection_read_channel_map.channel_map.len);
    }
    return rsp->data.rsp_connection_read_channel_map.result;

}

sl_status_t sl_bt_connection_set_power_reporting(uint8_t connection,
                                                 uint8_t mode) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_set_power_reporting.connection=connection;
    cmd->data.cmd_connection_set_power_reporting.mode=mode;

    cmd->header=sl_bt_cmd_connection_set_power_reporting_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_connection_set_power_reporting.result;

}

sl_status_t sl_bt_connection_set_remote_power_reporting(uint8_t connection,
                                                        uint8_t mode) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_set_remote_power_reporting.connection=connection;
    cmd->data.cmd_connection_set_remote_power_reporting.mode=mode;

    cmd->header=sl_bt_cmd_connection_set_remote_power_reporting_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_connection_set_remote_power_reporting.result;

}

sl_status_t sl_bt_connection_get_tx_power(uint8_t connection,
                                          uint8_t phy,
                                          int8_t *current_level,
                                          int8_t *max_level) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_get_tx_power.connection=connection;
    cmd->data.cmd_connection_get_tx_power.phy=phy;

    cmd->header=sl_bt_cmd_connection_get_tx_power_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    if (current_level) {
        *current_level = rsp->data.rsp_connection_get_tx_power.current_level;
    }
    if (max_level) {
        *max_level = rsp->data.rsp_connection_get_tx_power.max_level;
    }
    return rsp->data.rsp_connection_get_tx_power.result;

}

sl_status_t sl_bt_connection_get_remote_tx_power(uint8_t connection,
                                                 uint8_t phy) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_get_remote_tx_power.connection=connection;
    cmd->data.cmd_connection_get_remote_tx_power.phy=phy;

    cmd->header=sl_bt_cmd_connection_get_remote_tx_power_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_connection_get_remote_tx_power.result;

}

sl_status_t sl_bt_connection_set_tx_power(uint8_t connection,
                                          int16_t tx_power,
                                          int16_t *tx_power_out) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_set_tx_power.connection=connection;
    cmd->data.cmd_connection_set_tx_power.tx_power=tx_power;

    cmd->header=sl_bt_cmd_connection_set_tx_power_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_bt_host_handle_command();
    if (tx_power_out) {
        *tx_power_out = rsp->data.rsp_connection_set_tx_power.tx_power_out;
    }
    return rsp->data.rsp_connection_set_tx_power.result;

}

sl_status_t sl_bt_connection_read_remote_used_features(uint8_t connection) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_read_remote_used_features.connection=connection;

    cmd->header=sl_bt_cmd_connection_read_remote_used_features_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_connection_read_remote_used_features.result;

}

sl_status_t sl_bt_connection_get_security_status(uint8_t connection,
                                                 uint8_t *security_mode,
                                                 uint8_t *key_size,
                                                 uint8_t *bonding_handle) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_get_security_status.connection=connection;

    cmd->header=sl_bt_cmd_connection_get_security_status_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    if (security_mode) {
        *security_mode = rsp->data.rsp_connection_get_security_status.security_mode;
    }
    if (key_size) {
        *key_size = rsp->data.rsp_connection_get_security_status.key_size;
    }
    if (bonding_handle) {
        *bonding_handle = rsp->data.rsp_connection_get_security_status.bonding_handle;
    }
    return rsp->data.rsp_connection_get_security_status.result;

}

sl_status_t sl_bt_connection_set_data_length(uint8_t connection,
                                             uint16_t tx_data_len,
                                             uint16_t tx_time_us) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_set_data_length.connection=connection;
    cmd->data.cmd_connection_set_data_length.tx_data_len=tx_data_len;
    cmd->data.cmd_connection_set_data_length.tx_time_us=tx_time_us;

    cmd->header=sl_bt_cmd_connection_set_data_length_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_connection_set_data_length.result;

}

sl_status_t sl_bt_connection_read_statistics(uint8_t connection, uint8_t reset) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_read_statistics.connection=connection;
    cmd->data.cmd_connection_read_statistics.reset=reset;

    cmd->header=sl_bt_cmd_connection_read_statistics_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_connection_read_statistics.result;

}

sl_status_t sl_bt_connection_get_scheduling_details(uint8_t connection,
                                                    uint32_t *access_address,
                                                    uint8_t *role,
                                                    uint32_t *crc_init,
                                                    uint16_t *interval,
                                                    uint16_t *supervision_timeout,
                                                    uint8_t *central_clock_accuracy,
                                                    uint8_t *central_phy,
                                                    uint8_t *peripheral_phy,
                                                    uint8_t *channel_selection_algorithm,
                                                    uint8_t *hop,
                                                    sl_bt_connection_channel_map_t *channel_map,
                                                    uint8_t *channel,
                                                    uint16_t *event_counter,
                                                    uint32_t *start_time_us) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_get_scheduling_details.connection=connection;

    cmd->header=sl_bt_cmd_connection_get_scheduling_details_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    if (access_address) {
        *access_address = rsp->data.rsp_connection_get_scheduling_details.access_address;
    }
    if (role) {
        *role = rsp->data.rsp_connection_get_scheduling_details.role;
    }
    if (crc_init) {
        *crc_init = rsp->data.rsp_connection_get_scheduling_details.crc_init;
    }
    if (interval) {
        *interval = rsp->data.rsp_connection_get_scheduling_details.interval;
    }
    if (supervision_timeout) {
        *supervision_timeout = rsp->data.rsp_connection_get_scheduling_details.supervision_timeout;
    }
    if (central_clock_accuracy) {
        *central_clock_accuracy = rsp->data.rsp_connection_get_scheduling_details.central_clock_accuracy;
    }
    if (central_phy) {
        *central_phy = rsp->data.rsp_connection_get_scheduling_details.central_phy;
    }
    if (peripheral_phy) {
        *peripheral_phy = rsp->data.rsp_connection_get_scheduling_details.peripheral_phy;
    }
    if (channel_selection_algorithm) {
        *channel_selection_algorithm = rsp->data.rsp_connection_get_scheduling_details.channel_selection_algorithm;
    }
    if (hop) {
        *hop = rsp->data.rsp_connection_get_scheduling_details.hop;
    }
    if (channel_map) {
        memcpy(channel_map,&rsp->data.rsp_connection_get_scheduling_details.channel_map,sizeof(sl_bt_connection_channel_map_t));
    }
    if (channel) {
        *channel = rsp->data.rsp_connection_get_scheduling_details.channel;
    }
    if (event_counter) {
        *event_counter = rsp->data.rsp_connection_get_scheduling_details.event_counter;
    }
    if (start_time_us) {
        *start_time_us = rsp->data.rsp_connection_get_scheduling_details.start_time_us;
    }
    return rsp->data.rsp_connection_get_scheduling_details.result;

}

sl_status_t sl_bt_connection_close(uint8_t connection) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_close.connection=connection;

    cmd->header=sl_bt_cmd_connection_close_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_connection_close.result;

}

sl_status_t sl_bt_connection_forcefully_close(uint8_t connection) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_forcefully_close.connection=connection;

    cmd->header=sl_bt_cmd_connection_forcefully_close_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_connection_forcefully_close.result;

}

SL_BGAPI_DEPRECATED sl_status_t sl_bt_connection_get_rssi(uint8_t connection) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_get_rssi.connection=connection;

    cmd->header=sl_bt_cmd_connection_get_rssi_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_connection_get_rssi.result;

}

sl_status_t sl_bt_gatt_set_max_mtu(uint16_t max_mtu, uint16_t *max_mtu_out) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_set_max_mtu.max_mtu=max_mtu;

    cmd->header=sl_bt_cmd_gatt_set_max_mtu_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    if (max_mtu_out) {
        *max_mtu_out = rsp->data.rsp_gatt_set_max_mtu.max_mtu_out;
    }
    return rsp->data.rsp_gatt_set_max_mtu.result;

}

sl_status_t sl_bt_gatt_discover_primary_services(uint8_t connection) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_discover_primary_services.connection=connection;

    cmd->header=sl_bt_cmd_gatt_discover_primary_services_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_discover_primary_services.result;

}

sl_status_t sl_bt_gatt_discover_primary_services_by_uuid(uint8_t connection,
                                                         size_t uuid_len,
                                                         const uint8_t* uuid) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_discover_primary_services_by_uuid.connection=connection;
    if ((2+uuid_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_gatt_discover_primary_services_by_uuid.uuid.len=uuid_len;
    memcpy(cmd->data.cmd_gatt_discover_primary_services_by_uuid.uuid.data,uuid,uuid_len);

    cmd->header=sl_bt_cmd_gatt_discover_primary_services_by_uuid_id+(((2+uuid_len)&0xff)<<8)+(((2+uuid_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_discover_primary_services_by_uuid.result;

}

sl_status_t sl_bt_gatt_find_included_services(uint8_t connection,
                                              uint32_t service) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_find_included_services.connection=connection;
    cmd->data.cmd_gatt_find_included_services.service=service;

    cmd->header=sl_bt_cmd_gatt_find_included_services_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_find_included_services.result;

}

sl_status_t sl_bt_gatt_discover_characteristics(uint8_t connection,
                                                uint32_t service) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_discover_characteristics.connection=connection;
    cmd->data.cmd_gatt_discover_characteristics.service=service;

    cmd->header=sl_bt_cmd_gatt_discover_characteristics_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_discover_characteristics.result;

}

sl_status_t sl_bt_gatt_discover_characteristics_by_uuid(uint8_t connection,
                                                        uint32_t service,
                                                        size_t uuid_len,
                                                        const uint8_t* uuid) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_discover_characteristics_by_uuid.connection=connection;
    cmd->data.cmd_gatt_discover_characteristics_by_uuid.service=service;
    if ((6+uuid_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_gatt_discover_characteristics_by_uuid.uuid.len=uuid_len;
    memcpy(cmd->data.cmd_gatt_discover_characteristics_by_uuid.uuid.data,uuid,uuid_len);

    cmd->header=sl_bt_cmd_gatt_discover_characteristics_by_uuid_id+(((6+uuid_len)&0xff)<<8)+(((6+uuid_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_discover_characteristics_by_uuid.result;

}

sl_status_t sl_bt_gatt_discover_descriptors(uint8_t connection,
                                            uint16_t characteristic) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_discover_descriptors.connection=connection;
    cmd->data.cmd_gatt_discover_descriptors.characteristic=characteristic;

    cmd->header=sl_bt_cmd_gatt_discover_descriptors_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_discover_descriptors.result;

}

sl_status_t sl_bt_gatt_discover_characteristic_descriptors(uint8_t connection,
                                                           uint16_t start,
                                                           uint16_t end) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_discover_characteristic_descriptors.connection=connection;
    cmd->data.cmd_gatt_discover_characteristic_descriptors.start=start;
    cmd->data.cmd_gatt_discover_characteristic_descriptors.end=end;

    cmd->header=sl_bt_cmd_gatt_discover_characteristic_descriptors_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_discover_characteristic_descriptors.result;

}

sl_status_t sl_bt_gatt_set_characteristic_notification(uint8_t connection,
                                                       uint16_t characteristic,
                                                       uint8_t flags) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_set_characteristic_notification.connection=connection;
    cmd->data.cmd_gatt_set_characteristic_notification.characteristic=characteristic;
    cmd->data.cmd_gatt_set_characteristic_notification.flags=flags;

    cmd->header=sl_bt_cmd_gatt_set_characteristic_notification_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_set_characteristic_notification.result;

}

sl_status_t sl_bt_gatt_send_characteristic_confirmation(uint8_t connection) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_send_characteristic_confirmation.connection=connection;

    cmd->header=sl_bt_cmd_gatt_send_characteristic_confirmation_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_send_characteristic_confirmation.result;

}

sl_status_t sl_bt_gatt_read_characteristic_value(uint8_t connection,
                                                 uint16_t characteristic) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_read_characteristic_value.connection=connection;
    cmd->data.cmd_gatt_read_characteristic_value.characteristic=characteristic;

    cmd->header=sl_bt_cmd_gatt_read_characteristic_value_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_read_characteristic_value.result;

}

sl_status_t sl_bt_gatt_read_characteristic_value_from_offset(uint8_t connection,
                                                             uint16_t characteristic,
                                                             uint16_t offset,
                                                             uint16_t maxlen) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_read_characteristic_value_from_offset.connection=connection;
    cmd->data.cmd_gatt_read_characteristic_value_from_offset.characteristic=characteristic;
    cmd->data.cmd_gatt_read_characteristic_value_from_offset.offset=offset;
    cmd->data.cmd_gatt_read_characteristic_value_from_offset.maxlen=maxlen;

    cmd->header=sl_bt_cmd_gatt_read_characteristic_value_from_offset_id+(((7)&0xff)<<8)+(((7)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_read_characteristic_value_from_offset.result;

}

sl_status_t sl_bt_gatt_read_multiple_characteristic_values(uint8_t connection,
                                                           size_t characteristic_list_len,
                                                           const uint8_t* characteristic_list) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_read_multiple_characteristic_values.connection=connection;
    if ((2+characteristic_list_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_gatt_read_multiple_characteristic_values.characteristic_list.len=characteristic_list_len;
    memcpy(cmd->data.cmd_gatt_read_multiple_characteristic_values.characteristic_list.data,characteristic_list,characteristic_list_len);

    cmd->header=sl_bt_cmd_gatt_read_multiple_characteristic_values_id+(((2+characteristic_list_len)&0xff)<<8)+(((2+characteristic_list_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_read_multiple_characteristic_values.result;

}

sl_status_t sl_bt_gatt_read_characteristic_value_by_uuid(uint8_t connection,
                                                         uint32_t service,
                                                         size_t uuid_len,
                                                         const uint8_t* uuid) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_read_characteristic_value_by_uuid.connection=connection;
    cmd->data.cmd_gatt_read_characteristic_value_by_uuid.service=service;
    if ((6+uuid_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_gatt_read_characteristic_value_by_uuid.uuid.len=uuid_len;
    memcpy(cmd->data.cmd_gatt_read_characteristic_value_by_uuid.uuid.data,uuid,uuid_len);

    cmd->header=sl_bt_cmd_gatt_read_characteristic_value_by_uuid_id+(((6+uuid_len)&0xff)<<8)+(((6+uuid_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_read_characteristic_value_by_uuid.result;

}

sl_status_t sl_bt_gatt_write_characteristic_value(uint8_t connection,
                                                  uint16_t characteristic,
                                                  size_t value_len,
                                                  const uint8_t* value) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_write_characteristic_value.connection=connection;
    cmd->data.cmd_gatt_write_characteristic_value.characteristic=characteristic;
    if ((4+value_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_gatt_write_characteristic_value.value.len=value_len;
    memcpy(cmd->data.cmd_gatt_write_characteristic_value.value.data,value,value_len);

    cmd->header=sl_bt_cmd_gatt_write_characteristic_value_id+(((4+value_len)&0xff)<<8)+(((4+value_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_write_characteristic_value.result;

}

sl_status_t sl_bt_gatt_write_characteristic_value_without_response(uint8_t connection,
                                                                   uint16_t characteristic,
                                                                   size_t value_len,
                                                                   const uint8_t* value,
                                                                   uint16_t *sent_len) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_write_characteristic_value_without_response.connection=connection;
    cmd->data.cmd_gatt_write_characteristic_value_without_response.characteristic=characteristic;
    if ((4+value_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_gatt_write_characteristic_value_without_response.value.len=value_len;
    memcpy(cmd->data.cmd_gatt_write_characteristic_value_without_response.value.data,value,value_len);

    cmd->header=sl_bt_cmd_gatt_write_characteristic_value_without_response_id+(((4+value_len)&0xff)<<8)+(((4+value_len)&0x700)>>8);


    sl_bt_host_handle_command();
    if (sent_len) {
        *sent_len = rsp->data.rsp_gatt_write_characteristic_value_without_response.sent_len;
    }
    return rsp->data.rsp_gatt_write_characteristic_value_without_response.result;

}

sl_status_t sl_bt_gatt_prepare_characteristic_value_write(uint8_t connection,
                                                          uint16_t characteristic,
                                                          uint16_t offset,
                                                          size_t value_len,
                                                          const uint8_t* value,
                                                          uint16_t *sent_len) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_prepare_characteristic_value_write.connection=connection;
    cmd->data.cmd_gatt_prepare_characteristic_value_write.characteristic=characteristic;
    cmd->data.cmd_gatt_prepare_characteristic_value_write.offset=offset;
    if ((6+value_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_gatt_prepare_characteristic_value_write.value.len=value_len;
    memcpy(cmd->data.cmd_gatt_prepare_characteristic_value_write.value.data,value,value_len);

    cmd->header=sl_bt_cmd_gatt_prepare_characteristic_value_write_id+(((6+value_len)&0xff)<<8)+(((6+value_len)&0x700)>>8);


    sl_bt_host_handle_command();
    if (sent_len) {
        *sent_len = rsp->data.rsp_gatt_prepare_characteristic_value_write.sent_len;
    }
    return rsp->data.rsp_gatt_prepare_characteristic_value_write.result;

}

sl_status_t sl_bt_gatt_prepare_characteristic_value_reliable_write(uint8_t connection,
                                                                   uint16_t characteristic,
                                                                   uint16_t offset,
                                                                   size_t value_len,
                                                                   const uint8_t* value,
                                                                   uint16_t *sent_len) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_prepare_characteristic_value_reliable_write.connection=connection;
    cmd->data.cmd_gatt_prepare_characteristic_value_reliable_write.characteristic=characteristic;
    cmd->data.cmd_gatt_prepare_characteristic_value_reliable_write.offset=offset;
    if ((6+value_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_gatt_prepare_characteristic_value_reliable_write.value.len=value_len;
    memcpy(cmd->data.cmd_gatt_prepare_characteristic_value_reliable_write.value.data,value,value_len);

    cmd->header=sl_bt_cmd_gatt_prepare_characteristic_value_reliable_write_id+(((6+value_len)&0xff)<<8)+(((6+value_len)&0x700)>>8);


    sl_bt_host_handle_command();
    if (sent_len) {
        *sent_len = rsp->data.rsp_gatt_prepare_characteristic_value_reliable_write.sent_len;
    }
    return rsp->data.rsp_gatt_prepare_characteristic_value_reliable_write.result;

}

sl_status_t sl_bt_gatt_execute_characteristic_value_write(uint8_t connection,
                                                          uint8_t flags) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_execute_characteristic_value_write.connection=connection;
    cmd->data.cmd_gatt_execute_characteristic_value_write.flags=flags;

    cmd->header=sl_bt_cmd_gatt_execute_characteristic_value_write_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_execute_characteristic_value_write.result;

}

sl_status_t sl_bt_gatt_read_descriptor_value(uint8_t connection,
                                             uint16_t descriptor) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_read_descriptor_value.connection=connection;
    cmd->data.cmd_gatt_read_descriptor_value.descriptor=descriptor;

    cmd->header=sl_bt_cmd_gatt_read_descriptor_value_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_read_descriptor_value.result;

}

sl_status_t sl_bt_gatt_write_descriptor_value(uint8_t connection,
                                              uint16_t descriptor,
                                              size_t value_len,
                                              const uint8_t* value) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_write_descriptor_value.connection=connection;
    cmd->data.cmd_gatt_write_descriptor_value.descriptor=descriptor;
    if ((4+value_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_gatt_write_descriptor_value.value.len=value_len;
    memcpy(cmd->data.cmd_gatt_write_descriptor_value.value.data,value,value_len);

    cmd->header=sl_bt_cmd_gatt_write_descriptor_value_id+(((4+value_len)&0xff)<<8)+(((4+value_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_write_descriptor_value.result;

}

sl_status_t sl_bt_gattdb_new_session(uint16_t *session) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_gattdb_new_session_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    if (session) {
        *session = rsp->data.rsp_gattdb_new_session.session;
    }
    return rsp->data.rsp_gattdb_new_session.result;

}

sl_status_t sl_bt_gattdb_add_service(uint16_t session,
                                     uint8_t type,
                                     uint8_t property,
                                     size_t uuid_len,
                                     const uint8_t* uuid,
                                     uint16_t *service) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gattdb_add_service.session=session;
    cmd->data.cmd_gattdb_add_service.type=type;
    cmd->data.cmd_gattdb_add_service.property=property;
    if ((5+uuid_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_gattdb_add_service.uuid.len=uuid_len;
    memcpy(cmd->data.cmd_gattdb_add_service.uuid.data,uuid,uuid_len);

    cmd->header=sl_bt_cmd_gattdb_add_service_id+(((5+uuid_len)&0xff)<<8)+(((5+uuid_len)&0x700)>>8);


    sl_bt_host_handle_command();
    if (service) {
        *service = rsp->data.rsp_gattdb_add_service.service;
    }
    return rsp->data.rsp_gattdb_add_service.result;

}

sl_status_t sl_bt_gattdb_remove_service(uint16_t session, uint16_t service) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gattdb_remove_service.session=session;
    cmd->data.cmd_gattdb_remove_service.service=service;

    cmd->header=sl_bt_cmd_gattdb_remove_service_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gattdb_remove_service.result;

}

sl_status_t sl_bt_gattdb_add_included_service(uint16_t session,
                                              uint16_t service,
                                              uint16_t included_service,
                                              uint16_t *attribute) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gattdb_add_included_service.session=session;
    cmd->data.cmd_gattdb_add_included_service.service=service;
    cmd->data.cmd_gattdb_add_included_service.included_service=included_service;

    cmd->header=sl_bt_cmd_gattdb_add_included_service_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_bt_host_handle_command();
    if (attribute) {
        *attribute = rsp->data.rsp_gattdb_add_included_service.attribute;
    }
    return rsp->data.rsp_gattdb_add_included_service.result;

}

sl_status_t sl_bt_gattdb_remove_included_service(uint16_t session,
                                                 uint16_t attribute) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gattdb_remove_included_service.session=session;
    cmd->data.cmd_gattdb_remove_included_service.attribute=attribute;

    cmd->header=sl_bt_cmd_gattdb_remove_included_service_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gattdb_remove_included_service.result;

}

sl_status_t sl_bt_gattdb_add_uuid16_characteristic(uint16_t session,
                                                   uint16_t service,
                                                   uint16_t property,
                                                   uint16_t security,
                                                   uint8_t flag,
                                                   sl_bt_uuid_16_t uuid,
                                                   uint8_t value_type,
                                                   uint16_t maxlen,
                                                   size_t value_len,
                                                   const uint8_t* value,
                                                   uint16_t *characteristic) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gattdb_add_uuid16_characteristic.session=session;
    cmd->data.cmd_gattdb_add_uuid16_characteristic.service=service;
    cmd->data.cmd_gattdb_add_uuid16_characteristic.property=property;
    cmd->data.cmd_gattdb_add_uuid16_characteristic.security=security;
    cmd->data.cmd_gattdb_add_uuid16_characteristic.flag=flag;
    cmd->data.cmd_gattdb_add_uuid16_characteristic.uuid=uuid;
    cmd->data.cmd_gattdb_add_uuid16_characteristic.value_type=value_type;
    cmd->data.cmd_gattdb_add_uuid16_characteristic.maxlen=maxlen;
    if ((16+value_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_gattdb_add_uuid16_characteristic.value.len=value_len;
    memcpy(cmd->data.cmd_gattdb_add_uuid16_characteristic.value.data,value,value_len);

    cmd->header=sl_bt_cmd_gattdb_add_uuid16_characteristic_id+(((16+value_len)&0xff)<<8)+(((16+value_len)&0x700)>>8);


    sl_bt_host_handle_command();
    if (characteristic) {
        *characteristic = rsp->data.rsp_gattdb_add_uuid16_characteristic.characteristic;
    }
    return rsp->data.rsp_gattdb_add_uuid16_characteristic.result;

}

sl_status_t sl_bt_gattdb_add_uuid128_characteristic(uint16_t session,
                                                    uint16_t service,
                                                    uint16_t property,
                                                    uint16_t security,
                                                    uint8_t flag,
                                                    uuid_128 uuid,
                                                    uint8_t value_type,
                                                    uint16_t maxlen,
                                                    size_t value_len,
                                                    const uint8_t* value,
                                                    uint16_t *characteristic) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gattdb_add_uuid128_characteristic.session=session;
    cmd->data.cmd_gattdb_add_uuid128_characteristic.service=service;
    cmd->data.cmd_gattdb_add_uuid128_characteristic.property=property;
    cmd->data.cmd_gattdb_add_uuid128_characteristic.security=security;
    cmd->data.cmd_gattdb_add_uuid128_characteristic.flag=flag;
    cmd->data.cmd_gattdb_add_uuid128_characteristic.uuid=uuid;
    cmd->data.cmd_gattdb_add_uuid128_characteristic.value_type=value_type;
    cmd->data.cmd_gattdb_add_uuid128_characteristic.maxlen=maxlen;
    if ((30+value_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_gattdb_add_uuid128_characteristic.value.len=value_len;
    memcpy(cmd->data.cmd_gattdb_add_uuid128_characteristic.value.data,value,value_len);

    cmd->header=sl_bt_cmd_gattdb_add_uuid128_characteristic_id+(((30+value_len)&0xff)<<8)+(((30+value_len)&0x700)>>8);


    sl_bt_host_handle_command();
    if (characteristic) {
        *characteristic = rsp->data.rsp_gattdb_add_uuid128_characteristic.characteristic;
    }
    return rsp->data.rsp_gattdb_add_uuid128_characteristic.result;

}

sl_status_t sl_bt_gattdb_remove_characteristic(uint16_t session,
                                               uint16_t characteristic) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gattdb_remove_characteristic.session=session;
    cmd->data.cmd_gattdb_remove_characteristic.characteristic=characteristic;

    cmd->header=sl_bt_cmd_gattdb_remove_characteristic_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gattdb_remove_characteristic.result;

}

sl_status_t sl_bt_gattdb_add_uuid16_descriptor(uint16_t session,
                                               uint16_t characteristic,
                                               uint16_t property,
                                               uint16_t security,
                                               sl_bt_uuid_16_t uuid,
                                               uint8_t value_type,
                                               uint16_t maxlen,
                                               size_t value_len,
                                               const uint8_t* value,
                                               uint16_t *descriptor) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gattdb_add_uuid16_descriptor.session=session;
    cmd->data.cmd_gattdb_add_uuid16_descriptor.characteristic=characteristic;
    cmd->data.cmd_gattdb_add_uuid16_descriptor.property=property;
    cmd->data.cmd_gattdb_add_uuid16_descriptor.security=security;
    cmd->data.cmd_gattdb_add_uuid16_descriptor.uuid=uuid;
    cmd->data.cmd_gattdb_add_uuid16_descriptor.value_type=value_type;
    cmd->data.cmd_gattdb_add_uuid16_descriptor.maxlen=maxlen;
    if ((15+value_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_gattdb_add_uuid16_descriptor.value.len=value_len;
    memcpy(cmd->data.cmd_gattdb_add_uuid16_descriptor.value.data,value,value_len);

    cmd->header=sl_bt_cmd_gattdb_add_uuid16_descriptor_id+(((15+value_len)&0xff)<<8)+(((15+value_len)&0x700)>>8);


    sl_bt_host_handle_command();
    if (descriptor) {
        *descriptor = rsp->data.rsp_gattdb_add_uuid16_descriptor.descriptor;
    }
    return rsp->data.rsp_gattdb_add_uuid16_descriptor.result;

}

sl_status_t sl_bt_gattdb_add_uuid128_descriptor(uint16_t session,
                                                uint16_t characteristic,
                                                uint16_t property,
                                                uint16_t security,
                                                uuid_128 uuid,
                                                uint8_t value_type,
                                                uint16_t maxlen,
                                                size_t value_len,
                                                const uint8_t* value,
                                                uint16_t *descriptor) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gattdb_add_uuid128_descriptor.session=session;
    cmd->data.cmd_gattdb_add_uuid128_descriptor.characteristic=characteristic;
    cmd->data.cmd_gattdb_add_uuid128_descriptor.property=property;
    cmd->data.cmd_gattdb_add_uuid128_descriptor.security=security;
    cmd->data.cmd_gattdb_add_uuid128_descriptor.uuid=uuid;
    cmd->data.cmd_gattdb_add_uuid128_descriptor.value_type=value_type;
    cmd->data.cmd_gattdb_add_uuid128_descriptor.maxlen=maxlen;
    if ((29+value_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_gattdb_add_uuid128_descriptor.value.len=value_len;
    memcpy(cmd->data.cmd_gattdb_add_uuid128_descriptor.value.data,value,value_len);

    cmd->header=sl_bt_cmd_gattdb_add_uuid128_descriptor_id+(((29+value_len)&0xff)<<8)+(((29+value_len)&0x700)>>8);


    sl_bt_host_handle_command();
    if (descriptor) {
        *descriptor = rsp->data.rsp_gattdb_add_uuid128_descriptor.descriptor;
    }
    return rsp->data.rsp_gattdb_add_uuid128_descriptor.result;

}

sl_status_t sl_bt_gattdb_remove_descriptor(uint16_t session,
                                           uint16_t descriptor) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gattdb_remove_descriptor.session=session;
    cmd->data.cmd_gattdb_remove_descriptor.descriptor=descriptor;

    cmd->header=sl_bt_cmd_gattdb_remove_descriptor_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gattdb_remove_descriptor.result;

}

sl_status_t sl_bt_gattdb_start_service(uint16_t session, uint16_t service) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gattdb_start_service.session=session;
    cmd->data.cmd_gattdb_start_service.service=service;

    cmd->header=sl_bt_cmd_gattdb_start_service_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gattdb_start_service.result;

}

sl_status_t sl_bt_gattdb_stop_service(uint16_t session, uint16_t service) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gattdb_stop_service.session=session;
    cmd->data.cmd_gattdb_stop_service.service=service;

    cmd->header=sl_bt_cmd_gattdb_stop_service_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gattdb_stop_service.result;

}

sl_status_t sl_bt_gattdb_start_characteristic(uint16_t session,
                                              uint16_t characteristic) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gattdb_start_characteristic.session=session;
    cmd->data.cmd_gattdb_start_characteristic.characteristic=characteristic;

    cmd->header=sl_bt_cmd_gattdb_start_characteristic_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gattdb_start_characteristic.result;

}

sl_status_t sl_bt_gattdb_stop_characteristic(uint16_t session,
                                             uint16_t characteristic) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gattdb_stop_characteristic.session=session;
    cmd->data.cmd_gattdb_stop_characteristic.characteristic=characteristic;

    cmd->header=sl_bt_cmd_gattdb_stop_characteristic_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gattdb_stop_characteristic.result;

}

sl_status_t sl_bt_gattdb_commit(uint16_t session) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gattdb_commit.session=session;

    cmd->header=sl_bt_cmd_gattdb_commit_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gattdb_commit.result;

}

sl_status_t sl_bt_gattdb_abort(uint16_t session) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gattdb_abort.session=session;

    cmd->header=sl_bt_cmd_gattdb_abort_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gattdb_abort.result;

}

sl_status_t sl_bt_gatt_server_set_max_mtu(uint16_t max_mtu,
                                          uint16_t *max_mtu_out) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_set_max_mtu.max_mtu=max_mtu;

    cmd->header=sl_bt_cmd_gatt_server_set_max_mtu_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    if (max_mtu_out) {
        *max_mtu_out = rsp->data.rsp_gatt_server_set_max_mtu.max_mtu_out;
    }
    return rsp->data.rsp_gatt_server_set_max_mtu.result;

}

sl_status_t sl_bt_gatt_server_get_mtu(uint8_t connection, uint16_t *mtu) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_get_mtu.connection=connection;

    cmd->header=sl_bt_cmd_gatt_server_get_mtu_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    if (mtu) {
        *mtu = rsp->data.rsp_gatt_server_get_mtu.mtu;
    }
    return rsp->data.rsp_gatt_server_get_mtu.result;

}

sl_status_t sl_bt_gatt_server_find_attribute(uint16_t start,
                                             size_t type_len,
                                             const uint8_t* type,
                                             uint16_t *attribute) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_find_attribute.start=start;
    if ((3+type_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_gatt_server_find_attribute.type.len=type_len;
    memcpy(cmd->data.cmd_gatt_server_find_attribute.type.data,type,type_len);

    cmd->header=sl_bt_cmd_gatt_server_find_attribute_id+(((3+type_len)&0xff)<<8)+(((3+type_len)&0x700)>>8);


    sl_bt_host_handle_command();
    if (attribute) {
        *attribute = rsp->data.rsp_gatt_server_find_attribute.attribute;
    }
    return rsp->data.rsp_gatt_server_find_attribute.result;

}

sl_status_t sl_bt_gatt_server_read_attribute_value(uint16_t attribute,
                                                   uint16_t offset,
                                                   size_t max_value_size,
                                                   size_t *value_len,
                                                   uint8_t *value) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_read_attribute_value.attribute=attribute;
    cmd->data.cmd_gatt_server_read_attribute_value.offset=offset;

    cmd->header=sl_bt_cmd_gatt_server_read_attribute_value_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    if (value_len) {
        *value_len = rsp->data.rsp_gatt_server_read_attribute_value.value.len;
    }
    if (value && (rsp->data.rsp_gatt_server_read_attribute_value.value.len <= max_value_size)) {
        memcpy(value,rsp->data.rsp_gatt_server_read_attribute_value.value.data,rsp->data.rsp_gatt_server_read_attribute_value.value.len);
    }
    return rsp->data.rsp_gatt_server_read_attribute_value.result;

}

sl_status_t sl_bt_gatt_server_read_attribute_type(uint16_t attribute,
                                                  size_t max_type_size,
                                                  size_t *type_len,
                                                  uint8_t *type) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_read_attribute_type.attribute=attribute;

    cmd->header=sl_bt_cmd_gatt_server_read_attribute_type_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    if (type_len) {
        *type_len = rsp->data.rsp_gatt_server_read_attribute_type.type.len;
    }
    if (type && (rsp->data.rsp_gatt_server_read_attribute_type.type.len <= max_type_size)) {
        memcpy(type,rsp->data.rsp_gatt_server_read_attribute_type.type.data,rsp->data.rsp_gatt_server_read_attribute_type.type.len);
    }
    return rsp->data.rsp_gatt_server_read_attribute_type.result;

}

sl_status_t sl_bt_gatt_server_write_attribute_value(uint16_t attribute,
                                                    uint16_t offset,
                                                    size_t value_len,
                                                    const uint8_t* value) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_write_attribute_value.attribute=attribute;
    cmd->data.cmd_gatt_server_write_attribute_value.offset=offset;
    if ((5+value_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_gatt_server_write_attribute_value.value.len=value_len;
    memcpy(cmd->data.cmd_gatt_server_write_attribute_value.value.data,value,value_len);

    cmd->header=sl_bt_cmd_gatt_server_write_attribute_value_id+(((5+value_len)&0xff)<<8)+(((5+value_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_server_write_attribute_value.result;

}

sl_status_t sl_bt_gatt_server_send_user_read_response(uint8_t connection,
                                                      uint16_t characteristic,
                                                      uint8_t att_errorcode,
                                                      size_t value_len,
                                                      const uint8_t* value,
                                                      uint16_t *sent_len) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_send_user_read_response.connection=connection;
    cmd->data.cmd_gatt_server_send_user_read_response.characteristic=characteristic;
    cmd->data.cmd_gatt_server_send_user_read_response.att_errorcode=att_errorcode;
    if ((5+value_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_gatt_server_send_user_read_response.value.len=value_len;
    memcpy(cmd->data.cmd_gatt_server_send_user_read_response.value.data,value,value_len);

    cmd->header=sl_bt_cmd_gatt_server_send_user_read_response_id+(((5+value_len)&0xff)<<8)+(((5+value_len)&0x700)>>8);


    sl_bt_host_handle_command();
    if (sent_len) {
        *sent_len = rsp->data.rsp_gatt_server_send_user_read_response.sent_len;
    }
    return rsp->data.rsp_gatt_server_send_user_read_response.result;

}

sl_status_t sl_bt_gatt_server_send_user_write_response(uint8_t connection,
                                                       uint16_t characteristic,
                                                       uint8_t att_errorcode) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_send_user_write_response.connection=connection;
    cmd->data.cmd_gatt_server_send_user_write_response.characteristic=characteristic;
    cmd->data.cmd_gatt_server_send_user_write_response.att_errorcode=att_errorcode;

    cmd->header=sl_bt_cmd_gatt_server_send_user_write_response_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_server_send_user_write_response.result;

}

sl_status_t sl_bt_gatt_server_send_notification(uint8_t connection,
                                                uint16_t characteristic,
                                                size_t value_len,
                                                const uint8_t* value) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_send_notification.connection=connection;
    cmd->data.cmd_gatt_server_send_notification.characteristic=characteristic;
    if ((4+value_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_gatt_server_send_notification.value.len=value_len;
    memcpy(cmd->data.cmd_gatt_server_send_notification.value.data,value,value_len);

    cmd->header=sl_bt_cmd_gatt_server_send_notification_id+(((4+value_len)&0xff)<<8)+(((4+value_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_server_send_notification.result;

}

sl_status_t sl_bt_gatt_server_send_indication(uint8_t connection,
                                              uint16_t characteristic,
                                              size_t value_len,
                                              const uint8_t* value) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_send_indication.connection=connection;
    cmd->data.cmd_gatt_server_send_indication.characteristic=characteristic;
    if ((4+value_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_gatt_server_send_indication.value.len=value_len;
    memcpy(cmd->data.cmd_gatt_server_send_indication.value.data,value,value_len);

    cmd->header=sl_bt_cmd_gatt_server_send_indication_id+(((4+value_len)&0xff)<<8)+(((4+value_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_server_send_indication.result;

}

sl_status_t sl_bt_gatt_server_notify_all(uint16_t characteristic,
                                         size_t value_len,
                                         const uint8_t* value) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_notify_all.characteristic=characteristic;
    if ((3+value_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_gatt_server_notify_all.value.len=value_len;
    memcpy(cmd->data.cmd_gatt_server_notify_all.value.data,value,value_len);

    cmd->header=sl_bt_cmd_gatt_server_notify_all_id+(((3+value_len)&0xff)<<8)+(((3+value_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_server_notify_all.result;

}

sl_status_t sl_bt_gatt_server_read_client_configuration(uint8_t connection,
                                                        uint16_t characteristic,
                                                        uint16_t *client_config_flags) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_read_client_configuration.connection=connection;
    cmd->data.cmd_gatt_server_read_client_configuration.characteristic=characteristic;

    cmd->header=sl_bt_cmd_gatt_server_read_client_configuration_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_bt_host_handle_command();
    if (client_config_flags) {
        *client_config_flags = rsp->data.rsp_gatt_server_read_client_configuration.client_config_flags;
    }
    return rsp->data.rsp_gatt_server_read_client_configuration.result;

}

sl_status_t sl_bt_gatt_server_send_user_prepare_write_response(uint8_t connection,
                                                               uint16_t characteristic,
                                                               uint8_t att_errorcode,
                                                               uint16_t offset,
                                                               size_t value_len,
                                                               const uint8_t* value) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_send_user_prepare_write_response.connection=connection;
    cmd->data.cmd_gatt_server_send_user_prepare_write_response.characteristic=characteristic;
    cmd->data.cmd_gatt_server_send_user_prepare_write_response.att_errorcode=att_errorcode;
    cmd->data.cmd_gatt_server_send_user_prepare_write_response.offset=offset;
    if ((7+value_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_gatt_server_send_user_prepare_write_response.value.len=value_len;
    memcpy(cmd->data.cmd_gatt_server_send_user_prepare_write_response.value.data,value,value_len);

    cmd->header=sl_bt_cmd_gatt_server_send_user_prepare_write_response_id+(((7+value_len)&0xff)<<8)+(((7+value_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_server_send_user_prepare_write_response.result;

}

sl_status_t sl_bt_gatt_server_set_capabilities(uint32_t caps,
                                               uint32_t reserved) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_set_capabilities.caps=caps;
    cmd->data.cmd_gatt_server_set_capabilities.reserved=reserved;

    cmd->header=sl_bt_cmd_gatt_server_set_capabilities_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_server_set_capabilities.result;

}

sl_status_t sl_bt_gatt_server_enable_capabilities(uint32_t caps) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_enable_capabilities.caps=caps;

    cmd->header=sl_bt_cmd_gatt_server_enable_capabilities_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_server_enable_capabilities.result;

}

sl_status_t sl_bt_gatt_server_disable_capabilities(uint32_t caps) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_disable_capabilities.caps=caps;

    cmd->header=sl_bt_cmd_gatt_server_disable_capabilities_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_server_disable_capabilities.result;

}

sl_status_t sl_bt_gatt_server_get_enabled_capabilities(uint32_t *caps) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_gatt_server_get_enabled_capabilities_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    if (caps) {
        *caps = rsp->data.rsp_gatt_server_get_enabled_capabilities.caps;
    }
    return rsp->data.rsp_gatt_server_get_enabled_capabilities.result;

}

sl_status_t sl_bt_gatt_server_read_client_supported_features(uint8_t connection,
                                                             uint8_t *client_features) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_read_client_supported_features.connection=connection;

    cmd->header=sl_bt_cmd_gatt_server_read_client_supported_features_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    if (client_features) {
        *client_features = rsp->data.rsp_gatt_server_read_client_supported_features.client_features;
    }
    return rsp->data.rsp_gatt_server_read_client_supported_features.result;

}

sl_status_t sl_bt_nvm_save(uint16_t key,
                           size_t value_len,
                           const uint8_t* value) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_nvm_save.key=key;
    if ((3+value_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_nvm_save.value.len=value_len;
    memcpy(cmd->data.cmd_nvm_save.value.data,value,value_len);

    cmd->header=sl_bt_cmd_nvm_save_id+(((3+value_len)&0xff)<<8)+(((3+value_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_nvm_save.result;

}

sl_status_t sl_bt_nvm_load(uint16_t key,
                           size_t max_value_size,
                           size_t *value_len,
                           uint8_t *value) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_nvm_load.key=key;

    cmd->header=sl_bt_cmd_nvm_load_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    if (value_len) {
        *value_len = rsp->data.rsp_nvm_load.value.len;
    }
    if (value && (rsp->data.rsp_nvm_load.value.len <= max_value_size)) {
        memcpy(value,rsp->data.rsp_nvm_load.value.data,rsp->data.rsp_nvm_load.value.len);
    }
    return rsp->data.rsp_nvm_load.result;

}

sl_status_t sl_bt_nvm_erase(uint16_t key) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_nvm_erase.key=key;

    cmd->header=sl_bt_cmd_nvm_erase_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_nvm_erase.result;

}

sl_status_t sl_bt_nvm_erase_all() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_nvm_erase_all_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_nvm_erase_all.result;

}

sl_status_t sl_bt_test_dtm_tx_v4(uint8_t packet_type,
                                 uint8_t length,
                                 uint8_t channel,
                                 uint8_t phy,
                                 int8_t power_level) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_test_dtm_tx_v4.packet_type=packet_type;
    cmd->data.cmd_test_dtm_tx_v4.length=length;
    cmd->data.cmd_test_dtm_tx_v4.channel=channel;
    cmd->data.cmd_test_dtm_tx_v4.phy=phy;
    cmd->data.cmd_test_dtm_tx_v4.power_level=power_level;

    cmd->header=sl_bt_cmd_test_dtm_tx_v4_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_test_dtm_tx_v4.result;

}

sl_status_t sl_bt_test_dtm_tx_cw(uint8_t packet_type,
                                 uint8_t channel,
                                 uint8_t phy,
                                 int16_t power_level) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_test_dtm_tx_cw.packet_type=packet_type;
    cmd->data.cmd_test_dtm_tx_cw.channel=channel;
    cmd->data.cmd_test_dtm_tx_cw.phy=phy;
    cmd->data.cmd_test_dtm_tx_cw.power_level=power_level;

    cmd->header=sl_bt_cmd_test_dtm_tx_cw_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_test_dtm_tx_cw.result;

}

sl_status_t sl_bt_test_dtm_rx(uint8_t channel, uint8_t phy) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_test_dtm_rx.channel=channel;
    cmd->data.cmd_test_dtm_rx.phy=phy;

    cmd->header=sl_bt_cmd_test_dtm_rx_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_test_dtm_rx.result;

}

sl_status_t sl_bt_test_dtm_end() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_test_dtm_end_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_test_dtm_end.result;

}

sl_status_t sl_bt_sm_configure(uint8_t flags, uint8_t io_capabilities) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sm_configure.flags=flags;
    cmd->data.cmd_sm_configure.io_capabilities=io_capabilities;

    cmd->header=sl_bt_cmd_sm_configure_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_configure.result;

}

sl_status_t sl_bt_sm_set_minimum_key_size(uint8_t minimum_key_size) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sm_set_minimum_key_size.minimum_key_size=minimum_key_size;

    cmd->header=sl_bt_cmd_sm_set_minimum_key_size_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_set_minimum_key_size.result;

}

sl_status_t sl_bt_sm_set_debug_mode() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_sm_set_debug_mode_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_set_debug_mode.result;

}

SL_BGAPI_DEPRECATED sl_status_t sl_bt_sm_add_to_whitelist(bd_addr address, uint8_t address_type) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    memcpy(&cmd->data.cmd_sm_add_to_whitelist.address,&address,sizeof(bd_addr));
    cmd->data.cmd_sm_add_to_whitelist.address_type=address_type;

    cmd->header=sl_bt_cmd_sm_add_to_whitelist_id+(((7)&0xff)<<8)+(((7)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_add_to_whitelist.result;

}

sl_status_t sl_bt_sm_store_bonding_configuration(uint8_t max_bonding_count,
                                                 uint8_t policy_flags) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sm_store_bonding_configuration.max_bonding_count=max_bonding_count;
    cmd->data.cmd_sm_store_bonding_configuration.policy_flags=policy_flags;

    cmd->header=sl_bt_cmd_sm_store_bonding_configuration_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_store_bonding_configuration.result;

}

sl_status_t sl_bt_sm_set_bondable_mode(uint8_t bondable) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sm_set_bondable_mode.bondable=bondable;

    cmd->header=sl_bt_cmd_sm_set_bondable_mode_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_set_bondable_mode.result;

}

sl_status_t sl_bt_sm_set_passkey(int32_t passkey) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sm_set_passkey.passkey=passkey;

    cmd->header=sl_bt_cmd_sm_set_passkey_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_set_passkey.result;

}

sl_status_t sl_bt_sm_increase_security(uint8_t connection) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sm_increase_security.connection=connection;

    cmd->header=sl_bt_cmd_sm_increase_security_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_increase_security.result;

}

sl_status_t sl_bt_sm_enter_passkey(uint8_t connection, int32_t passkey) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sm_enter_passkey.connection=connection;
    cmd->data.cmd_sm_enter_passkey.passkey=passkey;

    cmd->header=sl_bt_cmd_sm_enter_passkey_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_enter_passkey.result;

}

sl_status_t sl_bt_sm_passkey_confirm(uint8_t connection, uint8_t confirm) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sm_passkey_confirm.connection=connection;
    cmd->data.cmd_sm_passkey_confirm.confirm=confirm;

    cmd->header=sl_bt_cmd_sm_passkey_confirm_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_passkey_confirm.result;

}

sl_status_t sl_bt_sm_bonding_confirm(uint8_t connection, uint8_t confirm) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sm_bonding_confirm.connection=connection;
    cmd->data.cmd_sm_bonding_confirm.confirm=confirm;

    cmd->header=sl_bt_cmd_sm_bonding_confirm_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_bonding_confirm.result;

}

sl_status_t sl_bt_sm_delete_bonding(uint8_t bonding) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sm_delete_bonding.bonding=bonding;

    cmd->header=sl_bt_cmd_sm_delete_bonding_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_delete_bonding.result;

}

sl_status_t sl_bt_sm_delete_bondings() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_sm_delete_bondings_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_delete_bondings.result;

}

sl_status_t sl_bt_sm_get_bonding_handles(uint32_t reserved,
                                         uint32_t *num_bondings,
                                         size_t max_bondings_size,
                                         size_t *bondings_len,
                                         uint8_t *bondings) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sm_get_bonding_handles.reserved=reserved;

    cmd->header=sl_bt_cmd_sm_get_bonding_handles_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    if (num_bondings) {
        *num_bondings = rsp->data.rsp_sm_get_bonding_handles.num_bondings;
    }
    if (bondings_len) {
        *bondings_len = rsp->data.rsp_sm_get_bonding_handles.bondings.len;
    }
    if (bondings && (rsp->data.rsp_sm_get_bonding_handles.bondings.len <= max_bondings_size)) {
        memcpy(bondings,rsp->data.rsp_sm_get_bonding_handles.bondings.data,rsp->data.rsp_sm_get_bonding_handles.bondings.len);
    }
    return rsp->data.rsp_sm_get_bonding_handles.result;

}

sl_status_t sl_bt_sm_get_bonding_details(uint32_t bonding,
                                         bd_addr *address,
                                         uint8_t *address_type,
                                         uint8_t *security_mode,
                                         uint8_t *key_size) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sm_get_bonding_details.bonding=bonding;

    cmd->header=sl_bt_cmd_sm_get_bonding_details_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    if (address) {
        memcpy(address,&rsp->data.rsp_sm_get_bonding_details.address,sizeof(bd_addr));
    }
    if (address_type) {
        *address_type = rsp->data.rsp_sm_get_bonding_details.address_type;
    }
    if (security_mode) {
        *security_mode = rsp->data.rsp_sm_get_bonding_details.security_mode;
    }
    if (key_size) {
        *key_size = rsp->data.rsp_sm_get_bonding_details.key_size;
    }
    return rsp->data.rsp_sm_get_bonding_details.result;

}

sl_status_t sl_bt_sm_find_bonding_by_address(bd_addr address,
                                             uint32_t *bonding,
                                             uint8_t *security_mode,
                                             uint8_t *key_size) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    memcpy(&cmd->data.cmd_sm_find_bonding_by_address.address,&address,sizeof(bd_addr));

    cmd->header=sl_bt_cmd_sm_find_bonding_by_address_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_bt_host_handle_command();
    if (bonding) {
        *bonding = rsp->data.rsp_sm_find_bonding_by_address.bonding;
    }
    if (security_mode) {
        *security_mode = rsp->data.rsp_sm_find_bonding_by_address.security_mode;
    }
    if (key_size) {
        *key_size = rsp->data.rsp_sm_find_bonding_by_address.key_size;
    }
    return rsp->data.rsp_sm_find_bonding_by_address.result;

}

sl_status_t sl_bt_sm_resolve_rpa(bd_addr rpa,
                                 bd_addr *address,
                                 uint8_t *address_type,
                                 uint32_t *bonding) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    memcpy(&cmd->data.cmd_sm_resolve_rpa.rpa,&rpa,sizeof(bd_addr));

    cmd->header=sl_bt_cmd_sm_resolve_rpa_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_bt_host_handle_command();
    if (address) {
        memcpy(address,&rsp->data.rsp_sm_resolve_rpa.address,sizeof(bd_addr));
    }
    if (address_type) {
        *address_type = rsp->data.rsp_sm_resolve_rpa.address_type;
    }
    if (bonding) {
        *bonding = rsp->data.rsp_sm_resolve_rpa.bonding;
    }
    return rsp->data.rsp_sm_resolve_rpa.result;

}

sl_status_t sl_bt_sm_set_bonding_key(uint32_t bonding,
                                     uint8_t key_type,
                                     aes_key_128 key) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sm_set_bonding_key.bonding=bonding;
    cmd->data.cmd_sm_set_bonding_key.key_type=key_type;
    memcpy(&cmd->data.cmd_sm_set_bonding_key.key,&key,sizeof(aes_key_128));

    cmd->header=sl_bt_cmd_sm_set_bonding_key_id+(((21)&0xff)<<8)+(((21)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_set_bonding_key.result;

}

sl_status_t sl_bt_sm_set_legacy_oob(uint8_t enable, aes_key_128 oob_data) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sm_set_legacy_oob.enable=enable;
    memcpy(&cmd->data.cmd_sm_set_legacy_oob.oob_data,&oob_data,sizeof(aes_key_128));

    cmd->header=sl_bt_cmd_sm_set_legacy_oob_id+(((17)&0xff)<<8)+(((17)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_set_legacy_oob.result;

}

sl_status_t sl_bt_sm_set_oob(uint8_t enable,
                             aes_key_128 *random,
                             aes_key_128 *confirm) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sm_set_oob.enable=enable;

    cmd->header=sl_bt_cmd_sm_set_oob_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    if (random) {
        memcpy(random,&rsp->data.rsp_sm_set_oob.random,sizeof(aes_key_128));
    }
    if (confirm) {
        memcpy(confirm,&rsp->data.rsp_sm_set_oob.confirm,sizeof(aes_key_128));
    }
    return rsp->data.rsp_sm_set_oob.result;

}

sl_status_t sl_bt_sm_set_remote_oob(uint8_t enable,
                                    aes_key_128 random,
                                    aes_key_128 confirm) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sm_set_remote_oob.enable=enable;
    memcpy(&cmd->data.cmd_sm_set_remote_oob.random,&random,sizeof(aes_key_128));
    memcpy(&cmd->data.cmd_sm_set_remote_oob.confirm,&confirm,sizeof(aes_key_128));

    cmd->header=sl_bt_cmd_sm_set_remote_oob_id+(((33)&0xff)<<8)+(((33)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_set_remote_oob.result;

}

sl_status_t sl_bt_sm_set_bonding_data(uint8_t connection,
                                      uint8_t type,
                                      size_t data_len,
                                      const uint8_t* data) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sm_set_bonding_data.connection=connection;
    cmd->data.cmd_sm_set_bonding_data.type=type;
    if ((3+data_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_sm_set_bonding_data.data.len=data_len;
    memcpy(cmd->data.cmd_sm_set_bonding_data.data.data,data,data_len);

    cmd->header=sl_bt_cmd_sm_set_bonding_data_id+(((3+data_len)&0xff)<<8)+(((3+data_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_set_bonding_data.result;

}

sl_status_t sl_bt_external_bondingdb_set_data(uint8_t connection,
                                              uint8_t type,
                                              size_t data_len,
                                              const uint8_t* data) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_external_bondingdb_set_data.connection=connection;
    cmd->data.cmd_external_bondingdb_set_data.type=type;
    if ((3+data_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_external_bondingdb_set_data.data.len=data_len;
    memcpy(cmd->data.cmd_external_bondingdb_set_data.data.data,data,data_len);

    cmd->header=sl_bt_cmd_external_bondingdb_set_data_id+(((3+data_len)&0xff)<<8)+(((3+data_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_external_bondingdb_set_data.result;

}

sl_status_t sl_bt_resolving_list_add_device_by_bonding(uint32_t bonding,
                                                       uint8_t privacy_mode) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_resolving_list_add_device_by_bonding.bonding=bonding;
    cmd->data.cmd_resolving_list_add_device_by_bonding.privacy_mode=privacy_mode;

    cmd->header=sl_bt_cmd_resolving_list_add_device_by_bonding_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_resolving_list_add_device_by_bonding.result;

}

sl_status_t sl_bt_resolving_list_add_device_by_address(bd_addr address,
                                                       uint8_t address_type,
                                                       aes_key_128 key,
                                                       uint8_t privacy_mode) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    memcpy(&cmd->data.cmd_resolving_list_add_device_by_address.address,&address,sizeof(bd_addr));
    cmd->data.cmd_resolving_list_add_device_by_address.address_type=address_type;
    memcpy(&cmd->data.cmd_resolving_list_add_device_by_address.key,&key,sizeof(aes_key_128));
    cmd->data.cmd_resolving_list_add_device_by_address.privacy_mode=privacy_mode;

    cmd->header=sl_bt_cmd_resolving_list_add_device_by_address_id+(((24)&0xff)<<8)+(((24)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_resolving_list_add_device_by_address.result;

}

sl_status_t sl_bt_resolving_list_remove_device_by_bonding(uint32_t bonding) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_resolving_list_remove_device_by_bonding.bonding=bonding;

    cmd->header=sl_bt_cmd_resolving_list_remove_device_by_bonding_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_resolving_list_remove_device_by_bonding.result;

}

sl_status_t sl_bt_resolving_list_remove_device_by_address(bd_addr address,
                                                          uint8_t address_type) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    memcpy(&cmd->data.cmd_resolving_list_remove_device_by_address.address,&address,sizeof(bd_addr));
    cmd->data.cmd_resolving_list_remove_device_by_address.address_type=address_type;

    cmd->header=sl_bt_cmd_resolving_list_remove_device_by_address_id+(((7)&0xff)<<8)+(((7)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_resolving_list_remove_device_by_address.result;

}

sl_status_t sl_bt_resolving_list_remove_all_devices() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_resolving_list_remove_all_devices_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_resolving_list_remove_all_devices.result;

}

sl_status_t sl_bt_accept_list_add_device_by_bonding(uint32_t bonding) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_accept_list_add_device_by_bonding.bonding=bonding;

    cmd->header=sl_bt_cmd_accept_list_add_device_by_bonding_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_accept_list_add_device_by_bonding.result;

}

sl_status_t sl_bt_accept_list_add_device_by_address(bd_addr address,
                                                    uint8_t address_type) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    memcpy(&cmd->data.cmd_accept_list_add_device_by_address.address,&address,sizeof(bd_addr));
    cmd->data.cmd_accept_list_add_device_by_address.address_type=address_type;

    cmd->header=sl_bt_cmd_accept_list_add_device_by_address_id+(((7)&0xff)<<8)+(((7)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_accept_list_add_device_by_address.result;

}

sl_status_t sl_bt_accept_list_remove_device_by_bonding(uint32_t bonding) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_accept_list_remove_device_by_bonding.bonding=bonding;

    cmd->header=sl_bt_cmd_accept_list_remove_device_by_bonding_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_accept_list_remove_device_by_bonding.result;

}

sl_status_t sl_bt_accept_list_remove_device_by_address(bd_addr address,
                                                       uint8_t address_type) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    memcpy(&cmd->data.cmd_accept_list_remove_device_by_address.address,&address,sizeof(bd_addr));
    cmd->data.cmd_accept_list_remove_device_by_address.address_type=address_type;

    cmd->header=sl_bt_cmd_accept_list_remove_device_by_address_id+(((7)&0xff)<<8)+(((7)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_accept_list_remove_device_by_address.result;

}

sl_status_t sl_bt_accept_list_remove_all_devices() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_accept_list_remove_all_devices_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_accept_list_remove_all_devices.result;

}

sl_status_t sl_bt_ota_set_device_name(size_t name_len, const uint8_t* name) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    if ((1+name_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_ota_set_device_name.name.len=name_len;
    memcpy(cmd->data.cmd_ota_set_device_name.name.data,name,name_len);

    cmd->header=sl_bt_cmd_ota_set_device_name_id+(((1+name_len)&0xff)<<8)+(((1+name_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_ota_set_device_name.result;

}

sl_status_t sl_bt_ota_set_advertising_data(uint8_t packet_type,
                                           size_t adv_data_len,
                                           const uint8_t* adv_data) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_ota_set_advertising_data.packet_type=packet_type;
    if ((2+adv_data_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_ota_set_advertising_data.adv_data.len=adv_data_len;
    memcpy(cmd->data.cmd_ota_set_advertising_data.adv_data.data,adv_data,adv_data_len);

    cmd->header=sl_bt_cmd_ota_set_advertising_data_id+(((2+adv_data_len)&0xff)<<8)+(((2+adv_data_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_ota_set_advertising_data.result;

}

sl_status_t sl_bt_ota_set_configuration(uint32_t flags) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_ota_set_configuration.flags=flags;

    cmd->header=sl_bt_cmd_ota_set_configuration_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_ota_set_configuration.result;

}

sl_status_t sl_bt_ota_set_rf_path(uint8_t enable, uint8_t antenna) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_ota_set_rf_path.enable=enable;
    cmd->data.cmd_ota_set_rf_path.antenna=antenna;

    cmd->header=sl_bt_cmd_ota_set_rf_path_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_ota_set_rf_path.result;

}

sl_status_t sl_bt_coex_set_options(uint32_t mask, uint32_t options) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_coex_set_options.mask=mask;
    cmd->data.cmd_coex_set_options.options=options;

    cmd->header=sl_bt_cmd_coex_set_options_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_coex_set_options.result;

}

sl_status_t sl_bt_coex_set_parameters(uint8_t priority,
                                      uint8_t request,
                                      uint8_t pwm_period,
                                      uint8_t pwm_dutycycle) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_coex_set_parameters.priority=priority;
    cmd->data.cmd_coex_set_parameters.request=request;
    cmd->data.cmd_coex_set_parameters.pwm_period=pwm_period;
    cmd->data.cmd_coex_set_parameters.pwm_dutycycle=pwm_dutycycle;

    cmd->header=sl_bt_cmd_coex_set_parameters_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_coex_set_parameters.result;

}

sl_status_t sl_bt_coex_set_directional_priority_pulse(uint8_t pulse) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_coex_set_directional_priority_pulse.pulse=pulse;

    cmd->header=sl_bt_cmd_coex_set_directional_priority_pulse_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_coex_set_directional_priority_pulse.result;

}

sl_status_t sl_bt_coex_get_parameters(uint8_t *priority,
                                      uint8_t *request,
                                      uint8_t *pwm_period,
                                      uint8_t *pwm_dutycycle) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_coex_get_parameters_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    if (priority) {
        *priority = rsp->data.rsp_coex_get_parameters.priority;
    }
    if (request) {
        *request = rsp->data.rsp_coex_get_parameters.request;
    }
    if (pwm_period) {
        *pwm_period = rsp->data.rsp_coex_get_parameters.pwm_period;
    }
    if (pwm_dutycycle) {
        *pwm_dutycycle = rsp->data.rsp_coex_get_parameters.pwm_dutycycle;
    }
    return rsp->data.rsp_coex_get_parameters.result;

}

sl_status_t sl_bt_coex_get_counters(uint8_t reset,
                                    size_t max_counters_size,
                                    size_t *counters_len,
                                    uint8_t *counters) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_coex_get_counters.reset=reset;

    cmd->header=sl_bt_cmd_coex_get_counters_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    if (counters_len) {
        *counters_len = rsp->data.rsp_coex_get_counters.counters.len;
    }
    if (counters && (rsp->data.rsp_coex_get_counters.counters.len <= max_counters_size)) {
        memcpy(counters,rsp->data.rsp_coex_get_counters.counters.data,rsp->data.rsp_coex_get_counters.counters.len);
    }
    return rsp->data.rsp_coex_get_counters.result;

}

sl_status_t sl_bt_cs_security_enable(uint8_t connection) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cs_security_enable.connection=connection;

    cmd->header=sl_bt_cmd_cs_security_enable_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cs_security_enable.result;

}

sl_status_t sl_bt_cs_set_default_settings(uint8_t connection,
                                          uint8_t initiator_status,
                                          uint8_t reflector_status,
                                          uint8_t antenna_identifier,
                                          int8_t max_tx_power) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cs_set_default_settings.connection=connection;
    cmd->data.cmd_cs_set_default_settings.initiator_status=initiator_status;
    cmd->data.cmd_cs_set_default_settings.reflector_status=reflector_status;
    cmd->data.cmd_cs_set_default_settings.antenna_identifier=antenna_identifier;
    cmd->data.cmd_cs_set_default_settings.max_tx_power=max_tx_power;

    cmd->header=sl_bt_cmd_cs_set_default_settings_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cs_set_default_settings.result;

}

sl_status_t sl_bt_cs_create_config(uint8_t connection,
                                   uint8_t config_id,
                                   uint8_t create_context,
                                   uint8_t main_mode_type,
                                   uint8_t sub_mode_type,
                                   uint8_t min_main_mode_steps,
                                   uint8_t max_main_mode_steps,
                                   uint8_t main_mode_repetition,
                                   uint8_t mode_calibration_steps,
                                   uint8_t role,
                                   uint8_t rtt_type,
                                   uint8_t cs_sync_phy,
                                   const sl_bt_cs_channel_map_t *channel_map,
                                   uint8_t channel_map_repetition,
                                   uint8_t channel_selection_type,
                                   uint8_t ch3c_shape,
                                   uint8_t ch3c_jump,
                                   uint8_t companion_signal_state) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cs_create_config.connection=connection;
    cmd->data.cmd_cs_create_config.config_id=config_id;
    cmd->data.cmd_cs_create_config.create_context=create_context;
    cmd->data.cmd_cs_create_config.main_mode_type=main_mode_type;
    cmd->data.cmd_cs_create_config.sub_mode_type=sub_mode_type;
    cmd->data.cmd_cs_create_config.min_main_mode_steps=min_main_mode_steps;
    cmd->data.cmd_cs_create_config.max_main_mode_steps=max_main_mode_steps;
    cmd->data.cmd_cs_create_config.main_mode_repetition=main_mode_repetition;
    cmd->data.cmd_cs_create_config.mode_calibration_steps=mode_calibration_steps;
    cmd->data.cmd_cs_create_config.role=role;
    cmd->data.cmd_cs_create_config.rtt_type=rtt_type;
    cmd->data.cmd_cs_create_config.cs_sync_phy=cs_sync_phy;
    memcpy(&cmd->data.cmd_cs_create_config.channel_map,channel_map,sizeof(sl_bt_cs_channel_map_t));
    cmd->data.cmd_cs_create_config.channel_map_repetition=channel_map_repetition;
    cmd->data.cmd_cs_create_config.channel_selection_type=channel_selection_type;
    cmd->data.cmd_cs_create_config.ch3c_shape=ch3c_shape;
    cmd->data.cmd_cs_create_config.ch3c_jump=ch3c_jump;
    cmd->data.cmd_cs_create_config.companion_signal_state=companion_signal_state;

    cmd->header=sl_bt_cmd_cs_create_config_id+(((27)&0xff)<<8)+(((27)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cs_create_config.result;

}

sl_status_t sl_bt_cs_remove_config(uint8_t connection, uint8_t config_id) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cs_remove_config.connection=connection;
    cmd->data.cmd_cs_remove_config.config_id=config_id;

    cmd->header=sl_bt_cmd_cs_remove_config_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cs_remove_config.result;

}

sl_status_t sl_bt_cs_set_channel_classification(const sl_bt_cs_channel_map_t *channel_map) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    memcpy(&cmd->data.cmd_cs_set_channel_classification.channel_map,channel_map,sizeof(sl_bt_cs_channel_map_t));

    cmd->header=sl_bt_cmd_cs_set_channel_classification_id+(((10)&0xff)<<8)+(((10)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cs_set_channel_classification.result;

}

sl_status_t sl_bt_cs_set_procedure_parameters(uint8_t connection,
                                              uint8_t config_id,
                                              uint16_t max_procedure_len,
                                              uint16_t min_procedure_interval,
                                              uint16_t max_procedure_interval,
                                              uint16_t max_procedure_count,
                                              uint32_t min_subevent_len,
                                              uint32_t max_subevent_len,
                                              uint8_t tone_antenna_config_selection,
                                              uint8_t phy,
                                              int8_t tx_pwr_delta,
                                              uint8_t preferred_peer_antenna) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cs_set_procedure_parameters.connection=connection;
    cmd->data.cmd_cs_set_procedure_parameters.config_id=config_id;
    cmd->data.cmd_cs_set_procedure_parameters.max_procedure_len=max_procedure_len;
    cmd->data.cmd_cs_set_procedure_parameters.min_procedure_interval=min_procedure_interval;
    cmd->data.cmd_cs_set_procedure_parameters.max_procedure_interval=max_procedure_interval;
    cmd->data.cmd_cs_set_procedure_parameters.max_procedure_count=max_procedure_count;
    cmd->data.cmd_cs_set_procedure_parameters.min_subevent_len=min_subevent_len;
    cmd->data.cmd_cs_set_procedure_parameters.max_subevent_len=max_subevent_len;
    cmd->data.cmd_cs_set_procedure_parameters.tone_antenna_config_selection=tone_antenna_config_selection;
    cmd->data.cmd_cs_set_procedure_parameters.phy=phy;
    cmd->data.cmd_cs_set_procedure_parameters.tx_pwr_delta=tx_pwr_delta;
    cmd->data.cmd_cs_set_procedure_parameters.preferred_peer_antenna=preferred_peer_antenna;

    cmd->header=sl_bt_cmd_cs_set_procedure_parameters_id+(((22)&0xff)<<8)+(((22)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cs_set_procedure_parameters.result;

}

sl_status_t sl_bt_cs_procedure_enable(uint8_t connection,
                                      uint8_t enable,
                                      uint8_t config_id) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cs_procedure_enable.connection=connection;
    cmd->data.cmd_cs_procedure_enable.enable=enable;
    cmd->data.cmd_cs_procedure_enable.config_id=config_id;

    cmd->header=sl_bt_cmd_cs_procedure_enable_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cs_procedure_enable.result;

}

sl_status_t sl_bt_cs_set_antenna_configuration(size_t antenna_element_offset_len,
                                               const uint8_t* antenna_element_offset) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    if ((1+antenna_element_offset_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_cs_set_antenna_configuration.antenna_element_offset.len=antenna_element_offset_len;
    memcpy(cmd->data.cmd_cs_set_antenna_configuration.antenna_element_offset.data,antenna_element_offset,antenna_element_offset_len);

    cmd->header=sl_bt_cmd_cs_set_antenna_configuration_id+(((1+antenna_element_offset_len)&0xff)<<8)+(((1+antenna_element_offset_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cs_set_antenna_configuration.result;

}

sl_status_t sl_bt_cs_read_local_supported_capabilities(uint8_t *num_config,
                                                       uint16_t *max_consecutive_procedures,
                                                       uint8_t *num_antennas,
                                                       uint8_t *max_antenna_paths,
                                                       uint8_t *roles,
                                                       uint8_t *optional_modes,
                                                       uint8_t *rtt_capability,
                                                       uint8_t *rtt_aa_only,
                                                       uint8_t *rtt_sounding,
                                                       uint8_t *rtt_random_payload,
                                                       uint8_t *optional_cs_sync_phys,
                                                       uint16_t *optional_subfeatures,
                                                       uint16_t *optional_t_ip1_times,
                                                       uint16_t *optional_t_ip2_times,
                                                       uint16_t *optional_t_fcs_times,
                                                       uint16_t *optional_t_pm_times,
                                                       uint8_t *t_sw_times) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_cs_read_local_supported_capabilities_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    if (num_config) {
        *num_config = rsp->data.rsp_cs_read_local_supported_capabilities.num_config;
    }
    if (max_consecutive_procedures) {
        *max_consecutive_procedures = rsp->data.rsp_cs_read_local_supported_capabilities.max_consecutive_procedures;
    }
    if (num_antennas) {
        *num_antennas = rsp->data.rsp_cs_read_local_supported_capabilities.num_antennas;
    }
    if (max_antenna_paths) {
        *max_antenna_paths = rsp->data.rsp_cs_read_local_supported_capabilities.max_antenna_paths;
    }
    if (roles) {
        *roles = rsp->data.rsp_cs_read_local_supported_capabilities.roles;
    }
    if (optional_modes) {
        *optional_modes = rsp->data.rsp_cs_read_local_supported_capabilities.optional_modes;
    }
    if (rtt_capability) {
        *rtt_capability = rsp->data.rsp_cs_read_local_supported_capabilities.rtt_capability;
    }
    if (rtt_aa_only) {
        *rtt_aa_only = rsp->data.rsp_cs_read_local_supported_capabilities.rtt_aa_only;
    }
    if (rtt_sounding) {
        *rtt_sounding = rsp->data.rsp_cs_read_local_supported_capabilities.rtt_sounding;
    }
    if (rtt_random_payload) {
        *rtt_random_payload = rsp->data.rsp_cs_read_local_supported_capabilities.rtt_random_payload;
    }
    if (optional_cs_sync_phys) {
        *optional_cs_sync_phys = rsp->data.rsp_cs_read_local_supported_capabilities.optional_cs_sync_phys;
    }
    if (optional_subfeatures) {
        *optional_subfeatures = rsp->data.rsp_cs_read_local_supported_capabilities.optional_subfeatures;
    }
    if (optional_t_ip1_times) {
        *optional_t_ip1_times = rsp->data.rsp_cs_read_local_supported_capabilities.optional_t_ip1_times;
    }
    if (optional_t_ip2_times) {
        *optional_t_ip2_times = rsp->data.rsp_cs_read_local_supported_capabilities.optional_t_ip2_times;
    }
    if (optional_t_fcs_times) {
        *optional_t_fcs_times = rsp->data.rsp_cs_read_local_supported_capabilities.optional_t_fcs_times;
    }
    if (optional_t_pm_times) {
        *optional_t_pm_times = rsp->data.rsp_cs_read_local_supported_capabilities.optional_t_pm_times;
    }
    if (t_sw_times) {
        *t_sw_times = rsp->data.rsp_cs_read_local_supported_capabilities.t_sw_times;
    }
    return rsp->data.rsp_cs_read_local_supported_capabilities.result;

}

sl_status_t sl_bt_cs_test_start(uint8_t main_mode_type,
                                uint8_t sub_mode_type,
                                uint8_t main_mode_repetition,
                                uint8_t mode_calibration_steps,
                                uint8_t role,
                                uint8_t rtt_type,
                                uint8_t cs_sync_phy,
                                uint8_t antenna_selection,
                                const sl_bt_cs_subevent_length_t *subevent_len,
                                uint16_t subevent_interval,
                                int8_t tx_power,
                                uint8_t t_ip1_time,
                                uint8_t t_ip2_time,
                                uint8_t t_fcs_time,
                                uint8_t t_pm_time,
                                uint8_t t_sw_time,
                                uint8_t tone_antenna_config,
                                uint8_t companion_signal_state,
                                uint16_t drbg_nonce,
                                uint16_t override_config,
                                size_t override_parameters_len,
                                const uint8_t* override_parameters) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cs_test_start.main_mode_type=main_mode_type;
    cmd->data.cmd_cs_test_start.sub_mode_type=sub_mode_type;
    cmd->data.cmd_cs_test_start.main_mode_repetition=main_mode_repetition;
    cmd->data.cmd_cs_test_start.mode_calibration_steps=mode_calibration_steps;
    cmd->data.cmd_cs_test_start.role=role;
    cmd->data.cmd_cs_test_start.rtt_type=rtt_type;
    cmd->data.cmd_cs_test_start.cs_sync_phy=cs_sync_phy;
    cmd->data.cmd_cs_test_start.antenna_selection=antenna_selection;
    memcpy(&cmd->data.cmd_cs_test_start.subevent_len,subevent_len,sizeof(sl_bt_cs_subevent_length_t));
    cmd->data.cmd_cs_test_start.subevent_interval=subevent_interval;
    cmd->data.cmd_cs_test_start.tx_power=tx_power;
    cmd->data.cmd_cs_test_start.t_ip1_time=t_ip1_time;
    cmd->data.cmd_cs_test_start.t_ip2_time=t_ip2_time;
    cmd->data.cmd_cs_test_start.t_fcs_time=t_fcs_time;
    cmd->data.cmd_cs_test_start.t_pm_time=t_pm_time;
    cmd->data.cmd_cs_test_start.t_sw_time=t_sw_time;
    cmd->data.cmd_cs_test_start.tone_antenna_config=tone_antenna_config;
    cmd->data.cmd_cs_test_start.companion_signal_state=companion_signal_state;
    cmd->data.cmd_cs_test_start.drbg_nonce=drbg_nonce;
    cmd->data.cmd_cs_test_start.override_config=override_config;
    if ((26+override_parameters_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_cs_test_start.override_parameters.len=override_parameters_len;
    memcpy(cmd->data.cmd_cs_test_start.override_parameters.data,override_parameters,override_parameters_len);

    cmd->header=sl_bt_cmd_cs_test_start_id+(((26+override_parameters_len)&0xff)<<8)+(((26+override_parameters_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cs_test_start.result;

}

sl_status_t sl_bt_l2cap_open_le_channel(uint8_t connection,
                                        uint16_t spsm,
                                        uint16_t max_sdu,
                                        uint16_t max_pdu,
                                        uint16_t credit,
                                        uint16_t *cid) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_l2cap_open_le_channel.connection=connection;
    cmd->data.cmd_l2cap_open_le_channel.spsm=spsm;
    cmd->data.cmd_l2cap_open_le_channel.max_sdu=max_sdu;
    cmd->data.cmd_l2cap_open_le_channel.max_pdu=max_pdu;
    cmd->data.cmd_l2cap_open_le_channel.credit=credit;

    cmd->header=sl_bt_cmd_l2cap_open_le_channel_id+(((9)&0xff)<<8)+(((9)&0x700)>>8);


    sl_bt_host_handle_command();
    if (cid) {
        *cid = rsp->data.rsp_l2cap_open_le_channel.cid;
    }
    return rsp->data.rsp_l2cap_open_le_channel.result;

}

sl_status_t sl_bt_l2cap_send_le_channel_open_response(uint8_t connection,
                                                      uint16_t cid,
                                                      uint16_t max_sdu,
                                                      uint16_t max_pdu,
                                                      uint16_t credit,
                                                      uint16_t errorcode) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_l2cap_send_le_channel_open_response.connection=connection;
    cmd->data.cmd_l2cap_send_le_channel_open_response.cid=cid;
    cmd->data.cmd_l2cap_send_le_channel_open_response.max_sdu=max_sdu;
    cmd->data.cmd_l2cap_send_le_channel_open_response.max_pdu=max_pdu;
    cmd->data.cmd_l2cap_send_le_channel_open_response.credit=credit;
    cmd->data.cmd_l2cap_send_le_channel_open_response.errorcode=errorcode;

    cmd->header=sl_bt_cmd_l2cap_send_le_channel_open_response_id+(((11)&0xff)<<8)+(((11)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_l2cap_send_le_channel_open_response.result;

}

sl_status_t sl_bt_l2cap_channel_send_data(uint8_t connection,
                                          uint16_t cid,
                                          size_t data_len,
                                          const uint8_t* data) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_l2cap_channel_send_data.connection=connection;
    cmd->data.cmd_l2cap_channel_send_data.cid=cid;
    if ((4+data_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_l2cap_channel_send_data.data.len=data_len;
    memcpy(cmd->data.cmd_l2cap_channel_send_data.data.data,data,data_len);

    cmd->header=sl_bt_cmd_l2cap_channel_send_data_id+(((4+data_len)&0xff)<<8)+(((4+data_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_l2cap_channel_send_data.result;

}

sl_status_t sl_bt_l2cap_channel_send_credit(uint8_t connection,
                                            uint16_t cid,
                                            uint16_t credit) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_l2cap_channel_send_credit.connection=connection;
    cmd->data.cmd_l2cap_channel_send_credit.cid=cid;
    cmd->data.cmd_l2cap_channel_send_credit.credit=credit;

    cmd->header=sl_bt_cmd_l2cap_channel_send_credit_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_l2cap_channel_send_credit.result;

}

sl_status_t sl_bt_l2cap_close_channel(uint8_t connection, uint16_t cid) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_l2cap_close_channel.connection=connection;
    cmd->data.cmd_l2cap_close_channel.cid=cid;

    cmd->header=sl_bt_cmd_l2cap_close_channel_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_l2cap_close_channel.result;

}

sl_status_t sl_bt_cte_transmitter_set_dtm_parameters(uint8_t cte_length,
                                                     uint8_t cte_type,
                                                     size_t switching_pattern_len,
                                                     const uint8_t* switching_pattern) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_transmitter_set_dtm_parameters.cte_length=cte_length;
    cmd->data.cmd_cte_transmitter_set_dtm_parameters.cte_type=cte_type;
    if ((3+switching_pattern_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_cte_transmitter_set_dtm_parameters.switching_pattern.len=switching_pattern_len;
    memcpy(cmd->data.cmd_cte_transmitter_set_dtm_parameters.switching_pattern.data,switching_pattern,switching_pattern_len);

    cmd->header=sl_bt_cmd_cte_transmitter_set_dtm_parameters_id+(((3+switching_pattern_len)&0xff)<<8)+(((3+switching_pattern_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_transmitter_set_dtm_parameters.result;

}

sl_status_t sl_bt_cte_transmitter_clear_dtm_parameters() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_cte_transmitter_clear_dtm_parameters_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_transmitter_clear_dtm_parameters.result;

}

sl_status_t sl_bt_cte_transmitter_enable_connection_cte(uint8_t connection,
                                                        uint8_t cte_types,
                                                        size_t switching_pattern_len,
                                                        const uint8_t* switching_pattern) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_transmitter_enable_connection_cte.connection=connection;
    cmd->data.cmd_cte_transmitter_enable_connection_cte.cte_types=cte_types;
    if ((3+switching_pattern_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_cte_transmitter_enable_connection_cte.switching_pattern.len=switching_pattern_len;
    memcpy(cmd->data.cmd_cte_transmitter_enable_connection_cte.switching_pattern.data,switching_pattern,switching_pattern_len);

    cmd->header=sl_bt_cmd_cte_transmitter_enable_connection_cte_id+(((3+switching_pattern_len)&0xff)<<8)+(((3+switching_pattern_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_transmitter_enable_connection_cte.result;

}

sl_status_t sl_bt_cte_transmitter_disable_connection_cte(uint8_t connection) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_transmitter_disable_connection_cte.connection=connection;

    cmd->header=sl_bt_cmd_cte_transmitter_disable_connection_cte_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_transmitter_disable_connection_cte.result;

}

sl_status_t sl_bt_cte_transmitter_enable_connectionless_cte(uint8_t handle,
                                                            uint8_t cte_length,
                                                            uint8_t cte_type,
                                                            uint8_t cte_count,
                                                            size_t switching_pattern_len,
                                                            const uint8_t* switching_pattern) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_transmitter_enable_connectionless_cte.handle=handle;
    cmd->data.cmd_cte_transmitter_enable_connectionless_cte.cte_length=cte_length;
    cmd->data.cmd_cte_transmitter_enable_connectionless_cte.cte_type=cte_type;
    cmd->data.cmd_cte_transmitter_enable_connectionless_cte.cte_count=cte_count;
    if ((5+switching_pattern_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_cte_transmitter_enable_connectionless_cte.switching_pattern.len=switching_pattern_len;
    memcpy(cmd->data.cmd_cte_transmitter_enable_connectionless_cte.switching_pattern.data,switching_pattern,switching_pattern_len);

    cmd->header=sl_bt_cmd_cte_transmitter_enable_connectionless_cte_id+(((5+switching_pattern_len)&0xff)<<8)+(((5+switching_pattern_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_transmitter_enable_connectionless_cte.result;

}

sl_status_t sl_bt_cte_transmitter_disable_connectionless_cte(uint8_t handle) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_transmitter_disable_connectionless_cte.handle=handle;

    cmd->header=sl_bt_cmd_cte_transmitter_disable_connectionless_cte_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_transmitter_disable_connectionless_cte.result;

}

sl_status_t sl_bt_cte_transmitter_enable_silabs_cte(uint8_t handle,
                                                    uint8_t cte_length,
                                                    uint8_t cte_type,
                                                    uint8_t cte_count,
                                                    size_t switching_pattern_len,
                                                    const uint8_t* switching_pattern) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_transmitter_enable_silabs_cte.handle=handle;
    cmd->data.cmd_cte_transmitter_enable_silabs_cte.cte_length=cte_length;
    cmd->data.cmd_cte_transmitter_enable_silabs_cte.cte_type=cte_type;
    cmd->data.cmd_cte_transmitter_enable_silabs_cte.cte_count=cte_count;
    if ((5+switching_pattern_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_cte_transmitter_enable_silabs_cte.switching_pattern.len=switching_pattern_len;
    memcpy(cmd->data.cmd_cte_transmitter_enable_silabs_cte.switching_pattern.data,switching_pattern,switching_pattern_len);

    cmd->header=sl_bt_cmd_cte_transmitter_enable_silabs_cte_id+(((5+switching_pattern_len)&0xff)<<8)+(((5+switching_pattern_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_transmitter_enable_silabs_cte.result;

}

sl_status_t sl_bt_cte_transmitter_disable_silabs_cte(uint8_t handle) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_transmitter_disable_silabs_cte.handle=handle;

    cmd->header=sl_bt_cmd_cte_transmitter_disable_silabs_cte_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_transmitter_disable_silabs_cte.result;

}

sl_status_t sl_bt_cte_receiver_set_dtm_parameters(uint8_t cte_length,
                                                  uint8_t cte_type,
                                                  uint8_t slot_durations,
                                                  size_t switching_pattern_len,
                                                  const uint8_t* switching_pattern) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_receiver_set_dtm_parameters.cte_length=cte_length;
    cmd->data.cmd_cte_receiver_set_dtm_parameters.cte_type=cte_type;
    cmd->data.cmd_cte_receiver_set_dtm_parameters.slot_durations=slot_durations;
    if ((4+switching_pattern_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_cte_receiver_set_dtm_parameters.switching_pattern.len=switching_pattern_len;
    memcpy(cmd->data.cmd_cte_receiver_set_dtm_parameters.switching_pattern.data,switching_pattern,switching_pattern_len);

    cmd->header=sl_bt_cmd_cte_receiver_set_dtm_parameters_id+(((4+switching_pattern_len)&0xff)<<8)+(((4+switching_pattern_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_receiver_set_dtm_parameters.result;

}

sl_status_t sl_bt_cte_receiver_clear_dtm_parameters() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_cte_receiver_clear_dtm_parameters_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_receiver_clear_dtm_parameters.result;

}

sl_status_t sl_bt_cte_receiver_set_sync_cte_type(uint8_t sync_cte_type) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_receiver_set_sync_cte_type.sync_cte_type=sync_cte_type;

    cmd->header=sl_bt_cmd_cte_receiver_set_sync_cte_type_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_receiver_set_sync_cte_type.result;

}

sl_status_t sl_bt_cte_receiver_set_default_sync_receive_parameters(uint8_t mode,
                                                                   uint16_t skip,
                                                                   uint16_t timeout,
                                                                   uint8_t sync_cte_type,
                                                                   uint8_t reporting_mode) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_receiver_set_default_sync_receive_parameters.mode=mode;
    cmd->data.cmd_cte_receiver_set_default_sync_receive_parameters.skip=skip;
    cmd->data.cmd_cte_receiver_set_default_sync_receive_parameters.timeout=timeout;
    cmd->data.cmd_cte_receiver_set_default_sync_receive_parameters.sync_cte_type=sync_cte_type;
    cmd->data.cmd_cte_receiver_set_default_sync_receive_parameters.reporting_mode=reporting_mode;

    cmd->header=sl_bt_cmd_cte_receiver_set_default_sync_receive_parameters_id+(((7)&0xff)<<8)+(((7)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_receiver_set_default_sync_receive_parameters.result;

}

sl_status_t sl_bt_cte_receiver_set_sync_receive_parameters(uint8_t connection,
                                                           uint8_t mode,
                                                           uint16_t skip,
                                                           uint16_t timeout,
                                                           uint8_t sync_cte_type,
                                                           uint8_t reporting_mode) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_receiver_set_sync_receive_parameters.connection=connection;
    cmd->data.cmd_cte_receiver_set_sync_receive_parameters.mode=mode;
    cmd->data.cmd_cte_receiver_set_sync_receive_parameters.skip=skip;
    cmd->data.cmd_cte_receiver_set_sync_receive_parameters.timeout=timeout;
    cmd->data.cmd_cte_receiver_set_sync_receive_parameters.sync_cte_type=sync_cte_type;
    cmd->data.cmd_cte_receiver_set_sync_receive_parameters.reporting_mode=reporting_mode;

    cmd->header=sl_bt_cmd_cte_receiver_set_sync_receive_parameters_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_receiver_set_sync_receive_parameters.result;

}

sl_status_t sl_bt_cte_receiver_configure(uint8_t flags) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_receiver_configure.flags=flags;

    cmd->header=sl_bt_cmd_cte_receiver_configure_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_receiver_configure.result;

}

sl_status_t sl_bt_cte_receiver_enable_connection_cte(uint8_t connection,
                                                     uint16_t interval,
                                                     uint8_t cte_length,
                                                     uint8_t cte_type,
                                                     uint8_t slot_durations,
                                                     size_t switching_pattern_len,
                                                     const uint8_t* switching_pattern) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_receiver_enable_connection_cte.connection=connection;
    cmd->data.cmd_cte_receiver_enable_connection_cte.interval=interval;
    cmd->data.cmd_cte_receiver_enable_connection_cte.cte_length=cte_length;
    cmd->data.cmd_cte_receiver_enable_connection_cte.cte_type=cte_type;
    cmd->data.cmd_cte_receiver_enable_connection_cte.slot_durations=slot_durations;
    if ((7+switching_pattern_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_cte_receiver_enable_connection_cte.switching_pattern.len=switching_pattern_len;
    memcpy(cmd->data.cmd_cte_receiver_enable_connection_cte.switching_pattern.data,switching_pattern,switching_pattern_len);

    cmd->header=sl_bt_cmd_cte_receiver_enable_connection_cte_id+(((7+switching_pattern_len)&0xff)<<8)+(((7+switching_pattern_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_receiver_enable_connection_cte.result;

}

sl_status_t sl_bt_cte_receiver_disable_connection_cte(uint8_t connection) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_receiver_disable_connection_cte.connection=connection;

    cmd->header=sl_bt_cmd_cte_receiver_disable_connection_cte_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_receiver_disable_connection_cte.result;

}

sl_status_t sl_bt_cte_receiver_enable_connectionless_cte(uint16_t sync,
                                                         uint8_t slot_durations,
                                                         uint8_t cte_count,
                                                         size_t switching_pattern_len,
                                                         const uint8_t* switching_pattern) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_receiver_enable_connectionless_cte.sync=sync;
    cmd->data.cmd_cte_receiver_enable_connectionless_cte.slot_durations=slot_durations;
    cmd->data.cmd_cte_receiver_enable_connectionless_cte.cte_count=cte_count;
    if ((5+switching_pattern_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_cte_receiver_enable_connectionless_cte.switching_pattern.len=switching_pattern_len;
    memcpy(cmd->data.cmd_cte_receiver_enable_connectionless_cte.switching_pattern.data,switching_pattern,switching_pattern_len);

    cmd->header=sl_bt_cmd_cte_receiver_enable_connectionless_cte_id+(((5+switching_pattern_len)&0xff)<<8)+(((5+switching_pattern_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_receiver_enable_connectionless_cte.result;

}

sl_status_t sl_bt_cte_receiver_disable_connectionless_cte(uint16_t sync) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_receiver_disable_connectionless_cte.sync=sync;

    cmd->header=sl_bt_cmd_cte_receiver_disable_connectionless_cte_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_receiver_disable_connectionless_cte.result;

}

sl_status_t sl_bt_cte_receiver_enable_silabs_cte(uint8_t slot_durations,
                                                 uint8_t cte_count,
                                                 size_t switching_pattern_len,
                                                 const uint8_t* switching_pattern) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_receiver_enable_silabs_cte.slot_durations=slot_durations;
    cmd->data.cmd_cte_receiver_enable_silabs_cte.cte_count=cte_count;
    if ((3+switching_pattern_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_cte_receiver_enable_silabs_cte.switching_pattern.len=switching_pattern_len;
    memcpy(cmd->data.cmd_cte_receiver_enable_silabs_cte.switching_pattern.data,switching_pattern,switching_pattern_len);

    cmd->header=sl_bt_cmd_cte_receiver_enable_silabs_cte_id+(((3+switching_pattern_len)&0xff)<<8)+(((3+switching_pattern_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_receiver_enable_silabs_cte.result;

}

sl_status_t sl_bt_cte_receiver_disable_silabs_cte() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_cte_receiver_disable_silabs_cte_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_receiver_disable_silabs_cte.result;

}

sl_status_t sl_bt_connection_analyzer_start(uint32_t access_address,
                                            uint32_t crc_init,
                                            uint16_t interval,
                                            uint16_t supervision_timeout,
                                            uint8_t central_clock_accuracy,
                                            uint8_t central_phy,
                                            uint8_t peripheral_phy,
                                            uint8_t channel_selection_algorithm,
                                            uint8_t hop,
                                            const sl_bt_connection_channel_map_t *channel_map,
                                            uint8_t channel,
                                            uint16_t event_counter,
                                            int32_t start_time_us,
                                            uint32_t flags,
                                            uint8_t *analyzer) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_analyzer_start.access_address=access_address;
    cmd->data.cmd_connection_analyzer_start.crc_init=crc_init;
    cmd->data.cmd_connection_analyzer_start.interval=interval;
    cmd->data.cmd_connection_analyzer_start.supervision_timeout=supervision_timeout;
    cmd->data.cmd_connection_analyzer_start.central_clock_accuracy=central_clock_accuracy;
    cmd->data.cmd_connection_analyzer_start.central_phy=central_phy;
    cmd->data.cmd_connection_analyzer_start.peripheral_phy=peripheral_phy;
    cmd->data.cmd_connection_analyzer_start.channel_selection_algorithm=channel_selection_algorithm;
    cmd->data.cmd_connection_analyzer_start.hop=hop;
    memcpy(&cmd->data.cmd_connection_analyzer_start.channel_map,channel_map,sizeof(sl_bt_connection_channel_map_t));
    cmd->data.cmd_connection_analyzer_start.channel=channel;
    cmd->data.cmd_connection_analyzer_start.event_counter=event_counter;
    cmd->data.cmd_connection_analyzer_start.start_time_us=start_time_us;
    cmd->data.cmd_connection_analyzer_start.flags=flags;

    cmd->header=sl_bt_cmd_connection_analyzer_start_id+(((33)&0xff)<<8)+(((33)&0x700)>>8);


    sl_bt_host_handle_command();
    if (analyzer) {
        *analyzer = rsp->data.rsp_connection_analyzer_start.analyzer;
    }
    return rsp->data.rsp_connection_analyzer_start.result;

}

sl_status_t sl_bt_connection_analyzer_stop(uint8_t analyzer) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_analyzer_stop.analyzer=analyzer;

    cmd->header=sl_bt_cmd_connection_analyzer_stop_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_connection_analyzer_stop.result;

}

sl_status_t sl_bt_user_message_to_target(size_t data_len,
                                         const uint8_t* data,
                                         size_t max_response_size,
                                         size_t *response_len,
                                         uint8_t *response) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    if ((1+data_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_user_message_to_target.data.len=data_len;
    memcpy(cmd->data.cmd_user_message_to_target.data.data,data,data_len);

    cmd->header=sl_bt_cmd_user_message_to_target_id+(((1+data_len)&0xff)<<8)+(((1+data_len)&0x700)>>8);


    sl_bt_host_handle_command();
    if (response_len) {
        *response_len = rsp->data.rsp_user_message_to_target.response.len;
    }
    if (response && (rsp->data.rsp_user_message_to_target.response.len <= max_response_size)) {
        memcpy(response,rsp->data.rsp_user_message_to_target.response.data,rsp->data.rsp_user_message_to_target.response.len);
    }
    return rsp->data.rsp_user_message_to_target.result;

}

sl_status_t sl_bt_user_manage_event_filter(size_t data_len,
                                           const uint8_t* data) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    if ((1+data_len) > SL_BGAPI_MAX_PAYLOAD_SIZE )
    {
        return SL_STATUS_COMMAND_TOO_LONG;
    }
    cmd->data.cmd_user_manage_event_filter.data.len=data_len;
    memcpy(cmd->data.cmd_user_manage_event_filter.data.data,data,data_len);

    cmd->header=sl_bt_cmd_user_manage_event_filter_id+(((1+data_len)&0xff)<<8)+(((1+data_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_user_manage_event_filter.result;

}

void sl_bt_user_reset_to_dfu() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;


    cmd->header=sl_bt_cmd_user_reset_to_dfu_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command_noresponse();
}
