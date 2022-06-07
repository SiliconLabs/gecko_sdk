# USB Host Mass Storage Device GBL Loader Example

Flash the device with the internal storage bootloader from Gecko bootloader examples to ensure that this example works.

This example project uses the USB host and the MSD modules in the Drivers directory to implement support for Mass Storage Devices (MSD). Information about the MSD device will be output on the VCOM port. When an MSD device is connected and detected as valid, this application will start looking for a valid GBL file. Once the GBL file is found, the flash memory allocated for the bootloader storage is reprogrammed with the GBL file. Right after the bootloader storage is reprogrammed, the bootloader upgrade procedure starts and a software reset is performed.
