#include "graphics.h"

static const std::map<sdl::key_code, size_t> KEYMAP = {
	{ SDLK_x, 0x00 },
	{ SDLK_1, 0x01 },
	{ SDLK_2, 0x02 },
	{ SDLK_3, 0x03 },
	{ SDLK_q, 0x04 },
	{ SDLK_w, 0x05 },
	{ SDLK_e, 0x06 },
	{ SDLK_a, 0x07 },
	{ SDLK_s, 0x08 },
	{ SDLK_d, 0x09 },
	{ SDLK_z, 0x0a },
	{ SDLK_c, 0x0b },
	{ SDLK_4, 0x0c },
	{ SDLK_r, 0x0d },
	{ SDLK_f, 0x0e },
	{ SDLK_v, 0x0f }
};

static const std::string WINDOW_NAME = "chip8";

const size_t FONT_SPRITE_SIZE = 5;

graphics::graphics()
	: window_{ }, renderer_{ }, texture_{ }, bitmap_{ 0 }, keys_{ false }, exit_flag_{ false }
{
	window_ = sdl::create_window(
		WINDOW_NAME.c_str(),
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	renderer_ = sdl::create_renderer(
		window_.get(),
		0
	);

	sdl::render_set_logical_size(
		renderer_.get(),
		WINDOW_WIDTH,
		WINDOW_HEIGHT
	);

	texture_ = sdl::create_texture(
		renderer_.get(),
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		PIXEL_WIDTH,
		PIXEL_HEIGHT
	);
}

void graphics::clear()
{
	std::memset(bitmap_, 0, sizeof(bitmap_));
}

void graphics::draw()
{
	int pixels[PIXELS];
	std::transform(bitmap_, bitmap_ + PIXELS, pixels,
		[](byte b) { return (b * 0x00ffffff) | 0xff000000; });

	sdl::update_texture(
		texture_.get(),
		nullptr,
		pixels,
		PIXEL_WIDTH * sizeof(int)
	);

	sdl::render_clear(renderer_.get());
	sdl::render_copy(renderer_.get(), texture_.get(), nullptr, nullptr);
	sdl::render_present(renderer_.get());
}

void graphics::poll_events()
{
	sdl::event event;

	while (sdl::poll_event(&event)) {
		if (event.type == SDL_QUIT) {
			exit_flag_ = true;
		} else if (event.type == SDL_KEYDOWN) {
			try {
				keys_[KEYMAP.at(event.key.keysym.sym)] = true;
			} catch(...) { }
		} else if (event.type == SDL_KEYUP) {
			try {
				keys_[KEYMAP.at(event.key.keysym.sym)] = false;
			} catch (...) {}
		}
	}
}

byte (&graphics::get_bitmap())[PIXELS]
{
	return bitmap_;
}

bool graphics::is_pressed(byte key) const
{
	if (key < sizeof(keys_)) {
		return keys_[key];
	}

	return false;
}

byte graphics::get_pressed_key()
{
	for (auto i = 0; i < sizeof(keys_); i++) {
		if (keys_[i]) {
			keys_[i] = false;
			return i;
		}
	}

	throw std::runtime_error("No key pressed.");
}

void graphics::set_exit_flag(bool exit_flag)
{
	exit_flag_ = exit_flag;
}

bool graphics::get_exit_flag() const
{
	return exit_flag_;
}
