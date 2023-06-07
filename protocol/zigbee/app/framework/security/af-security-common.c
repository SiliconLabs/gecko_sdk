/***************************************************************************//**
 * @file
 * @brief Security code common to both the Trust Center and the normal node.
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

#include "app/framework/include/af.h"
#include "app/framework/security/af-security.h"
#include "app/util/serial/sl_zigbee_command_interpreter.h"
#include "app/framework/cli/security-cli.h"
#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif //SL_COMPONENT_CATALOG_PRESENT

//------------------------------------------------------------------------------
bool emberAfClearLinkKeyTableUponFormingOrJoining = true;

const EmberAfSecurityProfileData sli_zigbee_af_security_profile_data[] = {
  #include "security-profile-data.h"
};

#if (defined(SL_CATALOG_CLI_PRESENT))
static const EmberKeyData unSetKey = DUMMY_KEY;

// This routine sets the keys from values previously set on the CLI.
// If none are set via the CLI, then the default keys for the security profile
// are used.
static void getKeyFromCli(EmberKeyData* returnData, bool linkKey)
{
  uint8_t* keyPtr = (linkKey
                     ? emberKeyContents(&cliPreconfiguredLinkKey)
                     : emberKeyContents(&cliNetworkKey));
  if (0 != MEMCOMPARE(keyPtr,
                      emberKeyContents(&unSetKey),
                      EMBER_ENCRYPTION_KEY_SIZE)) {
    MEMMOVE(emberKeyContents(returnData), keyPtr, EMBER_ENCRYPTION_KEY_SIZE);
  }
}

void getLinkKeyFromCli(EmberKeyData* returnData)
{
  getKeyFromCli(returnData, true);
}

void getNetworkKeyFromCli(EmberKeyData* returnData)
{
  getKeyFromCli(returnData, false);
}

#endif

void sli_zigbee_af_clear_link_key_table(void)
{
#if EMBER_KEY_TABLE_SIZE
  if (emberAfClearLinkKeyTableUponFormingOrJoining) {
    emberClearKeyTable();
  }
  emberAfClearLinkKeyTableUponFormingOrJoining = true;
#endif
}

const EmberAfSecurityProfileData *sli_zigbee_af_get_current_security_profile_data(void)
{
  uint8_t i;
  for (i = 0; i < COUNTOF(sli_zigbee_af_security_profile_data); i++) {
    if (sli_zigbee_af_pro_is_current_network()
        && (sli_zigbee_af_current_zigbee_pro_network->securityProfile
            == sli_zigbee_af_security_profile_data[i].securityProfile)) {
      return &sli_zigbee_af_security_profile_data[i];
    }
  }
  return NULL;
}

bool emberAfIsCurrentSecurityProfileSmartEnergy(void)
{
#ifdef EMBER_AF_HAS_SECURITY_PROFILE_SE
  return (sli_zigbee_af_pro_is_current_network()
          && ((sli_zigbee_af_current_zigbee_pro_network->securityProfile
               == EMBER_AF_SECURITY_PROFILE_SE_TEST)
              || (sli_zigbee_af_current_zigbee_pro_network->securityProfile
                  == EMBER_AF_SECURITY_PROFILE_SE_FULL)));
#else
  return false;
#endif
}
