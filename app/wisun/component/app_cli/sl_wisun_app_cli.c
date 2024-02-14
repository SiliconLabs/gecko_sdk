/***************************************************************************//**
 * @file
 * @brief
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "sl_component_catalog.h"
#include "sl_cli.h"
#include "sl_wisun_api.h"
#include "sl_wisun_trace_util.h"
#include "sl_wisun_cli_settings.h"
#include "sl_wisun_app_setting.h"
#include "sl_wisun_cli_util.h"
#include "sl_wisun_cli_core.h"
#if defined(SL_CATALOG_WISUN_APP_CORE_PRESENT)
  #include "sl_wisun_app_core_util.h"
  #include "sl_wisun_app_core_config.h"
#endif

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

/// Internal Config: Enable FAN 1.1 configuration
#define APP_CLI_ENABLE_FAN11_CONFIG          1U

/// Internal Config: Enable Explicit configuration
#define APP_CLI_ENABLE_EXPLICIT_CONFIG       1U

/// Wisun CLI domain ID
#define APP_CLI_WISUN_DOMAIN_ID              0U

/// App CLI input flag: None
#define APP_CLI_INPUT_FLAG_NONE              APP_SETTINGS_INPUT_FLAG_NONE

/// App CLI input flag: Signed
#define APP_CLI_INPUT_FLAG_SIGNED            APP_SETTINGS_INPUT_FLAG_SIGNED

/// App CLI input flag: Default
#define APP_CLI_INPUT_FLAG_DEFAULT           APP_SETTINGS_INPUT_FLAG_DEFAULT

/// App CLI output flag: None
#define APP_CLI_OUTPUT_FLAG_NONE             APP_SETTINGS_OUTPUT_FLAG_NONE

/// App CLI output flag: Signed
#define APP_CLI_OUTPUT_FLAG_SIGNED           APP_SETTINGS_OUTPUT_FLAG_SIGNED

/// App CLI output flag: Hex
#define APP_CLI_OUTPUT_FLAG_HEX              APP_SETTINGS_OUTPUT_FLAG_HEX

/// App CLI output flag: Fixed size
#define APP_CLI_OUTPUT_FLAG_FIXEDSIZE        APP_SETTINGS_OUTPUT_FLAG_FIXEDSIZE

/// App CLI output flag: Default
#define APP_CLI_OUTPUT_FLAG_DEFAULT          APP_SETTINGS_OUTPUT_FLAG_DEFAULT

/// App CLI value: None
#define APP_CLI_VALUE_SIZE_NONE              APP_SETTINGS_VALUE_SIZE_NONE

/// App CLI output flag: uint8
#define APP_CLI_VALUE_SIZE_UINT8             APP_SETTINGS_VALUE_SIZE_UINT8

/// App CLI output flag: uint16
#define APP_CLI_VALUE_SIZE_UINT16            APP_SETTINGS_VALUE_SIZE_UINT16

/// App CLI output flag: uint32
#define APP_CLI_VALUE_SIZE_UINT32            APP_SETTINGS_VALUE_SIZE_UINT32

/// App CLI string value length
#define APP_CLI_STR_VALUE_LENGTH             APP_SETTINGS_STR_VALUE_LENGTH

/// App CLI paramater string name: regulatory domain
#define APP_CLI_PHY_PARAM_REG_DOMAIN_STR    "regulatory_domain"

/// App CLI paramater string name: operating mode
#define APP_CLI_PHY_PARAM_OP_MODE_STR       "operating_mode"

/// App CLI paramater string name: operating class
#define APP_CLI_PHY_PARAM_OP_CLASS_STR      "operating_class"

#if APP_CLI_ENABLE_EXPLICIT_CONFIG
/// App CLI paramater string name: number of channels
#define APP_CLI_PHY_PARAM_NUM_OF_CH_STR     "number_of_channels"

/// App CLI paramater string name: CH0 frequency
#define APP_CLI_PHY_PARAM_CH0_FREQ_STR      "ch0_frequency"

/// App CLI paramater string name: channel spacing
#define APP_CLI_PHY_PARAM_CH_SPACING_STR    "channel_spacing"
#endif

#if APP_CLI_ENABLE_EXPLICIT_CONFIG || APP_CLI_ENABLE_FAN11_CONFIG
/// App CLI paramater string name: PHY mode ID
#define APP_CLI_PHY_PARAM_PHY_MODE_ID_STR   "phy_mode_id"
#endif

#if APP_CLI_ENABLE_FAN11_CONFIG
/// App CLI paramater string name: channel plan ID
#define APP_CLI_PHY_PARAM_CH_PLAN_ID_STR    "chan_plan_id"
#endif

/// App CLI paramater string name: PHY config type
#define APP_CLI_PHY_PARAM_PHY_CFG_TYPE_STR  "phy_config_type"

/// App CLI entry
typedef app_settings_entry_t app_cli_entry_t;

/// Structure typedef to store common PHY parameters, like reg. domain and PHY mode ID
typedef struct app_cli_phy_common_params {
  /// Regulatory domain
  uint8_t regulatory_domain;
  /// Operating class
  uint8_t operating_class;
  /// Operating mode
  uint16_t operating_mode;
#if APP_CLI_ENABLE_EXPLICIT_CONFIG
  /// Number of channels
  uint16_t number_of_channels;
  /// CH0 frequency
  uint32_t ch0_frequency;
  /// Channel spacing
  uint8_t channel_spacing;
#endif
#if APP_CLI_ENABLE_FAN11_CONFIG
  /// Channel plan ID
  uint8_t chan_plan_id;
#endif
#if APP_CLI_ENABLE_EXPLICIT_CONFIG || APP_CLI_ENABLE_FAN11_CONFIG
  /// PHY mode ID
  uint8_t phy_mode_id;
#endif
  /// PHY config type
  uint8_t phy_config_type;
} app_cli_phy_common_params_t;

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief Set CLI common PHY parameters from PHY config
 * @details Synchronization is required because of common parameters,
 *          like reg. domain and PHY mode ID
 * @return sl_status_t SL_STATUS_OK on succes, SL_STATUS_FAIL otherwise
 *****************************************************************************/
static sl_status_t _load_common_params_from_phy_cfg(void);

/**************************************************************************//**
 * @brief Store CLI common PHY parameters to PHY config
 * @details Synchronization is required because of common parameters,
 *          like reg domain and phy mode id
 * @return sl_status_t SL_STATUS_OK on succes, SL_STATUS_FAIL otherwise
 *****************************************************************************/
static sl_status_t _store_common_params_to_phy_cfg(void);

/**************************************************************************//**
 * @brief Helper to get connection status for getter
 * @param[out] *value_str is the desired value string
 * @param[in] *key_str is the key string of the set command
 * @param[in] *entry is the settings entry
 * @return SL_STATUS_OK if the setting is success.
 * @return SL_STATUS_FAIL if setting failed.
 *****************************************************************************/
static sl_status_t _app_cli_get_connection(char *value_str,
                                           const char *key_str,
                                           const app_cli_entry_t *entry);

/**************************************************************************//**
 * @brief Helper to set network name for setter
 * @param[out] *value_str is the desired value string
 * @param[in] *key_str is the key string of the set command
 * @param[in] *entry is the settings entry
 * @return SL_STATUS_OK if the setting is success.
 * @return SL_STATUS_FAIL if setting failed.
 *****************************************************************************/
static sl_status_t _app_cli_set_network_name(const char *value_str,
                                             const char *key_str,
                                             const app_cli_entry_t *entry);

/**************************************************************************//**
 * @brief Helper to set network size for setter
 * @param[out] *value_str is the desired value string
 * @param[in] *key_str is the key string of the set command
 * @param[in] *entry is the settings entry
 * @return SL_STATUS_OK if the setting is success.
 * @return SL_STATUS_FAIL if setting failed.
 *****************************************************************************/
static sl_status_t _app_cli_set_network_size(const char *value_str,
                                             const char *key_str,
                                             const app_cli_entry_t *entry);

/**************************************************************************//**
 * @brief Helper to set TX power for getter
 * @param[out] *value_str is the desired value string
 * @param[in] *key_str is the key string of the set command
 * @param[in] *entry is the settings entry
 * @return SL_STATUS_OK if the setting is success.
 * @return SL_STATUS_FAIL if setting failed.
 *****************************************************************************/
static sl_status_t _app_cli_set_tx_power(const char *value_str,
                                         const char *key_str,
                                         const app_cli_entry_t *entry);

/**************************************************************************//**
 * @brief Helper to get network name for getter
 * @param[out] *value_str is the desired value string
 * @param[in] *key_str is the key string of the set command
 * @param[in] *entry is the settings entry
 * @return SL_STATUS_OK if the setting is success.
 * @return SL_STATUS_FAIL if setting failed.
 *****************************************************************************/
static sl_status_t _app_cli_get_network_name(char *value_str,
                                             const char *key_str,
                                             const app_cli_entry_t *entry);

/**************************************************************************//**
 * @brief Helper to get network size for getter
 * @param[out] *value_str is the desired value string
 * @param[in] *key_str is the key string of the set command
 * @param[in] *entry is the settings entry
 * @return SL_STATUS_OK if the setting is success.
 * @return SL_STATUS_FAIL if setting failed.
 *****************************************************************************/
static sl_status_t _app_cli_get_network_size(char *value_str,
                                             const char *key_str,
                                             const app_cli_entry_t *entry);

/**************************************************************************//**
 * @brief Helper to get TX power for getter
 * @param[out] *value_str is the desired value string
 * @param[in] *key_str is the key string of the set command
 * @param[in] *entry is the settings entry
 * @return SL_STATUS_OK if the setting is success.
 * @return SL_STATUS_FAIL if setting failed.
 *****************************************************************************/
static sl_status_t _app_cli_get_tx_power(char *value_str,
                                         const char *key_str,
                                         const app_cli_entry_t *entry);

/**************************************************************************//**
 * @brief Is CLI setting parameter is used.
 * @details It indicates the parameteris used in the current setup.
 * @param param_str Parameter string.
 * @return true Parameter is used.
 * @return false Parameter is not used.
 *****************************************************************************/
static bool _is_param_used(const char *param_str);

/**************************************************************************//**
 * @brief Get param used string flag
 * @details Helper function to get string representation of parameter usage
 * @return const char*
 *****************************************************************************/
__STATIC_INLINE const char *_param_used_flag_str(const char *param_str);

/**************************************************************************//**
 * @brief Helper to get wisun phy for getter
 * @param[out] *value_str is the desired value string
 * @param[in] *key_str is the key string of the set command
 * @param[in] *entry is the settings entry
 * @return SL_STATUS_OK if the setting is success.
 * @return SL_STATUS_FAIL if setting failed.
 *****************************************************************************/
static sl_status_t _app_cli_get_phy(char *value_str,
                                    const char *key_str,
                                    const app_cli_entry_t *entry);

#if defined(SL_CATALOG_WISUN_MODE_SWITCH_PRESENT)
/**************************************************************************//**
 * @brief Helper to get wisun mode switch counters for getter
 * @param[out] *value_str is the desired value string
 * @param[in] *key_str is the key string of the set command
 * @param[in] *entry is the settings entry
 * @return SL_STATUS_OK if the setting is success.
 * @return SL_STATUS_FAIL if setting failed.
 *****************************************************************************/
static sl_status_t _app_ms_get_counters(char *value_str,
                                        const char *key_str,
                                        const app_cli_entry_t *entry);
#endif

/**************************************************************************//**
 * @brief Helper to set TX power for getter
 * @param[out] *value_str is the desired value string
 * @param[in] *key_str is the key string of the set command
 * @param[in] *entry is the settings entry
 * @return SL_STATUS_OK if the setting is success.
 * @return SL_STATUS_FAIL if setting failed.
 *****************************************************************************/
static sl_status_t _app_cli_set_phy(const char *value_str,
                                    const char *key_str,
                                    const app_settings_entry_t *entry);

#if defined(SL_CATALOG_WISUN_APP_CORE_PRESENT)
/**************************************************************************//**
 * @brief Helper to set regulation for setter
 * @param[out] *value_str is the desired value string
 * @param[in] *key_str is the key string of the set command
 * @param[in] *entry is the settings entry
 * @return SL_STATUS_OK if the setting is success.
 * @return SL_STATUS_FAIL if setting failed.
 *****************************************************************************/
static sl_status_t _app_set_regulation(const char *value_str,
                                       const char *key_str,
                                       const app_settings_entry_t *entry);

/**************************************************************************//**
 * @brief Helper to set regulation warning threshold for setter
 * @param[out] *value_str is the desired value string
 * @param[in] *key_str is the key string of the set command
 * @param[in] *entry is the settings entry
 * @return SL_STATUS_OK if the setting is success.
 * @return SL_STATUS_FAIL if setting failed.
 *****************************************************************************/
static sl_status_t _app_set_regulation_warning_threshold(const char *value_str,
                                                         const char *key_str,
                                                         const app_settings_entry_t *entry);

/**************************************************************************//**
 * @brief Helper to set regulation alert threshold for setter
 * @param[out] *value_str is the desired value string
 * @param[in] *key_str is the key string of the set command
 * @param[in] *entry is the settings entry
 * @return SL_STATUS_OK if the setting is success.
 * @return SL_STATUS_FAIL if setting failed.
 *****************************************************************************/
static sl_status_t _app_set_regulation_alert_threshold(const char *value_str,
                                                       const char *key_str,
                                                       const app_settings_entry_t *entry);

/**************************************************************************//**
 * @brief Helper to get regulation for getter
 * @param[out] *value_str is the desired value string
 * @param[in] *key_str is the key string of the set command
 * @param[in] *entry is the settings entry
 * @return SL_STATUS_OK if the setting is success.
 * @return SL_STATUS_FAIL if setting failed.
 *****************************************************************************/
static sl_status_t _app_get_regulation(char *value_str,
                                       const char *key_str,
                                       const app_cli_entry_t *entry);

/**************************************************************************//**
 * @brief Helper to get regulation warning threshold for setter
 * @param[out] *value_str is the desired value string
 * @param[in] *key_str is the key string of the set command
 * @param[in] *entry is the settings entry
 * @return SL_STATUS_OK if the setting is success.
 * @return SL_STATUS_FAIL if setting failed.
 *****************************************************************************/
static sl_status_t _app_get_regulation_warning_threshold(char *value_str,
                                                         const char *key_str,
                                                         const app_cli_entry_t *entry);

/**************************************************************************//**
 * @brief Helper to get regulation alert threshold for setter
 * @param[out] *value_str is the desired value string
 * @param[in] *key_str is the key string of the set command
 * @param[in] *entry is the settings entry
 * @return SL_STATUS_OK if the setting is success.
 * @return SL_STATUS_FAIL if setting failed.
 *****************************************************************************/
static sl_status_t _app_get_regulation_alert_threshold(char *value_str,
                                                       const char *key_str,
                                                       const app_cli_entry_t *entry);

#endif

#if defined(SL_CATALOG_WISUN_LFN_DEVICE_SUPPORT_PRESENT)
/**************************************************************************//**
 * @brief Helper to get device type
 * @param[out] *value_str is the desired value string
 * @param[in] *key_str is the key string of the set command
 * @param[in] *entry is the settings entry
 * @return SL_STATUS_OK if the setting is success.
 * @return SL_STATUS_FAIL if setting failed.
 *****************************************************************************/
static sl_status_t _app_get_device_type(char *value_str,
                                        const char *key_str,
                                        const app_cli_entry_t *entry);

/**************************************************************************//**
 * @brief Helper to get LFN profile
 * @param[out] *value_str is the desired value string
 * @param[in] *key_str is the key string of the set command
 * @param[in] *entry is the settings entry
 * @return SL_STATUS_OK if the setting is success.
 * @return SL_STATUS_FAIL if setting failed.
 *****************************************************************************/
static sl_status_t _app_get_lfn_profile(char *value_str,
                                        const char *key_str,
                                        const app_cli_entry_t *entry);
#endif

/**************************************************************************//**
 * @brief Connect to Wi-SUN network by PHY configuration type
 * @details CLI callback helper function
 * @param config_type PHY Configuration type
 *****************************************************************************/
static void _app_connect(const sl_wisun_phy_config_type_t config_type);

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

#if defined(SL_CATALOG_WISUN_APP_CORE_PRESENT)
/// Wi-SUN application regulation
static sl_wisun_regulation_t app_regulation = (sl_wisun_regulation_t)SL_WISUN_APP_CORE_REGULATION;
#endif

/// Common PHY parameters for CLI setter/getter
static app_cli_phy_common_params_t _phy_common_params = { 0U };

/// Mapping PHY config parameters by PHY config type
static const app_enum_t _phy_cfg_map[] = {
  // FAN 1.0 parameters
  { APP_CLI_PHY_PARAM_REG_DOMAIN_STR, SL_WISUN_PHY_CONFIG_FAN10 },
  { APP_CLI_PHY_PARAM_OP_CLASS_STR, SL_WISUN_PHY_CONFIG_FAN10 },
  { APP_CLI_PHY_PARAM_OP_MODE_STR, SL_WISUN_PHY_CONFIG_FAN10 },

  // FAN 1.1 parameters
#if APP_CLI_ENABLE_FAN11_CONFIG
  { APP_CLI_PHY_PARAM_REG_DOMAIN_STR, SL_WISUN_PHY_CONFIG_FAN11 },
  { APP_CLI_PHY_PARAM_CH_PLAN_ID_STR, SL_WISUN_PHY_CONFIG_FAN11 },
  { APP_CLI_PHY_PARAM_PHY_MODE_ID_STR, SL_WISUN_PHY_CONFIG_FAN11 },
#endif

  // Explicit parameters
#if APP_CLI_ENABLE_EXPLICIT_CONFIG
  { APP_CLI_PHY_PARAM_CH0_FREQ_STR, SL_WISUN_PHY_CONFIG_EXPLICIT },
  { APP_CLI_PHY_PARAM_NUM_OF_CH_STR, SL_WISUN_PHY_CONFIG_EXPLICIT },
  { APP_CLI_PHY_PARAM_CH_SPACING_STR, SL_WISUN_PHY_CONFIG_EXPLICIT },
  { APP_CLI_PHY_PARAM_PHY_MODE_ID_STR, SL_WISUN_PHY_CONFIG_EXPLICIT },
#endif
  // End list
  { NULL, 0 }
};

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

/// Wi-SUN application settings domain string
const char *app_settings_domain_str[] = {
  "wisun",
  NULL,
};

///  Wi-SUN application settings entry/entries
const app_cli_entry_t app_settings_entries[] =
{
  {
    .key = "network_name",
    .domain = APP_CLI_WISUN_DOMAIN_ID,
    .value_size = SL_WISUN_NETWORK_NAME_SIZE + 1,
    .input = APP_CLI_INPUT_FLAG_DEFAULT,
    .output = APP_CLI_OUTPUT_FLAG_DEFAULT,
    .value = NULL,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = _app_cli_set_network_name,
    .get_handler = _app_cli_get_network_name,
    .description = "Wi-SUN network [string] max 32"
  },
  {
    .key = APP_CLI_PHY_PARAM_PHY_CFG_TYPE_STR,
    .domain = APP_CLI_WISUN_DOMAIN_ID,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT8,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = NULL,
    .input_enum_list = NULL,
    .output_enum_list = app_wisun_phy_config_type_enum,
    .set_handler = NULL,
    .get_handler = _app_cli_get_phy,
    .description = "PHY configuration type (FAN 1.0|FAN 1.1|explicit)"
  },
  {
    .key = "network_size",
    .domain = APP_CLI_WISUN_DOMAIN_ID,
    .value_size = APP_CLI_VALUE_SIZE_UINT8,
    .input = APP_CLI_INPUT_FLAG_DEFAULT,
    .output = APP_CLI_OUTPUT_FLAG_DEFAULT,
    .value = NULL,
    .input_enum_list = app_wisun_nw_size_enum,
    .output_enum_list = app_wisun_nw_size_enum,
    .set_handler = _app_cli_set_network_size,
    .get_handler = _app_cli_get_network_size,
    .description = "Wi-SUN network size [uint8]"
  },
  {
    .key = "tx_power",
    .domain = APP_CLI_WISUN_DOMAIN_ID,
    .value_size = APP_CLI_VALUE_SIZE_UINT8,
    .input = APP_CLI_INPUT_FLAG_DEFAULT | APP_CLI_INPUT_FLAG_SIGNED,
    .output = APP_CLI_OUTPUT_FLAG_DEFAULT | APP_CLI_OUTPUT_FLAG_SIGNED,
    .value = NULL,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = _app_cli_set_tx_power,
    .get_handler = _app_cli_get_tx_power,
    .description = "TX power in dBm [uint8]"
  },
  {
    .key = APP_CLI_PHY_PARAM_REG_DOMAIN_STR,
    .domain = APP_CLI_WISUN_DOMAIN_ID,
    .value_size = APP_CLI_VALUE_SIZE_UINT8,
    .input = APP_CLI_INPUT_FLAG_DEFAULT,
    .output = APP_CLI_OUTPUT_FLAG_DEFAULT,
    .value = NULL,
    .input_enum_list = app_wisun_phy_reg_domain_enum,
    .output_enum_list = app_wisun_phy_reg_domain_enum,
    .set_handler = _app_cli_set_phy,
    .get_handler = _app_cli_get_phy,
    .description = "Wi-SUN regulatory domain [uint8]"
  },
  {
    .key = APP_CLI_PHY_PARAM_OP_CLASS_STR,
    .domain = APP_CLI_WISUN_DOMAIN_ID,
    .value_size = APP_CLI_VALUE_SIZE_UINT8,
    .input = APP_CLI_INPUT_FLAG_DEFAULT,
    .output = APP_CLI_OUTPUT_FLAG_DEFAULT,
    .value = NULL,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = _app_cli_set_phy,
    .get_handler = _app_cli_get_phy,
    .description = "Wi-SUN operation class [uint8]"
  },
  {
    .key = APP_CLI_PHY_PARAM_OP_MODE_STR,
    .domain = APP_CLI_WISUN_DOMAIN_ID,
    .value_size = APP_CLI_VALUE_SIZE_UINT8,
    .input = APP_CLI_INPUT_FLAG_DEFAULT,
    .output = APP_CLI_OUTPUT_FLAG_DEFAULT,
    .value = NULL,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = _app_cli_set_phy,
    .get_handler = _app_cli_get_phy,
    .description = "Wi-SUN operating mode [uint16]"
  },
#if APP_CLI_ENABLE_FAN11_CONFIG
  {
    .key = APP_CLI_PHY_PARAM_CH_PLAN_ID_STR,
    .domain = APP_CLI_WISUN_DOMAIN_ID,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT8,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = NULL,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = _app_cli_set_phy,
    .get_handler = _app_cli_get_phy,
    .description = "Wi-SUN channel plan ID [uint8]"
  },
#endif
#if APP_CLI_ENABLE_FAN11_CONFIG || APP_CLI_ENABLE_EXPLICIT_CONFIG
  {
    .key = APP_CLI_PHY_PARAM_PHY_MODE_ID_STR,
    .domain = APP_CLI_WISUN_DOMAIN_ID,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT8,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = NULL,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = _app_cli_set_phy,
    .get_handler = _app_cli_get_phy,
    .description = "Wi-SUN PHY mode ID [uint8]"
  },
#endif
#if APP_CLI_ENABLE_EXPLICIT_CONFIG
  {
    .key = APP_CLI_PHY_PARAM_CH0_FREQ_STR,
    .domain = APP_CLI_WISUN_DOMAIN_ID,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT32,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = NULL,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = _app_cli_set_phy,
    .get_handler = _app_cli_get_phy,
    .description = "Ch0 frequency in kHz [uint32]"
  },
  {
    .key = APP_CLI_PHY_PARAM_NUM_OF_CH_STR,
    .domain = APP_CLI_WISUN_DOMAIN_ID,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT16,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = NULL,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = _app_cli_set_phy,
    .get_handler = _app_cli_get_phy,
    .description = "Number of channels [uint16]"
  },
  {
    .key = APP_CLI_PHY_PARAM_CH_SPACING_STR,
    .domain = APP_CLI_WISUN_DOMAIN_ID,
    .value_size = APP_SETTINGS_VALUE_SIZE_UINT8,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = NULL,
    .input_enum_list = app_wisun_phy_channel_spacing_enum,
    .output_enum_list = app_wisun_phy_channel_spacing_enum,
    .set_handler = _app_cli_set_phy,
    .get_handler = _app_cli_get_phy,
    .description = "Channel spacing [string] (100kHz|200kHz|400kHz|600kHz)"
  },
#endif
  {
    .key = "join_state",
    .domain = APP_CLI_WISUN_DOMAIN_ID,
    .value_size = APP_CLI_VALUE_SIZE_UINT8,
    .input = APP_CLI_INPUT_FLAG_DEFAULT,
    .output = APP_CLI_OUTPUT_FLAG_DEFAULT,
    .value = NULL,
    .input_enum_list = app_wisun_conn_status_enum,
    .output_enum_list = app_wisun_conn_status_enum,
    .set_handler = NULL,
    .get_handler = _app_cli_get_connection,
    .description = "Wi-SUN join state"
  },
  {
    .key = "ip_address_global",
    .domain = APP_CLI_WISUN_DOMAIN_ID,
    .value_size = APP_CLI_VALUE_SIZE_NONE,
    .input = APP_CLI_INPUT_FLAG_DEFAULT,
    .output = APP_CLI_OUTPUT_FLAG_DEFAULT,
    .value = NULL,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_ip_address,
    .description = "Global IPv6 address"
  },
  {
    .key = "ip_address_link_local",
    .domain = APP_CLI_WISUN_DOMAIN_ID,
    .value_size = APP_CLI_VALUE_SIZE_NONE,
    .input = APP_CLI_INPUT_FLAG_DEFAULT,
    .output = APP_CLI_OUTPUT_FLAG_DEFAULT,
    .value = NULL,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_ip_address,
    .description = "Link local IPv6"
  },
  {
    .key = "ip_address_border_router",
    .domain = APP_CLI_WISUN_DOMAIN_ID,
    .value_size = APP_CLI_VALUE_SIZE_NONE,
    .input = APP_CLI_INPUT_FLAG_DEFAULT,
    .output = APP_CLI_OUTPUT_FLAG_DEFAULT,
    .value = NULL,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_ip_address,
    .description = "Border Router IPv6 address"
  },
  {
    .key = "ip_address_primary_parent",
    .domain = APP_CLI_WISUN_DOMAIN_ID,
    .value_size = APP_CLI_VALUE_SIZE_NONE,
    .input = APP_CLI_INPUT_FLAG_DEFAULT,
    .output = APP_CLI_OUTPUT_FLAG_DEFAULT,
    .value = NULL,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = app_settings_get_ip_address,
    .description = "Primary Parent IPv6 address"
  },
#if defined(SL_CATALOG_WISUN_MODE_SWITCH_PRESENT)
  {
    .key = "mode_switch_tx_counter",
    .domain = APP_CLI_WISUN_DOMAIN_ID,
    .value_size = APP_CLI_VALUE_SIZE_UINT32,
    .input = APP_CLI_INPUT_FLAG_DEFAULT,
    .output = APP_CLI_OUTPUT_FLAG_DEFAULT,
    .value = NULL,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = _app_ms_get_counters,
    .description = "Mode Switch Tx count"
  },
  {
    .key = "mode_switch_tx_failed_counter",
    .domain = APP_CLI_WISUN_DOMAIN_ID,
    .value_size = APP_CLI_VALUE_SIZE_UINT32,
    .input = APP_CLI_INPUT_FLAG_DEFAULT,
    .output = APP_CLI_OUTPUT_FLAG_DEFAULT,
    .value = NULL,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = _app_ms_get_counters,
    .description = "Mode Switch Tx failed count"
  },
  {
    .key = "mode_switch_rx_counter",
    .domain = APP_CLI_WISUN_DOMAIN_ID,
    .value_size = APP_CLI_VALUE_SIZE_UINT32,
    .input = APP_CLI_INPUT_FLAG_DEFAULT,
    .output = APP_CLI_OUTPUT_FLAG_DEFAULT,
    .value = NULL,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = _app_ms_get_counters,
    .description = "Mode Switch Rx count"
  },
  {
    .key = "mode_switch_rx_failed_counter",
    .domain = APP_CLI_WISUN_DOMAIN_ID,
    .value_size = APP_CLI_VALUE_SIZE_UINT32,
    .input = APP_CLI_INPUT_FLAG_DEFAULT,
    .output = APP_CLI_OUTPUT_FLAG_DEFAULT,
    .value = NULL,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = _app_ms_get_counters,
    .description = "Mode Switch Rx failed count"
  },
#endif
#if defined(SL_CATALOG_WISUN_APP_CORE_PRESENT)
  {
    .key = "regulation",
    .domain = APP_CLI_WISUN_DOMAIN_ID,
    .value_size = APP_CLI_VALUE_SIZE_UINT8,
    .input = APP_CLI_INPUT_FLAG_DEFAULT,
    .output = APP_CLI_OUTPUT_FLAG_DEFAULT,
    .value = NULL,
    .input_enum_list = app_regulation_enum,
    .output_enum_list = app_regulation_enum,
    .set_handler = _app_set_regulation,
    .get_handler = _app_get_regulation,
    .description = "Regional regulation [uint8]"
  },
  {
    .key = "regulation_warning_threshold",
    .domain = APP_CLI_WISUN_DOMAIN_ID,
    .value_size = APP_CLI_VALUE_SIZE_UINT8,
    .input = APP_CLI_INPUT_FLAG_SIGNED,
    .output = APP_CLI_OUTPUT_FLAG_SIGNED,
    .value = NULL,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = _app_set_regulation_warning_threshold,
    .get_handler = _app_get_regulation_warning_threshold,
    .description = "Transmission warning threshold in percent (-1 to disable) [int8]"
  },
  {
    .key = "regulation_alert_threshold",
    .domain = APP_CLI_WISUN_DOMAIN_ID,
    .value_size = APP_CLI_VALUE_SIZE_UINT8,
    .input = APP_CLI_INPUT_FLAG_SIGNED,
    .output = APP_CLI_OUTPUT_FLAG_SIGNED,
    .value = NULL,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = _app_set_regulation_alert_threshold,
    .get_handler = _app_get_regulation_alert_threshold,
    .description = "Transmission alert threshold in percent (-1 to disable) [int8]"
  },
#endif
#if defined(SL_CATALOG_WISUN_LFN_DEVICE_SUPPORT_PRESENT)
  {
    .key = "device_type",
    .domain = APP_CLI_WISUN_DOMAIN_ID,
    .value_size = APP_CLI_VALUE_SIZE_UINT8,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = NULL,
    .input_enum_list = app_wisun_device_type_enum,
    .output_enum_list = app_wisun_device_type_enum,
    .set_handler = NULL,
    .get_handler = _app_get_device_type,
    .description = "Device type"
  },
  {
    .key = "lfn_profile",
    .domain = APP_CLI_WISUN_DOMAIN_ID,
    .value_size = APP_CLI_VALUE_SIZE_UINT8,
    .input = APP_SETTINGS_INPUT_FLAG_DEFAULT,
    .output = APP_SETTINGS_OUTPUT_FLAG_DEFAULT,
    .value = NULL,
    .input_enum_list = app_wisun_lfn_profile_enum,
    .output_enum_list = app_wisun_lfn_profile_enum,
    .set_handler = NULL,
    .get_handler = _app_get_lfn_profile,
    .description = "Wi-SUN LFN profile"
  },
#endif
  {
    .key = NULL,
    .domain = 0,
    .value_size = APP_CLI_VALUE_SIZE_NONE,
    .input = APP_CLI_INPUT_FLAG_DEFAULT,
    .output = APP_CLI_OUTPUT_FLAG_DEFAULT,
    .value = NULL,
    .input_enum_list = NULL,
    .output_enum_list = NULL,
    .set_handler = NULL,
    .get_handler = NULL,
    .description = NULL
  }
};

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

#if defined(SL_CATALOG_APP_PROJECT_INFO_PRESENT)
void app_about(void)
{
  sl_wisun_app_core_util_project_info_print(false);
}
#endif

#if defined(SL_CATALOG_WISUN_APP_CORE_PRESENT)
static void _app_connect(const sl_wisun_phy_config_type_t config_type)
{
  sl_status_t stat = SL_STATUS_FAIL;

  stat = _load_common_params_from_phy_cfg();
  if (stat != SL_STATUS_OK) {
    printf("[Failed: Loading PHY config]\n");
    return;
  }

  // Set expected config type
  _phy_common_params.phy_config_type = (uint8_t) config_type;

  // Store CLI cfg to PHY cfg
  stat = _store_common_params_to_phy_cfg();

  if (stat != SL_STATUS_OK) {
    printf("[Failed: Storing PHY config]\n");
    return;
  }
  // call connect API
  sl_wisun_app_core_network_connect();
}

/* CLI app connect to FAN 1.0 handler */
void app_join_fan10(sl_cli_command_arg_t *arguments)
{
  (void) arguments;
  app_wisun_cli_mutex_lock();
  _app_connect(SL_WISUN_PHY_CONFIG_FAN10);
  app_wisun_cli_mutex_unlock();
}

/* CLI app connect to FAN 1.1 handler */
void app_join_fan11(sl_cli_command_arg_t *arguments)
{
  (void) arguments;
#if APP_CLI_ENABLE_FAN11_CONFIG
  app_wisun_cli_mutex_lock();
  _app_connect(SL_WISUN_PHY_CONFIG_FAN11);
  app_wisun_cli_mutex_unlock();
#else
  printf("[FAN 1.1 configratuion is not supported]\n");
#endif
}

/* CLI app connect explicit handler */
void app_join_explicit(sl_cli_command_arg_t *arguments)
{
  (void) arguments;
#if APP_CLI_ENABLE_EXPLICIT_CONFIG
  app_wisun_cli_mutex_lock();
  _app_connect(SL_WISUN_PHY_CONFIG_EXPLICIT);
  app_wisun_cli_mutex_unlock();
#else
  printf("[Explicit PHY configration is not supported]\n");
#endif
}

/* CLI app disconnect handler */
void app_disconnect(sl_cli_command_arg_t *arguments)
{
  sl_status_t ret;
  sl_wisun_join_state_t join_state = SL_WISUN_JOIN_STATE_DISCONNECTED;
  (void) arguments;

  app_wisun_cli_mutex_lock();

  ret = sl_wisun_get_join_state(&join_state);
  if (ret != SL_STATUS_OK) {
    printf("[Failed: Getting join state failed]\n");
    app_wisun_cli_mutex_unlock();
    return;
  }
  if (join_state == SL_WISUN_JOIN_STATE_DISCONNECTED) {
    printf("[Failed: already disconnected]\n");
    app_wisun_cli_mutex_unlock();
    return;
  }

  ret = sl_wisun_disconnect();
  if (ret == SL_STATUS_OK) {
    printf("[Disconnecting]\n");
  } else {
    printf("[Disconnection failed: %lu]\n", ret);
  }

  app_wisun_cli_mutex_unlock();
}
#endif

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------

static sl_status_t _load_common_params_from_phy_cfg(void)
{
  static sl_wisun_phy_config_t phy_cfg = { 0U };

  if (!app_wisun_setting_is_notified(APP_SETTING_NOTIFICATION_SET_PHY_CFG,
                                     APP_SETTING_DEFAULT_SUBSCRIPT_CH)) {
    return SL_STATUS_OK;
  }

  (void) app_wisun_setting_get_phy(&phy_cfg);

  // FAN 1.0 setting
  if (phy_cfg.type == SL_WISUN_PHY_CONFIG_FAN10) {
    _phy_common_params.regulatory_domain  = phy_cfg.config.fan10.reg_domain;
    _phy_common_params.operating_mode     = phy_cfg.config.fan10.op_mode;
    _phy_common_params.operating_class    = phy_cfg.config.fan10.op_class;

    // FAN 1.1 setting
  } else if (phy_cfg.type == SL_WISUN_PHY_CONFIG_FAN11) {
#if APP_CLI_ENABLE_FAN11_CONFIG
    _phy_common_params.regulatory_domain  = phy_cfg.config.fan11.reg_domain;
    _phy_common_params.chan_plan_id       = phy_cfg.config.fan11.chan_plan_id;
    _phy_common_params.phy_mode_id        = phy_cfg.config.fan11.phy_mode_id;
#else
    (void) 0U;
#endif
    // Explicit setting
  } else if (phy_cfg.type == SL_WISUN_PHY_CONFIG_EXPLICIT) {
#if APP_CLI_ENABLE_EXPLICIT_CONFIG
    _phy_common_params.ch0_frequency      = phy_cfg.config.explicit_plan.ch0_frequency_khz;
    _phy_common_params.number_of_channels = phy_cfg.config.explicit_plan.number_of_channels;
    _phy_common_params.channel_spacing    = phy_cfg.config.explicit_plan.channel_spacing;
    _phy_common_params.phy_mode_id        = phy_cfg.config.explicit_plan.phy_mode_id;
#else
    (void) 0U;
#endif
    // Invalid setting
  } else {
    return SL_STATUS_FAIL;
  }
  _phy_common_params.phy_config_type = phy_cfg.type;

  app_wisun_setting_ack_notification(APP_SETTING_NOTIFICATION_SET_PHY_CFG,
                                     APP_SETTING_DEFAULT_SUBSCRIPT_CH);
  return SL_STATUS_OK;
}

static sl_status_t _store_common_params_to_phy_cfg(void)
{
  static sl_wisun_phy_config_t phy_cfg = { 0U };

  // FAN 1.0 setting
  if (_phy_common_params.phy_config_type == SL_WISUN_PHY_CONFIG_FAN10) {
    phy_cfg.config.fan10.reg_domain            = _phy_common_params.regulatory_domain;
    phy_cfg.config.fan10.op_mode               = _phy_common_params.operating_mode;
    phy_cfg.config.fan10.op_class              = _phy_common_params.operating_class;

    // FAN 1.1 setting
  } else if (_phy_common_params.phy_config_type == SL_WISUN_PHY_CONFIG_FAN11) {
#if APP_CLI_ENABLE_FAN11_CONFIG
    phy_cfg.config.fan11.reg_domain            = _phy_common_params.regulatory_domain;
    phy_cfg.config.fan11.chan_plan_id          = _phy_common_params.chan_plan_id;
    phy_cfg.config.fan11.phy_mode_id           = _phy_common_params.phy_mode_id;
#else
    (void) 0U;
#endif
    // Explicit setting
  } else if (_phy_common_params.phy_config_type == SL_WISUN_PHY_CONFIG_EXPLICIT) {
#if APP_CLI_ENABLE_EXPLICIT_CONFIG
    phy_cfg.config.explicit_plan.ch0_frequency_khz  = _phy_common_params.ch0_frequency;
    phy_cfg.config.explicit_plan.number_of_channels = _phy_common_params.number_of_channels;
    phy_cfg.config.explicit_plan.channel_spacing    = _phy_common_params.channel_spacing;
    phy_cfg.config.explicit_plan.phy_mode_id        = _phy_common_params.phy_mode_id;
#else
    (void) 0U;
#endif
    // Invalid setting
  } else {
    return SL_STATUS_FAIL;
  }

  phy_cfg.type = _phy_common_params.phy_config_type;

  app_wisun_setting_set_phy(&phy_cfg);

  return SL_STATUS_OK;
}

/* App CLI getting connection state (join state) */
static sl_status_t _app_cli_get_connection(char *value_str,
                                           const char *key_str,
                                           const app_cli_entry_t *entry)
{
  sl_status_t res = SL_STATUS_FAIL;
  uint32_t value;
  const app_enum_t* value_enum;
  sl_wisun_join_state_t join_state = SL_WISUN_JOIN_STATE_DISCONNECTED;
  (void)key_str;

  if ((value_str == NULL) || (entry == NULL)) {
    return SL_STATUS_FAIL;
  }

  // gets the connection state from the core
  res = sl_wisun_get_join_state(&join_state);
  if (res != SL_STATUS_OK) {
    return res;
  }
  value = (uint32_t)join_state;

  // finds the proper string for the value
  value_enum = entry->output_enum_list;

  if (value_enum->value_str != NULL) {
    while (value_enum) {
      if (value_enum->value == value) {
        // Matching enumeration found
        break;
      }
      value_enum++;
    }
  } else {
    return SL_STATUS_FAIL;
  }

  // creates the value string
  snprintf(value_str, APP_CLI_STR_VALUE_LENGTH, "%s (%d)", value_enum->value_str, (uint8_t)value_enum->value);

  return SL_STATUS_OK;
}

/* App CLI setting network name */
static sl_status_t _app_cli_set_network_name(const char *value_str,
                                             const char *key_str,
                                             const app_cli_entry_t *entry)
{
  (void)key_str;
  (void)entry;

  return app_wisun_setting_set_network_name(value_str);
}

/* App CLI setting network size */
static sl_status_t _app_cli_set_network_size(const char *value_str,
                                             const char *key_str,
                                             const app_cli_entry_t *entry)
{
  sl_status_t res = SL_STATUS_FAIL;
  uint32_t value = 0U;
  (void)key_str;
  (void)entry;

  res = app_util_get_integer(&value,
                             value_str,
                             entry->input_enum_list,
                             entry->input & APP_CLI_INPUT_FLAG_SIGNED);
  if (res == SL_STATUS_OK) {
    // sets the network name
    res = app_wisun_setting_set_network_size((uint8_t*)&value);
  }

  return res;
}

/* App CLI setting tx power */
static sl_status_t _app_cli_set_tx_power(const char *value_str,
                                         const char *key_str,
                                         const app_cli_entry_t *entry)
{
  sl_status_t res = SL_STATUS_FAIL;
  int32_t value = 0U;
  (void)key_str;
  (void)entry;

  res = app_util_get_integer((uint32_t *)&value,
                             value_str,
                             entry->input_enum_list,
                             entry->input & APP_CLI_INPUT_FLAG_SIGNED);
  if (res == SL_STATUS_OK) {
    // sets the tx power
    res = app_wisun_setting_set_tx_power((int8_t*)&value);
  }

  return res;
}

/* App CLI setting network name */
static sl_status_t _app_cli_get_network_name(char *value_str,
                                             const char *key_str,
                                             const app_cli_entry_t *entry)
{
  sl_status_t res = SL_STATUS_FAIL;
  char name_buffer[MAX_SIZE_OF_NETWORK_NAME] = { 0 };
  (void)key_str;
  (void)entry;

  // gets the network name
  res = app_wisun_setting_get_network_name(name_buffer, sizeof(name_buffer));

  if (res == SL_STATUS_OK) {
    snprintf(value_str, APP_CLI_STR_VALUE_LENGTH, "%s", name_buffer);
  }

  return res;
}

/* App CLI setting network size */
static sl_status_t _app_cli_get_network_size(char *value_str,
                                             const char *key_str,
                                             const app_cli_entry_t *entry)
{
  sl_status_t res = SL_STATUS_FAIL;
  const app_enum_t* value_enum;
  uint8_t value = 0U;
  (void)key_str;

  res = app_wisun_setting_get_network_size(&value);
  // finds the proper string for the value
  value_enum = entry->output_enum_list;

  if (res != SL_STATUS_OK || value_enum->value_str == NULL) {
    return SL_STATUS_FAIL;
  }

  while (value_enum) {
    if (value_enum->value == value) {
      // Matching enumeration found
      break;
    }
    value_enum++;
  }

  // creates the value string
  snprintf(value_str, APP_CLI_STR_VALUE_LENGTH, "%s (%d)", value_enum->value_str, (uint8_t)value_enum->value);

  return res;
}

/* App CLI setting tx power */
static sl_status_t _app_cli_get_tx_power(char *value_str,
                                         const char *key_str,
                                         const app_cli_entry_t *entry)
{
  sl_status_t res = SL_STATUS_FAIL;
  int8_t value = 0U;
  (void)key_str;
  (void)entry;

  res = app_wisun_setting_get_tx_power(&value);
  if (res == SL_STATUS_OK) {
    snprintf(value_str, APP_CLI_STR_VALUE_LENGTH, "%d", value);
  } else {
    snprintf(value_str, APP_CLI_STR_VALUE_LENGTH, "N/A");
  }

  return res;
}

static bool _is_param_used(const char *param_str)
{
  app_enum_t *iter = NULL;

  iter = (app_enum_t *) _phy_cfg_map;

  while (iter != NULL && iter->value_str != NULL) {
    if (iter->value == _phy_common_params.phy_config_type
        && !strncmp(param_str, iter->value_str, APP_CLI_STR_VALUE_LENGTH)) {
      return true;
    }
    ++iter;
  }

  return false;
}

__STATIC_INLINE const char *_param_used_flag_str(const char *param_str)
{
  return _is_param_used(param_str) ? "" : "(unused)";
}

/* App CLI getting PHY parameters */
static sl_status_t _app_cli_get_phy(char *value_str,
                                    const char *key_str,
                                    const app_cli_entry_t *entry)
{
  sl_status_t res = SL_STATUS_FAIL;
  (void)key_str;

  if ((value_str == NULL) || (entry == NULL) || (entry->key == NULL)) {
    return res;
  }

  res = _load_common_params_from_phy_cfg();
  if (res != SL_STATUS_OK) {
    return res;
  }

  // Regulatory domain
  if (strstr(entry->key, APP_CLI_PHY_PARAM_REG_DOMAIN_STR)) {
    snprintf(value_str, APP_CLI_STR_VALUE_LENGTH, "%s (%u) %s",
             app_wisun_trace_util_reg_domain_to_str(_phy_common_params.regulatory_domain),
             _phy_common_params.regulatory_domain,
             _param_used_flag_str(APP_CLI_PHY_PARAM_REG_DOMAIN_STR));

    // Operating class
  } else if (strstr(entry->key, APP_CLI_PHY_PARAM_OP_CLASS_STR)) {
    snprintf(value_str, APP_CLI_STR_VALUE_LENGTH, "%u %s",
             _phy_common_params.operating_class,
             _param_used_flag_str(APP_CLI_PHY_PARAM_OP_CLASS_STR));

    // Operating mode
  } else if (strstr(entry->key, APP_CLI_PHY_PARAM_OP_MODE_STR)) {
    snprintf(value_str, APP_CLI_STR_VALUE_LENGTH, "0x%x %s",
             _phy_common_params.operating_mode,
             _param_used_flag_str(APP_CLI_PHY_PARAM_OP_MODE_STR));

#if APP_CLI_ENABLE_EXPLICIT_CONFIG
    // Number of channels
  } else if (strstr(entry->key, APP_CLI_PHY_PARAM_NUM_OF_CH_STR)) {
    snprintf(value_str, APP_CLI_STR_VALUE_LENGTH, "%u %s",
             _phy_common_params.number_of_channels,
             _param_used_flag_str(APP_CLI_PHY_PARAM_NUM_OF_CH_STR));

    // CH0 Frequency
  } else if (strstr(entry->key, APP_CLI_PHY_PARAM_CH0_FREQ_STR)) {
    snprintf(value_str, APP_CLI_STR_VALUE_LENGTH, "%lu %s",
             _phy_common_params.ch0_frequency,
             _param_used_flag_str(APP_CLI_PHY_PARAM_CH0_FREQ_STR));

    // Channel spacing
  } else if (strstr(entry->key, APP_CLI_PHY_PARAM_CH_SPACING_STR)) {
    snprintf(value_str, APP_CLI_STR_VALUE_LENGTH, "%s (%u) %s",
             app_wisun_trace_util_ch_spacing_to_str(_phy_common_params.channel_spacing),
             _phy_common_params.channel_spacing,
             _param_used_flag_str(APP_CLI_PHY_PARAM_CH_SPACING_STR));
#endif

#if APP_CLI_ENABLE_FAN11_CONFIG
    // Chan plan ID
  } else if (strstr(entry->key, APP_CLI_PHY_PARAM_CH_PLAN_ID_STR)) {
    snprintf(value_str, APP_CLI_STR_VALUE_LENGTH, "%u %s",
             _phy_common_params.chan_plan_id,
             _param_used_flag_str(APP_CLI_PHY_PARAM_CH_PLAN_ID_STR));
#endif

#if APP_CLI_ENABLE_EXPLICIT_CONFIG || APP_CLI_ENABLE_FAN11_CONFIG
    // PHY mode ID
  } else if (strstr(entry->key, APP_CLI_PHY_PARAM_PHY_MODE_ID_STR)) {
    snprintf(value_str, APP_CLI_STR_VALUE_LENGTH, "%u %s",
             _phy_common_params.phy_mode_id,
             _param_used_flag_str(APP_CLI_PHY_PARAM_PHY_MODE_ID_STR));
#endif

    // PHY config type
  } else if (strstr(entry->key, APP_CLI_PHY_PARAM_PHY_CFG_TYPE_STR)) {
    snprintf(value_str, APP_CLI_STR_VALUE_LENGTH, "%s (%d)",
             app_wisun_trace_util_phy_cfg_type_to_str(_phy_common_params.phy_config_type),
             _phy_common_params.phy_config_type);

    // Not found
  } else {
    return SL_STATUS_FAIL;
  }

  return SL_STATUS_OK;
}

/* App CLI getting PHY parameters */
static sl_status_t _app_cli_set_phy(const char *value_str,
                                    const char *key_str,
                                    const app_settings_entry_t *entry)
{
  sl_status_t res = SL_STATUS_FAIL;
  int32_t value = 0U;
  (void)key_str;

  if ((value_str == NULL) || (entry == NULL) || (entry->key == NULL)) {
    return res;
  }
  res = _load_common_params_from_phy_cfg();
  if (res != SL_STATUS_OK) {
    return res;
  }

  res = app_util_get_integer((uint32_t *)&value,
                             value_str,
                             entry->input_enum_list,
                             entry->input & APP_SETTINGS_INPUT_FLAG_SIGNED);
  if (res != SL_STATUS_OK) {
    return res;
  }

  // Regulatory domain
  if (strstr(entry->key, APP_CLI_PHY_PARAM_REG_DOMAIN_STR)) {
    _phy_common_params.regulatory_domain = value;

    // Operating class
  } else if (strstr(entry->key, APP_CLI_PHY_PARAM_OP_CLASS_STR)) {
    _phy_common_params.operating_class = value;

    // Operating mode
  } else if (strstr(entry->key, APP_CLI_PHY_PARAM_OP_MODE_STR)) {
    _phy_common_params.operating_mode = value;

#if APP_CLI_ENABLE_EXPLICIT_CONFIG
    // Number of channels
  } else if (strstr(entry->key, APP_CLI_PHY_PARAM_NUM_OF_CH_STR)) {
    _phy_common_params.number_of_channels = value;

    // CH0 Frequency
  } else if (strstr(entry->key, APP_CLI_PHY_PARAM_CH0_FREQ_STR)) {
    _phy_common_params.ch0_frequency = value;

    // Channel spacing
  } else if (strstr(entry->key, APP_CLI_PHY_PARAM_CH_SPACING_STR)) {
    _phy_common_params.channel_spacing = value;
#endif

#if APP_CLI_ENABLE_FAN11_CONFIG
    // Chan plan ID
  } else if (strstr(entry->key, APP_CLI_PHY_PARAM_CH_PLAN_ID_STR)) {
    _phy_common_params.chan_plan_id = value;
#endif

#if APP_CLI_ENABLE_EXPLICIT_CONFIG || APP_CLI_ENABLE_FAN11_CONFIG
    // PHY mode ID
  } else if (strstr(entry->key, APP_CLI_PHY_PARAM_PHY_MODE_ID_STR)) {
    _phy_common_params.phy_mode_id = value;
#endif
    // Not found
  } else {
    return SL_STATUS_FAIL;
  }

  return SL_STATUS_OK;
}

#if defined(SL_CATALOG_WISUN_MODE_SWITCH_PRESENT)
/* App CLI getting mode switch counters */
static sl_status_t _app_ms_get_counters(char *value_str,
                                        const char *key_str,
                                        const app_cli_entry_t *entry)
{
  sl_status_t res = SL_STATUS_FAIL;
  sl_wisun_statistics_t stat;
  (void)key_str;

  if ((value_str == NULL) || (entry == NULL) || (entry->key == NULL)) {
    return res;
  }

  // gets the statsitic that contains the mode switch information
  res = sl_wisun_get_statistics(SL_WISUN_STATISTICS_TYPE_MAC, &stat);

  if (res != SL_STATUS_OK) {
    return res;
  }
  // mode switch TX-RX counters (inc. failed)
  if (strstr(entry->key, "mode_switch_tx_counter")) {
    snprintf(value_str, APP_CLI_STR_VALUE_LENGTH, "%lu", stat.mac.tx_ms_count);
  } else if (strstr(entry->key, "mode_switch_tx_failed_counter")) {
    snprintf(value_str, APP_CLI_STR_VALUE_LENGTH, "%lu", stat.mac.tx_ms_failed_count);
  } else if (strstr(entry->key, "mode_switch_rx_counter")) {
    snprintf(value_str, APP_CLI_STR_VALUE_LENGTH, "%lu", stat.mac.rx_ms_count);
  } else if (strstr(entry->key, "mode_switch_rx_failed_counter")) {
    snprintf(value_str, APP_CLI_STR_VALUE_LENGTH, "%lu", stat.mac.rx_ms_failed_count);
  } else {
  }

  return SL_STATUS_OK;
}
#endif

#if defined(SL_CATALOG_WISUN_APP_CORE_PRESENT)
static sl_status_t _app_set_regulation(const char *value_str,
                                       const char *key_str,
                                       const app_settings_entry_t *entry)
{
  sl_status_t res = SL_STATUS_FAIL;
  uint32_t value = 0U;
  sl_wisun_app_core_reg_thresholds_t thresholds = { 0U };
  sl_wisun_join_state_t join_state = SL_WISUN_JOIN_STATE_DISCONNECTED;
  (void)key_str;
  (void)entry;

  if ((value_str == NULL) || (entry == NULL) || (entry->key == NULL)) {
    return SL_STATUS_FAIL;
  }

  // checking if the device connected or not
  res = sl_wisun_get_join_state(&join_state);
  if (res != SL_STATUS_OK) {
    return res;
  } else {
    if (join_state != SL_WISUN_JOIN_STATE_DISCONNECTED) {
      printf("[Regulation related settings unavailable, disconnection is needed]\n");
      return SL_STATUS_FAIL;
    }
  }

  res = app_util_get_integer(&value,
                             value_str,
                             entry->input_enum_list,
                             entry->input & APP_CLI_INPUT_FLAG_SIGNED);

  if (res != SL_STATUS_OK) {
    printf("[Failed: Get value error: %lu]\n", res);
    return res;
  }

  if (strstr(entry->key, "regulation")) {
    // sets the thresholds
    (void)sl_wisun_app_core_get_regulation_thresholds(&thresholds);
    res = sl_wisun_set_regulation_tx_thresholds(thresholds.warning_threshold,
                                                thresholds.alert_threshold);
    if (res != SL_STATUS_OK) {
      printf("[Failed: unable to set regulation TX thresholds: %lu]\n", res);
      return res;
    }

    // sets regulation
    res = sl_wisun_set_regulation((sl_wisun_regulation_t)value);
    if (res != SL_STATUS_OK) {
      printf("[Regulation not valid]\n");
      return res;
    } else {
      app_regulation = (sl_wisun_regulation_t)value;
    }

    // sets status of regulation
    if ((sl_wisun_regulation_t)value == SL_WISUN_APP_CORE_REGULATION_NONE) {
      sl_wisun_app_core_set_regulation_active(false);
    } else {
      sl_wisun_app_core_set_regulation_active(true);
    }
  }

  return SL_STATUS_OK;
}

static sl_status_t _app_set_regulation_warning_threshold(const char *value_str,
                                                         const char *key_str,
                                                         const app_settings_entry_t *entry)
{
  sl_status_t res = SL_STATUS_FAIL;
  uint32_t value = 0U;
  sl_wisun_app_core_reg_thresholds_t thresholds = { 0U };
  sl_wisun_join_state_t join_state = SL_WISUN_JOIN_STATE_DISCONNECTED;
  (void)key_str;

  if ((value_str == NULL) || (entry == NULL) || (entry->key == NULL)) {
    return SL_STATUS_FAIL;
  }

  // checking if the device connected or not
  res = sl_wisun_get_join_state(&join_state);
  if (res != SL_STATUS_OK) {
    return res;
  } else {
    if (join_state != SL_WISUN_JOIN_STATE_DISCONNECTED) {
      printf("[Regulation related settings unavailable, disconnection is needed]\n");
      return SL_STATUS_FAIL;
    }
  }

  res = app_util_get_integer(&value,
                             value_str,
                             entry->input_enum_list,
                             entry->input & APP_CLI_INPUT_FLAG_SIGNED);

  if (res != SL_STATUS_OK) {
    printf("[Failed: Get value error: %lu]\n", res);
    return res;
  }

  if (strstr(entry->key, "regulation_warning_threshold")) {
    (void)sl_wisun_app_core_get_regulation_thresholds(&thresholds);
    res = sl_wisun_set_regulation_tx_thresholds((int8_t)value, thresholds.alert_threshold);
    if (res != SL_STATUS_OK) {
      printf("[Failed: unable to set regulation TX warning threshold: %lu]\n", res);
      return res;
    } else {
      sl_wisun_app_core_set_regulation_thresholds((int8_t)value, thresholds.alert_threshold);
    }
  }

  return SL_STATUS_OK;
}

static sl_status_t _app_set_regulation_alert_threshold(const char *value_str,
                                                       const char *key_str,
                                                       const app_settings_entry_t *entry)
{
  sl_status_t res = SL_STATUS_FAIL;
  uint32_t value = 0U;
  sl_wisun_app_core_reg_thresholds_t thresholds = { 0U };
  sl_wisun_join_state_t join_state = SL_WISUN_JOIN_STATE_DISCONNECTED;
  (void)key_str;
  (void)entry;

  if ((value_str == NULL) || (entry == NULL) || (entry->key == NULL)) {
    return SL_STATUS_FAIL;
  }

  // checking if the device connected or not
  res = sl_wisun_get_join_state(&join_state);
  if (res != SL_STATUS_OK) {
    return res;
  } else {
    if (join_state != SL_WISUN_JOIN_STATE_DISCONNECTED) {
      printf("[Regulation related settings unavailable, disconnection is needed]\n");
      return SL_STATUS_FAIL;
    }
  }

  res = app_util_get_integer(&value,
                             value_str,
                             entry->input_enum_list,
                             entry->input & APP_CLI_INPUT_FLAG_SIGNED);

  if (res != SL_STATUS_OK) {
    printf("[Failed: Get value error: %lu]\n", res);
    return res;
  }

  if (strstr(entry->key, "regulation_alert_threshold")) {
    (void)sl_wisun_app_core_get_regulation_thresholds(&thresholds);
    res = sl_wisun_set_regulation_tx_thresholds(thresholds.warning_threshold, (int8_t)value);
    if (res != SL_STATUS_OK) {
      printf("[Failed: unable to set regulation TX alert threshold: %lu]\n", res);
      return res;
    } else {
      sl_wisun_app_core_set_regulation_thresholds(thresholds.warning_threshold, (int8_t)value);
    }
  }

  return SL_STATUS_OK;
}

static sl_status_t _app_get_regulation(char *value_str,
                                       const char *key_str,
                                       const app_cli_entry_t *entry)
{
  const app_enum_t *value_enum = NULL;
  (void)key_str;

  if ((value_str == NULL) || (entry == NULL) || (entry->key == NULL)) {
    return SL_STATUS_FAIL;
  }

  if (!strstr(entry->key, "regulation")) {
    return SL_STATUS_FAIL;
  }

  // finds the proper string for the value for regulation
  value_enum = entry->output_enum_list;
  if (value_enum->value_str == NULL) {
    return SL_STATUS_FAIL;
  }

  while (value_enum) {
    if (value_enum->value == app_regulation) {
      // Matching enumeration found
      break;
    }
    value_enum++;
  }

  snprintf(value_str, APP_CLI_STR_VALUE_LENGTH, "%s (%d)",
           value_enum->value_str, (uint8_t)value_enum->value);

  return SL_STATUS_OK;
}

static sl_status_t _app_get_regulation_warning_threshold(char *value_str,
                                                         const char *key_str,
                                                         const app_cli_entry_t *entry)
{
  sl_wisun_app_core_reg_thresholds_t thresholds = { 0U };
  (void)key_str;

  if ((value_str == NULL) || (entry == NULL) || (entry->key == NULL)) {
    return SL_STATUS_FAIL;
  }

  if (strstr(entry->key, "regulation_warning_threshold")) {
    (void)sl_wisun_app_core_get_regulation_thresholds(&thresholds);
    snprintf(value_str, APP_CLI_STR_VALUE_LENGTH, "%d",
             thresholds.warning_threshold);
  }

  return SL_STATUS_OK;
}

static sl_status_t _app_get_regulation_alert_threshold(char *value_str,
                                                       const char *key_str,
                                                       const app_cli_entry_t *entry)
{
  sl_wisun_app_core_reg_thresholds_t thresholds = { 0U };
  (void)key_str;

  if ((value_str == NULL) || (entry == NULL) || (entry->key == NULL)) {
    return SL_STATUS_FAIL;
  }

  if (strstr(entry->key, "regulation_alert_threshold")) {
    (void)sl_wisun_app_core_get_regulation_thresholds(&thresholds);
    snprintf(value_str, APP_CLI_STR_VALUE_LENGTH, "%d",
             thresholds.alert_threshold);
  }

  return SL_STATUS_OK;
}
#endif

#if defined(SL_CATALOG_WISUN_LFN_DEVICE_SUPPORT_PRESENT)
static sl_status_t _app_get_device_type(char *value_str,
                                        const char *key_str,
                                        const app_cli_entry_t *entry)
{
  const char *dev_type_str = NULL;
  sl_wisun_device_type_t dev_type = SL_WISUN_ROUTER;
  (void) entry;
  (void) key_str;

  if (value_str == NULL) {
    return SL_STATUS_FAIL;
  }

  dev_type =  sl_wisun_app_core_get_device_type();
  dev_type_str = app_wisun_trace_util_device_type_to_str((uint32_t) dev_type);

  if (dev_type_str == NULL) {
    return SL_STATUS_FAIL;
  }

  (void) snprintf(value_str, APP_CLI_STR_VALUE_LENGTH, "%s (%lu)", dev_type_str, (uint32_t) dev_type);
  return SL_STATUS_OK;
}

static sl_status_t _app_get_lfn_profile(char *value_str,
                                        const char *key_str,
                                        const app_cli_entry_t *entry)
{
  const char *lfn_profile_str = NULL;
  sl_wisun_lfn_profile_t lfn_profile = SL_WISUN_LFN_PROFILE_TEST;
  (void) entry;
  (void) key_str;

  if (value_str == NULL) {
    return SL_STATUS_FAIL;
  }

  lfn_profile =  sl_wisun_app_core_get_lfn_profile();
  lfn_profile_str = app_wisun_trace_util_lfn_profile_to_str((uint32_t) lfn_profile);

  if (lfn_profile_str == NULL) {
    return SL_STATUS_FAIL;
  }

  (void) snprintf(value_str, APP_CLI_STR_VALUE_LENGTH, "%s (%lu)", lfn_profile_str, (uint32_t) lfn_profile);
  return SL_STATUS_OK;
}
#endif
