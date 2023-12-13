/***************************************************************************//**
 * @file
 * @brief ABR Antenna Switching
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

#ifndef ABR_ANS_H
#define ABR_ANS_H

#include "sl_common.h"
#include "sl_bgapi.h"
#include "app_log.h"
#include "sl_bt_api.h"

#define MAX_ANTENNA_NUMBER 4
#define USER_CMD_GET_BOARD_NAME_ID  5
#define USER_CMD_SET_ANTENNA_NUM_ID 6
#define USER_CMD_GET_ANTENNA_OFFSET_ID 7
#define USER_RSP_GET_BOARD_NAME_LEN sizeof(uint8_t)
#define ANS_SUPPORTED_BOARD_NAME    "BRD4406A"
typedef struct {
  uint8_t id;
  uint8_t len;
  int16_t ant_offset_cm;
} ans_antenna_t;

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// Public functions

/**************************************************************************//**
 * ABR ANS antenna switching.
 * This function is used to change the antenna. Antenna numbers
 * are changing between 0-3.
 * @return void
 *****************************************************************************/
void ans_antenna_switching();

/**************************************************************************//**
 * ABR ANS decide antenna switching.
 * Decide if antenna switching is necessary. Get Board Name from target.
 * Only BRD4406A is supported. Get antenna offset paramters from target.
 * @param[in] wired Calls ans_set_antenna_offset() with this parameter.
 * If true, wired antenna offset is used. If false, wireless antenna offset
 * is used.
 * @return bool True if antenna switching is necessary
 *****************************************************************************/
bool ans_initiator_decide_antenna_switching(bool wired);

/**************************************************************************//**
 * ABR ANS set next antenna.
 * On BRD4406A there are 4 antennas. In case of antenna switching one antenna
 * is used for one procedure. Before each procedure this function will be
 * called to change the antenna.
 * @param[in] ant Sets the antenna id, offset and len
 * @return void
 *****************************************************************************/
void ans_set_next_antenna(ans_antenna_t* ant);

/**************************************************************************//**
 * ABR ANS set antenna offset.
 * On BRD4406A there are 4 antennas. In case of antenna switching one antenna
 * is used for one procedure. Before each procedure this function will be
 * called to change the antenna.
 * @param[in] offset Array of offset values.
 * @param[in] offset_num Number of antennas.
 * @return void
 *****************************************************************************/
void ans_set_antenna_offset(int16_t *offset, uint8_t offset_num);

#ifdef __cplusplus
};
#endif

#endif // ABR_ANS_H
