//#define STB_IMAGE_RESIZE_IMPLEMENTATION
//
//// Temporarily disables warnings
//#pragma warning(push, 0)
//#include "stb_image_resize2.h"
//#pragma warning(pop)

#include "image_processing.h"
#include <algorithm>

namespace ImageProcessing
{
	/*Image resize(const Image& image)
	{
		Image rImage {image};


		return rImage;
	}*/
	
	Image greyscale(const Image& image)
	{
		static constexpr std::string_view suffix {"_greyscale"};
		static constexpr int RGB {3};

		Image gImage {image};

		// The image isn't already monochrome
		if (gImage.channels() >= RGB)
		{
			for (std::size_t pixel {0}; pixel < gImage.size(); pixel += gImage.channels())
			{
				const auto r {gImage[pixel]};
				const auto g {gImage[pixel + 1]};
				const auto b {gImage[pixel + 2]};

				// An average of the sum of channel values
				const auto average {(r + g + b) / gImage.channels()};

				// Set the current pixel's channel values to 'average' 
				std::fill_n(gImage.data() + pixel, gImage.channels(), average);
			}
		}

		gImage.write(suffix);

		return gImage;
	}

	/*
	void convertToAscii(const Image& image)
	{

	}*/
}