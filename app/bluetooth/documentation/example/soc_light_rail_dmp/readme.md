# SoC - Light RAIL DMP

This is a Dynamic Multiprotocol reference application demonstrating a light bulb that can be switched both via Bluetooth and via a Proprietary protocol. To switch it via Bluetooth, use the EFR Connect smartphone app. To switch it via a Proprietary protocol, use the **Flex (RAIL) - Switch** example.

## Getting Started

To get started with Silicon Labs Bluetooth and Simplicity Studio, see [QSG169: Bluetooth SDK v3.x Quick Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg169-bluetooth-sdk-v3x-quick-start-guide.pdf).

This example implements a sample project with Bluetooth Low Energy and a proprietary protocol running in parallel on the device. The project is based on a Real Time Operating System (Micrium OS or FreeRTOS according to your choice). For more information about using Real Time Operating Systems with Bluetooth, see [AN1260: Integrating v3.x Silicon Labs Bluetooth Applications with Real-Time Operating Systems](https://www.silabs.com/documents/public/application-notes/an1260-integrating-v3x-bluetooth-applications-with-rtos.pdf).

For more details about the Bluetooth and proprietary DMP applications, see [AN1269: Dynamic Multiprotocol Development with Bluetooth and Proprietary Protocols on RAIL in GSDK v3.x](https://www.silabs.com/documents/public/application-notes/an1269-bluetooth-rail-dynamic-multiprotocol-gsdk-v3x.pdf) and [UG305: Dynamic Multiprotocol User’s Guide](https://www.silabs.com/documents/public/user-guides/ug305-dynamic-multiprotocol-users-guide.pdf)

## Project Setup

The sample project implements the functionality of a remote-controlled lightbulb, which can be controlled via Bluetooth and via a Proprietary protocol. After startup, the lightbulb advertises itself on BLE and Proprietary, and, when connected, it can be controlled by both. It will send a notification when the state has been changed, with the MAC address of the device which initiated the change. The project setup consists of two WSTKs and a mobile phone, as follows:

![](readme_img1.png)

### Controlling via Bluetooth

After flashing the Light demo on a board, it will be visible in the EFR Connect app (available on iOS and Android). Open the app on your phone, go to the Demo tab, and tap the Connected Lighting tile. Now you can connect to your device, as follows:
![](readme_img2.png)

Both the app display and the Bluetooth icon on the light’s LCD change, which indicates a connection:

![](readme_img3.png)

Tap the bulb icon on the smartphone app to toggle the light. The app display, the LCD display, and the LEDs all turn on. The app shows Last Event: Light On. Source is the MAC address of the device sending the command, in this case the smartphone:

![](readme_img4.png)

Note that the light demo has two modes, Advertise (ADVERT) and READY. These are for operation by the switch device, as described next. The smartphone app toggles the light regardless of the mode.

### Controlling with the Switch

To use this example, flash the **Flex (RAIL) - Switch** example project (available in the Flex SDK) to another board. To operate the light from the RAIL Switch application, first link the two devices. The RAIL switch starts in SCAN mode to look for lights in the vicinity. The light starts in ADVERTISE mode and broadcasts its address to nearby RAIL Switches, as follows:

![](readme_img5.png)

After a RAIL switch receives a light’s advertisement packet, it displays its short ID in the bottom left corner. If more lights are advertising at the same time, the switch displays the ID of the Light with the strongest signal, as shown in the image below:

![](readme_img6.png)

Press PB1 on the RAIL switch to store the light’s ID and put the device into LINK mode, as shown in the image below:

![](readme_img7.png)

Finally, press PB1 on the Light to place it into READY mode, in which it sends out the status of the light periodically and accepts toggle commands from the linked Switch, as shown in the image below:

![](readme_img8.png)

You should now be able to toggle the light using the linked switch. Note that more than one switch can be linked to a single light, but one switch cannot control more than one light. The app shows the source as the MAC address of the switch, as shown in the image below:

![](readme_img9.png)

Again, a briefly-displayed arrow shows the source of the command on the Light LCD, as follows:

![](readme_img10.png)

If you press the bulb icon on the app, both the light and the switch displays change, as follows:

![](readme_img11.png)

## Project Structure

The following image shows the overview of the software Architecture of the project.

![](readme_img12.png)

The event handling for the different protocols can be found in their respective tasks. `sl_rail_util_on_event()` is used to handle time-critical RAIL events, and it can signal the changes to `proprietary_app_task()`, which handles non-time-critical events and also executes scheduled proprietary radio tasks. `sl_bt_on_event()` is used to handle Bluetooth events, while `demo_app_task()` is responsible for implementing the state machine of the whole application.

### Bluetooth Configuration

The Bluetooth stack can be configured via the Bluetooth Software Components (see the SOFTWARE COMPONENTS tab in the Project Configurator for the .slcp file).

The project also contains the Silabs DMP Light service in the GATT database. GATT definitions can be viewed (and extended) using the GATT Configurator, which can be found under Advanced Configurators in the Software Components tab of the Project Configurator, as shown below:

![](readme_img13.png)

To learn how to use the GATT Configurator, see [UG438: GATT Configurator User’s Guide for Bluetooth SDK v3.x](https://www.silabs.com/documents/public/user-guides/ug438-gatt-configurator-users-guide-sdk-v3x.pdf).

The Bluetooth task creation and the stack initialization is implemented in the `sl_system_init()` function, called from the `main` function. The Bluetooth event handler function, `sl_bt_on_event`, can be found in the file *bluetooth_app.c*. This contains the Bluetooth implementation.

### Proprietary Configuration

RAIL (Radio Abstraction and Integration Layer) can be configured via the RAIL Software Components.

The proprietary protocol also needs a radio configuration. This example applies a default configuration, which works out-of-the-box, based on the radio board you use. The radio configuration can be viewed and altered in the Radio Configurator. The Radio Configurator can be found under Advanced Configurators in the Software Components tab of the Project Configurator, as shown below:

![](readme_img14.png)

To learn how to use the Radio Configurator, see [AN1253: EFR32 Radio Configurator Guide for Simplicity Studio 5](https://www.silabs.com/documents/public/application-notes/an1253-efr32-radio-configurator-guide-for-ssv5.pdf).

The proprietary task and the event handling are implemented in *app_proprietary.c*.

### Application Tasks

The main logic of the demo application is implemented in `demo_app_task()` that can be found in *app_bluetooth.c*. You can implement additional application-specific tasks in *app.c*.

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

[AN1269: Dynamic Multiprotocol Development with Bluetooth and Proprietary Protocols on RAIL in GSDK v3.x](https://www.silabs.com/documents/public/application-notes/an1269-bluetooth-rail-dynamic-multiprotocol-gsdk-v3x.pdf)

[UG305: Dynamic Multiprotocol User’s Guide](https://www.silabs.com/documents/public/user-guides/ug305-dynamic-multiprotocol-users-guide.pdf)

[AN1260: Integrating v3.x Silicon Labs Bluetooth Applications with Real-Time Operating Systems](https://www.silabs.com/documents/public/application-notes/an1260-integrating-v3x-bluetooth-applications-with-rtos.pdf)

[Bluetooth Training](https://www.silabs.com/support/training/bluetooth)

## Report Bugs & Get Support

You are always encouraged and welcome to report any issues you found to us via [Silicon Labs Community](https://www.silabs.com/community).