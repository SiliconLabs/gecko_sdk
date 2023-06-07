/**************************************************************************//**
 * Copyright 2017 Silicon Laboratories, Inc.
 *
 *****************************************************************************/

#include "mpsi-message-ids.h"

#ifdef EMBER_STACK_ZIGBEE
 #ifdef EZSP_HOST
// Host
  #define getNetworkParameters(nodeTypePtr, parametersPtr) \
  ezspGetNetworkParameters(nodeTypePtr, parametersPtr)
 #else
// SoC
  #define getNetworkParameters(nodeTypePtr, parametersPtr) \
  emberGetNetworkParameters(parametersPtr);                \
  (void)nodeTypePtr;
 #endif  // EZSP_HOST
 #define addTransientLinkKey sl_zb_sec_man_import_transient_link_key
#endif // EMBER_STACK_ZIGBEE

// Message callbacks
uint8_t mpsiHandleMessageGetAppsInfo(MpsiMessage_t *mpsiMessage);
uint8_t mpsiHandleMessageAppsInfo(MpsiMessage_t *mpsiMessage);
uint8_t mpsiHandleMessageBootloadSlot(MpsiMessage_t *mpsiMessage);
uint8_t mpsiHandleMessageError(MpsiMessage_t *mpsiMessage);
uint8_t mpsiHandleMessageInitiateJoining(MpsiMessage_t *mpsiMessage);
uint8_t mpsiHandleMessageGetZigbeeJoiningDeviceInfo(MpsiMessage_t *mpsiMessage);
uint8_t mpsiHandleMessageZigbeeJoiningDeviceInfo(MpsiMessage_t *mpsiMessage);
uint8_t mpsiHandleMessageSetZigbeeJoiningDeviceInfo(MpsiMessage_t *mpsiMessage);
uint8_t mpsiHandleMessageGetZigbeeTrustCenterJoiningCredentials(
  MpsiMessage_t *mpsiMessage);
uint8_t mpsiHandleMessageZigbeeTrustCenterJoiningCredentials(
  MpsiMessage_t *mpsiMessage);
uint8_t mpsiHandleMessageSetZigbeeTrustCenterJoiningCredentials(
  MpsiMessage_t *mpsiMessage);
