/***************************************************************************//**
 * @file
 * @brief KEYSCAN HAL implementation.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

#include <stdint.h>
#include <stdbool.h>

#include "em_core.h"
#include "em_device.h"
#include "em_assert.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "peripheral_keyscan.h"
#include "keyscan_driver_hal.h"
#include "keyscan_driver_config.h"

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

// We must obtain a period of 2 ms by dividing the Peripheral Clock with the
// internal keyscan clock divider.
#define KEYSCAN_CLOCK_PERIOD_MS  2u
#define KEYSCAN_CLOCK_FREQUENCY  (1000 / KEYSCAN_CLOCK_PERIOD_MS)

/***************************************************************************//**
 * Initializes the Keyscan peripheral.
 ******************************************************************************/
void sli_keyscan_driver_hal_init(void)
{
  sl_keyscan_config_t hw_config;
  uint32_t clock_freq;
  uint32_t clock_div;

  // Set hardware configuration
  hw_config.auto_start_enable = false;
  hw_config.column_number = SL_KEYSCAN_DRIVER_COLUMN_NUMBER;
  hw_config.row_number = SL_KEYSCAN_DRIVER_ROW_NUMBER;
  hw_config.scan_delay = SL_KEYSCAN_DRIVER_SCAN_DELAY_MS;
  hw_config.debounce_delay = SL_KEYSCAN_DRIVER_DEBOUNCE_DELAY_MS;
  hw_config.stable_delay = SL_KEYSCAN_DRIVER_STABLE_DELAY_MS;
  hw_config.single_press_enable = SL_KEYSCAN_DRIVER_SINGLEPRESS;

  // Clock initialization
  // TODO need to set the clock/oscillator for cmuClock_KEYSCAN. In driver or outside?
  clock_freq = CMU_ClockFreqGet(cmuClock_KEYSCAN);
  clock_div = clock_freq / KEYSCAN_CLOCK_FREQUENCY - 1;
  hw_config.clock_divider = clock_div;

  // Hardware initialization
  sl_keyscan_init(&hw_config);

  // Clear interrupt flags
  sl_keyscan_disable_interrupts(_KEYSCAN_IEN_MASK);
  sl_keyscan_clear_interrupts(_KEYSCAN_IEN_MASK);

  // Enable interrupts
  NVIC_ClearPendingIRQ(KEYSCAN_IRQn);
  NVIC_EnableIRQ(KEYSCAN_IRQn);
}

/***************************************************************************//**
 * Initializes the Keyscan peripheral GPIO.
 ******************************************************************************/
void sli_keyscan_driver_hal_init_gpio(void)
{
  uint8_t i;

  // GPIO setup
  for (i = 0; i < SL_KEYSCAN_DRIVER_COLUMN_NUMBER; i++) {
    GPIO->KEYSCANROUTE.ROUTEEN |= (1 << i);
  }

#if (SL_KEYSCAN_DRIVER_COLUMN_NUMBER >= 1u)
  GPIO->KEYSCANROUTE.COLOUT0ROUTE = (SL_KEYSCAN_DRIVER_COLUMN0_PORT << _GPIO_KEYSCAN_COLOUT0ROUTE_PORT_SHIFT)
                                    | (SL_KEYSCAN_DRIVER_COLUMN0_PIN << _GPIO_KEYSCAN_COLOUT0ROUTE_PIN_SHIFT);
  GPIO_PinModeSet(SL_KEYSCAN_DRIVER_COLUMN0_PORT, SL_KEYSCAN_DRIVER_COLUMN0_PIN, gpioModeWiredAnd, 1);
#if (SL_KEYSCAN_DRIVER_COLUMN_NUMBER >= 2u)
  GPIO->KEYSCANROUTE.COLOUT1ROUTE = (SL_KEYSCAN_DRIVER_COLUMN1_PORT << _GPIO_KEYSCAN_COLOUT1ROUTE_PORT_SHIFT)
                                    | (SL_KEYSCAN_DRIVER_COLUMN1_PIN << _GPIO_KEYSCAN_COLOUT1ROUTE_PIN_SHIFT);
  GPIO_PinModeSet(SL_KEYSCAN_DRIVER_COLUMN1_PORT, SL_KEYSCAN_DRIVER_COLUMN1_PIN, gpioModeWiredAnd, 1);
#if (SL_KEYSCAN_DRIVER_COLUMN_NUMBER >= 3u)
  GPIO->KEYSCANROUTE.COLOUT2ROUTE = (SL_KEYSCAN_DRIVER_COLUMN2_PORT << _GPIO_KEYSCAN_COLOUT2ROUTE_PORT_SHIFT)
                                    | (SL_KEYSCAN_DRIVER_COLUMN2_PIN << _GPIO_KEYSCAN_COLOUT2ROUTE_PIN_SHIFT);
  GPIO_PinModeSet(SL_KEYSCAN_DRIVER_COLUMN2_PORT, SL_KEYSCAN_DRIVER_COLUMN2_PIN, gpioModeWiredAnd, 1);
#if (SL_KEYSCAN_DRIVER_COLUMN_NUMBER >= 4u)
  GPIO->KEYSCANROUTE.COLOUT3ROUTE = (SL_KEYSCAN_DRIVER_COLUMN3_PORT << _GPIO_KEYSCAN_COLOUT3ROUTE_PORT_SHIFT)
                                    | (SL_KEYSCAN_DRIVER_COLUMN3_PIN << _GPIO_KEYSCAN_COLOUT3ROUTE_PIN_SHIFT);
  GPIO_PinModeSet(SL_KEYSCAN_DRIVER_COLUMN3_PORT, SL_KEYSCAN_DRIVER_COLUMN3_PIN, gpioModeWiredAnd, 1);
#if (SL_KEYSCAN_DRIVER_COLUMN_NUMBER >= 5u)
  GPIO->KEYSCANROUTE.COLOUT4ROUTE = (SL_KEYSCAN_DRIVER_COLUMN4_PORT << _GPIO_KEYSCAN_COLOUT4ROUTE_PORT_SHIFT)
                                    | (SL_KEYSCAN_DRIVER_COLUMN4_PIN << _GPIO_KEYSCAN_COLOUT4ROUTE_PIN_SHIFT);
  GPIO_PinModeSet(SL_KEYSCAN_DRIVER_COLUMN4_PORT, SL_KEYSCAN_DRIVER_COLUMN4_PIN, gpioModeWiredAnd, 1);
#if (SL_KEYSCAN_DRIVER_COLUMN_NUMBER >= 6u)
  GPIO->KEYSCANROUTE.COLOUT5ROUTE = (SL_KEYSCAN_DRIVER_COLUMN5_PORT << _GPIO_KEYSCAN_COLOUT5ROUTE_PORT_SHIFT)
                                    | (SL_KEYSCAN_DRIVER_COLUMN5_PIN << _GPIO_KEYSCAN_COLOUT5ROUTE_PIN_SHIFT);
  GPIO_PinModeSet(SL_KEYSCAN_DRIVER_COLUMN5_PORT, SL_KEYSCAN_DRIVER_COLUMN5_PIN, gpioModeWiredAnd, 1);
#if (SL_KEYSCAN_DRIVER_COLUMN_NUMBER >= 7u)
  GPIO->KEYSCANROUTE.COLOUT6ROUTE = (SL_KEYSCAN_DRIVER_COLUMN6_PORT << _GPIO_KEYSCAN_COLOUT6ROUTE_PORT_SHIFT)
                                    | (SL_KEYSCAN_DRIVER_COLUMN6_PIN << _GPIO_KEYSCAN_COLOUT6ROUTE_PIN_SHIFT);
  GPIO_PinModeSet(SL_KEYSCAN_DRIVER_COLUMN6_PORT, SL_KEYSCAN_DRIVER_COLUMN6_PIN, gpioModeWiredAnd, 1);
#if (SL_KEYSCAN_DRIVER_COLUMN_NUMBER >= 8u)
  GPIO->KEYSCANROUTE.COLOUT7ROUTE = (SL_KEYSCAN_DRIVER_COLUMN7_PORT << _GPIO_KEYSCAN_COLOUT7ROUTE_PORT_SHIFT)
                                    | (SL_KEYSCAN_DRIVER_COLUMN7_PIN << _GPIO_KEYSCAN_COLOUT7ROUTE_PIN_SHIFT);
  GPIO_PinModeSet(SL_KEYSCAN_DRIVER_COLUMN7_PORT, SL_KEYSCAN_DRIVER_COLUMN7_PIN, gpioModeWiredAnd, 1);

#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#if (SL_KEYSCAN_DRIVER_ROW_NUMBER >= 1u)
  GPIO->KEYSCANROUTE.ROWSENSE0ROUTE = (SL_KEYSCAN_DRIVER_ROW0_PORT << _GPIO_KEYSCAN_ROWSENSE0ROUTE_PORT_SHIFT)
                                      | (SL_KEYSCAN_DRIVER_ROW0_PIN << _GPIO_KEYSCAN_ROWSENSE0ROUTE_PIN_SHIFT);
  GPIO_PinModeSet(SL_KEYSCAN_DRIVER_ROW0_PORT, SL_KEYSCAN_DRIVER_ROW0_PIN, gpioModeInputPull, 1);

#if (SL_KEYSCAN_DRIVER_ROW_NUMBER >= 2u)
  GPIO->KEYSCANROUTE.ROWSENSE1ROUTE = (SL_KEYSCAN_DRIVER_ROW1_PORT << _GPIO_KEYSCAN_ROWSENSE1ROUTE_PORT_SHIFT)
                                      | (SL_KEYSCAN_DRIVER_ROW1_PIN << _GPIO_KEYSCAN_ROWSENSE1ROUTE_PIN_SHIFT);
  GPIO_PinModeSet(SL_KEYSCAN_DRIVER_ROW1_PORT, SL_KEYSCAN_DRIVER_ROW1_PIN, gpioModeInputPull, 1);

#if (SL_KEYSCAN_DRIVER_ROW_NUMBER >= 3u)
  GPIO->KEYSCANROUTE.ROWSENSE2ROUTE = (SL_KEYSCAN_DRIVER_ROW2_PORT << _GPIO_KEYSCAN_ROWSENSE2ROUTE_PORT_SHIFT)
                                      | (SL_KEYSCAN_DRIVER_ROW2_PIN << _GPIO_KEYSCAN_ROWSENSE2ROUTE_PIN_SHIFT);
  GPIO_PinModeSet(SL_KEYSCAN_DRIVER_ROW2_PORT, SL_KEYSCAN_DRIVER_ROW2_PIN, gpioModeInputPull, 1);

#if (SL_KEYSCAN_DRIVER_ROW_NUMBER >= 4u)
  GPIO->KEYSCANROUTE.ROWSENSE3ROUTE = (SL_KEYSCAN_DRIVER_ROW3_PORT << _GPIO_KEYSCAN_ROWSENSE3ROUTE_PORT_SHIFT)
                                      | (SL_KEYSCAN_DRIVER_ROW3_PIN << _GPIO_KEYSCAN_ROWSENSE3ROUTE_PIN_SHIFT);
  GPIO_PinModeSet(SL_KEYSCAN_DRIVER_ROW3_PORT, SL_KEYSCAN_DRIVER_ROW3_PIN, gpioModeInputPull, 1);

#if (SL_KEYSCAN_DRIVER_ROW_NUMBER >= 5u)
  GPIO->KEYSCANROUTE.ROWSENSE4ROUTE = (SL_KEYSCAN_DRIVER_ROW4_PORT << _GPIO_KEYSCAN_ROWSENSE4ROUTE_PORT_SHIFT)
                                      | (SL_KEYSCAN_DRIVER_ROW4_PIN << _GPIO_KEYSCAN_ROWSENSE4ROUTE_PIN_SHIFT);
  GPIO_PinModeSet(SL_KEYSCAN_DRIVER_ROW4_PORT, SL_KEYSCAN_DRIVER_ROW4_PIN, gpioModeInputPull, 1);
#if (SL_KEYSCAN_DRIVER_ROW_NUMBER >= 6u)
  GPIO->KEYSCANROUTE.ROWSENSE5ROUTE = (SL_KEYSCAN_DRIVER_ROW5_PORT << _GPIO_KEYSCAN_ROWSENSE5ROUTE_PORT_SHIFT)
                                      | (SL_KEYSCAN_DRIVER_ROW5_PIN << _GPIO_KEYSCAN_ROWSENSE5ROUTE_PIN_SHIFT);

  GPIO_PinModeSet(SL_KEYSCAN_DRIVER_ROW5_PORT, SL_KEYSCAN_DRIVER_ROW5_PIN, gpioModeInputPull, 1);
#endif
#endif
#endif
#endif
#endif
#endif
}

/***************************************************************************//**
 * Enables Keyscan interrupts by passing a set of flags.
 ******************************************************************************/
void sli_keyscan_driver_hal_enable_interrupts(uint8_t local_flags)
{
  uint32_t keyscan_ien = 0u;

  if (local_flags & KEYSCAN_DRIVER_EVENT_WAKEUP) {
    keyscan_ien |= KEYSCAN_IF_WAKEUP;
  }

  if (local_flags & KEYSCAN_DRIVER_EVENT_KEY) {
    keyscan_ien |= KEYSCAN_IF_KEY;
  }

  if (local_flags & KEYSCAN_DRIVER_EVENT_NOKEY) {
    keyscan_ien |= KEYSCAN_IF_NOKEY;
  }

  if (local_flags & KEYSCAN_DRIVER_EVENT_SCANNED) {
    keyscan_ien |= KEYSCAN_IF_SCANNED;
  }

  sl_keyscan_enable_interrupts(keyscan_ien);
}

/***************************************************************************//**
 * Gets the column and row information from the peripheral when a key is press.
 ******************************************************************************/
void sli_keyscan_driver_hal_get_column_row(uint8_t *p_column,
                                           uint8_t *p_row)
{
  uint32_t status;

  status = sl_keyscan_get_status();

  *p_column = (status & _KEYSCAN_STATUS_COL_MASK) >> _KEYSCAN_STATUS_COL_SHIFT;
  *p_row = (status & _KEYSCAN_STATUS_ROW_MASK) >> _KEYSCAN_STATUS_ROW_SHIFT;
  *p_row = ~*p_row;
}

/***************************************************************************//**
 * Return if keyscan scan is currently running or not.
 ******************************************************************************/
bool sli_keyscan_driver_hal_is_scan_running(void)
{
  uint32_t status;

  status = sl_keyscan_get_status();

  return ((status & _KEYSCAN_STATUS_RUNNING_MASK) >> _KEYSCAN_STATUS_RUNNING_SHIFT ? true : false);
}

/***************************************************************************//**
 * Starts the keyscan scan.
 ******************************************************************************/
void sli_keyscan_driver_hal_start_scan(bool enable)
{
  if (enable) {
    sl_keyscan_enable();
  }

  sl_keyscan_start_scan();

  sl_keyscan_wait_sync();
}

/***************************************************************************//**
 * Stops the keyscan scan.
 ******************************************************************************/
void sli_keyscan_driver_hal_stop_scan(void)
{
  sl_keyscan_stop_scan();

  sl_keyscan_wait_sync();

  sl_keyscan_disable();
}

/***************************************************************************//**
 * KEYSCAN interrupt handler.
 ******************************************************************************/
void KEYSCAN_IRQHandler(void)
{
  uint32_t irq_flags;
  uint32_t local_flags = 0;

  // Retrieve Keyscan interrupt flags
  irq_flags = sl_keyscan_get_interrupts();

  // Interrupt "wake-up from sleep" handling.
  if (irq_flags & KEYSCAN_IF_WAKEUP) {
    local_flags |= KEYSCAN_DRIVER_EVENT_WAKEUP;
  }

  // Interrupt "key pressed detected" handling.
  if (irq_flags & KEYSCAN_IF_KEY) {
    local_flags |= KEYSCAN_DRIVER_EVENT_KEY;
  }

  // Interrupt "all keys pressed now released" handling.
  if (irq_flags & KEYSCAN_IF_NOKEY) {
    local_flags |= KEYSCAN_DRIVER_EVENT_NOKEY;
  }

  // Interrupt "scanned complete with no key pressed" handling.
  if (irq_flags & KEYSCAN_IF_SCANNED) {
    local_flags |= KEYSCAN_DRIVER_EVENT_SCANNED;
  }

  // Clear all interrupt flags
  sl_keyscan_clear_interrupts(irq_flags);

  // Process interrupts
  sli_keyscan_process_irq(local_flags);
}
