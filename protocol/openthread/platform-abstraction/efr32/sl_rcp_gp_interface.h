/***************************************************************************//**
 * @file
 * @brief This file implements Green Power interface.
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

#ifndef SL_RCP_GP_INTERFACE_H_
#define SL_RCP_GP_INTERFACE_H_
#include "utils/mac_frame.h"
// GP state-machine states
typedef enum {
    SL_GP_STATE_INIT,
    SL_GP_STATE_IDLE,
    SL_GP_STATE_WAITING_FOR_PKT,
    SL_GP_STATE_SEND_RESPONSE,
    SL_GP_STATE_MAX
} sl_gp_state_t;

/**
 * This function returns if the given frame is a GP frame.
 *
 * @param[in]  aFrame       A pointer to the MAC frame buffer.
 * @param[in]  isRxFrame    If the give frame is a incoming or outgoing frame.
 *
 * @retval  true    Frame is a GP packet.
 * @retval  false   Frame is not a GP packet.
 */
bool sl_gp_intf_is_gp_pkt(otRadioFrame *aFrame, bool isRxFrame);

/**
 * This function stores the provided packet in global memory, to be sent as
 * a response for specific incoming packet.
 *
 * @param[in]  aFrame       A pointer to the MAC frame buffer.
 */
void sl_gp_intf_buffer_pkt(otRadioFrame *aFrame);

/**
 * This function returns current state of GP state machine.
 *
 * @retval  true    Status of GP state machine.
 */
sl_gp_state_t sl_gp_intf_get_state(void);

/**
 * This function performs GP RCP processing.
 *
 */
void efr32GpProcess(void);
#endif