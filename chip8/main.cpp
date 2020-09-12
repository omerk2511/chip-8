#include "utils.h"
#include "program.h"

int main(int argc, char* argv[])
{
	if (argc < 2) {
		std::cout << "[*] Usage: " << argv[0] << " rom" << std::endl;
		return 1;
	}

	try {
		program program{ utils::read_rom(argv[1]) };
		program.emulate();
	} catch(std::exception& e) {
		std::cout << "[-] Error: " << e.what() << std::endl;
	} catch (...) {
		std::cout << "[-] Unknown error" << std::endl;
	}

	return 0;
}