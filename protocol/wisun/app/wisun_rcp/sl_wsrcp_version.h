/***************************************************************************//**
 * Copyright 2021 Silicon Laboratories Inc. www.silabs.com
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
#ifndef SL_WSRCP_VERSION_H
#define SL_WSRCP_VERSION_H

#include <stdint.h>
#include <stdbool.h>

/* 256 patch releases ought to be enough for anybody */
#define VERSION_PATCH_MASK 0x000000FF
#define VERSION_MINOR_MASK 0x00FFFF00
#define VERSION_MAJOR_MASK 0xFF000000
#define VERSION_PATCH_SHIFT 0
#define VERSION_MINOR_SHIFT 8
#define VERSION_MAJOR_SHIFT 24

// Versions for machines
extern uint32_t version_api;
extern uint32_t version_fw;

// For human beings, we can provide a more descriptive version (ie. output of
// 'git describe --tags')
extern const char *version_fw_str;

#define VERSION(major, minor, patch) (                      \
    ((major << VERSION_MAJOR_SHIFT) & VERSION_MAJOR_MASK) | \
    ((minor << VERSION_MINOR_SHIFT) & VERSION_MINOR_MASK) | \
    ((patch << VERSION_PATCH_SHIFT) & VERSION_PATCH_MASK)   \
)

static inline bool version_older_than(uint32_t version,
                                      uint8_t major, uint16_t minor, uint8_t patch)
{
    return version < VERSION(major, minor, patch);
}

#endif
