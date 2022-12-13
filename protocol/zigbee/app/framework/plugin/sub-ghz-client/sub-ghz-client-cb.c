/***************************************************************************//**
 * @file
 * @brief
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "af.h"

/** @brief Sub-GHz Cluster Suspend ZCL Messages
 *
 * 'Suspend ZCL Messages' is a server command, sent to request the client
 * to temporarily suspend sending any ZCL messages to reduce the duty cycle.
 *
 * The clients's default action is to suspend ZCL messages for the requested period.
 *
 * @param period  suspend period in minutes
 *
 * @return  true to indicate the callback has been handled by the application,
 *          false to keep the default behaviour
 */
WEAK(bool emberAfPluginSubGhzSuspendZclMessagesCallback(uint8_t period))
{
  (void) period;        // unreferenced parameter

  return false;         // let the framework do its job
}
