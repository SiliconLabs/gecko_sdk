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
#include "sl_assert.h"
#include "mbedtls/build_info.h"
#if !defined(SL_TRUSTZONE_NONSECURE)
#if defined(SEMAILBOX_PRESENT) || defined(CRYPTOACC_PRESENT)
#include "sl_se_manager.h"
#endif
#if defined(CRYPTOACC_PRESENT) && (_SILICON_LABS_32B_SERIES_2_CONFIG > 2)
  #include "cryptoacc_management.h"
#endif
#endif // #if !defined(SL_TRUSTZONE_NONSECURE)

#if defined(MBEDTLS_THREADING_ALT) && defined(MBEDTLS_THREADING_C)
#include "mbedtls/threading.h"
#if defined(MBEDTLS_PSA_CRYPTO_C)
#include "cmsis_os2.h"
#include <stdbool.h>
static volatile bool mbedtls_psa_slots_mutex_inited = false;

/**
 * \brief          Lock all task switches
 *
 * \return         Previous lock state
 *
 */
static inline int32_t lock_task_switches(void)
{
  int32_t kernel_lock_state = 0;
  osKernelState_t kernel_state = osKernelGetState();
  if (kernel_state != osKernelInactive && kernel_state != osKernelReady) {
    kernel_lock_state = osKernelLock();
  }
  return kernel_lock_state;
}

/**
 * \brief          Restores the previous lock state
 */
static inline void restore_lock_state(int32_t kernel_lock_state)
{
  osKernelState_t kernel_state = osKernelGetState();
  if (kernel_state != osKernelInactive && kernel_state != osKernelReady) {
    if (osKernelRestoreLock(kernel_lock_state) < 0) {
      EFM_ASSERT(false);
    }
  }
}

#endif // defined(MBEDTLS_PSA_CRYPTO_C)
#endif // defined(MBEDTLS_THREADING_ALT) && defined(MBEDTLS_THREADING_C)

void sl_mbedtls_init(void)
{
#if !defined(SL_TRUSTZONE_NONSECURE)

#if defined(SEMAILBOX_PRESENT) || defined(CRYPTOACC_PRESENT)
  /* Initialize the SE Manager including the SE lock.
     No need for critical region here since sl_se_init implements one. */
  sl_status_t ret;
  ret = sl_se_init();
  EFM_ASSERT(ret == SL_STATUS_OK);
#endif

#if defined(CRYPTOACC_PRESENT) && (_SILICON_LABS_32B_SERIES_2_CONFIG > 2)
  // Set up SCA countermeasures in hardware
  cryptoacc_initialize_countermeasures();
#endif // SILICON_LABS_32B_SERIES_2_CONFIG > 2

#endif // #if !defined(SL_TRUSTZONE_NONSECURE)

#if defined(MBEDTLS_THREADING_ALT) && defined(MBEDTLS_THREADING_C)
  mbedtls_threading_set_alt(&THREADING_InitMutex,
                            &THREADING_FreeMutex,
                            &THREADING_TakeMutexBlocking,
                            &THREADING_GiveMutex);
  #if defined(MBEDTLS_PSA_CRYPTO_C)
  // Initialize mutex for PSA slot access in psa_crypto_slot_management.c
  if (!mbedtls_psa_slots_mutex_inited) {
    int32_t kernel_lock_state = lock_task_switches();
    if (!mbedtls_psa_slots_mutex_inited) {
      mbedtls_mutex_init(&mbedtls_psa_slots_mutex);
      mbedtls_psa_slots_mutex_inited = true;
    }
    restore_lock_state(kernel_lock_state);
  }
  #endif // #if defined(MBEDTLS_PSA_CRYPTO_C)
#endif // #if defined(MBEDTLS_THREADING_ALT) && defined(MBEDTLS_THREADING_C)
}
