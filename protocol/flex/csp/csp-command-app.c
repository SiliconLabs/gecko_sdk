/***************************************************************************//**
 * @brief Host functions for sending Connect management commands to the NCP.
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

// *** Generated file. Do not edit! ***
// vNCP Version: 1.0

#include PLATFORM_HEADER

#include "stack/include/ember.h"
#include "stack/core/sli-connect-api.h"

#include "csp-format.h"
#include "csp-command-utils.h"
#include "csp-api-enum-gen.h"

// networkState
EmberNetworkStatus emberNetworkState(void)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_NETWORK_STATE_IPC_COMMAND_ID,
                        "");
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberNetworkStatus networkStatus;
  fetchApiParams(apiCommandData,
                 "u",
                 &networkStatus);
  releaseCommandMutex();
  return networkStatus;
}

// stackIsUp
bool emberStackIsUp(void)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_STACK_IS_UP_IPC_COMMAND_ID,
                        "");
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  bool stackIsUp;
  fetchApiParams(apiCommandData,
                 "u",
                 &stackIsUp);
  releaseCommandMutex();
  return stackIsUp;
}

// setSecurityKey
EmberStatus emberSetSecurityKey(EmberKeyData *key)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_SET_SECURITY_KEY_IPC_COMMAND_ID,
                        "b",
                        key,
                        EMBER_ENCRYPTION_KEY_SIZE);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// GetSecurityKey
EmberStatus emberGetSecurityKey(EmberKeyData *key)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_GET_SECURITY_KEY_IPC_COMMAND_ID,
                        "b",
                        key->contents,
                        EMBER_ENCRYPTION_KEY_SIZE);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;

  uint8_t Size = EMBER_ENCRYPTION_KEY_SIZE;
  fetchApiParams(apiCommandData,
                 "ub",
                 &status,
                 key->contents,
                 &Size,
                 EMBER_ENCRYPTION_KEY_SIZE);
  releaseCommandMutex();
  return status;
}

#ifdef SL_CATALOG_CONNECT_AES_SECURITY_PRESENT
// setPsaSecurityKey
EmberStatus emberSetPsaSecurityKey(mbedtls_svc_key_id_t key_id)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_SET_PSA_SECURITY_KEY_IPC_COMMAND_ID,
                        "w",
                        key_id);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

#endif

#ifdef SL_CATALOG_CONNECT_AES_SECURITY_PRESENT
// RemovePsaSecurityKey
EmberStatus emberRemovePsaSecurityKey(void)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_REMOVE_PSA_SECURITY_KEY_IPC_COMMAND_ID,
                        "");
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

#endif

#ifdef CONNECT_NCP
// setNcpSecurityKey
EmberStatus emberSetNcpSecurityKey(uint8_t *key,
                                   uint8_t keyLength)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_SET_NCP_SECURITY_KEY_IPC_COMMAND_ID,
                        "b",
                        key,
                        keyLength);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

#endif

// getCounter
EmberStatus emberGetCounter(EmberCounterType counterType,
                            uint32_t* count)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_GET_COUNTER_IPC_COMMAND_ID,
                        "u",
                        counterType);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;

  fetchApiParams(apiCommandData,
                 "uw",
                 &status,
                 count);
  releaseCommandMutex();
  return status;
}

// setRadioChannelExtended
EmberStatus emberSetRadioChannelExtended(uint16_t channel,
                                         bool persistent)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_SET_RADIO_CHANNEL_EXTENDED_IPC_COMMAND_ID,
                        "vu",
                        channel,
                        persistent);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// setRadioChannel
EmberStatus emberSetRadioChannel(uint16_t channel)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_SET_RADIO_CHANNEL_IPC_COMMAND_ID,
                        "v",
                        channel);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// getRadioChannel
uint16_t emberGetRadioChannel(void)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_GET_RADIO_CHANNEL_IPC_COMMAND_ID,
                        "");
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  uint16_t channel;
  fetchApiParams(apiCommandData,
                 "v",
                 &channel);
  releaseCommandMutex();
  return channel;
}

// setRadioPower
EmberStatus emberSetRadioPower(int16_t power,
                               bool persistent)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_SET_RADIO_POWER_IPC_COMMAND_ID,
                        "vu",
                        power,
                        persistent);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// getRadioPower
int16_t emberGetRadioPower(void)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_GET_RADIO_POWER_IPC_COMMAND_ID,
                        "");
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  int16_t power;
  fetchApiParams(apiCommandData,
                 "v",
                 &power);
  releaseCommandMutex();
  return power;
}

// setRadioPowerMode
EmberStatus emberSetRadioPowerMode(bool radioOn)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_SET_RADIO_POWER_MODE_IPC_COMMAND_ID,
                        "u",
                        radioOn);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// setMacParams
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
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_SET_MAC_PARAMS_IPC_COMMAND_ID,
                        "suuuvvuwv",
                        ccaThreshold,
                        maxCcaAttempts,
                        minBackoffExp,
                        maxBackoffExp,
                        ccaBackoff,
                        ccaDuration,
                        maxRetries,
                        csmaTimeout,
                        ackTimeout);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// currentStackTasks
uint16_t emberCurrentStackTasks(void)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_CURRENT_STACK_TASKS_IPC_COMMAND_ID,
                        "");
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  uint16_t currentTasks;
  fetchApiParams(apiCommandData,
                 "v",
                 &currentTasks);
  releaseCommandMutex();
  return currentTasks;
}

// okToNap
bool emberOkToNap(void)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_OK_TO_NAP_IPC_COMMAND_ID,
                        "");
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  bool isOkToNap;
  fetchApiParams(apiCommandData,
                 "u",
                 &isOkToNap);
  releaseCommandMutex();
  return isOkToNap;
}

// okToHibernate
bool emberOkToHibernate(void)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_OK_TO_HIBERNATE_IPC_COMMAND_ID,
                        "");
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  bool isOkToHibernate;
  fetchApiParams(apiCommandData,
                 "u",
                 &isOkToHibernate);
  releaseCommandMutex();
  return isOkToHibernate;
}

// getEui64
uint8_t* emberGetEui64(void)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_GET_EUI64_IPC_COMMAND_ID,
                        "");
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  static uint8_t eui64[EUI64_SIZE];
  uint8_t eui64Size = EUI64_SIZE;
  fetchApiParams(apiCommandData,
                 "b",
                 eui64,
                 &eui64Size);
  releaseCommandMutex();
  return eui64;
}

// macGetParentAddress
EmberStatus emberMacGetParentAddress(EmberMacAddress *parentAddress)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_MAC_GET_PARENT_ADDRESS_IPC_COMMAND_ID,
                        "vbu",
                        parentAddress->addr.shortAddress,
                        parentAddress->addr.longAddress,
                        EUI64_SIZE,
                        parentAddress->mode);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;

  uint8_t longAddressSize = EUI64_SIZE;
  fetchApiParams(apiCommandData,
                 "uvbu",
                 &status,
                 &parentAddress->addr.shortAddress,
                 parentAddress->addr.longAddress,
                 &longAddressSize,
                 EUI64_SIZE,
                 &parentAddress->mode);
  releaseCommandMutex();
  return status;
}

// isLocalEui64
bool emberIsLocalEui64(EmberEUI64 eui64)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_IS_LOCAL_EUI64_IPC_COMMAND_ID,
                        "b",
                        eui64,
                        EUI64_SIZE);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  bool localEui64;
  fetchApiParams(apiCommandData,
                 "u",
                 &localEui64);
  releaseCommandMutex();
  return localEui64;
}

// getNodeId
EmberNodeId emberGetNodeId(void)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_GET_NODE_ID_IPC_COMMAND_ID,
                        "");
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberNodeId nodeId;
  fetchApiParams(apiCommandData,
                 "v",
                 &nodeId);
  releaseCommandMutex();
  return nodeId;
}

// getPanId
EmberPanId emberGetPanId(void)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_GET_PAN_ID_IPC_COMMAND_ID,
                        "");
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberPanId panId;
  fetchApiParams(apiCommandData,
                 "v",
                 &panId);
  releaseCommandMutex();
  return panId;
}

// getParentId
EmberNodeId emberGetParentId(void)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_GET_PARENT_ID_IPC_COMMAND_ID,
                        "");
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberNodeId parentNodeId;
  fetchApiParams(apiCommandData,
                 "v",
                 &parentNodeId);
  releaseCommandMutex();
  return parentNodeId;
}

// getNodeType
EmberNodeType emberGetNodeType(void)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_GET_NODE_TYPE_IPC_COMMAND_ID,
                        "");
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberNodeType nodeType;
  fetchApiParams(apiCommandData,
                 "u",
                 &nodeType);
  releaseCommandMutex();
  return nodeType;
}

// calibrateCurrentChannel
EmberStatus emberCalibrateCurrentChannel(void)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_CALIBRATE_CURRENT_CHANNEL_IPC_COMMAND_ID,
                        "");
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// calibrateCurrentChannelExtended
EmberStatus emberCalibrateCurrentChannelExtended(uint32_t calValueIn,
                                                 uint32_t* calValueOut)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_CALIBRATE_CURRENT_CHANNEL_EXTENDED_IPC_COMMAND_ID,
                        "w",
                        calValueIn);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;

  fetchApiParams(apiCommandData,
                 "uw",
                 &status,
                 calValueOut);
  releaseCommandMutex();
  return status;
}

// applyIrCalibration
EmberStatus emberApplyIrCalibration(uint32_t calValue)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_APPLY_IR_CALIBRATION_IPC_COMMAND_ID,
                        "w",
                        calValue);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// tempCalibration
EmberStatus emberTempCalibration(void)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_TEMP_CALIBRATION_IPC_COMMAND_ID,
                        "");
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// getCalType
EmberCalType emberGetCalType(void)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_GET_CAL_TYPE_IPC_COMMAND_ID,
                        "");
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberCalType calType;
  fetchApiParams(apiCommandData,
                 "w",
                 &calType);
  releaseCommandMutex();
  return calType;
}

// getMaximumPayloadLength
uint8_t emberGetMaximumPayloadLength(EmberMacAddressMode srcAddressMode,
                                     EmberMacAddressMode dstAddressMode,
                                     bool interpan,
                                     bool secured)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_GET_MAXIMUM_PAYLOAD_LENGTH_IPC_COMMAND_ID,
                        "uuuu",
                        srcAddressMode,
                        dstAddressMode,
                        interpan,
                        secured);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  uint8_t payloadLength;
  fetchApiParams(apiCommandData,
                 "u",
                 &payloadLength);
  releaseCommandMutex();
  return payloadLength;
}

// setIndirectQueueTimeout
EmberStatus emberSetIndirectQueueTimeout(uint32_t timeoutMs)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_SET_INDIRECT_QUEUE_TIMEOUT_IPC_COMMAND_ID,
                        "w",
                        timeoutMs);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// messageSend
EmberStatus emberMessageSend(EmberNodeId destination,
                             uint8_t endpoint,
                             uint8_t messageTag,
                             EmberMessageLength messageLength,
                             uint8_t *message,
                             EmberMessageOptions options)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_MESSAGE_SEND_IPC_COMMAND_ID,
                        "vuuubu",
                        destination,
                        endpoint,
                        messageTag,
                        messageLength,
                        message,
                        messageLength,
                        options);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// pollForData
EmberStatus emberPollForData(void)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_POLL_FOR_DATA_IPC_COMMAND_ID,
                        "");
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// macMessageSend
EmberStatus emberMacMessageSend(EmberMacFrame *macFrame,
                                uint8_t messageTag,
                                EmberMessageLength messageLength,
                                uint8_t *message,
                                EmberMessageOptions options)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_MAC_MESSAGE_SEND_IPC_COMMAND_ID,
                        "vbuvbuvvuuuubu",
                        macFrame->srcAddress.addr.shortAddress,
                        macFrame->srcAddress.addr.longAddress,
                        EUI64_SIZE,
                        macFrame->srcAddress.mode,
                        macFrame->dstAddress.addr.shortAddress,
                        macFrame->dstAddress.addr.longAddress,
                        EUI64_SIZE,
                        macFrame->dstAddress.mode,
                        macFrame->srcPanId,
                        macFrame->dstPanId,
                        macFrame->srcPanIdSpecified,
                        macFrame->dstPanIdSpecified,
                        messageTag,
                        messageLength,
                        message,
                        messageLength,
                        options);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// macSetPanCoordinator
EmberStatus emberMacSetPanCoordinator(bool isCoordinator)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_MAC_SET_PAN_COORDINATOR_IPC_COMMAND_ID,
                        "u",
                        isCoordinator);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// setPollDestinationAddress
EmberStatus emberSetPollDestinationAddress(EmberMacAddress *destination)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_SET_POLL_DESTINATION_ADDRESS_IPC_COMMAND_ID,
                        "vbu",
                        destination->addr.shortAddress,
                        destination->addr.longAddress,
                        EUI64_SIZE,
                        destination->mode);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// removeChild
EmberStatus emberRemoveChild(EmberMacAddress *address)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_REMOVE_CHILD_IPC_COMMAND_ID,
                        "vbu",
                        address->addr.shortAddress,
                        address->addr.longAddress,
                        EUI64_SIZE,
                        address->mode);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// getChildFlags
EmberStatus emberGetChildFlags(EmberMacAddress *address,
                               EmberChildFlags* flags)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_GET_CHILD_FLAGS_IPC_COMMAND_ID,
                        "vbu",
                        address->addr.shortAddress,
                        address->addr.longAddress,
                        EUI64_SIZE,
                        address->mode);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;

  fetchApiParams(apiCommandData,
                 "uu",
                 &status,
                 flags);
  releaseCommandMutex();
  return status;
}

// getChildInfo
EmberStatus emberGetChildInfo(EmberMacAddress *address,
                              EmberMacAddress *addressResp,
                              EmberChildFlags* flags)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_GET_CHILD_INFO_IPC_COMMAND_ID,
                        "vbu",
                        address->addr.shortAddress,
                        address->addr.longAddress,
                        EUI64_SIZE,
                        address->mode);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;

  uint8_t longAddressSize = EUI64_SIZE;

  fetchApiParams(apiCommandData,
                 "uvbuu",
                 &status,
                 &addressResp->addr.shortAddress,
                 addressResp->addr.longAddress,
                 &longAddressSize,
                 EUI64_SIZE,
                 &addressResp->mode,
                 flags);
  releaseCommandMutex();
  return status;
}

// purgeIndirectMessages
EmberStatus emberPurgeIndirectMessages(void)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_PURGE_INDIRECT_MESSAGES_IPC_COMMAND_ID,
                        "");
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// macAddShortToLongAddressMapping
EmberStatus emberMacAddShortToLongAddressMapping(EmberNodeId shortId,
                                                 EmberEUI64 longId)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_MAC_ADD_SHORT_TO_LONG_ADDRESS_MAPPING_IPC_COMMAND_ID,
                        "vb",
                        shortId,
                        longId,
                        EUI64_SIZE);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// macClearShortToLongAddressMappings
EmberStatus emberMacClearShortToLongAddressMappings(void)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_MAC_CLEAR_SHORT_TO_LONG_ADDRESS_MAPPINGS_IPC_COMMAND_ID,
                        "");
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// networkLeave
EmberStatus emberNetworkLeave(void)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_NETWORK_LEAVE_IPC_COMMAND_ID,
                        "");
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// networkInit
EmberStatus emberNetworkInit(void)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_NETWORK_INIT_IPC_COMMAND_ID,
                        "");
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// startActiveScan
EmberStatus emberStartActiveScan(uint16_t channel)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_START_ACTIVE_SCAN_IPC_COMMAND_ID,
                        "v",
                        channel);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// startEnergyScan
EmberStatus emberStartEnergyScan(uint16_t channel,
                                 uint8_t samples)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_START_ENERGY_SCAN_IPC_COMMAND_ID,
                        "vu",
                        channel,
                        samples);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// setApplicationBeaconPayload
EmberStatus emberSetApplicationBeaconPayload(uint8_t payloadLength,
                                             uint8_t *payload)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_SET_APPLICATION_BEACON_PAYLOAD_IPC_COMMAND_ID,
                        "b",
                        payload,
                        payloadLength);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// setSelectiveJoinPayload
EmberStatus emberSetSelectiveJoinPayload(uint8_t payloadLength,
                                         uint8_t *payload)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_SET_SELECTIVE_JOIN_PAYLOAD_IPC_COMMAND_ID,
                        "b",
                        payload,
                        payloadLength);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// clearSelectiveJoinPayload
EmberStatus emberClearSelectiveJoinPayload(void)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_CLEAR_SELECTIVE_JOIN_PAYLOAD_IPC_COMMAND_ID,
                        "");
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// formNetwork
EmberStatus emberFormNetwork(EmberNetworkParameters *parameters)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_FORM_NETWORK_IPC_COMMAND_ID,
                        "vvv",
                        parameters->panId,
                        parameters->radioTxPower,
                        parameters->radioChannel);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// joinNetworkExtended
EmberStatus emberJoinNetworkExtended(EmberNodeType nodeType,
                                     EmberNodeId nodeId,
                                     EmberNetworkParameters *parameters)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_JOIN_NETWORK_EXTENDED_IPC_COMMAND_ID,
                        "uvvvv",
                        nodeType,
                        nodeId,
                        parameters->panId,
                        parameters->radioTxPower,
                        parameters->radioChannel);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// joinNetwork
EmberStatus emberJoinNetwork(EmberNodeType nodeType,
                             EmberNetworkParameters *parameters)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_JOIN_NETWORK_IPC_COMMAND_ID,
                        "uvvv",
                        nodeType,
                        parameters->panId,
                        parameters->radioTxPower,
                        parameters->radioChannel);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// macFormNetwork
EmberStatus emberMacFormNetwork(EmberNetworkParameters *parameters)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_MAC_FORM_NETWORK_IPC_COMMAND_ID,
                        "vvv",
                        parameters->panId,
                        parameters->radioTxPower,
                        parameters->radioChannel);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// permitJoining
EmberStatus emberPermitJoining(uint8_t duration)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_PERMIT_JOINING_IPC_COMMAND_ID,
                        "u",
                        duration);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// joinCommissioned
EmberStatus emberJoinCommissioned(EmberNodeType nodeType,
                                  EmberNodeId nodeId,
                                  EmberNetworkParameters *parameters)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_JOIN_COMMISSIONED_IPC_COMMAND_ID,
                        "uvvvv",
                        nodeType,
                        nodeId,
                        parameters->panId,
                        parameters->radioTxPower,
                        parameters->radioChannel);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// resetNetworkState
void emberResetNetworkState(void)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_RESET_NETWORK_STATE_IPC_COMMAND_ID,
                        "");
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);
  releaseCommandMutex();
}

// frequencyHoppingSetChannelMask
EmberStatus emberFrequencyHoppingSetChannelMask(uint8_t channelMaskLength,
                                                uint8_t *channelMask)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_FREQUENCY_HOPPING_SET_CHANNEL_MASK_IPC_COMMAND_ID,
                        "b",
                        channelMask,
                        channelMaskLength);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// frequencyHoppingStartServer
EmberStatus emberFrequencyHoppingStartServer(void)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_FREQUENCY_HOPPING_START_SERVER_IPC_COMMAND_ID,
                        "");
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// frequencyHoppingStartClient
EmberStatus emberFrequencyHoppingStartClient(EmberNodeId serverNodeId,
                                             EmberPanId serverPanId)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_FREQUENCY_HOPPING_START_CLIENT_IPC_COMMAND_ID,
                        "vv",
                        serverNodeId,
                        serverPanId);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// frequencyHoppingStop
EmberStatus emberFrequencyHoppingStop(void)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_FREQUENCY_HOPPING_STOP_IPC_COMMAND_ID,
                        "");
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// setAuxiliaryAddressFilteringEntry
EmberStatus emberSetAuxiliaryAddressFilteringEntry(EmberNodeId nodeId,
                                                   uint8_t entryIndex)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_SET_AUXILIARY_ADDRESS_FILTERING_ENTRY_IPC_COMMAND_ID,
                        "vu",
                        nodeId,
                        entryIndex);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// getAuxiliaryAddressFilteringEntry
EmberNodeId emberGetAuxiliaryAddressFilteringEntry(uint8_t entryIndex)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_GET_AUXILIARY_ADDRESS_FILTERING_ENTRY_IPC_COMMAND_ID,
                        "u",
                        entryIndex);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberNodeId nodeId;
  fetchApiParams(apiCommandData,
                 "v",
                 &nodeId);
  releaseCommandMutex();
  return nodeId;
}

// startTxStream
EmberStatus emberStartTxStream(EmberTxStreamParameters parameters,
                               uint16_t channel)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_START_TX_STREAM_IPC_COMMAND_ID,
                        "uv",
                        parameters,
                        channel);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// stopTxStream
EmberStatus emberStopTxStream(void)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_STOP_TX_STREAM_IPC_COMMAND_ID,
                        "");
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// setActiveScanDuration
EmberStatus emberSetActiveScanDuration(uint16_t durationMs)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_SET_ACTIVE_SCAN_DURATION_IPC_COMMAND_ID,
                        "v",
                        durationMs);
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  EmberStatus status;
  fetchApiParams(apiCommandData,
                 "u",
                 &status);
  releaseCommandMutex();
  return status;
}

// getActiveScanDuration
uint16_t emberGetActiveScanDuration(void)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_GET_ACTIVE_SCAN_DURATION_IPC_COMMAND_ID,
                        "");
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  uint16_t durationMs;
  fetchApiParams(apiCommandData,
                 "v",
                 &durationMs);
  releaseCommandMutex();
  return durationMs;
}

// getDefaultChannel
uint16_t emberGetDefaultChannel(void)
{
  acquireCommandMutex();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  formatResponseCommand(apiCommandBuffer,
                        MAX_STACK_API_COMMAND_SIZE,
                        EMBER_GET_DEFAULT_CHANNEL_IPC_COMMAND_ID,
                        "");
  uint8_t *apiCommandData = sendBlockingCommand(apiCommandBuffer);

  uint16_t firstChannel;
  fetchApiParams(apiCommandData,
                 "v",
                 &firstChannel);
  releaseCommandMutex();
  return firstChannel;
}
