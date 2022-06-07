# SoC - Certificate-Based Authentication and Pairing

This example application demonstrates how to create secure connections with trusted devices, where the trust between the devices is based on device certificates instead of some classical authentication method like numeric comparison or passkey entry. This method ensures authenticated connections without any user interaction. A signed device certificate must be present on the devices.

## Getting started

To get started with Silicon Labs Bluetooth and Simplicity Studio, see [QSG169: Bluetooth® Quick-Start Guide for SDK v3.x and Higher](https://www.silabs.com/documents/public/quick-start-guides/qsg169-bluetooth-sdk-v3x-quick-start-guide.pdf).

This example is based on device certificates. To learn about device certificates, refer to [AN1268: Authenticating Silicon Labs Devices Using Device Certificates](https://www.silabs.com/documents/public/application-notes/an1268-efr32-secure-identity.pdf). To generate a device certificate for your device, run the **Bluetooth - SoC CSR Generator** sample app before running this sample app. To learn the usage of the CSR Generator, refer to its readme file.

Certificate-based authentication and pairing means that device A will only make a pairing/bonding with device B if device B can present a valid device certificate signed by a central authority (CA) that device A knows and trusts. Similarly, device B will only accept the pairing from device A if device A can present a valid device certificate signed by a CA that device B knows and trusts. The device certificates are validated using the CA certificate (or root certificate) that is also stored on both devices.

![](readme_img1.png)

After the devices have exchanged and validated each others' certificates, they create an authenticated secure connection using OOB (Out-Of-Band) data, where the OOB data is signed by the devices' private keys and validated with the device certificates. This ensures that the devices not only have the certificates but also have the corresponding private keys, which guarantee the devices' identity.

![](readme_img2.png)

Certificate-based authentication and pairing is useful in situations where multiple devices must create authenticated connections between each other without any user interaction.

## Testing the Example

This example application works only if the elliptic curve (EC) key pair, the device certificate and the root certificate are present on the device. These can be generated using the CSR Generator. Before using this example application, make sure you have properly-signed certificates present on your device. For further information read the readme file of the **Bluetooth SoC - CSR Generator** sample app.

In a pairing example two devices are needed: a central and a peripheral. This example is written so that it can act both as the central and as the peripheral device. In the central role, the device looks for the peripheral, connects to it, initiates certificate-based authentication and pairing, and finally writes a characteristic that can only be written via an authenticated connection. In the peripheral role, the device accepts connections, participates in certificate-based authentication and pairing and finally turns on an LED when its dedicated characteristic is written. The role can be defined in the project configuration.

To test the example:
1. Connect two devices to your PC.
2. Make sure you have run the CSR generator on both devices, so that you have an EC key pair and a signed device certificate on both devices. See the readme of the CSR Generator.
3. The CA certificate must be stored in the application, so you must copy the generated `sl_bt_cbap_root_cert.h` file into this project, under the */config* folder.
4. Build this example and flash it to one of the devices.
5. Open the slcp file of this project.
6. On the Overview tab, under Project Details, open the three-dots-menu, and click **Configuration**.
7. Change the Role from Peripheral to Central.
6. Build the project again and flash it to the other device.
7. Open a terminal program and connect to both devices to see their debug messages.
8. Reset both devices. The central will automatically connect to the peripheral and after some seconds you should see the LED on the peripheral turning on.

## Troubleshooting

Note that Software Example-based projects do not include a bootloader. However, they are configured to expect a bootloader to be present on the device. To get your application to work, either
- flash a bootloader to the device or
- uninstall the **OTA DFU** and **Bootloader Application Interface** software components.

To flash a bootloader, either create a bootloader project or run a precompiled **Demo** on your device from the Launcher view. Precompiled demos flash both bootloader and application images to the device. Then flash your own application image to overwrite the demo application but leave the bootloader in place. 

- To flash an OTA DFU-capable bootloader to the device, flash the **Bluetooth - SoC Thermometer** demo.
- To flash a UART DFU-capable bootloader to the device, flash the **Bluetooth - NCP** demo.
- For other bootloader types, create your own bootloader project and flash it to the device before flashing your application.
- When you flash your application image to the device, use the *.hex* or *.s37* output file. Flashing *.bin* files may overwrite (erase) the bootloader.
- On Series 1 devices (EFR32xG1x), both first stage and second stage bootloaders have to be flashed. This can be done at once by flashing the *-combined.s37* file found in the bootloader project after building the project.
- For more information, see [UG103.6: Bootloader Fundamentals](https://www.silabs.com/documents/public/user-guides/ug103-06-fundamentals-bootloading.pdf) and [UG489: Silicon Labs Gecko Bootloader User's Guide for GSDK 4.0 and Higher](https://cn.silabs.com/documents/public/user-guides/ug489-gecko-bootloader-user-guide-gsdk-4.pdf).

Before programming the radio board mounted on the mainboard, make sure the power supply switch is in the AEM position (right side) as shown below.

![Radio board power supply switch](readme_img0.png)

## Resources

[Bluetooth Documentation](https://docs.silabs.com/bluetooth/latest/)

[UG103.14: Bluetooth LE Fundamentals](https://www.silabs.com/documents/public/user-guides/ug103-14-fundamentals-ble.pdf)

[QSG169: Bluetooth SDK v3.x Quick Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg169-bluetooth-sdk-v3x-quick-start-guide.pdf)

[UG434: Silicon Labs Bluetooth ® C Application Developer's Guide for SDK v3.x](https://www.silabs.com/documents/public/user-guides/ug434-bluetooth-c-soc-dev-guide-sdk-v3x.pdf)

[AN1268: Authenticating Silicon Labs Devices Using Device Certificates](https://www.silabs.com/documents/public/application-notes/an1268-efr32-secure-identity.pdf)

[Bluetooth Training](https://www.silabs.com/support/training/bluetooth)

## Report Bugs & Get Support

You are always encouraged and welcome to report any issues you found to us via [Silicon Labs Community](https://www.silabs.com/community).