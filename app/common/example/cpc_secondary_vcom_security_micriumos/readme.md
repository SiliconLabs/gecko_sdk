# CPC Secondary VCOM

This sample application demonstrates how to open CPC user endpoints, and perform read and write operations.
The application receives data on user endpoints and echos it back.

A python script, **cpc_interactive_client.py**, can be used to simulate a host application.

## Installation and Use

Once the CPC secondary application is built and installed on the secondary, the CPC daemon and library can
be installed on the host device from the [Github repository](https://github.com/SiliconLabs/cpc-daemon).

Once the applications are installed, the secondary can be connected via the VCOM port to the host,
using a USB cable.

The sample application on the secondary will open two user endpoints, SL_CPC_ENDPOINT_USER_ID_0 and SL_CPC_ENDPOINT_USER_ID_1.
The Python script **cpc_interactive_client.py**, located in the script folder on the host, can be used to open and close
endpoints, and write to and read data from them.

As security is enabled, the host and secondary must undergo a binding process before communication can begin.
This can be initiated from the host by passing the bind argument, ie.

`cpcd -c cpcd.conf --bind ecdh`

Once the devices are bound, an unbind request can be sent from the host with the unbind argument:

`cpcd -c cpcd.conf --unbind`

The secondary will only accept the unbind if BUTTON 0 on the WSTK is depressed when the request is received (see
`sl_cpc_security_on_unbind_request` in cpc_app.c).
