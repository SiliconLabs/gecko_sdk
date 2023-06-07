/***************************************************************************//**
 * @file
 * @brief ESL Event List manipulation header.
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

#ifndef ESL_LIB_EVENT_LIST_H
#define ESL_LIB_EVENT_LIST_H

#include <stdint.h>
#include "sl_status.h"
#include "sl_slist.h"
#include "esl_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

/// ESL Library event structure
typedef struct esl_lib_evt_s {
  sl_slist_node_t                         node;                        ///< List node pointer
  esl_lib_evt_type_t                      evt_code;                    ///< Event code
  uint32_t                                id;                          ///< Event ID, used by library
  esl_lib_evt_data_t                      data;                        ///< Event data
} esl_lib_evt_t;

// -----------------------------------------------------------------------------
// Public functions

/**************************************************************************//**
 * Remove first event from list if exists and free up allocated memory.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_event_list_remove_first(void);

/**************************************************************************//**
 * Get the pointer of the first event in event list.
 *
 * @return Event instance pointer.
 *****************************************************************************/
esl_lib_evt_t *esl_lib_event_list_get_first(void);

/**************************************************************************//**
 * Add new element to the end of the list that contains event data.
 * @param[in] evt Pointer to event data to be pushed.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_event_list_push_back(esl_lib_evt_t *evt);

/**************************************************************************//**
 * Add new element to the end of the list that contains event data.
 * @param[in] event_type      Event type.
 * @param[in] additional_size Size in addition to the event header.
 * @param[in] ptr_out         Output event pointer.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_event_list_allocate(esl_lib_evt_type_t event_type,
                                        uint32_t           additional_size,
                                        esl_lib_evt_t      **ptr_out);

/**************************************************************************//**
 * Add new element to the end of the list that contains event data.
 * @param[in] lib_status Library status.
 * @param[in] node_id    Related node ID.
 * @param[in] status     Error status code.
 * @param[in] data       Additional data parameter.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_event_push_error(esl_lib_status_t      lib_status,
                                     esl_lib_node_id_t     *node_id,
                                     sl_status_t           status,
                                     esl_lib_status_data_t data);

#ifdef __cplusplus
};
#endif

#endif // ESL_LIB_EVENT_LIST_H
