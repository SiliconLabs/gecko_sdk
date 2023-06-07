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

#include "sl_wisun_app_core_util.h"
#include "sl_wisun_trace_util.h"
#include "sl_wisun_network_measurement.h"
#include "sl_wisun_network_measurement_remote_ctrl.h"
#include "sl_iperf.h"
#include "sl_iperf_util.h"
#include "socket.h"
#include "cmsis_os2.h"
#include "sl_cmsis_os2_common.h"
#include "sl_sleeptimer.h"
#include "sl_component_catalog.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

/// Network Measurement Remote Control buffer size
#define SL_WISUN_NWM_REMOTE_CTRL_BUFF_SIZE                     2048UL

/// Remote CLI measurement max query length
#define SL_WISUN_COAP_NWM_REMOTE_CLI_MAX_QUERY_LENGTH          (SL_WISUN_NWM_REMOTE_CTRL_BUFF_SIZE)

/// Remote CLI measurement max string length
#define SL_WISUN_COAP_NWM_REMOTE_CLI_MAX_ARG_STRING_LENGTH     128UL

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

/// Network Measurement Remote Control iperf help string
#define SL_WISUN_NWM_REMOTE_CTRL_IPERF_HELP_STRING \
  "\niPerf Remote Control CLI Help.\n\n\
  Writable options:\n\
    -options.remote_addr\n\
    -options.bandwidth\n\
    -options.duration\n\
    -options.interval\n\
  Example: iperf set options.bandwidth 10000\n\n\
  Start iPerf command: iperf <client|server>\n"

/// Remote CLI measurement print target type
typedef enum buffer_target_type {
  /// Nothing measurement
  BUFFER_TYPE_NONE = -1,
  /// Only Border Router measurement
  BUFFER_TYPE_BORDER_ROUTER,
  /// Only Primary Parent measurement
  BUFFER_TYPE_PARENT,
  /// Measure all of available nodes
  BUFFER_TYPE_ALL,
  /// Measure single node
  BUFFER_TYPE_SINGLE,
  // Measure iPerf
  BUFFER_TYPE_IPERF
} buffer_target_type_t;

// Remote CLI measurement command structure
typedef struct ctrl_cmd_type {
  /// Nothing measurement
  char* identifier;
  /// Argument1 string
  char* arg1;
  /// Argument2 string
  char* arg2;
  /// Argument3 string
  char* arg3;
} ctrl_cmd_type_t;
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
                                sl_wisun_nwm_node_stat_t *stat,
                                int16_t *payload_len);

/**************************************************************************//**
 * @brief Build and send CoAP response packet.
 * @details Build and send CoAP response packet.
 * @param[in] sockid Socket id.
 * @param[in] clnt_addr Client address.
 * @param[in,out] packet CoAP packet.
 * @param[in] target Measurement print target.
 * @return SL_STATUS_OK on success, otherwise an error code.
 *****************************************************************************/
static sl_status_t _build_send_output(const sl_wisun_coap_packet_t * const req_packet,
                                      sl_wisun_coap_packet_t * const resp_packet,
                                      buffer_target_type_t target);

/**************************************************************************//**
 * @brief Build payload for CoAP response packet.
 * @details Build payload for CoAP response packet.
 * @param[in, out] payload_len CoAP packet payload length.
 * @param[in] target Measurement print target.
 * @return SL_STATUS_OK on success, otherwise an error code.
 *****************************************************************************/
static sl_status_t _build_payload(buffer_target_type_t target);

/**************************************************************************//**
 * @brief Send CoAP response packet.
 * @details Send CoAP response packet.
 * @param[in] sockid Socket id.
 * @param[in] clnt_addr Client address.
 * @param[in] payload_len CoAP packet payload length.
 * @param[in,out] _buff CoAP packet.
 * @return SL_STATUS_OK on success, otherwise an error code.
 *****************************************************************************/
static sl_status_t _build_response_packet(char* payload,
                                          const sl_wisun_coap_packet_t * const req_packet,
                                          sl_wisun_coap_packet_t * const resp_packet);

/**************************************************************************//**
 * @brief Network Measurement custom stat handler.
 * @details Catch stat object after measurement and copy to local variable.
 * @param[in] stat Statistic result after a ping measurement.
 *****************************************************************************/
static void _sl_wisun_nwm_remote_ctrl_stat_handler(sl_wisun_ping_stat_t *stat);

/**************************************************************************//**
 * @brief CoAP remote CLI ping request parser.
 * @details Parse incoming request, and build response CoAP packet.
 * @param[in] req_packet Request packet.
 * @param[in,out] resp_packet Response packet.
 * @return SL_STATUS_OK on success, otherwise an error code.
 *****************************************************************************/
static sl_status_t _parse_ping(const sl_wisun_coap_packet_t * const req_packet,
                               sl_wisun_coap_packet_t * const resp_packet);

/**************************************************************************//**
 * @brief CoAP remote CLI iPerf request parser.
 * @details Parse incoming request, and build response CoAP packet.
 * @param[in] req_packet Request packet.
 * @param[in,out] resp_packet Response packet.
 * @return SL_STATUS_OK on success, otherwise an error code.
 *****************************************************************************/
static sl_status_t _parse_iperf(const sl_wisun_coap_packet_t * const req_packet,
                                sl_wisun_coap_packet_t * const resp_packet);

/**************************************************************************//**
 * @brief CLI command splitter.
 * @details Split CLI command string to structure.
 * @param[in] req_cmd Incoming CLI command string.
 * @param[in, out] cmd Command structure.
 *****************************************************************************/
static void _parse_remote_cmd(char* req_cmd,
                              ctrl_cmd_type_t* cmd);

/**************************************************************************//**
 * @brief iPerf server handler.
 * @details Start iPerf server.
 * @param[in] req_packet Request packet.
 * @param[in,out] resp_packet Response packet.
 * @return SL_STATUS_OK on success, otherwise an error code.
 *****************************************************************************/
static sl_status_t _start_iperf_server(const sl_wisun_coap_packet_t * const req_packet,
                                       sl_wisun_coap_packet_t * const resp_packet);

/**************************************************************************//**
 * @brief iPerf client handler.
 * @details Start iPerf client.
 * @param[in] req_packet Request packet.
 * @param[in,out] resp_packet Response packet.
 * @return SL_STATUS_OK on success, otherwise an error code.
 *****************************************************************************/
static sl_status_t _start_iperf_client(const sl_wisun_coap_packet_t * const req_packet,
                                       sl_wisun_coap_packet_t * const resp_packet);

/**************************************************************************//**
 * @brief Neighbour info handler.
 * @details Get Neighbour info.
 * @param[in] req_packet Request packet.
 * @param[in,out] resp_packet Response packet.
 * @return SL_STATUS_OK on success, otherwise an error code.
 *****************************************************************************/
static sl_status_t _get_nbr(const sl_wisun_coap_packet_t * const req_packet,
                            sl_wisun_coap_packet_t * const resp_packet);

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

/// Router storage
static sl_wisun_nwm_measurable_node_t _nodes[SL_WISUN_MAX_NODE_COUNT];

/// Stat childre storage
static sl_wisun_nwm_node_stat_t _children_stats[30U];

/// Stat border router storage
static sl_wisun_nwm_node_stat_t _br_stat;

/// Stat primary parent storage
static sl_wisun_nwm_node_stat_t _pp_stat;

/// Payload buffer
static char _payload_buff[SL_WISUN_NWM_REMOTE_CTRL_BUFF_SIZE] = { 0 };

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

void sl_wisun_coap_remote_cli_ping_cb(const sl_wisun_coap_packet_t * const req_packet,
                                      sl_wisun_coap_packet_t * const resp_packet)
{
  sl_status_t stat = SL_STATUS_FAIL;
  stat = _parse_ping(req_packet, resp_packet);
  printf("[COAP CLI Ping transaction %s]\n", stat == SL_STATUS_OK ? "succeed" : "failed");
}

void sl_wisun_coap_remote_cli_iperf_cb(const sl_wisun_coap_packet_t * const req_packet,
                                       sl_wisun_coap_packet_t * const resp_packet)
{
  sl_status_t stat = SL_STATUS_FAIL;
  stat = _parse_iperf(req_packet, resp_packet);
  printf("[COAP CLI iPerf transaction %s]\n", stat == SL_STATUS_OK ? "succeed" : "failed");
}

void sl_wisun_coap_remote_cli_nbr_cb(const sl_wisun_coap_packet_t * const req_packet,
                                     sl_wisun_coap_packet_t * const resp_packet)
{
  sl_status_t stat = SL_STATUS_FAIL;
  stat = _get_nbr(req_packet, resp_packet);
  printf("[COAP CLI NeighborInfo transaction %s]\n", stat == SL_STATUS_OK ? "succeed" : "failed");
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------

static sl_status_t _get_nbr(const sl_wisun_coap_packet_t * const req_packet,
                            sl_wisun_coap_packet_t * const resp_packet)
{
  int16_t free_payload_len  = SL_WISUN_NWM_REMOTE_CTRL_BUFF_SIZE;
  uint8_t children_count    = 0U;
  char *payload_pos         = NULL;
  sl_status_t stat          = SL_STATUS_FAIL;

  payload_pos = _payload_buff;

  // get count of neighbors
  (void) sl_wisun_nwm_get_nodes(_nodes, SL_WISUN_MAX_NODE_COUNT);

  sl_wisun_nwm_get_border_router_stat(&_br_stat);
  sl_wisun_nwm_get_primary_parent_stat(&_pp_stat);
  sl_wisun_nwm_get_children_stat(_children_stats, 30U, &children_count);

  payload_pos += snprintf(payload_pos, free_payload_len, "{\n");
  --free_payload_len;
  _parse_nbr_stat_to_json(&payload_pos, &_br_stat, &free_payload_len);
  _parse_nbr_stat_to_json(&payload_pos, &_pp_stat, &free_payload_len);

  for (uint8_t i = 0; i < children_count; ++i) {
    _parse_nbr_stat_to_json(&payload_pos, &_children_stats[i], &free_payload_len);
  }

  if ((payload_pos - 2U) >= _payload_buff) {
    // Remove last item comma and print JSON end
    snprintf(*(payload_pos - 2U) == ',' ? payload_pos - 2U : payload_pos, free_payload_len, "\n}");
  }

  stat = _build_response_packet(_payload_buff, req_packet, resp_packet);
  return stat;
}

static sl_status_t _parse_ping(const sl_wisun_coap_packet_t * const req_packet,
                               sl_wisun_coap_packet_t * const resp_packet)
{
  ctrl_cmd_type_t ping_cmd               = { 0U };
  wisun_addr_t remote_addr               = { 0U };
  uint16_t packet_count                  = 0U;
  uint16_t packet_size                   = 0U;
  char* req_payload                      = NULL;
  buffer_target_type_t print_target      = BUFFER_TYPE_NONE;
  sl_status_t res                        = SL_STATUS_FAIL;

  // Parsing incoming cli command string.
  req_payload = sl_wisun_coap_get_payload_str(req_packet);
  if (req_payload == NULL) {
    _build_response_packet("No CoAP payload: -e \"<cli command>\"", req_packet, resp_packet);
    return SL_STATUS_FAIL;
  }
  _parse_remote_cmd(req_payload, &ping_cmd);

  if (ping_cmd.identifier == NULL || ping_cmd.arg1 == NULL) {
    _build_response_packet("Not enough argument", req_packet, resp_packet);
    sl_wisun_coap_destroy_payload_str(req_payload);
    return SL_STATUS_FAIL;
  }

  // Handle help request.
  if (!strncmp(ping_cmd.arg1, "help", SL_WISUN_COAP_NWM_REMOTE_CLI_MAX_ARG_STRING_LENGTH)) {
    _build_response_packet("Ping CLI help: measure <packet_count> <packet_size> <address>", req_packet, resp_packet);
    sl_wisun_coap_destroy_payload_str(req_payload);
    return SL_STATUS_OK;
  }

  if (ping_cmd.arg2 == NULL) {
    sl_wisun_coap_destroy_payload_str(req_payload);
    _build_response_packet("Not enough argument", req_packet, resp_packet);
    return SL_STATUS_FAIL;
  }
  packet_count = atoi(ping_cmd.arg1);
  packet_size = atoi(ping_cmd.arg2);

  // Handle measurement request based on address.
  if (ping_cmd.arg3 != NULL && !strncmp(ping_cmd.arg3, "all", SL_WISUN_COAP_NWM_REMOTE_CLI_MAX_ARG_STRING_LENGTH)) {
    sl_wisun_nwm_quick_measure(SL_WISUN_NWM_TARGET_TYPE_ALL, packet_count, packet_size);
    print_target = BUFFER_TYPE_ALL;
  } else if (ping_cmd.arg3 != NULL && !strncmp(ping_cmd.arg3, "parent", SL_WISUN_COAP_NWM_REMOTE_CLI_MAX_ARG_STRING_LENGTH)) {
    sl_wisun_nwm_quick_measure(SL_WISUN_NWM_TARGET_TYPE_PARENT, packet_count, packet_size);
    print_target = BUFFER_TYPE_PARENT;
  } else if (ping_cmd.arg3 != NULL && !strncmp(ping_cmd.arg3, "br", SL_WISUN_COAP_NWM_REMOTE_CLI_MAX_ARG_STRING_LENGTH)) {
    sl_wisun_nwm_quick_measure(SL_WISUN_NWM_TARGET_TYPE_BORDER_ROUTER, packet_count, packet_size);
    print_target = BUFFER_TYPE_BORDER_ROUTER;
  } else {
    if (ping_cmd.arg3 != NULL && inet_pton(AF_WISUN, ping_cmd.arg3, &remote_addr.sin6_addr) == SOCKET_RETVAL_ERROR) {
      _build_response_packet("[IP address is not set or not valid]", req_packet, resp_packet);
      sl_wisun_coap_destroy_payload_str(req_payload);
      return SL_STATUS_FAIL;
    }
    (void)sl_wisun_ping(&remote_addr, packet_count, packet_size,
                        _sl_wisun_nwm_remote_ctrl_stat_handler, NULL);
    _stat.name = "Custom Node";
    _stat.addr = remote_addr;
    print_target = BUFFER_TYPE_SINGLE;
  }

  // Build response packet.
  res = _build_send_output(req_packet, resp_packet, print_target);
  if (res != SL_STATUS_OK) {
    _build_response_packet("[Buffer error]", req_packet, resp_packet);
  }

  // Clean memory.
  sl_wisun_coap_destroy_payload_str(req_payload);
  return SL_STATUS_OK;
}

static sl_status_t _parse_iperf(const sl_wisun_coap_packet_t * const req_packet,
                                sl_wisun_coap_packet_t * const resp_packet)
{
  ctrl_cmd_type_t iperf_cmd = { 0U };
  char* req_payload         = NULL;
  sl_status_t res           = SL_STATUS_FAIL;

  // Parsing incoming cli command string.
  req_payload = sl_wisun_coap_get_payload_str(req_packet);
  if (req_payload == NULL) {
    _build_response_packet("No CoAP payload: -e \"<cli command>\"", req_packet, resp_packet);
    return SL_STATUS_FAIL;
  }

  _parse_remote_cmd(req_payload, &iperf_cmd);

  if (iperf_cmd.identifier == NULL || iperf_cmd.arg1 == NULL) {
    _build_response_packet("Not enough argument", req_packet, resp_packet);
    sl_wisun_coap_destroy_payload_str(req_payload);
    return SL_STATUS_FAIL;
  }

  // Handle help request.
  if (!strncmp(iperf_cmd.arg1, "help", SL_WISUN_COAP_NWM_REMOTE_CLI_MAX_ARG_STRING_LENGTH)) {
    res = _build_response_packet(SL_WISUN_NWM_REMOTE_CTRL_IPERF_HELP_STRING, req_packet, resp_packet);
    sl_wisun_coap_destroy_payload_str(req_payload);
    return res;
  }

  // Handle server or client start requests.
  if (!strncmp(iperf_cmd.arg1, "server", SL_WISUN_COAP_NWM_REMOTE_CLI_MAX_ARG_STRING_LENGTH)) {
    res = _start_iperf_server(req_packet, resp_packet);
    sl_wisun_coap_destroy_payload_str(req_payload);
    return res;
  }

  if (!strncmp(iperf_cmd.arg1, "client", SL_WISUN_COAP_NWM_REMOTE_CLI_MAX_ARG_STRING_LENGTH)) {
    res = _start_iperf_client(req_packet, resp_packet);
    sl_wisun_coap_destroy_payload_str(req_payload);
    return res;
  }

  if (iperf_cmd.arg2 == NULL) {
    _build_response_packet("Not enough argument", req_packet, resp_packet);
    sl_wisun_coap_destroy_payload_str(req_payload);
    return res;
  }

  // Handle get requests.
  if (!strncmp(iperf_cmd.arg1, "get", SL_WISUN_COAP_NWM_REMOTE_CLI_MAX_ARG_STRING_LENGTH)) {
    if (!strncmp(iperf_cmd.arg2, "result", SL_WISUN_COAP_NWM_REMOTE_CLI_MAX_ARG_STRING_LENGTH)) {
      sl_iperf_test_get(&_last_test);
      res = _build_send_output(req_packet, resp_packet, BUFFER_TYPE_IPERF);
      if (res != SL_STATUS_OK) {
        _build_response_packet("[Buffer error]", req_packet, resp_packet);
      }
    } else {
      res = _build_response_packet("Not found argument.", req_packet, resp_packet);
    }

    // Clean memory
    sl_wisun_coap_destroy_payload_str(req_payload);
    return res;
  }

  if (iperf_cmd.arg3 == NULL) {
    _build_response_packet("Not enough argument", req_packet, resp_packet);
    sl_wisun_coap_destroy_payload_str(req_payload);
    return res;
  }

  // Handle settings requests.
  if (!strncmp(iperf_cmd.arg1, "set", SL_WISUN_COAP_NWM_REMOTE_CLI_MAX_ARG_STRING_LENGTH)) {
    if (!strncmp(iperf_cmd.arg2, "options.bandwidth", SL_WISUN_COAP_NWM_REMOTE_CLI_MAX_ARG_STRING_LENGTH)) {
      _options.bandwidth = atoi(iperf_cmd.arg3);
      res = _build_response_packet(iperf_cmd.arg3, req_packet, resp_packet);
    } else if (!strncmp(iperf_cmd.arg2, "options.remote_addr", SL_WISUN_COAP_NWM_REMOTE_CLI_MAX_ARG_STRING_LENGTH)) {
      memcpy(_options.remote_addr, iperf_cmd.arg3, sl_strnlen(iperf_cmd.arg3, SL_WISUN_COAP_NWM_REMOTE_CLI_MAX_QUERY_LENGTH));
      res = _build_response_packet(iperf_cmd.arg3, req_packet, resp_packet);
    } else if (!strncmp(iperf_cmd.arg2, "options.duration", SL_WISUN_COAP_NWM_REMOTE_CLI_MAX_ARG_STRING_LENGTH)) {
      _options.duration_ms = atoi(iperf_cmd.arg3);
      res = _build_response_packet(iperf_cmd.arg3, req_packet, resp_packet);
    } else if (!strncmp(iperf_cmd.arg2, "options.interval", SL_WISUN_COAP_NWM_REMOTE_CLI_MAX_ARG_STRING_LENGTH)) {
      _options.interval_ms = atoi(iperf_cmd.arg3);
      res = _build_response_packet(iperf_cmd.arg3, req_packet, resp_packet);
    } else {
      res = _build_response_packet("Not found argument.", req_packet, resp_packet);
    }
  } else {
    _build_response_packet("Unknown cli command", req_packet, resp_packet);
  }

  // Clean memory
  sl_wisun_coap_destroy_payload_str(req_payload);
  return res;
}

static sl_status_t _start_iperf_server(const sl_wisun_coap_packet_t * const req_packet,
                                       sl_wisun_coap_packet_t * const resp_packet)
{
  sl_iperf_test_t test = { 0U };

  // Set iPerf server options and init test descriptor.
  _options.mode = SL_IPERF_MODE_SERVER;
  _options.protocol = SL_IPERF_IPROTOV6_UDP;
  sl_iperf_test_init(&test, SL_IPERF_MODE_SERVER, SL_IPERF_IPROTOV6_UDP);
  memcpy(&test.opt, &_options, sizeof(sl_iperf_opt_t));

  // Adds the test to the queue
  if (!sl_iperf_test_add(&test)) {
    printf("[Adding test to queue failed]\n");
    return SL_STATUS_FAIL;
  }

  // Build response packet.
  _build_response_packet("[iPerf server started]", req_packet, resp_packet);

  return SL_STATUS_OK;
}

static sl_status_t _start_iperf_client(const sl_wisun_coap_packet_t * const req_packet,
                                       sl_wisun_coap_packet_t * const resp_packet)
{
  sl_iperf_test_t test = { 0U };
  sl_status_t res = SL_STATUS_FAIL;

  /// 1. Set iPerf client options and init test descriptor.
  _options.mode = SL_IPERF_MODE_CLIENT;
  _options.protocol = SL_IPERF_IPROTOV6_UDP;
  sl_iperf_test_init(&test, SL_IPERF_MODE_CLIENT, SL_IPERF_IPROTOV6_UDP);
  memcpy(&test.opt, &_options, sizeof(sl_iperf_opt_t));

  // Adds the test to the queue.
  if (!sl_iperf_test_add(&test)) {
    printf("[Adding test to queue failed]\n");
    return SL_STATUS_FAIL;
  }

  if (!sl_iperf_test_get(&_last_test)) {
    printf("[Getting test to queue failed]\n");
    return SL_STATUS_FAIL;
  }

  // Build response packet.
  res = _build_send_output(req_packet, resp_packet, BUFFER_TYPE_IPERF);
  if (res != SL_STATUS_OK) {
    _build_response_packet("[Buffer error]", req_packet, resp_packet);
  }

  return SL_STATUS_OK;
}

static void _parse_remote_cmd(char* req_cmd, ctrl_cmd_type_t* cmd)
{
  cmd->identifier = strtok(req_cmd, " ");
  cmd->arg1 = strtok(NULL, " ");
  cmd->arg2 = strtok(NULL, " ");
  cmd->arg3 = strtok(NULL, " ");
}

static sl_status_t _build_payload(buffer_target_type_t target)
{
  uint8_t children_count = 0U;
  char *payload_pos = _payload_buff;
  int16_t payload_len    = SL_WISUN_NWM_REMOTE_CTRL_BUFF_SIZE; // payload length
  int32_t r = 0L;

  // Get stats from stat storage
  sl_wisun_nwm_get_border_router_stat(&_br_stat);
  sl_wisun_nwm_get_primary_parent_stat(&_pp_stat);
  sl_wisun_nwm_get_children_stat(_children_stats, 30U, &children_count);

  if (target == BUFFER_TYPE_IPERF) {
    sl_iperf_log_set_buff(_last_test.log, _payload_buff, payload_len);
    sl_iperf_print_test_log_json(&_last_test);
    return SL_STATUS_OK;
  }

  // Print JSON start
  r = snprintf(payload_pos, payload_len, "{\n");
  if (r < 0L) {
    return SL_STATUS_FAIL;
  }
  payload_pos += r;

  // Print stats to buffer
  if (target == BUFFER_TYPE_PARENT || target == BUFFER_TYPE_ALL) {
    _parse_stat_to_json(&payload_pos, &_pp_stat, &payload_len);
  }

  if (target == BUFFER_TYPE_BORDER_ROUTER || target == BUFFER_TYPE_ALL) {
    _parse_stat_to_json(&payload_pos, &_br_stat, &payload_len);
  }

  if (target == BUFFER_TYPE_SINGLE) {
    _parse_stat_to_json(&payload_pos, &_stat, &payload_len);
  }

  for (uint8_t i = 0; i < children_count; ++i) {
    _parse_stat_to_json(&payload_pos, &_children_stats[i], &payload_len);
  }

  if ((payload_pos - 2U) >= _payload_buff) {
    // Remove last item comma and print JSON end
    r = snprintf(*(payload_pos - 2U) == ',' ? payload_pos - 2U : payload_pos, payload_len, "\n}");
    if (r < 0L) {
      return SL_STATUS_FAIL;
    }
  }

  return SL_STATUS_OK;
}

static sl_status_t _build_send_output(const sl_wisun_coap_packet_t * const req_packet, sl_wisun_coap_packet_t * const resp_packet, buffer_target_type_t target)
{
  sl_status_t retval = SL_STATUS_FAIL; // assume success of operation

  // Build payload from stat.
  retval = _build_payload(target);

  if (retval != SL_STATUS_OK) {
    return retval;
  }

  // Build response packet from built payload.
  retval = _build_response_packet(_payload_buff, req_packet, resp_packet);

  return retval;
}

static sl_status_t _build_response_packet(char* payload,
                                          const sl_wisun_coap_packet_t * const req_packet,
                                          sl_wisun_coap_packet_t * const resp_packet)
{
  sl_wisun_coap_packet_t *tmp = NULL;

  tmp = sl_wisun_coap_build_response(req_packet, COAP_MSG_CODE_RESPONSE_CONTENT);
  if (tmp == NULL) {
    return SL_STATUS_FAIL;
  }
  memcpy(resp_packet, tmp, sizeof(sl_wisun_coap_packet_t));
  sl_wisun_coap_destroy_packet(tmp);

  resp_packet->msg_code       = COAP_MSG_CODE_RESPONSE_CONTENT;
  resp_packet->content_format = COAP_CT_JSON;
  resp_packet->payload_ptr    = (uint8_t *) payload;
  resp_packet->payload_len    = (uint16_t) sl_strnlen(payload, SL_WISUN_NWM_REMOTE_CTRL_BUFF_SIZE);

  return SL_STATUS_OK;
}

static void _parse_stat_to_json(char **payload_pos, sl_wisun_nwm_node_stat_t *stat, int16_t *payload_len)
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
static void _sl_wisun_nwm_remote_ctrl_stat_handler(sl_wisun_ping_stat_t *stat)
{
  assert(stat->packet_count != 0);
  memcpy(&_stat.ping_stat, stat, sizeof(sl_wisun_ping_stat_t));
}
