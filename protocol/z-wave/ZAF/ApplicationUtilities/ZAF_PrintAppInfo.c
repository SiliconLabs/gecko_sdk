/**
 * @file
 *
 * ZAF PrintAppInfo module source file
 * @copyright 2023 Silicon Laboratories Inc.
 */

#include "DebugPrint.h"
#include "zw_build_no.h"
#include "zpal_misc.h"
#include "ZAF_PrintAppInfo.h"
#include "ZAF_AppName.h"

void ZAF_PrintAppInfo(void)
{
  char app_name[ZAF_FILE_SIZE_APP_NAME];
  ZAF_AppName_Read(app_name);
  DebugPrint("\n\n----------------------------------\n");
  DebugPrintf("Z-Wave Sample App: %s \n", app_name);
  DebugPrintf("SDK: %d.%d.%d ZAF: %d.%d.%d.%d\n",
              SDK_VERSION_MAJOR,
              SDK_VERSION_MINOR,
              SDK_VERSION_PATCH,
              zpal_get_app_version_major(),
              zpal_get_app_version_minor(),
              zpal_get_app_version_patch(),
              ZAF_BUILD_NO);
}
