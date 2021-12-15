/***************************************************************************
* @file
* @brief Provides the application interface structure which is needed by the bootloader code.
* @copyright 2019 Silicon Laboratories Inc.
*/

#ifdef EFR32ZG
#include <ZW_security_api.h>
#include <config_app.h>
#include <application_properties.h>

#ifndef ZAF_BUILD_NO
#define ZAF_BUILD_NO 0
#endif

#ifndef GENERIC_TYPE
#define GENERIC_TYPE 0  //Some of the application do not defines this so this defines here --for example serialapp
#endif

#ifndef APP_ICON_TYPE
#define APP_ICON_TYPE 0   //Some of the application do not defines this so this defines here --for example serialapp
#endif

#ifndef SPECIFIC_TYPE
#define SPECIFIC_TYPE 0  //Some of the application do not defines this so this defines here --for example serialapp
#endif

#ifndef REQUESTED_SECURITY_KEYS
#define REQUESTED_SECURITY_KEYS 0  //Some of the application do not defines this so this defines here --for example serialapp
#endif

/**
 * This structure is used by the bootloader to determine the version of the running application.
 * This structure may not be directly refrenced anywhere, but it is needed for bootloader api
 * to work properly. See btl_interface.h.
 *
 * WARNING!! Changing any of the elements in productID will make OTA firmware updates NOT work.
 * The 16 byte productId array of an application must exactly match the productId array of a new image or the bootloader will reject it.
 *
 * Attention: Variable is declared as volatile even though it is not expected to change.
 * However, without it, FW update to version 255 wouldn't update app.version value;
 * instead, this value would stay the same, when OTA was actually successful.
 */
const volatile ApplicationProperties_t app_properties = {
		.magic = APPLICATION_PROPERTIES_MAGIC,
		.structVersion = APPLICATION_PROPERTIES_VERSION,
		.signatureType = APPLICATION_SIGNATURE_CRC32,
		.signatureLocation=0,
		.app = {
				.type = APPLICATION_TYPE_ZWAVE,
				.version = APP_VERSION<<16 | APP_REVISION<<8 | APP_PATCH,
				.capabilities = 0UL,
				.productId={
						(APP_MANUFACTURER_ID>>8) & 0xFF,(APP_MANUFACTURER_ID>>0) & 0xFF,
						(APP_PRODUCT_ID>>8) & 0xFF, (APP_PRODUCT_ID>>0) & 0xFF,
						0x00, 0x00,
						0x00, 0x00,
						(APP_PRODUCT_TYPE_ID>>8) & 0xFF, (APP_PRODUCT_TYPE_ID>>0) & 0xFF,
						(APP_ICON_TYPE>>8) & 0xFF, (APP_ICON_TYPE>>0) & 0xFF,
						(GENERIC_TYPE>>0) & 0xFF, (GENERIC_TYPE>>0) & 0xFF,   //as generic type is 8 bit value
						((SPECIFIC_TYPE) & 0xFF),                                   //as specific type is 8 bit value
						(REQUESTED_SECURITY_KEYS >> 0) & 0xFF
						
				}
		}
};
#endif
