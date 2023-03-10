# TrustZone PSA Attestation (Workspace and Secure application)


The Simplicity IDE uses the `tz_psa_attestation_ws` workspace to create the following Secure and Non-secure applications for the TrustZone PSA Attestation example.  


* `tz_psa_attestation_s` (Secure application)
* `tz_psa_attestation_ns` (Non-secure application)

After building all the projects in the workspace, the following post-build actions will be processed.


* Combine the Secure and Non-secure binaries into one image for signing.
* Sign the combined image with the private key (PSA attestation requires the secure boot as the root of trust). The private key (`example_signing_key.pem`) for signing is located in the `autogen` folder of the Secure application.


The Secure application makes a TrustZone secure library for running PSA Crypto and Attestation in the Secure world. The following services are provided to the Non-secure world through the veneers in the Non-secure Callable (NSC).


* `Attestation`
* `MSC`
* `NVM3`
* `PSA Crypto`
* `PSA ITS`
* `SE Manager`
* `SYSCFG`


## Getting Started


1. Upgrade the kit’s firmware to the latest version (see `Adapter Firmware` under [General Device Information](https://docs.silabs.com/simplicity-studio-5-users-guide/latest/ss-5-users-guide-about-the-launcher/welcome-and-device-tabs#general-device-information) in the Simplicity Studio 5 User's Guide).
2. Upgrade the device’s SE firmware to the latest version (see `Secure Firmware` under [General Device Information](https://docs.silabs.com/simplicity-studio-5-users-guide/latest/ss-5-users-guide-about-the-launcher/welcome-and-device-tabs#general-device-information) in the Simplicity Studio 5 User's Guide).
3. Open any terminal program and connect to the kit’s VCOM port (if using `Device Console` in Simplicity Studio 5, `Line terminator:` must be set to `None`).
4. Use the `tz_psa_crypto_ecdh_ws` workspace to create Secure and Non-secure projects in the Simplicity IDE (see [Examples](https://docs.silabs.com/simplicity-studio-5-users-guide/latest/ss-5-users-guide-getting-started/start-a-project#examples) in the Simplicity Studio 5 User's Guide).
5. Build the Secure and Non-secure projects and download the combined images to the kit (refer to [AN1374: Series 2 TrustZone](https://www.silabs.com/documents/public/application-notes/an1374-trustzone.pdf) for details).
6. Run the example and follow the instructions shown on the console.


## Additional Information


1. This example cannot run if the `SECURE_BOOT_ENABLE` option (the root of trust of the attestation) in SE OTP is disabled. The combined image of Secure and Non-secure applications must be signed before flashing to the device.
2. The default optimization level is `Optimize for size (-Os)` on Simplicity IDE and IAR Embedded Workbench.


## Resources


[AN1374: Series 2 TrustZone](https://www.silabs.com/documents/public/application-notes/an1374-trustzone.pdf)


