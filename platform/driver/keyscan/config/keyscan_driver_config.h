/***************************************************************************//**
 * @file
 * @brief KEYSCAN driver configuration.
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

// <<< Use Configuration Wizard in Context Menu >>>

#ifndef KEYSCAN_DRIVER_CONFIG_H
#define KEYSCAN_DRIVER_CONFIG_H

// <o SL_KEYSCAN_DRIVER_COLUMN_NUMBER> Number of columns in keyscan <1-8>
// <i> Default: 3
#ifndef SL_KEYSCAN_DRIVER_COLUMN_NUMBER
#define SL_KEYSCAN_DRIVER_COLUMN_NUMBER 3
#endif

// <o SL_KEYSCAN_DRIVER_ROW_NUMBER> Number of rows in keyscan <1-6>
// <i> Default: 6
#ifndef SL_KEYSCAN_DRIVER_ROW_NUMBER
#define SL_KEYSCAN_DRIVER_ROW_NUMBER    6
#endif

// <o SL_KEYSCAN_DRIVER_SCAN_DELAY_MS> Scan Delay
//    <0=>     2ms
//    <1=>     4ms
//    <2=>     6ms
//    <3=>     8ms
//    <4=>     10ms
//    <5=>     12ms
//    <6=>     14ms
//    <7=>     16ms
//    <8=>     18ms
//    <9=>     20ms
//    <10=>    22ms
//    <11=>    24ms
//    <12=>    26ms
//    <13=>    28ms
//    <14=>    30ms
//    <15=>    32ms
// <i> Duration of the scan period per column
// <i> Default: 0
#ifndef SL_KEYSCAN_DRIVER_SCAN_DELAY_MS
#define SL_KEYSCAN_DRIVER_SCAN_DELAY_MS    SL_KEYSCAN_DELAY_2MS
#endif

// <o SL_KEYSCAN_DRIVER_DEBOUNCE_DELAY_MS> Debounce Delay
//    <0=>     2ms
//    <1=>     4ms
//    <2=>     6ms
//    <3=>     8ms
//    <4=>     10ms
//    <5=>     12ms
//    <6=>     14ms
//    <7=>     16ms
//    <8=>     18ms
//    <9=>     20ms
//    <10=>    22ms
//    <11=>    24ms
//    <12=>    26ms
//    <13=>    28ms
//    <14=>    30ms
//    <15=>    32ms
// <i> Duration of debounce period once a key press is detected.
// <i> Default: 0
#ifndef SL_KEYSCAN_DRIVER_DEBOUNCE_DELAY_MS
#define SL_KEYSCAN_DRIVER_DEBOUNCE_DELAY_MS    SL_KEYSCAN_DELAY_2MS
#endif

// <o SL_KEYSCAN_DRIVER_STABLE_DELAY_MS> Stable Delay
//    <0=>     2ms
//    <1=>     4ms
//    <2=>     6ms
//    <3=>     8ms
//    <4=>     10ms
//    <5=>     12ms
//    <6=>     14ms
//    <7=>     16ms
//    <8=>     18ms
//    <9=>     20ms
//    <10=>    22ms
//    <11=>    24ms
//    <12=>    26ms
//    <13=>    28ms
//    <14=>    30ms
//    <15=>    32ms
// <i> Duration of the stable period after the debounce stage.
// <i> Default: 0
#ifndef SL_KEYSCAN_DRIVER_STABLE_DELAY_MS
#define SL_KEYSCAN_DRIVER_STABLE_DELAY_MS    SL_KEYSCAN_DELAY_2MS
#endif

// <q SL_KEYSCAN_DRIVER_SINGLEPRESS> keyscan single-press functionality
// <i> Enable or disable single-press functionality.
// <i> Default: 0
#ifndef SL_KEYSCAN_DRIVER_SINGLEPRESS
#define SL_KEYSCAN_DRIVER_SINGLEPRESS  0
#endif

// <<< end of configuration section >>>

// <<< sl:start pin_tool >>>
#define SL_KEYSCAN_DRIVER_COLUMN0_PORT  gpioPortB
#define SL_KEYSCAN_DRIVER_COLUMN0_PIN   0

#define SL_KEYSCAN_DRIVER_COLUMN1_PORT  gpioPortB
#define SL_KEYSCAN_DRIVER_COLUMN1_PIN   1

#define SL_KEYSCAN_DRIVER_COLUMN2_PORT  gpioPortB
#define SL_KEYSCAN_DRIVER_COLUMN2_PIN   2

#define SL_KEYSCAN_DRIVER_COLUMN3_PORT  gpioPortB
#define SL_KEYSCAN_DRIVER_COLUMN3_PIN   3

#define SL_KEYSCAN_DRIVER_COLUMN4_PORT  gpioPortB
#define SL_KEYSCAN_DRIVER_COLUMN4_PIN   4

#define SL_KEYSCAN_DRIVER_COLUMN5_PORT  gpioPortB
#define SL_KEYSCAN_DRIVER_COLUMN5_PIN   5

#define SL_KEYSCAN_DRIVER_COLUMN6_PORT  gpioPortB
#define SL_KEYSCAN_DRIVER_COLUMN6_PIN   6

#define SL_KEYSCAN_DRIVER_COLUMN7_PORT  gpioPortB
#define SL_KEYSCAN_DRIVER_COLUMN7_PIN   7

#define SL_KEYSCAN_DRIVER_ROW0_PORT  gpioPortC
#define SL_KEYSCAN_DRIVER_ROW0_PIN   0

#define SL_KEYSCAN_DRIVER_ROW1_PORT  gpioPortC
#define SL_KEYSCAN_DRIVER_ROW1_PIN   1

#define SL_KEYSCAN_DRIVER_ROW2_PORT  gpioPortC
#define SL_KEYSCAN_DRIVER_ROW2_PIN   2

#define SL_KEYSCAN_DRIVER_ROW3_PORT  gpioPortC
#define SL_KEYSCAN_DRIVER_ROW3_PIN   3

#define SL_KEYSCAN_DRIVER_ROW4_PORT  gpioPortC
#define SL_KEYSCAN_DRIVER_ROW4_PIN   4

#define SL_KEYSCAN_DRIVER_ROW5_PORT  gpioPortC
#define SL_KEYSCAN_DRIVER_ROW5_PIN   5
// <<< sl:end pin_tool >>>

#endif /* KEYSCAN_DRIVER_CONFIG_H */
