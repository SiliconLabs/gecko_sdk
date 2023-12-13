/**
 * @file
 * Command Class Supervision Configuration API
 * @copyright 2022 Silicon Laboratories Inc.
 */

#include <CC_Supervision.h>
#include "cc_supervision_config.h"

bool cc_supervision_get_default_status_updates_enabled(void)
{
  return CC_SUPERVISION_CONFIG_DEFAULT_STATUS_UPDATES_ENABLED;
}
