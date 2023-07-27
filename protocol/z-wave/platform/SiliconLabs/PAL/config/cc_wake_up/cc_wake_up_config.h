/**
 * @file
 * @copyright 2023 Silicon Laboratories Inc.
 */

#ifndef _CC_WAKE_UP_CONFIG_H_
#define _CC_WAKE_UP_CONFIG_H_

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Command Class Wake Up Configuration

// <o CC_WAKE_UP_CONFIG_DEFAULT_SLEEP_TIME_SEC> Default sleep time between Wake Up Notifications <1..255:1> <f.d>
// <i> Default: 300
#define CC_WAKE_UP_CONFIG_DEFAULT_SLEEP_TIME_SEC  300

// <o CC_WAKE_UP_CONFIG_MINIMUM_SLEEP_TIME_SEC> Minimum sleep time between Wake Up Notifications <20..86400:1> <f.d>
// <i> Default: 20
#define CC_WAKE_UP_CONFIG_MINIMUM_SLEEP_TIME_SEC  20

// <o CC_WAKE_UP_CONFIG_MAXIMUM_SLEEP_TIME_SEC> Maximum sleep time between Wake Up Notifications <20..86400:1> <f.d>
// <i> Default: 86400
#define CC_WAKE_UP_CONFIG_MAXIMUM_SLEEP_TIME_SEC  86400

// <o CC_WAKE_UP_CONFIG_SLEEP_STEP_TIME_SEC> Sleep step time <1..255:1> <f.d>
// <i> Default: 20
#define CC_WAKE_UP_CONFIG_SLEEP_STEP_TIME_SEC  20

// </h>

// <<< end of configuration section >>>

#endif /* _CC_WAKE_UP_CONFIG_H_ */
