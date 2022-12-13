/***************************************************************************//**
 * @file
 * @brief HCI Three-Wire UART configuration
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
#ifndef SL_HCI_PACKET_3WIRE_CONFIG_H
#define SL_HCI_PACKET_3WIRE_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <e>Override default acknowledge timeout
// <i> The default timeout value is derived from the UART baud rate.
#define SL_HCI_PACKET_3WIRE_OVERRIDE_ACK_TIMEOUT 0

// <o>Acknowledgment packet is sent after a reliable packet in this amount of time if there is no other packet to be sent [ms]
// <i> Default: 710
#define SL_HCI_PACKET_3WIRE_ACK_TIMEOUT_MS 710

// </e>

// <e>Override default resending timeout
// <i> The default timeout value is derived from the UART baud rate.
#define SL_HCI_PACKET_3WIRE_OVERRIDE_RESEND_TIMEOUT 0

// <o>A reliable packet is resent if it is not acknowledged by the remote end in this amount of time [ms]
// <i> Default: 1065
#define SL_HCI_PACKET_3WIRE_RESEND_TIMEOUT_MS 1065

// </e>

// <<< end of configuration section >>>

#endif // SL_HCI_PACKET_3WIRE_CONFIG_H
