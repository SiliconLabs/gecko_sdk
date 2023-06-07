/***************************************************************************//**
 * @file
 * @brief
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "green-power-print-wrapper.h"

/***************************************************************************
* Print stub functions
* Customer should define these in their own application code
***************************************************************************/

#ifndef EMBER_TEST
WEAK(void emberAfCorePrintWrapper(const char * formatString, ...))
{
}

WEAK(void emberAfPrintBigEndianEui64Wrapper(uint8_t * eui, ...))
{
}

WEAK(void emberAfPrintBufferWrapper(uint16_t area, const uint8_t *buffer, uint16_t bufferLen, bool withSpace))
{
}

WEAK(void emberAfAppPrintlnWrapper(const char * formatString, ...))
{
}

WEAK(void emberAfPrintWrapper(uint16_t area, const char * formatString, ...))
{
}

WEAK(void emberAfCorePrintlnWrapper(const char * formatString, ...))
{
}

WEAK(void emberAfDebugPrintWrapper(const char * formatString, ...))
{
}

WEAK(void emberAfDebugPrintlnWrapper(const char * formatString, ...))
{
}

WEAK(void emberAfGreenPowerClusterPrintWrapper(const char * formatString, ...))
{
}

WEAK(void emberAfGreenPowerClusterPrintlnWrapper(const char * formatString, ...))
{
}

WEAK(void emberAfGreenPowerClusterPrintBufferWrapper(const uint8_t *buffer, uint16_t bufferLen, bool withSpace))
{
}

WEAK(void emberAfGreenPowerClusterPrintStringWrapper(const uint8_t *buffer))
{
}
#endif // !EMBER_TEST
