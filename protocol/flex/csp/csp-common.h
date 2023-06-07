/***************************************************************************//**
 * @brief Common functions for Connect Serial Protocol.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef __CSP_COMMON_H__
#define __CSP_COMMON_H__

/** @brief
 *  Gets the CSP version.
 */
uint16_t emberGetCspVersion(void);

/** @brief
 * Detects if the standalone bootloder is installed, and, if so,
 * returns the installed version and information about the platform,
 * micro and PHY. If not, the version will be set to 0xFFFF. A
 * returned version of 0x1234 indicates the version 1.2 build 34.
 */
void emberGetStandaloneBootloaderInfo(void);

/** @brief
 * Provides the result of a call to ::emberGetStandaloneBootloaderInfo.
 *
 * @param[in] version   BOOTLOADER_INVALID_VERSION if the standalone
 *                  bootloader is not present or the version of
 *                  the installed standalone bootloader.
 * @param[in] nodePlat  The value of PLAT on the node.
 * @param[in] nodeMicro The value of MICRO on the node.
 * @param[in] nodePhy   The value of PHY on the node.
 */
void emberGetStandaloneBootloaderInfoReturn(uint16_t version,
                                            uint8_t platformId,
                                            uint8_t microId,
                                            uint8_t phyId);

/** @brief
 * Launches the standalone bootloader (if installed).
 * The function returns an error if the standalone bootloader
 * is not present.
 *
 * @param[in] mode Controls the mode in which the standalone
 *             bootloader runs.
 *             Options are:
 *             STANDALONE_BOOTLOADER_NORMAL_MODE. The node will
 *             listen for an over-the-air image transfer on the
 *             current channel with current power settings.
 *             STANDALONE_BOOTLOADER_RECOVERY_MODE. The node will
 *             listen for an over-the-air image transfer on the
 *             default channel with default power settings. Both
 *             modes also allow an image transfer to begin with
 *             XMODEM over the serial protocol's Bootloader
 *             Frame.
 */
void emberLaunchStandaloneBootloader(uint8_t mode);

/** @brief
 * Provides the result of a call to ::emberLaunchStandaloneBootloader.
 *
 * @param[in] status An EmberStatus value indicating either success or the
 *               reason for failure.
 */
void emberLaunchStandaloneBootloaderReturn(EmberStatus status);

#endif // __CSP_COMMON_H__
