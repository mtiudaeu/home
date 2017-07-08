#---------- ALL CONFIGURABLE INPUT ----------
BUILD_DIR = ../bin/
H_FILES_EXT="h"
C_FILES_EXT="cpp"

#DEFINES = -DROOT_PATH=\"$(BUILD_DIR)\"
DEFINES = -DROOT_PATH=\"$(BUILD_DIR)\" -DLOG_DEBUG_ENABLED
CFLAGS_ALL = -I. -std=c++14 -Wall -Werror -Wextra -O2 -g -fPIC $(DEFINES)

SHARED_LIBS_CFLAGS = -shared

#---------- TARGETS ----------
ALL_OBJECTS = main.out core_module_manager.so game_context.so game_render.so game_catch_event.so game_update.so
ALL_OBJECTS_PATH = $(addprefix $(BUILD_DIR), $(ALL_OBJECTS))

build : $(ALL_OBJECTS_PATH:.so=.so.build)
deploy : $(ALL_OBJECTS_PATH)

#---------- DEPENDANCY RULES ----------
DEP_MAKEFILE=$(BUILD_DIR)Makefile_dep
-include $(DEP_MAKEFILE)

dep:
	mkdir -p $(BUILD_DIR)
	./build_dep.py $(BUILD_DIR) $(H_FILES_EXT) $(C_FILES_EXT) $(DEP_MAKEFILE) ALL_OBJECT_FILES CFLAGS_ALL

#---------- LIBRARIES BUILD & LINK ----------
$(BUILD_DIR)main.out : $(BUILD_DIR)main.o $(BUILD_DIR)data_data_manager.o
	$(CXX) $(CFLAGS_ALL) $^ -o $@ -ldl

$(BUILD_DIR)core_module_manager.so.build : $(BUILD_DIR)core_module_manager.o $(BUILD_DIR)data_data_manager.o
	$(CXX) $(CFLAGS_ALL) $(SHARED_LIBS_CFLAGS) $^ -o $@ -lGLEW -lGL

$(BUILD_DIR)game_context.so.build : $(BUILD_DIR)game_context.o
	$(CXX) $(CFLAGS_ALL) $(SHARED_LIBS_CFLAGS) $< -o $@ -lGLEW -lSDL2

$(BUILD_DIR)game_catch_event.so.build : $(BUILD_DIR)game_catch_event.o $(BUILD_DIR)data_data_manager.o
	$(CXX) $(CFLAGS_ALL) $(SHARED_LIBS_CFLAGS) $^ -o $@ -lSDL2

$(BUILD_DIR)game_render.so.build : $(BUILD_DIR)game_render.o $(BUILD_DIR)data_data_manager.o
	$(CXX) $(CFLAGS_ALL) $(SHARED_LIBS_CFLAGS) $^ -o $@ -lGLEW -lGL

$(BUILD_DIR)game_update.so.build : $(BUILD_DIR)game_update.o $(BUILD_DIR)data_data_manager.o
	$(CXX) $(CFLAGS_ALL) $(SHARED_LIBS_CFLAGS) $^ -o $@ -lSDL2

#---------- MOVE TO FINAL TARGET ----------
%.so : %.so.build
	mv $@.build $@
	cp $@ $@.build
	touch $@

#---------- CLEANING ----------
clean:
	rm $(BUILD_DIR)*

