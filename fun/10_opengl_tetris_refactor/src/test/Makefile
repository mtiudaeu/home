COMMON_TEST_OUT = $(BUILD_PATH)run_test.out

RUN_TEST_DEP_EXEC = $(addprefix $(BUILD_PATH),test_run_test.o graphics_primitive_text.o graphics_shader.o graphics_context.o graphics_primitive_rectangle_2D.o graphics_ui_text.o test_test_primitive_text.o test_test_ui_text.o test_test_primitive_rectangle_2D.o)
RUN_TEST_DEP_EXEC_EMCC = $(RUN_TEST_DEP_EXEC:.o=.bc)

$(BUILD_PATH)run_test.out : $(RUN_TEST_DEP_EXEC)
	$(GCC) $^ -o $@ -lGL -lGLEW -lSDL2 -lSDL2_image
$(BUILD_PATH)run_test.html : $(RUN_TEST_DEP_EXEC_EMCC)
	$(EMCC) $^ -o $@ --use-preload-plugins --preload-file common 
