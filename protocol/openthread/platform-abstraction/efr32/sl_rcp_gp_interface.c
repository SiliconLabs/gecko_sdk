/***************************************************************************//**
 * @file
 * @brief This file implements Green Power interface.
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

#include <assert.h>
#include "utils/mac_frame.h"
#include "rail_ieee802154.h"
#include "ieee802154mac.h"
#include <openthread/platform/time.h>
#include "common/logging.hpp"
#include "sl_status.h"
#include "sl_rcp_gp_interface.h"
#include "sl_packet_utils.h"
#include <string.h>

#if (SL_GP_RCP_INTERFACE_ENABLED == 1)

// This implements mechanism to buffer outgoing Channel Configuration (0xF3) and
// Commissioning Reply (0xF0) GPDF commands on the RCP to sent out on request
// from GPD with bidirectional capability with in a certain time window, i.e.
// between 20 and 25 msec.
// The machanism works following way -
// The zigbeed submits the outgoind GPDF command, this code on rcp intercepts the
// packet from transmit API and buffers the packet, does not send it out.
// The GPD sends request indicating its RX capability, this again intercept the
// rx message and based on the request, it sends out the above buffered message
// with in a time window of 20-25 msec from the time it received the message.

#define GP_MIN_MAINTENANCE_FRAME_LENGTH 10
#define GP_MIN_DATA_FRAME_LENGTH 14

#define GP_ADDRESSING_MODE_SRC_ID 0
#define GP_ADDRESSING_MODE_EUI64  2

#define GP_NWK_PROTOCOL_VERSION_CHECK(nwkFc) (((nwkFc >> 2) & 0x0F) == 3)
#define GP_NWK_FRAME_TYPE_MAINTENANCE_WITHOUT_EXTD_FC(nwkFc) ((nwkFc & 0xC3) == 0x01)
#define GP_NWK_FRAME_TYPE_DATA_WITH_EXTD_FC(nwkFc) ((nwkFc & 0xC3) == 0x80)

#define GP_NWK_UNSECURED_RX_DATA_FRAME(nwkExntdFc) ((nwkExntdFc & 0xF8) == 0x40)
#define GP_NWK_UNSECURED_TX_DATA_FRAME(nwkExntdFc) ((nwkExntdFc & 0xF8) == 0x80)
#define GP_NWK_ADDRESSING_APP_ID(nwkExntdFc) ((nwkExntdFc & 0x07))

#define GP_CHANNEL_REQUEST_CMD_ID 0xE3
#define GP_CHANNEL_CONFIGURATION_CMD_ID 0xF3
#define GP_COMMISSIONINGING_CMD_ID 0xE0
#define GP_COMMISSIONING_REPLY_CMD_ID 0xF0

#define GP_EXND_FC_INDEX                 1
#define GP_COMMAND_INDEX_FOR_MAINT_FRAME 1
#define GP_SRC_ID_INDEX_WITH_APP_MODE_0  2
#define GP_APP_EP_INDEX_WITH_APP_MODE_1  2
#define GP_COMMAND_INDEX_WITH_APP_MODE_1 3
#define GP_COMMAND_INDEX_WITH_APP_MODE_0 6

#define BUFFERED_PSDU_GP_SRC_ID_INDEX_WITH_APP_MODE_0 9
#define BUFFERED_PSDU_GP_APP_EP_INDEX_WITH_APP_MODE_1 9

static       volatile sl_gp_state_t      gp_state = SL_GP_STATE_INIT;
static       otRadioFrame                sGpTxFrame;
volatile     uint8_t                     sGpTxPsdu[IEEE802154_MAX_LENGTH];
volatile     uint64_t                    mRxTimestamp;

uint64_t     gpSmState[SL_GP_STATE_MAX];

sl_gp_state_t sl_gp_intf_get_state(void)
{
    return gp_state;
}

void efr32GpProcess(void)
{
    gpSmState[gp_state]++;

    switch(gp_state)
    {
        case SL_GP_STATE_INIT:
        {
            memset(gpSmState, 0, sizeof(gpSmState));
            sGpTxFrame.mPsdu = (uint8_t *)sGpTxPsdu;
            gp_state = SL_GP_STATE_IDLE;
            otLogDebgPlat("GP RCP INTF: GP Frame init!!");
        }
        break;
        case SL_GP_STATE_SEND_RESPONSE:
        {
            if(otPlatTimeGet() >= mRxTimestamp + 20500)
            {
                //Check if we need delay.
                otPlatRadioTransmit(NULL, &sGpTxFrame);
                gp_state = SL_GP_STATE_IDLE;
                otLogDebgPlat("GP RCP INTF: Sending Response!!");
            }
        }
        break;

        default:
        {
            // For all other states don't do anything
        }
        break;
    }
}

void sl_gp_intf_buffer_pkt(otRadioFrame *aFrame)
{
    memcpy(&sGpTxFrame, aFrame,         sizeof(otRadioFrame));
    memcpy((void *)sGpTxPsdu,   aFrame->mPsdu,  aFrame->mLength);

    gp_state = SL_GP_STATE_WAITING_FOR_PKT;
    otLogDebgPlat("GP RCP INTF: buffered!!");
}

bool sl_gp_intf_is_gp_pkt(otRadioFrame *aFrame, bool isRxFrame)
{
    bool            isGpPkt = false;
    uint8_t         *gpFrameStartIndex = efr32GetPayload(aFrame);
    otLogDebgPlat("GP RCP INTF: PL Index = %d", (gpFrameStartIndex - aFrame->mPsdu));

    // A Typical MAC Frame with GP NWK Frame in it
    // MAC Frame  : [<---------------MAC Header------------->||<------------------------------------NWK Frame----------------------------------->]
    //               FC(2) | Seq(1) | DstPan(2) | DstAddr(2) || FC(1) | ExtFC(0/1) | SrcId(0/4) | SecFc(0/4) | MIC(0/4) | <------GPDF(1/n)------>
    // The Green Power NWK FC and Ext FC are described as :
    //              FC    : ExtFC Present(b7)=1| AC(b6)=0| Protocol Ver(b5-b2)=3 GP frames| Frame Type(b1-b0) = 0
    //              ExtFC :  rxAfteTX (b6) = 1 |  AppId(b2-b0) = 0

    uint8_t fc = *gpFrameStartIndex;

    // The basic Identification of a GPDF Frame : The minimum GPDF length need to be 10 in this case for any direction
    // with network layer FC containing the Protocol Version field as 3.
    if (aFrame->mLength >= GP_MIN_MAINTENANCE_FRAME_LENGTH
        && GP_NWK_PROTOCOL_VERSION_CHECK(fc))
    {
        // For GP Maintenance Frame type without extened FC, the FC is exactly same for both RX and TX directions with auto commissioning bit = 0,
        // does not have a ExtFC field, only the command Id (which is the next byte in frame) indicates the direction.
        if (GP_NWK_FRAME_TYPE_MAINTENANCE_WITHOUT_EXTD_FC(fc))
        {
            uint8_t cmdId = *(gpFrameStartIndex + GP_COMMAND_INDEX_FOR_MAINT_FRAME);
            if (cmdId == GP_CHANNEL_REQUEST_CMD_ID
                && isRxFrame)
            {
                // Send out the buffered frame
                isGpPkt = true;
                gp_state = SL_GP_STATE_SEND_RESPONSE;
                mRxTimestamp = aFrame->mInfo.mRxInfo.mTimestamp;
            }
            else if (cmdId == GP_CHANNEL_CONFIGURATION_CMD_ID
                       && !isRxFrame)
            {
                // Buffer the frame
                isGpPkt = true;
            }
        }
        else if (GP_NWK_FRAME_TYPE_DATA_WITH_EXTD_FC(fc)         // Data frame with EXT FC present, extract the App Id, SrcId, direction and command Id
                 && aFrame->mLength >= GP_MIN_DATA_FRAME_LENGTH) // Minimum Data frame length with extended header and address
        {
            uint8_t extFc = *(gpFrameStartIndex + GP_EXND_FC_INDEX);

            // Process only unsecured commissioning frames for Tx/Rx with correct direction and RxAfterTx feilds
            if ((!isRxFrame
                 && GP_NWK_UNSECURED_TX_DATA_FRAME(extFc))
                || (isRxFrame
                    && GP_NWK_UNSECURED_RX_DATA_FRAME(extFc)))
            {
                if (GP_NWK_ADDRESSING_APP_ID(extFc) == GP_ADDRESSING_MODE_SRC_ID)
                {
                    uint8_t cmdId = *(gpFrameStartIndex + GP_COMMAND_INDEX_WITH_APP_MODE_0);
                    if (cmdId == GP_COMMISSIONING_REPLY_CMD_ID
                        && !isRxFrame)
                    {
                        // Buffer the frame
                        isGpPkt = true;
                    }
                    else if (cmdId == GP_COMMISSIONINGING_CMD_ID
                             && isRxFrame)
                    {
                        // Match the gpd src Id ?
                        if (!memcmp((const void *)(gpFrameStartIndex + GP_SRC_ID_INDEX_WITH_APP_MODE_0),
                                    (const void *)(sGpTxPsdu + BUFFERED_PSDU_GP_SRC_ID_INDEX_WITH_APP_MODE_0),
                                    sizeof(uint32_t)))
                        {
                            // Send out the buffered frame
                            gp_state = SL_GP_STATE_SEND_RESPONSE;
                            mRxTimestamp = aFrame->mInfo.mRxInfo.mTimestamp;
                        }
                    }
                }
                else if (GP_NWK_ADDRESSING_APP_ID(extFc) == GP_ADDRESSING_MODE_EUI64)
                {
                    uint8_t cmdId = *(gpFrameStartIndex + GP_COMMAND_INDEX_WITH_APP_MODE_1);
                    if (cmdId == GP_COMMISSIONING_REPLY_CMD_ID
                        && !isRxFrame)
                    {
                        // Buffer the frame
                        isGpPkt = true;
                    }
                    else if (cmdId == GP_COMMISSIONINGING_CMD_ID
                             && isRxFrame)
                    {
                        // Check the eui64 and app endpoint to send out the buffer packet.
                        otMacAddress aSrcAddress;
                        otMacAddress aDstAddress;
                        otMacFrameGetDstAddr(&sGpTxFrame, &aDstAddress);
                        otMacFrameGetSrcAddr(aFrame, &aSrcAddress);
                        if ( !memcmp(&(aDstAddress.mAddress.mExtAddress), &(aSrcAddress.mAddress.mExtAddress), sizeof(otExtAddress))
                             && (gpFrameStartIndex[GP_APP_EP_INDEX_WITH_APP_MODE_1] == sGpTxPsdu[BUFFERED_PSDU_GP_APP_EP_INDEX_WITH_APP_MODE_1]))
                        {
                            isGpPkt = true;
                            gp_state = SL_GP_STATE_SEND_RESPONSE;
                            mRxTimestamp = aFrame->mInfo.mRxInfo.mTimestamp;
                        }
                    }
                }
            }
        }
    }
    if(isGpPkt)
    {
        otLogDebgPlat("GP RCP INTF: GP filter passed!!");
    }

    return isGpPkt;
}

#endif
