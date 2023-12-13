# Bluetooth Mesh - NLC Dimming Control

The **Bluetooth Mesh - NLC Dimming Control** example is a working example application that you can use as a Dimming Control node in a Networked Lighting Control (NLC) network.

The example is an out-of-the-box Software Demo optimized for user experience where the device acts as a Dimming Control in an NLC network. Button presses on the mainboard or CLI commands can dim a remote device implementing the Basic Lightness Controller NLC profile (e.g. **Bluetooth Mesh - NLC Basic Lightness Controller**). The example also acts as a Low Power Node and tries to establish friendship. The example implements the Bluetooth Mesh Dimming Control NLC profile and is based on the Generic Level Client Model. This example requires one of the Internal Storage Bootloader (single image) variants, depending on device memory.

There are 2 variants of the NLC Dimming Control example. In typical cases, where power consumption is not the most important factor, we recommend using the **Bluetooth Mesh - NLC Dimming Control** example, as it is easier to get feedback about the current state and operations. If you want to have optimized power consumption, use the **Bluetooth Mesh - NLC Dimming Control Low Power** example, which also reduces power by disabling LCD, CLI and logging.

The example requires a friend node to function properly.

> **Warning**
> If the WSTK has a display, it is not going to be functional in case of xG22 SoCs, due to memory constraints.

![Bluetooth Mesh Networked Lighting Control - Dimming Control](readme_img7.png)

## Getting Started

To learn Bluetooth mesh technology basics, see [Bluetooth Mesh Network - An Introduction for Developers](https://www.bluetooth.com/wp-content/uploads/2019/03/Mesh-Technology-Overview.pdf).

To get started with Bluetooth Mesh and Simplicity Studio, see [QSG176: Bluetooth Mesh SDK v2.x Quick Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg176-bluetooth-mesh-sdk-v2x-quick-start-guide.pdf).

The term SoC stands for "System on Chip", meaning that this is a standalone application that runs on the EFR32/BGM and does not require any external MCU or other active components to operate.

This is an example of a Low Power Node-enabled Bluetooth Mesh application providing the functionality of the Dimming Control NLC profile. Once the node is provisioned and a Basic Lightness Controller subscribes to the client, the two buttons of the mainboard are used to publish the messages that will change the state of the Basic Lightness Controller node.

Buttons can control the following models:

- **Generic OnOff Client** model can turn the light on and off or toggle
- **Generic Level Client** model can control the light brightness

A friendship with a friend node has to be established for the dimming control node to start the sleep/poll cycles.

To add or remove features from the example, follow this process:

- Add model and feature components to your project
- Optionally configure the Mesh node through the "Bluetooth Mesh Configurator"

![Bluetooth Mesh Configurator](readme_img1.png)

To learn more about programming an SoC application, see [UG472: Silicon Labs Bluetooth ® Mesh Configurator User's guide for SDK v2.x](https://www.silabs.com/documents/public/user-guides/ug472-bluetooth-mesh-v2x-node-configuration-users-guide.pdf).

- Some components are configurable, and can be customized using the Component Editor

![Bluetooth Mesh Components](readme_img8.png)

- Respond to the events raised by the Bluetooth stack
- Implement additional application logic

[UG295: Silicon Labs Bluetooth ® Mesh C Application Developer's Guide for SDK v2.x](https://www.silabs.com/documents/public/user-guides/ug295-bluetooth-mesh-dev-guide.pdf) gives code-level information on the stack and the common pitfalls to avoid.

## Device Firmware Update

Device Firmware Update (DFU) is a new feature introduced in the Bluetooth Mesh Model specification v1.1 that provides a standard way to update device firmware over a Bluetooth mesh network. The example has the Target node functionality enabled by default that is fulfilled by installing the Firmware Update and BLOB Transfer model components:

- Firmware Update Server
- BLOB Transfer Server

![Bluetooth Mesh Firmware Update Components](readme_img9.png)

![Bluetooth Mesh Transfer Components](readme_img10.png)

For more information on the DFU examples, see **AN1370: Bluetooth® Mesh Device Firmware Update Example Walkthrough**. To learn the basics of the Bluetooth Mesh Device Firmware Update specification, see **AN1319: Bluetooth® Mesh Device Firmware Update**.

## Testing the Bluetooth Mesh - NLC Dimming Control Application

To test the application, do the following:

1. Make sure a bootloader is installed. See the Troubleshooting section.
2. Build and flash the **Bluetooth Mesh - NLC Dimming Control** example to the device.
3. Reset the device by pressing and releasing the reset button on the mainboard while pressing BTN0. The message "Factory reset" should appear on the LCD.
4. Provision the device in one of three ways:

   - NCP Host provisioner examples, see for example an SDK folder `app/btmesh/example_host/btmesh_host_provisioner` or [github](https://github.com/SiliconLabs/bluetooth_mesh_stack_features/tree/master/provisioning)

   - NCP Commander with NCP target device, see [Bluetooth NCP Commander guide](https://docs.silabs.com/simplicity-studio-5-users-guide/latest/ss-5-users-guide-tools-bluetooth-ncp-commander) or [AN1259: Using the v3.x Silicon Labs Bluetooth Stack in Network Co-Processor Mode](https://www.silabs.com/documents/public/application-notes/an1259-bt-ncp-mode-sdk-v3x.pdf)

   - For Mobile Phone use, see the [QSG176: Bluetooth Mesh SDK v2.x Quick-Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg176-bluetooth-mesh-sdk-v2x-quick-start-guide.pdf) for more information how to download and use the Silicon Labs Bluetooth Mesh application.

   Mobile Phone provisioning is recommended for NLC examples. The mobile application provides a simple network for NLC devices. Provisioning is illustrated in the following figures.

![Bluetooth Mesh start screen](readme_img6.png)

5. Open the app, choose the NLC tab and tap **Scan**.

![Bluetooth Mesh Provision Browser](readme_img2.png)

6. Tap **PROVISION** and continue provisioning.

![Bluetooth Mesh Provisioning Device](readme_img3.png)

7. The device is then automatically provisioned and configured.

8. The next step is to add another one or several NLC devices into your network, including an NLC Basic Lightness Controller, if it has not already been done. This is required to fully test the whole system, for example the friendship and other features. You can then control the **Bluetooth Mesh - NLC Basic Lightness Controller** example by pressing the buttons on the device. Read the applicable example project documentation to learn more.

For more information on the example, see [AN1299: Understanding the Silicon Labs Bluetooth Mesh SDK v2.x Lighting Demonstration](https://www.silabs.com/documents/public/application-notes/an1299-understanding-bluetooth-mesh-lighting-demo-sdk-2x.pdf).

The button presses in this example:

- Short press (less than 0.25s) controls the Lightness (**Generic Level Client** delta messages)
- Longer press changes light on/off (**Generic OnOff Client** messages)

## Troubleshooting

Note that Software Example-based projects do not include a bootloader. However, they are configured to expect a bootloader to be present on the device. To install a bootloader, from the Launcher perspective's EXAMPLE PROJECTS & DEMOS tab either build and flash one of the bootloader examples or run one of the precompiled demos. Precompiled demos flash a bootloader as well as the application image.

- To flash an OTA DFU-capable bootloader to the device, flash the **Bluetooth Mesh - SoC Switch CTL** demo.
- To flash a UART DFU-capable bootloader to the device, flash the **Bluetooth Mesh - NCP Empty** demo.
- For other bootloader types, create your own bootloader project and flash it to the device before flashing your application.
- When you flash your application image to the device, use the *.hex* or *.s37* output file. Flashing *.bin* files may overwrite (erase) the bootloader.
- On Series 1 devices (EFR32xG1x), both first stage and second stage bootloaders have to be flashed. This can be done at once by flashing the *-combined.s37* file found in the bootloader project after building the project.
- For more information, see [UG103.6: Bootloader Fundamentals](https://www.silabs.com/documents/public/user-guides/ug103-06-fundamentals-bootloading.pdf) and [UG489: Silicon Labs Gecko Bootloader User's Guide for GSDK 4.0 and Higher](https://cn.silabs.com/documents/public/user-guides/ug489-gecko-bootloader-user-guide-gsdk-4.pdf).

Before programming the radio board mounted on the mainboard, make sure the power supply switch the AEM position (right side) as shown below.

![Radio board power supply switch](readme_img0.png)

## Resources

[Bluetooth Documentation](https://docs.silabs.com/bluetooth/latest/)

[Bluetooth Mesh Network - An Introduction for Developers](https://www.bluetooth.com/wp-content/uploads/2019/03/Mesh-Technology-Overview.pdf)

[QSG176: Bluetooth Mesh SDK v2.x Quick Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg176-bluetooth-mesh-sdk-v2x-quick-start-guide.pdf)

[AN1315: Bluetooth Mesh Device Power Consumption Measurements](https://www.silabs.com/documents/public/application-notes/an1315-bluetooth-mesh-power-consumption-measurements.pdf)

[AN1316: Bluetooth Mesh Parameter Tuning for Network Optimization](https://www.silabs.com/documents/public/application-notes/an1316-bluetooth-mesh-network-optimization.pdf)

[AN1317: Using Network Analyzer with Bluetooth Low Energy ® and Mesh](https://www.silabs.com/documents/public/application-notes/an1317-network-analyzer-with-bluetooth-mesh-le.pdf)

[AN1318: IV Update in a Bluetooth Mesh Network](https://www.silabs.com/documents/public/application-notes/an1318-bluetooth-mesh-iv-update.pdf)

[AN1299: Understanding the Silicon Labs Bluetooth Mesh SDK v2.x Lighting Demonstration](https://www.silabs.com/documents/public/application-notes/an1299-understanding-bluetooth-mesh-lighting-demo-sdk-2x.pdf)

[UG295: Silicon Labs Bluetooth Mesh C Application Developer's Guide for SDK v2.x](https://www.silabs.com/documents/public/user-guides/ug295-bluetooth-mesh-dev-guide.pdf)

[UG472: Silicon Labs Bluetooth ® C Application Developer's Guide for SDK v3.x](https://www.silabs.com/documents/public/user-guides/ug434-bluetooth-c-soc-dev-guide-sdk-v3x.pdf)

[Bluetooth Training](https://www.silabs.com/support/training/bluetooth)

## Report Bugs & Get Support

You are always encouraged and welcome to report any issues you found to us via [Silicon Labs Community](https://www.silabs.com/community).
