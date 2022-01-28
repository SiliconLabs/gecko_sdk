# SoC - iBeacon

An iBeacon device is an implementation that sends non-connectable advertisements in iBeacon format. The iBeacon Service gives Bluetooth accessories a simple and convenient way to send iBeacon to smartphones. This example can be tested together with the EFR Connect mobile app.



## Getting Started

Introduced in iOS 7, iBeacon enables new location awareness possibilities for apps. Leveraging Bluetooth Low Energy (BLE), a device with iBeacon technology can be used to establish a region around an object. This allows an iOS device to determine  when it has entered or left the region, along with an estimation of proximity to a beacon.

For more beacon information, see [Apple iBeacon](https://developer.apple.com/ibeacon/)

To get started with Bluetooth and Simplicity Studio, see [QSG169: Bluetooth® SDK v3.x Quick Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg169-bluetooth-sdk-v3x-quick-start-guide.pdf).

To run this example, you will need:

- Any Bluetooth Low Energy compatible [radio board](https://www.silabs.com/wireless/bluetooth),
- A smartphone with [EFR Connect app](https://www.silabs.com/developers/efr-connect-mobile-app) installed. (Note: On Android, the distance will not be calculated.)

The following picture shows the system view of how it works.

![SoC-iBeacon-Overview](readme_img1.png)

Follow the below steps to set up the project:

1. Create the SoC-iBeacon project based on your hardware, then build and flash the image to your board. Alternatively, you could flash the pre-built demo image.

   ![create-project](readme_img2.png)

2. Open the *EFR Connect* app on your smartphone and allow the permission request the first time it's opened.

3. Click [Develop] -> [Browser]. You will see a list of nearby devices which are sending Bluetooth advertisement. Find the one named "iBeacon" .

   ![create-project](readme_img3.png)

   You can also see the Minor, Major and UUID number, and the EFR app will estimate the distance. (Note: On Android, the distance will not be calculated.)



## Troubleshooting

Note that __NO__ Bootloader is included in any Software Example projects, but they are configured so, that they expect a bootloader to be present on the device. To get your application work, you should either
- flash a bootloader to the device or
- uninstall the **OTA DFU** and **Bootloader Application Interface** software components.

To flash a bootloader, you should either create a bootloader project or run a precompiled **Demo** on your device from the Launcher view. Precompiled Demos flash both bootloader and application images to your device.

- To flash an OTA DFU capable bootloader to your device, *SoC-Thermometer* demo can be flashed before your application to load the bootloader.
- To flash a UART DFU capable bootloader to your device, *NCP-Empty* demo can be flashed before your application to load the bootloader.
- For your custom application, create your own bootloader project and flash it to your device before flashing your application.
- When you flash your application image to the device, use the *.hex* or *.s37* output file. Flashing *.bin* files may overwrite (erase) the bootloader.
- On Series 1 devices (EFR32xG1x), both first stage and second stage bootloaders have to be flashed. This can be done at once by flashing the **-combined.s37* file found in your bootloader project after building the project.
- For more information, see *[UG103: Bootloading fundamentals](https://www.silabs.com/documents/public/user-guides/ug103-06-fundamentals-bootloading.pdf)* and *[UG266: Silicon Labs Gecko Bootloader User's Guide](https://www.silabs.com/documents/public/user-guides/ug266-gecko-bootloader-user-guide.pdf)*.

Before programming the radio board mounted on the WSTK, make sure the power supply switch the AEM position (right side) as shown below.

![Radio board power supply switch](readme_img0.png)



## Resources

[Bluetooth Documentation](https://docs.silabs.com/bluetooth/latest/)

[UG103.14: Bluetooth® LE Fundamentals](https://www.silabs.com/documents/public/user-guides/ug103-14-fundamentals-ble.pdf)

[QSG169: Bluetooth® SDK v3.x Quick Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg169-bluetooth-sdk-v3x-quick-start-guide.pdf)

[UG434: Silicon Labs Bluetooth ® C Application Developer's Guide for SDK v3.x](https://www.silabs.com/documents/public/user-guides/ug434-bluetooth-c-soc-dev-guide-sdk-v3x.pdf)

[Bluetooth Training](https://www.silabs.com/support/training/bluetooth)

[Getting-Started-with-iBeacon](https://developer.apple.com/ibeacon/Getting-Started-with-iBeacon.pdf)


## Report Bugs & Get Support

You are always encouraged and welcome to report any issues you found to us via [Silicon Labs Community](https://www.silabs.com/community).
