# Wall Controller

The Z-Wave certified Wall Controller application shows a push-button switch panel implementation to control devices in the Z-Wave network from push buttons (physical or virtual) on a device that is meant to be mounted on a wall. Examples include scene and zone controller and wall-mounted AV controllers.

The Wall controller application implements a wall-mounted switch that has three individually configurable buttons. Each button has support for on/off and dimming.

The Wall Controller application is based on:

| <!-- -->                | <!-- -->                                                                                                          |
| ----------------------- | ----------------------------------------------------------------------------------------------------------------- |
| Role Type               | Always On End device (AOS)                                                                                        |
| Supporting Device Type  | Actuator                                                                                                          |
| Device Type             | Central Scene                                                                                                     |
| Generic Type            | Wall Controller                                                                                                   |
| Specific Type           | Not Used                                                                                                          |
| Requested security keys | S0, S2_UNAUTHENTICATED, and S2_AUTHENTICATED<br>The Wall Controller features do not depend on the security level. |

## Supported Command Classes

| Command Class             | Version | Required Security Class        |
| ------------------------- |:-------:| ------------------------------ |
| Association               |    2    | Highest granted Security Class |
| Association Group Info    |    3    | Highest granted Security Class |
| Central Scene             |    3    | Highest granted Security Class |
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

Use case:

The wall controller's three buttons are configurable to control nodes. Each button action is sent over the Lifeline as scene actions.

## Basic Command Class mapping

Basic Command Class is not mapped to any of the supported command classes.

## Association Groups

The following association groups are available for Z-Wave and Z-Wave Long Range respectively.

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
            <li>Central Scene: triggered by button press.</li>
            <li>Indicator Report: Triggered when LED1 changes state.</li>
        </ul>
    </td>
</tr><tr>
    <td>2</td>
    <td rowspan="2">BTN0</td>
    <td>Y</td>
    <td>Basic Set Command</td>
</tr><tr>
    <td>3</td>
    <td>Y</td>
    <td>Switch Multilevel CC</td>
</tr><tr>
    <td>4</td>
    <td rowspan="2">BTN2</td>
    <td>Y</td>
    <td>Basic Set Command</td>
</tr><tr>
    <td>5</td>
    <td>Y</td>
    <td>Switch Multilevel CC</td>
</tr><tr>
    <td>6</td>
    <td rowspan="2">BTN3</td>
    <td>Y</td>
    <td>Basic Set Command</td>
</tr><tr>
    <td>7</td>
    <td>Y</td>
    <td>Switch Multilevel CC</td>
</tr>
</table>

X: For Z-Wave node count is equal to 5 and for Z-Wave Long Range it is 1.

Y: For Z-Wave node count is equal to 5 and for Z-Wave Long Range it is 0.

## Usage of Buttons and LED Status

The following buttons and LEDs are used.

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
    <td rowspan="3">BTN0</td>
    <td>Press</td>
    <td><ul>
        <li>Lifeline with Central Scene Key Attribute "Key Pressed 1 Time"</li>
        <li>Trigger association group 2: Basic Set</li>
    </ul></td>
</tr><tr>
    <td>Hold start</td>
    <td><ul>
        <li>Lifeline with Central Scene Key Attribute "Key Held Down"</li>
        <li>Trigger association group 3: Multilevel Switch Start Level Change</li>
    </ul></td>
</tr><tr>
    <td>Hold release</td>
    <td><ul>
        <li>Lifeline with Central Scene Key Attribute "Key Released"</li>
        <li>Trigger association group 3: Multilevel Switch Stop Level Change</li>
    </ul></td>
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
</tr><tr>
    <td rowspan="3">BTN2</td>
    <td>Press</td>
    <td><ul>
        <li>Lifeline with Central Scene Key Attribute "Key Pressed 1 Time"</li>
        <li>Trigger association group 4: Basic Set</li>
    </ul></td>
</tr><tr>
    <td>Hold start</td>
    <td><ul>
        <li>Lifeline with Central Scene Key Attribute "Key Held Down"</li>
        <li>Trigger association group 5: Multilevel Switch Start Level Change</li>
    </ul></td>
</tr><tr>
    <td>Hold release</td>
    <td><ul>
        <li>Lifeline with Central Scene Key Attribute "Key Released"</li>
        <li>Trigger association group 5: Multilevel Switch Stop Level Change</li>
    </ul></td>
</tr><tr>
    <td rowspan="3">BTN3</td>
    <td>Press</td>
    <td><ul>
        <li>Lifeline with Central Scene Key Attribute "Key Pressed 1 Time"</li>
        <li>Trigger association group 6: Basic Set</li>
    </ul></td>
</tr><tr>
    <td>Hold start</td>
    <td><ul>
        <li>Lifeline with Central Scene Key Attribute "Key Held Down"</li>
        <li>Trigger association group 7: Multilevel Switch Start Level Change</li>
    </ul></td>
</tr><tr>
    <td>Hold release</td>
    <td><ul>
        <li>Lifeline with Central Scene Key Attribute "Key Released"</li>
        <li>Trigger association group 7: Multilevel Switch Stop Level Change</li>
    </ul></td>
</tr>
</table>

<table>
<tr>
    <th>LED</th>
    <th>Description</th>
</tr><tr>
    <td>LED1</td>
    <td>
        Blinks with 1 Hz when learn mode is active.
        Used for Indicator Command Class.
    </td>
</tr>
</table>

## Firmware Update

This section will describe backward compatibility when upgrading the Wall Controller application from one SDK to a newer version.

SDK 7.1x is the first SDK running on Z-Wave 700.
