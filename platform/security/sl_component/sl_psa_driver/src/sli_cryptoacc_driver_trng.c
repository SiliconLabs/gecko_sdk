/*******************************************************************************
 * @file
 * @brief Driver for TRNG randomness generation through the TRNG peripheral on
          VSE devices.
 *******************************************************************************
 * # License
 * <b>Copyright 2024 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "sli_psa_driver_features.h"

#if defined(SLI_MBEDTLS_DEVICE_VSE)

#include "psa/crypto.h"

#include "cryptoacc_management.h"
#include "sli_cryptoacc_driver_trng.h"

#include "sx_errors.h"
#include "cryptolib_types.h"
#include "sx_trng.h"
#include "sx_rng.h"
#include "sx_memcpy.h"
#include "ba431_config.h"

#include "sl_assert.h"
#include "em_device.h"

//------------------------------------------------------------------------------
// Defines

// Perform the TRNG conditioning test on startup.
#define DO_TRNG_COND_TEST (1)

// Allow performing a few retries before determining that the TRNG is in a
// seriously bad state and cannot be initialized properly.
#define MAX_INITIALIZATION_ATTEMPTS (4)

//------------------------------------------------------------------------------
// Constants

static const block_t trng_fifo_block = {
  .addr = (uint8_t *)ADDR_BA431_FIFO,
  .len = 0,
  .flags = BLOCK_S_CONST_ADDR
};

//------------------------------------------------------------------------------
// Forward Declarations

static void cryptoacc_trng_get_random_wrapper(void *unused_state,
                                              block_t output);

//------------------------------------------------------------------------------
// Global Data

const struct sx_rng sli_cryptoacc_trng_wrapper = {
  .param = NULL,
  .get_rand_blk = cryptoacc_trng_get_random_wrapper,
};

//------------------------------------------------------------------------------
// Static Function Definitions

static psa_status_t wait_until_trng_is_ready_for_sleep(void)
{
  // We do not want to risk clocking down the CRYPTOACC while the ring
  // oscillators are still spinning, since that means that they will not be
  // shut down (unless EM2 or lower is entered).
  uint32_t current_trng_status = BA431_STATE_RESET;
  while (((current_trng_status = ba431_read_status()) & BA431_STAT_MASK_STATE)
         != BA431_STATE_FIFOFULLOFF) {
    switch (current_trng_status & BA431_STAT_MASK_STATE) {
      case BA431_STATE_STARTUP:
      case BA431_STATE_RUNNING:
      case BA431_STATE_FIFOFULLON:
        // These are the only valid states that we would expect the TRNG to be
        // in now that we have read randomness from it.
        break;
      default:
        return PSA_ERROR_HARDWARE_FAILURE;
        break;
    }
  }

  // Make sure that no new alarms have been triggered while the FIFO was being
  // filled. All other (more serious) continous test failures will result in the
  // TRNG control finite state machine moving to the error state: meaning that
  // we would have already returned in the switch statement above.
  if (current_trng_status & BA431_STAT_MASK_PREALM_INT) {
    // The severity of a preliminary noise alarm is lower than other alarms that
    // will put the TRNG in an error state. Instead of (potentially) triggering
    // a system reset, we will make sure to disable the TRNG such that it needs
    // to be re-initialized before the next use: that will cause startup tests
    // to run again.
    ba431_disable_ndrng();
  }

  return PSA_SUCCESS;
}

static psa_status_t wait_until_trng_has_started(void)
{
  uint32_t ba431_status = 0;
  ba431_state_t ba431_state = BA431_STATE_RESET;

  // Poll the status until the startup routine has finished.
  do {
    ba431_status = ba431_read_status();
    ba431_state = (ba431_state_t) (ba431_status & BA431_STAT_MASK_STATE);
  } while ((ba431_state == BA431_STATE_RESET)
           || (ba431_state == BA431_STATE_STARTUP));

  // Make sure that the NIST-800-90B startup test passed (the fact that we have
  // left the startup state means that the corresponding AIS31 test also
  // passed).
  if (ba431_status & BA431_STAT_MASK_STARTUP_FAIL) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  // This would have been caught by the above startup failure check.
  EFM_ASSERT(ba431_state != BA431_STATE_ERROR);

  return PSA_SUCCESS;
}

static psa_status_t initialize_trng(void)
{
  size_t attempts_remaining = MAX_INITIALIZATION_ATTEMPTS;

  while (attempts_remaining--) {
    if (sx_trng_init(DO_TRNG_COND_TEST) != CRYPTOLIB_SUCCESS) {
      continue;
    }

    // The implementation of sx_trng_get_rand_blk() doesn't actually assert
    // that the startup check passed succesfully (only that the TRNG is no
    // longer in a reset- or startup state). Therefore, we will implement our
    // own functions for waiting until the startup has completed and then
    // getting randomness from the TRNG FIFO.
    if (wait_until_trng_has_started() != PSA_SUCCESS) {
      continue;
    }

    // When we reach this point, the TRNG has started succesfully and is ready
    // to be used.
    return PSA_SUCCESS;
  }

  // If we against all odds reach this point, we have not been able to
  // initialize the TRNG even after multiple retries.
  return PSA_ERROR_HARDWARE_FAILURE;
}

static bool trng_needs_initialization(void)
{
  // If the TRNG (NDRNG) is not enabled, it most definitely is not initialized.
  if ((ba431_read_controlreg() & BA431_CTRL_NDRNG_ENABLE) == 0u) {
    return true;
  }

  // If a full word of the conditioning (whitening) key is all zero, it probably
  // hasn't been initialized properly.
  uint32_t cond_key[4] = { 0 };
  ba431_read_conditioning_key(cond_key);
  if ((cond_key[0] == 0)
      || (cond_key[1] == 0)
      || (cond_key[2] == 0)
      || (cond_key[3] == 0)) {
    return true;
  }

  // No conditions were met, which means that the TRNG must have already been
  // initialized.
  return false;
}

static psa_status_t cryptoacc_trng_get_random(block_t output)
{
  if (trng_needs_initialization()) {
    // In addition to configuring the TRNG, this funtion will also wait until
    // the hardware is fully ready for usage.
    psa_status_t status = initialize_trng();
    if (status != PSA_SUCCESS) {
      return status;
    }
  }

  size_t n_bytes_generated = 0;
  while (n_bytes_generated < output.len) {
    // Don't attempt to read more from the TRNG FIFO than the amount of random
    // words that it currently holds.
    block_t chunk_block = block_t_convert(
      output.addr + n_bytes_generated,
      SX_MIN(output.len - n_bytes_generated,
             sizeof(uint32_t) * (ba431_read_fifolevel())));
    memcpy_blk(chunk_block, trng_fifo_block, chunk_block.len);
    n_bytes_generated += chunk_block.len;
  }

  // Potential bad states reached by the TRNG during the above randomness
  // generation will be handled by this function.
  return wait_until_trng_is_ready_for_sleep();
}

//------------------------------------------------------------------------------
// Public Function Definitions

/*
 * \brief
 *   Wrapper function for getting random data from the TRNG.
 *
 * \details
 *   Even though it is declared with a static scope, a function pointer to this
 *   function will be exposed so that it is indirectly usable for other
 *   compilation units as well.
 *
 * \note
 *   This function does not assume any responsibility to aquire and release
 *   ownership of the CRYPTOACC peripheral.
 *
 * \warning
 *   This function is called from contexts where it is not possible to return an
 *   error code. Any errors are therefore handled by resetting the system. This
 *   is deemed appropriate since a failed randomness generation may have severe
 *   security implications.
 */
static void cryptoacc_trng_get_random_wrapper(void *unused_state,
                                              block_t output)
{
  (void)unused_state;

  if (cryptoacc_trng_get_random(output) != PSA_SUCCESS) {
    EFM_ASSERT(false);
    sx_trng_apply_soft_reset();
    NVIC_SystemReset();
  }
}

psa_status_t sli_cryptoacc_trng_get_random(unsigned char *output, size_t len)
{
  psa_status_t status = cryptoacc_management_acquire();
  if (status != PSA_SUCCESS) {
    return status;
  }

  status = cryptoacc_trng_get_random(block_t_convert(output, len));
  if (status != PSA_SUCCESS) {
    // Soft reset such that the next attempt (if the function is called again)
    // is more likely to succeed.
    sx_trng_apply_soft_reset();
    cryptoacc_management_release();
    return status;
  }

  return cryptoacc_management_release();
}

#endif // SLI_MBEDTLS_DEVICE_VSE
