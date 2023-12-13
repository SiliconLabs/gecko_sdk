/***************************************************************************//**
 * @file
 * @brief Silicon Labs initialization functions for TensorFlow Light Micro.
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
#if defined __has_include

#if __has_include("sl_tflite_micro_model.h")
  #define HAS_TFLITE_MICRO_FLATBUFFER_IN_CONFIGURATION
#include "sl_tflite_micro_model.h"
#include "sl_tflite_micro_opcode_resolver.h"
#else
  #define sl_tflite_model_array   nullptr
#endif //__has_include("sl_tflite_micro_model.h")

#if __has_include("sl_tflite_micro_model_parameters.h")
#include "sl_tflite_micro_model_parameters.h"
#endif //__has_include("sl_tflite_micro_model_parameters.h")

#endif //__has_include

#include "sl_tflite_micro_init.h"
#include "sl_tflite_micro_config.h"
#include "sl_tflite_micro_debug_log.h"
#include "tensorflow/lite/micro/tflite_bridge/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "em_common.h"
#include "em_assert.h"
#include "sl_memory.h"
#include <new>

// Set arena size
#if (defined(SL_TFLITE_MODEL_RUNTIME_MEMORY_SIZE) && (SL_TFLITE_MICRO_ARENA_SIZE == 0))
// Use value from model parameters
  #define ARENA_SIZE SL_TFLITE_MODEL_RUNTIME_MEMORY_SIZE
#else
// Use value from configuration
  #define ARENA_SIZE SL_TFLITE_MICRO_ARENA_SIZE
#endif // SL_TFLITE_MODEL_RUNTIME_MEMORY_SIZE

#if SL_TFLITE_MICRO_INTERPRETER_INIT_ENABLE && defined(HAS_TFLITE_MICRO_FLATBUFFER_IN_CONFIGURATION)

#if (ARENA_SIZE == 0)
#warning "You have to configure the arena size in sl_tflite_micro_init_config.h"
#elif (ARENA_SIZE < -1)
#warning "Undefined arena size. Please set the arena size to a positive value or -1."
#endif // ARENA_SIZE == 0

#endif // SL_TFLITE_MICRO_INTERPRETER_INIT_ENABLE && defined(HAS_TFLITE_MICRO_FLATBUFFER_IN_CONFIGURATION)

#ifndef SL_TFLITE_MICRO_MODEL_ARRAY
#define SL_TFLITE_MICRO_MODEL_ARRAY sl_tflite_model_array
#endif

/***************************************************************************//**
 * @brief
 *  The tensor arena buffer used by TensorFlow Lite Micro.
 ******************************************************************************/
#if SL_TFLITE_MICRO_INTERPRETER_INIT_ENABLE && defined(HAS_TFLITE_MICRO_FLATBUFFER_IN_CONFIGURATION)
#if (ARENA_SIZE > 0) // Use arena size from configuration
static uint8_t tensor_arena[ARENA_SIZE] SL_ATTRIBUTE_ALIGN(16);
#elif (ARENA_SIZE == -1) // Use arena size which is calculated runtime
static uint8_t* tensor_arena = nullptr;
#endif

#endif

/***************************************************************************//**
 *  @brief The TensorFlow Lite Micro error reporter created by the init function.
 ******************************************************************************/
static tflite::ErrorReporter *sl_tflite_micro_error_reporter = nullptr;

/***************************************************************************//**
 *  @brief The TensorFlow Lite Micro interpreter created by the init function.
 ******************************************************************************/
static tflite::MicroInterpreter *sl_tflite_micro_interpreter = nullptr;

/***************************************************************************//**
 *  @brief A pointer to the input tensor, set by the init function.
 ******************************************************************************/
static TfLiteTensor* sl_tflite_micro_input_tensor = nullptr;

/***************************************************************************//**
 *  @brief A pointer to the output tensor, set by the init function.
 ******************************************************************************/
static TfLiteTensor* sl_tflite_micro_output_tensor = nullptr;

sl_status_t sl_tflite_micro_estimate_arena_size(const tflite::Model* model, const tflite::MicroOpResolver &opcode_resolver, size_t* estimated_size)
{
  size_t upper_limit = sl_memory_get_heap_region().size - 8 * 1024;
  size_t lower_limit = 2048;

  int last_working_buffer_size = -1;
  bool current_debug_log_status = sl_tflite_micro_is_debug_log_enabled();
  // Buffer for "placement new", to reduce mallocs (https://en.cppreference.com/w/cpp/language/new#Placement_new)
  uint8_t dummy_interpreter_buffer[sizeof(tflite::MicroInterpreter)] alignas(alignof(tflite::MicroInterpreter));

  // Disable debug log, because we expect TFLM allocation to fail
  // and we don't want to pollute the stdout with warnings
  sl_tflite_micro_enable_debug_log(false);

  // Make sure we find the true upper limit first, doing this will force malloc and sbrk in the nano_libc case
  // to allocate a large contiguous segment that can be reused.
  while (upper_limit > lower_limit) {
    void *buffer = malloc(upper_limit);
    if (buffer == nullptr) {
      upper_limit -= 1024;
    } else {
      free(buffer);
      break;
    }
  }

  while ((upper_limit > lower_limit) && (upper_limit - lower_limit) > 128) {
    size_t buffer_size = (upper_limit + lower_limit) / 2;

    // Allocate buffer
    uint8_t* buffer;
    uint8_t* buffer_base = sl_tflite_micro_allocate_tensor_arena(buffer_size, &buffer);

    if (buffer_base == nullptr) {
      // If we failed to allocate buffer, then the current buffer_size is the new upper limit
      upper_limit = buffer_size;
      continue;
    }

    // Instantiate a dummy interpreter
    tflite::MicroInterpreter* dummy_interpreter = new(dummy_interpreter_buffer) tflite::MicroInterpreter(model, opcode_resolver, buffer, buffer_size);
    if (dummy_interpreter->AllocateTensors() != kTfLiteOk) {
      // It fails to allocate if the buffer size is too small,
      // So the new lower limit is the buffer size+1
      lower_limit = buffer_size + 1;
    } else {
      // Otherwise, the model was successfully loaded
      // Save the buffer size
      last_working_buffer_size = buffer_size;

      // And set the upper limit to the working buffer size
      // (the goal is to find the smallest possible buffer size)
      upper_limit = buffer_size;
    }
    // Unload the interpreter so we can load it again, note that we do not call delete so as to not free the memory because we will reuse it.
    dummy_interpreter->~MicroInterpreter();
    dummy_interpreter = nullptr;

    // Free the buffer for the next iteration
    free(buffer_base);
  }
  // Set debug log status back to what it was before
  sl_tflite_micro_enable_debug_log(current_debug_log_status);

  if (last_working_buffer_size == -1) {
    *estimated_size = 0;

    // Return false if we failed to find a working buffer size
    return SL_STATUS_ALLOCATION_FAILED;
  }

  // Add some additional memory for any padding or invoking the context.GetTensor() APIs.
  last_working_buffer_size += 256;

  *estimated_size = last_working_buffer_size;
  return SL_STATUS_OK;
}
uint8_t *sl_tflite_micro_allocate_tensor_arena(size_t arena_size, uint8_t** tensor_arena)
{
  // Make the buffer size a multiple of the recommended 16 byte alignment in TFLM
  arena_size = ((arena_size + 16 - 1) / 16) * 16;
  // Allocate buffer, malloc is 8 bytes aligned but we need to ensure we can later align to 16 bytes, so we add 8 bytes.
  uint8_t* buffer_base = (uint8_t*)malloc(arena_size + 8);
  if (buffer_base == nullptr) {
    return nullptr;
  }
  // Align buffer to 16 bytes, and return the aligned pointer
  *tensor_arena = (uint8_t*)(((size_t)buffer_base + 16 - 1) & ~(16 - 1));

  return buffer_base;
}

/***************************************************************************//**
 * @brief
 *  Creates the error reporter and opcode resolver and initializes variables
 *  for the flatbuffer given by the configuration.
 ******************************************************************************/
static void init(void)
{
#if SL_TFLITE_MICRO_INTERPRETER_INIT_ENABLE && defined(HAS_TFLITE_MICRO_FLATBUFFER_IN_CONFIGURATION)
  static tflite::MicroErrorReporter micro_error_reporter;
  sl_tflite_micro_error_reporter = &micro_error_reporter;

  // Instantiate model from char array.
  // The array may have been created in autogen/sl_ml_model.h or elsewhere.
  const tflite::Model* model = tflite::GetModel(SL_TFLITE_MICRO_MODEL_ARRAY);

  // Check model schema version
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    TF_LITE_REPORT_ERROR(sl_tflite_micro_error_reporter, "Error: Invalid model version");
    while (1);
  }

  // Create op resolver
  tflite::MicroOpResolver &opcode_resolver = sl_tflite_micro_opcode_resolver();

  // Decide arena size
  size_t arena_size = ARENA_SIZE;

  #if (ARENA_SIZE == -1) // Use arena size which is calculated runtime

  if (sl_tflite_micro_estimate_arena_size(model, opcode_resolver, &arena_size) != SL_STATUS_OK) {
    TF_LITE_REPORT_ERROR(sl_tflite_micro_error_reporter, "Error: Failed to estimate arena size");
    while (1);
  }
  // Malloc is 8 bytes aligned but we need to ensure we can later align to 16 bytes, so we add 8 bytes.
  uint8_t* tensor_arena_base = sl_tflite_micro_allocate_tensor_arena(arena_size, &tensor_arena);

  if (tensor_arena_base == nullptr) {
    TF_LITE_REPORT_ERROR(sl_tflite_micro_error_reporter, "Error: Failed to allocate arena buffer");
    while (1);
  }

  #endif

  // Instantiate interpreter
  static tflite::MicroInterpreter static_interpreter(
    model, opcode_resolver, tensor_arena, arena_size);
  sl_tflite_micro_interpreter = &static_interpreter;

  // Allocate memory from tensor_arena for the model's tensors.
  if (sl_tflite_micro_interpreter->AllocateTensors() != kTfLiteOk) {
    TF_LITE_REPORT_ERROR(sl_tflite_micro_error_reporter, "Error: Arena size too small, failed to allocate tensors");
    while (1);
  }

  // Obtain pointers to input and output tensors
  sl_tflite_micro_input_tensor = sl_tflite_micro_interpreter->input(0);
  sl_tflite_micro_output_tensor = sl_tflite_micro_interpreter->output(0);
#endif // SL_TFLITE_MICRO_INTERPRETER_INIT_ENABLE && defined(HAS_TFLITE_MICRO_FLATBUFFER_IN_CONFIGURATION)
}

tflite::ErrorReporter *sl_tflite_micro_get_error_reporter()
{
  return sl_tflite_micro_error_reporter;
}

tflite::MicroInterpreter *sl_tflite_micro_get_interpreter()
{
  return sl_tflite_micro_interpreter;
}

TfLiteTensor* sl_tflite_micro_get_input_tensor()
{
  return sl_tflite_micro_input_tensor;
}

TfLiteTensor* sl_tflite_micro_get_output_tensor()
{
  return sl_tflite_micro_output_tensor;
}

#ifdef HAS_TFLITE_MICRO_FLATBUFFER_IN_CONFIGURATION
tflite::MicroOpResolver &sl_tflite_micro_opcode_resolver()
{
  SL_TFLITE_MICRO_OPCODE_RESOLVER(opcode_resolver);
  return opcode_resolver;
}
#endif

extern "C" void sl_tflite_micro_init(void)
{
  init();
}
