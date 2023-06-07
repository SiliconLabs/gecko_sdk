/***************************************************************************//**
 * @file
 * @brief NVM3 API definition (Device Specific).
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef NVM3_H
#define NVM3_H

#ifndef NVM3_HOST_BUILD
#include "em_device.h"
#endif

#include "nvm3_generic.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup nvm3
 * @{
 ******************************************************************************/

#define NVM3_MIN_FRAGMENT_COUNT         (2U)                            ///< The minimum number of fragments
#if defined(FLASH_PAGE_SIZE)
#define NVM3_MAX_OBJECT_SIZE_X          (NVM3_MAX_OBJECT_SIZE + 8)      // Adjust for an object header
#define FLASH_PAGE_SIZE_X               (FLASH_PAGE_SIZE - 20)          // Adjust for a page header
#define NVM3_FRAGMENT_COUNT             (((NVM3_MAX_OBJECT_SIZE_X - 1) / FLASH_PAGE_SIZE_X) + NVM3_MIN_FRAGMENT_COUNT)
#endif

typedef struct nvm3_ObjFrag {
  uint8_t              idx;                 // Fragment index
  bool                 isFirstFragFound;    // The object first fragment found
  bool                 isLastFragFound;     // The object last fragment found
#if defined(FLASH_PAGE_SIZE)
  nvm3_ObjFragDetail_t detail[NVM3_FRAGMENT_COUNT];
#else
  nvm3_ObjFragDetail_t detail[NVM3_MIN_FRAGMENT_COUNT];
#endif
} nvm3_ObjFrag_t;

typedef struct nvm3_Obj {
  nvm3_ObjectKey_t  key;          // The object key
  struct nvm3_Obj   *objAdr;      // The object pointer
  struct nvm3_Obj   *nextObjAdr;  // The next object pointer
  const void        *srcPtr;      // May be used to carry the source address of the data
  size_t            totalLen;     // The object total length
  uint8_t           objType;      // The object type
  bool              isHdrValid;   // The object header is valid
  bool              isValid;      // The object is valid
  bool              isFragmented; // The object is fragmented
  nvm3_ObjFrag_t    frag;         // The object fragment information
} nvm3_Obj_t;

// Definition of NVM3 variables
/// @brief A variable used by the NVM3 functions.
extern nvm3_Obj_t nvm3_internalObjectHandleA;
/// @brief A variable used by the NVM3 functions.
extern nvm3_Obj_t nvm3_internalObjectHandleB;
/// @brief A variable used by the NVM3 functions.
extern nvm3_Obj_t nvm3_internalObjectHandleC;
/// @brief A variable used by the NVM3 functions.
extern nvm3_Obj_t nvm3_internalObjectHandleD;
/// @brief A variable that must contain the maximum number of object fragments.
extern const uint8_t  nvm3_maxFragmentCount;
/// @brief A variable containing the object handle size in bytes.
extern const size_t   nvm3_objHandleSize;

#ifdef __cplusplus
}
#endif

/// @} end group nvm3 ****************************************************/

#endif /* NVM3_H */
