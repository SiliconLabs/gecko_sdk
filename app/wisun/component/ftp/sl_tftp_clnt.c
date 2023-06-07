/***************************************************************************//**
 * @file
 * @brief Trivial File Transfer Portocol Client
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

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "cmsis_os2.h"
#include "sl_string.h"

#include "sl_tftp_clnt.h"

#if SL_FTP_ENABLE_TFTP_PROTOCOL

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

/// Default buffer size: 512 bytes data + highest mem footprint of header
#define SL_TFTP_DEFAULT_BUFF_SIZE          (SL_TFTP_DATA_BLOCK_SIZE + sizeof(sl_tftp_pkt_t))

/// TFTP message queue length
#define SL_TFTP_MESSAGE_QUEUE_SIZE         1UL

/// TFTP error print format
#define SL_TFTP_ERROR_PRINT_FORMAT_STR \
  "[%s] TFTP Error (%u): %s\n"

/// TFTP RRQ print format
#define SL_TFTP_RRQ_PKT_PRINT_FORMAT_STR \
  "{\n"                                  \
  "  \"opcode\": \"RRQ\",\n"             \
  "  \"filename\": \"%s\",\n"            \
  "  \"mode\": \"%s\"\n"                 \
  "}\n"

/// TFTP WRQ print format
#define SL_TFTP_WRQ_PKT_PRINT_FORMAT_STR \
  "{\n"                                  \
  "  \"opcode\": \"WRQ\",\n"             \
  "  \"filename\": \"%s\",\n"            \
  "  \"mode\": \"%s\"\n"                 \
  "}\n"

/// TFTP ACK packet print format
#define SL_TFTP_ACK_PKT_PRINT_FORMAT_STR \
  "{\n"                                  \
  "  \"opcode\": \"ACK\",\n"             \
  "  \"block\": \"%u\"\n"                \
  "}\n"

/// TFTP Error packet print format
#define SL_TFTP_ERR_PKT_PRINT_FORMAT_STR \
  "{\n"                                  \
  "  \"opcode\": \"ERROR\",\n"           \
  "  \"errcode\": \"%u\",\n"             \
  "  \"errmsg\": \"%s\"\n"               \
  "}\n"

/// TFTP Data packet print format
#define SL_TFTP_DATA_PKT_PRINT_FORMAT_STR \
  "{\n"                                   \
  "  \"opcode\": \"DATA\",\n"             \
  "  \"block\": \"%u\",\n"                \
  "  \"size\": \"%u\"\n"                  \
  "}\n"

/// TFTP Event all mask
#define SL_TFTP_EVT_ALL_MSK               (0x00FFFFFFUL)

/// Error mask
#define SL_TFTP_EVT_ERROR_MSK             (0x00000001UL << 31UL)

/// Get requeset mask
#define SL_TFTP_EVT_GET_REQUEST_MSK       (0x00000001UL << 0UL)

/// Put request mask
#define SL_TFTP_EVT_PUT_REQUEST_MSK       (0x00000001UL << 1UL)

/// Operation finished mask
#define SL_TFTP_EVT_OP_FINISHED_MSK       (0x00000001UL << 2UL)

/// Swap bytes in uint16
#define __swap_bytes_16bit(__val) \
  (((__val) >> 8U) | ((__val) << 8U))

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

/***************************************************************************//**
 * @brief Default Data handler
 * @details Default callback to dump data in hex format
 * @param[in,out] clnt Client
 * @param[in] data_ptr Data ptr
 * @param[in] data_size Data size
 ******************************************************************************/
static void _default_data_hnd(sl_tftp_clnt_t * const clnt,
                              const uint8_t * const data_ptr,
                              const uint16_t data_size);

/***************************************************************************//**
 * @brief Default Error handler
 * @details Default callback to print error code and error message
 * @param[in,out] clnt Client
 * @param[in] error_code Error code
 * @param[in] error_msg Error message
 ******************************************************************************/
__STATIC_INLINE void _default_error_hnd(sl_tftp_clnt_t * const clnt,
                                        const uint16_t error_code,
                                        const char *error_msg);

/***************************************************************************//**
 * @brief TFTP Client service thread function
 * @details Thread function
 * @param[in] args Arguments (not used)
 ******************************************************************************/
static void _clnt_thr_fnc(void * args);

/***************************************************************************//**
 * @brief Is flag mask set
 * @details Helper function
 * @param[in] clnt Client
 * @param[in] flags_msk Mask
 * @return True if mask is set, otherwise false
 ******************************************************************************/
__STATIC_INLINE bool _is_flags_set(const sl_tftp_clnt_t * const clnt, uint32_t flags_msk);

/***************************************************************************//**
 * @brief Check pointer in buffer
 * @details Helper function
 * @param ptr Pointer
 * @param buff_ptr Buffer start pointer
 * @param buff_size Buffer size
 * @return bool True if it's in the buffer, otherwise False
 ******************************************************************************/
__STATIC_INLINE bool _is_ptr_in_buff(const uint8_t * const ptr,
                                     const uint8_t * const buff_ptr,
                                     const uint16_t buff_size);

/***************************************************************************//**
 * @brief Prepare and send ack packet
 * @details Helper function
 * @param[in,out] clnt Client
 * @param[in] block_num Block number
 * @param[in] sock_id Socket ID
 * @param[in,out] buff Buffer
 * @param[in] host_addr Host address bytes
 ******************************************************************************/
static void _prepare_and_send_ack(sl_tftp_clnt_t * const clnt,
                                  const uint16_t block_num,
                                  int32_t sock_id,
                                  uint8_t *buff,
                                  void *host_addr);

/***************************************************************************//**
 * @brief Prepare and send data packet
 * @details Helper function
 * @param[in,out] clnt Clinet
 * @param[in] block_num Block number
 * @param[in] data_ptr Data ptr
 * @param[in] data_size Data size
 * @param[in] sock_id Socket ID
 * @param[in,out] buff Buffer
 * @param[in] host_addr Host address bytes
 ******************************************************************************/
static void _prepare_and_send_data(sl_tftp_clnt_t * const clnt,
                                   const uint16_t block_num,
                                   const uint8_t *data_ptr,
                                   const uint16_t data_size,
                                   int32_t sock_id,
                                   uint8_t *buff,
                                   void *host_addr);

/***************************************************************************//**
 * @brief Calculate packet size
 * @details Helper function
 * @param[in] pkt Packet
 * @return uint16_t Size of packet
 ******************************************************************************/
static uint16_t _calc_packet_size(const sl_tftp_pkt_t * const pkt);

/***************************************************************************//**
 * @brief Build packet buffer
 * @details Helper function
 * @param[in] pkt Packet
 * @param[in,out] buff Buffer
 * @param[in] buff_size Max size of buffer
 * @return uint16_t Built packet size on success, otherwise 0
 ******************************************************************************/
static uint16_t _build_packet(const sl_tftp_pkt_t * const pkt,
                              uint8_t *buff,
                              const uint16_t buff_size);

/***************************************************************************//**
 * @brief Parse packet buffer
 * @details Helper function
 * @param[in,out] dst_pkt Destination packet
 * @param[in] buff Buffer
 * @param[in] buff_size Buffer payload size
 * @return sl_status_t SL_STATUS_OK on success, otherwise SL_STATUS_FAIL
 ******************************************************************************/
static sl_status_t _parse_packet(sl_tftp_pkt_t * const dst_pkt,
                                 const uint8_t * const buff,
                                 const uint16_t buff_size);

/***************************************************************************//**
 * @brief Read Request handler
 * @details Handling socket IO to read file from remote host
 * @param[in,out] clnt Client
 * @param[in,out] buff Buffer
 * @param[in] buff_size Buffer size
 ******************************************************************************/
static void _rrq_hnd(sl_tftp_clnt_t * const clnt,
                     uint8_t * const buff,
                     const uint32_t buff_size);

/***************************************************************************//**
 * @brief Write Request handler
 * @details Handling socket IO to read file from remote host
 * @param[in,out] clnt Client
 * @param[in,out] buff Buffer
 * @param[in] buff_size Buffer size
 ******************************************************************************/
static void _wrq_hnd(sl_tftp_clnt_t * const clnt,
                     uint8_t * const buff,
                     const uint32_t buff_size);

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

/// Thread ID
static osThreadId_t _clnt_thr = NULL;

/// TFTP Client task attribute
static const osThreadAttr_t _clnt_thr_attr = {
  .name        = "TftpClntThread",
  .attr_bits   = osThreadDetached,
  .cb_mem      = NULL,
  .cb_size     = 0,
  .stack_mem   = NULL,
  .stack_size  = (SL_TFTP_CLNT_STACK_SIZE_WORD * sizeof(void *)) & 0xFFFFFFF8U,
  .priority    = osPriorityNormal7,
  .tz_module   = 0
};

/// TFTP Client message queue ID
static osMessageQueueId_t _clnt_msg_queue_in = NULL;

/// TFTP Client message queue attributes
static const osMessageQueueAttr_t _clnt_msg_queue_in_attr = {
  .name      = "TftpClntMsgQueue",
  .attr_bits = 0,
  .cb_mem    = NULL,
  .cb_size   = 0,
  .mq_mem    = NULL,
  .mq_size   = 0
};

/// TFTP Client event flag attributes
static const osEventFlagsAttr_t _clnt_evt_attr = {
  .name      = "TftpClntEvt",
  .attr_bits = 0,
  .cb_mem    = NULL,
  .cb_size   = 0
};

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

void sl_tftp_clnt_service_init(void)
{
  _clnt_msg_queue_in = osMessageQueueNew(SL_TFTP_MESSAGE_QUEUE_SIZE,
                                         sizeof(sl_tftp_clnt_t),
                                         &_clnt_msg_queue_in_attr);
  assert(_clnt_msg_queue_in != NULL);

  _clnt_thr = osThreadNew(_clnt_thr_fnc, NULL, &_clnt_thr_attr);
  assert(_clnt_thr != NULL);
}

sl_status_t sl_tftp_clnt_init(sl_tftp_clnt_t * const clnt,
                              const char *host,
                              const uint16_t port,
                              sl_tftp_clnt_data_hnd_t data_hnd,
                              sl_tftp_clnt_error_hnd_t error_hnd)
{
  if (clnt == NULL) {
    return SL_STATUS_FAIL;
  }

  clnt->evt_flags = osEventFlagsNew(&_clnt_evt_attr);
  if (clnt->evt_flags == NULL) {
    return SL_STATUS_FAIL;
  }

  clnt->host = host == NULL ? SL_TFTP_LOCAL_HOST_STR : host;
  clnt->port = port;

  clnt->data_hnd = data_hnd == NULL ? _default_data_hnd : data_hnd;
  clnt->error_hnd = error_hnd == NULL ? _default_error_hnd : error_hnd;

  return SL_STATUS_OK;
}

uint16_t _calc_packet_size(const sl_tftp_pkt_t * const pkt)
{
  if (pkt->opcode == SL_TFTP_OPCODE_RRQ
      || pkt->opcode == SL_TFTP_OPCODE_WRQ) {
    return sizeof(uint16_t) + sizeof(uint8_t) * 2U
           + sl_strnlen((char *)pkt->content.request.filename, SL_TFTP_STR_MAX_LEN)
           + sl_strnlen((char *)pkt->content.request.mode, SL_TFTP_STR_MAX_LEN);
  } else if (pkt->opcode == SL_TFTP_OPCODE_DATA) {
    return sizeof(uint16_t) * 2U + pkt->content.data.data_size;
  } else if (pkt->opcode == SL_TFTP_OPCODE_ACK) {
    return sizeof(uint16_t) * 2U;
  } else if (pkt->opcode == SL_TFTP_OPCODE_ERROR) {
    return sizeof(uint16_t) + sl_strnlen((char *)pkt->content.error.errmsg, SL_TFTP_STR_MAX_LEN);
  }

  return 0U;
}

uint16_t _build_packet(const sl_tftp_pkt_t * const pkt,
                       uint8_t *buff,
                       const uint16_t buff_size)
{
  uint16_t req_buff_size = 0U;
  uint8_t *ptr = NULL;
  int32_t res = -1;

  if (buff == NULL || pkt == NULL) {
    return 0UL;
  }

  req_buff_size = _calc_packet_size(pkt);
  if (req_buff_size > buff_size) {
    return 0UL;
  }

  ptr = buff;

  // set opcode
  *((uint16_t *)ptr) = __swap_bytes_16bit(pkt->opcode);
  ptr += sizeof(uint16_t);

  // RRQ and WRQ request
  if (pkt->opcode == SL_TFTP_OPCODE_RRQ
      || pkt->opcode == SL_TFTP_OPCODE_WRQ) {
    res = snprintf((char *)ptr, req_buff_size - sizeof(uint16_t),
                   "%s%c%s", pkt->content.request.filename, '\0',
                   pkt->content.request.mode);
    return res < 0L ? 0UL : req_buff_size;

    // Data packet
  } else if (pkt->opcode == SL_TFTP_OPCODE_DATA) {
    *((uint16_t *)ptr) = __swap_bytes_16bit(pkt->content.data.block_num);
    ptr += sizeof(uint16_t);
    memcpy(ptr, pkt->content.data.data, pkt->content.data.data_size);

    // ACK packet
  } else if (pkt->opcode == SL_TFTP_OPCODE_ACK) {
    *((uint16_t *)ptr) = __swap_bytes_16bit(pkt->content.ack.block_num);

    // Error packet
  } else if (pkt->opcode == SL_TFTP_OPCODE_ERROR) {
    *((uint16_t *)ptr) = __swap_bytes_16bit(pkt->content.error.errcode);
    ptr += sizeof(uint16_t);
    res = snprintf((char *)ptr, req_buff_size - sizeof(uint16_t) * 2U,
                   "%s", pkt->content.error.errmsg);
    return res < 0L ? 0UL : req_buff_size;
  }

  return req_buff_size;
}

sl_status_t _parse_packet(sl_tftp_pkt_t * const dst_pkt,
                          const uint8_t *buff,
                          const uint16_t buff_size)
{
  uint8_t *ptr = NULL;
  uint32_t str_len = 0UL;

  if (buff == NULL || dst_pkt == NULL) {
    return SL_STATUS_FAIL;
  }

  ptr = (uint8_t *)buff;

  dst_pkt->opcode = __swap_bytes_16bit(*((uint16_t *)ptr));
  ptr += sizeof(uint16_t);

  if (!_is_ptr_in_buff(ptr, buff, buff_size)) {
    return SL_STATUS_FAIL;
  }

  // RRQ and WRQ request
  if (dst_pkt->opcode == SL_TFTP_OPCODE_RRQ
      || dst_pkt->opcode == SL_TFTP_OPCODE_WRQ) {
    dst_pkt->content.request.filename = (const char *)ptr;
    str_len = sl_strnlen((char *)dst_pkt->content.request.filename, SL_TFTP_STR_MAX_LEN);
    if (!_is_ptr_in_buff(ptr + str_len + 1U, buff, buff_size)) {
      return SL_STATUS_FAIL;
    }

    ptr += str_len;
    dst_pkt->content.request.mode = (const char *)ptr;
    str_len = sl_strnlen((char *)dst_pkt->content.request.mode, SL_TFTP_STR_MAX_LEN);
    if (!_is_ptr_in_buff(ptr + str_len + 1U, buff, buff_size)) {
      return SL_STATUS_FAIL;
    }

    // Data packet
  } else if (dst_pkt->opcode == SL_TFTP_OPCODE_DATA) {
    dst_pkt->content.data.block_num = __swap_bytes_16bit(*((uint16_t *)ptr));
    ptr += sizeof(uint16_t);
    if (!_is_ptr_in_buff(ptr, buff, buff_size)) {
      return SL_STATUS_FAIL;
    }
    dst_pkt->content.data.data = ptr;
    // Set data size
    dst_pkt->content.data.data_size = buff_size - 2U * sizeof(uint16_t);

    // ACK packet
  } else if (dst_pkt->opcode == SL_TFTP_OPCODE_ACK) {
    dst_pkt->content.ack.block_num = __swap_bytes_16bit(*((uint16_t *)ptr));

    // Error packet
  } else if (dst_pkt->opcode == SL_TFTP_OPCODE_ERROR) {
    dst_pkt->content.error.errcode = __swap_bytes_16bit(*((uint16_t *)ptr));
    ptr += sizeof(uint16_t);

    if (!_is_ptr_in_buff(ptr, buff, buff_size)) {
      return SL_STATUS_FAIL;
    }

    dst_pkt->content.error.errmsg = (const char *)ptr;
  }

  return SL_STATUS_OK;
}

void sl_tftp_clnt_print_pkt(const sl_tftp_pkt_t * const pkt)
{
  switch (pkt->opcode) {
    case SL_TFTP_OPCODE_RRQ:
      printf(SL_TFTP_RRQ_PKT_PRINT_FORMAT_STR,
             pkt->content.request.filename,
             pkt->content.request.mode);
      break;
    case SL_TFTP_OPCODE_WRQ:
      printf(SL_TFTP_WRQ_PKT_PRINT_FORMAT_STR,
             pkt->content.request.filename,
             pkt->content.request.mode);
      break;
    case SL_TFTP_OPCODE_DATA:
      printf(SL_TFTP_DATA_PKT_PRINT_FORMAT_STR,
             pkt->content.data.block_num,
             pkt->content.data.data_size);
      break;
    case SL_TFTP_OPCODE_ACK:
      printf(SL_TFTP_ACK_PKT_PRINT_FORMAT_STR,
             pkt->content.ack.block_num);
      break;

    case SL_TFTP_OPCODE_ERROR:
      printf(SL_TFTP_ERR_PKT_PRINT_FORMAT_STR,
             pkt->content.error.errcode,
             pkt->content.error.errmsg);
      break;

    default:
      printf("[TFTP Invalid packet: %u]\n", pkt->opcode);
      break;
  }
}

sl_status_t sl_tftp_clnt_request(sl_tftp_clnt_t * const clnt,
                                 const uint16_t opcode,
                                 const char *file,
                                 const char *mode)
{
  osStatus_t status = osError;

  if (clnt == NULL
      || file == NULL
      || mode == NULL
      || !(opcode == SL_TFTP_OPCODE_RRQ || opcode == SL_TFTP_OPCODE_WRQ)) {
    printf("[TFTP get error]\n");
    return SL_STATUS_FAIL;
  }

  clnt->packet.opcode = opcode;
  clnt->packet.content.request.filename = file;
  clnt->packet.content.request.mode = mode;

  status = osMessageQueuePut(_clnt_msg_queue_in, clnt, 0U, osWaitForever);

  return status != osOK ? SL_STATUS_FAIL : SL_STATUS_OK;
}

bool sl_tftp_clnt_is_op_finished(const sl_tftp_clnt_t * const clnt)
{
  return _is_flags_set(clnt, SL_TFTP_EVT_OP_FINISHED_MSK);
}

bool sl_tftp_clnt_is_op_get(const sl_tftp_clnt_t * const clnt)
{
  return _is_flags_set(clnt, SL_TFTP_EVT_GET_REQUEST_MSK);
}

bool sl_tftp_clnt_is_op_put(const sl_tftp_clnt_t * const clnt)
{
  return _is_flags_set(clnt, SL_TFTP_EVT_GET_REQUEST_MSK);
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------

__STATIC_INLINE  bool _is_flags_set(const sl_tftp_clnt_t * const clnt, uint32_t flags_msk)
{
  uint32_t flags = 0UL;
  flags = osEventFlagsGet(clnt->evt_flags);
  return (bool) (flags & flags_msk);
}

__STATIC_INLINE bool _is_ptr_in_buff(const uint8_t * const ptr,
                                     const uint8_t * const buff_ptr,
                                     const uint16_t buff_size)
{
  return (bool) ((ptr >= buff_ptr) && (ptr < (buff_ptr + buff_size)));
}

static void _default_data_hnd(sl_tftp_clnt_t * const clnt,
                              const uint8_t * const data_ptr,
                              const uint16_t data_size)
{
  printf("[%s]\n", clnt->host);
  sl_tftp_dump_buff(data_ptr, data_size);
}

__STATIC_INLINE void _default_error_hnd(sl_tftp_clnt_t * const clnt,
                                        const uint16_t error_code,
                                        const char *error_msg)
{
  printf(SL_TFTP_ERROR_PRINT_FORMAT_STR, clnt->host, error_code, error_msg);
}

static void _prepare_and_send_ack(sl_tftp_clnt_t * const clnt,
                                  const uint16_t block_num,
                                  int32_t sock_id,
                                  uint8_t *buff,
                                  void *host_addr)
{
  uint16_t pkt_payload_size = 0U;

  clnt->packet.opcode = SL_TFTP_OPCODE_ACK;
  clnt->packet.content.ack.block_num = block_num;
  pkt_payload_size = _build_packet(&clnt->packet, buff, SL_TFTP_DEFAULT_BUFF_SIZE);
  (void) sl_tftp_udp_sendto(sock_id, buff, pkt_payload_size, host_addr);
}

static void _prepare_and_send_data(sl_tftp_clnt_t * const clnt,
                                   const uint16_t block_num,
                                   const uint8_t *data_ptr,
                                   const uint16_t data_size,
                                   int32_t sock_id,
                                   uint8_t *buff,
                                   void *host_addr)
{
  uint16_t pkt_payload_size = 0U;

  clnt->packet.opcode = SL_TFTP_OPCODE_DATA;
  clnt->packet.content.data.block_num = block_num;
  clnt->packet.content.data.data = (uint8_t *) data_ptr;
  clnt->packet.content.data.data_size = data_size;
  pkt_payload_size = _build_packet(&clnt->packet, buff, SL_TFTP_DEFAULT_BUFF_SIZE);
  (void) sl_tftp_udp_sendto(sock_id, buff, pkt_payload_size, host_addr);
}

static void _rrq_hnd(sl_tftp_clnt_t * const clnt,
                     uint8_t * const buff,
                     const uint32_t buff_size)
{
  int32_t sock_id = SL_TFTP_INVALID_SOCKID;
  uint32_t timeout = 0UL;
  uint16_t pkt_payload_size = 0U;
  uint16_t block_num = 1U;
  static uint8_t host_addr[SL_TFTP_ADDR_SIZE] = { 0U };
  int32_t res = SL_FTP_ERROR;

  sock_id = sl_tftp_udp_socket_create();
  if (sock_id == SL_TFTP_INVALID_SOCKID) {
    sl_tftp_delay_ms(100UL);
    return;
  }

  sl_tftp_udp_get_addr_bytes(clnt->host, clnt->port, host_addr, SL_TFTP_ADDR_SIZE);

  pkt_payload_size = _build_packet(&clnt->packet, buff, buff_size);
  (void) sl_tftp_udp_sendto(sock_id, buff, pkt_payload_size, host_addr);

  while (timeout < SL_TFTP_CLNT_RECV_TIMEOUT_MS) {
    sl_tftp_delay_ms(100UL);

    res = sl_tftp_udp_recvfrom(sock_id, buff, SL_TFTP_DEFAULT_BUFF_SIZE, host_addr);
    if (res <= 0L) {
      timeout += 100UL;
      continue;
    }

    if (_parse_packet(&clnt->packet, buff, res) != SL_STATUS_OK) {
      timeout += 100UL;
      continue;
    }

#if defined(SL_TFTP_DEBUG)
    sl_tftp_clnt_print_pkt(&clnt->packet);
#endif

    if (clnt->packet.opcode == SL_TFTP_OPCODE_DATA) {
      // Get block number
      block_num = clnt->packet.content.data.block_num;
      if (clnt->data_hnd != NULL) {
        clnt->data_hnd(clnt, clnt->packet.content.data.data,
                       clnt->packet.content.data.data_size);
      }
      // Prepare ACK
      _prepare_and_send_ack(clnt, block_num, sock_id,
                            buff, host_addr);
#if defined(SL_TFTP_DEBUG)
      sl_tftp_clnt_print_pkt(&clnt->packet);
#endif
      // Last packet
      if (clnt->packet.content.data.data_size < SL_TFTP_DATA_BLOCK_SIZE) {
        break;
      }
    } else if (clnt->packet.opcode == SL_TFTP_OPCODE_ERROR) {
      if (clnt->error_hnd != NULL) {
        clnt->error_hnd(clnt, clnt->packet.content.error.errcode,
                        clnt->packet.content.error.errmsg);
      }
      // Prepare ACK
      _prepare_and_send_ack(clnt, block_num, sock_id,
                            buff, host_addr);
      sl_tftp_clnt_print_pkt(&clnt->packet);
    }

    timeout = 0UL;
  }

  sl_tftp_socket_close(sock_id);
}

static void _wrq_hnd(sl_tftp_clnt_t * const clnt,
                     uint8_t * const buff,
                     const uint32_t buff_size)
{
  int32_t sock_id = SL_TFTP_INVALID_SOCKID;
  uint32_t timeout = 0UL;
  uint16_t pkt_payload_size = 0U;
  uint16_t block_num = 0U;
  uint16_t required_block_num = 0U;
  static uint8_t host_addr[SL_TFTP_ADDR_SIZE] = { 0U };
  int32_t res = SL_FTP_ERROR;
  uint8_t *ptr = NULL;
  uint32_t remained_size = 0UL;
  uint16_t data_size = 0U;

  sock_id = sl_tftp_udp_socket_create();
  if (sock_id == SL_TFTP_INVALID_SOCKID) {
    sl_tftp_delay_ms(100UL);
    return;
  }

  sl_tftp_udp_get_addr_bytes(clnt->host, clnt->port, host_addr, SL_TFTP_ADDR_SIZE);

  pkt_payload_size = _build_packet(&clnt->packet, buff, buff_size);
  (void) sl_tftp_udp_sendto(sock_id, buff, pkt_payload_size, host_addr);

  ptr = (uint8_t *) clnt->ext_data;
  remained_size = clnt->ext_data_size;
  required_block_num = remained_size / SL_TFTP_DATA_BLOCK_SIZE + 1U;
  sl_tftp_debug("Prepare transfer: 0x%p address,  %lu bytes\n", ptr, remained_size);

  while (timeout < SL_TFTP_CLNT_RECV_TIMEOUT_MS) {
    sl_tftp_delay_ms(100UL);

    res = sl_tftp_udp_recvfrom(sock_id, buff, SL_TFTP_DEFAULT_BUFF_SIZE, host_addr);
    if (res <= 0L) {
      timeout += 100UL;
      continue;
    }

    if (_parse_packet(&clnt->packet, buff, res) != SL_STATUS_OK) {
      timeout += 100UL;
      continue;
    }
#if defined(SL_TFTP_DEBUG)
    // Print received packet
    sl_tftp_clnt_print_pkt(&clnt->packet);
#endif

    if (clnt->packet.opcode == SL_TFTP_OPCODE_ACK) {
      if (!remained_size && block_num == required_block_num) {
        sl_tftp_debug("Received last ack\n");
        break;
      }
      // reset timeout counter
      timeout = 0UL;

      // store block num
      block_num = clnt->packet.content.ack.block_num;

      // set ptr and block num
      if (block_num) {
        ptr += SL_TFTP_DATA_BLOCK_SIZE;
      }
      ++block_num;

      // Set data size
      data_size = remained_size < SL_TFTP_DATA_BLOCK_SIZE ? remained_size : SL_TFTP_DATA_BLOCK_SIZE;
      remained_size -= data_size;
    } else if (clnt->packet.opcode == SL_TFTP_OPCODE_ERROR) {
      if (clnt->error_hnd != NULL) {
        clnt->error_hnd(clnt, clnt->packet.content.error.errcode,
                        clnt->packet.content.error.errmsg);
      }
      break;
    }

    _prepare_and_send_data(clnt, block_num, (const uint8_t *)ptr, data_size,
                           sock_id, buff, host_addr);
#if defined(SL_TFTP_DEBUG)
    sl_tftp_clnt_print_pkt(&clnt->packet);
    printf("[%s]\n", clnt->host);
    sl_tftp_dump_buff(ptr, data_size);
#endif
  }
  sl_tftp_debug("Closing WRQ socket\n");
  sl_tftp_socket_close(sock_id);
}

static void _clnt_thr_fnc(void * args)
{
  osStatus_t status = osError;
  uint8_t msg_prio = 0U;
  static sl_tftp_clnt_t clnt = { 0U };
  static uint8_t buff[SL_TFTP_DEFAULT_BUFF_SIZE] = { 0UL };

  (void) args;

  // wait for network connected state
  while (!sl_ftp_is_network_connected()) {
    sl_tftp_delay_ms(1000UL);
  }

  (void) osEventFlagsClear(clnt.evt_flags, SL_TFTP_EVT_ALL_MSK);

  SL_TFTP_SERVICE_LOOP() {
    // Pop Test from the queue
    status = osMessageQueueGet(_clnt_msg_queue_in, &clnt, &msg_prio, osWaitForever);
    if (status != osOK) {
      sl_tftp_delay_ms(100UL);
      continue;
    }
    sl_tftp_debug("TFTP Client started\n");

#if defined(SL_TFTP_DEBUG)
    sl_tftp_clnt_print_pkt(&clnt.packet);
#endif

    if (clnt.packet.opcode == SL_TFTP_OPCODE_RRQ) {
      (void) osEventFlagsSet(clnt.evt_flags, SL_TFTP_EVT_GET_REQUEST_MSK);
      _rrq_hnd(&clnt, buff, SL_TFTP_DEFAULT_BUFF_SIZE);
    } else if (clnt.packet.opcode == SL_TFTP_OPCODE_WRQ) {
      (void) osEventFlagsSet(clnt.evt_flags, SL_TFTP_EVT_PUT_REQUEST_MSK);
      _wrq_hnd(&clnt, buff, SL_TFTP_DEFAULT_BUFF_SIZE);
    }

    (void) osEventFlagsClear(clnt.evt_flags, SL_TFTP_EVT_ALL_MSK);
    (void) osEventFlagsSet(clnt.evt_flags, SL_TFTP_EVT_OP_FINISHED_MSK);

    // sl_tftp_socket_close(sock_id);
    sl_tftp_debug("TFTP Client socket closed\n");
    sl_tftp_delay_ms(100UL);
  }
}

#endif
