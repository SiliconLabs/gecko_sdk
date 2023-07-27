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

#ifndef _SILABS_GREEN_POWER_TOKEN_WRAPPER_H_
#define _SILABS_GREEN_POWER_TOKEN_WRAPPER_H_
#include PLATFORM_HEADER
#include "green-power-adapter-config.h"
/***************************************************************************
* Token stub functions
* Customer should define these in their own application code
***************************************************************************/
#if (EMBER_AF_PLUGIN_GREEN_POWER_ADAPTER_USE_CUSTOM_TOKEN_SYSTEM == 1)
void halCommonSetTokenWrapper(uint16_t token, void *data);
void halCommonGetTokenWrapper(void *data, uint16_t token);
void halCommonSetIndexedTokenWrapper(uint16_t token, uint8_t index, void *data);
void halCommonGetIndexedTokenWrapper(void *data, uint16_t token, uint8_t index);

#ifdef halCommonSetToken
#undef halCommonSetToken
#endif //halCommonSetToken
#define halCommonSetToken(token, data) halCommonSetTokenWrapper(token, data)

#ifdef halCommonGetToken
#undef halCommonGetToken
#endif //halCommonSetToken
#define halCommonGetToken(data, token) halCommonGetTokenWrapper(data, token)

#ifdef halCommonSetIndexedToken
#undef halCommonSetIndexedToken
#endif //halCommonSetIndexedToken
#define halCommonSetIndexedToken(token, index, data) halCommonSetIndexedTokenWrapper(token, index, data)

#ifdef halCommonGetIndexedToken
#undef halCommonGetIndexedToken
#endif //halCommonGetIndexedToken
#define halCommonGetIndexedToken(data, token, index) halCommonGetIndexedTokenWrapper(data, token, index)
#endif // (EMBER_AF_PLUGIN_GREEN_POWER_ADAPTER_USE_CUSTOM_TOKEN_SYSTEM == 1)

#endif //_SILABS_GREEN_POWER_TOKEN_WRAPPER_H_
