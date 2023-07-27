/***************************************************************************//**
 * @file
 * @brief Pacgaking Assitent file.
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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
// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include "sl_flex_rail_package_assistant.h"
#include "sl_flex_rail_package_assistant_config.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------
static uint8_t print_packet_info = PRINT_PACKAGE_INFO;

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------
uint8_t get_print_packet_info(void)
{
  return print_packet_info;
}

void set_print_packet_info(uint8_t new_print_packet_info)
{
  print_packet_info = new_print_packet_info;
}

#if defined(RAIL0_CHANNEL_GROUP_1_PROFILE_WISUN_FSK)
/******************************************************************************
 * The API helps to unpack the received packet, point to the payload and returns the length.
 *****************************************************************************/
uint16_t unpack_packet(uint8_t *rx_destination, const RAIL_RxPacketInfo_t *packet_information, uint8_t **start_of_payload)
{
  uint16_t payload_size = 0;

  RAIL_CopyRxPacket(rx_destination, packet_information);
  uint8_t fcsType = 0U;
  uint8_t whitening = 0U;
  *start_of_payload
    = sl_flex_802154_packet_unpack_sunfsk_2byte_data_frame(packet_information,
                                                           &fcsType,
                                                           &whitening,
                                                           &payload_size,
                                                           rx_destination);
  if (print_packet_info) {
    #if defined(SL_CATALOG_APP_LOG_PRESENT)
    app_log_info("WISUN_FSK Package is ready, %d bytes payload read with %d fcsType and %d whitening\n ", payload_size, fcsType, whitening);
    #endif
  }
  return payload_size;
}

/******************************************************************************
 * The API prepares the packet for sending and load it in the RAIL TX FIFO
 *****************************************************************************/
void prepare_package(RAIL_Handle_t rail_handle, uint8_t *out_data, uint16_t length)
{
  // Check if write fifo has written all bytes
  uint16_t bytes_writen_in_fifo = 0;
  uint16_t packet_size = 0U;
  uint8_t tx_frame_buffer[256];
  uint8_t fcsType = WISUN_FSK_FCS_TYPE;
  uint8_t whitening = WISUN_FSK_WHITENING;
  sl_flex_802154_packet_pack_sunfsk_2bytes_data_frame(fcsType,
                                                      whitening,
                                                      length,
                                                      out_data,
                                                      &packet_size,
                                                      tx_frame_buffer);
  bytes_writen_in_fifo = RAIL_WriteTxFifo(rail_handle, tx_frame_buffer, packet_size, true);
  #if defined(SL_CATALOG_APP_ASSERT_PRESENT)
  app_assert(bytes_writen_in_fifo == packet_size,
             "RAIL_WriteTxFifo() failed to write in fifo (%d bytes instead of %d bytes)\n",
             bytes_writen_in_fifo,
             packet_size);
  #endif
  if (print_packet_info) {
    #if defined(SL_CATALOG_APP_LOG_PRESENT)
    app_log_info("WISUN_FSK Package is ready, %d bytes written with %d fcsType and %d whitening\n ", bytes_writen_in_fifo, fcsType, whitening);
    #endif
  }
}
#elif defined(RAIL0_CHANNEL_GROUP_1_PROFILE_WISUN_OFDM)
/******************************************************************************
 * The API helps to unpack the received packet, point to the payload and returns the length.
 *****************************************************************************/
uint16_t unpack_packet(uint8_t *rx_destination,
                       const RAIL_RxPacketInfo_t *packet_information,
                       uint8_t **start_of_payload)
{
  uint16_t payload_size = 0U;
  uint8_t rate = 0U;
  uint8_t scrambler = 0U;

  RAIL_CopyRxPacket(rx_destination, packet_information);
  *start_of_payload = sl_flex_802154_packet_unpack_ofdm_data_frame(packet_information,
                                                                   &rate,
                                                                   &scrambler,
                                                                   &payload_size,
                                                                   rx_destination);
  if (print_packet_info) {
    #if defined(SL_CATALOG_APP_LOG_PRESENT)
    app_log_info("WISUN_OFDM Package is ready, %d bytes payload read with %d rate and %d scrambler\n ", payload_size, rate, scrambler);
    #endif
  }
  return payload_size;
}

/******************************************************************************
 * The API prepares the packet for sending and load it in the RAIL TX FIFO
 *****************************************************************************/
void prepare_package(RAIL_Handle_t rail_handle, uint8_t *out_data, uint16_t length)
{
  // Check if write fifo has written all bytes
  uint16_t bytes_writen_in_fifo = 0;
  uint16_t packet_size = 0U;
  uint8_t tx_frame_buffer[256];
  uint8_t rate = WISUN_OFDM_RATE;     // rate: 5 bits wide, The Rate field (RA4-RA0) specifies the data rate of the payload and is equal to the numerical value of the MCS
  // 0x0 BPSK, coding rate 1/2, 4 x frequency repetition
  // 0x1 BPSK, coding rate 1/2, 2 x frequency repetition
  // 0x2 QPSK, coding rate 1/2, 2 x frequency repetition
  // 0x3 QPSK, coding rate 1/2
  // 0x4 QPSK, coding rate 3/4
  // 0x5 16-QAM, coding rate 1/2
  // 0x6 16-QAM, coding rate 3/4
  uint8_t scrambler = WISUN_OFDM_SCRAMBLER; // scrambler: 2 bits wide, The Scrambler field (S1-S0) specifies the scrambling seed

  sl_flex_802154_packet_pack_ofdm_data_frame(rate,
                                             scrambler,
                                             length,
                                             out_data,
                                             &packet_size,
                                             tx_frame_buffer);
  bytes_writen_in_fifo = RAIL_WriteTxFifo(rail_handle, tx_frame_buffer, packet_size, true);

  #if defined(SL_CATALOG_APP_ASSERT_PRESENT)
  app_assert(bytes_writen_in_fifo == packet_size,
             "RAIL_WriteTxFifo() failed to write in fifo (%d bytes instead of %d bytes)\n",
             bytes_writen_in_fifo,
             packet_size);
  #endif
  if (print_packet_info) {
    #if defined(SL_CATALOG_APP_LOG_PRESENT)
    app_log_info("WISUN_OFDM Package is ready, %d bytes written with %d rate and %d scrambler\n ", bytes_writen_in_fifo, rate, scrambler);
    #endif
  }
}

#elif defined(RAIL0_CHANNEL_GROUP_1_PROFILE_SUN_OQPSK)
/******************************************************************************
 * The API helps to unpack the received packet, point to the payload and returns the length.
 *****************************************************************************/
uint16_t unpack_packet(uint8_t *rx_destination, const RAIL_RxPacketInfo_t *packet_information, uint8_t **start_of_payload)
{
  uint16_t payload_size = 0U;
  bool spreadingMode = false;
  uint8_t rateMode = 0U;

  RAIL_CopyRxPacket(rx_destination, packet_information);
  *start_of_payload = sl_flex_802154_packet_unpack_oqpsk_data_frame(packet_information,
                                                                    &spreadingMode,
                                                                    &rateMode,
                                                                    &payload_size,
                                                                    rx_destination);
  if (print_packet_info) {
    #if defined(SL_CATALOG_APP_LOG_PRESENT)
    app_log_info("SUN_OQPSK Package is ready, %d bytes payload read with %d spreading mode and %d rate mode\n ", payload_size, spreadingMode, rateMode);
    #endif
  }
  return payload_size;
}

/******************************************************************************
 * The API prepares the packet for sending and load it in the RAIL TX FIFO
 *****************************************************************************/
void prepare_package(RAIL_Handle_t rail_handle, uint8_t *out_data, uint16_t length)
{
  // Check if write fifo has written all bytes
  uint16_t bytes_writen_in_fifo = 0;
  uint16_t packet_size = 0U;
  uint8_t tx_frame_buffer[256];
  bool spreadingMode = (bool)SUN_OQPSK_SPREADINGMODE;
  uint8_t rateMode = SUN_OQPSK_RATEMODE; // rateMode: 2 bits wide

  sl_flex_802154_packet_pack_oqpsk_data_frame(spreadingMode,
                                              rateMode,
                                              length,
                                              out_data,
                                              &packet_size,
                                              tx_frame_buffer);

  bytes_writen_in_fifo = RAIL_WriteTxFifo(rail_handle, tx_frame_buffer, packet_size, true);
  #if defined(SL_CATALOG_APP_ASSERT_PRESENT)
  app_assert(bytes_writen_in_fifo == packet_size,
             "RAIL_WriteTxFifo() failed to write in fifo (%d bytes instead of %d bytes)\n",
             bytes_writen_in_fifo,
             packet_size);
  #endif
  if (print_packet_info) {
    #if defined(SL_CATALOG_APP_LOG_PRESENT)
    app_log_info("SUN_OQPSK Package is ready, %d bytes written with %d spreading mode and %d rate mode\n ", bytes_writen_in_fifo, spreadingMode, rateMode);
    #endif
  }
}
#elif defined(RAIL0_CHANNEL_GROUP_1_PROFILE_BASE) && (defined(RAIL0_CHANNEL_GROUP_1_PHY_SIDEWALK_2GFSK_50KBPS) || defined(RAIL0_CHANNEL_GROUP_1_PHY_SIDEWALK_2GFSK_150KBPS) || defined(RAIL0_CHANNEL_GROUP_1_PHY_SIDEWALK_2GFSK_250KBPS)) || defined(RAIL0_CHANNEL_GROUP_1_PROFILE_SIDEWALK) || defined(RAIL0_CHANNELS_FOR_915_PROFILE_SIDEWALK)
/******************************************************************************
 * The API helps to unpack the received packet, point to the payload and returns the length.
 *****************************************************************************/
uint16_t unpack_packet(uint8_t *rx_destination, const RAIL_RxPacketInfo_t *packet_information, uint8_t **start_of_payload)
{
  uint16_t payload_size = 0;

  RAIL_CopyRxPacket(rx_destination, packet_information);
  uint8_t fcsType = 0U;
  uint8_t whitening = 0U;
  *start_of_payload
    = sl_flex_802154_packet_unpack_sidewalk_data_frame(packet_information,
                                                       &fcsType,
                                                       &whitening,
                                                       &payload_size,
                                                       rx_destination);
  if (print_packet_info) {
    #if defined(SL_CATALOG_APP_LOG_PRESENT)
    app_log_info("SideWalk Package is ready, %d bytes payload read with %d fcsType and %d whitening\n ", payload_size, fcsType, whitening);
    #endif
  }
  return payload_size;
}

/******************************************************************************
 * The API prepares the packet for sending and load it in the RAIL TX FIFO
 *****************************************************************************/
void prepare_package(RAIL_Handle_t rail_handle, uint8_t *out_data, uint16_t length)
{
  // Check if write fifo has written all bytes
  uint16_t bytes_writen_in_fifo = 0;
  uint16_t packet_size = 0U;
  uint8_t tx_frame_buffer[256];
  uint8_t fcsType = SIDEWALK_FSK_FCS_TYPE;
  uint8_t whitening = SIDEWALK_FSK_WHITENING;
  sl_flex_802154_packet_pack_sidewalk_data_frame(fcsType,
                                                 whitening,
                                                 length,
                                                 out_data,
                                                 &packet_size,
                                                 tx_frame_buffer);
  bytes_writen_in_fifo = RAIL_WriteTxFifo(rail_handle, tx_frame_buffer, packet_size, true);
  #if defined(SL_CATALOG_APP_ASSERT_PRESENT)
  app_assert(bytes_writen_in_fifo == packet_size,
             "RAIL_WriteTxFifo() failed to write in fifo (%d bytes instead of %d bytes)\n",
             bytes_writen_in_fifo,
             packet_size);
  #endif
  if (print_packet_info) {
    #if defined(SL_CATALOG_APP_LOG_PRESENT)
    app_log_info("SideWalk Package is ready, %d bytes written with %d fcsType and %d whitening\n ", bytes_writen_in_fifo, fcsType, whitening);
    #endif
  }
}

#else
/******************************************************************************
 * The API helps to unpack the received packet, point to the payload and returns the length.
 *****************************************************************************/
uint16_t unpack_packet(uint8_t *rx_destination, const RAIL_RxPacketInfo_t *packet_information, uint8_t **start_of_payload)
{
  RAIL_CopyRxPacket(rx_destination, packet_information);
  *start_of_payload = rx_destination;

  if (print_packet_info) {
    #if defined(SL_CATALOG_APP_LOG_PRESENT)
    app_log_info("Package is ready, %d bytes read\n", packet_information->packetBytes);
    #endif
  }

  return packet_information->packetBytes;
}

/******************************************************************************
 * The API prepares the packet for sending and load it in the RAIL TX FIFO
 *****************************************************************************/
void prepare_package(RAIL_Handle_t rail_handle, uint8_t *out_data, uint16_t length)
{
  // Check if write fifo has written all bytes
  uint16_t bytes_writen_in_fifo = 0;
  bytes_writen_in_fifo = RAIL_WriteTxFifo(rail_handle, out_data, length, true);
  #if defined(SL_CATALOG_APP_ASSERT_PRESENT)
  app_assert(bytes_writen_in_fifo == length,
             "RAIL_WriteTxFifo() failed to write in fifo (%d bytes instead of %d bytes)\n",
             bytes_writen_in_fifo,
             length);
  #endif
  if (print_packet_info) {
    #if defined(SL_CATALOG_APP_LOG_PRESENT)
    app_log_info("Package is ready, %d bytes written\n", bytes_writen_in_fifo);
    #endif
  }
}
#endif

/******************************************************************************
 * The API forwards the received rx packet on CLI
 *****************************************************************************/
void printf_rx_packet(const uint8_t * const rx_buffer, uint16_t length)
{
  #if defined(SL_CATALOG_APP_LOG_PRESENT)
  if (rx_buffer == NULL) {
    app_log_error("rx_buffer pointer is NULL!\n");
  } else if (length == 0) {
    app_log_error("packet length is zero!\n");
  } else {
    app_log_info("Packet has been received: ");
    for (uint16_t i = 0; i < length; i++) {
      // last byte
      if (i == length - 1) {
        app_log_info("0x%02X", rx_buffer[i]);
      } else {
        app_log_info("0x%02X, ", rx_buffer[i]);
      }
    }
    app_log_info("\n");
  }
  #endif
}

/*****************************************************************************
* Checks phy setting to avoid errors at packet sending
*****************************************************************************/
void validation_check(void)
{
  _Static_assert(SL_RAIL_UTIL_INIT_PROTOCOL_INST0_DEFAULT == SL_RAIL_UTIL_PROTOCOL_PROPRIETARY,
                 "Please use the Flex (RAIL) - Simple TRX Standards sample app instead, which is designed to show the protocol usage.");
}
