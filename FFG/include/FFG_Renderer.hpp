#ifndef FFG_RENDERER_H_INCLUDED
#define FFG_RENDERER_H_INCLUDED

#include <cmath>
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <string>
#include "FFG_Constants.hpp"
#include "FFG_Rect.hpp"
#include "FFG_Texture.hpp"

/***************************************************************************//**
 * Renderer representation. Is inherited by FFG_Engine. Handles the drawing of
 * textures and primitives to either the screen or other textures. Methods
 * relevant to FFG_Engine initial setup are:
 *
 *   - FFG_Renderer::set_window_title()
 *   - FFG_Renderer::set_screen_mode()
 *   - FFG_Renderer::set_vsync()
 *
 * If you need to query the screen's height, width, or flags, you can use:
 *
 *   - FFG_Renderer::screen_width()
 *   - FFG_Renderer::screen_height()
 *   - FFG_Renderer::check_window_flag()
 *
 * Changing the render target is done using:
 *
 *   - FFG_Renderer::set_render_target()
 *   - FFG_Renderer::reset_render_target()
 *
 * Drawing textures is done using:
 * 
 *   - FFG_Renderer::draw()
 * 
 * Primitive drawing is done using:
 *
 *   - FFG_Renderer::set_draw_color()
 *   - FFG_Renderer::draw_pixel()
 *   - FFG_Renderer::draw_h_line()
 *   - FFG_Renderer::draw_v_line()
 *   - FFG_Renderer::draw_line()
 *   - FFG_Renderer::draw_rectangle()
 *   - FFG_Renderer::draw_circle()
 *   - FFG_Renderer::draw_ellipse()
 *   - FFG_Renderer::render_clear()
 *
 * In all cases, before rendering, you should call FFG_Renderer::render_clear()
 * while the screen is the current render target. This will clear the screen to
 * the current draw color set using FFG_Renderer::set_draw_color().
 * 
 * Example usage:
 * -----------------------------------------------------------------------------
 * TODO: Add example usage.
 * -----------------------------------------------------------------------------
 ******************************************************************************/
class FFG_Renderer {
private:
	// INTERNAL:
	SDL_Renderer* renderer;
	// WINDOW:
	SDL_Window* window;
	std::string window_title;
	int screen_width_p;
	int screen_height_p;
	FFG_WindowMode window_mode;
	bool vsync_p;
protected:
	// CONTROL:
	FFG_Renderer();
	void init();
	void exit();
	void present();
public:
	// WINDOW:
	void set_window_title(const std::string& window_title);
	bool set_screen_mode(int width, int height, FFG_WindowMode mode);
	void set_vsync(bool vsync);
	int screen_width() const;
	int screen_height() const;
	bool check_window_flag(FFG_WindowFlag window_flag);
	// TEXTURE LOADING & UNLOADING:
	bool load_texture(FFG_Texture& texture);
	void unload_texture(FFG_Texture& texture);
	// RENDER TARGET:
	bool set_render_target(FFG_Texture& texture);
	bool reset_render_target();
	// TEXTURE DRAWING:
	bool draw(FFG_Texture& texture) const;
	bool draw(FFG_Texture& texture, FFG_Rect& source, int screen_x, int screen_y) const;
	bool draw(FFG_Texture& texture, FFG_Rect& source, FFG_Rect& destination) const;
	// PRIMITIVE DRAWING:
	bool set_draw_color(int r, int g, int b, int a);
	bool draw_pixel(int x, int y);
	bool draw_h_line(int y, int x1, int x2);
	bool draw_v_line(int x, int y1, int y2);
	bool draw_line(int x1, int y1, int x2, int y2);
	bool draw_rectangle(int x, int y, int w, int h, bool filled);
	bool draw_circle(int x, int y, int r, bool filled);
	bool draw_ellipse(int x, int y, int rx, int ry, bool filled);
	// BUFFER CONTROL:
	bool render_clear();
};

#endif // FFG_RENDERER_H_INCLUDED
