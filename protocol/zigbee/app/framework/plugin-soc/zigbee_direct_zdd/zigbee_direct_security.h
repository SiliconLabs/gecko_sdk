/***************************************************************************//**
 * @file zigbee_direct_security.h
 * @brief Zigbee direct security header
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc.  Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement.  This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef SILABS_ZIGBEE_DIRECT_SECURITY_H
#define SILABS_ZIGBEE_DIRECT_SECURITY_H

#include "sl_bluetooth.h"
#include "gatt_db.h"

typedef enum {
  BLE_OFF                = 0,
  OPEN_TO_BE_PROVISIONED,
  PROVISIONED_IN_PROVISIONING_SESSION,
  PROVISIONED,
  COMMISSIONED_BASIC,
  COMMISSIONED_ADMIN,
} sl_zigbee_direct_connection_status_t;

// Opcode defined by the Zigbee Direct Spec
enum {
  SESSION_ESTABLISHMENT_MSG_1 = 0x01,
  SESSION_ESTABLISHMENT_MSG_2 = 0x02,
  SESSION_ESTABLISHMENT_MSG_3 = 0x03,
  SESSION_ESTABLISHMENT_MSG_4 = 0x04,
};

extern uint8_t admin_key[16];
extern uint32_t sl_zigbee_direct_anonymous_join_timeout_sec;
extern uint8_t sl_zigbee_direct_interface_state;
extern uint8_t zigbee_direct_session_key[16];
extern uint32_t incoming_counter;
extern uint32_t outgoing_counter;
extern sl_zigbee_event_t sli_zigbee_direct_anonymous_join_event;
extern bool sli_zigbee_direct_tc_is_zigbee_direct_aware;

void sl_zigbee_direct_handle_authenticate_write(uint8_t connection, uint8array *writeValue, uint16_t characteristic);
void sli_zigbee_direct_anonymous_join_event_handler(sl_zigbee_event_t *event);

/** @brief Calculates the Basic Key for a given ZVD based on the
 * current network (transport) key
 *
 * @param zvd_IEEE         The EUI64 address of the ZVD.
 *
 * @param basic_key        The Basic Key is copied here.
 *
 * @return Returns ::SL_STATUS_OK the Basic Key was calculated successfully,
 *         ::SL_STATUS_FAIL if not.
 */
sl_status_t sl_zigbee_direct_calculate_basic_key(EmberEUI64 zvd_IEEE, uint8_t* basic_key);

/** @brief Calculates the Admin Key for a given ZVD based on the
 * current TC link key for that device
 *
 * @param zvd_IEEE         The EUI64 address of the ZVD.
 *
 * @param admin_key        The Admin Key is copied here.
 *
 * @return Returns ::SL_STATUS_OK the Admin Key was calculated successfully,
 *         ::SL_STATUS_FAIL if not.
 */
sl_status_t sl_zigbee_direct_calculate_admin_key(EmberEUI64 zvd_IEEE, uint8_t* admin_key);

/** @brief Converts 16-bit UUID into 128-bit UUID
 *
 * @param input         The 16-bit UUID.
 *
 * @param *output       Pointer to the 128-bit UUID
 *
 */
void sl_convert_16bit_uuid_to_128bit_uuid(uint16_t input, uint8_t *output);

/** @brief Initializes Zigbee Direct Security
 *
 * @return Returns ::SL_STATUS_OK in case Zigbee Direct security was initialized,
 *         ::SL_STATUS_FAIL if not.
 */
sl_status_t sli_zigbee_direct_security_init();

/** @brief Encrypt Zigbee Direct packet
 * Direction of transmission is ZDD towards ZVD
 *
 * @param sourceEui         The EUI64 address of the source (typically the ZDD).
 *
 * @param *encryptData      Pointer to the payload which is to be encrypted
 *
 * @param dataLen           Length of the payload which is to be encrypted
 *
 * @param handle            BLE handle via which the data is exchanged
 *
 * @return Returns ::SL_STATUS_OK if the payload was encrypted successfully,
 *                    The encryptData will contain the encrypted message
 *         ::SL_STATUS_FAIL if not.
 */
sl_status_t sl_zigbee_direct_security_encrypt_packet(EmberEUI64 sourceEui, uint8_t *encryptData, uint16_t dataLen, uint16_t handle);

/** @brief Decrypt Zigbee Direct packet
 * Direction of transmission is ZVD towards ZDD
 *
 * @param sourceEui         The EUI64 address of the source (typically the ZVD).
 *
 * @param *decryptData      Pointer to the payload which is to be decrypted
 *
 * @param dataLen           Length of the payload which is to be decrypted
 *
 * @param handle            BLE handle via which the data is exchanged
 *
 * @return Returns ::TRUE if the payload was decrypted successfully,
 *                    The decryptData will contain the decrypted message
 *         ::FALSE if not.
 */
bool sl_zigbee_direct_security_decrypt_packet(EmberEUI64 sourceEui, uint8_t *decryptData, uint16_t dataLen, uint16_t handle);

#endif // SILABS_ZIGBEE_DIRECT_SECURITY_H
