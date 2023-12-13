/**
 * @file
 * @brief Weak implementation of application name storage
 *
 * @details This module provides a basic, read-only implementation for storing
 * the application's name. It does not utilize the non-volatile memory, to
 * save on resources.
 *
 * @copyright 2023 Silicon Laboratories Inc.
 */

#include "ZAF_AppName.h"
#include <string.h>
#include "ZW_typedefs.h"

ZW_WEAK bool ZAF_AppName_Read(char * app_name)
{
  strncpy(app_name, ZAF_APP_NAME, ZAF_FILE_SIZE_APP_NAME);

  return true;
}

ZW_WEAK bool ZAF_AppName_Write(void)
{
  return true;
}
