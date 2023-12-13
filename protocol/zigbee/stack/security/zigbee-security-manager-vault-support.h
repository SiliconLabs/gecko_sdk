/***************************************************************************//**
 * @file
 * @brief Definitions for zigbee secure vault key ids and related macros.
 * See @ref token_stack for documentation.
 *
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef ZIGBEE_SECURITY_MANAGER_VAULT_SUPPORT_H
#define ZIGBEE_SECURITY_MANAGER_VAULT_SUPPORT_H

#include "security_manager.h"

#define ZB_PSA_KEY_TYPE (PSA_KEY_TYPE_AES)
#define ZB_PSA_ALG (PSA_ALG_AEAD_WITH_SHORTENED_TAG(PSA_ALG_CCM, 4))
#define ZB_PSA_KEY_USAGE (PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT | PSA_KEY_USAGE_EXPORT)

// These are the list of persisted keys and their IDs in PSA storage.
// Do NOT change these IDs across SDK versions because it will break backwards
// compatibility
#define ZB_PSA_KEY_ID_MIN                             0x00030000
#define ZB_PSA_KEY_ID_MAX                             0x0003FFFF
// These keys with offsets are indexed keys. There are a variable number of
// them. We reserve a maximum of 255 entries for them, each, but they are
// ultimately sized by their respective EMBER*SIZE macros (see below)
#define LINK_KEY_TABLE_OFFSET                         0x00000100
#define GREEN_POWER_PROXY_TABLE_OFFSET                0x00000200
#define GREEN_POWER_SINK_TABLE_OFFSET                 0x00000300

#define ZB_PSA_KEY_ID_ACTIVE_NWK_KEY                  (ZB_PSA_KEY_ID_MIN + 0)
#define ZB_PSA_KEY_ID_ALTERNATE_NWK_KEY               (ZB_PSA_KEY_ID_MIN + 1)
#define ZB_PSA_KEY_ID_PRECONFIGURED_APS_KEY           (ZB_PSA_KEY_ID_MIN + 2)
#define ZB_PSA_KEY_ID_ZLL_ENCRYPT_KEY                 (ZB_PSA_KEY_ID_MIN + 3)
#define ZB_PSA_KEY_ID_ZLL_PRE_CONFIGURED_KEY          (ZB_PSA_KEY_ID_MIN + 4)
#define ZB_PSA_KEY_ID_SECURE_EZSP_KEY                 (ZB_PSA_KEY_ID_MIN + 5)  // Deprecated
#define ZB_PSA_KEY_ID_VERSION_KEY                     (ZB_PSA_KEY_ID_MIN + 16)
#define ZB_PSA_KEY_ID_LINK_KEY_TABLE_START            (ZB_PSA_KEY_ID_MIN + LINK_KEY_TABLE_OFFSET)
#define ZB_PSA_KEY_ID_LINK_KEY_TABLE_END              (ZB_PSA_KEY_ID_LINK_KEY_TABLE_START + EMBER_KEY_TABLE_SIZE)
#define ZB_PSA_KEY_ID_GP_PROXY_TABLE_START            (ZB_PSA_KEY_ID_MIN + GREEN_POWER_PROXY_TABLE_OFFSET)
#define ZB_PSA_KEY_ID_GP_PROXY_TABLE_END              (ZB_PSA_KEY_ID_LINK_KEY_TABLE_START + EMBER_GP_PROXY_TABLE_SIZE)
#define ZB_PSA_KEY_ID_GP_SINK_TABLE_START             (ZB_PSA_KEY_ID_MIN + GREEN_POWER_SINK_TABLE_OFFSET)
#define ZB_PSA_KEY_ID_GP_SINK_TABLE_END               (ZB_PSA_KEY_ID_LINK_KEY_TABLE_START + EMBER_GP_SINK_TABLE_SIZE)

sl_status_t psa_to_sl_status(psa_status_t sec_man_error);

//Set version key byte in PSA to the most recent value
sl_status_t zb_sec_man_store_version_key(void);
//Get version key byte currently stored in PSA
//(to see if something may be outdated)
sl_status_t zb_sec_man_fetch_version_key(uint8_t* version);
#define ZB_SEC_MAN_CURRENT_VERSION_KEY 0x01
#define ZB_SEC_MAN_CURRENT_VERSION_KEY_SIZE 1

#if defined(SEMAILBOX_PRESENT)
#include "sli_se_opaque_functions.h"
#include "sli_se_opaque_types.h"
#endif

#endif // ZIGBEE_SECURITY_MANAGER_VAULT_SUPPORT_H
