/***************************************************************************//**
 * @file
 * @brief NCP reset configuration.
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

#ifndef NCP_RESET_CONFIG_H
#define NCP_RESET_CONFIG_H

// During init, system reset command is not sent because it can break e.g. the
// multi-protocol use case when used with CPC. Therefore, we just wait for the
// boot event without sending the first system reset command.
#ifndef NCP_RESET_TIMEOUT_INIT_MS
#define NCP_RESET_TIMEOUT_INIT_MS 1000
#endif

// If no boot event is received after the initial timeout, a system reset
// command is sent to the target. After the system reset, we should let enough
// time for the target to boot up and for the CPC to initialize.
#ifndef NCP_RESET_TIMEOUT_RETRY_MS
#define NCP_RESET_TIMEOUT_RETRY_MS 10000
#endif

// System reset is repeated NCP_RESET_RETRY_COUNT times.
#ifndef NCP_RESET_RETRY_COUNT
#define NCP_RESET_RETRY_COUNT 3
#endif

#endif // NCP_RESET_CONFIG_H
