/***************************************************************************//**
 * @file
 * @brief Initialize the Silicon Labs platform integration of mbedTLS.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "sl_mbedtls.h"
#include "mbedtls/threading.h"
#if defined(SEMAILBOX_PRESENT) || defined(CRYPTOACC_PRESENT)
#include "sl_se_manager.h"
#endif
#if defined(SLI_RADIOAES_REQUIRES_MASKING)
#include "sli_radioaes_management.h"
#endif

void sl_mbedtls_init(void)
{
#if defined(SEMAILBOX_PRESENT) || defined(CRYPTOACC_PRESENT)
  /* Initialize the SE Manager including the SE lock.
     No need for critical region here since sl_se_init implements one. */
  sl_status_t ret;
  ret = sl_se_init();
  EFM_ASSERT(ret == SL_STATUS_OK);
#endif

#if defined(MBEDTLS_THREADING_C)
  mbedtls_threading_set_alt(&THREADING_InitMutex,
                            &THREADING_FreeMutex,
                            &THREADING_TakeMutexBlocking,
                            &THREADING_GiveMutex);
#endif

#if defined(SLI_RADIOAES_REQUIRES_MASKING)
  /* Initialize the RADIOAES mask value early to avoid taking the hit of
   * requesting RNG output in IRQ context. Just acquiring and releasing the
   * peripheral should ensure the mask is properly set. */
  (void) sli_radioaes_acquire();
  (void) sli_radioaes_release();
#endif
}
