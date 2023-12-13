/***************************************************************************//**
 * @file
 * @brief Definitions for the Test Harness plugin.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif

/**
 * @defgroup test-harness Test Harness
 * @ingroup component
 * @brief API and Callbacks for the Test Harness Component
 *
 * This component implements software for support of non-standard test harness
 * behavior to induce failure conditions and verify certified device behavior.
 * This handles negative key establishment test cases for timeout and sending
 * bad messages, mangling OTA upgrade images, starting/stopping the trust center
 * keepalive, initiating network key updates, and testing ZCL attributes.
 *
 */

/**
 * @addtogroup test-harness
 * @{
 */

#define CBKE_OPERATION_GENERATE_KEYS   0
#define CBKE_OPERATION_GENERATE_KEYS_283K1   1
#define CBKE_OPERATION_GENERATE_SECRET 2
#define CBKE_OPERATION_GENERATE_SECRET_283K1 3

#if defined(SL_CATALOG_ZIGBEE_TEST_HARNESS_PRESENT)

#define TEST_HARNESS_PRINT_NAME "TestHarness"

extern EmberEventControl sli_zigbee_af_key_establishment_test_harness_eventControl;

extern uint16_t sli_zigbee_af_key_establishment_test_harness_generate_key_time;
extern uint16_t sli_zigbee_af_key_establishment_test_harness_confirm_key_time;

extern uint16_t sli_zigbee_af_key_establishment_test_harness_advertised_generate_key_time;

extern bool sli_zigbee_af_test_harness_allow_registration;

// Allows test harness to change the message or suppress it.
// Returns true if the message should be sent, false if not.
bool sli_zigbee_af_key_establishment_test_harness_message_send_callback(uint8_t message);

bool sli_zigbee_af_key_establishment_test_harness_cbke_callback(uint8_t cbkeOperation,
                                                                uint8_t* data1,
                                                                uint8_t* data2);
void sli_zigbee_af_key_establishment_test_harness_event_handler(sl_zigbee_event_t * event);

  #define EMBER_AF_CUSTOM_KE_EPHEMERAL_DATA_GENERATE_TIME_SECONDS \
  sli_zigbee_af_key_establishment_test_harness_generate_key_time
  #define EMBER_AF_CUSTOM_KE_GENERATE_SHARED_SECRET_TIME_SECONDS \
  sli_zigbee_af_key_establishment_test_harness_confirm_key_time

  #define EM_AF_ADVERTISED_EPHEMERAL_DATA_GEN_TIME_SECONDS \
  sli_zigbee_af_key_establishment_test_harness_advertised_generate_key_time

extern bool sli_zigbee_af_key_establishment_policy_allow_new_key_entries;
extern bool sli_zigbee_af_test_harness_support_for_new_price_fields;

  #define sendSE11PublishPriceCommand sli_zigbee_af_test_harness_support_for_new_price_fields

#else
  #define sendSE11PublishPriceCommand true

  #define EMBER_AF_TEST_HARNESS_EVENT_STRINGS

  #define sli_zigbee_af_key_establishment_test_harness_message_send_callback(x)      (true)
  #define sli_zigbee_af_key_establishment_test_harness_cbke_callback(x, y, z) (false)

  #define EMBER_KEY_ESTABLISHMENT_TEST_HARNESS_EVENT

  #define sli_zigbee_af_test_harness_allow_registration (1)
#endif

/**
 * @name Callbacks
 * @{
 */

/**
 * @defgroup test_harness_cb Test Harness
 * @ingroup af_callback
 * @brief Callbacks for Test Harness Component
 *
 */

/**
 * @addtogroup test_harness_cb
 * @{
 */

/** @brief Write attributes response callback.
 *
 * @param clusterId cluster ID
 * @param buffer buffer
 * @param bufLen buffer length
 *
 */
void emberAfPluginTestHarnessWriteAttributesResponseCallback(EmberAfClusterId clusterId,
                                                             uint8_t * buffer,
                                                             uint16_t bufLen);

/** @brief Read attributes response callback.
 *
 * @param clusterId cluster ID
 * @param buffer buffer
 * @param bufLen buffer length
 *
 */
void emberAfPluginTestHarnessReadAttributesResponseCallback(EmberAfClusterId clusterId,
                                                            uint8_t * buffer,
                                                            uint16_t bufLen);

/** @} */ // end of test_harness_cb
/** @} */ // end of name Callbacks
/** @} */ // end of test-harness

void sli_zigbee_af_test_harness_reset_aps_frame_counter(void);
void sli_zigbee_af_test_harness_advance_aps_frame_counter(void);
