/***************************************************************************//**
 * @file sl_zigbee_r23_app_stubs.c
 * @brief application callbacks needed for r23 stack operation
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

#include "sl_component_catalog.h"
#include "ember-types.h"
#include "sl_zigbee_address_info.h"
#include "sl_zigbee_zdo_management.h"
#include "sl_zigbee_zdo_security.h"
#include "sl_zigbee_dynamic_commissioning.h"

WEAK(void slx_zigbee_gu_zdo_dlk_override_supported_params(uint8_t *method_mask,
                                                          uint8_t *secret_mask))
{
}

WEAK(sl_status_t sl_zigbee_zdo_dlk_select_negotiation_parameters(sl_zigbee_address_info *partner,
                                                                 uint8_t their_supported_methods,
                                                                 uint8_t their_supported_secrets,
                                                                 uint8_t *selected_method,
                                                                 uint8_t *selected_secret))
{
  return SL_STATUS_NOT_SUPPORTED;
}

WEAK(bool slx_zigbee_gu_zdo_dlk_mangle_packet(Buffer *buffer))
{
  return false;
}

WEAK(bool slx_zigbee_gu_zdo_dlk_override_psk(uint8_t *key_buffer))
{
  return false;
}

WEAK(void sl_zigbee_zdo_retrieve_authentication_token_complete_callback(sl_status_t status))
{
}

WEAK(void sl_zigbee_beacon_survey_complete_callback(EmberZdoStatus status,
                                                    sl_zigbee_beacon_survey_results_t *survey_results,
                                                    uint8_t potential_parent_count,
                                                    sl_zigbee_potential_parent_t *potential_parents,
                                                    uint16_t pan_id_conflicts))
{
  UNUSED_VAR(status);
  UNUSED_VAR(survey_results);
  UNUSED_VAR(potential_parent_count);
  UNUSED_VAR(potential_parents);
  UNUSED_VAR(pan_id_conflicts);
}

WEAK(void sl_zigbee_set_authenticaion_level(EmberEUI64 target,
                                            sl_zigbee_initial_join_method *initial_join_method,
                                            sl_zigbee_active_link_key_type *active_link_key_type))
{
  UNUSED_VAR(initial_join_method);
  UNUSED_VAR(active_link_key_type);
}

WEAK(void sl_zigbee_get_authentication_level_callback(EmberZdoStatus rsp_status,
                                                      EmberEUI64 target,
                                                      uint8_t join_method,
                                                      uint8_t link_key_update))
{
  UNUSED_VAR(rsp_status);
  UNUSED_VAR(target);
  UNUSED_VAR(join_method);
  UNUSED_VAR(link_key_update);
}

WEAK(void sl_zigbee_zdo_get_config_response_handler(Buffer response,
                                                    uint16_t payload_index,
                                                    EmberNodeId source))
{
}

WEAK(void sl_zigbee_zdo_set_config_response_handler(Buffer response,
                                                    EmberZdoStatus zdoStatus,
                                                    uint16_t payload_index,
                                                    EmberNodeId source))
{
}

WEAK(void sl_zigbee_af_zdo_set_configuration_req_callback(uint8_t* message_ptr, uint8_t message_length))
{
}

WEAK(Buffer slx_gu_fc_challenge_finalize_cb(Buffer tlvs))
{
  return tlvs;
}

WEAK(void sl_zigbee_dynamic_commissioning_alert_callback(sl_zigbee_address_info *ids,
                                                         sl_zigbee_dynamic_commissioning_event_t event))
{
  UNUSED_VAR(ids);
  UNUSED_VAR(event);
}

WEAK(bool slx_gu_do_relay_dual_submit(void))
{
  return false;
}
