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

# Creates a directory, under the appropriate build configuration
# Copies an image file to the newly created directory
add_custom_command(TARGET image-to-ascii-tests PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/build/tests/$<CONFIG>/input
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/tests/input/apple.png ${CMAKE_SOURCE_DIR}/build/tests/$<CONFIG>/input/
)

catch_discover_tests(image-to-ascii-tests)