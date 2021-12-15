/***************************************************************************//**
 * @brief Ember Connect API renaming (to be used for bare metal SoC
 * applications).
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#ifndef __API_RENAME_H__
#define __API_RENAME_H__

// Core
#define emberApplyIrCalibration                            emApiApplyIrCalibration
#define emberCalibrateCurrentChannelExtended               emApiCalibrateCurrentChannelExtended
#define emberCurrentStackTasks                             emApiCurrentStackTasks
#define emberGetCalType                                    emApiGetCalType
#define emberGetCounter                                    emApiGetCounter
#define emberGetMaximumPayloadLength                       emApiGetMaximumPayloadLength
#define emberGetRadioChannel                               emApiGetRadioChannel
#define emberGetRadioPower                                 emApiGetRadioPower
#define emberInit                                          emApiInit
#define emberMacGetParentAddress                           emApiMacGetParentAddress
#define emberNetworkState                                  emApiNetworkState
#define emberSetIndirectQueueTimeout                       emApiSetIndirectQueueTimeout
#define emberSetMacParams                                  emApiSetMacParams
#define emberSetRadioChannelExtended                       emApiSetRadioChannelExtended
#define emberSetRadioPower                                 emApiSetRadioPower
#define emberSetRadioPowerMode                             emApiSetRadioPowerMode
#define emberSetSecurityKey                                emApiSetSecurityKey
#define emberStackIdleTimeMs                               emApiStackIdleTimeMs
#define emberStackIsUp                                     emApiStackIsUp
#define emberTempCalibration                               emApiTempCalibration
#define emberTick                                          emApiTick

// Messaging
#define emberGetChildFlags                                 emApiGetChildFlags
#define emberGetChildInfo                                  emApiGetChildInfo
#define emberMacAddShortToLongAddressMapping               emApiMacAddShortToLongAddressMapping
#define emberMacClearShortToLongAddressMappings            emApiMacClearShortToLongAddressMappings
#define emberMacMessageSend                                emApiMacMessageSend
#define emberMacSetPanCoordinator                          emApiMacSetPanCoordinator
#define emberMessageSend                                   emApiMessageSend
#define emberNetworkLeave                                  emApiNetworkLeave
#define emberPollForData                                   emApiPollForData
#define emberPurgeIndirectMessages                         emApiPurgeIndirectMessages
#define emberRemoveChild                                   emApiRemoveChild
#define emberSetPollDestinationAddress                     emApiSetPollDestinationAddress

// Network Management
#define emberClearSelectiveJoinPayload                     emApiClearSelectiveJoinPayload
#define emberFormNetwork                                   emApiFormNetwork
#define emberFrequencyHoppingSetChannelMask                emApiFrequencyHoppingSetChannelMask
#define emberFrequencyHoppingStartClient                   emApiFrequencyHoppingStartClient
#define emberFrequencyHoppingStartServer                   emApiFrequencyHoppingStartServer
#define emberFrequencyHoppingStop                          emApiFrequencyHoppingStop
#define emberGetActiveScanDuration                         emApiGetActiveScanDuration
#define emberGetAuxiliaryAddressFilteringEntry             emApiGetAuxiliaryAddressFilteringEntry
#define emberGetDefaultChannel                             emApiGetDefaultChannel
#define emberJoinCommissioned                              emApiJoinCommissioned
#define emberJoinNetworkExtended                           emApiJoinNetworkExtended
#define emberNetworkInit                                   emApiNetworkInit
#define emberPermitJoining                                 emApiPermitJoining
#define emberResetNetworkState                             emApiResetNetworkState
#define emberSetActiveScanDuration                         emApiSetActiveScanDuration
#define emberSetApplicationBeaconPayload                   emApiSetApplicationBeaconPayload
#define emberSetAuxiliaryAddressFilteringEntry             emApiSetAuxiliaryAddressFilteringEntry
#define emberSetSelectiveJoinPayload                       emApiSetSelectiveJoinPayload
#define emberStartActiveScan                               emApiStartActiveScan
#define emberStartEnergyScan                               emApiStartEnergyScan
#define emberStartTxStream                                 emApiStartTxStream
#define emberStopTxStream                                  emApiStopTxStream

#endif // __API_RENAME_H__
