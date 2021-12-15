/***************************************************************************//**
 * @file
 * @brief Configuration file for TensorFlow Lite Micro.
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

// <<< Use Configuration Wizard in Context Menu >>>

#ifndef SL_TFLITE_MICRO_CONFIG_H
#define SL_TFLITE_MICRO_CONFIG_H

/*******************************************************************************
 ******************************   DEFINES   ************************************
 ******************************************************************************/

// <s SL_TFLITE_MICRO_MODEL_ARRAY> The name of the model array
// <i> Default: default_model_array
// <i> Use the default_model_array or the name of the actual model array.
// <i> The array will be defined in the sl_tflite_micro_model.h if it is auto
// <i> generated from a flatbuffer.
#define SL_TFLITE_MICRO_MODEL_ARRAY     default_model_array

// <o SL_TFLITE_MICRO_ARENA_SIZE> Arena size
// <i> TensorFlow Lite Micro require a static allocated buffer to store the
// <i> model's activation buffers. Different models may require different
// <i> buffer sizes, and this configuration is used to define the size.
// <i> For background information on arena size, please refer to:
// <i> https://github.com/tensorflow/tensorflow/issues/35070 and
// <i> https://www.tensorflow.org/lite/microcontrollers/get_started_low_level#7_allocate_memory
// <i> for more information.
// <i> Default: 10240
#define SL_TFLITE_MICRO_ARENA_SIZE     (10240)

// <q SL_TFLITE_MICRO_INTERPRETER_INIT_ENABLE> Enable initialization of interpreter
// <i> If enabled, an instance of the MicroInterpreter will be created and
// <i> initialized automatically. If you required control of when and how the
// <i> MicroInterpreter is initialized then set this configuration to 0.
// <i> Default: 1
#define SL_TFLITE_MICRO_INTERPRETER_INIT_ENABLE    (1)

#endif // SL_TFLITE_MICRO_CONFIG_H

// <<< end of configuration section >>>
