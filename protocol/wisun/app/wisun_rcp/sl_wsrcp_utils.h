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
#ifndef SL_WSRCP_UTILS_H
#define SL_WSRCP_UTILS_H

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define min(x, y) ({ \
    typeof(x) _x = (x); \
    typeof(y) _y = (y); \
    _x < _y ? _x : _y;  \
})

#define max(x, y) ({ \
    typeof(x) _x = (x); \
    typeof(y) _y = (y); \
    _x > _y ? _x : _y;  \
})

#define container_of(ptr, type, member)  (type *)((uintptr_t)(ptr) - ((uintptr_t)(&((type *)0)->member)))
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

// gcc provides __builtin_ctz, but IAR don't
static inline int __CTZ(uint32_t val)
{
    int ret = 0;

    if (!val)
        return 32;
    while (!(val & 1)){
        ret++;
        val >>= 1;
    }
    return ret;
}
#define FIELD_GET(mask, reg) (((reg) & (mask)) >> __CTZ(mask))
#define FIELD_PREP(mask, val) (((val) << __CTZ(mask)) & (mask))

#endif
