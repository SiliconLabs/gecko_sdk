# SoC - Thermometer Client

This sample application demonstrates the operation of a client device in a multi-slave BLE topology. Silicon Labs Bluetooth stack supports simultaneous connection for up to eight slave devices at one time. This sample application illustrates how to handle simultaneous connection to four thermometer peripheral devices.

## Getting Started

To get started with Bluetooth and Simplicity Studio, see [QSG169: Bluetooth® SDK v3.x Quick Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg169-bluetooth-sdk-v3x-quick-start-guide.pdf).

To get familiar with client and server roles, see [GATT Server and Client Roles](https://docs.silabs.com/bluetooth/latest/general/gatt-protocol/gatt-server-and-client-roles).

To learn more about master and slave roles, see [Master and Slave Roles](https://docs.silabs.com/bluetooth/latest/general/connections/master-and-slave-roles).

To learn more about multi-slave BLE topology, see [Multi-Slave Topology](https://docs.silabs.com/bluetooth/latest/general/connections/multislave-topology).

You may also like to read [Bluetooth Connection Flowcharts](https://docs.silabs.com/bluetooth/latest/general/connections/bluetooth-connection-flowcharts) to understand the BLE connection procedures.


## Evaluating the Application

To evaluate this application, you need one EFR32/BGM device running the `SoC Thermometer Client` sample application, and at least one (but no more than four) peripheral devices running the `SoC Thermometer` application. The following figure shows the topological setup for testing this sample app.

![Network Topology](readme_img1.png)

When the client boots, it starts `Sanning`/`Discovering` advertising devices. It initiates a connection with those devices that contain the `Health Thermometer` service in their advertising packets.

After a connection is established, the client discovers the Health Thermometer service from the remote GATT database. After the service discovery is completed, the client discovers the thermometer characteristics and enables indications sent from a remote GATT server. The main GATT procedures are represented in the following state diagram.

![State diagram for the GATT procedures](readme_img2.png)

After programming the devices, open your terminal emulator and connect to your client device over its serial port. Set baud rate to 115200. Power on the slave thermometer devices and observe the output readings on your terminal.

![Temperature readings from four peripheral devices](readme_img3.png)



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
