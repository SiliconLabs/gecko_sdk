/***************************************************************************//**
 * @file
 * @brief Main file for Main Bootloader.
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

#include "config/btl_config.h"
#include "api/btl_interface.h"

#include "core/btl_core.h"
#include "core/btl_helper.h"
#include "core/btl_reset.h"
#include "core/btl_parse.h"
#include "core/btl_bootload.h"
#include "core/btl_upgrade.h"

#include "debug/btl_debug.h"

#ifdef BTL_GPIO_ACTIVATION
#include "gpio/gpio-activation/btl_gpio_activation.h"
#endif

#ifdef BTL_EZSP_GPIO_ACTIVATION
#include "gpio/ezsp-gpio-activation/btl_ezsp_gpio_activation.h"
#endif

#ifdef BOOTLOADER_SUPPORT_STORAGE
#include "storage/btl_storage.h"
#include "storage/bootloadinfo/btl_storage_bootloadinfo.h"
#endif

#ifdef BOOTLOADER_SUPPORT_COMMUNICATION
#include "communication/btl_communication.h"
#endif

#include "em_device.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_chip.h"
#if defined(_SILICON_LABS_32B_SERIES_2)
#include "fih.h"
#endif
#if defined(__GNUC__)
#define ROM_END_SIZE 0
extern const size_t __rom_end__;
#elif defined(__ICCARM__)
#define ROM_END_SIZE 4
const size_t __rom_end__ @ "ROM_SIZE";
#endif

// -----------------------------------------------------------------------------
// Test Functions

#if defined(TEST_BOOTLOADER_RAM_CLEAN_UP)
extern void ram_clean_up_test(void);
#endif

// --------------------------------
// Local function declarations

__STATIC_INLINE bool enterBootloader(void);
SL_NORETURN static void bootToApp(uint32_t);

#if defined(BOOTLOADER_INTERFACE_TRUSTZONE_AWARE)
static void btl_getPeripheralList(uint32_t *ppusatd0, uint32_t *ppusatd1);
#endif // BOOTLOADER_INTERFACE_TRUSTZONE_AWARE

#if defined(BOOTLOADER_WRITE_DISABLE) && (BOOTLOADER_WRITE_DISABLE == 1)
__STATIC_INLINE void lockBootloaderArea(void)
{
  // Disable write access to bootloader.
  // Prevents application from touching the bootloader.
#if defined(_MSC_PAGELOCK0_MASK)
#if defined(_CMU_CLKEN1_MASK)
  CMU->CLKEN1_SET = CMU_CLKEN1_MSC;
#endif

  uint32_t num_pages = (BTL_MAIN_STAGE_MAX_SIZE + BTL_FIRST_STAGE_SIZE) / FLASH_PAGE_SIZE;
  uint32_t pagelock = ~0;
  pagelock = pagelock >> (32 - num_pages);
  MSC->PAGELOCK0_SET = pagelock;

#if defined(_CMU_CLKEN1_MASK)
  CMU->CLKEN1_CLR = CMU_CLKEN1_MSC;
#endif
#elif defined(MSC_BOOTLOADERCTRL_BLWDIS)
  MSC->BOOTLOADERCTRL |= MSC_BOOTLOADERCTRL_BLWDIS;
#else
  // Do nothing
#endif
}
#endif

#if defined(BOOTLOADER_APPLOADER) || defined(_SILICON_LABS_32B_SERIES_2_CONFIG_5) || defined(_SILICON_LABS_32B_SERIES_2_CONFIG_8)
__STATIC_INLINE void configureSMUToDefault(void)
{
#if defined(CMU_CLKEN1_SMU)
  CMU->CLKEN1_SET = CMU_CLKEN1_SMU;
#endif

  // Config all peripherals to Secure
  SMU->PPUSATD0_SET = _SMU_PPUSATD0_MASK;
  SMU->PPUSATD1_SET = _SMU_PPUSATD1_MASK;

  // SAU treats all access as secure
#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  SAU->CTRL = 0;
  __DSB();
  __ISB();
#else
  #error "The startup code requires access to the CMSE toolchain extension to set proper SAU settings."
#endif // __ARM_FEATURE_CMSE

  // Clear and disable the SMU PPUSEC and BMPUSEC interrupt.
  NVIC_DisableIRQ(SMU_SECURE_IRQn);
  SMU->IEN_CLR = SMU_IEN_PPUSEC | SMU_IEN_BMPUSEC;
  NVIC_ClearPendingIRQ(SMU_SECURE_IRQn);
  SMU->IF_CLR = SMU_IF_PPUSEC | SMU_IF_BMPUSEC;

#if defined(CMU_CLKEN1_SMU)
  CMU->CLKEN1_CLR = CMU_CLKEN1_SMU;
#endif
}
#endif // BOOTLOADER_APPLOADER || _SILICON_LABS_32B_SERIES_2_CONFIG_5 || _SILICON_LABS_32B_SERIES_2_CONFIG_8

#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_5) || defined(_SILICON_LABS_32B_SERIES_2_CONFIG_8)
__STATIC_INLINE void configureSMU(void)
{
#if defined(CMU_CLKEN1_SMU)
  CMU->CLKEN1_SET = CMU_CLKEN1_SMU;
#endif

  // Config GPIO as Non-Secure.
  SMU->PPUSATD0_CLR = SMU_PPUSATD0_GPIO;

  // SAU treats all accesses as non-secure
#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  SAU->CTRL = SAU_CTRL_ALLNS_Msk;
  __DSB();
  __ISB();
#else
  #error "The startup code requires access to the CMSE toolchain extension to set proper SAU settings."
#endif // __ARM_FEATURE_CMSE

  // Clear and Enable the SMU PPUSEC and BMPUSEC interrupt.
  NVIC_ClearPendingIRQ(SMU_SECURE_IRQn);
  SMU->IF_CLR = SMU_IF_PPUSEC | SMU_IF_BMPUSEC;
  NVIC_EnableIRQ(SMU_SECURE_IRQn);
  SMU->IEN = SMU_IEN_PPUSEC | SMU_IEN_BMPUSEC;

#if defined(CMU_CLKEN1_SMU)
  CMU->CLKEN1_CLR = CMU_CLKEN1_SMU;
#endif
}
#endif // _SILICON_LABS_32B_SERIES_2_CONFIG_5 | _SILICON_LABS_32B_SERIES_2_CONFIG_8

void HardFault_Handler(void)
{
  BTL_DEBUG_PRINTLN("Fault          ");
  reset_resetWithReason(BOOTLOADER_RESET_REASON_FATAL);
}

// Main Bootloader implementation

int main(void)
{
  int32_t ret = BOOTLOADER_ERROR_STORAGE_BOOTLOAD;
  CHIP_Init();
  BTL_DEBUG_PRINTLN("BTL entry");

#if defined(EMU_CMD_EM01VSCALE2) && defined(EMU_STATUS_VSCALEBUSY)
  // Device supports voltage scaling, and the bootloader may have been entered
  // with a downscaled voltage. Scale voltage up to allow flash programming.
  if ((EMU->STATUS & EMU_STATUS_VSCALE_VSCALE2) != EMU_STATUS_VSCALE_VSCALE2) {
    EMU->CMD = EMU_CMD_EM01VSCALE2;
    while (EMU->STATUS & EMU_STATUS_VSCALEBUSY) {
      // Do nothing
    }
  }
#endif

  btl_init();

#ifdef BOOTLOADER_SUPPORT_STORAGE
  if (!reset_resetCounterEnabled()) {
    // Storage bootloaders might use part of the reason signature as a counter,
    // so only invalidate the signature when the counter is not in use.
    reset_invalidateResetReason();
  }
#else
  reset_invalidateResetReason();
#endif

#ifdef BOOTLOADER_SUPPORT_STORAGE
  // If the bootloader supports storage, first attempt to apply an existing
  // image from storage.
  ret = storage_main();

  if (ret == BOOTLOADER_OK) {
    // Firmware upgrade from storage successful. Disable the reset counter
    // and return to application
    if (reset_resetCounterEnabled()) {
      reset_disableResetCounter();
    }
    reset_resetWithReason(BOOTLOADER_RESET_REASON_GO);
  } else {
    if (!reset_resetCounterEnabled()) {
      // Start counting the number of consecutive resets after the first reset
      reset_enableResetCounter();
    }

    // Stop after three consecutive resets (the first one counts as 0)
    if (reset_getResetCounter() >= 2) {
      // If the system is not able to recover from a fault like BADAPP or
      // BADIMAGE, wait in a busy loop to ease reflashing and debugging.
      BTL_DEBUG_PRINTLN("Reset loop detected. Stopping...");
      reset_invalidateResetReason();
      while (1) {
        // Wait...
      }
    } else {
      reset_incrementResetCounter();
    }

    // Wait a short while (approx. 500 ms) before continuing.
    // This allows other operations to complete before the reset.
    for (volatile int i = 800000; i > 0; i--) {
      // Do nothing
    }
  }
#endif

#ifdef BOOTLOADER_SUPPORT_COMMUNICATION
  communication_init();

  ret = communication_start();
  if (ret != BOOTLOADER_OK) {
    reset_resetWithReason(BOOTLOADER_RESET_REASON_FATAL);
  }

  ret = communication_main();
  BTL_DEBUG_PRINT("Protocol returned ");
  BTL_DEBUG_PRINT_WORD_HEX(ret);
  BTL_DEBUG_PRINT_LF();

  communication_shutdown();

  if ((ret == BOOTLOADER_OK)
      || (ret == BOOTLOADER_ERROR_COMMUNICATION_DONE)) {
    reset_resetWithReason(BOOTLOADER_RESET_REASON_GO);
  }
#endif // BOOTLOADER_SUPPORT_COMMUNICATION

  // An error occurred in storage or communication, and a firmware upgrade
  // was not performed
  if (0
#ifdef BOOTLOADER_SUPPORT_COMMUNICATION
      || (ret == BOOTLOADER_ERROR_COMMUNICATION_IMAGE_ERROR)
      || (ret == BOOTLOADER_ERROR_COMMUNICATION_TIMEOUT)
#endif
#ifdef BOOTLOADER_SUPPORT_STORAGE
      || (ret == BOOTLOADER_ERROR_STORAGE_BOOTLOAD)
#endif
      ) {
    reset_resetWithReason(BOOTLOADER_RESET_REASON_BADIMAGE);
  } else {
    reset_resetWithReason(BOOTLOADER_RESET_REASON_FATAL);
  }

  return 0;
}

#ifdef BOOTLOADER_SUPPORT_STORAGE
extern const BootloaderStorageFunctions_t storageFunctions;
#endif

const MainBootloaderTable_t mainStageTable = {
  {
    .type = BOOTLOADER_MAGIC_MAIN,
    .layout = BOOTLOADER_HEADER_VERSION_MAIN,
    .version = BOOTLOADER_VERSION_MAIN
  },
  // Bootloader size is the relative address of the end variable plus 4 for the
  // CRC
  .size = ((uint32_t)&__rom_end__) - BTL_MAIN_STAGE_BASE + ROM_END_SIZE + 4,
  .startOfAppSpace = (BareBootTable_t *)(BTL_APPLICATION_BASE),
  .endOfAppSpace = (void *)(BTL_APPLICATION_BASE + BTL_APP_SPACE_SIZE),
  .capabilities = (0
#if defined(BOOTLOADER_ENFORCE_SIGNED_UPGRADE) && (BOOTLOADER_ENFORCE_SIGNED_UPGRADE == 1)
                   | BOOTLOADER_CAPABILITY_ENFORCE_UPGRADE_SIGNATURE
#endif
#if defined(BOOTLOADER_ENFORCE_ENCRYPTED_UPGRADE) && (BOOTLOADER_ENFORCE_ENCRYPTED_UPGRADE == 1)
                   | BOOTLOADER_CAPABILITY_ENFORCE_UPGRADE_ENCRYPTION
#endif
#if defined(BOOTLOADER_ENFORCE_SECURE_BOOT) && (BOOTLOADER_ENFORCE_SECURE_BOOT == 1)
                   | BOOTLOADER_CAPABILITY_ENFORCE_SECURE_BOOT
#endif
#if defined(BOOTLOADER_SUPPORT_CERTIFICATES) && (BOOTLOADER_SUPPORT_CERTIFICATES == 1)
                   | BOOTLOADER_CAPABILITY_ENFORCE_CERTIFICATE_SECURE_BOOT
#endif
#if defined(BOOTLOADER_ROLLBACK_PROTECTION) && (BOOTLOADER_ROLLBACK_PROTECTION == 1)
                   | BOOTLOADER_CAPABILITY_ROLLBACK_PROTECTION
#endif
                   | BOOTLOADER_CAPABILITY_BOOTLOADER_UPGRADE
                   | BOOTLOADER_CAPABILITY_GBL
                   | BOOTLOADER_CAPABILITY_GBL_SIGNATURE
#if !defined(BTL_PARSER_NO_SUPPORT_ENCRYPTION)
                   | BOOTLOADER_CAPABILITY_GBL_ENCRYPTION
#endif
#if defined(BOOTLOADER_SUPPORT_STORAGE) && (BOOTLOADER_SUPPORT_STORAGE == 1)
                   | BOOTLOADER_CAPABILITY_STORAGE
#endif
#if defined(BOOTLOADER_SUPPORT_COMMUNICATION) && (BOOTLOADER_SUPPORT_COMMUNICATION == 1)
                   | BOOTLOADER_CAPABILITY_COMMUNICATION
#endif
#if defined(BOOTLOADER_INTERFACE_TRUSTZONE_AWARE)
                   | BOOTLOADER_CAPABILITY_PERIPHERAL_LIST
#endif
                   ),
  .init = &btl_init,
  .deinit = &btl_deinit,
  .verifyApplication = &bootload_verifyApplication,
  .initParser = &core_initParser,
  .parseBuffer = &core_parseBuffer,
#if defined(BOOTLOADER_SUPPORT_STORAGE) && (BOOTLOADER_SUPPORT_STORAGE == 1)
  .storage = &storageFunctions,
#else
  .storage = NULL,
#endif
  .parseImageInfo = core_parseImageInfo,
  .parserContextSize = core_parserContextSize,
#if defined(BOOTLOADER_ROLLBACK_PROTECTION) && (BOOTLOADER_ROLLBACK_PROTECTION == 1)
  .remainingApplicationUpgrades = &bootload_remainingApplicationUpgrades,
#else
  .remainingApplicationUpgrades = NULL,
#endif
#if defined(BOOTLOADER_INTERFACE_TRUSTZONE_AWARE)
  .getPeripheralList = &btl_getPeripheralList,
#else
  .getPeripheralList = NULL,
#endif
  .getUpgradeLocation = bootload_getUpgradeLocation
};

#if defined(BOOTLOADER_SUPPORT_CERTIFICATES) && (BOOTLOADER_SUPPORT_CERTIFICATES == 1)
const ApplicationCertificate_t sl_app_certificate = {
  .structVersion = APPLICATION_CERTIFICATE_VERSION,
  .flags = { 0U },
  .key = { 0U },
  .version = 0,
  .signature = { 0U },
};
#endif

const ApplicationProperties_t sl_app_properties = {
  .magic = APPLICATION_PROPERTIES_MAGIC,
  .structVersion = APPLICATION_PROPERTIES_VERSION,
  .signatureType = APPLICATION_SIGNATURE_NONE,
  .signatureLocation = ((uint32_t)&__rom_end__) - BTL_MAIN_STAGE_BASE + ROM_END_SIZE,
  .app = {
    .type = APPLICATION_TYPE_BOOTLOADER,
    .version = BOOTLOADER_VERSION_MAIN,
    .capabilities = 0UL,
    .productId = { 0U },
  },
#if defined(BOOTLOADER_SUPPORT_CERTIFICATES) && (BOOTLOADER_SUPPORT_CERTIFICATES == 1)
  // If certificate based boot chain is enabled, the bootloader binary will be provided with
  // a certificate that does not contain any key.
  // A valid certificate needs to be injected to the bootloader images using Simplicity Commander.
  // Simplicity Commander will replace this certificate.
  .cert = (ApplicationCertificate_t *)&sl_app_certificate,
#else
  .cert = NULL,
#endif
  .longTokenSectionAddress = NULL,
  .decryptKey = { 0u },
};

/**
 * This function gets executed before ANYTHING got initialized.
 * So, no using global variables here!
 */
void SystemInit2(void)
{
#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_5) || defined(_SILICON_LABS_32B_SERIES_2_CONFIG_8)
  configureSMU();
#endif // _SILICON_LABS_32B_SERIES_2_CONFIG_5 || _SILICON_LABS_32B_SERIES_2_CONFIG_8

#if defined(TEST_BOOTLOADER_RAM_CLEAN_UP)
  ram_clean_up_test();
#endif

  // Initialize debug before first debug print
  BTL_DEBUG_INIT();

  // Assumption: We should enter the app
  volatile bool enterApp = true;
  // Assumption: The app should be verified
  volatile bool verifyApp = true;

  // Check if we came from EM4. If any other bit than the EM4 bit it set, we
  // can't know whether this was really an EM4 reset, and we need to do further
  // checking.
#if defined(RMU_RSTCAUSE_EM4RST) && defined(APPLICATION_VERIFICATION_SKIP_EM4_RST) \
  && (APPLICATION_VERIFICATION_SKIP_EM4_RST == 1)
  if (RMU->RSTCAUSE == RMU_RSTCAUSE_EM4RST) {
    // We came from EM4, app doesn't need to be verified
    verifyApp = false;
  } else if (enterBootloader()) {
    // We want to enter the bootloader, app doesn't need to be verified
    enterApp = false;
    verifyApp = false;
  }
#else
  if (enterBootloader()) {
    // We want to enter the bootloader, app doesn't need to be verified
    enterApp = false;
    verifyApp = false;
  }
#endif
  uint32_t startOfAppSpace = (uint32_t)mainStageTable.startOfAppSpace;

  // Sanity check application program counter
#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#endif
  uint32_t pc = *(uint32_t *)(startOfAppSpace + 4);
  if (pc == 0xFFFFFFFF) {
    // Sanity check failed; enter the bootloader
    reset_setResetReason(BOOTLOADER_RESET_REASON_BADAPP);
    enterApp = false;
    verifyApp = false;
  }
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
#if defined(_SILICON_LABS_32B_SERIES_2) && defined(CRYPTOACC_PRESENT)
  // fih_delay_init is applicable for vse devices
  fih_delay_init();
#endif
  // App should be verified
  if (verifyApp) {
#if defined(_SILICON_LABS_32B_SERIES_2)
    fih_delay();
#endif
    // If app verification fails, enter bootloader instead
    enterApp = bootload_verifyApplication(startOfAppSpace);
    if (!enterApp) {
      BTL_DEBUG_PRINTLN("App verify fail");
      reset_setResetReason(BOOTLOADER_RESET_REASON_BADAPP);
    }
  }

#if defined(BOOTLOADER_ROLLBACK_PROTECTION) && (BOOTLOADER_ROLLBACK_PROTECTION == 1)
  // Clean the stored application versions if requested with a magic.
  // The magic is only written when a bootloader upgrade is triggered.
  bootload_removeStoredApplicationVersions();

  if (enterApp) {
    enterApp = bootload_storeApplicationVersion(startOfAppSpace);
  }
#endif

  if (enterApp) {
    BTL_DEBUG_PRINTLN("Enter app");
    BTL_DEBUG_PRINT_LF();

#if defined(BOOTLOADER_SUPPORT_STORAGE)
    // Disable the reset counter if we're booting (back) into the application
    if (reset_resetCounterEnabled()) {
      reset_disableResetCounter();
    }
#endif

#if defined(BOOTLOADER_WRITE_DISABLE) && (BOOTLOADER_WRITE_DISABLE == 1)
    lockBootloaderArea();
#endif

#if defined(BOOTLOADER_ENFORCE_SECURE_BOOT) && (BOOTLOADER_ENFORCE_SECURE_BOOT == 1) \
    && defined(APPLICATION_WRITE_DISABLE) && (APPLICATION_WRITE_DISABLE == 1)
    // The neccessary check of valid signature pointer for application at startOfAppSpace
    // is already done in bootload_verifyApplication.
    bootload_lockApplicationArea(startOfAppSpace, 0);
#endif

#if defined(BOOTLOADER_APPLOADER) || defined(_SILICON_LABS_32B_SERIES_2_CONFIG_5) || defined(_SILICON_LABS_32B_SERIES_2_CONFIG_8)
    configureSMUToDefault();
#endif
    // Set vector table to application's table
    SCB->VTOR = startOfAppSpace;

    bootToApp(startOfAppSpace);
  }
  // Enter bootloader
}

/**
 * Jump to app
 */
__attribute__ ((noreturn, naked)) static void bootToApp(uint32_t startOfAppSpace)
{
  jumpToApplicationRoutine(startOfAppSpace);
  while (1) {
    // Do nothing
  }
}

/**
 * Check whether we should enter the bootloader
 *
 * @return True if the bootloader should be entered
 */
__STATIC_INLINE bool enterBootloader(void)
{
// *INDENT-OFF*
#if defined(EMU_RSTCAUSE_SYSREQ)
  if (EMU->RSTCAUSE & EMU_RSTCAUSE_SYSREQ) {
#else
  if (RMU->RSTCAUSE & RMU_RSTCAUSE_SYSREQRST) {
#endif
    // Check if we were asked to run the bootloader...
    switch (reset_classifyReset()) {
      case BOOTLOADER_RESET_REASON_BOOTLOAD:
      case BOOTLOADER_RESET_REASON_FORCE:
      case BOOTLOADER_RESET_REASON_UPGRADE:
      case BOOTLOADER_RESET_REASON_BADAPP:
        // Asked to go into bootload mode
        return true;
      default:
        break;
    }
  }
// *INDENT-ON*

#ifdef BTL_GPIO_ACTIVATION
  if (gpio_enterBootloader()) {
    // GPIO pin state signals bootloader entry
    return true;
  }
#endif

#ifdef BTL_EZSP_GPIO_ACTIVATION
  if (ezsp_gpio_enterBootloader()) {
    // GPIO pin state signals bootloader entry
    return true;
  }
#endif

  return false;
}

#if defined(BOOTLOADER_INTERFACE_TRUSTZONE_AWARE)
static void btl_getPeripheralList(uint32_t *ppusatd0, uint32_t *ppusatd1)
{
  if (ppusatd0 == NULL || ppusatd1 == NULL) {
    return;
  }
  *ppusatd0 = 0u;
  *ppusatd1 = 0u;

  *ppusatd0 |= SMU_PPUSATD0_MSC;
  *ppusatd0 |= SMU_PPUSATD0_CMU;
  *ppusatd0 |= SMU_PPUSATD0_HFRCO0;
#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_1) || defined(_SILICON_LABS_32B_SERIES_2_CONFIG_2) \
  || defined(_SILICON_LABS_32B_SERIES_2_CONFIG_3) || defined(_SILICON_LABS_32B_SERIES_2_CONFIG_4) || defined(_SILICON_LABS_32B_SERIES_2_CONFIG_7)
  *ppusatd0 |= SMU_PPUSATD0_GPIO;
#endif
  *ppusatd0 |= SMU_PPUSATD0_GPCRC;

#ifdef BOOTLOADER_SUPPORT_STORAGE
  if (storage_getDMAchannel() != -1) {
    *ppusatd0 |= SMU_PPUPATD0_LDMA;
    *ppusatd0 |= SMU_PPUSATD0_LDMAXBAR;
  }

#if defined(BTL_SPI_USART_ENABLE) || defined(BTL_SPI_EUSART_ENABLE)
  uint32_t ppusatdNr = 0xFFFFFFFFUL;
  uint32_t ppusatdUsartMask = storage_getSpiUsartPPUSATD(&ppusatdNr);
  if (ppusatdNr == 0u) {
    *ppusatd0 |= ppusatdUsartMask;
  } else if (ppusatdNr == 1u) {
    *ppusatd1 |= ppusatdUsartMask;
  }
#endif
#endif // BOOTLOADER_SUPPORT_STORAGE

#if defined(SMU_PPUSATD1_CRYPTOACC)
  *ppusatd1 |= SMU_PPUSATD1_CRYPTOACC;
#endif // SMU_PPUSATD1_CRYPTOACC
#if defined(SMU_PPUPATD1_SEMAILBOX)
  *ppusatd1 |= SMU_PPUPATD1_SEMAILBOX;
#endif // SMU_PPUPATD1_SEMAILBOX
}
#endif // BOOTLOADER_INTERFACE_TRUSTZONE_AWARE
