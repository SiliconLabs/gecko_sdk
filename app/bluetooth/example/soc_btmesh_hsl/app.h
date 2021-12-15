/***************************************************************************//**
 * @file
 * @brief Application interface provided to main().
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef APP_H
#define APP_H

#include <stdint.h>

/***************************************************************************//**
 * Application Init.
 ******************************************************************************/
void app_init(void);

/***************************************************************************//**
 * Application Process Action.
 ******************************************************************************/
void app_process_action(void);

/***************************************************************************//**
 * Shows the provisioning start information
 *
 * @param[in] result  Result code. 0: success, non-zero: error
 ******************************************************************************/
void app_show_btmesh_node_provisioning_started(uint16_t result);

/*******************************************************************************
 * Called when the Provisioning finishes successfully
 *
 * @param[in] address      Unicast address of the primary element of the node.
                           Ignored if unprovisioned.
 * @param[in] iv_index     IV index for the first network of the node
                           Ignored if unprovisioned.
 ******************************************************************************/
void app_show_btmesh_node_provisioned(uint16_t address,
                                      uint32_t iv_index);

/***************************************************************************//**
 * Shows the node reset information
 ******************************************************************************/
void app_show_btmesh_node_reset(void);

#endif // APP_H
