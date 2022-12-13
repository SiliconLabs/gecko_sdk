/**
 * @file
 * @brief This header file contains defines for application version in a generalized way.
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */

#ifndef _CONFIG_APP_H_
#define _CONFIG_APP_H_

#include <ZW_product_id_enum.h>
#include <ZW_classcmd.h>
#include <ZW_security_api.h>

#define APP_VERSION           SDK_VERSION_MAJOR
#define APP_REVISION          SDK_VERSION_MINOR
#define APP_PATCH             SDK_VERSION_PATCH

#ifdef ZW_SECURITY_PROTOCOL
#include <ZW_security_api.h>
#define REQUESTED_SECURITY_KEYS   ( SECURITY_KEY_S0_BIT | SECURITY_KEY_S2_UNAUTHENTICATED_BIT | SECURITY_KEY_S2_AUTHENTICATED_BIT | SECURITY_KEY_S2_ACCESS_BIT)
#else
#define REQUESTED_SECURITY_KEYS   0
#endif  /* ZW_SECURITY_PROTOCOL */

/* Accept all incoming command classes, regardless of NIF contents. */
#define ACCEPT_ALL_CMD_CLASSES

#ifndef ZAF_CONFIG_GENERIC_TYPE
#define ZAF_CONFIG_GENERIC_TYPE 0  //Some of the application do not defines this so this defines here --for example serialapp
#endif

#endif /* _CONFIG_APP_H_ */

