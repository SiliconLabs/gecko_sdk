/***************************************************************************//**
 * Copyright 2023-2024 Silicon Laboratories Inc. www.silabs.com
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available here[1]. This software is distributed to you in
 * Source Code format and is governed by the sections of the MSLA applicable to
 * Source Code.
 *
 * [1] www.silabs.com/about-us/legal/master-software-license-agreement
 *
 ******************************************************************************/
#ifndef SL_WSRCP_BTL_INTERFACE_H
#define SL_WSRCP_BTL_INTERFACE_H

#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif
#include "sl_wsrcp_log.h"

struct sl_wsrcp_mac;

#ifdef SL_CATALOG_GECKO_BOOTLOADER_INTERFACE_PRESENT
#include <btl_interface.h>

static inline void wisun_rcp_btl_reset(struct sl_wsrcp_mac *rcp_mac)
{
    int32_t ret;

    (void)rcp_mac;
    ret = bootloader_init();
    BUG_ON(ret != BOOTLOADER_OK);
    bootloader_rebootAndInstall();
}
#else
#include "sl_wsrcp_hif.h"

static inline void wisun_rcp_btl_reset(struct sl_wsrcp_mac *rcp_mac)
{
    (void)rcp_mac;
    FATAL(HIF_ENOBTL, "missing bootloader_interface component");
}
#endif // SL_CATALOG_GECKO_BOOTLOADER_INTERFACE_PRESENT

#endif // SL_WSRCP_BTL_INTERFACE_H
