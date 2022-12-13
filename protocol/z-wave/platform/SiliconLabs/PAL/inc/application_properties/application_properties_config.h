/**
 * @file
 * @copyright 2021 Silicon Laboratories Inc.
 */
#ifndef APPLICATION_PROPERTIES_CONFIG_H_
#define APPLICATION_PROPERTIES_CONFIG_H_

#include "application_properties.h"
#include "config_app.h"
#include "zaf_config.h"
#include "zaf_config_security.h"

#define SL_APPLICATION_SIGNATURE               APPLICATION_SIGNATURE_NONE
#define SL_APPLICATION_SIGNATURE_LOCATION      0x0
#define SL_APPLICATION_TYPE          APPLICATION_TYPE_ZWAVE
#define SL_APPLICATION_VERSION       (APP_VERSION<<16 | APP_REVISION<<8 | APP_PATCH)
#define SL_APPLICATION_CAPABILITIES   0UL
#define SL_APPLICATION_PRODUCT_ID {(ZAF_CONFIG_MANUFACTURER_ID>>8) & 0xFF,(ZAF_CONFIG_MANUFACTURER_ID>>0) & 0xFF, \
						           (ZAF_CONFIG_PRODUCT_ID>>8) & 0xFF, (ZAF_CONFIG_PRODUCT_ID>>0) & 0xFF,          \
						           0x00, 0x00,                                                      \
						           0x00, 0x00,                                                      \
						           (ZAF_CONFIG_PRODUCT_TYPE_ID>>8) & 0xFF, (ZAF_CONFIG_PRODUCT_TYPE_ID>>0) & 0xFF,\
						           (ZAF_CONFIG_INSTALLER_ICON_TYPE>>8) & 0xFF, (ZAF_CONFIG_INSTALLER_ICON_TYPE>>0) & 0xFF,            \
						           (ZAF_CONFIG_GENERIC_TYPE>>0) & 0xFF, (ZAF_CONFIG_GENERIC_TYPE>>0) & 0xFF,              \
						           ((ZAF_CONFIG_SPECIFIC_TYPE) & 0xFF),                                        \
						           ((ZAF_CONFIG_REQUESTED_SECURITY_KEYS >> 0) & 0xFF)}


#endif /* APPLICATION_PROPERTIES_CONFIG_H_ */
