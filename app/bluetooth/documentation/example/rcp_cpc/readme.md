# RCP CPC

The RCP (Radio Co-Processor) sample application runs the Bluetooth Controller (radio + Link Layer) and implements the controller part of the HCI, as defined in the *Bluetooth Core Specification, Vol 4: Host Controller Interface*. The HCI is a standardized way for Bluetooth host and controller to communicate with each other. Because the interface is standard, the host and controller can be from different vendors. Currently, Silicon Labs Bluetooth Controller supports UART (Universal Asynchronous Receiver-Transmitter) as the HCI transport layer. In this project Silicon Labs’ proprietary CPC (Co-Processor Communication) protocol is used as the transport protocol over UART.



## Getting Started

To get started with Bluetooth and Simplicity Studio, see [QSG169: Bluetooth® SDK v3.x Quick Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg169-bluetooth-sdk-v3x-quick-start-guide.pdf).



## HCI Protocol

HCI layer provides set of commands and events and ACL data packets. The Host sends commands to the controller. The commands are used to start advertising or scanning, establish connection to another Bluetooth device, read status information from the controller, and so on.

Events are sent from the Controller side to the Host. Events are used as a response to commands or to indicate various events in the controller such as scanning reports, connection establishment or closing, and various failures.

Silicon Labs Bluetooth LE Controller runs on EFR32 Radio Co-Processors. External Bluetooth Host stacks communicates with the controller over the HCI, also called RCP mode. See the following figure.

![](readme_img1.png)

For more details, see [AN1328: Enabling a Radio Co-Processor using the Bluetooth HCI Function](https://www.silabs.com/documents/public/application-notes/an1328-enabling-rcp-using-bt-hci.pdf)



## Supported Modes

ACL (Asynchronous Connection Less) data packets deliver user application data between the host and the controller in both directions.

Silicon Labs Bluetooth LE Controller does not support SCO (Synchronous Connection Oriented) and ISOC (Isochronous Channels) modes. Also, the related HCI messages are not supported.

Bluetooth specification defines Low Energy (LE), BR/EDR (classic) and AMP (alternate MAC and PHY) controllers. Note that Silicon Labs only supports the LE controller.



## Communication Interface

This project uses Silicon Labs’ proprietary CPC (Co-Processor Communication) protocol as the transport protocol over UART. This is useful in DMP (Dynamic Multi-protocol) use cases, when the host device communicates with multiple protocol stacks running on the Radio Co-Processor, but it may be also useful if you need a robust and secure transport protocol. See the following figure for an overview:

![](readme_img2.png)

For more information on CPC please refer to [AN1351: Using the Co-Processor Communication Daemon (CPCd)](https://www.silabs.com/documents/public/application-notes/an1351-using-co-processor-communication_daemon.pdf). To learn more about the DMP use case, see [AN1333: Running Zigbee, OpenThread, and Bluetooth Concurrently on a Linux Host with a Multiprotocol RCP](https://www.silabs.com/documents/public/application-notes/an1333-concurrent-protocols-with-802-15-4-rcp.pdf).



##  Troubleshooting

Note that __NO__ Bootloader is included in any Software Example projects, but it is configured in such a way that they expect a bootloader to be on the device. To ensure your application works, either:
- Flash a bootloader to the device or
- Uninstall the **OTA DFU** and **Bootloader Application Interface** software components.

To flash a bootloader, either create a bootloader project or run a precompiled **Demo** on your device from the Launcher view. Precompiled Demos flash both bootloader and application images to your device.

- To flash an OTA DFU capable bootloader to your device, flash the *SoC-Thermometer* demo before your application to load the bootloader.
- To flash a UART DFU capable bootloader to your device, flash the *NCP-Empty* demo before your application to load the bootloader.
- For a custom application, create a custom bootloader project and flash it to your device before flashing your application.
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

You are always encouraged and welcome to report any issues you found via [Silicon Labs Community](https://www.silabs.com/community).