/**
 * @file
 * Command Class Binary Switch Configuration API
 * @copyright 2022 Silicon Laboratories Inc.
 */

#ifndef CC_BINARY_SWITCH_CONFIG_API_H
#define CC_BINARY_SWITCH_CONFIG_API_H

#include <CC_BinarySwitch.h>
#include <stdint.h>

/**
 * @addtogroup CC Command Classes
 * @{
 * @addtogroup BinarySwitch Binary Switch
 * @{
 */

void cc_binary_switch_handler(cc_binary_switch_t * p_switch);

cc_binary_switch_t * cc_binary_switch_get_config(void);

uint8_t cc_binary_switch_get_config_length(void);
/**
 * @}
 * @}
 */

#endif /* CC_BINARY_SWITCH_CONFIG_API_H */
