/***************************************************************************//**
 * @file
 * @brief Place for common functions / definitions shared by Green Power Client/Server
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

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif
#ifdef SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
#include "app/framework/include/af.h"
#include "app/framework/util/af-main.h"
#include "app/framework/util/common.h"
#else // !SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
#include "green-power-adapter.h"
#endif //SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
#include "stack/include/zigbee-device-stack.h"
#include "green-power-common.h"

extern bool sli_zigbee_af_gp_address_match(const EmberGpAddress *a1, const EmberGpAddress *a2);
extern void sli_zigbee_spoof_device_announcement(uint16_t shortId,
                                                 uint8_t *sourceEUI64,
                                                 EmberEUI64 deviceAnnounceEui,
                                                 uint8_t capabilities);
extern EmberNodeId emberAfResponseDestination;
uint16_t sli_zigbee_af_copy_additional_info_block_structure_to_array(uint8_t commandId,
                                                                     EmberGpTranslationTableAdditionalInfoBlockOptionRecordField *additionalInfoBlockIn,
                                                                     uint8_t *additionalInfoBlockOut)
{
  uint8_t charCount = 0;
  uint8_t *additionalInfoBlockOutPtr = additionalInfoBlockOut;

  // copy GPD Additional information block length
  emberAfCopyInt8u(additionalInfoBlockOutPtr, 0, (uint8_t)(additionalInfoBlockIn->totalLengthOfAddInfoBlock));
  additionalInfoBlockOutPtr += sizeof(uint8_t);

  if ((additionalInfoBlockIn->totalLengthOfAddInfoBlock) != 0x00) {
    emberAfGreenPowerClusterPrintln("%d ", additionalInfoBlockIn->totalLengthOfAddInfoBlock);
    //if ((additionalInfoBlockIn->optionRecord.optionSelector != 0x00) && (recordIndex < additionalInfoBlockIn->totalNbOfOptionRecord) ) {
    // copy  option selector field
    //optionSelector = (additionalInfoBlockIn->optionRecord[recordIndex].optionID & 0xF0) | (additionalInfoBlockIn->optionRecord[recordIndex].optionLength & 0x0F);
    emberAfCopyInt8u(additionalInfoBlockOutPtr, 0, (uint8_t)(additionalInfoBlockIn->optionSelector));
    additionalInfoBlockOutPtr += sizeof(uint8_t);

    if (commandId == EMBER_ZCL_GP_GPDF_COMPACT_ATTRIBUTE_REPORTING ) {
      emberAfCopyInt8u(additionalInfoBlockOutPtr,
                       0,
                       (uint8_t)(additionalInfoBlockIn->optionData.compactAttr.reportIdentifier));
      additionalInfoBlockOutPtr += sizeof(uint8_t);
      emberAfCopyInt8u(additionalInfoBlockOutPtr,
                       0,
                       (uint8_t)(additionalInfoBlockIn->optionData.compactAttr.attrOffsetWithinReport));
      additionalInfoBlockOutPtr += sizeof(uint8_t);
      emberAfCopyInt16u(additionalInfoBlockOutPtr,
                        0,
                        (uint16_t)(additionalInfoBlockIn->optionData.compactAttr.clusterID));
      additionalInfoBlockOutPtr += sizeof(uint16_t);
      emberAfCopyInt16u(additionalInfoBlockOutPtr,
                        0,
                        (uint16_t)(additionalInfoBlockIn->optionData.compactAttr.attributeID));
      additionalInfoBlockOutPtr += sizeof(uint16_t);
      emberAfCopyInt8u(additionalInfoBlockOutPtr,
                       0,
                       (uint8_t)(additionalInfoBlockIn->optionData.compactAttr.attributeDataType));
      additionalInfoBlockOutPtr += sizeof(uint8_t);
      //attributeoptions = ((additionalInfoBlockIn->optionRecord[recordIndex].optionData.compactAttr.manufacturerIdPresent << 1) | (additionalInfoBlockIn->optionRecord[recordIndex].optionData.compactAttr.clientServer));
      emberAfCopyInt8u(additionalInfoBlockOutPtr, 0, (uint8_t)(additionalInfoBlockIn->optionData.compactAttr.attributeOptions));
      additionalInfoBlockOutPtr += sizeof(uint8_t);
      //if ( additionalInfoBlockIn->optionRecord[recordIndex].optionData.compactAttr.manufacturerIdPresent) {
      if (additionalInfoBlockIn->optionData.compactAttr.attributeOptions & 0x02) {
        emberAfCopyInt16u(additionalInfoBlockOutPtr,
                          0,
                          (uint16_t)(additionalInfoBlockIn->optionData.compactAttr.manufacturerID));
        additionalInfoBlockOutPtr += sizeof(uint16_t);
      }
      emberAfGreenPowerClusterPrintln("%d %d %d 0x%2X 0x%2X %d %d 0x%2X",
                                      additionalInfoBlockIn->optionSelector,
                                      additionalInfoBlockIn->optionData.compactAttr.reportIdentifier,
                                      additionalInfoBlockIn->optionData.compactAttr.attrOffsetWithinReport,
                                      additionalInfoBlockIn->optionData.compactAttr.clusterID,
                                      additionalInfoBlockIn->optionData.compactAttr.attributeID,
                                      additionalInfoBlockIn->optionData.compactAttr.attributeDataType,
                                      additionalInfoBlockIn->optionData.compactAttr.attributeOptions,
                                      additionalInfoBlockIn->optionData.compactAttr.manufacturerID);
    } else {
      emberAfCopyInt8u(additionalInfoBlockOutPtr,
                       0,
                       (uint8_t)(additionalInfoBlockIn->optionData.genericSwitch.contactStatus));
      additionalInfoBlockOutPtr += sizeof(uint8_t);
      emberAfCopyInt8u(additionalInfoBlockOutPtr,
                       0,
                       (uint8_t)(additionalInfoBlockIn->optionData.genericSwitch.contactBitmask));
      additionalInfoBlockOutPtr += sizeof(uint8_t);
    }

    emberAfGreenPowerClusterPrintln("%d 0x%2X 0x%2X",
                                    additionalInfoBlockIn->optionSelector,
                                    additionalInfoBlockIn->optionData.genericSwitch.contactBitmask,
                                    additionalInfoBlockIn->optionData.genericSwitch.contactStatus);
  }
  charCount = (uint16_t)(additionalInfoBlockOutPtr - additionalInfoBlockOut);
  if (additionalInfoBlockIn->totalLengthOfAddInfoBlock != (charCount - 1)) {
    emberAfGreenPowerClusterPrintln("[%s:%d] Error in Addiotional Information Block additionalInfoBlockIn->totalLengthOfAddInfoBlock = %d, charCount= %d",
                                    __FUNCTION__, __LINE__, additionalInfoBlockIn->totalLengthOfAddInfoBlock, charCount);
  }
  return charCount;
}

uint16_t emberAfFillCommandGreenPowerClusterGpNotificationSmart(uint16_t options,
                                                                uint32_t gpdSrcId,
                                                                uint8_t* gpdIeee,
                                                                uint8_t  gpdEndpoint,
                                                                uint32_t gpdSecurityFrameCounter,
                                                                uint8_t  gpdCommandId,
                                                                uint8_t gpdCommandPayloadLength,
                                                                const uint8_t* gpdCommandPayload,
                                                                uint16_t gppShortAddress,
                                                                uint8_t  gppDistance)
{
  uint16_t charCount = 0;
  EmberGpApplicationId appId = emberAfGreenPowerGetApplicationId(options);

  if ((appId != EMBER_GP_APPLICATION_SOURCE_ID)
      && (appId != EMBER_GP_APPLICATION_IEEE_ADDRESS)) {
    return 0;
  }

  charCount += emberAfFillExternalBuffer((ZCL_CLUSTER_SPECIFIC_COMMAND
                                          | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER
                                          | ZCL_DISABLE_DEFAULT_RESPONSE_MASK),
                                         ZCL_GREEN_POWER_CLUSTER_ID,
                                         ZCL_GP_NOTIFICATION_COMMAND_ID,
                                         "v",
                                         options);

  if (appId == EMBER_GP_APPLICATION_SOURCE_ID) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt32uInResp(gpdSrcId));
    charCount += sizeof(uint32_t);
  } else if (appId == EMBER_GP_APPLICATION_IEEE_ADDRESS) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutBlockInResp(gpdIeee, EUI64_SIZE));
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(gpdEndpoint));
    charCount += EUI64_SIZE + sizeof(uint8_t);
  }

  emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt32uInResp(gpdSecurityFrameCounter));
  emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(gpdCommandId));
  emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(gpdCommandPayloadLength));
  emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutBlockInResp(gpdCommandPayload, gpdCommandPayloadLength));
  charCount += sizeof(uint32_t) + sizeof(uint8_t) + gpdCommandPayloadLength + sizeof(uint8_t);
  if (options & EMBER_AF_GP_NOTIFICATION_OPTION_PROXY_INFO_PRESENT) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt16uInResp(gppShortAddress));
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(gppDistance));
    charCount += sizeof(uint16_t) + sizeof(uint8_t);
  }

  return charCount;
}

uint16_t emberAfFillCommandGreenPowerClusterGpPairingSearchSmart(uint16_t options,
                                                                 uint32_t gpdSrcId,
                                                                 uint8_t* gpdIeee,
                                                                 uint8_t endpoint)
{
  EmberGpApplicationId appId = emberAfGreenPowerGetApplicationId(options);
  uint16_t charCount = 0;

  if ((appId != EMBER_GP_APPLICATION_SOURCE_ID)
      && (appId != EMBER_GP_APPLICATION_IEEE_ADDRESS)) {
    return 0;
  }

  charCount += emberAfFillExternalBuffer((ZCL_CLUSTER_SPECIFIC_COMMAND           \
                                          | ZCL_DISABLE_DEFAULT_RESPONSE_MASK    \
                                          | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER), \
                                         ZCL_GREEN_POWER_CLUSTER_ID,             \
                                         ZCL_GP_PAIRING_SEARCH_COMMAND_ID,       \
                                         "v",                                    \
                                         options);

  if (appId == EMBER_GP_APPLICATION_SOURCE_ID) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt32uInResp(gpdSrcId));
    charCount += sizeof(uint32_t);
  } else if (appId == EMBER_GP_APPLICATION_IEEE_ADDRESS) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutBlockInResp(gpdIeee, EUI64_SIZE));
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(endpoint));
    charCount += EUI64_SIZE + sizeof(uint8_t);
  }

  return charCount;
}

uint16_t emberAfFillCommandGreenPowerClusterGpTunnelingStopSmart(uint8_t options,
                                                                 uint32_t gpdSrcId,
                                                                 uint8_t* gpdIeee,
                                                                 uint8_t endpoint,
                                                                 uint32_t gpdSecurityFrameCounter,
                                                                 uint16_t gppShortAddress,
                                                                 int8_t gppDistance)
{
  EmberGpApplicationId appId = emberAfGreenPowerGetApplicationId(options);
  uint16_t charCount = 0;

  if ((appId != EMBER_GP_APPLICATION_SOURCE_ID)
      && (appId != EMBER_GP_APPLICATION_IEEE_ADDRESS)) {
    return 0;
  }

  charCount += emberAfFillExternalBuffer((ZCL_CLUSTER_SPECIFIC_COMMAND           \
                                          | ZCL_DISABLE_DEFAULT_RESPONSE_MASK    \
                                          | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER), \
                                         ZCL_GREEN_POWER_CLUSTER_ID,             \
                                         ZCL_GP_TUNNELING_STOP_COMMAND_ID,       \
                                         "u",                                    \
                                         options);

  if (appId == EMBER_GP_APPLICATION_SOURCE_ID) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt32uInResp(gpdSrcId));
    charCount += sizeof(uint32_t);
  } else if (appId == EMBER_GP_APPLICATION_IEEE_ADDRESS) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutBlockInResp(gpdIeee, EUI64_SIZE));
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(endpoint));
    charCount += EUI64_SIZE + sizeof(uint8_t);
  }

  emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt32uInResp(gpdSecurityFrameCounter));
  emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt16uInResp(gppShortAddress));
  emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(gppDistance));

  charCount += sizeof(uint32_t) + sizeof(uint16_t) + sizeof(uint8_t);

  return charCount;
}

uint16_t emberAfFillCommandGreenPowerClusterGpCommissioningNotificationSmart(uint16_t options,
                                                                             uint32_t gpdSrcId,
                                                                             uint8_t* gpdIeee,
                                                                             uint8_t endpoint,
                                                                             uint8_t macSequenceNumber,
                                                                             EmberGpSecurityLevel gpdfSecurityLevel,
                                                                             EmberGpSecurityFrameCounter gpdSecurityFrameCounter,
                                                                             uint8_t gpdCommandId,
                                                                             uint8_t gpdCommandPayloadLength,
                                                                             const uint8_t *gpdCommandPayload,
                                                                             EmberNodeId gppShortAddress,
                                                                             uint8_t gppLink,
                                                                             EmberGpMic mic)
{
  EmberGpApplicationId appId = emberAfGreenPowerGetApplicationId(options);
  uint16_t charCount = 0;
  uint32_t securityFrameCounter = 0;

  if ((appId != EMBER_GP_APPLICATION_SOURCE_ID)
      && (appId != EMBER_GP_APPLICATION_IEEE_ADDRESS)) {
    return 0;
  }

  charCount += emberAfFillExternalBuffer((ZCL_CLUSTER_SPECIFIC_COMMAND
                                          | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER
                                          | ZCL_DISABLE_DEFAULT_RESPONSE_MASK),
                                         ZCL_GREEN_POWER_CLUSTER_ID,
                                         ZCL_GP_COMMISSIONING_NOTIFICATION_COMMAND_ID,
                                         "v",
                                         options);

  if (appId == EMBER_GP_APPLICATION_SOURCE_ID) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt32uInResp(gpdSrcId));
    charCount += sizeof(uint32_t);
  } else if (appId == EMBER_GP_APPLICATION_IEEE_ADDRESS) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutBlockInResp(gpdIeee, EUI64_SIZE));
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(endpoint));
    charCount += EUI64_SIZE + sizeof(uint8_t);
  }

  if (gpdfSecurityLevel == 0 ) {
    securityFrameCounter = (uint32_t)macSequenceNumber;
  } else {
    securityFrameCounter = gpdSecurityFrameCounter;
  }
  emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt32uInResp(securityFrameCounter));
  emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(gpdCommandId));
  emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(gpdCommandPayloadLength));
  emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutBlockInResp(gpdCommandPayload, gpdCommandPayloadLength));
  charCount += sizeof(uint32_t) + sizeof(uint8_t) + gpdCommandPayloadLength + sizeof(uint8_t);
  if (options & EMBER_AF_GP_COMMISSIONING_NOTIFICATION_OPTION_PROXY_INFO_PRESENT) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt16uInResp(gppShortAddress));
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(gppLink));
    charCount += sizeof(uint16_t) + sizeof(uint8_t);
  }

  if (options & EMBER_AF_GP_COMMISSIONING_NOTIFICATION_OPTION_SECURITY_PROCESSING_FAILED) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt32uInResp(mic));
    charCount += sizeof(uint32_t);
  }

  return charCount;
}

uint16_t emberAfFillCommandGreenPowerClusterGpTranslationTableUpdateSmart(uint16_t options,
                                                                          uint32_t gpdSrcId,
                                                                          uint8_t* gpdIeee,
                                                                          uint8_t endpoint,
                                                                          uint8_t translationsLen,
                                                                          GpTranslationTableUpdateTranslation* translations,
                                                                          EmberGpTranslationTableAdditionalInfoBlockOptionRecordField* additionalInfoBlock)
{
  EmberGpApplicationId appId = emberAfGreenPowerGetApplicationId(options);

  uint16_t charCount = 0;
  if (((appId != EMBER_GP_APPLICATION_SOURCE_ID)
       && (appId != EMBER_GP_APPLICATION_IEEE_ADDRESS))
      || (translations == NULL)) {
    return 0;
  }

  charCount += emberAfFillExternalBuffer((ZCL_CLUSTER_SPECIFIC_COMMAND               \
                                          | ZCL_DISABLE_DEFAULT_RESPONSE_MASK        \
                                          | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER),     \
                                         ZCL_GREEN_POWER_CLUSTER_ID,                 \
                                         ZCL_GP_TRANSLATION_TABLE_UPDATE_COMMAND_ID, \
                                         "v",                                        \
                                         options);

  if (appId == EMBER_GP_APPLICATION_SOURCE_ID) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt32uInResp(gpdSrcId));
    charCount += sizeof(uint32_t);
  } else if (appId == EMBER_GP_APPLICATION_IEEE_ADDRESS) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutBlockInResp(gpdIeee, EUI64_SIZE));
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(endpoint));
    charCount += EUI64_SIZE + sizeof(uint8_t);
  }

  emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(translations->index));
  charCount += sizeof(uint8_t);
  emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(translations->gpdCommandId));
  charCount += sizeof(uint8_t);
  emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(translations->endpoint));
  charCount += sizeof(uint8_t);
  emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt16uInResp(translations->profile));
  charCount += sizeof(uint16_t);
  emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt16uInResp(translations->cluster));
  charCount += sizeof(uint16_t);
  emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(translations->zigbeeCommandId));
  charCount += sizeof(uint8_t);
  emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutStringInResp(translations->zigbeeCommandPayload));
  charCount += emberAfStringLength(translations->zigbeeCommandPayload) + 1;
  if (emberAfGreenPowerTTUpdateGetAdditionalInfoBlockPresent(options) != 0
      && additionalInfoBlock) {
    uint8_t tempBuffer[32] = { 0 }; // Two records maximum per cli
    uint16_t length = sli_zigbee_af_copy_additional_info_block_structure_to_array(translations->gpdCommandId,
                                                                                  additionalInfoBlock,
                                                                                  tempBuffer);
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(length));
    charCount += sizeof(uint8_t);
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutBlockInResp(tempBuffer, length));
    charCount += length;
  }
  return charCount;
}

uint16_t emberAfFillCommandGreenPowerClusterGpPairingConfigurationSmart(uint8_t actions,
                                                                        uint16_t options,
                                                                        uint32_t gpdSrcId,
                                                                        uint8_t* gpdIeee,
                                                                        uint8_t endpoint,
                                                                        uint8_t deviceId,
                                                                        uint8_t groupListCount,
                                                                        uint8_t* groupList,
                                                                        uint16_t gpdAssignedAlias,
                                                                        uint8_t groupcastRadius,
                                                                        uint8_t securityOptions,
                                                                        uint32_t gpdSecurityFrameCounter,
                                                                        uint8_t* gpdSecurityKey,
                                                                        uint8_t numberOfPairedEndpoints,
                                                                        uint8_t* pairedEndpoints,
                                                                        uint8_t applicationInformation,
                                                                        uint16_t manufacturerId,
                                                                        uint16_t modeId,
                                                                        uint8_t numberOfGpdCommands,
                                                                        uint8_t * gpdCommandIdList,
                                                                        uint8_t clusterIdListCount,
                                                                        uint16_t * clusterListServer,
                                                                        uint16_t * clusterListClient,
                                                                        uint8_t switchInformationLength,
                                                                        uint8_t genericSwitchConfiguration,
                                                                        uint8_t currentContactStatus,
                                                                        uint8_t totalNumberOfReports,
                                                                        uint8_t numberOfReports,
                                                                        uint8_t* reportDescriptorM)
{
  EmberGpApplicationId appId = emberAfGreenPowerGetApplicationId(options);
  uint16_t charCount = 0;

  if ((appId != EMBER_GP_APPLICATION_SOURCE_ID)
      && (appId != EMBER_GP_APPLICATION_IEEE_ADDRESS)) {
    return 0;
  }

  charCount += emberAfFillExternalBuffer((ZCL_CLUSTER_SPECIFIC_COMMAND            \
                                          | ZCL_DISABLE_DEFAULT_RESPONSE_MASK     \
                                          | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER),  \
                                         ZCL_GREEN_POWER_CLUSTER_ID,              \
                                         ZCL_GP_PAIRING_CONFIGURATION_COMMAND_ID, \
                                         "uv",                                    \
                                         actions,
                                         options);

  if (appId == EMBER_GP_APPLICATION_SOURCE_ID) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt32uInResp(gpdSrcId));
    charCount += sizeof(uint32_t);
  } else if (appId == EMBER_GP_APPLICATION_IEEE_ADDRESS) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutBlockInResp(gpdIeee, EUI64_SIZE));
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(endpoint));
    charCount += EUI64_SIZE + sizeof(uint8_t);
  }

  emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(deviceId));
  emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutBlockInResp(groupList, groupListCount));
  charCount += sizeof(uint8_t) + groupListCount;

  if (options & EMBER_AF_GP_PAIRING_CONFIGURATION_OPTION_ASSIGNED_ALIAS) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt16uInResp(gpdAssignedAlias));
    charCount += sizeof(uint16_t);
  }

  emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(groupcastRadius));
  charCount += sizeof(uint8_t);

  if (options & EMBER_AF_GP_PAIRING_CONFIGURATION_OPTION_SECURITY_USE) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(securityOptions));
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt32uInResp(gpdSecurityFrameCounter));
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutBlockInResp(gpdSecurityKey, EMBER_ENCRYPTION_KEY_SIZE));
    charCount += sizeof(uint32_t) + sizeof(uint8_t) + EMBER_ENCRYPTION_KEY_SIZE;
  }

  emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(numberOfPairedEndpoints));
  charCount += sizeof(uint8_t);
  if (numberOfPairedEndpoints < EMBER_AF_GP_TRANSLATION_TABLE_ZB_ENDPOINT_PASS_FRAME_TO_APLLICATION) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutBlockInResp(pairedEndpoints, numberOfPairedEndpoints));
    charCount += numberOfPairedEndpoints;
  }

  if (options & EMBER_AF_GP_PAIRING_CONFIGURATION_OPTION_APPLICATION_INFORMATION_PRESENT) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(applicationInformation));
    if (applicationInformation & EMBER_AF_GP_APPLICATION_INFORMATION_MANUFACTURE_ID_PRESENT) {
      emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt16uInResp(manufacturerId));
      charCount += sizeof(uint16_t);
    }

    if (applicationInformation & EMBER_AF_GP_APPLICATION_INFORMATION_MODEL_ID_PRESENT) {
      emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt16uInResp(modeId));
      charCount += sizeof(uint16_t);
    }

    if (applicationInformation & EMBER_AF_GP_APPLICATION_INFORMATION_GPD_COMMANDS_PRESENT) {
      emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(numberOfGpdCommands));
      emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutBlockInResp(gpdCommandIdList, numberOfGpdCommands));
      charCount += sizeof(uint8_t) + numberOfGpdCommands;
    }

    if (applicationInformation & EMBER_AF_GP_APPLICATION_INFORMATION_CLUSTER_LIST_PRESENT) {
      emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(clusterIdListCount));
      emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutBlockInResp((uint8_t*)clusterListServer, sizeof(EmberAfClusterId) * (clusterIdListCount & EMBER_AF_GP_APPLICATION_INFORMATION_CLUSTER_LIST_NUMBER_OF_SERVER_CLUSTER_MASK)));
      emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutBlockInResp((uint8_t*)clusterListClient, sizeof(EmberAfClusterId) * ((clusterIdListCount & EMBER_AF_GP_APPLICATION_INFORMATION_CLUSTER_LIST_NUMBER_OF_CLIENT_CLUSTER_MASK) >> EMBER_AF_GP_APPLICATION_INFORMATION_CLUSTER_LIST_NUMBER_OF_CLIENT_CLUSTER_MASK_OFFSET)));
      charCount += sizeof(uint8_t)
                   + sizeof(EmberAfClusterId) * (clusterIdListCount & EMBER_AF_GP_APPLICATION_INFORMATION_CLUSTER_LIST_NUMBER_OF_SERVER_CLUSTER_MASK)
                   + sizeof(EmberAfClusterId) * ((clusterIdListCount & EMBER_AF_GP_APPLICATION_INFORMATION_CLUSTER_LIST_NUMBER_OF_CLIENT_CLUSTER_MASK) >> EMBER_AF_GP_APPLICATION_INFORMATION_CLUSTER_LIST_NUMBER_OF_CLIENT_CLUSTER_MASK_OFFSET);
    }
  }
  if (applicationInformation & EMBER_AF_GP_APPLICATION_INFORMATION_SWITCH_INFORMATION_PRESENT) { // Switch Information Present
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(switchInformationLength));
    charCount += sizeof(uint8_t);
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(genericSwitchConfiguration));
    charCount += sizeof(uint8_t);
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(currentContactStatus));
    charCount += sizeof(uint8_t);
  }
  // Application description should add the reports
  if (actions == EMBER_ZCL_GP_PAIRING_CONFIGURATION_ACTION_APPLICATION_DESCRIPTION) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(totalNumberOfReports));
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(numberOfReports));
    uint8_t nextOffset = 0;
    for (uint8_t index = 0; index < numberOfReports; index++) {
      uint8_t * descPtr;  // pointing to each report descriptor
      uint8_t descLength; // of each descriptor
      descPtr = &reportDescriptorM[nextOffset];
      // the report descriptor array has following meaning for indexs
      // descPtr[0] is reportId, descPtr[1] is options
      // the bit 0 of option indicates timeout Period Present (all other bits reserved)
      // if timeout(uint16 type)is present, the remaining length is present at index 5 else it is present
      // at index 3 of descPtr
      if (descPtr[1] & EMBER_AF_GP_GPD_APPLICATION_DESCRIPTION_COMMAND_REPORT_OPTIONS_TIMEOUT_PERIOD_PRESENT) {
        descLength = descPtr[4] + 5;
      } else {
        descLength = descPtr[2] + 3;
      }
      nextOffset += descLength;
    }
    // ptr to block and bytes to copy
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutBlockInResp(reportDescriptorM, nextOffset));
    charCount += nextOffset;
  }
  return charCount;
}

uint16_t emberAfFillCommandGreenPowerClusterGpSinkTableRequestSmart(uint8_t options,
                                                                    uint32_t gpdSrcId,
                                                                    uint8_t* gpdIeee,
                                                                    uint8_t endpoint,
                                                                    uint8_t index)
{
  EmberGpApplicationId appId = emberAfGreenPowerGetApplicationId(options);
  uint16_t charCount = 0;

  if ((appId != EMBER_GP_APPLICATION_SOURCE_ID)
      && (appId != EMBER_GP_APPLICATION_IEEE_ADDRESS)) {
    return 0;
  }

  charCount += emberAfFillExternalBuffer((ZCL_CLUSTER_SPECIFIC_COMMAND           \
                                          | ZCL_DISABLE_DEFAULT_RESPONSE_MASK    \
                                          | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER), \
                                         ZCL_GREEN_POWER_CLUSTER_ID,             \
                                         ZCL_GP_SINK_TABLE_REQUEST_COMMAND_ID,   \
                                         "uw",                                   \
                                         options,                                \
                                         gpdSrcId);

  if ( ((options & EMBER_AF_GP_SINK_TABLE_REQUEST_OPTIONS_REQUEST_TYPE)
        >> EMBER_AF_GP_SINK_TABLE_REQUEST_OPTIONS_REQUEST_TYPE_OFFSET) == EMBER_ZCL_GP_SINK_TABLE_REQUEST_OPTIONS_REQUEST_TABLE_ENTRIES_BY_GPD_ID) {
    if (appId == EMBER_GP_APPLICATION_SOURCE_ID) {
      emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt32uInResp(gpdSrcId));
      charCount += sizeof(uint32_t);
    } else if (appId == EMBER_GP_APPLICATION_IEEE_ADDRESS) {
      emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutBlockInResp(gpdIeee, EUI64_SIZE));
      emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(index));
      charCount += EUI64_SIZE + sizeof(uint8_t);
    }
  }
  if ( ((options & EMBER_AF_GP_SINK_TABLE_REQUEST_OPTIONS_REQUEST_TYPE)
        >> EMBER_AF_GP_SINK_TABLE_REQUEST_OPTIONS_REQUEST_TYPE_OFFSET) == EMBER_ZCL_GP_SINK_TABLE_REQUEST_OPTIONS_REQUEST_TABLE_ENTRIES_BY_INDEX) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(index));
    charCount += sizeof(uint8_t);
  }

  return charCount;
}

uint32_t emberAfFillCommandGreenPowerClusterGpNotificationResponseSmart(uint8_t options,
                                                                        uint32_t gpdSrcId,
                                                                        uint8_t* gpdIeee,
                                                                        uint8_t endpoint,
                                                                        uint32_t gpdSecurityFrameCounter)
{
  EmberGpApplicationId appId = emberAfGreenPowerGetApplicationId(options);
  uint16_t charCount = 0;

  if ((appId != EMBER_GP_APPLICATION_SOURCE_ID)
      && (appId != EMBER_GP_APPLICATION_IEEE_ADDRESS)) {
    return 0;
  }

  charCount += emberAfFillExternalBuffer((ZCL_CLUSTER_SPECIFIC_COMMAND        \
                                          | ZCL_DISABLE_DEFAULT_RESPONSE_MASK \
                                          | ZCL_FRAME_CONTROL_SERVER_TO_CLIENT),
                                         ZCL_GREEN_POWER_CLUSTER_ID,
                                         ZCL_GP_NOTIFICATION_RESPONSE_COMMAND_ID,
                                         "u",
                                         options);

  if (appId == EMBER_GP_APPLICATION_SOURCE_ID) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt32uInResp(gpdSrcId));
    charCount += sizeof(uint32_t);
  } else if (appId == EMBER_GP_APPLICATION_IEEE_ADDRESS) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutBlockInResp(gpdIeee, EUI64_SIZE));
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(endpoint));
    charCount += EUI64_SIZE + sizeof(uint8_t);
  }
  emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt32uInResp(gpdSecurityFrameCounter));
  charCount += sizeof(uint32_t);

  return charCount;
}

uint16_t emberAfFillCommandGreenPowerClusterGpPairingSmart(uint32_t options,
                                                           uint32_t gpdSrcId,
                                                           uint8_t* gpdIeee,
                                                           uint8_t endpoint,
                                                           uint8_t* sinkIeeeAddress,
                                                           uint16_t sinkNwkAddress,
                                                           uint16_t sinkGroupId,
                                                           uint8_t deviceId,
                                                           uint32_t gpdSecurityFrameCounter,
                                                           uint8_t* gpdKey,
                                                           uint16_t assignedAlias,
                                                           uint8_t groupcastRadius)
{
  EmberGpApplicationId appId = emberAfGreenPowerGetApplicationId(options);
  uint16_t charCount = 0;
  uint8_t commMode = emberAfGreenPowerPairingOptionsGetCommMode(options);

  if ((appId != EMBER_GP_APPLICATION_SOURCE_ID)
      && (appId != EMBER_GP_APPLICATION_IEEE_ADDRESS)) {
    return 0;
  }
  // The Disable default response sub-field of the Frame Control Field of
  // the ZCL header SHALL be set to 0b1.
  charCount += emberAfFillExternalBuffer((ZCL_CLUSTER_SPECIFIC_COMMAND
                                          | ZCL_FRAME_CONTROL_SERVER_TO_CLIENT
                                          | ZCL_DISABLE_DEFAULT_RESPONSE_MASK),
                                         ZCL_GREEN_POWER_CLUSTER_ID,
                                         ZCL_GP_PAIRING_COMMAND_ID,
                                         "x",
                                         options);

  if (appId == EMBER_GP_APPLICATION_SOURCE_ID) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt32uInResp(gpdSrcId));
    charCount += sizeof(uint32_t);
  } else if (appId == EMBER_GP_APPLICATION_IEEE_ADDRESS) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutBlockInResp(gpdIeee, EUI64_SIZE));
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(endpoint));
    charCount += EUI64_SIZE + sizeof(uint8_t);
  }

  if ((options & EMBER_AF_GP_PAIRING_OPTION_REMOVE_GPD) == 0x00) {
    if ((commMode == 0x00) || (commMode == 0x03)) {
      emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutBlockInResp(sinkIeeeAddress, EUI64_SIZE));
      emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt16uInResp(sinkNwkAddress));
      charCount += EUI64_SIZE + sizeof(uint16_t);
    } else if (commMode == 0x01 || commMode == 0x02) {
      emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt16uInResp(sinkGroupId));
      charCount += sizeof(uint16_t);
    }
  }

  if (emberAfGreenPowerPairingOptionsGetAddSink(options)) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(deviceId));
    charCount += sizeof(uint8_t);
  }
  if (options & EMBER_AF_GP_PAIRING_OPTION_GPD_SECURITY_FRAME_COUNTER_PRESENT) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt32uInResp(gpdSecurityFrameCounter));
    charCount += sizeof(uint32_t);
  }
  if (options & EMBER_AF_GP_PAIRING_OPTION_GPD_SECURITY_KEY_PRESENT) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutBlockInResp(gpdKey, EMBER_ENCRYPTION_KEY_SIZE));
    charCount += EMBER_ENCRYPTION_KEY_SIZE;
  }
  if (options & EMBER_AF_GP_PAIRING_OPTION_ASSIGNED_ALIAS_PRESENT) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt16uInResp(assignedAlias));
    charCount += sizeof(uint16_t);
  }
  if (options & EMBER_AF_GP_PAIRING_OPTION_GROUPCAST_RADIUS_PRESENT) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(groupcastRadius));
    charCount += sizeof(uint8_t);
  }

  return charCount;
}

uint16_t emberAfFillCommandGreenPowerClusterGpProxyCommissioningModeSmart(uint8_t options,
                                                                          uint16_t commissioningWindow,
                                                                          uint8_t channel)
{
  // docs-14-0563-08: "In the current version of the GP specification,
  // the Channel present sub-field SHALL always be set to 0b0 and
  // the Channel field SHALL NOT be present."
  uint16_t charCount = 0;

  options &= ~EMBER_AF_GP_PROXY_COMMISSIONING_MODE_OPTION_CHANNEL_PRESENT;
  charCount += emberAfFillExternalBuffer((ZCL_CLUSTER_SPECIFIC_COMMAND
                                          | ZCL_FRAME_CONTROL_SERVER_TO_CLIENT
                                          | ZCL_DISABLE_DEFAULT_RESPONSE_MASK),
                                         ZCL_GREEN_POWER_CLUSTER_ID,
                                         ZCL_GP_PROXY_COMMISSIONING_MODE_COMMAND_ID,
                                         "u",
                                         options);

  if (options & EMBER_AF_GP_PROXY_COMMISSIONING_MODE_EXIT_MODE_ON_COMMISSIONING_WINDOW_EXPIRATION) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt16uInResp(commissioningWindow));
    charCount += sizeof(uint16_t);
  }

  if (options & EMBER_AF_GP_PROXY_COMMISSIONING_MODE_OPTION_CHANNEL_PRESENT) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(channel));
    charCount += sizeof(uint8_t);
  }

  return charCount;
}

uint16_t emberAfFillCommandGreenPowerClusterGpResponseSmart(uint8_t  options,
                                                            uint16_t tempMasterShortAddress,
                                                            uint8_t  tempMasterTxChannel,
                                                            uint32_t gpdSrcId,
                                                            uint8_t* gpdIeee,
                                                            uint8_t  endpoint,
                                                            uint8_t  gpdCommandId,
                                                            uint8_t gpdCommandPayloadLength,
                                                            uint8_t* gpdCommandPayload)
{
  EmberGpApplicationId appId = emberAfGreenPowerGetApplicationId(options);
  uint16_t charCount = 0;
  if ((appId != EMBER_GP_APPLICATION_SOURCE_ID)
      && (appId != EMBER_GP_APPLICATION_IEEE_ADDRESS)) {
    return 0;
  }

  charCount += emberAfFillExternalBuffer((ZCL_CLUSTER_SPECIFIC_COMMAND
                                          | ZCL_DISABLE_DEFAULT_RESPONSE_MASK
                                          | ZCL_FRAME_CONTROL_SERVER_TO_CLIENT),
                                         ZCL_GREEN_POWER_CLUSTER_ID,
                                         ZCL_GP_RESPONSE_COMMAND_ID,
                                         "uvu",
                                         options,
                                         tempMasterShortAddress,
                                         tempMasterTxChannel);

  if (appId == EMBER_GP_APPLICATION_SOURCE_ID) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt32uInResp(gpdSrcId));
    charCount += sizeof(uint32_t);
  } else if (appId == EMBER_GP_APPLICATION_IEEE_ADDRESS) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutBlockInResp(gpdIeee, EUI64_SIZE));
    charCount += EUI64_SIZE;
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(endpoint));
    charCount += sizeof(uint8_t);
  }

  emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(gpdCommandId));
  emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(gpdCommandPayloadLength));
  emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutBlockInResp(gpdCommandPayload, gpdCommandPayloadLength));
  charCount += sizeof(uint8_t) + gpdCommandPayloadLength + sizeof(uint8_t);

  return charCount;
}

uint16_t emberAfFillCommandGreenPowerClusterGpProxyTableRequestSmart(uint8_t options,
                                                                     uint32_t gpdSrcId,
                                                                     uint8_t* gpdIeee,
                                                                     uint8_t endpoint,
                                                                     uint8_t index)
{
  EmberGpApplicationId appId = emberAfGreenPowerGetApplicationId(options);
  uint8_t requestType = (options & EMBER_AF_GP_PROXY_TABLE_REQUEST_OPTIONS_REQUEST_TYPE) >> 3;
  uint16_t charCount = 0;
  if ((appId != EMBER_GP_APPLICATION_SOURCE_ID)
      && (appId != EMBER_GP_APPLICATION_IEEE_ADDRESS)) {
    return 0;
  }

  charCount += emberAfFillExternalBuffer((ZCL_CLUSTER_SPECIFIC_COMMAND
                                          | ZCL_DISABLE_DEFAULT_RESPONSE_MASK
                                          | ZCL_FRAME_CONTROL_SERVER_TO_CLIENT),
                                         ZCL_GREEN_POWER_CLUSTER_ID,
                                         ZCL_GP_PROXY_TABLE_REQUEST_COMMAND_ID,
                                         "u",
                                         options);

  if (appId == EMBER_GP_APPLICATION_SOURCE_ID) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt32uInResp(gpdSrcId));
    charCount += sizeof(uint32_t);
  } else if (appId == EMBER_GP_APPLICATION_IEEE_ADDRESS) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutBlockInResp(gpdIeee, EUI64_SIZE));
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(endpoint));
    charCount += EUI64_SIZE + sizeof(uint8_t);
  }

  if (requestType == 0x01) {
    emberAfGreenPowerCheckReturnOfPutDataInResponse(emberAfPutInt8uInResp(endpoint));
    charCount += sizeof(uint8_t);
  }

  return charCount;
}

/*
 * Comparing two GP address.
 *
 * return - true if addresses are the same. otherwise, false.
 *
 */
bool emberAfGreenPowerCommonGpAddrCompare(const EmberGpAddress * a1,
                                          const EmberGpAddress * a2)
{
#ifndef EZSP_HOST
  return sli_zigbee_af_gp_address_match(a1, a2);
#else
  if (a1->applicationId == EMBER_GP_APPLICATION_SOURCE_ID
      && a2->applicationId == EMBER_GP_APPLICATION_SOURCE_ID) {
    if (a1->id.sourceId == a2->id.sourceId) {
      return true;
    }
  } else if (a1->applicationId == EMBER_GP_APPLICATION_IEEE_ADDRESS
             && a2->applicationId == EMBER_GP_APPLICATION_IEEE_ADDRESS) {
    if (!MEMCOMPARE(a1->id.gpdIeeeAddress, a2->id.gpdIeeeAddress, EUI64_SIZE)) {
      if (a1->endpoint == a2->endpoint
          || a1->endpoint == GREEN_POWER_SERVER_ALL_SINK_ENDPOINTS
          || a2->endpoint == GREEN_POWER_SERVER_ALL_SINK_ENDPOINTS
          || a1->endpoint == GREEN_POWER_SERVER_NO_PAIRED_ENDPOINTS
          || a2->endpoint == GREEN_POWER_SERVER_NO_PAIRED_ENDPOINTS) {
        return true;
      }
    }
  }
  return false;
#endif
}

bool sli_zigbee_af_gp_make_addr(EmberGpAddress *addr,
                                EmberGpApplicationId appId,
                                EmberGpSourceId srcId,
                                uint8_t *gpdIeee,
                                uint8_t endpoint)
{
  if (addr == NULL
      || ((endpoint > GREEN_POWER_SERVER_MAX_VALID_APP_ENDPOINT)
          && (endpoint < GREEN_POWER_SERVER_RAW_GPD_PROCESS_IN_APP_ENDPOINTS))) {
    return false;
  }

  if (appId == EMBER_GP_APPLICATION_SOURCE_ID) {
    if (IS_RESERVED_GPD_SRC_ID(srcId)) {
      return false;
    }
    addr->id.sourceId = srcId;
  } else if (appId == EMBER_GP_APPLICATION_IEEE_ADDRESS
             && gpdIeee != NULL) {
    if (((emberAfMemoryByteCompare(gpdIeee, EUI64_SIZE, 0)))) {
      return false;
    }
    MEMCOPY(addr->id.gpdIeeeAddress, gpdIeee, EUI64_SIZE);
    addr->endpoint = endpoint;
  } else {
    return false;
  }
  addr->applicationId = appId;
  return true;
}

void sli_zigbee_af_gp_spoof_device_annce(uint16_t nodeId,
                                         EmberEUI64 eui64,
                                         uint8_t capabilities)
{
#ifdef EZSP_HOST
  EmberApsFrame apsFrameDevAnnce;
  apsFrameDevAnnce.sourceEndpoint = EMBER_ZDO_ENDPOINT;
  apsFrameDevAnnce.destinationEndpoint = EMBER_ZDO_ENDPOINT;
  apsFrameDevAnnce.clusterId = END_DEVICE_ANNOUNCE;
  apsFrameDevAnnce.profileId = EMBER_ZDO_PROFILE_ID;
  apsFrameDevAnnce.options = EMBER_APS_OPTION_SOURCE_EUI64;
  apsFrameDevAnnce.options |= EMBER_APS_OPTION_USE_ALIAS_SEQUENCE_NUMBER;
  apsFrameDevAnnce.groupId = 0;
  uint8_t messageContents[GP_DEVICE_ANNOUNCE_SPOOF_MSG_SIZE];
  uint8_t apsSequence = 0;
  // Form the APS message for Bcast
  messageContents[0] = apsSequence; //Sequence
  messageContents[1] = (uint8_t)nodeId; //NodeId
  messageContents[2] = (uint8_t)(nodeId >> 8); //NodeId
  MEMCOPY(&messageContents[3], eui64, EUI64_SIZE); //IEEE Address
  messageContents[11] = capabilities; // Capability
  ezspProxyBroadcast(nodeId,//EmberNodeId source,
                     0xFFFD,//EmberNodeId destination,
                     0,//uint8_t nwkSequence,
                     &apsFrameDevAnnce,//EmberApsFrame *apsFrame,
                     0xFF,//uint8_t radius,
                     0xFF,// Tag Id
                     sizeof(messageContents),//uint8_t messageLength,
                     messageContents,//uint8_t *messageContents,
                     &apsSequence);
#else // !EZSP_HOST
  // Use the stack private function to save code space in case of SoC.
  sli_zigbee_spoof_device_announcement(nodeId,
                                       NULL,
                                       eui64,
                                       capabilities);
#endif // EZSP_HOST
}

EmberStatus sli_zigbee_af_gp_send_response_unicast(void)
{
  if (emberAfCurrentCommand()->interPanHeader == NULL) {
    emberAfResponseDestination = emberAfCurrentCommand()->source;
  }
  return emberAfSendResponse();
}
