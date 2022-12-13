/**
 * @file
 * Command Class Color Switch Configuration API
 * @copyright 2022 Silicon Laboratories Inc.
 */

#ifndef CC_MULTILEVEL_SWITCH_SUPPORT_CONFIG_API_H
#define CC_MULTILEVEL_SWITCH_SUPPORT_CONFIG_API_H

#include <CC_MultilevelSwitch_Support.h>
#include <stdint.h>

/**
 * @addtogroup CC
 * @{
 * @addtogroup MultilevelSwitch
 * @{
 */

cc_multilevel_switch_t *cc_multilevel_switch_support_get_switches();
uint8_t cc_multilevel_switch_support_get_length_switches();
uint8_t cc_multilevel_switch_support_get_default_duration();
void cc_multilevel_switch_support_cb(struct cc_multilevel_switch_t * p_switch);

/**
 * @}
 * @}
 */ 

#endif /* CC_MULTILEVEL_SWITCH_SUPPORT_CONFIG_API_H */
