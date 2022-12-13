/**
 * @file
 * @copyright 2022 Silicon Laboratories Inc.
 */
#ifndef _ZAF_CONFIG_API_H_
#define _ZAF_CONFIG_API_H_

#include <stdbool.h>
#include <stdint.h>
#include <ZW_classcmd.h>



/**
 * @brief Indicates if the bootloader is upgradable
 * 
 * @return uint8_t 1 if the bootloader is upgradable else 0
 */
uint8_t zaf_config_get_bootloader_upgradable(void);

/**
 * @brief Returns the target id of the bootloader
 * 
 * This function is only relevant if \ref zaf_config_get_bootloader_upgradable 
 * is true. The returned target id can be invalid if the bootloader is 
 * not upgradable
 * 
 * @return uint8_t the bootloader target id
 */
uint8_t zaf_config_get_bootloader_target_id(void);

/**
 * @brief Return the build number
 *   
 * @return uint16_t the build number
 */
uint16_t zaf_config_get_build_no(void);

/**
 * Returns the configured hardware version.
 * @return hardware version
 */
uint8_t zaf_config_get_hardware_version(void);

/**
 * Returns the configured hardware version.
 * @return hardware version
 */
uint8_t zaf_config_get_firmware_target_count(void);

/**
 * Returns the manufacturer ID defined in zaf_config.h
 *
 * The format of this value is specified by the Manufacturer Specific command class.
 *
 * @return Manufacturer ID
 */
uint16_t zaf_config_get_manufacturer_id(void);

/**
 * Returns the product type ID defined in zaf_config.h.
 *
 * The format of this value is specified by the Manufacturer Specific command class.
 *
 * @return Product type ID
 */
uint16_t zaf_config_get_product_type_id(void);

/**
 * Returns the product ID defined in zaf_config.h.
 *
 * The format of this value is specified by the Manufacturer Specific command class.
 *
 * @return Product ID
 */
uint16_t zaf_config_get_product_id(void);

/**
 * Returns the number of endpoints set in zaf_config.h.
 *
 * @return Number of endpoints
 */
uint8_t zaf_config_get_number_of_endpoints(void);

/**
 * Return default endpoint.
 * @note Usage: in cases when command was sent to root, and endpoints are supported.
 * Then root device should mirror endpoint 1.
 * If there is no endpoints, endpoint 0 is used.
 *
 * @return 0 if no endpoints, or 1 if endpoints are supported
 */
uint8_t zaf_config_get_default_endpoint(void);

/**
 * Returns the role type of the application.
 * @return Role type.
 */
uint8_t zaf_config_get_role_type(void);

/**
 * Retuns the requested security keys
 * 
 * @return uint8_t Requested security keys
 */
uint8_t zaf_config_get_requested_security_keys(void);

/**
 * Returns if the application is secure only
 * 
 * @return uint8_t 1 for secure only else 0
 */
uint8_t zaf_config_get_secure_only(void);

#endif /* _ZAF_CONFIG_API_H_ */
