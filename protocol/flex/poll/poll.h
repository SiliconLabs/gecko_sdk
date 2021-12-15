/***************************************************************************//**
 * @file
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

/**
 * @addtogroup poll
 * @brief APIs for the poll plugin.
 *
 * The Connect stack supports polling which enables (sleepy) end devices to
 * retrieve pending messages from the parent node (coordinator or range
 * extender).
 *
 * To use this feature, the Poll plugin must be enabled on the end devices.
 * If polling is enabled, the end device sends a data request to the parent node
 * which notifies the device whether there is a pending message or not, using the
 * acknowledge with the pending bit cleared or set. If there is no pending message
 * the communication ends with the acknowledge. If there is a pending message,
 * the parent node sends a data packet containing the pending message which will
 * be acknowledged by the end device.
 *
 * For convenience, Connect supports two polling intervals, long and short, both
 * behaves the same, only the polling period differs. For long polling the period
 * specified in second while in case of short polling the period is in quarter
 * seconds. The API provides a function to easily switch between the two. Purpose
 * of long polling is maintaining the connection between the end device and the
 * parent.
 *
 * The application will receive the polled message via the
 * @ref emberIncomingMessageHandler "emberAfIncomingMessageCallback()" function.
 *
 * The poll plugin uses ::emberPollForData() to retrieve the pending message. If the
 * poll plugin is enabled, using ::emberPollForData() is strongly not recommended.
 *
 * See poll.h for source code.
 *
 * @{
 */

/** @brief Set the short poll interval.
 *
 *  @param[in] intervalQS The short poll interval in quarter seconds.
 */
void emberAfPluginPollSetShortPollInterval(uint8_t intervalQS);

/** @brief Set the long poll interval.
 *
 *  @param[in] intervalS The long poll interval in seconds.
 */
void emberAfPluginPollSetLongPollInterval(uint16_t intervalS);

/** @brief Enable/disable short polling.
 *
 *  @param[in] enable If this parameter is true, short polling is enabled.
 *  Otherwise, the node switches back to long polling.
 */
void emberAfPluginPollEnableShortPolling(bool enable);

/** @} // END addtogroup
 */
