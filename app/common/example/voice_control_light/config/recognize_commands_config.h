/***************************************************************************//**
 * @file
 * @brief Command Recognition Config
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc.  Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement.  This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef RECOGNIZE_COMMANDS_CONFIG_H
#define RECOGNIZE_COMMANDS_CONFIG_H

#if __has_include("sl_tflite_micro_model_parameters.h")
// Include MLTK model parameters that are extracted from tflite file
  #include "sl_tflite_micro_model_parameters.h"
#endif

// <<< Use Configuration Wizard in Context Menu >>>
// <h> Keyword recognition configuration
// <i> Settings for further recognition of the instantaneous model outputs

// <o> Detection Threshold <0-255>
// <i> Sets a threshold for determining the confidence score required in order
// <i> to classify a keyword as detected. This can be increased to avoid
// <i> misclassifications.
// <i> The confidence scores are in the range <0-255>
// <i> Default: 160
#if defined(SL_TFLITE_MODEL_DETECTION_THRESHOLD)
  #define DETECTION_THRESHOLD SL_TFLITE_MODEL_DETECTION_THRESHOLD
#else
  #define DETECTION_THRESHOLD 160
#endif

// <o> Suppression time after detection [ms] <0-2000>
// <i> Sets a time window to wait after a detected keyword before triggering
// <i> a new detection.
// <i> Default: 1000
#if defined(SL_TFLITE_MODEL_SUPPRESSION_MS)
  #define SUPPRESSION_TIME_MS SL_TFLITE_MODEL_SUPPRESSION_MS
#else
  #define SUPPRESSION_TIME_MS 1000
#endif

// <<< end of configuration section >>>

#endif // RECOGNIZE_COMMANDS_CONFIG_H
