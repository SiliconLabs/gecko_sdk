/***************************************************************************//**
 * @file
 * @brief Application interface to the bootloader.
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "btl_interface.h"
#include "em_core.h"

static bool isInitialized = false;

void bootloader_getInfo(BootloaderInformation_t *info)
{
#if defined(BOOTLOADER_HAS_FIRST_STAGE)
  if (!bootloader_pointerToFirstStageValid(firstBootloaderTable)
      || !bootloader_pointerValid(mainBootloaderTable)) {
    // No bootloader is present (first stage or main stage invalid)
    info->type = NO_BOOTLOADER;
    info->capabilities = 0;
  } else if ((firstBootloaderTable->header.type == BOOTLOADER_MAGIC_FIRST_STAGE)
             && (mainBootloaderTable->header.type == BOOTLOADER_MAGIC_MAIN)) {
    info->type = SL_BOOTLOADER;
    info->version = mainBootloaderTable->header.version;
    info->capabilities = mainBootloaderTable->capabilities;
  } else {
    info->type = NO_BOOTLOADER;
    info->capabilities = 0;
  }
#else
  if (!bootloader_pointerValid(mainBootloaderTable)) {
    // No bootloader is present (first stage or main stage invalid)
    info->type = NO_BOOTLOADER;
    info->capabilities = 0;
  } else if (mainBootloaderTable->header.type == BOOTLOADER_MAGIC_MAIN) {
    info->type = SL_BOOTLOADER;
    info->version = mainBootloaderTable->header.version;
    info->capabilities = mainBootloaderTable->capabilities;
  } else {
    info->type = NO_BOOTLOADER;
    info->capabilities = 0;
  }
#endif
}

int32_t bootloader_init(void)
{
  int32_t retVal;
  bool isInitializedTemp;

  if (!bootloader_pointerValid(mainBootloaderTable)) {
    return BOOTLOADER_ERROR_INIT_TABLE;
  }

  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_ATOMIC();
  isInitializedTemp = isInitialized;
  isInitialized = true;
  CORE_EXIT_ATOMIC();

  if (isInitializedTemp == false) {
    retVal = mainBootloaderTable->init();
  } else {
    retVal = BOOTLOADER_OK;
  }
  return retVal;
}

int32_t bootloader_deinit(void)
{
  int32_t retVal;
  bool isInitializedTemp;

  if (!bootloader_pointerValid(mainBootloaderTable)) {
    return BOOTLOADER_ERROR_INIT_TABLE;
  }

  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_ATOMIC();
  isInitializedTemp = isInitialized;
  isInitialized = false;
  CORE_EXIT_ATOMIC();

  if (isInitializedTemp == true) {
    retVal = mainBootloaderTable->deinit();
  } else {
    retVal = BOOTLOADER_OK;
  }
  return retVal;
}

void bootloader_rebootAndInstall(void)
{
  // Set reset reason to bootloader entry
  BootloaderResetCause_t* resetCause = (BootloaderResetCause_t*) (RAM_MEM_BASE);
  resetCause->reason = BOOTLOADER_RESET_REASON_BOOTLOAD;
  resetCause->signature = BOOTLOADER_RESET_SIGNATURE_VALID;
#if defined(RMU_PRESENT)
  // Clear resetcause
  RMU->CMD = RMU_CMD_RCCLR;
  // Trigger a software system reset
  RMU->CTRL = (RMU->CTRL & ~_RMU_CTRL_SYSRMODE_MASK) | RMU_CTRL_SYSRMODE_FULL;
#endif
  NVIC_SystemReset();
}

int32_t bootloader_initParser(BootloaderParserContext_t *context,
                              size_t                    contextSize)
{
  if (!bootloader_pointerValid(mainBootloaderTable)) {
    return BOOTLOADER_ERROR_PARSE_FAILED;
  }
  return mainBootloaderTable->initParser(context, contextSize);
}

int32_t bootloader_parseBuffer(BootloaderParserContext_t   *context,
                               BootloaderParserCallbacks_t *callbacks,
                               uint8_t                     data[],
                               size_t                      numBytes)
{
  if (!bootloader_pointerValid(mainBootloaderTable)) {
    return BOOTLOADER_ERROR_PARSE_FAILED;
  }
  return mainBootloaderTable->parseBuffer(context, callbacks, data, numBytes);
}

int32_t bootloader_parseImageInfo(BootloaderParserContext_t *context,
                                  uint8_t                   data[],
                                  size_t                    numBytes,
                                  ApplicationData_t         *appInfo,
                                  uint32_t                  *bootloaderVersion)
{
  if (!bootloader_pointerValid(mainBootloaderTable)) {
    return BOOTLOADER_ERROR_PARSE_FAILED;
  }

  BootloaderInformation_t info = { .type = SL_BOOTLOADER, .version = 0U, .capabilities = 0U };
  bootloader_getInfo(&info);

  uint32_t blMajorVersion = ((info.version & BOOTLOADER_VERSION_MAJOR_MASK)
                             >> BOOTLOADER_VERSION_MAJOR_SHIFT);
  uint32_t blMinorVersion = ((info.version & BOOTLOADER_VERSION_MINOR_MASK)
                             >> BOOTLOADER_VERSION_MINOR_SHIFT);

  if ((blMajorVersion < 1UL) || (blMajorVersion == 1UL && blMinorVersion < 11UL)) {
    return BOOTLOADER_ERROR_PARSE_FAILED;
  }

  return mainBootloaderTable->parseImageInfo(context, data, numBytes, appInfo, bootloaderVersion);
}

uint32_t bootloader_parserContextSize(void)
{
  if (!bootloader_pointerValid(mainBootloaderTable)) {
    return 0UL;
  }

  BootloaderInformation_t info = { .type = SL_BOOTLOADER, .version = 0U, .capabilities = 0U };
  bootloader_getInfo(&info);

  uint32_t blMajorVersion = ((info.version & BOOTLOADER_VERSION_MAJOR_MASK)
                             >> BOOTLOADER_VERSION_MAJOR_SHIFT);
  uint32_t blMinorVersion = ((info.version & BOOTLOADER_VERSION_MINOR_MASK)
                             >> BOOTLOADER_VERSION_MINOR_SHIFT);

  if (blMajorVersion < 1UL) {
    return 384UL;
  }

  if (blMajorVersion == 1UL && blMinorVersion < 11UL) {
#if defined(_SILICON_LABS_32B_SERIES_2)
    if (blMinorVersion == 10UL) {
      return 524UL;
    } else {
      return 384UL;
    }
#else
    return 384UL;
#endif
  }

  return mainBootloaderTable->parserContextSize();
}

bool bootloader_verifyApplication(uint32_t startAddress)
{
  if (!bootloader_pointerValid(mainBootloaderTable)) {
    return false;
  }
  return mainBootloaderTable->verifyApplication(startAddress);
}

bool bootloader_secureBootEnforced(void)
{
  BootloaderInformation_t info = { .type = SL_BOOTLOADER, .version = 0U, .capabilities = 0U };
  bootloader_getInfo(&info);

  if (info.capabilities & BOOTLOADER_CAPABILITY_ENFORCE_SECURE_BOOT) {
    return true;
  }
  return false;
}

#if !defined(_SILICON_LABS_GECKO_INTERNAL_SDID_80)
uint32_t bootloader_remainingApplicationUpgrades(void)
{
  if (!bootloader_pointerValid(mainBootloaderTable)) {
    return 0UL;
  }

  BootloaderInformation_t info = { .type = SL_BOOTLOADER, .version = 0U, .capabilities = 0U };
  bootloader_getInfo(&info);

  uint32_t blMajorVersion = ((info.version & BOOTLOADER_VERSION_MAJOR_MASK)
                             >> BOOTLOADER_VERSION_MAJOR_SHIFT);
  uint32_t blMinorVersion = ((info.version & BOOTLOADER_VERSION_MINOR_MASK)
                             >> BOOTLOADER_VERSION_MINOR_SHIFT);

  if ((blMajorVersion < 1UL) || (blMajorVersion == 1UL && blMinorVersion < 11UL)) {
    return 0UL;
  }

  return mainBootloaderTable->remainingApplicationUpgrades();
}
#endif

#if defined(_SILICON_LABS_32B_SERIES_2)
bool bootloader_getCertificateVersion(uint32_t *version)
{
  // Access word 13 to read sl_app_properties of the bootloader.
  ApplicationProperties_t *blProperties =
    (ApplicationProperties_t *)(*(uint32_t *)(BTL_MAIN_STAGE_BASE + 52UL));

  if (!bootloader_pointerValid(blProperties)) {
    return false;
  }

  // Compatibility check of the application properties struct.
  if (((blProperties->structVersion & APPLICATION_PROPERTIES_VERSION_MAJOR_MASK)
       >> APPLICATION_PROPERTIES_VERSION_MAJOR_SHIFT) < 1UL) {
    return false;
  }
  if (((blProperties->structVersion & APPLICATION_PROPERTIES_VERSION_MINOR_MASK)
       >> APPLICATION_PROPERTIES_VERSION_MINOR_SHIFT) < 1UL) {
    return false;
  }

  if (blProperties->cert == NULL) {
    return false;
  }

  *version = blProperties->cert->version;
  return true;
}
#endif // _SILICON_LABS_32B_SERIES_2
