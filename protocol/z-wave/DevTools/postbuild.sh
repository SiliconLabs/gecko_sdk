#!/bin/bash

echo "Combine bootloader and FW into one file"

BOOTLOADER=$1
APPLICATION=$2
# Overwrite the application by appending the bootloader to it
commander convert $BOOTLOADER $APPLICATION --outfile $APPLICATION