/***************************************************************************//**
 * @file
 * @brief ABR initiator Interface
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

#ifndef ABR_INITIATOR_INTERFACE_H
#define ABR_INITIATOR_INTERFACE_H

/*******************************************************************************
 ********************************  TYPEDEFS  ***********************************
 ******************************************************************************/

typedef enum {
  ABR_STATE_UNINITALIZED = 0,
  ABR_STATE_DISCONNECTED,
  ABR_STATE_CONNECTED,
  ABR_STATE_SCANNING,
} abr_state_t;

/*******************************************************************************
 ******************************   PROTOTYPES   *********************************
 ******************************************************************************/

/**************************************************************************//**
 * @brief
 *   ASCII graphics for indicating wait status
 *
 *****************************************************************************/
void waiting_indication(void);

/**************************************************************************//**
 * @brief
 *   Sets the state value on UI.
 *
 * @param[in] state current state
 *****************************************************************************/
void platform_display_state(abr_state_t state);

#endif // ABR_INITIATOR_INTERFACE_H
