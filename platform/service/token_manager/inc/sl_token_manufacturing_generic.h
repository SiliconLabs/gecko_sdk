/***************************************************************************//**
 * @file
 * @brief Cortex-M3 Generic MFG token system
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef SL_TOKEN_MFG_GENERIC_H_
#define SL_TOKEN_MFG_GENERIC_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//--- User Data ---
typedef uint8_t tokTypeMfgEmberEui64[8];
typedef uint8_t tokTypeMfgCustomEui64[8];
typedef uint16_t tokTypeMfgCustomVersion;
typedef uint8_t tokTypeMfgString[16];
typedef uint8_t tokTypeMfgBoardName[16];
typedef uint16_t tokTypeMfgManufId;
typedef uint16_t tokTypeMfgPhyConfig;
typedef uint16_t tokTypeMfgAshConfig;
typedef uint16_t tokTypeMfgSynthFreqOffset;
typedef uint16_t tokTypeMfgCcaThreshold;
typedef uint8_t tokTypeMfgEzspStorage[8];
typedef uint16_t tokTypeMfgXoTune;
typedef uint8_t tokTypeMfgZwaveCountryFreq;
typedef uint8_t tokTypeMfgZwaveHardwareVersion;
typedef uint8_t tokTypeMfgZwavePseudoRandomNumber[16];
typedef uint8_t tokTypeMfgSerialNumber[16];
typedef uint8_t tokTypeMfgLfxoTune;
typedef uint16_t tokTypeMfgCTune;
typedef uint8_t tokTypeMfgKitSignature[4];
typedef uint8_t tokTypeMfgEui64[8];

//--- Lock Bits ---
// Main block Page Lock Words (PLWs)
typedef uint32_t tokTypeLockBitsPlw[4];
// Configuration Word Zero (CLW0)
typedef uint32_t tokTypeLockBitsClw0;
// Mass erase Lock Word (MLW)
typedef uint32_t tokTypeLockBitsMlw;
// User data page Lock Word (ULWs)
typedef uint32_t tokTypeLockBitsUlw;
// Debug Lock Word (DLW)
typedef uint32_t tokTypeLockBitsDlw;

//--- Lock Bits Data ---
// Smart Energy 1.0 (ECC 163k1 based crypto - 80-bit symmetric equivalent)
typedef struct {
  uint8_t certificate[48];
  uint8_t caPublicKey[22];
  uint8_t privateKey[21];
  // The bottom flag bit is 1 for uninitialized, 0 for initialized.
  // The other flag bits should be set to 0 at initialization.
  uint8_t flags;
} tokTypeMfgCbkeData;
typedef uint16_t tokTypeMfgSecurityConfig;
typedef struct {
  // The bottom flag bit is 1 for uninitialized, 0 for initialized.
  // Bits 1 and 2 give the size of the value string:
  // 0 = 6 bytes, 1 = 8 bytes, 2 = 12 bytes, 3 = 16 bytes.
  // The other flag bits should be set to 0 at initialization.
  // Special flags support.  Due to a bug in the way some customers
  // had programmed the flags field, we will also examine the upper
  // bits 9 and 10 for the size field.  Those bits are also reserved.
  uint16_t flags;
  uint8_t value[16];
  uint16_t crc;
} tokTypeMfgInstallationCode;
typedef struct {
  uint8_t data[16];  // AES-128 key
} tokTypeMfgSecureBootloaderKey;
// Smart Energy 1.2 (ECC 283k1 based crypto - 128-bit symmetric equivalent)
typedef struct {
  uint8_t certificate[74];
  uint8_t caPublicKey[37];
  uint8_t privateKey[36];
  // The bottom flag bit is 1 for uninitialized, 0 for initialized.
  // The other flag bits should be set to 0 at initialization.
  uint8_t flags;
} tokTypeMfgCbke283k1Data;
typedef uint8_t tokTypeMfgBootloadAesKey[16];
typedef struct {
  uint8_t data[32];  // ECDSA key point on P256 curve
} tokTypeMfgSignedBootloaderKeyX;
typedef struct {
  uint8_t data[32];  // ECDSA key point on P256 curve
} tokTypeMfgSignedBootloaderKeyY;
// Network join key with max length of 32 bytes
typedef struct {
  uint8_t joinKey[32];
  uint16_t joinKeyLength;
} tokTypeMfgThreadJoinKey;
typedef uint8_t tokTypeMfgNvm3CryptoKey[16];
typedef uint8_t tokTypeMfgZwavePrivateKey[32];
typedef uint8_t tokTypeMfgZwavePublicKey[32];
typedef uint8_t tokTypeMfgQRCode[90];
typedef uint8_t tokTypeMfgZwaveInitialized[1];

typedef uint16_t tokTypeMfgNvdataVersion;
typedef uint8_t tokTypeMfgEui64Hash[8];
typedef uint8_t tokTypeMfgRadioBandsSupported;
typedef int8_t tokTypeMfgRadioCrystalOffset;

/***************************************************************************//**
 * Available on series 1, series 2 and unix
 ******************************************************************************/
// Get manufacturing token string
void sl_get_mfg_token_string(tokTypeMfgString *data);

// Set manufacturing token string data
void sl_set_mfg_token_string_data(tokTypeMfgString *data);

// Get manufacturing token board name
void sl_get_mfg_token_board_name(tokTypeMfgBoardName *data);

// Set manufacturing token board name
void sl_set_mfg_token_board_name_data(tokTypeMfgBoardName *data);

// Get manufacturing token manufacturing ID
void sl_get_mfg_token_manuf_id(tokTypeMfgManufId *data);

// Set manufacturing token manufacturing ID
void sl_set_mfg_token_manuf_id_data(tokTypeMfgManufId *data);

// Get manufacturing token ASH config
void sl_get_mfg_token_ash_config(tokTypeMfgAshConfig *data);

// Set manufacturing token ASH config
void sl_set_mfg_token_ash_config_data(tokTypeMfgAshConfig *data);

// Get manufacturing token CCA threshold
void sl_get_mfg_token_cca_threshold(tokTypeMfgCcaThreshold *data);

// Set manufacturing token CCA threshold
void sl_set_mfg_token_cca_threshold_data(tokTypeMfgCcaThreshold *data);

// Get manufacturing token EZSP storage
void sl_get_mfg_token_ezsp_storage(tokTypeMfgEzspStorage *data);

// Set manufacturing token EZSP storage
void sl_set_mfg_token_ezsp_storage_data(tokTypeMfgEzspStorage *data);

// Get manufacturing token bootloader AES key
void sl_get_mfg_token_bootload_aes_key(tokTypeMfgBootloadAesKey *data);

// Set manufacturing token bootloader AES key
void sl_set_mfg_token_bootload_aes_key_data(tokTypeMfgBootloadAesKey *data);

// Get manufacturing token thread join key
void sl_get_mfg_token_thread_join_key(tokTypeMfgThreadJoinKey *data);

// Set manufacturing token thread join key
void sl_set_mfg_token_thread_join_key_data(tokTypeMfgThreadJoinKey *data);

// Get manufacturing token EUI64
void sl_get_mfg_token_eui64(tokTypeMfgEui64 *data);

// Set manufacturing token EUI64
void sl_set_mfg_token_eui64_data(tokTypeMfgEui64 *data);

/***************************************************************************//**
 * Only available on series 1, series 2
 ******************************************************************************/
#ifndef EMBER_TEST
// Get manufacturing token Ember EUI64
void sl_get_mfg_token_ember_eui64(tokTypeMfgEmberEui64 *data);

// Set manufacturing token Ember EUI64
void sl_set_mfg_token_ember_eui64_data(tokTypeMfgEmberEui64 *data);

// Get manufacturing token Custom version
void sl_get_mfg_token_custom_version(tokTypeMfgCustomVersion *data);

// Set manufacturing token Custom version
void sl_set_mfg_token_custom_version_data(tokTypeMfgCustomVersion *data);

// Get manufacturing token custom EUI64
void sl_get_mfg_token_custom_eui64(tokTypeMfgCustomEui64 *data);

// Set manufacturing token custom EUI64
void sl_set_mfg_token_custom_eui64_data(tokTypeMfgCustomEui64 *data);

// Get manufacturing token PHY config
void sl_get_mfg_token_phy_config(tokTypeMfgPhyConfig *data);

// Set manufacturing token PHY config
void sl_set_mfg_token_phy_config_data(tokTypeMfgPhyConfig *data);

// Get manufacturing token synth frequency offset
void sl_get_mfg_token_synth_freq_offset(tokTypeMfgSynthFreqOffset *data);

// Set manufacturing token synth frequency offset
void sl_set_mfg_token_synth_freq_offset_data(tokTypeMfgSynthFreqOffset *data);

// Get manufacturing token XO tune
void sl_get_mfg_token_xo_tune(tokTypeMfgXoTune *data);

// Set manufacturing token XO tune
void sl_set_mfg_token_xo_tune_data(tokTypeMfgXoTune *data);

// Get manufacturing token Zwave country frequency
void sl_get_mfg_token_zwave_country_freq(tokTypeMfgZwaveCountryFreq *data);

// Set manufacturing token Zwave country frequency
void sl_set_mfg_token_zwave_country_freq_data(tokTypeMfgZwaveCountryFreq *data);

// Get manufacturing token Zwave HW version
void sl_get_mfg_token_zwave_hw_version(tokTypeMfgZwaveHardwareVersion *data);

// Set manufacturing token Zwave HW version
void sl_set_mfg_token_zwave_hw_version_data(tokTypeMfgZwaveHardwareVersion *data);

// Get manufacturing token Zwave Pseudo random number
void sl_get_mfg_token_zwave_pseudo_random_number(tokTypeMfgZwavePseudoRandomNumber *data);

// Set manufacturing token Zwave Pseudo random number
void sl_set_mfg_token_zwave_pseudo_random_number_data(tokTypeMfgZwavePseudoRandomNumber *data);

// Get manufacturing token serial number
void sl_get_mfg_token_serial_number(tokTypeMfgSerialNumber *data);

// Set manufacturing token serial number
void sl_set_mfg_token_serial_number_data(tokTypeMfgSerialNumber *data);

// Get manufacturing token LFXO tune
void sl_get_mfg_token_lfxo_tune(tokTypeMfgLfxoTune *data);

// Set manufacturing token LFXO tune
void sl_set_mfg_token_lfxo_tune_data(tokTypeMfgLfxoTune *data);

// Get manufacturing token CTune
void sl_get_mfg_token_ctune(tokTypeMfgCTune *data);

// Set manufacturing token CTune
void sl_set_mfg_token_ctune_data(tokTypeMfgCTune *data);

// Get manufacturing token kit signature
void sl_get_mfg_token_kit_signature(tokTypeMfgKitSignature *data);

// Set manufacturing token kit signature
void sl_set_mfg_token_kit_signature_data(tokTypeMfgKitSignature *data);

// Get manufacturing token lockbits PLW
void sl_get_mfg_token_lockbits_plw(tokTypeLockBitsPlw *data);

// Set manufacturing token lockbits PLW
void sl_set_mfg_token_lockbits_plw_data(tokTypeLockBitsPlw *data);

// Get manufacturing token lockbits CLOW0
void sl_get_mfg_token_lockbits_clw0(tokTypeLockBitsClw0 *data);

// Set manufacturing token lockbits CLOW0
void sl_set_mfg_token_lockbits_clw0_data(tokTypeLockBitsClw0 *data);

// Get manufacturing token lockbits MLW
void sl_get_mfg_token_lockbits_mlw(tokTypeLockBitsMlw *data);

// Set manufacturing token lockbits MLW
void sl_set_mfg_token_lockbits_mlw_data(tokTypeLockBitsMlw *data);

// Get manufacturing token lockbits ULW
void sl_get_mfg_token_lockbits_ulw(tokTypeLockBitsUlw *data);

// Set manufacturing token lockbits ULW
void sl_set_mfg_token_lockbits_ulw_data(tokTypeLockBitsUlw *data);

// Get manufacturing token lockbits DLW
void sl_get_mfg_token_lockbits_dlw(tokTypeLockBitsDlw *data);

// Set manufacturing token lockbits DLW
void sl_set_mfg_token_lockbits_dlw_data(tokTypeLockBitsDlw *data);

// Get manufacturing token CBKE Data
void sl_get_mfg_token_cbke_data(tokTypeMfgCbkeData *data);

// Set manufacturing token CBKE Data
void sl_set_mfg_token_cbke_data(tokTypeMfgCbkeData *data);

// Get manufacturing token security config
void sl_get_mfg_token_security_config(tokTypeMfgSecurityConfig *data);

// Set manufacturing token security config
void sl_set_mfg_token_security_config_data(tokTypeMfgSecurityConfig *data);

// Get manufacturing token installation code
void sl_get_mfg_token_installation_code(tokTypeMfgInstallationCode *data);

// Set manufacturing token installation code
void sl_set_mfg_token_installation_code_data(tokTypeMfgInstallationCode *data);

// Get manufacturing token secure bootloader key
void sl_get_mfg_token_secure_bootloader_key(tokTypeMfgSecureBootloaderKey *data);

// Set manufacturing token secure bootloader key
void sl_set_mfg_token_secure_bootloader_key_data(tokTypeMfgSecureBootloaderKey *data);

// Get manufacturing token CBKE 283K1 data
void sl_get_mfg_token_cbke283k1_data(tokTypeMfgCbke283k1Data *data);

// Set manufacturing token CBKE 283K1 data
void sl_set_mfg_token_cbke283k1_data(tokTypeMfgCbke283k1Data *data);

// Get manufacturing token signed bootloader key X
void sl_get_mfg_token_signed_bootloader_key_x(tokTypeMfgSignedBootloaderKeyX *data);

// Set manufacturing token signed bootloader key X
void sl_set_mfg_token_signed_bootloader_key_x_data(tokTypeMfgSignedBootloaderKeyX *data);

// Get manufacturing token signed bootloader key Y
void sl_get_mfg_token_signed_bootloader_key_y(tokTypeMfgSignedBootloaderKeyY *data);

// Set manufacturing token signed bootloader key Y
void sl_set_mfg_token_signed_bootloader_key_y_data(tokTypeMfgSignedBootloaderKeyY *data);

// Get manufacturing token NVM3 crypto key
void sl_get_mfg_token_nvm3_crypto_key(tokTypeMfgNvm3CryptoKey *data);

// Set manufacturing token NVM3 crypto key
void sl_set_mfg_token_nvm3_crypto_key_data(tokTypeMfgNvm3CryptoKey *data);

// Get manufacturing token zwave private key
void sl_get_mfg_token_zw_prk(tokTypeMfgZwavePrivateKey *data);

// Set manufacturing token zwave private key
void sl_set_mfg_token_zw_prk_data(tokTypeMfgZwavePrivateKey *data);

// Get manufacturing token zwave public key
void sl_get_mfg_token_zw_puk(tokTypeMfgZwavePublicKey *data);

// Set manufacturing token zwave public key
void sl_set_mfg_token_zw_puk_data(tokTypeMfgZwavePublicKey *data);

// Get manufacturing token ZW QR code
void sl_get_mfg_token_zw_qr_code(tokTypeMfgQRCode *data);

// Set manufacturing token ZW QR code
void sl_set_mfg_token_zw_qr_code_data(tokTypeMfgQRCode *data);

// Get manufacturing token ZW initialized
void sl_get_mfg_token_zw_initialized(tokTypeMfgZwaveInitialized *data);

// Set manufacturing token ZW initialized
void sl_set_mfg_token_zw_initialized_data(tokTypeMfgZwaveInitialized *data);

// Get manufacturing token ZW QR code external
void sl_get_mfg_token_zw_qr_code_ext(tokTypeMfgQRCode *data);

// Set manufacturing token ZW QR code external
void sl_set_mfg_token_zw_qr_code_ext_data(tokTypeMfgQRCode *data);

/***************************************************************************//**
 * Only available on unix
 ******************************************************************************/
#else
// Get manufacturing token NVDATA version
void sl_get_mfg_token_nvdata_version(tokTypeMfgNvdataVersion *data);

// Set manufacturing token NVDATA version
void sl_set_mfg_token_nvdata_version_data(tokTypeMfgNvdataVersion *data);

// Get manufacturing token EUI64 Hash
void sl_get_mfg_token_eui64_hash(tokTypeMfgEui64Hash *data);

// Set manufacturing token EUI64 Hash
void sl_set_mfg_token_eui64_hash_data(tokTypeMfgEui64Hash *data);

// Get manufacturing token Radio bands supported
void sl_get_mfg_token_radio_bands_supported(tokTypeMfgRadioBandsSupported *data);

// Set manufacturing token Radio bands supported
void sl_set_mfg_token_radio_bands_supported_data(tokTypeMfgRadioBandsSupported *data);

// Get manufacturing token Radio crytal offset
void sl_get_mfg_token_radio_crystal_offset(tokTypeMfgRadioCrystalOffset *data);

// Set manufacturing token Radio crytal offset
void sl_set_mfg_token_radio_crystal_offset_data(tokTypeMfgRadioCrystalOffset *data);
#endif  // EMBER_TEST

#ifdef __cplusplus
}
#endif

#endif /* SL_TOKEN_MFG_GENERIC_H_ */
