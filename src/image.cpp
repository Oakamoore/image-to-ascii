#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define _CRT_SECURE_NO_WARNINGS

// Temporarily disables warnings
#pragma warning(push, 0)
#include "stb_image.h"
#include "stb_image_write.h"
#pragma warning(pop)

#include "image.h"

Image::Image(std::string_view fileName)
	: m_fileName {fileName}
{

}

