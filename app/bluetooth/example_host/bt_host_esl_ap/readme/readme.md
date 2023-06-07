


# ESL Access Point
----
This Python example implements the functionality of an Access Point as specified by the Bluetooth Electronic Shelf Label Profile specification using an NCP ESL AP target. The following features are offered by this example application:

- Finding advertising ESL Tags
- Connecting and configuring Tags either automatically or with full manual control
- Transfer images to Tags via Object Transfer Service (OTS)
- Sending commands to Tags either via Periodic Advertisements with Responses or to the ESL Control Point

## Limitations, known issues
---
- Only one BLE connection is handled at a time. This may affect the system scalability performance.
- In some cases, especially when there are many BLE devices advertising nearby while the AP is scanning for longer periods, the AP script may become unresponsive. In such a case, it may help to limit the period of scanning or to reduce the number of nearby advertising devices. If neither of these are possible, you may want to increase the throughput of the NCP VCOM according to [this article](https://community.silabs.com/s/article/wstk-virtual-com-port-baudrate-setting?language=en_US). After changing the WSTK VCOM speed as described, do not forget to update the VCOM Baud rate configuration of the ESL AP NCP example also accordingly, then re-build and re-flash the target with the new firmware.

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

In general, in any mode one can control the application via CLI - but it is encouraged to change to manual mode via the `mode` [command](#mode) before typing in any ESL control commands. For details of the possible commands, see the help of the ap\_cli.py file. (Type: `help` command in the CLI)

In automated mode the script executes the following functionality:

![](images/auto-mode.png)

You can see the details of the functionality for each mode in the *<mode>\_esl\_event* function. (e.g *cli\_esl\_event\_system\_boot*)

_Note: Shall any unsolicited error occur during the automated process, the automated cycle above may become interrupted. In most of such cases you can still use the CLI to enter commands, thus it is possible to recover the auto mode._

## Getting started
---
One should just run pip install -r requirements.txt before running make
The NCP Host side application requires Python v3. Run *pip install -r requirements.txt* to install all other requirements for the application. Make sure to run this command before running *make*.

On the target side an EFR device is needed, programmed with the *Bluetooth - NCP ESL Access Point* sample application along with an appropriate NCP BGAPI UART DFU bootloader. The bootloader example can be built from a standard, released Gecko SDK.

### Building the library

Run the *make* command in the project's root folder (*example\_host/bt\_host\_esl\_ap*). It will generate the *esl\_lib\_wrapper.py* and the *esl\_key\_lib\_wrapper.py*. These files are responsible for the transfer between the Python script and the C library.

### Starting AP application

AP can be run in manual, demo or automatic mode. Without using the `--cmd` or the `--demo` command line parameter, automatic mode is started.

For example to start AP on Windows system where an NCP is connected to COM4, type `python .\app.py COM4` in terminal. If the AP is the only Silabs board connected to the PC via USB there is no need to specify the COM port. Mode can also be set later runtime using the `mode` command.

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
    Send ESL ping command.

Usage: `ping <esl_id | all> [g=<group_id>]`

Parameters:
- `<esl_id>`:   ESL ID of the Tag. _Note: `all` also can be used as a broadcast address (0xff) if IOP_TEST config True. (Although it still makes no sense as broadcast messages doesn't solicit any response by the spec.)_
- `[g=<group_id>]`: ESL group ID (optional, default is group 0)

#### config
    Configure the writable mandatory GATT characteristics of the ESL tag.

Usage: `config [full] [esl_id=<ui8>] [g=<ui7>] [sync_key] [response_key] [time | absolute=<ui32>]`

Parameters:
- `full`:           Configure everything in one step.
- `esl_id=<u8>`:    New ESL ID of the connected tag.
- `group_id=<u7>`:  New ESL group ID (optional, default is group 0).
- `sync_key`:       Set current Access Point Sync Key Material.
- `response_key`:   Generate then set new Response Key Material.
- `time`:           Set current Absolute Time of the ESL Access Point.
- `absolute=<u32>`: Set custom Absolute Time value. Mutually exclusive with the 'time' parameter.

_Note:_
- _Either the keyword 'all' or at least one of the optional parameters shall be given. The following shortcuts can also be used as keyword replacement: 'i' for 'esl_id', 'g' for 'group', 'sk' for 'sync_key', 'rk' for 'response_key', 't' for 'time', 'a' for 'absolute'._

#### connect
    Connect to an ESL device with the specified address.

Usage: `connect <bt_addr> | <esl_id> [g=<group_id>] [address_type]`

Parameters:
- `<bt_addr>`:        Bluetooth address (e.g., 'AA:BB:CC:DD:EE:22') in case insensitive format.
- `<esl_id>`:         ESL ID of the Tag.
- `[g=<group_id>]`:   ESL group ID (optional, default is group 0).
- `[address_type]`:   ESL address type (optional), possible values:
  - `  public`:       Public device address (default).
  - `  static`:       Static device address.
  - `  rand_res`:     Resolvable private random address.
  - `  rand_nonres`:  Non-resolvable private random address.

_Notes:_
- _`<esl_id>` and `<group_id>` can be used instead of `<bt_addr>` if ESL is already configured._
- _`<address_type>` will be taken into account only if the given `<bt_addr>` is unknown - otherwise the proper type reported by the remote device will be used_
- _If the group ID is not given after the ESL ID then the default value group zero is used. This applies to many commands expecting the group ID as optional parameter._
- _The auto-configuring uses the following schema for ESL addressing: `(16 * number_of_already_synchronized_tags) + 1`_

Example: `connect bc:33:ac:fa:57:d0`

#### disconnect
    Initiate the Periodic Advertisement Sync Transfer process then 
    disconnect from an ESL device with the specified address.

Usage: `disconnect [bt_addr | esl_id [g=<group_id>]]`

Parameters:
- `[bt_addr]`:      Bluetooth address (e.g., 'AA:BB:CC:DD:EE:22') in case insensitive format.
- `[esl_id]`:       ESL ID of the Tag.
- `[g=<group_id>]`: ESL group ID (optional, default is group 0).

_Note:_
- _Should no address be given, then the default active connection will be closed if any._

Examples: `disconnect bc:33:ac:fa:57:d0` or simply `disconnect`

#### display\_image
    Display desired image on target ESL.

Usage: `usage: display_image <esl_id | all> <image_index> <display_idx> [g=<group_id>] [[time=<hh:mm:ss>] [date=<DD-MM-YYYY>] [delay=<delay_ms>] | [absolute=<abs_time>]]`

Parameters:
- `<esl_id>`:              ESL ID of the Tag. 
                           _Note: `all` also can be used as a broadcast address (0xff)._
- `<image_index>`:         Image index.
- `<display_idx>`:         Display index.
- `[g=<group_id>]`:        ESL group ID (optional, default is group 0).
- `[time=<hh:mm:ss>]`:     Execution time of the command in hour:min:sec format. (optional) 
                           _Note: If <delay_ms> is specified then it is also added to the calculated value as an additional delay._
- `[date=<DD-MM-YYYY>]`:   Execution date of the command in day-month-year numeric format (optional to time, only).
- `[delay=<delay_ms>]`:    Delay in milliseconds (optional).
- `[absolute=<abs_time>]`: absolute=<uint32_t>: Execution time of the command in ESL Absolute Time epoch value.

_Note:_ 
- _The following shortcuts can also be used as keyword replacement:_
- _'t' for 'time', 'd' for date, 'dy' for 'delay' and 'a' for 'absolute'._
- _Timed display commands with a delay shorter than the actual periodic advertisement interval may be rejected on receive by Implausible Absolute Time (0x0C) ESL error response._

Example: `display_image 17 1 0 delay=5000`

![](images/03_imageupdate.png)

#### image\_update
    Update single image on the connected Tag.

Usage: `image_update <image_index> <imagefile_path> [raw | display_index=<index>] [label=<text>] [cw | ccw | flip]`

Parameters:
- `<image_index>`:        Image index to update.
- `<imagefile_path>`:     Relative path of the image file.
- `[raw]`:                Upload raw image file without any conversion.
- `[display_index=<u8>]`: Try auto-conversion image for this display.
- `[label=<char>]`:       Label to be upload.
- `[cw]`:                 Clockwise rotation.
- `[ccw]`:                Counter clockwise rotation.
- `[flip]`:               Horizontal flip of the image.
- `[cropfit]`:            Crop the image for the given display.

_Note:_ 
- _ESL Tag must be connected to the AP before running this command._
- _The ESL won't display any change after the image upload is complete unless a `display image` command is also sent with the same image index - or a `refresh display` command to a display already showing the same image that has changed. Please refer to the `display_image` and `refresh_display` commands' examples._

Example: `image_update 1 image/croissant.png`


#### led
    Turn on / off or flash an LED utilizing the LED control command.

Usage: `led <on | off | flash> <esl_id | all> [g=<group_id>] [default] [pattern=<bits>] [on_period=<int>] [off_period=<int>] [brightness=<int>] [color=<#RGB>] [repeats=<times>] | [duration=<sec>] [index=<index>] [[time=<hh:mm:ss>] [date=<DD-MM-YYYY>] [delay=<delay_ms>] | [absolute=<abs_time>]]`

Parameters:
- `on`:                    Turn ON LED.
- `off`:                   Turn OFF LED.
- `flash`:                 Flash led based on a bit pattern.
- `<esl_id>`:              ESL ID of the Tag. _Note: `all` also can be used as a broadcast address (0xff)._
- `[g=<group_id>]`:        ESL group ID (optional, default is group 0).
- `[default]`:             Restore the default flashing pattern built-in with AP.
- `[pattern=<bits>]`:      A string containing either '1's or '0's, max length: 40.
- `[on_period=<int>]`:     Integer value from 1 to 255, meaning 'delay *2ms' for on state bits of the pattern. '0' is prohibited.
- `[off_period=<int>]`:    Integer value from 1 to 255, meaning 'delay *2ms' for off state bits of the pattern. '0' is prohibited.
- `[brightness=<int>]`:    4 step brightness from 0 to 3.
- `[color=<RGB>]`:         Red, green and blue values - only applies to LED with sRGB type.
- `[repeats=<times>]`:     How many times the pattern shall be repeated. Mutually exclusive with `duration=` parameter. Value set is [1-32767].
- `[duration=<sec>]`:      How many seconds the pattern shall be repeated. Mutually exclusive with `repeats=` parameter. Value set is [1-32767].
- `[index=<index>]`:       Index of the LED (optional, default 0).
- `[time=<hh:mm:ss>]`:     Execution time of the command in hour:min:sec format. (optional) _Note: If `<delay_ms>` is specified then it is also added to the calculated value as an additional delay._
- `[date=<DD-MM-YYYY>]`:   Execution date of the command in day-month-year numeric format (optional to time, only).
- `[delay=<delay_ms>]`:    Delay in milliseconds (optional).
- `[absolute=<abs_time>]`: Execution time of the command in ESL. Absolute Time epoch value. Mutually exclusive with other delays.

Example: `led flash 17 index=1 pattern=101100111000 time=16:18:00`

![](images/04_ledon.png)

_Notes:_
- _Timed LED commands with a delay shorter than the actual periodic advertisement interval may be rejected on receive by Implausible Absolute Time (0x0C) ESL error response. Please refer the ESL specification on timed commands._
- _If the delay is given in the human readable form (using `time=`) then the LED will either turn on on the same day at the specified time or the next day - the latter if the given time has passed already on your local computer's clock!_
- _In the SoC ESL Tag example the LED at index 0 is used for special purposes, that is it can't be controlled directly as opposed to LED 1 on the WSTK. Rather, LED 0 is used as optical feedback only for various internal states of the ESL Tag. Nevertheless, the special function for LED 0 can be still switched on and off via the `led` command._
- _Almost all of the optional led control parameters are "sticky", meaning that the last values are preserved by the AP internally and will be re-used next time, if the given parameter is omitted in the argument list. This doesn't apply on the delay, time and absolute parameters, though._
- _The following shortcuts can also be used as keyword replacement: 'd' for default, 'p' for 'pattern', 'on' for 'on_period', 'of' for 'off_period', 'b' for 'brightness', 'c' for 'color', 'r' for 'repeat', 'dn' for 'duration', 'i' for 'index', 't' for 'time', 'd' for date, 'dy' for 'delay' and 'a' for 'absolute'._

#### refresh\_display
    Refresh ESL Tag display.

Usage: `refresh_display <esl_id | all> <display_id> [g=<group_id>]`

Parameters:
- `<esl_id>`:       ESL ID of the Tag. _Note: `all` also can be used as a broadcast address (0xff)._
- `<display_id>`:   Display index.
- `[g=<group_id>]`: ESL group ID (optional, default is group 0).

#### unassociate
    Unassociate Tag from AP.

Usage: `unassociate <bt_addr | <esl_id | all [g=<group_id>]`

Parameters:
- `<bt_addr>`:      Bluetooth address in case insensitive format.
- `<esl_id>`:       ESL ID of the Tag. _Note: `all` also can be used as a broadcast address (0xff)._
- `[g=<group_id>]`: ESL group ID (optional, default is group 0).

_Note: the keyword `all` can be used as a substitute for the ESL broadcast address (0xff)._

Example: `unassociate 17 2`

#### factory\_reset
    Reset ESL to a state when it was not associated with the AP. 
    It means ESL deletes all configuration value set by the AP including image data.

Usage: `factory_reset <bt_addr | <esl_id | all [g=<group_id>]> [pawr]`

Parameters:
- `<bt_addr>`:      Bluetooth address in case insensitive format.
- `<esl_id>`:       ESL ID of the Tag. _Note: `all` also can be used as a broadcast address (0xff)._
- `[g=<group_id>]`: ESL group ID (optional, default is group 0).
- `[pawr]`:         Force command through PAwR sync train even if the addressed ESL is currently connected.

#### service\_reset
    Send Service Reset command.

Usage: `service_reset <esl_id | all> [g=<group_id>]`

Parameters:
- `<esl_id>`:       ESL ID of the tag. _Note: `all` also can be used as a broadcast address (0xff)._
- `[g=<group_id>]`: ESL group ID (optional, default is group 0).

#### read\_sensor
    Read sensor information.

Usage: `read_sensor <esl_id> <sensor_index> [g=<group_id>]`

Parameters:
- `<esl_id>`:       ESL ID of the tag.
- `<sensor_index>`: Sensor index.
- `[g=<group_id>]`: ESL group ID (optional, default is group 0).

### Access Point control commands
---
#### help
    Help utility.

Usage: `help <command>`

Examples:

- Display available commands:

    `help`

- Display help message of a specific (in this case `list`) command:

    `help list`

![](images/terminal_help.png)

#### mode
    Changes ESL Access Point operation mode.

Usage: `mode <auto> | <manual>`

Parameters:
- `<auto>`:   Switch to automatic mode.
- `<manual>`: Switch to manual mode.

Example: `mode manual`

#### scan
    Start or stop scanning for advertising ESL devices.

Usage: `scan <start [active] | stop>`

Parameters:
- `<start>`:  Start scanning for advertising ESL devices.
- `<stop>`:   Stop scanning for advertising ESL devices.
- `[active]`: Start active scan instead of default passive.

_Note: Scanning starts automatically after AP script is started in auto mode to provide continuous Tag discovery._

#### set\_rssi\_threshold
    Set RSSI filter threshold value. Below this value the device will be ignored during scanning.

Usage: `set_rssi_threshold <rssi_value>`

Parameters:
- `<rssi_value>`: RSSI value.

_Note: Negative values are accepted, only!_

#### list
    List ESL Tag information.

Usage: `list <advertising, a> | list <blocked, b> | <synchronized, s> | <usynchronized, u> | <connected, c> [verbose, v] [g=<group_id>]`

Parameters:
- `<advertising, a>`:    List advertising Tag information.
- `<blocked, b>`:        List blocked (advertising) tag information.
- `<connected, c>`:      List connected Tag information.
- `<synchronized, s>`:   List synchronized Tag information.
- `<unsynchronized, u>`: List unsynchronized Tag information.
- `[verbose, v]`:        List more detailed information (optional).
- `[g=<group_id>]`:      ESL group ID filter (optional - default: all group).

Example: `list synchronized v`

_Note: To reset the list of advertising and blocked lists you may want to issue a `scan start` command at any time._

#### sync
     Start / stop sending synchronization packets.

Usage:
  - `sync start [interval_min_ms] [interval_max_ms]`
  - `sync stop`
  - `sync config [ms] [<interval_min> <interval_max> <subevent_count> <subevent_interval> <response_slot_delay> <response_slot_spacing> <response_slot_count>]`

Parameters:
- `<start>`:                 Start sending periodic synchronization packets.
- `<stop>`:                  Stop sending periodic synchronization packets.
- `<config>`:                Set PAWR parameters.
- `[interval_min_ms]`:       Minimum periodic advertising interval in ms.
                             _Note: convenience option for 'start' command only!_
- `[interval_max_ms]`:       Maximum periodic advertising interval in ms.
                             _Note: convenience option for 'start' command only!_
- `<interval_min>`:          Minimum advertising interval in units of 1.25ms.
- `<interval_max>`:          Maximum advertising interval in units of 1.25ms.
- `<subevent_count>`:        Number of subevents.
- `<subevent_interval>`:     Subevent interval in units of 1.25ms.
- `<response_slot_delay>`:   Response slot delay in units of 1.25ms.
- `<response_slot_spacing>`: Response slot spacing in units of 0.125ms.
- `<response_slot_count>`:   Response slot count.

_Notes:_
- _Either only `<interval_min>` or `<interval_min>` and `<interval_max>` together can be used as an optional parameter in case of start._
- _After changing the PAwR sync configuration by `sync config` the sync train needs to be restarted by issuing a simple `sync start` command. The new config will take place until exiting the script._
- _Issuing `sync config` without any further parameter will display the current sync train configuration._
- _Using the optional 'ms' argument in the 'config' command allows you to specify timing parameters in milliseconds instead of their natural units, but this may introduce rounding errors. Please also note that with this option the fractional milliseconds can't be specified precisely._

Examples: `sync start 2000` or `sync config 1500 2500 3 250 170 3 24`

#### script
     Record or execute commands from an input file.

Usage: `script <record> <filename> | <run> <filename> | <wait> <seconds>`

Parameters:
- `<record>`:   Record commands to an output file <filename>. _Note: If `stop` given as a filename then recording of commands will stop._
- `<run>`:      Run commands from an input file <filename>.
- `<filename>`: Filename to write / read AP commands.
- `<wait>`:     Wait before running the next command.
- `<seconds>`:  Wait interval in seconds.

_Notes:_
- _Scripting is an experimental feature, only - it is lack of advanced features like programmed reactions to events or configuration dependent and / or conditional execution, etc.._
- _Recorded script files may contain script commands also, recursively. However, it is strongly advised to keep the recursion level low as possible. Use with care._

Examples: `script record myscript.esl`, `script record stop`, `script run myscript.esl`

#### exit
    Terminate AP application.

Usage: `exit`
