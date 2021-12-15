/**
 * @file
 * Offers an API for registering power locks.
 *
 * Power locks can make the application stay awake at a given power level for a given time.
 * @copyright 2018 Silicon Laboratories Inc.
 */

#ifndef ZWAVE_API_ZW_POWERMANAGER_API_H_
#define ZWAVE_API_ZW_POWERMANAGER_API_H_

#include <stdbool.h>
#include <stdint.h>

#define MAX_POWERDOWN_CALLBACKS  4

typedef enum
{
  PM_TYPE_RADIO,       //Prevents system from entering EM2
  PM_TYPE_PERIPHERAL,  //Prevents system from entering EM3
} pm_type_t;

typedef struct
{
  uint32_t dummy[10];
} SPowerLock_t;

/**
* Register a power mutex. There are two types of mutexes,
* PM_TYPE_RADIO will keep the system form going into EM2 mode,
* PM_TYPE_PHEREPHIAL will keep the system from going into EM3 mode.
*
* Must be called prior to calling any other PowerManager methods.
* Provides PowerManager with a timer for timed mutexes.
*
* @param[in]     handle             Address of a power lock.
* @param[in]     type               Type of mutex. (Prevent from entering EM2 or EM3)
*
* @return                           false if handle is NULL pointer. true otherwise.
*/
bool PM_Register (SPowerLock_t* handle, pm_type_t type);

/**
* Make the device stay awake.
*
* PM_Register() must have been invoked on the power lock before invoking this function.
*
* If invoked on an already active power lock, the timeout will be reset.
*
* @param[in]     handle             Address of a power lock.
* @param[in]     msec               Timeout value in milliseconds. If zero is given, the power lock
*                                   will stay active infinitely.
*/
void PM_StayAwake (SPowerLock_t* handle, uint32_t msec);

/**
* Cancels an active power lock.
*
* @param[in]     handle             Address of a power lock.
*/
void PM_Cancel (SPowerLock_t* handle);

#endif /* ZWAVE_API_ZW_POWERMANAGER_API_H_ */
