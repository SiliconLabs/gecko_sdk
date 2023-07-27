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

#define RAIL_PA_CURVES_EFF_OFDM_CURVES_NUM_VALUES  (244U)
#define RAIL_PA_CURVES_EFF_OFDM_CURVES_STEP_DDBM   (1U)
#define RAIL_PA_CURVES_EFF_OFDM_MAX_POWER_DDBM     (350U)
#define RAIL_PA_CURVES_EFF_OFDM_MIN_POWER_DDBM     (107U)
#define RAIL_PA_CURVES_EFF_OFDM_CURVES \
  {                                    \
    0x20f1e /* 10.7 dBm */,            \
    0x2101e /* 10.8 dBm */,            \
    0x2101e /* 10.8 dBm */,            \
    0x2101e /* 10.8 dBm */,            \
    0x2101e /* 10.8 dBm */,            \
    0x2101e /* 10.8 dBm */,            \
    0x2111e /* 11.3 dBm */,            \
    0x2111e /* 11.3 dBm */,            \
    0x2111e /* 11.3 dBm */,            \
    0x2111e /* 11.3 dBm */,            \
    0x2111e /* 11.3 dBm */,            \
    0x2121e /* 11.8 dBm */,            \
    0x2121e /* 11.8 dBm */,            \
    0x2121e /* 11.8 dBm */,            \
    0x2121e /* 11.8 dBm */,            \
    0x2131e /* 12.2 dBm */,            \
    0x2131e /* 12.2 dBm */,            \
    0x2131e /* 12.2 dBm */,            \
    0x2131e /* 12.2 dBm */,            \
    0x2141e /* 12.6 dBm */,            \
    0x2141e /* 12.6 dBm */,            \
    0x2141e /* 12.6 dBm */,            \
    0x2141e /* 12.6 dBm */,            \
    0x2151e /* 13.0 dBm */,            \
    0x2151e /* 13.0 dBm */,            \
    0x2151e /* 13.0 dBm */,            \
    0x2151e /* 13.0 dBm */,            \
    0x2161e /* 13.4 dBm */,            \
    0x2161e /* 13.4 dBm */,            \
    0x2161e /* 13.4 dBm */,            \
    0x2171e /* 13.7 dBm */,            \
    0x2171e /* 13.7 dBm */,            \
    0x2171e /* 13.7 dBm */,            \
    0x2171f /* 14.0 dBm */,            \
    0x2171f /* 14.0 dBm */,            \
    0x2171f /* 14.0 dBm */,            \
    0x21720 /* 14.3 dBm */,            \
    0x21721 /* 14.4 dBm */,            \
    0x21721 /* 14.4 dBm */,            \
    0x21721 /* 14.4 dBm */,            \
    0x21721 /* 14.4 dBm */,            \
    0x21722 /* 14.8 dBm */,            \
    0x21722 /* 14.8 dBm */,            \
    0x21722 /* 14.8 dBm */,            \
    0x21723 /* 15.1 dBm */,            \
    0x21723 /* 15.1 dBm */,            \
    0x21724 /* 15.3 dBm */,            \
    0x21724 /* 15.3 dBm */,            \
    0x21724 /* 15.3 dBm */,            \
    0x21824 /* 15.6 dBm */,            \
    0x21824 /* 15.6 dBm */,            \
    0x21824 /* 15.6 dBm */,            \
    0x21924 /* 15.9 dBm */,            \
    0x21a24 /* 16.0 dBm */,            \
    0x21a24 /* 16.0 dBm */,            \
    0x21a24 /* 16.0 dBm */,            \
    0x21b24 /* 16.3 dBm */,            \
    0x21b24 /* 16.3 dBm */,            \
    0x21b24 /* 16.3 dBm */,            \
    0x21c24 /* 16.6 dBm */,            \
    0x21c24 /* 16.6 dBm */,            \
    0x21c24 /* 16.6 dBm */,            \
    0x21d24 /* 16.9 dBm */,            \
    0x21d24 /* 16.9 dBm */,            \
    0x21d24 /* 16.9 dBm */,            \
    0x21e24 /* 17.2 dBm */,            \
    0x21e24 /* 17.2 dBm */,            \
    0x21e24 /* 17.2 dBm */,            \
    0x21f24 /* 17.5 dBm */,            \
    0x21f24 /* 17.5 dBm */,            \
    0x21f24 /* 17.5 dBm */,            \
    0x22024 /* 17.8 dBm */,            \
    0x22024 /* 17.8 dBm */,            \
    0x22024 /* 17.8 dBm */,            \
    0x22124 /* 18.1 dBm */,            \
    0x22124 /* 18.1 dBm */,            \
    0x22125 /* 18.3 dBm */,            \
    0x22125 /* 18.3 dBm */,            \
    0x22126 /* 18.5 dBm */,            \
    0x22126 /* 18.5 dBm */,            \
    0x22126 /* 18.5 dBm */,            \
    0x22127 /* 18.8 dBm */,            \
    0x22127 /* 18.8 dBm */,            \
    0x22128 /* 19.0 dBm */,            \
    0x22128 /* 19.0 dBm */,            \
    0x22129 /* 19.2 dBm */,            \
    0x22129 /* 19.2 dBm */,            \
    0x2212a /* 19.4 dBm */,            \
    0x2212a /* 19.4 dBm */,            \
    0x2222a /* 19.6 dBm */,            \
    0x2222a /* 19.6 dBm */,            \
    0x2232a /* 19.8 dBm */,            \
    0x2232a /* 19.8 dBm */,            \
    0x2232a /* 19.8 dBm */,            \
    0x2232a /* 19.8 dBm */,            \
    0x2242a /* 20.2 dBm */,            \
    0x2242a /* 20.2 dBm */,            \
    0x2252a /* 20.4 dBm */,            \
    0x2252a /* 20.4 dBm */,            \
    0x2262a /* 20.6 dBm */,            \
    0x2262a /* 20.6 dBm */,            \
    0x2272a /* 20.8 dBm */,            \
    0x2282a /* 20.9 dBm */,            \
    0x2282a /* 20.9 dBm */,            \
    0x2292a /* 21.1 dBm */,            \
    0x2292a /* 21.1 dBm */,            \
    0x22a2a /* 21.3 dBm */,            \
    0x22a2a /* 21.3 dBm */,            \
    0x22b2a /* 21.5 dBm */,            \
    0x22c2a /* 21.6 dBm */,            \
    0x22c2a /* 21.6 dBm */,            \
    0x22d2a /* 21.8 dBm */,            \
    0x22d2a /* 21.8 dBm */,            \
    0x22e2a /* 22.0 dBm */,            \
    0x22f2a /* 22.1 dBm */,            \
    0x22f2a /* 22.1 dBm */,            \
    0x2302a /* 22.3 dBm */,            \
    0x2312a /* 22.4 dBm */,            \
    0x2312a /* 22.4 dBm */,            \
    0x2322a /* 22.6 dBm */,            \
    0x2332a /* 22.7 dBm */,            \
    0x2342a /* 22.8 dBm */,            \
    0x2342a /* 22.8 dBm */,            \
    0x2352a /* 23.0 dBm */,            \
    0x2362a /* 23.1 dBm */,            \
    0x2372a /* 23.2 dBm */,            \
    0x2382a /* 23.3 dBm */,            \
    0x2382a /* 23.3 dBm */,            \
    0x2392a /* 23.5 dBm */,            \
    0x23a2a /* 23.6 dBm */,            \
    0x23b2a /* 23.7 dBm */,            \
    0x23c2a /* 23.8 dBm */,            \
    0x23d2a /* 23.9 dBm */,            \
    0x23e2a /* 24.0 dBm */,            \
    0x23f2a /* 24.1 dBm */,            \
    0x23f2b /* 24.2 dBm */,            \
    0x23f2b /* 24.2 dBm */,            \
    0x23f2c /* 24.4 dBm */,            \
    0x23f2c /* 24.4 dBm */,            \
    0x23f2d /* 24.6 dBm */,            \
    0x23f2d /* 24.6 dBm */,            \
    0x23f2e /* 24.8 dBm */,            \
    0x23f2e /* 24.8 dBm */,            \
    0x23f2f /* 25.0 dBm */,            \
    0x23f30 /* 25.1 dBm */,            \
    0x23f30 /* 25.1 dBm */,            \
    0x23f31 /* 25.3 dBm */,            \
    0x23f31 /* 25.3 dBm */,            \
    0x23f32 /* 25.5 dBm */,            \
    0x23f33 /* 25.6 dBm */,            \
    0x23f33 /* 25.6 dBm */,            \
    0x23f34 /* 25.8 dBm */,            \
    0x23f35 /* 25.9 dBm */,            \
    0x23f36 /* 26.0 dBm */,            \
    0x23f36 /* 26.0 dBm */,            \
    0x23f37 /* 26.2 dBm */,            \
    0x23f38 /* 26.3 dBm */,            \
    0x23f39 /* 26.4 dBm */,            \
    0x23f3a /* 26.5 dBm */,            \
    0x23f3a /* 26.5 dBm */,            \
    0x23f3b /* 26.7 dBm */,            \
    0x23f3c /* 26.8 dBm */,            \
    0x23f3d /* 26.9 dBm */,            \
    0x23f3e /* 27.0 dBm */,            \
    0x23f3e /* 27.0 dBm */,            \
    0x23f3f /* 27.2 dBm */,            \
    0x23f40 /* 27.3 dBm */,            \
    0x23f41 /* 27.4 dBm */,            \
    0x23f42 /* 27.5 dBm */,            \
    0x23f43 /* 27.6 dBm */,            \
    0x23f44 /* 27.7 dBm */,            \
    0x23f44 /* 27.7 dBm */,            \
    0x23f45 /* 27.9 dBm */,            \
    0x23f46 /* 28.0 dBm */,            \
    0x23f47 /* 28.1 dBm */,            \
    0x23f48 /* 28.2 dBm */,            \
    0x23f49 /* 28.3 dBm */,            \
    0x23f4a /* 28.4 dBm */,            \
    0x23f4b /* 28.5 dBm */,            \
    0x23f4c /* 28.6 dBm */,            \
    0x23f4d /* 28.7 dBm */,            \
    0x23f4e /* 28.8 dBm */,            \
    0x23f50 /* 28.9 dBm */,            \
    0x23f51 /* 29.0 dBm */,            \
    0x23f52 /* 29.1 dBm */,            \
    0x23f53 /* 29.2 dBm */,            \
    0x23f54 /* 29.3 dBm */,            \
    0x23f56 /* 29.4 dBm */,            \
    0x23f57 /* 29.5 dBm */,            \
    0x23f58 /* 29.6 dBm */,            \
    0x23f5a /* 29.7 dBm */,            \
    0x23f5b /* 29.8 dBm */,            \
    0x23f5c /* 29.9 dBm */,            \
    0x23f5e /* 30.0 dBm */,            \
    0x23f5f /* 30.1 dBm */,            \
    0x23f61 /* 30.2 dBm */,            \
    0x23f62 /* 30.3 dBm */,            \
    0x23f64 /* 30.4 dBm */,            \
    0x23f66 /* 30.5 dBm */,            \
    0x23f67 /* 30.6 dBm */,            \
    0x23f69 /* 30.7 dBm */,            \
    0x23f6b /* 30.8 dBm */,            \
    0x23f6e /* 30.9 dBm */,            \
    0x23f6f /* 31.0 dBm */,            \
    0x23f71 /* 31.1 dBm */,            \
    0x23f74 /* 31.2 dBm */,            \
    0x23f75 /* 31.3 dBm */,            \
    0x23f77 /* 31.4 dBm */,            \
    0x23f7a /* 31.5 dBm */,            \
    0x23f7c /* 31.6 dBm */,            \
    0x23f7e /* 31.7 dBm */,            \
    0x23f81 /* 31.8 dBm */,            \
    0x23f83 /* 31.9 dBm */,            \
    0x23f86 /* 32.0 dBm */,            \
    0x23f89 /* 32.1 dBm */,            \
    0x23f8c /* 32.2 dBm */,            \
    0x23f8f /* 32.3 dBm */,            \
    0x23f92 /* 32.4 dBm */,            \
    0x23f96 /* 32.5 dBm */,            \
    0x23f99 /* 32.6 dBm */,            \
    0x23f9e /* 32.7 dBm */,            \
    0x24284 /* 32.8 dBm */,            \
    0x24484 /* 32.9 dBm */,            \
    0x24684 /* 33.0 dBm */,            \
    0x24884 /* 33.1 dBm */,            \
    0x24a84 /* 33.2 dBm */,            \
    0x24e84 /* 33.3 dBm */,            \
    0x25084 /* 33.4 dBm */,            \
    0x25284 /* 33.5 dBm */,            \
    0x25684 /* 33.6 dBm */,            \
    0x25a84 /* 33.7 dBm */,            \
    0x25e84 /* 33.8 dBm */,            \
    0x26484 /* 33.9 dBm */,            \
    0x26784 /* 34.0 dBm */,            \
    0x26d84 /* 34.1 dBm */,            \
    0x27384 /* 34.2 dBm */,            \
    0x27c84 /* 34.3 dBm */,            \
    0x27f8c /* 34.4 dBm */,            \
    0x27f94 /* 34.5 dBm */,            \
    0x27f9d /* 34.6 dBm */,            \
    0x27fa6 /* 34.7 dBm */,            \
    0x27fb0 /* 34.8 dBm */,            \
    0x27fbb /* 34.9 dBm */,            \
    0x27fc6 /* 35.0 dBm */,            \
  }

#define RAIL_PA_CURVES_EFF_SUBGIG_CURVES_NUM_VALUES  (220U)
#define RAIL_PA_CURVES_EFF_SUBGIG_CURVES_STEP_DDBM   (1U)
#define RAIL_PA_CURVES_EFF_SUBGIG_MAX_POWER_DDBM     (356U)
#define RAIL_PA_CURVES_EFF_SUBGIG_MIN_POWER_DDBM     (137U)
#define RAIL_PA_CURVES_EFF_SUBGIG_CURVES \
  {                                      \
    0x41f0018 /* 13.7 dBm */,            \
    0x41f0019 /* 13.8 dBm */,            \
    0x41f0019 /* 13.8 dBm */,            \
    0x41f0019 /* 13.8 dBm */,            \
    0x41f001a /* 14.1 dBm */,            \
    0x41f001a /* 14.1 dBm */,            \
    0x41f001b /* 14.3 dBm */,            \
    0x41f001b /* 14.3 dBm */,            \
    0x41f001b /* 14.3 dBm */,            \
    0x41f001b /* 14.3 dBm */,            \
    0x41f001c /* 14.7 dBm */,            \
    0x41f001c /* 14.7 dBm */,            \
    0x41f001c /* 14.7 dBm */,            \
    0x41f001d /* 15.0 dBm */,            \
    0x41f001d /* 15.0 dBm */,            \
    0x41f001e /* 15.2 dBm */,            \
    0x41f001e /* 15.2 dBm */,            \
    0x41f001f /* 15.4 dBm */,            \
    0x41f001f /* 15.4 dBm */,            \
    0x41f0100 /* 15.6 dBm */,            \
    0x41f0100 /* 15.6 dBm */,            \
    0x41f0102 /* 15.8 dBm */,            \
    0x41f0102 /* 15.8 dBm */,            \
    0x41f0102 /* 15.8 dBm */,            \
    0x41f0102 /* 15.8 dBm */,            \
    0x41f0103 /* 16.2 dBm */,            \
    0x41f0103 /* 16.2 dBm */,            \
    0x41f0104 /* 16.4 dBm */,            \
    0x41f0104 /* 16.4 dBm */,            \
    0x41f0105 /* 16.6 dBm */,            \
    0x41f0105 /* 16.6 dBm */,            \
    0x41f0106 /* 16.8 dBm */,            \
    0x41f0106 /* 16.8 dBm */,            \
    0x41f0106 /* 16.8 dBm */,            \
    0x41f0107 /* 17.1 dBm */,            \
    0x41f0107 /* 17.1 dBm */,            \
    0x41f0108 /* 17.3 dBm */,            \
    0x41f0108 /* 17.3 dBm */,            \
    0x41f0109 /* 17.5 dBm */,            \
    0x41f010a /* 17.6 dBm */,            \
    0x41f010a /* 17.6 dBm */,            \
    0x41f010b /* 17.8 dBm */,            \
    0x41f010b /* 17.8 dBm */,            \
    0x41f010b /* 17.8 dBm */,            \
    0x41f010d /* 18.1 dBm */,            \
    0x41f010d /* 18.1 dBm */,            \
    0x41f010e /* 18.3 dBm */,            \
    0x41f010e /* 18.3 dBm */,            \
    0x41f010f /* 18.5 dBm */,            \
    0x41f010f /* 18.5 dBm */,            \
    0x41f010f /* 18.5 dBm */,            \
    0x41f010f /* 18.5 dBm */,            \
    0x41f0110 /* 18.9 dBm */,            \
    0x41f0111 /* 19.0 dBm */,            \
    0x41f0111 /* 19.0 dBm */,            \
    0x41f0112 /* 19.2 dBm */,            \
    0x41f0112 /* 19.2 dBm */,            \
    0x41f0113 /* 19.4 dBm */,            \
    0x41f0113 /* 19.4 dBm */,            \
    0x41f0114 /* 19.6 dBm */,            \
    0x41f0115 /* 19.7 dBm */,            \
    0x41f0116 /* 19.8 dBm */,            \
    0x41f0116 /* 19.8 dBm */,            \
    0x41f0117 /* 20.0 dBm */,            \
    0x41f0117 /* 20.0 dBm */,            \
    0x41f0118 /* 20.2 dBm */,            \
    0x41f0119 /* 20.3 dBm */,            \
    0x41f011a /* 20.4 dBm */,            \
    0x41f011b /* 20.5 dBm */,            \
    0x41f011b /* 20.5 dBm */,            \
    0x41f011c /* 20.7 dBm */,            \
    0x41f011d /* 20.8 dBm */,            \
    0x41f011e /* 20.9 dBm */,            \
    0x41f011f /* 21.0 dBm */,            \
    0x41f0201 /* 21.1 dBm */,            \
    0x41f0203 /* 21.2 dBm */,            \
    0x41f0205 /* 21.3 dBm */,            \
    0x41f0207 /* 21.4 dBm */,            \
    0x41f0209 /* 21.5 dBm */,            \
    0x41f020b /* 21.6 dBm */,            \
    0x41f020d /* 21.7 dBm */,            \
    0x41f020f /* 21.8 dBm */,            \
    0x41f0211 /* 21.9 dBm */,            \
    0x41f0213 /* 22.0 dBm */,            \
    0x41f0215 /* 22.1 dBm */,            \
    0x41f0217 /* 22.2 dBm */,            \
    0x41f0219 /* 22.3 dBm */,            \
    0x41f021b /* 22.4 dBm */,            \
    0x41f021d /* 22.5 dBm */,            \
    0x41f021f /* 22.6 dBm */,            \
    0x41f021f /* 22.6 dBm */,            \
    0x40b0104 /* 22.8 dBm */,            \
    0x40b0104 /* 22.8 dBm */,            \
    0x40b0105 /* 23.0 dBm */,            \
    0x40b0105 /* 23.0 dBm */,            \
    0x40b0106 /* 23.2 dBm */,            \
    0x40b0106 /* 23.2 dBm */,            \
    0x40b0107 /* 23.4 dBm */,            \
    0x40b0107 /* 23.4 dBm */,            \
    0x40b0108 /* 23.6 dBm */,            \
    0x40b0108 /* 23.6 dBm */,            \
    0x40b0109 /* 23.8 dBm */,            \
    0x40b010a /* 23.9 dBm */,            \
    0x40b010a /* 23.9 dBm */,            \
    0x40b010b /* 24.1 dBm */,            \
    0x40b010b /* 24.1 dBm */,            \
    0x40b010c /* 24.3 dBm */,            \
    0x40b010c /* 24.3 dBm */,            \
    0x40b010d /* 24.5 dBm */,            \
    0x40b010d /* 24.5 dBm */,            \
    0x40b010e /* 24.7 dBm */,            \
    0x40b010f /* 24.8 dBm */,            \
    0x40b010f /* 24.8 dBm */,            \
    0x40b010f /* 24.8 dBm */,            \
    0x40b010f /* 24.8 dBm */,            \
    0x40b0110 /* 25.2 dBm */,            \
    0x40b0110 /* 25.2 dBm */,            \
    0x40b0111 /* 25.4 dBm */,            \
    0x40b0112 /* 25.5 dBm */,            \
    0x40b0113 /* 25.6 dBm */,            \
    0x40b0113 /* 25.6 dBm */,            \
    0x40b0114 /* 25.8 dBm */,            \
    0x40b0115 /* 25.9 dBm */,            \
    0x40b0116 /* 26.0 dBm */,            \
    0x40b0116 /* 26.0 dBm */,            \
    0x40b0117 /* 26.2 dBm */,            \
    0x40b0117 /* 26.2 dBm */,            \
    0x40b0117 /* 26.2 dBm */,            \
    0x40b0118 /* 26.5 dBm */,            \
    0x40b0118 /* 26.5 dBm */,            \
    0x40b0119 /* 26.7 dBm */,            \
    0x40b011a /* 26.8 dBm */,            \
    0x40b011b /* 26.9 dBm */,            \
    0x40b011b /* 26.9 dBm */,            \
    0x40b011c /* 27.1 dBm */,            \
    0x40b011d /* 27.2 dBm */,            \
    0x40b011e /* 27.3 dBm */,            \
    0x40b011f /* 27.4 dBm */,            \
    0x40b0201 /* 27.5 dBm */,            \
    0x40b0203 /* 27.6 dBm */,            \
    0x40b0205 /* 27.7 dBm */,            \
    0x40b0207 /* 27.8 dBm */,            \
    0x40b0209 /* 27.9 dBm */,            \
    0x40b020b /* 28.0 dBm */,            \
    0x40b020d /* 28.1 dBm */,            \
    0x40b020f /* 28.2 dBm */,            \
    0x40b0211 /* 28.3 dBm */,            \
    0x40b0213 /* 28.4 dBm */,            \
    0x40b0217 /* 28.5 dBm */,            \
    0x40b0219 /* 28.6 dBm */,            \
    0x40b021b /* 28.7 dBm */,            \
    0x40b021d /* 28.8 dBm */,            \
    0x40b021f /* 28.9 dBm */,            \
    0x40b021f /* 28.9 dBm */,            \
    0x4030104 /* 29.1 dBm */,            \
    0x4030104 /* 29.1 dBm */,            \
    0x4030105 /* 29.3 dBm */,            \
    0x4030105 /* 29.3 dBm */,            \
    0x4030106 /* 29.5 dBm */,            \
    0x4030106 /* 29.5 dBm */,            \
    0x4030107 /* 29.7 dBm */,            \
    0x4030107 /* 29.7 dBm */,            \
    0x4030108 /* 29.9 dBm */,            \
    0x4030108 /* 29.9 dBm */,            \
    0x4030108 /* 29.9 dBm */,            \
    0x4030109 /* 30.2 dBm */,            \
    0x403010a /* 30.3 dBm */,            \
    0x403010a /* 30.3 dBm */,            \
    0x403010b /* 30.5 dBm */,            \
    0x403010b /* 30.5 dBm */,            \
    0x403010c /* 30.7 dBm */,            \
    0x403010c /* 30.7 dBm */,            \
    0x403010d /* 30.9 dBm */,            \
    0x403010e /* 31.0 dBm */,            \
    0x403010e /* 31.0 dBm */,            \
    0x403010f /* 31.2 dBm */,            \
    0x403010f /* 31.2 dBm */,            \
    0x4030110 /* 31.4 dBm */,            \
    0x4030110 /* 31.4 dBm */,            \
    0x4030111 /* 31.6 dBm */,            \
    0x4030111 /* 31.6 dBm */,            \
    0x4030112 /* 31.8 dBm */,            \
    0x4030113 /* 31.9 dBm */,            \
    0x4030113 /* 31.9 dBm */,            \
    0x4030114 /* 32.1 dBm */,            \
    0x4030115 /* 32.2 dBm */,            \
    0x4030116 /* 32.3 dBm */,            \
    0x4030117 /* 32.4 dBm */,            \
    0x4030117 /* 32.4 dBm */,            \
    0x4030118 /* 32.6 dBm */,            \
    0x4030119 /* 32.7 dBm */,            \
    0x403011a /* 32.8 dBm */,            \
    0x403011b /* 32.9 dBm */,            \
    0x403011c /* 33.0 dBm */,            \
    0x403011d /* 33.1 dBm */,            \
    0x403011e /* 33.2 dBm */,            \
    0x403011f /* 33.3 dBm */,            \
    0x4030201 /* 33.4 dBm */,            \
    0x4030203 /* 33.5 dBm */,            \
    0x4030207 /* 33.6 dBm */,            \
    0x4030209 /* 33.7 dBm */,            \
    0x403020b /* 33.8 dBm */,            \
    0x403020d /* 33.9 dBm */,            \
    0x4030211 /* 34.0 dBm */,            \
    0x4030213 /* 34.1 dBm */,            \
    0x4030217 /* 34.2 dBm */,            \
    0x4030219 /* 34.3 dBm */,            \
    0x403021d /* 34.4 dBm */,            \
    0x4000100 /* 34.5 dBm */,            \
    0x4000100 /* 34.5 dBm */,            \
    0x4000102 /* 34.7 dBm */,            \
    0x4000102 /* 34.7 dBm */,            \
    0x4000104 /* 34.9 dBm */,            \
    0x4000104 /* 34.9 dBm */,            \
    0x4000106 /* 35.1 dBm */,            \
    0x4000108 /* 35.2 dBm */,            \
    0x4000108 /* 35.2 dBm */,            \
    0x400010a /* 35.4 dBm */,            \
    0x400010c /* 35.5 dBm */,            \
    0x400010e /* 35.6 dBm */,            \
  }

#endif
// *INDENT-OFF*

#ifdef __cplusplus
}
#endif
