# Serial API

The Serial Applications Programming Interface (Serial API) allows a host to communicate with a Z-Wave
chip. The host may be PC or a less powerful embedded host CPU, e.g., in a remote control or in a
gateway device. Depending on the chip family, the Serial API may be accessed via RS-232 or USB
physical interfaces.

There are 2 available versions of SerialAPI:

 - SerialAPI Controller
 - SerialAPI End Device

The following host-based sample applications are available in the SDK:

- Z/IP Gateway &ndash; Gateway application using Serial API features of the bridge controller API
- PC Controller &ndash; Demonstrates Serial API features of the bridge controller API

The host-based sample applications are described in the respective SDK overview documents.

The Serial API leverages the Z-Wave Protocol API. The Serial API introduces additional messages related
to inter-host communications.