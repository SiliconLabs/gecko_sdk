/***************************************************************************//**
 * @file
 * @brief BT Mesh Firmware Distribution Server internal interfaces
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

#ifndef SLI_BTMESH_FW_DISTRIBUTION_SERVER_H_
#define SLI_BTMESH_FW_DISTRIBUTION_SERVER_H_

#include "sl_btmesh_dfu_platform_capi.h"

/***************************************************************************//**
 * Look up firmware information in NVM for given index
 *
 * @param element_index Index of the element
 * @param fw_index Index of the firmware
 * @param info Information buffer structure
 *
 * @return Status code
 * @retval SL_STATUS_OK In case of success
 * @retval SL_STATUS_INVALID_STATE If firmware list is uninitialized
 * @retval SL_STATUS_BT_MESH_DOES_NOT_EXIST If index is not in range
 ******************************************************************************/
sl_status_t sli_btmesh_fw_dist_server_get_fw_by_index(uint16_t element_index,
                                                      uint16_t fw_index,
                                                      mesh_dfu_dist_server_fw_info_t *info);

#endif // SLI_BTMESH_FW_DISTRIBUTION_SERVER_H_
