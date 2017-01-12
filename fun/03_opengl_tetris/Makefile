TARGETS_ALL = $(BUILD_PATH)tetris.out
INCLUDE_TEST = -DNO_RUN_TEST

include common/Makefile

# ---- TETRIS ----
TETRIS = tetris
TETRIS_DEP = 03_opengl_tetris/tetris.c common/graphics/context.h $(GRAPHICS_TEXT_HEADER)
TETRIS_DEP_EMCC = $(TETRIS_DEP:.o=.bc)

TETRIS_DEP_EXEC = $(addprefix $(BUILD_PATH),$(TETRIS).o $(GRAPHICS_CONTEXT).o $(GRAPHICS_TEXT).o $(GRAPHICS_SHADER).o )
TETRIS_DEP_EXEC_EMCC = $(TETRIS_DEP_EXEC:.o=.bc)


$(BUILD_PATH)$(TETRIS).o : $(TETRIS_DEP)
	$(GCC) -c $< -o $@
$(BUILD_PATH)$(TETRIS).bc : $(TETRIS_DEP_EMCC)
	$(EMCC) -c $< -o $@

$(BUILD_PATH)$(TETRIS).out : $(TETRIS_DEP_EXEC)
	$(GCC) $^ -o $@ -lGL -lGLEW -lSDL2 -lSDL2_image
$(BUILD_PATH)$(TETRIS).html : $(TETRIS_DEP_EXEC_EMCC)
	$(EMCC) $^ -o $@ --preload-file common/assets/text/texture.f.glsl --preload-file common/assets/text/texture.v.glsl --preload-file common/assets/text/ASCII_tileset.png
