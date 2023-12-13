/***************************************************************************//**
 * @file
 * @brief Wi-SUN Application Core Component
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

#ifndef __SL_WISUN_APP_CORE_H__
#define __SL_WISUN_APP_CORE_H__

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @addtogroup SL_WISUN_APP_CORE_API Application Core
 * @{
 *****************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "socket/socket.h"
#include "sl_wisun_event_mgr.h"
#include "sl_component_catalog.h"
#if defined(SL_CATALOG_WISUN_LFN_DEVICE_SUPPORT_PRESENT)
  #include "sl_wisun_lfn_params_api.h"
#endif

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @addtogroup SL_WISUN_APP_CORE_API_TYPES Application Core API type definitions
 * @ingroup SL_WISUN_APP_CORE_API
 * @{
 *****************************************************************************/

/// Error flag bits enum type definition
typedef enum app_core_error_state_flag{
  /// Setting Error Flag bit
  SETTING_ERROR_FLAG_BIT = 0,
  /// Connection Failed Error Flag bit
  CONNECTION_FAILED_ERROR_FLAG_BIT,
  /// Network Size Error Flag bit
  SET_NETWORK_SIZE_ERROR_FLAG_BIT,
  /// TX Power Error Flag bit
  SET_TX_POWER_ERROR_FLAG_BIT,
  /// Dwel interval Error flag bit
  SET_DWELL_INTERVAL_ERROR_FLAG_BIT,
  /// Setting MAC address Error Flag bit
  SET_MAC_ADDR_ERROR_FLAG_BIT,
  /// setting Allow mac address Error Flag bit
  SET_ALLOW_MAC_ADDR_ERROR_FLAG_BIT,
  /// setting Deny mac address Error Flag bit
  SET_DENY_MAC_ADDR_ERROR_FLAG_BIT,
  /// Trusted Certificate Error Flag bit
  SET_TRUSTED_CERTIFICATE_ERROR_FLAG_BIT,
  /// Device Certificate Error Flag bit
  SET_DEVICE_CERTIFICATE_ERROR_FLAG_BIT,
  /// Device Private Key Error Flag bit
  SET_DEVICE_PRIVATE_KEY_ERROR_FLAG_BIT,
  /// Get RF Setting Error Flag bit
  GET_RF_SETTINGS_ERROR_FLAG_BIT,
} app_core_error_state_flag_t;

/// Current address storage structure definition
typedef struct current_addr {
  /// Link local address
  in6_addr_t link_local;
  /// Global address
  in6_addr_t global;
  /// Border Router address
  in6_addr_t border_router;
  /// Primary Parent address
  in6_addr_t primary_parent;
  /// Secondary Parent address
  in6_addr_t secondary_parent;
} current_addr_t;

/// Regulation thresholds
typedef struct regulation_thresholds {
  /// Warning thresholds
  int8_t warning_threshold;
  /// Alert thresholds
  int8_t alert_threshold;
} regulation_thresholds_t;

/// Application time statistic
typedef struct app_core_time_stat {
  /// Current ms
  uint64_t curr_ms;
  /// Last connected ms
  uint64_t connected_ms;
  /// Total connected ms
  uint64_t tot_connected_ms;
  /// Last disconnected ms
  uint64_t disconnected_ms;
  /// Total disconnected ms
  uint64_t tot_disconnected_ms;
  /// Connection counter
  uint32_t conn_cnt;
} app_core_time_stat_t;

/** @} (end SL_WISUN_APP_CORE_API_TYPES) */
// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief Initialize Wi-SUN application core.
 * @details Initializing mutex, socket handler and set Wi-SUN settings.
 *****************************************************************************/
void app_wisun_core_init(void);

/**************************************************************************//**
 * @brief Get application core error.
 * @details The function retrieves the application core error status based on
 *          the flag.
 * @param[in] flag is the indicator of the error
 * @return bool True if error flag is set, otherwise false
 *****************************************************************************/
bool app_wisun_core_get_error(app_core_error_state_flag_t flag);

/**************************************************************************//**
 * @brief Connect to the Wi-SUN network.
 * @details Network initialization and connection.
 *          The function initializes the network with parameters
 *          (Network name, TX Power, Network size, etc.)
 *          by the stored settings in NVM
 *          if the settings component is added to the project,
 *          otherwise with the default settings.
 *****************************************************************************/
void app_wisun_network_connect(void);

/**************************************************************************//**
 * @brief Get the current addresses.
 * @details Copy cached addresses into destination.
 * @param[out] dest_addresses Destination
 *****************************************************************************/
void app_wisun_get_current_addresses(current_addr_t * const dest_addresses);

/**************************************************************************//**
 * @brief Set the regional regulation to active or passive.
 * @details After a stack API call for regional regulation, this function can
 * be used to store the status of the regulation (active or not).
 * @param[in] enabled (true = active, false = not active)
 *****************************************************************************/
void app_wisun_set_regulation_active(bool enabled);

/**************************************************************************//**
 * @brief Return the state of the regional regulation.
 * @details This function tells the caller if a regulation is currently active.
 * @return Boolean indicating if a regional regulation is currently active.
 *****************************************************************************/
bool app_wisun_get_regulation_active(void);

/**************************************************************************//**
 * @brief Get the remaining budget from the transmission quota.
 * @details Returns the state of the regional regulation and the remaining
 * budget in ms if applicable, or zero budget if exceeded or not regulated.
 * @param[out] budget_out pointer to return the remaining budget to.
 * @return Boolean to indicate if the returned value reflects a usable value.
 *****************************************************************************/
bool app_wisun_get_remaining_tx_budget(uint32_t* const budget_out);

/**************************************************************************//**
 * @brief Set up warning and alert thresholds for the regional regulation.
 * @details Sets up the percentages of warnings and alerts where the regulation
 * indicate that the transmission quota is approached/exceeded.
 * @param[in] warning_level new percentage for the warning threshold
 * @param[in] alert_level new percentage for the alert threshold
 *****************************************************************************/
void app_wisun_set_regulation_thresholds(const int8_t warning_level, const int8_t alert_level);

/**************************************************************************//**
 * @brief Get the warning and alert levels for approaching/exceeded the TX budget.
 * @details Values representing percentages of the allowed transmission quota in
 * ms are returned for the warning and alert levels, respectively.
 * @param[out] thresholds_out pointer to the struct to hold the thresholds
 * @return Boolean to indicate if the operation was successful
 *****************************************************************************/
bool app_wisun_get_regulation_thresholds(regulation_thresholds_t* thresholds_out);

/**************************************************************************//**
 * @brief Get Wi-SUN join state.
 * @details Thread-safe getter to get connection state.
 *          Join state is stored in appropriate event callback.
 * @return sl_wisun_join_state_t Join state value.
 *****************************************************************************/
sl_wisun_join_state_t app_wisun_get_join_state(void);

/**************************************************************************//**
 * @brief Get time statistic
 * @details Create a copy of time statistic storage with up-to-date values
 * @param[out] tstat Time statistic structure
 *****************************************************************************/
void app_wisun_get_time_stat(app_core_time_stat_t * const tstat);

#if defined(SL_CATALOG_WISUN_LFN_DEVICE_SUPPORT_PRESENT)

/**************************************************************************//**
 * @brief Get Wi-SUN device type
 * @details Getter to get device type.
 *          Device type can be SL_WISUN_LFN or SL_WISUN_ROUTER (FFN)
 * @return l_wisun_device_type_t Device type.
 *****************************************************************************/
sl_wisun_device_type_t app_wisun_get_device_type(void);

/**************************************************************************//**
 * @brief Get Wi-SUN LFN profile
 * @details Getter to get LFN profile.
 *          Device type can be SL_WISUN_LFN_PROFILE_TEST,
 *          SL_WISUN_LFN_PROFILE_BALANCED or SL_WISUN_LFN_PROFILE_ECO
 * @return sl_wisun_lfn_profile_t LFN profile.
 *****************************************************************************/
sl_wisun_lfn_profile_t app_wisun_get_lfn_profile(void);

/**************************************************************************//**
 * @brief Get LFN parameters
 * @return sl_wisun_lfn_params_t pointer to the set profile paramaters of LFN.
 *****************************************************************************/
const sl_wisun_lfn_params_t *app_wisun_get_lfn_params(void);
#endif

/** @}*/

#ifdef __cplusplus
}
#endif
#endif
