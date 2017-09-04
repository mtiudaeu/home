include_directories("../git_submodule/easy-headers/include")
include_directories(".")

add_library(sdl_lib STATIC sdl/context.cpp)
target_link_libraries(sdl_lib SDL2 GLEW)

add_executable(main main.cpp)
target_link_libraries(main sdl_lib)
