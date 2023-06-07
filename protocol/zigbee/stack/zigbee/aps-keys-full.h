/***************************************************************************//**
 * @file
 * @brief Header for the additional key functionality that is
 * necessary for a full Zigbee Pro stack.
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

#ifndef SILABS_APS_KEYS_FULL_H
#define SILABS_APS_KEYS_FULL_H

#include "include/ember.h"

extern const EmberLibraryStatus sli_zigbee_security_link_keys_library_status;

// These are the bitmask definitions for the token
#define KEY_TABLE_TYPE_LINK_KEY   0x1
#define KEY_TABLE_TYPE_MASTER_KEY 0x0

#define KEY_TABLE_TYPE_MASK                 (BIT(0))
#define KEY_TABLE_AUTHORIZED_KEY_MASK       (BIT(1))

#if !defined(EMBER_MULTI_NETWORK_STRIPPED)
#define sli_zigbee_get_key_entry_network_index(flags) \
  (((flags) & KEY_TABLE_TYPE_NETWORK_INDEX_MASK)      \
   >>  KEY_TABLE_TYPE_NETWORK_INDEX_OFFSET)
#else
#define sli_zigbee_get_key_entry_network_index(flags) (0)
#endif // !defined(EMBER_MULTI_NETWORK_STRIPPED)

// We use negative logic since the token bits are zero by default, and we
// must handle software upgrades of deployed devices.
#define KEY_TABLE_UNAUTHORIZED_KEY   0x02
// This bit defaults to 0 in the token, which is either "router" or "don't know".
// Upgrades of existing devices will not have recorded this data and therefore
// can't rely on it.  The intent of this bit is to know when it is absolutely
// unnecessary to send a key update to the device since it won't get it.
#define KEY_TABLE_SLEEPY_END_DEVICE         (BIT(2))

// We added the network index in the bitmask for the key token. If you need
// to add new bits here, add it starting from the end of the byte so that we
// can support potential increase of the maximum number of networks (which
// is capped to 8 right now for the link key entries).
#define KEY_TABLE_TYPE_NETWORK_INDEX_MASK   (BIT(3) | BIT(4) | BIT(5))
#define KEY_TABLE_TYPE_NETWORK_INDEX_OFFSET 3

// If this is set, it means the token's key field does not house the key itself,
// but instead the first four bytes hold the PSA key index saved in high-to-low
// byte order
#define KEY_TABLE_ENTRY_HAS_PSA_ID          (BIT(6))

// This bit indicates if entry in the key table is a Symmetric Passphrase
#define KEY_TABLE_SYMMETRIC_PASSPHRASE      (BIT(7))

void sli_zigbee_aps_security_read_frame_counters(void);

bool sli_zigbee_process_application_link_key(EmberEUI64 partnerEui64,
                                             bool amInitiator,
                                             EmberKeyData* keyData);

EmberStatus sli_zigbee_update_key_state(uint8_t index,
                                        uint8_t setFlags,
                                        uint8_t clearFlags);

#define sli_zigbee_update_key_authorization(index, keyIsAuthorized)      \
  sli_zigbee_update_key_state((index),                                   \
                              ((keyIsAuthorized)        /* set flags */  \
                               ? 0                                       \
                               : KEY_TABLE_UNAUTHORIZED_KEY),            \
                              ((keyIsAuthorized)       /* clear flags */ \
                               ? KEY_TABLE_UNAUTHORIZED_KEY              \
                               : 0))

#define sli_zigbee_update_key_note_end_device(index, sleepy) \
  sli_zigbee_update_key_state((index),                       \
                              ((sleepy) /* set flags */      \
                               ? KEY_TABLE_SLEEPY_END_DEVICE \
                               : 0),                         \
                              ((sleepy) /* clear flags */    \
                               ? 0                           \
                               : KEY_TABLE_SLEEPY_END_DEVICE))

void sli_zigbee_note_sleepy_device_in_key_table(EmberEUI64 eui64, bool sleepy);

#endif // SILABS_APS_KEYS_FULL_H
