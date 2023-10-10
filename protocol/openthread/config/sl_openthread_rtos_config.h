//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------
//
// <h>  Priority Configuration for OpenThread RTOS Task
// <o SL_OPENTHREAD_RTOS_TASK_PRIORITY> OpenThread task priority
// <i> Default: 24 (CMSIS-RTOS2 osPriorityNormal)
// <i> Defines OpenThread task priority. This must be a valid priority value
// <i> from CMSIS-RTOS2 osPriority_t definition.
#define SL_OPENTHREAD_RTOS_TASK_PRIORITY     (24)


// <o SL_OPENTHREAD_OS_STACK_TASK_SIZE> OpenThread stack task stack size in bytes <1000-20000>
// <i> Default: 4096
// <i> Defines the stack size of the OpenThread RTOS stack task. The value is in bytes and
// <i> and will be word aligned when it is applied at the task creation.
#define SL_OPENTHREAD_OS_STACK_TASK_SIZE 4608

// </h>
// <<< end of configuration section >>>
