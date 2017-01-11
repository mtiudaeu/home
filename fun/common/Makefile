default : gcc
gcc : gcc_targets
emcc : emcc_targets

# ---- Build Flags ----
# USE_SDL=2       : SDL2 Libraries
# USE_SDL_IMAGE=2 :
# --use-preload-plugins : Prevent format error with IMG_load from SDL_Image
EMCC = emcc -O2 -I. -DINCLUDE_RUN_TEST -Werror -s USE_SDL=2 -s USE_SDL_IMAGE=2 --use-preload-plugins
GCC = gcc -I. -g -DINCLUDE_RUN_TEST -Werror

# ---- Target Lists ----
TARGETS_ALL = $(BUILD_PATH)test_graphics.out
BUILD_PATH = bin/

all: gcc_targets emcc_targets
gcc_targets : $(TARGETS_ALL)
emcc_targets : $(TARGETS_ALL:.out=.html)

# ---- Dependancies ----
# Lower level dependancy to higher
# ---- TEST ----
TEST = test
TEST_DEP = test/test.c test/test.h
TEST_DEP_EMCC = $(TEST_DEP:.o=.bc)
# ---- GRAPHICS ----
# ---- GRAPHICS_SHADER ----
GRAPHICS_SHADER = shader
GRAPHICS_SHADER_DEP = graphics/shader.c graphics/shader.h log.h
GRAPHICS_SHADER_DEP_EMCC = $(GRAPHICS_SHADER_DEP:.o=.bc)
# ---- GRAPHICS_CONTEXT ----
GRAPHICS_CONTEXT = context
GRAPHICS_CONTEXT_DEP = graphics/context.c graphics/context.h log.h $(addprefix $(BUILD_PATH),$(TEST).o)
GRAPHICS_CONTEXT_DEP_EMCC = $(GRAPHICS_CONTEXT_DEP:.o=.bc)
# ---- GRAPHICS_TEXT ----
GRAPHICS_TEXT = text
GRAPHICS_TEXT_DEP = graphics/text/text.c graphics/text/text.h graphics/point.h log.h $(addprefix $(BUILD_PATH),$(GRAPHICS_SHADER).o $(TEST).o)
GRAPHICS_TEXT_DEP_EMCC = $(GRAPHICS_TEXT_DEP:.o=.bc)
# ---- TEST_GRAPHICS ----
TEST_GRAPHICS = test_graphics
TEST_GRAPHICS_DEP = graphics/test_graphics.c $(addprefix $(BUILD_PATH),$(GRAPHICS_CONTEXT).o $(GRAPHICS_TEXT).o $(TEST).o)
TEST_GRAPHICS_DEP_EMCC = $(TEST_GRAPHICS_DEP:.o=.bc)

TEST_GRAPHICS_DEP_EXEC = $(addprefix $(BUILD_PATH),test_graphics.o $(GRAPHICS_CONTEXT).o $(GRAPHICS_TEXT).o $(GRAPHICS_SHADER).o $(TEST).o)
TEST_GRAPHICS_DEP_EXEC_EMCC = $(TEST_GRAPHICS_DEP_EXEC:.o=.bc)

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
	$(EMCC) $^ -o $@ --preload-file assets/text/texture.f.glsl --preload-file assets/text/texture.v.glsl --preload-file assets/text/ASCII_tileset.png

# ---- clean ----
clean : 
	rm -f $(addprefix $(BUILD_PATH), *.o *.out *.js *.html *.bc *.mem *.data)




# ---- array ----
#test_array.out : array.o test.o
#	$(GCC) array.o test.o -o test_array.out
#
#array.o : array.h array.c test.o
#	$(GCC) -c array.c -o array.o

