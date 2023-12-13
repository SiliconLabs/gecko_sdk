/**
 * @file  sli_zigbee_zdo_cluster_filter.c
 * @brief Allows for configuration of ZDO policies restricting certain clusters
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

#include "stack/zigbee/sli_zigbee_zdo_cluster_filter.h"
#include "stack/include/zigbee-device-stack.h"

/// Forward declarations
// NOTE from zigbee-device.h
extern void sli_zigbee_zig_dev_prepare_zdo_message(EmberApsFrame *apsFrame,
                                                   uint16_t clusterId,
                                                   EmberApsOption options,
                                                   uint8_t sequence);
extern EmberStatus sli_zigbee_send_zig_dev_message(EmberNodeId destination,
                                                   EmberApsFrame *apsFrame,
                                                   const char * format, ...);
// NOTE from aps-relay.h
extern bool sli_zigbee_aps_relay_frame_required(EmberNodeId dest_short_id);

// related state
static bool zdo_configuration_mode_enabled = true;
static uint16_t* cluster_filter_list = NULL;
static uint8_t cluster_filter_count = 0;

void emberSetZDOConfigurationMode(bool enabled)
{
  zdo_configuration_mode_enabled = enabled;
}

bool sli_zigbee_get_zdo_configuration_mode(void)
{
  return zdo_configuration_mode_enabled;
}

static bool zdo_in_restricted_cluster_list(uint16_t cluster)
{
  uint8_t i;
  uint16_t restricted_clusters[] = { UNBIND_REQUEST, CLEAR_ALL_BINDINGS_REQUEST, BIND_REQUEST };
  uint8_t count = 3;
  uint16_t* restricted_list = restricted_clusters;

  if (cluster_filter_list
      && cluster_filter_count != 0 ) {
    restricted_list = cluster_filter_list;
    count = cluster_filter_count;
  }

  for (i = 0; i < count; i++) {
    if (restricted_list[i] == cluster) {
      return true;
    }
  }
  return false;
}

// NOTE overriding the restricted cluster list is not currently enabled
void sli_zigbee_zdo_set_restricted_cluster_list(uint16_t* pClusterList, uint8_t count)
{
  cluster_filter_list = pClusterList;
  cluster_filter_count = count;
}

bool sli_zigbee_zdo_cluster_command_is_authorized(EmberNodeId sender,
                                                  bool was_encrypted,
                                                  uint16_t cluster_id,
                                                  bool was_broadcast,
                                                  EmberApsOption options,
                                                  uint8_t sequence_number)
{
  if ((!sli_zigbee_get_zdo_configuration_mode() || sli_zigbee_aps_relay_frame_required(sender))
      && !was_encrypted
      && zdo_in_restricted_cluster_list(cluster_id)) {
    if (!was_broadcast) {
      EmberApsFrame shortcutResponseFrame;
      sli_zigbee_zig_dev_prepare_zdo_message(&shortcutResponseFrame,
                                             cluster_id | CLUSTER_ID_RESPONSE_MINIMUM,
                                             options,
                                             sequence_number);
      (void) sli_zigbee_send_zig_dev_message(sender, &shortcutResponseFrame, "1", EMBER_ZDP_NOT_AUTHORIZED);
    }
    return false;
  }
  return true;
}
