#include "directories.h"
#include "image.h"
#include "image_processing.h"
#include <iostream>
#include <array>
#include <cassert>

int main(int argc, char* argv[])
{
	// Create the base input and output directories 
	for (const auto& directory : Directories::directories)
	{
		std::filesystem::create_directory(directory);

		// The given directory was create successfully 
		assert(!std::filesystem::create_directory(directory));
	}

	if (argc <= 1)
	{
		std::cout << "No image(s) provided.";
		return -1;
	}

	// Skip the first command line argument 
	for (int i {1}; i < argc; ++i)
	{
		Image image {argv[i]};

		if (image.isValid())
		{
			Image resizedImage {ImageProcessing::resize(image)};

			Image greyscaleImage {ImageProcessing::greyscale(resizedImage)};

			ImageProcessing::convertToAscii(greyscaleImage);
		}

		std::cout << '\n';
	}

	return 0;
}