# TrustZone PSA Crypto ECDH (Non-secure application)


This example uses the PSA Crypto API to perform ECDH key agreement on the supported device.


The Elliptic Curve Diffie-Hellman (ECDH) is an anonymous key agreement protocol that allows two parties, each having an elliptic-curve private-public key pair, to establish a shared secret over an insecure channel.


In this example, two peers (client and server) each generate their Elliptic Curve Cryptography (ECC) key pair. They exchange public keys and compute a shared secret using their private ECC keys. These secrets are compared with each other to make sure they are equal.


The example redirects standard I/O to the virtual serial port (VCOM) of the kit. By default, the serial port setting is 115200 bps and 8-N-1 configuration.


The example has been instrumented with code to count the number of clock cycles spent in different operations. The results are printed on the VCOM serial port console. This feature can be disabled by defining `PSA_CRYPTO_PRINT=0` (default is 1) in the IDE setting (`Preprocessor->Defined symbols`).


## Key Storage


The following key storages are supported in this example:


* Volatile plain key in RAM
* Persistent plain key in [NVM3](https://docs.silabs.com/gecko-platform/3.1/driver/api/group-nvm3)
* Volatile wrapped key in RAM (Secure Vault High only)
* Persistent wrapped key in NVM3 (Secure Vault High only)


## Elliptic Curve Key


The following elliptic curve keys are supported in this example:


##### `PSA_ECC_FAMILY_SECP_R1` :


* SECP192R1 - 192-bit
* SECP256R1 - 256-bit
* SECP384R1 - 384-bit
* SECP521R1 - 521-bit


##### `PSA_ECC_FAMILY_MONTGOMERY` :

* CURVE25519 (X25519) - 255-bit
* CURVE448 (X448) - 448-bit (Secure Vault High only)


## Key Agreement Algorithm


The following key agreement algorithm is supported in this example:


* `PSA_ALG_ECDH`


The `PSA_ALG_KEY_AGREEMENT(PSA_ALG_ECDH, PSA_ALG_HKDF(hash_alg))` algorithm is used in the **PSA Crypto KDF** example.


## PSA Crypto API


The following PSA Crypto APIs are used in this example:


* `psa_crypto_init`
* `psa_key_attributes_init`
* `psa_set_key_type`
* `psa_set_key_bits`
* `psa_set_key_usage_flags`
* `psa_set_key_algorithm`
* `psa_set_key_id`
* `psa_set_key_lifetime`
* `psa_generate_key`
* `psa_reset_key_attributes`
* `psa_export_public_key`
* `psa_raw_key_agreement`
* `psa_destroy_key`
* `mbedtls_psa_crypto_free`


## Getting Started


The Non-secure application needs to work with the Secure application on a workspace (see readme in `tz_psa_crypto_ecdh_ws`).


## Additional Information


1. The example uses the CTR-DRBG, a pseudo-random number generator (PRNG) included in [Mbed TLS](https://docs.silabs.com/mbed-tls/latest/) to generate the random number. If the example is running on a device that includes a TRNG (True Random Number Generator) hardware module, the TRNG will be used as an entropy source to seed the CTR-DRBG. If the device does not incorporate a TRNG, the example will use [RAIL](https://docs.silabs.com/rail/latest/) or NV (non-volatile) seed (requires NVM3) as the entropy source.
2. If an algorithm is not supported in the hardware accelerator of the selected device, the PSA Crypto will use the software fallback feature in Mbed TLS.
3. The PSA Crypto does not yet support software fallback on the `CURVE448` curve.
4. The HSE Secure Vault Mid devices require SE firmware v1.2.11 or higher (EFR32xG21) and v2.1.7 or higher (other HSE devices) to support hardware acceleration on `CURVE25519`.
5. Change the `CLIENT_KEY_ID` and `SERVER_KEY_ID` values in `app_process.h` if these key IDs had already existed in NVM3.
6. The default optimization level is `Optimize for debugging (-Og)` on Simplicity IDE and `None` on IAR Embedded Workbench.

## Resources


[AN1311: Integrating Crypto Functionality Using PSA Crypto Compared to Mbed TLS](https://www.silabs.com/documents/public/application-notes/an1311-mbedtls-psa-crypto-porting-guide.pdf)
[AN1374: Series 2 TrustZone](https://www.silabs.com/documents/public/application-notes/an1374-trustzone.pdf)


