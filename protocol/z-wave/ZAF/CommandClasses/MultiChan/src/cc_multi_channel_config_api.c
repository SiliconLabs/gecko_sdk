/**
 * @file
 * Configuration API for CC Multi Channel
 *
 * @copyright 2023 Silicon Laboratories Inc.
 */
#include "cc_multi_channel_config_api.h"
#include "cc_multi_channel_config.h"

bool cc_multi_channel_are_endpoints_identical(void)
{
  return (bool)CC_MULTI_CHANNEL_IDENTICAL_ENDPOINTS;
}
