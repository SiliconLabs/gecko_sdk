/***************************************************************************//**
 * @file
 * @brief CPC-HCI bridge
 *
 * This application serves as a bridge between CPCd and btattach. As CPC
 * communication is available through libcpc.so API calls, and BlueZ stack
 * can only attach through btattach command to a UART interface, this app
 * serves as a bridge between the two communication interfaces.
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
#ifndef CPC_HCI_BRIDGE_CONFIG_H
#define CPC_HCI_BRIDGE_CONFIG_H

#define TIMEOUT_SEC                 0
#define TIMEOUT_USEC                5000
#define CPC_TX_BUF_SIZE             256
#define CPC_RX_BUF_SIZE             SL_CPC_READ_MINIMUM_SIZE
#define RETRY_COUNT                 10
#define CPC_RETRY_SLEEP_NS          100000000L
#define CPC_RESET_SLEEP_NS          10000L
#define THREAD_SLEEP_NS             1L
#define CPC_TRANSMIT_WINDOW         1
#define SYMLINK_PATH                "pts_hci"
#define CPC_DEFAULT_INSTANCE_NAME   "cpcd_0"

#endif // CPC_HCI_BRIDGE_CONFIG_H
