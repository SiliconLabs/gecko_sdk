#ifndef SL_BOARD_CONTROL_CONFIG_H
#define SL_BOARD_CONTROL_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <q SL_BOARD_ENABLE_VCOM> Enable Virtual COM UART
// <i> Default: 0
#define SL_BOARD_ENABLE_VCOM                    0

// <<< end of configuration section >>>

// <<< sl:start pin_tool >>>

// <gpio> SL_BOARD_ENABLE_VCOM
// $[GPIO_SL_BOARD_ENABLE_VCOM]
#define SL_BOARD_ENABLE_VCOM_PORT               gpioPortF
#define SL_BOARD_ENABLE_VCOM_PIN                7
// [GPIO_SL_BOARD_ENABLE_VCOM]$

// <<< sl:end pin_tool >>>

#endif // SL_BOARD_CONTROL_CONFIG_H
