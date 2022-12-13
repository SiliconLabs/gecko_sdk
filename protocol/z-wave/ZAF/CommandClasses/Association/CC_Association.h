/**
 * @file
 * Handler for Command Class Association.
 *
 * @addtogroup CC
 * @{
 * @addtogroup Association
 * @{
 *
 * CC Association and CC Multi Channel Association enable application level control of
 * other devices.
 *
 * For instance, a wall switch can control an LED bulb if an association to the LED bulb is created
 * in the wall switch. Another example could be a motion sensor that turns on an LED bulb when
 * motion is detected. Such associations can be created using either Association Set or Multi
 * Channel Association Set.
 *
 * Both CCs share a common module that stores the actual associations.
 *
 * The specifications of CC Association and CC Multi Channel Association can be found in
 * https://github.com/Z-Wave-Alliance/AWG/tree/main/source/management_command_classes/command_class_definitions
 *
 * @}
 * @}
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */

#ifndef _CC_ASSOCIATION_H_
#define _CC_ASSOCIATION_H_

#include <ZW_classcmd.h>
#include "ZAF_types.h"

/**
 * @addtogroup CC Command Classes
 * @{
 * @addtogroup Association (Multi Channel) Association
 * @{
 */

/**
 * @brief Returns the latest used association group.
 * @return Latest used association group.
 * @private
 */
extern uint8_t ApplicationGetLastActiveGroupId(void);

/**
 * @brief Returns the maximum number of nodes that can be stored in a given association group for
 * a given endpoint.
 * @param[in] groupIden A given Group ID.
 * @param[in] ep A given endpoint.
 * @return The maximum number of nodes.
 * @private
 */
extern uint8_t handleGetMaxNodesInGroup(
    uint8_t groupIden,
    uint8_t ep);

/**
 * @brief Handler for Association Set command.
 * @param[in] ep A given endpoint.
 * @param[in] pCmd A command containing the nodes to save in the association database.
 * @param[in] cmdLength Length of the command.
 * @param[in] commandClass Caller command class. This function may be called from multiple command classes.
 *            This parameter tells which one was it.
 * @return command handler return code
 * @private
 */
extern e_cmd_handler_return_code_t handleAssociationSet(
    uint8_t ep,
    ZW_MULTI_CHANNEL_ASSOCIATION_SET_1BYTE_V2_FRAME* pCmd,
    uint8_t cmdLength,
    uint8_t commandClass);

/**
 * @}
 * @}
 */

#endif // _CC_ASSOCIATION_H_
