#ifndef IMAGE_H
#define IMAGE_H

#include "directories.h"
#include <string_view>
#include <string>
#include <cstddef>

class Image
{
public:
	explicit Image(std::string_view fileName);

private:
	std::string m_fileName {};
	std::filesystem::path m_directory {};
	unsigned char* m_data {};
	std::size_t m_size {};
	int m_width {};
	int m_height {};
	int m_channels {};

};

#endif