/***************************************************************************//**
 * @file
 * @brief Definitions for the Reporting plugin.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef REPORTING_H
#define REPORTING_H
#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif
#ifdef SL_CATALOG_ZIGBEE_REPORTING_PRESENT
#include "reporting-config.h"
#else
#include "app/framework/plugin/reporting/config/reporting-config.h"
#endif
#if (EMBER_AF_PLUGIN_REPORTING_ENABLE_EXPANDED_TABLE == 1)
#define ENABLE_EXPANDED_TABLE
#endif
#if (EMBER_AF_PLUGIN_REPORTING_ENABLE_GROUP_BOUND_REPORTS == 1)
#define ENABLE_GROUP_BOUND_REPORTS
#endif

//TODO: Properly doxygenate this file

/**
 * @defgroup reporting Reporting
 * @ingroup component
 * @brief API and Callbacks for the Reporting Component
 *
 * Silicon Labs implementation of reporting. Reports are asynchronous messages
 * sent out when an ZCL attribute has changed. This component supports both
 * requesting reports from another device and sending out attribute reports when
 * the device has been configured to do so. If the application receives reports
 * from multiple sources, Silicon Labs recommends configuring it as a
 * concentrator. Note: This component only supports the binding-based
 * interpretation of reporting in which reports are sent to corresponding
 * entries in the binding table. Either the node sending the reports, the node
 * receiving the reports, or another third-party configuration device may create
 * the binding table entry(s) on the reporting node. For more details,
 * refer to the Application Framework Developers Guide for the current SDK
 * version.
 *
 */

/**
 * @addtogroup reporting
 * @{
 */

#define NULL_INDEX 0xFFFF

#if ENABLE_EXPANDED_TABLE
  #include "platform/emdrv/nvm3/inc/nvm3.h"

  #define REPORTING_TABLE_MAX_RANGE 0x400
  #define REPORTING_TABLE_PLUGIN_SIZE (EMBER_AF_PLUGIN_REPORTING_EXPANDED_TABLE_SIZE)

  #define NVM3KEY_REPORTING_TABLE_EXPANDED (NVM3KEY_DOMAIN_ZIGBEE | 0x6000)
  #define REPORTING_TABLE_EXPANDED_MAX_KEY (NVM3KEY_REPORTING_TABLE_EXPANDED + REPORTING_TABLE_MAX_RANGE - 1)
#else // not expanded
  #define REPORTING_TABLE_MAX_RANGE 127
  #define REPORTING_TABLE_PLUGIN_SIZE (EMBER_AF_PLUGIN_REPORTING_TABLE_SIZE)
#endif

// The default reporting will generate a table that is mandatory
// but user may still allocate some table for adding more reporting over
// the air or by cli as part of reporting plugin.
#ifndef REPORT_TABLE_SIZE
#if defined EMBER_AF_GENERATED_REPORTING_CONFIG_DEFAULTS_TABLE_SIZE
#define REPORT_TABLE_SIZE (EMBER_AF_GENERATED_REPORTING_CONFIG_DEFAULTS_TABLE_SIZE + REPORTING_TABLE_PLUGIN_SIZE)
#else
#define REPORT_TABLE_SIZE (REPORTING_TABLE_PLUGIN_SIZE)
#endif
#endif

#if REPORT_TABLE_SIZE > REPORTING_TABLE_MAX_RANGE
 #if ENABLE_EXPANDED_TABLE
   #error "Reporting Table total size exceeds the maximum configuration"
 #else
   #error "Reporting Table total size exceeds the maximum size.  Try enabling the expanded table option"
 #endif
#endif

typedef struct {
  uint32_t lastReportTimeMs;
  EmberAfDifferenceType lastReportValue;
  bool reportableChange;
} sli_zigbee_af_report_volatile_data_type;

extern sli_zigbee_af_report_volatile_data_type sli_zigbee_af_report_volatile_data[];

/**
 * @name API
 * @{
 */

/** @brief Configure the new reported attribute.
 *
 * @param newEntry Pointer to the struct containing the reporting configuration entry
 *
 * @return EmberAfStatus Status code
 *
 */
EmberAfStatus emberAfPluginReportingConfigureReportedAttribute(const EmberAfPluginReportingEntry *newEntry);

/** @brief Load the default reporting configuration.
 */
void emberAfPluginReportingLoadReportingConfigDefaults(void);

/** @brief Get the default reporting configuration.
 *
 * @param defaultConfiguration Pointer to the struct where default configuration will be stored
 *
 * @return bool true if there is a default value
 *
 */
bool emberAfPluginReportingGetReportingConfigDefaults(EmberAfPluginReportingEntry *defaultConfiguration);

/** @} */ // end of name API

/**
 * @name Callbacks
 * @{
 */

/**
 * @defgroup reporting_cb Reporting
 * @ingroup af_callback
 * @brief Callbacks for Reporting Component
 *
 */

/**
 * @addtogroup reporting_cb
 * @{
 */

/** @brief Configure a reporting entry.
 *
 * This callback is called by the Reporting plugin whenever a reporting entry
 * is configured, including when entries are deleted or updated. The
 * application can use this callback for scheduling readings or measurements
 * based on the minimum and maximum reporting interval for the entry. The
 * application should return EMBER_ZCL_STATUS_SUCCESS if it can support the
 * configuration or an error status otherwise. Note: attribute reporting is
 * required for many clusters and attributes, so rejecting a reporting
 * configuration may violate ZigBee specifications.
 *
 * @param entry   Ver.: always
 */
EmberAfStatus emberAfPluginReportingConfiguredCallback(const EmberAfPluginReportingEntry *entry);

/** @brief Get default reporting configuration values.
 *
 * This callback is called by the Reporting plugin to get the default reporting
 * configuration values from the user if a default value is not available within
 * AF-generated default reporting configuration table. The application needs to
 * write to the minInterval, maxInterval, and reportable change in the passed
 * I/O pointer in the argument while handling this callback. The application
 * returns true if it has provided default values or false for
 * reporting plugin for further handling.
 *
 * @param entry   Ver.: always
 */
bool emberAfPluginReportingGetDefaultReportingConfigCallback(EmberAfPluginReportingEntry *entry);

/** @} */ // end of reporting_cb
/** @} */ // end of name Callbacks
/** @} */ // end of reporting

void sli_zigbee_af_reporting_get_entry(uint16_t index, EmberAfPluginReportingEntry *result);
void sli_zigbee_af_reporting_set_entry(uint16_t index, EmberAfPluginReportingEntry *value);
uint16_t sli_zigbee_af_reporting_add_entry(EmberAfPluginReportingEntry* newEntry);
EmberStatus sli_zigbee_af_reporting_remove_entry(uint16_t index);
bool sli_zigbee_af_reporting_do_entries_match(const EmberAfPluginReportingEntry* const entry1,
                                              const EmberAfPluginReportingEntry* const entry2);
uint16_t sli_zigbee_af_reporting_conditionally_add_reporting_entry(EmberAfPluginReportingEntry* newEntry);

uint16_t sli_zigbee_af_reporting_num_entries(void);
uint16_t sli_zigbee_af_reporting_append_entry(EmberAfPluginReportingEntry* newEntry);
void sli_zigbee_af_reporting_get_last_value_all(void);
#endif //REPORTING_H
