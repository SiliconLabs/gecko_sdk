/**
 * Provides generic support for OPN LEDs
 *
 * @copyright 2023 Silicon Laboratories Inc.
 */

#ifndef RADIO_NO_BOARD_LED_H
#define RADIO_NO_BOARD_LED_H

/*************************************************************************/
/* Configure LEDs                                                        */
/*************************************************************************/

// <<< Use Configuration Wizard in Context Menu >>>

// <h>LED Configuration

// <o LED1_ON_VALUE> LED1 ON value
// <0=> Active low
// <1=> Active high
// <d> 1
#define LED1_ON_VALUE        1

// <o LED2_ON_VALUE> LED2 ON value
// <0=> Active low
// <1=> Active high
// <d> 1
#define LED2_ON_VALUE        1

// <o LED3_ON_VALUE> LED3 ON value
// <0=> Active low
// <1=> Active high
// <d> 1
#define LED3_ON_VALUE        1

// <o LED4_ON_VALUE> LED4 ON value
// <0=> Active low
// <1=> Active high
// <d> 1
#define LED4_ON_VALUE        1

// </h>

// <<< end of configuration section >>>

// <<< sl:start pin_tool >>>

#define LED1_LABEL           "LED0"
// <gpio> LED1_GPIO
// $[GPIO_LED1_GPIO]
#define LED1_GPIO_PORT       gpioPortB
#define LED1_GPIO_PIN        4
// [GPIO_LED1_GPIO]$

#define LED2_LABEL           "LED1"
// <gpio> LED2_GPIO
// $[GPIO_LED2_GPIO]
#define LED2_GPIO_PORT       gpioPortB
#define LED2_GPIO_PIN        5
// [GPIO_LED2_GPIO]$

#define LED3_LABEL           "LED2"
// <gpio> LED3_GPIO
// $[GPIO_LED3_GPIO]
#define LED3_GPIO_PORT       gpioPortA
#define LED3_GPIO_PIN        11
// [GPIO_LED3_GPIO]$

#define LED4_LABEL           "LED3"
// <gpio> LED4_GPIO
// $[GPIO_LED4_GPIO]
#define LED4_GPIO_PORT       gpioPortA
#define LED4_GPIO_PIN        12
// [GPIO_LED4_GPIO]$

// <<< sl:end pin_tool >>>

#endif /* RADIO_NO_BOARD_LED_H */
