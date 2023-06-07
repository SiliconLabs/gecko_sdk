# SoC - ABR Initiator

The Bluetooth SoC-ABR initiator is a project that you can use to test the Accurate Bluetooth Ranging feature. In the provided ABR setup, the reflector measures the phase of the received signal and sends this information back to the initiator.

## Usage
Build and flash the sample application.
After startup it will scan for a device running the "Soc - ABR Reflector" sample application. When found, the initiator will create a connection between them and will start the distance measurement process. The initiator will calculate the distance, display them on the LCD and also send them via UART.

![](./image/abr_lcd.jpg)


## Troubleshooting

This sample application does need a bootloader. Updating the software is only possible via re-flashing the code.

## Resources

[Bluetooth Documentation](https://docs.silabs.com/bluetooth/latest/)

[UG103.14: Bluetooth LE Fundamentals](https://www.silabs.com/documents/public/user-guides/ug103-14-fundamentals-ble.pdf)

[QSG169: Bluetooth SDK v3.x Quick Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg169-bluetooth-sdk-v3x-quick-start-guide.pdf)

[UG434: Silicon Labs Bluetooth ® C Application Developer's Guide for SDK v3.x](https://www.silabs.com/documents/public/user-guides/ug434-bluetooth-c-soc-dev-guide-sdk-v3x.pdf)

[Bluetooth Training](https://www.silabs.com/support/training/bluetooth)

