cmake_minimum_required(VERSION 3.27)
project(opengl_hello_world)

set(CMAKE_CXX_STANDARD 11)

add_executable(opengl_hello_world
        main.cpp
        shader.cpp
        shader.h
        panic.h
        VBO.cpp
        VBO.h
        VAO.cpp
        VAO.h
        EBO.cpp
        EBO.h
        texture.cpp
        texture.h
)

find_package(glad CONFIG REQUIRED)
target_link_libraries(opengl_hello_world PRIVATE glad::glad)
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(opengl_hello_world PRIVATE glfw)
find_package(assimp CONFIG REQUIRED)
target_link_libraries(opengl_hello_world PRIVATE assimp::assimp)
find_package(fmt CONFIG REQUIRED)
target_link_libraries(opengl_hello_world PRIVATE fmt::fmt)
find_package(fmt CONFIG REQUIRED)
target_link_libraries(opengl_hello_world PRIVATE fmt::fmt)
find_package(Stb REQUIRED)
target_include_directories(opengl_hello_world PRIVATE ${Stb_INCLUDE_DIR})
