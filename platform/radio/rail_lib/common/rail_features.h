/***************************************************************************//**
 * @file
 * @brief Auxiliary header for the RAIL library. Includes consistent definitions
 *   of features available across different chips.
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
#include "em_device.h"
#include "rail_types.h"

#ifndef __RAIL_FEATURES_H__
#define __RAIL_FEATURES_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup RAIL_API RAIL API
 * @{
 */

/******************************************************************************
 * RAIL Features
 *****************************************************************************/
/**
 * @addtogroup Features
 * @brief Overview of support for various features across hardware platforms.
 *        These defines can be used at compile time to determine which
 *        features are available on your platform. However, keep in mind that
 *        these defines hold true for chip families. Your specific part
 *        may have further restrictions (band limitations, power amplifier
 *        restrictions, and so on) on top of those listed below, for which
 *        runtime RAIL_Supports*() APIs can be used to check availability
 *        on a particular chip (after \ref RAIL_Init() has been called).
 *        In general, an attempt to call an API that is not supported on your
 *        chip family as listed below will result in a
 *        \ref RAIL_STATUS_INVALID_CALL.
 * @{
 */

/// Boolean to indicate whether the selected chip supports both SubGHz and 2.4 GHz bands.
/// See also runtime refinement \ref RAIL_SupportsDualBand().
#if ((_SILICON_LABS_EFR32_RADIO_TYPE == _SILICON_LABS_EFR32_RADIO_DUALBAND) \
  || ((FEAT_RF_2G4 == 1) && (FEAT_RF_SUBG == 1)))
#define RAIL_SUPPORTS_DUAL_BAND 1
#else
#define RAIL_SUPPORTS_DUAL_BAND 0
#endif
/// Backwards-compatible synonym of \ref RAIL_SUPPORTS_DUAL_BAND.
#define RAIL_FEAT_DUAL_BAND_RADIO RAIL_SUPPORTS_DUAL_BAND

/**
 * Indicate whether this chip supports dual 2.4 GHz and SubGHz band operation.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if the dual band is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_SUPPORTS_DUAL_BAND.
 */
bool RAIL_SupportsDualBand(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports the 2.4 GHz band.
/// See also runtime refinement \ref RAIL_Supports2p4GHzBand().
#if (((_SILICON_LABS_EFR32_RADIO_TYPE == _SILICON_LABS_EFR32_RADIO_DUALBAND) \
  || (_SILICON_LABS_EFR32_RADIO_TYPE == _SILICON_LABS_EFR32_RADIO_2G4HZ))    \
  || (FEAT_RF_2G4 == 1))
#define RAIL_SUPPORTS_2P4GHZ_BAND 1
#else
#define RAIL_SUPPORTS_2P4GHZ_BAND 0
#endif
/// Backwards-compatible synonym of \ref RAIL_SUPPORTS_2P4GHZ_BAND.
#define RAIL_FEAT_2G4_RADIO RAIL_SUPPORTS_2P4GHZ_BAND

/**
 * Indicate whether RAIL supports 2.4 GHz band operation on this chip.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if the 2.4 GHz band is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_SUPPORTS_2P4GHZ_BAND.
 */
bool RAIL_Supports2p4GHzBand(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports SubGHz bands.
/// See also runtime refinement \ref RAIL_SupportsSubGHzBand().
#if (((_SILICON_LABS_EFR32_RADIO_TYPE == _SILICON_LABS_EFR32_RADIO_DUALBAND) \
  || (_SILICON_LABS_EFR32_RADIO_TYPE == _SILICON_LABS_EFR32_RADIO_SUBGHZ))   \
  || (FEAT_RF_SUBG == 1))
#define RAIL_SUPPORTS_SUBGHZ_BAND 1
#else
#define RAIL_SUPPORTS_SUBGHZ_BAND 0
#endif
/// Backwards-compatible synonym of \ref RAIL_SUPPORTS_SUBGHZ_BAND.
#define RAIL_FEAT_SUBGIG_RADIO RAIL_SUPPORTS_SUBGHZ_BAND

/**
 * Indicate whether RAIL supports SubGHz band operation on this chip.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if the SubGHz band is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_SUPPORTS_SUBGHZ_BAND.
 */
bool RAIL_SupportsSubGHzBand(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports OFDM PA.
/// See also runtime refinement \ref RAIL_SupportsOFDMPA().
#if (_SILICON_LABS_32B_SERIES_2_CONFIG == 5)
#define RAIL_SUPPORTS_OFDM_PA 1
#else
#define RAIL_SUPPORTS_OFDM_PA 0
#endif

/**
 * Indicate whether RAIL supports OFDM band operation on this chip.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if OFDM operation is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_SUPPORTS_OFDM_PA.
 */
bool RAIL_SupportsOFDMPA(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports
/// bit masked address filtering.
/// See also runtime refinement \ref RAIL_SupportsAddrFilterAddressBitMask().
#if (_SILICON_LABS_32B_SERIES_2_CONFIG >= 2)
#define RAIL_SUPPORTS_ADDR_FILTER_ADDRESS_BIT_MASK 1
#else
#define RAIL_SUPPORTS_ADDR_FILTER_ADDRESS_BIT_MASK 0
#endif

/**
 * Indicate whether this chip supports bit masked address filtering
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if bit masked address filtering is supported; false otherwise.
 *
 * Runtime refinement of compile-time
 * \ref RAIL_SUPPORTS_ADDR_FILTER_ADDRESS_BIT_MASK.
 */
bool RAIL_SupportsAddrFilterAddressBitMask(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports
/// address filter mask information for incoming packets in
/// \ref RAIL_RxPacketInfo_t::filterMask and
/// \ref RAIL_IEEE802154_Address_t::filterMask.
/// See also runtime refinement \ref RAIL_SupportsAddrFilterMask().
#if (_SILICON_LABS_32B_SERIES_1_CONFIG != 1)
#define RAIL_SUPPORTS_ADDR_FILTER_MASK 1
#else
#define RAIL_SUPPORTS_ADDR_FILTER_MASK 0
#endif

/**
 * Indicate whether this chip supports address filter mask information
 * for incoming packets in
 * \ref RAIL_RxPacketInfo_t::filterMask and
 * \ref RAIL_IEEE802154_Address_t::filterMask.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if address filter information is supported; false otherwise
 *   (in which case \ref RAIL_RxPacketInfo_t::filterMask value is undefined).
 *
 * Runtime refinement of compile-time \ref RAIL_SUPPORTS_ADDR_FILTER_MASK.
 */
bool RAIL_SupportsAddrFilterMask(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports
/// alternate power settings for the Power Amplifier.
/// See also runtime refinement \ref RAIL_SupportsAlternateTxPower().
#if (_SILICON_LABS_32B_SERIES_1_CONFIG > 1) || (_SILICON_LABS_32B_SERIES_2_CONFIG == 3)
#define RAIL_SUPPORTS_ALTERNATE_TX_POWER 1
#else
#define RAIL_SUPPORTS_ALTERNATE_TX_POWER 0
#endif
/// Backwards-compatible synonym of \ref RAIL_SUPPORTS_ALTERNATE_TX_POWER.
#define RAIL_FEAT_ALTERNATE_POWER_TX_SUPPORTED RAIL_SUPPORTS_ALTERNATE_TX_POWER

/**
 * Indicate whether this chip supports alternate TX power settings.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if alternate TX power settings are supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref
 * RAIL_SUPPORTS_ALTERNATE_TX_POWER.
 */
bool RAIL_SupportsAlternateTxPower(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports antenna diversity.
/// See also runtime refinement \ref RAIL_SupportsAntennaDiversity().
#if ((_SILICON_LABS_32B_SERIES_1_CONFIG >= 2) \
  || (_SILICON_LABS_32B_SERIES == 2))
#define RAIL_SUPPORTS_ANTENNA_DIVERSITY 1
#else
#define RAIL_SUPPORTS_ANTENNA_DIVERSITY 0
#endif
/// Backwards-compatible synonym of \ref RAIL_SUPPORTS_ANTENNA_DIVERSITY.
#define RAIL_FEAT_ANTENNA_DIVERSITY RAIL_SUPPORTS_ANTENNA_DIVERSITY

/// Boolean to indicate whether the selected chip supports path diversity.
#if (_SILICON_LABS_32B_SERIES_2_CONFIG == 3)
#define RAIL_SUPPORTS_PATH_DIVERSITY 1
#else
#define RAIL_SUPPORTS_PATH_DIVERSITY 0
#endif

/**
 * Indicate whether this chip supports antenna diversity.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if antenna diversity is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_SUPPORTS_ANTENNA_DIVERSITY.
 *
 * @note Certain radio configurations may not support this feature even
 *   if the chip in general claims to support it.
 */
bool RAIL_SupportsAntennaDiversity(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports channel hopping.
/// See also runtime refinement \ref RAIL_SupportsChannelHopping().
#if ((_SILICON_LABS_32B_SERIES_1_CONFIG >= 2) || (_SILICON_LABS_32B_SERIES_2_CONFIG >= 1))
#define RAIL_SUPPORTS_CHANNEL_HOPPING 1
#else
#define RAIL_SUPPORTS_CHANNEL_HOPPING 0
#endif
/// Backwards-compatible synonym of \ref RAIL_SUPPORTS_CHANNEL_HOPPING.
#define RAIL_FEAT_CHANNEL_HOPPING RAIL_SUPPORTS_CHANNEL_HOPPING

/**
 * Indicate whether RAIL supports channel hopping on this chip.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if channel hopping is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_SUPPORTS_CHANNEL_HOPPING.
 */
bool RAIL_SupportsChannelHopping(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports dual sync words.
/// See also runtime refinement \ref RAIL_SupportsDualSyncWords().
#if 1
#define RAIL_SUPPORTS_DUAL_SYNC_WORDS 1
#else
#define RAIL_SUPPORTS_DUAL_SYNC_WORDS 0
#endif

/**
 * Indicate whether this chip supports dual sync words.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if dual sync words are supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_SUPPORTS_DUAL_SYNC_WORDS.
 *
 * @note Certain radio configurations may not support this feature even
 *   if the chip in general claims to support it.
 */
bool RAIL_SupportsDualSyncWords(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports automatic transitions
/// from TX to TX.
/// See also runtime refinement \ref RAIL_SupportsTxToTx().
#if (_SILICON_LABS_32B_SERIES_1_CONFIG != 1)
#define RAIL_SUPPORTS_TX_TO_TX 1
#else
#define RAIL_SUPPORTS_TX_TO_TX 0
#endif

/**
 * Indicate whether this chip supports automatic TX to TX transitions.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if TX to TX transitions are supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_SUPPORTS_TX_TO_TX.
 */
bool RAIL_SupportsTxToTx(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports thermistor measurements.
/// See also runtime refinement \ref RAIL_SupportsExternalThermistor().
#if ((_SILICON_LABS_32B_SERIES_2_CONFIG == 2) \
  || (_SILICON_LABS_32B_SERIES_2_CONFIG == 3) \
  || (_SILICON_LABS_32B_SERIES_2_CONFIG == 5) \
  || (_SILICON_LABS_32B_SERIES_2_CONFIG == 7))
#define RAIL_SUPPORTS_EXTERNAL_THERMISTOR 1
#else
#define RAIL_SUPPORTS_EXTERNAL_THERMISTOR 0
#endif
/// Backwards-compatible synonym of \ref RAIL_SUPPORTS_EXTERNAL_THERMISTOR.
#define RAIL_FEAT_EXTERNAL_THERMISTOR RAIL_SUPPORTS_EXTERNAL_THERMISTOR

/**
 * Indicate whether RAIL supports thermistor measurements on this chip.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if thermistor measurements are supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_SUPPORTS_EXTERNAL_THERMISTOR.
 */
bool RAIL_SupportsExternalThermistor(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports AUXADC measurements.
/// See also runtime refinement \ref RAIL_SupportsAuxAdc().
#if ((_SILICON_LABS_32B_SERIES_2_CONFIG == 2) || (_SILICON_LABS_32B_SERIES_2_CONFIG == 3) \
  || (_SILICON_LABS_32B_SERIES_2_CONFIG == 5) || (_SILICON_LABS_32B_SERIES_2_CONFIG == 7))
#define RAIL_SUPPORTS_AUXADC 1
#else
#define RAIL_SUPPORTS_AUXADC 0
#endif

/**
 * Indicate whether RAIL supports AUXADC measurements on this chip.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if AUXADC measurements are supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_SUPPORTS_AUXADC.
 */
bool RAIL_SupportsAuxAdc(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports a high-precision
/// LFRCO.
/// Best to use the runtime refinement \ref RAIL_SupportsPrecisionLFRCO()
/// because some chip revisions do not support it.
#if ((_SILICON_LABS_32B_SERIES_1_CONFIG == 3) || (_SILICON_LABS_32B_SERIES_2_CONFIG == 2) || (_SILICON_LABS_32B_SERIES_2_CONFIG == 7))
#define RAIL_SUPPORTS_PRECISION_LFRCO 1
#else
#define RAIL_SUPPORTS_PRECISION_LFRCO 0
#endif

/**
 * Indicate whether this chip supports a high-precision LFRCO.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if high-precision LFRCO is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_SUPPORTS_PRECISION_LFRCO.
 */
bool RAIL_SupportsPrecisionLFRCO(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports radio entropy.
/// See also runtime refinement \ref RAIL_SupportsRadioEntropy().
#if 1
#define RAIL_SUPPORTS_RADIO_ENTROPY 1
#else
#define RAIL_SUPPORTS_RADIO_ENTROPY 0
#endif

/**
 * Indicate whether this chip supports radio entropy.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if radio entropy is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_SUPPORTS_RADIO_ENTROPY.
 */
bool RAIL_SupportsRadioEntropy(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports
/// RFSENSE Energy Detection Mode.
/// See also runtime refinement \ref RAIL_SupportsRfSenseEnergyDetection().
#if ((_SILICON_LABS_32B_SERIES == 1) || (_SILICON_LABS_32B_SERIES_2_CONFIG == 2) || (_SILICON_LABS_32B_SERIES_2_CONFIG == 7))
#define RAIL_SUPPORTS_RFSENSE_ENERGY_DETECTION 1
#else
#define RAIL_SUPPORTS_RFSENSE_ENERGY_DETECTION 0
#endif

/**
 * Indicate whether RAIL supports RFSENSE Energy Detection Mode on this chip.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if RFSENSE Energy Detection Mode is supported; false otherwise.
 *
 * Runtime refinement of compile-time
 * \ref RAIL_SUPPORTS_RFSENSE_ENERGY_DETECTION.
 */
bool RAIL_SupportsRfSenseEnergyDetection(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports
/// RFSENSE Selective(OOK) Mode.
/// See also runtime refinement \ref RAIL_SupportsRfSenseSelectiveOok().
#if ((_SILICON_LABS_32B_SERIES_2_CONFIG == 2) || (_SILICON_LABS_32B_SERIES_2_CONFIG == 7))
#define RAIL_SUPPORTS_RFSENSE_SELECTIVE_OOK 1
#else
#define RAIL_SUPPORTS_RFSENSE_SELECTIVE_OOK 0
#endif
/// Backwards-compatible synonym of \ref RAIL_SUPPORTS_RFSENSE_SELECTIVE_OOK.
#define RAIL_FEAT_RFSENSE_SELECTIVE_OOK_MODE_SUPPORTED \
  RAIL_SUPPORTS_RFSENSE_SELECTIVE_OOK

/**
 * Indicate whether RAIL supports RFSENSE Selective(OOK) Mode on this chip.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if RFSENSE Selective(OOK) Mode is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_SUPPORTS_RFSENSE_SELECTIVE_OOK.
 */
bool RAIL_SupportsRfSenseSelectiveOok(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports the Energy Friendly
/// Front End Module (EFF).
/// See also runtime refinement \ref RAIL_SupportsEff().
#if (_SILICON_LABS_32B_SERIES_2_CONFIG == 5)
#define RAIL_SUPPORTS_EFF 1
#else
#define RAIL_SUPPORTS_EFF 0
#endif

/**
 * Indicate whether this chip supports EFF.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if EFF identifier is supported; false otherwise.
 */
bool RAIL_SupportsEff(RAIL_Handle_t railHandle);

// BLE features
// Some features may not be available on all platforms
// due to radio hardware limitations.

/// Boolean to indicate whether the selected chip supports BLE.
/// See also runtime refinement \ref RAIL_SupportsProtocolBLE().
#if 1
#define RAIL_SUPPORTS_PROTOCOL_BLE RAIL_SUPPORTS_2P4GHZ_BAND
#else
#define RAIL_SUPPORTS_PROTOCOL_BLE 0
#endif

/**
 * Indicate whether RAIL supports the BLE protocol on this chip.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if BLE is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_SUPPORTS_PROTOCOL_BLE.
 */
bool RAIL_SupportsProtocolBLE(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports BLE 1Mbps
/// Non-Viterbi PHY.
/// See also runtime refinement \ref RAIL_BLE_Supports1MbpsNonViterbi().
#if (_SILICON_LABS_32B_SERIES_1_CONFIG >= 1)
#define RAIL_BLE_SUPPORTS_1MBPS_NON_VITERBI RAIL_SUPPORTS_PROTOCOL_BLE
#else
#define RAIL_BLE_SUPPORTS_1MBPS_NON_VITERBI 0
#endif

/**
 * Indicate whether this chip supports BLE 1Mbps Non-Viterbi PHY.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if BLE 1Mbps Non-Viterbi is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_BLE_SUPPORTS_1MBPS_NON_VITERBI.
 */
bool RAIL_BLE_Supports1MbpsNonViterbi(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports BLE 1Mbps Viterbi
/// PHY.
/// See also runtime refinement \ref RAIL_BLE_Supports1MbpsViterbi().
#if (_SILICON_LABS_32B_SERIES_1_CONFIG != 1)
#define RAIL_BLE_SUPPORTS_1MBPS_VITERBI RAIL_SUPPORTS_PROTOCOL_BLE
#else
#define RAIL_BLE_SUPPORTS_1MBPS_VITERBI 0
#endif

/**
 * Indicate whether this chip supports BLE 1Mbps Viterbi PHY.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if BLE 1Mbps Viterbi is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_BLE_SUPPORTS_1MBPS_VITERBI.
 */
bool RAIL_BLE_Supports1MbpsViterbi(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports BLE 1Mbps operation.
/// See also runtime refinement \ref RAIL_BLE_Supports1Mbps().
#define RAIL_BLE_SUPPORTS_1MBPS \
  (RAIL_BLE_SUPPORTS_1MBPS_NON_VITERBI || RAIL_BLE_SUPPORTS_1MBPS_VITERBI)

/**
 * Indicate whether this chip supports BLE 1Mbps operation.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if BLE 1Mbps operation is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_BLE_SUPPORTS_1MBPS.
 */
static inline
bool RAIL_BLE_Supports1Mbps(RAIL_Handle_t railHandle)
{
  return (RAIL_BLE_Supports1MbpsNonViterbi(railHandle)
          || RAIL_BLE_Supports1MbpsViterbi(railHandle));
}

/// Boolean to indicate whether the selected chip supports BLE 2Mbps
/// Non-Viterbi PHY.
/// See also runtime refinement \ref RAIL_BLE_Supports2MbpsNonViterbi().
#if (_SILICON_LABS_32B_SERIES_1_CONFIG >= 2)
#define RAIL_BLE_SUPPORTS_2MBPS_NON_VITERBI RAIL_SUPPORTS_PROTOCOL_BLE
#else
#define RAIL_BLE_SUPPORTS_2MBPS_NON_VITERBI 0
#endif

/**
 * Indicate whether this chip supports BLE 2Mbps Non-Viterbi PHY.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if BLE 2Mbps Non-Viterbi is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_BLE_SUPPORTS_2MBPS_NON_VITERBI.
 */
bool RAIL_BLE_Supports2MbpsNonViterbi(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports BLE 2Mbps Viterbi
/// PHY.
/// See also runtime refinement \ref RAIL_BLE_Supports2MbpsViterbi().
#if (_SILICON_LABS_32B_SERIES_1_CONFIG != 1)
#define RAIL_BLE_SUPPORTS_2MBPS_VITERBI RAIL_SUPPORTS_PROTOCOL_BLE
#else
#define RAIL_BLE_SUPPORTS_2MBPS_VITERBI 0
#endif

/**
 * Indicate whether this chip supports BLE 2Mbps Viterbi PHY.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if BLE 2Mbps Viterbi is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_BLE_SUPPORTS_2MBPS_VITERBI.
 */
bool RAIL_BLE_Supports2MbpsViterbi(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports BLE 2Mbps operation.
/// See also runtime refinement \ref RAIL_BLE_Supports2Mbps().
#define RAIL_BLE_SUPPORTS_2MBPS \
  (RAIL_BLE_SUPPORTS_2MBPS_NON_VITERBI || RAIL_BLE_SUPPORTS_2MBPS_VITERBI)

/**
 * Indicate whether this chip supports BLE 2Mbps operation.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if BLE 2Mbps operation is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_BLE_SUPPORTS_2MBPS.
 */
static inline
bool RAIL_BLE_Supports2Mbps(RAIL_Handle_t railHandle)
{
  return (RAIL_BLE_Supports2MbpsNonViterbi(railHandle)
          || RAIL_BLE_Supports2MbpsViterbi(railHandle));
}

/// Boolean to indicate whether the selected chip supports BLE
/// Antenna Switching needed for Angle-of-Arrival receives or
/// Angle-of-Departure transmits.
/// See also runtime refinement \ref RAIL_BLE_SupportsAntennaSwitching().
#if ((_SILICON_LABS_32B_SERIES_2_CONFIG == 2) || (_SILICON_LABS_32B_SERIES_2_CONFIG == 4) || (_SILICON_LABS_32B_SERIES_2_CONFIG == 7))
#define RAIL_BLE_SUPPORTS_ANTENNA_SWITCHING RAIL_SUPPORTS_PROTOCOL_BLE
#else
#define RAIL_BLE_SUPPORTS_ANTENNA_SWITCHING 0
#endif

/**
 * Indicate whether this chip supports BLE Antenna Switching needed for
 * Angle-of-Arrival receives or Angle-of-Departure transmits.
 * @param[in] railHandle A RAIL instance handle.
 * @return true if BLE Antenna Switching is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_BLE_SUPPORTS_ANTENNA_SWITCHING.
 */
bool RAIL_BLE_SupportsAntennaSwitching(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports the BLE Coded PHY
/// used for Long-Range.
/// See also runtime refinement \ref RAIL_BLE_SupportsCodedPhy().
#if ((_SILICON_LABS_32B_SERIES_1_CONFIG == 3) \
  || (_SILICON_LABS_32B_SERIES_2_CONFIG == 1) \
  || (_SILICON_LABS_32B_SERIES_2_CONFIG == 2) \
  || (_SILICON_LABS_32B_SERIES_2_CONFIG == 4) \
  || (_SILICON_LABS_32B_SERIES_2_CONFIG == 7))
#define RAIL_BLE_SUPPORTS_CODED_PHY RAIL_SUPPORTS_PROTOCOL_BLE
#else
#define  RAIL_BLE_SUPPORTS_CODED_PHY 0
#endif
/// Backwards-compatible synonym of \ref RAIL_BLE_SUPPORTS_CODED_PHY.
#define RAIL_FEAT_BLE_CODED RAIL_BLE_SUPPORTS_CODED_PHY

/**
 * Indicate whether this chip supports BLE Coded PHY used for Long-Range.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if BLE Coded PHY is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_BLE_SUPPORTS_CODED_PHY.
 */
bool RAIL_BLE_SupportsCodedPhy(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports the BLE Simulscan PHY
/// used for simultaneous BLE 1Mbps and Coded PHY reception.
/// See also runtime refinement \ref RAIL_BLE_SupportsSimulscanPhy().
#if ((_SILICON_LABS_32B_SERIES_2_CONFIG == 2) \
  || (_SILICON_LABS_32B_SERIES_2_CONFIG == 4) \
  || (_SILICON_LABS_32B_SERIES_2_CONFIG == 7))
#define RAIL_BLE_SUPPORTS_SIMULSCAN_PHY RAIL_SUPPORTS_PROTOCOL_BLE
#else
#define RAIL_BLE_SUPPORTS_SIMULSCAN_PHY 0
#endif

/**
 * Indicate whether this chip supports BLE Simulscan PHY used for simultaneous
 * BLE 1Mbps and Coded PHY reception.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if BLE Simulscan PHY is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_BLE_SUPPORTS_SIMULSCAN_PHY.
 */
bool RAIL_BLE_SupportsSimulscanPhy(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports BLE
/// CTE (Constant Tone Extension) needed for Angle-of-Arrival/Departure
/// transmits.
/// See also runtime refinement \ref RAIL_BLE_SupportsCte().
#if ((_SILICON_LABS_32B_SERIES_2_CONFIG == 2) \
  || (_SILICON_LABS_32B_SERIES_2_CONFIG == 4) \
  || (_SILICON_LABS_32B_SERIES_2_CONFIG == 7))
#define RAIL_BLE_SUPPORTS_CTE RAIL_SUPPORTS_PROTOCOL_BLE
#else
#define RAIL_BLE_SUPPORTS_CTE 0
#endif

/**
 * Indicate whether this chip supports BLE CTE (Constant Tone Extension)
 * needed for Angle-of-Arrival/Departure transmits.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if BLE CTE is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_BLE_SUPPORTS_CTE.
 */
bool RAIL_BLE_SupportsCte(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports the
/// Quuppa PHY.
/// See also runtime refinement \ref RAIL_BLE_SupportsQuuppa().
#if ((_SILICON_LABS_32B_SERIES_2_CONFIG == 2) || (_SILICON_LABS_32B_SERIES_2_CONFIG == 7))
#define RAIL_BLE_SUPPORTS_QUUPPA RAIL_SUPPORTS_PROTOCOL_BLE
#else
#define RAIL_BLE_SUPPORTS_QUUPPA 0
#endif

/**
 * Indicate whether this chip supports the Quuppa PHY.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if the Quuppa is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_BLE_SUPPORTS_QUUPPA.
 */
bool RAIL_BLE_SupportsQuuppa(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports BLE
/// IQ Sampling needed for Angle-of-Arrival/Departure receives.
/// See also runtime refinement \ref RAIL_BLE_SupportsIQSampling().
#if ((_SILICON_LABS_32B_SERIES_2_CONFIG == 2) \
  || (_SILICON_LABS_32B_SERIES_2_CONFIG == 4) \
  || (_SILICON_LABS_32B_SERIES_2_CONFIG == 7))
#define RAIL_BLE_SUPPORTS_IQ_SAMPLING RAIL_SUPPORTS_PROTOCOL_BLE
#else
#define RAIL_BLE_SUPPORTS_IQ_SAMPLING 0
#endif

/**
 * Indicate whether this chip supports BLE IQ Sampling needed for
 * Angle-of-Arrival/Departure receives.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if BLE IQ Sampling is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_BLE_SUPPORTS_IQ_SAMPLING.
 */
bool RAIL_BLE_SupportsIQSampling(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports some BLE AOX
/// features.
#define RAIL_BLE_SUPPORTS_AOX          \
  (RAIL_BLE_SUPPORTS_ANTENNA_SWITCHING \
   || RAIL_BLE_SUPPORTS_IQ_SAMPLING    \
   || RAIL_BLE_SUPPORTS_CTE)

/// Backwards-compatible synonym of \ref RAIL_BLE_SUPPORTS_AOX
#define RAIL_FEAT_BLE_AOX_SUPPORTED RAIL_BLE_SUPPORTS_AOX

/// Boolean to indicate whether the selected chip supports BLE PHY switch to RX
/// functionality, which is used to switch BLE PHYs at a specific time
/// to receive auxiliary packets.
/// See also runtime refinement \ref RAIL_BLE_SupportsPhySwitchToRx().
#if (_SILICON_LABS_32B_SERIES_1_CONFIG != 1)
#define RAIL_BLE_SUPPORTS_PHY_SWITCH_TO_RX RAIL_SUPPORTS_PROTOCOL_BLE
#else
#define RAIL_BLE_SUPPORTS_PHY_SWITCH_TO_RX 0
#endif
/// Backwards-compatible synonym of \ref RAIL_BLE_SUPPORTS_PHY_SWITCH_TO_RX.
#define RAIL_FEAT_BLE_PHY_SWITCH_TO_RX RAIL_BLE_SUPPORTS_PHY_SWITCH_TO_RX

/**
 * Indicate whether this chip supports BLE PHY switch to RX
 * functionality, which is used to switch BLE PHYs at a specific time
 * to receive auxiliary packets.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if BLE PHY switch to RX is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_BLE_SUPPORTS_PHY_SWITCH_TO_RX.
 */
bool RAIL_BLE_SupportsPhySwitchToRx(RAIL_Handle_t railHandle);

// IEEE 802.15.4 features
// Some features may not be available on all platforms
// due to radio hardware limitations.

/// Boolean to indicate whether the selected chip supports IEEE 802.15.4.
/// See also runtime refinement \ref RAIL_SupportsProtocolIEEE802154().
#if 1
#define RAIL_SUPPORTS_PROTOCOL_IEEE802154 1
#else
#define RAIL_SUPPORTS_PROTOCOL_IEEE802154 0
#endif

/**
 * Indicate whether this chip supports the IEEE 802.15.4 protocol.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if the 802.15.4 protocol is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_SUPPORTS_PROTOCOL_IEEE802154.
 */
bool RAIL_SupportsProtocolIEEE802154(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports the
/// 802.15.4 Wi-Fi Coexistence PHY.
/// See also runtime refinement \ref RAIL_IEEE802154_SupportsCoexPhy().
#if (_SILICON_LABS_32B_SERIES_1_CONFIG > 1)
#define RAIL_IEEE802154_SUPPORTS_COEX_PHY (RAIL_SUPPORTS_PROTOCOL_IEEE802154 && RAIL_SUPPORTS_2P4GHZ_BAND)
#else
#define RAIL_IEEE802154_SUPPORTS_COEX_PHY 0
#endif
/// Backwards-compatible synonym of \ref RAIL_IEEE802154_SUPPORTS_COEX_PHY.
#define RAIL_FEAT_802154_COEX_PHY RAIL_IEEE802154_SUPPORTS_COEX_PHY

/**
 * Indicate whether this chip supports the IEEE 802.15.4 Wi-Fi Coexistence PHY.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if the 802.15.4 COEX PHY is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_IEEE802154_SUPPORTS_COEX_PHY.
 */
bool RAIL_IEEE802154_SupportsCoexPhy(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports a front end module.
/// See also runtime refinement \ref RAIL_IEEE802154_SupportsFemPhy().
#define RAIL_IEEE802154_SUPPORTS_FEM_PHY (RAIL_SUPPORTS_PROTOCOL_IEEE802154 && RAIL_SUPPORTS_2P4GHZ_BAND)

/**
 * Indicate whether this chip supports the IEEE 802.15.4
 * front end module optimized PHY.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if a front end module is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_IEEE802154_SUPPORTS_FEM_PHY.
 */
bool RAIL_IEEE802154_SupportsFemPhy(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports
/// IEEE 802.15.4E-2012 feature subset needed for Zigbee R22 GB868.
/// See also runtime refinement \ref
/// RAIL_IEEE802154_SupportsESubsetGB868().
#if 1
#define RAIL_IEEE802154_SUPPORTS_E_SUBSET_GB868 RAIL_SUPPORTS_PROTOCOL_IEEE802154
#else
#define RAIL_IEEE802154_SUPPORTS_E_SUBSET_GB868 0
#endif
/// Backwards-compatible synonym of \ref
/// RAIL_IEEE802154_SUPPORTS_E_SUBSET_GB868.
#define RAIL_FEAT_IEEE802154_E_GB868_SUPPORTED \
  RAIL_IEEE802154_SUPPORTS_E_SUBSET_GB868

/**
 * Indicate whether this chip supports the IEEE 802.15.4E-2012 feature
 * subset needed for Zigbee R22 GB868.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if 802.15.4E GB868 subset is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref
 * RAIL_IEEE802154_SUPPORTS_E_SUBSET_GB868.
 */
bool RAIL_IEEE802154_SupportsESubsetGB868(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports
/// IEEE 802.15.4E-2012 Enhanced ACKing.
/// See also runtime refinement \ref
/// RAIL_IEEE802154_SupportsEEnhancedAck().
#if (_SILICON_LABS_32B_SERIES_1_CONFIG != 1)
#define RAIL_IEEE802154_SUPPORTS_E_ENHANCED_ACK RAIL_IEEE802154_SUPPORTS_E_SUBSET_GB868
#else
#define RAIL_IEEE802154_SUPPORTS_E_ENHANCED_ACK 0
#endif
/// Backwards-compatible synonym of \ref
/// RAIL_IEEE802154_SUPPORTS_E_ENHANCED_ACK.
#define RAIL_FEAT_IEEE802154_E_ENH_ACK_SUPPORTED \
  RAIL_IEEE802154_SUPPORTS_E_ENHANCED_ACK

/**
 * Indicate whether this chip supports IEEE 802.15.4E-2012 Enhanced ACKing.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if 802.15.4E Enhanced ACKing is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref
 * RAIL_IEEE802154_SUPPORTS_E_ENHANCED_ACK.
 */
bool RAIL_IEEE802154_SupportsEEnhancedAck(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports
/// receiving IEEE 802.15.4E-2012 Multipurpose frames.
/// See also runtime refinement \ref
/// RAIL_IEEE802154_SupportsEMultipurposeFrames().
#if (_SILICON_LABS_32B_SERIES_1_CONFIG != 1)
#define RAIL_IEEE802154_SUPPORTS_E_MULTIPURPOSE_FRAMES RAIL_IEEE802154_SUPPORTS_E_SUBSET_GB868
#else
#define RAIL_IEEE802154_SUPPORTS_E_MULTIPURPOSE_FRAMES 0
#endif
/// Backwards-compatible synonym of \ref
/// RAIL_IEEE802154_SUPPORTS_E_MULTIPURPOSE_FRAMES.
#define RAIL_FEAT_IEEE802154_MULTIPURPOSE_FRAME_SUPPORTED \
  RAIL_IEEE802154_SUPPORTS_E_MULTIPURPOSE_FRAMES

/**
 * Indicate whether this chip supports IEEE 802.15.4E-2012 Multipurpose frame
 * reception.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if Multipurpose frame reception is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref
 * RAIL_IEEE802154_SUPPORTS_E_MULTIPURPOSE_FRAMES.
 */
bool RAIL_IEEE802154_SupportsEMultipurposeFrames(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports
/// IEEE 802.15.4G-2012 feature subset needed for Zigbee R22 GB868.
/// See also runtime refinement \ref
/// RAIL_IEEE802154_SupportsGSubsetGB868().
#if 1
#define RAIL_IEEE802154_SUPPORTS_G_SUBSET_GB868 \
  (RAIL_SUPPORTS_PROTOCOL_IEEE802154 && RAIL_SUPPORTS_SUBGHZ_BAND)
#else
#define RAIL_IEEE802154_SUPPORTS_G_SUBSET_GB868 0
#endif
/// Backwards-compatible synonym of \ref
/// RAIL_IEEE802154_SUPPORTS_G_SUBSET_GB868.
#define RAIL_FEAT_IEEE802154_G_GB868_SUPPORTED \
  RAIL_IEEE802154_SUPPORTS_G_SUBSET_GB868

/**
 * Indicate whether this chip supports IEEE 802.15.4G-2012 feature
 * subset needed for Zigbee R22 GB868.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if 802.15.4G GB868 subset is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref
 * RAIL_IEEE802154_SUPPORTS_G_SUBSET_GB868.
 */
bool RAIL_IEEE802154_SupportsGSubsetGB868(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports
/// dynamic FEC
#if (_SILICON_LABS_32B_SERIES_2_CONFIG > 1)
#define RAIL_IEEE802154_SUPPORTS_G_DYNFEC \
  RAIL_FEAT_IEEE802154_G_GB868_SUPPORTED  // limit to SUBGHZ for now
#else
#define RAIL_IEEE802154_SUPPORTS_G_DYNFEC 0
#endif

/**
 * Indicate whether this chip supports IEEE 802.15.4G dynamic FEC
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if dynamic FEC is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref
 * RAIL_IEEE802154_SUPPORTS_G_DYNFEC.
 */
bool RAIL_IEEE802154_SupportsGDynFec(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports
/// Wi-SUN mode switching
/// See also runtime refinement \ref
/// RAIL_IEEE802154_SupportsGModeSwitch().
#if (_SILICON_LABS_32B_SERIES_2_CONFIG == 5)
#define RAIL_IEEE802154_SUPPORTS_G_MODESWITCH \
  RAIL_IEEE802154_SUPPORTS_G_SUBSET_GB868  // limit to SUBGHZ for now
#else
#define RAIL_IEEE802154_SUPPORTS_G_MODESWITCH 0
#endif

/**
 * Indicate whether this chip supports Wi-SUN mode switching
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if Wi-SUN mode switching is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref
 * RAIL_IEEE802154_SUPPORTS_G_MODESWITCH.
 */
bool RAIL_IEEE802154_SupportsGModeSwitch(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports
/// IEEE 802.15.4G-2012 reception and transmission of frames
/// with 4-byte CRC.
/// See also runtime refinement \ref RAIL_IEEE802154_SupportsG4ByteCrc().
#if (_SILICON_LABS_32B_SERIES_1_CONFIG != 1)
#define RAIL_IEEE802154_SUPPORTS_G_4BYTE_CRC RAIL_IEEE802154_SUPPORTS_G_SUBSET_GB868
#else
#define RAIL_IEEE802154_SUPPORTS_G_4BYTE_CRC 0
#endif
/// Backwards-compatible synonym of \ref RAIL_IEEE802154_SUPPORTS_G_4BYTE_CRC.
#define RAIL_FEAT_IEEE802154_G_4BYTE_CRC_SUPPORTED \
  RAIL_IEEE802154_SUPPORTS_G_4BYTE_CRC

/**
 * Indicate whether this chip supports IEEE 802.15.4G-2012 reception and
 * transmission of frames with 4-byte CRC.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if 802.15.4G 4-byte CRC is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref
 * RAIL_IEEE802154_SUPPORTS_G_4BYTE_CRC.
 */
bool RAIL_IEEE802154_SupportsG4ByteCrc(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports
/// IEEE 802.15.4G-2012 reception of unwhitened frames.
/// See also runtime refinement \ref
/// RAIL_IEEE802154_SupportsGUnwhitenedRx().
#if (_SILICON_LABS_32B_SERIES_1_CONFIG != 1)
#define RAIL_IEEE802154_SUPPORTS_G_UNWHITENED_RX RAIL_IEEE802154_SUPPORTS_G_SUBSET_GB868
#else
#define RAIL_IEEE802154_SUPPORTS_G_UNWHITENED_RX 0
#endif
/// Backwards-compatible synonym of \ref
/// RAIL_IEEE802154_SUPPORTS_G_UNWHITENED_RX.
#define RAIL_FEAT_IEEE802154_G_UNWHITENED_RX_SUPPORTED \
  RAIL_IEEE802154_SUPPORTS_G_UNWHITENED_RX

/**
 * Indicate whether this chip supports IEEE 802.15.4G-2012 reception
 * of unwhitened frames.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if 802.15.4G unwhitened frame reception is supported;
 *   false otherwise.
 *
 * Runtime refinement of compile-time \ref
 * RAIL_IEEE802154_SUPPORTS_G_UNWHITENED_RX.
 */
bool RAIL_IEEE802154_SupportsGUnwhitenedRx(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports
/// IEEE 802.15.4G-2012 transmission of unwhitened frames.
/// See also runtime refinement \ref
/// RAIL_IEEE802154_SupportsGUnwhitenedTx().
#if (_SILICON_LABS_32B_SERIES_1_CONFIG != 1)
#define RAIL_IEEE802154_SUPPORTS_G_UNWHITENED_TX RAIL_IEEE802154_SUPPORTS_G_SUBSET_GB868
#else
#define RAIL_IEEE802154_SUPPORTS_G_UNWHITENED_TX 0
#endif
/// Backwards-compatible synonym of \ref
/// RAIL_IEEE802154_SUPPORTS_G_UNWHITENED_TX.
#define RAIL_FEAT_IEEE802154_G_UNWHITENED_TX_SUPPORTED \
  RAIL_IEEE802154_SUPPORTS_G_UNWHITENED_TX

/**
 * Indicate whether this chip supports IEEE 802.15.4G-2012 transmission
 * of unwhitened frames.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if 802.15.4G unwhitened frame transmit is supported;
 *   false otherwise.
 *
 * Runtime refinement of compile-time \ref
 * RAIL_IEEE802154_SUPPORTS_G_UNWHITENED_TX.
 */
bool RAIL_IEEE802154_SupportsGUnwhitenedTx(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports
/// canceling the frame-pending lookup event
/// \ref RAIL_EVENT_IEEE802154_DATA_REQUEST_COMMAND
/// when the radio transitions to a state that renders the
/// the reporting of this event moot (i.e., too late for
/// the stack to influence the outgoing ACK).
/// See also runtime refinement \ref
/// RAIL_IEEE802154_SupportsCancelFramePendingLookup().
#if (_SILICON_LABS_32B_SERIES_1_CONFIG != 1)
#define RAIL_IEEE802154_SUPPORTS_CANCEL_FRAME_PENDING_LOOKUP RAIL_SUPPORTS_PROTOCOL_IEEE802154
#else
#define RAIL_IEEE802154_SUPPORTS_CANCEL_FRAME_PENDING_LOOKUP 0
#endif
/// Backwards-compatible synonym of \ref
/// RAIL_IEEE802154_SUPPORTS_CANCEL_FRAME_PENDING_LOOKUP.
#define RAIL_FEAT_IEEE802154_CANCEL_FP_LOOKUP_SUPPORTED \
  RAIL_IEEE802154_SUPPORTS_CANCEL_FRAME_PENDING_LOOKUP

/**
 * Indicate whether this chip supports canceling the frame-pending lookup
 * event \ref RAIL_EVENT_IEEE802154_DATA_REQUEST_COMMAND when the radio
 * transitions to a state that renders the the reporting of this event moot
 * (i.e., too late for the stack to influence the outgoing ACK).
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if canceling the lookup event is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref
 * RAIL_IEEE802154_SUPPORTS_CANCEL_FRAME_PENDING_LOOKUP.
 */
bool RAIL_IEEE802154_SupportsCancelFramePendingLookup(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports
/// early triggering of the frame-pending lookup event
/// \ref RAIL_EVENT_IEEE802154_DATA_REQUEST_COMMAND
/// just after MAC address fields have been received.
/// See also runtime refinement \ref
/// RAIL_IEEE802154_SupportsEarlyFramePendingLookup().
#if 1
#define RAIL_IEEE802154_SUPPORTS_EARLY_FRAME_PENDING_LOOKUP RAIL_SUPPORTS_PROTOCOL_IEEE802154
#else
#define RAIL_IEEE802154_SUPPORTS_EARLY_FRAME_PENDING_LOOKUP 0
#endif
/// Backwards-compatible synonym of \ref
/// RAIL_IEEE802154_SUPPORTS_EARLY_FRAME_PENDING_LOOKUP.
#define RAIL_FEAT_IEEE802154_EARLY_FP_LOOKUP_SUPPORTED \
  RAIL_IEEE802154_SUPPORTS_EARLY_FRAME_PENDING_LOOKUP

/**
 * Indicate whether this chip supports early triggering of the frame-pending
 * lookup event \ref RAIL_EVENT_IEEE802154_DATA_REQUEST_COMMAND
 * just after MAC address fields have been received.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if early triggering is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref
 * RAIL_IEEE802154_SUPPORTS_EARLY_FRAME_PENDING_LOOKUP.
 */
bool RAIL_IEEE802154_SupportsEarlyFramePendingLookup(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports dual PA configs for mode switch
/// or concurrent mode.
/// See also runtime refinement \ref RAIL_IEEE802154_SupportsDualPaConfig().
#if (_SILICON_LABS_32B_SERIES_2_CONFIG == 5)
#define RAIL_IEEE802154_SUPPORTS_DUAL_PA_CONFIG 1
#else
#define RAIL_IEEE802154_SUPPORTS_DUAL_PA_CONFIG 0
#endif

/**
 * Indicate whether RAIL supports dual PA mode on this chip.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if the dual PA mode is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_IEEE802154_SUPPORTS_DUAL_PA_CONFIG.
 */
bool RAIL_IEEE802154_SupportsDualPaConfig(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports IEEE 802.15.4 PHY
/// with custom settings
#if ((_SILICON_LABS_32B_SERIES_1_CONFIG == 2) || (_SILICON_LABS_32B_SERIES_1_CONFIG == 3))
#define RAIL_IEEE802154_SUPPORTS_CUSTOM1_PHY (RAIL_SUPPORTS_PROTOCOL_IEEE802154 && RAIL_SUPPORTS_2P4GHZ_BAND)
#else
#define RAIL_IEEE802154_SUPPORTS_CUSTOM1_PHY 0
#endif

/**
 * Indicate whether this chip supports the IEEE 802.15.4 PHY with custom settings.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if the 802.15.4 PHY with custom settings is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_IEEE802154_SUPPORTS_CUSTOM1_PHY.
 */
bool RAIL_IEEE802154_SupportsCustom1Phy(RAIL_Handle_t railHandle);

// Z-Wave features
// Some features may not be available on all platforms
// due to radio hardware limitations.

/// Boolean to indicate whether the selected chip supports Z-Wave.
/// See also runtime refinement \ref RAIL_SupportsProtocolZWave().
#if (_SILICON_LABS_32B_SERIES_1_CONFIG >= 3) || (_SILICON_LABS_32B_SERIES_2_CONFIG == 3)
#define RAIL_SUPPORTS_PROTOCOL_ZWAVE RAIL_SUPPORTS_SUBGHZ_BAND
#else
#define RAIL_SUPPORTS_PROTOCOL_ZWAVE 0
#endif
/// Backwards-compatible synonym of \ref RAIL_SUPPORTS_PROTOCOL_ZWAVE.
#define RAIL_FEAT_ZWAVE_SUPPORTED RAIL_SUPPORTS_PROTOCOL_ZWAVE

/**
 * Indicate whether this chip supports the Z-Wave protocol.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if the Z-Wave protocol is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_SUPPORTS_PROTOCOL_ZWAVE.
 */
bool RAIL_SupportsProtocolZWave(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports energy detect PHY.
/// See also runtime refinement \ref RAIL_ZWAVE_SupportsEnergyDetectPhy().
#if (_SILICON_LABS_32B_SERIES_1_CONFIG >= 3)
#define RAIL_ZWAVE_SUPPORTS_ED_PHY RAIL_SUPPORTS_PROTOCOL_ZWAVE
#else
#define RAIL_ZWAVE_SUPPORTS_ED_PHY 0
#endif

/**
 * Indicate whether this chip supports the Z-Wave energy detect PHY.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if the Z-Wave energy detect PHY is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_ZWAVE_SUPPORTS_ED_PHY.
 */
bool RAIL_ZWAVE_SupportsEnergyDetectPhy(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports concurrent PHY.
/// See also runtime refinement \ref RAIL_ZWAVE_SupportsConcPhy().
#if (_SILICON_LABS_32B_SERIES_2_CONFIG == 3)
#define RAIL_ZWAVE_SUPPORTS_CONC_PHY RAIL_SUPPORTS_PROTOCOL_ZWAVE
#else
#define RAIL_ZWAVE_SUPPORTS_CONC_PHY 0
#endif

/**
 * Indicate whether this chip supports the Z-Wave concurrent PHY.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if the Z-Wave concurrent PHY is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_ZWAVE_SUPPORTS_CONC_PHY.
 */
bool RAIL_ZWAVE_SupportsConcPhy(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports SQ-based PHY.
/// See also runtime refinement \ref RAIL_SupportsSQPhy().
#if (_SILICON_LABS_32B_SERIES_2_CONFIG == 3)  \
  || (_SILICON_LABS_32B_SERIES_2_CONFIG == 4) \
  || (_SILICON_LABS_32B_SERIES_2_CONFIG == 5)
#define RAIL_SUPPORTS_SQ_PHY 1
#else
#define RAIL_SUPPORTS_SQ_PHY 0
#endif

/**
 * Indicate whether this chip supports SQ-based PHY.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if the SQ-based PHY is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_SUPPORTS_SQ_PHY.
 */
bool RAIL_SupportsSQPhy(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the code supports Z-Wave
/// region information in PTI and
/// newer RAIL_ZWAVE_RegionConfig_t structure
/// See also runtime refinement \ref RAIL_ZWAVE_SupportsRegionPti().
#if 1
#define RAIL_ZWAVE_SUPPORTS_REGION_PTI RAIL_SUPPORTS_PROTOCOL_ZWAVE
#else
#define RAIL_ZWAVE_SUPPORTS_REGION_PTI 0
#endif
/// Backwards-compatible synonym of \ref RAIL_ZWAVE_SUPPORTS_REGION_PTI.
#define RAIL_FEAT_ZWAVE_REGION_PTI RAIL_ZWAVE_SUPPORTS_REGION_PTI

/**
 * Indicate whether this chip supports Z-Wave Region in PTI.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if ZWAVE Region in PTI is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_ZWAVE_SUPPORTS_REGION_PTI.
 */
bool RAIL_ZWAVE_SupportsRegionPti(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports
/// direct mode.
/// See also runtime refinement \ref RAIL_SupportsDirectMode().
#if ((_SILICON_LABS_32B_SERIES == 1) || (_SILICON_LABS_32B_SERIES_2_CONFIG == 3))
#define RAIL_SUPPORTS_DIRECT_MODE 1
#else
#define RAIL_SUPPORTS_DIRECT_MODE 0
#endif

/**
 * Indicate whether this chip supports direct mode.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if direct mode is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref
 * RAIL_SUPPORTS_DIRECT_MODE.
 */
bool RAIL_SupportsDirectMode(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports
/// RX direct mode data to FIFO.
/// See also runtime refinement \ref RAIL_SupportsRxDirectModeDataToFifo().
#if (_SILICON_LABS_32B_SERIES_2_CONFIG == 3)
#define RAIL_SUPPORTS_RX_DIRECT_MODE_DATA_TO_FIFO 1
#else
#define RAIL_SUPPORTS_RX_DIRECT_MODE_DATA_TO_FIFO 0
#endif

/**
 * Indicate whether this chip supports RX direct mode data to FIFO.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if direct mode data to FIFO is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref
 * RAIL_SUPPORTS_RX_DIRECT_MODE_DATA_TO_FIFO.
 */
bool RAIL_SupportsRxDirectModeDataToFifo(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports
/// MFM protocol.
/// See also runtime refinement \ref RAIL_SupportsMfm().
#if (_SILICON_LABS_32B_SERIES_2_CONFIG == 3)
#define RAIL_SUPPORTS_MFM 1
#else
#define RAIL_SUPPORTS_MFM 0
#endif

/**
 * Indicate whether this chip supports MFM protocol.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if MFM protocol is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_SUPPORTS_MFM.
 */
bool RAIL_SupportsMfm(RAIL_Handle_t railHandle);

#if (_SILICON_LABS_32B_SERIES_2_CONFIG == 4)
/// Boolean to indicate whether the selected chip supports
/// 802.15.4 signal detection
  #define RAIL_IEEE802154_SUPPORTS_SIGNAL_IDENTIFIER  (RAIL_SUPPORTS_PROTOCOL_IEEE802154)
/// Boolean to indicate whether the selected chip supports
/// BLE signal detection
  #define RAIL_BLE_SUPPORTS_SIGNAL_IDENTIFIER         (RAIL_SUPPORTS_PROTOCOL_BLE)
#else
/// Boolean to indicate whether the selected chip supports
/// 802.15.4 signal detection
  #define RAIL_IEEE802154_SUPPORTS_SIGNAL_IDENTIFIER  0
/// Boolean to indicate whether the selected chip supports
/// BLE signal detection
  #define RAIL_BLE_SUPPORTS_SIGNAL_IDENTIFIER         0
#endif

/**
 * Indicate whether this chip supports IEEE 802.15.4 signal identifier.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if signal identifier is supported; false otherwise.
 */
bool RAIL_IEEE802154_SupportsSignalIdentifier(RAIL_Handle_t railHandle);

/**
 * Indicate whether this chip supports BLE signal identifier.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if signal identifier is supported; false otherwise.
 */
bool RAIL_BLE_SupportsSignalIdentifier(RAIL_Handle_t railHandle);

/// Boolean to indicate whether the selected chip supports
/// configurable RSSI threshold set by \ref RAIL_SetRssiDetectThreshold().
#if (_SILICON_LABS_32B_SERIES_2_CONFIG == 3) \
  || (_SILICON_LABS_32B_SERIES_2_CONFIG == 5)
#define RAIL_SUPPORTS_RSSI_DETECT_THRESHOLD (1U)
#else
#define RAIL_SUPPORTS_RSSI_DETECT_THRESHOLD (0U)
#endif

/**
 * Indicate whether this chip supports configurable RSSI threshold
 * set by \ref RAIL_SetRssiDetectThreshold().
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return true if setting configurable RSSI is supported; false otherwise.
 *
 * Runtime refinement of compile-time \ref RAIL_SUPPORTS_RSSI_DETECT_THRESHOLD.
 */
bool RAIL_SupportsRssiDetectThreshold(RAIL_Handle_t railHandle);

/** @} */ // end of group Features

/** @} */ // end of group RAIL_API

#ifdef __cplusplus
}
#endif

#endif // __RAIL_FEATURES_H__
