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

## Known Issues

### OTW Update

The following update paths for Serial API Controller are not possible using the
pre-built binaries because the defines `ZAF_CONFIG_GENERIC_TYPE` and
`ZAF_CONFIG_SPECIFIC_TYPE` differ across these versions:

- 7.19 or lower to 7.20
- 7.20 to 7.21 or higher

However, it is possible to create a custom firmware that is compatible with
earlier versions of the application by building the application manually after
editing `application_properties_config.h`.

If you want to update a device running the pre-built 7.19 or lower version
firmware to 7.20,
change both `PRODUCT_ID_GENERIC_TYPE` and `PRODUCT_ID_SPECIFIC_TYPE` to
`0`.

If you want to update a device running the pre-built 7.20 version firmware
to 7.21 or higher,
remove the following conditional block from the file:

```
#if (ZAF_CONFIG_GENERIC_TYPE == GENERIC_TYPE_STATIC_CONTROLLER && \
     ZAF_CONFIG_SPECIFIC_TYPE == SPECIFIC_TYPE_PC_CONTROLLER)
(...)
#endif
```

Changing these values will only affect the Product ID, stored in the struct
`sl_app_properties`.
The application will still report the values specified in the defines
`ZAF_CONFIG_GENERIC_TYPE` and `ZAF_CONFIG_SPECIFIC_TYPE` in its
Node Information Frame.\
Note that these values can  be changed on the fly using the Serial API command `SERIAL_API_APPL_NODE_INFORMATION`.
