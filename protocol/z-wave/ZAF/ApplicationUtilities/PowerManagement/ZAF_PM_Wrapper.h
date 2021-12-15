/**
 * @file
 * @brief Power Management Wrapper used by framework. Represents the interface for PM protocol module
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */

#ifndef ZAF_PM_WRAPPER_H_
#define ZAF_PM_WRAPPER_H_

#include <stdint.h>
#include <PowerManager.h>

/**
* An application API interface for the power manager API
* PM_TYPE_RADIO will keep the system form going into EM2 mode,
* PM_TYPE_PHEREPHIAL will keep the system from going into EM3 mode.
*
* Must be called prior to calling any other PowerManager methods.
* Provides PowerManager with a timer for timed mutexes.
*
* @param[in]     handle             Pointer to struct containing power lock.
* @param[in]     type               Type of mutex. (Prevent from entering EM2 or EM3)
*/
void ZAF_PM_Register (SPowerLock_t* handle, pm_type_t type);

/**
* Make the device stay awake.
*
* ZAF_PM_Register() must have been invoked on the power lock before invoking this function.
*
* If invoked on an already active power lock, the timeout will be reset.
*
* @param[in]     handle             Address of a power lock.
* @param[in]     msec               Timeout value in milliseconds. If zero is given, the power lock
*                                   will stay active infinitely.
*/
void ZAF_PM_StayAwake (SPowerLock_t* handle, unsigned int msec);

/**
* Cancels an active power lock.
*
* @param[in]     handle             Address of a power lock.
*/
void ZAF_PM_Cancel (SPowerLock_t* handle);

/**
* Cancels an active power lock from an interrupt service routine.
*
* @param[in]     handle             Address of a power lock.
*/
void ZAF_PM_CancelFromISR (SPowerLock_t* handle);

/**
 * Registers functions that will be called as the last step just before the
 * chip enters EM4 hibernate.
 *
 * NB: When the function is called the OS tick has been disabled and the FreeRTOS
 *     scheduler is no longer running. OS features like events, queues and timers
 *     are therefore unavailable and must not be called from the callback function.
 *
 *     The callback functions can be used to set pins and write to retention RAM.
 *     Do NOT try to write to the NVM3 file system.
 *
 * The maximum number of functions that can be registered is given by the macro
 * MAX_POWERDOWN_CALLBACKS in ZW_PowerManager_api.h
 *
 * @param callback Function to call on power down.
 */
void ZAF_PM_SetPowerDownCallback(void (*callback)(void));

/**
* Update the controller node information in the nodes file system
*
* @param[in]     forced  if true force node information update. else let the protocol decide to update or not
*/
void ZW_UpdateCtrlNodeInformation_API_IF (uint8_t forced);

#endif /* ZAF_PM_WRAPPER_H_*/
