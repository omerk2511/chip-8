#pragma once

#include <string>

struct cpu;
class memory;
class graphics;

class instruction
{
public:
	virtual ~instruction() { };

	virtual void execute(cpu& cpu, memory& memory, graphics& graphics) const = 0;
	virtual std::string to_string() const = 0;
};