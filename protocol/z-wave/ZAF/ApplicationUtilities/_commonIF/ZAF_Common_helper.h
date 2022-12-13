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
 * @param pAppProtocolConfig Protocol Configuration struct
 * @param AppTaskHandle Task handle
 * @param pAppHandles pointer to Application Handle in application
 */
void ZAF_Init(SProtocolConfig_t const * const pAppProtocolConfig, TaskHandle_t AppTaskHandle, SApplicationHandles *pAppHandles);

/**
 * Reset ZAF and command classes that have registered a reset function with a REGISTER_CC macro.
 */
void ZAF_Reset(void);

/**
 * Returns the task handle set by ZAF_Init().
 * @return Task handle.
 */
TaskHandle_t ZAF_getAppTaskHandle();

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
 * Reboot into the bootloader to install the new image
 *
 * The function should only be called either after successful OTA image update, or FW update
 * activation set command is received
 */
void ZAF_bootloader_reboot_and_install(void);

/**
 * @} // ZAF_IF
 */

#endif /* _ZAF_COMMON_HELPER_H_ */
