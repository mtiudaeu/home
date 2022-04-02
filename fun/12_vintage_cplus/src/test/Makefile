COMMON_TEST_OUT = $(BUILD_PATH)run_test.out

RUN_TEST_DEP_EXEC = $(addprefix $(BUILD_PATH),test_run_test.o test_test_common_str.o common_str.o test_test_common_log.o common_log.o test_test_common_dyn_buf.o common_dyn_buf.o)
RUN_TEST_DEP_EXEC_EMCC = $(RUN_TEST_DEP_EXEC:.o=.bc)

$(BUILD_PATH)run_test.out : $(RUN_TEST_DEP_EXEC)
	$(GCC) $^ -o $@ 
$(BUILD_PATH)run_test.html : $(RUN_TEST_DEP_EXEC_EMCC)
	$(EMCC) $^ -o $@ 
