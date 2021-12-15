/**
 * @file
 * @brief Query the application version
 *
 * This set of functions have been introduced to make sure the
 * application version only needs to be defined in the application
 * properties section.
 *
 * As an added benefit this makes it possible to only have the
 * application version in a single location in the application binary
 * allowing us to easily create multiple binaries with different versions
 * without re-building. This is useful for testing OTA firmware upgrades.
 *
 * For this strategy to work the pre-processor defines APP_VERSION,
 * ZAF_VERSION_MAJOR etc. should only be used to define the app_version
 * global variable. They must not be used anywhere else in the code.
 *
 * @copyright 2019 Silicon Laboratories Inc.
 */

#include "ZAF_app_version.h"
#include "application_properties.h"

extern const ApplicationProperties_t app_properties;

uint32_t ZAF_GetAppVersion(void)
{
  return app_properties.app.version;
}

uint8_t ZAF_GetAppVersionMajor(void)
{
  return (app_properties.app.version >> 16) & 0xFF;
}

uint8_t ZAF_GetAppVersionMinor(void)
{
  return (app_properties.app.version >> 8) & 0xFF;
}

uint8_t ZAF_GetAppVersionPatchLevel(void)
{
  return app_properties.app.version & 0xFF;
}
