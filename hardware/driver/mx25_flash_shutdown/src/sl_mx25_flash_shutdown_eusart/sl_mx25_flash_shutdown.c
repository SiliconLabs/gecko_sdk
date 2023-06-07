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
#include "em_eusart.h"
#include "em_gpio.h"
#include "sl_udelay.h"
#include "sl_mx25_flash_shutdown.h"
#include "stddef.h"

// Fallback to baudrate of 8 MHz if not defined for backwards compatibility
#ifndef SL_MX25_FLASH_SHUTDOWN_BAUDRATE
#define SL_MX25_FLASH_SHUTDOWN_BAUDRATE   7500000
#endif

// Define usart clock
#ifndef SL_MX25_FLASH_SHUTDOWN_SCLK
#define MERGE(x, y)   x##y
#define EUSART_CLOCK(n) MERGE(cmuClock_EUSART, n)
#define SL_MX25_FLASH_SHUTDOWN_SCLK EUSART_CLOCK(SL_MX25_FLASH_SHUTDOWN_PERIPHERAL_NO)
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
  EUSART_SpiInit_TypeDef init = EUSART_SPI_MASTER_INIT_DEFAULT_HF;
  EUSART_SpiAdvancedInit_TypeDef advancedInit = EUSART_SPI_ADVANCED_INIT_DEFAULT;

  CMU_ClockEnable(cmuClock_GPIO, true);
  CMU_ClockEnable(SL_MX25_FLASH_SHUTDOWN_SCLK, true);

  advancedInit.msbFirst     = true;
  advancedInit.autoCsEnable = false;
  init.bitRate = SL_MX25_FLASH_SHUTDOWN_BAUDRATE;

  init.advancedSettings = &advancedInit;

  EUSART_SpiInit(SL_MX25_FLASH_SHUTDOWN_PERIPHERAL, &init);

  // IO config
  GPIO_PinModeSet(SL_MX25_FLASH_SHUTDOWN_TX_PORT, SL_MX25_FLASH_SHUTDOWN_TX_PIN, gpioModePushPull, 1);
  GPIO_PinModeSet(SL_MX25_FLASH_SHUTDOWN_RX_PORT, SL_MX25_FLASH_SHUTDOWN_RX_PIN, gpioModeInput, 0);
  GPIO_PinModeSet(SL_MX25_FLASH_SHUTDOWN_SCLK_PORT, SL_MX25_FLASH_SHUTDOWN_SCLK_PIN, gpioModePushPull, 1);
  GPIO_PinModeSet(SL_MX25_FLASH_SHUTDOWN_CS_PORT, SL_MX25_FLASH_SHUTDOWN_CS_PIN, gpioModePushPull, 1);

  GPIO->EUSARTROUTE[SL_MX25_FLASH_SHUTDOWN_PERIPHERAL_NO].SCLKROUTE  = ((SL_MX25_FLASH_SHUTDOWN_SCLK_PORT << _GPIO_EUSART_SCLKROUTE_PORT_SHIFT)
                                                                        | (SL_MX25_FLASH_SHUTDOWN_SCLK_PIN  << _GPIO_EUSART_SCLKROUTE_PIN_SHIFT));
  GPIO->EUSARTROUTE[SL_MX25_FLASH_SHUTDOWN_PERIPHERAL_NO].RXROUTE   = ((SL_MX25_FLASH_SHUTDOWN_RX_PORT << _GPIO_EUSART_RXROUTE_PORT_SHIFT)
                                                                       | (SL_MX25_FLASH_SHUTDOWN_RX_PIN  << _GPIO_EUSART_RXROUTE_PIN_SHIFT));
  GPIO->EUSARTROUTE[SL_MX25_FLASH_SHUTDOWN_PERIPHERAL_NO].TXROUTE   = ((SL_MX25_FLASH_SHUTDOWN_TX_PORT << _GPIO_EUSART_TXROUTE_PORT_SHIFT)
                                                                       | (SL_MX25_FLASH_SHUTDOWN_TX_PIN  << _GPIO_EUSART_TXROUTE_PIN_SHIFT));
  GPIO->EUSARTROUTE[SL_MX25_FLASH_SHUTDOWN_PERIPHERAL_NO].ROUTEEN   = (GPIO_EUSART_ROUTEEN_RXPEN
                                                                       | GPIO_EUSART_ROUTEEN_TXPEN
                                                                       | GPIO_EUSART_ROUTEEN_SCLKPEN);

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
  EUSART_Spi_TxRx(SL_MX25_FLASH_SHUTDOWN_PERIPHERAL, 0xB9);

  // Chip select go high to end a flash command
  cs_high();

  // Deinit flash
  GPIO_PinModeSet(SL_MX25_FLASH_SHUTDOWN_TX_PORT, SL_MX25_FLASH_SHUTDOWN_TX_PIN, gpioModeDisabled, 0);
  GPIO_PinModeSet(SL_MX25_FLASH_SHUTDOWN_RX_PORT, SL_MX25_FLASH_SHUTDOWN_RX_PIN, gpioModeDisabled, 0);
  GPIO_PinModeSet(SL_MX25_FLASH_SHUTDOWN_SCLK_PORT, SL_MX25_FLASH_SHUTDOWN_SCLK_PIN, gpioModeDisabled, 1);
  GPIO_PinModeSet(SL_MX25_FLASH_SHUTDOWN_CS_PORT, SL_MX25_FLASH_SHUTDOWN_CS_PIN, gpioModeDisabled, 1);

  EUSART_Reset(SL_MX25_FLASH_SHUTDOWN_PERIPHERAL);

  GPIO->EUSARTROUTE[SL_MX25_FLASH_SHUTDOWN_PERIPHERAL_NO].SCLKROUTE = _GPIO_EUSART_SCLKROUTE_RESETVALUE;
  GPIO->EUSARTROUTE[SL_MX25_FLASH_SHUTDOWN_PERIPHERAL_NO].RXROUTE  = _GPIO_EUSART_RXROUTE_RESETVALUE;
  GPIO->EUSARTROUTE[SL_MX25_FLASH_SHUTDOWN_PERIPHERAL_NO].TXROUTE  = _GPIO_EUSART_TXROUTE_RESETVALUE;
  GPIO->EUSARTROUTE[SL_MX25_FLASH_SHUTDOWN_PERIPHERAL_NO].ROUTEEN  = _GPIO_EUSART_ROUTEEN_RESETVALUE;

  CMU_ClockEnable(SL_MX25_FLASH_SHUTDOWN_SCLK, false);
#endif
}
