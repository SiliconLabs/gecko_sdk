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
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "sl_wisun_trace_util.h"
#include "sl_wisun_types.h"
#include "rail_config.h"

#if defined(SL_CATALOG_FREERTOS_KERNEL_PRESENT)
// FreeRTOS
  #include "FreeRTOS.h"
#else
// MicriumOS
  #include "sl_malloc.h"
#endif

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

///  Size of the IPv6 string
#define IPV6_STRING_SIZE                (40U)

/// Empty IPv6 string
#define IPV6_EMPTY_STRING               "::"

/// Max length of the string of the phy
#define PHY_STR_MAX_LENGTH              (24U)

/// String of the FAN1.0
#define FAN_1_0_STR                     "FAN1.0"

/// String of the FAN1.1
#define FAN_1_1_STR                     "FAN1.1"

/// Print format string for FAN 1.0
#define FAN10_FORMAT_STR                "%s-%u-%x (%s)"

/// Print format string for FAN 1.0
#define FAN11_FORMAT_STR                "%s-%u-%u (%s)"

/// FAN 1.0 version
#define VERSION_WISUN_FAN1_0             0U

/// FAN 1.1 version
#define VERSION_WISUN_FAN1_1             1U

/// FSK PHY mode to operating mode table size
#define FSK_PHY_MODE_TO_OPM_TABLE_SIZE   9U

/// PHY mode minimum value
#define PHY_MODE_MIN_VAL                 1U

/// PHY mode minimum value
#define PHY_MODE_MAX_VAL                 8U

/// Allocate phy list element and return on error macro function
#define __alloc_phy_list_element_and_check(__dst_ptr, __phy_cfg_ptr) \
  do {                                                               \
    (__dst_ptr) = _alloc_phy_list_element(__phy_cfg_ptr);            \
    if (__dst_ptr == NULL) {                                         \
      return NULL;                                                   \
    }                                                                \
  } while (0)

/// PHY type enumeration
typedef enum phy_type {
  /// PHY type FSK
  PHY_TYPE_FSK = 0,
  /// PHY type FSK FEC
  PHY_TYPE_FSK_FEC,
  /// PHY type OFDM1
  PHY_TYPE_OFDM1,
  /// PHY type OFDM2
  PHY_TYPE_OFDM2,
  /// PHY type OFDM3
  PHY_TYPE_OFDM3,
  /// PHY type OFDM4
  PHY_TYPE_OFDM4,
} phy_type_t;

/// RAIL to Wi-SUN OFDM PHY mode ID map element
typedef struct rail_ofdm_phy_mode_id {
  /// RAIL PHY mode ID
  uint8_t rail_phy_mode_id;
  /// Wi-SUN PHY mode ID min
  uint8_t wisun_phy_mode_id_min;
  /// Wi-SUN PHY mode ID max
  uint8_t wisun_phy_mode_id_max;
} rail_ofdm_phy_mode_id_t;

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief Get string key by value from app_enum_t
 * @details Helper function
 * @param[in] app_enum Application enum storage
 * @param[in] val Reference value
 * @return const char* String value
 *****************************************************************************/
static const char *_get_str_key_by_val_from_enum(const app_enum_t * const app_enum,
                                                 const uint32_t val);

/**************************************************************************//**
 * @brief Allocate PHY list element
 * @details Helper function
 * @param[in] phy_cfg PHY config to copy
 * @return app_wisun_phy_list_t* Allocated element ptr or NULL on error
 *****************************************************************************/
static app_wisun_phy_list_t *_alloc_phy_list_element(sl_wisun_phy_config_t *phy_cfg);

/**************************************************************************//**
 * @brief Getting PHY config by channel config entry
 * @details Getting available PHY's configuration by channel config entry
 * @param[in] ch_config_entry channel config
 * @param[out] phy_config pointer of destination of getting
 * @return sl_status_t SL_STATUS_OK if it is successful, otherwise SL_STATUS_FAIL
 *****************************************************************************/
static sl_status_t _get_phy_cfg_from_ch_cfg_entry(const RAIL_ChannelConfigEntry_t * const ch_config_entry,
                                                  sl_wisun_phy_config_t * const phy_config);

/**************************************************************************//**
 * @brief Get PHY type
 * @details Helper function
 * @param[in] phy_mode_id PHY mode ID
 * @return uint8_t PHY type
 *****************************************************************************/
__STATIC_INLINE uint8_t _get_phy_type(const uint8_t phy_mode_id);

/**************************************************************************//**
 * @brief Get PHY mode
 * @details Helper function
 * @param[in] phy_mode_id PHY mode ID
 * @return uint8_t PHY mode
 *****************************************************************************/
__STATIC_INLINE uint8_t _get_phy_mode(const uint8_t phy_mode_id);

/**************************************************************************//**
 * @brief Is FSK PHY
 * @details Helper function
 * @param[in] phy_mode_id PHY mode ID
 * @return bool true ift it's FSK PHY, otherwise false
 *****************************************************************************/
__STATIC_INLINE bool _is_fsk(const uint8_t phy_mode_id);

/**************************************************************************//**
 * @brief Is OFDM PHY
 * @details Helper function
 * @param[in] phy_mode_id PHY mode ID
 * @return bool true ift it's OFDM PHY, otherwise false
 *****************************************************************************/
__STATIC_INLINE bool _is_ofdm(const uint8_t phy_mode_id);

/**************************************************************************//**
 * @brief Check PHY mode ID
 * @details Helper function
 * @param[in] phy_mode_id PHY mode ID
 * @return bool true ift it's valid value, otherwise false
 *****************************************************************************/
__STATIC_INLINE bool _check_phy_mode(const uint8_t phy_mode);

/**************************************************************************//**
 * @brief Get PHY options (Only for FAN1.1 OFDM)
 * @details Helper function. FAN1.1 PHY mode value will be replaced with
 *          Wi-SUN specific value for first option
 * @param[in,out] phy_cfg PHY mode ID
 * @return count onf options for FAN 1.1 OFDM PHYs, otherwise 1
 *****************************************************************************/
static uint8_t _get_phy_options(sl_wisun_phy_config_t * const phy_cfg);

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

/// Application enum for PHY config type
const app_enum_t app_wisun_phy_config_type_enum[] =
{
  { "FAN 1.0", SL_WISUN_PHY_CONFIG_FAN10 },
  { "FAN 1.1", SL_WISUN_PHY_CONFIG_FAN11 },
  { "explicit", SL_WISUN_PHY_CONFIG_EXPLICIT },
  { NULL, 0 }
};

/// Application enum for connection status
const app_enum_t app_wisun_conn_status_enum[] = {
  { "Disconnected", SL_WISUN_JOIN_STATE_DISCONNECTED },
  { "Select PAN", SL_WISUN_JOIN_STATE_SELECT_PAN },
  { "Authenticate", SL_WISUN_JOIN_STATE_AUTHENTICATE },
  { "Acquire PAN Config", SL_WISUN_JOIN_STATE_ACQUIRE_PAN_CONFIG },
  { "Configure Routing", SL_WISUN_JOIN_STATE_CONFIGURE_ROUTING },
  { "Operational", SL_WISUN_JOIN_STATE_OPERATIONAL },
  { NULL, 0 }
};

/// Application enum for regulatory domains of first phy parameter
const app_enum_t app_wisun_phy_reg_domain_enum[] = {
  { "WW", SL_WISUN_REGULATORY_DOMAIN_WW },
  { "NA", SL_WISUN_REGULATORY_DOMAIN_NA },
  { "JP", SL_WISUN_REGULATORY_DOMAIN_JP },
  { "EU", SL_WISUN_REGULATORY_DOMAIN_EU },
  { "CN", SL_WISUN_REGULATORY_DOMAIN_CN },
  { "IN", SL_WISUN_REGULATORY_DOMAIN_IN },
  { "MX", SL_WISUN_REGULATORY_DOMAIN_MX },
  { "BZ", SL_WISUN_REGULATORY_DOMAIN_BZ },
  { "AZ/NZ", SL_WISUN_REGULATORY_DOMAIN_AZ },        // NZ also
  { "KR", SL_WISUN_REGULATORY_DOMAIN_KR },
  { "PH", SL_WISUN_REGULATORY_DOMAIN_PH },
  { "MY", SL_WISUN_REGULATORY_DOMAIN_MY },
  { "HK", SL_WISUN_REGULATORY_DOMAIN_HK },
  { "SG", SL_WISUN_REGULATORY_DOMAIN_SG },
  { "TH", SL_WISUN_REGULATORY_DOMAIN_TH },
  { "VN", SL_WISUN_REGULATORY_DOMAIN_VN },
  { "APPLICATION", SL_WISUN_REGULATORY_DOMAIN_APP },  // application specific domain
  { NULL, 0 }
};

/// Application enum for network size
const app_enum_t app_wisun_nw_size_enum[] = {
  { "automatic", SL_WISUN_NETWORK_SIZE_AUTOMATIC },
  { "small", SL_WISUN_NETWORK_SIZE_SMALL },
  { "medium", SL_WISUN_NETWORK_SIZE_MEDIUM },
  { "large", SL_WISUN_NETWORK_SIZE_LARGE },
  { "test", SL_WISUN_NETWORK_SIZE_TEST },
  { "certification", SL_WISUN_NETWORK_SIZE_CERTIFICATION },
  { NULL, 0 }
};

/// Application enum for regulation
const app_enum_t app_regulation_enum[] = {
  { "none", SL_WISUN_REGULATION_NONE },
  { "arib", SL_WISUN_REGULATION_ARIB },
  { NULL, 0 }
};

const app_enum_t app_wisun_phy_channel_spacing_enum[] = {
  { "100kHz", SL_WISUN_CHANNEL_SPACING_100HZ },
  { "200kHz", SL_WISUN_CHANNEL_SPACING_200HZ },
  { "400kHz", SL_WISUN_CHANNEL_SPACING_400HZ },
  { "600kHz", SL_WISUN_CHANNEL_SPACING_600HZ },
  { NULL, 0 }
};

const app_enum_t app_wisun_device_type_enum[] =
{
  { "FFN", SL_WISUN_ROUTER },
  { "LFN", SL_WISUN_LFN },
  { NULL, 0 }
};

const app_enum_t app_wisun_lfn_profile_enum[] =
{
  { "test", SL_WISUN_LFN_PROFILE_TEST },
  { "balanced", SL_WISUN_LFN_PROFILE_BALANCED },
  { "eco", SL_WISUN_LFN_PROFILE_ECO },
  { NULL, 0 }
};

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

/// FSK phy mode ID to operation mode table
static const uint8_t _fsk_phy_mode_to_op_mode[FSK_PHY_MODE_TO_OPM_TABLE_SIZE] = {
  0xFF, 0x1a, 0x1b, 0x2a, 0x2b, 0x3, 0x4a, 0x4b, 0x5
};

/// Wi-SUN OFDM PHY mode ID map
static const rail_ofdm_phy_mode_id_t _ofdm_phy_map[] = {
  {
    .rail_phy_mode_id = 32,
    .wisun_phy_mode_id_min = 34,
    .wisun_phy_mode_id_max = 39
  },
  {
    .rail_phy_mode_id = 48,
    .wisun_phy_mode_id_min = 51,
    .wisun_phy_mode_id_max = 55
  },
  {
    .rail_phy_mode_id = 64,
    .wisun_phy_mode_id_min = 68,
    .wisun_phy_mode_id_max = 71
  },
  {
    .rail_phy_mode_id = 80,
    .wisun_phy_mode_id_min = 84,
    .wisun_phy_mode_id_max = 87
  }
};

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

void *app_wisun_malloc(size_t size)
{
  void *ptr = NULL;
#if defined(SL_CATALOG_FREERTOS_KERNEL_PRESENT)
  // FreeRTOS
  ptr =  pvPortMalloc(size);
#else
  // MicriumOS
  ptr = sl_malloc(size);
#endif
  return ptr;
}

void app_wisun_free(void *addr)
{
#if defined(SL_CATALOG_FREERTOS_KERNEL_PRESENT)
  // FreeRTOS
  vPortFree(addr);
#else
  // MicriumOS
  sl_free(addr);
#endif
}

const char* app_wisun_trace_util_get_ip_str(const void *const addr)
{
  char *dst = NULL;
  bool ipv6_res = false;

  if (addr == NULL) {
    return IPV6_EMPTY_STRING;
  }

  // allocate string buffer
  dst = app_wisun_malloc(IPV6_STRING_SIZE);
  if (dst == NULL) {
    return IPV6_EMPTY_STRING;
  }

  ipv6_res = ip6tos(addr, dst);  // convert address binary to text for wisun and ipv6
  return ipv6_res ? dst : IPV6_EMPTY_STRING; // dst -> success, empty string -> error;
}

const char * app_wisun_trace_util_conn_state_to_str(const uint32_t val)
{
  return _get_str_key_by_val_from_enum(app_wisun_conn_status_enum, val);
}

const char * app_wisun_trace_util_reg_domain_to_str(const uint32_t val)
{
  return _get_str_key_by_val_from_enum(app_wisun_phy_reg_domain_enum, val);
}

const char * app_wisun_trace_util_nw_size_to_str(const uint32_t val)
{
  return _get_str_key_by_val_from_enum(app_wisun_nw_size_enum, val);
}

const char * app_wisun_trace_util_phy_cfg_type_to_str(const uint32_t val)
{
  return _get_str_key_by_val_from_enum(app_wisun_phy_config_type_enum, val);
}

const char * app_wisun_trace_util_ch_spacing_to_str(const uint32_t val)
{
  return _get_str_key_by_val_from_enum(app_wisun_phy_channel_spacing_enum, val);
}

const char * app_wisun_trace_util_profile_to_str(const uint32_t val)
{
  return _get_str_key_by_val_from_enum(app_wisun_phy_config_type_enum, val);
}

const char * app_wisun_trace_util_device_type_to_str(const uint32_t val)
{
  return _get_str_key_by_val_from_enum(app_wisun_device_type_enum, val);
}

const char * app_wisun_trace_util_lfn_profile_to_str(const uint32_t val)
{
  return _get_str_key_by_val_from_enum(app_wisun_lfn_profile_enum, val);
}

app_wisun_phy_list_t *app_wisun_get_phy_list(app_wisun_phy_filter_t filter)
{
  static sl_wisun_phy_config_t phy_cfg = { 0U };
  app_wisun_phy_list_t *head    = NULL;
  app_wisun_phy_list_t *tail    = NULL;
  app_wisun_phy_list_t *p       = NULL;
  sl_status_t status            = SL_STATUS_OK;
  bool filter_res               = false;
  uint8_t phy_option_cnt        = 0U;

  // Iterate channel configs
  for (uint16_t idx = 0U; channelConfigs[idx] != NULL; ++idx) {
    // Iterate channel config entries
    for (uint16_t ch_entry_idx = 0U; ch_entry_idx < channelConfigs[idx]->length; ++ch_entry_idx) {
      // Get PHY CFG
      status = _get_phy_cfg_from_ch_cfg_entry(&channelConfigs[idx]->configs[ch_entry_idx], &phy_cfg);
      if (status != SL_STATUS_OK) {
        continue;
      }

      // Get count of PHY options. Only FAN1.1 OFDM PHYs has more options
      phy_option_cnt = _get_phy_options(&phy_cfg);
      for (uint8_t opt = 0U; opt < phy_option_cnt; ++opt) {
        if (filter != NULL) {
          filter_res = filter(&phy_cfg);
          if (!filter_res) {
            continue;
          }
        }

        // first element in the list
        if (head == NULL) {
          __alloc_phy_list_element_and_check(head, &phy_cfg);
          continue;
        }

        // allocate new element
        __alloc_phy_list_element_and_check(p, &phy_cfg);

        // move tail to end of the list
        tail = head;
        while (tail->next != NULL) {
          tail = tail->next;
        }
        tail->next = p;

        // increment PHY mode id for FAN11 OFDM PHYs
        if (phy_cfg.type == SL_WISUN_PHY_CONFIG_FAN11) {
          ++phy_cfg.config.fan11.phy_mode_id;
        }
      }
    }
  }

  return head;
}

app_wisun_phy_list_t *app_wisun_filter_phy_list(app_wisun_phy_list_t *list,
                                                app_wisun_phy_filter_t filter)
{
  app_wisun_phy_list_t *head = NULL;
  app_wisun_phy_list_t *tail = NULL;
  app_wisun_phy_list_t *p    = NULL;

  if (list == NULL || filter == NULL) {
    return NULL;
  }

  for (app_wisun_phy_list_t *iter = list; iter != NULL; iter = iter->next) {
    if (!filter(&iter->phy_cfg)) {
      continue;
    }

    // first element in the list
    if (head == NULL) {
      __alloc_phy_list_element_and_check(head, &iter->phy_cfg);
      continue;
    }

    // allocate new element
    __alloc_phy_list_element_and_check(p, &iter->phy_cfg);

    // move tail to end of the list
    tail = head;
    while (tail->next != NULL) {
      tail = tail->next;
    }
    tail->next = p;
  }

  return head;
}

void app_wisun_destroy_phy_list(app_wisun_phy_list_t * list)
{
  app_wisun_phy_list_t *tmp = NULL;
  while (list != NULL) {
    tmp = list;
    list = list->next;
    app_wisun_free((void *)tmp->name);
    app_wisun_free((void *)tmp);
  }
}

const char *app_wisun_phy_to_str(sl_wisun_phy_config_t *phy_cfg)
{
  char *str = NULL;

  str = app_wisun_malloc(PHY_STR_MAX_LENGTH);

  if (str == NULL) {
    return NULL;
  }

  if (phy_cfg->type == SL_WISUN_PHY_CONFIG_FAN10) {
    snprintf(str, PHY_STR_MAX_LENGTH, FAN10_FORMAT_STR,
             app_wisun_trace_util_reg_domain_to_str(phy_cfg->config.fan10.reg_domain),
             phy_cfg->config.fan10.op_class,
             phy_cfg->config.fan10.op_mode,
             FAN_1_0_STR);
  } else if (phy_cfg->type == SL_WISUN_PHY_CONFIG_FAN11) {
    snprintf(str, PHY_STR_MAX_LENGTH, FAN11_FORMAT_STR,
             app_wisun_trace_util_reg_domain_to_str(phy_cfg->config.fan11.reg_domain),
             phy_cfg->config.fan11.chan_plan_id,
             phy_cfg->config.fan11.phy_mode_id,
             FAN_1_1_STR);
  } else {
    app_wisun_free(str);
  }

  return (const char *) str;
}

#if !defined(SL_CATALOG_WISUN_NCP_PRESENT)
const sl_wisun_connection_params_t *sl_wisun_get_conn_param_by_nw_size(const sl_wisun_network_size_t nw_size)
{
  switch (nw_size) {
    // Small
    case SL_WISUN_NETWORK_SIZE_SMALL:
      return &SL_WISUN_PARAMS_PROFILE_SMALL;

    // Medium
    case SL_WISUN_NETWORK_SIZE_MEDIUM:
      return &SL_WISUN_PARAMS_PROFILE_MEDIUM;

    // Large
    case SL_WISUN_NETWORK_SIZE_LARGE:
      return &SL_WISUN_PARAMS_PROFILE_LARGE;

    // Test
    case SL_WISUN_NETWORK_SIZE_TEST:
      return &SL_WISUN_PARAMS_PROFILE_TEST;

    // Certifacete and automatic size are not supported
    default:
      return NULL;
  }
}
#endif

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------

static const char *_get_str_key_by_val_from_enum(const app_enum_t * const app_enum,
                                                 const uint32_t val)
{
  const app_enum_t *p = NULL;

  p = app_enum;
  while (p->value_str != NULL) {
    if (p->value == val) {
      return p->value_str;
    }
    ++p;
  }
  return NULL;
}

static app_wisun_phy_list_t *_alloc_phy_list_element(sl_wisun_phy_config_t *phy_cfg)
{
  app_wisun_phy_list_t *p = NULL;

  p = app_wisun_malloc(sizeof(app_wisun_phy_list_t));
  if (p == NULL) {
    return NULL;
  }

  p->name = app_wisun_phy_to_str(phy_cfg);
  memcpy(&p->phy_cfg, phy_cfg, sizeof(sl_wisun_phy_config_t));
  p->next = NULL;
  return p;
}

static sl_status_t _get_phy_cfg_from_ch_cfg_entry(const RAIL_ChannelConfigEntry_t * const ch_config_entry,
                                                  sl_wisun_phy_config_t * const phy_config)
{
  const uint8_t *stack_info = NULL;
  uint8_t phy_mode = 0U;
  uint8_t phy_type = 0U;

  if (ch_config_entry == NULL) {
    return SL_STATUS_FAIL;
  }

  stack_info = ch_config_entry->stackInfo;
  if (stack_info[0] != RAIL_PTI_PROTOCOL_WISUN) {
    // Not a Wi-SUN configuration
    return SL_STATUS_FAIL;
  }

  phy_type = _get_phy_type(stack_info[1]);
  phy_mode = _get_phy_mode(stack_info[1]);

  switch (stack_info[2]) {
    case VERSION_WISUN_FAN1_0:
      if (!_is_fsk(stack_info[1]) || !_check_phy_mode(phy_mode)) {
        return SL_STATUS_FAIL;
      }
      phy_config->type = SL_WISUN_PHY_CONFIG_FAN10;
      phy_config->config.fan10.reg_domain = stack_info[4];
      phy_config->config.fan10.op_class = stack_info[3];
      phy_config->config.fan10.op_mode = _fsk_phy_mode_to_op_mode[phy_mode];
      phy_config->config.fan10.fec = phy_type == PHY_TYPE_FSK_FEC;
      break;
    case VERSION_WISUN_FAN1_1:
      if (!(_is_fsk(stack_info[1]) || _is_ofdm(stack_info[1]))) {
        return SL_STATUS_FAIL;
      }
      phy_config->type = SL_WISUN_PHY_CONFIG_FAN11;
      phy_config->config.fan11.reg_domain = stack_info[4];
      phy_config->config.fan11.chan_plan_id = stack_info[3];
      phy_config->config.fan11.phy_mode_id = stack_info[1];
      break;
    default:
      // Unsupported version.
      return SL_STATUS_FAIL;
  }

  return SL_STATUS_OK;
}

__STATIC_INLINE uint8_t _get_phy_type(const uint8_t phy_mode_id)
{
  return (phy_mode_id >> 4U) & 0x0FU;
}

__STATIC_INLINE uint8_t _get_phy_mode(const uint8_t phy_mode_id)
{
  return phy_mode_id & 0x0FU;
}

__STATIC_INLINE bool _is_fsk(const uint8_t phy_mode_id)
{
  return (bool)((_get_phy_type(phy_mode_id) == PHY_TYPE_FSK)
                || (_get_phy_type(phy_mode_id) == PHY_TYPE_FSK_FEC));
}

__STATIC_INLINE bool _is_ofdm(const uint8_t phy_mode_id)
{
  return (bool)((_get_phy_type(phy_mode_id) >= PHY_TYPE_OFDM1)
                && (_get_phy_type(phy_mode_id) <= PHY_TYPE_OFDM4));
}

__STATIC_INLINE bool _check_phy_mode(const uint8_t phy_mode)
{
  return (bool)(phy_mode >= PHY_MODE_MIN_VAL && phy_mode <= PHY_MODE_MAX_VAL);
}

static uint8_t _get_phy_options(sl_wisun_phy_config_t * const phy_cfg)
{
  uint8_t phy_option_cnt = 1U;

  if (phy_cfg->type != SL_WISUN_PHY_CONFIG_FAN11) {
    return phy_option_cnt;
  }

  for (uint32_t map_idx = 0; map_idx < (sizeof(_ofdm_phy_map) / sizeof(rail_ofdm_phy_mode_id_t)); ++map_idx) {
    if (phy_cfg->config.fan11.phy_mode_id == _ofdm_phy_map[map_idx].rail_phy_mode_id) {
      // Corrigate first PHY mode ID
      phy_cfg->config.fan11.phy_mode_id = _ofdm_phy_map[map_idx].wisun_phy_mode_id_min;
      return _ofdm_phy_map[map_idx].wisun_phy_mode_id_max - _ofdm_phy_map[map_idx].wisun_phy_mode_id_min + 1U;
    }
  }

  return phy_option_cnt;
}
