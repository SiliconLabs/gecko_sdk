/***************************************************************************/ /**
 * @file
 * @brief CPC weak function prototypes grouped into one header. Those functions
 *        should be implemented by the user.
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

#ifndef SL_CPC_WEAK_PROTOTYPES_H
#define SL_CPC_WEAK_PROTOTYPES_H

#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif
#include "sl_common.h"
#include "sli_cpc_system_common.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

/***************************************************************************/ /**
 * @addtogroup cpc CPC
 * @{
 ******************************************************************************/

#if defined(SL_CATALOG_CPC_SECONDARY_PRESENT)
/***************************************************************************//**
 * Called when secondary app version is requested.
 * The format is up to the user. The string should be null terminated.
 ******************************************************************************/
const char* sl_cpc_secondary_app_version(void);
#endif

#if defined(SL_CATALOG_CPC_PRIMARY_PRESENT)

/***************************************************************************//**
 * Called when primary app version is requested.
 * The format is up to the user. The string should be null terminated.
 *
 * @note : CPC source code contains a weak definition that default to returning
 *         "UNDEFINED". If the user provides a strong definition of this function,
 *         the user shall return a static string.
 *
 * @return : String that represents the application version.
 ******************************************************************************/
const char* sl_cpc_primary_app_version(void);

/***************************************************************************//**
 * Callback implemented by the user to verify if the secondary application version
 * is compatible with this primary version.
 *
 * @note : If this function is not implemented, then no version check will be performed
 *         and CPC API will always be available after the startup sequence.
 *
 * @note : The function prototype is declared as weak. No default weak definition exist.
 *
 * @return bool :
 *   true : CPC is authorized to start normally
 *   false : The user decided that the application versions are not compatible.
 *           CPC API will be blocked and only a firmware upgrade will be possible
 ******************************************************************************/
SL_WEAK bool sl_cpc_user_is_ok_to_run(const char* primary_app_version, const char* secondary_app_version);

/***************************************************************************//**
 * Fetch the next firmware update image chunk from the user.
 *
 * @note : The prototype is declared as weak and no weak definition exist in CPC code.
 *         Not providing an implementation by the user is valid, although if the user asks
 *         to perform a firmware upgrade, sl_firmware_upgrade_start() will return SL_STATUS_NOT_AVAILABLE
 *
 * @param[in] chunk_buffer : 128 bytes buffer into which the user must copy the chunk
 *
 * @param[in] index : The byte index of the chunk being requested. When the FWU starts, the index starts
 *                    at 0 and will increment by 128 (chunk size) after each time the user submits a chunk.
 *
 * @param[in] chunk_size : This will always be 128 (chunk size) and is the number of bytes the user must copy into
 *                         the chunk_buffer. The only exception is for the last chunk; if the last chunk is less than
 *                         128 bytes, then the user must copy the the remaining bytes and return the size of the last
 *                         chunk in the 'size' out parameter.
 *
 * @param[out] size : This is the number of bytes the user has copied into the chunk buffer. For all chunks except the last
 *                    one, this value is expected to be 128 bytes, and some value between 1-128 for the last chunk.
 *
 * @param[out] last : false if the chunk is not the last chunk. The firmware update state machine will continue fetching
 *                    chunks from the user as long as the user does not return true on the last chunk.
 *
 * @return sl_status_t : Whether or not the user has written a valid chunk. In the case where the user does not have the
 *                requested chunk in hand when this function is called and does not want to block (for example, fetching
 *                is from a serial link or an external storage), SL_STATUS_NOT_READY would be returned. The firmware
 *                update state machine will retry later to ask the user for the chunk. The index will remain the same at
 *                the next call. When a value of SL_STATUS_OK is returned, the state machine will go ahead and send the
 *                chunk to the secondary.
 ******************************************************************************/
SL_WEAK sl_status_t sl_cpc_get_fwu_chunk(uint8_t * const chunk_buffer, const size_t index, const size_t chunk_size, size_t *size, bool *last);

#endif

/** @} (end addtogroup cpc) */

#ifdef __cplusplus
}
#endif

#endif // SL_CPC_H
