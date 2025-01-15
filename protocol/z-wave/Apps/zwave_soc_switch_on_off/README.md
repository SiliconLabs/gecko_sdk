# Switch On/Off

The Z-Wave certified Switch On/Off application shows a switch implementation, that turns on any device that is connected to power. Examples include lights, appliances, etc.

| <!-- -->                | <!-- -->                                     |
|-------------------------|----------------------------------------------|
| Role Type               | Always On End device (AOS)                   |
| Supporting Device Type  | Actuator                                     |
| Device Type             | Binary Switch                                |
| Generic Type            | Switch Binary                                |
| Specific Type           | Not Used                                     |
| Requested security keys | S0, S2_UNAUTHENTICATED, and S2_AUTHENTICATED |

## Supported Command Classes
The Switch On/Off application implements mandatory and some optional command classes. The table
below lists the supported Command Classes, their version, and their required Security class.

| Command Class             | Version | Required Security Class        |
| ------------------------- |:-------:| ------------------------------ |
| Association               |    2    | Highest granted Security Class |
| Association Group Info    |    3    | Highest granted Security Class |
| Basic                     |    2    | Highest granted Security Class |
| Binary Switch             |    2    | Highest granted Security Class |
| Device Reset Locally      |    1    | Highest granted Security Class |
| Firmware Update Meta Data |    5    | Highest granted Security Class |
| Indicator                 |    3    | Highest granted Security Class |
| Manufacturer Specific     |    2    | Highest Granted Security Class |
| Multi-Channel Association |    3    | Highest granted Security Class |
| Powerlevel                |    1    | Highest granted Security Class |
| Security 0                |    1    | None                           |
| Security 2                |    1    | None                           |
| Supervision               |    1    | None                           |
| Transport Service         |    2    | None                           |
| Version                   |    3    | Highest granted Security Class |
| Z-Wave Plus Info          |    2    | None                           |

### Basic Command Class mapping

Basic Command Class is mapped to Binary Switch CC

| Basic Command                          | Mapped Command                         |
|----------------------------------------|----------------------------------------|
| Basic Set (Value)                      | Binary Switch Set (Value)              |
| Basic Report (Current Value, Duration) | Binary Switch Report (Value, Duration) |

## Association Group configuration

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
            <li>Binary Switch Report: Triggered when the switch changes state.</li>
            <li>Indicator Report: Triggered when LED1 changes state.</li>
        </ul>
    </td>
</tr>
</table>

X: For Z-Wave node count is equal to 5 and for Z-Wave Long Range it is 1.

## Usage of Buttons and LED Status

To use the sample app, the BRD8029A Button and LEDs Expansion Board must be used. BTN0-BTN3 and LED0-LED3 refer to the buttons and LEDs on the Expansion Board.

The following LEDs and buttons shown in the next table below are used.

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
    <td>BTN0</td>
    <td>Press</td>
    <td>Toggle LED0</td>
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
    <td>Switch: LED ON indicates SWITCH ON / LED OFF indicates SWITCH OFF</td>
</tr><tr>
    <td>LED1</td>
    <td>
        Blinks with 1 Hz when learn mode is active.<br>
        Used for Indicator Command Class.
    </td>
</tr>
</table>

## Firmware Update

This section will describe backward compatibility when upgrading the Switch On/Off application from one SDK to a newer version.

SDK 7.1x is the first SDK running on Z-Wave 700.
