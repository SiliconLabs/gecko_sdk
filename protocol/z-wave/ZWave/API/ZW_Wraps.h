/**
 * @file
 * A module to wrap small functions of the FreeRTOS and other platform related
 * functions and expose it to the user.
 *
 * Certain wrapped functions are depedent of the state of the scheduler.
 *
 * @copyright 2021 Silicon Laboratories Inc.
 */

#ifndef __ZW_WRAPS_H__
#define __ZW_WRAPS_H__

/****************************************************************************
 * INCLUDE FILES
 ***************************************************************************/

#include <ZW_global_definitions.h>
#include <ZW_typedefs.h>

/****************************************************************************
 * CONFIGURATIONS*
 ***************************************************************************/

/****************************************************************************
 * DEFINITIONS, TYPEDEF and CONSTANTS
 ***************************************************************************/

/****************************************************************************
 * MACROS*
 ***************************************************************************/

/****************************************************************************
 * EXTERNAL VARIABLES*
 ***************************************************************************/

/****************************************************************************
 * ENUMERATIONS
 ***************************************************************************/

/****************************************************************************
 * STATIC CONTROLLING FUNCTIONS OF DUT
 ***************************************************************************/

/****************************************************************************
 * API FUNCTIONS
 ***************************************************************************/

/**
 * A non-blocking in-line delay that wraps the vTaskDelay() of FreeRTOS.
 *
 * @param ms The delay duration in ms. (Valid range 0 - 300000 (5 minutes))
 * @return Code_Fail_NotAllowed if called before the scheduler is running.
 *         Code_Fail_InvalidParameter if called with ms being out of bounds. (@see ReturnCode_t)
 */
ReturnCode_t ZW_delay_ms(uint32_t ms);

/****************************************************************************
 * THREAD FUNCTION*
 ***************************************************************************/

#endif // __ZW_WRAPS_H__
