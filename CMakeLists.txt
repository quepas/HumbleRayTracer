cmake_minimum_required(VERSION 3.0.0)

project(HumbleRayTracer)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})


add_executable(ray_tracer src/main.c)
target_link_libraries(ray_tracer ${SDL2_LIBRARIES})