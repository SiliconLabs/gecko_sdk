#ifndef __SL_WISUN_NETWORK_MEASUREMENT_REMOTE_CTRL_H__
#define __SL_WISUN_NETWORK_MEASUREMENT_REMOTE_CTRL_H__

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------

#include "sl_wisun_coap.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief Network Measurement Remote Control CoAP CLI ping measurement callback.
 * @details Handle incoming CLI command from CoAP message.
 * @param[in] req_packet Request packet.
 * @return sl_wisun_coap_packet_t * Response packet ptr
 *****************************************************************************/
sl_wisun_coap_packet_t * sl_wisun_coap_remote_cli_ping_cb(const sl_wisun_coap_packet_t * const req_packet);

/**************************************************************************//**
 * @brief Network Measurement Remote Control CoAP CLI iPerf measurement callback.
 * @details Handle incoming CLI command from CoAP message.
 * @param[in] req_packet Request packet.
 * @return sl_wisun_coap_packet_t * Response packet ptr
 *****************************************************************************/
sl_wisun_coap_packet_t * sl_wisun_coap_remote_cli_iperf_cb(const sl_wisun_coap_packet_t * const req_packet);

/**************************************************************************//**
 * @brief Network Measurement Remote Control CoAP CLI neighbour callback.
 * @details Handle incoming CLI command from CoAP message.
 * @param[in] req_packet Request packet.
 * @return sl_wisun_coap_packet_t * Response packet ptr
 *****************************************************************************/
sl_wisun_coap_packet_t * sl_wisun_coap_remote_cli_nbr_cb(const sl_wisun_coap_packet_t * const req_packet);

#endif
