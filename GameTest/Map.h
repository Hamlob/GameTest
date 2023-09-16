#pragma once
#include "Game.h"

constexpr auto MAP_HEIGHT = 20;
constexpr auto MAP_WIDTH = 25;
constexpr auto TILE_HEIGHT = 32;
constexpr auto TILE_WIDTH = 32;



class Map
{
public:
	Map();
	~Map();

	void LoadMap(int new_map[MAP_HEIGHT][MAP_WIDTH]);
	void DrawMap();

private:

	SDL_Rect _src, _dest;

	SDL_Texture* _dirt;
	SDL_Texture* _grass;
	SDL_Texture* _water;
	int map[MAP_HEIGHT][MAP_WIDTH];
};

