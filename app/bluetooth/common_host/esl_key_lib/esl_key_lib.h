/***************************************************************************//**
 * @file
 * @brief ESL key library header file.
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
#ifndef ESL_KEY_LIB_H
#define ESL_KEY_LIB_H

// -----------------------------------------------------------------------------
// Includes

#include "sl_status.h"
#include "sl_bt_api.h"
#include "esl_tag_core.h"

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// Macros and Typedefs
#ifdef WIN_DLL // compiler shall define this during windows build procedure
 #define DLL_EXPORT __declspec(dllexport)
#else
 #define DLL_EXPORT
#endif

///@typedef Pointer type for database handle
typedef struct db_handle_s *db_handle_p;

///@typedef Pointer type for a database record handle
typedef struct db_record_s *db_record_p;

///@typedef Possible record types enumeration
typedef enum {
  ESL_KEY_LIB_INVALID_RECORD = 0, // guard value, do not use!
  ESL_KEY_LIB_AP_RECORD,
  ESL_KEY_LIB_TAG_RECORD
} esl_key_lib_record_type_t;

// -----------------------------------------------------------------------------
// Database main interfaces

/**************************************************************************//**
 * Init ESL key database.
 *
 * @param[in] db_id Database ID.
 * @param[out] hnd_out Database handle.
 *
 * @retval SL_STATUS_OK Init successful.
 * @retval SL_STATUS_NULL_POINTER One or more parameters are passed as NULL.
 * @retval SL_STATUS_ALLOCATION_FAILED Cannot allocate database handle.
 * @retval SL_STATUS_INITIALIZATION Init failed.
 *
 * @note On status failures the handle will be NULL.
 *****************************************************************************/
sl_status_t DLL_EXPORT esl_key_lib_init_database(const char* db_id, db_handle_p *hnd_out);

/**************************************************************************//**
 * Deinit ESL key database.
 *
 * @param[in] hnd Handle of database to deinit.
 *
 * @retval SL_STATUS_OK Deinit successful.
 * @retval SL_STATUS_NULL_POINTER Input parameter passed as NULL.
 * @retval SL_STATUS_BUSY If database can't be closed yet - please repeat the
 *                        call later!
 * @retval SL_STATUS_FAILED If something went otherwise wrong.
 *****************************************************************************/
sl_status_t DLL_EXPORT esl_key_lib_deinit_database(db_handle_p hnd);

/**************************************************************************//**
 * Allocate space for a record.
 *
 * @param[in] type Record type.
 * @param[out] record_hnd_out Record handle.
 *
 * @retval SL_STATUS_OK Allocation was successful.
 * @retval SL_STATUS_INVALID_PARAMETER Record type is invalid or record_hnd_out
 *                                     is NULL.
 * @retval SL_STATUS_ALLOCATION_FAILED Allocation was not successful.
 *
 * @note On status failures the record_hnd_out will be NULL.
 *       After successful allocation it's the user's responsibility to free the
 *       record's storage space by calling @ref esl_key_lib_free_record()
 *****************************************************************************/
sl_status_t DLL_EXPORT esl_key_lib_alloc_record(esl_key_lib_record_type_t type,
                                                db_record_p *record_hnd_out);

/**************************************************************************//**
 * Free up space previously allocated for a database record.
 *
 * @param[in] ptr Record handle.
 *****************************************************************************/
void DLL_EXPORT esl_key_lib_free_record(db_record_p ptr);

/**************************************************************************//**
 * Store record in the database.
 *
 * @param[in] db_hnd Database handle.
 * @param[in] record_hnd Record handle.
 *
 * @retval SL_STATUS_OK Storing was successful.
 * @retval SL_STATUS_FAILED Failed storing the record.
 * @retval SL_STATUS_NULL_POINTER Any of the input parameters are NULL.
 * @retval SL_STATUS_OBJECT_WRITE SQLite step() is not SQLITE_OK (Mostly due
 *                                to UNIQUE or FOREIGN_KEY constraints!)
 * @retval SL_STATUS_ABORT SQLite finalize() is not SQLITE_OK.
 *****************************************************************************/
sl_status_t DLL_EXPORT esl_key_lib_store_record(const db_handle_p db_hnd,
                                                const db_record_p record_hnd);

/**************************************************************************//**
 * Store record in the database then set bind address.
 *
 * @param[in] db_hnd Database handle.
 * @param[in] record_hnd Record handle.
 * @param[in] bind_addr BLE address.
 *
 * @retval SL_STATUS_OK Storing was successful.
 * @retval SL_STATUS_FAILED Failed storing the record.
 * @retval SL_STATUS_NULL_POINTER Any of the input parameters are NULL.
 * @retval SL_STATUS_OBJECT_WRITE SQLite step() is not SQLITE_OK. (Mostly due
 *                                to UNIQUE or FOREIGN_KEY constraints!)
 * @retval SL_STATUS_ABORT SQLite finalize() is not SQLITE_OK.
 * @retval SL_STATUS_INVALID_TYPE The given record type is an AP record.
 *****************************************************************************/
sl_status_t DLL_EXPORT esl_key_lib_store_record_and_bind(const db_handle_p db_hnd,
                                                         const db_record_p record_hnd,
                                                         const bd_addr *bind_addr);

/**************************************************************************//**
 * Delete record from the database.
 *
 * @param[in] db_hnd Database handle.
 * @param[in] record_hnd Record handle.
 *
 * @retval SL_STATUS_OK Deleting was successful.
 * @retval SL_STATUS_NULL_POINTER Any of the input parameters are NULL.
 * @retval SL_STATUS_INVALID_PARAMETER Record type is invalid.
 * @retval SL_STATUS_FAILED Failed deleting the record.
 *****************************************************************************/
sl_status_t DLL_EXPORT esl_key_lib_delete_record(const db_handle_p db_hnd,
                                                 const db_record_p record_hnd);

/**************************************************************************//**
 * Clear the whole database.
 *
 * @param[in] hnd Database handle.
 *
 * @retval SL_STATUS_OK Clearing was successful.
 * @retval SL_STATUS_FAILED Failed clearing the database.
 *****************************************************************************/
sl_status_t DLL_EXPORT esl_key_lib_clear_database(const db_handle_p hnd);

/**************************************************************************//**
 * Get a record by BLE address directly from the key database.
 *
 * @param[in] db_hnd Database handle.
 * @param[in] ble_address Reference to BLE address to search for in the DB.
 * @param[out] record_hnd_out Record handle to the record if found, NULL
 *                            otherwise
 *
 * @retval SL_STATUS_OK Record acquired successfully - returns ok even if the
 *                      record is incomplete (e.g. not bound yet, etc.)
 * @retval SL_STATUS_FAIL Database (db_hnd) can't be opened or closed properly.
 * @retval SL_STATUS_NOT_FOUND Record was not found.
 * @retval SL_STATUS_NULL_POINTER One or more input parameter is NULL
 * @retval SL_STATUS_INITIALIZATION Error occurred during the database init or
 *                                  deinit.
 *
 * @note The caller will own the resulting record_hnd_out thus needs to
 *       release it by calling @ref esl_key_lib_free_record() on it after the
 *       work is done.
 *****************************************************************************/
sl_status_t DLL_EXPORT esl_key_lib_get_record_by_ble_address(const db_handle_p db_hnd,
                                                             const bd_addr *ble_address,
                                                             db_record_p *record_hnd_out);

/**************************************************************************//**
 * Get a record by ESL address directly from the key database.
 *
 * @param[in] db_hnd Database handle.
 * @param[in] esl_address ESL address.
 * @param[out] record_hnd_out Record handle to the record if found, NULL
 *                            otherwise
 *
 * @retval SL_STATUS_OK Record acquired successfully - returns ok even if the
 *                      record is incomplete (e.g. not bound yet, etc.)
 * @retval SL_STATUS_FAIL Database (db_hnd) can't be opened or closed properly.
 * @retval SL_STATUS_NOT_FOUND Record was not found.
 * @retval SL_STATUS_NULL_POINTER One or more input parameter is NULL
 * @retval SL_STATUS_INITIALIZATION Error occurred during the database init or
 *                                  deinit.
 * @note The caller will own the resulting record_hnd_out thus needs to
 *       release it by calling @ref esl_key_lib_free_record() on it after the
 *       work is done.
 *****************************************************************************/
sl_status_t DLL_EXPORT esl_key_lib_get_record_by_esl_address(const db_handle_p db_hnd,
                                                             const esl_address_t esl_address,
                                                             db_record_p *record_hnd_out);

// -----------------------------------------------------------------------------
// Setter interfaces for record data

/**************************************************************************//**
 * Set the BLE address for a record.
 *
 * @param[in] addr BLE address.
 * @param[in] ptr Record handle.
 *
 * @retval SL_STATUS_OK Setting the address was successful.
 * @retval SL_STATUS_FAILED Failed setting the address (if addr = NULL).
 *****************************************************************************/
sl_status_t DLL_EXPORT esl_key_lib_set_ble_address(const bd_addr *addr, db_record_p ptr);

/**************************************************************************//**
 * Set ESL address for a record.
 *
 * @param[in] addr ESL address.
 * @param[in] record_hnd Record handle.
 *
 * @retval SL_STATUS_OK Setting the address was successful.
 * @retval SL_STATUS_NULL_POINTER If record_hnd is NULL.
 * @retval SL_STATUS_INVALID_PARAMETER The given ESL address is invalid by ESLP.
 *****************************************************************************/
sl_status_t DLL_EXPORT esl_key_lib_set_esl_address(const esl_address_t addr,
                                                   db_record_p record_hnd);

/**************************************************************************//**
 * Set long term key (LTK) for an ESL record.
 *
 * @param[in] ltk_key LTK key
 * @param[in] record_hnd Record handle.
 *
 * @retval SL_STATUS_OK Setting the LTK was successful.
 * @retval SL_STATUS_NULL_POINTER If ltk_key = NULL or record_hnd = NULL.
 * @retval SL_STATUS_INVALID_TYPE If record type is AP type.
 *****************************************************************************/
sl_status_t DLL_EXPORT esl_key_lib_set_long_term_key(const aes_key_128 *ltk_key,
                                                     db_record_p ptr);

/**************************************************************************//**
 * Set Identity key (IRK) for an AP record.
 *
 * @param[in] id_key IRK key
 * @param[in] record_hnd Record handle.
 *
 * @retval SL_STATUS_OK Setting the Identity key was successful.
 * @retval SL_STATUS_NULL_POINTER If id_key = NULL or record_hnd = NULL.
 * @retval SL_STATUS_INVALID_TYPE If record type is ESL type.
 *****************************************************************************/
sl_status_t DLL_EXPORT esl_key_lib_set_identity_key(const aes_key_128 *id_key,
                                                    db_record_p record_hnd);

/**************************************************************************//**
 * Set AP key material for an AP record.
 *
 * @param[in] ap_key AP key
 * @param[in] record_hnd Record handle.
 *
 * @retval SL_STATUS_OK Setting the AP key material was successful.
 * @retval SL_STATUS_NULL_POINTER One or more input parameter is NULL
 * @retval SL_STATUS_INVALID_TYPE If record type is ESL type.
 *****************************************************************************/
sl_status_t DLL_EXPORT esl_key_lib_set_ap_key_material(const sl_bt_ead_key_material_p ap_key,
                                                       db_record_p record_hnd);

/**************************************************************************//**
 * Set Response key material for an ESL record.
 *
 * @param[in] response_key Response key
 * @param[in] record_hnd Record handle.
 *
 * @retval SL_STATUS_OK Setting the Response key material was successful.
 * @retval SL_STATUS_NULL_POINTER One or more input parameter is NULL
 * @retval SL_STATUS_INVALID_TYPE If record type is AP type.
 *****************************************************************************/
sl_status_t DLL_EXPORT esl_key_lib_set_response_key_material(const sl_bt_ead_key_material_p response_key,
                                                             db_record_p record_hnd);

// -------------------------------
// Getter interfaces for record data
/**************************************************************************//**
 * Get the type of a record.
 *
 * @param[in] record_hnd Record handle.
 * @param[out] type_out Type.
 *
 * @retval SL_STATUS_OK Getting the type of the record was successful.
 * @retval SL_STATUS_NULL_POINTER If any of the parameters are NULL.
 *****************************************************************************/
sl_status_t DLL_EXPORT esl_key_lib_get_record_type(const db_record_p record_hnd,
                                                   esl_key_lib_record_type_t *type_out);

/**************************************************************************//**
 * Get the BLE address of a record.
 *
 * @param[in] record_hnd Record handle.
 * @param[out] addr_out BLE address.
 *
 * @retval SL_STATUS_OK Getting the BLE address of the record was successful.
 * @retval SL_STATUS_NULL_POINTER If any of the parameters are NULL.
 *****************************************************************************/
sl_status_t DLL_EXPORT esl_key_lib_get_ble_address(const db_record_p record_hnd,
                                                   bd_addr *addr_out);

/**************************************************************************//**
 * Get the ESL address of a record.
 *
 * @param[in] record_hnd Record handle.
 * @param[out] addr_out ESL address.
 *
 * @retval SL_STATUS_OK Getting the Type of the Record was successful.
 * @retval SL_STATUS_NULL_POINTER If record_hnd and / or addr_out are NULL.
 * @retval SL_STATUS_INVALID_TYPE If record type is AP type.
 *****************************************************************************/
sl_status_t DLL_EXPORT esl_key_lib_get_esl_address(const db_record_p record_hnd,
                                                   esl_address_t *addr_out);

/**************************************************************************//**
 * Get bind address of a record, if bound already.
 *
 * @param[in] db_hnd Database handle.
 * @param[in] record_hnd Record handle.
 * @param[out] addr_out BLE address of the paired device (if any).
 *
 * @retval SL_STATUS_OK Getting the bind address was successful.
 * @retval SL_STATUS_NULL_POINTER If handle(s) and / or addr_out are NULL.
 * @retval SL_STATUS_INVALID_TYPE If record type is improper (must be ESL!)
 * @retval SL_STATUS_NOT_FOUND Bonded pair was not found.
 *****************************************************************************/
sl_status_t DLL_EXPORT esl_key_lib_get_bind_address(const db_handle_p db_hnd,
                                                    const db_record_p record_hnd,
                                                    bd_addr *addr_out);

/**************************************************************************//**
 * Get the Long Term Key of a record.
 *
 * @param[in] record_hnd Record handle (must be ESL type).
 * @param[out] ltk_key_out LTK key.
 *
 * @retval SL_STATUS_OK Getting the Long Term Key of the record was successful.
 * @retval SL_STATUS_NULL_POINTER If any of the parameters are NULL.
 * @retval SL_STATUS_NOT_INITIALIZED If record_hnd->long_term_key is unset.
 * @retval SL_STATUS_INVALID_TYPE If record type is AP type.
 *****************************************************************************/
sl_status_t DLL_EXPORT esl_key_lib_get_long_term_key(const db_record_p record_hnd,
                                                     aes_key_128 *ltk_key_out);

/**************************************************************************//**
 * Get the Identity Key of a record.
 *
 * @param[in] record_hnd Record handle (must be AP type).
 * @param[out] id_key_out IRK key.
 *
 * @retval SL_STATUS_OK Getting the Identity key of the record was successful.
 * @retval SL_STATUS_NULL_POINTER If any of the parameters are NULL.
 * @retval SL_STATUS_NOT_INITIALIZED If record_hnd->id_key is unset.
 * @retval SL_STATUS_INVALID_TYPE If record type is ESL type.
 *****************************************************************************/
sl_status_t DLL_EXPORT esl_key_lib_get_identity_key(const db_record_p record_hnd,
                                                    aes_key_128 *id_key_out);

/**************************************************************************//**
 * Get the AP Key Material of a record.
 *
 * @param[in] record_hnd Record handle (must be AP type).
 * @param[out] ap_key_out AP key.
 *
 * @retval SL_STATUS_OK Getting the AP key material was successful.
 * @retval SL_STATUS_NULL_POINTER If any of the parameters are NULL.
 * @retval SL_STATUS_INVALID_TYPE If record type is ESL type.
 *****************************************************************************/
sl_status_t DLL_EXPORT esl_key_lib_get_ap_key_material(const db_record_p record_hnd,
                                                       sl_bt_ead_key_material_p ap_key_out);

/**************************************************************************//**
 * Get the Response Key Material of a record.
 *
 * @param[in] record_hnd Record handle (must be ESL type).
 * @param[out] response_key_out Response key.
 *
 * @retval SL_STATUS_OK Getting the Response Key Material was successful.
 * @retval SL_STATUS_NULL_POINTER If any of the parameters are NULL.
 * @retval SL_STATUS_NOT_INITIALIZED If Response Key Material is unset.
 * @retval SL_STATUS_INVALID_TYPE If record type is AP type.
 *****************************************************************************/
sl_status_t DLL_EXPORT esl_key_lib_get_response_key_material(const db_record_p record_hnd,
                                                             sl_bt_ead_key_material_p response_key_out);

// -------------------------------
// Wrappers

/**************************************************************************//**
 * Delete record by BLE address.
 *
 * @param[in] db_hnd Database handle.
 * @param[in] ble_address Reference to BLE address to delete from DB.
 *
 * @retval SL_STATUS_OK Deleting the record was successful. Otherwise please
 *                      refer to @ref esl_key_lib_get_record_by_ble_address()
 *                      and @ref esl_key_lib_delete_record() for possible error
 *                      responses.
 * @note This function also returns SL_STATUS_OK also if the ble_address never
 *       existed in the database before the call.
 *****************************************************************************/
sl_status_t DLL_EXPORT esl_key_lib_delete_record_by_ble_address(const db_handle_p db_hnd,
                                                                const bd_addr *ble_address);

/**************************************************************************//**
 * Delete record by ESL address.
 *
 * @param[in] db_hnd Database handle.
 * @param[in] esl_address ESL address.
 *
 * @retval SL_STATUS_OK Deleting the record was successful. Otherwise please
 *                      refer to @ref esl_key_lib_get_record_by_esl_address()
 *                      and @ref esl_key_lib_delete_record() for possible error
 *                      responses.
 * @note This function also returns SL_STATUS_OK also if the ble_address never
 *       existed in the database before the call.
 *****************************************************************************/
sl_status_t DLL_EXPORT esl_key_lib_delete_record_by_esl_address(const db_handle_p db_hnd,
                                                                const esl_address_t esl_address);

/**************************************************************************//**
 * Get bind address by BLE address.
 *
 * @param[in] db_hnd Database handle.
 * @param[in] ble_address Reference to the ESL address which is searched by.
 * @param[out] bind_addr_out Bind address which found if any or NULL.
 *
 * @retval SL_STATUS_OK Deleting the record was successful.
 * @retval SL_STATUS_NOT_FOUND The record was not found.
 *****************************************************************************/
sl_status_t DLL_EXPORT esl_key_lib_get_bind_address_by_ble_address(const db_handle_p db_hnd,
                                                                   const bd_addr *ble_address,
                                                                   bd_addr *bind_addr_out);

/**************************************************************************//**
 * Get bind address by ESL address.
 *
 * @param[in] db_hnd Database handle.
 * @param[in] esl_address ESL address which is searched by.
 * @param[out] bind_addr_out Bind address which found if any or NULL.
 *
 * @retval SL_STATUS_OK Deleting the record was successful.
 * @retval SL_STATUS_NOT_FOUND The record was not found.
 *****************************************************************************/
sl_status_t DLL_EXPORT esl_key_lib_get_bind_address_by_esl_address(const db_handle_p db_hnd,
                                                                   const esl_address_t esl_address,
                                                                   bd_addr *bind_addr_out);
#ifdef __cplusplus
};
#endif

#endif // ESL_KEY_LIB_H
