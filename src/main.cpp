#include "directories.h"
#include "image.h"
#include <iostream>
#include <array>
#include <cassert>

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
	// Creates the base input and output directories 
	for (const auto& directory : Directories::directories)
	{
		std::filesystem::create_directory(directory);

		// The given directory was create successfully 
		assert(!std::filesystem::create_directory(directory));
	}

	Image image1 {"first.png"};
	image1.write("first");

	Image image2 {"second.jpeg"};
	image2.write("second");

	return 0;
}