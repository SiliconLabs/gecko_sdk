/**
 * Provides support for BRD8029A (LEDs on EXP Board)
 *
 * @copyright 2022 Silicon Laboratories Inc.
 */

#ifndef EXTENSION_BOARD_8029A_EFR32ZG23_LED_H
#define EXTENSION_BOARD_8029A_EFR32ZG23_LED_H

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
#define LED1_GPIO_PORT       gpioPortA
#define LED1_GPIO_PIN        6
// [GPIO_LED1_GPIO]$

#define LED2_LABEL           "LED1"
// <gpio> LED2_GPIO
// $[GPIO_LED2_GPIO]
#define LED2_GPIO_PORT       gpioPortA
#define LED2_GPIO_PIN        7
// [GPIO_LED2_GPIO]$

#define LED3_LABEL           "LED2"
// <gpio> LED3_GPIO
// $[GPIO_LED3_GPIO]
#define LED3_GPIO_PORT       gpioPortA
#define LED3_GPIO_PIN        10
// [GPIO_LED3_GPIO]$

/* NB: EFR32 peripheral: US0_CS#0
 */
#define LED4_LABEL           "LED3"
// <gpio> LED4_GPIO
// $[GPIO_LED4_GPIO]
#define LED4_GPIO_PORT       gpioPortA
#define LED4_GPIO_PIN        0
// [GPIO_LED4_GPIO]$

// <<< sl:end pin_tool >>>


/*************************************************************************/
/* Configure RGB LEDs                                                    */
/*************************************************************************/

/* BRD8029A does not have any RGB led!
 * If paired with radio board ZGM13 then the RGB on that board can be used
 */

#endif /* EXTENSION_BOARD_8029A_EFR32ZG23_LED_H */
