/***************************************************************************//**
 * @file
 * @brief ESL AP Library - Memory management implementation
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

#include <stdio.h>
#include "sl_slist.h"
#include "esl_lib_memory.h"
#include "esl_lib_log.h"

// -----------------------------------------------------------------------------
// Definitions

#define LOG_MODULE "MEM"

// Memory allocation list item type
typedef struct {
  sl_slist_node_t node;
  void            *ptr;
  size_t          size;
  uint32_t        line;
  char            *file;
} malloc_list_item_t;

// -----------------------------------------------------------------------------
// Forward declaration of private functions

static malloc_list_item_t *find_item(void *ptr);

// -----------------------------------------------------------------------------
// Private variables

// List head
static sl_slist_node_t *list = NULL;

// -----------------------------------------------------------------------------
// Public functions

void *_esl_lib_malloc(size_t size, const char *file, uint32_t line)
{
  // Allocate memory for data
  void *data = malloc(size);
  // Allocate memory for the list item
  malloc_list_item_t *item = (malloc_list_item_t *)malloc(sizeof(malloc_list_item_t));

  // Check for pointers
  if (data != NULL && item != NULL) {
    // Assign pointer and metadata
    item->ptr  = data;
    item->size = size;
    item->line = line;
    item->file = (char *)file;
    // Push it to the list
    sl_slist_push(&list, &item->node);
    // Return pointer to the allocated memory
    return data;
  }

  return NULL;
}
void _esl_lib_free(void *ptr, const char *file, uint32_t line)
{
  // Find item
  malloc_list_item_t *item = find_item(ptr);
  // Check if the item was found
  if (item != NULL) {
    // Remove from the list
    sl_slist_remove(&list, &item->node);
    // Free storage
    free(ptr);
    // Free list item
    free(item);
  }
}

size_t esl_lib_memory_get_size(void)
{
  malloc_list_item_t *item = NULL;
  uint32_t size = 0;
  // Iterate over the list
  SL_SLIST_FOR_EACH_ENTRY(list, item, malloc_list_item_t, node) {
    size += item->size;
  }
  return size;
}

uint32_t esl_lib_memory_get_count(void)
{
  malloc_list_item_t *item = NULL;
  size_t count = 0;
  // Iterate over the list
  SL_SLIST_FOR_EACH_ENTRY(list, item, malloc_list_item_t, node) {
    count++;
  }
  return count;
}

void esl_lib_memory_log(void)
{
  malloc_list_item_t *item = NULL;
  uint32_t count = 0;
  size_t size = 0;
  esl_lib_log_debug(LOG_MODULE, "---------------------------------------------");
  // Check for empty list
  if (list == NULL) {
    esl_lib_log_debug(LOG_MODULE, " Empty list.");
  }
  // Iterate and print items
  SL_SLIST_FOR_EACH_ENTRY(list, item, malloc_list_item_t, node) {
    esl_lib_log_debug(LOG_MODULE, "%8p Size = %zu allocated in %s:%u" APP_LOG_NL,
                      item->ptr,
                      item->size,
                      item->file,
                      item->line);
    count++;
    size += item->size;
  }
  // Summarize results
  esl_lib_log_debug(LOG_MODULE, "---------------------------------------------");
  esl_lib_log_debug(LOG_MODULE, " Count = %u Size = %zu", count, size);
  esl_lib_log_debug(LOG_MODULE, "---------------------------------------------");
}

// -----------------------------------------------------------------------------
// Private functions

static malloc_list_item_t *find_item(void *ptr)
{
  malloc_list_item_t *item = NULL;
  // Iterate over the list
  SL_SLIST_FOR_EACH_ENTRY(list, item, malloc_list_item_t, node) {
    if (item->ptr == ptr) {
      // Found the requested pointer
      return item;
    }
  }
  // Requested pointer not found
  return NULL;
}
