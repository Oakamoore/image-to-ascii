#define STB_IMAGE_RESIZE_IMPLEMENTATION

// Temporarily disables warnings
#pragma warning(push, 0)
#include "stb_image_resize2.h"
#pragma warning(pop)

#include "image_processing.h"
#include <algorithm>
#include <iostream>

namespace ImageProcessing
{
	Image resize(const Image& image)
	{
		constexpr float scaleFactor {0.1f};

		auto scale
		{
			[](int value, float factor)
			{
				return static_cast<int>(value * factor);
			}
		};

		Image resizedImage {scale(image.getWidth(), scaleFactor), scale(image.getHeight(), scaleFactor), image};

		const auto originalStride {image.getWidth() * image.getChannels()};
		const auto resizedStride {resizedImage.getWidth() * resizedImage.getChannels()};

		// Accounts for images with/without an alpha channel
		stbir_pixel_layout layout {image.getChannels() <= 3 ? STBIR_RGB : STBIR_RGBA};

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
		if (gImage.getChannels() >= 3)
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

	void convertToAscii([[maybe_unused]]const Image& image)
	{
		
	}
}