cmake_minimum_required(VERSION 3.22)
project(ja_craft)

set(CMAKE_CXX_STANDARD 20)

include_directories(glad/include)
include_directories(resources)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(ja_craft main.cpp glad/src/glad.c stb_image.h gfx/shader.cpp gfx/shader.h gfx/program.cpp gfx/program.h world/cube_mesh.h world/chunk.cpp world/chunk.h world/camera.cpp world/camera.h)

find_package(glfw3 REQUIRED NAMES glfw3 glfw)
find_package(glm REQUIRED)

target_link_libraries(ja_craft glfw)
target_link_libraries(ja_craft glm::glm)