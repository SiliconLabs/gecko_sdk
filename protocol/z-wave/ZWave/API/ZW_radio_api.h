/**
 * @file
 * Header file containing Z-Wave Radio related enumerations and functions.
 * @copyright 2019 Silicon Laboratories Inc.
 */
#ifndef ZW_RADIO_API_H_
#define ZW_RADIO_API_H_

#include <stdint.h>

typedef enum
{
  NORMAL_POWER = 0,
  MINUS_1_DB,
  MINUS_2_DB,
  MINUS_3_DB,
  MINUS_4_DB,
  MINUS_5_DB,
  MINUS_6_DB,
  MINUS_7_DB,
  MINUS_8_DB,
  MINUS_9_DB,
  MINIMUM_POWER = MINUS_9_DB
} ZW_PowerLevel_t;


typedef enum
{
  REGION_EU = 0,        /**< Radio is located in Region EU. 2 Channel region. **/
  REGION_US,            /**< Radio is located in Region US. 2 Channel region. **/
  REGION_ANZ,           /**< Radio is located in Region Australia/New Zealand. 2 Channel region. **/
  REGION_HK,            /**< Radio is located in Region Hong Kong. 2 Channel region. **/
  REGION_IN = 5,        /**< Radio is located in Region India. 2 Channel region. **/
  REGION_IL,            /**< Radio is located in Region Israel. 2 Channel region. **/
  REGION_RU,            /**< Radio is located in Region Russia. 2 Channel region. **/
  REGION_CN,            /**< Radio is located in Region China. 2 Channel region. **/
  REGION_US_LR,         /**< Radio is located in Region US. 2 Channel LR region. **/
  REGION_US_LR_BACKUP,  /**< Radio is located in Region US. 2 Channel LR Backup region. **/
  REGION_2CH_NUM = (REGION_US_LR_BACKUP - REGION_EU) + 1, /**< Number of 2 channel region values. For checking if value is out of range. **/
  REGION_JP = 32,       /**< Radio is located in Region Japan. 3 Channel region. **/
  REGION_KR,            /**< Radio is located in Region Korea. 3 Channel region. **/
  REGION_3CH_NUM = (REGION_KR - REGION_JP) + 1, /**< Number of 3 channel region values. For checking if value is out of range. **/
  REGION_US_LR_END_DEVICE = 48, /**< Radio is located in Region US Long Range End Device. 2 Long Range Channel Region. **/
  REGION_LR_END_DEVICE_NUM = 1,
  REGION_UNDEFINED = 0xFE,
  REGION_DEFAULT = 0xFF	/**< Radio is located in Library Default Region EU. 2 Channel region. **/
} ZW_Region_t;


typedef enum
{
  TF_REGION_866 = 64,
  TF_REGION_870,  // 65 //10
  TF_REGION_906,  // 66 //11
  TF_REGION_910,
  TF_REGION_878,
  TF_REGION_882,
  TF_REGION_886,  // 70 //15
  TF_REGION_2CH_NUM = (TF_REGION_886 - TF_REGION_866) + 1,
  TF_REGION_932_3CH = 96,
  TF_REGION_940_3CH,
  TF_REGION_835_3CH,
  TF_REGION_840_3CH,
  TF_REGION_850_3CH,  // 100
  TF_REGION_3CH_NUM = (TF_REGION_850_3CH - TF_REGION_932_3CH) + 1
} ZW_Region_TF_t;


/**@brief Wakeup interval for the radio. A FLiRS node will use 250 or 1000 ms interval, all other
 *        nodes should be configured as always listening.
 */
typedef enum
{
  NEVER_LISTEN = 0x00,  /**< Node is not listening (Only listen when application requests it) **/
  ALWAYS_LISTEN = 0x01, /**< Node is always listening **/
  WAKEUP_250ms = 0x02,  /**< Node wakes up every 250 ms interval to listen for a wakeup beam **/
  WAKEUP_1000ms = 0x03, /**< Node wakes up every 1000 ms interval to listen for a wakeup beam **/
} ZW_Wakeup_t;


/* Protocol Network statistics structure  */
typedef struct SNetworkStatistics
{
  uint32_t TxFrames;          /* Transmitted Frames */
  uint32_t TxLBTBackOffs;     /* LBT backoffs */
  uint32_t RxFrames;          /* Received Frames (No errors) */
  uint32_t RxLRCErrors;       /* Checksum Errors */
  uint32_t RxCRCErrors;       /* CRC16 Errors */
  uint32_t RxForeignHomeID;   /* Foreign Home ID */
  uint32_t TxTimeChannel0;    /* Accumulated transmission time in ms for channel 0 */
  uint32_t TxTimeChannel1;    /* Accumulated transmission time in ms for channel 1 */
  uint32_t TxTimeChannel2;    /* Accumulated transmission time in ms for channel 2 */
  uint32_t TxTimeChannel3;	  /* Accumulated transmission time in ms for channel 3, i.e., US_LR1 */
  uint32_t TxTimeChannel4;	  /* Accumulated transmission time in ms for channel 4, i.e., US_LR2 */
} SNetworkStatistics;


#endif /* ZW_RADIO_API_H_ */
