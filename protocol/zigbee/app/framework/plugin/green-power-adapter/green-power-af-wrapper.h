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

#ifndef _SILABS_GREEN_POWER_AF_WRAPPER_H_
#define _SILABS_GREEN_POWER_AF_WRAPPER_H_

#include "zap-config.h"
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

#ifdef FIXED_ENDPOINT_COUNT
#define MAX_ENDPOINT_COUNT FIXED_ENDPOINT_COUNT
#endif

extern uint8_t  appResponseData[EMBER_AF_MAXIMUM_SEND_PAYLOAD_LENGTH];
extern uint16_t appResponseLength;

#if (EMBER_AF_PLUGIN_GREEN_POWER_ADAPTER_USE_CUSTOM_ATTRIBUTE_SYSTEM == 1)
EmberAfStatus emberAfReadAttributeWrapper(uint8_t endpoint,
                                          EmberAfClusterId cluster,
                                          EmberAfAttributeId attributeID,
                                          uint8_t mask,
                                          uint8_t *dataPtr,
                                          uint8_t readLength,
                                          EmberAfAttributeType *dataType);
EmberAfStatus emberAfWriteAttributeWrapper(uint8_t endpoint,
                                           EmberAfClusterId cluster,
                                           EmberAfAttributeId attributeID,
                                           uint8_t mask,
                                           uint8_t* dataPtr,
                                           EmberAfAttributeType dataType);
EmberAfStatus emberAfWriteClientAttributeWrapper(uint8_t endpoint,
                                                 EmberAfClusterId cluster,
                                                 EmberAfAttributeId attributeID,
                                                 uint8_t* dataPtr,
                                                 EmberAfAttributeType dataType);
bool emberAfContainsServerWrapper(uint8_t endpoint, EmberAfClusterId clusterId);
bool emberAfContainsClientWrapper(uint8_t endpoint, EmberAfClusterId clusterId);

#define emberAfReadAttribute emberAfReadAttributeWrapper
#define emberAfWriteAttribute emberAfWriteAttributeWrapper
#define emberAfWriteClientAttribute emberAfWriteClientAttributeWrapper
#define emberAfContainsServer emberAfContainsServerWrapper
#define emberAfContainsClient emberAfContainsClientWrapper

#elif defined(EMBER_AF_NCP) && defined(SL_CATALOG_ZIGBEE_AF_SUPPORT_PRESENT)
bool emberAfContainsServerWrapper(uint8_t endpoint, EmberAfClusterId clusterId);
bool emberAfContainsClientWrapper(uint8_t endpoint, EmberAfClusterId clusterId);
#define emberAfContainsServer emberAfContainsServerWrapper
#define emberAfContainsClient emberAfContainsClientWrapper
#endif // (EMBER_AF_PLUGIN_GREEN_POWER_ADAPTER_USE_CUSTOM_ATTRIBUTE_SYSTEM == 1)

#if (EMBER_AF_PLUGIN_GREEN_POWER_ADAPTER_USE_CUSTOM_AF_INTERFACE == 1)
EmberApsFrame *emberAfGetCommandApsFrameWrapper(void);
EmberStatus emberAfSendCommandUnicastWrapper(EmberOutgoingMessageType type,
                                             uint16_t indexOrDestination);
EmberStatus emberAfSendCommandBroadcastWithAliasWrapper(EmberNodeId destination,
                                                        EmberNodeId alias,
                                                        uint8_t sequence);

EmberStatus emberAfSendCommandMulticastWithAliasWrapper(EmberMulticastId multicastId, EmberNodeId alias, uint8_t sequence);

uint16_t emberAfFillExternalBufferWrapper(uint8_t frameControl,
                                          EmberAfClusterId clusterId,
                                          uint8_t commandId,
                                          const char *format,
                                          ...);

#define emberAfGetCommandApsFrame emberAfGetCommandApsFrameWrapper
#define emberAfSendCommandUnicast emberAfSendCommandUnicastWrapper
#define emberAfSendCommandBroadcastWithAlias emberAfSendCommandBroadcastWithAliasWrapper
#define emberAfSendCommandMulticastWithAlias emberAfSendCommandMulticastWithAliasWrapper
#define emberAfFillExternalBuffer emberAfFillExternalBufferWrapper
#endif // (EMBER_AF_PLUGIN_GREEN_POWER_ADAPTER_USE_CUSTOM_AF_INTERFACE == 1)

bool emberAfAttributeWriteAccessCallback(int8u endpoint,
                                         EmberAfClusterId clusterId,
                                         int16u manufacturerCode,
                                         int16u attributeId);
bool emberAfMemoryByteCompare(const uint8_t* pointer, uint8_t count, uint8_t byteValue);
uint8_t emberAfGetRadioChannelWrapper(void);

#define emberAfGetRadioChannel emberAfGetRadioChannelWrapper

#endif //_SILABS_GREEN_POWER_AF_WRAPPER_H_
