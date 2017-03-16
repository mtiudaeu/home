#!/usr/bin/env python

import sys, subprocess

BUILD_PATH="bin/"

def file_path_to_target(file_path):
  return BUILD_PATH + file_path.replace("/","_")

def build_object_rules(c_file_path_list, make_file_target):
  global c_files_ext
  for c_file_path in c_file_path_list:
    c_file_target = file_path_to_target(c_file_path)
    o_file_target = c_file_target.replace(c_files_ext, ".o")
    make_file_target.write(o_file_target + ": " + c_file_path + " " + c_file_target + "\n")
    make_file_target.write("\t$(CXX) -c $< -o $@\n")
    
def build_extract_rules(file_path_list, make_file_target):
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

    make_file_target.write(file_target + ": " + file_path + " " + include_files + "\n")
    make_file_target.write("\ttouch " + file_target + "\n")

build_dir = sys.argv[1] 
h_files_ext = sys.argv[2] 
c_files_ext = sys.argv[3] 
target_file_path = sys.argv[4] 

make_file_target = open(target_file_path, 'w')

output = subprocess.check_output(["find", ".", "-name", "*."+h_files_ext])
output = output.replace("./","")
h_files = output.split()
build_extract_rules(h_files, make_file_target)

output = subprocess.check_output(["find", ".", "-name", "*."+c_files_ext])
output = output.replace("./","")
c_files = output.split()
build_extract_rules(c_files, make_file_target)
build_object_rules(c_files, make_file_target)

make_file_target.close()

