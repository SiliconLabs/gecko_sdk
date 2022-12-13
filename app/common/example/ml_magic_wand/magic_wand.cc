/***************************************************************************//**
 * @file
 * @brief Initalization and main functionality for application
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
#include "magic_wand.h"
#include "accelerometer.h"
#include "constants.h"
#include "predictor.h"
#include "sl_tflite_micro_model.h"
#include "sl_tflite_micro_init.h"
#include "sl_sleeptimer.h"
#include "sl_status.h"
#include "sl_led.h"
#include "sl_simple_led_instances.h"
#include <cstdio>

static int input_length;
static volatile bool inference_timeout;
static sl_sleeptimer_timer_handle_t inference_timer;
static sl_sleeptimer_timer_handle_t led_timer;
static TfLiteTensor* model_input;
static tflite::MicroInterpreter* interpreter;

// Triggered by the inference_timer
static void on_timeout_inference(sl_sleeptimer_timer_handle_t *handle, void* data)
{
  (void)handle; // unused
  (void)data; // unused
  inference_timeout = true;
}

// Triggered by the led_timer
void on_timeout_led(sl_sleeptimer_timer_handle_t *led_timer, void *data)
{
  (void)led_timer; // unused
  (void)data; // unused
  sl_led_turn_off(&sl_led_led0);
  sl_led_turn_off(&sl_led_led1);
}

void magic_wand_init(void)
{
  printf("Magic Wand\n");
  printf("init..\n");
  // Obtain pointer to the model's input tensor.
  model_input = sl_tflite_micro_get_input_tensor();
  interpreter = sl_tflite_micro_get_interpreter();
  if ((model_input->dims->size != 4) || (model_input->dims->data[0] != 1)
      || (model_input->dims->data[1] != SEQUENCE_LENGTH)
      || (model_input->dims->data[2] != ACCELEROMETER_CHANNELS)
      || (model_input->type != kTfLiteFloat32)) {
    printf("error: bad input tensor parameters in model\n");
    EFM_ASSERT(false);
    return;
  }

  input_length = model_input->bytes / sizeof(float);

  sl_status_t setup_status = accelerometer_setup();

  if (setup_status != SL_STATUS_OK) {
    printf("error: accelerometer setup failed\n");
    EFM_ASSERT(false);
    return;
  }

  // Waiting for accelerometer to become ready
  while (true) {
    sl_status_t status = accelerometer_read(NULL, 0);
    if (status == SL_STATUS_OK) {
      break;
    }
  }

  inference_timeout = false;
  sl_sleeptimer_start_periodic_timer_ms(&inference_timer, INFERENCE_PERIOD_MS, on_timeout_inference, NULL, 0, 0);
  printf("ready\n");
}


// Prints result and toggle LEDs. (red: wing, yellow: ring, green: slope)
static void handle_output(int gesture)
{
  uint32_t ts = sl_sleeptimer_tick_to_ms(sl_sleeptimer_get_tick_count());

  if (gesture == WING_GESTURE) {
    printf("t=%lu detection=wing (W)\n", ts);
    sl_led_turn_on(&sl_led_led0);
    sl_sleeptimer_start_timer_ms(&led_timer,
                                 TOGGLE_DELAY_MS,
                                 on_timeout_led, NULL,
                                 0,
                                 SL_SLEEPTIMER_NO_HIGH_PRECISION_HF_CLOCKS_REQUIRED_FLAG);
  } else if (gesture == RING_GESTURE) {
    printf("t=%lu detection=ring (O)\n", ts);
    sl_led_turn_on(&sl_led_led0);
    sl_led_turn_on(&sl_led_led1);
    sl_sleeptimer_start_timer_ms(&led_timer,
                                 TOGGLE_DELAY_MS,
                                 on_timeout_led, NULL,
                                 0,
                                 SL_SLEEPTIMER_NO_HIGH_PRECISION_HF_CLOCKS_REQUIRED_FLAG);
  } else if (gesture == SLOPE_GESTURE) {
    printf("t=%lu detection=slope (L)\n", ts);
    sl_led_turn_on(&sl_led_led1);
    sl_sleeptimer_start_timer_ms(&led_timer,
                                 TOGGLE_DELAY_MS,
                                 on_timeout_led, NULL,
                                 0,
                                 SL_SLEEPTIMER_NO_HIGH_PRECISION_HF_CLOCKS_REQUIRED_FLAG);
  } else if (gesture == NO_GESTURE) {
    // No spell detected
  }
}

void magic_wand_loop(void)
{
  // Insert data from accelerometer to the model.
  acc_data_t *dst = (acc_data_t *) model_input->data.f;
  size_t n = input_length / 3;
  sl_status_t status = accelerometer_read(dst, n);

  // If there was no new data, wait until next time.
  if (status == SL_STATUS_FAIL) {
    return;
  }

  // Inference is triggered periodically by a timer
  if (inference_timeout) {
    inference_timeout = false;

    TfLiteStatus invoke_status = interpreter->Invoke();

    if (invoke_status != kTfLiteOk) {
      printf("error: inference failed\n");
      return;
    }

    // Analyze the results to obtain a prediction
    const model_output_t *output = (const model_output_t *)interpreter->output(0)->data.f;
    int gesture = predict_gesture(output);

    // Produce an output
    handle_output(gesture);
  }
}
