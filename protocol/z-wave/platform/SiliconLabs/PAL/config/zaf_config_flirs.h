/**
 * @file
 * @copyright 2023 Silicon Laboratories Inc.
 */

#ifndef _ZAF_CONFIG_FLIRS_H_
#define _ZAF_CONFIG_FLIRS_H_

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Listening interval for FLiRS devices

// <o> Device Option mask for Frequently Listening (FLiRS) devices
// <i> Defines wakeup interval for FLiRs devices that's later used in deviceOptionMask.
// <APPLICATION_FREQ_LISTENING_MODE_250ms=> Wakes up every 250ms
// <APPLICATION_FREQ_LISTENING_MODE_1000ms=> Wakes up every 1000ms
// <i> Default: APPLICATION_FREQ_LISTENING_MODE_1000ms
#define ZAF_CONFIG_DEVICE_OPTION_MASK  APPLICATION_FREQ_LISTENING_MODE_1000ms

// </h>

// <<< end of configuration section >>>

#endif /* _ZAF_CONFIG_FLIRS_H_ */
