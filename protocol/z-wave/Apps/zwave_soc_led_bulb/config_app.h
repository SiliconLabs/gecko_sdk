/**
 * @file
 * @brief Configuration file for Switch On/Off sample application.
 * @details This file contains definitions for the Z-Wave+ Framework as well for the sample app.
 *
 * @copyright 2020 Silicon Laboratories Inc.
 */
#ifndef _CONFIG_APP_H_
#define _CONFIG_APP_H_

#include "ZW_classcmd.h"
#include "ZW_security_api.h"

/**
 * Application version, which is generated during release of SDK.
 * The application developer can freely alter the version numbers
 * according to his needs.
 */
#define APP_VERSION           ZAF_VERSION_MAJOR
#define APP_REVISION          ZAF_VERSION_MINOR
#define APP_PATCH             ZAF_VERSION_PATCH


/*
 * File identifiers for application file system
 * Range: 0x00000 - 0x0FFFF
 */
#define FILE_ID_APPLICATIONDATA     (0x00000)

#endif /* _CONFIG_APP_H_ */

