#include "program.h"

program::program(const std::vector<byte>& rom)
	: memory_{ rom }, cpu_{ }, graphics_{ }
{
}

void program::emulate()
{
	cpu_.pc = static_cast<word>(ROM_OFFSET);

	while (cpu_.pc < memory_.get_rom_end()) {
		auto insn = memory_.get<std::unique_ptr<instruction>>(cpu_.pc);
		cpu_.pc += sizeof(word);
		insn->execute(cpu_, memory_, graphics_);

		graphics_.poll_events();
		if (graphics_.get_exit_flag()) {
			return;
		}

		if (cpu_.dt) { cpu_.dt--; }
		if (cpu_.st) { cpu_.st--; printf("\7"); } // check this

		std::this_thread::sleep_for(std::chrono::microseconds(1667)); // move to constant
	}
}

void program::disassemble() const
{
	for (auto pc = ROM_OFFSET; pc < memory_.get_rom_end(); pc += sizeof(word)) {
		std::cout << memory_.get<std::shared_ptr<instruction>>(pc)->to_string() << std::endl;
	}
}