/***************************************************************************//**
 * @file
 * @brief Errno implementation
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

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------

#include "errno.h"
#include "cmsis_os2.h"
#include "sl_cmsis_os2_common.h"
#include <assert.h>

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief Static errno variable
 *****************************************************************************/
static errno_t __errno = ENOERROR;

/**************************************************************************//**
 * @brief Mutex for errno access
 *****************************************************************************/
static osMutexId_t __errno_mtx = NULL;

/**************************************************************************//**
 * @brief Mutex control block for errno
 *****************************************************************************/
__ALIGNED(8) static uint8_t __errno_mtx_mtx_cb[osMutexCbSize] = { 0 };

/**************************************************************************//**
 * @brief Mutex attributes for errno
 *****************************************************************************/
static const osMutexAttr_t  __errno_mtx_attr = {
  .name      = "ErrnoMutex",
  .attr_bits = osMutexRecursive,
  .cb_mem    = __errno_mtx_mtx_cb,
  .cb_size   = sizeof(__errno_mtx_mtx_cb)
};

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------
/* init errno */
void __init_errno(void)
{
  /*Init with zero*/
  __errno = ENOERROR;
  __errno_mtx = osMutexNew(&__errno_mtx_attr);
}

/*get errno*/
errno_t __get_errno(void)
{
  errno_t rval;
  assert(osMutexAcquire(__errno_mtx, osWaitForever) == osOK);
  rval = __errno;
  assert(osMutexRelease(__errno_mtx) == osOK);
  return rval;
}

/*set errno*/
void __set_errno(const errno_t errcode)
{
  assert(osMutexAcquire(__errno_mtx, osWaitForever) == osOK);
  __errno = errcode;
  assert(osMutexRelease(__errno_mtx) == osOK);
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------
