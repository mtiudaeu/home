#!/usr/bin/env python
#
# Usage
# python setup.py -p <install_path>
# example : python setup.py -p "/home/mathieu/.md_env"
# example : python setup.py -p "/magma/people/drapeaum/.md_env"

import tempfile, os, sys, getopt, subprocess, datetime

#---------------------------------------------------------------------
class EnvPath:
  def __init__(self, path):
    self.root = path
    self.bin = path + "/bin"
    self.share = path + "/share"
    self.env = path + "/env"

#---------------------------------------------------------------------
def process_call(cmd):
  subprocess.call(cmd)

#---------------------------------------------------------------------
# NOOP if directory doesn't exist
def folder_backup(src):
  if os.path.exists(src):
    timestamp = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
    backup_path = "%s.%s" % (src, timestamp)
    os.rename(src, backup_path)

#---------------------------------------------------------------------
def copy_env_folder(install_path):
  if "~" in install_path.root:
    raise Exception("Does not support '~' in environment path : " + install_path.root)

  folder_backup(install_path.root)

  process_call( ["mkdir", "-p", install_path.root ] )
  process_call( ["cp", "-r", "md_env/env", install_path.root] )

#---------------------------------------------------------------------
def on_success(install_path):
  print("copy the following into your ~/.bashrc")
  print("")
  print("export MD_ENV_PATH='" + install_path.root + "'")
  print("if [ -f $MD_ENV_PATH/env/bashrc ]; then")
  print("    . $MD_ENV_PATH/env/bashrc")
  print("fi")

#---------------------------------------------------------------------
def env_build(install_path):
  copy_env_folder(install_path)

#---------------------------------------------------------------------
def args_exit_error():
  print("Error : invalid arguments")
  args_exit_usage()

#---------------------------------------------------------------------
def args_exit_usage():
  print("python setup.py.py -p <path>")
  sys.exit()

#---------------------------------------------------------------------
def args_parse(argv):
  path=""
  try:
    opts, args = getopt.getopt(argv,"hp:",["path="])
  except getopt.GetoptError:
    args_exit_error()

  for opt, arg in opts:
    if opt == '-h':
      args_exit_usage()
    elif opt in ("-p", "--path"):
      path = arg

  if path is "":
    args_exit_error()

  return path

#---------------------------------------------------------------------
def main(argv):
  path = args_parse(argv)
  install_path = EnvPath(path)

  env_build(install_path)
  on_success(install_path)

#---------------------------------------------------------------------
if __name__ == "__main__":
  main(sys.argv[1:])
