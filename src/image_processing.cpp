#define STB_IMAGE_RESIZE_IMPLEMENTATION

// Temporarily disables warnings
#pragma warning(push, 0)
#include "stb_image_resize2.h"
#pragma warning(pop)

#include "image_processing.h"
#include <algorithm>
#include <iostream>
#include <utility>
#include <fstream>

static constexpr int s_threeChannel {3};

namespace ImageProcessing
{
	Image resize(const Image& image)
	{
		static constexpr float s_scaleFactor {0.15f};

		auto scale
		{
			[&](int value)
			{
				return static_cast<int>(value * s_scaleFactor);
			}
		};

		Image resizedImage {scale(image.getWidth()), scale(image.getHeight()), image};

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

		// Maps a value in one range, to an equivalent value in another
		auto mapValue
		{
			[](int value, std::pair<int, int> rangeOne, std::pair<int, int> rangeTwo)
			{
				const auto& [a1, a2] { rangeOne };
				const auto& [b1, b2] { rangeTwo };

				return ((value - a1) * (b2 - b1)) / (a2 - a1) + b1;
			}
		};

		const int length {static_cast<int>(s_density.size())};
		
		std::pair<int, int> pixelRange {0, 255};
		std::pair<int, int> densityRange {0, length - 1};
		
		// Flips the range depending on the number of channels an image has
		// As '.png' and '.jpg', etc.. have better outputs for different range orientations
		if (image.getChannels() > s_threeChannel)
			densityRange = {length - 1, 0};

		for (std::size_t i {0}; i < image.getHeight(); ++i)
		{
			for (std::size_t j {0}; j < image.getWidth(); ++j)
			{
				const auto pixel {(i * image.getWidth() + j) * image.getChannels()};

				const auto index {static_cast<std::size_t>(mapValue(image[pixel], pixelRange, densityRange))};

				file << s_density[index] << ' ';
			}
			
			file << '\n';
		}

		file.close();

		// Open file for reading
		file.open(image.getOutputPath().string() + fileName, std::ios::in);

		auto isFileEmpty
		{
			[](std::fstream& file)
			{
				return file.peek() == std::istream::traits_type::eof();
			}
		};

		std::cout << (isFileEmpty(file) ? "Failed to write \"" : "Wrote \"") << fileName;
		std::cout << "\" to " << image.getOutputPath() << '\n';
		
		file.close();
	}
}