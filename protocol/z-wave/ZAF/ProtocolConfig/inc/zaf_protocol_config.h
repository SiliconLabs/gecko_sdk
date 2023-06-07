/**
 * @file
 * @copyright 2023 Silicon Laboratories Inc.
 */
#ifndef ZAF_PROTOCOL_CONFIG_H
#define ZAF_PROTOCOL_CONFIG_H

#include "ZW_application_transport_interface.h"
#include "zpal_radio.h"

/**
 * @addtogroup ZAF
 * @{
 * @addtogroup ZAF_ProtocolConfig
 * @{
 */

/**
 * @brief Gets the application node info
 *
 * @return SAppNodeInfo_t* Pointer to the application node info
 */
SAppNodeInfo_t *zaf_get_app_node_info(void);

/**
 * @brief Gets the radio configuration
 *
 * @return SRadioConfig_t* Pointer to the radio configuration
 */
SRadioConfig_t* zaf_get_radio_config(void);

/**
 * @brief Gets the protocol configuration
 *
 * @return const SProtocolConfig_t* Pointer to the protocol configuration
 */
const SProtocolConfig_t *zaf_get_protocol_config(void);

/**
 * @} // ZAF_ProtocolConfig
 * @} // ZAF
 */

#endif /* ZAF_PROTOCOL_CONFIG_H */
