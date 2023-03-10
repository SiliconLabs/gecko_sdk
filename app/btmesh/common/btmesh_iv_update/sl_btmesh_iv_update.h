/***************************************************************************//**
 * @file
 * @brief Automatic IV Update component header
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_BTMESH_IV_UPDATE_H
#define SL_BTMESH_IV_UPDATE_H

#include "sl_btmesh_api.h"

/***************************************************************************//**
 * @defgroup iv_update Automatic IV Update Component
 * @brief Automatic IV Update Implementation
 * This component implements IV Update related functionality
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup iv_update
 * @{
 ******************************************************************************/

/***************************************************************************//**
 *  Handling of mesh iv_update related events.
 *  @param[in] evt  Pointer to incoming event.
 ******************************************************************************/
void sl_btmesh_iv_update_on_event(sl_btmesh_msg_t *evt);

/** @} (end addtogroup iv_update) */

#endif /* SL_BTMESH_IV_UPDATE_H */
