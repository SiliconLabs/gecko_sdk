/***************************************************************************//**
 * @file
 * @brief MX25 flash shutdown
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

#include "em_cmu.h"
#include "em_usart.h"
#include "em_gpio.h"
#include "sl_udelay.h"
#include "sl_mx25_flash_shutdown.h"

// Fallback to baudrate of 8 MHz if not defined for backwards compatibility
#ifndef SL_MX25_FLASH_SHUTDOWN_BAUDRATE
#define SL_MX25_FLASH_SHUTDOWN_BAUDRATE   8000000
#endif

// Define usart clock
#ifndef SL_MX25_FLASH_SHUTDOWN_CLK
#define MERGE(x, y)   x##y
#define USART_CLOCK(n) MERGE(cmuClock_USART, n)
#define SL_MX25_FLASH_SHUTDOWN_CLK USART_CLOCK(SL_MX25_FLASH_SHUTDOWN_PERIPHERAL_NO)
#endif

#ifdef SL_MX25_FLASH_SHUTDOWN_PERIPHERAL
static void cs_low(void)
{
  GPIO_PinOutClear(SL_MX25_FLASH_SHUTDOWN_CS_PORT, SL_MX25_FLASH_SHUTDOWN_CS_PIN);
}

static void cs_high(void)
{
  GPIO_PinOutSet(SL_MX25_FLASH_SHUTDOWN_CS_PORT, SL_MX25_FLASH_SHUTDOWN_CS_PIN);
}
#endif

/***************************************************************************//**
 *    Puts the MX25 into deep power down mode.
 ******************************************************************************/
void sl_mx25_flash_shutdown(void)
{
#ifdef SL_MX25_FLASH_SHUTDOWN_PERIPHERAL
  // Init flash
  USART_InitSync_TypeDef init = USART_INITSYNC_DEFAULT;

  CMU_ClockEnable(cmuClock_GPIO, true);
  CMU_ClockEnable(SL_MX25_FLASH_SHUTDOWN_CLK, true);

  init.msbf     = true;
  init.baudrate = SL_MX25_FLASH_SHUTDOWN_BAUDRATE;

  USART_InitSync(SL_MX25_FLASH_SHUTDOWN_PERIPHERAL, &init);

  // IO config
  GPIO_PinModeSet(SL_MX25_FLASH_SHUTDOWN_TX_PORT, SL_MX25_FLASH_SHUTDOWN_TX_PIN, gpioModePushPull, 1);
  GPIO_PinModeSet(SL_MX25_FLASH_SHUTDOWN_RX_PORT, SL_MX25_FLASH_SHUTDOWN_RX_PIN, gpioModeInput, 0);
  GPIO_PinModeSet(SL_MX25_FLASH_SHUTDOWN_CLK_PORT, SL_MX25_FLASH_SHUTDOWN_CLK_PIN, gpioModePushPull, 1);
  GPIO_PinModeSet(SL_MX25_FLASH_SHUTDOWN_CS_PORT, SL_MX25_FLASH_SHUTDOWN_CS_PIN, gpioModePushPull, 1);

#ifdef _GPIO_USART_ROUTEEN_MASK
  GPIO->USARTROUTE[SL_MX25_FLASH_SHUTDOWN_PERIPHERAL_NO].CLKROUTE  = ((SL_MX25_FLASH_SHUTDOWN_CLK_PORT << _GPIO_USART_CLKROUTE_PORT_SHIFT)
                                                                      | (SL_MX25_FLASH_SHUTDOWN_CLK_PIN  << _GPIO_USART_CLKROUTE_PIN_SHIFT));
  GPIO->USARTROUTE[SL_MX25_FLASH_SHUTDOWN_PERIPHERAL_NO].RXROUTE   = ((SL_MX25_FLASH_SHUTDOWN_RX_PORT << _GPIO_USART_RXROUTE_PORT_SHIFT)
                                                                      | (SL_MX25_FLASH_SHUTDOWN_RX_PIN  << _GPIO_USART_RXROUTE_PIN_SHIFT));
  GPIO->USARTROUTE[SL_MX25_FLASH_SHUTDOWN_PERIPHERAL_NO].TXROUTE   = ((SL_MX25_FLASH_SHUTDOWN_TX_PORT << _GPIO_USART_TXROUTE_PORT_SHIFT)
                                                                      | (SL_MX25_FLASH_SHUTDOWN_TX_PIN  << _GPIO_USART_TXROUTE_PIN_SHIFT));
  GPIO->USARTROUTE[SL_MX25_FLASH_SHUTDOWN_PERIPHERAL_NO].ROUTEEN   = (GPIO_USART_ROUTEEN_RXPEN
                                                                      | GPIO_USART_ROUTEEN_TXPEN
                                                                      | GPIO_USART_ROUTEEN_CLKPEN);
#else
  SL_MX25_FLASH_SHUTDOWN_PERIPHERAL->ROUTELOC0 = ((SL_MX25_FLASH_SHUTDOWN_RX_LOC << _USART_ROUTELOC0_RXLOC_SHIFT)
                                                  | (SL_MX25_FLASH_SHUTDOWN_TX_LOC << _USART_ROUTELOC0_TXLOC_SHIFT)
                                                  | (SL_MX25_FLASH_SHUTDOWN_CLK_LOC << _USART_ROUTELOC0_CLKLOC_SHIFT));
  SL_MX25_FLASH_SHUTDOWN_PERIPHERAL->ROUTEPEN  = (USART_ROUTEPEN_RXPEN
                                                  | USART_ROUTEPEN_TXPEN
                                                  | USART_ROUTEPEN_CLKPEN);
#endif

  // Wait for flash warm-up
  sl_udelay_wait(800);               // wait for tVSL=800us

  // Wake up flash in case the device is in deep power down mode already.
  cs_low();
  sl_udelay_wait(20);                  // wait for tCRDP=20us
  cs_high();
  sl_udelay_wait(35);                  // wait for tRDP=35us

  // Chip select go low to start a flash command
  cs_low();

  // Deep Power Down Mode command (0xB9)
  USART_SpiTransfer(SL_MX25_FLASH_SHUTDOWN_PERIPHERAL, 0xB9);

  // Chip select go high to end a flash command
  cs_high();

  // Deinit flash
  GPIO_PinModeSet(SL_MX25_FLASH_SHUTDOWN_TX_PORT, SL_MX25_FLASH_SHUTDOWN_TX_PIN, gpioModeDisabled, 0);
  GPIO_PinModeSet(SL_MX25_FLASH_SHUTDOWN_RX_PORT, SL_MX25_FLASH_SHUTDOWN_RX_PIN, gpioModeDisabled, 0);
  GPIO_PinModeSet(SL_MX25_FLASH_SHUTDOWN_CLK_PORT, SL_MX25_FLASH_SHUTDOWN_CLK_PIN, gpioModeDisabled, 1);
  GPIO_PinModeSet(SL_MX25_FLASH_SHUTDOWN_CS_PORT, SL_MX25_FLASH_SHUTDOWN_CS_PIN, gpioModeDisabled, 1);

  USART_Reset(SL_MX25_FLASH_SHUTDOWN_PERIPHERAL);

#ifdef _GPIO_USART_ROUTEEN_MASK
  GPIO->USARTROUTE[SL_MX25_FLASH_SHUTDOWN_PERIPHERAL_NO].CLKROUTE = _GPIO_USART_CLKROUTE_RESETVALUE;
  GPIO->USARTROUTE[SL_MX25_FLASH_SHUTDOWN_PERIPHERAL_NO].RXROUTE  = _GPIO_USART_RXROUTE_RESETVALUE;
  GPIO->USARTROUTE[SL_MX25_FLASH_SHUTDOWN_PERIPHERAL_NO].TXROUTE  = _GPIO_USART_TXROUTE_RESETVALUE;
  GPIO->USARTROUTE[SL_MX25_FLASH_SHUTDOWN_PERIPHERAL_NO].ROUTEEN  = _GPIO_USART_ROUTEEN_RESETVALUE;
#else
  SL_MX25_FLASH_SHUTDOWN_PERIPHERAL->ROUTELOC0 = _USART_ROUTELOC0_RESETVALUE;
  SL_MX25_FLASH_SHUTDOWN_PERIPHERAL->ROUTEPEN  = _USART_ROUTEPEN_RESETVALUE;
#endif

  CMU_ClockEnable(SL_MX25_FLASH_SHUTDOWN_CLK, false);
#endif
}
