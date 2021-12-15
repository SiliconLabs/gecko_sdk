/***************************************************************************//**
 * @brief Initialization APIs for bt stack
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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


#ifndef SL_BT_STACK_INIT_H
#define SL_BT_STACK_INIT_H

#include "sl_status.h"
#include "sl_bt_api.h"
#include "sl_bt_stack_config.h"
#if defined(SL_CATALOG_BLUETOOTH_FEATURE_PERIODIC_ADVERTISER_PRESENT)
#include "sl_bt_periodic_advertiser_config.h"
#endif


/* Forward declarations of BGAPI class declaration structures */
struct sli_bgapi_class;
extern const struct sli_bgapi_class sli_bgapi_class_bt_dfu_optimized;
extern const struct sli_bgapi_class sli_bgapi_class_bt_dfu_full;
extern const struct sli_bgapi_class sli_bgapi_class_bt_system_optimized;
extern const struct sli_bgapi_class sli_bgapi_class_bt_system_full;
extern const struct sli_bgapi_class sli_bgapi_class_bt_gap_optimized;
extern const struct sli_bgapi_class sli_bgapi_class_bt_gap_full;
extern const struct sli_bgapi_class sli_bgapi_class_bt_advertiser_optimized;
extern const struct sli_bgapi_class sli_bgapi_class_bt_advertiser_full;
extern const struct sli_bgapi_class sli_bgapi_class_bt_legacy_advertiser_optimized;
extern const struct sli_bgapi_class sli_bgapi_class_bt_legacy_advertiser_full;
extern const struct sli_bgapi_class sli_bgapi_class_bt_extended_advertiser_optimized;
extern const struct sli_bgapi_class sli_bgapi_class_bt_extended_advertiser_full;
extern const struct sli_bgapi_class sli_bgapi_class_bt_periodic_advertiser_optimized;
extern const struct sli_bgapi_class sli_bgapi_class_bt_periodic_advertiser_full;
extern const struct sli_bgapi_class sli_bgapi_class_bt_scanner_optimized;
extern const struct sli_bgapi_class sli_bgapi_class_bt_scanner_full;
extern const struct sli_bgapi_class sli_bgapi_class_bt_sync_optimized;
extern const struct sli_bgapi_class sli_bgapi_class_bt_sync_full;
extern const struct sli_bgapi_class sli_bgapi_class_bt_connection_optimized;
extern const struct sli_bgapi_class sli_bgapi_class_bt_connection_full;
extern const struct sli_bgapi_class sli_bgapi_class_bt_gatt_optimized;
extern const struct sli_bgapi_class sli_bgapi_class_bt_gatt_full;
extern const struct sli_bgapi_class sli_bgapi_class_bt_gattdb_optimized;
extern const struct sli_bgapi_class sli_bgapi_class_bt_gattdb_full;
extern const struct sli_bgapi_class sli_bgapi_class_bt_gatt_server_optimized;
extern const struct sli_bgapi_class sli_bgapi_class_bt_gatt_server_full;
extern const struct sli_bgapi_class sli_bgapi_class_bt_nvm_optimized;
extern const struct sli_bgapi_class sli_bgapi_class_bt_nvm_full;
extern const struct sli_bgapi_class sli_bgapi_class_bt_test_optimized;
extern const struct sli_bgapi_class sli_bgapi_class_bt_test_full;
extern const struct sli_bgapi_class sli_bgapi_class_bt_sm_optimized;
extern const struct sli_bgapi_class sli_bgapi_class_bt_sm_full;
extern const struct sli_bgapi_class sli_bgapi_class_bt_ota_optimized;
extern const struct sli_bgapi_class sli_bgapi_class_bt_ota_full;
extern const struct sli_bgapi_class sli_bgapi_class_bt_coex_optimized;
extern const struct sli_bgapi_class sli_bgapi_class_bt_coex_full;
extern const struct sli_bgapi_class sli_bgapi_class_bt_l2cap_optimized;
extern const struct sli_bgapi_class sli_bgapi_class_bt_l2cap_full;
extern const struct sli_bgapi_class sli_bgapi_class_bt_cte_transmitter_optimized;
extern const struct sli_bgapi_class sli_bgapi_class_bt_cte_transmitter_full;
extern const struct sli_bgapi_class sli_bgapi_class_bt_cte_receiver_optimized;
extern const struct sli_bgapi_class sli_bgapi_class_bt_cte_receiver_full;

extern void sl_btctrl_init_afh(uint32_t flags);
extern void sl_btctrl_enable_even_connsch();
extern void sli_bt_init_whitelisting();
extern void sl_memory_profiler_init();
extern void sli_bt_init_on_demand_start();
extern void sli_bgapi_init_rtos_adaptation();
extern void sli_bt_sync_enable();
extern void sli_bt_sync_scanner_enable();
extern void sl_btctrl_init_adv_ext();
extern void sli_bt_advertiser_enable_backwards_compatibility();
extern void sli_bt_advertiser_init();
extern void sli_bt_extended_advertiser_init();
extern void sli_bt_init_periodic_advertising();
extern void sli_bt_configure_max_periodic_advertisers(uint8_t max_periodic_advertisers);
extern void sl_btctrl_init_adv();
extern void sl_btctrl_init_adv_ext();
extern void sl_btctrl_init_periodic_adv();
extern void sl_btctrl_init_scan();
extern void sl_btctrl_init_scan_ext();
extern void sl_btctrl_init_conn();

/* Macro to get a pointer to a BGAPI class declaration */
#ifdef SL_BT_API_FULL
#define SL_BT_BGAPI_CLASS(class_name) &sli_bgapi_class_bt_ ## class_name ## _full
#else
#define SL_BT_BGAPI_CLASS(class_name) &sli_bgapi_class_bt_ ## class_name ## _optimized
#endif

/**
 * @brief Initialize controller features according to the feature selection.
 * This function is called by the stack when Bluetooth is started.
 */
void sli_bt_init_controller_features()
{
#if defined(SL_CATALOG_BLUETOOTH_FEATURE_ADVERTISER_PRESENT)
  sl_btctrl_init_adv();
#endif
#if defined(SL_CATALOG_BLUETOOTH_FEATURE_EXTENDED_ADVERTISER_PRESENT) \
    || (defined(SL_CATALOG_BLUETOOTH_FEATURE_ADVERTISER_PRESENT) \
        && !defined(SL_CATALOG_BLUETOOTH_EXTENDED_ADVERTISING_INCOMPATIBLE_PRESENT) \
        && !defined(SL_CATALOG_BLUETOOTH_FEATURE_LEGACY_ADVERTISER_PRESENT) \
        && !defined(SL_CATALOG_BLUETOOTH_FEATURE_EXTENDED_ADVERTISER_PRESENT))
  sl_btctrl_init_adv_ext();
#endif
#if defined(SL_CATALOG_BLUETOOTH_FEATURE_SCANNER_PRESENT)
  sl_btctrl_init_scan();
#endif
#if defined(SL_CATALOG_BLUETOOTH_FEATURE_CONNECTION_PRESENT)
  sl_btctrl_init_conn();
#endif
#if defined(SL_CATALOG_BLUETOOTH_FEATURE_SCANNER_PRESENT) \
    && !defined(SL_CATALOG_BLUETOOTH_EXTENDED_SCANNING_INCOMPATIBLE_PRESENT)
  sl_btctrl_init_scan_ext();
#endif
#if defined(SL_CATALOG_BLUETOOTH_FEATURE_PERIODIC_ADV_PRESENT)
  sl_btctrl_init_periodic_adv();
#endif
}

/**
 * @brief Configure backwards compatibility of the Bluetooth stack.
 *
 * This function uses the component catalog and other configuration to choose
 * what calls to make to the Bluetooth stack to configure backwards
 * compatibility. The functions are used to pull in the relevant implementations
 * from the Bluetooth library at link time.
 */
void sl_bt_configure_backwards_compatibility(const sl_bt_configuration_t *config)
{
  // Ignore the unused parameter in case no configured component needs it
  (void) config;

  // Enable periodic sync functionality if the application uses the "sync" class
#if defined(SL_CATALOG_BLUETOOTH_FEATURE_SYNC_PRESENT)
  sli_bt_sync_enable();
  sli_bt_sync_scanner_enable();
#endif

  // Enable "advertiser" component if the application uses advertising.
#if defined(SL_CATALOG_BLUETOOTH_FEATURE_ADVERTISER_PRESENT)
  sli_bt_advertiser_init();
  // Enable "extended_advertiser" component if the application uses the new
  // extended_advertiser class.
#if defined(SL_CATALOG_BLUETOOTH_FEATURE_EXTENDED_ADVERTISER_PRESENT)
  sli_bt_extended_advertiser_init();
#elif !defined(SL_CATALOG_BLUETOOTH_FEATURE_LEGACY_ADVERTISER_PRESENT) \
  && !defined(SL_CATALOG_BLUETOOTH_FEATURE_EXTENDED_ADVERTISER_PRESENT) \
  && !defined(SL_CATALOG_BLUETOOTH_FEATURE_PERIODIC_ADVERTISER_PRESENT)
  // Enable "advertiser" class backwards compatibility if the application does
  // not use any of the new classes that supersede "advertiser" functionality.
  sli_bt_advertiser_enable_backwards_compatibility();
#if !defined(SL_CATALOG_BLUETOOTH_EXTENDED_ADVERTISING_INCOMPATIBLE_PRESENT)
  sli_bt_extended_advertiser_init();
#endif
#endif
#endif

#if defined(SL_CATALOG_BLUETOOTH_FEATURE_PERIODIC_ADV_PRESENT)
  // When deprecated "bluetooth_feature_periodic_adv" is used, all advertising
  // sets are configured to be capable of periodic advertising.
  sli_bt_configure_max_periodic_advertisers(config->bluetooth.max_advertisers);
#endif

#if defined(SL_CATALOG_BLUETOOTH_FEATURE_PERIODIC_ADVERTISER_PRESENT)
  // When "bluetooth_feature_periodic_advertiser" is used, its configuration specifies
  // the number of advertising sets that are configured to be capable of periodic
  // advertising.
  sli_bt_configure_max_periodic_advertisers(SL_BT_CONFIG_MAX_PERIODIC_ADVERTISERS);
#endif
}

/**
 * @brief Initialize the Bluetooth stack.
 *
 * @param config The pointer of a valid configuration parameters
 * @return SL_STATUS_OK if the initialization was successful; Other error code
 *   indicates a failure.
 */
sl_status_t sl_bt_init_stack(const sl_bt_configuration_t *config);

/**
 * Initialize the Bluetooth on-demand start feature.
 *
 * This function is automatically called by code generated by the Universal
 * Configurator if the feature is included in the project. The application is
 * not expected to call this function directly.
 */
static inline void sl_bt_init_on_demand_start()
{
  sli_bt_init_on_demand_start();
}

/**
 * Initialize BGAPI RTOS adaptation.
 *
 * This function is automatically called by code generated by the Universal
 * Configurator if the feature is included in the project. The application is
 * not expected to call this function directly.
 */
static inline void sl_bgapi_init_rtos_adaptation()
{
  sli_bgapi_init_rtos_adaptation();
}

/**
 * Initialize multiprotocol. Please note that multiprotocol version of RAIL is
 * needed.
 *
 * This function is automatically called by code generated by the Universal
 * Configurator if the feature is included in the project. The application is
 * not expected to call this function directly.
 */
void sl_bt_init_multiprotocol();

/**
 * Initialize and enable Adaptive Frequency Hopping (AFH) feature.
 *
 * This function is automatically called by code generated by the Universal
 * Configurator if the feature is included in the project. The application is
 * not expected to call this function directly.
 */
static inline void sl_bt_init_afh()
{
  sl_btctrl_init_afh(1);
}

/**
 * Enable even scheduling algorithm for Bluetooth
 *
 * This function is automatically called by code generated by the Universal
 * Configurator if the feature is included in the project. The application is
 * not expected to call this function directly.
 */
static inline void sl_bt_enable_even_scheduling()
{
  sl_btctrl_enable_even_connsch();
}

/**
 * Initialize whitelisting feature.
 *
 * This function is automatically called by code generated by the Universal
 * Configurator if the feature is included in the project. The application is
 * not expected to call this function directly.
 */
static inline void sl_bt_init_whitelisting()
{
  sli_bt_init_whitelisting();
}


/**
 * Initialize the BGAPI classes for bt stack.
 *
 * This function is automatically called by code generated by the Universal
 * Configurator if the feature is included in the project. The application is
 * not expected to call this function directly.
 *
 * @param[in] classes NULL-terminated array of pointers to class declarations.
 *   The array must remain valid until the next system reboot.
 *
 * @return SL_STATUS_OK if the initialization was successful; Other error code
 *   indicates a failure.
 */
sl_status_t sl_bt_init_classes(const struct sli_bgapi_class * const * classes);

#endif