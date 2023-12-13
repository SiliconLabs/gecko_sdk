/***************************************************************************//**
 * @file app.c
 * @brief Callbacks implementation and application specific code.
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

#include PLATFORM_HEADER
#include "ember.h"

#ifdef SL_CATALOG_LEGACY_NCP_SPI_PRESENT
#include "em_gpio.h"
#include "spi-protocol-device.h"
#endif // SL_CATALOG_LEGACY_NCP_SPI_PRESENT

/** @brief
 *
 * Application framework equivalent of ::emberRadioNeedsCalibratingHandler
 */
void emberAfRadioNeedsCalibratingCallback(void)
{
  sl_mac_calibrate_current_channel();
}

void emberAfMainInitCallback(void)
{
#if (((SL_IOSTREAM_EUSART_VCOM_RESTRICT_ENERGY_MODE_TO_ALLOW_RECEPTION == 0) \
  || (SL_IOSTREAM_USART_VCOM_RESTRICT_ENERGY_MODE_TO_ALLOW_RECEPTION == 0))  \
  && !defined(EMBER_TEST))
  if ((strcmp(SL_BOARD_NAME, "BRD4186C") == 0)    \
      || (strcmp(SL_BOARD_NAME, "BRD4187C") == 0) \
      || (strcmp(SL_BOARD_NAME, "BRD4188B") == 0)) {
    GPIO_IntDisable(1 << BSP_SPINCP_NWAKE_PIN);
    GPIO_EM4WUExtIntConfig(BSP_SPINCP_NWAKE_PORT, BSP_SPINCP_NWAKE_PIN, 9, false, true);
  }
#endif // (((SL_IOSTREAM_EUSART_VCOM_RESTRICT_ENERGY_MODE_TO_ALLOW_RECEPTION == 0) ||
  // (SL_IOSTREAM_USART_VCOM_RESTRICT_ENERGY_MODE_TO_ALLOW_RECEPTION == 0)) &&
  // !defined(EMBER_TEST))
}
