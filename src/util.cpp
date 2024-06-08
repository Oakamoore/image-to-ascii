#include "util.h"

namespace ImageProcessing::Util
{
	int scale(int value, float factor)
	{
		return static_cast<int>(value * factor);
	}

	int mapValue(int value, std::pair<int, int> rangeOne, std::pair<int, int> rangeTwo)
	{
		const auto& [a1, a2] { rangeOne };
		const auto& [b1, b2] { rangeTwo };

		return ((value - a1) * (b2 - b1)) / (a2 - a1) + b1;
	}

	bool isFileEmpty(std::fstream& file)
	{
		return file.peek() == std::fstream::traits_type::eof();
	}
}