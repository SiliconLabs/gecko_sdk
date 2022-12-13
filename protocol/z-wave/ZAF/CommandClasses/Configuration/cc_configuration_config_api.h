/***************************************************************************//**
 * @file
 *
 * @copyright 2022 Silicon Laboratories Inc.
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
#ifndef CC_CONFIGURATION_CONFIG_API_H
#define CC_CONFIGURATION_CONFIG_API_H

#include <CC_Configuration.h>

/**
 * @addtogroup CC Command Classes
 * @{
 * @addtogroup Configuration
 * @{
 */

const cc_configuration_t *cc_configuration_get_configuration(void);

/**
 * @}
 * @}
 */

#endif  // CC_CONFIGURATION_CONFIG_API_H
