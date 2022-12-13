/***************************************************************************//**
 * @file timestamp.h
 * @brief timestamp class
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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
#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include "sl_sleeptimer.h"
#include <stdint.h>

// Class used for measuring timing using the sleeptimer
struct timestamp {
  uint32_t begin;
  uint32_t end;

  void start(void)
  {
    begin = sl_sleeptimer_get_tick_count();
  }

  void stop(void)
  {
    end = sl_sleeptimer_get_tick_count();
  }

  float duration_ms(void)
  {
    uint32_t freq = sl_sleeptimer_get_timer_frequency();
    return (end - begin) * 1000.f / freq;
  }
};

#endif
