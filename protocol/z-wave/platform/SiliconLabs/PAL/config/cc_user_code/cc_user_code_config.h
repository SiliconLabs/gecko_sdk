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

#ifndef _CC_USER_CODE_CONFIG_H_
#define _CC_USER_CODE_CONFIG_H_

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Command Class User Code Configuration

// <o CC_USER_CODE_MAX_IDS> Max number of user Code ID's and USER CODES <1..255:1> <f.d>
// <i> Default: 1
#define CC_USER_CODE_MAX_IDS  1

// <a.4 CC_USER_CODE_DEFAULT> The default user code used by the Command Class <0..255> <f.h>
// <i> Default:  { 0x31, 0x32, 0x33, 0x34 }
#define CC_USER_CODE_DEFAULT  { 0x31, 0x32, 0x33, 0x34 }

// </h>

// <<< end of configuration section >>>

#endif /* _CC_USER_CODE_CONFIG_H_ */
