/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

This file has been modified by Silicon Labs.
==============================================================================*/

#include "magic_wand/main_functions.h"
#include <cstdio>
#include "magic_wand/accelerometer_handler.h"
#include "magic_wand/constants.h"
#include "magic_wand/gesture_predictor.h"
#include "magic_wand/output_handler.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "sl_tflite_micro_model.h"
#include "sl_sleeptimer.h"

#define INFERENCE_PERIOD_MS 200

// Globals, used for compatibility with Arduino-style sketches.
namespace {
tflite::ErrorReporter* error_reporter = nullptr;
const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* model_input = nullptr;
int input_length;

// Create an area of memory to use for input, output, and intermediate arrays.
// The size of this will depend on the model you're using, and may need to be
// determined by experimentation.
constexpr int kTensorArenaSize = 6 * 1024;
uint8_t tensor_arena[kTensorArenaSize];
}  // namespace


static volatile bool inference_timeout;
static sl_sleeptimer_timer_handle_t inference_timer;

static void inference_timer_callback(sl_sleeptimer_timer_handle_t *handle, void* data)
{
  (void)handle;
  (void)data;
  inference_timeout = true;
}
// The name of this function is important for Arduino compatibility.
void setup() {
  // Set up logging. Google style is to avoid globals or statics because of
  // lifetime uncertainty, but since this has a trivial destructor it's okay.
  static tflite::MicroErrorReporter micro_error_reporter;  // NOLINT
  error_reporter = &micro_error_reporter;

  // Map the model into a usable data structure. This doesn't involve any
  // copying or parsing, it's a very lightweight operation.
  model = tflite::GetModel(sl_tflite_model_array);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    TF_LITE_REPORT_ERROR(error_reporter,
                         "Model provided is schema version %d not equal "
                         "to supported version %d.",
                         model->version(), TFLITE_SCHEMA_VERSION);
    return;
  }

  // Pull in only the operation implementations we need.
  // This relies on a complete list of all the ops needed by this graph.
  // An easier approach is to just use the AllOpsResolver, but this will
  // incur some penalty in code space for op implementations that are not
  // needed by this graph.
  static tflite::MicroMutableOpResolver<8> micro_op_resolver;  // NOLINT
  micro_op_resolver.AddConv2D();
  micro_op_resolver.AddDepthwiseConv2D();
  micro_op_resolver.AddFullyConnected();
  micro_op_resolver.AddMaxPool2D();
  micro_op_resolver.AddSoftmax();
  micro_op_resolver.AddReshape();
  micro_op_resolver.AddQuantize();
  micro_op_resolver.AddDequantize();

  // Build an interpreter to run the model with.
  static tflite::MicroInterpreter static_interpreter(
      model, micro_op_resolver, tensor_arena, kTensorArenaSize, error_reporter);
  interpreter = &static_interpreter;

  // Allocate memory from the tensor_arena for the model's tensors.
  interpreter->AllocateTensors();

  // Obtain pointer to the model's input tensor.
  model_input = interpreter->input(0);
  if ((model_input->dims->size != 4) || (model_input->dims->data[0] != 1) ||
      (model_input->dims->data[1] != 128) ||
      (model_input->dims->data[2] != kChannelNumber) ||
      (model_input->type != kTfLiteFloat32)) {
    TF_LITE_REPORT_ERROR(error_reporter,
                         "Bad input tensor parameters in model");
    return;
  }

  input_length = model_input->bytes / sizeof(float);

  TfLiteStatus setup_status = SetupAccelerometer(error_reporter);
  if (setup_status != kTfLiteOk) {
    TF_LITE_REPORT_ERROR(error_reporter, "Set up failed\n");
    return;
  }

  inference_timeout = false;
  sl_sleeptimer_start_periodic_timer_ms(&inference_timer, INFERENCE_PERIOD_MS, inference_timer_callback, NULL, 0, 0);

  printf(
    R"EOF(
                                            *
                      *                    ***
                     ***        *           *
                      *        ***     *
                 *              *     ***
                ***       *            *
                 *       ***
                          *
                                    *
                   *               ***
                  ***       **      *
                   *       ****
              *             **
             ***
              *             *
                    **     ***
                   ****     *
                *   **
              ****
        **********
         **********
          ************
          ***********
         *********
        *** ******
            **  **
           **
           **
          **
          **
         **
         **
        **
        **
       **
       **
      **
      **
     **
     **
    **
    **
   **
  ***
 ***
****
***
**
                    _        __    __                _
  /\/\   __ _  __ _(_) ___  / / /\ \ \__ _ _ __   __| |
 /    \ / _` |/ _` | |/ __| \ \/  \/ / _` | '_ \ / _` |
/ /\/\ \ (_| | (_| | | (__   \  /\  / (_| | | | | (_| |
\/    \/\__,_|\__, |_|\___|   \/  \/ \__,_|_| |_|\__,_|
              |___/

Detecting spells...
)EOF");
  printf("\n");
}

void loop() {
  // Attempt to read new data from the accelerometer.
  bool got_data =
      ReadAccelerometer(error_reporter, model_input->data.f, input_length);

  // If there was no new data, wait until next time.
  if (!got_data) return;

  // Only run inference every INFERENCE_PERIOD_MS ms
  if (inference_timeout){
  inference_timeout = false;

  // Run inference, and report any error.
  TfLiteStatus invoke_status = interpreter->Invoke();

  if (invoke_status != kTfLiteOk) {
    TF_LITE_REPORT_ERROR(error_reporter, "Invoke failed on index: %d\n",
                         begin_index);
    return;
  }
  // Analyze the results to obtain a prediction
  int gesture_index = PredictGesture(interpreter->output(0)->data.f);

  // Produce an output
  HandleOutput(error_reporter, gesture_index);

  }
}
