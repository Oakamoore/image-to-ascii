#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include "image.h"

namespace ImageProcessing
{
	Image resize(const Image& image);
	Image greyscale(const Image& image);
	void convertToAscii(const Image& image);
}

#endif