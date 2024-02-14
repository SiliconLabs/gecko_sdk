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

#ifndef __SL_WISUN_TRACE_UTIL_H__
#define __SL_WISUN_TRACE_UTIL_H__

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "cmsis_os2.h"
#include "sl_cmsis_os2_common.h"
#include "sl_component_catalog.h"
#include "sl_status.h"
#include "sl_wisun_ip6string.h"
#include "sl_wisun_types.h"
#if !defined(SL_CATALOG_WISUN_NCP_PRESENT)
  #include "sl_wisun_connection_params_api.h"
#endif
// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

/// Thread loop definition
#ifndef SL_WISUN_THREAD_LOOP
  #define SL_WISUN_THREAD_LOOP  while (1)
#endif

/**************************************************************************//**
 * @brief Macro to check a status and print a message if the state is not OK
 * @details Use this print a short message on any location where unhandled state
 *          should be noted.
 * @param[in] __status The status value or variable to compare
 * @return None
 *****************************************************************************/
#if !defined(__CHECK_FOR_STATUS)
#define __CHECK_FOR_STATUS(__status)                                       \
  do {                                                                     \
    if (__status != SL_STATUS_OK) {                                        \
      printf("%s() returned = 0x%08lx \n", __PRETTY_FUNCTION__, __status); \
    }                                                                      \
  } while (0)
#endif

/// Structure for using enum on the CLI
typedef struct {
  /// String value
  char *value_str;
  /// Integer value
  uint32_t value;
} app_enum_t;

/// Application PHY list descriptor
typedef struct app_wisun_phy_list {
  /// String representation of the PHY
  const char *name;
  /// PHY configration
  sl_wisun_phy_config_t phy_cfg;
  /// Next ptr
  struct app_wisun_phy_list *next;
} app_wisun_phy_list_t;

/// Application PHY list filter callback type definition
typedef bool (*app_wisun_phy_filter_t)(sl_wisun_phy_config_t *phy_cfg);

/// Time structure definition
typedef struct sl_wisun_trace_util_time {
  /// Time stamp in milisec
  uint64_t tot_milisecs;
  /// Days
  uint16_t days;
  /// Hours
  uint8_t hours;
  /// Minutes
  uint8_t minutes;
  /// Seconds
  uint8_t seconds;
} sl_wisun_trace_util_time_t;

/// Event notification
typedef struct app_wisun_trace_util_evt_notify {
  /// Event ID
  osEventFlagsId_t evt_id;
  /// Registered event channels
  uint32_t evt_chs;
  /// Wait options
  uint32_t wait_opt;
} app_wisun_trace_util_evt_notify_t;

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

/// PHY configration type enum
extern const app_enum_t app_wisun_phy_config_type_enum[];

/// Connection status enum
extern const app_enum_t app_wisun_conn_status_enum[];

/// Regulatory domain/PHY enum
extern const app_enum_t app_wisun_phy_reg_domain_enum[];

/// Network size enum
extern const app_enum_t app_wisun_nw_size_enum[];

/// Regulation enum
extern const app_enum_t app_regulation_enum[];

/// Channel spacing
extern const app_enum_t app_wisun_phy_channel_spacing_enum[];

/// Device type
extern const app_enum_t app_wisun_device_type_enum[];

/// LFN profile
extern const app_enum_t app_wisun_lfn_profile_enum[];

// -----------------------------------------------------------------------------
//                          Public Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief App wisun malloc wrapper
 * @details Wrapper for cover operating systems
 * @param size Size of expected allocation
 * @return void* Allocatod memory start address on success, NULL on error
 *****************************************************************************/
void *app_wisun_malloc(size_t size);

/**************************************************************************//**
 * @brief App wisun free warpper
 * @details Wrapper for cover operating systems
 * @param addr Address on heap to set free
 *****************************************************************************/
void app_wisun_free(void *addr);

/**************************************************************************//**
 * @brief Get IP address.
 * @details Uses the internal circular buffer
 * @param[in] value IP address raw byte values
 * @return const char* converted string ptr
 *****************************************************************************/
const char* app_wisun_trace_util_get_ip_str(const void *const addr);

/**************************************************************************//**
 * @brief Destroy allocated string buffer
 * @details Wrapper function of free
 * @param str String buffer ptr
 *****************************************************************************/
__STATIC_INLINE void app_wisun_trace_util_destroy_ip_str(const char * const str)
{
  app_wisun_free((void *) str);
}

/**************************************************************************//**
 * @brief Convert connection state enum values to string.
 * @details Converter function
 * @param[in] val Value to find
 * @return const char* String value
 *****************************************************************************/
const char* app_wisun_trace_util_conn_state_to_str(const uint32_t val);

/**************************************************************************//**
 * @brief Convert regulatory domain enum values to string.
 * @details Converter function
 * @param[in] val Value to find
 * @return const char* String value
 *****************************************************************************/
const char * app_wisun_trace_util_reg_domain_to_str(const uint32_t val);

/**************************************************************************//**
 * @brief Convert network size enum values to string.
 * @details Converter function
 * @param[in] val Value to find
 * @return const char* String value
 *****************************************************************************/
const char * app_wisun_trace_util_nw_size_to_str(const uint32_t val);

/**************************************************************************//**
 * @brief Convert PHY config type to string
 * @details Converter function
 * @param val Value to find
 * @return const char* String value
 *****************************************************************************/
const char * app_wisun_trace_util_phy_cfg_type_to_str(const uint32_t val);

/**************************************************************************//**
 * @brief Convert Channel Spacing to string
 * @details Converter function
 * @param val Value to find
 * @return const char* String value
 *****************************************************************************/
const char * app_wisun_trace_util_ch_spacing_to_str(const uint32_t val);

/**************************************************************************//**
 * @brief Convert Profile to string
 * @details Converter function
 * @param val Value to find
 * @return const char* String value
 *****************************************************************************/
const char * app_wisun_trace_util_profile_to_str(const uint32_t val);

/**************************************************************************//**
 * @brief Convert Device type to string
 * @details Converter function
 * @param val Value to find
 * @return const char* String value
 *****************************************************************************/
const char * app_wisun_trace_util_device_type_to_str(const uint32_t val);

/**************************************************************************//**
 * @brief Convert LFN profile to string
 * @details Converter function
 * @param val Value to find
 * @return const char* String value
 *****************************************************************************/
const char * app_wisun_trace_util_lfn_profile_to_str(const uint32_t val);

/**************************************************************************//**
 * @brief Swapping short unsigned integer endianess
 * @details It swaps the value pointed.
 * @param[in] num The swappng number
 * @return uint16_t integer
 *****************************************************************************/
__STATIC_INLINE uint16_t app_wisun_trace_swap_u16(uint16_t num)
{
  return (((num & 0xFF) << 8) | ((num & 0xFF00) >> 8));
}

/**************************************************************************//**
 * @brief Getting PHY list
 * @details It obtains all available PHYs in a list.
 * @param[in] filter is a function that defines the filter conditions
 * @return app_wisun_phy_list_t pointer of the allocated list, NULL on failure
 *****************************************************************************/
app_wisun_phy_list_t *app_wisun_get_phy_list(app_wisun_phy_filter_t filter);

/**************************************************************************//**
 * @brief Filter PHY list
 * @details Filtering existing PHY list.
 * @param[in] list PHY list
 * @param[in] filter Filter
 * @return app_wisun_phy_list_t* pointer of the allocated list, NULL on failure
 *****************************************************************************/
app_wisun_phy_list_t *app_wisun_filter_phy_list(app_wisun_phy_list_t *list,
                                                app_wisun_phy_filter_t filter);

/**************************************************************************//**
 * @brief Destroying the PHY list
 * @details It free the allocated list.
 * @param[in] list is a pointer of the list
 *****************************************************************************/
void app_wisun_destroy_phy_list(app_wisun_phy_list_t *list);

/**************************************************************************//**
 * @brief Getting the name of PHY
 * @details It give back the name of the PHY in string.
 * @param[in] phy_cfg is a pointer of a PHY configuration.
 * @return char* a string that is the name of the given PHY configuration.
 *****************************************************************************/
const char *app_wisun_phy_to_str(sl_wisun_phy_config_t *phy_cfg);

/**************************************************************************//**
 * @brief MAC address to string
 * @details Convert MAC address bytes to string
 * @param[in] mac_addr MAC address storage
 * @return char* a string that is the name of the given PHY configuration.
 *****************************************************************************/
const char *app_wisun_mac_addr_to_str(const sl_wisun_mac_address_t *mac_addr);

/**************************************************************************//**
 * @brief Destroying MAC address string
 * @details It free the allocated MAC address
 * @param[in] str is a pointer of the list
 *****************************************************************************/
__STATIC_INLINE void app_wisun_destroy_mac_addr_str(const char *str)
{
  app_wisun_free((void *)str);
}

#if !defined(SL_CATALOG_WISUN_NCP_PRESENT)
/**************************************************************************//**
 * @brief Get connection parameters by network size
 * @details Certificate and Auto network sizes are not supported
 * @param[in] nw_size Network size
 * @return const sl_wisun_connection_params_t* constant pointer of connection
 *                                             parameters on success,
 *                                             otherwise NULL
 *****************************************************************************/
const sl_wisun_connection_params_t *sl_wisun_get_conn_param_by_nw_size(const sl_wisun_network_size_t nw_size);
#endif

/**************************************************************************//**
 * @brief Initialize timestamp
 * @details This function sets the current tick to the reference point of the
 *          timestamps.
 * @param[in] time_ms time in ms to convert
 * @param[out] time destination time structure
 *****************************************************************************/
void app_wisun_trace_util_timestamp_init(const uint64_t time_ms,
                                         sl_wisun_trace_util_time_t * const time);

/**************************************************************************//**
 * @brief Get time in string
 * @details Returns time in ddd:hh:mm:ss format
 * @param[in] time time data to convert string
 * @return time string if succeeded otherwise NULL ptr
 *****************************************************************************/
const char *app_wisun_trace_util_time_to_str(const sl_wisun_trace_util_time_t * const time);

/**************************************************************************//**
 * @brief Destroying time string
 * @details It frees the allocated time string
 * @param[in] str string to free
 *****************************************************************************/
__STATIC_INLINE void app_wisun_trace_util_destroy_time_str(const char *str)
{
  app_wisun_free((void *)str);
}

/**************************************************************************//**
 * @brief Get elapsed time in milliseconds
 * @details This function returns the ellapsed time in milliseconds.
 * @param[out] ms elapsed time in milliseconds
 * @return sl_status_t SL_STATUS_OK on success, SL_STATUS_FAIL on error
 *****************************************************************************/
sl_status_t app_wisun_trace_util_timestamp_get_ms(uint64_t * const ms);

/**************************************************************************//**
 * @brief Init event notification
 * @details Init osEventFlags and subscribed channel storage
 * @param[in,out] evt_notify Event notification to initialise
 * @param[in] wait_opt Option for event wait
 * @return sl_status_t SL_STATUS_OK on success, SL_STATUS_FAIL on error
 *****************************************************************************/
sl_status_t app_wisun_trace_util_evt_notify_init(app_wisun_trace_util_evt_notify_t * const evt_notify, 
                                                 const uint32_t wait_opt);

/**************************************************************************//**
 * @brief Clear notifications
 * @details Clear subsrcibed channels (represented by bits) in osEventFlags
 * @param[in,out] evt_notify Event notification
 * @return sl_status_t SL_STATUS_OK on success, SL_STATUS_FAIL on error
 *****************************************************************************/
sl_status_t app_wisun_trace_util_evt_notify_clear(app_wisun_trace_util_evt_notify_t * const evt_notify);

/**************************************************************************//**
 * @brief Subscribe to notification
 * @details Getting subscribed channel ID
 * @param[in,out] evt_notify Event notification
 * @param[out] evt_ch Subscribed event channel
 * @return sl_status_t SL_STATUS_OK on success, SL_STATUS_FAIL on error
 *****************************************************************************/
sl_status_t app_wisun_trace_util_evt_notify_subscribe_ch(app_wisun_trace_util_evt_notify_t * const evt_notify, 
                                                         uint8_t * const evt_ch);

/**************************************************************************//**
 * @brief Unsubscribe to notification
 * @details Remove subscribed channel ID from osEventFlags
 * @param[in,out] evt_notify Event notification
 * @param[in] evt_ch Subscribed event channel
 * @return sl_status_t SL_STATUS_OK on success, SL_STATUS_FAIL on error
 *****************************************************************************/                                                         
sl_status_t app_wisun_trace_util_evt_notify_unsubscribe_ch(app_wisun_trace_util_evt_notify_t * const evt_notify, 
                                                           const uint8_t evt_ch);

/**************************************************************************//**
 * @brief Notify subscribed channels
 * @details Set osEventFlags by subscribed channels
 * @param[in] evt_notify Event notification
 * @return sl_status_t SL_STATUS_OK on success, SL_STATUS_FAIL on error
 *****************************************************************************/
sl_status_t app_wisun_trace_util_evt_notfiy_chs(const app_wisun_trace_util_evt_notify_t * const evt_notify);

/**************************************************************************//**
 * @brief Waiting for notification
 * @details Using osEventFlagsWait for waiting event flags described by ch_mask
 * @param[in] ch_mask Channel mask for waiting
 * @param[in] timeout Timeout
 * @return sl_status_t SL_STATUS_OK on success, SL_STATUS_FAIL on error
 *****************************************************************************/  
sl_status_t app_wisun_trace_util_evt_notify_wait(const app_wisun_trace_util_evt_notify_t * const evt_notify,
                                                 const uint32_t ch_mask,
                                                 const uint32_t timeout);

#ifdef __cplusplus
}
#endif

#endif /* __SL_WISUN_APP_UTIL_H__ */
