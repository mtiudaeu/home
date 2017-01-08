default : all

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
# ---- test ----
TEST_NAME = test
TEST_DEP = test/test.c test/test.h
TEST_DEP_EMCC = $(TEST_DEP:.o=.bc)
# ---- graphics ----
# ---- graphics shader ----
SHADER_NAME = shader
SHADER_DEP = graphics/shader.c graphics/shader.h log.h
SHADER_DEP_EMCC = $(SHADER_DEP:.o=.bc)
# ---- graphics context ----
CONTEXT_NAME = context
CONTEXT_DEP = graphics/context.c graphics/context.h log.h $(addprefix $(BUILD_PATH),test.o)
CONTEXT_DEP_EMCC = $(CONTEXT_DEP:.o=.bc)
# ---- graphics text ----
TEXT_NAME = text
TEXT_DEP = graphics/text.c graphics/text.h graphics/point.h log.h $(addprefix $(BUILD_PATH),shader.o test.o)
TEXT_DEP_EMCC = $(TEXT_DEP:.o=.bc)
# ---- graphics test all ----
TEST_GRAPHICS_NAME = test_graphics
TEST_GRAPHICS_DEP = graphics/test_graphics.c $(addprefix $(BUILD_PATH),context.o text.o test.o)
TEST_GRAPHICS_DEP_EMCC = $(TEST_GRAPHICS_DEP:.o=.bc)

TEST_GRAPHICS_DEP_EXEC = $(addprefix $(BUILD_PATH),test_graphics.o context.o text.o shader.o test.o)
TEST_GRAPHICS_DEP_EXEC_EMCC = $(TEST_GRAPHICS_DEP_EXEC:.o=.bc)

# ---- test ----
$(BUILD_PATH)$(TEST_NAME).o : $(TEST_DEP)
	$(GCC) -c $< -o $@
$(BUILD_PATH)$(TEST_NAME).bc : $(TEST_DEP_EMCC)
	$(EMCC) -c $< -o $@
# ---- graphics ----
# ---- graphics shader ----
$(BUILD_PATH)$(SHADER_NAME).o : $(SHADER_DEP)
	$(GCC) -c $< -o $@
$(BUILD_PATH)$(SHADER_NAME).bc : $(SHADER_DEP_EMCC)
	$(EMCC) -c $< -o $@
# ---- graphics context ----
$(BUILD_PATH)$(CONTEXT_NAME).o : $(CONTEXT_DEP)
	$(GCC) -c $< -o $@
$(BUILD_PATH)$(CONTEXT_NAME).bc : $(CONTEXT_DEP_EMCC)
	$(EMCC) -c $< -o $@
# ---- graphics text ----
$(BUILD_PATH)$(TEXT_NAME).o : $(TEXT_DEP)
	$(GCC) -c $< -o $@
$(BUILD_PATH)$(TEXT_NAME).bc : $(TEXT_DEP_EMCC)
	$(EMCC) -c $< -o $@
# ---- graphics test all ----
$(BUILD_PATH)$(TEST_GRAPHICS_NAME).o : $(TEST_GRAPHICS_DEP)
	$(GCC) -c $< -o $@
$(BUILD_PATH)$(TEST_GRAPHICS_NAME).bc : $(TEST_GRAPHICS_DEP_EMCC)
	$(EMCC) -c $< -o $@

$(BUILD_PATH)$(TEST_GRAPHICS_NAME).out : $(TEST_GRAPHICS_DEP_EXEC)
	$(GCC) $^ -o $@ -lGL -lGLEW -lSDL2 -lSDL2_image
$(BUILD_PATH)$(TEST_GRAPHICS_NAME).html : $(TEST_GRAPHICS_DEP_EXEC_EMCC)
	$(EMCC) $^ -o $@ --preload-file test/assets/text.v.glsl --preload-file test/assets/text.f.glsl --preload-file test/assets/ASCII_tileset.png

# ---- clean ----
clean : 
	rm -f $(addprefix $(BUILD_PATH), *.o *.out *.js *.html *.bc *.mem *.data)




# ---- array ----
#test_array.out : array.o test.o
#	$(GCC) array.o test.o -o test_array.out
#
#array.o : array.h array.c test.o
#	$(GCC) -c array.c -o array.o

