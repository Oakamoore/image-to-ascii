include(FetchContent)

FetchContent_Declare(
	Catch2
	GIT_REPOSITORY	https://github.com/catchorg/Catch2.git
	GIT_TAG			v3.6.0
)

FetchContent_MakeAvailable(Catch2)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)

add_executable(image-to-ascii-tests
	image_construction_tests.cpp
)

target_link_libraries(image-to-ascii-tests
	PRIVATE Catch2::Catch2WithMain
	PRIVATE image-to-ascii-lib
)

# Creates a directory
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/build/tests/Debug/input)

# Copies an image file to a directory
file(
	COPY ${CMAKE_SOURCE_DIR}/tests/input/apple.png 
	DESTINATION ${CMAKE_SOURCE_DIR}/build/tests/Debug/input/
)

catch_discover_tests(image-to-ascii-tests)