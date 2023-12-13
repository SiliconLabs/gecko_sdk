#  mbedTLS ECDSA Example

 This example uses hardware accelerators of the supported devices to perform ECDSA digital signature
 with mbedTLS.

##  Getting Started

1. Upgrade the kit’s firmware to the latest version (see `Adapter Firmware` under [General Device Information](https://docs.silabs.com/simplicity-studio-5-users-guide/latest/ss-5-users-guide-about-the-launcher/welcome-and-device-tabs#general-device-information) in the Simplicity Studio 5 User's Guide).
2. Upgrade the device’s SE firmware to the latest version when Series 2 device is used (see `Secure Firmware` under [General Device Information](https://docs.silabs.com/simplicity-studio-5-users-guide/latest/ss-5-users-guide-about-the-launcher/welcome-and-device-tabs#general-device-information) in the Simplicity Studio 5 User's Guide).
3. Open any terminal program and connect to the kit’s VCOM port (if using `Device Console` in Simplicity Studio 5, `Line terminator:` must be set to `None`).
4. Create this platform example project in the Simplicity IDE (see [Examples](https://docs.silabs.com/simplicity-studio-5-users-guide/latest/ss-5-users-guide-getting-started/start-a-project#examples) in the Simplicity Studio 5 User's Guide).
5. Build the example and download it to the kit (see [Simple Build](https://docs.silabs.com/simplicity-studio-5-users-guide/latest/ss-5-users-guide-building-and-flashing/building#simple-build) and [Flash Programmer](https://docs.silabs.com/simplicity-studio-5-users-guide/latest/ss-5-users-guide-building-and-flashing/flashing#flash-programmer) in the Simplicity Studio 5 User's Guide).
6. When the application starts, three options are presented for the three supported curves
 for the ECDSA algorithm. Press 1 or 2 to select
 which curve to use. If a valid option is chosen, the application will write to serial output when it has
 performed each step in the process. The example application is also programmed to measure the time spent
 in each step of the algorithm.

## Additional Information

 The example uses the CTR-DRBG, a pseudo random number generator (PRNG) included in mbedTLS to generate the
 key pair for the user. If the example is running on a device that includes a TRNG hardware module (True Random
 Number Generator), the TRNG will be used as entropy source to seed the CTR-DRBG. If the device does not incorporate a TRNG, the example will use RAIL as the entropy source. If neither of them is incorporated, dummy data will be seeded to the CTR-DRBG.
 The entropy accumulator of mbedTLS will use SHA256 to hash the entropy data pool which is filled with data from the entropy
 sources.

 The program asks the user to choose between two supported curves. The available
 curves with hardware acceleration support are:

* SECP256R1
* SECP192R1

### Turning off the Hardware Acceleration

 To check the performance gain of the hardware acceleration, switch it off by
 switching the value of **Enable hardware acceleration of crypto operations** in the component *Mbed TLS
 common functionality*. This is found under the tab *SOFTWARE COMPONENTS* → *Platform
 → Security*. 

 **Useful tip:** Filter on *Configurable Components* and *Installed Components* to
 find the configuration file more easily. 

## Troubleshooting

### Serial Port Settings

Be sure to select the following settings to see the serial output of this example:

* 115200 Baud Rate 
* 8-N-1 configuration
* Line terminator should be set to "None" if using Device Console in Simplicity Studio

### Programming the Radio Board

Before programming the radio board mounted on the mainboard, make sure the power supply switch is in the AEM position (right side) as shown below.

![Radio board power supply switch](image/readme_img0.png)

## Report Bugs & Get Support

You are always encouraged and welcome to report any issues you found to us via [Silicon Labs Community](https://community.silabs.com/).