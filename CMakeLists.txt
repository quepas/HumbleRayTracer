cmake_minimum_required(VERSION 3.0.0)

project(HumbleRayTracer LANGUAGES C)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(ray_tracer src/main.c src/rendering.c src/rendering.h src/math.c src/math.h src/scene.c src/scene.h)
target_link_libraries(ray_tracer ${SDL2_LIBRARIES} m)