/***************************************************************************//**
 * @brief The API between HCI and common HCI transport.
 *
 * The interface configuration shall be done using UC configuration.
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

#ifndef _HCI_COMMON_TRANSPORT_H_
#define _HCI_COMMON_TRANSPORT_H_

#include <stdbool.h>
#include <stdint.h>
#include "sl_btctrl_hci.h"

/**
 * The HCI receives a message from currently selected transport layer.
 * The HCI transport calls this function implemented in the HCI
 * once it has received a complete HCI message. If the HCI does not
 * manage to process the message, the transport may drop the message.
 * @param[in] data Pointer to the received data.
 * @param[in] len Length of the received data.
 * @param[in] lastFragment Indicates if this is the last fragment of
 *       a complete HCI message.
 * @return  0 - success
 *         -1 - out of memory
 *         -2 - badly formatted message. */
int16_t hci_common_transport_receive(uint8_t *data, int16_t len, bool lastFragment);

/**
 * Transmit HCI message using the currently used transport layer.
 * The HCI calls this function to transmit a full HCI message.
 * @param[in] data Data buffer to be transmitted.
 * @param[in] len Length of the data.
 * @return 0 - on success, or non-zero on failure. */
uint32_t hci_common_transport_transmit(uint8_t *data, int16_t len);

/**
 * The HCI transport indicates a message has been transmitted. */
void hci_common_transport_transmit_complete(uint32_t status);

/**
 * The HCI transport has been reconnected with the host. */
void hci_common_transport_transmit_reconnected(void);

/**
 * Initialize the currently selected transport layer. */
void hci_common_transport_init(void);

#endif // _COMMON_TRANSPORT_H_
