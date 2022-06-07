#SE Manager Attestation
This example uses the SE Manager API to fetch attestation tokens on the supported Series 2 device.
The example also contains code that demonstrates how the tokens can be parsed and printed in a human-readable format.
Parsing and printing of tokens on the actual device might not be a strictly typical use case, but it is nevertheless included in order to showcase the structure and capabilities of the supported attestation tokens.

An attestation token is a token that contains cryptographically signed claims about the device.
In other words, it provides a way to securely attest certain device information, such as the serial number, security configuration and other information about the state of the device.
An attestation token provided by the SE Manager API is a COSE_Sign1 structure that encapsulates the signed CBOR Web Token containing the claims.

The example redirects standard I/O to the virtual serial port (VCOM) of the kit. By default, the serial port setting is 115200 bps and 8-N-1 configuration.

The example has been instrumented with code to count the number of clock cycles spent in different operations. The results are printed on the VCOM serial port console. This feature can be disabled by defining SE_MANAGER_PRINT=0 (default is 1) in the IDE setting (Preprocessor->Defined symbols).

##SE Manager API
The following SE Manager APIs are used in this example:

sl_se_init    
sl_se_deinit   
sl_se_init_command_context   
sl_se_deinit_command_context   
sl_se_get_random   
sl_se_attestation_get_psa_iat_token   
sl_se_attestation_get_config_token 

##Getting Started   
Upgrade the kit’s firmware to the latest version (see Adapter Firmware under General Device Information in the Simplicity Studio 5 User's Guide).   
Upgrade the device’s SE firmware to the latest version (see Secure Firmware under General Device Information in the Simplicity Studio 5 User's Guide).   
Open any terminal program and connect to the kit’s VCOM port.  
Create this platform example project in the Simplicity IDE (see Examples in the Simplicity Studio 5 User's Guide, check Platform() checkbox to browse the platform examples).      
Build the example and download it to the kit (see Simple Build and Flash Programmer in the Simplicity Studio 5 User's Guide).    
Run the example and the console should display the process steps of this example.      

##Additional Information    
###Resources
[SE Manager API](https://docs.silabs.com/gecko-platform/latest/service/api/group-sl-se-manager)
