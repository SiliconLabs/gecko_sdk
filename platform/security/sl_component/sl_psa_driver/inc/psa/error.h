/***************************************************************************//**
 * # License
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is Third Party Software licensed by Silicon Labs from a third party
 * and is governed by the sections of the MSLA applicable to Third Party
 * Software and the additional terms set forth below.
 *
 ******************************************************************************/

#ifndef __SL_PSA_ERROR_H__
#define __SL_PSA_ERROR_H__

// Supplementary error codes for the SPM and RoT Services as defined in PSA
// Firmware Framework v1.0, which are not present in crypto_values.h. For non-
// TrustZone SKL builds, this file does not include anything at all. This is
// because our driver implementations only uses error codes that already exist
// in crypto_values.h.
#if defined(TFM_CONFIG_SL_SECURE_LIBRARY)
  #include "trusted-firmware-m/interface/include/psa/error.h"
#endif

#endif // __SL_PSA_ERROR_H__
