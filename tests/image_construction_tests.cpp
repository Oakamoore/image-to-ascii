#include "image.h"
#include "image_processing.h"
#include "directories.h"
#include <catch2/catch_test_macros.hpp>
#include <filesystem>
#include <string>
#include <string_view>
#include <algorithm>

namespace fs = std::filesystem;

namespace
{
	bool isInDirectory(const fs::path& directory, std::string_view fileName)
	{
		auto entry {fs::directory_iterator(directory)};

		auto found {std::find_if(entry, end(entry), [&fileName] (const auto& file)
		{
			return file.path().filename().string() == fileName;
		})};

		// File is found in given directory
		return (found != end(entry) ? true : false);
	}
}

TEST_CASE("Image object construction")
{
	// The input directory must exist
	REQUIRE(fs::is_directory(Directories::input));

	// Ensures the output directory doesn't exist yet
	fs::remove_all(Directories::output);
	REQUIRE_FALSE(fs::is_directory(Directories::output));

	SECTION("Failed construction")
	{
		std::string fileName {"banana.png"};

		// A given file within the input directory shouldn't exist
		REQUIRE_FALSE(isInDirectory(Directories::input, fileName));

		Image image {fileName};

		// Image construction should fail
		REQUIRE_FALSE(image.isValid());

		// A corresponding output directory shouldn't be created
		REQUIRE_FALSE(fs::is_directory(Directories::output / "banana"));
	}

	SECTION("Successful construction")
	{
		std::string fileName {"apple.png"};

		// A given file within the input directory should exist
		REQUIRE(isInDirectory(Directories::input, fileName));

		Image image {fileName};

		// Image construction should succeed
		REQUIRE(image.isValid());

		// A corresponding output directory should be created
		REQUIRE(fs::is_directory(Directories::output / "apple"));

		// Each of the following conversion steps should be successful 
		Image resizedImage {ImageProcessing::resize(image)};
		REQUIRE(isInDirectory(Directories::output / "apple", "apple_resized.png"));

		Image greyscaleImage {ImageProcessing::greyscale(resizedImage)};
		REQUIRE(isInDirectory(Directories::output / "apple", "apple_greyscale.png"));

		ImageProcessing::convertToAscii(greyscaleImage);
		REQUIRE(isInDirectory(Directories::output / "apple", "apple_ascii.txt"));
	}
}