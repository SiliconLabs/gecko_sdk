/***************************************************************************//**
 * @brief Adaptation for running Bluetooth on baremetal
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
#include "em_core.h"
#include <em_device.h>
#include <em_chip.h>

static uint32_t sli_btctrl_events;

void BTLE_LL_Process(uint32_t events);

void PendSV_Handler(void)
{
  CORE_DECLARE_IRQ_STATE;
  uint32_t events;

  CORE_ENTER_ATOMIC();
  events = sli_btctrl_events;
  sli_btctrl_events = 0;
  CORE_EXIT_ATOMIC();

  BTLE_LL_Process(events);
}

static void sli_btctrl_task_default_callback(void)
{
  //start sv
  SCB->ICSR = SCB_ICSR_PENDSVSET_Msk;
}

void BTLE_LL_EventRaise(uint32_t events)
{
  CORE_DECLARE_IRQ_STATE;
  if ((sli_btctrl_events & events) == events) {
    return;//Events already set
  }
  CORE_ENTER_ATOMIC();
  sli_btctrl_events |= events;
  CORE_EXIT_ATOMIC();
  sli_btctrl_task_default_callback();
}

void sli_btctrl_events_init()
{
  NVIC_ClearPendingIRQ(PendSV_IRQn);
  NVIC_EnableIRQ(PendSV_IRQn);
}

bool sli_pending_btctrl_events(void)
{
  if (sli_btctrl_events) {
    return true;
  } else {
    return false;
  }
}
