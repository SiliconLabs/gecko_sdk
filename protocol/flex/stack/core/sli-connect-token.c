/***************************************************************************//**
 * @file
 * @brief Code duplication to satisfy the token manager's dependency on the
 * legacy HAL
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

/**
 * @note This file should go away once the token manager's dependency on the
 * legacy HAL is deleted. For now we need an implementation of some
 * manufacturing token functions. As part of the legacy HAL replacement, we
 * can't include it anymore (it causes conflicts with other components).
 * So this is a temporary solution.
 */

#include "include/ember.h"
#include "sli-connect-token.h"
#if defined(SL_CATALOG_IOSTREAM_UART_COMMON_PRESENT)
#include "sl_iostream.h"
#endif

void halInternalGetMfgTokenData(void *data, uint16_t token, uint8_t index, uint32_t len)
{
  (void) sl_token_get_manufacturing_data(token, index, data, len);
}

void halInternalSetMfgTokenData(uint16_t token, void *data, uint32_t len)
{
  (void) sl_token_set_manufacturing_data(token, data, len);
}

void halInternalAssertFailed(const char * filename, int linenumber)
{
#if defined(SL_CATALOG_IOSTREAM_UART_COMMON_PRESENT)
  sl_iostream_printf(SL_IOSTREAM_STDOUT, "\r\n[ASSERT:%s:%d]\r\n", filename, linenumber);
#else
  (void)filename;
  (void)linenumber;
#endif // SL_CATALOG_IOSTREAM_UART_COMMON_PRESENT
  NVIC_SystemReset();
}
