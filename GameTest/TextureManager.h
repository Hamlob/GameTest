#pragma once

#include "Game.h"
#include "SDL_image.h"

class TextureManager
{

public:
	/**
	 * Creates a SDL_Texture from a specified image.
	 * 
	 * \param fileName		Name of the image file.	
	 * \return			SDL_Texture
	 */
	static SDL_Texture* LoadTexture(const char* fileName);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);

	//static SDL_Texture* LoadTexture(int texID);
};

