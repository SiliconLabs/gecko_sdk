/***************************************************************************//**
 * @file
 * @brief App Status commandline interface handler
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "sl_string.h"
#include "sl_cli.h"
#include "sl_wisun_cli_core.h"
#include "sl_wisun_app_status.h"
#include "sl_wisun_trace_util.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------
///  Size of the IPv6 string
#define IPV6_STRING_SIZE                (40U)

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------
///  Buffer to store the IPv6 string
static char ip_buff[IPV6_STRING_SIZE] = { 0 };

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------
/**************************************************************************//**
 * @brief App status get remote address and port
 * @details CLI function
 * @param[in] arguments Arguments
 *****************************************************************************/
void sl_app_status_cli_get_address(sl_cli_command_arg_t *arguments)
{
  (void)arguments;
  app_wisun_cli_mutex_lock();
  const sockaddr_in6_t* address = sl_wisun_app_status_get_remote_address();
  inet_ntop(AF_INET6, &(address->sin6_addr), ip_buff, sizeof(ip_buff));
  printf("remote_address=%s\n", ip_buff);
  printf("remote_port=%d\n", address->sin6_port);
  memset(ip_buff, 0, sizeof(ip_buff));
  app_wisun_cli_mutex_unlock();
}

/**************************************************************************//**
 * @brief App status get schedule time in ms
 * @details CLI function
 * @param[in] arguments Arguments
 *****************************************************************************/
void sl_app_status_cli_get_schedule(sl_cli_command_arg_t *arguments)
{
  (void)arguments;
  app_wisun_cli_mutex_lock();
  printf("schedule_time_m=%ld\n", sl_wisun_app_status_get_schedule_time_ms());
  app_wisun_cli_mutex_unlock();
}

/**************************************************************************//**
 * @brief App status set schedule time in ms
 * @details CLI function
 * @param[in] arguments Arguments
 *****************************************************************************/
void sl_app_status_cli_set_schedule(sl_cli_command_arg_t *arguments)
{
  uint32_t schedule_time_ms = 0;
  app_wisun_cli_mutex_lock();
  schedule_time_ms = sl_cli_get_argument_uint32(arguments, 0U);
  sl_wisun_app_status_set_schedule_time_ms(schedule_time_ms);
  printf("[Settings saved]\r\n");
  app_wisun_cli_mutex_unlock();
}

/**************************************************************************//**
 * @brief App status set remote address and port
 * @details CLI function
 * @param[in] arguments Arguments
 *****************************************************************************/
void sl_app_status_cli_set_address(sl_cli_command_arg_t *arguments)
{
  uint16_t port = 0;
  char *address = NULL;
  app_wisun_cli_mutex_lock();
  address = sl_cli_get_argument_string(arguments, 0U);
  port = sl_cli_get_argument_uint16(arguments, 1U);
  if (sl_wisun_app_status_set_remote_address(address, port) != 0U) {
    printf("[Failed: invalid remote address parameter]\r\n");
  } else {
    printf("[Settings saved]\r\n");
  }
  app_wisun_cli_mutex_unlock();
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------
