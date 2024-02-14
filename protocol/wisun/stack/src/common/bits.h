/*
 * Copyright (c) 2021-2022 Silicon Laboratories Inc. (www.silabs.com)
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
#include <em_device.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef BITS_H
#define BITS_H

/*
 * FIELD_GET() and FIELD_PREP() are macros make access to bit fields easy. The
 * caller just provide the mask. The macros automatically compute the necessary
 * shift. This makes the definition of bit fields more terse.
 *
 * There is no FIELD_SET() macro (a macro that change it arguments lead to
 * questions during when developer read the code). The proposed way to set bits
 * are:
 *
 *   var &= ~MASK;
 *   var |= FIELD_PREP(val, mask);
 *
 * or (more usual finally):
 *
 *   var = 0;
 *   var |= FIELD_PREP(val1, mask2);
 *   var |= FIELD_PREP(val2, mask2);
 */

#ifdef __GNUC__

#define __CTZ(value) __builtin_ctz(value)

#else

static inline int __ctz(unsigned int val)
{
    uint8_t bits = 4 * sizeof(unsigned int);
    int cnt = 0;

    if (!val)
        return 8 * sizeof(unsigned int);
    // Proceed in O(log(n)) of size in bits
    while (bits) {
        if (!(val & ((1U << bits) - 1))) {
            cnt += bits;
            val >>= bits;
        }
        bits >>= 1;
    }
    return cnt;
}
#define __CTZ(value) __ctz(value)

#endif

// Count Leading Zeroes
static inline uint8_t clz8(uint8_t val)
{
    return val ? __CLZ(val << (8 * (sizeof(unsigned int) - 1))) : 8;
}

#define FIELD_GET(mask, reg) (((reg) & (mask)) >> __CTZ(mask))
#define FIELD_PREP(mask, val) (((val) << __CTZ(mask)) & (mask))
#define FIELD_MAX(mask) ((mask) >> __CTZ(mask))

static inline bool bitget(const uint8_t *bits, int i)
{
    return bits[i / 8] & (1 << (i % 8));
}

static inline int bitcnt(const uint8_t *bits, int nbits)
{
    int cnt = 0;

    for (int i = 0; i < nbits; i++)
        if (bitget(bits, i))
            cnt++;
    return cnt;
}

static inline void bitset(uint8_t *bits, int i)
{
    bits[i / 8] |= 1 << i % 8;
}

static inline void bitclr(uint8_t *bits, int i)
{
    bits[i / 8] &= ~(1 << i % 8);
}

/**
 * @brief Set or reset contiguous bits in a bitmask
 *
 * @param dst Bitmask
 * @param val Value to apply
 * @param start Start index of the range
 * @param end End index of the range
 * @return void* Bitmask
 */
void *bitfill(void *dst, bool val, uint32_t start, uint32_t end);

/**
 * @brief Generate channel mask from string
 *
 * A NULL str allows the total number of channels.
 *
 * @param out Channel mask (1 means allowed channel)
 * @param size Size of the bitmask in 8 bits units
 * @param chan_count Total number of channels
 * @param str String specifying ranges of allowed channels (e.g. "0-3,13,42-255")
 * @return 0 for success
 */
int parse_bitmask(uint8_t *out, int size, uint16_t chan_count, const char *str);

#endif
