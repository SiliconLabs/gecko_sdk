/***************************************************************************//**
 * @file
 * @brief Board HW abstraction header for BRD4166A
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef BOARD_H
#define BOARD_H

/// Mask to enable EM4 wake-up BTN0
#define BOARD_BUTTON0_EM4WUEN_MASK 0x10

/// RGB LED present on board
#define BOARD_RGBLED_PRESENT       1
/// Number of LEDs on board
#define BOARD_RGBLED_COUNT         4
/// RGB LED Power Enable port
#define BOARD_RGBLED_PWR_EN_PORT   gpioPortJ
/// RGB LED Power Enable pin
#define BOARD_RGBLED_PWR_EN_PIN    14
/// RGB LED COM port
#define BOARD_RGBLED_COM_PORT      gpioPortI
/// RGB LED COM0 port
#define BOARD_RGBLED_COM0_PORT     gpioPortI
/// RGB LED COM0 pin
#define BOARD_RGBLED_COM0_PIN      0
/// RGB LED COM1 port
#define BOARD_RGBLED_COM1_PORT     gpioPortI
/// RGB LED COM1 pin
#define BOARD_RGBLED_COM1_PIN      1
/// RGB LED COM2 port
#define BOARD_RGBLED_COM2_PORT     gpioPortI
/// RGB LED COM2 pin
#define BOARD_RGBLED_COM2_PIN      2
/// RGB LED COM3 port
#define BOARD_RGBLED_COM3_PORT     gpioPortI
/// RGB LED COM3 pin
#define BOARD_RGBLED_COM3_PIN      3

/***************************************************************************//**
 * Initialize all LEDs.
 ******************************************************************************/
void rgb_led_init(void);

/***************************************************************************//**
 * De-initialize all LEDs by disabling them.
 ******************************************************************************/
void rgb_led_deinit(void);

/***************************************************************************//**
 * Set LED color based on RGB components.
 *
 * @param[in] mask         LED instance mask
 * @param[in] r            Red component
 * @param[in] g            Green component
 * @param[in] b            Blue component
 ******************************************************************************/
void rgb_led_set_rgb(uint8_t m, uint8_t r, uint8_t g, uint8_t b);

/***************************************************************************//**
 * Set LED color based on lightness and temperature.
 *
 * @param[in] m            LED instance mask
 * @param[in] level        Lightness level.
 * @param[in] hue          Hue level.
 * @param[in] saturation   Saturation level.
 ******************************************************************************/
void rgb_led_set(uint8_t m, uint16_t level, uint16_t hue, uint16_t saturation);

#endif // BOARD_H
