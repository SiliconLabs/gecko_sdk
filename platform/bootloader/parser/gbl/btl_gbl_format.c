/***************************************************************************//**
 * @file
 * @brief Definitions for the Silicon Labs GBL format
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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
#include <stddef.h>

#include "config/btl_config.h"

#include "core/btl_util.h"

#include "parser/gbl/btl_gbl_parser.h"
#include "parser/gbl/btl_gbl_format.h"

MISRAC_DISABLE
#include "em_device.h"
MISRAC_ENABLE

// -----------------------------------------------------------------------------
// Structs

// Array of parsing info structs for all the supported tags
const GblTagParsingInfo_t gblTagParsingInfoStructs[] = {
  // GBL Header Tag
  {
    .tagId       = GBL_TAG_ID_HEADER_V3,
    .parserState = GblParserStateHeader,
    .tagOrder    = GBL_TAG_ORDER_HEADER_V3,
    .reserved    = 0U,
    .flags       = GBL_TAG_FLAG_SINGLE_OCCURRENCE_ONLY
                   | GBL_TAG_FLAG_ALWAYS_UNENCRYPTED
  },

#if defined(BTL_PARSER_SUPPORT_VERSION_DEPENDENCY_TAG)
  // GBL Version Dependency Tag
  {
    .tagId       = GBL_TAG_ID_VERSION_DEPENDENCY,
    .parserState = GblParserStateVersionDependency,
    .tagOrder    = GBL_TAG_ORDER_VERSION_DEPENDENCY,
    .reserved    = 0U,
    .flags       = GBL_TAG_FLAG_ALWAYS_UNENCRYPTED
  },
#endif

#ifndef BTL_PARSER_NO_SUPPORT_ENCRYPTION
  // GBL Encryption Init Tag
  {
    .tagId       = GBL_TAG_ID_ENC_INIT,
    .parserState = GblParserStateEncryptionInit,
    .tagOrder    = GBL_TAG_ORDER_ENC_INIT,
    .reserved    = 0U,
    .flags       = GBL_TAG_FLAG_SINGLE_OCCURRENCE_ONLY
                   | GBL_TAG_FLAG_ALWAYS_UNENCRYPTED
  },
#endif

  // GBL Application Tag
  {
    .tagId       = GBL_TAG_ID_APPLICATION,
    .parserState = GblParserStateApplication,
    .tagOrder    = GBL_TAG_ORDER_APPLICATION,
    .reserved    = 0U,
    .flags       = GBL_TAG_FLAG_SINGLE_OCCURRENCE_ONLY
  },

#if defined(_SILICON_LABS_32B_SERIES_2)
  // GBL SE Upgrade Tag
  {
    .tagId       = GBL_TAG_ID_SE_UPGRADE,
    .parserState = GblParserStateSe,
    .tagOrder    = GBL_TAG_ORDER_SE_UPGRADE,
    .reserved    = 0U,
    .flags       = GBL_TAG_FLAG_SINGLE_OCCURRENCE_ONLY
#if defined(BOOTLOADER_SE_UPGRADE_NO_STAGING) \
                   && (BOOTLOADER_SE_UPGRADE_NO_STAGING == 1)
                   | GBL_TAG_FLAG_ALWAYS_UNENCRYPTED
#endif // defined(BOOTLOADER_SE_UPGRADE_NO_STAGING)
  },
#endif // defined(_SILICON_LABS_32B_SERIES_2)

  // GBL Bootloader Tag
  {
    .tagId       = GBL_TAG_ID_BOOTLOADER,
    .parserState = GblParserStateBootloader,
    .tagOrder    = GBL_TAG_ORDER_BOOTLOADER,
    .reserved    = 0U,
    .flags       = GBL_TAG_FLAG_SINGLE_OCCURRENCE_ONLY
  },

  // GBL Metadata Tag
  {
    .tagId       = GBL_TAG_ID_METADATA,
    .parserState = GblParserStateMetadata,
    .tagOrder    = GBL_TAG_ORDER_PROG_AND_METADATA,
    .reserved    = 0U,
    .flags       = 0U
  },

  // GBL Prog Tag
  {
    .tagId       = GBL_TAG_ID_PROG,
    .parserState = GblParserStateProg,
    .tagOrder    = GBL_TAG_ORDER_PROG_AND_METADATA,
    .reserved    = 0U,
    .flags       = 0U
  },

  // GBL EraseProg Tag
  {
    .tagId       = GBL_TAG_ID_ERASEPROG,
    .parserState = GblParserStateEraseProg,
    .tagOrder    = GBL_TAG_ORDER_PROG_AND_METADATA,
    .reserved    = 0U,
    .flags       = 0U
  },

#if defined(BTL_PARSER_SUPPORT_LZ4)
  // GBL Prog Tag (LZ4)
  {
    .tagId       = GBL_TAG_ID_PROG_LZ4,
    .parserState = GblParserStateCustomTag,
    .tagOrder    = GBL_TAG_ORDER_PROG_AND_METADATA,
    .reserved    = 0U,
    .flags       = 0U
  },
#endif

#if defined(BTL_PARSER_SUPPORT_LZMA)
  // GBL Prog Tag (LZMA)
  {
    .tagId       = GBL_TAG_ID_PROG_LZMA,
    .parserState = GblParserStateCustomTag,
    .tagOrder    = GBL_TAG_ORDER_PROG_AND_METADATA,
    .reserved    = 0U,
    .flags       = 0U
  },
#endif

#ifndef BTL_PARSER_NO_SUPPORT_ENCRYPTION
  // GBL Encryption Data Tag
  {
    .tagId       = GBL_TAG_ID_ENC_GBL_DATA,
    .parserState = GblParserStateEncryptionContainer,
    .tagOrder    = GBL_TAG_ORDER_ENC_GBL_DATA,
    .reserved    = 0U,
    .flags       = GBL_TAG_FLAG_ALWAYS_UNENCRYPTED
  },
#endif

#if defined(_SILICON_LABS_32B_SERIES_2)
  // GBL Certificate Tag
  {
    .tagId       = GBL_TAG_ID_CERTIFICATE_ECDSA_P256,
    .parserState = GblParserStateCertificate,
    .tagOrder    = GBL_TAG_ORDER_CERTIFICATE,
    .reserved    = 0U,
    .flags       = GBL_TAG_FLAG_SINGLE_OCCURRENCE_ONLY
                   | GBL_TAG_FLAG_ALWAYS_UNENCRYPTED
  },
#endif

  // GBL Signature Tag
  {
    .tagId       = GBL_TAG_ID_SIGNATURE_ECDSA_P256,
    .parserState = GblParserStateSignature,
    .tagOrder    = GBL_TAG_ORDER_SIGNATURE,
    .reserved    = 0U,
    .flags       = GBL_TAG_FLAG_SINGLE_OCCURRENCE_ONLY
                   | GBL_TAG_FLAG_ALWAYS_UNENCRYPTED
  },

  // GBL End Tag
  {
    .tagId       = GBL_TAG_ID_END,
    .parserState = GblParserStateFinalize,
    .tagOrder    = GBL_TAG_ORDER_END,
    .reserved    = 0U,
    .flags       = GBL_TAG_FLAG_SINGLE_OCCURRENCE_ONLY
                   | GBL_TAG_FLAG_ALWAYS_UNENCRYPTED
  }
};

// -----------------------------------------------------------------------------
// Functions

/***************************************************************************//**
 * Function for looking up and retrieving the parsing information struct
 * associated with a particular GBL tag type / tag ID.
 *
 * @param[in] tagId The tag ID to be looked up.
 * @returns A pointer to the GblTagParsingInfo_t struct associated with tagId,
 *          or a NULL pointer if the provided tagId cannot be found.
 ******************************************************************************/
const GblTagParsingInfo_t* gbl_getTagParsingInfoFromTagId(uint32_t tagId)
{
  const size_t numElements = sizeof(gblTagParsingInfoStructs)
                             / sizeof(GblTagParsingInfo_t);
  for (size_t i = 0; i < numElements; i++) {
    if (gblTagParsingInfoStructs[i].tagId == tagId) {
      return &gblTagParsingInfoStructs[i];
    }
  }
  return NULL; // Could not find struct corresponding to the given tagId
}
