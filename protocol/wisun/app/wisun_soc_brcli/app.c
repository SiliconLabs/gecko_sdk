/***************************************************************************//**
 * @file app.c
 * @brief Application code
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

#include <stdio.h>
#include <string.h>
#include <machine/endian.h>
#include <assert.h>
#include <cmsis_os2.h>
#include "em_device.h"
#include "sl_malloc.h"
#include "sl_cli.h"
#include "sl_wisun_br_api.h"
#include "app_settings.h"
#include "sl_wisun_cli_core.h"
#include "sl_wisun_cli_util.h"
#include "app_certificate_store.h"
#include "borderrouter_tasklet.h"
#include "sl_wisun_version.h"
#include "rail_features.h"

#if defined(SL_CATALOG_MICRIUMOS_KERNEL_PRESENT)
#include "os.h"
#endif
#if defined(SL_CATALOG_FREERTOS_KERNEL_PRESENT)
#include "FreeRTOS.h"
#include "task.h"
#endif

#define APP_TASK_PRIORITY 11
#define APP_TASK_STACK_SIZE 500 // in units of CPU_INT32U

/// Maximum size of a certificate
#define APP_CERTIFICATE_MAX_SIZE 2048

/// All certificates index
#define APP_CERTIFICATE_INDEX_ALL 255

/// Current certificate
static app_certificate_t *app_certificate;

/// Current certificate index
uint32_t app_certificate_index;

osThreadId_t app_task_id;

static const app_enum_t app_certificate_index_enum[] =
{
  { "all", APP_CERTIFICATE_INDEX_ALL },
  { NULL, 0 }
};

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

static void app_start(sl_wisun_phy_config_type_t phy_config_type)
{
  app_certificate_t *cert;
  app_certicate_info_t info;
  sl_status_t ret;
  uint16_t option = SL_WISUN_CERTIFICATE_OPTION_NONE;
  int i;
  sl_wisun_channel_mask_t channel_mask;
  sl_wisun_phy_config_t phy_config;
  sl_wisun_br_connection_params_t params;

  app_wisun_cli_mutex_lock();

  if (sl_wisun_br_set_tx_power(app_settings_wisun.tx_power) != SL_STATUS_OK) {
    printf("Fail to set Tx power!\r\n");
    goto cleanup;
  }

  switch (app_settings_wisun.network_size) {
    case SL_WISUN_NETWORK_SIZE_SMALL:
      params = SL_WISUN_BR_PARAMS_PROFILE_SMALL;
      break;
    case SL_WISUN_NETWORK_SIZE_MEDIUM:
      params = SL_WISUN_BR_PARAMS_PROFILE_MEDIUM;
      break;
    case SL_WISUN_NETWORK_SIZE_LARGE:
      params = SL_WISUN_BR_PARAMS_PROFILE_LARGE;
      break;
    case SL_WISUN_NETWORK_SIZE_TEST:
      params = SL_WISUN_BR_PARAMS_PROFILE_TEST;
      break;
    default:
      printf("[Failed: unsupported network size]\r\n");
      goto cleanup;
  }
  if (sl_wisun_br_set_connection_parameters(&params) != SL_STATUS_OK) {
    printf("[Failed to set network size!]\r\n");
    goto cleanup;
  }

  if (app_settings_get_channel_mask(app_settings_wisun.allowed_channels, &channel_mask) != SL_STATUS_OK) {
    printf("Failed to retrieve channel mask!\r\n");
    goto cleanup;
  }

  if (sl_wisun_br_set_channel_mask(&channel_mask) != SL_STATUS_OK) {
    printf("Failed to set channel mask!\r\n");
    goto cleanup;
  }

  if (sl_wisun_br_set_unicast_settings(app_settings_wisun.uc_dwell_interval_ms) != SL_STATUS_OK) {
    printf("Failed to set unicast settings!\r\n");
    goto cleanup;
  }

  if (sl_wisun_br_set_broadcast_settings(app_settings_wisun.bc_interval_ms,
                                         app_settings_wisun.bc_dwell_interval_ms) != SL_STATUS_OK) {
    printf("Failed to set broadcast settings!\r\n");
    goto cleanup;
  }

  for (i = 0; i < APP_CERTIFICATE_STORE_MAX_INDEX; ++i) {
    cert =  app_certificate_store_get(i);
    if (cert) {
      ret = app_certificate_parse(cert, &info);
      if (ret == SL_STATUS_OK) {
        if (info.type == app_certificate_type_trusted) {
          ret = sl_wisun_br_set_trusted_certificate(option,
                                                    cert->data_length,
                                                    cert->data);
          // There are potentially multiple trusted certificates,
          // append the following certificates into the chain.
          option |= SL_WISUN_CERTIFICATE_OPTION_APPEND;
        } else if (info.type == app_certificate_type_device) {
          ret = sl_wisun_set_br_device_certificate(SL_WISUN_CERTIFICATE_OPTION_HAS_KEY,
                                                   cert->data_length,
                                                   cert->data);
        } else if (info.type == app_certificate_type_device_pk) {
          ret = sl_wisun_set_br_device_private_key(SL_WISUN_CERTIFICATE_OPTION_NONE,
                                                   cert->data_length,
                                                   cert->data);
        }
      }

      app_certificate_free(cert);

      if (ret != SL_STATUS_OK) {
        printf("[Failed: unable to set certificate: %lu]\r\n", ret);
        goto cleanup;
      }
    }
  }

  ret = sl_wisun_br_set_regulation(app_settings_wisun.regulation);
  if (ret != SL_STATUS_OK) {
    printf("[Failed: unable to set regional regulation: %lu]\r\n", ret);
    goto cleanup;
  }

  switch (phy_config_type) {
      case SL_WISUN_PHY_CONFIG_FAN10:
        phy_config.config.fan10.reg_domain = app_settings_wisun.regulatory_domain;
        phy_config.config.fan10.op_class = app_settings_wisun.operating_class;
        phy_config.config.fan10.op_mode = app_settings_wisun.operating_mode;
        phy_config.config.fan10.fec = app_settings_wisun.fec;
        break;
      case SL_WISUN_PHY_CONFIG_FAN11:
        phy_config.config.fan11.reg_domain = app_settings_wisun.regulatory_domain;
        phy_config.config.fan11.chan_plan_id = app_settings_wisun.chan_plan_id;
        phy_config.config.fan11.phy_mode_id = app_settings_wisun.phy_mode_id;
        break;
      case SL_WISUN_PHY_CONFIG_EXPLICIT:
        phy_config.config.explicit.ch0_frequency_khz = app_settings_wisun.ch0_frequency;
        phy_config.config.explicit.number_of_channels = app_settings_wisun.number_of_channels;
        phy_config.config.explicit.channel_spacing = app_settings_wisun.channel_spacing;
        phy_config.config.explicit.phy_mode_id = app_settings_wisun.phy_mode_id;
        break;
      case SL_WISUN_PHY_CONFIG_IDS:
        phy_config.config.ids.protocol_id = app_settings_wisun.protocol_id;
        phy_config.config.ids.channel_id  = app_settings_wisun.channel_id;
        break;
      default:
        printf("[Failed: unsupported PHY configuration type: %u]\r\n", phy_config_type);
        goto cleanup;
  }

  app_settings_wisun.phy_config_type = phy_config.type = phy_config_type;

#if RAIL_IEEE802154_SUPPORTS_G_MODESWITCH
  if (app_settings_wisun.rx_phy_mode_ids_count) {
    ret = sl_wisun_br_set_pom_ie(app_settings_wisun.rx_phy_mode_ids_count,
                                 app_settings_wisun.rx_phy_mode_ids,
                                 0);
    if (ret != SL_STATUS_OK) {
      printf("[Failed: unable to RX PhyModeId list: %lu]\r\n", ret);
      goto cleanup;
    }
  }
#endif

  if (sl_wisun_br_start((const uint8_t *)app_settings_wisun.network_name, &phy_config)  == SL_STATUS_OK) {
    printf("Border router started\r\n");
  } else {
    printf("Failed to start border router\r\n");
  }

cleanup:
  app_wisun_cli_mutex_unlock();
}

void app_start_fan10(sl_cli_command_arg_t *arguments)
{
  (void)arguments;

  app_start(SL_WISUN_PHY_CONFIG_FAN10);
}

void app_start_fan11(sl_cli_command_arg_t *arguments)
{
  (void)arguments;

  app_start(SL_WISUN_PHY_CONFIG_FAN11);
}

void app_start_explicit(sl_cli_command_arg_t *arguments)
{
  (void)arguments;

  app_start(SL_WISUN_PHY_CONFIG_EXPLICIT);
}

void app_start_ids(sl_cli_command_arg_t *arguments)
{
  (void)arguments;

  app_start(SL_WISUN_PHY_CONFIG_IDS);
}

void app_about(void)
{
  printf("Wi-SUN Border Router CLI Application\r\n");
  printf("Versions:\r\n");
#if defined(__GNUC__) && defined(__GNUC_MINOR__) && defined(__GNUC_PATCHLEVEL__)
  printf("  * Compiler (GCC): %u.%u.%u\r\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#endif
#if defined(__ICCARM__) && defined(__VER__)
  printf("  * Compiler (IAR): %lu.%lu.%lu\r\n", __VER__ / 1000000UL, (__VER__ % 1000000UL) / 1000UL, __VER__ % 1000UL);
#endif
#if defined(SL_CATALOG_MICRIUMOS_KERNEL_PRESENT) && defined(OS_VERSION)
  printf("  * Micrium OS kernel: %lu.%lu.%lu\r\n", OS_VERSION / 10000UL, (OS_VERSION % 10000UL) / 100UL, OS_VERSION % 100UL);
#endif
#if defined(SL_CATALOG_FREERTOS_KERNEL_PRESENT) && defined(tskKERNEL_VERSION_MAJOR) && defined(tskKERNEL_VERSION_MINOR) && defined(tskKERNEL_VERSION_BUILD)
  printf("  * FreeRTOS kernel: %u.%u.%u\r\n", tskKERNEL_VERSION_MAJOR, tskKERNEL_VERSION_MINOR, tskKERNEL_VERSION_BUILD);
#endif
#if defined(SL_WISUN_VERSION_MAJOR) && defined(SL_WISUN_VERSION_MINOR) && defined(SL_WISUN_VERSION_PATCH)
  printf("  * Wi-SUN: %u.%u.%u\r\n", SL_WISUN_VERSION_MAJOR, SL_WISUN_VERSION_MINOR, SL_WISUN_VERSION_PATCH);
#endif
}

void app_reboot(sl_cli_command_arg_t *arguments)
{
  (void) arguments;

  app_wisun_cli_mutex_lock();

  NVIC_SystemReset();

  app_wisun_cli_mutex_unlock();
}

static void app_handle_certificate_line(char *arg_str, void *user)
{
  sl_status_t ret;
  app_certicate_info_t info;
  (void)user;

  if (!arg_str) {
    return;
  }

  if ((strlen(arg_str) == 1) && (arg_str[0] == '.')) {
    sl_cli_redirect_command(sl_cli_default_handle, NULL, NULL, NULL);
    ret = app_certificate_parse(app_certificate, &info);
    if (ret != SL_STATUS_OK) {
      printf("[Failed: invalid certificate: %lu]\r\n", ret);
      return;
    }
    ret = app_certificate_store_set((uint8_t)app_certificate_index, app_certificate);
    if (ret == SL_STATUS_OK) {
      printf("[Certificate saved]\r\n");
    } else {
      printf("[Failed: unable to store certificate: %lu]\r\n", ret);
    }
  } else {
    app_certificate_append_string(app_certificate, arg_str);
  }
}

void app_certificate_store(sl_cli_command_arg_t *arguments)
{
  app_wisun_cli_mutex_lock();

  app_certificate_index = sl_cli_get_argument_uint8(arguments, 0);

  app_certificate = app_certificate_init(APP_CERTIFICATE_MAX_SIZE);
  if (!app_certificate) {
    printf("[Failed: unable to store certificate]\r\n");
    goto cleanup;
  }

  sl_cli_redirect_command(sl_cli_default_handle, app_handle_certificate_line, "Certificate> ", NULL);

  printf("[Enter certificate line by line, followed by . (dot) on a separate line]\r\n");

cleanup:

  app_wisun_cli_mutex_unlock();
}

void app_certificate_remove(sl_cli_command_arg_t *arguments)
{
  sl_status_t ret;
  char *index;

  app_wisun_cli_mutex_lock();

  if (sl_cli_get_argument_count(arguments) != 1) {
    printf("[Failed: incorrect number of arguments]\r\n");
    goto cleanup;
  }

  index = sl_cli_get_argument_string(arguments, 0);
  if (index == NULL) {
    printf("[Failed: missing index]\r\n");
    goto cleanup;
  }

  ret = app_util_get_integer(&app_certificate_index,
                             index,
                             app_certificate_index_enum,
                             false);
  if (ret != SL_STATUS_OK) {
    printf("[Failed: invalid index: %s]\r\n", index);
    goto cleanup;
  }

  if (app_certificate_index == APP_CERTIFICATE_INDEX_ALL) {
    ret = app_certificate_store_remove(APP_CERTIFICATE_INDEX_ALL);
  } else {
    ret = app_certificate_store_remove(1 << app_certificate_index);
  }
  if (ret == SL_STATUS_OK) {
    printf("[Certificate removal succeeded]\r\n");
    goto cleanup;
  } else {
    printf("[Certificate removal failed: %lu]\r\n", ret);
    goto cleanup;
  }

cleanup:

  app_wisun_cli_mutex_unlock();
}

static const app_enum_t app_trace_level_type_enum[] =
{
  {"all",  0xFF},
  {NULL,      0}
};

static const app_enum_t app_trace_level_enum[] =
{
  {"none",    0},
  {"error",   1},
  {"err",     1},
  {"warning", 2},
  {"warn",    2},
  {"info",    3},
  {"debug",   4},
  {"dbg",     4},
  {NULL,      0}
};

static bool trace_level_add_entry(sl_wisun_trace_group_config_t *trace_config, uint8_t *group_count, uint8_t group_id, uint8_t trace_level)
{
  uint8_t i;

  for (i = 0; i < *group_count; i++) {
    if (trace_config[i].group_id == group_id) {
      // Found existing group. Update it.
      trace_config[i].trace_level = trace_level;
      return true;
    }
  }

  // group not found. Add new one.
  trace_config[i].group_id = group_id;
  trace_config[i].trace_level = trace_level;
  (*group_count)++;
  return false;
}

void app_set_trace_level(sl_cli_command_arg_t *arguments)
{
  sl_status_t ret;
  uint8_t i, group_count = 0;
  char *trace_config_string;
  uint32_t trace_level, group_id;
  char group_id_str[20], trace_level_str[20];
  sl_wisun_trace_group_config_t *trace_config = NULL;
  int res;
  const app_enum_t *value_enum;

  app_wisun_cli_mutex_lock();

  trace_config_string = sl_cli_get_argument_string(arguments, 0);
  trace_config = sl_malloc(SL_WISUN_TRACE_GROUP_COUNT * sizeof(sl_wisun_trace_group_config_t));
  trace_config_string = strtok(trace_config_string, ";");
  while (trace_config_string != NULL) {

    res = sscanf(trace_config_string, "%[^,],%s", group_id_str, trace_level_str);
    if (res != 2) {
      // Error parsing string
      ret = SL_STATUS_INVALID_PARAMETER;
      goto cleanup;
    }

    // Check group_id enum
    value_enum = app_util_get_enum_by_string(app_trace_level_type_enum, group_id_str);
    if (value_enum) {
      // group_id is an enum (only "all" accepted)

      // Check trace_level enum
      value_enum = app_util_get_enum_by_string(app_trace_level_enum, trace_level_str);

      if (value_enum) {
        trace_level = value_enum->value;
      } else {
        ret = app_util_get_integer(&trace_level, trace_level_str, NULL, false);
        if (ret != SL_STATUS_OK) {
          // Not a valid level value
          ret = SL_STATUS_INVALID_TYPE;
          goto cleanup;
        }
      }

      for (i = 0; i < SL_WISUN_TRACE_GROUP_COUNT; i++) {
        trace_level_add_entry(trace_config, &group_count, i, trace_level);
      }
    } else {
      // group_id is not an enum

      ret = app_util_get_integer(&group_id, group_id_str, NULL, false);
      if (ret != SL_STATUS_OK) {
        // Not a valid group value
        ret = SL_STATUS_INVALID_TYPE;
        goto cleanup;
      }

      // Check trace_level enum
      value_enum = app_util_get_enum_by_string(app_trace_level_enum, trace_level_str);

      if (value_enum) {
        trace_level = value_enum->value;
      } else {
        ret = app_util_get_integer(&trace_level, trace_level_str, NULL, false);
        if (ret != SL_STATUS_OK) {
          // Not a valid level value
          ret = SL_STATUS_INVALID_TYPE;
          goto cleanup;
        }
      }

      trace_level_add_entry(trace_config, &group_count, group_id, trace_level);
    }
    trace_config_string = strtok(NULL, ";");
  }

  ret = sl_wisun_br_set_trace_level(group_count, trace_config);
  if (ret != SL_STATUS_OK) {
    goto cleanup;
  }

cleanup:
  sl_free(trace_config);
  if (ret == SL_STATUS_OK) {
    printf("[Set %d trace groups]\r\n", group_count);
  } else {
    printf("[Error when setting trace level: %lu]\r\n", ret);
  }

  app_wisun_cli_mutex_unlock();
}

void app_set_unicast_tx_mode(sl_cli_command_arg_t *arguments)
{
  sl_status_t ret;
  uint8_t mode;

  app_wisun_cli_mutex_lock();

  mode = sl_cli_get_argument_uint8(arguments, 0);

  ret = sl_wisun_br_set_unicast_tx_mode(mode);

  if (ret == SL_STATUS_OK) {
    printf("[Unicast Tx mode set to %hu suceeded]\r\n", mode);
  } else {
    printf("[Failed: unable to set unicast Tx mode: %lu]\r\n", ret);
  }

  app_wisun_cli_mutex_unlock();
}

void app_reset_statistics(sl_cli_command_arg_t *arguments)
{
  sl_status_t ret;
  (void)arguments;

  app_wisun_cli_mutex_lock();

  ret = sl_wisun_br_reset_statistics(SL_WISUN_STATISTICS_TYPE_PHY);
  if (ret != SL_STATUS_OK) {
    goto cleanup;
  }

  ret = sl_wisun_br_reset_statistics(SL_WISUN_STATISTICS_TYPE_MAC);
  if (ret != SL_STATUS_OK) {
    goto cleanup;
  }

  ret = sl_wisun_br_reset_statistics(SL_WISUN_STATISTICS_TYPE_FHSS);
  if (ret != SL_STATUS_OK) {
    goto cleanup;
  }

  ret = sl_wisun_br_reset_statistics(SL_WISUN_STATISTICS_TYPE_WISUN);
  if (ret != SL_STATUS_OK) {
    goto cleanup;
  }

  ret = sl_wisun_br_reset_statistics(SL_WISUN_STATISTICS_TYPE_NETWORK);
  if (ret != SL_STATUS_OK) {
    goto cleanup;
  }

cleanup:

  if (ret == SL_STATUS_OK) {
    printf("[Statistics reset]\r\n");
  } else {
    printf("[Statistics reset failed: %lu]\r\n", ret);
  }

  app_wisun_cli_mutex_unlock();
}

void app_certificate_list(sl_cli_command_arg_t *arguments)
{
  (void)arguments;

  app_wisun_cli_mutex_lock();

  app_certificate_store_list();

  app_wisun_cli_mutex_unlock();
}

static void app_task(void *argument)
{
  (void)argument;

  printf("Wi-SUN Border Router CLI Application\r\n");

  sl_wisun_br_set_pti(app_settings_app.pti_state);

  border_router_init();

  if (app_settings_app.autostart) {
    app_start(app_settings_wisun.phy_config_type);
  }
}

void app_init(void)
{
  osThreadAttr_t app_task_attribute = {
    "App Task",
    osThreadDetached,
    NULL,
    0,
    NULL,
    (APP_TASK_STACK_SIZE * sizeof(void *)) & 0xFFFFFFF8u,
    APP_TASK_PRIORITY,
    0,
    0
  };

  app_task_id = osThreadNew(app_task, NULL, &app_task_attribute);
  assert(app_task_id != 0);
}

void sl_wisun_br_on_event(sl_wisun_br_evt_t *evt)
{
  sl_status_t result;
  char mac_str[24];

  app_wisun_cli_mutex_lock();

  switch (evt->header.id) {
    case SL_WISUN_BR_MSG_MODE_SWITCH_FALLBACK_IND_ID:
      result = app_util_get_mac_address_string(mac_str, &evt->evt.mode_switch_fallback.address);
      printf ("[mode switch fallback for %s !!]", result == SL_STATUS_OK ? mac_str : "invalid address");
      break;
    default:
      printf("[Unknown event: %d]\r\n", evt->header.id);
  }

  app_wisun_cli_mutex_unlock();
}