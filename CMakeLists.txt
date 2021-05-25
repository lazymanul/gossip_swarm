cmake_minimum_required(VERSION 3.0.0)
project(engine VERSION 0.1.0)
set (CMAKE_CXX_STANDARD 14)


add_library(glad STATIC glad.c)
add_library(shader STATIC shader.cpp)
add_library(resource_manager resource_manager.cpp)

add_executable(engine engine.cpp game.cpp sprite_renderer.cpp game_object.cpp ball_object.cpp)
target_link_libraries(engine shader)
target_link_libraries(engine resource_manager)
target_link_libraries(engine glad)
target_link_libraries(engine glfw)
target_link_libraries(engine ${CMAKE_DL_LIBS})


