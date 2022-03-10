/**************************************************************************//**
 * @file
 * @brief MGM24 ECA register and bit field definitions
 ******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories, Inc. www.silabs.com</b>
 ******************************************************************************
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
 *****************************************************************************/
#ifndef MGM24_ECA_H
#define MGM24_ECA_H
#define ECA_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup MGM24_ECA ECA
 * @{
 * @brief MGM24 ECA Register Declaration.
 *****************************************************************************/

/** ECA BUF Register Group Declaration. */
typedef struct {
  __IOM uint32_t BASE;                               /**< BUFFER BASE ADDRESS                                */
  __IOM uint32_t LIMITOFFSET;                        /**< Limit Offset                                       */
  __IOM uint32_t WMOFFSET;                           /**< Watermark Offset                                   */
} ECA_BUF_TypeDef;

/** ECA Register Declaration. */
typedef struct {
  __IM uint32_t   IPVERSION;                    /**< IP Version ID                                      */
  __IOM uint32_t  EN;                           /**< Module Enable                                      */
  __IOM uint32_t  SWRST;                        /**< Software Reset                                     */
  __IOM uint32_t  CMD;                          /**< Command                                            */
  __IOM uint32_t  CONTROL;                      /**< Control                                            */
  __IM uint32_t   STATUS;                       /**< Status                                             */
  __IOM uint32_t  IF;                           /**< Interrupt Flag                                     */
  __IOM uint32_t  IEN;                          /**< Interrupt EN                                       */
  __IM uint32_t   DMABUSERRORSTATUS;            /**< DMA Bus Error Status                               */
  ECA_BUF_TypeDef BUF[2U];                      /**<                                                    */
  __IM uint32_t   BUFPTRSTATUS;                 /**< Buffer Pointer Status                              */
  __IOM uint32_t  STARTTRIGCTRL;                /**< Start Trigger Control                              */
  __IOM uint32_t  STOPTRIGCTRL;                 /**< Stop Trigger Control                               */
  __IOM uint32_t  STARTTRIGENMASK;              /**< Start Trigger Enable Mask                          */
  __IOM uint32_t  STARTTRIGREDMASK;             /**< Start Trigger Rising Edge Mask                     */
  __IOM uint32_t  STARTTRIGFEDMASK;             /**< Start Trigger Falling Edge Mask                    */
  __IOM uint32_t  STARTTRIGLVL0MASK;            /**< Start Trigger Level 0 Mask                         */
  __IOM uint32_t  STARTTRIGLVL1MASK;            /**< Start Trigger Level 1 Mask                         */
  __IOM uint32_t  STOPTRIGENMASK;               /**< Stop Trigger Enable Mask                           */
  __IOM uint32_t  STOPTRIGREDMASK;              /**< Stop Trigger Rising Edge Mask                      */
  __IOM uint32_t  STOPTRIGFEDMASK;              /**< Stop Trigger Falling Edge Mask                     */
  __IOM uint32_t  STOPTRIGLVL0MASK;             /**< Stop Trigger Level 0 Mask                          */
  __IOM uint32_t  STOPTRIGLVL1MASK;             /**< Stop Trigger Level 1 Mask                          */
  __IOM uint32_t  CAPTURECTRL;                  /**< Capture Control                                    */
  __IOM uint32_t  CAPTURESTARTDELAY;            /**< Capture Start Delay                                */
  __IOM uint32_t  CAPTURESTOPDELAY;             /**< Capture Stop Delay                                 */
  __IOM uint32_t  CAPTURERATECTRL;              /**< Capture Rate Control                               */
  __IOM uint32_t  PLAYBACKCTRL;                 /**< Playback Control                                   */
  __IOM uint32_t  PLAYBACKRATECTRL;             /**< Playback Rate Control                              */
  __IOM uint32_t  EVENTCNTRCTRL;                /**< Event Counter Control                              */
  __IOM uint32_t  EVENTCNTRCOMPARE;             /**< Event Counter Compare                              */
  __IM uint32_t   EVENTCNTRSTATUS;              /**< Event Counter Status                               */
  uint32_t        RESERVED0[987U];              /**< Reserved for future use                            */
  __IM uint32_t   IPVERSION_SET;                /**< IP Version ID                                      */
  __IOM uint32_t  EN_SET;                       /**< Module Enable                                      */
  __IOM uint32_t  SWRST_SET;                    /**< Software Reset                                     */
  __IOM uint32_t  CMD_SET;                      /**< Command                                            */
  __IOM uint32_t  CONTROL_SET;                  /**< Control                                            */
  __IM uint32_t   STATUS_SET;                   /**< Status                                             */
  __IOM uint32_t  IF_SET;                       /**< Interrupt Flag                                     */
  __IOM uint32_t  IEN_SET;                      /**< Interrupt EN                                       */
  __IM uint32_t   DMABUSERRORSTATUS_SET;        /**< DMA Bus Error Status                               */
  ECA_BUF_TypeDef BUF_SET[2U];                  /**<                                                    */
  __IM uint32_t   BUFPTRSTATUS_SET;             /**< Buffer Pointer Status                              */
  __IOM uint32_t  STARTTRIGCTRL_SET;            /**< Start Trigger Control                              */
  __IOM uint32_t  STOPTRIGCTRL_SET;             /**< Stop Trigger Control                               */
  __IOM uint32_t  STARTTRIGENMASK_SET;          /**< Start Trigger Enable Mask                          */
  __IOM uint32_t  STARTTRIGREDMASK_SET;         /**< Start Trigger Rising Edge Mask                     */
  __IOM uint32_t  STARTTRIGFEDMASK_SET;         /**< Start Trigger Falling Edge Mask                    */
  __IOM uint32_t  STARTTRIGLVL0MASK_SET;        /**< Start Trigger Level 0 Mask                         */
  __IOM uint32_t  STARTTRIGLVL1MASK_SET;        /**< Start Trigger Level 1 Mask                         */
  __IOM uint32_t  STOPTRIGENMASK_SET;           /**< Stop Trigger Enable Mask                           */
  __IOM uint32_t  STOPTRIGREDMASK_SET;          /**< Stop Trigger Rising Edge Mask                      */
  __IOM uint32_t  STOPTRIGFEDMASK_SET;          /**< Stop Trigger Falling Edge Mask                     */
  __IOM uint32_t  STOPTRIGLVL0MASK_SET;         /**< Stop Trigger Level 0 Mask                          */
  __IOM uint32_t  STOPTRIGLVL1MASK_SET;         /**< Stop Trigger Level 1 Mask                          */
  __IOM uint32_t  CAPTURECTRL_SET;              /**< Capture Control                                    */
  __IOM uint32_t  CAPTURESTARTDELAY_SET;        /**< Capture Start Delay                                */
  __IOM uint32_t  CAPTURESTOPDELAY_SET;         /**< Capture Stop Delay                                 */
  __IOM uint32_t  CAPTURERATECTRL_SET;          /**< Capture Rate Control                               */
  __IOM uint32_t  PLAYBACKCTRL_SET;             /**< Playback Control                                   */
  __IOM uint32_t  PLAYBACKRATECTRL_SET;         /**< Playback Rate Control                              */
  __IOM uint32_t  EVENTCNTRCTRL_SET;            /**< Event Counter Control                              */
  __IOM uint32_t  EVENTCNTRCOMPARE_SET;         /**< Event Counter Compare                              */
  __IM uint32_t   EVENTCNTRSTATUS_SET;          /**< Event Counter Status                               */
  uint32_t        RESERVED1[987U];              /**< Reserved for future use                            */
  __IM uint32_t   IPVERSION_CLR;                /**< IP Version ID                                      */
  __IOM uint32_t  EN_CLR;                       /**< Module Enable                                      */
  __IOM uint32_t  SWRST_CLR;                    /**< Software Reset                                     */
  __IOM uint32_t  CMD_CLR;                      /**< Command                                            */
  __IOM uint32_t  CONTROL_CLR;                  /**< Control                                            */
  __IM uint32_t   STATUS_CLR;                   /**< Status                                             */
  __IOM uint32_t  IF_CLR;                       /**< Interrupt Flag                                     */
  __IOM uint32_t  IEN_CLR;                      /**< Interrupt EN                                       */
  __IM uint32_t   DMABUSERRORSTATUS_CLR;        /**< DMA Bus Error Status                               */
  ECA_BUF_TypeDef BUF_CLR[2U];                  /**<                                                    */
  __IM uint32_t   BUFPTRSTATUS_CLR;             /**< Buffer Pointer Status                              */
  __IOM uint32_t  STARTTRIGCTRL_CLR;            /**< Start Trigger Control                              */
  __IOM uint32_t  STOPTRIGCTRL_CLR;             /**< Stop Trigger Control                               */
  __IOM uint32_t  STARTTRIGENMASK_CLR;          /**< Start Trigger Enable Mask                          */
  __IOM uint32_t  STARTTRIGREDMASK_CLR;         /**< Start Trigger Rising Edge Mask                     */
  __IOM uint32_t  STARTTRIGFEDMASK_CLR;         /**< Start Trigger Falling Edge Mask                    */
  __IOM uint32_t  STARTTRIGLVL0MASK_CLR;        /**< Start Trigger Level 0 Mask                         */
  __IOM uint32_t  STARTTRIGLVL1MASK_CLR;        /**< Start Trigger Level 1 Mask                         */
  __IOM uint32_t  STOPTRIGENMASK_CLR;           /**< Stop Trigger Enable Mask                           */
  __IOM uint32_t  STOPTRIGREDMASK_CLR;          /**< Stop Trigger Rising Edge Mask                      */
  __IOM uint32_t  STOPTRIGFEDMASK_CLR;          /**< Stop Trigger Falling Edge Mask                     */
  __IOM uint32_t  STOPTRIGLVL0MASK_CLR;         /**< Stop Trigger Level 0 Mask                          */
  __IOM uint32_t  STOPTRIGLVL1MASK_CLR;         /**< Stop Trigger Level 1 Mask                          */
  __IOM uint32_t  CAPTURECTRL_CLR;              /**< Capture Control                                    */
  __IOM uint32_t  CAPTURESTARTDELAY_CLR;        /**< Capture Start Delay                                */
  __IOM uint32_t  CAPTURESTOPDELAY_CLR;         /**< Capture Stop Delay                                 */
  __IOM uint32_t  CAPTURERATECTRL_CLR;          /**< Capture Rate Control                               */
  __IOM uint32_t  PLAYBACKCTRL_CLR;             /**< Playback Control                                   */
  __IOM uint32_t  PLAYBACKRATECTRL_CLR;         /**< Playback Rate Control                              */
  __IOM uint32_t  EVENTCNTRCTRL_CLR;            /**< Event Counter Control                              */
  __IOM uint32_t  EVENTCNTRCOMPARE_CLR;         /**< Event Counter Compare                              */
  __IM uint32_t   EVENTCNTRSTATUS_CLR;          /**< Event Counter Status                               */
  uint32_t        RESERVED2[987U];              /**< Reserved for future use                            */
  __IM uint32_t   IPVERSION_TGL;                /**< IP Version ID                                      */
  __IOM uint32_t  EN_TGL;                       /**< Module Enable                                      */
  __IOM uint32_t  SWRST_TGL;                    /**< Software Reset                                     */
  __IOM uint32_t  CMD_TGL;                      /**< Command                                            */
  __IOM uint32_t  CONTROL_TGL;                  /**< Control                                            */
  __IM uint32_t   STATUS_TGL;                   /**< Status                                             */
  __IOM uint32_t  IF_TGL;                       /**< Interrupt Flag                                     */
  __IOM uint32_t  IEN_TGL;                      /**< Interrupt EN                                       */
  __IM uint32_t   DMABUSERRORSTATUS_TGL;        /**< DMA Bus Error Status                               */
  ECA_BUF_TypeDef BUF_TGL[2U];                  /**<                                                    */
  __IM uint32_t   BUFPTRSTATUS_TGL;             /**< Buffer Pointer Status                              */
  __IOM uint32_t  STARTTRIGCTRL_TGL;            /**< Start Trigger Control                              */
  __IOM uint32_t  STOPTRIGCTRL_TGL;             /**< Stop Trigger Control                               */
  __IOM uint32_t  STARTTRIGENMASK_TGL;          /**< Start Trigger Enable Mask                          */
  __IOM uint32_t  STARTTRIGREDMASK_TGL;         /**< Start Trigger Rising Edge Mask                     */
  __IOM uint32_t  STARTTRIGFEDMASK_TGL;         /**< Start Trigger Falling Edge Mask                    */
  __IOM uint32_t  STARTTRIGLVL0MASK_TGL;        /**< Start Trigger Level 0 Mask                         */
  __IOM uint32_t  STARTTRIGLVL1MASK_TGL;        /**< Start Trigger Level 1 Mask                         */
  __IOM uint32_t  STOPTRIGENMASK_TGL;           /**< Stop Trigger Enable Mask                           */
  __IOM uint32_t  STOPTRIGREDMASK_TGL;          /**< Stop Trigger Rising Edge Mask                      */
  __IOM uint32_t  STOPTRIGFEDMASK_TGL;          /**< Stop Trigger Falling Edge Mask                     */
  __IOM uint32_t  STOPTRIGLVL0MASK_TGL;         /**< Stop Trigger Level 0 Mask                          */
  __IOM uint32_t  STOPTRIGLVL1MASK_TGL;         /**< Stop Trigger Level 1 Mask                          */
  __IOM uint32_t  CAPTURECTRL_TGL;              /**< Capture Control                                    */
  __IOM uint32_t  CAPTURESTARTDELAY_TGL;        /**< Capture Start Delay                                */
  __IOM uint32_t  CAPTURESTOPDELAY_TGL;         /**< Capture Stop Delay                                 */
  __IOM uint32_t  CAPTURERATECTRL_TGL;          /**< Capture Rate Control                               */
  __IOM uint32_t  PLAYBACKCTRL_TGL;             /**< Playback Control                                   */
  __IOM uint32_t  PLAYBACKRATECTRL_TGL;         /**< Playback Rate Control                              */
  __IOM uint32_t  EVENTCNTRCTRL_TGL;            /**< Event Counter Control                              */
  __IOM uint32_t  EVENTCNTRCOMPARE_TGL;         /**< Event Counter Compare                              */
  __IM uint32_t   EVENTCNTRSTATUS_TGL;          /**< Event Counter Status                               */
} ECA_TypeDef;
/** @} End of group MGM24_ECA */

/**************************************************************************//**
 * @addtogroup MGM24_ECA
 * @{
 * @defgroup MGM24_ECA_BitFields ECA Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for ECA IPVERSION */
#define _ECA_IPVERSION_RESETVALUE                      0x00000001UL                            /**< Default value for ECA_IPVERSION             */
#define _ECA_IPVERSION_MASK                            0xFFFFFFFFUL                            /**< Mask for ECA_IPVERSION                      */
#define _ECA_IPVERSION_IPVERSION_SHIFT                 0                                       /**< Shift value for ECA_IPVERSION               */
#define _ECA_IPVERSION_IPVERSION_MASK                  0xFFFFFFFFUL                            /**< Bit mask for ECA_IPVERSION                  */
#define _ECA_IPVERSION_IPVERSION_DEFAULT               0x00000001UL                            /**< Mode DEFAULT for ECA_IPVERSION              */
#define ECA_IPVERSION_IPVERSION_DEFAULT                (_ECA_IPVERSION_IPVERSION_DEFAULT << 0) /**< Shifted mode DEFAULT for ECA_IPVERSION      */

/* Bit fields for ECA EN */
#define _ECA_EN_RESETVALUE                             0x00000000UL                     /**< Default value for ECA_EN                    */
#define _ECA_EN_MASK                                   0x00000003UL                     /**< Mask for ECA_EN                             */
#define ECA_EN_EN                                      (0x1UL << 0)                     /**< Module Enable                               */
#define _ECA_EN_EN_SHIFT                               0                                /**< Shift value for ECA_EN                      */
#define _ECA_EN_EN_MASK                                0x1UL                            /**< Bit mask for ECA_EN                         */
#define _ECA_EN_EN_DEFAULT                             0x00000000UL                     /**< Mode DEFAULT for ECA_EN                     */
#define ECA_EN_EN_DEFAULT                              (_ECA_EN_EN_DEFAULT << 0)        /**< Shifted mode DEFAULT for ECA_EN             */
#define ECA_EN_DISABLING                               (0x1UL << 1)                     /**< Disablement Busy Status                     */
#define _ECA_EN_DISABLING_SHIFT                        1                                /**< Shift value for ECA_DISABLING               */
#define _ECA_EN_DISABLING_MASK                         0x2UL                            /**< Bit mask for ECA_DISABLING                  */
#define _ECA_EN_DISABLING_DEFAULT                      0x00000000UL                     /**< Mode DEFAULT for ECA_EN                     */
#define ECA_EN_DISABLING_DEFAULT                       (_ECA_EN_DISABLING_DEFAULT << 1) /**< Shifted mode DEFAULT for ECA_EN             */

/* Bit fields for ECA SWRST */
#define _ECA_SWRST_RESETVALUE                          0x00000000UL                        /**< Default value for ECA_SWRST                 */
#define _ECA_SWRST_MASK                                0x00000003UL                        /**< Mask for ECA_SWRST                          */
#define ECA_SWRST_SWRST                                (0x1UL << 0)                        /**< Software Reset Command                      */
#define _ECA_SWRST_SWRST_SHIFT                         0                                   /**< Shift value for ECA_SWRST                   */
#define _ECA_SWRST_SWRST_MASK                          0x1UL                               /**< Bit mask for ECA_SWRST                      */
#define _ECA_SWRST_SWRST_DEFAULT                       0x00000000UL                        /**< Mode DEFAULT for ECA_SWRST                  */
#define ECA_SWRST_SWRST_DEFAULT                        (_ECA_SWRST_SWRST_DEFAULT << 0)     /**< Shifted mode DEFAULT for ECA_SWRST          */
#define ECA_SWRST_RESETTING                            (0x1UL << 1)                        /**< Software Reset Busy Status                  */
#define _ECA_SWRST_RESETTING_SHIFT                     1                                   /**< Shift value for ECA_RESETTING               */
#define _ECA_SWRST_RESETTING_MASK                      0x2UL                               /**< Bit mask for ECA_RESETTING                  */
#define _ECA_SWRST_RESETTING_DEFAULT                   0x00000000UL                        /**< Mode DEFAULT for ECA_SWRST                  */
#define ECA_SWRST_RESETTING_DEFAULT                    (_ECA_SWRST_RESETTING_DEFAULT << 1) /**< Shifted mode DEFAULT for ECA_SWRST          */

/* Bit fields for ECA CMD */
#define _ECA_CMD_RESETVALUE                            0x00000000UL                           /**< Default value for ECA_CMD                   */
#define _ECA_CMD_MASK                                  0x0000001FUL                           /**< Mask for ECA_CMD                            */
#define _ECA_CMD_MODE_SHIFT                            0                                      /**< Shift value for ECA_MODE                    */
#define _ECA_CMD_MODE_MASK                             0x3UL                                  /**< Bit mask for ECA_MODE                       */
#define _ECA_CMD_MODE_DEFAULT                          0x00000000UL                           /**< Mode DEFAULT for ECA_CMD                    */
#define _ECA_CMD_MODE_DISABLED                         0x00000001UL                           /**< Mode DISABLED for ECA_CMD                   */
#define _ECA_CMD_MODE_CAPTURE                          0x00000002UL                           /**< Mode CAPTURE for ECA_CMD                    */
#define _ECA_CMD_MODE_PLAYBACK                         0x00000003UL                           /**< Mode PLAYBACK for ECA_CMD                   */
#define ECA_CMD_MODE_DEFAULT                           (_ECA_CMD_MODE_DEFAULT << 0)           /**< Shifted mode DEFAULT for ECA_CMD            */
#define ECA_CMD_MODE_DISABLED                          (_ECA_CMD_MODE_DISABLED << 0)          /**< Shifted mode DISABLED for ECA_CMD           */
#define ECA_CMD_MODE_CAPTURE                           (_ECA_CMD_MODE_CAPTURE << 0)           /**< Shifted mode CAPTURE for ECA_CMD            */
#define ECA_CMD_MODE_PLAYBACK                          (_ECA_CMD_MODE_PLAYBACK << 0)          /**< Shifted mode PLAYBACK for ECA_CMD           */
#define ECA_CMD_STARTEVENTCNTR                         (0x1UL << 2)                           /**< Start Event Counter                         */
#define _ECA_CMD_STARTEVENTCNTR_SHIFT                  2                                      /**< Shift value for ECA_STARTEVENTCNTR          */
#define _ECA_CMD_STARTEVENTCNTR_MASK                   0x4UL                                  /**< Bit mask for ECA_STARTEVENTCNTR             */
#define _ECA_CMD_STARTEVENTCNTR_DEFAULT                0x00000000UL                           /**< Mode DEFAULT for ECA_CMD                    */
#define ECA_CMD_STARTEVENTCNTR_DEFAULT                 (_ECA_CMD_STARTEVENTCNTR_DEFAULT << 2) /**< Shifted mode DEFAULT for ECA_CMD            */
#define ECA_CMD_STOPEVENTCNTR                          (0x1UL << 3)                           /**< Stop Event Counter                          */
#define _ECA_CMD_STOPEVENTCNTR_SHIFT                   3                                      /**< Shift value for ECA_STOPEVENTCNTR           */
#define _ECA_CMD_STOPEVENTCNTR_MASK                    0x8UL                                  /**< Bit mask for ECA_STOPEVENTCNTR              */
#define _ECA_CMD_STOPEVENTCNTR_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for ECA_CMD                    */
#define ECA_CMD_STOPEVENTCNTR_DEFAULT                  (_ECA_CMD_STOPEVENTCNTR_DEFAULT << 3)  /**< Shifted mode DEFAULT for ECA_CMD            */
#define ECA_CMD_CLEAREVENTCNTR                         (0x1UL << 4)                           /**< Clear Event Counter                         */
#define _ECA_CMD_CLEAREVENTCNTR_SHIFT                  4                                      /**< Shift value for ECA_CLEAREVENTCNTR          */
#define _ECA_CMD_CLEAREVENTCNTR_MASK                   0x10UL                                 /**< Bit mask for ECA_CLEAREVENTCNTR             */
#define _ECA_CMD_CLEAREVENTCNTR_DEFAULT                0x00000000UL                           /**< Mode DEFAULT for ECA_CMD                    */
#define ECA_CMD_CLEAREVENTCNTR_DEFAULT                 (_ECA_CMD_CLEAREVENTCNTR_DEFAULT << 4) /**< Shifted mode DEFAULT for ECA_CMD            */

/* Bit fields for ECA CONTROL */
#define _ECA_CONTROL_RESETVALUE                        0x00000000UL                             /**< Default value for ECA_CONTROL               */
#define _ECA_CONTROL_MASK                              0x00000003UL                             /**< Mask for ECA_CONTROL                        */
#define ECA_CONTROL_BUFMODE                            (0x1UL << 0)                             /**< Buffer Mode                                 */
#define _ECA_CONTROL_BUFMODE_SHIFT                     0                                        /**< Shift value for ECA_BUFMODE                 */
#define _ECA_CONTROL_BUFMODE_MASK                      0x1UL                                    /**< Bit mask for ECA_BUFMODE                    */
#define _ECA_CONTROL_BUFMODE_DEFAULT                   0x00000000UL                             /**< Mode DEFAULT for ECA_CONTROL                */
#define _ECA_CONTROL_BUFMODE_SINGLE                    0x00000000UL                             /**< Mode SINGLE for ECA_CONTROL                 */
#define _ECA_CONTROL_BUFMODE_DUAL                      0x00000001UL                             /**< Mode DUAL for ECA_CONTROL                   */
#define ECA_CONTROL_BUFMODE_DEFAULT                    (_ECA_CONTROL_BUFMODE_DEFAULT << 0)      /**< Shifted mode DEFAULT for ECA_CONTROL        */
#define ECA_CONTROL_BUFMODE_SINGLE                     (_ECA_CONTROL_BUFMODE_SINGLE << 0)       /**< Shifted mode SINGLE for ECA_CONTROL         */
#define ECA_CONTROL_BUFMODE_DUAL                       (_ECA_CONTROL_BUFMODE_DUAL << 0)         /**< Shifted mode DUAL for ECA_CONTROL           */
#define ECA_CONTROL_QCHANNELMODE                       (0x1UL << 1)                             /**< Q-Channel Mode                              */
#define _ECA_CONTROL_QCHANNELMODE_SHIFT                1                                        /**< Shift value for ECA_QCHANNELMODE            */
#define _ECA_CONTROL_QCHANNELMODE_MASK                 0x2UL                                    /**< Bit mask for ECA_QCHANNELMODE               */
#define _ECA_CONTROL_QCHANNELMODE_DEFAULT              0x00000000UL                             /**< Mode DEFAULT for ECA_CONTROL                */
#define _ECA_CONTROL_QCHANNELMODE_ACCEPT               0x00000000UL                             /**< Mode ACCEPT for ECA_CONTROL                 */
#define _ECA_CONTROL_QCHANNELMODE_DENY                 0x00000001UL                             /**< Mode DENY for ECA_CONTROL                   */
#define ECA_CONTROL_QCHANNELMODE_DEFAULT               (_ECA_CONTROL_QCHANNELMODE_DEFAULT << 1) /**< Shifted mode DEFAULT for ECA_CONTROL        */
#define ECA_CONTROL_QCHANNELMODE_ACCEPT                (_ECA_CONTROL_QCHANNELMODE_ACCEPT << 1)  /**< Shifted mode ACCEPT for ECA_CONTROL         */
#define ECA_CONTROL_QCHANNELMODE_DENY                  (_ECA_CONTROL_QCHANNELMODE_DENY << 1)    /**< Shifted mode DENY for ECA_CONTROL           */

/* Bit fields for ECA STATUS */
#define _ECA_STATUS_RESETVALUE                         0x00000000UL                                /**< Default value for ECA_STATUS                */
#define _ECA_STATUS_MASK                               0x0000000FUL                                /**< Mask for ECA_STATUS                         */
#define _ECA_STATUS_RUNMODE_SHIFT                      0                                           /**< Shift value for ECA_RUNMODE                 */
#define _ECA_STATUS_RUNMODE_MASK                       0x3UL                                       /**< Bit mask for ECA_RUNMODE                    */
#define _ECA_STATUS_RUNMODE_DEFAULT                    0x00000000UL                                /**< Mode DEFAULT for ECA_STATUS                 */
#define _ECA_STATUS_RUNMODE_DISABLED                   0x00000000UL                                /**< Mode DISABLED for ECA_STATUS                */
#define _ECA_STATUS_RUNMODE_CAPTURE                    0x00000001UL                                /**< Mode CAPTURE for ECA_STATUS                 */
#define _ECA_STATUS_RUNMODE_PLAYBACK                   0x00000002UL                                /**< Mode PLAYBACK for ECA_STATUS                */
#define ECA_STATUS_RUNMODE_DEFAULT                     (_ECA_STATUS_RUNMODE_DEFAULT << 0)          /**< Shifted mode DEFAULT for ECA_STATUS         */
#define ECA_STATUS_RUNMODE_DISABLED                    (_ECA_STATUS_RUNMODE_DISABLED << 0)         /**< Shifted mode DISABLED for ECA_STATUS        */
#define ECA_STATUS_RUNMODE_CAPTURE                     (_ECA_STATUS_RUNMODE_CAPTURE << 0)          /**< Shifted mode CAPTURE for ECA_STATUS         */
#define ECA_STATUS_RUNMODE_PLAYBACK                    (_ECA_STATUS_RUNMODE_PLAYBACK << 0)         /**< Shifted mode PLAYBACK for ECA_STATUS        */
#define ECA_STATUS_SYNCBUSY                            (0x1UL << 2)                                /**< Sync Busy                                   */
#define _ECA_STATUS_SYNCBUSY_SHIFT                     2                                           /**< Shift value for ECA_SYNCBUSY                */
#define _ECA_STATUS_SYNCBUSY_MASK                      0x4UL                                       /**< Bit mask for ECA_SYNCBUSY                   */
#define _ECA_STATUS_SYNCBUSY_DEFAULT                   0x00000000UL                                /**< Mode DEFAULT for ECA_STATUS                 */
#define ECA_STATUS_SYNCBUSY_DEFAULT                    (_ECA_STATUS_SYNCBUSY_DEFAULT << 2)         /**< Shifted mode DEFAULT for ECA_STATUS         */
#define ECA_STATUS_EVENTCNTRSTARTED                    (0x1UL << 3)                                /**< Event Counter Started                       */
#define _ECA_STATUS_EVENTCNTRSTARTED_SHIFT             3                                           /**< Shift value for ECA_EVENTCNTRSTARTED        */
#define _ECA_STATUS_EVENTCNTRSTARTED_MASK              0x8UL                                       /**< Bit mask for ECA_EVENTCNTRSTARTED           */
#define _ECA_STATUS_EVENTCNTRSTARTED_DEFAULT           0x00000000UL                                /**< Mode DEFAULT for ECA_STATUS                 */
#define ECA_STATUS_EVENTCNTRSTARTED_DEFAULT            (_ECA_STATUS_EVENTCNTRSTARTED_DEFAULT << 3) /**< Shifted mode DEFAULT for ECA_STATUS         */

/* Bit fields for ECA IF */
#define _ECA_IF_RESETVALUE                             0x00000000UL                          /**< Default value for ECA_IF                    */
#define _ECA_IF_MASK                                   0x00003FFFUL                          /**< Mask for ECA_IF                             */
#define ECA_IF_BUF0WMIND                               (0x1UL << 0)                          /**< BUF0 Watermark Indication                   */
#define _ECA_IF_BUF0WMIND_SHIFT                        0                                     /**< Shift value for ECA_BUF0WMIND               */
#define _ECA_IF_BUF0WMIND_MASK                         0x1UL                                 /**< Bit mask for ECA_BUF0WMIND                  */
#define _ECA_IF_BUF0WMIND_DEFAULT                      0x00000000UL                          /**< Mode DEFAULT for ECA_IF                     */
#define ECA_IF_BUF0WMIND_DEFAULT                       (_ECA_IF_BUF0WMIND_DEFAULT << 0)      /**< Shifted mode DEFAULT for ECA_IF             */
#define ECA_IF_BUF1WMIND                               (0x1UL << 1)                          /**< BUF1 Watermark Indication                   */
#define _ECA_IF_BUF1WMIND_SHIFT                        1                                     /**< Shift value for ECA_BUF1WMIND               */
#define _ECA_IF_BUF1WMIND_MASK                         0x2UL                                 /**< Bit mask for ECA_BUF1WMIND                  */
#define _ECA_IF_BUF1WMIND_DEFAULT                      0x00000000UL                          /**< Mode DEFAULT for ECA_IF                     */
#define ECA_IF_BUF1WMIND_DEFAULT                       (_ECA_IF_BUF1WMIND_DEFAULT << 1)      /**< Shifted mode DEFAULT for ECA_IF             */
#define ECA_IF_BUF0FULLIND                             (0x1UL << 2)                          /**< BUF0 Full Indication                        */
#define _ECA_IF_BUF0FULLIND_SHIFT                      2                                     /**< Shift value for ECA_BUF0FULLIND             */
#define _ECA_IF_BUF0FULLIND_MASK                       0x4UL                                 /**< Bit mask for ECA_BUF0FULLIND                */
#define _ECA_IF_BUF0FULLIND_DEFAULT                    0x00000000UL                          /**< Mode DEFAULT for ECA_IF                     */
#define ECA_IF_BUF0FULLIND_DEFAULT                     (_ECA_IF_BUF0FULLIND_DEFAULT << 2)    /**< Shifted mode DEFAULT for ECA_IF             */
#define ECA_IF_BUF1FULLIND                             (0x1UL << 3)                          /**< BUF1 Full Indication                        */
#define _ECA_IF_BUF1FULLIND_SHIFT                      3                                     /**< Shift value for ECA_BUF1FULLIND             */
#define _ECA_IF_BUF1FULLIND_MASK                       0x8UL                                 /**< Bit mask for ECA_BUF1FULLIND                */
#define _ECA_IF_BUF1FULLIND_DEFAULT                    0x00000000UL                          /**< Mode DEFAULT for ECA_IF                     */
#define ECA_IF_BUF1FULLIND_DEFAULT                     (_ECA_IF_BUF1FULLIND_DEFAULT << 3)    /**< Shifted mode DEFAULT for ECA_IF             */
#define ECA_IF_STARTTRIG                               (0x1UL << 4)                          /**< Start Trigger                               */
#define _ECA_IF_STARTTRIG_SHIFT                        4                                     /**< Shift value for ECA_STARTTRIG               */
#define _ECA_IF_STARTTRIG_MASK                         0x10UL                                /**< Bit mask for ECA_STARTTRIG                  */
#define _ECA_IF_STARTTRIG_DEFAULT                      0x00000000UL                          /**< Mode DEFAULT for ECA_IF                     */
#define ECA_IF_STARTTRIG_DEFAULT                       (_ECA_IF_STARTTRIG_DEFAULT << 4)      /**< Shifted mode DEFAULT for ECA_IF             */
#define ECA_IF_STOPTRIG                                (0x1UL << 5)                          /**< Stop Trigger                                */
#define _ECA_IF_STOPTRIG_SHIFT                         5                                     /**< Shift value for ECA_STOPTRIG                */
#define _ECA_IF_STOPTRIG_MASK                          0x20UL                                /**< Bit mask for ECA_STOPTRIG                   */
#define _ECA_IF_STOPTRIG_DEFAULT                       0x00000000UL                          /**< Mode DEFAULT for ECA_IF                     */
#define ECA_IF_STOPTRIG_DEFAULT                        (_ECA_IF_STOPTRIG_DEFAULT << 5)       /**< Shifted mode DEFAULT for ECA_IF             */
#define ECA_IF_CAPTURESTART                            (0x1UL << 6)                          /**< Capture Start                               */
#define _ECA_IF_CAPTURESTART_SHIFT                     6                                     /**< Shift value for ECA_CAPTURESTART            */
#define _ECA_IF_CAPTURESTART_MASK                      0x40UL                                /**< Bit mask for ECA_CAPTURESTART               */
#define _ECA_IF_CAPTURESTART_DEFAULT                   0x00000000UL                          /**< Mode DEFAULT for ECA_IF                     */
#define ECA_IF_CAPTURESTART_DEFAULT                    (_ECA_IF_CAPTURESTART_DEFAULT << 6)   /**< Shifted mode DEFAULT for ECA_IF             */
#define ECA_IF_CAPTUREEND                              (0x1UL << 7)                          /**< Capture End                                 */
#define _ECA_IF_CAPTUREEND_SHIFT                       7                                     /**< Shift value for ECA_CAPTUREEND              */
#define _ECA_IF_CAPTUREEND_MASK                        0x80UL                                /**< Bit mask for ECA_CAPTUREEND                 */
#define _ECA_IF_CAPTUREEND_DEFAULT                     0x00000000UL                          /**< Mode DEFAULT for ECA_IF                     */
#define ECA_IF_CAPTUREEND_DEFAULT                      (_ECA_IF_CAPTUREEND_DEFAULT << 7)     /**< Shifted mode DEFAULT for ECA_IF             */
#define ECA_IF_PLAYBACKSTART                           (0x1UL << 8)                          /**< Playback Start                              */
#define _ECA_IF_PLAYBACKSTART_SHIFT                    8                                     /**< Shift value for ECA_PLAYBACKSTART           */
#define _ECA_IF_PLAYBACKSTART_MASK                     0x100UL                               /**< Bit mask for ECA_PLAYBACKSTART              */
#define _ECA_IF_PLAYBACKSTART_DEFAULT                  0x00000000UL                          /**< Mode DEFAULT for ECA_IF                     */
#define ECA_IF_PLAYBACKSTART_DEFAULT                   (_ECA_IF_PLAYBACKSTART_DEFAULT << 8)  /**< Shifted mode DEFAULT for ECA_IF             */
#define ECA_IF_PLAYBACKEND                             (0x1UL << 9)                          /**< Playback End                                */
#define _ECA_IF_PLAYBACKEND_SHIFT                      9                                     /**< Shift value for ECA_PLAYBACKEND             */
#define _ECA_IF_PLAYBACKEND_MASK                       0x200UL                               /**< Bit mask for ECA_PLAYBACKEND                */
#define _ECA_IF_PLAYBACKEND_DEFAULT                    0x00000000UL                          /**< Mode DEFAULT for ECA_IF                     */
#define ECA_IF_PLAYBACKEND_DEFAULT                     (_ECA_IF_PLAYBACKEND_DEFAULT << 9)    /**< Shifted mode DEFAULT for ECA_IF             */
#define ECA_IF_EVENTCNTRCOMP                           (0x1UL << 10)                         /**< Event Counter Compare                       */
#define _ECA_IF_EVENTCNTRCOMP_SHIFT                    10                                    /**< Shift value for ECA_EVENTCNTRCOMP           */
#define _ECA_IF_EVENTCNTRCOMP_MASK                     0x400UL                               /**< Bit mask for ECA_EVENTCNTRCOMP              */
#define _ECA_IF_EVENTCNTRCOMP_DEFAULT                  0x00000000UL                          /**< Mode DEFAULT for ECA_IF                     */
#define ECA_IF_EVENTCNTRCOMP_DEFAULT                   (_ECA_IF_EVENTCNTRCOMP_DEFAULT << 10) /**< Shifted mode DEFAULT for ECA_IF             */
#define ECA_IF_FIFOORERROR                             (0x1UL << 11)                         /**< FIFO Overrun Error                          */
#define _ECA_IF_FIFOORERROR_SHIFT                      11                                    /**< Shift value for ECA_FIFOORERROR             */
#define _ECA_IF_FIFOORERROR_MASK                       0x800UL                               /**< Bit mask for ECA_FIFOORERROR                */
#define _ECA_IF_FIFOORERROR_DEFAULT                    0x00000000UL                          /**< Mode DEFAULT for ECA_IF                     */
#define ECA_IF_FIFOORERROR_DEFAULT                     (_ECA_IF_FIFOORERROR_DEFAULT << 11)   /**< Shifted mode DEFAULT for ECA_IF             */
#define ECA_IF_FIFOURERROR                             (0x1UL << 12)                         /**< FIFO Underrun Error                         */
#define _ECA_IF_FIFOURERROR_SHIFT                      12                                    /**< Shift value for ECA_FIFOURERROR             */
#define _ECA_IF_FIFOURERROR_MASK                       0x1000UL                              /**< Bit mask for ECA_FIFOURERROR                */
#define _ECA_IF_FIFOURERROR_DEFAULT                    0x00000000UL                          /**< Mode DEFAULT for ECA_IF                     */
#define ECA_IF_FIFOURERROR_DEFAULT                     (_ECA_IF_FIFOURERROR_DEFAULT << 12)   /**< Shifted mode DEFAULT for ECA_IF             */
#define ECA_IF_DMABUSERROR                             (0x1UL << 13)                         /**< DMA Bus Error                               */
#define _ECA_IF_DMABUSERROR_SHIFT                      13                                    /**< Shift value for ECA_DMABUSERROR             */
#define _ECA_IF_DMABUSERROR_MASK                       0x2000UL                              /**< Bit mask for ECA_DMABUSERROR                */
#define _ECA_IF_DMABUSERROR_DEFAULT                    0x00000000UL                          /**< Mode DEFAULT for ECA_IF                     */
#define ECA_IF_DMABUSERROR_DEFAULT                     (_ECA_IF_DMABUSERROR_DEFAULT << 13)   /**< Shifted mode DEFAULT for ECA_IF             */

/* Bit fields for ECA IEN */
#define _ECA_IEN_RESETVALUE                            0x00000000UL                           /**< Default value for ECA_IEN                   */
#define _ECA_IEN_MASK                                  0x00003FFFUL                           /**< Mask for ECA_IEN                            */
#define ECA_IEN_BUF0WMIND                              (0x1UL << 0)                           /**< New BitField                                */
#define _ECA_IEN_BUF0WMIND_SHIFT                       0                                      /**< Shift value for ECA_BUF0WMIND               */
#define _ECA_IEN_BUF0WMIND_MASK                        0x1UL                                  /**< Bit mask for ECA_BUF0WMIND                  */
#define _ECA_IEN_BUF0WMIND_DEFAULT                     0x00000000UL                           /**< Mode DEFAULT for ECA_IEN                    */
#define ECA_IEN_BUF0WMIND_DEFAULT                      (_ECA_IEN_BUF0WMIND_DEFAULT << 0)      /**< Shifted mode DEFAULT for ECA_IEN            */
#define ECA_IEN_BUF1WMIND                              (0x1UL << 1)                           /**< New BitField                                */
#define _ECA_IEN_BUF1WMIND_SHIFT                       1                                      /**< Shift value for ECA_BUF1WMIND               */
#define _ECA_IEN_BUF1WMIND_MASK                        0x2UL                                  /**< Bit mask for ECA_BUF1WMIND                  */
#define _ECA_IEN_BUF1WMIND_DEFAULT                     0x00000000UL                           /**< Mode DEFAULT for ECA_IEN                    */
#define ECA_IEN_BUF1WMIND_DEFAULT                      (_ECA_IEN_BUF1WMIND_DEFAULT << 1)      /**< Shifted mode DEFAULT for ECA_IEN            */
#define ECA_IEN_BUF0FULLIND                            (0x1UL << 2)                           /**< New BitField                                */
#define _ECA_IEN_BUF0FULLIND_SHIFT                     2                                      /**< Shift value for ECA_BUF0FULLIND             */
#define _ECA_IEN_BUF0FULLIND_MASK                      0x4UL                                  /**< Bit mask for ECA_BUF0FULLIND                */
#define _ECA_IEN_BUF0FULLIND_DEFAULT                   0x00000000UL                           /**< Mode DEFAULT for ECA_IEN                    */
#define ECA_IEN_BUF0FULLIND_DEFAULT                    (_ECA_IEN_BUF0FULLIND_DEFAULT << 2)    /**< Shifted mode DEFAULT for ECA_IEN            */
#define ECA_IEN_BUF1FULLIND                            (0x1UL << 3)                           /**< New BitField                                */
#define _ECA_IEN_BUF1FULLIND_SHIFT                     3                                      /**< Shift value for ECA_BUF1FULLIND             */
#define _ECA_IEN_BUF1FULLIND_MASK                      0x8UL                                  /**< Bit mask for ECA_BUF1FULLIND                */
#define _ECA_IEN_BUF1FULLIND_DEFAULT                   0x00000000UL                           /**< Mode DEFAULT for ECA_IEN                    */
#define ECA_IEN_BUF1FULLIND_DEFAULT                    (_ECA_IEN_BUF1FULLIND_DEFAULT << 3)    /**< Shifted mode DEFAULT for ECA_IEN            */
#define ECA_IEN_STARTTRIG                              (0x1UL << 4)                           /**< New BitField                                */
#define _ECA_IEN_STARTTRIG_SHIFT                       4                                      /**< Shift value for ECA_STARTTRIG               */
#define _ECA_IEN_STARTTRIG_MASK                        0x10UL                                 /**< Bit mask for ECA_STARTTRIG                  */
#define _ECA_IEN_STARTTRIG_DEFAULT                     0x00000000UL                           /**< Mode DEFAULT for ECA_IEN                    */
#define ECA_IEN_STARTTRIG_DEFAULT                      (_ECA_IEN_STARTTRIG_DEFAULT << 4)      /**< Shifted mode DEFAULT for ECA_IEN            */
#define ECA_IEN_STOPTRIG                               (0x1UL << 5)                           /**< New BitField                                */
#define _ECA_IEN_STOPTRIG_SHIFT                        5                                      /**< Shift value for ECA_STOPTRIG                */
#define _ECA_IEN_STOPTRIG_MASK                         0x20UL                                 /**< Bit mask for ECA_STOPTRIG                   */
#define _ECA_IEN_STOPTRIG_DEFAULT                      0x00000000UL                           /**< Mode DEFAULT for ECA_IEN                    */
#define ECA_IEN_STOPTRIG_DEFAULT                       (_ECA_IEN_STOPTRIG_DEFAULT << 5)       /**< Shifted mode DEFAULT for ECA_IEN            */
#define ECA_IEN_CAPTURESTART                           (0x1UL << 6)                           /**< New BitField                                */
#define _ECA_IEN_CAPTURESTART_SHIFT                    6                                      /**< Shift value for ECA_CAPTURESTART            */
#define _ECA_IEN_CAPTURESTART_MASK                     0x40UL                                 /**< Bit mask for ECA_CAPTURESTART               */
#define _ECA_IEN_CAPTURESTART_DEFAULT                  0x00000000UL                           /**< Mode DEFAULT for ECA_IEN                    */
#define ECA_IEN_CAPTURESTART_DEFAULT                   (_ECA_IEN_CAPTURESTART_DEFAULT << 6)   /**< Shifted mode DEFAULT for ECA_IEN            */
#define ECA_IEN_CAPTUREEND                             (0x1UL << 7)                           /**< New BitField                                */
#define _ECA_IEN_CAPTUREEND_SHIFT                      7                                      /**< Shift value for ECA_CAPTUREEND              */
#define _ECA_IEN_CAPTUREEND_MASK                       0x80UL                                 /**< Bit mask for ECA_CAPTUREEND                 */
#define _ECA_IEN_CAPTUREEND_DEFAULT                    0x00000000UL                           /**< Mode DEFAULT for ECA_IEN                    */
#define ECA_IEN_CAPTUREEND_DEFAULT                     (_ECA_IEN_CAPTUREEND_DEFAULT << 7)     /**< Shifted mode DEFAULT for ECA_IEN            */
#define ECA_IEN_PLAYBACKSTART                          (0x1UL << 8)                           /**< New BitField                                */
#define _ECA_IEN_PLAYBACKSTART_SHIFT                   8                                      /**< Shift value for ECA_PLAYBACKSTART           */
#define _ECA_IEN_PLAYBACKSTART_MASK                    0x100UL                                /**< Bit mask for ECA_PLAYBACKSTART              */
#define _ECA_IEN_PLAYBACKSTART_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for ECA_IEN                    */
#define ECA_IEN_PLAYBACKSTART_DEFAULT                  (_ECA_IEN_PLAYBACKSTART_DEFAULT << 8)  /**< Shifted mode DEFAULT for ECA_IEN            */
#define ECA_IEN_PLAYBACKEND                            (0x1UL << 9)                           /**< New BitField                                */
#define _ECA_IEN_PLAYBACKEND_SHIFT                     9                                      /**< Shift value for ECA_PLAYBACKEND             */
#define _ECA_IEN_PLAYBACKEND_MASK                      0x200UL                                /**< Bit mask for ECA_PLAYBACKEND                */
#define _ECA_IEN_PLAYBACKEND_DEFAULT                   0x00000000UL                           /**< Mode DEFAULT for ECA_IEN                    */
#define ECA_IEN_PLAYBACKEND_DEFAULT                    (_ECA_IEN_PLAYBACKEND_DEFAULT << 9)    /**< Shifted mode DEFAULT for ECA_IEN            */
#define ECA_IEN_EVENTCNTRCOMP                          (0x1UL << 10)                          /**< New BitField                                */
#define _ECA_IEN_EVENTCNTRCOMP_SHIFT                   10                                     /**< Shift value for ECA_EVENTCNTRCOMP           */
#define _ECA_IEN_EVENTCNTRCOMP_MASK                    0x400UL                                /**< Bit mask for ECA_EVENTCNTRCOMP              */
#define _ECA_IEN_EVENTCNTRCOMP_DEFAULT                 0x00000000UL                           /**< Mode DEFAULT for ECA_IEN                    */
#define ECA_IEN_EVENTCNTRCOMP_DEFAULT                  (_ECA_IEN_EVENTCNTRCOMP_DEFAULT << 10) /**< Shifted mode DEFAULT for ECA_IEN            */
#define ECA_IEN_FIFOORERROR                            (0x1UL << 11)                          /**< New BitField                                */
#define _ECA_IEN_FIFOORERROR_SHIFT                     11                                     /**< Shift value for ECA_FIFOORERROR             */
#define _ECA_IEN_FIFOORERROR_MASK                      0x800UL                                /**< Bit mask for ECA_FIFOORERROR                */
#define _ECA_IEN_FIFOORERROR_DEFAULT                   0x00000000UL                           /**< Mode DEFAULT for ECA_IEN                    */
#define ECA_IEN_FIFOORERROR_DEFAULT                    (_ECA_IEN_FIFOORERROR_DEFAULT << 11)   /**< Shifted mode DEFAULT for ECA_IEN            */
#define ECA_IEN_FIFOURERROR                            (0x1UL << 12)                          /**< New BitField                                */
#define _ECA_IEN_FIFOURERROR_SHIFT                     12                                     /**< Shift value for ECA_FIFOURERROR             */
#define _ECA_IEN_FIFOURERROR_MASK                      0x1000UL                               /**< Bit mask for ECA_FIFOURERROR                */
#define _ECA_IEN_FIFOURERROR_DEFAULT                   0x00000000UL                           /**< Mode DEFAULT for ECA_IEN                    */
#define ECA_IEN_FIFOURERROR_DEFAULT                    (_ECA_IEN_FIFOURERROR_DEFAULT << 12)   /**< Shifted mode DEFAULT for ECA_IEN            */
#define ECA_IEN_DMABUSERROR                            (0x1UL << 13)                          /**< New BitField                                */
#define _ECA_IEN_DMABUSERROR_SHIFT                     13                                     /**< Shift value for ECA_DMABUSERROR             */
#define _ECA_IEN_DMABUSERROR_MASK                      0x2000UL                               /**< Bit mask for ECA_DMABUSERROR                */
#define _ECA_IEN_DMABUSERROR_DEFAULT                   0x00000000UL                           /**< Mode DEFAULT for ECA_IEN                    */
#define ECA_IEN_DMABUSERROR_DEFAULT                    (_ECA_IEN_DMABUSERROR_DEFAULT << 13)   /**< Shifted mode DEFAULT for ECA_IEN            */

/* Bit fields for ECA DMABUSERRORSTATUS */
#define _ECA_DMABUSERRORSTATUS_RESETVALUE              0x00000000UL                               /**< Default value for ECA_DMABUSERRORSTATUS     */
#define _ECA_DMABUSERRORSTATUS_MASK                    0xFFFFFFFFUL                               /**< Mask for ECA_DMABUSERRORSTATUS              */
#define _ECA_DMABUSERRORSTATUS_ADDR_SHIFT              0                                          /**< Shift value for ECA_ADDR                    */
#define _ECA_DMABUSERRORSTATUS_ADDR_MASK               0xFFFFFFFFUL                               /**< Bit mask for ECA_ADDR                       */
#define _ECA_DMABUSERRORSTATUS_ADDR_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for ECA_DMABUSERRORSTATUS      */
#define ECA_DMABUSERRORSTATUS_ADDR_DEFAULT             (_ECA_DMABUSERRORSTATUS_ADDR_DEFAULT << 0) /**< Shifted mode DEFAULT for ECA_DMABUSERRORSTATUS*/

/* Bit fields for ECA BUF_BASE */
#define _ECA_BUF_BASE_RESETVALUE                       0x00000000UL                      /**< Default value for ECA_BUF_BASE              */
#define _ECA_BUF_BASE_MASK                             0xFFFFFFFFUL                      /**< Mask for ECA_BUF_BASE                       */
#define _ECA_BUF_BASE_BASE_SHIFT                       0                                 /**< Shift value for ECA_BASE                    */
#define _ECA_BUF_BASE_BASE_MASK                        0xFFFFFFFFUL                      /**< Bit mask for ECA_BASE                       */
#define _ECA_BUF_BASE_BASE_DEFAULT                     0x00000000UL                      /**< Mode DEFAULT for ECA_BUF_BASE               */
#define ECA_BUF_BASE_BASE_DEFAULT                      (_ECA_BUF_BASE_BASE_DEFAULT << 0) /**< Shifted mode DEFAULT for ECA_BUF_BASE       */

/* Bit fields for ECA BUF_LIMITOFFSET */
#define _ECA_BUF_LIMITOFFSET_RESETVALUE                0x00000000UL                               /**< Default value for ECA_BUF_LIMITOFFSET       */
#define _ECA_BUF_LIMITOFFSET_MASK                      0x0007FFFCUL                               /**< Mask for ECA_BUF_LIMITOFFSET                */
#define _ECA_BUF_LIMITOFFSET_OFFSET_SHIFT              2                                          /**< Shift value for ECA_OFFSET                  */
#define _ECA_BUF_LIMITOFFSET_OFFSET_MASK               0x7FFFCUL                                  /**< Bit mask for ECA_OFFSET                     */
#define _ECA_BUF_LIMITOFFSET_OFFSET_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for ECA_BUF_LIMITOFFSET        */
#define ECA_BUF_LIMITOFFSET_OFFSET_DEFAULT             (_ECA_BUF_LIMITOFFSET_OFFSET_DEFAULT << 2) /**< Shifted mode DEFAULT for ECA_BUF_LIMITOFFSET*/

/* Bit fields for ECA BUF_WMOFFSET */
#define _ECA_BUF_WMOFFSET_RESETVALUE                   0x00000000UL                            /**< Default value for ECA_BUF_WMOFFSET          */
#define _ECA_BUF_WMOFFSET_MASK                         0x0007FFFCUL                            /**< Mask for ECA_BUF_WMOFFSET                   */
#define _ECA_BUF_WMOFFSET_OFFSET_SHIFT                 2                                       /**< Shift value for ECA_OFFSET                  */
#define _ECA_BUF_WMOFFSET_OFFSET_MASK                  0x7FFFCUL                               /**< Bit mask for ECA_OFFSET                     */
#define _ECA_BUF_WMOFFSET_OFFSET_DEFAULT               0x00000000UL                            /**< Mode DEFAULT for ECA_BUF_WMOFFSET           */
#define ECA_BUF_WMOFFSET_OFFSET_DEFAULT                (_ECA_BUF_WMOFFSET_OFFSET_DEFAULT << 2) /**< Shifted mode DEFAULT for ECA_BUF_WMOFFSET   */

/* Bit fields for ECA BUFPTRSTATUS */
#define _ECA_BUFPTRSTATUS_RESETVALUE                   0x00000000UL                            /**< Default value for ECA_BUFPTRSTATUS          */
#define _ECA_BUFPTRSTATUS_MASK                         0xFFFFFFFFUL                            /**< Mask for ECA_BUFPTRSTATUS                   */
#define _ECA_BUFPTRSTATUS_STATUS_SHIFT                 0                                       /**< Shift value for ECA_STATUS                  */
#define _ECA_BUFPTRSTATUS_STATUS_MASK                  0xFFFFFFFFUL                            /**< Bit mask for ECA_STATUS                     */
#define _ECA_BUFPTRSTATUS_STATUS_DEFAULT               0x00000000UL                            /**< Mode DEFAULT for ECA_BUFPTRSTATUS           */
#define ECA_BUFPTRSTATUS_STATUS_DEFAULT                (_ECA_BUFPTRSTATUS_STATUS_DEFAULT << 0) /**< Shifted mode DEFAULT for ECA_BUFPTRSTATUS   */

/* Bit fields for ECA STARTTRIGCTRL */
#define _ECA_STARTTRIGCTRL_RESETVALUE                  0x00000000UL                               /**< Default value for ECA_STARTTRIGCTRL         */
#define _ECA_STARTTRIGCTRL_MASK                        0x0000001FUL                               /**< Mask for ECA_STARTTRIGCTRL                  */
#define _ECA_STARTTRIGCTRL_TRACESEL_SHIFT              0                                          /**< Shift value for ECA_TRACESEL                */
#define _ECA_STARTTRIGCTRL_TRACESEL_MASK               0x7UL                                      /**< Bit mask for ECA_TRACESEL                   */
#define _ECA_STARTTRIGCTRL_TRACESEL_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for ECA_STARTTRIGCTRL          */
#define ECA_STARTTRIGCTRL_TRACESEL_DEFAULT             (_ECA_STARTTRIGCTRL_TRACESEL_DEFAULT << 0) /**< Shifted mode DEFAULT for ECA_STARTTRIGCTRL  */
#define ECA_STARTTRIGCTRL_ENABLE                       (0x1UL << 3)                               /**< Enable                                      */
#define _ECA_STARTTRIGCTRL_ENABLE_SHIFT                3                                          /**< Shift value for ECA_ENABLE                  */
#define _ECA_STARTTRIGCTRL_ENABLE_MASK                 0x8UL                                      /**< Bit mask for ECA_ENABLE                     */
#define _ECA_STARTTRIGCTRL_ENABLE_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for ECA_STARTTRIGCTRL          */
#define ECA_STARTTRIGCTRL_ENABLE_DEFAULT               (_ECA_STARTTRIGCTRL_ENABLE_DEFAULT << 3)   /**< Shifted mode DEFAULT for ECA_STARTTRIGCTRL  */
#define ECA_STARTTRIGCTRL_COMBMODE                     (0x1UL << 4)                               /**< Combination Mode                            */
#define _ECA_STARTTRIGCTRL_COMBMODE_SHIFT              4                                          /**< Shift value for ECA_COMBMODE                */
#define _ECA_STARTTRIGCTRL_COMBMODE_MASK               0x10UL                                     /**< Bit mask for ECA_COMBMODE                   */
#define _ECA_STARTTRIGCTRL_COMBMODE_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for ECA_STARTTRIGCTRL          */
#define _ECA_STARTTRIGCTRL_COMBMODE_AND                0x00000000UL                               /**< Mode AND for ECA_STARTTRIGCTRL              */
#define _ECA_STARTTRIGCTRL_COMBMODE_OR                 0x00000001UL                               /**< Mode OR for ECA_STARTTRIGCTRL               */
#define ECA_STARTTRIGCTRL_COMBMODE_DEFAULT             (_ECA_STARTTRIGCTRL_COMBMODE_DEFAULT << 4) /**< Shifted mode DEFAULT for ECA_STARTTRIGCTRL  */
#define ECA_STARTTRIGCTRL_COMBMODE_AND                 (_ECA_STARTTRIGCTRL_COMBMODE_AND << 4)     /**< Shifted mode AND for ECA_STARTTRIGCTRL      */
#define ECA_STARTTRIGCTRL_COMBMODE_OR                  (_ECA_STARTTRIGCTRL_COMBMODE_OR << 4)      /**< Shifted mode OR for ECA_STARTTRIGCTRL       */

/* Bit fields for ECA STOPTRIGCTRL */
#define _ECA_STOPTRIGCTRL_RESETVALUE                   0x00000000UL                              /**< Default value for ECA_STOPTRIGCTRL          */
#define _ECA_STOPTRIGCTRL_MASK                         0x0000001FUL                              /**< Mask for ECA_STOPTRIGCTRL                   */
#define _ECA_STOPTRIGCTRL_TRACESEL_SHIFT               0                                         /**< Shift value for ECA_TRACESEL                */
#define _ECA_STOPTRIGCTRL_TRACESEL_MASK                0x7UL                                     /**< Bit mask for ECA_TRACESEL                   */
#define _ECA_STOPTRIGCTRL_TRACESEL_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for ECA_STOPTRIGCTRL           */
#define ECA_STOPTRIGCTRL_TRACESEL_DEFAULT              (_ECA_STOPTRIGCTRL_TRACESEL_DEFAULT << 0) /**< Shifted mode DEFAULT for ECA_STOPTRIGCTRL   */
#define ECA_STOPTRIGCTRL_ENABLE                        (0x1UL << 3)                              /**< Enable                                      */
#define _ECA_STOPTRIGCTRL_ENABLE_SHIFT                 3                                         /**< Shift value for ECA_ENABLE                  */
#define _ECA_STOPTRIGCTRL_ENABLE_MASK                  0x8UL                                     /**< Bit mask for ECA_ENABLE                     */
#define _ECA_STOPTRIGCTRL_ENABLE_DEFAULT               0x00000000UL                              /**< Mode DEFAULT for ECA_STOPTRIGCTRL           */
#define ECA_STOPTRIGCTRL_ENABLE_DEFAULT                (_ECA_STOPTRIGCTRL_ENABLE_DEFAULT << 3)   /**< Shifted mode DEFAULT for ECA_STOPTRIGCTRL   */
#define ECA_STOPTRIGCTRL_COMBMODE                      (0x1UL << 4)                              /**< Combination Mode                            */
#define _ECA_STOPTRIGCTRL_COMBMODE_SHIFT               4                                         /**< Shift value for ECA_COMBMODE                */
#define _ECA_STOPTRIGCTRL_COMBMODE_MASK                0x10UL                                    /**< Bit mask for ECA_COMBMODE                   */
#define _ECA_STOPTRIGCTRL_COMBMODE_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for ECA_STOPTRIGCTRL           */
#define _ECA_STOPTRIGCTRL_COMBMODE_AND                 0x00000000UL                              /**< Mode AND for ECA_STOPTRIGCTRL               */
#define _ECA_STOPTRIGCTRL_COMBMODE_OR                  0x00000001UL                              /**< Mode OR for ECA_STOPTRIGCTRL                */
#define ECA_STOPTRIGCTRL_COMBMODE_DEFAULT              (_ECA_STOPTRIGCTRL_COMBMODE_DEFAULT << 4) /**< Shifted mode DEFAULT for ECA_STOPTRIGCTRL   */
#define ECA_STOPTRIGCTRL_COMBMODE_AND                  (_ECA_STOPTRIGCTRL_COMBMODE_AND << 4)     /**< Shifted mode AND for ECA_STOPTRIGCTRL       */
#define ECA_STOPTRIGCTRL_COMBMODE_OR                   (_ECA_STOPTRIGCTRL_COMBMODE_OR << 4)      /**< Shifted mode OR for ECA_STOPTRIGCTRL        */

/* Bit fields for ECA STARTTRIGENMASK */
#define _ECA_STARTTRIGENMASK_RESETVALUE                0x00000000UL                               /**< Default value for ECA_STARTTRIGENMASK       */
#define _ECA_STARTTRIGENMASK_MASK                      0xFFFFFFFFUL                               /**< Mask for ECA_STARTTRIGENMASK                */
#define _ECA_STARTTRIGENMASK_ENMASK_SHIFT              0                                          /**< Shift value for ECA_ENMASK                  */
#define _ECA_STARTTRIGENMASK_ENMASK_MASK               0xFFFFFFFFUL                               /**< Bit mask for ECA_ENMASK                     */
#define _ECA_STARTTRIGENMASK_ENMASK_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for ECA_STARTTRIGENMASK        */
#define ECA_STARTTRIGENMASK_ENMASK_DEFAULT             (_ECA_STARTTRIGENMASK_ENMASK_DEFAULT << 0) /**< Shifted mode DEFAULT for ECA_STARTTRIGENMASK*/

/* Bit fields for ECA STARTTRIGREDMASK */
#define _ECA_STARTTRIGREDMASK_RESETVALUE               0x00000000UL                                 /**< Default value for ECA_STARTTRIGREDMASK      */
#define _ECA_STARTTRIGREDMASK_MASK                     0xFFFFFFFFUL                                 /**< Mask for ECA_STARTTRIGREDMASK               */
#define _ECA_STARTTRIGREDMASK_REDMASK_SHIFT            0                                            /**< Shift value for ECA_REDMASK                 */
#define _ECA_STARTTRIGREDMASK_REDMASK_MASK             0xFFFFFFFFUL                                 /**< Bit mask for ECA_REDMASK                    */
#define _ECA_STARTTRIGREDMASK_REDMASK_DEFAULT          0x00000000UL                                 /**< Mode DEFAULT for ECA_STARTTRIGREDMASK       */
#define ECA_STARTTRIGREDMASK_REDMASK_DEFAULT           (_ECA_STARTTRIGREDMASK_REDMASK_DEFAULT << 0) /**< Shifted mode DEFAULT for ECA_STARTTRIGREDMASK*/

/* Bit fields for ECA STARTTRIGFEDMASK */
#define _ECA_STARTTRIGFEDMASK_RESETVALUE               0x00000000UL                                 /**< Default value for ECA_STARTTRIGFEDMASK      */
#define _ECA_STARTTRIGFEDMASK_MASK                     0xFFFFFFFFUL                                 /**< Mask for ECA_STARTTRIGFEDMASK               */
#define _ECA_STARTTRIGFEDMASK_FEDMASK_SHIFT            0                                            /**< Shift value for ECA_FEDMASK                 */
#define _ECA_STARTTRIGFEDMASK_FEDMASK_MASK             0xFFFFFFFFUL                                 /**< Bit mask for ECA_FEDMASK                    */
#define _ECA_STARTTRIGFEDMASK_FEDMASK_DEFAULT          0x00000000UL                                 /**< Mode DEFAULT for ECA_STARTTRIGFEDMASK       */
#define ECA_STARTTRIGFEDMASK_FEDMASK_DEFAULT           (_ECA_STARTTRIGFEDMASK_FEDMASK_DEFAULT << 0) /**< Shifted mode DEFAULT for ECA_STARTTRIGFEDMASK*/

/* Bit fields for ECA STARTTRIGLVL0MASK */
#define _ECA_STARTTRIGLVL0MASK_RESETVALUE              0x00000000UL                                   /**< Default value for ECA_STARTTRIGLVL0MASK     */
#define _ECA_STARTTRIGLVL0MASK_MASK                    0xFFFFFFFFUL                                   /**< Mask for ECA_STARTTRIGLVL0MASK              */
#define _ECA_STARTTRIGLVL0MASK_LVL0MASK_SHIFT          0                                              /**< Shift value for ECA_LVL0MASK                */
#define _ECA_STARTTRIGLVL0MASK_LVL0MASK_MASK           0xFFFFFFFFUL                                   /**< Bit mask for ECA_LVL0MASK                   */
#define _ECA_STARTTRIGLVL0MASK_LVL0MASK_DEFAULT        0x00000000UL                                   /**< Mode DEFAULT for ECA_STARTTRIGLVL0MASK      */
#define ECA_STARTTRIGLVL0MASK_LVL0MASK_DEFAULT         (_ECA_STARTTRIGLVL0MASK_LVL0MASK_DEFAULT << 0) /**< Shifted mode DEFAULT for ECA_STARTTRIGLVL0MASK*/

/* Bit fields for ECA STARTTRIGLVL1MASK */
#define _ECA_STARTTRIGLVL1MASK_RESETVALUE              0x00000000UL                                   /**< Default value for ECA_STARTTRIGLVL1MASK     */
#define _ECA_STARTTRIGLVL1MASK_MASK                    0xFFFFFFFFUL                                   /**< Mask for ECA_STARTTRIGLVL1MASK              */
#define _ECA_STARTTRIGLVL1MASK_LVL1MASK_SHIFT          0                                              /**< Shift value for ECA_LVL1MASK                */
#define _ECA_STARTTRIGLVL1MASK_LVL1MASK_MASK           0xFFFFFFFFUL                                   /**< Bit mask for ECA_LVL1MASK                   */
#define _ECA_STARTTRIGLVL1MASK_LVL1MASK_DEFAULT        0x00000000UL                                   /**< Mode DEFAULT for ECA_STARTTRIGLVL1MASK      */
#define ECA_STARTTRIGLVL1MASK_LVL1MASK_DEFAULT         (_ECA_STARTTRIGLVL1MASK_LVL1MASK_DEFAULT << 0) /**< Shifted mode DEFAULT for ECA_STARTTRIGLVL1MASK*/

/* Bit fields for ECA STOPTRIGENMASK */
#define _ECA_STOPTRIGENMASK_RESETVALUE                 0x00000000UL                              /**< Default value for ECA_STOPTRIGENMASK        */
#define _ECA_STOPTRIGENMASK_MASK                       0xFFFFFFFFUL                              /**< Mask for ECA_STOPTRIGENMASK                 */
#define _ECA_STOPTRIGENMASK_ENMASK_SHIFT               0                                         /**< Shift value for ECA_ENMASK                  */
#define _ECA_STOPTRIGENMASK_ENMASK_MASK                0xFFFFFFFFUL                              /**< Bit mask for ECA_ENMASK                     */
#define _ECA_STOPTRIGENMASK_ENMASK_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for ECA_STOPTRIGENMASK         */
#define ECA_STOPTRIGENMASK_ENMASK_DEFAULT              (_ECA_STOPTRIGENMASK_ENMASK_DEFAULT << 0) /**< Shifted mode DEFAULT for ECA_STOPTRIGENMASK */

/* Bit fields for ECA STOPTRIGREDMASK */
#define _ECA_STOPTRIGREDMASK_RESETVALUE                0x00000000UL                                /**< Default value for ECA_STOPTRIGREDMASK       */
#define _ECA_STOPTRIGREDMASK_MASK                      0xFFFFFFFFUL                                /**< Mask for ECA_STOPTRIGREDMASK                */
#define _ECA_STOPTRIGREDMASK_REDMASK_SHIFT             0                                           /**< Shift value for ECA_REDMASK                 */
#define _ECA_STOPTRIGREDMASK_REDMASK_MASK              0xFFFFFFFFUL                                /**< Bit mask for ECA_REDMASK                    */
#define _ECA_STOPTRIGREDMASK_REDMASK_DEFAULT           0x00000000UL                                /**< Mode DEFAULT for ECA_STOPTRIGREDMASK        */
#define ECA_STOPTRIGREDMASK_REDMASK_DEFAULT            (_ECA_STOPTRIGREDMASK_REDMASK_DEFAULT << 0) /**< Shifted mode DEFAULT for ECA_STOPTRIGREDMASK*/

/* Bit fields for ECA STOPTRIGFEDMASK */
#define _ECA_STOPTRIGFEDMASK_RESETVALUE                0x00000000UL                                /**< Default value for ECA_STOPTRIGFEDMASK       */
#define _ECA_STOPTRIGFEDMASK_MASK                      0xFFFFFFFFUL                                /**< Mask for ECA_STOPTRIGFEDMASK                */
#define _ECA_STOPTRIGFEDMASK_FEDMASK_SHIFT             0                                           /**< Shift value for ECA_FEDMASK                 */
#define _ECA_STOPTRIGFEDMASK_FEDMASK_MASK              0xFFFFFFFFUL                                /**< Bit mask for ECA_FEDMASK                    */
#define _ECA_STOPTRIGFEDMASK_FEDMASK_DEFAULT           0x00000000UL                                /**< Mode DEFAULT for ECA_STOPTRIGFEDMASK        */
#define ECA_STOPTRIGFEDMASK_FEDMASK_DEFAULT            (_ECA_STOPTRIGFEDMASK_FEDMASK_DEFAULT << 0) /**< Shifted mode DEFAULT for ECA_STOPTRIGFEDMASK*/

/* Bit fields for ECA STOPTRIGLVL0MASK */
#define _ECA_STOPTRIGLVL0MASK_RESETVALUE               0x00000000UL                                  /**< Default value for ECA_STOPTRIGLVL0MASK      */
#define _ECA_STOPTRIGLVL0MASK_MASK                     0xFFFFFFFFUL                                  /**< Mask for ECA_STOPTRIGLVL0MASK               */
#define _ECA_STOPTRIGLVL0MASK_LVL0MASK_SHIFT           0                                             /**< Shift value for ECA_LVL0MASK                */
#define _ECA_STOPTRIGLVL0MASK_LVL0MASK_MASK            0xFFFFFFFFUL                                  /**< Bit mask for ECA_LVL0MASK                   */
#define _ECA_STOPTRIGLVL0MASK_LVL0MASK_DEFAULT         0x00000000UL                                  /**< Mode DEFAULT for ECA_STOPTRIGLVL0MASK       */
#define ECA_STOPTRIGLVL0MASK_LVL0MASK_DEFAULT          (_ECA_STOPTRIGLVL0MASK_LVL0MASK_DEFAULT << 0) /**< Shifted mode DEFAULT for ECA_STOPTRIGLVL0MASK*/

/* Bit fields for ECA STOPTRIGLVL1MASK */
#define _ECA_STOPTRIGLVL1MASK_RESETVALUE               0x00000000UL                                  /**< Default value for ECA_STOPTRIGLVL1MASK      */
#define _ECA_STOPTRIGLVL1MASK_MASK                     0xFFFFFFFFUL                                  /**< Mask for ECA_STOPTRIGLVL1MASK               */
#define _ECA_STOPTRIGLVL1MASK_LVL1MASK_SHIFT           0                                             /**< Shift value for ECA_LVL1MASK                */
#define _ECA_STOPTRIGLVL1MASK_LVL1MASK_MASK            0xFFFFFFFFUL                                  /**< Bit mask for ECA_LVL1MASK                   */
#define _ECA_STOPTRIGLVL1MASK_LVL1MASK_DEFAULT         0x00000000UL                                  /**< Mode DEFAULT for ECA_STOPTRIGLVL1MASK       */
#define ECA_STOPTRIGLVL1MASK_LVL1MASK_DEFAULT          (_ECA_STOPTRIGLVL1MASK_LVL1MASK_DEFAULT << 0) /**< Shifted mode DEFAULT for ECA_STOPTRIGLVL1MASK*/

/* Bit fields for ECA CAPTURECTRL */
#define _ECA_CAPTURECTRL_RESETVALUE                    0x00000501UL                                        /**< Default value for ECA_CAPTURECTRL           */
#define _ECA_CAPTURECTRL_MASK                          0x7FF7FFFFUL                                        /**< Mask for ECA_CAPTURECTRL                    */
#define _ECA_CAPTURECTRL_TRACESEL_SHIFT                0                                                   /**< Shift value for ECA_TRACESEL                */
#define _ECA_CAPTURECTRL_TRACESEL_MASK                 0xFFUL                                              /**< Bit mask for ECA_TRACESEL                   */
#define _ECA_CAPTURECTRL_TRACESEL_DEFAULT              0x00000001UL                                        /**< Mode DEFAULT for ECA_CAPTURECTRL            */
#define ECA_CAPTURECTRL_TRACESEL_DEFAULT               (_ECA_CAPTURECTRL_TRACESEL_DEFAULT << 0)            /**< Shifted mode DEFAULT for ECA_CAPTURECTRL    */
#define _ECA_CAPTURECTRL_DATAWIDTH_SHIFT               8                                                   /**< Shift value for ECA_DATAWIDTH               */
#define _ECA_CAPTURECTRL_DATAWIDTH_MASK                0x700UL                                             /**< Bit mask for ECA_DATAWIDTH                  */
#define _ECA_CAPTURECTRL_DATAWIDTH_DEFAULT             0x00000005UL                                        /**< Mode DEFAULT for ECA_CAPTURECTRL            */
#define _ECA_CAPTURECTRL_DATAWIDTH_BIT1                0x00000000UL                                        /**< Mode BIT1 for ECA_CAPTURECTRL               */
#define _ECA_CAPTURECTRL_DATAWIDTH_BIT2                0x00000001UL                                        /**< Mode BIT2 for ECA_CAPTURECTRL               */
#define _ECA_CAPTURECTRL_DATAWIDTH_BIT4                0x00000002UL                                        /**< Mode BIT4 for ECA_CAPTURECTRL               */
#define _ECA_CAPTURECTRL_DATAWIDTH_BIT8                0x00000003UL                                        /**< Mode BIT8 for ECA_CAPTURECTRL               */
#define _ECA_CAPTURECTRL_DATAWIDTH_BIT16               0x00000004UL                                        /**< Mode BIT16 for ECA_CAPTURECTRL              */
#define _ECA_CAPTURECTRL_DATAWIDTH_BIT32               0x00000005UL                                        /**< Mode BIT32 for ECA_CAPTURECTRL              */
#define ECA_CAPTURECTRL_DATAWIDTH_DEFAULT              (_ECA_CAPTURECTRL_DATAWIDTH_DEFAULT << 8)           /**< Shifted mode DEFAULT for ECA_CAPTURECTRL    */
#define ECA_CAPTURECTRL_DATAWIDTH_BIT1                 (_ECA_CAPTURECTRL_DATAWIDTH_BIT1 << 8)              /**< Shifted mode BIT1 for ECA_CAPTURECTRL       */
#define ECA_CAPTURECTRL_DATAWIDTH_BIT2                 (_ECA_CAPTURECTRL_DATAWIDTH_BIT2 << 8)              /**< Shifted mode BIT2 for ECA_CAPTURECTRL       */
#define ECA_CAPTURECTRL_DATAWIDTH_BIT4                 (_ECA_CAPTURECTRL_DATAWIDTH_BIT4 << 8)              /**< Shifted mode BIT4 for ECA_CAPTURECTRL       */
#define ECA_CAPTURECTRL_DATAWIDTH_BIT8                 (_ECA_CAPTURECTRL_DATAWIDTH_BIT8 << 8)              /**< Shifted mode BIT8 for ECA_CAPTURECTRL       */
#define ECA_CAPTURECTRL_DATAWIDTH_BIT16                (_ECA_CAPTURECTRL_DATAWIDTH_BIT16 << 8)             /**< Shifted mode BIT16 for ECA_CAPTURECTRL      */
#define ECA_CAPTURECTRL_DATAWIDTH_BIT32                (_ECA_CAPTURECTRL_DATAWIDTH_BIT32 << 8)             /**< Shifted mode BIT32 for ECA_CAPTURECTRL      */
#define _ECA_CAPTURECTRL_DATAROTATESIZE_SHIFT          11                                                  /**< Shift value for ECA_DATAROTATESIZE          */
#define _ECA_CAPTURECTRL_DATAROTATESIZE_MASK           0xF800UL                                            /**< Bit mask for ECA_DATAROTATESIZE             */
#define _ECA_CAPTURECTRL_DATAROTATESIZE_DEFAULT        0x00000000UL                                        /**< Mode DEFAULT for ECA_CAPTURECTRL            */
#define ECA_CAPTURECTRL_DATAROTATESIZE_DEFAULT         (_ECA_CAPTURECTRL_DATAROTATESIZE_DEFAULT << 11)     /**< Shifted mode DEFAULT for ECA_CAPTURECTRL    */
#define ECA_CAPTURECTRL_STARTMODE                      (0x1UL << 16)                                       /**< Start Mode                                  */
#define _ECA_CAPTURECTRL_STARTMODE_SHIFT               16                                                  /**< Shift value for ECA_STARTMODE               */
#define _ECA_CAPTURECTRL_STARTMODE_MASK                0x10000UL                                           /**< Bit mask for ECA_STARTMODE                  */
#define _ECA_CAPTURECTRL_STARTMODE_DEFAULT             0x00000000UL                                        /**< Mode DEFAULT for ECA_CAPTURECTRL            */
#define _ECA_CAPTURECTRL_STARTMODE_MANUAL              0x00000000UL                                        /**< Mode MANUAL for ECA_CAPTURECTRL             */
#define _ECA_CAPTURECTRL_STARTMODE_START_TRIGGER       0x00000001UL                                        /**< Mode START_TRIGGER for ECA_CAPTURECTRL      */
#define ECA_CAPTURECTRL_STARTMODE_DEFAULT              (_ECA_CAPTURECTRL_STARTMODE_DEFAULT << 16)          /**< Shifted mode DEFAULT for ECA_CAPTURECTRL    */
#define ECA_CAPTURECTRL_STARTMODE_MANUAL               (_ECA_CAPTURECTRL_STARTMODE_MANUAL << 16)           /**< Shifted mode MANUAL for ECA_CAPTURECTRL     */
#define ECA_CAPTURECTRL_STARTMODE_START_TRIGGER        (_ECA_CAPTURECTRL_STARTMODE_START_TRIGGER << 16)    /**< Shifted mode START_TRIGGER for ECA_CAPTURECTRL*/
#define _ECA_CAPTURECTRL_STOPMODE_SHIFT                17                                                  /**< Shift value for ECA_STOPMODE                */
#define _ECA_CAPTURECTRL_STOPMODE_MASK                 0x60000UL                                           /**< Bit mask for ECA_STOPMODE                   */
#define _ECA_CAPTURECTRL_STOPMODE_DEFAULT              0x00000000UL                                        /**< Mode DEFAULT for ECA_CAPTURECTRL            */
#define _ECA_CAPTURECTRL_STOPMODE_CONTINUOUS           0x00000000UL                                        /**< Mode CONTINUOUS for ECA_CAPTURECTRL         */
#define _ECA_CAPTURECTRL_STOPMODE_BUF_FULL             0x00000001UL                                        /**< Mode BUF_FULL for ECA_CAPTURECTRL           */
#define _ECA_CAPTURECTRL_STOPMODE_STOP_TRIGGER         0x00000002UL                                        /**< Mode STOP_TRIGGER for ECA_CAPTURECTRL       */
#define _ECA_CAPTURECTRL_STOPMODE_STOP_TRIGGER_FULL    0x00000003UL                                        /**< Mode STOP_TRIGGER_FULL for ECA_CAPTURECTRL  */
#define ECA_CAPTURECTRL_STOPMODE_DEFAULT               (_ECA_CAPTURECTRL_STOPMODE_DEFAULT << 17)           /**< Shifted mode DEFAULT for ECA_CAPTURECTRL    */
#define ECA_CAPTURECTRL_STOPMODE_CONTINUOUS            (_ECA_CAPTURECTRL_STOPMODE_CONTINUOUS << 17)        /**< Shifted mode CONTINUOUS for ECA_CAPTURECTRL */
#define ECA_CAPTURECTRL_STOPMODE_BUF_FULL              (_ECA_CAPTURECTRL_STOPMODE_BUF_FULL << 17)          /**< Shifted mode BUF_FULL for ECA_CAPTURECTRL   */
#define ECA_CAPTURECTRL_STOPMODE_STOP_TRIGGER          (_ECA_CAPTURECTRL_STOPMODE_STOP_TRIGGER << 17)      /**< Shifted mode STOP_TRIGGER for ECA_CAPTURECTRL*/
#define ECA_CAPTURECTRL_STOPMODE_STOP_TRIGGER_FULL     (_ECA_CAPTURECTRL_STOPMODE_STOP_TRIGGER_FULL << 17) /**< Shifted mode STOP_TRIGGER_FULL for ECA_CAPTURECTRL*/
#define _ECA_CAPTURECTRL_COND_SHIFT                    20                                                  /**< Shift value for ECA_COND                    */
#define _ECA_CAPTURECTRL_COND_MASK                     0x300000UL                                          /**< Bit mask for ECA_COND                       */
#define _ECA_CAPTURECTRL_COND_DEFAULT                  0x00000000UL                                        /**< Mode DEFAULT for ECA_CAPTURECTRL            */
#define _ECA_CAPTURECTRL_COND_TIMED                    0x00000000UL                                        /**< Mode TIMED for ECA_CAPTURECTRL              */
#define _ECA_CAPTURECTRL_COND_START_TRIGGER            0x00000001UL                                        /**< Mode START_TRIGGER for ECA_CAPTURECTRL      */
#define _ECA_CAPTURECTRL_COND_SLAVE                    0x00000002UL                                        /**< Mode SLAVE for ECA_CAPTURECTRL              */
#define ECA_CAPTURECTRL_COND_DEFAULT                   (_ECA_CAPTURECTRL_COND_DEFAULT << 20)               /**< Shifted mode DEFAULT for ECA_CAPTURECTRL    */
#define ECA_CAPTURECTRL_COND_TIMED                     (_ECA_CAPTURECTRL_COND_TIMED << 20)                 /**< Shifted mode TIMED for ECA_CAPTURECTRL      */
#define ECA_CAPTURECTRL_COND_START_TRIGGER             (_ECA_CAPTURECTRL_COND_START_TRIGGER << 20)         /**< Shifted mode START_TRIGGER for ECA_CAPTURECTRL*/
#define ECA_CAPTURECTRL_COND_SLAVE                     (_ECA_CAPTURECTRL_COND_SLAVE << 20)                 /**< Shifted mode SLAVE for ECA_CAPTURECTRL      */
#define ECA_CAPTURECTRL_STOPCONDPRI                    (0x1UL << 22)                                       /**< Stop Condition Priority                     */
#define _ECA_CAPTURECTRL_STOPCONDPRI_SHIFT             22                                                  /**< Shift value for ECA_STOPCONDPRI             */
#define _ECA_CAPTURECTRL_STOPCONDPRI_MASK              0x400000UL                                          /**< Bit mask for ECA_STOPCONDPRI                */
#define _ECA_CAPTURECTRL_STOPCONDPRI_DEFAULT           0x00000000UL                                        /**< Mode DEFAULT for ECA_CAPTURECTRL            */
#define ECA_CAPTURECTRL_STOPCONDPRI_DEFAULT            (_ECA_CAPTURECTRL_STOPCONDPRI_DEFAULT << 22)        /**< Shifted mode DEFAULT for ECA_CAPTURECTRL    */
#define ECA_CAPTURECTRL_WRITEDIS                       (0x1UL << 23)                                       /**< Write Memory Disable                        */
#define _ECA_CAPTURECTRL_WRITEDIS_SHIFT                23                                                  /**< Shift value for ECA_WRITEDIS                */
#define _ECA_CAPTURECTRL_WRITEDIS_MASK                 0x800000UL                                          /**< Bit mask for ECA_WRITEDIS                   */
#define _ECA_CAPTURECTRL_WRITEDIS_DEFAULT              0x00000000UL                                        /**< Mode DEFAULT for ECA_CAPTURECTRL            */
#define ECA_CAPTURECTRL_WRITEDIS_DEFAULT               (_ECA_CAPTURECTRL_WRITEDIS_DEFAULT << 23)           /**< Shifted mode DEFAULT for ECA_CAPTURECTRL    */
#define ECA_CAPTURECTRL_DATAOUTEN                      (0x1UL << 24)                                       /**< Port Interface Enable                       */
#define _ECA_CAPTURECTRL_DATAOUTEN_SHIFT               24                                                  /**< Shift value for ECA_DATAOUTEN               */
#define _ECA_CAPTURECTRL_DATAOUTEN_MASK                0x1000000UL                                         /**< Bit mask for ECA_DATAOUTEN                  */
#define _ECA_CAPTURECTRL_DATAOUTEN_DEFAULT             0x00000000UL                                        /**< Mode DEFAULT for ECA_CAPTURECTRL            */
#define ECA_CAPTURECTRL_DATAOUTEN_DEFAULT              (_ECA_CAPTURECTRL_DATAOUTEN_DEFAULT << 24)          /**< Shifted mode DEFAULT for ECA_CAPTURECTRL    */
#define _ECA_CAPTURECTRL_DATAOUTDSHIFT_SHIFT           25                                                  /**< Shift value for ECA_DATAOUTDSHIFT           */
#define _ECA_CAPTURECTRL_DATAOUTDSHIFT_MASK            0x7E000000UL                                        /**< Bit mask for ECA_DATAOUTDSHIFT              */
#define _ECA_CAPTURECTRL_DATAOUTDSHIFT_DEFAULT         0x00000000UL                                        /**< Mode DEFAULT for ECA_CAPTURECTRL            */
#define ECA_CAPTURECTRL_DATAOUTDSHIFT_DEFAULT          (_ECA_CAPTURECTRL_DATAOUTDSHIFT_DEFAULT << 25)      /**< Shifted mode DEFAULT for ECA_CAPTURECTRL    */

/* Bit fields for ECA CAPTURESTARTDELAY */
#define _ECA_CAPTURESTARTDELAY_RESETVALUE              0x00000000UL                                /**< Default value for ECA_CAPTURESTARTDELAY     */
#define _ECA_CAPTURESTARTDELAY_MASK                    0xFFFFFFFFUL                                /**< Mask for ECA_CAPTURESTARTDELAY              */
#define _ECA_CAPTURESTARTDELAY_DELAY_SHIFT             0                                           /**< Shift value for ECA_DELAY                   */
#define _ECA_CAPTURESTARTDELAY_DELAY_MASK              0xFFFFFFFFUL                                /**< Bit mask for ECA_DELAY                      */
#define _ECA_CAPTURESTARTDELAY_DELAY_DEFAULT           0x00000000UL                                /**< Mode DEFAULT for ECA_CAPTURESTARTDELAY      */
#define ECA_CAPTURESTARTDELAY_DELAY_DEFAULT            (_ECA_CAPTURESTARTDELAY_DELAY_DEFAULT << 0) /**< Shifted mode DEFAULT for ECA_CAPTURESTARTDELAY*/

/* Bit fields for ECA CAPTURESTOPDELAY */
#define _ECA_CAPTURESTOPDELAY_RESETVALUE               0x00000000UL                               /**< Default value for ECA_CAPTURESTOPDELAY      */
#define _ECA_CAPTURESTOPDELAY_MASK                     0xFFFFFFFFUL                               /**< Mask for ECA_CAPTURESTOPDELAY               */
#define _ECA_CAPTURESTOPDELAY_DELAY_SHIFT              0                                          /**< Shift value for ECA_DELAY                   */
#define _ECA_CAPTURESTOPDELAY_DELAY_MASK               0xFFFFFFFFUL                               /**< Bit mask for ECA_DELAY                      */
#define _ECA_CAPTURESTOPDELAY_DELAY_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for ECA_CAPTURESTOPDELAY       */
#define ECA_CAPTURESTOPDELAY_DELAY_DEFAULT             (_ECA_CAPTURESTOPDELAY_DELAY_DEFAULT << 0) /**< Shifted mode DEFAULT for ECA_CAPTURESTOPDELAY*/

/* Bit fields for ECA CAPTURERATECTRL */
#define _ECA_CAPTURERATECTRL_RESETVALUE                0x00000000UL                             /**< Default value for ECA_CAPTURERATECTRL       */
#define _ECA_CAPTURERATECTRL_MASK                      0x0000FFFFUL                             /**< Mask for ECA_CAPTURERATECTRL                */
#define _ECA_CAPTURERATECTRL_RATE_SHIFT                0                                        /**< Shift value for ECA_RATE                    */
#define _ECA_CAPTURERATECTRL_RATE_MASK                 0xFFFFUL                                 /**< Bit mask for ECA_RATE                       */
#define _ECA_CAPTURERATECTRL_RATE_DEFAULT              0x00000000UL                             /**< Mode DEFAULT for ECA_CAPTURERATECTRL        */
#define ECA_CAPTURERATECTRL_RATE_DEFAULT               (_ECA_CAPTURERATECTRL_RATE_DEFAULT << 0) /**< Shifted mode DEFAULT for ECA_CAPTURERATECTRL*/

/* Bit fields for ECA PLAYBACKCTRL */
#define _ECA_PLAYBACKCTRL_RESETVALUE                   0x00000014UL                                /**< Default value for ECA_PLAYBACKCTRL          */
#define _ECA_PLAYBACKCTRL_MASK                         0x0000001FUL                                /**< Mask for ECA_PLAYBACKCTRL                   */
#define ECA_PLAYBACKCTRL_MODE                          (0x1UL << 0)                                /**< Playback Mode                               */
#define _ECA_PLAYBACKCTRL_MODE_SHIFT                   0                                           /**< Shift value for ECA_MODE                    */
#define _ECA_PLAYBACKCTRL_MODE_MASK                    0x1UL                                       /**< Bit mask for ECA_MODE                       */
#define _ECA_PLAYBACKCTRL_MODE_DEFAULT                 0x00000000UL                                /**< Mode DEFAULT for ECA_PLAYBACKCTRL           */
#define _ECA_PLAYBACKCTRL_MODE_SINGLE                  0x00000000UL                                /**< Mode SINGLE for ECA_PLAYBACKCTRL            */
#define _ECA_PLAYBACKCTRL_MODE_LOOP                    0x00000001UL                                /**< Mode LOOP for ECA_PLAYBACKCTRL              */
#define ECA_PLAYBACKCTRL_MODE_DEFAULT                  (_ECA_PLAYBACKCTRL_MODE_DEFAULT << 0)       /**< Shifted mode DEFAULT for ECA_PLAYBACKCTRL   */
#define ECA_PLAYBACKCTRL_MODE_SINGLE                   (_ECA_PLAYBACKCTRL_MODE_SINGLE << 0)        /**< Shifted mode SINGLE for ECA_PLAYBACKCTRL    */
#define ECA_PLAYBACKCTRL_MODE_LOOP                     (_ECA_PLAYBACKCTRL_MODE_LOOP << 0)          /**< Shifted mode LOOP for ECA_PLAYBACKCTRL      */
#define ECA_PLAYBACKCTRL_COND                          (0x1UL << 1)                                /**< Playback Condition                          */
#define _ECA_PLAYBACKCTRL_COND_SHIFT                   1                                           /**< Shift value for ECA_COND                    */
#define _ECA_PLAYBACKCTRL_COND_MASK                    0x2UL                                       /**< Bit mask for ECA_COND                       */
#define _ECA_PLAYBACKCTRL_COND_DEFAULT                 0x00000000UL                                /**< Mode DEFAULT for ECA_PLAYBACKCTRL           */
#define _ECA_PLAYBACKCTRL_COND_START_TRIGGER           0x00000000UL                                /**< Mode START_TRIGGER for ECA_PLAYBACKCTRL     */
#define _ECA_PLAYBACKCTRL_COND_TIMED                   0x00000001UL                                /**< Mode TIMED for ECA_PLAYBACKCTRL             */
#define ECA_PLAYBACKCTRL_COND_DEFAULT                  (_ECA_PLAYBACKCTRL_COND_DEFAULT << 1)       /**< Shifted mode DEFAULT for ECA_PLAYBACKCTRL   */
#define ECA_PLAYBACKCTRL_COND_START_TRIGGER            (_ECA_PLAYBACKCTRL_COND_START_TRIGGER << 1) /**< Shifted mode START_TRIGGER for ECA_PLAYBACKCTRL*/
#define ECA_PLAYBACKCTRL_COND_TIMED                    (_ECA_PLAYBACKCTRL_COND_TIMED << 1)         /**< Shifted mode TIMED for ECA_PLAYBACKCTRL     */
#define _ECA_PLAYBACKCTRL_DATAWIDTH_SHIFT              2                                           /**< Shift value for ECA_DATAWIDTH               */
#define _ECA_PLAYBACKCTRL_DATAWIDTH_MASK               0x1CUL                                      /**< Bit mask for ECA_DATAWIDTH                  */
#define _ECA_PLAYBACKCTRL_DATAWIDTH_DEFAULT            0x00000005UL                                /**< Mode DEFAULT for ECA_PLAYBACKCTRL           */
#define _ECA_PLAYBACKCTRL_DATAWIDTH_BIT1               0x00000000UL                                /**< Mode BIT1 for ECA_PLAYBACKCTRL              */
#define _ECA_PLAYBACKCTRL_DATAWIDTH_BIT2               0x00000001UL                                /**< Mode BIT2 for ECA_PLAYBACKCTRL              */
#define _ECA_PLAYBACKCTRL_DATAWIDTH_BIT4               0x00000002UL                                /**< Mode BIT4 for ECA_PLAYBACKCTRL              */
#define _ECA_PLAYBACKCTRL_DATAWIDTH_BIT8               0x00000003UL                                /**< Mode BIT8 for ECA_PLAYBACKCTRL              */
#define _ECA_PLAYBACKCTRL_DATAWIDTH_BIT16              0x00000004UL                                /**< Mode BIT16 for ECA_PLAYBACKCTRL             */
#define _ECA_PLAYBACKCTRL_DATAWIDTH_BIT32              0x00000005UL                                /**< Mode BIT32 for ECA_PLAYBACKCTRL             */
#define ECA_PLAYBACKCTRL_DATAWIDTH_DEFAULT             (_ECA_PLAYBACKCTRL_DATAWIDTH_DEFAULT << 2)  /**< Shifted mode DEFAULT for ECA_PLAYBACKCTRL   */
#define ECA_PLAYBACKCTRL_DATAWIDTH_BIT1                (_ECA_PLAYBACKCTRL_DATAWIDTH_BIT1 << 2)     /**< Shifted mode BIT1 for ECA_PLAYBACKCTRL      */
#define ECA_PLAYBACKCTRL_DATAWIDTH_BIT2                (_ECA_PLAYBACKCTRL_DATAWIDTH_BIT2 << 2)     /**< Shifted mode BIT2 for ECA_PLAYBACKCTRL      */
#define ECA_PLAYBACKCTRL_DATAWIDTH_BIT4                (_ECA_PLAYBACKCTRL_DATAWIDTH_BIT4 << 2)     /**< Shifted mode BIT4 for ECA_PLAYBACKCTRL      */
#define ECA_PLAYBACKCTRL_DATAWIDTH_BIT8                (_ECA_PLAYBACKCTRL_DATAWIDTH_BIT8 << 2)     /**< Shifted mode BIT8 for ECA_PLAYBACKCTRL      */
#define ECA_PLAYBACKCTRL_DATAWIDTH_BIT16               (_ECA_PLAYBACKCTRL_DATAWIDTH_BIT16 << 2)    /**< Shifted mode BIT16 for ECA_PLAYBACKCTRL     */
#define ECA_PLAYBACKCTRL_DATAWIDTH_BIT32               (_ECA_PLAYBACKCTRL_DATAWIDTH_BIT32 << 2)    /**< Shifted mode BIT32 for ECA_PLAYBACKCTRL     */

/* Bit fields for ECA PLAYBACKRATECTRL */
#define _ECA_PLAYBACKRATECTRL_RESETVALUE               0x00000000UL                              /**< Default value for ECA_PLAYBACKRATECTRL      */
#define _ECA_PLAYBACKRATECTRL_MASK                     0x0000FFFFUL                              /**< Mask for ECA_PLAYBACKRATECTRL               */
#define _ECA_PLAYBACKRATECTRL_RATE_SHIFT               0                                         /**< Shift value for ECA_RATE                    */
#define _ECA_PLAYBACKRATECTRL_RATE_MASK                0xFFFFUL                                  /**< Bit mask for ECA_RATE                       */
#define _ECA_PLAYBACKRATECTRL_RATE_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for ECA_PLAYBACKRATECTRL       */
#define ECA_PLAYBACKRATECTRL_RATE_DEFAULT              (_ECA_PLAYBACKRATECTRL_RATE_DEFAULT << 0) /**< Shifted mode DEFAULT for ECA_PLAYBACKRATECTRL*/

/* Bit fields for ECA EVENTCNTRCTRL */
#define _ECA_EVENTCNTRCTRL_RESETVALUE                  0x00000000UL                                      /**< Default value for ECA_EVENTCNTRCTRL         */
#define _ECA_EVENTCNTRCTRL_MASK                        0x0000001FUL                                      /**< Mask for ECA_EVENTCNTRCTRL                  */
#define ECA_EVENTCNTRCTRL_STARTMODE                    (0x1UL << 0)                                      /**< Start Mode                                  */
#define _ECA_EVENTCNTRCTRL_STARTMODE_SHIFT             0                                                 /**< Shift value for ECA_STARTMODE               */
#define _ECA_EVENTCNTRCTRL_STARTMODE_MASK              0x1UL                                             /**< Bit mask for ECA_STARTMODE                  */
#define _ECA_EVENTCNTRCTRL_STARTMODE_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for ECA_EVENTCNTRCTRL          */
#define _ECA_EVENTCNTRCTRL_STARTMODE_MANUAL            0x00000000UL                                      /**< Mode MANUAL for ECA_EVENTCNTRCTRL           */
#define _ECA_EVENTCNTRCTRL_STARTMODE_START_TRIGGER     0x00000001UL                                      /**< Mode START_TRIGGER for ECA_EVENTCNTRCTRL    */
#define ECA_EVENTCNTRCTRL_STARTMODE_DEFAULT            (_ECA_EVENTCNTRCTRL_STARTMODE_DEFAULT << 0)       /**< Shifted mode DEFAULT for ECA_EVENTCNTRCTRL  */
#define ECA_EVENTCNTRCTRL_STARTMODE_MANUAL             (_ECA_EVENTCNTRCTRL_STARTMODE_MANUAL << 0)        /**< Shifted mode MANUAL for ECA_EVENTCNTRCTRL   */
#define ECA_EVENTCNTRCTRL_STARTMODE_START_TRIGGER      (_ECA_EVENTCNTRCTRL_STARTMODE_START_TRIGGER << 0) /**< Shifted mode START_TRIGGER for ECA_EVENTCNTRCTRL*/
#define _ECA_EVENTCNTRCTRL_STOPMODE_SHIFT              1                                                 /**< Shift value for ECA_STOPMODE                */
#define _ECA_EVENTCNTRCTRL_STOPMODE_MASK               0x6UL                                             /**< Bit mask for ECA_STOPMODE                   */
#define _ECA_EVENTCNTRCTRL_STOPMODE_DEFAULT            0x00000000UL                                      /**< Mode DEFAULT for ECA_EVENTCNTRCTRL          */
#define _ECA_EVENTCNTRCTRL_STOPMODE_MANUAL             0x00000000UL                                      /**< Mode MANUAL for ECA_EVENTCNTRCTRL           */
#define _ECA_EVENTCNTRCTRL_STOPMODE_STOP_TRIGGER       0x00000001UL                                      /**< Mode STOP_TRIGGER for ECA_EVENTCNTRCTRL     */
#define _ECA_EVENTCNTRCTRL_STOPMODE_COMPARE            0x00000002UL                                      /**< Mode COMPARE for ECA_EVENTCNTRCTRL          */
#define ECA_EVENTCNTRCTRL_STOPMODE_DEFAULT             (_ECA_EVENTCNTRCTRL_STOPMODE_DEFAULT << 1)        /**< Shifted mode DEFAULT for ECA_EVENTCNTRCTRL  */
#define ECA_EVENTCNTRCTRL_STOPMODE_MANUAL              (_ECA_EVENTCNTRCTRL_STOPMODE_MANUAL << 1)         /**< Shifted mode MANUAL for ECA_EVENTCNTRCTRL   */
#define ECA_EVENTCNTRCTRL_STOPMODE_STOP_TRIGGER        (_ECA_EVENTCNTRCTRL_STOPMODE_STOP_TRIGGER << 1)   /**< Shifted mode STOP_TRIGGER for ECA_EVENTCNTRCTRL*/
#define ECA_EVENTCNTRCTRL_STOPMODE_COMPARE             (_ECA_EVENTCNTRCTRL_STOPMODE_COMPARE << 1)        /**< Shifted mode COMPARE for ECA_EVENTCNTRCTRL  */
#define _ECA_EVENTCNTRCTRL_COUNTMODE_SHIFT             3                                                 /**< Shift value for ECA_COUNTMODE               */
#define _ECA_EVENTCNTRCTRL_COUNTMODE_MASK              0x18UL                                            /**< Bit mask for ECA_COUNTMODE                  */
#define _ECA_EVENTCNTRCTRL_COUNTMODE_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for ECA_EVENTCNTRCTRL          */
#define _ECA_EVENTCNTRCTRL_COUNTMODE_ALWAYS            0x00000000UL                                      /**< Mode ALWAYS for ECA_EVENTCNTRCTRL           */
#define _ECA_EVENTCNTRCTRL_COUNTMODE_START_TRIGGER     0x00000001UL                                      /**< Mode START_TRIGGER for ECA_EVENTCNTRCTRL    */
#define _ECA_EVENTCNTRCTRL_COUNTMODE_STOP_TRIGGER      0x00000002UL                                      /**< Mode STOP_TRIGGER for ECA_EVENTCNTRCTRL     */
#define _ECA_EVENTCNTRCTRL_COUNTMODE_ALL_TRIGGER       0x00000003UL                                      /**< Mode ALL_TRIGGER for ECA_EVENTCNTRCTRL      */
#define ECA_EVENTCNTRCTRL_COUNTMODE_DEFAULT            (_ECA_EVENTCNTRCTRL_COUNTMODE_DEFAULT << 3)       /**< Shifted mode DEFAULT for ECA_EVENTCNTRCTRL  */
#define ECA_EVENTCNTRCTRL_COUNTMODE_ALWAYS             (_ECA_EVENTCNTRCTRL_COUNTMODE_ALWAYS << 3)        /**< Shifted mode ALWAYS for ECA_EVENTCNTRCTRL   */
#define ECA_EVENTCNTRCTRL_COUNTMODE_START_TRIGGER      (_ECA_EVENTCNTRCTRL_COUNTMODE_START_TRIGGER << 3) /**< Shifted mode START_TRIGGER for ECA_EVENTCNTRCTRL*/
#define ECA_EVENTCNTRCTRL_COUNTMODE_STOP_TRIGGER       (_ECA_EVENTCNTRCTRL_COUNTMODE_STOP_TRIGGER << 3)  /**< Shifted mode STOP_TRIGGER for ECA_EVENTCNTRCTRL*/
#define ECA_EVENTCNTRCTRL_COUNTMODE_ALL_TRIGGER        (_ECA_EVENTCNTRCTRL_COUNTMODE_ALL_TRIGGER << 3)   /**< Shifted mode ALL_TRIGGER for ECA_EVENTCNTRCTRL*/

/* Bit fields for ECA EVENTCNTRCOMPARE */
#define _ECA_EVENTCNTRCOMPARE_RESETVALUE               0x00000000UL                                 /**< Default value for ECA_EVENTCNTRCOMPARE      */
#define _ECA_EVENTCNTRCOMPARE_MASK                     0xFFFFFFFFUL                                 /**< Mask for ECA_EVENTCNTRCOMPARE               */
#define _ECA_EVENTCNTRCOMPARE_COMPARE_SHIFT            0                                            /**< Shift value for ECA_COMPARE                 */
#define _ECA_EVENTCNTRCOMPARE_COMPARE_MASK             0xFFFFFFFFUL                                 /**< Bit mask for ECA_COMPARE                    */
#define _ECA_EVENTCNTRCOMPARE_COMPARE_DEFAULT          0x00000000UL                                 /**< Mode DEFAULT for ECA_EVENTCNTRCOMPARE       */
#define ECA_EVENTCNTRCOMPARE_COMPARE_DEFAULT           (_ECA_EVENTCNTRCOMPARE_COMPARE_DEFAULT << 0) /**< Shifted mode DEFAULT for ECA_EVENTCNTRCOMPARE*/

/* Bit fields for ECA EVENTCNTRSTATUS */
#define _ECA_EVENTCNTRSTATUS_RESETVALUE                0x00000000UL                               /**< Default value for ECA_EVENTCNTRSTATUS       */
#define _ECA_EVENTCNTRSTATUS_MASK                      0xFFFFFFFFUL                               /**< Mask for ECA_EVENTCNTRSTATUS                */
#define _ECA_EVENTCNTRSTATUS_STATUS_SHIFT              0                                          /**< Shift value for ECA_STATUS                  */
#define _ECA_EVENTCNTRSTATUS_STATUS_MASK               0xFFFFFFFFUL                               /**< Bit mask for ECA_STATUS                     */
#define _ECA_EVENTCNTRSTATUS_STATUS_DEFAULT            0x00000000UL                               /**< Mode DEFAULT for ECA_EVENTCNTRSTATUS        */
#define ECA_EVENTCNTRSTATUS_STATUS_DEFAULT             (_ECA_EVENTCNTRSTATUS_STATUS_DEFAULT << 0) /**< Shifted mode DEFAULT for ECA_EVENTCNTRSTATUS*/

/** @} End of group MGM24_ECA_BitFields */
/** @} End of group MGM24_ECA */
/** @} End of group Parts */

#endif /* MGM24_ECA_H */
