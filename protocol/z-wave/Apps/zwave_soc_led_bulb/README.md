# LED Bulb

The Z-Wave certified LED Bulb application shows an implementation of a remotely controlled color 
switch. An example is a LED bulb or any other color capable device.

The LED Bulb application is based on:

| <!-- -->                | <!-- -->                                     |
| ----------------------- | -------------------------------------------- |
| Role Type               | Always On End device (AOS)                   |
| Supporting  Device Type | Actuator                                     |
| Device Type             | Color Switch                                 |
| Generic Type            | Switch Multilevel                            |
| Specific Type           | Color Tunable Multilevel                     |
| Requested security keys | S0, S2_UNAUTHENTICATED, and S2_AUTHENTICATED |

## Supported Command Classes

The LED Bulb application implements mandatory and some optional command classes. The table below 
lists the supported Command Classes, their version, and their required Security class

| Command Class             | Version | Required Security Class        |
| :------------------------ | :-----: | :----------------------------- |
| Association               |    2    | Highest granted Security Class |
| Association Group Info    |    3    | Highest granted Security Class |
| Basic                     |    2    | Highest granted Security Class |
| Color Switch              |    3    | Highest granted Security Class |
| Device Reset Locally      |    1    | Highest granted Security Class |
| Firmware Update Meta Data |    5    | Highest granted Security Class |
| Indicator                 |    3    | Highest granted Security Class |
| Manufacturer Specific     |    2    | Highest Granted Security Class |
| Multi-Channel Association |    3    | Highest granted Security Class |
| Multilevel Switch         |    4    | Highest granted Security Class |
| Powerlevel                |    1    | Highest granted Security Class |
| Security 0                |    1    | None                           |
| Security 2                |    1    | None                           |
| Supervision               |    1    | None                           |
| Transport Service         |    2    | None                           |
| Version                   |    3    | Highest granted Security Class |
| Z-Wave Plus Info          |    2    | None                           |


## Basic Command Class Mapping

The Basic Command Class is mapped according to the table below.

| Basic Command                          | Mapped Command                             |
| :------------------------------------- | :----------------------------------------- |
| Basic Set (Value)                      | Multilevel Switch Set (Value)              |
| Basic Report (Current Value, Duration) | Multilevel Switch Report (Value, Duration) |

## Association Groups

The following association groups shown in the table below are available for Z-Wave and Z-Wave Long 
Range respectively.

<table>
<tr>
    <th>ID</th>
    <th>Name</th>
    <th>Node Count</th>
    <th>Description</th>
</tr><tr>
    <td>1</td>
    <td>Lifeline</td>
    <td>X</td>
    <td>
        <p>Supports the following command classes:</p>
        <ul>
            <li>Device Reset Locally: triggered upon reset.</li>
            <li>Color Switch Report: Triggered when the switch changes state.</li>
            <li>Multilevel Switch Report: Triggered when the switch changes state.</li>
            <li>Indicator Report: Triggered when LED1 changes state.</li>
        </ul>
    </td>
</tr>
</table>

X: For Z-Wave node count is equal to 5 and for Z-Wave Long Range it is 1.

## Usage of Buttons and LED Status

The following LEDs and buttons shown in the table below are used.

<table>
<tr>
    <th>Button</th>
    <th>Action</th>
    <th>Description</th>
</tr><tr>
    <td>RST</td>
    <td>Press</td>
    <td>Resets the firmware of an application (like losing power). All volatile memory will be cleared.</td>
</tr><tr>
    <td rowspan="2">BTN1</td>
    <td>Press</td>
    <td>
        Enter "learn mode" (sending node info frame) to add/remove the device.<br>
        Removing the device from a network will reset it.
    </td>
</tr><tr>
    <td>Hold for at least 5 seconds and release</td>
    <td>Perform a reset to factory default operation of the device, and a Device Reset Locally Notification Command is sent via Lifeline.</td>
</tr>
</table>

<table>
<tr>
    <th>LED</th>
    <th>Description</th>
</tr><tr>
    <td>LED0</td>
    <td>
        Blinks with 1 Hz when learn mode is active.<br>
        Used for Indicator Command Class.
    </td>
</tr><tr>
    <td>LED1</td>
    <td>LED On -> Multilevel Switch On / Led Off -> Multilevel Switch Off</td>
</tr><tr>
    <td>RGB (on ZGM130 module)</td>
    <td>Controlled by CC Color Switch (colors) and CC Multilevel Switch (brightness)</td>
</tr>
</table>

## Firmware Update

SDK 7.14.0 is the first SDK, including LED Bulb. When there are new versions of LED Bulb application, backward compatibility notes will be added in this section.
