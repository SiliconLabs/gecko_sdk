/***************************************************************************//**
 * @brief NCP functions for sending Connect management commands to the Host.
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
#include "ncp/ncp-security.h"
#include "stack/core/sli-connect-api.h"

#include "csp-format.h"
#include "csp-command-utils.h"
#include "csp-api-enum-gen.h"

// networkState
static void networkStateCommandHandler(uint8_t *apiCommandData)
{
  EmberNetworkStatus networkStatus = emApiNetworkState();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_NETWORK_STATE_IPC_COMMAND_ID,
                                                 "u",
                                                 networkStatus);
  sendResponse(apiCommandBuffer, commandLength);
}

// stackIsUp
static void stackIsUpCommandHandler(uint8_t *apiCommandData)
{
  bool stackIsUp = emApiStackIsUp();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_STACK_IS_UP_IPC_COMMAND_ID,
                                                 "u",
                                                 stackIsUp);
  sendResponse(apiCommandBuffer, commandLength);
}

// setSecurityKey
static void setSecurityKeyCommandHandler(uint8_t *apiCommandData)
{
  EmberKeyData key;
  uint8_t emberEncryptionKeySize = EMBER_ENCRYPTION_KEY_SIZE;
  fetchApiParams(apiCommandData,
                 "b",
                 &key,
                 &emberEncryptionKeySize,
                 EMBER_ENCRYPTION_KEY_SIZE);
  EmberStatus status = emApiSetSecurityKey(&key);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_SET_SECURITY_KEY_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// GetSecurityKey
static void GetSecurityKeyCommandHandler(uint8_t *apiCommandData)
{
  EmberKeyData key;
  uint8_t emberEncryptionKeySize = EMBER_ENCRYPTION_KEY_SIZE;
  fetchApiParams(apiCommandData,
                 "b",
                 &key.contents,
                 &emberEncryptionKeySize,
                 EMBER_ENCRYPTION_KEY_SIZE);
  EmberStatus status = emApiGetSecurityKey(&key);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_GET_SECURITY_KEY_IPC_COMMAND_ID,
                                                 "ub",
                                                 status,
                                                 key.contents,
                                                 emberEncryptionKeySize);
  sendResponse(apiCommandBuffer, commandLength);
}

#ifdef SL_CATALOG_CONNECT_AES_SECURITY_PRESENT
// setPsaSecurityKey
static void setPsaSecurityKeyCommandHandler(uint8_t *apiCommandData)
{
  mbedtls_svc_key_id_t key_id;
  fetchApiParams(apiCommandData,
                 "w",
                 &key_id);
  EmberStatus status = emApiSetPsaSecurityKey(key_id);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_SET_PSA_SECURITY_KEY_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

#endif

#ifdef SL_CATALOG_CONNECT_AES_SECURITY_PRESENT
// RemovePsaSecurityKey
static void RemovePsaSecurityKeyCommandHandler(uint8_t *apiCommandData)
{
  EmberStatus status = emApiRemovePsaSecurityKey();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_REMOVE_PSA_SECURITY_KEY_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

#endif

// setNcpSecurityKeyPersistent
static void setNcpSecurityKeyPersistentCommandHandler(uint8_t *apiCommandData)
{
  uint8_t keyLength;
  uint32_t key_id;
  uint8_t *key;
  fetchApiParams(apiCommandData,
                 "pw",
                 &key,
                 &keyLength,
                 &key_id);
  EmberStatus status = emApiSetNcpSecurityKeyPersistent(key,
                                                        keyLength,
                                                        key_id);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_SET_NCP_SECURITY_KEY_PERSISTENT_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// setNcpSecurityKey
static void setNcpSecurityKeyCommandHandler(uint8_t *apiCommandData)
{
  uint8_t keyLength;
  uint8_t *key;
  fetchApiParams(apiCommandData,
                 "p",
                 &key,
                 &keyLength);
  EmberStatus status = emApiSetNcpSecurityKey(key,
                                              keyLength);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_SET_NCP_SECURITY_KEY_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

#ifdef SL_CATALOG_CONNECT_AES_SECURITY_PRESENT
// getKeyId
static void getKeyIdCommandHandler(uint8_t *apiCommandData)
{
  mbedtls_svc_key_id_t key_id = emApiGetKeyId();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_GET_KEY_ID_IPC_COMMAND_ID,
                                                 "w",
                                                 key_id);
  sendResponse(apiCommandBuffer, commandLength);
}

#endif

// getCounter
static void getCounterCommandHandler(uint8_t *apiCommandData)
{
  EmberCounterType counterType;
  uint32_t count;
  fetchApiParams(apiCommandData,
                 "u",
                 &counterType);
  EmberStatus status = emApiGetCounter(counterType,
                                       &count);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_GET_COUNTER_IPC_COMMAND_ID,
                                                 "uw",
                                                 status,
                                                 count);
  sendResponse(apiCommandBuffer, commandLength);
}

// setRadioChannelExtended
static void setRadioChannelExtendedCommandHandler(uint8_t *apiCommandData)
{
  uint16_t channel;
  bool persistent;
  fetchApiParams(apiCommandData,
                 "vu",
                 &channel,
                 &persistent);
  EmberStatus status = emApiSetRadioChannelExtended(channel,
                                                    persistent);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_SET_RADIO_CHANNEL_EXTENDED_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// setRadioChannel
static void setRadioChannelCommandHandler(uint8_t *apiCommandData)
{
  uint16_t channel;
  fetchApiParams(apiCommandData,
                 "v",
                 &channel);
  EmberStatus status = emApiSetRadioChannel(channel);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_SET_RADIO_CHANNEL_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// getRadioChannel
static void getRadioChannelCommandHandler(uint8_t *apiCommandData)
{
  uint16_t channel = emApiGetRadioChannel();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_GET_RADIO_CHANNEL_IPC_COMMAND_ID,
                                                 "v",
                                                 channel);
  sendResponse(apiCommandBuffer, commandLength);
}

// setRadioPower
static void setRadioPowerCommandHandler(uint8_t *apiCommandData)
{
  int16_t power;
  bool persistent;
  fetchApiParams(apiCommandData,
                 "vu",
                 &power,
                 &persistent);
  EmberStatus status = emApiSetRadioPower(power,
                                          persistent);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_SET_RADIO_POWER_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// getRadioPower
static void getRadioPowerCommandHandler(uint8_t *apiCommandData)
{
  int16_t power = emApiGetRadioPower();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_GET_RADIO_POWER_IPC_COMMAND_ID,
                                                 "v",
                                                 power);
  sendResponse(apiCommandBuffer, commandLength);
}

// setRadioPowerMode
static void setRadioPowerModeCommandHandler(uint8_t *apiCommandData)
{
  bool radioOn;
  fetchApiParams(apiCommandData,
                 "u",
                 &radioOn);
  EmberStatus status = emApiSetRadioPowerMode(radioOn);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_SET_RADIO_POWER_MODE_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// setMacParams
static void setMacParamsCommandHandler(uint8_t *apiCommandData)
{
  int8_t ccaThreshold;
  uint8_t maxCcaAttempts;
  uint8_t minBackoffExp;
  uint8_t maxBackoffExp;
  uint16_t ccaBackoff;
  uint16_t ccaDuration;
  uint8_t maxRetries;
  uint32_t csmaTimeout;
  uint16_t ackTimeout;
  fetchApiParams(apiCommandData,
                 "suuuvvuwv",
                 &ccaThreshold,
                 &maxCcaAttempts,
                 &minBackoffExp,
                 &maxBackoffExp,
                 &ccaBackoff,
                 &ccaDuration,
                 &maxRetries,
                 &csmaTimeout,
                 &ackTimeout);
  EmberStatus status = emApiSetMacParams(ccaThreshold,
                                         maxCcaAttempts,
                                         minBackoffExp,
                                         maxBackoffExp,
                                         ccaBackoff,
                                         ccaDuration,
                                         maxRetries,
                                         csmaTimeout,
                                         ackTimeout);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_SET_MAC_PARAMS_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// currentStackTasks
static void currentStackTasksCommandHandler(uint8_t *apiCommandData)
{
  uint16_t currentTasks = emApiCurrentStackTasks();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_CURRENT_STACK_TASKS_IPC_COMMAND_ID,
                                                 "v",
                                                 currentTasks);
  sendResponse(apiCommandBuffer, commandLength);
}

// okToNap
static void okToNapCommandHandler(uint8_t *apiCommandData)
{
  bool isOkToNap = emApiOkToNap();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_OK_TO_NAP_IPC_COMMAND_ID,
                                                 "u",
                                                 isOkToNap);
  sendResponse(apiCommandBuffer, commandLength);
}

// okToHibernate
static void okToHibernateCommandHandler(uint8_t *apiCommandData)
{
  bool isOkToHibernate = emApiOkToHibernate();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_OK_TO_HIBERNATE_IPC_COMMAND_ID,
                                                 "u",
                                                 isOkToHibernate);
  sendResponse(apiCommandBuffer, commandLength);
}

// getEui64
static void getEui64CommandHandler(uint8_t *apiCommandData)
{
  uint8_t eui64Size = EUI64_SIZE;
  uint8_t* eui64 = emApiGetEui64();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_GET_EUI64_IPC_COMMAND_ID,
                                                 "b",
                                                 eui64,
                                                 eui64Size);
  sendResponse(apiCommandBuffer, commandLength);
}

// macGetParentAddress
static void macGetParentAddressCommandHandler(uint8_t *apiCommandData)
{
  EmberMacAddress parentAddress;
  uint8_t eui64Size = EUI64_SIZE;
  fetchApiParams(apiCommandData,
                 "vbu",
                 &parentAddress.addr.shortAddress,
                 &parentAddress.addr.longAddress,
                 &eui64Size,
                 EUI64_SIZE,
                 &parentAddress.mode);
  EmberStatus status = emApiMacGetParentAddress(&parentAddress);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_MAC_GET_PARENT_ADDRESS_IPC_COMMAND_ID,
                                                 "uvbu",
                                                 status,
                                                 parentAddress.addr.shortAddress,
                                                 parentAddress.addr.longAddress,
                                                 eui64Size,
                                                 parentAddress.mode);
  sendResponse(apiCommandBuffer, commandLength);
}

// isLocalEui64
static void isLocalEui64CommandHandler(uint8_t *apiCommandData)
{
  uint8_t eui64[EUI64_SIZE];
  uint8_t eui64Size = EUI64_SIZE;
  fetchApiParams(apiCommandData,
                 "b",
                 &eui64,
                 &eui64Size,
                 EUI64_SIZE);
  bool localEui64 = emApiIsLocalEui64(eui64);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_IS_LOCAL_EUI64_IPC_COMMAND_ID,
                                                 "u",
                                                 localEui64);
  sendResponse(apiCommandBuffer, commandLength);
}

// getNodeId
static void getNodeIdCommandHandler(uint8_t *apiCommandData)
{
  EmberNodeId nodeId = emApiGetNodeId();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_GET_NODE_ID_IPC_COMMAND_ID,
                                                 "v",
                                                 nodeId);
  sendResponse(apiCommandBuffer, commandLength);
}

// getPanId
static void getPanIdCommandHandler(uint8_t *apiCommandData)
{
  EmberPanId panId = emApiGetPanId();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_GET_PAN_ID_IPC_COMMAND_ID,
                                                 "v",
                                                 panId);
  sendResponse(apiCommandBuffer, commandLength);
}

// getParentId
static void getParentIdCommandHandler(uint8_t *apiCommandData)
{
  EmberNodeId parentNodeId = emApiGetParentId();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_GET_PARENT_ID_IPC_COMMAND_ID,
                                                 "v",
                                                 parentNodeId);
  sendResponse(apiCommandBuffer, commandLength);
}

// getNodeType
static void getNodeTypeCommandHandler(uint8_t *apiCommandData)
{
  EmberNodeType nodeType = emApiGetNodeType();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_GET_NODE_TYPE_IPC_COMMAND_ID,
                                                 "u",
                                                 nodeType);
  sendResponse(apiCommandBuffer, commandLength);
}

// calibrateCurrentChannel
static void calibrateCurrentChannelCommandHandler(uint8_t *apiCommandData)
{
  EmberStatus status = emApiCalibrateCurrentChannel();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_CALIBRATE_CURRENT_CHANNEL_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// calibrateCurrentChannelExtended
static void calibrateCurrentChannelExtendedCommandHandler(uint8_t *apiCommandData)
{
  uint32_t calValueIn;
  uint32_t calValueOut;
  fetchApiParams(apiCommandData,
                 "w",
                 &calValueIn);
  EmberStatus status = emApiCalibrateCurrentChannelExtended(calValueIn,
                                                            &calValueOut);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_CALIBRATE_CURRENT_CHANNEL_EXTENDED_IPC_COMMAND_ID,
                                                 "uw",
                                                 status,
                                                 calValueOut);
  sendResponse(apiCommandBuffer, commandLength);
}

// applyIrCalibration
static void applyIrCalibrationCommandHandler(uint8_t *apiCommandData)
{
  uint32_t calValue;
  fetchApiParams(apiCommandData,
                 "w",
                 &calValue);
  EmberStatus status = emApiApplyIrCalibration(calValue);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_APPLY_IR_CALIBRATION_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// tempCalibration
static void tempCalibrationCommandHandler(uint8_t *apiCommandData)
{
  EmberStatus status = emApiTempCalibration();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_TEMP_CALIBRATION_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// getCalType
static void getCalTypeCommandHandler(uint8_t *apiCommandData)
{
  EmberCalType calType = emApiGetCalType();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_GET_CAL_TYPE_IPC_COMMAND_ID,
                                                 "w",
                                                 calType);
  sendResponse(apiCommandBuffer, commandLength);
}

// getMaximumPayloadLength
static void getMaximumPayloadLengthCommandHandler(uint8_t *apiCommandData)
{
  EmberMacAddressMode srcAddressMode;
  EmberMacAddressMode dstAddressMode;
  bool interpan;
  bool secured;
  fetchApiParams(apiCommandData,
                 "uuuu",
                 &srcAddressMode,
                 &dstAddressMode,
                 &interpan,
                 &secured);
  uint8_t payloadLength = emApiGetMaximumPayloadLength(srcAddressMode,
                                                       dstAddressMode,
                                                       interpan,
                                                       secured);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_GET_MAXIMUM_PAYLOAD_LENGTH_IPC_COMMAND_ID,
                                                 "u",
                                                 payloadLength);
  sendResponse(apiCommandBuffer, commandLength);
}

// setIndirectQueueTimeout
static void setIndirectQueueTimeoutCommandHandler(uint8_t *apiCommandData)
{
  uint32_t timeoutMs;
  fetchApiParams(apiCommandData,
                 "w",
                 &timeoutMs);
  EmberStatus status = emApiSetIndirectQueueTimeout(timeoutMs);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_SET_INDIRECT_QUEUE_TIMEOUT_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// getVersionInfo
static void getVersionInfoCommandHandler(uint8_t *apiCommandData)
{
  uint16_t gsdkVersion;
  uint16_t connectStackVersion;
  uint32_t bootloaderVersion;
  fetchApiParams(apiCommandData,
                 "");
  EmberStatus status = emApiGetVersionInfo(&gsdkVersion,
                                           &connectStackVersion,
                                           &bootloaderVersion);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_GET_VERSION_INFO_IPC_COMMAND_ID,
                                                 "uvvw",
                                                 status,
                                                 gsdkVersion,
                                                 connectStackVersion,
                                                 bootloaderVersion);
  sendResponse(apiCommandBuffer, commandLength);
}

// messageSend
static void messageSendCommandHandler(uint8_t *apiCommandData)
{
  EmberNodeId destination;
  uint8_t endpoint;
  uint8_t messageTag;
  EmberMessageLength messageLength;
  EmberMessageOptions options;
  uint8_t *message;
  fetchApiParams(apiCommandData,
                 "vuuupu",
                 &destination,
                 &endpoint,
                 &messageTag,
                 &messageLength,
                 &message,
                 &messageLength,
                 &options);
  EmberStatus status = emApiMessageSend(destination,
                                        endpoint,
                                        messageTag,
                                        messageLength,
                                        message,
                                        options);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_MESSAGE_SEND_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// pollForData
static void pollForDataCommandHandler(uint8_t *apiCommandData)
{
  EmberStatus status = emApiPollForData();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_POLL_FOR_DATA_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// macMessageSend
static void macMessageSendCommandHandler(uint8_t *apiCommandData)
{
  EmberMacFrame macFrame;
  uint8_t messageTag;
  EmberMessageLength messageLength;
  EmberMessageOptions options;
  uint8_t eui64Size = EUI64_SIZE;
  uint8_t *message;
  fetchApiParams(apiCommandData,
                 "vbuvbuvvuuuupu",
                 &macFrame.srcAddress.addr.shortAddress,
                 &macFrame.srcAddress.addr.longAddress,
                 &eui64Size,
                 EUI64_SIZE,
                 &macFrame.srcAddress.mode,
                 &macFrame.dstAddress.addr.shortAddress,
                 &macFrame.dstAddress.addr.longAddress,
                 &eui64Size,
                 EUI64_SIZE,
                 &macFrame.dstAddress.mode,
                 &macFrame.srcPanId,
                 &macFrame.dstPanId,
                 &macFrame.srcPanIdSpecified,
                 &macFrame.dstPanIdSpecified,
                 &messageTag,
                 &messageLength,
                 &message,
                 &messageLength,
                 &options);
  EmberStatus status = emApiMacMessageSend(&macFrame,
                                           messageTag,
                                           messageLength,
                                           message,
                                           options);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_MAC_MESSAGE_SEND_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// macSetPanCoordinator
static void macSetPanCoordinatorCommandHandler(uint8_t *apiCommandData)
{
  bool isCoordinator;
  fetchApiParams(apiCommandData,
                 "u",
                 &isCoordinator);
  EmberStatus status = emApiMacSetPanCoordinator(isCoordinator);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_MAC_SET_PAN_COORDINATOR_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// setPollDestinationAddress
static void setPollDestinationAddressCommandHandler(uint8_t *apiCommandData)
{
  EmberMacAddress destination;
  uint8_t eui64Size = EUI64_SIZE;
  fetchApiParams(apiCommandData,
                 "vbu",
                 &destination.addr.shortAddress,
                 &destination.addr.longAddress,
                 &eui64Size,
                 EUI64_SIZE,
                 &destination.mode);
  EmberStatus status = emApiSetPollDestinationAddress(&destination);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_SET_POLL_DESTINATION_ADDRESS_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// removeChild
static void removeChildCommandHandler(uint8_t *apiCommandData)
{
  EmberMacAddress address;
  uint8_t eui64Size = EUI64_SIZE;
  fetchApiParams(apiCommandData,
                 "vbu",
                 &address.addr.shortAddress,
                 &address.addr.longAddress,
                 &eui64Size,
                 EUI64_SIZE,
                 &address.mode);
  EmberStatus status = emApiRemoveChild(&address);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_REMOVE_CHILD_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// getChildFlags
static void getChildFlagsCommandHandler(uint8_t *apiCommandData)
{
  EmberMacAddress address;
  EmberChildFlags flags;
  uint8_t eui64Size = EUI64_SIZE;
  fetchApiParams(apiCommandData,
                 "vbu",
                 &address.addr.shortAddress,
                 &address.addr.longAddress,
                 &eui64Size,
                 EUI64_SIZE,
                 &address.mode);
  EmberStatus status = emApiGetChildFlags(&address,
                                          &flags);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_GET_CHILD_FLAGS_IPC_COMMAND_ID,
                                                 "uu",
                                                 status,
                                                 flags);
  sendResponse(apiCommandBuffer, commandLength);
}

// getChildInfo
static void getChildInfoCommandHandler(uint8_t *apiCommandData)
{
  EmberMacAddress address;
  EmberMacAddress addressResp;
  EmberChildFlags flags;
  uint8_t eui64Size = EUI64_SIZE;
  fetchApiParams(apiCommandData,
                 "vbu",
                 &address.addr.shortAddress,
                 &address.addr.longAddress,
                 &eui64Size,
                 EUI64_SIZE,
                 &address.mode);
  EmberStatus status = emApiGetChildInfo(&address,
                                         &addressResp,
                                         &flags);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_GET_CHILD_INFO_IPC_COMMAND_ID,
                                                 "uvbuu",
                                                 status,
                                                 addressResp.addr.shortAddress,
                                                 addressResp.addr.longAddress,
                                                 eui64Size,
                                                 address.mode,
                                                 flags);
  sendResponse(apiCommandBuffer, commandLength);
}

// purgeIndirectMessages
static void purgeIndirectMessagesCommandHandler(uint8_t *apiCommandData)
{
  EmberStatus status = emApiPurgeIndirectMessages();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_PURGE_INDIRECT_MESSAGES_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// macAddShortToLongAddressMapping
static void macAddShortToLongAddressMappingCommandHandler(uint8_t *apiCommandData)
{
  EmberNodeId shortId;
  uint8_t longId[EUI64_SIZE];
  uint8_t eui64Size = EUI64_SIZE;
  fetchApiParams(apiCommandData,
                 "vb",
                 &shortId,
                 &longId,
                 &eui64Size,
                 EUI64_SIZE);
  EmberStatus status = emApiMacAddShortToLongAddressMapping(shortId,
                                                            longId);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_MAC_ADD_SHORT_TO_LONG_ADDRESS_MAPPING_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// macClearShortToLongAddressMappings
static void macClearShortToLongAddressMappingsCommandHandler(uint8_t *apiCommandData)
{
  EmberStatus status = emApiMacClearShortToLongAddressMappings();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_MAC_CLEAR_SHORT_TO_LONG_ADDRESS_MAPPINGS_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// networkLeave
static void networkLeaveCommandHandler(uint8_t *apiCommandData)
{
  EmberStatus status = emApiNetworkLeave();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_NETWORK_LEAVE_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// networkInit
static void networkInitCommandHandler(uint8_t *apiCommandData)
{
  EmberStatus status = emApiNetworkInit();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_NETWORK_INIT_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// startActiveScan
static void startActiveScanCommandHandler(uint8_t *apiCommandData)
{
  uint16_t channel;
  fetchApiParams(apiCommandData,
                 "v",
                 &channel);
  EmberStatus status = emApiStartActiveScan(channel);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_START_ACTIVE_SCAN_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// startEnergyScan
static void startEnergyScanCommandHandler(uint8_t *apiCommandData)
{
  uint16_t channel;
  uint8_t samples;
  fetchApiParams(apiCommandData,
                 "vu",
                 &channel,
                 &samples);
  EmberStatus status = emApiStartEnergyScan(channel,
                                            samples);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_START_ENERGY_SCAN_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// setApplicationBeaconPayload
static void setApplicationBeaconPayloadCommandHandler(uint8_t *apiCommandData)
{
  uint8_t payloadLength;
  uint8_t *payload;
  fetchApiParams(apiCommandData,
                 "p",
                 &payload,
                 &payloadLength);
  EmberStatus status = emApiSetApplicationBeaconPayload(payloadLength,
                                                        payload);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_SET_APPLICATION_BEACON_PAYLOAD_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// setSelectiveJoinPayload
static void setSelectiveJoinPayloadCommandHandler(uint8_t *apiCommandData)
{
  uint8_t payloadLength;
  uint8_t *payload;
  fetchApiParams(apiCommandData,
                 "p",
                 &payload,
                 &payloadLength);
  EmberStatus status = emApiSetSelectiveJoinPayload(payloadLength,
                                                    payload);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_SET_SELECTIVE_JOIN_PAYLOAD_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// clearSelectiveJoinPayload
static void clearSelectiveJoinPayloadCommandHandler(uint8_t *apiCommandData)
{
  EmberStatus status = emApiClearSelectiveJoinPayload();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_CLEAR_SELECTIVE_JOIN_PAYLOAD_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// formNetwork
static void formNetworkCommandHandler(uint8_t *apiCommandData)
{
  EmberNetworkParameters parameters;
  fetchApiParams(apiCommandData,
                 "vvv",
                 &parameters.panId,
                 &parameters.radioTxPower,
                 &parameters.radioChannel);
  EmberStatus status = emApiFormNetwork(&parameters);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_FORM_NETWORK_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// joinNetworkExtended
static void joinNetworkExtendedCommandHandler(uint8_t *apiCommandData)
{
  EmberNodeType nodeType;
  EmberNodeId nodeId;
  EmberNetworkParameters parameters;
  fetchApiParams(apiCommandData,
                 "uvvvv",
                 &nodeType,
                 &nodeId,
                 &parameters.panId,
                 &parameters.radioTxPower,
                 &parameters.radioChannel);
  EmberStatus status = emApiJoinNetworkExtended(nodeType,
                                                nodeId,
                                                &parameters);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_JOIN_NETWORK_EXTENDED_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// joinNetwork
static void joinNetworkCommandHandler(uint8_t *apiCommandData)
{
  EmberNodeType nodeType;
  EmberNetworkParameters parameters;
  fetchApiParams(apiCommandData,
                 "uvvv",
                 &nodeType,
                 &parameters.panId,
                 &parameters.radioTxPower,
                 &parameters.radioChannel);
  EmberStatus status = emApiJoinNetwork(nodeType,
                                        &parameters);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_JOIN_NETWORK_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// macFormNetwork
static void macFormNetworkCommandHandler(uint8_t *apiCommandData)
{
  EmberNetworkParameters parameters;
  fetchApiParams(apiCommandData,
                 "vvv",
                 &parameters.panId,
                 &parameters.radioTxPower,
                 &parameters.radioChannel);
  EmberStatus status = emApiMacFormNetwork(&parameters);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_MAC_FORM_NETWORK_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// permitJoining
static void permitJoiningCommandHandler(uint8_t *apiCommandData)
{
  uint8_t duration;
  fetchApiParams(apiCommandData,
                 "u",
                 &duration);
  EmberStatus status = emApiPermitJoining(duration);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_PERMIT_JOINING_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// joinCommissioned
static void joinCommissionedCommandHandler(uint8_t *apiCommandData)
{
  EmberNodeType nodeType;
  EmberNodeId nodeId;
  EmberNetworkParameters parameters;
  fetchApiParams(apiCommandData,
                 "uvvvv",
                 &nodeType,
                 &nodeId,
                 &parameters.panId,
                 &parameters.radioTxPower,
                 &parameters.radioChannel);
  EmberStatus status = emApiJoinCommissioned(nodeType,
                                             nodeId,
                                             &parameters);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_JOIN_COMMISSIONED_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// resetNetworkState
static void resetNetworkStateCommandHandler(uint8_t *apiCommandData)
{
  emApiResetNetworkState();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_RESET_NETWORK_STATE_IPC_COMMAND_ID,
                                                 "");
  sendResponse(apiCommandBuffer, commandLength);
}

// frequencyHoppingSetChannelMask
static void frequencyHoppingSetChannelMaskCommandHandler(uint8_t *apiCommandData)
{
  uint8_t channelMaskLength;
  uint8_t *channelMask;
  fetchApiParams(apiCommandData,
                 "p",
                 &channelMask,
                 &channelMaskLength);
  EmberStatus status = emApiFrequencyHoppingSetChannelMask(channelMaskLength,
                                                           channelMask);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_FREQUENCY_HOPPING_SET_CHANNEL_MASK_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// frequencyHoppingStartServer
static void frequencyHoppingStartServerCommandHandler(uint8_t *apiCommandData)
{
  EmberStatus status = emApiFrequencyHoppingStartServer();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_FREQUENCY_HOPPING_START_SERVER_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// frequencyHoppingStartClient
static void frequencyHoppingStartClientCommandHandler(uint8_t *apiCommandData)
{
  EmberNodeId serverNodeId;
  EmberPanId serverPanId;
  fetchApiParams(apiCommandData,
                 "vv",
                 &serverNodeId,
                 &serverPanId);
  EmberStatus status = emApiFrequencyHoppingStartClient(serverNodeId,
                                                        serverPanId);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_FREQUENCY_HOPPING_START_CLIENT_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// frequencyHoppingStop
static void frequencyHoppingStopCommandHandler(uint8_t *apiCommandData)
{
  EmberStatus status = emApiFrequencyHoppingStop();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_FREQUENCY_HOPPING_STOP_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// setAuxiliaryAddressFilteringEntry
static void setAuxiliaryAddressFilteringEntryCommandHandler(uint8_t *apiCommandData)
{
  EmberNodeId nodeId;
  uint8_t entryIndex;
  fetchApiParams(apiCommandData,
                 "vu",
                 &nodeId,
                 &entryIndex);
  EmberStatus status = emApiSetAuxiliaryAddressFilteringEntry(nodeId,
                                                              entryIndex);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_SET_AUXILIARY_ADDRESS_FILTERING_ENTRY_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// getAuxiliaryAddressFilteringEntry
static void getAuxiliaryAddressFilteringEntryCommandHandler(uint8_t *apiCommandData)
{
  uint8_t entryIndex;
  fetchApiParams(apiCommandData,
                 "u",
                 &entryIndex);
  EmberNodeId nodeId = emApiGetAuxiliaryAddressFilteringEntry(entryIndex);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_GET_AUXILIARY_ADDRESS_FILTERING_ENTRY_IPC_COMMAND_ID,
                                                 "v",
                                                 nodeId);
  sendResponse(apiCommandBuffer, commandLength);
}

// startTxStream
static void startTxStreamCommandHandler(uint8_t *apiCommandData)
{
  EmberTxStreamParameters parameters;
  uint16_t channel;
  fetchApiParams(apiCommandData,
                 "uv",
                 &parameters,
                 &channel);
  EmberStatus status = emApiStartTxStream(parameters,
                                          channel);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_START_TX_STREAM_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// stopTxStream
static void stopTxStreamCommandHandler(uint8_t *apiCommandData)
{
  EmberStatus status = emApiStopTxStream();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_STOP_TX_STREAM_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// setActiveScanDuration
static void setActiveScanDurationCommandHandler(uint8_t *apiCommandData)
{
  uint16_t durationMs;
  fetchApiParams(apiCommandData,
                 "v",
                 &durationMs);
  EmberStatus status = emApiSetActiveScanDuration(durationMs);
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_SET_ACTIVE_SCAN_DURATION_IPC_COMMAND_ID,
                                                 "u",
                                                 status);
  sendResponse(apiCommandBuffer, commandLength);
}

// getActiveScanDuration
static void getActiveScanDurationCommandHandler(uint8_t *apiCommandData)
{
  uint16_t durationMs = emApiGetActiveScanDuration();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_GET_ACTIVE_SCAN_DURATION_IPC_COMMAND_ID,
                                                 "v",
                                                 durationMs);
  sendResponse(apiCommandBuffer, commandLength);
}

// getDefaultChannel
static void getDefaultChannelCommandHandler(uint8_t *apiCommandData)
{
  uint16_t firstChannel = emApiGetDefaultChannel();
  uint8_t *apiCommandBuffer = getApiCommandPointer();
  uint16_t commandLength = formatResponseCommand(apiCommandBuffer,
                                                 MAX_STACK_API_COMMAND_SIZE,
                                                 EMBER_GET_DEFAULT_CHANNEL_IPC_COMMAND_ID,
                                                 "v",
                                                 firstChannel);
  sendResponse(apiCommandBuffer, commandLength);
}

//------------------------------------------------------------------------------
// Callback command dispatcher (Application side)

void handleIncomingApiCommand(uint16_t commandId, uint8_t *apiCommandData)
{
  assert(isCurrentTaskStackTask());

  switch (commandId) {
    case EMBER_NETWORK_STATE_IPC_COMMAND_ID:
      networkStateCommandHandler(apiCommandData);
      break;
    case EMBER_STACK_IS_UP_IPC_COMMAND_ID:
      stackIsUpCommandHandler(apiCommandData);
      break;
    case EMBER_SET_SECURITY_KEY_IPC_COMMAND_ID:
      setSecurityKeyCommandHandler(apiCommandData);
      break;
    case EMBER_GET_SECURITY_KEY_IPC_COMMAND_ID:
      GetSecurityKeyCommandHandler(apiCommandData);
      break;

#ifdef SL_CATALOG_CONNECT_AES_SECURITY_PRESENT
    case EMBER_SET_PSA_SECURITY_KEY_IPC_COMMAND_ID:
      setPsaSecurityKeyCommandHandler(apiCommandData);
      break;
#endif

#ifdef SL_CATALOG_CONNECT_AES_SECURITY_PRESENT
    case EMBER_REMOVE_PSA_SECURITY_KEY_IPC_COMMAND_ID:
      RemovePsaSecurityKeyCommandHandler(apiCommandData);
      break;
#endif
    case EMBER_SET_NCP_SECURITY_KEY_PERSISTENT_IPC_COMMAND_ID:
      setNcpSecurityKeyPersistentCommandHandler(apiCommandData);
      break;
    case EMBER_SET_NCP_SECURITY_KEY_IPC_COMMAND_ID:
      setNcpSecurityKeyCommandHandler(apiCommandData);
      break;

#ifdef SL_CATALOG_CONNECT_AES_SECURITY_PRESENT
    case EMBER_GET_KEY_ID_IPC_COMMAND_ID:
      getKeyIdCommandHandler(apiCommandData);
      break;
#endif
    case EMBER_GET_COUNTER_IPC_COMMAND_ID:
      getCounterCommandHandler(apiCommandData);
      break;
    case EMBER_SET_RADIO_CHANNEL_EXTENDED_IPC_COMMAND_ID:
      setRadioChannelExtendedCommandHandler(apiCommandData);
      break;
    case EMBER_SET_RADIO_CHANNEL_IPC_COMMAND_ID:
      setRadioChannelCommandHandler(apiCommandData);
      break;
    case EMBER_GET_RADIO_CHANNEL_IPC_COMMAND_ID:
      getRadioChannelCommandHandler(apiCommandData);
      break;
    case EMBER_SET_RADIO_POWER_IPC_COMMAND_ID:
      setRadioPowerCommandHandler(apiCommandData);
      break;
    case EMBER_GET_RADIO_POWER_IPC_COMMAND_ID:
      getRadioPowerCommandHandler(apiCommandData);
      break;
    case EMBER_SET_RADIO_POWER_MODE_IPC_COMMAND_ID:
      setRadioPowerModeCommandHandler(apiCommandData);
      break;
    case EMBER_SET_MAC_PARAMS_IPC_COMMAND_ID:
      setMacParamsCommandHandler(apiCommandData);
      break;
    case EMBER_CURRENT_STACK_TASKS_IPC_COMMAND_ID:
      currentStackTasksCommandHandler(apiCommandData);
      break;
    case EMBER_OK_TO_NAP_IPC_COMMAND_ID:
      okToNapCommandHandler(apiCommandData);
      break;
    case EMBER_OK_TO_HIBERNATE_IPC_COMMAND_ID:
      okToHibernateCommandHandler(apiCommandData);
      break;
    case EMBER_GET_EUI64_IPC_COMMAND_ID:
      getEui64CommandHandler(apiCommandData);
      break;
    case EMBER_MAC_GET_PARENT_ADDRESS_IPC_COMMAND_ID:
      macGetParentAddressCommandHandler(apiCommandData);
      break;
    case EMBER_IS_LOCAL_EUI64_IPC_COMMAND_ID:
      isLocalEui64CommandHandler(apiCommandData);
      break;
    case EMBER_GET_NODE_ID_IPC_COMMAND_ID:
      getNodeIdCommandHandler(apiCommandData);
      break;
    case EMBER_GET_PAN_ID_IPC_COMMAND_ID:
      getPanIdCommandHandler(apiCommandData);
      break;
    case EMBER_GET_PARENT_ID_IPC_COMMAND_ID:
      getParentIdCommandHandler(apiCommandData);
      break;
    case EMBER_GET_NODE_TYPE_IPC_COMMAND_ID:
      getNodeTypeCommandHandler(apiCommandData);
      break;
    case EMBER_CALIBRATE_CURRENT_CHANNEL_IPC_COMMAND_ID:
      calibrateCurrentChannelCommandHandler(apiCommandData);
      break;
    case EMBER_CALIBRATE_CURRENT_CHANNEL_EXTENDED_IPC_COMMAND_ID:
      calibrateCurrentChannelExtendedCommandHandler(apiCommandData);
      break;
    case EMBER_APPLY_IR_CALIBRATION_IPC_COMMAND_ID:
      applyIrCalibrationCommandHandler(apiCommandData);
      break;
    case EMBER_TEMP_CALIBRATION_IPC_COMMAND_ID:
      tempCalibrationCommandHandler(apiCommandData);
      break;
    case EMBER_GET_CAL_TYPE_IPC_COMMAND_ID:
      getCalTypeCommandHandler(apiCommandData);
      break;
    case EMBER_GET_MAXIMUM_PAYLOAD_LENGTH_IPC_COMMAND_ID:
      getMaximumPayloadLengthCommandHandler(apiCommandData);
      break;
    case EMBER_SET_INDIRECT_QUEUE_TIMEOUT_IPC_COMMAND_ID:
      setIndirectQueueTimeoutCommandHandler(apiCommandData);
      break;
    case EMBER_GET_VERSION_INFO_IPC_COMMAND_ID:
      getVersionInfoCommandHandler(apiCommandData);
      break;
    case EMBER_MESSAGE_SEND_IPC_COMMAND_ID:
      messageSendCommandHandler(apiCommandData);
      break;
    case EMBER_POLL_FOR_DATA_IPC_COMMAND_ID:
      pollForDataCommandHandler(apiCommandData);
      break;
    case EMBER_MAC_MESSAGE_SEND_IPC_COMMAND_ID:
      macMessageSendCommandHandler(apiCommandData);
      break;
    case EMBER_MAC_SET_PAN_COORDINATOR_IPC_COMMAND_ID:
      macSetPanCoordinatorCommandHandler(apiCommandData);
      break;
    case EMBER_SET_POLL_DESTINATION_ADDRESS_IPC_COMMAND_ID:
      setPollDestinationAddressCommandHandler(apiCommandData);
      break;
    case EMBER_REMOVE_CHILD_IPC_COMMAND_ID:
      removeChildCommandHandler(apiCommandData);
      break;
    case EMBER_GET_CHILD_FLAGS_IPC_COMMAND_ID:
      getChildFlagsCommandHandler(apiCommandData);
      break;
    case EMBER_GET_CHILD_INFO_IPC_COMMAND_ID:
      getChildInfoCommandHandler(apiCommandData);
      break;
    case EMBER_PURGE_INDIRECT_MESSAGES_IPC_COMMAND_ID:
      purgeIndirectMessagesCommandHandler(apiCommandData);
      break;
    case EMBER_MAC_ADD_SHORT_TO_LONG_ADDRESS_MAPPING_IPC_COMMAND_ID:
      macAddShortToLongAddressMappingCommandHandler(apiCommandData);
      break;
    case EMBER_MAC_CLEAR_SHORT_TO_LONG_ADDRESS_MAPPINGS_IPC_COMMAND_ID:
      macClearShortToLongAddressMappingsCommandHandler(apiCommandData);
      break;
    case EMBER_NETWORK_LEAVE_IPC_COMMAND_ID:
      networkLeaveCommandHandler(apiCommandData);
      break;
    case EMBER_NETWORK_INIT_IPC_COMMAND_ID:
      networkInitCommandHandler(apiCommandData);
      break;
    case EMBER_START_ACTIVE_SCAN_IPC_COMMAND_ID:
      startActiveScanCommandHandler(apiCommandData);
      break;
    case EMBER_START_ENERGY_SCAN_IPC_COMMAND_ID:
      startEnergyScanCommandHandler(apiCommandData);
      break;
    case EMBER_SET_APPLICATION_BEACON_PAYLOAD_IPC_COMMAND_ID:
      setApplicationBeaconPayloadCommandHandler(apiCommandData);
      break;
    case EMBER_SET_SELECTIVE_JOIN_PAYLOAD_IPC_COMMAND_ID:
      setSelectiveJoinPayloadCommandHandler(apiCommandData);
      break;
    case EMBER_CLEAR_SELECTIVE_JOIN_PAYLOAD_IPC_COMMAND_ID:
      clearSelectiveJoinPayloadCommandHandler(apiCommandData);
      break;
    case EMBER_FORM_NETWORK_IPC_COMMAND_ID:
      formNetworkCommandHandler(apiCommandData);
      break;
    case EMBER_JOIN_NETWORK_EXTENDED_IPC_COMMAND_ID:
      joinNetworkExtendedCommandHandler(apiCommandData);
      break;
    case EMBER_JOIN_NETWORK_IPC_COMMAND_ID:
      joinNetworkCommandHandler(apiCommandData);
      break;
    case EMBER_MAC_FORM_NETWORK_IPC_COMMAND_ID:
      macFormNetworkCommandHandler(apiCommandData);
      break;
    case EMBER_PERMIT_JOINING_IPC_COMMAND_ID:
      permitJoiningCommandHandler(apiCommandData);
      break;
    case EMBER_JOIN_COMMISSIONED_IPC_COMMAND_ID:
      joinCommissionedCommandHandler(apiCommandData);
      break;
    case EMBER_RESET_NETWORK_STATE_IPC_COMMAND_ID:
      resetNetworkStateCommandHandler(apiCommandData);
      break;
    case EMBER_FREQUENCY_HOPPING_SET_CHANNEL_MASK_IPC_COMMAND_ID:
      frequencyHoppingSetChannelMaskCommandHandler(apiCommandData);
      break;
    case EMBER_FREQUENCY_HOPPING_START_SERVER_IPC_COMMAND_ID:
      frequencyHoppingStartServerCommandHandler(apiCommandData);
      break;
    case EMBER_FREQUENCY_HOPPING_START_CLIENT_IPC_COMMAND_ID:
      frequencyHoppingStartClientCommandHandler(apiCommandData);
      break;
    case EMBER_FREQUENCY_HOPPING_STOP_IPC_COMMAND_ID:
      frequencyHoppingStopCommandHandler(apiCommandData);
      break;
    case EMBER_SET_AUXILIARY_ADDRESS_FILTERING_ENTRY_IPC_COMMAND_ID:
      setAuxiliaryAddressFilteringEntryCommandHandler(apiCommandData);
      break;
    case EMBER_GET_AUXILIARY_ADDRESS_FILTERING_ENTRY_IPC_COMMAND_ID:
      getAuxiliaryAddressFilteringEntryCommandHandler(apiCommandData);
      break;
    case EMBER_START_TX_STREAM_IPC_COMMAND_ID:
      startTxStreamCommandHandler(apiCommandData);
      break;
    case EMBER_STOP_TX_STREAM_IPC_COMMAND_ID:
      stopTxStreamCommandHandler(apiCommandData);
      break;
    case EMBER_SET_ACTIVE_SCAN_DURATION_IPC_COMMAND_ID:
      setActiveScanDurationCommandHandler(apiCommandData);
      break;
    case EMBER_GET_ACTIVE_SCAN_DURATION_IPC_COMMAND_ID:
      getActiveScanDurationCommandHandler(apiCommandData);
      break;
    case EMBER_GET_DEFAULT_CHANNEL_IPC_COMMAND_ID:
      getDefaultChannelCommandHandler(apiCommandData);
      break;
    default: {
      assert(0);
    }
  }
}
