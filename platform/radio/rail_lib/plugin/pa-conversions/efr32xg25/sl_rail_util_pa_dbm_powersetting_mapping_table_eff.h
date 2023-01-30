/***************************************************************************//**
 * @file
 * @brief PA power conversion curves used by Silicon Labs PA power conversion
 *   functions.
 * @details This file contains the curves needed convert PA power levels to
 *   dBm powers.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#ifndef __PA_DBM_POWERSETTING_MAPPING_EFF_H_
#define __PA_DBM_POWERSETTING_MAPPING_EFF_H_

#ifdef __cplusplus
extern "C" {
#endif

#define RAIL_PA_CURVES_EFF_OFDM_CURVES_NUM_VALUES  (248U)
#define RAIL_PA_CURVES_EFF_OFDM_CURVES_STEP_DDBM   (1U)
#define RAIL_PA_CURVES_EFF_OFDM_MAX_POWER_DDBM     (300U)
#define RAIL_PA_CURVES_EFF_OFDM_MIN_POWER_DDBM     (53U)
#define RAIL_PA_CURVES_EFF_OFDM_CURVES \
  {                                    \
    0x20f1e /* 5.3 dBm */,             \
    0x20f1e /* 5.4 dBm */,             \
    0x20f1e /* 5.5 dBm */,             \
    0x20f1e /* 5.6 dBm */,             \
    0x20f1e /* 5.7 dBm */,             \
    0x2101e /* 5.8 dBm */,             \
    0x2101e /* 5.9 dBm */,             \
    0x2101e /* 6.0 dBm */,             \
    0x2101e /* 6.1 dBm */,             \
    0x2101e /* 6.2 dBm */,             \
    0x2111e /* 6.3 dBm */,             \
    0x2111e /* 6.4 dBm */,             \
    0x2111e /* 6.5 dBm */,             \
    0x2111e /* 6.6 dBm */,             \
    0x2111e /* 6.7 dBm */,             \
    0x2121e /* 6.8 dBm */,             \
    0x2121e /* 6.9 dBm */,             \
    0x2121e /* 7.0 dBm */,             \
    0x2121e /* 7.1 dBm */,             \
    0x2131e /* 7.2 dBm */,             \
    0x2131e /* 7.3 dBm */,             \
    0x2131e /* 7.4 dBm */,             \
    0x2131e /* 7.5 dBm */,             \
    0x2141e /* 7.6 dBm */,             \
    0x2141e /* 7.7 dBm */,             \
    0x2141e /* 7.8 dBm */,             \
    0x2141e /* 7.9 dBm */,             \
    0x2151e /* 8.0 dBm */,             \
    0x2151e /* 8.1 dBm */,             \
    0x2151e /* 8.2 dBm */,             \
    0x2151e /* 8.3 dBm */,             \
    0x2161e /* 8.4 dBm */,             \
    0x2161e /* 8.5 dBm */,             \
    0x2161e /* 8.6 dBm */,             \
    0x2171e /* 8.7 dBm */,             \
    0x2171e /* 8.8 dBm */,             \
    0x2171e /* 8.9 dBm */,             \
    0x2171f /* 9.0 dBm */,             \
    0x2171f /* 9.1 dBm */,             \
    0x2171f /* 9.2 dBm */,             \
    0x21720 /* 9.3 dBm */,             \
    0x21721 /* 9.4 dBm */,             \
    0x21721 /* 9.5 dBm */,             \
    0x21721 /* 9.6 dBm */,             \
    0x21721 /* 9.7 dBm */,             \
    0x21722 /* 9.8 dBm */,             \
    0x21722 /* 9.9 dBm */,             \
    0x21722 /* 10.0 dBm */,            \
    0x21723 /* 10.1 dBm */,            \
    0x21723 /* 10.2 dBm */,            \
    0x21724 /* 10.3 dBm */,            \
    0x21724 /* 10.4 dBm */,            \
    0x21724 /* 10.5 dBm */,            \
    0x21824 /* 10.6 dBm */,            \
    0x21824 /* 10.7 dBm */,            \
    0x21824 /* 10.8 dBm */,            \
    0x21924 /* 10.9 dBm */,            \
    0x21a24 /* 11.0 dBm */,            \
    0x21a24 /* 11.1 dBm */,            \
    0x21a24 /* 11.2 dBm */,            \
    0x21b24 /* 11.3 dBm */,            \
    0x21b24 /* 11.4 dBm */,            \
    0x21b24 /* 11.5 dBm */,            \
    0x21c24 /* 11.6 dBm */,            \
    0x21c24 /* 11.7 dBm */,            \
    0x21c24 /* 11.8 dBm */,            \
    0x21d24 /* 11.9 dBm */,            \
    0x21d24 /* 12.0 dBm */,            \
    0x21d24 /* 12.1 dBm */,            \
    0x21e24 /* 12.2 dBm */,            \
    0x21e24 /* 12.3 dBm */,            \
    0x21e24 /* 12.4 dBm */,            \
    0x21f24 /* 12.5 dBm */,            \
    0x21f24 /* 12.6 dBm */,            \
    0x21f24 /* 12.7 dBm */,            \
    0x22024 /* 12.8 dBm */,            \
    0x22024 /* 12.9 dBm */,            \
    0x22024 /* 13.0 dBm */,            \
    0x22124 /* 13.1 dBm */,            \
    0x22124 /* 13.2 dBm */,            \
    0x22125 /* 13.3 dBm */,            \
    0x22125 /* 13.4 dBm */,            \
    0x22126 /* 13.5 dBm */,            \
    0x22126 /* 13.6 dBm */,            \
    0x22126 /* 13.7 dBm */,            \
    0x22127 /* 13.8 dBm */,            \
    0x22127 /* 13.9 dBm */,            \
    0x22128 /* 14.0 dBm */,            \
    0x22128 /* 14.1 dBm */,            \
    0x22129 /* 14.2 dBm */,            \
    0x22129 /* 14.3 dBm */,            \
    0x2212a /* 14.4 dBm */,            \
    0x2212a /* 14.5 dBm */,            \
    0x2222a /* 14.6 dBm */,            \
    0x2222a /* 14.7 dBm */,            \
    0x2232a /* 14.8 dBm */,            \
    0x2232a /* 14.9 dBm */,            \
    0x2232a /* 15.0 dBm */,            \
    0x2232a /* 15.1 dBm */,            \
    0x2242a /* 15.2 dBm */,            \
    0x2242a /* 15.3 dBm */,            \
    0x2252a /* 15.4 dBm */,            \
    0x2252a /* 15.5 dBm */,            \
    0x2262a /* 15.6 dBm */,            \
    0x2262a /* 15.7 dBm */,            \
    0x2272a /* 15.8 dBm */,            \
    0x2282a /* 15.9 dBm */,            \
    0x2282a /* 16.0 dBm */,            \
    0x2292a /* 16.1 dBm */,            \
    0x2292a /* 16.2 dBm */,            \
    0x22a2a /* 16.3 dBm */,            \
    0x22a2a /* 16.4 dBm */,            \
    0x22b2a /* 16.5 dBm */,            \
    0x22c2a /* 16.6 dBm */,            \
    0x22c2a /* 16.7 dBm */,            \
    0x22d2a /* 16.8 dBm */,            \
    0x22d2a /* 16.9 dBm */,            \
    0x22e2a /* 17.0 dBm */,            \
    0x22f2a /* 17.1 dBm */,            \
    0x22f2a /* 17.2 dBm */,            \
    0x2302a /* 17.3 dBm */,            \
    0x2312a /* 17.4 dBm */,            \
    0x2312a /* 17.5 dBm */,            \
    0x2322a /* 17.6 dBm */,            \
    0x2332a /* 17.7 dBm */,            \
    0x2342a /* 17.8 dBm */,            \
    0x2342a /* 17.9 dBm */,            \
    0x2352a /* 18.0 dBm */,            \
    0x2362a /* 18.1 dBm */,            \
    0x2372a /* 18.2 dBm */,            \
    0x2382a /* 18.3 dBm */,            \
    0x2382a /* 18.4 dBm */,            \
    0x2392a /* 18.5 dBm */,            \
    0x23a2a /* 18.6 dBm */,            \
    0x23b2a /* 18.7 dBm */,            \
    0x23c2a /* 18.8 dBm */,            \
    0x23d2a /* 18.9 dBm */,            \
    0x23e2a /* 19.0 dBm */,            \
    0x23f2a /* 19.1 dBm */,            \
    0x23f2b /* 19.2 dBm */,            \
    0x23f2b /* 19.3 dBm */,            \
    0x23f2c /* 19.4 dBm */,            \
    0x23f2c /* 19.5 dBm */,            \
    0x23f2d /* 19.6 dBm */,            \
    0x23f2d /* 19.7 dBm */,            \
    0x23f2e /* 19.8 dBm */,            \
    0x23f2e /* 19.9 dBm */,            \
    0x23f2f /* 20.0 dBm */,            \
    0x23f30 /* 20.1 dBm */,            \
    0x23f30 /* 20.2 dBm */,            \
    0x23f31 /* 20.3 dBm */,            \
    0x23f31 /* 20.4 dBm */,            \
    0x23f32 /* 20.5 dBm */,            \
    0x23f33 /* 20.6 dBm */,            \
    0x23f33 /* 20.7 dBm */,            \
    0x23f34 /* 20.8 dBm */,            \
    0x23f35 /* 20.9 dBm */,            \
    0x23f36 /* 21.0 dBm */,            \
    0x23f36 /* 21.1 dBm */,            \
    0x23f37 /* 21.2 dBm */,            \
    0x23f38 /* 21.3 dBm */,            \
    0x23f39 /* 21.4 dBm */,            \
    0x23f3a /* 21.5 dBm */,            \
    0x23f3a /* 21.6 dBm */,            \
    0x23f3b /* 21.7 dBm */,            \
    0x23f3c /* 21.8 dBm */,            \
    0x23f3d /* 21.9 dBm */,            \
    0x23f3e /* 22.0 dBm */,            \
    0x23f3e /* 22.1 dBm */,            \
    0x23f3f /* 22.2 dBm */,            \
    0x23f40 /* 22.3 dBm */,            \
    0x23f41 /* 22.4 dBm */,            \
    0x23f42 /* 22.5 dBm */,            \
    0x23f43 /* 22.6 dBm */,            \
    0x23f44 /* 22.7 dBm */,            \
    0x23f44 /* 22.8 dBm */,            \
    0x23f45 /* 22.9 dBm */,            \
    0x23f46 /* 23.0 dBm */,            \
    0x23f47 /* 23.1 dBm */,            \
    0x23f48 /* 23.2 dBm */,            \
    0x23f49 /* 23.3 dBm */,            \
    0x23f4a /* 23.4 dBm */,            \
    0x23f4b /* 23.5 dBm */,            \
    0x23f4c /* 23.6 dBm */,            \
    0x23f4d /* 23.7 dBm */,            \
    0x23f4e /* 23.8 dBm */,            \
    0x23f50 /* 23.9 dBm */,            \
    0x23f51 /* 24.0 dBm */,            \
    0x23f52 /* 24.1 dBm */,            \
    0x23f53 /* 24.2 dBm */,            \
    0x23f54 /* 24.3 dBm */,            \
    0x23f56 /* 24.4 dBm */,            \
    0x23f57 /* 24.5 dBm */,            \
    0x23f58 /* 24.6 dBm */,            \
    0x23f5a /* 24.7 dBm */,            \
    0x23f5b /* 24.8 dBm */,            \
    0x23f5c /* 24.9 dBm */,            \
    0x23f5e /* 25.0 dBm */,            \
    0x23f5f /* 25.1 dBm */,            \
    0x23f61 /* 25.2 dBm */,            \
    0x23f62 /* 25.3 dBm */,            \
    0x23f64 /* 25.4 dBm */,            \
    0x23f66 /* 25.5 dBm */,            \
    0x23f67 /* 25.6 dBm */,            \
    0x23f69 /* 25.7 dBm */,            \
    0x23f6b /* 25.8 dBm */,            \
    0x23f6e /* 25.9 dBm */,            \
    0x23f6f /* 26.0 dBm */,            \
    0x23f71 /* 26.1 dBm */,            \
    0x23f74 /* 26.2 dBm */,            \
    0x23f75 /* 26.3 dBm */,            \
    0x23f77 /* 26.4 dBm */,            \
    0x23f7a /* 26.5 dBm */,            \
    0x23f7c /* 26.6 dBm */,            \
    0x23f7e /* 26.7 dBm */,            \
    0x23f81 /* 26.8 dBm */,            \
    0x23f83 /* 26.9 dBm */,            \
    0x23f86 /* 27.0 dBm */,            \
    0x23f89 /* 27.1 dBm */,            \
    0x23f8c /* 27.2 dBm */,            \
    0x23f8f /* 27.3 dBm */,            \
    0x23f92 /* 27.4 dBm */,            \
    0x23f96 /* 27.5 dBm */,            \
    0x23f99 /* 27.6 dBm */,            \
    0x23f9e /* 27.7 dBm */,            \
    0x24284 /* 27.8 dBm */,            \
    0x24484 /* 27.9 dBm */,            \
    0x24684 /* 28.0 dBm */,            \
    0x24884 /* 28.1 dBm */,            \
    0x24a84 /* 28.2 dBm */,            \
    0x24e84 /* 28.3 dBm */,            \
    0x25084 /* 28.4 dBm */,            \
    0x25284 /* 28.5 dBm */,            \
    0x25684 /* 28.6 dBm */,            \
    0x25a84 /* 28.7 dBm */,            \
    0x25e84 /* 28.8 dBm */,            \
    0x26484 /* 28.9 dBm */,            \
    0x26784 /* 29.0 dBm */,            \
    0x26d84 /* 29.1 dBm */,            \
    0x27384 /* 29.2 dBm */,            \
    0x27c84 /* 29.3 dBm */,            \
    0x27f8c /* 29.4 dBm */,            \
    0x27f94 /* 29.5 dBm */,            \
    0x27f9d /* 29.6 dBm */,            \
    0x27fa6 /* 29.7 dBm */,            \
    0x27fb0 /* 29.8 dBm */,            \
    0x27fbb /* 29.9 dBm */,            \
    0x27fc6 /* 30.0 dBm */             \
  }

#define RAIL_PA_CURVES_EFF_SUBGIG_CURVES_NUM_VALUES  (222U)
#define RAIL_PA_CURVES_EFF_SUBGIG_CURVES_STEP_DDBM   (1U)
#define RAIL_PA_CURVES_EFF_SUBGIG_MAX_POWER_DDBM     (300U)
#define RAIL_PA_CURVES_EFF_SUBGIG_MIN_POWER_DDBM     (79U)
#define RAIL_PA_CURVES_EFF_SUBGIG_CURVES \
  {                                      \
    0x41f0018 /*  7.9 dBm */,            \
    0x41f0018 /*  8.0 dBm */,            \
    0x41f0018 /*  8.1 dBm */,            \
    0x41f0019 /*  8.2 dBm */,            \
    0x41f0019 /*  8.3 dBm */,            \
    0x41f0019 /*  8.4 dBm */,            \
    0x41f001a /*  8.5 dBm */,            \
    0x41f001a /*  8.6 dBm */,            \
    0x41f001b /*  8.7 dBm */,            \
    0x41f001b /*  8.8 dBm */,            \
    0x41f001b /*  8.9 dBm */,            \
    0x41f001b /*  9.0 dBm */,            \
    0x41f001c /*  9.1 dBm */,            \
    0x41f001c /*  9.2 dBm */,            \
    0x41f001c /*  9.3 dBm */,            \
    0x41f001d /*  9.4 dBm */,            \
    0x41f001d /*  9.5 dBm */,            \
    0x41f001e /*  9.6 dBm */,            \
    0x41f001e /*  9.7 dBm */,            \
    0x41f001f /*  9.8 dBm */,            \
    0x41f001f /*  9.9 dBm */,            \
    0x41f0100 /* 10.0 dBm */,            \
    0x41f0100 /* 10.1 dBm */,            \
    0x41f0102 /* 10.2 dBm */,            \
    0x41f0102 /* 10.3 dBm */,            \
    0x41f0102 /* 10.4 dBm */,            \
    0x41f0102 /* 10.5 dBm */,            \
    0x41f0103 /* 10.6 dBm */,            \
    0x41f0103 /* 10.7 dBm */,            \
    0x41f0104 /* 10.8 dBm */,            \
    0x41f0104 /* 10.9 dBm */,            \
    0x41f0105 /* 11.0 dBm */,            \
    0x41f0105 /* 11.1 dBm */,            \
    0x41f0106 /* 11.2 dBm */,            \
    0x41f0106 /* 11.3 dBm */,            \
    0x41f0106 /* 11.4 dBm */,            \
    0x41f0107 /* 11.5 dBm */,            \
    0x41f0107 /* 11.6 dBm */,            \
    0x41f0108 /* 11.7 dBm */,            \
    0x41f0108 /* 11.8 dBm */,            \
    0x41f0109 /* 11.9 dBm */,            \
    0x41f010a /* 12.0 dBm */,            \
    0x41f010a /* 12.1 dBm */,            \
    0x41f010b /* 12.2 dBm */,            \
    0x41f010b /* 12.3 dBm */,            \
    0x41f010b /* 12.4 dBm */,            \
    0x41f010d /* 12.5 dBm */,            \
    0x41f010d /* 12.6 dBm */,            \
    0x41f010e /* 12.7 dBm */,            \
    0x41f010e /* 12.8 dBm */,            \
    0x41f010f /* 12.9 dBm */,            \
    0x41f010f /* 13.0 dBm */,            \
    0x41f010f /* 13.1 dBm */,            \
    0x41f010f /* 13.2 dBm */,            \
    0x41f0110 /* 13.3 dBm */,            \
    0x41f0111 /* 13.4 dBm */,            \
    0x41f0111 /* 13.5 dBm */,            \
    0x41f0112 /* 13.6 dBm */,            \
    0x41f0112 /* 13.7 dBm */,            \
    0x41f0113 /* 13.8 dBm */,            \
    0x41f0113 /* 13.9 dBm */,            \
    0x41f0114 /* 14.0 dBm */,            \
    0x41f0115 /* 14.1 dBm */,            \
    0x41f0116 /* 14.2 dBm */,            \
    0x41f0116 /* 14.3 dBm */,            \
    0x41f0117 /* 14.4 dBm */,            \
    0x41f0117 /* 14.5 dBm */,            \
    0x41f0118 /* 14.6 dBm */,            \
    0x41f0119 /* 14.7 dBm */,            \
    0x41f011a /* 14.8 dBm */,            \
    0x41f011b /* 14.9 dBm */,            \
    0x41f011b /* 15.0 dBm */,            \
    0x41f011c /* 15.1 dBm */,            \
    0x41f011d /* 15.2 dBm */,            \
    0x41f011e /* 15.3 dBm */,            \
    0x41f011f /* 15.4 dBm */,            \
    0x41f0201 /* 15.5 dBm */,            \
    0x41f0203 /* 15.6 dBm */,            \
    0x41f0205 /* 15.7 dBm */,            \
    0x41f0207 /* 15.8 dBm */,            \
    0x41f0209 /* 15.9 dBm */,            \
    0x41f020b /* 16.0 dBm */,            \
    0x41f020d /* 16.1 dBm */,            \
    0x41f020f /* 16.2 dBm */,            \
    0x41f0211 /* 16.3 dBm */,            \
    0x41f0213 /* 16.4 dBm */,            \
    0x41f0215 /* 16.5 dBm */,            \
    0x41f0217 /* 16.6 dBm */,            \
    0x41f0219 /* 16.7 dBm */,            \
    0x41f021b /* 16.8 dBm */,            \
    0x41f021d /* 16.9 dBm */,            \
    0x41f021f /* 17.0 dBm */,            \
    0x41f021f /* 17.1 dBm */,            \
    0x40b0104 /* 17.2 dBm */,            \
    0x40b0104 /* 17.3 dBm */,            \
    0x40b0105 /* 17.4 dBm */,            \
    0x40b0105 /* 17.5 dBm */,            \
    0x40b0106 /* 17.6 dBm */,            \
    0x40b0106 /* 17.7 dBm */,            \
    0x40b0107 /* 17.8 dBm */,            \
    0x40b0107 /* 17.9 dBm */,            \
    0x40b0108 /* 18.0 dBm */,            \
    0x40b0108 /* 18.1 dBm */,            \
    0x40b0109 /* 18.2 dBm */,            \
    0x40b010a /* 18.3 dBm */,            \
    0x40b010a /* 18.4 dBm */,            \
    0x40b010b /* 18.5 dBm */,            \
    0x40b010b /* 18.6 dBm */,            \
    0x40b010c /* 18.7 dBm */,            \
    0x40b010c /* 18.8 dBm */,            \
    0x40b010d /* 18.9 dBm */,            \
    0x40b010d /* 19.0 dBm */,            \
    0x40b010e /* 19.1 dBm */,            \
    0x40b010f /* 19.2 dBm */,            \
    0x40b010f /* 19.3 dBm */,            \
    0x40b010f /* 19.4 dBm */,            \
    0x40b010f /* 19.5 dBm */,            \
    0x40b0110 /* 19.6 dBm */,            \
    0x40b0110 /* 19.7 dBm */,            \
    0x40b0111 /* 19.8 dBm */,            \
    0x40b0112 /* 19.9 dBm */,            \
    0x40b0113 /* 20.0 dBm */,            \
    0x40b0113 /* 20.1 dBm */,            \
    0x40b0114 /* 20.2 dBm */,            \
    0x40b0115 /* 20.3 dBm */,            \
    0x40b0116 /* 20.4 dBm */,            \
    0x40b0116 /* 20.5 dBm */,            \
    0x40b0117 /* 20.6 dBm */,            \
    0x40b0117 /* 20.7 dBm */,            \
    0x40b0117 /* 20.8 dBm */,            \
    0x40b0118 /* 20.9 dBm */,            \
    0x40b0118 /* 21.0 dBm */,            \
    0x40b0119 /* 21.1 dBm */,            \
    0x40b011a /* 21.2 dBm */,            \
    0x40b011b /* 21.3 dBm */,            \
    0x40b011b /* 21.4 dBm */,            \
    0x40b011c /* 21.5 dBm */,            \
    0x40b011d /* 21.6 dBm */,            \
    0x40b011e /* 21.7 dBm */,            \
    0x40b011f /* 21.8 dBm */,            \
    0x40b0201 /* 21.9 dBm */,            \
    0x40b0203 /* 22.0 dBm */,            \
    0x40b0205 /* 22.1 dBm */,            \
    0x40b0207 /* 22.2 dBm */,            \
    0x40b0209 /* 22.3 dBm */,            \
    0x40b020b /* 22.4 dBm */,            \
    0x40b020d /* 22.5 dBm */,            \
    0x40b020f /* 22.6 dBm */,            \
    0x40b0211 /* 22.7 dBm */,            \
    0x40b0213 /* 22.8 dBm */,            \
    0x40b0217 /* 22.9 dBm */,            \
    0x40b0219 /* 23.0 dBm */,            \
    0x40b021b /* 23.1 dBm */,            \
    0x40b021d /* 23.2 dBm */,            \
    0x40b021f /* 23.3 dBm */,            \
    0x40b021f /* 23.4 dBm */,            \
    0x4030104 /* 23.5 dBm */,            \
    0x4030104 /* 23.6 dBm */,            \
    0x4030105 /* 23.7 dBm */,            \
    0x4030105 /* 23.8 dBm */,            \
    0x4030106 /* 23.9 dBm */,            \
    0x4030106 /* 24.0 dBm */,            \
    0x4030107 /* 24.1 dBm */,            \
    0x4030107 /* 24.2 dBm */,            \
    0x4030108 /* 24.3 dBm */,            \
    0x4030108 /* 24.4 dBm */,            \
    0x4030108 /* 24.5 dBm */,            \
    0x4030109 /* 24.6 dBm */,            \
    0x403010a /* 24.7 dBm */,            \
    0x403010a /* 24.8 dBm */,            \
    0x403010b /* 24.9 dBm */,            \
    0x403010b /* 25.0 dBm */,            \
    0x403010c /* 25.1 dBm */,            \
    0x403010c /* 25.2 dBm */,            \
    0x403010d /* 25.3 dBm */,            \
    0x403010e /* 25.4 dBm */,            \
    0x403010e /* 25.5 dBm */,            \
    0x403010f /* 25.6 dBm */,            \
    0x403010f /* 25.7 dBm */,            \
    0x4030110 /* 25.8 dBm */,            \
    0x4030110 /* 25.9 dBm */,            \
    0x4030111 /* 26.0 dBm */,            \
    0x4030111 /* 26.1 dBm */,            \
    0x4030112 /* 26.2 dBm */,            \
    0x4030113 /* 26.3 dBm */,            \
    0x4030113 /* 26.4 dBm */,            \
    0x4030114 /* 26.5 dBm */,            \
    0x4030115 /* 26.6 dBm */,            \
    0x4030116 /* 26.7 dBm */,            \
    0x4030117 /* 26.8 dBm */,            \
    0x4030117 /* 26.9 dBm */,            \
    0x4030118 /* 27.0 dBm */,            \
    0x4030119 /* 27.1 dBm */,            \
    0x403011a /* 27.2 dBm */,            \
    0x403011b /* 27.3 dBm */,            \
    0x403011c /* 27.4 dBm */,            \
    0x403011d /* 27.5 dBm */,            \
    0x403011e /* 27.6 dBm */,            \
    0x403011f /* 27.7 dBm */,            \
    0x4030201 /* 27.8 dBm */,            \
    0x4030203 /* 27.9 dBm */,            \
    0x4030207 /* 28.0 dBm */,            \
    0x4030209 /* 28.1 dBm */,            \
    0x403020b /* 28.2 dBm */,            \
    0x403020d /* 28.3 dBm */,            \
    0x4030211 /* 28.4 dBm */,            \
    0x4030213 /* 28.5 dBm */,            \
    0x4030217 /* 28.6 dBm */,            \
    0x4030219 /* 28.7 dBm */,            \
    0x403021d /* 28.8 dBm */,            \
    0x4000100 /* 28.9 dBm */,            \
    0x4000100 /* 29.0 dBm */,            \
    0x4000102 /* 29.1 dBm */,            \
    0x4000102 /* 29.2 dBm */,            \
    0x4000104 /* 29.3 dBm */,            \
    0x4000104 /* 29.4 dBm */,            \
    0x4000106 /* 29.5 dBm */,            \
    0x4000108 /* 29.6 dBm */,            \
    0x4000108 /* 29.7 dBm */,            \
    0x400010a /* 29.8 dBm */,            \
    0x400010c /* 29.9 dBm */,            \
    0x400010e /* 30.0 dBm */             \
  }

#endif
// *INDENT-OFF*

#ifdef __cplusplus
}
#endif
