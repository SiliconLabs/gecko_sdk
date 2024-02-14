# /*************************************************************************//**
#  * @file
#  * @brief Script to generate the PA dBm to Power Settings Mapping Table
#  * from a CSV file.
#  *****************************************************************************
#  * # License
#  * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
#  *****************************************************************************
#  *
#  * SPDX-License-Identifier: Zlib
#  *
#  * The licensor of this software is Silicon Laboratories Inc.
#  *
#  * This software is provided 'as-is', without any express or implied
#  * warranty. In no event will the authors be held liable for any damages
#  * arising from the use of this software.
#  *
#  * Permission is granted to anyone to use this software for any purpose,
#  * including commercial applications, and to alter it and redistribute it
#  * freely, subject to the following restrictions:
#  *
#  * 1. The origin of this software must not be misrepresented; you must not
#  *    claim that you wrote the original software. If you use this software
#  *    in a product, an acknowledgment in the product documentation would be
#  *    appreciated but is not required.
#  * 2. Altered source versions must be plainly marked as such, and must not be
#  *    misrepresented as being the original software.
#  * 3. This notice may not be removed or altered from any source distribution.
#  *
#  ****************************************************************************/

from __future__ import print_function
from __future__ import division
import sys
import argparse
import numpy
import csv
from pprint import pprint

API_INCREMENT_DEFAULT = 1


def decomment(csvfile):
    """
    Generator to strip comments from a CSV file.
    """
    for row in csvfile:
        raw = row.split("#")[0].strip()
        if raw:
            yield raw


def GenerateDbmToPowerSettingTableSUBGIG(
    File, minpwr, maxpwr, fem=False, increment=API_INCREMENT_DEFAULT
):
    """
    The code above does the following:
    1. Get CC, CF, SLICE, STRIPE data from the CSV file
    2. Generates the C array of the power settings
    3. Generates the C defines for the table
    4. Prints the C code to stdout
    """
    coarse, fine, slice, stripe = GetSUBGIGData(File)

    assert (
        coarse.__len__()
        == fine.__len__()
        == slice.__len__()
        == stripe.__len__()
        == (abs(maxpwr - minpwr) / increment) + 1
    ), "Expected number of power levels {} does not match actual number of power levels {}".format(
        abs(maxpwr - minpwr) / increment + 1, coarse.__len__()
    )

    powerSettings = []
    for cc, cf, stripe, slice in zip(coarse, fine, slice, stripe):
        powerSettings.append(hex((cf << 24) | (cc << 16) | (stripe << 8) | slice))
    pprint(powerSettings)
    cStr = ""
    cStr += "#define RAIL_PA_CURVES{}_SUBGIG_CURVES_NUM_VALUES  ({}U)\n".format(
        ("_EFF" if fem is True else ""), int(powerSettings.__len__())
    )
    cStr += "#define RAIL_PA_CURVES{}_SUBGIG_CURVES_STEP_DDBM   ({}U)\n".format(
        ("_EFF" if fem is True else ""), int(increment)
    )
    cStr += "#define RAIL_PA_CURVES{}_SUBGIG_MAX_POWER_DDBM     ({}{})\n".format(
        ("_EFF" if fem is True else ""), int(maxpwr), ("U" if maxpwr >= 0 else "")
    )
    cStr += "#define RAIL_PA_CURVES{}_SUBGIG_MIN_POWER_DDBM     ({}{})\n".format(
        ("_EFF" if fem is True else ""), int(minpwr), ("U" if minpwr >= 0 else "")
    )
    cStr += "#define RAIL_PA_CURVES{}_SUBGIG_CURVES \\\n".format(
        ("_EFF" if fem is True else "")
    )
    cStr += "\t{\t\\\n"
    cStr += StringFromVirtualPowerLevel(powerSettings, minpwr, increment)
    cStr += "\t\\\n\t}\n"
    return "\n" + cStr


def GetSUBGIGData(File):
    """
    The code above does the following:
    1. It opens the file and reads the data in.
    2. It checks that the number of columns is valid.
    3. It appends the data from the columns to the appropriate list.
    4. It returns the data as a tuple of numpy arrays.
    """
    coarse = []
    fine = []
    slice = []
    stripe = []
    with open(File, "r") as f:
        reader = csv.reader(decomment(f))
        for columns in reader:
            # check that data from columns is valid
            if len(columns) != 4:
                raise ValueError("Invalid number of columns in file")

            # Append the data from the columns
            coarse.append(int(columns[0]))
            fine.append(int(columns[1]))
            stripe.append(int(columns[2]))
            slice.append(int(columns[3]))

    return (
        numpy.array(coarse),
        numpy.array(fine),
        numpy.array(slice),
        numpy.array(stripe),
    )


# The following function converts a list of virtual power levels to a string.
# It takes in three arguments, the list of virtual power levels, the minimum value and the step value.
def StringFromVirtualPowerLevel(virtualPowerLevels, min, step):
    """
    Converts a list of virtual power levels to a string.
    """
    # Initialize an empty string and variables for the last power level and last dbm
    string = ""
    last_power_level = None
    last_dbm = None

    # Iterate through the list of virtual power levels
    for i in range(0, virtualPowerLevels.__len__()):

        # Check if the current power level is different from the last power level
        if virtualPowerLevels[i] != last_power_level:
            # Calculate the dbm value using the minimum value and step value
            last_dbm = (min + (i * step)) / 10
            last_power_level = virtualPowerLevels[i]

        # Add the power level and its corresponding dbm value to the string
        string += (
            "  "
            + virtualPowerLevels[i]
            + "\t/* {} dBm */".format(last_dbm)
        )

        # If it's not the last power level, add a comma and line break to the string
        if i != virtualPowerLevels.__len__() - 1:
            string += ", \\n"

    # Return the string
    return string


def GenerateDbmToPowerSettingTableOFDM(
    File, minpwr, maxpwr, fem=False, increment=API_INCREMENT_DEFAULT
):
    """
    1. Load the CSV file
    2. Get GAINDIG, SLICE, FILGAIN data from the CSV file
    3. Create the formatted string to be written to the header file
    4. Write the string to a header file
    """
    gaindig, slice, filgain = GetOFDMData(File)

    assert (
        gaindig.__len__()
        == slice.__len__()
        == filgain.__len__()
        == (abs(maxpwr - minpwr) / increment + 1)
    ), "Expected number of power levels {} does not match actual number of power levels {}".format(
        abs(maxpwr - minpwr) / increment, gaindig.__len__()
    )
    powerSettings = []
    for gaindig, slice, filgain in zip(gaindig, slice, filgain):
        powerSettings.append(hex((filgain << 16) | (slice << 8) | int((gaindig / 5))))
    pprint(powerSettings)
    cStr = ""
    cStr += "#define RAIL_PA_CURVES{}_OFDM_CURVES_NUM_VALUES  ({}U)\n".format(
        ("_EFF" if fem is True else ""), int(powerSettings.__len__())
    )
    cStr += "#define RAIL_PA_CURVES{}_OFDM_CURVES_STEP_DDBM   ({}U)\n".format(
        ("_EFF" if fem is True else ""), int(increment)
    )
    cStr += "#define RAIL_PA_CURVES{}_OFDM_MAX_POWER_DDBM     ({}{})\n".format(
        ("_EFF" if fem is True else ""), int(maxpwr), ("U" if maxpwr >= 0 else "")
    )
    cStr += "#define RAIL_PA_CURVES{}_OFDM_MIN_POWER_DDBM     ({}{})\n".format(
        ("_EFF" if fem is True else ""), int(minpwr), ("U" if minpwr >= 0 else "")
    )
    cStr += "#define RAIL_PA_CURVES_OFDM_CURVES \\\n"
    cStr += "\t{\t\\\n"
    cStr += StringFromVirtualPowerLevel(powerSettings, minpwr, increment)
    cStr += "\t\\\n\t}\n"
    return "\n" + cStr


def GetOFDMData(File):
    """
    The code above does the following:
    1. Open the file with the name given by File
    2. Pass the file to decomment which skips any lines starting with a #
    3. Read the data from the file using csv.reader
    4. Check that the data is valid
    5. Append the data to the numpy arrays
    6. Return the numpy arrays
    """
    gaindig = []
    slice = []
    filgain = []
    with open(File, "r") as f:
        reader = csv.reader(decomment(f))
        for columns in reader:
            # check that data from columns is valid
            if len(columns) != 3:
                raise ValueError("Invalid number of columns in file")

            # Append the data from the columns
            slice.append(int(columns[0]))
            gaindig.append(int(columns[1]))
            filgain.append(int(columns[2]))

    return (numpy.array(gaindig), numpy.array(slice), numpy.array(filgain))


def main():
    global API_INCREMENT_DEFAULT
    parser = argparse.ArgumentParser(
        description="Utility to fit PA data to RAIL Virtual Power Level Tables."
    )
    parser.add_argument(
        "File", type=str, help="The input  file to parse for power information"
    )
    parser.add_argument(
        "-min",
        "--minPower",
        type=float,
        required=True,
        help="The minimum power(in dBm rounded to 1 decimal place) for the table.",
    )
    parser.add_argument(
        "-max",
        "--maxPower",
        type=float,
        required=True,
        help="The maximum power(in dBm rounded to 1 decimal place) for the table.",
    )
    parser.add_argument(
        "-f",
        "--fem",
        type=bool,
        required=False,
        default=False,
        help="Specifies whether these curves are for the Front End Module.",
    )
    parser.add_argument(
        "-o",
        "--output",
        type=str,
        default="dbm_to_power_setting_table.h",
        required=False,
        help="The output file to print the results to. Will \
                      print to stdout by default.",
    )
    parser.add_argument(
        "-t",
        "--type",
        type=str,
        required=True,
        default="OFDM",
        help="Specifies whether these curves are for the OFDM or SUBGIG.",
    )
    a = parser.parse_args()

    if a.type == "OFDM":
        output = GenerateDbmToPowerSettingTableOFDM(
            a.File, a.minPower, a.maxPower, a.fem, round(a.increment, 1)
        )
    elif a.type == "SUBGIG":
        output = GenerateDbmToPowerSettingTableSUBGIG(
            a.File, a.minPower, a.maxPower, a.fem, round(a.increment, 1)
        )
    else:
        print(
            "Type {} is no valid. Please specify either OFDM or SUBGIG".format(a.type)
        )
        return 0
    if a.output is None:
        print(output)
    else:
        with open(a.output, "w") as f:
            f.write(output)

    return 0


if __name__ == "__main__":
    sys.exit(main())
