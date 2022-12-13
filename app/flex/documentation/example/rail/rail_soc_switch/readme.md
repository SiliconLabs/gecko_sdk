# RAIL SoC Switch

This is a bare metal SoC switch reference application demonstrating switching a light bulb via a Proprietary protocol. To switch it via 2.4 GHz radio through RAIL, use the **Flex (RAIL) - Switch** example.

## Getting Started

To get started with Silicon Labs Bluetooth and Simplicity Studio, see [QSG168: Proprietary Flex SDK SDK v3.x Quick Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg168-proprietary-flex-sdk-v3x-quick-start-guide.pdf).

This example implements a sample project using a 2.4 GHz-based radio configuration and a simple channel map to illustrate home automation applications. It sends a simple message to a kit running the **RAIL SoC Light** to switch the WSTK LEDs on and off.

## Project Setup

The sample project implements the functionality of switch for a remote-controlled lightbulb using a simple Proprietary protocol.

First, after plugging in your WSTK mounted with a 2.4 GHz-capable radio board, create and compile a **RAIL SoC Switch** example.

Then load the binary image to your target. The following frame buffer should show up on the WSTK LCD. By default the, switch sample application operates in a mode allowing connections (DMP BLE context) and thus, displays "SCAN" on the LCD bottom left corner.

![](switch/readme_img1.jpg)

The sample application can work in two modes, connected (see **SoC - Light RAIL DMP** example for more details) or simple TX/RX. This example uses only the simple TX/RX mode. To put the sample application in this mode, press button 1 on the WSTK. The LCD now displays "LINK" in the bottom left corner.

![](switch/readme_img2.jpg)

### Controlling the light

When the device running **RAIL SoC Light** is in "Ready" mode, it listens for messages coming from a switch.

Press button 0 on the switch WSTK to transmit a message that will light the LEDs on the kit running the light example. The graphic on the switch's LCD changes to on.

![](switch/readme_img5.jpg)

This should produce the following result on the WSTK running the **RAIL SoC Light** sample application.

![](switch/readme_img4.jpg)

### Proprietary Configuration

RAIL (Radio Abstraction and Integration Layer) can be configured through the RAIL components in the Software Components tab.

The proprietary protocol also needs a radio configuration. This example applies a default configuration, which works out-of-the-box, based on the radio board you use. The radio configuration can be viewed and altered in the Radio Configurator. The Radio Configurator can be found under Advanced Configurators in the Software Components tab of the Project Configurator, as shown below:

![](switch/readme_img5.png)

To learn how to use the Radio Configurator, see [AN1253: EFR32 Radio Configurator Guide for Simplicity Studio 5](https://www.silabs.com/documents/public/application-notes/an1253-efr32-radio-configurator-guide-for-ssv5.pdf).


## Troubleshooting

Note that Software Example-based projects do not include a bootloader. However, they are configured to expect a bootloader to be present on the device. To get your application to work, either

- flash a bootloader to the device or
- uninstall the **OTA DFU** and **Bootloader Application Interface** software components.

To flash a bootloader, either create a bootloader project or run a precompiled **Demo** on your device from the Launcher view. Precompiled demos flash both bootloader and application images to the device. Then flash your own application image to overwrite the demo application but leave the bootloader in place. 

- For other bootloader types, create your own bootloader project and flash it to the device before flashing your application.
- When you flash your application image to the device, use the *.hex* or *.s37* output file. Flashing *.bin* files may overwrite (erase) the bootloader.
- On Series 1 devices (EFR32xG1x), both first stage and second stage bootloaders have to be flashed. This can be done at once by flashing the *-combined.s37* file found in the bootloader project after building the project.
- For more information, see [UG103.6: Bootloader Fundamentals](https://www.silabs.com/documents/public/user-guides/ug103-06-fundamentals-bootloading.pdf) and [UG489: Silicon Labs Gecko Bootloader User's Guide for GSDK 4.0 and Higher](https://cn.silabs.com/documents/public/user-guides/ug489-gecko-bootloader-user-guide-gsdk-4.pdf).

Before programming the radio board mounted on the mainboard, make sure the power supply switch is in the AEM position (right side) as shown below.

![Radio board power supply switch](switch/readme_img0.png)

## Resources

[RAIL Documentation](https://docs.silabs.com/rail/2.13/)

## Report Bugs & Get Support

You are always encouraged and welcome to report any issues you found to us via [Silicon Labs Community](https://www.silabs.com/community).