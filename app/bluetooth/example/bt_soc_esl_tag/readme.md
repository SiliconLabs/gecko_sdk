
# Bluetooth - SoC ESL Tag

![](image/esltag.png)

This sample application is a reference implementation of the recently released Bluetooth SIG Electronic Shelf Label specification for prototype hardware designed by Silicon Labs.
The example is a showcase of the ESL specification, tested on BRD4182A radio board, but recommended for any BG22 devices. It provides optional, configurable components to customize the project according to your product requirements.

## ESL components
The ESL specification includes both mandatory and optional functionalities. In the reference implementation these are provided as components, as follows:

![](image/components.png)

### ESL Tag Core
The *ESL Tag Core* component implements the mandatory functionality of the specification. This is a key component and hence, a dependency for every other ESL component. Configuration options include advertising minimum and maximum intervals, power saving options, and general settings for the built-in battery level sensor. In general, these settings primarily affect the power consumption of the ESL Tag while it's in *unassociated*, *synchronized* (only the battery related options) or *unsynchronized* states.

![](image/core-config.png)

_Please note that the ESL Core component enables power saving by default after 60 minutes of idle time in Unassociated ESL state. This may impact the deployment of your entire ESL network if the overall deployment process would exceed the deep sleep timeout for individual ESLs.
For this reason, when configuring larger networks, it is recommended that you either choose the parameter carefully or disable the power saving option. Alternatively, batch deployment may be a solution, i.e. power up and deploy only as many ESLs to the network at one time as can be done within the configured timeout._

### Displays
The handling of the displays is split into two layers of abstraction in ESL Tag's design. The higher layer in this concept is represented by the *ESL Tag Display*, while the low-level driver for the actual display in use remains in a separate component. The latter must be written in a way that is interface compatible with the higher layer abstract display component and uses a non-blocking coding approach.
The *Bluetooth - SoC ESL Tag* example project in Simplicity Studio includes a reference driver for the memory LCD on the WSTK developer board, as well as an *ESL Tag User Defined Display Driver* component that only contains skeleton code to facilitate interfacing with a proprietary low level driver.

### ESL Tag Display
The *ESL Tag Display* is an abstract component which implements the functionality defined by the ESL Service specification for display components. The number of display instances can be configured in the configurations view. This component provides APIs for creating display instances and adding them to the available displays list. For details see the API description in the file *esl\_tag\_display.h*. The file *app.c* in the root of the example project demonstrates the display registration process at startup.

### ESL Tag WSTK Display Driver
For testing and development purposes the *ESL Tag WSTK LCD Driver* is provided which uses the built-in LCD display of a WSTK. This component takes care of the display's initialization and control, and it's ready to use straight away.

### ESL Tag User Defined Display Driver
For your project the actual display driver implementation is to be done with the *ESL Tag User Defined Display Driver*. This component defines the necessary callbacks in file *esl\_tag\_user\_display\_driver.c* in the project's root. Within that file you need to implement the following functions:
- *esl\_user\_display\_init()* and the
- *esl\_user\_display\_write()*
in order to make your display work with ESL Tag example.
For details see the API description in the files *esl\_tag\_display.h* and *esl\_tag\_display_core.h*. Furthermore, the skeleton code file *esl\_tag\_user\_display\_driver.c* offers additional suggestions in comments for the proper implementation.

### Image
Two components are provided for storing images. One stores them in RAM, and the other utilizes the NVM. These solutions are mutually exclusive.

#### ESL Tag RAM Image
The *ESL Tag RAM Image* stores all the images in RAM. It gives the quickest and easiest access to the data, but the size of the images is severely constrained by the controller's RAM.
The number of the images (*Image objects*) and the memory size can be configured. The *Image pool size* is the overall allocated size for all the images. In the SoC ESL Tag example project it is configured to have two images with a size of 2048 bytes each. There is no limitation, though, within the boundaries of the pool size. That is, it is allowed to allocate images of different sizes - e.g., in case of multiple displays with different resolutions - within the same image pool.
![](image/ram-config.png)

#### ESL Tag NVM Image
This variant implements the image storage using NVM3 component, occupying space from the internal flash of the target MCU. You can employ this method if the available RAM is insufficient e.g., due to higher resolutions or many images.
It has the following configuration option:
![](image/nvm-config.png)
The number of images can be set in a similar way to the ESL Tag RAM Image component. However, some other settings, which also affect the behavior of the ESL Tag NVM image component, can be controlled via the NVM Default image options as follows.
When receiving images, the fragments will be temporarily buffered in a statically allocated RAM area equal to the size of *NVM3 Default Instance Max Object Size* on the _NVM3 Default Instance Configuration_ page until their size reaches the configured value, at which point they will be stored as an image fragment in the Default NVM3 instance. Following the storage of one image fragment, the same buffer will be re-used to receive subsequent fragments.
![](image/default-nvm3-config.png)
Therefore, the *NVM3 Default Instance Max Object Size* will be the same as one image fragment size, with each NVM3 object having its own unique key. If the entire image does not fit into one of these NVM3 entries, the pieces will be automatically placed under subsequent keys linked together as one complete image. Because storing the fragments have some data overhead, the amount of storage space required for an image depends on the buffer size: the smaller the buffer, the more storage overhead there will be.

### ESL Tag LED
This component implements a full-fledged ESL LED driver for the WSTK board's LEDs. The essential LED control functions, *esl\_led\_on()* and *esl\_led\_off()* have to be adopted by the end user for the actual project hardware - for more information, please check the reference WSTK implementation in *app.c*. The current code base complies entirely with the ESL LED specification, including the brightness control and flashing pattern capabilities. The instance count is adjustable on the configuration page.

### ESL Tag Sensor
This component is a massive showcase of the ESL Sensor feature. The sensor component is logically divided into two groups: the first is a collection of integrated sensors, that may be enabled or disabled at will via the sensor's configuration page:
![](image/sensor-config.png)
The second set of sensors may be user-defined and can either:
- override an existing sensor with the same UUID as an integrated sensor above (no need to disable but for the sake of the code size), or
- add an additional sensor with a standard Mesh Device Property UUID, or
- be a completely custom solution as defined by the ESL Service specification.
Our implementation exposes all of the possibilities through the *esl\_sensor\_custom\_read()* function found in *app.c*.

## Project walkthrough

### Project configuration

The sample project contains the following components:

- ESL Core
- ESL Tag Display, configured to have 1 instance
  - ESL Tag WSTK LCD driver
- ESL Tag RAM Image, configured to have two images with a total size of 4096 bytes
- ESL Tag LED, with 2 LEDs
- ESL Tag Sensor, with 8 different sensors in total:
  - *Present Input Voltage* Mesh Device with UUID 0x0059 as battery voltage level,
  - *Present Operating Temperature* Mesh Device with UUID 0x0054,
  - *Device Firmware Revision* Mesh Device with UUID 0x000E,
  - *Device Date Of Manufacture* Mesh Device with UUID 0x000C,
  - *Device Operating Temperature Range Specification* Mesh Device with UUID 0x0013
  - Silabs Custom Simple Readout Counter with UUID 0x02FFCAFE
  - *Present Ambient Temperature* Mesh Device with UUID 0x004F
  - Silabs Custom Simple Button Sensor with UUID 0x02FFC0DE

### Sample code

The *app.c* contains the reference implementation for image, LED and sensor handling.

#### Adding images

Images can be added with the API *esl\_image\_add()*. As parameters it needs the width, height and how many bits are used to represent a pixel:

```c
sc = esl_image_add(WSTK_DISPLAY_WIDTH, WSTK_DISPLAY_HEIGHT, 1);
```

Note: adding an image means that there will be an allocated index and space for it, it does not add actual image data.

#### Adding displays

A display instance is to be declared first with *esl\_display\_create()*. It needs the width, height and the type of the display.

```C
esl_display_info_p info;
sc = esl_display_create(USER_DISPLAY_WIDTH, USER_DISPLAY_HEIGHT, <type>, &info);
```

After the display is created, it has to be registered in the system with the *esl\_display\_add()* where an init and write function pointer has to be provided. When a display write or refresh command is received from the ESL gateway, the write function will be called by the *ESL Tag Core* component:

```C
sc = esl_display_add(info, esl_wstk_lcd_init, esl_wstk_lcd_write);
```

For the declaration of the needed functions see the API description in the *esl\_tag\_display.h*

#### Adding LEDs

LED instances are created with the *esl\_led\_add()*. It needs a type and the red, blue and green values. For more details about the LED values see the ESL specification.
For a monochrome LED write:
``` c
sc = esl_led_add(ESL_LED_TYPE_MONOCHROME, ESL_LED_LEVEL_3,  ESL_LED_LEVEL_2, ESL_LED_LEVEL_0);
```
or for an sRGB color LED use:
``` c
sc = esl_led_add(ESL_LED_TYPE_SRGB, ESL_LED_LEVEL_3,  ESL_LED_LEVEL_2, ESL_LED_LEVEL_0);
```

The *esl\_led\_on()* and *esl\_led\_off()* functions are also implemented in the app.c, with an additional, simple software PWM implementation for the brightness control.

#### Adding sensors

Sensor instances are added by the *esl\_sensor\_add()* invocation as follows:

``` c
sc = esl_sensor_add(ESL_SENSOR_MESH_DEVICE, PRESENT_AMBIENT_TEMPERATURE);
```
in case of standard sensors with Mesh Sensor Device Property UUID or
``` c
sc = esl_sensor_add(<your_company_bluetooth_uuid>, <custom_sensor_id>);
```
in case of custom ESL sensors.

These newly added sensors then need to be handled by the *esl\_sensor\_custom\_read()* function - for a reference please check the provided examples in *app.c*.

## Advanced use case

### Using application-level over-the-air device firmware update method

By default, the *Bluetooth - SoC ESL Tag* example utilizes the *In-Place OTA DFU* component to provide OTA firmware upgrade capability. Please refer to the [Troubleshooting](#troubleshooting) section for details on which bootloader to use in that case. This OTA method has a drawback that an unsuccessful upgrade attempt may render the device inoperable while it is simpler to use, overall. For more robust operation, though, the so called *Application OTA DFU* component is also provided. However, this component will require a different bootloader type that has to be carefully configured.

You must first remove the *In-Place OTA DFU* component from the project before adding the *Application OTA DFU* and then rebuilding in order to use the new method. After the new firmware has been successfully flashed, the device won't function properly until the bootloader has been also updated appropriately.

To have a proper bootloader for the **Bluetooth - SoC ESL Tag** example with *Application OTA DFU* component on a BG22 MCU based device as an example, you have to create a bootloader project first in Simplicity Studio, then configure it as follows:
- Create a **Bootloader - SoC Internal Storage (single image on 512kB device)** project.
- Go to the *Software Components* page of the newly created project and search for the word "LZMA", then add the **GBL Compression (LZMA)** component. Now remove the search keyword.
- Go to **Common Storage** config page by selecting the *Installed* and *Configurable* checkboxes at the top of the page. Set the *Start address of bootload info* to 0.
  ![](image/common-storage.png)
- Go to **Bootloader Storage Slot Setup** config page and set slot 0 *Start Address* to 352256 and *Slot Size* to 139264. Please note that these values ensure that sufficient space is available for the application during the development phase, but the size of the update image slot is limited so that only a compressed release build image may fit. It is most likely that fine-tuning of these values will become necessary during the development.
  ![](image/slot-setup.png)
- Once you have created and flashed the custom bootloader, you must also flash the application - if it's not done already.

After successfully flashing the new bootloader that supports LZMA compression and the application with the *Application OTA DFU* component, you'll also need a firmware upgrade image in LZMA compressed GBL format. Please refer to Section 7.2.1 of the document [UG266: Silicon Labs Gecko Bootloader User's Guide for GSDK 3.2 and Lower](https://www.silabs.com/documents/public/user-guides/ug266-gecko-bootloader-user-guide.pdf).

As for the OTA upgrading process, please refer to [UG435.06: Bootloading and OTA with Silicon Labs Connect v3.x](https://www.silabs.com/documents/public/user-guides/ug435-06-bootloading-and-ota-with-connect-v3x.pdf).

## Troubleshooting

Note that __NO__ Bootloader is included in any Software Example projects, but they are configured so, that they expect a bootloader to be present on the device. To get your application to work, you should either
- flash a bootloader (*Bootloader - SoC Bluetooth AppLoader OTA DFU* project, in case of the default *In-place OTA DFU* component) to the device or
- uninstall the **In-place OTA DFU** and **Bootloader Application Interface** software components.
- When you flash your application image to the device, use the *.hex* or *.s37* output file. Flashing *.bin* files may overwrite (erase) the bootloader!
- For more information, see *[UG103: Bootloading fundamentals](https://www.silabs.com/documents/public/user-guides/ug103-06-fundamentals-bootloading.pdf)* and *[UG266: Silicon Labs Gecko Bootloader User's Guide](https://www.silabs.com/documents/public/user-guides/ug266-gecko-bootloader-user-guide.pdf)*.

Before programming the radio board mounted on the WSTK, make sure the power supply switch the AEM position (right side) as shown below.

![Radio board power supply switch](image/aem.png)



## Resources

[Bluetooth Documentation](https://docs.silabs.com/bluetooth/latest/)

[UG103.14: Bluetooth® LE Fundamentals](https://www.silabs.com/documents/public/user-guides/ug103-14-fundamentals-ble.pdf)

[QSG169: Bluetooth® SDK v3.x Quick Start Guide](https://www.silabs.com/documents/public/quick-start-guides/qsg169-bluetooth-sdk-v3x-quick-start-guide.pdf)

[UG434: Silicon Labs Bluetooth ® C Application Developer's Guide for SDK v3.x](https://www.silabs.com/documents/public/user-guides/ug434-bluetooth-c-soc-dev-guide-sdk-v3x.pdf)

[Bluetooth Training](https://www.silabs.com/support/training/bluetooth)



## Report Bugs & Get Support

You are always encouraged and welcome to report any issues you found to us via [Silicon Labs Community](https://www.silabs.com/community).
