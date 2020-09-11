#pragma once

#include <fstream>
#include <vector>
#include <string>

#include "types.h"

namespace utils
{
	std::vector<byte> read_rom(const std::string& path);
	word to_word(byte low, byte high);
}