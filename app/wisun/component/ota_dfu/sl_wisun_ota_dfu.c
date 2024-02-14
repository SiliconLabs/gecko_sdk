/***************************************************************************//**
 * @file
 * @brief Wi-SUN OTA DFU Service
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

#include <assert.h>
#include <string.h>
#include "cmsis_os2.h"
#include "sl_cmsis_os2_common.h"
#include "sl_status.h"
#include "btl_interface.h"
#include "sl_tftp_clnt.h"
#include "sl_wisun_app_core_util.h"
#include "sl_wisun_coap_rhnd.h"
#include "sl_wisun_ota_dfu.h"
#include "sl_wisun_ota_dfu_config.h"
#include "sl_wisun_coap.h"
#include "sl_string.h"
#include "sl_sleeptimer.h"
#include "socket/socket.h"

#if SL_WISUN_OTA_DFU_HOST_NOTIFY_ENABLED
#include "socket/socket.h"
#endif
// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

/// Error mask
#define SL_WISUN_OTA_DFU_EVT_FLAG_ALL_MSK                    0x00FFFFFFUL

/// OTA DFU Event all mask
#define SL_WISUN_OTA_DFU_EVT_FLAG_ERROR_MSK                  (1UL << 31UL)

/// OTA DFU start firmware update mask
#define SL_WISUN_OTA_DFU_EVT_FLAG_START_FW_UPDATE_MSK        (1UL << SL_WISUN_OTA_DFU_STATUS_FW_UPDATE_STARTED)

/// OTA DFU firmware downloaded mask
#define SL_WISUN_OTA_DFU_EVT_FLAG_FW_DOWNLOADED_MSK          (1UL << SL_WISUN_OTA_DFU_STATUS_FW_DOWNLOADED)

/// OTA DFU firmware verified mask
#define SL_WISUN_OTA_DFU_EVT_FLAG_FW_VERIFIED_MSK            (1UL << SL_WISUN_OTA_DFU_STATUS_FW_VERIFIED)

/// OTA DFU firmware set mask
#define SL_WISUN_OTA_DFU_EVT_FLAG_FW_SET_MSK                 (1UL << SL_WISUN_OTA_DFU_STATUS_FW_SET)

/// OTA DFU firmware update stopped/finished mask
#define SL_WISUN_OTA_DFU_EVT_FLAG_STOP_FW_UPDATE_MSK         (1UL << SL_WISUN_OTA_DFU_STATUS_FW_UPDATE_STOPPED)

/// OTA DFU firmware download error mask
#define SL_WISUN_OTA_DFU_EVT_FLAG_FW_DOWNLOAD_ERROR_MSK      (1UL << SL_WISUN_OTA_DFU_STATUS_FW_DOWNLOAD_ERROR)

/// OTA DFU firmware verification error mask
#define SL_WISUN_OTA_DFU_EVT_FLAG_FW_VERIFY_ERROR_MSK        (1UL << SL_WISUN_OTA_DFU_STATUS_FW_VERIFY_ERROR)

/// OTA DFU firmware set error mask
#define SL_WISUN_OTA_DFU_EVT_FLAG_FW_SET_ERROR_MSK           (1UL << SL_WISUN_OTA_DFU_STATUS_FW_SET_ERROR)

/// OTA DFU status json format string
#define SL_WISUN_OTA_DFU_STATUS_JSON_FORMAT_STR \
  "{\n"                                         \
  "\"ip\":\"%s\",\n"                            \
  "\"elapsed_t\":\"%.2lu:%.2lu:%.2lu\",\n"      \
  "\"downl_bytes\":%lu,\n"                      \
  "\"flags\": \"0x%.8lx\",\n"                   \
  "\"fw_update_started\": %u,\n"                \
  "\"fw_downloaded\": %u,\n"                    \
  "\"fw_verified\": %u,\n"                      \
  "\"fw_set\": %u,\n"                           \
  "\"fw_stopped\": %u,\n"                       \
  "\"fw_download_error\": %u,\n"                \
  "\"fw_verify_error\": %u,\n"                  \
  "\"fw_set_error\": %u\n"                      \
  "}\n"

/// OTA DFU status json string max length
#define SL_WISUN_OTA_DFU_STATUS_JSON_STR_MAX_LEN            320UL

/// OTA DFU delay in ms
#define SL_WISUN_OTA_DFU_DELAY_MS                           1000UL

/// OTA DFU shutdown delay in ms
#define SL_WISUN_OTA_DFU_SHUTDOWN_DELAY_MS                  5000UL

/// OTA DFU resource type
#define SL_WISUN_OTA_DFU_RT                                 "dfu"

/// OTA DFU resource interface
#define SL_WISUN_OTA_DFU_RESOURCE_IF_OTA                    "ota"

/// OTA DFU firmware update start payload string
#define SL_WISUN_OTA_DFU_START_PAYLOAD_STR                  "start"

/// OTA DFU firmware update stop payload string
#define SL_WISUN_OTA_DFU_STOP_PAYLOAD_STR                   "stop"

/// OTA DFU firmware reboot and install
#define SL_WISUN_OTA_DFU_REBOOT_AND_INSTALL_PAYLOAD_STR     "install"

/// Error firmware download format string
#define SL_WISUN_OTA_DFU_ERROR_FW_DOWNLOAD_FORMAT_STR \
  "error (%u): write flash (ret_val: %ld, offset: %lu, data_size: %u)\n"

/// Error firmware verify format string
#define SL_WISUN_OTA_DFU_ERROR_FW_VERIFY_FORMAT_STR \
  "error (%u): verify fw (ret_val: %ld)\n"

/// Error firmware set format string
#define SL_WISUN_OTA_DFU_ERROR_FW_SET_FORMAT_STR \
  "error (%u): set fw (ret_val: %ld)\n"

/// Notification CoAP message ID
#define SL_WISUN_OTA_DFU_HOST_NOTIFY_COAP_MSG_ID            9001U

/// Time sec to milisec
#define SL_WISUN_OTA_DFU_TIME_S_TO_MS   (1000UL)

/// Time minute to milisec
#define SL_WISUN_OTA_DFU_TIME_M_TO_MS   (60UL * SL_WISUN_OTA_DFU_TIME_S_TO_MS)

/// Time hour to milisec
#define SL_WISUN_OTA_DFU_TIME_H_TO_MS   (60UL * SL_WISUN_OTA_DFU_TIME_M_TO_MS)

#if SL_WISUN_OTA_DFU_HOST_NOTIFY_ENABLED
/// Notification channel typedef
typedef struct sl_wisun_ota_dfu_notify_ch {
  /// Notification socket
  int32_t sockid;
  /// Notification address
  sockaddr_in6_t addr;
  /// Notification packet
  sl_wisun_coap_packet_t pkt;
} sl_wisun_ota_dfu_notify_ch_t;
#endif

/// OTA DFU log macro function
#if SL_WISUN_OTA_DFU_VERBOSE_MODE_ENABLED
# define sl_wisun_ota_dfu_log(format, ...)                \
  do {                                                    \
    printf("[wisun-btl] (%lu) ", _get_elapsed_time_ms()); \
    printf(format, ##__VA_ARGS__);                        \
  } while (0)
#else
# define sl_wisun_ota_dfu_log(format, ...) \
  do {                                     \
    (void) format;                         \
  } while (0)
#endif

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

/***************************************************************************//**
 * @brief OTA DFU TFTP Data handler
 * @details Callback to store received data in SPI flash
 * @param[in,out] clnt Client
 * @param[in] data_ptr Data ptr
 * @param[in] data_size Data size
 ******************************************************************************/
static void _tftp_data_hnd(sl_tftp_clnt_t * const clnt,
                           const uint8_t * const data_ptr,
                           const uint16_t data_size);

/**************************************************************************//**
 * @brief OTA DFU CoAP callback.
 * @details Handle incoming firmware update request from CoAP message.
 * @param[in] req_packet Request packet.
 * * @return sl_wisun_coap_packet_t * Response packet ptr
 *****************************************************************************/
static sl_wisun_coap_packet_t * _ota_dfu_coap_response_cb(const sl_wisun_coap_packet_t * const req_packet);

/**************************************************************************//**
 * @brief Thread function of OTA DFU Service
 * @details Thread function
 * @param[in] args Arguments (not used)
 *****************************************************************************/
static void _ota_dfu_thr_fnc(void * args);

/**************************************************************************//**
 * @brief Get formatted time in hours, minutes and seconds
 * @details Helper function
 * @param[in] h hours
 * @param[in] m minutes
 * @param[in] s seconds
 *****************************************************************************/
static void _get_time_hms(uint32_t * const h, uint32_t * const m, uint32_t * const s);

/**************************************************************************//**
 * @brief Get status string in json format
 * @details Helper function
 * @return const char * Allocated string pointer on success, otherwise NULL
 *****************************************************************************/
static const char *_get_status_json_string(void);

/**************************************************************************//**
 * @brief Notify host
 * @details Send CoAP notification packet to set CoAP Server
 *****************************************************************************/
static void _notify_host(void);

/**************************************************************************//**
* @brief Change Status
* @details Change status flags and notify host
* @param[in] statu_mask Status flags to update
******************************************************************************/
static void _change_status(const uint32_t statu_mask);

/**************************************************************************//**
 * @brief Get elapsed time in ms
 * @details Get difference between now and stored reference
 *****************************************************************************/
__STATIC_INLINE uint32_t _get_elapsed_time_ms(void);

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

/// Thread ID
static osThreadId_t _ota_dfu_thr = NULL;

/// Downloaded bytes
static uint32_t _downl_bytes = 0UL;

/// Start tick count reference
static uint32_t _start_tick_cnt = 0UL;

/// Global IP String
static const char * _global_ip_str = NULL;

/// OTA DFU task attribute
static const osThreadAttr_t _ota_dfu_thr_attr = {
  .name        = "DfuThread",
  .attr_bits   = osThreadDetached,
  .cb_mem      = NULL,
  .cb_size     = 0,
  .stack_mem   = NULL,
  .stack_size  = app_stack_size_word_to_byte(SL_WISUN_OTA_DFU_STACK_SIZE_WORD),
  .priority    = osPriorityNormal7,
  .tz_module   = 0
};

/// OTA DFU event flag
static osEventFlagsId_t _ota_dfu_evt = NULL;

/// OTA DFU event flag attributes
static const osEventFlagsAttr_t _evt_attr = {
  .name      = "DfuEvt",
  .attr_bits = 0,
  .cb_mem    = NULL,
  .cb_size   = 0
};

/// OTA DFU CoAP resource
static const sl_wisun_coap_rhnd_resource_t _ota_dfu_resource = {
  .data.uri_path      = SL_WISUN_OTA_DFU_URI_PATH,
  .data.resource_type = SL_WISUN_OTA_DFU_RT,
  .data.interface     = SL_WISUN_OTA_DFU_RESOURCE_IF_OTA,
  .auto_response      = _ota_dfu_coap_response_cb,
  .discoverable       = true
};

#if SL_WISUN_OTA_DFU_HOST_NOTIFY_ENABLED
/// Notification channel
static sl_wisun_ota_dfu_notify_ch_t _notify_ch = {
  .sockid = -1L,
  .addr = { 0U },
  .pkt = { 0U },
};
#endif
// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

void sl_wisun_ota_dfu_init(void)
{
  _ota_dfu_evt = osEventFlagsNew(&_evt_attr);
  assert(_ota_dfu_evt != NULL);

  _ota_dfu_thr = osThreadNew(_ota_dfu_thr_fnc, NULL, &_ota_dfu_thr_attr);
  assert(_ota_dfu_thr != NULL);
  assert(sl_wisun_coap_rhnd_resource_add(&_ota_dfu_resource) == SL_STATUS_OK);
}

sl_status_t sl_wisun_ota_dfu_start_fw_update(void)
{
  uint32_t flags = 0UL;

  flags = osEventFlagsGet(_ota_dfu_evt);

  // error or already started
  if (flags & SL_WISUN_OTA_DFU_EVT_FLAG_ERROR_MSK
      || flags & SL_WISUN_OTA_DFU_EVT_FLAG_START_FW_UPDATE_MSK) {
    return SL_STATUS_FAIL;
  }

  flags = osEventFlagsSet(_ota_dfu_evt, SL_WISUN_OTA_DFU_EVT_FLAG_START_FW_UPDATE_MSK);

  // reset timer
  _start_tick_cnt = sl_sleeptimer_get_tick_count();
  return SL_STATUS_OK;
}

sl_status_t sl_wisun_ota_dfu_stop_fw_update(void)
{
  uint32_t flags = 0UL;

  flags = osEventFlagsGet(_ota_dfu_evt);

  // error or already started
  if (flags & SL_WISUN_OTA_DFU_EVT_FLAG_ERROR_MSK
      || flags & SL_WISUN_OTA_DFU_EVT_FLAG_STOP_FW_UPDATE_MSK) {
    return SL_STATUS_FAIL;
  }

  flags = osEventFlagsSet(_ota_dfu_evt, SL_WISUN_OTA_DFU_EVT_FLAG_STOP_FW_UPDATE_MSK);

  return SL_STATUS_OK;
}

#if !SL_WISUN_OTA_DFU_AUTO_INSTALL_ENABLED
sl_status_t sl_wisun_ota_dfu_reboot_and_install(void)
{
  bootloader_rebootAndInstall();

  // If the function returns, error occured.
  return SL_STATUS_FAIL;
}
#endif

uint32_t sl_wisun_ota_dfu_get_fw_update_status(void)
{
  return osEventFlagsGet(_ota_dfu_evt);
}

const char* sl_wisun_ota_dfu_get_fw_update_status_json_str(void)
{
  return _get_status_json_string();
}

void sl_wisun_ota_dfu_free_fw_update_status_json_str(const char * str)
{
  sl_wisun_coap_free((void *)str);
}

bool sl_wisun_ota_dfu_get_fw_update_status_flag(const sl_wisun_ota_dfu_status_t status_flag)
{
  uint32_t flags = 0UL;

  flags = osEventFlagsGet(_ota_dfu_evt);
  return (flags & SL_WISUN_OTA_DFU_EVT_FLAG_ERROR_MSK) || !(flags & 1UL << status_flag) ? false : true;
}

SL_WEAK void sl_wisun_ota_dfu_error_hnd(const sl_wisun_ota_dfu_error_code_t error_code,
                                        sl_wisun_ota_dfu_error_ctx_t * const error_ctx)
{
  switch (error_code) {
    case SL_WISUN_OTA_DFU_ERROR_FW_DOWNLOAD:
      sl_wisun_ota_dfu_log(SL_WISUN_OTA_DFU_ERROR_FW_DOWNLOAD_FORMAT_STR,
                           error_code,
                           error_ctx->download.ret_val,
                           error_ctx->download.offset,
                           error_ctx->download.data_size);
      break;

    case SL_WISUN_OTA_DFU_ERROR_FW_VERIFY:
      sl_wisun_ota_dfu_log(SL_WISUN_OTA_DFU_ERROR_FW_VERIFY_FORMAT_STR,
                           error_code, error_ctx->verify.ret_val);
      break;

    case SL_WISUN_OTA_DFU_ERROR_FW_SET:
      sl_wisun_ota_dfu_log(SL_WISUN_OTA_DFU_ERROR_FW_SET_FORMAT_STR,
                           error_code, error_ctx->set.ret_val);
      break;

    default:
      (void) error_ctx;
      break;
  }
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------

static void _get_time_hms(uint32_t * const h,
                          uint32_t * const m,
                          uint32_t * const s)
{
  uint32_t ms_val = 0UL;

  ms_val = _get_elapsed_time_ms();

  *h = ms_val / SL_WISUN_OTA_DFU_TIME_H_TO_MS;
  ms_val -= *h * SL_WISUN_OTA_DFU_TIME_H_TO_MS;

  *m = ms_val / SL_WISUN_OTA_DFU_TIME_M_TO_MS;
  ms_val -= *m * SL_WISUN_OTA_DFU_TIME_M_TO_MS;

  *s = ms_val / SL_WISUN_OTA_DFU_TIME_S_TO_MS;
}

static const char *_get_status_json_string(void)
{
  char * str = NULL;
  uint32_t flags = 0UL;
  uint32_t th = 0UL;
  uint32_t tm = 0UL;
  uint32_t ts = 0UL;

  str = (char *)sl_wisun_coap_malloc(SL_WISUN_OTA_DFU_STATUS_JSON_STR_MAX_LEN);

  if (str == NULL) {
    return NULL;
  }

  flags = osEventFlagsGet(_ota_dfu_evt);

  // Evt flag error
  if (flags & SL_WISUN_OTA_DFU_EVT_FLAG_ERROR_MSK) {
    return NULL;
  }
  _get_time_hms(&th, &tm, &ts);

  (void) snprintf(str, SL_WISUN_OTA_DFU_STATUS_JSON_STR_MAX_LEN,
                  SL_WISUN_OTA_DFU_STATUS_JSON_FORMAT_STR,
                  _global_ip_str,
                  th, tm, ts,
                  _downl_bytes,
                  flags,
                  (bool)(flags & SL_WISUN_OTA_DFU_EVT_FLAG_START_FW_UPDATE_MSK),
                  (bool)(flags & SL_WISUN_OTA_DFU_EVT_FLAG_FW_DOWNLOADED_MSK),
                  (bool)(flags & SL_WISUN_OTA_DFU_EVT_FLAG_FW_VERIFIED_MSK),
                  (bool)(flags & SL_WISUN_OTA_DFU_EVT_FLAG_FW_SET_MSK),
                  (bool)(flags & SL_WISUN_OTA_DFU_EVT_FLAG_STOP_FW_UPDATE_MSK),
                  (bool)(flags & SL_WISUN_OTA_DFU_EVT_FLAG_FW_DOWNLOAD_ERROR_MSK),
                  (bool)(flags & SL_WISUN_OTA_DFU_EVT_FLAG_FW_VERIFY_ERROR_MSK),
                  (bool)(flags & SL_WISUN_OTA_DFU_EVT_FLAG_FW_SET_ERROR_MSK));
  return (const char *)str;
}

static sl_wisun_coap_packet_t * _ota_dfu_coap_response_cb(const sl_wisun_coap_packet_t * const req_packet)
{
  sl_wisun_coap_packet_t *resp_packet = NULL;

  resp_packet = sl_wisun_coap_build_response(req_packet, COAP_MSG_CODE_RESPONSE_NOT_ACCEPTABLE);

  // packet cannot be allocated
  if (resp_packet == NULL) {
    return NULL;
  }

  // Check request type, only post or get allowed
  if (!(req_packet->msg_code == COAP_MSG_CODE_REQUEST_POST
        || req_packet->msg_code == COAP_MSG_CODE_REQUEST_GET)) {
    return NULL;
  }

  // Handle incoming empty payload
  if (req_packet->payload_ptr == NULL && req_packet->msg_code == COAP_MSG_CODE_REQUEST_POST) {
    return resp_packet;
  }

  // Init global IP string
  if (_global_ip_str == NULL) {
    _global_ip_str = sl_tftp_get_global_addr();
  }

  resp_packet->msg_code = COAP_MSG_CODE_RESPONSE_CREATED;
  resp_packet->content_format = COAP_CT_JSON;

  // CoAP PUT request to start firmware update
  if (req_packet->msg_code == COAP_MSG_CODE_REQUEST_POST) {
    // Start fw update
    if (!memcmp(SL_WISUN_OTA_DFU_START_PAYLOAD_STR,
                req_packet->payload_ptr,
                req_packet->payload_len)) {
      _start_tick_cnt = sl_sleeptimer_get_tick_count();
      (void) sl_wisun_ota_dfu_start_fw_update();

      // Stop fw update
    } else if (!memcmp(SL_WISUN_OTA_DFU_STOP_PAYLOAD_STR,
                       req_packet->payload_ptr,
                       req_packet->payload_len)) {
      (void) sl_wisun_ota_dfu_stop_fw_update();
#if !SL_WISUN_OTA_DFU_AUTO_INSTALL_ENABLED
      // Reboot and install firmware
    } else if (!memcmp(SL_WISUN_OTA_DFU_REBOOT_AND_INSTALL_PAYLOAD_STR,
                       req_packet->payload_ptr,
                       req_packet->payload_len)) {
      (void) sl_wisun_ota_dfu_reboot_and_install();
#endif
      // Bad request
    } else {
      resp_packet->msg_code = COAP_MSG_CODE_RESPONSE_BAD_REQUEST;
    }
  }

  resp_packet->payload_ptr = (uint8_t *) _get_status_json_string();
  resp_packet->payload_len = sl_strnlen((char *) resp_packet->payload_ptr,
                                        SL_WISUN_OTA_DFU_STATUS_JSON_STR_MAX_LEN);
  return resp_packet;
}

static void _tftp_data_hnd(sl_tftp_clnt_t * const clnt,
                           const uint8_t * const data_ptr,
                           const uint16_t data_size)
{
  uint32_t offset = 0;
  static uint32_t prev_offset = 0xFFFFFFFFUL;
  static sl_wisun_ota_dfu_error_ctx_t error_ctx = { 0U };
  static uint16_t chunk_cnt = 1U;

  // Calculate offset
  offset = (clnt->packet.content.data.block_num - 1UL) * SL_TFTP_DATA_BLOCK_SIZE;

  // Try to write the same offset
  // TFTP Server resent data packet (ack from client has not been received in time)
  if (offset == prev_offset) {
    sl_wisun_ota_dfu_log("download: resent offset '0x%.8lx'\n", offset);
    return;
  }
  prev_offset = offset;

  if (clnt->packet.content.data.block_num == 1) {
    _downl_bytes = clnt->packet.content.data.data_size;
  } else {
    _downl_bytes += clnt->packet.content.data.data_size;
    ++chunk_cnt;
  }
#if SL_WISUN_OTA_DFU_HOST_NOTIFY_ENABLED
  if (SL_WISUN_OTA_DFU_NOTIFY_DOWNLOAD_CHUNK_CNT == chunk_cnt) {
    chunk_cnt = 0U;
    _notify_host();
  }
#endif
  error_ctx.download.ret_val = bootloader_eraseWriteStorage(0, offset, (uint8_t *)data_ptr, data_size);

  if (error_ctx.download.ret_val != BOOTLOADER_OK) {
    _change_status(SL_WISUN_OTA_DFU_EVT_FLAG_FW_DOWNLOAD_ERROR_MSK);
    error_ctx.download.offset = offset;
    error_ctx.download.data_size = data_size;
    sl_wisun_ota_dfu_error_hnd(SL_WISUN_OTA_DFU_ERROR_FW_DOWNLOAD, &error_ctx);
    return;
  }

  sl_wisun_ota_dfu_log("download: received chunk %u, offset: 0x%.8lx\n",
                       clnt->packet.content.data.block_num, offset);
}

static void _tftp_error_hnd(sl_tftp_clnt_t * const clnt,
                            const uint16_t error_code,
                            const char *error_msg)
{
  (void)clnt;
  (void)error_code;
  (void)error_msg;

  _change_status(SL_WISUN_OTA_DFU_EVT_FLAG_FW_DOWNLOAD_ERROR_MSK);
  _notify_host();
}

static void _ota_dfu_thr_fnc(void * args)
{
  static BootloaderStorageInformation_t info = { 0U };
  static sl_tftp_clnt_t tftp_clnt = { 0U };
  static sl_wisun_ota_dfu_error_ctx_t error_ctx = { 0U };
  uint32_t flags = 0UL;

  (void) args;

#if SL_WISUN_OTA_DFU_HOST_NOTIFY_ENABLED
  // Create socket
  _notify_ch.sockid = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
  assert(_notify_ch.sockid != -1L);

  // Set address
  _notify_ch.addr.sin6_family = AF_INET6;
  _notify_ch.addr.sin6_port = SL_WISUN_OTA_DFU_NOTIFY_PORT;
  assert(inet_pton(AF_INET6, SL_WISUN_OTA_DFU_NOTIFY_HOST_ADDR,
                   &_notify_ch.addr.sin6_addr) != -1L);

  // prepare packet
  _notify_ch.pkt.msg_code = COAP_MSG_CODE_REQUEST_PUT;
  _notify_ch.pkt.msg_id = SL_WISUN_OTA_DFU_HOST_NOTIFY_COAP_MSG_ID;
  _notify_ch.pkt.msg_type = COAP_MSG_TYPE_NON_CONFIRMABLE;
  _notify_ch.pkt.content_format = COAP_CT_JSON;
  _notify_ch.pkt.uri_path_ptr = (uint8_t *)SL_WISUN_OTA_DFU_NOTIFY_URI_PATH;
  _notify_ch.pkt.uri_path_len = sl_strnlen((char *) SL_WISUN_OTA_DFU_NOTIFY_URI_PATH,
                                           SL_WISUN_OTA_DFU_STATUS_JSON_STR_MAX_LEN);

  _notify_ch.pkt.token_ptr = NULL;
  _notify_ch.pkt.token_len = 0U;
  _notify_ch.pkt.options_list_ptr = NULL;
#endif

  bootloader_getStorageInfo(&info);
  assert(info.numStorageSlots >= 1);

  SL_WISUN_OTA_DFU_SERVICE_LOOP() {
    osEventFlagsClear(_ota_dfu_evt, SL_WISUN_OTA_DFU_EVT_FLAG_ALL_MSK);
    flags = osEventFlagsWait(_ota_dfu_evt, SL_WISUN_OTA_DFU_EVT_FLAG_START_FW_UPDATE_MSK,
                             osFlagsWaitAny | osFlagsNoClear, osWaitForever);

    if (flags & SL_WISUN_OTA_DFU_EVT_FLAG_ERROR_MSK) {
      osDelay(SL_WISUN_OTA_DFU_DELAY_MS);
      continue;
    }

    // Start tick count
    _start_tick_cnt = sl_sleeptimer_get_tick_count();

    sl_wisun_ota_dfu_log("Storage info: version: %lu, capabilities: %lu, storageType: %lu, numStorageSlots: %lu\n",
                         info.version, info.capabilities, (uint32_t)info.storageType, info.numStorageSlots);
    sl_wisun_ota_dfu_log("Firmware upgrade started\n");

    // check stop request
    if (sl_wisun_ota_dfu_get_fw_update_status_flag(SL_WISUN_OTA_DFU_STATUS_FW_UPDATE_STOPPED)) {
      _notify_host();
      osDelay(SL_WISUN_OTA_DFU_DELAY_MS);
      continue;
    }

    // notify host
    _notify_host();

    if (sl_tftp_clnt_init(&tftp_clnt,
                          SL_WISUN_OTA_DFU_HOST_ADDR,
                          SL_WISUN_OTA_DFU_TFTP_PORT,
                          _tftp_data_hnd,
                          _tftp_error_hnd) != SL_STATUS_OK) {
      _change_status(SL_WISUN_OTA_DFU_EVT_FLAG_FW_DOWNLOAD_ERROR_MSK);
      osDelay(SL_WISUN_OTA_DFU_DELAY_MS);
      continue;
    }

    sl_wisun_ota_dfu_log("TFTP init done\n");

    // notify host
    _notify_host();

    sl_wisun_ota_dfu_log("TFTP download started: tftp://[%s]:%u/%s\n",
                         SL_WISUN_OTA_DFU_HOST_ADDR,
                         SL_WISUN_OTA_DFU_TFTP_PORT,
                         SL_WISUN_OTA_DFU_GBL_FILE);

    if (sl_tftp_clnt_request(&tftp_clnt,
                             SL_TFTP_OPCODE_RRQ,
                             SL_WISUN_OTA_DFU_GBL_FILE,
                             SL_TFTP_MODE_OCTET_STR) != SL_STATUS_OK) {
      osDelay(SL_WISUN_OTA_DFU_DELAY_MS);
      continue;
    }

    // waiting for finish firmware download
    SL_WISUN_OTA_DFU_SERVICE_LOOP() {
      if (sl_tftp_clnt_is_op_finished(&tftp_clnt)) {
        break;
      }
      osDelay(SL_WISUN_OTA_DFU_DELAY_MS);
    }

    // check download error
    if (sl_wisun_ota_dfu_get_fw_update_status_flag(SL_WISUN_OTA_DFU_STATUS_FW_DOWNLOAD_ERROR)) {
      osDelay(SL_WISUN_OTA_DFU_DELAY_MS);
      continue;
    }

    // check stop request
    if (sl_wisun_ota_dfu_get_fw_update_status_flag(SL_WISUN_OTA_DFU_STATUS_FW_UPDATE_STOPPED)) {
      _notify_host();
      osDelay(SL_WISUN_OTA_DFU_DELAY_MS);
      continue;
    }

    _change_status(SL_WISUN_OTA_DFU_EVT_FLAG_FW_DOWNLOADED_MSK);
    sl_wisun_ota_dfu_log("TFTP download finished\n");
    osDelay(SL_WISUN_OTA_DFU_DELAY_MS);

    // Verify Image
    error_ctx.verify.ret_val = bootloader_verifyImage(0U, NULL);
    if (error_ctx.verify.ret_val != BOOTLOADER_OK) {
      _change_status(SL_WISUN_OTA_DFU_EVT_FLAG_FW_VERIFY_ERROR_MSK);
      sl_wisun_ota_dfu_error_hnd(SL_WISUN_OTA_DFU_ERROR_FW_VERIFY, &error_ctx);
      continue;
    }
    _change_status(SL_WISUN_OTA_DFU_EVT_FLAG_FW_VERIFIED_MSK);
    sl_wisun_ota_dfu_log("Verify img finished\n");
    osDelay(SL_WISUN_OTA_DFU_DELAY_MS);

    // Set image
    error_ctx.set.ret_val = bootloader_setImageToBootload(0U);
    if (error_ctx.set.ret_val != BOOTLOADER_OK) {
      _change_status(SL_WISUN_OTA_DFU_EVT_FLAG_FW_SET_ERROR_MSK);
      sl_wisun_ota_dfu_error_hnd(SL_WISUN_OTA_DFU_ERROR_FW_SET, &error_ctx);
      continue;
    }
    _change_status(SL_WISUN_OTA_DFU_EVT_FLAG_FW_SET_MSK);
    sl_wisun_ota_dfu_log("Set img finished\n");

    osDelay(SL_WISUN_OTA_DFU_SHUTDOWN_DELAY_MS);

    // check stop request
    if (sl_wisun_ota_dfu_get_fw_update_status_flag(SL_WISUN_OTA_DFU_STATUS_FW_UPDATE_STOPPED)) {
      _notify_host();
      osDelay(SL_WISUN_OTA_DFU_DELAY_MS);
      continue;
    }

#if SL_WISUN_OTA_DFU_AUTO_INSTALL_ENABLED
    bootloader_rebootAndInstall();
#endif
  }
}

static void _notify_host(void)
{
#if SL_WISUN_OTA_DFU_HOST_NOTIFY_ENABLED
  uint16_t req_buff_size = 0UL;
  uint8_t * buff = NULL;

  _notify_ch.pkt.payload_ptr = (uint8_t *)_get_status_json_string();
  _notify_ch.pkt.payload_len = sl_strnlen((char *) _notify_ch.pkt.payload_ptr,
                                          SL_WISUN_OTA_DFU_STATUS_JSON_STR_MAX_LEN);

  req_buff_size = sl_wisun_coap_builder_calc_size(&_notify_ch.pkt);

  buff = (uint8_t *) sl_wisun_coap_malloc(req_buff_size);
  if (buff == NULL) {
    sl_wisun_ota_dfu_log("notify error: sl_wisun_coap_malloc buff\n");
    return;
  }

  if (sl_wisun_coap_builder(buff, &_notify_ch.pkt) < 0) {
    sl_wisun_coap_free(_notify_ch.pkt.payload_ptr);
    sl_wisun_coap_free(buff);
    sl_wisun_ota_dfu_log("notify error: sl_wisun_coap_builder\n");
    return;
  }

  (void) sendto(_notify_ch.sockid, buff, req_buff_size, 0L,
                (const struct sockaddr *) &_notify_ch.addr, sizeof(sockaddr_in6_t));
  sl_wisun_ota_dfu_log("notify: coap://[%s]:%u%s\n",
                       SL_WISUN_OTA_DFU_NOTIFY_HOST_ADDR,
                       SL_WISUN_OTA_DFU_NOTIFY_PORT,
                       SL_WISUN_OTA_DFU_NOTIFY_URI_PATH);
  sl_wisun_coap_free(_notify_ch.pkt.payload_ptr);
  sl_wisun_coap_free(buff);
#else
  (void) 0UL;
#endif
}

static void _change_status(const uint32_t status_mask)
{
  sl_wisun_ota_dfu_log("status update: 0x%lx\n", status_mask);
  (void) osEventFlagsSet(_ota_dfu_evt, status_mask);
  _notify_host();
}

__STATIC_INLINE uint32_t _get_elapsed_time_ms(void)
{
  return sl_sleeptimer_tick_to_ms(sl_sleeptimer_get_tick_count() - _start_tick_cnt);
}
