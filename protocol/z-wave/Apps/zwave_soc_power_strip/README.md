# Power Strip

The Z-Wave certified Power Strip application shows an extension block implementation used to turn on 
several devices that are connected to power. Examples include lights, appliances, etc.

The Power Strip Z-Wave certified application implements several endpoints, which can be controlled 
individually.

The Power Strip application is based on:

| <!-- -->                 | <!-- -->                                     |
| ------------------------ | -------------------------------------------- |
| Role Type                | Always On End device (AOS)                   |
| Supporting Device Type   | Actuator                                     |
| Device Type              | Binary Switch                                |
| Generic Type             | Switch Binary                                |
| Specific Type            | Not Used                                     |
| Requested security keys  | S0, S2_UNAUTHENTICATED, and S2_AUTHENTICATED |
| Endpoint 1 Device Type   | Binary Switch                                |
| Endpoint 1 Generic Type  | Switch Binary                                |
| Endpoint 1 Specific Type | Not Used                                     |
| Endpoint 2 Device Type   | Multilevel Switch                            |
| Endpoint 2 Generic Type  | Switch Multilevel                            |
| Endpoint 2 Specific Type | Not Used                                     |

Power Strip supports the "push mode" only of Notification CC and transmits the following notification 
types/events:
- Power Management
  - Overload detected (both endpoint 1 and 2)


##  Supported Command Classes

The Power Strip application implements mandatory and some optional command classes. The table 
below lists the supported command classes, their version, and their required Security class, if any.

| Command Class             | Version | Required Security Class        |
| :------------------------ | :-----: | :----------------------------- |
| Association               |    2    | Highest Granted Security Class |
| Association Group Info    |    3    | Highest Granted Security Class |
| Basic                     |    2    | Highest Granted Security Class |
| Device Reset Locally      |    1    | Highest Granted Security Class |
| Firmware Update Meta Data |    5    | Highest Granted Security Class |
| Indicator                 |    3    | Highest Granted Security Class |
| Manufacturer Specific     |    2    | Highest Granted Security Class |
| Multi-Channel             |    4    | Highest Granted Security Class |
| Multi-Channel Association |    3    | Highest Granted Security Class |
| Notification              |    8    | Highest Granted Security Class |
| Powerlevel                |    1    | Highest Granted Security Class |
| Security 0                |    1    | None                           |
| Security 2                |    1    | None                           |
| Supervision               |    1    | None                           |
| Switch Binary             |    2    | Highest Granted Security Class |
| Transport Service         |    2    | None                           |
| Version                   |    3    | Highest Granted Security Class |
| Z-Wave Plus Info          |    2    | None                           |

###  Supported Command Classes: Endpoint 1

Endpoint 1 implements the following command classes.

| Command Class             | Version | Required Security Class        |
| :------------------------ | :-----: | :----------------------------- |
| Association               |    2    | Highest Granted Security Class |
| Association Group Info    |    3    | Highest Granted Security Class |
| Basic                     |    2    | Highest Granted Security Class |
| Multi-Channel Association |    3    | Highest Granted Security Class |
| Notification              |    8    | Highest Granted Security Class |
| Security 0                |    1    | None                           |
| Security 2                |    1    | None                           |
| Supervision               |    1    | None                           |
| Switch Binary             |    2    | Highest Granted Security Class |
| Z-Wave Plus Info          |    2    | None                           |

###  Supported Command Classes: Endpoint 2

Endpoint 2 implements the following command classes.

| Command Class             | Version | Required Security Class        |
| :------------------------ | :-----: | :----------------------------- |
| Association               |    2    | Highest Granted Security Class |
| Association Group Info    |    3    | Highest Granted Security Class |
| Basic                     |    2    | Highest Granted Security Class |
| Multi-Channel Association |    3    | Highest Granted Security Class |
| Notification              |    8    | Highest Granted Security Class |
| Security 0                |    1    | None                           |
| Security 2                |    1    | None                           |
| Supervision               |    1    | None                           |
| Multilevel Switch         |    4    | Highest Granted Security Class |
| Z-Wave Plus Info          |    2    | None                           |

## Basic Command Class mapping

The Basic Command Class is mapped according to the next table.

| Endpoin | Basic Command                          | Mapped Command                             |
| :------ | :------------------------------------- | :----------------------------------------- |
| 1       | Basic Set (Value)                      | Binary Switch Set (Value)                  |
| 1       | Basic Report (Current Value, Duration) | Binary Switch Report (Value, Duration)     |
| 2       | Basic Set (Value)                      | Multilevel Switch Set (Value)              |
| 2       | Basic Report (Current Value, Duration) | Multilevel Switch Report (Value, Duration) |

## Association Groups

The following three tables show the available association groups for Z-Wave and Z-Wave Long 
Range respectively.
Backward compatibility for non-Multi Channel devices forces the root device AGI table to contain all the 
association groups mentioned in each of the endpoints AGI tables except from group 1, the Lifeline 
group.

### Association groups for Root Device:

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
            <li>Notification: triggered by the endpoints</li>
            <li>Indicator Report: Triggered when LED1 changes state.</li>
        </ul>
    </td>
</tr><tr>
    <td>2</td>
    <td>alarm EP 1</td>
    <td>Y</td>
    <td>Mirror of endpoint 1, group 2</td>
</tr><tr>
    <td>3</td>
    <td>alarm EP 2</td>
    <td>Y</td>
    <td>Mirror of endpoint 2, group 2</td>
</tr>
</table>

X: For Z-Wave node count is equal to 5 and for Z-Wave Long Range it is 1.

Y: For Z-Wave node count is equal to 5 and for Z-Wave Long Range it is 0.

### Association groups for Endpoint 1:

<table>
<tr>
    <th>ID</th>
    <th>Name</th>
    <th>Node Count</th>
    <th>Description</th>
</tr><tr>
    <td>1</td>
    <td>Lifeline</td>
    <td>0</td>
    <td>
        <p>Supports the following command classes:</p>
        <ul>
            <li>Binary Switch Report: Triggered when the switch changes state.</li>
            <li>Notification: triggered by the endpoints</li>
        </ul>
    </td>
</tr><tr>
    <td>2</td>
    <td>alarm EP 1</td>
    <td>Y</td>
    <td>Notification report on overload.</td>
</tr>
</table>

Y: For Z-Wave node count is equal to 5 and for Z-Wave Long Range it is 0.

### Association groups for Endpoint 2:

<table>
<tr>
    <th>ID</th>
    <th>Name</th>
    <th>Node Count</th>
    <th>Description</th>
</tr><tr>
    <td>1</td>
    <td>Lifeline</td>
    <td>0</td>
    <td>
        <p>Supports the following command classes:</p>
        <ul>
            <li>Multilevel Switch Report: Triggered when the switch changes state.</li>
            <li>Notification: triggered by the endpoints</li>
        </ul>
    </td>
</tr><tr>
    <td>2</td>
    <td>alarm EP 2</td>
    <td>Y</td>
    <td>Notification report on overload.</td>
</tr>
</table>

Y: For Z-Wave node count is equal to 5 and for Z-Wave Long Range it is 0.

## Usage of Buttons and LED Status

The following LEDs and buttons shown in the next table below are used.

<table>
<tr>
    <th rowspan="2">Button</th>
    <th rowspan="2">Action</th>
    <th colspan="2">Description</th>
</tr><tr>
    <th>WSTK</th>
    <th>800 Dev Kit</th>
</tr><tr>
    <td>RST</td>
    <td>Press</td>
    <td colspan="2">Resets the firmware of an application (like losing power). All volatile memory will be cleared.</td>
</tr><tr>
    <td>BTN0</td>
    <td>Keypress</td>
    <td colspan="2">Switch on/off endpoint 1</td>
</tr><tr>
    <td rowspan="2">BTN1</td>
    <td>Press</td>
    <td colspan="2">
        Enter "learn mode" (sending node info frame) to add/remove the device.<br>
        Removing the device from a network will reset it.
    </td>
</tr><tr>
    <td>Hold for at least 5 seconds and release</td>
    <td colspan="2">Perform a reset to factory default operation of the device, and a Device Reset Locally Notification Command is sent via Lifeline.</td>
</tr><tr>
    <td>BTN2</td>
    <td>Keypress</td>
    <td>
      Dimming or switch on/off endpoint 1.
      Pressing push-button turns light on/off and holding push-button
      performs dimming of light (toggle up/down)
    </td>
    <td></td>
</tr><tr>
    <td>BTN3</td>
    <td>Keypress</td>
    <td>
      <p>
        Toggles the transmission of an "Overload detected" notification.
        The first transmission, when enabled, will always be the first in the following list.
      </p>
      <p>The notifications will be transmitted in the following pattern:</p>
      <ol>
        <li>Notification from endpoint 1: Overload detected</li>
        <li>Notification from endpoint 1: No event</li>
        <li>Notification from endpoint 2: Overload detected</li>
        <li>Notification from endpoint 2: No event</li>
      </ol>
      <p>One notification will be transmitted every 30 seconds.</p>
    </td>
    <td></td>
</tr>
</table>

<table>
<tr>
    <th rowspan="2">LED</th>
    <th colspan="2">Description</th>
</tr><tr>
    <th>WSTK</th>
    <th>800 Dev Kit</th>
</tr><tr>
    <td>LED0</td>
    <td colspan="2">Endpoint 1 (switch on/off)</td>
</tr><tr>
    <td>LED1</td>
    <td>
      Blinks with 1 Hz when learn mode is active.
      Used for Indicator Command Class.
    </td>
    <td>Endpoint 2 (dimmer)</td>
</tr><tr>
    <td>RGB</td>
    <td>Endpoint 2 (dimmer)</td>
    <td>
    </td>
</tr>
</table>

## Firmware Update

This section will describe backward compatibility when upgrading the Power Strip application from one SDK to a newer version. 

SDK 7.1x is the first SDK running on Z-Wave 700.
