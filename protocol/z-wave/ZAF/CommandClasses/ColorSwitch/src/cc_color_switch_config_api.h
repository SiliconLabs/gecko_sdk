/**
 * @file
 * Command Class Color Switch Configuration API
 * @copyright 2022 Silicon Laboratories Inc.
 */

#ifndef CC_COLOR_SWITCH_CONFIG_API_H
#define CC_COLOR_SWITCH_CONFIG_API_H

#include <CC_ColorSwitch.h>
#include <stdint.h>
/**
 * @addtogroup CC
 * @{
 * @addtogroup ColorSwitch
 * @{
 */

void cc_color_switch_cb(s_colorComponent * colorComponent);
s_colorComponent *cc_color_switch_get_colorComponents(void);
uint8_t cc_color_switch_get_length_colorComponents(void);
uint8_t cc_color_switch_get_default_duration(void);

/**
 * @}
 * @}
 */
#endif /* CC_COLOR_SWITCH_CONFIG_API_H */
