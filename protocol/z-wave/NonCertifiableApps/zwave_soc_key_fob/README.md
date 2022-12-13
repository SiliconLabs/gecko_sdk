# Key Fob Application

The Key Fob application is an example of how a simple portable controller can be implemented. The Key Fob can include and exclude Z-Wave nodes (not Z-Wave Long Range) to its network and do simple control (Basic On/OFF) of one group of nodes. It supports non-secure, S0 and S2-unauthenticated encryption. NOTICE: The current version of the Key Fob cannot be Z-Wave certified.

The Key Fob can furthermore be included in a network as a secondary controller.

## Supported Command Classes

Key Fob implements mandatory and some optional command classes. The table below lists the supported Command Classes, their version, and their required Security class, if any.

| Command Class         | Version | Required Security Class        |
| :-------------------- | :-----: | :----------------------------- |
| Battery               |    2    | Highest granted Security Class |
| Manufacturer Specific |    2    | Highest Granted Security Class |
| Security              |    1    | None                           |
| Security 2            |    1    | None                           |
| Supervision           |    1    | None                           |
| Transport Service     |    2    | None                           |
| Version               |    3    | Highest granted Security Class |
| Z-Wave Plus Info      |    2    | None                           |

The Key Fob does not yet implement the Association Command Class but groups are locally maintained by the application.

## Controlling Command Class

The Basic Command Class is supported as a controlling command class. Basic Set (On/Off) commands can be sent to associated end devices by pressing buttons on the development board.

## Usage of Buttons and LED Status

<table>
<tr>
    <th>Button</th>
    <th>Action</th>
    <th>Description</th>
</tr><tr>
    <td rowspan="3">BTN0</td>
    <td>Short press</td>
    <td>ADD an end device to the KeyFobs network &ndash; LED1 blinks while inclusion is in progress.</td>
</tr><tr>
    <td>Hold (1 sec)</td>
    <td>REMOVE end device from the KeyFobs network - LED1 blinks while exclusion is in progress.</td>
</tr><tr>
    <td>Long Press (&gt;5 sec)</td>
    <td>Reset all settings to default.</td>
</tr><tr>
    <td rowspan="2">BTN1</td>
    <td>Short press</td>
    <td>Transmit BASIC SET ON to associated devices - LED1 is on until transfer completes or is timed out.</td>
</tr><tr>
    <td>Hold (1 sec)</td>
    <td>
        Associate an end device to the BASIC SET Group - LED1 blinks and LED0 is ON while in progress.<br>
        Press learn-mode button on the end device so it gets associated. (Press once more to deactivate learn-mode)
    </td>
</tr>
</tr><tr>
    <td rowspan="2">BTN2</td>
    <td>Short press</td>
    <td>Transmit BASIC SET OFF to associated devices &ndash; LED2 on until transfer completes or is timed out.</td>
</tr><tr>
    <td>Hold (1 sec)</td>
    <td>
        Remove device from BASIC SET Group. Group - LED1 blinks and LED2 is ON while in progress. <br>
        Press learn-mode button on the end device so it is removed. (Press once more to deactivate learn-mode
    </td>
</tr><tr>
    <td rowspan="2">BTN3</td>
    <td>Short press</td>
    <td>Enter Network Wide Inclusion (NWI) learn-mode so the KeyFob can be included as a secondary controller &ndash; LED3 is on while in NWI.</td>
</tr><tr>
    <td>Hold (1 sec)</td>
    <td>Enter Network Wide Exclusion (NWE) learn-mode so the KeyFob can be excluded from being a secondary controller.</td>
</tr>
</table>

For example, to control Switch On/Off end devices using a Key Fob controller. Follow the steps below for each end device.

1. Include the end device: Press **BTN0** on the **Key Fob**, then press **BTN1** on the **Switch On/Off**. LED1 will blink until inclusion has finished.
2. Associate the end device to the BASIC SET group: Hold **BTN1** on the **Key Fob**, then press **BTN1** on the **Switch On/Off**.  Press **BTN1** once more on the **Switch On/Off** to take it out of learn mode.
3. Control LED0 on the Switch On/Off: Press **BTN1** or **BTN2** on the **Key Fob** to turn LED0 On or Off.

## Firmware Update

Currently the Key Fob application does not support OTA firmware update
