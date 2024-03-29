cmake_minimum_required(VERSION 3.22)
project(ja-craft)

set(CMAKE_CXX_STANDARD 20)

include_directories(ext/glad/include)
include_directories(resources)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# external files that also need to get compiled
set(ext ext/glad/src/glad.c)

# graphics related source files
set(gfx mesh.cpp program.cpp shader.cpp texture_atlas.cpp)
list(TRANSFORM gfx PREPEND gfx/)

# physics related source files
set(physics aabb.cpp ray.cpp swept.cpp)
list(TRANSFORM physics PREPEND physics/)

# world related source files
set(world camera.cpp chunk.cpp default_terrain_generator.cpp flat_terrain_generator.cpp generator.cpp terrain.cpp)
list(TRANSFORM world PREPEND world/)

# total source files
set(sources main.cpp ${gfx} ${physics} ${world})
list(TRANSFORM sources PREPEND src/)

add_executable(ja_craft ${ext} ${sources})

find_package(glfw3 REQUIRED NAMES glfw3 glfw)
find_package(glm REQUIRED)

target_link_libraries(ja_craft glfw)
target_link_libraries(ja_craft glm::glm)

#add_executable(ja_craft src/main.cpp ext/glad/src/glad.c ext/stb_image.h src/gfx/shader.cpp src/gfx/shader.h src/gfx/program.cpp src/gfx/program.h src/world/cube_mesh.h src/world/chunk.cpp src/world/chunk.h src/world/camera.cpp src/world/camera.h src/gfx/mesh.h src/gfx/mesh.cpp src/physics/aabb.cpp src/physics/aabb.h src/world/chunk.cpp src/world/cube.cpp src/world/cube.h src/world/md_array_view.cpp src/world/md_array_view.h src/util/indices_view.h src/world/player.cpp src/world/player.h src/gfx/texture_atlas.cpp src/gfx/texture_atlas.h src/util/non_copyable.h src/world/terrain.cpp src/world/terrain.h src/physics/swept.h src/physics/swept.cpp src/physics/ray.cpp src/physics/ray.h ext/PerlinNoise.h src/world/generator.cpp src/world/generator.h src/world/flat_terrain_generator.cpp src/world/block.h src/world/terrain_generator.h src/world/default_terrain_generator.h src/world/default_terrain_generator.cpp src/world/block_info.h src/world/file.cpp src/world/file.h src/world/file.h)
