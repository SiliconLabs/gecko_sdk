/***************************************************************************//**
 * @file
 * @brief Internal APIs and defines for the Network Steering plugin.
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

#include "app/framework/plugin/network-steering/network-steering.h"

extern const char * sli_zigbee_af_network_steering_stateNames[];
extern uint8_t sli_zigbee_af_network_steering_total_beacons;
extern uint8_t sli_zigbee_af_network_steering_join_attempts;

#if (EMBER_AF_PLUGIN_NETWORK_STEERING_OPTIMIZE_SCANS != 1)
extern uint8_t sli_zigbee_af_network_steering_pan_id_index;
#endif // # EMBER_AF_PLUGIN_NETWORK_STEERING_OPTIMIZE_SCANS

uint8_t sli_zigbee_af_network_steering_get_max_possible_pan_ids(void);
void sli_zigbee_af_network_steering_clear_stored_pan_ids(void);
uint16_t* sli_zigbee_af_network_steering_get_stored_pan_id_pointer(uint8_t index);

void emberAfPluginNetworkSteeringCompleteCallback(EmberStatus status,
                                                  uint8_t totalBeacons,
                                                  uint8_t joinAttempts,
                                                  uint8_t finalState);
uint8_t sli_zigbee_af_network_steering_get_current_channel();

extern EmberAfPluginNetworkSteeringJoiningState sli_zigbee_af_network_steering_state;

#ifdef TRY_ALL_KEYS
  #define TRYING_ALL_KEYS                                                \
  (((sli_zigbee_af_network_steering_state)                               \
    == EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_PRIMARY_USE_ALL_KEYS) \
   || ((sli_zigbee_af_network_steering_state)                            \
       == EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_SECONDARY_USE_ALL_KEYS))
#else // TRY_ALL_KEYS
    #define TRYING_ALL_KEYS         false
#endif // TRY_ALL_KEYS

#define sli_zigbee_af_network_steering_state_uses_install_codes()             \
  (((sli_zigbee_af_network_steering_state)                                    \
    == EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_PRIMARY_INSTALL_CODE)      \
   || ((sli_zigbee_af_network_steering_state)                                 \
       == EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_SECONDARY_INSTALL_CODE) \
   || TRYING_ALL_KEYS)

#define sli_zigbee_af_network_steering_state_uses_centralized_key()     \
  (((sli_zigbee_af_network_steering_state)                              \
    == EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_PRIMARY_CENTRALIZED) \
   || ((sli_zigbee_af_network_steering_state)                           \
       == EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_SECONDARY_CENTRALIZED))

#define sli_zigbee_af_network_steering_state_uses_distributed_key()     \
  (((sli_zigbee_af_network_steering_state)                              \
    == EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_PRIMARY_DISTRIBUTED) \
   || ((sli_zigbee_af_network_steering_state)                           \
       == EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_SECONDARY_DISTRIBUTED))

#define sli_zigbee_af_network_steering_state_set_update_tclk() \
  ((sli_zigbee_af_network_steering_state)                      \
     |= EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_UPDATE_TCLK)
#define sli_zigbee_af_network_steering_state_update_tclk() \
  ((sli_zigbee_af_network_steering_state)                  \
   & EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_UPDATE_TCLK)
#define sli_zigbee_af_network_steering_state_clear_update_tclk() \
  ((sli_zigbee_af_network_steering_state)                        \
     &= ~EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_UPDATE_TCLK)

#define sli_zigbee_af_network_steering_state_set_verify_tclk() \
  ((sli_zigbee_af_network_steering_state)                      \
     |= EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_VERIFY_TCLK)
#define sli_zigbee_af_network_steering_state_verify_tclk() \
  ((sli_zigbee_af_network_steering_state)                  \
   & EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_VERIFY_TCLK)
#define sli_zigbee_af_network_steering_state_clear_verify_tclk() \
  ((sli_zigbee_af_network_steering_state)                        \
     &= ~EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_VERIFY_TCLK)
