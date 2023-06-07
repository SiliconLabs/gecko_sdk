#ifndef SL_BTCTRL_RESOLVING_LIST_CONFIG_H
#define SL_BTCTRL_RESOLVING_LIST_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Bluetooth Controller Configuration

// <o SL_BT_CONFIG_RESOLVING_LIST_SIZE> Bluetooth Controller Resolving List Size
// <0..8:1>
// <i> Default: 2
// <i> Define the number of resolving list entries to be used in linklayer privacy.
#define SL_BT_CONFIG_RESOLVING_LIST_SIZE     (2)

#if SL_BT_CONFIG_RESOLVING_LIST_SIZE > RADIOAES_BLE_RPA_MAX_KEYS
#error "The configured resolving list size cannot be handled by the bluetooth stack/controller"
#endif

// </h> Bluetooth Controller Configuration

// <<< end of configuration section >>>

#endif // SL_BTCTRL_RESOLVING_LIST_CONFIG_H
