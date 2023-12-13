# Copyright: 2023 Silicon Laboratories Inc. www.silabs.com
# License: MSLA
#
# The licensor of this software is Silicon Laboratories Inc. Your use of this
# software is governed by the terms of the Silicon Labs Master Software License
# Agreement (MSLA) available at
# https://www.silabs.com/about-us/legal/master-software-license-agreement
# By installing, copying or otherwise using this software, you agree to the
# terms of the MSLA.
#
This folder contains sample keys for signing and encrypting firmware images (GBL files).

It is important that the sample keys are not used for production. Each vendor should have 
his own set of keys. New kyes can be generated with simplicity commander by running the following
commands on the command line.

Creating new signing keys:
commander gbl keygen --type ecc-p256 -o manufacturer_sign.key

Creating new encryption keys:
commander gbl keygen --type aes-ccm -o manufacturer_encrypt.key

For OTA upgrade to work in a product the token file must be flashed to the device after
1) the bootloader has been flashed
2) the application has been flashed

commander flash --tokengroup znet --tokenfile manufacturer_encrypt.key --tokenfile manufacturer_sign.key-tokens.txt 

