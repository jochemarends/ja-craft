cmake_minimum_required(VERSION 3.20)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

project(ja-craft LANGUAGES C CXX)

set(compile_features cxx_std_23)

set(compile_options -Werror -Wall -Wextra -pedantic)

add_executable(ja-craft src/main.cpp inc/world/cube.h)

add_subdirectory(external/glad)

add_subdirectory(src/graphics)

add_subdirectory(src/utility)

add_subdirectory(src/world)

add_subdirectory(src/glfw)

target_include_directories(ja-craft PRIVATE inc)

# GLFW & GLM
find_package(glfw3 REQUIRED NAMES glfw glfw3)

find_package(glm REQUIRED)

target_link_libraries(ja-craft PRIVATE glad glfw glm::glm)

target_compile_features(ja-craft PRIVATE ${compile_features})

target_compile_options(ja-craft PRIVATE ${compile_options})

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug") 
    target_compile_options(ja-craft PRIVATE -Og -g -fno-omit-frame-pointer)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(ja-craft PRIVATE -O3)
endif()

