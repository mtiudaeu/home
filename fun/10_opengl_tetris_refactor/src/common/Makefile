COMMON_TEST_OUT = $(BUILD_PATH)run_test.out

RUN_TEST_DEP_EXEC = $(addprefix $(BUILD_PATH),common_run_test.o graphics_primitive_text.o graphics_shader.o graphics_context.o graphics_primitive_rectangle_2D.o common_ui_ui_text.o)
RUN_TEST_DEP_EXEC_EMCC = $(RUN_TEST_DEP_EXEC:.o=.bc)

$(BUILD_PATH)run_test.out : $(RUN_TEST_DEP_EXEC)
	$(GCC) $^ -o $@ -lGL -lGLEW -lSDL2 -lSDL2_image
$(BUILD_PATH)run_test.html : $(RUN_TEST_DEP_EXEC_EMCC)
	$(EMCC) $^ -o $@ --use-preload-plugins --preload-file common 
