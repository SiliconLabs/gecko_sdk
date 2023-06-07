/**
 * @file
 * A helper API for Task creation for the user domain and also a wrapper module
 * for the task creation functions of FreeRTOS.
 *
 * This module is used to control and limit the use of task creation by the user
 * so to accommodate easy backward compatibility in the future.
 *
 * @attention This module is limited to when the RTOS Scheduler is not running
 *
 * @copyright 2020 Silicon Laboratories Inc.
 */

#ifndef _USER_TASK_API_H_
#define _USER_TASK_API_H_

#include <ZW_typedefs.h>
#include <ZW_application_transport_interface.h>

/**
 * @addtogroup ZWaveAPI
 * @{
 * @addtogroup UserTask Z-Wave User Task API
 * @{
 */

/**
 * @brief A buffer structure to allocate the needed memory for a task in user space.
 *
 * The stack size is not fixed, but limited to between @ref TASK_STACK_SIZE_MAX
 * and @ref TASK_STACK_SIZE_MIN.
 * The actual size chosen must be set in stackBufferLength
 * The buffers must be allocated elsewhere, since this structure does not
 * allocate any space, but holds the pointers to the buffers
 */
typedef struct {
  StaticTask_t*  taskBuffer;         ///< Memory needed by the Task for internal states. Pointer to buffer
  uint8_t*       stackBuffer;        ///< Pointer to a statically allocated stack-buffer-array for the task. Pointer to buffer
  uint16_t       stackBufferLength;  ///< This is measured in bytes and is preferably a multiple of 4, or it will be rounded down
} ZW_UserTask_Buffer_t;

typedef enum {
  USERTASK_PRIORITY_BACKGROUND = 0, ///< Right above idle priority. Good for HMI and worker threads
  USERTASK_PRIORITY_NORMAL,         ///< The default 'APP'-task priority
  USERTASK_PRIORITY_HIGHEST,        ///< High priority UserTask. Good for handling interrupts requests.
} ZW_UserTask_Priority_t;

typedef struct {
  TaskFunction_t         pTaskFunc;      ///< The function of the task (Invalid parameter if NULL)
  char*                  pTaskName;      ///< The name of the task. (Max characters = configMAX_TASK_NAME_LEN). NULL allowed
  void*                  pUserTaskParam; ///< Any parameter variable of own choice that is casted as (void*). Can be NULL
  ZW_UserTask_Priority_t priority;       ///< The desired priority of the task.
  ZW_UserTask_Buffer_t*  taskBuffer;     ///< The buffer collection for the task. @see @ref ZW_UserTask_Buffer_t for more info.
} ZW_UserTask_t;

/**
 * Return code used by the functions in this module.
 *
 */
typedef enum {
  Code_Success = 0,           ///< Success.
  Code_Fail_Unknown,          ///< Default failed code with no helping indication. 
  Code_Fail_NoMemory,         ///< Failed due to lack of memory.
  Code_Fail_LimitReached,     ///< A set limit is reached for this operation.
  Code_Fail_NotFound,         ///< A specific entity could not be found.
  Code_Fail_Suspended,        ///< The operation or the entire module is globally suspended and cannot be utilized at this point in time.
  Code_Fail_InvalidState,     ///< Not in an appropriate state for this call.
  Code_Fail_InvalidOperation, ///< This operation can not be allowed at this point.
  Code_Fail_InvalidParameter, ///< Wrong/invalid input parameters.
  Code_DependencyUnavailable, ///< A required resource or dependency that this operation relies on was not setup or available. Perhaps wrong initialization order.
  Code_Fail_Busy,             ///< A resource needed by this operation or call is busy. Try again later. Potential racing condition or untimely action.
  Code_Fail_Timeout,          ///< Failed due to timeout.
  Code_Fail_Driver,           ///< Error occurred at the driver level.
  Code_Fail_NotImplemented,   ///< This operation is not supported due to limited implementation or need.
  Code_Fail_NotAllowed,       ///< This operation cannot be performed, since it is blocked or not allowed.
} ReturnCode_t;

/**
 * @brief Initializes this module.
 * @attention Should not be used directly.
 *
 * Return Returns ReturnCode_t. @see See @ref ReturnCode_t for more info.
 */
ReturnCode_t ZW_UserTask_Init(void);

/**
 * @brief Used to create user application level tasks.
 *
 * @param[in] task The task definition as input. @see See @ref ZW_UserTask_t for more info.
 * @param[out] xHandle Used to return the task handle. Can be NULL
 * Return Returns ReturnCode_t. See ReturnCode_t for more info.
 */
ReturnCode_t ZW_UserTask_CreateTask(ZW_UserTask_t* task, TaskHandle_t* xHandle);

/**
 * @brief Used to create the main application task at highest UserTask priority
 *
 * This function further registers Queue Notification Bit Numbers so that an association is created between
 * the bit number and the event handle to invoke for that event, when it occurs.
 *
 * This function should only be called once, or false is returned
 *
 * @attention This task is the only UserTask that should use the ZAF API functions.
 * Accessing the ZAF API functions from any other ZW_UserTask.h generated tasks
 * will lead to undefined behavior
 *
 * @param appTaskFunc Application task that will be triggered by FreeRTOS. (function pointer)
 * @param iZwRxQueueTaskNotificationBitNumber The bit number set by Protocol when a message has been put on the ZW Rx queue.
 *        (Receiving @ref EAPPLICATIONEVENT_ZWRX events)
 * @param iZwCommandStatusQueueTaskNotificationBitNumber The bit number Set by Protocol when a message has been put on the ZW command status queue.
 *        (Receiving @ref EAPPLICATIONEVENT_ZWCOMMANDSTATUS events)
 * @param pProtocolConfig Pointer to a statically allocated Protocol Config structure. @see SProtocolConfig_t
 * @return true if the main APP task was created successfully, false if not.
 */
bool ZW_UserTask_ApplicationRegisterTask(  VOID_CALLBACKFUNC(appTaskFunc)(SApplicationHandles*),
                                           uint8_t iZwRxQueueTaskNotificationBitNumber,
                                           uint8_t iZwCommandStatusQueueTaskNotificationBitNumber,
                                           const SProtocolConfig_t * pProtocolConfig);

/**
 * @}
 * @}
 */

#endif // _USER_TASK_API_H_
