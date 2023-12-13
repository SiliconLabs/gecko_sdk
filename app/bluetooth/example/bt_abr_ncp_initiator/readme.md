# NCP - ABR

This is a Network  Co-Processor (NCP) based target application. This serves as the target application of the ABR Initiator role. The Host sample app for it is provided under the folder: ../app/bluetooth/example_host/bt_abr_host_initiator

## Getting Started with NCP

The NCP Host and Target communicate via a serial interface (UART), which can be tunneled either via USB or via Ethernet if you use a development kit. The communication between the NCP Host and Target is defined in the Silicon Labs proprietary protocol called BGAPI. BGLib is the C reference implementation of the BGAPI protocol, which is to be used on the NCP Host side.

[AN1259: Using the v3.x Silicon Labs Bluetooth Stack in Network Co-Processor Mode](https://www.silabs.com/documents/public/application-notes/an1259-bt-ncp-mode-sdk-v3x.pdf) provides a detailed description how NCP works and how to configure it for your custom hardware.

## Usage

Build and flash the application. Use the "bt_abr_host_initiator" Host sample application to connect to it. The Host application will scan for a device running the "Soc - ABR Reflector" sample application. When found, the initiator will create a connection between them and will start the distance measurement process. The initiator calculates the distance, and display them in the command line terminal. It also saves the measured values to a jsonl file next to the executable.

## Troubleshooting

This sample application does need a bootloader. Updating the software is only possible via re-flashing the code.

Before programming the radio board mounted on the mainboard, make sure the power supply switch the AEM position (right side) as shown below.

![](./image/readme_img0.png)

## Resources

[Bluetooth Documentation](https://docs.silabs.com/bluetooth/latest/)

[UG103.14: Bluetooth LE Fundamentals](https://www.silabs.com/documents/public/user-guides/ug103-14-fundamentals-ble.pdf)

[QSG169: Bluetooth SDK v3.x Quick-Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg169-bluetooth-sdk-v3x-quick-start-guide.pdf)

[AN1259: Using the v3.x Silicon Labs Bluetooth Stack in Network Co-Processor Mode](https://www.silabs.com/documents/public/application-notes/an1259-bt-ncp-mode-sdk-v3x.pdf)

[Bluetooth Training](https://www.silabs.com/support/training/bluetooth)

