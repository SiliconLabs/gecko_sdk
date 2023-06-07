/***************************************************************************//**
 * @file
 * @brief CLI for the Price Client plugin.
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

#include "app/framework/include/af.h"

#include "app/framework/plugin/price-client/price-client.h"

#include "sl_cli.h"
// plugin price-client init <endpoint:1>
void sli_zigbee_af_price_client_cli_init(sl_cli_command_arg_t *arguments)
{
  uint8_t endpoint = sl_cli_get_argument_uint8(arguments, 0);
  emberAfPriceClusterClientInitCallback(endpoint);
}

// plugin price-client print <endpoint:1>
void sli_zigbee_af_price_client_cli_print(sl_cli_command_arg_t *arguments)
{
  uint8_t endpoint = sl_cli_get_argument_uint8(arguments, 0);
  sli_zigbee_af_price_client_print_info(endpoint);
}

// plugin price-client printEvent <endpoint:1> <issuerEventId:4>
void sli_zigbee_af_price_client_cli_printEvent(sl_cli_command_arg_t *arguments)
{
  uint8_t endpoint = sl_cli_get_argument_uint8(arguments, 0);
  uint32_t issuerEventId = sl_cli_get_argument_uint32(arguments, 1);
  sli_zigbee_af_price_client_print_by_event_id(endpoint, issuerEventId);
}

// plugin price-client table-clear <endpoint:1>
void sli_zigbee_af_price_client_cli_table_clear(sl_cli_command_arg_t *arguments)
{
  uint8_t endpoint = sl_cli_get_argument_uint8(arguments, 0);
  sli_zigbee_af_price_clear_price_table(endpoint);
}

// plugin price-client conv-factor printEvent <endpoint:1> <issuerEventId:4>
void sli_zigbee_af_price_client_cli_conversion_factor_print_by_event_id(sl_cli_command_arg_t *arguments)
{
  uint8_t  i;
  uint32_t issuerEventId;
  uint8_t  endpoint;
  endpoint = sl_cli_get_argument_uint8(arguments, 0);
  issuerEventId = sl_cli_get_argument_uint32(arguments, 1);
  i = sli_zigbee_af_price_get_conversion_factor_index_by_event_id(endpoint, issuerEventId);
  sli_zigbee_af_price_print_conversion_factor_entry_index(endpoint, i);
}

// plugin price-client calf-value printEvent <endpoint:1> <issuerEventId:4>
void sli_zigbee_af_price_client_cli_calorific_value_print_by_event_id(sl_cli_command_arg_t *arguments)
{
  uint8_t  i;
  uint32_t issuerEventId;
  uint8_t  endpoint;
  endpoint = sl_cli_get_argument_uint8(arguments, 0);
  issuerEventId = sl_cli_get_argument_uint32(arguments, 1);
  i = sli_zigbee_af_price_get_calorific_value_index_by_event_id(endpoint, issuerEventId);
  sli_zigbee_af_price_print_calorific_value_entry_index(endpoint, i);
}

// plugin price-client co2-value print <endpoint:1>
void sli_zigbee_af_price_client_cli_co2_value_table_print_current(sl_cli_command_arg_t *arguments)
{
  uint8_t i;
  uint8_t  endpoint;
  endpoint = sl_cli_get_argument_uint8(arguments, 0);
  i = emberAfPriceClusterGetActiveCo2ValueIndex(endpoint);
  if ( i < EMBER_AF_PLUGIN_PRICE_CLIENT_CO2_TABLE_SIZE ) {
    sli_zigbee_af_price_print_co2_value_table_print_index(endpoint, i);
  } else {
    emberAfPriceClusterPrintln("NO CURRENT CO2 VALUE");
  }
}

// plugin price-client bill-period printCurrent <endpoint:1>
void sli_zigbee_af_price_client_cli_billing_period_print_current(sl_cli_command_arg_t *arguments)
{
  uint8_t  i;
  uint8_t  endpoint;
  endpoint = sl_cli_get_argument_uint8(arguments, 0);
  i = sli_zigbee_af_price_get_active_billing_period_index(endpoint);
  sli_zigbee_af_price_print_billing_period_table_entry_index(endpoint, i);
}

// plugin price-client block-period printEvent <endpoint:1> <issuerEventId:4>
void sli_zigbee_af_price_client_cli_block_period_print_entry_by_event_id(sl_cli_command_arg_t *arguments)
{
  uint32_t issuerEventId;
  uint8_t  endpoint;
  uint8_t  i;

  endpoint = sl_cli_get_argument_uint8(arguments, 0);
  issuerEventId = sl_cli_get_argument_uint32(arguments, 1);
  i = sli_zigbee_af_price_get_block_period_table_index_by_event_id(endpoint, issuerEventId);
  sli_zigbee_af_price_print_block_period_table_index(endpoint, i);
}

// plugin price-client tier-label printTariff <endpoint:1> <issuerTariffId:4>
void sli_zigbee_af_price_client_cli_tier_label_table_print_tariff_id(sl_cli_command_arg_t *arguments)
{
  uint32_t issuerTariffId;
  uint8_t  i;
  uint8_t  endpoint;
  endpoint = sl_cli_get_argument_uint8(arguments, 0);
  issuerTariffId = sl_cli_get_argument_uint32(arguments, 1);
  i = sli_zigbee_af_price_get_active_tier_label_table_index_by_tariff_id(endpoint, issuerTariffId);
  sli_zigbee_af_price_print_tier_label_table_entry_index(endpoint, i);
}

extern uint8_t emberAfPriceClusterDefaultCppEventAuthorization;

// plugin price-client cpp-event setAuth <cppEventAuth:1>
void sli_zigbee_af_price_client_cli_set_cpp_event_auth(sl_cli_command_arg_t *arguments)
{
  emberAfPriceClusterDefaultCppEventAuthorization = sl_cli_get_argument_uint8(arguments, 0);
}

// plugin price-client consol-bill print <endpoint:1> <index:1>
void sli_zigbee_af_price_client_cli_consolidated_bill_table_print(sl_cli_command_arg_t *arguments)
{
  uint8_t endpoint = sl_cli_get_argument_uint8(arguments, 0);
  uint8_t i = sl_cli_get_argument_uint8(arguments, 1);
  sli_zigbee_af_price_print_consolidated_bill_table_index(endpoint, i);
}

// plugin price-client consol-bill printEvent <endpoint:1> <issuerEventId:4>
void sli_zigbee_af_price_client_cli_consolidated_bill_print_entry_by_event_id(sl_cli_command_arg_t *arguments)
{
  uint8_t  i;
  uint8_t endpoint = sl_cli_get_argument_uint8(arguments, 0);
  uint32_t issuerEventId = sl_cli_get_argument_uint32(arguments, 1);
  i = sli_zigbee_af_price_consolidated_bill_table_get_index_with_event_id(endpoint, issuerEventId);
  if ( i >= EMBER_AF_PLUGIN_PRICE_CLIENT_CONSOLIDATED_BILL_TABLE_SIZE ) {
    emberAfPriceClusterPrintln("NOT FOUND, Event ID=%d", issuerEventId);
  } else {
    sli_zigbee_af_price_print_consolidated_bill_table_index(endpoint, i);
  }
}

// plugin price-client consol-bill printCurrent <endpoint:1
void sli_zigbee_af_price_client_cli_consolidated_bill_print_current_entry(sl_cli_command_arg_t *arguments)
{
  uint8_t i;
  uint8_t endpoint = sl_cli_get_argument_uint8(arguments, 0);
  i = sli_zigbee_af_price_consolidated_bill_table_get_current_index(endpoint);
  if ( i >= EMBER_AF_PLUGIN_PRICE_CLIENT_CONSOLIDATED_BILL_TABLE_SIZE ) {
    emberAfPriceClusterPrintln("NO CURRENT BILL");
  } else {
    sli_zigbee_af_price_print_consolidated_bill_table_index(endpoint, i);
  }
}

// plugin price-client cpp-event print <endpoint:1>
void sli_zigbee_af_price_client_cli_cpp_event_print(sl_cli_command_arg_t *arguments)
{
  uint8_t endpoint = sl_cli_get_argument_uint8(arguments, 0);
  emberAfPricePrintCppEvent(endpoint);
}

// plugin price-client credit-pmt print <endpoint:1> <index:1>
void sli_zigbee_af_price_client_cli_credit_payment_table_print(sl_cli_command_arg_t *arguments)
{
  uint8_t endpoint = sl_cli_get_argument_uint8(arguments, 0);
  uint8_t i = sl_cli_get_argument_uint8(arguments, 1);
  sli_zigbee_af_price_print_credit_payment_table_index(endpoint, i);
}

// plugin price-client credit-pmt printEvent <endpoint:1> <issuerEventId:4>
void sli_zigbee_af_price_client_cli_credit_payment_print_entry_by_event_id(sl_cli_command_arg_t *arguments)
{
  uint8_t  i;
  uint32_t endpoint = sl_cli_get_argument_uint32(arguments, 0);
  uint32_t issuerEventId = sl_cli_get_argument_uint32(arguments, 1);
  i = sli_zigbee_af_price_credit_payment_table_get_index_with_event_id(endpoint, issuerEventId);
  if ( i >= EMBER_AF_PLUGIN_PRICE_CLIENT_CREDIT_PAYMENT_TABLE_SIZE ) {
    emberAfPriceClusterPrintln("NOT FOUND, Event ID=%d", issuerEventId);
  } else {
    sli_zigbee_af_price_print_credit_payment_table_index(endpoint, i);
  }
}

// plugin price-client currency-convers printEvent <endpoint:1> <issuerEventId:4>
void sli_zigbee_af_price_client_cli_currency_conversion_print_by_event_id(sl_cli_command_arg_t *arguments)
{
  uint8_t i;
  uint8_t  endpoint = sl_cli_get_argument_uint8(arguments, 0);
  uint32_t issuerEventId = sl_cli_get_argument_uint32(arguments, 1);
  i = emberAfPriceClusterCurrencyConversionTableGetIndexByEventId(endpoint, issuerEventId);
  if ( i >= EMBER_AF_PLUGIN_PRICE_CLIENT_CURRENCY_CONVERSION_TABLE_SIZE ) {
    emberAfPriceClusterPrintln("NOT FOUND, Event ID=%d", issuerEventId);
  } else {
    sli_zigbee_af_price_print_currency_conversion_table_index(endpoint, i);
  }
}

// plugin price-client currency-convers printCurrent <endpoint:1>
void sli_zigbee_af_price_client_clie_currency_conversion_print_current_currency(sl_cli_command_arg_t *arguments)
{
  uint8_t i;
  uint8_t endpoint = sl_cli_get_argument_uint8(arguments, 0);
  i = emberAfPriceClusterGetActiveCurrencyIndex(endpoint);
  if ( i < EMBER_AF_PLUGIN_PRICE_CLIENT_CURRENCY_CONVERSION_TABLE_SIZE ) {
    sli_zigbee_af_price_print_currency_conversion_table_index(endpoint, i);
  } else {
    emberAfPriceClusterPrintln("NO CURRENT CURRENCY");
  }
}
