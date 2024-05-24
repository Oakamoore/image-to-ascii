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

	Image image1 {"sample.png"};
	Image image2 {"test.png"};
	Image image3 {"image.png"};
	Image image5 {"another_sample.png"};
	Image image4 {"picture.png"};

	return 0;
}