# NCP - Host

This is a reference implementation of an NCP (Network Co-Processor) host, which is typically run on a central MCU without radio. It can connect to an NCP target via UART to access the Bluetooth stack of the target and to control it using BGAPI.

This  example uses the Dynamic GATT feature, and it must be used together with the **Bluetooth - NCP** target app.

## Getting Started

To get started with Silicon Labs Bluetooth software and Simplicity Studio, see [QSG169: Bluetooth SDK v3.x Quick-Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg169-bluetooth-sdk-v3x-quick-start-guide.pdf).

In the NCP context, the application runs on a host MCU or PC, which is called the **NCP host**, while the Bluetooth stack runs on an EFR32, which is called the **NCP target**. This example application demonstrates an NCP host implementation. Although it is written for an EFR32 device, it can be ported to other MCUs.

The NCP Host and Target communicate via a serial interface (UART), which can be tunneled either via USB or via Ethernet if you use a development kit. The communication between the NCP host and target is defined in the Silicon Labs proprietary protocol called BGAPI. BGLib is the reference implementation of the BGAPI protocol in C, to be used on the NCP Host side.

[AN1259: Using the v3.x Silicon Labs Bluetooth Stack in Network Co-Processor Mode](https://www.silabs.com/documents/public/application-notes/an1259-bt-ncp-mode-sdk-v3x.pdf) provides a detailed description how NCP works and how to configure it for your custom hardware.

The following figure shows the system view of NCP mode:

![System Block Diagram](readme_img1.png)

## Configuring the Host and Target

Use this example application with an NCP target application that is run on another mainboard.

1. Create the NCP target firmware for another mainboard on which you want to run the Bluetooth stack:

    1. Create a new **Bluetooth - NCP** example project.
    2. In the Project Configurator, find the **UARTDRV USART** component.
    3. Add a new instance with the name 'exp'. This will root the UART pins to the EXP header of the mainboard instead of vcom.
    4. Remove the 'vcom' instance.
    5. Find the **Board Control** component.
    6. In its configuration, disable Virtual COM UART.
    7. Build and flash the project to the target mainboard.

2. Build the NCP - Host project and flash it to the mainboard.

3. For UART communication, the TX and RX pins of the host mainboard need to be connected to the RX and TX pins of the target mainboard, respectively. Make sure the following connections are established:

    - *TX* pin (number 12 on the expansion header of the mainboard) of the host is connected to the *RX* pin (number 14 on the expansion header of the mainboard) of the target.

    - *RX* pin (number 14 on the expansion header of the mainboard) of the host is connected to the *TX* pin (number 12 on the expansion header of the mainboard) of the target.

    - *VMCU* pin (number 2 on the expansion header of the mainboard) of the host is connected to the *VMCU* pin (number 2 on the expansion header of the mainboard) of the target.

    - *GND* pin (number 1 on the expansion header of the mainboard) of the host is connected to the *GND* pin (number 1 on the expansion header of the mainboard) of the target.

    ![Connecting the Host and Target mainboards](readme_img2.png)

4. On the host, set the power supply switch into *AEM* position (the kit is powered via USB). On the target, set the power supply switch into *BAT* position. The red rectangles on the previous image show the position of the power supply switches on the host and the target. The VMCU and GND pins are used to power up the NCP target.

5. Power the NCP host via USB. The NCP host will receive the boot event from the NCP target. The host will send an advertiser_start command to the target. As a result, you should see your NCP target device advertising itself as a Silicon Labs Example.

## Extending the Host Code

The Bluetooth event handler in app.c of the NCP host project works the same way as the Bluetooth event handler in app.c of any SoC project. The difference is in the background. The NCP host project sends the command to the target device, while an SoC project executes the command on the SoC device.

## Extending the GATT Database

The Host can build up the GATT Database on the Target in runtime with the APIs provided by the Dynamic GATT Database component.

The Dynamic GATT Database APIs can be used for:

- Adding / Removing services, characteristics and descriptors.
- Modifying service, characteristic and descriptor properties.
- Maintaining a polymorphic GATT, where the database can be updated at any time.

This example demonstrates building a minimal GATT database. This can be extended by adding further services using the dynamic GATT API.

See the Bluetooth API reference manual section "GATT Database" for more details.

## Troubleshooting

Note that Software Example-based projects do not include a bootloader. However, they are configured to expect a bootloader to be present on the device. 

To flash a bootloader, either create a bootloader project or run a precompiled **Demo** on your device from the Launcher view. Precompiled demos flash both bootloader and application images to the device. Then flash your own application image to overwrite the demo application but leave the bootloader in place. 

- To flash an OTA DFU-capable bootloader to the device, flash the **Bluetooth - SoC Thermometer** demo.
- To flash a UART DFU-capable bootloader to the device, flash the **Bluetooth - NCP** demo.
- For other bootloader types, create your own bootloader project and flash it to the device before flashing your application.
- When you flash your application image to the device, use the *.hex* or *.s37* output file. Flashing *.bin* files may overwrite (erase) the bootloader.
- On Series 1 devices (EFR32xG1x), both first stage and second stage bootloaders have to be flashed. This can be done at once by flashing the *-combined.s37* file found in the bootloader project after building the project.
- For more information, see [UG103.6: Bootloader Fundamentals](https://www.silabs.com/documents/public/user-guides/ug103-06-fundamentals-bootloading.pdf) and [UG489: Silicon Labs Gecko Bootloader User's Guide for GSDK 4.0 and Higher](https://cn.silabs.com/documents/public/user-guides/ug489-gecko-bootloader-user-guide-gsdk-4.pdf).

Before programming the radio board mounted on the mainboard, make sure the power supply switch of the NCP host is in the AEM position (right side) as shown below, while the power supply switch of the NCP target board is in the BAT position.

![Radio Board Power Supply Switch](readme_img0.png)

## Resources

[Bluetooth Documentation](https://docs.silabs.com/bluetooth/latest/)

[UG103.14: Bluetooth LE Fundamentals](https://www.silabs.com/documents/public/user-guides/ug103-14-fundamentals-ble.pdf)

[QSG169: Bluetooth SDK v3.x Quick-Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg169-bluetooth-sdk-v3x-quick-start-guide.pdf)

[UG434: Silicon Labs Bluetooth ® C Application Developer's Guide for SDK v3.x](https://www.silabs.com/documents/public/user-guides/ug434-bluetooth-c-soc-dev-guide-sdk-v3x.pdf)

[Bluetooth Training](https://www.silabs.com/support/training/bluetooth)

## Report Bugs & Get Support

You are always encouraged and welcome to report any issues you found to us via [Silicon Labs Community](https://www.silabs.com/community).