/***************************************************************************//**
 * @file
 * @brief This file records the state of crypto operations so that the application
 * can defer processing until after crypto operations have completed.
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

#include "app/framework/util/common.h"
#include "crypto-state.h"

//------------------------------------------------------------------------------

static sli_zigbee_af_crypto_status cryptoStatus = EM_AF_NO_CRYPTO_OPERATION;
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_SECURITY)
static const char * cryptoStatusText[] = EM_AF_CRYPTO_STATUS_TEXT;
#endif //defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_SECURITY)

// If we are on a host micro, there is the possibility that a crypto
// operation ends on the NCP and we fail to hear about it, in this case
// we need a timeout to safeguard against this flag getting locked

//------------------------------------------------------------------------------

sli_zigbee_af_crypto_status sli_zigbee_af_get_crypto_status(void)
{
  return cryptoStatus;
}

void sli_zigbee_af_set_crypto_status(sli_zigbee_af_crypto_status newStatus)
{
  cryptoStatus = newStatus;
#if defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_SECURITY)
  emberAfSecurityPrintln("Crypto state: %p", cryptoStatusText[cryptoStatus]);
#endif // defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_SECURITY)
}
