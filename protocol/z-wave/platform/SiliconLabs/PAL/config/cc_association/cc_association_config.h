/***************************************************************************//**
 * # License
 * <b> Copyright 2023 Silicon Laboratories Inc. www.silabs.com </b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of the Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * https://www.silabs.com/about-us/legal/master-software-license-agreement
 * By installing, copying or otherwise using this software, you agree to the
 * terms of the MSLA.
 *
 ******************************************************************************/

#ifndef _CC_ASSOCIATION_CONFIG_H_
#define _CC_ASSOCIATION_CONFIG_H_

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Command Class Association - Group and Nodes configuration

// <o CC_ASSOCIATION_MAX_GROUPS_PER_ENDPOINT> Max number of groups <1..18:1> <f.d>
// <i> Maximum number of groups per endpoint
// <i> Default: 1
#define CC_ASSOCIATION_MAX_GROUPS_PER_ENDPOINT  1

// <o CC_ASSOCIATION_MAX_NODES_IN_GROUP> Max number of nodes <1..18:1> <f.d>
// <i> Maximum number of nodes in a group
// <i> Default: 5
#define CC_ASSOCIATION_MAX_NODES_IN_GROUP  5

// </h>

// <<< end of configuration section >>>

#endif /* _CC_ASSOCIATION_CONFIG_H_ */
