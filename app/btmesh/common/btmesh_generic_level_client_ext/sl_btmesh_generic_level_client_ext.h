/***************************************************************************//**
 * @file
 * @brief Generic Level Client module for Delta Set and Move Set Unacknowledged
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#ifndef SL_BTMESH_GENERIC_LEVEL_CLIENT_EXT_H
#define SL_BTMESH_GENERIC_LEVEL_CLIENT_EXT_H

/****************************************************************************//*
 * Generic Level Client state initialization
 *
 * This is called at each boot if provisioning is already done,
 * otherwise this function is called after provisioning is completed
 ******************************************************************************/
void sl_btmesh_generic_level_client_ext_init(void);

/***************************************************************************//**
 * Handling of mesh generic level client events
 *
 * This function is called automatically by Universal Configurator after
 * enabling the component
 *
 * @param[in] evt  Pointer to incoming event
 ******************************************************************************/
void sl_btmesh_generic_level_client_ext_on_event(sl_btmesh_msg_t *evt);

/***************************************************************************//**
 * Send Generic Level Delta Set Unacknowledged message
 *
 * @param[in] delta The Delta change of the Generic Level state in absolute value
 ******************************************************************************/
void sl_btmesh_generic_level_client_ext_delta_set_unack(int32_t delta);

/***************************************************************************//**
 * Send Generic Level Move Set Unacknowledged message
 *
 * @param[in] delta_level The Delta Level step to calculate Move speed for the Generic Level state
 ******************************************************************************/
void sl_btmesh_generic_level_client_ext_move_set_unack(int16_t delta_level);

/***************************************************************************//**
 * Halt previous Generic Level Move command
 ******************************************************************************/
void sl_btmesh_generic_level_client_ext_halt(void);

#endif // SL_BTMESH_GENERIC_LEVEL_CLIENT_EXT_H
