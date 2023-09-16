#include "SDL.h"
#include "Game.h"
#include "TextureManager.h"
#include <cstdlib>

using namespace std;

const int WIDTH = 800;
const int HEIGHT = 640;
const int FULLSCREEN = 1;
const int WINDOWED = 0;
const int FPS = 60;
const int FRAME_DURATION = 1000 / FPS;	//in ms

Uint32 frameStart;
int frameTime;
int input;

Game* game = nullptr;

int main(int argc, char* argv[]) {

	game = new Game();

	game->init("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, WINDOWED);

	while (game->running()) {

		frameStart = SDL_GetTicks();	//start time of each frame

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;	//time since the start of this frame

		//introduce delay to ensure each frame lasts for FRAME_DURATION
		if (frameTime < FRAME_DURATION) {
			SDL_Delay(FRAME_DURATION - frameTime);
		}
	}
	game->clean();

	return 0; 
}