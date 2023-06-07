/***************************************************************************//**
 * @file
 * @brief MVP HAL driver.
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
#include "sl_mvp_hal.h"
#include "sl_driver_mvp_config.h"
#include "em_device.h"
#if SL_MVP_ENABLE_DMA
#include "em_ldma.h"
#endif
#include "em_cmu.h"
#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif
#if defined(SL_CATALOG_KERNEL_PRESENT)
#include "cmsis_os2.h"
#endif
#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
#include "sl_power_manager.h"
#endif
#if SL_MVP_POWER_MODE == 1
#include "em_emu.h"
#endif

//************************************
// Validate configuration

#if SL_MVP_POWER_MODE == 1 && defined(SL_CATALOG_KERNEL_PRESENT)
  #error "SL_MVP_POWER_MODE=1 cannot be used together with an RTOS"
#endif

#if SL_MVP_POWER_MODE > 2
  #error "Unknown SL_MVP_POWER_MODE value"
#endif

//************************************
// Macro definitions

// This macro is used to configure if the MVP is enabled at all times between
// init and deinit by setting it to 1, or just enabled during command execution
// by setting it to 0.
#define SPEED_OVER_POWER          1

#if SL_MVP_POWER_MODE == 2
#define SL_MVP_EVENT_FLAG_IDLE    0x1
#endif

//************************************
// Static variables

static sli_mvp_enable_callback  callback_enable = NULL;
static sli_mvp_disable_callback callback_disable = NULL;
static sli_mvp_isr_callback     callback_isr = NULL;
static volatile bool            mvp_is_initialized = false;
static volatile bool            mvp_is_busy = false;
static sli_mvp_hal_config_t     hal_config = { .use_dma = SL_MVP_ENABLE_DMA,
                                               .dma_ch = SL_MVP_DMA_CHANNEL };
#if SL_MVP_ENABLE_DMA
static LDMA_Descriptor_t ldma_descriptor = LDMA_DESCRIPTOR_SINGLE_M2M_WORD(0, 0, 0);
static LDMA_TransferCfg_t ldma_config = LDMA_TRANSFER_CFG_MEMORY();
#endif

#if SL_MVP_POWER_MODE == 2
static bool                     mvp_event_is_initialized = false;
static osEventFlagsId_t         mvp_event_id;
#endif

//************************************
// Static functions

/**
 * @brief
 *   Load a program using the CPU.
 */
static void cpu_load(uint32_t *src, uint32_t *dst, size_t length)
{
  length /= sizeof(uint32_t);
  for (size_t i = 0; i < length; i++) {
    dst[i] = src[i];
  }
}

#if SL_MVP_ENABLE_DMA
/**
 * @brief
 *   Load a program using the LDMA.
 */
static void dma_load(void *src, void *dst, size_t length)
{
  length /= sizeof(uint32_t);
  ldma_descriptor.xfer.srcAddr = (uint32_t)src;
  ldma_descriptor.xfer.dstAddr = (uint32_t)dst;
  ldma_descriptor.xfer.xferCnt = length - 1;
  LDMA_StartTransfer(hal_config.dma_ch, &ldma_config, &ldma_descriptor);
}
#endif

/**
 * @brief
 *   Disable the MVP program execution.
 */
static void cmd_disable(void)
{
#if !SPEED_OVER_POWER
  if (callback_disable != NULL) {
    callback_disable();
  }
#endif
#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
  sl_power_manager_remove_em_requirement(SL_POWER_MANAGER_EM1);
#endif
  mvp_is_busy = false;
#if SL_MVP_POWER_MODE == 2
  uint32_t ret = osEventFlagsSet(mvp_event_id, SL_MVP_EVENT_FLAG_IDLE);
  EFM_ASSERT((int)ret >= 0);
#endif
}

#if defined(SL_CATALOG_POWER_MANAGER_PRESENT) && SPEED_OVER_POWER
/**
 * @brief
 *   Power manager callback when entering EM2/EM3 or waking up from EM2/EM3.
 */
static void em_transition(sl_power_manager_em_t from, sl_power_manager_em_t to)
{
  (void)from;

  if ((to == SL_POWER_MANAGER_EM2) || (to == SL_POWER_MANAGER_EM3)) {
    if (callback_disable != NULL) {
      callback_disable();
    }
  } else if ((to == SL_POWER_MANAGER_EM1) || (to == SL_POWER_MANAGER_EM0)) {
    if (callback_enable != NULL) {
      callback_enable();
    }
  }
}

static sl_power_manager_em_transition_event_handle_t em_event_handle;
static const sl_power_manager_em_transition_event_info_t em_event_info = {
  .event_mask = (SL_POWER_MANAGER_EVENT_TRANSITION_ENTERING_EM2
                | SL_POWER_MANAGER_EVENT_TRANSITION_LEAVING_EM2
                | SL_POWER_MANAGER_EVENT_TRANSITION_ENTERING_EM3
                | SL_POWER_MANAGER_EVENT_TRANSITION_LEAVING_EM3),
  .on_event = em_transition,
};

/**
 * @brief
 *   Add power manager transition event handling.
 */
static void em_add_transition_callback(void)
{
  sl_power_manager_subscribe_em_transition_event(&em_event_handle, &em_event_info);
}

/**
 * @brief
 *   Remove power manager transition event handling.
 */
static void em_remove_transition_callback(void)
{
  sl_power_manager_unsubscribe_em_transition_event(&em_event_handle);
}
#endif

#if SL_MVP_POWER_MODE == 2
/**
 * @brief
 *   Set the initial value of the idle flag.
 *
 * @note
 *   The os must be running before setting initial flag state.
 *   When the program is running it is ok to set the flag.
 */
static void set_idle_flag_initially(void)
{
  if (!mvp_event_is_initialized) {
    mvp_event_is_initialized = true;
    uint32_t ret = osEventFlagsSet(mvp_event_id, SL_MVP_EVENT_FLAG_IDLE);
    EFM_ASSERT((int)ret >= 0);
  }
}
#endif

//************************************
// Exported functions

sl_status_t sli_mvp_hal_config(sli_mvp_hal_config_t *config)
{
  hal_config = *config;
#if SL_MVP_ENABLE_DMA
  if (hal_config.use_dma) {
    CMU_ClockEnable(cmuClock_LDMA, true);
    LDMA_Init_t ldma_init = LDMA_INIT_DEFAULT;
    LDMA_Init(&ldma_init);
  }
#endif
  return SL_STATUS_OK;
}

sl_status_t sli_mvp_hal_init(sli_mvp_enable_callback enable, sli_mvp_disable_callback disable, sli_mvp_isr_callback isr)
{
  if (mvp_is_initialized) {
    return SL_STATUS_ALREADY_INITIALIZED;
  }
  callback_enable = enable;
  callback_disable = disable;
  callback_isr = isr;
  CMU->CLKEN1_SET = CMU_CLKEN1_MVP;
  sli_mvp_hal_config(&hal_config);
  NVIC_EnableIRQ(MVP_IRQn);
#if SPEED_OVER_POWER
  if (callback_enable != NULL) {
    callback_enable();
  }
#endif
#if SL_MVP_POWER_MODE == 2
  mvp_event_id = osEventFlagsNew(NULL);
  EFM_ASSERT(mvp_event_id != NULL);
#endif
#if defined(SL_CATALOG_POWER_MANAGER_PRESENT) && SPEED_OVER_POWER
  em_add_transition_callback();
#endif
  mvp_is_initialized = true;
  mvp_is_busy = false;
  return SL_STATUS_OK;
}

sl_status_t sli_mvp_hal_deinit(void)
{
  if (!mvp_is_initialized) {
    return SL_STATUS_NOT_INITIALIZED;
  }
  if (mvp_is_busy) {
    cmd_disable();
  }
#if SL_MVP_POWER_MODE == 2
  osStatus_t status = osEventFlagsDelete(mvp_event_id);
  EFM_ASSERT(status == osOK);
#endif
#if SPEED_OVER_POWER
  if (callback_disable != NULL) {
    callback_disable();
  }
#endif
#if defined(SL_CATALOG_POWER_MANAGER_PRESENT) && SPEED_OVER_POWER
  em_remove_transition_callback();
#endif
  mvp_is_initialized = false;
  NVIC_DisableIRQ(MVP_IRQn);
  CMU->CLKEN1_CLR = CMU_CLKEN1_MVP;
  return SL_STATUS_OK;
}

sl_status_t sli_mvp_hal_load_program(void *src, void *dst, size_t length)
{
  if (!mvp_is_initialized) {
    return SL_STATUS_NOT_INITIALIZED;
  }
  if (!mvp_is_busy) {
    return SL_STATUS_NOT_AVAILABLE;
  }
#if SL_MVP_ENABLE_DMA
  if (hal_config.use_dma) {
    dma_load(src, dst, length);
  } else {
    cpu_load(src, dst, length);
  }
#else
  cpu_load(src, dst, length);
#endif
  return SL_STATUS_OK;
}

void sli_mvp_hal_cmd_enable(void)
{
#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
  sl_power_manager_add_em_requirement(SL_POWER_MANAGER_EM1);
#endif
#if !SPEED_OVER_POWER
  if (callback_enable != NULL) {
    callback_enable();
  }
#endif
  mvp_is_busy = true;
#if SL_MVP_POWER_MODE == 2
  set_idle_flag_initially();
  // Consume the idle flag.
  uint32_t ret = osEventFlagsWait(mvp_event_id, SL_MVP_EVENT_FLAG_IDLE, osFlagsWaitAny, osWaitForever);
  EFM_ASSERT((int)ret >= 0);
#endif
}

bool sli_mvp_hal_cmd_is_busy(void)
{
  if (!mvp_is_initialized) {
    return false;
  }
  return mvp_is_busy;
}

void sli_mvp_hal_cmd_wait_for_completion()
{
#if SL_MVP_POWER_MODE == 1
  CORE_DECLARE_IRQ_STATE;
#endif

  if (!mvp_is_initialized) {
    return;
  }
#if SL_MVP_POWER_MODE == 2
  set_idle_flag_initially();
  uint32_t ret = osEventFlagsWait(mvp_event_id, SL_MVP_EVENT_FLAG_IDLE, osFlagsNoClear, osWaitForever);
  EFM_ASSERT((int)ret >= 0);
#else
  // Logically, just wait for the busy flag to go off. It's cleared in the ISR
  // when the operation is complete.
  // Because the busy flag is in memory, the MVP may add stalls if the flag is
  // accessed during program execution.
  // Mitigation: During most of the waiting, wait for the MVP to become idle.
  // This is the only improvement that requires knowledge of MVP registers in HAL.
  while(!(MVP->STATUS & MVP_STATUS_IDLE)) {
    // Wait until the MVP is idle.
#if SL_MVP_POWER_MODE == 1
    CORE_ENTER_CRITICAL();
    if (!(MVP->STATUS & MVP_STATUS_IDLE)) {
      EMU_EnterEM1();
    }
    CORE_EXIT_CRITICAL();
#endif
  }
  // Finally, wait for the interrupt handler to clear the flag.
  // It may take a few more cycles after the MVP has become idle.
  while (mvp_is_busy) {
  }
#endif
}

/**
 * @brief
 *   MVP Interrupt handler
 *
 * @details
 *   This interrupt handler is triggered whenever a program is done or when one
 *   of the performance counters wraps.
 */
void MVP_IRQHandler(void)
{
  if (callback_isr != NULL) {
    bool done;
    done = callback_isr();
    if (done) {
      cmd_disable();
    }
  }
}
