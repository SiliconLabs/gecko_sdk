/***************************************************************************//**
 * @file
 * @brief SPI abstraction used by memory lcd display
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "sl_memlcd_spi.h"
#include "em_cmu.h"
#include "stddef.h"

sl_status_t sli_memlcd_spi_init(sli_memlcd_spi_handle_t *handle, int bitrate, EUSART_ClockMode_TypeDef mode)
{
  EUSART_SpiInit_TypeDef init = EUSART_SPI_MASTER_INIT_DEFAULT_HF;
  EUSART_SpiAdvancedInit_TypeDef advancedInit = EUSART_SPI_ADVANCED_INIT_DEFAULT;
  EUSART_TypeDef *eusart = handle->eusart;

  advancedInit.msbFirst = true;
  init.advancedSettings = &advancedInit;

  CMU_ClockEnable(cmuClock_GPIO, true);
  CMU_ClockEnable(handle->clock, true);

  GPIO_PinModeSet((GPIO_Port_TypeDef)handle->sclk_port, handle->sclk_pin, gpioModePushPull, 0);
  GPIO_PinModeSet((GPIO_Port_TypeDef)handle->mosi_port, handle->mosi_pin, gpioModePushPull, 0);

  init.bitRate = bitrate;
  init.clockMode = mode;

  EUSART_SpiInit(eusart, &init);

#if EUSART_COUNT > 1
  int eusart_index = EUSART_NUM(eusart);
#else
  int eusart_index = 0;
#endif
  GPIO->EUSARTROUTE[eusart_index].TXROUTE = (handle->mosi_port << _GPIO_EUSART_TXROUTE_PORT_SHIFT)
                                            | (handle->mosi_pin << _GPIO_EUSART_TXROUTE_PIN_SHIFT);
  GPIO->EUSARTROUTE[eusart_index].SCLKROUTE = (handle->sclk_port << _GPIO_EUSART_SCLKROUTE_PORT_SHIFT)
                                              | (handle->sclk_pin << _GPIO_EUSART_SCLKROUTE_PIN_SHIFT);
  // note if another driver has enable RX
  uint32_t rxpen = GPIO->EUSARTROUTE[eusart_index].ROUTEEN & _GPIO_EUSART_ROUTEEN_RXPEN_MASK;
  GPIO->EUSARTROUTE[eusart_index].ROUTEEN = GPIO_EUSART_ROUTEEN_TXPEN | GPIO_EUSART_ROUTEEN_SCLKPEN | rxpen;

  return SL_STATUS_OK;
}

sl_status_t sli_memlcd_spi_shutdown(sli_memlcd_spi_handle_t *handle)
{
  EUSART_Enable(handle->eusart, eusartDisable);
  CMU_ClockEnable(handle->clock, false);
  return SL_STATUS_OK;
}

sl_status_t sli_memlcd_spi_tx(sli_memlcd_spi_handle_t *handle, const void *data, unsigned len)
{
  const char *buffer = data;
  EUSART_TypeDef *eusart = handle->eusart;

  for (unsigned i = 0; i < len; i++) {
#if defined(SL_MEMLCD_LPM013M126A)
    EUSART_Tx(eusart, buffer[i]);
#else
    EUSART_Tx(eusart, SL_RBIT8(buffer[i]));
#endif
  }

  /* Note that at this point all the data is loaded into the fifo, this does
   * not necessarily mean that the transfer is complete. */
  return SL_STATUS_OK;
}

void sli_memlcd_spi_wait(sli_memlcd_spi_handle_t *handle)
{
  EUSART_TypeDef *eusart = handle->eusart;

  /* Wait for all transfers to finish */
  while (!(eusart->STATUS & EUSART_STATUS_TXC))
    ;
}

void sli_memlcd_spi_rx_flush(sli_memlcd_spi_handle_t *handle)
{
  EUSART_TypeDef *eusart = handle->eusart;

  /* Read data until RXFIFO empty */
  while (eusart->STATUS & EUSART_STATUS_RXFL) {
    EUSART_Rx(eusart);
  }
}

sl_status_t sli_memlcd_spi_exit_em23(sli_memlcd_spi_handle_t *handle)
{
  EUSART_TypeDef *eusart = handle->eusart;

  EUSART_Enable(eusart, eusartEnable);
  BUS_RegMaskedWrite(&GPIO->EUSARTROUTE[EUSART_NUM(eusart)].ROUTEEN,
                     _GPIO_EUSART_ROUTEEN_TXPEN_MASK | _GPIO_EUSART_ROUTEEN_SCLKPEN_MASK,
                     GPIO_EUSART_ROUTEEN_TXPEN | GPIO_EUSART_ROUTEEN_SCLKPEN);

  return SL_STATUS_OK;
}

sl_status_t sli_memlcd_spi_enter_em23(sli_memlcd_spi_handle_t *handle)
{
  EUSART_TypeDef *eusart = handle->eusart;

  BUS_RegMaskedWrite(&GPIO->EUSARTROUTE[EUSART_NUM(eusart)].ROUTEEN,
                     _GPIO_EUSART_ROUTEEN_TXPEN_MASK | _GPIO_EUSART_ROUTEEN_SCLKPEN_MASK,
                     0);

  return SL_STATUS_OK;
}
