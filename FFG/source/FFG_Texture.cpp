#include "FFG_Texture.hpp"

/***************************************************************************//**
 * Constructor.
 ******************************************************************************/
FFG_Texture::FFG_Texture() {
	type = FFG_TEXTURE_DRAWTO;
	path = "";
	mem = nullptr;
	size_b = 0;
	drawto_width = 640;
	drawto_height = 480;
	texture = nullptr;
	loaded_width = -1;
	loaded_height = -1;
}

/***************************************************************************//**
 * Setting constructor. Refer to set.
 * @param path The path to the image in .png format.
 ******************************************************************************/
FFG_Texture::FFG_Texture(const std::string& path) {
	set(path);
}

/***************************************************************************//**
 * Setting constructor. Refer to set.
 * @param mem A pointer to the image data, encoded as a .png.
 * @param size_b The size of the data pointed to by mem.
 ******************************************************************************/
FFG_Texture::FFG_Texture(void* const mem, const unsigned int size_b) {
	set(mem, size_b);
}

/***************************************************************************//**
 * Setting constructor. Refer to set.
 * @param width The width of the texture.
 * @param height The height of the texture.
 ******************************************************************************/
FFG_Texture::FFG_Texture(const int width, const int height) {
	set(width, height);
}

/***************************************************************************//**
 * Sets the FFG_Texture to load an image from the path. Textures loaded this way
 * cannot be used as render targets.
 * @param path The path to the image in .png format.
 ******************************************************************************/
void FFG_Texture::set(const std::string& path) {
	type = FFG_TEXTURE_STR;
	this->path = path;
}

/***************************************************************************//**
 * Sets the FFG_Texture to load an image from a memory pointer. Textures loaded
 * this way cannot be used as render targets.
 * @param mem A pointer to the image data, encoded as a .png.
 * @param size_b The size of the data pointed to by mem.
 ******************************************************************************/
void FFG_Texture::set(void* const mem, const unsigned int size_b) {
	type = FFG_TEXTURE_MEM;
	this->mem = mem;
	this->size_b = size_b;
}

/***************************************************************************//**
 * Sets the FFG_Texture to load an empty image of a specified size. Textures
 * loaded this way can be used as render targets.
 * @param width The width of the texture.
 * @param height The height of the texture.
 ******************************************************************************/
void FFG_Texture::set(const int width, const int height) {
	type = FFG_TEXTURE_DRAWTO;
	drawto_width = width;
	drawto_height = height;
}

/***************************************************************************//**
 * Indicates if the texture is loaded.
 * @return True if the texture is loaded, otherwise false.
 ******************************************************************************/
bool FFG_Texture::is_loaded() const {
	if (!texture) return true;
	return false;
}

/***************************************************************************//**
 * Returns the width of the texture. Should only be called after the texture is
 * loaded.
 * @return The width of the texture.
 ******************************************************************************/
int FFG_Texture::get_width() const {
	if (!texture) return -1;
	return loaded_width;
}

/***************************************************************************//**
 * Returns the height of the texture. Should only be called after the texture is
 * loaded.
 * @return The height of the texture.
 ******************************************************************************/
int FFG_Texture::get_height() const {
	if (!texture) return -1;
	return loaded_height;
}

/***************************************************************************//**
 * Sets the texture modulation when drawing. Should only be called after the
 * texture is loaded.
 * @return The height of the texture.
 ******************************************************************************/
bool FFG_Texture::set_mod_color(int r, int g, int b) {
	if (!texture) return true;
	if (r < 0) r = 0;
	if (g < 0) g = 0;
	if (b < 0) b = 0;
	if (r > 255) r = 255;
	if (g > 255) g = 255;
	if (b > 255) b = 255;
	return SDL_SetTextureColorMod(texture, r, g, b);
}
