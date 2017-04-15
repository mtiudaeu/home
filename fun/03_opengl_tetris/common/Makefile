common_default : gcc
gcc : gcc_targets
emcc : emcc_targets

# ---- Build Flags ----
# USE_SDL=2       : SDL2 Libraries
# USE_SDL_IMAGE=2 :
# --use-preload-plugins : Prevent format error with IMG_load from SDL_Image
ifndef INCLUDE_TEST
INCLUDE_TEST = -DINCLUDE_RUN_TEST
endif
EMCC = emcc -O2 -I. $(INCLUDE_TEST) -Werror -s USE_SDL=2 -s USE_SDL_IMAGE=2 --use-preload-plugins
GCC = gcc -I. -g $(INCLUDE_TEST) -Werror

BUILD_PATH = bin/

# ---- Target Lists ----
ifndef TARGETS_ALL
TARGETS_ALL = $(BUILD_PATH)run_test.out
endif

all: gcc_targets emcc_targets
gcc_targets : $(TARGETS_ALL)
emcc_targets : $(TARGETS_ALL:.out=.html)

RUN_TEST_DEP_EXEC = $(addprefix $(BUILD_PATH),common_run_test.o common_graphics_text_text.o common_graphics_shader.o common_graphics_context.o common_graphics_primitive_rectangle_2D.o common_ui_ui_text.o)
RUN_TEST_DEP_EXEC_EMCC = $(RUN_TEST_DEP_EXEC:.o=.bc)

$(BUILD_PATH)run_test.out : $(RUN_TEST_DEP_EXEC)
	$(GCC) $^ -o $@ -lGL -lGLEW -lSDL2 -lSDL2_image
$(BUILD_PATH)run_test.html : $(RUN_TEST_DEP_EXEC_EMCC)
	$(EMCC) $^ -o $@ --preload-file common/assets/text/tileset.png --preload-file common/assets/tmp/tetris.png

# ---- clean ----
clean : 
	rm -f $(addprefix $(BUILD_PATH), *.o *.out *.js *.html *.bc *.mem *.data *.c *.h)
