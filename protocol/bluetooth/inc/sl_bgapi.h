/***************************************************************************//**
 * @brief Silicon Labs BGAPI types and macros
 *******************************************************************************
 * # License
 * <b>Copyright 2019-2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef SL_BGAPI_H
#define SL_BGAPI_H

#include <stdint.h>
#include "sl_status.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Macros to declare deprecated functions */
#if defined(__IAR_SYSTEMS_ICC__)
  #define SL_BGAPI_DEPRECATED _Pragma("deprecated")
#elif defined(__GNUC__)
  #define SL_BGAPI_DEPRECATED __attribute__((deprecated))
#else
  #define SL_BGAPI_DEPRECATED
#endif

/* Compatibility */
#ifndef PACKSTRUCT
/*Default packed configuration*/
#ifdef __GNUC__
#ifdef _WIN32
#define PACKSTRUCT(decl) decl __attribute__((__packed__, gcc_struct))
#else
#define PACKSTRUCT(decl) decl __attribute__((__packed__))
#endif
#define ALIGNED __attribute__((aligned(0x4)))
#elif __IAR_SYSTEMS_ICC__

#define PACKSTRUCT(decl) __packed decl

#define ALIGNED
#elif _MSC_VER  /*msvc*/

#define PACKSTRUCT(decl) __pragma(pack(push, 1) ) decl __pragma(pack(pop) )
#define ALIGNED
#else
#define PACKSTRUCT(a) a PACKED
#endif
#endif

/**
 * The maximum BGAPI command payload size.
 */
#ifndef SL_BGAPI_MAX_PAYLOAD_SIZE
#define SL_BGAPI_MAX_PAYLOAD_SIZE 256
#endif

/***************************************************************************//**
 * @addtogroup sl_bgapi_types BGAPI Types
 * @brief Common types in BGAPI protocol
 * @{
 */

#ifndef SL_BT_TYPE_UINT8ARRARY
#define SL_BT_TYPE_UINT8ARRARY
/** @brief Variable-length uint8_t array. Maximum length: 255 */
typedef struct {
  uint8_t len;    /**< Number of bytes stored in @p data */
  uint8_t data[]; /**< Data bytes*/
} uint8array;
#endif

#ifndef SL_BT_TYPE_BYTE_ARRARY
#define SL_BT_TYPE_BYTE_ARRARY
/** @brief Variable-length int8_t array. Maximum length: 65535 */
typedef struct {
  uint16_t len;    /**< Number of bytes stored in @p data */
  int8_t   data[]; /**< Data bytes*/
} byte_array;
#endif

#ifndef SL_BT_TYPE_BDADDR
#define SL_BT_TYPE_BDADDR
/** @brief Bluetooth address */
typedef struct {
  uint8_t addr[6]; /**< @brief Bluetooth address in reverse byte order */
} bd_addr;
#endif

#ifndef SL_BT_TYPE_UUID128
#define SL_BT_TYPE_UUID128
/** @brief 128-bit UUID */
typedef struct {
  uint8_t data[16]; /**< 128-bit UUID */
} uuid_128;
#endif

#ifndef SL_BT_TYPE_AES_KEY128
#define SL_BT_TYPE_AES_KEY128
/** @brief 128-bit AES key */
typedef struct {
  uint8_t data[16]; /**< 128-bit AES key */
} aes_key_128;
#endif

#ifndef SL_BT_TYPE_UUID16
#define SL_BT_TYPE_UUID16
/** @brief 16-bit UUID */
typedef struct {
  uint8_t data[2]; /**< 16-bit UUID */
} sl_bt_uuid_16_t;
#endif

#ifndef SL_BT_TYPE_UUID64
#define SL_BT_TYPE_UUID64
/** @brief 64-bit UUID */
typedef struct {
  uint8_t data[8]; /**< 64-bit UUID */
} sl_bt_uuid_64_t;
#endif

/** @} */ // end addtogroup sl_bgapi_types
/******************************************************************************/

/** @brief Internal function prototype for BGAPI command handlers */
typedef void (*sl_bgapi_handler)(const void*);

typedef enum sl_bgapi_msg_types {
  sl_bgapi_msg_type_cmd = 0x00,
  sl_bgapi_msg_type_rsp = 0x00,
  sl_bgapi_msg_type_evt = 0x80
} sl_bgapi_msg_types_t;

enum sl_bgapi_dev_types {
  sl_bgapi_dev_type_app = 0x00,
  sl_bgapi_dev_type_bt = 0x20,
  sl_bgapi_dev_type_btmesh = 0x28,
  sl_bgapi_dev_type_bgapi_debug = 0x30,
};

/***************************************************************************//**
 * @addtogroup sl_bgapi_types BGAPI Types
 * @brief Common types in BGAPI protocol
 * @{
 */

/**
 * @brief The length of a BGAPI message header which is 4 bytes
 */
#define SL_BGAPI_MSG_HEADER_LEN (4)

/**
 * @brief Get the device type of a BGAPI message
 *
 * @param HDR The header of the message as a uint32_t integer
 */
#define SL_BGAPI_MSG_DEVICE_TYPE(HDR) ((HDR) & 0x38)

/**
 * @brief Get the identifier of a BGAPI message including device type, class ID,
 * message type and message ID.
 *
 * @param HDR The header of the message as a uint32_t integer
 */
#define SL_BGAPI_MSG_ID(HDR) ((HDR) & 0xffff00f8)

/**
 * @brief Get the data payload length in a BGAPI message.
 *
 * @param HDR The header of the message as a uint32_t integer
 */
#define SL_BGAPI_MSG_LEN(HDR) ((((HDR) & 0x7) << 8) | (((HDR) & 0xff00) >> 8))

/**
 * @brief The bit indicating whether data of a BGAPI message is encrypted
 */
#define SL_BGAPI_BIT_ENCRYPTED (1 << 6) // Bit

/**
 * @brief Check whether data of a BGAPI message is encrypted.
 *
 * @param HDR The BGAPI header of the message as a uint32_t integer
 */
#define SL_BGAPI_MSG_ENCRYPTED(HDR) ((HDR)&SL_BGAPI_BIT_ENCRYPTED)

/** @} */ // end addtogroup sl_bgapi_types
/******************************************************************************/

/**
 * Internal function for setting the command handler function. Used by API library.
 *
 * @param cmd_handler_delegate Pointer to command handler delegate function
 */
void sli_bgapi_set_cmd_handler_delegate(void (*cmd_handler_delegate)(uint32_t,
                                                                     sl_bgapi_handler,
                                                                     const void*));

/**
 * @addtogroup sl_bgapi_functions BGAPI Functions
 * @{
 *
 * @brief Functions provided by the BGAPI protocol
 */

/**
 * @brief Lock the BGAPI for exclusive access.
 *
 * NOTE: This function is provided for NCP/CPC components that need to handle
 * BGAPI commands and responses in their binary format in an application that
 * uses an RTOS. Normal application code that issues BGAPI commands by calling
 * API functions defined by protocol stacks must never call this function
 * directly.
 *
 * See the documentation of @ref sl_bgapi_handle_command for the full sequence
 * that must be followed when processing commands in their binary format.
 *
 * @return SL_STATUS_OK if the lock has been obtained, otherwise an error code
 */
sl_status_t sl_bgapi_lock(void);

/**
 * @brief Release the lock obtained by @ref sl_bgapi_lock
 *
 * NOTE: This function is provided for NCP/CPC components that need to handle
 * BGAPI commands and responses in their binary format in an application that
 * uses an RTOS. Normal application code that issues BGAPI commands by calling
 * API functions defined by protocol stacks must never call this function
 * directly.
 *
 * See the documentation of @ref sl_bgapi_handle_command for the full sequence
 * that must be followed when processing commands in their binary format.
 */
void sl_bgapi_unlock(void);

/**
 * @brief Handle a BGAPI command in binary format.
 *
 * NOTE: This function is provided for NCP/CPC components that need to handle
 * BGAPI commands and responses in their binary format. Normal application code
 * that issues BGAPI commands by calling API functions defined by protocol
 * stacks must never call this function directly.
 *
 * If the application uses an RTOS, the caller must protect the BGAPI handling
 * by obtaining the BGAPI lock with @ref sl_bgapi_lock, handle the command with
 * @ref sl_bgapi_handle_command, read the response from the buffer returned by
 * @ref sl_bgapi_get_command_response, and then release the lock with @ref
 * sl_bgapi_unlock. Here's an example of the full sequence that's required:
 *
 * @code
 * // Lock BGAPI for exclusive access
 * sl_status_t status = sl_bgapi_lock();
 * if (status != SL_STATUS_OK) {
 *   // Locking will only fail if there are fatal unrecoverable errors with the
 *   // RTOS primitives, so caller may choose to just assert in case of errors.
 * }
 *
 * // Process the command
 * sl_bgapi_handle_command(hdr, data);
 *
 * // Read the response
 * void *rsp = sl_bgapi_get_command_response();
 * uint32_t rsp_header = *((uint32_t *)rsp);
 * size_t rsp_len = SL_BGAPI_MSG_LEN(rsp_header) + SL_BGAPI_MSG_HEADER_LEN;
 * // Send the `rsp_len` bytes of response starting from `rsp`
 *
 * // Finally unlock the BGAPI to allow other commands to proceed
 * sl_bgapi_unlock();
 * @endcode
 *
 * Empty stub implementations are provided for @ref sl_bgapi_lock and @ref
 * sl_bgapi_unlock, so the same sequence can be used for all NCP/CPC
 * implementations even if an RTOS is not present.
 *
 * @param[in] hdr The BGAPI command header
 * @param[in] data The payload data associated with the command
 */
void sl_bgapi_handle_command(uint32_t hdr, const void* data);

/**
 * @brief Get the response of a handled BGAPI command.
 *
 * NOTE: This function is provided for NCP/CPC components that need to handle
 * BGAPI commands and responses in their binary format. Normal application code
 * that issues BGAPI commands by calling API functions defined by protocol
 * stacks must never call this function directly.
 *
 * See the documentation of @ref sl_bgapi_handle_command for the full sequence
 * that must be followed when processing commands in their binary format.
 *
 * @return Pointer to the BGAPI response structure that was filled when the
 *   command was executed in @ref sl_bgapi_handle_command.
 */
void* sl_bgapi_get_command_response(void);

/** @} */ // end addtogroup sl_bgapi_functions

#ifdef __cplusplus
}
#endif

#endif
