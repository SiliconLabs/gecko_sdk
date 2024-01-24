/***************************************************************************//**
 * @file
 * @brief
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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
#include <stdio.h>
#include "sl_wisun_ping.h"
#include "cmsis_os2.h"
#include "sl_cmsis_os2_common.h"
#include "socket_hnd.h"
#include "sl_sleeptimer.h"
#include "sl_wisun_trace_util.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

/// Ping status socket error mask
#define SL_WISUN_PING_STATUS_SOCKET_ERROR           (1LU << 1LU)

/// Ping status connect error mask
#define SL_WISUN_PING_STATUS_CONNECT_ERROR          (1LU << 2LU)

/// Ping status send error mask
#define SL_WISUN_PING_STATUS_SEND_ERROR             (1LU << 3LU)

/// Ping interrupt requested mask
#define SL_WISUN_PING_STATUS_ABORT_REQUESTED        (1LU << 4LU)

/// Ping transaction finished mask
#define SL_WISUN_PING_STATUS_TRANSACTION_END        (1LU << 5LU)

/// Ping Start format string
#define SL_WISUN_PING_START_FORMAT_STR \
"PING %s: %u data bytes\n"

/// Ping Destination unreachable format string
#define SL_WISUN_PING_DEST_UNREACHABLE_STR \
"[Destination is unreachable]\n"

/// Ping one line statistic format string
#define SL_WISUN_PING_ONE_LINE_STAT_FORMAT_STR \
"[%u bytes from %s: seq=%u time=%lu ms]\n"

/// Ping full statistic format string
#define SL_WISUN_PING_FULL_STAT_FORMAT_STR                         \
"\nPing statistics for %s:\n"                                      \
"  Packets: Sent = %lu, Received = %lu, Lost = %u, (%lu%% loss)\n" \
"Approximate round trip times in milli-seconds:\n"                 \
"  Minimum = %lums, Maximum = %lums, Average = %lums\n\n"


// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief Fill ping packet payload
 * @details Helper function
 * @param[in,out] icmp_req
 *****************************************************************************/
__STATIC_INLINE void _fill_payload(sl_wisun_ping_echo_request_t * const icmp_req);

/**************************************************************************//**
 * @brief Compare request fields with response fields
 * @details Helper function
 * @param[in] req Request
 * @param[in] resp
 * @return true Request and response are mached
 * @return false Comparision failed
 *****************************************************************************/
__STATIC_INLINE bool _compare_req_resp(const sl_wisun_ping_echo_request_t * const req,
                                     const sl_wisun_ping_echo_response_t * const resp);

/**************************************************************************//**
 * @brief Get milisec value of time spent from start time stamp.
 * @details Helper function
 * @param[in] ping Ping packet
 * @return uint32_t Milisec value
 *****************************************************************************/
__STATIC_INLINE uint32_t _get_ms_val_from_start_time_stamp(const sl_wisun_ping_info_t * const ping);

/**************************************************************************//**
 * @brief Preapre failed response
 * @details Helper function
 * @param[out] resp Destinatino response
 * @param[in] status_flags Status flags
 *****************************************************************************/
__STATIC_INLINE void _prepare_and_push_failed_response(sl_wisun_ping_info_t * const resp, const uint32_t status_flags);

/**************************************************************************//**
 * @brief Ping task function
 * @details Service task function implemented for handling ICMP packets
 * @param[in] args Arguments (empty)
 *****************************************************************************/
static void _ping_task_fnc(void *args);

/**************************************************************************//**
 * @brief Event error getter
 * @details Helper function
 * @param[in] flags Flags
 * @return true Error occured
 * @return false No error
 *****************************************************************************/
__STATIC_INLINE bool _is_ping_evt_error(const uint32_t flags);

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

/// Ping task attributions
static  const osThreadAttr_t _ping_task_attr = {
  .name        = "Ping",
  .attr_bits   = osThreadDetached,
  .cb_mem      = NULL,
  .cb_size     = 0,
  .stack_mem   = NULL,
  .stack_size  = (SL_WISUN_PING_STACK_SIZE_WORD * sizeof(void *)) & 0xFFFFFFF8U,
  .priority    = osPriorityNormal2,
  .tz_module   = 0
};

/// Ping request message queue
static osMessageQueueId_t _ping_req_msg_queue = NULL;

/// Ping request messagequeue attributions
static const osMessageQueueAttr_t _ping_req_msg_queue_attr = {
  .name = "PingReqMsgQueue",
  .attr_bits = 0,
  .cb_mem = NULL,
  .cb_size = 0,
  .mq_mem = NULL,
  .mq_size = 0
};

/// Ping response message queue
static osMessageQueueId_t _ping_resp_msg_queue = NULL;

/// Ping response message queue attributes
static const osMessageQueueAttr_t _ping_resp_msg_queue_attr = {
  .name = "PingRespMsgQueue",
  .attr_bits = 0,
  .cb_mem = NULL,
  .cb_size = 0,
  .mq_mem = NULL,
  .mq_size = 0
};

/// Ping thread id
static osThreadId_t _ping_thr_id;

/// Ping event flags attributes
static const osEventFlagsAttr_t _ping_evt_attr = {
  .name      = "PingEvt",
  .attr_bits = 0,
  .cb_mem    = NULL,
  .cb_size   = 0
};

/// Ping event handler
static osEventFlagsId_t _ping_evt = NULL;

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

/* Ping init */
void sl_wisun_ping_init(void)
{
  _ping_evt = osEventFlagsNew(&_ping_evt_attr);
  assert(_ping_evt != NULL);

  _ping_req_msg_queue = osMessageQueueNew(SL_WISUN_PING_MAX_REQUEST_RESPONSE,
                                          sizeof(sl_wisun_ping_info_t),
                                          &_ping_req_msg_queue_attr);
  assert(_ping_req_msg_queue != NULL);

  _ping_resp_msg_queue = osMessageQueueNew(SL_WISUN_PING_MAX_REQUEST_RESPONSE,
                                           sizeof(sl_wisun_ping_info_t),
                                           &_ping_resp_msg_queue_attr);
  assert(_ping_resp_msg_queue != NULL);
  _ping_thr_id = osThreadNew(_ping_task_fnc, NULL, &_ping_task_attr);
  assert(_ping_thr_id != NULL);
}

/* Ping request */
void sl_wisun_ping_request(const sl_wisun_ping_info_t * const ping_request)
{
  osMessageQueuePut(_ping_req_msg_queue, ping_request, 0U, 0U);
}

/* Ping response */
void sl_wisun_ping_response(sl_wisun_ping_info_t * const ping_response)
{
  uint8_t msg_prio = 0;
  osMessageQueueGet(_ping_resp_msg_queue, ping_response, &msg_prio, osWaitForever);
  (void) msg_prio;
}

/* Ping */
sl_status_t sl_wisun_ping(const wisun_addr_t *const remote_addr,
                          const uint16_t packet_count,
                          const uint16_t packet_length,
                          sl_wisun_ping_stat_hnd_t stat_hnd,
                          sl_wisun_ping_req_resp_done_hnd_t req_resp_sent_hnd)
{
  sl_wisun_ping_info_t *req  = NULL;
  sl_wisun_ping_info_t *resp = NULL;
  sl_wisun_ping_stat_t *stat = NULL;
  const char *rem_ip_str     = NULL;
  static uint16_t id         = 0U;
  uint16_t packet_ok_count   = 0U;
  sl_status_t res            = SL_STATUS_OK;
  bool min_max_ref_set       = false;
  uint32_t flags             = 0UL;
  uint32_t resp_cnt          = 0UL;
  uint32_t sum_resp_pkt      = 0UL;

  // Check args
  if (!packet_count || !packet_length || remote_addr == NULL) {
    return SL_STATUS_FAIL;
  }

  // Clear all event flags
  (void) osEventFlagsClear(_ping_evt, 0xFFFFFFFFUL);

  // Clear response message queue
  (void) osMessageQueueReset(_ping_resp_msg_queue);

  req = (sl_wisun_ping_info_t *) app_wisun_malloc(sizeof(sl_wisun_ping_info_t));
  resp = (sl_wisun_ping_info_t *) app_wisun_malloc(sizeof(sl_wisun_ping_info_t));
  stat = (sl_wisun_ping_stat_t *) app_wisun_malloc(sizeof(sl_wisun_ping_stat_t));

  // fill statistic
  stat->packet_count  = packet_count;
  stat->lost          = 0U;
  stat->min_time_ms   = 0UL;
  stat->max_time_ms   = 0UL;
  stat->avg_time_ms   = 0UL;

  memcpy(&req->remote_addr, remote_addr, sizeof(wisun_addr_t));
  memcpy(&stat->remote_addr, remote_addr, sizeof(wisun_addr_t));

  req->identifier = id++;
  req->sequence_number = 1U;
  req->packet_length = packet_length;

  // check packet length, modify if it's necessary to avoid buffer underflow/overflow
  req->packet_length = req->packet_length < SL_WISUN_PING_MIN_PACKET_LENGTH
                       ? SL_WISUN_PING_MIN_PACKET_LENGTH : req->packet_length;
  req->packet_length = req->packet_length > SL_WISUN_PING_MAX_PACKET_LENGTH
                       ? SL_WISUN_PING_MAX_PACKET_LENGTH : req->packet_length;
  stat->packet_length = req->packet_length;

  rem_ip_str = app_wisun_trace_util_get_ip_str(&req->remote_addr.sin6_addr);

  printf(SL_WISUN_PING_START_FORMAT_STR,
         rem_ip_str, req->packet_length);
  app_wisun_trace_util_destroy_ip_str(rem_ip_str);

  for (uint16_t i = 0U; i < packet_count; ++i) {
    sl_wisun_ping_request(req);
    req->sequence_number++;

    flags = osEventFlagsWait(_ping_evt,
                             SL_WISUN_PING_STATUS_TRANSACTION_END
                             | SL_WISUN_PING_STATUS_ABORT_REQUESTED,
                             osFlagsWaitAny, SL_WISUN_PING_TIMEOUT_MS);

    if ((!_is_ping_evt_error(flags)) && 
        (flags & SL_WISUN_PING_STATUS_ABORT_REQUESTED)) {
      return SL_STATUS_ABORT;
    }

    // Get count of queued messages
    resp_cnt = osMessageQueueGetCount(_ping_resp_msg_queue);

     // if there isn't any response, but it should be
    if (!resp_cnt) {
      printf(SL_WISUN_PING_DEST_UNREACHABLE_STR);
      ++stat->lost;
    }

    // pop up messages
    for (uint32_t i = 0UL; i < resp_cnt; ++i) {
      sl_wisun_ping_response(resp);

      rem_ip_str = app_wisun_trace_util_get_ip_str(&resp->remote_addr.sin6_addr);
      if (resp->lost) {
        printf(SL_WISUN_PING_DEST_UNREACHABLE_STR);
      } else {
        printf(SL_WISUN_PING_ONE_LINE_STAT_FORMAT_STR,
               resp->packet_length,
               rem_ip_str,
               htons(resp->sequence_number),
               resp->response_time_ms);
      }
      app_wisun_trace_util_destroy_ip_str(rem_ip_str);

      if (resp->lost) {
        ++stat->lost;
      } else {
        stat->avg_time_ms += resp->response_time_ms;
        if (!min_max_ref_set) {
          stat->min_time_ms = resp->response_time_ms;
          stat->max_time_ms = resp->response_time_ms;
          min_max_ref_set = true;
        } else {
          stat->min_time_ms = stat->min_time_ms > resp->response_time_ms
                              ? resp->response_time_ms : stat->min_time_ms;
          stat->max_time_ms = stat->max_time_ms < resp->response_time_ms
                              ? resp->response_time_ms : stat->max_time_ms;
        }
      }

      if (req_resp_sent_hnd != NULL) {
        req_resp_sent_hnd(req, resp);
      }
    }
    osDelay(SL_WISUN_PING_PACKET_INTERVAL);
  }

  sum_resp_pkt = resp_cnt ? packet_count * resp_cnt : packet_count;

  if (stat->lost) {
    res = SL_STATUS_FAIL;
  }

  packet_ok_count = sum_resp_pkt - stat->lost;
  if (packet_ok_count) {
    stat->avg_time_ms /= packet_ok_count;
  } else {
    stat->avg_time_ms = 0UL;
  }

  rem_ip_str = app_wisun_trace_util_get_ip_str(&req->remote_addr.sin6_addr);
  if (stat_hnd == NULL) {
    printf(SL_WISUN_PING_FULL_STAT_FORMAT_STR, 
           rem_ip_str, 
           sum_resp_pkt, sum_resp_pkt - stat->lost, 
           stat->lost, 
           (stat->lost * 100U) / sum_resp_pkt,
           stat->min_time_ms, 
           stat->max_time_ms, 
           stat->avg_time_ms);
  } else {
    stat_hnd(stat);
  }
  app_wisun_trace_util_destroy_ip_str(rem_ip_str);

  // free memory
  app_wisun_free(stat);
  app_wisun_free(req);
  app_wisun_free(resp);
  return res;
}

void sl_wisun_ping_stop(void)
{
  (void) osEventFlagsSet(_ping_evt, SL_WISUN_PING_STATUS_ABORT_REQUESTED);
  osThreadSuspend(_ping_thr_id);
  osMessageQueueReset(_ping_req_msg_queue);
  osMessageQueueReset(_ping_resp_msg_queue);
  osThreadResume(_ping_thr_id);
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------

/* Ping task function */
static void _ping_task_fnc(void *args)
{
  static sl_wisun_ping_info_t req                = { 0U };
  static sl_wisun_ping_info_t resp               = { 0U };
  static sl_wisun_ping_echo_request_t icmp_req   = { 0U };
  static sl_wisun_ping_echo_response_t icmp_resp = { 0U };
  int32_t sockid                                 = SOCKET_INVALID_ID;
  osStatus_t stat                                = osError;
  socklen_t len                                  = sizeof(wisun_addr_t);
  int32_t r                                      = RETVAL_ERROR;
  uint32_t time_cnt                              = 0UL;
  uint8_t msg_prio                               = 0U;
  uint32_t status                                = 0UL;
  bool multicast                                 = false;

  (void) args;

  icmp_req.type = SL_WISUN_PING_TYPE_ECHO_REQUEST;
  icmp_req.code = SL_WISUN_PING_CODE_ECHO_REQUEST;
  icmp_req.checksum = 0U;

  // fill payload
  _fill_payload(&icmp_req);

  SL_WISUN_THREAD_LOOP {
    stat = osMessageQueueGet(_ping_req_msg_queue, &req, &msg_prio, 0U);
    (void) msg_prio;
    if (stat != osOK) {
      osDelay(1UL);
      continue;
    }

    status = osEventFlagsGet(_ping_evt);

    if (_is_ping_evt_error(status) || status & SL_WISUN_PING_STATUS_ABORT_REQUESTED) {
      osMessageQueueReset(_ping_req_msg_queue);
      _prepare_and_push_failed_response(&resp, SL_WISUN_PING_STATUS_ABORT_REQUESTED);
      continue;
    }

    // create socket and slect port
    req.remote_addr.sin6_family = AF_WISUN;
    req.remote_addr.sin6_port = htons(SL_WISUN_PING_ICMP_PORT);

    sockid = socket(AF_WISUN, SOCK_RAW, IPPROTO_ICMP);

    if (sockid == SOCKET_INVALID_ID) {
      _prepare_and_push_failed_response(&resp, SL_WISUN_PING_STATUS_SOCKET_ERROR);
      continue;
    }

    // reset previous response
    memset(&icmp_resp, 0U, sizeof(icmp_resp));
    icmp_req.identifier = htons(req.identifier);
    icmp_req.sequence_number = app_wisun_trace_swap_u16(req.sequence_number);

    // send request
    r = sendto(sockid, (const void *) &icmp_req, req.packet_length, 0,
               (const struct sockaddr *)&req.remote_addr, sizeof(wisun_addr_t));
    if (r == RETVAL_ERROR) {
      _prepare_and_push_failed_response(&resp, SL_WISUN_PING_STATUS_SEND_ERROR);
      close(sockid);
      continue;
    }

    // create timestamp after send/sendto
    req.start_time_stamp = sl_sleeptimer_get_tick_count();

    // calculate time milisec counter
    do {
      time_cnt = _get_ms_val_from_start_time_stamp(&req);

      // init response with the request content
      memcpy(&resp, &req, sizeof(sl_wisun_ping_info_t));
      resp.lost = true;

      while (time_cnt < SL_WISUN_PING_TIMEOUT_MS) {
        // receive response
        r = recvfrom(sockid, (void *)&icmp_resp, req.packet_length, 0L,
                     (struct sockaddr *)&resp.remote_addr, &len);

        if (r > 0L) {
          break;
        }
        osDelay(1UL);
        time_cnt = _get_ms_val_from_start_time_stamp(&req);
      }

      if (time_cnt >= SL_WISUN_PING_TIMEOUT_MS) {
        break;
      }

      // if address is not the requeste address (multicast address)
      if (memcmp(&resp.remote_addr.sin6_addr.s6_addr,
                 &req.remote_addr.sin6_addr.s6_addr,
                 sizeof(req.remote_addr.sin6_addr.s6_addr))) {
        multicast = true;
      } else {
        multicast = false;
      }

      // packet validation
      resp.lost = !_compare_req_resp(&icmp_req, &icmp_resp);

      resp.stop_time_stamp = sl_sleeptimer_get_tick_count();
      resp.response_time_ms = sl_sleeptimer_tick_to_ms(resp.stop_time_stamp - resp.start_time_stamp);

      // put response into the message queue
      osMessageQueuePut(_ping_resp_msg_queue, &resp, 0U, 0U);
      osDelay(1UL); // thread dispatch
    } while (multicast);

    osEventFlagsSet(_ping_evt, SL_WISUN_PING_STATUS_TRANSACTION_END);
    close(sockid);
  }
}

/* Compare request response */
__STATIC_INLINE bool _compare_req_resp(const sl_wisun_ping_echo_request_t * const req, const sl_wisun_ping_echo_response_t * const resp)
{
  return req->identifier == resp->identifier
         && req->sequence_number == resp->sequence_number
         && req->type == SL_WISUN_PING_TYPE_ECHO_REQUEST
         && resp->type == SL_WISUN_PING_TYPE_ECHO_RESPONSE ? true : false;
}

/* Prepare and push failed response */
__STATIC_INLINE void _prepare_and_push_failed_response(sl_wisun_ping_info_t * const resp, const uint32_t status_flags)
{
  resp->start_time_stamp = 0;
  resp->stop_time_stamp = 0;
  resp->lost = true;
  (void) osEventFlagsSet(_ping_evt, status_flags);
  osMessageQueuePut(_ping_resp_msg_queue, resp, 0U, 0U);
}

/* Get milisec value from start time stamp*/
__STATIC_INLINE uint32_t _get_ms_val_from_start_time_stamp(const sl_wisun_ping_info_t * const ping)
{
  return sl_sleeptimer_tick_to_ms(sl_sleeptimer_get_tick_count() - ping->start_time_stamp);
}

/* Fill payload */
__STATIC_INLINE void _fill_payload(sl_wisun_ping_echo_request_t * const icmp_req)
{
  // fill payload
  char c = '0';
  for (uint16_t i = 0; i < SL_WISUN_PING_MAX_PAYLOAD_LENGTH; ++i) {
    if (c > '9') {
      c = '0';
    }
    icmp_req->payload[i] = c;
    ++c;
  }
}

__STATIC_INLINE bool _is_ping_evt_error(const uint32_t flags)
{
  return (bool) (flags & (1UL << 31U));
}
