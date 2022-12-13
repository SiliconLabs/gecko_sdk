/**
 * @file app_node_info.c
 * @copyright 2022 Silicon Laboratories Inc.
 */

#include "app_node_info.h"

uint8_t aAppNodeInfoCCUnSecureIncluded[APPL_NODEPARM_MAX];
uint8_t aAppNodeInfoCCSecureIncludedUnSecure[APPL_NODEPARM_MAX];
uint8_t aAppNodeInfoCCSecureIncludedSecure[APPL_NODEPARM_MAX];

SCommandClassSet_t CommandClasses = {
  .UnSecureIncludedCC.iListLength = 0,
  .UnSecureIncludedCC.pCommandClasses = aAppNodeInfoCCUnSecureIncluded,
  .SecureIncludedUnSecureCC.iListLength = 0,
  .SecureIncludedUnSecureCC.pCommandClasses = aAppNodeInfoCCSecureIncludedUnSecure,
  .SecureIncludedSecureCC.iListLength = 0,
  .SecureIncludedSecureCC.pCommandClasses = aAppNodeInfoCCSecureIncludedSecure
};

// Setup defaults
SAppNodeInfo_t AppNodeInfo =
{
#ifdef ZW_CONTROLLER
#ifdef ZW_CONTROLLER_STATIC
        .NodeType.generic = GENERIC_TYPE_STATIC_CONTROLLER,
        .NodeType.specific = SPECIFIC_TYPE_PC_CONTROLLER,
        .DeviceOptionsMask = APPLICATION_NODEINFO_LISTENING
#else  // ifdef ZW_CONTROLLER_STATIC
        .NodeType.generic = GENERIC_TYPE_GENERIC_CONTROLLER,
        .NodeType.specific = SPECIFIC_TYPE_PORTABLE_REMOTE_CONTROLLER,
        .DeviceOptionsMask = APPLICATION_NODEINFO_NOT_LISTENING
#endif // ifdef ZW_CONTROLLER_STATIC
#else  // #ifdef ZW_CONTROLLER
        .NodeType.generic = GENERIC_TYPE_SWITCH_MULTILEVEL,
        .NodeType.specific = SPECIFIC_TYPE_NOT_USED,
        .DeviceOptionsMask = APPLICATION_NODEINFO_LISTENING
#endif // #ifdef ZW_CONTROLLER
};

const uint8_t CCListSizes[3] =
{
  sizeof(aAppNodeInfoCCUnSecureIncluded),
  sizeof(aAppNodeInfoCCSecureIncludedUnSecure),
  sizeof(aAppNodeInfoCCSecureIncludedSecure)
};
