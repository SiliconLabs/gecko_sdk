/***************************************************************************//**
 * @brief Ember Connect API renaming
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of  Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software  is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include "stack/include/ember.h"
#include "stack/core/sli-connect-api.h"
#ifdef SL_CATALOG_CONNECT_AES_SECURITY_PRESENT
#include <psa/crypto.h>
#endif

// Core
EmberNetworkStatus emberNetworkState(void)
{
  return emApiNetworkState();
}

bool emberStackIsUp(void)
{
  return emApiStackIsUp();
}

EmberStatus emberSetSecurityKey(EmberKeyData *key)
{
  return emApiSetSecurityKey(key);
}

EmberStatus emberGetSecurityKey(EmberKeyData *key)
{
  return emApiGetSecurityKey(key);
}

#ifdef SL_CATALOG_CONNECT_AES_SECURITY_PRESENT
EmberStatus emberSetPsaSecurityKey(mbedtls_svc_key_id_t key_id)
{
  return emApiSetPsaSecurityKey(key_id);
}
#endif

#ifdef SL_CATALOG_CONNECT_AES_SECURITY_PRESENT
EmberStatus emberRemovePsaSecurityKey(void)
{
  return emApiRemovePsaSecurityKey();
}
#endif

#ifdef SL_CATALOG_CONNECT_AES_SECURITY_PRESENT
mbedtls_svc_key_id_t emberGetKeyId(void)
{
  return emApiGetKeyId();
}
#endif

EmberStatus emberGetCounter(EmberCounterType counterType,
                            uint32_t* count)
{
  return emApiGetCounter(counterType,
                         count);
}

EmberStatus emberSetRadioChannelExtended(uint16_t channel,
                                         bool persistent)
{
  return emApiSetRadioChannelExtended(channel,
                                      persistent);
}

EmberStatus emberSetRadioChannel(uint16_t channel)
{
  return emApiSetRadioChannel(channel);
}

uint16_t emberGetRadioChannel(void)
{
  return emApiGetRadioChannel();
}

EmberStatus emberSetRadioPower(int16_t power,
                               bool persistent)
{
  return emApiSetRadioPower(power,
                            persistent);
}

int16_t emberGetRadioPower(void)
{
  return emApiGetRadioPower();
}

EmberStatus emberSetRadioPowerMode(bool radioOn)
{
  return emApiSetRadioPowerMode(radioOn);
}

EmberStatus emberSetMacParams(int8_t ccaThreshold,
                              uint8_t maxCcaAttempts,
                              uint8_t minBackoffExp,
                              uint8_t maxBackoffExp,
                              uint16_t ccaBackoff,
                              uint16_t ccaDuration,
                              uint8_t maxRetries,
                              uint32_t csmaTimeout,
                              uint16_t ackTimeout)
{
  return emApiSetMacParams(ccaThreshold,
                           maxCcaAttempts,
                           minBackoffExp,
                           maxBackoffExp,
                           ccaBackoff,
                           ccaDuration,
                           maxRetries,
                           csmaTimeout,
                           ackTimeout);
}

uint16_t emberCurrentStackTasks(void)
{
  return emApiCurrentStackTasks();
}

bool emberOkToNap(void)
{
  return emApiOkToNap();
}

bool emberOkToHibernate(void)
{
  return emApiOkToHibernate();
}

uint8_t* emberGetEui64(void)
{
  return emApiGetEui64();
}

EmberStatus emberMacGetParentAddress(EmberMacAddress *parentAddress)
{
  return emApiMacGetParentAddress(parentAddress);
}

bool emberIsLocalEui64(EmberEUI64 eui64)
{
  return emApiIsLocalEui64(eui64);
}

EmberNodeId emberGetNodeId(void)
{
  return emApiGetNodeId();
}

EmberPanId emberGetPanId(void)
{
  return emApiGetPanId();
}

EmberNodeId emberGetParentId(void)
{
  return emApiGetParentId();
}

EmberNodeType emberGetNodeType(void)
{
  return emApiGetNodeType();
}

EmberStatus emberCalibrateCurrentChannel(void)
{
  return emApiCalibrateCurrentChannel();
}

EmberStatus emberCalibrateCurrentChannelExtended(uint32_t calValueIn,
                                                 uint32_t* calValueOut)
{
  return emApiCalibrateCurrentChannelExtended(calValueIn,
                                              calValueOut);
}

EmberStatus emberApplyIrCalibration(uint32_t calValue)
{
  return emApiApplyIrCalibration(calValue);
}

EmberStatus emberTempCalibration(void)
{
  return emApiTempCalibration();
}

EmberCalType emberGetCalType(void)
{
  return emApiGetCalType();
}

uint8_t emberGetMaximumPayloadLength(EmberMacAddressMode srcAddressMode,
                                     EmberMacAddressMode dstAddressMode,
                                     bool interpan,
                                     bool secured)
{
  return emApiGetMaximumPayloadLength(srcAddressMode,
                                      dstAddressMode,
                                      interpan,
                                      secured);
}

EmberStatus emberSetIndirectQueueTimeout(uint32_t timeoutMs)
{
  return emApiSetIndirectQueueTimeout(timeoutMs);
}

EmberStatus emberGetVersionInfo(uint16_t* gsdkVersion,
                                uint16_t* connectStackVersion,
                                uint32_t* bootloaderVersion)
{
  return emApiGetVersionInfo(gsdkVersion,
                             connectStackVersion,
                             bootloaderVersion);
}

uint32_t emberStackIdleTimeMs(uint16_t * currentStackTasks)
{
  return emApiStackIdleTimeMs(currentStackTasks);
}

void emberTick(void)
{
  emApiTick();
}

EmberStatus emberInit(void)
{
  return emApiInit();
}

// Messaging
EmberStatus emberMessageSend(EmberNodeId destination,
                             uint8_t endpoint,
                             uint8_t messageTag,
                             EmberMessageLength messageLength,
                             uint8_t *message,
                             EmberMessageOptions options)
{
  return emApiMessageSend(destination,
                          endpoint,
                          messageTag,
                          messageLength,
                          message,
                          options);
}

EmberStatus emberPollForData(void)
{
  return emApiPollForData();
}

EmberStatus emberMacMessageSend(EmberMacFrame *macFrame,
                                uint8_t messageTag,
                                EmberMessageLength messageLength,
                                uint8_t *message,
                                EmberMessageOptions options)
{
  return emApiMacMessageSend(macFrame,
                             messageTag,
                             messageLength,
                             message,
                             options);
}

EmberStatus emberMacSetPanCoordinator(bool isCoordinator)
{
  return emApiMacSetPanCoordinator(isCoordinator);
}

EmberStatus emberSetPollDestinationAddress(EmberMacAddress *destination)
{
  return emApiSetPollDestinationAddress(destination);
}

EmberStatus emberRemoveChild(EmberMacAddress *address)
{
  return emApiRemoveChild(address);
}

EmberStatus emberGetChildFlags(EmberMacAddress *address,
                               EmberChildFlags* flags)
{
  return emApiGetChildFlags(address,
                            flags);
}

EmberStatus emberGetChildInfo(EmberMacAddress *address,
                              EmberMacAddress *addressResp,
                              EmberChildFlags* flags)
{
  return emApiGetChildInfo(address,
                           addressResp,
                           flags);
}

EmberStatus emberPurgeIndirectMessages(void)
{
  return emApiPurgeIndirectMessages();
}

EmberStatus emberMacAddShortToLongAddressMapping(EmberNodeId shortId,
                                                 EmberEUI64 longId)
{
  return emApiMacAddShortToLongAddressMapping(shortId,
                                              longId);
}

EmberStatus emberMacClearShortToLongAddressMappings(void)
{
  return emApiMacClearShortToLongAddressMappings();
}

EmberStatus emberNetworkLeave(void)
{
  return emApiNetworkLeave();
}

// Network Management
EmberStatus emberNetworkInit(void)
{
  return emApiNetworkInit();
}

EmberStatus emberStartActiveScan(uint16_t channel)
{
  return emApiStartActiveScan(channel);
}

EmberStatus emberStartEnergyScan(uint16_t channel,
                                 uint8_t samples)
{
  return emApiStartEnergyScan(channel,
                              samples);
}

EmberStatus emberSetApplicationBeaconPayload(uint8_t payloadLength,
                                             uint8_t *payload)
{
  return emApiSetApplicationBeaconPayload(payloadLength,
                                          payload);
}

EmberStatus emberSetSelectiveJoinPayload(uint8_t payloadLength,
                                         uint8_t *payload)
{
  return emApiSetSelectiveJoinPayload(payloadLength,
                                      payload);
}

EmberStatus emberClearSelectiveJoinPayload(void)
{
  return emApiClearSelectiveJoinPayload();
}

EmberStatus emberFormNetwork(EmberNetworkParameters *parameters)
{
  return emApiFormNetwork(parameters);
}

EmberStatus emberJoinNetworkExtended(EmberNodeType nodeType,
                                     EmberNodeId nodeId,
                                     EmberNetworkParameters *parameters)
{
  return emApiJoinNetworkExtended(nodeType,
                                  nodeId,
                                  parameters);
}

EmberStatus emberJoinNetwork(EmberNodeType nodeType,
                             EmberNetworkParameters *parameters)
{
  return emApiJoinNetwork(nodeType,
                          parameters);
}

EmberStatus emberMacFormNetwork(EmberNetworkParameters *parameters)
{
  return emApiMacFormNetwork(parameters);
}

EmberStatus emberPermitJoining(uint8_t duration)
{
  return emApiPermitJoining(duration);
}

EmberStatus emberJoinCommissioned(EmberNodeType nodeType,
                                  EmberNodeId nodeId,
                                  EmberNetworkParameters *parameters)
{
  return emApiJoinCommissioned(nodeType,
                               nodeId,
                               parameters);
}

void emberResetNetworkState(void)
{
  emApiResetNetworkState();
}

EmberStatus emberFrequencyHoppingSetChannelMask(uint8_t channelMaskLength,
                                                uint8_t *channelMask)
{
  return emApiFrequencyHoppingSetChannelMask(channelMaskLength,
                                             channelMask);
}

EmberStatus emberFrequencyHoppingStartServer(void)
{
  return emApiFrequencyHoppingStartServer();
}

EmberStatus emberFrequencyHoppingStartClient(EmberNodeId serverNodeId,
                                             EmberPanId serverPanId)
{
  return emApiFrequencyHoppingStartClient(serverNodeId,
                                          serverPanId);
}

EmberStatus emberFrequencyHoppingStop(void)
{
  return emApiFrequencyHoppingStop();
}

EmberStatus emberSetAuxiliaryAddressFilteringEntry(EmberNodeId nodeId,
                                                   uint8_t entryIndex)
{
  return emApiSetAuxiliaryAddressFilteringEntry(nodeId,
                                                entryIndex);
}

EmberNodeId emberGetAuxiliaryAddressFilteringEntry(uint8_t entryIndex)
{
  return emApiGetAuxiliaryAddressFilteringEntry(entryIndex);
}

EmberStatus emberStartTxStream(EmberTxStreamParameters parameters,
                               uint16_t channel)
{
  return emApiStartTxStream(parameters,
                            channel);
}

EmberStatus emberStopTxStream(void)
{
  return emApiStopTxStream();
}

EmberStatus emberSetActiveScanDuration(uint16_t durationMs)
{
  return emApiSetActiveScanDuration(durationMs);
}

uint16_t emberGetActiveScanDuration(void)
{
  return emApiGetActiveScanDuration();
}

uint16_t emberGetDefaultChannel(void)
{
  return emApiGetDefaultChannel();
}
