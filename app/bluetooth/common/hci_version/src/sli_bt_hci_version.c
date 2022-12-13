/***************************************************************************//**
 * @file
 * @brief Bluetooth Version Specific Command
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "sli_bt_hci_version.h"
#include "sl_bt_hci_version_config.h"
#include "sl_btctrl_hci_handler.h"

static const struct sli_bt_hci_version_response sli_bt_hci_version = SL_BT_HCI_VERSION_RESPONSE;

//Status codes defined in Bluetooth spec
#define BT_OK             0 //Command was succesful
#define BT_ERR_INVALID 0x12 //Used as a generic error

sl_btctrl_command_handler_t sli_bt_hci_command_handler;
bool sli_bt_hci_handle_version_command(struct sl_btctrl_hci_message * hcimsg);

void sli_bt_hci_init_version(void)
{
  sl_btctrl_hci_register_handler(&sli_bt_hci_command_handler, &sli_bt_hci_handle_version_command);
}

bool sli_bt_hci_handle_version_command(struct sl_btctrl_hci_message * hcimsg)
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
    case SL_BT_HCI_GET_VERSION_OPCODE:
      if (length == 0) {
        sl_btctrl_hci_message_set_response(hcimsg, BT_OK, (uint8_t*) &sli_bt_hci_version, sizeof(sli_bt_hci_version));
      } else {
        //Parameters was passed to command -> error
        sl_btctrl_hci_message_set_response(hcimsg, BT_ERR_INVALID, NULL, 0);
      }
      return true;
  }
  return false;
}
