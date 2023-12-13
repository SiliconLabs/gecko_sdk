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

#ifndef _ZAF_EVENT_DISTRIBUTOR_SOC_CONFIG_H_
#define _ZAF_EVENT_DISTRIBUTOR_SOC_CONFIG_H_

// <<< Use Configuration Wizard in Context Menu >>>

// <h> ZAF Event Distributor Core Configuration

// <o ZAF_EVENT_DISTRIBUTOR_SOC_CONFIG_APP_QUEUE_SIZE> Application event queue size <1..255:1> <f.h>
// <i> Default: 5
#define ZAF_EVENT_DISTRIBUTOR_SOC_CONFIG_APP_QUEUE_SIZE  5

// <o ZAF_EVENT_DISTRIBUTOR_SOC_CONFIG_CC_QUEUE_SIZE> Command Class event queue size <1..255:1> <f.h>
// <i> Default: 2
#define ZAF_EVENT_DISTRIBUTOR_SOC_CONFIG_CC_QUEUE_SIZE  2

// </h>

// <<< end of configuration section >>>

#endif /* _ZAF_EVENT_DISTRIBUTOR_SOC_CONFIG_H_ */
