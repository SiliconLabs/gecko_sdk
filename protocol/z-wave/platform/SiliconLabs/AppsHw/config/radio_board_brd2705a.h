/**
 * Provides support for BRD2705A (xG28 Explorer Kit)
 *
 * @copyright 2023 Silicon Laboratories Inc.
 */

#ifndef RADIO_BOARD_BRD2705A_H
#define RADIO_BOARD_BRD2705A_H

#include "radio_board_brd2705a_button.h"
#if defined(ZW_APPSHW_POWERSTRIP)
#include "radio_board_brd2705a_led_pwm.h"
#else
#include "radio_board_brd2705a_led.h"
#endif

/*************************************************************************/
/* Map physical board IO devices to application LEDs and buttons         */
/*************************************************************************/

#define APP_LED_A              BOARD_LED1
#define APP_LED_INDICATOR      BOARD_LED2  // Positioned opposite APP_BUTTON_LEARN_RESET

#define APP_BUTTON_A           BOARD_BUTTON_PB1 // Supports EM4 wakeup
#define APP_BUTTON_LEARN_RESET BOARD_BUTTON_PB2

#define APP_WAKEUP_BTN_SLDR    BOARD_BUTTON_PB1 // Use this one when wakeup capability is required and button is preferred to slider
#define APP_WAKEUP_SLDR_BTN    BOARD_BUTTON_PB1 // Use this one when wakeup capability is required and slider is preferred to button

#endif /* RADIO_BOARD_BRD2705A_H */
