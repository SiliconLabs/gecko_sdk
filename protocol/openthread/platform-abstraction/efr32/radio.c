/*
 *  Copyright (c) 2023, The OpenThread Authors.
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
 *   This file implements the OpenThread platform abstraction for radio communication.
 *
 */

#include <assert.h>
#include <openthread-core-config.h>
#include <openthread-system.h>
#include <openthread/link.h>
#include <openthread/platform/alarm-micro.h>
#include <openthread/platform/alarm-milli.h>
#include <openthread/platform/diag.h>
#include <openthread/platform/radio.h>
#include <openthread/platform/time.h>

#include "common/debug.hpp"
#include "common/logging.hpp"
#include "utils/code_utils.h"
#include "utils/link_metrics.h"
#include "utils/mac_frame.h"

#include "board_config.h"
#include "em_core.h"
#include "em_system.h"
#include "ieee802154mac.h"
#include "pa_conversions_efr32.h"
#include "platform-band.h"
#include "platform-efr32.h"
#include "rail.h"
#include "rail_config.h"
#include "rail_ieee802154.h"
#include "sl_packet_utils.h"
#include "soft_source_match_table.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT

#ifdef SL_CATALOG_RAIL_MULTIPLEXER_PRESENT
#include "sl_rail_mux_rename.h"
#endif

#ifdef SL_CATALOG_RAIL_UTIL_ANT_DIV_PRESENT
#include "sl_rail_util_ant_div.h"
#include "sl_rail_util_ant_div_config.h"
#endif // SL_CATALOG_RAIL_UTIL_ANT_DIV_PRESENT

#ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
#include "coexistence-802154.h"
#endif // SL_CATALOG_RAIL_UTIL_COEX_PRESENT

#ifdef SL_CATALOG_RAIL_UTIL_IEEE802154_STACK_EVENT_PRESENT
#include "sl_rail_util_ieee802154_stack_event.h"
#endif // SL_CATALOG_RAIL_UTIL_IEEE802154_STACK_EVENT_PRESENT

#ifdef SL_CATALOG_RAIL_UTIL_IEEE802154_PHY_SELECT_PRESENT
#include "sl_rail_util_ieee802154_phy_select.h"
#endif // #ifdef SL_CATALOG_RAIL_UTIL_IEEE802154_PHY_SELECT_PRESENT

#ifdef SL_CATALOG_OT_RCP_GP_INTERFACE_PRESENT
#include "sl_rcp_gp_interface.h"
#endif

#ifdef SL_CATALOG_RAIL_UTIL_IEEE802154_FAST_CHANNEL_SWITCHING_PRESENT
#include "sl_rail_util_ieee802154_fast_channel_switching_config.h"
#endif // SL_CATALOG_RAIL_UTIL_IEEE802154_FAST_CHANNEL_SWITCHING_PRESENT

//------------------------------------------------------------------------------
// Enums, macros and static variables

#ifndef LOW_BYTE
#define LOW_BYTE(n) ((uint8_t)((n)&0xFF))
#endif // LOW_BTE

#ifndef HIGH_BYTE
#define HIGH_BYTE(n) ((uint8_t)(LOW_BYTE((n) >> 8)))
#endif // HIGH_BYTE

// Intentionally maintaining separate groups for series-1 and series-2 devices
// This gives flexibility to add new elements to be read, like CCA Thresholds.
#if defined(_SILICON_LABS_32B_SERIES_1)
#define USERDATA_MFG_CUSTOM_EUI_64 (2)
#elif defined(_SILICON_LABS_32B_SERIES_2)
#define USERDATA_MFG_CUSTOM_EUI_64 (2)
#else
#error "UNSUPPORTED DEVICE"
#endif

#ifndef USERDATA_END
#define USERDATA_END (USERDATA_BASE + FLASH_PAGE_SIZE)
#endif

#define EFR32_RECEIVE_SENSITIVITY -100   // dBm
#define EFR32_RSSI_AVERAGING_TIME 16     // us
#define EFR32_RSSI_AVERAGING_TIMEOUT 300 // us

// Internal flags
#define FLAG_RADIO_INIT_DONE 0x00000001
#define FLAG_ONGOING_TX_DATA 0x00000002
#define FLAG_ONGOING_TX_ACK 0x00000004
#define FLAG_WAITING_FOR_ACK 0x00000008
#define FLAG_CURRENT_TX_USE_CSMA 0x00000010
#define FLAG_SCHEDULED_RX_PENDING 0x00000020

// Radio Events
#define EVENT_TX_SUCCESS 0x00000100
#define EVENT_TX_CCA_FAILED 0x00000200
#define EVENT_TX_NO_ACK 0x00000400
#define EVENT_TX_SCHEDULER_ERROR 0x00000800
#define EVENT_TX_FAILED 0x00001000
#define EVENT_ACK_SENT_WITH_FP_SET 0x00002000
#define EVENT_SECURED_ACK_SENT 0x00004000
#define EVENT_SCHEDULED_RX_STARTED 0x00008000

#define TX_WAITING_FOR_ACK 0x00
#define TX_NO_ACK 0x01

#define ONGOING_TX_FLAGS (FLAG_ONGOING_TX_DATA | FLAG_ONGOING_TX_ACK)
#define RADIO_TX_EVENTS  (EVENT_TX_SUCCESS | EVENT_TX_CCA_FAILED | EVENT_TX_NO_ACK | EVENT_TX_SCHEDULER_ERROR | EVENT_TX_FAILED)

#define QUARTER_DBM_IN_DBM 4
#define US_IN_MS 1000

/* FilterMask provided by RAIL is structured as follows:
 * |  Bit:7  |  Bit:6  |  Bit:5  |    Bit:4    |  Bit:3  |  Bit:2  |  Bit:1  |    Bit:0     |
 * |  Addr2  |  Addr1  |  Addr0  |  Bcast Addr | Pan Id2 | Pan Id1 | Pan Id0 | Bcast PanId  |
 * | Matched | Matched | Matched |   Matched   | Matched | Matched | Matched |   Matched    |
 */

#define RADIO_BCAST_IID (0)
#define RADIO_GET_FILTER_MASK(iid) (1 << (iid))
#define RADIO_PANID_FILTER_SHIFT (0)
#define RADIO_ADDR_FILTER_SHIFT (4)

#define RADIO_BCAST_PANID_FILTER_MASK RADIO_GET_FILTER_MASK(0)
#define RADIO_INDEX0_PANID_FILTER_MASK RADIO_GET_FILTER_MASK(1)
#define RADIO_INDEX1_PANID_FILTER_MASK RADIO_GET_FILTER_MASK(2)
#define RADIO_INDEX2_PANID_FILTER_MASK RADIO_GET_FILTER_MASK(3)

#define RADIO_GET_PANID_FILTER_MASK(filter) \
    (filter & (RADIO_BCAST_PANID_FILTER_MASK  | \
               RADIO_INDEX0_PANID_FILTER_MASK | \
               RADIO_INDEX1_PANID_FILTER_MASK | \
               RADIO_INDEX2_PANID_FILTER_MASK))

#define RADIO_BCAST_ADDR_FILTER_MASK (RADIO_GET_FILTER_MASK(0) << RADIO_ADDR_FILTER_SHIFT)
#define RADIO_INDEX0_ADDR_FILTER_MASK (RADIO_GET_FILTER_MASK(1) << RADIO_ADDR_FILTER_SHIFT)
#define RADIO_INDEX1_ADDR_FILTER_MASK (RADIO_GET_FILTER_MASK(2) << RADIO_ADDR_FILTER_SHIFT)
#define RADIO_INDEX2_ADDR_FILTER_MASK (RADIO_GET_FILTER_MASK(3) << RADIO_ADDR_FILTER_SHIFT)

#define RADIO_GET_ADDR_FILTER_MASK(filter) \
    (filter & (RADIO_BCAST_ADDR_FILTER_MASK  | \
               RADIO_INDEX0_ADDR_FILTER_MASK | \
               RADIO_INDEX1_ADDR_FILTER_MASK | \
               RADIO_INDEX2_ADDR_FILTER_MASK))

#define RADIO_BCAST_PANID (0xFFFF)
#define INVALID_VALUE (0xFF)

#if defined(_SILICON_LABS_32B_SERIES_1)
#define DEVICE_CAPABILITY_MCU_EN (1)
#else
#define DEVICE_CAPABILITY_MCU_EN (DEVINFO->SWCAPA1 & _DEVINFO_SWCAPA1_RFMCUEN_MASK)
#endif

static otRadioCaps sRadioCapabilities = (OT_RADIO_CAPS_ACK_TIMEOUT
                                         | OT_RADIO_CAPS_CSMA_BACKOFF
                                         | OT_RADIO_CAPS_ENERGY_SCAN
                                         | OT_RADIO_CAPS_SLEEP_TO_TX
#if (OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2)
                                         | OT_RADIO_CAPS_TRANSMIT_SEC
    // When scheduled tx is required, we support RAIL_StartScheduledCcaCsmaTx
    // (delay is indicated in tx frame info set in MAC)
                                         | OT_RADIO_CAPS_TRANSMIT_TIMING
    // When scheduled rx is required, we support RAIL_ScheduleRx in our
    // implementation of otPlatRadioReceiveAt
                                         | OT_RADIO_CAPS_RECEIVE_TIMING
#endif
                                        );

// Energy Scan
typedef enum
{
    ENERGY_SCAN_STATUS_IDLE,
    ENERGY_SCAN_STATUS_IN_PROGRESS,
    ENERGY_SCAN_STATUS_COMPLETED
} energyScanStatus;

typedef enum
{
    ENERGY_SCAN_MODE_SYNC,
    ENERGY_SCAN_MODE_ASYNC
} energyScanMode;

typedef struct
{
    uint8_t     length;
    uint8_t     channel;
    uint8_t     lqi;
    int8_t      rssi;
    uint8_t     iid;
    uint32_t    timestamp;
} rxPacketDetails;

typedef struct 
{
    rxPacketDetails packetInfo;
    uint8_t         psdu[IEEE802154_MAX_LENGTH];
} rxBuffer;

typedef uint8_t rxBufferIndex_t;

static volatile energyScanStatus sEnergyScanStatus;
static volatile int8_t           sEnergyScanResultDbm;
static energyScanMode            sEnergyScanMode;

static bool sIsSrcMatchEnabled = false;

#if OPENTHREAD_RADIO && OPENTHREAD_CONFIG_MULTIPAN_RCP_ENABLE == 1
#define RADIO_INTERFACE_COUNT 4
#define RADIO_EXT_ADDR_COUNT (RADIO_INTERFACE_COUNT - 1)
#else
#define RADIO_INTERFACE_COUNT 1
#define RADIO_EXT_ADDR_COUNT (RADIO_INTERFACE_COUNT)
#endif

#if RADIO_CONFIG_2P4GHZ_OQPSK_SUPPORT
#define SL_CHANNEL_MAX OT_RADIO_2P4GHZ_OQPSK_CHANNEL_MAX
#define SL_CHANNEL_MIN OT_RADIO_2P4GHZ_OQPSK_CHANNEL_MIN
#define SL_MAX_CHANNELS_SUPPORTED ((OT_RADIO_2P4GHZ_OQPSK_CHANNEL_MAX - OT_RADIO_2P4GHZ_OQPSK_CHANNEL_MIN) + 1)
#elif RADIO_CONFIG_SUBGHZ_SUPPORT
#define SL_CHANNEL_MAX OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MAX
#define SL_CHANNEL_MIN OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MIN
#define SL_MAX_CHANNELS_SUPPORTED                                 \
    ((OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MAX    \
      - OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MIN) \
     + 1)

#elif RADIO_CONFIG_915MHZ_OQPSK_SUPPORT // Not supported
#define SL_CHANNEL_MAX OT_RADIO_915MHZ_OQPSK_CHANNEL_MAX
#define SL_CHANNEL_MIN OT_RADIO_915MHZ_OQPSK_CHANNEL_MIN
#define SL_MAX_CHANNELS_SUPPORTED ((OT_RADIO_915MHZ_OQPSK_CHANNEL_MAX - OT_RADIO_915MHZ_OQPSK_CHANNEL_MIN) + 1)
#endif

#define SL_INVALID_TX_POWER (127)

// Receive
static rxBuffer          sReceivePacket[SL_OPENTHREAD_RADIO_RX_BUFFER_COUNT];
static uint8_t           sReceiveAckPsdu[IEEE802154_MAX_LENGTH];
static otRadioFrame      sReceiveFrame;
static otRadioFrame      sReceiveAckFrame;
static otError           sReceiveError;

// Transmit
static otRadioFrame  sTransmitFrame;
static uint8_t       sTransmitPsdu[IEEE802154_MAX_LENGTH];
static otRadioFrame *sTxFrame = NULL;
static uint8_t       sLastLqi = 0;
static int8_t        sLastRssi = 0;
static otExtAddress  sExtAddress[RADIO_EXT_ADDR_COUNT];

static int8_t sMaxChannelPower[RADIO_INTERFACE_COUNT][SL_MAX_CHANNELS_SUPPORTED];
static int8_t sDefaultTxPower[RADIO_INTERFACE_COUNT];

// CSMA config: Should be globally scoped
RAIL_CsmaConfig_t csmaConfig = RAIL_CSMA_CONFIG_802_15_4_2003_2p4_GHz_OQPSK_CSMA;
RAIL_CsmaConfig_t cslCsmaConfig = RAIL_CSMA_CONFIG_SINGLE_CCA;

#if OPENTHREAD_CONFIG_MAC_HEADER_IE_SUPPORT
static otRadioIeInfo sTransmitIeInfo;
#endif

// Radio
#define CCA_THRESHOLD_UNINIT 127
#define CCA_THRESHOLD_DEFAULT -75 // dBm  - default for 2.4GHz 802.15.4

#define UNINITIALIZED_CHANNEL 0xFF

static bool              sPromiscuous = false;
static efr32CommonConfig sCommonConfig;
static efr32BandConfig   sBandConfig;
static efr32BandConfig  *sCurrentBandConfig = NULL;

static int8_t sCcaThresholdDbm = CCA_THRESHOLD_DEFAULT;

#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
efr32RadioCounters railDebugCounters;

// Create an alias for readability of RX debug tracking
#define rxDebugStep (railDebugCounters.mRadioDebugData.m8[RX_DEBUG_COUNTER0])
#endif

#if OPENTHREAD_RADIO && OPENTHREAD_CONFIG_MULTIPAN_RCP_ENABLE == 1
extern uint8_t otNcpPlatGetCurCommandIid(void);
static uint8_t sRailFilterMask = RADIO_BCAST_PANID_FILTER_MASK;

#if SL_RAIL_UTIL_IEEE802154_FAST_CHANNEL_SWITCHING_ENABLED

#define FAST_CHANNEL_SWITCHING_SUPPORT 1
static RAIL_IEEE802154_RxChannelSwitchingCfg_t sChannelSwitchingCfg;
static RAIL_IEEE802154_RX_CHANNEL_SWITCHING_BUF_ALIGNMENT_TYPE
    sChannelSwitchingBuffer[RAIL_IEEE802154_RX_CHANNEL_SWITCHING_BUF_BYTES
                            / RAIL_IEEE802154_RX_CHANNEL_SWITCHING_BUF_ALIGNMENT];

static bool isMultiChannel(void)
{
    uint8_t firstChannel = UNINITIALIZED_CHANNEL;
    for (uint8_t i = 0U; i < RAIL_IEEE802154_RX_CHANNEL_SWITCHING_NUM_CHANNELS; i++)
    {
        if (sChannelSwitchingCfg.channels[i] != UNINITIALIZED_CHANNEL)
        {
            if (firstChannel == UNINITIALIZED_CHANNEL)
            {
                firstChannel = sChannelSwitchingCfg.channels[i];
            }
            else if (firstChannel != sChannelSwitchingCfg.channels[i])
            {
                return true;
            }
        }
    }
    return false;
}

static uint8_t fastChannelIndex(uint8_t aChannel)
{
    for (uint8_t i = 0U; i < RAIL_IEEE802154_RX_CHANNEL_SWITCHING_NUM_CHANNELS; i++)
    {
        if (sChannelSwitchingCfg.channels[i] == aChannel)
        {
            return i;
        }
    }
    return INVALID_VALUE;
}

#endif // SL_RAIL_UTIL_IEEE802154_FAST_CHANNEL_SWITCHING_ENABLED

#else // OPENTHREAD_RADIO && OPENTHREAD_CONFIG_MULTIPAN_RCP_ENABLE == 1
#define otNcpPlatGetCurCommandIid() 0
#endif // OPENTHREAD_RADIO && OPENTHREAD_CONFIG_MULTIPAN_RCP_ENABLE == 1

// RAIL

#ifdef SL_CATALOG_RAIL_MULTIPLEXER_PRESENT
RAIL_Handle_t gRailHandle;
#if SL_OPENTHREAD_COEX_COUNTER_ENABLE
static void sl_ot_coex_counter_on_event(sl_rail_util_coex_event_t event);
#endif // SL_OPENTHREAD_COEX_COUNTER_ENABLE
#else
RAIL_Handle_t emPhyRailHandle;
#endif // SL_CATALOG_RAIL_MULTIPLEXER_PRESENT

static const RAIL_IEEE802154_Config_t sRailIeee802154Config = {
    .addresses = NULL,
    .ackConfig =
        {
            .enable     = true,
            .ackTimeout = 672,
            .rxTransitions =
                {
                    .success = RAIL_RF_STATE_RX,
                    .error   = RAIL_RF_STATE_RX,
                },
            .txTransitions =
                {
                    .success = RAIL_RF_STATE_RX,
                    .error   = RAIL_RF_STATE_RX,
                },
        },
    .timings =
        {
            .idleToRx = 100,
            .txToRx   = 192 - 10,
            .idleToTx = 100,
#if OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2
            .rxToTx = 256, // accommodate enhanced ACKs
#else
            .rxToTx = 192,
#endif
            .rxSearchTimeout     = 0,
            .txToRxSearchTimeout = 0,
            .txToTx              = 0,
        },
    .framesMask                        = RAIL_IEEE802154_ACCEPT_STANDARD_FRAMES,
    .promiscuousMode                   = false,
    .isPanCoordinator                  = false,
    .defaultFramePendingInOutgoingAcks = false,
};

#if RADIO_CONFIG_SUBGHZ_SUPPORT
#define PHY_HEADER_SIZE 2
// SHR: 4 bytes preamble, 2 bytes SFD
// 802.15.4 spec describes GFSK SHR to be the same format as SUN O-QPSK
// except preamble is 32 symbols (4 octets).
#define SHR_SIZE 6
#else
#define PHY_HEADER_SIZE 1
#define SHR_SIZE 5 // 4 bytes of preamble, 1 byte sync-word
#endif

#define SHR_DURATION_US 160 // Duration of SHR in us.

// Misc
static volatile uint32_t miscRadioState = 0;
static bool              emPendingData  = false;

#ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
enum
{
    RHO_INACTIVE = 0,
    RHO_EXT_ACTIVE,
    RHO_INT_ACTIVE, // Not used
    RHO_BOTH_ACTIVE,
};

static uint8_t rhoActive = RHO_INACTIVE;
static bool    ptaGntEventReported;
static bool    sRadioCoexEnabled = true;

#if SL_OPENTHREAD_COEX_COUNTER_ENABLE
uint32_t efr32RadioCoexCounters[SL_RAIL_UTIL_COEX_EVENT_COUNT] = {0};
#endif // SL_OPENTHREAD_COEX_COUNTER_ENABLE

#endif // SL_CATALOG_RAIL_UTIL_COEX_PRESENT

/**
 * This function gets the lowest value for the maxTxPower for a channel, from the maxTxPowerTable set
 * across all interfaces. It also gets the highest defaultTxPower set across all interfaces.
 *
 * @param[out]  defaultTxPower   A pointer to update the derived defaultTxPower across all IIDs.
 * @param[out]  txPowerFromTable A pointer to update the Tx Power derived from the MaxChannelPowerTable.
 *
 */
static void sli_get_default_and_max_powers_across_iids(int8_t  *defaultTxPower,
                                                       int8_t  *txPowerFromTable,
                                                       uint16_t channel)
{
    OT_ASSERT(txPowerFromTable != NULL);
    OT_ASSERT(defaultTxPower != NULL);

    for (uint8_t iid = 0U; iid < RADIO_INTERFACE_COUNT; iid++)
    {
        // Obtain the minimum Tx power set by different iids, for `channel`
        // If there is an interface using lower Tx power than the one we have
        // in txPowerFromTable..
        // Update txPowerFromTable.
        *txPowerFromTable = SL_MIN(*txPowerFromTable, sMaxChannelPower[iid][channel - SL_CHANNEL_MIN]);

        // If the default Tx Power set is not invalid..
        if (sDefaultTxPower[iid] != SL_INVALID_TX_POWER)
        {
            // Obtain the Max value between local defaultTxPower and sDefaultTxPower.
            // If selected default Tx Power is Invalid, initialise it to sDefaultTxPower.
            // We have already validated that sDefaultTxPower holds a valid value.
            *defaultTxPower = (*defaultTxPower == SL_INVALID_TX_POWER) ? sDefaultTxPower[iid]
                                                                       : SL_MAX(*defaultTxPower, sDefaultTxPower[iid]);
        }
    }
}

static int8_t sli_get_max_tx_power_across_iids(void)
{
    int8_t   maxChannelTxPower = SL_INVALID_TX_POWER;
    int8_t   maxDefaultTxPower = SL_INVALID_TX_POWER;
    int8_t   selectedTxPower   = SL_INVALID_TX_POWER;
    uint16_t channel;

#if FAST_CHANNEL_SWITCHING_SUPPORT
    if (isMultiChannel())
    {
        // Find the maxChannelTxPower, to be minimum of Max channel power for the
        // channels infast channel config, accross all iids. This is because, if a iid_1
        // sets the max tx power of the channel to be less than the max tx power set by
        // iid_2, we will need to work with the lower tx power to be compliant on both
        // interfaces.

        // Find the maxDefaultTxPower, to be maximum of the default Tx power accross all
        // the interfaces.

        for (uint8_t i = 0U; i < RAIL_IEEE802154_RX_CHANNEL_SWITCHING_NUM_CHANNELS; i++)
        {
            // Get the channel stored in sChannelSwitchingCfg
            channel = sChannelSwitchingCfg.channels[i];

            sli_get_default_and_max_powers_across_iids(&maxDefaultTxPower, &maxChannelTxPower, channel);
        }
    }
    else
#endif
    {
        RAIL_GetChannel(gRailHandle, &channel);
        sli_get_default_and_max_powers_across_iids(&maxDefaultTxPower, &maxChannelTxPower, channel);
    }

    // Return the minimum of maxChannelTxPower and maxDefaultTxPower.
    selectedTxPower = SL_MIN(maxChannelTxPower, maxDefaultTxPower);
    return (selectedTxPower == SL_INVALID_TX_POWER) ? OPENTHREAD_CONFIG_DEFAULT_TRANSMIT_POWER : selectedTxPower;
}

//------------------------------------------------------------------------------
// RX Buffer management

static volatile bool sRxBufferFull = false; // Used to distinguish full vs empty circular buffer state

static inline bool isRxBufferFull(void)
{
    return sRxBufferFull;
}

#if SL_OPENTHREAD_RADIO_RX_BUFFER_COUNT > 1

#define CIRCULAR_BUFFER_INCR(index) ((index) = ((index) + 1) % (SL_OPENTHREAD_RADIO_RX_BUFFER_COUNT))

static volatile rxBufferIndex_t sRxBufferHead = 0; // Index of available buffer for use by producer callback
static rxBufferIndex_t sRxBufferTail = 0; // Index of next buffer to consume by processing loop

static inline bool isRxBufferEmpty(void)
{
    CORE_DECLARE_IRQ_STATE;
    CORE_ENTER_ATOMIC();
    bool isEmpty = ((sRxBufferHead == sRxBufferTail) && (!isRxBufferFull()));
    CORE_EXIT_ATOMIC();
    return isEmpty;
}

/* Return index of next available buffer, or return the buffer count if no buffers are available */
static inline rxBufferIndex_t getFreeBufferIndex(void)
{
    return (isRxBufferFull()) ? SL_OPENTHREAD_RADIO_RX_BUFFER_COUNT : sRxBufferHead;
}

/* Return index of next buffer to process, or return the buffer count if no buffers can be processed */
static inline rxBufferIndex_t getStoredBufferIndex(void)
{
    return (isRxBufferEmpty()) ? SL_OPENTHREAD_RADIO_RX_BUFFER_COUNT : sRxBufferTail;
}

/* Helper function to determine if a buffer is marked as ready to process */
static inline bool canProcessNextRxBuffer(void)
{
    return (!isRxBufferEmpty());
}

/* Marks the state of the next available buffer as ready to process */
static inline void reserveNextRxBuffer(void)
{
    CIRCULAR_BUFFER_INCR(sRxBufferHead);
    sRxBufferFull = (sRxBufferHead == sRxBufferTail);
}

/* Updates the buffer at the provided index as available after being processed */
static inline void releaseCurrentRxBuffer(void)
{
    CORE_DECLARE_IRQ_STATE;
    CORE_ENTER_ATOMIC();
    CIRCULAR_BUFFER_INCR(sRxBufferTail);
    sRxBufferFull = false;
    CORE_EXIT_ATOMIC();
}
#endif
#if RADIO_CONFIG_ENABLE_CUSTOM_EUI_SUPPORT
/*
 * This API reads the UserData page on the given EFR device.
 */
static int readUserData(void *buffer, uint16_t index, int len, bool changeByteOrder)
{
    uint8_t *readLocation  = (uint8_t *)USERDATA_BASE + index;
    uint8_t *writeLocation = (uint8_t *)buffer;

    // Sanity check to verify if the ouput buffer is valid and the index and len are valid.
    // If invalid, change the len to -1 and return.
    otEXPECT_ACTION((writeLocation != NULL) && ((readLocation + len) <= (uint8_t *)USERDATA_END), len = -1);

    // Copy the contents of flash into output buffer.

    for (int idx = 0; idx < len; idx++)
    {
        if (changeByteOrder)
        {
            writeLocation[idx] = readLocation[(len - 1) - idx];
        }
        else
        {
            writeLocation[idx] = readLocation[idx];
        }
    }

exit:
    // Return len, len was changed to -1 to indicate failure.
    return len;
}
#endif

/*
 * This API converts the FilterMask to appropriate IID. If there are any errors, it will fallback on bcast IID.
 *
 */
static inline uint8_t getIidFromFilterMask(uint8_t mask)
{
    uint8_t iid = INVALID_VALUE;

#if OPENTHREAD_RADIO && OPENTHREAD_CONFIG_MULTIPAN_RCP_ENABLE == 1
    // We need only the Pan Id masks here, as we are not matching the addresses.
    // Also mask all the unused indices.
    mask &= sRailFilterMask;

    // The only acceptable values for mask at this point are:
    // 1 - BCAST PANID   - IID(0)
    // 2 - INDEX 0       - IID(1)
    // 4 - INDEX 1       - IID(2)
    // 8 - INDEX 2       - IID(3)
    //
    // The packet should either be directed to one of the PANs or Bcast.
    // (mask & (mask -1) is a simplistic way of testing if the mask is a power of 2.
    otEXPECT_ACTION(((mask != 0) && (mask & (mask - 1)) == 0), iid = 0);

    while (mask)
    {
        iid++;
        mask >>= 1;
    }

exit:
#else
    (void)mask;
    iid = RADIO_BCAST_IID;
#endif
    return iid;
}

/*
 * This API validates the received FilterMask by checking if the destination address
 * in the received packet corresponds to destination PanID.
 */
static bool isFilterMaskValid(uint8_t mask)
{
    bool valid = false;

#if OPENTHREAD_RADIO && OPENTHREAD_CONFIG_MULTIPAN_RCP_ENABLE == 1

    /* Packet will be considered as a valid packet in 3 cases:
     * Case 1: If the packet was directed towards bcast address or bcast panid
     *
     * Case 2: If the packet was directed to one of our valid address/PANID combos
     *         (Compare all non-bcast PANID filters against their corresponding
     *          address filters for same IID and see if any match)
     *
     * Case 3: We don't have either the destination addressing field or destination PanId
     *         in the received packet to determine if the dest address and dest pan match.
     */
    if( ((mask & RADIO_BCAST_PANID_FILTER_MASK) ||
         (mask & RADIO_BCAST_ADDR_FILTER_MASK)) ||    //Case 1
        // Find any non-broadcast PAN ID match and get ready to compare it
        ((((mask & (RADIO_INDEX0_PANID_FILTER_MASK |
                   RADIO_INDEX1_PANID_FILTER_MASK |
                   RADIO_INDEX2_PANID_FILTER_MASK)) >> RADIO_PANID_FILTER_SHIFT) &
        // ...To see if it coincides with any address matches for same IID
         (RADIO_GET_ADDR_FILTER_MASK(mask) >> RADIO_ADDR_FILTER_SHIFT)) != 0) || //Case 2
        (((RADIO_GET_PANID_FILTER_MASK(mask)) == 0) ||
         ((RADIO_GET_ADDR_FILTER_MASK(mask)) == 0))   //Case 3
    )
    {
        valid = true;
    }
#else
    (void)mask;
    valid    = true;
#endif

    return valid;
}

/*
 * RAIL accepts 3 pan indices 0, 1 or 2. But valid IIDs are 1, 2 and 3 (0 is reserved for bcast).
 * This API validates the passed IID and converts it into usable PanIndex.
 */

static inline uint8_t getPanIndexFromIid(uint8_t iid)
{
    uint8_t panIndex = 0;

#if OPENTHREAD_RADIO && OPENTHREAD_CONFIG_MULTIPAN_RCP_ENABLE == 1
    otEXPECT_ACTION(((iid < RADIO_INTERFACE_COUNT) && (iid != 0)), panIndex = INVALID_VALUE);
    panIndex = iid - 1;
exit:
#else
    panIndex = iid;
#endif
    return panIndex;
}

#if (OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2)

enum
{
    MAC_KEY_PREV,
    MAC_KEY_CURRENT,
    MAC_KEY_NEXT,
    MAC_KEY_COUNT
};

typedef struct securityMaterial
{
    uint8_t             ackKeyId;
    uint8_t             keyId;
    uint32_t            macFrameCounter;
    uint32_t            ackFrameCounter;
    otMacKeyMaterial    keys[MAC_KEY_COUNT];
} securityMaterial;

// Transmit Security
static securityMaterial sMacKeys[RADIO_INTERFACE_COUNT];

#if OPENTHREAD_CONFIG_MAC_CSL_RECEIVER_ENABLE

// CSL parameters
static uint32_t sCslPeriod;
static uint32_t sCslSampleTime;

static uint16_t getCslPhase(uint32_t shrTxTime)
{
    uint32_t cslPeriodInUs = sCslPeriod * OT_US_PER_TEN_SYMBOLS;
    uint32_t diff;

    if (shrTxTime == 0U)
    {
        shrTxTime = otPlatAlarmMicroGetNow();
    }

    diff = ((sCslSampleTime % cslPeriodInUs) - (shrTxTime % cslPeriodInUs) + cslPeriodInUs) % cslPeriodInUs;

    return (uint16_t)(diff / OT_US_PER_TEN_SYMBOLS);
}
#endif // OPENTHREAD_CONFIG_MAC_CSL_RECEIVER_ENABLE

// Enhanced ACK IE data
static uint8_t sAckIeData[OT_ACK_IE_MAX_SIZE];
static uint8_t sAckIeDataLength = 0;

static uint8_t generateAckIeData(uint8_t *aLinkMetricsIeData, uint8_t aLinkMetricsIeDataLen)
{
    OT_UNUSED_VARIABLE(aLinkMetricsIeData);
    OT_UNUSED_VARIABLE(aLinkMetricsIeDataLen);

    uint8_t offset = 0;

#if OPENTHREAD_CONFIG_MAC_CSL_RECEIVER_ENABLE
    if (sCslPeriod > 0)
    {
        offset += otMacFrameGenerateCslIeTemplate(sAckIeData);
    }
#endif

#if OPENTHREAD_CONFIG_MLE_LINK_METRICS_SUBJECT_ENABLE
    if (aLinkMetricsIeData != NULL && aLinkMetricsIeDataLen > 0)
    {
        offset += otMacFrameGenerateEnhAckProbingIe(sAckIeData, aLinkMetricsIeData, aLinkMetricsIeDataLen);
    }
#endif

    return offset;
}

static otError radioProcessTransmitSecurity(otRadioFrame *aFrame, uint8_t iid)
{
    otError error = OT_ERROR_NONE;
    uint8_t keyId;
    uint8_t keyToUse;
    uint8_t panIndex = getPanIndexFromIid(iid);

    otEXPECT(otMacFrameIsSecurityEnabled(aFrame) && otMacFrameIsKeyIdMode1(aFrame)
             && !aFrame->mInfo.mTxInfo.mIsSecurityProcessed);

    OT_ASSERT(panIndex != INVALID_VALUE);

    if (otMacFrameIsAck(aFrame))
    {
        keyId = otMacFrameGetKeyId(aFrame);

        otEXPECT_ACTION(keyId != 0, error = OT_ERROR_FAILED);

        if (keyId == sMacKeys[iid].keyId - 1)
        {
            keyToUse = MAC_KEY_PREV;
        }
        else if (keyId == sMacKeys[iid].keyId)
        {
            keyToUse = MAC_KEY_CURRENT;
        }
        else if (keyId == sMacKeys[iid].keyId + 1)
        {
            keyToUse = MAC_KEY_NEXT;
        }
        else
        {
            error = OT_ERROR_SECURITY;
            otEXPECT(false);
        }
    }
    else
    {
        keyId    = sMacKeys[iid].keyId;
        keyToUse = MAC_KEY_CURRENT;
    }

    aFrame->mInfo.mTxInfo.mAesKey = &sMacKeys[iid].keys[keyToUse];

    if (!aFrame->mInfo.mTxInfo.mIsHeaderUpdated)
    {
        if (otMacFrameIsAck(aFrame))
        {
            // Store ack frame counter and ack key ID for receive frame
            sMacKeys[iid].ackKeyId        = keyId;
            sMacKeys[iid].ackFrameCounter = sMacKeys[iid].macFrameCounter;
        }

        otMacFrameSetKeyId(aFrame, keyId);
        otMacFrameSetFrameCounter(aFrame, sMacKeys[iid].macFrameCounter++);
    }

#if defined(_SILICON_LABS_32B_SERIES_2)
    efr32PlatProcessTransmitAesCcm(aFrame, &sExtAddress[panIndex]);
#else
    otMacFrameProcessTransmitAesCcm(aFrame, &sExtAddress[panIndex]);
#endif

exit:
    return error;
}
#endif // (OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2)

static uint8_t readInitialPacketData(RAIL_RxPacketInfo_t *packetInfo,
                                     uint8_t              expected_data_bytes_max,
                                     uint8_t              expected_data_bytes_min,
                                     uint8_t             *buffer,
                                     uint8_t              buffer_len)
{
    uint8_t packetBytesRead = 0;

    // Check if we have enough buffer
    OT_ASSERT((buffer_len >= expected_data_bytes_max) || (packetInfo != NULL));

    // Read the packet info
    RAIL_GetRxIncomingPacketInfo(gRailHandle, packetInfo);

    // We are trying to get the packet info of a packet before it is completely received.
    // We do this to evaluate the FP bit in response and add IEs to ACK if needed.
    // Check to see if we have received atleast minimum number of bytes requested.
    otEXPECT_ACTION(packetInfo->packetBytes >= expected_data_bytes_min, packetBytesRead = 0);

    // Only extract what we care about
    if (packetInfo->packetBytes > expected_data_bytes_max)
    {
        packetInfo->packetBytes = expected_data_bytes_max;
        // Check if the initial portion of the packet received so far exceeds the max value requested.
        if (packetInfo->firstPortionBytes >= expected_data_bytes_max)
        {
            // If we have received more, make sure to copy only the required bytes into the buffer.
            packetInfo->firstPortionBytes = expected_data_bytes_max;
            packetInfo->lastPortionData   = NULL;
        }
    }

    // Copy number of bytes as indicated in `packetInfo->firstPortionBytes` into the buffer.
    RAIL_CopyRxPacket(buffer, packetInfo);
    packetBytesRead = packetInfo->packetBytes;

exit:
    return packetBytesRead;
}

//------------------------------------------------------------------------------
// Forward Declarations

static void RAILCb_Generic(RAIL_Handle_t aRailHandle, RAIL_Events_t aEvents);

static void efr32PhyStackInit(void);

#if OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2
static void updateIeInfoTxFrame(uint32_t shrTxTime);
#endif

#ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
static void efr32CoexInit(void);
// Try to transmit the current outgoing frame subject to MAC-level PTA
static void tryTxCurrentPacket(void);
#else
// Transmit the current outgoing frame.
void        txCurrentPacket(void);
#define tryTxCurrentPacket txCurrentPacket
#endif // SL_CATALOG_RAIL_UTIL_COEX_PRESENT

static void txFailedCallback(bool isAck, uint32_t status);

static bool validatePacketDetails(RAIL_RxPacketHandle_t   packetHandle,
                                  RAIL_RxPacketDetails_t *pPacketDetails,
                                  RAIL_RxPacketInfo_t    *pPacketInfo,
                                  uint16_t               *packetLength);
static bool validatePacketTimestamp(RAIL_RxPacketDetails_t *pPacketDetails, uint16_t packetLength);
static void updateRxFrameDetails(RAIL_RxPacketDetails_t *pPacketDetails,
                                 bool securedOutgoingEnhancedAck,
                                 bool framePendingSetInOutgoingAck,
                                 uint8_t iid,
                                 uint8_t aReceiveBufferInUse);

static otError skipRxPacketLengthBytes(RAIL_RxPacketInfo_t *pPacketInfo);

//------------------------------------------------------------------------------
// Helper Functions

#ifdef SL_CATALOG_RAIL_UTIL_IEEE802154_STACK_EVENT_PRESENT

static bool phyStackEventIsEnabled(void)
{
    bool result = false;

#if (defined(SL_CATALOG_RAIL_UTIL_ANT_DIV_PRESENT) && SL_RAIL_UTIL_ANT_DIV_RX_RUNTIME_PHY_SELECT)
    result = true;
#endif // SL_CATALOG_RAIL_UTIL_ANT_DIV_PRESENT

#ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
    if (sRadioCoexEnabled)
    {
        result |= sl_rail_util_coex_is_enabled();
#ifdef SL_RAIL_UTIL_COEX_RUNTIME_PHY_SELECT
        result |= SL_RAIL_UTIL_COEX_RUNTIME_PHY_SELECT;
#endif
    }
#endif // SL_CATALOG_RAIL_UTIL_COEX_PRESENT

    return result;
}

static RAIL_Events_t currentEventConfig = RAIL_EVENTS_NONE;
static void          updateEvents(RAIL_Events_t mask, RAIL_Events_t values)
{
    RAIL_Status_t status;
    RAIL_Events_t newEventConfig = (currentEventConfig & ~mask) | (values & mask);
    if (newEventConfig != currentEventConfig)
    {
        currentEventConfig = newEventConfig;
        status             = RAIL_ConfigEvents(gRailHandle, mask, values);
        OT_ASSERT(status == RAIL_STATUS_NO_ERROR);
    }
}

static sl_rail_util_ieee802154_stack_event_t handlePhyStackEvent(sl_rail_util_ieee802154_stack_event_t stackEvent,
                                                                 uint32_t                              supplement)
{
    return (phyStackEventIsEnabled()
#ifdef SL_CATALOG_RAIL_MULTIPLEXER_PRESENT
                ? sl_rail_mux_ieee802154_on_event(gRailHandle, stackEvent, supplement)
#else
                ? sl_rail_util_ieee802154_on_event(stackEvent, supplement)
#endif
                : 0);
}
#else
static void updateEvents(RAIL_Events_t mask, RAIL_Events_t values)
{
    RAIL_Status_t status;
    status = RAIL_ConfigEvents(gRailHandle, mask, values);
    OT_ASSERT(status == RAIL_STATUS_NO_ERROR);
}

#define handlePhyStackEvent(event, supplement) 0
#endif // SL_CATALOG_RAIL_UTIL_IEEE802154_STACK_EVENT_PRESENT

// Set or clear the passed flag.
static inline void setInternalFlag(uint16_t flag, bool val)
{
    CORE_DECLARE_IRQ_STATE;
    CORE_ENTER_ATOMIC();
    miscRadioState = (val ? (miscRadioState | flag) : (miscRadioState & ~flag));
    CORE_EXIT_ATOMIC();
}
// Returns true if the passed flag is set, false otherwise.
static inline bool getInternalFlag(uint16_t flag)
{
    return ((miscRadioState & flag) != 0);
}

static inline bool txWaitingForAck(void)
{
    return (getInternalFlag(FLAG_ONGOING_TX_DATA) && ((sTransmitFrame.mPsdu[0] & IEEE802154_FRAME_FLAG_ACK_REQUIRED) != 0));
}

static bool txIsDataRequest(void)
{
    uint16_t fcf = sTransmitFrame.mPsdu[IEEE802154_FCF_OFFSET] | (sTransmitFrame.mPsdu[IEEE802154_FCF_OFFSET + 1] << 8);

    return(getInternalFlag(FLAG_ONGOING_TX_DATA) && (fcf & IEEE802154_FRAME_TYPE_MASK) == IEEE802154_FRAME_TYPE_COMMAND);
}

#ifdef SL_CATALOG_RAIL_UTIL_IEEE802154_STACK_EVENT_PRESENT
static inline bool isReceivingFrame(void)
{
    return (RAIL_GetRadioState(gRailHandle) & RAIL_RF_STATE_RX_ACTIVE) == RAIL_RF_STATE_RX_ACTIVE;
}
#endif

static void radioSetIdle(void)
{
    if (RAIL_GetRadioState(gRailHandle) != RAIL_RF_STATE_IDLE)
    {
        RAIL_Idle(gRailHandle, RAIL_IDLE, true);
        (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_IDLED, 0U);
        (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_IDLED, 0U);
    }
    RAIL_YieldRadio(gRailHandle);
}

static otError radioSetRx(uint8_t aChannel)
{
    otError       error = OT_ERROR_NONE;
    RAIL_Status_t status;

    RAIL_SchedulerInfo_t bgRxSchedulerInfo = {
        .priority = RADIO_SCHEDULER_BACKGROUND_RX_PRIORITY,
        // sliptime/transaction time is not used for bg rx
    };

#if FAST_CHANNEL_SWITCHING_SUPPORT
    if (isMultiChannel())
    {
        // Calling RAIL_StartRx with a channel not listed in the channel
        // switching config is a bug.
        OT_ASSERT(fastChannelIndex(aChannel) != INVALID_VALUE);

        radioSetIdle();
        status = RAIL_IEEE802154_ConfigRxChannelSwitching(gRailHandle, &sChannelSwitchingCfg);
        OT_ASSERT(status == RAIL_STATUS_NO_ERROR);
        status = RAIL_ConfigRxOptions(gRailHandle, RAIL_RX_OPTION_CHANNEL_SWITCHING, RAIL_RX_OPTION_CHANNEL_SWITCHING);
        OT_ASSERT(status == RAIL_STATUS_NO_ERROR);
    }
    else
    {
        status = RAIL_ConfigRxOptions(gRailHandle, RAIL_RX_OPTION_CHANNEL_SWITCHING, RAIL_RX_OPTIONS_NONE);
        OT_ASSERT(status == RAIL_STATUS_NO_ERROR);
    }
#endif

    status = RAIL_StartRx(gRailHandle, aChannel, &bgRxSchedulerInfo);
    otEXPECT_ACTION(status == RAIL_STATUS_NO_ERROR, error = OT_ERROR_FAILED);

    (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_LISTEN, 0U);

    otLogInfoPlat("State=OT_RADIO_STATE_RECEIVE");
exit:
    return error;
}

#if (OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2)
static otError radioScheduleRx(uint8_t aChannel, uint32_t aStart, uint32_t aDuration)
{
    otError       error = OT_ERROR_NONE;
    RAIL_Status_t status;

    RAIL_SchedulerInfo_t bgRxSchedulerInfo = {
        .priority = RADIO_SCHEDULER_BACKGROUND_RX_PRIORITY,
        // sliptime/transaction time is not used for bg rx
    };

    // Configure scheduled receive as requested
    RAIL_ScheduleRxConfig_t rxCfg = {.start                   = aStart,
                                     .startMode               = RAIL_TIME_ABSOLUTE,
                                     .end                     = aDuration,
                                     .endMode                 = RAIL_TIME_DELAY,
                                     .rxTransitionEndSchedule = 1, // This lets us idle after a scheduled-rx
                                     .hardWindowEnd = 0}; // This lets us receive a packet near a window-end-event

    status = RAIL_ScheduleRx(gRailHandle, aChannel, &rxCfg, &bgRxSchedulerInfo);
    otEXPECT_ACTION(status == RAIL_STATUS_NO_ERROR, error = OT_ERROR_FAILED);

    (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_LISTEN, 0U);
exit:
    return error;
}
#endif // (OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2)

static void configureTxPower(RAIL_TxPowerConfig_t *aTxPowerConfig, int8_t aTxPower)
{
    RAIL_Status_t       status;
    RAIL_TxPowerLevel_t tx_power_lvl;
    RAIL_TxPower_t      tx_power_dbm = aTxPower * 10;

    tx_power_lvl = RAIL_GetTxPower(gRailHandle);

    // Always need to call RAIL_SetTxPowerDbm after RAIL_ConfigTxPower
    // First need to get existing power setting and reassert value after config

    if (tx_power_lvl != RAIL_TX_POWER_LEVEL_INVALID)
    {
        tx_power_dbm = RAIL_GetTxPowerDbm(gRailHandle);
    }

    status = RAIL_ConfigTxPower(gRailHandle, aTxPowerConfig);
    OT_ASSERT(status == RAIL_STATUS_NO_ERROR);

    status = RAIL_SetTxPowerDbm(gRailHandle, tx_power_dbm);
    OT_ASSERT(status == RAIL_STATUS_NO_ERROR);
}

//------------------------------------------------------------------------------
// Radio Initialization
static RAIL_Handle_t efr32RailInit(efr32CommonConfig *aCommonConfig)
{
    RAIL_Status_t status;
    RAIL_Handle_t handle;

#if !OPENTHREAD_RADIO
    OT_ASSERT(DEVICE_CAPABILITY_MCU_EN);
#endif

    handle = RAIL_Init(&aCommonConfig->mRailConfig, NULL);
    OT_ASSERT(handle != NULL);

#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
    status = RAIL_InitPowerManager();
    OT_ASSERT(status == RAIL_STATUS_NO_ERROR);
#endif // SL_CATALOG_POWER_MANAGER_PRESENT

    status = RAIL_ConfigCal(handle, RAIL_CAL_ALL);
    OT_ASSERT(status == RAIL_STATUS_NO_ERROR);

    status = RAIL_SetPtiProtocol(handle, RAIL_PTI_PROTOCOL_THREAD);
    OT_ASSERT(status == RAIL_STATUS_NO_ERROR);

    status = RAIL_IEEE802154_Init(handle, &sRailIeee802154Config);
    OT_ASSERT(status == RAIL_STATUS_NO_ERROR);

#if (OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2)
    // Enhanced Frame Pending
    status = RAIL_IEEE802154_EnableEarlyFramePending(handle, true);
    OT_ASSERT(status == RAIL_STATUS_NO_ERROR);

    status = RAIL_IEEE802154_EnableDataFramePending(handle, true);
    OT_ASSERT(status == RAIL_STATUS_NO_ERROR);

    // Copies of MAC keys for encrypting at the radio layer
    memset(sMacKeys, 0, sizeof(sMacKeys));
#endif // (OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2)

    uint16_t actualLength = 0;
    actualLength = RAIL_SetTxFifo(handle, aCommonConfig->mRailTxFifo.fifo, 0, sizeof(aCommonConfig->mRailTxFifo.fifo));
    OT_ASSERT(actualLength == sizeof(aCommonConfig->mRailTxFifo.fifo));

    // Enable RAIL multi-timer
    RAIL_ConfigMultiTimer(true);

    return handle;
}

static void efr32RailConfigLoad(efr32BandConfig *aBandConfig, int8_t aTxPower)
{
    RAIL_Status_t        status;
    RAIL_TxPowerConfig_t txPowerConfig = {SL_RAIL_UTIL_PA_SELECTION_2P4GHZ,
                                          SL_RAIL_UTIL_PA_VOLTAGE_MV,
                                          SL_RAIL_UTIL_PA_RAMP_TIME_US};

    if (aBandConfig->mChannelConfig != NULL)
    {
        status = RAIL_IEEE802154_SetPtiRadioConfig(gRailHandle, RAIL_IEEE802154_PTI_RADIO_CONFIG_915MHZ_R23_NA_EXT);
        OT_ASSERT(status == RAIL_STATUS_NO_ERROR);

        uint16_t firstChannel = UNINITIALIZED_CHANNEL;
        firstChannel = RAIL_ConfigChannels(gRailHandle, aBandConfig->mChannelConfig, NULL);
        OT_ASSERT(firstChannel == aBandConfig->mChannelMin);

        txPowerConfig.mode = SL_RAIL_UTIL_PA_SELECTION_SUBGHZ;
        status =
            RAIL_IEEE802154_ConfigGOptions(gRailHandle, RAIL_IEEE802154_G_OPTION_GB868, RAIL_IEEE802154_G_OPTION_GB868);
        OT_ASSERT(status == RAIL_STATUS_NO_ERROR);
    }
    else
    {
#if defined(SL_CATALOG_RAIL_UTIL_IEEE802154_PHY_SELECT_PRESENT)
        status = sl_rail_util_ieee802154_config_radio(gRailHandle);
#else
        status = RAIL_IEEE802154_Config2p4GHzRadio(gRailHandle);
#endif // SL_CATALOG_RAIL_UTIL_IEEE802154_PHY_SELECT_PRESENT
        OT_ASSERT(status == RAIL_STATUS_NO_ERROR);
    }

#if (OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2)
    // 802.15.4E support (only on platforms that support it, so error checking is disabled)
    // Note: This has to be called after RAIL_IEEE802154_Config2p4GHzRadio due to a bug where this call
    // can overwrite options set below.
    RAIL_IEEE802154_ConfigEOptions(gRailHandle,
                                   (RAIL_IEEE802154_E_OPTION_GB868 | RAIL_IEEE802154_E_OPTION_ENH_ACK),
                                   (RAIL_IEEE802154_E_OPTION_GB868 | RAIL_IEEE802154_E_OPTION_ENH_ACK));
#endif // (OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2)

    if (aTxPower != SL_INVALID_TX_POWER)
    {
        configureTxPower(&txPowerConfig, aTxPower);
    }
}

static void efr32RadioSetTxPower(int8_t aPowerDbm)
{
    RAIL_Status_t status;

    status = RAIL_SetTxPowerDbm(gRailHandle, ((RAIL_TxPower_t)aPowerDbm) * 10);
    OT_ASSERT(status == RAIL_STATUS_NO_ERROR);
}

static efr32BandConfig *efr32RadioGetBandConfig(uint8_t aChannel)
{
    efr32BandConfig *config = NULL;

    if ((sBandConfig.mChannelMin <= aChannel) && (aChannel <= sBandConfig.mChannelMax))
    {
        config = &sBandConfig;
    }

    return config;
}

static void efr32ConfigInit(void (*aEventCallback)(RAIL_Handle_t railHandle, RAIL_Events_t events))
{
    sCommonConfig.mRailConfig.eventsCallback = aEventCallback;
    sCommonConfig.mRailConfig.protocol       = NULL; // only used by Bluetooth stack
#if RADIO_CONFIG_DMP_SUPPORT
    sCommonConfig.mRailConfig.scheduler = &(sCommonConfig.mRailSchedState);
#else
    sCommonConfig.mRailConfig.scheduler = NULL; // only needed for DMP
#endif

#if RADIO_CONFIG_2P4GHZ_OQPSK_SUPPORT
    sBandConfig.mChannelConfig = NULL;
#else
    sBandConfig.mChannelConfig          = channelConfigs[0];
#endif
    sBandConfig.mChannelMin = SL_CHANNEL_MIN;
    sBandConfig.mChannelMax = SL_CHANNEL_MAX;

#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
    memset(&railDebugCounters, 0x00, sizeof(efr32RadioCounters));
#endif

    memset(sMaxChannelPower, SL_INVALID_TX_POWER, sizeof(sMaxChannelPower));
    memset(sDefaultTxPower, SL_INVALID_TX_POWER, sizeof(sDefaultTxPower));

    gRailHandle = efr32RailInit(&sCommonConfig);
    OT_ASSERT(gRailHandle != NULL);

    updateEvents(RAIL_EVENTS_ALL,
                 (0 | RAIL_EVENT_RX_ACK_TIMEOUT | RAIL_EVENT_RX_PACKET_RECEIVED
#if OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2
                  | RAIL_EVENT_SCHEDULED_TX_STARTED | RAIL_EVENT_TX_SCHEDULED_TX_MISSED
                  | RAIL_EVENT_SCHEDULED_RX_STARTED | RAIL_EVENT_RX_SCHEDULED_RX_END | RAIL_EVENT_RX_SCHEDULED_RX_MISSED
#endif
                  | RAIL_EVENTS_TXACK_COMPLETION | RAIL_EVENTS_TX_COMPLETION | RAIL_EVENT_RSSI_AVERAGE_DONE
                  | RAIL_EVENT_IEEE802154_DATA_REQUEST_COMMAND
#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT || RADIO_CONFIG_DMP_SUPPORT
                  | RAIL_EVENT_CONFIG_SCHEDULED | RAIL_EVENT_CONFIG_UNSCHEDULED | RAIL_EVENT_SCHEDULER_STATUS
#endif
                  | RAIL_EVENT_CAL_NEEDED));

    efr32RailConfigLoad(&(sBandConfig), OPENTHREAD_CONFIG_DEFAULT_TRANSMIT_POWER);
}

void efr32RadioInit(void)
{
    if (getInternalFlag(FLAG_RADIO_INIT_DONE))
    {
        return;
    }
    RAIL_Status_t status;

    // check if RAIL_TX_FIFO_SIZE is power of two..
    OT_ASSERT((RAIL_TX_FIFO_SIZE & (RAIL_TX_FIFO_SIZE - 1)) == 0);

    // check the limits of the RAIL_TX_FIFO_SIZE.
    OT_ASSERT((RAIL_TX_FIFO_SIZE >= 64) || (RAIL_TX_FIFO_SIZE <= 4096));

    efr32ConfigInit(RAILCb_Generic);
    setInternalFlag(FLAG_RADIO_INIT_DONE, true);

    status = RAIL_ConfigSleep(gRailHandle, RAIL_SLEEP_CONFIG_TIMERSYNC_ENABLED);
    OT_ASSERT(status == RAIL_STATUS_NO_ERROR);

    memset(&sReceivePacket, 0x00, sizeof(sReceivePacket));

    sReceiveFrame.mLength       = 0;
    sReceiveFrame.mPsdu         = NULL;

    sReceiveAckFrame.mLength    = 0;
    sReceiveAckFrame.mPsdu      = sReceiveAckPsdu;
    sTransmitFrame.mLength      = 0;
    sTransmitFrame.mPsdu        = sTransmitPsdu;

#if OPENTHREAD_CONFIG_MAC_HEADER_IE_SUPPORT
    sTransmitFrame.mInfo.mTxInfo.mIeInfo = &sTransmitIeInfo;
#endif

#if OPENTHREAD_CONFIG_MLE_LINK_METRICS_SUBJECT_ENABLE
    otLinkMetricsInit(EFR32_RECEIVE_SENSITIVITY);
#endif
    sCurrentBandConfig = efr32RadioGetBandConfig(OPENTHREAD_CONFIG_DEFAULT_CHANNEL);
    OT_ASSERT(sCurrentBandConfig != NULL);

    sl_rail_util_pa_init();
    efr32RadioSetTxPower(OPENTHREAD_CONFIG_DEFAULT_TRANSMIT_POWER);

    status = RAIL_ConfigRxOptions(gRailHandle,
                                  RAIL_RX_OPTION_TRACK_ABORTED_FRAMES,
                                  RAIL_RX_OPTION_TRACK_ABORTED_FRAMES);
    OT_ASSERT(status == RAIL_STATUS_NO_ERROR);
    efr32PhyStackInit();
    efr32RadioSetCcaMode(SL_OPENTHREAD_RADIO_CCA_MODE);

    sEnergyScanStatus = ENERGY_SCAN_STATUS_IDLE;

#if FAST_CHANNEL_SWITCHING_SUPPORT
    sChannelSwitchingCfg.bufferBytes = RAIL_IEEE802154_RX_CHANNEL_SWITCHING_BUF_BYTES;
    sChannelSwitchingCfg.buffer      = sChannelSwitchingBuffer;
    for (uint8_t i = 0U; i < RAIL_IEEE802154_RX_CHANNEL_SWITCHING_NUM_CHANNELS; i++)
    {
        sChannelSwitchingCfg.channels[i] = UNINITIALIZED_CHANNEL;
    }
#endif

    otLogInfoPlat("Initialized");
}

void efr32RadioDeinit(void)
{
    RAIL_Status_t status;

    RAIL_Idle(gRailHandle, RAIL_IDLE_ABORT, true);
    status = RAIL_ConfigEvents(gRailHandle, RAIL_EVENTS_ALL, 0);
    OT_ASSERT(status == RAIL_STATUS_NO_ERROR);

    sCurrentBandConfig = NULL;
}

//------------------------------------------------------------------------------
// Energy Scan support

static void energyScanComplete(int8_t scanResultDbm)
{
    sEnergyScanResultDbm = scanResultDbm;
    sEnergyScanStatus    = ENERGY_SCAN_STATUS_COMPLETED;
}

static otError efr32StartEnergyScan(energyScanMode aMode, uint16_t aChannel, RAIL_Time_t aAveragingTimeUs)
{
    RAIL_Status_t    status = RAIL_STATUS_NO_ERROR;
    otError          error  = OT_ERROR_NONE;
    efr32BandConfig *config = NULL;

    otEXPECT_ACTION(sEnergyScanStatus == ENERGY_SCAN_STATUS_IDLE, error = OT_ERROR_BUSY);

    sEnergyScanStatus = ENERGY_SCAN_STATUS_IN_PROGRESS;
    sEnergyScanMode   = aMode;

    RAIL_Idle(gRailHandle, RAIL_IDLE, true);

    config = efr32RadioGetBandConfig(aChannel);
    otEXPECT_ACTION(config != NULL, error = OT_ERROR_INVALID_ARGS);

    if (sCurrentBandConfig != config)
    {
        efr32RailConfigLoad(config, SL_INVALID_TX_POWER);
        sCurrentBandConfig = config;
    }

    RAIL_SchedulerInfo_t scanSchedulerInfo = {.priority        = RADIO_SCHEDULER_CHANNEL_SCAN_PRIORITY,
                                              .slipTime        = RADIO_SCHEDULER_CHANNEL_SLIP_TIME,
                                              .transactionTime = aAveragingTimeUs};

    status = RAIL_StartAverageRssi(gRailHandle, aChannel, aAveragingTimeUs, &scanSchedulerInfo);
    otEXPECT_ACTION(status == RAIL_STATUS_NO_ERROR, error = OT_ERROR_FAILED);

exit:
    if (status != RAIL_STATUS_NO_ERROR)
    {
        energyScanComplete(OT_RADIO_RSSI_INVALID);
    }
    return error;
}

//------------------------------------------------------------------------------
// Stack support

uint64_t otPlatRadioGetNow(otInstance *aInstance)
{
    OT_UNUSED_VARIABLE(aInstance);

    return otPlatTimeGet();
}

void otPlatRadioGetIeeeEui64(otInstance *aInstance, uint8_t *aIeeeEui64)
{
    OT_UNUSED_VARIABLE(aInstance);

#if RADIO_CONFIG_ENABLE_CUSTOM_EUI_SUPPORT
    // Invalid EUI
    uint8_t nullEui[] = {0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU};

    // Read the Custom EUI and compare it to nullEui
    if ((readUserData(aIeeeEui64, USERDATA_MFG_CUSTOM_EUI_64, OT_EXT_ADDRESS_SIZE, true) == -1)
        || (memcmp(aIeeeEui64, nullEui, OT_EXT_ADDRESS_SIZE) == 0))
#endif
    {
        uint64_t eui64;
        uint8_t *eui64Ptr = NULL;

        eui64    = SYSTEM_GetUnique();
        eui64Ptr = (uint8_t *)&eui64;

        for (uint8_t i = 0; i < OT_EXT_ADDRESS_SIZE; i++)
        {
            aIeeeEui64[i] = eui64Ptr[(OT_EXT_ADDRESS_SIZE - 1) - i];
        }
    }
}

void otPlatRadioSetPanId(otInstance *aInstance, uint16_t aPanId)
{
    OT_UNUSED_VARIABLE(aInstance);

    RAIL_Status_t status;
    uint8_t       iid      = otNcpPlatGetCurCommandIid();
    uint8_t       panIndex = getPanIndexFromIid(iid);

    OT_ASSERT(panIndex != INVALID_VALUE);
    otLogInfoPlat("PANID=%X index=%u IID=%d", aPanId, panIndex, iid);
    utilsSoftSrcMatchSetPanId(iid, aPanId);

    status = RAIL_IEEE802154_SetPanId(gRailHandle, aPanId, panIndex);
    OT_ASSERT(status == RAIL_STATUS_NO_ERROR);

#if OPENTHREAD_RADIO && OPENTHREAD_CONFIG_MULTIPAN_RCP_ENABLE == 1
    // We already have IID 0 enabled in filtermask to track BCAST Packets, so
    // track only unique PanIds.
    if (aPanId != RADIO_BCAST_PANID)
    {
        sRailFilterMask |= RADIO_GET_FILTER_MASK(iid);
    }
#endif
}

void otPlatRadioSetExtendedAddress(otInstance *aInstance, const otExtAddress *aAddress)
{
    RAIL_Status_t status;
    uint8_t       panIndex = getPanIndexFromIid(otNcpPlatGetCurCommandIid());

    OT_UNUSED_VARIABLE(aInstance);
    OT_ASSERT(panIndex != INVALID_VALUE);

    for (size_t i = 0; i < sizeof(*aAddress); i++)
    {
        sExtAddress[panIndex].m8[i] = aAddress->m8[sizeof(*aAddress) - 1 - i];
    }

    otLogInfoPlat("ExtAddr=%X%X%X%X%X%X%X%X index=%u",
                  aAddress->m8[7],
                  aAddress->m8[6],
                  aAddress->m8[5],
                  aAddress->m8[4],
                  aAddress->m8[3],
                  aAddress->m8[2],
                  aAddress->m8[1],
                  aAddress->m8[0],
                  panIndex);

    status = RAIL_IEEE802154_SetLongAddress(gRailHandle, (uint8_t *)aAddress->m8, panIndex);
    OT_ASSERT(status == RAIL_STATUS_NO_ERROR);
}

void otPlatRadioSetShortAddress(otInstance *aInstance, uint16_t aAddress)
{
    OT_UNUSED_VARIABLE(aInstance);

    RAIL_Status_t status;
    uint8_t       panIndex = getPanIndexFromIid(otNcpPlatGetCurCommandIid());

    OT_ASSERT(panIndex != INVALID_VALUE);
    otLogInfoPlat("ShortAddr=%X index=%u", aAddress, panIndex);

    status = RAIL_IEEE802154_SetShortAddress(gRailHandle, aAddress, panIndex);
    OT_ASSERT(status == RAIL_STATUS_NO_ERROR);
}

otRadioState otPlatRadioGetState(otInstance *aInstance)
{
    otRadioState radioState = OT_RADIO_STATE_INVALID;

    OT_UNUSED_VARIABLE(aInstance);

    switch (RAIL_GetRadioState(gRailHandle))
    {
    case RAIL_RF_STATE_RX_ACTIVE:
        radioState = OT_RADIO_STATE_RECEIVE;
        break;
    
    case RAIL_RF_STATE_TX_ACTIVE:
        radioState = OT_RADIO_STATE_TRANSMIT;
        break;
    
    case RAIL_RF_STATE_IDLE:
        radioState = OT_RADIO_STATE_SLEEP;
        break;

    case RAIL_RF_STATE_INACTIVE:
        radioState = OT_RADIO_STATE_DISABLED;
        break;
    }

    return radioState;
}

bool otPlatRadioIsEnabled(otInstance *aInstance)
{
    OT_UNUSED_VARIABLE(aInstance);

    return (getInternalFlag(FLAG_RADIO_INIT_DONE));
}

otError otPlatRadioEnable(otInstance *aInstance)
{
    otEXPECT(!otPlatRadioIsEnabled(aInstance));

    otLogInfoPlat("State=OT_RADIO_STATE_SLEEP");

exit:
    return OT_ERROR_NONE;
}

otError otPlatRadioDisable(otInstance *aInstance)
{
    otEXPECT(otPlatRadioIsEnabled(aInstance));

    otLogInfoPlat("State=OT_RADIO_STATE_DISABLED");

exit:
    return OT_ERROR_NONE;
}

otError otPlatRadioSleep(otInstance *aInstance)
{
    OT_UNUSED_VARIABLE(aInstance);
    otError error = OT_ERROR_NONE;

    otEXPECT_ACTION(!getInternalFlag(ONGOING_TX_FLAGS), error = OT_ERROR_BUSY);

    otLogInfoPlat("State=OT_RADIO_STATE_SLEEP");
    setInternalFlag(FLAG_SCHEDULED_RX_PENDING, false);
    radioSetIdle();

exit:
    return error;
}

otError efr32RadioLoadChannelConfig(uint8_t aChannel, int8_t aTxPower)
{
    otError          error = OT_ERROR_NONE;
    efr32BandConfig *config;

    config  = efr32RadioGetBandConfig(aChannel);
    otEXPECT_ACTION(config != NULL, error = OT_ERROR_INVALID_ARGS);

    if (sCurrentBandConfig != config)
    {
        RAIL_Idle(gRailHandle, RAIL_IDLE, true);
        efr32RailConfigLoad(config, aTxPower);
        sCurrentBandConfig = config;
    }
    else
    {
        efr32RadioSetTxPower(aTxPower);
    }

exit:
    return error;
}

otError otPlatRadioReceive(otInstance *aInstance, uint8_t aChannel)
{
    otError          error = OT_ERROR_NONE;
    RAIL_Status_t    status;
    int8_t           txPower;

    OT_UNUSED_VARIABLE(aInstance);
    otEXPECT_ACTION(!getInternalFlag(FLAG_ONGOING_TX_DATA)
                     && sEnergyScanStatus != ENERGY_SCAN_STATUS_IN_PROGRESS, error = OT_ERROR_INVALID_STATE);

#if FAST_CHANNEL_SWITCHING_SUPPORT
    uint8_t index = getPanIndexFromIid(otNcpPlatGetCurCommandIid());
    OT_ASSERT(index < RAIL_IEEE802154_RX_CHANNEL_SWITCHING_NUM_CHANNELS);
    sChannelSwitchingCfg.channels[index] = aChannel;
#endif

    txPower = sli_get_max_tx_power_across_iids();
    error = efr32RadioLoadChannelConfig(aChannel, txPower);
    otEXPECT(error == OT_ERROR_NONE);

    status = radioSetRx(aChannel);
    otEXPECT_ACTION(status == RAIL_STATUS_NO_ERROR, error = OT_ERROR_FAILED);
    setInternalFlag(FLAG_SCHEDULED_RX_PENDING, false);

    sReceiveFrame.mChannel = aChannel;
    sReceiveAckFrame.mChannel = aChannel;

exit:
    return error;
}

#if (OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2)
otError otPlatRadioReceiveAt(otInstance *aInstance, uint8_t aChannel, uint32_t aStart, uint32_t aDuration)
{
    otError          error = OT_ERROR_NONE;
    RAIL_Status_t    status;
    int8_t           txPower = sli_get_max_tx_power_across_iids();

    OT_UNUSED_VARIABLE(aInstance);

    error = efr32RadioLoadChannelConfig(aChannel, txPower);
    otEXPECT(error == OT_ERROR_NONE);

    status = radioScheduleRx(aChannel, aStart, aDuration);
    otEXPECT_ACTION(status == RAIL_STATUS_NO_ERROR, error = OT_ERROR_FAILED);
    setInternalFlag(FLAG_SCHEDULED_RX_PENDING, true);

    sReceiveFrame.mChannel = aChannel;
    sReceiveAckFrame.mChannel = aChannel;

exit:
    return error;
}
#endif // (OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2)

otError otPlatRadioTransmit(otInstance *aInstance, otRadioFrame *aFrame)
{
    otError          error = OT_ERROR_NONE;
    int8_t           txPower = sli_get_max_tx_power_across_iids();

#if OPENTHREAD_RADIO && OPENTHREAD_CONFIG_MULTIPAN_RCP_ENABLE == 1 && (defined SL_CATALOG_OT_RCP_GP_INTERFACE_PRESENT)
    // Accept GP packets even if radio is not in required state.
    if ((sl_gp_intf_get_state() != SL_GP_STATE_SEND_RESPONSE) && sl_gp_intf_is_gp_pkt(aFrame, false))
    {
        sl_gp_intf_buffer_pkt(aFrame);
    }
    else
#endif
    {
        error = efr32RadioLoadChannelConfig(aFrame->mChannel, txPower);
        otEXPECT(error == OT_ERROR_NONE);

        OT_ASSERT(!getInternalFlag(FLAG_ONGOING_TX_DATA));
        OT_ASSERT(aFrame == &sTransmitFrame);

        setInternalFlag(RADIO_TX_EVENTS, false);
        sTxFrame       = aFrame;

        setInternalFlag(FLAG_CURRENT_TX_USE_CSMA, aFrame->mInfo.mTxInfo.mCsmaCaEnabled);

#if OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2
#if OPENTHREAD_CONFIG_MAC_CSL_RECEIVER_ENABLE
        if (sCslPeriod > 0 && sTxFrame->mInfo.mTxInfo.mTxDelay == 0)
        {
            // Only called for CSL children (sCslPeriod > 0)
            // Note: Our SSEDs "schedule" transmissions to their parent in order to know
            // exactly when in the future the data packets go out so they can calculate
            // the accurate CSL phase to send to their parent.
            sTxFrame->mInfo.mTxInfo.mTxDelayBaseTime = RAIL_GetTime();
            sTxFrame->mInfo.mTxInfo.mTxDelay = 3000; // Chosen after internal certification testing
        }
#endif
        updateIeInfoTxFrame(sTxFrame->mInfo.mTxInfo.mTxDelayBaseTime + sTxFrame->mInfo.mTxInfo.mTxDelay + SHR_DURATION_US);
        // Note - we need to call this outside of txCurrentPacket as for Series 2,
        // this results in calling the SE interface from a critical section which is not permitted.
        radioProcessTransmitSecurity(sTxFrame, sTxFrame->mIid);
#endif // OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2

        CORE_DECLARE_IRQ_STATE;
        CORE_ENTER_ATOMIC();
        setInternalFlag(FLAG_SCHEDULED_RX_PENDING, false);
        setInternalFlag(FLAG_ONGOING_TX_DATA, true);
        tryTxCurrentPacket();
        CORE_EXIT_ATOMIC();

        if (getInternalFlag(EVENT_TX_FAILED))
        {
            otPlatRadioTxStarted(aInstance, aFrame);
        }
    }
exit:
    return error;
}

#if OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2
void updateIeInfoTxFrame(uint32_t shrTxTime)
{
    OT_ASSERT(sTxFrame != NULL);

#if OPENTHREAD_CONFIG_MAC_HEADER_IE_SUPPORT && OPENTHREAD_CONFIG_TIME_SYNC_ENABLE
    // Seek the time sync offset and update the rendezvous time
    if (sTxFrame->mInfo.mTxInfo.mIeInfo->mTimeIeOffset != 0)
    {
        uint8_t *timeIe = sTxFrame->mPsdu + sTxFrame->mInfo.mTxInfo.mIeInfo->mTimeIeOffset;
        uint64_t time   = otPlatTimeGet() + sTxFrame->mInfo.mTxInfo.mIeInfo->mNetworkTimeOffset;

        *timeIe = sTxFrame->mInfo.mTxInfo.mIeInfo->mTimeSyncSeq;

        *(++timeIe) = (uint8_t)(time & 0xff);
        for (uint8_t i = 1; i < sizeof(uint64_t); i++)
        {
            time        = time >> 8;
            *(++timeIe) = (uint8_t)(time & 0xff);
        }
    }
#endif // OPENTHREAD_CONFIG_MAC_HEADER_IE_SUPPORT && OPENTHREAD_CONFIG_TIME_SYNC_ENABLE

#if OPENTHREAD_CONFIG_MAC_CSL_RECEIVER_ENABLE
    // Update IE data in the 802.15.4 header with the newest CSL period / phase
    if (sCslPeriod > 0 && !sTxFrame->mInfo.mTxInfo.mIsHeaderUpdated)
    {
        otMacFrameSetCslIe(sTxFrame, (uint16_t)sCslPeriod, getCslPhase(shrTxTime));
    }
#else
    OT_UNUSED_VARIABLE(shrTxTime);
#endif // OPENTHREAD_CONFIG_MAC_CSL_RECEIVER_ENABLE
}
#endif // OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2

void txCurrentPacket(void)
{
    OT_ASSERT(getInternalFlag(FLAG_ONGOING_TX_DATA));
    OT_ASSERT(sTxFrame != NULL);

    RAIL_TxOptions_t  txOptions  = RAIL_TX_OPTIONS_DEFAULT;
    RAIL_Status_t     status     = RAIL_STATUS_INVALID_STATE;
    uint8_t           frameLength;
    bool              ackRequested;

#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
    railDebugCounters.mRailPlatTxTriggered++;
#endif
    // signalling this event earlier, as this event can OT_ASSERT REQ (expecially for a
    // non-CSMA transmit) giving the Coex master a little more time to grant or deny.
    if (getInternalFlag(FLAG_CURRENT_TX_USE_CSMA))
    {
        (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_PENDED_PHY, (uint32_t) true);
    }
    else
    {
        (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_PENDED_PHY, (uint32_t) false);
    }

    frameLength = (uint8_t)sTxFrame->mLength;

    if (PHY_HEADER_SIZE == 1)
    {
        RAIL_WriteTxFifo(gRailHandle, &frameLength, sizeof frameLength, true);
    }
    else
    { // 2 byte PHR for Sub-GHz
        uint8_t PHRByte1 = (0x08U /*FCS=2byte*/ | 0x10U /*Whiten=enabled*/);
        uint8_t PHRByte2 = (uint8_t)(__RBIT(frameLength) >> 24);

        RAIL_WriteTxFifo(gRailHandle, &PHRByte1, sizeof PHRByte1, true);
        RAIL_WriteTxFifo(gRailHandle, &PHRByte2, sizeof PHRByte2, false);
    }
    RAIL_WriteTxFifo(gRailHandle, sTxFrame->mPsdu, frameLength - 2, false);

    RAIL_SchedulerInfo_t txSchedulerInfo = {
        .priority        = RADIO_SCHEDULER_TX_PRIORITY,
        .slipTime        = RADIO_SCHEDULER_CHANNEL_SLIP_TIME,
        .transactionTime = 0, // will be calculated later if DMP is used
    };

    ackRequested = (sTxFrame->mPsdu[0] & IEEE802154_FRAME_FLAG_ACK_REQUIRED);
    if (ackRequested)
    {
        txOptions |= RAIL_TX_OPTION_WAIT_FOR_ACK;

#if RADIO_CONFIG_DMP_SUPPORT
        // time we wait for ACK
        if (RAIL_GetSymbolRate(gRailHandle) > 0)
        {
            txSchedulerInfo.transactionTime += 12 * 1e6 / RAIL_GetSymbolRate(gRailHandle);
        }
        else
        {
            txSchedulerInfo.transactionTime += 12 * RADIO_TIMING_DEFAULT_SYMBOLTIME_US;
        }
#endif
    }

#ifdef SL_CATALOG_RAIL_UTIL_ANT_DIV_PRESENT
    // Update Tx options to use currently-selected antenna.
    // If antenna diverisity on Tx is disabled, leave both options 0
    // so Tx antenna tracks Rx antenna.
    if (sl_rail_util_ant_div_get_tx_antenna_mode() != SL_RAIL_UTIL_ANT_DIV_DISABLED)
    {
        txOptions |= ((sl_rail_util_ant_div_get_tx_antenna_selected() == SL_RAIL_UTIL_ANTENNA_SELECT_ANTENNA1)
                          ? RAIL_TX_OPTION_ANTENNA0
                          : RAIL_TX_OPTION_ANTENNA1);
    }
#endif // SL_CATALOG_RAIL_UTIL_ANT_DIV_PRESENT

#if RADIO_CONFIG_DMP_SUPPORT
    // time needed for the frame itself
    // 4B preamble, 1B SFD, 1B PHR is not counted in frameLength
    if (RAIL_GetBitRate(gRailHandle) > 0)
    {
        txSchedulerInfo.transactionTime += (frameLength + 4 + 1 + 1) * 8 * 1e6 / RAIL_GetBitRate(gRailHandle);
    }
    else
    { // assume 250kbps
        txSchedulerInfo.transactionTime += (frameLength + 4 + 1 + 1) * RADIO_TIMING_DEFAULT_BYTETIME_US;
    }
#endif

    if (sTxFrame->mInfo.mTxInfo.mTxDelay == 0)
    {
        if (getInternalFlag(FLAG_CURRENT_TX_USE_CSMA))
        {
#if RADIO_CONFIG_DMP_SUPPORT
            // time needed for CSMA/CA
            txSchedulerInfo.transactionTime += RADIO_TIMING_CSMA_OVERHEAD_US;
#endif
            csmaConfig.csmaTries    = sTxFrame->mInfo.mTxInfo.mMaxCsmaBackoffs;
            csmaConfig.ccaThreshold = sCcaThresholdDbm;

            status = RAIL_StartCcaCsmaTx(gRailHandle,
                                         sTxFrame->mChannel,
                                         txOptions,
                                         &csmaConfig,
                                         &txSchedulerInfo);
        }
        else
        {
            status = RAIL_StartTx(gRailHandle, sTxFrame->mChannel, txOptions, &txSchedulerInfo);
        }

        if (status == RAIL_STATUS_NO_ERROR) {
            (void) handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_STARTED, 0U);
        }
    }
    else
    {
        // For CSL transmitters (FTDs):
        // mTxDelayBaseTime = rx-timestamp (end of sync word) when we received CSL-sync with IEs
        // mTxDelay = Delay starting from mTxDelayBaseTime
        //
        // For CSL receivers (SSEDs):
        // mTxDelayBaseTime = timestamp when otPlatRadioTransmit is called
        // mTxDelay = Chosen value in the future where transmit is scheduled, so we know exactly
        // when to calculate the phase (we can't do this on-the-fly as the packet is going out
        // due to platform limitations.  see radioScheduleRx)
        //
        // Note that both use single CCA config, overriding any CCA/CSMA configs from the stack
        //
#if OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2
        RAIL_ScheduleTxConfig_t scheduleTxOptions = {
            .when = sTxFrame->mInfo.mTxInfo.mTxDelayBaseTime + sTxFrame->mInfo.mTxInfo.mTxDelay - SHR_DURATION_US,
            .mode = RAIL_TIME_ABSOLUTE,
            .txDuringRx = RAIL_SCHEDULED_TX_DURING_RX_POSTPONE_TX
        };

        // CSL transmissions don't use CSMA but MAC accounts for single CCA time.
        // cslCsmaConfig is set to RAIL_CSMA_CONFIG_SINGLE_CCA above.
        status = RAIL_StartScheduledCcaCsmaTx(gRailHandle,
                                              sTxFrame->mChannel,
                                              txOptions,
                                              &scheduleTxOptions,
                                              &cslCsmaConfig,
                                              &txSchedulerInfo);

        if (status == RAIL_STATUS_NO_ERROR) {
#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
            railDebugCounters.mRailEventsScheduledTxTriggeredCount++;
#endif
            (void) handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_STARTED, 0U);
        }
#endif
    }
    if (status == RAIL_STATUS_NO_ERROR)
    {
#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
        railDebugCounters.mRailTxStarted++;
#endif
    }
    else
    {
#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
        railDebugCounters.mRailTxStartFailed++;
#endif
        (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_BLOCKED, (uint32_t)ackRequested);
        txFailedCallback(false, EVENT_TX_FAILED);

        otSysEventSignalPending();
    }
}

otRadioFrame *otPlatRadioGetTransmitBuffer(otInstance *aInstance)
{
    OT_UNUSED_VARIABLE(aInstance);

    return &sTransmitFrame;
}

int8_t otPlatRadioGetRssi(otInstance *aInstance)
{
    otError  error;
    uint32_t start;
    int8_t   rssi     = OT_RADIO_RSSI_INVALID;
    uint8_t  aChannel = sReceiveFrame.mChannel;

    OT_UNUSED_VARIABLE(aInstance);

    otEXPECT(!getInternalFlag(FLAG_ONGOING_TX_DATA));

#if FAST_CHANNEL_SWITCHING_SUPPORT
    uint8_t index = getPanIndexFromIid(otNcpPlatGetCurCommandIid());
    OT_ASSERT(index < RAIL_IEEE802154_RX_CHANNEL_SWITCHING_NUM_CHANNELS);
    if (sChannelSwitchingCfg.channels[index] != UNINITIALIZED_CHANNEL)
    {
        aChannel = sChannelSwitchingCfg.channels[index];
    }
#endif

    error = efr32StartEnergyScan(ENERGY_SCAN_MODE_SYNC, aChannel, EFR32_RSSI_AVERAGING_TIME);
    otEXPECT(error == OT_ERROR_NONE);

    start = RAIL_GetTime();

    // waiting for the event RAIL_EVENT_RSSI_AVERAGE_DONE
    while (sEnergyScanStatus == ENERGY_SCAN_STATUS_IN_PROGRESS
           && ((RAIL_GetTime() - start) < EFR32_RSSI_AVERAGING_TIMEOUT))
        ;

    if (sEnergyScanStatus == ENERGY_SCAN_STATUS_COMPLETED)
    {
        rssi = sEnergyScanResultDbm;
    }

    sEnergyScanStatus = ENERGY_SCAN_STATUS_IDLE;
exit:
    return rssi;
}

otRadioCaps otPlatRadioGetCaps(otInstance *aInstance)
{
    OT_UNUSED_VARIABLE(aInstance);

    return sRadioCapabilities;
}

bool otPlatRadioGetPromiscuous(otInstance *aInstance)
{
    OT_UNUSED_VARIABLE(aInstance);

    return sPromiscuous;
}

void otPlatRadioSetPromiscuous(otInstance *aInstance, bool aEnable)
{
    OT_UNUSED_VARIABLE(aInstance);

    RAIL_Status_t status;

    sPromiscuous = aEnable;

    status = RAIL_IEEE802154_SetPromiscuousMode(gRailHandle, aEnable);
    OT_ASSERT(status == RAIL_STATUS_NO_ERROR);
}

void otPlatRadioEnableSrcMatch(otInstance *aInstance, bool aEnable)
{
    OT_UNUSED_VARIABLE(aInstance);

    // set Frame Pending bit for all outgoing ACKs if aEnable is false
    sIsSrcMatchEnabled = aEnable;
}

otError otPlatRadioGetTransmitPower(otInstance *aInstance, int8_t *aPower)
{
    OT_UNUSED_VARIABLE(aInstance);

    otError error = OT_ERROR_NONE;

    otEXPECT_ACTION(aPower != NULL, error = OT_ERROR_INVALID_ARGS);
    // RAIL_GetTxPowerDbm() returns power in deci-dBm (0.1dBm)
    // Divide by 10 because aPower is supposed be in units dBm
    *aPower = RAIL_GetTxPowerDbm(gRailHandle) / 10;

exit:
    return error;
}

otError otPlatRadioSetTransmitPower(otInstance *aInstance, int8_t aPower)
{
    OT_UNUSED_VARIABLE(aInstance);

    RAIL_Status_t status;
    int8_t        maxTxPower;

    sDefaultTxPower[otNcpPlatGetCurCommandIid()] = aPower;
    maxTxPower                                   = sli_get_max_tx_power_across_iids();

    // RAIL_SetTxPowerDbm() takes power in units of deci-dBm (0.1dBm)
    // Multiply by 10 because aPower is supposed be in units dBm
    status = RAIL_SetTxPowerDbm(gRailHandle, ((RAIL_TxPower_t)maxTxPower) * 10);
    OT_ASSERT(status == RAIL_STATUS_NO_ERROR);

    return OT_ERROR_NONE;
}

// Required for RCP error recovery
// See src/lib/spinel/radio_spinel.cpp::RestoreProperties()
otError otPlatRadioSetChannelMaxTransmitPower(otInstance *aInstance, uint8_t aChannel, int8_t aMaxPower)
{
    otError error = OT_ERROR_NONE;
    uint8_t iid   = otNcpPlatGetCurCommandIid();
    int8_t  txPower;

    OT_UNUSED_VARIABLE(aInstance);

    otEXPECT_ACTION(aChannel >= SL_CHANNEL_MIN && aChannel <= SL_CHANNEL_MAX, error = OT_ERROR_INVALID_ARGS);

    sMaxChannelPower[iid][aChannel - SL_CHANNEL_MIN] = aMaxPower;
    txPower                                          = sli_get_max_tx_power_across_iids();
    efr32RadioSetTxPower(txPower);

exit:
    return error;
}

otError otPlatRadioGetCcaEnergyDetectThreshold(otInstance *aInstance, int8_t *aThreshold)
{
    OT_UNUSED_VARIABLE(aInstance);

    otError error = OT_ERROR_NONE;
    otEXPECT_ACTION(aThreshold != NULL, error = OT_ERROR_INVALID_ARGS);

    *aThreshold = sCcaThresholdDbm;

exit:
    return error;
}

otError otPlatRadioSetCcaEnergyDetectThreshold(otInstance *aInstance, int8_t aThreshold)
{
    OT_UNUSED_VARIABLE(aInstance);

    sCcaThresholdDbm = aThreshold;

    return OT_ERROR_NONE;
}

int8_t otPlatRadioGetReceiveSensitivity(otInstance *aInstance)
{
    OT_UNUSED_VARIABLE(aInstance);

    return EFR32_RECEIVE_SENSITIVITY;
}

otError otPlatRadioEnergyScan(otInstance *aInstance, uint8_t aScanChannel, uint16_t aScanDuration)
{
    OT_UNUSED_VARIABLE(aInstance);

    return efr32StartEnergyScan(ENERGY_SCAN_MODE_ASYNC, aScanChannel, (RAIL_Time_t)aScanDuration * US_IN_MS);
}

//------------------------------------------------------------------------------
// Radio Config: Thread 1.2 transmit security support

#if (OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2)
void otPlatRadioSetMacKey(otInstance             *aInstance,
                          uint8_t                 aKeyIdMode,
                          uint8_t                 aKeyId,
                          const otMacKeyMaterial *aPrevKey,
                          const otMacKeyMaterial *aCurrKey,
                          const otMacKeyMaterial *aNextKey,
                          otRadioKeyType          aKeyType)
{
    uint8_t iid = otNcpPlatGetCurCommandIid();

    OT_UNUSED_VARIABLE(aInstance);
    OT_UNUSED_VARIABLE(aKeyIdMode);
    OT_UNUSED_VARIABLE(aKeyType);

    OT_ASSERT(aPrevKey != NULL && aCurrKey != NULL && aNextKey != NULL);

    sMacKeys[iid].keyId = aKeyId;
    memcpy(&sMacKeys[iid].keys[MAC_KEY_PREV], aPrevKey, sizeof(otMacKeyMaterial));
    memcpy(&sMacKeys[iid].keys[MAC_KEY_CURRENT], aCurrKey, sizeof(otMacKeyMaterial));
    memcpy(&sMacKeys[iid].keys[MAC_KEY_NEXT], aNextKey, sizeof(otMacKeyMaterial));

#if defined(_SILICON_LABS_32B_SERIES_2) && (OPENTHREAD_CONFIG_CRYPTO_LIB == OPENTHREAD_CONFIG_CRYPTO_LIB_PSA)
    size_t aKeyLen = 0;
    otError error = OT_ERROR_NONE;

    error = otPlatCryptoExportKey(sMacKeys[iid].keys[MAC_KEY_PREV].mKeyMaterial.mKeyRef,
                                  sMacKeys[iid].keys[MAC_KEY_PREV].mKeyMaterial.mKey.m8,
                                  sizeof(sMacKeys[iid].keys[MAC_KEY_PREV]),
                                  &aKeyLen);
    OT_ASSERT(error == OT_ERROR_NONE);

    error = otPlatCryptoExportKey(sMacKeys[iid].keys[MAC_KEY_CURRENT].mKeyMaterial.mKeyRef,
                                  sMacKeys[iid].keys[MAC_KEY_CURRENT].mKeyMaterial.mKey.m8,
                                  sizeof(sMacKeys[iid].keys[MAC_KEY_CURRENT]),
                                  &aKeyLen);
    OT_ASSERT(error == OT_ERROR_NONE);

    error = otPlatCryptoExportKey(sMacKeys[iid].keys[MAC_KEY_NEXT].mKeyMaterial.mKeyRef,
                                  sMacKeys[iid].keys[MAC_KEY_NEXT].mKeyMaterial.mKey.m8,
                                  sizeof(sMacKeys[iid].keys[MAC_KEY_NEXT]),
                                  &aKeyLen);
    OT_ASSERT(error == OT_ERROR_NONE);

#endif
}

void otPlatRadioSetMacFrameCounter(otInstance *aInstance, uint32_t aMacFrameCounter)
{
    uint8_t iid = otNcpPlatGetCurCommandIid();

    OT_UNUSED_VARIABLE(aInstance);

    CORE_DECLARE_IRQ_STATE;
    CORE_ENTER_ATOMIC();

    sMacKeys[iid].macFrameCounter = aMacFrameCounter;

    CORE_EXIT_ATOMIC();
}

void otPlatRadioSetMacFrameCounterIfLarger(otInstance *aInstance, uint32_t aMacFrameCounter)
{
    uint8_t iid = otNcpPlatGetCurCommandIid();

    OT_UNUSED_VARIABLE(aInstance);

    CORE_DECLARE_IRQ_STATE;
    CORE_ENTER_ATOMIC();

    if (aMacFrameCounter > sMacKeys[iid].macFrameCounter)
    {
        sMacKeys[iid].macFrameCounter = aMacFrameCounter;
    }

    CORE_EXIT_ATOMIC();
}

//------------------------------------------------------------------------------
// Radio Config: Enhanced Acks, CSL

#if OPENTHREAD_CONFIG_MAC_CSL_RECEIVER_ENABLE
otError otPlatRadioEnableCsl(otInstance         *aInstance,
                             uint32_t            aCslPeriod,
                             otShortAddress      aShortAddr,
                             const otExtAddress *aExtAddr)
{
    OT_UNUSED_VARIABLE(aInstance);
    OT_UNUSED_VARIABLE(aShortAddr);
    OT_UNUSED_VARIABLE(aExtAddr);

    sCslPeriod = aCslPeriod;

    return OT_ERROR_NONE;
}

void otPlatRadioUpdateCslSampleTime(otInstance *aInstance, uint32_t aCslSampleTime)
{
    OT_UNUSED_VARIABLE(aInstance);

    sCslSampleTime = aCslSampleTime;
}

#endif // OPENTHREAD_CONFIG_MAC_CSL_RECEIVER_ENABLE

uint8_t otPlatRadioGetCslAccuracy(otInstance *aInstance)
{
    OT_UNUSED_VARIABLE(aInstance);

    return otPlatTimeGetXtalAccuracy();
}

uint8_t otPlatRadioGetCslUncertainty(otInstance *aInstance)
{
    OT_UNUSED_VARIABLE(aInstance);

    return SL_OPENTHREAD_CSL_TX_UNCERTAINTY;
}

//------------------------------------------------------------------------------
// Radio Config: Link Metrics

#if OPENTHREAD_CONFIG_MLE_LINK_METRICS_SUBJECT_ENABLE
otError otPlatRadioConfigureEnhAckProbing(otInstance          *aInstance,
                                          otLinkMetrics        aLinkMetrics,
                                          const otShortAddress aShortAddress,
                                          const otExtAddress  *aExtAddress)
{
    OT_UNUSED_VARIABLE(aInstance);

    return otLinkMetricsConfigureEnhAckProbing(aShortAddress, aExtAddress, aLinkMetrics);
}
#endif
#endif // (OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2)

#if OPENTHREAD_CONFIG_PLATFORM_RADIO_COEX_ENABLE
otError otPlatRadioSetCoexEnabled(otInstance *aInstance, bool aEnabled)
{
    OT_UNUSED_VARIABLE(aInstance);
    sl_status_t status = sl_rail_util_coex_set_enable(aEnabled);
    if (aEnabled && !sl_rail_util_coex_is_enabled())
    {
        otLogInfoPlat("Coexistence GPIO configurations not set");
        return OT_ERROR_FAILED;
    }
    sRadioCoexEnabled = aEnabled;
    return (status != SL_STATUS_OK) ? OT_ERROR_FAILED : OT_ERROR_NONE;
}

bool otPlatRadioIsCoexEnabled(otInstance *aInstance)
{
    OT_UNUSED_VARIABLE(aInstance);
    return (sRadioCoexEnabled && sl_rail_util_coex_is_enabled());
}

otError otPlatRadioGetCoexMetrics(otInstance *aInstance, otRadioCoexMetrics *aCoexMetrics)
{
    OT_UNUSED_VARIABLE(aInstance);
    otError error = OT_ERROR_NONE;

    otEXPECT_ACTION(aCoexMetrics != NULL, error = OT_ERROR_INVALID_ARGS);

    memset(aCoexMetrics, 0, sizeof(otRadioCoexMetrics));
    // TO DO:
    // Tracking coex metrics with detailed granularity currently
    // not implemented.
    // memcpy(aCoexMetrics, &sCoexMetrics, sizeof(otRadioCoexMetrics));
exit:
    return error;
}
#endif // OPENTHREAD_CONFIG_PLATFORM_RADIO_COEX_ENABLE

#if (OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2)
//------------------------------------------------------------------------------
// Radio implementation: Enhanced ACKs, CSL

// Return false if we should generate an immediate ACK
// Return true otherwise
static bool writeIeee802154EnhancedAck(RAIL_Handle_t        aRailHandle,
                                       RAIL_RxPacketInfo_t *packetInfoForEnhAck,
                                       uint8_t             *initialPktReadBytes,
                                       uint8_t             *receivedPsdu)
{
    // RAIL will generate an Immediate ACK for us.
    // For an Enhanced ACK, we need to generate the whole packet ourselves.

    // An 802.15.4 packet from RAIL should look like:
    // 1/2 |   1/2  | 0/1  |  0/2   | 0/2/8  |  0/2   | 0/2/8  |   14
    // PHR | MacFCF | Seq# | DstPan | DstAdr | SrcPan | SrcAdr | SecHdr

    // With RAIL_IEEE802154_EnableEarlyFramePending(), RAIL_EVENT_IEEE802154_DATA_REQUEST_COMMAND
    // is triggered after receiving through the SrcAdr field of Version 0/1 packets,
    // and after receiving through the SecHdr for Version 2 packets.

    otRadioFrame receivedFrame, enhAckFrame;
    uint8_t      enhAckPsdu[IEEE802154_MAX_LENGTH];

#define EARLY_FRAME_PENDING_EXPECTED_BYTES (2U + 2U + 1U + 2U + 8U + 2U + 8U + 14U)
#define FINAL_PACKET_LENGTH_WITH_IE (EARLY_FRAME_PENDING_EXPECTED_BYTES + OT_ACK_IE_MAX_SIZE)

    otEXPECT((packetInfoForEnhAck != NULL) && (initialPktReadBytes != NULL) && (receivedPsdu != NULL));

    *initialPktReadBytes = readInitialPacketData(packetInfoForEnhAck,
                                                 EARLY_FRAME_PENDING_EXPECTED_BYTES,
                                                 (PHY_HEADER_SIZE + 2),
                                                 receivedPsdu,
                                                 FINAL_PACKET_LENGTH_WITH_IE);

    uint8_t iid = INVALID_VALUE;

    if (*initialPktReadBytes == 0U)
    {
        return true; // Nothing to read, which means generating an immediate ACK is also pointless
    }

    receivedFrame.mPsdu     = receivedPsdu + PHY_HEADER_SIZE;
    receivedFrame.mLength   = *initialPktReadBytes - PHY_HEADER_SIZE;
    enhAckFrame.mPsdu       = enhAckPsdu + PHY_HEADER_SIZE;

    if (! otMacFrameIsVersion2015(&receivedFrame))
    {
        return false;
    }

    otMacAddress aSrcAddress;
    uint8_t      linkMetricsDataLen = 0;
    uint8_t     *dataPtr            = NULL;
    bool         setFramePending    = false;

#if _SILICON_LABS_32B_SERIES_1_CONFIG == 1 && OPENTHREAD_RADIO && OPENTHREAD_CONFIG_MULTIPAN_RCP_ENABLE == 1
    otPanId destPanId;

    destPanId = efr32GetDstPanId(&receivedFrame);
    iid       = utilsSoftSrcMatchFindIidFromPanId(destPanId);
#else
    iid = getIidFromFilterMask(packetInfoForEnhAck->filterMask);
#endif

    otMacFrameGetSrcAddr(&receivedFrame, &aSrcAddress);

    if (sIsSrcMatchEnabled && (aSrcAddress.mType != OT_MAC_ADDRESS_TYPE_NONE))
    {
#if _SILICON_LABS_32B_SERIES_1_CONFIG == 1 && OPENTHREAD_RADIO && OPENTHREAD_CONFIG_MULTIPAN_RCP_ENABLE == 1
        if (iid == 0 || iid == INVALID_VALUE) // search all tables only if we cant find the iid based on dest panid
        {
            for (uint8_t i = 1; i <= RADIO_CONFIG_SRC_MATCH_PANID_NUM; i++)
            {
                setFramePending = (aSrcAddress.mType == OT_MAC_ADDRESS_TYPE_EXTENDED
                                       ? (utilsSoftSrcMatchExtFindEntry(i, &aSrcAddress.mAddress.mExtAddress) >= 0)
                                       : (utilsSoftSrcMatchShortFindEntry(i, aSrcAddress.mAddress.mShortAddress) >= 0));
                if (setFramePending)
                {
                    break;
                }
            }
        }
        else
#endif
        {
            setFramePending = (aSrcAddress.mType == OT_MAC_ADDRESS_TYPE_EXTENDED
                                   ? (utilsSoftSrcMatchExtFindEntry(iid, &aSrcAddress.mAddress.mExtAddress) >= 0)
                                   : (utilsSoftSrcMatchShortFindEntry(iid, aSrcAddress.mAddress.mShortAddress) >= 0));
        }
    }

    // Generate our IE header.
    // Write IE data for enhanced ACK (link metrics + allocate bytes for CSL)

#if OPENTHREAD_CONFIG_MLE_LINK_METRICS_SUBJECT_ENABLE
    uint8_t linkMetricsData[OT_ENH_PROBING_IE_DATA_MAX_SIZE];

    linkMetricsDataLen = otLinkMetricsEnhAckGenData(&aSrcAddress, sLastLqi, sLastRssi, linkMetricsData);

    if (linkMetricsDataLen > 0)
    {
        dataPtr = linkMetricsData;
    }
#endif

    sAckIeDataLength = generateAckIeData(dataPtr, linkMetricsDataLen);

    otEXPECT(otMacFrameGenerateEnhAck(&receivedFrame, setFramePending, sAckIeData, sAckIeDataLength, &enhAckFrame)
             == OT_ERROR_NONE);

#if OPENTHREAD_CONFIG_MAC_CSL_RECEIVER_ENABLE
    if (sCslPeriod > 0)
    {
        // Calculate time in the future where the SHR is done being sent out
        uint32_t ackShrDoneTime = // Currently partially received packet's SHR time
                                  (otPlatAlarmMicroGetNow() - (packetInfoForEnhAck->packetBytes * OT_RADIO_SYMBOL_TIME * 2)
                                  // PHR of this packet
                                  + (PHY_HEADER_SIZE * OT_RADIO_SYMBOL_TIME * 2)
                                  // Received frame's expected time in the PHR
                                  + (receivedFrame.mLength * OT_RADIO_SYMBOL_TIME * 2)
                                  // rxToTx turnaround time
                                  + sRailIeee802154Config.timings.rxToTx
                                  // PHR time of the ACK
                                  + (PHY_HEADER_SIZE * OT_RADIO_SYMBOL_TIME * 2)
                                  // SHR time of the ACK
                                  + (SHR_SIZE * OT_RADIO_SYMBOL_TIME * 2));

        // Update IE data in the 802.15.4 header with the newest CSL period / phase
        otMacFrameSetCslIe(&enhAckFrame, (uint16_t)sCslPeriod, getCslPhase(ackShrDoneTime));
    }
#endif

    if (otMacFrameIsSecurityEnabled(&enhAckFrame))
    {
        otEXPECT(radioProcessTransmitSecurity(&enhAckFrame, iid) == OT_ERROR_NONE);
    }

    // Before we're done, store some important info in reserved bits in the
    // MAC header (cleared later)
    // Check whether frame pending is set.
    // Check whether enhanced ACK is secured.
    otEXPECT((skipRxPacketLengthBytes(packetInfoForEnhAck)) == OT_ERROR_NONE);
    uint8_t *macFcfPointer =
        ((packetInfoForEnhAck->firstPortionBytes == 0) ? (uint8_t *)packetInfoForEnhAck->lastPortionData
                                                       : (uint8_t *)packetInfoForEnhAck->firstPortionData);

    if (otMacFrameIsSecurityEnabled(&enhAckFrame))
    {
        *macFcfPointer |= IEEE802154_SECURED_OUTGOING_ENHANCED_ACK;
    }

    if (setFramePending)
    {
        *macFcfPointer |= IEEE802154_FRAME_PENDING_SET_IN_OUTGOING_ACK;
    }

    // Fill in PHR now that we know Enh-ACK's length
    if (PHY_HEADER_SIZE == 2U) // Not true till SubGhz implementation is in place
    {
        enhAckPsdu[0] = (0x08U /*FCS=2byte*/ | 0x10U /*Whiten=enabled*/);
        enhAckPsdu[1] = (uint8_t)(__RBIT(enhAckFrame.mLength) >> 24);
    }
    else
    {
        enhAckPsdu[0] = enhAckFrame.mLength;
    }

    RAIL_Status_t enhAckStatus = RAIL_IEEE802154_WriteEnhAck(aRailHandle, enhAckPsdu, enhAckFrame.mLength);
#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
    otEXPECT_ACTION(enhAckStatus == RAIL_STATUS_NO_ERROR, railDebugCounters.mRailEventsEnhAckTxFailed++);
#else
    otEXPECT(enhAckStatus == RAIL_STATUS_NO_ERROR);
#endif

exit:
    return true;
}
#endif // (OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2)

//------------------------------------------------------------------------------
// RAIL callbacks

static void dataRequestCommandCallback(RAIL_Handle_t aRailHandle)
{
#define MAX_EXPECTED_BYTES (2U + 2U + 1U) // PHR + FCF + DSN

    uint8_t             receivedPsdu[IEEE802154_MAX_LENGTH];
    uint8_t             pktOffset = PHY_HEADER_SIZE;
    uint8_t             initialPktReadBytes;
    RAIL_RxPacketInfo_t packetInfo;

    // This callback occurs after the address fields of an incoming
    // ACK-requesting CMD or DATA frame have been received and we
    // can do a frame pending check.  We must also figure out what
    // kind of ACK is being requested -- Immediate or Enhanced.

#if (OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2)
    if (writeIeee802154EnhancedAck(aRailHandle, &packetInfo, &initialPktReadBytes, receivedPsdu))
    {
        // We also return true above if there were failures in
        // generating an enhanced ACK.
        return;
    }
#else
    initialPktReadBytes =
        readInitialPacketData(&packetInfo, MAX_EXPECTED_BYTES, pktOffset + 2, receivedPsdu, MAX_EXPECTED_BYTES);
#endif

    // Calculate frame pending for immediate-ACK
    // If not, RAIL will send an immediate ACK, but we need to do FP lookup.
    RAIL_Status_t status = RAIL_STATUS_NO_ERROR;

    // Check if we read the FCF, if not, set macFcf to 0
    uint16_t macFcf = (initialPktReadBytes <= pktOffset) ? 0U : receivedPsdu[pktOffset];

    bool framePendingSet = false;

    if (sIsSrcMatchEnabled)
    {
        RAIL_IEEE802154_Address_t sourceAddress;

        status = RAIL_IEEE802154_GetAddress(aRailHandle, &sourceAddress);
        otEXPECT(status == RAIL_STATUS_NO_ERROR);

        uint8_t iid = getIidFromFilterMask(packetInfo.filterMask);
#if _SILICON_LABS_32B_SERIES_1_CONFIG == 1 && OPENTHREAD_RADIO && OPENTHREAD_CONFIG_MULTIPAN_RCP_ENABLE == 1
        if (iid == 0) // on MG1 the RAIL filter mask doesn't work so search all tables
        {
            for (uint8_t i = 1; i <= RADIO_CONFIG_SRC_MATCH_PANID_NUM; i++)
            {
                framePendingSet =
                    (sourceAddress.length == RAIL_IEEE802154_LongAddress
                         ? (utilsSoftSrcMatchExtFindEntry(i, (otExtAddress *)sourceAddress.longAddress) >= 0)
                         : (utilsSoftSrcMatchShortFindEntry(i, sourceAddress.shortAddress) >= 0));
                if (framePendingSet)
                {
                    status = RAIL_IEEE802154_SetFramePending(aRailHandle);
                    otEXPECT(status == RAIL_STATUS_NO_ERROR);
                    break;
                }
            }
        }
        else
#endif
            if ((sourceAddress.length == RAIL_IEEE802154_LongAddress
                 && utilsSoftSrcMatchExtFindEntry(iid, (otExtAddress *)sourceAddress.longAddress) >= 0)
                || (sourceAddress.length == RAIL_IEEE802154_ShortAddress
                    && utilsSoftSrcMatchShortFindEntry(iid, sourceAddress.shortAddress) >= 0))
        {
            status = RAIL_IEEE802154_SetFramePending(aRailHandle);
            otEXPECT(status == RAIL_STATUS_NO_ERROR);
            framePendingSet = true;
        }
    }
    else if ((macFcf & IEEE802154_FRAME_TYPE_MASK) != IEEE802154_FRAME_TYPE_DATA)
    {
        status = RAIL_IEEE802154_SetFramePending(aRailHandle);
        otEXPECT(status == RAIL_STATUS_NO_ERROR);
        framePendingSet = true;
    }

    if (framePendingSet)
    {
        // Store whether frame pending was set in the outgoing ACK in a reserved
        // bit of the MAC header (cleared later)

        otEXPECT((skipRxPacketLengthBytes(&packetInfo)) == OT_ERROR_NONE);
        uint8_t *macFcfPointer = ((packetInfo.firstPortionBytes == 0) ? (uint8_t *)packetInfo.lastPortionData
                                                                      : (uint8_t *)packetInfo.firstPortionData);
        *macFcfPointer |= IEEE802154_FRAME_PENDING_SET_IN_OUTGOING_ACK;
    }

exit:
    if (status == RAIL_STATUS_INVALID_STATE)
    {
        otLogWarnPlat("Too late to modify outgoing FP");
    }
    else
    {
        OT_ASSERT(status == RAIL_STATUS_NO_ERROR);
    }
}

static void packetReceivedCallback(RAIL_RxPacketHandle_t packetHandle)
{
    RAIL_RxPacketInfo_t    packetInfo;
    RAIL_RxPacketDetails_t packetDetails;
    uint16_t               length = 0;
    bool                   framePendingInAck = false;
    bool                   dropPacket = false;
    uint8_t                iid = 0;
    uint8_t                *psdu = sReceiveAckFrame.mPsdu;
#if SL_OPENTHREAD_RADIO_RX_BUFFER_COUNT > 1
    rxBufferIndex_t        receiveBufferInUse = SL_OPENTHREAD_RADIO_RX_BUFFER_COUNT;
#endif

    packetHandle = RAIL_GetRxPacketInfo(gRailHandle, packetHandle, &packetInfo);
    otEXPECT_ACTION((packetHandle != RAIL_RX_PACKET_HANDLE_INVALID
                     && packetInfo.packetStatus == RAIL_RX_PACKET_READY_SUCCESS),
                    dropPacket = true);

    otEXPECT_ACTION(validatePacketDetails(packetHandle, &packetDetails, &packetInfo, &length),
                    dropPacket = true);

    otEXPECT_ACTION((skipRxPacketLengthBytes(&packetInfo)) == OT_ERROR_NONE,
                    dropPacket = true);

    uint8_t macFcf =
        ((packetInfo.firstPortionBytes == 0) ? packetInfo.lastPortionData[0] : packetInfo.firstPortionData[0]);

    iid = getIidFromFilterMask(packetInfo.filterMask);

#if SL_OPENTHREAD_RADIO_RX_BUFFER_COUNT > 1
    if(!packetDetails.isAck)
    { 
        receiveBufferInUse = getFreeBufferIndex();
        otEXPECT_ACTION(receiveBufferInUse < SL_OPENTHREAD_RADIO_RX_BUFFER_COUNT, dropPacket = true);
        psdu = sReceivePacket[receiveBufferInUse].psdu;
    }
#endif

    if (packetDetails.isAck)
    {
        otEXPECT_ACTION((length >= IEEE802154_MIN_LENGTH
                         && (macFcf & IEEE802154_FRAME_TYPE_MASK)
                             == IEEE802154_FRAME_TYPE_ACK),
                        dropPacket = true);

        // read packet
        RAIL_CopyRxPacket(psdu, &packetInfo);

#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
        railDebugCounters.mRailEventAcksReceived++;
#endif
        sReceiveAckFrame.mLength = length;

        // Releasing the ACK frames here, ensures that the main thread (processRxPackets)
        // is not wasting cycles, releasing the ACK frames from the Rx FIFO queue.
        RAIL_ReleaseRxPacket(gRailHandle, packetHandle);

        (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_ENDED, (uint32_t)isReceivingFrame());

        if (txWaitingForAck()
            && (psdu[IEEE802154_DSN_OFFSET] == sTransmitFrame.mPsdu[IEEE802154_DSN_OFFSET]))
        {
            otEXPECT_ACTION(validatePacketTimestamp(&packetDetails, length), dropPacket = true);
            updateRxFrameDetails(&packetDetails, false, false, iid, INVALID_VALUE);

            // Processing the ACK frame in ISR context avoids the Tx state to be messed up,
            // in case the Rx FIFO queue gets wiped out in a DMP situation.
            setInternalFlag(EVENT_TX_SUCCESS, true);
            setInternalFlag(FLAG_WAITING_FOR_ACK | FLAG_ONGOING_TX_DATA, false);

            framePendingInAck = ((macFcf & IEEE802154_FRAME_FLAG_FRAME_PENDING) != 0);
            (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_ACK_RECEIVED, (uint32_t)framePendingInAck);

            if (txIsDataRequest() && framePendingInAck)
            {
                emPendingData = true;
            }
        }
        // Yield the radio upon receiving an ACK as long as it is not related to
        // a data request.
        if (!txIsDataRequest())
        {
            RAIL_YieldRadio(gRailHandle);
        }
    }
    else
    {
        otEXPECT_ACTION(sPromiscuous || (length >= IEEE802154_MIN_DATA_LENGTH), dropPacket = true);

#if SL_OPENTHREAD_RADIO_RX_BUFFER_COUNT > 1
        // read packet
        RAIL_CopyRxPacket(psdu, &packetInfo);
        RAIL_ReleaseRxPacket(gRailHandle, packetHandle);

        otEXPECT_ACTION(validatePacketTimestamp(&packetDetails, length), dropPacket = true);

        reserveNextRxBuffer();
        sReceivePacket[receiveBufferInUse].packetInfo.length  = length;
        sReceivePacket[receiveBufferInUse].packetInfo.channel = packetDetails.channel;
        sReceivePacket[receiveBufferInUse].packetInfo.rssi = packetDetails.rssi;
        sReceivePacket[receiveBufferInUse].packetInfo.lqi = packetDetails.lqi;
        sReceivePacket[receiveBufferInUse].packetInfo.timestamp = packetDetails.timeReceived.packetTime;
        sReceivePacket[receiveBufferInUse].packetInfo.iid = iid;

#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
        railDebugCounters.mRailPlatRadioReceiveProcessedCount++;
#endif
#endif

        if (macFcf & IEEE802154_FRAME_FLAG_ACK_REQUIRED)
        {
            (void)handlePhyStackEvent((RAIL_IsRxAutoAckPaused(gRailHandle)
                                           ? SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_ACK_BLOCKED
                                           : SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_ACKING),
                                      (uint32_t)isReceivingFrame());
            setInternalFlag(FLAG_ONGOING_TX_ACK, true);
        }
        else
        {
            (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_ENDED, (uint32_t)isReceivingFrame());
            // We received a frame that does not require an ACK as result of a data
            // poll: we yield the radio here.
            if (emPendingData)
            {
                RAIL_YieldRadio(gRailHandle);
                emPendingData = false;
            }
        }
    }
exit:
    if (dropPacket) {
        // Release the corrupted packet that won't be processed further
        (void) RAIL_ReleaseRxPacket(gRailHandle, packetHandle);
        (void) handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_CORRUPTED,
                                   (uint32_t) isReceivingFrame());
    }	
}

static void packetSentCallback(bool isAck)
{
    if (isAck)
    {
        // We successfully sent out an ACK.
        setInternalFlag(FLAG_ONGOING_TX_ACK, false);
        // We acked the packet we received after a poll: we can yield now.
        if (emPendingData)
        {
            RAIL_YieldRadio(gRailHandle);
            emPendingData = false;
        }
    }
    else if (getInternalFlag(FLAG_ONGOING_TX_DATA))
    {
        setInternalFlag(FLAG_CURRENT_TX_USE_CSMA, false);

        if (txWaitingForAck())
        {
            setInternalFlag(FLAG_WAITING_FOR_ACK, true);
            (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_ACK_WAITING, 0U);
        }
        else
        {
            (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_ENDED, 0U);
            RAIL_YieldRadio(gRailHandle);
            setInternalFlag(EVENT_TX_SUCCESS, true);
            //Broadcast packet clear the ONGOING flag here.
            setInternalFlag(FLAG_ONGOING_TX_DATA, false);
        }
#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
        railDebugCounters.mRailEventPacketSent++;
#endif
    }
}

static void txFailedCallback(bool isAck, uint32_t status)
{
    if (isAck)
    {
        setInternalFlag(FLAG_ONGOING_TX_ACK, false);
    }
    else if (getInternalFlag(FLAG_ONGOING_TX_DATA))
    {
        if (status == EVENT_TX_CCA_FAILED)
        {
            setInternalFlag(EVENT_TX_CCA_FAILED, true);
            setInternalFlag(FLAG_CURRENT_TX_USE_CSMA, false);
#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
            railDebugCounters.mRailEventChannelBusy++;
#endif
        }
        else
        {
            setInternalFlag(EVENT_TX_FAILED, true);
#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
            railDebugCounters.mRailEventTxAbort++;
#endif
        }
        setInternalFlag((FLAG_ONGOING_TX_DATA | FLAG_WAITING_FOR_ACK), false);
        RAIL_YieldRadio(gRailHandle);
    }
}

static void ackTimeoutCallback(void)
{
    OT_ASSERT(txWaitingForAck());
    OT_ASSERT(getInternalFlag(FLAG_WAITING_FOR_ACK));

    setInternalFlag(EVENT_TX_NO_ACK, true);
    setInternalFlag(FLAG_ONGOING_TX_DATA, false);

#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
    railDebugCounters.mRailEventNoAck++;
#endif

#ifdef SL_CATALOG_RAIL_UTIL_ANT_DIV_PRESENT
    // If antenna diversity is enabled toggle the selected antenna.
    sl_rail_util_ant_div_toggle_tx_antenna();
#endif // SL_CATALOG_RAIL_UTIL_ANT_DIV_PRESENT
    // TO DO: Check if we have an OT function that
    // provides the number of mac retry attempts left
    (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_ACK_TIMEDOUT, 0);

    setInternalFlag(FLAG_WAITING_FOR_ACK, false);
    RAIL_YieldRadio(gRailHandle);
    emPendingData = false;
}

static void schedulerEventCallback(RAIL_Handle_t aRailHandle)
{
    RAIL_SchedulerStatus_t status = RAIL_GetSchedulerStatus(aRailHandle);
    bool transmitBusy = getInternalFlag(FLAG_ONGOING_TX_DATA);

    OT_ASSERT(status != RAIL_SCHEDULER_STATUS_INTERNAL_ERROR);

    if (status == RAIL_SCHEDULER_STATUS_CCA_CSMA_TX_FAIL || status == RAIL_SCHEDULER_STATUS_SINGLE_TX_FAIL
        || status == RAIL_SCHEDULER_STATUS_SCHEDULED_TX_FAIL
        || (status == RAIL_SCHEDULER_STATUS_SCHEDULE_FAIL && transmitBusy)
        || (status == RAIL_SCHEDULER_STATUS_EVENT_INTERRUPTED && transmitBusy))
    {
        if (getInternalFlag(FLAG_ONGOING_TX_ACK))
        {
            (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_ACK_ABORTED, (uint32_t)isReceivingFrame());
            txFailedCallback(true, EVENT_TX_FAILED);
        }
        // We were in the process of TXing a data frame, treat it as a CCA_FAIL.
        if (getInternalFlag(FLAG_ONGOING_TX_DATA))
        {
            (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_BLOCKED, (uint32_t)txWaitingForAck());
            txFailedCallback(false, EVENT_TX_CCA_FAILED);
        }

#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
        railDebugCounters.mRailEventSchedulerStatusError++;
#endif
    }
    else if (status == RAIL_SCHEDULER_STATUS_AVERAGE_RSSI_FAIL
            || (status == RAIL_SCHEDULER_STATUS_SCHEDULE_FAIL && sEnergyScanStatus == ENERGY_SCAN_STATUS_IN_PROGRESS))
    {
        energyScanComplete(OT_RADIO_RSSI_INVALID);
    }
}

static void configUnscheduledCallback(void)
{
    // We are waiting for an ACK: we will never get the ACK we were waiting for.
    // We want to call ackTimeoutCallback() only if the PACKET_SENT event
    // already fired (which would clear the FLAG_ONGOING_TX_DATA flag).
    if (getInternalFlag(FLAG_WAITING_FOR_ACK))
    {
        ackTimeoutCallback();
    }

    // We are about to send an ACK, which it won't happen.
    if (getInternalFlag(FLAG_ONGOING_TX_ACK))
    {
      txFailedCallback(true, EVENT_TX_FAILED);
    }
}

static void RAILCb_Generic(RAIL_Handle_t aRailHandle, RAIL_Events_t aEvents)
{
#ifdef SL_CATALOG_RAIL_UTIL_IEEE802154_STACK_EVENT_PRESENT
    if (aEvents & (RAIL_EVENT_RX_SYNC1_DETECT | RAIL_EVENT_RX_SYNC2_DETECT))
    {
        (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_STARTED, (uint32_t)isReceivingFrame());
    }
#endif // SL_CATALOG_RAIL_UTIL_IEEE802154_STACK_EVENT_PRESENT

#ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
    if (aEvents & RAIL_EVENT_SIGNAL_DETECTED)
    {
        (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_SIGNAL_DETECTED, 0U);
    }
#endif // SL_CATALOG_RAIL_UTIL_COEX_PRESENT

    if ((aEvents & RAIL_EVENT_IEEE802154_DATA_REQUEST_COMMAND)
#ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
        && !RAIL_IsRxAutoAckPaused(aRailHandle)
#endif // SL_CATALOG_RAIL_UTIL_COEX_PRESENT
    )
    {
        dataRequestCommandCallback(aRailHandle);
    }

#ifdef SL_CATALOG_RAIL_UTIL_IEEE802154_STACK_EVENT_PRESENT
    if (aEvents & RAIL_EVENT_RX_FILTER_PASSED)
    {
        (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_ACCEPTED, (uint32_t)isReceivingFrame());
    }
#endif // SL_CATALOG_RAIL_UTIL_IEEE802154_STACK_EVENT_PRESENT

    if (aEvents & RAIL_EVENT_TX_PACKET_SENT)
    {
        packetSentCallback(false);
    }
    else if (aEvents & RAIL_EVENT_TX_CHANNEL_BUSY)
    {
        (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_BLOCKED, (uint32_t) txWaitingForAck());
        txFailedCallback(false, EVENT_TX_CCA_FAILED);
    }
    else if (aEvents & RAIL_EVENT_TX_BLOCKED)
    {
        (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_BLOCKED, (uint32_t) txWaitingForAck());
        txFailedCallback(false, EVENT_TX_FAILED);
    }
    else if (aEvents & (RAIL_EVENT_TX_UNDERFLOW | RAIL_EVENT_TX_ABORTED))
    {
        (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_ABORTED, (uint32_t) txWaitingForAck());
        txFailedCallback(false, EVENT_TX_FAILED);
    }
    else
    {
        // Pre-completion aEvents are processed in their logical order:
#ifdef SL_CATALOG_RAIL_UTIL_IEEE802154_STACK_EVENT_PRESENT
        if (aEvents & RAIL_EVENT_TX_START_CCA)
        {
            // We are starting RXWARM for a CCA check
            (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_CCA_SOON, 0U);
        }
        if (aEvents & RAIL_EVENT_TX_CCA_RETRY)
        {
            // We failed a CCA check and need to retry
            (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_CCA_BUSY, 0U);
        }
        if (aEvents & RAIL_EVENT_TX_CHANNEL_CLEAR)
        {
            // We're going on-air
            (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_STARTED, 0U);
        }
#endif // SL_CATALOG_RAIL_UTIL_IEEE802154_STACK_EVENT_PRESENT
    }

#if OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2

    // Note: RAIL_EVENT_SCHEDULED_TX_STARTED and RAIL_EVENT_SCHEDULED_RX_STARTED have the
    // same numerical value because one cannot schedule both RX and TX simultaneously.
    // Have to take due care to check for these statuses depending on whether we're
    // scheduling a transmit or receive.  Therefore, we're using an internal flag
    // 'FLAG_SCHEDULED_RX_PENDING' to track our scheduled-receive state.

    if (getInternalFlag(FLAG_SCHEDULED_RX_PENDING))
    {
        if (aEvents & RAIL_EVENT_SCHEDULED_RX_STARTED)
        {
            setInternalFlag(EVENT_SCHEDULED_RX_STARTED, true);
        }

        // Once done with scheduled receive, clear internal scheduled-rx flag and idle.
        // If we miss a scheduled receive, let application schedule another.
        if (aEvents & RAIL_EVENT_RX_SCHEDULED_RX_END || aEvents & RAIL_EVENT_RX_SCHEDULED_RX_MISSED)
        {
            setInternalFlag(FLAG_SCHEDULED_RX_PENDING, false);
            setInternalFlag(EVENT_SCHEDULED_RX_STARTED, false);
            radioSetIdle();
        }
    }
    else
    {
        if (aEvents & RAIL_EVENT_SCHEDULED_TX_STARTED)
        {
#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
            railDebugCounters.mRailEventsScheduledTxStartedCount++;
#endif
        }
        else if (aEvents & RAIL_EVENT_TX_SCHEDULED_TX_MISSED)
        {
            txFailedCallback(false, EVENT_TX_SCHEDULER_ERROR);
        }
    }
#endif // OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2

    if (aEvents & RAIL_EVENT_RX_PACKET_RECEIVED)
    {
        packetReceivedCallback(RAIL_HoldRxPacket(aRailHandle));
#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
        railDebugCounters.mRailEventPacketReceived++;
#endif
    }

#ifdef SL_CATALOG_RAIL_UTIL_IEEE802154_STACK_EVENT_PRESENT
    if (aEvents & RAIL_EVENT_RX_FRAME_ERROR)
    {
        (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_CORRUPTED, (uint32_t)isReceivingFrame());
    }
    // The following 3 events cause us to not receive a packet
    if (aEvents & (RAIL_EVENT_RX_PACKET_ABORTED | RAIL_EVENT_RX_ADDRESS_FILTERED | RAIL_EVENT_RX_FIFO_OVERFLOW))
    {
        (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_FILTERED, (uint32_t)isReceivingFrame());
    }
#endif // SL_CATALOG_RAIL_UTIL_IEEE802154_STACK_EVENT_PRESENT

    if (aEvents & RAIL_EVENT_TXACK_PACKET_SENT)
    {
        (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_ACK_SENT, (uint32_t)isReceivingFrame());
        packetSentCallback(true);
    }
    if (aEvents & (RAIL_EVENT_TXACK_ABORTED | RAIL_EVENT_TXACK_UNDERFLOW))
    {
        (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_ACK_ABORTED, (uint32_t)isReceivingFrame());
        txFailedCallback(true, 0xFF);
    }
    if (aEvents & RAIL_EVENT_TXACK_BLOCKED)
    {
        (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_ACK_BLOCKED, (uint32_t)isReceivingFrame());
        txFailedCallback(true, 0xFF);
    }
    // Deal with ACK timeout after possible RX completion in case RAIL
    // notifies us of the ACK and the timeout simultaneously -- we want
    // the ACK to win over the timeout.
    if (aEvents & RAIL_EVENT_RX_ACK_TIMEOUT)
    {
        if (getInternalFlag(FLAG_WAITING_FOR_ACK))
        {
            ackTimeoutCallback();
        }
    }

    if (aEvents & RAIL_EVENT_CONFIG_UNSCHEDULED)
    {
        (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_RX_IDLED, 0U);
        configUnscheduledCallback();
#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
        railDebugCounters.mRailEventConfigUnScheduled++;
#endif
    }

    if (aEvents & RAIL_EVENT_CONFIG_SCHEDULED)
    {
#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
        railDebugCounters.mRailEventConfigScheduled++;
#endif
    }

    if (aEvents & RAIL_EVENT_SCHEDULER_STATUS)
    {
        schedulerEventCallback(aRailHandle);
    }

    if (aEvents & RAIL_EVENT_CAL_NEEDED)
    {
        RAIL_Status_t status;

        status = RAIL_Calibrate(aRailHandle, NULL, RAIL_CAL_ALL_PENDING);
        // TODO: Non-RTOS DMP case fails
#if (!defined(SL_CATALOG_BLUETOOTH_PRESENT) || defined(SL_CATALOG_KERNEL_PRESENT))
        OT_ASSERT(status == RAIL_STATUS_NO_ERROR);
#else
        OT_UNUSED_VARIABLE(status);
#endif

#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
        railDebugCounters.mRailEventCalNeeded++;
#endif
    }

    if (aEvents & RAIL_EVENT_RSSI_AVERAGE_DONE)
    {
        const int16_t energyScanResultQuarterDbm = RAIL_GetAverageRssi(aRailHandle);
        RAIL_YieldRadio(aRailHandle);

        energyScanComplete(energyScanResultQuarterDbm == RAIL_RSSI_INVALID
                               ? OT_RADIO_RSSI_INVALID
                               : (energyScanResultQuarterDbm / QUARTER_DBM_IN_DBM));
#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
        railDebugCounters.mRailPlatRadioEnergyScanDoneCbCount++;
#endif
    }
    // scheduled and unscheduled config events happen very often, 
    // especially in a DMP situation where there is an active BLE connection.
    // Waking up the OT RTOS task on every one of these occurrences causes 
    // a lower priority CLI task to starve and makes it appear like a code lockup 
    // There is no reason to wake the OT task for these events!
    if ( !(aEvents & RAIL_EVENT_CONFIG_SCHEDULED) &&  !(aEvents & RAIL_EVENT_CONFIG_UNSCHEDULED)) {
        otSysEventSignalPending();
    }
}

//------------------------------------------------------------------------------
// Main thread packet handling

static bool validatePacketDetails(RAIL_RxPacketHandle_t   packetHandle,
                                  RAIL_RxPacketDetails_t *pPacketDetails,
                                  RAIL_RxPacketInfo_t    *pPacketInfo,
                                  uint16_t               *packetLength)
{
    bool pktValid = true;
    RAIL_Status_t rStatus;
#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
    rxDebugStep = 0;
#endif
    
    rStatus = RAIL_GetRxPacketDetailsAlt(gRailHandle, packetHandle, pPacketDetails);
    otEXPECT_ACTION(rStatus == RAIL_STATUS_NO_ERROR, pktValid = false);
#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
    rxDebugStep++;
#endif

    otEXPECT_ACTION(isFilterMaskValid(pPacketInfo->filterMask), pktValid = false);
#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
    rxDebugStep++;
#endif

    // RAIL's packetBytes includes the (1 or 2 byte) PHY header but not the 2-byte CRC.
    // We want *packetLength to match the PHY header length so we add 2 for CRC
    // and subtract the PHY header size.
    *packetLength = pPacketInfo->packetBytes + 2U - PHY_HEADER_SIZE;

    if (PHY_HEADER_SIZE == 1)
    {
        otEXPECT_ACTION(*packetLength == pPacketInfo->firstPortionData[0], pktValid = false);
    }
    else
    {
        uint8_t lengthByte =
            ((pPacketInfo->firstPortionBytes > 1) ? pPacketInfo->firstPortionData[1] : pPacketInfo->lastPortionData[0]);
        otEXPECT_ACTION(*packetLength == (uint16_t)(__RBIT(lengthByte) >> 24), pktValid = false);
    }
#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
    rxDebugStep++;
#endif

    // check the length validity of recv packet; RAIL should take care of this.
    otEXPECT_ACTION((*packetLength >= IEEE802154_MIN_LENGTH && *packetLength <= IEEE802154_MAX_LENGTH),
                    pktValid = false);
#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
    rxDebugStep++;
#endif

exit:
#if (OPENTHREAD_CONFIG_LOG_LEVEL == OT_LOG_LEVEL_DEBG)
    if (!pktValid) {
        otLogDebgPlat("RX Pkt Invalid: rStatus=0x%X, filterMask=0x%2X, pktLen=%i", rStatus, pPacketInfo->filterMask,*packetLength);
#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
        otLogDebgPlat("RX debug step=%i", rxDebugStep);
#endif
    }
#endif
    return pktValid;
}

static bool validatePacketTimestamp(RAIL_RxPacketDetails_t *pPacketDetails, uint16_t packetLength)
{
    bool rxTimestampValid = true;

    // Get the timestamp when the SFD was received
    otEXPECT_ACTION(pPacketDetails->timeReceived.timePosition != RAIL_PACKET_TIME_INVALID, rxTimestampValid = false);

    // + PHY HEADER SIZE for PHY header
    // We would not need this if PHR is not included and we want the MHR
    pPacketDetails->timeReceived.totalPacketBytes = packetLength + PHY_HEADER_SIZE;

    otEXPECT_ACTION((RAIL_GetRxTimeSyncWordEndAlt(gRailHandle, pPacketDetails) == RAIL_STATUS_NO_ERROR),
                    rxTimestampValid = false);
exit:
    return rxTimestampValid;
}

static void updateRxFrameDetails(RAIL_RxPacketDetails_t *pPacketDetails,
                                 bool                   securedOutgoingEnhancedAck,
                                 bool                   framePendingSetInOutgoingAck,
                                 uint8_t                iid,
                                 uint8_t                aReceiveBufferInUse)
{
    // Current time > sync-receive timestamp
    // Therefore lower 32 bits of current time should always be greater than lower 32 bits
    // of sync-rx timestamp unless there is a overflow.  In such cases, we do not want to
    // take overflow into consideration for sync-rx timestamp.
    uint64_t railUsTimeNow    = otPlatTimeGet();
    uint32_t railUsTimerWraps = railUsTimeNow >> 32;
    RAIL_Time_t timestamp = (pPacketDetails != NULL
                             ? pPacketDetails->timeReceived.packetTime
                             : sReceivePacket[aReceiveBufferInUse].packetInfo.timestamp);

    // Address multiple overflows, such as what would happen if the current time overflows
    // from 0x00000001FFFFFFFF to 0x0000000200000000 (leave the higher 32 bits as 0)
    if ((railUsTimeNow & 0xFFFFFFFF) <= timestamp)
    {
        railUsTimerWraps--;
    }

    if (pPacketDetails != NULL && pPacketDetails->isAck)
    {
        sReceiveAckFrame.mInfo.mRxInfo.mRssi = pPacketDetails->rssi;
        sReceiveAckFrame.mInfo.mRxInfo.mLqi  = pPacketDetails->lqi;
        sReceiveAckFrame.mInfo.mRxInfo.mTimestamp = timestamp + ((uint64_t)railUsTimerWraps << 32);
        sReceiveAckFrame.mIid = iid;
    }
    else
    {
        if (pPacketDetails != NULL)
        {
            sReceiveFrame.mInfo.mRxInfo.mRssi = pPacketDetails->rssi;
            sLastRssi = pPacketDetails->rssi;

            sReceiveFrame.mInfo.mRxInfo.mLqi  = pPacketDetails->lqi;
            sLastLqi = pPacketDetails->lqi;
        }
        else
        {
            sReceiveFrame.mInfo.mRxInfo.mRssi = sReceivePacket[aReceiveBufferInUse].packetInfo.rssi;
            sLastRssi = sReceivePacket[aReceiveBufferInUse].packetInfo.rssi;

            sReceiveFrame.mInfo.mRxInfo.mLqi  = sReceivePacket[aReceiveBufferInUse].packetInfo.lqi;
            sLastLqi = sReceivePacket[aReceiveBufferInUse].packetInfo.rssi;
        }

        sReceiveFrame.mInfo.mRxInfo.mTimestamp = timestamp + ((uint64_t) railUsTimerWraps << 32);
        // Set this flag only when the packet is really acknowledged with a secured enhanced ACK.
        sReceiveFrame.mInfo.mRxInfo.mAckedWithSecEnhAck = securedOutgoingEnhancedAck;
        // Set this flag only when the packet is really acknowledged with frame pending set.
        sReceiveFrame.mInfo.mRxInfo.mAckedWithFramePending = framePendingSetInOutgoingAck;
        sReceiveFrame.mIid = iid;

#if OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2
        // Use stored values for these
        sReceiveFrame.mInfo.mRxInfo.mAckKeyId = sMacKeys[iid].ackKeyId;
        sReceiveFrame.mInfo.mRxInfo.mAckFrameCounter = sMacKeys[iid].ackFrameCounter;
#endif
    }
}

static otError skipRxPacketLengthBytes(RAIL_RxPacketInfo_t *pPacketInfo)
{
    otError error = OT_ERROR_NONE;
    otEXPECT_ACTION(pPacketInfo->firstPortionBytes > 0, error = OT_ERROR_FAILED);

    pPacketInfo->firstPortionData += PHY_HEADER_SIZE;
    pPacketInfo->packetBytes -= PHY_HEADER_SIZE;

    if (PHY_HEADER_SIZE == 1 || pPacketInfo->firstPortionBytes > 1)
    {
        pPacketInfo->firstPortionBytes -= PHY_HEADER_SIZE;
    }
    else
    {
        pPacketInfo->firstPortionBytes = 0U;
        // Increment lastPortionData to skip the second byte of the PHY header
        otEXPECT_ACTION(pPacketInfo->lastPortionData != NULL, error = OT_ERROR_FAILED);
        pPacketInfo->lastPortionData++;
    }

exit:
    return error;
}

static bool prepareNextRxPacketforCb(void)
{
#if SL_OPENTHREAD_RADIO_RX_BUFFER_COUNT == 1
    RAIL_RxPacketHandle_t  packetHandle = RAIL_RX_PACKET_HANDLE_INVALID;
    RAIL_RxPacketInfo_t    packetInfo;
    RAIL_RxPacketDetails_t packetDetails;
    RAIL_Status_t          status;
    uint16_t               length;
    bool                   rxProcessDone = false;
    uint8_t                iid           = 0;
    rxBufferIndex_t index = 0;

    CORE_DECLARE_IRQ_STATE;
    CORE_ENTER_ATOMIC();

    //Initialise the mPsdu to free buffer
    sReceiveFrame.mPsdu = sReceivePacket[index].psdu;

    packetHandle = RAIL_GetRxPacketInfo(gRailHandle, RAIL_RX_PACKET_HANDLE_OLDEST_COMPLETE, &packetInfo);
    otEXPECT_ACTION(
        (packetHandle != RAIL_RX_PACKET_HANDLE_INVALID && packetInfo.packetStatus == RAIL_RX_PACKET_READY_SUCCESS),
        packetHandle = RAIL_RX_PACKET_HANDLE_INVALID);

    iid = getIidFromFilterMask(packetInfo.filterMask);

    otEXPECT(validatePacketDetails(packetHandle, &packetDetails, &packetInfo, &length));

    otEXPECT((skipRxPacketLengthBytes(&packetInfo)) == OT_ERROR_NONE);

    // As received ACK frames are already processed in packetReceivedCallback,
    // we only need to read and process the non-ACK frames here.
    otEXPECT(sPromiscuous || (!packetDetails.isAck && (length >= IEEE802154_MIN_DATA_LENGTH)));

    // read packet
    RAIL_CopyRxPacket(sReceiveFrame.mPsdu, &packetInfo);
    sReceiveFrame.mLength = length;

    uint8_t *macFcfPointer = sReceiveFrame.mPsdu;
    sReceiveFrame.mChannel = packetDetails.channel;

    // Check the reserved bits in the MAC header, then clear them.

    // If we sent an enhanced ACK, check if it was secured.
    bool securedOutgoingEnhancedAck = ((*macFcfPointer & IEEE802154_SECURED_OUTGOING_ENHANCED_ACK) != 0);
    *macFcfPointer &= ~IEEE802154_SECURED_OUTGOING_ENHANCED_ACK;

    // Check whether frame pendinng bit was set in the outgoing ACK.
    bool framePendingSetInOutgoingAck = ((*macFcfPointer & IEEE802154_FRAME_PENDING_SET_IN_OUTGOING_ACK) != 0);
    *macFcfPointer &= ~IEEE802154_FRAME_PENDING_SET_IN_OUTGOING_ACK;

    status = RAIL_ReleaseRxPacket(gRailHandle, packetHandle);
    if (status == RAIL_STATUS_NO_ERROR)
    {
        packetHandle = RAIL_RX_PACKET_HANDLE_INVALID;
    }

    otEXPECT(validatePacketTimestamp(&packetDetails, length));
    updateRxFrameDetails(&packetDetails, securedOutgoingEnhancedAck, framePendingSetInOutgoingAck, iid, 0);
    rxProcessDone = true;

#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
    railDebugCounters.mRailPlatRadioReceiveProcessedCount++;
#endif

exit:
    if (packetHandle != RAIL_RX_PACKET_HANDLE_INVALID)
    {
        RAIL_ReleaseRxPacket(gRailHandle, packetHandle);
    }
    CORE_EXIT_ATOMIC();
#else
    bool rxProcessDone = true;
    rxBufferIndex_t index = getStoredBufferIndex();
    uint8_t *psdu = sReceivePacket[index].psdu;

    // Check the reserved bits in the MAC header, then clear them.
    // If we sent an enhanced ACK, check if it was secured.
    bool securedOutgoingEnhancedAck = ((*psdu & IEEE802154_SECURED_OUTGOING_ENHANCED_ACK) != 0);
    *psdu &= ~IEEE802154_SECURED_OUTGOING_ENHANCED_ACK;

    // Check whether frame pendinng bit was set in the outgoing ACK.
    bool framePendingSetInOutgoingAck = ((*psdu & IEEE802154_FRAME_PENDING_SET_IN_OUTGOING_ACK) != 0);
    *psdu &= ~IEEE802154_FRAME_PENDING_SET_IN_OUTGOING_ACK;

    sReceiveFrame.mChannel = sReceivePacket[index].packetInfo.channel;
    sReceiveFrame.mLength = sReceivePacket[index].packetInfo.length;
    sReceiveFrame.mPsdu = sReceivePacket[index].psdu;

    updateRxFrameDetails(NULL, securedOutgoingEnhancedAck, framePendingSetInOutgoingAck, sReceivePacket[index].packetInfo.iid, index);
#endif

    return rxProcessDone;
}

static void processNextRxPacket(otInstance *aInstance)
{
    if (prepareNextRxPacketforCb())
    {
        sReceiveError = OT_ERROR_NONE;

#if OPENTHREAD_CONFIG_DIAG_ENABLE
        if (otPlatDiagModeGet())
        {
            otPlatDiagRadioReceiveDone(aInstance, &sReceiveFrame, sReceiveError);
        }
        else
#endif
        {
#if OPENTHREAD_RADIO && OPENTHREAD_CONFIG_MULTIPAN_RCP_ENABLE == 1 && (defined SL_CATALOG_OT_RCP_GP_INTERFACE_PRESENT)
            (void) sl_gp_intf_is_gp_pkt(&sReceiveFrame, true);
#endif
            otPlatRadioReceiveDone(aInstance, &sReceiveFrame, sReceiveError);
#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
            railDebugCounters.mRailPlatRadioReceiveDoneCbCount++;
#endif
        }

#if SL_OPENTHREAD_RADIO_RX_BUFFER_COUNT > 1
        releaseCurrentRxBuffer();
#endif

        otSysEventSignalPending();
    }
}

static void processRxPackets(otInstance *aInstance)
{
#if SL_OPENTHREAD_RADIO_RX_BUFFER_COUNT > 1
    while (canProcessNextRxBuffer())
    {
       processNextRxPacket(aInstance);
    }
#else
    processNextRxPacket(aInstance);
#endif
}

static void processTxComplete(otInstance *aInstance)
{
    otError      txStatus;
    otRadioFrame *ackFrame = NULL;
    
    if(getInternalFlag(RADIO_TX_EVENTS))
    {
        if(getInternalFlag(EVENT_TX_SUCCESS))
        {
            txStatus = OT_ERROR_NONE;

            if (sTransmitFrame.mPsdu[0] & IEEE802154_FRAME_FLAG_ACK_REQUIRED)
            {
                ackFrame = &sReceiveAckFrame;
            }

            setInternalFlag(EVENT_TX_SUCCESS, false);
        }
        else if(getInternalFlag(EVENT_TX_CCA_FAILED))
        {
            txStatus = OT_ERROR_CHANNEL_ACCESS_FAILURE;
            setInternalFlag(EVENT_TX_CCA_FAILED, false);
        }
        else if(getInternalFlag(EVENT_TX_NO_ACK))
        {
            txStatus = OT_ERROR_NO_ACK;
            setInternalFlag(EVENT_TX_NO_ACK, false);
        }
        else
        {
            txStatus = OT_ERROR_ABORT;
            setInternalFlag(EVENT_TX_FAILED, false);
        }

        if(txStatus != OT_ERROR_NONE)
        {
            otLogDebgPlat("Transmit failed ErrorCode=%d", txStatus);
        }

#if OPENTHREAD_CONFIG_DIAG_ENABLE
        if (otPlatDiagModeGet())
        {
            otPlatDiagRadioTransmitDone(aInstance, sTxFrame, txStatus);
        }
        else
#endif
        {
            // Clear any internally-set txDelays so future transmits are not affected.
            sTxFrame->mInfo.mTxInfo.mTxDelayBaseTime = 0;
            sTxFrame->mInfo.mTxInfo.mTxDelay = 0;
            otPlatRadioTxDone(aInstance, sTxFrame, ackFrame, txStatus);
        }

#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
        railDebugCounters.mRailPlatRadioTxDoneCbCount++;
#endif
        otSysEventSignalPending();
    }
}

void efr32RadioProcess(otInstance *aInstance)
{
    (void)handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TICK, 0U);

    // We should process the received packet first. Adding it at the end of this function,
    // will delay the stack notification until the next call to efr32RadioProcess()
    processRxPackets(aInstance);
    processTxComplete(aInstance);

    if (sEnergyScanMode == ENERGY_SCAN_MODE_ASYNC && sEnergyScanStatus == ENERGY_SCAN_STATUS_COMPLETED)
    {
        sEnergyScanStatus = ENERGY_SCAN_STATUS_IDLE;
        otPlatRadioEnergyScanDone(aInstance, sEnergyScanResultDbm);
        otSysEventSignalPending();

#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
        railDebugCounters.mRailEventEnergyScanCompleted++;
#endif
    }
}

//------------------------------------------------------------------------------
// Antenna Diversity, Wifi coexistence and Runtime PHY select support

RAIL_Status_t efr32RadioSetCcaMode(uint8_t aMode)
{
    return RAIL_IEEE802154_ConfigCcaMode(gRailHandle, aMode);
}

RAIL_IEEE802154_PtiRadioConfig_t efr32GetPtiRadioConfig(void)
{
    return (RAIL_IEEE802154_GetPtiRadioConfig(gRailHandle));
}

#ifdef SL_CATALOG_RAIL_UTIL_IEEE802154_PHY_SELECT_PRESENT

otError setRadioState(otRadioState state)
{
    otError error = OT_ERROR_NONE;

    // Defer idling the radio if we have an ongoing TX task
    otEXPECT_ACTION(!getInternalFlag(ONGOING_TX_FLAGS), error = OT_ERROR_FAILED);

    switch (state)
    {
    case OT_RADIO_STATE_RECEIVE:
        otEXPECT_ACTION(radioSetRx(sReceiveFrame.mChannel) == OT_ERROR_NONE, error = OT_ERROR_FAILED);
        break;
    case OT_RADIO_STATE_SLEEP:
        radioSetIdle();
        break;
    default:
        error = OT_ERROR_FAILED;
    }
exit:
    return error;
}

void sl_ot_update_active_radio_config(void)
{
    CORE_DECLARE_IRQ_STATE;
    CORE_ENTER_ATOMIC();

    // Proceed with PHY selection only if 2.4 GHz band is used
    otEXPECT(sBandConfig.mChannelConfig == NULL);

    otRadioState currentState = otPlatRadioGetState(NULL);
    otEXPECT(setRadioState(OT_RADIO_STATE_SLEEP) == OT_ERROR_NONE);
    sl_rail_util_ieee802154_config_radio(gRailHandle);
    otEXPECT(setRadioState(currentState) == OT_ERROR_NONE);

exit:
    CORE_EXIT_ATOMIC();
    return;
}
#endif // SL_CATALOG_RAIL_UTIL_IEEE802154_PHY_SELECT_PRESENT

#ifdef SL_CATALOG_RAIL_UTIL_ANT_DIV_PRESENT
void efr32AntennaConfigInit(void)
{
    RAIL_Status_t status;
    sl_rail_util_ant_div_init();
    status = sl_rail_util_ant_div_update_antenna_config();
    OT_ASSERT(status == RAIL_STATUS_NO_ERROR);
}
#endif // SL_CATALOG_RAIL_UTIL_ANT_DIV_PRESENT

#ifdef SL_CATALOG_RAIL_UTIL_IEEE802154_STACK_EVENT_PRESENT

static void changeDynamicEvents(void)
{
    /* clang-format off */
    const RAIL_Events_t eventMask = RAIL_EVENTS_NONE
                                    | RAIL_EVENT_RX_SYNC1_DETECT
                                    | RAIL_EVENT_RX_SYNC2_DETECT
                                    | RAIL_EVENT_RX_FRAME_ERROR
                                    | RAIL_EVENT_RX_FIFO_OVERFLOW
                                    | RAIL_EVENT_RX_ADDRESS_FILTERED
                                    | RAIL_EVENT_RX_PACKET_ABORTED
                                    | RAIL_EVENT_RX_FILTER_PASSED
                                    | RAIL_EVENT_TX_CHANNEL_CLEAR
                                    | RAIL_EVENT_TX_CCA_RETRY
                                    | RAIL_EVENT_TX_START_CCA
                                    | RAIL_EVENT_SIGNAL_DETECTED;
    /* clang-format on */
    RAIL_Events_t eventValues = RAIL_EVENTS_NONE;

    if (phyStackEventIsEnabled())
    {
        eventValues |= eventMask;
    }
    updateEvents(eventMask, eventValues);
}
#endif // SL_CATALOG_RAIL_UTIL_IEEE802154_STACK_EVENT_PRESENT

static void efr32PhyStackInit(void)
{
#ifdef SL_CATALOG_RAIL_UTIL_ANT_DIV_PRESENT
    efr32AntennaConfigInit();
#endif // SL_CATALOG_RAIL_UTIL_ANT_DIV_PRESENT

#ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT
    efr32CoexInit();
#endif // SL_CATALOG_RAIL_UTIL_COEX_PRESENT

#ifdef SL_CATALOG_RAIL_UTIL_IEEE802154_STACK_EVENT_PRESENT
    changeDynamicEvents();
#endif
}

#ifdef SL_CATALOG_RAIL_UTIL_COEX_PRESENT

static void emRadioEnableAutoAck(void)
{
    CORE_DECLARE_IRQ_STATE;
    CORE_ENTER_ATOMIC();

    if (getInternalFlag(FLAG_RADIO_INIT_DONE))
    {
        if ((rhoActive >= RHO_INT_ACTIVE) // Internal always holds ACKs
            || ((rhoActive > RHO_INACTIVE)
                && ((sl_rail_util_coex_get_options() & SL_RAIL_UTIL_COEX_OPT_ACK_HOLDOFF)
                    != SL_RAIL_UTIL_COEX_OPT_DISABLED)))
        {
            RAIL_PauseRxAutoAck(gRailHandle, true);
        }
        else
        {
            RAIL_PauseRxAutoAck(gRailHandle, false);
        }
    }
    CORE_EXIT_ATOMIC();
}

static void emRadioEnablePta(bool enable)
{
    halInternalInitPta();

    // When PTA is enabled, we want to negate PTA_REQ as soon as an incoming
    // frame is aborted, e.g. due to filtering.  To do that we must turn off
    // the TRACKABFRAME feature that's normally on to benefit sniffing on PTI.
    RAIL_Status_t status = RAIL_ConfigRxOptions(gRailHandle,
                                                RAIL_RX_OPTION_TRACK_ABORTED_FRAMES,
                                                (enable ? RAIL_RX_OPTIONS_NONE : RAIL_RX_OPTION_TRACK_ABORTED_FRAMES));
    OT_ASSERT(status == RAIL_STATUS_NO_ERROR);
}

static void efr32CoexInit(void)
{
#if SL_OPENTHREAD_COEX_COUNTER_ENABLE && defined(SL_CATALOG_RAIL_MULTIPLEXER_PRESENT)
    sl_rail_mux_set_coex_counter_handler(gRailHandle, &sl_ot_coex_counter_on_event);
#endif // SL_OPENTHREAD_COEX_COUNTER_ENABLE && defined(SL_CATALOG_RAIL_MULTIPLEXER_PRESENT)

    sl_rail_util_coex_options_t coexOptions = sl_rail_util_coex_get_options();

#if SL_OPENTHREAD_COEX_MAC_HOLDOFF_ENABLE
    coexOptions |= SL_RAIL_UTIL_COEX_OPT_MAC_HOLDOFF;
#else
    if (sl_rail_util_coex_get_radio_holdoff())
    {
        coexOptions |= SL_RAIL_UTIL_COEX_OPT_MAC_HOLDOFF;
    }
#endif // SL_OPENTHREAD_COEX_MAC_HOLDOFF_ENABLE

    sl_rail_util_coex_set_options(coexOptions);

    emRadioEnableAutoAck(); // Might suspend AutoACK if RHO already in effect
    emRadioEnablePta(sl_rail_util_coex_is_enabled());
}

// Managing radio transmission
static void onPtaGrantTx(sl_rail_util_coex_req_t ptaStatus)
{
    // Only pay attention to first PTA Grant callback, ignore any further ones
    if (ptaGntEventReported)
    {
        return;
    }
    ptaGntEventReported = true;

    OT_ASSERT(ptaStatus == SL_RAIL_UTIL_COEX_REQCB_GRANTED);
    // PTA is telling us we've gotten GRANT and should send ASAP *without* CSMA
    setInternalFlag(FLAG_CURRENT_TX_USE_CSMA, false);
    txCurrentPacket();
}

static void tryTxCurrentPacket(void)
{
    OT_ASSERT(getInternalFlag(FLAG_ONGOING_TX_DATA));

    ptaGntEventReported = false;
    sl_rail_util_ieee802154_stack_event_t ptaStatus =
        handlePhyStackEvent(SL_RAIL_UTIL_IEEE802154_STACK_EVENT_TX_PENDED_MAC, (uint32_t)&onPtaGrantTx);
    if (ptaStatus == SL_RAIL_UTIL_IEEE802154_STACK_STATUS_SUCCESS)
    {
        // Normal case where PTA allows us to start the (CSMA) transmit below
        txCurrentPacket();
    }
    else if (ptaStatus == SL_RAIL_UTIL_IEEE802154_STACK_STATUS_CB_PENDING)
    {
        // onPtaGrantTx() callback will take over (and might already have)
    }
    else if (ptaStatus == SL_RAIL_UTIL_IEEE802154_STACK_STATUS_HOLDOFF)
    {
        txFailedCallback(false, EVENT_TX_FAILED);
    }
}

// Managing CCA Threshold
static void setCcaThreshold(void)
{
    if (sCcaThresholdDbm == CCA_THRESHOLD_UNINIT)
    {
        sCcaThresholdDbm = CCA_THRESHOLD_DEFAULT;
    }
    CORE_DECLARE_IRQ_STATE;
    CORE_ENTER_ATOMIC();
    int8_t thresholddBm = sCcaThresholdDbm;

    if (getInternalFlag(FLAG_RADIO_INIT_DONE))
    {
        if (rhoActive > RHO_INACTIVE)
        {
            thresholddBm = RAIL_RSSI_INVALID_DBM;
        }
        RAIL_Status_t status = RAIL_SetCcaThreshold(gRailHandle, thresholddBm);
        OT_ASSERT(status == RAIL_STATUS_NO_ERROR);
    }
    CORE_EXIT_ATOMIC();
}

static void emRadioHoldOffInternalIsr(uint8_t active)
{
    if (active != rhoActive)
    {
        rhoActive = active; // Update rhoActive early
        if (getInternalFlag(FLAG_RADIO_INIT_DONE))
        {
            setCcaThreshold();
            emRadioEnableAutoAck();
        }
    }
}

// External API used by Coex Component
SL_WEAK void emRadioHoldOffIsr(bool active)
{
    emRadioHoldOffInternalIsr((uint8_t)active | (rhoActive & ~RHO_EXT_ACTIVE));
}

#if SL_OPENTHREAD_COEX_COUNTER_ENABLE

#ifdef SL_CATALOG_RAIL_MULTIPLEXER_PRESENT
static void sl_ot_coex_counter_on_event(sl_rail_util_coex_event_t event)
#else
void sl_rail_util_coex_counter_on_event(sl_rail_util_coex_event_t event)
#endif
{
    otEXPECT(event < SL_RAIL_UTIL_COEX_EVENT_COUNT);
    efr32RadioCoexCounters[event] += 1;
exit:
    return;
}

void efr32RadioClearCoexCounters(void)
{
    memset((void *)efr32RadioCoexCounters, 0, sizeof(efr32RadioCoexCounters));
}

#endif // SL_OPENTHREAD_COEX_COUNTER_ENABLE
#endif // SL_CATALOG_RAIL_UTIL_COEX_PRESENT

#if RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
void efr32ClearRadioCounters(void)
{
    memset(&railDebugCounters, 0, sizeof(railDebugCounters));
}

#endif // RADIO_CONFIG_DEBUG_COUNTERS_SUPPORT
