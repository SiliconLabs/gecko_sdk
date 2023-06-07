/***************************************************************************//**
 * @file
 * @brief This file contains stubs for basic debug functionality. It
 * returns only failure.
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

//------------------------------------------------------------------------------
#ifndef DEBUG_STRIPPED // TODO: EMZIGBEE-6992 for cleanup

void sli_zigbee_debug_receive_tick(void)
{
}

void emberDebugBinaryPrintf(const char * formatString, ...)
{
  (void)formatString;
}

void emberDebugAssert(const char * filename, int linenumber)
{
  (void)filename;
  (void)linenumber;
}

void emberDebugMemoryDump(uint8_t *start, uint8_t *end)
{
  (void)start;
  (void)end;
}

void sli_zigbee_debug_binary_format(uint16_t debugType, const char * formatString, ...)
{
  (void)debugType;
  (void)formatString;
}

void sli_util_debug_send_vuart_message(uint8_t *buff, uint8_t len)
{
  (void)buff;
  (void)len;
}

void sli_zigbee_debug_reset_info(void)
{
}

void sli_zigbee_debug_process_incoming(uint16_t debugType, uint8_t *data, uint8_t length)
{
  (void)debugType;
  (void)data;
  (void)length;
}

//------------------------------------------------------------------------------
// For lower layer stubs, refer to debug-platform-stub.c in the HAL.

#endif // DEBUG_STRIPPED
