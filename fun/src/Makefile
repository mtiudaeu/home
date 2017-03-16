#---------- ALL CONFIGURABLE INPUT ----------
BUILD_DIR = ../bin/
H_FILES_EXT="h"
C_FILES_EXT="cpp"

CFLAGS_ALL = -std=c++14 -Wall -Werror -Wextra -O2 -g #flags for every object and target

#MDTMP
#SHARED_LIBS_CFLAGS = -fPIC -shared
SHARED_LIBS_CFLAGS = -fPIC -shared
MAIN_LDLIBS = -ldl

#---------- MDTMP ----------

DEP_MAKEFILE=$(BUILD_DIR)Makefile_dep

gen_dep:
	mkdir -p $(BUILD_DIR)
	./make/build_dep.py $(BUILD_DIR) $(H_FILES_EXT) $(C_FILES_EXT) $(DEP_MAKEFILE) ALL_OBJECT_FILES CFLAGS_ALL

-include $(DEP_MAKEFILE)

#---------- MDTMP ----------
#MDTMP
#all : $(ALL_OBJECT_FILES)
all : main.out hello.so

hello.so : $(BUILD_DIR)hello.o
	$(CXX) $(CFLAGS_ALL) $(SHARED_LIBS_CFLAGS) $< -o $@

main.out : $(BUILD_DIR)main.o $(BUILD_DIR)module.o
	$(CXX) $(CFLAGS_ALL) $^ -o $@ $(MAIN_LDLIBS)

#clean:
#	rm *.so *.o *.out *.html *.bc *.mem *.js

