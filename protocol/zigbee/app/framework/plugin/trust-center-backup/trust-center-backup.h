/***************************************************************************//**
 * @file trust-center-backup.h
 * @brief Definitions for the Trust Center Backup plugin.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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
#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif

#ifdef SL_CATALOG_ZIGBEE_TRUST_CENTER_BACKUP_PRESENT
#include "trust-center-backup-config.h"
#else
#include "config/trust-center-backup-config.h"
#endif
#if (EMBER_AF_PLUGIN_TRUST_CENTER_BACKUP_POSIX_FILE_BACKUP_SUPPORT == 1)
#define POSIX_FILE_BACKUP_SUPPORT
#endif

/**
 * @defgroup trust-center-backup Trust Center Backup
 * @ingroup component
 * @brief API and Callbacks for the Trust Center Backup Component
 *
 * This component is only for a trust center.  It provides a set of APIs
 * for importing and exporting the backup info for a Smart Energy trust center.
 * It requires extending to hook up import/export routines into an external
 * storage device or network, where the data may be saved to and restored from.
 *
 */

/**
 * @addtogroup trust-center-backup
 * @{
 */

/**
 * @name API
 * @{
 */

/** @brief export backup data
 *
 * @param backup Ver.: always
 *
 * @return EmberStatus status code
 *
 */
EmberStatus emberTrustCenterExportBackupData(EmberAfTrustCenterBackupData* backup);

/** @brief Import backup and start network
 *
 * @param nbackup Ver.: always
 *
 * @return EmberStatus status code
 *
 */
EmberStatus emberTrustCenterImportBackupAndStartNetwork(const EmberAfTrustCenterBackupData* backup);

/** @brief Import backup from file
 *
 * @param filepath Ver.: always
 *
 * @return EmberStatus status code
 *
 * @note Available only for EMBER_AF_PLUGIN_TRUST_CENTER_BACKUP_POSIX_FILE_BACKUP_SUPPORT
 *
 */
EmberStatus emberAfTrustCenterImportBackupFromFile(const char* filepath);

/** @brief export backup to a file
 *
 * @param filepath Ver.: always
 *
 * @return EmberStatus status code
 *
 * @note Available only for EMBER_AF_PLUGIN_TRUST_CENTER_BACKUP_POSIX_FILE_BACKUP_SUPPORT
 *
 */
EmberStatus emberAfTrustCenterExportBackupToFile(const char* filepath);

/** @brief saves tokens to a file
 *
 * @param filepath Ver.: always
 *
 * @return EmberStatus status code
 *
 * @note Available only for EMBER_AF_PLUGIN_TRUST_CENTER_BACKUP_POSIX_FILE_BACKUP_SUPPORT
 *
 */
EmberStatus emberAfTrustCenterBackupSaveTokensToFile(const char* filepath);

/** @brief restores tokens from a file
 *
 * @param filepath Ver.: always
 *
 * @return EmberStatus status code
 *
 * @note Available only for EMBER_AF_PLUGIN_TRUST_CENTER_BACKUP_POSIX_FILE_BACKUP_SUPPORT
 *
 */
EmberStatus emberAfTrustCenterBackupRestoreTokensFromFile(const char* filepath);

/** @brief Updates zigbeed tokens from a file that stores NCP tokens.
 *
 * @param filepath Ver.: always
 *
 * @return EmberStatus status code
 *
 * @note Available only for EMBER_AF_PLUGIN_TRUST_CENTER_BACKUP_POSIX_FILE_BACKUP_SUPPORT
 *
 */
EmberStatus emberAfTrustCenterBackupWriteNcpTokenToZigbeedTokens(const char* filepath);

/** @} */ // end of name API
/** @} */ // end of trust-center-backup

#ifdef SL_CLI_TYPES_H
//requires CLI support; avoid having scripted unit test try to compile

EmberStatus sli_zigbee_af_trust_center_backup_save_keys_to_data(EmberTokenData* data_s, uint32_t nvm3Key, uint8_t index);
EmberStatus sli_zigbee_af_trust_center_backup_restore_keys_from_data(EmberTokenData* data_s, uint32_t nvm3Key, uint8_t index);

void sli_zigbee_af_tc_export_command(sl_cli_command_arg_t *arguments);
void sli_zigbee_af_tc_import_command(sl_cli_command_arg_t *arguments);
void sli_zigbee_af_trust_center_backup_save_tokens_to_file_cli(sl_cli_command_arg_t *arguments);
void sli_zigbee_af_trust_center_backup_restore_tokens_from_file_cli(sl_cli_command_arg_t *arguments);

#endif //SL_CLI_TYPES_H
