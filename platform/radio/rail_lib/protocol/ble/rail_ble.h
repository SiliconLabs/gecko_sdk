/***************************************************************************//**
 * @file
 * @brief The BLE specific header file for the RAIL library.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef __RAIL_BLE_H__
#define __RAIL_BLE_H__

// Get the standard include types
#include <stdint.h>
#include <stdbool.h>

// Get the RAIL specific structures and types
#include "rail_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @addtogroup BLE
/// @ingroup Protocol_Specific
/// Accelerator routines for Bluetooth Low Energy (BLE).
///
/// The APIs in this module configure the radio for BLE
/// operation and provide additional helper routines necessary for
/// normal BLE send/receive that aren't available directly in RAIL.
/// RAIL APIs should be used to set up the application. However,
/// RAIL_ConfigChannels() and RAIL_ConfigRadio() should not be called to set up
/// the PHY. Instead, RAIL_BLE_Config* APIs should be used to set up the
/// 1 Mbps, 2 Mbps, or Coded PHY configurations needed by the application. These
/// APIs will configure the hardware and also configure the set of valid BLE
/// channels.
///
/// To implement a standard BLE link layer, you will also need to handle tight
/// turnaround times and send packets at specific instants. This can all be
/// managed through general RAIL functions, such as RAIL_ScheduleTx(),
/// RAIL_ScheduleRx(), and RAIL_SetStateTiming(). See RAIL APIs for more
/// useful functions.
///
/// A simple example to set up the application to be in BLE mode is shown
/// below. Note that this will put the radio on the first advertising channel
/// with the advertising Access Address. In any full-featured BLE application you
/// will need to use the RAIL_BLE_ConfigChannelRadioParams() function to change
/// the sync word and other parameters as needed based on your connection.
///
/// @code{.c}
///
/// // RAIL Handle set at initialization time.
/// static RAIL_Handle_t gRailHandle = NULL;
///
/// static void radioEventHandler(RAIL_Handle_t railHandle,
///                               RAIL_Events_t events)
/// {
///   // ... handle RAIL events, e.g., receive and transmit completion
/// }
///
/// #if MULTIPROTOCOL
/// // Allocate memory for RAIL to hold BLE-specific state information
/// static RAIL_BLE_State_t bleState; // Must never be const
/// static RAILSched_Config_t schedCfg; // Must never be const
/// static RAIL_Config_t railCfg = {  // Must never be const
///   .eventsCallback = &radioEventHandler,
///   .protocol = &bleState, // For BLE, RAIL needs additional state memory
///   .scheduler = &schedCfg, // For MultiProtocol, additional scheduler memory
/// };
/// #else
/// static RAIL_Config_t railCfg = {  // Must never be const
///   .eventsCallback = &radioEventHandler,
///   .protocol = NULL,
///   .scheduler = NULL,
/// };
/// #endif
///
/// // Set the radio to receive on the first BLE advertising channel.
/// int bleAdvertiseEnable(void)
/// {
///   // Initializes the RAIL library and any internal state it requires.
///   gRailHandle = RAIL_Init(&railCfg, NULL);
///
///   // Calls the BLE initialization function to load the right radio configuration.
///   RAIL_BLE_Init(gRailHandle);
///
///   // Always choose the Viterbi PHY configuration if available on your chip
///   // for performance reasons.
///   RAIL_BLE_ConfigPhy1MbpsViterbi(gRailHandle);
///
///   // Configures us for the first advertising channel (Physical: 0, Logical: 37).
///   // The CRC init value and Access Address come from the BLE specification.
///   RAIL_BLE_ConfigChannelRadioParams(gRailHandle,
///                                     0x555555,
///                                     0x8E89BED6,
///                                     37,
///                                     false);
///
///   // Starts receiving on physical channel 0 (logical channel 37).
///   RAIL_StartRx(gRailHandle, 0, NULL);
///  }
/// @endcode
///
/// @{

/**
 * @enum RAIL_BLE_Coding_t
 * @brief The variant of the BLE Coded PHY.
 */
RAIL_ENUM(RAIL_BLE_Coding_t) {
  /** Enables the 125 kbps variant of the BLE Coded PHY */
  RAIL_BLE_Coding_125kbps = 0,
  /** @deprecated Will be removed in a future version of RAIL */
  RAIL_BLE_Coding_125kbps_DSA = 1,
  /** Enables the 500 kbps variant of the BLE Coded PHY */
  RAIL_BLE_Coding_500kbps = 2,
  /** @deprecated Will be removed in a future version of RAIL */
  RAIL_BLE_Coding_500kbps_DSA = 3,
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Self-referencing defines minimize compiler complaints when using RAIL_ENUM
#define RAIL_BLE_Coding_125kbps     ((RAIL_BLE_Coding_t) RAIL_BLE_Coding_125kbps)
#define RAIL_BLE_Coding_125kbps_DSA ((RAIL_BLE_Coding_t) RAIL_BLE_Coding_125kbps_DSA)
#define RAIL_BLE_Coding_500kbps     ((RAIL_BLE_Coding_t) RAIL_BLE_Coding_500kbps)
#define RAIL_BLE_Coding_500kbps_DSA ((RAIL_BLE_Coding_t) RAIL_BLE_Coding_500kbps_DSA)
#endif //DOXYGEN_SHOULD_SKIP_THIS

/**
 * @enum RAIL_BLE_Phy_t
 * @brief The variant of the BLE PHY.
 */
RAIL_ENUM(RAIL_BLE_Phy_t) {
  /** Use the standard BLE 1Mbps PHY */
  RAIL_BLE_1Mbps,
  /** Use the high data rate BLE 2Mbps PHY */
  RAIL_BLE_2Mbps,
  /** Enables the 125 kbps variant of the BLE Coded PHY */
  RAIL_BLE_Coded125kbps,
  /** Enables the 500 kbps variant of the BLE Coded PHY */
  RAIL_BLE_Coded500kbps,
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Self-referencing defines minimize compiler complaints when using RAIL_ENUM
#define RAIL_BLE_1Mbps        ((RAIL_BLE_Phy_t) RAIL_BLE_1Mbps)
#define RAIL_BLE_2Mbps        ((RAIL_BLE_Phy_t) RAIL_BLE_2Mbps)
#define RAIL_BLE_Coded125kbps ((RAIL_BLE_Phy_t) RAIL_BLE_Coded125kbps)
#define RAIL_BLE_Coded500kbps ((RAIL_BLE_Phy_t) RAIL_BLE_Coded500kbps)
#endif //DOXYGEN_SHOULD_SKIP_THIS

/// @addtogroup BLE_PHY BLE Radio Configurations
/// Radio configurations for the RAIL BLE Accelerator
///
/// These radio configurations are used to configure BLE when a function such
/// as \ref RAIL_BLE_ConfigPhy1MbpsViterbi() is called. Each radio
/// configuration listed below is compiled into the RAIL library as a weak
/// symbol that will take into account per-die defaults. If the board
/// configuration in use has different settings than the default, such as a
/// different radio subsystem clock frequency, these radio configurations can
/// be overriden to account for those settings.
/// @{

/**
 * Default PHY to use for BLE 1M non-Viterbi. Will be NULL if
 * \ref RAIL_BLE_SUPPORTS_1MBPS_NON_VITERBI is 0.
 */
extern const RAIL_ChannelConfig_t *const RAIL_BLE_Phy1Mbps;

/**
 * Default PHY to use for BLE 2M non-Viterbi. Will be NULL if
 * \ref RAIL_BLE_SUPPORTS_2MBPS_NON_VITERBI is 0.
 */
extern const RAIL_ChannelConfig_t *const RAIL_BLE_Phy2Mbps;

/**
 * Default PHY to use for BLE 1M Viterbi. Will be NULL if
 * \ref RAIL_BLE_SUPPORTS_1MBPS_VITERBI is 0.
 */
extern const RAIL_ChannelConfig_t *const RAIL_BLE_Phy1MbpsViterbi;

/**
 * Default PHY to use for BLE 2M Viterbi. Will be NULL if
 * \ref RAIL_BLE_SUPPORTS_2MBPS_VITERBI is 0.
 */
extern const RAIL_ChannelConfig_t *const RAIL_BLE_Phy2MbpsViterbi;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/**
 * Default PHY to use for BLE 1M Viterbi HADM. Will be NULL if
 * \ref RAIL_BLE_SUPPORTS_HADM is 0. On EFR32XG24, this will also
 * be NULL for non 40MHz HFXO frequencies.
 */
extern const RAIL_ChannelConfig_t *const RAIL_BLE_Phy1MbpsViterbiHadm;

/**
 * Default PHY to use for BLE 2M Viterbi HADM. Will be NULL if
 * \ref RAIL_BLE_SUPPORTS_HADM is 0. On EFR32XG24, this will also
 * be NULL for non 40MHz HFXO frequencies.
 */
extern const RAIL_ChannelConfig_t *const RAIL_BLE_Phy2MbpsViterbiHadm;
#endif

/**
 * PHY to use for BLE 2M with AoX functionality. Will be NULL if either
 * \ref RAIL_BLE_SUPPORTS_2MBPS_VITERBI or \ref RAIL_BLE_SUPPORTS_AOX is 0.
 */
extern const RAIL_ChannelConfig_t *const RAIL_BLE_Phy2MbpsAox;

/**
 * Default PHY to use for BLE Coded 125kbps. Will be NULL if
 * \ref RAIL_BLE_SUPPORTS_CODED_PHY is 0. This PHY can receive on both
 * 125kbps and 500kbps BLE Coded, but will only transmit at 125kbps.
 */
extern const RAIL_ChannelConfig_t *const RAIL_BLE_Phy125kbps;

/**
 * Default PHY to use for BLE Coded 500kbps. Will be NULL if
 * \ref RAIL_BLE_SUPPORTS_CODED_PHY is 0. This PHY can receive on both
 * 125kbps and 500kbps BLE Coded, but will only transmit at 125kbps.
 */
extern const RAIL_ChannelConfig_t *const RAIL_BLE_Phy500kbps;

/**
 * Default PHY to use for BLE Simulscan. Will be NULL if
 * \ref RAIL_BLE_SUPPORTS_SIMULSCAN_PHY is 0. This PHY can receive on 1Mbps
 * as well as 125kbps and 500kbps BLE Coded, but will only transmit at 1Mbps.
 */
extern const RAIL_ChannelConfig_t *const RAIL_BLE_PhySimulscan;

/**
 * Default 1Mbps Quuppa PHY. Will be NULL if
 * \ref RAIL_BLE_SUPPORTS_QUUPPA is 0.
 */
extern const RAIL_ChannelConfig_t *const RAIL_BLE_PhyQuuppa;

/// @} // End of group BLE_PHY

// Defines for subPhyID field in RAIL_RxPacketDetails_t
/** subPhyId indicating a 500kbps packet */
#define RAIL_BLE_RX_SUBPHY_ID_500K     (0U)
/** subPhyId indicating a 125kbps packet */
#define RAIL_BLE_RX_SUBPHY_ID_125K     (1U)
/** subPhyId value indicating a 1Mbps packet */
#define RAIL_BLE_RX_SUBPHY_ID_1M       (2U)
/** Invalid subPhyId value */
#define RAIL_BLE_RX_SUBPHY_ID_INVALID  (3U)
/** subPhyId indicating the total count */
#define RAIL_BLE_RX_SUBPHY_COUNT       (4U)

/**
 * @enum RAIL_BLE_SignalIdentifierMode_t
 * @brief Available Signal Identifier modes.
 */
RAIL_ENUM(RAIL_BLE_SignalIdentifierMode_t) {
  /* Disable signal detection mode. */
  RAIL_BLE_SIGNAL_IDENTIFIER_MODE_DISABLE = 0,
  /* BLE 1Mbps (GFSK) detection mode. */
  RAIL_BLE_SIGNAL_IDENTIFIER_MODE_1MBPS,
  /* BLE 2Mbps (GFSK) detection mode. */
  RAIL_BLE_SIGNAL_IDENTIFIER_MODE_2MBPS
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Self-referencing defines minimize compiler complaints when using RAIL_ENUM
#define RAIL_BLE_SIGNAL_IDENTIFIER_MODE_DISABLE ((RAIL_BLE_SignalIdentifierMode_t)RAIL_BLE_SIGNAL_IDENTIFIER_MODE_DISABLE)
#define RAIL_BLE_SIGNAL_IDENTIFIER_MODE_1MBPS   ((RAIL_BLE_SignalIdentifierMode_t)RAIL_BLE_SIGNAL_IDENTIFIER_MODE_1MBPS)
#define RAIL_BLE_SIGNAL_IDENTIFIER_MODE_2MBPS   ((RAIL_BLE_SignalIdentifierMode_t)RAIL_BLE_SIGNAL_IDENTIFIER_MODE_2MBPS)
#endif

/**
 * @struct RAIL_BLE_State_t
 * @brief A state structure for BLE.
 *
 * This structure must be allocated in application global read-write memory
 * that persists for the duration of BLE usage. It cannot be allocated
 * in read-only memory or on the call stack.
 */
typedef struct RAIL_BLE_State {
  uint32_t crcInit; /**< The value used to initialize the CRC algorithm. */
  uint32_t accessAddress; /**< The access address used for the connection. */
  uint16_t channel; /**< The logical channel used. */
  bool disableWhitening; /**< Indicates whether the whitening engine should be off. */
  uint16_t whiteInit; /**< The value used to initialize the whitening algorithm */
} RAIL_BLE_State_t;

/**
 * Configure RAIL to run in BLE mode.
 *
 * @param[in] railHandle A handle for RAIL instance.
 * This function changes your radio, channel configuration, and other
 * parameters to match what is needed for BLE. To switch back to a
 * default RAIL mode, call RAIL_BLE_Deinit() first. This function
 * will configure the protocol output on PTI to \ref RAIL_PTI_PROTOCOL_BLE.
 *
 * @note BLE may not be enabled while Auto-ACKing is enabled.
 */
void RAIL_BLE_Init(RAIL_Handle_t railHandle);

/**
 * Take RAIL out of BLE mode.
 *
 * @param[in] railHandle A handle for RAIL instance.
 * This function will undo some of the configuration that happens when you call
 * RAIL_BLE_Init(). After this you can safely run your normal radio
 * initialization code to use a non-BLE configuration. This function does \b
 * not change back your radio or channel configurations so you must do this by
 * manually reinitializing. This also resets the protocol output on PTI to \ref
 * RAIL_PTI_PROTOCOL_CUSTOM.
 */
void RAIL_BLE_Deinit(RAIL_Handle_t railHandle);

/**
 * Determine whether BLE mode is enabled or not.
 *
 * @param[in] railHandle A handle for RAIL instance.
 * @return True if BLE mode is enabled and false otherwise.
 * This function returns the current status of RAIL's BLE mode. It is enabled by
 * a call to RAIL_BLE_Init() and disabled by a call to RAIL_BLE_Deinit().
 */
bool RAIL_BLE_IsEnabled(RAIL_Handle_t railHandle);

/**
 * Switch to the 1 Mbps Quuppa PHY.
 *
 * @param[in] railHandle A handle for RAIL instance.
 * @return Status code indicating success of the function call.
 *
 * You can use this function to switch to the Quuppa PHY.
 *
 * @note Not all chips support the 1Mbps Quuppa PHY. This API should return RAIL_STATUS_INVALID_CALL if
 * unsupported by the hardware we're building for.
 */
RAIL_Status_t RAIL_BLE_ConfigPhyQuuppa(RAIL_Handle_t railHandle);

/**
 * Switch to the Viterbi 1 Mbps BLE PHY.
 *
 * @param[in] railHandle A handle for RAIL instance.
 * @return A status code indicating success of the function call.
 *
 * Use this function to switch back to the default BLE 1 Mbps PHY if you
 * have switched to the 2 Mbps or another configuration. You may only call this
 * function after initializing BLE and while the radio is idle.
 *
 * @note The EFR32XG1 family does not support BLE Viterbi PHYs. However, calls
 *   to this function from that family will be silently redirected to the legacy
 *   \ref RAIL_BLE_ConfigPhy1Mbps().
 */
RAIL_Status_t RAIL_BLE_ConfigPhy1MbpsViterbi(RAIL_Handle_t railHandle);

/**
 * Switch to the legacy non-Viterbi 1 Mbps BLE PHY.
 *
 * @param[in] railHandle A handle for RAIL instance.
 * @return A status code indicating success of the function call.
 *
 * Use this function to switch back to the legacy BLE 1 Mbps PHY if you
 * have switched to the 2 Mbps or another configuration. You may only call this
 * function after initializing BLE and while the radio is idle.
 *
 * @note The EFR32XG2x family does not support BLE non-Viterbi PHYs.
 */
RAIL_Status_t RAIL_BLE_ConfigPhy1Mbps(RAIL_Handle_t railHandle);

/**
 * Switch to the Viterbi 2 Mbps BLE PHY.
 *
 * @param[in] railHandle A handle for RAIL instance.
 * @return A status code indicating success of the function call.
 *
 * Use this function to switch back to the BLE 2 Mbps PHY from the
 * default 1 Mbps option. You may only call this function after initializing BLE
 * and while the radio is idle.
 *
 * @note The EFR32XG1 family does not support BLE Viterbi PHYs.
 */
RAIL_Status_t RAIL_BLE_ConfigPhy2MbpsViterbi(RAIL_Handle_t railHandle);

/**
 * Switch to the legacy non-Viterbi 2 Mbps BLE PHY.
 *
 * @param[in] railHandle A handle for RAIL instance.
 * @return A status code indicating success of the function call.
 *
 * Use this function to switch back to legacy BLE 2Mbps PHY from the
 * default 1 Mbps option. You may only call this function after initializing BLE
 * and while the radio is idle.
 *
 * @note The EFR32XG1 and EFR32XG2x families do not support BLE non-Viterbi
 *   2 Mbps PHY.
 */
RAIL_Status_t RAIL_BLE_ConfigPhy2Mbps(RAIL_Handle_t railHandle);

/**
 * Switch to the BLE Coded PHY.
 *
 * @param[in] railHandle A handle for RAIL instance.
 * @param[in] bleCoding The RAIL_BLE_Coding_t to use
 * @return A status code indicating success of the function call.
 *
 * Use this function to switch back to BLE Coded PHY from the default
 * 1 Mbps option. You may only call this function after initializing BLE and
 * while the radio is idle. When using a BLE Coded PHY, the \ref
 * RAIL_RxPacketDetails_t::subPhyId marks the coding of the received packet.
 * A subPhyId of 0 marks a 500 kbps packet, and a subPhyId of 1 marks a 125
 * kbps packet.
 *
 * @note The EFR32XG1, EFR32XG12, and EFR32XG14 families do not support BLE
 *   Coded PHYs.
 */
RAIL_Status_t RAIL_BLE_ConfigPhyCoded(RAIL_Handle_t railHandle,
                                      RAIL_BLE_Coding_t bleCoding);

/**
 * Switch to the Simulscan PHY.
 *
 * @param[in] railHandle A handle for RAIL instance.
 * @return A status code indicating success of the function call.
 *
 * Use this function to switch to the BLE Simulscan PHY. You may only
 * call this function after initializing BLE and while the radio is idle.
 * When using Simulscan PHY, the \ref RAIL_RxPacketDetails_t::subPhyId
 * marks the coding of the received packet. A subPhyId of 0 marks a
 * 500 kbps packet, a subPhyId of 1 marks a 125 kbps packet, and a
 * subPhyId of 2 marks a 1 Mbps packet.
 *
 * @note: The Simulscan PHY is supported only on some 2.4 GHz Series-2 parts.
 * The preprocessor symbol \ref RAIL_BLE_SUPPORTS_SIMULSCAN_PHY and the
 * runtime function \ref RAIL_BLE_SupportsSimulscanPhy() may be used to
 * test for support of the Simulscan PHY.
 */
RAIL_Status_t RAIL_BLE_ConfigPhySimulscan(RAIL_Handle_t railHandle);

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/**
 * Switch to the 1 Mbps BLE PHY for HADM.
 *
 * @param[in] railHandle A handle for RAIL instance.
 * @return A status code indicating success of the function call.
 *
 * Use this function to switch back to the BLE 1 Mbps HADM PHY from
 * another configuration. You may only call this
 * function after initializing BLE and while the radio is idle.
 *
 * @note This PHY is only supported when \ref RAIL_BLE_SUPPORTS_HADM is not 0.
 */
RAIL_Status_t RAIL_BLE_ConfigPhy1MbpsHadm(RAIL_Handle_t railHandle);

/**
 * Switch to the 2 Mbps BLE PHY for HADM.
 *
 * @param[in] railHandle A handle for RAIL instance.
 * @return A status code indicating success of the function call.
 *
 * Use this function to switch back to the BLE 2 Mbps HADM PHY from
 * another configuration. You may only call this
 * function after initializing BLE and while the radio is idle.
 *
 * @note This PHY is only supported when \ref RAIL_BLE_SUPPORTS_HADM is not 0.
 */
RAIL_Status_t RAIL_BLE_ConfigPhy2MbpsHadm(RAIL_Handle_t railHandle);
#endif

/**
 * Change BLE radio parameters.
 *
 * @param[in] railHandle A handle for RAIL instance.
 * @param[in] crcInit The value to use for CRC initialization.
 * @param[in] accessAddress The access address to use for the connection. The
 * bits of this parameter are transmitted or received LSB first.
 * @param[in] channel The logical channel that you're changing to, which
 * initializes the whitener if used.
 * @param[in] disableWhitening This can turn off the whitening engine and is useful
 * for sending BLE test mode packets that don't have this turned on.
 * @return A status code indicating success of the function call.
 *
 * This function can be used to switch radio parameters on every connection
 * and/or channel change. It is BLE-aware and will set the access address,
 * preamble, CRC initialization value, and whitening configuration without
 * requiring you to load a new radio configuration. This function should not be
 * called while the radio is active.
 */
RAIL_Status_t RAIL_BLE_ConfigChannelRadioParams(RAIL_Handle_t railHandle,
                                                uint32_t crcInit,
                                                uint32_t accessAddress,
                                                uint16_t channel,
                                                bool disableWhitening);

/**
 * Change the current BLE PHY and go into receive.
 *
 * @param[in] railHandle A handle for RAIL instance.
 * @param[in] phy Indicates which PHY to receive on
 * @param[in] railChannel Which channel of the given PHY to receive on
 * @param[in] startRxTime When to enter RX
 * @param[in] crcInit The value to use for CRC initialization.
 * @param[in] accessAddress The access address to use for the connection.  The
 * bits of this parameter are transmitted or received LSB first.
 * @param[in] logicalChannel The logical channel that you're changing to, which
 * initializes the whitener if used.
 * @param[in] disableWhitening This can turn off the whitening engine and is useful
 * for sending BLE test mode packets that don't have this turned on.
 * @return A status code indicating success of the function call.
 *
 * This function is used to implement auxiliary packet reception, as defined in
 * the BLE specification. The radio will be put into IDLE, the PHY and channel
 * will be changed, and then receive will be entered at the start time given.
 * The new receive will have a timeout of 30 us, which means that this function
 * should only be called if the offset unit is 30 us.
 *
 * This function is extremely time-sensitive, and may only be called within the
 * interrupt context of a \ref RAIL_EVENT_RX_PACKET_RECEIVED event.
 */
RAIL_Status_t RAIL_BLE_PhySwitchToRx(RAIL_Handle_t railHandle,
                                     RAIL_BLE_Phy_t phy,
                                     uint16_t railChannel,
                                     uint32_t startRxTime,
                                     uint32_t crcInit,
                                     uint32_t accessAddress,
                                     uint16_t logicalChannel,
                                     bool disableWhitening);

/**
 * Configure and enable signal identifier for BLE signal detection.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @param[in] signalIdentifierMode Mode of signal identifier operation.
 *
 * This features allows detection of BLE signal on air based on the mode.
 * This function must be called once before \ref RAIL_BLE_EnableSignalDetection
 * to configure and enable signal identifier.
 *
 * To enable event for signal detection \ref RAIL_ConfigEvents() must be called
 * for enabling \ref RAIL_EVENT_SIGNAL_DETECTED.
 *
 * This function is only supported by chips where
 * \ref RAIL_BLE_SUPPORTS_SIGNAL_IDENTIFIER and
 * \ref RAIL_BLE_SupportsSignalIdentifier() are true.
 *
 * @return Status code indicating success of the function call.
 */
RAIL_Status_t RAIL_BLE_ConfigSignalIdentifier(RAIL_Handle_t railHandle,
                                              RAIL_BLE_SignalIdentifierMode_t signalIdentifierMode);

/**
 * Enable or disable signal identifier interrupt for BLE signal detection.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @param[in] enable Signal detection is enabled if true, disabled if false.
 *
 * \ref RAIL_BLE_ConfigSignalIdentifier must be called once before calling this
 * function to configure and enable signal identifier.
 * Once a signal is detected signal detection will be turned off and this
 * function should be called to re-enable the signal detection without needing
 * to call \ref RAIL_BLE_ConfigSignalIdentifier if the signal identifier
 * is already configured and enabled.
 *
 * This function is only supported by chips where
 * \ref RAIL_BLE_SUPPORTS_SIGNAL_IDENTIFIER and
 * \ref RAIL_BLE_SupportsSignalIdentifier() are true.
 *
 * @return Status code indicating success of the function call.
 */
RAIL_Status_t RAIL_BLE_EnableSignalDetection(RAIL_Handle_t railHandle,
                                             bool enable);

/**
 * @brief Backward compatible name for the \ref
 * RAIL_BLE_EnableSignalDetection API.
 */
#define RAIL_BLE_EnableSignalIdentifier RAIL_BLE_EnableSignalDetection

/******************************************************************************
 * Angle of Arrival/Departure (AoX)
 *****************************************************************************/
/**
 * @addtogroup AoX Angle of Arrival/Departure
 * @{
 * @brief These APIs are to a stack implementing BLE's angle of arrival and
 * angle of departure functionality.
 *
 * They are designed for use by the Silicon Labs BLE stack only at this time and
 * may cause problems if accessed directly.
 */

/**
 *
 * The maximum number of GPIO pins used for AoX Antenna switching.
 *
 * If the user configures more pins using
 * \ref RAIL_BLE_ConfigAoxAntenna than allowed
 * \ref RAIL_BLE_AOX_ANTENNA_PIN_COUNT, then
 * \ref RAIL_STATUS_INVALID_PARAMETER status will be returned.
 *
 * \ref RAIL_STATUS_INVALID_CALL is returned if :
 * \ref RAIL_BLE_AOX_ANTENNA_PIN_COUNT is set to 0 or
 * The user configures no pins.
 *
 * The maximum value \ref RAIL_BLE_AOX_ANTENNA_PIN_COUNT can take depends on
 * number of Antenna route pins , a chip provides.
 * For EFR32XG22, the maximum value of \ref RAIL_BLE_AOX_ANTENNA_PIN_COUNT is 6.
 * If the user configures fewer pins than \ref RAIL_BLE_AOX_ANTENNA_PIN_COUNT,
 * then only number of pins asked by user will be configured with
 * \ref RAIL_STATUS_NO_ERROR.
 *
 */
#define RAIL_BLE_AOX_ANTENNA_PIN_COUNT (6U)

/**
 * @enum RAIL_BLE_AoxOptions_t
 * @brief Angle of Arrival/Departure options bit fields
 */
RAIL_ENUM_GENERIC(RAIL_BLE_AoxOptions_t, uint16_t) {
  /** Shift position of \ref RAIL_BLE_AOX_OPTIONS_SAMPLE_MODE bit */
  RAIL_BLE_AOX_OPTIONS_SAMPLE_MODE_SHIFT = 0,
  /** Shift position of \ref RAIL_BLE_AOX_OPTIONS_CONNLESS bit */
  RAIL_BLE_AOX_OPTIONS_CONNLESS_SHIFT = 1,
  /** Shift position of \ref RAIL_BLE_AOX_OPTIONS_CONN bit */
  RAIL_BLE_AOX_OPTIONS_CONN_SHIFT = 2,
  /** Shift position of \ref RAIL_BLE_AOX_OPTIONS_DISABLE_BUFFER_LOCK bit */
  RAIL_BLE_AOX_OPTIONS_DISABLE_BUFFER_LOCK_SHIFT = 3,
};

/**
 * @deprecated Obsolete AOX option
 */
#define RAIL_BLE_AOX_OPTIONS_DO_SWITCH           (0U)
/**
 * @deprecated Obsolete AOX option
 */
#define RAIL_BLE_AOX_OPTIONS_TX_ENABLED          (0U)
/**
 * @deprecated Obsolete AOX option
 */
#define RAIL_BLE_AOX_OPTIONS_RX_ENABLED          (0U)
/**
 * @deprecated Please use \ref RAIL_BLE_AOX_OPTIONS_DISABLE_BUFFER_LOCK_SHIFT instead.
 */
#define RAIL_BLE_AOX_OPTIONS_LOCK_CTE_BUFFER_SHIFT RAIL_BLE_AOX_OPTIONS_DISABLE_BUFFER_LOCK_SHIFT

/**
 * Disable the AoX feature.
 */
#define RAIL_BLE_AOX_OPTIONS_DISABLED            (0U)
/**
 * Sets one of the two AoX sampling/switching modes: 1 us or 2 us window.
 */
#define RAIL_BLE_AOX_OPTIONS_SAMPLE_MODE         (1U << RAIL_BLE_AOX_OPTIONS_SAMPLE_MODE_SHIFT)
/**
 * Enables connectionless AoX Rx packets.
 */
#define RAIL_BLE_AOX_OPTIONS_CONNLESS            (1U << RAIL_BLE_AOX_OPTIONS_CONNLESS_SHIFT)
/**
 * Enables connection based AoX Rx packets.
 */
#define RAIL_BLE_AOX_OPTIONS_CONN                (1U << RAIL_BLE_AOX_OPTIONS_CONN_SHIFT)
/**
 * Disables CTE buffer lock.
 */
#define RAIL_BLE_AOX_OPTIONS_DISABLE_BUFFER_LOCK (1U << RAIL_BLE_AOX_OPTIONS_DISABLE_BUFFER_LOCK_SHIFT)
/**
 * Enables connection based or connectionless AoX Rx packets.
 */
#define RAIL_BLE_AOX_OPTIONS_ENABLED             (RAIL_BLE_AOX_OPTIONS_CONN | RAIL_BLE_AOX_OPTIONS_CONNLESS)

/**
 * @struct RAIL_BLE_AoxConfig_t
 * @brief Contains arguments for \ref RAIL_BLE_ConfigAox function.
 */
typedef struct RAIL_BLE_AoxConfig {
  /**
   * See RAIL_BLE_AOX_OPTIONS_* for bitfield defines for different AoX features.
   */
  RAIL_BLE_AoxOptions_t aoxOptions;
  /**
   * Size of the raw AoX CTE (continuous tone extension) data capture buffer in
   * bytes. Note this value should be a multiple of 4 as each IQ sample
   * requires 4 bytes.
   */
  uint16_t cteBuffSize;
  /**
   * Address to where the received CTE is written. Buffer must be 32-bit
   * aligned.
   */
  uint32_t * cteBuffAddr;
  /**
   * Address to first element of antenna pattern array. Array must be in RAM.
   * Each element of the array contains an antenna number. The switching pattern
   * is defined by the order of antennas in this array.
   */
  uint8_t * antArrayAddr;
  /**
   * Size of the antenna pattern array.
   */
  uint8_t antArraySize;
} RAIL_BLE_AoxConfig_t;

/**
 * @struct RAIL_BLE_AoxAntennaPortPins_t
 * @brief Contains elements of \ref RAIL_BLE_AoxAntennaConfig_t struct.
 */
typedef struct RAIL_BLE_AoxAntennaPortPins {
  /**
   * The port which is used for AoX antenna switching
   */
  uint8_t antPort;
  /**
   * The pin which is used for AoX antenna switching
   */
  uint8_t antPin;
} RAIL_BLE_AoxAntennaPortPins_t;

/**
 * @struct RAIL_BLE_AoxAntennaConfig_t
 * @brief Contains arguments for \ref RAIL_BLE_ConfigAoxAntenna function for
 * EFR32XG22.
 */
typedef struct RAIL_BLE_AoxAntennaConfig {
  /**
   * A pointer to an array containing struct of port and pin used for
   * AoX antenna switching
   */
  RAIL_BLE_AoxAntennaPortPins_t *antPortPin;
  /**
   * Number of antenna pins to be configured.
   */
  uint8_t antCount;
} RAIL_BLE_AoxAntennaConfig_t;

/**
 * Lock/unlock the CTE buffer from the application's perspective. The radio
 * will write to the buffer only if the bit is NOT set at the beginning of the
 * sampling period. The radio will set the bit once the sampling period starts
 * to indicate that some CTE data has been collected, which will not be
 * overwritten during the next sampling period, unless the buffer is unlocked by
 * the application.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @param[in] lock Lock the CTE buffer if true and unlock it if false.
 * @return True if the CTE buffer is locked after the call, otherwise false.
 */
bool RAIL_BLE_LockCteBuffer(RAIL_Handle_t railHandle, bool lock);

/**
 * Determine whether the CTE buffer is currently locked or not.
 *
 * @param[in] railHandle A handle for RAIL instance.
 * @return True if CTE buffer is locked and false otherwise.
 */
bool RAIL_BLE_CteBufferIsLocked(RAIL_Handle_t railHandle);

/**
 * Get the offset into CTE sample of CTE data.
 *
 * @param[in] railHandle A handle for RAIL instance.
 * @return The offset of CTE data in a CTE sample in bytes.
 * On unsupported platforms this returns 0.
 */
uint8_t RAIL_BLE_GetCteSampleOffset(RAIL_Handle_t railHandle);

/**
 * Get the effective sample rate used by the ADC to capture the CTE samples.
 *
 * @param[in] railHandle A handle for RAIL instance.
 * @return The actual sample rate used to capture the CTE in samples per second.
 * On unsupported platforms this returns 0.
 */
uint32_t RAIL_BLE_GetCteSampleRate(RAIL_Handle_t railHandle);

/**
 * Configure Angle of Arrival/Departure (AoX) functionality. AoX is a method
 * of radio localization which infers angle of arrival/departure of the signal
 * based on different phases of the raw I/Q signal from different antennas by
 * controlling external RF switch during the continuous tone extension (CTE).
 * Connection based AoX packets are different than normal BLE packets in that
 * they have 3 header bytes instead of 2 and they have CTE appended after the
 * payload's CRC. 3rd byte or CTE info contains CTE length. Connectionless AoX
 * packets have 2 header bytes and CTE info is part of the payload. AoX is
 * supported on EFR32XG12/13/14 only on legacy 1Mbps BLE PHY.
 * Note that calling \ref RAIL_GetRadioEntropy during AoX reception may break
 * receiving packets.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @param[in] aoxConfig Configuration options for AoX
 * @return RAIL_Status_t indicating success or failure of the call.
 */
RAIL_Status_t RAIL_BLE_ConfigAox(RAIL_Handle_t railHandle,
                                 const RAIL_BLE_AoxConfig_t *aoxConfig);
/**
 * Perform one time initialization of AoX registers.
 * This function must be called before \ref RAIL_BLE_ConfigAox
 * and before configuring the BLE PHY.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return RAIL_Status_t indicating success or failure of the call.
 */
RAIL_Status_t RAIL_BLE_InitCte(RAIL_Handle_t railHandle);

/**
 * Perform initialization of AoX antenna GPIO pins.
 * This function must be called before calls to \ref RAIL_BLE_InitCte
 * and \ref RAIL_BLE_ConfigAox, and before configuring the BLE PHY,
 * else a \ref RAIL_STATUS_INVALID_CALL is returned.
 *
 * If user configures more pins, i.e., antCount in
 * \ref RAIL_BLE_AoxAntennaConfig_t, than allowed
 * \ref RAIL_BLE_AOX_ANTENNA_PIN_COUNT, then the API returns
 * \ref RAIL_STATUS_INVALID_PARAMETER.
 *
 * If user configures lesser than or equal to number of pins allowed by
 * \ref RAIL_BLE_AOX_ANTENNA_PIN_COUNT, then the requested number of pins
 * are configured and \ref RAIL_STATUS_NO_ERROR is returned.
 *
 * If AoX antenna switching is inactive, non-AoX transmits and receives
 * will occur on the first antenna specified by the antenna pattern or
 * on the default antenna if no antenna pattern is provided.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @param[in] antennaConfig structure to hold the set of ports and pins to
 * configure Antenna pins for AoX Antenna switching.
 * @return RAIL_Status_t indicating success or failure of the call.
 */
RAIL_Status_t RAIL_BLE_ConfigAoxAntenna(RAIL_Handle_t railHandle,
                                        RAIL_BLE_AoxAntennaConfig_t *antennaConfig);

/** @} */  // end of group AoX

 #ifndef DOXYGEN_SHOULD_SKIP_THIS
/******************************************************************************
 * High Accuracy Distance Measurement (HADM)
 *****************************************************************************/
/**
 * @addtogroup HADM High Accuracy Distance Measurement
 * @{
 * @brief These APIs are to a stack implementing BLE's high accuracy distance
 * measurement functionality.
 *
 * They are designed for use by the Silicon Labs BLE stack only at this time and
 * may cause problems if accessed directly.
 */

/**
 * @enum RAIL_BLE_HadmRole_t
 * @brief The device role during HADM events.
 */
RAIL_ENUM(RAIL_BLE_HadmRole_t) {
  /** Device cannot perform HADM events. */
  RAIL_BLE_HADM_ROLE_UNASSIGNED = 0,
  /** Device is an initiator during HADM events */
  RAIL_BLE_HADM_ROLE_INITIATOR = 1,
  /** Device is a reflector during HADM events */
  RAIL_BLE_HADM_ROLE_REFLECTOR = 2,
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Self-referencing defines minimize compiler complaints when using RAIL_ENUM
#define RAIL_BLE_HADM_ROLE_UNASSIGNED ((RAIL_BLE_HadmRole_t) RAIL_BLE_HADM_ROLE_UNASSIGNED)
#define RAIL_BLE_HADM_ROLE_INITIATOR  ((RAIL_BLE_HadmRole_t) RAIL_BLE_HADM_ROLE_INITIATOR)
#define RAIL_BLE_HADM_ROLE_REFLECTOR  ((RAIL_BLE_HadmRole_t) RAIL_BLE_HADM_ROLE_REFLECTOR)
#endif//DOXYGEN_SHOULD_SKIP_THIS

/**
 * @struct RAIL_BLE_HadmResults_t
 * @brief Contains measurement results from HADM step
 */
typedef struct {
  uint32_t result[7]; /**< HADM measurement data for a particular step. */
} RAIL_BLE_HadmResults_t;

/**
 * @enum RAIL_BLE_HadmRttType_t
 * @brief HADM RTT Types.
 */
RAIL_ENUM(RAIL_BLE_HadmRttType_t) {
  /** Coarse cost function engine method RTT. */
  RAIL_BLE_HADM_RTT_AA_ONLY = 0U,
  /** 32 bit sounding sequence method RTT. */
  RAIL_BLE_HADM_RTT_32B_SS = 1U,
  /** 96 bit sounding sequence method RTT. */
  RAIL_BLE_HADM_RTT_96B_SS = 2U,
};

/**
 *  The minimum size in 32 bit words for the IQ buffer. This value guarantees
 *  all IQ samples for a single 1mbps HADM step can be stored.
 */
#define RAIL_BLE_HADM_1MBPS_MINIMUM_IQ_BUFFER_SIZE  600

/**
 * @struct RAIL_BLE_HadmConfig_t
 * @brief Contains arguments for \ref RAIL_BLE_ConfigHadm function.
 */
typedef struct RAIL_BLE_HadmConfig {
  RAIL_BLE_HadmRole_t role; /**< The device role during HADM event. */
  uint16_t hadmSqteSteps; /**< Number of steps in HADM event. */
  /** Pointer to HADM measurements. Set to NULL if unused. */
  RAIL_BLE_HadmResults_t *pHadmDataOutput;
  uint16_t t_fcs; /**< Frequency change spacing (in us). */
  uint16_t t_ip1; /**< Interlude period for mode 0 & 1 steps (in us). */
  uint16_t t_ip2; /**< Interlude period for mode 2 steps (in us). */
  uint16_t t_pm; /**< Phase measurement time (in us). */
  /**
   * Pointer to buffer where IQ data will be written. Buffer must be 32-bit
   * aligned.
   */
  uint32_t *pIqBuffer;
  /**
   * Size of IQ buffer in 32 bit words. Must be at least \ref
   * RAIL_BLE_HADM_1MBPS_MINIMUM_IQ_BUFFER_SIZE or else an error will be
   * returned by \ref RAIL_BLE_ConfigHadm.
   */
  uint16_t iqBufferSize;
  /**
   * Step Index to perform the event calibration. This index must correspond
   * to a mode 0 step or else the event calibration won't occur.
   */
  uint8_t eventCalStepIndex;
  RAIL_BLE_HadmRttType_t rttType; /**< RTT type returned during mode 1 step. */
  /**
   * A pointer to the selected HADM event gain index. This field will be
   * populated after \ref eventCalStepIndex has been reached.
   */
  uint8_t *pEventGainIndex;
  /**
   * A pointer to the selected HADM event Fractional Frequency Offset
   * (FFO) * 100. This field will be populated after \ref eventCalStepIndex
   * has been reached.
   */
  int16_t *pEventFfo;
  bool disableRttGdComp; /**< Debug flag to disable RTT GD compensation. */
  bool disablePbrDcComp; /**< Debug flag to disable PBR DC compensation. */
  bool disablePbrGdComp; /**< Debug flag to disable PBR GD compensation. */
  bool forceAgcGain;     /**< Debug flag to force event gain for calibration. */
  uint32_t forcedAgcStatus0; /**< Equivalent AGC status0 register to force. */
} RAIL_BLE_HadmConfig_t;

/** The maximum number of HADM steps allowed during a HADM event */
#define RAIL_BLE_HADM_MAX_SQTE_STEPS 512

/**
 * @enum RAIL_BLE_HadmStepState_t
 * @brief The current HADM step state.
 */
RAIL_ENUM(RAIL_BLE_HadmStepState_t) {
  /** HADM step state idle */
  RAIL_BLE_HADM_STATE_IDLE = 0,
  /** HADM step state initiator initiator transmit mode 0 */
  RAIL_BLE_HADM_STATE_I_TX_MODE0 = 1,
  /** HADM step state initiator reflector transmit mode 0 */
  RAIL_BLE_HADM_STATE_R_TX_MODE0 = 2,
  /** HADM step state initiator initiator transmit mode 1 */
  RAIL_BLE_HADM_STATE_I_TX_MODE1 = 3,
  /** HADM step state initiator reflector transmit mode 1 */
  RAIL_BLE_HADM_STATE_R_TX_MODE1 = 4,
  /** HADM step state initiator initiator transmit mode 2 */
  RAIL_BLE_HADM_STATE_R_TX_MODE2 = 6,
  /** HADM step state initiator reflector transmit mode 2 */
  RAIL_BLE_HADM_STATE_I_TX_MODE2 = 7,
};

/**
 * First step state for HADM mode 0.
 */
#define RAIL_BLE_HADM_STEP_MODE0             RAIL_BLE_HADM_STATE_I_TX_MODE0

/**
 * First step state for HADM mode 1.
 */
#define RAIL_BLE_HADM_STEP_MODE1             RAIL_BLE_HADM_STATE_I_TX_MODE1

/**
 * First step state for HADM mode 2.
 */
#define RAIL_BLE_HADM_STEP_MODE2             RAIL_BLE_HADM_STATE_I_TX_MODE2

/**
 * @enum RAIL_BLE_HadmStepMode_t
 * @brief The HADM step mode.
 */
RAIL_ENUM(RAIL_BLE_HadmStepMode_t) {
  RAIL_BLE_HADM_MODE_0,   /**< HADM step mode 0. */
  RAIL_BLE_HADM_MODE_1,   /**< HADM step mode 1. */
  RAIL_BLE_HADM_MODE_2,   /**< HADM step mode 2. */
  RAIL_BLE_HADM_MODE_3,   /**< HADM step mode 3. */
};

/**
 * @enum RAIL_BLE_HadmAntennaId_t
 * @brief The HADM antenna ID.
 */
RAIL_ENUM(RAIL_BLE_HadmAntennaId_t) {
  RAIL_BLE_HADM_ANTENNA_1 = 0, /**< HADM antenna ID 1. */
  RAIL_BLE_HADM_ANTENNA_2, /**< HADM antenna ID 2. */
  RAIL_BLE_HADM_ANTENNA_3, /**< HADM antenna ID 3. */
  RAIL_BLE_HADM_ANTENNA_4, /**< HADM antenna ID 4. */
};

/**
 * @enum RAIL_BLE_HadmRttPacketQuality_t
 * @brief HADM RTT packet quality.
 */
RAIL_ENUM(RAIL_BLE_HadmRttPacketQuality_t) {
  /** Access address check succeeded. */
  RAIL_BLE_HADM_RTT_AA_SUCCESS = 0U,
  /** Access address had one or more bit errors. */
  RAIL_BLE_HADM_RTT_AA_BIT_ERRORS = 1U,
  /** Access address not found. */
  RAIL_BLE_HADM_RTT_AA_NOT_FOUND = 2U,
};

/**
 * @struct RAIL_BLE_HadmMode0Results_t
 * @brief Contains HADM mode 0 step measurement results.
 */
typedef struct RAIL_BLE_HadmMode0Results {
  /** Mode of HADM step. */
  uint8_t mode;
  /** Antenna ID. */
  RAIL_BLE_HadmAntennaId_t antenna;
  /** RSSI during step in integer dBm. */
  int8_t rssi;
  /** Packet quality */
  uint8_t packetQuality;
  /** Reserved */
  uint16_t reserved;
  /** Fractional Frequency Offset (FFO) * 100 */
  int16_t hadmFfo;
  /** The gain setting. */
  uint32_t stepGainSetting;
  /** Reserved */
  uint32_t reserved1;
} RAIL_BLE_HadmMode0Results_t;

/**
 *  A sentinel value to indicate an invalid rtt time value in
 *  \ref RAIL_BLE_HadmMode1Results_t::rttHalfNs
 */
#define RAIL_BLE_HADM_INVALID_RTT_VALUE ((int16_t)0x8000)

/**
 * @struct RAIL_BLE_HadmMode1Results_t
 * @brief Contains HADM mode 1 step measurement results.
 */
typedef struct RAIL_BLE_HadmMode1Results {
  /** Mode of HADM step. */
  uint8_t mode;
  /** Antenna ID. */
  RAIL_BLE_HadmAntennaId_t antenna;
  /** RSSI during step in integer dBm. */
  int8_t rssi;
  /** Packet quality */
  uint8_t packetQuality;
  /**
   * For the initiator, this is the time (in 0.5 ns units) between time of
   * departure and time of arrival excluding known offsets such as interlude
   * period and packet length.
   * For the reflector, this is the time (in 0.5 ns units) between time of
   * arrival and time of departure excluding known offsets such as interlude
   * period and packet length.
   */
  int16_t rttHalfNs;
  /** Flag used to indicate whether we have missed FCAL during calibration */
  uint8_t missedFcal;
  /** Reserved */
  uint8_t reserved1;
  /** Reserved */
  uint32_t reserved2[2];
} RAIL_BLE_HadmMode1Results_t;

/**
 * @enum RAIL_BLE_HadmToneQuality_t
 * @brief HADM tone quality.
 */
RAIL_ENUM(RAIL_BLE_HadmToneQuality_t) {
  /** Good quality HADM mode 2 tone. */
  RAIL_BLE_HADM_TONE_QUALITY_GOOD = 0U,
  /** Medium quality HADM mode 2 tone. */
  RAIL_BLE_HADM_TONE_QUALITY_MEDIUM = 1U,
  /** Low quality HADM mode 2 tone. */
  RAIL_BLE_HADM_TONE_QUALITY_LOW = 2U,
  /** HADM mode 2 tone quality indication unavailable. */
  RAIL_BLE_HADM_TONE_QUALITY_UNAVAILABLE = 3U,
};

/**
 * @struct RAIL_BLE_HadmMode2Results_t
 * @brief Contains HADM mode 2 step measurement results.
 */
typedef struct RAIL_BLE_HadmMode2Results {
  /** Mode of HADM step. */
  uint8_t mode;
  /** Antenna ID. */
  RAIL_BLE_HadmAntennaId_t antenna;
  /** Flag used to indicate whether we have missed FCAL during calibration */
  uint8_t missedFcal;
  /** Reserved */
  uint8_t reserved1;
  /** PCT i value */
  int16_t pctI;
  /** PCT q value */
  int16_t pctQ;
  /** Tone extension PCT i value */
  int16_t pctToneExtI;
  /** Tone extension PCT q value */
  int16_t pctToneExtQ;
  /** Tone quality indicator */
  RAIL_BLE_HadmToneQuality_t tqi;
  /** Tone quality indicator for tone extension */
  RAIL_BLE_HadmToneQuality_t tqiToneExt;
  /** Reserved */
  uint16_t reserved2;
} RAIL_BLE_HadmMode2Results_t;

/**
 * @struct RAIL_BLE_HadmStepResults_t
 * @brief Generic HADM step mode result structure. Based on the value of the
 *   mode field, this structure can be type cast to the appropriate mode
 *   specific structure \ref RAIL_BLE_HadmMode0Results_t,
 *   \ref RAIL_BLE_HadmMode1Results_t, or RAIL_BLE_HadmMode2Results_t.
 */
typedef struct RAIL_BLE_HadmStepResults {
  /** Mode of HADM step. */
  uint8_t mode;
  /** Reserved */
  uint8_t reserved0;
  /** Reserved */
  uint16_t reserved1;
  /** Reserved */
  uint32_t reserved2[3];
} RAIL_BLE_HadmStepResults_t;

/**
 * @struct RAIL_BLE_HadmMode0DebugResults_t
 * @brief Contains HADM mode 0 step measurement debug results.
 */
typedef struct RAIL_BLE_HadmMode0DebugResults {
  /** Highest recorded RSSI up to and including the current mode 0 step. */
  int16_t highestRssi;
  /**
   * FFO of the Mode 0 step with the highest recorded RSSI
   * up to and including the current Mode 0 step.
   */
  int16_t hadmFfo;
  /**
   * AGC gain value of the Mode 0 step with the highest recorded
   * RSSI up to and including the current Mode 0 step.
   */
  uint32_t agcStatus0;
  /**
   * For devices configured as an initiator, the measured frequency offset
   * in Hz between the two devices during a HADM mode 0 step. For devices
   * configured as a reflector, this value will always be 0.
   */
  int32_t freqOffHz;
  /**
   * Estimated coarse frequency offset in internal units.
   */
  int32_t hwFreqOffEst;
  /** Reserved */
  uint32_t reserved[3];
} RAIL_BLE_HadmMode0DebugResults_t;

/**
 * @struct RAIL_BLE_HadmMode1DebugResults_t
 * @brief Contains HADM mode 1 step measurement debug results.
 */
typedef struct RAIL_BLE_HadmMode1DebugResults {
  uint16_t toxClks;
  int16_t fracRttHalfNs;
  uint32_t coarseRttHalfNs;
  int32_t gdCompRttHalfNs;
  int32_t toxWithOffsetsRttHalfNs;
  uint32_t hadmstatus3;
  uint32_t hadmstatus4;
  uint32_t hadmstatus5;
} RAIL_BLE_HadmMode1DebugResults_t;

/**
 * @struct RAIL_BLE_HadmMode2DebugResults_t
 * @brief Contains HADM mode 2 step measurement debug results.
 */
typedef struct RAIL_BLE_HadmMode2DebugResults {
  /** DCCOMP i value */
  int16_t dcCompI;
  /** DCCOMP q value */
  int16_t dcCompQ;
  /** GDCOMP i value */
  int16_t gdCompI;
  /** GDCOMP q value */
  int16_t gdCompQ;
  /** Raw tone quality value */
  uint16_t tqiRaw;
  /** Raw tone quality tone extension value */
  uint16_t tqiToneExtRaw;
  /** FCAL value from SYNTH_VCOTUNING */
  uint16_t fcal;
  /** Reserved */
  uint16_t reserved;
  /** Reserved */
  uint32_t reserved1[3];
} RAIL_BLE_HadmMode2DebugResults_t;

/**
 * @struct RAIL_BLE_HadmStepDebugResults_t
 * @brief Generic HADM step mode debug result structure. Based on the value of
 *   the mode field, this structure can be type cast to the appropriate mode
 *   specific structure \ref RAIL_BLE_HadmMode0DebugResults_t,
 *   \ref RAIL_BLE_HadmMode1DebugResults_t, or RAIL_BLE_HadmMode2DebugResults_t.
 */
typedef struct RAIL_BLE_HadmStepDebugResults {
  uint32_t reserved;
  uint32_t reserved1;
  uint32_t reserved2;
  uint32_t reserved3;
  uint32_t reserved4;
  uint32_t reserved5;
  uint32_t reserved6;
} RAIL_BLE_HadmStepDebugResults_t;

/**
 * @struct RAIL_BLE_HadmStepConfig_t
 * @brief Contains arguments for \ref RAIL_BLE_SetNextHadmStep.
 */
typedef struct RAIL_BLE_HadmStepConfig {
  /** Sets the HADM step state. */
  RAIL_BLE_HadmStepState_t stepState;
  /** Indicates whether this is final step in HADM event. */
  bool lastStep;
  /**
   * Transmit tone during tone extension slot in mode 2 packet.
   * This field is ignored during RX and for all non mode 2 packets.
   */
  bool transmitToneExtension;
  /** Sets the HADM step logical channel. */
  uint16_t channel;
  /**
   * Length of packet payload in bytes. Should not include trailer, guard,
   * or UC bits. Only used for mode 1 steps, ignored otherwise.
   */
  uint16_t packetLength;
  /** The initiator (first) access address during step. */
  uint32_t initAccessAddress;
  /** The reflector (second) access address during step. */
  uint32_t reflAccessAddress;
  /** Pointer to TX data to be transmitted. Ignored for mode 0 and 2 steps. */
  uint8_t *pTxData;
  /** RTT marker bit position. Ignored for mode 0 and 2 steps. */
  uint8_t rttMarkerBitPosition[2];
  /**
   * A pointer to an array of HADM step results. These results will be
   * populated after the completion of the HADM step. This array can be cast to
   * \ref RAIL_BLE_HadmMode0Results_t, \ref RAIL_BLE_HadmMode1Results_t, or
   * \ref RAIL_BLE_HadmMode2Results_t as appropriate to read mode specific
   * results.
   */
  RAIL_BLE_HadmStepResults_t *pResults;
  /**
   * A pointer to an array of HADM step debug results. These results will be
   * populated after the completion of the HADM step. This array can be cast to
   * \ref RAIL_BLE_HadmMode0DebugResults_t, \ref
   * RAIL_BLE_HadmMode1DebugResults_t, or \ref RAIL_BLE_HadmMode2DebugResults_t
   * as appropriate to read mode specific debug results.
   *
   * Setting this pointer to NULL means no debug data will be collected.
   */
  RAIL_BLE_HadmStepDebugResults_t *pDebugResults;
  /**
   * Pointer to contiguous global read-write memory that will be used
   * by RAIL to store channel switching information.
   * It need not be initialized and applications should never write
   * data anywhere in this buffer.
   *
   * @note the size in words of this buffer must be at least as large as
   * 3 + /ref RAIL_CHANNEL_HOPPING_BUFFER_SIZE_PER_CHANNEL. This buffer
   * is for internal use to the library.
   */
  uint32_t *pBuffer;
  /**
   * This parameter must be set to the length of the buffer array. This way,
   * during configuration, the software can confirm it's writing within the
   * range of the buffer. The configuration API will return an error
   * if bufferLength is insufficient.
   */
  uint16_t bufferLength;
  /** Reserved */
  uint16_t reserved0;
  /**
   * A pointer to the start of captured IQ data for this step. This pointer
   * will be populated after the completion of the HADM step.
   */
  uint32_t **pIqBuffer;
  /**
   * A pointer to captured IQ data size in 32 bit words. This pointer will be
   * populated after the completion of the HADM step.
   */
  uint16_t *pIqBufferSize;
  /**
   * A pointer to a boolean to indicate whether to preserve IQ data for this
   * step. If this is the final step of the event, IQ data will automatically
   * be preserved regardless of how this boolean is set. For other steps, if
   * this boolean is set true, and there are at least \ref
   * RAIL_BLE_HADM_1MBPS_MINIMUM_IQ_BUFFER_SIZE unused 32 bit words still
   * available in the event IQ buffer, this step's IQ data will be preserved
   * and not be overwritten by IQ data from a subsequent step. Otherwise, this
   * step's IQ data will not be preserved and may be overwritten. This boolean
   * will be updated after completion of the HADM step to indicate whether the
   * IQ data from that step was actually preserved.
   */
  bool *pSaveIqData;
} RAIL_BLE_HadmStepConfig_t;

/**
 * @struct RAIL_BLE_HadmAntennaConfig_t
 * @brief Contains arguments for \ref RAIL_BLE_ConfigHadmAntenna function.
 */
typedef struct RAIL_BLE_HadmAntennaConfig {
  int8_t antennaCount; /**< Total number of antenna elements. */
  const int16_t *pAntennaOffsetCm; /**< Pointer to antenna offsets in cm units. */
} RAIL_BLE_HadmAntennaConfig_t;

/** The maximum number of antennas supported. */
#define RAIL_BLE_HADM_MAX_ANTENNAS 4

/**
 * @struct RAIL_BLE_HadmGdCompTables_t
 * @brief Contains pointers to HADM group delay compensation tables.
 */
typedef struct RAIL_BLE_HadmGdCompTables {
  /** Pointer to PBR phase LSB group delay compensation table. */
  const int16_t *pPbrPhaseLsb;
  /** Pointer to RTT slope group delay compensation table. */
  const int16_t *pRttSlope;
  /** Pointer to RTT offset group delay compensation table. */
  const int16_t *pRttOffset;
  /** Common length for each table in units of int16_t. */
  uint8_t length;
} RAIL_BLE_HadmGdCompTables_t;

/**
 * Configure High Accuracy Distance Measurement (HADM) functionality.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @param[in] hadmConfig Configuration options for HADM.
 * @return RAIL_Status_t indicating success or failure of the call.
 *
 * @warning This API is not safe to use in a multiprotocol app.
 */
RAIL_Status_t RAIL_BLE_ConfigHadm(RAIL_Handle_t railHandle,
                                  const RAIL_BLE_HadmConfig_t *hadmConfig);

/**
 * Enable High Accuracy Distance Measurement (HADM) functionality.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @param[in] enable Enable or disable HADM functionality.
 * @return RAIL_Status_t indicating success or failure of the call.
 *
 * @warning This API is not safe to use in a multiprotocol app.
 */
RAIL_Status_t RAIL_BLE_EnableHadm(RAIL_Handle_t railHandle,
                                  bool enable);

/**
 * Set up the next HADM step.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @param[in,out] hadmStepConfig Configuration options for next HADM step.
 * @param[in] pend If true, apply configuration at next appropriate radio
 *   transition (i.e. at Rx2Tx for an initiator, or Tx2Rx for a reflector).
 *   Otherwise, apply configuration immediately.
 * @return RAIL_Status_t indicating success or failure of the call.
 *
 * @note When the next HADM step is to be pended, the specified step in
 *   hadmStepConfig must be the initial step state for a particular mode (e.g.
 *   \ref RAIL_BLE_HADM_STEP_MODE0, \ref RAIL_BLE_HADM_STEP_MODE1, or \ref
 *   RAIL_BLE_HADM_STEP_MODE2). Otherwise this API will return \ref
 *   RAIL_STATUS_INVALID_PARAMETER.
 *
 * @warning This API is not safe to use in a multiprotocol app.
 */
RAIL_Status_t RAIL_BLE_SetNextHadmStep(RAIL_Handle_t railHandle,
                                       const RAIL_BLE_HadmStepConfig_t *hadmStepConfig,
                                       bool pend);

/**
 * Configure antennas for HADM event.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @param[in] pAntennaConfig A pointer to the antenna config
 * @return RAIL_Status_t indicating success or failure of the call.
 */
RAIL_Status_t RAIL_BLE_ConfigHadmAntenna(RAIL_Handle_t railHandle,
                                         RAIL_BLE_HadmAntennaConfig_t *pAntennaConfig);

/**
 * Loads the HADM RTT and PBR group delay compensation tables for a
 * particular PA mode.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @param[in] pTables Pointer to group delay compensation lookup tables.
 * @param[in] powerMode The PA mode for which to load compensation tables.
 * @return Status code indicating success of the function call.
 */
RAIL_Status_t RAIL_BLE_LoadHadmCompTables(RAIL_Handle_t railHandle,
                                          const RAIL_BLE_HadmGdCompTables_t *pTables,
                                          RAIL_TxPowerMode_t powerMode);

/**
 * Callback used to load HADM group delay compensation tables for all PA modes
 * supported by device during \ref RAIL_BLE_EnableHadm when enable is true.
 * This function is optional to implement.
 *
 * @return Status code indicating success of the function call.
 *
 * @note If this callback function is not implemented, unneeded tables may not
 * be dead stripped, resulting in larger overall code size. The API \ref
 * RAIL_BLE_LoadHadmCompTables should be used within this callback to load the
 * appropriate tables for each supported PA mode.
 */
RAIL_Status_t RAILCb_BLE_HadmGdCompTableLoad(void);

/** @} */  // end of group HADM
#endif//DOXYGEN_SHOULD_SKIP_THIS

/// @addtogroup BLETX2TX BLE TX Channel Hopping
/// @{
/// @code{.c}
///
/// // Configuration to send one additional packet
/// static RAIL_BLE_TxChannelHoppingConfigEntry_t entry[1];
/// static uint32_t buffer[BUFFER_SIZE];
/// static RAIL_BLE_TxRepeatConfig_t repeat = {
///   .iterations = 1,
///   .repeatOptions = RAIL_TX_REPEAT_OPTION_HOP,
///   .delayOrHop.channelHopping = {
///     .buffer = buffer,
///     .bufferLength = BUFFER_SIZE,
///     .numberOfChannels = 1,
///     .entries = &entry[0],
///   },
/// };
///
/// // Send a normal packet on the current channel, then a packet on a new channel
/// int bleSendThenAdvertise(uint8_t *firstPacket, uint8_t *secondPacket)
/// {
///   // Load both packets into the FIFO
///   RAIL_WriteTxFifo(railHandle, firstPacket, FIRST_PACKET_LEN, true);
///   RAIL_WriteTxFifo(railHandle, secondPacket, SECOND_PACKET_LEN, false);
///
///   // Configure a 300 us turnaround between transmits
///   entry[0].delayMode = RAIL_CHANNEL_HOPPING_DELAY_MODE_STATIC;
///   entry[0].delay = 300; // microseconds
///
///   // Use default advertising parameters
///   entry[0].disableWhitening = false;
///   entry[0].crcInit = 0x00555555;
///   entry[0].accessAddress = 0x8E89BED6;
///
///   // Transmit the repeated packet on the first advertising channel
///   entry[0].phy = RAIL_BLE_1Mbps;
///   entry[0].railChannel = 0;
///   entry[0].logicalChannel = 37;
///
///  // Configure repeated transmit in RAIL, then transmit, sending both packets
///  RAIL_BLE_SetNextTxRepeat(railHandle, &repeat);
///  RAIL_StartTx(railHandle, currentChannel, RAIL_TX_OPTIONS_DEFAULT, NULL);
/// }
/// @endcode

/**
 * @struct RAIL_BLE_TxChannelHoppingConfigEntry_t
 * @brief Structure that represents one of the channels that is part of a
 *   \ref RAIL_BLE_TxChannelHoppingConfig_t sequence of channels used in
 *   channel hopping.
 */
typedef struct RAIL_BLE_TxChannelHoppingConfigEntry {
  /**
   * Idle time in microseconds to wait before hopping into the
   * channel indicated by this entry.
   */
  uint32_t delay;
  /**
   * The BLE PHY to use for this hop's transmit.
   */
  RAIL_BLE_Phy_t phy;
  /**
   * The logical channel to use for this hop's transmit. The whitener will
   * be reinitialized if used.
   */
  uint8_t logicalChannel;
  /**
   * The channel number to be used for this hop's transmit. If this is an
   * invalid channel for the chosen PHY, the call to \ref RAIL_SetNextTxRepeat()
   * will fail.
   */
  uint8_t railChannel;
  /**
   * This can turn off the whitening engine and is useful for sending BLE test
   * mode packets that don't have this turned on.
   */
  bool disableWhitening;
  /**
   * The value to use for CRC initialization.
   */
  uint32_t crcInit;
  /**
   * The access address to use for the connection.
   */
  uint32_t accessAddress;
} RAIL_BLE_TxChannelHoppingConfigEntry_t;

/**
 * @struct RAIL_BLE_TxChannelHoppingConfig_t
 * @brief Wrapper struct that will contain the sequence of
 *   \ref RAIL_BLE_TxChannelHoppingConfigEntry_t that represents the channel
 *   sequence to use during TX Channel Hopping.
 */
typedef struct RAIL_BLE_TxChannelHoppingConfig {
  /**
   * Pointer to contiguous global read-write memory that will be used
   * by RAIL to store channel hopping information throughout its operation.
   * It need not be initialized and applications should never write
   * data anywhere in this buffer.
   */
  uint32_t *buffer;
  /**
   * This parameter must be set to the length of the buffer array. This way,
   * during configuration, the software can confirm it's writing within the
   * range of the buffer. The configuration API will return an error
   * if bufferLength is insufficient.
   */
  uint16_t bufferLength;
  /** The number of channels that is in the channel hopping sequence. */
  uint8_t numberOfChannels;
  /**
   * Pad bytes reserved for future use and currently ignored.
   */
  uint8_t reserved;
  /**
   * A pointer to the first element of an array of \ref
   * RAIL_BLE_TxChannelHoppingConfigEntry_t that represents the channels
   * used during channel hopping. The length of this array must be
   * numberOfChannels.
   */
  RAIL_BLE_TxChannelHoppingConfigEntry_t *entries;
} RAIL_BLE_TxChannelHoppingConfig_t;

/// @struct RAIL_BLE_TxRepeatConfig_t
/// @brief A configuration structure for repeated transmits
///
typedef struct RAIL_BLE_TxRepeatConfig {
  /**
   * The number of repeated transmits to run. A total of (iterations + 1)
   * transmits will go on-air in the absence of errors.
   */
  uint16_t iterations;
  /**
   * Repeat option(s) to apply.
   */
  RAIL_TxRepeatOptions_t repeatOptions;
  /**
   * Per-repeat delay or hopping configuration, depending on repeatOptions.
   */
  union {
    /**
     * When \ref RAIL_TX_REPEAT_OPTION_HOP is not set, this specifies
     * the delay time between each repeated transmit. Specify \ref
     * RAIL_TRANSITION_TIME_KEEP to use the current \ref
     * RAIL_StateTiming_t::txToTx transition time setting.
     */
    RAIL_TransitionTime_t delay;
    /**
     * When \ref RAIL_TX_REPEAT_OPTION_HOP is set, this specifies
     * the channel hopping configuration to use when hopping between
     * repeated transmits. Per-hop delays are configured within each
     * \ref RAIL_BLE_TxChannelHoppingConfigEntry_t::delay rather than
     * this union's delay field.
     */
    RAIL_BLE_TxChannelHoppingConfig_t channelHopping;
  } delayOrHop;
} RAIL_BLE_TxRepeatConfig_t;

/**
 * Set up automatic repeated transmits after the next transmit.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @param[in] repeatConfig The configuration structure for repeated transmits.
 * @return Status code indicating a success of the function call.
 *
 * Repeated transmits will occur after an application-initiated transmit caused
 * by calling one of the \ref Packet_TX APIs. The repetition will only occur
 * after the first application-initiated transmit after this function is
 * called. Future repeated transmits must be requested by calling this function
 * again.
 *
 * Each repeated transmit that occurs will have full \ref PTI information and
 * will receive events such as \ref RAIL_EVENT_TX_PACKET_SENT as normal.
 *
 * If a TX error occurs during the repetition, the process will abort and the
 * TX error transition from \ref RAIL_SetTxTransitions will be used. If the
 * repetition completes successfully, the TX success transition from
 * \ref RAIL_SetTxTransitions will be used.
 *
 * Any call to \ref RAIL_Idle or \ref RAIL_StopTx will clear the pending
 * repeated transmits. The state will also be cleared by another call to this
 * function. To clear the repeated transmits before they've started without
 * stopping other radio actions, call this function with a \ref
 * RAIL_BLE_TxRepeatConfig_t::iterations count of 0. A DMP switch will clear this
 * state only if the initial transmit triggering the repeated transmits has
 * started.
 *
 * The application is responsible for populating the transmit data to be used
 * by the repeated transmits via \ref RAIL_SetTxFifo or \ref RAIL_WriteTxFifo.
 * Data will be transmitted from the TX FIFO. If the TX FIFO does not have
 * sufficient data to transmit, a TX error and a \ref
 * RAIL_EVENT_TX_UNDERFLOW will occur. To avoid an underflow, the
 * application should queue data to be transmitted as early as possible.
 *
 * This function will fail to configure the repetition if a transmit of any
 * kind is ongoing, including during the time between an initial transmit and
 * the end of a previously-configured repetition.
 *
 * @note This feature/API is not supported on the EFR32XG1 family of chips.
 *        Use the compile time symbol \ref RAIL_SUPPORTS_TX_TO_TX or the runtime
 *        call \ref RAIL_SupportsTxToTx() to check whether the platform supports
 *        this feature.
 */
RAIL_Status_t RAIL_BLE_SetNextTxRepeat(RAIL_Handle_t railHandle,
                                       const RAIL_BLE_TxRepeatConfig_t *repeatConfig);

/** @} */  // end of group BLETX2TX

/** @} */ // end of BLE

/// @addtogroup Calibration
/// @brief Bluetooth protocol-specific APIs for calibrating the radio.
/// @{

/**
 * Calibrate image rejection for Bluetooth Low Energy.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @param[out] imageRejection The result of the image rejection calibration.
 * @return A status code indicating success of the function call.
 *
 * Some chips have protocol-specific image rejection calibrations programmed
 * into their flash. This function will either get the value from flash and
 * apply it, or run the image rejection algorithm to find the value.
 */
RAIL_Status_t RAIL_BLE_CalibrateIr(RAIL_Handle_t railHandle,
                                   uint32_t *imageRejection);

/// @} // End of group Calibration

#ifdef __cplusplus
}
#endif

#endif // __RAIL_BLE_H__
