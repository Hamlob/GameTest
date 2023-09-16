#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"

class ColliderComp: public Component
{
public:
	SDL_Rect collider;
	std::string tag;

	TransformComp* transform;

	ColliderComp();
	ColliderComp(std::string name) {
		tag = name;
	}

	void init() override {

		//if the object (entity) does not have a transform component, create one
		if (false == entity_p->hasComponent<TransformComp>()) {
			entity_p->addComponent<TransformComp>();
		}
		transform = &entity_p->getComponent<TransformComp>();
	}


	void update() override {
		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
		collider.w = static_cast<int>(transform->width * transform->scale);
		collider.h = static_cast<int>(transform->height * transform->scale);
	}
};

