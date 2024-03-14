/***************************************************************************//**
 * # License
 * <b> Copyright 2019 Silicon Laboratories Inc. www.silabs.com </b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of the Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * https://www.silabs.com/about-us/legal/master-software-license-agreement
 * By installing, copying or otherwise using this software, you agree to the
 * terms of the MSLA.
 *
 ******************************************************************************/

/**
 * @file
 * @brief Hal config header file
 */
#ifndef HAL_CONFIG_H
#define HAL_CONFIG_H

#ifdef ZWAVE_SERIES_800
#include "hal-config-board-800.h"
#else
#include "hal-config-board-700.h"
#endif

#endif /* HAL_CONFIG_H */
