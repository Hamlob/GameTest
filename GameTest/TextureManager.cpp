#include "TextureManager.h"

/*
#define DIRT_ID 0
#define GRASS_ID 1
#define WATER_ID 2
#define PLAYER_ID 3
#define ENEMY_ID 4

//store pointers to all textures in the game as static variables to prevent loading the same texture multiple times, when multiple objects look the same
static SDL_Texture* dirt_tex = nullptr;
static SDL_Texture* water_tex = nullptr;
static SDL_Texture* grass_tex = nullptr;
static SDL_Texture* player_tex = nullptr;
static SDL_Texture* enemy_tex = nullptr;
*/

SDL_Texture* TextureManager::LoadTexture(const char* texture) {

	SDL_Surface* tmpSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest) {
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}

/*
SDL_Texture* TextureManager::LoadTexture(int texID){
	switch (texID)
	{
	case DIRT_ID: 
		if (dirt_tex == nullptr) {
			dirt_tex = TextureManager::LoadTexture("textures/dirt.png");
		}
		return dirt_tex;
	case WATER_ID:
		if (water_tex == nullptr) {
			water_tex = TextureManager::LoadTexture("textures/water.png");
		}
		return water_tex;
	case GRASS_ID:
		if (grass_tex == nullptr) {
			grass_tex = TextureManager::LoadTexture("textures/grass.png");
		}
		return grass_tex;
	case PLAYER_ID:
		if (player_tex == nullptr) {
			player_tex = TextureManager::LoadTexture("textures/player.png");
		}
		return player_tex;
	case ENEMY_ID:
		if (enemy_tex == nullptr) {
			enemy_tex = TextureManager::LoadTexture("textures/enemy.png");
		}
		return enemy_tex;
	default:
		break;
	}
}
*/