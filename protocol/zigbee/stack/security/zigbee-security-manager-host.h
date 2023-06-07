/***************************************************************************//**
 * @file
 * @brief Definitions specific to the host implementation of Zigbee Security
 * Manager.
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef _ZIGBEE_SECURITY_MANAGER_HOST_H_
#define _ZIGBEE_SECURITY_MANAGER_HOST_H_

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "ember-types.h"
#endif

//Default value for context's PSA algorithm permission (CCM* with 4 byte tag).
//Only used by NCPs with secure key storage; define is mirrored here to allow
//host code to initialize the context itself rather than needing a new EZSP frame.
#define ZB_PSA_ALG 0x05440100

//Host-only API to check whether the NCP uses key storage.
uint8_t sl_zb_sec_man_version();

#endif // _ZIGBEE_SECURITY_MANAGER_INTERNAL_H_
