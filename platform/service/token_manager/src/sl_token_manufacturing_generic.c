/***************************************************************************//**
 * @file sl_token_mfg_generic.c
 * @brief TOKEN_MFG_GENERIC implementation.
 * @version 1.0.0
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

#include "sl_token_manufacturing_generic.h"
#include "sl_token_manufacturing_api.h"

void sl_get_mfg_token_string(tokTypeMfgString *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_STRING);
}

void sl_set_mfg_token_string_data(tokTypeMfgString *data)
{
  halCommonSetMfgToken(TOKEN_MFG_STRING, data);
}

void sl_get_mfg_token_board_name(tokTypeMfgBoardName *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_BOARD_NAME);
}

void sl_set_mfg_token_board_name_data(tokTypeMfgBoardName *data)
{
  halCommonSetMfgToken(TOKEN_MFG_BOARD_NAME, data);
}

void sl_get_mfg_token_manuf_id(tokTypeMfgManufId *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_MANUF_ID);
}

void sl_set_mfg_token_manuf_id_data(tokTypeMfgManufId *data)
{
  halCommonSetMfgToken(TOKEN_MFG_MANUF_ID, data);
}

void sl_get_mfg_token_ash_config(tokTypeMfgAshConfig *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_ASH_CONFIG);
}

void sl_set_mfg_token_ash_config_data(tokTypeMfgAshConfig *data)
{
  halCommonSetMfgToken(TOKEN_MFG_ASH_CONFIG, data);
}

void sl_get_mfg_token_cca_threshold(tokTypeMfgCcaThreshold *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_CCA_THRESHOLD);
}

void sl_set_mfg_token_cca_threshold_data(tokTypeMfgCcaThreshold *data)
{
  halCommonSetMfgToken(TOKEN_MFG_CCA_THRESHOLD, data);
}

void sl_get_mfg_token_ezsp_storage(tokTypeMfgEzspStorage *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_EZSP_STORAGE);
}

void sl_set_mfg_token_ezsp_storage_data(tokTypeMfgEzspStorage *data)
{
  halCommonSetMfgToken(TOKEN_MFG_EZSP_STORAGE, data);
}

void sl_get_mfg_token_bootload_aes_key(tokTypeMfgBootloadAesKey *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_BOOTLOAD_AES_KEY);
}

void sl_set_mfg_token_bootload_aes_key_data(tokTypeMfgBootloadAesKey *data)
{
  halCommonSetMfgToken(TOKEN_MFG_BOOTLOAD_AES_KEY, data);
}

void sl_get_mfg_token_thread_join_key(tokTypeMfgThreadJoinKey *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_THREAD_JOIN_KEY);
}

void sl_set_mfg_token_thread_join_key_data(tokTypeMfgThreadJoinKey *data)
{
  halCommonSetMfgToken(TOKEN_MFG_THREAD_JOIN_KEY, data);
}

void sl_get_mfg_token_eui64(tokTypeMfgEui64 *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_EUI_64);
}

void sl_set_mfg_token_eui64_data(tokTypeMfgEui64 *data)
{
  halCommonSetMfgToken(TOKEN_MFG_EUI_64, data);
}

/***************************************************************************//**
 * Only available on series 1, series 2
 ******************************************************************************/
#ifndef EMBER_TEST
void sl_get_mfg_token_ember_eui64(tokTypeMfgEmberEui64 *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_EMBER_EUI_64);
}

void sl_set_mfg_token_ember_eui64_data(tokTypeMfgEmberEui64 *data)
{
  halCommonSetMfgToken(TOKEN_MFG_EMBER_EUI_64, data);
}

void sl_get_mfg_token_custom_version(tokTypeMfgCustomVersion *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_CUSTOM_VERSION);
}

void sl_set_mfg_token_custom_version_data(tokTypeMfgCustomVersion *data)
{
  halCommonSetMfgToken(TOKEN_MFG_CUSTOM_VERSION, data);
}

void sl_get_mfg_token_custom_eui64(tokTypeMfgCustomEui64 *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_CUSTOM_EUI_64);
}

void sl_set_mfg_token_custom_eui64_data(tokTypeMfgCustomEui64 *data)
{
  halCommonSetMfgToken(TOKEN_MFG_CUSTOM_EUI_64, data);
}

void sl_get_mfg_token_phy_config(tokTypeMfgPhyConfig *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_PHY_CONFIG);
}

void sl_set_mfg_token_phy_config_data(tokTypeMfgPhyConfig *data)
{
  halCommonSetMfgToken(TOKEN_MFG_PHY_CONFIG, data);
}

void sl_get_mfg_token_synth_freq_offset(tokTypeMfgSynthFreqOffset *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_SYNTH_FREQ_OFFSET);
}

void sl_set_mfg_token_synth_freq_offset_data(tokTypeMfgSynthFreqOffset *data)
{
  halCommonSetMfgToken(TOKEN_MFG_SYNTH_FREQ_OFFSET, data);
}

void sl_get_mfg_token_xo_tune(tokTypeMfgXoTune *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_XO_TUNE);
}

void sl_set_mfg_token_xo_tune_data(tokTypeMfgXoTune *data)
{
  halCommonSetMfgToken(TOKEN_MFG_XO_TUNE, data);
}

void sl_get_mfg_token_zwave_country_freq(tokTypeMfgZwaveCountryFreq *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_ZWAVE_COUNTRY_FREQ);
}

void sl_set_mfg_token_zwave_country_freq_data(tokTypeMfgZwaveCountryFreq *data)
{
  halCommonSetMfgToken(TOKEN_MFG_ZWAVE_COUNTRY_FREQ, data);
}

void sl_get_mfg_token_zwave_hw_version(tokTypeMfgZwaveHardwareVersion *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_ZWAVE_HW_VERSION);
}

void sl_set_mfg_token_zwave_hw_version_data(tokTypeMfgZwaveHardwareVersion *data)
{
  halCommonSetMfgToken(TOKEN_MFG_ZWAVE_HW_VERSION, data);
}

void sl_get_mfg_token_zwave_pseudo_random_number(tokTypeMfgZwavePseudoRandomNumber *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_ZWAVE_PSEUDO_RANDOM_NUMBER);
}

void sl_set_mfg_token_zwave_pseudo_random_number_data(tokTypeMfgZwavePseudoRandomNumber *data)
{
  halCommonSetMfgToken(TOKEN_MFG_ZWAVE_PSEUDO_RANDOM_NUMBER, data);
}

void sl_get_mfg_token_serial_number(tokTypeMfgSerialNumber *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_SERIAL_NUMBER);
}

void sl_set_mfg_token_serial_number_data(tokTypeMfgSerialNumber *data)
{
  halCommonSetMfgToken(TOKEN_MFG_SERIAL_NUMBER, data);
}

void sl_get_mfg_token_lfxo_tune(tokTypeMfgLfxoTune *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_LFXO_TUNE);
}

void sl_set_mfg_token_lfxo_tune_data(tokTypeMfgLfxoTune *data)
{
  halCommonSetMfgToken(TOKEN_MFG_LFXO_TUNE, data);
}

void sl_get_mfg_token_ctune(tokTypeMfgCTune *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_CTUNE);
}

void sl_set_mfg_token_ctune_data(tokTypeMfgCTune *data)
{
  halCommonSetMfgToken(TOKEN_MFG_CTUNE, data);
}

void sl_get_mfg_token_kit_signature(tokTypeMfgKitSignature *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_KIT_SIGNATURE);
}

void sl_set_mfg_token_kit_signature_data(tokTypeMfgKitSignature *data)
{
  halCommonSetMfgToken(TOKEN_MFG_KIT_SIGNATURE, data);
}

void sl_get_mfg_token_lockbits_plw(tokTypeLockBitsPlw *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_LOCKBITS_PLW);
}

void sl_set_mfg_token_lockbits_plw_data(tokTypeLockBitsPlw *data)
{
  halCommonSetMfgToken(TOKEN_MFG_LOCKBITS_PLW, data);
}

void sl_get_mfg_token_lockbits_clw0(tokTypeLockBitsClw0 *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_LOCKBITS_CLW0);
}

void sl_set_mfg_token_lockbits_clw0_data(tokTypeLockBitsClw0 *data)
{
  halCommonSetMfgToken(TOKEN_MFG_LOCKBITS_CLW0, data);
}

void sl_get_mfg_token_lockbits_mlw(tokTypeLockBitsMlw *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_LOCKBITS_MLW);
}

void sl_set_mfg_token_lockbits_mlw_data(tokTypeLockBitsMlw *data)
{
  halCommonSetMfgToken(TOKEN_MFG_LOCKBITS_MLW, data);
}

void sl_get_mfg_token_lockbits_ulw(tokTypeLockBitsUlw *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_LOCKBITS_ULW);
}

void sl_set_mfg_token_lockbits_ulw_data(tokTypeLockBitsUlw *data)
{
  halCommonSetMfgToken(TOKEN_MFG_LOCKBITS_ULW, data);
}

void sl_get_mfg_token_lockbits_dlw(tokTypeLockBitsDlw *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_LOCKBITS_DLW);
}

void sl_set_mfg_token_lockbits_dlw_data(tokTypeLockBitsDlw *data)
{
  halCommonSetMfgToken(TOKEN_MFG_LOCKBITS_DLW, data);
}

void sl_get_mfg_token_cbke_data(tokTypeMfgCbkeData *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_CBKE_DATA);
}

void sl_set_mfg_token_cbke_data(tokTypeMfgCbkeData *data)
{
  halCommonSetMfgToken(TOKEN_MFG_CBKE_DATA, data);
}

void sl_get_mfg_token_security_config(tokTypeMfgSecurityConfig *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_SECURITY_CONFIG);
}

void sl_set_mfg_token_security_config_data(tokTypeMfgSecurityConfig *data)
{
  halCommonSetMfgToken(TOKEN_MFG_SECURITY_CONFIG, data);
}

void sl_get_mfg_token_installation_code(tokTypeMfgInstallationCode *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_INSTALLATION_CODE);
}

void sl_set_mfg_token_installation_code_data(tokTypeMfgInstallationCode *data)
{
  halCommonSetMfgToken(TOKEN_MFG_INSTALLATION_CODE, data);
}

void sl_get_mfg_token_secure_bootloader_key(tokTypeMfgSecureBootloaderKey *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_SECURE_BOOTLOADER_KEY);
}

void sl_set_mfg_token_secure_bootloader_key_data(tokTypeMfgSecureBootloaderKey *data)
{
  halCommonSetMfgToken(TOKEN_MFG_SECURE_BOOTLOADER_KEY, data);
}

void sl_get_mfg_token_cbke283k1_data(tokTypeMfgCbke283k1Data *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_CBKE_283K1_DATA);
}

void sl_set_mfg_token_cbke283k1_data(tokTypeMfgCbke283k1Data *data)
{
  halCommonSetMfgToken(TOKEN_MFG_CBKE_283K1_DATA, data);
}

void sl_get_mfg_token_signed_bootloader_key_x(tokTypeMfgSignedBootloaderKeyX *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_SIGNED_BOOTLOADER_KEY_X);
}

void sl_set_mfg_token_signed_bootloader_key_x_data(tokTypeMfgSignedBootloaderKeyX *data)
{
  halCommonSetMfgToken(TOKEN_MFG_SIGNED_BOOTLOADER_KEY_X, data);
}

void sl_get_mfg_token_signed_bootloader_key_y(tokTypeMfgSignedBootloaderKeyY *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_SIGNED_BOOTLOADER_KEY_Y);
}

void sl_set_mfg_token_signed_bootloader_key_y_data(tokTypeMfgSignedBootloaderKeyY *data)
{
  halCommonSetMfgToken(TOKEN_MFG_SIGNED_BOOTLOADER_KEY_Y, data);
}

void sl_get_mfg_token_nvm3_crypto_key(tokTypeMfgNvm3CryptoKey *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_NVM3_CRYPTO_KEY);
}

void sl_set_mfg_token_nvm3_crypto_key_data(tokTypeMfgNvm3CryptoKey *data)
{
  halCommonSetMfgToken(TOKEN_MFG_NVM3_CRYPTO_KEY, data);
}

void sl_get_mfg_token_zw_prk(tokTypeMfgZwavePrivateKey *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_ZW_PRK);
}

void sl_set_mfg_token_zw_prk_data(tokTypeMfgZwavePrivateKey *data)
{
  halCommonSetMfgToken(TOKEN_MFG_ZW_PRK, data);
}

void sl_get_mfg_token_zw_puk(tokTypeMfgZwavePublicKey *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_ZW_PUK);
}

void sl_set_mfg_token_zw_puk_data(tokTypeMfgZwavePublicKey *data)
{
  halCommonSetMfgToken(TOKEN_MFG_ZW_PUK, data);
}

void sl_get_mfg_token_zw_qr_code(tokTypeMfgQRCode *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_ZW_QR_CODE);
}

void sl_set_mfg_token_zw_qr_code_data(tokTypeMfgQRCode *data)
{
  halCommonSetMfgToken(TOKEN_MFG_ZW_QR_CODE, data);
}

void sl_get_mfg_token_zw_initialized(tokTypeMfgZwaveInitialized *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_ZW_INITIALIZED);
}

void sl_set_mfg_token_zw_initialized_data(tokTypeMfgZwaveInitialized *data)
{
  halCommonSetMfgToken(TOKEN_MFG_ZW_INITIALIZED, data);
}

void sl_get_mfg_token_zw_qr_code_ext(tokTypeMfgQRCode *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_ZW_QR_CODE_EXT);
}

void sl_set_mfg_token_zw_qr_code_ext_data(tokTypeMfgQRCode *data)
{
  halCommonSetMfgToken(TOKEN_MFG_ZW_QR_CODE_EXT, data);
}

/***************************************************************************//**
 * Only available on unix
 ******************************************************************************/
#else
void sl_get_mfg_token_nvdata_version(tokTypeMfgNvdataVersion *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_NVDATA_VERSION);
}

void sl_set_mfg_token_nvdata_version_data(tokTypeMfgNvdataVersion *data)
{
  halCommonSetMfgToken(TOKEN_MFG_NVDATA_VERSION, data);
}

void sl_get_mfg_token_eui64_hash(tokTypeMfgEui64Hash *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_EUI_64_HASH);
}

void sl_set_mfg_token_eui64_hash_data(tokTypeMfgEui64Hash *data)
{
  halCommonSetMfgToken(TOKEN_MFG_EUI_64_HASH, data);
}

void sl_get_mfg_token_radio_bands_supported(tokTypeMfgRadioBandsSupported *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_RADIO_BANDS_SUPPORTED);
}

void sl_set_mfg_token_radio_bands_supported_data(tokTypeMfgRadioBandsSupported *data)
{
  halCommonSetMfgToken(TOKEN_MFG_RADIO_BANDS_SUPPORTED, data);
}

void sl_get_mfg_token_radio_crystal_offset(tokTypeMfgRadioCrystalOffset *data)
{
  halCommonGetMfgToken(data, TOKEN_MFG_RADIO_CRYSTAL_OFFSET);
}

void sl_set_mfg_token_radio_crystal_offset_data(tokTypeMfgRadioCrystalOffset *data)
{
  halCommonSetMfgToken(TOKEN_MFG_RADIO_CRYSTAL_OFFSET, data);
}
#endif  // EMBER_TEST
