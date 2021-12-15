/***************************************************************************//**
 * @file
 * @brief Universal SPI controller usart driver for the Silicon Labs Bootloader.
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc.  Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement.  This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include "config/btl_config.h"

#include "btl_driver_spi_controller.h"
#include "btl_driver_util.h"

#include "em_cmu.h"
#include "em_usart.h"
#include "em_gpio.h"
#include "btl_spi_controller_usart_driver_cfg.h"

#define BTL_DRIVER_SPI_USART_TXLOC \
  (SL_USART_EXTFLASH_TX_LOC << _USART_ROUTELOC0_TXLOC_SHIFT)
#define BTL_DRIVER_SPI_USART_RXLOC \
  (SL_USART_EXTFLASH_RX_LOC << _USART_ROUTELOC0_RXLOC_SHIFT)
#define BTL_DRIVER_SPI_USART_CLKLOC \
  (SL_USART_EXTFLASH_CLK_LOC << _USART_ROUTELOC0_CLKLOC_SHIFT)

#if !defined(SL_USART_EXTFLASH_PERIPHERAL)
#error "SL_USART_EXTFLASH_PERIPHERAL not defined"
#endif

#if SL_USART_EXTFLASH_PERIPHERAL_NO == 0
#define BTL_DRIVER_SPI_USART          USART0
#define BTL_DRIVER_SPI_USART_NUM      0
#define BTL_DRIVER_SPI_USART_CLOCK    cmuClock_USART0
#elif SL_USART_EXTFLASH_PERIPHERAL_NO == 1
#define BTL_DRIVER_SPI_USART          USART1
#define BTL_DRIVER_SPI_USART_NUM      1
#define BTL_DRIVER_SPI_USART_CLOCK    cmuClock_USART1
#elif SL_USART_EXTFLASH_PERIPHERAL_NO == 2
#define BTL_DRIVER_SPI_USART          USART2
#define BTL_DRIVER_SPI_USART_NUM      2
#define BTL_DRIVER_SPI_USART_CLOCK    cmuClock_USART2
#elif SL_USART_EXTFLASH_PERIPHERAL_NO == 3
#define BTL_DRIVER_SPI_USART          USART3
#define BTL_DRIVER_SPI_USART_NUM      3
#define BTL_DRIVER_SPI_USART_CLOCK    cmuClock_USART3
#elif SL_USART_EXTFLASH_PERIPHERAL_NO == 4
#define BTL_DRIVER_SPI_USART          USART4
#define BTL_DRIVER_SPI_USART_NUM      4
#define BTL_DRIVER_SPI_USART_CLOCK    cmuClock_USART4
#elif SL_USART_EXTFLASH_PERIPHERAL_NO == 5
#define BTL_DRIVER_SPI_USART          USART5
#define BTL_DRIVER_SPI_USART_NUM      5
#define BTL_DRIVER_SPI_USART_CLOCK    cmuClock_USART5
#elif SL_USART_EXTFLASH_PERIPHERAL_NO == 6
#define BTL_DRIVER_SPI_USART          USART6
#define BTL_DRIVER_SPI_USART_NUM      6
#define BTL_DRIVER_SPI_USART_CLOCK    cmuClock_USART6
#else
#error "Invalid SL_USART_EXTFLASH_PERIPHERAL"
#endif

void spi_init(void)
{
#if defined(CMU_CTRL_HFPERCLKEN)
  CMU_ClockEnable(cmuClock_GPIO, true);
  CMU_ClockEnable(BTL_DRIVER_SPI_USART_CLOCK, true);
#endif
#if defined(_CMU_CLKEN0_MASK)
  CMU->CLKEN0_SET = CMU_CLKEN0_GPIO;
#if SL_USART_EXTFLASH_PERIPHERAL_NO == 0
  CMU->CLKEN0_SET = CMU_CLKEN0_USART0;
#elif SL_USART_EXTFLASH_PERIPHERAL_NO == 1
  CMU->CLKEN0_SET = CMU_CLKEN0_USART1;
#else
#error "Invalid SL_USART_EXTFLASH_PERIPHERAL"
#endif
#endif

  // MOSI
  GPIO_PinModeSet(SL_USART_EXTFLASH_TX_PORT,
                  SL_USART_EXTFLASH_TX_PIN,
                  gpioModePushPull,
                  0);
  // MISO
  GPIO_PinModeSet(SL_USART_EXTFLASH_RX_PORT,
                  SL_USART_EXTFLASH_RX_PIN,
                  gpioModeInputPull,
                  0);
  // CLK
  GPIO_PinModeSet(SL_USART_EXTFLASH_CLK_PORT,
                  SL_USART_EXTFLASH_CLK_PIN,
                  gpioModePushPull,
                  0);
  // CS#
  GPIO_PinModeSet(SL_USART_EXTFLASH_CS_PORT,
                  SL_USART_EXTFLASH_CS_PIN,
                  gpioModePushPull,
                  1);

  // Don't do USART_InitSync here since it pulls in ClockFreqGet which is a
  // terrifyingly large function

#if defined(USART_EN_EN)
  BTL_DRIVER_SPI_USART->EN_SET = USART_EN_EN;
#endif

  // Make sure disabled first, before resetting other registers
  BTL_DRIVER_SPI_USART->CMD = USART_CMD_RXDIS
                              | USART_CMD_TXDIS
                              | USART_CMD_MASTERDIS
                              | USART_CMD_RXBLOCKDIS
                              | USART_CMD_TXTRIDIS
                              | USART_CMD_CLEARTX
                              | USART_CMD_CLEARRX;
  BTL_DRIVER_SPI_USART->TRIGCTRL = _USART_TRIGCTRL_RESETVALUE;
  BTL_DRIVER_SPI_USART->IEN = _USART_IEN_RESETVALUE;
#if defined(_USART_IFC_MASK)
  BTL_DRIVER_SPI_USART->IFC = _USART_IFC_MASK;
#else
  BTL_DRIVER_SPI_USART->IF_CLR = _USART_IF_MASK;
#endif

  // Set up for SPI
  BTL_DRIVER_SPI_USART->CTRL = _USART_CTRL_RESETVALUE
                               | USART_CTRL_SYNC
                               | USART_CTRL_CLKPOL_IDLELOW
                               | USART_CTRL_CLKPHA_SAMPLELEADING
                               | USART_CTRL_MSBF;

  // Configure databits, leave stopbits and parity at reset default (not used)
  BTL_DRIVER_SPI_USART->FRAME = _USART_FRAME_RESETVALUE
                                | USART_FRAME_DATABITS_EIGHT;

  // Configure baudrate
  uint32_t clkdiv = util_getClockFreq();
  clkdiv = (clkdiv - 1) / (2 * SL_USART_EXTFLASH_FREQUENCY);
  clkdiv = clkdiv << 8;
  clkdiv &= _USART_CLKDIV_DIV_MASK;
  BTL_DRIVER_SPI_USART->CLKDIV = clkdiv;

  // Finally enable (as specified)
  BTL_DRIVER_SPI_USART->CMD = USART_CMD_MASTEREN;

#if defined(_USART_ROUTEPEN_RESETVALUE)
  BTL_DRIVER_SPI_USART->ROUTEPEN = USART_ROUTEPEN_TXPEN
                                   | USART_ROUTEPEN_RXPEN
                                   | USART_ROUTEPEN_CLKPEN;

  BTL_DRIVER_SPI_USART->ROUTELOC0 = BTL_DRIVER_SPI_USART_TXLOC
                                    | BTL_DRIVER_SPI_USART_RXLOC
                                    | BTL_DRIVER_SPI_USART_CLKLOC;
#else
  GPIO->USARTROUTE[BTL_DRIVER_SPI_USART_NUM].TXROUTE = 0
                                                       | (SL_USART_EXTFLASH_TX_PORT << _GPIO_USART_TXROUTE_PORT_SHIFT)
                                                       | (SL_USART_EXTFLASH_TX_PIN << _GPIO_USART_TXROUTE_PIN_SHIFT);
  GPIO->USARTROUTE[BTL_DRIVER_SPI_USART_NUM].RXROUTE = 0
                                                       | (SL_USART_EXTFLASH_RX_PORT << _GPIO_USART_RXROUTE_PORT_SHIFT)
                                                       | (SL_USART_EXTFLASH_RX_PIN << _GPIO_USART_RXROUTE_PIN_SHIFT);
  GPIO->USARTROUTE[BTL_DRIVER_SPI_USART_NUM].CLKROUTE = 0
                                                        | (SL_USART_EXTFLASH_CLK_PORT << _GPIO_USART_CLKROUTE_PORT_SHIFT)
                                                        | (SL_USART_EXTFLASH_CLK_PIN << _GPIO_USART_CLKROUTE_PIN_SHIFT);

  GPIO->USARTROUTE[BTL_DRIVER_SPI_USART_NUM].ROUTEEN = 0
                                                       | GPIO_USART_ROUTEEN_TXPEN
                                                       | GPIO_USART_ROUTEEN_RXPEN
                                                       | GPIO_USART_ROUTEEN_CLKPEN;
#endif

  BTL_DRIVER_SPI_USART->CMD = USART_CMD_RXEN | USART_CMD_TXEN;
}

void spi_deinit(void)
{
  util_deinitUsart(BTL_DRIVER_SPI_USART, BTL_DRIVER_SPI_USART_NUM, BTL_DRIVER_SPI_USART_CLOCK);
#if defined(_CMU_CLKEN0_MASK)
  CMU->CLKEN0_CLR = CMU_CLKEN0_GPIO;
#endif
}

void spi_writeByte(uint8_t data)
{
  USART_SpiTransfer(BTL_DRIVER_SPI_USART, data);
}

void spi_writeHalfword(uint16_t data)
{
  USART_Tx(BTL_DRIVER_SPI_USART, (data >> 8) & 0xFF);
  USART_Tx(BTL_DRIVER_SPI_USART, data & 0xFF);
  USART_Rx(BTL_DRIVER_SPI_USART);
  USART_Rx(BTL_DRIVER_SPI_USART);
}

void spi_write3Byte(uint32_t data)
{
  USART_Tx(BTL_DRIVER_SPI_USART, (data >> 16) & 0xFF);
  USART_Tx(BTL_DRIVER_SPI_USART, (data >> 8) & 0xFF);
  USART_Tx(BTL_DRIVER_SPI_USART, data & 0xFF);
  USART_Rx(BTL_DRIVER_SPI_USART);
  USART_Rx(BTL_DRIVER_SPI_USART);
  USART_Rx(BTL_DRIVER_SPI_USART);
}

uint8_t spi_readByte(void)
{
  return USART_SpiTransfer(BTL_DRIVER_SPI_USART, 0xFF);
}

uint16_t spi_readHalfword(void)
{
  uint16_t retval = 0;
  USART_Tx(BTL_DRIVER_SPI_USART, 0xFF);
  USART_Tx(BTL_DRIVER_SPI_USART, 0xFF);
  retval = USART_Rx(BTL_DRIVER_SPI_USART) << 8;
  retval |= USART_Rx(BTL_DRIVER_SPI_USART);

  return retval;
}

void spi_setCsActive(void)
{
  GPIO_PinOutClear(SL_USART_EXTFLASH_CS_PORT, SL_USART_EXTFLASH_CS_PIN);
}

void spi_setCsInactive(void)
{
  GPIO_PinOutSet(SL_USART_EXTFLASH_CS_PORT, SL_USART_EXTFLASH_CS_PIN);
}
