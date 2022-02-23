TETRIS_OUT = $(BUILD_PATH)tetris.out

TETRIS_DEP_EXEC = $(addprefix $(BUILD_PATH),tetris_tetris.o tetris_piece.o tetris_board.o graphics_ui_text.o graphics_primitive_text.o  graphics_primitive_rectangle_2D.o graphics_shader.o graphics_context.o)
TETRIS_DEP_EXEC_EMCC = $(TETRIS_DEP_EXEC:.o=.bc)

$(BUILD_PATH)tetris.out : $(TETRIS_DEP_EXEC)
	$(GCC) $^ -o $@ -lGL -lGLEW -lSDL2 -lSDL2_image
$(BUILD_PATH)tetris.html : $(TETRIS_DEP_EXEC_EMCC)
	$(EMCC) $^ -o $@ --use-preload-plugins --preload-file common


