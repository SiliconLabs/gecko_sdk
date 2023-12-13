/*
 *  Copyright (c) 2023, The OpenThread Authors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/*******************************************************************************
 * @file
 * @brief This file implements Green Power interface.
 ******************************************************************************/

#ifndef SL_RCP_GP_INTERFACE_H_
#define SL_RCP_GP_INTERFACE_H_

#include <stdbool.h>
#include <openthread/platform/radio.h>

// GP state-machine states
typedef enum
{
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
