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
#ifndef PREDICTOR_H
#define PREDICTOR_H

#include "constants.h"

typedef struct model_output {
  float gesture[GESTURE_COUNT];
} model_output_t;

/***************************************************************************//**
 * @brief
 *   Perform a prediction based on the latest inference output.
 *
 * @details
 *   Takes in the model output in a rolling history buffer and does averaging
 *   over the last predictions. If the prediction proability is too low or the
 *   predictions happens too soon, no prediction is triggered.
 *
 * @param output
 *   Model output buffer containing the confidence of each of the classes.
 *
 * @return
 *   Results of the last prediction in the form of a classification id.
 *   0: wing("W"), 1: ring("O"), 2: slope("angle"), 3: unknown
 ******************************************************************************/
int predict_gesture(const model_output_t* output);

#endif // PREDICTOR_H
