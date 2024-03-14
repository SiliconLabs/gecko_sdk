/***************************************************************************//**
 * @file
 * @brief ESL key library implementation.
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

// -----------------------------------------------------------------------------
// Includes

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sqlite3.h"
#include "app_log.h"
#include "esl_key_lib.h"
#include "sl_bt_ead_core.h"

// Check SQLITE version
#if SQLITE_VERSION_NUMBER != 3041002
#warning Untested SQLITE version
#endif

// -----------------------------------------------------------------------------
// Macros and Typedefs

#define ESL_KEY_LIB_QUERY_FIRST_FIELD       1

#define ESL_KEY_LIB_BLE_ADDRESS_FIELD       1
#define ESL_KEY_LIB_AES_128_KEY_FIELD       2
#define ESL_KEY_LIB_EAD_KEY_MATERIAL_FIELD  3
#define ESL_KEY_LIB_ESL_ADDRESS_FIELD       4
#define ESL_KEY_LIB_BIND_ADDRESS_FIELD      5

#define ESL_KEY_LIB_BLE_ADDRESS_COLUMN_INDEX       (ESL_KEY_LIB_BLE_ADDRESS_FIELD - 1)
#define ESL_KEY_LIB_AES_128_KEY_COLUMN_INDEX       (ESL_KEY_LIB_AES_128_KEY_FIELD - 1)
#define ESL_KEY_LIB_EAD_KEY_MATERIAL_COLUMN_INDEX  (ESL_KEY_LIB_EAD_KEY_MATERIAL_FIELD - 1)
#define ESL_KEY_LIB_ESL_ADDRESS_COLUMN_INDEX       (ESL_KEY_LIB_ESL_ADDRESS_FIELD - 1)
#define ESL_KEY_LIB_BIND_ADDRESS_COLUMN_INDEX      (ESL_KEY_LIB_BIND_ADDRESS_FIELD - 1)

// Database handle structure
struct db_handle_s {
  bool       keep_it_open;
  const char *database_name;
  sqlite3    *sqlite_db_handle;
};

// Record structure
struct db_record_s {
  db_handle_p               hnd;
  esl_key_lib_record_type_t type;
  esl_address_t             *esl_address;
  esl_address_t             esl_address_data;
  bd_addr                   ble_address;
  union {
    aes_key_128             identity_key;   // only in AP record
    aes_key_128             long_term_key;  // only in Tag record
  };
  union {
    struct sl_bt_ead_key_material_s ap_key_material;       // only in AP record
    struct sl_bt_ead_key_material_s response_key_material; // only in Tag record
  };
};

// -----------------------------------------------------------------------------
// Static Function Declarations

/******************************************************************************
 * Try open the database if not yet opened
 * @retval Same as sqlite3_open() return value or SQLITE_MISUSE if hnd is
 *         NULL or SQLITE_OK if hnd->sqlite_db_handle is not NULL
 *****************************************************************************/
static int connect_db(db_handle_p hnd);

/******************************************************************************
 * Safe close the database with basic error handling included
 * @retval Same as sqlite3_close_v2() return value or SQLITE_MISUSE if hnd is
 *         NULL or SQLITE_DONE if hnd->sqlite_db_handle is NULL
 *****************************************************************************/
static int disconnect_db(db_handle_p hnd);

/******************************************************************************
 * Validate the given BLE address
 * 00:00:00:00:00:00 and FF:FF:FF:FF:FF:FF EUIs are prohibited by the IEEE
 * EUI-48 restriction.
 *
 * @retval SL_STATUS_OK if the address is a valid BLE address
 * @retval SL_STATUS_INVALID_PARAMETER if the address is an invalid BLE address
 *****************************************************************************/
static sl_status_t validate_ble_addr(const bd_addr *ble_address);

/******************************************************************************
 * Validate the given ESL address
 *
 * @retval SL_STATUS_OK if the address is a valid ESL address
 * @retval SL_STATUS_INVALID_PARAMETER if the address is an invalid ESL address
 *****************************************************************************/
static sl_status_t validate_esl_addr(const esl_address_t address);

/******************************************************************************
 * Store record (internal)
 *
 * @param[in] db_hnd Database handle.
 * @param[in] record_hnd Record handle.
 * @param[in] bind_addr AP BLE address to bind to (only Tag type).
 *
 * @retval SL_STATUS_OK Storing was successful.
 * @retval SL_STATUS_FAILED Failed storing the record.
 * @retval SL_STATUS_NULL_POINTER Any of the input parameters are NULL.
 * @retval SL_STATUS_OBJECT_WRITE SQLite step() is not SQLITE_OK. (Mostly due
 *                                to UNIQUE or FOREIGN_KEY constraints!)
 * @retval SL_STATUS_ABORT SQLite finalize() is not SQLITE_OK.
 * @retval SL_STATUS_INVALID_TYPE The given record type is an AP record.
 *****************************************************************************/
static sl_status_t internal_store_record(const db_handle_p hnd,
                                         const db_record_p ptr,
                                         const bd_addr *bind_addr);

// -----------------------------------------------------------------------------
// Static Variables
static const uint8_t address_length = sizeof(bd_addr);

static const char    empty_key[SL_BT_EAD_KEY_MATERIAL_SIZE] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

// -----------------------------------------------------------------------------
// Public Function Definitions

#ifdef WIN_DLL
#include "windows.h"
BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
  return TRUE;
}
#endif
// -------------------------------
// Database main interfaces
sl_status_t esl_key_lib_init_database(const char *db_id, db_handle_p *hnd_out)
{
  sl_status_t status = SL_STATUS_NULL_POINTER;

  if ((hnd_out != NULL) && (db_id != NULL)) {
    char       *db_id_cpy;
    char       *error;

    *hnd_out = (db_handle_p)malloc(sizeof(struct db_handle_s));

    if (*hnd_out == NULL) {
      status = SL_STATUS_ALLOCATION_FAILED;
    } else {
      status = SL_STATUS_OK;
      memset((*hnd_out), 0, sizeof(struct db_handle_s));
    }

    if (status == SL_STATUS_OK) {
      size_t db_id_len = strlen((char*)db_id) + 1; // include terminating NUL
      // Allocate memory on heap for DB ID string copy
      db_id_cpy        = malloc(db_id_len);

      if (db_id_cpy == NULL) {
        status = SL_STATUS_ALLOCATION_FAILED;
      } else {
        strcpy(db_id_cpy, (char*)db_id);
        // Store the copy address in our handle
        (*hnd_out)->database_name = db_id_cpy;
      }
    }

    if (status == SL_STATUS_OK) {
      int        rc;
      static const char *sql_create_ap = "CREATE TABLE IF NOT EXISTS "
                                         "ap_table(ap_ble_address varchar(6) NOT NULL "
                                         "PRIMARY KEY, identity_key varchar(16), "
                                         "ap_key_material varchar(24) NOT NULL);";

      static const char *sql_create_tag = "CREATE TABLE IF NOT EXISTS "
                                          "tag_table(tag_ble_address varchar(6) NOT NULL "
                                          "PRIMARY KEY, long_term_key varchar(16), "
                                          "response_key_material varchar(24), "
                                          "esl_address varchar(2),"
                                          "bind_address varchar(6), "
                                          "FOREIGN KEY (bind_address) "
                                          "REFERENCES ap_table(ap_ble_address),"
                                          "UNIQUE(esl_address) ON CONFLICT ABORT);";

      rc = connect_db(*hnd_out);

      if (rc != SQLITE_OK) {
        status = SL_STATUS_INITIALIZATION;
      } else {
        // Variable 'db' is just a short alias to write less...
        sqlite3    **db = &(*hnd_out)->sqlite_db_handle;

        rc = sqlite3_exec(*db, sql_create_ap, NULL, NULL, &error);

        if (rc == SQLITE_OK) {
          rc = sqlite3_exec(*db, sql_create_tag, NULL, NULL, &error);
        }

        if (rc != SQLITE_OK) {
          app_log_critical("Database creation failed to execute statement: %s" APP_LOG_NL, sqlite3_errmsg(*db));
          status = SL_STATUS_INITIALIZATION;
        }
      }
    }

    if (status != SL_STATUS_OK) {
      free(db_id_cpy);
      free(*hnd_out);
      *hnd_out = NULL;
    }

    (void)disconnect_db(*hnd_out); // close result is irrelevant here
  }

  return status;
}

sl_status_t esl_key_lib_deinit_database(db_handle_p hnd)
{
  sl_status_t status = SL_STATUS_NULL_POINTER;

  if (hnd != NULL) {
    int rc;

    hnd->keep_it_open = false; // force close on deinit!
    rc = disconnect_db(hnd);

    if (rc == SQLITE_OK || rc == SQLITE_DONE) {
      free((char*)(hnd->database_name));
      free(hnd);
      hnd = NULL;
      status = SL_STATUS_OK;
    } else if (rc == SQLITE_BUSY) {
      app_log_error("There are unfinished statements, the connection cannot be closed." APP_LOG_NL);
      status = SL_STATUS_BUSY;
    } else {
      status = SL_STATUS_FAIL;
    }
  }

  return status;
}

sl_status_t esl_key_lib_alloc_record(esl_key_lib_record_type_t type, db_record_p *record_hnd_out)
{
  sl_status_t status = SL_STATUS_INVALID_PARAMETER;

  if ((record_hnd_out != NULL) && ((type == ESL_KEY_LIB_AP_RECORD) || (type == ESL_KEY_LIB_TAG_RECORD))) {
    status = SL_STATUS_ALLOCATION_FAILED;
    *record_hnd_out = (db_record_p)malloc(sizeof(struct db_record_s));

    if (*record_hnd_out != NULL) {
      memset(*record_hnd_out, 0, sizeof(struct db_record_s));
      (*record_hnd_out)->type = type;
      status = SL_STATUS_OK;
    }
  }

  return status;
}

void esl_key_lib_free_record(db_record_p record_hnd)
{
  free(record_hnd); // Safe to call with NULL, no need to check record_hnd for it.
}

sl_status_t esl_key_lib_store_record(const db_handle_p db_hnd, const db_record_p record_hnd)
{
  return internal_store_record(db_hnd, record_hnd, NULL);
}

sl_status_t esl_key_lib_store_record_and_bind(const db_handle_p db_hnd, const db_record_p record_hnd, const bd_addr *ble_address)
{
  return internal_store_record(db_hnd, record_hnd, ble_address);
}

sl_status_t esl_key_lib_delete_record(const db_handle_p db_hnd, const db_record_p record_hnd)
{
  int rc;
  sqlite3_stmt *stmt;
  sl_status_t status = SL_STATUS_INITIALIZATION;

  const char *sql = "DELETE FROM ap_table WHERE ap_ble_address= ?;";
  sqlite3 **db = &(db_hnd->sqlite_db_handle);

  if ((db_hnd == NULL) || (record_hnd == NULL)) {
    return SL_STATUS_NULL_POINTER;
  } else if ((record_hnd->type != ESL_KEY_LIB_AP_RECORD) && (record_hnd->type != ESL_KEY_LIB_TAG_RECORD)) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  rc = connect_db(db_hnd);

  if (rc == SQLITE_OK) {
    rc = sqlite3_exec(*db, "PRAGMA foreign_keys = ON;", NULL, NULL, NULL);
  }

  if (rc == SQLITE_OK) {
    if (record_hnd->type == ESL_KEY_LIB_TAG_RECORD) {
      sql = "DELETE FROM tag_table WHERE tag_ble_address= ?;";
    }

    rc = sqlite3_prepare_v2(*db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
      app_log_error("Failed to execute prepare: %s" APP_LOG_NL, sqlite3_errmsg(*db));
    } else {
      bd_addr *ble_address = &(record_hnd->ble_address);

      sqlite3_bind_blob(stmt, ESL_KEY_LIB_QUERY_FIRST_FIELD, ble_address, address_length, SQLITE_TRANSIENT);
      rc = sqlite3_step(stmt);
      if (rc != SQLITE_DONE) {
        app_log_error("Failed to execute step: %s" APP_LOG_NL, sqlite3_errmsg(*db));
        status = SL_STATUS_OBJECT_WRITE;

        if (rc == SQLITE_BUSY) {
          app_log_error("Sqlite is busy: %d" APP_LOG_NL, rc);
        }
      }

      rc = sqlite3_finalize(stmt);
      if (rc != SQLITE_OK) {
        app_log_error("Failed to execute finalize: %s" APP_LOG_NL, sqlite3_errmsg(*db));
        status = SL_STATUS_ABORT;
      } else {
        status = SL_STATUS_OK;
      }
    }

    (void)disconnect_db(db_hnd);
  }

  return status;
}

sl_status_t esl_key_lib_clear_database(const db_handle_p hnd)
{
  sl_status_t status = SL_STATUS_NULL_POINTER;

  if (hnd != NULL) {
    char* error;
    int rc;
    sqlite3 **db = &(hnd->sqlite_db_handle);

    status = SL_STATUS_FAIL;
    rc = connect_db(hnd);

    if (rc == SQLITE_OK) {
      // Delete tables
      rc = sqlite3_exec(*db, "DELETE FROM ap_table;", NULL, NULL, &error);

      if (rc == SQLITE_OK) {
        rc = sqlite3_exec(*db, "DELETE FROM tag_table;", NULL, NULL, &error);
      }

      (void)disconnect_db(hnd);
    }

    if (rc != SQLITE_OK) {
      app_log_error("Failed to execute statement: %s" APP_LOG_NL, sqlite3_errmsg(*db));
    } else {
      status = SL_STATUS_OK;
    }
  }

  return status;
}

sl_status_t esl_key_lib_get_record_by_ble_address(const db_handle_p db_hnd, const bd_addr *ble_address, db_record_p *record_hnd_out)
{
  sqlite3_stmt *stmt = NULL;
  sqlite3      **db;
  int          rc;
  sl_status_t  status = SL_STATUS_NULL_POINTER;

  if (db_hnd != NULL && ble_address != NULL && record_hnd_out != NULL) {
    *record_hnd_out = NULL;
    status = esl_key_lib_alloc_record(ESL_KEY_LIB_TAG_RECORD, record_hnd_out);
  }

  if (status == SL_STATUS_OK) {
    db = &(db_hnd->sqlite_db_handle); // short alias
    rc = connect_db(db_hnd);

    if (rc != SQLITE_OK) {
      status = SL_STATUS_FAIL;
    } else {
      // Searching in the ap table
      rc = sqlite3_prepare_v2(*db, "SELECT * FROM ap_table WHERE ap_ble_address = ?;", -1, &stmt, NULL);

      if (rc != SQLITE_OK) {
        app_log_error("Failed to execute prepare: %s" APP_LOG_NL, sqlite3_errmsg(*db));
        status = SL_STATUS_INITIALIZATION;
      } else {
        sqlite3_bind_blob(stmt, ESL_KEY_LIB_BLE_ADDRESS_FIELD, ble_address, address_length, SQLITE_TRANSIENT);
      }
    }
  }

  if (status == SL_STATUS_OK) {
    rc = sqlite3_step(stmt);

    if ((rc == SQLITE_ROW) && sqlite3_column_bytes(stmt, ESL_KEY_LIB_BLE_ADDRESS_COLUMN_INDEX)) { // row found in ap table
      (*record_hnd_out)->type = ESL_KEY_LIB_AP_RECORD;
      memcpy(&((*record_hnd_out)->ble_address), sqlite3_column_blob(stmt, ESL_KEY_LIB_BLE_ADDRESS_COLUMN_INDEX), sqlite3_column_bytes(stmt, ESL_KEY_LIB_BLE_ADDRESS_COLUMN_INDEX));
      memcpy(&((*record_hnd_out)->identity_key), sqlite3_column_blob(stmt, ESL_KEY_LIB_AES_128_KEY_COLUMN_INDEX), sqlite3_column_bytes(stmt, ESL_KEY_LIB_AES_128_KEY_COLUMN_INDEX));
      memcpy(&((*record_hnd_out)->ap_key_material), sqlite3_column_blob(stmt, ESL_KEY_LIB_EAD_KEY_MATERIAL_COLUMN_INDEX), sqlite3_column_bytes(stmt, ESL_KEY_LIB_EAD_KEY_MATERIAL_COLUMN_INDEX));
    } else {
      // Destroy the previous statement, searching in the tag table instead
      sqlite3_finalize(stmt);
      stmt = NULL;
      rc = sqlite3_prepare_v2(*db, "SELECT * FROM tag_table WHERE tag_ble_address = ?;", -1, &stmt, NULL);

      if (rc != SQLITE_OK) {
        app_log_error("Failed to execute prepare: %s" APP_LOG_NL, sqlite3_errmsg(*db));
        status = SL_STATUS_INITIALIZATION;
      } else {
        sqlite3_bind_blob(stmt, ESL_KEY_LIB_BLE_ADDRESS_FIELD, ble_address, address_length, SQLITE_TRANSIENT);
        rc = sqlite3_step(stmt);

        if ((rc == SQLITE_ROW) && sqlite3_column_bytes(stmt, ESL_KEY_LIB_BLE_ADDRESS_COLUMN_INDEX)) {
          (*record_hnd_out)->type = ESL_KEY_LIB_TAG_RECORD;
          memcpy(&((*record_hnd_out)->ble_address), sqlite3_column_blob(stmt, ESL_KEY_LIB_BLE_ADDRESS_COLUMN_INDEX), sqlite3_column_bytes(stmt, ESL_KEY_LIB_BLE_ADDRESS_COLUMN_INDEX));
          memcpy(&((*record_hnd_out)->long_term_key), sqlite3_column_blob(stmt, ESL_KEY_LIB_AES_128_KEY_COLUMN_INDEX), sqlite3_column_bytes(stmt, ESL_KEY_LIB_AES_128_KEY_COLUMN_INDEX));
          memcpy(&((*record_hnd_out)->response_key_material), sqlite3_column_blob(stmt, ESL_KEY_LIB_EAD_KEY_MATERIAL_COLUMN_INDEX), sqlite3_column_bytes(stmt, ESL_KEY_LIB_EAD_KEY_MATERIAL_COLUMN_INDEX));
          if ((*record_hnd_out)->esl_address != NULL) {
            memcpy((*record_hnd_out)->esl_address, sqlite3_column_blob(stmt, ESL_KEY_LIB_ESL_ADDRESS_COLUMN_INDEX), sqlite3_column_bytes(stmt, ESL_KEY_LIB_ESL_ADDRESS_COLUMN_INDEX));
          }
        } else {
          status = SL_STATUS_NOT_FOUND;
        }
      }
    }

    if (stmt != NULL) {
      rc = sqlite3_finalize(stmt);

      if (rc != SQLITE_OK) {
        status = SL_STATUS_INITIALIZATION;
      }
    }

    if (status != SL_STATUS_FAIL) {
      (void)disconnect_db(db_hnd);
    }
  }

  if (status != SL_STATUS_OK) {
    // try to release the allocated handle on any error, ignore result at this point
    (void)esl_key_lib_free_record(*record_hnd_out);
    *record_hnd_out = NULL;
  }

  return status;
}

sl_status_t esl_key_lib_get_record_by_esl_address(const db_handle_p db_hnd, const esl_address_t esl_address, db_record_p *record_hnd_out)
{
  sqlite3_stmt *stmt = NULL;
  sqlite3      **db;
  int          rc;
  sl_status_t  status = SL_STATUS_NULL_POINTER;

  if (db_hnd != NULL && record_hnd_out != NULL) {
    *record_hnd_out = NULL;
    status = validate_esl_addr(esl_address);

    if (status == SL_STATUS_OK) {
      status = esl_key_lib_alloc_record(ESL_KEY_LIB_TAG_RECORD, record_hnd_out);
    }
  }

  if (status == SL_STATUS_OK) {
    db = &(db_hnd->sqlite_db_handle); // short alias
    rc = connect_db(db_hnd);

    if (rc != SQLITE_OK) {
      status = SL_STATUS_FAIL;
    } else {
      // Searching in the ap table
      rc = sqlite3_prepare_v2(*db, "SELECT * FROM tag_table WHERE esl_address = ?;", -1, &stmt, NULL);

      if (rc != SQLITE_OK) {
        app_log_error("Failed to execute prepare: %s" APP_LOG_NL, sqlite3_errmsg(*db));
        status = SL_STATUS_INITIALIZATION;
      } else {
        sqlite3_bind_blob(stmt, ESL_KEY_LIB_QUERY_FIRST_FIELD, &esl_address, sizeof(esl_address), SQLITE_TRANSIENT);
      }
    }
  }

  if (status == SL_STATUS_OK) {
    rc = sqlite3_step(stmt);

    if ((rc == SQLITE_ROW) && sqlite3_column_bytes(stmt, ESL_KEY_LIB_BLE_ADDRESS_COLUMN_INDEX)) {
      (*record_hnd_out)->type = ESL_KEY_LIB_TAG_RECORD;
      memcpy(&((*record_hnd_out)->ble_address), sqlite3_column_blob(stmt, ESL_KEY_LIB_BLE_ADDRESS_COLUMN_INDEX), sqlite3_column_bytes(stmt, ESL_KEY_LIB_BLE_ADDRESS_COLUMN_INDEX));
      memcpy(&((*record_hnd_out)->long_term_key), sqlite3_column_blob(stmt, ESL_KEY_LIB_AES_128_KEY_COLUMN_INDEX), sqlite3_column_bytes(stmt, ESL_KEY_LIB_AES_128_KEY_COLUMN_INDEX));
      memcpy(&((*record_hnd_out)->response_key_material), sqlite3_column_blob(stmt, ESL_KEY_LIB_EAD_KEY_MATERIAL_COLUMN_INDEX), sqlite3_column_bytes(stmt, ESL_KEY_LIB_EAD_KEY_MATERIAL_COLUMN_INDEX));
      memcpy(&((*record_hnd_out)->esl_address_data), sqlite3_column_blob(stmt, ESL_KEY_LIB_ESL_ADDRESS_COLUMN_INDEX), sqlite3_column_bytes(stmt, ESL_KEY_LIB_ESL_ADDRESS_COLUMN_INDEX));
      (*record_hnd_out)->esl_address = &((*record_hnd_out)->esl_address_data);
    } else {
      status = SL_STATUS_NOT_FOUND;
    }

    if (stmt != NULL) {
      rc = sqlite3_finalize(stmt);

      if (rc != SQLITE_OK) {
        status = SL_STATUS_INITIALIZATION;
      }
    }

    if (status != SL_STATUS_FAIL) {
      (void)disconnect_db(db_hnd);
    }
  }

  if (status != SL_STATUS_OK) {
    // try to release the allocated handle on any error, ignore result at this point
    (void)esl_key_lib_free_record(*record_hnd_out);
    *record_hnd_out = NULL;
  }

  return status;
}

// -------------------------------
// Setter interfaces for record data

sl_status_t esl_key_lib_set_ble_address(const bd_addr *addr, db_record_p record_hnd)
{
  sl_status_t status = SL_STATUS_NULL_POINTER;
  if ((addr != NULL) || (record_hnd != NULL)) {
    status = validate_ble_addr(addr);

    if (status == SL_STATUS_OK) {
      memcpy(&(record_hnd->ble_address), addr, address_length);
    }
  }
  return status;
}

sl_status_t esl_key_lib_set_esl_address(const esl_address_t esl_address, db_record_p record_hnd)
{
  sl_status_t status = SL_STATUS_NULL_POINTER;

  if (record_hnd != NULL) {
    status = validate_esl_addr(esl_address);

    if (status == SL_STATUS_OK) {
      memcpy(&((record_hnd)->esl_address_data), &esl_address, sizeof(esl_address_t));
      record_hnd->esl_address = &(record_hnd->esl_address_data);
    }
  }

  return status;
}

sl_status_t esl_key_lib_set_long_term_key(const aes_key_128 *ltk_key, db_record_p record_hnd)
{
  if ((ltk_key != NULL) && (record_hnd != NULL)) {
    if (record_hnd->type == ESL_KEY_LIB_AP_RECORD) {
      return SL_STATUS_INVALID_TYPE;
    } else {
      memcpy(&((record_hnd)->long_term_key), ltk_key, sizeof(aes_key_128));
      return SL_STATUS_OK;
    }
  }

  return SL_STATUS_NULL_POINTER;
}

sl_status_t esl_key_lib_set_identity_key(const aes_key_128 *id_key, db_record_p record_hnd)
{
  if ((id_key != NULL) && (record_hnd != NULL)) {
    if (record_hnd->type == ESL_KEY_LIB_TAG_RECORD) {
      return SL_STATUS_INVALID_TYPE;
    } else {
      memcpy(&((record_hnd)->identity_key), id_key, sizeof(aes_key_128));
      return SL_STATUS_OK;
    }
  }

  return SL_STATUS_NULL_POINTER;
}

sl_status_t esl_key_lib_set_ap_key_material(const sl_bt_ead_key_material_p ap_key, db_record_p record_hnd)
{
  if ((ap_key != NULL) && (record_hnd != NULL)) {
    if (record_hnd->type == ESL_KEY_LIB_TAG_RECORD) {
      return SL_STATUS_INVALID_TYPE;
    } else {
      memcpy(&((record_hnd)->ap_key_material), ap_key, SL_BT_EAD_KEY_MATERIAL_SIZE);
      return SL_STATUS_OK;
    }
  }

  return SL_STATUS_NULL_POINTER;
}

sl_status_t esl_key_lib_set_response_key_material(const sl_bt_ead_key_material_p response_key, db_record_p record_hnd)
{
  if ((response_key != NULL) && (record_hnd != NULL)) {
    if (record_hnd->type == ESL_KEY_LIB_AP_RECORD) {
      return SL_STATUS_INVALID_TYPE;
    } else {
      memcpy(&((record_hnd)->response_key_material), response_key, SL_BT_EAD_KEY_MATERIAL_SIZE);
      return SL_STATUS_OK;
    }
  }

  return SL_STATUS_NULL_POINTER;
}

// -------------------------------
// Getter interfaces for record data

sl_status_t esl_key_lib_get_record_type(const db_record_p record_hnd, esl_key_lib_record_type_t *type_out)
{
  sl_status_t status = SL_STATUS_NULL_POINTER;

  if (record_hnd != NULL && type_out != NULL) {
    memcpy(type_out, &(record_hnd->type), sizeof(esl_key_lib_record_type_t));
    status = SL_STATUS_OK;
  }

  return status;
}

sl_status_t esl_key_lib_get_ble_address(const db_record_p record_hnd, bd_addr *addr_out)
{
  sl_status_t status = SL_STATUS_NULL_POINTER;

  if (record_hnd != NULL && addr_out != NULL) {
    memcpy(addr_out, &(record_hnd->ble_address), address_length);
    status = SL_STATUS_OK;
  }

  return status;
}

sl_status_t esl_key_lib_get_esl_address(const db_record_p record_hnd, esl_address_t *addr_out)
{
  sl_status_t status = SL_STATUS_NULL_POINTER;

  if (record_hnd != NULL && addr_out != NULL) {
    if (record_hnd->type == ESL_KEY_LIB_TAG_RECORD) {
      if (record_hnd->esl_address != NULL) {
        *addr_out = *record_hnd->esl_address;
        status = SL_STATUS_OK;
      } else {
        status = SL_STATUS_NOT_INITIALIZED;
      }
    } else {
      status = SL_STATUS_INVALID_TYPE;
    }
  }

  return status;
}

sl_status_t esl_key_lib_get_bind_address(const db_handle_p db_hnd, const db_record_p record_hnd, bd_addr *addr_out)
{
  static const char *sql_select = "SELECT bind_address FROM tag_table WHERE tag_ble_address = ?";
  int          rc;
  sl_status_t  status           = SL_STATUS_INITIALIZATION;
  sqlite3      **db             = &(db_hnd->sqlite_db_handle);
  sqlite3_stmt *stmt;

  if (db_hnd == NULL || record_hnd == NULL || addr_out == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  if (record_hnd->type != ESL_KEY_LIB_TAG_RECORD) {
    return SL_STATUS_INVALID_TYPE;
  }

  rc = connect_db(db_hnd);

  if (rc == SQLITE_OK) {
    rc = sqlite3_prepare_v2(*db, sql_select, -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
      app_log_error("Failed to execute prepare: %s" APP_LOG_NL, sqlite3_errmsg(*db));
    } else {
      // Check if addr is in tag_table
      sqlite3_bind_blob(stmt, ESL_KEY_LIB_BLE_ADDRESS_FIELD, &(record_hnd->ble_address), address_length, SQLITE_TRANSIENT);
      rc = sqlite3_step(stmt);

      if ((rc == SQLITE_ROW) && sqlite3_column_bytes(stmt, ESL_KEY_LIB_BLE_ADDRESS_COLUMN_INDEX)) {
        // Found ble address in tag table, reading bind address
        memcpy(addr_out, sqlite3_column_blob(stmt, ESL_KEY_LIB_BIND_ADDRESS_COLUMN_INDEX), sqlite3_column_bytes(stmt, ESL_KEY_LIB_BIND_ADDRESS_COLUMN_INDEX));
        status = SL_STATUS_OK;
      } else {
        status = SL_STATUS_NOT_FOUND;
      }

      // finalize & close, ignore results
      (void)sqlite3_finalize(stmt);
      (void)disconnect_db(db_hnd);
    }
  }

  return status;
}

sl_status_t esl_key_lib_get_long_term_key(const db_record_p record_hnd, aes_key_128 *ltk_key_out)
{
  sl_status_t status = SL_STATUS_NULL_POINTER;

  if (record_hnd != NULL && ltk_key_out != NULL) {
    if (record_hnd->type == ESL_KEY_LIB_TAG_RECORD) {
      const size_t key_size = sizeof(aes_key_128);

      if (!memcmp(empty_key, &(record_hnd->long_term_key), key_size)) {
        status = SL_STATUS_NOT_INITIALIZED;
      } else {
        memcpy(ltk_key_out, &(record_hnd->long_term_key), key_size);
        status = SL_STATUS_OK;
      }
    } else {
      status = SL_STATUS_INVALID_TYPE;
    }
  }

  return status;
}

sl_status_t esl_key_lib_get_identity_key(const db_record_p record_hnd, aes_key_128 *id_key_out)
{
  sl_status_t status = SL_STATUS_NULL_POINTER;

  if (record_hnd != NULL && id_key_out != NULL) {
    if (record_hnd->type == ESL_KEY_LIB_AP_RECORD) {
      const size_t key_size = sizeof(aes_key_128);

      if (!memcmp(empty_key, &(record_hnd->identity_key), key_size)) {
        status = SL_STATUS_NOT_INITIALIZED;
      } else {
        memcpy(id_key_out, &(record_hnd->identity_key), key_size);
        status = SL_STATUS_OK;
      }
    } else {
      status = SL_STATUS_INVALID_TYPE;
    }
  }

  return status;
}

sl_status_t esl_key_lib_get_ap_key_material(const db_record_p record_hnd, sl_bt_ead_key_material_p ap_key_out)
{
  sl_status_t status = SL_STATUS_NULL_POINTER;

  if (record_hnd != NULL && ap_key_out != NULL) {
    if (record_hnd->type == ESL_KEY_LIB_AP_RECORD) {
      const size_t key_size = sizeof(empty_key);

      if (!memcmp(empty_key, &(record_hnd->ap_key_material), key_size)) {
        status = SL_STATUS_NOT_INITIALIZED;
      } else {
        memcpy(ap_key_out, &(record_hnd->ap_key_material), SL_BT_EAD_KEY_MATERIAL_SIZE);
        status = SL_STATUS_OK;
      }
    } else {
      status = SL_STATUS_INVALID_TYPE;
    }
  }

  return status;
}

sl_status_t esl_key_lib_get_response_key_material(const db_record_p record_hnd, sl_bt_ead_key_material_p response_key_out)
{
  sl_status_t status = SL_STATUS_NULL_POINTER;

  if (record_hnd != NULL && response_key_out != NULL) {
    if (record_hnd->type == ESL_KEY_LIB_TAG_RECORD) {
      const size_t key_size = sizeof(empty_key);

      if (!memcmp(empty_key, &(record_hnd->response_key_material), key_size)) {
        status = SL_STATUS_NOT_INITIALIZED;
      } else {
        memcpy(response_key_out, &(record_hnd->response_key_material), key_size);
        status = SL_STATUS_OK;
      }
    } else {
      status = SL_STATUS_INVALID_TYPE;
    }
  }

  return status;
}

// -------------------------------
// Wrappers

sl_status_t esl_key_lib_delete_record_by_ble_address(const db_handle_p db_hnd, const bd_addr *ble_address)
{
  sl_status_t status;
  db_record_p record;

  db_hnd->keep_it_open = true;
  status = esl_key_lib_get_record_by_ble_address(db_hnd, ble_address, &record);

  if (status == SL_STATUS_OK) {
    status = esl_key_lib_delete_record(db_hnd, record);
    esl_key_lib_free_record(record);
  } else if (status == SL_STATUS_NOT_FOUND) {
    status = SL_STATUS_OK; // trying to delete a non-existent address shall be OK (idempotent delete)
  }

  db_hnd->keep_it_open = false;
  disconnect_db(db_hnd);

  return status;
}

sl_status_t esl_key_lib_delete_record_by_esl_address(const db_handle_p db_hnd, const esl_address_t esl_address)
{
  sl_status_t status;
  db_record_p record;

  db_hnd->keep_it_open = true;
  status = esl_key_lib_get_record_by_esl_address(db_hnd, esl_address, &record);

  if (status == SL_STATUS_OK) {
    status = esl_key_lib_delete_record(db_hnd, record);
    esl_key_lib_free_record(record);
  } else if (status == SL_STATUS_NOT_FOUND) {
    status = SL_STATUS_OK; // trying to delete a non-existent address shall be OK (idempotent delete)
  }

  db_hnd->keep_it_open = false;
  disconnect_db(db_hnd);

  return status;
}

sl_status_t esl_key_lib_get_bind_address_by_ble_address(const db_handle_p db_hnd, const bd_addr *ble_address, bd_addr *bind_addr_out)
{
  sl_status_t status;
  db_record_p record;

  db_hnd->keep_it_open = true;
  status = esl_key_lib_get_record_by_ble_address(db_hnd, ble_address, &record);

  if (status == SL_STATUS_OK) {
    status = esl_key_lib_get_bind_address(db_hnd, record, bind_addr_out);
    esl_key_lib_free_record(record);
  }

  db_hnd->keep_it_open = false;
  disconnect_db(db_hnd);

  return status;
}

sl_status_t esl_key_lib_get_bind_address_by_esl_address(const db_handle_p db_hnd, const esl_address_t esl_address, bd_addr *bind_addr_out)
{
  sl_status_t status;
  db_record_p record;

  db_hnd->keep_it_open = true;
  status = esl_key_lib_get_record_by_esl_address(db_hnd, esl_address, &record);

  if (status == SL_STATUS_OK) {
    status = esl_key_lib_get_bind_address(db_hnd, record, bind_addr_out);
    esl_key_lib_free_record(record);
  }

  db_hnd->keep_it_open = false;
  disconnect_db(db_hnd);

  return status;
}

// -----------------------------------------------------------------------------
// Static Function Definitions

// Try open the database if not yet opened
static int connect_db(db_handle_p hnd)
{
  int rc = SQLITE_MISUSE; // this is a custom, yet sqlite3 compatible error code

  if (hnd != NULL) {
    sqlite3 **db = &(hnd->sqlite_db_handle);

    if (hnd->sqlite_db_handle != NULL) {
      return SQLITE_OK;
    }

    rc = sqlite3_open(hnd->database_name, db);

    if (rc != SQLITE_OK) {
      app_log_critical("Failed to open database: %s" APP_LOG_NL, sqlite3_errmsg(*db));
    }
  }

  return rc;
}

// Safe close the database with basic error handling included
static int disconnect_db(db_handle_p hnd)
{
  int rc = SQLITE_MISUSE; // this is a custom, yet sqlite3 compatible error code

  if (hnd != NULL) {
    if (hnd->sqlite_db_handle == NULL || hnd->keep_it_open) {
      return SQLITE_DONE;
    }

    rc = sqlite3_close_v2(hnd->sqlite_db_handle);

    if (rc == SQLITE_OK) {
      hnd->sqlite_db_handle = NULL;
    } else if (rc == SQLITE_BUSY) {
      app_log_error("There are unfinished statements, the connection cannot be closed!" APP_LOG_NL);
    } else {
      app_log_critical("Failed to execute close: %s" APP_LOG_NL, sqlite3_errmsg(hnd->sqlite_db_handle));
    }
  } else {
    app_log_warning("Invalid call: disconnect_db(NULL)!" APP_LOG_NL);
  }

  return rc;
}

// Validate the given BLE address
static sl_status_t validate_ble_addr(const bd_addr *ble_address)
{
  sl_status_t status = SL_STATUS_INVALID_PARAMETER;
  uint8_t invalid_address[address_length];

  memset(invalid_address, 0, address_length); // all zeroes is invalid

  if (!!memcmp(invalid_address, ble_address->addr, address_length)) {
    memset(invalid_address, 0xFF, address_length); // all 0xff is reserved

    if (!!memcmp(invalid_address, ble_address->addr, address_length)) {
      status = SL_STATUS_OK;
    } else {
      app_log_error("Invalid BLE address (IEEE EUI-48 reserved)." APP_LOG_NL);
    }
  } else {
    app_log_error("Invalid BLE address (null)." APP_LOG_NL);
  }
  return status;
}

// Validate the given ESL address
static sl_status_t validate_esl_addr(const esl_address_t address)
{
  // ESL address is ESL ID + Group ID
  // The ESL address lower 8 bits with mask (ESL_Address & 0xff) should be between 0x00 és 0xFE (cannot be 0xFF)
  // The MSB lower 7 bits is group ID, where the RFU (ESL_Address & 0x8000) should be 0
  if (((address & ESL_ID_MASK) == ESL_BROADCAST_ID)
      || ((address & (esl_address_t)(~(ESL_ID_MASK | ESL_GROUP_ID_MASK))) != 0)) {
    return SL_STATUS_INVALID_PARAMETER;
  } else {
    return SL_STATUS_OK;
  }
}

// Store record (internal)
static sl_status_t internal_store_record(const db_handle_p db_hnd,
                                         const db_record_p record_hnd,
                                         const bd_addr *bind_addr)
{
  int rc;
  sqlite3_stmt       *stmt;
  sqlite3            **db = &(db_hnd->sqlite_db_handle); // short alias
  const bd_addr      *ble_address  = &(record_hnd->ble_address);
  const aes_key_128  *identity_key = &(record_hnd->identity_key);
  const sl_bt_ead_key_material_p key_material = &(record_hnd->ap_key_material);
  sl_status_t status;

  const char *sql_select = "SELECT * FROM tag_table WHERE tag_ble_address= ?;"; // always check "the other" table if the address already exists: it's a usage error!
  const char *sql_insert = "INSERT OR REPLACE INTO ap_table (ap_ble_address, identity_key, ap_key_material) VALUES (?,?,?);";

  // Parameter guards, immediate return on fail
  if ((db_hnd == NULL) || (record_hnd == NULL)) {
    return SL_STATUS_NULL_POINTER;
  } else if ((record_hnd->type != ESL_KEY_LIB_AP_RECORD) && (record_hnd->type != ESL_KEY_LIB_TAG_RECORD)) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  status = validate_ble_addr(ble_address);

  if (status != SL_STATUS_OK) {
    // return immediately if the ble_address is invalid
    return status;
  }

  if (record_hnd->type == ESL_KEY_LIB_TAG_RECORD) {
    sql_select = "SELECT * FROM ap_table WHERE ap_ble_address= ?;"; // please note: we're going to search in the other type of table

    if (bind_addr != NULL) {
      status = validate_ble_addr(bind_addr);

      // do UPSERT on tag_ble_address conflict, while this will abort on esl_address conflict as it has to be UNIQUE (so does the BLE address as well, but in that case we consider it an update)
      if (status == SL_STATUS_OK) {
        // these expressions are called: "UPSERT"s. UPSERT as such isn't standard SQL but SQLite has support since 3.24.0
        sql_insert = "INSERT INTO tag_table (tag_ble_address, long_term_key, response_key_material, esl_address, bind_address) VALUES (?,?,?,?,?) ON CONFLICT(tag_ble_address) DO UPDATE SET tag_ble_address=excluded.tag_ble_address, long_term_key=excluded.long_term_key, response_key_material=excluded.response_key_material, esl_address=excluded.esl_address, bind_address=excluded.bind_address;";
      } else {
        // still safe to return immediately on error (since there's no sqlite operation yet)
        return status;
      }
    } else {
      sql_insert = "INSERT INTO tag_table (tag_ble_address, long_term_key, response_key_material, esl_address) VALUES (?,?,?,?) ON CONFLICT(tag_ble_address) DO UPDATE SET tag_ble_address=excluded.tag_ble_address, long_term_key=excluded.long_term_key, response_key_material=excluded.response_key_material, esl_address=excluded.esl_address;";
    }
  }

  rc = connect_db(db_hnd);

  if (rc == SQLITE_OK) {
    rc = sqlite3_exec(*db, "PRAGMA foreign_keys = ON;", NULL, NULL, NULL);
  }

  if (rc == SQLITE_OK) {
    rc = sqlite3_prepare_v2(*db, sql_select, -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
      app_log_critical("Failed to execute prepare: %s" APP_LOG_NL, sqlite3_errmsg(*db));
      status = SL_STATUS_INITIALIZATION;
    } else {
      sqlite3_bind_blob(stmt, ESL_KEY_LIB_BLE_ADDRESS_FIELD, ble_address, address_length, SQLITE_TRANSIENT);
    }

    if (status == SL_STATUS_OK) {
      rc = sqlite3_step(stmt);

      if ((rc == SQLITE_ROW) && sqlite3_column_bytes(stmt, ESL_KEY_LIB_BLE_ADDRESS_COLUMN_INDEX)) { // row already exists, usage error!
        status = SL_STATUS_INVALID_TYPE;
      } else if (rc != SQLITE_DONE) { // something went wrong with sql engine
        app_log_error("Failed to execute step: %s" APP_LOG_NL, sqlite3_errmsg(*db));
        status = SL_STATUS_FAIL;
      }
    }

    if (stmt != NULL) {
      (void)sqlite3_finalize(stmt);
      stmt = NULL;
    }

    if (status == SL_STATUS_OK) {
      // BLE address is not in the other table, we can put the new record in
      rc = sqlite3_prepare_v2(*db, sql_insert, -1, &stmt, NULL);

      if (rc != SQLITE_OK) {
        app_log_error("Failed to execute prepare: %s" APP_LOG_NL, sqlite3_errmsg(*db));
        status = SL_STATUS_OBJECT_WRITE;
      }
    }

    if (status == SL_STATUS_OK) {
      sqlite3_bind_blob(stmt, ESL_KEY_LIB_BLE_ADDRESS_FIELD, ble_address, address_length, SQLITE_TRANSIENT);
      sqlite3_bind_blob(stmt, ESL_KEY_LIB_AES_128_KEY_FIELD, identity_key, sizeof(aes_key_128), SQLITE_TRANSIENT);
      sqlite3_bind_blob(stmt, ESL_KEY_LIB_EAD_KEY_MATERIAL_FIELD, key_material, SL_BT_EAD_KEY_MATERIAL_SIZE, SQLITE_TRANSIENT);

      if (record_hnd->type == ESL_KEY_LIB_TAG_RECORD) {
        sqlite3_bind_blob(stmt, ESL_KEY_LIB_ESL_ADDRESS_FIELD, record_hnd->esl_address, sizeof(esl_address_t), SQLITE_TRANSIENT);
        sqlite3_bind_blob(stmt, ESL_KEY_LIB_BIND_ADDRESS_FIELD, bind_addr, address_length, SQLITE_TRANSIENT);
      }

      rc = sqlite3_step(stmt);

      if (rc != SQLITE_DONE) {
        app_log_error("Failed to execute step: %s, %d" APP_LOG_NL, sqlite3_errmsg(*db), rc);
        status = SL_STATUS_OBJECT_WRITE;
      }

      rc = sqlite3_finalize(stmt);
      if (rc != SQLITE_OK) {
        app_log_error("Failed to execute finalize: %s" APP_LOG_NL, sqlite3_errmsg(*db));
        status = SL_STATUS_ABORT;
      }
    }

    (void)disconnect_db(db_hnd);
  } else {
    status = SL_STATUS_INITIALIZATION;
  }

  return status;
}
