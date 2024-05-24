#include "directories.h"
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




	return 0;
}