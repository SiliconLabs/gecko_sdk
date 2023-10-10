/*
 * Copyright (c) 2023 Silicon Laboratories Inc. (www.silabs.com)
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this software
 * is governed by the terms of the Silicon Labs Master Software License Agreement (MSLA)
 * available at www.silabs.com/about-us/legal/master-software-license-agreement.
 * This software is distributed to you in Object Code format and/or Source Code format and
 * is governed by the sections of the MSLA applicable to Object Code, Source Code and
 * Modified Open Source Code. By using this software, you agree to the terms of the MSLA.
 *
 * This software is a modified version of the ARM/Pelion Wi-SUN FAN software stack which is
 * licensed under Apache 2.0 (see below). Modifications to the ARM/Pelion Wi-SUN software stack
 * within this software are subject to the above copyright notice and licensed pursuant to the MSLA.
 *
 * The original ARM/Pelion Wi-SUN FAN software stack is subject to the following copyright notice.
 *
 * Copyright (c) 2014-2018, Pelion and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "sl_component_catalog.h"
#include "sl_wsrcp_mac.h"
#include "sl_wsrcp_log.h"
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
    (void)rcp_mac;
#endif  // SL_CATALOG_GECKO_BOOTLOADER_INTERFACE_PRESENT
}