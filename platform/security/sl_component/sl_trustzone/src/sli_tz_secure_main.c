/***************************************************************************//**
 * @file
 * @brief Silicon Labs TrustZone secure main implementation.
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

#if defined (SL_COMPONENT_CATALOG_PRESENT)
  #include "sl_component_catalog.h"
#endif

#include "arm_cmse.h"
#include "em_device.h"
#include "psa/crypto.h"

#if defined(SL_CATALOG_GECKO_BOOTLOADER_INTERFACE_PRESENT)
  #include "btl_interface.h"
#endif

  #include "sl_se_manager.h"
  #include "sl_se_manager_util.h"
#if defined(CRYPTOACC_PRESENT)
  #include "psa/internal_trusted_storage.h"
  #include "sli_psa_driver_common.h"
  #include "cryptoacc_management.h"
#endif

#include "tz_secure_memory_autogen.h"
#include "sli_se_version_dependencies.h"

#include "sl_mpu.h"
#include "fih.h"

// -----------------------------------------------------------------------------
// External symbols

#if defined(__GNUC__)
extern const uint32_t linker_sg_begin;
extern const uint32_t linker_vectors_begin;
#elif defined(__ICCARM__)
const uint32_t linker_sg_begin @ "Veneer$$CMSE";
const uint32_t linker_vectors_begin @ ".intvec";
#endif

#if defined(MBEDTLS_PSA_CRYPTO_STORAGE_C) && defined(SLI_PSA_ITS_ENCRYPTED)
// Extern declaration is required due to the duplicate header used when
// the ITS service is compiled for the SKL secure appication.
extern psa_status_t sli_psa_its_set_root_key(uint8_t *root_key, size_t root_key_size);
#endif

// -----------------------------------------------------------------------------
// Global variables

#if (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)
bool otp_initialized = false;
sl_se_otp_init_t otp_configuration = { 0 };
uint32_t otp_version = 0u;
#endif // (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)

// -----------------------------------------------------------------------------
// Typedefs

typedef void (*nsfunc)(void) __attribute__((cmse_nonsecure_call));

// -----------------------------------------------------------------------------
// Macros

// The NS application is placed right after the secure application
#define TZ_NS_FLASH_OFFSET (TZ_S_FLASH_END - FLASH_BASE)
#define TZ_NS_RAM_OFFSET   (TZ_S_RAM_END - SRAM_BASE)

#define FIRMWARE_START_ADDRESS ((uint32_t)&linker_vectors_begin)

// THe FIH panic loop is a FI hardened infinite loop that includes multiple
// branch instructions that loopback in order to make unlooping difficult.
#if defined(TFM_FIH_PROFILE_ON)
  #define INFINITE_LOOP() FIH_PANIC
#else
  #define INFINITE_LOOP() while (1) {}
#endif // defined(TFM_FIH_PROFILE_ON)

#define AIRCR_UNLOCK_VECTKEY (0x05FAUL)
#define AIRCR_VECTKEY_STAT   (0xFA05UL)

// Mark the full range below as NS in SAU,
// and let the PPU generate access faults instead.
#define PERIPHERALS_BASE_NS_START (0x50000000UL)
#define PERIPHERALS_BASE_NS_END   (0xBFFFFFFFUL)

#define EPPB_REGION_START (0xE0044000UL)
#define EPPB_REGION_END   (0xE00FDFFFUL)

// Lock every page up until the NS app.
#define NUM_PAGES_TO_LOCK ((TZ_NS_FLASH_OFFSET + FLASH_PAGE_SIZE - 1) \
                           / FLASH_PAGE_SIZE)

// Each page is represented as a bit in the registers.
#define NUM_PAGELOCK_REGISTERS (FLASH_SIZE / FLASH_PAGE_SIZE / 32)

#if defined(MBEDTLS_PSA_CRYPTO_STORAGE_C) && defined(SLI_PSA_ITS_ENCRYPTED)
// The oldest supported HSE/VSE firmware versions
  #if (_SILICON_LABS_32B_SERIES_2_CONFIG >= 3)
    #define OLDEST_SUPPORTED_SE_FW_VERSION (0x00020201)  // v2.2.1
  #else
    #define OLDEST_SUPPORTED_SE_FW_VERSION (0x0001020e)  // v1.2.14
  #endif

  #if !defined(SEMAILBOX_PRESENT)
    #define ROOT_MAILBOX_SIZE                   (512UL)
  #endif
// Negative iniitalisation value.
  #define A_NEGATIVE_VALUE                       0xAAAA5555
#endif // defined(MBEDTLS_PSA_CRYPTO_STORAGE_C) && defined(SLI_PSA_ITS_ENCRYPTED)

#if defined (__ICCARM__)
  #define BUILTIN_UNREACHABLE()
#elif defined (__GNUC__)
  #define BUILTIN_UNREACHABLE() __builtin_unreachable();
#endif

// -----------------------------------------------------------------------------
// Static function declarations

static inline bool bootloader_present(void);
#if defined(TFM_FIH_PROFILE_ON) && defined(FIH_ENABLE_DELAY)
static inline void configure_sau_smu_for_fih_delay(void);
#endif
static inline void configure_smu_peripherals(void);
static inline void configure_smu_bus_masters(void);
static inline void enable_smu_security_fault_interrupts(void);

// Force all FIH instrumented functions to be called explicitly,
// that is, apply the noinline attribute to instruct the compiler.
// The reason is that FIH instrumentation consumes a huge portion
// of stack, and if all functions are inlined the stack frame of
// the secure main() function will become bigger than 3KBytes which
// is the total configured stack size causing stack overflow.
// By forcing the compiler to generate explicit funciton calls, each
// call will generate a new small stack frame which lives only until
// the function returns.
static fih_int __attribute__ ((noinline)) configure_sau(void);
static fih_int __attribute__ ((noinline)) configure_sau_region(uint32_t rnr, uint32_t rbar, uint32_t rlar);
static fih_int __attribute__ ((noinline)) configure_smu(void);
static fih_int __attribute__ ((noinline)) configure_interrupt_target_states(void);
static fih_int __attribute__ ((noinline)) prioritise_secure_exceptions(void);
static fih_int __attribute__ ((noinline)) enable_fault_exceptions(void);
static fih_int __attribute__ ((noinline)) enable_ns_fpu(void);
static fih_int __attribute__ ((noinline)) enable_page_locks(void);
__WEAK void start_ns_app(void);

#if defined(CRYPTOACC_PRESENT)
static fih_int __attribute__ ((noinline)) clear_rootdata(void);
#endif
#if (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)
__WEAK fih_int __attribute__ ((noinline)) store_otp_configuration(void);
static fih_int __attribute__ ((noinline)) store_se_otp_version(void);
#endif // (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)
static inline void fatal_error(void);
static fih_int __attribute__ ((noinline)) configure_mpu(void);

#if defined(MBEDTLS_PSA_CRYPTO_STORAGE_C) && defined(SLI_PSA_ITS_ENCRYPTED)
static fih_int __attribute__ ((noinline)) check_se_version(uint32_t se_version);
#if defined(SEMAILBOX_PRESENT)
static fih_int __attribute__ ((noinline)) verify_hse_version(void);
#else
extern bool rootIsOutputMailboxValid(void);
static fih_int __attribute__ ((noinline)) vse_is_mailbox_valid(void);
static fih_int __attribute__ ((noinline)) vse_get_reply_ptr(uint32_t **vse_reply_ptr);
static fih_int __attribute__ ((noinline)) vse_get_se_version(const uint32_t *vse_reply_ptr, uint32_t *se_version);
static fih_int __attribute__ ((noinline)) vse_get_reply_status(const uint32_t *vse_reply_ptr, uint32_t *vse_reply_status);
static fih_int __attribute__ ((noinline)) vse_get_data_length(const uint32_t *vse_reply_ptr, uint32_t *vse_data_length);
static fih_int __attribute__ ((noinline)) setup_storage_root_key(void);
#endif
#endif // defined(MBEDTLS_PSA_CRYPTO_STORAGE_C) && defined(SLI_PSA_ITS_ENCRYPTED)

// -----------------------------------------------------------------------------
// Static constants

// We will use an array of pagelock registers in order to keep
// the lock setting logic from becoming unreadable. This also
// means that the code will handle differences in flash size.
static volatile uint32_t *const pagelock_registers[] = {
  #if defined(_MSC_PAGELOCKWORD0_RESETVALUE)
  &MSC->PAGELOCKWORD0_SET,
  #elif defined(_MSC_PAGELOCK0_RESETVALUE)
  &MSC->PAGELOCK0_SET,
  #else
  // All devices must have at least one pagelock register.
  #error "Unable to lock pages for this device"
  #endif
  #if defined(_MSC_PAGELOCKWORD1_RESETVALUE)
  &MSC->PAGELOCKWORD1_SET,
  #elif defined(_MSC_PAGELOCK1_RESETVALUE)
  &MSC->PAGELOCK1_SET,
  #endif
  #if defined(_MSC_PAGELOCKWORD2_RESETVALUE)
  &MSC->PAGELOCKWORD2_SET,
  #elif defined(_MSC_PAGELOCK2_RESETVALUE)
  &MSC->PAGELOCK2_SET,
  #endif
  #if defined(_MSC_PAGELOCKWORD3_RESETVALUE)
  &MSC->PAGELOCKWORD3_SET,
  #elif defined(_MSC_PAGELOCK3_RESETVALUE)
  &MSC->PAGELOCK3_SET,
  #endif
  #if defined(_MSC_PAGELOCKWORD4_RESETVALUE)
  &MSC->PAGELOCKWORD4_SET,
  #endif
  #if defined(_MSC_PAGELOCKWORD5_RESETVALUE)
  &MSC->PAGELOCKWORD5_SET,
  #endif
  #if defined(_MSC_PAGELOCKWORD6_RESETVALUE)
  &MSC->PAGELOCKWORD6_SET,
  #endif
  #if defined(_MSC_PAGELOCKWORD7_RESETVALUE)
  &MSC->PAGELOCKWORD7_SET,
  #endif
};

// -----------------------------------------------------------------------------
// Main function

int main(void)
{
  fih_int fih_rc = FIH_FAILURE;

  #if defined(TFM_FIH_PROFILE_ON) && defined(FIH_ENABLE_DELAY)
  configure_sau_smu_for_fih_delay();
    #if defined(CRYPTOACC_PRESENT)
  cryptoacc_trng_initialize();
    #endif
  #endif

  FIH_CALL(enable_fault_exceptions, fih_rc);
  if (fih_not_eq(fih_rc, FIH_SUCCESS)) {
    fatal_error();
  }

  // Prioritise secure exceptions to avoid NS being able to pre-empt
  // secure SVC or SecureFault.
  FIH_CALL(prioritise_secure_exceptions, fih_rc);
  if (fih_not_eq(fih_rc, FIH_SUCCESS)) {
    fatal_error();
  }

  // Configure interrupt target states before any secure interrupts are enabled.
  FIH_CALL(configure_interrupt_target_states, fih_rc);
  if (fih_not_eq(fih_rc, FIH_SUCCESS)) {
    fatal_error();
  }

  #if defined(MBEDTLS_PSA_CRYPTO_STORAGE_C) && defined(SLI_PSA_ITS_ENCRYPTED)
  #if defined(SEMAILBOX_PRESENT)
  // HSE devices don't need any SRK initialization, since it will be available
  // as an internal key. However, we'll still check the SE version to ensure
  // that SRK is supported.
  FIH_CALL(verify_hse_version, fih_rc);
  if (fih_not_eq(fih_rc, FIH_SUCCESS)) {
    fatal_error();
  }
  #else // SEMAILBOX_PRESENT
  // Setup SRK for devices without an HSE. (The SE version is checked as part of this
  // procedure.) Note that this is done before setting up the SAU/SMU since the root key is
  // stored in FRCRAM which is not guaranteed to stay Secure after TZ initialization. We
  // therefore need to initialize and clear the SRK passed from the VSE before setting
  // anything to Non-Secure.
  FIH_CALL(setup_storage_root_key, fih_rc);
  if (fih_not_eq(fih_rc, FIH_SUCCESS)) {
    fatal_error();
  }
  #endif // SEMAILBOX_PRESENT
  #endif // defined(MBEDTLS_PSA_CRYPTO_STORAGE_C) && defined(SLI_PSA_ITS_ENCRYPTED)

  #if (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)
  sl_status_t sl_status = sl_se_init();
  if (fih_not_eq(fih_int_encode(sl_status), fih_int_encode(SL_STATUS_OK))) {
    fatal_error();
  }

  FIH_CALL(store_se_otp_version, fih_rc);
  if (fih_not_eq(fih_rc, FIH_SUCCESS)) {
    fatal_error();
  }

  FIH_CALL(store_otp_configuration, fih_rc);
  if (fih_not_eq(fih_rc, FIH_SUCCESS)) {
    fatal_error();
  }
  #endif
  #if defined(CRYPTOACC_PRESENT)
  // At the startup of the VSE devices, we need to invalidate the
  // ROOTDATA0 register which is only accessible by S to ensure that NS apps
  // can't craft a malicious mailbox command. This is a possible scenario since
  // FRCRAM, which is used as the (virtual) mailbox interface has to be configured as NS.
  FIH_CALL(clear_rootdata, fih_rc);
  if (fih_not_eq(fih_rc, FIH_SUCCESS)) {
    fatal_error();
  }
  #endif // CRYPTOACC_PRESENT

  // We should configure the SAU as early as possible in order to avoid odd
  // PPU security faults when accessing peripherals (e.g. CMU) after they have
  // been reconfigured by the SMU.
  FIH_CALL(configure_sau, fih_rc);
  if (fih_not_eq(fih_rc, FIH_SUCCESS)) {
    fatal_error();
  }
  FIH_CALL(configure_smu, fih_rc);
  if (fih_not_eq(fih_rc, FIH_SUCCESS)) {
    fatal_error();
  }
  FIH_CALL(configure_mpu, fih_rc);
  if (fih_not_eq(fih_rc, FIH_SUCCESS)) {
    fatal_error();
  }

  // The NS app should not be able to write to secure flash (including the
  // bootloader). As an extra layer of protection, we will enable flash page
  // locks. This also stops the NS app from being able to erase the S code
  // using the MSC service, which is another benefit.
  FIH_CALL(enable_page_locks, fih_rc);
  if (fih_not_eq(fih_rc, FIH_SUCCESS)) {
    fatal_error();
  }

  volatile psa_status_t psa_status = PSA_ERROR_GENERIC_ERROR;
  psa_status = psa_crypto_init();
  if (fih_not_eq(fih_int_encode(psa_status), fih_int_encode(PSA_SUCCESS))) {
    fatal_error();
  }

  FIH_CALL(enable_ns_fpu, fih_rc);
  if (fih_not_eq(fih_rc, FIH_SUCCESS)) {
    fatal_error();
  }

  start_ns_app();

  // Will never get here, as non-secure software doesn't return.
  fatal_error();
}

// -----------------------------------------------------------------------------
// Static functions

#if defined(TFM_FIH_PROFILE_ON)
static int32_t __attribute__ ((noinline)) bootloader_table_valid(void)
{
  return bootloader_pointerValid(mainBootloaderTable) ? FIH_TRUE : FIH_FALSE;
}
static int32_t __attribute__ ((noinline)) bootloader_magic_valid(void)
{
  if (mainBootloaderTable->header.type == BOOTLOADER_MAGIC_MAIN) {
    return FIH_TRUE;
  } else {
    return FIH_FALSE;
  }
}
#endif

static inline bool bootloader_present(void)
{
#if defined(TFM_FIH_PROFILE_ON)
  volatile int32_t rc_1 = bootloader_table_valid();
  volatile int32_t rc_2 = bootloader_table_valid();
  if (rc_1 != rc_2) {
    fatal_error();
  }
  if (rc_1 == FIH_TRUE) {
    rc_1 = bootloader_magic_valid();
    rc_2 = bootloader_magic_valid();
    if (rc_1 != rc_2) {
      fatal_error();
    }
    return rc_1 == FIH_TRUE ? true : false;
  }
#else
  if (bootloader_pointerValid(mainBootloaderTable)) {
    if (mainBootloaderTable->header.type == BOOTLOADER_MAGIC_MAIN) {
      return true;
    }
  }
#endif
  return false;
}

/**************************************************************************//**
 * @brief Handle a fault by performing a soft reset.
 *****************************************************************************/
static inline void fatal_error(void)
{
  #if defined(DEBUG_EFM)
  INFINITE_LOOP();
  #else
  NVIC_SystemReset();
    #if defined(TFM_FIH_PROFILE_ON) && defined(TFM_FIH_PROFILE_HIGH)
  __asm volatile ("b fatal_error");
  __asm volatile ("b fatal_error");
  __asm volatile ("b fatal_error");
  __asm volatile ("b fatal_error");
  __asm volatile ("b fatal_error");
  __asm volatile ("b fatal_error");
  __asm volatile ("b fatal_error");
  __asm volatile ("b fatal_error");
  __asm volatile ("b fatal_error");
    #endif
  BUILTIN_UNREACHABLE();
  #endif
}

#if defined(CRYPTOACC_PRESENT)
/**************************************************************************//**
 * @brief Clear the ROOTDATA0 register
 *****************************************************************************/
static fih_int __attribute__ ((noinline)) clear_rootdata(void)
{
  fih_int fih_rc = FIH_FAILURE; // if fatal_error glitched, return failure

  #if defined(TFM_FIH_PROFILE_ON) && defined(FIH_ENABLE_DELAY)
  // CMU is already set to NS during fih_delay initialisation in
  // configure_sau_smu_for_fih_delay.
  CMU_TypeDef *cmu = CMU_NS;
  #else
  CMU_TypeDef *cmu = CMU_S;
  #endif

  #if defined(CMU_CLKEN0_SYSCFG)
  // Saving the state is not necessary.
  cmu->CLKEN0_SET = CMU_CLKEN0_SYSCFG;
  #endif

  #define VSE_MB_ADDRESS_INVALIDATED (0xFFFFFFFFUL)
  // Set ROOTDATA0 (which is used as the input channel) to an invalid address.
  SYSCFG_S->ROOTDATA0 = VSE_MB_ADDRESS_INVALIDATED;

  if (fih_not_eq(fih_int_encode(SYSCFG_S->ROOTDATA0),
                 fih_int_encode(VSE_MB_ADDRESS_INVALIDATED))) {
    fatal_error();
  } else {
    fih_rc = FIH_SUCCESS;
  }

  #if defined(CMU_CLKEN0_SYSCFG)
  cmu->CLKEN0_CLR = CMU_CLKEN0_SYSCFG;
  #endif

  FIH_RET(fih_rc);
}
#endif

/**************************************************************************//**
 * @brief Configure the memory region below the secure main to XN
 *****************************************************************************/
static fih_int __attribute__ ((noinline)) configure_mpu(void)
{
  fih_int fih_rc = FIH_FAILURE; // if fatal_error glitched, return failure
  volatile sl_status_t status = SL_STATUS_FAIL;
#if defined(SL_CATALOG_GECKO_BOOTLOADER_INTERFACE_PRESENT)
  #define FIH_INIT_STEP_CONFIGURE_MPU  2
#else
  #define FIH_INIT_STEP_CONFIGURE_MPU  1
#endif
  FIH_CFI_STEP_INIT(FIH_INIT_STEP_CONFIGURE_MPU);

#if defined(SL_CATALOG_GECKO_BOOTLOADER_INTERFACE_PRESENT)
  if (bootloader_present()) {
    // The main bootloader table pointer is valid, assume we have a bootloader.
    if (bootloader_init() != BOOTLOADER_OK) {
      fatal_error();
    }
    status = sl_mpu_disable_execute(FLASH_BASE,
                                    FIRMWARE_START_ADDRESS - 1,
                                    FIRMWARE_START_ADDRESS - FLASH_BASE);
    if (fih_not_eq(fih_int_encode(status), fih_int_encode(SL_STATUS_OK))) {
      fatal_error();
      goto exit; // if fatal_error is glitched
    }
    // Reset status to FAIL in case next call is glitched.
    status = SL_STATUS_FAIL;
  }
  FIH_CFI_STEP_DECREMENT();
#endif // SL_CATALOG_GECKO_BOOTLOADER_INTERFACE_PRESENT

  // Everything after S space is painted XN. Nothing from NS will be executed
  // from S. This doesn't affect NS MPU.
  status = sl_mpu_disable_execute(TZ_S_FLASH_END,
                                  FLASH_BASE + FLASH_SIZE - 1u,
                                  FLASH_BASE + FLASH_SIZE - TZ_S_FLASH_END);
  if (fih_not_eq(fih_int_encode(status), fih_int_encode(SL_STATUS_OK))) {
    fatal_error();
    goto exit; // if fatal_error is glitched
  } else {
    fih_rc = FIH_SUCCESS;
    FIH_CFI_STEP_DECREMENT();
  }

  FIH_RET(fih_rc);
  exit:
  FIH_CFI_STEP_ERR_RESET();
  FIH_RET(FIH_FAILURE);
}

#if (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)
/**************************************************************************//**
 * @brief Store the debug state
 *****************************************************************************/
__WEAK fih_int __attribute__ ((noinline)) store_otp_configuration(void)
{
  fih_int fih_rc = FIH_FAILURE; // if fatal_error is glitched, return failure
  sl_se_command_context_t cmd_ctx;
  sl_status_t status = sl_se_read_otp(&cmd_ctx,
                                      &otp_configuration);
  if (fih_not_eq(fih_int_encode(status), fih_int_encode(SL_STATUS_OK))
#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_1)
      && fih_not_eq(fih_int_encode(status), fih_int_encode(SL_STATUS_COMMAND_IS_INVALID))
#else
      && fih_not_eq(fih_int_encode(status), fih_int_encode(SL_STATUS_NOT_INITIALIZED))
#endif
      ) {
    fatal_error();
  } else {
    fih_rc = FIH_SUCCESS;
  }
  if (status == SL_STATUS_OK) {
    otp_initialized = true;
  } else {
    otp_initialized = false;
  }

  FIH_RET(fih_rc);
}

/**************************************************************************//**
 * @brief Store the SE OTP version
 *****************************************************************************/
static fih_int __attribute__ ((noinline)) store_se_otp_version(void)
{
  fih_int fih_rc = FIH_FAILURE; // if fatal_error is glitched, return failure

  sl_se_command_context_t cmd_ctx;
  sl_status_t status = sl_se_get_otp_version(&cmd_ctx,
                                             &otp_version);
  if (fih_not_eq(fih_int_encode(status), fih_int_encode(SL_STATUS_OK))) {
    #if defined(CRYPTOACC_PRESENT)
    otp_version = 0u;
    fih_rc = FIH_SUCCESS;
    #else
    fatal_error();
    #endif
  } else {
    if (fih_eq(fih_int_encode(otp_version), fih_int_encode(0))) {
      fatal_error();
    } else {
      fih_rc = FIH_SUCCESS;
    }
  }

  FIH_RET(fih_rc);
}
#endif // (_SILICON_LABS_SECURITY_FEATURE != _SILICON_LABS_SECURITY_FEATURE_VAULT)

/**************************************************************************//**
 * @brief Configure the specified SAU region.
 *****************************************************************************/
static fih_int __attribute__ ((noinline)) configure_sau_region(uint32_t rnr, uint32_t rbar, uint32_t rlar)
{
  fih_int fih_rc = FIH_FAILURE; // if fatal_error is glitched, return failure

  SAU->RNR = rnr;
  SAU->RBAR = rbar;
  SAU->RLAR = rlar;

  if (fih_not_eq(fih_int_encode(SAU->RNR), fih_int_encode(rnr))
      || fih_not_eq(fih_int_encode(SAU->RBAR), fih_int_encode(rbar))
      || fih_not_eq(fih_int_encode(SAU->RLAR), fih_int_encode(rlar))) {
    fatal_error();
  } else {
    fih_rc = FIH_SUCCESS;
  }

  FIH_RET(fih_rc);
}

struct sau_cfg_t {
  uint32_t RBAR;
  uint32_t RLAR;
};

#define CONFIGURED_SAU_REGIONS 7

static const struct sau_cfg_t sau_cfg[CONFIGURED_SAU_REGIONS] = {
  { // NS Flash ( an overlapping NSC region for SG veneers is setup in SMU )
    (uint32_t)&linker_sg_begin,
    FLASH_BASE + FLASH_SIZE - 1u,
  },
  { // RNR # 1  NS Peripherals
    PERIPHERALS_BASE_NS_START,
    PERIPHERALS_BASE_NS_END,
  },
  { // RNR # 2 NS SRAM
    SRAM_BASE + TZ_NS_RAM_OFFSET,
    SRAM_BASE + SRAM_SIZE - 1u,
  },
  { // RNR # 3 User Data
    MSC_FLASH_USERDATA_MEM_BASE,
    MSC_FLASH_USERDATA_MEM_END,
  },
  { // RNR # 4 Device Info
    MSC_FLASH_DEVINFO_MEM_BASE,
    MSC_FLASH_DEVINFO_MEM_END,
  },
  { // RNR # 5 Chip Config
    MSC_FLASH_CHIPCONFIG_MEM_BASE,
    MSC_FLASH_CHIPCONFIG_MEM_END,
  },
  { // RNR # 6 EPPB
    EPPB_REGION_START,
    EPPB_REGION_END,
  },
};

/**************************************************************************//**
 * @brief Configure the memory ranges' security attributes using the SAU.
 *****************************************************************************/
static fih_int __attribute__ ((noinline)) configure_sau(void)
{
  fih_int fih_rc;
  uint32_t i;
  #define FIH_INIT_STEP_CONFIGURE_SAU  3

  FIH_CFI_STEP_INIT(FIH_INIT_STEP_CONFIGURE_SAU);

  // Enable the needed SAU regions
  // NOTE: SAU_RLAR_NSC_Pos is not needed since we set all regions to NS.
  // For NS Flash ( an overlapping NSC region for SG veneers is setup in SMU )
  for (i = 0; i < CONFIGURED_SAU_REGIONS; i++) {
    FIH_CALL(configure_sau_region, fih_rc,
             i & SAU_RNR_REGION_Msk,
             sau_cfg[i].RBAR & SAU_RBAR_BADDR_Msk,
             (sau_cfg[i].RLAR & SAU_RLAR_LADDR_Msk) | SAU_RLAR_ENABLE_Msk);
    if (fih_not_eq(fih_rc, FIH_SUCCESS)) {
      fatal_error();
      goto exit; // if fatal_error is glitched
    }
  }

  FIH_CFI_STEP_DECREMENT();

  // Disable the remaining regions
  for (; // i = CONFIGURED_SAU_REGIONS; i should not be clobbered in between
       i < ((SAU->TYPE & SAU_TYPE_SREGION_Msk) >> SAU_TYPE_SREGION_Pos);
       i++) {
    FIH_CALL(configure_sau_region, fih_rc, i, 0u, 0u); // Enable mask not set
    if (fih_not_eq(fih_rc, FIH_SUCCESS)) {
      fatal_error();
      goto exit; // if fatal_error is glitched
    }
  }

  FIH_CFI_STEP_DECREMENT();

  /* Enable SAU */
#ifdef TFM_FIH_PROFILE_ON
  TZ_SAU_Enable();
  TZ_SAU_Enable();
#endif
  TZ_SAU_Enable();

  FIH_CFI_STEP_DECREMENT();

  FIH_RET(fih_rc);
  exit:
  FIH_CFI_STEP_ERR_RESET();
  FIH_RET(FIH_FAILURE);
}

/**************************************************************************//**
 * @brief Configures the TZ memory map using the SMU.
 *
 * Configures the memory map with the SMU using the defines TZ_NS_FLASH_OFFSET
 * and TZ_NS_RAM_OFFSET as start locations for the non-secure sections in flash
 * and RAM. All of the peripherals are mapped and available for the non-secure
 * application, except for the a few secure-only peripherals.
 *****************************************************************************/
static fih_int __attribute__ ((noinline)) configure_smu(void)
{
  #define FIH_INIT_STEP_CONFIGURE_SMU  5

  FIH_CFI_STEP_INIT(FIH_INIT_STEP_CONFIGURE_SMU);

  // Enable clocking (where necessary).
  #if defined(CMU_CLKEN1_SMU)
    #if defined(TFM_FIH_PROFILE_ON) && defined(FIH_ENABLE_DELAY)
  CMU_NS->CLKEN1_SET = CMU_CLKEN1_SMU;
    #else
  CMU_S->CLKEN1_SET = CMU_CLKEN1_SMU;
    #endif // defined(TFM_FIH_PROFILE_ON) && defined(FIH_ENABLE_DELAY)
  #endif
  SMU->LOCK = SMU_LOCK_SMULOCKKEY_UNLOCK;

  // Configure flash into S/NSC/NS regions.
  // S - NSC boundary
  SMU->ESAUMRB01 = FLASH_BASE & _SMU_ESAUMRB01_MASK;
  if (fih_not_eq(fih_int_encode(SMU->ESAUMRB01),
                 fih_int_encode(FLASH_BASE & _SMU_ESAUMRB01_MASK))) {
    fatal_error();
    goto exit; // if fatal_error is glitched
  }
  // NSC - NS boundary
  SMU->ESAUMRB12 = (FLASH_BASE + TZ_NS_FLASH_OFFSET) & _SMU_ESAUMRB12_MASK;
  if (fih_not_eq(fih_int_encode(SMU->ESAUMRB12),
                 fih_int_encode((FLASH_BASE + TZ_NS_FLASH_OFFSET) & _SMU_ESAUMRB12_MASK))) {
    fatal_error();
    goto exit; // if fatal_error is glitched
  }

  // Configure RAM into S/NS regions.

  // S - NSC boundary
  SMU->ESAUMRB45 = (SRAM_BASE + TZ_NS_RAM_OFFSET) & _SMU_ESAUMRB45_MASK;
  if (fih_not_eq(fih_int_encode(SMU->ESAUMRB45),
                 fih_int_encode((SRAM_BASE + TZ_NS_RAM_OFFSET) & _SMU_ESAUMRB45_MASK))) {
    fatal_error();
    goto exit; // if fatal_error is glitched
  }
  // NSC - NS boundary
  SMU->ESAUMRB56 = (SRAM_BASE + TZ_NS_RAM_OFFSET) & _SMU_ESAUMRB56_MASK;
  if (fih_not_eq(fih_int_encode(SMU->ESAUMRB56),
                 fih_int_encode((SRAM_BASE + TZ_NS_RAM_OFFSET) & _SMU_ESAUMRB56_MASK))) {
    fatal_error();
    goto exit; // if fatal_error is glitched
  }

  // Make the info page NS.
  SMU->ESAURTYPES0 = SMU_ESAURTYPES0_ESAUR3NS;
  if (fih_not_eq(fih_int_encode(SMU->ESAURTYPES0),
                 fih_int_encode(SMU_ESAURTYPES0_ESAUR3NS))) {
    fatal_error();
    goto exit; // if fatal_error is glitched
  }

  // Make the EPPB area NS.
  SMU->ESAURTYPES1 = SMU_ESAURTYPES1_ESAUR11NS;
  if (fih_not_eq(fih_int_encode(SMU->ESAURTYPES1),
                 fih_int_encode(SMU_ESAURTYPES1_ESAUR11NS))) {
    fatal_error();
    goto exit; // if fatal_error is glitched
  }

  FIH_CFI_STEP_DECREMENT();

  configure_smu_peripherals();

  FIH_CFI_STEP_DECREMENT();

  configure_smu_bus_masters();

  FIH_CFI_STEP_DECREMENT();

  enable_smu_security_fault_interrupts();

  FIH_CFI_STEP_DECREMENT();

  // Lock SMU config.
  SMU->LOCK = 0;

  // Disable clocking (where necessary).
  #if defined(CMU_CLKEN1_SMU)
  CMU_NS->CLKEN1_CLR = CMU_CLKEN1_SMU;
  #endif

  FIH_CFI_STEP_DECREMENT();

  FIH_RET(FIH_SUCCESS);

  exit:
  FIH_CFI_STEP_ERR_RESET();
  FIH_RET(FIH_FAILURE);
}

#if defined(TFM_FIH_PROFILE_ON) && defined(FIH_ENABLE_DELAY)

static inline void configure_sau_smu_for_fih_delay(void)
{
  // Enable SAU region needed for NS Peripherals, especially CMU_NS
  TZ_SAU_Enable();
  SAU->RNR = 1; // NS Peripherals
  SAU->RBAR = PERIPHERALS_BASE_NS_START & SAU_RBAR_BADDR_Msk;
  SAU->RLAR = ((PERIPHERALS_BASE_NS_END) &SAU_RLAR_LADDR_Msk)
              | (0 << SAU_RLAR_NSC_Pos)
              | SAU_RLAR_ENABLE_Msk;

  // Enable SMU clock (where necessary).
  // NOTE: We use CMU_S before CMU is set to NS in PPUSATD0.
  #if defined(CMU_CLKEN1_SMU)
  CMU_S->CLKEN1_SET = CMU_CLKEN1_SMU;
  #endif
  SMU->LOCK = SMU_LOCK_SMULOCKKEY_UNLOCK;

  configure_smu_peripherals();

  // Lock SMU config.
  SMU->LOCK = 0;

  // Disable SMU clock (where necessary).
  // NOTE: CMU_NS is required for CMU access from now on
  #if defined(CMU_CLKEN1_SMU)
  CMU_NS->CLKEN1_CLR = CMU_CLKEN1_SMU;
  #endif
}

#endif // defined(TFM_FIH_PROFILE_ON) && defined(FIH_ENABLE_DELAY)

/**************************************************************************//**
 * @brief Configures secure attributes of peripherals using the SMU.
 *
 * This function is device dependent. Assumes that the SMU is clocked.
 *****************************************************************************/
static inline void configure_smu_peripherals(void)
{
  #if defined(SEMAILBOX_PRESENT)
  // All peripherals are non-secure except SMU, SEMAILBOX, MSC and SYSCFG.
  SMU->PPUSATD0_CLR = _SMU_PPUSATD0_MASK
                      & ~(SMU_PPUSATD0_SYSCFG
                          | SMU_PPUSATD0_MSC);
  SMU->PPUSATD1_CLR = _SMU_PPUSATD1_MASK
                      & ~(SMU_PPUSATD1_SMU
                          | SMU_PPUSATD1_SEMAILBOX);
  #elif defined(CRYPTOACC_PRESENT)
  // All peripherals are non-secure except SMU, CRYPTOACC, MSC and SYSCFG.
  SMU->PPUSATD0_CLR = _SMU_PPUSATD0_MASK
                      & ~(SMU_PPUSATD0_SYSCFG
                          | SMU_PPUSATD0_MSC);
  SMU->PPUSATD1_CLR = _SMU_PPUSATD1_MASK
                      & ~(SMU_PPUSATD1_SMU
                          | SMU_PPUSATD1_CRYPTOACC);
  #endif
}

/**************************************************************************//**
 * @brief Configures secure state of bus masters using the SMU.
 *
 * This function is device dependent. Assumes that the SMU is clocked.
 *****************************************************************************/
static inline void configure_smu_bus_masters(void)
{
  #if defined(SEMAILBOX_PRESENT) && (_SILICON_LABS_32B_SERIES_2_CONFIG == 1)
  // Configure all bus-masters execpt for SEDMA as non-secure.
  SMU->BMPUSATD0_CLR = _SMU_BMPUSATD0_MASK
                       & ~(SMU_BMPUSATD0_SEDMA);
  #elif defined(SEMAILBOX_PRESENT) && (_SILICON_LABS_32B_SERIES_2_CONFIG > 1)
  // Configure all bus-masters execpt for SEEXTDMA as non-secure.
  SMU->BMPUSATD0_CLR = _SMU_BMPUSATD0_MASK
                       & ~(SMU_BMPUSATD0_SEEXTDMA);
  #elif defined(CRYPTOACC_PRESENT)
  // Configure all bus-masters execpt for CRYPTOACC as non-secure.
  SMU->BMPUSATD0_CLR = _SMU_BMPUSATD0_MASK
                       & ~(SMU_BMPUSATD0_CRYPTOACC);
  #endif
}

/**************************************************************************//**
 * @brief Enable SMU security fault interrupts.
 *
 * Assumes that the SMU is clocked.
 *****************************************************************************/
static inline void enable_smu_security_fault_interrupts(void)
{
  NVIC_ClearPendingIRQ(SMU_SECURE_IRQn);
  SMU->IF_CLR = SMU_IF_PPUSEC | SMU_IF_BMPUSEC;
  NVIC_EnableIRQ(SMU_SECURE_IRQn);
  SMU->IEN = SMU_IEN_PPUSEC | SMU_IEN_BMPUSEC;
}

/**************************************************************************//**
 * @brief Configure interrupt target states.
 *
 * Interrupts must either point at the secure or non-secure world. After reset
 * everything points to the secure world, and this function redirects all
 * intterupts to non-secure to better support existing applications.
 *****************************************************************************/
static fih_int __attribute__ ((noinline)) configure_interrupt_target_states(void)
{
  fih_int fih_rc = FIH_SUCCESS;

  // Start by setting all Interrupt Non-Secure State (ITNS) bits. This results
  // in all IRQs being targeted at the NS world.
  for (size_t i = 0; i < sizeof(NVIC->ITNS) / sizeof(NVIC->ITNS[0]); i++) {
    NVIC->ITNS[i] = 0xFFFFFFFF;
  }

  // Clear the ITNS bits corresponding to all IRQs belonging to S peripherals.
  #if defined(SEMAILBOX_PRESENT)
  NVIC_ClearTargetState(SEMBRX_IRQn);
  NVIC_ClearTargetState(SEMBTX_IRQn);
  NVIC_ClearTargetState(SMU_SECURE_IRQn);
  NVIC_ClearTargetState(SYSCFG_IRQn);
  NVIC_ClearTargetState(MSC_IRQn);
  #elif defined(CRYPTOACC_PRESENT)
  NVIC_ClearTargetState(CRYPTOACC_IRQn);
  NVIC_ClearTargetState(TRNG_IRQn);
  NVIC_ClearTargetState(PKE_IRQn);
  NVIC_ClearTargetState(SMU_SECURE_IRQn);
  NVIC_ClearTargetState(SYSCFG_IRQn);
  NVIC_ClearTargetState(MSC_IRQn);
  #endif

#if defined(TFM_FIH_PROFILE_ON) && defined(TFM_FIH_PROFILE_HIGH)

#define NUM_ITNS_REGS (EXT_IRQ_COUNT / 32 + (EXT_IRQ_COUNT % 32 ? 1 : 0))
#define CLEAR_ITNS_BIT(irqn) \
  expected_itns[(((uint32_t)irqn) >> 5UL)] &= ~((uint32_t)(1UL << (((uint32_t)irqn) & 0x1FUL)));
  uint32_t expected_itns[NUM_ITNS_REGS];

  for (size_t i = 0; i < NUM_ITNS_REGS; i++) {
    expected_itns[i] = 0xFFFFFFFF;
  }

#if defined(SEMAILBOX_PRESENT)
  CLEAR_ITNS_BIT(SEMBRX_IRQn);
  CLEAR_ITNS_BIT(SEMBTX_IRQn);
  CLEAR_ITNS_BIT(SMU_SECURE_IRQn);
  CLEAR_ITNS_BIT(SYSCFG_IRQn);
  CLEAR_ITNS_BIT(MSC_IRQn);
#elif defined(CRYPTOACC_PRESENT)
  CLEAR_ITNS_BIT(CRYPTOACC_IRQn);
  CLEAR_ITNS_BIT(TRNG_IRQn);
  CLEAR_ITNS_BIT(PKE_IRQn);
  CLEAR_ITNS_BIT(SMU_SECURE_IRQn);
  CLEAR_ITNS_BIT(SYSCFG_IRQn);
  CLEAR_ITNS_BIT(MSC_IRQn);
#endif

  // Clear unused most significant irq bits in ITNS
  for (size_t i = EXT_IRQ_COUNT; i < 32 * NUM_ITNS_REGS; i++) {
    CLEAR_ITNS_BIT(i);
  }

  // Check that all Interrupt Non-Secure State (ITNS) bits are as exptected
  for (size_t i = 0; i < NUM_ITNS_REGS; i++) {
    if (fih_not_eq(fih_int_encode(NVIC->ITNS[i]), fih_int_encode(expected_itns[i]))) {
      fatal_error();
      fih_rc = FIH_FAILURE; // if fatal_error is glitched, return failure
    }
  }
#endif // defined(TFM_FIH_PROFILE_ON) && defined(TFM_FIH_PROFILE_HIGH)

  FIH_RET(fih_rc);
}

/**************************************************************************//**
 * @brief Prioritize the secure exceptions
 *
 * Modify the relative priorities of Secure and Non-secure interrupts,
 * so that the priority range for Secure interrupts extends to higher
 * priorities than the range for Non-secure interrupts.
 *****************************************************************************/
static fih_int __attribute__ ((noinline)) prioritise_secure_exceptions(void)
{
  fih_int fih_rc = FIH_FAILURE; // if fatal_error is glitched, return failure

  uint32_t scb_vectkey = AIRCR_UNLOCK_VECTKEY;
  uint32_t scb_AIRCR = SCB_AIRCR_PRIS_Msk
                       | (scb_vectkey << SCB_AIRCR_VECTKEY_Pos)
                       | (SCB->AIRCR & ~SCB_AIRCR_VECTKEY_Msk);

  SCB->AIRCR = scb_AIRCR;

  scb_AIRCR &= ~SCB_AIRCR_VECTKEY_Msk;
  scb_AIRCR |= AIRCR_VECTKEY_STAT << SCB_AIRCR_VECTKEY_Pos;

  // Verify register if store instruction was glitched
  if (fih_not_eq(fih_int_encode(scb_AIRCR), fih_int_encode(SCB->AIRCR))) {
    fatal_error();
  } else {
    fih_rc = FIH_SUCCESS;
  }
  FIH_RET(fih_rc);
}

/**************************************************************************//**
 * @brief Enables SecureFault, BusFault, UsageFault, and MemFault system
 *        exceptions.
 *****************************************************************************/
static fih_int __attribute__ ((noinline)) enable_fault_exceptions(void)
{
  uint32_t enable_mask = SCB_SHCSR_SECUREFAULTENA_Msk
                         | SCB_SHCSR_BUSFAULTENA_Msk
                         | SCB_SHCSR_USGFAULTENA_Msk
                         | SCB_SHCSR_MEMFAULTENA_Msk;

  // Enable SecureFault, BusFault, UsageFault and MemFault.
  volatile uint32_t shcsr = SCB->SHCSR | enable_mask;

  SCB->SHCSR = shcsr;

  #if defined(TFM_FIH_PROFILE_ON) && defined(TFM_FIH_PROFILE_HIGH)
  // Verify register if store instruction was glitched
  if (fih_not_eq(fih_int_encode(shcsr & enable_mask),
                 fih_int_encode(SCB->SHCSR & enable_mask))) {
    fatal_error();
    FIH_RET(FIH_FAILURE); // if fatal_error is glitched, return failure
  }
  #endif
  FIH_RET(FIH_SUCCESS);
}

/**************************************************************************//**
 * @brief Enable the FPU for the non-secure app.
 *****************************************************************************/
static fih_int __attribute__ ((noinline)) enable_ns_fpu(void)
{
  volatile uint32_t nsacr = SCB->NSACR
                            | (SCB_NSACR_CP10_Msk)  // enable CP10 Full Access
                            | (SCB_NSACR_CP11_Msk); // enable CP11 Full Access
  SCB->NSACR = nsacr;

  #if defined(TFM_FIH_PROFILE_ON) && defined(TFM_FIH_PROFILE_HIGH)
  // Verify register if store instruction was glitched
  if (fih_not_eq(fih_int_encode(nsacr), fih_int_encode(SCB->NSACR))) {
    fatal_error();
    FIH_RET(FIH_FAILURE); // if fatal_error is glitched, return failure
  }
  #endif
  FIH_RET(FIH_SUCCESS);
}

/**************************************************************************//**
 * @brief Enable the flash page locks corresponding to the bootloader and
 *        secure library code.
 *****************************************************************************/
static fih_int __attribute__ ((noinline)) enable_page_locks(void)
{
  fih_int fih_rc = FIH_SUCCESS;

  #if defined(_CMU_CLKEN1_MASK)
  CMU->CLKEN1_SET = CMU_CLKEN1_MSC;
  #endif

  size_t pages_to_lock = NUM_PAGES_TO_LOCK;

  // Iterate over pagelock registers and set as many ones needed.
  for (size_t i = 0; i < NUM_PAGELOCK_REGISTERS; ++i) {
    if (pages_to_lock < 32u) {
      // It is possible that pages_to_lock is equal to zero at this point
      // (for example when the total amount of pages to lock is zero mod 32).
      // This should not be a problem though, as pushing 0 into _SET is a no-op
      *pagelock_registers[i] = (1u << pages_to_lock) - 1;
      if (fih_not_eq(fih_int_encode(*pagelock_registers[i]),
                     fih_int_encode((1u << pages_to_lock) - 1))) {
        fatal_error();
        fih_rc = FIH_FAILURE; // if fatal_error is glitched, return failure
      }
      pages_to_lock = 0u;
      break;
    } else {
      *pagelock_registers[i] = 0xffffffffu;
      if (fih_not_eq(fih_int_encode(*pagelock_registers[i]),
                     fih_int_encode(0xffffffffu))) {
        fatal_error();
        fih_rc = FIH_FAILURE; // if fatal_error is glitched, return failure
      }
      pages_to_lock -= 32u;
    }
  }

  #if defined(_CMU_CLKEN1_MASK)
  CMU->CLKEN1_CLR = CMU_CLKEN1_MSC;
  #endif

  FIH_RET(fih_rc);
}

/**************************************************************************//**
 * @brief Start non-secure app.
 *
 * This function should not return.
 *****************************************************************************/
__WEAK void start_ns_app(void)
{
  // Set stack pointer.
  __TZ_set_MSP_NS(*((uint32_t *)(FLASH_BASE + TZ_NS_FLASH_OFFSET)));
  __TZ_set_PSP_NS(*((uint32_t *)(FLASH_BASE + TZ_NS_FLASH_OFFSET)));

  #if defined(TFM_FIH_PROFILE_ON) && defined(TFM_FIH_PROFILE_HIGH)
  // Verify MSP_NS is not glitched
  if (fih_not_eq(fih_int_encode(__TZ_get_MSP_NS()),
                 fih_int_encode(*((uint32_t *)(FLASH_BASE
                                               + TZ_NS_FLASH_OFFSET))))) {
    fatal_error();
  }
  #endif

  // Set vector table (may be done by SystemInit() on NS side, but do it here
  // to be sure).
  SCB_NS->VTOR = (FLASH_BASE + TZ_NS_FLASH_OFFSET);

  #if defined(TFM_FIH_PROFILE_ON) && defined(TFM_FIH_PROFILE_HIGH)
  // Verify NS VTOR is not glitched
  if (fih_not_eq(fih_int_encode(SCB_NS->VTOR),
                 fih_int_encode(FLASH_BASE + TZ_NS_FLASH_OFFSET))) {
    fatal_error();
  }
  #endif

  // Read address of the non-secure reset handler.
  volatile uint32_t *fp_location =
    (uint32_t *)(FLASH_BASE + TZ_NS_FLASH_OFFSET + 4UL);
  nsfunc fp = (nsfunc) * fp_location;

  // Verify that the read of the NS reset handler address is not glitched
  if (fih_not_eq(fih_int_encode((int32_t)fp),
                 fih_int_encode((int32_t)(*fp_location)))) {
    fatal_error();
  }

  // Reset the Secure MSP to the top of stack which should be located where
  // the stack seal starts. The existing stack frames on the secure stack can
  // be dismissed, and veneer functions will generate new frames starting from
  // the top of stack.
  extern uint32_t __STACK_SEAL;
  __set_MSP((uint32_t) &__STACK_SEAL);

  // NOTE:
  // Make sure the stack pointer is not moved after resetting the secure MSP
  // above, between and before the call to the NS reset handler just below.
  // Moving the stack pointer between, HERE, will break the secure stack.
  // If possible, avoid any other code in between, HERE.

  // Call the non-secure reset handler,, should not return.
  fp();
}

#if defined(MBEDTLS_PSA_CRYPTO_STORAGE_C) && defined(SLI_PSA_ITS_ENCRYPTED)

static fih_int __attribute__ ((noinline)) check_se_version(uint32_t se_version)
{
  fih_int fih_rc = FIH_FAILURE; // if fatal_error is glitched, return failure
  volatile int32_t version_diff = A_NEGATIVE_VALUE;
  #define FIH_INIT_STEP_VERFIY_SE_VERSION 3
  FIH_CFI_STEP_INIT(FIH_INIT_STEP_VERFIY_SE_VERSION);

  // Verify that the SE version newer than the oldest supported version.
  if (se_version < OLDEST_SUPPORTED_SE_FW_VERSION) {
    fatal_error();
    goto exit; // if fatal_error is glitched
  }

  FIH_CFI_STEP_DECREMENT();

  // Double check that that se_version is higher than the initial version with
  // SRK support in case the previous if statement was glitched.
  // The following subtraction is based on the assumption that both minuend and
  // subtrahend are unsigned 32-bit values masked with 0x00FFFFFFU, ref
  // definition of SLI_VERSION_REMOVE_DIE_ID.
  version_diff = SLI_VERSION_REMOVE_DIE_ID(se_version) - OLDEST_SUPPORTED_SE_FW_VERSION;
  if (version_diff < 0) {
    fatal_error();
    goto exit; // if fatal_error is glitched
  }

  FIH_CFI_STEP_DECREMENT();

  // Additional check that the version_diff is different than the initial value.
  if (fih_eq(fih_int_encode(version_diff),
             fih_int_encode(A_NEGATIVE_VALUE))) {
    fatal_error();
    goto exit; // if fatal_error is glitched
  } else {
    fih_rc = FIH_SUCCESS;
    FIH_CFI_STEP_DECREMENT();
  }

  FIH_RET(fih_rc);

  exit:
  FIH_CFI_STEP_ERR_RESET();
  FIH_RET(FIH_FAILURE);
}

#if defined(SEMAILBOX_PRESENT)
/**************************************************************************//**
 * @brief Verify that the HSE has a supported firmware version.
 *
 * The Storage Root Key must be present in order for the TrustZone-enabled
 * secure key storage to work. Support for this was added in SE FW v1.2.12,
 * which is the minimum version supported.
 *****************************************************************************/
static fih_int __attribute__ ((noinline)) verify_hse_version(void)
{
  fih_int fih_rc = FIH_FAILURE;
  #define FIH_INIT_STEP_VERIFY_HSE_VERSION  2
  FIH_CFI_STEP_INIT(FIH_INIT_STEP_VERIFY_HSE_VERSION);

  sl_se_command_context_t cmd_ctx;
  uint32_t se_version = 0;
  sl_status_t status = sl_se_get_se_version(&cmd_ctx, &se_version);
  if (status != SL_STATUS_OK) {
    fatal_error();
    goto exit; // if fatal_error is glitched
  }

  FIH_CFI_STEP_DECREMENT();

  // Check that the SE fw version is accepted.
  FIH_CALL(check_se_version, fih_rc, se_version);
  if (fih_eq(fih_rc, FIH_SUCCESS)) {
    FIH_CFI_STEP_DECREMENT();
    FIH_RET(fih_rc);
  }

  exit:
  FIH_CFI_STEP_ERR_RESET();
  fatal_error();
  FIH_RET(FIH_FAILURE); // if fatal_error is glitched, return failure
}

#else // defined(SEMAILBOX_PRESENT)

static fih_int __attribute__ ((noinline)) vse_is_mailbox_valid(void)
{
  if (!rootIsOutputMailboxValid()) {
    FIH_RET(fih_int_encode(SE_RESPONSE_MAILBOX_INVALID));
  } else {
    FIH_RET(fih_int_encode(SE_RESPONSE_OK));
  }
}

static fih_int __attribute__ ((noinline)) vse_get_reply_ptr(uint32_t **vse_reply_ptr)
{
  #if ((defined(SL_TRUSTZONE_SECURE) && !defined(SL_TRUSTZONE_PERIPHERAL_AHBRADIO_S)) \
  || (defined(SL_TRUSTZONE_PERIPHERAL_AHBRADIO_S) && SL_TRUSTZONE_PERIPHERAL_AHBRADIO_S))

    #define RDMEM_FRCRAM_MEM_BASE RDMEM_FRCRAM_S_MEM_BASE
    #define ROOT_MAILBOX_OUTPUT_BASE SYSCFG->ROOTDATA1;
    #define ROOT_MAILBOX_OUTPUT_BASE_EXPECTED ROOT_MAILBOX_OUTPUT_S_BASE
  #else
    #define RDMEM_FRCRAM_MEM_BASE RDMEM_FRCRAM_NS_MEM_BASE
  // VSE will always output the secure address, if NS is desired, caculate the NS address.
    #define ROOT_MAILBOX_OUTPUT_BASE (SYSCFG->ROOTDATA1 - RDMEM_FRCRAM_S_MEM_BASE + RDMEM_FRCRAM_NS_MEM_BASE)
    #define ROOT_MAILBOX_OUTPUT_BASE_EXPECTED (RDMEM_FRCRAM_NS_MEM_END + 1 - ROOT_MAILBOX_SIZE)
  #endif

  #if defined(TFM_FIH_PROFILE_ON) && defined(FIH_ENABLE_DELAY)
  // CMU is already set to NS during fih_delay initialisation
  // configure_sau_smu_for_fih_delay.
  CMU_TypeDef *cmu = CMU_NS;
  #else
  CMU_TypeDef *cmu = CMU_S;
  #endif

  // Store current CLKEN0 state
  uint32_t clken0_state = cmu->CLKEN0;

  cmu->CLKEN0_SET = CMU_CLKEN0_SYSCFG;

  // Get pointer to VSE mailbox reply structure
  *vse_reply_ptr = (uint32_t*)(ROOT_MAILBOX_OUTPUT_BASE);

  // Restore prior CLKEN0 state
  cmu->CLKEN0 = clken0_state;

  if ((uint32_t) *vse_reply_ptr > ROOT_MAILBOX_OUTPUT_BASE_EXPECTED
      || (uint32_t)*vse_reply_ptr < RDMEM_FRCRAM_MEM_BASE) {
    fatal_error();
  }
  FIH_RET(FIH_SUCCESS);
}

static fih_int __attribute__ ((noinline)) vse_get_se_version(const uint32_t *vse_reply_ptr, uint32_t *se_version)
{
  *se_version = vse_reply_ptr[1];
  FIH_RET(FIH_SUCCESS);
}

static fih_int __attribute__ ((noinline)) vse_get_reply_status(const uint32_t *vse_reply_ptr, uint32_t *vse_reply_status)
{
  *vse_reply_status = vse_reply_ptr[2];
  FIH_RET(FIH_SUCCESS);
}

static fih_int __attribute__ ((noinline)) vse_get_data_length(const uint32_t *vse_reply_ptr, uint32_t *vse_data_length)
{
  *vse_data_length = vse_reply_ptr[4];
  FIH_RET(FIH_SUCCESS);
}

/**************************************************************************//**
 * @brief Setup Storage Root Key (SRK)
 *
 * Reads the TrustZone Root Key / Storage Root Key passed from the VSE and
 * configures ITS to use it for NVM3 encryption.
 *****************************************************************************/
static fih_int __attribute__ ((noinline)) setup_storage_root_key(void)
{
  fih_int fih_rc = FIH_FAILURE; // if fatal_error is glitched, return failure

  #if defined(CRYPTOACC_PRESENT)

  // Size of VSE Output Mailbox instance.
  #define VSE_REPLY_SIZE_BYTES                          20UL
  #define VSE_REPLY_SIZE_WORDS         (VSE_REPLY_SIZE_BYTES / sizeof(uint32_t))
  // The data field size is the full output mailbox minus
  // the header/reply structure which is 20 bytes.
  #define ROOT_MAILBOX_DATA_SIZE      (ROOT_MAILBOX_SIZE - VSE_REPLY_SIZE_BYTES)
  #define VSE_REPLY_STATUS_TRUSTZONE_ROOT_KEY      (1 << 22)
  #define TZ_SRK_SIZE_WORDS                               8
  typedef struct {
    uint32_t data[TZ_SRK_SIZE_WORDS];
    uint32_t checksum;
  } vse_srk_t;

  #define FIH_INIT_STEP_SETUP_STORAGE_ROOT_KEY  8

  uint32_t *vse_reply = NULL;
  uint32_t se_version = 0;
  uint32_t vse_reply_status = 0;
  uint32_t vse_data_length = ROOT_MAILBOX_SIZE; // initialise to invalid size
  vse_srk_t *srk;
  uint32_t checksum = 0;
  volatile psa_status_t status = PSA_ERROR_GENERIC_ERROR;

  FIH_CFI_STEP_INIT(FIH_INIT_STEP_SETUP_STORAGE_ROOT_KEY);

  // Check that the VSE mailbox is valid
  FIH_CALL(vse_is_mailbox_valid, fih_rc);
  if (fih_not_eq(fih_rc, fih_int_encode(SE_RESPONSE_OK))) {
    fatal_error();
    goto exit; // if fatal_error is glitched
  }

  FIH_CFI_STEP_DECREMENT();

  // Get pointer to the VSE output mailbox reply structure
  FIH_CALL(vse_get_reply_ptr, fih_rc, &vse_reply);
  if (fih_not_eq(fih_rc, FIH_SUCCESS)) {
    fatal_error();
    goto exit; // if fatal_error is glitched
  }
  if (fih_eq(fih_int_encode((int32_t)vse_reply),
             fih_int_encode((int32_t)NULL))) {
    fatal_error();
    goto exit; // if fatal_error is glitched
  }

  FIH_CFI_STEP_DECREMENT();

  // Get VSE firmware version
  FIH_CALL(vse_get_se_version, fih_rc, vse_reply, &se_version);
  if (fih_not_eq(fih_rc, FIH_SUCCESS)) {
    fatal_error();
    goto exit; // if fatal_error is glitched
  }

  // Verify that the SE firmware version is accepted.
  FIH_CALL(check_se_version, fih_rc, se_version);
  if (fih_not_eq(fih_rc, FIH_SUCCESS)) {
    fatal_error();
    goto exit; // if fatal_error is glitched
  }

  FIH_CFI_STEP_DECREMENT();

  // Verify that the TrustZone Root Key flag is present in the reply status
  FIH_CALL(vse_get_reply_status, fih_rc, vse_reply, &vse_reply_status);
  if (fih_not_eq(fih_rc, FIH_SUCCESS)) {
    fatal_error();
    goto exit; // if fatal_error is glitched
  }
  if (fih_eq(fih_int_encode(vse_reply_status & VSE_REPLY_STATUS_TRUSTZONE_ROOT_KEY),
             fih_int_encode(0))) {
    fatal_error();
    goto exit; // if fatal_error is glitched
  }

  FIH_CFI_STEP_DECREMENT();

  // Read the SRK next to the mailbox, i.e. after the VSE reply header, data length and
  // checksum (+1).
  FIH_CALL(vse_get_data_length, fih_rc, vse_reply, &vse_data_length);
  if (fih_not_eq(fih_rc, FIH_SUCCESS)) {
    fatal_error();
    goto exit; // if fatal_error is glitched
  }
  if (vse_data_length > ROOT_MAILBOX_DATA_SIZE) {
    fatal_error();
    goto exit; // if fatal_error is glitched
  }

  FIH_CFI_STEP_DECREMENT();

  // Set pointer to the SRK now as we determined the VSE data length
  srk = (vse_srk_t*)(vse_reply + VSE_REPLY_SIZE_WORDS + vse_data_length + 1);

  // Verify checksum
  for (uint32_t i = 0; i < sizeof(srk->data) / sizeof(uint32_t); ++i) {
    checksum ^= srk->data[i];
  }
  if (fih_not_eq(fih_int_encode(checksum), fih_int_encode(srk->checksum))) {
    fatal_error();
    goto exit; // if fatal_error is glitched
  }

  FIH_CFI_STEP_DECREMENT();

  // Set the ITS root key. Note that this function is not dependent on PSA Crypto
  // being initialized.
  status = sli_psa_its_set_root_key((uint8_t*)srk->data, sizeof(srk->data));
  if (fih_not_eq(fih_int_encode(status), fih_int_encode(PSA_SUCCESS))) {
    fatal_error();
    goto exit; // if fatal_error is glitched
  }

  FIH_CFI_STEP_DECREMENT();

  // Clear the SRK from the mailbox location
  status = PSA_ERROR_GENERIC_ERROR;
  status = sli_psa_zeroize(srk, sizeof(vse_srk_t));
  if (fih_not_eq(fih_int_encode(status), fih_int_encode(PSA_SUCCESS))) {
    fatal_error();
    goto exit; // if fatal_error is glitched
  } else {
    fih_rc = FIH_SUCCESS;
  }

  FIH_CFI_STEP_DECREMENT();

  #else // defined(CRYPTOACC_PRESENT)
    #error "Unknown device without SEMAILBOX (HSE) or CRYPTOACC (VSE)"
  #endif // defined(CRYPTOACC_PRESENT)

  FIH_RET(fih_rc);
  exit:
  FIH_CFI_STEP_ERR_RESET();
  FIH_RET(FIH_FAILURE);
}
#endif // #if SEMAILBOX_PRESENT #else ...

#endif // defined(MBEDTLS_PSA_CRYPTO_STORAGE_C) && defined(SLI_PSA_ITS_ENCRYPTED)

// -----------------------------------------------------------------------------
// Fault handlers

__WEAK void SMU_SECURE_IRQHandler(void)
{
  fatal_error();
}

__WEAK void HardFault_Handler(void)
{
  fatal_error();
}

__WEAK void SecureFault_Handler(void)
{
  fatal_error();
}

__WEAK void UsageFault_Handler(void)
{
  fatal_error();
}

__WEAK void BusFault_Handler(void)
{
  fatal_error();
}

__WEAK void mpu_fault_handler(void)
{
  fatal_error();
}
