/***************************************************************************//**
 * @file
 * @brief Implements Host-side secure EZSP functionality.
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
#include "platform/service/legacy_host/inc/token.h"
#include "app/util/ezsp/ezsp-protocol.h"
#include "app/util/ezsp/secure-ezsp-host.h"

//------------------------------------------------------------------------------
// Public APIs

EzspStatus emberSecureEzspSetSecurityKey(EmberKeyData *securityKey,
                                         SecureEzspSecurityType securityType)
{
  EzspStatus status;

  status = ezspSetSecurityKey(securityKey, securityType);

  if (status == EZSP_SUCCESS) {
    sli_zigbee_secure_ezsp_set_security_key(securityKey);
    sli_zigbee_secure_ezsp_set_security_type(securityType);
    sli_zigbee_secure_ezsp_set_state(SECURE_EZSP_STATE_PARAMETERS_PENDING);

    // Save new key to host token
    tokTypeSecureEzspSecurityKey tok;
    MEMMOVE(tok.contents,
            emberKeyContents(securityKey),
            EMBER_ENCRYPTION_KEY_SIZE);
    halCommonSetToken(TOKEN_SECURE_EZSP_SECURITY_KEY, &tok);
  }

  return status;
}

EzspStatus emberSecureEzspSetSecurityParameters(SecureEzspSecurityLevel securityLevel,
                                                SecureEzspRandomNumber *hostRandomNumber)
{
  EzspStatus status;
  SecureEzspRandomNumber ncpRandomNumber;

  status = ezspSetSecurityParameters(securityLevel, hostRandomNumber, &ncpRandomNumber);

  if (status == EZSP_SUCCESS) {
    sli_zigbee_secure_ezsp_set_security_level(securityLevel);
    sli_zigbee_secure_ezsp_generate_session_ids(hostRandomNumber, &ncpRandomNumber);
    sli_zigbee_secure_ezsp_set_state(SECURE_EZSP_STATE_SYNCED);
  }

  return status;
}

EzspStatus emberSecureEzspResetToFactoryDefaults(void)
{
  EzspStatus status;

  status = ezspResetToFactoryDefaults();

  if (status == EZSP_SUCCESS) {
    sli_zigbee_secure_ezsp_reset();
  }

  return status;
}

//------------------------------------------------------------------------------
// Internal functions and handlers.

EzspStatus sli_zigbee_secure_ezsp_init(void)
{
  SecureEzspSecurityType ncpSecurityType;
  EzspStatus hostSecurityKeyStatus;
  EzspStatus ncpSecurityKeyStatus = ezspGetSecurityKeyStatus(&ncpSecurityType);

  if (sli_zigbee_secure_ezsp_is_security_key_set()) {
    hostSecurityKeyStatus = EZSP_ERROR_SECURITY_KEY_ALREADY_SET;

    tokTypeSecureEzspSecurityKey tok;
    halCommonGetToken(&tok, TOKEN_SECURE_EZSP_SECURITY_KEY);
    MEMMOVE(emberKeyContents(sli_zigbee_secure_ezsp_get_security_key()),
            tok.contents,
            EMBER_ENCRYPTION_KEY_SIZE);
  } else {
    hostSecurityKeyStatus = EZSP_ERROR_SECURITY_KEY_NOT_SET;
  }

  secureEzspSerialDebug(stderr, "Secure EZSP Init; NCP: 0x%02X, Host: 0x%02X\n",
                        ncpSecurityKeyStatus,
                        hostSecurityKeyStatus);

  if (ncpSecurityKeyStatus == EZSP_ERROR_SECURITY_KEY_ALREADY_SET) {
    sli_zigbee_secure_ezsp_set_state(SECURE_EZSP_STATE_PARAMETERS_PENDING);
  }

  emberSecureEzspInitCallback(ncpSecurityKeyStatus,
                              hostSecurityKeyStatus,
                              ncpSecurityType);
  return EZSP_SUCCESS;
}

EzspStatus sli_zigbee_secure_ezsp_set_security_key(EmberKeyData *securityKey)
{
  //TODO: Remove when we fully move Secure EZSP key out of RAM
  MEMMOVE(emberKeyContents(sli_zigbee_secure_ezsp_get_security_key()),
          emberKeyContents(securityKey),
          EMBER_ENCRYPTION_KEY_SIZE);
  return EZSP_SUCCESS;
}

EzspStatus sli_zigbee_secure_ezsp_reset(void)
{
  // Reset token
  tokTypeSecureEzspSecurityKey tok;
  MEMSET(&tok, 0x00, sizeof(tokTypeSecureEzspSecurityKey));
  halCommonSetToken(TOKEN_SECURE_EZSP_SECURITY_KEY, &tok);

  sli_zigbee_secure_ezsp_de_init();
  return EZSP_SUCCESS;
}
