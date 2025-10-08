#ifndef SL_BTCTRL_CONFIG_H
#define SL_BTCTRL_CONFIG_H

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

// <o SL_BT_CONFIG_MAX_QUEUED_ADV_REPORTS> Maximum number of queued advertisement reports <1-255>
// <i> Default: 10
// <i> Define the maximum number of queued advertisement reports. Additional advertisement reports are dropped.
#define SL_BT_CONFIG_MAX_QUEUED_ADV_REPORTS     (10)

// <h> Advertising Configuration
// <e SL_BT_CONTROLLER_PRIMARY_EXT_PACKET_INCLUDE_TX_POWER> Include TX Power in the extended header of primary extended advertising packets
// <i> This is default setting to all advertising sets unless it is specifically overridden by VS_SiliconLabs_Set_Advertising_Config_Bits.
// <i> Default: 0
// <i> Enabling this option takes effect only if permitted by Le_Set_Extended_Advertising_Parameters
// <i> According to Link Layer specification, Vol 6, Part B, Table 2.4 and Table 2.5:
// <i> Optional in 1M PHY when the advertiser is connectable or scannable, or with auxiliary pointer.
// <i> In other cases, the Extended Advertising TX Power is always optional by settings.
#define SL_BT_CONTROLLER_PRIMARY_EXT_PACKET_INCLUDE_TX_POWER     (0)
// </e>
// <e SL_BT_CONTROLLER_PRIMARY_EXT_PACKET_INCLUDE_ADDRESS> Include Advertiser Address in the header of primary extended advertising packets
// <i> This is default setting to all advertising sets unless it is specifically overridden by VS_SiliconLabs_Set_Advertising_Config_Bits.
// <i> Default: 0
// <i> Enabling this option takes effect only if permitted by Le_Set_Extended_Advertising_Parameters
// <i> According to Link Layer specification, Vol 6, Part B, Table 2.4 and Table 2.5:
// <i> Optional in 1M PHY when the advertiser is non-connectable and non-scannable, with auxiliary pointer.
// <i> Mandatory when the advertiser is non-connectable and non-scannable, without auxiliary pointer.
// <i> Forbidden when the advertiser is connectable or scannable.
#define SL_BT_CONTROLLER_PRIMARY_EXT_PACKET_INCLUDE_ADDRESS      (0)
// </e>
// </h> Advertising Configuration
// </h> Bluetooth Controller Configuration

// <<< end of configuration section >>>

#endif // SL_BTCTRL_CONFIG_H
