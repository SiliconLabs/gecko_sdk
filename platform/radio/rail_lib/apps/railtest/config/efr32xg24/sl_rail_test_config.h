#ifndef SL_RAIL_TEST_CONFIG_H
#define SL_RAIL_TEST_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>
// <h> RAILtest Configuration

// <s.50 SL_RAIL_TEST_APP_NAME> Application name displayed by CLI on boot
// <i> Default: "RAILtest"
#define SL_RAIL_TEST_APP_NAME  "RAILtest"

// <o SL_RAIL_TEST_MAX_PACKET_LENGTH> Maximum packet length
// <i> Default: 1024
#define SL_RAIL_TEST_MAX_PACKET_LENGTH  1024

// <o SL_RAIL_TEST_CONTINUOUS_TRANSFER_PERIOD> Continuous transfer period
// <i> Default: 250
#define SL_RAIL_TEST_CONTINUOUS_TRANSFER_PERIOD  250

// <o SL_RAIL_TEST_TX_BUFFER_SIZE> Transmit buffer size
// <i> Default: 512
#define SL_RAIL_TEST_TX_BUFFER_SIZE  512

// <o SL_RAIL_TEST_RX_BUFFER_SIZE> Receive buffer size
// <i> Default: 512
#define SL_RAIL_TEST_RX_BUFFER_SIZE  512

// <o SL_RAIL_TEST_BUTTON_LONG_HOLD_DURATION_MS> Button Long Press Duration (milliseconds)
// <i> Default: 1000
#define SL_RAIL_TEST_BUTTON_LONG_HOLD_DURATION_MS  1000

// </h>
// <<< end of configuration section >>>

// <<< sl:start pin_tool >>>
// <gpio> SL_RAIL_TEST_PER
// $[GPIO_SL_RAIL_TEST_PER]
#define SL_RAIL_TEST_PER_PORT                    gpioPortC
#define SL_RAIL_TEST_PER_PIN                     2
// [GPIO_SL_RAIL_TEST_PER]$
// <<< sl:end pin_tool >>>

#endif // SL_RAIL_TEST_CONFIG_H
