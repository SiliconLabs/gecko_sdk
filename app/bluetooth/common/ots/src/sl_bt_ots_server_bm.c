/***************************************************************************//**
 * @file
 * @brief OTS Server adaptation without an OS Kernel (Bare Metal)
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
#include <stdbool.h>
#include <stdint.h>
#include "sl_status.h"
#include "em_core.h"
#include "sli_bt_ots_server_adaptation.h"
#include "sl_bt_ots_server_config.h"
#include "sl_bt_ots_server_instances.h"
#include "sl_bluetooth_connection_config.h"
#include "sli_bt_ots_datatypes.h"
#include "app_queue.h"

// -----------------------------------------------------------------------------
// Bare metal private variables

// Storage for indication queues
static uint8_t indication_queue_data[SL_BT_CONFIG_MAX_CONNECTIONS]
[SL_BT_OTS_SERVER_CONFIG_INDICATION_QUEUE_SIZE
 * sizeof(sli_bt_ots_indication_queue_item_t)];

// Indication queue implementation
static app_queue_t indication_queue[SL_BT_CONFIG_MAX_CONNECTIONS];

// -----------------------------------------------------------------------------
// Forward declaration of private functions

static bool server_has_task(void);

// -----------------------------------------------------------------------------
// Bare metal functions

bool sli_bt_ots_server_adaptation_indication_queue_is_empty(uint8_t index)
{
  bool ret = false;
  ret = app_queue_is_empty(&indication_queue[index]);
  return ret;
}

sl_status_t sli_bt_ots_server_adaptation_indication_queue_add(uint8_t                            index,
                                                              sli_bt_ots_indication_queue_item_t *item)
{
  sl_status_t sc = SL_STATUS_NOT_FOUND;
  if (index < SL_BT_CONFIG_MAX_CONNECTIONS) {
    sc = app_queue_add(&indication_queue[index], (uint8_t *)item);
  }
  return sc;
}

sl_status_t sli_bt_ots_server_adaptation_indication_queue_peek(uint8_t                            index,
                                                               sli_bt_ots_indication_queue_item_t *item)
{
  sl_status_t sc = SL_STATUS_NOT_FOUND;
  if (index < SL_BT_CONFIG_MAX_CONNECTIONS) {
    sc = app_queue_peek(&indication_queue[index],
                        (uint8_t *)item);
  }
  return sc;
}

sl_status_t sli_bt_ots_server_adaptation_indication_queue_remove(uint8_t index)
{
  sl_status_t sc = SL_STATUS_NOT_FOUND;
  sli_bt_ots_indication_queue_item_t item;
  if (index < SL_BT_CONFIG_MAX_CONNECTIONS) {
    sc = app_queue_remove(&indication_queue[index],
                          (uint8_t *)&item);
  }
  return sc;
}

sl_status_t sli_bt_ots_server_adaptation_indication_queue_proceed()
{
  // Do nothing for bare metal
  return SL_STATUS_OK;
}

sl_status_t sli_bt_ots_server_adaptation_indication_queue_clear(uint8_t index)
{
  sl_status_t sc = SL_STATUS_NOT_FOUND;
  if (index >= SL_BT_CONFIG_MAX_CONNECTIONS) {
    return sc;
  }

  CORE_DECLARE_IRQ_STATE;

  CORE_ENTER_CRITICAL();
  // Reinit queue
  app_queue_t *queue = &indication_queue[index];
  sc = app_queue_init(queue, queue->size, queue->item_size, queue->data);
  CORE_EXIT_CRITICAL();
  return sc;
}

sl_status_t sli_bt_ots_server_adaptation_acquire(void)
{
  // Do nothing for bare metal
  return SL_STATUS_OK;
}

sl_status_t sli_bt_ots_server_adaptation_release(void)
{
  // Do nothing for bare metal
  return SL_STATUS_OK;
}

void sli_bt_ots_server_adaptation_init(void)
{
  CORE_DECLARE_IRQ_STATE;

  CORE_ENTER_CRITICAL();
  // Initialize Object Server instance
  for (uint8_t i = 0; i < SL_BT_CONFIG_MAX_CONNECTIONS; i++) {
    app_queue_init(&indication_queue[i],
                   SL_BT_OTS_SERVER_CONFIG_INDICATION_QUEUE_SIZE,
                   sizeof(sli_bt_ots_indication_queue_item_t),
                   indication_queue_data[i]);
  }
  CORE_EXIT_CRITICAL();
}

#ifdef SL_CATALOG_POWER_MANAGER_PRESENT

static bool server_has_task(void)
{
  for (uint8_t queue_index = 0;
       queue_index < SL_BT_CONFIG_MAX_CONNECTIONS;
       queue_index++) {
    if ( !app_queue_is_empty(&indication_queue[queue_index])) {
      return true;
    }
  }
  return false;
}

sl_power_manager_on_isr_exit_t sli_bt_ots_server_sleep_on_isr_exit(void)
{
  sl_power_manager_on_isr_exit_t ret = SL_POWER_MANAGER_IGNORE;
  if (server_has_task()) {
    ret = SL_POWER_MANAGER_WAKEUP;
  }
  return ret;
}

bool sli_bt_ots_server_is_ok_to_sleep(void)
{
  bool ret = true;
  if (server_has_task()) {
    ret = false;
  }
  return ret;
}

#endif // SL_CATALOG_POWER_MANAGER_PRESENT
