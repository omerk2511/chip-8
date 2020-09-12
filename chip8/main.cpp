#include "utils.h"
#include "program.h"
#include "sdl.h"

void run(const std::string& path)
{
	program program{ utils::read_rom(path) };
	program.emulate();
}

int main(int argc, char* argv[])
{
	if (argc < 2) {
		std::cout << "[*] Usage: " << argv[0] << " rom" << std::endl;
		return 1;
	}

	try {
		sdl::init(SDL_INIT_VIDEO);
		run(argv[1]);
		sdl::quit();
	} catch(std::exception& e) {
		std::cout << "[-] Error: " << e.what() << std::endl;
	} catch (...) {
		std::cout << "[-] Unknown error" << std::endl;
	}

	return 0;
}