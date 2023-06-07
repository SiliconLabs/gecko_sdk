/***************************************************************************//**
 * @file
 * @brief
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
#ifndef SIMPLE_RAIL_CONFIG_H_
#define SIMPLE_RAIL_CONFIG_H_

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Size of the RAIL RX FIFO
// <o SL_FLEX_RAIL_RX_FIFO_SIZE> Capacity of the RAIL RX FIFO
// <128=> 128
// <256=> 256
// <512=> 512
// <1024=> 1024
// <2048=> 2048
// <4096=> 4096
// <i> Default: 256
#define SL_FLEX_RAIL_RX_FIFO_SIZE  256
// </h>

// <h> Size of the RAIL TX FIFO
// <o SL_FLEX_RAIL_TX_FIFO_SIZE> Capacity of the RAIL TX FIFO
// <128=> 128
// <256=> 256
// <512=> 512
// <1024=> 1024
// <2048=> 2048
// <4096=> 4096
// <i> Default: 256
#define SL_FLEX_RAIL_TX_FIFO_SIZE  256
// </h>

#endif /* SIMPLE_RAIL_CONFIG_H_ */
