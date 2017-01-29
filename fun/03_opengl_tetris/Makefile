TARGETS_ALL = $(BUILD_PATH)tetris.out
INCLUDE_TEST = -DNO_RUN_TEST

include common/Makefile

TETRIS_DEP_EXEC = $(addprefix $(BUILD_PATH),03_opengl_tetris_tetris.o common_ui_ui_text.o common_graphics_text_text.o  common_graphics_primitive_square_2D.o common_graphics_shader.o common_graphics_context.o)
TETRIS_DEP_EXEC_EMCC = $(TETRIS_DEP_EXEC:.o=.bc)

$(BUILD_PATH)tetris.out : $(TETRIS_DEP_EXEC)
	$(GCC) $^ -o $@ -lGL -lGLEW -lSDL2 -lSDL2_image
$(BUILD_PATH)tetris.html : $(TETRIS_DEP_EXEC_EMCC)
	$(EMCC) $^ -o $@ --preload-file common/assets/text/ASCII_tileset.png

include 03_opengl_tetris/Makefile_generated
