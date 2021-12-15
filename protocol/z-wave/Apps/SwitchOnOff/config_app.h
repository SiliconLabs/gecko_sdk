/**
 * @file
 * @brief Configuration file for Switch On/Off sample application.
 * @details This file contains definitions for the Z-Wave+ Framework as well for the sample app.
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */
#ifndef _CONFIG_APP_H_
#define _CONFIG_APP_H_

#include <ZW_product_id_enum.h>
#include <CC_ManufacturerSpecific.h>

/**
 * Application version, which is generated during release of SDK.
 * The application developer can freely alter the version numbers
 * according to his needs.
 */
#define APP_VERSION           ZAF_VERSION_MAJOR
#define APP_REVISION          ZAF_VERSION_MINOR
#define APP_PATCH             ZAF_VERSION_PATCH

/**
 * Defines device generic and specific types
 */
//@ [GENERIC_TYPE_ID]
#define GENERIC_TYPE          GENERIC_TYPE_SWITCH_BINARY
#define SPECIFIC_TYPE         SPECIFIC_TYPE_NOT_USED
//@ [GENERIC_TYPE_ID]

/**
 * See ZW_basic_api.h for ApplicationNodeInformation field deviceOptionMask
 */
//@ [DEVICE_OPTIONS_MASK_ID]
#define DEVICE_OPTIONS_MASK   APPLICATION_NODEINFO_LISTENING
//@ [DEVICE_OPTIONS_MASK_ID]

/**
 * Defines used to initialize the Z-Wave Plus Info Command Class.
 */
//@ [APP_TYPE_ID]
#define APP_ROLE_TYPE         ZWAVEPLUS_INFO_REPORT_ROLE_TYPE_SLAVE_ALWAYS_ON
#define APP_NODE_TYPE         ZWAVEPLUS_INFO_REPORT_NODE_TYPE_ZWAVEPLUS_NODE
#define APP_ICON_TYPE         ICON_TYPE_GENERIC_ON_OFF_POWER_SWITCH
#define APP_USER_ICON_TYPE    ICON_TYPE_GENERIC_ON_OFF_POWER_SWITCH
//@ [APP_TYPE_ID]

/**
 * Defines used to initialize the Manufacturer Specific Command Class.
 */
#define APP_MANUFACTURER_ID   MFG_ID_ZWAVE
#define APP_PRODUCT_TYPE_ID   PRODUCT_TYPE_ID_ZWAVE_PLUS_V2
#define APP_PRODUCT_ID        PRODUCT_ID_SwitchOnOff

#define APP_FIRMWARE_ID       APP_PRODUCT_ID | (APP_PRODUCT_TYPE_ID << 8)

/**
 * Defines used to initialize the Association Group Information (AGI)
 * Command Class.
 *
 * @attention
 * The sum of NUMBER_OF_ENDPOINTS, MAX_ASSOCIATION_GROUPS and MAX_ASSOCIATION_IN_GROUP
 * may not exceed 18 as defined by ASSOCIATION_ALLOCATION_MAX or an error will be thrown
 * during compilation.
 *
 * @attention
 * It is advised not to change the parameters once a product has been launched, as subsequent
 * upgrades will erase the old structure's content and start a fresh association table.
 */
#define NUMBER_OF_ENDPOINTS         0
#define MAX_ASSOCIATION_GROUPS      1
#define MAX_ASSOCIATION_IN_GROUP    5

/*
 * File identifiers for application file system
 * Range: 0x00000 - 0x0FFFF
 */
#define FILE_ID_APPLICATIONDATA     (0x00000)

/**
 * Security keys
 */
//@ [REQUESTED_SECURITY_KEYS_ID]
#define REQUESTED_SECURITY_KEYS   (SECURITY_KEY_S0_BIT | SECURITY_KEY_S2_UNAUTHENTICATED_BIT | SECURITY_KEY_S2_AUTHENTICATED_BIT)
//@ [REQUESTED_SECURITY_KEYS_ID]

/**
 * Setup if Powerdown DEBUG should be enabled or disabled
 *
 * Setting can have no impact - is target dependent
 *   Silabs 700 series no impact
 *   Silabs 800 series makes it possible for debugger/programmer to contact a target in EM2/EM3 power mode
 *
 * The definition is only set if it's not already set making it possible to pass the frequency to
 * the compiler by command line or in the Studio project.
 */
#ifndef APP_POWERDOWNDEBUG
#define APP_POWERDOWNDEBUG         EPOWERDOWNDEBUG_ENABLED
#endif

#endif /* _CONFIG_APP_H_ */

