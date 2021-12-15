/***************************************************************************//**
 * @file
 * @brief Correlated angle database for asset tags.
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

#include "aoa_corr_angles.h"

// -----------------------------------------------------------------------------
// Default values of configuration parameters.

// Maximum number of incomplete sequence ids.
#define AOA_CORR_ANGLES_MAX_NUM_SEQUENCE_IDS    6

// Maximum sequence range where data does not reset.
#define AOA_CORR_ANGLES_MAX_SEQUENCE_DIFF       20

// -----------------------------------------------------------------------------
// Type definitions.

// Forward declarations
typedef struct aoa_corr_angles_node aoa_corr_angles_node_t;

// Correlated angle node
struct aoa_corr_angles_node{
  aoa_id_t id;
  aoa_corr_angles_t *corr_angles;
  aoa_corr_angles_node_t *next;
};

// -----------------------------------------------------------------------------
// Private function declarations.
static void aoa_corr_angles_remove_old_data(aoa_corr_angles_t *corr_angles_array,
                                            int32_t sequence);
static uint32_t aoa_corr_angles_get_slot_by_sequence(aoa_corr_angles_t *corr_angles_array,
                                                     int32_t sequence);

// -----------------------------------------------------------------------------
// Module variables.

// Linked list head
static aoa_corr_angles_node_t *head_corr_angles = NULL;

// Configuration
aoa_corr_angles_config_t aoa_corr_angles_config = {
  0,
  AOA_CORR_ANGLES_MAX_NUM_SEQUENCE_IDS,
  AOA_CORR_ANGLES_MAX_SEQUENCE_DIFF
};

// -----------------------------------------------------------------------------
// Public function definitions.

/**************************************************************************//**
 * Adds a correlated angle to the list.
 *****************************************************************************/
sl_status_t aoa_corr_angles_new(aoa_id_t id,
                                aoa_corr_angles_t **corr_angles)
{
  aoa_corr_angles_node_t *new = (aoa_corr_angles_node_t *)malloc(sizeof(aoa_corr_angles_node_t));
  if (NULL == new) {
    return SL_STATUS_ALLOCATION_FAILED;
  }

  new->corr_angles = (aoa_corr_angles_t *)malloc(aoa_corr_angles_config.sequence_id_slots * sizeof(aoa_corr_angles_t));
  if (NULL == new->corr_angles) {
    return SL_STATUS_ALLOCATION_FAILED;
  }

  // Initialize the angle structures
  for (uint32_t i = 0; i < aoa_corr_angles_config.sequence_id_slots; i++) {
    new->corr_angles[i].angles = (aoa_angle_t *)malloc(aoa_corr_angles_config.locator_count * sizeof(aoa_angle_t));
    new->corr_angles[i].has_angle = (bool *)malloc(aoa_corr_angles_config.locator_count * sizeof(bool));
    new->corr_angles[i].sequence = -1;
    new->corr_angles[i].num_angles = 0;

    if ((NULL == new->corr_angles[i].angles) || (NULL == new->corr_angles[i].has_angle)) {
      return SL_STATUS_ALLOCATION_FAILED;
    }
  }

  aoa_id_copy(new->id, id);
  new->next = head_corr_angles;
  head_corr_angles = new;
  *corr_angles = new->corr_angles;

  return SL_STATUS_OK;
}

/**************************************************************************//**
 * Returns an entry from the database by its ID.
 *****************************************************************************/
sl_status_t aoa_corr_angles_get_by_id(aoa_id_t id,
                                      aoa_corr_angles_t **corr_angles)
{
  aoa_corr_angles_node_t *current = head_corr_angles;

  if (NULL == head_corr_angles) {
    return SL_STATUS_NOT_FOUND;
  }

  while (NULL != current) {
    if (0 == aoa_id_compare(current->id, id)) {
      *corr_angles = current->corr_angles;
      return SL_STATUS_OK;
    }
    current = current->next;
  }

  return SL_STATUS_NOT_FOUND;
}

/**************************************************************************//**
 * Adds data to the slot.
 *****************************************************************************/
sl_status_t aoa_corr_angles_add_data(aoa_corr_angles_t *corr_angles_array,
                                     uint32_t locator_id,
                                     aoa_angle_t *angle,
                                     uint32_t *angle_slot)
{
  uint32_t slot = 0;

  // Drop stored data that are considered too old
  aoa_corr_angles_remove_old_data(corr_angles_array, angle->sequence);

  // Find the correct correlated angle slot
  slot = aoa_corr_angles_get_slot_by_sequence(corr_angles_array, angle->sequence);

  if (slot > aoa_corr_angles_config.sequence_id_slots) {
    return SL_STATUS_FAIL;
  }

  // Insert the slot if it is not present yet.
  if (corr_angles_array[slot].sequence != angle->sequence) {
    for (int i = aoa_corr_angles_config.sequence_id_slots - 1; i > slot; i--) {
      corr_angles_array[i].sequence = corr_angles_array[i - 1].sequence;
      corr_angles_array[i].num_angles = corr_angles_array[i - 1].num_angles;
      memcpy(corr_angles_array[i].angles, corr_angles_array[i - 1].angles, aoa_corr_angles_config.locator_count * sizeof(aoa_angle_t));
      memcpy(corr_angles_array[i].has_angle, corr_angles_array[i - 1].has_angle, aoa_corr_angles_config.locator_count * sizeof(bool));
    }
    corr_angles_array[slot].num_angles = 0;
    memset(corr_angles_array[slot].has_angle, 0, aoa_corr_angles_config.locator_count);
    corr_angles_array[slot].sequence = angle->sequence;
  }
  memcpy(&corr_angles_array[slot].angles[locator_id], angle, sizeof(aoa_angle_t));
  corr_angles_array[slot].has_angle[locator_id] = true;
  corr_angles_array[slot].num_angles++;

  *angle_slot = slot;

  return SL_STATUS_OK;
}

/**************************************************************************//**
 * Cleans up already processed data.
 *****************************************************************************/
sl_status_t aoa_corr_angles_cleanup(aoa_corr_angles_t *corr_angles_array,
                                    uint32_t cleanup_start_idx)
{
  if (cleanup_start_idx > aoa_corr_angles_config.sequence_id_slots) {
    return SL_STATUS_FAIL;
  }

  for (; cleanup_start_idx < aoa_corr_angles_config.sequence_id_slots; cleanup_start_idx++) {
    corr_angles_array[cleanup_start_idx].num_angles = 0;
    corr_angles_array[cleanup_start_idx].sequence = -1;
    memset(corr_angles_array[cleanup_start_idx].has_angle, 0, aoa_corr_angles_config.locator_count);
  }

  return SL_STATUS_OK;
}

/**************************************************************************//**
 * Destroys the database and all of its entries.
 *****************************************************************************/
void aoa_corr_angles_destroy(void)
{
  aoa_corr_angles_node_t *current;
  aoa_corr_angles_node_t *next;

  for (current = head_corr_angles; current != NULL; current = next) {
    next = current->next;
    free(current->corr_angles->angles);
    free(current->corr_angles->has_angle);
    free(current->corr_angles);
    free(current);
  }

  head_corr_angles = NULL;
}

// -----------------------------------------------------------------------------
// Private function definitions.

/**************************************************************************//**
 * Removes old angles.
 *****************************************************************************/
static void aoa_corr_angles_remove_old_data(aoa_corr_angles_t *corr_angles_array,
                                            int32_t sequence)
{
  for (uint32_t i = 0; i < aoa_corr_angles_config.sequence_id_slots; i++) {
    if (aoa_sequence_compare(corr_angles_array[i].sequence, sequence) > aoa_corr_angles_config.max_sequence_diff) {
      for (uint32_t k = i; k < aoa_corr_angles_config.sequence_id_slots; k++) {
        corr_angles_array[k].num_angles = 0;
        corr_angles_array[k].sequence = -1;
        memset(corr_angles_array[k].has_angle, 0, aoa_corr_angles_config.locator_count);
      }
      return;
    }
  }
}

/**************************************************************************//**
 * Returns an angle slot by the sequence number.
 *****************************************************************************/
static uint32_t aoa_corr_angles_get_slot_by_sequence(aoa_corr_angles_t *corr_angles_array,
                                                     int32_t sequence)
{
  for (uint32_t i = 0; i < aoa_corr_angles_config.sequence_id_slots; i++) {
    if (sequence == corr_angles_array[i].sequence) {
      return i;
    }
  }
  return 0;
}
