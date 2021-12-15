/***************************************************************************//**
 * @file
 * @brief CTE Handle module for AoA locator
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

#include <stdio.h>
#include <stdlib.h>
#include "aoa_cte.h"
#include "system.h"
#include "aoa_cte_config.h"
#include "aoa_board.h"

// -----------------------------------------------------------------------------
// Module variables.

// Current CTE mode.
static aoa_cte_type_t cte_mode = AOA_CTE_DEFAULT_MODE;

aoa_cte_config_t aoa_cte_config = {
  AOA_CTE_SAMPLING_INTERVAL,
  AOA_CTE_MIN_LENGTH,
  AOA_CTE_COUNT,
  AOA_CTE_SLOT_DURATION
};

// -----------------------------------------------------------------------------
// Public function definitions.

/**************************************************************************//**
 * Initializes the module.
 *****************************************************************************/
void aoa_cte_init(void)
{
  uint8_t antenna_array[AOA_NUM_ARRAY_ELEMENTS] = SWITCHING_PATTERN;
  aoa_cte_config.switching_pattern = malloc(AOA_NUM_ARRAY_ELEMENTS * sizeof(uint8_t));
  memcpy(aoa_cte_config.switching_pattern, antenna_array, sizeof(antenna_array));
  aoa_cte_config.switching_pattern_length = AOA_NUM_ARRAY_ELEMENTS;
}

/**************************************************************************//**
 * Handles the bluetooth event.
 *****************************************************************************/
sl_status_t aoa_cte_bt_on_event(sl_bt_msg_t *evt)
{
  sl_status_t sc = SL_STATUS_OK;
  switch (cte_mode) {
    case AOA_CTE_TYPE_SILABS:
      sc = cte_bt_on_event_silabs(evt);
      break;
    case AOA_CTE_TYPE_CONN_LESS:
      sc = cte_bt_on_event_conn_less(evt);
      break;
    case AOA_CTE_TYPE_CONN:
      sc = cte_bt_on_event_conn(evt);
      break;
    default:
      break;
  }

  return sc;
}

/**************************************************************************//**
 * Sets the CTE Mode.
 *****************************************************************************/
sl_status_t aoa_cte_set_mode(aoa_cte_type_t mode)
{
  if (mode >= AOA_CTE_TYPE_COUNT) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  cte_mode = mode;
  return SL_STATUS_OK;
}

/**************************************************************************//**
 * Returns the CTE Mode.
 *****************************************************************************/
aoa_cte_type_t aoa_cte_get_mode(void)
{
  return cte_mode;
}

/**************************************************************************//**
 * Callback to notify the application on new iq report.
 *****************************************************************************/
SL_WEAK void aoa_cte_on_iq_report(aoa_db_entry_t *tag,
                                  aoa_iq_report_t *iq_report)
{
  // Implement in the application.
}
