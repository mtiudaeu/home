include_directories("../git_submodule/easy-headers/include")
include_directories(".")

add_library(sdl_lib STATIC sdl/context.cpp)
target_link_libraries(sdl_lib SDL2 GLEW)

add_library(gl_lib STATIC gl/render.cpp gl/render_2d_texture.cpp gl/shader.cpp)
target_link_libraries(gl_lib GL SDL2 SDL2_image) 

add_executable(main main.cpp)
target_link_libraries(main sdl_lib gl_lib)
