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

#ifndef __API_RENAME_UNDEF_H__
#define __API_RENAME_UNDEF_H__

// Core
#undef emberApplyIrCalibration
#undef emberCalibrateCurrentChannelExtended
#undef emberCurrentStackTasks
#undef emberGetCalType
#undef emberGetCounter
#undef emberGetMaximumPayloadLength
#undef emberGetRadioChannel
#undef emberGetRadioPower
#undef emberInit
#undef emberMacGetParentAddress
#undef emberNetworkState
#undef emberSetIndirectQueueTimeout
#undef emberSetMacParams
#undef emberSetRadioChannelExtended
#undef emberSetRadioPower
#undef emberSetRadioPowerMode
#undef emberSetSecurityKey
#undef emberStackIdleTimeMs
#undef emberStackIsUp
#undef emberTempCalibration
#undef emberTick

// Messaging
#undef emberGetChildFlags
#undef emberGetChildInfo
#undef emberMacAddShortToLongAddressMapping
#undef emberMacClearShortToLongAddressMappings
#undef emberMacMessageSend
#undef emberMacSetPanCoordinator
#undef emberMessageSend
#undef emberNetworkLeave
#undef emberPollForData
#undef emberPurgeIndirectMessages
#undef emberRemoveChild
#undef emberSetPollDestinationAddress

// Network Management
#undef emberClearSelectiveJoinPayload
#undef emberFormNetwork
#undef emberFrequencyHoppingSetChannelMask
#undef emberFrequencyHoppingStartClient
#undef emberFrequencyHoppingStartServer
#undef emberFrequencyHoppingStop
#undef emberGetActiveScanDuration
#undef emberGetAuxiliaryAddressFilteringEntry
#undef emberGetDefaultChannel
#undef emberJoinCommissioned
#undef emberJoinNetworkExtended
#undef emberNetworkInit
#undef emberPermitJoining
#undef emberResetNetworkState
#undef emberSetActiveScanDuration
#undef emberSetApplicationBeaconPayload
#undef emberSetAuxiliaryAddressFilteringEntry
#undef emberSetSelectiveJoinPayload
#undef emberStartActiveScan
#undef emberStartEnergyScan
#undef emberStartTxStream
#undef emberStopTxStream

#endif // __API_RENAME_UNDEF_H__
