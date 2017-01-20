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

ifndef BUILD_PATH
BUILD_PATH = bin/
endif

# ---- Target Lists ----
ifndef TARGETS_ALL
TARGETS_ALL = $(BUILD_PATH)test_graphics.out
endif

all: gcc_targets emcc_targets
gcc_targets : $(TARGETS_ALL)
emcc_targets : $(TARGETS_ALL:.out=.html)

# ---- Dependancies ----
# Lower level dependancy to higher
# ---- TEST ----
TEST = test
TEST_DEP = common/test/test.c common/test/test.h
TEST_DEP_EMCC = $(TEST_DEP:.o=.bc)
# ---- GRAPHICS ----
# ---- GRAPHICS_SHADER ----
GRAPHICS_SHADER = shader
GRAPHICS_SHADER_DEP = common/graphics/shader.c common/graphics/shader.h common/log.h
GRAPHICS_SHADER_DEP_EMCC = $(GRAPHICS_SHADER_DEP:.o=.bc)
# ---- GRAPHICS_CONTEXT ----
GRAPHICS_CONTEXT = context
GRAPHICS_CONTEXT_DEP = common/graphics/context.c common/graphics/context.h common/log.h common/test/test.h
GRAPHICS_CONTEXT_DEP_EMCC = $(GRAPHICS_CONTEXT_DEP:.o=.bc)
# ---- GRAPHICS_TEXT ----
GRAPHICS_TEXT = text
GRAPHICS_TEXT_HEADER = common/graphics/text/text.h common/graphics/point.h
GRAPHICS_TEXT_DEP = common/graphics/text/text.c $(GRAPHICS_TEXT_HEADER) common/graphics/text/square_vertices.h common/graphics/text/square_texture.h common/log.h common/graphics/shader.h common/test/test.h 
GRAPHICS_TEXT_DEP_EMCC = $(GRAPHICS_TEXT_DEP:.o=.bc)
# ---- TEST_GRAPHICS ----
TEST_GRAPHICS = test_graphics
TEST_GRAPHICS_DEP = common/graphics/test_graphics.c common/test/test.h common/graphics/context.h $(GRAPHICS_TEXT_HEADER)
TEST_GRAPHICS_DEP_EMCC = $(TEST_GRAPHICS_DEP:.o=.bc)

TEST_GRAPHICS_DEP_EXEC = $(addprefix $(BUILD_PATH),$(TEST_GRAPHICS).o $(GRAPHICS_CONTEXT).o $(GRAPHICS_TEXT).o $(GRAPHICS_SHADER).o $(TEST).o)
TEST_GRAPHICS_DEP_EXEC_EMCC = $(TEST_GRAPHICS_DEP_EXEC:.o=.bc)
# ---- UI_TEXT ----
UI_TEXT = ui_text
UI_TEXT_HEADER = common/ui/ui_text.h common/graphics/point.h
UI_TEXT_DEP = common/ui/ui_text.c $(UI_TEXT_HEADER) $(GRAPHICS_TEXT_HEADER) common/log.h
UI_TEXT_DEP_EMCC = $(UI_TEXT_DEP:.o=.bc)

# ---- Objects ----
# ---- TEST ----
$(BUILD_PATH)$(TEST).o : $(TEST_DEP)
	$(GCC) -c $< -o $@
$(BUILD_PATH)$(TEST).bc : $(TEST_DEP_EMCC)
	$(EMCC) -c $< -o $@
# ---- GRAPHICS ----
# ---- GRAPHICS_SHADER ----
$(BUILD_PATH)$(GRAPHICS_SHADER).o : $(GRAPHICS_SHADER_DEP)
	$(GCC) -c $< -o $@
$(BUILD_PATH)$(GRAPHICS_SHADER).bc : $(GRAPHICS_SHADER_DEP_EMCC)
	$(EMCC) -c $< -o $@
# ---- GRAPHICS_CONTEXT ----
$(BUILD_PATH)$(GRAPHICS_CONTEXT).o : $(GRAPHICS_CONTEXT_DEP)
	$(GCC) -c $< -o $@
$(BUILD_PATH)$(GRAPHICS_CONTEXT).bc : $(GRAPHICS_CONTEXT_DEP_EMCC)
	$(EMCC) -c $< -o $@
# ---- GRAPHICS_TEXT ----
$(BUILD_PATH)$(GRAPHICS_TEXT).o : $(GRAPHICS_TEXT_DEP)
	$(GCC) -c $< -o $@
$(BUILD_PATH)$(GRAPHICS_TEXT).bc : $(GRAPHICS_TEXT_DEP_EMCC)
	$(EMCC) -c $< -o $@
# ---- TEST_GRAPHICS ----
$(BUILD_PATH)$(TEST_GRAPHICS).o : $(TEST_GRAPHICS_DEP)
	$(GCC) -c $< -o $@
$(BUILD_PATH)$(TEST_GRAPHICS).bc : $(TEST_GRAPHICS_DEP_EMCC)
	$(EMCC) -c $< -o $@

$(BUILD_PATH)$(TEST_GRAPHICS).out : $(TEST_GRAPHICS_DEP_EXEC)
	$(GCC) $^ -o $@ -lGL -lGLEW -lSDL2 -lSDL2_image
$(BUILD_PATH)$(TEST_GRAPHICS).html : $(TEST_GRAPHICS_DEP_EXEC_EMCC)
	$(EMCC) $^ -o $@ --preload-file common/assets/text/texture.f.glsl --preload-file common/assets/text/texture.v.glsl --preload-file common/assets/text/ASCII_tileset.png

# ---- UI_TEXT ----
$(BUILD_PATH)$(UI_TEXT).o : $(UI_TEXT_DEP)
	$(GCC) -c $< -o $@
$(BUILD_PATH)$(UI_TEXT).bc : $(UI_TEXT_DEP_EMCC)
	$(EMCC) -c $< -o $@

# ---- clean ----
clean : 
	rm -f $(addprefix $(BUILD_PATH), *.o *.out *.js *.html *.bc *.mem *.data)

