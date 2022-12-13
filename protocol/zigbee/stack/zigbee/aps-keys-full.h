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

extern const EmberLibraryStatus emSecurityLinkKeysLibraryStatus;

// These are the bitmask definitions for the token
#define KEY_TABLE_TYPE_LINK_KEY   0x1
#define KEY_TABLE_TYPE_MASTER_KEY 0x0

#define KEY_TABLE_TYPE_MASK                 (BIT(0))
#define KEY_TABLE_AUTHORIZED_KEY_MASK       (BIT(1))

#if !defined(EMBER_MULTI_NETWORK_STRIPPED)
#define emGetKeyEntryNetworkIndex(flags)         \
  (((flags) & KEY_TABLE_TYPE_NETWORK_INDEX_MASK) \
   >>  KEY_TABLE_TYPE_NETWORK_INDEX_OFFSET)
#else
#define emGetKeyEntryNetworkIndex(flags) (0)
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

#define emHaveFreeKeyEntry() \
  (0xFF != emberFindKeyTableEntry(NULL, true))

void emApsSecurityReadFrameCounters(void);

bool emProcessApplicationLinkKey(EmberEUI64 partnerEui64,
                                 bool amInitiator,
                                 EmberKeyData* keyData);

#define emFindLinkKeyEntry(address) \
  emberFindKeyTableEntry((address), true)

#define emAddOrUpdateLinkKeyEntry(address, keyData) \
  emberAddOrUpdateKeyTableEntry((address), true, (keyData))

#define emSetLinkKeyEntry(index, address, keyData) \
  emberSetKeyTableEntry((index), (address), true, (keyData))

#define emSetMasterKeyEntry(index, address, keyData) \
  emberSetKeyTableEntry((index), (address), true, (keyData))

#define emFindMasterKeyEntry(address) \
  emberFindKeyTableEntry((address), false)

EmberStatus emUpdateKeyState(uint8_t index,
                             uint8_t setFlags,
                             uint8_t clearFlags);

#define emUpdateKeyAuthorization(index, keyIsAuthorized)                 \
  emUpdateKeyState((index),                                              \
                   ((keyIsAuthorized)                   /* set flags */  \
                    ? 0                                                  \
                    : KEY_TABLE_UNAUTHORIZED_KEY),                       \
                   ((keyIsAuthorized)                  /* clear flags */ \
                    ? KEY_TABLE_UNAUTHORIZED_KEY                         \
                    : 0))

#define emUpdateKeyNoteEndDevice(index, sleepy)           \
  emUpdateKeyState((index),                               \
                   ((sleepy)            /* set flags */   \
                    ? KEY_TABLE_SLEEPY_END_DEVICE         \
                    : 0),                                 \
                   ((sleepy)            /* clear flags */ \
                    ? 0                                   \
                    : KEY_TABLE_SLEEPY_END_DEVICE))

void emNoteSleepyDeviceInKeyTable(EmberEUI64 eui64, bool sleepy);

#endif // SILABS_APS_KEYS_FULL_H
