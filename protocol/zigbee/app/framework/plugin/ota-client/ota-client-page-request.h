/***************************************************************************//**
 * @file
 * @brief Zigbee Over-the-air bootload cluster for upgrading firmware and
 * downloading device specific file.
 * This file handles the page request feature for the client.
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

enum {
  EM_AF_NO_PAGE_REQUEST              = 0,
  EM_AF_WAITING_PAGE_REQUEST_REPLIES = 1,
  EM_AF_RETRY_MISSED_PACKETS         = 2,
  EM_AF_PAGE_REQUEST_COMPLETE        = 3,
  EM_AF_BLOCK_ALREADY_RECEIVED       = 4,
  EM_AF_PAGE_REQUEST_ERROR           = 0xFF
};
typedef uint8_t sli_zigbee_af_page_request_client_status;

#define EM_AF_PAGE_REQUEST_BLOCK_SIZE 32

// This routine returns a timer indicating how long we should wait for
// the page request responses to come in.  0 if there was an error.
uint32_t sli_zigbee_af_init_page_request_client(uint32_t offsetForPageRequest,
                                                uint32_t totalImageSize);
void sli_zigbee_af_page_request_timer_expired(void);
bool sli_zigbee_af_handling_page_request_client(void);
sli_zigbee_af_page_request_client_status sli_zigbee_af_get_current_page_request_status(void);
sli_zigbee_af_page_request_client_status sli_zigbee_af_note_received_block_for_page_request_client(uint32_t offset);
sli_zigbee_af_page_request_client_status sli_zigbee_af_next_missed_block_request_offset(uint32_t* nextOffset);

uint32_t sli_zigbee_af_get_page_request_missed_packet_delay_ms(void);
uint32_t sli_zigbee_af_get_finished_page_request_offset(void);
void sli_zigbee_af_abort_page_request(void);
