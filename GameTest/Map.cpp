#include "Map.h"
#include "TextureManager.h"

int defaultMap[MAP_HEIGHT][MAP_WIDTH] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,1,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,2,0,0,1,1,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0},
	{0,0,0,0,0,0,1,1,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,0,0,0,0,1,2,2,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

Map::Map() {
	//move all the texture loading into texture manager and make them static
	_dirt = TextureManager::LoadTexture("textures/dirt.png");
	_grass = TextureManager::LoadTexture("textures/grass.png");
	_water = TextureManager::LoadTexture("textures/water.png");

	LoadMap(defaultMap);

	_src.x = _src.y = 0;
	_src.h = _dest.h = TILE_HEIGHT;
	_src.w = _dest.w = TILE_WIDTH;

}

Map::~Map() {
	SDL_DestroyTexture(_grass);
	SDL_DestroyTexture(_dirt);
	SDL_DestroyTexture(_water);
}

void Map::LoadMap(int new_map[MAP_HEIGHT][MAP_WIDTH]) {

	for (int row = 0; row < MAP_HEIGHT; row++) 
	{
		for (int column = 0; column < MAP_WIDTH; column++) 
		{
			map[row][column] = new_map[row][column];
		}
	}

}

void Map::DrawMap() {

	int type = 0;

	for (int row = 0; row < MAP_HEIGHT; row++)
	{
		for (int column = 0; column < MAP_WIDTH; column++)
		{
			type = map[row][column];

			_dest.x = column * TILE_WIDTH;
			_dest.y = row * TILE_HEIGHT;

			switch (type) {
			case 0:
				TextureManager::Draw(_water, _src, _dest);
				break;
			case 1:
				TextureManager::Draw(_grass, _src, _dest);
				break;
			case 2:
				TextureManager::Draw(_dirt, _src, _dest);
				break;
			default:
				break;
			}
		}
	}

}
