#pragma once
#include "Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	TransformComp* transform;

	//init function gets the pointer to the transform component of this game object (entity)
	void init() override {
		transform = &entity->getComponent<TransformComp>();
	}

	void update() override {


		//assign appropriate velocity direction depending on the movement keys pressed
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -1;		//-1 because y position increases downwards (starts at top)
				break;
			case SDLK_a:
				transform->velocity.x = -1;		//x position increases towards right
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				break;
			default:
				break;
			}
		}


		//reset the velocity to 0 when the movement keys are released
		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				break;
			case SDLK_a:
				transform->velocity.x = 0;		
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				break;
			default:
				break;
			}
		}
	}

};

