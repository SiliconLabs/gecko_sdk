/***************************************************************************//**
 * @file
 * @brief Socket Handler
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

#include <string.h>
#include "sli_socket_hnd.h"
#include "sl_malloc.h"
#include "em_common.h"
#include "cmsis_os2.h"
#include "sl_mempool.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

/// Using static buffer or not
#define SOCKET_HND_USE_STATIC_BUFFER                                  1U

/// Size of the sockaddress storage general container
#define SOCKADDR_STORAGE_SIZE                                         28U

/// Socket domain is not set indicator
#define SOCKET_DOMAIN_NOT_SET                                         0UL

/// Socket handler status error mask
#define SOCKET_HND_STATUS_EVT_ERROR_MSK                               (1UL << 31UL)

/// Unlock and set errno internal macro function
#define __unlock_set_errno_ret_error(__errno_val__) \
  do {                                              \
    _unlock();                                      \
    sli_socket_hnd_set_errno(__errno_val__);        \
    return SLI_SOCKET_HND_RETVAL_ERROR;             \
  } while (0)

/// Set fifo ptr to default macro function
#define _set_fifo_ptr_to_default(hnd_ptr)                            \
  do {                                                               \
    hnd_ptr->fifo._head = hnd_ptr->fifo._tail = hnd_ptr->fifo._buff; \
  } while (0)

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief Allocate remote address
 * @details Helper function
 * @return NULL on error, otherwise pointer of allocated memory
 *****************************************************************************/
__STATIC_INLINE uint8_t *_alloc_remote_addr(void);

/**************************************************************************//**
 * @brief Allocate socket buffer
 * @details Helper function
 * @return NULL on error, otherwise pointer of allocated memory
 *****************************************************************************/
__STATIC_INLINE uint8_t *_alloc_socket_buff(void);

/**************************************************************************//**
 * @brief Free remote address
 * @details Helper function
 * @param[in] addr Address of memory
 *****************************************************************************/
__STATIC_INLINE void _free_remote_addr(const void * const addr);

/**************************************************************************//**
 * @brief Free socket buffer
 * @details Helper function
 * @param[in] addr Address of memory
 *****************************************************************************/
__STATIC_INLINE void _free_socket_buff(const void * const addr);

/**************************************************************************//**
 * @brief Set socket handler state
 * @details Helper function
 * @param[in,out] socket_hnd Socket handler
 * @param[in] state State
 *****************************************************************************/
__STATIC_INLINE void _set_state(sli_socket_hnd_t *socket_hnd,
                                const sli_socket_hnd_state_id_t state);

/**************************************************************************//**
 * @brief Clear socket handler state
 * @details Helper function
 * @param[in,out] socket_hnd Socket handler
 * @param[in] state State
 *****************************************************************************/
__STATIC_INLINE void _clear_state(sli_socket_hnd_t *socket_hnd,
                                  const sli_socket_hnd_state_id_t state);

/**************************************************************************//**
 * @brief Destroy socket handler
 * @details Set socket handler ptr to NULL and reset content
 * @param[in,out] socket_hnd socket handler ptr
 *****************************************************************************/
static void _destroy_socket_hnd(sli_socket_hnd_t *socket_hnd);

/**************************************************************************//**
 * @brief Mutex lock
 * @details Lock socket handler mutex
 * @param[in,out] socket_hnd socket handler ptr
 *****************************************************************************/
__STATIC_INLINE void _lock(void);

/**************************************************************************//**
 * @brief Mutex unlock
 * @details Release socket handler mutex
 * @param[in,out] socket_hnd socket handler ptr
 *****************************************************************************/
__STATIC_INLINE void _unlock(void);

/**************************************************************************//**
 * @brief Init fifo (internal)
 * @details Internal fifo init to set fifo ptrs and flag to default
 * @param[in,out] hnd socket handler
 * @param[in] buff_ptr buff ptr
 * @param[in] size size of the fifo
 *****************************************************************************/
static void _init_fifo(sli_socket_hnd_t *hnd, uint8_t *buff_ptr, const uint32_t size);

/**************************************************************************//**
 * @brief Reset fifo buffer pointers and flags
 * @param[in,out] hnd socket handler
 *****************************************************************************/
static void _reset_fifo(sli_socket_hnd_t *hnd);

/**************************************************************************//**
 * @brief Set socket storage
 * @details static function to set handler structure pointer
 * @param[in] idx index of storage
 * @param[in] domain domain, eg. AF_WISUN
 * @param[in] socket_id socket id
 * @param[in] socket_addr_struct socket address structure pointer
 * @param[in] socket_addr_len length of socket address structure
 *****************************************************************************/
static void _set_socket_storage(const uint8_t idx,
                                const uint16_t domain,
                                const int32_t socket_id,
                                void *socket_addr_struct,
                                const uint8_t socket_addr_len);

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

/// Socket storage background container
static sli_socket_hnd_t _socket_storage[SL_SOCKET_MAX_SOCKET_COUNT] = { 0 };

/// Socket storage pointer array
static sli_socket_hnd_t *_sockets[SL_SOCKET_MAX_SOCKET_COUNT] = { NULL };

#if SOCKET_HND_USE_STATIC_BUFFER
/// Allocate a common socket buffer if malloc not prefered
static uint8_t _buff[SL_SOCKET_MAX_SOCKET_COUNT * SL_SOCKET_BUFFER_SIZE] = { 0 };

/// Static memory pool for socket buffer
static sl_mempool_t _buff_mpool = { 0U };

/// Allocate a common buffer for storing the current remote address
static uint8_t _remote_addr_storage[SL_SOCKET_MAX_SOCKET_COUNT * SOCKADDR_STORAGE_SIZE] = { 0 };

/// Static memory pool for remote address storage
static sl_mempool_t _remote_addr_mpool = { 0U };
#endif

/// Socket counter
static uint8_t _cnt = 0;

/// Socket handler mutex
static osMutexId_t _socket_hnd_mtx = NULL;

/// Socket handler mutex attributes
static const osMutexAttr_t  _socket_hnd_mtx_attr = {
  .name      = "SocketHndMutex",
  .attr_bits = osMutexRecursive,
  .cb_mem    = NULL,
  .cb_size   = 0
};

/// Socket status event flags attributes
static const osEventFlagsAttr_t _socket_hnd_evt_attr = {
  .name      = "SocketHndEvt",
  .attr_bits = 0,
  .cb_mem    = NULL,
  .cb_size   = 0
};

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

/* socket handler fifo init */
void sli_socket_hnd_fifo_init(sli_socket_hnd_t *hnd, uint8_t *buff_ptr, const uint32_t size)
{
  if (hnd == NULL) {
    return;
  }
  _lock();
  _init_fifo(hnd, buff_ptr, size);
  _unlock();
}

/* socket handler fifo reset */
void sli_socket_hnd_fifo_reset(sli_socket_hnd_t *hnd)
{
  if (hnd == NULL) {
    return;
  }
  _lock();
  _reset_fifo(hnd);
  _unlock();
}

/* socket handler fifo write */
int32_t sli_socket_hnd_fifo_write(sli_socket_hnd_t *hnd, const uint8_t *data, uint32_t * const size)
{
  int32_t retval = SLI_SOCKET_HND_RETVAL_OK;
  uint32_t usedspace = 0;
  if (hnd == NULL) {
    return SLI_SOCKET_HND_RETVAL_ERROR;
  }

  _lock();

  // Reset fifo befor write if overwrite options is enabled
  if (hnd->fifo._enable_overwrite) {
    _reset_fifo(hnd);
  }

  usedspace = hnd->fifo._head - hnd->fifo._buff;

  if (usedspace + *size > hnd->fifo._size) {
    retval = SLI_SOCKET_HND_RETVAL_ERROR; // overflow
    _set_state(hnd, SOCKET_FIFO_OVERFLOW);
    *size = hnd->fifo._size - usedspace;
  }

  if (*size) {
    memcpy(hnd->fifo._head, data, *size);
    hnd->fifo._head += *size;
  }

  _unlock();
  return retval;
}

/* Socket handler fifo read */
int32_t sli_socket_hnd_fifo_read(sli_socket_hnd_t *hnd, uint8_t *data, uint32_t *size)
{
  int32_t retval = SLI_SOCKET_HND_RETVAL_OK;
  uint32_t available = 0;

  if (hnd == NULL) {
    return SLI_SOCKET_HND_RETVAL_ERROR;
  }

  _lock();

  available = hnd->fifo._head - hnd->fifo._tail; // calculate available data
  if (available < *size) {
    retval = SLI_SOCKET_HND_RETVAL_ERROR; // underflow
    _set_state(hnd, SOCKET_FIFO_UNDERFLOW);
    *size = available; // trim size
  }

  if (*size) {
    memcpy(data, hnd->fifo._tail, *size);
    hnd->fifo._tail += *size;
  }

  // if head is at tail (fifo empty),
  // set pointers to default to increse possible write size to the max
  if (hnd->fifo._head == hnd->fifo._tail) {
    _set_fifo_ptr_to_default(hnd);
  }
  _unlock();

  return retval;
}

int32_t sli_socket_hnd_fifo_set_overwrite(sli_socket_hnd_t *hnd, const bool enabled)
{
  if (hnd == NULL) {
    return SLI_SOCKET_HND_RETVAL_ERROR;
  }

  _lock();
  hnd->fifo._enable_overwrite = enabled;
  _unlock();

  return SLI_SOCKET_HND_RETVAL_OK;
}

int32_t sli_socket_hnd_fifo_get_overwrite(const sli_socket_hnd_t *hnd, bool * const dest_val)
{
  if (hnd == NULL) {
    return SLI_SOCKET_HND_RETVAL_ERROR;
  }

  _lock();
  *dest_val = hnd->fifo._enable_overwrite;
  _unlock();

  return SLI_SOCKET_HND_RETVAL_OK;
}

/* Init socket handler */
void sli_socket_hnd_init(void)
{
  osKernelState_t kernel_state = osKernelLocked;

  // get kernel status to avoid mutex assert failure
  kernel_state = osKernelGetState();

#if SOCKET_HND_USE_STATIC_BUFFER
  // Initialize socket buffer storage
  assert(sl_mempool_create(&_buff_mpool,
                           SL_SOCKET_MAX_SOCKET_COUNT,
                           SL_SOCKET_BUFFER_SIZE,
                           _buff,
                           sizeof(_buff)) == SL_STATUS_OK);

  // Initialize remote address mempool
  assert(sl_mempool_create(&_remote_addr_mpool,
                           SL_SOCKET_MAX_SOCKET_COUNT,
                           SOCKADDR_STORAGE_SIZE,
                           _remote_addr_storage,
                           sizeof(_remote_addr_storage)) == SL_STATUS_OK);
#endif
  // Create socket handler mutex
  _socket_hnd_mtx = osMutexNew(&_socket_hnd_mtx_attr);
  assert(_socket_hnd_mtx);
  if (kernel_state == osKernelRunning) {
    _lock(); // lock socket handler
  }

  for (uint8_t i = 0; i < SL_SOCKET_MAX_SOCKET_COUNT; ++i) {
    // reset content
    _destroy_socket_hnd(&_socket_storage[i]);
    // pointer set to NULL to indicate free slot
    _sockets[i] = NULL;
  }
  // reset counter
  _cnt = 0;

  if (kernel_state == osKernelRunning) {
    _unlock(); // unlock socket handler
  }
}

/* Add socket handler */
int32_t sli_socket_hnd_add(const uint16_t domain,
                           const int32_t socket_id,
                           void *socket_addr_struct,
                           const uint8_t socket_addr_len)
{
  int32_t retval = SLI_SOCKET_HND_RETVAL_ERROR;
  int16_t first_free_idx = -1;

  if (socket_id < 0) { // socket handler can be higher than zero
    return retval;
  }

  _lock(); // lock socket handler

  for (int16_t i = SL_SOCKET_MAX_SOCKET_COUNT - 1; i >= 0; --i) {
    if (_sockets[i] == NULL) { // find the first free slot
      first_free_idx = i;
    } else if (_sockets[i]->socket_id == socket_id) { // check socket id is already exist in the storage
      __unlock_set_errno_ret_error(EINVAL);
    }
  }
  if (first_free_idx == -1) {
    __unlock_set_errno_ret_error(EINVAL); // no free slot found
  }
  _set_socket_storage((uint8_t) first_free_idx, domain, socket_id, socket_addr_struct, socket_addr_len);

  ++_cnt;
  retval = _cnt;

  _unlock(); // unlock socket handler

  return retval;
}

/* Get socket handler pointer */
sli_socket_hnd_t *sli_socket_hnd_get(const int32_t socket_id)
{
  sli_socket_hnd_t *retval = NULL;
  _lock(); // lock socket handler

  for (uint8_t i = 0; i < SL_SOCKET_MAX_SOCKET_COUNT; ++i) {
    if (_sockets[i] == NULL) {
      continue;
    }

    if (_sockets[i]->socket_id == socket_id) {
      retval =  _sockets[i];
      break;
    }
  }

  _unlock(); // unlock socket handler

  return retval;
}

/* Remove socket handler */
int32_t sli_socket_hnd_remove(const int32_t socket_id)
{
  int32_t retval = SLI_SOCKET_HND_RETVAL_ERROR;

  _lock(); // lock socket handler

  for (uint8_t i = 0; i < SL_SOCKET_MAX_SOCKET_COUNT; ++i) {
    if (_sockets[i] == NULL) {
      continue;
    }

    if (_sockets[i]->socket_id == socket_id) {
      _destroy_socket_hnd(_sockets[i]); /*Clear storage element*/
      _sockets[i] = NULL; /*Set pointer to NULL as 'free'*/
      --_cnt;
      retval = _cnt;
      break;
    }
  }

  _unlock(); // unlock socket handler

  return retval;
}

/* get count of sockets in handler */
uint8_t sli_socket_hnd_get_cnt(void)
{
  uint8_t retval = 0;

  _lock(); // lock socket handler
  retval = _cnt;
  _unlock(); //unlock socket handler

  return retval;
}

/* set socket handler state */
void sli_socket_hnd_set_state(sli_socket_hnd_t *handler, const sli_socket_hnd_state_id_t state_id, bool value)
{
  if (value) {
    _set_state(handler, state_id);
  } else {
    _clear_state(handler, state_id);
  }
}

/* get socket state */
void sli_socket_hnd_get_state(const sli_socket_hnd_t *handler, const sli_socket_hnd_state_id_t state_id, bool *dest_value)
{
  uint32_t flags = 0UL;
  flags = osEventFlagsGet(handler->state);

  // error
  if (flags & SOCKET_HND_STATUS_EVT_ERROR_MSK) {
    *dest_value = false;
  } else {
    *dest_value = (bool) (flags & (1 << state_id));
  }
}

bool sli_socket_hnd_is_remote_addr_stored(const sli_socket_hnd_t * const handler)
{
  bool res = false;
  _lock();
  res = (bool)(handler->remote_addr != NULL);
  _unlock();
  return res;
}

int32_t sli_socket_hnd_write_remote_addr(sli_socket_hnd_t *hnd, const void *data, const uint8_t size, const uint8_t offset)
{
  if (hnd == NULL || data == NULL || ((size + offset) > SOCKADDR_STORAGE_SIZE)) {
    return SLI_SOCKET_HND_RETVAL_ERROR;
  }

  _lock(); // lock
  if (hnd->remote_addr == NULL) {
    hnd->remote_addr = _alloc_remote_addr();
    if (hnd->remote_addr == NULL) {
      _unlock();
      return SLI_SOCKET_HND_RETVAL_ERROR;
    }
  }

  memcpy(hnd->remote_addr + offset, data, size);
  _unlock(); // lock
  return SLI_SOCKET_HND_RETVAL_OK;
}

int32_t sli_socket_hnd_read_remote_addr(const sli_socket_hnd_t *hnd, void *data, const uint8_t size, const uint8_t offset)
{
  if (hnd == NULL || data == NULL || ((size + offset) > SOCKADDR_STORAGE_SIZE)) {
    return SLI_SOCKET_HND_RETVAL_ERROR;
  }
  _lock(); // lock

  if (hnd->remote_addr == NULL) {
    _unlock();
    return SLI_SOCKET_HND_RETVAL_ERROR;
  }

  memcpy(data, hnd->remote_addr + offset, size);
  _unlock(); //unlock
  return SLI_SOCKET_HND_RETVAL_OK;
}

void sli_socket_hnd_set_sockaddr(sli_socket_hnd_t *handler, const void *sockaddr_struct, const uint8_t socket_addr_len)
{
  if (handler == NULL || sockaddr_struct == NULL) {
    return;
  }
  handler->raw_socket_addr = (void *)sockaddr_struct;   // store the address ptr
  handler->socket_addr_len = socket_addr_len;           // length of complete structure size with domain
}

void sli_socket_hnd_wait_for_conn_available_evt(const sli_socket_hnd_t *hnd)
{
  (void) osEventFlagsWait(hnd->state, (1UL << SOCKET_STATE_CONNECTION_AVAILABLE), osFlagsWaitAny, osWaitForever);
}

/* Weak implementation of fifo overflow handling */
SL_WEAK void sli_socket_hnd_fifo_overflow_handler(const int32_t socketid,
                                                  const uint8_t *buffer,
                                                  const uint32_t size,
                                                  const uint8_t *remaining_buffer)
{
  (void) socketid;
  (void) buffer;
  (void) size;
  (void) remaining_buffer;
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------

__STATIC_INLINE uint8_t *_alloc_remote_addr(void)
{
#if SOCKET_HND_USE_STATIC_BUFFER
  return (uint8_t *)sl_mempool_alloc(&_remote_addr_mpool);
#else
  return (uint8_t *)sl_malloc(SOCKADDR_STORAGE_SIZE);
#endif
}

__STATIC_INLINE uint8_t *_alloc_socket_buff(void)
{
#if SOCKET_HND_USE_STATIC_BUFFER
  return (uint8_t *)sl_mempool_alloc(&_buff_mpool);
#else
  return (uint8_t *)sl_malloc(SL_SOCKET_BUFFER_SIZE);
#endif
}

__STATIC_INLINE void _free_remote_addr(const void * const addr)
{
#if SOCKET_HND_USE_STATIC_BUFFER
  sl_mempool_free(&_remote_addr_mpool, addr);
#else
  sl_free(addr);
#endif
}

__STATIC_INLINE void _free_socket_buff(const void * const addr)
{
#if SOCKET_HND_USE_STATIC_BUFFER
  sl_mempool_free(&_buff_mpool, addr);
#else
  sl_free(addr);
#endif
}

/* Set socket storage */
void _set_socket_storage(const uint8_t idx, const uint16_t domain, const int32_t socket_id, void *socket_addr_struct, const uint8_t socket_addr_len)
{
  uint8_t *buff = NULL;
  _sockets[idx] = &_socket_storage[idx];
  _sockets[idx]->socket_id = socket_id;
  _sockets[idx]->domain = domain;
  _sockets[idx]->raw_socket_addr = socket_addr_struct;
  _sockets[idx]->socket_addr_len = socket_addr_len;
  _sockets[idx]->state = osEventFlagsNew(&_socket_hnd_evt_attr);

  buff = _alloc_socket_buff();
  assert(buff != NULL);
  _init_fifo(_sockets[idx], buff, SL_SOCKET_BUFFER_SIZE);

  // Set remote address to NULL
  _sockets[idx]->remote_addr = NULL;
}

__STATIC_INLINE void _set_state(sli_socket_hnd_t *socket_hnd, const sli_socket_hnd_state_id_t state)
{
  (void) osEventFlagsSet(socket_hnd->state, 1U << state);
}

__STATIC_INLINE void _clear_state(sli_socket_hnd_t *socket_hnd, const sli_socket_hnd_state_id_t state)
{
  (void) osEventFlagsClear(socket_hnd->state, 1U << state);
}

/* lock mutex*/
__STATIC_INLINE void _lock()
{
  assert(osMutexAcquire(_socket_hnd_mtx, osWaitForever) == osOK);
}

/* unlock mutex */
__STATIC_INLINE void _unlock()
{
  assert(osMutexRelease(_socket_hnd_mtx) == osOK);
}

/* Destroy socket handler */
static void _destroy_socket_hnd(sli_socket_hnd_t *socket_hnd)
{
  socket_hnd->domain = SOCKET_DOMAIN_NOT_SET;
  socket_hnd->socket_id = SLI_SOCKET_HND_INVALID_ID;
  socket_hnd->raw_socket_addr = NULL;
  socket_hnd->socket_addr_len = 0;

  // delete states
  (void) osEventFlagsClear(socket_hnd->state, 0x00FFFFFFUL);
  (void) osEventFlagsDelete(socket_hnd->state);
  _free_socket_buff(socket_hnd->fifo._buff);
  _free_remote_addr(socket_hnd->remote_addr);
  socket_hnd->fifo._buff = socket_hnd->fifo._head = socket_hnd->fifo._tail = NULL;
  socket_hnd->remote_addr = NULL;
  socket_hnd->fifo._size = SL_SOCKET_BUFFER_SIZE;
}

/* init fifo internal */
static void _init_fifo(sli_socket_hnd_t *hnd, uint8_t *buff_ptr, const uint32_t size)
{
  _clear_state(hnd, SOCKET_FIFO_UNDERFLOW);
  _clear_state(hnd, SOCKET_FIFO_OVERFLOW);
  hnd->fifo._enable_overwrite = false; // overwrite is disabled
  hnd->fifo._buff = hnd->fifo._head = hnd->fifo._tail = buff_ptr;
  hnd->fifo._size = size;
}

/* reset fifo */
static void _reset_fifo(sli_socket_hnd_t *hnd)
{
  _clear_state(hnd, SOCKET_FIFO_UNDERFLOW);
  _clear_state(hnd, SOCKET_FIFO_OVERFLOW);
  _set_fifo_ptr_to_default(hnd);
}
