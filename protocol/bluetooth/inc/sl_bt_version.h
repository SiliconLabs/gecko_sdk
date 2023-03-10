/***************************************************************************//**
 * @brief Bluetooth stack version definition
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

#ifndef SL_BT_VERSION_H
#define SL_BT_VERSION_H

/***************************************************************************//**
 * @addtogroup sl_bt_version Bluetooth SDK version
 * @brief Bluetooth SDK version information
 * @{
 */

/**
 * @brief The major number of Bluetooth SDK version
 *
 * An increment indicates incompatible Bluetooth API changes.
 */
#define SL_BT_VERSION_MAJOR 5

/**
 * @brief The minor number of Bluetooth SDK version
 *
 * An increment indicates new backwards compatible functionalities.
 */
#define SL_BT_VERSION_MINOR 1

/**
 * @brief The patch number of Bluetooth SDK version
 *
 * An increment indicates backwards compatible bug fixes.
 */
#define SL_BT_VERSION_PATCH 1

/**
 * @brief The build number which the Bluetooth SDK was created from
 */
#define SL_BT_VERSION_BUILD 190

/**
 * @brief The hash value of the build the Bluetooth SDK was created from
 */
#define SL_BT_VERSION_HASH {0x12,0x9d,0xd1,0x22,0x5a,0x94,0x8a,0x21,0x5d,0xc4,0x93,0xa0,0x7d,0xfe,0x74,0x57,0x8b,0x81,0x79,0x6d}

/**
 * Deprecated and replaced by SL_BT_VERSION_MAJOR
 */
#define BG_VERSION_MAJOR SL_BT_VERSION_MAJOR

/**
 * Deprecated and replaced by SL_BT_VERSION_MINOR
 */
#define BG_VERSION_MINOR SL_BT_VERSION_MINOR

/**
 * Deprecated and replaced by SL_BT_VERSION_PATCH
 */
#define BG_VERSION_PATCH SL_BT_VERSION_PATCH

/**
 * Deprecated and replaced by SL_BT_VERSION_BUILD
 */
#define BG_VERSION_BUILD SL_BT_VERSION_BUILD

/**
 * Deprecated and replaced by SL_BT_VERSION_HASH
 */
#define BG_VERSION_HASH SL_BT_VERSION_HASH

/** @} */ // end addtogroup sl_bt_version

#endif
