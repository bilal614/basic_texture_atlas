# CMake entry point
cmake_minimum_required (VERSION 3.11)
project (basic_texture_atlas)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
    ${PROJECT_SOURCE_DIR}/src/AtlasMetaDataWriter.cpp
    ${PROJECT_SOURCE_DIR}/src/RgbaImage.cpp
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

if(WIN32)
    add_custom_command(TARGET basic_texture_atlas_host  POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/test_images
        ${CMAKE_CURRENT_BINARY_DIR}/Debug/test_images)

    add_custom_command(TARGET basic_texture_atlas_host  POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/test_images
        ${CMAKE_CURRENT_BINARY_DIR}/Release/test_images)
else()
    add_custom_command(TARGET basic_texture_atlas_host  POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/test_images
        ${CMAKE_CURRENT_BINARY_DIR}/test_images)
endif()
