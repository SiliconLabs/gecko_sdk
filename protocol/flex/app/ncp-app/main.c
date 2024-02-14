/***************************************************************************//**
 * @brief Connect - NCP application
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

#include <assert.h>
#include "sl_component_catalog.h"
#include "sl_system_init.h"
#include "app_framework_common.h"
#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
  #include "sl_power_manager.h"
#endif
#if defined(SL_CATALOG_KERNEL_PRESENT)
#include "sl_system_kernel.h"
#else
#include "sl_system_process_action.h"
#endif // SL_CATALOG_KERNEL_PRESENT
#include "sl_cpc.h"
#include "sl_gsdk_version.h"
#include "rail.h"

#define RAIL_RX_FIFO_SIZE 2048

static bool rail_rx_fifo_is_initialized = false;
static uint8_t *phy_rx_fifo = NULL;

RAIL_Status_t RAILCb_SetupRxFifo(RAIL_Handle_t railHandle)
{
  if (!rail_rx_fifo_is_initialized) {
    uint16_t rxFifoSize = RAIL_RX_FIFO_SIZE;
    phy_rx_fifo = (uint8_t *)malloc(rxFifoSize);
    assert(phy_rx_fifo != NULL);
    assert(RAIL_SetRxFifo(railHandle, &phy_rx_fifo[0], &rxFifoSize)
           == RAIL_STATUS_NO_ERROR);
    // Check that the allocated memory size in RAIL corresponds to what we want
    assert(rxFifoSize == RAIL_RX_FIFO_SIZE);
    rail_rx_fifo_is_initialized = true;
  }
  return RAIL_STATUS_NO_ERROR;
}

void app_init(void)
{
}

void app_process_action(void)
{
}

/**
 * The version returned by getting the app version through CPC is a char string
 * (e.g. "4.3.1").
 * This function can also be refined to return a user-defined application specific version
 */
const char* sl_cpc_secondary_app_version(void)
{
  return SL_GSDK_VERSION_STR;
}

int main(void)
{
  // Initialize Silicon Labs device, system, service(s) and protocol stack(s).
  // Note that if the kernel is present, processing task(s) will be created by
  // this call.
  sl_system_init();

  // Initialize the application. For example, create periodic timer(s) or
  // task(s) if the kernel is present.
  app_init();

#if defined(SL_CATALOG_KERNEL_PRESENT)
  // Start the kernel. Task(s) created in app_init() will start running.
  sl_system_kernel_start();
#else // SL_CATALOG_KERNEL_PRESENT
  while (1) {
    // Do not remove this call: Silicon Labs components process action routine
    // must be called from the super loop.
    sl_system_process_action();

    // Application process.
    app_process_action();
  }
#endif // SL_CATALOG_KERNEL_PRESENT
}
