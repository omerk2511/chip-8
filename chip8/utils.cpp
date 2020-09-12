#include "utils.h"

std::vector<byte> utils::read_rom(const std::string& path)
{
	std::ifstream file;
	file.exceptions(std::ifstream::badbit);

	file.open(path, std::ios::in | std::ios::binary | std::ios::ate);

	const auto file_size = file.tellg();
	std::vector<byte> rom(file_size, 0);

	file.seekg(0, std::ios::beg);
	file.read(reinterpret_cast<char*>(rom.data()), file_size);

	file.close();

	return rom;
}

word utils::to_word(byte low, byte high)
{
	return (low << 8) | high;
}
