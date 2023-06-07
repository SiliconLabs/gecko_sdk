/**
 * @file
 * Command Class Supervision Configuration API
 * @copyright 2022 Silicon Laboratories Inc.
 */

#ifndef CC_SUPERVISION_CONFIG_API_H
#define CC_SUPERVISION_CONFIG_API_H

#include <CC_Supervision.h>
#include <stdint.h>

/**
 * @addtogroup CC
 * @{
 * @addtogroup Supervision
 * @{
 */

/**
 * @brief Returns whether transmission of status updates is enabled or disabled by default.
 * Used by the Supervion Command Class initialization
 * 
 * @return true if enabled, false if disabled
 */
bool cc_supervision_get_default_status_updates_enabled();

/**
 * @}
 * @}
 */ 

#endif /* CC_SUPERVISION_CONFIG_API_H */
