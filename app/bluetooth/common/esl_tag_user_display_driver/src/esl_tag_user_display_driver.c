/***************************************************************************//**
 * @file
 * @brief WSTK display driver implementation for user defined displays.
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/
#include <stdint.h>
#include <stdarg.h>
#include "esl_tag_log.h"
#include "esl_tag_display.h"
#include "esl_tag_image_core.h"
#include "esl_tag_user_display_driver.h"

sl_status_t esl_user_display_write(int param_count, ...)
{
  // Please note that implementing this function is mandatory.

  // Declaring pointer to the argument list
  va_list     ptr;
  // Default status is SL_STATUS_IN_PROGRESS, set to SL_STATUS_OK once the
  // display data has been written successfully.
  sl_status_t status = SL_STATUS_IN_PROGRESS;
  // Variables for va parameters
  uint8_t     display_index;  // 2nd parameter
  uint8_t     image_index;    // 3rd parameter

  // User display write: Invalid parameters!
  sl_bt_esl_assert(param_count == ESL_DISPLAY_WRITE_FUNC_PARAMETERS_COUNT);

  // Initializing argument to the list pointer
  va_start(ptr, param_count);

  // Accessing variables (after each call to va_arg our ptr points to next one)
  display_index = (uint8_t)va_arg(ptr, int);
  image_index   = (uint8_t)va_arg(ptr, int);

  // end argument list traversal
  va_end(ptr);

  /////////////////////////////////////////////////////////////////////////////
  // Put your additional display driver write code here!                     //
  // This is called by ESL display core on appropriate request coming from   //
  // the ESL Access Point the ESL Tag is synchronized to.                    //
  // Please do not call any long term blocking functions from here!          //
  // If the write goes slowly on your display, and especially, if it needs   //
  // a sequence of multiple transactions which takes long time, then please  //
  // do the scheduling only from here.                                       //
  // Do not forget to set result = SL_STATUS_OK after successful operation,  //
  // including the scheduling only, if it's the case.                        //
  /////////////////////////////////////////////////////////////////////////////

  return status;
}

sl_status_t esl_user_display_init(int param_count, ...)
{
  /////////////////////////////////////////////////////////////////////////////
  // Please note that implementing this function can be omitted if unnecessary
  // - in that particular case just pass a NULL ptr to the esl_display_create()
  // call in the appropriate parameter.
  /////////////////////////////////////////////////////////////////////////////

  // Declaring pointer to the argument list
  va_list     ptr;
  // Default status is SL_STATUS_FAIL, set to SL_STATUS_OK once the display
  // has been initialized successfully.
  sl_status_t status = SL_STATUS_FAIL;
  // Variable for va parameter
  uint8_t     index;  // 2nd parameter

  // User display init: Invalid parameters!
  sl_bt_esl_assert(param_count == ESL_DISPLAY_INIT_FUNC_PARAMETERS_COUNT);

  // Initializing argument to the list pointer
  va_start(ptr, param_count);
  // Extract the index value (the only extra parameter)
  index = (uint8_t)va_arg(ptr, int);
  va_end(ptr);

  /////////////////////////////////////////////////////////////////////////////
  // Put your additional display driver init code here!                      //
  // This is called once, during the invocation of esl_display_create().     //
  // Temporary blocking functions are allowed to be called from here yet not //
  // recommended.                                                            //
  // If the display needs pre-initialization - especially if it takes longer //
  // time to finish (e.g. internal boot of the display or a clock to become  //
  // stable) - then it is highly recommended to take those pre-steps in the  //
  // callback called app_init(), instead - and take only the post-init steps //
  // here, if there's any.                                                   //
  // Do not forget to set result = SL_STATUS_OK after successful init.       //
  /////////////////////////////////////////////////////////////////////////////

  return status;
}
