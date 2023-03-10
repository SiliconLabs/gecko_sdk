/***************************************************************************//**
 * @file
 * @brief Interface of Firmware Update Server
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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
#ifndef SL_BTMESH_FIRMWARE_UPDATE_SERVER_H
#define SL_BTMESH_FIRMWARE_UPDATE_SERVER_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/***************************************************************************//**
 * @addtogroup mesh_fw_update_server BT Mesh Firmware Update Server
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * Initializes the Firmware Update Server application layer component
 ******************************************************************************/
void sl_btmesh_firmware_update_server_init(void);

/***************************************************************************//**
 * Processes BT Mesh stack events for Firmware Update Server application
 *
 * @param[in] evt BT Mesh event
 ******************************************************************************/
void sl_btmesh_firmware_update_server_on_event(sl_btmesh_msg_t *evt);

/***************************************************************************//**
 * Executes a step of firmware verification
 *
 * @note Uses user API callouts.
 ******************************************************************************/
void sl_btmesh_firmware_update_server_verify_step_handle(void);

/***************************************************************************//**
 * Executes a step of metadata check
 *
 * @note Uses user API callouts.
 ******************************************************************************/
void sl_btmesh_firmware_update_server_metadata_check_step_handle(void);

/***************************************************************************//**
 * @} end mesh_fw_update_server
 ******************************************************************************/

#ifdef __cplusplus
}
#endif // __cplusplus

/***************************************************************************//**
 * Check if BT Mesh Firmware Update Server allows the system to sleep
 *
 * @return If it is ok to sleep
 * @retval true The system is allowed to sleep
 * @retval false The system shall be kept awake
 *
 * The verification and metadata check runs in the main loop step by step and
 * therefore the power manager shall not put the system into sleep mode while
 * these operations are not completed.
 ******************************************************************************/
extern bool sl_btmesh_firmware_update_server_is_ok_to_sleep(void);

#endif // SL_BTMESH_FIRMWARE_UPDATE_SERVER_H
