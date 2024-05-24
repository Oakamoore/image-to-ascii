#ifndef DIRECTORIES_H
#define DIRECTORIES_H

#include <filesystem>
#include <array>

namespace Directories
{
	static constexpr int numDirectories {2};

	// The base directories, used to determine where to read
	// and write images to/from. 

	inline const std::filesystem::path input {"./input/"};
	inline const std::filesystem::path output {"./output/"};

	inline const std::array<std::filesystem::path, numDirectories> directories {input, output};
}

#endif