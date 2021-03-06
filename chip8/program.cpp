#include "program.h"

static constexpr int CYCLE_DELAY_US = 1667;

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
		if (cpu_.st) { cpu_.st--; } // check this beep

		std::this_thread::sleep_for(std::chrono::microseconds(CYCLE_DELAY_US));
	}
}

void program::disassemble() const
{
	for (auto pc = ROM_OFFSET; pc < memory_.get_rom_end(); pc += sizeof(word)) {
		std::cout << memory_.get<std::unique_ptr<instruction>>(pc)->to_string() << std::endl;
	}
}