/***************************************************************************//**
 * @file
 * @brief Simple Communication Interface - FreeRTOS configuration file
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

#ifndef SL_SIMPLE_COM_FREERTOS_CONFIG_H
#define SL_SIMPLE_COM_FREERTOS_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <o SL_SIMPLE_COM_TASK_PRIO> Priority of the Simple COM OS task
// <i> Default: 4
// <i> Priority of the Simple COM OS task
#define SL_SIMPLE_COM_TASK_PRIO         4

// <o SL_SIMPLE_COM_TASK_STACK> Stack size of the Simple COM OS task in bytes
// <i> Default: 1024
// <i> Stack size of the Simple COM OS task (bytes)
#define SL_SIMPLE_COM_TASK_STACK        1024

// <s SL_SIMPLE_COM_TASK_NAME> Name of the Simple COM OS task
// <i> Default: "simple_com_task"
// <i> Name of the Simple COM OS task
#define SL_SIMPLE_COM_TASK_NAME         "simple_com_task"

// <<< end of configuration section >>>

#endif // SL_SIMPLE_COM_FREERTOS_CONFIG_H
