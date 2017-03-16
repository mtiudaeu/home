DEP_MAKEFILE=$(BUILD_DIR)Makefile_dep

gen_dep:
	mkdir -p $(BUILD_DIR)
	./make/build_dep.py $(BUILD_DIR) $(H_FILES_EXT) $(C_FILES_EXT) $(DEP_MAKEFILE) ALL_OBJECT_FILES

-include $(DEP_MAKEFILE)
