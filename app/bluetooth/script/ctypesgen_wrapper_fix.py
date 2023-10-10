#!/usr/bin/env python3

import os
import sys
import argparse
import re

SECTION_1_ORIG = r'(\w+) \= os\.path\.abspath\((\1)\)'
SECTION_1_REPL = ' = os.path.abspath(os.path.join(os.path.dirname(__file__), '

SECTION_2_ORIG = 'add_library_search_dirs([])'
SECTION_2_REPL = 'add_library_search_dirs(["./lib"])'

SECTION_3_ORIG = '# No libraries'
SECTION_3_REPL = '# Begin libraries\n'\
                 '\n'\
                 'n = os.path.splitext(os.path.basename(__file__))[0]\n'\
                 'if n.endswith("_wrapper"):\n'\
                 '    n = n[:-len("_wrapper")]\n'\
                 'p = sys.platform\n'\
                 'if p == "darwin":\n'\
                 '    _libs["{:s}.dylib".format(n)] = load_library(n)\n'\
                 'elif (p == "cygwin" or p == "win32" or p == "msys"):\n'\
                 '    _libs["{:s}.dll".format(n)] = load_library(n)\n'\
                 '# Posix\n'\
                 'else:\n'\
                 '    _libs["{:s}.so".format(n)] = load_library(n)\n'\
                 '\n'\
                 '# End libraries'

def main():
    parser = argparse.ArgumentParser(
        description="ctypesgen Python wrapper fix")
    parser.add_argument(
        "file",
        help="Path to Python wrapper file to fix")
    parser.add_argument(
        "-v",
        action="store_true",
        help="verbose")
    args = parser.parse_args()
    pf = os.path.normpath(os.path.join(os.getcwd(), args.file))
    if args.v:
        print("Python wrapper file to fix: {:s}".format(pf))
    try:
        with open(pf, "r") as f:
            c = f.read()
    except FileNotFoundError:
        print("Python wrapper file not found: {:s}".format(pf))
        sys.exit(1)
    ret = re.search(SECTION_1_ORIG, c)
    if ret == None:
        print("'{:s}' not found".format(SECTION_1_ORIG))
        sys.exit(2)
    variable = ret.group(0).split()[0]
    cm = re.sub(SECTION_1_ORIG, variable + SECTION_1_REPL + variable + "))", c)
    if cm == c:
        print("'{:s}' could not change".format(SECTION_1_ORIG))
        sys.exit(2)
    c = cm
    cm = c.replace(SECTION_2_ORIG, SECTION_2_REPL, 1)
    if cm == c:
        print("'{:s}' not found".format(SECTION_2_ORIG))
        sys.exit(3)
    c = cm
    cm = c.replace(SECTION_3_ORIG, SECTION_3_REPL, 1)
    if cm == c:
        print("'{:s}' not found".format(SECTION_3_ORIG))
        sys.exit(4)
    try:
        with open(pf, "w") as f:
            f.write(cm)
    except FileNotFoundError:
        print("Python wrapper file not found: {:s}".format(pf))
        sys.exit(5)

if __name__ == "__main__":
    main()
