/**
 * @file
 * @copyright 2023 Silicon Laboratories Inc.
 */

#ifndef _CC_ASSOCIATION_CONFIG_H_
#define _CC_ASSOCIATION_CONFIG_H_

/**
 * \defgroup configuration Configuration
 * Configuration
 *
 * \addtogroup configuration
 * @{
 */
/**
 * \defgroup cc_association_group_nodes_configuration Command Class Association - Group and Nodes configuration
 * Command Class Association - Group and Nodes configuration
 *
 * \addtogroup cc_association_group_nodes_configuration
 * @{
 */

/**
 * Max number of groups <1..18:1>
 *
 * Maximum number of groups per endpoint
 */
#if !defined(CC_ASSOCIATION_MAX_GROUPS_PER_ENDPOINT)
#define CC_ASSOCIATION_MAX_GROUPS_PER_ENDPOINT  1
#endif /* !defined(CC_ASSOCIATION_MAX_GROUPS_PER_ENDPOINT) */

/**
 * Max number of nodes <1..18:1>
 *
 * Maximum number of nodes in a group
 */
#if !defined(CC_ASSOCIATION_MAX_NODES_IN_GROUP)
#define CC_ASSOCIATION_MAX_NODES_IN_GROUP  5
#endif /* !defined(CC_ASSOCIATION_MAX_NODES_IN_GROUP) */

/**@}*/ /* \addtogroup cc_association_group_nodes_configuration */

/**@}*/ /* \addtogroup configuration */
#endif /* _CC_ASSOCIATION_CONFIG_H_ */
