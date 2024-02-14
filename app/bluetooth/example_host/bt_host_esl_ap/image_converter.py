#!/usr/bin/env python3
"""
Image converter class and CLI utility for Silabs' ESLs
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

import argparse
import numpy as np
from operator import mul
from ap_logger import getLogger
from PIL import Image, ImageOps, ImageDraw, ImageFont
import io
import os
from sys import exit as sys_exit

# default configuration
CONF_EPD_DISPLAY_SIZE = (416, 240)
CONF_WSTK_DISPLAY_SIZE = (128, 128)
CONF_DEFAULT_FONTSIZE = 9
CONF_FIT_CENTERING = (0.5, 0.5)
CONF_ROTATION = None


class XbmConverter:
    """XBM converter class"""

    # define display color tuples
    xbm_white = (255, 255, 255)
    xbm_black = (0, 0, 0)
    xbm_grey25 = (63, 63, 63)
    xbm_grey50 = (127, 127, 127)
    xbm_grey75 = (191, 191, 191)
    xbm_red = (220, 19, 25)  # Silicon Lab's red
    xbm_rose75 = (220, 70, 75)
    xbm_rose50 = (220, 120, 123)
    xbm_rose25 = (220, 170, 172)
    xbm_cyan = (0, 200, 200)
    xbm_magenta = (200, 0, 200)
    xbm_yellow = (200, 200, 0)

    def __init__(self, image=None):
        self.image = image
        self.raw_image = b""
        self.image_out = None
        self.file_name = "AP_image"
        self.DISPLAY_WSTK_PALETTE = XbmConverter.xbm_white + XbmConverter.xbm_black
        self.DISPLAY_EPD_PALETTE = (
            XbmConverter.xbm_white + XbmConverter.xbm_black + XbmConverter.xbm_red
        )
        self.DISPLAY_EPD_4_PALETTE = (
            XbmConverter.xbm_white
            + XbmConverter.xbm_black
            + XbmConverter.xbm_yellow
            + XbmConverter.xbm_red
        )
        self.DISPLAY_CMYK_PALETTE = (
            XbmConverter.xbm_white
            + XbmConverter.xbm_cyan
            + XbmConverter.xbm_magenta
            + XbmConverter.xbm_yellow
            + XbmConverter.xbm_black
        )

    # Logger
    @property
    def log(self):
        return getLogger("IMG")

    def open(self, img_path):
        """Open image file"""
        try:
            self.image = Image.open(img_path, "r").convert(mode="RGBA")
            self.file_name = img_path
        except:
            self.log.error("Cannot open image file: %s!", img_path)
            self.image = None

    def open_frombytes(self, img_bytes):
        """Open image file"""
        try:
            self.image = Image.open(io.BytesIO(img_bytes)).convert(mode="RGBA")
        except:
            self.log.error("Cannot create image from bytes!")
            self.image = None

    def save_to_xbm(self, out):
        """Convert image to xbm format and save it to an output file"""
        try:
            filename = out.split(".")[0] + "_esl.xbm"
            path, file = os.path.split(filename)
            self.image_out.save(filename, format="xbm")
            self.log.info(
                "Image saved to XBM format as '%s' under path '%s'.", file, path
            )
        except AttributeError:
            self.log.error("File saving to XBM failed!")

    def save_to_png(self, out):
        """Convert image to PNG format and save it to an output file"""
        try:
            filename = out.split(".")[0] + "_esl.png"
            path, file = os.path.split(filename)
            self.image.convert("RGBA").save(filename, format="png")
            self.log.info(
                "Image saved to PNG format as '%s' under path '%s'.", file, path
            )
        except AttributeError:
            self.log.error("File saving to PNG failed!")

    def save_to_raw(self, out):
        """Save raw output data to binary file"""
        try:
            filename = out.split(".")[0] + "_esl.bin"
            path, file = os.path.split(filename)
            with open(filename, "wb") as binary_file:
                # Write bytes to file
                binary_file.write(self.raw_image)
                self.log.info(
                    "Image saved in RAW binary format as '%s' under path '%s'.",
                    file,
                    path,
                )
        except:
            self.log.error("RAW file saving failed!")

    def reverse_bits(self, x):
        """Reversing MSB->LSB bit order of a bytes class object"""
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
        """Return byte stream of the pixels data"""
        pixels_unpadded = [0] * int(len(pixels) / 8)
        for x in range(len(pixels)):
            byte = int(x / 8)
            pixel_pos = 7 - x % 8
            if pixels[x] != 0:
                pixels_unpadded[byte] = pixels_unpadded[byte] | (1 << pixel_pos)

        return bytes(pixels_unpadded)

    def show(self):
        """Display the result image on computer's screen"""
        self.image.convert("RGB").show()

    def convert(
        self,
        display_size=CONF_WSTK_DISPLAY_SIZE,
        bw=True,
        bitflip=None,
        rotation=CONF_ROTATION,
        cropfit=False,
        fit_centering=CONF_FIT_CENTERING,
        label=None,
        fontsize=CONF_DEFAULT_FONTSIZE,
        write_raw=False,
    ):
        """Convert image to byte stream of adjacent frames with 1bit/pixel representation for each output color"""
        if bw:
            image_palette = self.DISPLAY_WSTK_PALETTE
            if display_size == CONF_WSTK_DISPLAY_SIZE and bitflip is None:
                bitflip = True  # only WSTK memory LCD needs bit flipping
        else:
            image_palette = self.DISPLAY_EPD_PALETTE
        # create the quantizer base object
        pal_image = Image.new("P", (1, len(image_palette) // 3))
        pal_image.putpalette(
            image_palette + image_palette[0:3] * (256 - int(len(image_palette) // 3))
        )

        # get a font
        fnt = ImageFont.truetype(
            "font.otf", int((fontsize * display_size[0]) / CONF_WSTK_DISPLAY_SIZE[0])
        )

        # check the image
        if self.image is None:
            return bytearray()

        if rotation is not None:
            self.image = self.image.transpose(rotation)

        # do some auto adjustment for normalized results
        display_image = Image.new("RGBA", self.image.size, image_palette[0:3])
        display_image = Image.alpha_composite(display_image, self.image)
        display_image = ImageOps.autocontrast(
            display_image.convert("RGB"), preserve_tone=True
        )

        if cropfit:
            display_image = ImageOps.fit(
                display_image,
                display_size,
                method=Image.LANCZOS,
                centering=fit_centering,
            )
        else:
            display_image.thumbnail(display_size, resample=Image.LANCZOS)

        display_image = ImageOps.pad(
            display_image, display_size, color=image_palette[0:3]
        )  # assume that image_palette[0:3] is white - change if it's not!
        try:
            display_image = display_image.quantize(palette=pal_image)
        except:
            self.log.error("Cannot quantize image!")
            return None
        color_count = len(display_image.getcolors())
        color_max_index = color_count - 1
        # get a drawing context
        if label is not None:
            dc = ImageDraw.Draw(display_image)
            dc.multiline_text(
                (5, 5),
                str(label),
                font=fnt,
                fill=1,
                stroke_width=3,
                stroke_fill=0,
                spacing=2,
            )
        self.image = display_image.copy()
        temp_palette = list(
            XbmConverter.xbm_black + XbmConverter.xbm_white * (color_max_index)
        )
        frames = []
        for i in range(color_max_index):

            temp_palette = temp_palette[-3:] + temp_palette[:-3]
            display_image.putpalette(temp_palette)
            frames.append(display_image.convert("1"))

        if not bw:
            image_size = tuple(map(mul, display_size, (1, color_max_index)))
        else:
            image_size = display_size

        self.image_out = Image.new(
            "RGB", image_size, image_palette[0:3]
        )  # assume that image_palette[0:3] is BG color - change if it's not!

        for i, frame in enumerate(frames):
            self.image_out.paste(frame, (0, i * frame.height))

        if display_size != CONF_WSTK_DISPLAY_SIZE or bw is not True:
            self.image_out = ImageOps.invert(self.image_out)

        self.image_out = self.image_out.convert("1")

        if bitflip:
            rawimage = self.reverse_bits(self.image_out.tobytes())
            self.image_out.frombytes(rawimage, decoder_name="raw")

        self.raw_image = self.pixel_list_to_bytes(list(self.image_out.getdata()))

        if write_raw:
            self.save_to_raw(self.file_name)

        return self.raw_image


class checked_range(object):
    def __init__(self, start, end):
        self.start = start
        self.end = end

    def __eq__(self, other):
        return self.start <= other <= self.end

    def __contains__(self, item):
        return self.__eq__(item)

    def __iter__(self):
        yield self

    def __repr__(self):
        return "[{0},{1}]".format(self.start, self.end)


def readable_file(path_str):
  if not os.path.isfile(path_str):
    raise argparse.ArgumentTypeError("'{0}' is not a valid file!".format(path_str))
  if os.access(path_str, os.R_OK):
    return path_str
  else:
    raise argparse.ArgumentTypeError("'{0}' is not a readable file!".format(prospective_dir))


def main():
    """Script entry point."""
    log = getLogger("CNV")
    parser = argparse.ArgumentParser(
        formatter_class=lambda prog: argparse.RawDescriptionHelpFormatter(
            prog, max_help_position=35
        ),
        description="""
Silicon Labs ESL Tag image converter utility (experimental).
Supports the most popular image formats as input images.
                                     """,
        epilog="""
    Notes:    To use space or backslash in the filename or other special characters, such as line break escape
              sequences in the text caption, please enclose these strings in quotes.
              The modifiers for rotation are mutually exclusive.
              Rotation and centering is done before the conversion.
              Centering values are effective only if fitting by cropping is also requested.

    Examples: %(prog)s ./img1.jpg 416 240 --h_center=0.6 --ccw --label=\"Line 1\\nLine 2\"
              Rotate image by 90 degree clockwise then convert to a 416x240 (WxH) display with two lines of label.

              %(prog)s "/user/home/path with space/img.jpg" 128 128 -bw --bitflip --cropfit
              Fits image to the output image ratio first by cropping, then convert to B&W for WSTK display with reversed bit order.
              """,
    )
    # Add positional arguments: file, width, height
    parser.add_argument(
        "imagefile_path",
        type=readable_file,
        help="Relative or full path to the selected image file. Use quotation marks if the path contains spaces.",
    )
    parser.add_argument(
        "width",
        metavar="<u16>",
        choices=checked_range(1, 8192),
        type=int,
        help="Width in pixels for the target display.",
    )
    parser.add_argument(
        "height",
        metavar="<u16>",
        choices=checked_range(1, 8192),
        type=int,
        help="Height in pixels for the target display.",
    )
    # Add optional arguments: image center coordinates, fontsize, label text, black and white conversion, bit order reversal option and fitting method
    parser.add_argument(
        "--h_center",
        "-hc",
        default=0.5,
        metavar="<float>",
        choices=checked_range(0.0, 1.0),
        type=float,
        help="Horizontal centering, effective only if --cropfit is not set.",
    )
    parser.add_argument(
        "--v_center",
        "-vc",
        default=0.5,
        metavar="<float>",
        choices=checked_range(0.0, 1.0),
        type=float,
        help="Horizontal centering, effective only if --cropfit is not set.",
    )
    parser.add_argument(
        "--fontsize",
        "-fs",
        metavar="<u8>",
        default=CONF_DEFAULT_FONTSIZE,
        choices=checked_range(6, 255),
        type=int,
        help="Font size for the optional label text.",
    )
    parser.add_argument(
        "--label",
        "-l",
        metavar="<str>",
        help="Caption to be written over the image. Use quotation marks if it includes spaces or line breaks.",
    )
    parser.add_argument(
        "--blackwhite",
        "-bw",
        action="store_true",
        help="Converts to black and white (default: B/W + red).",
    )
    parser.add_argument(
        "--bitflip",
        "-br",
        action="store_true",
        help="Do bit order reversal within the data bytes for e.g. WSTK B/W images.",
    )
    parser.add_argument(
        "--cropfit",
        "-c",
        action="store_true",
        help="Fit the image to the display proportions by cropping.",
    )
    # Add mutually exclusive optional arguments for rotation
    parser_image_rotator_group = parser.add_mutually_exclusive_group()
    parser_image_rotator_group.add_argument(
        "--cw",
        "-rr",
        action="store_const",
        const=Image.ROTATE_270,
        dest="rotation",
        help="Clockwise (right) rotation.",
    )
    parser_image_rotator_group.add_argument(
        "--ccw",
        "-rl",
        action="store_const",
        const=Image.ROTATE_90,
        dest="rotation",
        help="Counter clockwise (left) rotation.",
    )
    parser_image_rotator_group.add_argument(
        "--flip",
        "-f",
        action="store_const",
        const=Image.ROTATE_180,
        dest="rotation",
        help="Turn the image upside down.",
    )

    args = parser.parse_args()
    img = XbmConverter()
    # Open image file
    file = args.imagefile_path # create a shorter alias
    img.open(file)
    # Convert into a byte stream of adjacent frames with 1bit/pixel representation for each color
    log.info("Converting image: " + file)
    print(args)
    xbm = img.convert(
        (args.width, args.height),
        args.blackwhite,
        args.bitflip,
        args.rotation,
        args.cropfit,
        (args.h_center, args.v_center),
        args.label,
        args.fontsize,
        False,
    )
    log.info("The conversion is done. Now save in different formats:")
    img.save_to_png(file)
    img.save_to_xbm(file)
    img.save_to_raw(file)
    log.info("Show resulting image on the screen...")
    img.show()


if __name__ == "__main__":
    main()
