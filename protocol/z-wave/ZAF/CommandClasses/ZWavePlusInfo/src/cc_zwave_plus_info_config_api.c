/**
 * @file
 * Command Class ZWave Plus Info Configuration API
 * @copyright 2022 Silicon Laboratories Inc.
 */

#include "cc_zwave_plus_info_config_api.h"
#include "zaf_config.h"

zw_plus_info_config_icons_t root_icons =
{
  .installer_icon_type = ZAF_CONFIG_INSTALLER_ICON_TYPE,
  .user_icon_type = ZAF_CONFIG_USER_ICON_TYPE,
  .endpoint = 0
};

zw_plus_info_config_icons_t * cc_zwave_plus_info_config_get_root_icons(void)
{
  return &root_icons;
}


