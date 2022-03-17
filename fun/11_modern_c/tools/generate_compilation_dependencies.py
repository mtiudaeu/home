#!/usr/bin/env python2

# Usage :
# ./generate_compilation_dependencies.py src > Makefile_generated
#
# Find all .h and .c file and extract compilation depedencies.

import sys, subprocess

BUILD_PATH="../bin/"

def main():
  dir_path = sys.argv[1]

  # Get all .h files
  output = subprocess.check_output(["find", dir_path, "-name", "*.h"])
  output = output.replace("./","")
  h_files = output.split()
  # Extract dependencies
  build_extract_rules(h_files)

  # Get all .c files
  output = subprocess.check_output(["find", dir_path, "-name", "*.c"])
  output = output.replace("./","")
  c_files = output.split()
  # Extract dependencies
  build_extract_rules(c_files)
  # Build object rules.
  build_object_rules(c_files)


def file_path_to_target(file_path):
  return BUILD_PATH + file_path.replace("/","_")

def build_object_rules(c_file_path_list):
  for c_file_path in c_file_path_list:
    c_file_target = file_path_to_target(c_file_path)
    o_file_target = c_file_target.replace(".c", ".o")
    print(o_file_target + ": " + c_file_path + " " + c_file_target )
    print("\t$(GCC) -c $< -o $@")
    bc_file_target = c_file_target.replace(".c", ".bc")
    print(bc_file_target + ": " + c_file_path + " " + c_file_target )
    print("\t$(EMCC) -c $< -o $@")
    
def build_extract_rules(file_path_list):
  for file_path in file_path_list:
    p1 = subprocess.Popen(["grep", "#include", file_path], stdout=subprocess.PIPE)
    p2 = subprocess.Popen(["grep", "-v", "<"], stdin=p1.stdout, stdout=subprocess.PIPE)
    p1.stdout.close()  # Allow p1 to receive a SIGPIPE if p2 exits.
    include_files = p2.communicate()[0]
    include_files = include_files.replace("#include ","")
    include_files = include_files.replace("\"","")
    include_files = include_files.replace("\n"," ")
    include_files = include_files.split()
    include_files = [file_path_to_target(include_file) for include_file in include_files]

    include_files = " ".join(include_files)
    file_target = file_path_to_target(file_path)

    print(file_target + ": " + file_path + " " + include_files)
    print("\ttouch " + file_target)

main()
