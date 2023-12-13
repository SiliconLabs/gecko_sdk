#!/usr/bin/env python3
import sys
import os
import re
import subprocess
import shutil
import time
import argparse
import builtins
import tkinter as tk
from tkinter import filedialog as fd
from pathlib import Path
from glob import glob
from datetime import datetime as dt

LOGO = "  _____                _         _____ ______ _        __ _ _            \n"
LOGO += " /  __ \              | |       |  __ \| ___ \ |      / _(_) |           \n"
LOGO += " | /  \/_ __ ___  __ _| |_ ___  | |  \/| |_/ / |     | |_ _| | ___  ___  \n"
LOGO += " | |   | '__/ _ \/ _` | __/ _ \ | | __ | ___ \ |     |  _| | |/ _ \/ __| \n"
LOGO += " | \__/\ | |  __/ (_| | ||  __/ | |_\ \| |_/ / |____ | | | | |  __/\__ \ \n"
LOGO += "  \____/_|  \___|\__,_|\__\___|  \____/\____/\_____/ |_| |_|_|\___||___/ \n"

# Configuration
INTERACTIVE = True
ALWAYS_SELECT_GCC_EXT = True
COMPRESS_GBLS = True
PURGE_SRECS = True
VERBOSE = False
OUTDIR = 'output_gbl'

# Artifacts the script will looking for
BOOT_S1_F = 'bootloader-second-stage.s37'
BOOT_S2_F = 'bootloader-apploader.s37'
SIGN_N = 'app-sign'
SIGN_F = SIGN_N + '-key.pem'
ENCRYPT_N = 'app-encrypt'
ENCRYPT_F = ENCRYPT_N + '-key.txt'
# Output filenames without extensions
APPLO_N = 'apploader'
BOOTLO_N = 'bootloader'
APPLI_N = 'application'
UARTDFU_N = 'full'

# ANSI terminal code
class ansi:
    rd = '\033[0;31m'  # red
    gn = '\033[0;32m'  # green
    yl = '\033[0;33m'  # yellow
    pr = '\033[0;35m'  # purple
    cl = '\033[0m'     # clear
    prev_ln = '\x1b[F' # previous line (begin)

# tips enumerator class to show to the user e.g. if some input file is missing or special config
# used for the generator
class tip:
    BOOT =        0  
    ENCRYPT =     1
    SIGN =        2
    COMPRESS =    3
    INTERACTIVE = 4

# enumerator class for print out levels to show
class lvl:
    INFO = 0  # INFO
    OKAY = 1  # OK
    WARN = 2  # WARNING
    ERR =  3  # ERROR

# Operation switches
BOOT_EXIST = False
ENCRYPT_KEY_EXIST = False

# Functions
def print(level, *args, **kwargs):
    """Print function

    Override built in print function to display information in the following format (with colors):
    [   OK   ] Operation Finished.
    
    :param level: INFO, OK, WARNING or ERROR levels, see definition of lvl class
    :type level: lvl enumerator class
    """
    if level == lvl.INFO:
        builtins.print(" " * 12, end="")
    else:
        builtins.print("[", end="")
        if level == lvl.OKAY:
            builtins.print(ansi.gn + "   OK   ", end="")
        elif level == lvl.WARN:
            builtins.print(ansi.yl + "WARNING ", end="")
        elif level == lvl.ERR:
            builtins.print(ansi.rd + " ERROR  ", end="")
        builtins.print(ansi.cl + "]: ", end="")
    builtins.print(*args, **kwargs, flush=True)


def print_question(question, delay=0.5):
    """Print question

    Print out a yes-or-no question in the terminal in the same format as print.
    Default selection marked in uppercase and requires only to press Enter.

    :param question: the text of the yes-or-no question
    :type question: str
    :param delay: delay after the answer, defaults to 0.5 sec
    :type delay: float, optional
    :return: True if 'Y' is the answer, else False
    :rtype: bool
    """
    builtins.print("[" + ansi.pr + "QUESTION" + ansi.cl + "]: ", end='')
    yorno = input(question + " [Y/n]:\n" + " " * 12)
    if yorno.lower() == 'n':
        # overwrites the previous line content: n --> No.
        builtins.print(ansi.prev_ln + "\r" + " " * 12 + ansi.yl + "No." + ansi.cl)
        time.sleep(delay)
        return False
    else:
        # overwrites the previous line content:  --> Yes.
        builtins.print(ansi.prev_ln + "\r" + " " * 12 + ansi.gn + "Yes." + ansi.cl)
        time.sleep(delay)
        return True


def print_tip(t, delay=1.5):
    """Prints out selected tip to the standard output

    :param t: selected tip to display
    :type t: Literal
    """
    offset = " " * 12
    if t == tip.BOOT:
        msg = "Tip: to add bootloader to the apploader you have the following options:\n" + offset
        msg += "Option 1:\n" + offset
        msg += "- copy a bootloader image .s37 to the current working directory\n" + offset
        if SERIES_1:
            boot = BOOT_S1_F
        else:
            boot = BOOT_S2_F
        msg += "- rename it to " + ansi.yl + f"{boot}" + ansi.cl + " and rerun this script\n" + offset
        msg += "Option 2:\n" + offset
        msg += "- rerun this script with "+ansi.yl+"-i"+ansi.cl+" argument to activate interactive mode\n" + offset
        msg += "- when prompted select the desired bootloader .s37 image with a filedialog"
        msg += "Option 3:\n" + offset
        msg += "- rerun this script with "+ansi.yl+"-b"+ansi.cl+" argument and specify a direct path to\n" + offset
        msg += "  the selected bootloader .s37 file\n" + offset
        msg += "Note: Series-2 devices support merged bootloaders a.k.a. bootloader-apploader.s37\n" + offset
        msg += "      for applications that are utilize in-place OTA DFU.\n" + offset
        
    elif t == tip.ENCRYPT or t == tip.SIGN:
        if t == tip.ENCRYPT:
            action = "encrypt"
            key = action + "ion key .txt"
            arg = "-k"
            filename = ENCRYPT_F
        else:
            action = "sign"
            key = action + "ature key .pem"
            arg = "-s"
            filename = SIGN_F
        msg = f"Tip: to generate {action}ed GBL files you have the following options:\n" + offset
        msg += "Option 1:\n" + offset
        msg += f"- copy the {key} file to the current working directory\n" + offset
        msg += "- rename it to " + ansi.yl + f"{filename}" + ansi.cl + " and rerun this script\n" + offset
        msg += "Option 2:\n" + offset
        msg += "- rerun this script with "+ansi.yl+"-i"+ansi.cl+" argument to activate interactive mode\n" + offset
        msg += "- when prompted select the generation option to generate the key automatically\n" + offset
        msg += "Option 3:\n" + offset
        msg += "- rerun this script with "+ansi.yl+f"{arg}"+ansi.cl+" argument and specify a direct path to\n" + offset
        msg += "  the selected key file\n" + offset

    elif t == tip.COMPRESS:
        cpx = ansi.yl + "support decompressing" + ansi.cl
        msg = f"Compressed GBLs require a bootloader that {cpx} the GBL!"
    elif t == tip.INTERACTIVE:
        msg = ansi.pr + "INTERACTIVE MODE" + ansi.cl + " selected!\n" + offset
        msg += "For missing tools or files a dialog will be shown to specify the absolute path to the tool\n" + offset
        msg += "in console- or filedialogs, for "+ansi.yl+"keys"+ansi.cl+" the script will offer\n" + offset
        msg += "the generation option.\n" + offset
        msg += "If you want to run this script without any human interaction e.g. in automated environment\n" + offset
        msg += "it is suggested to not use this mode!\n" + offset
        msg += "Consult with the helper (-h or --help) for more"
    print(lvl.INFO,msg)
    time.sleep(delay)


def display_menu(elems_list, title):
    """Display text-based menu

    Display text based menu for the user in the terminal.
    The options in the displayed menu defined by the elem_list.

    The user shall select from 1st to last or press other keys to abort the selection.

    :param elems_list: list that will be taken as the options for the menu
    :type elems_list: lst
    :param title: title that will be displayed above the options
    :type title: str
    :return: selected element from the elems_list (as string)
    :rtype: str
    """
    print(lvl.INFO,title)
    for i in range(0, len(elems_list)):
        print(lvl.INFO,f"[{i+1}] ", str(elems_list[i]))
    
    message = f"Select one from above [ 1 - {len(elems_list)} ] and press Enter!\n" + " " * 12
    message += "To abort press any other key and press Enter!"
    print(lvl.INFO,message)
    try:
        s = int(input(" " * 12))
    except (TypeError, ValueError):
        s = 0

    if s in range(1, len(elems_list)+1):
        print(lvl.INFO,ansi.prev_ln + " " *12 + f"{str(s)} - \'{str(elems_list[s-1])}\'.")
        return str(elems_list[s-1])
    print(lvl.INFO,f"Abort selection.")
    return None


def interactive_menu(sep):
    """Realize interactive menu to configure the generator

    Shows terminal-dialogs and displays terminal-menu in order to set all possible switches in
    an interactive way.
    The switches:
    - sign GBLs (bool)
    - encrypt GBLs (bool)
    - compress GBLs (bool)
    - compression method as string (lz4, lzma, both)
    - generate UARTDFU GBLs (bool)

    :param sep: separator string that only used for display style
    :type sep: str
    :return: valid values for sign, encrypt, cpress, cpress_method, uartdfu
    :rtype: bool, bool, bool, str, bool
    """
    offset = " " * 12
    
    print_tip(tip.INTERACTIVE)
    print(lvl.INFO,sep)
    print(lvl.INFO,"Select generation steps below ...")
    print(lvl.INFO,sep)
    
    question = "Would you like to "+ ansi.yl + "sign" + ansi.cl + " your GBL files?\n" + offset
    question += "Note: if you don't have .pem files this script will generate them\n" + offset
    question += "for you later on if you want to."
    sign = print_question(question)
    
    question = "Would you like to "+ ansi.yl + "encrypt" + ansi.cl + " your GBL files?\n" + offset
    question += "Note: if you don't have an encryption key .txt this script will generate them\n" + offset
    question += "for you later on if you want to."
    encrypt = print_question(question)
    
    question = "Would you like to "+ ansi.yl + "compress" + ansi.cl + " your GBL files?\n" + offset
    question += "Note: for compressed GBLs you have to use a bootloader that is capable to\n" + offset
    question += ansi.yl + "decompress" + ansi.cl + " those images!"
    cpress = print_question(question)
    if cpress:
        cpress_method = display_menu(['lz4', 'lzma', 'both'], "Select compression method!")
    else:
        cpress = False
        cpress_method = ""
        print(lvl.WARN, "Did not selected compression method!")
        print(lvl.INFO, "Compression will be skipped!")
    
    uartdfu = print_question("Would you like to generate "+ ansi.yl + "UARTDFU" + ansi.cl + " GBL files?")
    
    print(lvl.INFO, sep)
    print(lvl.INFO, "Setup finished:")
    print(lvl.INFO, sep)
    # "Sign | Encrypt | Compress | Compress method | UART DFU GBLs"
    # " yes | no      | yes      | lzma            | yes"
    print(lvl.INFO, "Sign | Encrypt | Compress | Compress method | UART DFU GBLs")
    print(lvl.INFO, f"{'yes  ' if sign else 'no   '}| {'yes     ' if encrypt else 'no      '}|", end="")
    if cpress_method == "lz4":
        cpress_method += " "
    elif cpress_method == "":
        cpress_method = "none"
    builtins.print(f"{' yes      ' if cpress else ' no       '}| {cpress_method}            |", end="")
    builtins.print(f"{' yes' if uartdfu else ' no'}")

    return sign, encrypt, cpress, cpress_method, uartdfu


def detect_platform():
    """Detects host platform and returns with it

    :return: platform in lower letters string
    :rtype: str
    """
    platform = os.sys.platform.lower()
    if platform == 'win32':
        response = run_cmd(['uname'], True, verbose=VERBOSE)
        if response is None:
            return 'cmd'
        elif re.search(r'is not recognized', response):
            return 'cmd'
        else:
            match_result = re.search(r'MSYS_NT', response)
            if match_result:
                return 'msys'
            match_result = re.search(r'MINGW', response)
            if match_result:
                return 'mingw'
            match_result = re.search(r'CYGWIN_NT', response)
            if match_result:
                return 'cygwin'
    else:
        return platform


def run_cmd(command_list, supp_ex_disp=False, verbose=False):
    """Execute terminal command

    Execute terminal command in a subprocess and return with the content of the standard error and
    standard output if its not empty.

    :param command_list: terminal command as a list
    :type command_list: lst
    :param supp_ex_disp: suppress exception display, defaults to False
    :type supp_ex_disp: bool, optional
    :param verbose: verbosity enable, defaults to False
    :type verbose: bool, optional
    :return: in case not empty return with stderr or stdout content as utf-8 encoded string
    :rtype: str
    """
    if verbose:
        print(lvl.INFO,"Call:")
        print(lvl.INFO,"\'" + " ".join(command_list) + "\'")
    try:
        cmd_proc = subprocess.run(command_list, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    except FileNotFoundError:
        cmd_proc = subprocess.run(command_list, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
    except Exception as ex:
        if not supp_ex_disp:
            print(lvl.ERR,ansi.rd + " ".join(command_list), ansi.cl + "could not be executed!")
            print(lvl.INFO,"Exception:\n" + ansi.rd + str(ex) + ansi.cl)
        return None

    err = cmd_proc.stderr.decode('utf-8')
    out = cmd_proc.stdout.decode('utf-8')

    if err != "":
        if not supp_ex_disp:
            print(lvl.ERR,"Error during execution of \'" + " ".join(command_list)+"\'!")
            print(lvl.INFO,"stderr:\n"+ansi.rd+err+ansi.cl)
        return err
    elif out != "":
        return out
    else:
        return None


def reformat_path(path):
    """Reformat path to forwardslash posix format

    Reformat path to posix format with forward slashes that is universally accepted by win & posix.
    Also converting cygwin and msys paths to this format.

    :param path: original path
    :type path: str
    :return: reformatted path
    :rtype: str
    """
    path = path.replace('\r', '').replace('\n', '')
    if PLATFORM == 'cygwin':
        m: re.Match = re.match(r"^/cygdrive/(\w)/[\w\s\\/_\-\.]+$", path)
        if m is not None:
            path = re.sub(r"^/cygdrive/\w/", f"{m.group(1)}:/", path)
            return str(Path(path).as_posix())
        else:
            return str(Path(path).as_posix())
    elif PLATFORM == 'msys' or PLATFORM == 'mingw':
        m: re.Match = re.match(r"^/(\w)/[\w\s\\/_\-\.]+$", path)
        if m is not None:
            path = re.sub(r"^/\w/", f"{m.group(1)}:/", path)
            return str(Path(path).as_posix())
        else:
            return str(Path(path).as_posix())
    else:
        return str(Path(path).as_posix())


def check_util_exist(util_name, env):
    """Check wether the selected utility exist

    Check if the selected utility exists in the system PATH. 

    :param util_name: name of the utility (without extension on windows)
    :type util_name: str
    :param env: environment variable
    :type env: str
    :return: absolute path to the utility if exists
    :rtype: str
    """
    if PLATFORM != 'cmd':
        cmd = ['which']
        result_re = r'which: no'
    else:
        util_name += '.exe'
        cmd = ['where']
        result_re = r'Could not find files'
    cmd.append(util_name)
    cmd_result = run_cmd(cmd, True, verbose=VERBOSE)
    match_err = re.search(result_re, cmd_result)
    if match_err:
        if os.environ[env] is not None:
            print(lvl.WARN,f"{util_name} not found in PATH!")
            p = reformat_path(os.environ[env])
            for root, files in os.walk(p):
                for f in files:
                    if f.endswith(util_name) and os.access(os.path.join(root, f), os.X_OK):
                        f = os.path.join(root, f)
                        p = reformat_path(f)
                        print(lvl.OKAY,"Using " + ansi.gn + f"{env}" + ansi.cl + f" instead: {p}")
                        return p
            print(lvl.ERR, f"Could not find {util_name}!")
            return None
    else:
        p = reformat_path(cmd_result)
        print(lvl.OKAY, f"{util_name} detected: {p}")
        return p


def get_file_list(path, extension):
    """Get all files with the selected extension

    Get files with the selected extension in the selected path.

    :param path: path in which the search shall be done
    :type path: str
    :param extension: extension without a '.'
    :type extension: str
    :return: list of absolute filepaths with the selected extension
    :rtype: lst
    """
    file_list = []
    try:
        for root, dirs, files in os.walk(path):
            for file in files:
                if file.endswith(extension):
                    file_list.append(os.path.join(root, file))
    except TypeError:
        print(lvl.ERR,"Invalid path:" + ansi.rd + path + ansi.cl + "!")
    return file_list


def is_target_series_1(build_artifact):
    """Determine the target series

    Determine the target series based on the existing build artifact.

    :param build_artifact: absolute path the the build artifact
    :type build_artifact: str
    :return: True if its a Series-1 project, else False
    :rtype: bool
    """
    with open(build_artifact, 'r', errors='ignore') as app:
        lines = app.readlines()
        for line in lines:
            if line.find('text_apploader') != -1:
                return True
        return False


def is_file_exist(path, suppress_ex=False):
    """Check if the file exist

    Check path if its a file and it does exist.
    If not, or any kind of exception occurs print out the exception and return with False.
    Or return with True.

    :param path: path the the file
    :type path: str
    :param suppress_ex: _description_, defaults to False
    :type suppress_ex: bool, optional
    :return: True if the file exists, or False.
    :rtype: bool
    """
    try:
        path = reformat_path(path)
        return os.path.isfile(path)
    except:
        if path is None and not suppress_ex:
            print(lvl.ERR, ansi.rd + "File does not exist!" + ansi.cl)
        elif not suppress_ex:
            print(lvl.ERR, ansi.rd + f"\'{path}\' does not exist!" + ansi.cl)
    return False


def extract_to_srec(srec_name, remove_sections, out_path, only_section=False):
    """Extract binary data to srec file

    Extract binary data with arm-eabi-objcopy into an .srec file for further usage.
    If the only_section flag set, only the sections in the remove_sections input parameter will remain.
    With this flag the complementer action of the original will be done.

    :param srec_name: name of the srec file (without extension)
    :type srec_name: str
    :param remove_sections: list of the .sections that has to be removed
    :type remove_sections: lst
    :param out_path: output path where the .srec file will be saved
    :type out_path: str
    :param only_section: copy only the sections mentioned in remove_sections, defaults to False
    :type only_section: bool, optional
    :return: path to the .srec file
    :rtype: str
    """
    srec_file = reformat_path(os.path.join(OUTDIR, srec_name + '.srec'))
    cmd = [OBJCOPY, '-O', 'srec']
    for sect in remove_sections:
        if only_section:
            cmd.extend(['-j', sect])
        else:
            cmd.extend(['-R', sect])
    cmd.extend([out_path, srec_file])
    response = run_cmd(cmd, verbose=VERBOSE)
    if response is None and os.path.isfile(srec_file):
        print(lvl.INFO, srec_file + " extracted.")
        return srec_file
    else:
        print(lvl.WARN, "Could not extract \'"+" ,".join(sect) + "\' sections from"+out_path+"!")
        return None


def convert_srec(srec_list, srec_out_name, signature=None, with_crc=False):
    """Converter function that converts and/or merges srec file(s) into new srec.

    Merge a list of srec files into one.
    Optionally converts unprotected srec files to crc-protected srec or signed srec files.
    These two types required to generate crc-protected or signed GBLs.

    :param srec_list: list of the input .srec filepaths that has to be merged
    :type srec_list: str list
    :param srec_out_name: the name of the output .srec file (without extension)
    :type srec_out_name: str
    :param signature: signature .pem filepath, defaults to None
    :type signature: str, optional
    :param with_crc: enable crc32 protect for output .srec, defaults to False
    :type with_crc: bool, optional
    :return: output .srec filepath
    :rtype: str
    """
    srec_out = reformat_path(os.path.join(OUTDIR, srec_out_name))
    cmd = [COMMANDER, 'convert']
    for sr in srec_list:
        cmd.append(sr)
    if with_crc:
        srec_out += '-crc'
        cmd.append('--crc')
    if signature is not None:
        srec_out += '-signed'
        cmd.extend(['--secureboot', '--keyfile', signature])
    srec_out += '.srec'
    cmd.extend(['-o', srec_out])
    response = run_cmd(cmd, verbose=VERBOSE)
    match_res = re.search(r'Writing to', response)
    if match_res and is_file_exist(srec_out):
        print(lvl.INFO, " ".join(srec_list) + " converted to " + srec_out)
        return srec_out
    else:
        print(lvl.WARN, "Could not convert " + " ".join(srec_list) + " to " + srec_out)
        print(lvl.INFO, "command response:", response)
        return None


def convert_srec_uartdfu(srec_list, srec_out_name):
    """Merge .srec files specialized for UARTDFU GBLs

    Convert/merge .srec file(s) for specialized UARTDFU GBLs.

    :param srec_list: list of input .srec filepaths
    :type srec_list: str list
    :param srec_out_name: name of the output .srec file (without extension)
    :type srec_out_name: str
    :return: output .srec
    :rtype: str
    """
    if len(srec_list) == 2:
        applo_srec = srec_list[0]
        app_srec = srec_list[1]
        if is_file_exist(applo_srec) and is_file_exist(app_srec):
            out_srec = convert_srec([applo_srec, app_srec], srec_out_name)
            if is_file_exist(out_srec):
                print(lvl.OKAY, f"{applo_srec} and {app_srec} converted to {out_srec}.")
                return out_srec
            else:
                print(lvl.WARN, f"Failed to convert {applo_srec} and {app_srec} to {out_srec}!")
                return None
        elif not is_file_exist(applo_srec) and is_file_exist(app_srec):
            out_srec = reformat_path(os.path.join(OUTDIR, srec_out_name + '.srec'))
            try:
                shutil.copy(app_srec, out_srec)
                print(lvl.OKAY, f"{app_srec} converted to {out_srec}.")
                return out_srec
            except shutil.SameFileError:
                print(lvl.ERR, "Source and destination files are the same! Aborting.")
            except PermissionError:
                print(lvl.ERR, "Permission denied!")
            except Exception as ex:
                print(lvl.ERR, f"Exception occured during execution of shutil.copy()!")
                print(lvl.ERR, f"{ex}\n")
            return None
        else:
            print(lvl.INFO, "Invalid .srec file list! None of the record contains actual files!")
            return None
    else:
        print(lvl.WARN, "Failed to convert srec files! At least 2 srecs required!")
        return None


def key_gen(key_name, encrypt_type='aes-ccm'):
    """Encryption/signature key generator function

    Generate encryption or signature keys with the selected encryption methods.
    To generate encrypt key, use 'ecc-p256'
    To generate signature keys, use the default 'aes-ccm'

    :param key_name: name of the output key (without extension)
    :type key_name: str
    :param encrypt_type: encryption method, defaults to 'aes-ccm'
    :type encrypt_type: str, optional
    :return: True in case of successful key generation, False otherwise
    :rtype: bool
    """
    REGEX_GENKEY = r'Using .* generation.*DONE'
    cmd = [COMMANDER, 'util', 'genkey', '--type']
    key_pf = '-key.txt'
    if encrypt_type != 'aes-ccm':
        REGEX_GENKEY = r'Writing private key.*DONE'
        encrypt_type = 'ecc-p256'
        key_pf = '-key.pem'
        pkey_pf = '-pubkey.pem'
        print(lvl.INFO,"Generate signature keys ...")
        cmd.extend([encrypt_type, '--privkey', key_name + key_pf, '--pubkey', key_name + pkey_pf])
    else:
        print(lvl.INFO,"Generate encryption key ...")
        cmd.extend([encrypt_type, '--outfile', key_name + key_pf])

    r = run_cmd(cmd, verbose=VERBOSE)
    match_r = re.search(REGEX_GENKEY, r, flags=re.DOTALL)
    if match_r and is_file_exist(key_name + key_pf):
        print(lvl.OKAY, ansi.gn + f"{key_name+key_pf}" + ansi.cl + " generated.")
        return True
    elif match_r and is_file_exist(key_name + key_pf) and is_file_exist(key_name + pkey_pf):
        print(lvl.OKAY,f"{key_name+key_pf}, {key_name+pkey_pf}.")
        return True
    else:
        print(lvl.WARN,"Could not generate key!")
    return False


def create_gbl_file(gbl_name, app_data, app_encrypt=None, app_sign=None, boot=None, cpress_a='', crc=False):
    """Create GBL file function

    Builds up and initiates GBL generator command for simplicity commander based on the input parameters.
    It is capable of the generation of: signed, encrypted, compressed and crc-protected GBL files.


    :param gbl_name: Base name of the output gbl file (without extension), postfixes will be added automatically: 
                     signed, encrypted versions will get -signed and/or -encrypted postfixes etc.
    :type gbl_name: str
    :param app_data: application data filepath (.srec or .gbl)
    :type app_data: str
    :param app_encrypt: encrypt-key filepath, defaults to None
    :type app_encrypt: str, optional
    :param app_sign: signature-key filepath, defaults to None
    :type app_sign: str, optional
    :param boot: bootloader image filepath, defaults to None
    :type boot: str, optional
    :param cpress_a: compression algorythm {lz4, lzma}, defaults to ''
    :type cpress_a: str, optional
    :param crc: generate protected GBL files with crc32 as well, defaults to False
    :type crc: bool, optional
    :return: filepath to the output gbl file or None in case of errors
    :rtype: str
    """
    if app_data is None and boot is None:
        print(lvl.ERR,"Could not find " + app_data + "! Aborting GBL generation!")
        return None
    cmd = [COMMANDER, 'gbl', 'create']
    
    if app_data is not None:
        cmd.extend(['--app', app_data])
    if app_sign is not None:
        gbl_name += '-signed'
        cmd.extend(['--sign', app_sign])
    if app_encrypt is not None:
        gbl_name += '-encrypted'
        cmd.extend(['--encrypt', app_encrypt])
    if crc:
        gbl_name += '-crc'
    if boot is not None:
        cmd.extend(['--bootloader', boot])
    if cpress_a in ('lz4', 'lzma'):
        gbl_name += '-' + cpress_a
        cmd.extend(['--compress', cpress_a])
    gbl_name += '.gbl'
    gbl_file = reformat_path(os.path.join(OUTDIR, gbl_name))
    cmd.insert(3, gbl_file)
    
    if is_file_exist(gbl_file):
        print(lvl.WARN, ansi.yl + f"{gbl_name}" + ansi.cl + " already exists!")
        backup_text = '_bkp' + dt.now().strftime("%Y-%m-%d-%H-%M-%S")
        os.rename(reformat_path(os.path.join(OUTDIR, gbl_name)), 
                  reformat_path(os.path.join(OUTDIR, gbl_name + backup_text)))
        print(lvl.INFO, f"{gbl_name} renamed to {gbl_name + backup_text}.")
        gbl_name = "New " + ansi.gn + gbl_name + ansi.cl
    else:
        gbl_name = ansi.gn + gbl_name + ansi.cl
    
    response = run_cmd(cmd, verbose=VERBOSE)
    match_res = re.search(r'Writing GBL file', response)
    if match_res:
        print(lvl.OKAY, gbl_name + " generated.\n")
        return gbl_file
    else:
        return None


def generate_gbls(name, srec, s1=True, boot_img=None, encrypt_k=None, sign_k=None,
                  cpress=True, cpress_m='both', uartdfu=False):
    """Generate multiple GBL files

    Generate all GBL files that can be generated based on the input parameters.
    It also differentiate between Series-1 and Series-2 devices.
    Apploader GBLs for example can only be used for Series-1 devices!

    :param name: base name for the GBL files
    :type name: str
    :param srec: application data .srec
    :type srec: str
    :param s1: Series-1 mode, defaults to True
    :type s1: bool, optional
    :param boot_img: path to the boot image .s37, defaults to None
    :type boot_img: str, optional
    :param encrypt_k: path to the encrypt key .txt, defaults to None
    :type encrypt_k: str, optional
    :param sign_k: path to the signature key .pem, defaults to None
    :type sign_k: str, optional
    :param cpress: generate compressed GBLs as well, defaults to True
    :type cpress: bool, optional
    :param cpress_m: compression method {'lz4', 'lzma', 'both'}, defaults to 'both'
    :type cpress_m: str, optional
    :param uartdfu: generate UARTDFU GBLs as well, defaults to False
    :type uartdfu: bool, optional
    """
    if uartdfu:
        # full.gbl
        create_gbl_file(name, srec)
        if cpress:
            if cpress_m in ('lz4', 'both'):
                # full-lz4.gbl
                create_gbl_file(name, srec, cpress_a='lz4')
            if cpress_m in ('lzma', 'both'):
                # full-lzma.gbl
                create_gbl_file(name, srec, cpress_a='lzma')
        
        if is_file_exist(encrypt_k):
            # full-encrypted.gbl
            create_gbl_file(name, srec, app_encrypt=encrypt_k)
            if cpress:
                if cpress_m in ('lz4', 'both'):
                    # full-encrypted-lz4.gbl
                    create_gbl_file(name, srec, app_encrypt=encrypt_k, cpress_a='lz4')
                if cpress_m in ('lzma', 'both'):
                    # full-encrypted-lzma.gbl
                    create_gbl_file(name, srec, app_encrypt=encrypt_k, cpress_a='lzma')
        
        apploader_srec = reformat_path(os.path.join(OUTDIR, APPLO_N + '-crc.srec'))
        app_srec = reformat_path(os.path.join(OUTDIR, APPLI_N + '-crc.srec'))

        srec_crc = convert_srec_uartdfu([apploader_srec, app_srec], name + '-crc')
        if not is_file_exist(srec_crc):
            print(lvl.WARN,f"Skipping {name}-crc.gbl generation!\n")
        else:
            # full-crc.gbl
            create_gbl_file(name, srec_crc, crc=True)

        apploader_s_srec = reformat_path(os.path.join(OUTDIR, APPLO_N + '-signed.srec'))
        app_s_srec = reformat_path(os.path.join(OUTDIR, APPLI_N + '-signed.srec'))

        srec_signed = convert_srec_uartdfu([apploader_s_srec, app_s_srec], name + '-signed')
        if srec_signed is None or not is_file_exist(srec_signed):
            print(lvl.WARN,f"Skipping {name}-signed.gbl generation!\n")
        else:
            # full-signed.gbl
            create_gbl_file(name, srec_signed, app_sign=sign_k)
            if is_file_exist(encrypt_k):
                # full-signed-encrypted.gbl
                create_gbl_file(name, srec_signed, app_encrypt=encrypt_k, app_sign=sign_k)

    else:
        if srec is None and not s1:
            if is_file_exist(boot_img, suppress_ex=True):
                # bootloader.gbl
                create_gbl_file(name, None, boot=boot_img)
            else:
                print(lvl.WARN, f"Missing bootloader image: {boot_img}!")
        else:
            srec_crc = convert_srec([srec], name, with_crc=True)
            if is_file_exist(boot_img, suppress_ex=True):
                if is_file_exist(sign_k, suppress_ex=True):
                    srec_signed = convert_srec([srec], name + '-bootloader', signature=sign_k)
                    if is_file_exist(encrypt_k, suppress_ex=True):
                        # appl*-bootloader-signed-encrypted.gbl
                        create_gbl_file(name + '-bootloader', srec_signed, app_encrypt=encrypt_k,
                                        app_sign=sign_k, boot=boot_img)
                    # appl*-bootloader-signed.gbl
                    create_gbl_file(name + '-bootloader', srec_signed, app_sign=sign_k, boot=boot_img)
                
                if is_file_exist(encrypt_k, suppress_ex=True):
                    # appl*-bootloader-encrypted.gbl
                    create_gbl_file(name + '-bootloader', srec, app_encrypt=encrypt_k, boot=boot_img)
                    # appl*-bootloader-encrypted-crc.gbl
                    create_gbl_file(name + '-bootloader', srec_crc, app_encrypt=encrypt_k, boot=boot_img, crc=True)
                    if cpress:
                        if cpress_m in ('lz4', 'both'):
                            # appl*-bootloader-encrypted-lz4.gbl
                            create_gbl_file(name + '-bootloader', srec, cpress_a='lz4',
                                            app_encrypt=encrypt_k, boot=boot_img)
                        if cpress_m in ('lzma', 'both'):
                            # appl*-bootloader-encrypted-lzma.gbl
                            create_gbl_file(name + '-bootloader', srec, cpress_a='lzma',
                                            app_encrypt=encrypt_k, boot=boot_img)
                # appl*-bootloader.gbl
                create_gbl_file(name + '-bootloader', srec, boot=boot_img)
                # appl*-bootloader-crc.gbl
                create_gbl_file(name + '-bootloader', srec_crc, boot=boot_img, crc=True)
                if cpress:
                    if cpress_m in ('lz4', 'both'):
                        # appl*-bootloader-lz4.gbl
                        create_gbl_file(name + '-bootloader', srec, cpress_a='lz4', boot=boot_img)
                    if cpress_m in ('lzma', 'both'):
                        # appl*-bootloader-lzma.gbl
                        create_gbl_file(name + '-bootloader', srec, cpress_a='lzma', boot=boot_img)

            if is_file_exist(sign_k, suppress_ex=True):
                srec_signed = convert_srec([srec], name, signature=sign_k)
                if is_file_exist(encrypt_k, suppress_ex=True):
                    # appl*-signed-encrypted.gbl
                    create_gbl_file(name, srec_signed, app_encrypt=encrypt_k, app_sign=sign_k)
                # appl*-signed.gbl
                create_gbl_file(name, srec_signed, app_sign=sign_k)

            if is_file_exist(encrypt_k, suppress_ex=True):
                # appl*-encrypted.gbl
                create_gbl_file(name, srec, app_encrypt=encrypt_k)
                # appl*-encrypted-crc.gbl
                create_gbl_file(name, srec_crc, app_encrypt=encrypt_k, crc=True)
                if cpress:
                    if cpress_m in ('lz4', 'both'):
                        # appl*-encrypted-lz4.gbl
                        create_gbl_file(name, srec, cpress_a='lz4', app_encrypt=encrypt_k)
                    if cpress_m in ('lzma', 'both'):
                        # appl*-encrypted-lzma.gbl
                        create_gbl_file(name, srec, cpress_a='lzma', app_encrypt=encrypt_k)
            # appl*.gbl
            create_gbl_file(name, srec)
            # appl*-crc.gbl
            create_gbl_file(name, srec_crc, crc=True)
            if cpress:
                if cpress_m in ('lz4', 'both'):
                    # appl*-lz4.gbl
                    create_gbl_file(name, srec, cpress_a='lz4')
                if cpress_m in ('lzma', 'both'):
                    # appl*-lzma.gbl
                    create_gbl_file(name, srec, cpress_a='lzma')                                    

def main():
    # Platform
    global PLATFORM

    # Utility paths
    global COMMANDER
    global OBJCOPY

    global OUTDIR
    
    # .axf or .out file to generate from
    global PRJ_ARTIFACT
    global SERIES_1
    
    global BOOT_S1_F
    global BOOT_S2_F

    SIGN_KEY_EXIST = False
    
    # file globals
    global SIGN_F
    global ENCRYPT_F

    # these flags define the generator phases
    # it comes from either command arguments or from the interactive mode
    SIGN = False
    ENCRYPT = False
    CPRESS = False
    CPRESS_METHOD = "lzma"
    UARTDFU = False

    separator = "-" * 80
    delay_display = 0.5

    # Before any work check the Python version ...
    if sys.version_info < (3, 6, 0):
        sys.stderr.write("ERROR: you need at least Python v3.6.0 to run this script!\n")
        sys.exit(1)

    builtins.print(LOGO)
    # Workaround for cmd.exe color codes - without this the bare-codes are visible only.
    os.system("")

    # Argument parse
    parser = argparse.ArgumentParser(
        prog="create_bl_files.py", description=f"Create Gecko Bootloader Files")
    # arguments
    parser.add_argument("-o", "--outdir", dest="outdir", type=str, help="output directory for the generated files", 
                        metavar="DIRECTORY")
    parser.add_argument("-w", "--overwrite", dest="overwrite_old", action="store_true", help="Overwrite existing GBLs")
    parser.add_argument("-i", "--interactive", dest="interactive", action="store_true", 
                        help="ignore args and give choices to the user")
    parser.add_argument("-k", "--key", dest="encryption_key", help="encryption key .txt", metavar="FILE", 
                        type=argparse.FileType('r', encoding='UTF-8'))
    parser.add_argument("-b", "--boot", dest="boot_img", help="bootloader.s37 file", metavar="FILE",
                        type=argparse.FileType('r', encoding='UTF-8'))
    parser.add_argument("-s", "--signature", dest="signature_key", help="signature key .pem", metavar="FILE",
                        type=argparse.FileType('r', encoding='UTF-8'))
    parser.add_argument("-a", "--all", dest="all", action="store_true", help="create every possible GBL files")
    parser.add_argument("-u", "--uartdfu", dest="uartdfu", action="store_true", help="create GBLs for UART DFU")
    parser.add_argument("-cpr", "--compress", dest="compress", choices=["lz4", "lzma", "both"], 
                        help="Compress GBLs with the chosen method")
    args = parser.parse_args()
            
    if args.outdir is not None and os.path.isdir(args.outdir):
        OUTDIR = reformat_path(args.outdir)
        print(lvl.OKAY, "Custom output directory set to " + ansi.yl + f"{OUTDIR}"+ ansi.cl + ".")
    else:
        if not os.path.isdir(OUTDIR):
            os.makedirs(OUTDIR)
            print(lvl.OKAY,f"Create {OUTDIR} directory.")
        else:
            print(lvl.OKAY,f"Directory {OUTDIR} already exists.")

    # reformat paths to the input files
    if args.encryption_key is not None:
        args.encryption_key = reformat_path(args.encryption_key)
    if args.boot_img is not None:
        args.boot_img = reformat_path(args.boot_img)
    if args.signature_key is not None:
        args.signature_key = reformat_path(args.signature_key)

    # Environment
    print(lvl.INFO,separator)
    print(lvl.INFO,"Check environment ...")
    print(lvl.INFO,separator)
    time.sleep(delay_display)

    PLATFORM = detect_platform()
    print(lvl.INFO,"Detected platform: " + ansi.yl + PLATFORM + ansi.cl)

    res = check_util_exist('commander', 'PATH_SCMD')
    if res is not None:
        COMMANDER = res
    else:
        sys.exit(1)

    res = check_util_exist('arm-none-eabi-objcopy', 'PATH_GCCARM')
    if res is not None:
        OBJCOPY = res
    else:
        sys.exit(1)

    builtins.print("")
    print(lvl.INFO,separator)
    print(lvl.INFO,"Check input files ...")
    print(lvl.INFO,separator)
    time.sleep(delay_display)

    axf = get_file_list(os.getcwd(), '.axf')
    out = get_file_list(os.getcwd(), '.out')

    artifacts_num = len(axf) + len(out)
    if artifacts_num > 1:
        print(lvl.WARN,f"Multiple build artifacts detected ({artifacts_num})!")
        if ALWAYS_SELECT_GCC_EXT:
            PRJ_ARTIFACT = reformat_path(axf[0])
        else:
            PRJ_ARTIFACT = reformat_path(out[0])
        print(lvl.WARN,f"Build artifact selected: {PRJ_ARTIFACT}")
        print(lvl.INFO,"Choose which to select automatically by changing the value of \'ALWAYS_SELECT_GCC_EXT\'!\n")
    elif artifacts_num == 1:
        if len(axf) != 0:
            PRJ_ARTIFACT = reformat_path(axf[0])
        if len(out) != 0:
            PRJ_ARTIFACT = reformat_path(out[0])
        print(lvl.OKAY,f"Build artifact selected: {PRJ_ARTIFACT}")
    else:
        print(lvl.ERR,"Neither *.axf or *.out build artifacts found!")
        print(lvl.INFO,ansi.yl+"Project built successfully before running this script?\n"+ansi.cl)
        sys.exit(1)
    
    if args.interactive == True:
        SIGN, ENCRYPT, CPRESS, CPRESS_METHOD, UARTDFU = interactive_menu(separator)
    elif args.interactive == False:
        if all(v is None or v == False for v in vars(args).values()):
            print(lvl.WARN, "No argument specified, using " + ansi.yl + "--all" + ansi.cl + " meaning:")
            AUTO_KEYGEN = True
            SIGN = True
            ENCRYPT = True
            CPRESS = True
            CPRESS_METHOD = "both"
            UARTDFU = True
            msg = ansi.yl + "ALL FEATURES ENABLED" + ansi.cl + ": "
            msg += "sign, encrypt, compress and generate UARTDFU GBLs too."
            print(lvl.WARN, msg)
            print(lvl.INFO, "Missing keys will be "+ansi.yl+"automatically "+ansi.cl+"generated!")
            time.sleep(delay_display)

        if args.all:
            SIGN = True
            ENCRYPT = True
            CPRESS = True
            CPRESS_METHOD = "both"
            UARTDFU = True
            msg = ansi.yl + "ALL FEATURES ENABLED" + ansi.cl + ": "
            msg += "sign, encrypt, compress and generate UARTDFU GBLs too."
            print(lvl.WARN, msg)
            print(lvl.INFO, "Missing keys will be automatically generated!")
            time.sleep(delay_display)
        else:
            if args.signature_key:
                SIGN = True
            if args.encryption_key:
                ENCRYPT = True
            if args.compress in ("lz4", "lzma", "both"):
                CPRESS = True
                CPRESS_METHOD = args.compress
            if args.uartdfu:
                UARTDFU = True
                
    time.sleep(delay_display)

    builtins.print("")
    print(lvl.INFO,separator)
    print(lvl.INFO,"Check bootloader image ...")
    print(lvl.INFO,separator)
    time.sleep(delay_display)

    print(lvl.OKAY,"Target device: ", end='')
    SERIES_1 = is_target_series_1(PRJ_ARTIFACT)
    if SERIES_1:
        builtins.print(ansi.gn + "Series-1\n" + ansi.cl)
    else:
        builtins.print(ansi.gn + "Series-2\n" + ansi.cl)
    
    if args.boot_img is not None:
        BOOT_EXIST = is_file_exist(args.boot_img)
        print(lvl.OKAY,f"Bootloader image added as argument: {args.boot_img}")
        if SERIES_1:
            BOOT_S1_F = args.boot_img
        else:
            BOOT_S2_F = args.boot_img
    elif args.interactive:
        print(lvl.INFO,"Display filedialog ...")
        root = tk.Tk()
        root.withdraw()
        if SERIES_1:
            w_title = "Select Series-1 bootloader .s37"
        else:
            w_title = "Select Series-2 bootloader .s37"
        boot_path = fd.askopenfile(initialdir=os.getcwd(), title=w_title)
        BOOT_EXIST = is_file_exist(boot_path.name, suppress_ex=True)
        if BOOT_EXIST:
            if SERIES_1:
                BOOT_S1_F = boot_path.name
            else:
                BOOT_S2_F = boot_path.name
            print(lvl.OKAY,"Selected a valid bootloader .s37 image.")
        else:
            print(lvl.ERR,"Invalid file has been selected as bootloader image!")
    else:
        print(lvl.INFO,"No boot image in command argument.")
        print(lvl.INFO,"Check current working directory ...\n")
        if SERIES_1:
            BOOT_EXIST = is_file_exist(BOOT_S1_F)
        else:
            BOOT_EXIST = is_file_exist(BOOT_S2_F)

    # show the compression related tip only in case all features shall be used or compression selected
    # according to the command-arguments, and interactive mode is not active
    if (args.all or args.compress in ("lzma", "lz4", "both")) and not args.interactive:
        print_tip(tip.COMPRESS)

    # if can not recognize bootloader, print out the tip on how to use it if interactive mode is not active
    if not BOOT_EXIST:
        BOOT_S1_F = None
        BOOT_S2_F = None
        print(lvl.INFO,"Bootloader addition will be skipped!\n")
        if not args.interactive:
            print_tip(tip.BOOT)
    else:
        print(lvl.OKAY,"Bootloader image detected.\n")
        time.sleep(delay_display)

    if SIGN:    
        builtins.print("")
        print(lvl.INFO,separator)
        print(lvl.INFO,"Check prerequisites for signed GBL generation ...")
        print(lvl.INFO,separator)
        time.sleep(delay_display)

        if args.signature_key is not None:
            SIGN_KEY_EXIST = is_file_exist(args.signature_key)
            if SIGN_KEY_EXIST:
                print(lvl.OKAY,f"Signature key added as argument: {args.signature_key}")
                SIGN_F = args.signature_key
            else:
                print(lvl.WARN, f"Invalid signature key in command argument: {args.signature_key}!")
                print(lvl.INFO, "Check current working directory ...")
                SIGN_KEY_EXIST = is_file_exist(SIGN_F)
        else:
            print(lvl.INFO, f"No signature key in command argument.")
            print(lvl.INFO, "Check current working directory ...")
            SIGN_KEY_EXIST = is_file_exist(SIGN_F)

        if not SIGN_KEY_EXIST:
            print(lvl.WARN,f"Could not detect {SIGN_F}!")
            if args.interactive:
                decision = print_question(f"Would you like to generate {SIGN_F} now?", delay=delay_display)
                if not decision:
                    SIGN_F = None
                    print(lvl.WARN,f"Will not generate {SIGN_F}!")
                    print(lvl.INFO,"Application signing will be skipped!\n")
                    time.sleep(delay_display)
                else:
                    time.sleep(delay_display)
                    # in this case the gbl generator function will check wether the key_gen really generated
                    # a valid signature key or not
                    SIGN_KEY_EXIST = key_gen(SIGN_N, encrypt_type='ecc-p256')
            elif args.all or AUTO_KEYGEN:
                # generate the signature keys automatically 
                SIGN_KEY_EXIST = key_gen(SIGN_N, encrypt_type='ecc-p256')
            else:
                print(lvl.WARN,f"Could not detect {SIGN_F}!")
                print(lvl.INFO,"Application signing will be skipped!\n")
                print_tip(tip.SIGN)
                SIGN_F = None
        else:
            print(lvl.OKAY,f"Detected {SIGN_F}.")
    else:
        SIGN_F = None

    if ENCRYPT:
        builtins.print("")
        print(lvl.INFO,separator)
        print(lvl.INFO,"Check prerequisites for encrypted GBL generation ...")
        print(lvl.INFO,separator)
        time.sleep(delay_display)

        ENCRYPT_KEY_EXIST = is_file_exist(ENCRYPT_F)
        if not ENCRYPT_KEY_EXIST:
            print(lvl.WARN,f"Could not detect {ENCRYPT_F}!")
            if args.interactive:
                decision = print_question(f"Would you like to generate {ENCRYPT_F} now?", delay=delay_display)
                if not decision:
                    ENCRYPT_F = None
                    print(lvl.WARN,f"Will not generate {ENCRYPT_F}!")
                    print(lvl.INFO,"Application encryption will be skipped!\n")
                    time.sleep(delay_display)
                else:
                    time.sleep(delay_display)
                    # in this case the gbl generator function will check wether the key_gen really generated
                    # a valid encryption key or not
                    ENCRYPT_KEY_EXIST = key_gen(ENCRYPT_N)
            elif args.all or AUTO_KEYGEN:
                # generate the encryption key automatically
                ENCRYPT_KEY_EXIST = key_gen(ENCRYPT_N)
            else:
                print(lvl.WARN,f"Could not detect {ENCRYPT_F}! Application signing will be skipped!")
                print_tip(tip.ENCRYPT)
                ENCRYPT_F = None
        else:
            print(lvl.OKAY,f"Detected {ENCRYPT_F}.")
    else:
        ENCRYPT_F = None

    if SERIES_1:
        builtins.print("")
        print(lvl.INFO, separator)
        print(lvl.INFO, "Generate apploader GBLs ...")
        print(lvl.INFO, separator)
        time.sleep(delay_display)
        applo_srec = extract_to_srec(APPLO_N, ['.text_apploader*'], PRJ_ARTIFACT, only_section=True)
        generate_gbls(APPLO_N, applo_srec, boot_img=BOOT_S1_F, encrypt_k=ENCRYPT_F, sign_k=SIGN_F)
    else:
        if BOOT_EXIST:
            builtins.print("")
            print(lvl.INFO, separator)
            print(lvl.INFO, "Generate bootloader GBL ...")
            print(lvl.INFO, separator)
            time.sleep(delay_display)
            generate_gbls(BOOTLO_N, None, s1=False, boot_img=BOOT_S2_F, cpress=False)

    builtins.print("")
    print(lvl.INFO, separator)
    print(lvl.INFO, "Generate application GBLs ...")
    print(lvl.INFO, separator)
    time.sleep(delay_display)
    
    # extract all sections except the .text_apploader* and .text_signature*
    app_srec = extract_to_srec(APPLI_N, ['.text_apploader*', '.text_signature*'], PRJ_ARTIFACT)
    if app_srec is not None:
        if SERIES_1:
            generate_gbls(APPLI_N, app_srec, boot_img=BOOT_S1_F, encrypt_k=ENCRYPT_F, sign_k=SIGN_F,
                              cpress=CPRESS, cpress_m=CPRESS_METHOD)
        else:
            generate_gbls(APPLI_N, app_srec, s1=False, boot_img=BOOT_S2_F, encrypt_k=ENCRYPT_F, 
                             sign_k=SIGN_F, cpress=CPRESS, cpress_m=CPRESS_METHOD)
    else:
        print(lvl.ERR, f"Could not create {APPLI_N}.srec!")
        print(lvl.ERR, "Exit program.")
        sys.exit(1)

    if UARTDFU:
        # for UART DFU compatible GBL extract every section except the .text_bootloader section into an srec
        uartdfu_srec = extract_to_srec(UARTDFU_N, ['.text_bootloader*'], PRJ_ARTIFACT)
        # generate UART DFU GBLs
        generate_gbls(UARTDFU_N, uartdfu_srec, encrypt_k=ENCRYPT_F, sign_k=SIGN_F, cpress=CPRESS, 
                      cpress_m=CPRESS_METHOD, uartdfu=True)

    if PURGE_SRECS:
        builtins.print("")
        print(lvl.INFO,separator)
        print(lvl.INFO,"Erase all temporary srec files ...")
        print(lvl.INFO,separator)
        print(lvl.INFO,"Note: set \'PURGE_SRECS\' to False to keep these files.")
        time.sleep(delay_display)
        files_to_erase = glob(OUTDIR + '/*.srec')
        for file in files_to_erase:
            try:
                os.remove(file)
            except:
                print(lvl.WARN,f"Could not erase {file}!")
        print(lvl.INFO,"Finished.")


if __name__ == "__main__":
    main()
