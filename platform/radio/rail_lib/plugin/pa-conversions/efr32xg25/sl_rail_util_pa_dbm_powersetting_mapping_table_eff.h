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

#define RAIL_PA_CURVES_EFF_OFDM_CURVES_NUM_VALUES  (214U)
#define RAIL_PA_CURVES_EFF_OFDM_CURVES_STEP_DDBM   (1U)
#define RAIL_PA_CURVES_EFF_OFDM_MAX_POWER_DDBM     (300U)
#define RAIL_PA_CURVES_EFF_OFDM_MIN_POWER_DDBM     (87U)
#define RAIL_PA_CURVES_EFF_OFDM_CURVES \
  {                                    \
    0x2142a /* 8.7 dBm */,             \
    0x2152a /* 8.8 dBm */,             \
    0x2162a /* 8.9 dBm */,             \
    0x2172a /* 9.0 dBm */,             \
    0x2182a /* 9.1 dBm */,             \
    0x2192a /* 9.2 dBm */,             \
    0x21a2a /* 9.3 dBm */,             \
    0x21b2a /* 9.4 dBm */,             \
    0x21c2a /* 9.5 dBm */,             \
    0x21d2a /* 9.6 dBm */,             \
    0x21e2a /* 9.7 dBm */,             \
    0x21f2a /* 9.8 dBm */,             \
    0x2202a /* 9.9 dBm */,             \
    0x2212a /* 10.0 dBm */,            \
    0x2222a /* 10.1 dBm */,            \
    0x2232a /* 10.2 dBm */,            \
    0x2242a /* 10.3 dBm */,            \
    0x2252a /* 10.4 dBm */,            \
    0x2262a /* 10.5 dBm */,            \
    0x2272a /* 10.6 dBm */,            \
    0x2282a /* 10.7 dBm */,            \
    0x2292a /* 10.8 dBm */,            \
    0x22a2a /* 10.9 dBm */,            \
    0x22b2a /* 11.0 dBm */,            \
    0x22c2a /* 11.1 dBm */,            \
    0x22d2a /* 11.2 dBm */,            \
    0x22e2a /* 11.3 dBm */,            \
    0x22f2a /* 11.4 dBm */,            \
    0x2302a /* 11.5 dBm */,            \
    0x2312a /* 11.6 dBm */,            \
    0x2322a /* 11.7 dBm */,            \
    0x2332a /* 11.8 dBm */,            \
    0x2342a /* 11.9 dBm */,            \
    0x2352a /* 12.0 dBm */,            \
    0x2362a /* 12.1 dBm */,            \
    0x2372a /* 12.2 dBm */,            \
    0x2382a /* 12.3 dBm */,            \
    0x2392a /* 12.4 dBm */,            \
    0x23a2a /* 12.5 dBm */,            \
    0x23b2a /* 12.6 dBm */,            \
    0x23c2a /* 12.7 dBm */,            \
    0x23d2a /* 12.8 dBm */,            \
    0x23e2a /* 12.9 dBm */,            \
    0x23f2a /* 13.0 dBm */,            \
    0x23f2a /* 13.1 dBm */,            \
    0x23f2a /* 13.2 dBm */,            \
    0x23f2b /* 13.3 dBm */,            \
    0x23f2b /* 13.4 dBm */,            \
    0x23f2c /* 13.5 dBm */,            \
    0x23f2c /* 13.6 dBm */,            \
    0x23f2c /* 13.7 dBm */,            \
    0x23f2d /* 13.8 dBm */,            \
    0x23f2d /* 13.9 dBm */,            \
    0x23f2e /* 14.0 dBm */,            \
    0x23f2e /* 14.1 dBm */,            \
    0x23f2e /* 14.2 dBm */,            \
    0x23f2f /* 14.3 dBm */,            \
    0x23f2f /* 14.4 dBm */,            \
    0x23f30 /* 14.5 dBm */,            \
    0x23f30 /* 14.6 dBm */,            \
    0x23f30 /* 14.7 dBm */,            \
    0x23f31 /* 14.8 dBm */,            \
    0x23f31 /* 14.9 dBm */,            \
    0x23f32 /* 15.0 dBm */,            \
    0x23f32 /* 15.1 dBm */,            \
    0x23f32 /* 15.2 dBm */,            \
    0x23f33 /* 15.3 dBm */,            \
    0x23f33 /* 15.4 dBm */,            \
    0x23f34 /* 15.5 dBm */,            \
    0x23f34 /* 15.6 dBm */,            \
    0x23f35 /* 15.7 dBm */,            \
    0x23f35 /* 15.8 dBm */,            \
    0x23f36 /* 15.9 dBm */,            \
    0x23f37 /* 16.0 dBm */,            \
    0x23f37 /* 16.1 dBm */,            \
    0x23f38 /* 16.2 dBm */,            \
    0x23f38 /* 16.3 dBm */,            \
    0x23f39 /* 16.4 dBm */,            \
    0x23f3a /* 16.5 dBm */,            \
    0x23f3a /* 16.6 dBm */,            \
    0x23f3b /* 16.7 dBm */,            \
    0x23f3b /* 16.8 dBm */,            \
    0x23f3c /* 16.9 dBm */,            \
    0x23f3d /* 17.0 dBm */,            \
    0x23f3d /* 17.1 dBm */,            \
    0x23f3e /* 17.2 dBm */,            \
    0x23f3e /* 17.3 dBm */,            \
    0x23f3f /* 17.4 dBm */,            \
    0x23f40 /* 17.5 dBm */,            \
    0x23f40 /* 17.6 dBm */,            \
    0x23f41 /* 17.7 dBm */,            \
    0x23f41 /* 17.8 dBm */,            \
    0x23f42 /* 17.9 dBm */,            \
    0x23f43 /* 18.0 dBm */,            \
    0x23f43 /* 18.1 dBm */,            \
    0x23f44 /* 18.2 dBm */,            \
    0x23f44 /* 18.3 dBm */,            \
    0x23f45 /* 18.4 dBm */,            \
    0x23f46 /* 18.5 dBm */,            \
    0x23f47 /* 18.6 dBm */,            \
    0x23f47 /* 18.7 dBm */,            \
    0x23f48 /* 18.8 dBm */,            \
    0x23f49 /* 18.9 dBm */,            \
    0x23f4a /* 19.0 dBm */,            \
    0x23f4b /* 19.1 dBm */,            \
    0x23f4b /* 19.2 dBm */,            \
    0x23f4c /* 19.3 dBm */,            \
    0x23f4d /* 19.4 dBm */,            \
    0x23f4e /* 19.5 dBm */,            \
    0x23f4f /* 19.6 dBm */,            \
    0x23f4f /* 19.7 dBm */,            \
    0x23f50 /* 19.8 dBm */,            \
    0x23f51 /* 19.9 dBm */,            \
    0x23f52 /* 20.0 dBm */,            \
    0x23f53 /* 20.1 dBm */,            \
    0x23f53 /* 20.2 dBm */,            \
    0x23f54 /* 20.3 dBm */,            \
    0x23f55 /* 20.4 dBm */,            \
    0x23f56 /* 20.5 dBm */,            \
    0x23f57 /* 20.6 dBm */,            \
    0x23f58 /* 20.7 dBm */,            \
    0x23f59 /* 20.8 dBm */,            \
    0x23f5a /* 20.9 dBm */,            \
    0x23f5b /* 21.0 dBm */,            \
    0x23f5c /* 21.1 dBm */,            \
    0x23f5d /* 21.2 dBm */,            \
    0x23f5e /* 21.3 dBm */,            \
    0x23f5f /* 21.4 dBm */,            \
    0x23f60 /* 21.5 dBm */,            \
    0x23f61 /* 21.6 dBm */,            \
    0x23f62 /* 21.7 dBm */,            \
    0x23f63 /* 21.8 dBm */,            \
    0x23f64 /* 21.9 dBm */,            \
    0x23f65 /* 22.0 dBm */,            \
    0x23f66 /* 22.1 dBm */,            \
    0x23f67 /* 22.2 dBm */,            \
    0x23f68 /* 22.3 dBm */,            \
    0x23f69 /* 22.4 dBm */,            \
    0x23f6a /* 22.5 dBm */,            \
    0x23f6b /* 22.6 dBm */,            \
    0x23f6c /* 22.7 dBm */,            \
    0x23f6e /* 22.8 dBm */,            \
    0x23f6f /* 22.9 dBm */,            \
    0x23f70 /* 23.0 dBm */,            \
    0x23f71 /* 23.1 dBm */,            \
    0x23f72 /* 23.2 dBm */,            \
    0x23f74 /* 23.3 dBm */,            \
    0x23f75 /* 23.4 dBm */,            \
    0x23f76 /* 23.5 dBm */,            \
    0x23f77 /* 23.6 dBm */,            \
    0x23f78 /* 23.7 dBm */,            \
    0x23f7a /* 23.8 dBm */,            \
    0x23f7b /* 23.9 dBm */,            \
    0x23f7c /* 24.0 dBm */,            \
    0x23f7e /* 24.1 dBm */,            \
    0x23f7f /* 24.2 dBm */,            \
    0x23f81 /* 24.3 dBm */,            \
    0x23f82 /* 24.4 dBm */,            \
    0x23f83 /* 24.5 dBm */,            \
    0x23f85 /* 24.6 dBm */,            \
    0x23f86 /* 24.7 dBm */,            \
    0x23f88 /* 24.8 dBm */,            \
    0x23f89 /* 24.9 dBm */,            \
    0x23f8a /* 25.0 dBm */,            \
    0x23f8c /* 25.1 dBm */,            \
    0x23f8e /* 25.2 dBm */,            \
    0x23f8f /* 25.3 dBm */,            \
    0x23f91 /* 25.4 dBm */,            \
    0x23f92 /* 25.5 dBm */,            \
    0x23f94 /* 25.6 dBm */,            \
    0x23f96 /* 25.7 dBm */,            \
    0x23f97 /* 25.8 dBm */,            \
    0x23f99 /* 25.9 dBm */,            \
    0x23f9a /* 26.0 dBm */,            \
    0x23f9c /* 26.1 dBm */,            \
    0x23f9e /* 26.2 dBm */,            \
    0x23fa0 /* 26.3 dBm */,            \
    0x24084 /* 26.4 dBm */,            \
    0x24184 /* 26.5 dBm */,            \
    0x24284 /* 26.6 dBm */,            \
    0x24384 /* 26.7 dBm */,            \
    0x24484 /* 26.8 dBm */,            \
    0x24584 /* 26.9 dBm */,            \
    0x24684 /* 27.0 dBm */,            \
    0x24884 /* 27.1 dBm */,            \
    0x24a84 /* 27.2 dBm */,            \
    0x24c84 /* 27.3 dBm */,            \
    0x24e84 /* 27.4 dBm */,            \
    0x25084 /* 27.5 dBm */,            \
    0x25284 /* 27.6 dBm */,            \
    0x25484 /* 27.7 dBm */,            \
    0x25684 /* 27.8 dBm */,            \
    0x25884 /* 27.9 dBm */,            \
    0x25a84 /* 28.0 dBm */,            \
    0x25c84 /* 28.1 dBm */,            \
    0x25e84 /* 28.2 dBm */,            \
    0x26184 /* 28.3 dBm */,            \
    0x26484 /* 28.4 dBm */,            \
    0x26784 /* 28.5 dBm */,            \
    0x26a84 /* 28.6 dBm */,            \
    0x26d84 /* 28.7 dBm */,            \
    0x27084 /* 28.8 dBm */,            \
    0x27384 /* 28.9 dBm */,            \
    0x27684 /* 29.0 dBm */,            \
    0x27984 /* 29.1 dBm */,            \
    0x27c84 /* 29.2 dBm */,            \
    0x27f84 /* 29.3 dBm */,            \
    0x27f8c /* 29.4 dBm */,            \
    0x27f94 /* 29.5 dBm */,            \
    0x27f9d /* 29.6 dBm */,            \
    0x27fa6 /* 29.7 dBm */,            \
    0x27fb0 /* 29.8 dBm */,            \
    0x27fbb /* 29.9 dBm */,            \
    0x27fc6 /* 30.0 dBm */             \
  }

#define RAIL_PA_CURVES_EFF_SUBGIG_CURVES_NUM_VALUES  (224U)
#define RAIL_PA_CURVES_EFF_SUBGIG_CURVES_STEP_DDBM   (1U)
#define RAIL_PA_CURVES_EFF_SUBGIG_MAX_POWER_DDBM     (343U)
#define RAIL_PA_CURVES_EFF_SUBGIG_MIN_POWER_DDBM     (120U)
#define RAIL_PA_CURVES_EFF_SUBGIG_CURVES \
  {                                      \
    0x41f0018 /* 12.0 dBm */,            \
    0x41f0018 /* 12.1 dBm */,            \
    0x41f0019 /* 12.2 dBm */,            \
    0x41f0019 /* 12.3 dBm */,            \
    0x41f0019 /* 12.4 dBm */,            \
    0x41f001a /* 12.5 dBm */,            \
    0x41f001a /* 12.6 dBm */,            \
    0x41f001b /* 12.7 dBm */,            \
    0x41f001b /* 12.8 dBm */,            \
    0x41f001b /* 12.9 dBm */,            \
    0x41f001b /* 13.0 dBm */,            \
    0x41f001c /* 13.1 dBm */,            \
    0x41f001c /* 13.2 dBm */,            \
    0x41f001d /* 13.3 dBm */,            \
    0x41f001d /* 13.4 dBm */,            \
    0x41f001d /* 13.5 dBm */,            \
    0x41f001d /* 13.6 dBm */,            \
    0x41f001e /* 13.7 dBm */,            \
    0x41f001e /* 13.8 dBm */,            \
    0x41f001f /* 13.9 dBm */,            \
    0x41f001f /* 14.0 dBm */,            \
    0x41f0100 /* 14.1 dBm */,            \
    0x41f0100 /* 14.2 dBm */,            \
    0x41f0101 /* 14.3 dBm */,            \
    0x41f0101 /* 14.4 dBm */,            \
    0x41f0102 /* 14.5 dBm */,            \
    0x41f0102 /* 14.6 dBm */,            \
    0x41f0103 /* 14.7 dBm */,            \
    0x41f0103 /* 14.8 dBm */,            \
    0x41f0103 /* 14.9 dBm */,            \
    0x41f0104 /* 15.0 dBm */,            \
    0x41f0104 /* 15.1 dBm */,            \
    0x41f0105 /* 15.2 dBm */,            \
    0x41f0105 /* 15.3 dBm */,            \
    0x41f0106 /* 15.4 dBm */,            \
    0x41f0106 /* 15.5 dBm */,            \
    0x41f0107 /* 15.6 dBm */,            \
    0x41f0107 /* 15.7 dBm */,            \
    0x41f0107 /* 15.8 dBm */,            \
    0x41f0108 /* 15.9 dBm */,            \
    0x41f0108 /* 16.0 dBm */,            \
    0x41f0109 /* 16.1 dBm */,            \
    0x41f010a /* 16.2 dBm */,            \
    0x41f010a /* 16.3 dBm */,            \
    0x41f010b /* 16.4 dBm */,            \
    0x41f010b /* 16.5 dBm */,            \
    0x41f010b /* 16.6 dBm */,            \
    0x41f010c /* 16.7 dBm */,            \
    0x41f010d /* 16.8 dBm */,            \
    0x41f010d /* 16.9 dBm */,            \
    0x41f010e /* 17.0 dBm */,            \
    0x41f010e /* 17.1 dBm */,            \
    0x41f010f /* 17.2 dBm */,            \
    0x41f010f /* 17.3 dBm */,            \
    0x41f010f /* 17.4 dBm */,            \
    0x41f010f /* 17.5 dBm */,            \
    0x41f0110 /* 17.6 dBm */,            \
    0x41f0111 /* 17.7 dBm */,            \
    0x41f0112 /* 17.8 dBm */,            \
    0x41f0112 /* 17.9 dBm */,            \
    0x41f0113 /* 18.0 dBm */,            \
    0x41f0113 /* 18.1 dBm */,            \
    0x41f0114 /* 18.2 dBm */,            \
    0x41f0115 /* 18.3 dBm */,            \
    0x41f0116 /* 18.4 dBm */,            \
    0x41f0116 /* 18.5 dBm */,            \
    0x41f0117 /* 18.6 dBm */,            \
    0x41f0117 /* 18.7 dBm */,            \
    0x41f0117 /* 18.8 dBm */,            \
    0x41f0118 /* 18.9 dBm */,            \
    0x41f0119 /* 19.0 dBm */,            \
    0x41f011a /* 19.1 dBm */,            \
    0x41f011b /* 19.2 dBm */,            \
    0x41f011b /* 19.3 dBm */,            \
    0x41f011c /* 19.4 dBm */,            \
    0x41f011c /* 19.5 dBm */,            \
    0x41f011d /* 19.6 dBm */,            \
    0x41f011e /* 19.7 dBm */,            \
    0x41f011f /* 19.8 dBm */,            \
    0x41f0201 /* 19.9 dBm */,            \
    0x41f0203 /* 20.0 dBm */,            \
    0x41f0205 /* 20.1 dBm */,            \
    0x41f0207 /* 20.2 dBm */,            \
    0x41f0209 /* 20.3 dBm */,            \
    0x41f020b /* 20.4 dBm */,            \
    0x41f020d /* 20.5 dBm */,            \
    0x41f020f /* 20.6 dBm */,            \
    0x41f0211 /* 20.7 dBm */,            \
    0x41f0213 /* 20.8 dBm */,            \
    0x41f0215 /* 20.9 dBm */,            \
    0x41f0217 /* 21.0 dBm */,            \
    0x41f0219 /* 21.1 dBm */,            \
    0x41f021b /* 21.2 dBm */,            \
    0x41f021d /* 21.3 dBm */,            \
    0x41f021f /* 21.4 dBm */,            \
    0x40b0104 /* 21.5 dBm */,            \
    0x40b0104 /* 21.6 dBm */,            \
    0x40b0105 /* 21.7 dBm */,            \
    0x40b0105 /* 21.8 dBm */,            \
    0x40b0106 /* 21.9 dBm */,            \
    0x40b0106 /* 22.0 dBm */,            \
    0x40b0107 /* 22.1 dBm */,            \
    0x40b0107 /* 22.2 dBm */,            \
    0x40b0107 /* 22.3 dBm */,            \
    0x40b0107 /* 22.4 dBm */,            \
    0x40b0108 /* 22.5 dBm */,            \
    0x40b0108 /* 22.6 dBm */,            \
    0x40b0109 /* 22.7 dBm */,            \
    0x40b010a /* 22.8 dBm */,            \
    0x40b010a /* 22.9 dBm */,            \
    0x40b010b /* 23.0 dBm */,            \
    0x40b010b /* 23.1 dBm */,            \
    0x40b010c /* 23.2 dBm */,            \
    0x40b010c /* 23.3 dBm */,            \
    0x40b010d /* 23.4 dBm */,            \
    0x40b010d /* 23.5 dBm */,            \
    0x40b010e /* 23.6 dBm */,            \
    0x40b010f /* 23.7 dBm */,            \
    0x40b010f /* 23.8 dBm */,            \
    0x40b010f /* 23.9 dBm */,            \
    0x40b010f /* 24.0 dBm */,            \
    0x40b010f /* 24.1 dBm */,            \
    0x40b0110 /* 24.2 dBm */,            \
    0x40b0111 /* 24.3 dBm */,            \
    0x40b0112 /* 24.4 dBm */,            \
    0x40b0113 /* 24.5 dBm */,            \
    0x40b0113 /* 24.6 dBm */,            \
    0x40b0113 /* 24.7 dBm */,            \
    0x40b0114 /* 24.8 dBm */,            \
    0x40b0115 /* 24.9 dBm */,            \
    0x40b0116 /* 25.0 dBm */,            \
    0x40b0116 /* 25.1 dBm */,            \
    0x40b0117 /* 25.2 dBm */,            \
    0x40b0117 /* 25.3 dBm */,            \
    0x40b0117 /* 25.4 dBm */,            \
    0x40b0118 /* 25.5 dBm */,            \
    0x40b0119 /* 25.6 dBm */,            \
    0x40b011a /* 25.7 dBm */,            \
    0x40b011b /* 25.8 dBm */,            \
    0x40b011b /* 25.9 dBm */,            \
    0x40b011c /* 26.0 dBm */,            \
    0x40b011d /* 26.1 dBm */,            \
    0x40b011d /* 26.2 dBm */,            \
    0x40b011e /* 26.3 dBm */,            \
    0x40b011f /* 26.4 dBm */,            \
    0x40b0201 /* 26.5 dBm */,            \
    0x40b0203 /* 26.6 dBm */,            \
    0x40b0205 /* 26.7 dBm */,            \
    0x40b0207 /* 26.8 dBm */,            \
    0x40b0209 /* 26.9 dBm */,            \
    0x40b020b /* 27.0 dBm */,            \
    0x40b020d /* 27.1 dBm */,            \
    0x40b020f /* 27.2 dBm */,            \
    0x40b0211 /* 27.3 dBm */,            \
    0x40b0213 /* 27.4 dBm */,            \
    0x40b0215 /* 27.5 dBm */,            \
    0x40b0217 /* 27.6 dBm */,            \
    0x40b0219 /* 27.7 dBm */,            \
    0x40b021b /* 27.8 dBm */,            \
    0x40b021d /* 27.9 dBm */,            \
    0x40b021f /* 28.0 dBm */,            \
    0x40b021f /* 28.1 dBm */,            \
    0x4030104 /* 28.2 dBm */,            \
    0x4030105 /* 28.3 dBm */,            \
    0x4030106 /* 28.4 dBm */,            \
    0x4030107 /* 28.5 dBm */,            \
    0x4030108 /* 28.6 dBm */,            \
    0x4030109 /* 28.7 dBm */,            \
    0x403010a /* 28.8 dBm */,            \
    0x403010b /* 28.9 dBm */,            \
    0x403010c /* 29.0 dBm */,            \
    0x403010d /* 29.1 dBm */,            \
    0x403010e /* 29.2 dBm */,            \
    0x403010f /* 29.3 dBm */,            \
    0x4030110 /* 29.4 dBm */,            \
    0x4030111 /* 29.5 dBm */,            \
    0x4030112 /* 29.6 dBm */,            \
    0x4030113 /* 29.7 dBm */,            \
    0x4030114 /* 29.8 dBm */,            \
    0x4030115 /* 29.9 dBm */,            \
    0x4030116 /* 30.0 dBm */,            \
    0x4030117 /* 30.1 dBm */,            \
    0x4030118 /* 30.2 dBm */,            \
    0x4030119 /* 30.3 dBm */,            \
    0x403011a /* 30.4 dBm */,            \
    0x403011b /* 30.5 dBm */,            \
    0x403011c /* 30.6 dBm */,            \
    0x403011d /* 30.7 dBm */,            \
    0x403011e /* 30.8 dBm */,            \
    0x403011f /* 30.9 dBm */,            \
    0x4030201 /* 31.0 dBm */,            \
    0x4030203 /* 31.1 dBm */,            \
    0x4030205 /* 31.2 dBm */,            \
    0x4030207 /* 31.3 dBm */,            \
    0x4030209 /* 31.4 dBm */,            \
    0x403020b /* 31.5 dBm */,            \
    0x403020d /* 31.6 dBm */,            \
    0x403020f /* 31.7 dBm */,            \
    0x4030211 /* 31.8 dBm */,            \
    0x4030213 /* 31.9 dBm */,            \
    0x4030215 /* 32.0 dBm */,            \
    0x4030217 /* 32.1 dBm */,            \
    0x4030219 /* 32.2 dBm */,            \
    0x403021b /* 32.3 dBm */,            \
    0x403021d /* 32.4 dBm */,            \
    0x4000100 /* 32.5 dBm */,            \
    0x4000102 /* 32.6 dBm */,            \
    0x4000104 /* 32.7 dBm */,            \
    0x4000106 /* 32.8 dBm */,            \
    0x4000108 /* 32.9 dBm */,            \
    0x400010a /* 33.0 dBm */,            \
    0x400010c /* 33.1 dBm */,            \
    0x400010e /* 33.2 dBm */,            \
    0x4000110 /* 33.3 dBm */,            \
    0x4000112 /* 33.4 dBm */,            \
    0x4000115 /* 33.5 dBm */,            \
    0x4000118 /* 33.6 dBm */,            \
    0x400011b /* 33.7 dBm */,            \
    0x400011e /* 33.8 dBm */,            \
    0x4000203 /* 33.9 dBm */,            \
    0x400020b /* 34.0 dBm */,            \
    0x4000211 /* 34.1 dBm */,            \
    0x4000219 /* 34.2 dBm */,            \
    0x400021f /* 34.3 dBm */             \
  }

#endif
// *INDENT-OFF*

#ifdef __cplusplus
}
#endif
