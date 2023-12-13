/***************************************************************************//**
 * @file
 * @brief BT Mesh Segmentation and Reassembly Server Configuration
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

#ifndef SL_BTMESH_SAR_CONFIG_SERVER_CONFIG_H
#define SL_BTMESH_SAR_CONFIG_SERVER_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <e SL_BTMESH_SAR_CONFIG_SERVER_CUSTOM_TRANSMITTER_CFG_VAL> Custom SAR Transmitter Default State
// <i> If the default SAR Transmitter state in BT Mesh stack isn't sufficient then the SAR Transmitter default state
// <i> can be customized and overridden by activating this configuration option.
// <i> The SAR Transmitter state is configured before provisioning once because the BT Mesh stack stores the SAR
// <i> Transmitter state persistently so the SAR Configuration Client can modify the default value after provisioning.
#define SL_BTMESH_SAR_CONFIG_SERVER_CUSTOM_TRANSMITTER_CFG_VAL  0

// <o SL_BTMESH_SAR_CONFIG_SERVER_TX_SEGMENT_INTERVAL_STEP_MS_CFG_VAL> Default SAR Tx Segment Interval Step [ms]
// <i> Default SAR Transmitter Segment Interval Step controls the interval between transmissions of segments of a
// <i> segmented message in milliseconds.
// <i> The value is the range of 10ms to 160ms in 10ms steps, intermediate values are rounded down to the nearest
// <i> multiple of 10.
// <i> Default value is 20ms.
// <10..160:10>
// <d> 20
#define SL_BTMESH_SAR_CONFIG_SERVER_TX_SEGMENT_INTERVAL_STEP_MS_CFG_VAL  20

// <o SL_BTMESH_SAR_CONFIG_SERVER_TX_UNICAST_RETRANS_COUNT_CFG_VAL> Default SAR Tx Unicast Retransmission Count
// <i> Default SAR Transmitter Unicast Retransmission Count state controls the maximum number of transmissions of
// <i> segments of segmented messages to a unicast destination.
// <i> Valid range is 0 - 15, where 0 represents a single transmission.
// <i> Default value is 7, resulting in 8 transmissions total.
// <0..15:1>
// <d> 7
#define SL_BTMESH_SAR_CONFIG_SERVER_TX_UNICAST_RETRANS_COUNT_CFG_VAL  7

// <o SL_BTMESH_SAR_CONFIG_SERVER_TX_UNICAST_RETRANS_WO_PROG_COUNT_CFG_VAL> Default SAR Transmitter Unicast Retransmissions Without Progress Count
// <i> Default SAR Transmitter Unicast Retransmissions Without Progress Count state controls the maximum number of
// <i> retransmissions of segments of segmented messages to a unicast destination without progress (without newly
// <i> marking any segments acknowledged).
// <i> Valid range is 0 - 15, where 0 represents a single transmission.
// <i> Default value is 2, resulting in 3 transmissions.
// <i> Value of this state should be set to a value greater by two or more than the value of the SAR Receiver
// <i> Acknowledgement Retransmissions Count on a peer node. This helps prevent the SAR Transmitter from abandoning
// <i> the SAR prematurely.
// <0..15:1>
// <d> 2
#define SL_BTMESH_SAR_CONFIG_SERVER_TX_UNICAST_RETRANS_WO_PROG_COUNT_CFG_VAL  2

// <o SL_BTMESH_SAR_CONFIG_SERVER_TX_UNICAST_RETRANS_INTERVAL_STEP_MS_CFG_VAL> Default SAR Transmitter Unicast Retransmissions Interval Step [ms]
// <i> Default SAR Transmitter Unicast Retransmissions Interval Step state controls the minimum interval between
// <i> retransmissions of segments of a segmented message for a destination that is a unicast address in 25ms steps.
// <i> Valid range is 25 - 400ms, intermediate values are rounded down to the nearest multiple of 25.
// <i> Default value is 200ms.
// <25..400:25>
// <d> 200
#define SL_BTMESH_SAR_CONFIG_SERVER_TX_UNICAST_RETRANS_INTERVAL_STEP_MS_CFG_VAL  200

// <o SL_BTMESH_SAR_CONFIG_SERVER_TX_UNICAST_RETRANS_INTERVAL_INC_MS_CFG_VAL> Default SAR Transmitter Unicast Retransmissions Interval Increment [ms]
// <i> Default SAR Transmitter Unicast Retransmissions Interval Increment state controls the incremental component (TTL)
// <i> of the interval between retransmissions of segments of a segmented message for a destination that is a unicast
// <i> address in 25ms steps.
// <i> Valid range is 25 - 400ms, intermediate values are rounded down to the nearest multiple of 25.
// <i> Default value is 50ms.
// <25..400:25>
// <d> 50
#define SL_BTMESH_SAR_CONFIG_SERVER_TX_UNICAST_RETRANS_INTERVAL_INC_MS_CFG_VAL  50

// <o SL_BTMESH_SAR_CONFIG_SERVER_TX_MULTICAST_RETRANS_COUNT_CFG_VAL> Default SAR Transmitter Multicast Retransmissions Count
// <i> Default SAR Transmitter Multicast Retransmissions Count state controls the maximum number of transmissions of
// <i> segments of segmented messages to a group address or a virtual address.
// <i> Valid range is 0 - 15, where 0 represents a single transmission.
// <i> Default value is 1, resulting in 2 transmissions.
// <0..15:1>
// <d> 1
#define SL_BTMESH_SAR_CONFIG_SERVER_TX_MULTICAST_RETRANS_COUNT_CFG_VAL  1

// <o SL_BTMESH_SAR_CONFIG_SERVER_TX_MULTICAST_RETRANS_INTERVAL_STEP_MS_CFG_VAL> Default SAR Transmitter Multicast Retransmissions Interval Step [ms]
// <i> Default SAR Transmitter Multicast Retransmissions Interval Step state controls the interval between retransmissions
// <i> of segments of a segmented message for a destination that is a group address or a virtual address in 25ms steps.
// <i> Valid range is 25-400ms, intermediate values are rounded down to the nearest multiple of 25.
// <i> Default value is 100ms.
// <25..400:25>
// <d> 100
#define SL_BTMESH_SAR_CONFIG_SERVER_TX_MULTICAST_RETRANS_INTERVAL_STEP_MS_CFG_VAL  100

// </e>

// <e SL_BTMESH_SAR_CONFIG_SERVER_CUSTOM_RECEIVER_CFG_VAL> Custom SAR Receiver Default State
// <i> If the default SAR Receiver state in BT Mesh stack isn't sufficient then the SAR Receiver default state
// <i> can be customized and overridden by activating this configuration option.
// <i> The SAR Receiver state is configured before provisioning once because the BT Mesh stack stores the SAR
// <i> Receiver state persistently so the SAR Configuration Client can modify the default value after provisioning.
#define SL_BTMESH_SAR_CONFIG_SERVER_CUSTOM_RECEIVER_CFG_VAL  0

// <o SL_BTMESH_SAR_CONFIG_SERVER_RX_SEGMENTS_THRESHOLD_CFG_VAL> Default SAR Receiver Segments Threshold
// <i> Default SAR Receiver Segments Threshold state represents the size of a segmented message in number of segments
// <i> above which the Segment Acknowledgment messages are enabled.
// <i> Valid range is 0 - 31.
// <i> Default value is 3 (segments).
// <0..31:1>
// <d> 3
#define SL_BTMESH_SAR_CONFIG_SERVER_RX_SEGMENTS_THRESHOLD_CFG_VAL  3

// <o SL_BTMESH_SAR_CONFIG_SERVER_RX_ACK_DELAY_INC_CFG_VAL> Default SAR Receiver Acknowledgment Delay Increment
// <i> Default SAR Receiver Acknowledgment Delay Increment state controls the interval between the reception of a new
// <i> segment of a segmented message for a destination that is a unicast address and the transmission of the Segment
// <i> Acknowledgment for that message.
// <i> Formula: Acknowledgment Delay Increment = SAR Acknowledgment Delay Increment + 1.5
// <i> Valid range is 0 - 7.
// <i> Default is 2, resulting in 3.5 segment transmission interval steps.
// <0..7:1>
// <d> 2
#define SL_BTMESH_SAR_CONFIG_SERVER_RX_ACK_DELAY_INC_CFG_VAL  2

// <o SL_BTMESH_SAR_CONFIG_SERVER_RX_DISCARD_TIMEOUT_MS_CFG_VAL> Default SAR Receiver Discard Timeout [ms]
// <i> Default SAR Receiver Discard Timeout state controls the time that the lower transport layer waits after receiving
// <i> unique segments of a segmented message before discarding that segmented message in 5s steps.
// <i> Valid range is 5000 - 80000ms, intermediate values are rounded down to the nearest multiple of 5s.
// <i> Default value is 10000ms.
// <5000..80000:5000>
// <d> 10000
#define SL_BTMESH_SAR_CONFIG_SERVER_RX_DISCARD_TIMEOUT_MS_CFG_VAL  10000

// <o SL_BTMESH_SAR_CONFIG_SERVER_RX_SEGMENT_INTERVAL_STEP_MS_CFG_VAL> Default SAR Receiver Segment Interval Step [ms]
// <i> Default SAR Receiver Segment Interval Step state indicates the interval between received segments of a segmented
// <i> message in milliseconds. This is used to control rate of transmission of Segment Acknowledgment messages.
// <i> Valid range is 10 - 160ms, intermediate values are rounded down to the nearest multiple of 10.
// <i> Default value is 20ms.
// <10..160:10>
// <d> 20
#define SL_BTMESH_SAR_CONFIG_SERVER_RX_SEGMENT_INTERVAL_STEP_MS_CFG_VAL  20

// <o SL_BTMESH_SAR_CONFIG_SERVER_RX_ACK_RETRANS_COUNT_CFG_VAL> Default SAR Receiver Acknowledgment Retransmissions Count
// <i> Default SAR Receiver Acknowledgment Retransmissions Count state controls the maximum number of retransmissions of
// <i> Segment Acknowledgment messages sent by the lower transport layer.
// <i> Valid range is 0 - 3.
// <i> Default value is 2, representing 2 retransmissions or 3 in total.
// <0..3:1>
// <d> 2
#define SL_BTMESH_SAR_CONFIG_SERVER_RX_ACK_RETRANS_COUNT_CFG_VAL  2

// </e>

// <<< end of configuration section >>>

#endif // SL_BTMESH_SAR_CONFIG_SERVER_CONFIG_H
