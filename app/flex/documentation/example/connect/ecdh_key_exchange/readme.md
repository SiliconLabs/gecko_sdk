# Connect: Elliptic-Curve Diffie–Hellman (ECDH) Key Agreement

## Introduction

The Connect stack supports sending encrypted messages using a pre-shared
(AES-128) key, which must be common for the whole network (hereinafter referred
to as *network key*). However, sometimes it is not feasible to pre-share the key
(for example burning the key to the device at production) or apply the key
manually (like typing in on some kind of console as the UART of the device).
Fortunately, it is possible to create a shared key (hereinafter referred to as
*shared key*) between two devices using the Diffie-Hellman algorithm while any
third party will not have the information to recover the key from the data sent
over the communication medium. This key however unique between every two
parties, so the current implementation will use this shared key to securely
distribute the network key to other devices. Note, that the method used in this
example does not protect against physical access to the devices or against
man-in-the-middle attack (MITM).

## Prerequisites

The provided method applicable for any Connect based application with any EFR32
device which supports Connect.

Further readings:

- [Connect Online Documentation](https://docs.silabs.com/connect-stack/latest/)
- [Connect Tutorial
  Series](https://community.silabs.com/s/article/connect-tutorial-series?language=en_US)

## Prepare the Application

Open the *Flex (Connect) - SoC ECDH Key Exchange* through Simplicity Studio
project wizard.

Compile the code and download to two (or optionally more) radio boards.

## Major Steps of Key Exchange

Although the same code runs on both (each) devices, one of the devices will act
as the *server* and the other(s) will be *client(s)* (if a device becomes a
*server* or a *client* depends on the executed CLI commands only).

- creating private/public key pair locally on the devices using ECC
- exporting the public part (X and Y points) as 32-byte arrays
- transferring the public part to another device
- creating a shared secret and shared key which can be used for secure data
  transfer
- the *server* sends the network key to the remote side securely using the
  shared key for encryption
- the *client* sets the network key on to securely communicate with the members
  of the network using the network key

## Testing the Application

If everything went well, a CLI interface should be available where the user can
issue the necessary commands.

### Example

Private and public keys are generated once, at startup and will be reused for
subsequent generations of shared keys.

Assume there are two devices a *server* (node ID will be `1`) and a client (node
ID will be `2`). Any of the devices can act as a *server* or act as a *client*.
First, issue the `leave` command on both parties - that's not mandatory
(especially for the first use when none of the addresses are commissioned), but
it makes sure that the network state is reset, no short addresses are assigned.

```text
leave
```

The next step is to choose a network key (this will be used as the common key in
the network for Connect encrypted messages). The key can be an arbitrary chosen
16-byte long value. `set-network-key` does not apply the key, it just stores in
a variable that will be set to the default value (all `0x00`s) on device
restart. This command must be executed on the *server*.

```text
set_network_key {00112233445566778899aabbccddeeff}
```

Choose a node ID for the *server*:

```text
set_node_id 1
```

Then choose a node ID for the *client*:

```text
set_node_id 2
```

Send the *server*'s public key for the *client*:

```text
send_public_key 2
```

Send the *client*'s public key for the *server*:

```text
send_public_key 1
```

At this point, all the necessary information is available on both sides to
create the shared secret (and the shared key), but no third party who may
observe the communication can recover the shared secret from the messages
exchanged.

Generate the shared key (issue the command on both *server* and *client*):

```text
generate_shared_key
```

For convenience there is a CLI command to show the shared key, to check whether
the same key generated on both sides:

```text
print_shared_key
```

To send the network key to the *client*, issue the `send-network-key` on the
*server*. The network key will be AES encrypted using the shared key. Connect's
message encryption will not be used here (security bit is not set) - since the
network key is not known at this point, so the message will be sent unencrypted
but the payload which transfers the key **will** be protected by encrypting the
payload with the previously generated shared key.

```text
send_network_key 2
```

To check whether the network keys match issue the following command on both
sides:

```text
print_network_key
```

To apply the network key (write the key to the non-volatile memory)
`apply_network_key` on the  *server* and the *client* as well.

```text
apply_network_key
```

To enable secure communication between the parties (using Connect's security
feature), issue the following command on both devices (if the parameter is `0`
the security feature will be turned off).

```text
set_security 1
```

From this point, secure communication is possible between the devices, the
command below will send the text `Hi!` from the *client* to the *server* but the
opposite direction should work as well.

```text
send_message 1 "Hi!"
```

### Notes

In normal use cases, it is not necessary to write the key on the *server* and
the *clients* at every restart. The usual workflow is that the network key is
stored in the non-volatile space of the *server* - in the code memory for
example and apply once (at first power up or initiated by a CLI command, etc.).
Although Connect's
[`emberSetSecurityKey()`](https://docs.silabs.com/connect-stack/latest/group-stack-info#ga90da760f71e7b50c5b0edbda6a97d2bc)
API function stores the network key in a non-volatile space, there is no API
call to read it back - thus the application must store the network key in a
retrievable form to be able to send it to the *clients*.

The security can be enabled at the beginning of the process above, because
enabling security for the messages is only makes sense for sent messages,
received messages are passed to the application if the network keys match (the
device can decode the message) or if the message is unencrypted. If the
encryption status is not checked by the application for the incoming messages
malicious devices can trick the devices in the network.

The above method for transferring the network key works with multiple *client*
devices, but in that the key sharing process must be repeated between the
*server* and every *client* one by one.

## Conclusion

Although the Connect does not support ECDH key exchange at the stack level, the
way to add ECDH key exchange is fairly easy and straightforward by adding
*Connect* -> *ECDH key exchange* component in the Universal Configurator.

## Report Bugs & Get Support

You are always encouraged and welcome to report any issues you found to us via
[Silicon Labs
Community](https://community.silabs.com/s/topic/0TO1M000000qHaKWAU/proprietary?language=en_US).
