/**
 * @file zaf_cc_list_generator.c
 *
 * Generates CC lists used for the Node Information Frame and for validation of incoming frames.
 *
 * @copyright 2022 Silicon Laboratories Inc.
 */

#include <zaf_cc_list_generator.h>
#include <ZAF_CC_Invoker.h>
#include <FreeRTOS.h>
#include <zaf_config_api.h>

//#define DEBUGPRINT
#include "DebugPrint.h"

typedef struct zaf_endpoint_cc_lists {
  zaf_cc_list_t unsecure_included_ccs;
  zaf_cc_list_t secure_included_unsecure_ccs;
  zaf_cc_list_t secure_included_secure_ccs;
} zaf_endpoint_cc_lists_t;

static zaf_cc_list_t g_unsecure_included_ccs = {
  .cc_list = NULL,
  .list_size = 0,
};

static zaf_cc_list_t g_secure_included_unsecure_ccs = {
  .cc_list = NULL,
  .list_size = 0,
};

static zaf_cc_list_t g_secure_included_secure_ccs = {
  .cc_list = NULL,
  .list_size = 0,
};

static zaf_endpoint_cc_lists_t *g_endpoints_ccs = NULL;

static bool should_skip_cc(zaf_cc_list_t *zaf_cc_list, uint8_t cc)
{
  uint8_t i;

  for (i = 0; i < zaf_cc_list->list_size; i++) {
    if (zaf_cc_list->cc_list[i] == cc) {
      return true;
    }
    // DT:03.11.0003.1
    if (cc == COMMAND_CLASS_SWITCH_BINARY
        && zaf_cc_list->cc_list[i] == COMMAND_CLASS_SWITCH_MULTILEVEL) {
      return true;
    }
    // DT:03.11.0003.1
    if (cc == COMMAND_CLASS_SWITCH_MULTILEVEL
        && zaf_cc_list->cc_list[i] == COMMAND_CLASS_SWITCH_BINARY) {
      return true;
    }
  }

  return false;
}

static bool add_to_lists(uint8_t endpoint, uint8_t cc)
{
  bool should_skip;
  zaf_cc_list_t *unsecure_included_cc;
  zaf_cc_list_t *secure_included_unsecure_cc;
  zaf_cc_list_t *secure_included_secure_cc;

  zafi_cc_list_generator_get_lists(endpoint, &unsecure_included_cc, &secure_included_unsecure_cc, &secure_included_secure_cc);

  should_skip = false;
  should_skip |= should_skip_cc(unsecure_included_cc, cc);
  should_skip |= should_skip_cc(secure_included_unsecure_cc, cc);
  should_skip |= should_skip_cc(secure_included_secure_cc, cc);

  // If command class is already included
  // Bail out
  if (should_skip) {
    return false;
  }

  switch (cc) {
    // CC:0020.01.00.21.003
    // CC:0020.01.00.21.004
    case COMMAND_CLASS_BASIC:
    // Dummy CC added to avoid empty list
    case 0xFF:
      return true;
    case COMMAND_CLASS_ZWAVEPLUS_INFO:
    case COMMAND_CLASS_TRANSPORT_SERVICE_V2:
    case COMMAND_CLASS_SECURITY:
    case COMMAND_CLASS_SECURITY_2:
    case COMMAND_CLASS_SUPERVISION:
    case COMMAND_CLASS_APPLICATION_STATUS:
    case COMMAND_CLASS_INCLUSION_CONTROLLER:
    case COMMAND_CLASS_MULTI_CMD:
    case COMMAND_CLASS_TIME:
      unsecure_included_cc->cc_list[unsecure_included_cc->list_size++] = cc;
      secure_included_unsecure_cc->cc_list[secure_included_unsecure_cc->list_size++] = cc;
      break;

    default:
      if (!zaf_config_get_secure_only()) {
        unsecure_included_cc->cc_list[unsecure_included_cc->list_size++] = cc;
      }
      secure_included_secure_cc->cc_list[secure_included_secure_cc->list_size++] = cc;
      break;
  }

  return true;
}

static bool fill_lists_from_config(zaf_cc_config_entry_latest_t const * const p_cc_config_entry, void *context)
{
  uint8_t endpoint;

  endpoint = *(uint8_t*)context;

  if (!p_cc_config_entry->p_cc_configuration
      || p_cc_config_entry->p_cc_configuration->endpoint != endpoint) {
    return false;
  }

  // Inserted directly on the list
  switch (p_cc_config_entry->command_class) {
    case COMMAND_CLASS_ZWAVEPLUS_INFO:
    case COMMAND_CLASS_SECURITY:
    case COMMAND_CLASS_SECURITY_2:
    case COMMAND_CLASS_TRANSPORT_SERVICE_V2:
      break;

    default:
      add_to_lists(endpoint, (uint8_t) p_cc_config_entry->command_class);
      add_to_lists(0, (uint8_t) p_cc_config_entry->command_class);
      break;
  }

  return false;
}

static bool fill_lists(CC_handler_map_latest_t const * const p_cc_entry, __attribute__((unused)) zaf_cc_context_t context)
{
  // Inserted directly on the list
  switch (p_cc_entry->CC) {
    case COMMAND_CLASS_ZWAVEPLUS_INFO:
    case COMMAND_CLASS_SECURITY:
    case COMMAND_CLASS_SECURITY_2:
    case COMMAND_CLASS_TRANSPORT_SERVICE_V2:
      return false;

    default:
      add_to_lists(0, (uint8_t) p_cc_entry->CC);
      return false;
  }
}

static void add_mandatory_ccs(uint8_t endpoint, uint8_t requested_security_keys)
{
  add_to_lists(endpoint, COMMAND_CLASS_ZWAVEPLUS_INFO);

  if (requested_security_keys & SECURITY_KEY_S0_BIT) {
    add_to_lists(endpoint, COMMAND_CLASS_SECURITY);
  }

  if (requested_security_keys & SECURITY_KEY_S2_MASK) {
    add_to_lists(endpoint, COMMAND_CLASS_SECURITY_2);
  }

  if (endpoint != 0) {
    //DT:00.11.0005.1
    add_to_lists(endpoint, COMMAND_CLASS_ASSOCIATION);
    add_to_lists(endpoint, COMMAND_CLASS_MULTI_CHANNEL_ASSOCIATION_V2);
    add_to_lists(endpoint, COMMAND_CLASS_ASSOCIATION_GRP_INFO);
    add_to_lists(endpoint, COMMAND_CLASS_SUPERVISION);
  } else {
    // CC:0055.02.00.21.003
    add_to_lists(endpoint, COMMAND_CLASS_TRANSPORT_SERVICE_V2);
  }
}

void zafi_cc_list_generator_get_lists(uint8_t endpoint, zaf_cc_list_t **unsecure_included_ccs, zaf_cc_list_t **secure_included_unsecure_ccs, zaf_cc_list_t **secure_included_secure_ccs)
{
  uint8_t number_of_endpoints;

  number_of_endpoints = zaf_config_get_number_of_endpoints();

  if (endpoint == 0) {
    *unsecure_included_ccs = &g_unsecure_included_ccs;
    *secure_included_unsecure_ccs = &g_secure_included_unsecure_ccs;
    *secure_included_secure_ccs = &g_secure_included_secure_ccs;
  } else if (g_endpoints_ccs && (--endpoint) < number_of_endpoints) {
    *unsecure_included_ccs = &g_endpoints_ccs[endpoint].unsecure_included_ccs;
    *secure_included_unsecure_ccs = &g_endpoints_ccs[endpoint].secure_included_unsecure_ccs;
    *secure_included_secure_ccs = &g_endpoints_ccs[endpoint].secure_included_secure_ccs;
  } else {
    *unsecure_included_ccs = NULL;
    *secure_included_unsecure_ccs = NULL;
    *secure_included_secure_ccs = NULL;
  }
}

void zafi_cc_list_generator_generate(void)
{
  uint8_t requested_security_keys;
  uint8_t number_of_endpoints;
  uint8_t i;
  size_t cc_list_max_size;

  requested_security_keys = zaf_config_get_requested_security_keys();
  cc_list_max_size = ZAF_CC_handler_map_size();
  number_of_endpoints = zaf_config_get_number_of_endpoints();

  if (requested_security_keys & SECURITY_KEY_S0_BIT) {
    cc_list_max_size++;
  }

  if (requested_security_keys & SECURITY_KEY_S2_MASK) {
    cc_list_max_size++;
  }

  // CC:0055.02.00.21.003
  // COMMAND_CLASS_TRANSPORT_SERVICE_V2
  cc_list_max_size++;

  // Allocated lists
  g_unsecure_included_ccs.cc_list = pvPortMalloc(cc_list_max_size * sizeof(uint8_t));
  g_unsecure_included_ccs.list_size = 0;
  g_secure_included_unsecure_ccs.cc_list = pvPortMalloc(cc_list_max_size * sizeof(uint8_t));
  g_secure_included_unsecure_ccs.list_size = 0;
  g_secure_included_secure_ccs.cc_list = pvPortMalloc(cc_list_max_size * sizeof(uint8_t));
  g_secure_included_secure_ccs.list_size = 0;
  add_mandatory_ccs(0, requested_security_keys);

  // Handle endpoints before, root device
  if (number_of_endpoints > 0) {
    g_endpoints_ccs = pvPortMalloc(number_of_endpoints * sizeof(zaf_endpoint_cc_lists_t));
    for (i = 0; i < number_of_endpoints; ) {
      g_endpoints_ccs[i].unsecure_included_ccs.cc_list = pvPortMalloc(cc_list_max_size * sizeof(uint8_t));
      g_endpoints_ccs[i].unsecure_included_ccs.list_size = 0;
      g_endpoints_ccs[i].secure_included_unsecure_ccs.cc_list = pvPortMalloc(cc_list_max_size * sizeof(uint8_t));
      g_endpoints_ccs[i].secure_included_unsecure_ccs.list_size = 0;
      g_endpoints_ccs[i].secure_included_secure_ccs.cc_list = pvPortMalloc(cc_list_max_size * sizeof(uint8_t));
      g_endpoints_ccs[i].secure_included_secure_ccs.list_size = 0;
      // Endpoint is not 0 indexed
      i++;
      add_mandatory_ccs(i, requested_security_keys);
      ZAF_CC_config_foreach(fill_lists_from_config, &i);
    }
  }

  ZAF_CC_foreach(fill_lists, NULL);
}

void zafi_cc_list_generator_destroy(void)
{
  uint8_t number_of_endpoints;
  uint8_t i;

  number_of_endpoints = zaf_config_get_number_of_endpoints();

  if (number_of_endpoints > 0) {
    for (i = 0; i < number_of_endpoints; i++) {
      g_endpoints_ccs[i].unsecure_included_ccs.list_size = 0;
      vPortFree(g_endpoints_ccs[i].unsecure_included_ccs.cc_list);
      g_endpoints_ccs[i].secure_included_unsecure_ccs.list_size = 0;
      vPortFree(g_endpoints_ccs[i].secure_included_unsecure_ccs.cc_list);
      g_endpoints_ccs[i].secure_included_secure_ccs.list_size = 0;
      vPortFree(g_endpoints_ccs[i].secure_included_secure_ccs.cc_list);
    }
    vPortFree(g_endpoints_ccs);
  }

  g_unsecure_included_ccs.list_size = 0;
  vPortFree(g_unsecure_included_ccs.cc_list);
  g_secure_included_unsecure_ccs.list_size = 0;
  vPortFree(g_secure_included_unsecure_ccs.cc_list);
  g_secure_included_secure_ccs.list_size = 0;
  vPortFree(g_secure_included_secure_ccs.cc_list);
}
