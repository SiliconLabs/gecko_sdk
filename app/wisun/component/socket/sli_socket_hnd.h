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
#ifndef _SLI_SOCKET_HND_H_
#define _SLI_SOCKET_HND_H_

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "sl_wisun_types.h"
#include "cmsis_os2.h"
#include "errno.h"
#include "sl_socket_config.h"
#include "em_common.h"

/**************************************************************************//**
 * @defgroup SL_WISUN_SOCKET_HND Socket Handler
 * @ingroup SL_WISUN_SOCKET
 * @{
 *****************************************************************************/

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------
/// Return value of error
#define SLI_SOCKET_HND_RETVAL_ERROR                            (-1L)

/// Return value of correct execution
#define SLI_SOCKET_HND_RETVAL_OK                               (0L)

/// Invalid socket id
#define SLI_SOCKET_HND_INVALID_ID                              (-1L)

/// Socket EOF for closed socket indication
#define SLI_SOCKET_HND_SOCKET_EOF                              (0L)

/// Set errno number macro function
#define sli_socket_hnd_set_errno(err) \
  do {                                \
    errno = (err);                    \
  } while (0)

/// Set errno and return with value macro function
#define sli_socket_hnd_set_errno_ret_error(err) \
  do {                                          \
    sli_socket_hnd_set_errno(err);              \
    return SLI_SOCKET_HND_RETVAL_ERROR;         \
  } while (0)

/**************************************************************************//**
 * @defgroup SL_WISUN_SOCKET_HND_TYPES Socket Handler type definitions
 * @ingroup SL_WISUN_SOCKET_HND
 * @{
 *****************************************************************************/

/// Socket state ID enum
typedef enum sli_socket_hnd_state_id {
  /// Socket State Connection available ID
  SOCKET_STATE_CONNECTION_AVAILABLE = 0,
  /// Socket State FIFO underflow ID
  SOCKET_FIFO_UNDERFLOW,
  /// Socket State FIFO overflow ID
  SOCKET_FIFO_OVERFLOW
} sli_socket_hnd_state_id_t;

/// Socket FIFO handler structure
typedef struct sli_socket_hnd_fifo {
  /// Overwrite previous fifo content.
  /// Fifo is reset and start writing from begining of the buffer
  bool _enable_overwrite;
  /// head pointer to write
  uint8_t *_head;
  /// tail pointer to read
  uint8_t *_tail;
  /// destination buffer pointer
  uint8_t *_buff;
  /// size of the FIFO
  uint32_t _size;
} sli_socket_hnd_fifo_t;

/// Socket handler structure
typedef struct sli_socket_hnd {
  /// socket id
  int32_t socket_id;
  /// socket address length
  uint8_t socket_addr_len;
  /// socket state
  osEventFlagsId_t state;
  /// socket FIFO handler
  sli_socket_hnd_fifo_t fifo;
  /// socket buffer ptr
  uint8_t *socket_buff;
  /// storing the current remote address structure
  uint8_t *remote_addr;
  /// socket family : AF_INET, AF_INET6, AF_WISUN
  uint16_t domain;
  /// socket address pointer
  void *raw_socket_addr;
} sli_socket_hnd_t;

/** @} (end SL_WISUN_SOCKET_HND_TYPES) */

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief Socket handler init.
 * @details Socket handler initialization with default data and null ptr
 *****************************************************************************/
void sli_socket_hnd_init(void);

/**************************************************************************//**
 * @brief Add socket to the internal container.
 * @details Push socket id, socket address with length of address info to storage
 * @param[in] domain The address domain or family, it can be AF_WISUN, AF_INET and AF_INET6
 * @param[in] socket_id socket id
 * @param[in] socket_addr_struct socket address pointer
 * @param[in] socket_addr_len size of address structure
 * @return count of sockets if successful, -1 otherwise
 *****************************************************************************/
int32_t sli_socket_hnd_add(uint16_t domain,
                           const int32_t socket_id,
                           void *socket_addr_struct,
                           const uint8_t socket_addr_len);

/**************************************************************************//**
 * @brief Add only the socket handler to the internal container.
 * @details Push socket id, socket address and length is initialized with zero
 * @param[in] domain The address domain or family, it can be AF_WISUN, AF_INET and AF_INET6
 * @param[in] socket_id socket id
 * @return count of sockets if successful, -1 otherwise
 *****************************************************************************/
__STATIC_INLINE int32_t sli_socket_hnd_add_sockid(uint16_t domain,
                                                  const int32_t socket_id)
{
  return sli_socket_hnd_add(domain, socket_id, NULL, 0);
}

/**************************************************************************//**
 * @brief Get socket handler.
 * @details Get socket handler by socket id
 * @param[in] socket_id socket id
 * @return socket handler pointer in storage if successful, NULL ptr otherwise
 *****************************************************************************/
sli_socket_hnd_t *sli_socket_hnd_get(const int32_t socket_id);

/**************************************************************************//**
 * @brief Check socket id in the storage.
 * @details
 * @param[in] socket_id socket id
 * @return true if socket id is in the storage already, false otherwise
 *****************************************************************************/
__STATIC_INLINE bool sli_socket_hnd_is_exist(const int32_t socket_id)
{
  return (sli_socket_hnd_get(socket_id) == NULL) ? false : true;
}

/**************************************************************************//**
 * @brief Remove socket handler from the storage.
 * @details
 * @param[in] socket_id socket id
 * @return count of sockets in the storage if successful, -1 otherwise
 *****************************************************************************/
int32_t sli_socket_hnd_remove(const int32_t socket_id);

/**************************************************************************//**
 * @brief Get count of sockets in the storage.
 * @details
 * @return count of sockets in the storage if successful, 0 otherwise
 *****************************************************************************/
uint8_t sli_socket_hnd_get_cnt(void);

/**************************************************************************//**
 * @brief Get count of available free slots in the storage.
 * @details
 * @return count of free socket slots in the storage if successful, 0 otherwise
 *****************************************************************************/
__STATIC_INLINE uint8_t sli_socket_hnd_get_available_cnt(void)
{
  return (SL_SOCKET_MAX_SOCKET_COUNT - sli_socket_hnd_get_cnt());
}

/**************************************************************************//**
 * @brief Set socket handler raw socket addr ptr and domain from socket structure.
 * @details Only the raw address ptr is stored, without mem copy
 * @param[out] handler socket handler pointer
 * @param[in] sockaddr_struct the entire socket address structure ptr
 * @param[in] socket_addr_len byte size of the address structure
 *****************************************************************************/
void sli_socket_hnd_set_sockaddr(sli_socket_hnd_t *handler,
                                 const void *sockaddr_struct,
                                 const uint8_t socket_addr_len);

/**************************************************************************//**
 * @brief Set socket handler state.
 * @details Set socket handler state by socket state ID
 * @param[out] handler socket handler ptr
 * @param[in] state_id state ID enum
 * @param[in] value bool value of the state
 *****************************************************************************/
void sli_socket_hnd_set_state(sli_socket_hnd_t *handler,
                              const sli_socket_hnd_state_id_t state_id,
                              const bool value);

/**************************************************************************//**
 * @brief Get socket handler state.
 * @details Get socket handler state by socket state ID
 * @param[in] handler socket handler ptr
 * @param[in] state_id state ID enum
 * @param[out] dest_value bool value of the state
 *****************************************************************************/
void sli_socket_hnd_get_state(const sli_socket_hnd_t *handler,
                              const sli_socket_hnd_state_id_t state_id,
                              bool * const dest_value);

/**************************************************************************//**
 * @brief Initialize socket handler FIFO.
 * @details Set FIFO pointers, size and states (thread safe)
 * @param[in,out] hnd handler
 * @param[in] buff_ptr buffer pointer for FIFO storage
 * @param[in] size size of the FIFO storage
 *****************************************************************************/
void sli_socket_hnd_fifo_init(sli_socket_hnd_t *hnd,
                              uint8_t *buff_ptr,
                              const uint32_t size);

/**************************************************************************//**
 * @brief Reset socket handler FIFO storage
 * @details Set head and tail pointers to the buffer pointers and reset state
 * @param[in,out] hnd socket handler ptr
 *****************************************************************************/
void sli_socket_hnd_fifo_reset(sli_socket_hnd_t *hnd);

/**************************************************************************//**
 * @brief Is remote address stored
 * @details Check remote address ptr is NULL or set
 * @param[in] handler Socket handler
 * @return True if remote address is stored, otherwise false
 *****************************************************************************/
bool sli_socket_hnd_is_remote_addr_stored(const sli_socket_hnd_t * const handler);

/**************************************************************************//**
 * @brief Write data to FIFO.
 * @details Write to FIFO with error handling and size correction
 * @param[in,out] hnd socket handler ptr
 * @param[in] data data buffer to write
 * @param[in,out] size size of data to write, it will be set to the exact wrote size
 * @return return -1 if an error occurred overflow, otherwise 0
 *****************************************************************************/
int32_t sli_socket_hnd_fifo_write(sli_socket_hnd_t *hnd, const uint8_t *data, uint32_t * const size);

/**************************************************************************//**
 * @brief Read data from FIFO.
 * @details Read data from FIFO with error handling and size correction
 * @param[in,out] hnd socket handler ptr
 * @param[in] data data buffer to read
 * @param[in,out] size size of data to read, it will be set to the exact read size
 * @return return -1 if an error occurred underflow, otherwise 0
 *****************************************************************************/
int32_t sli_socket_hnd_fifo_read(sli_socket_hnd_t *hnd, uint8_t *data, uint32_t *size);

/**************************************************************************//**
 * @brief Destroy socket handler FIFO.
 * @details Set pointers to NULL
 * @param[in,out] hnd socket handler ptr
 *****************************************************************************/
__STATIC_INLINE void sli_socket_hnd_fifo_destroy(sli_socket_hnd_t *hnd)
{
  sli_socket_hnd_fifo_init(hnd, NULL, 0);
}

/**************************************************************************//**
 * @brief Set FIFO overwrite mode
 * @details Set overwrite mode with reset FIFO
 * @param[in,out] hnd socket handler ptr
 * @param[in] enabled overwrite mode enabled or disabled bool
 * @return return -1 if an error occurred, otherwise 0
 *****************************************************************************/
int32_t sli_socket_hnd_fifo_set_overwrite(sli_socket_hnd_t *hnd,
                                          const bool enabled);

/**************************************************************************//**
 * @brief Get FIFO overwrite mode.
 * @details Get overwrite mode with reset FIFO
 * @param[in,out] hnd socket handler ptr
 * @param[out] dest_val Result value
 * @return return -1 if an error occurred, otherwise 0
 *****************************************************************************/
int32_t sli_socket_hnd_fifo_get_overwrite(const sli_socket_hnd_t *hnd,
                                          bool * const dest_val);

/**************************************************************************//**
 * @brief Fill socket handler remote address with data
 * @details The function uses internal memcopy
 * @param[in,out] hnd socket handler ptr
 * @param[in] data data pointer to write
 * @param[in] size size of data to write
 * @param[in] offset offset
 * @return return -1 on error, otherwise 0
 *****************************************************************************/
int32_t sli_socket_hnd_write_remote_addr(sli_socket_hnd_t *hnd,
                                         const void *data,
                                         const uint8_t size,
                                         const uint8_t offset);

/**************************************************************************//**
 * @brief Read socket handler remote address
 * @details The function uses internal memcopy
 * @param[in] hnd socket handler ptr
 * @param[out] data destination buffer ptr
 * @param[in] size size of data to read
 * @param[in] offset offset
 * @return return -1 on error, otherwise 0
 *****************************************************************************/
int32_t sli_socket_hnd_read_remote_addr(const sli_socket_hnd_t *hnd,
                                        void *data,
                                        const uint8_t size,
                                        const uint8_t offset);
                                        
/**************************************************************************//**
 * @brief Wait for connection available event
 * @details Check handler status and wait for data event handler termination
 * @param[in] hnd Socket handler
 *****************************************************************************/
void sli_socket_hnd_wait_for_conn_available_evt(const sli_socket_hnd_t *hnd);

/**************************************************************************//**
 * @brief Wi-SUN socket fifo overflow handler.
 * @details Weak implementation, it can be overrided.
 *          User can create own backup process to store remaining data
 * @param[in] socketid socket id
 * @param[in] buffer the original buffer ptr
 * @param[in] size size of the original buffer
 * @param[in] remaining_buffer remaining buffer ptr
 *****************************************************************************/
SL_WEAK void sli_socket_hnd_fifo_overflow_handler(const int32_t socketid,
                                                  const uint8_t *buffer,
                                                  const uint32_t size,
                                                  const uint8_t *remaining_buffer);

/** @}*/
#ifdef __cplusplus
}
#endif
#endif
