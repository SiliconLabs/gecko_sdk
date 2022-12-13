/***************************************************************************//**
 * @brief Sample watchdog refresh event component configuration header.
 ********************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

// <<< Use Configuration Wizard in Context Menu >>>

// <h>Zigbee Watchdog reset component configuration

// <e SL_ZIGBEE_WATCHDOG_PERIODIC_REFRESH_ENABLE> Enable periodic watchdog refresh
// <i> Default: TRUE
// <i> This allows for enabling or disabling periodic watchdog refresh
#define SL_ZIGBEE_WATCHDOG_PERIODIC_REFRESH_ENABLE   1

// <o SL_ZIGBEE_WATCHDOG_REFRESH_DURATION_MS> Watchdog refresh duration <50-5000>
// <i> Default: 1000
// <i> Defines the periodic interval at which the watchdog timer is reset in the application
#define SL_ZIGBEE_WATCHDOG_REFRESH_DURATION_MS   1000

// </e>
// </h>

// <<< end of configuration section >>>
