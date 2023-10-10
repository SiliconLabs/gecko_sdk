/***************************************************************************//**
 * @file
 * @brief User API header for BLOB Transfer Server component
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

#ifndef SL_BTMESH_BLOB_TRANSFER_SERVER_API_H
#define SL_BTMESH_BLOB_TRANSFER_SERVER_API_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/***************************************************************************//**
 * @addtogroup mesh_blob_transfer_server
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup mesh_blob_transfer_server_api
 *
 * BT Mesh BLOB Transfer Server user-overridable API
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * Called when starting BLOB transfer
 *
 * @param[in] blob_id Identifier of BLOB to be transferred
 ******************************************************************************/
extern void sl_btmesh_blob_transfer_server_transfer_start(sl_bt_uuid_64_t const *const blob_id);

/***************************************************************************//**
 * Called when new block is started
 *
 * @note Progress is incremented on a chunk basis, but user callback is called
 * on block basis to avoid too frequent calls.
 *
 * @param[in] blob_id Identifier of the BLOB being transferred
 * @param[in] progress Progress in floating point percentage
 ******************************************************************************/
extern void sl_btmesh_blob_transfer_server_transfer_progress(sl_bt_uuid_64_t const *const blob_id,
                                                             float progress);

/***************************************************************************//**
 * Called when BLOB transfer is done
 *
 * @param[in] blob_id Identifier of BLOB transferred
 ******************************************************************************/
extern void sl_btmesh_blob_transfer_server_transfer_done(sl_bt_uuid_64_t const *const blob_id);

/***************************************************************************//**
 * Called when BLOB transfer is aborted
 *
 * @param[in] blob_id Identifier of BLOB being transferred
 ******************************************************************************/
extern void sl_btmesh_blob_transfer_server_transfer_abort(sl_bt_uuid_64_t const *const blob_id);

/***************************************************************************//**
 * Called when BLOB storage signals it's full
 ******************************************************************************/
extern void sl_btmesh_blob_transfer_server_storage_full(void);

/** @} end mesh_blob_transfer_server_api */

/** @} end mesh_blob_transfer_server */

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // SL_BTMESH_BLOB_TRANSFER_SERVER_API_H
