cmake_minimum_required(VERSION 3.29)
project(Orbits C)

add_executable(Orbits src/draw.c src/orbital_body.c)
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
target_include_directories(Orbits PRIVATE include)
target_link_libraries(Orbits m raylib)