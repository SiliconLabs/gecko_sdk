/*
 * Copyright (c) 2019, Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef __ATTEST_EAT_DEFINES_H__
#define __ATTEST_EAT_DEFINES_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined(TFM_CONFIG_SL_SECURE_LIBRARY)

// http://arm.com/psa/2.0.0 profile

#define EAT_CBOR_ARM_LABEL_CHALLENGE            (10u)
#define EAT_CBOR_ARM_LABEL_UEID                 (256u)
#define EAT_CBOR_ARM_LABEL_PROFILE_DEFINITION   (265u)
#define EAT_CBOR_ARM_RANGE_BASE                 (2394u)
#define EAT_CBOR_ARM_LABEL_CLIENT_ID            (EAT_CBOR_ARM_RANGE_BASE)
#define EAT_CBOR_ARM_LABEL_SECURITY_LIFECYCLE   (EAT_CBOR_ARM_RANGE_BASE + 1u)
#define EAT_CBOR_ARM_LABEL_IMPLEMENTATION_ID    (EAT_CBOR_ARM_RANGE_BASE + 2u)
#define EAT_CBOR_ARM_LABEL_BOOT_SEED            (EAT_CBOR_ARM_RANGE_BASE + 3u)
#define EAT_CBOR_ARM_LABEL_HW_VERSION           (EAT_CBOR_ARM_RANGE_BASE + 4u)
#define EAT_CBOR_ARM_LABEL_SW_COMPONENTS        (EAT_CBOR_ARM_RANGE_BASE + 5u)
#define EAT_CBOR_ARM_LABEL_ORIGINATION          (EAT_CBOR_ARM_RANGE_BASE + 6u)

#else

#define EAT_CBOR_ARM_RANGE_BASE                 (-75000)
#define EAT_CBOR_ARM_LABEL_PROFILE_DEFINITION   (EAT_CBOR_ARM_RANGE_BASE - 0)
#define EAT_CBOR_ARM_LABEL_CLIENT_ID            (EAT_CBOR_ARM_RANGE_BASE - 1)
#define EAT_CBOR_ARM_LABEL_SECURITY_LIFECYCLE   (EAT_CBOR_ARM_RANGE_BASE - 2)
#define EAT_CBOR_ARM_LABEL_IMPLEMENTATION_ID    (EAT_CBOR_ARM_RANGE_BASE - 3)
#define EAT_CBOR_ARM_LABEL_BOOT_SEED            (EAT_CBOR_ARM_RANGE_BASE - 4)
#define EAT_CBOR_ARM_LABEL_HW_VERSION           (EAT_CBOR_ARM_RANGE_BASE - 5)
#define EAT_CBOR_ARM_LABEL_SW_COMPONENTS        (EAT_CBOR_ARM_RANGE_BASE - 6)
#define EAT_CBOR_ARM_LABEL_NO_SW_COMPONENTS     (EAT_CBOR_ARM_RANGE_BASE - 7)
#define EAT_CBOR_ARM_LABEL_CHALLENGE            (EAT_CBOR_ARM_RANGE_BASE - 8)
#define EAT_CBOR_ARM_LABEL_UEID                 (EAT_CBOR_ARM_RANGE_BASE - 9)
#define EAT_CBOR_ARM_LABEL_ORIGINATION          (EAT_CBOR_ARM_RANGE_BASE - 10)

#endif // TFM_CONFIG_SL_SECURE_LIBRARY

#define EAT_CBOR_SW_COMPONENT_MEASUREMENT_TYPE  (1)
#define EAT_CBOR_SW_COMPONENT_MEASUREMENT_VALUE (2)
/* Reserved                                     (3) */
#define EAT_CBOR_SW_COMPONENT_VERSION           (4)
#define EAT_CBOR_SW_COMPONENT_SIGNER_ID         (5)
#define EAT_CBOR_SW_COMPONENT_MEASUREMENT_DESC  (6)

/* Indicates that the boot status intentionally (i.e. boot loader does not
 * capable to produce it) does not contain any SW components' measurement.
 * Required integer value for claim labeled EAT_CBOR_ARM_LABEL_NO_SW_COMPONENTS.
 */
#define NO_SW_COMPONENT_FIXED_VALUE 1

#ifdef __cplusplus
}
#endif

#endif /* __ATTEST_EAT_DEFINES_H__ */
