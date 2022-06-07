# USB Device Mass Storage Device GBL Loader Example

Flash the device with the internal storage bootloader from Gecko bootloader examples to ensure that this example works. 

This example project uses the USB device protocol stack to implement a Mass Storage Device (MSD). Once the kit is connected to a PC via USB, it appears as an MSD with a FAT12-formatted disk. The MSD is used to store a GBL file used for bootloader upgrade. When a valid GBL file is dragged and dropped into the disk, the application waits for the file to be completely transferred. As soon as the transfer is completed, the flash memory allocated for the bootloader storage is reprogrammed with the GBL file. After the bootloader storage is reprogrammed, the bootloader upgrade procedure starts and a software reset is performed.
