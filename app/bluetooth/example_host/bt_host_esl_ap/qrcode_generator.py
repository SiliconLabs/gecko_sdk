#!/usr/bin/env python3
"""
QR code generator for ESL demo
"""

# Copyright 2023 Silicon Laboratories Inc. www.silabs.com
#
# SPDX-License-Identifier: Zlib
#
# The licensor of this software is Silicon Laboratories Inc.
#
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

from image_converter import XbmConverter, Image
from intelhex import IntelHex
import subprocess
import argparse
import logging
import qrcode
import bincopy
import sys
import os
import re
import io

QR_CODE_VERSION = 3 # 29x29 matrix
QR_CODE_BORDER = 4 # default is 4, which is the minimum in the specification
WSTK_DISPLAY_H = 128
WSTK_DISPLAY_W = 128
MAGIC_CONST = b'.qrc_ph_pic_data'

# Add commander path to system environment variables
try:
    os.environ['PATH'] += os.pathsep + os.environ['PATH_SCMD']
except KeyError:
    # Commander path has to be set up manually
    pass

class Commander:
    """ Simplicity Commander helper """
    def __init__(self, serialno=None, ip=None):
        self.conn_args = []
        if serialno is not None:
            self.conn_args += ['--serialno', serialno]
        if ip is not None:
            self.conn_args += ['--ip', ip]

    def call(self, args):
        try:
            return subprocess.run(["commander"] + args + self.conn_args,
                                    stdout=subprocess.PIPE,
                                    shell=False,
                                    check=True).stdout.decode()
        except FileNotFoundError:
            print("Simplicity Commander not found.")
            print("Make sure that the Simplicity Commander is installed and the PATH environment variable is set up correctly.")
            sys.exit(1)
        except subprocess.CalledProcessError as error:
            print("Simplicity Commander failed.")
            print(error.stdout.decode())
            sys.exit(1)

    def get_board_uid(self):
        uid = ''
        # Executing the Commander call and store the console output
        commander_response = self.call(['device', 'info'])
        # Look for the line "Unique ID      : <MAC address>"
        uid_info = re.search(r'Unique ID\s*:\s*(.*)\s*.*', commander_response)
        if uid_info:
            # Keep the MAC address, chopping the dummy values from the center
            uid = uid_info.group(1)[0:2] + ':' \
                    + uid_info.group(1)[2:4] + ':' \
                    + uid_info.group(1)[4:6] + ':' \
                    + uid_info.group(1)[10:12] + ':' \
                    + uid_info.group(1)[12:14] + ':' \
                    + uid_info.group(1)[14:16]
        return uid

    def flash_board(self, filename):
        commander_response = self.call(['flash', filename])
        print(commander_response)

def generate_qrcode(data, height, width):
    # QR code is a square we take the smaller
    pixel = min(height, width)
    # Creating box_size: This parameter controls how many pixels each "box" of the QR code is
    box_size = int(pixel / 37)
    qr = qrcode.QRCode(QR_CODE_VERSION,
                       qrcode.constants.ERROR_CORRECT_M,
                       box_size,
                       QR_CODE_BORDER)
    # Adding data to the instance 'qr'
    qr.add_data(data)
    # Handle overflow exception
    try:
        qr.make(fit = False)
    except qrcode.exceptions.DataOverflowError as err:
        print(err)
        sys.exit(1)
    # Create black and white QR code image
    img = qr.make_image(fill_color = 'black',
                        back_color = 'white')
    qr_width, qr_height = img.size
    print(f"Generated QR code size: {qr_width}x{qr_height}")
    print(f"Scaling it to: {width}x{height}")
    # Adding border
    top_border = round((height - qr_height) / 2)
    left_border = round((width - qr_width) / 2)
    result = Image.new('RGB', (width, height), XbmConverter.xbm_white)
    result.paste(img, (left_border, top_border))
    # Create bytes from image
    img_xbm = XbmConverter(result)
    xbm = img_xbm.convert()
    return xbm

def merge_qr_hex(qrcode, ihex, sa, hex_file_out="merged.hex"):
    qrhex = IntelHex()
    qrhex.puts(sa, qrcode)
    ihex.merge(qrhex, overlap='replace')
    ihex.write_hex_file(hex_file_out)
    print(f"Created new hex file: {hex_file_out}")
    return hex_file_out

def find_magic_in_hex(ihex):
    found = ihex.find(MAGIC_CONST)
    offset = found+len(MAGIC_CONST)
    size = ihex[offset]+ihex[offset+1]*256
    addr = ihex[(offset+2)]+ihex[(offset+3)]*256+ihex[(offset+4)]*(256**2)+ihex[(offset+5)]*(256**3)
    print("Size of original picture data: ", size)
    print("Start address: ", hex(addr))
    return addr, size

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("hex", help="The output file of the ESL Tag project or pre-built demo in Intel HEX (.hex) or Motorola S-Records (.s37) format.")
    parser.add_argument("-s", "--serialno", help="J-Link serial number of the WSTK")
    parser.add_argument("--ip", help="IP address of the WSTK")
    parser.add_argument("-w", "--width", type=int, help="width of the desired image in pixel", default=WSTK_DISPLAY_W)
    parser.add_argument("-he", "--height", type=int, help="height of the desired image in pixel", default=WSTK_DISPLAY_H)
    args = parser.parse_args()

    commander = Commander(args.serialno, args.ip)

    # 1) Check if file is in a known format: Intel HEX (.hex), or Motorola S-Records (.s37) 
    ihex = None
    try:
        f = bincopy.BinFile(args.hex)
    except IOError as e:
        print(e)
        sys.exit(e.errno)
    except bincopy.UnsupportedFileFormatError:
        print("Can't open file:", args.hex, "due to unknown format.")
        sys.exit(1)
    else:
        try:
            ihex = IntelHex(io.StringIO(f.as_ihex()))
        except:
            print("IntelHex import error.")
            sys.exit(1)

    # 2) Read MAC address and create QR code data
    uid = commander.get_board_uid()
    print('UID: ' + uid)
    data = "connect " + uid

    # 3) Generate QR code: the generated data should be a binary which can be flashed to NVM
    bin_image = generate_qrcode(data, args.height, args.width)

    # 4) Find the magic constant with commander in the given hex file
    start_addr, size = find_magic_in_hex(ihex)

    # 5) Check if the space is enough for the QR code
    if size < len(bin_image):
        print("There is not enough memory to flash the QR code")
        sys.exit(1)

    # 6) Create the new hex file and flash it on the device
 
    merged_hex = merge_qr_hex(bin_image, ihex, start_addr)
    commander.flash_board(merged_hex)

if __name__ == "__main__":
    main()
