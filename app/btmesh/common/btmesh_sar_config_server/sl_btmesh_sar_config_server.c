/***************************************************************************//**
 * @file
 * @brief BT Mesh SAR Configuration Server
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

#include <stdint.h>
#include <string.h>

#include "sl_status.h"
#include "sl_bt_api.h"
#include "sl_btmesh_api.h"

#include "app_assert.h"

#include "sl_btmesh_sar_config_server.h"
#include "sl_btmesh_sar_config_server_config.h"

/***************************************************************************//**
 * @addtogroup sar_config_server BT Mesh SAR Configuration Server
 * @{
 ******************************************************************************/

// -----------------------------------------------------------------------------
// Macros

// Utility macro to check if any default SAR state value needs to be customized
#define SL_BTMESH_SAR_CONFIG_SERVER_CUSTOM_DEFAULT         \
  (SL_BTMESH_SAR_CONFIG_SERVER_CUSTOM_TRANSMITTER_CFG_VAL) \
  || (SL_BTMESH_SAR_CONFIG_SERVER_CUSTOM_RECEIVER_CFG_VAL)

// -----------------------------------------------------------------------------
// Enums, structs, typedefs

/***************************************************************************//**
 * Segmentation and Reassembly Transmitter Configuration State
 *
 * The structure members are in the descending order of alignment requirement and
 * care shall be taken to eliminate padding bytes to support struct comparison
 * by memcmp.
 ******************************************************************************/
typedef struct {
  /// Unicast Retransmissions Interval Step state controls the minimum interval
  /// between retransmissions of segments of a segmented message for a destination
  /// that is a unicast address in milliseconds.
  /// Valid range is 25 - 400ms in 25ms steps.
  uint16_t unicast_retrans_interval_step_ms;
  /// Unicast Retransmissions Interval Increment state controls the incremental
  /// component (TTL) of the interval between retransmissions of segments of a
  /// segmented message for a destination that is a unicast address in milliseconds.
  /// Valid range is 25 - 400ms in 25ms steps.
  uint16_t unicast_retrans_interval_inc_ms;
  /// Multicast Retransmissions Interval Step state controls the interval between
  /// retransmissions of segments of a segmented message for a destination that
  /// is a group address or a virtual address in milliseconds.
  /// Valid range is 25-400ms in 25ms steps.
  uint16_t multicast_retrans_interval_step_ms;
  /// Segment Interval Step controls the interval between transmissions of
  /// segments of a segmented message in milliseconds.
  /// The value is the range of 10ms to 160ms in 10ms steps.
  uint8_t segment_interval_step_ms;
  /// Unicast Retransmission Count state controls the maximum number of
  /// transmissions of segments of segmented messages to a unicast destination.
  /// Valid range is 0 - 15, where 0 represents a single transmission.
  uint8_t unicast_retrans_count;
  /// Unicast Retransmissions Without Progress Count state controls the maximum
  /// number of retransmissions of segments of segmented messages to a unicast
  /// destination without progress (without newly marking any segments acknowledged).
  /// Valid range is 0 - 15, where 0 represents a single transmission.
  uint8_t unicast_retrans_wo_progress_count;
  /// Multicast Retransmissions Count state controls the maximum number of
  /// transmissions of segments of segmented messages to a group address or
  /// a virtual address.
  /// Valid range is 0 - 15, where 0 represents a single transmission.
  uint8_t multicast_retrans_count;
} sl_btmesh_sar_config_server_transmitter_t;

/***************************************************************************//**
 * Segmentation and Reassembly Receiver Configuration State
 *
 * The structure members are in the descending order of alignment requirement and
 * care shall be taken to eliminate padding bytes to support struct comparison
 * by memcmp.
 ******************************************************************************/
typedef struct {
  /// Discard Timeout state controls the time that the lower transport layer
  /// waits after receiving unique segments of a segmented message before
  /// discarding that segmented message in milliseconds.
  /// Valid range is 5000 - 80000ms in 5000ms steps.
  uint32_t discard_timeout_ms;
  /// Segments Threshold state represents the size of a segmented message in number
  /// of segments above which the Segment Acknowledgment messages are enabled.
  /// Valid range is 0 - 31.
  uint8_t segments_threshold;
  /// Acknowledgment Delay Increment state controls the interval between the
  /// reception of a new segment of a segmented message for a destination that
  /// is a unicast address and the transmission of the Segment Acknowledgment
  /// for that message.
  /// Formula: Acknowledgment Delay Increment = SAR Acknowledgment Delay Increment + 1.5
  /// Valid range is 0 - 7.
  uint8_t ack_delay_increment;
  /// Segment Interval Step state indicates the interval between received
  /// segments of a segmented message in milliseconds. This is used to control
  /// rate of transmission of Segment Acknowledgment messages.
  /// Valid range is 10 - 160ms in 10ms steps.
  uint8_t segment_interval_step_ms;
  /// Acknowledgment Retransmissions Count state controls the maximum number
  /// of retransmissions of Segment Acknowledgment messages sent by the lower
  /// transport layer.
  /// Valid range is 0 - 3.
  uint8_t ack_retrans_count;
} sl_btmesh_sar_config_server_receiver_t;

// -----------------------------------------------------------------------------
// Private function declarations

/*******************************************************************************
 * Overrides default SAR Transmitter and Receiver states in BT Mesh stack
 *
 * The SAR Transmitter and Receiver default states are modified in the BT
 * Mesh stack on sl_btmesh_evt_node_initialized_id event when the device is
 * unprovisioned. The current SAR Transmitter and Receiver states can be modified
 * by SAR Configuration Client after provisioning, and therefore the default
 * state values can be overwritten remotely this way.
 ******************************************************************************/
#if SL_BTMESH_SAR_CONFIG_SERVER_CUSTOM_DEFAULT
static void sl_btmesh_sar_config_server_override_defaults(void);
#endif

// -----------------------------------------------------------------------------
// Static variables

#if SL_BTMESH_SAR_CONFIG_SERVER_CUSTOM_TRANSMITTER_CFG_VAL
// Custom SAR Transmitter Default State
static const sl_btmesh_sar_config_server_transmitter_t sar_conf_tx_default = {
  .segment_interval_step_ms = SL_BTMESH_SAR_CONFIG_SERVER_TX_SEGMENT_INTERVAL_STEP_MS_CFG_VAL,
  .unicast_retrans_count = SL_BTMESH_SAR_CONFIG_SERVER_TX_UNICAST_RETRANS_COUNT_CFG_VAL,
  .unicast_retrans_wo_progress_count = SL_BTMESH_SAR_CONFIG_SERVER_TX_UNICAST_RETRANS_WO_PROG_COUNT_CFG_VAL,
  .unicast_retrans_interval_step_ms = SL_BTMESH_SAR_CONFIG_SERVER_TX_UNICAST_RETRANS_INTERVAL_STEP_MS_CFG_VAL,
  .unicast_retrans_interval_inc_ms = SL_BTMESH_SAR_CONFIG_SERVER_TX_UNICAST_RETRANS_INTERVAL_INC_MS_CFG_VAL,
  .multicast_retrans_count = SL_BTMESH_SAR_CONFIG_SERVER_TX_MULTICAST_RETRANS_COUNT_CFG_VAL,
  .multicast_retrans_interval_step_ms = SL_BTMESH_SAR_CONFIG_SERVER_TX_MULTICAST_RETRANS_INTERVAL_STEP_MS_CFG_VAL
};
#endif // SL_BTMESH_SAR_CONFIG_SERVER_CUSTOM_TRANSMITTER_CFG_VAL

#if SL_BTMESH_SAR_CONFIG_SERVER_CUSTOM_RECEIVER_CFG_VAL
// Custom SAR Receiver Default State
static const sl_btmesh_sar_config_server_receiver_t sar_conf_rx_default = {
  .segments_threshold = SL_BTMESH_SAR_CONFIG_SERVER_RX_SEGMENTS_THRESHOLD_CFG_VAL,
  .ack_delay_increment = SL_BTMESH_SAR_CONFIG_SERVER_RX_ACK_DELAY_INC_CFG_VAL,
  .discard_timeout_ms = SL_BTMESH_SAR_CONFIG_SERVER_RX_DISCARD_TIMEOUT_MS_CFG_VAL,
  .segment_interval_step_ms = SL_BTMESH_SAR_CONFIG_SERVER_RX_SEGMENT_INTERVAL_STEP_MS_CFG_VAL,
  .ack_retrans_count = SL_BTMESH_SAR_CONFIG_SERVER_RX_ACK_RETRANS_COUNT_CFG_VAL
};
#endif // SL_BTMESH_SAR_CONFIG_SERVER_CUSTOM_RECEIVER_CFG_VAL

// -----------------------------------------------------------------------------
// Private function definitions

/*******************************************************************************
 * Overrides default SAR Transmitter and Receiver states in BT Mesh stack
 ******************************************************************************/
#if SL_BTMESH_SAR_CONFIG_SERVER_CUSTOM_DEFAULT
static void sl_btmesh_sar_config_server_override_defaults(void)
{
  bool sar_conf_mismatch;
  sl_status_t sc;

  // The SAR Transmitter and Receiver configuration getter and setter functions
  // don't require initialization call and it is not mandatory to have SAR
  // Configuration Server in the Device Composition Data.
  // The initialization calls are necessary only to handle SAR Config messages.

#if SL_BTMESH_SAR_CONFIG_SERVER_CUSTOM_TRANSMITTER_CFG_VAL
  sl_btmesh_sar_config_server_transmitter_t sar_conf_tx;

  // Get the current SAR Transmitter state from the BT Mesh stack
  sc = sl_btmesh_sar_config_server_get_sar_transmitter(&sar_conf_tx.segment_interval_step_ms,
                                                       &sar_conf_tx.unicast_retrans_count,
                                                       &sar_conf_tx.unicast_retrans_wo_progress_count,
                                                       &sar_conf_tx.unicast_retrans_interval_step_ms,
                                                       &sar_conf_tx.unicast_retrans_interval_inc_ms,
                                                       &sar_conf_tx.multicast_retrans_count,
                                                       &sar_conf_tx.multicast_retrans_interval_step_ms);
  app_assert_status_f(sc, "Failed to get SAR Tx Config");
  sar_conf_mismatch = memcmp(&sar_conf_tx, &sar_conf_tx_default, sizeof(sar_conf_tx));
  if (sar_conf_mismatch || (sc != SL_STATUS_OK)) {
    // If the default and current SAR Transmitter states are different then
    // the default shall be set in the BT Mesh stack
    sc = sl_btmesh_sar_config_server_set_sar_transmitter(sar_conf_tx_default.segment_interval_step_ms,
                                                         sar_conf_tx_default.unicast_retrans_count,
                                                         sar_conf_tx_default.unicast_retrans_wo_progress_count,
                                                         sar_conf_tx_default.unicast_retrans_interval_step_ms,
                                                         sar_conf_tx_default.unicast_retrans_interval_inc_ms,
                                                         sar_conf_tx_default.multicast_retrans_count,
                                                         sar_conf_tx_default.multicast_retrans_interval_step_ms);
    app_assert_status_f(sc, "Failed to set SAR Tx Config");
  }
#endif // SL_BTMESH_SAR_CONFIG_SERVER_CUSTOM_TRANSMITTER_CFG_VAL

#if SL_BTMESH_SAR_CONFIG_SERVER_CUSTOM_RECEIVER_CFG_VAL
  sl_btmesh_sar_config_server_receiver_t sar_conf_rx;

  // Get the current SAR Receiver state from the BT Mesh stack
  sc = sl_btmesh_sar_config_server_get_sar_receiver(&sar_conf_rx.segments_threshold,
                                                    &sar_conf_rx.ack_delay_increment,
                                                    &sar_conf_rx.discard_timeout_ms,
                                                    &sar_conf_rx.segment_interval_step_ms,
                                                    &sar_conf_rx.ack_retrans_count);
  app_assert_status_f(sc, "Failed to get SAR Rx Config");
  sar_conf_mismatch = memcmp(&sar_conf_rx, &sar_conf_rx_default, sizeof(sar_conf_rx));
  if (sar_conf_mismatch || (sc != SL_STATUS_OK)) {
    // If the default and current SAR Receiver states are different then
    // the default shall be set in the BT Mesh stack
    sc = sl_btmesh_sar_config_server_set_sar_receiver(sar_conf_rx_default.segments_threshold,
                                                      sar_conf_rx_default.ack_delay_increment,
                                                      sar_conf_rx_default.discard_timeout_ms,
                                                      sar_conf_rx_default.segment_interval_step_ms,
                                                      sar_conf_rx_default.ack_retrans_count);
    app_assert_status_f(sc, "Failed to set SAR Rx Config");
  }
  #endif // SL_BTMESH_SAR_CONFIG_SERVER_CUSTOM_RECEIVER_CFG_VAL
}
#endif // SL_BTMESH_SAR_CONFIG_SERVER_CUSTOM_DEFAULT

// -----------------------------------------------------------------------------
// Public function definitions
void sl_btmesh_sar_config_server_on_event(const sl_btmesh_msg_t *const evt)
{
  uint32_t event_id = SL_BT_MSG_ID(evt->header);
  sl_status_t sc;

  switch (event_id) {
    case sl_btmesh_evt_prov_initialized_id:
    case sl_btmesh_evt_node_initialized_id: {
      sc = sl_btmesh_sar_config_server_init();
      app_assert_status_f(sc, "Failed to init SAR Config Server");

      #if SL_BTMESH_SAR_CONFIG_SERVER_CUSTOM_DEFAULT
      if (sc == SL_STATUS_OK) {
        if (event_id == sl_btmesh_evt_node_initialized_id
            && !evt->data.evt_node_initialized.provisioned) {
          // The SAR Transmitter and Receiver states shall be overridden with
          // custom default values only when the device is unprovisioned to
          // avoid modifying SAR states which were set by SAR Configuration
          // Client explicitly.
          sl_btmesh_sar_config_server_override_defaults();
        }
      }
      #endif // SL_BTMESH_SAR_CONFIG_SERVER_CUSTOM_DEFAULT
      break;
    }
  }
}

/** @} end sar_config_server */
