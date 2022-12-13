/**
 * @file
 * Handler for Command Class Association Group Info.
 *
 * @addtogroup CC Command Classes
 * @{
 * @addtogroup cc_agi Association Group Information
 * @{
 *
 * CC Association Group Information (CC AGI) reports which commands a device can control and which
 * commands are reported to the Lifeline.
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
 * CC AGI has one API function that is relevant when implementing a
 * command class:
 * - ReqNodeList()
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


#include <ZW_classcmd.h>
#include "ZAF_types.h"
#include "agi.h"

/**
 * @addtogroup CC Command Classes
 * @{
 * @addtogroup cc_agi Association Group Information
 * @{
 */

/**
 * @brief Read AGI group name
 * @param[out] pGroupName OUT point to group name
 * @param[in] groupId IN group identifier
 * @param[in] endpoint IN end-point number
 * @private
 */
extern size_t CC_AGI_groupNameGet_handler(
    char * pGroupName,
    uint8_t groupId,
    uint8_t endpoint);

/**
 * @brief Get application specific Group Info
 * @param[in] groupId group identifier
 * @param[in] endpoint is the endpoint number
 * @param[out] report pointer to data of type VG_ASSOCIATION_GROUP_INFO_REPORT_VG
 * @private
 */
extern void CC_AGI_groupInfoGet_handler(
  uint8_t groupId,
  uint8_t endpoint,
  VG_ASSOCIATION_GROUP_INFO_REPORT_VG* report);

/**
 * @brief Returns the number of association groups for a given endpoint.
 * @param[in] endpoint A given endpoint where 0 is the root device.
 * @return Number of association groups.
 * @private
 */
extern uint8_t CC_AGI_groupCount_handler(uint8_t endpoint);

/**
 * @brief Set Application specific Group Command List
 * @param[out] pGroupList pointer to the list
 * @param[out] pGroupListSize Pointer to a variable that can contain the list size.
 * @param[in] groupId group identifier
 * @param[in] endpoint is the endpoint number
 * @return command status (true/false)
 * @private
 */
extern bool GetApplGroupCommandList(
    uint8_t * pGroupList,
    size_t * pGroupListSize,
    uint8_t groupId,
    uint8_t endpoint);

/**
 * Corrects a given group ID if it's invalid.
 *
 * According to CC:0059.01.05.12.002 in SDS13782-4 "Association Group Command List Report" SHOULD
 * respond with commands for group 1 if the given group ID is invalid (0 or higher than the number
 * of groups for a given endpoint).
 * @param endpoint Endpoint to match against.
 * @param pGroupId Pointer to group ID.
 * @private
 */
extern void ZAF_CC_AGI_CorrectGroupIdIfInvalid(uint8_t endpoint, uint8_t * pGroupId);

/**
 * @}
 * @}
 */

#endif
