#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define _CRT_SECURE_NO_WARNINGS

// Temporarily disables warnings
#pragma warning(push, 0)
#include "stb_image.h"
#include "stb_image_write.h"
#pragma warning(pop)

#include "image.h"
#include <iostream>

Image::Image(std::string_view fileName)
	: m_isValid {read(fileName)}
{
	std::cerr << (m_isValid ? "Read \"" : "Failed to read \"") << fileName << "\"\n";

	if (m_isValid)
	{
		// Removes the file extension from the image name: "image.png" -> "image"
		m_directory = static_cast<std::filesystem::path>(fileName).replace_extension();

		m_sourceName = m_directory.string();

		// Prepends the './output/' directory 
		m_directory = (Directories::output / m_directory).string() + '/';

		// Creates a new directory named after the image 
		std::filesystem::create_directory(m_directory);
	}
}

Image::~Image()
{
	// Deallocates the memory held by 'm_data'
	stbi_image_free(m_data);
}

bool Image::read(std::string_view fileName)
{
	const auto inputImage {Directories::input.string() + static_cast<std::string>(fileName)};

	// Attempt to read the image 
	m_data = stbi_load(inputImage.c_str(), &m_width, &m_height, &m_channels, 0);

	return m_data != nullptr;
}

void Image::write(std::string_view imageName)
{
	// Only valid 'Image' objects can be 
	// used to create an output image
	if (!m_isValid)
		return;
	
	// Ouput images default to '.png'
	const auto outputImage {m_directory.string() + static_cast<std::string>(imageName) + ".png"};

	int hasWritten {stbi_write_png(outputImage.c_str(), m_width, m_height, m_channels, m_data, m_width * m_channels)};

	std::cout << (hasWritten ? "Wrote to " : "Failed to write to ") << m_directory << "\n\n";
}