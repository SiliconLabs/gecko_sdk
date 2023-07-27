#ifndef SL_BT_HCI_COEX_CONFIG_H
#define SL_BT_HCI_COEX_CONFIG_H

/***********************************************************************************************//**
 * @addtogroup hci_coex
 * @{
 **************************************************************************************************/

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Bluetooth Coexistence Vendor Specific API Configuration

// <o SL_BT_HCI_COEX_SET_OPTIONS_OPCODE> Opcode for Coex Set Options Command <f.h>
// <d> 0xff00
// <i> Defines opcode that is used to identify Coex Set Options Command,
// <i> this must be chosen that it doesn't overlap with any other vendor specific command
// <i> Coex Set Options is a thin wrapper over sl_bt_set_coex_options command in RAIL Bluetooth Coexistence Plugin
// <i> Pass sli_bt_hci_coex_set_options_t structure as input
#define SL_BT_HCI_COEX_SET_OPTIONS_OPCODE     0xff00

// <o SL_BT_HCI_COEX_SET_PARAMETERS_OPCODE> Opcode for Coex Set Parameters Command <f.h>
// <d> 0xff01
// <i> Defines opcode that is used to identify Coex Set Parameters Command,
// <i> this must be chosen that it doesn't overlap with any other vendor specific command
// <i> Coex Set Parameters is a thin wrapper over sl_bt_coex_set_config
// <i> Pass sl_bt_ll_coex_config_t structure as input
// <i> Command is always succesful
#define SL_BT_HCI_COEX_SET_PARAMETERS_OPCODE     0xff01

// <o SL_BT_HCI_COEX_GET_PARAMETERS_OPCODE> Opcode for Coex Get Parameters Command <f.h>
// <d> 0xff02
// <i> Defines opcode that is used to identify Coex Get Parameters Command,
// <i> this must be chosen that it doesn't overlap with any other vendor specific command
// <i> Coex Get Parameters is a thin wrapper over sl_bt_coex_get_config
// <i> Command Returns sl_bt_ll_coex_config_t structure as output
// <i> Command is always succesful
#define SL_BT_HCI_COEX_GET_PARAMETERS_OPCODE     0xff02

// <o SL_BT_HCI_COEX_SET_DIRECTIONAL_PRIORITY_PULSE_OPCODE> Opcode for Coex Set Directional Priority Pulse Command <f.h>
// <d> 0xff03
// <i> Defines opcode that is used to identify Coex Set Directional Priority Pulse Command,
// <i> this must be chosen that it doesn't overlap with any other vendor specific command
// <i> Coex Set Directional Priority Pulse is a thin wrapper over COEX_HAL_SetDpPulseWidth
// <i> Input parameter is single uint8_t that defines pulse width in useconds
// <i> Output parameters is SL_STATUS, command is successful if status is SL_STATUS_SUCCESS
#define SL_BT_HCI_COEX_SET_DIRECTIONAL_PRIORITY_PULSE_OPCODE     0xff03

// <o SL_BT_HCI_COEX_GET_COUNTERS_OPCODE> Opcode for Coex Get Counters Command <f.h>
// <d> 0xff04
// <i> Defines opcode that is used to identify Coex Get Counters Command,
// <i> this must be chosen that it doesn't overlap with any other vendor specific command
// <i> Coex Get Counters is a thin wrapper over sl_bt_get_coex_counters command in RAIL Bluetooth Coexistence Plugin
// <i> Command takes no parameters
// <i> Command outputs counters array from the coexistence plugin
#define SL_BT_HCI_COEX_GET_COUNTERS_OPCODE     0xff04

// </h> Bluetooth Coexistence Vendor Specific API Configuration

// <<< end of configuration section >>>

/** @} (end addtogroup hci_coex) */
#endif // SL_BT_HCI_COEX_CONFIG_H
