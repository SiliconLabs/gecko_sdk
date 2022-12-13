/***************************************************************************//**
 * @file
 * @brief Simple Communication Interface - FreeRTOS adaptation
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
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "semphr.h"
#include "em_common.h"
#include "app_assert.h"
#include "sl_simple_com.h"
#include "sl_simple_com_freertos_config.h"

/// Task stack definition and identifier
static StackType_t  simple_com_task_stack[SL_SIMPLE_COM_TASK_STACK] = { 0 };
static StaticTask_t simple_com_task_buffer;
static TaskHandle_t simple_com_task_handle;

/// Binary semaphore to run the task only if it's really necessary
static SemaphoreHandle_t simple_com_semaphore;

/// Task function-prototype
static void simple_com_task(void *p_arg);

/**************************************************************************//**
 * Function to trigger the OS task to proceed
 *****************************************************************************/
void sl_simple_com_os_task_proceed(void)
{
  (void)xSemaphoreGive(simple_com_semaphore);
}

/**************************************************************************//**
 * OS initialization function
 *****************************************************************************/
void sl_simple_com_os_task_init(void)
{
  simple_com_semaphore = xSemaphoreCreateCounting(UINT8_MAX, 0u);
  app_assert(NULL != simple_com_semaphore, "Failed to create Simple COM sempahore!");

  simple_com_task_handle =
    xTaskCreateStatic(simple_com_task,
                      SL_SIMPLE_COM_TASK_NAME,
                      SL_SIMPLE_COM_TASK_STACK,
                      NULL,
                      SL_SIMPLE_COM_TASK_PRIO,
                      simple_com_task_stack,
                      &simple_com_task_buffer);
  app_assert(NULL != simple_com_task_handle,
             "Simple COM task creation failed!");
}

/**************************************************************************//**
 * Simple COM OS task
 *
 * @param[in] p_arg FreeRTOS task arguments
 *****************************************************************************/
static void simple_com_task(void *p_arg)
{
  (void)p_arg;
  sl_simple_com_os_task_proceed();

  while (1) {
    if (xSemaphoreTake(simple_com_semaphore, portMAX_DELAY) == pdTRUE) {
      sl_simple_com_step();
    }
  }
}
