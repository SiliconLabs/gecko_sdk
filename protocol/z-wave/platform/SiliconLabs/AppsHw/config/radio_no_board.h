/**
 * Provides support for BRD4001A (Wireless Starter Kit Mainboard)
 *
 * Provides support for the limited number of LEDs and buttons on the WSK mainboard.
 * Only use in case a button extension board is not used.
 *
 * @copyright 2023 Silicon Laboratories Inc.
 */

#ifndef RADIO_NO_BOARD_H
#define RADIO_NO_BOARD_H

#include "radio_no_board_button.h"
#include "radio_no_board_led.h"

/*************************************************************************/
/* Map physical board IO devices to application LEDs and buttons         */
/*************************************************************************/

/* Map application LEDs to board LEDs */
#define APP_LED_A              BOARD_LED1
#define APP_LED_INDICATOR      BOARD_LED2
#define APP_LED_B              BOARD_LED4
#define APP_LED_C              BOARD_LED3

/* Mapping application buttons to board buttons */
#define APP_BUTTON_A           BOARD_BUTTON_PB1
#define APP_BUTTON_LEARN_RESET BOARD_BUTTON_PB2
#define APP_BUTTON_B           BOARD_BUTTON_PB3
#define APP_BUTTON_C           BOARD_BUTTON_PB4

/* The next two are identical since on the BRD8029A only PB2 and PB3
 * can trigger a wakeup from EM4. PB2 is already used for learn/reset
 */
#define APP_WAKEUP_BTN_SLDR    BOARD_BUTTON_PB3 // Use this one when wakeup capability is required and button is preferred to slider
#define APP_WAKEUP_SLDR_BTN    BOARD_BUTTON_PB3 // Use this one when wakeup capability is required and slider is preferred to button

#endif /* RADIO_NO_BOARD_H */
