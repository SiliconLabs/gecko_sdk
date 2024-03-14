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

#if (SL_VSE_BUFFER_TRNG_DATA_DURING_SLEEP)
  #include "sl_component_catalog.h"
  #if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
    #include "sl_power_manager.h"
  #else
    #error "The 'Power Manager' component must be included in the project"
  #endif // SL_CATALOG_POWER_MANAGER_PRESENT
#endif // SL_VSE_BUFFER_TRNG_DATA_DURING_SLEEP

//------------------------------------------------------------------------------
// Defines

// Perform the TRNG conditioning test on startup.
#define DO_TRNG_COND_TEST (1)

// Allow performing a few retries before determining that the TRNG is in a
// seriously bad state and cannot be initialized properly.
#define MAX_INITIALIZATION_ATTEMPTS (4)

// Magic word written to the random data buffer in RAM. Used as a basic sanity
// check to make sure that the data actually has been retained during sleep.
#define BUFFERED_RANDOMNESS_MAGIC_WORD (0xF55E0830)

//------------------------------------------------------------------------------
// Forward Declarations

static void cryptoacc_trng_get_random_wrapper(void *unused_state,
                                              block_t output);

#if SL_VSE_BUFFER_TRNG_DATA_DURING_SLEEP

static void store_trng_fifo_data(sl_power_manager_em_t from,
                                 sl_power_manager_em_t to);

#endif // SL_VSE_BUFFER_TRNG_DATA_DURING_SLEEP

//------------------------------------------------------------------------------
// Static Constants

static const block_t trng_fifo_block = {
  .addr = (uint8_t *)ADDR_BA431_FIFO,
  .len = 0,
  .flags = BLOCK_S_CONST_ADDR,
};

#if SL_VSE_BUFFER_TRNG_DATA_DURING_SLEEP

static const sl_power_manager_em_transition_event_info_t buffer_trng_data_event = {
  .event_mask = SL_POWER_MANAGER_EVENT_TRANSITION_ENTERING_EM2
                | SL_POWER_MANAGER_EVENT_TRANSITION_ENTERING_EM3,
  .on_event = store_trng_fifo_data,
};

#endif // SL_VSE_BUFFER_TRNG_DATA_DURING_SLEEP

//------------------------------------------------------------------------------
// Global Constants

const struct sx_rng sli_cryptoacc_trng_wrapper = {
  .param = NULL,
  .get_rand_blk = cryptoacc_trng_get_random_wrapper,
};

//------------------------------------------------------------------------------
// Static Variables

#if SL_VSE_BUFFER_TRNG_DATA_DURING_SLEEP

static sl_power_manager_em_transition_event_handle_t buffer_trng_handle = { 0 };

// Keep all of the buffered randomness in the .bss section. Powering down the
// RAM bank containing this section would be a clear user error. We prefer to
// not use the heap for this data since the heap section expands (based on the
// linkerfile) into RAM banks that technically would be OK to power down.
static uint32_t buffered_randomness[SL_VSE_MAX_TRNG_WORDS_BUFFERED_DURING_SLEEP + 1]
  = { 0 };
static size_t n_buffered_random_bytes = 0;

#endif // SL_VSE_BUFFER_TRNG_DATA_DURING_SLEEP

//------------------------------------------------------------------------------
// Static Function Definitions

#if SL_VSE_BUFFER_TRNG_DATA_DURING_SLEEP

/*
 * \brief
 *   Callback function for buffering all bytes currently in the TRNG FIFO.
 *
 * \details
 *   Will be called by the Power Manager on EM2/EM3 entry. Before this function
 *   returns, it will unsubscribe to the Power Manager event that caused it to
 *   trigger.
 *
 * \attention
 *   This function will disable the TRNG (NDRBG).
 */
static void store_trng_fifo_data(sl_power_manager_em_t from,
                                 sl_power_manager_em_t to)
{
  (void)to;
  (void)from;

  // It should be safe to assume that the CRYPTOACC resource won't be acquired
  // by anyone when we're entering EM2/EM2.
  if (cryptoacc_management_acquire() != PSA_SUCCESS) {
    return;
  }

  // We don't want the TRNG to start refilling the FIFO after we've read all of
  // the remaining data (since we'll necessarily go below the refill threshold).
  ba431_disable_ndrng();

  block_t buffered_randomness_block =
    block_t_convert(buffered_randomness,
                    SX_MIN(sizeof(uint32_t) * ba431_read_fifolevel(),
                           SL_VSE_MAX_TRNG_WORDS_BUFFERED_DURING_SLEEP * sizeof(uint32_t)));

  memcpy_blk(buffered_randomness_block,
             trng_fifo_block,
             buffered_randomness_block.len);

  if (cryptoacc_management_release() != PSA_SUCCESS) {
    return;
  }

  n_buffered_random_bytes = buffered_randomness_block.len;

  // Write a magic word to the end of the RAM buffer. This will be checked
  // before the buffered data is used, as a basic sanity check that the data was
  // actually retained in EM2/EM3.
  buffered_randomness[SL_VSE_MAX_TRNG_WORDS_BUFFERED_DURING_SLEEP]
    = BUFFERED_RANDOMNESS_MAGIC_WORD;

  // We are no longer interested in knowing if the device goes to sleep now that
  // we have buffered the TRNG data.
  sl_power_manager_unsubscribe_em_transition_event(&buffer_trng_handle);
}

#endif // SL_VSE_BUFFER_TRNG_DATA_DURING_SLEEP

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
    // that the startup check passed successfully (only that the TRNG is no
    // longer in a reset- or startup state). Therefore, we will implement our
    // own functions for waiting until the startup has completed and then
    // getting randomness from the TRNG FIFO.
    if (wait_until_trng_has_started() != PSA_SUCCESS) {
      continue;
    }

    // When we reach this point, the TRNG has started successfully and is ready
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
  EFM_ASSERT(!(output.flags & BLOCK_S_CONST_ADDR));

  #if SL_VSE_BUFFER_TRNG_DATA_DURING_SLEEP
  // Service as much of the request as possible from the already collected
  // randomness which was buffered when EM2/EM3 was entered previously.
  if ((n_buffered_random_bytes > 0)
      && (buffered_randomness[SL_VSE_MAX_TRNG_WORDS_BUFFERED_DURING_SLEEP]
          == BUFFERED_RANDOMNESS_MAGIC_WORD)) {
    block_t chunk_block = block_t_convert(output.addr,
                                          SX_MIN(output.len,
                                                 n_buffered_random_bytes));
    uint8_t *start_of_unused_randomness
      = (uint8_t *)buffered_randomness
        + SL_VSE_MAX_TRNG_WORDS_BUFFERED_DURING_SLEEP * sizeof(uint32_t)
        - n_buffered_random_bytes;
    block_t buffered_randomness_block =
      block_t_convert(start_of_unused_randomness, n_buffered_random_bytes);
    memcpy_blk(chunk_block, buffered_randomness_block, chunk_block.len);

    n_buffered_random_bytes -= chunk_block.len;
    output.len -= chunk_block.len;
    output.addr += chunk_block.len;

    if (n_buffered_random_bytes == 0) {
      // Remove the magic word from RAM.
      buffered_randomness[SL_VSE_MAX_TRNG_WORDS_BUFFERED_DURING_SLEEP] = 0;
    }
    if (output.len == 0) {
      return PSA_SUCCESS;
    }
  }
  #endif // SL_VSE_BUFFER_TRNG_DATA_DURING_SLEEP

  if (trng_needs_initialization()) {
    // In addition to configuring the TRNG, this function will also wait until
    // the hardware is fully ready for usage.
    psa_status_t status = initialize_trng();
    if (status != PSA_SUCCESS) {
      return status;
    }

    #if SL_VSE_BUFFER_TRNG_DATA_DURING_SLEEP
    // Now that we have initialized the TRNG, we know that its FIFO level will
    // never go below the threshold level (outside of the duration of this
    // function). In order to avoid wasting already generated random words, we
    // will now register a callback function for storing randomness on EM2/EM3
    // entry.
    sl_power_manager_subscribe_em_transition_event(&buffer_trng_handle,
                                                   &buffer_trng_data_event);
    #endif // SL_VSE_BUFFER_TRNG_DATA_DURING_SLEEP
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
  psa_status_t status = wait_until_trng_is_ready_for_sleep();
  if (status != PSA_SUCCESS) {
    return status;
  }

  return PSA_SUCCESS;
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
 *   This function does not assume any responsibility to acquire and release
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
