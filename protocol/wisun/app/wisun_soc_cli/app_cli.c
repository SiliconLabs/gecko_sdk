/***************************************************************************//**
 * @file app_cli.c
 * @brief Application CLI handler
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
#include "sl_malloc.h"
#include <assert.h>
#include <cmsis_os2.h>
#include "sl_cli.h"
#include "sl_wisun_ip6string.h"
#include "sl_sleeptimer.h"
#include "sl_wisun_test_certificates.h"
#include "sl_slist.h"
#include "app_settings.h"
#include "sl_wisun_rf_test.h"
#include "sl_wisun_cli_core.h"
#include "sl_wisun_api.h"
#include "sl_wisun_trace_api.h"
#include "sl_wisun_cli_core.h"
#include "sl_wisun_version.h"
#include "rail_features.h"
#include "socket/socket.h"

#ifdef SL_CATALOG_POWER_MANAGER_PRESENT
#include "sl_power_manager.h"
#endif

#ifdef WISUN_FAN_CERTIFICATION
#include "sl_wisun_alliance_certificates.h"
#endif

#if defined __ICCARM__
#define htonl(x) (__REV(x))
#define htons(x) (__REV16(x))
#define ntohl(x) (__REV(x))
#define ntohs(x) (__REV16(x))
#elif defined __GNUC__
#include <machine/endian.h>
#define	htonl(x) __htonl(x)
#define	htons(x) __htons(x)
#define	ntohl(x) __ntohl(x)
#define	ntohs(x) __ntohs(x)
#else
#error "Toolchain undefined"
#endif

#if defined(SL_CATALOG_MICRIUMOS_KERNEL_PRESENT)
#include "os.h"
#endif
#if defined(SL_CATALOG_FREERTOS_KERNEL_PRESENT)
#include "FreeRTOS.h"
#include "task.h"
#endif

#define APP_TASK_PRIORITY osPriorityLow3 // Lowest priority in the system for all CLI related task
#define APP_TASK_STACK_SIZE 500 // in units of CPU_INT32U

#define APP_ICMPV6_TYPE_ECHO_REQUEST 128
#define APP_ICMPV6_TYPE_ECHO_RESPONSE 129
#define APP_ICMPV6_CODE_ECHO_REQUEST 0
#define APP_ICMPV6_CODE_ECHO_RESPONSE 0
#define APP_ICMPV6_PORT 0

SL_PACK_START(1)
typedef struct {
  uint8_t type;
  uint8_t code;
  uint16_t checksum;
  uint16_t identifier;
  uint16_t sequence_number;
  uint8_t payload[];
} SL_ATTRIBUTE_PACKED app_icmpv6_echo_request_t;
SL_PACK_END()

static const app_enum_t app_socket_event_mode[] =
{
  { "indication", 0 },
  { "polling", 1 },
  { NULL, 0 }
};

static const app_enum_t app_socket_nonblock[] =
{
  { "disable", 0 },
  { "enable", 1 },
  { NULL, 0 }
};

static const app_enum_t app_remote_address_enum[] =
{
  { "br", SL_WISUN_IP_ADDRESS_TYPE_BORDER_ROUTER },
  { "border_router", SL_WISUN_IP_ADDRESS_TYPE_BORDER_ROUTER },
  { "p1", SL_WISUN_IP_ADDRESS_TYPE_PRIMARY_PARENT },
  { "parent1", SL_WISUN_IP_ADDRESS_TYPE_PRIMARY_PARENT },
  { "p2", SL_WISUN_IP_ADDRESS_TYPE_SECONDARY_PARENT },
  { "parent2", SL_WISUN_IP_ADDRESS_TYPE_SECONDARY_PARENT },
  { NULL, 0 }
};

static const app_enum_t app_mac_enum[] =
{
  { "all", 0 },
  { "any", 0 },
  { NULL, 0 }
};

static const app_enum_t app_regulation_tx_level_enum[] =
{
  { "low", SL_WISUN_REGULATION_TX_LEVEL_LOW },
  { "warning", SL_WISUN_REGULATION_TX_LEVEL_WARNING },
  { "alert", SL_WISUN_REGULATION_TX_LEVEL_ALERT },
  { NULL, 0 }
};

static const app_enum_t app_frame_type_enum[] = {
  { "pas", SL_WISUN_FRAME_TYPE_PAS },
  { "pa", SL_WISUN_FRAME_TYPE_PA },
  { "pcs", SL_WISUN_FRAME_TYPE_PCS },
  { "pc", SL_WISUN_FRAME_TYPE_PC },
  { "dis", SL_WISUN_FRAME_TYPE_DIS },
  { "dio", SL_WISUN_FRAME_TYPE_DIO },
  { NULL, 0 }
};

typedef sl_status_t (*app_socket_option_handler)(sl_wisun_socket_option_data_t *option_data,
                                                 const char *option_data_str);

static sl_status_t app_socket_event_mode_handler(sl_wisun_socket_option_data_t *option_data,
                                                 const char *option_data_str);

static sl_status_t app_socket_multicast_group_handler(sl_wisun_socket_option_data_t *option_data,
                                                      const char *option_data_str);

static sl_status_t app_socket_nonblocking_mode_handler(sl_wisun_socket_option_data_t *option_data,
                                                       const char *option_data_str);

static sl_status_t app_socket_send_buffer_limit_handler (sl_wisun_socket_option_data_t *option_data,
                                                         const char *option_data_str);

static sl_status_t app_get_ip_address(in6_addr_t *value,
                                      const char *value_str);

static const char* app_get_ip_address_str(const in6_addr_t *value);

typedef struct
{
  char *option;
  uint32_t option_name;
  uint32_t option_level;
  uint32_t option_lenght;
  app_socket_option_handler handler;
} app_socket_option_t;

static const app_socket_option_t app_set_socket_options[] =
{
  { "event_mode", SOCKET_EVENT_MODE, APP_LEVEL_SOCKET, sizeof(uint32_t), app_socket_event_mode_handler },
  { "blocking_mode", SO_NONBLOCK, APP_LEVEL_SOCKET, sizeof(uint32_t), app_socket_nonblocking_mode_handler },
  { "join_multicast_group", IPV6_JOIN_GROUP, IPPROTO_IPV6, sizeof(in6_addr_t), app_socket_multicast_group_handler },
  { "leave_multicast_group", IPV6_LEAVE_GROUP, IPPROTO_IPV6, sizeof(in6_addr_t), app_socket_multicast_group_handler },
  { "send_buffer_limit", SO_SNDBUF, SOL_SOCKET, sizeof(int32_t),app_socket_send_buffer_limit_handler },
  { NULL, 0, 0, 0, NULL }
};

static const app_socket_option_t app_get_socket_options[] =
{
  { "receive_buff_size", SO_RCVBUF, SOL_SOCKET, sizeof(int32_t),NULL },
  { "send_buff_size", SO_SNDBUF, SOL_SOCKET,sizeof(int32_t), NULL },
  { "unicast_hops", IPV6_UNICAST_HOPS, IPPROTO_IPV6, sizeof(int16_t), NULL },
  { "multicast_hops", IPV6_MULTICAST_HOPS, IPPROTO_IPV6, sizeof(int16_t), NULL },
  { NULL, 0, 0, 0, NULL }
};

typedef app_icmpv6_echo_request_t app_icmpv6_echo_response_t;

static sl_wisun_socket_id_t app_ping_socket_id = SOCKET_INVALID_ID;
static uint32_t app_ping_tick_count;

static const in6_addr_t APP_IN6ADDR_ANY = { 0 };

static const sl_wisun_mac_address_t APP_BROADCAST_MAC =
{
  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }
};

const char * const APP_SOCKET_TYPE_STR[] =
{
  "UDP client",
  "UDP server",
  "TCP client",
  "TCP server"
};

const char * const APP_SOCKET_STATE_STR[] =
{
  "ACTIVE",
  "LISTENING",
  "CONNECTING",
  "CLOSING"
};

typedef enum
{
  APP_CONNECTION_STATE_NOT_CONNECTED,
  APP_CONNECTION_STATE_CONNECTING,
  APP_CONNECTION_STATE_CONNECTED
} app_connection_state_t;

typedef enum {
  APP_SOCKET_TYPE_UDP_CLIENT,
  APP_SOCKET_TYPE_UDP_SERVER,
  APP_SOCKET_TYPE_TCP_CLIENT,
  APP_SOCKET_TYPE_TCP_SERVER
} app_socket_type_t;

typedef enum {
  APP_SOCKET_STATE_ACTIVE,
  APP_SOCKET_STATE_LISTENING,
  APP_SOCKET_STATE_CONNECTING,
  APP_SOCKET_STATE_CLOSING
} app_socket_state_t;

typedef struct
{
  sl_slist_node_t node;
  sl_wisun_socket_id_t socket_id;
  app_socket_type_t socket_type;
  app_socket_state_t socket_state;
  in6_addr_t remote_address;
  uint16_t remote_port;
} app_socket_entry_t;

#define APP_MAX_SOCKET_ENTRIES 10
static sl_slist_node_t *app_socket_entry_list_free;
static sl_slist_node_t *app_socket_entry_list;
static app_socket_entry_t app_socket_entries[APP_MAX_SOCKET_ENTRIES];
static app_connection_state_t app_connection_state;
static uint32_t app_connection_tick_count;

#ifdef SL_CATALOG_POWER_MANAGER_PRESENT
#define EM_EVENT_MASK_ALL  (SL_POWER_MANAGER_EVENT_TRANSITION_ENTERING_EM0   \
                            | SL_POWER_MANAGER_EVENT_TRANSITION_LEAVING_EM0  \
                            | SL_POWER_MANAGER_EVENT_TRANSITION_ENTERING_EM1 \
                            | SL_POWER_MANAGER_EVENT_TRANSITION_LEAVING_EM1  \
                            | SL_POWER_MANAGER_EVENT_TRANSITION_ENTERING_EM2 \
                            | SL_POWER_MANAGER_EVENT_TRANSITION_LEAVING_EM2  \
                            | SL_POWER_MANAGER_EVENT_TRANSITION_ENTERING_EM3 \
                            | SL_POWER_MANAGER_EVENT_TRANSITION_LEAVING_EM3)

void lfn_em_cb(sl_power_manager_em_t from, sl_power_manager_em_t to)
{
  static uint32_t em_start_tick[EM_MAX + 1] = {0};
  uint32_t em_switch_tick = sl_sleeptimer_get_tick_count();

  em_start_tick[to] = em_switch_tick;
  lfn_em_time_ms[from] += sl_sleeptimer_tick_to_ms(em_switch_tick - em_start_tick[from]);
}

static sl_power_manager_em_transition_event_handle_t lfn_em_handle;
static const sl_power_manager_em_transition_event_info_t lfn_em_info = {
  .event_mask = EM_EVENT_MASK_ALL,
  .on_event = lfn_em_cb,
};
#endif

#if RAIL_IEEE802154_SUPPORTS_G_MODESWITCH
static uint8_t op_mode_to_phy_mode_id(uint8_t op_mode)
{
  uint8_t phy_mode_id;
  switch(op_mode) {
    case 0x1a:
      phy_mode_id = 1;
      break;
    case 0x1b:
      phy_mode_id = 2;
      break;
    case 0x2:
      phy_mode_id = 3;
      break;
    case 0x2b:
      phy_mode_id = 4;
      break;
    case 0x3:
      phy_mode_id = 5;
      break;
    case 0x4a:
      phy_mode_id = 6;
      break;
    case 0x4b:
      phy_mode_id = 7;
      break;
    case 0x5:
      phy_mode_id = 8;
      break;
    default:
      printf("[Invalid operating_mode!\r\n]");
      phy_mode_id = 255;
  }

  return phy_mode_id;
}

// return base PhyModeId
static uint8_t find_base_operating_mode(void)
{
  if (app_settings_wisun.phy_config_type == SL_WISUN_PHY_CONFIG_FAN10) {
    return op_mode_to_phy_mode_id(app_settings_wisun.operating_mode);
  } else {
    return app_settings_wisun.phy_mode_id;
  }
}

static bool check_base_operating_mode_in_pom_ie(uint8_t phy_mode_id_count, const uint8_t *phy_mode_ids)
{
  uint8_t base_mode = find_base_operating_mode();
  uint8_t i;
  bool found = false;

  if (base_mode != 255) {
    for (i = 0; i < phy_mode_id_count; i++) {
      if (phy_mode_ids[i] == base_mode) {
        found = true;
        break;
      }
    }
  }

  return found;
}

static void add_base_operating_mode_in_pom_ie(uint8_t *phy_mode_id_count_p, uint8_t *phy_mode_id_p)
{
  uint8_t base_mode = find_base_operating_mode();

  if (base_mode != 255) {
    uint8_t temp_phy_mode_ids[15];
    uint8_t nb;

    // Save previous POM-IE
    memcpy(temp_phy_mode_ids, phy_mode_id_p, *phy_mode_id_count_p);

    // Add base mode first
    phy_mode_id_p[0] = base_mode;

    // Restore other modes. Remove last one if POM-IE is full.
    nb = *phy_mode_id_count_p < 15 ? *phy_mode_id_count_p : 14;
    memcpy(&phy_mode_id_p[1], temp_phy_mode_ids, nb);

    *phy_mode_id_count_p = nb + 1;
  }
}
#endif

static app_socket_entry_t *app_socket_alloc_entry()
{
  sl_slist_node_t *item;
  app_socket_entry_t *entry = NULL;

  item = sl_slist_pop(&app_socket_entry_list_free);
  if (item) {
    entry = SL_SLIST_ENTRY(item, app_socket_entry_t, node);
    memset(entry, 0, sizeof(app_socket_entry_t));
    entry->socket_id = SOCKET_INVALID_ID;
  }

  return entry;
}

static void app_socket_free_entry(app_socket_entry_t *entry)
{
  if (!entry) {
    return;
  }

  // Remove the entry from the active entries list
  sl_slist_remove(&app_socket_entry_list, &entry->node);

  // Push the entry to the free entries list
  sl_slist_push(&app_socket_entry_list_free, &entry->node);
}

static app_socket_entry_t *app_socket_entry(sl_wisun_socket_id_t socket_id)
{
  app_socket_entry_t *entry = NULL;

  SL_SLIST_FOR_EACH_ENTRY(app_socket_entry_list, entry, app_socket_entry_t, node) {
    if (entry->socket_id == socket_id) {
      return entry;
    }
  }

  return NULL;
}

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

static void app_join(sl_wisun_phy_config_type_t phy_config_type);

static void app_cli_task(void *argument)
{
  sl_status_t ret;
  (void)argument;

  ret = sl_wisun_set_regulation_tx_thresholds(app_settings_wisun.regulation_warning_threshold,
                                              app_settings_wisun.regulation_alert_threshold);
  if (ret != SL_STATUS_OK) {
    printf("[Failed: unable to set regulation TX thresholds: %lu]\r\n", ret);
  }

  if (app_settings_app.autoconnect) {
    app_join((sl_wisun_phy_config_type_t)app_settings_wisun.phy_config_type);
  }

  osThreadExit();
}

void app_cli_init(void)
{
  int i;
  osThreadId_t app_task_id;

  printf("Wi-SUN CLI Application\r\n");

  // Initialize socket entry lists
  sl_slist_init(&app_socket_entry_list_free);
  sl_slist_init(&app_socket_entry_list);

  for (i = 0; i < APP_MAX_SOCKET_ENTRIES; ++i) {
    sl_slist_push(&app_socket_entry_list_free, &app_socket_entries[i].node);
  }

#ifdef SL_CATALOG_POWER_MANAGER_PRESENT
  sl_power_manager_subscribe_em_transition_event(&lfn_em_handle, &lfn_em_info);
#endif

  const osThreadAttr_t app_task_attribute = {
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

  app_task_id = osThreadNew(app_cli_task, NULL, &app_task_attribute);
  assert(app_task_id != 0);
}

void app_about(void)
{
  printf("Wi-SUN CLI Application\r\n");
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

static void app_handle_network_update_ind(sl_wisun_evt_t *evt)
{
  sl_status_t ret;
  in6_addr_t address;

  if (evt->evt.network_update.status == SL_STATUS_OK) {
    printf("[Network update]\r\n");

    if (evt->evt.network_update.flags & (1 << SL_WISUN_NETWORK_UPDATE_FLAGS_GLOBAL_IP)) {
      ret = sl_wisun_get_ip_address(SL_WISUN_IP_ADDRESS_TYPE_GLOBAL, &address);
      if (ret == SL_STATUS_OK) {
        printf("[Global IPv6 address updated: %s]\r\n", app_get_ip_address_str(&address));
      } else {
        printf("[Global IPv6 address not available]\r\n");
      }
    }

    if (evt->evt.network_update.flags & (1 << SL_WISUN_NETWORK_UPDATE_FLAGS_PRIMARY_PARENT)) {
      ret = sl_wisun_get_ip_address(SL_WISUN_IP_ADDRESS_TYPE_PRIMARY_PARENT, &address);
      if (ret == SL_STATUS_OK) {
        printf("[Primary parent updated: %s]\r\n", app_get_ip_address_str(&address));
      } else {
        printf("[Primary parent removed]\r\n");
      }
    }

    if (evt->evt.network_update.flags & (1 << SL_WISUN_NETWORK_UPDATE_FLAGS_SECONDARY_PARENT)) {
      ret = sl_wisun_get_ip_address(SL_WISUN_IP_ADDRESS_TYPE_SECONDARY_PARENT, &address);
      if (ret == SL_STATUS_OK) {
        printf("[Secondary parent updated: %s]\r\n", app_get_ip_address_str(&address));
      } else {
        printf("[Secondary parent removed]\r\n");
      }
    }
  }
}

static void app_handle_connected_ind(sl_wisun_evt_t *evt)
{
  sl_status_t ret;
  uint32_t tick_count, time_ms;
  in6_addr_t address;

  tick_count = sl_sleeptimer_get_tick_count();
  time_ms = sl_sleeptimer_tick_to_ms(tick_count - app_connection_tick_count);

  if (evt->evt.connected.status == SL_STATUS_OK) {
    app_connection_state = APP_CONNECTION_STATE_CONNECTED;
    printf("[Connected: %lu s]\r\n", time_ms / 1000);
    ret = sl_wisun_get_ip_address(SL_WISUN_IP_ADDRESS_TYPE_GLOBAL, &address);
    if (ret == SL_STATUS_OK) {
      printf("[IPv6 address: %s]\r\n", app_get_ip_address_str(&address));
    } else {
      printf("[IPv6 address not available]\r\n");
    }
  } else {
    app_connection_state = APP_CONNECTION_STATE_NOT_CONNECTED;
    printf("[Connection failed: %lu]\r\n", evt->evt.connected.status);
  }
}

static void app_handle_ping_socket_data(sl_wisun_evt_t *evt)
{
  app_icmpv6_echo_response_t *packet;
  uint32_t tick_count, time_ms;

  packet = (app_icmpv6_echo_response_t *)evt->evt.socket_data.data;

  if (packet->type != APP_ICMPV6_TYPE_ECHO_RESPONSE) {
    printf("unexpected ICMP message type: %hu\r\n", packet->type);
    return;
  }

  tick_count = sl_sleeptimer_get_tick_count();
  time_ms = sl_sleeptimer_tick_to_ms(tick_count - app_ping_tick_count);

  printf("%u bytes from %s: icmp_seq=%u time=%lu ms\r\n",
         evt->evt.socket_data.data_length,
         app_get_ip_address_str(&evt->evt.socket_data.remote_address),
         htons(packet->sequence_number),
         time_ms);
}

static void app_handle_socket_data(sl_wisun_evt_t *evt)
{
  app_printable_data_ctx_t printable_data_ctx;
  char *printable_data;

  printf("[Data from %s (%u): %lu,%u",
         app_get_ip_address_str(&evt->evt.socket_data.remote_address),
         evt->evt.socket_data.remote_port,
         evt->evt.socket_data.socket_id, evt->evt.socket_data.data_length);
  if (app_settings_app.printable_data_length) {
    printable_data = app_util_printable_data_init(&printable_data_ctx,
                                                  evt->evt.socket_data.data,
                                                  evt->evt.socket_data.data_length,
                                                  app_settings_app.printable_data_as_hex,
                                                  app_settings_app.printable_data_length);
    while (printable_data) {
      printf("\r\n%s", printable_data);
      printable_data = app_util_printable_data_next(&printable_data_ctx);
    }
  }
  printf("]\r\n");
}

static void app_handle_socket_data_ind(sl_wisun_evt_t *evt)
{
  if (evt->evt.socket_data.socket_id == app_ping_socket_id) {
    app_handle_ping_socket_data(evt);
  } else {
    app_handle_socket_data(evt);
  }
}

static void app_handle_socket_data_available_ind(sl_wisun_evt_t *evt)
{
  printf("[Data available: %lu,%u]\r\n",
         evt->evt.socket_data_available.socket_id,
         evt->evt.socket_data_available.data_length);
}

static void app_handle_socket_connected_ind(sl_wisun_evt_t *evt)
{
  app_socket_entry_t *entry;

  entry = app_socket_entry(evt->evt.socket_connected.socket_id);
  if (!entry) {
    printf("[Failed: unable to find the specified socket: %lu]\r\n",
           evt->evt.socket_connected.socket_id);
    return;
  }

  if (evt->evt.socket_connected.status == SL_STATUS_OK) {
    entry->socket_state = APP_SOCKET_STATE_ACTIVE;
    printf("[Opened: %lu]\r\n", evt->evt.socket_connected.socket_id);
  } else {
    close(entry->socket_id);
    app_socket_free_entry(entry);
    printf("[Open failed: %lu]\r\n", evt->evt.socket_connected.status);
  }
}

static void app_handle_socket_connection_available_ind(sl_wisun_evt_t *evt)
{
  app_socket_entry_t *entry;
  sockaddr_in6_t ipv6_remote_addr;

  uint32_t addr_length = sizeof(sockaddr_in6_t);

  printf("[Socket connection available: %lu]\r\n",
         evt->evt.socket_connection_available.socket_id);

  entry = app_socket_alloc_entry();
  if (!entry) {
    printf("[Failed: unable to allocate a socket entry]\r\n");
    return;
  }

  entry->socket_type = APP_SOCKET_TYPE_TCP_CLIENT;
  entry->socket_state = APP_SOCKET_STATE_ACTIVE;

  entry->socket_id = accept(evt->evt.socket_connection_available.socket_id,
                            (struct sockaddr *) &ipv6_remote_addr,
                            &addr_length);

  if (entry->socket_id == SOCKET_INVALID_ID  || addr_length != sizeof(sockaddr_in6_t)) {
    printf("[Failed: unable to accept a connection]\r\n");
    return;
  }

  entry->remote_port = ipv6_remote_addr.sin6_port;
  memcpy(entry->remote_address.address, &ipv6_remote_addr.sin6_addr.address, IPV6_ADDR_SIZE);

  // Push the entry to the active entries list
  sl_slist_push_back(&app_socket_entry_list, &entry->node);

  printf("[Accepted %s (%u): %lu]\r\n", app_get_ip_address_str(&entry->remote_address),
    entry->remote_port, entry->socket_id);
}

static void app_handle_socket_closing_ind(sl_wisun_evt_t *evt)
{
  app_socket_entry_t *entry;

  entry = app_socket_entry(evt->evt.socket_closing.socket_id);
  if (!entry) {
    printf("[Failed: unable to find the specified socket: %lu]\r\n",
           evt->evt.socket_closing.socket_id);
    return;
  }

  entry->socket_state = APP_SOCKET_STATE_CLOSING;

  printf("[Closing: %lu]\r\n", evt->evt.socket_closing.socket_id);
}

static void app_handle_disconnected_ind(sl_wisun_evt_t *evt)
{
  (void)evt;

  app_connection_state = APP_CONNECTION_STATE_NOT_CONNECTED;

  printf("[Disconnected]\r\n");
}

static void app_handle_connection_lost_ind(sl_wisun_evt_t *evt)
{
  (void)evt;

  app_connection_state = APP_CONNECTION_STATE_CONNECTING;

  printf("[Connection lost, connecting to \"%s\"]\r\n", app_settings_wisun.network_name);
}

static void app_handle_socket_data_sent(sl_wisun_evt_t *evt)
{
  app_socket_entry_t *entry;

  entry = app_socket_entry(evt->evt.socket_data_sent.socket_id);
  if (!entry) {
    printf("[Failed: unable to find the specified socket: %lu]\r\n",
           evt->evt.socket_data_sent.socket_id);
    return;
  }

  if (evt->evt.socket_data_sent.status == SL_STATUS_OK) {
    printf("[Data sent: %lu,%lu]\r\n", evt->evt.socket_data_sent.socket_id, evt->evt.socket_data_sent.socket_space_left);
  } else {
    printf("[Failed: data sent, error %lu (socket %lu)]\r\n", evt->evt.socket_data_sent.status, evt->evt.socket_data_sent.socket_id);
  }
}

static void app_handle_socket_data_sent_ind(sl_wisun_evt_t *evt)
{
  // Handle socket data sent indications only for UDP and TCP sockets.
  if (evt->evt.socket_data_sent.socket_id != app_ping_socket_id) {
    app_handle_socket_data_sent(evt);
  }
}

static void app_handle_join_state_ind(sl_wisun_evt_t *evt)
{
  const app_enum_t *ptr;

  if (app_settings_wisun.device_type == SL_WISUN_LFN) {
    ptr = app_util_get_enum_by_integer(app_settings_wisun_join_state_enum_lfn, evt->evt.join_state.join_state);
  } else {
    ptr = app_util_get_enum_by_integer(app_settings_wisun_join_state_enum_ffn, evt->evt.join_state.join_state);
  }

  if (ptr) {
    printf("[%s]\r\n", ptr->value_str);
  }
}

static void app_handle_regulation_tx_level_ind(sl_wisun_evt_t *evt)
{
  const app_enum_t *ptr;

  ptr = app_util_get_enum_by_integer(app_regulation_tx_level_enum,
                                     evt->evt.regulation_tx_level.tx_level);
  if (ptr) {
    printf("[Regulation TX level: %s (%lu) (%lu ms)]\r\n", ptr->value_str, ptr->value, evt->evt.regulation_tx_level.tx_duration_ms);
  }
}

static void app_handle_lfn_wake_up_ind(sl_wisun_evt_t *evt)
{
  (void)evt;
  //printf("[LFN Wake-up for %lu us, next in %"PRIu64" us]\r\n", evt->evt.lfn_wake_up.wup_duration_us, evt->evt.lfn_wake_up.next_wup_us);
}

static void app_handle_lfn_multicast_reg_ind(sl_wisun_evt_t *evt)
{
  char ipv6_string[40];

  ip6tos(&evt->evt.lfn_multicast_reg.ip_address.address, ipv6_string);

  if (evt->evt.lfn_multicast_reg.status == SL_STATUS_OK) {
    printf("[LFN multicast group registration %s succeeded]\r\n", ipv6_string);
  } else {
    printf("[LFN multicast group registration %s fails]\r\n", ipv6_string);
  }
}

void sl_wisun_on_event(sl_wisun_evt_t *evt)
{
  sl_status_t result;
  char mac_str[24];

  app_wisun_cli_mutex_lock();

  switch (evt->header.id) {
    case SL_WISUN_MSG_NETWORK_UPDATE_IND_ID:
     app_handle_network_update_ind(evt);
     break;
    case SL_WISUN_MSG_CONNECTED_IND_ID:
      app_handle_connected_ind(evt);
      break;
    case SL_WISUN_MSG_SOCKET_DATA_IND_ID:
      app_handle_socket_data_ind(evt);
      break;
    case SL_WISUN_MSG_SOCKET_DATA_AVAILABLE_IND_ID:
      app_handle_socket_data_available_ind(evt);
      break;
    case SL_WISUN_MSG_SOCKET_CONNECTED_IND_ID:
      app_handle_socket_connected_ind(evt);
      break;
    case SL_WISUN_MSG_SOCKET_CONNECTION_AVAILABLE_IND_ID:
      app_handle_socket_connection_available_ind(evt);
      break;
    case SL_WISUN_MSG_SOCKET_CLOSING_IND_ID:
      app_handle_socket_closing_ind(evt);
      break;
    case SL_WISUN_MSG_DISCONNECTED_IND_ID:
      app_handle_disconnected_ind(evt);
      break;
    case SL_WISUN_MSG_CONNECTION_LOST_IND_ID:
      app_handle_connection_lost_ind(evt);
      break;
    case SL_WISUN_MSG_SOCKET_DATA_SENT_IND_ID:
      app_handle_socket_data_sent_ind(evt);
      break;
    case SL_WISUN_MSG_JOIN_STATE_IND_ID:
      app_handle_join_state_ind(evt);
      break;
    case SL_WISUN_MSG_REGULATION_TX_LEVEL_IND_ID:
      app_handle_regulation_tx_level_ind(evt);
      break;
    case SL_WISUN_MSG_MODE_SWITCH_FALLBACK_IND_ID:
      result = app_util_get_mac_address_string(mac_str, &evt->evt.mode_switch_fallback.address);
      printf ("[mode switch fallback for %s!!]\r\n", result == SL_STATUS_OK ? mac_str : "invalid address");
      break;
    case SL_WISUN_MSG_LFN_WAKE_UP_IND_ID:
      app_handle_lfn_wake_up_ind(evt);
      break;
    case SL_WISUN_MSG_LFN_MULTICAST_REG_IND_ID:
      app_handle_lfn_multicast_reg_ind(evt);
      break;
    default:
      printf("[Unknown event: %d]\r\n", evt->header.id);
  }

  app_wisun_cli_mutex_unlock();
}

static sl_status_t channel_spacing_khz_to_id(uint32_t channel_spacing_khz, uint8_t *channel_spacing_id)
{
  sl_status_t result = SL_STATUS_OK;

  switch (channel_spacing_khz) {
    case 100:
      *channel_spacing_id = SL_WISUN_CHANNEL_SPACING_100KHZ;
      break;
    case 200:
      *channel_spacing_id = SL_WISUN_CHANNEL_SPACING_200KHZ;
      break;
    case 250:
      *channel_spacing_id = SL_WISUN_CHANNEL_SPACING_250KHZ;
      break;
    case 400:
      *channel_spacing_id = SL_WISUN_CHANNEL_SPACING_400KHZ;
      break;
    case 600:
      *channel_spacing_id = SL_WISUN_CHANNEL_SPACING_600KHZ;
      break;
    case 800:
      *channel_spacing_id = SL_WISUN_CHANNEL_SPACING_800KHZ;
      break;
    case 1200:
      *channel_spacing_id = SL_WISUN_CHANNEL_SPACING_1200KHZ;
      break;
    default:
      result = SL_STATUS_FAIL;
  }

  return result;
}

static void app_join(sl_wisun_phy_config_type_t phy_config_type)
{
  sl_status_t ret;
  const uint8_t *root_certificate;
  const uint8_t *client_certificate;
  const uint8_t *client_key;
  sl_wisun_channel_mask_t channel_mask;
  sl_wisun_phy_config_t phy_config;
  sl_wisun_connection_params_t params;
  sl_wisun_lfn_params_t lfn_params;
  uint8_t phy_mode_id_count, is_mdr_command_capable;
  uint8_t phy_mode_id[SL_WISUN_MAX_PHY_MODE_ID_COUNT];
  uint8_t *phy_mode_id_p, *phy_mode_id_count_p;
  uint8_t channel_spacing_id;
#if RAIL_IEEE802154_SUPPORTS_G_MODESWITCH
  bool set_pom_ie = false;
#endif

  app_wisun_cli_mutex_lock();

  if (app_connection_state != APP_CONNECTION_STATE_NOT_CONNECTED) {
    printf("[Failed: already connecting or connected]\r\n");
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
        phy_config.config.explicit_plan.ch0_frequency_khz = app_settings_wisun.ch0_frequency;
        phy_config.config.explicit_plan.number_of_channels = app_settings_wisun.number_of_channels;

        if (channel_spacing_khz_to_id(app_settings_wisun.channel_spacing, &channel_spacing_id) != SL_STATUS_OK) {
          printf("[Invalid channel spacing\r\n]");
          goto cleanup;
        }

        phy_config.config.explicit_plan.channel_spacing = channel_spacing_id;
        phy_config.config.explicit_plan.phy_mode_id = app_settings_wisun.phy_mode_id;
        break;
      case SL_WISUN_PHY_CONFIG_IDS:
        phy_config.config.ids.protocol_id  = app_settings_wisun.protocol_id;
        phy_config.config.ids.channel_id   = app_settings_wisun.channel_id;
        phy_config.config.ids.phy_mode_id  = app_settings_wisun.phy_mode_id;
        break;
      case SL_WISUN_PHY_CONFIG_CUSTOM_FSK:
        phy_config.config.custom_fsk.ch0_frequency_khz = app_settings_wisun.ch0_frequency;
        phy_config.config.custom_fsk.number_of_channels = app_settings_wisun.number_of_channels;
        phy_config.config.custom_fsk.channel_spacing_khz = app_settings_wisun.channel_spacing;
        phy_config.config.custom_fsk.phy_mode_id = app_settings_wisun.phy_mode_id;
        phy_config.config.custom_fsk.crc_type = app_settings_wisun.crc_type;
        phy_config.config.custom_fsk.preamble_length = app_settings_wisun.preamble_length;
        break;
      case SL_WISUN_PHY_CONFIG_CUSTOM_OFDM:
        phy_config.config.custom_ofdm.ch0_frequency_khz = app_settings_wisun.ch0_frequency;
        phy_config.config.custom_ofdm.number_of_channels = app_settings_wisun.number_of_channels;
        phy_config.config.custom_ofdm.channel_spacing_khz = app_settings_wisun.channel_spacing;
        phy_config.config.custom_ofdm.phy_mode_id = app_settings_wisun.phy_mode_id;
        phy_config.config.custom_ofdm.crc_type = app_settings_wisun.crc_type;
        phy_config.config.custom_ofdm.stf_length = app_settings_wisun.stf_length;
        break;
      case SL_WISUN_PHY_CONFIG_CUSTOM_OQPSK:
        phy_config.config.custom_oqpsk.ch0_frequency_khz = app_settings_wisun.ch0_frequency;
        phy_config.config.custom_oqpsk.number_of_channels = app_settings_wisun.number_of_channels;
        phy_config.config.custom_oqpsk.channel_spacing_khz = app_settings_wisun.channel_spacing;
        phy_config.config.custom_oqpsk.phy_mode_id = app_settings_wisun.phy_mode_id;
        phy_config.config.custom_oqpsk.crc_type = app_settings_wisun.crc_type;
        phy_config.config.custom_oqpsk.preamble_length = app_settings_wisun.preamble_length;
        break;
      default:
        printf("[Failed: unsupported PHY configuration type: %u]\r\n", phy_config_type);
        goto cleanup;
  }

  app_settings_wisun.phy_config_type = phy_config.type = phy_config_type;

  ret = sl_wisun_set_device_type((sl_wisun_device_type_t)app_settings_wisun.device_type);
  if (ret != SL_STATUS_OK) {
    printf("[Failed: unable to set device type: %lu]\r\n", ret);
    goto cleanup;
  }

  switch (app_settings_wisun.network_size) {
    case SL_WISUN_NETWORK_SIZE_SMALL:
      params = SL_WISUN_PARAMS_PROFILE_SMALL;
      break;
    case SL_WISUN_NETWORK_SIZE_MEDIUM:
      params = SL_WISUN_PARAMS_PROFILE_MEDIUM;
      break;
    case SL_WISUN_NETWORK_SIZE_LARGE:
      params = SL_WISUN_PARAMS_PROFILE_LARGE;
      break;
    case SL_WISUN_NETWORK_SIZE_TEST:
      params = SL_WISUN_PARAMS_PROFILE_TEST;
      break;
    case SL_WISUN_NETWORK_SIZE_CERTIFICATION:
      params = SL_WISUN_PARAMS_PROFILE_CERTIF;
      break;
    default:
      printf("[Failed: unsupported network size]\r\n");
      goto cleanup;
  }
  ret = sl_wisun_set_connection_parameters(&params);

  if (ret != SL_STATUS_OK) {
    printf("[Failed: unable to set network size: %lu]\r\n", ret);
    goto cleanup;
  }

  if (app_settings_wisun.device_type == SL_WISUN_LFN) {
    switch (app_settings_wisun.lfn_profile) {
      case SL_WISUN_LFN_PROFILE_TEST:
        lfn_params = SL_WISUN_PARAMS_LFN_TEST;
        break;
      case SL_WISUN_LFN_PROFILE_BALANCED:
        lfn_params = SL_WISUN_PARAMS_LFN_BALANCED;
        break;
      case SL_WISUN_LFN_PROFILE_ECO:
        lfn_params = SL_WISUN_PARAMS_LFN_ECO;
        break;
      default:
        printf("[Failed: unsupported LFN profile]\r\n");
        goto cleanup;
    }
    ret = sl_wisun_set_lfn_parameters(&lfn_params);
    if (ret != SL_STATUS_OK) {
      printf("[Failed: unable to set LFN parameters: %lu]\r\n", ret);
      goto cleanup;
    }
  }

  ret = sl_wisun_set_tx_power(app_settings_wisun.tx_power);
  if (ret != SL_STATUS_OK) {
    printf("[Failed: unable to set TX power: %lu]\r\n", ret);
    goto cleanup;
  }

  if (app_settings_wisun.certificate_chain == APP_CERTIFICATE_CHAIN_SILABS) {
    root_certificate = WISUN_ROOT_CERTIFICATE;
    client_certificate = WISUN_CLIENT_CERTIFICATE;
    client_key = WISUN_CLIENT_KEY;
#ifdef WISUN_FAN_CERTIFICATION
  } else if (app_settings_wisun.certificate_chain == APP_CERTIFICATE_CHAIN_CERTIF) {
    root_certificate = WISUN_ALLIANCE_ROOT_CERTIFICATE;
    client_certificate = WISUN_ALLIANCE_CLIENT_CERTIFICATE;
    client_key = WISUN_ALLIANCE_CLIENT_KEY;
#endif
  } else {
    printf("[Failed: invalid certificate chain: %u]\r\n", app_settings_wisun.certificate_chain);
    goto cleanup;
  }

  ret = sl_wisun_set_trusted_certificate(SL_WISUN_CERTIFICATE_OPTION_IS_REF,
                                         strlen((const char *)root_certificate) + 1,
                                         root_certificate);
  if (ret != SL_STATUS_OK) {
    printf("[Failed: unable to set the trusted certificate: %lu]\r\n", ret);
    goto cleanup;
  }

  ret = sl_wisun_set_device_certificate(SL_WISUN_CERTIFICATE_OPTION_IS_REF | SL_WISUN_CERTIFICATE_OPTION_HAS_KEY,
                                        strlen((const char *)client_certificate) + 1,
                                        client_certificate);
  if (ret != SL_STATUS_OK) {
    printf("[Failed: unable to set the device certificate: %lu]\r\n", ret);
    goto cleanup;
  }

  ret = sl_wisun_set_device_private_key(SL_WISUN_PRIVATE_KEY_OPTION_IS_REF,
                                        strlen((const char *)client_key) + 1,
                                        client_key);
  if (ret != SL_STATUS_OK) {
    printf("[Failed: unable to set the device private key: %lu]\r\n", ret);
    goto cleanup;
  }

  ret = app_settings_get_channel_mask(app_settings_wisun.allowed_channels, &channel_mask);
  ret = sl_wisun_set_channel_mask(&channel_mask);
  if (ret != SL_STATUS_OK) {
    printf("[Failed: unable to set channel mask: %lu]\r\n", ret);
    goto cleanup;
  }

  ret = sl_wisun_set_unicast_settings(app_settings_wisun.uc_dwell_interval_ms);
  if (ret != SL_STATUS_OK) {
    printf("[Failed: unable to set unicast settings: %lu]\r\n", ret);
    goto cleanup;
  }

  ret = sl_wisun_set_regulation((sl_wisun_regulation_t)app_settings_wisun.regulation);
  if (ret != SL_STATUS_OK) {
    printf("[Failed: unable to set regional regulation: %lu]\r\n", ret);
    goto cleanup;
  }

  ret = sl_wisun_set_pti_state(app_settings_app.pti_state);
  if (ret != SL_STATUS_OK) {
    printf("[Failed to set PTI state]\r\n");
    goto cleanup;
  }

#if SLI_WISUN_DISABLE_SECURITY
  ret = sl_wisun_set_security_state(app_security_state);
  if (ret != SL_STATUS_OK) {
    printf("[Failed to set security state %"PRIu32"]\r\n", app_security_state);
    goto cleanup;
  }
#endif

  ret = sl_wisun_join((const uint8_t *)app_settings_wisun.network_name, &phy_config);
  if (ret == SL_STATUS_OK) {
    app_connection_state = APP_CONNECTION_STATE_CONNECTING;
    app_connection_tick_count = sl_sleeptimer_get_tick_count();
    printf("[Connecting to \"%s\"]\r\n", app_settings_wisun.network_name);
  } else {
    printf("[Connection failed: %lu]\r\n", ret);
    goto cleanup;
  }

#if RAIL_IEEE802154_SUPPORTS_G_MODESWITCH
  // Configure POM-IE
  // If PhyModeIds are set by user, send them to the stack, otherwise
  // retrieve the default PhyModeIds from the stack first
  if (app_settings_wisun.rx_phy_mode_ids_count == 0) {
    // Check if default PhyList can be retrieved from device
    if (sl_wisun_get_pom_ie(&phy_mode_id_count, phy_mode_id, &is_mdr_command_capable) == SL_STATUS_OK) {
      phy_mode_id_p = phy_mode_id;
      phy_mode_id_count_p = &phy_mode_id_count;

      // Check base mode is inside POM_IE
      if (!check_base_operating_mode_in_pom_ie(phy_mode_id_count, phy_mode_id_p)) {
        add_base_operating_mode_in_pom_ie(phy_mode_id_count_p, phy_mode_id_p);
        set_pom_ie = true;
      }

      if (is_mdr_command_capable != app_settings_wisun.rx_mdr_capable) {
        set_pom_ie = true;
      }
    } else {
      // POM-IE not available
      goto cleanup;
    }
  } else {
    // Set by user
    phy_mode_id_p = app_settings_wisun.rx_phy_mode_ids;
    phy_mode_id_count_p = &app_settings_wisun.rx_phy_mode_ids_count;
    set_pom_ie = true;
  }

  if (set_pom_ie) {
    ret = sl_wisun_set_pom_ie(*phy_mode_id_count_p,
                              phy_mode_id_p,
                              app_settings_wisun.rx_mdr_capable);
    if (ret != SL_STATUS_OK) {
      printf("[Failed: unable to set RX PhyModeId list: %lu]\r\n", ret);
      goto cleanup;
    }
  }
#else
  (void)phy_mode_id_count;
  (void)is_mdr_command_capable;
  (void)phy_mode_id;
  (void)phy_mode_id_p;
  (void)phy_mode_id_count_p;
#endif

cleanup:

  app_wisun_cli_mutex_unlock();
}

void app_join_fan10(sl_cli_command_arg_t *arguments)
{
  (void)arguments;

  app_join(SL_WISUN_PHY_CONFIG_FAN10);
}

void app_join_fan11(sl_cli_command_arg_t *arguments)
{
  (void)arguments;

  app_join(SL_WISUN_PHY_CONFIG_FAN11);
}

void app_join_explicit(sl_cli_command_arg_t *arguments)
{
  (void)arguments;

  app_join(SL_WISUN_PHY_CONFIG_EXPLICIT);
}

void app_join_custom_fsk(sl_cli_command_arg_t *arguments)
{
  (void)arguments;

  app_join(SL_WISUN_PHY_CONFIG_CUSTOM_FSK);
}

void app_join_custom_ofdm(sl_cli_command_arg_t *arguments)
{
  (void)arguments;

  app_join(SL_WISUN_PHY_CONFIG_CUSTOM_OFDM);
}

void app_join_custom_oqpsk(sl_cli_command_arg_t *arguments)
{
  (void)arguments;

  app_join(SL_WISUN_PHY_CONFIG_CUSTOM_OQPSK);
}

void app_join_ids(sl_cli_command_arg_t *arguments)
{
  (void)arguments;

  app_join(SL_WISUN_PHY_CONFIG_IDS);
}

void app_disconnect(sl_cli_command_arg_t *arguments)
{
  sl_status_t ret;
  (void)arguments;

  app_wisun_cli_mutex_lock();

  if (app_connection_state == APP_CONNECTION_STATE_NOT_CONNECTED) {
    printf("[Failed: already disconnected]\r\n");
    goto cleanup;
  }

  ret = sl_wisun_disconnect();
  if (ret == SL_STATUS_OK) {
    app_connection_state = APP_CONNECTION_STATE_NOT_CONNECTED;
    printf("[Disconnecting]\r\n");
  } else {
    printf("[Disconnection failed: %lu]\r\n", ret);
  }

cleanup:

  app_wisun_cli_mutex_unlock();
}

void app_ping(sl_cli_command_arg_t *arguments)
{
  sl_status_t ret;
  char *arg_remote_address;
  app_icmpv6_echo_request_t *packet;
  uint16_t packet_data_length;
  uint8_t *packet_data = NULL;
  uint16_t payload_data_length;
  uint8_t *payload_data = NULL;
  uint32_t socket_option_value = SL_WISUN_SOCKET_EVENT_MODE_INDICATION;
  int32_t socket_retval = SOCKET_RETVAL_ERROR;
  sockaddr_in6_t dest_addr = {
    .sin6_family   = AF_INET6,
    .sin6_port     = APP_ICMPV6_PORT,
    .sin6_flowinfo = 0,
    .sin6_addr     = APP_IN6ADDR_ANY,
    .sin6_scope_id = 0
  };

  (void)arguments;

  app_wisun_cli_mutex_lock();

  arg_remote_address = sl_cli_get_argument_string(arguments, 0);
  ret = app_get_ip_address(&dest_addr.sin6_addr, arg_remote_address);
  if (ret != SL_STATUS_OK) {
    printf("[Failed: invalid remote address parameter]\r\n");
    goto cleanup;
  }

  if (app_ping_socket_id != SOCKET_INVALID_ID) {
    close(app_ping_socket_id);
    app_ping_socket_id = SOCKET_INVALID_ID;
  }

  app_ping_socket_id = socket(AF_INET6, (SOCK_RAW | SOCK_NONBLOCK), IPPROTO_ICMP);
  if (app_ping_socket_id == SOCKET_INVALID_ID) {
    printf("[Failed: unable to open a socket]\r\n");
    goto cleanup;
  }

  socket_retval = setsockopt(app_ping_socket_id,
                             APP_LEVEL_SOCKET,
                             SOCKET_EVENT_MODE,
                             &socket_option_value,
                             sizeof(uint32_t));
  if (socket_retval == SOCKET_RETVAL_ERROR) {
    printf("[Failed: unable to set socket option]\r\n");
    goto error_handler;
  }

  if (sl_cli_get_argument_count(arguments) == 2) {
    packet_data_length = sl_cli_get_argument_uint16(arguments, 1);
  } else {
    packet_data_length = app_settings_ping.packet_length;
  }

  payload_data_length = packet_data_length - sizeof(app_icmpv6_echo_request_t);
  packet_data = sl_malloc(packet_data_length);
  if (!packet_data) {
    printf("[Failed: unable to allocate memory for an ICMP packet]\r\n");
    goto error_handler;
  }

  // ICMPv6 Echo Request header, checksum is calculated by the stack
  packet = (app_icmpv6_echo_request_t *)packet_data;
  packet->type = APP_ICMPV6_TYPE_ECHO_REQUEST;
  packet->code = APP_ICMPV6_CODE_ECHO_REQUEST;
  packet->checksum = 0;
  packet->identifier = htons(app_settings_ping.identifier);
  packet->sequence_number = htons(app_settings_ping.sequence_number);

  // ICMPv6 Echo Request payload
  payload_data = packet->payload;
  while (payload_data_length) {
    if (payload_data_length < app_settings_ping.pattern_length) {
      memcpy(payload_data, app_settings_ping.pattern, payload_data_length);
      payload_data += payload_data_length;
      payload_data_length = 0;
    } else {
      memcpy(payload_data, app_settings_ping.pattern, app_settings_ping.pattern_length);
      payload_data += app_settings_ping.pattern_length;
      payload_data_length -= app_settings_ping.pattern_length;
    }
  }

  socket_retval = sendto(app_ping_socket_id,
                         packet_data,
                         packet_data_length,
                         0,
                         (const struct sockaddr *) &dest_addr,
                         sizeof(sockaddr_in6_t));

  if (socket_retval == SOCKET_RETVAL_ERROR) {
    printf("[Failed: unable to send an ICMP packet: %ld]\r\n", socket_retval);
    goto error_handler;
  }
  else {
    app_ping_tick_count = sl_sleeptimer_get_tick_count();
    printf("PING %s: %ld data bytes\r\n", app_get_ip_address_str(&dest_addr.sin6_addr), socket_retval);
    goto cleanup;
  }

error_handler:

  if (app_ping_socket_id != SOCKET_INVALID_ID) {
    close(app_ping_socket_id);
    app_ping_socket_id = SOCKET_INVALID_ID;
  }

cleanup:

  sl_free(packet_data);
  packet_data = NULL;

  app_wisun_cli_mutex_unlock();
}

void app_tcp_client(sl_cli_command_arg_t *arguments)
{
  sl_status_t ret;
  app_socket_entry_t *entry;
  char *arg_remote_address;
  uint32_t socket_option_value = SL_WISUN_SOCKET_EVENT_MODE_INDICATION;
  int32_t socket_retval = SOCKET_RETVAL_ERROR;
  sockaddr_in6_t ipv6_remote_addr = {
    .sin6_family    = AF_INET6,
    .sin6_addr      = in6addr_any,
    .sin6_port      = 0,
    .sin6_flowinfo  = 0,
    .sin6_scope_id  = 0
  };

  app_wisun_cli_mutex_lock();

  // Parameters
  arg_remote_address = sl_cli_get_argument_string(arguments, 0);
  ret = app_get_ip_address(&ipv6_remote_addr.sin6_addr, arg_remote_address);
  if (ret != SL_STATUS_OK) {
    printf("[Failed: invalid remote address parameter]\r\n");
    goto cleanup;
  }

  ipv6_remote_addr.sin6_port = sl_cli_get_argument_uint16(arguments, 1);
  if (!ipv6_remote_addr.sin6_port) {
    printf("[Failed: invalid remote port parameter]\r\n");
    goto cleanup;
  }

  entry = app_socket_alloc_entry();
  if (!entry) {
    printf("[Failed: unable to allocate a socket entry]\r\n");
    goto cleanup;
  }

  entry->socket_type = APP_SOCKET_TYPE_TCP_CLIENT;
  entry->socket_state = APP_SOCKET_STATE_CONNECTING;
  entry->remote_address = ipv6_remote_addr.sin6_addr;
  entry->remote_port = ipv6_remote_addr.sin6_port;

  entry->socket_id = socket(AF_INET6, (SOCK_STREAM | SOCK_NONBLOCK), IPPROTO_TCP);
  if (entry->socket_id == SOCKET_INVALID_ID) {
    printf("[Failed: unable to open a socket]\r\n");
    goto error_handler;
  }

  socket_retval = setsockopt(entry->socket_id,
                             APP_LEVEL_SOCKET,
                             SOCKET_EVENT_MODE,
                             &socket_option_value,
                             sizeof(uint32_t));
  if (socket_retval == SOCKET_RETVAL_ERROR) {
    printf("[Failed: unable to set socket option]\r\n");
    goto error_handler;
  }

  socket_retval = connect(entry->socket_id, (const struct sockaddr *) &ipv6_remote_addr, sizeof(sockaddr_in6_t));
  if (socket_retval == SOCKET_RETVAL_ERROR) {
    printf("[Failed: unable to connect a socket: %ld]\r\n", socket_retval);
    goto error_handler;
  }

  // Push the entry to the active entries list
  sl_slist_push_back(&app_socket_entry_list, &entry->node);

  printf("[Opening: %s (%u): %lu]\r\n",
          app_get_ip_address_str(&ipv6_remote_addr.sin6_addr),
          ipv6_remote_addr.sin6_port,
          entry->socket_id);

  goto cleanup;

error_handler:

  if (entry->socket_id != SOCKET_INVALID_ID) {
    close(entry->socket_id);
  }
  app_socket_free_entry(entry);

cleanup:

  app_wisun_cli_mutex_unlock();

}

void app_tcp_server(sl_cli_command_arg_t *arguments)
{
  app_socket_entry_t *entry;
  uint32_t socket_option_value = SL_WISUN_SOCKET_EVENT_MODE_INDICATION;
  int32_t socket_retval = SOCKET_RETVAL_ERROR;
  sockaddr_in6_t app_sockaddr = {
    .sin6_family   = AF_INET6,
    .sin6_port     = 0,
    .sin6_flowinfo = 0,
    .sin6_addr     = APP_IN6ADDR_ANY,
    .sin6_scope_id = 0
  };

  app_wisun_cli_mutex_lock();

  // Parameters
  app_sockaddr.sin6_port = sl_cli_get_argument_uint16(arguments, 0);
  if (!app_sockaddr.sin6_port) {
    printf("[Failed: invalid local port parameter]\r\n");
    goto cleanup;
  }

  entry = app_socket_alloc_entry();
  if (!entry) {
    printf("[Failed: unable to allocate a socket entry]\r\n");
    goto cleanup;
  }

  entry->socket_type = APP_SOCKET_TYPE_TCP_SERVER;
  entry->socket_state = APP_SOCKET_STATE_LISTENING;
  entry->remote_port = app_sockaddr.sin6_port;

  entry->socket_id = socket(AF_INET6, (SOCK_STREAM | SOCK_NONBLOCK), IPPROTO_TCP);
  if (entry->socket_id == SOCKET_INVALID_ID) {
    printf("[Failed: unable to open a socket]\r\n");
    goto error_handler;
  }

  socket_retval = setsockopt(entry->socket_id,
                             APP_LEVEL_SOCKET,
                             SOCKET_EVENT_MODE,
                             &socket_option_value,
                             sizeof(uint32_t));
  if (socket_retval == SOCKET_RETVAL_ERROR) {
    printf("[Failed: unable to set socket option]\r\n");
    goto error_handler;
  }

  socket_retval = bind(entry->socket_id, (const struct sockaddr *) &app_sockaddr, sizeof(sockaddr_in6_t));
  if (socket_retval == SOCKET_RETVAL_ERROR) {
    printf("[Failed: unable to bind a socket: %ld]\r\n", socket_retval);
    goto error_handler;
  }

  socket_retval = listen(entry->socket_id, 0);
  if (socket_retval == SOCKET_RETVAL_ERROR) {
    printf("[Failed: unable to listen on a socket: %ld]\r\n", socket_retval);
    goto error_handler;
  }

  // Push the entry to the active entries list
  sl_slist_push_back(&app_socket_entry_list, &entry->node);

  printf("[Listening: %lu]\r\n", entry->socket_id);
  goto cleanup;

error_handler:

  if (entry->socket_id != SOCKET_INVALID_ID) {
    close(entry->socket_id);
  }
  app_socket_free_entry(entry);

cleanup:

  app_wisun_cli_mutex_unlock();
}

void app_udp_client(sl_cli_command_arg_t *arguments)
{
  sl_status_t ret;
  app_socket_entry_t *entry;
  char *arg_remote_address;
  uint32_t socket_option_value = SL_WISUN_SOCKET_EVENT_MODE_INDICATION;
  int32_t socket_retval = SOCKET_RETVAL_ERROR;
  sockaddr_in6_t ipv6_remote_addr = {
    .sin6_family   = AF_INET6,
    .sin6_addr     = in6addr_any,
    .sin6_port     = 0,
    .sin6_flowinfo = 0,
    .sin6_scope_id = 0
  };

  app_wisun_cli_mutex_lock();

  // Parameters
  arg_remote_address = sl_cli_get_argument_string(arguments, 0);
  ret = app_get_ip_address(&ipv6_remote_addr.sin6_addr, arg_remote_address);
  if (ret != SL_STATUS_OK) {
    printf("[Failed: invalid remote address parameter]\r\n");
    goto cleanup;
  }

  ipv6_remote_addr.sin6_port = sl_cli_get_argument_uint16(arguments, 1);
  if (!ipv6_remote_addr.sin6_port) {
    printf("[Failed: invalid remote port parameter]\r\n");
    goto cleanup;
  }

  entry = app_socket_alloc_entry();
  if (!entry) {
    printf("[Failed: unable to allocate a socket entry]\r\n");
    goto cleanup;
  }

  entry->socket_type = APP_SOCKET_TYPE_UDP_CLIENT;
  entry->socket_state = APP_SOCKET_STATE_ACTIVE;
  entry->remote_address = ipv6_remote_addr.sin6_addr;
  entry->remote_port = ipv6_remote_addr.sin6_port;

  entry->socket_id = socket(AF_INET6, (SOCK_DGRAM | SOCK_NONBLOCK), IPPROTO_UDP);
  if (entry->socket_id == SOCKET_INVALID_ID) {
    printf("[Failed: unable to open a socket]\r\n");
    goto error_handler;
  }

  socket_retval = setsockopt(entry->socket_id,
                             APP_LEVEL_SOCKET,
                             SOCKET_EVENT_MODE,
                             &socket_option_value,
                             sizeof(uint32_t));
  if (socket_retval == SOCKET_RETVAL_ERROR) {
    printf("[Failed: unable to set socket option]\r\n");
    goto error_handler;
  }

  socket_retval = connect(entry->socket_id, (const struct sockaddr *) &ipv6_remote_addr, sizeof(sockaddr_in6_t));
  if (socket_retval == SOCKET_RETVAL_ERROR) {
    printf("[Failed: unable to connect a socket: %ld]\r\n]", socket_retval);
    goto error_handler;
  }

  // Push the entry to the active entries list
  sl_slist_push_back(&app_socket_entry_list, &entry->node);

  printf("[Opened: %lu]\r\n", entry->socket_id);
  goto cleanup;

error_handler:

  if (entry->socket_id != SOCKET_INVALID_ID) {
    close(entry->socket_id);
  }
  app_socket_free_entry(entry);

cleanup:

  app_wisun_cli_mutex_unlock();
}

void app_udp_server(sl_cli_command_arg_t *arguments)
{
  app_socket_entry_t *entry;
  uint32_t socket_option_value = SL_WISUN_SOCKET_EVENT_MODE_INDICATION;
  int32_t socket_retval = SOCKET_RETVAL_ERROR;
  sockaddr_in6_t app_sockaddr = {
    .sin6_family   = AF_INET6,
    .sin6_port     = 0,
    .sin6_flowinfo = 0,
    .sin6_addr     = APP_IN6ADDR_ANY,
    .sin6_scope_id = 0
  };

  app_wisun_cli_mutex_lock();

  // Parameters
  app_sockaddr.sin6_port = sl_cli_get_argument_uint16(arguments, 0);
  if (!app_sockaddr.sin6_port) {
    printf("[Failed: invalid local port parameter]\r\n");
    goto cleanup;
  }

  entry = app_socket_alloc_entry();
  if (!entry) {
    printf("[Failed: unable to allocate a socket entry]\r\n");
    goto cleanup;
  }

  entry->socket_type = APP_SOCKET_TYPE_UDP_SERVER;
  entry->socket_state = APP_SOCKET_STATE_ACTIVE;
  entry->remote_port = app_sockaddr.sin6_port;

  entry->socket_id = socket(AF_INET6, (SOCK_DGRAM | SOCK_NONBLOCK), IPPROTO_UDP);
  if (entry->socket_id == SOCKET_INVALID_ID) {
    printf("[Failed: unable to open a socket]\r\n");
    goto error_handler;
  }

  socket_retval = setsockopt(entry->socket_id,
                             APP_LEVEL_SOCKET,
                             SOCKET_EVENT_MODE,
                             &socket_option_value,
                             sizeof(uint32_t));
  if (socket_retval == SOCKET_RETVAL_ERROR) {
    printf("[Failed: unable to set socket option]\r\n");
    goto error_handler;
  }

  socket_retval = bind(entry->socket_id, (const struct sockaddr *) &app_sockaddr, sizeof(sockaddr_in6_t));
  if (socket_retval == SOCKET_RETVAL_ERROR) {
    printf("[Failed: unable to bind a socket: %ld]\r\n", socket_retval);
    goto error_handler;
  }

  // Push the entry to the active entries list
  sl_slist_push_back(&app_socket_entry_list, &entry->node);

  printf("[Listening: %lu]\r\n", entry->socket_id);
  goto cleanup;

error_handler:

  if (entry->socket_id != SOCKET_INVALID_ID) {
    close(entry->socket_id);
  }
  app_socket_free_entry(entry);

cleanup:

  app_wisun_cli_mutex_unlock();
}

void app_socket_close(sl_cli_command_arg_t *arguments)
{
  app_socket_entry_t *entry;
  sl_wisun_socket_id_t socket_id;

  int32_t socket_retval = SOCKET_RETVAL_ERROR;

  app_wisun_cli_mutex_lock();

  // Parameters
  socket_id = sl_cli_get_argument_uint32(arguments, 0);

  entry = app_socket_entry(socket_id);
  if (!entry) {
    printf("[Failed: unable to find the specified socket]\r\n");
    goto cleanup;
  }

  socket_retval = close(socket_id);
  if (socket_retval == SOCKET_RETVAL_ERROR) {
    printf("[Failed: unable to close a socket: %ld]\r\n", socket_retval);
    goto cleanup;
  }

  app_socket_free_entry(entry);

  printf("[Closed: %lu]\r\n", socket_id);

cleanup:

  app_wisun_cli_mutex_unlock();
}

void app_socket_read(sl_cli_command_arg_t *arguments)
{
  app_socket_entry_t *entry;
  uint16_t data_length;
  uint8_t data[40];
  sl_wisun_socket_id_t socket_id;
  app_printable_data_ctx_t printable_data_ctx;
  char *printable_data;

  int32_t socket_retval = SOCKET_RETVAL_ERROR;
  socklen_t address_length = sizeof(sockaddr_in6_t);
  sockaddr_in6_t remote_address = {
    .sin6_family   = AF_INET6,
    .sin6_port     = 0,
    .sin6_flowinfo = 0,
    .sin6_addr     = APP_IN6ADDR_ANY,
    .sin6_scope_id = 0
  };

  app_wisun_cli_mutex_lock();

  // Parameters
  socket_id = sl_cli_get_argument_uint32(arguments, 0);

  data_length = sl_cli_get_argument_uint16(arguments, 1);
  if (!data_length) {
    printf("[Failed: invalid amount of bytes to read]\r\n");
    goto cleanup;
  }

  entry = app_socket_entry(socket_id);
  if (!entry) {
    printf("[Failed: unable to find the specified socket]\r\n");
    goto cleanup;
  }

  if (entry->socket_type == APP_SOCKET_TYPE_TCP_SERVER) {
    printf("[Failed: TCP server socket is not readable]\r\n");
    goto cleanup;
  }

  socket_retval = recvfrom(socket_id, data, data_length, 0, (struct sockaddr *) &remote_address, &address_length);
  if (socket_retval == SOCKET_RETVAL_ERROR) {
    printf("[Failed: unable to read from a socket: %ld]\r\n", socket_retval);
    goto cleanup;
  }

  printf("[Data from %s (%u): %lu,%ld",
         app_get_ip_address_str(&remote_address.sin6_addr),
         remote_address.sin6_port,
         socket_id,
         socket_retval);

  if (app_settings_app.printable_data_length) {
    printable_data = app_util_printable_data_init(&printable_data_ctx,
                                                  data,
                                                  data_length,
                                                  app_settings_app.printable_data_as_hex,
                                                  app_settings_app.printable_data_length);
    while (printable_data) {
      printf("\r\n%s", printable_data);
      printable_data = app_util_printable_data_next(&printable_data_ctx);
    }
  }
  printf("]\r\n");

cleanup:

  app_wisun_cli_mutex_unlock();
}

void app_socket_write(sl_cli_command_arg_t *arguments)
{
  app_socket_entry_t *entry;
  const char *data;
  sl_wisun_socket_id_t socket_id;

  int32_t socket_retval = SOCKET_RETVAL_ERROR;

  app_wisun_cli_mutex_lock();

  // Parameters
  socket_id = sl_cli_get_argument_uint32(arguments, 0);

  data = sl_cli_get_argument_string(arguments, 1);
  if (!data || !strlen(data)) {
    printf("[Failed: invalid data to be written]\r\n");
    goto cleanup;
  }

  entry = app_socket_entry(socket_id);
  if (!entry) {
    printf("[Failed: unable to find the specified socket]\r\n");
    goto cleanup;
  }

  if (entry->socket_type == APP_SOCKET_TYPE_TCP_SERVER) {
    printf("[Failed: TCP server socket is not writable]\r\n");
    goto cleanup;
  }

  if (entry->socket_type == APP_SOCKET_TYPE_UDP_SERVER) {
    printf("[Failed: UDP server socket requires socket_writeto]\r\n");
    goto cleanup;
  }

  socket_retval = send(socket_id, (const void *) data, strlen(data), 0);
  if (socket_retval == SOCKET_RETVAL_ERROR) {
    printf("[Failed: unable to write to a socket: %ld]\r\n", socket_retval);
    goto cleanup;
  }

  printf("[Wrote %ld bytes]\r\n", socket_retval);

cleanup:

  app_wisun_cli_mutex_unlock();
}

void app_socket_writeto(sl_cli_command_arg_t *arguments)
{
  sl_status_t ret;
  app_socket_entry_t *entry;
  char *arg_remote_address;
  const char *data;
  sl_wisun_socket_id_t socket_id;

  int32_t socket_retval = SOCKET_RETVAL_ERROR;
  sockaddr_in6_t ipv6_dest_addr = {
    .sin6_family   = AF_INET6,
    .sin6_port     = 0,
    .sin6_flowinfo = 0,
    .sin6_addr     = APP_IN6ADDR_ANY,
    .sin6_scope_id = 0
  };

  app_wisun_cli_mutex_lock();

  // Parameters
  socket_id = sl_cli_get_argument_uint32(arguments, 0);

  arg_remote_address = sl_cli_get_argument_string(arguments, 1);
  ret = app_get_ip_address(&ipv6_dest_addr.sin6_addr, arg_remote_address);
  if (ret != SL_STATUS_OK) {
    printf("[Failed: invalid remote address parameter]\r\n");
    goto cleanup;
  }

  ipv6_dest_addr.sin6_port = sl_cli_get_argument_uint16(arguments, 2);
  if (!ipv6_dest_addr.sin6_port) {
    printf("[Failed: invalid remote port parameter]\r\n");
    goto cleanup;
  }

  data = sl_cli_get_argument_string(arguments, 3);
  if (!data || !strlen(data)) {
    printf("[Failed: invalid data to be written]\r\n");
    goto cleanup;
  }

  entry = app_socket_entry(socket_id);
  if (!entry) {
    printf("[Failed: unable to find the specified socket]\r\n");
    goto cleanup;
  }

  if (entry->socket_type == APP_SOCKET_TYPE_TCP_SERVER) {
    printf("[Failed: TCP server socket is not writable]\r\n");
    goto cleanup;
  }

  socket_retval = sendto(socket_id,
                         (const void *)data,
                         strlen(data),
                         0,
                         (const struct sockaddr *) &ipv6_dest_addr,
                         sizeof(sockaddr_in6_t));
  if (socket_retval == SOCKET_RETVAL_ERROR) {
    printf("[Failed: unable to write to a socket: %ld]\r\n", socket_retval);
    goto cleanup;
  }

  printf("[Wrote %ld bytes]\r\n", socket_retval);

cleanup:

  app_wisun_cli_mutex_unlock();
}

void app_socket_list(sl_cli_command_arg_t *arguments)
{
  app_socket_entry_t *entry = NULL;
  char info_str[64];
  (void)arguments;

  app_wisun_cli_mutex_lock();

  printf("!  ##  Type        Info\r\n");

  SL_SLIST_FOR_EACH_ENTRY(app_socket_entry_list, entry, app_socket_entry_t, node) {
    sprintf(info_str, "%s (%u) (%s)", app_get_ip_address_str(&entry->remote_address),
      entry->remote_port, APP_SOCKET_STATE_STR[entry->socket_state]);
    printf("#  %2lu  %10s  %s\r\n", entry->socket_id, APP_SOCKET_TYPE_STR[entry->socket_type], info_str);
  }

  printf("!\r\n");

  app_wisun_cli_mutex_unlock();
}

void app_socket_set_option(sl_cli_command_arg_t *arguments)
{
  sl_status_t ret = SL_STATUS_OK;
  app_socket_entry_t *entry;
  sl_wisun_socket_id_t socket_id;
  char *arg_option;
  char *arg_option_data;
  const app_socket_option_t *iter;
  SL_ALIGN(4) sl_wisun_socket_option_data_t option_data SL_ATTRIBUTE_ALIGN(4);

  int32_t socket_retval = SOCKET_RETVAL_ERROR;

  app_wisun_cli_mutex_lock();

  // Parameters
  socket_id = sl_cli_get_argument_uint32(arguments, 0);

  arg_option = sl_cli_get_argument_string(arguments, 1);
  if (!arg_option || !strlen(arg_option)) {
    printf("[Failed: invalid option parameter]\r\n");
    goto cleanup;
  }

  arg_option_data = sl_cli_get_argument_string(arguments, 2);
  if (!arg_option || !strlen(arg_option)) {
    printf("[Failed: invalid option data parameter]\r\n");
    goto cleanup;
  }

  entry = app_socket_entry(socket_id);
  if (!entry) {
    printf("[Failed: unable to find the specified socket]\r\n");
    goto cleanup;
  }

  iter = app_set_socket_options;
  while (iter->option) {
    if (!strcmp(iter->option, arg_option)) {
      if (iter->handler) {
        ret = iter->handler(&option_data, arg_option_data);
        break;
      }
    }
    iter++;
  }

  if (!iter->option) {
    printf("[Failed: invalid option parameter]\r\n");
    goto cleanup;
  }

  if (ret != SL_STATUS_OK) {
    printf("[Failed: invalid option data parameter]\r\n");
    goto cleanup;
  }

 socket_retval = setsockopt(socket_id,
                            iter->option_level,
                            iter->option_name,
                            (void *) &option_data,
                            iter->option_lenght);
  if (socket_retval == SOCKET_RETVAL_ERROR) {
    printf("[Failed: unable to set socket option: %ld]\r\n", socket_retval);
    goto cleanup;
  }

  printf("[Socket option set]\r\n");

cleanup:

  app_wisun_cli_mutex_unlock();
}

static sl_status_t app_socket_event_mode_handler(sl_wisun_socket_option_data_t *option_data,
                                                 const char *option_data_str)
{
  // The caller guarantees the aligment of the option data,
  // thus the warning can be ignored.
  #if defined __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpragmas"
  #pragma GCC diagnostic ignored "-Waddress-of-packed-member"
  #elif defined __ICCARM__
  #pragma diag_suppress=Pa039
  #endif

  return app_util_get_integer((uint32_t *) &option_data->value, option_data_str, app_socket_event_mode, false);

  // Restore the defaults
  #ifdef __GNUC__
  #pragma GCC diagnostic pop
  #elif defined __ICCARM__
  #pragma diag_default=Pa039
  #endif
}

static sl_status_t app_socket_nonblocking_mode_handler(sl_wisun_socket_option_data_t *option_data,
                                                     const char *option_data_str)
{
  // The caller guarantees the aligment of the option data,
  // thus the warning can be ignored.
  #if defined __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpragmas"
  #pragma GCC diagnostic ignored "-Waddress-of-packed-member"
  #elif defined __ICCARM__
  #pragma diag_suppress=Pa039
  #endif

  return app_util_get_integer((uint32_t *) &option_data->value, option_data_str, app_socket_nonblock, false);

  // Restore the defaults
  #ifdef __GNUC__
  #pragma GCC diagnostic pop
  #elif defined __ICCARM__
  #pragma diag_default=Pa039
  #endif
}

static sl_status_t app_socket_send_buffer_limit_handler (sl_wisun_socket_option_data_t *option_data,
                                                         const char *option_data_str)
{
    // The caller guarantees the aligment of the option data,
  // thus the warning can be ignored.
  #if defined __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpragmas"
  #pragma GCC diagnostic ignored "-Waddress-of-packed-member"
  #elif defined __ICCARM__
  #pragma diag_suppress=Pa039
  #endif

  return app_util_get_integer((uint32_t *) &option_data->value, option_data_str, NULL, false);

  // Restore the defaults
  #ifdef __GNUC__
  #pragma GCC diagnostic pop
  #elif defined __ICCARM__
  #pragma diag_default=Pa039
  #endif
}

static sl_status_t app_socket_multicast_group_handler(sl_wisun_socket_option_data_t *option_data,
                                                      const char *option_data_str)
{
  // The caller guarantees the aligment of the option data,
  // thus the warning can be ignored.
  #ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpragmas"
  #pragma GCC diagnostic ignored "-Waddress-of-packed-member"
  #elif defined __ICCARM__
  #pragma diag_suppress=Pa039
  #endif

  if (!stoip6(option_data_str, strlen(option_data_str), &option_data->ipv6_address.address)) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  return SL_STATUS_OK;

  // Restore the defaults
  #ifdef __GNUC__
  #pragma GCC diagnostic pop
  #elif defined __ICCARM__
  #pragma diag_default=Pa039
  #endif
}

static sl_status_t app_get_ip_address(in6_addr_t *value,
                                      const char *value_str)
{
  const app_enum_t *value_enum;

  if (!value_str) {
    return SL_STATUS_FAIL;
  }

  value_enum = app_util_get_enum_by_string(app_remote_address_enum, value_str);
  if (value_enum) {
    // Resolve the enumerated address
    return sl_wisun_get_ip_address((sl_wisun_ip_address_type_t)value_enum->value, value);
  }

  // Convert address string to binary
  if (!stoip6(value_str, strlen(value_str), &value->address[0])) {
    return SL_STATUS_FAIL;
  }

  return SL_STATUS_OK;
}

static const char* app_get_ip_address_str(const in6_addr_t *value)
{
  static char remote_address_str[40];

  ip6tos(value->address, remote_address_str);

  return remote_address_str;
}

void app_mac_allow(sl_cli_command_arg_t *arguments)
{
  sl_status_t ret;
  char *address_str = NULL;
  sl_wisun_mac_address_t address;
  const app_enum_t *value_enum;

  app_wisun_cli_mutex_lock();

  address_str = sl_cli_get_argument_string(arguments, 0);

  value_enum = app_util_get_enum_by_string(app_mac_enum, address_str);
  if (value_enum) {
    // Assume enumeration means a broadcast address
    address = APP_BROADCAST_MAC;
  } else {
    // Attempt to convert the MAC address string
    ret = app_util_get_mac_address(&address, address_str);
    if (ret != SL_STATUS_OK) {
      printf("[Failed: unable to parse the MAC address: %lu]\r\n", ret);
      goto cleanup;
    }
  }

  ret = sl_wisun_allow_mac_address(&address);
  if (ret != SL_STATUS_OK) {
    printf("[Failed: unable to add the MAC address to the access list: %lu]\r\n", ret);
    goto cleanup;
  }

  printf("[MAC address added to the access list]\r\n");

cleanup:

  app_wisun_cli_mutex_unlock();
}

void app_mac_deny(sl_cli_command_arg_t *arguments)
{
  sl_status_t ret;
  char *address_str = NULL;
  sl_wisun_mac_address_t address;
  const app_enum_t *value_enum;

  app_wisun_cli_mutex_lock();

  address_str = sl_cli_get_argument_string(arguments, 0);

  value_enum = app_util_get_enum_by_string(app_mac_enum, address_str);
  if (value_enum) {
    // Assume enumeration means a broadcast address
    address = APP_BROADCAST_MAC;
  } else {
    // Attempt to convert the MAC address string
    ret = app_util_get_mac_address(&address, address_str);
    if (ret != SL_STATUS_OK) {
      printf("[Failed: unable to parse the MAC address: %lu]\r\n", ret);
      goto cleanup;
    }
  }

  ret = sl_wisun_deny_mac_address(&address);
  if (ret != SL_STATUS_OK) {
    printf("[Failed: unable to add the MAC address to the deny list: %lu]\r\n", ret);
    goto cleanup;
  }

  printf("[MAC address added to the deny list]\r\n");

cleanup:

  app_wisun_cli_mutex_unlock();
}

void app_socket_get_option(sl_cli_command_arg_t *arguments)
{
  app_socket_entry_t *entry;
  sl_wisun_socket_id_t socket_id;
  char *arg_option;
  const app_socket_option_t *iter;
  SL_ALIGN(4) sl_wisun_socket_option_data_t option_data SL_ATTRIBUTE_ALIGN(4);

  int32_t socket_retval = SOCKET_RETVAL_ERROR;
  socklen_t option_lenght = 0;

  app_wisun_cli_mutex_lock();

  if (sl_cli_get_argument_count(arguments) == 0) {
    iter = app_get_socket_options;
    printf("Options list :\r\n");
    while (iter->option) {
      printf("%s\r\n",iter->option);
      iter++;
    }

  } else if (sl_cli_get_argument_count(arguments) != 2) {
    printf("[Failed: invalid number of arguments]\r\n");
    goto cleanup;

  } else {
    // Parameters
    socket_id = sl_cli_get_argument_uint32(arguments, 0);

    arg_option = sl_cli_get_argument_string(arguments, 1);
    if (!arg_option || !strlen(arg_option)) {
      printf("[Failed: invalid option parameter]\r\n");
      goto cleanup;
    }

    entry = app_socket_entry(socket_id);
    if (!entry) {
      printf("[Failed: unable to find the specified socket]\r\n");
      goto cleanup;
    }

    iter = app_get_socket_options;
    while (iter->option) {
      if (!strcmp(iter->option, arg_option)) {
          break;
      }
      iter++;
    }

    if (!iter->option) {
      printf("[Failed: invalid option parameter]\r\n");
      goto cleanup;
    }

    option_lenght = iter->option_lenght;
    socket_retval = getsockopt(socket_id,
                               iter->option_level,
                               iter->option_name,
                               (void *) &option_data,
                               &option_lenght);
    if (socket_retval == SOCKET_RETVAL_ERROR) {
      printf("[Failed: unable to get socket option: %ld]\r\n", socket_retval);
      goto cleanup;
    }

    printf("[Socket option get: %lu]\r\n", option_data.value);

  }

cleanup:

  app_wisun_cli_mutex_unlock();
}

void app_clear_credential_cache(sl_cli_command_arg_t *arguments)
{
  sl_status_t ret;
  (void)arguments;

  app_wisun_cli_mutex_lock();

  ret = sl_wisun_clear_credential_cache();
  if (ret == SL_STATUS_OK) {
    printf("[Credential cache cleared]\r\n");
  } else {
    printf("[Credential cache clear failed: %lu]\r\n", ret);
  }

  app_wisun_cli_mutex_unlock();
}

void app_reset_statistics(sl_cli_command_arg_t *arguments)
{
  sl_status_t ret;
  (void)arguments;

  app_wisun_cli_mutex_lock();

  ret = sl_wisun_reset_statistics(SL_WISUN_STATISTICS_TYPE_PHY);
  if (ret != SL_STATUS_OK) {
    goto cleanup;
  }

  ret = sl_wisun_reset_statistics(SL_WISUN_STATISTICS_TYPE_MAC);
  if (ret != SL_STATUS_OK) {
    goto cleanup;
  }

  ret = sl_wisun_reset_statistics(SL_WISUN_STATISTICS_TYPE_FHSS);
  if (ret != SL_STATUS_OK) {
    goto cleanup;
  }

  ret = sl_wisun_reset_statistics(SL_WISUN_STATISTICS_TYPE_WISUN);
  if (ret != SL_STATUS_OK) {
    goto cleanup;
  }

  ret = sl_wisun_reset_statistics(SL_WISUN_STATISTICS_TYPE_NETWORK);
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

void app_set_lfn_support(sl_cli_command_arg_t *arguments)
{
  sl_status_t ret;
  uint8_t lfn_limit;

  app_wisun_cli_mutex_lock();

  lfn_limit = sl_cli_get_argument_uint8(arguments, 0);

  ret = sl_wisun_set_lfn_support(lfn_limit);
  if (ret != SL_STATUS_OK) {
    printf("[Failed: unable to set LFN support: %lu]\r\n", ret);
  }

  app_wisun_cli_mutex_unlock();
}


void app_rftest_start_stream(sl_cli_command_arg_t *arguments)
{
  sl_status_t ret;
  (void)arguments;
  (void)ret;
  uint16_t channel;

  channel = sl_cli_get_argument_uint32(arguments, 0);

  ret = sl_wisun_start_stream(channel);

  printf("RF Test stream started %lu\r\n", ret);
}

void app_rftest_stop_stream(sl_cli_command_arg_t *arguments)
{
  sl_status_t ret;
  (void)arguments;
  (void)ret;

  ret = sl_wisun_stop_stream();
  printf("RF Test stream stopped %lu\r\n", ret);
}

void app_rftest_start_tone(sl_cli_command_arg_t *arguments)
{
  sl_status_t ret;
  (void)arguments;
  (void)ret;
  uint16_t channel;

  channel = sl_cli_get_argument_uint32(arguments, 0);

  ret = sl_wisun_start_tone(channel);

  printf("RF Test tone started %lu\r\n", ret);
}

void app_rftest_stop_tone(sl_cli_command_arg_t *arguments)
{
  sl_status_t ret;
  (void)arguments;
  (void)ret;

  ret = sl_wisun_stop_tone();
  printf("RF Test tone stopped %lu\r\n", ret);
}

void app_rftest_set_tx_power(sl_cli_command_arg_t *arguments)
{
  sl_status_t ret;
  (void)ret;
  int16_t tx_power;

  tx_power = sl_cli_get_argument_int8(arguments, 0);

  ret = sl_wisun_set_test_tx_power(tx_power);
  printf("RF Test tx Power set to  %d\r\n", tx_power);
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

  ret = sl_wisun_set_trace_level(group_count, trace_config);
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

  ret = sl_wisun_set_unicast_tx_mode(mode);

  if (ret == SL_STATUS_OK) {
    printf("[Unicast Tx mode set to %hu suceeded]\r\n", mode);
  } else {
    printf("[Failed: unable to set unicast Tx mode: %lu]\r\n", ret);
  }

  app_wisun_cli_mutex_unlock();
}

/* CLI app mode switch */
void app_mode_switch(sl_cli_command_arg_t *arguments)
{
  sl_status_t res;
  sl_wisun_mac_address_t address;
  uint8_t mode;
  uint8_t phy_mode_id;
  char *address_str = "ff:ff:ff:ff:ff:ff:ff:ff";

  app_wisun_cli_mutex_lock();

  mode = sl_cli_get_argument_uint8(arguments, 0);
  phy_mode_id = sl_cli_get_argument_uint8(arguments, 1);

  if (sl_cli_get_argument_count(arguments) > 2) {
    // to get the third argument that is the specified address
    address_str = sl_cli_get_argument_string(arguments, 2);
    if (address_str == NULL) {
      printf("[Failed: invalid address string argument]\r\n");
      goto cleanup;
    }
  }

  // Attempt to convert the MAC address string
  res = app_util_get_mac_address(&address, address_str);
  if (res != SL_STATUS_OK) {
    printf("[Failed: unable to parse the MAC address: %lu]\r\n", res);
    goto cleanup;
  }

  res = sl_wisun_set_mode_switch(mode, phy_mode_id, &address);
  switch (res) {
    case SL_STATUS_OK:
      printf("[Mode switch succeeded]\r\n");
      break;
    case SL_STATUS_NOT_SUPPORTED:
      printf("[Mode switch feature not supported on this chip]\r\n");
      break;
    default:
      printf("[Mode switch failed]\r\n");
  }

cleanup:

  app_wisun_cli_mutex_unlock();
}

void app_trigger_frame(sl_cli_command_arg_t *arguments)
{
  char *value_str;
  uint32_t frame_type;
  sl_status_t ret;

  app_wisun_cli_mutex_lock();

  value_str = sl_cli_get_argument_string(arguments, 0);
  if (value_str == NULL) {
    printf("[Failed: missing frame type]\r\n");
    goto cleanup;
  }

  ret = app_util_get_integer(&frame_type,
                             value_str,
                             app_frame_type_enum,
                             false);
  if (ret != SL_STATUS_OK) {
    printf("[Failed: invalid frame type: %s]\r\n", value_str);
    goto cleanup;
  }

  ret = sl_wisun_trigger_frame((sl_wisun_frame_type_t)frame_type);
  if (ret != SL_STATUS_OK) {
    printf("[Failed: unable to trigger frame %s: %lu]\r\n", value_str, ret);
    goto cleanup;
  }

  printf("[Frame %s triggered successfully]\r\n", value_str);

cleanup:

  app_wisun_cli_mutex_unlock();
}
