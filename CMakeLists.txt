cmake_minimum_required(VERSION 3.28)
project(opengl_hello_world)

set(CMAKE_CXX_STANDARD 11)

add_executable(opengl_hello_world main.cpp)

find_package(glad CONFIG REQUIRED)
target_link_libraries(opengl_hello_world PRIVATE glad::glad)
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(opengl_hello_world PRIVATE glfw)
#find_package(glew CONFIG REQUIRED)
#target_link_libraries(ogldev_tutorials PRIVATE glew)
find_package(assimp CONFIG REQUIRED)
target_link_libraries(opengl_hello_world PRIVATE assimp::assimp)