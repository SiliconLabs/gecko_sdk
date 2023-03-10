/*
 * Copyright (c) 2020-2021, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef __TFM_HAL_PLATFORM_H__
#define __TFM_HAL_PLATFORM_H__

#include <stddef.h>
#include <stdint.h>

#ifdef TFM_FIH_PROFILE_ON
#include "fih.h"
#else
#include "tfm_hal_defs.h"
#endif

#ifdef TFM_FIH_PROFILE_ON

/**
 * \brief This function performs the platform-specific initialization.
 *
 * This function is called after architecture and platform common initialization
 * has finished during system early startup.
 *
 * \retval Returns values as specified by FIH specific platform error code.
 */
fih_int tfm_hal_platform_init(void);
#else
/**
 * \brief This function performs the platform-specific initialization.
 *
 * This function is called after architecture and platform common initialization
 * has finished during system early startup.
 *
 * \retval TFM_HAL_SUCCESS          Init success.
 * \retval TFM_HAL_ERROR_GENERIC    Generic errors.
 */
enum tfm_hal_status_t tfm_hal_platform_init(void);
#endif

/**
 * \brief System reset
 */
void tfm_hal_system_reset(void);

/**
 * \brief Set up the RNG for use with random delays.
 *
 * \retval TFM_HAL_SUCCESS        Platform specific random number generation
 *                                initialization succeeded.
 * \retval Other code             Initialization failed.
 */
int32_t tfm_hal_random_init(void);

/**
 * \brief Get a random number from an RNG seeded with an entropy source.
 *
 * \param[out] rand               Buffer to hold the random value
 * \param[in] size                The size of the buffer
 *
 * \retval TFM_HAL_SUCCESS        Platform specific random number generation
 *                                succeed.
 * \retval Other code             generation failed.
 */
int32_t tfm_hal_random_generate(uint8_t *rand, size_t size);

#endif /* __TFM_HAL_PLATFORM_H__ */
