/*
 *  Copyright (c) 2018, The OpenThread Authors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 *   This file defines the radio counters updated by the efr32 PAL.
 *
 */

#ifndef RADIO_COUNTERS_H_
#define RADIO_COUNTERS_H_
typedef struct efr32RadioCounters
{
    uint32_t mRailPlatTxTriggered;
    uint32_t mRailPlatRadioReceiveDoneCbCount;
    uint32_t mRailPlatRadioReceiveProcessedCount;
    uint32_t mRailPlatRadioEnergyScanDoneCbCount;
    uint32_t mRailPlatRadioTxDoneCbCount;
    uint32_t mRailTxStarted;
    uint32_t mRailTxStartFailed;
    uint32_t mRailEventAcksReceived;
    uint32_t mRailEventConfigScheduled;
    uint32_t mRailEventConfigUnScheduled;
    uint32_t mRailEventPacketSent;
    uint32_t mRailEventChannelBusy;
    uint32_t mRailEventEnergyScanCompleted;
    uint32_t mRailEventCalNeeded;
    uint32_t mRailEventPacketReceived;
    uint32_t mRailEventNoAck;
    uint32_t mRailEventTxAbort;
    uint32_t mRailEventSchedulerStatusError;
    uint32_t mRailEventsSchedulerStatusTransmitBusy;
    uint32_t mRailEventsSchedulerStatusLastStatus;
    uint32_t mRailEventsEnhAckTxFailed;
    uint32_t mRailEventsScheduledTxTriggeredCount;
    uint32_t mRailEventsScheduledTxStartedCount;
    union { 
        // Allow for reuse / overloading of fields for various debugging
        uint32_t m32;
        uint16_t m16[2];
        uint8_t  m8[4]; // see defines below for suggested subfield usage
    } mRadioDebugData;
} efr32RadioCounters;

// Offsets for use with Radio Debug Data subfields
enum
{
    RX_DEBUG_COUNTER0 = 0,
    RX_DEBUG_COUNTER1,
    TX_DEBUG_COUNTER0,
    TX_DEBUG_COUNTER1
};
#endif // RADIO_COUNTERS_H_
