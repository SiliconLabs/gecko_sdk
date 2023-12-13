/***************************************************************************//**
 * @file
 * @brief Stub implementation of additional key functionality that is
 * necessary for a Full Zigbee Pro Stack.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include PLATFORM_HEADER
#include "stack/include/ember-types.h"
#include "stack/include/library.h"

const EmberLibraryStatus sli_zigbee_security_link_keys_library_status = EMBER_LIBRARY_IS_STUB;

void sli_zigbee_aps_security_read_frame_counters(void)
{
}

EmberStatus sli_zigbee_get_key_table_entry(uint8_t index, EmberKeyStruct *result)
{
  (void)index;
  (void)result;
  return EMBER_LIBRARY_NOT_PRESENT;
}

uint8_t emberFindKeyTableEntry(EmberEUI64 address, bool linkKey)
{
  (void)address;
  (void)linkKey;
  return 0xFF;
}

EmberStatus sli_zigbee_af_set_key_table_entry(bool erase,
                                              uint8_t index,
                                              EmberKeyStruct* keyStruct)
{
  (void)erase;
  (void)index;
  (void)keyStruct;
  return EMBER_LIBRARY_NOT_PRESENT;
}

EmberStatus emberEraseKeyTableEntry(uint8_t index)
{
  (void)index;
  return EMBER_LIBRARY_NOT_PRESENT;
}

bool sli_zigbee_process_application_link_key(EmberEUI64 partnerEui64,
                                             bool amInitiator,
                                             EmberKeyData* keyData)
{
  (void)partnerEui64;
  (void)amInitiator;
  (void)keyData;
  return false;
}

EmberStatus sli_zigbee_update_key_state(uint8_t index,
                                        uint8_t setFlags,
                                        uint8_t clearFlags)
{
  (void)index;
  (void)setFlags;
  (void)clearFlags;
  return EMBER_LIBRARY_NOT_PRESENT;
}

void sli_zigbee_note_sleepy_device_in_key_table(EmberEUI64 eui64, bool sleepy)
{
  (void)eui64;
  (void)sleepy;
}

EmberStatus emberClearKeyTable(void)
{
  return EMBER_LIBRARY_NOT_PRESENT;
}

uint8_t sli_zigbee_find_key_table_entry(EmberEUI64 address, bool linkKey, uint8_t bitmask)
{
  return 0xFF;
}
