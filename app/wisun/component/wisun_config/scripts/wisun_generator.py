#!/usr/bin/env python

# The generator creates embedded source files based on the wisun configuration file, .wisunconf.
# Using proper restriction files beside the .wisunconf file the generator can be controlled
# which properties of the configuration is used. Jinja template helps generate the files and their
# contents.
# Currently the restriction:
# - deniedProperties is fully covered (every property can be denied)
# - if no visible tabs defined, all tabs will be shown

from fileinput import filename
import os
import json
import re
from jinja2 import Environment, FileSystemLoader
import argparse

def get_input_output_path():
    """It gets the input and output location of configuration file and of autogen location
    where the generated source files of configuration born.
    Other input file(s) read, the restriction file(s) to controll which settings are used during
    the generation.

    :return: configuration file location with file name, output folder path, 
             array of restriction file(s) and their path(es).
    :rtype: string, string, string[]
    """

    cwd = os.getcwd()
    parser = argparse.ArgumentParser(
        description="Wi-SUN Configurator code generator"
    )
    parser.add_argument("input", nargs="?", default=cwd)
    parser.add_argument("-o",dest="output", nargs="?", default=cwd)

    args = parser.parse_args()

    # Find all .wisunconf files in the input directory
    wisunconf_path_list = [
        os.path.join(args.input, filename)
        for filename in os.listdir(args.input)
        if re.search(r"\.wisunconf$", filename, re.IGNORECASE)
    ]

    # gets the .wisunconf file, and define the output folder path (autogen)
    if wisunconf_path_list:
        wisunconf_path = wisunconf_path_list[0]
    else:
        wisunconf_path = args.input

    # Find all .restriction files in the input directory
    restrictions_pathes = [
        os.path.join(args.input, filename)
        for filename in os.listdir(args.input)
        if re.search(r"\.restriction$", filename, re.IGNORECASE)
    ]

    # Set restrictions_pathes to None if no .restriction files were found
    if not restrictions_pathes:
        restrictions_pathes = None

    return wisunconf_path, str(args.output), restrictions_pathes

def config_generate(only_radio, config, template_dir:str, c_jinja_file_name:str, h_jinja_file_name:str):
    """It generates the configuration embedded source files .c and .h files based on jinja template files.

    :param config: Read configuration from the .json shaped configuration file
    :type config: dictionary
    :param template_dir: location of jinja template files
    :type template_dir: str
    :param c_jinja_file_name: jinja file name of .c generated config file
    :type c_jinja_file_name: str
    :param h_jinja_file_name: jinja file name of .c generated config file
    :type h_jinja_file_name: str
    :return: generated file contents (for .c and .h)
    :rtype: str, str
    """

    file_loader = FileSystemLoader(template_dir)
    env = Environment(loader=file_loader)

    # getting mac address
    mac_address = []
    if config['macAddress'] is not None:
        mac_address = re.findall("[a-fA-F0-9][a-fA-F0-9]", config['macAddress'])
    # getting mac address list
    mac_list = []
    if config['macList'] is not None:
        for mac_list_address in config['macList']:
            mac_list.append(re.findall("[a-fA-F0-9][a-fA-F0-9]", mac_list_address))

    template = env.get_template(c_jinja_file_name)
    c_output = template.render(only_radio=only_radio, config=config, macAddress=mac_address, macList=mac_list)

    template = env.get_template(h_jinja_file_name)
    h_output = template.render(only_radio=only_radio, config=config, macAddress=mac_address, macList=mac_list)

    return c_output, h_output

def get_wisun_config(path):
    """It gets the configuration content from the file, parsed by json format

    :param path: path and file name of the configuration
    :type path: str
    :return: configuration content
    :rtype: dictionary
    """

    with open(path) as f:
        conf = json.load(f)

    return conf

def get_wisun_restrictions(paths):
    """Get the content of the restriction file(s) and merge them into two lists

    :param paths: list of restriction path(s) with its/their file(s) name
    :type paths: list[str]
    :return: visible tabs, denied properties
    :rtype: tuple[list[str], list[str]]
    """
    visible_tabs = []
    denied_properties = []

    for path in paths:
        with open(path) as file:
            restriction = json.load(file)

            visible_tabs.extend(field.get("value") 
                                for field in restriction if field.get("name") == "visibleTabs")
            denied_properties.extend(field.get("value") 
                                     for field in restriction if field.get("name") == "deniedProperties")

    return visible_tabs, denied_properties

def get_wisun_config_struct():
    """It gets the configuration structure for getting know what configuration settings are.

    :return: configuration structure
    :rtype: dictionary
    """
    with open("config.json") as f:
        conf = json.load(f)

    return conf

def get_allowed_channel_mask(allowed_chan):
    mask = 0



def get_allowed_channels(allowed_channels_config: list()) -> list():

    allowed_channel_mask = 0
    bit_mask = 255

    if len(allowed_channels_config) == 0:
        return 
    
    for chan in allowed_channels_config:
        allowed_channel_mask = allowed_channel_mask | get_allowed_channel_mask(chan)

    return [(allowed_channel_mask & (bit_mask << ((31 - num) * 8))) for num in range(32)]


def bit_pos_to_byte_bit(bit_pos: int) -> tuple:
    return (int(bit_pos / 8), bit_pos % 8,)

def set_ch_mask_range(dest_lst: list, num_a:int, num_b:int):
    num_a_byte_bit:tuple = bit_pos_to_byte_bit(int(num_a))
    num_b_byte_bit:tuple = bit_pos_to_byte_bit(int(num_b))
    for i in range(num_b_byte_bit[0] - num_a_byte_bit[0] + 1):
        offset = i + num_a_byte_bit[0]
        
        if offset == num_a_byte_bit[0]:
            msk_val = 0xff & (0xff << num_a_byte_bit[1])  
        elif offset == (num_b_byte_bit[0]):
            msk_val = 0xff & (0xff >> (7 - num_b_byte_bit[1]))
        else:
            msk_val = 0xff

        dest_lst[offset] = (dest_lst[offset] | msk_val)

def set_ch_mask_single(dest_lst: list, num:int):
    num_byte_bit:tuple = bit_pos_to_byte_bit(int(num))
    msk_val = 0xff & (0x01 << num_byte_bit[1])  
    dest_lst[num_byte_bit[0]] = (dest_lst[num_byte_bit[0]] | msk_val)

def calculate_channel_mask(dest_lst: list, allowed_channels: list):
    # reset array
    for i in range(32):
        ch_int_lst.append(0)
    for msk_str in allowed_channels:
        m = re.match(r"(\d+)\-(\d+)",msk_str)
        if (m != None):
            num_a: int = m.group(1)
            num_b: int = m.group(2)
            set_ch_mask_range(dest_lst, num_a, num_b)
        else:
            num: int = msk_str
            set_ch_mask_single(dest_lst, num)

if __name__ == "__main__":

    print("--------WisunConfGenerator---------")

    # getting paths (configuration and restriction)
    input_path, output_path, restrictions_pathes = get_input_output_path()

    # getting confiuration as a dictionary
    wisunconf = get_wisun_config(path=input_path)

    # getting configuration structure
    config_struct = get_wisun_config_struct()
    ch_int_lst: list = []

    if wisunconf['allowedChannels']:
        calculate_channel_mask(ch_int_lst, wisunconf['allowedChannels'])
    else:
        for i in range(32):
            ch_int_lst.append(255)

    wisunconf['allowedChannels'] = [hex(ch) for ch in ch_int_lst]
    # getting restricions and defining the config data which is used, which is not
    only_radio = False

    if restrictions_pathes is not None:
        hidden_tabs = []

        visible_tabs, denied_properties = get_wisun_restrictions(restrictions_pathes)

        merged_visible_tabs = [element for innerList in visible_tabs for element in innerList]
        merged_denied_properties = [element for innerList in denied_properties for element in innerList]
        
        if merged_visible_tabs:
            hidden_tabs = [tab for tab in config_struct.keys() if tab not in merged_visible_tabs]

        for prop in merged_denied_properties:
            wisunconf[prop] = None
            
        for tab in hidden_tabs:
            for prop in config_struct[tab]:
                wisunconf[prop] = None
    
        # Check for special case of visibleTabs
        if len(merged_visible_tabs) == 1 and "radio" in merged_visible_tabs:
            only_radio = True

    # using jinja templates it generates the source fils' strings
    wisun_config_c_file, wisun_config_h_file = config_generate(only_radio=only_radio,
                                                               config=wisunconf,
                                                               template_dir="../templates",
                                                               c_jinja_file_name="sl_wisun_config.c.jinja",
                                                               h_jinja_file_name="sl_wisun_config.h.jinja")

    # gets the source files accurate location
    config_c_path = os.path.join(output_path, "sl_wisun_config.c")
    config_h_path = os.path.join(output_path, "sl_wisun_config.h")

    # writes the generated strings into files
    with open(config_c_path, "w") as f:
        f.write(wisun_config_c_file)
    with open(config_h_path, "w") as f:
        f.write(wisun_config_h_file)

    print(f"Wi-SUN config: {input_path}")
    if restrictions_pathes is not None:
        for restriction in restrictions_pathes:
            print(f"Restriction: {restriction}")
    print(f"Generated files:\r\n"
        "  sl_wisun_config.c\r\n"
        "  sl_wisun_config.h")

    print("-----------------------------------")