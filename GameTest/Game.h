#pragma once

#include "SDL.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include "textures.h"

class ColliderComp;	//forward declaration

class Game
{
public:
	Game();
	~Game();

	/**
	 * Function to initialize the required window and renderer objects and start the game.
	 *
	 * \param p_title	Title of the window
	 * \param xpos
	 * \param ypos
	 * \param width
	 * \param height
	 * \param fullscreen	1 for fullscreen, 0 for windowed mode.
	 */
	void init(const char* p_title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents();
	void update();
	void render();
	void clean();

	/**
	 * Checks if the game is currently running.
	 * 
	 * \return 1 if running, 0 if not running.
	 */
	bool running() { return _isRunning; }

	//global renderer used by all classes
	static SDL_Renderer* renderer;

	//event for input handling
	static SDL_Event event;

	//items to check collision for
	static std::vector<ColliderComp*> colliders;

private:
	int _count;
	bool _isRunning;
	SDL_Window* window;
};
