#pragma once

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

#include "types.h"
#include "cpu.h"
#include "memory.h"
#include "graphics.h"
#include "instruction.h"

class program final
{
public:
	program(const std::vector<byte>& rom);

	void emulate();
	void disassemble() const;

private:
	cpu cpu_;
	memory memory_;
	graphics graphics_;
};