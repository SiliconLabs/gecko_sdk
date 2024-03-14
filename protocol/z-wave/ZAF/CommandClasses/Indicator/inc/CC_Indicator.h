/**
 * @file
 * Handler for Command Class Indicator V3
 * 
 * @addtogroup CC
 * @{
 * @addtogroup Indicator
 * @{
 * 
 * Indicator CC is mandatory since Z-Wave+ V2. It can be used to identify a device in the network, by 
 * sending command that will, for example, set the LED indicator to ON over a certain period.
 * 
 * @}
 * @}
 * 
 * @copyright 2019 Silicon Laboratories Inc.
 */

#ifndef CC_INDICATOR_H_
#define CC_INDICATOR_H_

#include <ZAF_types.h>
#include <ZW_classcmd.h>
#include <CC_Common.h>

/**
 * @addtogroup CC
 * @{
 * @addtogroup Indicator
 * @{
 */

/**
 * Struct used to pass operational data to TSE module.
 *
 * See ZAF_TSE_Trigger() for more information.
 *
 * @attention Receive options MUST be the first element as TSE relies on the receive options.
 */
typedef struct s_CC_indicator_data_t_
{
  RECEIVE_OPTIONS_TYPE_EX rxOptions; /**< rxOptions */
  uint8_t indicatorId; /**< Indicator Id */
} s_CC_indicator_data_t;

/**
 * Resets the indicator CC properties to their "off" values.
 *
 * If the application manually de-activates the Indicator (e.g. learn mode), it should call
 * this function to have the CC Indicator values refreshed before it reports
 * its state to the Lifeline destinations.
 *
 * When starting a blink sequence we simply off load the blinking to a
 * board specific indicator LED implementation. The indicator command
 * class does not keep time on when the indicator LED has completed
 * its blink sequence, instead it queries the board when a GET request
 * is received.
 */
void CC_Indicator_RefreshIndicatorProperties(void);

/**
 * CC Indicator handler that MUST be defined by the platform specific application source code to
 * signal patterns.
 *
 * Even though on/off time parameters are given in milliseconds, the
 * resolution is 1/10'th of a second.
 * 
 * @param on_time_ms  ON duration (in milliseconds) for a single blink cycle.
 *                    If on_time_ms is zero the indicator should be turned off.
 *
 * @param off_time_ms OFF duration (in milliseconds) for a single blink cycle.
 *
 * @param num_cycles  Number of blink cycles. If num_cycles is zero the indicator
 *                    LED should blink "forever" or until the next time this
 *                    function is called.
*/
void cc_indicator_handler(uint32_t on_time_ms, uint32_t off_time_ms, uint32_t num_cycles);

/**
 * @}
 * @}
 */ 

#endif /* CC_INDICATOR_H_ */
