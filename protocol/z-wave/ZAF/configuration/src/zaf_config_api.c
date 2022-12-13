/**
 * @file
 * Configuration file for the ZAF 
 *
 * @copyright 2022 Silicon Laboratories Inc.
 */

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/
#include <zaf_config.h>
#include <zaf_config_security.h>
#include <zaf_config_api.h>
#include <zw_build_no.h>
/****************************************************************************/
/*                      PRIVATE TYPES and DEFINITIONS                       */
/****************************************************************************/

/****************************************************************************/
/*                              PRIVATE DATA                                */
/****************************************************************************/

/****************************************************************************/
/*                              EXPORTED DATA                               */
/****************************************************************************/

/****************************************************************************/
/*                            PRIVATE FUNCTIONS                             */
/****************************************************************************/

/****************************************************************************/
/*                             PUBLIC FUNCTIONS                             */
/****************************************************************************/

uint8_t zaf_config_get_bootloader_upgradable(void)
{
    return ZAF_CONFIG_BOOTLOADER_UPGRADABLE;
}

uint8_t zaf_config_get_bootloader_target_id(void)
{
    return ZAF_CONFIG_BOOTLOADER_TARGET_ID;
}

uint16_t zaf_config_get_build_no(void)
{
    return (uint16_t)ZAF_BUILD_NO;
}

uint8_t zaf_config_get_hardware_version(void)
{
  return ZAF_CONFIG_HARDWARE_VERSION;
}

uint8_t zaf_config_get_firmware_target_count(void)
{
  return ZAF_CONFIG_FIRMWARE_TARGET_COUNT;
}

uint16_t zaf_config_get_manufacturer_id(void)
{
  return ZAF_CONFIG_MANUFACTURER_ID;
}

uint16_t zaf_config_get_product_type_id(void)
{
  return ZAF_CONFIG_PRODUCT_TYPE_ID;
}

uint16_t zaf_config_get_product_id(void)
{
  return ZAF_CONFIG_PRODUCT_ID;
}

uint8_t zaf_config_get_number_of_endpoints(void)
{
  return ZAF_CONFIG_NUMBER_OF_END_POINTS;
}

uint8_t zaf_config_get_default_endpoint(void) {
  return ZAF_CONFIG_NUMBER_OF_END_POINTS ? 1 : 0;
}

uint8_t zaf_config_get_role_type(void) {
  return ZAF_CONFIG_APP_ROLE_TYPE;
}

uint8_t zaf_config_get_requested_security_keys(void)
{
  return ZAF_CONFIG_REQUESTED_SECURITY_KEYS;
}

uint8_t zaf_config_get_secure_only(void)
{
  return ZAF_CONFIG_SECURE_ONLY;
}
