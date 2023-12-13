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

#ifndef _ZPAL_ZWAVE_NVM_INSTANCE_CONFIG_H_
#define _ZPAL_ZWAVE_NVM_INSTANCE_CONFIG_H_

// <<< Use Configuration Wizard in Context Menu >>>

// <h>ZAF NVM3 config

#ifndef ZPAL_ZW_NVM_CACHE_SIZE
// <o ZPAL_ZW_NVM_CACHE_SIZE> NVM3 Z-Wave Instance Cache Size
// <i> Number of NVM3 objects to cache. To reduce access times this number
// <i> should be equal to or higher than the number of NVM3 objects in the
// <i> Z-Wave NVM3 instance (all ZAF and application NVM3 objects).
// <i> Count of objects stored by ZAF depend on the application. At least
// <i> 11 object should be reserved for ZAF.
// <i> see [TODO add a user documentation] for more details
// <i> Default: 11
#define ZPAL_ZW_NVM_CACHE_SIZE  11
#endif

#ifndef ZPAL_ZW_NVM_MAX_OBJECT_SIZE
//<o ZPAL_ZW_NVM_MAX_OBJECT_SIZE> NVM3 Z-Wave Instance Max Object Size
//<i> Size of the largest object that can be stored by ZAF or application.
//<i> For ZAF, it should be at least the largest of:
//<i> - CC_NOTIFICATION_MAX_NOTIFICATIONS
//<i> - 3 * CC_ASSOCIATION_MAX_NODES_IN_GROUP * (1+ZAF_CONFIG_NUMBER_OF_END_POINTS) + CC_ASSOCIATION_MAX_GROUPS_PER_ENDPOINT
//<i> - 204 (minimum required by nvm3 library)
//<i> Default: 204
#define ZPAL_ZW_NVM_MAX_OBJECT_SIZE 204
#endif

#ifndef ZPAL_ZW_NVM_INSTANCE_REPACK_HEADROOM
// <o ZPAL_ZW_NVM_INSTANCE_REPACK_HEADROOM> NVM3 Z-Wave Instance User Repack Headroom
//<i> Headroom determining how many bytes below the forced repack limit the user
//<i> repack limit should be placed.
//<i> Default: 12
#define ZPAL_ZW_NVM_INSTANCE_REPACK_HEADROOM  12
#endif

// </h>

// <<< end of configuration section >>>

#endif /* _ZPAL_ZWAVE_NVM_INSTANCE_CONFIG_H_ */
