/**************************************************************************//**
* @file
* @brief BT Mesh Key export functionality
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

// ----------------------------------------------------------------------------
// Includes

#include <stdio.h>
#include <stdbool.h>
#include "app_assert.h"
#include "app_log.h"
#include "sl_bt_api.h"
#include "sl_btmesh_api.h"

#include "sl_common.h"

// ----------------------------------------------------------------------------
// Macros

#define NET_KEY 0
#define APP_KEY 1

#define OLD_KEY 0
#define CURRENT_KEY 1

#define A16_AS_ARGS(A)              \
  (A)[0], (A)[1], (A)[2], (A)[3],   \
  (A)[4], (A)[5], (A)[6], (A)[7],   \
  (A)[8], (A)[9], (A)[10], (A)[11], \
  (A)[12], (A)[13], (A)[14], (A)[15]

// ----------------------------------------------------------------------------
// Type definitions

// This structure holds the exported data for the device keys
typedef struct {
  uuid_128 uuid;
  uint16_t address;
  aes_key_128 key;
} devkey_t;

// ----------------------------------------------------------------------------
// Static Variables

// This enum holds the state of the task
static enum {
  IDLE,
  START,
  GET_DEVICES,
  WRITE_FILE,
} state = IDLE;

// File name
static char *file_name = "BtMeshKeys.json";
// Index to track
static int ddb_index = 0;

// Array containing the device keys
static devkey_t *devkeys = NULL;
// length of the devkeys array
static uint16_t devkeys_count = 0;

// ----------------------------------------------------------------------------
// Function definitions

void btmesh_key_export_set_file_name(char* name)
{
  file_name = name;
}

void btmesh_key_export_start()
{
  state = START;
}

bool btmesh_key_export_is_idle()
{
  return state == IDLE;
}

void btmesh_key_export_task()
{
  sl_status_t sc;
  switch (state) {
    case START:
      sc = sl_btmesh_prov_list_ddb_entries(&devkeys_count);
      app_assert_status_f(sc, "Failed to list ddb entries");
      if (devkeys_count > 0) {
        devkeys = malloc(devkeys_count * sizeof(devkey_t));
        app_assert(devkeys != NULL, "Memory allocation failed");
        ddb_index = 0;
        state = GET_DEVICES;
      } else {
        state = WRITE_FILE;
      }
      break;
    case GET_DEVICES:
      //if devkeys array is filled -> WRITE_FILE;
      break;
    case WRITE_FILE: {
      FILE *fptr = fopen(file_name, "w");
      app_assert(fptr != NULL, "File open failed");
      uint32_t iv_index;
      uint8_t iv_update_state;
      sc = sl_btmesh_node_get_ivupdate_state(&iv_index, &iv_update_state);
      app_assert_status(sc);
      fprintf(fptr, "{\n");
      fprintf(fptr, "  \"ivIndex\": %d,\n", iv_index);

      fprintf(fptr, "  \"netKeys\": [\n");
      uint32_t netkey_count;
      sc = sl_btmesh_node_get_key_count(NET_KEY, &netkey_count);
      app_assert_status(sc);
      for (uint32_t i = 0; i < netkey_count; i++) {
        uint16_t id;
        uint16_t netkey_index;
        aes_key_128 key;
        sc = sl_btmesh_node_get_key(NET_KEY, i, CURRENT_KEY, &id, &netkey_index, &key);
        app_assert_status(sc);
        fprintf(fptr, "    {\n");
        fprintf(fptr, "      \"index\": \"%d\",\n", id);
        fprintf(fptr,
                "      \"value\": \"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\"\n",
                A16_AS_ARGS(key.data));
        if (i + 1 == netkey_count) {
          fprintf(fptr, "    }\n");
        } else {
          fprintf(fptr, "    },\n");
        }
      }
      fprintf(fptr, "  ],\n");

      fprintf(fptr, "  \"appKeys\": [\n");
      uint32_t appkey_count;
      sc = sl_btmesh_node_get_key_count(1, &appkey_count);
      app_assert_status(sc);
      for (uint32_t i = 0; i < appkey_count; i++) {
        uint16_t id;
        uint16_t netkey_index;
        aes_key_128 key;
        sc = sl_btmesh_node_get_key(APP_KEY, i, CURRENT_KEY, &id, &netkey_index, &key);
        app_assert_status(sc);
        fprintf(fptr, "    {\n");
        fprintf(fptr, "      \"boundNetKeyIndex\": \"%d\",\n", netkey_index);
        fprintf(fptr, "      \"index\": \"%d\",\n", id);
        fprintf(fptr,
                "      \"value\": \"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\"\n",
                A16_AS_ARGS(key.data));
        if (i + 1 == appkey_count) {
          fprintf(fptr, "    }\n");
        } else {
          fprintf(fptr, "    },\n");
        }
      }
      fprintf(fptr, "  ],\n");

      fprintf(fptr, "  \"devKeys\": [\n");
      for (uint32_t i = 0; i < devkeys_count; i++) {
        devkey_t devkey = devkeys[i];
        fprintf(fptr, "    {\n");
        fprintf(fptr, "      \"primaryAddress\": \"%d\",\n", devkey.address);
        fprintf(fptr,
                "      \"uuid\": \"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\",\n",
                A16_AS_ARGS(devkey.uuid.data));
        fprintf(fptr,
                "      \"value\": \"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\"\n",
                A16_AS_ARGS(devkey.key.data));
        if (i + 1 == devkeys_count) {
          fprintf(fptr, "    }\n");
        } else {
          fprintf(fptr, "    },\n");
        }
      }
      fprintf(fptr, "  ]\n");

      fprintf(fptr, "}\n");
      free(devkeys);
      fclose(fptr);
      state = IDLE;
      break;
    }
    case IDLE:
      //do nothing
      break;
    default:
      break;
  }
}

void btmesh_key_export_on_event(sl_btmesh_msg_t *evt)
{
  uint32_t evt_id = SL_BT_MSG_ID(evt->header);
  if (state == GET_DEVICES
      && evt_id == sl_btmesh_evt_prov_ddb_list_id) {
    uuid_128 uuid = evt->data.evt_prov_ddb_list.uuid;
    uint16_t address;
    aes_key_128 key;
    uint16_t netkey_index;
    uint8_t elements;
    sl_status_t sc = sl_btmesh_prov_get_ddb_entry(uuid, &key, &netkey_index, &address, &elements);
    app_assert_status(sc);
    devkeys[ddb_index] = (devkey_t){ uuid, address, key };

    ddb_index++;
    if (ddb_index == devkeys_count) {
      state = WRITE_FILE;
    }
  }
}
