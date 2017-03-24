#---------- ALL CONFIGURABLE INPUT ----------
BUILD_DIR = ../bin/
H_FILES_EXT="h"
C_FILES_EXT="cpp"

#DEFINES = -DROOT_PATH=\"$(BUILD_DIR)\"
DEFINES = -DROOT_PATH=\"$(BUILD_DIR)\" -DLOG_DEBUG_ENABLED
CFLAGS_ALL = -std=c++14 -Wall -Werror -Wextra -O2 -g -fPIC $(DEFINES)

SHARED_LIBS_CFLAGS = -shared

#---------- TARGETS ----------
all : $(BUILD_DIR)main.out $(BUILD_DIR)module_manager.so $(BUILD_DIR)context.so
test : $(BUILD_DIR)main.out $(BUILD_DIR)module_manager.so.tmp $(BUILD_DIR)context.so.tmp

#---------- DEPENDANCY RULES ----------
DEP_MAKEFILE=$(BUILD_DIR)Makefile_dep
-include $(DEP_MAKEFILE)

dep:
	mkdir -p $(BUILD_DIR)
	./build_dep.py $(BUILD_DIR) $(H_FILES_EXT) $(C_FILES_EXT) $(DEP_MAKEFILE) ALL_OBJECT_FILES CFLAGS_ALL

#---------- LIBRARIES ----------
$(BUILD_DIR)main.out : $(BUILD_DIR)main.o $(BUILD_DIR)module.o
	$(CXX) $(CFLAGS_ALL) $^ -o $@ -ldl

$(BUILD_DIR)module_manager.so.tmp : $(BUILD_DIR)module_manager.o $(BUILD_DIR)module.o
	$(CXX) $(CFLAGS_ALL) $(SHARED_LIBS_CFLAGS) $^ -o $@ -ldl

$(BUILD_DIR)context.so.tmp : $(BUILD_DIR)context.o
	$(CXX) $(CFLAGS_ALL) $(SHARED_LIBS_CFLAGS) $< -o $@ -lGLEW -lSDL2

$(BUILD_DIR)module_manager.so : $(BUILD_DIR)module_manager.so.tmp
	mv $@.tmp $@
$(BUILD_DIR)context.so : $(BUILD_DIR)context.so.tmp
	mv $@.tmp $@

#---------- CLEANING ----------
clean:
	rm $(BUILD_DIR)*

