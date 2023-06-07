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

#ifndef _SILABS_GREEN_POWER_PRINT_WRAPPER_H_
#define _SILABS_GREEN_POWER_PRINT_WRAPPER_H_

#include "zap-command.h"
#include "zap-id.h"
#include "zap-type.h"
#include "zap-enabled-incoming-commands.h"
#if !defined SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
#define SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
#include "zap-command-structs.h"
#undef SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
#endif

#include "sl_service_function.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif

#ifdef SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
#include "zcl-framework-core-config.h"
#endif // SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT

#include "green-power-adapter-config.h"

#endif // SL_COMPONENT_CATALOG_PRESENT

/***************************************************************************
* Print stub functions
* Customer should define these in their own application code
***************************************************************************/

#ifndef EMBER_TEST
void emberAfPrintWrapper(uint16_t area, const char * formatString, ...);
void emberAfPrintBigEndianEui64Wrapper(uint8_t * eui, ...);
void emberAfPrintBufferWrapper(uint16_t area, const uint8_t *buffer, uint16_t bufferLen, bool withSpace);
void emberAfCorePrintWrapper(const char * formatString, ...);
void emberAfCorePrintlnWrapper(const char * formatString, ...);
void emberAfAppPrintlnWrapper(const char * formatString, ...);
void emberAfDebugPrintWrapper(const char * formatString, ...);
void emberAfDebugPrintlnWrapper(const char * formatString, ...);
void emberAfGreenPowerClusterPrintWrapper(const char * formatString, ...);
void emberAfGreenPowerClusterPrintlnWrapper(const char * formatString, ...);
void emberAfGreenPowerClusterPrintBufferWrapper(const uint8_t *buffer, uint16_t bufferLen, bool withSpace);
void emberAfGreenPowerClusterPrintStringWrapper(const uint8_t *buffer);

#ifdef emberAfCorePrint
#undef emberAfCorePrint
#endif //emberAfCorePrint
#define emberAfCorePrint(...) emberAfCorePrintWrapper(__VA_ARGS__)

#ifdef emberAfPrintBigEndianEui64
#undef emberAfPrintBigEndianEui64
#endif //emberAfPrintBigEndianEui64
#define emberAfPrintBigEndianEui64(...) emberAfPrintBigEndianEui64Wrapper(__VA_ARGS__)

#ifdef emberAfCorePrintln
#undef emberAfCorePrintln
#endif //emberAfCorePrintln
#define emberAfCorePrintln(...) emberAfCorePrintlnWrapper(__VA_ARGS__)

#ifdef emberAfGreenPowerClusterPrint
#undef emberAfGreenPowerClusterPrint
#endif //emberAfGreenPowerClusterPrint
#define emberAfGreenPowerClusterPrint(...) emberAfGreenPowerClusterPrintWrapper(__VA_ARGS__)

#ifdef emberAfGreenPowerClusterPrintln
#undef emberAfGreenPowerClusterPrintln
#endif //emberAfGreenPowerClusterPrintln
#define emberAfGreenPowerClusterPrintln(...) emberAfGreenPowerClusterPrintlnWrapper(__VA_ARGS__)

#ifdef emberAfGreenPowerClusterPrintBuffer
#undef emberAfGreenPowerClusterPrintBuffer
#endif //emberAfGreenPowerClusterPrintBuffer
#define emberAfGreenPowerClusterPrintBuffer(buffer, len, withSpace) emberAfGreenPowerClusterPrintBufferWrapper(buffer, len, withSpace)

#ifdef emberAfGreenPowerClusterPrintString
#undef emberAfGreenPowerClusterPrintString
#endif //emberAfGreenPowerClusterPrintString
#define emberAfGreenPowerClusterPrintString(buffer) emberAfGreenPowerClusterPrintStringWrapper(buffer)

#ifdef emberAfDebugPrint
#undef emberAfDebugPrint
#endif //emberAfDebugPrint
#define emberAfDebugPrint(...) emberAfDebugPrintWrapper(__VA_ARGS__)

#ifdef emberAfDebugPrintln
#undef emberAfDebugPrintln
#endif //emberAfDebugPrintln
#define emberAfDebugPrintln(...) emberAfDebugPrintlnWrapper(__VA_ARGS__)

#ifdef emberAfPrint
#undef emberAfPrint
#endif //emberAfPrint
#define emberAfPrint(...) emberAfPrintWrapper(__VA_ARGS__)

#ifdef emberAfAppPrintln
#undef emberAfAppPrintln
#endif //emberAfAppPrintln
#define emberAfAppPrintln(...) emberAfAppPrintlnWrapper(__VA_ARGS__)

#ifdef emberAfPrintBuffer
#undef emberAfPrintBuffer
#endif //emberAfPrintBuffer
#define emberAfPrintBuffer(...) emberAfPrintBufferWrapper(__VA_ARGS__)

#endif // !EMBER_TEST

#endif //_SILABS_GREEN_POWER_PRINT_WRAPPER_H_
