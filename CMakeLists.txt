cmake_minimum_required(VERSION 3.29)
project(Orbits C)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIR})

add_executable(Orbits src/main.c src/screen.c src/orbital_body.c)

target_include_directories(Orbits PRIVATE include)
target_link_libraries(Orbits m ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})