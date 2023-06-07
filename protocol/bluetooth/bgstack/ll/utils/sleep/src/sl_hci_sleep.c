#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <em_device.h>
#include <em_gpio.h>
#include <gpiointerrupt.h>
#include <rail.h>
#include <sl_power_manager.h>
#include <sl_status.h>

#define SL_BTCTRL_HCI_SLEEP_EXCLUDE_WEAKS
#include "sl_btctrl_hci_sleep.h"
#include "sl_btctrl_hci_transport.h"

static bool sleep_requested;
static bool em1_required = false;
static bool send_sleep_command_complete = false;
#if (!defined(SL_CATALOG_CPC_SECONDARY_PRESENT))
static uint8_t pin;
static uint8_t port;
#endif // (!defined(SL_CATALOG_CPC_SECONDARY_PRESENT))

SL_WEAK bool sl_hci_uart_is_ok_to_sleep(void)
{
  return true;
}

bool sl_btctrl_hci_sleep_is_ok_to_sleep(void)
{
  return sl_hci_uart_is_ok_to_sleep();
}

static void sl_btctrl_hci_clear_sleep_request(void)
{
  sleep_requested = false;
}

bool sl_btctrl_hci_sleep_request()
{
// Vendor specific sleep command not supported for CPC
#if defined(SL_CATALOG_CPC_SECONDARY_PRESENT)
  return false;
#endif

  if (sleep_requested) {
    return false;
  }

  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_ATOMIC();

  sleep_requested = true;
#if (!defined(SL_CATALOG_CPC_SECONDARY_PRESENT))
  uint32_t mask = 1 << pin;
  GPIO_IntClear(mask);
  GPIO_IntEnable(mask);
#endif // (!defined(SL_CATALOG_CPC_SECONDARY_PRESENT))

  sli_power_manager_update_em_requirement(SL_POWER_MANAGER_EM1, false);

  CORE_EXIT_ATOMIC();

  return true;
}

void sl_btctrl_hci_sleep_require_em1(bool req)
{
  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_ATOMIC();

  if (!em1_required && req) {
    sli_power_manager_update_em_requirement(SL_POWER_MANAGER_EM1, true);
  } else if (em1_required && !req) {
    sli_power_manager_update_em_requirement(SL_POWER_MANAGER_EM1, false);
  }

  em1_required = req;

  CORE_EXIT_ATOMIC();
}

#if (!defined(SL_CATALOG_CPC_SECONDARY_PRESENT))
static void wakeup_interrupt(uint8_t intNo)
{
  uint32_t mask = 1 << pin;

  if ((1 << intNo) & mask) {
    GPIO_IntDisable(mask);
    send_sleep_command_complete = true;
    sleep_requested = false;
    sli_power_manager_update_em_requirement(SL_POWER_MANAGER_EM1, true);
  }
}
#endif // (!defined(SL_CATALOG_CPC_SECONDARY_PRESENT))

void sl_btctrl_hci_sleep_sleep(void)
{
  if (send_sleep_command_complete == true) {
    if (sl_bthci_sleep_wakeup_callback() == SL_STATUS_OK) {
      send_sleep_command_complete = false;
    }
  }
}

void sl_btctrl_hci_sleep_init(void)
{
  GPIOINT_Init();
#if (!defined(SL_CATALOG_CPC_SECONDARY_PRESENT))
  sl_btctrl_hci_transport_get_port_pin(&port, &pin);
  GPIO_ExtIntConfig(port, pin, pin, true, false, false);
  GPIOINT_CallbackRegister(pin, wakeup_interrupt);
#endif // (!defined(SL_CATALOG_CPC_SECONDARY_PRESENT))
  sl_btctrl_hci_clear_sleep_request();
  sli_power_manager_update_em_requirement(SL_POWER_MANAGER_EM1, true);
  sli_power_manager_update_em_requirement(SL_POWER_MANAGER_EM2, true);

  // Initialize power manager support on RAIL.
  void *BTLE_LL_GetRadioHandle();
  RAIL_Handle_t rail_handle = BTLE_LL_GetRadioHandle();
  RAIL_ConfigSleep(rail_handle, RAIL_SLEEP_CONFIG_TIMERSYNC_ENABLED);
  RAIL_InitPowerManager();
}

// this callback function can be overwritten by hci layer and can
// be used to transmit hci command complete event
SL_WEAK sl_status_t sl_bthci_sleep_wakeup_callback()
{
  return SL_STATUS_OK;
}
