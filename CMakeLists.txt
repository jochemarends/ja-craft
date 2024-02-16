cmake_minimum_required(VERSION 3.20)

project(ja-craft LANGUAGES C CXX)

set(compile_features cxx_std_20)

set(compile_options -Werror -Wall -Wextra -pedantic)

add_executable(ja-craft src/main.cpp)

add_subdirectory(external/glad)

add_subdirectory(src/graphics)

add_subdirectory(src/glfw)

target_include_directories(ja-craft PRIVATE inc)

# GLFW
find_package(glfw3 REQUIRED NAMES glfw glfw3)

target_link_libraries(ja-craft PRIVATE glad glfw)

target_compile_features(ja-craft PRIVATE ${compile_features})

target_compile_options(ja-craft PRIVATE ${compile_options})

