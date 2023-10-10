/***************************************************************************//**
 * @file
 * @brief Factory Reset module
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "sl_status.h"
#include "sl_bt_api.h"
#include "sl_btmesh_api.h"
#include "em_common.h"
#include "app_assert.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT

#ifdef SL_CATALOG_CLI_PRESENT
#include "sl_cli.h"
#endif // SL_CATALOG_CLI_PRESENT

#ifdef SL_CATALOG_SLEEPTIMER_PRESENT
#include "sl_sleeptimer.h"
#endif

#include "sl_btmesh_factory_reset.h"
#include "sl_btmesh_node_reset_handler.h"

/***************************************************************************//**
 * @addtogroup FactoryReset
 * @{
 ******************************************************************************/

/*******************************************************************************
 * This function is called to initiate node reset.
 ******************************************************************************/
void sl_btmesh_initiate_node_reset()
{
  sl_status_t sc = SL_STATUS_OK;
  // Perform a factory reset of the node. This removes all the keys
  // and other settings that have been configured for this node
  sc = sl_btmesh_node_reset();
  app_assert_status_f(sc, "Failed to reset node");

  // Application callback on node reset
  sl_btmesh_factory_reset_on_node_reset();

  // Application components node reset handler
  sl_btmesh_app_node_reset_handler();

  // Small delay before reboot
  sl_sleeptimer_delay_millisecond(100);

  // Reboot
  sl_bt_system_reset(0);
}

/*******************************************************************************
 * This function is called to initiate full reset.
 ******************************************************************************/
void sl_btmesh_initiate_full_reset()
{
  sl_status_t sc = SL_STATUS_OK;
  // Perform a factory reset of the node. This removes all the keys
  // and other settings that have been configured for this node
  sc = sl_btmesh_node_reset();
  app_assert_status_f(sc, "Failed to reset node");
  // Perform a full reset by erasing PS storage.
  sc = sl_bt_nvm_erase_all();
  app_assert_status_f(sc, "Failed to erase NVM");

  // Application callback on full reset
  sl_btmesh_factory_reset_on_full_reset();

  // Small delay before reboot
  sl_sleeptimer_delay_millisecond(100);

  // Reboot
  sl_bt_system_reset(0);
}

/***************************************************************************//**
 * CLI Callback
 * @param[in] arguments pointer to CLI arguments
 ******************************************************************************/
#ifdef SL_CATALOG_CLI_PRESENT
void factory_reset_from_cli(sl_cli_command_arg_t *arguments)
{
  (void)arguments;
  sl_btmesh_initiate_full_reset();
}

void node_reset_from_cli(sl_cli_command_arg_t *arguments)
{
  (void)arguments;
  sl_btmesh_initiate_node_reset();
}
#endif // SL_CATALOG_CLI_PRESENT

/***************************************************************************//**
 * Weak implementation of node reset callback
 ******************************************************************************/
SL_WEAK void sl_btmesh_factory_reset_on_node_reset(void)
{
}

/***************************************************************************//**
 * Weak implementation of full reset callback
 ******************************************************************************/
SL_WEAK void sl_btmesh_factory_reset_on_full_reset(void)
{
}

/** @} (end addtogroup FactoryReset) */
