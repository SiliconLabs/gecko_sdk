/***************************************************************************//**
 * @file
 * @brief ESL Tag interface provided to main and bluetooth event handler.
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
#ifndef ESL_CORE_H
#define ESL_CORE_H
#include <stdint.h>
#include <stdbool.h>
#include "sl_bt_api.h"
#include "sl_bt_ead_core.h"
#include "esl_tag_errors.h"
#include "esl_tag_core_config.h"
#include "esl_tag_response.h"
#include "esl_tag_tlv.h"

/// @typedef ESL Tag Basic State type
typedef uint16_t                        esl_basic_state_t;

/// @typedef ESL Address type: consists of ESL ID and Group ID
typedef uint16_t                        esl_address_t;

/// @typedef ESL Tag ID type
typedef uint8_t                         esl_id_t;

/// @typedef ESL Tag Group ID type
typedef uint8_t                         esl_group_id_t;

/// @typedef ESL Tag internal states
typedef enum {
  esl_state_boot = 0,
  esl_state_unassociated,
  esl_state_configuring,
  esl_state_synchronized,
  esl_state_unsynchronized,
  esl_state_updating
} esl_state_t;

/// @typedef ESL Tag function pointer type for generic methods with variadic
/// arguments. That is, any function, returning sl_status_t, while expecting one
/// integer as its mandatory input, and any arbitrary number and types of other
/// parameters if necessary. Implementation of such methods then are up to the
/// users. param_count can be zero as well - if no input parameter is needed by
/// the actual implementation.
typedef sl_status_t(*esl_va_method_p)(int param_count, ...);

/// @typedef ESL Tag function pointer type for generic functions without input
/// and output needs
typedef void(*esl_void_func_p)(void);

/// Maximum allowed payload length for ESL Control Point & PAwR messages
#define ESL_PAYLOAD_MAX_LENGTH      (48u) // ESL Profile d09r18, Section 5.3.1.1

/// Minimum payload length for ESL Control Point & periodic sync messages
#define ESL_PAYLOAD_MIN_LENGTH      (2u)  // 1 TLV

/// Sync packet and PAwR response Link Layer overhead
#define ESL_PAYLOAD_OVERHEAD        (2u)  // Length + AD Type fields

/// Maximum length of single command / response on ESL Control Point
#define ESL_CP_MAX_PAYLOAD_LENGTH   (17) // ESL Service d09r18, Section 3.10.1.1

/// ESL ID for broadcast messages
#define ESL_BROADCAST_ID            ((esl_id_t)0xFF)

/// ESL Advertising Data type for PAwR command and response packets
#define ESL_AD_TYPE                 ((uint8_t)0x34) // BARB assigned number

/// Simple mask for getting the ESL ID from ESL Address
#define ESL_ID_MASK                 ((esl_address_t)0x00FF)

/// Simple mask for getting the ESL group ID from ESL Address
#define ESL_GROUP_ID_MASK           ((esl_address_t)0x7F00)

// ESL Basic State related bit definitions
/// ESL bit status: true
#define ESL_TRUE                    (1u)

/// ESL bit status: false
#define ESL_FALSE                   (0u)

/// ESL bit set: wrapper for @ref ESL_TRUE, more readable when setting a bit
#define ESL_SET                     ESL_TRUE

/// ESL bit clear: wrapper for @ref ESL_FALSE, more readable when clearing a bit
#define ESL_CLEAR                   ESL_FALSE

/// ESL Tag Service Needed bit position
#define ESL_BASIC_STATE_SERVICE_NEEDED_BIT    (0u)

/// ESL Synchronized bit position
#define ESL_BASIC_STATE_SYNCHRONIZED_BIT      (1u)

/// ESL Active LED bit position
#define ESL_BASIC_STATE_ACTIVE_LED_BIT        (2u)

/// ESL Pending LED bit position
#define ESL_BASIC_STATE_PENDING_LED_BIT       (3u)

/// ESL Pending Display Update bit position
#define ESL_BASIC_STATE_PENDING_DISPLAY_BIT   (4u)

/// ESL Tag basic state - single bit mask compositor
#define ESL_BASIC_STATE_MASK(bit)             ((esl_basic_state_t) \
                                               (1u << bit))

/**************************************************************************//**
 * Function like macro getter for ESL ID from ESL Address
 * @param[in] addr_word ESL Address to get the ESL ID from
 * @return esl_id_t ESL ID
 *****************************************************************************/
#define \
  esl_core_get_id(addr_word)        ((esl_id_t)(addr_word & ESL_ID_MASK))

/**************************************************************************//**
 * Function like macro getter for ESL Group ID from ESL Address
 * @param[in] addr_word ESL Address to get the ESl Group ID from
 * @return esl_group_id_t ESL Group ID
 *****************************************************************************/
#define                                               \
  esl_core_get_group_id(addr_word)  ((esl_group_id_t) \
                                     ((addr_word & ESL_GROUP_ID_MASK) >> 8))

/**************************************************************************//**
 * ESL Tag internal status getter. Can be used to check whether an action is
 * allowed to process or not.
 * @return @ref esl_state_t actual internal status of the ESL Tag
 *****************************************************************************/
esl_state_t esl_core_get_status(void);

/**************************************************************************//**
 * Get ESL AP (client) notification status
 * @return true if notifications are enabled, false otherwise
 *****************************************************************************/
bool esl_core_has_notifications(void);

/**************************************************************************//**
 * Get ESL Tag Basic State.
 * @return @ref esl_basic_state_t actual Basic State value of the ESL Tag
 *****************************************************************************/
esl_basic_state_t esl_core_get_basic_state(void);

/**************************************************************************//**
 * Get single ESL Basic State bit value
 * @param[in] bit Position to get the bit information from
 * @return ESL_TRUE or ESL_FALSE depending on actual bit value
 *****************************************************************************/
uint8_t esl_core_get_basic_state_bit(uint8_t bit);

/**************************************************************************//**
 * Set single bit of ESL Basic State
 * @param[in] bit Position of the bit to be set / clear within basic state
 * @param[in] value ESL_SET or ESL_CLEAR, depending on the needs
 * @return esl_basic_state_t new value of the ESL basic state storage
 *****************************************************************************/
esl_basic_state_t esl_core_set_basic_state_bit(uint8_t bit, uint8_t value);

/**************************************************************************//**
 * Read the value from the AP Key characteristics of ESL service.
 * Returns SL_STATUS_NOT_READY until AP Key is written by the bonded AP.
 * My return other failing status as well, depending on stack response, or
 * SL_STATUS_OK on success. In the latter case, the data will be available in
 * *(uint8_t*)ap_key in a format of little endian (packed) byte stream. Size of
 * the stream is defined in ESL standard.
 *
 * @param[out] ap_key esl_ap_key_p pointer type to the storage
 * @return sl_status_t
 *****************************************************************************/
sl_status_t esl_core_read_ap_key(sl_bt_ead_key_material_p ap_key);

/**************************************************************************//**
 * Read the value from the Response Key characteristics of ESL service.
 * Otherwise it works the same way as the @ref esl_core_read_ap_key.
 *
 * @param[out] response_key esl_response_key_p pointer type to the storage
 * @return sl_status_t
 *****************************************************************************/
sl_status_t esl_core_read_response_key(sl_bt_ead_key_material_p response_key);

/**************************************************************************//**
 * Read the value from the ESL Address characteristics of ESL service.
 * Otherwise it works the same way as the @ref esl_core_read_ap_key.
 *
 * @param[out] address esl_address_t pointer type to the storage
 * @return sl_status_t
 *****************************************************************************/
sl_status_t esl_core_read_esl_address(esl_address_t *address);

/**************************************************************************//**
 * Read the value of ESL Absolute Time characteristics of ESL service.
 * Otherwise it works the same way as the @ref esl_core_read_ap_key.
 *
 * @param[out] time uint32_t pointer type to the storage
 * @return sl_status_t
 *****************************************************************************/
sl_status_t esl_core_read_absolute_time(uint32_t *time);

/**************************************************************************//**
 * Update sync parameters for PAwR
 *
 * @param[in] timeout uint32_t new timeout value or set 0 to leave that alone
 * @param[in] skip uint16_t new skip cycles value or set 0 to not skip any
 * @return sl_status_t
 *****************************************************************************/
sl_status_t esl_core_update_sync_parameters(uint32_t timeout, uint16_t skip);

/**************************************************************************//**
 * Clear bonding and put Tag in Unassociated state
 *****************************************************************************/
void esl_core_unassociate(void);

/**************************************************************************//**
* Async disconnect Tag from AP
*
* @param[in] data Unused by this function but mandatory for app_scheduler tasks
* @param[in] size Unused by this function but mandatory for app_scheduler tasks
******************************************************************************/
void esl_core_async_disconnect(void *p_event_data, uint16_t event_size);

/**************************************************************************//**
 * ESL core boot event callback.
 * Exports @ref esl_core_bt_on_event boot event for convenience. There are
 * several restricted action before the BT stack boot event, thus it's highly
 * recommended to wait this event before doing any bluetooth related init,
 * especially those depending on characteristic reads or writes.
 *****************************************************************************/
void esl_core_boot_event(void);

/**************************************************************************//**
 * ESL core unassociate opcode callback.
 * Exports the ESL Unassociate command processed callback for convenience. This
 * function can be implemented for taking any user action may needed after
 * successful execution of either a remote unassociate command request received
 * from the ESL Access Point or any internal event that results the ESL being
 * unassociated. Typical actions may include but not limited to restore
 * some factory default image on the display e.g. for OOB provisioning and / or
 * to reset LED states etc.
 *****************************************************************************/
void esl_core_unassociate_callback(void);

/**************************************************************************//**
 * ESL core service reset opcode event.
 * Exports the ESL Service Reset command processing event for convenience. This
 * function can be implemented for taking any user action may needed during
 * execution of a remote service reset command request received from the ESL
 * Access Point. Typical action is to quick check whether the Service Needed
 * Basic State flag can be really reset or not - if not, then it is permitted
 * to call @ref esl_core_set_basic_state_bit(ESL_BASIC_STATE_SERVICE_NEEDED_BIT)
 * within the function. In this particular case the response will tell the ESL
 * AP immediately that the flag was not reset.
 * @note Writing a blocking code for this function is strictly PROHIBITED!
 *****************************************************************************/
void esl_core_service_reset_event(void);

/**************************************************************************//**
 * ESL Core Update Complete opcode callback.
 * Exports the ESL Update Complete command processed callback for convenience.
 * This function can be implemented to perform any user action required after
 * a successful execution of a remote Update Complete command request received
 * from the ESL Access Point that results in a completed configuration update
 * on the ESL.
 * @note: Writing a blocking code for this function is strictly FORBIDDEN!
 *****************************************************************************/
void esl_core_update_complete_callback(void);

/**************************************************************************//**
 * ESL Core init hook.
 * Allows the application developer to perform specific early actions before
 * the ESL tag is initialized, such as enabling custom peripherals.
 * @note: Writing a blocking code for this function is allowed yet not
 *        recommended.
 *****************************************************************************/
void esl_core_init_hook(void);

/**************************************************************************//**
 * ESL Core shutdown hook.
 * Allows the application developer to perform specific actions before the ESL
 * tag is turned off, such as disabling custom peripherals for further energy
 * savings. The shutdown process cannot be interrupted when this function is
 * called.
 * @note: Writing a blocking code for this function is not recommended.
 *****************************************************************************/
void esl_core_shutdown_hook(void);
#endif // ESL_CORE_H
