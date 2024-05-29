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
#include <algorithm>

Image::Image(std::string_view fileName)
	: m_isValid {read(fileName)}
{
	std::cerr << (m_isValid ? "Read \"" : "Failed to read \"") << fileName << "\"\n";

	if (m_isValid)
	{
		m_size = static_cast<std::size_t>(m_width * m_height * m_channels);

		// Remove the file extension from the image name: "image.png" -> "image"
		m_directory = static_cast<std::filesystem::path>(fileName).replace_extension();

		m_source = m_directory.string();

		// Prepends the './output/' directory 
		m_directory = (Directories::output / m_directory).string() + '/';

		// Create a new directory named after the image 
		std::filesystem::create_directory(m_directory);
	}
}

Image::Image(const Image& image)
	: m_source {image.m_source}
	, m_directory {image.m_directory}
	, m_width {image.m_width}
	, m_height {image.m_height}
	, m_channels {image.m_channels}
	, m_isValid {image.m_isValid}
{
	m_size = static_cast<std::size_t>(m_width * m_height * m_channels);

	// Allocate a buffer equal to the size of the image 
	m_data = new std::uint8_t[m_size];
	
	// Perform a deep copy of the image data
	std::copy(&image.m_data[0], &image.m_data[image.m_size], m_data);
}

Image::Image(Image&& image) noexcept
	: m_source {std::move(image.m_source)}
	, m_directory {std::move(image.m_directory)}
	, m_size {image.m_size}
	, m_width {image.m_width}
	, m_height {image.m_height}
	, m_channels {image.m_channels}
	, m_isValid {image.m_isValid}
{
	// Transfer ownership 
	m_data = image.m_data;

	image.m_data = nullptr;
}

Image::~Image()
{
	// Deallocates the memory held by 'm_data'
	stbi_image_free(m_data);
}

bool Image::read(std::string_view fileName)
{
	const auto inputImage {Directories::input.string() + fileName.data()};

	// Attempt to read the image 
	m_data = stbi_load(inputImage.c_str(), &m_width, &m_height, &m_channels, 0);

	return m_data != nullptr;
}

void Image::write(std::string_view suffix)
{
	static constexpr std::string_view extension {".png"};

	// Ouput images default to '.png'
	const auto outputImage {m_directory.string() + m_source + suffix.data() + extension.data()};

	int hasWritten {stbi_write_png(outputImage.c_str(), m_width, m_height, m_channels, m_data, m_width * m_channels)};

	const auto imageName {m_source + suffix.data() + extension.data()};

	if (hasWritten)
		std::cout << "Wrote \"" << imageName << "\" to ";
	else
		std::cout << "Failed to write \"" << imageName << "\" to ";

	std::cout << m_directory << '\n';
}