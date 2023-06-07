/**
 * Provides support for BRD8029A (LEDs on EXP Board)
 *
 * @copyright 2022 Silicon Laboratories Inc.
 */

#ifndef RADIO_BOARD_BRD2603A_LED_H
#define RADIO_BOARD_BRD2603A_LED_H

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

// </h>

// <h>PWM configuration

// <o SL_PWM_LED1_FREQUENCY> PWM frequency [Hz]
// <i> Default: 10000
#define SL_PWM_LED1_FREQUENCY       10000

// <o SL_PWM_LED1_POLARITY> Polarity
// <PWM_ACTIVE_HIGH=> Active high
// <PWM_ACTIVE_LOW=> Active low
// <i> Default: PWM_ACTIVE_HIGH
#define SL_PWM_LED1_POLARITY        PWM_ACTIVE_HIGH
// </h> end pwm configuration

// <<< end of configuration section >>>

// <<< sl:start pin_tool >>>

#define LED1_LABEL           "LED0"
// <gpio> LED1_GPIO
// $[GPIO_LED1_GPIO]
#define LED1_GPIO_PORT       gpioPortC
#define LED1_GPIO_PIN        8
// [GPIO_LED1_GPIO]$

// <timer channel=OUTPUT> SL_PWM_LED1
// $[TIMER_SL_PWM_LED1]
#define SL_PWM_LED1_PERIPHERAL                   TIMER1
#define SL_PWM_LED1_PERIPHERAL_NO                1

#define SL_PWM_LED1_OUTPUT_CHANNEL               0
// TIMER1 CC0 on PC09
#define SL_PWM_LED1_OUTPUT_PORT                  gpioPortC
#define SL_PWM_LED1_OUTPUT_PIN                   9

// [TIMER_SL_PWM_LED1]$

// <<< sl:end pin_tool >>>

#endif /* RADIO_BOARD_BRD2603A_LED_H */
