/***************************************************************************//**
 * @file
 * @brief Definition of error codes that occur in rail for use in
 *   RAILCb_AssertFailed. This file is purely informational and optional -
 *   it need not be included even if rail_assert libraries are included.
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

#ifndef __RAIL_ASSERT_ERROR_CODES_H__
#define __RAIL_ASSERT_ERROR_CODES_H__

#include "rail_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup Assertions
 * @{
 */

/**
 * Enumeration of all possible error codes from RAIL_ASSERT
 */
RAIL_ENUM_GENERIC(RAIL_AssertErrorCodes_t, uint32_t)
{
  /** Appended info missing from RX packet. */
  RAIL_ASSERT_FAILED_APPENDED_INFO_MISSING = 0,
  /** Receive FIFO too small for IR calibration. */
  RAIL_ASSERT_FAILED_RX_FIFO_BYTES = 1,
  /** Invalid assert, no longer used. */
  RAIL_ASSERT_UNUSED_2 = 2,
  /** Receive FIFO entry has invalid status. */
  RAIL_ASSERT_FAILED_ILLEGAL_RXLEN_ENTRY_STATUS = 3,
  /** Receive FIFO entry bad packet length. */
  RAIL_ASSERT_FAILED_BAD_PACKET_LENGTH = 4,
  /** Unable to configure radio for IR calibration. */
  RAIL_ASSERT_FAILED_SYNTH_DIVCTRL_ENUM_CONVERSION_ERROR = 5,
  /** Reached unexpected state while handling RX FIFO events. */
  RAIL_ASSERT_FAILED_UNEXPECTED_STATE_RX_FIFO = 6,
  /** Reached unexpected state while handling RXLEN FIFO events. */
  RAIL_ASSERT_FAILED_UNEXPECTED_STATE_RXLEN_FIFO = 7,
  /** Reached unexpected state while handling TX FIFO events. */
  RAIL_ASSERT_FAILED_UNEXPECTED_STATE_TX_FIFO = 8,
  /** Reached unexpected state while handling TX ACK FIFO events. */
  RAIL_ASSERT_FAILED_UNEXPECTED_STATE_TXACK_FIFO = 9,
  /** Invalid assert, no longer used. */
  RAIL_ASSERT_UNUSED_10 = 10,
  /** Invalid assert, no longer used. */
  RAIL_ASSERT_UNUSED_11 = 11,
  /** Invalid assert, no longer used. */
  RAIL_ASSERT_UNUSED_12 = 12,
  /** Error synchronizing the RAIL timebase after sleep. */
  RAIL_ASSERT_FAILED_RTCC_POST_WAKEUP = 13,
  /** VCO frequency outside supported range. */
  RAIL_ASSERT_FAILED_SYNTH_VCO_FREQUENCY = 14,
  /** Radio active while changing channels. */
  RAIL_ASSERT_FAILED_RAC_STATE = 15,
  /** Invalid Synth VCOCTRL field calculation. */
  RAIL_ASSERT_FAILED_SYNTH_INVALID_VCOCTRL = 16,
  /** Nested attempt to lock the sequencer. */
  RAIL_ASSERT_FAILED_NESTED_SEQUENCER_LOCK = 17,
  /** RSSI averaging enabled without a valid callback. */
  RAIL_ASSERT_FAILED_RSSI_AVERAGE_DONE = 18,
  /** Invalid assert, no longer used. */
  RAIL_ASSERT_UNUSED_19 = 19,
  /** Unable to seed radio pseudo random number generator. */
  RAIL_ASSERT_FAILED_PROTIMER_RANDOM_SEED = 20,
  /** Timeout exceeds EFR32XG1 register size. */
  RAIL_ASSERT_FAILED_EFR32XG1_REGISTER_SIZE = 21,
  /** Invalid timer channel specified. */
  RAIL_ASSERT_FAILED_PROTIMER_CHANNEL = 22,
  /** Invalid assert, no longer used. */
  RAIL_ASSERT_UNUSED_23 = 23,
  /** LBT config exceeds EFR32XG1 register size. */
  RAIL_ASSERT_FAILED_BASECNTTOP = 24,
  /** Invalid assert, no longer used. */
  RAIL_ASSERT_UNUSED_25 = 25,
  /** Could not synchronize RAIL timebase with the RTC. */
  RAIL_ASSERT_FAILED_RTCC_SYNC_MISSED = 26,
  /** Clock source not ready. */
  RAIL_ASSERT_FAILED_CLOCK_SOURCE_NOT_READY = 27,
  /** Invalid assert, no longer used. */
  RAIL_ASSERT_UNUSED_28 = 28,
  /** NULL was supplied as a RAIL_Handle_t argument. */
  RAIL_ASSERT_NULL_HANDLE = 29,
  /** Invalid assert, no longer used. */
  RAIL_ASSERT_UNUSED_30 = 30,
  /** API improperly called while protocol inactive. */
  RAIL_ASSERT_FAILED_NO_ACTIVE_CONFIG = 31,
  /** Invalid assert, no longer used. */
  RAIL_ASSERT_UNUSED_32 = 32,
  /** Invalid assert, no longer used. */
  RAIL_ASSERT_UNUSED_33 = 33,
  /** Invalid assert, no longer used. */
  RAIL_ASSERT_UNUSED_34 = 34,
  /** Invalid assert, no longer used. */
  RAIL_ASSERT_UNUSED_35 = 35,
  /** Invalid assert, no longer used. */
  RAIL_ASSERT_UNUSED_36 = 36,
  /** Invalid assert, no longer used. */
  RAIL_ASSERT_UNUSED_37 = 37,
  /** Invalid assert, no longer used. */
  RAIL_ASSERT_UNUSED_38 = 38,
  /** This function is deprecated and must not be called. */
  RAIL_ASSERT_DEPRECATED_FUNCTION = 39,
  /** Multiprotocol task started with no event to run. */
  RAIL_ASSERT_MULTIPROTOCOL_NO_EVENT = 40,
  /** Invalid interrupt enabled. */
  RAIL_ASSERT_FAILED_INVALID_INTERRUPT_ENABLED = 41,
  /** Invalid assert, no longer used. */
  RAIL_ASSERT_UNUSED_42 = 42,
  /** Division by zero. */
  RAIL_ASSERT_DIVISION_BY_ZERO = 43,
  /** Function cannot be called without access to the hardware. */
  RAIL_ASSERT_CANT_USE_HARDWARE = 44,
  /** Pointer parameter was passed as NULL. */
  RAIL_ASSERT_NULL_PARAMETER = 45,
  /** Invalid assert, no longer used. */
  RAIL_ASSERT_UNUSED_46 = 46,
  /** Synth radio config buffer for channel hopping too small. */
  RAIL_ASSERT_SMALL_SYNTH_RADIO_CONFIG_BUFFER = 47,
  /** Buffer provided for RX Channel Hopping is too small. */
  RAIL_ASSERT_CHANNEL_HOPPING_BUFFER_TOO_SHORT = 48,
  /** Invalid action was attempted on a module. */
  RAIL_ASSERT_INVALID_MODULE_ACTION = 49,
  /** The radio config for this channel is not compatible with channel hopping. */
  RAIL_ASSERT_CHANNEL_HOPPING_INVALID_RADIO_CONFIG = 50,
  /** Channel change failed. */
  RAIL_ASSERT_CHANNEL_CHANGE_FAILED = 51,
  /** Attempted to read invalid register. */
  RAIL_ASSERT_INVALID_REGISTER = 52,
  /** Invalid assert, no longer used. */
  RAIL_ASSERT_UNUSED_53 = 53,
  /** DMP radio config caching failed. */
  RAIL_ASSERT_CACHE_CONFIG_FAILED = 54,
  /** NULL was supplied as a RAIL_StateTransitions_t argument. */
  RAIL_ASSERT_NULL_TRANSITIONS = 55,
  /** LDMA transfer failed. */
  RAIL_ASSERT_BAD_LDMA_TRANSFER = 56,
  /** Attempted to wake up with invalid RTCC sync data. */
  RAIL_ASSERT_INVALID_RTCC_SYNC_VALUES = 57,
  /** Radio sequencer hit a fault condition. */
  RAIL_ASSERT_SEQUENCER_FAULT = 58,
  /** Bus fault. */
  RAIL_ASSERT_BUS_ERROR = 59,
  /** The current radio config cannot be used with packet filtering. */
  RAIL_ASSERT_INVALID_FILTERING_CONFIG = 60,
  /** Retiming configuration error. */
  RAIL_ASSERT_RETIMING_CONFIG = 61,
  /** TX CRC configuration is corrupt. */
  RAIL_ASSERT_FAILED_TX_CRC_CONFIG = 62,
  /** The current PA config does not allow for this operation. */
  RAIL_ASSERT_INVALID_PA_OPERATION = 63,
  /** The sequencer selected an invalid PA. */
  RAIL_ASSERT_SEQ_INVALID_PA_SELECTED = 64,
  /** Invalid/unsupported channel config. */
  RAIL_ASSERT_FAILED_INVALID_CHANNEL_CONFIG = 65,
  /** Radio Calculator configuration HFXO frequency mismatch with chip */
  RAIL_ASSERT_INVALID_XTAL_FREQUENCY = 66,
  /** Invalid assert, no longer used. */
  RAIL_ASSERT_UNUSED_67 = 67,
  /** Software modem image does not support requested modulation  */
  RAIL_ASSERT_UNSUPPORTED_SOFTWARE_MODEM_MODULATION = 68,
  /** Failed to disable RTCC synchronization. */
  RAIL_ASSERT_FAILED_RTCC_SYNC_STOP = 69,
  /** Multitimer linked list corrupted. */
  RAIL_ASSERT_FAILED_MULTITIMER_CORRUPT = 70,
  /** Unable to configure radio for temperature calibration. */
  RAIL_ASSERT_FAILED_TEMPCAL_ERROR = 71,
  /** Invalid EFF configuration. */
  RAIL_ASSERT_INVALID_EFF_CONFIGURATION = 72,
  /** Invalid RFFPLL configuration. */
  RAIL_ASSERT_INVALID_RFFPLL_CONFIGURATION = 73,
  /** Secure access fault. */
  RAIL_ASSERT_SECURE_ACCESS_FAULT = 74,
  /** SYSRTC0 not running. */
  RAIL_ASSERT_FAILED_SYSRTC0_NOT_RUNNING = 75,
  /** Radio Configurator not updated. */
  RAIL_ASSERT_RADIO_CONFIG_NOT_UP_TO_DATE = 76,
  /** Failed to set the event for configurable RSSI threshold. */
  RAIL_ASSERT_FAILED_RSSI_THRESHOLD = 77,
  /** Intended and actual Z-Wave region configuration mismatch. */
  RAIL_ASSERT_INCORRECT_ZWAVE_REGION = 78,
  /** Attempted to sleep with stale RTCC synchronization data */
  RAIL_ASSERT_FAILED_RTCC_SYNC_STALE_DATA = 79,
  /** Attempted to clear LOG2X4 with a DEC1 value not equal to 0 */
  RAIL_ASSERT_INVALID_LOG2X4_CLEAR_CONDITION = 80,
  /** Failed to complete DMA write */
  RAIL_ASSERT_FAILED_DMA_WRITE_INCOMPLETE = 81,
  /** RAIL does not support this Radio Calculator configuration */
  RAIL_ASSERT_CALCULATOR_NOT_SUPPORTED = 82,
  /** Invalid binary image was loaded onto the sequencer */
  RAIL_ASSERT_INVALID_SEQUENCER_IMAGE = 83,
  /** No common or protocol image selected to be loaded onto the sequencer */
  RAIL_ASSERT_MISSING_SEQUENCER_IMAGE = 84,
  /** Software modem image invalid or missing */
  RAIL_ASSERT_INVALID_OR_MISSING_SOFTWARE_MODEM_IMAGE = 85,
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Self-referencing defines minimize compiler complaints when using RAIL_ENUM
#define RAIL_ASSERT_FAILED_APPENDED_INFO_MISSING               ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_APPENDED_INFO_MISSING)
#define RAIL_ASSERT_FAILED_RX_FIFO_BYTES                       ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_RX_FIFO_BYTES)
#define RAIL_ASSERT_UNUSED_2                                   ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_UNUSED_2)
#define RAIL_ASSERT_FAILED_ILLEGAL_RXLEN_ENTRY_STATUS          ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_ILLEGAL_RXLEN_ENTRY_STATUS)
#define RAIL_ASSERT_FAILED_BAD_PACKET_LENGTH                   ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_BAD_PACKET_LENGTH)
#define RAIL_ASSERT_FAILED_SYNTH_DIVCTRL_ENUM_CONVERSION_ERROR ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_SYNTH_DIVCTRL_ENUM_CONVERSION_ERROR)
#define RAIL_ASSERT_FAILED_UNEXPECTED_STATE_RX_FIFO            ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_UNEXPECTED_STATE_RX_FIFO)
#define RAIL_ASSERT_FAILED_UNEXPECTED_STATE_RXLEN_FIFO         ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_UNEXPECTED_STATE_RXLEN_FIFO)
#define RAIL_ASSERT_FAILED_UNEXPECTED_STATE_TX_FIFO            ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_UNEXPECTED_STATE_TX_FIFO)
#define RAIL_ASSERT_FAILED_UNEXPECTED_STATE_TXACK_FIFO         ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_UNEXPECTED_STATE_TXACK_FIFO)
#define RAIL_ASSERT_UNUSED_10                                  ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_UNUSED_10)
#define RAIL_ASSERT_UNUSED_11                                  ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_UNUSED_11)
#define RAIL_ASSERT_UNUSED_12                                  ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_UNUSED_12)
#define RAIL_ASSERT_FAILED_RTCC_POST_WAKEUP                    ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_RTCC_POST_WAKEUP)
#define RAIL_ASSERT_FAILED_SYNTH_VCO_FREQUENCY                 ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_SYNTH_VCO_FREQUENCY)
#define RAIL_ASSERT_FAILED_RAC_STATE                           ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_RAC_STATE)
#define RAIL_ASSERT_FAILED_SYNTH_INVALID_VCOCTRL               ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_SYNTH_INVALID_VCOCTRL)
#define RAIL_ASSERT_FAILED_NESTED_SEQUENCER_LOCK               ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_NESTED_SEQUENCER_LOCK)
#define RAIL_ASSERT_FAILED_RSSI_AVERAGE_DONE                   ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_RSSI_AVERAGE_DONE)
#define RAIL_ASSERT_UNUSED_19                                  ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_UNUSED_19)
#define RAIL_ASSERT_FAILED_PROTIMER_RANDOM_SEED                ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_PROTIMER_RANDOM_SEED)
#define RAIL_ASSERT_FAILED_EFR32XG1_REGISTER_SIZE              ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_EFR32XG1_REGISTER_SIZE)
#define RAIL_ASSERT_FAILED_PROTIMER_CHANNEL                    ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_PROTIMER_CHANNEL)
#define RAIL_ASSERT_UNUSED_23                                  ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_UNUSED_23)
#define RAIL_ASSERT_FAILED_BASECNTTOP                          ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_BASECNTTOP)
#define RAIL_ASSERT_UNUSED_25                                  ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_UNUSED_25)
#define RAIL_ASSERT_FAILED_RTCC_SYNC_MISSED                    ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_RTCC_SYNC_MISSED)
#define RAIL_ASSERT_FAILED_CLOCK_SOURCE_NOT_READY              ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_CLOCK_SOURCE_NOT_READY)
#define RAIL_ASSERT_UNUSED_28                                  ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_UNUSED_28)
#define RAIL_ASSERT_NULL_HANDLE                                ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_NULL_HANDLE)
#define RAIL_ASSERT_UNUSED_30                                  ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_UNUSED_30)
#define RAIL_ASSERT_FAILED_NO_ACTIVE_CONFIG                    ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_NO_ACTIVE_CONFIG)
#define RAIL_ASSERT_UNUSED_32                                  ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_UNUSED_32)
#define RAIL_ASSERT_UNUSED_33                                  ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_UNUSED_33)
#define RAIL_ASSERT_UNUSED_34                                  ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_UNUSED_34)
#define RAIL_ASSERT_UNUSED_35                                  ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_UNUSED_35)
#define RAIL_ASSERT_UNUSED_36                                  ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_UNUSED_36)
#define RAIL_ASSERT_UNUSED_37                                  ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_UNUSED_37)
#define RAIL_ASSERT_UNUSED_38                                  ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_UNUSED_38)
#define RAIL_ASSERT_DEPRECATED_FUNCTION                        ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_DEPRECATED_FUNCTION)
#define RAIL_ASSERT_MULTIPROTOCOL_NO_EVENT                     ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_MULTIPROTOCOL_NO_EVENT)
#define RAIL_ASSERT_FAILED_INVALID_INTERRUPT_ENABLED           ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_INVALID_INTERRUPT_ENABLED)
#define RAIL_ASSERT_UNUSED_42                                  ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_UNUSED_42)
#define RAIL_ASSERT_DIVISION_BY_ZERO                           ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_DIVISION_BY_ZERO)
#define RAIL_ASSERT_CANT_USE_HARDWARE                          ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_CANT_USE_HARDWARE)
#define RAIL_ASSERT_NULL_PARAMETER                             ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_NULL_PARAMETER)
#define RAIL_ASSERT_UNUSED_46                                  ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_UNUSED_46)
#define RAIL_ASSERT_SMALL_SYNTH_RADIO_CONFIG_BUFFER            ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_SMALL_SYNTH_RADIO_CONFIG_BUFFER)
#define RAIL_ASSERT_CHANNEL_HOPPING_BUFFER_TOO_SHORT           ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_CHANNEL_HOPPING_BUFFER_TOO_SHORT)
#define RAIL_ASSERT_INVALID_MODULE_ACTION                      ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_INVALID_MODULE_ACTION)
#define RAIL_ASSERT_CHANNEL_HOPPING_INVALID_RADIO_CONFIG       ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_CHANNEL_HOPPING_INVALID_RADIO_CONFIG)
#define RAIL_ASSERT_CHANNEL_CHANGE_FAILED                      ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_CHANNEL_CHANGE_FAILED)
#define RAIL_ASSERT_INVALID_REGISTER                           ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_INVALID_REGISTER)
#define RAIL_ASSERT_UNUSED_53                                  ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_UNUSED_53)
#define RAIL_ASSERT_CACHE_CONFIG_FAILED                        ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_CACHE_CONFIG_FAILED)
#define RAIL_ASSERT_NULL_TRANSITIONS                           ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_NULL_TRANSITIONS)
#define RAIL_ASSERT_BAD_LDMA_TRANSFER                          ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_BAD_LDMA_TRANSFER)
#define RAIL_ASSERT_INVALID_RTCC_SYNC_VALUES                   ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_INVALID_RTCC_SYNC_VALUES)
#define RAIL_ASSERT_SEQUENCER_FAULT                            ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_SEQUENCER_FAULT)
#define RAIL_ASSERT_BUS_ERROR                                  ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_BUS_ERROR)
#define RAIL_ASSERT_INVALID_FILTERING_CONFIG                   ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_INVALID_FILTERING_CONFIG)
#define RAIL_ASSERT_RETIMING_CONFIG                            ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_RETIMING_CONFIG)
#define RAIL_ASSERT_FAILED_TX_CRC_CONFIG                       ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_TX_CRC_CONFIG)
#define RAIL_ASSERT_INVALID_PA_OPERATION                       ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_INVALID_PA_OPERATION)
#define RAIL_ASSERT_SEQ_INVALID_PA_SELECTED                    ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_SEQ_INVALID_PA_SELECTED)
#define RAIL_ASSERT_FAILED_INVALID_CHANNEL_CONFIG              ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_INVALID_CHANNEL_CONFIG)
#define RAIL_ASSERT_INVALID_XTAL_FREQUENCY                     ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_INVALID_XTAL_FREQUENCY)
#define RAIL_ASSERT_UNUSED_67                                  ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_UNUSED_67)
#define RAIL_ASSERT_UNSUPPORTED_SOFTWARE_MODEM_MODULATION      ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_UNSUPPORTED_SOFTWARE_MODEM_MODULATION)
#define RAIL_ASSERT_FAILED_RTCC_SYNC_STOP                      ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_RTCC_SYNC_STOP)
#define RAIL_ASSERT_FAILED_MULTITIMER_CORRUPT                  ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_MULTITIMER_CORRUPT)
#define RAIL_ASSERT_FAILED_TEMPCAL_ERROR                       ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_TEMPCAL_ERROR)
#define RAIL_ASSERT_INVALID_EFF_CONFIGURATION                  ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_INVALID_EFF_CONFIGURATION)
#define RAIL_ASSERT_INVALID_RFFPLL_CONFIGURATION               ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_INVALID_RFFPLL_CONFIGURATION)
#define RAIL_ASSERT_SECURE_ACCESS_FAULT                        ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_SECURE_ACCESS_FAULT)
#define RAIL_ASSERT_FAILED_SYSRTC0_NOT_RUNNING                 ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_SYSRTC0_NOT_RUNNING)
#define RAIL_ASSERT_RADIO_CONFIG_NOT_UP_TO_DATE                ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_RADIO_CONFIG_NOT_UP_TO_DATE)
#define RAIL_ASSERT_FAILED_RSSI_THRESHOLD                      ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_RSSI_THRESHOLD)
#define RAIL_ASSERT_INCORRECT_ZWAVE_REGION                     ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_INCORRECT_ZWAVE_REGION)
#define RAIL_ASSERT_FAILED_RTCC_SYNC_STALE_DATA                ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_RTCC_SYNC_STALE_DATA)
#define RAIL_ASSERT_INVALID_LOG2X4_CLEAR_CONDITION             ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_INVALID_LOG2X4_CLEAR_CONDITION)
#define RAIL_ASSERT_FAILED_DMA_WRITE_INCOMPLETE                ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_FAILED_DMA_WRITE_INCOMPLETE)
#define RAIL_ASSERT_CALCULATOR_NOT_SUPPORTED                   ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_CALCULATOR_NOT_SUPPORTED)
#define RAIL_ASSERT_INVALID_SEQUENCER_IMAGE                    ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_INVALID_SEQUENCER_IMAGE)
#define RAIL_ASSERT_MISSING_SEQUENCER_IMAGE                    ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_MISSING_SEQUENCER_IMAGE)
#define RAIL_ASSERT_INVALID_OR_MISSING_SOFTWARE_MODEM_IMAGE    ((RAIL_AssertErrorCodes_t) RAIL_ASSERT_INVALID_OR_MISSING_SOFTWARE_MODEM_IMAGE)
#endif//DOXYGEN_SHOULD_SKIP_THIS

/// Use this define to create an array of error messages that map to the codes
/// in \ref RAIL_AssertErrorCodes_t. You can use these to print slightly more
/// detailed error strings related to a particular assert error code if desired.
/// For example, you could implement your assert failed callback as follows to
/// make use of this.
///
/// @code{.c}
/// void RAILCb_AssertFailed(RAIL_Handle_t railHandle, uint32_t errorCode)
/// {
///   static const char* railErrorMessages[] = RAIL_ASSERT_ERROR_MESSAGES;
///   const char *errorMessage = "Unknown";
///
///   // If this error code is within the range of known error messages then use
///   // the appropriate error message.
///   if (errorCode < (sizeof(railErrorMessages) / sizeof(char*))) {
///     errorMessage = railErrorMessages[errorCode];
///   }
///   printf(errorMessage);
///
///   // Reset the chip since an assert is a fatal error
///   NVIC_SystemReset();
/// }
/// @endcode
///
#define RAIL_ASSERT_ERROR_MESSAGES {                                                   \
    /* 0*/ "Appended info missing from RX packet",                                     \
    /* 1*/ "Receive FIFO too small for IR calibration",                                \
    /* 2*/ "Invalid assert, no longer used",                                           \
    /* 3*/ "Receive FIFO entry has invalid status",                                    \
    /* 4*/ "Receive FIFO entry bad packet length",                                     \
    /* 5*/ "Unable to configure radio for IR calibration",                             \
    /* 6*/ "Reached unexpected state while handling RX FIFO events",                   \
    /* 7*/ "Reached unexpected state while handling RXLEN FIFO events",                \
    /* 8*/ "Reached unexpected state while handling TX FIFO events",                   \
    /* 9*/ "Reached unexpected state while handling TX ACK FIFO events",               \
    /*10*/ "Invalid assert, no longer used",                                           \
    /*11*/ "Invalid assert, no longer used",                                           \
    /*12*/ "Invalid assert, no longer used",                                           \
    /*13*/ "Error synchronizing the RAIL timebase after sleep",                        \
    /*14*/ "VCO frequency outside supported range",                                    \
    /*15*/ "Radio active while changing channels",                                     \
    /*16*/ "Invalid Synth VCOCTRL field calculation",                                  \
    /*17*/ "Nested attempt to lock the sequencer",                                     \
    /*18*/ "RSSI averaging enabled without a valid callback",                          \
    /*19*/ "Invalid assert, no longer used",                                           \
    /*20*/ "Unable to seed radio pseudo random number generator",                      \
    /*21*/ "Timeout exceeds EFR32XG1 register size",                                   \
    /*22*/ "Invalid timer channel specified",                                          \
    /*23*/ "Invalid assert, no longer used",                                           \
    /*24*/ "LBT config exceeds EFR32XG1 register size",                                \
    /*25*/ "Invalid assert, no longer used",                                           \
    /*26*/ "Could not synchronize RAIL timebase with the RTC",                         \
    /*27*/ "Clock source not ready",                                                   \
    /*28*/ "Invalid assert, no longer used",                                           \
    /*29*/ "NULL was supplied as a RAIL_Handle_t argument",                            \
    /*30*/ "Invalid assert, no longer used",                                           \
    /*31*/ "API improperly called while protocol inactive",                            \
    /*32*/ "Invalid assert, no longer used",                                           \
    /*33*/ "Invalid assert, no longer used",                                           \
    /*34*/ "Invalid assert, no longer used",                                           \
    /*35*/ "Invalid assert, no longer used",                                           \
    /*36*/ "Invalid assert, no longer used",                                           \
    /*37*/ "Invalid assert, no longer used",                                           \
    /*38*/ "Invalid assert, no longer used",                                           \
    /*39*/ "This function is deprecated and must not be called",                       \
    /*40*/ "Multiprotocol task started with no event to run",                          \
    /*41*/ "Invalid interrupt enabled",                                                \
    /*42*/ "Invalid assert, no longer used",                                           \
    /*43*/ "Division by zero",                                                         \
    /*44*/ "Function cannot be called without access to the hardware",                 \
    /*45*/ "Pointer parameter was passed as NULL",                                     \
    /*46*/ "Invalid assert, no longer used",                                           \
    /*47*/ "Synth radio config buffer for channel hopping too small",                  \
    /*48*/ "Buffer provided for RX Channel Hopping is too small",                      \
    /*49*/ "Invalid action was attempted on a module",                                 \
    /*50*/ "The radio config for this channel is not compatible with channel hopping", \
    /*51*/ "Channel change failed",                                                    \
    /*52*/ "Attempted to read invalid register",                                       \
    /*53*/ "Invalid assert, no longer used",                                           \
    /*54*/ "DMP radio config caching failed",                                          \
    /*55*/ "NULL was supplied as a RAIL_StateTransitions_t argument",                  \
    /*56*/ "LDMA transfer failed",                                                     \
    /*57*/ "Attempted to wake up with invalid RTCC sync data",                         \
    /*58*/ "Radio sequencer hit a fault condition",                                    \
    /*59*/ "Bus fault",                                                                \
    /*60*/ "The current radio config cannot be used with packet filtering",            \
    /*61*/ "Retiming configuration error",                                             \
    /*62*/ "TX CRC configuration is corrupt",                                          \
    /*63*/ "The current PA config does not allow for this operation",                  \
    /*64*/ "The sequencer selected an invalid PA",                                     \
    /*65*/ "Invalid/unsupported channel config",                                       \
    /*66*/ "Radio Calculator configuration HFXO frequency mismatch with chip",         \
    /*67*/ "Invalid assert, no longer used",                                           \
    /*68*/ "Software modem image does not support requested modulation",               \
    /*69*/ "Failed to disable RTCC synchronization",                                   \
    /*70*/ "Multitimer linked list corrupted",                                         \
    /*71*/ "Unable to configure radio for temperature calibration",                    \
    /*72*/ "Invalid EFF configuration",                                                \
    /*73*/ "PHY and System RFFPLL settings do not match",                              \
    /*74*/ "Secure access fault",                                                      \
    /*75*/ "SYSRTC0 not running",                                                      \
    /*76*/ "Radio Configurator not updated",                                           \
    /*77*/ "Failed to set the event for configurable RSSI threshold",                  \
    /*78*/ "Intended and actual Z-Wave region configuration mismatch",                 \
    /*79*/ "Attempted to sleep with stale RTCC synchronization data",                  \
    /*80*/ "Attempted to clear LOG2X4 with a DEC1 value not equal to 0",               \
    /*81*/ "Failed to complete DMA write",                                             \
    /*82*/ "RAIL does not support this Radio Calculator configuration",                \
    /*83*/ "Invalid binary image loaded on sequencer",                                 \
    /*84*/ "No common or protocol image selected to be loaded onto the sequencer",     \
    /*85*/ "Software modem image invalid or missing",                                  \
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  // __RAIL_ASSERT_ERROR_CODES_H__
