/**
 * @file
 * @copyright 2022 Silicon Laboratories Inc.
 */

#ifndef _ZW_REGION_CONFIG_H_
#define _ZW_REGION_CONFIG_H_

/**
 * \defgroup configuration Configuration
 * Configuration
 *
 * \addtogroup configuration
 * @{
 */
/**
 * \defgroup zwave_radio_configuration Z-Wave Radio Configuration
 * Z-Wave Radio Configuration
 *
 * \addtogroup zwave_radio_configuration
 * @{
 */

/**
 * The supported region of the device. Used only if region value is not previously written in MFG_ZWAVE_COUNTRY_FREQ token. To delete value from MFG token, run: commander flash --tokengroup znet --token MFG_ZWAVE_COUNTRY_FREQ:0xFF
 *
 * The supported region of the device. Used only if region value is not previously written in MFG_ZWAVE_COUNTRY_FREQ token. To delete value from MFG token, run: commander flash --tokengroup znet --token MFG_ZWAVE_COUNTRY_FREQ:0xFF
 *
 *  Option  | Value
 * -------- | -------
 * Default (Europe)  | REGION_DEFAULT
 * Australia / New Zealand  | REGION_ANZ
 * China  | REGION_CN
 * Europe  | REGION_EU
 * Hong Kong  | REGION_HK
 * Israel  | REGION_IL
 * India  | REGION_IN
 * Japan  | REGION_JP
 * Korea  | REGION_KR
 * Russia  | REGION_RU
 * United States  | REGION_US
 * United States Long Range  | REGION_US_LR
 *
 */
#if !defined(ZW_REGION)
#define ZW_REGION  REGION_DEFAULT
#endif /* !defined(ZW_REGION) */

/**@}*/ /* \addtogroup zwave_radio_configuration */

/**@}*/ /* \addtogroup configuration */
#endif /* _ZW_REGION_CONFIG_H_ */
