/**
 * @file
 * @brief This header file contains defines for application version in a generalized way.
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */

#ifndef _CONFIG_APP_H_
#define _CONFIG_APP_H_

#include "ZW_classcmd.h"
#include "ZW_security_api.h"

/****************************************************************************
 *
 * Application version, which is generated during release of SDK.
 * The application developer can freely alter the version numbers
 * according to his needs.
 *
 ****************************************************************************/
#define APP_VERSION           ZAF_VERSION_MAJOR
#define APP_REVISION          ZAF_VERSION_MINOR
#define APP_PATCH             ZAF_VERSION_PATCH


/*
 * File identifiers for application file system
 * Range: 0x00000 - 0x0FFFF
 */
#define FILE_ID_APPLICATIONDATA     (0x00000)

/**
 * Heat event notification handler period in ms
 */
#define HEAT_EVENT_CHECK_PERIOD_MS           5000

/**
 * The timeout value in milli seconds that used when sending basic set command due to an event
 */
#define BASIC_SET_TIMEOUT         10000

#endif /* _CONFIG_APP_H_ */
