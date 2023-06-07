/**
 * @file
 * Command Class Supervision Configuration API
 * @copyright 2022 Silicon Laboratories Inc.
 */

#ifndef _CC_ZWAVE_PLUS_INFO_CONFIG_API_H_
#define _CC_ZWAVE_PLUS_INFO_CONFIG_API_H_

#include <ZW_classcmd.h>
#include <ZAF_types.h>

/**
 * @addtogroup CC
 * @{
 * @addtogroup ZWavePlusInfo
 * @{
 */

typedef struct
{
  uint16_t installer_icon_type;
  uint16_t user_icon_type;
  uint8_t endpoint;
}
zw_plus_info_config_icons_t;

/**
 * @brief Returns the Installer and User Icon Type configuration of the root device.
 * 
 * @return Pointer to struct contains the icon types.
 */
zw_plus_info_config_icons_t * cc_zwave_plus_info_config_get_root_icons(void);

/**
 * @brief Returns the number of endpoints defined in the application command class
 * configuration. In case of no zw_cc_zwaveplusinfo is given in the config, returns
 * with 0.
 * 
 * @return the number of endpoints.
 */
uint8_t cc_zwave_plus_info_config_get_endpoint_count(void);

/**
 * @brief Returns the Installer and User Icon Type configuration of the given 'endpoint'.
 * 
 * @param endpoint the index of the requested endpoint. First endpoint index starting by 1.
 * @return Pointer to struct contains the icon types for the given endpoint.
 */
zw_plus_info_config_icons_t * cc_zwave_plus_info_config_get_endpoint_entry(uint8_t endpoint);

/**
 * @}
 * @}
 */ 

#endif /* _CC_ZWAVE_PLUS_INFO_CONFIG_API_H_ */
