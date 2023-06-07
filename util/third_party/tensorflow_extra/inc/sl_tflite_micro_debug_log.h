/***************************************************************************//**
 * @file
 * @brief Silicon Labs additional logging functionality for TensorFlow Light Micro.
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_TFLITE_MICRO_DEBUG_LOG_H
#define SL_TFLITE_MICRO_DEBUG_LOG_H
/***************************************************************************//**
 * @addtogroup tflite_micro_debug_log TensorFlow Lite Micro Debug
 * Additional SL utilities for logging in TensorFlow Lite Micro.
 * @{
 ******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
/***************************************************************************//**
 * @brief
 *  Enable or disable debug logging.
 * @param[in] enable Whether the debug logging should be enabled or disabled.
 *
 ******************************************************************************/
void sl_tflite_micro_enable_debug_log(bool enable);
/***************************************************************************//**
 * @brief
 *  Check if debug logging is enabled.
 * @return Whether debug logging is enabled.
 *
 ******************************************************************************/
bool sl_tflite_micro_is_debug_log_enabled(void);
#ifdef __cplusplus
}  // extern "C"
#endif // __cplusplus
/** @} (end addtogroup tflite_micro_debug_log) */

#endif // SL_TFLITE_MICRO_DEBUG_LOG_H
