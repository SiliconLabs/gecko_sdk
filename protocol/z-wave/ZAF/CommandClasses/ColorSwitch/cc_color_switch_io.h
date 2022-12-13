/**
 * @file
 * Command Class Color Switch I/O interface
 * @copyright 2022 Silicon Laboratories Inc.
 */
#ifndef CC_COLOR_SWITCH_IO_H
#define CC_COLOR_SWITCH_IO_H

#include <CC_ColorSwitch.h>

/**
 * @addtogroup CC
 * @{
 * @addtogroup ColorSwitch
 * @{
 */


bool cc_color_switch_write(uint8_t color_component_id, s_colorComponent *color_component);
bool cc_color_switch_read(uint8_t color_component_id, s_colorComponent *color_component);

/**
 * @}
 * @}
 */
#endif /* CC_COLOR_SWITCH_IO_H */
