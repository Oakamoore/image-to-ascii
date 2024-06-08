#define STB_IMAGE_RESIZE_IMPLEMENTATION

// Temporarily disables warnings
#pragma warning(push, 0)
#include "stb_image_resize2.h"
#pragma warning(pop)

#include "image_processing.h"
#include "util.h"
#include <algorithm>
#include <iostream>
#include <utility>
#include <fstream>

constexpr int s_threeChannel {3};

namespace ImageProcessing
{
	Image resize(const Image& image)
	{
		// This can't be static if you want to account for different image sizes
		static constexpr float s_scaleFactor {0.1f};

		Image resizedImage {Util::scale(image.getWidth(), s_scaleFactor), Util::scale(image.getHeight(), s_scaleFactor), image};

		const auto originalStride {image.getWidth() * image.getChannels()};
		const auto resizedStride {resizedImage.getWidth() * resizedImage.getChannels()};

		// Accounts for images with/without an alpha channel
		stbir_pixel_layout layout {image.getChannels() <= s_threeChannel ? STBIR_RGB : STBIR_RGBA};

		stbir_resize_uint8_linear
		(
			image.getData(), image.getWidth(), image.getHeight(), originalStride,
			resizedImage.getData(), resizedImage.getWidth(), resizedImage.getHeight(),
			resizedStride, layout
		);

		resizedImage.write("_resized");

		return resizedImage;
	}
	
	Image greyscale(const Image& image)
	{
		Image gImage {image};

		// The image isn't already monochrome
		if (gImage.getChannels() >= s_threeChannel)
		{
			for (std::size_t pixel {0}; pixel < gImage.getSize(); pixel += gImage.getChannels())
			{
				const auto r {gImage[pixel]};
				const auto g {gImage[pixel + 1]};
				const auto b {gImage[pixel + 2]};

				// An average of the sum of channel values
				const auto average {(r + g + b) / gImage.getChannels()};

				// Set the current pixel's channel values to 'average' 
				std::fill_n(gImage.getData() + pixel, gImage.getChannels(), average);
			}
		}

		gImage.write("_greyscale");

		return gImage;
	}

	void convertToAscii(const Image& image)
	{
		// Represents the brightness of a given pixel
		static constexpr std::string_view s_density {"$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\" ^ `'. "};

		const auto fileName {image.getSourceName() + "_ascii.txt"};

		std::fstream file {};

		// Open file for writing
		file.open(image.getOutputPath().string() + fileName, std::ios::out);

		const int length {static_cast<int>(s_density.size())};

		auto pixelRange {std::make_pair(0, 255)};
		auto densityRange {std::make_pair(0, length - 1)};
		
		// Flips the range depending on the number of channels an image has
		// As '.png' and '.jpg', etc.. have better outputs for different range orientations
		if (image.getChannels() > s_threeChannel)
			densityRange = {length - 1, 0};

		for (std::size_t i {0}; i < image.getHeight(); ++i)
		{
			for (std::size_t j {0}; j < image.getWidth(); ++j)
			{
				const auto pixel {(i * image.getWidth() + j) * image.getChannels()};

				// Maps a value in one range, to an equivalent value in another
				const auto index {static_cast<std::size_t>(Util::mapValue(image[pixel], pixelRange, densityRange))};

				file << s_density[index] << ' ';
			}
			
			file << '\n';
		}

		file.close();

		// Open file for reading
		file.open(image.getOutputPath().string() + fileName, std::ios::in);

		std::cout << (Util::isFileEmpty(file) ? "Failed to write \"" : "Wrote \"") << fileName;
		std::cout << "\" to " << image.getOutputPath() << '\n';
		
		file.close();
	}
}