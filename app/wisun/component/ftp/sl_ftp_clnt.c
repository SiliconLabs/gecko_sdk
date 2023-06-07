/***************************************************************************//**
 * @file
 * @brief File Transfer Portocol Client header
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
#include <stdlib.h>
#include <assert.h>
#include "cmsis_os2.h"
#include "sl_ftp_clnt.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

#if SL_FTP_ENABLE_FTP_PROTOCOL

/// Server return code long string length
#define SL_FTP_SRV_RETURN_CODE_LONG_STR_LEN       5U

/// Server return code standard string length
#define SL_FTP_SRV_RETURN_CODE_STD_STR_LEN        3U

/// Server return code string buffer size
#define SL_FTP_SRV_RETURN_CODE_BUFF_SIZE          (SL_FTP_SRV_RETURN_CODE_LONG_STR_LEN + 1)

/// Print data channel line string length
#define SL_FTP_CLNT_DATA_PRINT_LINE_LEN           20UL

/// Client data ch message queue size
#define SL_FTP_MESSAGE_QUEUE_SIZE                 1UL

/// Uint8 string buffer size
#define SL_FTP_UINT8_STR_BUFF_SIZE                4U

/// Uint16 string buffer size
#define SL_FTP_UINT16_STR_BUFF_SIZE               6U

/// Data channel connect request mask
#define SL_FTP_DATA_CH_REQUEST_CONNECT_MSK        (0x00000001UL << 0UL)

/// Data channel connected response mask
#define SL_FTP_DATA_CH_RESPONSE_CONNECTED_MSK     (0x00000001UL << 1UL)

/// Data channel receive request mask
#define SL_FTP_DATA_CH_REQUEST_RECV_MSK           (0x00000001UL << 2UL)

/// Data channel send request mask
#define SL_FTP_DATA_CH_REQUEST_SEND_MSK           (0x00000001UL << 3UL)

/// Data channel close request mask
#define SL_FTP_DATA_CH_REQUEST_CLOSE_MSK          (0x00000001UL << 4UL)

/// Data channel closed response mask
#define SL_FTP_DATA_CH_RESPONSE_CLOSED_MSK        (0x00000001UL << 5UL)

/// Data channel error mask
#define SL_FTP_DATA_CH_ERROR_MSK                  (0x00000001UL << 31UL)

/// Data channel all flags mask
#define SL_FTP_DATA_CH_ALL_FLAG_MSK               (0x00FFFFFFUL)

/// Check error expression helper macro function
#define __check_err(__expression)         \
  do {                                    \
    if ((__expression) == SL_FTP_ERROR) { \
      return SL_STATUS_FAIL;              \
    }                                     \
  } while (0)

/// Check status expression helper macro function
#define __check_stat(__expression)        \
  do {                                    \
    if ((__expression) != SL_STATUS_OK) { \
      return SL_STATUS_FAIL;              \
    }                                     \
  } while (0)

/// Move pointer to next expression macro function
#define __move_ptr_to_next_expr(__ptr, __buff_end, __expr) \
  do {                                                     \
    while ((__ptr) < (__buff_end) && (__expr)) {           \
      ++(__ptr);                                           \
    }                                                      \
  } while (0)

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

/***************************************************************************//**
 * @brief Requeset data channel operation
 * @details Helper function
 * @param[in,out] clnt FTP Client
 * @param[in] evt_flag_msk Event flag mask to request
 ******************************************************************************/
static void _request_data_ch_operation(sl_ftp_clnt_t * const clnt, uint32_t evt_flag_msk);

/***************************************************************************//**
 * @brief Waiting for data channel operation
 * @details Helper function
 * @param[in,out] clnt FTP Client
 * @param[in] evt_flag_msk Event flag mask to wait
 ******************************************************************************/
static void _wait_data_ch_operation(sl_ftp_clnt_t * const clnt, uint32_t evt_flag_msk);

/***************************************************************************//**
 * @brief Connect channel
 * @details Helper function
 * @param[in,out] clnt_ch Client channel (control or data)
 * @return sl_status_t SL_STATUS_OK on success, otherwise SL_STATUS_FAIL
 ******************************************************************************/
static sl_status_t _connect_channel(sl_ftp_clnt_ch_t * const clnt_ch);

/***************************************************************************//**
 * @brief Build command to buffer
 * @details Helper function
 * @param[in,out] clnt
 * @param[in] ctrl_cmd
 * @param[in] content
 * @return int32_t Built buffer size on success, otherwise -1
 ******************************************************************************/
static int32_t _build_cmd(sl_ftp_clnt_t *clnt,
                          const char *ctrl_cmd,
                          const char *content);

/***************************************************************************//**
 * @brief Send on channel
 * @details Helper function
 * @param[in,out] clnt_ch Client channel
 * @param[in] size
 * @return sl_status_t SL_STATUS_OK on success, otherwise SL_STATUS_FAIL
 ******************************************************************************/
static sl_status_t _send_on_ch(sl_ftp_clnt_ch_t * const clnt_ch,
                               size_t size);

/***************************************************************************//**
 * @brief Receive on channel
 * @details Helper function
 * @param[in,out] clnt_ch Client channel
 * @param[in] timeout Timeout in milisecs
 * @return int32_t Received buffer size on success, otherwise -1
 ******************************************************************************/
static int32_t _recv_on_ch(sl_ftp_clnt_ch_t * const clnt_ch,
                           const uint32_t timeout);

/***************************************************************************//**
 * @brief Print received control buffer
 * @details Helper function
 * @param[in,out] clnt_ch Client channel
 * @param[in] rcv_data_size Received data size
 ******************************************************************************/
static void _print_rcv_ctrl(sl_ftp_clnt_ch_t * const clnt_ch,
                            const size_t rcv_data_size);

/***************************************************************************//**
 * @brief Print received data buffer
 * @details Helper function
 * @param[in,out] clnt_ch Client channel
 * @param[in] rcv_data_size Received data size
 ******************************************************************************/
static void _print_rcv_data(sl_ftp_clnt_ch_t * const clnt_ch,
                            const size_t rcv_data_size);

/***************************************************************************//**
 * @brief Get server return code
 * @details Helper function
 * @param[in,out] clnt FTP Client
 ******************************************************************************/
static void _get_srv_ret_code(sl_ftp_clnt_t * const clnt);

/***************************************************************************//**
 * @brief Get data port for passive mode
 * @details Helper function
 * @param[in,out] clnt FTP client
 ******************************************************************************/
static void _get_data_port_passive_mode(sl_ftp_clnt_t * const clnt);

/***************************************************************************//**
 * @brief Get data port for extended passive mode
 * @details Helper function
 * @param[in,out] clnt FTP client
 ******************************************************************************/
static void _get_data_port_ext_passive_mode(sl_ftp_clnt_t * const clnt);

/***************************************************************************//**
 * @brief Parse Server return code
 * @details Helper function
 * @param[in,out] clnt FTP Client
 * @return sl_status_t SL_STATUS_OK on success, otherwise SL_STATUS_FAIL
 ******************************************************************************/
static sl_status_t _parse_ret_code(sl_ftp_clnt_t * const clnt);

/***************************************************************************//**
 * @brief Get mode command
 * @details Helper function
 * @param[in] clnt FTP Client
 * @return const char* Command string pointer or NULL
 ******************************************************************************/
static const char *_get_mode_cmd(const sl_ftp_clnt_t * const clnt);

/***************************************************************************//**
 * @brief FTP Client data channel thread function
 * @details Thread function
 * @param[in] args Arguments (not used)
 ******************************************************************************/
static void _clnt_thr_fnc(void * args);

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

#if SL_FTP_CLNT_DEFAULT_BUFF_ENABLE
/// Controll channel default buffer
static uint8_t _ctrl_buff[SL_FTP_CLNT_CTRL_BUFF_SIZE] = { 0U };

/// Data channel default buffer
static uint8_t _data_buff[SL_FTP_CLNT_DATA_BUFF_SIZE] = { 0U };
#endif

/// Thread ID
static osThreadId_t _ftp_clnt_thr = NULL;

/// FTP Client task attribute
static const osThreadAttr_t _ftp_clnt_thr_attr = {
  .name        = "FtpClntThread",
  .attr_bits   = osThreadDetached,
  .cb_mem      = NULL,
  .cb_size     = 0,
  .stack_mem   = NULL,
  .stack_size  = (SL_FTP_CLNT_STACK_SIZE_WORD * sizeof(void *)) & 0xFFFFFFF8U,
  .priority    = osPriorityNormal7,
  .tz_module   = 0
};

/// FTP Client message queue ID
static osMessageQueueId_t _ftp_clnt_msg_queue_in = NULL;

/// FTP Client message queue attributes
static const osMessageQueueAttr_t _ftp_clnt_msg_queue_in_attr = {
  .name = "FtpClntMsgQueueIn",
  .attr_bits = 0,
  .cb_mem = NULL,
  .cb_size = 0,
  .mq_mem = NULL,
  .mq_size = 0
};

/// FTP event flags attributes
static const osEventFlagsAttr_t _ftp_clnt_evt_attr = {
  .name      = "FtpClntEvt",
  .attr_bits = 0,
  .cb_mem    = NULL,
  .cb_size   = 0
};

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

void sl_ftp_clnt_service_init(void)
{
  _ftp_clnt_msg_queue_in = osMessageQueueNew(SL_FTP_MESSAGE_QUEUE_SIZE,
                                             sizeof(sl_ftp_clnt_t),
                                             &_ftp_clnt_msg_queue_in_attr);
  assert(_ftp_clnt_msg_queue_in != NULL);

  _ftp_clnt_thr = osThreadNew(_clnt_thr_fnc, NULL, &_ftp_clnt_thr_attr);
  assert(_ftp_clnt_thr != NULL);
}

sl_status_t sl_ftp_clnt_init(sl_ftp_clnt_t * const clnt,
                             const char *host)
{
  if (clnt == NULL) {
    return SL_STATUS_FAIL;
  }

  // Mode initialization
  clnt->mode = FTP_CLNT_MODE_EXT_PASSIVE;

  // Ctrl channel host init
  clnt->ctrl_ch.host = host == NULL ? SL_FTP_LOCAL_HOST_STR : host;
  clnt->ctrl_ch.port = SL_FTP_SRV_DEFAULT_CTRL_PORT;
  clnt->ctrl_ch.sock_id = SL_FTP_INVALID_SOCKID;

  // Data channel host init
  clnt->data_ch.host = host == NULL ? SL_FTP_LOCAL_HOST_STR : host;
  clnt->data_ch.port = SL_FTP_SRV_DEFAULT_DATA_PORT;
  clnt->data_ch.sock_id = SL_FTP_INVALID_SOCKID;

#if SL_FTP_CLNT_DEFAULT_BUFF_ENABLE
  clnt->ctrl_ch.buff_ptr = _ctrl_buff;
  clnt->ctrl_ch.buff_size = SL_FTP_CLNT_CTRL_BUFF_SIZE;
  clnt->data_ch.buff_size = SL_FTP_CLNT_DATA_BUFF_SIZE;
  clnt->data_ch.buff_ptr = _data_buff;
#else
  clnt->ctrl_ch.buff_ptr = NULL;
  clnt->ctrl_ch.buff_size = 0UL;
  clnt->data_ch.buff_ptr = NULL;
  clnt->data_ch.buff_size = 0UL;
#endif

  clnt->ctrl_ch.data_hnd = _print_rcv_ctrl;
  clnt->data_ch.data_hnd = _print_rcv_data;

  clnt->evt_flags = osEventFlagsNew(&_ftp_clnt_evt_attr);
  if (clnt->evt_flags == NULL) {
    return SL_STATUS_FAIL;
  }

  return SL_STATUS_OK;
}

static sl_status_t _connect_channel(sl_ftp_clnt_ch_t * const clnt_ch)
{
  int32_t res = SL_FTP_ERROR;

  if (clnt_ch == NULL) {
    return SL_STATUS_FAIL;
  }

  clnt_ch->sock_id = sl_ftp_tcp_socket_create();

  if (clnt_ch->sock_id == SL_FTP_INVALID_SOCKID) {
    sl_ftp_debug("Socket creation failed\n");
    return SL_STATUS_FAIL;
  }

  res = sl_ftp_tcp_socket_connect(clnt_ch->sock_id, clnt_ch->host, clnt_ch->port);

  if (res == SL_FTP_ERROR) {
    sl_ftp_debug("Connect failed\n");
    (void) sl_ftp_socket_close(clnt_ch->sock_id);
    return SL_STATUS_FAIL;
  }

  return SL_STATUS_OK;
}

sl_status_t sl_wiusn_ftp_clnt_connect(sl_ftp_clnt_t * const clnt)
{
  if (_connect_channel(&clnt->ctrl_ch) == SL_STATUS_FAIL) {
    return SL_STATUS_FAIL;
  }

  printf("[FTP Client connected to '%s']\n", clnt->ctrl_ch.host);
  return SL_STATUS_OK;
}

static sl_status_t _send_on_ch(sl_ftp_clnt_ch_t * const clnt_ch, size_t size)
{
  if (clnt_ch == NULL) {
    return SL_STATUS_FAIL;
  }

  if (sl_ftp_tcp_socket_send(clnt_ch->sock_id,
                             clnt_ch->buff_ptr,
                             size) == SL_FTP_ERROR) {
    return SL_STATUS_FAIL;
  }

  return SL_STATUS_OK;
}

static int32_t _recv_on_ch(sl_ftp_clnt_ch_t * const clnt_ch,
                           const uint32_t timeout)
{
  int32_t res = SL_FTP_ERROR;
  uint8_t *data_ptr = NULL;
  uint8_t *buff_end = NULL;
  size_t remained_size = 0UL;
  int32_t recv_bytes = 0L;

  if (clnt_ch == NULL) {
    return SL_FTP_ERROR;
  }

  buff_end = clnt_ch->buff_ptr + clnt_ch->buff_size;
  data_ptr = clnt_ch->buff_ptr;
  remained_size = clnt_ch->buff_size;

  for (uint8_t retry = 0U; retry < 2U; ++retry) {
    res = 0L;
    for (size_t i = 0U; i < (timeout / 100U) && data_ptr < buff_end; ++i) {
      sl_ftp_delay_ms(100U);
      res = sl_ftp_tcp_socket_recv(clnt_ch->sock_id, data_ptr, remained_size);
      if (res > 0L) {
        break;
      }
    }
    data_ptr += res;
    recv_bytes += res;
    remained_size -= res;
  }

  // Always terminate buffer
  clnt_ch->buff_ptr[clnt_ch->buff_size - 1] = 0U;

  return recv_bytes;
}

sl_status_t sl_ftp_clnt_send_cmd(sl_ftp_clnt_t * const clnt,
                                 const char *cmd,
                                 const char *content)
{
  int32_t res = SL_FTP_ERROR;

  res = _build_cmd(clnt, cmd, content);
  if (res < 0L) {
    return SL_STATUS_FAIL;
  }

  if (_send_on_ch(&clnt->ctrl_ch, res) != SL_STATUS_OK) {
    return SL_STATUS_FAIL;
  }

  printf("[%s] %s\n", clnt->ctrl_ch.host, (const char *)clnt->ctrl_ch.buff_ptr);

  return SL_STATUS_OK;
}

sl_status_t sl_ftp_clnt_recv_ctrl(sl_ftp_clnt_t * const clnt)
{
  int32_t recv_data = SL_FTP_ERROR;

  recv_data = _recv_on_ch(&clnt->ctrl_ch, SL_FTP_CLNT_RECV_TIMEOUT_MS);
  if (recv_data == SL_FTP_ERROR) {
    return SL_STATUS_FAIL;
  }

  _get_srv_ret_code(clnt);
  if (_parse_ret_code(clnt) == SL_STATUS_FAIL) {
    return SL_STATUS_FAIL;
  }

  if (clnt->ctrl_ch.data_hnd != NULL) {
    clnt->ctrl_ch.data_hnd(&clnt->ctrl_ch, recv_data);
  }

  return SL_STATUS_OK;
}

sl_status_t sl_ftp_clnt_recv_ctrl_until_ret_code(sl_ftp_clnt_t * const clnt,
                                                 sl_ftp_srv_ret_code_t ret_code)
{
  int32_t res = SL_FTP_ERROR;
  uint32_t time_cnt = 0;
  if (clnt == NULL) {
    return SL_STATUS_FAIL;
  }

  while (time_cnt < SL_FTP_CLNT_RECV_TIMEOUT_MS) {
    sl_ftp_delay_ms(100U);
    res = sl_ftp_tcp_socket_recv(clnt->ctrl_ch.sock_id,
                                 clnt->ctrl_ch.buff_ptr,
                                 clnt->ctrl_ch.buff_size);
    if (res > 0) {
      _get_srv_ret_code(clnt);
      _parse_ret_code(clnt);
      if (clnt->ctrl_ch.data_hnd != NULL) {
        clnt->ctrl_ch.data_hnd(&clnt->ctrl_ch, res);
      }
      if (clnt->srv_ret_code == ret_code) {
        return SL_STATUS_OK;
      }
      // reset time cnt if something received
      time_cnt = 0UL;
    }
    time_cnt += 100UL;
  }

  return SL_STATUS_FAIL;
}

static void _get_srv_ret_code(sl_ftp_clnt_t * const clnt)
{
  char ret_code[SL_FTP_SRV_RETURN_CODE_BUFF_SIZE] = { 0UL };

  clnt->srv_ret_code = SL_FTP_ERROR;

  if (clnt->ctrl_ch.buff_size < SL_FTP_SRV_RETURN_CODE_BUFF_SIZE) {
    return;
  }
  memcpy(ret_code, clnt->ctrl_ch.buff_ptr, SL_FTP_SRV_RETURN_CODE_LONG_STR_LEN);

  if ((ret_code[0U] - '0') > 6L) {
    return;
  } else if (ret_code[0U] == '1'
             && ret_code[1U] == '0'
             && ret_code[2U] == '0') {
    ret_code[SL_FTP_SRV_RETURN_CODE_LONG_STR_LEN] = 0U;
  } else {
    ret_code[SL_FTP_SRV_RETURN_CODE_STD_STR_LEN] = 0U;
  }

  clnt->srv_ret_code = atoi(ret_code);
}

sl_status_t sl_ftp_clnt_connect_auth(sl_ftp_clnt_t * const clnt,
                                     const char *user,
                                     const char *password)
{
  sl_status_t status = SL_STATUS_FAIL;
  const char *mode_cmd = NULL;

  status = sl_wiusn_ftp_clnt_connect(clnt);
  if (status != SL_STATUS_OK) {
    printf("[FTP client socket cannot be created]");
    return status;
  }

  sl_ftp_delay_ms(SL_FTP_CLNT_RECV_TIMEOUT_MS);

  __check_stat(sl_ftp_clnt_send_cmd(clnt, "", NULL));
  __check_stat(sl_ftp_clnt_recv_ctrl_until_ret_code(clnt, SL_FTP_SRV_RET_CODE_2XX_SREADY));

  __check_stat(sl_ftp_clnt_send_cmd(clnt, SL_FTP_CTRL_CMD_USER, user));
  __check_stat(sl_ftp_clnt_recv_ctrl_until_ret_code(clnt, SL_FTP_SRV_RET_CODE_3XX_USRNAMEOK));

  __check_stat(sl_ftp_clnt_send_cmd(clnt, SL_FTP_CTRL_CMD_PASS, password));
  __check_stat(sl_ftp_clnt_recv_ctrl_until_ret_code(clnt, SL_FTP_SRV_RET_CODE_2XX_USRLOGI));

  __check_stat(sl_ftp_clnt_send_cmd(clnt, SL_FTP_CTRL_CMD_SYST, NULL));
  __check_stat(sl_ftp_clnt_recv_ctrl_until_ret_code(clnt, SL_FTP_SRV_RET_CODE_2XX_NAMESYST));

  __check_stat(sl_ftp_clnt_send_cmd(clnt, SL_FTP_CTRL_CMD_FEAT, NULL));
  sl_ftp_delay_ms(SL_FTP_CLNT_RECV_TIMEOUT_MS);
  __check_stat(sl_ftp_clnt_recv_ctrl_until_ret_code(clnt, SL_FTP_SRV_RET_CODE_2XX_SYSSTAT));

  __check_stat(sl_ftp_clnt_send_cmd(clnt, SL_FTP_CTRL_CMD_HELP, "SITE"));
  sl_ftp_delay_ms(SL_FTP_CLNT_RECV_TIMEOUT_MS);
  __check_stat(sl_ftp_clnt_recv_ctrl_until_ret_code(clnt, SL_FTP_SRV_RET_CODE_2XX_HELPMSG));

  __check_stat(sl_ftp_clnt_send_cmd(clnt, SL_FTP_CTRL_CMD_OPTS, "UTF8 ON"));
  __check_stat(sl_ftp_clnt_recv_ctrl_until_ret_code(clnt, SL_FTP_SRV_RET_CODE_2XX_REQACTOK));

  __check_stat(sl_ftp_clnt_send_cmd(clnt, SL_FTP_CTRL_CMD_PWD, NULL));
  __check_stat(sl_ftp_clnt_recv_ctrl_until_ret_code(clnt, SL_FTP_SRV_RET_CODE_2XX_PNAMCREATE));

  __check_stat(sl_ftp_clnt_send_cmd(clnt, SL_FTP_CTRL_CMD_TYPE, "A"));
  __check_stat(sl_ftp_clnt_recv_ctrl_until_ret_code(clnt, SL_FTP_SRV_RET_CODE_2XX_REQACTOK));

  mode_cmd = _get_mode_cmd(clnt);
  if (mode_cmd == NULL) {
    return SL_STATUS_FAIL;
  }
  __check_stat(sl_ftp_clnt_send_cmd(clnt, mode_cmd, NULL));
  sl_ftp_delay_ms(SL_FTP_CLNT_RECV_TIMEOUT_MS);
  __check_stat(sl_ftp_clnt_recv_ctrl_until_ret_code(clnt, SL_FTP_SRV_RET_CODE_2XX_EPSVMODE));

  _request_data_ch_operation(clnt, SL_FTP_DATA_CH_REQUEST_CONNECT_MSK | SL_FTP_DATA_CH_REQUEST_RECV_MSK);
  _wait_data_ch_operation(clnt, SL_FTP_DATA_CH_RESPONSE_CONNECTED_MSK);

  __check_stat(sl_ftp_clnt_send_cmd(clnt, SL_FTP_CTRL_CMD_LIST, NULL));
  __check_stat(sl_ftp_clnt_recv_ctrl_until_ret_code(clnt, SL_FTP_SRV_RET_CODE_1XX_FILESTAT));

  __check_stat(sl_ftp_clnt_recv_ctrl_until_ret_code(clnt, SL_FTP_SRV_RET_CODE_2XX_CLOSEDATAC));

  _request_data_ch_operation(clnt, SL_FTP_DATA_CH_REQUEST_CLOSE_MSK);
  _wait_data_ch_operation(clnt, SL_FTP_DATA_CH_RESPONSE_CLOSED_MSK);
  (void) osEventFlagsClear(clnt->evt_flags, SL_FTP_DATA_CH_ALL_FLAG_MSK);
  clnt->data_ch.buff_ptr[clnt->data_ch.buff_size - 1U] = 0;
  printf("%s\n", clnt->data_ch.buff_ptr);

  return status;
}

sl_status_t sl_ftp_clnt_get(sl_ftp_clnt_t * const clnt, const char *file)
{
  const char *mode_cmd = NULL;

  mode_cmd = _get_mode_cmd(clnt);
  if (mode_cmd == NULL) {
    return SL_STATUS_FAIL;
  }

  __check_stat(sl_ftp_clnt_send_cmd(clnt, SL_FTP_CTRL_CMD_TYPE, "I"));
  __check_stat(sl_ftp_clnt_recv_ctrl_until_ret_code(clnt, SL_FTP_SRV_RET_CODE_2XX_REQACTOK));

  __check_stat(sl_ftp_clnt_send_cmd(clnt, mode_cmd, NULL));
  __check_stat(sl_ftp_clnt_recv_ctrl_until_ret_code(clnt, SL_FTP_SRV_RET_CODE_2XX_EPSVMODE));

  _request_data_ch_operation(clnt, SL_FTP_DATA_CH_REQUEST_CONNECT_MSK | SL_FTP_DATA_CH_REQUEST_RECV_MSK);
  _wait_data_ch_operation(clnt, SL_FTP_DATA_CH_RESPONSE_CONNECTED_MSK);

  __check_stat(sl_ftp_clnt_send_cmd(clnt, SL_FTP_CTRL_CMD_RETR, file));
  __check_stat(sl_ftp_clnt_recv_ctrl_until_ret_code(clnt, SL_FTP_SRV_RET_CODE_1XX_FILESTAT));

  __check_stat(sl_ftp_clnt_recv_ctrl_until_ret_code(clnt, SL_FTP_SRV_RET_CODE_2XX_CLOSEDATAC));

  // _request_data_ch_operation(clnt, SL_FTP_DATA_CH_REQUEST_CLOSE_MSK);
  _wait_data_ch_operation(clnt, SL_FTP_DATA_CH_RESPONSE_CLOSED_MSK);
  (void) osEventFlagsClear(clnt->evt_flags, SL_FTP_DATA_CH_ALL_FLAG_MSK);

  return SL_STATUS_OK;
}

sl_status_t sl_ftp_clnt_put(sl_ftp_clnt_t * const clnt,
                            const char *file)
{
  const char *mode_cmd = NULL;

  mode_cmd = _get_mode_cmd(clnt);
  if (mode_cmd == NULL) {
    return SL_STATUS_FAIL;
  }

  __check_stat(sl_ftp_clnt_send_cmd(clnt, SL_FTP_CTRL_CMD_TYPE, "I"));
  __check_stat(sl_ftp_clnt_recv_ctrl_until_ret_code(clnt, SL_FTP_SRV_RET_CODE_2XX_REQACTOK));

  __check_stat(sl_ftp_clnt_send_cmd(clnt, mode_cmd, NULL));
  __check_stat(sl_ftp_clnt_recv_ctrl_until_ret_code(clnt, SL_FTP_SRV_RET_CODE_2XX_EPSVMODE));

  _request_data_ch_operation(clnt, SL_FTP_DATA_CH_REQUEST_CONNECT_MSK | SL_FTP_DATA_CH_REQUEST_SEND_MSK);
  _wait_data_ch_operation(clnt, SL_FTP_DATA_CH_RESPONSE_CONNECTED_MSK);

  __check_stat(sl_ftp_clnt_send_cmd(clnt, SL_FTP_CTRL_CMD_STOR, file));
  __check_stat(sl_ftp_clnt_recv_ctrl_until_ret_code(clnt, SL_FTP_SRV_RET_CODE_1XX_FILESTAT));

  __check_stat(sl_ftp_clnt_recv_ctrl_until_ret_code(clnt, SL_FTP_SRV_RET_CODE_2XX_CLOSEDATAC));

  // _request_data_ch_operation(clnt, SL_FTP_DATA_CH_REQUEST_CLOSE_MSK);
  _wait_data_ch_operation(clnt, SL_FTP_DATA_CH_RESPONSE_CLOSED_MSK);
  (void) osEventFlagsClear(clnt->evt_flags, SL_FTP_DATA_CH_ALL_FLAG_MSK);
  return SL_STATUS_OK;
}

sl_status_t sl_ftp_clnt_delete_file(sl_ftp_clnt_t * const clnt,
                                    const char *file)
{
  __check_stat(sl_ftp_clnt_send_cmd(clnt, SL_FTP_CTRL_CMD_DELE, file));
  __check_stat(sl_ftp_clnt_recv_ctrl_until_ret_code(clnt, SL_FTP_SRV_RET_CODE_2XX_FILEACTOK));
  return SL_STATUS_OK;
}

sl_status_t sl_ftp_clnt_close(sl_ftp_clnt_t * const clnt)
{
  __check_stat(sl_ftp_clnt_send_cmd(clnt, SL_FTP_CTRL_CMD_QUIT, NULL));
  if (clnt == NULL || clnt->ctrl_ch.sock_id == SL_FTP_INVALID_SOCKID
      || sl_ftp_socket_close(clnt->ctrl_ch.sock_id) == SL_FTP_ERROR) {
    return SL_STATUS_FAIL;
  }

  if (clnt->data_ch.sock_id != SL_FTP_INVALID_SOCKID) {
    (void)sl_ftp_socket_close(clnt->ctrl_ch.sock_id);
  }

  return SL_STATUS_OK;
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------

static void _request_data_ch_operation(sl_ftp_clnt_t * const clnt, uint32_t evt_flag_msk)
{
  (void) osEventFlagsSet(clnt->evt_flags, evt_flag_msk);
  if (evt_flag_msk & SL_FTP_DATA_CH_REQUEST_CONNECT_MSK) {
    (void) osMessageQueuePut(_ftp_clnt_msg_queue_in, clnt, 0U, osWaitForever);
  }
}

static void _wait_data_ch_operation(sl_ftp_clnt_t * const clnt, uint32_t evt_flag_msk)
{
  (void) osEventFlagsWait(clnt->evt_flags, evt_flag_msk, osFlagsWaitAny, SL_FTP_CLNT_RECV_TIMEOUT_MS);
}

static int32_t _build_cmd(sl_ftp_clnt_t *clnt,
                          const char *ctrl_cmd,
                          const char *content)
{
  int32_t res = 0;

  if (content != NULL) {
    // CMD with content
    res = snprintf((char * const)clnt->ctrl_ch.buff_ptr,
                   clnt->ctrl_ch.buff_size,
                   "%s %s\n", ctrl_cmd, content);
  } else {
    // CMD without content
    res = snprintf((char * const)clnt->ctrl_ch.buff_ptr,
                   clnt->ctrl_ch.buff_size,
                   "%s\n", ctrl_cmd);
  }

  return res;
}

static void _get_data_port_passive_mode(sl_ftp_clnt_t * const clnt)
{
  // 227 Entering Passive Mode (0,0,0,0,182,79).

  uint8_t *ptru = NULL;
  uint8_t *ptrl = NULL;
  uint8_t *buff_end = NULL;
  char vals[SL_FTP_UINT8_STR_BUFF_SIZE] = { 0U };
  uint8_t valu = 0U;
  uint8_t vall = 0U;
  uint8_t cpy_size = 0U;

  ptru = clnt->ctrl_ch.buff_ptr;
  buff_end = clnt->ctrl_ch.buff_ptr + clnt->ctrl_ch.buff_size;
  clnt->data_ch.port = SL_FTP_SRV_DEFAULT_DATA_PORT;

  for (uint8_t i = 0; i < 4UL; ++i, ++ptru) {
    __move_ptr_to_next_expr(ptru, buff_end, *ptru != ',');
  }

  __move_ptr_to_next_expr(ptru, buff_end, !(*ptru >= '0' && *ptru <= '9'));

  ptrl = ptru;
  __move_ptr_to_next_expr(ptrl, buff_end, *ptrl != ',');

  cpy_size = (uint8_t) (ptrl - ptru);
  memcpy(vals, ptru, cpy_size < sizeof(vals) ? cpy_size : sizeof(vals) - 1);
  vals[sizeof(vals) - 1] = 0U;
  valu = (uint8_t) atoi(vals);

  if (++ptrl >= (buff_end - 1U)) {
    return;
  }
  __move_ptr_to_next_expr(ptrl, buff_end, !(*ptrl >= '0' && *ptrl <= '9'));
  ptru = ptrl;
  __move_ptr_to_next_expr(ptru, buff_end, *ptru != ')');
  memset(vals, 0, sizeof(vals));

  cpy_size = (uint8_t)(ptru - ptrl);
  memcpy(vals, ptrl, cpy_size < sizeof(vals) ? cpy_size : sizeof(vals) - 1);
  vals[sizeof(vals) - 1] = 0U;
  vall = (uint8_t) atoi(vals);

  clnt->data_ch.port = (uint16_t)((uint32_t)valu * 256U + vall);
}

static void _get_data_port_ext_passive_mode(sl_ftp_clnt_t * const clnt)
{
  // 229 Entering Extended Passive Mode (|||56977|)

  uint8_t *ptrs = NULL;
  uint8_t *ptre = NULL;
  uint8_t *buff_end = NULL;
  uint8_t cpy_size = 0U;
  char vals[SL_FTP_UINT16_STR_BUFF_SIZE] = { 0U };

  ptrs = clnt->ctrl_ch.buff_ptr;
  buff_end = clnt->ctrl_ch.buff_ptr + clnt->ctrl_ch.buff_size;
  __move_ptr_to_next_expr(ptrs, buff_end, *ptrs != '|');

  if (ptrs >= (buff_end - 3U)
      || (char) ptrs[0U] != '|'
      || (char) ptrs[1U] != '|'
      || (char) ptrs[2U] != '|') {
    return;
  }
  ptrs += 3U;

  ptre = ptrs;

  __move_ptr_to_next_expr(ptre, buff_end, *ptre != '|');
  cpy_size = ptre - ptrs;
  memcpy(vals, ptrs, cpy_size < sizeof(vals) ? cpy_size : sizeof(vals) - 1U);
  vals[sizeof(vals) - 1U] = 0U;

  clnt->data_ch.port = (uint16_t) atoi(vals);
}

static sl_status_t _parse_ret_code(sl_ftp_clnt_t * const clnt)
{
  switch (clnt->srv_ret_code) {
    case SL_FTP_ERROR:
      break;

    case SL_FTP_SRV_RET_CODE_2XX_PSVMODE:
      _get_data_port_passive_mode(clnt);
      clnt->mode = FTP_CLNT_MODE_PASSIVE;
      break;

    case SL_FTP_SRV_RET_CODE_2XX_EPSVMODE:
      _get_data_port_ext_passive_mode(clnt);
      clnt->mode = FTP_CLNT_MODE_EXT_PASSIVE;
      break;

    default: break;
  }
  return SL_STATUS_OK;
}

static const char *_get_mode_cmd(const sl_ftp_clnt_t * const clnt)
{
  switch (clnt->mode) {
    case FTP_CLNT_MODE_PASSIVE:
      return SL_FTP_CTRL_CMD_PASV;
    case FTP_CLNT_MODE_EXT_PASSIVE:
      return SL_FTP_CTRL_CMD_EPSV;
    default:
      return NULL;
  }
}

static void _print_rcv_ctrl(sl_ftp_clnt_ch_t * const clnt_ch,
                            const size_t rcv_data_size)
{
  if (clnt_ch->buff_size <= rcv_data_size) {
    clnt_ch->buff_ptr[clnt_ch->buff_size - 1] = 0U;
  } else {
    clnt_ch->buff_ptr[rcv_data_size] = 0U;
  }

  printf("[%s] >> %s\n", clnt_ch->host, clnt_ch->buff_ptr);
}

static void _print_rcv_data(sl_ftp_clnt_ch_t * const clnt_ch,
                            const size_t rcv_data_size)
{
  printf("[%s]\n", clnt_ch->host);
  sl_ftp_dump_buff(clnt_ch->buff_ptr, rcv_data_size);
}

static void _clnt_thr_fnc(void * args)
{
  osStatus_t status = osError;
  uint8_t msg_prio = 0U;
  static sl_ftp_clnt_t clnt = { 0U };
  int32_t res = SL_FTP_ERROR;
  uint32_t timeout = 0UL;
  uint32_t flags = 0UL;
  (void) args;

  // wait for network connected state
  while (!sl_ftp_is_network_connected()) {
    sl_ftp_delay_ms(1000UL);
  }
  sl_ftp_debug("FTP Data Service started\n");
  SL_FTP_SERVICE_LOOP() {
    // Pop Test from the queue
    status = osMessageQueueGet(_ftp_clnt_msg_queue_in, &clnt, &msg_prio, osWaitForever);
    if (status != osOK) {
      sl_ftp_delay_ms(1UL);
      continue;
    }

    flags = osEventFlagsGet(clnt.evt_flags);

    // flag error
    if (flags & SL_FTP_DATA_CH_ERROR_MSK) {
      sl_ftp_debug("Error flags: %lu\n", flags);
      sl_ftp_delay_ms(1UL);
      continue;
    }

    if (flags & SL_FTP_DATA_CH_REQUEST_CONNECT_MSK) {
      sl_ftp_debug("Connect request flags: %lu\n", flags);
      _connect_channel(&clnt.data_ch);
      sl_ftp_delay_ms(1000UL);
      (void) osEventFlagsSet(clnt.evt_flags, SL_FTP_DATA_CH_RESPONSE_CONNECTED_MSK);
    }

    // Receive request
    if (flags & SL_FTP_DATA_CH_REQUEST_SEND_MSK) {
      sl_ftp_debug("Receiving on data channel started: %ld, %s, %u\n",
                   clnt.data_ch.sock_id, clnt.data_ch.host, clnt.data_ch.port);

      SL_FTP_SERVICE_LOOP(){
        flags = osEventFlagsGet(clnt.evt_flags);
        if ((flags & SL_FTP_DATA_CH_ERROR_MSK)
            || (flags & SL_FTP_DATA_CH_REQUEST_CLOSE_MSK)) {
          sl_ftp_debug("Close request flags: %lu\n", flags);
          sl_ftp_delay_ms(1UL);
          break;
        }

        sl_ftp_delay_ms(100UL);
        res = sl_ftp_tcp_socket_recv(clnt.data_ch.sock_id, clnt.data_ch.buff_ptr, clnt.data_ch.buff_size);
        if (res > 0) {
          if (clnt.data_ch.data_hnd) {
            clnt.data_ch.data_hnd(&clnt.data_ch, res);
          }
          timeout = 0UL;
        } else if (timeout > SL_FTP_CLNT_RECV_TIMEOUT_MS) {
          break;
        }
        timeout += 100UL;
      }

      // Send request
    } else if (flags & SL_FTP_DATA_CH_REQUEST_SEND_MSK) {
      sl_ftp_debug("Sending on data channel started: %ld, %s, %u\n",
                   clnt.data_ch.sock_id, clnt.data_ch.host, clnt.data_ch.port);
      while (1) {
        sl_ftp_delay_ms(100UL);
        res = sl_ftp_tcp_socket_send(clnt.data_ch.sock_id, clnt.data_ch.buff_ptr, clnt.data_ch.buff_size);
        if (res > 0L || timeout > SL_FTP_CLNT_RECV_TIMEOUT_MS) {
          break;
        }
        timeout += 100UL;
      }
    }

    sl_ftp_debug("Closing data channel\n");
    sl_ftp_socket_close(clnt.data_ch.sock_id);
    // clear all flags
    (void) osEventFlagsClear(clnt.evt_flags, SL_FTP_DATA_CH_ALL_FLAG_MSK);
    (void) osEventFlagsSet(clnt.evt_flags, SL_FTP_DATA_CH_RESPONSE_CLOSED_MSK);
    sl_ftp_delay_ms(1UL);
  }
}
#endif
