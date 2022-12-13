/***************************************************************************//**
 * @file app_settings.c
 * @brief Application settings handler
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sl_wisun_ip6string.h"
#include "nvm3.h"
#include "app_settings.h"
#include "sl_wisun_br_api.h"
#include "sl_default_phy.h"
#include "sl_wisun_cli_util.h"
#include "sl_wisun_types.h"
#include "rail_features.h"

#define APP_SETTINGS_WISUN_DEFAULT_NETWORK_NAME  "Wi-SUN Network"
#define APP_SETTINGS_WISUN_DEFAULT_NETWORK_SIZE  SL_WISUN_NETWORK_SIZE_SMALL
#define APP_SETTINGS_WISUN_DEFAULT_TX_POWER  20
#define APP_SETTINGS_WISUN_DEFAULT_UC_DWELL_INTERVAL  255
#define APP_SETTINGS_WISUN_DEFAULT_BC_INTERVAL  1020
#define APP_SETTINGS_WISUN_DEFAULT_BC_DWELL_INTERVAL  255
#define APP_SETTINGS_WISUN_DEFAULT_CH0_FREQUENCY  863100
#define APP_SETTINGS_WISUN_DEFAULT_NUMBER_OF_CHANNELS  69
#define APP_SETTINGS_WISUN_DEFAULT_CHANNEL_SPACING  SL_WISUN_CHANNEL_SPACING_100HZ
#define APP_SETTINGS_WISUN_CHANNEL_MASK_ALL  0xFFFFFFFF
#define APP_SETTINGS_WISUN_CHANNEL_MASK_NONE  0
#define APP_SETTINGS_WISUN_FIXED_CHANNEL_DISABLE  256
#define APP_SETTINGS_WISUN_DEFAULT_ALLOWED_CHANNELS  "0-255"
#define APP_SETTINGS_WISUN_DEFAULT_REGULATION  SL_WISUN_REGULATION_NONE
#define APP_SETTINGS_WISUN_DEFAULT_PHY_CONFIG_TYPE  SL_WISUN_PHY_CONFIG_FAN10
#define APP_SETTINGS_WISUN_DEFAULT_CHAN_PLAN_ID  1
#define APP_SETTINGS_WISUN_DEFAULT_PHY_MODE_ID  2

#ifndef APP_SETTINGS_APP_DEFAULT_AUTOSTART
# define APP_SETTINGS_APP_DEFAULT_AUTOSTART  false
#endif

typedef enum
{
  app_settings_domain_wisun       = 0x00,
  app_settings_domain_statistics  = 0x01,
  app_settings_domain_app         = 0x02
} app_settings_domain_t;

const char *app_settings_domain_str[] =
{
  "wisun",
  "statistics",
  "app",
  NULL,
};

typedef enum
{
  app_statistics_domain_phy        = 0x00,
  app_statistics_domain_mac        = 0x01,
  app_statistics_domain_fhss       = 0x02,
  app_statistics_domain_wisun      = 0x03,
  app_statistics_domain_network    = 0x04,
  app_statistics_domain_regulation = 0x05
} app_statistics_domain_t;

const char *app_statistics_domain_str[] =
{
  "phy",
  "mac",
  "fhss",
  "wisun",
  "network",
  "regulation",
  NULL,
};

static const app_settings_wisun_t app_settings_wisun_default = {
  .network_name = APP_SETTINGS_WISUN_DEFAULT_NETWORK_NAME,
  .regulatory_domain = APP_SETTINGS_WISUN_DEFAULT_REGULATORY_DOMAIN,
  .operating_class = APP_SETTINGS_WISUN_DEFAULT_OPERATING_CLASS,
  .operating_mode = APP_SETTINGS_WISUN_DEFAULT_OPERATING_MODE,
  .network_size = APP_SETTINGS_WISUN_DEFAULT_NETWORK_SIZE,
  .tx_power = APP_SETTINGS_WISUN_DEFAULT_TX_POWER,
  .uc_dwell_interval_ms = APP_SETTINGS_WISUN_DEFAULT_UC_DWELL_INTERVAL,
  .bc_interval_ms = APP_SETTINGS_WISUN_DEFAULT_BC_INTERVAL,
  .bc_dwell_interval_ms = APP_SETTINGS_WISUN_DEFAULT_BC_DWELL_INTERVAL,
  .state = SLI_WISUN_BR_TASK_STATE_UNINITIALIZED,
  .channel_spacing = APP_SETTINGS_WISUN_DEFAULT_CHANNEL_SPACING,
  .number_of_channels = APP_SETTINGS_WISUN_DEFAULT_NUMBER_OF_CHANNELS,
  .ch0_frequency = APP_SETTINGS_WISUN_DEFAULT_CH0_FREQUENCY,
  .allowed_channels = APP_SETTINGS_WISUN_DEFAULT_ALLOWED_CHANNELS,
  .trace_filter = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
  .regulation = APP_SETTINGS_WISUN_DEFAULT_REGULATION,
  .chan_plan_id = APP_SETTINGS_WISUN_DEFAULT_CHAN_PLAN_ID,
  .phy_mode_id = APP_SETTINGS_WISUN_DEFAULT_PHY_MODE_ID,
  .phy_config_type = APP_SETTINGS_WISUN_DEFAULT_PHY_CONFIG_TYPE
};

static const app_settings_app_t app_settings_app_default = {
  .printable_data_as_hex = false,
  .printable_data_length = APP_UTIL_PRINTABLE_DATA_MAX_LENGTH,
  .autostart = APP_SETTINGS_APP_DEFAULT_AUTOSTART,
  .pti_state = true
};

app_settings_wisun_t app_settings_wisun;
app_settings_app_t app_settings_app;

//static sl_wisun_statistics_t app_statistics;

const app_saving_item_t app_saving_item_wisun = {
  .data = &app_settings_wisun,
  .data_size = sizeof(app_settings_wisun),
  .default_val = &app_settings_wisun_default
};

const app_saving_item_t app_saving_item_app = {
  .data = &app_settings_app,
  .data_size = sizeof(app_settings_app),
  .default_val = &app_settings_app_default
};

const app_saving_item_t *saving_settings[] = {
  &app_saving_item_wisun,
  &app_saving_item_app,
  NULL
};

static sl_wisun_statistics_t app_statistics;

static const app_enum_t app_settings_wisun_phy_config_type_enum[] =
{
  { "FAN 1.0", SL_WISUN_PHY_CONFIG_FAN10 },
  { "FAN 1.1", SL_WISUN_PHY_CONFIG_FAN11 },
  { "explicit", SL_WISUN_PHY_CONFIG_EXPLICIT },
  { NULL, 0 }
};

static const app_enum_t app_settings_wisun_network_size_enum[] =
{
  { "automatic", SL_WISUN_NETWORK_SIZE_AUTOMATIC },
  { "small", SL_WISUN_NETWORK_SIZE_SMALL },
  { "medium", SL_WISUN_NETWORK_SIZE_MEDIUM },
  { "large", SL_WISUN_NETWORK_SIZE_LARGE },
  { "test", SL_WISUN_NETWORK_SIZE_TEST },
  { "certification", SL_WISUN_NETWORK_SIZE_CERTIFICATION },
  { NULL, 0 }
};

static const app_enum_t app_settings_wisun_reg_domain_enum[] =
{
  { "WW", SL_WISUN_REGULATORY_DOMAIN_WW },
  { "NA", SL_WISUN_REGULATORY_DOMAIN_NA },
  { "JP", SL_WISUN_REGULATORY_DOMAIN_JP },
  { "EU", SL_WISUN_REGULATORY_DOMAIN_EU },
  { "CN", SL_WISUN_REGULATORY_DOMAIN_CN },
  { "IN", SL_WISUN_REGULATORY_DOMAIN_IN },
  { "MX", SL_WISUN_REGULATORY_DOMAIN_MX },
  { "BZ", SL_WISUN_REGULATORY_DOMAIN_BZ },
  { "AZ/NZ", SL_WISUN_REGULATORY_DOMAIN_AZ },
  { "AZ", SL_WISUN_REGULATORY_DOMAIN_AZ },
  { "NZ", SL_WISUN_REGULATORY_DOMAIN_NZ },
  { "KR", SL_WISUN_REGULATORY_DOMAIN_KR },
  { "PH", SL_WISUN_REGULATORY_DOMAIN_PH },
  { "MY", SL_WISUN_REGULATORY_DOMAIN_MY },
  { "HK", SL_WISUN_REGULATORY_DOMAIN_HK },
  { "SG", SL_WISUN_REGULATORY_DOMAIN_SG },
  { "TH", SL_WISUN_REGULATORY_DOMAIN_TH },
  { "VN", SL_WISUN_REGULATORY_DOMAIN_VN },
  { "application", SL_WISUN_REGULATORY_DOMAIN_APP },
  { NULL, 0 }
};

static const app_enum_t app_settings_wisun_operating_class_enum[] =
{
  { "application", SL_WISUN_OPERATING_CLASS_APP },
  { NULL, 0 }
};

static const app_enum_t app_settings_wisun_br_state_enum[] =
{
  { "uninitialized", SLI_WISUN_BR_TASK_STATE_UNINITIALIZED },
  { "initialized", SLI_WISUN_BR_TASK_STATE_INITIALIZED },
  { "started", SLI_WISUN_BR_TASK_STATE_STARTED },
  { NULL, 0 }
};

static const app_enum_t app_settings_phy_channel_spacing_enum[] =
{
  { "100kHz", SL_WISUN_CHANNEL_SPACING_100KHZ },
  { "200kHz", SL_WISUN_CHANNEL_SPACING_200KHZ },
  { "400kHz", SL_WISUN_CHANNEL_SPACING_400KHZ },
  { "600kHz", SL_WISUN_CHANNEL_SPACING_600KHZ },
  { "250kHz", SL_WISUN_CHANNEL_SPACING_250KHZ },
  { "800kHz", SL_WISUN_CHANNEL_SPACING_800KHZ },
  { "1200kHz", SL_WISUN_CHANNEL_SPACING_1200KHZ },
  { NULL, 0 }
};

static const app_enum_t app_settings_wisun_regulation_enum[] =
{
  { "none", SL_WISUN_REGULATION_NONE },
  { "arib", SL_WISUN_REGULATION_ARIB },
  { NULL, 0 }
};

static sl_status_t app_settings_get_fan10_phy_config(char *value_str,
                                                     const char *key_str,
                                                     const app_settings_entry_t *entry);
static sl_status_t app_settings_get_fan11_phy_config(char *value_str,
                                                     const char *key_str,
                                                     const app_settings_entry_t *entry);
static sl_status_t app_settings_get_explicit_phy_config(char *value_str,
                                                        const char *key_str,
                                                        const app_settings_entry_t *entry);
static sl_status_t app_settings_get_fan10_and_fan11_phy_config(char *value_str,
                                                               const char *key_str,
                                                               const app_settings_entry_t *entry);
static sl_status_t app_settings_get_fan11_and_explicit_phy_config(char *value_str,
                                                                  const char *key_str,
                                                                  const app_settings_entry_t *entry);
static sl_status_t app_settings_get_gak(char *value_str,
                                        const char *key_str,
                                        const app_settings_entry_t *entry);
static sl_status_t app_settings_get_lfn_gak(char *value_str,
                                            const char *key_str,
                                            const app_settings_entry_t *entry);
static sl_status_t app_settings_get_mac_address(char *value_str,
                                                const char *key_str,
                                                const app_settings_entry_t *entry);
static sl_status_t app_settings_get_ip_addresses(char *value_str,
                                                 const char *key_str,
                                                 const app_settings_entry_t *entry);
static sl_status_t app_settings_get_statistics(char *value_str,
                                               const char *key_str,
                                               const app_settings_entry_t *entry);
static sl_status_t app_settings_get_statistics_regulation(char *value_str,
                                                          const char *key_str,
                                                          const app_settings_entry_t *entry);
static sl_status_t app_settings_get_state(char *value_str,
                                          const char *key_str,
                                          const app_settings_entry_t *entry);
static sl_status_t app_settings_get_channel_mask_str(char *value_str,
                                                     const char *key_str,
                                                     const app_settings_entry_t *entry);
static sl_status_t app_settings_set_allowed_channels(const char *value_str,
                                                     const char *key_str,
                                                     const app_settings_entry_t *entry);
static sl_status_t app_settings_set_trace_filter(const char *value_str,
                                                 const char *key_str,
                                                 const app_settings_entry_t *entry);
static sl_status_t app_settings_get_trace_filter(char *value_str,
                                                 const char *key_str,
                                                 const app_settings_entry_t *entry);
static sl_status_t app_settings_set_pti_state(const char *value_str,
                                              const char *key_str,
                                              const app_settings_entry_t *entry);
static sl_status_t app_settings_set_regulation(const char *value_str,
                                               const char *key_str,
                                               const app_settings_entry_t *entry);
#if RAIL_IEEE802154_SUPPORTS_G_MODESWITCH
static sl_status_t app_settings_set_rx_phy_mode_ids(const char *value_str,
                                                    const char *key_str,
                                                    const app_settings_entry_t *entry);
static sl_status_t app_settings_get_rx_phy_mode_ids(char *value_str,
                                                    const char *key_str,
                                                    const app_settings_entry_t *entry);
#endif

const app_settings_entry_t app_settings_entries[] =
{
  {
    .key = "state",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_NONE,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_settings_wisun.state,
    .input_enum_list = NULL,
    .output_enum_list = app_settings_wisun_br_state_enum,
    .set_handler = NULL,
    .get_handler = app_settings_get_state,
    .description = "Border router state"
  },
  {
    .key = "network_name",
    .domain = app_settings_domain_wisun,
    .value_size = SL_WISUN_NETWORK_NAME_SIZE+1,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_settings_wisun.network_name,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = app_settings_set_string,
    .get_handler = app_settings_get_string,
    .description = "Wi-SUN network [string] max 32"
  },
  {
    .key = "phy_config_type",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT8,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_settings_wisun.phy_config_type,
    .input_enum_list = NULL,
    .output_enum_list = app_settings_wisun_phy_config_type_enum,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "PHY configuration type (FAN 1.0|FAN 1.1|explicit)"
  },
  {
    .key = "regulatory_domain",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT8,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_settings_wisun.regulatory_domain,
    .input_enum_list = app_settings_wisun_reg_domain_enum,
    .output_enum_list = app_settings_wisun_reg_domain_enum,
    .set_handler = app_settings_set_integer,
    .get_handler = app_settings_get_fan10_and_fan11_phy_config,
    .description = "Wi-SUN regulatory domain [uint8]"
  },
  {
    .key = "operating_class",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT8,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_settings_wisun.operating_class,
    .input_enum_list = app_settings_wisun_operating_class_enum,
    .output_enum_list = app_settings_wisun_operating_class_enum,
    .set_handler = app_settings_set_integer,
    .get_handler = app_settings_get_fan10_phy_config,
    .description = "Wi-SUN operation class [uint8]"
  },
  {
    .key = "operating_mode",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT16,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT | APP_SETTINGS_OUTPUT_FLAG_HEX,
    .value = &app_settings_wisun.operating_mode,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = app_settings_set_integer,
    .get_handler = app_settings_get_fan10_phy_config,
    .description = "Wi-SUN operating mode [uint16]"
  },
  {
    .key = "fec",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT8,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_settings_wisun.fec,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = app_settings_set_integer,
    .get_handler = app_settings_get_fan10_phy_config,
    .description = "1 to use FEC, 0 otherwise [bool] (0|1)"
  },
  {
    .key = "chan_plan_id",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT8,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_settings_wisun.chan_plan_id,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = app_settings_set_integer,
    .get_handler = app_settings_get_fan11_phy_config,
    .description = "Wi-SUN channel plan ID [uint8]"
  },
  {
    .key = "phy_mode_id",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT8,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_settings_wisun.phy_mode_id,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = app_settings_set_integer,
    .get_handler = app_settings_get_fan11_and_explicit_phy_config,
    .description = "Wi-SUN PHY mode ID [uint8]"
  },
  {
    .key = "ch0_frequency",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_settings_wisun.ch0_frequency,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = app_settings_set_integer,
    .get_handler = app_settings_get_explicit_phy_config,
    .description = "Ch0 frequency in kHz [uint32]"
  },
  {
    .key = "number_of_channels",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT16,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_settings_wisun.number_of_channels,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = app_settings_set_integer,
    .get_handler = app_settings_get_explicit_phy_config,
    .description = "Number of channels [uint16]"
  },
  {
    .key = "channel_spacing",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT8,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_settings_wisun.channel_spacing,
    .input_enum_list = app_settings_phy_channel_spacing_enum,
    .output_enum_list = app_settings_phy_channel_spacing_enum,
    .set_handler = app_settings_set_integer,
    .get_handler = app_settings_get_explicit_phy_config,
    .description = "Channel spacing [string] (100kHz|200kHz|400kHz|600kHz|250kHz|800kHz|1200kHz)"
  },
  {
    .key = "network_size",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT8,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_settings_wisun.network_size,
    .input_enum_list = app_settings_wisun_network_size_enum,
    .output_enum_list = app_settings_wisun_network_size_enum,
    .set_handler = app_settings_set_integer,
    .get_handler = app_settings_get_integer,
    .description = "Wi-SUN network size [uint8]"
  },
  {
    .key = "tx_power",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT8,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT | APP_SETTINGS_INPUT_FLAG_SIGNED,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT | APP_SETTINGS_OUTPUT_FLAG_SIGNED,
    .value = &app_settings_wisun.tx_power,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = app_settings_set_integer,
    .get_handler = app_settings_get_integer,
    .description = "TX power in dBm [uint8]"
  },
  {
    .key = "unicast_dwell_interval",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT8,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_settings_wisun.uc_dwell_interval_ms,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = app_settings_set_integer,
    .get_handler = app_settings_get_integer,
    .description = "Unicast dwell interval in ms [uint8]"
  },
  {
    .key = "broadcast_interval",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_settings_wisun.bc_interval_ms,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = app_settings_set_integer,
    .get_handler = app_settings_get_integer,
    .description = "Broadcast interval in ms [uint32]"
  },
  {
    .key = "broadcast_dwell_interval",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT8,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_settings_wisun.bc_dwell_interval_ms,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = app_settings_set_integer,
    .get_handler = app_settings_get_integer,
    .description = "Broadcast dwell interval in ms [uint8]"
  },
  {
    .key = "channel_mask",
    .domain = app_settings_domain_wisun,
    .value_size = APP_UTIL_PRINTABLE_DATA_MAX_LENGTH+1,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = app_settings_wisun.allowed_channels,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_channel_mask_str,
    .description = "Excluded channel mask"
  },
  {
    .key = "allowed_channels",
    .domain = app_settings_domain_wisun,
    .value_size = APP_UTIL_PRINTABLE_DATA_MAX_LENGTH+1,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = app_settings_wisun.allowed_channels,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = app_settings_set_allowed_channels,
    .get_handler = app_settings_get_string,
    .description = "Allowed channel ranges (e.g. 0-54,57-60,64,67-68)"
  },
  {
    .key = "gak1",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_NONE,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = app_settings_wisun.gak[0],
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_gak,
    .description = "GAK derived from GTK1 [string]"
  },
  {
    .key = "gak2",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_NONE,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = app_settings_wisun.gak[1],
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_gak,
    .description = "GAK derived from GTK2 [string]"
  },
  {
    .key = "gak3",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_NONE,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = app_settings_wisun.gak[2],
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_gak,
    .description = "GAK derived from GTK3 [string]"
  },
  {
    .key = "gak4",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_NONE,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = app_settings_wisun.gak[3],
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_gak,
    .description = "GAK derived from GTK4 [string]"
  },
  {
    .key = "lfn_gak1",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_NONE,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = app_settings_wisun.lfn_gak[0],
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_lfn_gak,
    .description = "GAK derived from LGTK1 [string]"
  },
  {
    .key = "lfn_gak2",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_NONE,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = app_settings_wisun.lfn_gak[1],
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_lfn_gak,
    .description = "GAK derived from LGTK2 [string]"
  },
  {
    .key = "lfn_gak3",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_NONE,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = app_settings_wisun.lfn_gak[2],
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_lfn_gak,
    .description = "GAK derived from LGTK3 [string]"
  },
  {
    .key = "mac_address",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_NONE,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = NULL,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_mac_address,
    .description = "MAC address (EUI-64)"
  },
  {
    .key = "ip_addresses",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_NONE,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = NULL,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_ip_addresses,
    .description = "IPv6 addresses"
  },
  {
    .key = "phy",
    .domain = app_settings_domain_statistics,
    .value_size = APP_SETTINGS_VALUE_SIZE_NONE,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = (void *)SL_WISUN_STATISTICS_TYPE_PHY,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_statistics,
    .description = "PHY statistics and errors"
  },
  {
    .key = "mac",
    .domain = app_settings_domain_statistics,
    .value_size = APP_SETTINGS_VALUE_SIZE_NONE,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = (void *)SL_WISUN_STATISTICS_TYPE_MAC,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_statistics,
    .description = "MAC statistics and errors"
  },
  {
    .key = "fhss",
    .domain = app_settings_domain_statistics,
    .value_size = APP_SETTINGS_VALUE_SIZE_NONE,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = (void *)SL_WISUN_STATISTICS_TYPE_FHSS,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_statistics,
    .description = "FHSS statistics and errors"
  },
  {
    .key = "wisun",
    .domain = app_settings_domain_statistics,
    .value_size = APP_SETTINGS_VALUE_SIZE_NONE,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = (void *)SL_WISUN_STATISTICS_TYPE_WISUN,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_statistics,
    .description = "Wi-SUN statistics and errors"
  },
  {
    .key = "network",
    .domain = app_settings_domain_statistics,
    .value_size = APP_SETTINGS_VALUE_SIZE_NONE,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = (void *)SL_WISUN_STATISTICS_TYPE_NETWORK,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_statistics,
    .description = "Network statistics and errors"
  },
  {
    .key = "regulation",
    .domain = app_settings_domain_statistics,
    .value_size = APP_SETTINGS_VALUE_SIZE_NONE,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = (void *)SL_WISUN_STATISTICS_TYPE_REGULATION,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_statistics_regulation,
    .description = "Regional regulation statistics and errors"
  },
  {
    .key = "printable_data_as_hex",
    .domain = app_settings_domain_app,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT8,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_settings_app.printable_data_as_hex,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = app_settings_set_integer,
    .get_handler = app_settings_get_integer,
    .description = "Print socket data as hex [bool] (0|1)"
  },
  {
    .key = "printable_data_length",
    .domain = app_settings_domain_app,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT8,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_settings_app.printable_data_length,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = app_settings_set_integer,
    .get_handler = app_settings_get_integer,
    .description = "Socket data line length [uint8]"
  },
  {
    .key = "autostart",
    .domain = app_settings_domain_app,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT8,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_settings_app.autostart,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = app_settings_set_integer,
    .get_handler = app_settings_get_integer,
    .description = "Disable or enable autostart [bool] (0|1)"
  },
  {
    .key = "pti_state",
    .domain = app_settings_domain_app,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT8,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_settings_app.pti_state,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = app_settings_set_pti_state,
    .get_handler = app_settings_get_integer,
    .description = "Disable or enable PTI [bool] (0|1)"
  },
  {
    .key = "trace_filter",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_NONE,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = NULL,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = app_settings_set_trace_filter,
    .get_handler = app_settings_get_trace_filter,
    .description = "Trace filter group list, 1 bit per group"
  },
  {
    .key = "regulation",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT8,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_settings_wisun.regulation,
    .input_enum_list = app_settings_wisun_regulation_enum,
    .output_enum_list = app_settings_wisun_regulation_enum,
    .set_handler = app_settings_set_regulation,
    .get_handler = app_settings_get_integer,
    .description = "Regional regulation [uint8]"
  },
#if RAIL_IEEE802154_SUPPORTS_G_MODESWITCH
  {
    .key = "rx_phy_mode_ids_count",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT8,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_settings_wisun.rx_phy_mode_ids_count,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = NULL,
    .description = "Number of PhyModeId configured"
  },
  {
    .key = "rx_phy_mode_ids",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT8,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_settings_wisun.rx_phy_mode_ids,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = app_settings_set_rx_phy_mode_ids,
    .get_handler = app_settings_get_rx_phy_mode_ids,
    .description = "List of PhyModeId to advertise in POM-IE"
  },
#endif
  {
    .key = NULL,
    .domain = 0,
    .value_size = APP_SETTINGS_VALUE_SIZE_NONE,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = NULL,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = NULL
  }
};

static const app_settings_entry_t app_trace_filter_entries[] = {
  {
    .key = "000-031",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT | APP_SETTINGS_OUTPUT_FLAG_HEX | APP_SETTINGS_OUTPUT_FLAG_FIXEDSIZE,
    .value = &app_settings_wisun.trace_filter[0],
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = app_settings_set_integer,
    .get_handler = app_settings_get_integer,
    .description = "Trace filter bitfield 000-031 [uint32]"
  },
  {
    .key = "032-063",
    .domain = app_settings_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT | APP_SETTINGS_OUTPUT_FLAG_HEX | APP_SETTINGS_OUTPUT_FLAG_FIXEDSIZE,
    .value = &app_settings_wisun.trace_filter[4],
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = app_settings_set_integer,
    .get_handler = app_settings_get_integer,
    .description = "Trace filter bitfield 032-063 [uint32]"
  },
  {
    .key = NULL,
    .domain = 0,
    .value_size = APP_SETTINGS_VALUE_SIZE_NONE,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = NULL,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = NULL,
    .description = NULL
  }
};

static const app_settings_entry_t app_statistics_entries[] =
{
  {
    .key = "crc_fails",
    .domain = app_statistics_domain_phy,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.phy.crc_fails,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Crc fails"
  },
  {
    .key = "tx_timeouts",
    .domain = app_statistics_domain_phy,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.phy.tx_timeouts,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Tx timeouts"
  },
  {
    .key = "rx_timeouts",
    .domain = app_statistics_domain_phy,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.phy.rx_timeouts,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Rx timeouts"
  },
  {
    .key = "tx_queue_size",
    .domain = app_statistics_domain_mac,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT16,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.mac.tx_queue_size,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Tx queue size"
  },
  {
    .key = "tx_queue_peak",
    .domain = app_statistics_domain_mac,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT16,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.mac.tx_queue_peak,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Tx queue peak"
  },
#if defined(SL_CATALOG_WISUN_MODE_SWITCH_PRESENT)
  {
    .key = "rx_ms_count",
    .domain = app_statistics_domain_mac,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.mac.rx_ms_count,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Rx count using mode switch"
  },
  {
    .key = "tx_ms_count",
    .domain = app_statistics_domain_mac,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.mac.tx_ms_count,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Tx count using mode switch"
  },
  {
    .key = "rx_ms_failed",
    .domain = app_statistics_domain_mac,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.mac.rx_ms_failed_count,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Rx failed count using mode switch"
  },
  {
    .key = "tx_ms_failed",
    .domain = app_statistics_domain_mac,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.mac.tx_ms_failed_count,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Tx failed count using mode switch"
  },
#endif
  {
    .key = "rx_count",
    .domain = app_statistics_domain_mac,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.mac.rx_count,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Rx count"
  },
  {
    .key = "tx_count",
    .domain = app_statistics_domain_mac,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.mac.tx_count,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Tx count"
  },
  {
    .key = "bc_rx_count",
    .domain = app_statistics_domain_mac,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.mac.bc_rx_count,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Bc rx count"
  },
  {
    .key = "bc_tx_count",
    .domain = app_statistics_domain_mac,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.mac.bc_tx_count,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Bc tx count"
  },
  {
    .key = "rx_drop_count",
    .domain = app_statistics_domain_mac,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.mac.rx_drop_count,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Rx drop count"
  },
  {
    .key = "tx_bytes",
    .domain = app_statistics_domain_mac,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.mac.tx_bytes,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Tx bytes"
  },
  {
    .key = "rx_bytes",
    .domain = app_statistics_domain_mac,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.mac.rx_bytes,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Rx bytes"
  },
  {
    .key = "tx_failed_count",
    .domain = app_statistics_domain_mac,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.mac.tx_failed_count,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Tx failed count"
  },
  {
    .key = "retry_count",
    .domain = app_statistics_domain_mac,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.mac.retry_count,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Retry count"
  },
  {
    .key = "cca_attempts_count",
    .domain = app_statistics_domain_mac,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.mac.cca_attempts_count,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Cca attempts count"
  },
  {
    .key = "failed_cca_count",
    .domain = app_statistics_domain_mac,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.mac.failed_cca_count,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Failed cca count"
  },
  {
    .key = "drift_compensation",
    .domain = app_statistics_domain_fhss,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT16,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT | APP_SETTINGS_INPUT_FLAG_SIGNED,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT | APP_SETTINGS_OUTPUT_FLAG_SIGNED,
    .value = &app_statistics.fhss.drift_compensation,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Drift compensation"
  },
  {
    .key = "hop_count",
    .domain = app_statistics_domain_fhss,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT16,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.fhss.hop_count,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Hop count"
  },
  {
    .key = "synch_interval",
    .domain = app_statistics_domain_fhss,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT16,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.fhss.synch_interval,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Synch interval"
  },
  {
    .key = "prev_avg_synch_fix",
    .domain = app_statistics_domain_fhss,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT16,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT | APP_SETTINGS_INPUT_FLAG_SIGNED,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT | APP_SETTINGS_OUTPUT_FLAG_SIGNED,
    .value = &app_statistics.fhss.prev_avg_synch_fix,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Prev avf synch fix"
  },
  {
    .key = "synch_lost",
    .domain = app_statistics_domain_fhss,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.fhss.synch_lost,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Synch lost"
  },
  {
    .key = "unknown_neighbor",
    .domain = app_statistics_domain_fhss,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.fhss.unknown_neighbor,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Unknown neighbor"
  },
  {
    .key = "synch_lost",
    .domain = app_statistics_domain_fhss,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.fhss.channel_retry,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Synch lost"
  },
  {
    .key = "pan_control_rx_count",
    .domain = app_statistics_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.wisun.pan_control_rx_count,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "PAN control rx count"
  },
  {
    .key = "pan_control_tx_count",
    .domain = app_statistics_domain_wisun,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.wisun.pan_control_tx_count,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "PAN control tx count"
  },
  {
    .key = "ip_rx_count",
    .domain = app_statistics_domain_network,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.network.ip_rx_count,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Ip rx count"
  },
  {
    .key = "ip_tx_count",
    .domain = app_statistics_domain_network,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.network.ip_tx_count,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Ip tx count"
  },
  {
    .key = "ip_rx_drop",
    .domain = app_statistics_domain_network,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.network.ip_rx_drop,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Ip rx drop"
  },
  {
    .key = "ip_cksum_error",
    .domain = app_statistics_domain_network,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.network.ip_cksum_error,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Ip cksum error"
  },
  {
    .key = "ip_tx_bytes",
    .domain = app_statistics_domain_network,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.network.ip_tx_bytes,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Ip tx bytes"
  },
  {
    .key = "ip_rx_bytes",
    .domain = app_statistics_domain_network,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.network.ip_rx_bytes,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Ip rx bytes"
  },
  {
    .key = "ip_routed_up",
    .domain = app_statistics_domain_network,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.network.ip_routed_up,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Ip routed up"
  },
  {
    .key = "ip_no_route",
    .domain = app_statistics_domain_network,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.network.ip_no_route,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Ip no route"
  },
  {
    .key = "frag_rx_errors",
    .domain = app_statistics_domain_network,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.network.frag_rx_errors,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Frag rx errors"
  },
  {
    .key = "frag_tx_errors",
    .domain = app_statistics_domain_network,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.network.frag_tx_errors,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Frag tx errors"
  },
  {
    .key = "rpl_route_routecost_better_change",
    .domain = app_statistics_domain_network,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.network.rpl_route_routecost_better_change,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Rpl route routecost better change"
  },
  {
    .key = "ip_routeloop_detect",
    .domain = app_statistics_domain_network,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.network.ip_routeloop_detect,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Ip routeloop detect"
  },
  {
    .key = "rpl_memory_overflow",
    .domain = app_statistics_domain_network,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.network.rpl_memory_overflow,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Rpl memory overflow"
  },
  {
    .key = "rpl_parent_tx_fail",
    .domain = app_statistics_domain_network,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.network.rpl_parent_tx_fail,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Rpl parent tx fail"
  },
  {
    .key = "rpl_unknown_instance",
    .domain = app_statistics_domain_network,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.network.rpl_unknown_instance,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Rpl unknown instance"
  },
  {
    .key = "rpl_local_repair",
    .domain = app_statistics_domain_network,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.network.rpl_local_repair,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Rpl local repair"
  },
  {
    .key = "rpl_global_repair",
    .domain = app_statistics_domain_network,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.network.rpl_global_repair,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Rpl global repair"
  },
  {
    .key = "rpl_malformed_message",
    .domain = app_statistics_domain_network,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.network.rpl_malformed_message,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Rpl malformed message"
  },
  {
    .key = "rpl_time_no_next_hop",
    .domain = app_statistics_domain_network,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.network.rpl_time_no_next_hop,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Rpl time no next hop"
  },
  {
    .key = "rpl_total_memory",
    .domain = app_statistics_domain_network,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.network.rpl_total_memory,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Rpl total memory"
  },
  {
    .key = "buf_alloc",
    .domain = app_statistics_domain_network,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.network.buf_alloc,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Buf alloc"
  },
  {
    .key = "buf_headroom_realloc",
    .domain = app_statistics_domain_network,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.network.buf_headroom_realloc,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Buf headroom realloc"
  },
  {
    .key = "buf_headroom_shuffle",
    .domain = app_statistics_domain_network,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.network.buf_headroom_shuffle,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Buf headroom shuffle"
  },
  {
    .key = "buf_headroom_fail",
    .domain = app_statistics_domain_network,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.network.buf_headroom_fail,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Buf headroom fail"
  },
  {
    .key = "etx_1st_parent",
    .domain = app_statistics_domain_network,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT16,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.network.etx_1st_parent,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Etx 1st parent"
  },
  {
    .key = "etx_2nd_parent",
    .domain = app_statistics_domain_network,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT16,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.network.etx_2nd_parent,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Etx 2nd parent"
  },
  {
    .key = "adapt_layer_tx_queue_size",
    .domain = app_statistics_domain_network,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT16,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.network.adapt_layer_tx_queue_size,
    .input_enum_list =  NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Adapt layer tx queue size"
  },
  {
    .key = "adapt_layer_tx_queue_peak",
    .domain = app_statistics_domain_network,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT16,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.network.adapt_layer_tx_queue_peak,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Adapt layer tx queue peak"
  },
  {
    .key = "tx_duration_ms",
    .domain = app_statistics_domain_regulation,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = &app_statistics.regulation.arib.tx_duration_ms,
    .input_enum_list = (void *)SL_WISUN_REGULATION_ARIB,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_integer,
    .description = "Total transmission duration during last hour in milliseconds"
  },
  {
    .key = NULL,
    .domain = 0,
    .value_size = APP_SETTINGS_VALUE_SIZE_NONE,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = NULL,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = NULL,
    .description = NULL
  }
};

static sl_status_t app_settings_get_phy_config(char *value_str,
                                               const char *key_str,
                                               const app_settings_entry_t *entry,
                                               bool unused)
{
  sl_status_t status;

  status = app_settings_get_integer(value_str, key_str, entry);
  if (status == SL_STATUS_OK && unused) {
    strcat(value_str, " (unused)");
  }

  return status;
}

static sl_status_t app_settings_get_fan10_phy_config(char *value_str,
                                                     const char *key_str,
                                                     const app_settings_entry_t *entry)
{
  bool used = app_settings_wisun.phy_config_type == SL_WISUN_PHY_CONFIG_FAN10;
  return app_settings_get_phy_config(value_str, key_str, entry, !used);
}

static sl_status_t app_settings_get_fan11_phy_config(char *value_str,
                                                     const char *key_str,
                                                     const app_settings_entry_t *entry)
{
  bool used = app_settings_wisun.phy_config_type == SL_WISUN_PHY_CONFIG_FAN11;
  return app_settings_get_phy_config(value_str, key_str, entry, !used);
}

static sl_status_t app_settings_get_explicit_phy_config(char *value_str,
                                                        const char *key_str,
                                                        const app_settings_entry_t *entry)
{
  bool used = app_settings_wisun.phy_config_type == SL_WISUN_PHY_CONFIG_EXPLICIT;
  return app_settings_get_phy_config(value_str, key_str, entry, !used);
}

static sl_status_t app_settings_get_fan10_and_fan11_phy_config(char *value_str,
                                                               const char *key_str,
                                                               const app_settings_entry_t *entry)
{
  bool used = app_settings_wisun.phy_config_type == SL_WISUN_PHY_CONFIG_FAN10
           || app_settings_wisun.phy_config_type == SL_WISUN_PHY_CONFIG_FAN11;
  return app_settings_get_phy_config(value_str, key_str, entry, !used);
}

static sl_status_t app_settings_get_fan11_and_explicit_phy_config(char *value_str,
                                                                  const char *key_str,
                                                                  const app_settings_entry_t *entry)
{
  bool used = app_settings_wisun.phy_config_type == SL_WISUN_PHY_CONFIG_FAN11
           || app_settings_wisun.phy_config_type == SL_WISUN_PHY_CONFIG_EXPLICIT;
  return app_settings_get_phy_config(value_str, key_str, entry, !used);
}

static sl_status_t app_settings_get_gak(char *value_str,
                                        const char *key_str,
                                        const app_settings_entry_t *entry)
{
  (void)key_str;

  sli_wisun_br_task_state_t state;
  uint8_t *gak = (uint8_t *) entry->value;
  uint16_t key_index;
  int ret;

  if(!sl_wisun_br_get_state(&state) && state != SLI_WISUN_BR_TASK_STATE_STARTED) {
    return SL_STATUS_FAIL;
  }

  ret = sscanf(entry->key, "gak%hu", &key_index);

  sl_wisun_br_get_gak(key_index-1, gak);

  sprintf(value_str, "%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x",
          *gak,        *(gak + 1),  *(gak + 2),  *(gak + 3),
          *(gak + 4),  *(gak + 5),  *(gak + 6),  *(gak + 7),
          *(gak + 8),  *(gak + 9),  *(gak + 10), *(gak + 11),
          *(gak + 12), *(gak + 13), *(gak + 14), *(gak + 15));

  if (ret == 1) {
    return SL_STATUS_OK;
  } else {
    return SL_STATUS_FAIL;
  }
}

static sl_status_t app_settings_get_lfn_gak(char *value_str,
                                            const char *key_str,
                                            const app_settings_entry_t *entry)
{
  (void)key_str;

  sli_wisun_br_task_state_t state;
  uint8_t *gak = (uint8_t *) entry->value;
  uint16_t key_index;
  int ret;

  if(!sl_wisun_br_get_state(&state) && state != SLI_WISUN_BR_TASK_STATE_STARTED) {
    return SL_STATUS_FAIL;
  }

  ret = sscanf(entry->key, "lfn_gak%hu", &key_index);

  sl_wisun_br_get_gak(key_index-1 + 4, gak);

  sprintf(value_str, "%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x",
          *gak,        *(gak + 1),  *(gak + 2),  *(gak + 3),
          *(gak + 4),  *(gak + 5),  *(gak + 6),  *(gak + 7),
          *(gak + 8),  *(gak + 9),  *(gak + 10), *(gak + 11),
          *(gak + 12), *(gak + 13), *(gak + 14), *(gak + 15));

  if (ret == 1) {
    return SL_STATUS_OK;
  } else {
    return SL_STATUS_FAIL;
  }
}

static sl_status_t app_settings_get_mac_address(char *value_str,
                                                const char *key_str,
                                                const app_settings_entry_t *entry)
{
  sl_status_t ret;
  sl_wisun_mac_address_t address;
  (void)key_str;
  (void)entry;

  ret = sl_wisun_br_get_mac_address(&address);
  if (ret == SL_STATUS_OK) {
    ret = app_util_get_mac_address_string(value_str, &address);
  }

  return ret;
}

static sl_status_t app_settings_get_ip_addresses(char *value_str,
                                                 const char *key_str,
                                                 const app_settings_entry_t *entry)
{
  uint8_t addr_ll[16], addr_gua[16], addr_dodagid[16];
  char str_ll[128], str_gua[128], str_dodagid[128];

  int count;
  (void)key_str;
  (void)entry;

  count = sprintf(value_str, "[");
  value_str += count;

  sl_wisun_br_get_ip_addresses(addr_ll, addr_gua, addr_dodagid);
  ip6tos(addr_ll, str_ll);
  ip6tos(addr_gua, str_gua);
  ip6tos(addr_dodagid, str_dodagid);

  count = sprintf(value_str,"ll: %s gua: %s dodagid: %s", str_ll, str_gua, str_dodagid);
  value_str += count;

  count = sprintf(value_str, "]");
  value_str += count;

  return SL_STATUS_OK;
}

static sl_status_t app_settings_get_state(char *value_str,
                                          const char *key_str,
                                          const app_settings_entry_t *entry)
{
  (void)key_str;

  sli_wisun_br_task_state_t state;
  uint8_t value_length = sizeof(sli_wisun_br_task_state_t);

  sl_wisun_br_get_state(&state);

  return app_util_get_string(value_str,
                             state,
                             entry->output_enum_list,
                             false,
                             false,
                             value_length);
}

static sl_status_t app_settings_get_statistics(char *value_str,
                                               const char *key_str,
                                               const app_settings_entry_t *entry)
{
  sl_status_t ret;
  const app_settings_entry_t *iter;
  sl_wisun_statistics_type_t statistics_type;

  // API statistics type is stored in the settings entry value.
  #ifdef __GNUC__
  statistics_type = (sl_wisun_statistics_type_t) entry->value;
  #elif defined __ICCARM__
  statistics_type = (sl_wisun_statistics_type_t)((uint32_t) entry->value & 0xFF);
  #endif

  // Update statistics
  ret = sl_wisun_br_get_statistics(statistics_type, &app_statistics);
  if (ret != SL_STATUS_OK) {
    printf("[Failed to retrieve statistics: %lu]\r\n", ret);
    return SL_STATUS_FAIL;
  }

  iter = app_statistics_entries;
  while (iter->key) {
    if (!strcmp(entry->key, app_statistics_domain_str[iter->domain])) {
      if (!key_str || !strcmp(iter->key, key_str)) {
        if (iter->get_handler) {
          ret = iter->get_handler(value_str, NULL, iter);
          if (ret == SL_STATUS_OK) {
            printf("%s.%s.%s = %s\r\n", app_settings_domain_str[entry->domain], app_statistics_domain_str[iter->domain], iter->key, value_str);
          }
        }
      }
    }
    iter++;
  }

  // Prevent parent from printing anything
  return SL_STATUS_FAIL;
}

static sl_status_t app_settings_get_statistics_regulation(char *value_str,
                                                          const char *key_str,
                                                          const app_settings_entry_t *entry)
{
  sl_status_t ret;
  const app_settings_entry_t *iter;

  // Update statistics
  ret = sl_wisun_br_get_statistics(SL_WISUN_STATISTICS_TYPE_REGULATION, &app_statistics);
  if (ret != SL_STATUS_OK) {
    return ret;
  }

  iter = app_statistics_entries;
  while (iter->key) {
    if (!strcmp(entry->key, app_statistics_domain_str[iter->domain])) {
      // Associated regional regulation is coded in input_enum_list.
      if (app_settings_wisun.regulation == (sl_wisun_regulation_t)iter->input_enum_list) {
        if (!key_str || !strcmp(iter->key, key_str)) {
          if (iter->get_handler) {
            ret = iter->get_handler(value_str, NULL, iter);
            if (ret == SL_STATUS_OK) {
              printf("%s.%s.%s = %s\r\n", app_settings_domain_str[entry->domain], app_statistics_domain_str[iter->domain], iter->key, value_str);
            }
          }
        }
      }
    }
    iter++;
  }

  // Prevent parent from printing anything
  return SL_STATUS_FAIL;
}

static sl_status_t app_ranges_to_mask(const char *str, uint8_t *mask, uint32_t size)
{
  char *endptr;
  uint32_t cur, end, index;
  memset(mask, 0, size * sizeof(uint8_t));
  do {
    if (*str == '\0') {
      return SL_STATUS_FAIL;
    }
    cur = strtoul(str, &endptr, 0);
    if (*endptr == '-') {
      str = endptr + 1;
      end = strtoul(str, &endptr, 0);
    } else {
      end = cur;
    }
    if (*endptr != '\0' && *endptr != ',') {
      return SL_STATUS_FAIL;
    }
    if (cur > end) {
      return SL_STATUS_FAIL;
    }
    for (; cur <= end; cur++) {
      index = cur / 8;
      if (index < size) {
        mask[index] |= 1 << (cur % 8);
      } else {
        return SL_STATUS_FAIL;
      }
    }
    str = endptr + 1;
  } while (*endptr != '\0');

  return SL_STATUS_OK;
}

sl_status_t app_settings_get_channel_mask(const char *str, sl_wisun_channel_mask_t *channel_mask)
{
  return app_ranges_to_mask(str, channel_mask->mask, SL_WISUN_CHANNEL_MASK_SIZE);
}

static sl_status_t app_settings_get_channel_mask_str(char *value_str,
                                                     const char *key_str,
                                                     const app_settings_entry_t *entry)
{
  sl_status_t ret;
  sl_wisun_channel_mask_t channel_mask;
  int index, end;
  (void)key_str;

  ret = app_settings_get_channel_mask(entry->value, &channel_mask);
  if (ret == SL_STATUS_OK) {
    // Flip bits to get excluded channel mask.
    for (index = 0; index < SL_WISUN_CHANNEL_MASK_SIZE; index++) {
      channel_mask.mask[index] = channel_mask.mask[index] ^ 0xFF;
    }
    // Look for first byte different of 0xFF starting from the end.
    for (end = SL_WISUN_CHANNEL_MASK_SIZE - 1; end >= 0; end--) {
      if (channel_mask.mask[end] != 0xFF) {
        break;
      }
    }
    sprintf(value_str, "%02x", channel_mask.mask[0]);
    value_str += 2;
    for (index = 1; index <= end; index++) {
      sprintf(value_str, ":%02x", channel_mask.mask[index]);
      value_str += 3;
    }
  }

  return ret;
}

static sl_status_t app_settings_set_allowed_channels(const char *value_str,
                                                     const char *key_str,
                                                     const app_settings_entry_t *entry)
{
  sl_status_t ret;
  (void)key_str;
  (void)entry;
  sl_wisun_channel_mask_t channel_mask;

  ret = app_settings_get_channel_mask(value_str, &channel_mask);
  if (ret == SL_STATUS_OK) {
    ret = app_settings_set_string(value_str, key_str, entry);
  }

  return ret;
}

static sl_status_t app_settings_set_trace_filter(const char *value_str,
                                                 const char *key_str,
                                                 const app_settings_entry_t *entry)
{
  sl_status_t ret;
  const app_settings_entry_t *iter;
  (void)entry;

  if (!value_str) {
    return SL_STATUS_INVALID_KEY;
  }

  iter = app_trace_filter_entries;
  while (iter->key) {
    if (!key_str || !strcmp(iter->key, key_str)) {
      if (iter->set_handler) {
        ret = iter->set_handler(value_str, key_str, iter);
        if (ret != SL_STATUS_OK) {
          return ret;
        } else {
          return sl_wisun_br_set_trace_filter(app_settings_wisun.trace_filter);
        }
      } else {
        return SL_STATUS_PERMISSION;
      }
    }
    iter++;
  }

  return SL_STATUS_OK;
}

static sl_status_t app_settings_get_trace_filter(char *value_str,
                                                 const char *key_str,
                                                 const app_settings_entry_t *entry)
{
  sl_status_t ret;
  const app_settings_entry_t *iter;
  char trace_filter_string[128];
  (void)value_str;

  iter = app_trace_filter_entries;
  while (iter->key) {
    if (!key_str || !strcmp(iter->key, key_str)) {
      if (iter->get_handler) {
        ret = iter->get_handler(trace_filter_string, NULL, iter);
        if (ret == SL_STATUS_OK) {
          printf("%s.%s.%s = %s\r\n", app_settings_domain_str[entry->domain], entry->key, iter->key, trace_filter_string);
        }
      }
    }
    iter++;
  }

  // Prevent parent from printing anything
  return SL_STATUS_FAIL;
}

static sl_status_t app_settings_set_pti_state(const char *value_str,
                                              const char *key_str,
                                              const app_settings_entry_t *entry)
{
  sl_status_t ret;
  uint32_t pti_state;
  (void)key_str;
  (void)entry;

  ret = app_util_get_integer(&pti_state, value_str, NULL, false);
  if (ret != SL_STATUS_OK) {
    // Not a valid PTI state.
    ret = SL_STATUS_INVALID_TYPE;
  } else if (pti_state > 1) {
    // Not a valid PTI state.
    ret = SL_STATUS_INVALID_PARAMETER;
  }

  if (ret == SL_STATUS_OK) {
    app_settings_app.pti_state = pti_state;
    ret = sl_wisun_br_set_pti(pti_state);
    if (ret == SL_STATUS_OK) {
      printf("[PTI set correctly]\r\n");
    } else {
      printf("[Failed to set PTI]\r\n");
      ret = SL_STATUS_OK;  // To prevent the caller to display an error message.
    }
  }

  return ret;
}

static sl_status_t app_settings_set_regulation(const char *value_str,
                                               const char *key_str,
                                               const app_settings_entry_t *entry)
{
  sl_status_t ret;
  sli_wisun_br_task_state_t state;

  sl_wisun_br_get_state(&state);

  if (state == SLI_WISUN_BR_TASK_STATE_STARTED) {
    return SL_STATUS_INVALID_STATE;
  }

  ret = app_settings_set_integer(value_str, key_str, entry);

  return ret;
}

#if RAIL_IEEE802154_SUPPORTS_G_MODESWITCH
static sl_status_t app_settings_set_rx_phy_mode_ids(const char *value_str,
                                                    const char *key_str,
                                                    const app_settings_entry_t *entry)
{
  sl_status_t ret = SL_STATUS_OK;
  char *end_str, *start_str;
  uint8_t phy_mode_id;
  uint8_t phy_mode_ids_count = 0;
  uint8_t phy_mode_ids[SL_WISUN_MAX_PHY_MODE_ID_COUNT];


  (void)key_str;
  (void)entry;

  start_str = (char *) value_str;

  do {
    phy_mode_id = strtoul(start_str, &end_str, 0);

    if (end_str == start_str) {
      // No integer found
      ret = SL_STATUS_INVALID_PARAMETER;
      break;
    }

    phy_mode_ids[phy_mode_ids_count] = phy_mode_id;
    phy_mode_ids_count++;

    if (*end_str == ',') {
      // list separator, point to next element
      end_str++;
    }
    start_str = end_str;
  } while (*end_str != '\0');

  if (ret == SL_STATUS_OK) {
    memcpy(app_settings_wisun.rx_phy_mode_ids, phy_mode_ids, phy_mode_ids_count);
    app_settings_wisun.rx_phy_mode_ids_count = phy_mode_ids_count;

    ret = sl_wisun_br_set_pom_ie(app_settings_wisun.rx_phy_mode_ids_count,
                                 app_settings_wisun.rx_phy_mode_ids,
                                 0);
  }

  return ret;
}

static sl_status_t app_settings_get_rx_phy_mode_ids(char *value_str,
                                                    const char *key_str,
                                                    const app_settings_entry_t *entry)
{
  int i;
  sl_status_t ret = SL_STATUS_OK;
  uint8_t phy_mode_id_count, is_mdr_command_capable;
  uint8_t phy_mode_id[SL_WISUN_MAX_PHY_MODE_ID_COUNT];
  uint8_t *phy_mode_id_p, *phy_mode_id_count_p;

  (void) key_str;
  (void) entry;


  if (app_settings_wisun.rx_phy_mode_ids_count == 0) {
    // Check if default PhyList can be retrieved from device
    if (sl_wisun_br_get_pom_ie(&phy_mode_id_count, phy_mode_id, &is_mdr_command_capable) == SL_STATUS_OK) {
      phy_mode_id_p = phy_mode_id;
      phy_mode_id_count_p = &phy_mode_id_count;
      app_settings_wisun.rx_phy_mode_ids_count = phy_mode_id_count;
    } else {
      ret = SL_STATUS_FAIL;
    }
  } else {
    phy_mode_id_p = app_settings_wisun.rx_phy_mode_ids;
    phy_mode_id_count_p = &app_settings_wisun.rx_phy_mode_ids_count;
  }

  if (ret == SL_STATUS_OK) {
    if (*phy_mode_id_count_p == 0) {
      sprintf(value_str, "no PhyModeId set");
    } else {
      for (i = 0; i < *phy_mode_id_count_p - 1; i ++) {
        sprintf(value_str, "0x%02x,", phy_mode_id_p[i]);
        value_str += 5;
      }
      // Last one without coma
      sprintf(value_str, "0x%02x", phy_mode_id_p[i]);
    }
  }

  return SL_STATUS_OK;
}
#endif