/***************************************************************************/ /**
 * @file
 * @brief BT Mesh Remote Provisioner Component
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

// -----------------------------------------------------------------------------
// Includes

#include <stdlib.h>
#include "app_assert.h"
#include "app_log.h"
#include "sl_common.h"
#include "sl_slist.h"
#include "btmesh_prov.h"
#include "btmesh_remote_prov.h"
#include "btmesh_db.h"
#include "app_timer.h"

// -----------------------------------------------------------------------------
// Macros

/// Indication that remote provisioning server is available
#define REMOTE_PROV_SERVER_AVAILABLE            1
/// Maximum number of UUIDs that can be reported during scanning
#define REMOTE_SCAN_ITEM_LIMIT                  10
/// Perform multiple remote target scan
#define MULTIPLE_TARGET_SCAN                    0
/// Link open type to disable NPPI procedure
#define REMOTE_PROV_NPPI_DISABLE                (uint8_t)0xFF
/// Link open timeout in seconds
#define LINK_OPEN_TIMEOUT                       (uint8_t)10
/// Retry number of server scan capabilies
#define SCAN_CAPABILITIES_RETRY                 (uint8_t)0
/// Server scan capabilities timeout in miliseconds
#define SCAN_CAPABILITIES_TIMEOUT               (uint32_t)1000
/// Element index which contains the remote provisioning client model on host provisioner
#define REMOTE_PROV_CLIENT_ELEMENT_INDEX        0

// -----------------------------------------------------------------------------
// Type definitions

/// Internal structure for remote provisioning server parameters storage
struct remote_provisioning_server_s{
  uint16_t index;
  uint16_t server_address;
  uint8_t  max_items;
  uint8_t  server_status;
  uint8_t  unprov_dev_count;
  uuid_128 *unprov_uuid;
  uint16_t *unprov_oob_capabilities;
};

typedef struct remote_provisioning_server_s remote_provisioning_server_t;

// -----------------------------------------------------------------------------
// Static Variables

/// UUID of the unprovisioned device during remote provisioning operation
static uuid_128 rp_uuid;
/// List of available remote provisioning servers
static remote_provisioning_server_t *serverlist = NULL;
/// Number of nodes in the network
static uint16_t node_count;
/// Number of available active remote provisioning servers
static uint16_t active_server_count;
/// Netkey index of the ongoing command
static uint16_t active_netkey_index;
/// Index of the current server in the serverlist
static uint8_t serverlist_index;
/// Current retry numbers of server scan capabilities
static uint8_t scan_capabilities_retry_count;
/// Timer for server scan capabilities report
static app_timer_t get_capabilities_timer;
/// Timer for remote scanning unprovisioned devices
static app_timer_t unprov_scan_timer;

// -----------------------------------------------------------------------------
// Static Function Declarations

/***************************************************************************//**
* Server related list reorder by eliminating the non available or non active
* remote provisioning server elements from serverlist
*
*******************************************************************************/
static void serverlist_reorder(void);

/***************************************************************************//**
* Timer start and capabilities scan start for current server in serverlist
* @retval SL_STATUS_OK If the next server scan capabilities check started
*         successfully
*         Error code otherwise
*******************************************************************************/
static sl_status_t start_next_capabilities_scan(void);

/***************************************************************************//**
* Get server capabilities timer callback
*
* @param[in] timer Pointer to the timer used
* @param[in] data Data from the timer
*******************************************************************************/
static void on_get_capabilities_timer(app_timer_t *timer, void *data);

/***************************************************************************//**
* Get unprovisioned nodes scan timer callback
*
* @param[in] timer Pointer to the timer used
* @param[in] data Data from the timer
*******************************************************************************/
static void on_unprov_scan_timer(app_timer_t *timer, void *data);

// -----------------------------------------------------------------------------
// Function definitions

void btmesh_remote_prov_on_event(const sl_btmesh_msg_t *evt)
{
  sl_status_t sc;
  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_btmesh_evt_remote_provisioning_client_scan_capabilities_id: {
      const sl_btmesh_evt_remote_provisioning_client_scan_capabilities_t *rem_prov_scan_cap_evt;
      rem_prov_scan_cap_evt = &(evt->data.evt_remote_provisioning_client_scan_capabilities);
      if (rem_prov_scan_cap_evt->max_items > 0) {
        serverlist[serverlist_index].index = active_server_count;
        serverlist[serverlist_index].max_items = rem_prov_scan_cap_evt->max_items;
        serverlist[serverlist_index].server_status = REMOTE_PROV_SERVER_AVAILABLE;
        active_server_count++;
        btmesh_remote_prov_on_client_scan_capabilities(rem_prov_scan_cap_evt->server,
                                                       rem_prov_scan_cap_evt->max_items);
        sc = start_next_capabilities_scan();
        if (SL_STATUS_OK != sc) {
          app_log_status_warning_f(sc,
                                   "Failed to start next server scan capabilities check addr: 0x%04x!" APP_LOG_NEW_LINE,
                                   rem_prov_scan_cap_evt->server);
        }
      }
      break;
    }

    case sl_btmesh_evt_remote_provisioning_client_scan_report_id: {
      uint16_t server_idx;
      const sl_btmesh_evt_remote_provisioning_client_scan_report_t *rem_prov_scan_report_evt;
      rem_prov_scan_report_evt = &(evt->data.evt_remote_provisioning_client_scan_report);
      uint16_t oob = rem_prov_scan_report_evt->oob;
      for (server_idx = 0; server_idx < active_server_count; server_idx++) {
        if (rem_prov_scan_report_evt->server == serverlist[server_idx].server_address) {
          uint16_t unprov_cnt = serverlist[server_idx].unprov_dev_count;
          serverlist[server_idx].unprov_uuid = realloc(serverlist[server_idx].unprov_uuid, (unprov_cnt + 1) * sizeof(uuid_128));
          if (NULL != serverlist[server_idx].unprov_uuid) {
            memcpy(serverlist[server_idx].unprov_uuid[unprov_cnt].data, rem_prov_scan_report_evt->uuid.data, sizeof(uuid_128));
            serverlist[server_idx].unprov_dev_count++;
          } else {
            app_log_error("Memory realloc error for remote prov scanning"APP_LOG_NEW_LINE);
          }
          serverlist[server_idx].unprov_oob_capabilities = realloc(serverlist[server_idx].unprov_oob_capabilities, (unprov_cnt + 1) * sizeof(uint16_t));
          if (NULL != serverlist[server_idx].unprov_oob_capabilities) {
            serverlist[server_idx].unprov_oob_capabilities[unprov_cnt] = oob;
          } else {
            app_log_error("Memory realloc error for remote prov scanning"APP_LOG_NEW_LINE);
          }
        }
      }
      btmesh_remote_prov_on_client_scan_report(rem_prov_scan_report_evt->uuid);
      break;
    }

    case sl_btmesh_evt_remote_provisioning_client_link_report_id: {
      const sl_btmesh_evt_remote_provisioning_client_link_report_t *rem_prov_link_report_evt;
      rem_prov_link_report_evt = &(evt->data.evt_remote_provisioning_client_link_report);
      if ((sl_btmesh_remote_provisioning_server_success == rem_prov_link_report_evt->status)
          && (sl_btmesh_remote_provisioning_client_link_state_active == rem_prov_link_report_evt->state)) {
        sc = sl_btmesh_prov_provision_remote_device(rp_uuid, rem_prov_link_report_evt->server);
        if (SL_STATUS_OK != sc) {
          app_log_status_warning_f(sc, "Failed to start device remote provisioning!" APP_LOG_NEW_LINE);
        }
      } else if (sl_btmesh_remote_provisioning_server_link_closed_by_client != rem_prov_link_report_evt->status) {
        btmesh_prov_on_provision_failed_evt(rem_prov_link_report_evt->status,
                                            rp_uuid);
      }
      break;
    }
    case sl_btmesh_evt_remote_provisioning_client_scan_status_id: {
      const sl_btmesh_evt_remote_provisioning_client_scan_status_t *rem_prov_scan_status_evt;
      rem_prov_scan_status_evt = &(evt->data.evt_remote_provisioning_client_scan_status);
      btmesh_remote_prov_on_client_scan_status(rem_prov_scan_status_evt->server,
                                               rem_prov_scan_status_evt->status,
                                               rem_prov_scan_status_evt->state);
      break;
    }
    case sl_btmesh_evt_remote_provisioning_client_link_status_id: {
      const sl_btmesh_evt_remote_provisioning_client_link_status_t *rem_prov_link_status_evt;
      rem_prov_link_status_evt = &(evt->data.evt_remote_provisioning_client_link_status);
      btmesh_remote_prov_on_client_link_status(rem_prov_link_status_evt->server,
                                               rem_prov_link_status_evt->status,
                                               rem_prov_link_status_evt->state);
      break;
    }
    default:
      break;
  }
}

sl_status_t btmesh_remote_prov_start_server_capabilities_scan(uint16_t netkey_index)
{
  sl_status_t sc = SL_STATUS_OK;
  sl_slist_node_t *node_list;
  btmesh_db_node_t *node;
  btmesh_db_network_t *network = NULL;
  uint16_t idx = 0;

  node_count = 0;
  network = btmesh_db_network_get_network(netkey_index);

  if (NULL != network) {
    node_count = network->node_count;
  }

  if (0 < node_count) {
    active_netkey_index = netkey_index;
    // Clear remote serverlist
    btmesh_prov_free_remote_serverlist();
    // Create serverlist for all possible nodes
    serverlist = (remote_provisioning_server_t*)calloc(node_count, sizeof(remote_provisioning_server_t));
    if (NULL == serverlist) {
      sc = SL_STATUS_ALLOCATION_FAILED;
    } else {
      // Get the available nodelist
      node_list = btmesh_db_get_node_list();
      // Go trough nodelist and read the address of every available node
      idx = 0;
      SL_SLIST_FOR_EACH_ENTRY(node_list, node, btmesh_db_node_t, list_elem) {
        if (true == node->node_available) {
          serverlist[idx].server_address = node->prov.prim_address;
          serverlist[idx].index          = REMOTE_PROV_UNUSED_ID;
          idx++;
        }
      }
      // Start scanning available servers with first element in the list
      sc = sl_btmesh_remote_provisioning_client_get_scan_capabilities(netkey_index,
                                                                      serverlist[serverlist_index].server_address,
                                                                      REMOTE_PROV_CLIENT_ELEMENT_INDEX);
      if (SL_STATUS_OK != sc) {
        app_log_status_warning_f(sc,
                                 "Failed to start scan capabilities for server: 0x%04x!" APP_LOG_NEW_LINE,
                                 serverlist[serverlist_index].server_address);
      } else {
        // Start timer for scan capabilities response timeout
        sc = app_timer_start(&get_capabilities_timer,
                             SCAN_CAPABILITIES_TIMEOUT,
                             on_get_capabilities_timer,
                             NULL,
                             false);
        if (SL_STATUS_OK != sc) {
          app_log_status_warning_f(sc, "Failed to start capabilities timer" APP_LOG_NEW_LINE);
        }
      }
    }
  } else {
    sc = SL_STATUS_EMPTY;
  }
  return sc;
}

sl_status_t btmesh_remote_prov_start_device_scan_by_address(uint16_t netkey_index, uint16_t server, uint8_t timeout)
{
  uuid_128 dummy_uuid = { 0 };
  uint16_t idx;
  uint32_t timeout_ms;

  sl_status_t sc = sl_btmesh_remote_provisioning_client_start_scan(netkey_index,
                                                                   server,
                                                                   REMOTE_PROV_CLIENT_ELEMENT_INDEX,
                                                                   REMOTE_SCAN_ITEM_LIMIT,
                                                                   timeout,
                                                                   MULTIPLE_TARGET_SCAN,
                                                                   dummy_uuid);
  if (SL_STATUS_OK != sc) {
    app_log_status_warning_f(sc, "Failed to start remote scan!" APP_LOG_NEW_LINE);
  } else {
    timeout_ms = timeout * 1000;
    sc = app_timer_start(&unprov_scan_timer,
                         timeout_ms,
                         on_unprov_scan_timer,
                         NULL,
                         false);
    if (SL_STATUS_OK != sc) {
      app_log_status_warning_f(sc, "Failed to start scanning timer" APP_LOG_NEW_LINE);
    }
    for (idx = 0; idx < active_server_count; idx++) {
      if (server == serverlist[idx].server_address) {
        free(serverlist[idx].unprov_uuid);
        serverlist[idx].unprov_uuid = NULL;
        free(serverlist[idx].unprov_oob_capabilities);
        serverlist[idx].unprov_oob_capabilities = NULL;
        serverlist[idx].unprov_dev_count = 0;
      }
    }
  }

  return sc;
}

sl_status_t btmesh_remote_prov_list_unprovisioned_nodes_by_addr(uint16_t addr)
{
  uint16_t server_idx;
  uint16_t uuid_idx;

  for (server_idx = 0; server_idx < active_server_count; server_idx++) {
    if (addr == serverlist[server_idx].server_address) {
      for (uuid_idx = 0; uuid_idx < serverlist[server_idx].unprov_dev_count; uuid_idx++) {
        btmesh_remote_prov_on_unprovisioned_node_list(uuid_idx,
                                                      serverlist[server_idx].unprov_uuid[uuid_idx]);
      }
      if (0 != uuid_idx) {
        return SL_STATUS_OK;
      } else {
        return SL_STATUS_EMPTY;
      }
    }
  }
  return SL_STATUS_EMPTY;
}

sl_status_t btmesh_remote_prov_start_provisioning(uint16_t netkey_index,
                                                  uint16_t server,
                                                  uuid_128 uuid,
                                                  uint8_t bearer_type,
                                                  uint8_t attention_timer_sec)
{
  sl_status_t sc;
  rp_uuid = uuid;
  bd_addr rp_mac = { 0 };
  sc = btmesh_prov_setup_provisioning(netkey_index, rp_uuid, bearer_type, attention_timer_sec);
  if (SL_STATUS_BT_MESH_ALREADY_EXISTS == sc) {
    btmesh_db_add_node_to_network_by_uuid(netkey_index, rp_uuid);
    btmesh_prov_delete_ddb_entry(rp_uuid);
  } else if (SL_STATUS_OK != sc) {
    app_log_status_warning_f(sc, "Failed to create provisioning session!" APP_LOG_NEW_LINE);
  } else {
    sc = btmesh_db_create_node(rp_uuid, rp_mac, server, 0, bearer_type, 0);
    if ((SL_STATUS_OK != sc) && (SL_STATUS_ALREADY_EXISTS != sc)) {
      app_log_status_warning_f(sc, "Failed to create node in database!" APP_LOG_NEW_LINE);
    }

    sc = btmesh_db_add_node_to_network_by_uuid(netkey_index, rp_uuid);
    if (SL_STATUS_OK != sc) {
      app_log_status_warning_f(sc, "Failed to add node to network in database!" APP_LOG_NEW_LINE);
    }

    sc = sl_btmesh_remote_provisioning_client_open_link(netkey_index,
                                                        server,
                                                        REMOTE_PROV_CLIENT_ELEMENT_INDEX,
                                                        LINK_OPEN_TIMEOUT,
                                                        REMOTE_PROV_NPPI_DISABLE,
                                                        rp_uuid);
    if (SL_STATUS_OK != sc) {
      app_log_status_warning_f(sc, "Remote provisioning failed to open link!" APP_LOG_NEW_LINE);
    }
  }

  return sc;
}

sl_status_t btmesh_remote_prov_get_server_address_by_id(uint16_t id, uint16_t *server)
{
  uint16_t server_idx;

  for (server_idx = 0; server_idx < active_server_count; server_idx++) {
    if (id == serverlist[server_idx].index) {
      *server = serverlist[server_idx].server_address;
      return SL_STATUS_OK;
    }
  }
  return SL_STATUS_NOT_FOUND;
}

sl_status_t btmesh_remote_prov_get_unprov_uuid_by_id(uint16_t id, uint16_t server, uuid_128 *uuid, uint16_t *oob_capabilities)
{
  uint16_t server_idx;
  uint16_t uuid_idx;

  for (server_idx = 0; server_idx < active_server_count; server_idx++) {
    if (server == serverlist[server_idx].server_address) {
      for (uuid_idx = 0; uuid_idx < serverlist[server_idx].unprov_dev_count; uuid_idx++) {
        if (id == uuid_idx) {
          *uuid = serverlist[server_idx].unprov_uuid[uuid_idx];
          *oob_capabilities = serverlist[server_idx].unprov_oob_capabilities[uuid_idx];
          return SL_STATUS_OK;
        }
      }
    }
  }
  return SL_STATUS_EMPTY;
}

void btmesh_prov_free_remote_serverlist(void)
{
  uint16_t idx;
  if (NULL != serverlist) {
    for (idx = 0; idx < active_server_count; idx++) {
      free(serverlist[idx].unprov_uuid);
      serverlist[idx].unprov_uuid = NULL;
    }
    free(serverlist);
    serverlist = NULL;
    active_server_count = 0;
    serverlist_index = 0;
    scan_capabilities_retry_count = 0;
  }
}

sl_status_t btmesh_remote_prov_list_active_servers(void)
{
  uint16_t idx = 0;
  uint16_t cnt = 0;

  while (idx < active_server_count) {
    if (REMOTE_PROV_SERVER_AVAILABLE == serverlist[cnt].server_status) {
      btmesh_remote_prov_on_serverlist(serverlist[cnt].index, serverlist[cnt].server_address);
      idx++;
    }
    cnt++;
  }
  if (0 == idx) {
    return SL_STATUS_EMPTY;
  }

  return SL_STATUS_OK;
}

// -----------------------------------------------------------------------------
// Local static functions

static void serverlist_reorder(void)
{
  remote_provisioning_server_t *tmp_serverlist = NULL;
  uint16_t idx;

  tmp_serverlist = (remote_provisioning_server_t*)calloc(active_server_count, sizeof(remote_provisioning_server_t));

  if (NULL != tmp_serverlist) {
    for (idx = 0; idx < node_count; idx++) {
      if ((REMOTE_PROV_SERVER_AVAILABLE == serverlist[idx].server_status) && (0 != serverlist[idx].server_address)) {
        memcpy(tmp_serverlist + serverlist[idx].index, serverlist + idx, sizeof(remote_provisioning_server_t) );
      }
    }

    free(serverlist);
    serverlist = tmp_serverlist;
  }
}

static sl_status_t start_next_capabilities_scan(void)
{
  sl_status_t ret_val = SL_STATUS_OK;
  sl_status_t sc = app_timer_stop(&get_capabilities_timer);
  if (SL_STATUS_OK != sc) {
    app_log_status_warning_f(sc, "Failed to stop timer!" APP_LOG_NEW_LINE);
    ret_val = sc;
  }
  serverlist_index++;
  if (node_count > serverlist_index) {
    // Initialize retry counter at first scan capabilities call for next node in list
    scan_capabilities_retry_count = 0;

    sc = sl_btmesh_remote_provisioning_client_get_scan_capabilities(active_netkey_index,
                                                                    serverlist[serverlist_index].server_address,
                                                                    REMOTE_PROV_CLIENT_ELEMENT_INDEX);
    if (SL_STATUS_OK != sc) {
      app_log_status_warning_f(sc,
                               "Failed to start scan capabilities for next server: 0x%04x!" APP_LOG_NEW_LINE,
                               serverlist[serverlist_index].server_address);
      ret_val = sc;
    }
    sc = app_timer_start(&get_capabilities_timer,
                         SCAN_CAPABILITIES_TIMEOUT,
                         on_get_capabilities_timer,
                         NULL,
                         false);
    if (SL_STATUS_OK != sc) {
      app_log_status_warning_f(sc, "Failed to start capabilities timer next server" APP_LOG_NEW_LINE);
      ret_val = sc;
    }
  } else {
    serverlist_reorder();
    btmesh_remote_prov_on_client_scan_capabilities_finished();
  }
  return ret_val;
}

// -----------------------------------------------------------------------------
// Timer callbacks

static void on_get_capabilities_timer(app_timer_t *timer, void *data)
{
  (void)data;
  (void)timer;

  sl_status_t sc;
  if (SCAN_CAPABILITIES_RETRY > scan_capabilities_retry_count) {
    scan_capabilities_retry_count++;
    sc = sl_btmesh_remote_provisioning_client_get_scan_capabilities(active_netkey_index,
                                                                    serverlist[serverlist_index].server_address,
                                                                    REMOTE_PROV_CLIENT_ELEMENT_INDEX);
    if (SL_STATUS_OK != sc) {
      app_log_status_warning_f(sc,
                               "Failed to restart scan capabilities for server: 0x%04x in cb!" APP_LOG_NEW_LINE,
                               serverlist[serverlist_index].server_address);
    }
    sc = app_timer_start(&get_capabilities_timer,
                         SCAN_CAPABILITIES_TIMEOUT,
                         on_get_capabilities_timer,
                         NULL,
                         false);
    if (SL_STATUS_OK != sc) {
      app_log_status_warning_f(sc, "Failed to start capabilities timer in callback retry" APP_LOG_NEW_LINE);
    }
  } else {
    serverlist_index++;
    if (node_count > serverlist_index) {
      // Initialize retry counter at first scan capabilities call for next node in list
      scan_capabilities_retry_count = 0;
      sc = sl_btmesh_remote_provisioning_client_get_scan_capabilities(active_netkey_index,
                                                                      serverlist[serverlist_index].server_address,
                                                                      REMOTE_PROV_CLIENT_ELEMENT_INDEX);
      if (SL_STATUS_OK != sc) {
        app_log_status_warning_f(sc,
                                 "Failed to start scan capabilities for next server: 0x%04x in cb!" APP_LOG_NEW_LINE,
                                 serverlist[serverlist_index].server_address);
      }
      sc = app_timer_start(&get_capabilities_timer,
                           SCAN_CAPABILITIES_TIMEOUT,
                           on_get_capabilities_timer,
                           NULL,
                           false);
      if (SL_STATUS_OK != sc) {
        app_log_status_warning_f(sc, "Failed to start capabilities timer in callback next server" APP_LOG_NEW_LINE);
      }
    } else {
      // If all servers capabilities scan are finalized reorganize the list by removing the non-active servers
      serverlist_reorder();
      btmesh_remote_prov_on_client_scan_capabilities_finished();
    }
  }
}

static void on_unprov_scan_timer(app_timer_t *timer, void *data)
{
  (void)data;
  (void)timer;

  btmesh_remote_prov_on_client_scan_finished();
}

// -----------------------------------------------------------------------------
// Weak implementations of callbacks

SL_WEAK void btmesh_remote_prov_on_client_scan_capabilities(uint16_t server,
                                                            uint8_t  max_items)
{
  (void)server;
  (void)max_items;
}

SL_WEAK void btmesh_remote_prov_on_client_scan_capabilities_finished(void)
{
}

SL_WEAK void btmesh_remote_prov_on_client_scan_report(uuid_128 uuid)
{
  (void)uuid;
}

SL_WEAK void btmesh_remote_prov_on_client_scan_finished(void)
{
}

SL_WEAK void btmesh_remote_prov_on_unprovisioned_node_list(uint16_t id,
                                                           uuid_128 uuid)
{
  (void)id;
  (void)uuid;
}

SL_WEAK void btmesh_remote_prov_on_serverlist(uint16_t id,
                                              uint16_t server)
{
  (void)id;
  (void)server;
}

SL_WEAK void btmesh_remote_prov_on_client_scan_status(uint16_t server,
                                                      uint8_t status,
                                                      uint8_t state)
{
}

SL_WEAK void btmesh_remote_prov_on_client_link_status(uint16_t server,
                                                      uint8_t status,
                                                      uint8_t state)
{
}
