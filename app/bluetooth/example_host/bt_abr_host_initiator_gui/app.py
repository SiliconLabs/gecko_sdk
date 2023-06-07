#!/usr/bin/env python3
 ###############################################################################
 # # License
 # <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
 ###############################################################################
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
 #
 ##############################################################################/

import os
import datetime
import argparse
from matplotlib import pyplot
try:
    import serial
except ImportError:
    pass

# Run "python app.py --help" for help

DEFAULT_DISTANCE_FILE = os.path.join(os.path.dirname(__file__),
                                     '../bt_abr_host_initiator/exe/distance.txt')
DEFAULT_RSSI_DISTANCE_FILE = os.path.join(os.path.dirname(__file__),
                                     '../bt_abr_host_initiator/exe/distance_rssi.txt')
LABEL_NAMES = ['HADM', 'RSSI']
DEFAULT_SERIAL_DEVICE = ""
SECONDS_TO_WAIT_FOR_EXIT = 3
DISTANCE_POINTS_IN_PLOT = 100
SHOW_LEGEND = True

class DemoPlotParams:
    """Demo plot parameters"""
    def __init__(self):
        self.history = DISTANCE_POINTS_IN_PLOT
        self.show_legend = SHOW_LEGEND
        self.num_files = 1
        self.distances = [] # list of lists of distances
        self.figure = ''
        self.dist_axes = ''
        self.seconds_to_wait_for_exit = SECONDS_TO_WAIT_FOR_EXIT
        self.plot_styles = ['bo', 'ro']
        self.plot_marker_sizes = [10, 10]
        self.dist_lines = None
        self.is_plot_initiated = False
        self.labels = LABEL_NAMES

DPLOT_PARAMS = DemoPlotParams()

def plot_demo(new_distances):
    """Initialise the plot and update it based on the dict (method: distance) of newly recorded distances"""
    distance_values = list(new_distances.values())
    distance_keys = list(new_distances.keys())
    # If called for the first time, initiate
    if not DPLOT_PARAMS.is_plot_initiated:
        pyplot.ion()
        pyplot.subplots(figsize=(20, 10))
        DPLOT_PARAMS.dist_axes = pyplot.subplot(1, 1, 1)
        DPLOT_PARAMS.dist_axes.set_xlim([0, DPLOT_PARAMS.history])
        DPLOT_PARAMS.dist_axes.set_xticks([])
        DPLOT_PARAMS.dist_axes.tick_params(axis='y', which='major', labelsize=20)
        DPLOT_PARAMS.dist_axes.set_ylabel("Distance (m)", fontsize = 30)

        DPLOT_PARAMS.distances = DPLOT_PARAMS.num_files*[None]
        DPLOT_PARAMS.dist_lines = DPLOT_PARAMS.num_files*[None]
        for i in range(DPLOT_PARAMS.num_files):
            DPLOT_PARAMS.distances[i] = [distance_values[i]]
            DPLOT_PARAMS.dist_lines[i], = DPLOT_PARAMS.dist_axes.plot(DPLOT_PARAMS.distances[i],
                                                                      DPLOT_PARAMS.plot_styles[i],
                                                                      markersize = DPLOT_PARAMS.plot_marker_sizes[i],
                                                                      label=distance_keys[i])
        DPLOT_PARAMS.is_plot_initiated = True
    else:
        # Update the distance plot
        for i in range(DPLOT_PARAMS.num_files):
            dist_line = DPLOT_PARAMS.dist_lines[i]
            try:
                DPLOT_PARAMS.distances[i].append(float(distance_values[i]))
                label_text = f"{distance_keys[i]} : {DPLOT_PARAMS.distances[i][-1]:0.2f} m"
                dist_line.set(label=label_text)
            except TypeError:
                pass
            x_data = list(range(0, len(DPLOT_PARAMS.distances[i]), 1))
            dist_line.set(xdata=x_data, ydata=DPLOT_PARAMS.distances[i])
        try:
            dist_title = f"{new_distances['HADM']:0.2f}m"
            DPLOT_PARAMS.dist_axes.set_title(' '.join(dist_title), fontsize=80, fontweight='bold')
        except TypeError:
            pass

    if DPLOT_PARAMS.show_legend:
        DPLOT_PARAMS.dist_axes.legend(fontsize=20)

    # Automatic scaling of the Y axis
    dist_max = max([max(dlist, default=0) for dlist in DPLOT_PARAMS.distances])
    if dist_max < 3.0:
        demo_plot_ylim = 3
    elif dist_max < 5.0:
        demo_plot_ylim = 5
    elif dist_max < 10.0:
        demo_plot_ylim = 10
    else:
        demo_plot_ylim = 35
    DPLOT_PARAMS.dist_axes.set_ylim([0, demo_plot_ylim])

    # Pause or plt will not show the figure.
    pyplot.pause(1e-20)

    # Start emptying values when history is full
    if any([len(distances) > DPLOT_PARAMS.history for distances in DPLOT_PARAMS.distances]):
        for i in range(DPLOT_PARAMS.num_files):
            DPLOT_PARAMS.distances[i] = DPLOT_PARAMS.distances[i][1:]

def process_ncp_init(distance_files_to_plot):
    """Extract distance values from the NCP initiator"""

    for file in distance_files_to_plot:
        if not os.path.isfile(file):
            print(f"Output distance file {file} was not specified or found. Closing the program.")
            return

    file_positions = len(distance_files_to_plot)*[0]
    last_new_distance_time = datetime.datetime.now()

    while True:
        distances_to_plot = len(distance_files_to_plot)*[None]
        distance_dict = dict.fromkeys(DPLOT_PARAMS.labels)
        # Read the disstance files
        for i in range(DPLOT_PARAMS.num_files):
            with open(distance_files_to_plot[i], encoding='UTF-8') as distance_file:
                distance_file.seek(file_positions[i])
                distances_to_plot[i] = distance_file.readline()
                if distances_to_plot[i]:
                    file_positions[i] = distance_file.tell()
        # Check if reading any distance was successful
        if not any(distances_to_plot):
            time_delta = datetime.datetime.now() - last_new_distance_time
            if time_delta.seconds > DPLOT_PARAMS.seconds_to_wait_for_exit:
                print(f"No new measurements for over {DPLOT_PARAMS.seconds_to_wait_for_exit} s. "
                        "Closing the program.")
                break
        # If successful, then update the distance plot
        else:
            last_new_distance_time = datetime.datetime.now()
            for i in range(DPLOT_PARAMS.num_files):
                try:
                    distance_dict[DPLOT_PARAMS.labels[i]] = float(distances_to_plot[i])
                except ValueError:
                    pass
            plot_demo(distance_dict)

def process_soc_init(init_serial_port = ""):
    """Extract distance values from the SoC initiator"""
    try:
        ser = serial.Serial(port=init_serial_port, baudrate=115200)
    except IOError:
        print("Serial port to the SoC initiator could not be opened")
        return
    except NameError:
        print("Python module 'serial' is not imported")
        return

    last_new_distance_time = datetime.datetime.now()
    while True:
        if ser.in_waiting > 0:
            new_dist = ser.read(ser.in_waiting)
            # Try reading distance
            try:
                data_str = new_dist[2:-2].decode("ascii")
                distance = str(int(data_str) / 1000.0)
            except ValueError:
                distance = None
            # Check if reading the distance was successful
            if not distance:
                time_delta = datetime.datetime.now() - last_new_distance_time
                if time_delta.seconds > DPLOT_PARAMS.seconds_to_wait_for_exit:
                    print(f"No new measurements for over {DPLOT_PARAMS.seconds_to_wait_for_exit} s. "
                          "Closing the program.")
                    break
            else:
                last_new_distance_time = datetime.datetime.now()
                distance_dict = {LABEL_NAMES[0]: float(distance)}
                plot_demo(distance_dict)

def main():
    """Process input arguments and launch the visualisation"""
    parser = argparse.ArgumentParser(description =
                                     "SoC mode: Connect the SoC initiator to the computer by USB and run this script. "
                                     "NCP mode: Start the host application and run this script.")
    parser.add_argument("--mode", choices=['ncp', 'soc'], default='ncp', type=str.lower,
                        help="Initiator mode ncp (default) or soc")
    parser.add_argument("--filename", default=DEFAULT_DISTANCE_FILE,
                        help='Path to the output distance (NCP mode only)')
    parser.add_argument("--serial", default=DEFAULT_SERIAL_DEVICE,
                        help='Initiator serial port (SoC mode only)')
    parser.add_argument("--rssi", action='store_true', help="Enable RSSI plotting (NCP mode only)")
    parser.add_argument("--rssi_filename", default=DEFAULT_RSSI_DISTANCE_FILE, help='Path to the RSSI output distance (NCP mode only)')
    args = parser.parse_args()

    if args.mode == 'soc':
        process_soc_init(args.serial)
    else:
        distance_files_to_plot = [args.filename]
        if args.rssi:
            distance_files_to_plot.append(args.rssi_filename)
        DPLOT_PARAMS.num_files = len(distance_files_to_plot)
        process_ncp_init(distance_files_to_plot)

if __name__ == '__main__':
    main()
