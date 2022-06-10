# CMake entry point
cmake_minimum_required (VERSION 3.11)
project (basic_texture_atlas)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(GCC_COVERAGE_COMPILE_FLAGS "-static -static-libgcc -static-libstdc++")
# Add the next line to get all the compiler warnings
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall)


include_directories(
    ${PROJECT_SOURCE_DIR}/include/
    ${PROJECT_SOURCE_DIR}/lodepng-master/
)


add_library( 
    basic_texture_atlas_lib
    ${PROJECT_SOURCE_DIR}/lodepng-master/lodepng.cpp
    ${PROJECT_SOURCE_DIR}/src/ImageEncoder.cpp
    ${PROJECT_SOURCE_DIR}/src/ImageDecoder.cpp
    ${PROJECT_SOURCE_DIR}/src/Image.cpp
)

target_link_libraries(
    basic_texture_atlas_lib
)

add_executable(
    basic_texture_atlas_host
    ${PROJECT_SOURCE_DIR}/src/main.cpp
)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


target_link_libraries(
    basic_texture_atlas_host
    basic_texture_atlas_lib
)
