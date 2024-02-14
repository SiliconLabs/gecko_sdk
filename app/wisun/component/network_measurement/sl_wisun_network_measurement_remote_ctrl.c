/***************************************************************************/ /**
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

#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "sl_string.h"
#include "sl_wisun_app_core_util.h"
#include "sl_wisun_trace_util.h"
#include "sl_wisun_network_measurement.h"
#include "sl_wisun_network_measurement_remote_ctrl.h"
#include "sl_iperf.h"
#include "sl_iperf_util.h"
#include "sl_iperf_log.h"
#include "socket/socket.h"
#include "cmsis_os2.h"
#include "sl_cmsis_os2_common.h"
#include "sl_sleeptimer.h"
#include "sl_component_catalog.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

/// Network Measurement Remote Control buffer size
#define SL_WISUN_NWM_REMOTE_CTRL_BUFF_SIZE                 2048UL

/// Remote CLI measurement max query length
#define SL_WISUN_NWM_REMOTE_CTRL_MAX_QUERY_LENGTH          (SL_WISUN_NWM_REMOTE_CTRL_BUFF_SIZE)

/// Remote CLI measurement max string length
#define SL_WISUN_NWM_REMOTE_CTRL_MAX_ARG_STRING_LENGTH     128UL


/// Max stored neighbor count
#define SL_WISUN_NWM_REMOTE_CTRL_MAX_NB_COUNT              30UL

/// Network Measurement Remote Control ping stat format
#define SL_WISUN_NWM_REMOTE_CTRL_PING_STAT_JSON_FORMAT \
  "\"%s\":{\"address\":\"%s\",\
\"pc\":%u,\
\"pl\":%u,\
\"lost\":%u,\
\"min\":%lu,\
\"max\":%lu,\
\"avg\":%lu\
},\n"

/// Network Measurement Remote Control ping stat format
#define SL_WISUN_NWM_REMOTE_CTRL_NBR_STAT_JSON_FORMAT \
  "\"%s\":{\
\"addr\":\"%s\",\
\"lt\":%lu,\
\"txc\":%lu,\
\"txf\":%lu,\
\"txmsc\":%lu,\
\"txmsf\":%lu,\
\"rplr\":%u,\
\"etx\":%u,\
\"rslo\":%u,\
\"rsli\":%u\
},\n"

/// Succeed str
#define SL_WISUN_NWM_REMOTE_CTRL_SUCCEED_STR                      "succeed"
/// Failed str
#define SL_WISUN_NWM_REMOTE_CTRL_FAILED_STR                       "failed"
/// Ping transaction result format str
#define SL_WISUN_NWM_REMOTE_CTRL_PING_RESULT_FROMAT_STR           "[COAP CLI Ping transaction %s]\n"
/// iPerf transaction result format str
#define SL_WISUN_NWM_REMOTE_CTRL_IPERF_RESULT_FROMAT_STR          "[COAP CLI iPerf transaction %s]\n"
/// Neighbor info transaction result format str
#define SL_WISUN_NWM_REMOTE_CTRL_NBRINFO_RESULT_FROMAT_STR        "[COAP CLI NeighborInfo transaction %s]\n"

/// Arg help str
#define SL_WISUN_NWM_REMOTE_CTRL_ARG_HELP_STR                     "help"
/// Arg all str
#define SL_WISUN_NWM_REMOTE_CTRL_ARG_ALL_NODE_STR                 "all"
/// Arg parent node str
#define SL_WISUN_NWM_REMOTE_CTRL_ARG_PARENT_NODE_STR              "parent"
/// Arg Br node str
#define SL_WISUN_NWM_REMOTE_CTRL_ARG_BR_NODE_STR                  "br"
/// Arg Custom node str
#define SL_WISUN_NWM_REMOTE_CTRL_ARG_CUSTOM_NODE_STR              "Custom Node"
/// Arg server str
#define SL_WISUN_NWM_REMOTE_CTRL_ARG_SERVER_STR                   "server"
/// Arg client str
#define SL_WISUN_NWM_REMOTE_CTRL_ARG_CLIENT_STR                   "client"
/// Arg get str
#define SL_WISUN_NWM_REMOTE_CTRL_ARG_GET_STR                      "get"
/// Arg json str
#define SL_WISUN_NWM_REMOTE_CTRL_ARG_JSON_STR                     "json"
/// Arg text str
#define SL_WISUN_NWM_REMOTE_CTRL_ARG_TEXT_STR                     "text"
/// Arg set str
#define SL_WISUN_NWM_REMOTE_CTRL_ARG_SET_STR                      "set"
/// Arg options bandwidth str
#define SL_WISUN_NWM_REMOTE_CTRL_ARG_OPTIONS_BW_STR               "options.bandwidth"
/// Arg options remote addr str
#define SL_WISUN_NWM_REMOTE_CTRL_ARG_OPTIONS_REMOTE_ADDR_STR      "options.remote_addr"
/// Arg options duration str
#define SL_WISUN_NWM_REMOTE_CTRL_ARG_OPTIONS_DURATION_STR         "options.duration"
/// Arg options interval str
#define SL_WISUN_NWM_REMOTE_CTRL_ARG_OPTIONS_INTERVAL_STR         "options.interval"

/// Response no coap payload str
#define SL_WISUN_NWM_REMOTE_CTRL_RESP_NO_COAP_PAYLOAD_STR         "[No CoAP payload: -e \"<cli command>\"]"
/// Response not enough argument str
#define SL_WISUN_NWM_REMOTE_CTRL_RESP_NOT_ENOUGH_ARG_STR          "[Not enough argument]"
/// Response ping help str
#define SL_WISUN_NWM_REMOTE_CTRL_RESP_PING_HELP_STR               "[Ping CLI help: measure <packet_count> <packet_size> <address>]"
/// Response IP not valid str
#define SL_WISUN_NWM_REMOTE_CTRL_RESP_IP_NOT_VALID_STR            "[IP address is not set or not valid]"
/// Response invalid result type str
#define SL_WISUN_NWM_REMOTE_CTRL_RESP_INVALID_RES_TYPE_STR        "[Invalid result type]"
/// Response buffer error str
#define SL_WISUN_NWM_REMOTE_CTRL_RESP_BUFF_ERROR_STR              "[Buffer error]"
/// Response unknown cli command str
#define SL_WISUN_NWM_REMOTE_CTRL_RESP_UNKNOWN_CLI_STR             "[Unknown cli command]"
/// Response test queue failed str
#define SL_WISUN_NWM_REMOTE_CTRL_RESP_TEST_QUEUE_FAILED_STR       "[Adding test to queue failed]"
/// Response iPerf server started str
#define SL_WISUN_NWM_REMOTE_CTRL_RESP_IPERF_SRV_STARTED           "[iPerf server started]"
/// Response iPerf client started str
#define SL_WISUN_NWM_REMOTE_CTRL_RESP_IPERF_CLNT_STARTED          "[iPerf client started]"
/// Response iPerf set successfully str
#define SL_WISUN_NWM_REMOTE_CTRL_RESP_IPERF_SET_SUCCEED           "[iPerf parameter is set succesfully]"
/// Response iPerf set failed str
#define SL_WISUN_NWM_REMOTE_CTRL_RESP_IPERF_SET_FAILED            "[iPerf parameter setting is failed]"
/// Response iperf help str
#define SL_WISUN_NWM_REMOTE_CTRL_RESP_IPERF_HELP_STR \
  "\niPerf Remote Control CLI Help.\n\n\
  Writable options:\n\
    - remote_addr\n\
    - bandwidth\n\
    - duration\n\
    - interval\n\
  Example: iperf set options.bandwidth 10000\n\n\
  Start iPerf command: iperf <client|server>\n\n\
  Get iPerf results: iperf get <text|json>\n"

/// Remote CLI measurement print target type
typedef enum sl_wisun_nwm_remote_ctrl_buf_target {
  /// Nothing measurement
  SL_WISUN_NWM_REMOTE_CTRL_BUF_TARGET_NONE = -1,
  /// Only Border Router measurement
  SL_WISUN_NWM_REMOTE_CTRL_BUF_TARGET_BORDER_ROUTER,
  /// Only Primary Parent measurement
  SL_WISUN_NWM_REMOTE_CTRL_BUF_TARGET_PARENT,
  /// Measure all of available nodes
  SL_WISUN_NWM_REMOTE_CTRL_BUF_TARGET_ALL,
  /// Measure single node
  SL_WISUN_NWM_REMOTE_CTRL_BUF_TARGET_SINGLE,
  // Measurement iPerf json format
  SL_WISUN_NWM_REMOTE_CTRL_BUF_TARGET_IPERF_JSON,
  // Measurement iPerf text format
  SL_WISUN_NWM_REMOTE_CTRL_BUF_TARGET_IPERF_TEXT,
  // Neighbor info buff type
  SL_WISUN_NWM_REMOTE_CTRL_BUF_TARGET_NBINF
} sl_wisun_nwm_remote_ctrl_buf_target_t;

/// Remote CLI measurement command structure
typedef struct sl_wisun_nwm_remote_ctrl_cmd {
  /// Nothing measurement
  char* identifier;
  /// Argument1 string
  char* arg1;
  /// Argument2 string
  char* arg2;
  /// Argument3 string
  char* arg3;
} sl_wisun_nwm_remote_ctrl_cmd_t;

/// Remote CLI response
typedef struct sl_wisun_nwm_remote_ctrl_resp {
  /// message code
  sn_coap_msg_code_e msg_code;
  /// payload constant str ptr
  const char *payload;
} sl_wisun_nwm_remote_ctrl_resp_t;

/// Response no coap payload
static const sl_wisun_nwm_remote_ctrl_resp_t _resp_no_coap_payload = {
  .payload = SL_WISUN_NWM_REMOTE_CTRL_RESP_NO_COAP_PAYLOAD_STR, 
  .msg_code= COAP_MSG_CODE_RESPONSE_NOT_ACCEPTABLE
};
/// Response not enough argument
static const sl_wisun_nwm_remote_ctrl_resp_t _resp_not_enough_arg = {
  .payload = SL_WISUN_NWM_REMOTE_CTRL_RESP_NOT_ENOUGH_ARG_STR, 
  .msg_code= COAP_MSG_CODE_RESPONSE_NOT_ACCEPTABLE
};
/// Response ping help
static const sl_wisun_nwm_remote_ctrl_resp_t _resp_ping_help = {
  .payload = SL_WISUN_NWM_REMOTE_CTRL_RESP_PING_HELP_STR,
  .msg_code= COAP_MSG_CODE_RESPONSE_CONTENT
};
/// Response IP not valid
static const sl_wisun_nwm_remote_ctrl_resp_t _resp_ip_not_valid = {
  .payload = SL_WISUN_NWM_REMOTE_CTRL_RESP_IP_NOT_VALID_STR,
  .msg_code= COAP_MSG_CODE_RESPONSE_NOT_ACCEPTABLE
};
/// Response invalid result type
static const sl_wisun_nwm_remote_ctrl_resp_t _resp_invalid_res_type = {
  .payload = SL_WISUN_NWM_REMOTE_CTRL_RESP_INVALID_RES_TYPE_STR,
  .msg_code= COAP_MSG_CODE_RESPONSE_NOT_ACCEPTABLE
};
/// Response buffer error
static const sl_wisun_nwm_remote_ctrl_resp_t _resp_buff_error = {
  .payload = SL_WISUN_NWM_REMOTE_CTRL_RESP_BUFF_ERROR_STR,
  .msg_code= COAP_MSG_CODE_RESPONSE_NOT_ACCEPTABLE
};
/// Response unknown cli command
static const sl_wisun_nwm_remote_ctrl_resp_t _resp_unknown_cli = {
  .payload = SL_WISUN_NWM_REMOTE_CTRL_RESP_UNKNOWN_CLI_STR,
  .msg_code= COAP_MSG_CODE_RESPONSE_NOT_ACCEPTABLE
};
/// Response test queue faled
static const sl_wisun_nwm_remote_ctrl_resp_t _resp_test_queue_failed = {
  .payload = SL_WISUN_NWM_REMOTE_CTRL_RESP_TEST_QUEUE_FAILED_STR,
  .msg_code= COAP_MSG_CODE_RESPONSE_NOT_ACCEPTABLE
};
/// Response iPerf server started
static const sl_wisun_nwm_remote_ctrl_resp_t _resp_iperf_srv_started = {
  .payload = SL_WISUN_NWM_REMOTE_CTRL_RESP_IPERF_SRV_STARTED,
  .msg_code= COAP_MSG_CODE_RESPONSE_CONTENT
};
/// Response iPerf client started
static const sl_wisun_nwm_remote_ctrl_resp_t _resp_iperf_clnt_started = {
  .payload = SL_WISUN_NWM_REMOTE_CTRL_RESP_IPERF_CLNT_STARTED,
  .msg_code= COAP_MSG_CODE_RESPONSE_CONTENT
};

/// Response iPerf set successfully
static const sl_wisun_nwm_remote_ctrl_resp_t _resp_iperf_set_succeed = {
  .payload = SL_WISUN_NWM_REMOTE_CTRL_RESP_IPERF_SET_SUCCEED,
  .msg_code= COAP_MSG_CODE_RESPONSE_CHANGED
};

/// Response iPerf set failed
static const sl_wisun_nwm_remote_ctrl_resp_t _resp_iperf_set_failed = {
  .payload = SL_WISUN_NWM_REMOTE_CTRL_RESP_IPERF_SET_FAILED,
  .msg_code= COAP_MSG_CODE_RESPONSE_NOT_ACCEPTABLE
};

/// Response iperf help
static const sl_wisun_nwm_remote_ctrl_resp_t _resp_iperf_help = {
  .payload = SL_WISUN_NWM_REMOTE_CTRL_RESP_IPERF_HELP_STR,
  .msg_code= COAP_MSG_CODE_RESPONSE_CONTENT
};

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief Ping statistic to JSON parser.
 * @details Parse Ping measurement result to JSON format.
 * @param[in, out] payload_pos Payload buffer print position.
 * @param[in] stat Ping statistic.
 * @param[in,out] payload_len Remaining payload size.
 * @return Payload buffer position after print.
 *****************************************************************************/
static void _parse_stat_to_json(char **payload_pos,
                                const sl_wisun_nwm_node_stat_t * const stat,
                                uint16_t * const payload_len);

/**************************************************************************//**
 * @brief Build payload and CoAP packet
 * @details Helper function
 * @param[in] req_packet Request packet
 * @param[in] target Measurement print target
 * @return sl_wisun_coap_packet_t * Built CoAP packet on success, otherwise NULL
 *****************************************************************************/
static sl_wisun_coap_packet_t *  _build_response(const sl_wisun_coap_packet_t * const req_packet,
                                                 const sl_wisun_nwm_remote_ctrl_buf_target_t target);


/**************************************************************************//**
 * @brief Build iPerf result in json and plain text format
 * @details Helper function
 * @param[in] target Measurement print target
 * @param[in,out] payload_buff Payload buffer pointer
 * @return char * Payload for CoAP packet on success, otherwise NULL
 *****************************************************************************/
static char * _build_iperf_result(const sl_wisun_nwm_remote_ctrl_buf_target_t target,
                                  char * const payload_buff);

/**************************************************************************//**
 * @brief Build neighbor info string
 * @details Helper function
 * @param[in,out] payload_buff Payload buffer pointer
 * @param[in,out] nodes Node storage ptr
 * @param[in,out] br_stat Border router statistic ptr
 * @param[in,out] pp_stat Primary parent statistic ptr
 * @param[in,out] children_stats Children statistic array
 * @return char * Payload for CoAP packet on success, otherwise NULL
 *****************************************************************************/
static char * _build_nbr_info(char * const payload_buff,
                              sl_wisun_nwm_measurable_node_t * const nodes,
                              sl_wisun_nwm_node_stat_t * const br_stat,
                              sl_wisun_nwm_node_stat_t * const pp_stat,
                              sl_wisun_nwm_node_stat_t * const children_stats);

/**************************************************************************//**
 * @brief Build neighbor info string
 * @details Helper function
 * @param[in] target Measurement print target
 * @param[in,out] payload_buff Payload buffer pointer
 * @param[in,out] br_stat Border router statistic ptr
 * @param[in,out] pp_stat Primary parent statistic ptr
 * @param[in,out] children_stats Children statistic array
 * @return char * Payload for CoAP packet on success, otherwise NULL
 *****************************************************************************/
static char * _build_ping_meas_stat(const sl_wisun_nwm_remote_ctrl_buf_target_t target,
                                    char * const payload_buff,
                                    sl_wisun_nwm_node_stat_t * const br_stat,
                                    sl_wisun_nwm_node_stat_t * const pp_stat,
                                    sl_wisun_nwm_node_stat_t * const children_stats);

/**************************************************************************//**
 * @brief Build payload for CoAP response packet.
 * @details Build payload for CoAP response packet.
 * @param[in] target Measurement print target.
 * @return char * built payload on success, otherwise NULL
 *****************************************************************************/
static char * _build_payload(sl_wisun_nwm_remote_ctrl_buf_target_t target);

/**************************************************************************//**
 * @brief Build response packet from response instance
 * @details Build response with response builder API based on the request packet, and set payload if it's exist
 * @param[in] resp Response instance
 * @param[in] req_packet Request packet
 * @return sl_wisun_coap_packet_t * Response packet ptr
 *****************************************************************************/
static sl_wisun_coap_packet_t * _build_response_packet(const sl_wisun_nwm_remote_ctrl_resp_t * const resp,
                                                       const sl_wisun_coap_packet_t * const req_packet);

/**************************************************************************//**
 * @brief Network Measurement custom stat handler.
 * @details Catch stat object after measurement and copy to local variable.
 * @param[in] stat Statistic result after a ping measurement.
 *****************************************************************************/
static void _stat_handler(sl_wisun_ping_stat_t *stat);

/**************************************************************************//**
 * @brief CoAP remote CLI ping request parser.
 * @details Parse incoming request, and build response CoAP packet.
 * @param[in] req_packet Request packet.
 * @return sl_wisun_coap_packet_t * Response packet ptr
 *****************************************************************************/
static sl_wisun_coap_packet_t * _parse_ping(const sl_wisun_coap_packet_t * const req_packet);

/**************************************************************************//**
 * @brief CoAP remote CLI iPerf request parser.
 * @details Parse incoming request, and build response CoAP packet.
 * @param[in] req_packet Request packet.
 * @return sl_wisun_coap_packet_t * Response packet ptr
 *****************************************************************************/
static sl_wisun_coap_packet_t * _parse_iperf(const sl_wisun_coap_packet_t * const req_packet);

/**************************************************************************//**
 * @brief CLI command splitter.
 * @details Split CLI command string to structure.
 * @param[in] req_cmd Incoming CLI command string.
 * @param[in, out] cmd Command structure.
 *****************************************************************************/
static void _parse_remote_cmd(char* req_cmd,
                              sl_wisun_nwm_remote_ctrl_cmd_t* cmd);

/**************************************************************************//**
 * @brief iPerf server handler.
 * @details Start iPerf server.
 * @param[in] req_packet Request packet.
 * @return sl_wisun_coap_packet_t * Response packet ptr
 *****************************************************************************/
static sl_wisun_coap_packet_t * _start_iperf_server(const sl_wisun_coap_packet_t * const req_packet);

/**************************************************************************//**
 * @brief iPerf client handler.
 * @details Start iPerf client.
 * @param[in] req_packet Request packet.
 * @return sl_wisun_coap_packet_t * Response packet ptr
 *****************************************************************************/
static sl_wisun_coap_packet_t * _start_iperf_client(const sl_wisun_coap_packet_t * const req_packet);


/**************************************************************************//**
 * @brief Parse neighbor statistic to json format
 * @details Helper function
 * @param[in,out] payload_pos Current payload position, it is incremented
 * @param[in] stat Statistic data
 * @param[in,out] payload_len Current payload length, it is decremented
 *****************************************************************************/
static void _parse_nbr_stat_to_json(char **payload_pos,
                                    const sl_wisun_nwm_node_stat_t * const stat,
                                    int16_t * const payload_len);

/**************************************************************************//**
 * @brief Log printer only to buffer
 * @details Helper function to print to the internal buffer
 * @param[in,out] log Log instance
 * @param[in] format Format string
 * @param[in] ... args
 * @return int32_t Result by functions like snprintf and printf
 *****************************************************************************/
static int32_t _log_print_only_buff(sl_iperf_log_t * const log, const char * format, ...);

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

/// iperf structure with default settings of options
static sl_iperf_opt_t _options = {
  .bandwidth = SL_IPERF_CLIENT_DEFAULT_BANDWIDTH_BPS,
  .bw_format = SL_IPERF_OPT_BW_FORMAT_BITS_PER_SEC,
  .interval_ms = SL_IPERF_DEFAULT_INTERVAL_MS,
  .mode = SL_IPERF_MODE_SERVER,
  .protocol = SL_IPERF_IPROTOV6_UDP,
  .port = SL_IPERF_SERVER_DEFAULT_PORT,
  .duration_ms = SL_IPERF_CLIENT_DEFAULT_SEND_TIME_MS,
  .buf_len = SL_IPERF_BUFFER_SIZE
};

/// Network Measurement Remote Control Ping stat
static sl_wisun_nwm_node_stat_t _stat;

/// Network Measurement Remote Control iPerf last test result
static sl_iperf_test_t _last_test = { 0U };

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

__STATIC_INLINE void _print_cb_result(const char * format_str, 
                                      const sl_wisun_coap_packet_t * const resp_packet)
{
   printf(format_str, resp_packet != NULL ? SL_WISUN_NWM_REMOTE_CTRL_SUCCEED_STR : SL_WISUN_NWM_REMOTE_CTRL_FAILED_STR);
}

sl_wisun_coap_packet_t * sl_wisun_coap_remote_cli_ping_cb(const sl_wisun_coap_packet_t * const req_packet)
{
  sl_wisun_coap_packet_t * resp_packet = NULL;
  resp_packet = _parse_ping(req_packet);
  _print_cb_result(SL_WISUN_NWM_REMOTE_CTRL_PING_RESULT_FROMAT_STR, resp_packet);
  return resp_packet;
}

sl_wisun_coap_packet_t * sl_wisun_coap_remote_cli_iperf_cb(const sl_wisun_coap_packet_t * const req_packet)
{
  sl_wisun_coap_packet_t * resp_packet = NULL;
  resp_packet = _parse_iperf(req_packet);
  _print_cb_result(SL_WISUN_NWM_REMOTE_CTRL_IPERF_RESULT_FROMAT_STR, resp_packet);
  return resp_packet;
}

sl_wisun_coap_packet_t * sl_wisun_coap_remote_cli_nbr_cb(const sl_wisun_coap_packet_t * const req_packet)
{
  sl_wisun_coap_packet_t * resp_packet = NULL;
  resp_packet = _build_response(req_packet, SL_WISUN_NWM_REMOTE_CTRL_BUF_TARGET_NBINF);
  _print_cb_result(SL_WISUN_NWM_REMOTE_CTRL_NBRINFO_RESULT_FROMAT_STR, resp_packet);
  return resp_packet;
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------


static sl_wisun_coap_packet_t * _parse_ping(const sl_wisun_coap_packet_t * const req_packet)
{
  sl_wisun_nwm_remote_ctrl_cmd_t ping_cmd = { 0U };
  sockaddr_in6_t remote_addr = { 0U };
  uint16_t packet_count = 0U;
  uint16_t packet_size = 0U;
  char* req_payload = NULL;
  sl_wisun_nwm_remote_ctrl_buf_target_t print_target = SL_WISUN_NWM_REMOTE_CTRL_BUF_TARGET_NONE;

  // Parsing incoming cli command string.
  req_payload = sl_wisun_coap_get_payload_str(req_packet);
  if (req_payload == NULL) {
    return _build_response_packet(&_resp_no_coap_payload, req_packet);
  }
  _parse_remote_cmd(req_payload, &ping_cmd);

  if (ping_cmd.identifier == NULL || ping_cmd.arg1 == NULL) {
    sl_wisun_coap_destroy_payload_str(req_payload);
    return _build_response_packet(&_resp_not_enough_arg, req_packet);
  }

  // Handle help request.
  if (!strncmp(ping_cmd.arg1,
               SL_WISUN_NWM_REMOTE_CTRL_ARG_HELP_STR, 
               SL_WISUN_NWM_REMOTE_CTRL_MAX_ARG_STRING_LENGTH)) {
    sl_wisun_coap_destroy_payload_str(req_payload);
    return _build_response_packet(&_resp_ping_help, req_packet);
  }

  if (ping_cmd.arg2 == NULL) {
    sl_wisun_coap_destroy_payload_str(req_payload);
    return _build_response_packet(&_resp_not_enough_arg, req_packet);
  }
  packet_count = atoi(ping_cmd.arg1);
  packet_size = atoi(ping_cmd.arg2);

  // Handle measurement request based on address.
  if (ping_cmd.arg3 != NULL && !strncmp(ping_cmd.arg3, 
                                        SL_WISUN_NWM_REMOTE_CTRL_ARG_ALL_NODE_STR, 
                                        SL_WISUN_NWM_REMOTE_CTRL_MAX_ARG_STRING_LENGTH)) {
    sl_wisun_nwm_quick_measure(SL_WISUN_NWM_TARGET_TYPE_ALL, packet_count, packet_size);
    print_target = SL_WISUN_NWM_REMOTE_CTRL_BUF_TARGET_ALL;
  } else if (ping_cmd.arg3 != NULL && !strncmp(ping_cmd.arg3, 
                                               SL_WISUN_NWM_REMOTE_CTRL_ARG_PARENT_NODE_STR, 
                                               SL_WISUN_NWM_REMOTE_CTRL_MAX_ARG_STRING_LENGTH)) {
    sl_wisun_nwm_quick_measure(SL_WISUN_NWM_TARGET_TYPE_PARENT, packet_count, packet_size);
    print_target = SL_WISUN_NWM_REMOTE_CTRL_BUF_TARGET_PARENT;
  } else if (ping_cmd.arg3 != NULL && !strncmp(ping_cmd.arg3, 
                                               SL_WISUN_NWM_REMOTE_CTRL_ARG_BR_NODE_STR, 
                                               SL_WISUN_NWM_REMOTE_CTRL_MAX_ARG_STRING_LENGTH)) {
    sl_wisun_nwm_quick_measure(SL_WISUN_NWM_TARGET_TYPE_BORDER_ROUTER, packet_count, packet_size);
    print_target = SL_WISUN_NWM_REMOTE_CTRL_BUF_TARGET_BORDER_ROUTER;
  } else {
    if (ping_cmd.arg3 != NULL && inet_pton(AF_INET6, ping_cmd.arg3, &remote_addr.sin6_addr) == SOCKET_RETVAL_ERROR) {
      sl_wisun_coap_destroy_payload_str(req_payload);
      return _build_response_packet(&_resp_ip_not_valid, req_packet);
    }
    (void)sl_wisun_ping(&remote_addr, packet_count, packet_size,
                        _stat_handler, NULL);
    _stat.name = SL_WISUN_NWM_REMOTE_CTRL_ARG_CUSTOM_NODE_STR;
    _stat.addr = remote_addr;
    print_target = SL_WISUN_NWM_REMOTE_CTRL_BUF_TARGET_SINGLE;
  }

  sl_wisun_coap_destroy_payload_str(req_payload);

  // Build response packet
  return _build_response(req_packet, print_target);
}

static sl_wisun_coap_packet_t * _parse_iperf(const sl_wisun_coap_packet_t * const req_packet)
{
  sl_wisun_nwm_remote_ctrl_cmd_t iperf_cmd = { 0U };
  char* req_payload = NULL;
  sl_wisun_nwm_remote_ctrl_buf_target_t get_res_type = SL_WISUN_NWM_REMOTE_CTRL_BUF_TARGET_NONE;
  sl_wisun_coap_packet_t * resp_packet = NULL;

  // Parsing incoming cli command string.
  req_payload = sl_wisun_coap_get_payload_str(req_packet);
  if (req_payload == NULL) {
    return _build_response_packet(&_resp_no_coap_payload, req_packet);
  }

  _parse_remote_cmd(req_payload, &iperf_cmd);

  if (iperf_cmd.identifier == NULL || iperf_cmd.arg1 == NULL) {
    sl_wisun_coap_destroy_payload_str(req_payload);
    return _build_response_packet(&_resp_not_enough_arg, req_packet);
  }

  // Handle help request.
  if (!strncmp(iperf_cmd.arg1, 
               SL_WISUN_NWM_REMOTE_CTRL_ARG_HELP_STR, 
               SL_WISUN_NWM_REMOTE_CTRL_MAX_ARG_STRING_LENGTH)) {
    sl_wisun_coap_destroy_payload_str(req_payload);
    return _build_response_packet(&_resp_iperf_help, req_packet);
  }

  // Handle server or client start requests.
  if (!strncmp(iperf_cmd.arg1, 
               SL_WISUN_NWM_REMOTE_CTRL_ARG_SERVER_STR, 
               SL_WISUN_NWM_REMOTE_CTRL_MAX_ARG_STRING_LENGTH)) {
    sl_wisun_coap_destroy_payload_str(req_payload);
    return _start_iperf_server(req_packet);
  }

  if (!strncmp(iperf_cmd.arg1, 
               SL_WISUN_NWM_REMOTE_CTRL_ARG_CLIENT_STR, 
               SL_WISUN_NWM_REMOTE_CTRL_MAX_ARG_STRING_LENGTH)) {
    sl_wisun_coap_destroy_payload_str(req_payload);
    return _start_iperf_client(req_packet);
  }

  if (iperf_cmd.arg2 == NULL) {
    sl_wisun_coap_destroy_payload_str(req_payload);

    return _build_response_packet(&_resp_not_enough_arg, req_packet);
  }

  // Handle get requests.
  if (!strncmp(iperf_cmd.arg1, 
               SL_WISUN_NWM_REMOTE_CTRL_ARG_GET_STR, 
               SL_WISUN_NWM_REMOTE_CTRL_MAX_ARG_STRING_LENGTH)) {
    if (!strncmp(iperf_cmd.arg2, 
                 SL_WISUN_NWM_REMOTE_CTRL_ARG_JSON_STR, 
                 SL_WISUN_NWM_REMOTE_CTRL_MAX_ARG_STRING_LENGTH)) {
      get_res_type = SL_WISUN_NWM_REMOTE_CTRL_BUF_TARGET_IPERF_JSON;
    } else if (!strncmp(iperf_cmd.arg2, 
                        SL_WISUN_NWM_REMOTE_CTRL_ARG_TEXT_STR, 
                        SL_WISUN_NWM_REMOTE_CTRL_MAX_ARG_STRING_LENGTH)) {
      get_res_type = SL_WISUN_NWM_REMOTE_CTRL_BUF_TARGET_IPERF_TEXT;
    } else {
      // Invalid iperf get request
      resp_packet = _build_response_packet(&_resp_invalid_res_type, req_packet);
    }

    if (get_res_type != SL_WISUN_NWM_REMOTE_CTRL_BUF_TARGET_NONE) {
      (void) sl_iperf_test_get(&_last_test, 1);
      resp_packet = _build_response(req_packet, get_res_type);
      if (resp_packet == NULL) {
        resp_packet = _build_response_packet(&_resp_buff_error, req_packet);
      }
    }

    // Clean memory
    sl_wisun_coap_destroy_payload_str(req_payload);
    return resp_packet;
  }

  if (iperf_cmd.arg3 == NULL) {
    sl_wisun_coap_destroy_payload_str(req_payload);
    return _build_response_packet(&_resp_not_enough_arg, req_packet);
  }

  // Handle settings requests.
  if (!strncmp(iperf_cmd.arg1, 
               SL_WISUN_NWM_REMOTE_CTRL_ARG_SET_STR, 
               SL_WISUN_NWM_REMOTE_CTRL_MAX_ARG_STRING_LENGTH)) {

    if (!strncmp(iperf_cmd.arg2, 
                 SL_WISUN_NWM_REMOTE_CTRL_ARG_OPTIONS_BW_STR, 
                 SL_WISUN_NWM_REMOTE_CTRL_MAX_ARG_STRING_LENGTH)) {
      _options.bandwidth = atoi(iperf_cmd.arg3);
      resp_packet = _build_response_packet(&_resp_iperf_set_succeed, req_packet);
    
    } else if (!strncmp(iperf_cmd.arg2, 
                        SL_WISUN_NWM_REMOTE_CTRL_ARG_OPTIONS_REMOTE_ADDR_STR, 
                        SL_WISUN_NWM_REMOTE_CTRL_MAX_ARG_STRING_LENGTH)) {
      memcpy(_options.remote_addr, 
             iperf_cmd.arg3, 
             sl_strnlen(iperf_cmd.arg3, SL_WISUN_NWM_REMOTE_CTRL_MAX_QUERY_LENGTH));
      resp_packet = _build_response_packet(&_resp_iperf_set_succeed, req_packet);
    
    } else if (!strncmp(iperf_cmd.arg2, 
                        SL_WISUN_NWM_REMOTE_CTRL_ARG_OPTIONS_DURATION_STR, 
                        SL_WISUN_NWM_REMOTE_CTRL_MAX_ARG_STRING_LENGTH)) {
      _options.duration_ms = atoi(iperf_cmd.arg3);
      resp_packet = _build_response_packet(&_resp_iperf_set_succeed, req_packet);
    
    } else if (!strncmp(iperf_cmd.arg2, 
                        SL_WISUN_NWM_REMOTE_CTRL_ARG_OPTIONS_INTERVAL_STR, 
                        SL_WISUN_NWM_REMOTE_CTRL_MAX_ARG_STRING_LENGTH)) {
      _options.interval_ms = atoi(iperf_cmd.arg3);
      resp_packet = _build_response_packet(&_resp_iperf_set_succeed, req_packet);
    
    } else {
      resp_packet = _build_response_packet(&_resp_iperf_set_failed, req_packet);
    }
  } else {
    resp_packet = _build_response_packet(&_resp_unknown_cli, req_packet);
  }

  // Clean memory
  sl_wisun_coap_destroy_payload_str(req_payload);
  return resp_packet;
}

static  sl_wisun_coap_packet_t * _start_iperf_server(const sl_wisun_coap_packet_t * const req_packet)
{
  static sl_iperf_test_t test = { 0U };

  // Set iPerf server options and init test descriptor.
  _options.mode = SL_IPERF_MODE_SERVER;
  _options.protocol = SL_IPERF_IPROTOV6_UDP;
  sl_iperf_test_init(&test, SL_IPERF_MODE_SERVER, SL_IPERF_IPROTOV6_UDP);
  memcpy(&test.opt, &_options, sizeof(sl_iperf_opt_t));

  // Adds the test to the queue
  if (!sl_iperf_test_add(&test)) {
    return _build_response_packet(&_resp_test_queue_failed, 
                                  req_packet);
  }

  // Build response packet.
  return _build_response_packet(&_resp_iperf_srv_started, 
                                req_packet);
}

static sl_wisun_coap_packet_t * _start_iperf_client(const sl_wisun_coap_packet_t * const req_packet)
{
  static sl_iperf_test_t test = { 0U };

  /// 1. Set iPerf client options and init test descriptor.
  _options.mode = SL_IPERF_MODE_CLIENT;
  _options.protocol = SL_IPERF_IPROTOV6_UDP;
  sl_iperf_test_init(&test, SL_IPERF_MODE_CLIENT, SL_IPERF_IPROTOV6_UDP);
  memcpy(&test.opt, &_options, sizeof(sl_iperf_opt_t));

  // Adds the test to the queue.
  if (!sl_iperf_test_add(&test)) {
    return _build_response_packet(&_resp_test_queue_failed, req_packet);
  }

  // Build response packet.
  return _build_response_packet(&_resp_iperf_clnt_started, 
                                req_packet);
}

static void _parse_remote_cmd(char* req_cmd, sl_wisun_nwm_remote_ctrl_cmd_t* cmd)
{
  cmd->identifier = strtok(req_cmd, " ");
  cmd->arg1 = strtok(NULL, " ");
  cmd->arg2 = strtok(NULL, " ");
  cmd->arg3 = strtok(NULL, " ");
}

static char * _build_iperf_result(const sl_wisun_nwm_remote_ctrl_buf_target_t target,
                                  char * const payload_buff)
{
     // Set buffer
    sl_iperf_log_set_buff(_last_test.log, payload_buff, SL_WISUN_NWM_REMOTE_CTRL_BUFF_SIZE);

    // Set printer
    sl_iperf_log_set_printer(_last_test.log, _log_print_only_buff);

    if (target == SL_WISUN_NWM_REMOTE_CTRL_BUF_TARGET_IPERF_JSON) {
      // Print json formatted log
      sl_iperf_print_test_log_json(&_last_test);
    } else {
      // print connection string with addresses
      sl_iperf_test_print_udp_conn_str(&_last_test);
      // print report header
      if (_last_test.opt.mode == SL_IPERF_MODE_SERVER) {
        sl_iperf_test_print_udp_srv_report_hdr(&_last_test);
      } else {
        sl_iperf_test_print_udp_clnt_report_hdr(&_last_test);
      }
      // print report summary
      sl_iperf_test_calculate_average_bandwidth(&_last_test);
    }

    // Reinit log
    sl_iperf_log_init(_last_test.log);
    return payload_buff;
}

static char * _build_nbr_info(char * const payload_buff,
                              sl_wisun_nwm_measurable_node_t * const nodes,
                              sl_wisun_nwm_node_stat_t * const br_stat,
                              sl_wisun_nwm_node_stat_t * const pp_stat,
                              sl_wisun_nwm_node_stat_t * const children_stats)
{
  int16_t free_payload_len = SL_WISUN_NWM_REMOTE_CTRL_BUFF_SIZE;
  uint8_t children_count = 0U;
  char *payload_pos = NULL;

  payload_pos = payload_buff;

  // get count of neighbors
  (void) sl_wisun_nwm_get_nodes(nodes, SL_WISUN_MAX_NODE_COUNT, true);

  sl_wisun_nwm_get_border_router_stat(br_stat);
  sl_wisun_nwm_get_primary_parent_stat(pp_stat);
  sl_wisun_nwm_get_children_stat(children_stats, 30U, &children_count);

  payload_pos += snprintf(payload_pos, free_payload_len, "{\n");
  --free_payload_len;
  _parse_nbr_stat_to_json(&payload_pos, br_stat, &free_payload_len);
  _parse_nbr_stat_to_json(&payload_pos, pp_stat, &free_payload_len);

  for (uint8_t i = 0; i < children_count; ++i) {
    _parse_nbr_stat_to_json(&payload_pos, &children_stats[i], &free_payload_len);
  }

  if ((payload_pos - 2U) >= payload_buff) {
    // Remove last item comma and print JSON end
    snprintf(*(payload_pos - 2U) == ',' ? payload_pos - 2U : payload_pos, free_payload_len, "\n}");
  }

  return payload_buff;
}

static char * _build_ping_meas_stat(const sl_wisun_nwm_remote_ctrl_buf_target_t target,
                                    char * const payload_buff,
                                    sl_wisun_nwm_node_stat_t * const br_stat,
                                    sl_wisun_nwm_node_stat_t * const pp_stat,
                                    sl_wisun_nwm_node_stat_t * const children_stats)
{
  uint8_t children_count = 0U;
  char *payload_pos = payload_buff;
  uint16_t payload_len = SL_WISUN_NWM_REMOTE_CTRL_BUFF_SIZE;
  int32_t r = 0L;

  // Get stats from stat storage
  sl_wisun_nwm_get_border_router_stat(br_stat);
  sl_wisun_nwm_get_primary_parent_stat(pp_stat);
  sl_wisun_nwm_get_children_stat(children_stats, 30U, &children_count);


  // Print JSON start
  r = snprintf(payload_pos, payload_len, "{\n");
  if (r < 0L) {
    return NULL;
  }
  payload_pos += r;

  // Print stats to buffer
  if (target == SL_WISUN_NWM_REMOTE_CTRL_BUF_TARGET_PARENT || target == SL_WISUN_NWM_REMOTE_CTRL_BUF_TARGET_ALL) {
    _parse_stat_to_json(&payload_pos, pp_stat, &payload_len);
  }

  if (target == SL_WISUN_NWM_REMOTE_CTRL_BUF_TARGET_BORDER_ROUTER || target == SL_WISUN_NWM_REMOTE_CTRL_BUF_TARGET_ALL) {
    _parse_stat_to_json(&payload_pos, br_stat, &payload_len);
  }

  if (target == SL_WISUN_NWM_REMOTE_CTRL_BUF_TARGET_SINGLE) {
    _parse_stat_to_json(&payload_pos, &_stat, &payload_len);
  }

  for (uint8_t i = 0; i < children_count; ++i) {
    _parse_stat_to_json(&payload_pos, &children_stats[i], &payload_len);
  }

  if ((payload_pos - 2U) >= payload_buff) {
    // Remove last item comma and print JSON end
    r = snprintf(*(payload_pos - 2U) == ',' ? payload_pos - 2U : payload_pos, payload_len, "\n}");
    if (r < 0L) {
      return NULL;
    }
  }

  return payload_buff;
}

static char * _build_payload(sl_wisun_nwm_remote_ctrl_buf_target_t target)
{
  static sl_wisun_nwm_measurable_node_t nodes[SL_WISUN_MAX_NODE_COUNT];
  static sl_wisun_nwm_node_stat_t children_stats[SL_WISUN_NWM_REMOTE_CTRL_MAX_NB_COUNT];
  static sl_wisun_nwm_node_stat_t br_stat;
  static sl_wisun_nwm_node_stat_t pp_stat;
  static char payload_buff[SL_WISUN_NWM_REMOTE_CTRL_BUFF_SIZE] = { 0U };

  if (target == SL_WISUN_NWM_REMOTE_CTRL_BUF_TARGET_IPERF_JSON || target == SL_WISUN_NWM_REMOTE_CTRL_BUF_TARGET_IPERF_TEXT) {
    return _build_iperf_result(target, payload_buff);
  } else if (target == SL_WISUN_NWM_REMOTE_CTRL_BUF_TARGET_NBINF) {
    return _build_nbr_info(payload_buff, nodes, &br_stat, &pp_stat, children_stats);
  } else {
    return _build_ping_meas_stat(target, payload_buff, &br_stat, &pp_stat, children_stats);
  }
}

static sl_wisun_coap_packet_t *  _build_response(const sl_wisun_coap_packet_t * const req_packet,
                                                    const sl_wisun_nwm_remote_ctrl_buf_target_t target)
{
  static sl_wisun_nwm_remote_ctrl_resp_t resp = { 
    .msg_code = COAP_MSG_CODE_RESPONSE_CONTENT,
    .payload = NULL
  };

  // Build payload from stat.
  resp.payload = _build_payload(target);

  // Build response packet from built payload.
  return _build_response_packet(&resp, req_packet);
}

static sl_wisun_coap_packet_t * _build_response_packet(const sl_wisun_nwm_remote_ctrl_resp_t * const resp,
                                                       const sl_wisun_coap_packet_t * const req_packet)
{
  sl_wisun_coap_packet_t *resp_packet = NULL;

  resp_packet = sl_wisun_coap_build_response(req_packet, resp->msg_code);
  if (resp_packet == NULL) {
    return NULL;
  }
  if (resp->payload != NULL) {
    resp_packet->payload_ptr = (uint8_t *) resp->payload;
    resp_packet->payload_len = (uint16_t) sl_strnlen((char *)resp->payload, SL_WISUN_NWM_REMOTE_CTRL_BUFF_SIZE);
  }
  return resp_packet;
}

static void _parse_stat_to_json(char **payload_pos, 
                                const sl_wisun_nwm_node_stat_t * const stat, 
                                uint16_t * const payload_len)
{
  int32_t r = 0U;
  const char *ip_str = NULL;

  ip_str = app_wisun_trace_util_get_ip_str(&stat->addr.sin6_addr);
  r = snprintf(*payload_pos, *payload_len, SL_WISUN_NWM_REMOTE_CTRL_PING_STAT_JSON_FORMAT,
               stat->name,
               ip_str,
               stat->ping_stat.packet_count,
               stat->ping_stat.packet_length,
               stat->ping_stat.lost,
               stat->ping_stat.min_time_ms,
               stat->ping_stat.max_time_ms,
               stat->ping_stat.avg_time_ms);
  if (r >= 0 && r < *payload_len) {
    *payload_len -= r;
    *payload_pos += r;
  }
  app_wisun_trace_util_destroy_ip_str(ip_str);
}

static void _parse_nbr_stat_to_json(char **payload_pos,
                                    const sl_wisun_nwm_node_stat_t * const stat,
                                    int16_t * const payload_len)
{
  int32_t r  = 0L;
  const char *ip_str = NULL;

  ip_str = app_wisun_trace_util_get_ip_str(&stat->addr.sin6_addr);

  r = snprintf(*payload_pos, *payload_len, SL_WISUN_NWM_REMOTE_CTRL_NBR_STAT_JSON_FORMAT,
               stat->name,
               ip_str,
               stat->stat.lifetime,
               stat->stat.mac_tx_count,
               stat->stat.mac_tx_failed_count,
               stat->stat.mac_tx_ms_count,
               stat->stat.mac_tx_ms_failed_count,
               stat->stat.rpl_rank,
               stat->stat.etx,
               stat->stat.rsl_in,
               stat->stat.rsl_out);

  if (r >= 0 && r < *payload_len) {
    *payload_len -= r;
    *payload_pos += r;
  }
  app_wisun_trace_util_destroy_ip_str(ip_str);
}

/* Statistic printer */
static void _stat_handler(sl_wisun_ping_stat_t *stat)
{
  assert(stat->packet_count != 0);
  memcpy(&_stat.ping_stat, stat, sizeof(sl_wisun_ping_stat_t));
}

static int32_t _log_print_only_buff(sl_iperf_log_t * const log, const char * format, ...)
{
  va_list args;
  int32_t res = -1L;
  size_t free_bytes = 0;

  if (log == NULL) {
    return res;
  }

  va_start(args, format);

  if (log->buffered
      && log->buff.buff != NULL
      && log->buff.size) {
    free_bytes = log->buff.size - (log->buff.pos - log->buff.buff);

    if (free_bytes) {
      res = vsnprintf(log->buff.pos, free_bytes, format, args);
      if (res > 0L) {
        log->buff.pos += res;
      }
    }
  }

  va_end(args);
  return res;
}
