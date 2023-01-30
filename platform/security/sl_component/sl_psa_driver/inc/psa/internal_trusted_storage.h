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
/** \file internal_trusted_storage.h
 * \brief Interface and declarations of trusted storage.
 */

#ifndef INTERNAL_TRUSTED_STORAGE_H
#define INTERNAL_TRUSTED_STORAGE_H

// We need to add condition for TFM internal_trusted_storage.h, in case that
// -cp option is not selected.
#if defined(SL_TRUSTZONE_SECURE)
#include "trusted-firmware-m/interface/include/psa/internal_trusted_storage.h"
#else
#include "psa_crypto_its.h"
#include "sli_internal_trusted_storage.h"
#endif

#endif /* INTERNAL_TRUSTED_STORAGE_H */
