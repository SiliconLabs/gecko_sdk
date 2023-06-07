# Wi-SUN - SoC Border Router

The Wi-SUN Border Router demonstration provides a Wi-SUN Border Router implementation running entirely on the EFR32. It provides an easy and quick way to evaluate the Silicon Labs Wi-SUN stack solution without deploying an expensive and cumbersome production-grade Wi-SUN Border Router. A CLI (Command-Line Interface) is exposed to facilitate the configuration.

> The Wi-SUN Border Router demonstration is delivered only in a binary format. The implementation does not scale for a production-grade Border Router maintaining several thousand Wi-SUN nodes.

## Getting Started

To get started with Wi-SUN and Simplicity Studio, see [QSG181: Wi-SUN SDK Quick Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg181-wi-sun-sdk-quick-start-guide.pdf).

The Wi-SUN Border Router demonstration is required to use the other Wi-SUN sample applications. The Wi-SUN Border Router creates a Wi-SUN network the Wi-SUN nodes can join. When part of the same network, the Wi-SUN nodes are able to exchange IP packets.

To get started with the demo, follow these steps:

* Flash the "Wi-SUN Border Router" demonstration to a compatible device.
* In Simplicity Studio, open a console on the device.
* Start the Border Router using the CLI command `wisun start_fan11` when using FAN-1.1 PHY configuration type and `wisun start_fan10` in order to use FAN-1.0 Phy configuration type.

See the associated sections in [QSG181: Wi-SUN SDK Quick Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg181-wi-sun-sdk-quick-start-guide.pdf) if you want step-by-step guidelines for each operation.

## Wi-SUN Border Router Commands

To see the available commands, enter the following command in the console:

    wisun help

The list of available commands is output on the console with the associated help. Following is an extended description and examples of how to use each command.

| Command | Description | Example |
|---|---|---|
|`wisun start_fan10` <br /> `w st10`  | Start the border router using FAN-1.0 PHY settings  | `> wisun start_fan10`    |
| `wisun start_fan11` <br /> `w st11`  | Start the border router using FAN-1.1 PHY settings  | `> wisun start_fan11`    |
| `wisun start_explicit` <br /> `w ste`| Start the border router using explicit PHY settings | `> wisun start_explicit` |
| `wisun.start_ids` <br> `w sti` | Start the border router using radio conf ids | `> wisun start_ids` |
| `wisun get [domain].[key]` | Get a setting variable. <br /> Specifying only the domain retrieves all keys of the domain. | `> wisun get wisun.ip_addresses` <br> `> wisun get wisun` |
| `wisun set [domain].[key] [value]` | Set a setting variable | `> wisun set wisun.network_size test` |
| `wisun save` | Save variables to NVM  | `> wisun save` |
| `wisun reset` | Reset variables to default values | `> wisun reset` |
| `wisun certificate_store` | Store a certificate | `> wisun certificate_store` |
| `wisun certificate_remove` | Remove a certificate | `> wisun certificate_remove 1` |
| `wisun certificate_list` | List installed certificates | `> wisun certificate_list` |
| `wisun reset_statistics` <br> `w rs` | Reset the statistics | `> wisun reset` |
| `wisun set_unicast_tx_mode [mode]` | configure unicast tx mode: <br> - [uint8] mode: 0=default, 1=slot | `> wisun set_unicast_tx_mode 0` |
| `wisun set_lfn_support [lfn_limit] [lfn_support_pan]`| configure LFN support: <br> - [uint8] lfn_limit: Number of LFN children (10 maximum) <br> - [uint8] lfn_support_pan: Enable or disable LFN support for BR's PAN (0 or 1) | `> wisun set_lfn_support 3 0` |
| `wisun mode_switch [mode] [phy_mode_id] [neighbor_mac_address]` <br> `w ms` |  configure mode switch: <br> - [uint8] mode: 0=disabled, 1=enabled, 2=default <br> - [uint8] PhyModeId <br> - [string] neighbor MAC address (optional)   | `> wisun mode_switch 1 84` <br> `> wisun mode_switch 1 84 01:02:03:04:05:06:07:08 ` |
|`wisun set_trace_level <string>` | Set [trace level](https://docs.silabs.com/wisun/latest/wisun-stack-api/sl-wisun-types#sl-wisun-trace-level-t) for a [trace group](https://docs.silabs.com/wisun/latest/wisun-stack-api/sl-wisun-types#sl-wisun-trace-group-t) | - To set all 64 trace groups at once: <br>  `> wisun set_trace_level all` <br> - To set 2 groups at once: <br> `> wisun set_trace_level 1,none;4,info` |

## Wi-SUN Border Router Settings

The command-line interface maintains a number of settings. The Wi-SUN settings are distributed in two sections: *wisun* and *app*. They can be listed by entering:

    wisun get <section name>

The Wi-SUN stack settings are listed with their current state/value. Some of them can be modified by using the following command prototype:

    wisun set <section name>.<settings name> <value>

To modify the network name used by the Wi-SUN Border Router, enter:

    wisun set wisun.network_name "My Network"

Next time you issue the `wisun start_fan11` command in the case of a FAN-1.1 PHY, the Border Router creates a Wi-SUN network named "My Network".

### *wisun* Section Settings

- The settings in the *wisun* section are directly related to the Wi-SUN stack behavior. The following is a detailed setting list.
- Writable settings are valid for all PHYs unless it is specified otherwise in the last column .

| Variable | R/W | Type | Values | Description | Applies to |
|---|---|---|---|---|---|
| wisun.state | R | string | - initialized (1)<br> - operational (2) | State of the border router |  |
| wisun.network_name | R/W | string | up to 31 ASCII characters | Name of the Wi-SUN network |  |
| wisun.phy_config_type | R | string | - FAN 1.0 (0) <br> - FAN 1.1 (1) <br> - explicit (2) <br> - IDs (3) | PHY configuration type |  |
| wisun.regulatory_domain | R/W | integer | - WW (0): Worldwide <br> - NA (1): North America<br> - JP (2): Japan <br> - EU (3): Europe <br> - CN (4): China <br> - IN (5): India <br> - MX (6): Mexico <br> - BZ (7): Brazil <br> - AZ (8): Australia/New Zealand <br> - KR (9): South Korea <br> - PH (10): Philippines<br> - MY (11): Malaysia <br> - HK (12): Hong Kong <br> - SG (13): Singapore <br> - TH (14): Thailand <br> - VN (15): Vietnam <br> - application (255): application specific | Regulatory domain of the Wi-SUN network | - FAN1.0 <br> - FAN1.1 |
| wisun.operating_class | R/W | integer | - 1 to 4 <br> - application (255): application specific | Operating class of the Wi-SUN network to use | - FAN1.0 |
| wisun.operating_mode | R/W | integer | - 0x1a (1a) <br>- 0x1b (1b) <br> - 0x2a (2a) <br> - 0x2b (2b) <br> - 0x3 (3) <br> - 0x4a (4a) <br> - 0x4b (4b) <br> - 0x5 (5) | Operating mode of the Wi-SUN network to use | - FAN1.0 |
| wisun.fec | R/W | bool | - enable FEC (1) <br> - disable FEC (0) | enable or disable FEC | - FAN1.0 |
| wisun.chan_plan_id| R/W | integer | - Europe: 32-37 <br> - North America: 1-5 <br> - Brazil: 1-5 <br> - Japan: 21-24 | Wi-SUN channel plan ID [uint8] | - FAN1.1 |
| wisun.phy_mode_id | R/W | integer | - Europe: <br> FSK without FEC: 1/3/5 <br> FSK FEC: 17/19/21 <br> OFDM: 84-86 <br> - North America: <br> FSK without FEC: 2/3/5/6/8 <br> FSK FEC: 18/19/21/22/24 <br> OFDM: 34-38 / 51-54 / 68-70 / 84-86 <br> - Brazil: <br> FSK without FEC: 2/3/5/6/8 <br> FSK fEC: 18/19/21/22/24 <OFDM> 34-38 / 51-54 / 68-70 / 84-86 <BR> - Japan: <br> FSK without FEC: 2/4/5/7/8 <br> FSK FEC: 18/20/21/23/24 <br> OFDM: 51-54 / 68-70 / 84-86 |  Wi-SUN PHY mode ID [uint8] | - FAN1.1 <br> - explicit <br> - join by IDs |
| wisun.ch0_frequency | R/W | integer | - 100kHz (0) <br> - 200KHz (1) <br> - 400KHz (2) <br> - 600 KHz (3) <br> - 250KHz (4) <br> - 800KHz (5) <br> - 1200KHz (6) | Ch0 frequency in kHz | - explicit |
| wisun.channel_spacing | R/W | integer | - 100 kHz (0) <br> - 200 kHz (1) <br> - 400 kHz (2) <br> - 600 kHz (3) <br> - 250KHz (54)<br> - 800KHz (5)<br> - 1200KHz (6) | channel spacing | - explicit |
| wisun.number_of_channels | R/W | integer | [uint16] | Number of channels | - explicit |
| wisun.protocol_id | R/W | integer | [uint16] | Radioconf protocol ID | - join by IDs |
| wisun.channel_id | R/W | integer | [uint16] | Radioconf protocol ID | - join by IDs |
| wisun.network_size                   | R/W | integer     | - automatic (0) <br> - small (default): less than 100 nodes (1) <br> - medium: 100 to 1000 nodes (2) <br> - large: more than 1000 nodes (3) <br> - test (4) <br> - certification (6) |  Used to optimize network timings considering the number of expected nodes on the network. |  |
| wisun.allowed_channels | R/W | integer | Allowed channel ranges (e.g. 0-54,57-60,64,67-68) |Allowed channel ranges |  |
| wisun.unicast_dwell_interval | R/W | integer | 15 to 255 | Unicast dwell interval in milliseconds |  |
| wisun.broadcast_dwell_interval | R/W | integer | 100 to 255 | Broadcast dwell interval in milliseconds |  |
| wisun.broadcast_interval | R/W | integer | Broadcast dwell interval to 16777 | Broadcast interval in milliseconds |  |
| wisun.channel_mask | R | string |  | Excluded channel mask |  |
| wisun.gtk1 | R/W | string | GTK to install, 'none' to uninstall | GTK to install |  |
| wisun.gtk2 | R/W | string | GTK to install, 'none' to uninstall | GTK to install |  |
| wisun.gtk3 | R/W | string | GTK to install, 'none' to uninstall | GTK to install |  |
| wisun.gtk4 | R/W | string | GTK to install, 'none' to uninstall | GTK to install |  |
| wisun.gak1 |  R  | string |  | GAK derived from GTK1 |  |
| wisun.gak2 |  R  | string |  | GAK derived from GTK2 |  |
| wisun.gak3 |  R  | string |  | GAK derived from GTK3 |  |
| wisun.gak4 |  R  | string |  | GAK derived from GTK4 |  |
| wisun.lfn_gak1 | R | string |  | GAK derived from LGTK1 |  |
| wisun.lfn_gak2 | R | string |  | GAK derived from LGTK1 |  |
| wisun.lfn_gak3 | R | string |  | GAK derived from LGTK1 |  |
| wisun.mac_address | R | string |  | MAC address (EUI-64)|  |
|wisun.ip_addresses | R | string |  | IPv6 addresses |  |
| wisun.trace_filter | R/W | integer |  1 bit per group | Trace filter group list |  |
| wisun.regulation | R/W | integer | [uint8] | Regional regulation |  |
| wisun.device_type | R/W | integer | - FFN (0) <br> - LFN (1)  <br> - BR (2) | Device type |  |
| wisun.rx_phy_mode_ids | R/W | integer | list of phy_mode_ids | List of PhyModeId to advertise in POM-IE | FAN1.1 |
| wisun.lfn_profile | R/W | integer | - Test (0) <br> - Balanced (1) <br> - Eco (2) | Wi-SUN LFN profile | FAN1.1 |

### *app* Section Settings

The settings in the *app* section relate to the application options. A detailed setting list follows.

| Variable | R/W | Type | Values | Description |
|---|---|---|---|---|
| app.autostart | R/W | integer | 0: the border router does not start on reset<br>1: the border router automatically starts on reset | If enabled, the border router automatically starts |
| app.printable_data_length | R/W | integer | 0: received socket data is not printed<br>1 - 64: amount of characters per line | If enabled, received socket data is printed |
| app.printable_data_as_hex | R/W | integer | 0: print received socket data as ASCII<br>1: print received socket data as hex | Output type for received socket data |
| app.pti_state | R/W | bool | 0: disable <br> 1: enable | Disable or enable PTI [bool] (0&#124;1) |
## Troubleshooting

Before programming the radio board mounted on the WSTK, ensure the power supply switch is in the AEM position (right side), as shown.

![Radio Board Power Supply Switch](readme_img0.png)

## Resources

* [Wi-SUN Stack API documentation](https://docs.silabs.com/wisun/latest)
* [AN1330: Wi-SUN Mesh Network Performance](https://www.silabs.com/documents/public/application-notes/an1330-wi-sun-network-performance.pdf)
* [AN1332: Wi-SUN Network Setup and Configuration](https://www.silabs.com/documents/public/application-notes/an1332-wi-sun-network-configuration.pdf)
* [AN1364: Wi-SUN Network Performance Measurement Application](https://www.silabs.com/documents/public/application-notes/an1364-wi-sun-network-performance-measurement-app.pdf)
* [QSG181: Wi-SUN Quick-Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg181-wi-sun-sdk-quick-start-guide.pdf)
* [UG495: Wi-SUN Developer's Guide](https://www.silabs.com/documents/public/user-guides/ug495-wi-sun-developers-guide.pdf)

## Report Bugs & Get Support

You are always encouraged and welcome to ask any questions or report any issues you found to us via [Silicon Labs Community](https://community.silabs.com/s/topic/0TO1M000000qHc6WAE/wisun).
