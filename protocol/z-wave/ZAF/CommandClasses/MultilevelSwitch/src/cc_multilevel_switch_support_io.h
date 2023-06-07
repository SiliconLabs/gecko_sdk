/**
 * @file
 * Command Class Multilevel Switch I/O interface
 * @copyright 2022 Silicon Laboratories Inc.
 */
#ifndef cc_multilevel_switch_support_io_H
#define cc_multilevel_switch_support_io_H

#include <CC_MultilevelSwitch_Support.h>

/**
 * @addtogroup CC
 * @{
 * @addtogroup MultilevelSwitch
 * @{
 */

bool cc_multilevel_switch_write(uint8_t multilevel_component_id, cc_multilevel_switch_t *multilevel_switch);
bool cc_multilevel_switch_read(uint8_t multilevel_component_id, cc_multilevel_switch_t *multilevel_switch);

/**
 * @}
 * @}
 */ 

#endif /* cc_multilevel_switch_support_io_H */
