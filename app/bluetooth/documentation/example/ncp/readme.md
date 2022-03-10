# NCP

This is a Network  Co-Processor (NCP) target application. It runs the Bluetooth stack and provides access to it by exposing the Bluetooth API (BGAPI) via UART  connection. NCP mode makes it possible to run your application on a host  controller or PC.

This example does not have a GATT database, but makes it  possible to build one from the application using Dynamic GATT API. Use this example together with NCP host example applications.

## Getting Started

To get started with Silicon Labs Bluetooth software and Simplicity Studio, see [QSG169: Bluetooth SDK v3.x Quick Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg169-bluetooth-sdk-v3x-quick-start-guide.pdf).

In the NCP context, the application runs on a host MCU or PC, which is called the NCP Host, while the Bluetooth stack runs on an EFR32, which is called the NCP Target.

The NCP Host and Target communicate via a serial interface (UART), which can be tunneled either via USB or via Ethernet if you use a development kit. The communication between the NCP Host and Target is defined in the Silicon Labs proprietary protocol called BGAPI. BGLib is the C reference implementation of the BGAPI protocol, which is to be used on the NCP Host side.

[AN1259: Using the v3.x Silicon Labs Bluetooth Stack in Network Co-Processor Mode](https://www.silabs.com/documents/public/application-notes/an1259-bt-ncp-mode-sdk-v3x.pdf) provides a detailed description how NCP works and how to configure it for your custom hardware.

The following figures show the system view of NCP mode.

![System View](readme_img1.png)
![System Block Diagram](readme_img2.png)

## Evaluating with Bluetooth NCP Commander

NCP Commander can be used to control the target and test NCP firmware without developing your own host application. In Simplicity Studio, browse to the Launcher -> Compatible Tools tab and open NCP Commander. A shortcut to the Compatible Tools can also be found on the top toolbar. Follow these steps to make the NCP target advertise. See [AN1259: Using the Silicon Labs v3.x Bluetooth Stack in Network Co-Processor Mode](https://www.silabs.com/documents/public/application-notes/an1259-bt-ncp-mode-sdk-v3x.pdf) for additional details. 

1. Connect the board to a PC via USB and start NCP Commander from Simplicity Studio.

![step 1](readme_img3.png)

2. Choose the board from the list and click **Connect**.

![step 2](readme_img4.png)

3. The NCP host will try to get the Bluetooth address from the NCP target. If it succeeds, the connection is established.

4. Click **Create Set** and then **Start** under "Advertise Set (0)" table to start advertising. See the "Smart Console" for details.
    ![step 3](readme_img5.png)
    ![step 3](readme_img7.png)

5. Open the EFR Connect or any Bluetooth browser application to see your device advertising (without any name). You may also connect to the device, although it does not have a GATT database to be discovered by default.

## Extending the GATT database

This example project does not have a GATT database. It only contains the Generic Attributer Service. The GATT database can be built with the APIs provided by the Dynamic GATT Configurator component. See the Bluetooth API reference manual section "GATT Database" for more details.

## Troubleshooting

Note that Software Example-based projects do not include a bootloader. However, they are configured to expect a bootloader to be present on the device. To get your application to work, either
- flash a bootloader to the device or
- uninstall the **Bootloader Application Interface** software component.

To flash a bootloader, either create a bootloader project or run a precompiled **Demo** on your device from the Launcher view. Precompiled demos flash both bootloader and application images to the device. Then flash your own application image to overwrite the demo application but leave the bootloader in place. 

- To flash an OTA DFU-capable bootloader to the device, flash the **Bluetooth - SoC Thermometer** demo.
- To flash a UART DFU-capable bootloader to the device, flash the **Bluetooth - NCP** demo.
- For other bootloader types, create your own bootloader project and flash it to the device before flashing your application.
- When you flash your application image to the device, use the *.hex* or *.s37* output file. Flashing *.bin* files may overwrite (erase) the bootloader.
- On Series 1 devices (EFR32xG1x), both first stage and second stage bootloaders have to be flashed. This can be done at once by flashing the *-combined.s37* file found in the bootloader project after building the project.
- For more information, see [UG103.6: Bootloader Fundamentals](https://www.silabs.com/documents/public/user-guides/ug103-06-fundamentals-bootloading.pdf) and [UG489: Silicon Labs Gecko Bootloader User's Guide for GSDK 4.0 and Higher](https://cn.silabs.com/documents/public/user-guides/ug489-gecko-bootloader-user-guide-gsdk-4.pdf).

Before programming the radio board mounted on the mainboard, make sure the power supply switch the AEM position (right side) as shown below.

![Radio board power supply switch](readme_img0.png)

## Resources

[Bluetooth Documentation](https://docs.silabs.com/bluetooth/latest/)

[UG103.14: Bluetooth LE Fundamentals](https://www.silabs.com/documents/public/user-guides/ug103-14-fundamentals-ble.pdf)

[QSG169: Bluetooth SDK v3.x Quick-Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg169-bluetooth-sdk-v3x-quick-start-guide.pdf)

[AN1259: Using the v3.x Silicon Labs Bluetooth Stack in Network Co-Processor Mode](https://www.silabs.com/documents/public/application-notes/an1259-bt-ncp-mode-sdk-v3x.pdf)

[Bluetooth Training](https://www.silabs.com/support/training/bluetooth)

## Report Bugs & Get Support

You are always encouraged and welcome to report any issues you found to us via [Silicon Labs Community](https://www.silabs.com/community).