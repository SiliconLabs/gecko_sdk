/***************************************************************************//**
 * @file
 * @brief SL_ML_FFT
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
#include "microfrontend/sl_ml_fft.h"
#define FIXED_POINT 16
#include "kiss_fft.h"
#include "tools/kiss_fftr.h"

/**************************************************************************//**
 * Compute real FFT
 *****************************************************************************/
void sli_ml_fft_compute(struct sli_ml_fft_state* state, const int16_t* input,
                int input_scale_shift) {
  const size_t input_size = state->input_size;
  const size_t fft_size = state->fft_size;

  int16_t* fft_input = state->input;

  // Scale input by the given shift.
  size_t i;
  for (i = 0; i < input_size; ++i) {
    fft_input[i] = static_cast<int16_t>(static_cast<uint16_t>(input[i])
                                        << input_scale_shift);
  }

  // Zero out whatever else remains in the top part of the input.
  for (; i < fft_size; ++i) {
    fft_input[i] = 0;
  }

  // Apply the FFT.
  kiss_fftr(reinterpret_cast<kiss_fftr_cfg>(state->scratch),
            state->input,
            reinterpret_cast<kiss_fft_cpx*>(state->output));
}

/**************************************************************************//**
 * Initialize FFT state
 *****************************************************************************/
sl_status_t sli_ml_fft_init(struct sli_ml_fft_state* state, size_t input_size) {
  state->input_size = input_size;
  state->fft_size = 1;
  while (state->fft_size < state->input_size) {
    state->fft_size <<= 1;
  }

  state->input = reinterpret_cast<int16_t*>(malloc(state->fft_size * sizeof(*state->input)));
  if (state->input == nullptr) {
    return SL_STATUS_ALLOCATION_FAILED;
  }

  state->output = reinterpret_cast<complex_int16_t*>(malloc((state->fft_size / 2 + 1) * sizeof(*state->output) * 2));
  if (state->output == nullptr) {
    return SL_STATUS_ALLOCATION_FAILED;
  }

  // Ask kissfft how much memory it wants.
  size_t scratch_size = 0;
  kiss_fftr_cfg kfft_cfg = kiss_fftr_alloc(state->fft_size, 0, nullptr, &scratch_size);
  if (kfft_cfg != nullptr) {
    return SL_STATUS_ALLOCATION_FAILED;
  }
  state->scratch = malloc(scratch_size);
  if (state->scratch == nullptr) {
    return SL_STATUS_ALLOCATION_FAILED;
  }
  state->scratch_size = scratch_size;
  // Let kissfft configure the scratch space we just allocated
  kfft_cfg = kiss_fftr_alloc(state->fft_size, 0, state->scratch, &scratch_size);
  if (kfft_cfg != state->scratch) {
    return SL_STATUS_ALLOCATION_FAILED;
  }
  return SL_STATUS_OK;
}

void sli_ml_fft_deinit(struct sli_ml_fft_state* state) {
  free(state->input);
  free(state->output);
  free(state->scratch);
}

/**************************************************************************//**
 * Clear FFT buffers
 *****************************************************************************/
void sli_ml_fft_reset(struct sli_ml_fft_state* state){
  memset(state->input, 0, state->fft_size * sizeof(*state->input));
  memset(state->output, 0, (state->fft_size / 2 + 1) * sizeof(*state->output));
}
