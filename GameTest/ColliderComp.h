#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"

class ColliderComp: public Component
{
public:
	SDL_Rect colliderRect;
	std::string tag;

	TransformComp* transform;

	ColliderComp();
	ColliderComp(std::string name) {
		tag = name;
	}

	void init() override {

		//if the object (entity) does not have a transform component, create one
		if (false == entity->hasComponent<TransformComp>()) {
			entity->addComponent<TransformComp>();
		}
		transform = &entity->getComponent<TransformComp>();

		//add this colliders to the global list (vector) of colliders
		Game::colliders.push_back(this);
	}


	void update() override {
		colliderRect.x = static_cast<int>(transform->position.x);
		colliderRect.y = static_cast<int>(transform->position.y);
		colliderRect.w = static_cast<int>(transform->width * transform->scale);
		colliderRect.h = static_cast<int>(transform->height * transform->scale);
	}
};

