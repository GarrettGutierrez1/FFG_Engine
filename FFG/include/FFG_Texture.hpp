#ifndef FFG_TEXTURE_H_INCLUDED
#define FFG_TEXTURE_H_INCLUDED

#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <string>
#include <vector>
#include "FFG_Constants.hpp"
class FFG_Renderer;

/***************************************************************************//**
 * Texture representation. Used with FFG_Renderer to draw images to the screen
 * or to other textures.
 * 
 * Query the dimensions of the texture using:
 *
 *   - FFG_Texture::get_width()
 *   - FFG_Texture::get_height()
 *
 * See if the texture is loaded using:
 *
 *   - FFG_Texture::is_loaded()
 *
 * Set the color modulation of the texture using:
 *
 *	 - FFG_Texture::set_mod_color()
 *
 * Example usage:
 * -----------------------------------------------------------------------------
 * TODO: Add example usage.
 * -----------------------------------------------------------------------------
 ******************************************************************************/
class FFG_Texture {
private:
	friend class FFG_Renderer;
private:
	FFG_TextureType type;
	std::string path;
	void* mem;
	unsigned int size_b;
	int drawto_width;
	int drawto_height;
	SDL_Texture* texture;
	int loaded_width;
	int loaded_height;
public:
	// CONSTRUCTION:
	FFG_Texture();
	FFG_Texture(const std::string& path);
	FFG_Texture(void* const mem, const unsigned int size_b);
	FFG_Texture(const int width, const int height);
	// SETTERS:
	void set(const std::string& path);
	void set(void* const mem, const unsigned int size_b);
	void set(const int width, const int height);
	// INFO & MODIFICATION:
	bool is_loaded() const;
	int get_width() const;
	int get_height() const;
	bool set_mod_color(int r, int g, int b);
};

#endif // FFG_TEXTURE_H_INCLUDED
