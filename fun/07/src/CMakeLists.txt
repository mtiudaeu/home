include_directories(".")


add_library(sdl_lib STATIC sdl/SDLWrapper.cpp)
target_link_libraries(sdl_lib SDL2 GLEW)

add_library(app_lib STATIC App.cpp)
target_link_libraries(app_lib sdl_lib)


#add_library(gl_lib STATIC
            #gl/render.cpp
            #gl/render_2d_texture.cpp
            #gl/shader.cpp
            #gl/text.cpp
           #)

#target_link_libraries(gl_lib GL SDL2 SDL2_image) 

add_executable(main main.cpp)
target_link_libraries(main app_lib)
