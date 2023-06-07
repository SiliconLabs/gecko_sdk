/***************************************************************************//**
 * @file
 * @brief I2C simple poll-based master mode driver
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

#ifndef SL_I2CSPM_H
#define SL_I2CSPM_H
#include "em_gpio.h"
#include "em_i2c.h"

/***************************************************************************//**
 * @addtogroup i2cspm I2C Simple Polled Master
 * @brief I2C Simple Polled Master driver
 *
 * @details
 *   This driver supports master mode, single bus-master only. It blocks
 *   while waiting for the transfer is complete, polling for completion in EM0.
 * @{
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 ******************************   DEFINES   ************************************
 ******************************************************************************/

/* clock cycles for bus recovery */
#define SL_I2C_RECOVER_NUM_CLOCKS  10

/*******************************************************************************
 ********************************   STRUCTS   **********************************
 ******************************************************************************/

/** I2C driver instance initialization structure.
    This data structure contains a number of I2C configuration options
    required for driver instance initialization.
    This struct is passed to @ref I2CSPM_Init() when initializing a I2CSPM
    instance. */
typedef struct {
  I2C_TypeDef           *port;          /**< Peripheral port */
  GPIO_Port_TypeDef     sclPort;        /**< SCL pin port number */
  uint8_t               sclPin;         /**< SCL pin number */
  GPIO_Port_TypeDef     sdaPort;        /**< SDA pin port number */
  uint8_t               sdaPin;         /**< SDA pin number */
#if defined(_SILICON_LABS_32B_SERIES_0)
  uint8_t               portLocation;   /**< Port location */
#elif defined(_SILICON_LABS_32B_SERIES_1)
  uint8_t               portLocationScl; /**< Port location of SCL signal */
  uint8_t               portLocationSda; /**< Port location of SDA signal */
#endif
  uint32_t              i2cRefFreq;     /**< I2C reference clock */
  uint32_t              i2cMaxFreq;     /**< I2C max bus frequency to use */
  I2C_ClockHLR_TypeDef  i2cClhr;        /**< Clock low/high ratio control */
} I2CSPM_Init_TypeDef;

/// I2CSPM Peripheral
typedef I2C_TypeDef sl_i2cspm_t;

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Initialize I2C peripheral.
 *
 * @details
 *   This driver supports master mode only, single bus-master. In addition
 *   to configuring the I2C peripheral module, it also configures DK/STK
 *   specific setup in order to use the I2C bus.
 *
 * @param[in] init
 *   Pointer to I2C initialization structure
 ******************************************************************************/
void I2CSPM_Init(I2CSPM_Init_TypeDef *init);

/***************************************************************************//**
 * @brief
 *   Perform I2C transfer.
 *
 * @param[in] i2c
 *   Pointer to the peripheral port
 *
 * @param[in] seq
 *   Pointer to sequence structure defining the I2C transfer to take place. The
 *   referenced structure must exist until the transfer has fully completed.
 *
 * @return
 *   Returns status of ongoing transfer
 ******************************************************************************/
I2C_TransferReturn_TypeDef I2CSPM_Transfer(I2C_TypeDef *i2c, I2C_TransferSeq_TypeDef *seq);

#ifdef __cplusplus
}
#endif

/** @} (end group i2cspm) */

#endif /* SL_I2CSPM_H */
