#ifndef SL_BOARD_CONTROL_CONFIG_H
#define SL_BOARD_CONTROL_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <q SL_BOARD_ENABLE_DISPLAY> Enable Display
// <i> Default: 0
#define SL_BOARD_ENABLE_DISPLAY                 0

// <q SL_BOARD_DISABLE_MEMORY_SPI> Disable SPI Flash
// <i> Default: 1
#define SL_BOARD_DISABLE_MEMORY_SPI             1

// <<< end of configuration section >>>

// <<< sl:start pin_tool >>>

// <gpio> SL_BOARD_ENABLE_DISPLAY
// $[GPIO_SL_BOARD_ENABLE_DISPLAY]
#define SL_BOARD_ENABLE_DISPLAY_PORT            gpioPortB
#define SL_BOARD_ENABLE_DISPLAY_PIN             1
// [GPIO_SL_BOARD_ENABLE_DISPLAY]$

// <<< sl:end pin_tool >>>

#endif // SL_BOARD_CONTROL_CONFIG_H
