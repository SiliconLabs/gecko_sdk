/**
 * @file
 *
 * This module contains the functionality to send frames from the application
 * to the protocol. It has a FIFO to ensure determinism in the process.
 * The queue size is configurable since it is heavily dependent on the use case
 * of the application.
 * The default size is set to 2 since this is the minimum for our sample
 * applications. The user must configure it for optimal memory usage.
 * @copyright 2023 Silicon Laboratories Inc.
 */

#ifndef ZAF_TRANSPORT_TX_H_
#define ZAF_TRANSPORT_TX_H_

#include <stdint.h>
#include <stdbool.h>
#include "ZAF_types.h"

/**
 * @addtogroup ZAF
 * @{
 * @addtogroup ZAF_Transport
 * @{
 */

typedef struct {
  uint16_t dest_node_id;              ///< If provided, then the frame is only sent to this node. If zero, then it's sent to entire group
  const agi_profile_t *agi_profile;   ///< AGI profile. If NULL, is lifeline.
  uint8_t source_endpoint;            ///< Endpoint that sends the frame. Zero for root device.
  uint8_t dest_endpoint;              ///< Endpoint that receives the frame. Zero for root device. Ignored if dest_node_id is zero.
  uint8_t tx_options;                 ///< Transmit option flags.
  security_key_t security_key;        ///< Security key.
  bool bit_addressing;                ///< Tells if bit addressing should be used
  bool use_supervision;               ///< Tells if supervision should be used
} zaf_tx_options_t;

/**
 * Type used by the callbacks that are called once the tranmission is done
 */
typedef void(*zaf_tx_callback_t)(transmission_result_t * pTxResult);

/**
 * Sends a frame to the controller which is to be transmitted
 *
 * @param frame Pointer to the frame
 * @param frame_length Frame length
 * @param callback Callback which is called once the transmission is done
 * @param zaf_tx_options Transmit options
 * @return true In case the module is capable enqueueing the frame
 * @return false In case the module is not capable enqueueing the frame
 */
bool zaf_transport_tx(const uint8_t *frame, uint8_t frame_length, zaf_tx_callback_t callback, zaf_tx_options_t *zaf_tx_options);

/**
 * Converts the Receive Options to the Transmit Options needed by this module
 *
 * @param rx_options A pointer to the receive options
 * @param tx_options A pointer to the transmit options
 */
void zaf_transport_rx_to_tx_options(RECEIVE_OPTIONS_TYPE_EX *rx_options, zaf_tx_options_t* tx_options);

/**
 * Resumes the transport queue
 *
 */
void zaf_transport_resume(void);

/**
 * Pauses the transport queue
 *
 * @remarks This module is asynchronous therefore when using the pause
 * functionality the user MUST be aware of deadlock situations
 */
void zaf_transport_pause(void);

/**
 * Initializes the transport queue and needed variables
 *
 */
void zaf_transport_init(void);

/**
 * @} // ZAF_Transport
 * @} // ZAF
 */

#endif /* ZAF_TRANSPORT_TX_H_ */
