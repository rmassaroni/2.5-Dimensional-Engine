cmake_minimum_required(VERSION 3.10)
project(PixelEngine)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} src)

file(GLOB_RECURSE SOURCES "src/*.cpp")

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(engine ${SOURCES})

target_link_libraries(engine ${SDL2_LIBRARIES} SDL2_image)
