#include "FFG_Renderer.hpp"

/***************************************************************************//**
 * Protected. Constructor.
 ******************************************************************************/
FFG_Renderer::FFG_Renderer() {
	window = nullptr;
	renderer = nullptr;
	window_title = FFG_RENDERER_DEFAULT_NAME;
	screen_width_p = FFG_RENDERER_DEFAULT_WIDTH;
	screen_height_p = FFG_RENDERER_DEFAULT_HEIGHT;
	vsync_p = FFG_RENDERER_DEFAULT_VSYNC;
	window_mode = FFG_WINDOW_WINDOWED;
}

/***************************************************************************//**
 * Protected. Initializes the renderer. Should only be called once per
 * application, by FFG_Engine.
 ******************************************************************************/
void FFG_Renderer::init() {
	// Initialize SDL:
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) throw FFG_RENDERER_SDL_FAIL;
	// Initialize SDL_Image:
	if (!(IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG)) throw FFG_RENDERER_IMG_FAIL;
	// Initialize the SDL_Window in accordance with the specified mode:
	Uint32 window_flags;
	switch (window_mode) {
		case FFG_WINDOW_WINDOWED:
			window_flags = SDL_WINDOW_SHOWN;
			break;
		case FFG_WINDOW_MATCHDESKTOP:
			window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP;
			break;
		// case FFG_WINDOW_FULLSCREEN:
		// 	   window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN;
		// 	   break;
		// case FFG_WINDOW_BORDERLESS:
		// 	   window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS;
		// 	   break;
	}
	window = SDL_CreateWindow(window_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width_p, screen_height_p, window_flags);
	if (!window) throw FFG_RENDERER_WINDOW_FAIL;
	// Initialize the SDL_Renderer:
	Uint32 renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE;
	if (vsync_p) renderer_flags = renderer_flags | SDL_RENDERER_PRESENTVSYNC;
	renderer = SDL_CreateRenderer(window, -1, renderer_flags);
	if (!renderer) throw FFG_RENDERER_RENDERER_FAIL;
	// Retrieve the actual size of the renderer's output:
	if (SDL_GetRendererOutputSize(renderer, &screen_width_p, &screen_height_p)) throw FFG_RENDERER_SIZE_FAIL;
}

/***************************************************************************//**
 * Protected. Uninitializes the renderer. Should only be called once per
 * application, at the very end, by FFG_Engine.
 ******************************************************************************/
void FFG_Renderer::exit() {
	// Destory the renderer:
	if (renderer) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}
	// Destroy the window:
	if (window) {
		SDL_DestroyWindow(window);
		window = nullptr;
	}
	// Uninitialize SDL:
	IMG_Quit();
	SDL_Quit();
}

/***************************************************************************//**
 * Protected. Presents what has been drawn to the screen.
 ******************************************************************************/
void FFG_Renderer::present() {
	SDL_RenderPresent(renderer);
}

/***************************************************************************//**
 * Sets the title of the window. Can be called at any time. If it is called
 * before the initialization of the window, the name will be used when the
 * window is created. If it is called after the initialization of the window,
 * will update the window's title immediately.
 * @param window_title The new window title.
 ******************************************************************************/
void FFG_Renderer::set_window_title(const std::string& window_title) {
	this->window_title = window_title;
	if (window && renderer) SDL_SetWindowTitle(window, this->window_title.c_str());
}

/***************************************************************************//**
 * Sets the screen width and height as well as its mode. Note that
 * FFG_WINDOW_MATCHDEKSTOP will ignore the width and height. Can be called
 * before engine initialization in order to set initial window state. If called
 * afterwards, will update the screen. The screen width and height specified
 * might not be the width and height used. Use FFG_Renderer::get_screen_width()
 * and FFG_Renderer::get_screen_height() to query those.
 * @param width The width of the window.
 * @param height The height of the window.
 * @param mode The window mode.
 * @return False on success. Otherwise true.
 ******************************************************************************/
bool FFG_Renderer::set_screen_mode(int width, int height, FFG_WindowMode mode) {
	if (width < 1) width = 1;
	if (height < 1) height = 1;
	window_mode = mode;
	if (renderer) {
		switch (mode) {
			case FFG_WINDOW_WINDOWED:
				if (SDL_SetWindowFullscreen(window, 0)) return true;
				SDL_SetWindowBordered(window, SDL_TRUE);
				SDL_SetWindowSize(window, width, height);
				break;
			case FFG_WINDOW_MATCHDESKTOP:
				SDL_SetWindowBordered(window, SDL_TRUE);
				SDL_SetWindowSize(window, width, height);
				if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP)) return true;
				break;
		}
		if (SDL_GetRendererOutputSize(renderer, &screen_width_p, &screen_height_p)) return true;
	} else {
		screen_width_p = width;
		screen_height_p = height;
	}
	return false;
}

/***************************************************************************//**
 * Sets Vsync to on or off. Should be set prior to running the engine,
 * otherwise this method is a no-op.
 * @param vsync TRUE if vsync should be enabled. Otherwise FALSE.
 ******************************************************************************/
void FFG_Renderer::set_vsync(bool vsync) {
	vsync_p = vsync;
}

/***************************************************************************//**
 * Gets the screen's width. O(1).
 * @return The screen's width.
 ******************************************************************************/
int FFG_Renderer::screen_width() const {
	return screen_width_p;
}

/***************************************************************************//**
 * Gets the screen's height. O(1).
 * @return The screen's height.
 ******************************************************************************/
int FFG_Renderer::screen_height() const {
	return screen_height_p;
}

/***************************************************************************//**
 * Indicates if a flag is set on the window.
 * @return If the flag is set on the window.
 ******************************************************************************/
bool FFG_Renderer::check_window_flag(FFG_WindowFlag window_flag) {
	Uint32 check_flag = 0;
	switch(window_flag) {
		case FFG_WINFLAG_MINIMIZED:
			check_flag = SDL_WINDOW_MINIMIZED;
			break;
		case FFG_WINFLAG_MAXIMIZED:
			check_flag = SDL_WINDOW_MAXIMIZED;
			break;
		case FFG_WINFLAG_INPUT_FOCUS:
			check_flag = SDL_WINDOW_INPUT_FOCUS;
			break;
		case FFG_WINFLAG_MOUSE_FOCUS:
			check_flag = SDL_WINDOW_MOUSE_FOCUS;
			break;
	}
	return check_flag & SDL_GetWindowFlags(window);
}

/***************************************************************************//**
 * Loads the texture.
 * @param texture The texture to load.
 * @return False on success. Otherwise true.
 ******************************************************************************/
bool FFG_Renderer::load_texture(FFG_Texture& texture) {
	if (texture.texture) return false;
	SDL_Surface* loaded_surface = nullptr;
	SDL_RWops* rw = nullptr;
	switch (texture.type) {
		case FFG_TEXTURE_STR:
		case FFG_TEXTURE_MEM:
			// Load the unoptimized PNG from path/memory:
			switch (texture.type) {
				case FFG_TEXTURE_STR:
					// From path:
					loaded_surface = IMG_Load(texture.path.c_str());
					break;
				case FFG_TEXTURE_MEM:
					// From memory:
					rw = SDL_RWFromConstMem(texture.mem, texture.size_b);
					if (!rw) return true;
					loaded_surface = IMG_LoadPNG_RW(rw);
					break;
			}
			// Create a texture from the surface:
			if (!loaded_surface) return true;
			texture.texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
			SDL_FreeSurface(loaded_surface);
			break;
		case FFG_TEXTURE_DRAWTO:
			// Create an empty draw-toable texture:
			texture.texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, texture.drawto_width, texture.drawto_height);
			break;
	}
	if (!texture.texture) return true;
	if (SDL_QueryTexture(texture.texture, nullptr, nullptr, &texture.loaded_width, &texture.loaded_height)) return true;
	return false;
}

/***************************************************************************//**
 * Unloads the texture.
 * @param texture The texture to unload.
 ******************************************************************************/
void FFG_Renderer::unload_texture(FFG_Texture& texture) {
	if (texture.texture) SDL_DestroyTexture(texture.texture);
	texture.texture = nullptr;
}

/***************************************************************************//**
 * Sets this texture as the current render target. If this texture was not
 * initialized as a render target, behavior is undefined.
 * @param texture The texture to set as the render target.
 * @return False on success. Otherwise true.
 ******************************************************************************/
bool FFG_Renderer::set_render_target(FFG_Texture& texture) {
	if (!texture.texture) return true;
	return SDL_SetRenderTarget(renderer, texture.texture);
}

/***************************************************************************//**
 * Sets the screen as the current target.
 * @return False on success, otherwise true.
 ******************************************************************************/
bool FFG_Renderer::reset_render_target() {
	if (!renderer) return true;
	return SDL_SetRenderTarget(renderer, nullptr);
}

/***************************************************************************//**
 * Draws the entirety of the texture to the entirety of the current target. May
 * stretch or compress the image as needed.
 * @param texture The texture to draw from.
 * @return False on success. Otherwise true.
 ******************************************************************************/
bool FFG_Renderer::draw(FFG_Texture& texture) const {
	if (!texture.texture) return true;
	return SDL_RenderCopy(renderer, texture.texture, nullptr, nullptr);
}

/***************************************************************************//**
 * Draws a portion of the texture to a location on the current target. The
 * draw-to area will be the same as the draw-from area, meaning no stretching or
 * compressing of the image will occur.
 * @param texture The texture to draw from.
 * @param source The area on the soruce texture to draw from.
 * @param screen_x The upper-left x coordinate to draw to on the current target.
 * @param screen_y The upper-left y coordinate to draw to on the current target.
 * @return False on success. Otherwise true.
 ******************************************************************************/
bool FFG_Renderer::draw(FFG_Texture& texture, FFG_Rect& source, int screen_x, int screen_y) const {
	if (!texture.texture) return true;
	SDL_Rect destination;
	destination.x = screen_x;
	destination.y = screen_y;
	destination.w = source.w;
	destination.h = source.h;
	return SDL_RenderCopy(renderer, texture.texture, &source, &destination);
}

/***************************************************************************//**
 * Draws a portion of the texture to a location on the current target. Allows
 * the target area to differ from the source area, resulting in a stretched or
 * compressed image.
 * @param texture The texture to draw from.
 * @param source The area on the source texture to draw from.
 * @param destination The area on the destination target to draw to.
 * @return False on success. Otherwise true.
 ******************************************************************************/
bool FFG_Renderer::draw(FFG_Texture& texture, FFG_Rect& source, FFG_Rect& destination) const {
	if (!texture.texture) return true;
	return SDL_RenderCopy(renderer, texture.texture, &source, &destination);
}

/***************************************************************************//**
 * Sets the draw color for clearing or drawing primitives.
 * @param r The red component of the color.
 * @param g The green component of the color.
 * @param b The blue component of the color.
 * @param a The alpha component of the color.
 * @return False on success, otherwise true.
 ******************************************************************************/
bool FFG_Renderer::set_draw_color(int r, int g, int b, int a) {
	if (!renderer) return true;
	if (r < 0) r = 0;
	if (g < 0) g = 0;
	if (b < 0) b = 0;
	if (a < 0) a = 0;
	if (r > 255) r = 255;
	if (g > 255) g = 255;
	if (b > 255) b = 255;
	if (a > 255) a = 255;
	if (SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND)) return true;
	return SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

/***************************************************************************//**
 * Draws a pixel of the current draw color on the current target.
 * @param x The x-coordinate.
 * @param y The y-coordinate.
 * @return False on success, otherwise true.
 ******************************************************************************/
bool FFG_Renderer::draw_pixel(int x, int y) {
	if (!renderer) return true;
	return SDL_RenderDrawPoint(renderer, x, y);
}

/***************************************************************************//**
 * Draws a horizontal line of the current draw color on the current target.
 * @param y The y-coordinate of both endpoints.
 * @param x1 The x-coordinate of the first endpoint.
 * @param x2 The x-coordinate of the second endpoint.
 * @return False on success, otherwise true.
 ******************************************************************************/
bool FFG_Renderer::draw_h_line(int y, int x1, int x2) {
	if (!renderer) return true;
	return SDL_RenderDrawLine(renderer, x1, y, x2, y);
}

/***************************************************************************//**
 * Draws a vertical line of current draw color on the current target.
 * @param x The x-coordinate of both endpoints.
 * @param y1 The y-coordinate of the first endpoint.
 * @param y2 The y-coordinate of the second endpoint.
 * @return False on success, otherwise true.
 ******************************************************************************/
bool FFG_Renderer::draw_v_line(int x, int y1, int y2) {
	if (!renderer) return true;
	return SDL_RenderDrawLine(renderer, x, y1, x, y2);
}

/***************************************************************************//**
 * Draws a line of the current draw color connecting two endpoints on the
 * current target.
 * @param x1 The x-coordinate of the first endpoint.
 * @param y1 The y-coordinate of the first endpoint.
 * @param x2 The x-coordinate of the second endpoint.
 * @param y2 The y-coordinate of the second endpoint.
 * @return False on success, otherwise true.
 ******************************************************************************/
bool FFG_Renderer::draw_line(int x1, int y1, int x2, int y2) {
	if (!renderer) return true;
	return SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

/***************************************************************************//**
 * Draws a rectangle of the current draw color with the given dimensions on the
 * current target.
 * @param x The x-coordinate of the upper-left of the rectangle.
 * @param y The y-coordinate of the upper-left of the rectangle.
 * @param w The width of the rectangle.
 * @param h The height of the rectangle.
 * @param filled If the rectangle should be filled or not.
 * @return False on success, otherwise true.
 ******************************************************************************/
bool FFG_Renderer::draw_rectangle(int x, int y, int w, int h, bool filled) {
	if (!renderer) return true;
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	if (filled) {
		return SDL_RenderFillRect(renderer, &rect);
	}
	return SDL_RenderDrawRect(renderer, &rect);
}

/***************************************************************************//**
 * Draws a circle of the current draw color to the current target.
 * @param x The x-coordinate of the circle center.
 * @param y The y-coordinate of the circle center.
 * @param r The radius of the circle.
 * @param filled If the circle should be filled or not.
 * @return False on success, otherwise true.
 ******************************************************************************/
bool FFG_Renderer::draw_circle(int x, int y, int r, bool filled) {
	if (!renderer) return true;
	if (r == 0) return SDL_RenderDrawPoint(renderer, x, y);
	if (r < 0) r *= -1;
	int r2 = r * r;
	if (filled) {
		if (SDL_RenderDrawLine(renderer, x, y + r, x, y - r)) return true;
		for (int ix = 1; ix <= r; ix++) {
			int iy = (int)sqrt(r2 - ix*ix);
			if (SDL_RenderDrawLine(renderer, x + ix, y + iy, x + ix, y - iy)) return true;
			if (SDL_RenderDrawLine(renderer, x - ix, y + iy, x - ix, y - iy)) return true;
		}
	} else {
		if (SDL_RenderDrawPoint(renderer, x, y + r)) return true;
		if (SDL_RenderDrawPoint(renderer, x, y - r)) return true;
		if (SDL_RenderDrawPoint(renderer, x + r, y)) return true;
		if (SDL_RenderDrawPoint(renderer, x - r, y)) return true;
		int until = (int)((double)(r) / sqrt(2.0));
		until = until + 1;
		for (int ix = 1; ix < until; ix++) {
			int iy = (int)sqrt(r2 - ix*ix);
			if (SDL_RenderDrawPoint(renderer, x + ix, y + iy)) return true;
			if (SDL_RenderDrawPoint(renderer, x + ix, y - iy)) return true;
			if (SDL_RenderDrawPoint(renderer, x - ix, y + iy)) return true;
			if (SDL_RenderDrawPoint(renderer, x - ix, y - iy)) return true;
			if (SDL_RenderDrawPoint(renderer, x + iy, y + ix)) return true;
			if (SDL_RenderDrawPoint(renderer, x + iy, y - ix)) return true;
			if (SDL_RenderDrawPoint(renderer, x - iy, y + ix)) return true;
			if (SDL_RenderDrawPoint(renderer, x - iy, y - ix)) return true;
		}
	}
	return false;
}

/***************************************************************************//**
 * Draws an ellipse of the current draw color to the current target.
 * @param x The x-coordinate of the ellipse center.
 * @param y The y-coordinate of the ellipse center.
 * @param rx The x radius of the ellipse.
 * @param ry The y radius of the ellipse.
 * @param filled If the ellipse should be filled or not.
 * @return False on success, otherwise true.
 ******************************************************************************/
bool FFG_Renderer::draw_ellipse(int x, int y, int rx, int ry, bool filled) {
	if (!renderer) return true;
	if (rx < 0) rx *= -1;
	if (ry < 0) ry *= -1;
	if (rx == ry) return draw_circle(x, y, rx, filled);
	if (rx == 0) return SDL_RenderDrawLine(renderer, x, y - ry, x, y + ry);
	if (ry == 0) return SDL_RenderDrawLine(renderer, x - rx, y, x + rx, y);
	int rx2 = rx*rx;
	int ry2 = ry*ry;
	if (filled) {
		if (SDL_RenderDrawLine(renderer, x, y + ry, x, y - ry)) return true;
		for (int ix = 1; ix <= rx; ix++) {
			int iy = (int)((double)(ry)*sqrt(1.0 - ((double)(ix*ix) / (double)(rx2))));
			if (SDL_RenderDrawLine(renderer, x + ix, y + iy, x + ix, y - iy)) return true;
			if (SDL_RenderDrawLine(renderer, x - ix, y + iy, x - ix, y - iy)) return true;
		}
	} else {
		if (SDL_RenderDrawPoint(renderer, x, y + ry)) return true;
		if (SDL_RenderDrawPoint(renderer, x, y - ry)) return true;
		int until = (int)((double)(rx2) / sqrt((double)(rx2 + ry2)));
		until = until + 1;
		for (int ix = 1; ix < until; ix++) {
			int iy = (int)((double)(ry)*sqrt(1.0 - ((double)(ix*ix) / (double)(rx2))));
			if (SDL_RenderDrawPoint(renderer, x + ix, y + iy)) return true;
			if (SDL_RenderDrawPoint(renderer, x + ix, y - iy)) return true;
			if (SDL_RenderDrawPoint(renderer, x - ix, y + iy)) return true;
			if (SDL_RenderDrawPoint(renderer, x - ix, y - iy)) return true;
		}
		until = (int)((double)(ry2) / sqrt((double)(rx2 + ry2)));
		until = until + 1;
		for (int iy = 0; iy < until; iy++) {
			int ix = (int)((double)(rx)*sqrt(1.0 - ((double)(iy*iy) / (double)(ry2))));
			if (SDL_RenderDrawPoint(renderer, x + ix, y + iy)) return true;
			if (SDL_RenderDrawPoint(renderer, x + ix, y - iy)) return true;
			if (SDL_RenderDrawPoint(renderer, x - ix, y + iy)) return true;
			if (SDL_RenderDrawPoint(renderer, x - ix, y - iy)) return true;
		}
	}
	return false;
}

/***************************************************************************//**
 * Clears the current target, filling it in with the current draw color.
 * @return False on success, otherwise true.
 ******************************************************************************/
bool FFG_Renderer::render_clear() {
	if (!renderer) return true;
	return SDL_RenderClear(renderer);
}
