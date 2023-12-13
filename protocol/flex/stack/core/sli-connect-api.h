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

#ifndef __SLI_CONNECT_API_H__
#define __SLI_CONNECT_API_H__

// Core
EmberNetworkStatus emApiNetworkState(void);

bool emApiStackIsUp(void);

EmberStatus emApiSetSecurityKey(EmberKeyData *key);

EmberStatus emApiGetSecurityKey(EmberKeyData *key);

#ifdef SL_CATALOG_CONNECT_AES_SECURITY_PRESENT
EmberStatus emApiSetPsaSecurityKey(mbedtls_svc_key_id_t key_id);
#endif

#ifdef SL_CATALOG_CONNECT_AES_SECURITY_PRESENT
EmberStatus emApiRemovePsaSecurityKey(void);
#endif

#ifdef SL_CATALOG_CONNECT_AES_SECURITY_PRESENT
mbedtls_svc_key_id_t emApiGetKeyId(void);
#endif

EmberStatus emApiGetCounter(EmberCounterType counterType,
                            uint32_t* count);

EmberStatus emApiSetRadioChannelExtended(uint16_t channel,
                                         bool persistent);

EmberStatus emApiSetRadioChannel(uint16_t channel);

uint16_t emApiGetRadioChannel(void);

EmberStatus emApiSetRadioPower(int16_t power,
                               bool persistent);

int16_t emApiGetRadioPower(void);

EmberStatus emApiSetRadioPowerMode(bool radioOn);

EmberStatus emApiSetMacParams(int8_t ccaThreshold,
                              uint8_t maxCcaAttempts,
                              uint8_t minBackoffExp,
                              uint8_t maxBackoffExp,
                              uint16_t ccaBackoff,
                              uint16_t ccaDuration,
                              uint8_t maxRetries,
                              uint32_t csmaTimeout,
                              uint16_t ackTimeout);

uint16_t emApiCurrentStackTasks(void);

bool emApiOkToNap(void);

bool emApiOkToHibernate(void);

uint8_t* emApiGetEui64(void);

EmberStatus emApiMacGetParentAddress(EmberMacAddress *parentAddress);

bool emApiIsLocalEui64(EmberEUI64 eui64);

EmberNodeId emApiGetNodeId(void);

EmberPanId emApiGetPanId(void);

EmberNodeId emApiGetParentId(void);

EmberNodeType emApiGetNodeType(void);

EmberStatus emApiCalibrateCurrentChannel(void);

EmberStatus emApiCalibrateCurrentChannelExtended(uint32_t calValueIn,
                                                 uint32_t* calValueOut);

EmberStatus emApiApplyIrCalibration(uint32_t calValue);

EmberStatus emApiTempCalibration(void);

EmberCalType emApiGetCalType(void);

uint16_t emApiGetMaximumPayloadLength(EmberMacAddressMode srcAddressMode,
                                      EmberMacAddressMode dstAddressMode,
                                      bool interpan,
                                      bool secured);

EmberStatus emApiSetIndirectQueueTimeout(uint32_t timeoutMs);

uint32_t emApiGetInt32uMillisecondTick(void);

EmberStatus emApiGetVersionInfo(uint16_t* gsdkVersion,
                                uint16_t* connectStackVersion,
                                uint32_t* bootloaderVersion);

EmberStatus emApiOfdmSetMcs(uint8_t mcs);

EmberStatus emApiOfdmGetMcs(uint8_t* mcs);

EmberStatus emApiNcpSetLongMessagesUse(bool useLongMessages);

bool emApiUsingLongMessages(void);

uint32_t emApiStackIdleTimeMs(uint16_t * currentStackTasks);

void emApiTick(void);

EmberStatus emApiInit(void);

// Messaging
EmberStatus emApiMessageSend(EmberNodeId destination,
                             uint8_t endpoint,
                             uint8_t messageTag,
                             EmberMessageLength messageLength,
                             uint8_t *message,
                             EmberMessageOptions options);

EmberStatus emApiPollForData(void);

EmberStatus emApiMacMessageSend(EmberMacFrame *macFrame,
                                uint8_t messageTag,
                                EmberMessageLength messageLength,
                                uint8_t *message,
                                EmberMessageOptions options);

EmberStatus emApiMacSetPanCoordinator(bool isCoordinator);

EmberStatus emApiSetPollDestinationAddress(EmberMacAddress *destination);

EmberStatus emApiRemoveChild(EmberMacAddress *address);

EmberStatus emApiGetChildFlags(EmberMacAddress *address,
                               EmberChildFlags* flags);

EmberStatus emApiGetChildInfo(EmberMacAddress *address,
                              EmberMacAddress *addressResp,
                              EmberChildFlags* flags);

EmberStatus emApiPurgeIndirectMessages(void);

EmberStatus emApiMacAddShortToLongAddressMapping(EmberNodeId shortId,
                                                 EmberEUI64 longId);

EmberStatus emApiMacClearShortToLongAddressMappings(void);

EmberStatus emApiNetworkLeave(void);

// Network Management
EmberStatus emApiNetworkInit(void);

EmberStatus emApiStartActiveScan(uint16_t channel);

EmberStatus emApiStartEnergyScan(uint16_t channel,
                                 uint8_t samples);

EmberStatus emApiSetApplicationBeaconPayload(uint8_t payloadLength,
                                             uint8_t *payload);

EmberStatus emApiSetSelectiveJoinPayload(uint8_t payloadLength,
                                         uint8_t *payload);

EmberStatus emApiClearSelectiveJoinPayload(void);

EmberStatus emApiFormNetwork(EmberNetworkParameters *parameters);

EmberStatus emApiJoinNetworkExtended(EmberNodeType nodeType,
                                     EmberNodeId nodeId,
                                     EmberNetworkParameters *parameters);

EmberStatus emApiJoinNetwork(EmberNodeType nodeType,
                             EmberNetworkParameters *parameters);

EmberStatus emApiMacFormNetwork(EmberNetworkParameters *parameters);

EmberStatus emApiPermitJoining(uint8_t duration);

EmberStatus emApiJoinCommissioned(EmberNodeType nodeType,
                                  EmberNodeId nodeId,
                                  EmberNetworkParameters *parameters);

void emApiResetNetworkState(void);

EmberStatus emApiFrequencyHoppingSetChannelMask(uint8_t channelMaskLength,
                                                uint8_t *channelMask);

EmberStatus emApiFrequencyHoppingStartServer(void);

EmberStatus emApiFrequencyHoppingStartClient(EmberNodeId serverNodeId,
                                             EmberPanId serverPanId);

EmberStatus emApiFrequencyHoppingStop(void);

EmberStatus emApiSetAuxiliaryAddressFilteringEntry(EmberNodeId nodeId,
                                                   uint8_t entryIndex);

EmberNodeId emApiGetAuxiliaryAddressFilteringEntry(uint8_t entryIndex);

EmberStatus emApiStartTxStream(EmberTxStreamParameters parameters,
                               uint16_t channel);

EmberStatus emApiStopTxStream(void);

EmberStatus emApiSetActiveScanDuration(uint16_t durationMs);

uint16_t emApiGetActiveScanDuration(void);

uint16_t emApiGetDefaultChannel(void);

#endif // __SLI_CONNECT_API_H__
