/***************************************************************************//**
 * @file
 * @brief App BT Mesh Utility
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

#ifndef APP_BTMESH_UTIL_H
#define APP_BTMESH_UTIL_H

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT

#include "app_btmesh_util_config.h"
#include "sl_status.h"
#include "sl_btmesh_api.h"

/***************************************************************************//**
 * @addtogroup App BT Mesh Utility
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @def app_btmesh_util_log_status_f
 * @brief Logs the btmesh API failures
 *
 * There are two special errors which are related to missing model configuration.
 * If the BT Mesh configurator (e.g. mobile app) does not bind application key
 * to the model or does not configure the model publication data then publish
 * or other API calls which leads to message sending fails.
 * From the BT Mesh node perspective it can't be determined if the configurator
 * missed these configuration steps on purpose or not so these errors are logged
 * at a less severe log level.
 ******************************************************************************/
#if defined(SL_CATALOG_APP_LOG_PRESENT)
#define app_btmesh_util_log_status_f(sc, ...)                               \
  do {                                                                      \
    switch (sc) {                                                           \
      case SL_STATUS_OK:                                                    \
        break;                                                              \
      case SL_STATUS_BT_MESH_APP_KEY_NOT_BOUND:                             \
        app_log_status_level_f(APP_BTMESH_UTIL_LOG_LEVEL_APP_KEY_NOT_BOUND, \
                               sc,                                          \
                               __VA_ARGS__);                                \
        break;                                                              \
      case SL_STATUS_BT_MESH_PUBLISH_NOT_CONFIGURED:                        \
        app_log_status_level_f(APP_BTMESH_UTIL_LOG_LEVEL_PUBLISH_NOT_CONF,  \
                               sc,                                          \
                               __VA_ARGS__);                                \
        break;                                                              \
      default:                                                              \
        app_log_status_level_f(APP_LOG_LEVEL_ERROR, sc, __VA_ARGS__);       \
        break;                                                              \
    }                                                                       \
  } while (0)
#else
#define app_btmesh_util_log_status_f(sc, ...) (void)(sc)
#endif

// This macro calculates the number of precompile logging enable request in the
// specific c file where the this header file is included from
#define APP_BTMESH_UTIL_COMPONENT_LOGGING                 \
  (SL_BTMESH_BLOB_STORAGE_LOGGING_CFG_VAL                 \
   + SL_BTMESH_BLOB_TRANSFER_CLIENT_LOGGING_CFG_VAL       \
   + SL_BTMESH_BLOB_TRANSFER_SERVER_LOGGING_CFG_VAL       \
   + SL_BTMESH_CTL_CLIENT_LOGGING_CFG_VAL                 \
   + SL_BTMESH_CTL_SERVER_LOGGING_CFG_VAL                 \
   + SL_BTMESH_FRIEND_LOGGING_CFG_VAL                     \
   + SL_BTMESH_FW_DIST_SERVER_LOGGING_CFG_VAL             \
   + SL_BTMESH_FW_UPDATE_SERVER_LOGGING_CFG_VAL           \
   + SL_BTMESH_GENERIC_ONOFF_SERVER_LOGGING_CFG_VAL       \
   + SL_BTMESH_HSL_SERVER_LOGGING_CFG_VAL                 \
   + SL_BTMESH_IV_UPDATE_LOGGING_CFG_VAL                  \
   + SL_BTMESH_LC_SERVER_LOGGING_CFG_VAL                  \
   + SL_BTMESH_LIGHTING_CLIENT_LOGGING_CFG_VAL            \
   + SL_BTMESH_LIGHTING_SERVER_LOGGING_CFG_VAL            \
   + SL_BTMESH_LPN_LOGGING_CFG_VAL                        \
   + SL_BTMESH_PROVISIONEE_LOGGING_CFG_VAL                \
   + SL_BTMESH_PROVISIONER_LOGGING_CFG_VAL                \
   + SL_BTMESH_PROVISIONING_DECORATOR_LOGGING_CFG_VAL     \
   + SL_BTMESH_REMOTE_PROVISIONING_CLIENT_LOGGING_CFG_VAL \
   + SL_BTMESH_REMOTE_PROVISIONING_SERVER_LOGGING_CFG_VAL \
   + SL_BTMESH_SCENE_CLIENT_LOGGING_CFG_VAL               \
   + SL_BTMESH_SCHEDULER_SERVER_LOGGING_CFG_VAL           \
   + SL_BTMESH_SELF_PROVISIONING_CLI_LOGGING_CFG_VAL      \
   + SL_BTMESH_SENSOR_CLIENT_LOGGING_CFG_VAL              \
   + SL_BTMESH_SENSOR_SERVER_LOGGING_CFG_VAL              \
   + SL_BTMESH_TIME_SERVER_LOGGING_CFG_VAL                \
   + SL_BTMESH_VENDOR_LOOPBACK_LOGGING_CFG_VAL)
// Component A shall not include the config file of another component B because
// <COMPONENT_B>_LOGGING macro of component B could turn on the logging in the
// component A unnecessarily. This is important in case of components with log.
// Warning is emitted to notify the developer to resolve the include problem.
#if (1 < APP_BTMESH_UTIL_COMPONENT_LOGGING)
#warning "Multiple BT Mesh component logging macros are defined in one file."
#endif

// Defines the local log macros for components based on the component configuration.
// The app_btmesh_util.h file shall be included after the component configuration
// header file include which defines the <COMPONENT>_LOGGING macro.
// Warning! The app_btmesh_util.h header file is context sensitive so it behaves
//          differently in different c files based on the file specific value of
//          the <COMPONENT>_LOGGING macros so this header shall not be included
//          from other header files.
#if defined(SL_CATALOG_APP_LOG_PRESENT) && (APP_BTMESH_UTIL_COMPONENT_LOGGING != 0)
#define log_nl()                                           app_log_nl()
#define log(...)                                           app_log(__VA_ARGS__)
#define log_level(level, ...)                              app_log_level(level, __VA_ARGS__)
#define log_debug(...)                                     app_log_debug(__VA_ARGS__)
#define log_info(...)                                      app_log_info(__VA_ARGS__)
#define log_warning(...)                                   app_log_warning(__VA_ARGS__)
#define log_error(...)                                     app_log_error(__VA_ARGS__)
#define log_critical(...)                                  app_log_critical(__VA_ARGS__)
#define log_append(...)                                    app_log_append(__VA_ARGS__)
#define log_append_level(level, ...)                       app_log_append_level(level, __VA_ARGS__)
#define log_append_debug(...)                              app_log_append_debug(__VA_ARGS__)
#define log_append_info(...)                               app_log_append_info(__VA_ARGS__)
#define log_append_warning(...)                            app_log_append_warning(__VA_ARGS__)
#define log_append_error(...)                              app_log_append_error(__VA_ARGS__)
#define log_append_critical(...)                           app_log_append_critical(__VA_ARGS__)
#define log_status_debug(sc)                               app_log_status_debug(sc)
#define log_status_info(sc)                                app_log_status_info(sc)
#define log_status_warning(sc)                             app_log_status_warning(sc)
#define log_status_error(sc)                               app_log_status_error(sc)
#define log_status_critical(sc)                            app_log_status_critical(sc)
#define log_status_debug_f(sc, ...)                        app_log_status_debug_f(sc, __VA_ARGS__)
#define log_status_info_f(sc, ...)                         app_log_status_info_f(sc, __VA_ARGS__)
#define log_status_warning_f(sc, ...)                      app_log_status_warning_f(sc, __VA_ARGS__)
#define log_status_error_f(sc, ...)                        app_log_status_error_f(sc, __VA_ARGS__)
#define log_status_critical_f(sc, ...)                     app_log_status_critical_f(sc, __VA_ARGS__)
#define log_status(sc)                                     app_log_status(sc)
#define log_status_level(level, sc)                        app_log_status_level(level, sc)
#define log_status_f(sc, ...)                              app_log_status_f(sc, __VA_ARGS__)
#define log_status_level_f(level, sc, ...)                 app_log_status_level_f(level, sc, __VA_ARGS__)
#define log_btmesh_status_f(sc, ...)                       app_btmesh_util_log_status_f(sc, __VA_ARGS__)
#define log_hexdump_debug(p_data, len)                     app_log_hexdump_debug(p_data, len)
#define log_hexdump_info(p_data, len)                      app_log_hexdump_info(p_data, len)
#define log_hexdump_warning(p_data, len)                   app_log_hexdump_warning(p_data, len)
#define log_hexdump_error(p_data, len)                     app_log_hexdump_error(p_data, len)
#define log_hexdump_critical(p_data, len)                  app_log_hexdump_critical(p_data, len)
#define log_hexdump_level(level, p_data, len)              app_log_hexdump_level(level, p_data, len)
#define log_hexdump_debug_s(separator, p_data, len)        app_log_hexdump_debug_s(separator, p_data, len)
#define log_hexdump_info_s(separator, p_data, len)         app_log_hexdump_info_s(separator, p_data, len)
#define log_hexdump_warning_s(separator, p_data, len)      app_log_hexdump_warning_s(separator, p_data, len)
#define log_hexdump_error_s(separator, p_data, len)        app_log_hexdump_error_s(separator, p_data, len)
#define log_hexdump_critical_s(separator, p_data, len)     app_log_hexdump_critical_s(separator, p_data, len)
#define log_hexdump_level_s(level, separator, p_data, len) app_log_hexdump_level_s(level, separator, p_data, len)
#else
#define log_nl()
#define log(...)
#define log_level(level, ...)
#define log_debug(...)
#define log_info(...)
#define log_warning(...)
#define log_error(...)
#define log_critical(...)
#define log_append(...)
#define log_append_level(level, ...)
#define log_append_debug(...)
#define log_append_info(...)
#define log_append_warning(...)
#define log_append_error(...)
#define log_append_critical(...)
#define log_status_debug(sc) (void)(sc)
#define log_status_info(sc) (void)(sc)
#define log_status_warning(sc) (void)(sc)
#define log_status_error(sc) (void)(sc)
#define log_status_critical(sc) (void)(sc)
#define log_status_debug_f(sc, ...) (void)(sc)
#define log_status_info_f(sc, ...) (void)(sc)
#define log_status_warning_f(sc, ...) (void)(sc)
#define log_status_error_f(sc, ...) (void)(sc)
#define log_status_critical_f(sc, ...) (void)(sc)
#define log_status(sc) (void)(sc)
#define log_status_level(level, sc) (void)(sc)
#define log_status_f(sc, ...) (void)(sc)
#define log_status_level_f(level, sc, ...) (void)(sc)
#define log_btmesh_status_f(sc, ...) (void)(sc)
#define log_hexdump_debug(p_data, len)
#define log_hexdump_info(p_data, len)
#define log_hexdump_warning(p_data, len)
#define log_hexdump_error(p_data, len)
#define log_hexdump_critical(p_data, len)
#define log_hexdump_level(level, p_data, len)
#define log_hexdump_debug_s(separator, p_data, len)
#define log_hexdump_info_s(separator, p_data, len)
#define log_hexdump_warning_s(separator, p_data, len)
#define log_hexdump_error_s(separator, p_data, len)
#define log_hexdump_critical_s(separator, p_data, len)
#define log_hexdump_level_s(level, separator, p_data, len)
#endif // defined(SL_CATALOG_APP_LOG_PRESENT) && (APP_BTMESH_UTIL_COMPONENT_LOGGING != 0)

/// Maximum size of UUID64 string representation with separators (including null char)
#define APP_BTMESH_UUID_64_STR_MAX_SIZE 24

// Log new line shortcut definition
#define NL APP_LOG_NL

/***************************************************************************//**
 * Provides string representation of UUID64 in a compound literal
 *
 * It is guaranteed that this macro returns a valid string even in case of
 * invalid parameters.
 *
 * @warning This macro calls @ref app_btmesh_uuid_64_to_string function with a
 * compound literal which means the lifetime of returned string representation
 * is the same as the enclosing block so the return value shall not be referenced
 * outside of the most enclosing block where this macro is called from.
 * For example the macro value shall not be returned from the caller function.
 *
 * This macro can be used in printf-like calls (e.g. log calls) directly because
 * it returns a string under every circumstances and the lifetime of compound
 * literal is not problematic if the value is passed as a parameter directly
 * to another function.
 *
 * @param[in] uuid_64 Input UUID64 which shall be converted to string
 * @param[in] separator Separator character to be used between two hex characters.
 *   If the separator is the null character then the no separator is used.
 * @param[in] uppercase If true hex characters are upper case otherwise lower case
 *
 * @return String representation of UUID64 which has enclosing block lifetime
 * @retval "INVALID" if an error occurs due to invalid parameters
 ******************************************************************************/
#define APP_BTMESH_UUID_64_TO_STRING(uuid_64, separator, uppercase)                  \
  app_btmesh_uuid_64_to_string((char[APP_BTMESH_UUID_64_STR_MAX_SIZE]){ 0 },         \
                               sizeof((char[APP_BTMESH_UUID_64_STR_MAX_SIZE]){ 0 }), \
                               uuid_64,                                              \
                               separator,                                            \
                               uppercase)

/***************************************************************************//**
 * Convert progress into percentage, based on target and current values
 *
 * @param _target Target value
 * @param _progress Current value
 * @retval Float percentage of the progress
 ******************************************************************************/
#define SL_PROG_TO_PCT(_target, _progress) \
  (((float)(_progress)) / ((float)(_target)) * 100.0f)

/***************************************************************************//**
 * Convert progress into percentage, based on target and current values
 *
 * @param _target Target value
 * @param _progress Current value
 * @retval Integer percentage of the progress
 ******************************************************************************/
#define SL_PROG_TO_PCT_INT(_target, _progress) \
  (((_progress) * 100) / (_target) )

/***************************************************************************//**
 * Silicon Laboratories Company ID as integer
 ******************************************************************************/
#define SLI_SILABS_CID_INT      0x02FF

/***************************************************************************//**
 * Silicon Laboratories Company ID as little-endian string
 ******************************************************************************/
#define SLI_SILABS_CID_STR_LE   "\xFF\x02"

/***************************************************************************//**
 * Silicon Laboratories Company ID as big-endian string
 ******************************************************************************/
#define SLI_SILABS_CID_STR_BE   "\x02\xFF"

/***************************************************************************//**
 * Initializes the NVM interface.
 *
 * Calls the default initializer of NVM3.
 *
 * @return Status code
 * @retval SL_STATUS_OK                   In case of success
 * @retval SL_STATUS_ALREADY_INITIALIZED  In case it was initialized earlier
 *                                        with parameters different from default
 *
 ******************************************************************************/
sl_status_t app_btmesh_nvm_init(void);

/***************************************************************************//**
 * Reads data from NVM.
 *
 * @param[in] key     Identifier of the data.
 * @param[out] buf    Buffer to the data to read.
 * @param[inout] len  Pointer to the length of the read data. As in input it
 *                    takes the length of buffer. As an output it contains the
 *                    length of the read data.
 * @return Status code
 * @retval SL_STATUS_OK                 In case of success
 * @retval SL_STATUS_INVALID_STATE      In case NVM has not been initialized
 * @retval SL_STATUS_INVALID_KEY        In case key is invalid
 * @retval SL_STATUS_NOT_FOUND          In case key has not been found
 * @retval SL_STATUS_INVALID_PARAMETER  In case any of the input parameters is
 *                                      invalid
 ******************************************************************************/
sl_status_t app_btmesh_nvm_read(uint16_t key, void *buf, size_t *len);

/***************************************************************************//**
 * Writes data into the NVM.
 *
 * @param[in] key   Identifier of the data.
 * @param[in] buf   Buffer to the data to write.
 * @param[in] len   Length of the data in the buffer.
 * @return Status code
 * @retval SL_STATUS_OK                   In case of success
 * @retval SL_STATUS_INVALID_STATE        In case NVM has not been initialized
 * @retval SL_STATUS_FULL                 In case NVM is full
 * @retval SL_STATUS_NO_MORE_RESOURCE     In case NVM doesn't have the resources
 *                                        to store the data
 * @retval SL_STATUS_FLASH_PROGRAM_FAILED In case writing to NVM has failed
 * @retval SL_STATUS_INVALID_PARAMETER    In case any of the input parameters is
 *                                        invalid
 ******************************************************************************/
sl_status_t app_btmesh_nvm_write(uint16_t key, const void *buf, size_t len);

/***************************************************************************//**
 * Erases data from NVM.
 *
 * @param[in] key   Identifier of the data.
 * @return Status code
 * @retval SL_STATUS_OK                   In case of success
 * @retval SL_STATUS_INVALID_STATE        In case NVM has not been initialized
 * @retval SL_STATUS_INVALID_KEY          In case key is invalid
 * @retval SL_STATUS_NOT_FOUND            In case key has not been found
 * @retval SL_STATUS_FLASH_PROGRAM_FAILED In case writing to NVM has failed
 * @retval SL_STATUS_INVALID_PARAMETER    In case any of the input parameters is
 *                                        invalid
 ******************************************************************************/
sl_status_t app_btmesh_nvm_erase(uint16_t key);

/***************************************************************************//**
 * Erases all NVM data.
 *
 * @return Status code
 * @retval SL_STATUS_OK                   In case of success
 * @retval SL_STATUS_INVALID_STATE        In case NVM has not been initialized
 * @retval SL_STATUS_INVALID_PARAMETER    In case any of the input parameters is
 *                                        invalid
 ******************************************************************************/
sl_status_t app_btmesh_nvm_erase_all(void);

/***************************************************************************//**
 * Provides string representation of UUID64
 *
 * It is guaranteed that this function returns a valid string even in case of
 * invalid parameters.
 *
 * @param[out] buffer Output buffer where the string representation is written
 * @param[in] buffer_size Size of output buffer
 * @param[in] uuid_64 Input UUID64 which shall be converted to string
 * @param[in] separator Separator character to be used between two hex characters.
 *   If the separator is the null character then no separator is used.
 * @param[in] uppercase If true hex characters are upper case otherwise lower case
 *
 * @return Output buffer which contains the string representation of UUID64
 * @retval "INVALID" if an error occurs due to invalid parameters
 ******************************************************************************/
const char *app_btmesh_uuid_64_to_string(char *buffer,
                                         uint32_t buffer_size,
                                         const sl_bt_uuid_64_t *uuid_64,
                                         char separator,
                                         bool uppercase);

/***************************************************************************//**
 * Provides hex representation of byte array as a string
 *
 * It is guaranteed that this function returns a valid string even in case of
 * invalid parameters.
 *
 * @param[out] buffer Output buffer where the hex representation is written
 * @param[in] buffer_size Size of output buffer
 * @param[in] bytes Input byte array which shall be converted to hex
 * @param[in] bytes_size Size of input byte array
 * @param[in] separator Separator character to be used between two hex characters.
 *   If the separator is the null character then no separator is used.
 * @param[in] uppercase If true hex characters are upper case otherwise lower case
 *
 * @return Output buffer which contains the hex representation of byte array
 * @retval "INVALID" if an error occurs due to invalid parameters
 ******************************************************************************/
const char *app_btmesh_bytes_to_hex(char *buffer,
                                    uint32_t buffer_size,
                                    const uint8_t *bytes,
                                    uint32_t bytes_size,
                                    char separator,
                                    bool uppercase);

/** @} (end addtogroup App BT Mesh Utility) */

#endif /* APP_BTMESH_UTIL_H */
