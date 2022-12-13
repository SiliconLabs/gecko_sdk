/***************************************************************************//**
 * @file app.cc
 * @brief application functions.
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
#include "app.h"
#include "timestamp.h"
#include "sl_pwm_instances.h"
#include "sl_pwm.h"
#include "sl_sleeptimer.h"
#include "sl_tflite_micro_init.h"
#include <stdio.h>

#define TIME_DELAY_MS        50
#define INFERENCE_PER_CYCLE (1000 / TIME_DELAY_MS)
#define X_RANGE             (2.f * 3.14159265359f)

static int count = 0;
static tflite::MicroInterpreter *interpreter;
static TfLiteTensor *input;
static TfLiteTensor *output;

static void handle_output(timestamp& ms, float x, float y);

void app_init(void)
{
  sl_pwm_start(&sl_pwm_led0);

  interpreter = sl_tflite_micro_get_interpreter();
  input = sl_tflite_micro_get_input_tensor();
  output = sl_tflite_micro_get_output_tensor();
}

void app_process_action(void)
{
  timestamp ts;
  sl_sleeptimer_delay_millisecond(TIME_DELAY_MS);

  float position = (float)count / INFERENCE_PER_CYCLE;
  float x = position * X_RANGE;

  int8_t x_quantized = x / input->params.scale + input->params.zero_point;
  input->data.int8[0] = x_quantized;

  ts.start();
  TfLiteStatus invoke_status = interpreter->Invoke();
  ts.stop();

  if (invoke_status != kTfLiteOk) {
    printf("error: inference failed, x=%f status=%d\n", x, invoke_status);
    return;
  }

  int8_t y_quantized = output->data.int8[0];
  float y = (y_quantized - output->params.zero_point) * output->params.scale;

  handle_output(ts, x, y);

  count += 1;
  if (count >= INFERENCE_PER_CYCLE) {
    count = 0;
  }
}

static void handle_output(timestamp& ts, float x, float y)
{
  uint8_t pwm_percent = (uint8_t)(((y + 1)) * 50);

  printf("x=%f y=%f (%.3f ms)\n", x, y, ts.duration_ms());
  sl_pwm_set_duty_cycle(&sl_pwm_led0, pwm_percent);
}

void HardFault_Handler(void)
{
  printf("error: HardFault\n");
  while (1)
    ;
}
