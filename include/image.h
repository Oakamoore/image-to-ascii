#ifndef IMAGE_H
#define IMAGE_H

#include "directories.h"
#include <string_view>
#include <string>
#include <cstddef>
#include <cstdint>

class Image
{
public:
	explicit Image(std::string_view fileName);
	Image(const Image& image);
	~Image();

	bool read(std::string_view fileName);
	void write(std::string_view suffix); 

	Image operator=(const Image& image) = delete;

private:
	std::string m_source {};				// Source image name without file extension
	std::filesystem::path m_directory {};	// Output directory, based on source image name
	std::uint8_t* m_data {};
	std::size_t m_size {};
	int m_width {};
	int m_height {};
	int m_channels {};
	bool m_isValid {};

};

#endif