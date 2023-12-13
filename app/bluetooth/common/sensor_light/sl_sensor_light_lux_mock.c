/***************************************************************************//**
 * @file
 * @brief Ambient light and UV index sensor (Mock)
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#include <stddef.h>
#include "sl_sensor_lux.h"
#include "sl_sensor_light.h"
#include "sl_sensor_light_lux_mock.h"

#define LUX_MIN   ((float)0)         // Lightness minimum in lux
#define LUX_MAX   ((float)167772.14) // Lightness maximum in lux

#define UVI_MIN   ((float)0)         // UV Index minimum

// -----------------------------------------------------------------------------
// Variables

static float lux_value = LUX_MIN; // Lightness value
static float uvi_value = UVI_MIN;

// -----------------------------------------------------------------------------
// Public function definitions

sl_status_t sl_sensor_light_init(void)
{
  return SL_STATUS_OK;
}

void sl_sensor_light_deinit(void)
{
}

sl_status_t sl_sensor_light_get(float *lux, float *uvi)
{
  sl_status_t sc = SL_STATUS_OK;

  *uvi = uvi_value;
  *lux = lux_value;

  return sc;
}

void sl_sensor_light_set(float lux, float uvi)
{
  if (lux > LUX_MAX) {
    lux = LUX_MIN;
  }

  lux_value = lux;
  uvi_value = uvi;
}

sl_status_t sl_sensor_lux_init(void)
{
  return SL_STATUS_OK;
}

void sl_sensor_lux_deinit(void)
{
}

sl_status_t sl_sensor_lux_get(float *lux)
{
  sl_status_t sc = SL_STATUS_OK;

  *lux = lux_value;

  return sc;
}

void sl_sensor_lux_set(float lux)
{
  if (lux > LUX_MAX) {
    lux = LUX_MIN;
  }

  lux_value = lux;
}
