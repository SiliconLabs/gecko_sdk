#include "sl_component_catalog.h"
#include "sl_wsrcp_log.h"
#include "sl_wsrcp_mac.h"
#if (defined(SL_CATALOG_GECKO_BOOTLOADER_INTERFACE_PRESENT))
#include <btl_interface.h>
#endif // SL_CATALOG_GECKO_BOOTLOADER_INTERFACE_PRESENT

void wisun_rcp_btl_reset(struct sl_wsrcp_mac *rcp_mac)
{
#if (defined(SL_CATALOG_GECKO_BOOTLOADER_INTERFACE_PRESENT))
    BootloaderResetCause_t* resetCause = (BootloaderResetCause_t*) (RAM_MEM_BASE);
    resetCause->reason = BOOTLOADER_RESET_REASON_BOOTLOAD;
    resetCause->signature = BOOTLOADER_RESET_SIGNATURE_VALID;
#if defined(RMU_PRESENT)
    // Clear resetcause
    RMU->CMD = RMU_CMD_RCCLR;
    // Trigger a software system reset
    RMU->CTRL = (RMU->CTRL & ~_RMU_CTRL_SYSRMODE_MASK) | RMU_CTRL_SYSRMODE_EXTENDED;
#endif  // RMU_PRESENT
    wsmac_on_reset_req(rcp_mac);
#else
    (void) rcp_mac;
#endif  // SL_CATALOG_GECKO_BOOTLOADER_INTERFACE_PRESENT
}