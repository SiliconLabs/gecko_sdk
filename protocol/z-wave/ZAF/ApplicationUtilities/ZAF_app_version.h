/**
 * @file
 * @brief Query the application version
 * @copyright 2019 Silicon Laboratories Inc.
 */

#ifndef ZAF_APP_VERSION_H_
#define ZAF_APP_VERSION_H_

#include <stdint.h>

/**
 * Get the full application version
 *
 * @return 32-bit application version
 */
uint32_t ZAF_GetAppVersion(void);

/**
 * Get the major application version
 *
 * @return Major application version
 */
uint8_t ZAF_GetAppVersionMajor(void);

/**
 * Get the minor application version
 *
 * @return Minor application version
 */
uint8_t ZAF_GetAppVersionMinor(void);

/**
 * Get the application patch level
 *
 * @return Application patch level
 */
uint8_t ZAF_GetAppVersionPatchLevel(void);

#endif /* ZAF_APP_VERSION_H_ */
