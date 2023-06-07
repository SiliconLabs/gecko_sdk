/***************************************************************************//**
 * @file
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "em_device.h"
#include "em_chip.h"

#include "cslib_hwconfig.h"
#include "cslib_config.h"

#include "cslib.h"
#include "hardware_routines.h"
#include "low_power_config.h"

// Drivers
#include "em_acmp.h"
#include "em_assert.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "em_lesense.h"
#include "em_rtc.h"

uint8_t timerTick;

void CAPSENSE_Init(void);

/**************************************************************************//**
 * Configure sensor for sleep mode
 *
 * Configures sensor peripheral(s) for sleep mode scanning
 *
 *****************************************************************************/
void CSLIB_configureSensorForSleepModeCB(void)
{
  CAPSENSE_Init();
}

/**************************************************************************//**
 * Ready system for entrance into sleep mode
 *
 * Function configures hardware for optimal low power in sleep mode
 *
 *****************************************************************************/
void readyRegistersForSleep(void)
{
  // stub function called in sleep mode state machine
}

/**************************************************************************//**
 * Restore registers from sleep
 *
 * Re-enable and get system ready for active mode
 *
 *****************************************************************************/
void restoreRegistersFromSleep(void)
{
  // stub function called in sleep mode state machine
}

/**************************************************************************//**
 * Configure to sleep mode
 *
 * Re-enable and get system ready for active mode
 *
 *****************************************************************************/
void CSLIB_enterLowPowerStateCB(void)
{
  EMU_EnterEM2(true);
}

/**************************************************************************//**
 * Configure timer for active mode
 *
 * This is a top-level call to configure the timer to active mode, one of the
 * two defined modes of operation in the system.  This instance of the function
 * configures the SmaRTClock to the frequency defined in cslib_config.h.
 *
 *****************************************************************************/
void CSLIB_configureTimerForActiveModeCB(void)
{
#if (defined(_EFM32_PEARL_FAMILY))
  rtccSetup(1000 / DEF_ACTIVE_MODE_PERIOD);
#else
  rtcSetup(1000 / DEF_ACTIVE_MODE_PERIOD);
#endif
}

/**************************************************************************//**
 * Configure timer for sleep mode
 *
 * This is a top-level call to configure the timer to sleep mode, one of the
 * two defined modes of operation in the system.  This instance of the function
 * configures the SmaRTClock to the frequency defined in cslib_config.h.
 *
 *****************************************************************************/
void CSLIB_configureTimerForSleepModeCB(void)
{
#if (defined(_EFM32_PEARL_FAMILY))
  rtccSetup(1000 / DEF_SLEEP_MODE_PERIOD);
#else
  rtcSetup(1000 / DEF_SLEEP_MODE_PERIOD);
#endif
}

/**************************************************************************//**
 * Check timer
 *
 *****************************************************************************/
void CSLIB_checkTimerCB(void)
{
  // Stub function because EFM32 code sets flag inside RTC ISR
}
