/***************************************************************************//**
 * @file
 * @brief Wi-SUN CoAP resource handler
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

#include <string.h>
#include <assert.h>
#include "sl_string.h"
#include "sl_wisun_types.h"
#include "sl_wisun_coap_rhnd.h"
#include "sli_wisun_coap_mem.h"
#include "sl_wisun_coap.h"
#include "cmsis_os2.h"
#include "sl_cmsis_os2_common.h"
#include "sl_status.h"
#include "sl_mempool.h"
#include "sl_wisun_app_core_util.h"
#include "sli_wisun_coap_rd.h"

#if SL_WISUN_COAP_RESOURCE_HND_SERVICE_ENABLE
#include "socket.h"
#endif

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------
/// Default Resource Discovery port (RFC7252)
#define SL_WISUN_COAP_RESOURCE_DISCOVERY_DEFAULT_PORT   5683U

/// Is separated Resource Discovery Socket required
#define SL_WISUN_COAP_RD_SOCKET_REQUIRED \
  (SL_WISUN_COAP_RESOURCE_HND_SERVICE_PORT != SL_WISUN_COAP_RESOURCE_DISCOVERY_DEFAULT_PORT)

/// Unlock the CoAP resource mutex and return.
#define _coap_resource_mutex_release_and_return_val(__val) \
  do {                                                     \
    _coap_resource_mutex_release();                        \
    return (__val);                                        \
  } while (0)

/// Unlock the CoAP resource mutex and return with check if OS is running.
#define _coap_resource_mutex_check_release_and_return_val(__val) \
  do {                                                           \
    _coap_resource_mutex_check_release();                        \
    return (__val);                                              \
  } while (0)

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief Resource mutex lock and return
 * @return none
 *****************************************************************************/
__STATIC_INLINE void _coap_resource_mutex_check_acquire(void);

/**************************************************************************//**
 * @brief Resouce mutex unlock and return
 * @return none
 *****************************************************************************/
__STATIC_INLINE void _coap_resource_mutex_check_release(void);

/**************************************************************************//**
 * @brief Resource mutex lock
 * @return none
 *****************************************************************************/
__STATIC_INLINE void _coap_resource_mutex_acquire(void);

/**************************************************************************//**
 * @brief Resource mutex unlock
 * @return none
 *****************************************************************************/
__STATIC_INLINE void _coap_resource_mutex_release(void);

/**************************************************************************//**
 * @brief Get resource ptr
 * @details Get resource ptr from storage
 * @param[in] uri_path URI path
 * @return sl_wisun_coap_rhnd_resource_t* Resource ptr, NULL on error
 *****************************************************************************/
static sl_wisun_coap_rhnd_resource_t *  _get_resource(const char * const uri_path);

#if SL_WISUN_COAP_RESOURCE_HND_SERVICE_ENABLE

/**************************************************************************//**
 * @brief Is request packet?
 * @details helper function
 * @param[in] packet Packet
 * @return true Request packet
 * @return false Response or Empty packet
 *****************************************************************************/
__STATIC_INLINE bool _is_request_packet(const sl_wisun_coap_packet_t * const packet);

/**************************************************************************//**
 * @brief Thread function of Resource Handler Service
 * @details Thread function
 * @param[in] args Arguments (not used)
 *****************************************************************************/
static void _rhnd_thr_fnc(void * args);

#endif

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

/// Wi-SUN CoAP Resource Handler mutex attribute
static const osMutexAttr_t _wisun_coap_resource_mtx_attr = {
  .name      = "WisunCoapResourceMutex",
  .attr_bits = osMutexRecursive,
  .cb_mem    = NULL,
  .cb_size   = 0U
};

/// Resource manager mutex
static osMutexId_t _wisun_coap_resource_mtx = NULL;

#if SL_WISUN_COAP_RESOURCE_HND_SERVICE_ENABLE
/// Thread ID
static osThreadId_t _rhnd_thr = NULL;

/// iPerf task attribute
static const osThreadAttr_t _rhnd_thr_attr = {
  .name        = "CoAP-RHND-Service",
  .attr_bits   = osThreadDetached,
  .cb_mem      = NULL,
  .cb_size     = 0U,
  .stack_mem   = NULL,
  .stack_size  = app_stack_size_word_to_byte(SL_WISUN_COAP_RESOURCE_HND_STACK_SIZE_WORD),
  .priority    = osPriorityNormal7,
  .tz_module   = 0U
};
#endif

/// Internal Resource buffer
static sl_wisun_coap_rhnd_resource_t _resource_table[SL_WISUN_COAP_RESOURCE_HND_MAX_RESOURCES] = { 0U };

/// Temporary Resource buffer to store resource list
static sl_wisun_coap_rhnd_resource_t _tmp_resources[SL_WISUN_COAP_RESOURCE_HND_MAX_RESOURCES] = { 0U };

/// Resource storage mempool
static sl_mempool_t _resources = { 0U };

/// Socket communication buffer to receive/send
static uint8_t _rhnd_sock_buff[SL_WISUN_COAP_RESOURCE_HND_SOCK_BUFF_SIZE] = { 0 };

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

void sl_wisun_coap_rhnd_init(void)
{
  sl_status_t stat = SL_STATUS_FAIL;
  // init mutex
  _wisun_coap_resource_mtx = osMutexNew(&_wisun_coap_resource_mtx_attr);
  assert(_wisun_coap_resource_mtx != NULL);

  // create mempool for resources
  stat = sl_mempool_create(&_resources,
                           SL_WISUN_COAP_RESOURCE_HND_MAX_RESOURCES,
                           sizeof(sl_wisun_coap_rhnd_resource_t),
                           _resource_table,
                           sizeof(_resource_table));
  assert(stat == SL_STATUS_OK);

#if SL_WISUN_COAP_RESOURCE_HND_SERVICE_ENABLE
  // init thread
  _rhnd_thr = osThreadNew(_rhnd_thr_fnc, NULL, &_rhnd_thr_attr);
  assert(_rhnd_thr != NULL);
#endif
}

/* Register resource */
sl_status_t sl_wisun_coap_rhnd_resource_add(const sl_wisun_coap_rhnd_resource_t * const src_resource)
{
  sl_wisun_coap_rhnd_resource_t *resource = NULL;
  sl_mempool_block_hnd_t *slot            = _resources.blocks;

  _coap_resource_mutex_check_acquire();

  // Check resource is alredy exist
  while (slot != NULL) {
    resource = (sl_wisun_coap_rhnd_resource_t *)slot->start_addr;
    if (!strncmp(resource->data.uri_path,
                 src_resource->data.uri_path,
                 SL_WISUN_COAP_URI_PATH_MAX_SIZE)) {
      _coap_resource_mutex_check_release_and_return_val(SL_STATUS_FAIL);
    }
    slot = slot->next;
  }

  resource = sl_mempool_alloc(&_resources);

  // resource cannot be allocated
  if (resource == NULL) {
    _coap_resource_mutex_check_release_and_return_val(SL_STATUS_FAIL);
  }

  // Copy resource data
  memcpy(resource, src_resource, sizeof(sl_wisun_coap_rhnd_resource_t));

  _coap_resource_mutex_check_release();
  return SL_STATUS_OK;
}

/* Remove resource by URI path */
sl_status_t sl_wisun_coap_rhnd_resource_remove_by_uri(const char* uri_path)
{
  sl_wisun_coap_rhnd_resource_t *resource = NULL;
  _coap_resource_mutex_acquire();

  resource = _get_resource(uri_path);

  if (resource == NULL) {
    _coap_resource_mutex_release_and_return_val(SL_STATUS_FAIL);
  }

  sl_mempool_free(&_resources, resource);

  _coap_resource_mutex_release();
  return SL_STATUS_OK;
}

const sl_wisun_coap_rhnd_resource_t * sl_wisun_coap_rhnd_get_resources(void)
{
  sl_wisun_coap_rhnd_resource_t *resource = NULL;
  sl_mempool_block_hnd_t *slot            = _resources.blocks;
  size_t cnt                              = 0UL;

  _coap_resource_mutex_check_acquire();

  // reset temporary resource storage
  memset(_tmp_resources, 0U, sizeof(_tmp_resources));

  // Iterate resources
  while (slot != NULL) {
    resource = (sl_wisun_coap_rhnd_resource_t *)slot->start_addr;

    // copy resource to temporary storage
    if (cnt < SL_WISUN_COAP_RESOURCE_HND_MAX_RESOURCES) {
      memcpy(&_tmp_resources[cnt], resource, sizeof(sl_wisun_coap_rhnd_resource_t));
      // link to list;
      if (cnt > 0U) {
        _tmp_resources[cnt - 1].next = &_tmp_resources[cnt];
      }
      ++cnt;
    }

    slot = slot->next;
  }

  _coap_resource_mutex_check_release();

  return !cnt ? NULL : (const sl_wisun_coap_rhnd_resource_t *) _tmp_resources;
}

void sl_wisun_coap_rhnd_print_resources(void)
{
  sl_wisun_coap_rhnd_resource_t *resource = NULL;
  sl_mempool_block_hnd_t *slot            = _resources.blocks;

  _coap_resource_mutex_acquire();

  while (slot != NULL) {
    resource = (sl_wisun_coap_rhnd_resource_t *)slot->start_addr;
    printf("%s\n", resource->data.uri_path);
    slot = slot->next;
  }

  _coap_resource_mutex_release();
}

sl_status_t sl_wisun_coap_rhnd_set_auto_response(const char*  uri_path,
                                                 sl_wisun_coap_rhnd_auto_resp_t response)
{
  sl_wisun_coap_rhnd_resource_t *resource = NULL;

  if (response == NULL) {
    return SL_STATUS_FAIL;
  }

  _coap_resource_mutex_acquire();

  resource = _get_resource(uri_path);

  if (resource == NULL) {
    _coap_resource_mutex_release_and_return_val(SL_STATUS_FAIL);
  }

  resource->auto_response = response;

  _coap_resource_mutex_release();
  return SL_STATUS_OK;
}

sl_status_t sl_wisun_coap_rhnd_reset_auto_response(const char * uri_path)
{
  sl_wisun_coap_rhnd_resource_t *resource = NULL;

  _coap_resource_mutex_acquire();

  resource = _get_resource(uri_path);

  if (resource == NULL) {
    _coap_resource_mutex_release_and_return_val(SL_STATUS_FAIL);
  }

  resource->auto_response = NULL;

  _coap_resource_mutex_release();
  return SL_STATUS_OK;
}

sl_status_t sl_wisun_coap_rhnd_prepare_auto_response(const char * uri_path,
                                                     const sl_wisun_coap_packet_t * const req_packet,
                                                     sl_wisun_coap_packet_t * const resp_packet)
{
  sl_wisun_coap_rhnd_resource_t *resource = NULL;

  _coap_resource_mutex_acquire();

  resource = _get_resource(uri_path);
  if (resource == NULL || resource->auto_response == NULL) {
    _coap_resource_mutex_release_and_return_val(SL_STATUS_FAIL);
  }

  // call auto response function to prepare response
  resource->auto_response(req_packet, resp_packet);

  _coap_resource_mutex_release();

  return SL_STATUS_OK;
}

#if SL_WISUN_COAP_RESOURCE_HND_SERVICE_ENABLE
SL_WEAK void sl_wisun_coap_rhnd_service_resp_received_hnd(sl_wisun_coap_packet_t * req_packet,
                                                          sl_wisun_coap_packet_t * resp_packet)
{
  (void) req_packet;
  (void) resp_packet;
  printf("[CoAP-RHND-Service: Response packet received]\n");
}

SL_WEAK void sl_wisun_coap_rhnd_service_uri_path_error_hnd(sl_wisun_coap_packet_t * req_packet)
{
  (void) req_packet;
  printf("[CoAP-RHND-Service: Error occured in URI path handling]\n");
}

SL_WEAK void sl_wisun_coap_rhnd_service_buff_ovflow_error_hnd(sl_wisun_coap_packet_t * req_packet,
                                                              sl_wisun_coap_packet_t * resp_packet)
{
  (void) req_packet;
  (void) resp_packet;
  printf("[CoAP-RHND-Service: Buffer overflow occured]\n");
}

SL_WEAK void sl_wisun_coap_rhnd_service_packet_build_error_hnd(sl_wisun_coap_packet_t * req_packet,
                                                               sl_wisun_coap_packet_t * resp_packet)
{
  (void) req_packet;
  (void) resp_packet;
  printf("[CoAP-RHND-Service: Response build error occured]\n");
}

SL_WEAK void sl_wisun_coap_rhnd_service_resp_send_error_hnd(sl_wisun_coap_packet_t * req_packet,
                                                            sl_wisun_coap_packet_t * resp_packet)
{
  (void) req_packet;
  (void) resp_packet;
  printf("[CoAP-RHND-Service: Response send error occured]\n");
}
#endif

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------

/* Mutex acquire with check if OS is running */
__STATIC_INLINE void _coap_resource_mutex_check_acquire(void)
{
  if (osKernelGetState() == osKernelRunning) {
    assert(osMutexAcquire(_wisun_coap_resource_mtx, osWaitForever) == osOK);
  }
}

/* Mutex release with check if OS is running */
__STATIC_INLINE void _coap_resource_mutex_check_release(void)
{
  if (osKernelGetState() == osKernelRunning) {
    assert(osMutexRelease(_wisun_coap_resource_mtx) == osOK);
  }
}

/* Mutex acquire */
__STATIC_INLINE void _coap_resource_mutex_acquire(void)
{
  assert(osMutexAcquire(_wisun_coap_resource_mtx, osWaitForever) == osOK);
}

/* Mutex release */
__STATIC_INLINE void _coap_resource_mutex_release(void)
{
  assert(osMutexRelease(_wisun_coap_resource_mtx) == osOK);
}

static sl_wisun_coap_rhnd_resource_t *  _get_resource(const char * const uri_path)
{
  sl_wisun_coap_rhnd_resource_t *resource = NULL;
  sl_mempool_block_hnd_t *slot            = _resources.blocks;

  while (slot != NULL) {
    resource = (sl_wisun_coap_rhnd_resource_t *)slot->start_addr;
    if (!strncmp(uri_path, resource->data.uri_path, SL_WISUN_COAP_URI_PATH_MAX_SIZE)) {
      return resource;
    }
    slot = slot->next;
  }

  return NULL;
}

#if SL_WISUN_COAP_RESOURCE_HND_SERVICE_ENABLE
__STATIC_INLINE bool _is_request_packet(const sl_wisun_coap_packet_t * const packet)
{
  return (bool)(packet->msg_code == COAP_MSG_CODE_REQUEST_GET
                || packet->msg_code == COAP_MSG_CODE_REQUEST_POST
                || packet->msg_code == COAP_MSG_CODE_REQUEST_PUT
                || packet->msg_code == COAP_MSG_CODE_REQUEST_DELETE);
}

static void _rhnd_thr_fnc(void * args)
{
  sl_wisun_coap_packet_t *req_pkt                 = NULL;
  sl_wisun_coap_packet_t *resp_pkt                = NULL;
  const sl_wisun_coap_rhnd_resource_t *resource   = NULL;
  const char *uri_path                            = NULL;
  char *discovery_payload                         = NULL;
  int32_t sockid                                  = SOCKET_INVALID_ID;
  int32_t sockid_active                           = SOCKET_INVALID_ID;
  int32_t r                                       = SOCKET_INVALID_ID;
  socklen_t sock_len                              = 0UL;
  size_t resp_len                                 = 0UL;
  uint16_t discovery_paylod_len                   = 0U;
  static wisun_addr_t srv_addr                    = { 0U };
  static wisun_addr_t clnt_addr                   = { 0U };
#if SL_WISUN_COAP_RD_SOCKET_REQUIRED
  int32_t sockid_rd                               = SOCKET_INVALID_ID;
  static wisun_addr_t srv_addr_rd                 = { 0U };
#endif

// Clean-up code
#define __cleanup_service()                 \
  do {                                      \
    sl_wisun_coap_destroy_packet(req_pkt);  \
    sl_wisun_coap_destroy_packet(resp_pkt); \
    sl_wisun_coap_free(discovery_payload);  \
  } while (0)

  (void) args;

  SL_COAP_SERVICE_LOOP() {
    // wait for network connected state
    if (!app_wisun_network_is_connected()) {
      osDelay(1000UL);
      continue;
    }

    // creating socket
    sockid = socket(AF_WISUN, SOCK_DGRAM, IPPROTO_UDP);
    assert(sockid != SOCKET_INVALID_ID);

    // fill the server address structure
    srv_addr.sin6_family = AF_WISUN;
    srv_addr.sin6_addr = in6addr_any;
    srv_addr.sin6_port = htons(SL_WISUN_COAP_RESOURCE_HND_SERVICE_PORT);

    sock_len = sizeof(wisun_addr_t);

    // bind address to the socket
    r = bind(sockid, (const struct sockaddr *) &srv_addr, sock_len);
    assert(r != SOCKET_RETVAL_ERROR);

#if SL_WISUN_COAP_RD_SOCKET_REQUIRED
    sockid_rd = socket(AF_WISUN, SOCK_DGRAM, IPPROTO_UDP);
    assert(sockid_rd != SOCKET_INVALID_ID);

    srv_addr_rd.sin6_family = AF_WISUN;
    srv_addr_rd.sin6_addr = in6addr_any;
    srv_addr_rd.sin6_port = htons(SL_WISUN_COAP_RESOURCE_DISCOVERY_DEFAULT_PORT);

    // bind address to the socket
    r = bind(sockid_rd, (const struct sockaddr *) &srv_addr_rd, sock_len);
    assert(r != SOCKET_RETVAL_ERROR);

#endif

    // Receiver loop
    while (1) {
      // Dispatch
      osDelay(1UL);

      // Receive UDP packets
      sockid_active = sockid;
      r = recvfrom(sockid_active, _rhnd_sock_buff,
                   SL_WISUN_COAP_RESOURCE_HND_SOCK_BUFF_SIZE, 0L,
                   (struct sockaddr *) &clnt_addr, &sock_len);

#if SL_WISUN_COAP_RD_SOCKET_REQUIRED
      // Check resource discovery socket
      if (r <= 0L) {
        sockid_active = sockid_rd;
        r = recvfrom(sockid_active, _rhnd_sock_buff,
                     SL_WISUN_COAP_RESOURCE_HND_SOCK_BUFF_SIZE, 0L,
                     (struct sockaddr *) &clnt_addr, &sock_len);
      }
#endif

      if (r > 0L) {
        // Parse packet
        req_pkt = sl_wisun_coap_parser((uint16_t) r, _rhnd_sock_buff);

        // Check Packet
        if (req_pkt == NULL) {
          continue;
        }
        printf("[CoAP-RHND-Service: Received packet]\n");
        sl_wisun_coap_print_packet(req_pkt, false);

        // Handling response and empty packets
        if (!_is_request_packet(req_pkt)) {
          sl_wisun_coap_rhnd_service_resp_received_hnd(req_pkt, resp_pkt);
          continue;
        }

        // Handling requests

        // Process the request based on the uri path
        resource = sl_wisun_coap_rhnd_get_resources();
        discovery_payload = sli_wisun_coap_rd_parser(resource, req_pkt, &discovery_paylod_len);
        if (discovery_payload != NULL) {
          // Build response to resource discovery request
          resp_pkt = sli_wisun_coap_rd_build_response(discovery_payload, discovery_paylod_len, req_pkt);

          // Resource request handling
        } else {
          // Prepare URI path string
          uri_path = sl_wisun_coap_get_uri_path_str(req_pkt);
          if (uri_path == NULL) {
            sl_wisun_coap_rhnd_service_uri_path_error_hnd(req_pkt);
            continue;
          }

          // Get resource
          resource = _get_resource((const char *) uri_path);

          // Free URI path string
          sl_wisun_coap_destroy_uri_path_str((char *)uri_path);

          // Check resource and its auto response callback
          if (resource != NULL && resource->auto_response != NULL) {
            // Create auto-response packet
            resp_pkt = sl_wisun_coap_malloc(sizeof(sl_wisun_coap_packet_t));
            if (resp_pkt != NULL) {
              resource->auto_response(req_pkt, resp_pkt);
            }
          } else {
            // Create "Not found" packet
            resp_pkt = sl_wisun_coap_build_response(req_pkt, COAP_MSG_CODE_RESPONSE_NOT_FOUND);
            if (resp_pkt == NULL) {
              __cleanup_service();
              continue;
            }
          }
        }

        // Build response message
        resp_len = sl_wisun_coap_builder_calc_size(resp_pkt);
        if (resp_len > SL_WISUN_COAP_RESOURCE_HND_SOCK_BUFF_SIZE) {
          sl_wisun_coap_rhnd_service_buff_ovflow_error_hnd(req_pkt, resp_pkt);
          __cleanup_service();
          continue;
        }

        if (sl_wisun_coap_builder(_rhnd_sock_buff, resp_pkt) < 0L) {
          sl_wisun_coap_rhnd_service_packet_build_error_hnd(req_pkt, resp_pkt);
          __cleanup_service();
          continue;
        }

        printf("[CoAP-RHND-Service: Response packet]\n");
        sl_wisun_coap_print_packet(resp_pkt, false);

        // Send response
        if (sendto(sockid_active, _rhnd_sock_buff, resp_len, 0L,
                   (const struct sockaddr *) &clnt_addr, sock_len) == SOCKET_RETVAL_ERROR) {
          sl_wisun_coap_rhnd_service_resp_send_error_hnd(req_pkt, resp_pkt);
        }
        // Free packets
        __cleanup_service();

        // Check network connection after a session
      } else if (r == SOCKET_RETVAL_ERROR && !app_wisun_network_is_connected()) {
        close(sockid);
#if SL_WISUN_COAP_RD_SOCKET_REQUIRED
        close(sockid_rd);
#endif
        osDelay(1000UL);

        // Free packets
        __cleanup_service();

        break;
      }
    }
  }
#undef __cleanup_service
}
#endif
