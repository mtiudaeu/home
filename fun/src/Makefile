#---------- ALL CONFIGURABLE INPUT ----------
BUILD_DIR = ../bin/
H_FILES_EXT="h"
C_FILES_EXT="cpp"

CFLAGS_ALL = -std=c++14 -Wall -Werror -Wextra -O2 -g -DROOT_PATH=\"$(BUILD_DIR)\" -fPIC

SHARED_LIBS_CFLAGS = -shared

#---------- REBUILD DEPENDANCY RULE ----------

DEP_MAKEFILE=$(BUILD_DIR)Makefile_dep

dep:
	mkdir -p $(BUILD_DIR)
	./build_dep.py $(BUILD_DIR) $(H_FILES_EXT) $(C_FILES_EXT) $(DEP_MAKEFILE) ALL_OBJECT_FILES CFLAGS_ALL

-include $(DEP_MAKEFILE)

#---------- TARGETS ----------
all : $(BUILD_DIR)main.out $(BUILD_DIR)module_manager.so $(BUILD_DIR)hello.so $(BUILD_DIR)context.so

$(BUILD_DIR)main.out : $(BUILD_DIR)main.o $(BUILD_DIR)module.o
	$(CXX) $(CFLAGS_ALL) $^ -o $@ -ldl

$(BUILD_DIR)module_manager.so : $(BUILD_DIR)module_manager.o $(BUILD_DIR)module.o
	$(CXX) $(CFLAGS_ALL) $(SHARED_LIBS_CFLAGS) $^ -o $@ -ldl

#MDTMP remove hello
$(BUILD_DIR)hello.so : $(BUILD_DIR)hello.o
	$(CXX) $(CFLAGS_ALL) $(SHARED_LIBS_CFLAGS) $< -o $@

$(BUILD_DIR)context.so : $(BUILD_DIR)context.o
	$(CXX) $(CFLAGS_ALL) $(SHARED_LIBS_CFLAGS) $< -o $@ -lGL -lGLEW -lSDL2 -lSDL2_image
#MDTMP validate library link above.

clean:
	rm $(BUILD_DIR)*

