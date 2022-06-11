# CMake entry point
cmake_minimum_required (VERSION 3.11)
project (basic_texture_atlas)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(REMOVE_RECURSE ${CMAKE_CURRENT_BINARY_DIR}/test_images)
file(COPY ${PROJECT_SOURCE_DIR}/test_images DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include_directories(
    ${PROJECT_SOURCE_DIR}/include/
    ${PROJECT_SOURCE_DIR}/lodepng/
)

add_library( 
    basic_texture_atlas_lib
    ${PROJECT_SOURCE_DIR}/lodepng/lodepng.cpp
    ${PROJECT_SOURCE_DIR}/src/ImageDecoder.cpp
    ${PROJECT_SOURCE_DIR}/src/ImageEncoder.cpp
    ${PROJECT_SOURCE_DIR}/src/ImageReel.cpp
    ${PROJECT_SOURCE_DIR}/src/ImageSrcDir.cpp
)

target_link_libraries(
    basic_texture_atlas_lib
)

add_executable(
    basic_texture_atlas_host
    ${PROJECT_SOURCE_DIR}/src/main.cpp
)

target_link_libraries(
    basic_texture_atlas_host
    basic_texture_atlas_lib
)
