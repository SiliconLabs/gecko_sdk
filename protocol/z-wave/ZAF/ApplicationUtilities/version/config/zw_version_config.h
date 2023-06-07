/**
 * @file
 * @copyright 2023 Silicon Laboratories Inc.
 */

#ifndef _ZW_VERSION_CONFIG_H_
#define _ZW_VERSION_CONFIG_H_

/**
 * \defgroup configuration Configuration
 * Configuration
 *
 * \addtogroup configuration
 * @{
 */
/**
 * \defgroup app_version_configuration Application Version Configuration
 * Application Version Configuration
 *
 * \addtogroup app_version_configuration
 * @{
 */

/**
 * Application Major Version <1..255:1>
 *
 */
#if !defined(APP_VERSION)
#define APP_VERSION  1
#endif /* !defined(APP_VERSION) */

/**
 * Application Minor Version <1..255:1>
 *
 */
#if !defined(APP_REVISION)
#define APP_REVISION  0
#endif /* !defined(APP_REVISION) */

/**
 * Application Patch Version <1..255:1>
 *
 */
#if !defined(APP_PATCH)
#define APP_PATCH  0
#endif /* !defined(APP_PATCH) */

/**@}*/ /* \addtogroup app_version_configuration */

/**@}*/ /* \addtogroup configuration */
#endif /* _ZW_VERSION_CONFIG_H_ */
