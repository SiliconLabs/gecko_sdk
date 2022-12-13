/***************************************************************************//**
 * @file
 * @brief OS memory debug for application
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
//                                   Includes
// -----------------------------------------------------------------------------

#include <assert.h>
#include <stdint.h>

#include "app_os_stat.h"
#include "app_os_stat_config.h"
#include "sl_mempool.h"
#include "sl_status.h"
#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"
#include "sl_component_catalog.h"

#if defined(SL_CATALOG_MICRIUMOS_KERNEL_PRESENT)
#include "os_cfg.h"
#elif defined (SL_CATALOG_FREERTOS_KERNEL_PRESENT)
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#endif

// Check RTT setup
#if (SEGGER_RTT_PRINTF_BUFFER_SIZE < 512UL)
#warning 'SEGGER_RTT_PRINTF_BUFFER_SIZE' not set. (>= 512 recommended)
#endif

// Check OS config to get info about threafs
#if APP_OS_STAT_THREAD_STACK_ENABLED
#if defined(SL_CATALOG_MICRIUMOS_KERNEL_PRESENT)
  #if !OS_CFG_STAT_TASK_EN
  #warning 'OS_CFG_STAT_TASK_EN' not enabled
  #endif

  #if !OS_CFG_DBG_EN
  #warning 'OS_CFG_DBG_EN' not enabled
  #endif
#endif

#if defined(SL_CATALOG_FREERTOS_KERNEL_PRESENT)
  #if !configUSE_TRACE_FACILITY
  #warning 'configUSE_TRACE_FACILITY' not enabled
  #endif
#endif
#endif

// Include condition to trace heap usage
#if APP_OS_STAT_HEAP_ENABLED
  #include <stdlib.h>
#if defined(__GNUC__)
  #include <malloc.h>
#elif defined (__ICCARM__)
  #include <iar_dlmalloc.h>
#endif
#endif

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

/// Stack size in bytes
#define APP_OS_THREAD_STACK_SIZE_BYTE  ((APP_OS_STAT_STACK_SIZE_WORD * sizeof(void *)) & 0xFFFFFFF8U)

/// Print prefix for service
#define APP_OS_PRINT_PREFIX           "[APP_OS_STAT]"

/// Print RTT
#define __print_rtt(__format_str, ...)                                           \
  do {                                                                           \
    SEGGER_RTT_LOCK();                                                           \
    SEGGER_RTT_printf(APP_OS_STAT_RTT_LOG_CHANNEL, __format_str, ##__VA_ARGS__); \
    SEGGER_RTT_UNLOCK();                                                         \
  } while (0)

/// App OS Thread stack statistic print format
#if defined(SL_CATALOG_MICRIUMOS_KERNEL_PRESENT)
#define APP_OS_THREAD_STACK_STAT_PRINT_FORMAT \
  "\n" APP_OS_PRINT_PREFIX "[%s] Used/Tot: %lu/%lu"

#elif defined(SL_CATALOG_FREERTOS_KERNEL_PRESENT)
#define APP_OS_THREAD_STACK_STAT_PRINT_FORMAT \
  "\n" APP_OS_PRINT_PREFIX "[%s] Free: %lu"
#endif

/// App OS Heap statistic print format
#define APP_OS_STAT_HEAP_PRINT_FORMAT             \
  "\n" APP_OS_PRINT_PREFIX "[heap]arena    : %lu" \
  "\n" APP_OS_PRINT_PREFIX "[heap]ordblks  : %lu" \
  "\n" APP_OS_PRINT_PREFIX "[heap]smblks   : %lu" \
  "\n" APP_OS_PRINT_PREFIX "[heap]hblks    : %lu" \
  "\n" APP_OS_PRINT_PREFIX "[heap]hblkhd   : %lu" \
  "\n" APP_OS_PRINT_PREFIX "[heap]fsmblks  : %lu" \
  "\n" APP_OS_PRINT_PREFIX "[heap]usmblks  : %lu" \
  "\n" APP_OS_PRINT_PREFIX "[heap]uordblks : %lu" \
  "\n" APP_OS_PRINT_PREFIX "[heap]fordblks : %lu" \
  "\n" APP_OS_PRINT_PREFIX "[heap]keepcost : %lu" \
  "\n" APP_OS_PRINT_PREFIX "[heap]max_used : %lu"

/// App OS memory statistic
typedef struct app_os_stat_mem {
  /// Min free space
  uint32_t min_free;
  /// Max free space
  uint32_t max_free;
  /// Min used space
  uint32_t min_used;
  /// Max used space
  uint32_t max_used;
} app_os_stat_mem_t;

#if APP_OS_STAT_THREAD_STACK_ENABLED
/// App OS thread statistic
typedef struct app_os_stat_thread {
  /// Thread ID
  osThreadId_t id;
  /// Memory statistic
  app_os_stat_mem_t stat;
} app_os_stat_thread_t;
#endif

#if APP_OS_STAT_HEAP_ENABLED
/// App OS heap statistic
typedef struct app_os_stat_heap {
  /// Malloc info
  struct mallinfo minfo;
  /// Memory statistic
  app_os_stat_mem_t stat;
} app_os_stat_heap_t;
#endif
// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

/***************************************************************************//**
 * @brief Service thread function
 * @details Thread function
 * @param[in] args Args (not used)
 ******************************************************************************/
static void _app_os_stat_thr_fnc(void *args);

/***************************************************************************//**
 * @brief Update statistic structure
 * @details Helper function
 * @param[in,out] stat
 * @param[in] free Free space
 * @param[in] used Used space
 ******************************************************************************/
static void _update_stat(app_os_stat_mem_t * const stat,
                         const uint32_t free,
                         const uint32_t used);

#if APP_OS_STAT_THREAD_STACK_ENABLED
/***************************************************************************//**
 * @brief Print thread stack statistic
 * @details Helper function
 * @param[in] thr_id Thread ID ptr
 ******************************************************************************/
static void _print_thread_stack_stat(app_os_stat_thread_t * const thr_stat);
#endif

#if APP_OS_STAT_HEAP_ENABLED
/***************************************************************************//**
 * @brief Print heap statistic
 * @details Helper function
 ******************************************************************************/
static void _print_heap_stat(void);
#endif

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

// Static thread cb allocation
__ALIGNED(8) static uint8_t _thr_cb[osThreadCbSize] = { 0 };

// Static thread stack allocation
__ALIGNED(8) static uint8_t _thr_stack[APP_OS_THREAD_STACK_SIZE_BYTE] = { 0 };

/// Service thread attributes
static const osThreadAttr_t _thr_attr = {
  .name        = "AppOsStatThread",
  .attr_bits   = osThreadDetached,
  .cb_mem      = _thr_cb,
  .cb_size     = sizeof(_thr_cb),
  .stack_mem   = _thr_stack,
  .stack_size  = sizeof(_thr_stack),
  .priority    = APP_OS_STAT_THREAD_PRIO,
  .tz_module   = 0U
};

/// Service Thread ID
static osThreadId_t _thr_id = NULL;

#if APP_OS_STAT_THREAD_STACK_ENABLED
#if APP_OS_STAT_MANUAL_REGISTER_THREADS
/// Mempool to store registered threads
static sl_mempool_t _threads_mempool = { 0U };
#else
static osThreadId_t _thr_id_buff[APP_OS_STAT_MAX_THREAD_CNT] = { NULL };
#endif

/// Buffer of thread stat mempool
static app_os_stat_thread_t _thr_stat_buff[APP_OS_STAT_MAX_THREAD_CNT] = { NULL };
#endif

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

void app_os_stat_init(void)
{
  // Create service thread
  _thr_id = osThreadNew(_app_os_stat_thr_fnc, NULL, &_thr_attr);
  assert(_thr_id != NULL);

#if APP_OS_STAT_THREAD_STACK_ENABLED && APP_OS_STAT_MANUAL_REGISTER_THREADS
  // Create mempool for threads
  sl_status_t stat = SL_STATUS_FAIL;
  stat = sl_mempool_create(&_threads_mempool,
                           APP_OS_STAT_MAX_THREAD_CNT,
                           sizeof(app_os_stat_thread_t),
                           _thr_stat_buff,
                           sizeof(_thr_stat_buff));
  assert(stat == SL_STATUS_OK);
#endif
}

#if APP_OS_STAT_THREAD_STACK_ENABLED && APP_OS_STAT_MANUAL_REGISTER_THREADS
sl_status_t app_os_stat_register_thread(const osThreadId_t thr_id)
{
  app_os_stat_thread_t *tmp_stat = NULL;

  if (thr_id == NULL) {
    return SL_STATUS_FAIL;
  }

  tmp_stat = sl_mempool_alloc(&_threads_mempool);
  if (tmp_stat == NULL) {
    return SL_STATUS_FAIL;
  }

  tmp_stat->id = thr_id;
  tmp_stat->stat.max_free = 0UL;
  tmp_stat->stat.min_free = UINT32_MAX;
  tmp_stat->stat.max_used = 0UL;
  tmp_stat->stat.min_used = UINT32_MAX;

  return SL_STATUS_OK;
}

sl_status_t app_os_stat_remove_thread(const osThreadId_t thr_id)
{
  sl_mempool_block_hnd_t *block   = NULL;
  app_os_stat_thread_t *thr_stat  = NULL;

  block = _threads_mempool.blocks;

  while (block != NULL) {
    thr_stat = (app_os_stat_thread_t *) block->start_addr;
    if (thr_stat->id == thr_id) {
      sl_mempool_free(&_threads_mempool, thr_stat);
      return SL_STATUS_OK;
    }
    block = block->next;
  }
  return SL_STATUS_FAIL;
}
#endif
// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------

static void _app_os_stat_thr_fnc(void *args)
{
  (void) args;

#if APP_OS_STAT_THREAD_STACK_ENABLED
#if APP_OS_STAT_MANUAL_REGISTER_THREADS
  app_os_stat_thread_t *thr_stat  = NULL;
  osThreadId_t current_thr_id     = NULL;
  sl_mempool_block_hnd_t *block   = NULL;

  // register current thread
  current_thr_id = osThreadGetId();
  app_os_stat_register_thread(current_thr_id);
#else
  uint32_t thr_cnt = 0UL;

  // get thread IDs
  thr_cnt = osThreadEnumerate(_thr_id_buff, APP_OS_STAT_MAX_THREAD_CNT);
  // copy thread IDs to statistic storage
  for (uint32_t i = 0UL; i < thr_cnt; ++i) {
    _thr_stat_buff[i].id = _thr_id_buff[i];
  }
#endif
#endif

  while (1) {
    __print_rtt("\n");

// Print thread stack statistic
#if APP_OS_STAT_THREAD_STACK_ENABLED
#if APP_OS_STAT_MANUAL_REGISTER_THREADS
    block = _threads_mempool.blocks;
    while (block != NULL) {
      thr_stat = (app_os_stat_thread_t *) block->start_addr;
      if (thr_stat != NULL) {
        _print_thread_stack_stat(thr_stat);
      }
      block = block->next;
    }
#else
    for (uint32_t i = 0; i < thr_cnt; ++i) {
      _print_thread_stack_stat(&_thr_stat_buff[i]);
    }
#endif
#endif

// Print heap statistic
#if APP_OS_STAT_HEAP_ENABLED
    _print_heap_stat();
#endif

    __print_rtt("\n");
    osDelay(APP_OS_STAT_UPDATE_PERIODE_TIME_MS);
  }
}

static void _update_stat(app_os_stat_mem_t * const stat, const uint32_t free, const uint32_t used)
{
  stat->max_free = stat->max_free < free ? free : stat->max_free;
  stat->min_free = stat->min_free > free ? free : stat->min_free;

  stat->max_used = stat->max_used < used ? used : stat->max_used;
  stat->min_used = stat->min_used > used ? used : stat->min_used;
}

#if APP_OS_STAT_THREAD_STACK_ENABLED
static void _print_thread_stack_stat(app_os_stat_thread_t * const thr_stat)
{
  const char *name     = NULL;
  uint32_t stack_size  = 0UL;
  uint32_t stack_free = 0UL;
  uint32_t stack_used  = 0UL;

  name = osThreadGetName(thr_stat->id);

#if defined(SL_CATALOG_MICRIUMOS_KERNEL_PRESENT)
  stack_size = osThreadGetStackSize(thr_stat->id);
  stack_free = osThreadGetStackSpace(thr_stat->id);
  stack_used = stack_size - stack_free;
#elif defined(SL_CATALOG_FREERTOS_KERNEL_PRESENT)
  (void) stack_size;
  (void) stack_used;
  stack_free = osThreadGetStackSpace(thr_stat->id);
#endif

  // update minimum stack sapce
  _update_stat(&thr_stat->stat, stack_free, stack_used);
#if defined(SL_CATALOG_MICRIUMOS_KERNEL_PRESENT)
  __print_rtt(APP_OS_THREAD_STACK_STAT_PRINT_FORMAT,
              name == NULL ? "N/A" : name, stack_used, stack_size);
#elif defined(SL_CATALOG_FREERTOS_KERNEL_PRESENT)
  __print_rtt(APP_OS_THREAD_STACK_STAT_PRINT_FORMAT,
              name == NULL ? "N/A" : name, stack_free);
#endif
}
#endif

#if APP_OS_STAT_HEAP_ENABLED
static void _print_heap_stat(void)
{
  static app_os_stat_heap_t heap = {
    .minfo = { 0U },
    .stat.max_free = 0UL,
    .stat.min_free = UINT32_MAX,
    .stat.max_used = 0UL,
    .stat.min_used = UINT32_MAX
  };

  // get mallinfo
#if defined (__ICCARM__)
  heap.minfo = __iar_dlmallinfo();
#else
  heap.minfo = mallinfo();
#endif

  // update statistic
  _update_stat(&heap.stat, heap.minfo.fordblks, heap.minfo.uordblks);

  __print_rtt(APP_OS_STAT_HEAP_PRINT_FORMAT,
              heap.minfo.arena,
              heap.minfo.ordblks,
              heap.minfo.smblks,
              heap.minfo.hblks,
              heap.minfo.hblkhd,
              heap.minfo.fsmblks,
              heap.minfo.usmblks,
              heap.minfo.uordblks,
              heap.minfo.fordblks,
              heap.minfo.keepcost,
              heap.stat.max_used);
}
#endif
