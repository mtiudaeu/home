TARGETS_ALL = $(BUILD_PATH)tetris.out
INCLUDE_TEST = -DNO_RUN_TEST

include common/Makefile

TETRIS_DEP_EXEC = $(addprefix $(BUILD_PATH),tetris_tetris.o tetris_piece.o tetris_board.o common_ui_ui_text.o common_graphics_text_text.o  common_graphics_primitive_rectangle_2D.o common_graphics_shader.o common_graphics_context.o)
TETRIS_DEP_EXEC_EMCC = $(TETRIS_DEP_EXEC:.o=.bc)

$(BUILD_PATH)tetris.out : $(TETRIS_DEP_EXEC)
	$(GCC) $^ -o $@ -lGL -lGLEW -lSDL2 -lSDL2_image
$(BUILD_PATH)tetris.html : $(TETRIS_DEP_EXEC_EMCC)
	$(EMCC) $^ -o $@ --use-preload-plugins --preload-file common

include Makefile_generated
