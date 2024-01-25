#include "padZeros.hpp"
#include <string>

std::string padZeros(int number, int length) {
	std::string numStr{std::to_string(number)};
	while (numStr.length() < length) 
		numStr = '0' + numStr;

	return numStr;
}
