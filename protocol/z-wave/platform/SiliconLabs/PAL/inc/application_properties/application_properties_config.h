/***************************************************************************//**
 * # License
 * <b> Copyright 2023 Silicon Laboratories Inc. www.silabs.com </b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of the Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * https://www.silabs.com/about-us/legal/master-software-license-agreement
 * By installing, copying or otherwise using this software, you agree to the
 * terms of the MSLA.
 *
 ******************************************************************************/

#ifndef APPLICATION_PROPERTIES_CONFIG_H_
#define APPLICATION_PROPERTIES_CONFIG_H_

#include "application_properties.h"
#include "ZW_classcmd.h"
#include "zaf_config.h"
#include "zaf_config_security.h"
#include "zw_version_config.h"

/*
 * Change specific and generic device type to 0 for Serial API Controller.
 * Without this, OTW firmware update is not possible from older versions
 * (<7.20.0).
 */
#if (ZAF_CONFIG_GENERIC_TYPE == GENERIC_TYPE_STATIC_CONTROLLER && \
     ZAF_CONFIG_SPECIFIC_TYPE == SPECIFIC_TYPE_PC_CONTROLLER)
#define PRODUCT_ID_GENERIC_TYPE 0
#define PRODUCT_ID_SPECIFIC_TYPE SPECIFIC_TYPE_NOT_USED
#else
#define PRODUCT_ID_GENERIC_TYPE ZAF_CONFIG_GENERIC_TYPE
#define PRODUCT_ID_SPECIFIC_TYPE ZAF_CONFIG_SPECIFIC_TYPE
#endif

#define SL_APPLICATION_SIGNATURE           APPLICATION_SIGNATURE_NONE
#define SL_APPLICATION_SIGNATURE_LOCATION  0x0
#define SL_APPLICATION_TYPE     APPLICATION_TYPE_ZWAVE
#define SL_APPLICATION_VERSION  (APP_VERSION<<16 | APP_REVISION<<8 | APP_PATCH)
#define SL_APPLICATION_CAPABILITIES  0UL
#define SL_APPLICATION_PRODUCT_ID { \
  (ZAF_CONFIG_MANUFACTURER_ID>>8) & 0xFF,     (ZAF_CONFIG_MANUFACTURER_ID>>0) & 0xFF, \
  (ZAF_CONFIG_PRODUCT_ID>>8) & 0xFF,          (ZAF_CONFIG_PRODUCT_ID>>0) & 0xFF, \
  0x00,                                       0x00,\
  0x00,                                       0x00,\
  (ZAF_CONFIG_PRODUCT_TYPE_ID>>8) & 0xFF,     (ZAF_CONFIG_PRODUCT_TYPE_ID>>0) & 0xFF, \
  (ZAF_CONFIG_INSTALLER_ICON_TYPE>>8) & 0xFF, (ZAF_CONFIG_INSTALLER_ICON_TYPE>>0) & 0xFF, \
  (PRODUCT_ID_GENERIC_TYPE>>0) & 0xFF,        (PRODUCT_ID_GENERIC_TYPE>>0) & 0xFF, \
  ((PRODUCT_ID_SPECIFIC_TYPE) & 0xFF), \
  ((ZAF_CONFIG_REQUESTED_SECURITY_KEYS >> 0) & 0xFF) \
}

#endif /* APPLICATION_PROPERTIES_CONFIG_H_ */
