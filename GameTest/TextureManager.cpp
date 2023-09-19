#include "TextureManager.h"
#include "textures.h"

const int numTextures = sizeof(texturePaths);

static SDL_Texture* texturePointers[numTextures];
static int textureUsers[numTextures] = { 0 };

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest) {
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}

SDL_Texture* TextureManager::LoadTexture(int texID){

	//if no object is using the texture to be loaded, load the texture and store its poitner in texturePointers, if the texture is being used by another object, the pointer is already there
	if (textureUsers[texID] == 0) {
		SDL_Surface* tmpSurface = IMG_Load(texturePaths[texID]);		//load a texture from a path according to its ID (paths and IDs stored in textures.h file)
		texturePointers[texID] = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
		SDL_FreeSurface(tmpSurface);
	}

	textureUsers[texID] += 1;	//update the number of users for this texture
	return texturePointers[texID];
}

void TextureManager::UnloadTexture(int texID){
	textureUsers[texID] -= 1;
	//if there are no users for the texture, destroy it
	if (textureUsers[texID] < 1) {
		SDL_DestroyTexture(texturePointers[texID]);
	}
	return;
}
