/**
 * @file
 * Handler for Command Class Binary Switch.
 * @copyright 2018 Silicon Laboratories Inc.
 */

#ifndef _CC_BINARY_SWITCH_H_
#define _CC_BINARY_SWITCH_H_

#include <ZAF_types.h>
#include <ZW_TransportEndpoint.h>
#include "ZAF_Actuator.h"

/**
 * @addtogroup CC Command Classes
 * @{
 * @addtogroup BinarySwitch Binary Switch
 * @{
 */

#define BIN_SWITCH_DURATION_MIN_VAL_SECONDS 0x00
#define BIN_SWITCH_DURATION_MAX_VAL_SECONDS 0x7F
#define BIN_SWITCH_DURATION_MIN_VAL_MINUTES 0x80
#define BIN_SWITCH_DURATION_MAX_VAL_MINUTES 0xFE
#define BIN_SWITCH_DURATION_FACTORY_DEFAULT 0xFF
#define BIN_SWITCH_DURATION_MAX_MINUTES     (BIN_SWITCH_DURATION_MAX_VAL_MINUTES - BIN_SWITCH_DURATION_MIN_VAL_MINUTES)

struct cc_binary_switch_t; // Forward declaration

typedef void (*cc_binary_switch_callback_t)(struct cc_binary_switch_t * p_switch);

typedef struct cc_binary_switch_t {
  RECEIVE_OPTIONS_TYPE_EX rxOpt;            ///< Contains information required for Supervision and
                                            ///< True Status. Must be the first element in this
                                            ///< struct because TSE assumes this location.
  uint8_t endpoint;                         ///< The switch must be tied to an endpoint. Must be set
                                            ///< to 0 if no endpoints. The endpoint value MUST be
                                            ///< located as the second element in this struct as ZAF
                                            ///< depends on that for generation of the Node
                                            ///< Information Frame.
  s_Actuator actuator;                      ///< The ZAF actuator handles transitions between values.
  cc_binary_switch_callback_t callback;     ///< That will be invoked on changes of the current value.
                                            ///< Will only be invoked if no callback is passed to
                                            ///< cc_binary_switch_init().
  uint8_t default_duration;
  uint8_t old_value;                        ///< As this is a binary switch, the old value must be
                                            ///< kept until the target value is reached (in case of
                                            ///< a duration higher than zero).
} cc_binary_switch_t;

/**
 * Handler for mapping Basic Set to Multilevel Switch Set.
 *
 * This function MUST NOT be used for anything else than mapping.
 * @param[in] value Mapped value.
 * @param[in] duration Mapped duration.
 * @param[in] endpoint Mapped endpoint.
 * @return Result of the set command. @ref E_CMD_HANDLER_RETURN_CODE_HANDLED if the actual value
 *         was set to the given value right away. @ref E_CMD_HANDLER_RETURN_CODE_WORKING if the
 *         actual value is transitioning to the given value. @ref E_CMD_HANDLER_RETURN_CODE_FAIL
 *         if the parameters were incorrect.
 */
e_cmd_handler_return_code_t cc_binary_switch_set_handler(uint8_t value,
                                                         uint8_t duration,
                                                         uint8_t endpoint);

/**
 * Sets the value of a given binary switch.
 *
 * This function can be used in an application that might have a button.
 *
 * Must be used for local actuation only.
 * @param p_switch The switch of which the value is set.
 * @param value The value to set.
 */
void cc_binary_switch_set(cc_binary_switch_t * p_switch, uint8_t value);

/**
 * Returns the current value of a given binary switch.
 *
 * Must be used for local actuation only.
 * @param p_switch The switch of which the value is returned.
 * @return Current value of the given switch.
 */
uint8_t cc_binary_switch_get_current_value(cc_binary_switch_t * p_switch);

/**
 * @}
 * @}
 */

#endif /* _CC_BINARY_SWITCH_H_ */
