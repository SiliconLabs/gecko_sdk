# SoC - Thunderboard

This example collects and processes sensor data from the Thunderboard Sense 2 or the Thunderboard EFR32BG22 board, and gives immediate graphical feedback through the Thunderboard iOS/Android application.

## Getting Started

To get started with Silicon Labs Bluetooth and Simplicity Studio, see [QSG169: Bluetooth SDK v3.x Quick Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg169-bluetooth-sdk-v3x-quick-start-guide.pdf).

To run this example, you need either a Thunderboard Sense 2 or a Thunderboard EFR32BG22 board, a mobile device, and the Thunderboard mobile application, available for [iOS](https://apps.apple.com/us/app/thunderboard/id1097181650) and [Android](https://play.google.com/store/apps/details?id=com.silabs.thunderboard).

### Project Setup

The available sensors are different based on the board you use. For a list of the available features, see the User's Guide for the respective boards:

[UG415:Thunderboard EFR32BG22 User's guide](https://www.silabs.com/documents/public/user-guides/ug415-sltb010a-user-guide.pdf)

[UG309: Thunderboard Sense 2 User's Guide](https://www.silabs.com/documents/public/user-guides/ug309-sltb004a-user-guide.pdf)

After flashing the demo, the board starts to advertise, and after a 30 seconds timeout it goes into sleep mode. It wakes up when the left button (BTN0) is pressed. The state diagram of the firmware is shown below.

![](readme_img1.png)

You can connect the device by tapping its name in the Thunderboard app. After the connection is established, you will see the dashboard. There, you can select the categories of the different sensor types and the controls to see.

The screenshots are taken with the Thunderboard Sense 2. The same categories apply for the EFR32BG22, but with a reduced set of sensors and LEDs.

By selecting the environment data, you can see the values of the different sensors mounted on the board, as shown below:

![](readme_img2.png)  ![](readme_img3.png)

Within the I/O you can control the LEDs on the board and see the state of the push buttons. Inside the Motion part, you will see a 3D image of the board. Note that the orientation changes when you move the board, as shown below.
![](readme_img4.png) ![](readme_img5.png)

## Project Structure

The project code is the same for both boards. The different sensor configurations are set in the automatically generated *sl_component_catalog.h*. The main application file, *app.c*, configures the project accordingly.

The Bluetooth-related event handling is implemented in the function `sl_bt_on_event`.

The projects contain the needed services in the GATT database. GATT definitions can be extended using the GATT Configurator, which can be found under Advanced Configurators in the Software Components tab of the Project Configurator:

![](readme_img6.png)

To learn how to use the GATT Configurator, see [UG438: GATT Configurator User’s Guide for Bluetooth SDK v3.x](https://www.silabs.com/documents/public/user-guides/ug438-gatt-configurator-users-guide-sdk-v3x.pdf).

The sensors and I/O are also handled in this file by overriding the default weak implementation of the service handling functions.

Additional functionality can be added to the empty app_process_action function.

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