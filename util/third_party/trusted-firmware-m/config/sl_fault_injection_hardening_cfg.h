/***************************************************************************//**
 * @file
 * @brief Configuration header of Fault Injection Hardening Library
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc.  Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement.  This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
#ifndef FAULT_INJECTION_HARDENING_CFG_H
#define FAULT_INJECTION_HARDENING_CFG_H

// <<< Use Configuration Wizard in Context Menu >>>
// <h> Fault Injection Profile Configuration

// <e SL_TFM_FIH_PROFILE_ON> Enable TFM Fault Injection Hardening Profile
// <i> Default: 0
// <i> Enforce TFM Fault Injection Hardening Profile ON in the firmware
//     TZ bootloader applies the FI hardening to critical bootloader functions.
//     TZ Secure Key Library initialisation applies FI hardening to secure that the TZ configuration is securely setup before jumping to the NonSecure application
#define SL_TFM_FIH_PROFILE_ON         0

#if defined(SL_TFM_FIH_PROFILE_ON) && (SL_TFM_FIH_PROFILE_ON == 1)
#define TFM_FIH_PROFILE_ON
#endif

// <q SL_TFM_FIH_PROFILE_LOW> TFM Fault Injection Hardening Profile as Low.
// <i> Default: 0
// <i> enabled. Configures the TFM Fault Injection Hardening profile as low.
//              Includes FIH_ENABLE_GLOBAL_FAIL (hardens the mitigations against the loop)
//              Includes FIH_ENABLE_CFI (Control Flow Integrity) creates a global counter that is
//              incremented before every FIH_CALL of vulnerable functions. On the function
//              return the counter is decremented, and after the return it is verified that
//              the counter has the same value as before this process.
#define SL_TFM_FIH_PROFILE_LOW        0

#if defined(SL_TFM_FIH_PROFILE_LOW) && (SL_TFM_FIH_PROFILE_LOW == 1)
#define TFM_FIH_PROFILE_LOW
#endif

// <q SL_TFM_FIH_PROFILE_MEDIUM> TFM Fault Injection Hardening Profile as Medium.
// <i> Default: 0
// <i> enabled. Configures the TFM Fault Injection Hardening profile as medium.
//              Includes FIH_ENABLE_DOUBLE_VARS makes critical variables into a tuple (x, x ^ msk).
//              Then the correctness of x can be checked by XORing the two tuple values together.
//              This also means that comparisons between fih_ints can be verified
//              by doing x == y && x_msk == y_msk.
//              Includes FIH_ENABLE_GLOBAL_FAIL (hardens the mitigations against the loop)
//              Includes FIH_ENABLE_CFI (Control Flow Integrity) creates a global counter that is
//              incremented before every FIH_CALL of vulnerable functions. On the function
//              return the counter is decremented, and after the return it is verified that
//              the counter has the same value as before this process.
#define SL_TFM_FIH_PROFILE_MEDIUM                    0

#if defined(SL_TFM_FIH_PROFILE_MEDIUM) && (SL_TFM_FIH_PROFILE_MEDIUM == 1)
#define TFM_FIH_PROFILE_MEDIUM
#endif

// <q SL_TFM_FIH_PROFILE_HIGH> TFM Fault Injection Hardening Profile as High.
// <i> Default: 0
// <i> enabled. Configures the TFM Fault Injection Hardening profile as high.
//              Includes FIH_ENABLE_DELAY causes random delays. This makes it hard to cause faults precisely
//              Includes FIH_ENABLE_DOUBLE_VARS makes critical variables into a tuple (x, x ^ msk).
//              Then the correctness of x can be checked by XORing the two tuple values together.
//              This also means that comparisons between fih_ints can be verified
//              by doing x == y && x_msk == y_msk.
//              Includes FIH_ENABLE_GLOBAL_FAIL (hardens the mitigations against the loop)
//              Includes FIH_ENABLE_CFI (Control Flow Integrity) creates a global counter that is
//              incremented before every FIH_CALL of vulnerable functions. On the function
//              return the counter is decremented, and after the return it is verified that
//              the counter has the same value as before this process.
#define SL_TFM_FIH_PROFILE_HIGH         0

#if defined(SL_TFM_FIH_PROFILE_HIGH) && (SL_TFM_FIH_PROFILE_HIGH == 1)
#define TFM_FIH_PROFILE_HIGH
#endif

// </e>

// </h>

// <<< end of configuration section >>>
#if defined(TFM_FIH_PROFILE_ON)
  #if (defined(TFM_FIH_PROFILE_LOW) && defined(TFM_FIH_PROFILE_MEDIUM) && defined(TFM_FIH_PROFILE_HIGH))
    #error "Choose either TFM fault injection hardening profile as LOW or Medium or High"
  #endif // TFM_FIH_PROFILE_LOW && TFM_FIH_PROFILE_MEDIUM && TFM_FIH_PROFILE_HIGH

  #if (defined(TFM_FIH_PROFILE_LOW) && !defined(TFM_FIH_PROFILE_MEDIUM) && defined(TFM_FIH_PROFILE_HIGH))
    #error "Choose either TFM fault injection hardening profile as LOW or Medium or High"
  #endif // TFM_FIH_PROFILE_LOW && !TFM_FIH_PROFILE_MEDIUM && TFM_FIH_PROFILE_HIGH

  #if (defined(TFM_FIH_PROFILE_LOW) && defined(TFM_FIH_PROFILE_MEDIUM) && !defined(TFM_FIH_PROFILE_HIGH))
    #error "Choose either TFM fault injection hardening profile as LOW or Medium or High"
  #endif // TFM_FIH_PROFILE_LOW && TFM_FIH_PROFILE_MEDIUM && !TFM_FIH_PROFILE_HIGH

  #if (!defined(TFM_FIH_PROFILE_LOW) && defined(TFM_FIH_PROFILE_MEDIUM) && defined(TFM_FIH_PROFILE_HIGH))
    #error "Choose either TFM fault injection hardening profile as LOW or Medium or High"
  #endif // !TFM_FIH_PROFILE_LOW && TFM_FIH_PROFILE_MEDIUM && TFM_FIH_PROFILE_HIGH
#endif // TFM_FIH_PROFILE_ON
#endif // FAULT_INJECTION_HARDENING_CFG_H
