/***************************************************************************//**
 * @file
 * @brief CPC Timer API.
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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
#ifndef SLI_CPC_TIMER_H
#define SLI_CPC_TIMER_H

#include "sl_status.h"

#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif

#if (defined(SL_CATALOG_SLEEPTIMER_PRESENT))
#include "sl_sleeptimer.h"
#else
#include "cpc_types.h"
#endif

/***************************************************************************//**
 * Typedef for the handle used to identify a timer.
 *
 * @param handle The timer handle.
 ******************************************************************************/
#if (defined(SL_CATALOG_SLEEPTIMER_PRESENT))
typedef sl_sleeptimer_timer_handle_t sli_cpc_timer_handle_t;
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if !(defined(SL_CATALOG_SLEEPTIMER_PRESENT))
/***************************************************************************//**
 * Converts milliseconds into ticks.
 *
 * @param time_ms Number of milliseconds.
 *
 * @return Corresponding ticks number.
 *
 * @note The result is "rounded" to the superior tick number.
 *       This function is light and cannot fail so it should be privileged to
 *       perform a millisecond to tick conversion.
 ******************************************************************************/
uint32_t cpc_timer_ms_to_tick(uint16_t time_ms);

/***************************************************************************//**
 * Converts ticks in milliseconds.
 *
 * @param tick Number of tick.
 *
 * @return Corresponding milliseconds number.
 *
 * @note The result is rounded to the inferior millisecond.
 ******************************************************************************/
uint32_t cpc_timer_tick_to_ms(uint32_t tick);

/***************************************************************************//**
 * Gets current 32 bits global tick count.
 *
 * @return Current tick count.
 ******************************************************************************/
uint32_t cpc_timer_get_tick_count(void);

/***************************************************************************//**
 * Gets current 64 bits global tick count.
 *
 * @return Current tick count.
 ******************************************************************************/
uint64_t cpc_timer_get_tick_count64(void);

/***************************************************************************//**
 * Initialize a 32 bits timer
 *
 * @param handle Pointer to handle to timer.
 * @return SL_STATUS_OK if successful.
 ******************************************************************************/
sl_status_t cpc_timer_init(sli_cpc_timer_handle_t *handle);

/***************************************************************************//**
 * Starts a 32 bits timer.
 *
 * @param handle Pointer to handle to timer.
 * @param timeout Timer timeout, in timer ticks.
 * @param callback Callback function that will be called when
 *        timeout expires.
 * @param callback_data Pointer to user data that will be passed to callback.
 *
 * @return SL_STATUS_OK if successful.
 ******************************************************************************/
sl_status_t cpc_timer_start_timer(sli_cpc_timer_handle_t *handle,
                                  uint32_t timeout,
                                  void (*callback)(sli_cpc_timer_handle_t *handle, void *data),
                                  void *callback_data);

/**************************************************************************//**
 * Starts a 32 bits timer.
 *
 * @param handle Pointer to handle to timer.
 * @param timeout_ms Timer timeout, in milliseconds.
 * @param callback Callback function that will be called when
 *        timeout expires.
 * @param callback_data Pointer to user data that will be passed to callback.
 *
 * @return SL_STATUS_OK if successful.
 *****************************************************************************/
sl_status_t cpc_timer_start_timer_ms(sli_cpc_timer_handle_t *handle,
                                     uint32_t timeout_ms,
                                     void (*callback)(sli_cpc_timer_handle_t *handle, void *data),
                                     void *callback_data);

/***************************************************************************//**
 * Restarts a 32 bits timer.
 *
 * @param handle Pointer to handle to timer.
 * @param timeout Timer timeout, in timer ticks.
 * @param callback Callback function that will be called when
 *        initial/periodic timeout expires.
 * @param callback_data Pointer to user data that will be passed to callback.

 * @return SL_STATUS_OK if successful.
 ******************************************************************************/
sl_status_t cpc_timer_restart_timer(sli_cpc_timer_handle_t *handle,
                                    uint32_t timeout,
                                    void (*callback)(sli_cpc_timer_handle_t *handle, void *data),
                                    void *callback_data);

/***************************************************************************//**
 * Stops a timer.
 *
 * @param handle Pointer to handle to timer.
 *
 * @return SL_STATUS_OK if successful.
 ******************************************************************************/
sl_status_t cpc_timer_stop_timer(sli_cpc_timer_handle_t *handle);

/***************************************************************************//**
 * Delays for the specified number of milliseconds.
 *
 * @param delay_ms Delay in milliseconds.
 *
 * @return SL_STATUS_OK if successful.
 ******************************************************************************/
sl_status_t cpc_timer_delay_millisecond(uint32_t delay_ms);
#endif

/***************************************************************************//**
 * Initialize the CPC timer
 *
 * @param Handle of the CPC timer
 *
 * @return SL_STATUS_OK if successful.
 ******************************************************************************/
static inline sl_status_t sli_cpc_timer_init(sli_cpc_timer_handle_t *handle)
{
#if (defined(SL_CATALOG_SLEEPTIMER_PRESENT))
  (void)handle;
  return SL_STATUS_OK;
#else
  return cpc_timer_init(handle);
#endif
}

/***************************************************************************//**
 * Converts milliseconds into ticks.
 *
 * @param time_ms Number of milliseconds.
 *
 * @return Corresponding ticks number.
 *
 * @note The result is "rounded" to the superior tick number.
 *       This function is light and cannot fail so it should be privileged to
 *       perform a millisecond to tick conversion.
 ******************************************************************************/
static inline uint32_t sli_cpc_timer_ms_to_tick(uint16_t time_ms)
{
#if (defined(SL_CATALOG_SLEEPTIMER_PRESENT))
  return sl_sleeptimer_ms_to_tick(time_ms);
#else
  return cpc_timer_ms_to_tick(time_ms);
#endif
}

/***************************************************************************//**
 * Converts ticks in milliseconds.
 *
 * @param tick Number of tick.
 *
 * @return Corresponding milliseconds number.
 *
 * @note The result is rounded to the inferior millisecond.
 ******************************************************************************/
static inline uint32_t sli_cpc_timer_tick_to_ms(uint32_t tick)
{
#if (defined(SL_CATALOG_SLEEPTIMER_PRESENT))
  return sl_sleeptimer_tick_to_ms(tick);
#else
  return cpc_timer_tick_to_ms(tick);
#endif
}

/***************************************************************************//**
 * Gets current 32 bits global tick count.
 *
 * @return Current tick count.
 ******************************************************************************/
static inline uint32_t sli_cpc_timer_get_tick_count(void)
{
#if (defined(SL_CATALOG_SLEEPTIMER_PRESENT))
  return sl_sleeptimer_get_tick_count();
#else
  return cpc_timer_get_tick_count();
#endif
}

/***************************************************************************//**
 * Gets current 64 bits global tick count.
 *
 * @return Current tick count.
 ******************************************************************************/
static inline uint64_t sli_cpc_timer_get_tick_count64(void)
{
#if (defined(SL_CATALOG_SLEEPTIMER_PRESENT))
  return sl_sleeptimer_get_tick_count64();
#else
  return cpc_timer_get_tick_count64();
#endif
}

/***************************************************************************//**
 * Starts a 32 bits timer.
 *
 * @param handle Pointer to handle to timer.
 * @param timeout Timer timeout, in timer ticks.
 * @param callback Callback function that will be called when
 *        timeout expires.
 * @param callback_data Pointer to user data that will be passed to callback.
 *
 * @return SL_STATUS_OK if successful.
 ******************************************************************************/
static inline sl_status_t sli_cpc_timer_start_timer(sli_cpc_timer_handle_t *handle,
                                                    uint32_t timeout,
                                                    void (*callback)(sli_cpc_timer_handle_t *handle, void *data),
                                                    void *callback_data)
{
#if (defined(SL_CATALOG_SLEEPTIMER_PRESENT))
  return sl_sleeptimer_start_timer((sl_sleeptimer_timer_handle_t *)handle,
                                   timeout,
                                   (sl_sleeptimer_timer_callback_t)callback,
                                   callback_data,
                                   0,
                                   0);
#else
  return cpc_timer_start_timer(handle,
                               timeout,
                               callback,
                               callback_data);
#endif
}

/**************************************************************************//**
 * Starts a 32 bits timer.
 *
 * @param handle Pointer to handle to timer.
 * @param timeout_ms Timer timeout, in milliseconds.
 * @param callback Callback function that will be called when
 *        timeout expires.
 * @param callback_data Pointer to user data that will be passed to callback.
 *
 * @return SL_STATUS_OK if successful.
 *****************************************************************************/
static inline sl_status_t sli_cpc_timer_start_timer_ms(sli_cpc_timer_handle_t *handle,
                                                       uint32_t timeout_ms,
                                                       void (*callback)(sli_cpc_timer_handle_t *handle, void *data),
                                                       void *callback_data)
{
#if (defined(SL_CATALOG_SLEEPTIMER_PRESENT))
  return sl_sleeptimer_start_timer_ms((sl_sleeptimer_timer_handle_t *)handle,
                                      timeout_ms,
                                      (sl_sleeptimer_timer_callback_t)callback,
                                      callback_data,
                                      0,
                                      0);
#else
  return cpc_timer_start_timer_ms(handle,
                                  timeout_ms,
                                  callback,
                                  callback_data);
#endif
}
/***************************************************************************//**
 * Restarts a 32 bits timer.
 *
 * @param handle Pointer to handle to timer.
 * @param timeout Timer timeout, in timer ticks.
 * @param callback Callback function that will be called when
 *        initial/periodic timeout expires.
 * @param callback_data Pointer to user data that will be passed to callback.

 * @return SL_STATUS_OK if successful.
 ******************************************************************************/
static inline sl_status_t sli_cpc_timer_restart_timer(sli_cpc_timer_handle_t *handle,
                                                      uint32_t timeout,
                                                      void (*callback)(sli_cpc_timer_handle_t *handle, void *data),
                                                      void *callback_data)
{
#if (defined(SL_CATALOG_SLEEPTIMER_PRESENT))
  return sl_sleeptimer_restart_timer((sl_sleeptimer_timer_handle_t *)handle,
                                     timeout,
                                     (sl_sleeptimer_timer_callback_t)callback,
                                     callback_data,
                                     0,
                                     0);
#else
  return cpc_timer_restart_timer(handle,
                                 timeout,
                                 callback,
                                 callback_data);
#endif
}

/***************************************************************************//**
 * Stops a timer.
 *
 * @param handle Pointer to handle to timer.
 *
 * @return SL_STATUS_OK if successful.
 ******************************************************************************/
static inline sl_status_t sli_cpc_timer_stop_timer(sli_cpc_timer_handle_t *handle)
{
#if (defined(SL_CATALOG_SLEEPTIMER_PRESENT))
  return sl_sleeptimer_stop_timer((sl_sleeptimer_timer_handle_t *)handle);
#else
  return cpc_timer_stop_timer(handle);
#endif
}

/***************************************************************************//**
 * Delays for the specified number of milliseconds.
 *
 * @param delay_ms Delay in milliseconds.
 ******************************************************************************/
static inline void sli_cpc_timer_delay_millisecond(uint16_t delay_ms)
{
#if (defined(SL_CATALOG_SLEEPTIMER_PRESENT))
  sl_sleeptimer_delay_millisecond(delay_ms);
#else
  cpc_timer_delay_millisecond((uint32_t)delay_ms);
#endif
}

#ifdef __cplusplus
}
#endif

#endif // SLI_CPC_TIMER_H
