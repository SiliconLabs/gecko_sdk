/***************************************************************************//**
 * @brief Extern declaration of user-configurable global variables
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef __EMBER_CONFIGURATION__
#define __EMBER_CONFIGURATION__

#include <stdint.h>

// Configurable stack parameters.
extern uint8_t emberMacAckTimeoutMS;
extern int8_t emRadioCcaThreshold;
extern int16_t emberDefaultTxPowerDeciDbm;

extern uint16_t emberFrequencyHoppingSeed;
extern uint16_t emberFrequencyHoppingStartChannel;
extern uint16_t emberFrequencyHoppingEndChannel;
extern uint16_t emberFrequencyHoppingChannelDurationMs;
extern uint16_t emberFrequencyHoppingChannelGuardDurationMs;
extern uint16_t emberFrequencyHoppingServerFreqInfoBroadcastPeriodS;
extern uint16_t emberFrequencyHoppingSleepyClientResyncPeriodS;
extern uint16_t emberFrequencyHoppingAlwaysOnClientSyncTimeoutS;
extern uint8_t  emberFrequencyHoppingServerAdvertisingIterationCount;

extern uint8_t emberMacOutgoingQueueSize;
extern EmOutgoingPacket *emMacOutgoingQueue;

extern uint32_t emberChildTimeoutSec;
extern uint8_t emberChildTableSize;
extern EmberChildEntry *emChildTable;

extern uint8_t emberIndirectPacketQueueSize;
extern EmOutgoingPacket *emIndirectPacketQueue;
extern EmberMacAddress *emIndirectQueueSourceAddresses;
extern uint32_t *emIndirectQueueTimeouts;
extern uint32_t emberMacIndirectTimeoutMs;

extern uint16_t emberCoordinatorFirstShortIdToBeAssigned;

#endif // __EMBER_CONFIGURATION__
