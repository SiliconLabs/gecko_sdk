/***************************************************************************//**
 * @brief Adaptation for running Bluetooth in RTOS
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

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <cmsis_os2.h>
#include "sl_status.h"
#include "em_core.h"
#include "sl_cmsis_os2_common.h"
#include "sl_btctrl_rtos_config.h"
#include "sl_btctrl_rtos.h"

#ifdef CONFIGURATION_HEADER
#include CONFIGURATION_HEADER
#endif // CONFIGURATION_HEADER

//Bluetooth event flag definitions
#define SL_BT_RTOS_EVENT_FLAG_LL           0x00000002U    //Linklayer task needs an update

static uint32_t sli_btctrl_events;

//Bluetooth linklayer thread
static void linklayer_thread(void *p_arg);
static osThreadId_t tid_thread_link_layer;
__ALIGNED(8) static uint8_t thread_link_layer_stk[
  SL_BTCTRL_RTOS_LINK_LAYER_TASK_STACK_SIZE & 0xFFFFFFF8u];
__ALIGNED(4) static uint8_t thread_link_layer_cb[osThreadCbSize];
static const osThreadAttr_t thread_Linklayer_attr = {
  .name = "Bluetooth linklayer",
  .stack_mem = thread_link_layer_stk,
  .stack_size = sizeof(thread_link_layer_stk),
  .cb_mem = thread_link_layer_cb,
  .cb_size = osThreadCbSize,
  .priority = (osPriority_t) SL_BTCTRL_RTOS_LINK_LAYER_TASK_PRIORITY
};

static osEventFlagsId_t bluetooth_event_flags;
__ALIGNED(4) static uint8_t bluetooth_event_flags_cb[osEventFlagsCbSize];
static const osEventFlagsAttr_t bluetooth_event_flags_attr = {
  .name = "Bluetooth event flags",
  .attr_bits = 0U,
  .cb_mem = bluetooth_event_flags_cb,
  .cb_size = osEventFlagsCbSize
};

uint8_t sl_btctrl_rtos_get_stack_space(uint32_t *stack_space)
{
  *stack_space = osThreadGetStackSpace(tid_thread_link_layer);
  return 0;
}

static void sl_btctrl_rtos_deinit()
{
  (void) osEventFlagsDelete(bluetooth_event_flags);
  bluetooth_event_flags = NULL;
  (void) osThreadTerminate(tid_thread_link_layer);
  tid_thread_link_layer = NULL;
}

sl_status_t sl_btctrl_rtos_init()
{
  // Create event flags
  if (bluetooth_event_flags == NULL) {
    bluetooth_event_flags = osEventFlagsNew(&bluetooth_event_flags_attr);
  }
  if (bluetooth_event_flags == NULL) {
    goto failed;
  }

  // Create thread for Linklayer
  if (tid_thread_link_layer == NULL) {
    tid_thread_link_layer = osThreadNew(linklayer_thread,
                                        NULL,
                                        &thread_Linklayer_attr);
  }
  if (tid_thread_link_layer == NULL) {
    goto failed;
  }

  return SL_STATUS_OK;
  failed:
  sl_btctrl_rtos_deinit();
  return SL_STATUS_FAIL;
}

void BTLE_LL_Process(uint32_t events);

static void linklayer_thread(void *p_arg)
{
  (void)p_arg;
  CORE_DECLARE_IRQ_STATE;

  uint32_t events;
  while (1) {
    osEventFlagsWait(bluetooth_event_flags,
                     SL_BT_RTOS_EVENT_FLAG_LL,
                     osFlagsWaitAny,
                     osWaitForever);

    CORE_ENTER_ATOMIC();
    events = sli_btctrl_events;
    sli_btctrl_events = 0;
    CORE_EXIT_ATOMIC();

    BTLE_LL_Process(events);
  }
}

bool sli_pending_btctrl_events(void)
{
  return sli_btctrl_events != 0;
}

void BTLE_LL_EventRaise(uint32_t events)
{
  if ((sli_btctrl_events & events) == events) {//Events already pending
    return;
  }
  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_ATOMIC();
  sli_btctrl_events |= events;
  CORE_EXIT_ATOMIC();
  osEventFlagsSet(bluetooth_event_flags,
                  SL_BT_RTOS_EVENT_FLAG_LL);
}
