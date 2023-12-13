/**
 * @file
 * @copyright 2023 Silicon Laboratories Inc.
 */
#include "zaf_protocol_config.h"
#include "zw_config_rf.h"
#include "zw_region_config.h"
#include "zaf_config.h"
#include "zaf_config_security.h"

ZW_WEAK const SVirtualSlaveNodeInfoTable_t VirtualSlaveNodeInfoTable = {
  .iTableLength = 0,
  .ppNodeInfo = NULL
};

/**
 * Set up security keys to request when joining a network.
 */
static const uint8_t SecureKeysRequested = ZAF_CONFIG_REQUESTED_SECURITY_KEYS;

static SAppNodeInfo_t AppNodeInfo =
{
  .DeviceOptionsMask = ZAF_CONFIG_DEVICE_OPTION_MASK,
  .NodeType.generic = ZAF_CONFIG_GENERIC_TYPE,
  .NodeType.specific = ZAF_CONFIG_SPECIFIC_TYPE,
};

static SRadioConfig_t RadioConfig =
{
  .iListenBeforeTalkThreshold = ELISTENBEFORETALKTRESHOLD_DEFAULT,
  .iTxPowerLevelMax = APP_MAX_TX_POWER,
  .iTxPowerLevelAdjust = APP_MEASURED_0DBM_TX_POWER,
  .iTxPowerLevelMaxLR = APP_MAX_TX_POWER_LR,
  .eRegion = ZW_REGION,
  .radio_debug_enable = ENABLE_RADIO_DEBUG
};

static const SProtocolConfig_t ProtocolConfig = {
  .pVirtualSlaveNodeInfoTable = &VirtualSlaveNodeInfoTable,
  .pSecureKeysRequested = &SecureKeysRequested,
  .pNodeInfo = &AppNodeInfo,
  .pRadioConfig = &RadioConfig
};

SAppNodeInfo_t *zaf_get_app_node_info(void)
{
  return &AppNodeInfo;
}

SRadioConfig_t* zaf_get_radio_config(void)
{
  return &RadioConfig;
}

const SProtocolConfig_t *zaf_get_protocol_config(void)
{
  return &ProtocolConfig;
}
