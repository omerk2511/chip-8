#pragma once

#include <SDL.h>
#include <memory>
#include <functional>
#include <stdexcept>
#include <string>

namespace sdl
{
	template<typename T>
	using ptr = std::unique_ptr<T, std::function<void(T*)>>;

	using window = SDL_Window;
	using renderer = SDL_Renderer;
	using texture = SDL_Texture;
	using rect = SDL_Rect;
	using event = SDL_Event;
	using key_code = SDL_Keycode;

	void init(int flags);
	void quit();

	std::string get_error();

	ptr<window> create_window(const std::string& title, int x, int y, int w, int h, int flags);
	void destroy_window(window* window);

	ptr<renderer> create_renderer(window* window, int flags);
	void destroy_renderer(renderer* renderer);
	void render_clear(renderer* renderer);
	void render_present(renderer* renderer);
	void render_copy(renderer* renderer, texture* texture, rect* src, rect* dest);
	void render_set_logical_size(renderer* renderer, int w, int h);

	ptr<texture> create_texture(renderer* renderer, int format, int access, int w, int h);
	void destroy_texture(texture* texture);
	void update_texture(texture* texture, rect* rect, const void* pixels, int pitch);

	bool poll_event(sdl::event* event);
}