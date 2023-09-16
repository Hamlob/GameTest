#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"

Map* map;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;		//only one event at a time that changes depending on the input

//create entity manager and create a player as an entity
EntityManager manager;
auto& player(manager.addEntity());
auto& wall(manager.addEntity());

bool wall_hit = 0;

Game::Game() {

}

Game::~Game() {

}

void Game::init(const char* p_title, int xpos, int ypos, int width, int height, bool fullscreen) {

	int flag_fs = 0;
	if (true == fullscreen) {
		flag_fs = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL Initialized" << std::endl;
		
		window = SDL_CreateWindow(p_title, xpos, ypos, width, height, flag_fs);
		if (window) {
			std::cout << "Window created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
			std::cout << "Renderer initialized" << std::endl;
		}

		_isRunning = true;
	}

	else {
		_isRunning = false;
	}

	map = new Map();

	//create a player object
	player.addComponent<TransformComp>(100, 100, 64, 64, 1);
	player.addComponent<SpriteComp>("textures/player.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComp>("player");

	//create a wall
	wall.addComponent<TransformComp>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComp>("textures/dirt.png");
	wall.addComponent<ColliderComp>("wall");
}

void Game::handleEvents() {

	
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			_isRunning = false;
			break;
	}

}

void Game::update() {

	manager.refresh();
	manager.update();

	//check for collision
	if (Collision::AABB(player.getComponent<ColliderComp>().collider, wall.getComponent<ColliderComp>().collider)) {
		player.getComponent<TransformComp>().velocity * -1;		//function that multiplies the vector (velocity) by integer, does not need to be assigned to a variable, same ase setZero() function
	
		wall_hit = !wall_hit;
	
	}

	if (true == wall_hit) {
		player.getComponent<SpriteComp>().setTexture("textures/enemy.png");
	}
	else {
		player.getComponent<SpriteComp>().setTexture("textures/player.png");
	}


}


void Game::render() {

	SDL_RenderClear(renderer);

	map->DrawMap();

	manager.draw();

	SDL_RenderPresent(renderer);	


}
void Game::clean() {

	SDL_DestroyWindow(window);

}