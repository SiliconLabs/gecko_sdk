/***************************************************************************//**
 * @file
 * @brief Button Driver
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "sl_button.h"
#include <stddef.h>

sl_status_t sl_button_init(const sl_button_t *handle)
{
  if (handle->init != NULL) {
    return handle->init(handle);
  } else {
    return SL_STATUS_NULL_POINTER;
  }
}

sl_button_state_t sl_button_get_state(const sl_button_t *handle)
{
  if (handle->get_state != NULL) {
    return handle->get_state(handle);
  } else {
    return (sl_button_state_t)BUTTON_ERROR;
  }
}

void sl_button_poll_step(const sl_button_t *handle)
{
  if (handle->poll != NULL) {
    handle->poll(handle);
  }
}

void sl_button_enable(const sl_button_t *handle)
{
  if (handle->enable != NULL) {
    handle->enable(handle);
  }
}

void sl_button_disable(const sl_button_t *handle)
{
  if (handle->disable != NULL) {
    handle->disable(handle);
  }
}

SL_WEAK void sl_button_on_change(const sl_button_t *handle)
{
  (void)handle;
}
