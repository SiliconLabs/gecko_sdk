/***************************************************************************//**
 * @file
 * @brief Averaging and evaluation of model output for prediction of gesture
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
#include "predictor.h"
#include "constants.h"
#include <cstdio>

// State for the averaging algorithm we're using.
//static float prediction_history[GESTURE_COUNT][PREDICTION_HISTORY_LEN] = {};
static model_output_t history[PREDICTION_HISTORY_LEN] = {};
static int history_index = 0;
static int suppression_count = 0;
static int previous_prediction = NO_GESTURE;

int predict_gesture(const model_output_t* output)
{
  // Record the latest predictions in our rolling history buffer.
  history[history_index] = *output;

  ++history_index;
  if (history_index >= PREDICTION_HISTORY_LEN) {
    history_index = 0;
  }

  // Average the last n predictions for each gesture, and find which has the
  // highest score.
  int max_predict_index = -1;
  float max_predict_score = 0.0f;

  for (int i = 0; i < GESTURE_COUNT; i++) {
    float prediction_sum = 0.0f;
    for (int j = 0; j < PREDICTION_HISTORY_LEN; ++j) {
      prediction_sum += history[j].gesture[i];
    }
    const float prediction_average = prediction_sum / PREDICTION_HISTORY_LEN;
    if ((max_predict_index == -1) || (prediction_average > max_predict_score)) {
      max_predict_index = i;
      max_predict_score = prediction_average;
    }
  }

#if DEBUG_LOGGING
  printf("Latest prediction: %i with probability %f\n", max_predict_index, max_predict_score);
#endif

  // If there's been a recent prediction, don't trigger a new one too soon.
  if (suppression_count > 0) {
    --suppression_count;
  }
  // If we're predicting no gesture, or the average score is too low, or there's
  // been a gesture recognised too recently, return no gesture.
  if ((max_predict_index == NO_GESTURE)
      || (max_predict_score < DETECTION_THRESHOLD)
      || ((max_predict_index == previous_prediction) && (suppression_count > 0))) {
    return NO_GESTURE;
  } else {
    // There was a new predicition
    // Reset the suppression counter so we don't come up with another prediction
    // too soon.
    suppression_count = PREDICTION_SUPPRESSION;
    previous_prediction = max_predict_index;
    return max_predict_index;
  }
}
