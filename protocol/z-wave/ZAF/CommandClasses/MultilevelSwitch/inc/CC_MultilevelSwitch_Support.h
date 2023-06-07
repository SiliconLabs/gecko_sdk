/**
 * @file
 * Handler for Command Class Multilevel Switch.
 *
 * This file contains functions for supporting CC Multilevel Switch. It is intended for
 * applications that is to be controlled by other devices using CC Multilevel Switch.
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */

#ifndef _CC_MULTILEVEL_SWITCH_H_
#define _CC_MULTILEVEL_SWITCH_H_

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/
#include <ZW_classcmd.h>
#include <CC_Common.h>
#include <ZAF_types.h>
#include <ZW_TransportEndpoint.h>
#include <ZAF_Actuator.h>
#include "ZAF_CC_Invoker.h"

/**
 * @addtogroup CC
 * @{
 * @addtogroup MultilevelSwitch
 * @{
 */


typedef struct cc_multilevel_switch_t {
  RECEIVE_OPTIONS_TYPE_EX rxOpt;            // Contains information required for Supervision and
                                            // True Status. Must be the first element in this
                                            // struct because TSE assumes this location.
  uint8_t endpoint;                         // The switch must be tied to an endpoint. (0 if no endpoints)
  s_Actuator actuator;                      // Defined in ZAF_Actuator.h
} cc_multilevel_switch_t;

typedef void (*cc_multilevel_switch_callback_t)(struct cc_multilevel_switch_t * p_switch);

/**
 * Sets the value of a given multilevel switch.
 *
 * This function can be used in an application that might have a button.
 *
 * Must be used for local actuation only.
 *
 * @param p_switch The switch of which the value is set.
 * @param value The value to set.
 * @param duration The time it takes to reach the value.
 */
void cc_multilevel_switch_set(cc_multilevel_switch_t * p_switch, uint8_t value, uint8_t duration);

/**
 * Starts changing the value of a given multilevel switch.
 *
 * Must be used for local actuation only.
 * @param p_switch The multilevel switch of which the value is changed.
 * @param up The direction of the change. If true the value will decrease. If false, the value will
 *           increase.
 * @param ignore_start_level Decides whether the start level is ignored or not. If set to true,
 *                           the change will start from the current value. If set to false, the
 *                           value will start it's change from the given start level.
 * @param start_level The value to start from if ignore_start_level is set to false.
 * @param duration The duration of the change.
 */
void cc_multilevel_switch_start_level_change(cc_multilevel_switch_t * p_switch,
                                             bool up,
                                             bool ignore_start_level,
                                             uint8_t start_level,
                                             uint8_t duration);

/**
 * Stops an ongoing change of a given multilevel switch.
 *
 * If no change is ongoing, nothing happens.
 *
 * Must be used for local actuation only.
 * @param p_switch The multilevel switch of which the change will be stopped.
 */
void cc_multilevel_switch_stop_level_change(cc_multilevel_switch_t * p_switch);

/**
 * Returns the current value of a given multilevel switch.
 *
 * Must be used for local actuation only.
 * @param p_switch The multilevel switch of which the value is returned.
 * @return Current value of the given multilevel switch.
 */
uint8_t cc_multilevel_switch_get_current_value(cc_multilevel_switch_t * p_switch);

/**
 * Returns the last on-value of a given multilevel switch.
 *
 * Must be used for local actuation only.
 * @param p_switch The multilevel switch of which the last on-value is returned.
 * @return Last on value of the given multilevel switch.
 */
uint8_t cc_multilevel_switch_get_last_on_value(cc_multilevel_switch_t * p_switch);

/**
 * Returns the min value of all multilevel switches.
 *
 * @return uint8_t Min value of all multilevel switches.
 */
uint8_t cc_multilevel_switch_get_min_value();

/**
 * Returns the max value of all multilevel switches.
 *
 * @return uint8_t Max value of all multilevel switches.
 */
uint8_t cc_multilevel_switch_get_max_value();

void cc_multilevel_switch_support_cb(struct cc_multilevel_switch_t * p_switch);

cc_multilevel_switch_t *cc_multilevel_switch_support_config_get_switches();
uint8_t cc_multilevel_switch_support_config_get_length_switches();
uint8_t cc_multilevel_switch_support_config_get_default_duration();

/**
 * @}
 * @}
 */ 

#endif
