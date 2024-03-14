/**
 * @file
 * Handler for Command Class Association Group Info.
 *
 * @addtogroup CC Command Classes
 * @{
 * @addtogroup cc_agi Association Group Information
 * @{
 *
 * ## General information
 * 
 * CC Association Group Information (CC AGI) reports which commands a device can control and which
 * commands are reported to the Lifeline.
 * 
 * ## CC AGI configuration
 *
 * The Lifeline group is automatically configured, but other groups may be manually configured if
 * desired. For instance, a wall switch might control a bulb using CC Binary Switch. In such case,
 * the wall switch would need to have an association group defined that lists Binary Switch Set.
 * Simplicity Studio / SLC generates this configuration automatically based on
 * user configuration in *.cc_config files.
 *
 * Example of configuration:
 * @code{.yaml}
 * zw_cc_agi:
 *   endpoints:
 *     - endpoint: 0
 *       groups:
 *         - name: BTN0
 *           profile_msb: ASSOCIATION_GROUP_INFO_REPORT_PROFILE_CONTROL
 *           profile_lsb: ASSOCIATION_GROUP_INFO_REPORT_PROFILE_CONTROL_KEY01
 *           commands:
 *             - command_class: COMMAND_CLASS_BASIC_V2
 *               command: BASIC_SET_V2
 * @endcode
 *
 * The specification of CC AGI can be found in
 * https://github.com/Z-Wave-Alliance/AWG/tree/main/source/management_command_classes/command_class_definitions
 *
 * @}
 * @}
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */

#ifndef _CC_ASSOCIATION_GROUP_INFO_H_
#define _CC_ASSOCIATION_GROUP_INFO_H_

#include "ZAF_types.h"

/**
 * @addtogroup CC Command Classes
 * @{
 * @addtogroup cc_agi Association Group Information
 * @{
 */

/**
 * Returns the number of configured association groups for a given endpoint.
 *
 * This function will return 1 for any endpoint if the node is added to a Z-Wave LR network.
 *
 * @param[in] endpoint A given endpoint where 0 is the root device.
 * @return Number of configured association groups.
 * @private
 */
uint8_t CC_AGI_groupCount_handler(uint8_t endpoint);

/**
 * Returns the association group ID that matches the given AGI profile, command class/command-pair
 * and endpoint.
 *
 * @param[in] profile AGI profile to search for.
 * @param[in] cmdGrp Command class / command pair to search for.
 * @param[in] endpoint Endpoint.
 * @return Returns the group ID, if found. Otherwise 0xFF.
 */
uint8_t cc_agi_get_group_id(agi_profile_t const * const profile,
                            ccc_pair_t const * const cmdGrp,
                            uint8_t const endpoint);

/**
 * @}
 * @}
 */

#endif
