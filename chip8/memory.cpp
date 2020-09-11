#include "memory.h"
#include "memory.h"

const size_t MEMORY_SIZE = 4096;
const size_t ROM_OFFSET = 0x200;

static const std::vector<byte> font = {
	0xf0, 0x90, 0x90, 0x90, 0xf0,
	0x20, 0x60, 0x20, 0x20, 0x70,
	0xf0, 0x10, 0xf0, 0x80, 0xf0,
	0xf0, 0x10, 0xf0, 0x10, 0xf0,
	0x90, 0x90, 0xf0, 0x10, 0x10,
	0xf0, 0x80, 0xf0, 0x10, 0xf0,
	0xf0, 0x80, 0xf0, 0x90, 0xf0,
	0xf0, 0x10, 0x20, 0x40, 0x40,
	0xf0, 0x90, 0xf0, 0x90, 0xf0,
	0xf0, 0x90, 0xf0, 0x10, 0xf0,
	0xf0, 0x90, 0xf0, 0x90, 0x90,
	0xe0, 0x90, 0xe0, 0x90, 0xe0,
	0xf0, 0x80, 0x80, 0x80, 0xf0,
	0xe0, 0x90, 0x90, 0x90, 0xe0,
	0xf0, 0x80, 0xf0, 0x80, 0xf0,
	0xf0, 0x80, 0xf0, 0x80, 0x80
};

memory::memory(const std::vector<byte>& rom)
	: ram_(MEMORY_SIZE, 0), rom_end_{ ROM_OFFSET + rom.size() }
{
	std::copy(font.begin(), font.end(), ram_.begin());
	std::copy(rom.begin(), rom.end(), ram_.begin() + ROM_OFFSET);
}

void memory::push_address(const word address)
{
	stack_.push(address);
}

word memory::pop_address()
{
	auto address = stack_.top();
	stack_.pop();

	return address;
}