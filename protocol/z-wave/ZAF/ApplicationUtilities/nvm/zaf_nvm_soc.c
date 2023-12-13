/**
 * @file
 * ZAF NVM handling for SoC's
 *
 * @copyright 2022 Silicon Laboratories Inc.
 */
#include <Assert.h>
#include <ZAF_Common_helper.h>
#include <ZAF_file_ids.h>
#include <ZAF_nvm_app.h>
#include <ZAF_nvm.h>
#include <zaf_nvm_soc.h>
#include <zpal_misc.h>
#include <ZW_typedefs.h>

//#define DEBUGPRINT
#include "DebugPrint.h"

void
zafi_nvm_app_set_default_configuration(void)
{
  ZAF_Reset();

  uint32_t appVersion = zpal_get_app_version();
  const zpal_status_t status = ZAF_nvm_write(ZAF_FILE_ID_APP_VERSION, &appVersion, ZAF_FILE_SIZE_APP_VERSION);
  ASSERT(ZPAL_STATUS_OK == status);

  zaf_nvm_app_set_default_configuration();
}

void
zafi_nvm_app_reset(void)
{
  DPRINT("Resetting application FileSystem to default\r\n");

  ZAF_nvm_app_erase();
  ZAF_nvm_erase();

  /* Apparently there is no valid configuration in file system, so load */
  /* default values and save them to file system. */
  zafi_nvm_app_set_default_configuration();

  zaf_nvm_app_reset();
}

void
zafi_nvm_app_load_configuration(void)
{
  uint32_t saved_version, current_version;
  zpal_status_t status;

  status = ZAF_nvm_read(ZAF_FILE_ID_APP_VERSION, &saved_version, ZAF_FILE_SIZE_APP_VERSION);

  if (ZPAL_STATUS_OK == status) {
    current_version = zpal_get_app_version();
    if (current_version != saved_version) {
      zaf_nvm_app_load_configuration_migration(current_version, saved_version);
      // Add code for migration of file system to higher version here.
    }

    zaf_nvm_app_load_configuration();
  } else {
    DPRINT("Application FileSystem Verify failed\r\n");

    // Reset the file system if ZAF_FILE_ID_APP_VERSION is missing since this indicates
    // corrupt or missing file system.
    zafi_nvm_app_reset();
  }
}

ZW_WEAK void
zaf_nvm_app_set_default_configuration(void)
{
}

ZW_WEAK void
zaf_nvm_app_reset(void)
{
}

ZW_WEAK void
zaf_nvm_app_load_configuration(void)
{
}

ZW_WEAK void
zaf_nvm_app_load_configuration_migration(__attribute__((unused)) uint32_t current_version, __attribute__((unused)) uint32_t saved_version)
{
}
