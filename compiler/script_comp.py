# Will take in a script source file and compile it into the script definition
# and virtual machine instruction file.

import argparse
import os
import sys
import re

# allows the script file to be entered as well as custom output locations
parser = argparse.ArgumentParser(description='Compile script source file')
parser.add_argument('source',
                    help='Script source file (.helis)')
parser.add_argument('--outdef',
                    help='Output script definition file (.helidef)',
                    required=False)
parser.add_argument('--outvmi',
                    help='Output script VM instruction file (.heli)',
                    required=False)
args = parser.parse_args()

# removes the last extension of the source file
script_name_no_extension = args.source.rsplit('.', 1)[0]

# if custom output locations are not provided, will be generated
source_file_path = args.source
out_def_file_path = args.outdef \
    if args.outdef is not None else \
    script_name_no_extension + '.helidef'
out_vm_instr_path = args.outvmi \
    if args.outvmi is not None else \
    script_name_no_extension + '.heli'

print('Compiler will work with following files:')
print('\tInput script file:', source_file_path)
print('\tOut def file:', out_def_file_path)
print('\tOut def VM instr file:', out_vm_instr_path)

print()  # newline

if not os.path.isfile(source_file_path):
    print('Cannot file input source file:', source_file_path)
    sys.exit(1)  # error

# obtains the lines in the script file
with open(source_file_path, 'r') as file:
    source_file_comments_lines = file.readlines()

# removes anything after comments on a line
source_file_lines = [line.split('%')[0].strip()
                     for line in source_file_comments_lines]
source_file = ''.join((line + '\n') for line in source_file_lines)

print('Source file:')
print(source_file)

#