/***************************************************************************//**
 * @file
 * @brief APIs for the Coulomb Counter plugin.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SILABS_COULOMB_COUNTER_H
#define SILABS_COULOMB_COUNTER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SL_WEAK
#define SL_WEAK __attribute__ ((weak))
#endif

#define COULOMB_COUNTER_MAX_NB_USER_DEFINED_ADDITIVE_STATES   (16U)
typedef enum {
  EMBER_AF_PLUGIN_COULOMB_COUNTER_RADIO_MODE_RX_SHIFT = 0,
  EMBER_AF_PLUGIN_COULOMB_COUNTER_RADIO_MODE_TX_SHIFT = 1,
  EMBER_AF_PLUGIN_COULOMB_COUNTER_CORE_MODE_SLEEP_SHIFT = 2,
  EMBER_AF_PLUGIN_COULOMB_COUNTER_CORE_MODE_IDLE_SHIFT = 3,
  EMBER_AF_PLUGIN_COULOMB_COUNTER_CORE_MODE_AWAKE_SHIFT = 4,
  // Maximum value allowed for core mode
  EMBER_AF_PLUGIN_COULOMB_COUNTER_CORE_MODE_MAX = 32
} EmberAfPluginCoulombCounterCoreMode;

/** Radio in Idle state */

/** Radio in Receive state */
#define EMBER_AF_PLUGIN_COULOMB_COUNTER_RADIO_MODE_RX                (1U << EMBER_AF_PLUGIN_COULOMB_COUNTER_RADIO_MODE_RX_SHIFT)
/** Radio in Transmit state */
#define EMBER_AF_PLUGIN_COULOMB_COUNTER_RADIO_MODE_TX                (1U << EMBER_AF_PLUGIN_COULOMB_COUNTER_RADIO_MODE_TX_SHIFT)

#define EMBER_AF_PLUGIN_COULOMB_COUNTER_CORE_MODE_SLEEP              (1U << EMBER_AF_PLUGIN_COULOMB_COUNTER_CORE_MODE_SLEEP_SHIFT)

#define EMBER_AF_PLUGIN_COULOMB_COUNTER_CORE_MODE_IDLE               (1U << EMBER_AF_PLUGIN_COULOMB_COUNTER_CORE_MODE_IDLE_SHIFT)

#define EMBER_AF_PLUGIN_COULOMB_COUNTER_CORE_MODE_AWAKE              (1U << EMBER_AF_PLUGIN_COULOMB_COUNTER_CORE_MODE_AWAKE_SHIFT)

/** A mask representing all Radio state options <bit1:bit0>*/
#define EMBER_AF_PLUGIN_COULOMB_COUNTER_RADIO_EVENT_MASK             (0x03U)

/** A mask representing all EM mode options <bit4:bit2>*/
#define EMBER_AF_PLUGIN_COULOMB_COUNTER_EM_MODE_MASK                 (0x1CU)

#define EMBER_AF_PLUGIN_COULOMB_COUNTER_MASK                         (0xFFFFU)
#define EMBER_AF_PLUGIN_COULOMB_COUNTER_USER_DEF_STATES              (EMBER_AF_PLUGIN_COULOMB_COUNTER_MASK \
                                                                      << COULOMB_COUNTER_MAX_NB_USER_DEFINED_ADDITIVE_STATES)

/** @brief Updates the state of all tracked additive modes.
 *
 * Updates the current state of all tracked additive modes. All bits raised in the bitfield indicate
 * that the state is current 'On'. Any update to the bitfield from the previously stored value will
 * trigger an energy consumption update.
 * Upper 16 bits are the user-defined additive modes while the lower 16 bits are reserved for the
 * Radio states and core modes.
 *
 * @param[in] mask Mask for choosing between the User-defined or Default modes.
 * @param[in] options Values to set for the User-defined or Default modes.
 *
 * @note User must not set/unset the lower 16 bits, those are reserved for internal use.
 *      Only the upper 16 bits may be used for any custom additive states.
 */
void emberAfPluginCoulombCounterEventCallback(uint32_t mask, uint32_t options);

/** @brief Returns the current core mode.
 *
 * Returns the current core mode of the system. The core mode is the basis for energy consumption measurements.
 * Each core mode is mutually exclusive.
 *
 * @return the current core mode.
 */
uint16_t emberAfPluginCommandCoulombCounterGetCurrentCoreMode(void);

/** @brief Returns the current state of all additive modes.
 *
 * Returns the current state of all additive modes. All bits raised in the bitfield indicate
 * that the state is current 'On'.
 *
 * @return the current additive modes bitfield.
 */
uint16_t emberAfPluginCommandCoulombCounterGetAdditiveModesBitfield(void);

/** @brief Returns the cumulative energy usage metric since last value reset.
 *
 * Returns the cumulative energy usage metric since last value reset. This value is in the same unit as all other
 * provided values and is persisted until explicitely reset.
 *
 * @return the currently recorded energy usage.
 */
uint32_t emberAfPluginCommandCoulombCounterGetEnergyUsage(void);

/** @brief Resets the energy usage metric.
 *
 * Resets the energy usage metric. This calls clears both the volatile and non volatile values.
 */
void emberAfPluginCommandCoulombCounterResetEnergyUsage(void);

/** @brief Tick function for this plugin.
 *
 * This tick function monitors the time since the last time we saved the NVM token
 * and makes sure we periodically write it to flash.
 */
void emberAfPluginCoulombCounterTick(void);

#ifdef __cplusplus
}
#endif

#endif //SILABS_COULOMB_COUNTER_H
