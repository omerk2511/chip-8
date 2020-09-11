#pragma once

#include <vector>
#include <stack>
#include <memory>

#include "types.h"
#include "instruction.h"
#include "parsing.h"
#include "utils.h"
#include "graphics.h"

namespace parsing
{
	std::unique_ptr<instruction> parse_instruction(const word opcode);
}

extern const size_t MEMORY_SIZE;
extern const size_t ROM_OFFSET;

class memory final
{
public:
	memory(const std::vector<byte>& rom);

	template<typename T>
	T get(const size_t address) const
	{
		return *reinterpret_cast<const T*>(&ram_[address]);
	}

	template<>
	std::unique_ptr<instruction> get(const size_t address) const
	{
		return parsing::parse_instruction(utils::to_word(ram_[address], ram_[address + 1]));
	}

	template<typename T>
	void set(const size_t address, const T value)
	{
		*reinterpret_cast<T*>(&ram_[address]) = value;
	}

	void push_address(const word address);
	word pop_address();

	size_t get_rom_end() const { return rom_end_; }

private:
	std::vector<byte> ram_;
	std::stack<word> stack_;

	size_t rom_end_;
};