/***************************************************************************//**
 * @file
 * @brief Trivial File Transfer Portocol Client header file
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

#ifndef __SL_TFTP_CLIENT_H__
#define __SL_TFTP_CLIENT_H__

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------

#include <stdint.h>
#include <stddef.h>
#include "cmsis_os2.h"
#include "sl_status.h"
#include "sl_ftp.h"
#include "sl_ftp_config.h"

#if SL_FTP_ENABLE_TFTP_PROTOCOL

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

/// Default TFTP host port
#define SL_TFTP_DEFAULT_HOST_PORT        69U

/// TFTP Data block size
#define SL_TFTP_DATA_BLOCK_SIZE          512UL

/// TFTP receive timeout
#define SL_TFTP_RECV_TIMEOUT_MS          8000UL

/// TFTP string max length (filename, mode)
#define SL_TFTP_STR_MAX_LEN              256UL

/// Netascii mode string
#define SL_TFTP_MODE_NETASCII_STR        "netascii"

/// Octet mode string
#define SL_TFTP_MODE_OCTET_STR           "octet"

/// Mail mode string
#define SL_TFTP_MODE_MAIL_STR            "mail"

/// Netascii mode string length
#define SL_TFTP_MODE_NETASCII_STR_LEN    8U

/// Octet mode string length
#define SL_TFTP_MODE_OCTET_STR_LEN       5U

/// Mail mode string length
#define SL_TFTP_MODE_MAIL_STR_LEN        4U

/// TFTP Read Request operation code
#define SL_TFTP_OPCODE_RRQ               1U

/// TFTP Write Request operation code
#define SL_TFTP_OPCODE_WRQ               2U

/// TFTP Data operation code
#define SL_TFTP_OPCODE_DATA              3U

/// TFTP Acknowledgement operation code
#define SL_TFTP_OPCODE_ACK               4U

/// TFTP Error operation code
#define SL_TFTP_OPCODE_ERROR             5U

/// Not defined, see error message (if any).
#define SL_TFTP_ERROCODE_NOTDEF          0U
/// File not found.
#define SL_TFTP_ERROCODE_FNOTFOUND       1U
/// Access violation.
#define SL_TFTP_ERROCODE_ACCVIOL         2U
/// Disk full or allocation exceeded.
#define SL_TFTP_ERROCODE_DISKFULL        3U
/// Illegal TFTP operation.
#define SL_TFTP_ERROCODE_ILLEGALOP       4U
/// Unknown transfer ID.
#define SL_TFTP_ERROCODE_UNKNTID         5U
/// File already exists.
#define SL_TFTP_ERROCODE_FEXIST          6U
/// No such user.
#define SL_TFTP_ERROCODE_NOUSR           7U

#if  defined(SL_WISUN_UNIT_TEST)
#warning Unit test enabled
/// TFTP Service loop for unit tests
#define SL_TFTP_SERVICE_LOOP()       for (uint8_t i = 0U; i < SL_TFTP_SERVICE_LOOP_EXPECTED_CNT; ++i)
#else
/// TFTP Service loop
#define SL_TFTP_SERVICE_LOOP()       while (1)
#endif

/// TFTP requeset packet
typedef struct sl_tftp_req_pkt {
  /// File name
  const char *filename;
  /// Mode
  const char *mode;
} sl_tftp_req_pkt_t;

/// TFTP data packet
typedef struct sl_tftp_data_pkt {
  /// Block number
  uint16_t block_num;
  /// Data ptr
  uint8_t *data;
  /// Data size
  uint16_t data_size;
} sl_tftp_data_pkt_t;

/// TFTP ack packet
typedef struct sl_tftp_ack_pkt {
  /// Block number
  uint16_t block_num;
} sl_tftp_ack_pkt_t;

/// TFTP error packet
typedef struct sl_tftp_error_pkt {
  /// Error code
  uint16_t errcode;
  /// Error message
  const char *errmsg;
} sl_tftp_error_pkt_t;

/// TFTP Packet content union
typedef union sl_tftp_pkt_content {
  /// Request
  sl_tftp_req_pkt_t request;
  /// Data
  sl_tftp_data_pkt_t data;
  /// Ack
  sl_tftp_ack_pkt_t ack;
  /// Error
  sl_tftp_error_pkt_t error;
} sl_tftp_pkt_content_t;

/// TFTP packet handler
typedef struct sl_tftp_pkt {
  /// Operation code
  uint16_t opcode;
  /// Content
  sl_tftp_pkt_content_t content;
} sl_tftp_pkt_t;

/// TFTP Client
typedef struct sl_tftp_clnt {
  /// Host address string
  const char *host;
  /// Port
  uint16_t port;
  /// Packet
  sl_tftp_pkt_t packet;
  /// Event flags
  osEventFlagsId_t evt_flags;
  /// External data pointer to WRQ
  const uint8_t * ext_data;
  /// External data size
  uint32_t ext_data_size;
  /// Data handler callback
  void (*data_hnd)(struct sl_tftp_clnt* const clnt,
                   const uint8_t * const data_ptr,
                   const uint16_t data_size);
  /// Error handler callback
  void (*error_hnd)(struct sl_tftp_clnt* const clnt,
                    const uint16_t error_code,
                    const char * error_msg);
} sl_tftp_clnt_t;

/// Data handler callback definition
typedef void (*sl_tftp_clnt_data_hnd_t)(sl_tftp_clnt_t * const clnt,
                                        const uint8_t * const data_ptr,
                                        const uint16_t data_size);

/// Error handler callback defintion
typedef void (*sl_tftp_clnt_error_hnd_t)(sl_tftp_clnt_t * const clnt,
                                         const uint16_t error_code,
                                         const char *error_msg);

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

/***************************************************************************//**
 * @brief Init TFTP Client service
 * @details Initialize TFTP client OS objects
 ******************************************************************************/
void sl_tftp_clnt_service_init(void);

/***************************************************************************//**
 * @brief Init TFTP Client
 * @details Initialize TFTP Client context
 * @param[in,out] clnt Client to initialize
 * @param[in] host Host address string
 * @param[in] port Port number
 * @param[in] data_hnd Data handler callback
 * @param[in] error_hnd Error handler callback
 * @return sl_status_t SL_STATUS_OK on success, otherwise SL_STATUS_FAIL
 ******************************************************************************/
sl_status_t sl_tftp_clnt_init(sl_tftp_clnt_t * const clnt,
                              const char *host,
                              const uint16_t port,
                              sl_tftp_clnt_data_hnd_t data_hnd,
                              sl_tftp_clnt_error_hnd_t error_hnd);

/***************************************************************************//**
 * @brief Init TFTP Client default
 * @details Initialize Client with default values from config file parameters:
 *          host: SL_TFTP_CLNT_DEFAULT_HOST
 *          port: SL_TFTP_DEFAULT_HOST_PORT
 *          data_hnd: simple hex dump callback
 *          error_hnd: error code and message printer
 * @param[in,out] clnt Client to initialize
 * @return sl_status_t SL_STATUS_OK on success, otherwise SL_STATUS_FAIL
 ******************************************************************************/
__STATIC_INLINE sl_status_t sl_tftp_clnt_default_init(sl_tftp_clnt_t * const clnt)
{
  return sl_tftp_clnt_init(clnt, SL_TFTP_CLNT_DEFAULT_HOST,
                           SL_TFTP_DEFAULT_HOST_PORT,
                           NULL, NULL);
}

/***************************************************************************//**
 * @brief Print packet
 * @details Print packet info in json format
 * @param[in] pkt Packet to print
 ******************************************************************************/
void sl_tftp_clnt_print_pkt(const sl_tftp_pkt_t * const pkt);

/***************************************************************************//**
 * @brief TFTP Client request
 * @details Send request for Server (RRQ or WRQ)
 * @param[in,out] clnt Client
 * @param[in] opcode Operation code: SL_TFTP_OPCODE_RRQ or SL_TFTP_OPCODE_WRQ
 * @param[in] file File name to put or get
 * @param[in] mode Mode string
 * @return sl_status_t SL_STATUS_OK on success, otherwise SL_STATUS_FAIL
 ******************************************************************************/
sl_status_t sl_tftp_clnt_request(sl_tftp_clnt_t * const clnt,
                                 const uint16_t opcode,
                                 const char *file,
                                 const char *mode);

/***************************************************************************//**
 * @brief TFT Client Get
 * @details Get file from server in netascii mode
 * @param[in,out] clnt Client
 * @param[in] file File name
 * @return sl_status_t SL_STATUS_OK on success, otherwise SL_STATUS_FAIL
 ******************************************************************************/
__STATIC_INLINE sl_status_t sl_tftp_clnt_get(sl_tftp_clnt_t * const clnt, const char *file)
{
  return sl_tftp_clnt_request(clnt, SL_TFTP_OPCODE_RRQ, file, SL_TFTP_MODE_NETASCII_STR);
}

/***************************************************************************//**
 * @brief TFT Client Put
 * @details Send buffer content to file on remote server
 * @param[in,out] clnt Client
 * @param[in] file File name to store data
 * @return sl_status_t SL_STATUS_OK on success, otherwise SL_STATUS_FAIL
 ******************************************************************************/
__STATIC_INLINE sl_status_t sl_tftp_clnt_put(sl_tftp_clnt_t * const clnt, const char *file)
{
  return sl_tftp_clnt_request(clnt, SL_TFTP_OPCODE_WRQ, file, SL_TFTP_MODE_NETASCII_STR);
}

/***************************************************************************//**
 * @brief TFTP Client is finished operation
 * @details Check read or write operations wheither is in progress
 * @param[in] clnt Client
 * @return true Is finished
 * @return false Is in progress
 ******************************************************************************/
bool sl_tftp_clnt_is_op_finished(const sl_tftp_clnt_t * const clnt);

/***************************************************************************//**
 * @brief TFTP Client is Get operation
 * @details Check Read operation is in progress
 * @param[in] clnt Client
 * @return true Is in progress otherwise false
 ******************************************************************************/
bool sl_tftp_clnt_is_op_get(const sl_tftp_clnt_t * const clnt);

/***************************************************************************//**
 * @brief TFTP Client is Put operation
 * @details Check Write operation is in progress
 * @param[in] clnt Client
 * @return true Is in progress otherwise false
 ******************************************************************************/
bool sl_tftp_clnt_is_op_put(const sl_tftp_clnt_t * const clnt);

#endif

#ifdef __cplusplus
}
#endif
#endif
