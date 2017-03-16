#!/usr/bin/env python

import sys, subprocess

def file_path_to_target(file_path):
  global build_dir

  return build_dir + file_path.replace("/","_")

def build_object_rules(c_file_path_list):
  global c_file_ext
  global makefile_path

  for c_file_path in c_file_path_list:
    c_file_target = file_path_to_target(c_file_path)
    o_file_target = c_file_target.replace(c_file_ext, ".o")
    makefile_path.write(o_file_target + ": " + c_file_path + " " + c_file_target + "\n")
    makefile_path.write("\t$(CXX) -c $< -o $@\n")
    
def build_extract_rules(file_path_list):
  global makefile_path

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

    makefile_path.write(file_target + ": " + file_path + " " + include_files + "\n")
    makefile_path.write("\ttouch " + file_target + "\n")

build_dir = sys.argv[1] 
h_file_ext = sys.argv[2] 
c_file_ext = sys.argv[3] 
makefile_path = open(sys.argv[4], 'w')

p = subprocess.check_output(["find", ".", "-name", "*."+h_file_ext])
p = p.replace("./","")
h_files = p.split()
build_extract_rules(h_files)

p = subprocess.check_output(["find", ".", "-name", "*."+c_file_ext])
p = p.replace("./","")
c_files = p.split()
build_extract_rules(c_files)
build_object_rules(c_files)

makefile_path.close()

