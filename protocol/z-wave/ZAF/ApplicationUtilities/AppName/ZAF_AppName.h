/**
 * @file
 * @brief Stores the name of the application
 *
 * @details Stores the application's name, aiding the identification of devices
 * during development.
 *
 * @copyright 2023 Silicon Laboratories Inc.
 */

#ifndef ZAF_APPNAME_H
#define ZAF_APPNAME_H

#include <stdbool.h>
#include "zaf_appname_config.h"

#if !defined(ZAF_APP_NAME)
#error "The application's name is not defined"
#endif

#define ZAF_FILE_SIZE_APP_NAME 30 // 29 characters + \0

/**
 * @brief Reads the name of the application into a character array.
 *
 * @param[out] app_name
 * @return status of the read operation
 */
bool ZAF_AppName_Read(char * app_name);

/**
 * @brief Writes the name of the application to the non-volatile memory, if it
 * isn't already up to date.
 *
 * @return status of the write operation
 */
bool ZAF_AppName_Write(void);

#endif /* ZAF_APPNAME_H */
