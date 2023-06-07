/**
 * @file
 * @brief Non-volatile memory implementation of application name storage
 *
 * @details This module enables externally reading the name of the application,
 * which simplifies identifying devices when there are multiple ones connected.
 *
 * @copyright 2023 Silicon Laboratories Inc.
 */

#include "ZAF_AppName.h"
#include <string.h>
#include "ZAF_file_ids.h"
#include "ZAF_nvm.h"
#include "zpal_nvm.h"

bool ZAF_AppName_Read(char * app_name)
{
  zpal_status_t status;

  status = ZAF_nvm_read(
    ZAF_FILE_ID_APP_NAME, app_name, ZAF_FILE_SIZE_APP_NAME
    );

  return status == ZPAL_STATUS_OK;
}

bool ZAF_AppName_Write()
{
  char app_name_new[ZAF_FILE_SIZE_APP_NAME];
  char app_name_current[ZAF_FILE_SIZE_APP_NAME];
  zpal_status_t status = ZPAL_STATUS_OK;

  /* Copy the application's name to a new, fixed size string and fill the
   * remaining bytes with '\0' */
  strncpy(app_name_new, ZAF_APP_NAME, ZAF_FILE_SIZE_APP_NAME);
  void * blank_characters_after_name = (void *)app_name_new + sizeof(ZAF_APP_NAME);
  uint8_t number_of_blank_bytes = ZAF_FILE_SIZE_APP_NAME - sizeof(ZAF_APP_NAME);
  memset(blank_characters_after_name, 0, number_of_blank_bytes);

  ZAF_AppName_Read(app_name_current);

  // Overwrite the application's name in NVM if it doesn't match
  bool is_nvm_outdated = strncmp(app_name_current, app_name_new,
                                 ZAF_FILE_SIZE_APP_NAME - 1
                                 ) != 0;
  if (is_nvm_outdated) {
    status = ZAF_nvm_write(ZAF_FILE_ID_APP_NAME, app_name_new,
                           ZAF_FILE_SIZE_APP_NAME);
  }

  return status == ZPAL_STATUS_OK;
}
