# SoC - Thermometer RTOS

This example application demonstrates the integration of a Real Time Operating System (RTOS) into Bluetooth applications. RTOS is added to the **Bluetooth - SoC Thermometer** example.

## Getting Started

To get started with Silicon Labs Bluetooth and Simplicity Studio, see [QSG169: Bluetooth SDK v3.x Quick Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg169-bluetooth-sdk-v3x-quick-start-guide.pdf).

To learn more about how the thermometer example application works, create a **SoC - Thermometer** example project (without RTOS).

## Bluetooth over RTOS

The following image shows the system architecture of an RTOS based Bluetooth application. The Bluetooth stack is run in multiple tasks:
- Link Layer Task signals Bluetooth Host Task when the Bluetooth stack needs an update.
- Bluetooth Host Task updates the Bluetooth stack, issues stack events to Event Handler Task and handles commands from application tasks.
- Event Handler Task handles and dispatches stack events to `sl_bt_on_event()` that needs to be integrated in the application.
![RTOS system architecture](readme_img1.png)

To learn more about RTOS integration into Bluetooth projects, see [AN1260: Integrating v3.x Silicon Labs Bluetooth Applications with Real-Time Operating Systems](https://www.silabs.com/documents/public/application-notes/an1260-integrating-v3x-bluetooth-applications-with-rtos.pdf).

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

Before programming the radio board mounted on the mainboard, make sure the power supply switch the AEM position (right side) as shown below.

![Radio board power supply switch](readme_img0.png)

## Resources

[Bluetooth Documentation](https://docs.silabs.com/bluetooth/latest/)

[UG103.14: Bluetooth LE Fundamentals](https://www.silabs.com/documents/public/user-guides/ug103-14-fundamentals-ble.pdf)

[QSG169: Bluetooth SDK v3.x Quick Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg169-bluetooth-sdk-v3x-quick-start-guide.pdf)

[UG434: Silicon Labs Bluetooth ® C Application Developer's Guide for SDK v3.x](https://www.silabs.com/documents/public/user-guides/ug434-bluetooth-c-soc-dev-guide-sdk-v3x.pdf)

[Bluetooth Training](https://www.silabs.com/support/training/bluetooth)

## Report Bugs & Get Support

You are always encouraged and welcome to report any issues you found to us via [Silicon Labs Community](https://www.silabs.com/community).