/**
 * @file
 * Command Class Association Group Information Configuration API
 * @copyright 2022 Silicon Laboratories Inc.
 */

#ifndef CC_AGI_CONFIG_API_H
#define CC_AGI_CONFIG_API_H

#include "ZAF_types.h"

/**
 * @addtogroup CC Command Classes
 * @{
 * @addtogroup cc_agi
 * @{
 * @addtogroup cc_agi_config Configuration of CC Association Group Information
 * @{
 */

/**
 * Defines an AGI group.
 */
typedef struct {
  const agi_profile_t profile;
  const uint8_t ccc_pair_count;
  const ccc_pair_t * ccc_pairs;
  const char * name;
  const uint8_t name_length;
} cc_agi_group_t;

/**
 * Defines the AGI configuration of one endpoint.
 */
typedef struct {
  const cc_agi_group_t * groups;
  const uint8_t group_count;
} cc_agi_config_t;

/**
 * Returns the address of the first element in the configuration array.
 * @return Address of the first element in the CC AGI configuration.
 */
const cc_agi_config_t * cc_agi_get_config(void);

/**
 * Returns the number of configured groups for a given endpoint.
 * @param endpoint Endpoint.
 * @return Number of groups.
 */
uint8_t cc_agi_config_get_group_count_by_endpoint(uint8_t endpoint);

/**
 * Returns the address of the first element in the array of root device groups.
 *
 * @note The first element is group 2.
 *
 * @return Address of first element in root device group array.
 */
const cc_agi_group_t * cc_agi_get_rootdevice_groups(void);

/**
 * @}
 * @}
 * @}
 */

#endif /* CC_AGI_CONFIG_API_H */
