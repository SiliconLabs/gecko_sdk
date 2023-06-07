#ifndef SL_BT_CONNECTION_CONFIG_H
#define SL_BT_CONNECTION_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>
// <o SL_BT_CONFIG_MAX_CONNECTIONS> Max number of connections reserved for user <0-32>
// <i> Default: 4
// <i> Define the number of connections the application needs.
#define SL_BT_CONFIG_MAX_CONNECTIONS     (4)

// <o SL_BT_CONFIG_CONNECTION_DATA_LENGTH> Preferred maximum TX payload octets <27-251>
// <i> Default: 251
// <i> Define the preferred maximum TX payload octets that will be used on connections.
// <i> This value is set to the controller as the default suggested data length when
// <i> Bluetooth stack is started.
#define SL_BT_CONFIG_CONNECTION_DATA_LENGTH     (251)

// <<< end of configuration section >>>
#endif
