#include "sli_bt_hci_coex.h"
#include "sl_bt_hci_coex_config.h"
#include "sl_btctrl_hci_handler.h"
#include "coexistence-ble.h"
#include "coexistence-hal.h"

//Status codes defined in Bluetooth spec
#define BT_OK             0 //Command was succesful
#define BT_ERR_INVALID 0x12 //Used as a generic error

sl_btctrl_command_handler_t sli_bt_hci_command_handler;
bool sli_bt_hci_handle_coex_command(struct sl_btctrl_hci_message * hcimsg);

void sli_bt_hci_init_coex(void)
{
  sl_btctrl_hci_register_handler(&sli_bt_hci_command_handler, &sli_bt_hci_handle_coex_command);
}

bool sli_bt_hci_handle_coex_command(struct sl_btctrl_hci_message * hcimsg)
{
  uint16_t opcode;
  if (sl_btctrl_hci_message_get_opcode(hcimsg, &opcode) != SL_STATUS_OK) {
    return false;
  }
  size_t length;
  if (sl_btctrl_hci_message_get_length(hcimsg, &length) != SL_STATUS_OK) {
    return false;
  }

  switch (opcode) {
    case SL_BT_HCI_COEX_SET_OPTIONS_OPCODE:
      if (length == sizeof(sli_bt_hci_coex_set_options_t)) {
        sli_bt_hci_coex_set_options_t options;
        if (sl_btctrl_hci_message_get_parameters(hcimsg, (uint8_t*)&options, sizeof(options)) == SL_STATUS_OK) {
          bool rv = sl_bt_set_coex_options(options.mask, options.options);
          sl_btctrl_hci_message_set_response(hcimsg, rv ? BT_OK : BT_ERR_INVALID, NULL, 0);
          return true;
        }
      }
      //Invalid parameters or some other error
      sl_btctrl_hci_message_set_response(hcimsg, BT_ERR_INVALID, NULL, 0);
      return true;
    case SL_BT_HCI_COEX_SET_PARAMETERS_OPCODE:
      if (length == sizeof(sl_bt_ll_coex_config_t)) {
        sl_bt_ll_coex_config_t params;
        if (sl_btctrl_hci_message_get_parameters(hcimsg, (uint8_t*)&params, sizeof(params)) == SL_STATUS_OK) {
          sl_bt_coex_set_config(&params);
          sl_btctrl_hci_message_set_response(hcimsg, BT_OK, NULL, 0);
          return true;
        }
      }
      //Invalid parameters or some other error
      sl_btctrl_hci_message_set_response(hcimsg, BT_ERR_INVALID, NULL, 0);
      return true;
#if 0 //Depends on BG-12346
    case SL_BT_HCI_COEX_GET_PARAMETERS_OPCODE:
      if (length == 0) {
        sl_bt_ll_coex_config_t params;
        sl_bt_coex_get_config(&params);
        sl_btctrl_hci_message_set_response(hcimsg, BT_OK, &params, sizeof(params));
        return true;
      }
      //Invalid parameters or some other error
      sl_btctrl_hci_message_set_response(hcimsg, BT_ERR_INVALID, NULL, 0);
      return true;
#endif
    case SL_BT_HCI_COEX_SET_DIRECTIONAL_PRIORITY_PULSE_OPCODE:
      if (length == sizeof(uint8_t)) {
        uint8_t params;
        if (sl_btctrl_hci_message_get_parameters(hcimsg, &params, sizeof(params)) == SL_STATUS_OK) {
          sl_status_t rv = COEX_HAL_SetDpPulseWidth(params);
          sl_btctrl_hci_message_set_response(hcimsg, rv == SL_STATUS_OK ? BT_OK : BT_ERR_INVALID, (uint8_t*) &rv, sizeof(rv));
          return true;
        }
      }
      //Invalid parameters or some other error
      sl_btctrl_hci_message_set_response(hcimsg, BT_ERR_INVALID, NULL, 0);
      return true;
    case SL_BT_HCI_COEX_GET_COUNTERS_OPCODE:
      if (length == 0) {
        uint8_t size;
        const void *ptr;
        bool ret = sl_bt_get_coex_counters(&ptr, &size);

        sl_btctrl_hci_message_set_response(hcimsg, ret ? BT_OK : BT_ERR_INVALID, ptr, size);
        return true;
      }
      //Invalid parameters or some other error
      sl_btctrl_hci_message_set_response(hcimsg, BT_ERR_INVALID, NULL, 0);
      return true;
  }
  return false;
}
