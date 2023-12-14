#!/usr/bin/env python3
"""
Image converter.
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

import numpy as np
from operator import mul
from ap_logger import getLogger
from PIL import Image, ImageOps, ImageDraw, ImageFont
import io

# default configuration
CONF_EPD_DISPLAY_SIZE = (416,240)
CONF_WSTK_DISPLAY_SIZE = (128,128)
CONF_DEFAULT_FONTSIZE = 9
CONF_FIT_CENTERING = (0.5, 0.5)
CONF_ROTATION = None

class XbmConverter():
    """ XBM converter class """

    # define display color tuples
    xbm_white = (255,255,255)
    xbm_black = (0,0,0)
    xbm_grey25 = (63,63,63)
    xbm_grey50 = (127,127,127)
    xbm_grey75 = (191,191,191)
    xbm_red = (220,19,25) # Silicon Lab's red
    xbm_rose75 = (220,70,75)
    xbm_rose50 = (220,120,123)
    xbm_rose25 = (220,170,172)
    xbm_yellow = (200,200,0)

    def __init__(self, image=None):
        self.image = image
        self.DISPLAY_WSTK_PALETTE = (XbmConverter.xbm_white + XbmConverter.xbm_black)
        self.DISPLAY_EPD_PALETTE = (XbmConverter.xbm_white + XbmConverter.xbm_black + XbmConverter.xbm_red)

    # Logger
    @property
    def log(self):
        return getLogger("IMG")

    def open(self, img_path):
        """ Open image file """
        try:
            self.image = Image.open(img_path, "r").convert(mode='RGB')
        except:
            self.log.error("Cannot open image file: %s!", img_path)
            self.image = None
    
    def open_frombytes(self, img_bytes):
        """ Open image file """
        try:
            self.image = Image.open(io.BytesIO(img_bytes)).convert(mode='RGB')
        except:
            self.log.error("Cannot open image file: %s!", img_bytes)
            self.image = None

    def save_to_xbm(self, out):
        """ Covert image to xbm format and save it to an output file """
        try:
            self.image.convert('1').save(out, format='xbm')
        except AttributeError:
            self.log.error("File conversion failed!")

    def reverse_bits(self, x):
      """ Reversing MSB->LSB bit order of a bytes class object """
      x = np.frombuffer(x, dtype=np.uint8)
      bits_num = x.dtype.itemsize * 8
      # because bitwise operations may change number of bits in numbers
      one_array = np.array([1], x.dtype)
      # switch bits in-place
      for i in range(int(bits_num / 2)):
        right_bit_mask = (one_array << i)[0]
        left_bit = (x & right_bit_mask) << (bits_num - 1 - i * 2)
        left_bit_mask = (one_array << (bits_num - 1 - i))[0]
        right_bit = (x & left_bit_mask) >> (bits_num - 1 - i * 2)
        moved_bits_mask = left_bit_mask | right_bit_mask
        x = x & (~moved_bits_mask) | left_bit | right_bit
      return x.tobytes()

    def pixel_list_to_bytes(self, pixels):
        pixels_unpadded = [0] * int(len(pixels) / 8)
        for x in range(len(pixels)):
            byte = int(x / 8)
            pixel_pos = 7 - x % 8
            if pixels[x] != 0:
                pixels_unpadded[byte] = pixels_unpadded[byte] | (1 << pixel_pos)

        return bytes(pixels_unpadded)
    
    def convert(self, display_size=CONF_WSTK_DISPLAY_SIZE, bw=True, bitflip=True, rotation=CONF_ROTATION, cropfit=False, fit_centering=CONF_FIT_CENTERING, label=None, fontsize=CONF_DEFAULT_FONTSIZE, write_raw=False):
        """ Convert image to xbm and return with bytearray datatype """
        if bw:
            image_palette = self.DISPLAY_WSTK_PALETTE
            if display_size != CONF_WSTK_DISPLAY_SIZE:
                bitflip = False # only WSTK memory LCD needs bit flipping
        else:
            image_palette = self.DISPLAY_EPD_PALETTE
            bitflip = False
        # create the quantizer base object
        pal_image = Image.new("P", (1,1))
        pal_image.putpalette(image_palette + XbmConverter.xbm_black*(256 - int(len(image_palette)/3)))

        # get a font
        fnt = ImageFont.truetype("font.otf", int((fontsize * display_size[0]) / CONF_WSTK_DISPLAY_SIZE[0]))

        # check the image
        if self.image is None:
            return bytearray()

        if rotation is not None:
            self.image = self.image.transpose(rotation)

        # do some auto adjustment for normalized results
        display_image = ImageOps.autocontrast(self.image, preserve_tone=True)

        if cropfit:
            display_image = ImageOps.fit(display_image, display_size, method=Image.LANCZOS, centering=fit_centering)
        else:
            display_image.thumbnail(display_size, resample=Image.LANCZOS)
        
        display_image = ImageOps.pad(display_image, display_size, color=XbmConverter.xbm_white)
        try:
            display_image = display_image.quantize(palette=pal_image)
        except:
            pass

        # get a drawing context
        if label is not None:
            dc = ImageDraw.Draw(display_image)
            dc.multiline_text((5, 5), str(label), font=fnt, fill=1, stroke_width=3, stroke_fill=0, spacing=2)

        black_pixels = display_image.remap_palette([0,1,0]).convert('1')
        red_pixels = display_image.remap_palette([0,0,2]).convert('1')
        image_size = display_size

        if not(bw):
            image_size = tuple(map(mul, display_size, (1,2)))

        image_out = Image.new('RGB', image_size, "white") # would be better to use the display color
        image_out.paste(black_pixels, (0,0))
        image_out.paste(red_pixels, (0, black_pixels.height))

        if display_size != CONF_WSTK_DISPLAY_SIZE or bw is not True:
            image_out = ImageOps.invert(image_out)

        image_out = image_out.convert('1')

        if bitflip:
            rawimage = self.reverse_bits(image_out.tobytes())
            image_out.frombytes(rawimage, decoder_name='raw')

        if write_raw:
            with open("image.raw", "wb") as binary_file:
                # Write bytes to file
                binary_file.write(image_out.tobytes())

        return self.pixel_list_to_bytes(list(image_out.getdata()))

# Example usage:
# img = XbmConverter()
# # Open image file
# img.open("imagefile_path")
# # Convert to XBM and load into a variable
# xbm = img.convert()
