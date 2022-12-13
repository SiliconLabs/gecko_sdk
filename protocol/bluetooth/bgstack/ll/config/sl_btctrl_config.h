#ifndef SL_BT_RTOS_CONFIG_H
#define SL_BT_RTOS_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Bluetooth Controller Configuration

// <o SL_BT_CONTROLLER_BUFFER_MEMORY> Bluetooth Controller Buffer Memory
// <i> Default: SL_BT_CONTROLLER_BUFFER_MEMORY
// <i> Define the Amount of memory to allocate for tx/rx buffers in Bluetooth Controller
#define SL_BT_CONTROLLER_BUFFER_MEMORY     (8192)

// <o SL_BT_CONTROLLER_LE_BUFFER_SIZE_MAX> Bluetooth Controller ACL data packets that can be stored
// <i> Default: SL_BT_CONTROLLER_LE_BUFFER_SIZE_MAX
// <i> Define the total number of the maximum sized ACL data packets that can be received from the host
#define SL_BT_CONTROLLER_LE_BUFFER_SIZE_MAX     (3)

// <o SL_BT_CONTROLLER_COMPLETED_PACKETS_THRESHOLD> Total transmitted packets threshold for all connections to send the Number Of Completed Packets HCI event to the host <1-255>
// <i> Default: 4
// <i> Define the number of transmitted air interface ACL packets to trigger the Number Of Completed Packets HCI event.
#define SL_BT_CONTROLLER_COMPLETED_PACKETS_THRESHOLD     (4)

// <o SL_BT_CONTROLLER_COMPLETED_PACKETS_EVENTS_TIMEOUT> Number of connection events to send the Number Of Completed Packets HCI event to the host <1-255>
// <i> Default: 3
// <i> Define the maximum number of connection events since the previous Number Of Completed Packets HCI event to trigger reporting of any unreported completed ACL packets.
#define SL_BT_CONTROLLER_COMPLETED_PACKETS_EVENTS_TIMEOUT     (3)

// </h> Bluetooth Controller Configuration

// <<< end of configuration section >>>

#endif // SL_BT_RTOS_CONFIG_H
