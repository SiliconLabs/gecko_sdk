/***************************************************************************/ /**
 * @file
 * @brief UART recorder Init API helper implementation.
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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
 ******************************************************************************/

#include <stddef.h>

#include "em_core.h"
#include "sl_uart_recorder.h"
#include "sl_uart_recorder_config.h"
#include "sl_status.h"
#include "sl_iostream.h"
#include "sl_iostream_uart.h"

#ifdef SL_CATALOG_IOSTREAM_USART_PRESENT
#include "sl_iostream_init_usart_instances.h"
#endif

#ifdef SL_CATALOG_IOSTREAM_LEUART_PRESENT
#include "sl_iostream_init_leuart_instances.h"
#endif

#ifdef SL_CATALOG_IOSTREAM_EUSART_PRESENT
#include "sl_iostream_init_eusart_instances.h"
#endif

/*******************************************************************************
 *********************************   DEFINES   *********************************
 ******************************************************************************/

#define CREATE_STREAM_INSTANCE_FROM_NAME(name)  sl_iostream_uart_##name##_handle
#define BUILD_STREAM_INSTANCE_HANDLE_NAME(name)  CREATE_STREAM_INSTANCE_FROM_NAME(name)

/***************************************************************************//**
 * Initialize UART recorder module.
 *
 * @return  Status code.
 ******************************************************************************/
sl_status_t sl_uart_recorder_init_helper(void)
{
  sl_iostream_uart_t *stream = BUILD_STREAM_INSTANCE_HANDLE_NAME(SL_SYSTEMVIEW_UART_RECORDER_IOSTREAM_INSTANCE_NAME);

  return sl_uart_recorder_init(stream);
}
