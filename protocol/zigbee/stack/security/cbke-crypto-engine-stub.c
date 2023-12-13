/***************************************************************************//**
 * @file
 * @brief Stub version of the Certificate Based Key Exchange library.  See non-stub
 * file for more information.
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

#include PLATFORM_HEADER
#include "stack/include/ember-types.h"
#include "stack/include/library.h"
#include "stack/include/ember-types-internal.h"

CryptoOperation sli_zigbee_next_crypto_operation = NULL_OPERATION;
uint8_t* partnerEuiBigEndian = NULL;
// Normally these bools never change in the stub library. However for testing
// it is easier to use the stub version of the library, and allow them to be
// changed.
EMBER_TEST_EXTERNAL_CONST bool sli_zigbee_keys_authorized_by_default  = true;
EMBER_TEST_EXTERNAL_CONST bool sli_zigbee_app_key_requests_are_allowed = true;
bool sli_zigbee_use_static_empheral_keys = false;
const EmberLibraryStatus sli_zigbee_cbke_core_library_status = EMBER_LIBRARY_IS_STUB;
//------------------------------------------------------------------------------

bool sli_zigbee_cbke_is_idle(void)
{
  return true;
}

void sli_zigbee_cbke_tick(void)
{
}

void sli_zigbee_prepare_for_cbke_operation(void)
{
}

void sli_zigbee_prep_for_ecc_operation(uint8_t index, bool start)
{
  (void)index;
  (void)start;
}

void startupRadio(void)
{
}

int sli_zigbee_watchdog_tickle(void)
{
  return EMBER_ERR_FATAL;
}

bool sli_zigbee_are_keys_authorized_by_default(void)
{
  // By default without the CBKE library we assume that all keys added
  // (via emberSetInitialSecurityState() or sl_zb_sec_man_import_link_key())
  // are authorized for APS data messages.
  return sli_zigbee_keys_authorized_by_default;         // true
}

bool sli_zigbee_does_security_policy_allow_app_key_requests(EmberEUI64 partner1,
                                                            EmberEUI64 partner2)
{
  (void)partner1;
  (void)partner2;
  return sli_zigbee_app_key_requests_are_allowed;       // true
}

EmberStatus sli_zigbee_validate_partner_link_key_request(EmberEUI64 partner)
{
  (void)partner;
  return EMBER_LIBRARY_NOT_PRESENT;
}

int sli_zigbee_random_data_generator(void *buffer, uint32_t size)
{
  (void)buffer;
  (void)size;
  return EMBER_ERR_FATAL;
}

int sli_zigbee_hash_function(uint8_t* digest, uint32_t size, uint8_t* data)
{
  (void)digest;
  (void)size;
  (void)data;
  return EMBER_ERR_FATAL;
}
void copyEui64BigEndian(bool mine, uint8_t* eui64)
{
  (void)mine;
  (void)eui64;
}
