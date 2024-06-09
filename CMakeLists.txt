cmake_minimum_required(VERSION 3.29)

project(image-to-ascii VERSION 1.0 DESCRIPTION "A command line tool for converting image to ASCII art" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(image-to-ascii src/main.cpp src/image.cpp src/image_processing.cpp src/util.cpp)

target_include_directories(image-to-ascii PRIVATE include lib)

