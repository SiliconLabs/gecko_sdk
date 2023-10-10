# ESL Access Point
----
This Python example implements the functionality of an Access Point as specified by the Bluetooth Electronic Shelf Label Profile specification using an NCP ESL AP target. The following features are offered by this example application:

- Finding advertising ESL Tags
- Connecting and configuring Tags either automatically or with full manual control
- Transfer images to Tags via Object Transfer Service (OTS)
- Sending commands to Tags either via Periodic Advertisements with Responses or to the ESL Control Point

Table of content:
- [ESL Access Point](#esl-access-point)
  - [Features](#features)
  - [Limitations, known issues](#limitations-known-issues)
  - [Project structure](#project-structure)
  - [Getting started](#getting-started)
    - [Pre-steps before building](#pre-steps-before-building)
    - [Building the shared libraries](#building-the-shared-libraries)
    - [Pre-steps before building](#pre-steps-before-building-1)
    - [Building the shared libraries](#building-the-shared-libraries-1)
    - [Starting AP application](#starting-ap-application)
  - [Runtime commands](#runtime-commands)
    - [ESL Tag commands](#esl-tag-commands)
      - [ping](#ping)
      - [config](#config)
      - [connect](#connect)
      - [delete\_timed](#delete_timed)
      - [disconnect](#disconnect)
      - [display\_image](#display_image)
      - [image\_update](#image_update)
      - [led](#led)
      - [refresh\_display](#refresh_display)
      - [update\_complete](#update_complete)
      - [unassociate](#unassociate)
      - [factory\_reset](#factory_reset)
      - [service\_reset](#service_reset)
      - [read\_sensor](#read_sensor)
      - [vendor\_opcode](#vendor_opcode)
    - [Access Point control commands](#access-point-control-commands)
      - [help](#help)
      - [mode](#mode)
      - [set\_rssi\_threshold](#set_rssi_threshold)
      - [scan](#scan)
      - [list](#list)
      - [sync](#sync)
      - [demo](#demo)
      - [script](#script)
      - [verbosity](#verbosity)
      - [exit](#exit)

## Features
- Full support of ESL Profile and Service specification v1.0
- Built-in auto conversion for Silabs ESL example devices with image storage and display for any size. 
- Multiple connections in parallel up to the limits of the Bluetooth stack on the attached ESL Network Co-Processor embedded target.
- Encrypted communication between the AP script and the embedded target, which can be optionally disabled or completely removed. For more information on building prerequisites of the secure components for the NCP, see chapter 4.2 of the SiLabs application note [AN-1259](https://www.silabs.com/documents/public/application-notes/an1259-bt-ncp-mode-sdk-v3x.pdf).
- Simple chaining in CLI using `;` (semicolon) as separator between consequtive commands
- Simple [scripting](#script) capability

## Limitations, known issues
---
- In some cases, especially when there are many BLE devices advertising nearby while the AP is scanning for longer periods, the AP script may become unresponsive. In such a case, it may help to limit the period of scanning or to reduce the number of nearby advertising devices. If neither of these are possible, you may want to increase the throughput of the NCP VCOM according to [this article](https://community.silabs.com/s/article/wstk-virtual-com-port-baudrate-setting?language=en_US). After changing the WSTK VCOM speed as described, do not forget to update the VCOM Baud rate configuration of the ESL AP NCP example also accordingly, then re-build and re-flash the target with the new firmware.
- On Windows, there is also a known issue when running the AP where the debugging trace and command line input can interfere with each other on some terminals if python pyreadline3 is installed, so it is strongly recommended to uninstall it using the command `pip uninstall pyreadline3` before running the AP. To find out if it is installed or not, the command `pip freeze` can be used.
- MSYS2 MinGW bash is not recommended for use with ESL Access Point Python example application due to various compatibility issues between the native Windows Python environment and that of MSYS2.
 
## Project structure
---
The Access Point Python application consists of the following files:

- ap\_cli.py
- ap\_config.py
- ap\_constants.py
- ap\_core.py
- ap\_ead.py
- ap\_logger.py
- ap\_response\_parser.py
- ap\_sensor.py
- app.py
- esl\_command.py
- esl\_key\_lib.py
- esl\_lib.py
- esl\_tag.py
- image\_converter.py

You can see the logical structure on the following diagram:

![](images/struct.png)

The application has three operation mode: automated and a (semi-) manual mode. The third one is the demo mode, which is the same as the manual mode with an extra functionality:
it starts advertising the ESL AP GATT Service with two characteristic. The advertising stops if a remote device (e.g mobile phone) established a connection with the AP as peripheral.
If the connection is closed the ESL AP will start the advertising again.

In general, in any mode one can control the application via CLI - but it is encouraged to change to manual mode via the [`mode`](#mode) command before typing in any ESL control commands. For details of the possible commands, see the help of the ap\_cli.py file. (Type: [`help`](#help) command in the CLI)

In automated mode the script executes the following functionality:

![](images/auto-mode.png)

You can see the details of the functionality for each mode in the *<mode>\_esl\_event* function. (e.g *cli\_esl\_event\_system\_boot*)

_Note: Shall any unsolicited error occur during the automated process, the automated cycle above may become interrupted. In most of such cases you can still use the CLI to enter commands, thus it is possible to recover the auto mode._

## Getting started
---
The NCP Host side application requires Python 3. Run `pip install -r requirements.txt` to install all other requirements for the application. Make sure to run this command before running `make`.

On the target side an EFR device is needed, programmed with the *Bluetooth - NCP ESL Access Point* sample application along with an appropriate bootloader project called *Bootloader - NCP BGAPI UART DFU*.

To run the ESL AP Python host example, a preliminary step is required to build the necessary ESL shared libraries which are written in C. As for the build environment and build process, three main operating systems are supported: Windows, Linux and macOS, all of which can be used on any machine architecture.

### Pre-steps before building
For Windows only, the first thing we need is a UNIX-like utility environment, for which we have MSYS2 as a regular tool at Silabs. After downloading and installing MSYS2, we also need to download make utility and the appropriate Minimalist GNU for Windows GCC compiler: to choose the right architecture, we need to know which Python architecture we have, as it needs to compile slightly differently for 64-bit and 32-bit versions.

As for the Python version, version 3.9 is recommended - but later versions may work as well. On Windows, it is also recommended to install it into a custom directory to avoid unexpected errors later. It is essential that the installed executable environment is not placed in the read-only '*Program Files*' folders, and that the installer is allowed to set the necessary PATH variables. Furtunatelly, no such complications are known to exist with Linux and macOS.

Some possible pitfalls of a Windows installation may happen: the MSYS2 MinGW environment can have a built-in Python interpreter installed in the */usr/bin* or */mingw/bin* folder (`which Python` can be used to find out). Although advanced users will be definitely able to compile with this Python if they know how to fix various errors that may come during the build execution, it is strongly discouraged due to the many potential sources of trouble.
In addition, as it was mentioned earlier, if the native Windows Python is located in Program Files, advanced manual configuration of the PATH environment variable may be also required, without which the build process can stall at the final stage. That's why it's heavily recommended to install it in location that isn't write-protected, as shown in the image below.

![](images/python_install_windows.png)

Installing the proper GCC version is also essential. For example, if our Python is 32-bit, but the ESL key library and ESL C library are compiled with GCC for MinGW64, the import will fail and the AP example code will not start. This means either issuing `pacman -S make mingw-w64-x86_64-gcc`, or `pacman -S make mingw-w64-i686-gcc` in the MinGW32 or MinGW64 bash terminal, depending on Python interpreter architecture.

Finally, as we're about to use the systems' native Python environment, the MSYS2 MinGW environment should be started with the `-use-full-path` option. Without this, the compilation will fail as well. That is, start either with `msys2_shell.cmd -mingw32 -use-full-path` or `msys2_shell.cmd –mingw64 -use-full-path` depending on Python.

### Building the shared libraries

### Pre-steps before building
For Windows only, the first thing we need is a UNIX-like utility environment, for which we have MSYS2 as a regular tool at Silabs. After downloading and installing MSYS2, we also need to download make utility and the appropriate Minimalist GNU for Windows GCC compiler: to choose the right architecture, we need to know which Python architecture we have, as it needs to compile slightly differently for 64-bit and 32-bit versions.

As for the Python version, version 3.9 is recommended - but later versions may work as well. On Windows, it is also recommended to install it into a custom directory to avoid unexpected errors later. It is essential that the installed executable environment is not placed in the read-only `Program Files` folders, and that the installer is allowed to set the necessary PATH variables. Furtunatelly, no such complications are known to exist with Linux and macOS.

Some possible pitfalls of a Windows installation may happen: the MSYS2 MinGW environment can have a built-in Python interpreter installed in the */usr/bin* or */mingw/bin* folder (`which Python` can be used to find out). Although advanced users will be definitely able to compile with this Python if they know how to fix various errors that may come during the build execution, it is strongly discouraged due to the many potential sources of trouble.
In addition, as it was mentioned earlier, if the native Windows Python is located in Program Files, advanced manual configuration of the PATH environment variable may be also required, without which the build process can stall at the final stage. That's why it's heavily recommended to install it in location that isn't write-protected, as shown in the image below.

![](images/python_install_windows.png)

Installing the proper GCC version is also essential. For example, if our Python is 32-bit, but the ESL key library and ESL C library are compiled with GCC for MinGW64, the import will fail and the AP example code will not start. This means either issuing `pacman -S make mingw-w64-x86_64-gcc`, or `pacman -S make mingw-w64-i686-gcc` in the MinGW32 or MinGW64 bash terminal, depending on Python interpreter architecture.

Finally, as we're about to use the systems' native Python environment, the MSYS2 MinGW environment should be started with the `-use-full-path` option. Without this, the compilation will fail as well. That is, start either with `msys2_shell.cmd -mingw32 -use-full-path` or `msys2_shell.cmd mingw64 -use-full-path` depending on Python.

### Building the shared libraries

Run the `make` command in the project's root folder (*example\_host/bt\_host\_esl\_ap*). It will generate the *esl\_lib\_wrapper.py* and the *esl\_key\_lib\_wrapper.py*. These files are responsible for the transfer between the Python script and the C library.

### Starting AP application

On Windows, the PowerShell is the preferred running environment, but it can also run under the basic command line. However, using the MSYS2 MinGW bash is not recommended for this purpose due to known compatibility issues between the native Windows Python running environment and that of MSYS2. On other systems like Linux and macOS any terminal can be used. 
 
AP can be run in manual, demo or automatic mode. Without using the `--cmd` or the `--demo` command line parameter, automatic mode is started.

For example to start AP on Windows system where an NCP is connected to COM4, type `python .\app.py COM4` in terminal. If the AP is the only Silabs board connected to the PC via USB there is no need to specify the COM port. Mode can also be set later runtime using the [`mode`](#mode) command.

![](images/ap_start.png)

In parallel one or more Tags can be powered on. Once they booted up, the WSTK display will show the following picture (assuming an unmodified *Bluetooth - SoC ESL Tag* example project):

![](images/01_startup.png)

Assuming the automated mode startup above, the already running AP script will find then configure the Tag shortly after with an arbitrary image:

![](images/02_provisioned.png)

## Runtime commands
---
### ESL Tag commands
---

#### ping
    Get the Basic State response of the addressed ESL.

Usage: `ping [-h] [--group_id <u7>] esl_id`

Parameters:
- `esl_id`:                 ESL ID of the Tag. _Note: `all` also can be used as a broadcast address (0xff) if `IOP_TEST` config is set to `True`. (Although it still makes no sense as broadcast messages doesn't solicit any response by the spec.)_
- `[--group_id, -g <u7>]`:  ESL group ID (optional, default is group 0)

#### config
    Configure the writable mandatory GATT characteristics of the ESL tag.

Usage: `config [-h] [--full] [--esl_id <u8>] [--group_id <u7>] [--sync_key] [--response_key] [--time | --absolute <u32>] [device]`

Positional argument:
- `device`:                       Bluetooth address of the target device (e.g. `AA:BB:CC:DD:EE:22`) in case insensitive format or `all`.

Parameters:
- `[--full]`:                     Configure everything in one step. ESL ID and group can be specified to override default values - see notes.
- `[--esl_id, -i <esl_id_type>]`: New ESL ID of the connected tag.
- `[--group_id, -g <u7>]`:        New ESL group ID (optional, default is group 0).
- `[--sync_key, -sk]`:            Set current Access Point Sync Key Material.
- `[--response_key, -rk]`:        Generate then set new Response Key Material.
- `[--time, -t]`:                 Set current Absolute Time of the ESL Access Point.
- `[--absolute, -a <u32>]`:       Set custom Absolute Time epoch value - use with care! _Mutually exclusive with the `--time` parameter._

_Notes:_
- _Either the option `--full` or at least one of the optional parameters shall be given._
- _The 'all' keyword can be used to configure a number of connected ESLs, but the ESL ID can't be specified in turn, as this would make the command ambiguous._
- _However, the same ESL group ID can be specified for multiple connected devices - but use this with care, as this command doesn't check against existing ESL configurations, so the network MAY END UP BROKEN!_

Examples:
-  `config --full --absolute 0`
  
   Will configure everything plus overrides the ESL Absolute Time epoch value for the given tag (e.g. for testing purposes)
-  `config -i 2 -g 3`

   (Re-)configure only ESL ID and group ID - please note that the other ESL Characteristics e.g. Key Materials and Absolute Time will remain unchanged this way, including their unconfigured states if that's the case.
-  `config -i 1 AA:BB:CC:DD:EE:22`

   (Re-)configure only ESL ID while group ID remains unchanged (0 by default if not given before). Bluetooth address shall be given if there are more active connection opened.

#### connect
    Connect to one or more ESL devices.

Usage: `connect [-h] [--group_id <u7>] [--addr_type, -t] address`

positional arguments:
- `address`                 Bluetooth address (e.g. `AA:BB:CC:DD:EE:22`) in case insensitive format or ESL ID of the tag or `all`.

Parameters:
- `[--group_id, -g <u7>]`:  ESL group ID (optional, default is group 0).
- `[--addr_type, -t]`:      ESL address type (optional), possible values:
    - `public`:             Public device address (default assumption).
    - `static`:             Random static device address.

_Notes:_
- _`<esl_id>` and `<group_id>` can be used instead of `<bt_addr>` if ESL is already configured._
- _`<address_type>` will be taken into account only if the given `<bt_addr>` is unknown - otherwise the proper type reported by the remote device will be used._
- _If the `<group_id>` is not given after the ESL ID then the default value group zero is used. This applies to many commands expecting the group ID as optional parameter._
- _The `all` keyword can be used with a special meaning with `connect` command: it will try to connect to all advertiser ESLs (within the 'group_id' if it is given or to any advertisers if it isn't) up to the the maximum number of simultaneous connections supported by the current build of the ESL library and the attached Network Co-Processor embedded controller._
- _If the group is specified along with the keyword `all`, then only devices in the group will be connected. That is, specifying the group ID will not work with ESLs that are not yet configured._
- _An explicit address type is ignored for an already configured ESL that is addressed by ESL ID. The correct type is already known in this case and will be used instead._

Examples:
- `connect bc:33:ac:fa:57:d0`

   Try connect to the given address - even if it's advertisement is not detected e.g. due disabled scanning. Will fail with timeout if the given address is out of radio range.
- `connect`

   Checks nearby advertisers and connects to one if there's only one. Scan needs to be enabled for this to work.
- `connect all`

   Checks nearby advertisers and connects to all up to the supported number of parallel connections. Scan needs to be enabled for this to work.

#### delete\_timed
    Delete a delayed command of an ESL Tag peripheral with the selected index.

Usage: `delete_timed [-h] [--group_id <u7>] {led,display} esl_id index`

Parameters:
- `{led,display}`: Delete timed led or display_image command.
- `esl_id`:        ESL ID of the Tag.
- `index`:         Index of the LED or the display.
- `[--group_id, -g <u7>]`:  ESL group ID (optional, default is group 0).

#### disconnect
    Initiate the Periodic Advertisement Sync Transfer process if PAwR train is
    available then disconnect from an ESL device with the specified address.

Usage: `disconnect [-h] [--group_id <u7>] [<address>]`

Positional argument:
- `<address>`:  Bluetooth address (e.g. `AA:BB:CC:DD:EE:22`) in case insensitive format or ESL ID of the tag or `all`.

Parameters:
- `[--group_id, -g <u7>]`:  ESL group ID (optional, default is group 0).

_Notes:_
- _If no address is specified, the default active connection is closed - if only one exists._
- _To close more existing connections at once, you can use the `disconnect all` command._
- _If the group ID is specified with the keyword `all`, then only the devices in the group will be disconnected._

Examples: 
- `disconnect bc:33:ac:fa:57:d0`

  Disconnect from the addressed device.
- `disconnect`

  Disconnect from the only existing connection - gives error response if there's none or more than one.
- `disconnect all -g0`

  Disconnect from all connected ESLs that are in group 0.


#### display\_image
    Display desired image on target ESL.

Usage: `display_image [-h] [--group_id <u7>] [--time <hh:mm:ss> | --absolute <u32>] [--delay <u32>] [--date <YYYY-MM-DD>] esl_id image_index display_index`

Parameters:
- `esl_id`:                    ESL ID of the Tag. 
                               _Note: `all` also can be used as a broadcast address (0xff)._
- `image_index`:               Image index.
- `display_idx`:               Display index.
- `[--group_id, -g <u7>]`:     ESL group ID (optional, default is group 0).
- `[--time, -t <hh:mm:ss>]`:   Execution time of the command in hour:min:sec format. (optional) 
                               _Note: If <--delay> is specified then it is also added to the calculated value as an additional delay._
- `[--absolute, -a <u32>]`:    Execution time of the command in ESL Absolute Time epoch value. Mutually exclusive with timed delay.
- `[--date, -d <YYYY-MM-DD>]`: Execution date of the command in ISO-8601 format (optional to time, only).
- `[--delay, -dy <u32>]`:      Delay in milliseconds (optional).

_Note:_ 
- _Timed display commands with a delay shorter than the actual periodic advertisement interval may be rejected on receive by Implausible Absolute Time (0x0C) ESL error response._

Example: 
- `display_image 17 1 0 --delay=5000`

![](images/03_imageupdate.png)

#### image\_update
    Update single image on one or more connected Tags.

Usage: `image_update [-h] [--address <addr>] [--group_id <u7>] [--label <str>] [--cropfit] [--raw | --display_index <u8>] [--cw | --ccw | --flip] image_index imagefile_path`

Positional arguments:
- `image_index`:                Image storage index of the ESL tag to be updated.
- `imagefile_path`:             Relative or full path to the selected image file. Use quotation marks if the path contains spaces.
- `[address]`:                  Bluetooth address of the target device or ESL ID / `all` if there are more ESLs connected.

Optional arguments:
- `[--group_id <u7>, -g <u7>]`: ESL group ID (optional, default is group 0)
- `[--label, -l <str>]`:        Caption to be written over the image. Use quotation marks if it includes spaces or line breaks.
- `[--cropfit, -c]`:            Fit the image to the display proportions by cropping.
- `[--raw, -r]`:                Upload raw image file without any conversion.
- `[--display_index, -d <u8>]`: Try auto-conversion image for this display. Mutuall exclusive with `--raw` argument.
- `[--cw, -rr]`:                Clockwise (right) rotation.
- `[--ccw, -rl]`:               Counter clockwise (left) rotation.
- `[--flip, -f]`:               Turn the image upside down
                                _Note: cw, ccw and flip are mutually exclusive_

_Notes:_ 
- _ESL Tag must be connected to the AP before running this command._
- _The ESL won't display any change after the image upload is complete unless a `display image` command is also sent with the same image index - or a `refresh display` command to a display already showing the same image that has changed. Please refer to the `display_image` and `refresh_display` commands' examples._
- _To use space or backslash in the filename or other special characters, such as line break escape sequences in the text caption, please enclose these strings in quotes._
- _The modifiers like rotation, fitting and and labeling are mutually exclusive with raw data input._
- _If the group is specified along with the keyword `all`, then only connected devices in the group will be affected._

Examples:
- `image_update 0 ./image/banana.png --label="Line 1\nLine 2"`

  Send an image to index 0 on the single connected ESL with two lines of label. Note that address is a positional argument yet it can be omitted if there's only one connected device present at the moment.
- `image_update 1 "/user/home/path with space/img.jpg"` all

  Use the 'all' keyword as special address to send the same image to slot 1 on all connected ESLs.

#### led
    Turn on / off or flash an LED utilizing the LED control command.

Usage: `led [-h] [--group_id <u7>] [--default] [--pattern <bits>] [--on_period <int[0,3]>] [--off_period <int[0,3]>] [--brightness <int[0,3]>] [--color <int[0,3]>] [--repeats <u15> | --duration <u15>] [--index <u8>] [--time <hh:mm:ss> | --absolute <u32>] [--delay <u32>] [--date YYYY-MM-DD] {on,off,flash} esl_id`

Parameters:
- `{on,off,flash}`:                 Turn ON/OFF LED or flash LED based on a bit pattern.
- `esl_id`:                         ESL ID of the Tag. _Note: `all` also can be used as a broadcast address (0xff)._
- `[--group_id, -g <u7>]`:          ESL group ID (optional, default is group 0).
- `[--default, -d]`:                Restore the default flashing pattern built-in with AP.
- `[--pattern, -p <bits>]`:         A string containing either `1`s or `0`s, max length: 40.
- `[--on_period, -on <int[0,3]>]`:  Integer value from 1 to 255, meaning `delay *2ms` for on state bits of the pattern. `0` is prohibited.
- `[--off_period, -of <int[0,3]>]`: Integer value from 1 to 255, meaning `delay *2ms` for off state bits of the pattern. `0` is prohibited.
- `[--brightness, -b <int[0,3]>]`:  4 step brightness from 0 to 3.
- `[--color, -c <int[0,3]>]`:       Red, green and blue values - only applies to LED with sRGB type.
- `[--repeats, -r <u15>]`:          How many times the pattern shall be repeated. Mutually exclusive with `--duration` parameter. Value set is [1-32767].
- `[--duration, -dn <u15>]`:        How many seconds the pattern shall be repeated. Mutually exclusive with `--repeats` parameter. Value set is [1-32767].
- `[--index, -i <u8>]`:             Index of the LED (optional, default 0).
- `[--time, -t <hh:mm:ss>]`:        Execution time of the command in hour:min:sec format. (optional)
                                    _Note: If `<--delay>` is specified then it is also added to the calculated value as an additional delay._
- `[--absolute, -a <u32>]`:         Execution time of the command in ESL Absolute Time epoch value. Mutually exclusive with timed delay.
- `[--date, -dt YYYY-MM-DD]`:       Execution date of the command in ISO-8601 format (optional to time, only).
- `[--delay, -dy <u32>]`:           Delay in milliseconds (optional).

Example: `led flash 17 --index=1 --pattern=101100111000 --time=16:18:00`

![](images/04_ledon.png)

_Notes:_
- _Arguments controlling flashing parameters are ignored for 'on' and 'off' commands._
- _Color and brightness control parameters are useless for 'off' command._
- _Timed LED commands with a delay shorter than the actual periodic advertisement interval may be rejected on receive by Implausible Absolute Time (0x0C) ESL error response. Please refer the ESL specification on timed commands._
- _If the delay is given in the human readable form (using `--time`) then the LED will either turn on on the same day at the specified time or the next day - the latter if the given time has passed already on your local computer's clock!_
- _In the SoC ESL Tag example the LED at index 0 is used for special purposes, that is it can't be controlled directly as opposed to LED 1 on the WSTK. Rather, LED 0 is used as optical feedback only for various internal states of the ESL Tag. Nevertheless, the special function for LED 0 can be still switched on and off via the `led` command._
- _Almost all of the optional led control parameters are "sticky", meaning that the last values are preserved by the AP internally and will be re-used next time, if the given parameter is omitted in the argument list. This doesn't apply on the delay, time and absolute parameters, though._

#### refresh\_display
    Refresh ESL Tag display.

Usage: `refresh_display [-h] [--group_id <u7>] esl_id display_index`

Parameters:
- `esl_id`:                ESL ID of the Tag. _Note: `all` also can be used as a broadcast address (0xff)._
- `display_id`:            Display index.
- `[--group_id, -g <u7>]`: ESL group ID (optional, default is group 0).

#### update\_complete
    Send Update Complete ESL opcode.
Usage: `update_complete [-h] [--group_id <u7>] [address]`

Positional argument:
- `[address]`:             Bluetooth address (e.g. `AA:BB:CC:DD:EE:22`) in case insensitive format or ESL ID of the tag or `all`.

Parameters:
- `[--group_id, -g <u7>]`: ESL group ID (optional, default is group 0).

_Notes:_
- _The `update_complete` command works only in IOP test mode!_
- _If the group is specified along with the keyword `all`, then only connected devices in the group will be affected._

#### unassociate
    Unassociate Tag from AP.

Usage: `unassociate [-h] [--group_id <u7>] address`

Parameters:
- `address`:                Bluetooth address in case insensitive format or ESL ID of the Tag.
                            _Note: `all` also can be used as a broadcast address (0xff)._
- `[--group_id, -g <u7>]`:  ESL group ID (optional, default is group 0).

Example: `unassociate 17 -g 2`

#### factory\_reset
    Reset ESL to a state when it was not associated with the AP. 
    It means ESL deletes all configuration value set by the AP including image data.

Usage: `factory_reset [-h] [--group_id <u7>] [--pawr] address`

Parameters:
- `address`:                Bluetooth address in case insensitive format or ESL ID of the Tag. 
                            _Note: `all` also can be used as a broadcast address (0xff)._
- `[--group_id, -g <u7>]`:  ESL group ID (optional, default is group 0).
- `[--pawr]`:               Force command through PAwR sync train even if the addressed ESL is currently connected.

#### service\_reset
    Send Service Reset command.

Usage: `service_reset [-h] [--group_id <u7>] esl_id`

Parameters:
- `esl_id`:                 ESL ID of the tag. _Note: `all` also can be used as a broadcast address (0xff)._
- `[--group_id, -g <u7>]`:  ESL group ID (optional, default is group 0).

#### read\_sensor
    Read sensor information.

Usage: ` read_sensor [-h] [--group_id <u7>] esl_id sensor_index`

Parameters:
- `esl_id`:                 ESL ID of the tag.
- `sensor_index`:           Sensor index.
- `[--group_id, -g <u7>]`:  ESL group ID (optional, default is group 0).

#### vendor\_opcode
    Send generic ESL vendor specific command.

Usage: `vendor_opcode [-h] [--group_id <u7>] [--data <hex>] esl_id`

Parameters:
- `esl_id`:                ESL ID of the tag.
- `[--data, -d <hex>]`:    ASCII hexadecimal data stream up to 16 bytes overall - an appropriate TLV to the given length will be built automatically.
- `[--group_id, -g <u7>]`: ESL group ID (optional, default is group 0).

Examples:
- `vendor_opcode 0 -g 1`

  There will be no extra payload, the resulting ESL TLV is 0F00 for group 1
- `vendor_opcode 3 --data 0x0004`

  2 bytes payload, the resulting ESL TLV is 2F030004 for default group 0
- `vendor_opcode 1 --data 12233` 

  3 bytes payload, the resulting ESL TLV is 3F01012233
- `vendor_opcode 5 -d 0012233`

  4 bytes payload, the resulting ESL TLV is 4F0500012233

### Access Point control commands
---
#### help
    Help utility.

Usage: `help <command>`

Examples:
- `help`

  Display available commands
- `help list`

  Display help message of a specific (in this case `list`) command


![](images/terminal_help.png)

#### mode
    Changes ESL Access Point operation mode.

Usage: `mode [-h] [{auto,manual}]`

Parameters:
- `{auto,manual}`:   Switch to automatic or manual mode.

_Note: To check current mode you can issue the command without argument._

Examples:
- `mode manual`

  Change mode to manual mode.
- `mode`

  Ask current mode.

#### set\_rssi\_threshold
    Set RSSI filter threshold value. Below this value the device will be ignored during scanning.

Usage: ` set_rssi_threshold [-h] rssi`

Parameters:
- `rssi`: RSSI value.

_Note: Negative values are accepted, only!_

#### scan
    Start or stop scanning for advertising ESL devices.

Usage: `scan [-h] [--active, -a] {start,stop}`

Parameters:
- `{start, stop}`: Start/stop scanning for advertising ESL devices.
- `[--active]`:    Start active scan instead of default passive.

_Notes:_
- _Passive tpye scanning starts automatically when AP script is started in auto mode to provide continuous Tag discovery._
- _You can obtain the current status of the scanning by omitting the choice._

#### list
    List ESL Tag information.

Usage: `list [-h] [--verbose] [--group_id <u7>] state [state ...]`

Parameters:
- `state`:                   {advertising, a, blocked, b, connected, c, synchronized, s, unsynchronized, u} 
    - `[advertising, a]`:    List advertising Tag information.
    - `[blocked, b]`:        List blocked (advertising) tag information.
    - `[connected, c]`:      List connected Tag information.
    - `[synchronized, s]`:   List synchronized Tag information.
    - `[unsynchronized, u]`: List unsynchronized Tag information.
- `[--verbose, -v]`:         List more detailed information (optional).
- `[--group_id, -g <u7>]`:   ESL group ID filter (optional - default: all group).

Examples:
- `list synchronized -v`
- `list a c`

_Note: To reset the list of advertising and blocked lists you may want to issue a `scan start` command at any time._

#### sync
     Start / stop sending synchronization packets.

Usage:
  - `sync [-h] [--millis] [--in_max <int>] [--in_min <int>] [--se_count <int>] [--se_interval <int>] [--rs_delay <int>] [--rs_spacing <int>] [--rs_count <int>] {start,stop,config}`

Parameters:
- `{start,stop,config}`:              Start/Stop sending periodic synchronization packets or set PAWR parameters.
- `[--millis, -ms]`:                  Specify timing parameters in milliseconds.
- `[--in_max <int>, -max <int>]`:     Maximum periodic advertising interval in ms if -ms was given, otherwise in units of 1.25ms.
- `[--in_min <int>, -min <int>]`:     Minimum periodic advertising interval in ms if -ms was given, otherwise in units of 1.25ms.
- `[--se_count <int>, -sc <int>]`:    Number of subevents.
- `[--se_interval <int>, -si <int>]`: Subevent interval in ms if -ms was given, otherwise in units of 1.25ms.
- `[--rs_delay <int>, -rd <int>]`:    Response slot delay in ms if -ms was given, otherwise in units of 1.25ms.
- `[--rs_spacing <int>, -rs <int>]`:  Response slot spacing in ms if -ms was given, otherwise in units of 0.125ms.
- `[--rs_count <int>, -rc <int>]`:    Response slot count.

_Notes:_
- _After changing the PAwR sync configuration by `sync config` the sync train needs to be restarted by issuing a simple `sync start` command. The new config will take place until exiting the script._
- _Issuing `sync config` without any further parameter will display the current sync train configuration._
- _Using the optional `-ms` argument with the 'config' subcommand allows you to specify timing parameters in milliseconds instead of their natural units, but this may introduce rounding errors. Please also note that with this option the fractional milliseconds can't be specified precisely._
- _You can ask for the current status of the PAwR train by omitting the choice._

Examples:
- `sync start`

  Start sync with current PAwR parameters.
- `sync config -min 1500 -max 2500 -sc 3 -si 250 -rd 170 -rs 3 -rc 24`

  Configure PAwR train with given parameters - please note that the new config will be active after sync is re-started.
- `sync config`

  Get current config and doesn't change any sync status. That is, the PAwR train will continue running if it was already enabled.  
- `sync start [-min 2000] -max 2100`

  Start sync with current PAwR parameters, but temporarily override the interval to a value between 2.0 and 2.1 seconds. Please note that this short form is only for convenience to quickly change the interval, but its effect on the current configuration is not permanent and the value is always interpreted in milliseconds - so it may also introduce rounding errors.

#### demo
     Control the built-in advertising feature of the ESL NCP AP target for the ESL demo in the EFR Connect mobile application.

Usage:  `demo [-h] {on,off}`

Parameters:
- `{on,off}`: Turn AP advertising on or off for ESL Demo in EFR Connect mobile app.

#### script
     Record or execute commands from an input file.

Usage: `script [-h] {record,run,wait} file_or_sec`

Parameters:
- `{record,run,wait}`: Record commands to an output file <filename> or
                       run commands from an input file <filename> or
                       wait interval in seconds <seconds>.
- `file_or_sec`: Filename to write / read AP commands (in case of record/run)
                 or wait interval in seconds (in case of wait)

_Notes:_
- _Note: If `stop` given as a filename then recording of commands will stop._
- _Scripting is an experimental feature, only - it is lack of advanced features like programmed reactions to events or configuration dependent and / or conditional execution, etc.._
- _Recorded script files may run other scripts also, but never use it recursively! That is, avoid running the script from within itself or the AP script will crash. However, it is strongly advised to keep the scripting level low as possible. Use with care!_

Examples:
- `script record myscript.esl`

  Start recording to local file `myscript.esl`.
- `script record stop`

  Stop current recording (issue after steps to be recorded were executed manually).
- `script run myscript.esl`

  Repeat steps (commands) that were previously recorded to local file `myscript.esl`.
- `script record test.script ; image_update 0 "image/banana.png" -l "hello;\n world!" ; ping 0 ; config -f -i1 ; script wait 2 ; display_image 1 0 0 ; script record stop`

  Advanced example to demonstrate complex scripting with command chaining at the same time. Please note that the command separator `;` needs spaces before and after for the chaining to work properly. The recored script will contain one command per line as it was recorded without command chaining.

#### verbosity

     Set Access Point logging verbosity level at runtime

Usage:  `verbosity [-h] [{NOTSET,DEBUG,INFO,WARNING,ERROR,CRITICAL}]`

Parameters:
- `{NOTSET,DEBUG,INFO,WARNING,ERROR,CRITICAL}` Level to apply

_Notes:_
- _To check current verbosity level you can issue the command without argument._
- _NOTSET can be used to display debugging messages not only for AP code, but also for all python modules that may utilze logging._

#### exit
    Terminate AP application.

Usage: `exit`
