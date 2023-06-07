/***************************************************************************//**
 * @file
 * @brief ESL Tag operation codes and interfaces declarations
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
#ifndef ESL_TAG_OPCODE_H
#define ESL_TAG_OPCODE_H
#include "sl_status.h"
#include "esl_tag_tlv.h"

/// Ping opcode does nothing but solicits a response
#define ESL_TLV_OPCODE_PING                 ((tlv_t)0x00)

/// Transitions the ESL from the Synchronized state to the Unassociated state
#define ESL_TLV_OPCODE_UNASSOCIATE          ((tlv_t)0x01)

/// Sets the Service Needed flag to False
#define ESL_TLV_OPCODE_SERVICE_RST          ((tlv_t)0x02)

/// Requests the ESL to unassociate from the AP and revert to its original state
#define ESL_TLV_OPCODE_FACTORY_RST          ((tlv_t)0x03)

/// Requests that the ESL return the synchronized state once synchronized
#define ESL_TLV_OPCODE_UPDATE_COMPLETE      ((tlv_t)0x04)

/// Requests a response with sensor data, or an indication that data is not yet
/// available
#define ESL_TLV_OPCODE_READ_SENSOR          ((tlv_t)0x10)

/// Refreshes the current displayed image to keep the displayed image fresh on
/// the display
#define ESL_TLV_OPCODE_REFRESH_DISPLAY      ((tlv_t)0x11)

/// Displays a pre­stored image on an ESL display
#define ESL_TLV_OPCODE_DISPLAY_IMAGE        ((tlv_t)0x20)

/// Displays a pre­stored image on an ESL display at a specified time
#define ESL_TLV_OPCODE_DISPLAY_TIMED_IMAGE  ((tlv_t)0x60)

/// Turns on/off an LED with a color/flashing pattern
#define ESL_TLV_OPCODE_LED_CONTROL          ((tlv_t)0xB0)

/// Turns on/off an LED with a color/flashing pattern at a specified time
#define ESL_TLV_OPCODE_LED_TIMED_CONTROL    ((tlv_t)0xF0)

/// Allows vendors to specify their own commands
#define ESL_TLV_OPCODE_VENDOR_SPECIFIC      ((tlv_t)0x0F)

/// Minimal length of a valid opcode
#define ESL_TLV_OPCODE_MIN_LENGTH           (2) // ESL Profile d09r18, 3.10.1.1
/**************************************************************************//**
 * Parse all opcodes coming from the ESL Control Point or a PAwR sync message
 * and execute them one after the other until:
 * - there's no fail during opcode processing (see @ref esl_core_process_opcode)
 * - there are more messages addressed to the current ESL Tag
 *
 * @param[in] msg void pointer to the incoming data
 * @param[in] len uint8_t length of the incoming data
 * @return sl_status_t
 *****************************************************************************/
sl_status_t esl_core_parse_all_opcodes(void *data, uint8_t len);

/**************************************************************************//**
 * Execute an opcode.
 * Sets the last error if problem occurred during execution and returns an
 * SL_STATUS_FAIL result, SL_STATUS_OK, otherwise.
 *
 * @param[in] self_id esl_id_t the current ESL ID of the device
 * @param[in] id esl_id_t the least significant 8 bit of target ESL Address
 * @param[in] opcode tlv_t opcode to execute
 * @param[out] data void pointer of the pointer to the corresponding data set
 * @note Increments **data pointer to the next opcode on successful operation
 * @return sl_status_t
 *****************************************************************************/
sl_status_t esl_core_process_opcode(esl_id_t self_id,
                                    esl_id_t id,
                                    tlv_t opcode,
                                    void **data);

/**************************************************************************//**
 * Execute a vendor specified opcode.

 * @note On successful processing the @ref esl_core_build_response() shall be
 *       called and this function shall return SL_STATUS_OK. To set up the first
 *       parameter for the response builder function the following macro
 *       invocation can be used:
 *       @ref esl_core_set_tlv_len(ESL_TLV_RESPONSE_VENDOR_VALUE, output_length)
 *       Otherwise, this function shall call @ref esl_core_set_last_error() with
 *       the desired ESL error code and return SL_STATUS_FAIL if a known opcode
 *       is received, but the processing failed, or SL_STATUS_NOT_SUPPORTED if
 *       the opcode is just unknown.
 *
 * @param[in] opcode the vendor specified opcode to process
 * @param[in] input_length length of input data
 * @param[in] data void pointer of the input data to be processed
 * @return sl_status_t
 *****************************************************************************/
sl_status_t esl_core_process_vendor_opcode(tlv_t opcode,
                                           uint8_t input_length,
                                           void *data);

/*******************************************************************************
 * Remove all delayed commands from pending tasks list
 ******************************************************************************/
void esl_core_purge_delayed_commands();

#endif // ESL_TAG_OPCODE_H
