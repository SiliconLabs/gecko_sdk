/**
 * @file
 * @copyright 2022 Silicon Laboratories Inc.
 */

#ifndef _CC_NOTIFICATION_CONFIG_H_
#define _CC_NOTIFICATION_CONFIG_H_

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Command Class Notification- notifications configuration

// <o> Max number of notifications <1..255:1> <f.d>
// <i> Maximum number of notifications supported by application.
// <i> Default: 1
#define CC_NOTIFICATION_MAX_NOTIFICATIONS  1

// </h>
// <h> Command Class Notification - events configuration

// <o> Max number of events per notification <1..255:1> <f.d>
// <i> Maximum number of events for single notification.
// <i> Default: 1
#define CC_NOTIFICATION_MAX_EVENTS_PER_NOTIFICATION  1

// </h>

// <<< end of configuration section >>>

#endif /* _CC_NOTIFICATION_CONFIG_H_ */
