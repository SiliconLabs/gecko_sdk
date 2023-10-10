/***************************************************************************//**
 * @file
 * @brief Timer Windows specific code
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#include <WinError.h>
#include "app_timer.h"
#include "app_log.h"

/**************************************************************************//**
 * @addtogroup timer
 * @{
 *****************************************************************************/

// -----------------------------------------------------------------------------
// Private defines

// ID is being generated using this parameter
#define GENERATE_TIMER_ID 0ULL

// -----------------------------------------------------------------------------
// Private variables

// Start of the linked list which contains the active timers.
static app_timer_t *app_timer_head = NULL;

// -----------------------------------------------------------------------------
// Private function declarations

/***************************************************************************//**
 * Common callback
 *
 * @param[in] hwnd Required by function prototype, unused parameter
 * @param[in] uMsg Required by function prototype, unused parameter
 * @param[in] timer_id Timer id of expired timer
 * @param[in] dwTime Required by function prototype, unused parameter
 *
 * Call timer callback associated with the ID and delete timer if timer was
 * non-periodic.
 ******************************************************************************/
__attribute__((stdcall)) static void app_timer_common_callback(HWND hwnd,
                                                               UINT uMsg,
                                                               UINT_PTR timer_id,
                                                               DWORD dwTime);
/***************************************************************************//**
 * Append a timer to the end of the linked list.
 *
 * @param[in] timer Pointer to the timer handle.
 *
 * @pre Assumes that the timer is not present in the list.
 ******************************************************************************/
static void append_app_timer(app_timer_t *timer);

/***************************************************************************//**
 * Remove a timer from the linked list.
 *
 * @param[in] timer Pointer to the timer handle.
 *
 * @return Presence of the timer in the linked list.
 * @retval true  Timer was in the list.
 * @retval false Timer was not found in the list.
 ******************************************************************************/
static WINBOOL remove_app_timer(app_timer_t *timer);

/***************************************************************************//**
 * Check if timer is in the list
 *
 * @param[in] timer app_timer reference
 *
 * @returns true if the timer is in the list, flase if not
 ******************************************************************************/
static bool contains_app_timer(app_timer_t *timer);

// -----------------------------------------------------------------------------
// Private function definitions

/***************************************************************************//**
 * Common callback
 ******************************************************************************/
__attribute__((stdcall)) static void app_timer_common_callback(HWND hwnd,
                                                               UINT uMsg,
                                                               UINT_PTR timer_id,
                                                               DWORD dwTime)
{
  (void) *hwnd;
  (void) uMsg;
  (void) dwTime;
  app_timer_t *tmp_timer_ptr = app_timer_head;

  while ((NULL != tmp_timer_ptr)
         && (tmp_timer_ptr->app_timer_handle.timer_id != timer_id)) {
    tmp_timer_ptr = tmp_timer_ptr->next;
  }
  if (NULL == tmp_timer_ptr) {
    app_log_error("Timer handle %d not found." APP_LOG_NL, timer_id);
    (void)KillTimer(NULL, timer_id);
    (void)GetLastError();
  } else {
    tmp_timer_ptr->app_timer_handle.triggered = true;
    // Delete non-periodic timers
    if (false == tmp_timer_ptr->periodic) {
      (void)KillTimer(NULL, timer_id);
      (void)GetLastError();
      tmp_timer_ptr->app_timer_handle.timer_id = 0;
    }
  }
}

/***************************************************************************//**
 * Append timer
 ******************************************************************************/
static void append_app_timer(app_timer_t *timer)
{
  if (NULL != app_timer_head) {
    bool exist = false;
    app_timer_t *current = app_timer_head;
    // Find end of list.
    while (NULL != current->next) {
      current = current->next;
      if (timer == current) {
        exist = true;
        break;
      }
    }
    if (false == exist) {
      current->next = timer;
    }
  } else {
    app_timer_head = timer;
  }
  timer->next = NULL;
}

/***************************************************************************//**
 * Remove timer
 ******************************************************************************/
static WINBOOL remove_app_timer(app_timer_t *timer)
{
  app_timer_t *prev = NULL;
  app_timer_t *current = app_timer_head;

  // Find timer in list.
  while ((NULL != current) && (timer != current)) {
    prev = current;
    current = current->next;
  }

  if (timer != current) {
    // Not found.
    return false;
  }

  if (NULL != prev) {
    prev->next = timer->next;
  } else {
    app_timer_head = timer->next;
  }
  return true;
}

/***************************************************************************//**
 * Check if app timer is in the list
 ******************************************************************************/
static bool contains_app_timer(app_timer_t *timer)
{
  app_timer_t *local_timer = app_timer_head;

  while (NULL != local_timer) {
    if (timer == local_timer) {
      return true;
    }
    local_timer = local_timer->next;
  }
  return false;
}
// -----------------------------------------------------------------------------
// Public function definitions

/***************************************************************************//**
 * Timer init
 ******************************************************************************/
void app_timer_init(void)
{
  app_log_debug("Timer function intialized" APP_LOG_NL);
}

/***************************************************************************//**
 * Step
 ******************************************************************************/
void sli_app_timer_step(void)
{
  app_timer_t *tmp_timer_ptr = app_timer_head;

  MSG msg;
  memset(&msg, 0, sizeof(msg));
  while (FALSE != PeekMessage(&msg,
                              NULL, // handle to window to receive the message
                              WM_TIMER, // lowest message to examine
                              WM_TIMER, // highest message to examine
                              PM_REMOVE)) { // remove message from queue
    TranslateMessage(&msg);  // translates virtual-key codes
    DispatchMessage(&msg);   // dispatches message to windows
  }

  while (NULL != tmp_timer_ptr) {
    if (true == tmp_timer_ptr->app_timer_handle.triggered) {
      // Delete if timer is non-periodic
      if (false == tmp_timer_ptr->periodic) {
        sl_status_t status = app_timer_stop(tmp_timer_ptr);
        if (SL_STATUS_OK != status) {
          app_log_error("One-shot timer could not be cleared." APP_LOG_NL);
        }
      }
      if (NULL != tmp_timer_ptr->callback) {
        tmp_timer_ptr->callback(tmp_timer_ptr, tmp_timer_ptr->callback_data);
      }
      tmp_timer_ptr->app_timer_handle.triggered = false;
    }
    tmp_timer_ptr = tmp_timer_ptr->next;
  }
}

/***************************************************************************//**
 * Start a timer
 ******************************************************************************/
sl_status_t app_timer_start(app_timer_t *timer,
                            uint32_t timeout_ms,
                            app_timer_callback_t callback,
                            void *callback_data,
                            bool is_periodic)
{
  UINT_PTR tmp_timer_id;
  timer->callback = callback;
  timer->callback_data = callback_data;
  timer->timeout = timeout_ms;
  timer->periodic = is_periodic;
  timer->next = NULL;
  timer->app_timer_handle.triggered = false;

  // Check input parameters.
  if ((timeout_ms == 0) && is_periodic) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  if (NULL == timer) {
    return SL_STATUS_NULL_POINTER;
  }

  // Create timer
  tmp_timer_id = SetTimer(NULL,
                          GENERATE_TIMER_ID,
                          (unsigned int)timeout_ms,
                          app_timer_common_callback);
  if (0 == tmp_timer_id) {
    return SL_STATUS_FAIL;
  } else {
    timer->app_timer_handle.timer_id = tmp_timer_id;
  }

  append_app_timer(timer);
  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Stop a timer
 ******************************************************************************/
sl_status_t app_timer_stop(app_timer_t *timer)
{
  sl_status_t result = SL_STATUS_NULL_POINTER;
  WINBOOL status = false;
  if (timer == NULL) {
    return result;
  }

  if (contains_app_timer(timer)) {
    if (timer->app_timer_handle.timer_id != 0) {
      status = KillTimer(NULL, timer->app_timer_handle.timer_id);
    } else {
      status = true; // Can be stopped already either because it's one-shot and expired or by users
      result = SL_STATUS_OK;
    }

    if (false == status) {
      DWORD LastError = GetLastError();
      if (!LastError || LastError == ERROR_INVALID_WINDOW_HANDLE) {
        // Special cases on Windows
        // 0 a.k.a ERROR_SUCCESS means that the operation failed successfully.
        // ERROR_INVALID_WINDOW_HANDLE seems normal on some Windows versions if hWnd was passed as NULL
        result = SL_STATUS_OK;
      } else {
        app_log_error("Stopping timer returned with error code %lu "
                      APP_LOG_NL, LastError);
        result = SL_STATUS_FAIL;
      }
    } else {
      result = SL_STATUS_OK;
    }

    if (result == SL_STATUS_OK) {
      timer->app_timer_handle.timer_id = 0;
      (void)remove_app_timer(timer);
    }
  } else {
    if (timer->app_timer_handle.timer_id != 0) {
      (void)KillTimer(NULL, timer->app_timer_handle.timer_id);
      (void)GetLastError();
      timer->app_timer_handle.timer_id = 0;
    }
  }
  return result;
}
/** @} (end addtogroup timer) */
