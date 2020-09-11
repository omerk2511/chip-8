#pragma once

#include "sdl.h"
#include "types.h"

#include <map>
#include <algorithm>

static constexpr size_t PIXEL_WIDTH = 64;
static constexpr size_t PIXEL_HEIGHT = 32;

static constexpr size_t PIXELS = PIXEL_WIDTH * PIXEL_HEIGHT;

static constexpr size_t WINDOW_WIDTH = 1024;
static constexpr size_t WINDOW_HEIGHT = 512;

class graphics final
{
public:
	graphics();
	~graphics();

	void clear();
	void draw();

	void poll_events();

	byte (&get_bitmap())[PIXELS];

	bool is_pressed(byte key) const;
	byte get_pressed_key();

	void set_exit_flag(bool exit_flag);
	bool get_exit_flag() const;

private:
	sdl::ptr<sdl::window> window_;
	sdl::ptr<sdl::renderer> renderer_;
	sdl::ptr<sdl::texture> texture_;

	byte bitmap_[PIXELS];
	bool keys_[16]; // move to constant
	bool exit_flag_;
};