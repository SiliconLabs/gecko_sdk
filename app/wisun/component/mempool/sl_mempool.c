/***************************************************************************//**
 * @file
 * @brief Memory Pool
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
//                                   Includes
// -----------------------------------------------------------------------------

#include "em_common.h"
#include "sl_mempool.h"
#include "sl_component_catalog.h"

#if defined(SL_CATALOG_FREERTOS_KERNEL_PRESENT)
// FreeRTOS
  #include "FreeRTOS.h"
#else
// MicriumOS and bare-metal
  #include "sl_malloc.h"
#endif

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief Init block handler
 * @details Helper function
 * @param[out] block Block handler pointer
 *****************************************************************************/
static inline void _init_block(sl_mempool_block_hnd_t * const block);

/**************************************************************************//**
 * @brief Allocate block handler
 * @details Helper function
 * @return sl_mempool_block_hnd_t* Block handler pointer on succes
 *                                 or NULL on error
 *****************************************************************************/
static sl_mempool_block_hnd_t *_alloc_block_hnd(void);

/**************************************************************************//**
 * @brief Free block handler
 * @details Helper function
 * @param[in] block_hnd Block handler ptr
 *****************************************************************************/
static void _free_block_hnd(sl_mempool_block_hnd_t * block_hnd);

/**************************************************************************//**
 * @brief Get block handler by address
 * @details Helper function
 * @param[in] addr Address
 * @param[in] memp Memory Pool object
 * @return sl_mempool_block_hnd_t* Block handler pointer on succes
 *                                 or NULL on error
 *****************************************************************************/
static sl_mempool_block_hnd_t *_get_block_hnd_by_addr(const void * const addr,
                                                      const sl_mempool_t * const memp);

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

sl_status_t sl_mempool_create(sl_mempool_t *memp,
                              const size_t block_count,
                              const size_t block_size,
                              void * const buff,
                              const size_t buff_size)
{
  // Check arguments
  if (memp == NULL
      || buff == NULL
      || !buff_size
      || (block_count * block_size) > buff_size
      || (block_count * block_size) == 0) {
    return SL_STATUS_FAIL;
  }

  memp->block_count = block_count;
  memp->block_size = block_size;
  memp->buff = buff;
  memp->buff_size = buff_size;
  memp->blocks = NULL;
  memp->used_block_count = 0;

  return SL_STATUS_OK;
}

void * sl_mempool_alloc(sl_mempool_t * const memp)
{
  void * tmp_addr = NULL;
  sl_mempool_block_hnd_t *tmp_block = NULL;

  if (memp == NULL) {
    return NULL;
  }

  // block list is full
  if (memp->used_block_count == memp->block_count) {
    return NULL;
  }

  for (size_t i = 0; i < memp->block_count; ++i) {
    tmp_addr = (void *)((uint8_t *)memp->buff + (i * memp->block_size));
    // find free address of the buffer
    if (_get_block_hnd_by_addr(tmp_addr, memp) != NULL) {
      continue;
    }
    tmp_block = memp->blocks;
    memp->blocks = _alloc_block_hnd();
    if (memp->blocks == NULL) {
      memp->blocks = tmp_block;
      return NULL;
    }

    _init_block(memp->blocks);

    // init new block handler
    memp->blocks->start_addr = tmp_addr;
    memp->blocks->next = tmp_block;
    ++memp->used_block_count;

    return memp->blocks->start_addr;
  }

  return NULL;
}

void sl_mempool_free(sl_mempool_t * const memp, const void * const addr)
{
  sl_mempool_block_hnd_t *block = NULL;
  sl_mempool_block_hnd_t *prev_block = NULL;

  block = memp->blocks;
  prev_block = block;

  while (block != NULL) {
    if (block->start_addr == addr) {
      // remove block
      prev_block->next = block->next;

      if (block == memp->blocks) {
        memp->blocks = block->next;
      }

      _free_block_hnd(block);

      --memp->used_block_count;
      break;
    }
    prev_block = block;
    block = block->next;
  }
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------

static inline void _init_block(sl_mempool_block_hnd_t * const block)
{
  block->next = NULL;
  block->start_addr = NULL;
}

static sl_mempool_block_hnd_t *_alloc_block_hnd(void)
{
#if defined(SL_CATALOG_FREERTOS_KERNEL_PRESENT)
  // FreeRTOS
  return (sl_mempool_block_hnd_t *) pvPortMalloc(sizeof(sl_mempool_block_hnd_t));
#else
  // MicriumOS
  return (sl_mempool_block_hnd_t *) sl_malloc(sizeof(sl_mempool_block_hnd_t));
#endif
}

static void _free_block_hnd(sl_mempool_block_hnd_t * block_hnd)
{
#if defined(SL_CATALOG_FREERTOS_KERNEL_PRESENT)
  // FreeRTOS
  vPortFree(block_hnd);
#else
  // MicriumOS
  sl_free(block_hnd);
#endif
}

static sl_mempool_block_hnd_t * _get_block_hnd_by_addr(const void * const addr,
                                                       const sl_mempool_t * const memp)
{
  sl_mempool_block_hnd_t *block = NULL;

  block = memp->blocks;

  while (block != NULL) {
    if (addr == block->start_addr) {
      return block;
    }
    block = block->next;
  }

  return NULL;
}
