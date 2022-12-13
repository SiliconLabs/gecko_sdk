/***************************************************************************//**
 * @file
 * @brief
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "sl_status.h"
#include "sl_component_catalog.h"
#include "sl_wisun_trace_util.h"
#include "sl_wisun_app_core_util.h"
#include "sl_wisun_trace_util.h"
#include "sl_wisun_app_setting.h"
#include "sl_wisun_network_measurement_gui.h"
#include "sli_wisun_network_measurement_settings_gui.h"
#include "sl_display.h"
#include "sl_gui.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

/// Domain list
typedef struct phy_domain_list {
  /// Domain string representation
  const char *str;
  /// Domain value
  uint8_t domain;
  /// Next ptr
  struct phy_domain_list *next;
} phy_domain_list_t;

/// Filterable parameter storage definition
typedef struct filterable {
  /// Profile
  uint8_t profile;
  /// Domain
  uint8_t domain;
} filterable_t;

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief Setting of PHY Profile
 * @details Form function for selecting regulatory domain
 * @param[in] args Arguments
 *****************************************************************************/
static void _phy_fan_form(void *args);

/**************************************************************************//**
 * @brief Setting of PHY domain
 * @details Form function for selecting PHYs
 * @param[in] args Arguments
 *****************************************************************************/
static void _phy_domain_form(void *args);

/**************************************************************************//**
 * @brief Setting of chosen PHY
 * @details Helper function
 * @param[in] args Arguments
 *****************************************************************************/
static void _set_phy(void *args);

/**************************************************************************//**
 * @brief Filter for profile and domain
 * @details Filter callback
 * @param[in] phy_cfg PHY cfg
 * @return true PHY is matched
 * @return false PHY is not matched
 *****************************************************************************/
static inline bool filter_profile(sl_wisun_phy_config_t *phy_cfg);

/**************************************************************************//**
 * @brief Full clean-up
 * @details Free allocated PHY lists and domain lists
 *****************************************************************************/
static void _full_cleanup(void);

/**************************************************************************//**
 * @brief Destroy domain list
 * @details Free domain list allocation
 *****************************************************************************/
static void _destroy_domain_list(void);

/**************************************************************************//**
 * @brief Add domain to list
 * @details Allocate new domain element on the heap
 * @param[in] domain Domain element
 * @return sl_status_t SL_STATUS_OK on success, otherwise SL_STATUS_FAIL
 *****************************************************************************/
static sl_status_t _add_domain_to_list(const phy_domain_list_t * const domain);

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

/// FAN 1.0 profile
static const uint8_t profile_fan10 = SL_WISUN_PHY_CONFIG_FAN10;

/// FAN 1.1 profile
static const uint8_t profile_fan11 = SL_WISUN_PHY_CONFIG_FAN11;

/// Filterable parameters
static filterable_t filter_params = {
  .profile = SL_WISUN_PHY_CONFIG_FAN10,
  .domain = SL_WISUN_REGULATORY_DOMAIN_NA
};

/// Domain list
static phy_domain_list_t *_domain_list = NULL;

/// Filtered PHY list
static app_wisun_phy_list_t *_phy_list = NULL;

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

void sli_wisun_nwm_phy_select_form(void *args)
{
  // const char *profile_str        = NULL;
  (void) args;

  _full_cleanup();

  sl_gui_init_all_widget();
  sl_gui_title_set_label("PHY profile selection");
  sl_gui_title_update();
  sl_gui_optionlist_add_item("Back", sli_wisun_settings_form, NULL);

  sl_gui_optionlist_add_item(app_wisun_trace_util_phy_cfg_type_to_str(SL_WISUN_PHY_CONFIG_FAN10),
                             _phy_fan_form, (void *)&profile_fan10);
  sl_gui_optionlist_add_item(app_wisun_trace_util_phy_cfg_type_to_str(SL_WISUN_PHY_CONFIG_FAN11),
                             _phy_fan_form, (void *)&profile_fan11);

  sl_gui_optionlist_assign_event_hnd_to_btn(SL_GUI_BUTTON0);
  sl_gui_optionlist_update();
  sl_gui_button_set_label(SL_GUI_BUTTON1, "Down");
  sl_gui_button_set_label(SL_GUI_BUTTON0, "Select");
  sl_gui_button_set_callback(SL_GUI_BUTTON1, sli_wisun_scroll_optionlist_and_set_select, NULL);
  sl_gui_button_update(SL_GUI_BUTTON0);
  sl_gui_button_update(SL_GUI_BUTTON1);
  sl_display_update();
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------

static void _phy_fan_form(void *args)
{
  uint8_t *profile               = NULL;
  app_wisun_phy_list_t *tmp_list = NULL;
  app_enum_t *iter               = NULL;
  phy_domain_list_t domain       = { 0 };

  profile = (uint8_t *)args;
  (void) args;

  filter_params.profile = *profile;

  // destroy domain list
  _destroy_domain_list();

  sl_gui_init_all_widget();
  sl_gui_title_set_label("PHY reg. domains");
  sl_gui_title_update();

  sl_gui_optionlist_add_item("Back", sli_wisun_nwm_phy_select_form, NULL);

  // find available domains
  iter = (app_enum_t *)app_wisun_phy_reg_domain_enum;
  while (iter != NULL && iter->value_str != NULL) {
    filter_params.domain = iter->value;
    tmp_list = app_wisun_get_phy_list(filter_profile);
    if (tmp_list != NULL) {
      domain.domain = iter->value;
      domain.str = iter->value_str;
      _add_domain_to_list(&domain);
    }
    app_wisun_destroy_phy_list(tmp_list);
    ++iter;
  }

  for (phy_domain_list_t *iter = _domain_list; iter != NULL; iter = iter->next) {
    sl_gui_optionlist_add_item(iter->str, _phy_domain_form,
                               iter);
  }
  sl_gui_optionlist_assign_event_hnd_to_btn(SL_GUI_BUTTON0);
  sl_gui_optionlist_update();
  sl_gui_button_set_label(SL_GUI_BUTTON1, "Down");
  sl_gui_button_set_label(SL_GUI_BUTTON0, "Select");
  sl_gui_button_set_callback(SL_GUI_BUTTON1, sli_wisun_scroll_optionlist_and_set_select, NULL);
  sl_gui_button_update(SL_GUI_BUTTON0);
  sl_gui_button_update(SL_GUI_BUTTON1);
  sl_display_update();
}

static void _phy_domain_form(void *args)
{
  phy_domain_list_t *domain = NULL;

  domain = (phy_domain_list_t *)args;
  filter_params.domain = domain->domain;

  // get phy list
  _phy_list = app_wisun_get_phy_list(filter_profile);;

  // destroy domain list
  _destroy_domain_list();

  sl_gui_init_all_widget();
  sl_gui_title_set_label("PHY selection");
  sl_gui_title_update();

  sl_gui_optionlist_add_item("Back", _phy_fan_form, NULL);

  for (app_wisun_phy_list_t *iter = _phy_list; iter != NULL; iter = iter->next) {
    sl_gui_optionlist_add_item(iter->name, _set_phy, iter);
  }

  sl_gui_optionlist_assign_event_hnd_to_btn(SL_GUI_BUTTON0);
  sl_gui_optionlist_update();
  sl_gui_button_set_label(SL_GUI_BUTTON1, "Down");
  sl_gui_button_set_label(SL_GUI_BUTTON0, "Select");
  sl_gui_button_set_callback(SL_GUI_BUTTON1, sli_wisun_scroll_optionlist_and_set_select, NULL);
  sl_gui_button_update(SL_GUI_BUTTON0);
  sl_gui_button_update(SL_GUI_BUTTON1);
  sl_display_update();
}

static void _set_phy(void *args)
{
  app_wisun_phy_list_t *phy = NULL;

  phy = (app_wisun_phy_list_t *)(args);

  if (phy == NULL) {
    return;
  }

  if (app_wisun_setting_set_phy(&phy->phy_cfg) == SL_STATUS_OK) {
    printf("[New PHY set: %s]\n", phy->name);
  } else {
    printf("[Failure: Selected PHY cannot be set]");
    return;
  }

  // full cleanup
  _full_cleanup();

  // to disconnet from the network
  sl_wisun_disconnect();

  // to connect to the network with the new settings
  app_wisun_network_connect();
}

static inline bool filter_profile(sl_wisun_phy_config_t *phy_cfg)
{
  switch (filter_params.profile) {
    case SL_WISUN_PHY_CONFIG_FAN10:
      return (bool) (phy_cfg->type == SL_WISUN_PHY_CONFIG_FAN10
                     && phy_cfg->config.fan10.reg_domain == filter_params.domain);
    case SL_WISUN_PHY_CONFIG_FAN11:
      return (bool) (phy_cfg->type == SL_WISUN_PHY_CONFIG_FAN11
                     && phy_cfg->config.fan11.reg_domain == filter_params.domain);
    default:
      return false;
  }
}

static sl_status_t _add_domain_to_list(const phy_domain_list_t * const domain)
{
  phy_domain_list_t *p = NULL;

  // check domain is already added
  for (phy_domain_list_t *iter = _domain_list; iter != NULL; iter = iter->next) {
    if (domain->domain == iter->domain) {
      return SL_STATUS_OK;
    }
  }

  // first element
  if (_domain_list == NULL) {
    _domain_list = app_wisun_malloc(sizeof(phy_domain_list_t));
    if (_domain_list == NULL) {
      return SL_STATUS_FAIL;
    }
    memcpy(_domain_list, domain, sizeof(phy_domain_list_t));
    _domain_list->next = NULL;
    return SL_STATUS_OK;
  }

  // add new element to tail
  p = _domain_list;
  while (p->next != NULL) {
    p = p->next;
  }
  p->next = app_wisun_malloc(sizeof(phy_domain_list_t));
  if (p->next == NULL) {
    return SL_STATUS_FAIL;
  }
  memcpy(p->next, domain, sizeof(phy_domain_list_t));
  p->next->next = NULL;

  return SL_STATUS_OK;
}

static void _destroy_domain_list(void)
{
  phy_domain_list_t *p    = NULL;
  phy_domain_list_t *iter = NULL;

  iter = _domain_list;

  while (iter != NULL) {
    p = iter;
    iter = iter->next;
    app_wisun_free(p);
  }
  _domain_list = NULL;
}

static void _full_cleanup(void)
{
  // destroy filtered PHY list by domain
  app_wisun_destroy_phy_list(_phy_list);
  _phy_list = NULL;

  // destroy domain list
  _destroy_domain_list();
}
