/***************************************************************************/ /**
 * @file
 * @brief SystemView UART recorder
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
 *
 ******************************************************************************/

#ifndef SL_UART_RECORDER_H
#define SL_UART_RECORDER_H

#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif

#include "sl_iostream.h"
#include "sl_iostream_uart.h"

#ifdef __cplusplus
extern "C"
{
#endif

/***************************************************************************//**
 * @addtogroup uart_recorder SystemView UART Recorder
 *
 * @brief SystemView UART Recorder
 * @details
 * ## Overview
 *
 *   Segger SystemView allows to record events using a UART instead of the
 *   regular RTT. Using RTT is recommended as it is faster and more efficient.
 *   However, it is not possible to use RTT to log events in an application that
 *   sleeps to EM2 or EM3 energy mode. The SystemView UART recorder module can
 *   be used in applications that have to sleep to low energy modes to log
 *   events. Refer to SystemView user manual to know how to configure the
 *   SystemView host application to use UART mode.
 *
 * ## How it works
 *
 *   Establishing a connection with SystemView host application is composed
 *   of 3 phases:
 *
 *   1) Waiting for the hello message. The SystemView host application emits a
 *      "hello" message once recording is started. The moment when the hello
 *      message is received is unpredictable. For that reason, when
 *      SL_SYSTEMVIEW_UART_RECORDER_PREVENT_SLEEP_BEFORE_CONNECTION is enabled,
 *      a requirement on EM1 is added at initialization so the UART is able to
 *      receive all the time.
 *
 *   2) Hello message is received. After hello message is received, the device
 *      replies with its own hello message. From that point, logs can be
 *      transmitted. However, at the beginning of the recording, the SystemView
 *      host app will emit several commands to retrieve information on the
 *      target. So the device must remain able to receive message from the UART.
 *      That is why, when the configuration
 *      SL_SYSTEMVIEW_UART_RECORDER_PREVENT_SLEEP_BEFORE_CONNECTION is enabled,
 *      the requirement on EM1 is not removed right away. Instead, the
 *      requirement is removed after a delay defined by
 *      SL_SYSTEMVIEW_UART_RECORDER_DELAY_BEFORE_EM1_REMOVE.
 *
 *   3) If SL_SYSTEMVIEW_UART_RECORDER_PREVENT_SLEEP_BEFORE_CONNECTION is
 *      enabled, the EM1 requirement is removed after the delay
 *      SL_SYSTEMVIEW_UART_RECORDER_DELAY_BEFORE_EM1_REMOVE. Form that point,
 *      unless the application puts a requirement on EM1, the communication
 *      becomes unidirectional. The transmission of the logs to the host
 *      SystemView application will only occur when the system is woken up (in
 *      EM0). Any message logged from an IRQ while the system is sleeping will
 *      be transmitted at next wakeup.
 *
 *   Once the connection is established and the requirement on EM1 is removed,
 *   stopping the SystemView recording is likely to fail, unless the device
 *   happens to be in EM0 when the stop message is transmitted. Starting a new
 *   recording will likely require to restart the device application.
 *
 * ## How to use
 *
 *   By adding this module to your project, it will automatically be
 *   initialized. The function sl_uart_recorder_process_action() has to be
 *   called from the main loop in baremetal applications.
 *   The uart recorder uses the IOStream module as the UART driver. The stream
 *   instance name to use can be specified with the configuration
 *   SL_SYSTEMVIEW_UART_RECORDER_IOSTREAM_INSTANCE_NAME when using Simplicity
 *   Studio's project configuration tool. Otherwise, the stream handle must be
 *   specified when calling the function sl_uart_recorder_init().
 *
 * @{
 ******************************************************************************/

// -----------------------------------------------------------------------------
// Prototypes

/***************************************************************************//**
 * Initialize UART recorder module.
 *
 * @param   stream  UART stream to use.
 *
 * @return  Status code.
 ******************************************************************************/
sl_status_t sl_uart_recorder_init(sl_iostream_uart_t *stream);

/***************************************************************************/ /**
 *  The baremetal process action function.
 ******************************************************************************/
#if !defined(SL_CATALOG_KERNEL_PRESENT)
/***************************************************************************//**
 * SystemView UART recorder process action handler.
 ******************************************************************************/
void sl_uart_recorder_process_action(void);
#endif

#if !defined(SL_CATALOG_KERNEL_PRESENT)
/***************************************************************************//**
 * Determines if UART recorder is ok to enter sleep.
 *
 * @return True if nothing has been received on the stream, false otherwise.
 ******************************************************************************/
bool sl_uart_recorder_is_ok_to_sleep(void);
#endif

#ifdef __cplusplus
}
#endif

#endif // SL_UART_RECORDER_H
