#ifndef UTIL_H
#define UTIL_H

#include <utility>
#include <fstream>

namespace ImageProcessing::Util
{
	int scale(int value, float factor);
	int mapValue(int value, std::pair<int, int> rangeOne, std::pair<int, int> rangeTwo);
	bool isFileEmpty(std::fstream& file);
}

#endif