/***************************************************************************//**
 * @file
 * @brief Implements secure EZSP stubs.
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

#include "stack/include/ember.h"
#include "app/util/ezsp/ezsp-protocol.h"

EzspStatus sli_zigbee_secure_ezsp_init(void)
{
  return EZSP_ERROR_INVALID_CALL;
}
EzspStatus sli_zigbee_secure_ezsp_de_init(void)
{
  return EZSP_ERROR_INVALID_CALL;
}
bool sli_zigbee_secure_ezsp_is_on(void)
{
  return false;
}
EzspStatus sli_zigbee_secure_ezsp_encode(void)
{
  return EZSP_ERROR_INVALID_CALL;
}
EzspStatus sli_zigbee_secure_ezsp_decode(void)
{
  return EZSP_ERROR_INVALID_CALL;
}
void sli_zigbee_secure_ezsp_set_state(uint8_t state)
{
  (void)state;
}
bool sli_zigbee_secure_ezsp_parameters_are_pending(void)
{
  return false;
}
