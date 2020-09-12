#include "sdl.h"

static constexpr int SDL_SUCCESS = 0;

static constexpr int SDL_FIRST_RENDERER = -1;

void sdl::init(int flags)
{
	auto status = ::SDL_Init(flags);

	if (status != SDL_SUCCESS) {
		throw std::runtime_error("Could not initialize SDL: " + sdl::get_error());
	}
}

void sdl::quit()
{
	::SDL_Quit();
}

std::string sdl::get_error()
{
	return ::SDL_GetError();
}

sdl::ptr<sdl::window> sdl::create_window(const std::string& title, int x, int y, int w, int h, int flags)
{
	auto window = ::SDL_CreateWindow(
		title.c_str(),
		x, y, w, h,
		flags
	);

	if (!window) {
		throw std::runtime_error("Could not create a SDL window: " + sdl::get_error());
	}

	return sdl::ptr<sdl::window>(window, sdl::destroy_window);
}

void sdl::destroy_window(window* window)
{
	::SDL_DestroyWindow(window);
}

sdl::ptr<sdl::renderer> sdl::create_renderer(window* window, int flags)
{
	auto renderer = ::SDL_CreateRenderer(
		window,
		SDL_FIRST_RENDERER,
		flags
	);

	if (!renderer) {
		throw std::runtime_error("Could not create a SDL renderer: " + sdl::get_error());
	}

	return sdl::ptr<sdl::renderer>(renderer, sdl::destroy_renderer);
}

void sdl::destroy_renderer(renderer* renderer)
{
	::SDL_DestroyRenderer(renderer);
}

void sdl::render_clear(renderer* renderer)
{
	auto status = ::SDL_RenderClear(renderer);

	if (status != SDL_SUCCESS) {
		throw std::runtime_error("Could not clear renderer: " + sdl::get_error());
	}
}

void sdl::render_present(renderer* renderer)
{
	::SDL_RenderPresent(renderer);
}

void sdl::render_copy(renderer* renderer, texture* texture, rect* src, rect* dest)
{
	auto status = ::SDL_RenderCopy(
		renderer,
		texture,
		src,
		dest
	);

	if (status != SDL_SUCCESS) {
		throw std::runtime_error("Could not copy a portion of the texture to the renderer: " + sdl::get_error());
	}
}

void sdl::render_set_logical_size(renderer* renderer, int w, int h)
{
	auto status = ::SDL_RenderSetLogicalSize(
		renderer,
		w, h
	);

	if (status != SDL_SUCCESS) {
		throw std::runtime_error("Could not set renderer's logical size: " + sdl::get_error());
	}
}

sdl::ptr<sdl::texture> sdl::create_texture(renderer* renderer, int format, int access, int w, int h)
{
	auto texture = ::SDL_CreateTexture(
		renderer,
		format,
		access,
		w, h
	);

	if (!texture) {
		throw std::runtime_error("Could not create a texture: " + sdl::get_error());
	}

	return sdl::ptr<sdl::texture>(texture, sdl::destroy_texture);
}

void sdl::destroy_texture(texture* texture)
{
	::SDL_DestroyTexture(texture);
}

void sdl::update_texture(texture* texture, rect* rect, const void* pixels, int pitch)
{
	auto status = ::SDL_UpdateTexture(
		texture,
		rect,
		pixels,
		pitch
	);

	if (status != SDL_SUCCESS) {
		throw std::runtime_error("Could not update texture: " + sdl::get_error());
	}
}

bool sdl::poll_event(sdl::event* event)
{
	return ::SDL_PollEvent(event);
}