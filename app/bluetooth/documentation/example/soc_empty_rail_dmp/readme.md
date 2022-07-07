# SoC - Empty RAIL DMP

This is a basic implementation of a Bluetooth and proprietary dynamic multiprotocol (DMP) application. It serves as a starting point for any DMP application development.

## Getting Started

To get started with Silicon Labs Bluetooth and Simplicity Studio, see [QSG169: Bluetooth SDK v3.x Quick Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg169-bluetooth-sdk-v3x-quick-start-guide.pdf).

This example implements a basic project with Bluetooth Low Energy and a proprietary protocol running in parallel on the device. The project is based on a Real Time Operating System (Micrium OS or FreeRTOS according to your choice). For more information about using Real Time Operating Systems with Bluetooth, see [AN1260: Integrating v3.x Silicon Labs Bluetooth Applications with Real-Time Operating Systems](https://www.silabs.com/documents/public/application-notes/an1260-integrating-v3x-bluetooth-applications-with-rtos.pdf).

For more details about the Bluetooth and proprietary DMP applications, see [AN1269: Dynamic Multiprotocol Development with Bluetooth and Proprietary Protocols on RAIL in GSDK v3.x](https://www.silabs.com/documents/public/application-notes/an1269-bluetooth-rail-dynamic-multiprotocol-gsdk-v3x.pdf) and [UG305: Dynamic Multiprotocol User’s Guide](https://www.silabs.com/documents/public/user-guides/ug305-dynamic-multiprotocol-users-guide.pdf).

## Project Setup

![](readme_img1.png)

The principle is the same for all Bluetooth DMP (Dynamic Multi-Protocol) applications: the device is able to communicate via Bluetooth and via a secondary protocol (either a standard one, like Zigbee, or a proprietary one) at the same time, making it possible to control the DMP device with different type of devices, or the DMP device can also act as a gateway between the different protocols. The physical layer of the proprietary protocol may be a standard one (like IEEE 802.15.4) or entirely proprietary if your device provides support for it (see datasheet).

This project implements the skeleton of such a solution using Bluetooth and a proprietary protocol with a proprietary physical layer. Callbacks for Bluetooth and proprietary event handling are added, but not implemented (except a very basic Bluetooth functionality that starts advertising after the boot event). The developer can add any functionality.

## Project Structure

The following image shows the overview of the software Architecture of the project.

![](readme_img2.png)

The Bluetooth stack and RAIL are running in the background, using several tasks that should not be modified by the developer. Instead, `sl_bt_on_event()` and `sl_rail_util_on_event()` should be populated with Bluetooth and proprietary event handlers. Note: `sl_rail_util_on_event()` is called from interrupt context, therefore it must implement time-critical event handlers only! Non-time-critical event handling must be implemented in the `app_proprietary_task()`. `sl_bt_on_event()` is not called from interrupt context, therefore it can implement any type of event handlers. To add additional non-event-driven functionality, create new custom tasks.
 
### Bluetooth Configuration

The Bluetooth stack can be configured via the Bluetooth Software Components (see the SOFTWARE COMPONENTS tab in the Project Configurator for the .slcp file).

The project also contains a basic GATT database. GATT definitions can be extended using the GATT Configurator, which can be found under Advanced Configurators in the Software Components tab of the Project Configurator.

![](readme_img3.png)

To learn how to use the GATT Configurator, see [UG438: GATT Configurator User’s Guide for Bluetooth SDK v3.x](https://www.silabs.com/documents/public/user-guides/ug438-gatt-configurator-users-guide-sdk-v3x.pdf).

The Bluetooth task creation and the stack initialization is already implemented in the `sl_system_init()` function, called from the `main` function. The Bluetooth event handler function, `sl_bt_on_event`, can be found in the file *bluetooth_app.c*. This contains a basic event handler, which can be extended according to the applications needs. The default implementation starts advertising with the device name defined in the GATT Configurator. After flashing it to the device, it will be visible in the EFR connect app, as follows:

![](readme_img4.png)

### Proprietary Configuration

RAIL (Radio Abstraction and Integration Layer) can be configured via the RAIL Software Components.

The proprietary protocol also needs a radio configuration. This example applies a default configuration, which works out-of-the-box, based on the radio board you use. The radio configuration can be viewed and altered in the Radio Configurator. The Radio Configurator can be found under Advanced Configurators in the Software Components tab of the Project Configurator, as shown below:

![](readme_img5.png)

To learn how to use the Radio Configurator, see [AN1253: EFR32 Radio Configurator Guide for Simplicity Studio 5](https://www.silabs.com/documents/public/application-notes/an1253-efr32-radio-configurator-guide-for-ssv5.pdf).

`sl_rail_util_on_event()` and `app_proprietary_task()` are implemented in *app_proprietary.c*. Extend these functions to implement your proprietary events handlers.

### Application Tasks

You can implement additional application-specific tasks in *app.c*. You can create and handle any RTOS task here according to your functionality.

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

[AN1260: Integrating v3.x Silicon Labs Bluetooth Applications with Real-Time Operating Systems](https://www.silabs.com/documents/public/application-notes/an1260-integrating-v3x-bluetooth-applications-with-rtos.pdf)

[AN1269: Dynamic Multiprotocol Development with Bluetooth and Proprietary Protocols on RAIL in GSDK v3.x](https://www.silabs.com/documents/public/application-notes/an1269-bluetooth-rail-dynamic-multiprotocol-gsdk-v3x.pdf) 

 [UG305: Dynamic Multiprotocol User’s Guide](https://www.silabs.com/documents/public/user-guides/ug305-dynamic-multiprotocol-users-guide.pdf)

[Bluetooth Training](https://www.silabs.com/support/training/bluetooth)

## Report Bugs & Get Support

You are always encouraged and welcome to report any issues you found to us via [Silicon Labs Community](https://www.silabs.com/community).