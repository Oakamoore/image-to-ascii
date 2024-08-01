cmake_minimum_required(VERSION 3.29)

project(image-to-ascii 
	VERSION 1.0 
	DESCRIPTION "A command line tool for converting images to ASCII art" 
	HOMEPAGE_URL "https://github.com/Oakamoore/image-to-ascii"
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)	

add_library(image-to-ascii-lib
	src/image.cpp
	src/image_processing.cpp
	src/util.cpp
)

target_include_directories(image-to-ascii-lib 
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

option(ENABLE_TESTING "Enable tests" ON)

if(ENABLE_TESTING)
	enable_testing()
	add_subdirectory(tests)
endif()

add_executable(image-to-ascii 
	src/main.cpp
)

target_link_libraries(image-to-ascii 
	PRIVATE image-to-ascii-lib
)