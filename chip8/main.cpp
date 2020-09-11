#include "utils.h"
#include "program.h"

int main(int argc, char* argv[])
{
	// check argc and stuff
	// validate argv[1]
	// pass rom to emulation(...)

	program program{ utils::read_rom(argv[1]) };
	program.emulate();

	return 0;
}