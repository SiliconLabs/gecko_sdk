/***************************************************************************//**
 * @brief BT API source code compatibility for deprecated items
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_BT_API_COMPATIBILITY_H
#define SL_BT_API_COMPATIBILITY_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Deprecated and replaced by sl_bt_gap_phy_t.
 */
typedef enum
{
  sl_bt_gap_1m_phy    = 0x1,  /**< (0x1) 1M PHY */
  sl_bt_gap_2m_phy    = 0x2,  /**< (0x2) 2M PHY */
  sl_bt_gap_coded_phy = 0x4,  /**< (0x4) Coded PHY, 125k (S=8) or 500k (S=2) */
  sl_bt_gap_any_phys  = 0xff  /**< (0xff) Any PHYs the device supports */
} sl_bt_gap_phy_type_t;

/**
 * Deprecated and replaced by sl_bt_gap_phy_coding_t.
 */
typedef enum
{
  sl_bt_gap_1m_phy_uncoded = 0x1, /**< (0x1) 1M PHY */
  sl_bt_gap_2m_phy_uncoded = 0x2, /**< (0x2) 2M PHY */
  sl_bt_gap_coded_phy_125k = 0x4, /**< (0x4) 125k Coded PHY (S=8) */
  sl_bt_gap_coded_phy_500k = 0x8  /**< (0x8) 500k Coded PHY (S=2) */
} sl_bt_gap_phy_and_coding_type_t;


#ifdef __cplusplus
}
#endif

#endif