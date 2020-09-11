#pragma once

#include <memory>

#include "types.h"
#include "reg.h"
#include "instruction.h"
#include "instructions.h"

namespace parsing
{
	std::unique_ptr<instruction> parse_instruction(const word opcode);
}