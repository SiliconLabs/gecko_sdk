/***************************************************************************//**
 * @brief sl_btmesh_hsl_server.h
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

#ifndef SL_BTMESH_HSL_SERVER_H
#define SL_BTMESH_HSL_SERVER_H

#include "sl_btmesh_api.h"

// -----------------------------------------------------------------------------
// Functions which are automatically called when the component is selected

/***************************************************************************//**
 * Handle HSL Server events.
 *
 * This function is called automatically by Universal Configurator after
 * enabling the component.
 *
 * @param[in] evt  Pointer to incoming event.
 ******************************************************************************/
void sl_btmesh_hsl_server_on_event(sl_btmesh_msg_t *evt);

/***************************************************************************//**
 * HSL Server initialization.
 * This should be called at each boot if provisioning is already done.
 * Otherwise this function should be called after provisioning is completed.
 * It is called automatically by the Universal Configurator Framework
 *
 ******************************************************************************/
void sl_btmesh_hsl_server_init(void);

#endif // SL_BTMESH_HSL_SERVER_H
