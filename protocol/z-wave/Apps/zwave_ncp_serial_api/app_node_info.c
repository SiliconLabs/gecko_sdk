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

const uint8_t CCListSizes[3] =
{
  sizeof(aAppNodeInfoCCUnSecureIncluded),
  sizeof(aAppNodeInfoCCSecureIncludedUnSecure),
  sizeof(aAppNodeInfoCCSecureIncludedSecure)
};
