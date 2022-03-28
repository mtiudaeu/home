MAIN_OUT = $(BUILD_PATH)main.out

MAIN_DEP_EXEC = $(addprefix $(BUILD_PATH), main_main.o common_str.o common_dyn_buf.o common_log.o graphic_context.o)
MAIN_DEP_EXEC_EMCC = $(MAIN_DEP_EXEC:.o=.bc)

$(BUILD_PATH)main.out : $(MAIN_DEP_EXEC)
	$(GCC) $^ -o $@ -lGL -lGLEW -lSDL2
$(BUILD_PATH)main.html : $(MAIN_DEP_EXEC_EMCC)
	$(EMCC) $^ -o $@ 
