#pragma once

#include "Game.h"
#include "SDL_image.h"

class TextureManager
{

public:

	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);

	/**
	 * If the texture is not used yet, loads it and returns pointer to it. If it is used, just returns poitner to the previously loaded texture.
	 * 
	 * \param texID	ID of the texture as defined in "textures.h"
	 * \return SDL_Texture*
	 */
	static SDL_Texture* LoadTexture(int texID);

	/**
	 * Keeps tracks of the texture users and destroys the texture if needed.
	 * 
	 * \param texID
	 */
	static void UnloadTexture(int texID);
};

