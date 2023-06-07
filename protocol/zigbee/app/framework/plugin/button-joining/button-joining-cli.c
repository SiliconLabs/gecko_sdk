/***************************************************************************//**
 * @file
 * @brief CLI commands for forming/joining using the hardware buttons.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include "app/framework/include/af.h"
#include "button-joining.h"

// TODO: temporary defines, these are defined in the app-builder generated
// board header.
#define BUTTON0         0
#define BUTTON1         1

void emberAfPluginButtonJoiningButton0Command(sl_cli_command_arg_t *arguments)
{
  emberAfPluginButtonJoiningPressButton(BUTTON0);
}

void emberAfPluginButtonJoiningButton1Command(sl_cli_command_arg_t *arguments)
{
  emberAfPluginButtonJoiningPressButton(BUTTON1);
}
