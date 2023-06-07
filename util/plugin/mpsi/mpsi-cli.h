/**************************************************************************//**
 * Copyright 2017 Silicon Laboratories, Inc.
 *
 *****************************************************************************/

#ifndef __MPSI_CLI_H__
#define __MPSI_CLI_H__

#if defined (EMBER_STACK_ZIGBEE)
#define sli_mpsi_cli_entry_action(command, function, paramList, help) \
  emberCommandEntryAction(command, function, paramList, help)

#define sli_mpsi_cli_entry_terminator() \
  emberCommandEntryTerminator()

#define sli_mpsi_cli_signed_command_argument(arg) \
  emberSignedCommandArgument(arg)

#define sli_mpsi_cli_unsigned_command_argument(arg) \
  emberUnsignedCommandArgument(arg)

#define sli_mpsi_cli_copy_string_argument(arg, buffer, length, leftPad) \
  emberCopyStringArgument(arg, buffer, length, leftPad)

#define CLI_HANDLER_PARAM_LIST void

#elif defined (EMBER_STACK_BLE)
#define sli_mpsi_cli_entry_action(command, function, paramList, help) \
  COMMAND_ENTRY(command, paramList, function, help)

#define sli_mpsi_cli_entry_terminator() \
  COMMAND_SEPARATOR("")

#define sli_mpsi_cli_signed_command_argument(arg) \
  ciGetSigned(buf[arg + 1])

#define sli_mpsi_cli_unsigned_command_argument(arg) \
  ciGetUnsigned(buf[arg + 1])

uint8_t sli_mpsi_cli_copy_string_argument(uint8_t arg,
                                          uint8_t *buffer,
                                          uint8_t length,
                                          bool    leftPad)
{
  MEMMOVE(buffer, buf[arg], length);
  (void)leftPad;
  return length;
}

#define CLI_HANDLER_PARAM_LIST int abc, char **buf

#else
#error "MPSI CLI: Unsupported stack!"
#endif

#define MPSI_COMMAND_LIST                                          \
  sli_mpsi_cli_entry_action("receive-message",                     \
                            sli_mpsi_cli_receive_message, "uvub",  \
                            "Simulate receiving an MPSI message"), \
  sli_mpsi_cli_entry_action("send-message",                        \
                            sli_mpsi_cli_send_message, "uvub",     \
                            "Simulate sending an MPSI message"),   \
  sli_mpsi_cli_entry_terminator()

void sli_mpsi_cli_receive_message(CLI_HANDLER_PARAM_LIST);
void sli_mpsi_cli_send_message(CLI_HANDLER_PARAM_LIST);

#endif // __MPSI_CLI_H__
