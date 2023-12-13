/***************************************************************************//**
 * @file
 * @brief Header file for hooks required by the power manager
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

#ifndef __SL_CONNECT_POWER_MANAGER_H__
#define __SL_CONNECT_POWER_MANAGER_H__

bool sl_connect_is_ok_to_sleep(void);
sl_power_manager_on_isr_exit_t sl_connect_sleep_on_isr_exit(void);

#endif
