# NCP - Empty

This is a Network  Co-Processor (NCP) target application. It runs the Bluetooth stack and  provides access to it by exposing the Bluetooth API (BGAPI) via UART  connection. NCP mode makes it possible to run your application on a host  controller or PC.

Unlike the Bluetooth - NCP sample app, this example contains a minimal GATT database. It can be used with Bluetooth NCP Commander, but it cannot be used with host applications that use Dynamic GATT API. Use the Bluetooth - NCP sample app instead, when testing NCP host sample applications, or remove the GATT database initialization part from the host sample application.



## Getting Started

To get started with Silicon Labs Bluetooth software, see [QSG169: Bluetooth® SDK v3.x Quick-Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg169-bluetooth-sdk-v3x-quick-start-guide.pdf).

In the NCP context, the application runs on a host MCU or PC, which is called the NCP Host, while the Bluetooth stack runs on an EFR32, which is called the NCP Target.

The NCP Host and Target communicates via a serial interface (UART). The communication between the NCP Host and Target is defined in the Silicon Labs proprietary protocol called BGAPI. BGLib is the reference implementation of the BGAPI protocol in C, which is to be used on the NCP Host side.

[AN1259: Using the v3.x Silicon Labs Bluetooth® Stack in Network Co-Processor Mode](https://www.silabs.com/documents/public/application-notes/an1259-bt-ncp-mode-sdk-v3x.pdf) provides a detailed description how NCP works and how to configure it for your custom hardware.

The following figures show the system view of NCP mode.

![System View](readme_img1.png)
![System Block Diagram](readme_img2.png)



## Evaluating with NCP Commander

NCP Commander, which allows you to control the target without developing your own host application, is used to test the NCP firmware. In Simplicity Studio, browse to the launcher -> Compatible Tools tab -> open up NCP Commander. A shortcut to the Compatible Tools can also be found on the top toolbar. Follow the below steps to make the NCP target advertise.

1. Connect your board to a PC via USB and start NCP Commander from Simplicity Studio.
![step 1](readme_img3.png)
2. Choose your board from the list. Then, click "Connect".
![step 2](readme_img4.png)
3. The NCP host will try to get the Bluetooth address from the NCP target. If it succeeds, the connection is established.
4. Click on "Create Set" and then on "Start" button under "Advertise Set (0)" table to start advertising. See the "Smart Console" for details.
    ![step 3](readme_img5.png)
    ![step 3](readme_img7.png)

5. Open the EFR Connect or any Bluetooth browser application to see your device advertising as "Silabs Example". You may also connect to the device and discover its GATT database.



## Extending the GATT database

The NCP-empty application implements a basic GATT database. GATT definitions can be extended using the GATT Configurator, which can be found under Advanced Configurators in the Software Components tab of the Project Configurator. To open the Project Configurator, open the .slcp file of the project.

![Opening GATT Configurator](readme_img6.png)

To learn how to use the GATT Configurator, see [UG438: GATT Configurator User’s Guide for Bluetooth® SDK v3.x](https://www.silabs.com/documents/public/user-guides/ug438-gatt-configurator-users-guide-sdk-v3x.pdf).

The other NCP target example project "Bluetooth - NCP" does not have a GATT database. It uses APIs to build up the database at runtime, which is preferred for NCP projects. With the Dynamic GATT Database solution, the target application does not need to be changed and synchronized with the Host part when the GATT Database is modified. If you still insist to use the GATT configurator, please remove the GATT database initialization from the host sample application.



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

[QSG169: Bluetooth® SDK v3.x Quick-Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg169-bluetooth-sdk-v3x-quick-start-guide.pdf)

[AN1259: Using the v3.x Silicon Labs Bluetooth® Stack in Network Co-Processor Mode](https://www.silabs.com/documents/public/application-notes/an1259-bt-ncp-mode-sdk-v3x.pdf)

[Bluetooth Training](https://www.silabs.com/support/training/bluetooth)



## Report Bugs & Get Support

You are always encouraged and welcome to report any issues you found to us via [Silicon Labs Community](https://www.silabs.com/community).