/**
 * @file
 * Command Class Association Group Information Configuration API
 * @copyright 2022 Silicon Laboratories Inc.
 */

#ifndef CC_AGI_CONFIG_API_H
#define CC_AGI_CONFIG_API_H

#include <agi.h>
#include <stdint.h>
#include <zaf_config.h>

/**
 * @addtogroup CC Command Classes
 * @{
 * @addtogroup cc_agi
 * @{
 * @addtogroup cc_agi_config Configuration of CC Association Group Information
 * @{
 */

/**
 * Struct containing the address of a group array and the number of groups in the array.
 */
typedef struct {
  AGI_GROUP const * const pTable;
  uint8_t tableSize;
} AGI_TABLE_EP;

/**
 * Struct containing the group lists for root device and each endpoint, if any endpoints.
 */
typedef struct {
  AGI_TABLE_EP tableEndpoint[ZAF_CONFIG_NUMBER_OF_END_POINTS + 1];
} AGI_TABLE;

/**
 * Returns the address of the CC AGI configuration table.
 * @return Address of CC AGI configuration table.
 */
const AGI_TABLE* cc_agi_get_config(void);

/**
 * Returns the address of the root device group array.
 * @return Address of root device group array.
 */
const AGI_GROUP* cc_agi_get_rootdevice_groups(void);

/**
 * @}
 * @}
 * @}
 */

#endif /* CC_AGI_CONFIG_API_H */
