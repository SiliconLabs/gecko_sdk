/**************************************************************************//**
 * Copyright 2017 Silicon Laboratories, Inc.
 *
 *****************************************************************************/

#ifndef __SLOT_MANAGER_CLI_H__
#define __SLOT_MANAGER_CLI_H__

#include "sl_cli.h"

#define MAX_FLASH_READ_BYTES    100

void sli_slot_manager_cli_bootload_slot(sl_cli_command_arg_t *arguments);
void sli_slot_manager_cli_erase_slot(sl_cli_command_arg_t *arguments);
void sli_slot_manager_cli_print_external_flash_info(sl_cli_command_arg_t *arguments);
void sli_slot_manager_cli_read_ext_flash(sl_cli_command_arg_t *arguments);
void sli_slot_manager_cli_print_slots_info(sl_cli_command_arg_t *arguments);

#endif // __SLOT_MANAGER_CLI_H__
