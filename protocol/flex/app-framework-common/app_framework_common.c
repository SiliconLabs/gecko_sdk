/***************************************************************************//**
 * @brief Connect Application Framework common code.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#include <assert.h>
#include "callback_dispatcher.h"
#include "app_framework_callback.h"
#include "stack/core/sl-connect-watchdog.h"
#include "em_rmu.h"
#include "em_emu.h"

#include "sl_component_catalog.h"

#if defined(SL_CATALOG_CONNECT_CMSIS_STACK_IPC_PRESENT)
extern EmberStatus emApiInit(void);
extern void emApiTick(void);
#define stack_init emApiInit
#define stack_tick emApiTick
#else
#define stack_init emberInit
#define stack_tick emberTick
#endif

EmberTaskId emAppTask;
extern const EmberEventData emAppEvents[];
extern void(*emAppEventsHandlerPtrTable[])(void);
extern const uint8_t emAfEventTableOffset;
extern uint8_t emAfEventTableHandleIndex;

static uint32_t savedResetCause;

void connect_standard_phy_2_4g(void)
{
  assert(emberPhyConfigInit(EMBER_STANDARD_PHY_2_4GHZ) == EMBER_SUCCESS);
}

void connect_stack_init(void)
{
  EmberStatus status;

  #ifndef EMBER_TEST
  savedResetCause = RMU_ResetCauseGet();
  RMU_ResetCauseClear(); // So resetCause is rational and not an accumulated mess
  // Release GPIOs that were held by EM4h to ensure proper startup
  EMU_UnlatchPinRetention();
  #endif

  emberTaskEnableIdling(true);

  // Initialize the radio and the stack.  If this fails, we have to assert
  // because something is wrong.
  status = stack_init();
  assert(status == EMBER_SUCCESS);
}

uint32_t emberAfGetResetCause(void)
{
  return savedResetCause;
}

void connect_app_framework_init(void)
{
  // Init and register the application events.
  emAppTask = emberTaskInit(emAppEvents);

  // Call the init callback of plugins that subscribed to it.
  emberAfInit();
  // Call the application init callback.
  emberAfInitCallback();
}

EmberStatus emberAfAllocateEvent(EmberEventControl **control, void (*handler)(void))
{
  if (emAppEvents[emAfEventTableHandleIndex + emAfEventTableOffset].control != NULL) {
    *control = emAppEvents[emAfEventTableHandleIndex + emAfEventTableOffset].control;
    emAppEventsHandlerPtrTable[emAfEventTableHandleIndex] = handler;
    emAfEventTableHandleIndex++;
    return EMBER_SUCCESS;
  } else {
    // table is full
    return EMBER_TABLE_FULL;
  }
}

void connect_stack_tick(void)
{
  // Pet the watchdog.
  WDOGn_Feed(DEFAULT_WDOG);
  // Call the stack tick API.
  stack_tick();
}

void connect_app_framework_tick(void)
{
  // Pet the watchdog.
  WDOGn_Feed(DEFAULT_WDOG);
  // Call the application tick callback.
  emberAfTickCallback();
  // Call the tick callback of plugins that subscribed to it.
  emberAfTick();
  // Run application events.
  emberRunTask(emAppTask);
}
