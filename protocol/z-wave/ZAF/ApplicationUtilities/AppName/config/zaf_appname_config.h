/**
 * @file
 * @copyright 2023 Silicon Laboratories Inc.
 */

#ifndef _ZAF_APPNAME_CONFIG_H_
#define _ZAF_APPNAME_CONFIG_H_

/**
 * \defgroup configuration Configuration
 * Configuration
 *
 * \addtogroup configuration
 * @{
 */
/**
 * \defgroup zaf_appname_configuration ZAF Application Name Configuration
 * ZAF Application Name Configuration
 *
 * \addtogroup zaf_appname_configuration
 * @{
 */

/**
 * Application Name (maximum length: 29)
 *
 */
#if !defined(ZAF_APP_NAME)
#define ZAF_APP_NAME  "zwave_application"
#endif /* !defined(ZAF_APP_NAME) */

/**@}*/ /* \addtogroup zaf_appname_configuration */

/**@}*/ /* \addtogroup configuration */
#endif /* _ZAF_APPNAME_CONFIG_H_ */
