/*
 * Copyright (c) 2022 Silicon Laboratories Inc. (www.silabs.com)
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of the Silicon Labs Master Software License
 * Agreement (MSLA) available at [1].  This software is distributed to you in
 * Object Code format and/or Source Code format and is governed by the sections
 * of the MSLA applicable to Object Code, Source Code and Modified Open Source
 * Code. By using this software, you agree to the terms of the MSLA.
 *
 * [1]: https://www.silabs.com/about-us/legal/master-software-license-agreement
 */
#ifndef STRING_EXTRA_H_
#define STRING_EXTRA_H_
#include <stdint.h>
#include <string.h>

static inline int memzcmp(const void *src, size_t size)
{
	const uint8_t *buf = src;

	if (!size)
		return 0;
	if (*buf)
		return 1;
	return memcmp(buf, buf + 1, size - 1);
}

static inline void *memrcpy(void *dst, const void *src, size_t size)
{
    const uint8_t *src8 = src;
    uint8_t *dst8 = dst;
    unsigned int i;

    for (i = 0; i < size; i++)
        dst8[i] = src8[size - i - 1];
    return dst;
}

#endif
