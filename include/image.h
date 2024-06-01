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
	Image(Image&& image) noexcept;
	~Image();

	bool read(std::string_view fileName);
	void write(std::string_view suffix); 

	std::uint8_t* data() const { return m_data; }
	std::size_t size() const { return m_size; }
	int channels() const { return m_channels; }

	std::uint8_t& operator[](std::size_t index);

	Image operator=(const Image&) = delete;
	Image operator=(Image&&) = delete;

private:
	std::string m_sourceName {};				
	std::filesystem::path m_outputPath {};	
	std::uint8_t* m_data {};
	std::size_t m_size {};
	int m_width {};
	int m_height {};
	int m_channels {};
	bool m_isValid {};

};

#endif