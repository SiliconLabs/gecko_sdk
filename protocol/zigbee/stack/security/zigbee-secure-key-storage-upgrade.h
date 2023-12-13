/***************************************************************************//**
 * @file
 * @brief Headers for APIs used in upgrading key storage (from legacy plaintext
 * storage in NVM3 over to PSA storage)
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "stack/include/zigbee-security-manager.h"

//key types to distinguish when printing
enum {
  KEYS_STATUS_NETWORK = 0,
  KEYS_STATUS_LINK = 1,
  KEYS_STATUS_ZLL = 2,
  KEYS_STATUS_GP = 3,
  KEYS_STATUS_OTHER = 4,
  NUMBER_OF_KEY_TYPES = 5,
}; typedef uint8_t zb_sec_man_upgrade_print_categories;

//Main function of upgrade component (calls other functions to migrate each
//key type, tracks the status of overall migration)
void sli_zb_sec_man_upgrade_key_storage(void);

//Move contents of link key table from plaintext NVM3 tokens to Secure Vault
sl_status_t zb_sec_man_upgrade_link_key_table(void);

#if defined(SL_CATALOG_ZIGBEE_GREEN_POWER_PRESENT)
sl_status_t zb_sec_man_upgrade_gp_proxy_table(void);
sl_status_t zb_sec_man_upgrade_gp_sink_table(void);
extern uint8_t sli_zigbee_gp_proxy_table_size;
extern uint8_t sli_zigbee_gp_sink_table_size;
#endif // defined(SL_CATALOG_ZIGBEE_GREEN_POWER_PRESENT)

sl_status_t zb_sec_man_upgrade_nwk_key(uint8_t key_index);

sl_status_t zb_sec_man_upgrade_tc_link_key(void);

#if defined(SL_CATALOG_ZIGBEE_LIGHT_LINK_PRESENT)
sl_status_t zb_sec_man_upgrade_zll_key(void);
#endif // defined(SL_CATALOG_ZIGBEE_LIGHT_LINK_PRESENT)
