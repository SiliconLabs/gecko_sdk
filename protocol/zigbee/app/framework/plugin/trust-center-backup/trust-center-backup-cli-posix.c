/***************************************************************************//**
 * @file
 * @brief CLI for backing up or restoring TC data to unix filesystem.
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

#include "app/framework/include/af.h"
#include "app/framework/util/common.h"
#include "app/framework/util/util.h"
#include "app/util/serial/sl_zigbee_command_interpreter.h"
#include "app/framework/plugin/trust-center-backup/trust-center-backup.h"

#include "app/framework/util/af-main.h"

#include <errno.h>

#ifndef EMBER_SCRIPTED_TEST
  #include "trust-center-backup-config.h"
#else
  #include "config/trust-center-backup-config.h"
#endif

#if (EMBER_AF_PLUGIN_TRUST_CENTER_BACKUP_POSIX_FILE_BACKUP_SUPPORT == 1)
  #define POSIX_FILE_BACKUP_SUPPORT
#endif // EMBER_AF_PLUGIN_TRUST_CENTER_BACKUP_POSIX_FILE_BACKUP_SUPPORT

#if defined(EMBER_TEST)
  #define POSIX_FILE_BACKUP_SUPPORT
#endif

#if defined(POSIX_FILE_BACKUP_SUPPORT)

// *****************************************************************************
// Globals

// This is passed as an argument to emberCopyStringArgument() which only
// supports 8-bit values.
#define MAX_FILEPATH_LENGTH 255

#ifdef SL_CATALOG_ZIGBEE_CORE_CLI_PRESENT
// Forward Declarations

static void getFilePathFromCommandLine(sl_cli_command_arg_t *arguments, uint8_t* result);

// *****************************************************************************
// Functions

void sli_zigbee_af_tc_export_command(sl_cli_command_arg_t *arguments)
{
  uint8_t file[MAX_FILEPATH_LENGTH];
  getFilePathFromCommandLine(arguments, file);

  emberAfTrustCenterExportBackupToFile((const char*)file);
}

void sli_zigbee_af_trust_center_backup_save_tokens_to_file_cli(sl_cli_command_arg_t *arguments)
{
  uint8_t file[MAX_FILEPATH_LENGTH];
  getFilePathFromCommandLine(arguments, file);
  EmberStatus status = emberAfTrustCenterBackupSaveTokensToFile((const char*)file);
  printf("%s Status = %d\n", (status == EMBER_SUCCESS) ? "SUCCESS" : "ERROR", status);
}

void sli_zigbee_af_tc_import_command(sl_cli_command_arg_t *arguments)
{
  uint8_t file[MAX_FILEPATH_LENGTH];
  getFilePathFromCommandLine(arguments, file);

  emberAfTrustCenterImportBackupFromFile((const char*)file);
}

void sli_zigbee_af_trust_center_backup_restore_tokens_from_file_cli(sl_cli_command_arg_t *arguments)
{
  uint8_t file[MAX_FILEPATH_LENGTH];
  getFilePathFromCommandLine(arguments, file);
  EmberStatus status = emberAfTrustCenterBackupRestoreTokensFromFile((const char*)file);
  printf("%s Status = %d\n", (status == EMBER_SUCCESS) ? "SUCCESS" : "ERROR", status);
}

static void getFilePathFromCommandLine(sl_cli_command_arg_t *arguments, uint8_t* result)
{
  uint8_t length = sl_zigbee_copy_string_arg(arguments, 0,
                                             result,
                                             MAX_FILEPATH_LENGTH,
                                             false); // leftpad?
  result[length] = '\0';
}

void sli_zigbee_af_trust_center_backup_restore_reset_node_cli(sl_cli_command_arg_t *arguments)
{
  (void)arguments;
#if defined EZSP_HOST
  ezspResetNode();
#endif
}

void sli_zigbee_af_trust_center_backup_write_ncp_token_to_zigbeed_tokens_cli(sl_cli_command_arg_t *arguments)
{
  uint8_t file[MAX_FILEPATH_LENGTH];
  getFilePathFromCommandLine(arguments, file);
  EmberStatus status = emberAfTrustCenterBackupWriteNcpTokenToZigbeedTokens((const char*)file);
  printf("%s Status = %d\n", (status == EMBER_SUCCESS) ? "SUCCESS" : "ERROR", status);
}

#endif // SL_CLI_TYPES_H
#endif // defined(POSIX_FILE_BACKUP_SUPPORT)
