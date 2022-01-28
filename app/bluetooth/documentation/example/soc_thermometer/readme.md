# SoC - Thermometer

This example implements the Health Thermometer service. It enables a peer device to connect and receive temperature values via Bluetooth. The reported values are measured by a temperature sensor located on the WSTK.



## Getting Started

To get started with Bluetooth and Simplicity Studio, see [QSG169: Bluetooth® SDK v3.x Quick Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg169-bluetooth-sdk-v3x-quick-start-guide.pdf).

This example implements the predefined [Thermometer Service](https://www.bluetooth.com/xml-viewer/?src=https://www.bluetooth.com/wp-content/uploads/Sitecore-Media-Library/Gatt/Xml/Services/org.bluetooth.service.health_thermometer.xml). To run this example, you will need the following:

- A WSTK with Bluetooth Low Energy compatible [radio board](https://www.silabs.com/wireless/bluetooth).
- An *[iOS](https://itunes.apple.com/us/app/silicon-labs-blue-gecko-wstk/id1030932759?mt=8)* or *[Android](https://play.google.com/store/apps/details?id=com.siliconlabs.bledemo)* smartphone with EFR Connect app installed.

The following image shows the system view of how it works.

![System View](readme_img1.png)

Follow the below steps to get the temperature value on your smartphone.

1. Create the soc-thermometer project based on your hardware, then build and flash the image to your board. Alternatively, you could flash the pre-built demo image.
![step 1](readme_img2.png)
2. Open the *EFR Connect* app on your smartphone and allow the permission request when opened for the first time.
3. Click [Develop] -> [Browser] and you will see a list of nearby devices which are sending Bluetooth advertisement. Find the one named "Thermometer Example" and click the `connect` button on the right side.
![step 3](readme_img3.png)
4. Wait for the connection to establish and GATT database to be loaded, then find the *Health Thermometer* service, and click `More Info`.
![step 4](readme_img4.png)
5. Four characteristics will show up. Find the *Temperature Measurement* and press the `indicate` button. Then, you will see the temperature value getting updated periodically. You should also see the temperature displayed change as you press your the top of the sensor with your finger, as shown below. If your board is not connected to a temperature sensor (e.g. because of limited number of available pins), a generated value will be shown which changes 1 degree Celsius every second.
![step 5](readme_img5.png)
![Finger on sensor](readme_img6.PNG)

Alternatively, you can follow the below steps instead of the above step 3-5 to use the Health Thermometer feature in the app. This will automatically scan and list devices advertising the Health Thermometer service and, upon connection, will automatically enable notifications and display the temperature data.
![Alternative 1](readme_img7.PNG)
![Alternative 2](readme_img8.PNG)



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

When starting your project, set the power supply switch to the AEM position (right side), as shown below.

![Radio board power supply switch](readme_img0.png)



## Resources

[Bluetooth Documentation](https://docs.silabs.com/bluetooth/latest/)

[UG103.14: Bluetooth® LE Fundamentals](https://www.silabs.com/documents/public/user-guides/ug103-14-fundamentals-ble.pdf)

[QSG169: Bluetooth® SDK v3.x Quick Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg169-bluetooth-sdk-v3x-quick-start-guide.pdf)

[UG434: Silicon Labs Bluetooth ® C Application Developer's Guide for SDK v3.x](https://www.silabs.com/documents/public/user-guides/ug434-bluetooth-c-soc-dev-guide-sdk-v3x.pdf)

[Bluetooth Training](https://www.silabs.com/support/training/bluetooth)

[Bluetooth SIG thermometer profile specification](https://www.bluetooth.org/docman/handlers/downloaddoc.ashx?doc_id=238687&_ga=2.28821308.120082263.1538382903-201228904.1529395147)



## Report Bugs & Get Support

You are always encouraged and welcome to report any issues you found to us via [Silicon Labs Community](https://www.silabs.com/community).