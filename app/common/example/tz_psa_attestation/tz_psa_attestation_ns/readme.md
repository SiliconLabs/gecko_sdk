# TrustZone PSA Attestation (Non-secure application)


This example uses the PSA attestation API to fetch the PSA attestation token on the supported Series 2 device.

The example also demonstrates how the PSA attestation token can be parsed and printed in a human-readable format. Parsing and printing the PSA attestation token on the chip might not be a typical use case. But it can showcase the structure and capabilities of the PSA attestation token.

An attestation token is a token that contains cryptographically signed claims about the device. In other words, it provides a way to securely attest certain device information, such as the serial number and security configuration. The PSA attestation token is a COSE_Sign1 structure that encapsulates the signed CBOR Web Token containing the claims.

The example redirects standard I/O to the virtual serial port (VCOM) of the kit. By default, the serial port setting is 115200 bps and 8-N-1 configuration.

The example has been instrumented with code to count the number of clock cycles spent in different operations. The results are printed on the VCOM serial port console. This feature can be disabled by defining `PSA_CRYPTO_PRINT=0` (default is 1) in the IDE setting (`Preprocessor->Defined symbols`).

## PSA attestation API


The following PSA attestation APIs are used in this example:


* `psa_initial_attest_get_token_size`
* `psa_initial_attest_get_token`
* `sl_tz_attestation_get_public_key` (Silicon Labs custom API)



## Getting Started


The Non-secure application needs to work with the Secure application on a workspace (see readme in `tz_psa_attestation_ws`).


## Additional Information


1. The Silicon Labs custom API `sl_tz_attestation_get_public_key()` is used to get the Public Attestation Key.
2. The Series 2 device will generate the PSA attestation token by request unless the SE OTP is uninitialized or the `SECURE_BOOT_ENABLE` option in SE OTP is disabled.
3. The default optimization level is `Optimize for debugging (-Og)` on Simplicity IDE and `None` on IAR Embedded Workbench.


## Resources


[AN1374: Series 2 TrustZone](https://www.silabs.com/documents/public/application-notes/an1374-trustzone.pdf)