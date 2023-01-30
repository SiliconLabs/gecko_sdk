/**
 * Provides generic support for OPN Buttons
 *
 * @copyright 2023 Silicon Laboratories Inc.
 */

#ifndef RADIO_NO_BOARD_BUTTON_H
#define RADIO_NO_BOARD_BUTTON_H

/*************************************************************************/
/* Configure push buttons                                                */
/*************************************************************************/

// <<< Use Configuration Wizard in Context Menu >>>

// <h>Button Configuration

#define PB1_LABEL           "BTN0"

// <o PB1_ON_VALUE> Button1 ON value
// <1=> Active high
// <0=> Active low
// <d> 0
#define PB1_ON_VALUE        0

// <o PB1_INT_NO> Button1 interrupt pin number
// <d> 6
#define PB1_INT_NO          6

// <q PB1_CAN_WAKEUP_EM4> Button1 wake up from EM4
// <d> 0
#define PB1_CAN_WAKEUP_EM4  0

#define PB2_LABEL           "BTN1"

// <o PB2_ON_VALUE> Button2 ON value
// <1=> Active high
// <0=> Active low
// <d> 0
#define PB2_ON_VALUE        0

// <o PB2_INT_NO> Button2 interrupt pin number
// <d> 7
#define PB2_INT_NO          7

// <q PB2_CAN_WAKEUP_EM4> Button2 wake up from EM4
// <d> 1
#define PB2_CAN_WAKEUP_EM4  1

#define PB3_LABEL           "BTN2"

// <o PB3_ON_VALUE> Button3 ON value
// <1=> Active high
// <0=> Active low
// <d> 0
#define PB3_ON_VALUE        0

// <o PB3_INT_NO> Button3 interrupt pin number
// <d> 10
#define PB3_INT_NO          10

// <q PB3_CAN_WAKEUP_EM4> Button3 wake up from EM4
// <d> 1
#define PB3_CAN_WAKEUP_EM4  1

#define PB4_LABEL           "BTN3"

// <o PB4_ON_VALUE> Button4 ON value
// <1=> Active high
// <0=> Active low
// <d> 0
#define PB4_ON_VALUE        0

// <o PB4_INT_NO> Button4 interrupt pin number
// <d> 11
#define PB4_INT_NO          11

// <q PB4_CAN_WAKEUP_EM4> Button4 wake up from EM4
// <d> 0
#define PB4_CAN_WAKEUP_EM4  0

// </h>

// <<< end of configuration section >>>

// <<< sl:start pin_tool >>>

// <gpio> PB1_GPIO
// $[GPIO_PB1_GPIO]
#define PB1_GPIO_PORT       gpioPortA
#define PB1_GPIO_PIN        13
// [GPIO_PB1_GPIO]$

// <gpio> PB2_GPIO
// $[GPIO_PB2_GPIO]
#define PB2_GPIO_PORT       gpioPortA
#define PB2_GPIO_PIN        14
// [GPIO_PB2_GPIO]$

// <gpio> PB3_GPIO
// $[GPIO_PB3_GPIO]
#define PB3_GPIO_PORT       gpioPortC
#define PB3_GPIO_PIN        5
// [GPIO_PB3_GPIO]$

// <gpio> PB4_GPIO
// $[GPIO_PB4_GPIO]
#define PB4_GPIO_PORT       gpioPortC
#define PB4_GPIO_PIN        7
// [GPIO_PB4_GPIO]$

// <<< sl:end pin_tool >>>

#endif /* RADIO_NO_BOARD_BUTTON_H */
