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

#include <stddef.h>
#include <string.h>
#include <assert.h>
#include "sl_status.h"
#include "sl_string.h"
#include "cmsis_os2.h"
#include "sl_cmsis_os2_common.h"
#include "sl_wisun_api.h"
#include "sl_wisun_cli_settings.h"
#include "sl_wisun_app_setting.h"
#include "sl_wisun_trace_util.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

/// Settings notification error bit
#define APP_SETTINGS_NOTIFICATION_ERROR_FLAG_BIT    31U

/// Settings notification error flag mask
#define APP_SETTINGS_NOTIFICATION_ERROR_FLAG_MSK    (1U << APP_SETTINGS_NOTIFICATION_ERROR_FLAG_BIT)

/// Default Network name for initialization
#define APP_SETTINGS_DEFAULT_NETWORK_NAME           "Wi-SUN Network"

/// Setting notification descriptor
typedef struct app_setting_notif_dsc {
  /// Event ID
  osEventFlagsId_t evt_id;
  /// Notification type
  app_setting_notification_t type;
  /// Subscribed channels
  uint32_t subscribed_chs;
} app_setting_notif_dsc_t;

/// Count of available notifications
#define APP_SETTINGS_NOTIFICATION_COUNT             4UL

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief Acquire application mutex
 * @details Internal mutex lock
 *****************************************************************************/
__STATIC_INLINE void _app_wisun_mutex_acquire(void);

/**************************************************************************//**
 * @brief Release application mutex
 * @details Internal mutex release
 *****************************************************************************/
__STATIC_INLINE void _app_wisun_mutex_release(void);

/**************************************************************************//**
 * @brief Helper function for checking the name of the Wi-SUN network
 * @param [in] *name is the network name that are wanted to check
 * @param [out] *name_len is the length of the name that calculated by the function.
 * @return char* const char pointer that points to checked name or to the default
 *          one if the checked one is incorrect.
 *****************************************************************************/
static const char* _app_check_nw_name(const char *name, size_t *const name_len);

/**************************************************************************//**
 * @brief Get notification entry from table
 * @details Helper function
 * @param[in] type Notification type
 * @return app_setting_notif_dsc_t* Notification entry on success or NULL on error
 *****************************************************************************/
static app_setting_notif_dsc_t *_get_notification_entry(app_setting_notification_t type);

/**************************************************************************//**
 * @brief App setting notify
 * @details Notify subsribed channels about settings calls
 * @param[in] notif Notification type
 * @return sl_status_t SL_STATUS_OK on success, otherwise SL_STATUS_FAIL
 *****************************************************************************/
static sl_status_t _setting_notify(app_setting_notification_t notif);

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

/// App settings mutex
static osMutexId_t _app_wisun_setting_mtx;

///  App settings mutex attribute
static const osMutexAttr_t _app_wisun_setting_mtx_attr = {
  .name      = "AppWisunSettingMutex",
  .attr_bits = osMutexRecursive,
  .cb_mem    = NULL,
  .cb_size   = 0
};

/// Settings event flags attributes
static const osEventFlagsAttr_t _wisun_setting_evt_attr = {
  .name      = "AppWisunSettingEvtFlags",
  .attr_bits = 0,
  .cb_mem    = NULL,
  .cb_size   = 0
};

/// Wi-SUN application settings
static app_setting_wisun_t _wisun_app_settings = { 0 };

/// Default settings structure
static const app_setting_wisun_t wisun_app_settings_default = {
#if defined(WISUN_CONFIG_NETWORK_NAME)
  .network_name = WISUN_CONFIG_NETWORK_NAME,
#else
  .network_name = APP_SETTINGS_DEFAULT_NETWORK_NAME,
#endif
#if defined(WISUN_CONFIG_NETWORK_SIZE)
  .network_size = WISUN_CONFIG_NETWORK_SIZE,
#else
  .network_size = SL_WISUN_NETWORK_SIZE_SMALL,
#endif
#if defined(WISUN_CONFIG_TX_POWER)
  .tx_power = WISUN_CONFIG_TX_POWER,
#else
  .tx_power = 20U,
#endif
  .is_default_phy = true,
#if defined(WISUN_CONFIG_DEVICE_TYPE)
  .device_type = WISUN_CONFIG_DEVICE_TYPE,
#else
  .device_type = SL_WISUN_ROUTER,
#endif
#if defined(WISUN_CONFIG_DEVICE_PROFILE)
  .lfn_profile = WISUN_CONFIG_DEVICE_PROFILE,
#else
  .lfn_profile = SL_WISUN_LFN_PROFILE_TEST,
#endif
#if defined(WISUN_CONFIG_DEFAULT_PHY_FAN10)
  .phy = {
    .type = SL_WISUN_PHY_CONFIG_FAN10,
    .config.fan10.reg_domain = WISUN_CONFIG_REGULATORY_DOMAIN,
    .config.fan10.op_class = WISUN_CONFIG_OPERATING_CLASS,
    .config.fan10.op_mode = WISUN_CONFIG_OPERATING_MODE,
  },
#elif defined(WISUN_CONFIG_DEFAULT_PHY_FAN11)
  .phy = {
    .type = SL_WISUN_PHY_CONFIG_FAN11,
    .config.fan11.reg_domain = WISUN_CONFIG_REGULATORY_DOMAIN,
    .config.fan11.chan_plan_id = WISUN_CONFIG_CHANNEL_PLAN_ID,
    .config.fan11.phy_mode_id = WISUN_CONFIG_PHY_MODE_ID,
  },
#else
  .phy = { 0 },
#endif
};

/// Notifications
static app_setting_notif_dsc_t _notifications[APP_SETTINGS_NOTIFICATION_COUNT] = {
  {
    .type = APP_SETTING_NOTIFICATION_SET_NETWORK_NAME,
    .evt_id = NULL,
    .subscribed_chs = (1U << APP_SETTING_DEFAULT_SUBSCRIPT_CH),
  },
  {
    .type = APP_SETTING_NOTIFICATION_SET_NETWORK_SIZE,
    .evt_id = NULL,
    .subscribed_chs = (1U << APP_SETTING_DEFAULT_SUBSCRIPT_CH),
  },
  {
    .type = APP_SETTING_NOTIFICATION_SET_TX_POWER,
    .evt_id = NULL,
    .subscribed_chs = (1U << APP_SETTING_DEFAULT_SUBSCRIPT_CH),
  },
  {
    .type = APP_SETTING_NOTIFICATION_SET_PHY_CFG,
    .evt_id = NULL,
    .subscribed_chs = (1U << APP_SETTING_DEFAULT_SUBSCRIPT_CH),
  }
};

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

///  Wi-SUN application network saving settings
const app_saving_item_t network_saving_settings = {
  .data = &_wisun_app_settings,
  .data_size = sizeof(_wisun_app_settings),
  .default_val = &wisun_app_settings_default
};

/// Wi-SUN application all saved data
const app_saving_item_t *saving_settings[] = {
  &network_saving_settings,
  NULL
};

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

/* Initialization of Wi-SUN setting */
void app_wisun_setting_init(void)
{
  // init wisun settings mutex
  _app_wisun_setting_mtx = osMutexNew(&_app_wisun_setting_mtx_attr);
  assert(_app_wisun_setting_mtx != NULL);

  // init wisun settings event flags
  for (size_t idx = 0; idx < APP_SETTINGS_NOTIFICATION_COUNT; ++idx) {
    _notifications[idx].evt_id = osEventFlagsNew(&_wisun_setting_evt_attr);
    assert(_notifications[idx].evt_id != NULL);
  }
}

/* Get setting */
sl_status_t app_wisun_setting_get(app_setting_wisun_t *const wisun_setting)
{
  sl_status_t res = SL_STATUS_OK;

  if (wisun_setting == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  // create a deepcopy of setting
  _app_wisun_mutex_acquire();
  memcpy(wisun_setting, &_wisun_app_settings, sizeof(app_setting_wisun_t));
  _app_wisun_mutex_release();

  return res;
}

/* Setting Wi-SUN network name */
sl_status_t app_wisun_setting_set_network_name(const char *const name)
{
  const char *network_name = NULL;
  size_t name_len = 0U;
  sl_status_t stat = SL_STATUS_FAIL;

  if (name == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  _app_wisun_mutex_acquire();
  // check the network name, and return checked name.
  network_name = _app_check_nw_name(name, &name_len);

  if (name_len < MAX_SIZE_OF_NETWORK_NAME) {
    memcpy(_wisun_app_settings.network_name, network_name, name_len);
    _wisun_app_settings.network_name[name_len] = 0U;
  } else {
    _app_wisun_mutex_release();
    return SL_STATUS_FAIL;
  }

  stat = _setting_notify(APP_SETTING_NOTIFICATION_SET_NETWORK_NAME);
  _app_wisun_mutex_release();

  return stat;
}

/* Setting Wi-SUN network size */
sl_status_t app_wisun_setting_set_network_size(const uint8_t *const size)
{
  sl_status_t stat = SL_STATUS_FAIL;

  if (size == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  _app_wisun_mutex_acquire();
  _wisun_app_settings.network_size = *size;
  stat = _setting_notify(APP_SETTING_NOTIFICATION_SET_NETWORK_SIZE);
  _app_wisun_mutex_release();

  return stat;
}

/* Setting Wi-SUN TX power */
sl_status_t app_wisun_setting_set_tx_power(const int8_t *const tx_power)
{
  sl_status_t stat = SL_STATUS_FAIL;

  if (tx_power == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  _app_wisun_mutex_acquire();

  _wisun_app_settings.tx_power = *tx_power;

  stat = _setting_notify(APP_SETTING_NOTIFICATION_SET_TX_POWER);

  _app_wisun_mutex_release();

  return stat;
}

/* Setting Wi-SUN PHY */
sl_status_t app_wisun_setting_set_phy(const sl_wisun_phy_config_t *const phy)
{
  sl_status_t stat = SL_STATUS_FAIL;

  if (phy == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  _app_wisun_mutex_acquire();
  _wisun_app_settings.is_default_phy = false;
  memcpy(&_wisun_app_settings.phy, phy, sizeof(sl_wisun_phy_config_t));

  // Set notifiication
  stat = _setting_notify(APP_SETTING_NOTIFICATION_SET_PHY_CFG);

  _app_wisun_mutex_release();

  return stat;
}

/* Getting network name */
sl_status_t app_wisun_setting_get_network_name(char *const name, uint8_t size)
{
  uint8_t name_len = 0U;

  if ((name == NULL) || (size < MAX_SIZE_OF_NETWORK_NAME)) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  _app_wisun_mutex_acquire();

  name_len = (uint8_t)sl_strlen(_wisun_app_settings.network_name);

  if (name_len < MAX_SIZE_OF_NETWORK_NAME) {
    memset(name, 0U, MAX_SIZE_OF_NETWORK_NAME);
    memcpy(name, _wisun_app_settings.network_name, name_len);
  } else {
    return SL_STATUS_FAIL;
  }

  _app_wisun_mutex_release();
  return SL_STATUS_OK;
}

/* Getting network size */
sl_status_t app_wisun_setting_get_network_size(uint8_t *const size)
{
  if (size == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  _app_wisun_mutex_acquire();
  *size = _wisun_app_settings.network_size;
  _app_wisun_mutex_release();

  return SL_STATUS_OK;
}

/* Getting TX power */
sl_status_t app_wisun_setting_get_tx_power(int8_t *const tx_power)
{
  if (tx_power == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  _app_wisun_mutex_acquire();
  *tx_power = _wisun_app_settings.tx_power;
  _app_wisun_mutex_release();

  return SL_STATUS_OK;
}

/* Getting PHY */
sl_status_t app_wisun_setting_get_phy(sl_wisun_phy_config_t *const phy)
{
  if (phy == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  _app_wisun_mutex_acquire();
  memcpy(phy, &_wisun_app_settings.phy, sizeof(sl_wisun_phy_config_t));
  _app_wisun_mutex_release();

  return SL_STATUS_OK;
}

sl_status_t app_wisun_setting_init_phy_cfg(void)
{
  sl_status_t stat = SL_STATUS_OK;

  if (_wisun_app_settings.is_default_phy) {
    // Full radio config: create a copy of already prepared phy config with default settings
    memcpy(&_wisun_app_settings.phy, &wisun_app_settings_default.phy, sizeof(sl_wisun_phy_config_t));
  }

  // Set notifiications
  stat  = _setting_notify(APP_SETTING_NOTIFICATION_SET_PHY_CFG);

  return stat;
}

sl_status_t app_wisun_setting_subscribe_notification(const app_setting_notification_t type,
                                                     uint8_t * const channel)
{
  sl_status_t stat = SL_STATUS_FAIL;
  app_setting_notif_dsc_t *notif = NULL;
  uint32_t mask = 0UL;
  notif = _get_notification_entry(type);
  if (notif == NULL || channel == NULL) {
    return stat;
  }

  _app_wisun_mutex_acquire();
  for (uint8_t i = 0U; i < sizeof(notif->subscribed_chs) * 8U; ++i) {
    mask = (1U << i);
    if (i != APP_SETTINGS_NOTIFICATION_ERROR_FLAG_BIT
        && !(notif->subscribed_chs & mask)) {
      *channel = i;
      notif->subscribed_chs |= mask;
      stat = SL_STATUS_OK;
      break;
    }
  }
  _app_wisun_mutex_release();

  return stat;
}

bool app_wisun_setting_is_notified(const app_setting_notification_t type,
                                   const uint8_t channel)
{
  uint32_t flags = 0UL;
  app_setting_notif_dsc_t *notif = NULL;

  notif = _get_notification_entry(type);
  if (notif == NULL) {
    return false;
  }
  flags = osEventFlagsWait(notif->evt_id, (1U << channel), osFlagsNoClear, 0UL);

  return (flags & APP_SETTINGS_NOTIFICATION_ERROR_FLAG_MSK)
         ? false : (bool) (flags & (1U << channel));
}

void app_wisun_setting_unsubscribe(const app_setting_notification_t type,
                                   const uint8_t channel)
{
  app_setting_notif_dsc_t *notif = NULL;

  notif = _get_notification_entry(type);
  if (notif == NULL) {
    return;
  }

  _app_wisun_mutex_acquire();
  notif->subscribed_chs &= ~(1U << channel);
  _app_wisun_mutex_release();
}

void app_wisun_setting_ack_notification(const app_setting_notification_t type,
                                        const uint8_t channel)
{
  app_setting_notif_dsc_t *notif = NULL;

  notif = _get_notification_entry(type);
  if (notif == NULL) {
    return;
  }

  (void) osEventFlagsClear(notif->evt_id, 1U << channel);
}

static sl_status_t _setting_notify(const app_setting_notification_t type)
{
  app_setting_notif_dsc_t *notif = NULL;
  uint32_t flags = 0UL;

  notif = _get_notification_entry(type);
  if (notif == NULL) {
    return SL_STATUS_FAIL;
  }
  flags = osEventFlagsSet(notif->evt_id, notif->subscribed_chs);
  if (flags & APP_SETTINGS_NOTIFICATION_ERROR_FLAG_MSK) {
    return SL_STATUS_FAIL;
  }
  return SL_STATUS_OK;
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------

/* Mutex acquire */
__STATIC_INLINE void _app_wisun_mutex_acquire(void)
{
  assert(osMutexAcquire(_app_wisun_setting_mtx, osWaitForever) == osOK);
}

/* Mutex release */
__STATIC_INLINE void _app_wisun_mutex_release(void)
{
  assert(osMutexRelease(_app_wisun_setting_mtx) == osOK);
}

static const char* _app_check_nw_name(const char *name, size_t *const name_len)
{
  const char* ret_name = APP_SETTINGS_DEFAULT_NETWORK_NAME;

  *name_len = sl_strnlen((char*)name, SL_WISUN_NETWORK_NAME_SIZE);
  if (!(*name_len < SL_WISUN_NETWORK_NAME_SIZE) || (*name_len == 0) ) {
    // sets the default name and its size
    ret_name = APP_SETTINGS_DEFAULT_NETWORK_NAME;
    *name_len = sl_strnlen(APP_SETTINGS_DEFAULT_NETWORK_NAME, SL_WISUN_NETWORK_NAME_SIZE);
    printf("\r\n[Warning: The name of Wi-SUN network is incorrect, default name used, \"%s\" ]\r\n", ret_name);
  } else {
    ret_name = name;
  }

  return ret_name;
}

static app_setting_notif_dsc_t *_get_notification_entry(app_setting_notification_t type)
{
  for (size_t idx = 0; idx < APP_SETTINGS_NOTIFICATION_COUNT; ++idx) {
    if (_notifications[idx].type == type) {
      return &_notifications[idx];
    }
  }
  return NULL;
}
