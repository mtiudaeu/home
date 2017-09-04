include_directories("../git_submodule/easy-headers/include")
include_directories(".")

add_library(gl_lib STATIC gl/context.cpp)
target_link_libraries(gl_lib SDL2 GLEW)

add_executable(main main.cpp)
target_link_libraries(main gl_lib)
