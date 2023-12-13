/*
 *  Copyright (c) 2023, The OpenThread Authors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 *   This file includes all compile-time configuration constants used by
 *   efr32 applications for OpenThread.
 */

#ifndef OPENTHREAD_CORE_EFR32_CONFIG_H_
#define OPENTHREAD_CORE_EFR32_CONFIG_H_

#include "sl_device_init_hfxo.h"
#include "sl_device_init_hfxo_config.h"

#if defined(HARDWARE_BOARD_HAS_LFXO)
#include "sl_device_init_lfxo.h"
#include "sl_device_init_lfxo_config.h"
#endif

// Use (user defined) application config file to define OpenThread configurations
#ifdef SL_OPENTHREAD_APPLICATION_CONFIG_FILE
#include SL_OPENTHREAD_APPLICATION_CONFIG_FILE
#endif

// Use (pre-defined) stack features config file available for applications built
// with Simplicity Studio
#ifdef SL_OPENTHREAD_STACK_FEATURES_CONFIG_FILE
#include SL_OPENTHREAD_STACK_FEATURES_CONFIG_FILE
#endif

#include "board_config.h"
#include "em_device.h"

/**
 * @def OPENTHREAD_CONFIG_PLATFORM_BOOTLOADER_MODE_ENABLE
 *
 * Allow triggering a platform reset to bootloader mode, if supported.
 *
 */
#if defined(SL_CATALOG_GECKO_BOOTLOADER_INTERFACE_PRESENT)
#define OPENTHREAD_CONFIG_PLATFORM_BOOTLOADER_MODE_ENABLE 1
#endif

/**
 * @def OPENTHREAD_CONFIG_PLATFORM_MAC_KEYS_EXPORTABLE_ENABLE
 *
 * Calling crypto functions in interrupt context when another operation is running
 * causes issues in Series-2 devices.  To safeguard enhanced ACK encryption, it is
 * better to use RADIOAES and not rely on SE.  For series-2 devices, this means we
 * make MAC keys exportable and copy the literal keys in radio.c (instead of using
 * key references)
 *
 */
#if defined(_SILICON_LABS_32B_SERIES_2)
#define OPENTHREAD_CONFIG_PLATFORM_MAC_KEYS_EXPORTABLE_ENABLE 1
#endif

/*
 * @def OPENTHREAD_CONFIG_RADIO_915MHZ_OQPSK_SUPPORT
 *
 * Define to 1 if you want to enable physical layer to support OQPSK modulation in 915MHz band.
 * (currently not supported).
 *
 */
#if RADIO_CONFIG_915MHZ_OQPSK_SUPPORT
#define OPENTHREAD_CONFIG_RADIO_915MHZ_OQPSK_SUPPORT 1
#else
#define OPENTHREAD_CONFIG_RADIO_915MHZ_OQPSK_SUPPORT 0
#endif

/*
 * @def OPENTHREAD_CONFIG_RADIO_2P4GHZ_OQPSK_SUPPORT
 *
 * Define to 1 if you want to enable physical layer to support OQPSK modulation in 2.4GHz band.
 *
 */
#if RADIO_CONFIG_2P4GHZ_OQPSK_SUPPORT
#define OPENTHREAD_CONFIG_RADIO_2P4GHZ_OQPSK_SUPPORT 1
#else
#define OPENTHREAD_CONFIG_RADIO_2P4GHZ_OQPSK_SUPPORT 0
#endif

/*
 * @def OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_SUPPORT
 *
 * Define to 1 if you want to enable physical layer to support proprietary radio configurations.
 *
 * This configuration option is used by the Sub-GHz feature to specify proprietary radio parameters,
 * currently not defined by the Thread spec.
 */
#if RADIO_CONFIG_SUBGHZ_SUPPORT
#define OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_SUPPORT 1
#else
#define OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_SUPPORT 0
#endif

#if RADIO_CONFIG_SUBGHZ_SUPPORT
/**
 * @def OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_PAGE
 *
 * Channel Page value for (proprietary) Sub-GHz PHY using 2GFSK modulation in 915MHz band.
 *
 */
#ifndef OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_PAGE
#define OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_PAGE 23
#endif

/**
 * @def OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MIN
 *
 * Minimum Channel number supported with (proprietary) Sub-GHz PHY using 2GFSK modulation in 915MHz band.
 *
 */
#ifndef OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MIN
#define OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MIN 0
#endif

/**
 * @def OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MAX
 *
 * Maximum Channel number supported with (proprietary) Sub-GHz PHY using 2GFSK modulation in 915MHz band.
 *
 */
#ifndef OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MAX
#define OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MAX 24
#endif

/**
 * @def OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MASK
 *
 * Default Channel Mask for (proprietary) Sub-GHz PHY using 2GFSK modulation in 915MHz band.
 *
 */
#ifndef OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MASK
#define OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MASK 0x1ffffff
#endif

/**
 * @def OPENTHREAD_CONFIG_DEFAULT_CHANNEL
 *
 * Default channel to use when working with proprietary radio configurations.
 *
 */
#ifndef OPENTHREAD_CONFIG_DEFAULT_CHANNEL
#define OPENTHREAD_CONFIG_DEFAULT_CHANNEL OPENTHREAD_CONFIG_PLATFORM_RADIO_PROPRIETARY_CHANNEL_MIN
#endif
#endif // RADIO_CONFIG_SUBGHZ_SUPPORT

/**
 * @def OPENTHREAD_CONFIG_PLATFORM_INFO
 *
 * The platform-specific string to insert into the OpenThread version string.
 *
 */
#ifndef OPENTHREAD_CONFIG_PLATFORM_INFO
#define OPENTHREAD_CONFIG_PLATFORM_INFO "EFR32"
#endif

/**
 * @def OPENTHREAD_CONFIG_UPTIME_ENABLE
 *
 * (For FTDs only) Define to 1 to enable tracking the uptime of OpenThread instance.
 *
 */
#ifndef OPENTHREAD_CONFIG_UPTIME_ENABLE
#define OPENTHREAD_CONFIG_UPTIME_ENABLE OPENTHREAD_FTD
#endif

/**
 * @def OPENTHREAD_CONFIG_CHILD_SUPERVISION_CHECK_TIMEOUT
 *
 * The default supervision check timeout interval (in seconds) used by a device in child state. Set to zero to disable
 * the supervision check process on the child.
 *
 * The check timeout interval can be changed using `otChildSupervisionSetCheckTimeout()`.
 *
 * If the sleepy child does not hear from its parent within the specified timeout interval, it initiates the re-attach
 * process (MLE Child Update Request/Response exchange with its parent).
 *
 * Setting to zero by default as this is an optional feature that can lead to unexpected detach behavior.
 *
 */
#ifndef OPENTHREAD_CONFIG_CHILD_SUPERVISION_CHECK_TIMEOUT
#define OPENTHREAD_CONFIG_CHILD_SUPERVISION_CHECK_TIMEOUT 0
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_CSL_REQUEST_AHEAD_US
 *
 * Define how many microseconds ahead should MAC deliver CSL frame to SubMac.
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_CSL_REQUEST_AHEAD_US
#define OPENTHREAD_CONFIG_MAC_CSL_REQUEST_AHEAD_US 2000
#endif

/**
 * @def OPENTHREAD_CONFIG_CSL_RECEIVE_TIME_AHEAD
 *
 * Reception scheduling and ramp up time needed for the CSL receiver to be ready, in units of microseconds.
 *
 */
#ifndef OPENTHREAD_CONFIG_CSL_RECEIVE_TIME_AHEAD
#define OPENTHREAD_CONFIG_CSL_RECEIVE_TIME_AHEAD 600
#endif

/**
 * @def OPENTHREAD_CONFIG_MIN_RECEIVE_ON_AHEAD
 *
 * The minimum time (in microseconds) before the MHR start that the radio should be in receive state and ready to
 * properly receive in order to properly receive any IEEE 802.15.4 frame. Defaults to the duration of SHR + PHR.
 *
 * 802.15.4 2.4GHz OQPSK:
 * SHR: 4 bytes of preamble, 1 byte of sync word
 * PHR: 1 byte
 * Total (6 * 32) = 192 us.
 *
 * Proprietary SubGhz (2GFSK in 915MHz):
 * SHR: 4 bytes preamble, 2 bytes SFD = 6 bytes
 * PHR: 2 bytes
 * Total (8 * 32) = 256 us.
 *
 */
#ifndef OPENTHREAD_CONFIG_MIN_RECEIVE_ON_AHEAD
#if RADIO_CONFIG_SUBGHZ_SUPPORT
  #define OPENTHREAD_CONFIG_MIN_RECEIVE_ON_AHEAD 256
#else
  #define OPENTHREAD_CONFIG_MIN_RECEIVE_ON_AHEAD 192
#endif
#endif

/**
 * @def OPENTHREAD_CONFIG_MIN_RECEIVE_ON_AFTER
 *
 * The minimum time (in microseconds) after the MHR start that the radio should be in receive state in order
 * to properly receive any IEEE 802.15.4 frame. Defaults to the duration of a maximum size frame, plus AIFS,
 * plus the duration of maximum enh-ack frame. Platforms are encouraged to improve this value for energy
 * efficiency purposes.
 *
 * In theory, RAIL should automatically extend the duration of the receive window once the SHR has been
 * detected, so we should be able to set this to zero.
 *
 */
#ifndef OPENTHREAD_CONFIG_MIN_RECEIVE_ON_AFTER
#define OPENTHREAD_CONFIG_MIN_RECEIVE_ON_AFTER 0
#endif

/*
 * @def OPENTHREAD_CONFIG_MAC_SOFTWARE_RETRANSMIT_ENABLE
 *
 * Define to 1 if you want to enable software retransmission logic.
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_SOFTWARE_RETRANSMIT_ENABLE
#define OPENTHREAD_CONFIG_MAC_SOFTWARE_RETRANSMIT_ENABLE OPENTHREAD_RADIO
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_SOFTWARE_CSMA_BACKOFF_ENABLE
 *
 * Define to 1 if you want to enable software CSMA-CA backoff logic.
 * RCPs only.
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_SOFTWARE_CSMA_BACKOFF_ENABLE
#define OPENTHREAD_CONFIG_MAC_SOFTWARE_CSMA_BACKOFF_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_SOFTWARE_TX_SECURITY_ENABLE
 *
 * Define to 1 if you want to enable software transmission security logic.
 * RCPs only.
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_SOFTWARE_TX_SECURITY_ENABLE
#define OPENTHREAD_CONFIG_MAC_SOFTWARE_TX_SECURITY_ENABLE \
    (OPENTHREAD_RADIO && (OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2))
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_SOFTWARE_TX_TIMING_ENABLE
 *
 * Define to 1 to enable software transmission target time logic.
 * RCPs only.
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_SOFTWARE_TX_TIMING_ENABLE
#define OPENTHREAD_CONFIG_MAC_SOFTWARE_TX_TIMING_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_SOFTWARE_RX_TIMING_ENABLE
 *
 * Define to 1 to enable software reception target time logic.
 * RCPs only.
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_SOFTWARE_RX_TIMING_ENABLE
#define OPENTHREAD_CONFIG_MAC_SOFTWARE_RX_TIMING_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_MAC_SOFTWARE_ENERGY_SCAN_ENABLE
 *
 * Define to 1 if you want to enable software energy scanning logic.
 * RCPs only.
 *
 */
#ifndef OPENTHREAD_CONFIG_MAC_SOFTWARE_ENERGY_SCAN_ENABLE
#define OPENTHREAD_CONFIG_MAC_SOFTWARE_ENERGY_SCAN_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_PLATFORM_USEC_TIMER_ENABLE
 *
 * Define to 1 if you want to support microsecond timer in platform.
 *
 */
#ifndef OPENTHREAD_CONFIG_PLATFORM_USEC_TIMER_ENABLE
#define OPENTHREAD_CONFIG_PLATFORM_USEC_TIMER_ENABLE (OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2)
#endif

/**
 * @def OPENTHREAD_CONFIG_PLATFORM_FLASH_API_ENABLE
 *
 * Define to 1 to enable otPlatFlash* APIs to support non-volatile storage.
 *
 * When defined to 1, the platform MUST implement the otPlatFlash* APIs instead of the otPlatSettings* APIs.
 *
 */
#ifndef OPENTHREAD_CONFIG_PLATFORM_FLASH_API_ENABLE
#define OPENTHREAD_CONFIG_PLATFORM_FLASH_API_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_TCP_ENABLE
 *
 * Define as 1 to enable TCPlp (low power TCP defined in Thread spec).
 *
 */
#ifndef OPENTHREAD_CONFIG_TCP_ENABLE
#define OPENTHREAD_CONFIG_TCP_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_NCP_HDLC_ENABLE
 *
 * Define to 1 to enable the NCP HDLC interface.
 *
 */
#ifndef OPENTHREAD_CONFIG_NCP_HDLC_ENABLE
#define OPENTHREAD_CONFIG_NCP_HDLC_ENABLE 1
#endif

/**
 * @def OPENTHREAD_CONFIG_NCP_CPC_ENABLE
 *
 * Define to 1 to enable NCP CPC support.
 *
 */
#ifndef OPENTHREAD_CONFIG_NCP_CPC_ENABLE
#define OPENTHREAD_CONFIG_NCP_CPC_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_NCP_SPI_ENABLE
 *
 * Define to 1 to enable NCP SPI support.
 *
 */
#ifndef OPENTHREAD_CONFIG_NCP_SPI_ENABLE
#define OPENTHREAD_CONFIG_NCP_SPI_ENABLE 0
#endif

/**
 * @def OPENTHREAD_CONFIG_MIN_SLEEP_DURATION_MS
 *
 * Minimum duration in ms below which the platform will not
 * enter a deep sleep (EM2) mode.
 *
 */
#ifndef OPENTHREAD_CONFIG_MIN_SLEEP_DURATION_MS
#define OPENTHREAD_CONFIG_MIN_SLEEP_DURATION_MS 5
#endif

/**
 * @def OPENTHREAD_CONFIG_EFR32_UART_TX_FLUSH_TIMEOUT_MS
 *
 * Maximum time to wait for a flush to complete in otPlatUartFlush().
 *
 * Value is in milliseconds
 *
 */
#ifndef OPENTHREAD_CONFIG_EFR32_UART_TX_FLUSH_TIMEOUT_MS
#define OPENTHREAD_CONFIG_EFR32_UART_TX_FLUSH_TIMEOUT_MS 500
#endif

/**
 * @def OPENTHREAD_CONFIG_PSA_ITS_NVM_OFFSET
 *
 * This is the offset in ITS where the persistent keys are stored.
 * For Silabs OT applications, this needs to be in the range of
 * 0x20000 to 0x2ffff.
 *
 */
#define OPENTHREAD_CONFIG_PSA_ITS_NVM_OFFSET 0x20000

/**
 * @def OPENTHREAD_CONFIG_PLATFORM_KEY_REFERENCES_ENABLE
 *
 * This config enables key references to be used in Openthread stack instead of
 * literal keys.
 *
 * Platform needs to support PSA Crypto to enable this option.
 *
 */
#ifndef OPENTHREAD_CONFIG_PLATFORM_KEY_REFERENCES_ENABLE
#if OPENTHREAD_RADIO
#define OPENTHREAD_CONFIG_PLATFORM_KEY_REFERENCES_ENABLE 0
#else
#define OPENTHREAD_CONFIG_PLATFORM_KEY_REFERENCES_ENABLE 1
#endif
#endif

/**
 * @def OPENTHREAD_CONFIG_CRYPTO_LIB
 *
 * Selects the crypto backend library for OpenThread.
 *
 * There are several options available, but we enable PSA if key references are
 * available.  Otherwise, mbedTLS is used as default (see src/core/config/crypto.h)
 *
 * - @sa OPENTHREAD_CONFIG_CRYPTO_LIB_MBEDTLS
 * - @sa OPENTHREAD_CONFIG_CRYPTO_LIB_PSA
 * - @sa OPENTHREAD_CONFIG_CRYPTO_LIB_PLATFORM
 *
 */
#if OPENTHREAD_CONFIG_PLATFORM_KEY_REFERENCES_ENABLE
#define OPENTHREAD_CONFIG_CRYPTO_LIB OPENTHREAD_CONFIG_CRYPTO_LIB_PSA
#endif

/**
 * @def SL_OPENTHREAD_CSL_TX_UNCERTAINTY
 *
 * Uncertainty of scheduling a CSL transmission, in ±10 us units.
 *
 * Note: This value was carefully configured to meet Thread certification
 * requirements for Silicon Labs devices.
 *
 */
#ifndef SL_OPENTHREAD_CSL_TX_UNCERTAINTY
#if OPENTHREAD_RADIO || OPENTHREAD_CONFIG_REFERENCE_DEVICE_ENABLE
  # define SL_OPENTHREAD_CSL_TX_UNCERTAINTY 175
#elif OPENTHREAD_FTD
  // Approx. ~128 us. for single CCA + some additional tx uncertainty in testing
  #define SL_OPENTHREAD_CSL_TX_UNCERTAINTY 20
#else
  // Approx. ~128 us. for single CCA
  //
  // Note: Our SSEDs "schedule" transmissions to their parent in order to know
  // exactly when in the future the data packets go out so they can calculate
  // the accurate CSL phase to send to their parent.
  //
  // The receive windows on the SSEDs scale with this value, so increasing this
  // uncertainty to account for full CCA/CSMA with 0..7 backoffs
  // (see RAIL_CSMA_CONFIG_802_15_4_2003_2p4_GHz_OQPSK_CSMA) will mean that the
  // receive windows can get very long (~ 5ms.)
  //
  // We have updated SSEDs to use a single CCA (RAIL_CSMA_CONFIG_SINGLE_CCA)
  // instead. If they are in very busy channels, CSL won't be reliable anyway.
  #define SL_OPENTHREAD_CSL_TX_UNCERTAINTY 12
#endif
#endif

/**
 * @def SL_OPENTHREAD_HFXO_ACCURACY
 *
 * Worst case XTAL accuracy in units of ± ppm. Also used for calculations during CSL operations.
 *
 * @note Platforms may optimize this value based on operational conditions (i.e.: temperature).
 *
 */
#ifndef SL_OPENTHREAD_HFXO_ACCURACY
  #define SL_OPENTHREAD_HFXO_ACCURACY SL_DEVICE_INIT_HFXO_PRECISION
#endif

/**
 * @def SL_OPENTHREAD_LFXO_ACCURACY
 *
 * Worst case XTAL accuracy in units of ± ppm. Also used for calculations during CSL operations.
 *
 * @note Platforms may optimize this value based on operational conditions (i.e.: temperature).
 */
#ifndef SL_OPENTHREAD_LFXO_ACCURACY
  #if defined(HARDWARE_BOARD_HAS_LFXO)
    #define SL_OPENTHREAD_LFXO_ACCURACY SL_DEVICE_INIT_LFXO_PRECISION
  #else
    #define SL_OPENTHREAD_LFXO_ACCURACY 0
  #endif
#endif

/**
 * @def SL_OPENTHREAD_RADIO_CCA_MODE
 *
 * Defines the CCA mode to be used by the platform.
 *
 */
#ifndef SL_OPENTHREAD_RADIO_CCA_MODE
#define SL_OPENTHREAD_RADIO_CCA_MODE RAIL_IEEE802154_CCA_MODE_RSSI
#endif

/**
 * @def SL_OPENTHREAD_RADIO_RX_BUFFER_COUNT
 *
 * Max number of RX buffers to use in the radio driver
 *
 */
#ifndef SL_OPENTHREAD_RADIO_RX_BUFFER_COUNT
#define SL_OPENTHREAD_RADIO_RX_BUFFER_COUNT 16
#endif

/**
 * @def SL_OPENTHREAD_ECDSA_PRIVATE_KEY_SIZE
 *
 * Max Private key size supported by ECDSA Crypto handler.
 *
 */
#ifndef SL_OPENTHREAD_ECDSA_PRIVATE_KEY_SIZE
#define SL_OPENTHREAD_ECDSA_PRIVATE_KEY_SIZE 32
#endif

#endif // OPENTHREAD_CORE_EFR32_CONFIG_H_
