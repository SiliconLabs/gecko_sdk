# TrustZone PSA Crypto ECDH (Workspace and Secure Application)

The Simplicity IDE uses the `tz_psa_crypto_ecdh_ws` workspace to create the following Secure and Non-secure applications for the TrustZone PSA Crypto ECDH example. The post-build action in the workspace will combine the Secure and Non-secure binaries into one image for flashing.  

* `tz_psa_crypto_ecdh_s` (Secure application)
* `tz_psa_crypto_ecdh_ns` (Non-secure application)

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

1. The default optimization level is `Optimize for size (-Os)` on Simplicity IDE and IAR Embedded Workbench.

## Troubleshooting

### Serial Port Settings

Be sure to select the following settings to see the serial output of this example:

* 115200 Baud Rate 
* 8-N-1 configuration
* Line terminator should be set to "None" if using Device Console in Simplicity Studio

### Programming the Radio Board

Before programming the radio board mounted on the mainboard, make sure the power supply switch is in the AEM position (right side) as shown below.

![Radio board power supply switch](tz_psa_crypto_ecdh_ns/image/readme_img0.png)

## Resources

[AN1374: Series 2 TrustZone](https://www.silabs.com/documents/public/application-notes/an1374-trustzone.pdf)

## Report Bugs & Get Support

You are always encouraged and welcome to report any issues you found to us via [Silicon Labs Community](https://community.silabs.com/).