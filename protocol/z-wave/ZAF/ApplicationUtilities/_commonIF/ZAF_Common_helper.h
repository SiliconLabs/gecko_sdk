/**
 * @file
 * @brief Common stuff used by apps.
 * @details It's purpose is to minimize function calls from end applications.
 *  Shouldn't be called directly from CC or utils, to avoid mutual dependencies
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */

#ifndef _ZAF_COMMON_HELPER_H_
#define _ZAF_COMMON_HELPER_H_

#include "ZW_application_transport_interface.h"
#include "FreeRTOS.h"
#include "task.h"

/**
 * @addtogroup ZAF_IF ZAF Interface
 * @{
 */

/**
 * Initializes the Z-Wave Application Framework
 *
 * This function must be invoked by end devices and portable controllers, but not Serial API.
 *
 * It initializes the following stuff:
 * - Application timer
 * - Board
 * - Application file system
 * - Power lock for FLiRS
 * - True Status
 * - Command Publisher
 * - All command classes that have registered an init function.
 * - Generates the three lists of command classes used for Node Information Frame, etc.
 *
 * @param AppTaskHandle Task handle
 * @param pAppHandles pointer to Application Handle in application
 */
void ZAF_Init(TaskHandle_t AppTaskHandle, SApplicationHandles *pAppHandles);

/**
 * Reset ZAF and command classes that have registered a reset function with a REGISTER_CC macro.
 */
void ZAF_Reset(void);

/**
 * Returns the task handle set by ZAF_Init().
 * @return Task handle.
 */
TaskHandle_t ZAF_getAppTaskHandle(void);

/**
 * Makes the node stay awake for either 2 or 10 seconds.
 *
 * For an LS (listening sleeping) node, the node will stay awake for 2 seconds. If the node supports
 * CC Wake Up, it will stay awake for 10 seconds, if CC Wake Up is active.
 *
 * For RS (reporting sleeping), the node will stay awake for 10 seconds, if CC Wake Up is active.
 */
void zaf_stay_awake(void);

/**
 * Function called when the \ref EVENT_SYSTEM_LEARNMODE_FINISHED is received
 * 
 * This function is weakly defined and can be overwritten by one command class.
 * Applications should not overwrite this function instead they should handle
 * the event.
 * CC WakeUp overwrites it.
 */
void zaf_learn_mode_finished(void);

/**
 * @} // ZAF_IF
 */

#endif /* _ZAF_COMMON_HELPER_H_ */
