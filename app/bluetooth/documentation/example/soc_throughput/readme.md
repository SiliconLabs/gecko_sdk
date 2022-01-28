# SoC - Throughput

This sample application allows measuring data throughput between EFR32 devices as well as between an EFR32 and a smartphone running the EFR Connect mobile app.



## Getting started

To get started with Bluetooth and Simplicity Studio, please refer to [QSG169: Bluetooth® SDK v3.x Quick Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg169-bluetooth-sdk-v3x-quick-start-guide.pdf).

This example implements a GATT service that can be used to measure application data throughput using acknowledged or unacknowledged transactions, namely indications or notifications.

There are 3 use cases for this throughput measurement setup:

1. EFR32 (SoC) <-> Mobile phone + EFR Connect
2. EFR32 (SoC) <-> EFR32 (SoC)
3. EFR32 (SoC) <-> EFR32 (NCP) + Host (typically PC)


The two last use cases require two Silicon Labs kits, such as [SLWSTK6021A](https://www.silabs.com/development-tools/wireless/efr32xg22-wireless-starter-kit), [SLTB010A](https://www.silabs.com/development-tools/thunderboard/thunderboard-bg22-kit) or [BGM220-EK4314A](https://www.silabs.com/development-tools/wireless/bluetooth/bgm220-explorer-kit).

To test throughput against a mobile phone please install EFR Connect for [Android](https://play.google.com/store/apps/details?id=com.siliconlabs.bledemo&hl=en&gl=US) or [iOS](https://apps.apple.com/us/app/efr-connect/id1030932759). Source code for the mobile app is available on [Github](https://github.com/SiliconLabs?q=efrconnect&type=&language=&sort=).



### EFR32 (SoC) <-> Mobile phone + EFR Connect

For this use case only one kit is required. After flashing the sample app the firmware will boot as a peripheral by default, and the mobile phone acts as a central.

Open EFR Connect, go to the demo view and select the Throughput demo. A pop-up will show all the devices around you which are running the _Bluetooth - SoC Throughput_ firmware. Tap on the device to go into the Throughput demo view.

![Demo view](readme_img1.jpg) ![Pop up](readme_img2.jpg)

Data can be pushed to the mobile phone by pressing PB0 (notifications) or PB1 (indications) on the kit. From the mobile app side data can be pushed to the EFR32 by tapping the Start button at the bottom. The data transfer type (notifications/indications) can be selected at the top of the connection parameters window.

![Throughput demo](readme_img3.jpg)

The animation below showcases the demo running on a BGM220 Explorer Kit (BGM220-EK4314A) with the mobile app running on an Android device.

![Throughput demo animation](readme_img4.gif)



### EFR (SoC) <-> EFR32 (SoC)

For this use case the _Bluetooth - SoC Throughput_ sample app must be flashed on both kits. By default the firmware boots in peripheral mode but it can boot in central mode by keeping PB0 pressed while resetting the device. The role can be read from the first line on the display.

![Kits booted](readme_img5.jpg)

Throughput testing can start as soon as the devices establish a connection and subscribe to indications/notifications on each other's GATT database. The status is indicated on the second line of the display, when both side show "ST: Subscribed" then testing is ready to start.

Notifications can be pushed by pressing PB0 and indications can be pushed by pressing PB1. The data can be pushed from either kit since both have the throughput service on their GATT database and they subscribe to notifications/indications on the remote device's GATT.

Data will be sent for as long as the button is pressed on the device and the status will be "ST: Testing" during that time.

![Kits booted](readme_img6.jpg)

Once the button is released the average throughput will be calculated and shown on the display as well as how many packets were sent. This information is on the two last lines of the display.

![Kits booted](readme_img7.jpg)



### EFR32 (SoC) <-> EFR32 (NCP) + Host (typically PC)

The final use case consists of one kit flashed with _Bluetooth - SoC Throughput_ sample app and a second kit flashed with _Bluetooth - NCP Empty_. The NCP device will be controlled by a dedicated host application which is located in _C:\SiliconLabs\SimplicityStudio\v5\developer\sdks\gecko_sdk_suite\v3.1\app\bluetooth\example_host\throughput_. 

> To learn more about NCP firmware and how to build the host applications please refer to [AN1259: Using the v3.x Silicon Labs Bluetooth® Stack in Network Co-Processor Mode](https://www.silabs.com/documents/public/application-notes/an1259-bt-ncp-mode-sdk-v3x.pdf).

In this setup data can only be sent from the SoC to the NCP device because the NCP firmware does not contain the Throughput service in its GATT server.



## Additional Notes

These next sections describe some more details about the sample app.

### Operation on 1-button boards

The _Bluetooth - SoC Throughput_ also runs on boards which only have 1 user button, such as [SLTB010A](https://www.silabs.com/development-tools/thunderboard/thunderboard-bg22-kit) or [BGM220-EK4314A](https://www.silabs.com/development-tools/wireless/bluetooth/bgm220-explorer-kit). The behavior is determined by the button press duration:
* Short press will switch between sending notifications or indications. The default out of boot is sending notifications.
* Long press will send data.
* To boot into central mode instead of periperal, keep the button pressed while resetting the device.

### CLI (Command Line Interface)

The _Bluetooth - SoC Throughput_ sample app has a CLI which is used to report activity as well as modify parameters in runtime. You can easily access the CLI with a terminal emulator such as Tera Term or from within [Simplicity Studio](https://www.silabs.com/developers/simplicity-studio) by right-click on the debug adapter -> Launch Console -> Serial 1 tab -> type 'help' on the command prompt.

 ![CLI](readme_img8.png)

The available command set allows multiple options such as changing connection parameters, MTU size, TX power, amongst others.

On devices without display the CLI is used for printing a virtual display which mimics the 
physical display on the mainboard.

 ![CLI](readme_img9.png)



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



## Report Bugs & Get Support

You are always encouraged and welcome to report any issues you found to us via [Silicon Labs Community](https://www.silabs.com/community).