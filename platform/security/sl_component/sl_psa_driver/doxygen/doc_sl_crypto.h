/***************************************************************************//**
 * @file
 * @brief Overview of plugins for hardware accelerated cryptography
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

/**
   @defgroup sl_crypto_plugins Silicon Labs Cryptography Hardware Acceleration Plugins
   @brief Overview of plugins for hardware accelerated cryptography
   @{

   @section sl_crypto_intro Introduction
   The Silicon Labs distribution of mbed TLS includes alternative
   implementations (plugins) from Silicon Labs for selected mbed TLS and PSA
   Crypto library functions. The plugins use the AES-, CRYPTO-, CRYPTOACC- and
   SE hardware peripherals to accelerate low-level cryptographic primitives and
   algorithms. Available acceleration hardware depends on the target device.

   @section sl_crypto_psa_intro PSA Crypto versus mbed TLS plugins
   There are currently (mbed TLS v2.24 and forward) two sets of interfaces that
   have plugins for acceleration on Silicon Labs devices. The first interface is
   through the @ref sl_crypto "mbed TLS API plugins", which have been released
   by Silicon Labs since the mbed TLS 2.1.2 distribution. These plugins continue
   to be available, but will be deprecated and subsequently removed in a future
   release, together with the deprecation of the relevant mbed TLS APIs. It is
   these plugins that get exercised when calling cryptography APIs prefixed
   `mbedtls_*`.

   @note Note that the mbed TLS API plugins have been updated, and some now
         depend on their PSA counterparts. This is done to streamline code on
         systems that use both API sets. Users are advised to update their
         source file lists accordingly.

   The other set of plugins make up the PSA Crypto accelerator interface. These 
   drivers provide hardware acceleration when using the PSA Cryptography APIs
   (prefixed `psa_*`). Users are encouraged to migrate to PSA Cryptography APIs
   for their cryptographic processing needs at their earliest convenience. For
   products where it does not make sense to do so (legacy products, end-of-life,
   ...), the mbed TLS APIs remain available.

   For more information on the Silicon Labs implementation of the PSA Crypto
   accelerator interface across the different products, refer to 
   \ref sl_psa_drivers.

   The application note "AN1311: Mbed TLS to PSA Crypto Porting Guide" provides
   detailed information related to porting an existing application based on the
   classic mbed TLS APIs to use the new PSA Crypto APIs. The application note
   also includes detailed information about which crypto functions are
   accelerated on specific devices.

   @defgroup sl_crypto Silicon Labs Cryptography Hardware Acceleration Plugins for mbed TLS
   @brief Overview of plugins for hardware accelerated cryptography through the mbed TLS APIs
   @{

   These plugins hook into acceleration points in the relevant mbed TLS APIs,
   for the algorithms that can be accelerated by the hardware peripheral
   included in the respective device.

   The plugins support sharing of cryptography hardware in multi-threaded
   applications, as well as a reduced overhead configuration for optimal
   performance in single-threaded applications. Multi-threaded support is
   provided by the @ref sl_crypto_threading module.


   @section sl_aes_plugin AES Peripheral

   A plugin for the AES peripheral is provided for classic EFM32 and EZR32 MCUs (Series-0).

   For more details, see accelerated implementation file aes_aes.c located in
   the sl_mbedtls_support/src/ subdirectory.


   @section sl_crypto_plugin CRYPTO Peripheral

   The Series-1 devices incorporate the CRYPTO peripheral for cryptographic
   hardware acceleration. The plugins using the CRYPTO peripheral support 
   multi-threaded applications by implementing mbed TLS threading primitives and
   are located in `sl_mbedtls_support/src/crypto_*` and 
   `sl_psa_driver/src/sli_crypto_*`. These implementations are replacing the
   corresponding software implementations in `mbedtls/library`.

   Driver files supporting acceleration through legacy mbed TLS APIs (`mbedtls_*`):
   @li <b>crypto_aes.c:</b> acceleration for the AES block cipher together with
      a few common modes of operation.
   @li <b>crypto_gcm.c:</b> acceleration for the AES-GCM mode of AEAD.
   @li <b>crypto_ecp.c:</b> acceleration of ECC point multiplication (secp192r1,
      secp224r1 and secp256r1).
   @li <b>mbedtls_aes.c:</b> acceleration for AES in the ECB mode of operation.
      Uses the corresponding PSA Crypto driver for acceleration.
   @li <b>mbedtls_ccm.c:</b> acceleration for the AES-CCM mode of AEAD.
      Uses the corresponding PSA Crypto driver for acceleration.
   @li <b>mbedtls_cmac.c:</b> acceleration of the AES-CMAC algorithm for MACs.
      Uses the corresponding PSA Crypto driver for acceleration.
   @li <b>mbedtls_sha.c:</b> acceleration of SHA-1 and SHA-2 hash functions.
      Uses the corresponding PSA Crypto driver for acceleration.

   @section sl_se_crypto_plugin Secure Engine Peripheral

   The EFR32xG21, EFR32xG23 & EFR32xG24 devices incorporate the SE peripheral
   for cryptographic hardware acceleration. The plugins using the SE peripheral
   support multi-threaded applications by implementing mbed TLS threading
   primitives, and are located in `sl_mbedtls_support/src/se_*` and
   `sl_psa_driver/src/sli_se_*`. These implementations are replacing the
   corresponding software implementations in `mbedtls/library/`.

   @note The Secure Engine drivers are multi-thread capable, but do not support
         preemption. This means the application developer is responsible for not
         calling a driver-accelerated PSA API under conditions which would cause
         preemption of an already-running operation. For baremetal applications,
         this usually means not calling cryptographic operations from ISR. For
         RTOS-based applications, this boils down to not calling these 
         SE-accelerated functions from either ISR or inside critical/atomic
         sections, since the underlying mutex acquisition would fail.

   Driver files supporting acceleration through legacy mbed TLS APIs (`mbedtls_*`):
   @li <b>se_aes.c:</b> acceleration for the AES block cipher together with a
      few common modes of operation.
   @li <b>se_gcm.c:</b> acceleration for the AES-GCM mode of AEAD.
   @li <b>se_jpake.c:</b> acceleration of the Elliptic Curve (EC) J-PAKE
      protocol for key agreement.
   @li <b>mbedtls_aes.c:</b> acceleration for AES in the ECB mode of operation.
      Uses the corresponding PSA Crypto driver for acceleration.
   @li <b>mbedtls_ccm.c:</b> acceleration for the AES-CCM mode of AEAD.
      Uses the corresponding PSA Crypto driver for acceleration.
   @li <b>mbedtls_cmac.c:</b> acceleration of the AES-CMAC algorithm for MACs.
      Uses the corresponding PSA Crypto driver for acceleration.
   @li <b>mbedtls_ecdsa_ecdh.c:</b> acceleration of two common schemes built on
      Elliptic Curve Cryptography (ECC): ECDSA for signatures, and ECDH for key
      agreement. Uses the corresponding PSA Crypto driver for acceleration.
   @li <b>mbedtls_sha.c:</b> acceleration of SHA-1 and SHA-2 hash functions.
      Uses the corresponding PSA Crypto driver for acceleration.

   @section sl_se_cryptoacc_plugin CRYPTOACC Peripheral

   The EFR32xG22 devices incorporate the CRYPTOACC peripheral for cryptographic
   hardware acceleration. The plugins using the CRYPTOACC peripheral support
   multi-threaded applications by implementing mbed TLS threading primitives,
   and are located in `sl_mbedtls_support/src/cryptoacc_*` and
   `sl_psa_driver/src/sli_cryptoacc_*`. These implementations are replacing the
   corresponding software implementations in `mbedtls/library/`.

   @note The CRYPTOACC peripheral has not been hardened against side-channel
      analysis (SCA) attacks. Certain APIs in mbed TLS might give the impression
      of being secured against this class of attack, but this is not
      necessarily true if the hardware acceleration plugins are used. For
      example: some APIs operating over elliptic curves will require an RNG
      function pointer and state to be passed as arguments in order to perform
      coordinate randomization. Since the CRYPTOACC peripheral does not allow
      for this type of acceleration, these parameters will not be used. However,
      it should be stated that timing based SCA attacks are more challenging to
      perform on hardware accelerated operations of this type -- since they are
      significantly faster than their software implementation counterparts.

   Driver files supporting acceleration through legacy mbed TLS APIs (mbedtls_*):
   @li <b>cryptoacc_aes.c:</b> acceleration for the AES block cipher together
      with a few common modes of operation.
   @li <b>cryptoacc_gcm.c:</b> acceleration for the AES-GCM mode of AEAD.
   @li <b>mbedtls_aes.c:</b> acceleration for AES in the ECB mode of operation.
      Uses the corresponding PSA Crypto driver for acceleration.
   @li <b>mbedtls_ccm.c:</b> acceleration for the AES-CCM mode of AEAD.
      Uses the corresponding PSA Crypto driver for acceleration.
   @li <b>mbedtls_cmac.c:</b> acceleration of the AES-CMAC algorithm for MACs.
      Uses the corresponding PSA Crypto driver for acceleration.
   @li <b>mbedtls_ecdsa_ecdh.c:</b> acceleration of two common schemes built on
      Elliptic Curve Cryptography (ECC): ECDSA for signatures, and ECDH for key
      agreement. Uses the corresponding PSA Crypto driver for acceleration.
   @li <b>mbedtls_sha.c:</b> acceleration of SHA-1 and SHA-2 hash functions.
      Uses the corresponding PSA Crypto driver for acceleration.

   @} end group sl_crypto

   @defgroup sl_psa_drivers Silicon Labs Cryptography Hardware Acceleration Drivers for PSA Crypto
   @brief Overview of drivers for hardware accelerated cryptography through the PSA Crypto APIs
   @{

   @section Introduction
   The Silicon Labs distribution of mbed TLS includes device-specific drivers
   for selected PSA Crypto library functions. The drivers use the CRYPTO-,
   CRYPTOACC- or SE hardware peripherals to accelerate cryptographic
   primitives and algorithms according to the PSA Crypto driver model. Available
   acceleration hardware depends on the target device.

   @note The PSA Crypto driver interface is prone to change across releases.
         These interfaces are therefore prefixed with sli_* to denote their
         potential instability. Users are strongly discouraged from depending
         directly on the driver interface, and should rather use the top-level
         PSA Crypto APIs.

   For more information on the PSA Crypto accelerator driver interface, and its
   specification, see `docs/proposed/psa-driver-interface.md`.


   @section sl_psa_drivers_crypto CRYPTO peripheral drivers for PSA Crypto

   The Series-1 devices incorporate the CRYPTO peripheral for cryptographic
   hardware acceleration. 

   The drivers using the CRYPTO peripheral are located in 
   `sl_psa_driver/src/sli_crypto_*`. These implementations are
   plugged in through the PSA Crypto driver interface, and rely on 
   <b>crypto_management.c</b> to provide multi-threaded access to the driver.

   @note Although the hardware acceleration drivers have been made thread-safe,
         the PSA Crypto core implemented in mbed TLS does not fully implement
         thread safety. See \ref sl_psa_thread_safety for more information.

   Driver files for supporting acceleration through PSA Crypto APIs using the CRYPTO peripheral:
   @li <b>sli_crypto_transparent_driver_aead.c:</b> AES-CCM and AES-GCM
      acceleration support for use through the PSA Crypto API.
   @li <b>sli_crypto_transparent_driver_cipher.c:</b> AES (ECB, CTR, CFB, OFB,
      CBC) acceleration support for use through the PSA Crypto API.
   @li <b>sli_crypto_transparent_driver_hash.c:</b> SHA-1 and SHA-256
      acceleration for use through the PSA Crypto API.
   @li <b>sli_crypto_transparent_driver_mac.c:</b> AES-CMAC acceleration support
      for use through the PSA Crypto API.


   @section sl_psa_drivers_se Secure Engine peripheral drivers for PSA Crypto

   The EFR32xG21, EFR32xG23 & EFR32xG24 devices incorporate the SE peripheral
   for cryptographic hardware acceleration. 

   The drivers using the SE peripheral are located in
   `sl_psa_driver/src/sli_se_*` . These plugins also depend on Silicon Labs'
   SE Manager.

   On Vault High devices, the plugins for the SE peripheral in opaque mode
   provide support for using wrapped keys through the PSA API.

   @note The Secure Engine drivers are multi-thread capable, but do not support
         preemption. This means the application developer is responsible for not
         calling a driver-accelerated PSA API under conditions which would cause
         preemption of an already-running operation. For baremetal applications,
         this usually means not calling cryptographic operations from ISR. For
         RTOS-based applications, this boils down to not calling these 
         SE-accelerated functions from either ISR or inside critical/atomic
         sections, since the underlying mutex acquisition would fail. Also note
         that the PSA Crypto core implemented in mbed TLS does not fully
         implement thread safety. See \ref sl_psa_thread_safety for more
         information.

   Base driver files supporting acceleration through PSA Crypto APIs (all depend
   on sli_se_driver_key_management.c):
   @li <b>sli_se_driver_aead.c:</b> Supporting symmetric-key AEAD algorithms for
      both transparent and opaque SE drivers.
   @li <b>sli_se_driver_cipher.c:</b> Supporting symmetric-key cipher algorithms
      for both transparent and opaque SE drivers.
   @li <b>sli_se_driver_key_derivation.c:</b> Supporting key agreement for both
      transparent and opaque SE drivers.
   @li <b>sli_se_driver_key_management.c:</b> Supporting key management for both
      transparent and opaque SE drivers.
   @li <b>sli_se_driver_mac.c:</b> Supporting symmetric-key MAC functions for
      both transparent and opaque SE drivers.
   @li <b>sli_se_driver_signature.c:</b> Supporting elliptic-curve signature
      functions for both transparent and opaque SE drivers.
   @li <b>sli_se_transparent_driver_hash.c:</b> Accelerated hashing functions
      (SHA-1 and SHA-2 families) for use with PSA Crypto according to the PSA
      Crypto accelerator driver model.

   Driver files supporting acceleration with plaintext keys through PSA Crypto
   APIs (all depend on sli_se_driver_key_management.c):
   @li <b>sli_se_transparent_driver_aead.c:</b> Symmetric-key AEAD algorithm
      acceleration using plaintext keys (depends on sli_se_driver_aead.c).
   @li <b>sli_se_transparent_driver_cipher.c:</b> Symmetric-key block cipher
      algorithm acceleration using plaintext keys (depends on
      sli_se_driver_cipher.c).
   @li <b>sli_se_transparent_driver_hash.c:</b> Accelerated hashing functions
      (SHA-1 and SHA-2 families) for use with PSA Crypto according to the PSA
      Crypto accelerator driver model.
   @li <b>sli_se_transparent_driver_mac.c:</b> Symmetric-key MAC algorithm
      acceleration using plaintext keys (depends on sli_se_driver_mac.c).
   @li <b>sli_se_transparent_key_derivation.c:</b> Key agreement acceleration
      using plaintext keys (depends on sli_se_driver_key_derivation.c).

   Driver files supporting acceleration with wrapped keys through PSA Crypto
   APIs (all depend on sli_se_driver_key_management.c):
   @li <b>sli_se_opaque_driver_aead.c:</b> Symmetric-key AEAD algorithm
      acceleration using wrapped keys (depends on sli_se_driver_aead.c).
   @li <b>sli_se_opaque_driver_cipher.c:</b> Symmetric-key block cipher
      algorithm acceleration using wrapped keys (depends on sli_se_driver_cipher.c).
   @li <b>sli_se_opaque_driver_mac.c:</b> Symmetric-key MAC algorithm
      acceleration using wrapped keys (depends on sli_se_driver_mac.c).
   @li <b>sli_se_opaque_key_derivation.c:</b> Key agreement acceleration using
      wrapped keys (depends on sli_se_driver_key_derivation.c).


   @section sl_psa_drivers_cryptoacc CRYPTOACC peripheral drivers for PSA Crypto

   The EFR32xG22 devices incorporate the CRYPTOACC peripheral for cryptographic
   hardware acceleration. 
   
   The drivers using the CRYPTOACC peripheral are located in 
   `sl_psa_driver/src/sli_cryptoacc_*`. These implementations are
   plugged in through the PSA Crypto driver interface, and rely on 
   <b>cryptoacc_management.c</b> to provide multi-threaded access to the driver.

   @note Although the hardware acceleration drivers have been made thread-safe,
         the PSA Crypto core implemented in mbed TLS does not fully implement
         thread safety. See \ref sl_psa_thread_safety for more information.

   Driver files supporting acceleration with plaintext keys through PSA Crypto
   APIs:
   @li <b>sli_cryptoacc_transparent_driver_aead.c:</b> Symmetric-key AEAD
      algorithm acceleration using CRYPTOACC.
   @li <b>sli_cryptoacc_transparent_driver_cipher.c:</b> Symmetric-key block
      cipher algorithm acceleration using CRYPTOACC.
   @li <b>sli_cryptoacc_transparent_driver_hash.c:</b> Accelerated hashing
      functions (SHA-1 and SHA-2 families) using CRYPTOACC.
   @li <b>sli_cryptoacc_transparent_driver_mac.c:</b> Symmetric-key MAC
      algorithm acceleration using CRYPTOACC.
   @li <b>sli_cryptoacc_transparent_driver_key_derivation.c:</b> Key agreement
      acceleration using CRYPTOACC.
   @li <b>sli_cryptoacc_transparent_driver_signature.c:</b> Elliptic-curve
      signature functions acceleration using CRYPTOACC.


   @section missing_features Missing Features

   Missing features and known limitations for the PSA crypto drivers are listed
   below. 

   <b>AEAD multipart:</b>
   @li Missing support for non-12-byte IV for GCM multipart.
   @li Passing of AAD in multiple parts is only supported on Series-1 devices. 


   @} end group sl_psa_drivers

   @} end group sl_crypto_plugins */
