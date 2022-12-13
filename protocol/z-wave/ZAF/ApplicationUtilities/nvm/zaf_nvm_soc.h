/**
 * @file
 * ZAF NVM SOC application handling
 * @copyright 2022 Silicon Laboratories Inc.
 */

#ifndef ZAF_NVM_SOC_H_
#define ZAF_NVM_SOC_H_

#include <stdint.h>

/**
 * @addtogroup ZAF
 * @{
 * @addtogroup NVM
 * @{
 */

/**
 * @brief Used by the application to execute actions after a set default
 * configuration
 *
 */
void zaf_nvm_app_set_default_configuration(void);

/**
 * @brief Used by the application to execute actions after a application reset
 *
 */
void zaf_nvm_app_reset(void);

/**
 * @brief Used by the application to execute actions after a load configuration
 *
 */
void zaf_nvm_app_load_configuration(void);

/**
 * @brief Used by the application to execute actions when the current version
 * differs from the saved version
 *
 * @param current_version Version returned by zpal_get_app_version
 * @param saved_version Version stored in ZAF_FILE_ID_APP_VERSION
 */
void zaf_nvm_app_load_configuration_migration(uint32_t current_version, uint32_t saved_version);

/**
 * @brief Resets configuration to default values.
 *
 * @remarks Internal function only
 *
 * Add application specific functions here to initialize configuration values stored in persistent memory.
 * Will be called at any of the following events:
 *  - Network Exclusion
 *  - Network Secure Inclusion (after S2 bootstrapping complete)
 *  - Device Reset Locally
 */
void zafi_nvm_app_set_default_configuration(void);

/**
 * @brief Resets the NVM file system
 *
 * @remarks Internal function only
 *
 */
void zafi_nvm_app_reset(void);

/**
 * @brief Loads the default configuration common for all applications.
 *
 * @remarks If no settings are found, the application file system will be erased and default values
 *          will be written.
 *
 * @remarks Internal function. Don't invoke from application.
 *
 */
void zafi_nvm_app_load_configuration(void);

/**
 * @} // NVM
 * @} // ZAF
 */

#endif /* ZAF_NVM_SOC_H_ */
