/***************************************************************************//**
 * @file
 * @brief ESL Command List manipulation.
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
#include <stdlib.h>
#include "esl_lib_command_list.h"
#include "esl_lib_memory.h"

// -----------------------------------------------------------------------------
// Private variables

// Command counter
static uint32_t list_id = 0;

// -----------------------------------------------------------------------------
// Public function definitions

sl_status_t esl_lib_command_list_remove(sl_slist_node_t            **list,
                                        esl_lib_command_list_cmd_t *cmd)
{
  sl_status_t sc = SL_STATUS_OK;
  if (cmd == NULL) {
    sc = SL_STATUS_NULL_POINTER;
  } else {
    // Remove and free up list item
    if (list != NULL && *list != NULL) {
      sl_slist_remove(list, &cmd->node);
    }
    esl_lib_memory_free(cmd);
  }
  return sc;
}

esl_lib_command_list_cmd_t *esl_lib_command_list_get(sl_slist_node_t **list)
{
  return (esl_lib_command_list_cmd_t *)sl_slist_pop(list);
}

sl_status_t esl_lib_command_list_put(sl_slist_node_t            **list,
                                     esl_lib_command_list_cmd_t *cmd)
{
  sl_status_t sc = SL_STATUS_OK;
  if (cmd == NULL) {
    sc = SL_STATUS_NULL_POINTER;
  } else {
    cmd->id = list_id++;
    // Add the new item to the command list
    sl_slist_push_back(list, &cmd->node);
  }
  return sc;
}

void esl_lib_command_list_cleanup(sl_slist_node_t **list)
{
  esl_lib_command_list_cmd_t *cmd;
  if (list != NULL) {
    if (*list != NULL) {
      while ((cmd = (esl_lib_command_list_cmd_t *)sl_slist_pop(list)) != NULL) {
        sl_slist_remove(list, &cmd->node);
        esl_lib_memory_free(cmd);
      }
      *list = NULL;
    }
  }
}
