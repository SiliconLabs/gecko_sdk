# NCP - Host

This sample application is a reference implementation of an NCP (Network Co-Processor) host, which is typically run on a central MCU without radio. It can connect to an NCP target via UART to access the Bluetooth stack of the target and to control it using BGAPI.

This  example uses the Dynamic GATT feature, and it must be used together with the **Bluetooth - NCP** target app.



## Getting Started

To get started with Bluetooth and Simplicity Studio, see [QSG169: Bluetooth® SDK v3.x Quick-Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg169-bluetooth-sdk-v3x-quick-start-guide.pdf).

In the NCP context, the application runs on a host MCU or PC, the **NCP host**, while the Bluetooth stack runs on an EFR32, the **NCP target**. This sample application demonstrates an NCP host implementation. Although it is written for an EFR32 device, it can be ported to other MCUs.

The NCP host and target communicate via a serial interface (UART). The communication between the NCP host and target is defined in the Silicon Labs proprietary protocol called BGAPI. BGLib is the reference implementation of the BGAPI protocol in C, to be used on the NCP Host side.

[AN1259: Using the v3.x Silicon Labs Bluetooth® Stack in Network Co-Processor Mode](https://www.silabs.com/documents/public/application-notes/an1259-bt-ncp-mode-sdk-v3x.pdf) provides a detailed description how NCP works and how to configure it for your custom hardware.

The following figure shows the system view of NCP mode:

![System Block Diagram](readme_img1.png)



## Setting Up

Use this sample application with an NCP target application that is run on another WSTK.

1. Build the NCP - Host project and flash it to the WSTK.

2. Create the NCP target firmware for another WSTK on which you want to run the Bluetooth stack

    1. Create a new Bluetooth - NCP example project
    2. In the project configurator find the UARTDRV USART software component
    3. Add a new instance with the name 'exp'. This will root the UART pins to the EXP header of the WSTK instead of vcom
    4. Remove the 'vcom' instance
    5. Find the Board Control software component
    6. In the configuration of the Board Control software component disable Virtual COM UART
    7. Build and flash the project to the target WSTK

3. For UART communication, the TX and RX pins of the host WSTK need to be connected to the RX and TX pins of the target WSTK, respectively. Make sure the following connections are established:

    - *TX* pin (number 12 on the expansion header of the WSTK) of the host is connected to the *RX* pin (number 14 on the expansion header of the WSTK) of the target.

    - *RX* pin (number 14 on the expansion header of the WSTK) of the host is connected to the *TX* pin (number 12 on the expansion header of the WSTK) of the target.

    - *VMCU* pin (number 2 on the expansion header of the WSTK) of the host is connected to the *VMCU* pin (number 2 on the expansion header of the WSTK) of the target.

    - *GND* pin (number 1 on the expansion header of the WSTK) of the host is connected to the *GND* pin (number 1 on the expansion header of the WSTK) of the target.

    ![Connecting the Host and Target WSTKs](readme_img2.png)


4. On the host, set the power supply switch into *AEM* position (the kit is powered via USB). On the target, set the power supply switch into *BAT* position. The red rectangles on the previous image show the position of the power supply switches on the host and the target. The VMCU and GND pins are used to power up the NCP target.

5. Power your NCP host via USB. Your NCP host will receive the boot event from the NCP target. The host will send an advertiser_start command to the target. As a result, you should see your NCP target device advertising itself as a Silicon Labs Example.



## Extending the Host Code

The Bluetooth event handler in app.c of the NCP host project works the same way as the Bluetooth event handler in app.c of any SoC project. The difference is in the background whereby the NCP host project sends the command to the target device, while SoC projects execute the command on the SoC device.



## Extending the GATT Database

The Host can build up the GATT Database on the Target in runtime with the APIs provided by the Dynamic GATT Database component.

The Dynamic GATT Database APIs can be used for :

- Adding / Removing services, characteristics and descriptors
- Modifying service, characteristic and descriptor properties
- Maintaining a polymorphic GATT, the database can be updated in any time

This example demonstrates the building of a minimal GATT database. This can be extended by adding further services using the dynamic GATT API.

See the Bluetooth API reference manual section "GATT Database" for more details.



## Troubleshooting

Note that __NO__ Bootloader is included in any Software Example project. However, when a precompiled demo is flashed, both bootloader and application images are loaded onto the device.

- To flash an example which doesn't have a corresponding prebuilt demo, *SoC-Empty* demo can be flashed before your application to load the bootloader.
- For your custom application, create your own bootloader project and flash it to your device before flashing your application.
- When you flash your application image to the device, use the *.hex* or *.s37* output file. Flashing *.bin* files may overwrite (erase) the bootloader.
- On Series 1 devices (EFR32xG1x), both first stage and second stage bootloaders have to be flashed. This can be done at once by flashing the **-combined.s37* file found in your bootloader project after building the project.
- For more information, see *[UG103: Bootloading fundamentals](https://www.silabs.com/documents/public/user-guides/ug103-06-fundamentals-bootloading.pdf)* and *[UG266: Silicon Labs Gecko Bootloader User's Guide](https://www.silabs.com/documents/public/user-guides/ug266-gecko-bootloader-user-guide.pdf)*.

Before programming the radio board mounted on the WSTK, make sure the power supply switch the AEM position (right side) as shown below.s

![Radio Board Power Supply Switch](readme_img0.png)



## Resources

[Bluetooth Documentation](https://docs.silabs.com/bluetooth/latest/)

[UG103.14: Bluetooth® LE Fundamentals](https://www.silabs.com/documents/public/user-guides/ug103-14-fundamentals-ble.pdf)

[QSG169: Bluetooth® SDK v3.x Quick-Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg169-bluetooth-sdk-v3x-quick-start-guide.pdf)

[UG434: Silicon Labs Bluetooth ® C Application Developer's Guide for SDK v3.x](https://www.silabs.com/documents/public/user-guides/ug434-bluetooth-c-soc-dev-guide-sdk-v3x.pdf)

[Bluetooth Training](https://www.silabs.com/support/training/bluetooth)



## Report Bugs & Get Support

You are always encouraged and welcome to report any issues you found to us via [Silicon Labs Community](https://www.silabs.com/community).