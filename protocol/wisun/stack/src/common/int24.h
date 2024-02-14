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
#ifndef INT24_H_
#define INT24_H_

#include <stdint.h>

/* Try to mimic 24bits numbers. These types are used in several Wi-SUN IEs. So,
 * we try to also use uint24_t in the structures representing IEs.
 */

typedef uint32_t       uint24_t;
typedef int32_t        int24_t;

#define UINT24_C(x) UINT32_C(x)
#define INT24_C(x)  INT32_C(x)


/* All macros MIN and MAX are obviously not very well defined, so we
 * intentionally don't define them.
 */
// #define INT24_MIN        (-8388607-1)
// #define INT24_MAX        (8388607)
// #define UINT24_MAX       (16777215U)
// #define UINT_LEAST24_MAX (16777215U)
// #define INT_LEAST24_MIN  (-8388607-1)
// #define INT_LEAST24_MAX  (8388607)
// #define UINT_FAST24_MAX  UINT_FAST32_MAX
// #define INT_FAST24_MIN   INT_FAST32_MIN
// #define INT_FAST24_MAX   INT_FAST32_MAX

#define PRId24 PRId32
#define PRIi24 PRIi32
#define PRIo24 PRIo32
#define PRIu24 PRIu32
#define PRIx24 PRIx32
#define PRIX24 PRIX32

#define PRIdLEAST24 PRIdLEAST32
#define PRIiLEAST24 PRIiLEAST32
#define PRIoLEAST24 PRIoLEAST32
#define PRIuLEAST24 PRIuLEAST32
#define PRIxLEAST24 PRIxLEAST32
#define PRIXLEAST24 PRIXLEAST32

#define PRIdFAST24 PRIdFAST32
#define PRIiFAST24 PRIiFAST32
#define PRIoFAST24 PRIoFAST32
#define PRIuFAST24 PRIuFAST32
#define PRIxFAST24 PRIxFAST32
#define PRIXFAST24 PRIXFAST32

#define SCNd24 SCNd32
#define SCNi24 SCNi32
#define SCNu24 SCNu32
#define SCNo24 SCNo32
#define SCNx24 SCNx32
#define SCNX24 SCNX32

#define SCNdLEAST24 SCNdLEAST32
#define SCNiLEAST24 SCNiLEAST32
#define SCNoLEAST24 SCNoLEAST32
#define SCNuLEAST24 SCNuLEAST32
#define SCNxLEAST24 SCNxLEAST32
#define SCNXLEAST24 SCNXLEAST32

#define SCNdFAST24 SCNdFAST32
#define SCNiFAST24 SCNiFAST32
#define SCNoFAST24 SCNoFAST32
#define SCNuFAST24 SCNuFAST32
#define SCNxFAST24 SCNxFAST32
#define SCNXFAST24 SCNXFAST32

#endif
