# Bluetooth Mesh - SoC Empty with Certificate-Based Provisioning Support

  This example demonstrates the bare minimum needed for a Bluetooth Mesh C application that allows Certificate-Based Provisioning (CBP). The application
  starts Unprovisioned Device Beaconing after boot waiting to be provisioned to a Mesh Network. This Software Example can be used as a starting point for
  an SoC project and it can be customized by adding new components from the Component Browser or by modifying the application (app.c). This example
  requires one of the Internal Storage Bootloader (single image) variants depending on device memory.

## Getting Started

To learn Bluetooth mesh technology basics, see [Bluetooth Mesh Networking - An Introduction for Developers](https://www.bluetooth.com/wp-content/uploads/2019/03/Mesh-Technology-Overview.pdf).

To get started with Silicon Labs Bluetooth Mesh and Simplicity Studio, see [QSG176: Bluetooth® Mesh Quick-Start Guide for SDK v2.x and v3.x](https://www.silabs.com/documents/public/quick-start-guides/qsg176-bluetooth-mesh-sdk-v2x-quick-start-guide.pdf).

To learn more about Certificate-Based Provisioning, see [AN1386: Bluetooth Mesh Certificate-Based Provisioning](https://www.silabs.com/documents/public/application-notes/an1386-bluetooth-mesh-certificate-based-provisioning.pdf).

The term SoC stands for "System on Chip". In the SoC model the entire system (stack and application) resides on a single chip, whereas in the NCP model the stack processing is done in a separate coprocessor that interacts with the application’s microcontroller through an external serial interface.

This example is an (almost) empty project that has only the bare minimum with Proxy and Relay features included to make a working Bluetooth Mesh application, configured to use Certificate Based Provisioning.

To add or remove features from the example, follow this process:

- Add model and feature components to your project
- Optionally configure your Mesh node through the "Bluetooth Mesh Configurator". It is configured to have only one element supporting a minimal set of models.

![Bluetooth Mesh Configurator](readme_img1.png)

To learn more about programming an SoC application, see [UG472: Bluetooth® Mesh Stack and Bluetooth® Mesh Configurator User's Guide for SDK v2.x and Higher](https://www.silabs.com/documents/public/user-guides/ug472-bluetooth-mesh-v2x-node-configuration-users-guide.pdf).

- Some components are configurable, and can be customized using the Component Editor

![Bluetooth Mesh Components](readme_img2.png)

- Respond to the events raised by the Bluetooth stack
- Implement additional application logic

[UG295: Silicon Labs Bluetooth® Mesh C Application Developer’s Guide for SDK v2.x and Higher](https://www.silabs.com/documents/public/user-guides/ug295-bluetooth-mesh-dev-guide.pdf) gives code-level information on the stack and the common pitfalls to avoid.

## Responding to Bluetooth Events

Just like in the Bluetooth Low Energy SDK, a Mesh application is event-driven. The Bluetooth Mesh stack generates events when a remote device connects or disconnects, for example, or when it publishes a message. While it is not necessary to react to all events, the ones requiring action should be handled by the application in the `sl_btmesh_on_event()` function. The prototype of this function is implemented in *app.c*. To handle more events, the switch-case statement of this function is to be extended. For the list of Bluetooth Mesh events, see the HTML documentation available in Simplicity Studio:

![Bluetooth Mesh API](readme_img3.png)

## Implementing Application Logic

Additional application logic has to be implemented in the `app_init()` and `app_process_action()` functions. Find the definitions of these functions in *app.c*. The `app_init()` function is called once when the device is booted, and `app_process_action()` is called repeatedly in a while(1) loop. For example, you can poll peripherals in this function.

## Features Already Added to Bluetooth Mesh - SoC Empty with Certificate-Based Provisioning Support Application

The **Bluetooth Mesh - SoC Empty with Certificate-Based Provisioning Support** application is ***almost*** empty. It implements the bare minimum needed for a Bluetooth Mesh C application that incorporates Certificate-Based Provisioning (CBP). The application starts Unprovisioned Device Beaconing after boot waiting to be provisioned to a Mesh Network.

## Testing the Bluetooth Mesh - SoC Empty with Certificate-Based Provisioning Support Application

As described above, an empty example does nothing except broadcast unprovisioned beacons with Certificate-Based Provisioning (CBP) configured. To make this example work, multiple steps are needed utilizing other examples:

1. Please, follow the readme instructions of the **Bluetooth Mesh - SoC CSR Generator (Secure Vault)** project in Simplicity Studio.
2. Create a CA certificate. Skip this step if you already have a root certificate you wish to use. Install the Python modules cryptography and jinja2 as follows:
    - `pip3 install cryptography`
    - `pip3 install jinja2`

    Once these modules have been installed, create the CA certificate with the following command:
    - `python3 {SDK_folder}\app\bluetooth\script\certificate authorities\create_authority_certificate.py`

    The CA certificate can now be found in `{SDK_folder}\app\bluetooth\script\certificate authorities\central_authority\certificate.pem`. 

3. Run the production_line_tool.py python script on your computer with the following parameters:
    - `python3 {SDK_folder}\app\bluetooth\script\certificate authorities\production_line_tool.py --serial <serialnumber>`

4. Build and flash the **Bluetooth Mesh - SoC Empty with Certificate-Based Provisioning Support** example to your device. Do not erase the device beforehand, just overwrite the existing content. The flashing can be done, for example, using the Simplicity Studio internal **Flash Programmer** or external **Simplicity Commander** tools.
5. Download the Silicon Labs **Bluetooth Mesh** smartphone application available on [iOS](https://apps.apple.com/us/app/bluetooth-mesh-by-silicon-labs/id1411352948) and [Android](https://play.google.com/store/apps/details?id=com.siliconlabs.bluetoothmesh). Make sure to reset the local database by pressing the **Reset local database** button in the menu **More**.
6. Open the app, choose the Provision Browser, and tap **Scan**. Now you should find your device advertising. Tap **PROVISION**.

![Bluetooth Mesh App](readme_img5.png)

7. In the dialog for the unprovisioned node, ensure that the **Use Certificate-based Provisioning** option is enabled then tap the **Obtain certificate from device** item as shown below.

![Bluetooth Mesh App](readme_img6.png)

8. Once the device certificate has been sent, the **Device certificate** status changes to `Available` as shown below. 

![Bluetooth Mesh App](readme_img7.png)

9. Tap the **Select certificate** item to browse for the root certificate. The root certificate is generated by the `create_authority_certificate.py` script and has to be available for the App, either through the filesystem or via cloud storage. The root certificate is either required in .pem or .der format, based on the mobile platform. You may have to convert the certificate to the proper format with the `openssl x509 -inform PEM -in certificate.pem -outform DER -out certificate.der` command.

![Bluetooth Mesh App](readme_img8.png)

10. Tap the **Provision/Continue** button on the screen to complete the provisioning process.

![Bluetooth Mesh App](readme_img9.png)

## Troubleshooting

Note that Software Example-based projects do not include a bootloader. However, they are configured to expect a bootloader to be present on the device. To install a bootloader, from the Launcher perspective's EXAMPLE PROJECTS & DEMOS tab either build and flash one of the bootloader examples or run one of the precompiled demos. Precompiled demos flash a bootloader as well as the application image.

- To flash an OTA DFU-capable bootloader to the device, flash the **Bluetooth Mesh - SoC Switch** demo.
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

[UG295: Silicon Labs Bluetooth Mesh C Application Developer's Guide for SDK v2.x](https://www.silabs.com/documents/public/user-guides/ug295-bluetooth-mesh-dev-guide.pdf)

[UG472: Silicon Labs Bluetooth ® C Application Developer's Guide for SDK v3.x](https://www.silabs.com/documents/public/user-guides/ug434-bluetooth-c-soc-dev-guide-sdk-v3x.pdf)

[Bluetooth Training](https://www.silabs.com/support/training/bluetooth)

## Report Bugs & Get Support

You are always encouraged and welcome to report any issues you found to us via [Silicon Labs Community](https://www.silabs.com/community).
